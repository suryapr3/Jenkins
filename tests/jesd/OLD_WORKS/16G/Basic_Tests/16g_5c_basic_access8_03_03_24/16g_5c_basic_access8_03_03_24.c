
/*********************************************************************************************
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
* @file    16g_5c_basic_access6_02_03_24.c
* @brief   jesd reset, clk for register access enabled
* @details enable jesd link as needed,
*/

/*********************************************************************************************
* LOCAL INCLUDE STATEMENTS                    *
*********************************************************************************************/
//#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"

#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"
#include "jesd_common_functions.h"
#include<time.h> 

/***********************************************
* LOCAL/PRIVATE MACROS AND DEFINES            *
***********************************************/

//#define printf LOG_PRINT


void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

static void access_rx_and_tx_blocks(void)
{
    uint32_t tx_gb_empty_reg = 0;
    uint32_t tx_gb_full_reg = 0;
    uint32_t rx_gb_empty_reg = 0;
    uint32_t rx_gb_full_reg = 0;
    uint32_t fec_en = 0;

    int i,j=0;
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};
    
    for(i=0; i<1; i++)
    {
        tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
        tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
    }
    for(j=0; j<1; j++)
    {
        rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
        rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
    }

    printf("\n  ######example register read of tx and rx registers\n");
    printf("  Value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
    printf("  Value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
    printf("  Value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
    printf("  Value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);

    //write to rx reg
    i=0;
    printf("\n  ######example register write of rx registers\n");
    fec_en  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET, "JESD_XIP_204C_RX_MEM_RX_FEC_REG");
    printf("  Value before write of JESD_XIP_204C_RX_MEM_RX_FEC_REG is 0x%x \n",fec_en);
    write_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET,0x00000001,JESD_XIP_204C_RX_MEM_RX_FEC_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_FEC_REG");
    fec_en  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET, "JESD_XIP_204C_RX_MEM_RX_FEC_REG");
    printf("  Value after write of JESD_XIP_204C_RX_MEM_RX_FEC_REG is 0x%x \n",fec_en);
}

static void access_glue_and_crux_clk_blocks(void)
{
    int i = 0;
    uint32_t tsb_full_value = 0;
    uint32_t tsb_src_en_value = 0;
    uint32_t rx_soni_value = 0;
    uint32_t rx_datapath_gate_sel =0;

    uint32_t base_rx_glue[] = {DLNK_JESDABC0_RX_GLUE_BASE,  DLNK_JESDABC1_RX_GLUE_BASE,  DLNK_JESDABC2_RX_GLUE_BASE,  DLNK_JESDABC3_RX_GLUE_BASE};
    uint32_t base_tx_glue[] = {DLNK_JESDABC0_TX_GLUE_BASE,  DLNK_JESDABC1_TX_GLUE_BASE,  DLNK_JESDABC2_TX_GLUE_BASE,  DLNK_JESDABC3_TX_GLUE_BASE};
    uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
    for(i=0; i<1; i++)
    {
        rx_soni_value = read_reg_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI");
        tsb_full_value  = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");
        printf("  ######example register read of glue and crux_clk registers\n");
        printf("  Value of JESDABC_RX_GLUE_MEM_RX_GLUE_SONI is 0x%x \n",rx_soni_value);
        printf("  Value of JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS is 0x%x \n",tsb_full_value);
        printf("  Value of JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);

        printf("\n  ######example register write of rx_glue and tx_glue registers\n");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");
        printf("  Value before write of JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);
        write_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET,0x00000001,JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");
        printf("  Value after write of JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);
        printf("  Value before write of JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL is 0x%x \n",rx_datapath_gate_sel);
        write_reg_18a(base_rx_glue[i] + JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET,0x01,JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_POINTER_TBL2");
        rx_datapath_gate_sel = read_reg_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, "JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL");
        printf("  Value after write of JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL is 0x%x \n",rx_datapath_gate_sel);
    }
}

int main(int argc, const char *argv[])
{
    int rv;
    fpga_clk_and_sysref_period(0x10,0x10,0x1900190,0x1900190);
    delay(100);

    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
    delay(100);
    init();
    delay(1000);

    //pass the link instances to be enabled
    jesd_reset((JESD_INSTANCE_0), 0);
    delay(1000);

    //enable sysref
    fpga_provided_sysref_en(0x90,0x90);
    delay(100);

    //access rx and tx registers
    access_rx_and_tx_blocks();

    //configure clks with default clk,
    clk_enable (NULL);
/*
    //if enable usecase, use this 
    struct clk_config_s UC_clk_cfg = 
    {
        0x18,
        0x0000000f,
        0x000b001b,
        1,
        1,
        1,
        0x18,
        0x00000017,
        0x00170023,
        1,
        1,
        1
    };
    clk_enable (&UC_clk_cfg);
*/

    delay(100);
    access_glue_and_crux_clk_blocks();

    return rv;
}//main_ends


