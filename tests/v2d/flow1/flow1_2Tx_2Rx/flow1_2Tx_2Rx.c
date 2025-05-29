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
 * @file    flow1_2Tx_2Rx.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D via path A from two VEX Cores
 *          and receving it back to two VEX Cores via path F.
 * @TC Description:
        1. 0.5 usec long block (L) is split between  two Tx and two Rx vex cores in the ratio 1:1(equal split) or 3:1(unequal split)
           by split_method parameter. In other words the split is L/2:L/2 or 3L/4:L/4.
        2. V2D memory will be configured for 3 times of the block size of corresponding
           sample rate for A0 and A1.
        3. With Rx loop back enabled the data looped back at sample interface
           was expected to reach the two Rx VEX cores in the same split ration of Tx VEX cores
           where comparison will be performed.
        4. Two Rx VEX cores on which comparison algo was running will update the comparison result for
           every vector comparison and once the total vector comparison was done HOST will
           read the result.
        5. Host will be waiting on a memory location where Two Rx VEX cores will update the number of vectors
           it was processed.
        6. The supported Sample rates are
           8IQ and 16R
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow1_common_utils.h"
#include "common_utils.h"

#include "v2d_flow1_tx.map.h"
#include "v2d_flow1_rx.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define MAX_BLOCKS 1000
#define B2H_ADD_MAP_B2_OFFSET  0x10000
#define NUM_VEX_CORES   4
#define NUM_TX_VEX_CORES    2
#define NUM_RX_VEX_CORES    (NUM_VEX_CORES - NUM_TX_VEX_CORES)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

const char *g_vex_fw_binary[] = {"vex_fw/sim_m64/v2d_flow1_tx.fw", "vex_fw/sim_m64/v2d_flow1_rx.fw", "vex_fw/sim_m64/v2d_flow1_unequal_split_tx1.fw"};

int g_initial_blocks = 3;    // This corresponds to 1L and VEX will transfer 2.5L before BFN trigger.
int g_num_blocks_v2d_buffer = 3;    /* This corresponds to 3L which is total buffer size allocated in the
                                       32K sample V2D buffer space.*/

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last ten entries order shouldn't be modified*/
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
    // Mask was set for total 1K flits in words
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0xFFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
    // These are for Buffer A1
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET), (0x80000000 | B2H_ADD_MAP_B2_OFFSET), NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL1"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL1"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},

    /* Value should be 2 blocks of data for any rate */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow1_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    /* value should be 2 blocks of data for any rate */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL1"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow1_rx_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL1"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL1"},
    /***********************************************************************************************************************************/
    /*These last 10 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow1_rx_vbuffer_out), \
        NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET, (NSIP_HBI_H2B_ADDR_LKUP_TBL_VALID_BF_MSK | HIVE_ADDR_v2d_flow1_rx_vbuffer_out), \
        NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0x7, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CONTROL_TBL1_OFFSET, 0x7, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL1"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL1"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET, 0x1, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL1"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last Seven entries order shouldn't be modified*/
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE_2STREAM, \
        AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},

    /************************************************************************************************************/
    /* The last Seven entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/

    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x3FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND1_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND1"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STREAM_CNT1_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STREAM_CNT_WR_MASK, "TX_STREAM_CNT1"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STREAM_CNT1_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STREAM_CNT_WR_MASK, "RX_STREAM_CNT1"}
    /************************************************************************************************************/
};



/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int configure_v2d_host(int[], int, int, int, int, sys_rate_t);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id[], V2d Id, APB Id, split_method and sys_rate
 * @return          status
 */
