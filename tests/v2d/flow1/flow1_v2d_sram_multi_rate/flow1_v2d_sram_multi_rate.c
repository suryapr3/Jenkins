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
 * @file    flow1_v2d_sram_multi_rate.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D and receving it back.
 * @details 1. Completley fill the V2D SRAM and check the data integrity for all
 *             valid sample rates.
            2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
        1. 32K samples (1K vectors) for given data rate will be streamed to V2D from
           configured VEX core.
        2. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        3. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        4. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS

#include "flow1_common_utils.h"
#include "common_utils.h"

#include "v2d_flow1_tx.map.h"
#include "v2d_flow1_rx_p25iq.map.h"
#include "v2d_flow1_rx_p5_8iq.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
/*SRAM is of size of 1024 vectors*/
#define MAX_BLOCKS (1024 / g_flow1_vectors_per_block[sys_rate])
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int g_initial_block_size = 3;
/* The value should be number of blocks required for 32K samples i.e 1024 vectors defined as per order in sys_rate_t enum */

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last 5 entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    // These are for Buffer A0
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    /* Value should be 2 blocks of data for any rate*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow1_rx_p5_8iq_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 5 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x6000 later it will be modified with the value which corresponds to map file*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer_out), \
        NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET, 0x7, NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK, "H2B_MD_CTRL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last Three entries order shouldn't be modified*/
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A0 for 2048 flits filling entire SRAM*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},

    /************************************************************************************************************/
    /* The last three entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, 0x200, AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STRM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STREAM_CNT0"}
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
/*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 3 * VEC2FLIT(g_flow1_vectors_per_block[sys_rate]);
    printf("fill_level_value : 0x%x\n", fill_level_value);
#endif
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


    for (i = 0; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), (0x80000000 | HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer_out),\
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

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 3); i++)
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

#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
#endif

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_VALUE_SRAM, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), RX_GNRL_CSR_VALUE, \
            AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[1]) + VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_flow1_rx_p5_8iq_consumer_sm_gate, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    return rv;
}

int main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int vex_num_param[2] = {0}, v2d_num, apb_num, host_flag = 1, test_status = 0, loop_wait_count = 0, drf_clock = 0,
        host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
    sys_rate_t sys_rate;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;

    int dmem_offset = DMEM_OFFSET;
    int offset_val[] = {HIVE_ADDR_v2d_flow1_tx_g_scalar_val, HIVE_ADDR_v2d_flow1_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow1_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow1_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow1_tx_g_host_cycle_count};
    unsigned int val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_scalar_val, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_blocks, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_count1};
    unsigned int vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];

    init(); /* Initialize the srp*/

    LOG_PRINT("INFO: logger beginning");
    printf("INFO: argc : %d", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    v2d_num = argv[2];
    apb_num = argv[3];
    drf_clock = (int) argv[4];
    sys_rate = (int) argv[5];

    printf ("INFO: argv[0] : %d = tx_vex", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx_vex", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[3] : %d = apb_num", apb_num);
    printf ("INFO: argv[4] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[5] : %d = sys_rate %d", sys_rate, sys_rate);

    add_val[0] = val_kargs[0];
    val_kargs[3] = 1024 / g_flow1_vectors_per_block[sys_rate];
    val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[2] =1024 / g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    //This value should be numberof blocks that were configured in the VEX memory to hold
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;
    if (rv = v2d_clk_enable(v2d_num, apb_num))
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
    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock,sys_rate))
    {
        printf ("ERROR: configure_v2d_host");
        return rv;
    }

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed");
        return rv;
    }

    /*Clearing the VEX VMEM and DMEM for both Tx and Rx vex cores*/
    if (rv = vex_mem_clear(vex_num_param[0], srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[0]);
        return rv;
    }
    if (rv = vex_mem_clear((vex_num_param[1]), srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num_param[1]);
        return rv;
    }

    printf("Host: start vex program load \n");
    if ((rv = vex_loader(vex_num_param[0], "vex_fw/sim_m64/v2d_flow1_tx.fw")))
        return rv;

    /* The VEX Rx FW code is sample rate dependent, hence loading different fw files for different
     * sample rates*/
    if (SYS_RATE_IQ_P25 == sys_rate)
    {
        if ((rv = vex_loader(vex_num_param[1], "vex_fw/sim_m64/v2d_flow1_rx_p25iq.fw")))
            return rv;
    }
    else
    {
        if ((rv = vex_loader(vex_num_param[1], "vex_fw/sim_m64/v2d_flow1_rx_p5_8iq.fw")))
            return rv;
    }
    printf("Host: vex program load - done\n");

        /* Loading the host parameters to VEX  Tx core*/
    if (load_vex_param(vex_num_param[0]/*vex_core*/, ARRAY_SIZE(offset_val)/*size of array*/, offset_val, val_kargs))
    {
        LOG_ERROR("Tx vex param loading failed");
    }

    /* Loading the host parameters to VEX  Rx core*/
    if (load_vex_param(vex_num_param[1] /*vex_core*/, ARRAY_SIZE(vex_rx_offset_val), vex_rx_offset_val, vex_rx_val_kargs))
    {
        LOG_ERROR("Rx vex param loading failed");
    }
    for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = ((i*NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j);
        }   // for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++) ends
    }   // for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++) ends

     write_mem_18a(VEX_VMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow1_tx_vbuffer,/*local_addr*/
                        (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC),
                        val_inp[0],
                        "VEX_VMEM");
      write_mem_18a(VEX_VMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer,/*local_addr*/
                   (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC), val_inp[0],
                    "VEX_VMEM");

    printf("Host: vex program start\n");
    vex_start(vex_num_param[1], 0); // RX VEX
    vex_start(vex_num_param[0], 0); // Tx VEX

    printf("Host: vex program start - done\n");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, "B2H_FLIT_COUNT")) <
            (3 * g_flow1_vectors_per_block[sys_rate] * 2))
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
    printf ("b2h_flit_cnt : %d\n", b2h_flit_cnt);

    /*signal VEX to start continuous flow*/
    if (rv = write_reg_18a(VEX_DMEM(vex_num_param[0]) + HIVE_ADDR_v2d_flow1_tx_g_host_indicator,
                    host_flag, 0xFFFFFFFF, "HOST_INDICATION"))
    {
        LOG_ERROR("Host Indication failed");
        return rv;
    }

    /* Triggering the forced BFN*/
    if (rv = tx_start_bfn_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }
#endif

    loop_wait_count = 0;
    usleep(10000);

    while ((h2b_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "H2B_FLIT_COUNT"))  <
            (((1024 / g_flow1_vectors_per_block[sys_rate]) * (g_flow1_vectors_per_block[sys_rate] * 2))))
    {

        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while H2B_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);

    }
    printf ("h2b_flit cnt is %d\n", h2b_flit_cnt);

    loop_wait_count = 0;
    usleep(10000);

    while (host_vec_processed < ((1024 / g_flow1_vectors_per_block[sys_rate]) * g_flow1_vectors_per_block[sys_rate]))
    {
        host_vec_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_count1, "vec_processed");
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
    host_result = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_compare_result, "compare_result");
    host_blocks_processed = read_reg_18a(VEX_DMEM(vex_num_param[1]) + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_add_val_out, "blocks_processed");

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

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 3 * VEC2FLIT(g_flow1_vectors_per_block[sys_rate]);

    /*Checking whether fill level was triggered properly or not*/
    fill_level_check(v2d_num, apb_num, fill_level_value);
#endif

    if (rv = interrupt_status_check(v2d_num, apb_num, TX_UNDERRUN_VALUE, 0, 0))
    {
        printf("ERROR: interrupt check failed\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Interrupt check passed\n");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, sys_rate : %s\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx_vex_num : %d, rx_vex_num : %d, v2d_num : %d, apb_num : %d, drf_clock : %s, sys_rate : %s\n",
                vex_num_param[0], vex_num_param[1], v2d_num, apb_num, drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
        rv = 1;
    }

    return rv;
}   // main ends
