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
 * @file    flow3_pdpd_ingress.c
 * @brief   HOST Configuration code for evaluating the PDPD block with GMP and DDR terms enabled along with
 *          enabling the X-Capture at PDPD ingress.
 * @details 1. Configuration of VEX, V2D's Common Module for sending data from VEX to V2D via B path
               with passthru gain enabled along with GMP and DDR terms and receving it back to other VEX.
            2. Compares the received output with REF output for result evaluation.
            3. Configure the MEM_FB to receive the data from PDPD Ingress and do the comparison from HOST
               for 1MB captured data.
   @TC Description:
        1. 8K samples Limited by the storage VMEM on the Rx VEX for storing output TV for given data rate will be streamed
           to V2D Tx from configured VEX core.
        2. PDPD block was configured with GMP and DDR terms along with passthru gain and with POST FILTER enabled with PASSTHRU mode.
        3. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        4. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 8K sample comparison was done HOST will
           read the result.
        5. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        6. Rx VEX will exclude the first vector from comparison as there is difference between MATLAB model and FPGA output.
        7. X-Data capture at PDPD Ingress was enabled in single shot mode for 256K samples and corresponding MEM_FB configuration
           was done from the HOST.
        8. X-Data capture will be triggered from BFN timed trigger which will be programmed from RCS.
        9. Host will read and compare the 256K samples from Capture memory to evaluate PASS FAIL criteria.
        6. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

*****************************************************************************************************************************************
NOTE:
CAPTURE_DURATION compile flag should be same state(enabled/disabled) in both HOST code as well as RCS code, care should be taken while
compiling.
*****************************************************************************************************************************************
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow3_common_utils.h"
#include "common_utils.h"
#include "quad_delayed_start_common_utils.h"

#include "v2d_flow3_tx.map.h"
#include "v2d_flow3_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NSIP_1_EXP_VALUE 0
#define NUM_VEX_CORES   2
#define POST_FILTER_COEFF 100
#define TEST_VECTORS    "../../flow3/test_vectors/"
#define RCS_HANDSHAKE_VALUE 0xC000C0C0
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

// used for handshaing between HOST and RCS
int g_rsm_buffer[] = {0x23FFEC};

// may change once new functions are added, check .map file
int g_dcode_buffer[] = {0xE4030};

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/* The value should be VEX_MAX_BUF/g_vectors_per_block[drf_clk][pdpd_rate] in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {32, 16, 8, 4, 2},
    {21, 10, 5, 2, 1}
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
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow3_rx_consumer_sm_gate), \
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
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, \
        NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, "HBI_1_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow3_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, AV2D_CSR_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last Five entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX from PDPD, TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to P5 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at P5 GSPS
      need to be picked up dynamically for the specific run*/
#if LIVEIQ_SAMPLES
	// setting the capture point to PDPD egress for capturing the output of PDPD
#define PDPD_EGRESS_CAPTURE (0x2)
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT | (PDPD_EGRESS_CAPTURE << AV2D_CSR_PIF_CTRL_PD_CAP_MEM_SEL_BF_OFF), \
		        AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},

#else 
	// setting the capture point to PDPD ingress for capturing the x data    
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT | (0 << AV2D_CSR_PIF_CTRL_PD_CAP_MEM_SEL_BF_OFF), \
        AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
#endif //LIVEIQ_SAMPLES
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
int flow3_configure_pdpd(int, int, int);
int configure_v2d_host(int *, int, int, int, int, int);
int ref_output_read(unsigned int *host_ref_data, int num_vectors, int filter_mode, int test_config);
#if LIVEIQ_SAMPLES
int read_liveIQ_params(v2d_liveIQ_param_t * v2d_liveIQ_param ,pdpd_rate_t  pdpd_out_rate);
int vector_read_dec_u32(
    FILE *fp,   // Vector Input file data type
    int *dPtr,  // Pointer to output array
    int num) ;   // Number of elements
#endif //LIVEIQ_SAMPLES

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
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
    LOG_DEBUG("Buffer: 0x%x", v2d_buffer_b);

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
    LOG_INFO("cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    LOG_INFO("strm2cio configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow3_rx_consumer_sm_gate, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
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
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow3_rx_vbuffer_out), g_cm_0_config_tbl[i].mask, \
                    g_cm_0_config_tbl[i].name))
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
    LOG_INFO("CM configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_v2d_flow3_config_tbl[i].value, g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_v2d_flow3_config_tbl[i].value | (drf_clock << 7), g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    (g_v2d_flow3_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }

    if (FILTER_MODE == post_filter_mode)
    {
        if (rv = pdpd_post_c_reg_config(v2d_num, apb_num, POST_FILTER_COEFF))
        {
            LOG_ERROR("pdpd post c reg config failed");
            return rv;
        }
    }

    rv = flow3_configure_pdpd(v2d_num, apb_num, test_config);
    LOG_INFO("V2D pdpd configuration completed");

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
    LOG_INFO("V2D configuration completed");

    return rv;
}

/**
 * @brief           Function to read the ref vectors to be provided to
 *                  VEX Rx cores.
 * @param [in]      pointers to rx buffer, num_vectors, filter_mode and test_config
 * @return          status value
 */
