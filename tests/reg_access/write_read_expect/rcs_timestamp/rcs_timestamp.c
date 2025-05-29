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
    RCS_TIMER_TIMESTAMP_BASE
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
            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL0_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL1_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL2_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL2_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL3_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL3_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL4_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL4_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL5_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL5_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL6_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL6_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL7_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL7_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL8_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL8_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL9_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL9_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL10_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL10_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL11_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL11_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL12_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL12_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL13_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL13_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL14_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL14_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GPIO_SEL15_OFFSET, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GPIO_SEL_RD_MASK, RCS_TIMESTAMP_EC_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GPIO_SEL15_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_GRP_SEL_OFFSET, \
                                    RCS_TIMESTAMP_EC_GRP_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_GRP_SEL_RD_MASK, RCS_TIMESTAMP_EC_GRP_SEL_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_GRP_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_EN_OFFSET, \
                                    RCS_TIMESTAMP_EC_EN_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_EN_RD_MASK, RCS_TIMESTAMP_EC_EN_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_EN_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_WND_START_OFFSET, \
                                    RCS_TIMESTAMP_WND_START_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_WND_START_RD_MASK, RCS_TIMESTAMP_WND_START_WR_MASK, \
                                    "RCS_TIMESTAMP_WND_START_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_SETUP_OFFSET, \
                                    RCS_TIMESTAMP_SETUP_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_SETUP_RD_MASK, RCS_TIMESTAMP_SETUP_WR_MASK, \
                                    "RCS_TIMESTAMP_SETUP_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_7_0_OFFSET, \
                                    RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_7_0_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_7_0_RD_MASK, RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_7_0_WR_MASK, \
                                    "RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_7_0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_15_8_OFFSET, \
                                    RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_15_8_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_15_8_RD_MASK, RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_15_8_WR_MASK, \
                                    "RCS_TIMESTAMP_GPIOGRP_DEBOUNCE_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_OV_ERR_MASK_R_OFFSET, \
                                    RCS_TIMESTAMP_EC_OV_ERR_MASK_R_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_OV_ERR_MASK_R_RD_MASK, RCS_TIMESTAMP_EC_OV_ERR_MASK_R_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_OV_ERR_MASK_R_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_EC_OV_ERR_STAT_R_OFFSET, \
                                    RCS_TIMESTAMP_EC_OV_ERR_STAT_R_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_EC_OV_ERR_STAT_R_RD_MASK, RCS_TIMESTAMP_EC_OV_ERR_STAT_R_WR_MASK, \
                                    "RCS_TIMESTAMP_EC_OV_ERR_STAT_R_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMESTAMP_STAT_R_OFFSET, \
                                    RCS_TIMESTAMP_STAT_R_DEFAULT, write_data, expected_data, \
                                    RCS_TIMESTAMP_STAT_R_RD_MASK, RCS_TIMESTAMP_STAT_R_WR_MASK, \
                                    "RCS_TIMESTAMP_STAT_R_OFFSET");

        }

    }

}
