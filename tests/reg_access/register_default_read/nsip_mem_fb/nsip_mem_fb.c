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
    uint32_t error = 0;
    int i;
    init();

    uint32_t base_address[] = {MEM_FB0_NSIP_HBI_0_BASE, MEM_FB0_NSIP_HBI_1_BASE,
    MEM_FB1_NSIP_HBI_0_BASE, MEM_FB1_NSIP_HBI_1_BASE
    };

        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
        {
            read_reg_expect_18a(base_address[i]+NSIP_HBI_SCRATCH_OFFSET, \
                                    NSIP_HBI_SCRATCH_DEFAULT, \
                                    NSIP_HBI_SCRATCH_RD_MASK, \
                                    "NSIP_HBI_SCRATCH_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET, \
                                    NSIP_HBI_B2H_FF_FIFO_CTRL_DEFAULT, \
                                    NSIP_HBI_B2H_FF_FIFO_CTRL_RD_MASK, \
                                    "NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET");


            read_reg_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET, \
                                    NSIP_HBI_B2H_CSR_CREDIT_CS_DEFAULT, \
                                    NSIP_HBI_B2H_CSR_CREDIT_CS_RD_MASK, \
                                    "NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, \
                                    NSIP_HBI_B2H_CSR_FLIT_CNT_DEFAULT, \
                                    NSIP_HBI_B2H_CSR_FLIT_CNT_RD_MASK, \
                                    "NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_STAT_OFFSET, \
                                    NSIP_HBI_INTR_INT_STAT_DEFAULT, \
                                    NSIP_HBI_INTR_INT_STAT_RD_MASK, \
                                    "NSIP_HBI_INTR_INT_STAT_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, \
                                    NSIP_HBI_INTR_INT_HIGH_EN_DEFAULT, \
                                    NSIP_HBI_INTR_INT_HIGH_EN_RD_MASK, \
                                    "NSIP_HBI_INTR_INT_HIGH_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_LOW_EN_OFFSET, \
                                    NSIP_HBI_INTR_INT_LOW_EN_DEFAULT, \
                                    NSIP_HBI_INTR_INT_LOW_EN_RD_MASK, \
                                    "NSIP_HBI_INTR_INT_LOW_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_CLR_OFFSET, \
                                    NSIP_HBI_INTR_INT_CLR_DEFAULT, \
                                    NSIP_HBI_INTR_INT_CLR_RD_MASK, \
                                    "NSIP_HBI_INTR_INT_CLR_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_FORCE_OFFSET, \
                                    NSIP_HBI_INTR_INT_FORCE_DEFAULT, \
                                    NSIP_HBI_INTR_INT_FORCE_RD_MASK, \
                                    "NSIP_HBI_INTR_INT_FORCE_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON00_OFFSET, \
                                    NSIP_HBI_SMON_SMON00_DEFAULT, \
                                    NSIP_HBI_SMON_SMON00_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON00_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON01_OFFSET, \
                                    NSIP_HBI_SMON_SMON01_DEFAULT, \
                                    NSIP_HBI_SMON_SMON01_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON01_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON02_OFFSET, \
                                    NSIP_HBI_SMON_SMON02_DEFAULT, \
                                    NSIP_HBI_SMON_SMON02_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON02_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON03_OFFSET, \
                                    NSIP_HBI_SMON_SMON03_DEFAULT, \
                                    NSIP_HBI_SMON_SMON03_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON03_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON04_OFFSET, \
                                    NSIP_HBI_SMON_SMON04_DEFAULT, \
                                    NSIP_HBI_SMON_SMON04_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON04_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON05_OFFSET, \
                                    NSIP_HBI_SMON_SMON05_DEFAULT, \
                                    NSIP_HBI_SMON_SMON05_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON05_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON07_OFFSET, \
                                    NSIP_HBI_SMON_SMON07_DEFAULT, \
                                    NSIP_HBI_SMON_SMON07_RD_MASK, \
                                    "NSIP_HBI_SMON_SMON07_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_DEFAULT, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_RD_MASK, \
                                    "NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_DEFAULT, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_RD,\
                                    "NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, \
                                    NSIP_HBI_H2B_FF_FIFO_CTRL_DEFAULT, \
                                    NSIP_HBI_H2B_FF_FIFO_CTRL_RD_MASK, \
                                    "NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_FLIT_CNT_OFFSET, \
                                    NSIP_HBI_H2B_FLIT_CNT_DEFAULT, \
                                    NSIP_HBI_H2B_FLIT_CNT_RD_MASK, \
                                    "NSIP_HBI_H2B_FLIT_CNT_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_MD_CMD_STRM_EN_DEFAULT, \
                                    NSIP_HBI_MD_CMD_STRM_EN_RD_MASK, \
                                    "NSIP_HBI_MD_CMD_STRM_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_MSG_OFFSET, \
                                    NSIP_HBI_MD_CMD_MSG_DEFAULT, \
                                    NSIP_HBI_MD_CMD_MSG_RD_MASK, \
                                    "NSIP_HBI_MD_CMD_MSG_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_MD_CMD_CTRL_DEFAULT, \
                                    NSIP_HBI_MD_CMD_CTRL_RD_MASK, \
                                    "NSIP_HBI_MD_CMD_CTRL_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SCNT_PRL_SEQ_CNT_OFFSET, \
                                    NSIP_HBI_SCNT_PRL_SEQ_CNT_DEFAULT, \
                                    NSIP_HBI_SCNT_PRL_SEQ_CNT_RD_MASK, \
                                    "NSIP_HBI_SCNT_PRL_SEQ_CNT_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_SCNT_PRL_STRM_EN_OFFSET, \
                                    NSIP_HBI_SCNT_PRL_STRM_EN_DEFAULT, \
                                    NSIP_HBI_SCNT_PRL_STRM_EN_RD_MASK, \
                                    "NSIP_HBI_SCNT_PRL_STRM_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL4_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL5_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL6_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL7_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL8_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL9_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL10_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL11_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL12_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL13_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL14_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL15_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL16_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL17_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL18_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL19_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL20_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL21_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL22_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL23_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL24_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL25_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL26_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL27_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL28_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL29_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL30_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_CTRL_TBL31_OFFSET, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_DEFAULT, \
                                    NSIP_HBI_H2B_MD_CTRL_TBL_RD_MASK, \
                                    "NSIP_HBI_H2B_MD_CTRL_TBL31_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR0_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR0_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR1_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR1_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR2_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR2_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR3_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR3_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR4_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR4_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR5_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR5_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR6_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR6_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR7_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR7_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR8_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR8_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR9_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR9_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR10_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR10_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR11_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR11_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR12_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR12_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR13_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR13_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR14_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR14_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR15_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR15_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR16_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR16_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR17_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR17_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR18_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR18_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR19_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR19_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR20_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR20_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR21_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR21_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR22_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR22_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR23_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR23_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR24_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR24_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR25_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR25_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR26_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR26_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR27_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR27_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR28_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR28_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR29_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR29_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR30_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR30_OFFSET");

            read_reg_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR31_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR31_OFFSET");


    }

}
