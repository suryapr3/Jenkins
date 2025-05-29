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
 * @file    flow4_multi_rate.c
 * @details 1. This TC validates the PDPD functionality with extra terms enabled in MODE 1
               configuration and PDPD output data will be receving other VEX CORE.
            2. Compares the received output with REF output for result evaluation.
   @TC Description:
        1. 8K samples Limited by the storage VMEM on the Rx VEX for storing output TVfor given data rate will be streamed
           to V2D Tx from configured VEX core.
        2. The input to DPD block and the extra terms are transmitted from same VEX core.
        3. PDPD block was configured with GMP and DDR terms along with passthru gain.
        4. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 8K sample comparison was done HOST will
           read the result.
        6. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        7. Rx VEX will exclude the first vector from comparison as there is difference between MATLAB model and FPGA output.
        8. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow4_common_utils.h"
#include "common_utils.h"

#include "v2d_flow4_tx.map.h"
#include "v2d_flow4_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NSIP_1_EXP_VALUE 0
#define NUM_VEX_CORES   2
#define B2H_ADD_MAP_B_OFFSET    0x10000
#define POST_FILTER_COEFF 100
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const char *ref_file[2][NUM_CONFIG_PDPD] = {
    {"ref_output_config0.txt", "ref_output_config1.txt", "ref_output_config2.txt", "ref_output_config3.txt", "ref_output_config4.txt",
    "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config11.txt", "ref_output_config12.txt", "ref_output_config13.txt", "ref_output_config14.txt",
    "ref_output_config15.txt", "ref_output_config16.txt"},
    {"ref_output_config0_filter_mode.txt", "ref_output_config1_filter_mode.txt", "ref_output_config2_filter_mode.txt",
     "ref_output_config3_filter_mode.txt", "ref_output_config4_filter_mode.txt", "ref_output_config5_filter_mode.txt",
     "ref_output_config6_filter_mode.txt", "ref_output_config7_filter_mode.txt", "ref_output_config8_filter_mode.txt",
     "ref_output_config9_filter_mode.txt", "ref_output_config10_filter_mode.txt", "ref_output_config11_filter_mode.txt",
     "ref_output_config12_filter_mode.txt", "ref_output_config13_filter_mode.txt", "ref_output_config14_filter_mode.txt",
     "ref_output_config15_filter_mode.txt", "ref_output_config16_filter_mode.txt"}
};

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 4; // For B+C cases the minimum buffer depth is 4L to accommodate the insertion.