int ref_output_read(unsigned int *host_ref_data, int num_vectors, int filter_mode, int test_config)
{
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;
    pdpd_rate_t pdpd_out_rate;

    pdpd_out_rate = g_test_config_tbl[test_config][1];

    sprintf(tref_file, "%s%s", TEST_VECTORS,ref_file[filter_mode][test_config]);

    LOG_INFO("output file : %s", tref_file);
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        LOG_ERROR("Not able to open the output file");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_data,
                num_vectors * NUM_OF_ELEMENTS_PER_VEC) < \
                (num_vectors * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_ERROR("Insufficient Output REF data");
        return -1;
    }

    fclose(fp_ref_output);
    return 0;
}

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0,
        post_filter_mode = 0, delay_value = 0, capture_delay_value = 0;
    uint32_t capture_blocks = 0, blocks_per_1mb = 0, cycles_per_block = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    int dmem_offset = DMEM_OFFSET;

    int offset_val[] = {HIVE_ADDR_v2d_flow3_tx_g_scalar_val, HIVE_ADDR_v2d_flow3_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow3_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow3_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow3_tx_g_initial_block_size, HIVE_ADDR_v2d_flow3_tx_g_host_cycle_count};
#if LIVEIQ_SAMPLES
   unsigned int val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
#else 
    unsigned int val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
#endif   //LIVEIQ_SAMPLES
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow3_rx_g_scalar_val, HIVE_ADDR_v2d_flow3_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow3_rx_g_num_blocks, HIVE_ADDR_v2d_flow3_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow3_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
    int fill_level_value[MAX_NUM_STREAMS] = {0};
    int watermark_buf[MAX_NUM_STREAMS] = {0};
    v2d_shdw_live_reg_check_t reg_check;

#if RCS_TRIGGER
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    // corresponds to v2d_num, apb_num, tx_vex_num, rx_vex_num, drf_clock, delay value, capture delay value and num_blocks to capture
    int rcs_host_param[8] = {0};
#endif

    init(); // Initializing the srp

    /*This is specific to FPGA*/
    follower_bfn_wa_fpga();

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    test_config = argv[5];
    post_filter_mode = argv[6];
    delay_value = (int) argv[7];
    capture_delay_value = (int) argv[8];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
#if CAPTURE_DURATION
    capture_blocks = (int) argv[9];
#else
    capture_blocks = (FLITS_PER_1MB / VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]));
#endif

    LOG_INFO("argv[0] : %d = tx_vex0", vex_num_param[0]);
    LOG_INFO("argv[1] : %d = rx_vex", vex_num_param[1]);
    LOG_INFO("argv[2] : %d = v2d_num", v2d_num);
    LOG_INFO("argv[3] : %d = apb_num", apb_num);
    LOG_INFO("argv[4] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    LOG_INFO("argv[5] : %d = test_config", test_config);
    LOG_INFO("argv[6] : %d = post_filter_mode %s", post_filter_mode, post_filter_mode_str[post_filter_mode]);
    LOG_INFO("argv[7] : %d = delay_value", delay_value);
    LOG_INFO("argv[8] : %d = capture_delay_value", capture_delay_value);
#if CAPTURE_DURATION
    LOG_INFO("argv[9] : %d = capture_blocks", capture_blocks);
#endif
    LOG_INFO("IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);
#if LIVEIQ_SAMPLES
	//read matlab TVs and parameters
	// define th structure with the params
	//v2d_live_IQ_param_t v2d_live_IQ_param;  global def, in common_utils.h

	if (rv = read_liveIQ_params( &v2d_liveIQ_param , pdpd_out_rate )){

		LOG_ERROR("LIVEIQ_SAMPLES:Reading LIVEIQ from files failed");
	}
	// modify the number of terms for 4gsps and 8 gsps

	if (g_test_config_tbl[test_config][0]== 3){  //4gsps
		
		v2d_liveIQ_param.num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS_4GSPS;
		v2d_liveIQ_param.num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS_4GSPS;
		
	} else if (g_test_config_tbl[test_config][0]== 4){  //8gsps
		
		v2d_liveIQ_param.num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS_8GSPS;
		v2d_liveIQ_param.num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS_8GSPS;		
	}
	
   printf("LIVEIQ_SAMPLES:num_gmp_termsblock =%d num_ddr_terms = %d\n", v2d_liveIQ_param.num_gmp_terms,v2d_liveIQ_param.num_ddr_terms); 
#endif //LIVEIQ_SAMPLES           
            

    cycles_per_block = (drf_clock) ? CYCLES_PER_BLOCK_1P5G : CYCLES_PER_BLOCK_983M;

#if CAPTURE_DURATION
    blocks_per_1mb = (FLITS_PER_1MB / VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]));
    if (capture_blocks > blocks_per_1mb)
    {
        LOG_WARNING("provided block number exceedes the blocks_per_1mb for the given data rate \
                     new value for capture_blocks: %d", blocks_per_1mb);
        capture_blocks = blocks_per_1mb;
    }

