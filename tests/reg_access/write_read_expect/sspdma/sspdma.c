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
    RCS_SSPDMA0_BASE
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


        for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
        {
            write_read_expect_18a(base_address[i]+SSPDMA_CR0_OFFSET, \
                                    SSPDMA_CR0_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CR0_RD_MASK, SSPDMA_CR0_WR_MASK, \
                                    "SSPDMA_CR0_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_CR1_OFFSET, \
                                    SSPDMA_CR1_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CR1_RD_MASK, SSPDMA_CR1_WR_MASK, \
                                    "SSPDMA_CR1_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+SSPDMA_DR_OFFSET, \
                                    SSPDMA_DR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_DR_RD_MASK, SSPDMA_DR_WR_MASK, \
                                    "SSPDMA_DR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_SR_OFFSET, \
                                    SSPDMA_SR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_SR_RD_MASK, SSPDMA_SR_WR_MASK, \
                                    "SSPDMA_SR_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+SSPDMA_CPSR_OFFSET, \
                                    SSPDMA_CPSR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CPSR_RD_MASK, SSPDMA_CPSR_WR_MASK, \
                                    "SSPDMA_CPSR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_IMSC_OFFSET, \
                                    SSPDMA_IMSC_DEFAULT, write_data, expected_data, \
                                    SSPDMA_IMSC_RD_MASK, SSPDMA_IMSC_WR_MASK, \
                                    "SSPDMA_IMSC_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_RIS_OFFSET, \
                                    SSPDMA_RIS_DEFAULT, write_data, expected_data, \
                                    SSPDMA_RIS_RD_MASK, SSPDMA_RIS_WR_MASK, \
                                    "SSPDMA_RIS_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_MIS_OFFSET, \
                                    SSPDMA_MIS_DEFAULT, write_data, expected_data, \
                                    SSPDMA_MIS_RD_MASK, SSPDMA_MIS_WR_MASK, \
                                    "SSPDMA_MIS_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_ICR_OFFSET, \
                                    SSPDMA_ICR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_ICR_RD_MASK, SSPDMA_ICR_WR_MASK, \
                                    "SSPDMA_ICR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_DMACR_OFFSET, \
                                    SSPDMA_DMACR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_DMACR_RD_MASK, SSPDMA_DMACR_WR_MASK, \
                                    "SSPDMA_DMACR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_CSR_OFFSET, \
                                    SSPDMA_CSR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CSR_RD_MASK, SSPDMA_CSR_WR_MASK, \
                                    "SSPDMA_CSR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_TCR_OFFSET, \
                                    SSPDMA_TCR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_TCR_RD_MASK, SSPDMA_TCR_WR_MASK, \
                                    "SSPDMA_TCR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_ITIP_OFFSET, \
                                    SSPDMA_ITIP_DEFAULT, write_data, expected_data, \
                                    SSPDMA_ITIP_RD_MASK, SSPDMA_ITIP_WR_MASK, \
                                    "SSPDMA_ITIP_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_ITOP_OFFSET, \
                                    SSPDMA_ITOP_DEFAULT, write_data, expected_data, \
                                    SSPDMA_ITOP_RD_MASK, SSPDMA_ITOP_WR_MASK, \
                                    "SSPDMA_ITOP_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+SSPDMA_TDR_OFFSET, \
                                    SSPDMA_TDR_DEFAULT, write_data, expected_data, \
                                    SSPDMA_TDR_RD_MASK, SSPDMA_TDR_WR_MASK, \
                                    "SSPDMA_TDR_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PERIPHID0_OFFSET, \
                                    SSPDMA_PERIPHID0_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PERIPHID0_RD_MASK, SSPDMA_PERIPHID0_WR_MASK, \
                                    "SSPDMA_PERIPHID0_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PERIPHID1_OFFSET, \
                                    SSPDMA_PERIPHID1_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PERIPHID1_RD_MASK, SSPDMA_PERIPHID1_WR_MASK, \
                                    "SSPDMA_PERIPHID1_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PERIPHID2_OFFSET, \
                                    SSPDMA_PERIPHID2_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PERIPHID2_RD_MASK, SSPDMA_PERIPHID2_WR_MASK, \
                                    "SSPDMA_PERIPHID2_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PERIPHID3_OFFSET, \
                                    SSPDMA_PERIPHID3_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PERIPHID3_RD_MASK, SSPDMA_PERIPHID3_WR_MASK, \
                                    "SSPDMA_PERIPHID3_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PCELLID0_OFFSET, \
                                    SSPDMA_PCELLID0_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PCELLID0_RD_MASK, SSPDMA_PCELLID0_WR_MASK, \
                                    "SSPDMA_PCELLID0_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PCELLID1_OFFSET, \
                                    SSPDMA_PCELLID1_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PCELLID1_RD_MASK, SSPDMA_PCELLID1_WR_MASK, \
                                    "SSPDMA_PCELLID1_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PCELLID2_OFFSET, \
                                    SSPDMA_PCELLID2_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PCELLID2_RD_MASK, SSPDMA_PCELLID2_WR_MASK, \
                                    "SSPDMA_PCELLID2_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_PCELLID3_OFFSET, \
                                    SSPDMA_PCELLID3_DEFAULT, write_data, expected_data, \
                                    SSPDMA_PCELLID3_RD_MASK, SSPDMA_PCELLID3_WR_MASK, \
                                    "SSPDMA_PCELLID3_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_CTL_OFFSET, \
                                    SSPDMA_CTL_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CTL_RD_MASK, SSPDMA_CTL_WR_MASK, \
                                    "SSPDMA_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_CFG_OFFSET, \
                                    SSPDMA_CFG_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CFG_RD_MASK, SSPDMA_CFG_WR_MASK, \
                                    "SSPDMA_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_ADDR_LO_OFFSET, \
                                    SSPDMA_ADDR_LO_DEFAULT, write_data, expected_data, \
                                    SSPDMA_ADDR_LO_RD_MASK, SSPDMA_ADDR_LO_WR_MASK, \
                                    "SSPDMA_ADDR_LO_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_ADDR_HI_OFFSET, \
                                    SSPDMA_ADDR_HI_DEFAULT, write_data, expected_data, \
                                    SSPDMA_ADDR_HI_RD_MASK, SSPDMA_ADDR_HI_WR_MASK, \
                                    "SSPDMA_ADDR_HI_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_STAT_OFFSET, \
                                    SSPDMA_STAT_DEFAULT, write_data, expected_data, \
                                    SSPDMA_STAT_RD_MASK, SSPDMA_STAT_WR_MASK, \
                                    "SSPDMA_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_CRC32_OFFSET, \
                                    SSPDMA_CRC32_DEFAULT, write_data, expected_data, \
                                    SSPDMA_CRC32_RD_MASK, SSPDMA_CRC32_WR_MASK, \
                                    "SSPDMA_CRC32_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_STAT_OFFSET, \
                                    SSPDMA_LVL_IRQ_STAT_DEFAULT, write_data, expected_data, \
                                    SSPDMA_LVL_IRQ_STAT_RD_MASK, SSPDMA_LVL_IRQ_STAT_WR_MASK, \
                                    "SSPDMA_LVL_IRQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_MASK_OFFSET, \
                                    SSPDMA_LVL_IRQ_MASK_DEFAULT, write_data, expected_data, \
                                    SSPDMA_LVL_IRQ_MASK_RD_MASK, SSPDMA_LVL_IRQ_MASK_WR_MASK, \
                                    "SSPDMA_LVL_IRQ_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_INV_OFFSET, \
                                    SSPDMA_LVL_IRQ_INV_DEFAULT, write_data, expected_data, \
                                    SSPDMA_LVL_IRQ_INV_RD_MASK, SSPDMA_LVL_IRQ_INV_WR_MASK, \
                                    "SSPDMA_LVL_IRQ_INV_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_NOMASK_OFFSET, \
                                    SSPDMA_LVL_IRQ_NOMASK_DEFAULT, write_data, expected_data, \
                                    SSPDMA_LVL_IRQ_NOMASK_RD_MASK, SSPDMA_LVL_IRQ_NOMASK_WR_MASK, \
                                    "SSPDMA_LVL_IRQ_NOMASK_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_STAT_OFFSET, \
                                    SSPDMA_EDG_IRQ_STAT_DEFAULT, write_data, expected_data, \
                                    SSPDMA_EDG_IRQ_STAT_RD_MASK, SSPDMA_EDG_IRQ_STAT_WR_MASK, \
                                    "SSPDMA_EDG_IRQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_MASK_OFFSET, \
                                    SSPDMA_EDG_IRQ_MASK_DEFAULT, write_data, expected_data, \
                                    SSPDMA_EDG_IRQ_MASK_RD_MASK, SSPDMA_EDG_IRQ_MASK_WR_MASK, \
                                    "SSPDMA_EDG_IRQ_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_INV_OFFSET, \
                                    SSPDMA_EDG_IRQ_INV_DEFAULT, write_data, expected_data, \
                                    SSPDMA_EDG_IRQ_INV_RD_MASK, SSPDMA_EDG_IRQ_INV_WR_MASK, \
                                    "SSPDMA_EDG_IRQ_INV_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_NOMASK_OFFSET, \
                                    SSPDMA_EDG_IRQ_NOMASK_DEFAULT, write_data, expected_data, \
                                    SSPDMA_EDG_IRQ_NOMASK_RD_MASK, SSPDMA_EDG_IRQ_NOMASK_WR_MASK, \
                                    "SSPDMA_EDG_IRQ_NOMASK_OFFSET");

            write_read_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_RAW_OFFSET, \
                                    SSPDMA_EDG_IRQ_RAW_DEFAULT, write_data, expected_data, \
                                    SSPDMA_EDG_IRQ_RAW_RD_MASK, SSPDMA_EDG_IRQ_RAW_WR_MASK, \
                                    "SSPDMA_EDG_IRQ_RAW_OFFSET");

        }

    }

}
