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
 * @file    connectivity.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D and receving it back.
 * @details 1. Configuration of VEX, V2D's Common Module(4 ports) for sending data from VEX to V2D
               and receving it back to VEX for 0.5IQ GSPS
            2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
        1. 1 block of samples for data rate of 0.5GSPS will be streamed to V2D from
           configured VEX core.
        2. Based on Port num either Path A along with path F as feedback path will be configured or
           Path B along with Path D as feedback path was conifgured.
        3. With Rx loop back enabled the data looped back was expected to reach
           the VEX core where comparison will be performed.
        4. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the one block of vector comparison was done HOST will
           read the result.
        5, Rx VEX will exclude the first block from data comparison as there is a mismatch for the
           first block in MATLAB model and FPGA output when PDPD block is involved.
        5. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.

 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "flow6_common_utils.h"
#include "common_utils.h"

#include "v2d_connectivity.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define TEST_VECTORS    "../flow6/test_vectors/"
#define TX_GNRL_CSR_CONNECTIVITY    AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last four entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET), FIFO_CONTROL_VALUE, NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, \
        "B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
        "B2H_CREDIT_CS"},
    // These are for Buffer A0
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, \
        "H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
     /* Value should be 2 blocks of data for any rate */
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, (NUM_DATA_BLOCKS - 1), NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "H2B_BUF_SZ_HW_TBL0"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_connectivity_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "H2B_TK_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80004000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_TK_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "H2B_MD_ROUTE_LKUP_TBL0"},
    {V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"}
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last four entries order shouldn't be modified*/
static v2d_flow_tbl_t g_cm_1_config_tbl[] = {
// NSIP Interrupt enable registers
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "HBI_1_INT_HIGH_EN"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "HBI_1_INT_LOW_EN"},

// B2H Registers
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET), FIFO_CONTROL_VALUE, NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, \
        "HBI_1_B2H_FIFO_CONTROL"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET), B2H_CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
        "HBI_1_B2H_CREDIT_CS"},
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET), 0x80000000, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in bytes
    {(V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET), 0x1FFFF, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
        "HBI_1_B2H_ADDR_MASK_TBL0"},

// H2B Registers
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, FIFO_CONTROL_VALUE, NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, \
        "CM_1_H2B_FIFO_CONTROL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, H2B_CREDIT_READY_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "CM_1_H2B_CREDIT_CS"},
    /* 512 flits of DEST Buffer Size in VEX corresponds to 2 blocks of data for max 8GSPS case*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, NUM_DATA_BLOCKS - 1, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
        "HBI_1_H2B_BUF_SZ_HW_TBL"},
    /* Data will be written to VEX location 0x10080 , i.e VEX DMEM location 0x80*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, (STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_connectivity_consumer_sm_gate), \
        NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "HBI_1_H2B_TK_ADDR_LKUP_TBL_0"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, STRM2CIO_2_VEX_DMEM_OFFSET, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ADDR_LKUP_TBL_0"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET, 0xF, NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK, \
        "HBI_1_H2B_MD_CONTROL_TBL"},
    /***********************************************************************************************************************************/
    /*These last 4 entries orders shouldn't be altered as they will be modified based on the run time parameter for vex number*/
    /* Data will be written to VEX location 0x4000 , i.e VEX VMEM location 0x4000*/
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80004000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_ADDR_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "HBI_1_H2B_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_TK_ROUTE_LKUP_TBL"},
    {V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
        "HBI_1_H2B_MD_ROUTE_LKUP_TBL"}
    /***********************************************************************************************************************************/
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last entry order shouldn't be modified*/
static v2d_flow_tbl_t g_v2d_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

    // Rx Path Settings , D path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},

