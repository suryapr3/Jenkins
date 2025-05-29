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
 * @file    flow2_Ch0_Ch1.c
 * @details 1. Configuration of VEX, V2D and Common Module for sending data from VEX to V2D via B path
               with passthru gain enabled along with PASSTHRU post filter mode and receving it back to
               other VEX for both the channels via F path.
            2. Evaluate the result written by VEX for the test case evaluation.
   @TC Description:
        1. 1000 blocks for given data rate will be streamed to V2D Tx from
           configured VEX core for both the Channels.
        2. PDPD block was configured with PASS THRU gain.
        3. V2D memory will be configured for 3 times of the block size of corresponding
           sample rate for the first channel and 16 times of the blocks size for the second
           channel.
        4. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        6, Rx VEX will exclude the first block from data comparison as there is a mismatch for the
           first block in MATLAB model and FPGA output.
        7. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        8. On Tx VEX same block of data is continuously transmitted for 1000 blocks.
        9. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow2_common_utils.h"
#include "common_utils.h"

#include "v2d_flow2_tx.map.h"
#include "v2d_flow2_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NUM_VEX_CORES   4
#define NUM_TX_VEX_CORES    2
#define NUM_RX_VEX_CORES    (NUM_VEX_CORES - NUM_TX_VEX_CORES)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/*config 10 to 16 will be equal to config 5 to 9 as there were no LUT's present*/
const char *ref_file[NUM_CONFIG_PDPD] = {
    "ref_output_p5gsps.txt", "ref_output_1gsps.txt", "ref_output_2gsps.txt", "ref_output_4gsps.txt", "ref_output_8gsps.txt",
    "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt",
    "ref_output_config9.txt", "ref_output_config10.txt"
};

/*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
 * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
int g_num_blocks_v2d_buffer[2] = {3, 3};
int g_initial_block_size = 0;    // VEX will transfer 0.5L before BFN trigger.
#else
/* For the second channel the num blocks was increased to accomodate the inherent delay while triggering BFN registers from HOST
 * Ch0 Buffer 4L Fill Level 0.5L
 * Ch1 Buffer 16L Fill Level 0.5L (Ch1 buffer increased to avoid the CRUX chocking)*/
int g_num_blocks_v2d_buffer[2] = {4, 16};
int g_initial_block_size = 0;    // VEX will transfer 0.5L before BFN trigger.
#endif

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

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow2_rx_consumer_sm_gate), NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80004000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
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
        NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, "HBI_1_B2H_FIFO_CTRL"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
        "HBI_1_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in Bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow2_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last Five entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
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
int flow2_configure_pdpd(int, int, int, int);
int configure_v2d_host(int[], int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      array of vex num, V2d num, drf_clock and test_config
 * @return          status value
 */

int configure_v2d_host(int vex_num_param[], int v2d_num, int drf_clock, int test_config)
{
    int i, rv = 0, v2d_buffer_b = 0, vex_cnt = 0;
    lut_mode_t lut_mode = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    printf("fill_level_value : %x\n", fill_level_value);
#endif

    /* Loop for APB0 , APB1 corresponds to Ch0 , Ch1 configuration*/
    for (vex_cnt = 0; vex_cnt < NUM_TX_VEX_CORES; vex_cnt++)
    {
        int vex_num = vex_num_param[vex_cnt * 2];
        int apb_num = vex_cnt;
        v2d_buffer_b = ((((g_num_blocks_v2d_buffer[vex_cnt]) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
        printf ("Buffer: %x\n", v2d_buffer_b);

        for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
        {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
                return rv;
        }
        // Corresponds to cio2strm dest id
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
        printf("INFO: cio2strm configuration completed");

        vex_num = vex_num_param[(vex_cnt * 2) + 1]; // Rx VEX num
        for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
        {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                        g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
                return rv;
        }
        printf("INFO: strm2cio configuration completed");

        // SDF init
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                    HIVE_ADDR_v2d_flow2_rx_consumer_sm_gate, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
            return rv;

        for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
                return rv;
        }
        for (; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                        (0x80000000 | HIVE_ADDR_v2d_flow2_rx_vbuffer_out), g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
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
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num, \
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

        for (i = 0; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 5; i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        g_v2d_flow2_config_tbl[i].value, g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
                return rv;
        }
        for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 4; i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        g_v2d_flow2_config_tbl[i].value | (drf_clock << 7), g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
                return rv;
        }
        for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 3; i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        v2d_buffer_b, g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
                return rv;
        }
        for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 2; i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        (g_v2d_flow2_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                        g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
                return rv;
        }
        for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 1; i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
                return rv;
        }
        for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl); i++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                        g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
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

        rv = flow2_configure_pdpd(v2d_num, apb_num, test_config, POST_C_CENTER_VALUE_UNITY_GAIN);
        printf("INFO: V2D pdpd configuration completed");

        /************************************************************************************************************/
        /* This should be the last register of Tx to configure*/
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_VALUE, \
                AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
            return rv;
        /* This should be the last register of Rx to configure*/
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), RX_GNRL_CSR_VALUE, \
                AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
            return rv;
        /************************************************************************************************************/
        printf("INFO: V2D configuration completed");
    }

    return rv;
}

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    int lc, i, j, vex_cnt = 0;
    int vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, drf_clock, test_config;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    int dmem_offset = DMEM_OFFSET;

    int offset_val[] = {HIVE_ADDR_v2d_flow2_tx_g_scalar_val, HIVE_ADDR_v2d_flow2_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow2_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow2_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow2_tx_g_initial_block_size, HIVE_ADDR_v2d_flow2_tx_g_host_cycle_count};
    unsigned int val_kargs[] = {0x0, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow2_rx_g_scalar_val, HIVE_ADDR_v2d_flow2_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow2_rx_g_num_blocks, HIVE_ADDR_v2d_flow2_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow2_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_out[NUMBER_OF_VECTORS_OUTPUT][NUM_OF_ELEMENTS_PER_VEC] =  {0};
    unsigned int host_ref_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int apb0_b2h_flit_count = 0, apb0_h2b_flit_count = 0, apb1_b2h_flit_count = 0, apb1_h2b_flit_count = 0;
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);
    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    vex_num_param[2] = argv[2];
    vex_num_param[3] = argv[3];
    v2d_num = argv[4];
    drf_clock = (int) argv[5];
    test_config = (int) argv[6];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = tx0_vex\n", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx0_vex\n", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = tx1_vex\n", vex_num_param[2]);
    printf ("INFO: argv[3] : %d = rx1_vex\n", vex_num_param[3]);
    printf ("INFO: argv[4] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[5] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[6] : %d = test_config\n", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)\n",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    // one block extra needs to be send to avoid the underrun
    val_kargs[3] = vex_rx_val_kargs[2] + 1;
    val_kargs[4] = g_initial_block_size;

    /* Clear the VEX VMEM and DMEM for all the used VEX cores*/
    for (vex_cnt = 0; vex_cnt < ARRAY_SIZE(vex_num_param); vex_cnt++)
    {
        vex_mem_clear(vex_num_param[vex_cnt], srp);
    }
    if (rv = v2d_clk_enable(v2d_num, DRF_CHANNEL_BOTH))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }

    /*Enabling the VEX clock as per DRF clock*/
