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
 * @file    underrun_B_extraterms.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D from path B and C
 *          and receving it back via path F.
 * @details 1. This TC validates the underflow in path B first and in path C later by
 *             sending 1 and 2  block of samples respectively
            2. Compares the received output with REF output for result evaluation.
            3. Check whether the underrun flag was set or not along with last valid sample.
   @TC Description:
        1. One block and 2 blocks of data (0.5usec worth) for given data rate will be streamed to V2D Tx from
           configured VEX cores for path B and path C respectively.
        2. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core.
        3. Once underrun interrupt asserted last sample will be continuously played which will be streamed
           to Rx VEX core where the data integrity check will be performed.
        4. Whether the last valid sample has been streamed continuously or not will be checked from HOST side.
        5. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
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

#include "v2d_flow4_tx_c.map.h"
#include "v2d_flow4_rx.map.h"
#include "v2d_flow4_tx_b.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define printf LOG_PRINT

#define PATH_PREFIX "test_vectors/"
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define NUMBER_OF_VECTORS_INPUT 128 // Corresponds to 1 block of data for 8GSPS corresponds to Max Rate
#define NUMBER_OF_VECTORS_OUTPUT 256 // Corresponds to 2 block of data for 8GSPS corresponds to Max Rate
#define NUM_OF_ELEMENTS_PER_VEC 32
#define VEC2FLIT(vec)   (vec * 2)
#define VEX_MAX_BUF_SIZE 256    // in vectors and it should be power of 2

#define APB_OFFSET_GEN(apb_num) (apb_num * 0x20000)

#define CIO2STRM_INT_EN_VALUE 0x3F
#define CIO2STRM_FIFO_STATUS_CTL_VALUE 0x00000001
#define CIO2STRM_WORD_CNT_CTL_VALUE 0x00000001
#define STRM2CIO_INT_ENABLE_VALUE 0xF
#define STRM2CIO_FIFO_STATUS_CTL_VALUE 0x00000001
#define STRM2CIO_WORD_CNT_CTL_VALUE 0x00000001
#define NSIP_HBI_INT_CSR_INT_VALUE 0xFFF
#define FIFO_CONTROL_VALUE 0x00000184
#define CREDIT_CS_VALUE 0x3
#define MISC_CTRL_VALUE 0x0
#define CSR_INT_VALUE 0xFFFFFFFF

#define PD_MAIN_UNDERRUN_BIT    18
#define PD_EXTRA_UNDERRUN_BIT   19
#define RX_1_NO_CFG_DROP_BIT    11
#define INTERRUPT_STATUS    ((1 << PD_EXTRA_UNDERRUN_BIT)| (1 << PD_MAIN_UNDERRUN_BIT) | (1 << RX_1_NO_CFG_DROP_BIT))

#define PASSTHRU_DELAY  0xA
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct v2d_flow2_config_tbl_s {
    uint32_t offset;
    uint32_t value;
    uint32_t mask;
    char *name;
} v2d_flow_tbl_t;