#endif

    /*enabling the V2D clock for the given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        LOG_ERROR("v2d_clk_enable failed");
        return rv;
    }

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    //This value should be numberof blocks that were configured in the VEX memory to hold
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    // Tx VEX needs to send the data in accordance to the pdpd_out_rate
    // one block extra needs to be send to avoid the underrun
    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
#if LIVEIQ_SAMPLES
	/* number of blocks to be TXed by the VEX_TX core */
    val_kargs[3] = (VMEM_SIZE_SAMPLES/32)/g_vectors_per_block[drf_clock][pdpd_out_rate];
	printf("LIVEIQ_SAMPLES: numTX block =%d vectors per block = %d\n", val_kargs[3], val_kargs[1]);    
#else
    val_kargs[3] = vex_rx_val_kargs[2] + 1;
#endif 
    val_kargs[4] = g_initial_block_size;

#if VEX_1P5G
    if (CLOCK_1P5G == drf_clock)
    {
#if LIVEIQ_SAMPLES
		 LOG_ERROR("LIVEIQ_SAMPLES: This feature runs for 983Hz clock only and NOT for 1.5GHz clock.. ");
#endif 	
        val_kargs[5] = CYCLES_PER_BLOCK_1P5G - 1;
    }
#endif

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config, post_filter_mode))
    {
        LOG_ERROR("Host Configuration failed");
        return rv;
    }

    /*Perform the FB_MEM configuration for X Capture*/
    if (mem_fb_x_capture_configuration(SINGLE_CAPTURE_MODE, 0x3FFF, v2d_num, apb_num))
    {
        LOG_ERROR("MEM_FB configuration failed");
    }

#if CAPTURE_DURATION
    /*Prefill the MEM_FB with known pattern*/
    fill_mem_fb(v2d_num, MEM_FB_INIT_VALUE);
#endif

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        LOG_ERROR("reset_abc failed");
        return rv;
    }

#if RCS_TRIGGER
    int rd_wr_value[32] = {0}, capture_cycles = 0;

    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];

    rcs_config(&rcs_params);

    rcs_host_param[0] = v2d_num;
    rcs_host_param[1] = apb_num;
    rcs_host_param[2] = vex_num_param[0];
    rcs_host_param[3] = vex_num_param[1];
    rcs_host_param[4] = drf_clock;
    rcs_host_param[5] = delay_value;
    rcs_host_param[6] = capture_delay_value + CAPTURE_DELAY_DELTA_VALUE;
#if CAPTURE_DURATION
    capture_cycles = capture_blocks * cycles_per_block;

    rcs_host_param[7] = capture_cycles;
#endif

    LOG_INFO("loaded the elf:%s", rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file);

    //clear the dram
    memset(rd_wr_value, 0, sizeof(rd_wr_value));
    write_mem_18a(g_dcode_buffer[0], 32, rd_wr_value, "DCODE_BUFFER");
    write_mem_18a(g_rsm_buffer[0], 1, rd_wr_value, "DCODE_BUFFER");

    /*Load the parameters to RCS RSM memory*/
    write_mem_18a(RSM_MEM_OFFSET, ARRAY_SIZE(rcs_host_param), rcs_host_param, "RCS_HOST_PARAM");
#endif

    /* Input Vector Generation*/
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_in_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)));
        }
    }

    /* Reading the REF pattern*/
    if (rv = ref_output_read(host_ref_data, VEX_MAX_BUF_SIZE, post_filter_mode, test_config))
    {
        return rv;
    }

    /*Clearing the VEX VMEM and DMEM for both Tx and Rx vex cores*/
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            LOG_ERROR("vex_mem_clear failed for vex:%d", vex_num_param[lc]);
            return rv;
        }
    }

    LOG_INFO("start vex program load");
    if ((rv = vex_loader(vex_num_param[0], "../vex_fw/sim_m64/v2d_flow3_tx.fw")))
        return rv;

    if ((rv = vex_loader(vex_num_param[1], "../vex_fw/sim_m64/v2d_flow3_rx.fw")))
        return rv;
    LOG_INFO("vex program load - done");

    /* Loading the host parameters to VEX  Tx core*/
    if (load_vex_param(vex_num_param[0]/*vex_core*/, ARRAY_SIZE(offset_val)/*size of array*/, offset_val, val_kargs))
    {
        LOG_ERROR("Tx vex param loading failed");
    }

    /* Loading the host parameters to VEX  Rx core*/
    if (load_vex_param(vex_num_param[1]/*vex_core*/, ARRAY_SIZE(vex_rx_offset_val), vex_rx_offset_val, vex_rx_val_kargs))
    {
        LOG_ERROR("Rx vex param loading failed");
    }