/* The value should be VEX_MAX_BUF/g_vectors_per_block[drf_clk][pdpd_rate] in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {32, 16, 8, 4, 2},
    {20, 10, 5, 2, 1}
};

// The last two entries order shouldn't be modified
static v2d_flow_tbl_t g_flow4_cio2strm_config_tbl[] = {
// INT Enable
    {CIO2STRM_OFFSET + CIO2STRM_INT_EN_OFFSET, CIO2STRM_INT_EN_VALUE, \
        CIO2STRM_INT_EN_WR_MASK, "CIO2STRM_INT_ENABLE"},

//VE00 cio2strm
    {CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE, \
        CIO2STRM_FIFO_STAT_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, \
        CIO2STRM_WORD_CNT_CTL_WR_MASK, "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the Two stream from vex core to CRUX*/
    {CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET, 0x00000003, CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, \
        CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW0"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET, (B2H_ADD_MAP_B_OFFSET - 1), \
        CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},

    //MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW1_OFFSET, B2H_ADD_MAP_B_OFFSET, \
        CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW1"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH1_OFFSET, 0x01FFFF, \
        CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH1"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET1_OFFSET, 0x00000000, \
        CIO2STRM_MEM_OFFSET_WR_MASK, "CIO2STRM_MEM_OFFSET1"},
    /***********************************************************************************************************************************/
    /*These last 2 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    //STRM_DEST[0] - mapped to V2D_0_Port_0
    {CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET, 0x00000046, CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
    //STRM_DEST[0] - mapped to V2D_0_Port_1
    {CIO2STRM_OFFSET + CIO2STRM_STRM_DEST1_OFFSET, 0x00000047, CIO2STRM_STRM_DEST_WR_MASK, \
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
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, "HBI_0_B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
        "HBI_0_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), (B2H_ADD_MAP_B_OFFSET - 1), NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
        "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow4_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

 /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x8000 , i.e VEX VMEM location 0x8000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80008000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK, "H2B_MD_CTRL_TBL0"},
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
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, "HBI_1_B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
        "HBI_1_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), (0x80000000 | B2H_ADD_MAP_B_OFFSET), \
        NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), ((2 * B2H_ADD_MAP_B_OFFSET) - 1), \
        NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, "HBI_1_B2H_ADDR_MASK_TBL0"},
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Seven entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow4_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last seven entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX from PDPD, TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer C*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x3FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STRM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
};

#if 0
#define PDPD_PASSTHRU_C_SHDW_OFFSET ( 0x0000e2c0U )
#define PDPD_PASSTHRU_C_LIVE_OFFSET ( 0x0000e2c4U )
#define PDPD_EXTRA_STATIC_OFFSET ( 0x0000e2c8U )
#define PDPD_SCRATCH_OFFSET      ( 0x0000e2ccU )
#define PDPD_CFG_OFFSET       ( 0x0000e2d0U )
#define PDPD_CTRL_OFFSET      ( 0x0000e2d4U )
#define PDPD_CSR_CFG_OFFSET   ( 0x0000e2d8U )
#define PDPD_CSR_ERROR0_OFFSET   ( 0x0000e2dcU )
#define PDPD_CSR_ERROR1_OFFSET   ( 0x0000e2e0U )
#define PDPD_INT_STAT_OFFSET   ( 0x0000e400U )
#define PDPD_INT_HIGH_EN_OFFSET  ( 0x0000e404U )
#define PDPD_INT_LOW_EN_OFFSET   ( 0x0000e408U )
#define PDPD_INT_CLEAR_OFFSET    ( 0x0000e40cU )
#define PDPD_INT_FORCE_OFFSET    ( 0x0000e410U )
#define PDPD_APB_STATUS_OFFSET ( 0x0000e414U )
#endif

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int flow4_configure_pdpd(int, int, int);
int configure_v2d_host(int *, int, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock , test_config and post_filter_mode
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config, int post_filter_mode)
{
    int i, rv = 0, v2d_buffer_b = 0, v2d_buffer_c= 0, pdpd_in_rate = 0, pdpd_out_rate = 0, fill_level_value = 0,
        tx_stream_cnt_value = 0, rx_stream_cnt_value = 0;
    bool us_granularity_required = FALSE;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

#if VEX_1US_WINDOW
    us_granularity_required = get_us_granularity_status(drf_clock, test_config);

    if (us_granularity_required)
    {
        /* Buffer C should be always allocated at lower half of V2D buffer with 3 times of the block size and
         * Buffer B should be always allocated at higher half of V2D buffer with 4 times of the block size*/
        v2d_buffer_c = ((((g_num_blocks_v2d_buffer - 1) * (2 * g_vectors_per_block[drf_clock][pdpd_out_rate] * 2)) - 1) << 16);
        v2d_buffer_b = V2D_BUFFER1_OFFSET | ((V2D_BUFFER1_OFFSET + g_num_blocks_v2d_buffer * \
                       (2 * g_vectors_per_block[drf_clock][pdpd_in_rate] * 2) - 1) << 16);
        tx_stream_cnt_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) - 1;
        rx_stream_cnt_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])) - 1;
    }
    else
#endif
    {

        v2d_buffer_c = ((((g_num_blocks_v2d_buffer - 1) * (g_vectors_per_block[drf_clock][pdpd_out_rate] * 2)) - 1) << 16);
        v2d_buffer_b = V2D_BUFFER1_OFFSET | ((V2D_BUFFER1_OFFSET + g_num_blocks_v2d_buffer * \
                       (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2) - 1) << 16);
        tx_stream_cnt_value = (VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) - 1;
        rx_stream_cnt_value = (VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])) - 1;
    }
    printf ("Buffer b: %x, Buffer C: %x\n", v2d_buffer_b, v2d_buffer_c);

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    // Fill level value should be 2.5 times of the B block size as per HAS
#if VEX_1US_WINDOW
    if (us_granularity_required)
   {
       fill_level_value = (2 * VEC2FLIT(2 * g_vectors_per_block[drf_clock][pdpd_in_rate])) + (2 * g_vectors_per_block[drf_clock][pdpd_in_rate]);
   }
   else
#endif
   {
       fill_level_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) + g_vectors_per_block[drf_clock][pdpd_in_rate];
   }
   printf("fill_level_value : %x\n", fill_level_value);
