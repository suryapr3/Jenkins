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
 * @file    dyn_flow3_mode1_rcs_vex.c
 * @brief   HOST Configuration code for evaluating the PDPD block with GMP and DDR terms enabled along with
 *          enabling the X-Capture at PDPD egress and updating the LUT coeffecients at regular intervals from
 *          the VEX Core via immediate mode.
 * @details 1. Configuration of VEX, V2D's Common Module for sending data from VEX to V2D via B path
               with passthru gain enabled along with GMP and DDR terms and receving it back to other VEX.
            2. Compares the received output with REF output for result evaluation.
            3. Configure the MEM_FB to receive the data from PDPD Egress and do the comparison from HOST
               for 1MB captured data.
   @TC Description:
        1. Tx VEX will be sending the samples continuously to PDPD at required rate until there was an indication from
           HOST to stop the data transfer.
        2. PDPD block was configured with GMP and DDR terms along with passthru gain and with POST FILTER enabled with PASSTHRU mode.
        3. The GMP and DDR terms will be updated by RCS core at the boot time and by ADAPT VEX at regular intervals and the corresponding
           LUT coeffecients will be updated in the VEX VMEM by the HOST.
        4. Host will be waiting on a memory location where RCS core will update an indication to indicate it has transferred the
           first set of LUT's towards PDPD.
        5. The Initial LUT will be transferred from SHADOW to LIVE via immediate transfer mode from RCS and this will be verified by HOST.
        6. Data capture at PDPD Egress was enabled in single shot mode for 256K samples and corresponding MEM_FB configuration
           was done from the HOST.
        8. X-Data capture will be triggered from BFN timed trigger which will be programmed from RCS.
        9. PASS/FAIL is determined by comparing the PDPD egress captured data with the MATLAB generated output date by HOST.
        10. During Comparison HOST will ignore the first block and 10 blocks during every LUT transition.
        11. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ for 983M clock
            0.75IQ 1.5IQ 3IQ and 6IQ except 12IQ for 1.5G clock

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow3_common_utils.h"
#include "common_utils.h"
#include "quad_delayed_start_common_utils.h"
#include "v2d_host_rcs_common_utils.h"

#include "v2d_flow3_tx.map.h"
#include "v2d_adapt_mode1.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NSIP_1_EXP_VALUE 0
#define NUM_VEX_CORES   2
#define POST_FILTER_COEFF 100
#define RCS_HANDSHAKE_VALUE 0xC000C0C0
#define B2H_MAP_VALUE_G_COEFF 0x20000   // in Bytes
#define B2H_MAP_VALUE_PASSTHRU_GAIN 0x24000 // in Bytes
#define CIO2STRM_MEM_MAP  0x10000

#define V2D_PDPD_GMP_TERMS_DYNAMIC          (16)
#define V2D_PDPD_DDR_TERMS_DYNAMIC          (0)

/* 65 I values of LUT will be generated with this value*/
#if 1
/*For boot up set of LUT value*/
#define GMP_C_I_VALUE_0                     (0x83)
/*For second set of LUT value*/
#define GMP_C_I_VALUE_1                     (0x5f)
/*For Third set of LUT value*/
#define GMP_C_I_VALUE_2                     (0x11)
/*For fourth set of LUT value*/
#define GMP_C_I_VALUE_3                     (0x50)
#else
/* This set of coeffecients caused saturation in matlab hence
 * not using*/
#define GMP_C_I_VALUE_0                     (GMP_C_I_VALUE)
/*For second set of LUT value*/
#define GMP_C_I_VALUE_1                     (1 << 10)
/*For Third set of LUT value*/
#define GMP_C_I_VALUE_2                     (1 << 9)
/*For fourth set of LUT value*/
#define GMP_C_I_VALUE_3                     (1 << 8)
#endif

/*There are total 4 LUT updates including Boot LUT update*/
#define MAX_LUT_UPDATES                     (4)

#define RCS_LUT_BUFFER_ADDR                 (0x00210000)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

// used for handshaing between HOST and RCS
int g_rsm_buffer[] = {0x23FFEC};

