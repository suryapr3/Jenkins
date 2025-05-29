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
    SYSCON_FUSE_CLIENT_ECM_BASE
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
            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_ID_ECM_ID_0_OFFSET, \
                                    FUSE_CLIENT_ECM_ID_ECM_ID_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_ID_ECM_ID_0_RD_MASK, FUSE_CLIENT_ECM_ID_ECM_ID_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_ID_ECM_ID_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_0_OFFSET, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_0_RD_MASK, FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_1_OFFSET, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_1_RD_MASK, FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_1_WR_MASK, \
                                    "FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_2_OFFSET, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_2_RD_MASK, FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_2_WR_MASK, \
                                    "FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_3_OFFSET, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_3_RD_MASK, FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_3_WR_MASK, \
                                    "FUSE_CLIENT_ECM_INTEL_TST_ECM_INTEL_TEST_OEM_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_LOCK_ECM_LOCK_OFFSET, \
                                    FUSE_CLIENT_ECM_LOCK_ECM_LOCK_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_LOCK_ECM_LOCK_RD_MASK, FUSE_CLIENT_ECM_LOCK_ECM_LOCK_WR_MASK, \
                                    "FUSE_CLIENT_ECM_LOCK_ECM_LOCK_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_0_OFFSET, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_0_RD_MASK, FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_1_OFFSET, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_1_RD_MASK, FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_1_WR_MASK, \
                                    "FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_2_OFFSET, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_2_RD_MASK, FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_2_WR_MASK, \
                                    "FUSE_CLIENT_ECM_ACCESS_ECM_ACCESS_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OVRIDE_ECM_OVRIDE_0_OFFSET, \
                                    FUSE_CLIENT_ECM_OVRIDE_ECM_OVRIDE_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OVRIDE_ECM_OVRIDE_0_RD_MASK, FUSE_CLIENT_ECM_OVRIDE_ECM_OVRIDE_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OVRIDE_ECM_OVRIDE_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_00_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_00_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_00_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_00_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_00_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_01_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_01_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_01_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_01_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_01_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_02_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_02_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_02_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_02_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_02_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_03_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_03_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_03_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_03_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_03_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_10_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_10_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_10_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_10_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_10_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_11_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_11_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_11_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_11_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_11_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_12_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_12_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_12_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_12_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_12_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_13_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_13_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_13_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_13_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_13_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_20_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_20_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_20_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_20_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_20_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_21_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_21_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_21_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_21_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_21_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_22_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_22_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_22_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_22_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_22_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_23_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_23_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_23_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_23_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_23_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_30_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_30_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_30_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_30_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_30_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_31_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_31_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_31_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_31_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_31_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_32_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_32_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_32_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_32_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_32_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_33_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_33_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_33_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_33_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_33_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_40_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_40_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_40_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_40_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_40_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_41_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_41_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_41_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_41_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_41_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_42_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_42_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_42_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_42_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_42_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_43_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_43_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_43_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_43_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_43_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_50_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_50_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_50_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_50_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_50_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_51_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_51_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_51_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_51_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_51_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_52_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_52_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_52_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_52_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_52_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_53_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_53_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_53_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_53_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_53_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_60_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_60_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_60_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_60_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_60_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_61_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_61_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_61_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_61_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_61_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_62_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_62_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_62_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_62_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_62_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_63_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_63_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_63_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_63_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_63_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_70_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_70_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_70_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_70_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_70_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_71_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_71_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_71_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_71_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_71_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_72_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_72_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_72_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_72_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_72_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_73_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_73_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_73_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_73_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_73_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_80_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_80_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_80_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_80_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_80_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_81_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_81_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_81_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_81_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_81_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_82_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_82_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_82_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_82_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_82_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_83_OFFSET, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_83_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_83_RD_MASK, FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_83_WR_MASK, \
                                    "FUSE_CLIENT_ECM_RB_ENTR_ECM_RB_ENTR_83_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_0_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_0_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_1_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_1_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_1_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_2_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_2_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_2_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_3_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_3_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_3_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_4_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_4_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_4_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_4_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_4_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_5_OFFSET, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_5_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_5_RD_MASK, FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_5_WR_MASK, \
                                    "FUSE_CLIENT_ECM_SPARE_MAJ_ECM_SPARE_MAJ_5_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_0_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_0_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_0_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_0_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_1_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_1_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_1_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_1_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_2_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_2_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_2_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_2_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_3_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_3_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_3_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_3_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_4_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_4_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_4_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_4_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_4_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_5_OFFSET, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_5_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_5_RD_MASK, FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_5_WR_MASK, \
                                    "FUSE_CLIENT_ECM_OEM_SPARE_ECM_OEM_SPARE_5_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_SEL_OFFSET, \
                                    FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_SEL_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_SEL_RD_MASK, FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_SEL_WR_MASK, \
                                    "FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_VAL_OFFSET, \
                                    FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_VAL_DEFAULT, write_data, expected_data, \
                                    FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_VAL_RD_MASK, FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_VAL_WR_MASK, \
                                    "FUSE_CLIENT_ECM_MAJ_DBG_ECM_MAJFUNC_DBG_VAL_OFFSET");

        }

    }

}
