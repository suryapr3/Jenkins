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
/*
 * @file    pc_hbi_drop.c
 * @details 1. This TC validates the PC_HBI_DROP interrupt generation.
   @TC Description:
        1. Configure all the V2D registers.
        2. Trigger the MODE1 transfer from RCS via AXI interface.
        3. Same time trigger the VEX to send the mode1 data, VEX will be triggered from RCS.
        4. Validate whether required interrupts were generated or not to make the TC PASS or FAIL.
        5. This TC supports all available rates
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow3_common_utils.h"

#include "v2d_flow3_gbuffer_mode1_tx.map.h"
#include "v2d_flow3_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define B2H_MAP_VALUE_G_COEFF 0x20000   // in Bytes
#define B2H_MAP_VALUE_PASSTHRU_GAIN 0x24000 // in Bytes
#define NUM_VEX_CORES   2
#define AX_RW_OFFSET    0x10000
#define V2D_EXP_INTERRUPT_VALUE  AV2D_CSR_INT_CSR_INT_STATUS_PC_HBI_DROP_BF_MSK
#define RCS_HANDSHAKE_VALUE 0x5588
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int g_initial_block_size = 1;    // This corresponds to 1L and VEX will transfer 1.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

int rsm_flag_addr_offset[] = {0x23ffec}; // Handshaking address between RSM and HOST

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
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
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
    /* Data will be written to VEX VMEM location 0x8000*/
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
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), (B2H_MAP_VALUE_G_COEFF - 1), NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},
    // This was for GMP DDR Coeff update from VEX in MODE 1
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL4_OFFSET), (0x80000000 | B2H_MAP_VALUE_G_COEFF), \
        NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "CM_1_B2H_ADDR_MAP_TBL4"},
    // Mask was set for total 256 flits in Bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL4_OFFSET), 0x3FFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL4"},
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow3_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_INT_LOW_EN"},

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
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STREAM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
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
int flow3_configure_pdpd(int, int, int);
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
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = PDPD_LUT_48;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
    printf ("Buffer: 0x%x", v2d_buffer_b);

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    // Fill level value should be 1.5 times of the B block size as per HAS
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
                HIVE_ADDR_v2d_flow3_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
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
                    (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow3_rx_vbuffer_out), \
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

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

    rv = gbuffer_update_configure_pdpd(v2d_num, apb_num, test_config);
    printf("INFO: V2D pdpd configuration completed");

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

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num = 0, vex_num_param[NUM_VEX_CORES] = {0}, v2d_num, apb_num, underrun_reg_value = 0, drf_clock = 0, test_config = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    lut_mode_t lut_mode = PDPD_LUT_48;
    int dmem_offset = DMEM_OFFSET;

    int offset_val[] = {HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_scalar_val, HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_initial_block_size, HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_dpd_coeff_base,
                         HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_passthru_coeff_base, HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_host_cycle_count,
                         HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_g_vectors_g_buf};
    unsigned int val_kargs[] = {0x00010002, NUMBER_OF_VECTORS_INPUT, 0, 0, 3, (B2H_MAP_VALUE_G_COEFF),
                             (B2H_MAP_VALUE_PASSTHRU_GAIN), (CYCLES_PER_BLOCK_983M - 1), 120};

    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    /*Holds the 48 LUT's Data*/
    unsigned int dpd_coeff_buffer[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0};
    unsigned int vex_dpd_coeff_buffer[G_BUF_LUT][NUM_WORDS_PER_LUT] = {0xabc};
    /* Holds the Passthru coeff data*/
    unsigned int dpd_passthru_buffer_data[1][NUM_OF_ELEMENTS_PER_VEC] = {0};
    int host_flag = 0, test_status = 0, loop_wait_count = 0;
    uint32_t bfn_lo_int_value = 0, bfn_hi_int_value = 0;
    v2d_shdw_live_reg_check_t reg_check;