// may change once new functions are added, check .map file
int g_dcode_buffer[] = {0xE4030};

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/*Due to the number of GMP terms used few output files will be same*/
const char *ref_file[NUM_CONFIG_PDPD] = {
    "ref_output_config0.txt", "ref_output_config0.txt", "ref_output_config0.txt", "ref_output_config0.txt", "ref_output_config4.txt",
    "ref_output_config5.txt", "ref_output_config5.txt", "ref_output_config7.txt", "ref_output_config8.txt", "ref_output_config9.txt",
    "ref_output_config10.txt", "ref_output_config5.txt", "ref_output_config5.txt", "ref_output_config7.txt", "ref_output_config14.txt",
    "ref_output_config15.txt", "ref_output_config16.txt"
};


/* The value should be VEX_MAX_BUF/g_vectors_per_block[drf_clk][pdpd_rate] in pdpd_rate_t enum */
const uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {32, 16, 8, 4, 2},
    {20, 10, 5, 2, 1}
};

// The last two entries order shouldn't be modified
static v2d_flow_tbl_t g_dynamic_cio2strm_config_tbl[] = {
// INT Enable
    {CIO2STRM_OFFSET + CIO2STRM_INT_EN_OFFSET, CIO2STRM_INT_EN_VALUE, \
        CIO2STRM_INT_EN_WR_MASK, "CIO2STRM_INT_ENABLE"},

//VE00 cio2strm
    {CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE,
        CIO2STRM_FIFO_STAT_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, \
        CIO2STRM_WORD_CNT_CTL_WR_MASK, "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the single stream from vex core to CRUX*/
    {CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET, 0x00000003, CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, \
        CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW0"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET, (CIO2STRM_MEM_MAP - 1), \
        CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},

    //MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW1_OFFSET, (CIO2STRM_MEM_MAP), \
        CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW1"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH1_OFFSET, 0x01FFFF, \
        CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH1"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET1_OFFSET, 0x00000000, CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET1"},
    /***********************************************************************************************************************************/
    /*These last 2 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    //STRM_DEST[0] - mapped to V2D_0_Port_0
    {CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET, 0x00000044, CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
    {CIO2STRM_OFFSET + CIO2STRM_STRM_DEST1_OFFSET, 0x00000046, CIO2STRM_STRM_DEST_WR_MASK, \
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

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + 0), \
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
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), (B2H_MAP_VALUE_G_COEFF - 1), NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},
    // This was for GMP DDR Coeff update from VEX in MODE 1 via stream 4
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL4_OFFSET), (0x80000000 | B2H_MAP_VALUE_G_COEFF), \
        NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, "CM_1_B2H_ADDR_MAP_TBL4"},
    // Mask was set for total 256 flits in Bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL4_OFFSET), 0x3FFF, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL4"},
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
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_DEFAULT, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to P5 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at P5 GSPS
      need to be picked up dynamically for the specific run and PDPD Egress capture is enabled*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT | (0x2 << AV2D_CSR_PIF_CTRL_PD_CAP_MEM_SEL_BF_OFF), \
        AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
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
void lut_mem_copy(unsigned int (*dpd_coeff_buffer)[NUM_WORDS_PER_LUT],
                   unsigned int (*dpd_coeff_buffer1)[NUM_WORDS_PER_LUT],
                   unsigned int (*dpd_coeff_buffer2)[NUM_WORDS_PER_LUT],
                   int vex_num,
                   lut_mode_t lut_mode);
int get_gmp_terms(int test_config);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function to get the gmp_terms
 * @param [in]      pdpd_out_rate
 * @return          num_gmp_terms
 */
int get_gmp_terms(int test_config)
{
    int max_gmp_terms = 0, gmp_terms = V2D_PDPD_GMP_TERMS_DYNAMIC;

    max_gmp_terms = g_test_config_tbl[test_config][4];
    if (gmp_terms > max_gmp_terms)
    {
        gmp_terms = max_gmp_terms;
    }

    LOG_INFO("GMP terms configured: 0x%x", gmp_terms);
    return gmp_terms;
}

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock, test_config and post_filter_mode
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config, int post_filter_mode)
{
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0, fill_level_value = 0, tx_stream_cnt_value = 0,
        rx_stream_cnt_value = 0, gmp_terms = V2D_PDPD_GMP_TERMS_DYNAMIC;
    bool us_granularity_required = FALSE;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    gmp_terms = get_gmp_terms(test_config);

#if VEX_1US_WINDOW
    /*To check whether 1us granularity is required or not*/
    us_granularity_required = get_us_granularity_status(drf_clock, test_config);

    if (us_granularity_required)
    {
        /* If 1us granularity is required all the buffer sizes should be doubled*/
        v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (2 * g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
        tx_stream_cnt_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) - 1;
        rx_stream_cnt_value = (2 * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])) - 1;
    }
    else
#endif
    {
        v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
        tx_stream_cnt_value = (VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate])) - 1;
        rx_stream_cnt_value = (VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])) - 1;
    }
    LOG_DEBUG("Buffer: 0x%x", v2d_buffer_b);

    for (i = 0; i < ARRAY_SIZE(g_dynamic_cio2strm_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_dynamic_cio2strm_config_tbl[i].offset, \
                    g_dynamic_cio2strm_config_tbl[i].value, g_dynamic_cio2strm_config_tbl[i].mask, g_dynamic_cio2strm_config_tbl[i].name))
            return rv;
    }
    for (;i < ARRAY_SIZE(g_dynamic_cio2strm_config_tbl) - 1; i++)
    {
        // Corresponds to cio2strm dest id
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_dynamic_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
                g_dynamic_cio2strm_config_tbl[i].mask, g_dynamic_cio2strm_config_tbl[i].name))
            return rv;
    }
    for (;i < ARRAY_SIZE(g_dynamic_cio2strm_config_tbl); i++)
    {
        // Corresponds to cio2strm dest id
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_dynamic_cio2strm_config_tbl[i].offset, vex_num[1], \
                g_dynamic_cio2strm_config_tbl[i].mask, g_dynamic_cio2strm_config_tbl[i].name))
            return rv;
    }

    for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    // Corresponds to cio2strm dest id
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][1], \
            g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
        return rv;

    LOG_INFO("cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
            return rv;
    }
    printf("INFO: strm2cio configuration completed");

    for (i = 0; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | 0x8000), g_cm_0_config_tbl[i].mask, \
                    g_cm_0_config_tbl[i].name))
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
                    (AV2D_CSR_TX_CSR_TX_STRM_CNT_STRM_EN_BF_MSK | tx_stream_cnt_value), g_v2d_flow3_config_tbl[i].mask, \
                    g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    (AV2D_CSR_TX_CSR_TX_STRM_CNT_STRM_EN_BF_MSK | rx_stream_cnt_value), g_v2d_flow3_config_tbl[i].mask, \
                    g_v2d_flow3_config_tbl[i].name))
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

    rv = dynamic_gbuffer_update_configure_pdpd(v2d_num, apb_num, test_config, gmp_terms, V2D_PDPD_DDR_TERMS_DYNAMIC);
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
 * @brief           Function for copying the LUT's to PDPD ADAPT VEX VMEM
 * @param [in]      pointers to the LUT buffers, vex_num and lut_mode
 * @return          status value
 */
