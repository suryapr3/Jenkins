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
    FB_ANT0_CMEM_CFG0_BASE, FB_ANT0_CMEM_CFG1_BASE, FB_ANT1_CMEM_CFG0_BASE, FB_ANT1_CMEM_CFG1_BASE
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
            write_read_expect_18a(base_address[i]+CMEM_CFG_SCRATCH_OFFSET, \
                                    CMEM_CFG_SCRATCH_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_SCRATCH_RD_MASK, CMEM_CFG_SCRATCH_WR_MASK, \
                                    "CMEM_CFG_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_OFFSET, \
                                    CMEM_CFG_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_RD_MASK, CMEM_CFG_WR_MASK, \
                                    "CMEM_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_START_OFFSET, \
                                    CMEM_CFG_START_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_START_RD_MASK, CMEM_CFG_START_WR_MASK, \
                                    "CMEM_CFG_START_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_END_OFFSET, \
                                    CMEM_CFG_END_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_END_RD_MASK, CMEM_CFG_END_WR_MASK, \
                                    "CMEM_CFG_END_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_CUR_OFFSET, \
                                    CMEM_CFG_CUR_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_CUR_RD_MASK, CMEM_CFG_CUR_WR_MASK, \
                                    "CMEM_CFG_CUR_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_MODE_OFFSET, \
                                    CMEM_CFG_MODE_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_MODE_RD_MASK, CMEM_CFG_MODE_WR_MASK, \
                                    "CMEM_CFG_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_LFSR_SEED_OFFSET, \
                                    CMEM_CFG_LFSR_SEED_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_LFSR_SEED_RD_MASK, CMEM_CFG_LFSR_SEED_WR_MASK, \
                                    "CMEM_CFG_LFSR_SEED_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_FIXED_PATTERN_OFFSET, \
                                    CMEM_CFG_FIXED_PATTERN_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_FIXED_PATTERN_RD_MASK, CMEM_CFG_FIXED_PATTERN_WR_MASK, \
                                    "CMEM_CFG_FIXED_PATTERN_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_RAMP_CFG_OFFSET, \
                                    CMEM_CFG_RAMP_CFG_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_RAMP_CFG_RD_MASK, CMEM_CFG_RAMP_CFG_WR_MASK, \
                                    "CMEM_CFG_RAMP_CFG_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+CMEM_CFG_INIT_RAM_OFFSET, \
                                    CMEM_CFG_INIT_RAM_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INIT_RAM_RD_MASK, CMEM_CFG_INIT_RAM_WR_MASK, \
                                    "CMEM_CFG_INIT_RAM_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ERR_STAT_OFFSET, \
                                    CMEM_CFG_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ERR_STAT_RD_MASK, CMEM_CFG_ERR_STAT_WR_MASK, \
                                    "CMEM_CFG_ERR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_INT_STAT_OFFSET, \
                                    CMEM_CFG_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INT_STAT_RD_MASK, CMEM_CFG_INT_STAT_WR_MASK, \
                                    "CMEM_CFG_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_INT_HI_EN_OFFSET, \
                                    CMEM_CFG_INT_HI_EN_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INT_HI_EN_RD_MASK, CMEM_CFG_INT_HI_EN_WR_MASK, \
                                    "CMEM_CFG_INT_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_INT_LO_EN_OFFSET, \
                                    CMEM_CFG_INT_LO_EN_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INT_LO_EN_RD_MASK, CMEM_CFG_INT_LO_EN_WR_MASK, \
                                    "CMEM_CFG_INT_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_INT_CLR_OFFSET, \
                                    CMEM_CFG_INT_CLR_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INT_CLR_RD_MASK, CMEM_CFG_INT_CLR_WR_MASK, \
                                    "CMEM_CFG_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_INT_FORCE_OFFSET, \
                                    CMEM_CFG_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_INT_FORCE_RD_MASK, CMEM_CFG_INT_FORCE_WR_MASK, \
                                    "CMEM_CFG_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO0_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO0_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO1_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO1_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO2_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO2_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO3_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO3_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO4_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO4_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO5_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO5_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO6_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO6_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_INFO7_OFFSET, \
                                    CMEM_CFG_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_INFO_RD_MASK, CMEM_CFG_ECC_ERR_INFO_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_INFO7_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL0_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL1_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL2_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL3_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL4_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL4_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL5_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL5_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL6_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL6_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_CTRL7_OFFSET, \
                                    CMEM_CFG_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_CTRL_RD_MASK, CMEM_CFG_ECC_CTRL_WR_MASK, \
                                    "CMEM_CFG_ECC_CTRL7_OFFSET");

            write_read_expect_18a(base_address[i]+CMEM_CFG_ECC_ERR_STAT_OFFSET, \
                                    CMEM_CFG_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_ECC_ERR_STAT_RD_MASK, CMEM_CFG_ECC_ERR_STAT_WR_MASK, \
                                    "CMEM_CFG_ECC_ERR_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+CMEM_CFG_APB_BRDG_STAT_OFFSET, \
                                    CMEM_CFG_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    CMEM_CFG_APB_BRDG_STAT_RD_MASK, CMEM_CFG_APB_BRDG_STAT_WR_MASK, \
                                    "CMEM_CFG_APB_BRDG_STAT_OFFSET");

        }

    }

}