#if VEX_1P5G
    if (CLOCK_1P5G == drf_clock)
    {
        val_kargs[5] = CYCLES_PER_BLOCK_1P5G - 1;
    }
#endif
    if (rv = configure_v2d_host(vex_num_param, v2d_num, drf_clock, test_config))
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

    /* Input Vector Generation*/
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_in_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j *2)));
        }
    }

    /*Loading the REF pattern*/
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
                g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC) < \
                g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC)
    {
        printf("ERROR: Insufficient Output REF data\n");
        return -1;
    }
    fclose(fp_ref_output);

    printf("Host: start vex program load \n");

    for (vex_cnt = 0; vex_cnt < NUM_TX_VEX_CORES; vex_cnt++)
    {
        int rx_vex_num = vex_num_param[(2 * vex_cnt) + 1]; // RX VEX Core
        int tx_vex_num = vex_num_param[(2 *vex_cnt)];   // Tx VEX Core

        if ((rv = vex_loader(tx_vex_num, "vex_fw/sim_m64/v2d_flow2_tx.fw")))
            return rv;

        if ((rv = vex_loader(rx_vex_num, "vex_fw/sim_m64/v2d_flow2_rx.fw")))
            return rv;
        printf("Host: vex program load - done\n");

        /* Loading the host parameters to VEX  Tx core*/
        if (load_vex_param(tx_vex_num/*vex_core*/, ARRAY_SIZE(offset_val)/*size of array*/, offset_val, val_kargs))
        {
            LOG_ERROR("Tx vex param loading failed");
        }

        /* Loading the host parameters to VEX  Rx core*/
        if (load_vex_param(rx_vex_num /*vex_core*/, ARRAY_SIZE(vex_rx_offset_val), vex_rx_offset_val, vex_rx_val_kargs))
        {
            LOG_ERROR("Rx vex param loading failed");
        }

        /*Loading input pattern to Tx VEX core*/
        if ((rv = write_mem_18a(VEX_VMEM(tx_vex_num) + HIVE_ADDR_v2d_flow2_tx_vbuffer,/*local_addr*/
                            (g_vectors_per_block[drf_clock][pdpd_in_rate] * NUM_OF_ELEMENTS_PER_VEC), val_inp[0],
                             "VEX_VMEM")))
            return rv;

        /*Loading REF pattern to Rx VEX core*/
        if ((rv = write_mem_18a(VEX_VMEM(rx_vex_num) + HIVE_ADDR_v2d_flow2_rx_vbuffer,/*local_addr*/
                             (g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC), host_ref_data,
                             "VEX_VMEM")))
        return rv;
    }
    printf("Host: vex program start");

    vex_start(vex_num_param[1], 0); // Start Rx0 VEX Core
    vex_start(vex_num_param[0], 0); // Start Tx0 VEX Core
    vex_start(vex_num_param[3], 0); // Start Rx1 VEX Core
    vex_start(vex_num_param[2], 0); // Start Tx1 VEX Core
    printf("Host: vex program start - done");