void lut_mem_copy(unsigned int (*dpd_coeff_buffer)[NUM_WORDS_PER_LUT],
                   unsigned int (*dpd_coeff_buffer1)[NUM_WORDS_PER_LUT],
                   unsigned int (*dpd_coeff_buffer2)[NUM_WORDS_PER_LUT],
                   int vex_num,
                   lut_mode_t lut_mode)
{

    int i = 0;

    unsigned int *buffer_address[] = {dpd_coeff_buffer[0], dpd_coeff_buffer1[0], dpd_coeff_buffer2[0]};
    unsigned int dpd_passthru_buffer_data[1][NUM_OF_ELEMENTS_PER_VEC] = {0};

    // Passthru coeffecients
    dpd_passthru_buffer_data[0][0] = (PASSTHRU_I_COEFF_UNITY_GAIN) << 16 | PASSTHRU_Q_COEFF_UNITY_GAIN;
    // 65th bit should be set as 1 for imeediate update
    dpd_passthru_buffer_data[0][2] = 0x2;

    /*There are three LUT updates from VEX core
     * Each LUT(including passthru gain) will be of size 242 flits so that the next LUT will always start
     * at 1024 bit boundary which is required by VEX LOAD instruction*/
    for (i = 0; i < (MAX_LUT_UPDATES - 1); i++)
    {
        uint32_t addr = HIVE_ADDR_v2d_adapt_mode1_v_gbuffer + (i * ((g_vectors_g_buf_lut_mode[lut_mode] + 1) * BYTES_PER_VEC));

        /*Loading the DPD Coeff buffer*/
        write_mem_18a(VEX_VMEM(vex_num) + addr,/*local_addr*/
                      (g_vectors_g_buf_lut_mode[lut_mode] * NUM_OF_ELEMENTS_PER_VEC),
                      buffer_address[i],
                      "GBUFFER0_VEX_VMEM");

        /*Loading the PASSTHRU Coeff buffer*/
        write_mem_18a(VEX_VMEM(vex_num) + addr + (g_vectors_g_buf_lut_mode[lut_mode] * BYTES_PER_VEC),/*local_addr*/
                      (NUM_OF_ELEMENTS_PER_VEC),
                      dpd_passthru_buffer_data[0],
                      "PASSTHRU_DATA_0_VEX_VMEM");
    }
}

