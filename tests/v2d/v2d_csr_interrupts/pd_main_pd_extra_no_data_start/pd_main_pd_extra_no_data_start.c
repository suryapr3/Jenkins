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
 * @file    pd_main_pd_extra_no_data_start.c
 * @details 1. This TC validates the PD_MAIN_NO_DATA_START and PD_EXTRA_NO_DATA_START interrupts
 *             generation.
   @TC Description:
        1. Configure all the V2D registers.
        2. Trigger the forced BFN without initiating any data flow.
        3. Validate whether required interrupts were generated or not to make the TC PASS or FAIL.
        4. This TC supports below rates
            0.5IQ 1IQ 2IQ 4IQ and 8IQ

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow4_common_utils.h"
#include "common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NUM_VEX_CORES   2
#define NSIP_1_EXP_VALUE 0
#define B2H_ADD_MAP_B_OFFSET    0x10000
#define V2D_EXP_INTERRUPT_VALUE (AV2D_CSR_INT_CSR_INT_STATUS_PD_EXTRA_NODATA_START_BF_MSK | AV2D_CSR_INT_CSR_INT_STATUS_PD_MAIN_NODATA_START_BF_MSK)
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

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
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 1K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), (B2H_ADD_MAP_B_OFFSET - 1), NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET), \
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
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), (0x80000000 | B2H_ADD_MAP_B_OFFSET), \
        NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), ((2 * B2H_ADD_MAP_B_OFFSET) - 1), \
        NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "HBI_1_B2H_ADDR_MASK_TBL0"},
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
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
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
int configure_v2d_host(int *, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock , test_config and post_filter_mode
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, int test_config)
{
    int i, rv = 0, v2d_buffer_b = 0, v2d_buffer_c= 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    /* Buffer C should be always allocated at lower half of V2D buffer with 2 times of the block size and
     * Buffer B should be always allocated at higher half of V2D buffer with 3 times of the block size*/
    v2d_buffer_c = ((((g_num_blocks_v2d_buffer - 1) * (g_vectors_per_block[drf_clock][pdpd_out_rate] * 2)) - 1) << 16);
    v2d_buffer_b = V2D_BUFFER1_OFFSET | ((V2D_BUFFER1_OFFSET + g_num_blocks_v2d_buffer * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2) - 1) << 16);
    printf ("Buffer b: %x, Buffer C: %x\n", v2d_buffer_b, v2d_buffer_c);

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | 0x0), \
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
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow4_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow4_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow4_config_tbl[i].mask, g_v2d_flow4_config_tbl[i].name))
            return rv;
    }

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
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0,
        post_filter_mode = 0;
    uint32_t bfn_lo_int_value = 0, bfn_hi_int_value = 0, test_status = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    v2d_num = argv[0];
    apb_num = argv[1];
    drf_clock = (int) argv[2];
    test_config = argv[3];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf ("INFO: argv[0] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[1] : %d = apb_num\n", apb_num);
    printf ("INFO: argv[2] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[3] : %d = test_config\n", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)\n",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

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

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    /* Trigger BFN to start the PDPD block*/
    if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }

    /*Check the Interrupt status*/
    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_EXP_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed\n");
    }

    if (DRF_CHANNEL_0 == apb_num)
    {
        bfn_lo_int_value = BFN_CSR_SUBB_LO_INTR_CH0_AV2D_LO_INTR_BF_MSK;
        bfn_hi_int_value = BFN_CSR_SUBB_HI_INTR_CH0_AV2D_HI_INTR_BF_MSK;
    }
    else
    {
        bfn_lo_int_value = BFN_CSR_SUBB_LO_INTR_CH1_AV2D_LO_INTR_BF_MSK;
        bfn_hi_int_value = BFN_CSR_SUBB_HI_INTR_CH1_AV2D_HI_INTR_BF_MSK;
    }

    /*Check the BFN sub block interrupt status*/
    if (rv = bfn_interrupt_status_check(v2d_num, apb_num, bfn_lo_int_value, bfn_hi_int_value))
    {
        printf("ERROR: BFN SUBB validation failed");
    }

    /*Clear the interrupt bits in status registers by writing to CLEAR register*/
    if (rv = write_interrupt_clear(v2d_num, apb_num, V2D_EXP_INTERRUPT_VALUE, 0/*nsip0 interrupt vlaue*/, 0/*nsip1 interrupt value*/))
    {
        printf("Interrupt clear failed");
    }

    /*Check the Interrupt status again as it is functional scenario the interrupt bit shouldn't be reset*/
    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_EXP_INTERRUPT_VALUE, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
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
        printf("Host:---- SUCCESS ---- v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s\n",
                v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode]);
    }
    else
    {
        printf("Host:---- FAIL ---- v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d, post_filter_mode: %s\n",
                v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2], post_filter_mode_str[post_filter_mode]);
        rv = 1;
    }

    return rv;
}