#if LIVEIQ_SAMPLES
	/* load the whole of 16K samples of VEMEM with input */

	int liveIQ_input[VMEM_SIZE_SAMPLES] ;
	int liveIQ_output[VMEM_SIZE_SAMPLES] ;
	int actual_output[VMEM_SIZE_SAMPLES] ;
	int num_test_pts;

	FILE *fp_liveIQ = NULL;

	
	num_test_pts = LIVE_IQ_NTESTPTS;
	if (LIVE_IQ_NTESTPTS>VMEM_SIZE_SAMPLES){
		num_test_pts = VMEM_SIZE_SAMPLES;
	}
	fp_liveIQ = fopen("liveIQ_ref_in_IQ.txt","w");		
	//for (i=0;i<num_test_pts;i++){
	for (i=0;i<VMEM_SIZE_SAMPLES;i++){
			liveIQ_input[i] =  ( ((v2d_liveIQ_param.data_in_i[i])&0xFFFF)<<16  ) | (v2d_liveIQ_param.data_in_q[i] & 0xFFFF) ;
			//liveIQ_input[i] =  (( i & 0xFFFF)<<16  ) | (i & 0xFFFF) ;

			fprintf(fp_liveIQ, "0x%x\n", liveIQ_input[i]);

	}
	fclose(fp_liveIQ);
	
	fp_liveIQ = fopen("liveIQ_ref_out_IQ.txt","w");		
	for (i=0;i<num_test_pts;i++){
			liveIQ_output[i] =  ( ((v2d_liveIQ_param.y_out_i[i])&0xFFFF)<<16  ) | (v2d_liveIQ_param.y_out_q[i] & 0xFFFF) ;
			 fprintf(fp_liveIQ, "0x%x\n", liveIQ_output[i]);
	}
	fclose(fp_liveIQ);
	
    /* Loading the input vector for Tx vex core*/


    //write_mem_18a((VEX_VMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow3_tx_vbuffer),
    write_mem_18a((VEX_VMEM(vex_num_param[0]) ),
                  //(val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC)/*size*/,
                  VMEM_SIZE_SAMPLES, //enire VMEM i.e 16K samples loaded
                  &liveIQ_input[0],
                  "LIVEIQ_SAMPLES_TX_VEX_VMEM");

#else

    /* Loading the input vector for Tx vex core*/
    write_mem_18a((VEX_VMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow3_tx_vbuffer),
                  (val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC)/*size*/,
                  val_inp[0],
                  "TX_VEX_VMEM");

    /* Loading the Reference vectors to Rx vex core for the comparison*/
     write_mem_18a((VEX_VMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow3_rx_vbuffer),
                   (VEX_MAX_BUF_SIZE * NUM_OF_ELEMENTS_PER_VEC),
                   host_ref_data,
                   "RX_VEX_VMEM");
#endif //LIVEIQ_SAMPLES

#if RCS_TRIGGER
    /*start RCS core0
     *RCS core will start both Rx and Tx cores respectively and after the program the QUAD BFN with the delay value
     *passed as an argument.*/
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");

    /* Wait for RCS to complete it's execution*/
    if (rv = poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_HANDSHAKE_VALUE))
    {
        LOG_ERROR("poll rcs failed");
        return rv;
    }

    /*Checking BFN sync between QUAD and RCS*/
    if (rv = quad_v2d_sync_check())
    {
        if ((ABC_18A_0P8_0_4 == g_abc_build_version) || (ABC_18A_0P8_0_3 == g_abc_build_version))
        {
            LOG_WARNING("BFN's of V2D in QUAD are not in sync");
        }
        else
        {
            LOG_ERROR("BFN's of V2D in QUAD are not in sync");
            return rv;
        }
    }
#endif
#if !LIVEIQ_SAMPLES
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
    reg_check.gmp_shift_value = FLOW3_GMP_SHIFT_VALUE;
    reg_check.ddr_shift_value = FLOW3_DDR_SHIFT_VALUE;

    if (rv = gmp_ddr_shdw_live_reg_check(&reg_check))
    {
        LOG_ERROR("SHDW to LIVE transition failied\n");
        return 1;
    }
    else
    {
        LOG_INFO("SHDW to LIVE tranition passed\n");
    }
#endif
#endif //!LIVEIQ_SAMPLES

    loop_wait_count = 0;
    usleep(10000);

    /*Wait till required number of flits reached the H2B interface*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_CNT_OFFSET, "H2B_FLIT_COUNT")) <
            (VEC2FLIT(VEX_MAX_BUF_SIZE)))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            LOG_WARNING("Breaking the loop while H2B_FLIT_CNT0x%x is not the required number of flits\n", h2b_flit_count);
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
        host_vec_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow3_rx_g_count1, "vec_processed");

        if (loop_wait_count >= 30)
        {
            LOG_ERROR("VEX core didn't processed enough vectors0x%x\n", host_vec_processed);
            rv = 1;
            return rv;
        }
        loop_wait_count ++;
        usleep(10000);
    }
#if !LIVEIQ_SAMPLES
    /*There are no REF vectors for 1.5G clock for this specific input pattern*/
    if (CLOCK_983M == drf_clock)
    {
        /* Reading the results from Rx VEX*/
        host_result = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow3_rx_g_compare_result, "compare_result");
        host_blocks_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow3_rx_g_add_val_out, "blocks_processed");

        printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
        printf ("processed blocks 0x%x\n", host_blocks_processed);

        if (0xFFFFFFFF != host_result)
        {
            LOG_ERROR(" Received output didn't match with Reference output TV\n");
            test_status = 1;
        }
        else
        {
            printf("Received output matches with Reference output\n");
        }
    }
#endif //!LIVEIQ_SAMPLES

#if LIVEIQ_SAMPLES
    /* As the TX VEX cores only send 16K samples which are the reference input forLIVEIQ_SAMPLES  PD_MAIN_UNDER_RUN(bit18)) is expected be set after this*/
