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
    SYSCON_FUSE_CLIENT_APB_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_FUSE_REGISTER_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_2_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_3_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_4_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_5_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_6_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_7_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_8_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_DEFAULT, \
                                    FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_RD_MASK, "FUSE_CLIENT_APB_ABCSOC_HVM_SPARE_FUSE_REGISTER_9_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_0_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_1_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_2_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_2_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_2_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_3_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_3_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_3_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_4_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_4_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_4_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_5_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_5_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_5_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_6_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_6_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_6_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_7_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_7_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_7_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_8_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_8_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_8_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_9_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_9_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_9_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_10_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_10_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_10_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_10_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_11_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_11_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_11_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_11_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_12_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_12_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_12_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_12_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_13_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_13_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_13_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_13_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_14_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_14_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_14_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_14_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_15_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_15_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_15_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_15_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_16_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_16_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_16_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_16_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_17_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_17_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_17_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_17_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_18_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_18_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_18_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_18_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_19_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_19_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_19_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_19_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_20_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_20_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_20_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_20_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_21_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_21_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_21_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_21_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_REGISTER_22_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_22_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_REGISTER_22_RD_MASK, "FUSE_CLIENT_APB_ANALOG_REGISTER_22_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_RD_MASK, "FUSE_CLIENT_APB_ANALOG_BG_TRIM_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_RD_MASK, "FUSE_CLIENT_APB_ANALOG_BG_TRIM_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_00_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_00_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_00_RD_MASK, "FUSE_CLIENT_APB_ANALOG_RESERVE_00_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_01_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_01_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_01_RD_MASK, "FUSE_CLIENT_APB_ANALOG_RESERVE_01_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_02_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_02_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_02_RD_MASK, "FUSE_CLIENT_APB_ANALOG_RESERVE_02_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_03_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_03_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_03_RD_MASK, "FUSE_CLIENT_APB_ANALOG_RESERVE_03_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_RESERVE_04_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_04_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_RESERVE_04_RD_MASK, "FUSE_CLIENT_APB_ANALOG_RESERVE_04_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_2_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA0_HWC4016C_3_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_2_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_OFFSET, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_DEFAULT, \
                                    FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_RD_MASK, "FUSE_CLIENT_APB_ANALOG_ANA1_HWC4016C_3_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_0_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_0_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_0_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_1_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_1_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_1_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_2_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_2_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_2_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_2_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_3_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_3_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_3_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_3_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_4_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_4_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_4_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_4_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_5_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_5_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_5_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_5_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_6_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_6_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_6_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_6_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_7_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_7_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_7_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_7_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_8_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_8_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_8_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_8_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_9_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_9_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_9_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_9_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_10_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_10_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_10_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_10_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_11_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_11_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_11_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_11_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_12_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_12_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_12_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_12_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_13_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_13_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_13_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_13_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_14_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_14_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_14_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_14_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_15_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_15_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_15_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_15_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_16_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_16_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_16_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_16_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_17_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_17_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_17_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_17_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_18_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_18_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_18_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_18_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_19_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_19_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_19_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_19_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_20_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_20_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_20_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_20_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_21_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_21_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_21_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_21_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_22_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_22_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_22_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_22_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_23_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_23_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_23_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_23_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_24_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_24_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_24_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_24_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_25_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_25_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_25_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_25_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_26_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_26_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_26_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_26_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_27_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_27_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_27_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_27_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_28_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_28_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_28_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_28_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_29_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_29_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_29_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_29_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_30_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_30_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_30_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_30_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_31_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_31_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_31_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_31_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_32_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_32_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_32_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_32_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_33_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_33_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_33_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_33_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_34_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_34_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_34_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_34_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_35_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_35_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_35_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_35_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_36_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_36_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_36_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_36_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_37_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_37_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_37_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_37_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_38_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_38_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_38_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_38_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_39_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_39_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_39_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_39_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_40_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_40_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_40_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_40_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_41_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_41_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_41_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_41_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_42_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_42_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_42_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_42_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_43_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_43_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_43_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_43_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_44_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_44_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_44_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_44_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_45_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_45_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_45_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_45_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_46_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_46_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_46_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_46_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_47_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_47_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_47_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_47_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_48_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_48_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_48_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_48_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_49_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_49_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_49_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_49_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_50_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_50_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_50_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_50_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_51_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_51_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_51_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_51_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_52_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_52_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_52_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_52_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_53_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_53_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_53_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_53_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_54_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_54_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_54_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_54_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_55_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_55_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_55_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_55_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_56_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_56_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_56_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_56_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_57_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_57_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_57_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_57_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_58_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_58_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_58_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_58_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_59_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_59_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_59_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_59_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_60_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_60_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_60_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_60_OFFSET");

        read_reg_expect_18a(base_address[i]+FUSE_CLIENT_APB_SERDES_REGISTER_61_OFFSET, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_61_DEFAULT, \
                                    FUSE_CLIENT_APB_SERDES_REGISTER_61_RD_MASK, "FUSE_CLIENT_APB_SERDES_REGISTER_61_OFFSET");

    }

}
