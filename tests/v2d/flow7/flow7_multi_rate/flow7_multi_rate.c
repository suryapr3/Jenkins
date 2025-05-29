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
 * @file    flow7_multi_rate.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D and receving it back.
 * @details 1. Configuration of VEX, V2D and Common Module for sending data from VEX to V2D via C path
               with POST C center tap enabled and receving it back to other VEX via F path.
            2. Compares the received output with REF output for result evaluation.
   @TC Description:
        1. 1000 blocks for given data rate will be streamed to V2D Tx from
           configured VEX core.
        2. PDPD block was configured with POST C center tap with a specified gain.
        3. With Rx loop back (F Path) enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        4. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        5. The same data block will be sent continuously for 1000 blocks in the PASSTRHU mode.
        6, Rx VEX will exclude the first block from data comparison as there is a mismatch for the
           first block in MATLAB model and FPGA output.
        6. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        7. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow7_common_utils.h"
#include "common_utils.h"

#include "v2d_flow7_tx.map.h"
#include "v2d_flow7_rx.map.h"
#include "v2d_flow7_filter_mode_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define POST_C_CENTER_VALUE 1023
#define MAX_BLOCKS_PASSTHRU_MODE    1000
#define POST_FILTER_COEFF 100
#define NUM_VEX_CORES   2
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

