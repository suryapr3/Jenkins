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
 * @file    post_processing_2streams.c
 * @details 1. This TC validates the Post Processing path.
            2. The expected result was to check data integrity on both D and F paths.
 * @TC Description:
        1. pre-defined number of blocks (1000) will be streamed at a required rate to V2D CM1 (B Path) from
           configured VEX core.
        2. PDPD loop back is enabled so data will be looped back along with path D from CM1 on two streams which are
           equally divided and the data will be transmitted to path A in two streams via CM0 from another VEX core without any
           modification.
        3. Rx loop back is enabled so data will be looped back along with path F to another VEX core.
        4. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the Rx VEX core.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison was done HOST will read the result.
        6. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        7. Rx VEX core which receivs the D path data will exclude the first block.
        8. Same data block will be sent continuously by Tx VEX core on B path so that comparison
           can be run for good number of blocks.
        9. The Tx VEX core will be continuously streaming the data until host indicates them to stop the transmission.
        10. The above can be used to verify whether V2D is getting underrun before the Tx VEX stop transmitting
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow6_common_utils.h"
#include "common_utils.h"

#include "v2d_path_b_tx.map.h"
#include "v2d_path_d_rx.map.h"
#include "v2d_path_f_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define NUM_VEX_CORES   4
/* Same VEX core will receive the data from D path and send it to A path*/
#define NUM_TX_VEX_CORES    3   /*Tx VEX feeds PDPD MAIN and another Two VEX cores feed A path*/
#define NUM_RX_VEX_CORES    3   /*Two Rx VEX receives data from D path and other VEX core receives data from F path*/

#define RX_GNRL_CSR_VALUE_POST_PROCESSING   (AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_EN_BF_MSK | AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_CFG_COMPLETE_BF_MSK | AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_CFG_COMPLETE_BF_MSK)

#define POST_PROCESSING_INTERRUPT_VALUE V2D_INTERRUPT_VALUE | AV2D_CSR_INT_CSR_INT_STATUS_TX_UNDERRUN_BF_MSK
#define B2H_ADD_MAP_B2_OFFSET   0x10000
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
int g_initial_block_size = 1;

int g_num_blocks_v2d_buffer = 3;

/*config 11 to 16 will be equal to config 5 to 10 as there were no LUT's present*/
const char *ref_file[NUM_CONFIG_PDPD] = {
    "ref_output_p5gsps.txt", "ref_output_1gsps.txt", "ref_output_2gsps.txt", "ref_output_4gsps.txt", "ref_output_8gsps.txt",
    "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt",
    "ref_output_config9.txt", "ref_output_config10.txt"
};

char *g_vex_fw_binary[] = {"vex_fw/sim_m64/v2d_path_b_tx.fw", "vex_fw/sim_m64/v2d_path_d_rx.fw", "vex_fw/sim_m64/v2d_path_d_rx.fw",
    "vex_fw/sim_m64/v2d_path_f_rx.fw"};

/* The value corresponds to the number of blocks the TC should run defined as per order in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {1000, 1000, 1000, 1000, 1000},
    {1000, 1000, 1000, 1000, 1000},
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last five entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, \
        "B2H_CREDIT_CS"},
    // These are for Buffer A0
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), (B2H_ADD_MAP_B2_OFFSET - 1), NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},
    // These are for Buffer A1
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET), (0x80000000 | B2H_ADD_MAP_B2_OFFSET), NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL1"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET), (B2H_ADD_MAP_B2_OFFSET - 1), NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL1"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    /*For all data rates the VEX buffer is two times of the block size*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_path_f_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to provided VEX VMEM location(in Bytes) */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last ten entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_1_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "HBI_1_INT_HIGH_EN"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "HBI_1_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "HBI_1_B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, \
        "HBI_1_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "CM_1_H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "CM_1_H2B_CREDIT_CS"},
    /*For all data rates the VEX buffer is two times of the block size*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "HBI_1_H2B_BUF_SZ_HW_TBL"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_path_d_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "HBI_1_H2B_TK_ADDR_LKUP_TBL_0"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ADDR_LKUP_TBL_0"},
    /* DEST Buffer Size in VEX corresponds to 2 blocks of data*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "HBI_1_H2B_BUF_SZ_HW_TBL1"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_path_d_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "HBI_1_H2B_TK_ADDR_LKUP_TBL1"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ADDR_LKUP_TBL1"},

    /***********************************************************************************************************************************/
    /*These last 10 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to provided VEX VMEM location(in Bytes) */
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_ADDR_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_ADDR_LKUP_TBL1"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, \
        "HBI_1_H2B_MD_CONTROL_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL1_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, \
        "HBI_1_H2B_MD_CONTROL_TBL1"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "HBI_1_H2B_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "HBI_1_H2B_ROUTE_LKUP_TBL1"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ROUTE_LKUP_TBL1"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ROUTE_LKUP_TBL1"}

    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last eleven entry order shouldn't be modified*/
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, POST_PROCESSING_2STREAM_RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, \
        "RX_PACKET_SZ"},