/**
 * @brief           Main Function
 * @param [in]      argc and pointer to argv
 * @return          status value
 */
int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0,
        post_filter_mode = 0, delay_value = 0, capture_delay_value = 0;
    uint32_t capture_blocks = 0, blocks_per_1mb = 0, cycles_per_block = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    bool us_granularity_required = FALSE;

    int dmem_offset = DMEM_OFFSET;

    int offset_val[] = {HIVE_ADDR_v2d_flow3_tx_g_scalar_val, HIVE_ADDR_v2d_flow3_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow3_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow3_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow3_tx_g_initial_block_size, HIVE_ADDR_v2d_flow3_tx_g_host_cycle_count,
                         HIVE_ADDR_v2d_flow3_tx_g_vex_indication_address};
    unsigned int val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1), 0};

    int guffer_tx_offset_val[] = {HIVE_ADDR_v2d_adapt_mode1_g_vectors_g_buf, HIVE_ADDR_v2d_adapt_mode1_g_dpd_coeff_base,
                                  HIVE_ADDR_v2d_adapt_mode1_g_host_cycle_count, HIVE_ADDR_v2d_adapt_mode1_g_lut_update_block_duration,
                                  HIVE_ADDR_v2d_adapt_mode1_g_max_lut_update};
    int gbuffer_tx_val_args[] = {120, B2H_MAP_VALUE_G_COEFF, (CYCLES_PER_BLOCK_983M - 1), 0, (MAX_LUT_UPDATES - 1)};

    unsigned int val_inp[VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
    int fill_level_value[MAX_NUM_STREAMS] = {0};
    int watermark_buf[MAX_NUM_STREAMS] = {0};
    v2d_shdw_live_reg_check_t reg_check;
    /*Holds the 48 LUT's Data*/
    unsigned int dpd_coeff_buffer[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0};
    unsigned int dpd_coeff_buffer_1[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0};
    unsigned int dpd_coeff_buffer_2[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0};
    unsigned int dpd_coeff_buffer_3[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0};
    lut_mode_t lut_mode = PDPD_LUT_48;
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;

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
    delay_value = (int) argv[6];
    post_filter_mode = (int) argv[7];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];
    /*As the capture is at PDPD EGRESS num_blocks will be depend on pdpd out rate*/
    capture_blocks = (FLITS_PER_1MB / VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate]));

    LOG_INFO("argv[0] : %d = tx_vex0", vex_num_param[0]);
    LOG_INFO("argv[1] : %d = g_coeff_vex", vex_num_param[1]);
    LOG_INFO("argv[2] : %d = v2d_num", v2d_num);
    LOG_INFO("argv[3] : %d = apb_num", apb_num);
    LOG_INFO("argv[4] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    LOG_INFO("argv[5] : %d = test_config", test_config);
    LOG_INFO("argv[6] : %d = delay_value", delay_value);
    LOG_INFO("argv[7] : %d = post_filter_mode %s", post_filter_mode, post_filter_mode_str[post_filter_mode]);
    LOG_INFO("IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    cycles_per_block = (drf_clock) ? CYCLES_PER_BLOCK_1P5G : CYCLES_PER_BLOCK_983M;

#if VEX_1US_WINDOW
    us_granularity_required = get_us_granularity_status(drf_clock, test_config);
    if (us_granularity_required)
    {
        LOG_INFO("VEX_1US granularity enabled");
    }
#endif

    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    // one block extra needs to be send to avoid the underrun
    val_kargs[3] = capture_blocks + 1;
    val_kargs[4] = g_initial_block_size;
    /*DMEM address of Gbuffer Tx VEX*/
    val_kargs[6] = STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_adapt_mode1_g_vex_indicator;
    /*Getting the number of clocks per block in VEX*/
#if VEX_1P5G
    val_kargs[5] = CYCLES_PER_BLOCK_1P5G - 1;
#endif

    /*Number of vectors per LUT*/
    gbuffer_tx_val_args[0] = g_vectors_g_buf_lut_mode[lut_mode];
    /*Duration of each LUT in blocks*/
    gbuffer_tx_val_args[3] = (get_frac_os(test_config) * (FLITS_PER_1MB / VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]))) / MAX_LUT_UPDATES;