/*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
 * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((apb0_b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, "APB0_B2H_FLIT_COUNT")) <
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) + VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate] / 2)))
    {
        // do nothing wait in this loop until (g_initial_block_size + 0.5) blocks of data was received
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while APB0 B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    loop_wait_count = 0;
    while ((apb1_b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, 1) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "APB1_B2H_FLIT_COUNT")) <
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) + VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate] / 2)))
    {
        // do nothing wait until (g_initial_block_size + 0.5) blocks are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while APB1 B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    printf ("apb0_b2h_flit_cnt : %d, apb1_b2h_flit_cnt: %d\n", apb0_b2h_flit_count, apb1_b2h_flit_count);

    host_flag = 1;
    /* Ch0 is triggered first, Ch1 is triggered next this order should be maintained as buffer size is
     * configured for this specific order*/
    for (vex_cnt = 0; vex_cnt < ARRAY_SIZE(vex_num_param); vex_cnt++)
    {
        int vex_num = vex_num_param[vex_cnt];
        /*Signal VEX to start continuous flow*/
        if (rv = write_reg_18a(VEX_DMEM(vex_num) + HIVE_ADDR_v2d_flow2_tx_g_host_indicator,
                        host_flag,
                        0xFFFFFFFF,
                        "HOST_INDICATION"))
            return rv;
        int apb_num = vex_cnt;
        if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
        {
            printf ("BFN trigger failed\n");
            return rv;
        }
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till required number of flits reached the APB0 H2B interface*/
    while ((apb0_h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_CNT_OFFSET, "APB0_H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while APB0_H2B_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    loop_wait_count = 0;

    /*Wait till required number of flits reached the APB1 H2B interface*/
    while ((apb1_h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, 1) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_CNT_OFFSET, "APB1_H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while APB1_H2B_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("apb0_h2b_flit_cnt is %d, apb1_h2b_flit_cnt is %d\n", apb0_h2b_flit_count, apb1_h2b_flit_count);

    loop_wait_count = 0;
    usleep(10000);

    for (vex_cnt = 0; vex_cnt < NUM_RX_VEX_CORES; vex_cnt++)
    {
        int vex_num = vex_num_param[(2 * vex_cnt) + 1];
        host_vec_processed = 0;
        host_blocks_processed = 0;
        loop_wait_count = 0;

        /*Wait till the RX VEX processed required number of vectors*/
        while (host_vec_processed < ((g_max_blocks[drf_clock][pdpd_out_rate] - 1) * g_vectors_per_block[drf_clock][pdpd_out_rate]))
        {
            host_vec_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow2_rx_g_count1, "vec_processed");

            if (loop_wait_count >= 30)
            {
                printf("ERROR: VEX core %d didn't processed enough vectors\n", vex_num + 1);
                rv = 1;
                return rv;
            }
            loop_wait_count ++;
            usleep(10000);
        }

        /* Reading the results from Rx VEX*/
        host_result = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow2_rx_g_compare_result, "compare_result");
        host_blocks_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow2_rx_g_add_val_out, "blocks_processed");

        printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
        printf ("processed blocks 0x%x\n", host_blocks_processed);

        if (0xFFFFFFFF != host_result)
        {
            printf ("ERROR: Received output didn't match with Reference output TV\n");
            test_status |= 1;
        }
        else
        {
            printf("HOST: Received output matches with reference output for vex:%d\n", vex_num + 1);
        }

        /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
         * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
        int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];

        /*Checking whether fill level was triggered properly or not*/
        pdpd_fill_level_check(v2d_num, vex_cnt/*apb_num*/, fill_level_value);
#endif

        if (rv = interrupt_status_check(v2d_num, vex_cnt, V2D_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
        {
            printf("ERROR:Interrupt check failed\n");
            test_status |= 1;
        }
        else
        {
            printf("HOST: Interrupt status check passed");
        }
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx0_vex_num : %d, rx0_vex_num: %d, tx1_vex_num : %d, rx1_vex_num : %d, v2d_num : %d,drf_clock: %s, \
                pdpd_in_rate: %s, pdpd_out_rate: %s, lut_mode: %d\n",
        vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, drf_clock_str[drf_clock],
        pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx0_vex_num : %d, rx0_vex_num: %d, tx1_vex_num : %d, rx1_vex_num : %d, v2d_num : %d,drf_clock: %s, \
                pdpd_in_rate: %s, pdpd_out_rate: %s, lut_mode: %d\n",
        vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, drf_clock_str[drf_clock],
        pdpd_rate_str[pdpd_in_rate], pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
        rv = 1;
    }

    return rv;
}
