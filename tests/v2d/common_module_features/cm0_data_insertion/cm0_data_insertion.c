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
 * @file    cm0_data_insertion.c
 * @brief   HOST Configuration code for validating the data insertion feature in CM0
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
        6. The insert feature will be enabled after the initial INSERT_BLOCKS_START blocks and again disabled at
           INSERT_BLOCKS_END block boundries, during insertion period a constant data will be streamed by CM.
        7. During Insertion period , VEX won't send any data towards V2D and the next block after the
           insertion period ends will be sent in a timely manner by VEX.
        8. After insertion period ends VEX will be continuously sending the data untill it receives
           indication from HOST to stop the transmission.
        9. The Drop feature will be enabled at (INSERT_BLOCKS_END + 1) block onwards.
        10. Rx VEX will do the integrity check for the initial 100 blocks and later 500 insertion blocks
           and for the first block after insertion stops.
        11. The supported Sample rates are[0.25IQ , 16R]
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

#define INSERT_BLOCKS_START    0x64
#define INSERT_BLOCKS_END 0x1F4
#define INSERT_BLOCKS (INSERT_BLOCKS_END - INSERT_BLOCKS_START)
#define INSERT_SAMPLE   0xDEADBEAF
#define NSIP0_STATUS_VALUE   NSIP_HBI_INTR_INT_STATUS_B2H_INSERT_VEX_DROP_BF_MSK
#define MAX_BLOCKS  1000
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int g_num_blocks_v2d_buffer = 3;

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last six entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, \
        "B2H_CREDIT_CS"},
    // These are for Buffer A0
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},
    // Configuration for insertion
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_INSERT_STREAM_OFFSET), NSIP_HBI_B2H_CSR_B2H_INSERT_STREAM_DEFAULT, \
        NSIP_HBI_B2H_CSR_B2H_INSERT_STREAM_WR_MASK, "B2H_INSERT_STREAM_MAP"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INSERT_QUEUE_CSR0_B2H_INSERT_NULL_SAMPLE_OFFSET), INSERT_SAMPLE, \
        NSIP_HBI_INSERT_QUEUE_CSR_B2H_INSERT_NULL_SAMPLE_WR_MASK, "B2H_INSERT_NULL_SAMPLE"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INSERT_QUEUE_CSR0_CMD_INSERT_STREAM_EN_OFFSET, 0x1, NSIP_HBI_INSERT_QUEUE_CSR_CMD_INSERT_STREAM_EN_WR_MASK, \
        "B2H_CMD_INSERT_STREAM_EN"},
    /*Command to start the insertion*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INSERT_QUEUE_CSR0_CMD_INSERT_CONTROL_OFFSET, 0x80000000 | (INSERT_BLOCKS_START), \
        NSIP_HBI_INSERT_QUEUE_CSR_CMD_INSERT_CONTROL_WR_MASK, "B2H_CMD_INSERT_CONTROL"},
    /*Command to stop the insertion*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INSERT_QUEUE_CSR0_CMD_INSERT_CONTROL_OFFSET, (INSERT_BLOCKS_END), \
        NSIP_HBI_INSERT_QUEUE_CSR_CMD_INSERT_CONTROL_WR_MASK, "B2H_CMD_INSERT_CONTROL"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
     /* Value should be 2 blocks of data for any rate */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow1_rx_p5_8iq_consumer_sm_gate), NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    /* Configuration for droping the data*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_DROP_CMD0_CMD_DROP_STREAM_EN_OFFSET, 0x1, NSIP_HBI_DROP_CMD_DROP_STREAM_EN_WR_MASK, \
        "H2B_CMD_DTROP_STREAM_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_DROP_CMD0_CMD_DROP_CONTROL_OFFSET, 0x80000000 | (INSERT_BLOCKS_END + 1), NSIP_HBI_DROP_CMD_DROP_CONTROL_WR_MASK, \
        "H2B_CMD_DROP_CONTROL"},
    /***********************************************************************************************************************************/
    /*These last 6 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INSERT_QUEUE_CSR0_B2H_INSERT_CSR_OFFSET), NSIP_HBI_INSERT_QUEUE_CSR_B2H_INSERT_CSR_USE_NULL_BF_MSK, \
        NSIP_HBI_INSERT_QUEUE_CSR_B2H_INSERT_CSR_WR_MASK, "B2H_INSERT_CSR_OFFSET"},
    /* Data will be written to VEX location 0x6100 , i.e VEX VMEM location 0x6100*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80006100, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
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
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, 0x200, AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
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
 * @param [in]      pointer to Vex Id array, V2d Id, APB Id , drf_clock and sys_rate
 * @return          status
 */