int configure_v2d_host(int vex_num[], int v2d_num, int apb_num, int split_method, int drf_clock, sys_rate_t sys_rate)
{
    int i, j, rv = 0, v2d_stream_cnt0 = 0, v2d_stream_cnt1 = 0, md_control0 = 0, md_control1 = 0,
        v2d_tx_ptr_bound0 = 0, v2d_tx_ptr_bound1 = 0, vex_index = 0;

    if (SPLIT_METHOD_EQUAL == split_method)  // equal split
    {
        v2d_stream_cnt0 = (g_flow1_vectors_per_block[sys_rate] - 1);
        v2d_stream_cnt1 = (g_flow1_vectors_per_block[sys_rate] - 1);
    }
    else if (SPLIT_METHOD_UNEQUAL == split_method)   // split in 3:1 ratio i.e 3/4 th by first VEX and 1/4th by second VEX cores
    {
        v2d_stream_cnt0 = (((VEC2FLIT(g_flow1_vectors_per_block[sys_rate]) / 4) * 3) - 1);
        v2d_stream_cnt1 = ((VEC2FLIT(g_flow1_vectors_per_block[sys_rate]) / 4) - 1);
    }

    // Derive the MD_CONTROL_TBL which is used to send the tokenss from V2D to destination VEX
    md_control0 = v2d_stream_cnt0;
    md_control1 = v2d_stream_cnt1;

    // Derive V2D Tx PTR BOUND values from the stream counts.
    v2d_tx_ptr_bound0 = ((g_num_blocks_v2d_buffer * (v2d_stream_cnt0 + 1)) - 1) << 16;
    v2d_tx_ptr_bound1 = (((g_num_blocks_v2d_buffer * g_flow1_vectors_per_block[sys_rate] * 2) - 1) << 16) |
                            (g_num_blocks_v2d_buffer * (v2d_stream_cnt0 + 1));

    printf("v2d_tx_ptr_bound0 : 0x%x\n v2d_tx_ptr_bound1 : 0x%x\n", v2d_tx_ptr_bound0, v2d_tx_ptr_bound1);

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = (v2d_stream_cnt0 + 1) + ((v2d_stream_cnt0 + 1) / 2);
    printf("fill_level_value : 0x%x\n", fill_level_value);
#endif

    for (j = 0; j < NUM_TX_VEX_CORES; j++)
    {
        vex_index = (j * 2);
        for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
       {
            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[vex_index]) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
                return rv;
        }
        // Corresponds to cio2strm dest id
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[vex_index]) + g_cio2strm_config_tbl[i].offset, g_v2d_host_id[v2d_num][apb_num][0], \
                    g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
        printf("INFO: cio2strm configuration completed for vex %d\n", vex_num[vex_index]);

        /*vex_index corresponds to RX vex core*/
        vex_index = vex_index + 1;
        for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
        {

            if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[vex_index]) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
                        g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
                return rv;
        }
        printf("INFO: strm2cio configuration completed");

        // SDF init
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num[vex_index]) + VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                    HIVE_ADDR_v2d_flow1_rx_consumer_sm_gate, VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
            return rv;
        printf ("INFO: SDF configuration completed for VEX%d",vex_num[vex_index]);
    }

    for (i = 0; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 10); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i < (ARRAY_SIZE(g_cm_0_config_tbl) - 8); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), (0x80000000 | HIVE_ADDR_v2d_flow1_rx_vbuffer_out), \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 7); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), md_control0,\
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 6); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), md_control1,\
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[1], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num[3], \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    printf ("INFO: CM configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 7); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 6; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    v2d_tx_ptr_bound0, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    v2d_tx_ptr_bound1, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value | (drf_clock << 7) | sys_rate, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl) - 2; i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), (0x80000000 | v2d_stream_cnt0), \
                g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), (0x80000000 | v2d_stream_cnt1), \
                g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
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

    return rv;
}

/**
 * @brief           Function populating the parameters to be provided to
 *                  VEX cores
 * @param [in]      vex0_tx_args, vex1_tx_args, vex0_rx_args, vex1_rx_args and split_method, sys_rate
 * @return          none
 */
void vex_param_gen (unsigned int *vex0_tx_args, unsigned int *vex1_tx_args,
        unsigned int *vex0_rx_args, unsigned int *vex1_rx_args, int split_method, sys_rate_t sys_rate)
{
    vex0_tx_args[3] = MAX_BLOCKS;
    vex1_tx_args[3] = MAX_BLOCKS;
    vex0_rx_args[2] = MAX_BLOCKS;
    vex1_rx_args[2] = MAX_BLOCKS;
    vex1_tx_args[2] = B2H_ADD_MAP_B2_OFFSET; // in bytes
    vex0_tx_args[5] = g_initial_blocks;
    vex1_tx_args[5] = g_initial_blocks;
    vex0_rx_args[4] = 1;
    vex1_rx_args[4] = 1;

    if (SPLIT_METHOD_EQUAL == split_method)  // equal split
    {
        vex0_tx_args[1] = g_flow1_vectors_per_block[sys_rate] / 2;
        vex1_tx_args[1] = g_flow1_vectors_per_block[sys_rate] / 2;
        vex0_rx_args[1] = vex0_tx_args[1];
        vex1_rx_args[1] = vex1_tx_args[1];
        vex0_rx_args[3] = NUM_DATA_BLOCKS;
        vex1_rx_args[3] = NUM_DATA_BLOCKS;
    }
    else if (SPLIT_METHOD_UNEQUAL == split_method)   // split in 3:1 ratio i.e 3/4 by first VEX and 1/4 by second vex
    {
        vex0_tx_args[1] = (g_flow1_vectors_per_block[sys_rate] / 4) * 3;
        vex1_tx_args[1] = g_flow1_vectors_per_block[sys_rate] / 4;
        vex0_rx_args[1] = vex0_tx_args[1];
        vex1_rx_args[1] = vex1_tx_args[1];
        vex0_rx_args[3] = NUM_DATA_BLOCKS;
        vex1_rx_args[3] = NUM_DATA_BLOCKS;
    }
}