// Tx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x3FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0400, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_TX_CSR_TX_STRM_CNT_WR_MASK, "TX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PD_STRM_CNT0_OFFSET, 0x8000000F, AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_WR_MASK, "RX_PD_STREAM_CNT0"},
    /************************************************************************************************************/
    /* The last entry order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_DEFAULT, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /************************************************************************************************************/
};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int flow6_configure_pdpd(int, int, int, int);
int configure_v2d_host(int, int, int, int, int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id, V2d Id, APB Id and cm_num
 * @return          status
 */
int configure_v2d_host(int vex_num, int v2d_num, int apb_num, int cm_num, int drf_clock)
{
    int i, rv = 0, sif_ctrl_value = 0, host_id = 0, rx_gnrl_csr_value = 0;

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 3 * VEC2FLIT(g_vectors_per_block[0][0]); // As TC will be running only for P5GSPS
    printf("fill_level_value : 0x%x", fill_level_value);
#endif

    /* Corresponds to Path A along with Path F*/
    if (0 == cm_num)
    {
        sif_ctrl_value = AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK | (drf_clock << AV2D_CSR_TX_CSR_TX_SIF_CTRL_DRF_1P5G_CLK_BF_OFF) | \
                         SYS_RATE_IQ_P5;
        host_id = g_v2d_host_id[v2d_num][apb_num][0];
        rx_gnrl_csr_value = AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_CFG_COMPLETE_BF_MSK;
    }
    else    /* Corresponds to Path B along with Path D*/
    {
        sif_ctrl_value = (drf_clock << AV2D_CSR_TX_CSR_TX_SIF_CTRL_DRF_1P5G_CLK_BF_OFF) | AV2D_CSR_TX_CSR_TX_SIF_CTRL_DEFAULT;
        host_id = g_v2d_host_id[v2d_num][apb_num][1];
        rx_gnrl_csr_value = AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_EN_BF_MSK | AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_CFG_COMPLETE_BF_MSK;
    }

    for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }
    // Corresponds to cio2strm dest id
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_cio2strm_config_tbl[i].offset, host_id, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
        return rv;

    printf("INFO: cio2strm configuration completed");

    for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
    {
        if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
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
    for (;i< (ARRAY_SIZE(g_cm_0_config_tbl) - 3); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), \
                    (0x80000000 | HIVE_ADDR_v2d_connectivity_vbuffer_out), g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
    for (; i <  (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {

        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_0_config_tbl[i].offset), vex_num, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }

    for (i = 0; i < ARRAY_SIZE(g_cm_1_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), \
                    (0x80000000 | HIVE_ADDR_v2d_connectivity_vbuffer_out), g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_cm_1_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_cm_1_config_tbl[i].offset), vex_num, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
    printf ("INFO: CM configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_v2d_config_tbl) - 1); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), \
                    g_v2d_config_tbl[i].value, g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_config_tbl); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_config_tbl[i].offset), sif_ctrl_value, \
                g_v2d_config_tbl[i].mask, g_v2d_config_tbl[i].name))
           return rv;
    }

    rv = flow6_configure_pdpd(v2d_num, apb_num, 0, POST_C_CENTER_VALUE_UNITY_GAIN);
    printf("INFO: V2D pdpd configuration completed");

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    if (1 == cm_num)    // Corresponds to Path B along with Path D
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                    AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                    AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
            return rv;
    }
    else    // Corresponds to Path A along with Path F
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_AC_WM_EN_BF_MSK | fill_level_value, AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
            return rv;
    }
#endif

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_CONNECTIVITY, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), \
                rx_gnrl_csr_value, AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D configuration completed");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_BASE(vex_num) + VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                HIVE_ADDR_v2d_connectivity_consumer_sm_gate, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;

    return rv;
}

