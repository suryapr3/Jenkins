
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
#include<time.h>

/***********************************************
* LOCAL/PRIVATE MACROS AND DEFINES            *
***********************************************/

//#define printf LOG_PRINT

//configure clk and sysref
void fpga_clk_and_sysref_period(uint32_t rx_clk, uint32_t tx_clk, uint32_t rx_sysref_period, uint32_t tx_sysref_period)
{
    printf("\n###configuring fpga clk and sysref period\n");
    char buffer_1[50];
    char buffer_2[50];
    char buffer_3[50];
    char buffer_4[50];
    sprintf(buffer_1, "frioPciWrite -F s5a1 -P 0x20000 0x%x", rx_clk);
    sprintf(buffer_2, "frioPciWrite -F s5b1 -P 0x20000 0x%x", tx_clk);
    sprintf(buffer_3, "frioPciWrite -F s5a1 -P 0x20004 0x%x", rx_sysref_period);
    sprintf(buffer_4, "frioPciWrite -F s5b1 -P 0x20004 0x%x", tx_sysref_period);
    system(buffer_1);
    system(buffer_2);
    system(buffer_3);
    system(buffer_4);
    printf("buffer1 is %s \n",buffer_1);
    printf("buffer2 is %s \n",buffer_2);
    printf("buffer3 is %s \n",buffer_3);
    printf("buffer4 is %s \n",buffer_4);
/*    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
    system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
    system("frioPciWrite -F s5b1 -P 0x20004 0x1900190"); */
}

void fpga_provided_sysref_en(uint32_t rx_sysref, uint32_t tx_sysref)
{
    printf("\n###enabling fpga based sysref\n");
    char buffer_1[50];
    char buffer_2[50];
    sprintf(buffer_1, "frioPciWrite -F s5a1 -P 0x20000 0x%x", rx_sysref);
    sprintf(buffer_2, "frioPciWrite -F s5b1 -P 0x20000 0x%x", tx_sysref);
    system(buffer_1);
    system(buffer_2);
    //system("frioPciWrite -F s5a1 -P 0x20000 0x90");
    //system("frioPciWrite -F s5b1 -P 0x20000 0x90");
}

void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}


static int program_cmn_csr_rx_registers()
{
    int i=0;
    uint32_t base_address_cmn[] = {DLNK_JESD0_CMN_CSR_BASE, DLNK_JESD1_CMN_CSR_BASE, DLNK_JESD2_CMN_CSR_BASE, DLNK_JESD3_CMN_CSR_BASE};
    printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");

    for(i=0; i<1; i++)
    {
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_IP_CLK_CTRL_OFFSET, JESD_CMN_CSR_RX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESD_CMN_CSR_RX_IP_CLK_CTRL_RD_MASK, JESD_CMN_CSR_RX_IP_CLK_CTRL_WR_MASK, "JESD_CMN_CSR_RX_IP_CLK_CTRL_OFFSET");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_SYSREF_TSAD_OFFSET, JESD_CMN_CSR_RX_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESD_CMN_CSR_RX_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_RX_SYSREF_TSAD_WR_MASK, "JESD_CMN_CSR_RX_SYSREF_TSAD");

        //bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_SYNC_POINT_CTRL_OFFSET, JESD_CMN_CSR_RX_SYNC_POINT_CTRL_DEFAULT, 0x001f007f, 0x001f007f, JESD_CMN_CSR_RX_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_RX_SYNC_POINT_CTRL_WR_MASK, "JESD_CMN_CSR_RX_SYNC_POINT_CTRL");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_OFFSET, JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_WR_MASK, "JESD_CMN_CSR_RX_BFN_SYSREF_TSAD");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x001f007f, 0x001f007f, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL");

        //this register can be ingnored as per RP, roshan 12/02/24
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_OFFSET, JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_RD_MASK, JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_WR_MASK, "JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_CLK_GEN_EN_OFFSET, JESD_CMN_CSR_RX_CLK_GEN_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_RX_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_RX_CLK_GEN_EN_WR_MASK, "JESD_CMN_CSR_RX_CLK_GEN_EN");

        //this register can be ingnored as per RP, roshan 12/02/24
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_OFFSET, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_WR_MASK, "JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_OFFSET, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_WR_MASK, "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN");
    }
}