// Tx Path Settings
    /************************************************************************************************************/
    /* The last eleven entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    /*Rx loop back was set*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x3FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND1_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND1"},
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT_WR_MASK, "RX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT1_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT_WR_MASK, "RX_PD_STREAM_CNT1"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT1_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT1"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int flow6_configure_pdpd(int, int, int, int);
int configure_v2d_host(int *, int, int, int, int, sys_rate_t);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock, test_config and sys_rate
 * @return          status
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config, sys_rate_t sys_rate)
{
    int i = 0, j = 0, rv = 0, v2d_buffer_b = 0, v2d_buffer_a0 = 0, v2d_buffer_a1 = 0, v2d_tx_stream_cnt0 = 0, v2d_tx_stream_cnt1 = 0,
        rx_pd_stream_cnt = 0, md_control_d0 = 0, md_control_d1 = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    v2d_tx_stream_cnt0 = g_flow1_vectors_per_block[sys_rate] - 1;
    v2d_tx_stream_cnt1 = g_flow1_vectors_per_block[sys_rate] - 1;

    rx_pd_stream_cnt = g_flow1_vectors_per_block[sys_rate] - 1;
    md_control_d0 = (g_vectors_per_block[drf_clock][pdpd_out_rate]) - 1;
    md_control_d1 = (g_vectors_per_block[drf_clock][pdpd_out_rate]) - 1;

    /* Buffer A should be always allocated at lower half of V2D buffer with 3 times of the block size and
     * Buffer B should be always allocated at higher half of V2D buffer with 2 times of the block size*/
    v2d_buffer_a0 = ((((g_num_blocks_v2d_buffer) * (g_flow1_vectors_per_block[sys_rate])) - 1) << 16);
    v2d_buffer_a1 = ((((g_num_blocks_v2d_buffer) * g_flow1_vectors_per_block[sys_rate] * 2) - 1) << 16) |
                            ((g_num_blocks_v2d_buffer) * (v2d_tx_stream_cnt0 + 1));


    v2d_buffer_b = V2D_BUFFER1_OFFSET | ((V2D_BUFFER1_OFFSET + ((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2) - 1) << 16));
    printf ("Buffer b: 0x%x, Buffer A0: 0x%x, Buffer A1: 0x%x", v2d_buffer_b, v2d_buffer_a0, v2d_buffer_a1);

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_pdpd_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    int fill_level_a_path_value = (v2d_tx_stream_cnt0 + 1) + ((v2d_tx_stream_cnt0 + 1) / 2);
    printf("fill_level_pdpd_value : 0x%x, fill_level_a_path_value : 0x%x", fill_level_pdpd_value, fill_level_a_path_value);
    int water_mark_value = (AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | \
                           (fill_level_pdpd_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF)) | \
                           (AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WM_EN_BF_MSK | fill_level_a_path_value);
