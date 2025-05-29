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
 * @file    flow5_multi_rate.c
 * @details 1. This TC validates the PDPD functionality with extra terms enabled in MODE 1
               configuration and PDPD output data will be receving other VEX CORE.
            2. Compares the received output with REF output for result evaluation.
   @TC Description:
        1. 1000 blocks for given data rate will be streamed to V2D Tx from configured VEX cores.
        2. The input to DPD block will be transmitted from one VEX core and the two extra terms are
           transmitted from same VEX core which is different to the one transmits the PDPD input.
        3. PDPD block was configured with GMP and DDR terms along with passthru gain.
        4. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 8K sample comparison was done HOST will
           read the result.
        6. Rx VEX will exclude the first vector from comparison as there is difference between MATLAB model and FPGA output.
        7. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        8. Both the PDPD input and extra terms VEX cores will transmit the same data for every block so that
           the comparison can be run for more blocks.
        9. The Tx VEX cores will be continuously streaming the data until host indicates them to stop the transmission.
        10. The above can be used to verify whether V2D is getting underrun before the Tx VEX stop transmitting
            the data.
        11. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow5_common_utils.h"
#include "common_utils.h"

#include "v2d_flow5_tx_b.map.h"
#include "v2d_flow5_tx_c.map.h"
#include "v2d_flow5_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define NSIP_1_EXP_VALUE 0
// These are the logical mapping of VEX to CIO2STRM
#define BUFFER_START_ADDRESS_C0 0x0
#define BUFFER_START_ADDRESS_C1 0x8000
#define BUFFER_START_ADDRESS_B  0x0
#define CIO2STRM_MEM_MAP  0x10000
#define NUM_VEX_CORES   3
#define NUM_TX_VEX_CORES    2
#define NUM_RX_VEX_CORES    (NUM_VEX_CORES - NUM_TX_VEX_CORES)
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const char *ref_file[NUM_CONFIG_PDPD] = {
    "ref_output_config0.txt", "ref_output_config1.txt", "ref_output_config2.txt", "ref_output_config3.txt", "ref_output_config4.txt",
    "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config11.txt", "ref_output_config12.txt", "ref_output_config13.txt", "ref_output_config14.txt",
    "ref_output_config15.txt", "ref_output_config16.txt"
};


char *g_vex_fw_binary[] = {"vex_fw/sim_m64/v2d_flow5_tx_b.fw", "vex_fw/sim_m64/v2d_flow5_tx_c.fw", "vex_fw/sim_m64/v2d_flow5_rx.fw"};

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/* The value should be as per order defined in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {1000, 1000, 1000, 1000, 1000},
    {1000, 1000, 1000, 1000, 1000}
};

// The last two entries order shouldn't be modified
static v2d_flow_tbl_t g_flow5_cio2strm_config_tbl[] = {
// INT Enable
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_INT_ENABLE_OFFSET, CIO2STRM_INT_EN_VALUE, \
        CIO2STRM_MEM_CIO2STRM_INT_ENABLE_WR_MASK, "CIO2STRM_INT_ENABLE"},

//VE00 cio2strm
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE, \
        CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, \
        CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_WR_MASK, "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the Two stream from vex core to CRUX*/
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_RANGE_EN_OFFSET, 0x00000003, CIO2STRM_MEM_CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW0"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_OFFSET, (CIO2STRM_MEM_MAP - 1), \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},

    //MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW1_OFFSET, (CIO2STRM_MEM_MAP), \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW1"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH1_OFFSET, 0x01FFFF, \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH1"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET1_OFFSET, 0x00000000, \
        CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, "CIO2STRM_MEM_OFFSET1"},
    /***********************************************************************************************************************************/
    /*These last 2 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    //STRM_DEST[0] - mapped to V2D_0_Port_0
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_STRM_DEST0_OFFSET, 0x00000046, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
    //STRM_DEST[1] - mapped to V2D_0_Port_0
    {CIO2STRM_OFFSET + CIO2STRM_MEM_CIO2STRM_STRM_DEST1_OFFSET, 0x00000046, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST1"}
    /***********************************************************************************************************************************/
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
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "HBI_0_B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, \
        "HBI_0_B2H_CREDIT_CS"},
    // CM addr map and addr tbl offsets should match with the VEX transmit address
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 512 flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), (CIO2STRM_MEM_MAP - 1), \
        NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET), 0x80000000 | CIO2STRM_MEM_MAP, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL1"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET), ((2 * CIO2STRM_MEM_MAP) - 1), \
        NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL1"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow5_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x8000 , i.e VEX VMEM location 0x8000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80008000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"}
    /***********************************************************************************************************************************/
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
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
    // CM addr map and addr tbl offsets should match with the VEX transmit address
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000 | BUFFER_START_ADDRESS_B, \
        NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0xFFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last nine entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow5_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last nine entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x3FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND1_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT1_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT1"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
};

