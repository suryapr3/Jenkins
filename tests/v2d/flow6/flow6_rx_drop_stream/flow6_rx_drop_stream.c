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
 * @file    flow6_drop_stream.c
 * @brief   HOST Configuration code for evaluating the Drop stream in the D path.
 * @details 1. Configuration of VEX, V2D and Common Module for sending data from VEX to V2D via B path
               with passthru gain enabled and receving it back to other VEX via D path.
            2. Compares the received output with REF output for result evaluation.
   @TC Description:
        1. continuous blocks for given data rate will be streamed to V2D Tx from
           configured VEX core.
        2. PDPD block was configured with PASS THRU gain and POST FILTER is configured in
           PASSTHRU Mode.
        3. With PDPD Rx loop back (D Path) enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        4. The Rx drop stream (stream 4) is enabled for 1 block of data which will drop the
           alternate blocks in the Rx direction.
        5. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        6, Rx VEX will exclude the first block from data comparison as there is a mismatch for the
           first block in MATLAB model and FPGA output.
        7. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        8. The Tx VEX core will be continuously streaming the data until host indicates them to stop the transmission.
        9. The above can be used to verify whether V2D is getting underrun before the Tx VEX stop transmitting
            the data.
        10. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow6_common_utils.h"
#include "common_utils.h"

#include "v2d_flow6_tx.map.h"
#include "v2d_flow6_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define NUM_VEX_CORES   2
#define TEST_VECTORS_PATH   "test_vectors/"
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
static int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/*config 11 to 16 will be equal to config 5 to 10 as there were no LUT's present*/
const char *ref_file[NUM_CONFIG_PDPD] = {
    "ref_output_p5gsps.txt", "ref_output_1gsps.txt", "ref_output_2gsps.txt", "ref_output_4gsps.txt", "ref_output_8gsps.txt",
    "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config5.txt", "ref_output_config6.txt", "ref_output_config7.txt", "ref_output_config8.txt",
    "ref_output_config9.txt", "ref_output_config10.txt"
};

/* The value corresponds to the number of blocks the TC should run defined as per order in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {32, 16, 8, 4, 2},
    {1000, 1000, 1000, 1000, 1000},
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last five entries order shouldn't be modified*/
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
    /*For any data rate the destination buffer should be of size 2 blocks*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "HBI_1_H2B_BUF_SZ_HW_TBL"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow6_rx_consumer_sm_gate, \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "HBI_1_H2B_TK_ADDR_LKUP_TBL_0"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ADDR_LKUP_TBL_0"},

    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80004000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_ADDR_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, \
        "HBI_1_H2B_MD_CONTROL_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "HBI_1_H2B_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ROUTE_LKUP_TBL"}
    /***********************************************************************************************************************************/
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last six entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow6_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

    // Rx Path Settings , D path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PD_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last six entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX from PDPD
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_DEFAULT, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT_WR_MASK, "RX_PD_STREAM_CNT0"},
    // Rx Stream for Dropping
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT4_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_PD_STREAM_CNT_WR_MASK, "RX_PD_STREAM_CNT4"}
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
int flow6_configure_pdpd(int, int, int, int);
int configure_v2d_host(int *, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock and test_config
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config)
{
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate, pdpd_out_rate;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
    printf ("Buffer: 0x%x", v2d_buffer_b);

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
    printf("fill_level_value : 0x%x", fill_level_value);
#endif

    for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    // Corresponds to cio2strm dest id
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
            g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
        return rv;
    printf("INFO: cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    printf("INFO: strm2cio configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow6_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    for (i = 0; i < (ARRAY_SIZE(g_cm_1_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_cm_1_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), \
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow6_rx_vbuffer_out), \
                    g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_cm_1_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), g_md_control_tbl[drf_clock][pdpd_out_rate], \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_cm_1_config_tbl)); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), vex_num[1], \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf("INFO: CM configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow6_config_tbl) - 6; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    g_v2d_flow6_config_tbl[i].value, g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }
    for (;i < ARRAY_SIZE(g_v2d_flow6_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    g_v2d_flow6_config_tbl[i].value | (drf_clock << 7), g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow6_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow6_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    (g_v2d_flow6_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow6_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow6_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow6_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow6_config_tbl[i].mask, g_v2d_flow6_config_tbl[i].name))
            return rv;
    }

    rv = flow6_configure_pdpd(v2d_num, apb_num, test_config, POST_C_CENTER_VALUE_UNITY_GAIN);
    printf("INFO: V2D pdpd configuration completed");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

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
    printf("INFO: V2D configuration completed");

    return rv;
}

/**
 * @brief           Function to read the ref vectors to be provided to
 *                  VEX Rx cores.
 * @param [in]      pointers to rx buffer, num_vectors and test_config
 * @return          status value
 */
