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
    SYSCON_IFS_FC_APB_BASE
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
            write_read_expect_18a(base_address[i]+FUSE_CTRL_OFFSET, \
                                    FUSE_CTRL_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_RD_MASK, FUSE_CTRL_WR_MASK, \
                                    "FUSE_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_CMD_OFFSET, \
                                    FUSE_CTRL_CMD_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_CMD_RD_MASK, FUSE_CTRL_CMD_WR_MASK, \
                                    "FUSE_CTRL_CMD_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_CNTERS_OFFSET, \
                                    FUSE_CTRL_CNTERS_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_CNTERS_RD_MASK, FUSE_CTRL_CNTERS_WR_MASK, \
                                    "FUSE_CTRL_CNTERS_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_DATA_OFFSET, \
                                    FUSE_CTRL_DATA_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_DATA_RD_MASK, FUSE_CTRL_DATA_WR_MASK, \
                                    "FUSE_CTRL_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_ECC_DATA_OFFSET, \
                                    FUSE_CTRL_ECC_DATA_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_ECC_DATA_RD_MASK, FUSE_CTRL_ECC_DATA_WR_MASK, \
                                    "FUSE_CTRL_ECC_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_STAT_OFFSET, \
                                    FUSE_CTRL_STAT_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_STAT_RD_MASK, FUSE_CTRL_STAT_WR_MASK, \
                                    "FUSE_CTRL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_HIP_ECC_STAT_OFFSET, \
                                    FUSE_CTRL_HIP_ECC_STAT_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_HIP_ECC_STAT_RD_MASK, FUSE_CTRL_HIP_ECC_STAT_WR_MASK, \
                                    "FUSE_CTRL_HIP_ECC_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_DBG_CTRL_OFFSET, \
                                    FUSE_CTRL_DBG_CTRL_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_DBG_CTRL_RD_MASK, FUSE_CTRL_DBG_CTRL_WR_MASK, \
                                    "FUSE_CTRL_DBG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_HIP_OFFSET, \
                                    FUSE_CTRL_HIP_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_HIP_RD_MASK, FUSE_CTRL_HIP_WR_MASK, \
                                    "FUSE_CTRL_HIP_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_HIP_REGISTER_DATA_OFFSET, \
                                    FUSE_CTRL_HIP_REGISTER_DATA_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_HIP_REGISTER_DATA_RD_MASK, FUSE_CTRL_HIP_REGISTER_DATA_WR_MASK, \
                                    "FUSE_CTRL_HIP_REGISTER_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_HIP_CTRL_OFFSET, \
                                    FUSE_CTRL_HIP_CTRL_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_HIP_CTRL_RD_MASK, FUSE_CTRL_HIP_CTRL_WR_MASK, \
                                    "FUSE_CTRL_HIP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_DRNG_ES_CFG0_OFFSET, \
                                    FUSE_CTRL_DRNG_ES_CFG0_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_DRNG_ES_CFG0_RD_MASK, FUSE_CTRL_DRNG_ES_CFG0_WR_MASK, \
                                    "FUSE_CTRL_DRNG_ES_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CTRL_DRNG_ES_CFG1_OFFSET, \
                                    FUSE_CTRL_DRNG_ES_CFG1_DEFAULT, write_data, expected_data, \
                                    FUSE_CTRL_DRNG_ES_CFG1_RD_MASK, FUSE_CTRL_DRNG_ES_CFG1_WR_MASK, \
                                    "FUSE_CTRL_DRNG_ES_CFG1_OFFSET");

        }

    }

}