#endif

    for (i = 0; i < ARRAY_SIZE(g_flow4_cio2strm_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_flow4_cio2strm_config_tbl[i].offset, g_flow4_cio2strm_config_tbl[i].value, \
                g_flow4_cio2strm_config_tbl[i].mask, g_flow4_cio2strm_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_flow4_cio2strm_config_tbl) - 1; i++)
    {
        // Corresponds to cio2strm dest id for extra terms
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_flow4_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][0], \
                g_flow4_cio2strm_config_tbl[i].mask, g_flow4_cio2strm_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_flow4_cio2strm_config_tbl); i++)
    {
        // Corresponds to cio2strm dest id for PDPD main data
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_flow4_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
                g_flow4_cio2strm_config_tbl[i].mask, g_flow4_cio2strm_config_tbl[i].name))
            return rv;
    }
    printf("INFO: cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    printf("INFO: strm2cio configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow4_rx_consumer_sm_gate, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
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
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow4_rx_vbuffer_out), \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    rx_stream_cnt_value, g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[1], \
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

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 7; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    g_v2d_flow4_config_tbl[i].value, g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 6; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    g_v2d_flow4_config_tbl[i].value | (drf_clock << 7), g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), v2d_buffer_b, \
                g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), v2d_buffer_c, \
                g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    (g_v2d_flow4_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    (AV2D_CSR_TX_CSR_TX_STRM_CNT_STRM_EN_BF_MSK | tx_stream_cnt_value), g_v2d_flow4_config_tbl[i].mask, \
                    g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    (AV2D_CSR_TX_CSR_TX_STRM_CNT_STRM_EN_BF_MSK | rx_stream_cnt_value), g_v2d_flow4_config_tbl[i].mask, \
                    g_v2d_flow4_config_tbl[i].name))
            return rv;
    }

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

    if (FILTER_MODE == post_filter_mode)
    {
        if (rv = pdpd_post_c_reg_config(v2d_num, apb_num, POST_FILTER_COEFF))
        {
            printf("pdpd post c reg config failed\n");
            return rv;
        }
    }

    rv = flow4_configure_pdpd(v2d_num, apb_num, test_config);
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

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0,
        post_filter_mode = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    bool us_granularity_required = FALSE;

    int dmem_offset = DMEM_OFFSET;

    int vex_tx_offset_val[] = {HIVE_ADDR_v2d_flow4_tx_g_scalar_val, HIVE_ADDR_v2d_flow4_tx_g_b_num_vecs_in,
                         HIVE_ADDR_v2d_flow4_tx_g_c_num_vecs_in, HIVE_ADDR_v2d_flow4_tx_g_b_dest_buffer_base,
                         HIVE_ADDR_v2d_flow4_tx_g_c_dest_buffer_base,HIVE_ADDR_v2d_flow4_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow4_tx_g_initial_block_size, HIVE_ADDR_v2d_flow4_tx_g_host_cycle_count};
    unsigned int vex_tx_val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, NUMBER_OF_VECTORS_INPUT, B2H_ADD_MAP_B_OFFSET, 0x0, 0, 3,
                                        (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow4_rx_g_scalar_val, HIVE_ADDR_v2d_flow4_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow4_rx_g_num_blocks, HIVE_ADDR_v2d_flow4_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow4_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
    v2d_shdw_live_reg_check_t reg_check;
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    test_config = argv[5];
    post_filter_mode = argv[6];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = tx_vex0\n", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx_vex\n", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[3] : %d = apb_num\n", apb_num);
    printf ("INFO: argv[4] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[5] : %d = test_config\n", test_config);
    printf ("INFO: argv[6] : %d = post_filter_mode %s\n", post_filter_mode, post_filter_mode_str[post_filter_mode]);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)\n",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

#if VEX_1US_WINDOW
    us_granularity_required = get_us_granularity_status(drf_clock, test_config);

    if (us_granularity_required)
    {
        LOG_INFO("VEX_1US granularity enabled");
    }
#endif

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    //This value should be numberof blocks that were configured in the VEX memory to hold
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    // Tx VEX needs to send the data in accordance to the pdpd_out_rate
    // one block extra needs to be send to avoid the underrun
    vex_tx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    vex_tx_val_kargs[2] = g_vectors_per_block[drf_clock][pdpd_out_rate];    // Number of vectors for C path
    vex_tx_val_kargs[5] = vex_rx_val_kargs[2] + 1;  // Number of blocks
    vex_tx_val_kargs[6] = g_initial_block_size;

#if VEX_1P5G
    vex_tx_val_kargs[7] = CYCLES_PER_BLOCK_1P5G - 1;
#endif