int configure_v2d_host(int *vex_num, int v2d_num, int apb_num, int drf_clock, sys_rate_t sys_rate)
{
    int i, rv = 0, insert_csr_value = 0;

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = (VEC2FLIT(g_flow1_vectors_per_block[sys_rate])) + g_flow1_vectors_per_block[sys_rate];
#endif

    if (CLOCK_983M == drf_clock)
    {
        insert_csr_value = (((CYCLES_PER_BLOCK_983M - 1) << 10) | g_flow1_md_control_tbl[sys_rate]);
    }
    else
    {
        insert_csr_value = (((CYCLES_PER_BLOCK_1P5G - 1) << 10) | g_flow1_md_control_tbl[sys_rate]);
    }

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

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 6); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i< (ARRAY_SIZE(g_cm_0_config_tbl) - 5); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value | insert_csr_value, \
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

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    ((((g_num_blocks_v2d_buffer) * (g_flow1_vectors_per_block[sys_rate] * 2)) - 1) << 16), g_v2d_config_tbl[i].mask, \
                    g_v2d_config_tbl[i].name))
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
        host_vec_processed = 0, host_blocks_processed = 0;
    sys_rate_t sys_rate;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;

    int dmem_offset = DMEM_OFFSET;
    int offset_val[] = {HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_scalar_val, HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_dest_buffer_base, HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_num_blocks,
                         HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_insert_start_block, HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_insert_stop_block,
                         HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_cycle_count};
    unsigned int val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, INSERT_BLOCKS_START, INSERT_BLOCKS_END, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_scalar_val, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_vecs_in,
                               HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_num_blocks, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_tbs_in_blk,
                               HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_count1, HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_data_insert_block_start,
                               HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_data_insert_block_end};
    unsigned int vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0, INSERT_BLOCKS_START, INSERT_BLOCKS_END};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0}, watermark_buf[MAX_NUM_STREAMS] = {0};
    unsigned int insert_pattern[2 * NUM_OF_ELEMENTS_PER_VEC] = {0}, host_output[NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1], fifo_ptr[2];

    init(); /* Initialize the srp*/

    LOG_PRINT("INFO: logger beginning\n");
    printf("INFO: argc : %d\n", argc);

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
    val_kargs[3] = MAX_BLOCKS;
    val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[2] = MAX_BLOCKS;
    vex_rx_val_kargs[1] = g_flow1_vectors_per_block[sys_rate];
    vex_rx_val_kargs[3] = NUM_DATA_BLOCKS;

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }
    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, drf_clock,sys_rate))
    {
        printf ("ERROR: configure_v2d_host\n");
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

    printf("Host: start vex Rx program load \n");

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

    printf("Host: start vex Tx program load \n");
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
    printf("Host: vex program load - done\n");

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

    /*Generating the input pattern*/
    for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = ((i*NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j);
        }   // for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++) ends
    }   // for (i = 0; i < g_flow1_vectors_per_block[sys_rate]; i++) ends

    /*populating the insert pattern*/
    for (i = 0; i < ARRAY_SIZE(insert_pattern); i++)
    {
        insert_pattern[i] = INSERT_SAMPLE;
    }

    /*Loading the input test Vectors to Tx vex*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_tx_p25_4iq_vbuffer,/*local_addr*/
                        val_inp[0],
                        (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Loading the insert test pattern to Tx vex*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_rx_p5_8iq_vinsert_pattern_buffer,/*local_addr*/
                        insert_pattern,
                        (2 * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Loading the REF test Vectors to Rx vex*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                         vex_num_param[1],
                         SRP_VEX_VMEM,
                         HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer,/*local_addr*/
                         val_inp[0],
                         (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
         return rv;

    /*Read the FIFO_PTR field in INSERT_CSR registers to check the command queue depth*/
    get_nsip0_insert_fifo_ptr(v2d_num, apb_num, 1/*num of command queus used*/, fifo_ptr);

    if (2 != fifo_ptr[0])   // The first entry to the FIFO will be popped immediatly once the data was written
    {
        printf("WARNING: fifo_ptr depth is not proper\n");
    }

    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, vex_num_param[1], 0); // Rx VEX Core
    srp_vex_start(vex_hdl, vex_num_param[0], 0); // Tx VEX Core
    printf("Host: vex program start - done\n");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if !FILL_LEVEL_TRIGGER
    usleep(10000);
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, \
                    "B2H_FLIT_COUNT")) <
            ((g_flow1_vectors_per_block[sys_rate] * 2) + g_flow1_vectors_per_block[sys_rate]))
    {
        // do nothing wait until 1.5 blocks are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf("HOST: b2h flit cnt: %d\n",b2h_flit_cnt);

    /*signal VEX to start continuous flow*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    /*Triggering the forced BFN*/
    if (rv = tx_start_bfn_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }
#endif

    /*Wait untill INSERT_BLOCK_START blocks reached the B2H to read the insert state*/
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, \
                    "B2H_FLIT_COUNT")) <
            ((INSERT_BLOCKS_START * (g_flow1_vectors_per_block[sys_rate] * 2))))
    {

        if (loop_wait_count >= 80)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT count 0x%x is not the required number of flits\n", b2h_flit_cnt);
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }

    int insertion_state;
    insertion_state = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_INSERT_STATE_OFFSET, \
            "INSERT_STATE");

    if (1 != insertion_state)
    {
        printf("WARNING: Insert state : 0x%x is not set\n", insertion_state);
    }

    loop_wait_count = 0;

    /*Rx VEX will process only the remaining vectors which are not dropped by CM and wait till those many
     * vectors are processed*/
    while (host_vec_processed < ((INSERT_BLOCKS_START + 1) * g_flow1_vectors_per_block[sys_rate]))
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
            printf("ERROR: VEX core didn't processed enough vectors, processed vectors: 0x%x\n", host_vec_processed);
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

    if ((rv = srp_dev_block_read32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[1],
                    dmem_offset + HIVE_ADDR_v2d_flow1_rx_p5_8iq_g_add_val_out,
                    &host_blocks_processed,
                    1,
                    flags)))
        return rv;

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x\n", host_vec_processed / g_flow1_vectors_per_block[sys_rate]);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV\n");
        test_status = 1;
    }
    else
    {
        printf("HOST: Received output matches with Reference output\n");
    }

    if (rv = srp_vex_memid_load(vex_hdl,
                        vex_num_param[1],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_rx_p5_8iq_vbuffer_out,/*local_addr*/
                        host_output,
                        sizeof(host_output)))
        return rv;

    /*Read the FIFO_PTR field in INSERT_CSR registers to check the command queue depth*/
    get_nsip0_insert_fifo_ptr(v2d_num, apb_num, 1/*num of command queus used*/, fifo_ptr);

    if (1 != fifo_ptr[0])   //1 means the FIFO is empty
    {
        printf("WARNING: fifo is not empty\n");
    }

    /* As the TX VEX cores are continuously transmitting no underrun should be set*/
    if (rv = interrupt_status_check(v2d_num, apb_num, 0/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: interrupt check failed\n");
        test_status |= 1;
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(g_flow1_vectors_per_block[sys_rate]) + g_flow1_vectors_per_block[sys_rate];

    /*Checking whether fill level was triggered properly or not*/
    fill_level_check(v2d_num, apb_num, fill_level_value);
#endif

    /* Get the watermark high , low values for V2D Buffers*/
    if (rv = get_tx_wm_hilo(v2d_num, apb_num, 1/*Number of streams*/, watermark_buf))
    {
        printf("ERROR: get_tx_pdpd_wm_hilo failed\n");
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

    /*Signal from host to stop continuous flow on B Tx Vex Core , which in turn will signal the C Tx Vex core to stop continuous transmission*/
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num_param[0],
                    dmem_offset + HIVE_ADDR_v2d_flow1_tx_p25_4iq_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    usleep(10000);

    /*As VEX cores stopped transmitting the underrun interrupt should be set now*/
    if (rv = interrupt_status_check(v2d_num, apb_num, TX_UNDERRUN_VALUE, 0/*NSIP0 value*/, 0/*NSIP1 value*/))
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