int main(int vex_num, int v2d_num, int port_num, int drf_clock)
{
    int rv = 0, test_status = 0;
    int flags = 0;
    int lc, i, j;
    int apb_num, host_flag = 1, cm_num = 0, loop_wait_count = 0, v2d_interrupt_value = 0;
    unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;

    int dmem_offset = DMEM_OFFSET;
    int vex_param_offset_val[] = {HIVE_ADDR_v2d_connectivity_g_scalar_val, HIVE_ADDR_v2d_connectivity_g_num_vecs_in,
                                HIVE_ADDR_v2d_connectivity_g_num_blocks, HIVE_ADDR_v2d_connectivity_g_tbs_in_blk,
                                HIVE_ADDR_v2d_connectivity_g_dest_buffer_base, HIVE_ADDR_v2d_connectivity_g_count1};
    unsigned int vex_param_val_args[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0, 0};
    unsigned int val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int host_ref_data[NUMBER_OF_VECTORS_OUTPUT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];
    char tref_file[100] = {'\0'};
    FILE *fp_ref_output = NULL;

    init(); /* Initialize the srp*/

    LOG_PRINT("INFO: logger beginning");
    printf ("INFO: argv[0] : %d = vex_num", vex_num);
    printf ("INFO: argv[1] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[2] : %d = port_num", port_num);
    printf ("INFO: argv[3] : %d = drf_clock", drf_clock);

    apb_num = port_num / 2;
    cm_num = port_num % 2;
    printf("vex id: %d, v2d_num : %d, apb_num: %d, cm_num: %d, drf_clock: %s",vex_num, v2d_num, apb_num, cm_num, drf_clock_str[drf_clock]);
    vex_param_val_args[1] = g_vectors_per_block[0][PDPD_RATE_IQ_P5];
    vex_param_val_args[2] = 2;
    vex_param_val_args[3] = NUM_DATA_BLOCKS;

    /*enabling the V2D clock*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        printf("ERROR: v2d_quad_clk_enable failed");
        return rv;
    }

    if (rv = configure_v2d_host(vex_num, v2d_num, apb_num, cm_num, drf_clock))
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

    /*Clearing the VEX VMEM and DMEM for vex core*/
    if (rv = vex_mem_clear(vex_num, srp))
    {
        printf("ERROR: vex_mem_clear failed for vex:%d", vex_num);
        return rv;
    }

    printf("Host: start vex Rx program load ");

    if ((rv = vex_loader(vex_num, "vex_fw/sim_m64/v2d_connectivity.fw")))
        return rv;

    printf("Host: vex program load - done");

    /* Loading the host parameters to VEX  Rx core*/
    if (load_vex_param(vex_num /*vex_core*/, ARRAY_SIZE(vex_param_offset_val), vex_param_offset_val, vex_param_val_args))
    {
        LOG_ERROR("Rx vex param loading failed");
    }

    /* Input Vector Generation*/
    for (i = 0; i < g_vectors_per_block[0][PDPD_RATE_IQ_P5]; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)))  ;
        }
    }

    sprintf(tref_file, "%s%s", TEST_VECTORS,"ref_output_p5gsps.txt");

    printf ("HOST: output file : %s", tref_file);
    fp_ref_output = fopen(tref_file, "r");
    if (NULL == fp_ref_output)
    {
        printf("ERROR: Not able to open the output file");
        return -1;
    }

    if (vector_read_hex_u32(fp_ref_output,
                host_ref_data,
                g_vectors_per_block[0][PDPD_RATE_IQ_P5] * NUM_OF_ELEMENTS_PER_VEC) < \
                g_vectors_per_block[0][PDPD_RATE_IQ_P5] * NUM_OF_ELEMENTS_PER_VEC)
    {
        printf("ERROR: Insufficient Output REF data");
        return -1;
    }
    fclose(fp_ref_output);

    write_mem_18a(VEX_VMEM(vex_num) + HIVE_ADDR_v2d_connectivity_vbuffer,/*local_addr*/
                        (g_vectors_per_block[0][PDPD_RATE_IQ_P5] * NUM_OF_ELEMENTS_PER_VEC), val_inp[0],
                        "VEX_VMEM");

    if (0 == cm_num)    // For Path A
    {
        write_mem_18a(VEX_VMEM(vex_num) + HIVE_ADDR_v2d_connectivity_vbuffer_ref,/*local_addr*/
                            (g_vectors_per_block[0][PDPD_RATE_IQ_P5] * NUM_OF_ELEMENTS_PER_VEC), val_inp[0],
                        "VEX_VMEM");
    }
    else    // For Path B
    {
        write_mem_18a(VEX_VMEM(vex_num) + HIVE_ADDR_v2d_connectivity_vbuffer_ref,/*local_addr*/
                            (g_vectors_per_block[0][PDPD_RATE_IQ_P5] * NUM_OF_ELEMENTS_PER_VEC),host_ref_data,
                            "VEX_VMEM");
    }

    printf("Host: vex program start");

    vex_start( vex_num, 0);

    printf("Host: vex program start - done");