#if VEX_1US_WINDOW
    if (us_granularity_required)
    {
        /*number of vectors per block needs to be multiplied by 2*/
        vex_rx_val_kargs[1] = 2 * g_vectors_per_block[drf_clock][pdpd_out_rate];
        vex_tx_val_kargs[1] = 2 * g_vectors_per_block[drf_clock][pdpd_in_rate];
        vex_tx_val_kargs[2] = 2 * g_vectors_per_block[drf_clock][pdpd_out_rate];

        /*max blocks has to be divide by 2*/
        vex_rx_val_kargs[2] = (g_max_blocks[drf_clock][pdpd_out_rate] / 2) + 1;
        vex_tx_val_kargs[5] = vex_rx_val_kargs[2] + 1;

        /* Clock duration has to be multiply by 2*/
        vex_tx_val_kargs[7] = ((vex_tx_val_kargs[7] + 1) * 2) - 1;
    }
#endif

    /*enabling the V2D clock for all the V2D's in the QUAD*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_quad_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config, post_filter_mode))
    {
        printf("Host Configuration failed\n");
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
            printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[lc]);
            return rv;
        }
    }

    printf("Host: start vex program load\n");
    if ((rv = vex_loader(vex_num_param[0], "vex_fw/sim_m64/v2d_flow4_tx.fw")))
        return rv;

    if ((rv = vex_loader(vex_num_param[1], "vex_fw/sim_m64/v2d_flow4_rx.fw")))
        return rv;
    printf("Host: vex program load - done\n");

    /* Loading the host parameters to VEX  Tx core*/
    if (load_vex_param(vex_num_param[0]/*vex_core*/, ARRAY_SIZE(vex_tx_offset_val)/*size of array*/, vex_tx_offset_val, vex_tx_val_kargs))
    {
        LOG_ERROR("Tx vex param loading failed");
    }

    /* Loading the host parameters to VEX  Rx core*/
    if (load_vex_param(vex_num_param[1]/*vex_core*/, ARRAY_SIZE(vex_rx_offset_val)/*size of array*/, vex_rx_offset_val, vex_rx_val_kargs))
    {
        LOG_ERROR("Rx vex param loading failed");
    }

    if (rv = input_pattern_read(val_inp, INPUT_IQ_FILE))
    {
        LOG_ERROR("input pattern read fail");
        return rv;
    }

    /* Reading the REF data from the stored test vectors*/
    sprintf(tref_file, "%s%s", "../test_vectors_1us/", get_ref_file_flow4(post_filter_mode, test_config));

    printf ("HOST: output file : %s\n", tref_file);
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file\n");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_data,
                VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC) < \
                (VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient Output REF data\n");
        return -1;
    }

    fclose(fp_ref_output);

    /* Loading the input vector for Tx vex core*/
    write_mem_18a((VEX_VMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow4_tx_vbuffer),
                (VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC),
                val_inp,
                "TX_VEX_VMEM");

    /* Loading the Reference vectors to Rx vex core for the comparison*/
    /* First block of data will be excluded while loading to Rx VMEM due to MATLAB output generation issue.*/
    write_mem_18a((VEX_VMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow4_rx_vbuffer),
                   VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC,
                   host_ref_data + (vex_rx_val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC),
                   "RX_VEX_VMEM");

    printf("Host: vex program start\n");
    vex_start(vex_num_param[1], 0); // Rx VEX Core
    vex_start(vex_num_param[0], 0); // Tx VEX Core
    printf("Host: vex program start - done\n");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, "B2H_FLIT_COUNT")) < \
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]))))
    {
        // do nothing wait in this loop until 1 blocks of data was received
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("b2h_flit_cnt : %d\n", b2h_flit_count);

    host_flag = 1;
    /*Signal Tx VEX to start continuous flow*/
    if (rv = write_reg_18a(VEX_DMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow4_tx_g_host_indicator,
                host_flag, 0xFFFFFFFF, "HOST_INDICATION"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }

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
    reg_check.gmp_shift_value = FLOW4_GMP_SHIFT_VALUE;
    reg_check.ddr_shift_value = FLOW4_DDR_SHIFT_VALUE;

    if (rv = gmp_ddr_shdw_live_reg_check(&reg_check))
    {
        printf("ERROR: SHDW to LIVE transition failied\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: SHDW to LIVE tranition passed\n");
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till required number of flits reached the H2B interface*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_CNT_OFFSET, "H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])))
    {
        // do nothing wait in this loop
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
    while (host_vec_processed < ((vex_rx_val_kargs[2] - 1) * vex_rx_val_kargs[1]))
    {
        host_vec_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow4_rx_g_count1, "vec_processed");

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
    host_result = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow4_rx_g_compare_result, "compare_result");
    host_blocks_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow4_rx_g_add_val_out, "blocks_processed");

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

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];

    /*Checking whether fill level was triggered properly or not*/
    pdpd_fill_level_check(v2d_num, apb_num, fill_level_value);
#endif

    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed\n");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode]);
        rv = 1;
    }

    return rv;
}
