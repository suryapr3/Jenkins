/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/
/**
 * @file    underrun_B_with_A.c
 * @brief   1. HOST Configuration code for evaluating the underrun in B path when A path is enabled.
            2. The expected result was assert the PDPD main underrun , keep playing last sample
               until new sample arrives.
 * @TC Description:
        1. Continuous blocks will be streamed at a required rate to V2D CM0 (A Path) from
           configured VEX core.
        2. 1 block of samples for given data rate will be streamed to V2D CM1 (B Path) from
           configured VEX core.
        3. Rx loop back is enabled so data will be looped back along with path F from CM0 and
           looped back via path D from CM1.
        4. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the VEX cores which is same as Tx vex.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison was done HOST will read the result.
        6. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        7. Read the Interrupt status register and check whether PDPD_INTERRUPT was set or not.
        8. Indicate the VEX core to start continuous transmission to CM1.
        9. Clear the PDPD_MAIN_INTERRUPT by writing to the INT_CLEAR register.
        10. Read the Interrupt status register and check whether PDPD_INTERRUPT was reset or not.
        11. Indicate both the VEX cores to stop the transmission.
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"
#include "srp_v2d_regs.h"
#include "srp_vexa_vexabc_regs.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "flow6_common_utils.h"

#include "v2d_path_b.map.h"
#include "v2d_path_a.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define PASSTHRU_I_COEFF    (1 << 13)
#define PASSTHRU_Q_COEFF    0

#define RX_PACKET_SZ_VALUE  ((2 << 16) | 2) /*Rx_stream0 and Rx_pd_stream0 set to 2*/
#define TX_SIF_CTRL_VALUE   ((1 << 9)| 2)   /*RX loopbak was set and TX_SYS_RATE was set to 0.5IQ*/

#define TX_UNDERRUN_BIT 12
#define TX_NO_DATA_START_BIT    13
#define INTERRUPT_VALUE ((1 << PDPD_MAIN_UNDERRUN_BIT) | (1 << TX_NO_DATA_START_BIT) | (1 << TX_UNDERRUN_BIT))
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const uint32_t v2d_host_id[][2][2] = {
    {{0x44, 0x45},   // Host ID for V2D0_Port0 and V2D0_Port1
     {0x46, 0x47}},   // Host ID for V2D0_Port2 and V2D0_Port3
    {{0x4A, 0x4B},   // Host ID for V2D1_Port0 and V2D1_Port1
     {0x4C, 0x4D}},   // Host ID for V2D1_Port2 and V2D1_Port3
    {{0x50, 0x51},   // Host ID for V2D2_Port0 and V2D2_Port1
     {0x52, 0x53}},   // Host ID for V2D2_Port2 and V2D2_Port3
    {{0x56, 0x57},   // Host ID for V2D3_Port0 and V2D3_Port1
     {0x58, 0x59}},   // Host ID for V2D3_Port2 and V2D3_Port3
    {{0x5C, 0x5D},   // Host ID for V2D4_Port0 and V2D4_Port1
     {0x5E, 0x5F}},   // Host ID for V2D4_Port2 and V2D4_Port3
    {{0x62, 0x63},   // Host ID for V2D5_Port0 and V2D5_Port1
     {0x64, 0x65}},   // Host ID for V2D5_Port2 and V2D5_Port3
    {{0x68, 0x69},   // Host ID for V2D6_Port0 and V2D6_Port1
     {0x6A, 0x6B}},   // Host ID for V2D6_Port2 and V2D6_Port3
    {{0x6E, 0x6F},   // Host ID for V2D7_Port0 and V2D7_Port1
     {0x70, 0x71}}   // Host ID for V2D7_Port2 and V2D7_Port3
};

/* Vectors per block for the given sample rate which was defined as per order in pdpd_rate_t enum*/
const int g_vectors_per_block[] = {8, 16, 32, 64, 128};

/* The value should be (number of flits per data block -1) and the MSB bit should be set to enable the corresponding
 * stream*/
const uint32_t g_tx_strm_cnt0_value[] = {0x8000000F, 0x8000001F, 0x8000003F, 0x8000007F, 0x800000FF};

/* Bit 8 to 11 indicates the Block size in flits which should be equal to corresponding elements in g_vectors_per_block
 * array for the given sample rate which was defined as per order in pdpd_rate_t enum*/
const int g_md_control_tbl[] = {0x400, 0x500, 0x600, 0x700, 0x800};