#if 0
#define PDPD_PASSTHRU_C_SHDW_OFFSET ( 0x0000e2c0U )
#define PDPD_PASSTHRU_C_LIVE_OFFSET ( 0x0000e2c4U )
#define PDPD_EXTRA_STATIC_OFFSET ( 0x0000e2c8U )
#define PDPD_SCRATCH_OFFSET      ( 0x0000e2ccU )
#define PDPD_CONFIG_OFFSET       ( 0x0000e2d0U )
#define PDPD_CONTROL_OFFSET      ( 0x0000e2d4U )
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
int flow5_configure_pdpd(int, int, int);
int configure_v2d_host(int *, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num drf_clock and test config
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config)
{
    int i, j, rv = 0, v2d_buffer_b = 0, v2d_buffer_c0 = 0, v2d_buffer_c1 = 0, pdpd_in_rate = 0, pdpd_out_rate = 0, tx_c_stream_cnt = 0;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    /* Buffer C should be always allocated at lower half of V2D buffer and
     * Buffer B should be always allocated at higher half of V2D buffer*/
    v2d_buffer_c0 = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_out_rate])) - 1) << 16);
    v2d_buffer_c1 = ((v2d_buffer_c0) >> 16) + 1 | ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_out_rate] * 2)) - 1) << 16);
    v2d_buffer_b = V2D_BUFFER1_OFFSET | ((V2D_BUFFER1_OFFSET + g_num_blocks_v2d_buffer * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2) - 1) << 16);
    printf ("Buffer b: 0x%x, Buffer C0: 0x%x, Buffer C1: 0x%x\n", v2d_buffer_b, v2d_buffer_c0, v2d_buffer_c1);

    tx_c_stream_cnt = AV2D_CSR_TX_CSR_TX_STREAM_CNT_STREAM_EN_BF_MSK | ((VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate]) / 2) - 1);

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    // Fill level value should be 2.5 times of the B block size as per HAS
    int fill_level_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    printf("fill_level_value : 0x%x\n", fill_level_value);