#if RCS_TRIGGER
    srp_hdl_t srp_rcs_hdl = NULL;
    srp_dev_config_t srp_cfg = {0};
    int dev_id = 0;
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    int rcs_host_param[9] = {0}; // corresponds to tx vex num, rx vex num, v2d_num, apb_num , numbe of vectors to write and 128 bits for mode2 update
#endif

    init(); // Initializing the srp

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    test_config = argv[5];
    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    lut_mode = g_test_config_tbl[test_config][2];

    printf ("INFO: argv[0] : %d = tx_vex0", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx_vex", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[3] : %d = apb_num", apb_num);
    printf ("INFO: argv[4] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[5] : %d = test_config", test_config);
    printf ("INFO : IN_RATE (%s), OUT_RATE (%s), toatal LUT (%d)",
            pdpd_rate_str[g_test_config_tbl[test_config][0]], pdpd_rate_str[g_test_config_tbl[test_config][1]], \
            num_lut[g_test_config_tbl[test_config][2]]);

    // one block extra needs to be send to avoid the underrun
    val_kargs[1] = g_vectors_per_block[drf_clock][pdpd_in_rate];
    val_kargs[3] = g_max_blocks[drf_clock][pdpd_out_rate] + 1;
    val_kargs[4] = g_initial_block_size;
    val_kargs[8] = g_vectors_g_buf_lut_mode[lut_mode];

    dpd_passthru_buffer_data[0][0] = (PASSTHRU_I_COEFF_UNITY_GAIN) << 16 | PASSTHRU_Q_COEFF_UNITY_GAIN;

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*enabling the V2D clock for the given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }

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
    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        if (rv = vex_mem_clear(vex_num_param[lc], srp))
        {
            printf("ERROR: vex_mem_clear failed for vex:%d", vex_num_param[lc]);
            return rv;
        }
    }

    printf("Host: start vex program load");
    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow3_gbuffer_mode1_tx.fw")))
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

    /*Populating the 241 flits of G buffer*/
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

    populate_g_buffer(dpd_coeff_buffer, &reg_check, lut_mode);

    /*Loading the DPD Coeff buffer*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_v_gbuffer,/*local_addr*/
                        vex_dpd_coeff_buffer[0],
                        sizeof(dpd_coeff_buffer))))
        return rv;

    /*Loading the PASSTHRU Coeff buffer*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow3_gbuffer_mode1_tx_v_passthru_gain,/*local_addr*/
                        dpd_passthru_buffer_data[0],
                        (NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;


#if RCS_TRIGGER
    int words_index = 0;
    srp_dev_config(dev_id, srp, &srp_cfg, &srp_rcs_hdl);

    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];

    srp_rcs_config(srp_rcs_hdl, &rcs_params);

    rcs_host_param[0] = vex_num_param[0];   // Tx VEX num
    rcs_host_param[1] = vex_num_param[1];   // Rx VEX num
    rcs_host_param[2] = v2d_num;
    rcs_host_param[3] = apb_num;
    rcs_host_param[4] = g_vectors_g_buf_lut_mode[lut_mode];
    rcs_host_param[5] = dpd_passthru_buffer_data[0][0];

    /*Load the parameters to RCS RSM memory*/
    for (lc = 0; lc < ARRAY_SIZE(rcs_host_param); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                SRP_BLOCK_RCS_RSM, /*BlockVal,*/
                0, /*IndexVal*/
                RSM_MEM_OFFSET + (lc * sizeof(int)),
                (rcs_host_param + lc),
                1,
                flags)))
            return rv;
    }

    for (lc = 0; lc < G_BUF_LUT; lc++)
    {
        for (words_index = 0; words_index < NUM_WORDS_PER_LUT; words_index++)
        {
            if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
                    0, /*IndexVal*/
                    AX_RW_OFFSET + (((lc * NUM_WORDS_PER_LUT) + words_index) * sizeof(int)),
                    &(dpd_coeff_buffer[lc][words_index]),
                    1,
                    flags)))
                return rv;

        }
    }

    // start RCS core0
    // RCS core will start the AXI transfer of PDPD coeff in MODE1 and trigger the VEX Tx core along with it.
    // At the end it will trigger the SHDW to LIVE transfer switching of coeffecients by writing to the PDPD
    // CONTROL register.
    srp_rcs_rcp_start(srp_rcs_hdl, SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");

    /*wait till the RCS completed it's execution*/
    if (rv = poll_rsm_flag_rcs(rsm_flag_addr_offset[0], RCS_HANDSHAKE_VALUE))
    {
        printf("ERROR: poll rcs failed");
        return rv;
    }
#endif

#if (0 == REGRESSION)
    /*To Check whether SHADOW to LIVE transition happened or not*/
    if (rv = gmp_ddr_shdw_live_reg_check(&reg_check))
    {
        printf("ERROR: SHDW to LIVE transition failied");
        //return 1;
    }
    else
    {
        printf("HOST: SHDW to LIVE tranition passed");
    }

    /*Check whether passthru value transferred from SHDW to LIVE*/
    if (rv = passthru_reg_check(v2d_num, apb_num, dpd_passthru_buffer_data[0][0]))
    {
        printf("ERROR: PASSTHRU REG SHDW TO LIVE Transition failed");
        //return 1;
    }
    else
    {
        printf("HOST: PASSTHRU REG SHDW to LIVE transition passed");
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    if (rv = interrupt_status_check(v2d_num, apb_num, V2D_EXP_INTERRUPT_VALUE/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: interrupt check failed");
        test_status |= 1;
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

    /*As the scenario was ended the interrupt should be reset*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt check failed");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed");
    }

    /*Read the RCS DMAC CH1 interrupt*/
    if ((RCS_DMAC_CH1_INTSTATUS_BLOCK_TFR_DONE_INTSTAT_BF_MSK | RCS_DMAC_CH1_INTSTATUS_DMA_TFR_DONE_INTSTAT_BF_MSK) !=
            get_rcs_dmac_ch1_int_status())
    {
        printf("ERROR: RCS DMAC int status was not expected");
    }

    /*Clear the RCS DMAC interrupt*/
    if (rv = clear_rcs_dmac_ch1_int(RCS_DMAC_CH1_INTCLEARREG_CLEAR_BLOCK_TFR_DONE_INTSTAT_BF_MSK |
                RCS_DMAC_CH1_INTCLEARREG_CLEAR_DMA_TFR_DONE_INTSTAT_BF_MSK))
    {
        printf("WARNING: RCS int clear failed");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex : %d, rx_vex : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, pdpd_in_rate: %s, \
                pdpd_out_rate: %s, lut_mode: %d",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], pdpd_rate_str[pdpd_in_rate],
                pdpd_rate_str[pdpd_out_rate], g_test_config_tbl[test_config][2]);
        rv = 1;
    }

    return rv;
}