// The last entry should be CIO2STRM_STRM_DEST0_OFFSET
static v2d_flow6_tbl_t g_cio2strm_config_tbl[] = {
// INT Enable
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_INT_ENABLE, CIO2STRM_INT_EN_VALUE, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_INT_ENABLE_WR_MASK, \
        "CIO2STRM_INT_ENABLE"},
//VE00 cio2strm
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_FIFO_STATUS_CTL, CIO2STRM_FIFO_STATUS_CTL_VALUE,
        VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_FIFO_STATUS_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_WORD_CNT_CTL, CIO2STRM_WORD_CNT_CTL_VALUE, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_WORD_CNT_CTL_WR_MASK, \
        "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the single stream from vex core to CRUX*/
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_RANGE_EN, 0x00000001, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(0), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(0), 0x0FFFFFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(0), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[0] - mapped to V2D_0_Port_0
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(0), 0x00000044, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"}
};

static v2d_flow6_tbl_t g_strm2cio_config_tbl[] = {
// INT Enable
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_INT_ENABLE, STRM2CIO_INT_ENABLE_VALUE, VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_INT_ENABLE_WR_MASK, \
        "STRM2CIO_INT_ENABLE"},

// VE00 strm2cio
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_FIFO_STATUS_CTL, STRM2CIO_FIFO_STATUS_CTL_VALUE, \
        VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_FIFO_STATUS_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_WORD_CNT_CTL, STRM2CIO_WORD_CNT_CTL_VALUE, VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_WORD_CNT_CTL_WR_MASK, \
        "STRM2CIO_MEM_WORD_CNT_CTL"}
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last Three entries order shouldn't be modified*/
static v2d_flow6_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL(0)), FIFO_CONTROL_VALUE, \
        V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_CREDIT_CS(0)), CREDIT_CS_VALUE, V2D_AV2D_APB_NSIP_HBI_0_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_MISC_CTRL(0)), MISC_CTRL_VALUE, V2D_AV2D_APB_NSIP_HBI_0_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},
    // These are for Buffer A0
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MAP_TBL(0,0)), 0x80000000, V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MASK_TBL(0,0)), 0x7FFF, V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_FIFO_CSR_H2B_FIFO_CONTROL(0), FIFO_CONTROL_VALUE, \
        V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_CREDIT_READY_CS(0), CREDIT_CS_VALUE, V2D_AV2D_APB_NSIP_HBI_0_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_FC_EN(0), MISC_CTRL_VALUE, V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},
    /* 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case */
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_SZ_HW_TBL(0,0), 0x9, V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ADDR_LKUP_TBL(0,0), 0x4020, V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ADDR_LKUP_TBL(0,0), 0x4000, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_ADDR_LKUP_TBL(0,0), 0x80001000, V2D_AV2D_APB_NSIP_HBI_0_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_CONTROL_TBL(0,0), 0x400, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 3 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last 4 entries order shouldn't be modified*/
static v2d_flow6_tbl_t g_cm_1_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_AV2D_APB_NSIP_HBI_1_INT_CSR_INT_HIGH_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_1_INT_CSR_INT_HIGH_EN_WR_MASK, \
        "HBI_1_INT_HIGH_EN"},
    {V2D_AV2D_APB_NSIP_HBI_1_INT_CSR_INT_LOW_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_1_INT_CSR_INT_LOW_EN_WR_MASK, \
        "HBI_1_INT_LOW_EN"},