#endif

    /* Configure cio2strm for vex_param[0] and vex_param[1]*/
    for (j = 0; j < NUM_TX_VEX_CORES; j++)
    {
        for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
        {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j]) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
                return rv;
        }
    }

    for (j = 0; j < 1; j++)
    {
        // Corresponds to cio2strm dest id for PDPD Main data VEX core
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }

    for (; j < NUM_TX_VEX_CORES; j++)
    {
        // Corresponds to cio2strm dest id for post processing VEX cores
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][0], \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    printf("INFO: cio2strm configuration completed");

    /* Configure strm2cio for vex_param[1] ,vex_param[2] and vex_param[3]*/
    for (j = 0; j < NUM_RX_VEX_CORES; j++)
    {
        for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
        {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j + 1]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                    g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
                return rv;
        }

        // SDF init
        // For all the RX VEX Cores the SDF address was constant which is 0x80
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j + 1]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                    HIVE_ADDR_v2d_path_d_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
            return rv;

        printf("INFO: strm2cio configuration completed");
    }

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    (g_cm_0_config_tbl[i].value | HIVE_ADDR_v2d_path_f_rx_vbuffer_out), g_cm_0_config_tbl[i].mask, \
                    g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_flow1_md_control_tbl[sys_rate], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {
        /* Corresponds to F path*/
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), (vex_num[3]), \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    //CM1 configuration
    for (i = 0; i < ARRAY_SIZE(g_cm_1_config_tbl) - 10; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 8; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), \
                    (g_cm_1_config_tbl[i].value | HIVE_ADDR_v2d_path_d_rx_vbuffer_out), g_cm_1_config_tbl[i].mask, \
                    g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 7; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), md_control_d0, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 6; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), md_control_d1, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), vex_num[1], \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), vex_num[2], \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf ("INFO: CM configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 11); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_v2d_config_tbl) - 10); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    (g_v2d_config_tbl[i].value | (drf_clock << 7) | (sys_rate)), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_v2d_config_tbl) - 9); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_v2d_config_tbl) - 8); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    v2d_buffer_a0, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_v2d_config_tbl) - 7); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    v2d_buffer_a1, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 6); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (g_v2d_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                   g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 5); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate]), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 3); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (0x80000000 | rx_pd_stream_cnt), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 2); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (0x80000000 | v2d_tx_stream_cnt0), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl) - 1); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (0x80000000 | v2d_tx_stream_cnt0), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < (ARRAY_SIZE(g_v2d_config_tbl)); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                   (g_flow1_tx_strm_cnt0_offset[sys_rate]), g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }

    rv = flow6_configure_pdpd(v2d_num, apb_num, test_config, POST_C_CENTER_VALUE_UNITY_GAIN);
    printf("INFO: V2D pdpd configuration completed");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, water_mark_value, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), \
                POST_PROCESSING_TX_GNRL_CSR_VALUE, AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), \
                RX_GNRL_CSR_VALUE_POST_PROCESSING, AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D configuration completed");

    return rv;
}


/**
 * @brief           Function populating the parameters to be provided to
 *                  VEX cores based on the split method
 * @param [in]      vex0_tx_args, vex1_tx_args, vex0_rx_args, and split_method, pdpd_rate
 * @return          none
 */