#if VEX_1US_WINDOW
    if (us_granularity_required)
    {
        /*number of vectors per block needs to be multiplied by 2*/
        val_kargs[1] = 2 * g_vectors_per_block[drf_clock][pdpd_in_rate];
        /* Clock duration has to be multiply by 2*/
        val_kargs[5] = ((val_kargs[5] + 1) * 2) - 1;
        gbuffer_tx_val_args[2] = val_kargs[5];

        /*Number of blocks has to be divide by 2*/
        capture_blocks = capture_blocks / 2;
        gbuffer_tx_val_args[3] /= 2;
    }
#endif

    /*enabling the V2D clock for the given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        LOG_ERROR("v2d_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config, post_filter_mode))
    {
        LOG_ERROR("Host Configuration failed");
        return rv;
    }

    /*Perform the FB_MEM configuration for Capture*/
    if (mem_fb_x_capture_configuration(SINGLE_CAPTURE_MODE, 0x3FFF, v2d_num, apb_num))
    {
        LOG_ERROR("MEM_FB configuration failed");
    }

    /*Prefill the MEM_FB with known pattern*/
    fill_mem_fb(v2d_num, MEM_FB_INIT_VALUE);

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        LOG_ERROR("reset_abc failed");
        return rv;
    }

    /*Populating the 241 flits of G buffer*/
    reg_check.v2d_num = v2d_num;
    reg_check.apb_num = apb_num;
    reg_check.test_config = test_config;
    reg_check.num_gmp_terms = get_gmp_terms(test_config);
    reg_check.num_ddr_terms = V2D_PDPD_DDR_TERMS;
    reg_check.gmp_c_i_value = GMP_C_I_VALUE_0;
    reg_check.gmp_c_q_value = GMP_C_Q_VALUE;
    reg_check.ddr_c_i_value = DDR_C_I_VALUE;
    reg_check.ddr_c_q_value = DDR_C_Q_VALUE;
    reg_check.gmp_shift_value = FLOW3_GMP_SHIFT_VALUE;
    reg_check.ddr_shift_value = FLOW3_DDR_SHIFT_VALUE;

    populate_g_buffer(dpd_coeff_buffer, &reg_check, lut_mode);