// B2H Registers
    {(V2D_AV2D_APB_NSIP_HBI_1_B2H_FIFO_CSR_B2H_FIFO_CONTROL(0)), FIFO_CONTROL_VALUE, \
        V2D_AV2D_APB_NSIP_HBI_1_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "HBI_1_B2H_FIFO_CONTROL"},
    {(V2D_AV2D_APB_NSIP_HBI_1_B2H_CREDIT_CS(0)), CREDIT_CS_VALUE, V2D_AV2D_APB_NSIP_HBI_1_B2H_CREDIT_CS_WR_MASK, "HBI_1_B2H_CREDIT_CS"},
    {(V2D_AV2D_APB_NSIP_HBI_1_B2H_MISC_CTRL(0)), MISC_CTRL_VALUE, V2D_AV2D_APB_NSIP_HBI_1_B2H_MISC_CTRL_WR_MASK, "HBI_1_B2H_MISC_CTRL"},
    {(V2D_AV2D_APB_NSIP_HBI_1_B2H_ADDR_MAP_TBL(0,0)), 0x80000000, V2D_AV2D_APB_NSIP_HBI_1_B2H_ADDR_MAP_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits
    {(V2D_AV2D_APB_NSIP_HBI_1_B2H_ADDR_MASK_TBL(0,0)), 0x7FFF, V2D_AV2D_APB_NSIP_HBI_1_B2H_ADDR_MASK_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_FIFO_CSR_H2B_FIFO_CONTROL(0), FIFO_CONTROL_VALUE, \
        V2D_AV2D_APB_NSIP_HBI_1_H2B_FIFO_CSR_H2B_FIFO_CONTROL_WR_MASK, "CM_1_H2B_FIFO_CONTROL"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_CREDIT_READY_CS(0), CREDIT_CS_VALUE, V2D_AV2D_APB_NSIP_HBI_1_H2B_CREDIT_READY_CS_WR_MASK, \
        "CM_1_H2B_CREDIT_CS"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_BUF_FC_EN(0), MISC_CTRL_VALUE, V2D_AV2D_APB_NSIP_HBI_1_H2B_BUF_FC_EN_WR_MASK, "CM_1_H2B_FC_EN"},
    /* 512 flits of DEST Buffer Size in VEX corresponds to 2 blocks of data for max 8GSPS case*/
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_BUF_SZ_HW_TBL(0,0), 0x9, V2D_AV2D_APB_NSIP_HBI_1_H2B_BUF_SZ_HW_TBL_WR_MASK, "HBI_1_H2B_BUF_SZ_HW_TBL"},
    /* Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_TK_ADDR_LKUP_TBL(0,0), 0x4020, V2D_AV2D_APB_NSIP_HBI_1_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ADDR_LKUP_TBL_0"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_ADDR_LKUP_TBL(0,0), 0x4000, V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ADDR_LKUP_TBL_0"},
    /* Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_ADDR_LKUP_TBL(0,0), 0x80001000, V2D_AV2D_APB_NSIP_HBI_1_H2B_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_ADDR_LKUP_TBL"},
    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_CONTROL_TBL(0,0), 0x400, V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_CONTROL_TBL_WR_MASK, \
        "HBI_1_H2B_MD_CONTROL_TBL"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_1_H2B_ROUTE_LKUP_TBL_WR_MASK, "HBI_1_H2B_ROUTE_LKUP_TBL"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_TK_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_1_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ROUTE_LKUP_TBL"},
    {V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_1_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ROUTE_LKUP_TBL"}
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last 3 entries order shouldn't be modified*/
static v2d_flow6_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_AV2D_APB_CSR_INT_HIGH_EN(0), CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_AV2D_APB_CSR_INT_LOW_EN(0), CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Rx Path Settings
    {V2D_AV2D_APB_CSR_RX_PACKET_SZ(0), RX_PACKET_SZ_VALUE, V2D_AV2D_APB_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},

