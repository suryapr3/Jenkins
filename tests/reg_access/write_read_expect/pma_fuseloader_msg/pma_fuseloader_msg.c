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
    DLNK_JESD0_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD1_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD2_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD3_PHY_PMA0_FUSELOADER_BASE
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
            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_CTRL_STAT_OFFSET, \
                                    PMA_FUSELOADER_MSG_CTRL_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_CTRL_STAT_RD_MASK, PMA_FUSELOADER_MSG_CTRL_STAT_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_CTRL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_CTRL_OFFSET, \
                                    PMA_FUSELOADER_MSG_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_CTRL_RD_MASK, PMA_FUSELOADER_MSG_CTRL_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_0_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_0_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_0_RD_MASK, PMA_FUSELOADER_MSG_ADDR_0_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_0_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_0_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_0_RD_MASK, PMA_FUSELOADER_MSG_VAL_0_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_1_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_1_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_1_RD_MASK, PMA_FUSELOADER_MSG_ADDR_1_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_1_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_1_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_1_RD_MASK, PMA_FUSELOADER_MSG_VAL_1_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_2_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_2_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_2_RD_MASK, PMA_FUSELOADER_MSG_ADDR_2_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_2_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_2_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_2_RD_MASK, PMA_FUSELOADER_MSG_VAL_2_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_3_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_3_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_3_RD_MASK, PMA_FUSELOADER_MSG_ADDR_3_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_3_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_3_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_3_RD_MASK, PMA_FUSELOADER_MSG_VAL_3_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_4_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_4_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_4_RD_MASK, PMA_FUSELOADER_MSG_ADDR_4_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_4_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_4_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_4_RD_MASK, PMA_FUSELOADER_MSG_VAL_4_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_5_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_5_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_5_RD_MASK, PMA_FUSELOADER_MSG_ADDR_5_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_5_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_5_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_5_RD_MASK, PMA_FUSELOADER_MSG_VAL_5_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_6_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_6_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_6_RD_MASK, PMA_FUSELOADER_MSG_ADDR_6_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_6_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_6_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_6_RD_MASK, PMA_FUSELOADER_MSG_VAL_6_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_7_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_7_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_ADDR_7_RD_MASK, PMA_FUSELOADER_MSG_ADDR_7_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_ADDR_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_7_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_7_DEFAULT, write_data, expected_data, \
                                    PMA_FUSELOADER_MSG_VAL_7_RD_MASK, PMA_FUSELOADER_MSG_VAL_7_WR_MASK, \
                                    "PMA_FUSELOADER_MSG_VAL_7_OFFSET");

        }

    }

}