#endif

    for (j = 0; j < NUM_TX_VEX_CORES; j++)
    {
        for (i = 0; i < ARRAY_SIZE(g_flow5_cio2strm_config_tbl) - 2; i++)
        {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[j]) + g_flow5_cio2strm_config_tbl[i].offset, g_flow5_cio2strm_config_tbl[i].value, \
                    g_flow5_cio2strm_config_tbl[i].mask, g_flow5_cio2strm_config_tbl[i].name))
                return rv;
        }
    }

    for (i = (ARRAY_SIZE(g_flow5_cio2strm_config_tbl) - 2); i < ARRAY_SIZE(g_flow5_cio2strm_config_tbl) - 1; i++)
    {
        // Corresponds to cio2strm dest id for PDPD Main data
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_flow5_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
                g_flow5_cio2strm_config_tbl[i].mask, g_flow5_cio2strm_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_flow5_cio2strm_config_tbl); i++)
    {
        // Corresponds to cio2strm dest id for extra terms VEX
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_flow5_cio2strm_config_tbl[i].offset, vex_num[1], \
                g_flow5_cio2strm_config_tbl[i].mask, g_flow5_cio2strm_config_tbl[i].name))
            return rv;
    }

    for (i = (ARRAY_SIZE(g_flow5_cio2strm_config_tbl) - 2); i < ARRAY_SIZE(g_flow5_cio2strm_config_tbl); i++)
    {
        // Corresponds to cio2strm dest id for extra terms
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_flow5_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][0], \
                g_flow5_cio2strm_config_tbl[i].mask, g_flow5_cio2strm_config_tbl[i].name))
            return rv;
    }
    printf("INFO: cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[2]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    printf("INFO: strm2cio configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[2]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow5_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow5_rx_vbuffer_out), \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    g_md_control_tbl[drf_clock][pdpd_out_rate], g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[2], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    for (i = 0; i < ARRAY_SIZE(g_cm_1_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf("INFO: CM configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 9; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    g_v2d_flow5_config_tbl[i].value, g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 8; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    g_v2d_flow5_config_tbl[i].value | (drf_clock << 7), g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 7; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), v2d_buffer_b, \
                g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 6; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), v2d_buffer_c0, \
                g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), v2d_buffer_c1, \
                g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    (g_v2d_flow5_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    tx_c_stream_cnt, g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow5_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow5_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow5_config_tbl[i].mask, g_v2d_flow5_config_tbl[i].name))
            return rv;
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

    rv = flow5_configure_pdpd(v2d_num, apb_num, test_config);
    printf("INFO: V2D pdpd configuration completed\n");

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), \
                TX_GNRL_CSR_VALUE, AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), \
                RX_GNRL_CSR_VALUE, AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf("INFO: V2D configuration completed\n");

    return rv;
}

/**
 * @brief           Function to read the ref vectors to be provided to
 *                  VEX Rx cores.
 * @param [in]      pointers to rx buffer and test_config
 * @return          status value
 */