// Tx Path Settings
    {V2D_AV2D_APB_CSR_TX_SIF_CTRL(0), TX_SIF_CTRL_VALUE, V2D_AV2D_APB_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_AV2D_APB_CSR_TX_PTR_BOUND(0,0), 0x3FF0000, V2D_AV2D_APB_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_AV2D_APB_CSR_TX_PD_PTR_BOUND(0,0), 0x7FF0400, V2D_AV2D_APB_CSR_TX_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    {V2D_AV2D_APB_CSR_TX_STREAM_CNT(0,0), 0x8000000F, V2D_AV2D_APB_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_AV2D_APB_CSR_RX_STREAM_CNT(0,0), 0x8000000F, V2D_AV2D_APB_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
    /* The last 3 entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    {V2D_AV2D_APB_CSR_PIF_CTRL(0) ,0x0, V2D_AV2D_APB_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    {V2D_AV2D_APB_CSR_TX_PD_STREAM_CNT(0,0), 0x8000000F, V2D_AV2D_APB_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_AV2D_APB_CSR_RX_PD_STREAM_CNT(0,0), 0x8000000F, V2D_AV2D_APB_CSR_RX_PD_STREAM_CNT_WR_MASK, "RX_PD_STREAM_CNT0"},
    /************************************************************************************************************/
};

v2d_flow6_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

v2d_flow6_tbl_t g_v2d_pdpd_passthru_config_tbl[] = {
    //I[31:16]Q[15:0]. I= 2^13, Q=0
    {V2D_PDPD_PASSTHRU_C_SHDW(0), ((0x2<<13)<<16), V2D_PDPD_PASSTHRU_C_SHDW_WR_MASK , "PDPD_PASSTHRU_C_SHDW"},
    {V2D_PDPD_PASSTHRU_C_LIVE(0), ((0x2<<13)<<16), V2D_PDPD_PASSTHRU_C_LIVE_WR_MASK, "PDPD_PASSTHRU_C_LIVE"}
};

v2d_flow6_tbl_t g_v2d_pdpd_config_config_tbl[] = {
    //passthru_dly =0, pdpd_rate-> run time param
    {V2D_PDPD_CONFIG(0), 0x7, V2D_PDPD_CONFIG_WR_MASK, "PDPD_CONFIG"}
};

v2d_flow6_tbl_t g_v2d_pdpd_control_config_tbl[] = {
    {V2D_PDPD_CONTROL(0), 0x0, V2D_PDPD_CONTROL_WR_MASK, "PDPD_CONTROL"}
};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int configure_v2d_host(int, int, int, pdpd_rate_t);
int release_reset_abc_noc(void *);
int flow6_configure_pdpd(int, int, pdpd_rate_t);
int flow6_bfn_force_trigger(int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id, V2d Id, APB Id and SYS_RATE_IQ_P5
 * @return          status
 */
int configure_v2d_host(int vex_num, int v2d_num, int apb_num, pdpd_rate_t pdpd_rate)
{
    int i, j = 0, rv = 0, host_id = 0, vex_id = 0, rx_gnrl_csr_value = 0;

    rx_gnrl_csr_value = ((1 << 2) | 1); // RX_PD_CFG_COMPLETE and RX_CFG_COMPLETE are set

    for (j = 0; j < 2; j++)
    {
        vex_id = vex_num + j;
        host_id = v2d_host_id[v2d_num][apb_num][1 - j];

        for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
        {
            if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_id, g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
                return rv;
        }

        // Corresponds to cio2strm dest id
        if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_id, g_cio2strm_config_tbl[i].offset, host_id, \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;

        printf("INFO: cio2strm configuration completed");

        for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
        {

            if (rv = write_reg(SRP_BLOCK_VEX_CORE, (vex_id), g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                        g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
                return rv;
        }
        printf("INFO: strm2cio configuration completed");
    }
        // SDF init
    if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM, \
                HIVE_ADDR_v2d_path_b_consumer_sm_gate, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {

        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), (vex_num + 1), \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    for (i = 0; i < ARRAY_SIZE(g_cm_1_config_tbl) - 4; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 3; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_md_control_tbl[pdpd_rate], \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), vex_num, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf ("INFO: CM configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 3); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 2); i++)
    {
       if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_config_tbl[i].offset), \
                   (g_v2d_config_tbl[i].value | pdpd_rate), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl)); i++)
    {
       if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_config_tbl[i].offset), \
                   (g_tx_strm_cnt0_value[pdpd_rate]), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }

    rv = flow6_configure_pdpd(v2d_num, apb_num, pdpd_rate);
    printf("INFO: V2D pdpd configuration completed");

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + V2D_AV2D_APB_CSR_TX_GNRL_CSR(0)), TX_GNRL_CSR_VALUE, \
            V2D_AV2D_APB_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + V2D_AV2D_APB_CSR_RX_GNRL_CSR(0)), rx_gnrl_csr_value, \
            V2D_AV2D_APB_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D configuration completed");


    return rv;
}


/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id and pdpd_rate
 * @return          none
 */
int flow6_configure_pdpd(int v2d_num, int apb_num, pdpd_rate_t pdpd_rate)
{
    int rv = 0;
    int i_value = 0, q_value = 0, update_passthru = 0;
    i_value = PASSTHRU_I_COEFF;
    q_value = PASSTHRU_Q_COEFF;

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_config_reg_config(v2d_num, apb_num, pdpd_rate))
    {
        printf ("PDPD reg config failed\n");
        return rv;
    }
    if (rv = pdpd_control_reg_config(v2d_num, apb_num, update_passthru))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_reg_config(v2d_num, apb_num, i_value, q_value))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    printf("INFO: PDPD configuration Completed");
    return rv;
}