#if !FILL_LEVEL_TRIGGER
    if (0 == cm_num)
    {
        while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                        NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
                (VEC2FLIT(g_vectors_per_block[0][SYS_RATE_IQ_P5])))
        {
            // do nothing wait until 1 blocks are received in this loop
            if (loop_wait_count >= 30)
            {
                printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits");
                break;
            }
            loop_wait_count ++;
            usleep(10000);
        }
    }
    else
    {
        while ((b2h_flit_cnt += read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                        NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "B2H_FLIT_COUNT")) <
                (VEC2FLIT(g_vectors_per_block[0][SYS_RATE_IQ_P5])))
        {
            // do nothing wait until 1 blocks are received in this loop
            if (loop_wait_count >= 30)
            {
                printf("WARNING: Breaking the loop while B2H_FLIT_CNT is not the required number of flits");
                break;
            }
            loop_wait_count ++;
            usleep(10000);
        }

    }

    /*Triggering the forced BFN*/
    if (0 == cm_num)    /* for path A*/
    {
        if (rv = tx_start_bfn_trigger(v2d_num, apb_num))
        {
            printf("TX BFN trigger failed");
            return rv;
        }
    }
    else    /*for path B*/
    {
        if (rv = pdpd_start_bfn_force_trigger(v2d_num, apb_num))
        {
            printf ("PDPD BFN trigger failed");
            return rv;
        }
    }
#endif

    usleep(10000);
    loop_wait_count = 0;

    /*Wait till the RX VEX processed required number of vectors*/
    while (host_vec_processed < (g_vectors_per_block[0][PDPD_RATE_IQ_P5]))
    {
        host_vec_processed = read_reg_18a(VEX_DMEM(vex_num) + HIVE_ADDR_v2d_connectivity_g_count1, "vec_processed");

        if (loop_wait_count >= 30)
        {
            printf("ERROR: VEX core didn't processed enough vectors 0x%x", host_vec_processed);
            rv = 1;
            return rv;
        }

        loop_wait_count ++;
        usleep(10000);
    }

    /* Reading the results from Rx VEX*/
    host_result = read_reg_18a(VEX_DMEM(vex_num) + HIVE_ADDR_v2d_connectivity_g_compare_result, "compare_result");
    host_blocks_processed = read_reg_18a(VEX_DMEM(vex_num) + HIVE_ADDR_v2d_connectivity_g_add_val_out, "blocks_processed");

    printf ("HOST_result : 0x%x, processed vectors 0x%x ", host_result, host_vec_processed);
    printf ("processed blocks 0x%x", host_blocks_processed);

    if (0xFFFFFFFF != host_result)
    {
        printf ("ERROR: Received output didn't match with Reference output TV");
        test_status = 1;
    }
    else
    {
        printf("HOST: Received output matches with Reference output");
    }

    /*FILL_LEVEL_TRIGGER falg will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
#if FILL_LEVEL_TRIGGER
    int fill_level_value = 3 * VEC2FLIT(g_vectors_per_block[0][PDPD_RATE_IQ_P5]);
#endif

    if (0 == cm_num)
    {
        v2d_interrupt_value = AV2D_CSR_INT_CSR_INT_STAT_TX_UNDERRUN_BF_MSK;
#if FILL_LEVEL_TRIGGER
        /*Checking whether fill level was triggered properly or not*/
        fill_level_check(v2d_num, apb_num, fill_level_value);
#endif
    }
    else
    {
        v2d_interrupt_value = AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_MSK;

#if FILL_LEVEL_TRIGGER
        /*Checking whether fill level was triggered properly or not*/
        pdpd_fill_level_check(v2d_num, apb_num, fill_level_value);
#endif
    }

    if (rv = interrupt_status_check(v2d_num, apb_num, v2d_interrupt_value, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
    {
        printf("ERROR: Interrupt status check failed");
        test_status = 1;
    }
    else
    {
        printf("HOST:Interrupt check passed");
    }

    if (0 == test_status)
    {
        printf("Host:---- SUCCESS ---- vex_num : %d, v2d_num : %d, port_num : %d, drf_clock: %s", vex_num, v2d_num, port_num, drf_clock_str[drf_clock]);
    }
    else
    {
        printf("Host:---- FAIL---- vex_num : %d, v2d_num : %d, port_num : %d, drf_clock: %s", vex_num, v2d_num, port_num, drf_clock_str[drf_clock]);
        rv = 1;
    }
    return rv;
}   // main ends