int ref_output_read(unsigned int *host_ref_data, int test_config)
{
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;

    sprintf(tref_file, "%s%s", PATH_PREFIX,ref_file[test_config]);

    printf ("HOST: output file : %s\n", tref_file);
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file\n");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_data,
                VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC) < \
                (VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient Output REF data\n");
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

    int dmem_offset = DMEM_OFFSET;

    int vex_tx_b_offset_val[] = {HIVE_ADDR_v2d_flow5_tx_b_g_scalar_val, HIVE_ADDR_v2d_flow5_tx_b_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow5_tx_b_g_dest_buffer_base,HIVE_ADDR_v2d_flow5_tx_b_g_vex_indication_address,
                         HIVE_ADDR_v2d_flow5_tx_b_g_num_blocks, HIVE_ADDR_v2d_flow5_tx_b_g_initial_block_size,
                         HIVE_ADDR_v2d_flow5_tx_b_g_host_cycle_count};
    unsigned int vex_tx_b_val_kargs[] = {0x0, NUMBER_OF_VECTORS_INPUT, 0, STRM2CIO_2_VEX_DMEM_OFFSET, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_tx_c_offset_val[] = {HIVE_ADDR_v2d_flow5_tx_c_g_scalar_val, HIVE_ADDR_v2d_flow5_tx_c_g_num_vecs_in,
                        HIVE_ADDR_v2d_flow5_tx_c_g_dest_buffer_base_c0, HIVE_ADDR_v2d_flow5_tx_c_g_dest_buffer_base_c1,
                        HIVE_ADDR_v2d_flow5_tx_c_g_num_blocks, HIVE_ADDR_v2d_flow5_tx_c_g_initial_block_size,
                        HIVE_ADDR_v2d_flow5_tx_c_g_host_cycle_count};
    unsigned int vex_tx_c_val_kargs[] = {0x0, NUMBER_OF_VECTORS_INPUT, 0, 0x10000, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow5_rx_g_scalar_val, HIVE_ADDR_v2d_flow5_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow5_rx_g_num_blocks, HIVE_ADDR_v2d_flow5_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow5_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC] = {0}, watermark_buf[MAX_NUM_STREAMS] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
    v2d_shdw_live_reg_check_t reg_check;

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    vex_num_param[2] = argv[2];
    v2d_num = argv[3];
    apb_num = argv[4];
    drf_clock = (int) argv[5];
    test_config = argv[6];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = tx_vex_b\n", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = tx_vex_c\n", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = rx_vex\n", vex_num_param[2]);
    printf ("INFO: argv[3] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[4] : %d = apb_num\n", apb_num);
    printf ("INFO: argv[5] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[6] : %d = test_config\n", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)\n",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    //This value should be numberof blocks that were configured in the VEX memory to hold
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    // Parameters for tx_b vex
    vex_tx_b_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    vex_tx_b_val_kargs[3] = STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow5_tx_c_g_vex_indicator;
    vex_tx_b_val_kargs[4] = vex_rx_val_kargs[2] + 1;
    vex_tx_b_val_kargs[5] = g_initial_block_size;

    // Parameters for tx_c vex
    vex_tx_c_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_tx_c_val_kargs[2] = BUFFER_START_ADDRESS_C0;
    vex_tx_c_val_kargs[3] = CIO2STRM_MEM_MAP;
    vex_tx_c_val_kargs[4] = vex_rx_val_kargs[2] + 1;
    vex_tx_c_val_kargs[5] = g_initial_block_size;


    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*enabling the V2D clock for all the V2D's in the QUAD*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_quad_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config))
    {
        printf("Host Configuration failed\n");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
        return rv;

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
            printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[lc]);
            return rv;
        }
    }

    printf("Host: start vex program load\n");
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[lc], g_vex_fw_binary[lc])))
            return rv;
    }

    /* If the rate is P5 load the specific extra terms Tx VEX core fw*/
    if (PDPD_RATE_IQ_P5 == pdpd_out_rate)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow5_tx_c_p5iq.fw")))
            return rv;
    }
    printf("Host: vex program load - done\n");

    /* Loading the host parameters to VEX  Tx  B core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_tx_b_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[0],
                        dmem_offset + vex_tx_b_offset_val[lc],
                        &vex_tx_b_val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++) ends


    /* Loading the host parameters to VEX  Tx C0 & C1 core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_tx_c_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + vex_tx_c_offset_val[lc],
                        &vex_tx_c_val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++) ends

    /* Loading the host parameters to VEX  Rx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[2],
                        dmem_offset + vex_rx_offset_val[lc],
                        &vex_rx_val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++) ends

    /* Input Vector Generation*/
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_in_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)));
        }
    }

    /* Reading the REF pattern*/
    if (rv = ref_output_read(host_ref_data, test_config))
    {
        return rv;
    }

    for (lc = 0; lc < NUM_TX_VEX_CORES; lc++)
    {
        /* Loading the input vector for Tx vex cores*/
        if ((rv = srp_vex_memid_store(vex_hdl,
                            vex_num_param[lc],
                            SRP_VEX_VMEM,
                            HIVE_ADDR_v2d_flow5_tx_b_vbuffer,/*local_addr*/
                            val_inp[0],
                            (g_vectors_per_block[drf_clock][pdpd_in_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
    }

    /* Loading the Reference vectors to Rx vex core for the comparison*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[2],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow5_rx_vbuffer,/*local_addr*/
                        host_ref_data,
                        (VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    printf("Host: vex program start for tx & rx vex cores\n");
    srp_vex_start(vex_hdl, vex_num_param[2], 0); // Rx VEX Core
    srp_vex_start(vex_hdl, vex_num_param[1], 0); // Tx VEX Core for extra terms
    srp_vex_start(vex_hdl, vex_num_param[0], 0); // Tx VEX Core for PDPD main data
    printf("Host: vex program start - done\n");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET,"B2H_FLIT_COUNT")) < \
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]))))
    {
        // do nothing wait in this loop until 1 blocks of pre-fill data was received
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("b2h_flit_cnt_CM1 : %d\n", b2h_flit_count);

    b2h_flit_count = 0;
    loop_wait_count = 0;
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET,"B2H_FLIT_COUNT")) < \
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate]))))
    {
        // do nothing wait in this loop until 1 blocks of pre-fill data was received
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("b2h_flit_cnt_CM0 : %d\n", b2h_flit_count);

    host_flag = 1;
    /*Signal from host to start continuous flow on B Tx Vex Core , which in turn will signal the C Tx Vex core to start continuous transmission*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow5_tx_b_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /* Trigger BFN to start the PDPD block*/
    if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }
#endif

#if (0 == REGRESSION)
    /*To Check whether SHADOW to LIVE transition happened or not*/
    reg_check.v2d_num = v2d_num;
    reg_check.apb_num = apb_num;
    reg_check.test_config = test_config;
    reg_check.num_gmp_terms = V2D_PDPD_GMP_TERMS;
    reg_check.num_ddr_terms = V2D_PDPD_DDR_TERMS;
    reg_check.gmp_c_i_value = GMP_C_I_VALUE;
    reg_check.gmp_c_q_value = GMP_C_Q_VALUE;
    reg_check.ddr_c_i_value = DDR_C_I_VALUE;
    reg_check.ddr_c_q_value = DDR_C_Q_VALUE;
    reg_check.gmp_shift_value = FLOW5_GMP_SHIFT_VALUE;
    reg_check.ddr_shift_value = FLOW5_DDR_SHIFT_VALUE;

    if (rv = gmp_ddr_shdw_live_reg_check(&reg_check))
    {
        printf("ERROR: SHDW to LIVE transition failied\n");
        test_status = 1;
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till required number of flits reached the H2B interface*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])))
    {
        // do nothing wait in this loop till required number of flits streamed in H2B direction
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("h2b_flit cnt is %d\n", h2b_flit_count);

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till the RX VEX processed required number of vectors*/
    while (host_vec_processed < (g_max_blocks[drf_clock][pdpd_out_rate] * g_vectors_per_block[drf_clock][pdpd_out_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[2],
                        dmem_offset + HIVE_ADDR_v2d_flow5_rx_g_count1,
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
    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[2],
                    dmem_offset + HIVE_ADDR_v2d_flow5_rx_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[2],
                    dmem_offset + HIVE_ADDR_v2d_flow5_rx_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x\n", host_blocks_processed);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV\n");
        test_status = 1;
    }
    else
    {
        printf("Received output matches with Reference output\n");
    }

    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: interrupt check failed\n");
        test_status |= 1;
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    int triggered_fill_level_value[MAX_NUM_STREAMS];

    /*Checking whether fill level was triggered properly or not*/
    pdpd_fill_level_check(v2d_num, apb_num, fill_level_value);

    /* Get the fill value when V2D was triggered*/
    get_tx_trigger_fill_level(v2d_num, apb_num, 2/*Number of streams*/,triggered_fill_level_value);

    printf("HOST: Triggered at stream0:0x%x, stream1: 0x%x",
            (triggered_fill_level_value[0] & 0xFFF), ((triggered_fill_level_value[0] >> 16) & 0xFFF));
#endif

    /* Get the watermark high , low values for V2D Buffers*/
    if (rv = get_tx_pdpd_wm_hilo(v2d_num, apb_num, 1/*Number of streams*/, watermark_buf))
    {
        printf("ERROR: get_tx_pdpd_wm_hilo failed\n");
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

    for (lc = 0; lc < NUM_TX_VEX_CORES; lc ++)
    {
        /*Signal from host to stop continuous flow on B Tx Vex Core , which in turn will signal the C Tx Vex core to stop continuous transmission*/
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[lc],
                        dmem_offset + HIVE_ADDR_v2d_flow5_tx_b_g_host_indicator,
                        &host_flag,
                        1,
                        flags)))
            return rv;
    }

    usleep(1000);

    /*As VEX cores stopped transmitting the underrun interrupt should be set now*/
    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check success\n");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- vex_tx_b : %d, vex_tx_c : %d, vex_rx : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, \
                pdpd_in_rate : %s, pdpd_out_rate : %s, lut_mode : %d\n",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], v2d_num, apb_num, drf_clock_str[drf_clock],
                pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
    }
    else
    {
        printf("Host:---- FAIL ---- vex_tx_b : %d, vex_tx_c : %d, vex_rx : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, \
                pdpd_in_rate : %s, pdpd_out_rate : %s, lut_mode : %d\n",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], v2d_num, apb_num, drf_clock_str[drf_clock],
                pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
        rv = 1;
    }

    return rv;
}