int main(int argc, const char *argv[])
{
    int rv = 0, test_result = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int apb_num = 0, host_flag = 1, vex_num = 0, v2d_num = 0, underrun_sample = 0, expected_underrun_sample = 0, pdpd_rate = 0,
        loop_wait_count = 0;
    volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0,
             host_indicator = 0, underrun_reg_value = 0, num_blocks_sent = 0;
    int dmem_offset = 0x4000;
    int vex_path_b_offset_val[] = {HIVE_ADDR_v2d_path_b_g_scalar_val, HIVE_ADDR_v2d_path_b_g_num_vecs_in,
                                HIVE_ADDR_v2d_path_b_g_num_blocks, HIVE_ADDR_v2d_path_b_g_tbs_in_blk,
                                HIVE_ADDR_v2d_path_b_g_dest_buffer_base, HIVE_ADDR_v2d_path_b_g_host_indicator,
                                HIVE_ADDR_v2d_path_b_g_count1};
    unsigned int vex_path_b_args_val[] = {0x00120014, NUMBER_OF_VECTORS_INPUT, 1, 64, 0, 0, 0};
    int vex_path_a_offset_val[] = {HIVE_ADDR_v2d_path_a_g_scalar_val, HIVE_ADDR_v2d_path_a_g_num_vecs_in,
                                   HIVE_ADDR_v2d_path_a_g_host_indicator, HIVE_ADDR_v2d_path_a_g_dest_buffer_base};
    unsigned int vex_path_a_args_val[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};

    init(); /* Initialize the srp*/

#if (1 == REGRESSION)
    subsys_reset_cycle();
    v2d_reset_cycle();
    crux_reset_cycle();
    vex_reset_cycle();
#endif

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);
    printf ("INFO: argv[0] : %d\n", argv[0]);
    printf ("INFO: argv[1] : %d\n", argv[1]);
    printf ("INFO: argv[2] : %d\n", argv[2]);
    vex_num = argv[0];
    v2d_num = argv[1];
    apb_num = argv[2];
    pdpd_rate = argv[3];
    printf("INFO: vex_num : %d, v2d_num : %d, apb_num : %d, pdpd_rate: %d\n", vex_num, v2d_num, apb_num, pdpd_rate);

    vex_path_b_args_val[1] = g_vectors_per_block[pdpd_rate];
    vex_path_b_args_val[2] = 1;
    vex_path_b_args_val[3] = VEX_MAX_BUF_SIZE / g_vectors_per_block[pdpd_rate];

    vex_path_a_args_val[1] = g_vectors_per_block[PDPD_RATE_IQ_P5];

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = configure_v2d_host(vex_num, v2d_num, apb_num, pdpd_rate))
    {
        printf ("ERROR: configure_v2d_host\n");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, vex_params)))
        return rv;

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    /*Clearing the VEX VMEM and DMEM for both vex cores*/
    if (rv = vex_mem_clear(vex_num, srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num);
        return rv;
    }
    if (rv = vex_mem_clear((vex_num + 1), srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num + 1);
        return rv;
    }

    /* vex_num will be used to feed the data to Tx Path B and to loop it back via path D
     * vex_num + 1 will be used to feed the data to Tx path A and to loop it back via path F
     * there by realizing the post processing use case configuration*/
    printf("Host: start vex Rx program load \n");
    if ((rv = srp_vex_loader(vex_hdl, vex_num, "vex_fw/sim_m64/v2d_path_b.fw")))
        return rv;

    if ((rv = srp_vex_loader(vex_hdl, vex_num + 1, "vex_fw/sim_m64/v2d_path_a.fw")))
        return rv;

    printf("Host: vex program load - done\n");

    /* Loading the host parameters to VEX core feeding path B*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_b_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + vex_path_b_offset_val[lc],
                        &vex_path_b_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Loading the host parameters to VEX core feeding path C*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_a_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        (vex_num + 1),
                        dmem_offset + vex_path_a_offset_val[lc],
                        &vex_path_a_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Input Vector Generation , input is generated with (EVEN values for IQ avoiding the LSB difference from PDPD) in such a way that
     * with PASSTHRU gain configured the same data will be received as output.*/
    for (i = 0; i < g_vectors_per_block[pdpd_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j *2)))  ;
        }
    }

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_b_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num + 1,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_a_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;


    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, (vex_num + 1), 0);   // Start A+F
    srp_vex_start(vex_hdl, vex_num, 0); // Start B+D
    printf("Host: vex program start - done\n");

    usleep(1000);

    /* This BFN order need not be maintained specific to this TC we are starting A path first and then B path reversing the order
     * was also verified and it is passing*/
    while ((b2h_flit_cnt += read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_NSIP_HBI_0_B2H_FLIT_COUNT(apb_num), "B2H_FLIT_COUNT")) <
            3 * (VEC2FLIT(g_vectors_per_block[PDPD_RATE_IQ_P5])))
    {
        // do nothing wait until 1 blocks are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT for CM0 is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /* Trigger the forced BFN for path A*/
    if (0 == apb_num)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_CONFIG(0), 0x1, \
                V2D_BFN_CSR_BFNE_CONFIG_WR_MASK, "BFNE_CONFIG0"))
            return rv;
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_START(0), 0xFFFFFFFF, \
                V2D_BFN_CSR_BFNE_START_WR_MASK, "BFNE_START0"))
            return rv;
    }
    else if (1 == apb_num)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_CONFIG(1), 0x1, \
                V2D_BFN_CSR_BFNE_CONFIG_WR_MASK, "BFNE_CONFIG1"))
            return rv;
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_START(1), 0xFFFFFFFF, \
                V2D_BFN_CSR_BFNE_START_WR_MASK, "BFNE_START1"))
            return rv;
    }

    b2h_flit_cnt = 0;
    loop_wait_count = 0;

    while ((b2h_flit_cnt += read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_NSIP_HBI_1_B2H_FLIT_COUNT(apb_num), "HBI_1_B2H_FLIT_COUNT")) <
            (VEC2FLIT(g_vectors_per_block[pdpd_rate])))
    {
        // do nothing wait until 1 blocks are received in this loop
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT for CM1 is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf("HOST: b2h flit cnt: %d\n",b2h_flit_cnt);

    /*Triggering the forced BFN for path B*/
    if (rv = flow6_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }

    usleep(10000);
    loop_wait_count = 0;

    while (host_vec_processed < (1 * g_vectors_per_block[pdpd_rate]))
    {
        if ((rv = srp_core_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + HIVE_ADDR_v2d_path_b_g_count1,
                        &host_vec_processed,
                        1,
                        flags)))
            return rv;

        if (loop_wait_count >= 30)
        {
            printf("ERROR: VEX core didn't processed enough vectors\n");
            rv = 1;
            return rv;
        }

        loop_wait_count ++;
        usleep(10000);
    }

    /* Reading the results from Rx VEX*/
    if ((rv = srp_core_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_v2d_path_b_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_core_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_v2d_path_b_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x\n", host_blocks_processed - vex_path_b_args_val[0]);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV\n");
        test_result = 1;
    }
    else
    {
        printf("Received output matches with Reference output\n");
    }

    /* The expectation is only PDPD_UNDERRUN_BIT will be set and TX_UNDERRUN will not be set*/
    underrun_reg_value = read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_STATUS(apb_num), "V2D_INT_STATUS");

    if (underrun_reg_value & PDPD_MAIN_UNDERRUN_VALUE)
    {
        printf ("HOST: B buffer (PDPD main data )Underrun flag was set\n");
    }
    else
    {
        printf ("ERROR: PDPD underrun flag was not set , interrupt register value is %x\n", underrun_reg_value);
        test_result = 1;
    }

    /* Read the last sample that will be streamed continuously*/
    usleep(10000);
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_b_vbuffer_out,/*local_addr*/
                        &underrun_sample,
                        sizeof(int)))
        return rv;

    expected_underrun_sample = val_inp[(g_vectors_per_block[pdpd_rate] - 1)][(NUM_OF_ELEMENTS_PER_VEC - 1)] + vex_path_b_args_val[0];

    if (underrun_sample != expected_underrun_sample)
    {
        printf("ERROR: Last valid sample hasn't been streamed for Path B after the first underrun\n");
        printf("Expected : %x, received : %x\n", expected_underrun_sample, underrun_sample);
        test_result = 1;
    }
    else
    {
        printf("HOST: Last valid sample has been streamed continuously for path B after the first underrun\n");
    }

    /* Indicate the VEX PATH B to start continuous transmission*/
    host_indicator = 1;
    if ((rv = srp_core_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_v2d_path_b_g_host_indicator,
                    &host_indicator,
                    1,
                    flags)))
        return rv;

    /*Clear the PDPD MAIN UNDERRUN interrupt in status register*/
    if (rv = write_whole_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_CLEAR(apb_num), PDPD_MAIN_UNDERRUN_VALUE, 0xFFFFFFF, "CSR_INT_CLEAR"))
        return rv;

    /* The expectation is PDPD_MAIN_UNDERRUN_BIT will be reset*/
    underrun_reg_value = read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_STATUS(apb_num), "V2D_INT_STATUS");

    if (0 == (underrun_reg_value & PDPD_MAIN_UNDERRUN_VALUE))
    {
        printf ("HOST: B buffer (PDPD main data) Underrun flag was not set\n");
    }
    else
    {
        printf ("ERROR: underrun flag was set , interrupt register value is %x\n", underrun_reg_value);
        test_result = 1;
    }

    /* Indicate both the vex cores to stop transmission*/
    host_indicator = 2;
    if ((rv = srp_core_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_v2d_path_b_g_host_indicator,
                    &host_indicator,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_core_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    (vex_num + 1),
                    dmem_offset + HIVE_ADDR_v2d_path_a_g_host_indicator,
                    &host_indicator,
                    1,
                    flags)))
        return rv;

    usleep(10000);
    underrun_sample = 0;

    /* Read the last sample that will be streamed continuously*/
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_b_vbuffer_out,/*local_addr*/
                        &underrun_sample,
                        sizeof(int)))
        return rv;

    expected_underrun_sample = val_inp[(g_vectors_per_block[pdpd_rate] - 1)][(NUM_OF_ELEMENTS_PER_VEC - 1)] +\
                               (2 * vex_path_b_args_val[0]);
    if (underrun_sample != expected_underrun_sample)
    {
        printf("ERROR: Last valid sample hasn't streamed for path B after the second underrun\n");
        printf("Expected : %x, received : %x\n", expected_underrun_sample, underrun_sample);
        printf("num_blocks_sent: %x\n", num_blocks_sent);
        test_result = 1;
    }
    else
    {
        printf("HOST: Last valid sample has been streamed continuously for path B after the second underrun\n");
    }

    usleep(10000);
    num_blocks_sent = 0;
    underrun_sample = 0;

    /* Read the number of blocks sent by vex_path_a and last sample that will be streamed continuously*/
    if ((rv = srp_core_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    (vex_num + 1),
                    dmem_offset + HIVE_ADDR_v2d_path_a_g_num_blocks,
                    &num_blocks_sent,
                    1,
                    flags)))
        return rv;

    if (rv = srp_vex_memid_load(vex_hdl,
                        (vex_num + 1),
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_a_vbuffer_out,/*local_addr*/
                        &underrun_sample,
                        sizeof(int)))
        return rv;


    expected_underrun_sample = val_inp[(g_vectors_per_block[PDPD_RATE_IQ_P5] - 1)][(NUM_OF_ELEMENTS_PER_VEC - 1)] + \
                               ((num_blocks_sent - 1)+ vex_path_a_args_val[0]);
    if (underrun_sample != expected_underrun_sample)
    {
        printf("ERROR: Last valid sample hasn't been streamed for path A\n");
        printf("Expected : %x, received : %x\n", expected_underrun_sample, underrun_sample);
        test_result = 1;
    }
    else
    {
        printf("HOST: Last valid sample has been streamed continuously for path A\n");
    }

    /* The expectation is PDPD_UNDERRUN_BIT(18), TX_UNDERRUN(12) and TX_NO_DATA_START(13) will be set
     * TX_NO_DATA_START(13) bit shoudn't be set ideally but it is a bug in N5 which will be resolved in 18A*/
    underrun_reg_value = read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_STATUS(apb_num), "V2D_INT_STATUS");

    if (underrun_reg_value & INTERRUPT_VALUE)
    {
        printf ("HOST: B buffer (PDPD main data)Underrun flag , Tx_underrun , Tx_no_data_start was set\n");
    }
    else
    {
        printf ("ERROR: expected bits were not set in the interrupt register, interrupt register value is %x\n", underrun_reg_value);
        test_result = 1;
    }

    if (0 == test_result)
    {
        printf("Host:---- SUCCESS ---- vex_num : %d, v2d_num : %d, apb_num: %d, pdpd_rate: %d\n", vex_num, v2d_num, apb_num, pdpd_rate);
    }
    else
    {
        printf("Host:---- FAIL ---- vex_num : %d, v2d_num : %d, apb_num: %d, pdpd_rate: %d\n", vex_num, v2d_num, apb_num, pdpd_rate);
        rv = 1;
    }
    return rv;
}   // main ends