static int program_cmn_csr_tx_registers()
{
    int i=0;
    uint32_t base_address_cmn[] = {DLNK_JESD0_CMN_CSR_BASE, DLNK_JESD1_CMN_CSR_BASE, DLNK_JESD2_CMN_CSR_BASE, DLNK_JESD3_CMN_CSR_BASE};
    printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");

    for(i=0; i<1; i++)
    {
        //write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_NUM_VALID_STR_OFFSET, JESD_CMN_CSR_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESD_CMN_CSR_TX_NUM_VALID_STR_RD_MASK, JESD_CMN_CSR_TX_NUM_VALID_STR_WR_MASK, "JESD_CMN_CSR_TX_NUM_VALID_STR");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_IP_CLK_CTRL_OFFSET, JESD_CMN_CSR_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESD_CMN_CSR_TX_IP_CLK_CTRL_RD_MASK, JESD_CMN_CSR_TX_IP_CLK_CTRL_WR_MASK, "JESD_CMN_CSR_TX_IP_CLK_CTRL");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_SYSREF_TSAD_OFFSET, JESD_CMN_CSR_TX_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESD_CMN_CSR_TX_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_TX_SYSREF_TSAD_WR_MASK, "JESD_CMN_CSR_TX_SYSREF_TSAD");

        //bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_SYNC_POINT_CTRL_OFFSET, JESD_CMN_CSR_TX_SYNC_POINT_CTRL_DEFAULT, 0x001f007f, 0x001f007f, JESD_CMN_CSR_TX_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_TX_SYNC_POINT_CTRL_WR_MASK, "JESD_CMN_CSR_TX_SYNC_POINT_CTRL");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_OFFSET, JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_WR_MASK, "JESD_CMN_CSR_TX_BFN_SYSREF_TSAD");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x001f007f, 0x001f007f, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL");

        //this register can be ingnored as per RP, roshan 12/02/24
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_OFFSET, JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_RD_MASK, JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_WR_MASK, "JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_CLK_GEN_EN_OFFSET, JESD_CMN_CSR_TX_CLK_GEN_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_TX_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_TX_CLK_GEN_EN_WR_MASK, "JESD_CMN_CSR_TX_CLK_GEN_EN");

        //this register can be ingnored as per RP, roshan 12/02/24
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_OFFSET, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_WR_MASK, "JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN");
        write_read_expect_18a(base_address_cmn[i]+JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_OFFSET, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_DEFAULT, 0x00000001, 0x00000001, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_WR_MASK, "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN");

    }
}

static void access_rx_and_tx_blocks(void)
{
    uint32_t tx_gb_empty_reg = 0;
    uint32_t tx_gb_full_reg = 0;
    uint32_t rx_gb_empty_reg = 0;
    uint32_t rx_gb_full_reg = 0;
    uint32_t fec_en = 0;

    int i,j=0;
    uint32_t base_address_rx[] = {DLNK_JESD0_XIP_204C_RX_BASE,  DLNK_JESD1_XIP_204C_RX_BASE,  DLNK_JESD2_XIP_204C_RX_BASE,  DLNK_JESD3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESD0_XIP_204C_TX_BASE,  DLNK_JESD1_XIP_204C_TX_BASE,  DLNK_JESD2_XIP_204C_TX_BASE,  DLNK_JESD3_XIP_204C_TX_BASE};

    for(i=0; i<1; i++)
    {
        tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_GEARBOX_EMPTY_STAT_OFFSET, "JL_N_TX_GB_EMPTY_REG");
        tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_GEARBOX_FULL_STAT_OFFSET, "JL_N_TX_GB_FULL_REG");
    }
    for(j=0; j<1; j++)
    {
        rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_OFFSET, "JL_N_RX_GB_EMPTY_REG");
        rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_GEARBOX_FULL_STAT_OFFSET, "JL_N_RX_GB_FULL_REG");
    }

    printf("\n  ######example register read of tx and rx registers\n");
    printf("  Value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
    printf("  Value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
    printf("  Value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
    printf("  Value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);


    //write to rx reg
    i=0;
    printf("\n  ######example register write of rx registers\n");
    fec_en  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_FEC_OFFSET, "JESD_XIP_204C_RX_FEC_REG");
    printf("  Value before write of JESD_XIP_204C_RX_FEC_REG is 0x%x \n",fec_en);
    write_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_FEC_OFFSET,0x00000001,JESD_XIP_204C_RX_FEC_WR_MASK, "JESD_XIP_204C_RX_FEC_REG");
    fec_en  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_FEC_OFFSET, "JESD_XIP_204C_RX_FEC_REG");
    printf("  Value after write of JESD_XIP_204C_RX_FEC_REG is 0x%x \n",fec_en);

}