int ref_output_read(unsigned int *host_ref_data, int num_vectors, int test_config)
{
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;
    pdpd_rate_t pdpd_out_rate;

    pdpd_out_rate = g_test_config_tbl[test_config][1];

    sprintf(tref_file, "%s%s", TEST_VECTORS_PATH,ref_file[test_config]);

    printf ("HOST: output file : %s", tref_file);
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

    int offset_val[] = {HIVE_ADDR_v2d_flow6_tx_g_scalar_val, HIVE_ADDR_v2d_flow6_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow6_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow6_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow6_tx_g_initial_block_size, HIVE_ADDR_v2d_flow6_tx_g_host_cycle_count};
    unsigned int val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow6_rx_g_scalar_val, HIVE_ADDR_v2d_flow6_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow6_rx_g_num_blocks, HIVE_ADDR_v2d_flow6_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow6_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_out[NUMBER_OF_VECTORS_OUTPUT][NUM_OF_ELEMENTS_PER_VEC] =  {0};
    unsigned int host_ref_data[VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC] = {0}, watermark_buf[MAX_NUM_STREAMS] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    test_config= (int) argv[5];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = tx_vex0", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx_vex", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[3] : %d = apb_num", apb_num);
    printf ("INFO: argv[4] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[5] : %d = test_config", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    // one block extra needs to be send to avoid the underrun
    val_kargs[3] = vex_rx_val_kargs[2] + 1;
    val_kargs[4] = g_initial_block_size;

    /*Enabling the clock for corresponding V2D Channel*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d clk enable failed");
        return rv;
    }

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config))
    {
        printf("Host Configuration failed");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
        return rv;

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed");
        return rv;
    }

    /*Clearing the VEX VMEM and DMEM for both Tx and Rx vex cores*/
    for (lc = 0; lc < ARRAY_SIZE(vex_num_param); lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            printf("ERROR: vex_mem_clear failed for vex:%d", vex_num_param[lc]);
            return rv;
        }
    }

    printf("Host: start vex program load");
    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow6_tx.fw")))
        return rv;

    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow6_rx.fw")))
        return rv;
    printf("Host: vex program load - done");

    /* Loading the host parameters to VEX  Tx core*/
    for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[0],
                        dmem_offset + offset_val[lc],
                        &val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Loading the host parameters to VEX  Rx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + vex_rx_offset_val[lc],
                        &vex_rx_val_kargs[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Input Vector Generation*/
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_in_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j *2)));
        }
    }

    // Loading the output REF pattern
    if (rv = ref_output_read(host_ref_data, VEX_MAX_BUF_SIZE/*number of vectors*/, test_config))
    {
        return rv;
    }

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow6_tx_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[drf_clock][pdpd_in_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

   if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow6_rx_vbuffer,/*local_addr*/
                        host_ref_data,
                        (VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    printf("Host: vex program start");
    srp_vex_start(vex_hdl, vex_num_param[1], 0); // Rx VEX Core
    srp_vex_start(vex_hdl, vex_num_param[0], 0); // Tx VEX Core
    printf("Host: vex program start - done");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) + \
             VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate] / 2)))
    {
        // do nothing wait in this loop until 1.5 blocks of data was received
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT 0x%x is not the required number of flits", b2h_fllit_count);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    host_flag = 1;

    /*Signal VEX to start continuous flow*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow6_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /* Triggering the forced BFN*/
    if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed");
        return rv;
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till required number of flits reached the H2B interface*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT")) <
            (g_max_blocks[drf_clock][pdpd_out_rate] * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT 0x%x is not the required number of flits", h2b_flit_count);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till the RX VEX processed required number of vectors*/
    while (host_vec_processed < (g_max_blocks[drf_clock][pdpd_out_rate] * g_vectors_per_block[drf_clock][pdpd_out_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + HIVE_ADDR_v2d_flow6_rx_g_count1,
                        &host_vec_processed,
                        1,
                        flags)))
            return rv;

        if (loop_wait_count >= 30)
        {
            printf("ERROR: VEX core didn't processed enough vectors 0x%x", host_vec_processed);
            rv = 1;
            return rv;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /* Reading the results from Rx VEX*/
    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow6_rx_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow6_rx_g_add_val_out,
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
        printf("Received samples match with the Reference output");
    }

    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed");
        test_status = 1;
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];

    /*Checking whether fill level was triggered properly or not*/
    pdpd_fill_level_check(v2d_num, apb_num, fill_level_value);
#endif

    /* Get the watermark high , low values for V2D Buffers*/
    if (rv = get_tx_pdpd_wm_hilo(v2d_num, apb_num, 1/*Number of streams*/, watermark_buf))
    {
        printf("ERROR: get_tx_pdpd_wm_hilo failed");
        test_status |= 1;
    }
    else
    {
        printf("HOST: Low watermark value : 0x%x", watermark_buf[0] & 0xFFF);
        printf("HOST: High watermark value : 0x%x", (watermark_buf[0] >> 16) & 0xFFF);
    }

    /*this value shouldn't be modified as this is linked to VEX code and if modified VEX code needs to be modified
     * accordinlgy and needs to be recompiled*/
    host_flag = VEX_STOP_TRANSMIT_INDICATION;

    /*Signal from host to stop continuous flow on Tx Vex Core*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow6_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    usleep(1000);

    /*As VEX cores stopped transmitting the underrun interrupt should be set now*/
    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: interrupt check failed");
        test_status = 1;
    }
    else
    {
        printf("HOST:Interrupt check passed");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock: %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
        rv = 1;
    }

    return rv;
}
