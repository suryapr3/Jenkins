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
    FB_ANT0_CMEM_CFG0_BASE, FB_ANT0_CMEM_CFG1_BASE, FB_ANT1_CMEM_CFG0_BASE, FB_ANT1_CMEM_CFG1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+CMEM_CFG_SCRATCH_OFFSET, \
                                    CMEM_CFG_SCRATCH_DEFAULT, \
                                    CMEM_CFG_SCRATCH_RD_MASK, "CMEM_CFG_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_OFFSET, \
                                    CMEM_CFG_DEFAULT, \
                                    CMEM_CFG_RD_MASK, "CMEM_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_START_OFFSET, \
                                    CMEM_CFG_START_DEFAULT, \
                                    CMEM_CFG_START_RD_MASK, "CMEM_CFG_START_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_END_OFFSET, \
                                    CMEM_CFG_END_DEFAULT, \
                                    CMEM_CFG_END_RD_MASK, "CMEM_CFG_END_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_CUR_OFFSET, \
                                    CMEM_CFG_CUR_DEFAULT, \
                                    CMEM_CFG_CUR_RD_MASK, "CMEM_CFG_CUR_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_MODE_OFFSET, \
                                    CMEM_CFG_MODE_DEFAULT, \
                                    CMEM_CFG_MODE_RD_MASK, "CMEM_CFG_MODE_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_LFSR_SEED_OFFSET, \
                                    CMEM_CFG_LFSR_SEED_DEFAULT, \
                                    CMEM_CFG_LFSR_SEED_RD_MASK, "CMEM_CFG_LFSR_SEED_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_FIXED_PATTERN_OFFSET, \
                                    CMEM_CFG_FIXED_PATTERN_DEFAULT, \
                                    CMEM_CFG_FIXED_PATTERN_RD_MASK, "CMEM_CFG_FIXED_PATTERN_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_RAMP_CFG_OFFSET, \
                                    CMEM_CFG_RAMP_CFG_DEFAULT, \
                                    CMEM_CFG_RAMP_CFG_RD_MASK, "CMEM_CFG_RAMP_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INIT_RAM_OFFSET, \
                                    CMEM_CFG_INIT_RAM_DEFAULT, \
                                    CMEM_CFG_INIT_RAM_RD_MASK, "CMEM_CFG_INIT_RAM_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ERR_STAT_OFFSET, \
                                    CMEM_CFG_ERR_STAT_DEFAULT, \
                                    CMEM_CFG_ERR_STAT_RD_MASK, "CMEM_CFG_ERR_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INT_STAT_OFFSET, \
                                    CMEM_CFG_INT_STAT_DEFAULT, \
                                    CMEM_CFG_INT_STAT_RD_MASK, "CMEM_CFG_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INT_HI_EN_OFFSET, \
                                    CMEM_CFG_INT_HI_EN_DEFAULT, \
                                    CMEM_CFG_INT_HI_EN_RD_MASK, "CMEM_CFG_INT_HI_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INT_LO_EN_OFFSET, \
                                    CMEM_CFG_INT_LO_EN_DEFAULT, \
                                    CMEM_CFG_INT_LO_EN_RD_MASK, "CMEM_CFG_INT_LO_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INT_CLR_OFFSET, \
                                    CMEM_CFG_INT_CLR_DEFAULT, \
                                    CMEM_CFG_INT_CLR_RD_MASK, "CMEM_CFG_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_INT_FORCE_OFFSET, \
                                    CMEM_CFG_INT_FORCE_DEFAULT, \
                                    CMEM_CFG_INT_FORCE_RD_MASK, "CMEM_CFG_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO0_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO0_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO1_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO1_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO2_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO2_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO3_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO3_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO4_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO4_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO5_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO5_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO6_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO6_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO7_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, "CMEM_CFG_ECC_ERR_INFO7_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL0_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL1_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL2_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL3_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL3_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL4_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL4_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL5_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL5_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL6_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL6_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL7_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, "CMEM_CFG_ECC_CTRL7_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_STAT_OFFSET, \
                                    CMEM_CFG_ECC_ERR_STAT_DEFAULT, \
                                    CMEM_CFG_ECC_ERR_STAT_RD_MASK, "CMEM_CFG_ECC_ERR_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CMEM_CFG_APB_BRDG_STAT_OFFSET, \
                                    CMEM_CFG_APB_BRDG_STAT_DEFAULT, \
                                    CMEM_CFG_APB_BRDG_STAT_RD_MASK, "CMEM_CFG_APB_BRDG_STAT_OFFSET");

    }

}