#if RCS_TRIGGER
    int rd_wr_value[32] = {0}, capture_cycles = 0;
    unsigned int dpd_passthru_buffer_data[1][NUM_OF_ELEMENTS_PER_VEC] = {0};

    // Passthru coeffecients
    dpd_passthru_buffer_data[0][0] = (PASSTHRU_I_COEFF_UNITY_GAIN) << 16 | PASSTHRU_Q_COEFF_UNITY_GAIN;
    // 65th bit should be set as 1 for imeediate update
    dpd_passthru_buffer_data[0][2] = 0x2;

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
    rcs_host_param[7] = g_vectors_g_buf_lut_mode[lut_mode];

    LOG_INFO("loaded the elf:%s", rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file);

    //clear the dram
    memset(rd_wr_value, 0, sizeof(rd_wr_value));
    write_mem_18a(g_dcode_buffer[0], 32, rd_wr_value, "DCODE_BUFFER");
    write_mem_18a(g_rsm_buffer[0], 1, rd_wr_value, "DCODE_BUFFER");

    /*Load the parameters to RCS RSM memory*/
    write_mem_18a(RSM_MEM_OFFSET, ARRAY_SIZE(rcs_host_param), rcs_host_param, "RCS_HOST_PARAM");

    /*Load the LUT Buffer to RCS*/
    write_mem_18a(RCS_LUT_BUFFER_ADDR, g_vectors_g_buf_lut_mode[lut_mode] * NUM_OF_ELEMENTS_PER_VEC, dpd_coeff_buffer[0], "LUT_COEFF");
    /*Load the Passthru coeff to RCS*/
    write_mem_18a(RCS_LUT_BUFFER_ADDR + (g_vectors_g_buf_lut_mode[lut_mode] * BYTES_PER_VEC),
                  NUM_OF_ELEMENTS_PER_VEC,
                  dpd_passthru_buffer_data[0],
                  "LUT_COEFF");
#endif

    /*reading the Matlab generated input Vector to be loaded to VEX_TX*/
    if (rv = input_pattern_read(val_inp, "../test_vectors/flow3/input_iq.txt"))
    {
        LOG_ERROR("input pattern read fail");
        return rv;
    }

    /*reading the matlab generated output test vectors to be used for integrity check by host*/
    sprintf(tref_file, "%s%s", "../test_vectors/flow3/",ref_file[test_config]);

    printf ("HOST: output file : %s", tref_file);

    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file");
        return -1;
    }

    /*Clearing the VEX VMEM and DMEM for both Tx and GBUFF Tx vex cores*/
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            LOG_ERROR("vex_mem_clear failed for vex:%d", vex_num_param[lc]);
            return rv;
        }
    }

    LOG_INFO("start vex program load");
    if ((rv = vex_loader(vex_num_param[0], "./vex_fw/sim_m64/v2d_flow3_tx.fw")))
        return rv;

    if ((rv = vex_loader(vex_num_param[1], "./vex_fw/sim_m64/v2d_adapt_mode1.fw")))
        return rv;
    LOG_INFO("vex program load - done");

    /* Loading the host parameters to VEX  Tx core*/
    if (load_vex_param(vex_num_param[0]/*vex_core*/, ARRAY_SIZE(offset_val)/*size of array*/, offset_val, val_kargs))
    {
        LOG_ERROR("Tx vex param loading failed");
    }

    /* Loading the host parameters to VEX Gbuffer Tx core*/
    if (load_vex_param(vex_num_param[1]/*vex_core*/, ARRAY_SIZE(guffer_tx_offset_val), guffer_tx_offset_val, gbuffer_tx_val_args))
    {
        LOG_ERROR("Rx vex param loading failed");
    }

    /* Loading the input vector for Tx vex core*/
    write_mem_18a((VEX_VMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow3_tx_vbuffer),
                  (VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC)/*size*/,
                  val_inp,
                  "TX_VEX_VMEM");

    /*Second LUT population*/
    reg_check.gmp_c_i_value = GMP_C_I_VALUE_1;
    populate_g_buffer(dpd_coeff_buffer_1, &reg_check, lut_mode);

    /*Third LUT population*/
    reg_check.gmp_c_i_value = GMP_C_I_VALUE_2;
    populate_g_buffer(dpd_coeff_buffer_2, &reg_check, lut_mode);

    /*Fourth LUT population*/
    reg_check.gmp_c_i_value = GMP_C_I_VALUE_3;
    populate_g_buffer(dpd_coeff_buffer_3, &reg_check, lut_mode);

    /*loading the 3 LUTs to VEX_ADAPT*/
    lut_mem_copy(dpd_coeff_buffer_1, dpd_coeff_buffer_2, dpd_coeff_buffer_3, vex_num_param[1], lut_mode);