// PDPD interface sample rate
typedef enum {
  PDPD_RATE_IQ_P5 = 0, //   1 "I+Q" every 2 clocks ( 0.5 samples per clock)
  PDPD_RATE_IQ_1  = 1, //   1 "I+Q" every 1 clocks ( 1 sample per clock)
  PDPD_RATE_IQ_2  = 2, //   2 "I+Q" every 1 clocks ( 2 samples per clock)
  PDPD_RATE_IQ_4  = 3, //   4 "I+Q" every 1 clocks ( 4 samples per clock)
  PDPD_RATE_IQ_8  = 4  //   8 "I+Q" every 1 clock  ( 8 samples per clock)
} pdpd_rate_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const uint32_t g_v2d_host_id[][2][2] = {
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
static v2d_flow_tbl_t g_cio2strm_config_tbl[] = {
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

static v2d_flow_tbl_t g_strm2cio_config_tbl[] = {
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
  The Last 4 entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN(0), NSIP_HBI_INT_CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL(0)), 0x00000184, \
        V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_CREDIT_CS(0)), 0x3, V2D_AV2D_APB_NSIP_HBI_0_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_MISC_CTRL(0)), 0x0, V2D_AV2D_APB_NSIP_HBI_0_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MAP_TBL(0,0)), 0x80000000, V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MASK_TBL(0,0)), 0x7FFF, V2D_AV2D_APB_NSIP_HBI_0_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_FIFO_CSR_H2B_FIFO_CONTROL(0), FIFO_CONTROL_VALUE, \
        V2D_AV2D_APB_NSIP_HBI_0_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_CREDIT_READY_CS(0), CREDIT_CS_VALUE, V2D_AV2D_APB_NSIP_HBI_0_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_FC_EN(0), MISC_CTRL_VALUE, V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_SZ_HW_TBL(0,0), 0x9, V2D_AV2D_APB_NSIP_HBI_0_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ADDR_LKUP_TBL(0,0), 0x4020, V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ADDR_LKUP_TBL(0,0), 0x4000, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x2000 * 4 = 0x8000 , i.e VEX VMEM location 0x4000*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_ADDR_LKUP_TBL(0,0), 0x80002000, V2D_AV2D_APB_NSIP_HBI_0_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_CONTROL_TBL(0,0), 0x300, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ROUTE_LKUP_TBL(0,0), 0x0, V2D_AV2D_APB_NSIP_HBI_0_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"}
    /***********************************************************************************************************************************/
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
static v2d_flow_tbl_t g_cm_1_config_tbl[] = {
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
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last 4 entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow2_config_tbl[] = {
// Interrupt Enable
    {V2D_AV2D_APB_CSR_INT_HIGH_EN(0), CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_AV2D_APB_CSR_INT_LOW_EN(0), CSR_INT_VALUE, V2D_AV2D_APB_NSIP_HBI_0_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    {V2D_AV2D_APB_CSR_TX_SIF_CTRL(0), 0x300, V2D_AV2D_APB_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"}, //TX from PDPD, TX_RX_LOOPBACK set
    /*B buffer settings.*/
    {V2D_AV2D_APB_CSR_TX_PD_PTR_BOUND(0,0), 0x3FF0000, V2D_AV2D_APB_CSR_TX_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    {V2D_AV2D_APB_CSR_TX_PTR_BOUND(0,0), 0x7FF0400, V2D_AV2D_APB_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    // Rx Path Settings , F path
    {V2D_AV2D_APB_CSR_RX_PACKET_SZ(0), 0x0, V2D_AV2D_APB_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last four entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_AV2D_APB_CSR_PIF_CTRL(0) ,0x0, V2D_AV2D_APB_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_AV2D_APB_CSR_TX_PD_STREAM_CNT(0,0), 0x800000FF, V2D_AV2D_APB_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_AV2D_APB_CSR_TX_STREAM_CNT(0,0), 0x800000FF, V2D_AV2D_APB_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_AV2D_APB_CSR_RX_STREAM_CNT(0,0), 0x800000FF, V2D_AV2D_APB_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/

};

static v2d_flow_tbl_t g_v2d_pdpd_passthru_config_tbl[] = {
    //I[31:16]Q[15:0]. I= 2^13, Q=0
    {V2D_PDPD_PASSTHRU_C_SHDW(0), ((0x2<<13)<<16), V2D_PDPD_PASSTHRU_C_SHDW_WR_MASK , "PDPD_PASSTHRU_C_SHDW"},
    {V2D_PDPD_PASSTHRU_C_LIVE(0), ((0x2<<13)<<16), V2D_PDPD_PASSTHRU_C_LIVE_WR_MASK, "PDPD_PASSTHRU_C_LIVE"}
};

static v2d_flow_tbl_t g_v2d_pdpd_config_config_tbl[] = {
    //passthru_dly =0, pdpd_rate-> run time param
    {V2D_PDPD_CONFIG(0), 0x7, V2D_PDPD_CONFIG_WR_MASK, "PDPD_CONFIG"}
};

static v2d_flow_tbl_t g_v2d_pdpd_control_config_tbl[] = {
    {V2D_PDPD_CONTROL(0), 0x0, V2D_PDPD_CONTROL_WR_MASK, "PDPD_CONTROL"}
};

static v2d_flow_tbl_t g_v2d_pdpd_extra_static_config_tbl[] = {
    {V2D_PDPD_EXTRA_STATIC(0), 0x0, V2D_PDPD_EXTRA_STATIC_WR_MASK, "PDPD_EXTRA_STATIC"}
};

static v2d_flow_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

#if 0
#define V2D_PDPD_PASSTHRU_C_SHDW(0) ( 0x0000e2c0U )
#define V2D_PDPD_PASSTHRU_C_LIVE(0) ( 0x0000e2c4U )
#define PDPD_EXTRA_STATIC_OFFSET ( 0x0000e2c8U )
#define PDPD_SCRATCH_OFFSET      ( 0x0000e2ccU )
#define V2D_PDPD_CONFIG(0)       ( 0x0000e2d0U )
#define V2D_PDPD_CONTROL(0)      ( 0x0000e2d4U )
#define PDPD_CSR_CONFIG_OFFSET   ( 0x0000e2d8U )
#define PDPD_CSR_ERROR0_OFFSET   ( 0x0000e2dcU )
#define PDPD_CSR_ERROR1_OFFSET   ( 0x0000e2e0U )
#define PDPD_INT_STATUS_OFFSET   ( 0x0000e400U )
#define PDPD_INT_HIGH_EN_OFFSET  ( 0x0000e404U )
#define PDPD_INT_LOW_EN_OFFSET   ( 0x0000e408U )
#define PDPD_INT_CLEAR_OFFSET    ( 0x0000e40cU )
#define PDPD_INT_FORCE_OFFSET    ( 0x0000e410U )
#define PDPD_APB_STATUS_OFFSET ( 0x0000e414U )
#endif


/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int flow2_configure_pdpd(int, int, pdpd_rate_t);
int pdpd_config_reg_config(int, int, pdpd_rate_t);
int pdpd_control_reg_config(int, int);
int pdpd_passthru_c_reg_config(int, int);
int configure_v2d_host(int[], int, int, pdpd_rate_t);
int release_reset_abc_noc(void *);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num and sys_rate
 * @return          status value
 */
int configure_v2d_host(int vex_num_param[], int v2d_num, int apb_num, pdpd_rate_t pdpd_rate)
{
    int i, j = 0, rv = 0, vex_num = 0;

    for (j = 0; j < ARRAY_SIZE(vex_num_param); j++)
    {
        vex_num = vex_num_param[j];
        for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
        {
            if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num, g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                        g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
                return rv;
        }
        // Corresponds to cio2strm dest id
        if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num, g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][j], \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    printf("INFO: cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num_param[0] + 1, g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                    g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    printf("INFO: strm2cio configuration completed");

    // SDF init
    if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num_param[0] + 1, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM, \
                HIVE_ADDR_v2d_flow4_rx_consumer_sm_gate, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;
    printf("INFO: SDF configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_cm_0_config_tbl) - 4; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {

        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), g_md_control_tbl[pdpd_rate], \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  ARRAY_SIZE(g_cm_0_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), (vex_num_param[0] + 1), \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    for (i = 0; i < ARRAY_SIZE(g_cm_1_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                    g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf("INFO: CM configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 4; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_v2d_flow2_config_tbl[i].value, g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 3; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    (g_v2d_flow2_config_tbl[i].value | pdpd_rate), g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[pdpd_rate], g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }

    rv = flow2_configure_pdpd(v2d_num, apb_num, pdpd_rate);
    printf("INFO: V2D pdpd configuration completed");

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + V2D_AV2D_APB_CSR_TX_GNRL_CSR(0)), 0x810202, \
                V2D_AV2D_APB_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + V2D_AV2D_APB_CSR_RX_GNRL_CSR(0)), 0x1, \
                V2D_AV2D_APB_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf("INFO: V2D configuration completed");

    return rv;
}

/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id and pdpd_rate
 * @return          none
 */
int flow2_configure_pdpd(int v2d_num, int apb_num, pdpd_rate_t pdpd_rate)
{
    int rv = 0;

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_config_reg_config(v2d_num, apb_num, pdpd_rate))
    {
        printf ("PDPD reg config failed\n");
        return rv;
    }
    if (rv = pdpd_control_reg_config(v2d_num, apb_num))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_reg_config(v2d_num, apb_num))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_extra_static_reg_config(v2d_num, apb_num))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }

    printf("INFO: PDPD configuration Completed");
    return rv;
}

/**
 * @brief           Function configuring the pdpd config egsiter from host
 * @param [in]      V2d Id , APB Id and pdpd_rate
 * @return          status
 */
int pdpd_config_reg_config(int v2d_num, int apb_num, pdpd_rate_t pdpd_rate)
{
    int rv = 0;
    static v2d_pdpd_config_t pdpd_config_reg;

    printf("INFO: PDPD configuration Started");
    //config regsiter bit fileds
    unsigned int ext_ctrl_update_c_lut  = 0 ;/* 0: GMP/DDR Coefficient LUT live update is controlled by the CONTROL register
                                                1: GMP/DDR Coefficient LUT live update is controlled externally, e.g. via sample count */

    /*External Non-linear Magnitude Mapping LUT Update Enable
      0: Non-linear magnitude mapping LUT live update is controlled by the CONTROL register
      1: Non-linear magnitude mapping LUT live update is controlled externally, e.g. via sample count*/
    unsigned int ext_ctrl_update_nl_lut = 0 ;

    /*External Passthru Coefficient Update Enable
      0: Passthru coefficient live update is controlled by the CONTROL register
      1: Passthru coefficient live update is controlled externally, e.g. via sample coun
     */
    unsigned int ext_ctrl_update_passthru = 0;

    /*External Bypass Enable
      0: Bypass mode is controlled by the CONTROL register
      1: Bypass mode is controlled externally, e.g. via sample count
     */
    unsigned int ext_ctrl_bypass = 0;

    /*Non-linear Magnitude Enable
      0: Non-linear magnitude mapping is NOT enabled
      1: Non-linear magnitude mapping is enabled
    */
    unsigned int nlmag_enable = 0;

    /*Non-linear Magnitude Interpolation
      0: Non-linear magnitude mapping LUT interpolation is NOT enabled
      1: Non-linear magnitude mapping LUT interpolation is enabled
     */
    unsigned int nlmag_interp = 0;

    /*Coefficient LUT Segmnts
      0: All GMP/DDR Coefficient LUTs have 64 segments (all 65 entries are used).
      1: All GMP/DDR Coefficient LUTs have 32 segments (only entries 0..32 are used)
     */
    unsigned int clut_segments = 0;

    /*Coefficient LUT Interpolation
      0: GMP/DDR Coefficient LUT interpolation is NOT enabled
      1: GMP/DDR Coefficient LUT interpolation is enabled
     */
    unsigned int clut_interp = 0;

    /*Select Passthru Delay
      Passthru sample delay
      *NOTE: // this should be greater than the m & q delay, to be taken care in
    */
    unsigned int passthru_dly = PASSTHRU_DELAY;

    /*Output Shift
      0: Final output result is NOT shifted prior to the saturation/rounding stage.
      1: Final output result is shifted right by 1 prior to the saturation/rounding stag
    */
    unsigned int out_shift = 0;

    /*0: Ganged terms are NOT included in the final output.
      1: Ganged terms are included in the final output.
      In a ganged configuration this bit should be set to 1 for the primary (PDPD0) instance.
    */
    unsigned int gang_in_en = 0;

    /*0: Ganged terms are NOT output to the partner PDPD instance.
      1: Ganged terms are output to the partner PDPD instance.
      In a ganged configuration this bit should be set to 1 for the secondary (PDPD1) instance.
    */
    unsigned int gang_out_en = 0;

#if 0
    pdpd_config_reg.pdpd_rate = pdpd_rate; //3
    pdpd_config_reg.ext_ctrl_update_c_lut = ext_ctrl_update_c_lut; //1
    pdpd_config_reg.ext_ctrl_update_nl_lut = ext_ctrl_update_nl_lut; //1
    pdpd_config_reg.ext_ctrl_update_passthru = ext_ctrl_update_passthru; //1
    pdpd_config_reg.ext_ctrl_bypass = ext_ctrl_bypass; //1
    pdpd_config_reg.nlmag_enable = nlmag_enable; //1
    pdpd_config_reg.nlmag_interp = nlmag_interp; //1
    pdpd_config_reg.clut_segments = clut_segments; //1
    pdpd_config_reg.clut_interp = clut_interp; //1
    pdpd_config_reg.passthru_dly = passthru_dly; //7
    pdpd_config_reg.out_shift = out_shift; //1
    pdpd_config_reg.gang_in_en = gang_in_en; //1
    pdpd_config_reg.gang_out_en = gang_out_en; //1
    g_v2d_pdpd_config_config_tbl[0].value = pdpd_config_reg.d;
#else

    g_v2d_pdpd_config_config_tbl[0].value =  ((pdpd_rate & 0x7) |((ext_ctrl_update_c_lut & 0x1) << 0x3) | ((ext_ctrl_update_nl_lut & 0x1) << 4) | \
                                        ((ext_ctrl_update_passthru & 0x1) << 5) | ((ext_ctrl_bypass & 0x1)<< 6)| ((nlmag_enable & 0x1) << 7)| \
                                        ((nlmag_interp & 0x1 )<< 8) | ((clut_segments & 0x1) << 9) | ((clut_interp&0x1) << 10) | \
                                        ((passthru_dly & 0x3F) << 11) | ((out_shift & 0x1) << 18)| \
                                        ((gang_in_en & 0x1) << 19)| ((gang_out_en & 0x1) << 20) );

#endif

    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_pdpd_config_config_tbl[0].offset), \
            g_v2d_pdpd_config_config_tbl[0].value, g_v2d_pdpd_config_config_tbl[0].mask, g_v2d_pdpd_config_config_tbl[0].name))
        return rv;

    return rv;
}

/**
 * @brief           Function configuring the pdpd config egsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_control_reg_config(int v2d_num, int apb_num)
{
    static v2d_pdpd_control_t pdpd_control_reg;
    int rv = 0;

    uint32_t update_c_lut = 0; // : 1;
    ///< Writing a 1 to this bit causes all of the GMP/DDR shadow coefficient
    ///< registers to be copied to their live counterparts. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="0" ResetValue="0x0"

    uint32_t update_nl_lut = 0; // : 1;
    ///< Writing a 1 to this bit causes all of the NL_MAG LUT shadow coefficient
    ///< registers to be copied to their live counterparts. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="1" ResetValue="0x0"

    uint32_t update_passthru  = 0 ;//: 1;
    ///< Writing a 1 to this bit causes the PASSTHRU shadow coefficient register
    ///< to be copied to its live counterpart. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="2" ResetValue="0x0"

    uint32_t bypass  = 0; //: 1;
    ///< 0: All statically enabled terms are included in the final output.
    ///< 1: Only the passthru term is included in the final output.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"
    //uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
#if 0
    pdpd_control_reg.update_c_lut = update_c_lut;
    pdpd_control_reg.update_nl_lut = update_nl_lut;
    pdpd_control_reg.update_passthru = update_passthru;
    pdpd_control_reg.bypass = bypass;
    g_v2d_pdpd_control_config_tbl[0].value = pdpd_control_reg.d;
#else
    g_v2d_pdpd_control_config_tbl[0].value = (((update_c_lut & 0x1)) | ((update_nl_lut & 0x1) << 1) | \
                                            ((update_passthru & 0x1) <<2 ) | ((bypass & 0x1) << 3));
#endif

    if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_pdpd_control_config_tbl[0].offset), \
                g_v2d_pdpd_control_config_tbl[0].value, g_v2d_pdpd_control_config_tbl[0].mask, g_v2d_pdpd_control_config_tbl[0].name))
        return rv;
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient regsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_passthru_c_reg_config(int v2d_num, int apb_num)
{
    int i, rv = 0;
    v2d_pdpd_passthru_c_shdw_t pdpd_passthru_c_shdw_reg;
    /* rom MATLAB
     *  passthru_coeff_i = 2^13;  % real part
        passthru_coeff_q = 0;  % imaginary part
     * */

    uint32_t Q  = 0; //: 15;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="15" ResetValue="None"

    uint32_t I  = 1 << 13 ; //: 15;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="31" ResetValue="None"

    pdpd_passthru_c_shdw_reg.q = Q;
    pdpd_passthru_c_shdw_reg.i = I;

#if 0
    g_v2d_pdpd_passthru_config_tbl[0].value = pdpd_passthru_c_shdw_reg.d; // shadow register
    g_v2d_pdpd_passthru_config_tbl[1].value = pdpd_passthru_c_shdw_reg.d; // live register
#else
    g_v2d_pdpd_passthru_config_tbl[0].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
    g_v2d_pdpd_passthru_config_tbl[1].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
    printf ("%x\n", g_v2d_pdpd_passthru_config_tbl[0].value);
#endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_passthru_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_pdpd_passthru_config_tbl[i].offset), \
                g_v2d_pdpd_passthru_config_tbl[i].value, g_v2d_pdpd_passthru_config_tbl[i].mask, g_v2d_pdpd_passthru_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient regsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_extra_static_reg_config (int v2d_num, int apb_num)
{
    int i, rv = 0;
    v2d_pdpd_extra_static_t pdpd_extra_static_reg;

    uint32_t en = 1;
    /* Extra Terms Enable
    0: The extra terms are not enabled
    1: The extra terms are enabled */
    uint32_t sel = PASSTHRU_DELAY;
    /* Select Delay
    Extra terms delay */

    pdpd_extra_static_reg.en = en;
    pdpd_extra_static_reg.sel = sel;

    g_v2d_pdpd_extra_static_config_tbl[0].value = pdpd_extra_static_reg.d;

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_extra_static_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, (APB_OFFSET_GEN(apb_num) + g_v2d_pdpd_extra_static_config_tbl[i].offset), \
                g_v2d_pdpd_extra_static_config_tbl[i].value, g_v2d_pdpd_extra_static_config_tbl[i].mask, g_v2d_pdpd_extra_static_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function for noc reset
 * @param [in]      srp
 * @return          status value
 */
int release_reset_abc_noc (void *srp)
{
    int i, rv = 0, flags = 0;
    for (i = 0; i < ARRAY_SIZE(g_vex_noc_config); i++)
    {
        rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CFG_CTRL,
                        0,
                        g_vex_noc_config[i].offset,
                        &g_vex_noc_config[i].value,
                        1,
                        flags);

    }
    return rv;
}

/**
 * @brief           Function for triggering bfn
 * @param [in]      v2d_num and apb_num
 * @return          status value
 */
int trigger_bfn_pdpd_ingress(int v2d_num, int apb_num)
{
    int rv = 0;
    if (0 == apb_num)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_CONFIG(2), 0x1, \
                    V2D_BFN_CSR_BFNE_CONFIG_WR_MASK, "BFNE_CONFIG2"))
            return rv;
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_START(2), 0xFFFFFFFF, \
                    V2D_BFN_CSR_BFNE_START_WR_MASK, "BFNE_START2"))
            return rv;
    }
    else if (1 == apb_num)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_CONFIG(3), 0x1, \
                    V2D_BFN_CSR_BFNE_CONFIG_WR_MASK, "BFNE_CONFIG3"))
            return rv;
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, V2D_BFN_CSR_BFNE_START(3), 0xFFFFFFFF, \
                V2D_BFN_CSR_BFNE_START_WR_MASK, "BFNE_START3"))
            return rv;
    }
    return rv;

}

