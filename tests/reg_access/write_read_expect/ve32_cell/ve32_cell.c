/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
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
*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"
#include "common_functions.h"
#include "srp_block_ids.h"

#define write_data0 0xA5A5A5A5
#define write_data1 0x5a5a5a5a


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    uint32_t error = 0;
    uint32_t write_status = 0;
    uint32_t write_iteration;
    uint32_t write_data;
    uint32_t expected_data;
    int i;
    init();

    uint32_t base_address[] = {
    VEXABC0_SC_VE32_CELL_BASE, VEXABC1_SC_VE32_CELL_BASE, VEXABC2_SC_VE32_CELL_BASE, VEXABC3_SC_VE32_CELL_BASE, VEXABC4_SC_VE32_CELL_BASE,
    VEXABC5_SC_VE32_CELL_BASE, VEXABC6_SC_VE32_CELL_BASE, VEXABC7_SC_VE32_CELL_BASE, VEXABC8_SC_VE32_CELL_BASE, VEXABC9_SC_VE32_CELL_BASE,
    VEXABC10_SC_VE32_CELL_BASE, VEXABC11_SC_VE32_CELL_BASE, VEXABC12_SC_VE32_CELL_BASE, VEXABC13_SC_VE32_CELL_BASE, VEXABC14_SC_VE32_CELL_BASE,
    VEXABC15_SC_VE32_CELL_BASE, VEXABC16_SC_VE32_CELL_BASE, VEXABC17_SC_VE32_CELL_BASE, VEXABC18_SC_VE32_CELL_BASE, VEXABC19_SC_VE32_CELL_BASE,
    VEXABC20_SC_VE32_CELL_BASE, VEXABC21_SC_VE32_CELL_BASE, VEXABC22_SC_VE32_CELL_BASE, VEXABC23_SC_VE32_CELL_BASE, VEXABC24_SC_VE32_CELL_BASE,
    VEXABC25_SC_VE32_CELL_BASE, VEXABC26_SC_VE32_CELL_BASE, VEXABC27_SC_VE32_CELL_BASE, VEXABC28_SC_VE32_CELL_BASE, VEXABC29_SC_VE32_CELL_BASE,
    VEXABC30_SC_VE32_CELL_BASE, VEXABC31_SC_VE32_CELL_BASE, VEXABC32_SC_VE32_CELL_BASE, VEXABC33_SC_VE32_CELL_BASE, VEXABC34_SC_VE32_CELL_BASE,
    VEXABC35_SC_VE32_CELL_BASE, VEXABC36_SC_VE32_CELL_BASE, VEXABC37_SC_VE32_CELL_BASE, VEXABC38_SC_VE32_CELL_BASE, VEXABC39_SC_VE32_CELL_BASE
    };


    for (write_iteration = 0;write_iteration < 1; write_iteration++)
    {
        if (write_iteration == 0 )
        {
            write_data = write_data0;
        }
        else
        {
            write_data = write_data1;
        }

        expected_data = write_data;


        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
        {
			LOG_PRINT("i is %d", i);
        if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
            continue;
        }
        else
        {
			write_read_expect_18a(base_address[i]+VE32_CELL_LM_SDFGATE_RIDC_IRQPRIO_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_SDFGATE_RIDC_IRQPRIO_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_SDFGATE_RIDC_IRQPRIO_BP_DMEM_RD_MASK, VE32_CELL_LM_SDFGATE_RIDC_IRQPRIO_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_SDFGATE_RIDC_IRQPRIO_BP_DMEM_OFFSET");


//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case			
//            write_read_expect_18a(base_address[i]+VE32_CELL_CTRL_OFFSET, \
                                    VE32_CELL_CTRL_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CTRL_RD_MASK, VE32_CELL_CTRL_WR_MASK, \
                                    "VE32_CELL_CTRL_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VE32_CELL_START_ADDR_OFFSET, \
                                    VE32_CELL_START_ADDR_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_START_ADDR_RD_MASK, VE32_CELL_START_ADDR_WR_MASK, \
                                    "VE32_CELL_START_ADDR_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VE32_CELL_STAT_OFFSET, \
                                    VE32_CELL_STAT_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_STAT_RD_MASK, VE32_CELL_STAT_WR_MASK, \
                                    "VE32_CELL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_ID_OFFSET, \
                                    VE32_CELL_ID_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_ID_RD_MASK, VE32_CELL_ID_WR_MASK, \
                                    "VE32_CELL_ID_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_EXE_LSBS_OFFSET, \
                                    VE32_CELL_CNT_EXE_LSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_EXE_LSBS_RD_MASK, VE32_CELL_CNT_EXE_LSBS_WR_MASK, \
                                    "VE32_CELL_CNT_EXE_LSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_EXE_MSBS_OFFSET, \
                                    VE32_CELL_CNT_EXE_MSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_EXE_MSBS_RD_MASK, VE32_CELL_CNT_EXE_MSBS_WR_MASK, \
                                    "VE32_CELL_CNT_EXE_MSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_SLP_LSBS_OFFSET, \
                                    VE32_CELL_CNT_SLP_LSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_SLP_LSBS_RD_MASK, VE32_CELL_CNT_SLP_LSBS_WR_MASK, \
                                    "VE32_CELL_CNT_SLP_LSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_SLP_MSBS_OFFSET, \
                                    VE32_CELL_CNT_SLP_MSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_SLP_MSBS_RD_MASK, VE32_CELL_CNT_SLP_MSBS_WR_MASK, \
                                    "VE32_CELL_CNT_SLP_MSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_CLK_LSBS_OFFSET, \
                                    VE32_CELL_CNT_CLK_LSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_CLK_LSBS_RD_MASK, VE32_CELL_CNT_CLK_LSBS_WR_MASK, \
                                    "VE32_CELL_CNT_CLK_LSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_CNT_CLK_MSBS_OFFSET, \
                                    VE32_CELL_CNT_CLK_MSBS_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_CNT_CLK_MSBS_RD_MASK, VE32_CELL_CNT_CLK_MSBS_WR_MASK, \
                                    "VE32_CELL_CNT_CLK_MSBS_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_ECC_IRQ_SBE_OFFSET, \
                                    VE32_CELL_ECC_IRQ_SBE_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_ECC_IRQ_SBE_RD_MASK, VE32_CELL_ECC_IRQ_SBE_WR_MASK, \
                                    "VE32_CELL_ECC_IRQ_SBE_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_ECC_IRQ_DBE_OFFSET, \
                                    VE32_CELL_ECC_IRQ_DBE_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_ECC_IRQ_DBE_RD_MASK, VE32_CELL_ECC_IRQ_DBE_WR_MASK, \
                                    "VE32_CELL_ECC_IRQ_DBE_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_ECC_IRQCLR_SBE_OFFSET, \
                                    VE32_CELL_ECC_IRQCLR_SBE_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_ECC_IRQCLR_SBE_RD_MASK, VE32_CELL_ECC_IRQCLR_SBE_WR_MASK, \
                                    "VE32_CELL_ECC_IRQCLR_SBE_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_ECC_IRQCLR_DBE_OFFSET, \
                                    VE32_CELL_ECC_IRQCLR_DBE_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_ECC_IRQCLR_DBE_RD_MASK, VE32_CELL_ECC_IRQCLR_DBE_WR_MASK, \
                                    "VE32_CELL_ECC_IRQCLR_DBE_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SEQUENCER_IRQ_STTR_OFFSET, \
                                    VE32_CELL_SEQUENCER_IRQ_STTR_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SEQUENCER_IRQ_STTR_RD_MASK, VE32_CELL_SEQUENCER_IRQ_STTR_WR_MASK, \
                                    "VE32_CELL_SEQUENCER_IRQ_STTR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_IRQPRIO_STTR_IDLE_OFFSET, \
                                    VE32_CELL_IRQPRIO_STTR_IDLE_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_IRQPRIO_STTR_IDLE_RD_MASK, VE32_CELL_IRQPRIO_STTR_IDLE_WR_MASK, \
                                    "VE32_CELL_IRQPRIO_STTR_IDLE_OFFSET");

//            write_read_expect_18a(base_address[i]+VE32_CELL_IRQPRIO_STTR_SLEEP_OFFSET, \
                                    VE32_CELL_IRQPRIO_STTR_SLEEP_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_IRQPRIO_STTR_SLEEP_RD_MASK, VE32_CELL_IRQPRIO_STTR_SLEEP_WR_MASK, \
                                    "VE32_CELL_IRQPRIO_STTR_SLEEP_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_IRQPRIO_STTR_FALSE_START_OFFSET, \
                                    VE32_CELL_IRQPRIO_STTR_FALSE_START_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_IRQPRIO_STTR_FALSE_START_RD_MASK, VE32_CELL_IRQPRIO_STTR_FALSE_START_WR_MASK, \
                                    "VE32_CELL_IRQPRIO_STTR_FALSE_START_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SDFGATE_IRQ_RIDC_OOB_OFFSET, \
                                    VE32_CELL_SDFGATE_IRQ_RIDC_OOB_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SDFGATE_IRQ_RIDC_OOB_RD_MASK, VE32_CELL_SDFGATE_IRQ_RIDC_OOB_WR_MASK, \
                                    "VE32_CELL_SDFGATE_IRQ_RIDC_OOB_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SDFGATE_IRQCLR_RIDC_OOB_OFFSET, \
                                    VE32_CELL_SDFGATE_IRQCLR_RIDC_OOB_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SDFGATE_IRQCLR_RIDC_OOB_RD_MASK, VE32_CELL_SDFGATE_IRQCLR_RIDC_OOB_WR_MASK, \
                                    "VE32_CELL_SDFGATE_IRQCLR_RIDC_OOB_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_BP_DMEM_ARB_DMEM_REQ_OFFSET, \
                                    VE32_CELL_BP_DMEM_ARB_DMEM_REQ_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_BP_DMEM_ARB_DMEM_REQ_RD_MASK, VE32_CELL_BP_DMEM_ARB_DMEM_REQ_WR_MASK, \
                                    "VE32_CELL_BP_DMEM_ARB_DMEM_REQ_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SIMD0_VMEM_ARB_VMEM_WP_OFFSET, \
                                    VE32_CELL_SIMD0_VMEM_ARB_VMEM_WP_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SIMD0_VMEM_ARB_VMEM_WP_RD_MASK, VE32_CELL_SIMD0_VMEM_ARB_VMEM_WP_WR_MASK, \
                                    "VE32_CELL_SIMD0_VMEM_ARB_VMEM_WP_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SIMD0_LUTMEM_ARB_LUTMEM_WP_OFFSET, \
                                    VE32_CELL_SIMD0_LUTMEM_ARB_LUTMEM_WP_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SIMD0_LUTMEM_ARB_LUTMEM_WP_RD_MASK, VE32_CELL_SIMD0_LUTMEM_ARB_LUTMEM_WP_WR_MASK, \
                                    "VE32_CELL_SIMD0_LUTMEM_ARB_LUTMEM_WP_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_CTRL_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_CTRL_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_CTRL_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_CTRL_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_CTRL_BP_CFG_OFFSET");
//Commnting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_CFG_OFFSET");
            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_CFG_OFFSET");
            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_CNT_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_CNT_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_CNT_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_SBE_CNT_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_CNT_BP_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_CNT_BP_CFG_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_CNT_BP_CFG_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_CNT_BP_CFG_RD_MASK, VE32_CELL_LM_ECC_DBE_CNT_BP_CFG_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_CNT_BP_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_CTRL_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_CTRL_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_CTRL_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_CTRL_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_CTRL_BP_DMEM_OFFSET");
//Commnting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_IRQPRIO_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_IRQPRIO_BP_DMEM_OFFSET");
            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_BAD_ADDR_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_BAD_ADDR_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_CNT_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_CNT_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_CNT_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_CNT_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_CNT_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_CNT_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_CNT_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_CNT_BP_DMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_CNT_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_CNT_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_CTRL_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_CTRL_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_CTRL_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_CTRL_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_CTRL_SIMD0_VMEM_OFFSET");
//Commnting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_IRQPRIO_SIMD0_VMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_IRQPRIO_SIMD0_VMEM_OFFSET");
            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_BAD_ADDR_SIMD0_VMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_BAD_ADDR_SIMD0_VMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_SBE_CNT_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_SBE_CNT_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_SBE_CNT_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_SBE_CNT_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_SBE_CNT_SIMD0_VMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_ECC_DBE_CNT_SIMD0_VMEM_OFFSET, \
                                    VE32_CELL_LM_ECC_DBE_CNT_SIMD0_VMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_ECC_DBE_CNT_SIMD0_VMEM_RD_MASK, VE32_CELL_LM_ECC_DBE_CNT_SIMD0_VMEM_WR_MASK, \
                                    "VE32_CELL_LM_ECC_DBE_CNT_SIMD0_VMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_RD_MASK, VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_LM_SDFGATE_RIDC_INT_CTRL_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_SDFGATE_RIDC_INT_CTRL_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_SDFGATE_RIDC_INT_CTRL_BP_DMEM_RD_MASK, VE32_CELL_LM_SDFGATE_RIDC_INT_CTRL_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_SDFGATE_RIDC_INT_CTRL_BP_DMEM_OFFSET");

                        write_read_expect_18a(base_address[i]+VE32_CELL_LM_SDFGATE_RIDC_STAT_BP_DMEM_OFFSET, \
                                    VE32_CELL_LM_SDFGATE_RIDC_STAT_BP_DMEM_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_LM_SDFGATE_RIDC_STAT_BP_DMEM_RD_MASK, VE32_CELL_LM_SDFGATE_RIDC_STAT_BP_DMEM_WR_MASK, \
                                    "VE32_CELL_LM_SDFGATE_RIDC_STAT_BP_DMEM_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SEG_BASE_0_BP_XMEM_EXT_IF_OFFSET, \
                                    VE32_CELL_SEG_BASE_0_BP_XMEM_EXT_IF_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SEG_BASE_0_BP_XMEM_EXT_IF_RD_MASK, VE32_CELL_SEG_BASE_0_BP_XMEM_EXT_IF_WR_MASK, \
                                    "VE32_CELL_SEG_BASE_0_BP_XMEM_EXT_IF_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_CELL_SEG_BASE_0_SIMD0_XVMEM_EXT_IF_OFFSET, \
                                    VE32_CELL_SEG_BASE_0_SIMD0_XVMEM_EXT_IF_DEFAULT, write_data, expected_data, \
                                    VE32_CELL_SEG_BASE_0_SIMD0_XVMEM_EXT_IF_RD_MASK, VE32_CELL_SEG_BASE_0_SIMD0_XVMEM_EXT_IF_WR_MASK, \
                                    "VE32_CELL_SEG_BASE_0_SIMD0_XVMEM_EXT_IF_OFFSET");

        }

    }

}
}
