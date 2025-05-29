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
    ANT0_ASC0_BASE, ANT0_ASC1_BASE, ANT0_ASC2_BASE, ANT0_ASC3_BASE, ANT0_ASC_FB_BASE,
    ANT1_ASC0_BASE, ANT1_ASC1_BASE, ANT1_ASC2_BASE, ANT1_ASC3_BASE, ANT1_ASC_FB_BASE,
    ANT2_ASC0_BASE, ANT2_ASC1_BASE, ANT2_ASC2_BASE, ANT2_ASC3_BASE, ANT2_ASC_FB_BASE,
    ANT3_ASC0_BASE, ANT3_ASC1_BASE, ANT3_ASC2_BASE, ANT3_ASC3_BASE, ANT3_ASC_FB_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE0_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE0_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE0_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE0_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE1_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE1_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE1_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE1_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE2_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE2_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE2_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE2_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE3_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE3_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE3_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE3_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE4_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE4_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE4_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE4_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE5_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE5_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE5_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE5_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE6_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE6_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE6_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE6_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE7_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE7_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE7_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE7_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE8_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE8_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE8_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE8_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE9_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE9_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE9_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE9_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE10_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE10_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE10_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE10_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE11_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE11_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE11_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE11_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE12_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE12_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE12_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE12_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE13_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE13_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE13_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE13_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE14_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE14_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE14_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE14_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE15_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE15_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE15_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE15_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT1_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT2_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT3_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT4_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT5_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT6_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT7_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT8_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT9_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT10_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT11_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT12_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT13_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT14_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT15_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT16_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT17_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT18_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT19_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT19_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT20_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT20_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT21_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT21_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT22_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT22_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT23_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT23_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT24_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT24_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT25_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT25_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT26_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT26_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT27_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT27_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT28_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT28_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT29_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT29_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT30_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT30_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT31_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT31_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W_LUT32_OFFSET, \
                                    ASC_SLICE_W_LUT_DEFAULT, \
                                    ASC_SLICE_W_LUT_RD_MASK, "ASC_SLICE16_W_LUT32_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W1_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W2_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W3_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W4_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W5_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W6_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W7_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W8_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W9_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W10_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W11_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W12_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W13_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W14_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W15_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W16_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W16_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W17_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W17_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_W18_OFFSET, \
                                    ASC_SLICE_W_DEFAULT, \
                                    ASC_SLICE_W_RD_MASK, "ASC_SLICE16_W18_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SLICE16_C_OFFSET, \
                                    ASC_SLICE_C_DEFAULT, \
                                    ASC_SLICE_C_RD_MASK, "ASC_SLICE16_C_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW0_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW1_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW2_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW3_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW4_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW5_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW6_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW7_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW8_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW9_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW10_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW11_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW12_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW13_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW14_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_SHDW15_OFFSET, \
                                    ASC_XTALK_M1_SHDW_DEFAULT, \
                                    ASC_XTALK_M1_SHDW_RD_MASK, "ASC_XTALK_M1_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW0_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW1_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW2_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW3_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW4_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW5_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW6_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW7_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW8_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW9_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW10_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW11_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW12_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW13_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW14_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_SHDW15_OFFSET, \
                                    ASC_XTALK_N0_SHDW_DEFAULT, \
                                    ASC_XTALK_N0_SHDW_RD_MASK, "ASC_XTALK_N0_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW0_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW1_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW2_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW3_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW4_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW5_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW6_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW7_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW8_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW9_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW10_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW11_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW12_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW13_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW14_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_SHDW15_OFFSET, \
                                    ASC_XTALK_P1_SHDW_DEFAULT, \
                                    ASC_XTALK_P1_SHDW_RD_MASK, "ASC_XTALK_P1_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE0_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE1_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE2_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE3_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE4_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE5_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE6_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE7_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE8_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE9_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE10_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE11_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE12_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE13_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE14_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_M1_LIVE15_OFFSET, \
                                    ASC_XTALK_M1_LIVE_DEFAULT, \
                                    ASC_XTALK_M1_LIVE_RD_MASK, "ASC_XTALK_M1_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE0_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE1_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE2_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE3_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE4_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE5_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE6_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE7_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE8_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE9_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE10_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE11_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE12_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE13_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE14_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_N0_LIVE15_OFFSET, \
                                    ASC_XTALK_N0_LIVE_DEFAULT, \
                                    ASC_XTALK_N0_LIVE_RD_MASK, "ASC_XTALK_N0_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE0_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE1_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE2_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE3_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE4_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE5_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE6_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE7_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE8_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE9_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE10_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE11_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE12_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE13_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE14_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_XTALK_P1_LIVE15_OFFSET, \
                                    ASC_XTALK_P1_LIVE_DEFAULT, \
                                    ASC_XTALK_P1_LIVE_RD_MASK, "ASC_XTALK_P1_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_SCRATCH_OFFSET, \
                                    ASC_SCRATCH_DEFAULT, \
                                    ASC_SCRATCH_RD_MASK, "ASC_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_CFG_OFFSET, \
                                    ASC_CFG_DEFAULT, \
                                    ASC_CFG_RD_MASK, "ASC_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_CTRL_OFFSET, \
                                    ASC_CTRL_DEFAULT, \
                                    ASC_CTRL_RD_MASK, "ASC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_CSR_CFG_OFFSET, \
                                    ASC_CSR_CFG_DEFAULT, \
                                    ASC_CSR_CFG_RD_MASK, "ASC_CSR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_CSR_ERR_OFFSET, \
                                    ASC_CSR_ERR_DEFAULT, \
                                    ASC_CSR_ERR_RD_MASK, "ASC_CSR_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_APB_BRDG_STAT_OFFSET, \
                                    ASC_APB_BRDG_STAT_DEFAULT, \
                                    ASC_APB_BRDG_STAT_RD_MASK, "ASC_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_INT_STAT_OFFSET, \
                                    ASC_INT_STAT_DEFAULT, \
                                    ASC_INT_STAT_RD_MASK, "ASC_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_INT_HIGH_EN_OFFSET, \
                                    ASC_INT_HIGH_EN_DEFAULT, \
                                    ASC_INT_HIGH_EN_RD_MASK, "ASC_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_INT_LOW_EN_OFFSET, \
                                    ASC_INT_LOW_EN_DEFAULT, \
                                    ASC_INT_LOW_EN_RD_MASK, "ASC_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_INT_CLR_OFFSET, \
                                    ASC_INT_CLR_DEFAULT, \
                                    ASC_INT_CLR_RD_MASK, "ASC_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+ASC_INT_FORCE_OFFSET, \
                                    ASC_INT_FORCE_DEFAULT, \
                                    ASC_INT_FORCE_RD_MASK, "ASC_INT_FORCE_OFFSET");

    }

}