#define PD_MAIN_UNDERRUN   (0x1<<18)
    if (rv = interrupt_status_check(v2d_num, apb_num, PD_MAIN_UNDERRUN/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        LOG_ERROR("interrupt check failed\n");
        test_status |= 1;
    }
#else
    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        LOG_ERROR("interrupt check failed\n");
        test_status |= 1;
    }
#endif //LIVEIQ_SAMPLES
    /* Get the watermark high , low values for V2D Buffers*/
    if (rv = get_tx_pdpd_wm_hilo(v2d_num, apb_num, 1/*Number of streams*/, watermark_buf))
    {
        LOG_ERROR("get_tx_pdpd_wm_hilo failed\n");
        test_status |= 1;
    }
    else
    {
        printf("HOST: Low watermark value : 0x%x", watermark_buf[0] & 0xFFF);
        printf("HOST: High watermark value : 0x%x", (watermark_buf[0] >> 16) & 0xFFF);
    }

    loop_wait_count = 0;
    h2b_flit_count = 0;

    /*Wait till required number of flits reached the H2B interface
     * Checking the H2B registers because the B2H count might not include the delay*/
    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_CNT_OFFSET, "B2H_FLIT_COUNT")) <
            ((capture_delay_value / cycles_per_block) + capture_blocks)* VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate]))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            LOG_WARNING("Breaking the loop while H2B_FLIT_CNT 0x%x is not the required number of flits\n", h2b_flit_count);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /*this value shouldn't be modified as this is linked to VEX code and if modified VEX code needs to be modified
     * accordinlgy and needs to be recompiled*/
    host_flag = VEX_STOP_TRANSMIT_INDICATION;

    /*Signal from host to stop continuous flow on B Tx Vex Core , which in turn will signal the C Tx Vex core to stop continuous transmission*/
    if (rv = write_reg_18a(VEX_DMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow3_tx_g_host_indicator,
                host_flag, 0xFFFFFFFF, "HOST_INDICATION"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }
#if LIVEIQ_SAMPLES
#define NUM_SAMPLES_PER_VECTOR 32

	FILE *fp_i = NULL ,*fp_q = NULL;
	int32_t sample_16= 0;
	int blocks_to_read = 0, out_rate = 0;
	
	
	num_test_pts = LIVE_IQ_NTESTPTS;
	if (LIVE_IQ_NTESTPTS>VMEM_SIZE_SAMPLES){
		num_test_pts = VMEM_SIZE_SAMPLES;
	}
	out_rate = g_test_config_tbl[test_config][1];

#if LIVEIQ_PASSTHRU_TEST
	fp_i = fopen("liveIQ_FP_passthru_out_i.txt","w");	
	fp_q = fopen("liveIQ_FP_passthru_out_q.txt","w");
#else

    if (out_rate == PDPD_RATE_IQ_P5) {
		fp_i = fopen("liveIQ_FP_LUT48_64_i_p5gsps.txt","w");	
		fp_q = fopen("liveIQ_FP_LUT48_64_q_p5gsps.txt","w");
	} else if(out_rate == PDPD_RATE_IQ_1){
		fp_i = fopen("liveIQ_FP_LUT48_64_i_1gsps.txt","w");	
		fp_q = fopen("liveIQ_FP_LUT48_64_q_1gsps.txt","w");
	} else if(out_rate == PDPD_RATE_IQ_2){
		fp_i = fopen("liveIQ_FP_LUT48_64_i_2gsps.txt","w");	
		fp_q = fopen("liveIQ_FP_LUT48_64_q_2gsps.txt","w");
	} else if(out_rate == PDPD_RATE_IQ_4){
		fp_i = fopen("liveIQ_FP_LUT24_64_i_4gsps.txt","w");	
		fp_q = fopen("liveIQ_FP_LUT24_64_q_4gsps.txt","w");
	} else if(out_rate == PDPD_RATE_IQ_8){
		fp_i = fopen("liveIQ_FP_LUT12_64_i_8gsps.txt","w");	
		fp_q = fopen("liveIQ_FP_LUT12_64_q_8gsps.txt","w");
	}
#endif //LIVEIQ_PASSTHRU_TEST
	blocks_to_read = (VMEM_SIZE_SAMPLES/32)/g_vectors_per_block[drf_clock][pdpd_out_rate];
	printf("LIVEIQ_SAMPLES:blocks_to_read=%d num vectors per block=%d\n", blocks_to_read,val_kargs[1]);
    rv = liveIQ_pdpd_egress_cap_mem_read(v2d_num, &liveIQ_output[0], &actual_output[0], val_kargs[1] /* num_vectors_per_block*/,  drf_clock, blocks_to_read /* blocks_to_read*/);

	//for (i=0;i<num_test_pts;i++){
	for (i=0;i<400;i++){
		if (liveIQ_output[i] != actual_output[i]){
			printf("MISMATCH Ref_y_out_IQ[%d]=0x%x   0x%x actual_output[%d] \n", i,liveIQ_output[i],actual_output[i],i);
			}else{
				printf("MATCHED Ref_y_out_IQ[%d]=0x%x   0x%x actual_output[%d] \n", i,liveIQ_output[i],actual_output[i],i);
			}
	}
	//printing the output from FPGA
	for (i=0;i<num_test_pts;i++){

			//Extracting the I value
			sample_16 = (actual_output[i])>>16 ;
			 fprintf(fp_i, "%d\n", sample_16);
			//Extracting the Q value			 
			sample_16 = ((actual_output[i])<<16 )>>16;			 
			 fprintf(fp_q, "%d\n", sample_16);	
	}
    fclose (fp_i);
    fclose (fp_q);		
    
	/*skipping first 200 samples from comaprison, MATLAB is different from that of actual RTL, which is know issue. 
	The RTL ouptput is correct, with which the FPGA out put is matching in earlier investigations, as also discussed with the designer ( Doug)
	once the issue is fixed in MATLAB dn sim environemtn, this can be fixed. */
#define NUM_SAMPLES_SKIPPED (200)	
	for (i=NUM_SAMPLES_SKIPPED;i<num_test_pts;i++){
			//printing the output from FPGA
			//Extracting the I value
			sample_16 = (actual_output[i])>>16 ;
			if ( sample_16 != ( ((v2d_liveIQ_param.y_out_i[i])  )) ) {
				        LOG_ERROR("LIVEIQ_SAMPLES: Output MISMATCH ERROR  for I value at sample index +%d  EXITING....\n", i);
				        rv = -1;
				        return;
			}
			
			//Extracting the Q value			 
			sample_16 = ((actual_output[i])<<16 )>>16;			 
			if ( sample_16 != (v2d_liveIQ_param.y_out_q[i] ) ) {
				        LOG_ERROR("LIVEIQ_SAMPLES: Output MISMATCH ERROR at sample doe Q value index +%d  EXITING....\n", i);
				        rv = -1;
				        return;
			}			 
	 		 
	}	
	 

#else
    /*Capture Memory comparison*/
    if (rv = pdpd_ingress_cap_mem_compare(v2d_num, val_kargs[0]/*add_factor*/, val_kargs[1]/*num_of_vectors*/, capture_delay_value,
                drf_clock, capture_blocks))
    {
        LOG_ERROR("FB_MEM comparison failed");
    }
    else
    {
        LOG_INFO("MEM_FB comparison passed");
    }
#endif //LIVEIQ_SAMPLES
#if CAPTURE_DURATION
    if (capture_blocks < blocks_per_1mb)
    {
        if (rv = fb_mem_compare_extra_block(v2d_num, val_kargs[1], MEM_FB_INIT_VALUE, capture_blocks))
        {
            LOG_ERROR("capture didn't end properly");
        }
    }
#endif

    /*As VEX cores stopped transmitting the underrun interrupt should be set now*/
    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        LOG_ERROR("Interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed\n");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s, delay_value: %d, capture_delay_value: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode],
                delay_value, capture_delay_value);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s, delay_value: %d, capture_delay_value: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode],
                delay_value, capture_delay_value);
        rv = 1;
    }

    return rv;
}
#if LIVEIQ_SAMPLES

