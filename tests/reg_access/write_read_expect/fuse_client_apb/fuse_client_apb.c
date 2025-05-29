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
    SYSCON_FUSE_CLIENT_APB_BASE
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
            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_RD_MASK, FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_RD_MASK, FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_RD_MASK, FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_WR_MASK, \
                                    "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_0_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_1_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_2_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_2_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_3_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_3_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_4_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_4_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_4_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_4_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_5_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_5_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_5_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_5_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_6_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_6_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_6_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_6_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_7_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_7_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_7_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_7_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_8_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_8_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_8_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_8_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_9_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_9_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_9_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_9_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_10_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_10_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_10_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_10_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_10_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_11_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_11_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_11_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_11_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_11_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_12_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_12_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_12_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_12_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_12_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_13_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_13_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_13_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_13_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_13_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_14_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_14_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_14_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_14_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_14_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_15_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_15_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_15_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_15_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_15_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_16_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_16_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_16_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_16_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_16_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_17_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_17_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_17_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_17_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_17_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_18_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_18_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_18_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_18_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_18_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_19_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_19_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_19_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_19_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_19_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_20_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_20_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_20_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_20_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_20_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_21_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_21_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_21_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_21_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_21_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_22_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_22_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_22_RD_MASK, FUSE_CLIENT_APB_ANALOG_REGISTER_22_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_REGISTER_22_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_RD_MASK, FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_RD_MASK, FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_00_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_00_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_00_RD_MASK, FUSE_CLIENT_APB_ANALOG_RESERVE_00_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_RESERVE_00_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_01_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_01_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_01_RD_MASK, FUSE_CLIENT_APB_ANALOG_RESERVE_01_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_RESERVE_01_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_02_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_02_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_02_RD_MASK, FUSE_CLIENT_APB_ANALOG_RESERVE_02_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_RESERVE_02_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_03_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_03_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_03_RD_MASK, FUSE_CLIENT_APB_ANALOG_RESERVE_03_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_RESERVE_03_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_04_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_04_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_04_RD_MASK, FUSE_CLIENT_APB_ANALOG_RESERVE_04_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_RESERVE_04_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_RD_MASK, FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_WR_MASK, \
                                    "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_0_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_0_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_1_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_1_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_2_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_2_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_3_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_3_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_4_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_4_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_4_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_4_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_5_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_5_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_5_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_5_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_6_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_6_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_6_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_6_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_7_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_7_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_7_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_7_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_8_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_8_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_8_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_8_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_9_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_9_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_9_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_9_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_10_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_10_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_10_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_10_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_10_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_11_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_11_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_11_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_11_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_11_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_12_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_12_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_12_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_12_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_12_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_13_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_13_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_13_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_13_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_13_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_14_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_14_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_14_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_14_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_14_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_15_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_15_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_15_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_15_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_15_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_16_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_16_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_16_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_16_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_16_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_17_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_17_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_17_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_17_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_17_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_18_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_18_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_18_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_18_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_18_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_19_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_19_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_19_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_19_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_19_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_20_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_20_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_20_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_20_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_20_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_21_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_21_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_21_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_21_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_21_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_22_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_22_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_22_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_22_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_22_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_23_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_23_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_23_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_23_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_23_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_24_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_24_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_24_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_24_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_24_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_25_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_25_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_25_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_25_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_25_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_26_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_26_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_26_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_26_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_26_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_27_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_27_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_27_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_27_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_27_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_28_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_28_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_28_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_28_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_28_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_29_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_29_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_29_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_29_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_29_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_30_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_30_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_30_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_30_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_30_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_31_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_31_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_31_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_31_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_31_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_32_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_32_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_32_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_32_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_32_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_33_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_33_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_33_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_33_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_33_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_34_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_34_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_34_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_34_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_34_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_35_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_35_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_35_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_35_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_35_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_36_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_36_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_36_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_36_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_36_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_37_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_37_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_37_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_37_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_37_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_38_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_38_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_38_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_38_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_38_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_39_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_39_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_39_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_39_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_39_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_40_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_40_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_40_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_40_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_40_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_41_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_41_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_41_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_41_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_41_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_42_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_42_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_42_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_42_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_42_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_43_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_43_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_43_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_43_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_43_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_44_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_44_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_44_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_44_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_44_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_45_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_45_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_45_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_45_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_45_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_46_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_46_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_46_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_46_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_46_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_47_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_47_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_47_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_47_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_47_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_48_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_48_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_48_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_48_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_48_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_49_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_49_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_49_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_49_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_49_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_50_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_50_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_50_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_50_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_50_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_51_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_51_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_51_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_51_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_51_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_52_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_52_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_52_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_52_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_52_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_53_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_53_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_53_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_53_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_53_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_54_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_54_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_54_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_54_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_54_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_55_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_55_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_55_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_55_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_55_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_56_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_56_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_56_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_56_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_56_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_57_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_57_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_57_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_57_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_57_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_58_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_58_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_58_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_58_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_58_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_59_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_59_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_59_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_59_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_59_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_60_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_60_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_60_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_60_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_60_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_61_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_61_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_61_RD_MASK, FUSE_CLIENT_APB_SERDES_REGISTER_61_WR_MASK, \
                                    "FUSE_CLIENT_APB_SERDES_REGISTER_61_OFFSET");

        }

    }

}