void vex_param_gen(unsigned int *vex_path_b_tx_args_val, unsigned int *vex_path_d_rx0_args_val, unsigned int *vex_path_d_rx1_args_val,
        unsigned int *vex_path_f_rx_args_val, int drf_clock, int test_config, sys_rate_t sys_rate)
{
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    vex_path_d_rx0_args_val[1] = g_vectors_per_block[drf_clock][pdpd_out_rate] / 2;
    vex_path_d_rx0_args_val[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    vex_path_d_rx0_args_val[3] = NUM_DATA_BLOCKS;

    vex_path_d_rx1_args_val[1] = g_vectors_per_block[drf_clock][pdpd_out_rate] / 2;
    vex_path_d_rx1_args_val[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    vex_path_d_rx1_args_val[3] = NUM_DATA_BLOCKS;

    vex_path_b_tx_args_val[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    // one block extra needs to be send to avoid the underrun
    vex_path_b_tx_args_val[3] = vex_path_d_rx0_args_val[2] + 1;
    vex_path_b_tx_args_val[4] = g_initial_block_size;

    vex_path_f_rx_args_val[1] = g_flow1_vectors_per_block[sys_rate];
    vex_path_f_rx_args_val[2] = vex_path_d_rx0_args_val[2] - 1;
    vex_path_f_rx_args_val[3] = NUM_DATA_BLOCKS;
}

/**
 * @brief           Function to read the ref vectors to be provided to
 *                  VEX Rx cores.
 * @param [in]      pointers to rx buffer, num_vectors and test_config
 * @return          status value
 */
int ref_output_read(unsigned int *host_ref_data, unsigned int *host_ref_d0_data, unsigned int *host_ref_d1_data, int num_vectors,
        int test_config)
{
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;
    pdpd_rate_t pdpd_out_rate;

    pdpd_out_rate = g_test_config_tbl[test_config][1];

    sprintf(tref_file, "%s%s", PATH_PREFIX,ref_file[test_config]);

    printf ("HOST: output file : %s\n", tref_file);
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_data,
                num_vectors * NUM_OF_ELEMENTS_PER_VEC) < \
                (num_vectors * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient Output REF data");
        return -1;
    }

    //rewinding the file pointer to starting of FILE
    rewind(fp_ref_output);

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_d0_data,
                (num_vectors / 2) * NUM_OF_ELEMENTS_PER_VEC) < \
                (num_vectors / 2) * NUM_OF_ELEMENTS_PER_VEC)
    {
        printf("ERROR: Insufficient Output REF data");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_d1_data,
                (num_vectors / 2) * NUM_OF_ELEMENTS_PER_VEC) < \
                (num_vectors / 2) * NUM_OF_ELEMENTS_PER_VEC)
    {
        printf("ERROR: Insufficient Output REF data");
        return -1;
    }

    fclose(fp_ref_output);
    return 0;
}

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    sys_rate_t sys_rate;

    int dmem_offset = DMEM_OFFSET;
    int vex_path_b_tx_offset_val[] = {HIVE_ADDR_v2d_path_b_tx_g_scalar_val, HIVE_ADDR_v2d_path_b_tx_g_num_vecs_in,
                                        HIVE_ADDR_v2d_path_b_tx_g_dest_buffer_base, HIVE_ADDR_v2d_path_b_tx_g_num_blocks,
                                        HIVE_ADDR_v2d_path_b_tx_g_initial_block_size, HIVE_ADDR_v2d_path_b_tx_g_host_cycle_count};
    unsigned int vex_path_b_tx_args_val[] = {0x0, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};

    int vex_path_f_rx_offset_val[] = {HIVE_ADDR_v2d_path_f_rx_g_scalar_val, HIVE_ADDR_v2d_path_f_rx_g_num_vecs_in,
                                        HIVE_ADDR_v2d_path_f_rx_g_num_blocks, HIVE_ADDR_v2d_path_f_rx_g_tbs_in_blk,
                                        HIVE_ADDR_v2d_path_f_rx_g_count1};
    unsigned int vex_path_f_rx_args_val[] = {0x0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    int vex_path_d_rx_offset_val[] = {HIVE_ADDR_v2d_path_d_rx_g_scalar_val, HIVE_ADDR_v2d_path_d_rx_g_num_vecs_in,
                                        HIVE_ADDR_v2d_path_d_rx_g_num_blocks, HIVE_ADDR_v2d_path_d_rx_g_tbs_in_blk,
                                        HIVE_ADDR_v2d_path_d_rx_g_dest_buffer_base, HIVE_ADDR_v2d_path_d_rx_g_count1};
    unsigned int vex_path_d_rx0_args_val[] = {0x0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0, 0};
    unsigned int vex_path_d_rx1_args_val[] = {0x0, NUMBER_OF_VECTORS_INPUT, 1, 64, B2H_ADD_MAP_B2_OFFSET, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0}, watermark_buf[MAX_NUM_STREAMS] = {0};
    unsigned int host_ref_d0_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_d1_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;

    init(); /* Initialize the srp*/

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    vex_num_param[2] = argv[2];
    vex_num_param[3] = argv[3];
    v2d_num = argv[4];
    apb_num = argv[5];
    drf_clock = argv[6];
    test_config = argv[7];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = tx_b_vex0", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = tx0_d_vex", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = tx1_d_vex", vex_num_param[2]);
    printf ("INFO: argv[3] : %d = rx_f_vex", vex_num_param[3]);
    printf ("INFO: argv[4] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[5] : %d = apb_num", apb_num);
    printf ("INFO: argv[6] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[7] : %d = test_config", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    sys_rate = g_pdpd_rate_sys_rate_map[drf_clock][pdpd_out_rate];

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*enabling the V2D clock for given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_quad_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config, sys_rate))
    {
        printf ("ERROR: configure_v2d_host");
        return rv;
    }

    /*Gnerating the VEX params*/
    vex_param_gen(vex_path_b_tx_args_val, vex_path_d_rx0_args_val, vex_path_d_rx1_args_val, vex_path_f_rx_args_val, drf_clock, test_config, sys_rate);

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
    {
        printf("ERROR: vex config failed\n");
        return rv;
    }

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    /*Clearing the VEX VMEM and DMEM for both Tx and Rx vex cores*/
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            printf("ERROR: vex_mem_clear failed for vex:%d", vex_num_param[lc]);
            return rv;
        }
    }

    /* vex_num[0] will be used to feed the data to Tx Path B and to loop it back via path D to
     * vex_num[1] and vex_num[2], whatever received on these vex cores via D path will be used to feed the data to Tx path A
     * and to loop it back via path F
     * vex_num[3] will be used to receive the data from path F
     * there by realizing the post processing use case configuration*/

    printf("Host: start vex program load");
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[lc], g_vex_fw_binary[lc])))
        {
            printf("vex loader failed for vex core: %d", lc);
            return rv;
        }
    }

    printf("Host: vex program load - done");

    /* Loading the host parameters to VEX Path B Tx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_b_tx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[0],
                        dmem_offset + vex_path_b_tx_offset_val[lc],
                        &vex_path_b_tx_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Loading the host parameters to VEX path D Rx0 core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_d_rx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        (vex_num_param[1]),
                        dmem_offset + vex_path_d_rx_offset_val[lc],
                        &vex_path_d_rx0_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Loading the host parameters to VEX path D Rx1 core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_d_rx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        (vex_num_param[2]),
                        dmem_offset + vex_path_d_rx_offset_val[lc],
                        &vex_path_d_rx1_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Loading the host parameters to VEX path F Rx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_path_f_rx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        (vex_num_param[3]),
                        dmem_offset + vex_path_f_rx_offset_val[lc],
                        &vex_path_f_rx_args_val[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /*Input Vector generation*/
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_in_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)));
        }
    }

    /* Reading the REF pattern*/
    if (rv = ref_output_read(host_ref_data, host_ref_d0_data, host_ref_d1_data, g_vectors_per_block[drf_clock][pdpd_out_rate], test_config))
    {
        return rv;
    }

    /*Loading the input pattern to B Tx VEX Core*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_b_tx_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[drf_clock][pdpd_in_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Loading the REF pattern to both the D path and F Path VEX cores*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_d_rx_vbuffer,/*local_addr*/
                        host_ref_d0_data,
                        ((g_vectors_per_block[drf_clock][pdpd_out_rate] / 2) * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[2],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_d_rx_vbuffer,/*local_addr*/
                        host_ref_d1_data,
                        ((g_vectors_per_block[drf_clock][pdpd_out_rate] / 2) * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[3],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_path_f_rx_vbuffer,/*local_addr*/
                        host_ref_data,
                        ((g_vectors_per_block[drf_clock][pdpd_out_rate]) * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    printf("Host: vex program start");
    srp_vex_start(vex_hdl, vex_num_param[3], 0); // Start F
    srp_vex_start(vex_hdl, vex_num_param[1], 0); // Start D0
    srp_vex_start(vex_hdl, (vex_num_param[2]), 0);   // Start D1
    srp_vex_start(vex_hdl, vex_num_param[0], 0); // Start B
    printf("Host: vex program start - done");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(1000);

    /* This Sequence shouldn't be changed ,as per post processing flow first B path should be triggered
     * The fill level B path - g_initial_block_size * L = 1 * L
     * Buffer Depth B - 3L
     * similarly fill level A path - g_initial_block_size * L = 1 * L
     * Buffer Depth A - (32Ksample - Buffer Depth B)
     * Buffer Depth for A is kept high to avoid CRUX traffic choking , deviation from actual recommandation*/
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "HBI_1_B2H_FLIT_COUNT")) <
            (g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])))
    {
        // do nothing wait until 1 blocks are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT 0x%x is not the required number of flits", b2h_flit_count);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /* Indicate the VEX PATH B to start continuous transmission*/
    host_indicator = 1;
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_path_b_tx_g_host_indicator,
                    &host_indicator,
                    1,
                    flags)))
        return rv;

    /*Triggering the Path B forced BFN*/
    if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed");
        return rv;
    }

    loop_wait_count = 0;
    b2h_flit_cnt = 0;

    /* Waitng for fill level number of flits in path A*/
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
            g_initial_block_size * (VEC2FLIT(g_flow1_vectors_per_block[sys_rate])))
    {
        // do nothing wait until 1 blocks are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT for CM0 is not the required number of flits");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /*Triggering the Path A forced BFN*/
    if (rv = tx_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed");
        return rv;
    }
#endif
    usleep(10000);
    loop_wait_count = 0;

    /*Wait till required number of flits reached the H2B interface*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_flow1_vectors_per_block[sys_rate])))
    {
        // do nothing wait in this loop till required number of flits streamed in H2B direction
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT 0x%x is not the required number of flits", h2b_flit_count);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    loop_wait_count = 0;
    usleep(1000);

    /*Wait till the RX VEX processed required number of vectors*/
    while (host_vec_processed < (vex_path_f_rx_args_val[2] * g_flow1_vectors_per_block[sys_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[3],
                        dmem_offset + HIVE_ADDR_v2d_path_f_rx_g_count1,
                        &host_vec_processed,
                        1,
                        flags)))
            return rv;

        if (loop_wait_count >= 30)
        {
            printf("ERROR: VEX core didn't processed enough vectors, host_vec_processed : 0x%x", host_vec_processed);
            rv = 1;
            return rv;
        }

        loop_wait_count ++;
        usleep(10000);
    }

    /* Reading the results from Rx VEX*/
    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[3],
                    dmem_offset + HIVE_ADDR_v2d_path_f_rx_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[3],
                    dmem_offset + HIVE_ADDR_v2d_path_f_rx_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x", host_blocks_processed);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV");
        test_status = 1;
    }
    else
    {
        printf("Received output matches with Reference output");
    }

    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: interrupt check failed");
        test_status |= 1;
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int pdpd_fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    int tx_fill_level_value = (g_flow1_vectors_per_block[sys_rate]) + (g_flow1_vectors_per_block[sys_rate] / 2);
    int triggered_fill_level_value[MAX_NUM_STREAMS];

    /*Checking whether fill level was triggered properly or not*/
    pdpd_fill_level_check(v2d_num, apb_num, pdpd_fill_level_value);
    fill_level_check(v2d_num, apb_num, tx_fill_level_value);

    /* Get the fill value when V2D was triggered*/
    get_tx_trigger_fill_level(v2d_num, apb_num, 2/*Number of streams*/, triggered_fill_level_value);
    printf("HOST: Triggered at stream0:0x%x, stream1: 0x%x",
            (triggered_fill_level_value[0] & 0xFFF), ((triggered_fill_level_value[0] >> 16) & 0xFFF));
