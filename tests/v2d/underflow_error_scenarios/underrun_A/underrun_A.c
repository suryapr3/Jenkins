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
 * @file    underrun_A.c
 * @brief   HOST Configuration code for evaluating the underrun behaviour in A path.
 * @details 1. Configuration of VEX, V2D and Common Module for sending data from VEX to V2D
               and receving it back to VEX.
            2. Compares the received output with REF output for result evaluation.
            3. Check whether the underrun flag was set or not.
   @TC Description:
        1. One block of data (0.5usec worth) for given data rate will be streamed to V2D Tx from
           configured VEX core.
        2. With Rx loop back enabled the data looped bac at sample interface
           was expected to reach the same VEX core.
        3. Once underrun interrupt asserted last sample will be continuously played which will be streamed to Rx part
           and routed to other two VEX cores which are x+1 and x+2 (x is the configured VEX)
        4. Supported data rates are below
            P25IQ to 8IQ
            3R to 16R

 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow1_common_utils.h"
#include "common_utils.h"
#include "v2d_underrun_a_rx_p5_8iq.map.h"
#include "v2d_underrun_a_tx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/


/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/


int g_initial_block_size = 1;

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// The last 9 entries order shouldn't be modified
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, \
        "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, \
        "B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, \
        "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_vbuffer_out), \
        NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"}
    /***********************************************************************************************************************************/
};

// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Three entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "INT_LOW_EN"},
// Tx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last three entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    /*Set Rx Loopback bit (9)*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, 0x200, AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT0_OFFSET, 0x8000000B, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x8000000B, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"}
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
 * @param [in]      Vex num, V2d num APB num and sys_rate
 * @return          status value
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, sys_rate_t sys_rate)
{
    int i, rv = 0;

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

    for (i = 0; i < ARRAY_SIZE(g_cm_0_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  ARRAY_SIZE(g_cm_0_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_flow1_md_control_tbl[sys_rate], \
                    g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  ARRAY_SIZE(g_cm_0_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[1], g_cm_0_config_tbl[i].mask, \
                g_cm_0_config_tbl[i].name))
            return rv;
    }
    printf("INFO: CM configuration completed");

    for (i = 0; i < (ARRAY_SIZE(g_v2d_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), g_v2d_config_tbl[i].value, \
                g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value | (drf_clock << 7) | sys_rate, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
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
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), \
                TX_GNRL_CSR_VALUE, AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), \
                RX_GNRL_CSR_VALUE, AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf("INFO: V2D configuration completed");

// SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
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
        host_vec_processed = 0, host_blocks_processed = 0;
    sys_rate_t sys_rate;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;
    int dmem_offset =  DMEM_OFFSET;
    int num_vec = NUMBER_OF_VECTORS_INPUT;
    int offset_val[4] = {HIVE_ADDR_v2d_underrun_a_tx_g_scalar_val, HIVE_ADDR_v2d_underrun_a_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_underrun_a_tx_g_dest_buffer_base, HIVE_ADDR_v2d_underrun_a_tx_g_num_blocks};
    unsigned val_kargs[4] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_scalar_val, HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_num_vecs_in,
                               HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_num_blocks, HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_tbs_in_blk,
                               HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_count1};
    unsigned int vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 2, 0};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_out[NUMBER_OF_VECTORS_OUTPUT][NUM_OF_ELEMENTS_PER_VEC] =  {0};
    unsigned int add_val[1], underrun_reg_value, underrun_sample_new[8], underrun_sample[8], buf_status = 0;


    init();

    LOG_PRINT ("INFO: logger beginning\n");
    printf ("INFO: argc : %d\n", argc);
     vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    sys_rate = (int) argv[5];

    printf ("INFO: argv[0] : %d = tx_vex\n", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx_vex\n", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[3] : %d = apb_num\n", apb_num);
    printf ("INFO: argv[4] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[5] : %d = sys_rate %s\n", sys_rate, sys_rate_str[sys_rate]);

    add_val[0] = val_kargs[0];
    val_kargs[3] = g_initial_block_size;
    val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[2] = g_initial_block_size;
    vex_rx_val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*enabling the V2D clock for the given channel*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_quad_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock, sys_rate))
    {
        printf("ERROR: configure_v2d_host\n");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
    {
        printf("ERROR: vex_config failed\n");
        return rv;
    }

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    printf("Host: start vex program load\n");
    if ((rv = srp_vex_loader(vex_hdl, vex_num_param[0], "vex_fw/sim_m64/v2d_underrun_a_tx.fw")))
        return rv;

    if (SYS_RATE_IQ_P375 >= sys_rate)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_underrun_a_rx_p25iq.fw")))
            return rv;
    }
    else
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[1], "vex_fw/sim_m64/v2d_underrun_a_rx_p5_8iq.fw")))
            return rv;
    }


    printf("Host: vex program load - done\n");

    /* Loading the Host to VEX config params*/
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
    }

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
    for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = ((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j)  ;
        }
    }

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_underrun_a_tx_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;


    /* Reading underrun Reg value at the starting which shouldn't be set*/
    if (0 == get_v2d_interrupt_status(v2d_num, apb_num))
    {
        printf ("Underrun flag was not set\n");
    }
    else
    {
        printf("ERROR:Underrun flag was set before the V2D start\n");
        test_status = 1;
    }

    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, vex_num_param[0], 0);
    srp_vex_start(vex_hdl, vex_num_param[1], 0);
    printf("Host: vex program start - done\n");

    usleep(10000);

    /* Wait until you get required number of flits transferred through NSIP module from VEX to V2D*/
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) < (g_initial_block_size * g_flow1_vectors_per_block[sys_rate] * 2))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /*Trigger the forced BFN*/
    if (rv = tx_start_bfn_trigger(v2d_num, apb_num))
    {
        printf("ERROR: bfn force trigger failed\n");
        return rv;
    }

    loop_wait_count = 0;
    usleep(1000);

    /* Wait until you get one block of data transferred through NSIP module in H2B direction as part of Rx Loopback*/
    while ((h2b_flit_cnt += read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FLIT_COUNT_OFFSET), \
                    "H2B_FLIT_COUNT")) < g_initial_block_size * (g_flow1_vectors_per_block[sys_rate] * 2))
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

    loop_wait_count = 0;
    usleep(10000);

    while (host_vec_processed < (g_flow1_vectors_per_block[sys_rate]))
    {
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[1],
                        dmem_offset + HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_count1,
                        &host_vec_processed,
                        1,
                        flags)))
            return rv;

        if (loop_wait_count >= 30)
        {
            printf("loop wait count value= %d", loop_wait_count);
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
                    dmem_offset + HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_compare_result,
                    &host_result,
                    1,
                    flags)))
        return rv;

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x\n", host_blocks_processed - add_val[0]);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Received output matches with Reference output\n");
    }

    /* Reading underrun Reg value after one block reception expected to be set*/
    underrun_reg_value = get_v2d_interrupt_status(v2d_num, apb_num);

    if ((underrun_reg_value >> 12) & 0x1)
    {
        printf("HOST: Underrun flag was set\n");
    }
    else
    {
        printf("ERROR: Underrun flag was not set, value 0x%x\n", underrun_reg_value);
        test_status = 1;
    }

    /*Read the underrun Sample*/
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_vbuffer,/*local_addr*/
                        underrun_sample,
                        sizeof(underrun_sample)))
        return rv;

    host_flag = 1;
    /*signal VEX to start continuous flow*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_underrun_a_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    usleep(1000);
    b2h_flit_cnt = 0;

    /* Wait until you get required number of flits transferred through NSIP module from VEX to V2D*/
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, \
                    "B2H_FLIT_COUNT")) < (g_initial_block_size * g_flow1_vectors_per_block[sys_rate] * 2))
    {
        // do nothing wait in this loop
        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT 0x%x is not the required number of flits\n", b2h_flit_cnt);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    /*Read the underrun Sample*/
    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_underrun_a_rx_p5_8iq_vbuffer,/*local_addr*/
                        underrun_sample_new,
                        sizeof(underrun_sample_new)))
        return rv;

    if (0 == data_compare(underrun_sample, underrun_sample_new, ARRAY_SIZE(underrun_sample)))
    {
        printf("HOST: underrun sample check was passed\n");
    }
    else
    {
        printf("HOST:---FAIL--- underrun sample check was failed\n");
    }

    if (rv = interrupt_status_check(v2d_num, apb_num, TX_UNDERRUN_VALUE, 0, 0))
    {
        printf("ERROR: interrupt check failed\n");
        test_status = 1;
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, sys_rate : %s\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, sys_rate : %d\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
        rv = 1;
    }

    return rv;
}
