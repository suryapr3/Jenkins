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
 * @file    flow1_odd_v2d.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D via path A
 *          and receving it back via path F by using QUAD delayed start and only
 *          ODD V2D will be triggered.
 * @TC Description:
        1. 1000 blocks for given data rate will be streamed to V2D from
           configured VEX core.
        2. V2D memory will be configured for 3 times of the block size of corresponding
           sample rate.
        3. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        4. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        5. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        6. Only Odd V2D DRF channel will be configured and only correspnding clocks will
           be enabled.
        7. The BFN trigger will be coming from even V2D BFN configuration for the corresponding
           odd V2D channel.
        8. VEX CORES triggering along with the BFN programming will be triggered from RCS.
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS

#include "v2d_flow1_tx_p25_4iq.map.h"
#include "flow1_common_utils.h"
#include "common_utils.h"

#include "v2d_flow1_tx_8iq.map.h"
#include "v2d_flow1_rx_p25iq.map.h"
#include "v2d_flow1_rx_p5_8iq.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define MAX_BLOCKS  1000
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int g_num_blocks_v2d_buffer = 3;

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last four entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    // These are for Buffer A0
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
     /* Value should be 2 blocks of data for any rate */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow1_rx_p5_8iq_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x6000 , i.e VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer_out), \
        NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},

    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0x7, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last four entries order shouldn't be modified*/
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},

    /************************************************************************************************************/
    /* The last four entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x4FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"}
    /************************************************************************************************************/
};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int configure_v2d_host(int *, int, int, int, sys_rate_t);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id, V2d Id, APB Id and sys_rate
 * @return          status
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, sys_rate_t sys_rate)
{
    int i,rv = 0;

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

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_flow1_md_control_tbl[sys_rate], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[1], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    printf ("INFO: CM configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    ((((g_num_blocks_v2d_buffer) * (g_flow1_vectors_per_block[sys_rate] * 2)) - 1) << 16), \
                    g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value | (drf_clock << 7) |sys_rate, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), g_flow1_tx_strm_cnt0_offset[sys_rate], \
                    g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_VALUE, \
                AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), RX_GNRL_CSR_VALUE, \
                AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow1_rx_p5_8iq_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

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
    int vex_num_param[2] = {0}, v2d_num, apb_num, host_flag = 1, test_status = 0, loop_wait_count = 0, drf_clock=0, host_result = 0,
        host_vec_processed = 0, host_blocks_processed = 0, quad_instance = 0, quad_v2d_index = 0, delay_value = 0;
    sys_rate_t sys_rate;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;

    int dmem_offset = DMEM_OFFSET;
    int offset_val[] = {HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_scalar_val, HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_dest_buffer_base, HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_num_blocks,
                         HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_cycle_count};
    unsigned int val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_scalar_val, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_vecs_in,
                               HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_blocks, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_tbs_in_blk,
                               HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_count1};
    unsigned int vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];
    int fill_level_value[MAX_NUM_STREAMS] = {0};
    int watermark_buf[MAX_NUM_STREAMS] = {0};

#if RCS_TRIGGER
    srp_hdl_t srp_rcs_hdl = NULL;
    srp_dev_config_t srp_cfg = {0};
    int dev_id = 0;
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    int rcs_host_param[3] = {0}; // corresponds to quad_instance, apb_num and delay value
#endif

    init(); /* Initialize the srp*/

    LOG_PRINT("INFO: logger beginning");
    printf("INFO: argc : %d", argc);

    quad_instance = argv[0];
    apb_num = argv[1];
    drf_clock = (int) argv[2];
    sys_rate = (int) argv[3];
    delay_value = (int) argv[4];

    printf ("INFO: argv[0] : %d = quad_instance", quad_instance);
    printf ("INFO: argv[1] : %d = apb_num", apb_num);
    printf ("INFO: argv[2] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[3] : %d = sys_rate %s", sys_rate, sys_rate_str[sys_rate]);
    printf ("INFO: argv[4] : %d = delay_value", delay_value);

    v2d_num = g_v2d_instance_in_quad[quad_instance][1]; // odd V2D
    vex_num_param[0] = g_vex_instance_in_v2d[v2d_num][0];    // Tx VEX
    vex_num_param[1] = g_vex_instance_in_v2d[v2d_num][1];    // Rx VEX

    add_val[0] = val_kargs[0];
    val_kargs[3] = MAX_BLOCKS;
    val_kargs[1] = g_flow1_vectors_per_block[sys_rate];

    vex_rx_val_kargs[2] = MAX_BLOCKS;
    vex_rx_val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*enabling the V2D clock for the odd numbered V2D only*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }

#if RCS_TRIGGER
    srp_dev_config(dev_id, srp, &srp_cfg, &srp_rcs_hdl);

    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];

    srp_rcs_config(srp_rcs_hdl, &rcs_params);

    rcs_host_param[0] = quad_instance;
    rcs_host_param[1] = apb_num;
    rcs_host_param[2] = delay_value;

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
#endif

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, sys_rate))
    {
        printf ("ERROR: configure_v2d_host");
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
    if (rv = vex_mem_clear(vex_num_param[0], srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d", vex_num_param[0]);
        return rv;
    }
    if (rv = vex_mem_clear((vex_num_param[1]), srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d", vex_num_param[1]);
        return rv;
    }

    printf("Host: start vex Rx program load ");

    /*The VEX kernel is sys rate dependent*/
    if (SYS_RATE_IQ_P375 >= sys_rate)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow1_rx_p25iq.fw")))
            return rv;
    }
    else
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_flow1_rx_p5_8iq.fw")))
            return rv;
    }

    printf("Host: start vex Tx program load ");
    if ((SYS_RATE_IQ_8 == sys_rate) || (SYS_RATE_R_16 == sys_rate))
    {

        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow1_tx_8iq.fw")))
            return rv;
    }
    else
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_flow1_tx_p25_4iq.fw")))
            return rv;
    }
    printf("Host: vex program load - done");

    /* Loading the host parameters to VEX Tx core*/
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

    for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = ((i*NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j);
        }   // for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++) ends
    }   // for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++) ends

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_tx_p25_4iq_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                         vex_num_param[1],
                         SRP_VEX_VMEM,
                         HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer,/*local_addr*/
                         val_inp[0],
                         (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
         return rv;

#if RCS_TRIGGER
    // start RCS core0
    // RCS core will start both Rx and Tx cores respectively and after the program the QUAD BFN with the delay value
    // passed as an argument.
    srp_rcs_rcp_start(srp_rcs_hdl, SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");
#endif

    loop_wait_count = 0;
    /*Wait till the required number of flits reached H2B interface*/
    while ((h2b_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT"))  <
            ((MAX_BLOCKS * (g_flow1_vectors_per_block[sys_rate] * 2))))
    {

        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT 0x%x is not the required number of flits", h2b_flit_cnt);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    loop_wait_count = 0;
    usleep(1000);

    /*Wait till required number of vectors have been processed by VEX FW*/
    while (host_vec_processed < (MAX_BLOCKS * g_flow1_vectors_per_block[sys_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_count1,
                        &host_vec_processed,
                        1,
                        flags)))
            return rv;

        if (loop_wait_count >= 30)
        {
            printf("ERROR: VEX core didn't processed enough vectors 0x%x\n", host_vec_processed);
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
                    dmem_offset + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    /*Reading the number of blocks processed by VEX*/
    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x", host_blocks_processed - add_val[0]);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV");
        test_status = 1;
    }
    else
    {
        printf("HOST: Received output matches with Reference output");
    }

    /*interrupt check for V2D 0 Ch 0*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0, 0, 0))
    {
        printf("ERROR: interrupt check failed");
        test_status |= 1;
    }

    /*Read the fill level trigger value for DRF channel*/
    get_tx_trigger_fill_level(v2d_num, apb_num, 1/*number of streams*/, fill_level_value);
    printf("BFN triggered when buffer is @0x%x", fill_level_value[0]);

    /*Read the water mark register for DRF channel*/
    get_tx_wm_hilo(v2d_num, apb_num, 1/*number of streams*/, watermark_buf);
    printf("low watermark value 0x%x", (watermark_buf[0] & 0xFFF));
    printf("high watermark value 0x%x", ((watermark_buf[0] >> 16) & 0xFFF));

    /*this value shouldn't be modified as this is linked to VEX code and if modified VEX code needs to be modified
     * accordinlgy and needs to be recompiled*/
    host_flag = VEX_STOP_TRANSMIT_INDICATION;

    /*Signal from host to stop continuous flow on B Tx Vex Core , which in turn will signal the C Tx Vex core to stop continuous transmission*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /*This sleep is required to provide enough time to get the underrun set*/
    usleep(10000);

    /*Interrupt check for V2D*/
    if (rv = interrupt_status_check(v2d_num, apb_num, TX_UNDERRUN_VALUE, 0/*nsip_0_exp_value*/, 0/*nsip_1_exp_value*/))
    {
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed");
    }


    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- quad_instance: %d, drf_clock: %s, sys_rate: %s, delay_value: %d",
                quad_instance, drf_clock_str[drf_clock], sys_rate_str[sys_rate], delay_value);
    }
    else
    {
        printf("Host:---- FAIL ---- quad_instance: %d, drf_clock: %s, sys_rate: %s, delay_value: %d",
                quad_instance, drf_clock_str[drf_clock], sys_rate_str[sys_rate], delay_value);
        rv = 1;
    }

    return rv;
}   // main ends