int read_liveIQ_params(v2d_liveIQ_param_t * v2d_liveIQ_param, pdpd_rate_t  out_rate)
{
/* the eblow apramters are used same as that of MATLAB*/

#define LIVEIQ_PASSTHRU_DELAY   64
#define LIVE_IQ_PASSTHRU_COEFT_I  7977
#define LIVE_IQ_PASSTHRU_COEFT_Q  -23	
    //LUT0, SHIFT=0;
	
	FILE *fp_liveIQ = NULL, *fp_i= NULL, *fp_q = NULL;

	int i,j;
	
	v2d_liveIQ_param->passthru_dly = LIVEIQ_PASSTHRU_DELAY;
	v2d_liveIQ_param->passthru_coeft_i = LIVE_IQ_PASSTHRU_COEFT_I;
	v2d_liveIQ_param->passthru_coeft_q = LIVE_IQ_PASSTHRU_COEFT_Q;

	v2d_liveIQ_param->num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS;
	v2d_liveIQ_param->num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS;
	
	//term types
	fp_liveIQ = fopen("matlab/termType.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/ltermType.txt");
        return -1;
    }
    int test_array[48];
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->term_types[0],
                48)<48)
    {
        printf("ERROR: Insufficient read from matlab/termType.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
     printf("matlab/termType\n");
     for (i=0; i<48; i++){
		//printf("0x%x\n",v2d_liveIQ_param->term_types[i]);
		 }
	
	
	//q delay
	fp_liveIQ = fopen("matlab/q_dly.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/q_dly.txt");
        return -1;
    }

 
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->q_delay[0],
                48) <48 )
    {
        printf("ERROR: Insufficient read from matlab/q_dly.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
     for (i=0; i<48; i++){
		 //printf("0x%x\n",v2d_liveIQ_param->q_delay[i]);
		 }
	printf("matlab/q_dly*****\n");
	     
	     
	     
	//m delay
    fp_liveIQ = fopen("matlab/m_dly.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/m_dly.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->m_delay[0],
                48) < 48)
    {
        printf("ERROR: Insufficient read from matlab/m_dly.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
	printf("matlab/m_dly*****\n");     
     for (i=0; i<48; i++){
		 //printf("0x%x\n",v2d_liveIQ_param->m_delay[i]);
		 }
		 

	//lut_c_i[32+16][65]  lut_c_q[32+16][65]
	/* the duplciation of coefficients from the available 48 LUTS, for the 4gsps nd 8gsps is done insdei the  code, 
    in a similar way that is done in matlba  code. hence no need to read rate specific LUT C values */
	fp_i = fopen("matlab/liveIQ_lut_c_i.txt","r");	
	fp_q = fopen("matlab/liveIQ_lut_c_q.txt","r");		 


    if (NULL == fp_i)
    {
        LOG_ERROR("Not able to open the matlab/liveIQ_lut_c_i.txt for the required rate\n");
        return -1;
    }
    
    if (NULL == fp_q)
    {
        LOG_ERROR("Not able to open the matlab/liveIQ_lut_c_q.txt for the required rate\n");
        return -1;
    }    
    
    
    if (vector_read_dec_u32(fp_i,
                &v2d_liveIQ_param->lut_c_i[0][0],
                48*65) < (48*65))
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_lut_c_i.txt");
        return -1;
    }

     /* print the params */
	printf("matlab/liveIQ_lut_c_i*****\n");
	
	/* for testing only */      
    //for (i=v2d_liveIQ_param->num_gmp_terms; i<48; i++){
     for (i=1; i<48; i++){
		 for (j=0;j<65;j++){
			 //making all values zero for the not enabled GMP terms( logic will works for the first few GMP terms))
			 //v2d_liveIQ_param->lut_c_i[i][j]=0;
			//printf("0x%x\n",v2d_liveIQ_param->lut_c_i[i][j]);
			}
		 }	
    // hard code the C value , for testing only
     for (i=0; i<1; i++){
		 //making all values zero for the not enabled GMP terms( logic will works for the first few GMP terms))
		 for (j=0;j<65;j++){
			//printf("0x%x\n",v2d_liveIQ_param->lut_c_q[i][j]);
			//v2d_liveIQ_param->lut_c_i[i][j] = GMP_C_I_VALUE -1 ;   //(1 << 11)
			}
		 }		 

    if (vector_read_dec_u32(fp_q,
                &v2d_liveIQ_param->lut_c_q[0][0],
                48*65)< (48*65))
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_lut_c_q.txt");
        return -1;
    }

     /* print the params */
	printf("matlab/liveIQ_lut_c_q*****\n");  

	/* for testing only */ 	     
    //for (i=v2d_liveIQ_param->num_gmp_terms; i<48; i++){
    for (i=1; i<48; i++){
		 //making all values zero for the not enabled GMP terms( logic will works for the first few GMP terms))
		 for (j=0;j<65;j++){
			//printf("0x%x\n",v2d_liveIQ_param->lut_c_q[i][j]);
			//v2d_liveIQ_param->lut_c_q[i][j] = 0;
			}
		 }	

 	// hard code the C value for testing only

    for (i=0; i<1; i++){
		 //making all values zero for the not enabled GMP terms( logic will works for the first few GMP terms))
		 for (j=0;j<65;j++){
			//printf("0x%x\n",v2d_liveIQ_param->lut_c_q[i][j]);
			//v2d_liveIQ_param->lut_c_q[i][j] = GMP_C_I_VALUE -1  ; //GMP_C_Q_VALUE;
			}
		 }	
		 
    fclose (fp_i);
    fclose (fp_q);
    		 
 	//lut_s 	
    fp_liveIQ = fopen("matlab/liveIQ_lut_s.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the liveIQ_lut_s.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->lut_s[0],
                48)< 48)
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_lut_s.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
	printf("matlab/liveIQ_lut_s*****\n"); 
   
    for (i=0; i<10; i++){

			//printf("0x%x\n",v2d_liveIQ_param->lut_s[i]);

		}	 	
 	 	
	//data_in_i
    fp_liveIQ = fopen("matlab/liveIQ_data_in_i.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/liveIQ_data_in_i.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->data_in_i[0],
                LIVE_IQ_NTESTPTS ) <LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_data_in_i.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
	printf("matlab/liveIQ_data_in_i*****\n");       
     for (i=0; i<25; i++){

			//printf("0x%x\n",v2d_liveIQ_param->data_in_i[i]);

		 }	
	//data_in_q
    fp_liveIQ = fopen("matlab/liveIQ_data_in_q.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/liveIQ_data_in_q.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->data_in_q[0],
                LIVE_IQ_NTESTPTS ) < LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_data_in_q.txt");
        return -1;
    }
    fclose (fp_liveIQ);
	printf("matlab/liveIQ_data_in_q*****\n");     
     /* print the params */
     for (i=0; i<25; i++){

			//printf("0x%x\n",v2d_liveIQ_param->data_in_q[i]);

		 }
