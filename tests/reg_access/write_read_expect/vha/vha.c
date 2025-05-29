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
    VHA0_BASE, VHA1_BASE, VHA2_BASE, VHA3_BASE, VHA4_BASE,
    VHA5_BASE, VHA6_BASE, VHA7_BASE
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
            write_read_expect_18a(base_address[i]+VHA_SCRATCH_OFFSET, \
                                    VHA_SCRATCH_DEFAULT, write_data, expected_data, \
                                    VHA_SCRATCH_RD_MASK, VHA_SCRATCH_WR_MASK, \
                                    "VHA_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DP_INIT_OFFSET, \
                                    VHA_DP_INIT_DEFAULT, write_data, expected_data, \
                                    VHA_DP_INIT_RD_MASK, VHA_DP_INIT_WR_MASK, \
                                    "VHA_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_CFG_OFFSET, \
                                    VHA_CFG_DEFAULT, write_data, expected_data, \
                                    VHA_CFG_RD_MASK, VHA_CFG_WR_MASK, \
                                    "VHA_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DL_CTL_OFFSET, \
                                    VHA_DL_CTL_DEFAULT, write_data, expected_data, \
                                    VHA_DL_CTL_RD_MASK, VHA_DL_CTL_WR_MASK, \
                                    "VHA_DL_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DL_IF_CFG_OFFSET, \
                                    VHA_DL_IF_CFG_DEFAULT, write_data, expected_data, \
                                    VHA_DL_IF_CFG_RD_MASK, VHA_DL_IF_CFG_WR_MASK, \
                                    "VHA_DL_IF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DL_SWG_CFG_OFFSET, \
                                    VHA_DL_SWG_CFG_DEFAULT, write_data, expected_data, \
                                    VHA_DL_SWG_CFG_RD_MASK, VHA_DL_SWG_CFG_WR_MASK, \
                                    "VHA_DL_SWG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DL_STAT_OFFSET, \
                                    VHA_DL_STAT_DEFAULT, write_data, expected_data, \
                                    VHA_DL_STAT_RD_MASK, VHA_DL_STAT_WR_MASK, \
                                    "VHA_DL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_UL_CTL_OFFSET, \
                                    VHA_UL_CTL_DEFAULT, write_data, expected_data, \
                                    VHA_UL_CTL_RD_MASK, VHA_UL_CTL_WR_MASK, \
                                    "VHA_UL_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_UL_IF_CFG_OFFSET, \
                                    VHA_UL_IF_CFG_DEFAULT, write_data, expected_data, \
                                    VHA_UL_IF_CFG_RD_MASK, VHA_UL_IF_CFG_WR_MASK, \
                                    "VHA_UL_IF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_UL_SWG_CFG_OFFSET, \
                                    VHA_UL_SWG_CFG_DEFAULT, write_data, expected_data, \
                                    VHA_UL_SWG_CFG_RD_MASK, VHA_UL_SWG_CFG_WR_MASK, \
                                    "VHA_UL_SWG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_UL_STAT_OFFSET, \
                                    VHA_UL_STAT_DEFAULT, write_data, expected_data, \
                                    VHA_UL_STAT_RD_MASK, VHA_UL_STAT_WR_MASK, \
                                    "VHA_UL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_DP_INIT_DONE_OFFSET, \
                                    VHA_DP_INIT_DONE_DEFAULT, write_data, expected_data, \
                                    VHA_DP_INIT_DONE_RD_MASK, VHA_DP_INIT_DONE_WR_MASK, \
                                    "VHA_DP_INIT_DONE_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_INT_HIGH_STAT_OFFSET, \
                                    VHA_INT_HIGH_STAT_DEFAULT, write_data, expected_data, \
                                    VHA_INT_HIGH_STAT_RD_MASK, VHA_INT_HIGH_STAT_WR_MASK, \
                                    "VHA_INT_HIGH_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+VHA_INT_LOW_STAT_OFFSET, \
                                    VHA_INT_LOW_STAT_DEFAULT, write_data, expected_data, \
                                    VHA_INT_LOW_STAT_RD_MASK, VHA_INT_LOW_STAT_WR_MASK, \
                                    "VHA_INT_LOW_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+VHA_APB_BRDG_STAT_OFFSET, \
                                    VHA_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    VHA_APB_BRDG_STAT_RD_MASK, VHA_APB_BRDG_STAT_WR_MASK, \
                                    "VHA_APB_BRDG_STAT_OFFSET");

        }

    }

}