/**
 * @brief           Function generating the input TV's
 * @param [in]      pointers to tx0, tx1 buffers, vex0_input_vectors and sys_rate
 * @return          none
 */
void input_vec_gen (unsigned int (*val_inp_tx0)[NUM_OF_ELEMENTS_PER_VEC], unsigned int (*val_inp_tx1)[NUM_OF_ELEMENTS_PER_VEC],
        unsigned int vex0_num_input_vectors, sys_rate_t sys_rate)
{

    int i, j;

    for (i = 0; i < vex0_num_input_vectors; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp_tx0[i][j] = ((i*NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j);
        }   // for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++) ends
    }   // for (i = 0; i < vex0_num_input_vectors; i++) ends

    for (i = vex0_num_input_vectors; i < g_flow1_vectors_per_block[sys_rate]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp_tx1[i - vex0_num_input_vectors][j] = ((i*NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j);
        }   // for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++) ends
    }   //(i = vex0_tx_args[1]; i < vex0_num_input_vectors; i++) ends
}


int main(int argc, const char *argv[])
{
    int rv = 0, test_status = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num_param[NUM_VEX_CORES] = {0}, vex_cnt = 0, v2d_num, apb_num, host_flag = 1, split_method = SPLIT_METHOD_EQUAL,
        loop_wait_count = 0, drf_clock=0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
    sys_rate_t sys_rate;
    volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0;

    int dmem_offset = DMEM_OFFSET;
    int offset_val[] = {HIVE_ADDR_v2d_flow1_tx_g_scalar_val, HIVE_ADDR_v2d_flow1_tx_g_num_vecs_in,
                         HIVE_ADDR_v2d_flow1_tx_g_dest_buffer_base, HIVE_ADDR_v2d_flow1_tx_g_num_blocks,
                         HIVE_ADDR_v2d_flow1_tx_g_tx_instance, HIVE_ADDR_v2d_flow1_tx_g_initial_block_size,
                         HIVE_ADDR_v2d_flow1_tx_g_host_cycle_count};
    unsigned int vex0_tx_args[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, 0, 0, (CYCLES_PER_BLOCK_983M - 1)};
    unsigned int vex1_tx_args[] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, 1, 0, (CYCLES_PER_BLOCK_983M - 1)};
    int vex_rx_offset_val[] = {HIVE_ADDR_v2d_flow1_rx_g_scalar_val, HIVE_ADDR_v2d_flow1_rx_g_num_vecs_in,
                                HIVE_ADDR_v2d_flow1_rx_g_num_blocks, HIVE_ADDR_v2d_flow1_rx_g_tbs_in_blk,
                                HIVE_ADDR_v2d_flow1_rx_g_tokens_per_block, HIVE_ADDR_v2d_flow1_rx_g_count1};
    unsigned int vex0_rx_args[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 1, 0};
    unsigned int vex1_rx_args[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 1, 0};
    unsigned int val_inp_tx0[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int val_inp_tx1[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];

    init(); /* Initialize the srp*/

    LOG_PRINT("INFO: logger beginning\n");
    printf("INFO: argc : %d\n", argc);

    vex_num_param[0] = argv[0];
    vex_num_param[1] = argv[1];
    vex_num_param[2] = argv[2];
    vex_num_param[3] = argv[3];
    v2d_num = argv[4];
    apb_num = argv[5];
    split_method = argv[6];
    drf_clock = (int) argv[7];
    sys_rate = (int) argv[8];

    printf ("INFO: argv[0] : %d = tx0_vex\n", vex_num_param[0]);
    printf ("INFO: argv[1] : %d = rx0_vex\n", vex_num_param[1]);
    printf ("INFO: argv[2] : %d = tx1_vex\n", vex_num_param[2]);
    printf ("INFO: argv[3] : %d = rx1_vex\n", vex_num_param[3]);
    printf ("INFO: argv[4] : %d = v2d_num\n", v2d_num);
    printf ("INFO: argv[5] : %d = apb_num\n", apb_num);
    printf ("INFO: argv[6] : %d = split_method\n", split_method);
    printf ("INFO: argv[7] : %d = drf_clock %s\n", drf_clock, drf_clock_str[drf_clock]);
    printf ("INFO: argv[8] : %d = sys_rate %s\n", sys_rate, sys_rate_str[sys_rate]);

    add_val[0] = vex0_tx_args[0];

    vex_param_gen(vex0_tx_args, vex1_tx_args, vex0_rx_args, vex1_rx_args, split_method, sys_rate);

    for (lc = 0; lc < ARRAY_SIZE(vex0_tx_args); lc++)
    {
        printf("vex0_tx_args[%d]: %d\n", lc, vex0_tx_args[lc]);
        printf("vex1_tx_args[%d]: %d\n", lc, vex1_tx_args[lc]);
    }

    for (lc = 0; lc < ARRAY_SIZE(vex0_rx_args); lc++)
    {
        printf("vex0_rx_args[%d]: %d\n", lc, vex0_rx_args[lc]);
        printf("vex1_rx_args[%d]: %d\n", lc, vex1_rx_args[lc]);
    }

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    /*Enable the V2D clock*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num_param, v2d_num, apb_num, split_method, drf_clock, sys_rate))
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
    for (lc = 0; lc < ARRAY_SIZE(vex_num_param); lc++)
    {
        int vex_num = vex_num_param[lc];

        if (rv = vex_mem_clear(vex_num, srp))
        {
            printf("ERROR: vex_mem_clear failed for vex:%d\n", vex_num);
            return rv;
        }
    }

    /*Generating the parameters to VEX*/
    input_vec_gen(val_inp_tx0, val_inp_tx1, vex0_tx_args[1], sys_rate);

    printf("Host: start vex program load \n");

    // If it is equal split both Tx VEX cores will be loaded with same VEX FW in case of
    // unequal split Tx0 will be loaded with v2d_flow1_tx.fw and Tx1 will be loaded with
    // unequal_split_tx1.fw
    for (vex_cnt = 0; vex_cnt < ARRAY_SIZE(vex_num_param); vex_cnt++)
    {
        int vex_num = vex_num_param[vex_cnt];

        if ((rv = srp_vex_loader(vex_hdl, vex_num, g_vex_fw_binary[vex_cnt % 2])))
            return rv;
    }

    if (SPLIT_METHOD_UNEQUAL == split_method)
    {
        if ((rv = srp_vex_loader(vex_hdl, vex_num_param[2], g_vex_fw_binary[2])))
            return rv;
    }
    printf("Host: vex program load - done for vex\n");

    /* Loading the host parameters to VEX Tx cores*/
    for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[0],
                        dmem_offset + offset_val[lc],
                        &vex0_tx_args[lc],
                        1,
                        flags)))
            return rv;

        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[2],
                        dmem_offset + offset_val[lc],
                        &vex1_tx_args[lc],
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
                        &vex0_rx_args[lc],
                        1,
                        flags)))
            return rv;

        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num_param[3],
                        dmem_offset + vex_rx_offset_val[lc],
                        &vex1_rx_args[lc],
                        1,
                        flags)))
            return rv;
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /*Loading the input vectors to Tx and Rx VEX cores*/
    /* First Tx Vex Core*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[0],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_tx_vbuffer,/*local_addr*/
                        val_inp_tx0[0],
                        (vex0_tx_args[1] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /*Second Tx VEX core*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                        vex_num_param[2],
                        SRP_VEX_VMEM,
                        HIVE_ADDR_v2d_flow1_tx_vbuffer,/*local_addr*/
                        val_inp_tx1[0],
                        (vex1_tx_args[1] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    /* First Rx VEX Core*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                         vex_num_param[1],
                         SRP_VEX_VMEM,
                         HIVE_ADDR_v2d_flow1_rx_vbuffer,/*local_addr*/
                         val_inp_tx0[0],
                         (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
         return rv;

    /*Second Rx VEX Core*/
    if ((rv = srp_vex_memid_store(vex_hdl,
                         vex_num_param[3],
                         SRP_VEX_VMEM,
                         HIVE_ADDR_v2d_flow1_rx_vbuffer,/*local_addr*/
                         val_inp_tx1[0],
                         (g_flow1_vectors_per_block[sys_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
         return rv;


    printf("Host: vex program start\n");
    srp_vex_start(vex_hdl, vex_num_param[1], 0);    // Rx0 VEX
    srp_vex_start(vex_hdl, vex_num_param[0], 0);    // Tx0 VEX
    srp_vex_start(vex_hdl, vex_num_param[3], 0);    // Rx1 VEX
    srp_vex_start(vex_hdl, vex_num_param[2], 0);    // Tx1 VEX
    printf("Host: vex program start - done\n");

    usleep(10000);

#if !FILL_LEVEL_TRIGGER
    while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
            (g_initial_blocks * VEC2FLIT(g_flow1_vectors_per_block[sys_rate])) + VEC2FLIT(vex0_tx_args[1]/2))
    {
        // do nothing wait until required samples (1 Complete A0+A1 and 1/2 of A0) are received in this loop
        if (loop_wait_count >= 30)
        {
            printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits\n");
            break;
        }
        loop_wait_count ++;
        usleep(10000);
    }
    printf("HOST: b2h flit cnt: %d\n",b2h_flit_cnt);


    host_flag = 1;

    /*signal Both Tx VEX cores to start continuous flow*/
    /* The relative dealy between Tx0 Vex Core and Tx1 Vex core based on the split is not taken care currently - OPEN ITEM*/
    for (vex_cnt = 0; vex_cnt < NUM_TX_VEX_CORES; vex_cnt++)
    {
        int vex_index = vex_cnt * 2;
        int vex_num = vex_num_param[vex_index];

        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + HIVE_ADDR_v2d_flow1_tx_g_host_indicator,
                        &host_flag,
                        1,
                        flags)))
            return rv;
    }

    /*Triggering the forced BFN*/
    if (rv = tx_start_bfn_trigger(v2d_num, apb_num))
    {
        printf ("BFN trigger failed\n");
        return rv;
    }

#endif

    loop_wait_count = 0;
    usleep(10000);

    while ((h2b_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "H2B_FLIT_COUNT"))  <
            ((MAX_BLOCKS * (g_flow1_vectors_per_block[sys_rate] * 2))))
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

    int num_vectors_block[2];
    num_vectors_block[0] = vex0_rx_args[1];
    num_vectors_block[1] = vex1_rx_args[1];

    /* Read the output results from both the Rx vex cores*/
    for (vex_cnt = 0; vex_cnt < NUM_RX_VEX_CORES; vex_cnt++)
    {

        host_vec_processed = 0;
        loop_wait_count = 0;
        int vex_index = (vex_cnt * 2) + 1;
        int vex_num = vex_num_param[vex_index];

        while (host_vec_processed < ((MAX_BLOCKS * num_vectors_block[vex_cnt])))
        {
            if ((rv = srp_dev_block_read32(srp,
                            SRP_BLOCK_VEX_CORE,
                            vex_num,
                            dmem_offset + HIVE_ADDR_v2d_flow1_rx_g_count1,
                            &host_vec_processed,
                            1,
                            flags)))
                return rv;

            if (loop_wait_count >= 30)
            {
                printf("ERROR: VEX core %d didn't processed enough vectors\n", vex_num);
                rv = 1;
                return rv;
            }
            loop_wait_count ++;
            usleep(10000);
        }

        /* Reading the results from Rx VEX*/
        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + HIVE_ADDR_v2d_flow1_rx_g_compare_result,
                        &host_result,
                        1,
                        flags)))
            return rv;

        if ((rv = srp_dev_block_read32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + HIVE_ADDR_v2d_flow1_rx_g_add_val_out,
                        &host_blocks_processed,
                        1,
                        flags)))
            return rv;

        printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
        printf ("processed blocks  by vex %d 0x%x", (vex_num + 1), host_blocks_processed - add_val[0]);

        if (0xFFFFFFFF != host_result)
        {
            printf ("ERROR: Received output didn't match with Reference output TV for Rx VEX%d", (vex_num));
            test_status |= 1;
        }
        else
        {
            printf("Received output matches with Reference output");
        }
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = VEC2FLIT(vex0_tx_args[1]) + vex0_tx_args[1];

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
        printf("Host:---- SUCCESS ---- tx0_vex_num : %d, rx0_vex_num: %d, tx1_vex_num : %d, rx1_vex_num : %d, v2d_num : %d, apb_num : %d, \
                split_method: %s, drf_clock: %s, sys_rate: %s\n",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, apb_num, split_method_str[split_method],
                drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
    }
    else
    {
        printf("Host:---- FAIL ---- tx0_vex_num : %d, rx0_vex_num: %d, tx1_vex_num : %d, rx1_vex_num : %d, v2d_num : %d, apb_num : %d, \
                split_method: %s, drf_clock: %s, sys_rate: %s\n",
                vex_num_param[0], vex_num_param[1], vex_num_param[2], vex_num_param[3], v2d_num, apb_num, split_method_str[split_method],
                drf_clock_str[drf_clock], sys_rate_str[sys_rate]);
        rv = 1;
    }

    return rv;
}   // main ends