#if LIVEIQ_PASSTHRU_TEST
//#define LIVE_IQ_PASSTHRU_COEFT_I  7977
//#define LIVE_IQ_PASSTHRU_COEFT_Q  -23		
	v2d_liveIQ_param->passthru_dly = 63;// LIVEIQ_PASSTHRU_DELAY;
	v2d_liveIQ_param->passthru_coeft_i = 7977;
	v2d_liveIQ_param->passthru_coeft_q = -23	;
    // set the GMP and DDR terms to zero
	v2d_liveIQ_param->num_gmp_terms = 0 ; //V2D_PDPD_MAX_GMP_TERMS;
	v2d_liveIQ_param->num_ddr_terms =  0 ;//V2D_PDPD_MAX_DDR_TERMS;
	//y_out_i
    fp_liveIQ = fopen("matlab/liveIQ_ref_output_passthru_i.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the matlab/liveIQ_ref_output_passthru_i.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->y_out_i[0],
                LIVE_IQ_NTESTPTS ) < LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from matlab/liveIQ_ref_output_passthru_i.txt");
        return -1;
    }
    fclose (fp_liveIQ);
    /* print the params */
	printf("matlab/liveIQ_ref_output_passthru_i*****\n");     
     
     for (i=0; i<25; i++){

			//printf("0x%x\n",v2d_liveIQ_param->y_out_i[i]);

		 }	
	//y_out_q
    fp_liveIQ = fopen("liveIQ_ref_output_passthru_q.txt","r");
    if (NULL == fp_liveIQ)
    {
        LOG_ERROR("Not able to open the liveIQ_ref_output_passthru_q.txt");
        return -1;
    }
    
    
    if (vector_read_dec_u32(fp_liveIQ,
                &v2d_liveIQ_param->y_out_q[0],
                LIVE_IQ_NTESTPTS ) <LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from liveIQ_ref_output_passthru_q.txt");
        return -1;
    }
    fclose (fp_liveIQ);
     /* print the params */
	printf("liveIQ_ref_output_passthru_q*****\n");  
	     
     for (i=0; i<250; i++){

			printf("READING 0x%x\n",v2d_liveIQ_param->y_out_q[i]);

		 }