const char *ref_file[2][PDPD_NUM_SAMPLE_RATES] = {
    {"ref_output_p5gsps.txt", "ref_output_1gsps.txt", "ref_output_2gsps.txt", "ref_output_4gsps.txt", "ref_output_8gsps.txt"},
    {"ref_output_p5gsps_filter_mode.txt", "ref_output_1gsps_filter_mode.txt", "ref_output_2gsps_filter_mode.txt",
        "ref_output_4gsps_filter_mode.txt", "ref_output_8gsps_filter_mode.txt"},
};

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/* The value should be number of blocks required for 8K samples i.e 256 vectors defined as per order in pdpd_rate_t enum */
uint32_t g_max_blocks[][PDPD_NUM_SAMPLE_RATES] = {
    {32, 16, 8, 4, 2},
    {86, 43, 22, 11, 6}
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last five entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// OFFSETS are from V2D PDPD base
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
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow7_rx_consumer_sm_gate), NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow7_rx_vbuffer_out), NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"}
    /***********************************************************************************************************************************/
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow7_config_tbl[] = {
// OFFSETS are from V2D PDPD base
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
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    /* Set the PD_EXTRA_ONLY bit*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_PD_EXTRA_ONLY_BF_MSK, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
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
int flow7_configure_pdpd(int, int, lut_mode_t, int);
int configure_v2d_host(int *, int, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock, test_config and filter_mode
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config, int post_filter_mode)
{
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = 0;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];
    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_out_rate] * 2)) - 1) << 16);

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate]) + g_vectors_per_block[drf_clock][pdpd_out_rate];
    printf("fill_level_value : %x\n", fill_level_value);
#endif

    printf ("Buffer: %x\n", v2d_buffer_b);

    for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    // Corresponds to cio2strm dest id
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[0]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][0], \
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
                HIVE_ADDR_v2d_flow7_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (PASSTHRU_MODE == post_filter_mode)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                        (0x80000000 | HIVE_ADDR_v2d_flow7_rx_vbuffer_out), g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
                return rv;
        }
        else
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                        (0x80000000 | HIVE_ADDR_v2d_flow7_filter_mode_rx_vbuffer_out), g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
                return rv;
        }
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

    printf("INFO: CM configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow7_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow7_config_tbl[i].offset), \
                    g_v2d_flow7_config_tbl[i].value, g_v2d_flow7_config_tbl[i].mask, g_v2d_flow7_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow7_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow7_config_tbl[i].offset), \
                    g_v2d_flow7_config_tbl[i].value | (drf_clock << 7), g_v2d_flow7_config_tbl[i].mask, g_v2d_flow7_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow7_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow7_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_flow7_config_tbl[i].mask, g_v2d_flow7_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow7_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow7_config_tbl[i].offset), \
                    (g_v2d_flow7_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow7_config_tbl[i].mask, g_v2d_flow7_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow7_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow7_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow7_config_tbl[i].mask, g_v2d_flow7_config_tbl[i].name))
            return rv;
    }

    if (FILTER_MODE == post_filter_mode)
    {
        if (rv = pdpd_post_c_reg_config(v2d_num, apb_num, POST_FILTER_COEFF))
        {
            printf("pdpd post c reg config failed\n");
            return rv;
        }
    }

    rv = flow7_configure_pdpd(v2d_num, apb_num, lut_mode, POST_C_CENTER_VALUE);
    printf("INFO: V2D pdpd configuration completed");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WM_EN_BF_MSK | fill_level_value, AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

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

    return rv;
}


int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0,
        post_filter_mode = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    int dmem_offset = DMEM_OFFSET;

    int offset_val[] = {HIVE_ADDR_v2d_flow7_tx_g_scalar_val, HIVE_ADDR_v2d_flow7_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow7_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow7_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow7_tx_g_initial_block_size, HIVE_ADDR_v2d_flow7_tx_g_host_cycle_count};
    unsigned int val_kargs[] = {0x00000000, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow7_rx_g_scalar_val, HIVE_ADDR_v2d_flow7_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow7_rx_g_num_blocks, HIVE_ADDR_v2d_flow7_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow7_rx_g_count1};
    unsigned int vex_rx_val_kargs[] = {0x00000000, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_out[NUMBER_OF_VECTORS_OUTPUT][NUM_OF_ELEMENTS_PER_VEC] =  {0};
    unsigned int host_ref_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_vec_processed = 0, host_blocks_processed = 0, host_flag = 1, host_result = 0, test_status = 0, loop_wait_count = 0;
    volatile int b2h_flit_count = 0, h2b_flit_count = 0;
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
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)\n",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);
    printf ("INFO: argv[6] : %d = post_filter_mode %s\n", post_filter_mode, post_filter_mode_str[post_filter_mode]);

    if (PASSTHRU_MODE == post_filter_mode)
    {
        g_max_blocks[drf_clock][pdpd_out_rate] = MAX_BLOCKS_PASSTHRU_MODE;  // In PASSTHRU mode comparision will be done for 1000 blocks
    }

    vex_rx_val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    vex_rx_val_kargs[2] = (g_max_blocks[drf_clock][pdpd_out_rate] + 1);
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    // Tx VEX needs to send the data in accordance to the pdpd_out_rate
    // two block extra needs to be send to avoid the underrun
    val_kargs[3] = vex_rx_val_kargs[2] + 1;
    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_out_rate];
    val_kargs[4] = g_initial_block_size;

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }
    /* Configure the POST C filter taps, center tap is already configured in configure_v2d_host()*/
    if (FILTER_MODE == post_filter_mode)
    {
        val_kargs[0] = 0x00010002;   // To have continuous changing pattern for filter mode. This vlaue shouldn't be modified as it is tied
                                    // to the matlab generated output
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, test_config, post_filter_mode))
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
    for (lc = 0 ; lc < NUM_VEX_CORES; lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[lc]);
            return rv;
        }
    }

    printf("Host: start vex program load\n");
    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow7_tx.fw")))
        return rv;

    if (PASSTHRU_MODE == post_filter_mode)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow7_rx.fw")))
            return rv;
    }
    else
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow7_filter_mode_rx.fw")))
            return rv;
    }
    printf("Host: vex program load - done\n");

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
    for (i = 0; i < g_vectors_per_block[drf_clock][pdpd_out_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = ((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + j);
        }
    }

    sprintf(tref_file, "%s%s", PATH_PREFIX,ref_file[post_filter_mode][pdpd_out_rate]);

    printf ("HOST: output file : %s\n", tref_file);
    fp_ref_output = fopen(tref_file,"r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file\n");
        return -1;
    }

    /* In passthru mode same block of data will be fed continuoulsy so only one block of samples are sufficient for REFERENCE pattern.
     * where as in filter mode the input will be continuously changing hence require total reference vectors*/
    if (PASSTHRU_MODE == post_filter_mode)
    {
        if (vector_read_hex_u32(fp_ref_output,
                    host_ref_data,
                    1 * g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC) < \
                    1 * g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC)
        {
            printf("ERROR: Insufficient Output REF data\n");
            return -1;
        }
    }
    else
    {
        if (vector_read_hex_u32(fp_ref_output,
                    host_ref_data,
                    g_max_blocks[drf_clock][pdpd_out_rate] * g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC) < \
                    (g_max_blocks[drf_clock][pdpd_out_rate] * g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC))
        {
            printf("ERROR: Insufficient Output REF data\n");
            return -1;
        }
    }

    fclose(fp_ref_output);

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow7_tx_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if (PASSTHRU_MODE == post_filter_mode)
    {
        if ((rv = srp_vex_memid_store(vex_hdl,
                            vex_num_param[1],
                            SRP_VEX_VMEM,
                            HIVE_ADDR_v2d_flow7_rx_vbuffer,/*local_addr*/
                            host_ref_data,
                            (g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
    }
    else
    {
        if ((rv = srp_vex_memid_store(vex_hdl,
                            vex_num_param[1],
                            SRP_VEX_VMEM,
                            HIVE_ADDR_v2d_flow7_rx_vbuffer,/*local_addr*/
                            host_ref_data,
                            (g_max_blocks[drf_clock][pdpd_out_rate] * g_vectors_per_block[drf_clock][pdpd_out_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
    }


    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, vex_num_param[1], 0); // Rx VEX Core
    srp_vex_start(vex_hdl, vex_num_param[0], 0); // Tx VEX Core
    printf("Host: vex program start - done\n");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
            ((g_initial_block_size * VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate])) + \
             VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_out_rate] / 2)))
    {
        // do nothing wait in this loop until 1.5 blocks of data was received
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
    /*Signal VEX to start continuous flow*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow7_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /* Triggering the forced BFN*/
    if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    while ((h2b_flit_count += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT")) <
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

    /* Rx VEX will compare one block less to the max blocks as first block will be discarded*/
    while (host_vec_processed < ((g_max_blocks[drf_clock][pdpd_out_rate] - 1) * g_vectors_per_block[drf_clock][pdpd_out_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + HIVE_ADDR_v2d_flow7_rx_g_count1,
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
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow7_rx_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow7_rx_g_add_val_out,
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
        printf("Received samples match with the Reference output\n");
    }

    if (rv = interrupt_status_check(v2d_num, apb_num, TX_UNDERRUN_VALUE, 0, 0))
    {
        printf("ERROR: interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST:Interrupt check passed\n");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock: %d, pdpd_in_rate: %d, pdpd_out_rate: %d\n",
                vex_num, v2d_num, apb_num, drf_clock, pdpd_in_rate, pdpd_out_rate);
    }
    else
    {
        printf("Host:---- FAIL ---- vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock: %d, pdpd_in_rate : %d, pdpd_out_rate: %d\n",
                vex_num, v2d_num, apb_num, drf_clock, pdpd_in_rate, pdpd_out_rate);
        rv = 1;
    }

    return rv;
}
