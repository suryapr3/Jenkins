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
    VHA0_ANT0_BASE, VHA0_ANT1_BASE, VHA1_ANT0_BASE, VHA1_ANT1_BASE, VHA2_ANT0_BASE,
    VHA2_ANT1_BASE, VHA3_ANT0_BASE, VHA3_ANT1_BASE, VHA4_ANT0_BASE, VHA4_ANT1_BASE,
    VHA5_ANT0_BASE, VHA5_ANT1_BASE, VHA6_ANT0_BASE, VHA6_ANT1_BASE, VHA7_ANT0_BASE,
    VHA7_ANT1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+VHA_ANT_SCRATCH_OFFSET, \
                                    VHA_ANT_SCRATCH_DEFAULT, \
                                    VHA_ANT_SCRATCH_RD_MASK, "VHA_ANT_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_CFG_OFFSET, \
                                    VHA_ANT_CFG_DEFAULT, \
                                    VHA_ANT_CFG_RD_MASK, "VHA_ANT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_CFG_OFFSET, \
                                    VHA_ANT_DL_CFG_DEFAULT, \
                                    VHA_ANT_DL_CFG_RD_MASK, "VHA_ANT_DL_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_TX_ALARM_EN_OFFSET, \
                                    VHA_ANT_TX_ALARM_EN_DEFAULT, \
                                    VHA_ANT_TX_ALARM_EN_RD_MASK, "VHA_ANT_TX_ALARM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_CFG0_OFFSET, \
                                    VHA_ANT_DL_IF_CFG_DEFAULT, \
                                    VHA_ANT_DL_IF_CFG_RD_MASK, "VHA_ANT_DL_IF_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_CFG1_OFFSET, \
                                    VHA_ANT_DL_IF_CFG_DEFAULT, \
                                    VHA_ANT_DL_IF_CFG_RD_MASK, "VHA_ANT_DL_IF_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_OF_CFG0_OFFSET, \
                                    VHA_ANT_DL_OF_CFG_DEFAULT, \
                                    VHA_ANT_DL_OF_CFG_RD_MASK, "VHA_ANT_DL_OF_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_OF_CFG1_OFFSET, \
                                    VHA_ANT_DL_OF_CFG_DEFAULT, \
                                    VHA_ANT_DL_OF_CFG_RD_MASK, "VHA_ANT_DL_OF_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_ECC_CTRL0_OFFSET, \
                                    VHA_ANT_DL_IF_ECC_CTRL_DEFAULT, \
                                    VHA_ANT_DL_IF_ECC_CTRL_RD_MASK, "VHA_ANT_DL_IF_ECC_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_ECC_CTRL1_OFFSET, \
                                    VHA_ANT_DL_IF_ECC_CTRL_DEFAULT, \
                                    VHA_ANT_DL_IF_ECC_CTRL_RD_MASK, "VHA_ANT_DL_IF_ECC_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_ARB_CFG_OFFSET, \
                                    VHA_ANT_ARB_CFG_DEFAULT, \
                                    VHA_ANT_ARB_CFG_RD_MASK, "VHA_ANT_ARB_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_CFG_OFFSET, \
                                    VHA_ANT_UL_CFG_DEFAULT, \
                                    VHA_ANT_UL_CFG_RD_MASK, "VHA_ANT_UL_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_IF_CFG_OFFSET, \
                                    VHA_ANT_UL_IF_CFG_DEFAULT, \
                                    VHA_ANT_UL_IF_CFG_RD_MASK, "VHA_ANT_UL_IF_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_IF_ECC_CTRL_OFFSET, \
                                    VHA_ANT_UL_IF_ECC_CTRL_DEFAULT, \
                                    VHA_ANT_UL_IF_ECC_CTRL_RD_MASK, "VHA_ANT_UL_IF_ECC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_OF_CFG0_OFFSET, \
                                    VHA_ANT_UL_OF_CFG_DEFAULT, \
                                    VHA_ANT_UL_OF_CFG_RD_MASK, "VHA_ANT_UL_OF_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_OF_CFG1_OFFSET, \
                                    VHA_ANT_UL_OF_CFG_DEFAULT, \
                                    VHA_ANT_UL_OF_CFG_RD_MASK, "VHA_ANT_UL_OF_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_INT_STAT_OFFSET, \
                                    VHA_ANT_INT_STAT_DEFAULT, \
                                    VHA_ANT_INT_STAT_RD_MASK, "VHA_ANT_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_INT_HIGH_EN_OFFSET, \
                                    VHA_ANT_INT_HIGH_EN_DEFAULT, \
                                    VHA_ANT_INT_HIGH_EN_RD_MASK, "VHA_ANT_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_INT_LOW_EN_OFFSET, \
                                    VHA_ANT_INT_LOW_EN_DEFAULT, \
                                    VHA_ANT_INT_LOW_EN_RD_MASK, "VHA_ANT_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_INT_CLR_OFFSET, \
                                    VHA_ANT_INT_CLR_DEFAULT, \
                                    VHA_ANT_INT_CLR_RD_MASK, "VHA_ANT_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_INT_FORCE_OFFSET, \
                                    VHA_ANT_INT_FORCE_DEFAULT, \
                                    VHA_ANT_INT_FORCE_RD_MASK, "VHA_ANT_INT_FORCE_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+VHA_ANT_APB_BRDG_STAT_OFFSET, \
                                    VHA_ANT_APB_BRDG_STAT_DEFAULT, \
                                    VHA_ANT_APB_BRDG_STAT_RD_MASK, "VHA_ANT_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_STAT0_OFFSET, \
                                    VHA_ANT_DL_IF_STAT_DEFAULT, \
                                    VHA_ANT_DL_IF_STAT_RD_MASK, "VHA_ANT_DL_IF_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_STAT1_OFFSET, \
                                    VHA_ANT_DL_IF_STAT_DEFAULT, \
                                    VHA_ANT_DL_IF_STAT_RD_MASK, "VHA_ANT_DL_IF_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_CC_IF_STAT0_OFFSET, \
                                    VHA_ANT_DL_CC_IF_STAT_DEFAULT, \
                                    VHA_ANT_DL_CC_IF_STAT_RD_MASK, "VHA_ANT_DL_CC_IF_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_CC_IF_STAT1_OFFSET, \
                                    VHA_ANT_DL_CC_IF_STAT_DEFAULT, \
                                    VHA_ANT_DL_CC_IF_STAT_RD_MASK, "VHA_ANT_DL_CC_IF_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_ECC_STAT_OFFSET, \
                                    VHA_ANT_DL_IF_ECC_STAT_DEFAULT, \
                                    VHA_ANT_DL_IF_ECC_STAT_RD_MASK, "VHA_ANT_DL_IF_ECC_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_ECC_INFO0_OFFSET, \
                                    VHA_ANT_DL_IF_ECC_INFO_DEFAULT, \
                                    VHA_ANT_DL_IF_ECC_INFO_RD_MASK, "VHA_ANT_DL_IF_ECC_INFO0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_IF_ECC_INFO1_OFFSET, \
                                    VHA_ANT_DL_IF_ECC_INFO_DEFAULT, \
                                    VHA_ANT_DL_IF_ECC_INFO_RD_MASK, "VHA_ANT_DL_IF_ECC_INFO1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_OF_STAT0_OFFSET, \
                                    VHA_ANT_DL_OF_STAT_DEFAULT, \
                                    VHA_ANT_DL_OF_STAT_RD_MASK, "VHA_ANT_DL_OF_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_OF_STAT1_OFFSET, \
                                    VHA_ANT_DL_OF_STAT_DEFAULT, \
                                    VHA_ANT_DL_OF_STAT_RD_MASK, "VHA_ANT_DL_OF_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_IF_STAT_OFFSET, \
                                    VHA_ANT_UL_IF_STAT_DEFAULT, \
                                    VHA_ANT_UL_IF_STAT_RD_MASK, "VHA_ANT_UL_IF_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_CC_IF_STAT_OFFSET, \
                                    VHA_ANT_UL_CC_IF_STAT_DEFAULT, \
                                    VHA_ANT_UL_CC_IF_STAT_RD_MASK, "VHA_ANT_UL_CC_IF_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_IF_ECC_STAT_OFFSET, \
                                    VHA_ANT_UL_IF_ECC_STAT_DEFAULT, \
                                    VHA_ANT_UL_IF_ECC_STAT_RD_MASK, "VHA_ANT_UL_IF_ECC_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_IF_ECC_INFO_OFFSET, \
                                    VHA_ANT_UL_IF_ECC_INFO_DEFAULT, \
                                    VHA_ANT_UL_IF_ECC_INFO_RD_MASK, "VHA_ANT_UL_IF_ECC_INFO_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_OF_STAT0_OFFSET, \
                                    VHA_ANT_UL_OF_STAT_DEFAULT, \
                                    VHA_ANT_UL_OF_STAT_RD_MASK, "VHA_ANT_UL_OF_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_OF_STAT1_OFFSET, \
                                    VHA_ANT_UL_OF_STAT_DEFAULT, \
                                    VHA_ANT_UL_OF_STAT_RD_MASK, "VHA_ANT_UL_OF_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_ARB_CNT0_OFFSET, \
                                    VHA_ANT_DL_ARB_CNT_DEFAULT, \
                                    VHA_ANT_DL_ARB_CNT_RD_MASK, "VHA_ANT_DL_ARB_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_DL_ARB_CNT1_OFFSET, \
                                    VHA_ANT_DL_ARB_CNT_DEFAULT, \
                                    VHA_ANT_DL_ARB_CNT_RD_MASK, "VHA_ANT_DL_ARB_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_ARB_CNT0_OFFSET, \
                                    VHA_ANT_UL_ARB_CNT_DEFAULT, \
                                    VHA_ANT_UL_ARB_CNT_RD_MASK, "VHA_ANT_UL_ARB_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_UL_ARB_CNT1_OFFSET, \
                                    VHA_ANT_UL_ARB_CNT_DEFAULT, \
                                    VHA_ANT_UL_ARB_CNT_RD_MASK, "VHA_ANT_UL_ARB_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_ARB_STAT_OFFSET, \
                                    VHA_ANT_ARB_STAT_DEFAULT, \
                                    VHA_ANT_ARB_STAT_RD_MASK, "VHA_ANT_ARB_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R0_OFFSET, \
                                    VHA_ANT_SMON_R0_DEFAULT, \
                                    VHA_ANT_SMON_R0_RD_MASK, "VHA_ANT_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R1_OFFSET, \
                                    VHA_ANT_SMON_R1_DEFAULT, \
                                    VHA_ANT_SMON_R1_RD_MASK, "VHA_ANT_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R2_OFFSET, \
                                    VHA_ANT_SMON_R2_DEFAULT, \
                                    VHA_ANT_SMON_R2_RD_MASK, "VHA_ANT_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R3_OFFSET, \
                                    VHA_ANT_SMON_R3_DEFAULT, \
                                    VHA_ANT_SMON_R3_RD_MASK, "VHA_ANT_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R4_OFFSET, \
                                    VHA_ANT_SMON_R4_DEFAULT, \
                                    VHA_ANT_SMON_R4_RD_MASK, "VHA_ANT_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R5_OFFSET, \
                                    VHA_ANT_SMON_R5_DEFAULT, \
                                    VHA_ANT_SMON_R5_RD_MASK, "VHA_ANT_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R6_OFFSET, \
                                    VHA_ANT_SMON_R6_DEFAULT, \
                                    VHA_ANT_SMON_R6_RD_MASK, "VHA_ANT_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_ANT_SMON_R7_OFFSET, \
                                    VHA_ANT_SMON_R7_DEFAULT, \
                                    VHA_ANT_SMON_R7_RD_MASK, "VHA_ANT_SMON_R7_OFFSET");

    }

}