#endif

    /* Get the watermark high , low values for V2D Buffers*/
    if (rv = get_tx_pdpd_wm_hilo(v2d_num, apb_num, 1/*Number of streams*/, watermark_buf))
    {
        printf("ERROR: get_tx_pdpd_wm_hilo failed");
        test_status |= 1;
    }
    else
    {
        printf("HOST: Low watermark value for B buffer0 : 0x%x", watermark_buf[0] & 0xFFF);
        printf("HOST: High watermark value for B buffer0: 0x%x", (watermark_buf[0] >> 16) & 0xFFF);
    }

    /* Get the watermark high , low values for V2D extra terms Buffers*/
    if (rv = get_tx_wm_hilo(v2d_num, apb_num, 2/*Number of streams*/, watermark_buf))
    {
        printf("ERROR: get_tx_pdpd_wm_hilo failed\n");
        test_status |= 1;
    }
    else
    {
        for (lc = 0; lc < 2; lc++)
        {
            printf("HOST: Low watermark value for C buffer%d: 0x%x", lc, watermark_buf[lc] & 0xFFF);
            printf("HOST: High watermark value for C buffer%d: 0x%x", lc, (watermark_buf[lc] >> 16) & 0xFFF);
        }
    }

    /*this value shouldn't be modified as this is linked to VEX code and if modified VEX code needs to be modified
     * accordinlgy and needs to be recompiled*/
    host_flag = VEX_STOP_TRANSMIT_INDICATION;

    /*Signal from host to stop continuous flow on D Rx0 Vex Core*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_path_d_rx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /*Signal from host to stop continuous flow on D Rx1 Vex Core*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[2],
                    dmem_offset + HIVE_ADDR_v2d_path_d_rx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /*Signal from host to stop continuous flow on B Tx Vex Core*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_path_b_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    usleep(1000);

    /*As VEX cores stopped transmitting the underrun interrupt should be set now*/
    if (rv = interrupt_status_check(v2d_num, apb_num, POST_PROCESSING_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check success");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- vex_tx_b : %d, vex_rx0_d : %d, vex_rx1_d : %d, vex_rx_f : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, \
                pdpd_in_rate : %s, pdpd_out_rate : %s, lut_mode : %d",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, apb_num, drf_clock_str[drf_clock],
                pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
    }
    else
    {
        printf("Host:---- ERROR ---- vex_tx_b : %d, vex_rx0_d : %d, vex_rx1_d : %d, vex_rx_f : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, \
                pdpd_in_rate : %s, pdpd_out_rate : %s, lut_mode : %d",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, apb_num, drf_clock_str[drf_clock],
                pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
        rv = 1;
    }

    return rv;
}   // main ends
