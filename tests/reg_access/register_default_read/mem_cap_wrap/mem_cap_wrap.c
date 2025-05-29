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
    MEM_CAP0_BASE, MEM_CAP1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL0_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL1_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL2_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL3_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL4_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL5_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MUX_SEL6_OFFSET, \
                                    MEM_CAP_WRAP_MUX_SEL_DEFAULT, \
                                    MEM_CAP_WRAP_MUX_SEL_RD_MASK, "MEM_CAP_WRAP_MUX_SEL6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR0_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR1_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR2_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR3_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR4_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR5_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_MEM_ERR6_OFFSET, \
                                    MEM_CAP_WRAP_MEM_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_MEM_ERR_RD_MASK, "MEM_CAP_WRAP_MEM_ERR6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR0_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR1_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR2_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR3_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR4_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR5_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_ERR6_OFFSET, \
                                    MEM_CAP_WRAP_ECC_ERR_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_ERR_RD_MASK, "MEM_CAP_WRAP_ECC_ERR6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CORRECT_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CORRECT_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CORRECT_RD_MASK, "MEM_CAP_WRAP_ECC_CORRECT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET, \
                                    MEM_CAP_WRAP_PWR_DOWN_CTRL_DEFAULT, \
                                    MEM_CAP_WRAP_PWR_DOWN_CTRL_RD_MASK, "MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG0_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG1_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG2_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG3_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG4_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG5_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG6_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG7_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG8_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG8_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG9_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG9_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG10_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG10_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG11_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG11_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG12_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG12_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG13_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG13_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG14_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG14_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG15_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG15_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG16_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG16_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG17_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG17_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG18_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG18_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG19_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG19_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG20_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG20_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG21_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG21_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG22_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG22_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG23_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG23_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG24_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG24_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG25_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG25_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG26_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG26_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_CFG27_OFFSET, \
                                    MEM_CAP_WRAP_ECC_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_CFG_RD_MASK, "MEM_CAP_WRAP_ECC_CFG27_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_LVL0_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_LVL0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_LVL1_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_LVL1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_LVL2_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_LVL2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_LVL3_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_LVL3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_DBE_LVL0_OFFSET, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_DBE_LVL0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_DBE_LVL1_OFFSET, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_DBE_LVL1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_DBE_LVL2_OFFSET, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_DBE_LVL2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_DBE_LVL3_OFFSET, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_DBE_LVL_RD_MASK, "MEM_CAP_WRAP_ECC_DBE_LVL3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_CNT_OVFL0_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_CNT_OVFL0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_CNT_OVFL1_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_CNT_OVFL1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_CNT_OVFL2_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_CNT_OVFL2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_SBE_CNT_OVFL3_OFFSET, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_SBE_CNT_OVFL_RD_MASK, "MEM_CAP_WRAP_ECC_SBE_CNT_OVFL3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_STAT_INDEX_OFFSET, \
                                    MEM_CAP_WRAP_ECC_STAT_INDEX_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_STAT_INDEX_RD_MASK, "MEM_CAP_WRAP_ECC_STAT_INDEX_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_ECC_STAT_OFFSET, \
                                    MEM_CAP_WRAP_ECC_STAT_DEFAULT, \
                                    MEM_CAP_WRAP_ECC_STAT_RD_MASK, "MEM_CAP_WRAP_ECC_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_START0_OFFSET, \
                                    MEM_CAP_WRAP_RX_START_DEFAULT, \
                                    MEM_CAP_WRAP_RX_START_RD_MASK, "MEM_CAP_WRAP_RX_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_START1_OFFSET, \
                                    MEM_CAP_WRAP_RX_START_DEFAULT, \
                                    MEM_CAP_WRAP_RX_START_RD_MASK, "MEM_CAP_WRAP_RX_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_START2_OFFSET, \
                                    MEM_CAP_WRAP_RX_START_DEFAULT, \
                                    MEM_CAP_WRAP_RX_START_RD_MASK, "MEM_CAP_WRAP_RX_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_START3_OFFSET, \
                                    MEM_CAP_WRAP_RX_START_DEFAULT, \
                                    MEM_CAP_WRAP_RX_START_RD_MASK, "MEM_CAP_WRAP_RX_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_START4_OFFSET, \
                                    MEM_CAP_WRAP_RX_START_DEFAULT, \
                                    MEM_CAP_WRAP_RX_START_RD_MASK, "MEM_CAP_WRAP_RX_START4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_END0_OFFSET, \
                                    MEM_CAP_WRAP_RX_END_DEFAULT, \
                                    MEM_CAP_WRAP_RX_END_RD_MASK, "MEM_CAP_WRAP_RX_END0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_END1_OFFSET, \
                                    MEM_CAP_WRAP_RX_END_DEFAULT, \
                                    MEM_CAP_WRAP_RX_END_RD_MASK, "MEM_CAP_WRAP_RX_END1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_END2_OFFSET, \
                                    MEM_CAP_WRAP_RX_END_DEFAULT, \
                                    MEM_CAP_WRAP_RX_END_RD_MASK, "MEM_CAP_WRAP_RX_END2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_END3_OFFSET, \
                                    MEM_CAP_WRAP_RX_END_DEFAULT, \
                                    MEM_CAP_WRAP_RX_END_RD_MASK, "MEM_CAP_WRAP_RX_END3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_END4_OFFSET, \
                                    MEM_CAP_WRAP_RX_END_DEFAULT, \
                                    MEM_CAP_WRAP_RX_END_RD_MASK, "MEM_CAP_WRAP_RX_END4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_CUR0_OFFSET, \
                                    MEM_CAP_WRAP_RX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_RX_CUR_RD_MASK, "MEM_CAP_WRAP_RX_CUR0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_CUR1_OFFSET, \
                                    MEM_CAP_WRAP_RX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_RX_CUR_RD_MASK, "MEM_CAP_WRAP_RX_CUR1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_CUR2_OFFSET, \
                                    MEM_CAP_WRAP_RX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_RX_CUR_RD_MASK, "MEM_CAP_WRAP_RX_CUR2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_CUR3_OFFSET, \
                                    MEM_CAP_WRAP_RX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_RX_CUR_RD_MASK, "MEM_CAP_WRAP_RX_CUR3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_CUR4_OFFSET, \
                                    MEM_CAP_WRAP_RX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_RX_CUR_RD_MASK, "MEM_CAP_WRAP_RX_CUR4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_MODE0_OFFSET, \
                                    MEM_CAP_WRAP_RX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_RX_MODE_RD_MASK, "MEM_CAP_WRAP_RX_MODE0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_MODE1_OFFSET, \
                                    MEM_CAP_WRAP_RX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_RX_MODE_RD_MASK, "MEM_CAP_WRAP_RX_MODE1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_MODE2_OFFSET, \
                                    MEM_CAP_WRAP_RX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_RX_MODE_RD_MASK, "MEM_CAP_WRAP_RX_MODE2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_MODE3_OFFSET, \
                                    MEM_CAP_WRAP_RX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_RX_MODE_RD_MASK, "MEM_CAP_WRAP_RX_MODE3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RX_MODE4_OFFSET, \
                                    MEM_CAP_WRAP_RX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_RX_MODE_RD_MASK, "MEM_CAP_WRAP_RX_MODE4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_START0_OFFSET, \
                                    MEM_CAP_WRAP_TX_START_DEFAULT, \
                                    MEM_CAP_WRAP_TX_START_RD_MASK, "MEM_CAP_WRAP_TX_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_START1_OFFSET, \
                                    MEM_CAP_WRAP_TX_START_DEFAULT, \
                                    MEM_CAP_WRAP_TX_START_RD_MASK, "MEM_CAP_WRAP_TX_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_START2_OFFSET, \
                                    MEM_CAP_WRAP_TX_START_DEFAULT, \
                                    MEM_CAP_WRAP_TX_START_RD_MASK, "MEM_CAP_WRAP_TX_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_START3_OFFSET, \
                                    MEM_CAP_WRAP_TX_START_DEFAULT, \
                                    MEM_CAP_WRAP_TX_START_RD_MASK, "MEM_CAP_WRAP_TX_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_END0_OFFSET, \
                                    MEM_CAP_WRAP_TX_END_DEFAULT, \
                                    MEM_CAP_WRAP_TX_END_RD_MASK, "MEM_CAP_WRAP_TX_END0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_END1_OFFSET, \
                                    MEM_CAP_WRAP_TX_END_DEFAULT, \
                                    MEM_CAP_WRAP_TX_END_RD_MASK, "MEM_CAP_WRAP_TX_END1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_END2_OFFSET, \
                                    MEM_CAP_WRAP_TX_END_DEFAULT, \
                                    MEM_CAP_WRAP_TX_END_RD_MASK, "MEM_CAP_WRAP_TX_END2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_END3_OFFSET, \
                                    MEM_CAP_WRAP_TX_END_DEFAULT, \
                                    MEM_CAP_WRAP_TX_END_RD_MASK, "MEM_CAP_WRAP_TX_END3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_CUR0_OFFSET, \
                                    MEM_CAP_WRAP_TX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_TX_CUR_RD_MASK, "MEM_CAP_WRAP_TX_CUR0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_CUR1_OFFSET, \
                                    MEM_CAP_WRAP_TX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_TX_CUR_RD_MASK, "MEM_CAP_WRAP_TX_CUR1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_CUR2_OFFSET, \
                                    MEM_CAP_WRAP_TX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_TX_CUR_RD_MASK, "MEM_CAP_WRAP_TX_CUR2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_CUR3_OFFSET, \
                                    MEM_CAP_WRAP_TX_CUR_DEFAULT, \
                                    MEM_CAP_WRAP_TX_CUR_RD_MASK, "MEM_CAP_WRAP_TX_CUR3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_MODE0_OFFSET, \
                                    MEM_CAP_WRAP_TX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_TX_MODE_RD_MASK, "MEM_CAP_WRAP_TX_MODE0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_MODE1_OFFSET, \
                                    MEM_CAP_WRAP_TX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_TX_MODE_RD_MASK, "MEM_CAP_WRAP_TX_MODE1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_MODE2_OFFSET, \
                                    MEM_CAP_WRAP_TX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_TX_MODE_RD_MASK, "MEM_CAP_WRAP_TX_MODE2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TX_MODE3_OFFSET, \
                                    MEM_CAP_WRAP_TX_MODE_DEFAULT, \
                                    MEM_CAP_WRAP_TX_MODE_RD_MASK, "MEM_CAP_WRAP_TX_MODE3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER0_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER1_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER2_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER3_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER4_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER5_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_UPPER6_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_UPPER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_UPPER6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER0_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER1_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER2_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER3_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER4_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER5_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_LFSR_SEED_LOWER6_OFFSET, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_DEFAULT, \
                                    MEM_CAP_WRAP_LFSR_SEED_LOWER_RD_MASK, "MEM_CAP_WRAP_LFSR_SEED_LOWER6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN0_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN1_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN2_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN3_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN4_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN5_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_FIXED_PATTERN6_OFFSET, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_DEFAULT, \
                                    MEM_CAP_WRAP_FIXED_PATTERN_RD_MASK, "MEM_CAP_WRAP_FIXED_PATTERN6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG0_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG1_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG2_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG3_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG4_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG5_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_RAMP_CFG6_OFFSET, \
                                    MEM_CAP_WRAP_RAMP_CFG_DEFAULT, \
                                    MEM_CAP_WRAP_RAMP_CFG_RD_MASK, "MEM_CAP_WRAP_RAMP_CFG6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM0_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM1_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM2_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM3_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM4_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM5_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INIT_RAM6_OFFSET, \
                                    MEM_CAP_WRAP_INIT_RAM_DEFAULT, \
                                    MEM_CAP_WRAP_INIT_RAM_RD_MASK, "MEM_CAP_WRAP_INIT_RAM6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_CAPT_OFFSET, \
                                    MEM_CAP_WRAP_CAPT_DEFAULT, \
                                    MEM_CAP_WRAP_CAPT_RD_MASK, "MEM_CAP_WRAP_CAPT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SCRATCH_OFFSET, \
                                    MEM_CAP_WRAP_SCRATCH_DEFAULT, \
                                    MEM_CAP_WRAP_SCRATCH_RD_MASK, "MEM_CAP_WRAP_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TDPACK_FIFO_WM_OFFSET, \
                                    MEM_CAP_WRAP_TDPACK_FIFO_WM_DEFAULT, \
                                    MEM_CAP_WRAP_TDPACK_FIFO_WM_RD_MASK, "MEM_CAP_WRAP_TDPACK_FIFO_WM_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_TDPACK_FIFO_STAT_OFFSET, \
                                    MEM_CAP_WRAP_TDPACK_FIFO_STAT_DEFAULT, \
                                    MEM_CAP_WRAP_TDPACK_FIFO_STAT_RD_MASK, "MEM_CAP_WRAP_TDPACK_FIFO_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INT_STAT_OFFSET, \
                                    MEM_CAP_WRAP_INT_STAT_DEFAULT, \
                                    MEM_CAP_WRAP_INT_STAT_RD_MASK, "MEM_CAP_WRAP_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INT_HIGH_EN_OFFSET, \
                                    MEM_CAP_WRAP_INT_HIGH_EN_DEFAULT, \
                                    MEM_CAP_WRAP_INT_HIGH_EN_RD_MASK, "MEM_CAP_WRAP_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INT_LOW_EN_OFFSET, \
                                    MEM_CAP_WRAP_INT_LOW_EN_DEFAULT, \
                                    MEM_CAP_WRAP_INT_LOW_EN_RD_MASK, "MEM_CAP_WRAP_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INT_CLR_OFFSET, \
                                    MEM_CAP_WRAP_INT_CLR_DEFAULT, \
                                    MEM_CAP_WRAP_INT_CLR_RD_MASK, "MEM_CAP_WRAP_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_INT_FORCE_OFFSET, \
                                    MEM_CAP_WRAP_INT_FORCE_DEFAULT, \
                                    MEM_CAP_WRAP_INT_FORCE_RD_MASK, "MEM_CAP_WRAP_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R0_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R0_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R0_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R1_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R1_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R1_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R2_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R2_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R2_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R3_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R3_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R3_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R4_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R4_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R4_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R5_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R5_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R5_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R6_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R6_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R6_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_SMON_CSR_SMON_R7_OFFSET, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R7_DEFAULT, \
                                    MEM_CAP_WRAP_SMON_CSR_SMON_R7_RD_MASK, "MEM_CAP_WRAP_SMON_CSR_SMON_R7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_WRAP_APB_BRDG_STAT_OFFSET, \
                                    MEM_CAP_WRAP_APB_BRDG_STAT_DEFAULT, \
                                    MEM_CAP_WRAP_APB_BRDG_STAT_RD_MASK, "MEM_CAP_WRAP_APB_BRDG_STAT_OFFSET");

    }

}