int main(int argc, const char *argv[])
{

    int rv = 0, test_status = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num_param[2] = {0}, v2d_num, apb_num, underrun_reg_value = 0, host_indicator = 0, vex_cnt = 0,
        host_vec_processed = 0, host_result = 0, host_blocks_processed = 0;
    pdpd_rate_t pdpd_rate;

    int dmem_offset = 0x4000, underrun_sample = 0, loop_wait_count = 0;
    int v2d_flow4_tx_c_offset_val[] = {HIVE_ADDR_v2d_flow4_tx_c_g_scalar_val, HIVE_ADDR_v2d_flow4_tx_c_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow4_tx_c_g_dest_buffer_base, HIVE_ADDR_v2d_flow4_tx_c_g_initial_block_size,
                         HIVE_ADDR_v2d_flow4_tx_c_g_host_indicator};
    unsigned int v2d_flow4_tx_c_args_val[] = {0x00120014, NUMBER_OF_VECTORS_INPUT, 0, 2, 0};    // Initial block size is 2 for C path

    int v2d_flow4_tx_b_offset_val[] = {HIVE_ADDR_v2d_flow4_tx_b_g_scalar_val, HIVE_ADDR_v2d_flow4_tx_b_g_num_vecs_in ,
                         HIVE_ADDR_v2d_flow4_tx_b_g_dest_buffer_base, HIVE_ADDR_v2d_flow4_tx_b_g_initial_block_size,
                         HIVE_ADDR_v2d_flow4_tx_b_g_host_indicator};
    unsigned int v2d_flow4_tx_b_args_val[] = {0x00120014, NUMBER_OF_VECTORS_INPUT, 0, 1, 0};    // Initial block size is 1 for B path

    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow4_rx_g_scalar_val, HIVE_ADDR_v2d_flow4_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow4_rx_g_num_blocks, HIVE_ADDR_v2d_flow4_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow4_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00120014, NUMBER_OF_VECTORS_INPUT, 2, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_out[NUMBER_OF_VECTORS_OUTPUT][NUM_OF_ELEMENTS_PER_VEC] =  {0};
    unsigned int host_exp_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
    char tref_file[30] = {'\0'};
    FILE *fp_ref_output = NULL;

    init(); // Initializing the srp

#if (1 == REGRESSION)
    subsys_reset_cycle();
    v2d_reset_cycle();
    crux_reset_cycle();
    vex_reset_cycle();
#endif

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);
    printf ("INFO: argv[0] : %d\n", (int)argv[0]);
    printf ("INFO: argv[1] : %d\n", (int)argv[1]);
    printf ("INFO: argv[2] : %d\n", (int)argv[2]);
    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    pdpd_rate = (int) argv[4];
    printf ("INFO: vex id0: %d, vex_id1: %d, v2d_num : %d , apb_num: %d, pdpd_rate: %d\n", vex_num_param[0], vex_num_param[1], v2d_num, apb_num, pdpd_rate);

    v2d_flow4_tx_c_args_val[1] = g_vectors_per_block[pdpd_rate];
    v2d_flow4_tx_b_args_val[1] = g_vectors_per_block[pdpd_rate];
    vex_rx_val_kargs[1] = g_vectors_per_block[pdpd_rate];
    vex_rx_val_kargs[3] = VEX_MAX_BUF_SIZE / g_vectors_per_block[pdpd_rate];

    switch(pdpd_rate)
    {
        case 0:
            sprintf(tref_file,"%sref_output_p5gsps.txt",PATH_PREFIX);
            break;
        case 1:
            sprintf(tref_file,"%sref_output_1gsps.txt",PATH_PREFIX);
            break;
        case 2:
            sprintf(tref_file,"%sref_output_2gsps.txt",PATH_PREFIX);
            break;
        case 3:
            sprintf(tref_file,"%sref_output_4gsps.txt",PATH_PREFIX);
            break;
        case 4:
            sprintf(tref_file,"%sref_output_8gsps.txt",PATH_PREFIX);
            break;
    }

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, pdpd_rate))
    {
        printf("Host Configuration failed\n");
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

    /*Clearing the VEX VMEM and DMEM for all used vex cores*/
    if (rv = vex_mem_clear(vex_num_param[0], srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[0]);
        return rv;
    }
    if (rv = vex_mem_clear((vex_num_param[0] + 1), srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[0] + 1);
        return rv;
    }
    if (rv = vex_mem_clear((vex_num_param[1]), srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[1]);
        return rv;
    }

    printf("Host: start vex program load\n");
    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow4_tx_c.fw")))
        return rv;

    if ((rv = srp_vex_loader(vex_hdl, (vex_num_param[1]), "vex_fw/sim_m64/v2d_flow4_tx_b.fw")))
        return rv;

    if ((rv = srp_vex_loader(vex_hdl, (vex_num_param[0] + 1), "vex_fw/sim_m64/v2d_flow4_rx.fw")))
        return rv;

    printf("Host: vex program load - done\n");

    /* Loading parameters for path_c_tx*/
    for (lc = 0; lc < ARRAY_SIZE(v2d_flow4_tx_c_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                SRP_BLOCK_VEX_CORE,
                vex_num_param[0],
                dmem_offset + v2d_flow4_tx_c_offset_val[lc],
                &v2d_flow4_tx_c_args_val[lc],
                1,
                flags)))
            return rv;
    }

    /* Loading parameters for path_b_tx*/
    for (lc = 0; lc < ARRAY_SIZE(v2d_flow4_tx_b_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                SRP_BLOCK_VEX_CORE,
                vex_num_param[1],
                dmem_offset + v2d_flow4_tx_b_offset_val[lc],
                &v2d_flow4_tx_b_args_val[lc],
                1,
                flags)))
            return rv;
    }

    /* Loading the host parameters to VEX  Rx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[0] + 1,
                        dmem_offset + vex_rx_offset_val[lc],
                        &vex_rx_val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Input Vector Generation and loading to VEX memory*/
    for (i = 0; i < g_vectors_per_block[pdpd_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2* NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j *2)))  ;
        }
    }

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow4_tx_c_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow4_tx_b_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Reading the REF output and loading it to Rx VEX memory*/
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file\n");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_exp_data,
                (2 * g_vectors_per_block[pdpd_rate]* NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY) < \
            ((2 * g_vectors_per_block[pdpd_rate]* NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY))
    {
        printf("ERROR: Insufficient Output REF data\n");
        return -1;
    }
    fclose(fp_ref_output);


   if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0] + 1,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow4_rx_vbuffer,/*local_addr*/
                        host_exp_data,
                        2 * (g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Check the Interrupt reg value before start of test*/
    underrun_reg_value = read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_STATUS(apb_num), "V2D_INT_STATUS");

    if (0 == underrun_reg_value)
    {
        printf ("HOST: B buffer (PDPD main data )Underrun flag was not set\n");
    }
    else
    {
        printf ("ERROR: underrun flag was set before the start of test, value is %x\n", underrun_reg_value);
        test_status = 1;
        rv = 1;
        return rv;
    }

    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, vex_num_param[0], 0);    // Start path B Tx VEX
    srp_vex_start(vex_hdl, vex_num_param[0] + 1, 0);    // start Rx VEX
    srp_vex_start(vex_hdl, vex_num_param[1], 0);    // start path C Tx VEX
    printf("Host: vex program start - done\n");

    while ((b2h_flit_count += read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_NSIP_HBI_1_B2H_FLIT_COUNT(apb_num), \
                    "HBI_1_B2H_FLIT_COUNT")) < VEC2FLIT(g_vectors_per_block[pdpd_rate])) // 1 blocks of data
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf("b2h_flit_count: %d\n", b2h_flit_count);

    /*trigger BFN for PDPD ingress*/
    if (rv = trigger_bfn_pdpd_ingress(v2d_num, apb_num))
    {
        printf("ERROR: pdpd ingress bfn trigger failed\n");
        return rv;
    }

    loop_wait_count = 0;

    while ((h2b_flit_count += read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_NSIP_HBI_0_H2B_FLIT_COUNT(apb_num), \
                    "HBI_0_H2B_FLIT_COUNT")) < VEC2FLIT(g_vectors_per_block[pdpd_rate])) // wait for single block of sample in the H2B
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf("h2b_flit_count: %d\n", h2b_flit_count);

    usleep(10000);

    /* Check whetehr required interrupts were set in the status register*/
    underrun_reg_value = read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_CSR_INT_STATUS(apb_num), "V2D_INT_STATUS");

    if ((underrun_reg_value == INTERRUPT_STATUS))
    {
        printf(" PDPD main underrun, PDPD extra underrun and Rx_1_no_Cfg drop bits were set\n");
    }
    else
    {
        printf("ERROR: Underrun flag was not set, value %x\n", underrun_reg_value);
        test_status = 1;
    }

    /* Check the Data integrity on the Rx vex*/
    int vex_num = vex_num_param[0];
    loop_wait_count = 0;

    while (host_vec_processed < (g_vectors_per_block[pdpd_rate]))
    {
        if ((rv = srp_core_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num + 1,
                        dmem_offset + HIVE_ADDR_v2d_flow4_rx_g_count1,
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
                    vex_num + 1,
                    dmem_offset + HIVE_ADDR_v2d_flow4_rx_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_core_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num + 1,
                    dmem_offset + HIVE_ADDR_v2d_flow4_rx_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x\n", host_blocks_processed / vex_rx_val_kargs[0]);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV\n");
        test_status = 1;
    }
    else
    {
        printf("Received output matches with reference output\n");
    }

    /* Check the last valid sample that was streamed by V2D*/
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num + 1,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow4_rx_vbuffer_out,/*local_addr*/
                        &underrun_sample,
                        sizeof(int)))
        return rv;

    if (underrun_sample == host_exp_data[(2 * g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY - 1])
    {
        printf("Last valid sample has been streamed continuously\n");
    }
    else
    {
        printf("ERROR: Last valid sample hasn't been streamed\n");
        printf("Expected %x, streamed %x\n",
                host_exp_data[(2 * g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY - 1], underrun_sample);
        test_status = 1;
    }

    /* Indicate both the Tx VEX cores to send one more block of data*/
    host_indicator = 1;

    if ((rv = srp_core_block_write32(srp,
            SRP_BLOCK_VEX_CORE,
            vex_num_param[0],
            dmem_offset + HIVE_ADDR_v2d_flow4_tx_c_g_host_indicator,
            &host_indicator,
            1,
            flags)))
        return rv;

    if ((rv = srp_core_block_write32(srp,
            SRP_BLOCK_VEX_CORE,
            vex_num_param[1],
            dmem_offset + HIVE_ADDR_v2d_flow4_tx_b_g_host_indicator,
            &host_indicator,
            1,
            flags)))
        return rv;

    b2h_flit_count = 0;
    loop_wait_count = 0;

    while ((b2h_flit_count += read_reg(SRP_BLOCK_V2D, v2d_num, V2D_AV2D_APB_NSIP_HBI_1_B2H_FLIT_COUNT(apb_num), \
                    "HBI_1_B2H_FLIT_COUNT")) < VEC2FLIT(g_vectors_per_block[pdpd_rate])) // 1 blocks of data
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    usleep(10000);
    /* Check the last valid sample that was streamed by V2D after sending additional data*/
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num + 1,
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow4_rx_vbuffer_out,/*local_addr*/
                        &underrun_sample,
                        sizeof(int)))
        return rv;

    if (underrun_sample == host_exp_data[(2 * g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY - 1])
    {
        printf("Last valid sample has been streamed continuously after sending additional data\n");
    }
    else
    {
        printf("ERROR: Last valid sample hasn't been streamed\n");
        printf("Expected %x, streamed %x\n",
                host_exp_data[(2 * g_vectors_per_block[pdpd_rate] * NUM_OF_ELEMENTS_PER_VEC) + PASSTHRU_DELAY - 1], underrun_sample);
        test_status = 1;
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- Tx_vex1 : %d, Tx_vex2 : %d, v2d_num : %d, apb_num: %d, sys_rate: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, pdpd_rate);
    }
    else
    {
        printf("Host:---- FAIL ---- Tx_vex1 : %d, Tx_vex2 : %d, v2d_num : %d, apb_num: %d, sys_rate: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, pdpd_rate);
        rv = 1;
    }

    return rv;
}