#else		 
	//y_out_i ,y_out_q
	
   if (out_rate == PDPD_RATE_IQ_P5) {
		fp_i = fopen("matlab/liveIQ_ref_LUTall_64_i.txt","r");	
		fp_q = fopen("matlab/liveIQ_ref_LUTall_64_q.txt","r");
	} else if(out_rate == PDPD_RATE_IQ_1){
		fp_i = fopen("matlab/liveIQ_ref_LUTall_64_i.txt","r");	
		fp_q = fopen("matlab/liveIQ_ref_LUTall_64_q.txt","r");
	} else if(out_rate == PDPD_RATE_IQ_2){
		fp_i = fopen("matlab/liveIQ_ref_LUTall_64_i.txt","r");	
		fp_q = fopen("matlab/liveIQ_ref_LUTall_64_q.txt","r");
	} else if(out_rate == PDPD_RATE_IQ_4){
		fp_i = fopen("matlab/liveIQ_ref_LUTall_64_i_4gsps.txt","r");	
		fp_q = fopen("matlab/liveIQ_ref_LUTall_64_q_4gsps.txt","r");
	} else if(out_rate == PDPD_RATE_IQ_8){
		fp_i = fopen("matlab/liveIQ_ref_LUT12_64_i_8gsps.txt","r");	
		fp_q = fopen("matlab/liveIQ_ref_LUT12_64_q_8gsps.txt","r");
	}	
	
    if (NULL == fp_i)
    {
        LOG_ERROR("Not able to open the Reference output I file for teh required rate\n");
        return -1;
    }
 
     if (NULL == fp_q)
    {
        LOG_ERROR("Not able to open the Reference output Q file for teh required rate\n");
        return -1;
    }   
    

    if (vector_read_dec_u32(fp_i,
                &v2d_liveIQ_param->y_out_i[0],
                LIVE_IQ_NTESTPTS ) < LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from liveIQ_ref_output_i.txt");
        return -1;
    }

     /* print the params */
	printf("liveIQ_ref_output_i*****\n");     
     
    for (i=0; i<25; i++){

			//printf("0x%x\n",v2d_liveIQ_param->y_out_i[i]);

		}	
    if (vector_read_dec_u32(fp_q,
                &v2d_liveIQ_param->y_out_q[0],
                LIVE_IQ_NTESTPTS ) <LIVE_IQ_NTESTPTS)
    {
        printf("ERROR: Insufficient read from liveIQ_ref_output_q.txt");
        return -1;
    }
    //fclose (fp_liveIQ);
    
    fclose (fp_i);
    fclose (fp_q);    
     /* print the params */
	printf("liveIQ_ref_output_q*****\n");       
    for (i=0; i<25; i++){

			//printf("0x%x\n",v2d_liveIQ_param->y_out_q[i]);
		}	
#endif 	//LIVEIQ_PASSTHRU_TEST	 		 		 			 
 			 		 
	}
	
	
	
int vector_read_dec_u32(
    FILE *fp,   // Vector Input file data type
    int *dPtr,  // Pointer to output array
    int num)    // Number of elements
{
    int i, fileEnd;
    int iVal;

    fileEnd = 0;

    for (i=0; i<num; i++)
    {
        fileEnd = fscanf(fp, "%d", &iVal);

        if (fileEnd != 1)
            return(-1);

        *dPtr = iVal;
        dPtr++;
    }
    return(i);
}
#endif  //LIVEIQ_SAMPLES