static void access_glue_and_crux_clk_blocks(void)
{
    int i = 0;
    uint32_t tsb_full_value = 0;
    uint32_t tsb_src_en_value = 0;
    uint32_t rx_soni_value = 0;
    uint32_t rx_datapath_gate_sel =0;

    uint32_t base_rx_glue[] = {DLNK_JESD0_RX_GLUE_BASE,  DLNK_JESD1_RX_GLUE_BASE,  DLNK_JESD2_RX_GLUE_BASE,  DLNK_JESD3_RX_GLUE_BASE};
    uint32_t base_tx_glue[] = {DLNK_JESD0_TX_GLUE_BASE,  DLNK_JESD1_TX_GLUE_BASE,  DLNK_JESD2_TX_GLUE_BASE,  DLNK_JESD3_TX_GLUE_BASE};
    uint32_t base_address_crux_clk_csr[] = {DLNK_JESD0_CRUX_CLK_CSR_BASE,  DLNK_JESD1_CRUX_CLK_CSR_BASE,  DLNK_JESD2_CRUX_CLK_CSR_BASE,  DLNK_JESD3_CRUX_CLK_CSR_BASE};
    for(i=0; i<1; i++)
    {
        rx_soni_value = read_reg_18a(base_rx_glue[i]+JESD_RX_GLUE_SONI_OFFSET, "JESD_RX_GLUE_SONI");
        tsb_full_value  = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_OFFSET, "JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET, "JESD_TX_GLUE_DATA_SRC_EN");
        printf("  ######example register read of glue and crux_clk registers\n");
        printf("  Value of JESD_RX_GLUE_SONI is 0x%x \n",rx_soni_value);
        printf("  Value of JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT is 0x%x \n",tsb_full_value);
        printf("  Value of JESD_TX_GLUE_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);

        printf("\n  ######example register write of rx_glue and tx_glue registers\n");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET, "JESD_TX_GLUE_DATA_SRC_EN");
        printf("  Value before write of JESD_TX_GLUE_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);
        write_reg_18a(base_tx_glue[i] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET,0x00000001,JESD_TX_GLUE_DATA_SRC_EN_WR_MASK, "JESD_TX_GLUE_DATA_SRC_EN");
        tsb_src_en_value  = read_reg_18a(base_tx_glue[i] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET, "JESD_TX_GLUE_DATA_SRC_EN");
        printf("  Value after write of JESD_TX_GLUE_DATA_SRC_EN is 0x%x \n",tsb_src_en_value);

        rx_datapath_gate_sel = read_reg_18a(base_rx_glue[i]+JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET, "JESD_RX_GLUE_DATAPATH_GATE_SEL");
        printf("  Value before write of JESD_RX_GLUE_DATAPATH_GATE_SEL is 0x%x \n",rx_datapath_gate_sel);
        write_reg_18a(base_rx_glue[i] + JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET,0x01,JESD_RX_GLUE_DATAPATH_GATE_SEL_WR_MASK, "JESD_RX_GLUE_DATAPATH_GATE_SEL");
        rx_datapath_gate_sel = read_reg_18a(base_rx_glue[i]+JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET, "JESD_RX_GLUE_DATAPATH_GATE_SEL");
        printf("  Value after write of JESD_RX_GLUE_DATAPATH_GATE_SEL is 0x%x \n",rx_datapath_gate_sel);
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

    //enable clk for rx and tx ip
    program_cmn_csr_tx_registers();
    program_cmn_csr_rx_registers();

    //access rx and tx registers
    access_rx_and_tx_blocks();

    delay(100);
    //access glue and crux registers
    access_glue_and_crux_clk_blocks();

    return rv;
}//main_ends


