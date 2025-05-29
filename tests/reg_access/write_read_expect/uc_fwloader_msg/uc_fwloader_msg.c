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
    DLNK_JESD0_PHY_UC_FWLOADER_BASE, DLNK_JESD1_PHY_UC_FWLOADER_BASE, DLNK_JESD2_PHY_UC_FWLOADER_BASE, DLNK_JESD3_PHY_UC_FWLOADER_BASE
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
            write_read_expect_18a(base_address[i]+UC_FWLOADER_MSG_ADDR_OFFSET, \
                                    UC_FWLOADER_MSG_ADDR_OFFSET_DEFAULT, write_data, expected_data, \
                                    UC_FWLOADER_MSG_ADDR_OFFSET_RD_MASK, UC_FWLOADER_MSG_ADDR_OFFSET_WR_MASK, \
                                    "UC_FWLOADER_MSG_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+UC_FWLOADER_MSG_LOAD_DATA_OFFSET, \
                                    UC_FWLOADER_MSG_LOAD_DATA_DEFAULT, write_data, expected_data, \
                                    UC_FWLOADER_MSG_LOAD_DATA_RD_MASK, UC_FWLOADER_MSG_LOAD_DATA_WR_MASK, \
                                    "UC_FWLOADER_MSG_LOAD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+UC_FWLOADER_MSG_FWLOADER_CTRL_OFFSET, \
                                    UC_FWLOADER_MSG_FWLOADER_CTRL_DEFAULT, write_data, expected_data, \
                                    UC_FWLOADER_MSG_FWLOADER_CTRL_RD_MASK, UC_FWLOADER_MSG_FWLOADER_CTRL_WR_MASK, \
                                    "UC_FWLOADER_MSG_FWLOADER_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+UC_FWLOADER_MSG_FWLOADER_APB_CTRL_OFFSET, \
                                    UC_FWLOADER_MSG_FWLOADER_APB_CTRL_DEFAULT, write_data, expected_data, \
                                    UC_FWLOADER_MSG_FWLOADER_APB_CTRL_RD_MASK, UC_FWLOADER_MSG_FWLOADER_APB_CTRL_WR_MASK, \
                                    "UC_FWLOADER_MSG_FWLOADER_APB_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+UC_FWLOADER_MSG_FWLOADER_APB_STAT_OFFSET, \
                                    UC_FWLOADER_MSG_FWLOADER_APB_STAT_DEFAULT, write_data, expected_data, \
                                    UC_FWLOADER_MSG_FWLOADER_APB_STAT_RD_MASK, UC_FWLOADER_MSG_FWLOADER_APB_STAT_WR_MASK, \
                                    "UC_FWLOADER_MSG_FWLOADER_APB_STAT_OFFSET");

        }

    }

}
