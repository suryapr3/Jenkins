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


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    int i;
    init();

    uint32_t base_address[] = {
    RCS_SSPDMA0_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+SSPDMA_CR0_OFFSET, \
                                    SSPDMA_CR0_DEFAULT, \
                                    SSPDMA_CR0_RD_MASK, "SSPDMA_CR0_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CR1_OFFSET, \
                                    SSPDMA_CR1_DEFAULT, \
                                    SSPDMA_CR1_RD_MASK, "SSPDMA_CR1_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_DR_OFFSET, \
                                    SSPDMA_DR_DEFAULT, \
                                    SSPDMA_DR_RD_MASK, "SSPDMA_DR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_SR_OFFSET, \
                                    SSPDMA_SR_DEFAULT, \
                                    SSPDMA_SR_RD_MASK, "SSPDMA_SR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CPSR_OFFSET, \
                                    SSPDMA_CPSR_DEFAULT, \
                                    SSPDMA_CPSR_RD_MASK, "SSPDMA_CPSR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_IMSC_OFFSET, \
                                    SSPDMA_IMSC_DEFAULT, \
                                    SSPDMA_IMSC_RD_MASK, "SSPDMA_IMSC_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_RIS_OFFSET, \
                                    SSPDMA_RIS_DEFAULT, \
                                    SSPDMA_RIS_RD_MASK, "SSPDMA_RIS_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_MIS_OFFSET, \
                                    SSPDMA_MIS_DEFAULT, \
                                    SSPDMA_MIS_RD_MASK, "SSPDMA_MIS_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_ICR_OFFSET, \
                                    SSPDMA_ICR_DEFAULT, \
                                    SSPDMA_ICR_RD_MASK, "SSPDMA_ICR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_DMACR_OFFSET, \
                                    SSPDMA_DMACR_DEFAULT, \
                                    SSPDMA_DMACR_RD_MASK, "SSPDMA_DMACR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CSR_OFFSET, \
                                    SSPDMA_CSR_DEFAULT, \
                                    SSPDMA_CSR_RD_MASK, "SSPDMA_CSR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_TCR_OFFSET, \
                                    SSPDMA_TCR_DEFAULT, \
                                    SSPDMA_TCR_RD_MASK, "SSPDMA_TCR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_ITIP_OFFSET, \
                                    SSPDMA_ITIP_DEFAULT, \
                                    SSPDMA_ITIP_RD_MASK, "SSPDMA_ITIP_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_ITOP_OFFSET, \
                                    SSPDMA_ITOP_DEFAULT, \
                                    SSPDMA_ITOP_RD_MASK, "SSPDMA_ITOP_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_TDR_OFFSET, \
                                    SSPDMA_TDR_DEFAULT, \
                                    SSPDMA_TDR_RD_MASK, "SSPDMA_TDR_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PERIPHID0_OFFSET, \
                                    SSPDMA_PERIPHID0_DEFAULT, \
                                    SSPDMA_PERIPHID0_RD_MASK, "SSPDMA_PERIPHID0_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PERIPHID1_OFFSET, \
                                    SSPDMA_PERIPHID1_DEFAULT, \
                                    SSPDMA_PERIPHID1_RD_MASK, "SSPDMA_PERIPHID1_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PERIPHID2_OFFSET, \
                                    SSPDMA_PERIPHID2_DEFAULT, \
                                    SSPDMA_PERIPHID2_RD_MASK, "SSPDMA_PERIPHID2_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PERIPHID3_OFFSET, \
                                    SSPDMA_PERIPHID3_DEFAULT, \
                                    SSPDMA_PERIPHID3_RD_MASK, "SSPDMA_PERIPHID3_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PCELLID0_OFFSET, \
                                    SSPDMA_PCELLID0_DEFAULT, \
                                    SSPDMA_PCELLID0_RD_MASK, "SSPDMA_PCELLID0_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PCELLID1_OFFSET, \
                                    SSPDMA_PCELLID1_DEFAULT, \
                                    SSPDMA_PCELLID1_RD_MASK, "SSPDMA_PCELLID1_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PCELLID2_OFFSET, \
                                    SSPDMA_PCELLID2_DEFAULT, \
                                    SSPDMA_PCELLID2_RD_MASK, "SSPDMA_PCELLID2_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_PCELLID3_OFFSET, \
                                    SSPDMA_PCELLID3_DEFAULT, \
                                    SSPDMA_PCELLID3_RD_MASK, "SSPDMA_PCELLID3_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CTL_OFFSET, \
                                    SSPDMA_CTL_DEFAULT, \
                                    SSPDMA_CTL_RD_MASK, "SSPDMA_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CFG_OFFSET, \
                                    SSPDMA_CFG_DEFAULT, \
                                    SSPDMA_CFG_RD_MASK, "SSPDMA_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_ADDR_LO_OFFSET, \
                                    SSPDMA_ADDR_LO_DEFAULT, \
                                    SSPDMA_ADDR_LO_RD_MASK, "SSPDMA_ADDR_LO_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_ADDR_HI_OFFSET, \
                                    SSPDMA_ADDR_HI_DEFAULT, \
                                    SSPDMA_ADDR_HI_RD_MASK, "SSPDMA_ADDR_HI_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_STAT_OFFSET, \
                                    SSPDMA_STAT_DEFAULT, \
                                    SSPDMA_STAT_RD_MASK, "SSPDMA_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_CRC32_OFFSET, \
                                    SSPDMA_CRC32_DEFAULT, \
                                    SSPDMA_CRC32_RD_MASK, "SSPDMA_CRC32_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_STAT_OFFSET, \
                                    SSPDMA_LVL_IRQ_STAT_DEFAULT, \
                                    SSPDMA_LVL_IRQ_STAT_RD_MASK, "SSPDMA_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_MASK_OFFSET, \
                                    SSPDMA_LVL_IRQ_MASK_DEFAULT, \
                                    SSPDMA_LVL_IRQ_MASK_RD_MASK, "SSPDMA_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_INV_OFFSET, \
                                    SSPDMA_LVL_IRQ_INV_DEFAULT, \
                                    SSPDMA_LVL_IRQ_INV_RD_MASK, "SSPDMA_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_LVL_IRQ_NOMASK_OFFSET, \
                                    SSPDMA_LVL_IRQ_NOMASK_DEFAULT, \
                                    SSPDMA_LVL_IRQ_NOMASK_RD_MASK, "SSPDMA_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_STAT_OFFSET, \
                                    SSPDMA_EDG_IRQ_STAT_DEFAULT, \
                                    SSPDMA_EDG_IRQ_STAT_RD_MASK, "SSPDMA_EDG_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_MASK_OFFSET, \
                                    SSPDMA_EDG_IRQ_MASK_DEFAULT, \
                                    SSPDMA_EDG_IRQ_MASK_RD_MASK, "SSPDMA_EDG_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_INV_OFFSET, \
                                    SSPDMA_EDG_IRQ_INV_DEFAULT, \
                                    SSPDMA_EDG_IRQ_INV_RD_MASK, "SSPDMA_EDG_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_NOMASK_OFFSET, \
                                    SSPDMA_EDG_IRQ_NOMASK_DEFAULT, \
                                    SSPDMA_EDG_IRQ_NOMASK_RD_MASK, "SSPDMA_EDG_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+SSPDMA_EDG_IRQ_RAW_OFFSET, \
                                    SSPDMA_EDG_IRQ_RAW_DEFAULT, \
                                    SSPDMA_EDG_IRQ_RAW_RD_MASK, "SSPDMA_EDG_IRQ_RAW_OFFSET");

    }

}
