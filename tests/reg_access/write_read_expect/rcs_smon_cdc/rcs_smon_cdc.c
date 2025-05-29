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
    RCS_SMON_VEX_STRM_BASE
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
            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_READ_ID_CMP_OFFSET, \
                                    RCS_SMON_CDC_READ_ID_CMP_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_READ_ID_CMP_RD_MASK, RCS_SMON_CDC_READ_ID_CMP_WR_MASK, \
                                    "RCS_SMON_CDC_READ_ID_CMP_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_WRITE_ID_CMP_OFFSET, \
                                    RCS_SMON_CDC_WRITE_ID_CMP_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_WRITE_ID_CMP_RD_MASK, RCS_SMON_CDC_WRITE_ID_CMP_WR_MASK, \
                                    "RCS_SMON_CDC_WRITE_ID_CMP_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON00_OFFSET, \
                                    RCS_SMON_CDC_SMON00_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON00_RD_MASK, RCS_SMON_CDC_SMON00_WR_MASK, \
                                    "RCS_SMON_CDC_SMON00_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON01_OFFSET, \
                                    RCS_SMON_CDC_SMON01_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON01_RD_MASK, RCS_SMON_CDC_SMON01_WR_MASK, \
                                    "RCS_SMON_CDC_SMON01_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON02_OFFSET, \
                                    RCS_SMON_CDC_SMON02_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON02_RD_MASK, RCS_SMON_CDC_SMON02_WR_MASK, \
                                    "RCS_SMON_CDC_SMON02_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON03_OFFSET, \
                                    RCS_SMON_CDC_SMON03_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON03_RD_MASK, RCS_SMON_CDC_SMON03_WR_MASK, \
                                    "RCS_SMON_CDC_SMON03_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON04_OFFSET, \
                                    RCS_SMON_CDC_SMON04_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON04_RD_MASK, RCS_SMON_CDC_SMON04_WR_MASK, \
                                    "RCS_SMON_CDC_SMON04_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON05_OFFSET, \
                                    RCS_SMON_CDC_SMON05_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON05_RD_MASK, RCS_SMON_CDC_SMON05_WR_MASK, \
                                    "RCS_SMON_CDC_SMON05_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON06_OFFSET, \
                                    RCS_SMON_CDC_SMON06_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON06_RD_MASK, RCS_SMON_CDC_SMON06_WR_MASK, \
                                    "RCS_SMON_CDC_SMON06_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_SMON07_OFFSET, \
                                    RCS_SMON_CDC_SMON07_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_SMON07_RD_MASK, RCS_SMON_CDC_SMON07_WR_MASK, \
                                    "RCS_SMON_CDC_SMON07_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_SMON_CDC_APB_BRDG_STAT_OFFSET, \
                                    RCS_SMON_CDC_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    RCS_SMON_CDC_APB_BRDG_STAT_RD_MASK, RCS_SMON_CDC_APB_BRDG_STAT_WR_MASK, \
                                    "RCS_SMON_CDC_APB_BRDG_STAT_OFFSET");

        }

    }

}