#if RCS_TRIGGER
    /*start RCS core0
     *RCS core will start Tx core and after the program the QUAD BFN with the delay value
     *passed as an argument.*/
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");

#if (0 == REGRESSION)

    /* Wait for RCS to write the LUT*/
    if (rv = poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_GPDMA_TFR_DONE))
    {
        LOG_ERROR("poll rcs failed for RCS_GPDMA_TRANSFER_DONE");
        return rv;
    }

    /*To Check whether SHADOW to LIVE transition happened or not*/
    reg_check.v2d_num = v2d_num;
    reg_check.apb_num = apb_num;
    reg_check.test_config = test_config;
    reg_check.num_gmp_terms = get_gmp_terms(test_config);
    reg_check.num_ddr_terms = V2D_PDPD_DDR_TERMS;
    reg_check.gmp_c_i_value = GMP_C_I_VALUE_0;
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

    if (rv = write_reg_18a(g_rsm_buffer[0], HOST_VALIDATION_DONE, 0xFFFFFFFF, "RSM_FLAG"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }
#endif

    /* Wait for RCS to complete it's execution*/
    if (rv = poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_COMPLETE))
    {
        LOG_ERROR("poll rcs failed for RCS completion");
        return rv;
    }

    /*Checking BFN sync between QUAD and RCS*/
    if (rv = quad_v2d_sync_check())
    {
        if ((CLOCK_1P5G == drf_clock) && ((ABC_18A_0P8_0_4 == g_abc_build_version) || (ABC_18A_0P8_0_3 == g_abc_build_version)))
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

    loop_wait_count = 0;
    usleep(10000);

    /*Wait until the required number of flits transferred from VEX to HOST*/
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, "B2H_FLIT_COUNT")) < \
            (get_frac_os(test_config) * ((FLITS_PER_1MB) + (FLITS_PER_1MB / 2))))
    {
        // do nothing wait in this loop until required number of flits were received
        if (loop_wait_count >= 60)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf ("b2h_flit_cnt : %d", b2h_flit_count);

    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        LOG_ERROR("interrupt check failed\n");
        test_status |= 1;
    }

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

    /*this value shouldn't be modified as this is linked to VEX code and if modified VEX code needs to be modified
     * accordinlgy and needs to be recompiled*/
    host_flag = VEX_STOP_TRANSMIT_INDICATION;

    /*Signal from host to stop continuous flow on B Tx Vex Core*/
    if (rv = write_reg_18a(VEX_DMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow3_tx_g_host_indicator,
                host_flag, 0xFFFFFFFF, "HOST_INDICATION"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }

    /*Signal from host to stop continuous flow on G BUFFER Tx*/
    if (rv = write_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_adapt_mode1_g_host_indicator,
                host_flag, 0xFFFFFFFF, "HOST_INDICATION"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }

    /*Capture Memory comparison*/
    if (rv = pdpd_egress_cap_mem_compare(v2d_num, g_vectors_per_block[drf_clock][pdpd_out_rate]/*num_of_vectors*/, capture_delay_value,
                drf_clock, capture_blocks, (capture_blocks / MAX_LUT_UPDATES)/*LUT Block Duration*/, lut_mode, fp_ref_output))
    {
        LOG_ERROR("FB_MEM comparison failed");
    }
    else
    {
        LOG_INFO("MEM_FB comparison passed");
    }

    fclose(fp_ref_output);

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
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s, delay_value: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode],
                delay_value);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s, delay_value: %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode],
                delay_value);
        rv = 1;
    }

    return rv;
}
