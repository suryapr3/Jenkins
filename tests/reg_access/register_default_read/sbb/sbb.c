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
    SYSCON_SBB_MODULE_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+SBB_SEMAPHORE_OFFSET, \
                                    SBB_SEMAPHORE_DEFAULT, \
                                    SBB_SEMAPHORE_RD_MASK, "SBB_SEMAPHORE_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_FUNCTION_OFFSET, \
                                    SBB_FUNCTION_DEFAULT, \
                                    SBB_FUNCTION_RD_MASK, "SBB_FUNCTION_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_AUTH_STAT_PARAM_OFFSET, \
                                    SBB_AUTH_STAT_PARAM_DEFAULT, \
                                    SBB_AUTH_STAT_PARAM_RD_MASK, "SBB_AUTH_STAT_PARAM_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_AUTH_STAT_OFFSET, \
                                    SBB_AUTH_STAT_DEFAULT, \
                                    SBB_AUTH_STAT_RD_MASK, "SBB_AUTH_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_STAT0_OFFSET, \
                                    SBB_STAT0_DEFAULT, \
                                    SBB_STAT0_RD_MASK, "SBB_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_STAT1_OFFSET, \
                                    SBB_STAT1_DEFAULT, \
                                    SBB_STAT1_RD_MASK, "SBB_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_DBG0_OFFSET, \
                                    SBB_DBG0_DEFAULT, \
                                    SBB_DBG0_RD_MASK, "SBB_DBG0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_DBG1_OFFSET, \
                                    SBB_DBG1_DEFAULT, \
                                    SBB_DBG1_RD_MASK, "SBB_DBG1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VENDOR0_OFFSET, \
                                    SBB_VENDOR0_DEFAULT, \
                                    SBB_VENDOR0_RD_MASK, "SBB_VENDOR0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VENDOR1_OFFSET, \
                                    SBB_VENDOR1_DEFAULT, \
                                    SBB_VENDOR1_RD_MASK, "SBB_VENDOR1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_RSLT0_OFFSET, \
                                    SBB_RSLT0_DEFAULT, \
                                    SBB_RSLT0_RD_MASK, "SBB_RSLT0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_RSLT1_OFFSET, \
                                    SBB_RSLT1_DEFAULT, \
                                    SBB_RSLT1_RD_MASK, "SBB_RSLT1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_ACTRL_VERIF_OFFSET, \
                                    SBB_MEAS_ACTRL_VERIF_DEFAULT, \
                                    SBB_MEAS_ACTRL_VERIF_RD_MASK, "SBB_MEAS_ACTRL_VERIF_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_ACTRL_SBB_OFFSET, \
                                    SBB_MEAS_ACTRL_SBB_DEFAULT, \
                                    SBB_MEAS_ACTRL_SBB_RD_MASK, "SBB_MEAS_ACTRL_SBB_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_ACTRL_EXT_OFFSET, \
                                    SBB_MEAS_ACTRL_EXT_DEFAULT, \
                                    SBB_MEAS_ACTRL_EXT_RD_MASK, "SBB_MEAS_ACTRL_EXT_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_ACTRL_CLR_OFFSET, \
                                    SBB_MEAS_ACTRL_CLR_DEFAULT, \
                                    SBB_MEAS_ACTRL_CLR_RD_MASK, "SBB_MEAS_ACTRL_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_UNIQUE_ID0_OFFSET, \
                                    SBB_UNIQUE_ID0_DEFAULT, \
                                    SBB_UNIQUE_ID0_RD_MASK, "SBB_UNIQUE_ID0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_UNIQUE_ID1_OFFSET, \
                                    SBB_UNIQUE_ID1_DEFAULT, \
                                    SBB_UNIQUE_ID1_RD_MASK, "SBB_UNIQUE_ID1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_HW_VER0_OFFSET, \
                                    SBB_HW_VER0_DEFAULT, \
                                    SBB_HW_VER0_RD_MASK, "SBB_HW_VER0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_HW_VER1_OFFSET, \
                                    SBB_HW_VER1_DEFAULT, \
                                    SBB_HW_VER1_RD_MASK, "SBB_HW_VER1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H0_OFFSET, \
                                    SBB_MEAS_H0_DEFAULT, \
                                    SBB_MEAS_H0_RD_MASK, "SBB_MEAS_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L0_OFFSET, \
                                    SBB_MEAS_L0_DEFAULT, \
                                    SBB_MEAS_L0_RD_MASK, "SBB_MEAS_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H1_OFFSET, \
                                    SBB_MEAS_H1_DEFAULT, \
                                    SBB_MEAS_H1_RD_MASK, "SBB_MEAS_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L1_OFFSET, \
                                    SBB_MEAS_L1_DEFAULT, \
                                    SBB_MEAS_L1_RD_MASK, "SBB_MEAS_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H2_OFFSET, \
                                    SBB_MEAS_H2_DEFAULT, \
                                    SBB_MEAS_H2_RD_MASK, "SBB_MEAS_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L2_OFFSET, \
                                    SBB_MEAS_L2_DEFAULT, \
                                    SBB_MEAS_L2_RD_MASK, "SBB_MEAS_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H3_OFFSET, \
                                    SBB_MEAS_H3_DEFAULT, \
                                    SBB_MEAS_H3_RD_MASK, "SBB_MEAS_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L3_OFFSET, \
                                    SBB_MEAS_L3_DEFAULT, \
                                    SBB_MEAS_L3_RD_MASK, "SBB_MEAS_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H4_OFFSET, \
                                    SBB_MEAS_H4_DEFAULT, \
                                    SBB_MEAS_H4_RD_MASK, "SBB_MEAS_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L4_OFFSET, \
                                    SBB_MEAS_L4_DEFAULT, \
                                    SBB_MEAS_L4_RD_MASK, "SBB_MEAS_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H5_OFFSET, \
                                    SBB_MEAS_H5_DEFAULT, \
                                    SBB_MEAS_H5_RD_MASK, "SBB_MEAS_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L5_OFFSET, \
                                    SBB_MEAS_L5_DEFAULT, \
                                    SBB_MEAS_L5_RD_MASK, "SBB_MEAS_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H6_OFFSET, \
                                    SBB_MEAS_H6_DEFAULT, \
                                    SBB_MEAS_H6_RD_MASK, "SBB_MEAS_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L6_OFFSET, \
                                    SBB_MEAS_L6_DEFAULT, \
                                    SBB_MEAS_L6_RD_MASK, "SBB_MEAS_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H7_OFFSET, \
                                    SBB_MEAS_H7_DEFAULT, \
                                    SBB_MEAS_H7_RD_MASK, "SBB_MEAS_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L7_OFFSET, \
                                    SBB_MEAS_L7_DEFAULT, \
                                    SBB_MEAS_L7_RD_MASK, "SBB_MEAS_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H8_OFFSET, \
                                    SBB_MEAS_H8_DEFAULT, \
                                    SBB_MEAS_H8_RD_MASK, "SBB_MEAS_H8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L8_OFFSET, \
                                    SBB_MEAS_L8_DEFAULT, \
                                    SBB_MEAS_L8_RD_MASK, "SBB_MEAS_L8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H9_OFFSET, \
                                    SBB_MEAS_H9_DEFAULT, \
                                    SBB_MEAS_H9_RD_MASK, "SBB_MEAS_H9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L9_OFFSET, \
                                    SBB_MEAS_L9_DEFAULT, \
                                    SBB_MEAS_L9_RD_MASK, "SBB_MEAS_L9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H10_OFFSET, \
                                    SBB_MEAS_H10_DEFAULT, \
                                    SBB_MEAS_H10_RD_MASK, "SBB_MEAS_H10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L10_OFFSET, \
                                    SBB_MEAS_L10_DEFAULT, \
                                    SBB_MEAS_L10_RD_MASK, "SBB_MEAS_L10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H11_OFFSET, \
                                    SBB_MEAS_H11_DEFAULT, \
                                    SBB_MEAS_H11_RD_MASK, "SBB_MEAS_H11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L11_OFFSET, \
                                    SBB_MEAS_L11_DEFAULT, \
                                    SBB_MEAS_L11_RD_MASK, "SBB_MEAS_L11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H12_OFFSET, \
                                    SBB_MEAS_H12_DEFAULT, \
                                    SBB_MEAS_H12_RD_MASK, "SBB_MEAS_H12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L12_OFFSET, \
                                    SBB_MEAS_L12_DEFAULT, \
                                    SBB_MEAS_L12_RD_MASK, "SBB_MEAS_L12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H13_OFFSET, \
                                    SBB_MEAS_H13_DEFAULT, \
                                    SBB_MEAS_H13_RD_MASK, "SBB_MEAS_H13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L13_OFFSET, \
                                    SBB_MEAS_L13_DEFAULT, \
                                    SBB_MEAS_L13_RD_MASK, "SBB_MEAS_L13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H14_OFFSET, \
                                    SBB_MEAS_H14_DEFAULT, \
                                    SBB_MEAS_H14_RD_MASK, "SBB_MEAS_H14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L14_OFFSET, \
                                    SBB_MEAS_L14_DEFAULT, \
                                    SBB_MEAS_L14_RD_MASK, "SBB_MEAS_L14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H15_OFFSET, \
                                    SBB_MEAS_H15_DEFAULT, \
                                    SBB_MEAS_H15_RD_MASK, "SBB_MEAS_H15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L15_OFFSET, \
                                    SBB_MEAS_L15_DEFAULT, \
                                    SBB_MEAS_L15_RD_MASK, "SBB_MEAS_L15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H16_OFFSET, \
                                    SBB_MEAS_H16_DEFAULT, \
                                    SBB_MEAS_H16_RD_MASK, "SBB_MEAS_H16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L16_OFFSET, \
                                    SBB_MEAS_L16_DEFAULT, \
                                    SBB_MEAS_L16_RD_MASK, "SBB_MEAS_L16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H17_OFFSET, \
                                    SBB_MEAS_H17_DEFAULT, \
                                    SBB_MEAS_H17_RD_MASK, "SBB_MEAS_H17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L17_OFFSET, \
                                    SBB_MEAS_L17_DEFAULT, \
                                    SBB_MEAS_L17_RD_MASK, "SBB_MEAS_L17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H18_OFFSET, \
                                    SBB_MEAS_H18_DEFAULT, \
                                    SBB_MEAS_H18_RD_MASK, "SBB_MEAS_H18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L18_OFFSET, \
                                    SBB_MEAS_L18_DEFAULT, \
                                    SBB_MEAS_L18_RD_MASK, "SBB_MEAS_L18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H19_OFFSET, \
                                    SBB_MEAS_H19_DEFAULT, \
                                    SBB_MEAS_H19_RD_MASK, "SBB_MEAS_H19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L19_OFFSET, \
                                    SBB_MEAS_L19_DEFAULT, \
                                    SBB_MEAS_L19_RD_MASK, "SBB_MEAS_L19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H20_OFFSET, \
                                    SBB_MEAS_H20_DEFAULT, \
                                    SBB_MEAS_H20_RD_MASK, "SBB_MEAS_H20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L20_OFFSET, \
                                    SBB_MEAS_L20_DEFAULT, \
                                    SBB_MEAS_L20_RD_MASK, "SBB_MEAS_L20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H21_OFFSET, \
                                    SBB_MEAS_H21_DEFAULT, \
                                    SBB_MEAS_H21_RD_MASK, "SBB_MEAS_H21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L21_OFFSET, \
                                    SBB_MEAS_L21_DEFAULT, \
                                    SBB_MEAS_L21_RD_MASK, "SBB_MEAS_L21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H22_OFFSET, \
                                    SBB_MEAS_H22_DEFAULT, \
                                    SBB_MEAS_H22_RD_MASK, "SBB_MEAS_H22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L22_OFFSET, \
                                    SBB_MEAS_L22_DEFAULT, \
                                    SBB_MEAS_L22_RD_MASK, "SBB_MEAS_L22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H23_OFFSET, \
                                    SBB_MEAS_H23_DEFAULT, \
                                    SBB_MEAS_H23_RD_MASK, "SBB_MEAS_H23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L23_OFFSET, \
                                    SBB_MEAS_L23_DEFAULT, \
                                    SBB_MEAS_L23_RD_MASK, "SBB_MEAS_L23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H24_OFFSET, \
                                    SBB_MEAS_H24_DEFAULT, \
                                    SBB_MEAS_H24_RD_MASK, "SBB_MEAS_H24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L24_OFFSET, \
                                    SBB_MEAS_L24_DEFAULT, \
                                    SBB_MEAS_L24_RD_MASK, "SBB_MEAS_L24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H25_OFFSET, \
                                    SBB_MEAS_H25_DEFAULT, \
                                    SBB_MEAS_H25_RD_MASK, "SBB_MEAS_H25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L25_OFFSET, \
                                    SBB_MEAS_L25_DEFAULT, \
                                    SBB_MEAS_L25_RD_MASK, "SBB_MEAS_L25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H26_OFFSET, \
                                    SBB_MEAS_H26_DEFAULT, \
                                    SBB_MEAS_H26_RD_MASK, "SBB_MEAS_H26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L26_OFFSET, \
                                    SBB_MEAS_L26_DEFAULT, \
                                    SBB_MEAS_L26_RD_MASK, "SBB_MEAS_L26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H27_OFFSET, \
                                    SBB_MEAS_H27_DEFAULT, \
                                    SBB_MEAS_H27_RD_MASK, "SBB_MEAS_H27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L27_OFFSET, \
                                    SBB_MEAS_L27_DEFAULT, \
                                    SBB_MEAS_L27_RD_MASK, "SBB_MEAS_L27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H28_OFFSET, \
                                    SBB_MEAS_H28_DEFAULT, \
                                    SBB_MEAS_H28_RD_MASK, "SBB_MEAS_H28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L28_OFFSET, \
                                    SBB_MEAS_L28_DEFAULT, \
                                    SBB_MEAS_L28_RD_MASK, "SBB_MEAS_L28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H29_OFFSET, \
                                    SBB_MEAS_H29_DEFAULT, \
                                    SBB_MEAS_H29_RD_MASK, "SBB_MEAS_H29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L29_OFFSET, \
                                    SBB_MEAS_L29_DEFAULT, \
                                    SBB_MEAS_L29_RD_MASK, "SBB_MEAS_L29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H30_OFFSET, \
                                    SBB_MEAS_H30_DEFAULT, \
                                    SBB_MEAS_H30_RD_MASK, "SBB_MEAS_H30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L30_OFFSET, \
                                    SBB_MEAS_L30_DEFAULT, \
                                    SBB_MEAS_L30_RD_MASK, "SBB_MEAS_L30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H31_OFFSET, \
                                    SBB_MEAS_H31_DEFAULT, \
                                    SBB_MEAS_H31_RD_MASK, "SBB_MEAS_H31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L31_OFFSET, \
                                    SBB_MEAS_L31_DEFAULT, \
                                    SBB_MEAS_L31_RD_MASK, "SBB_MEAS_L31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H32_OFFSET, \
                                    SBB_MEAS_H32_DEFAULT, \
                                    SBB_MEAS_H32_RD_MASK, "SBB_MEAS_H32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L32_OFFSET, \
                                    SBB_MEAS_L32_DEFAULT, \
                                    SBB_MEAS_L32_RD_MASK, "SBB_MEAS_L32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H33_OFFSET, \
                                    SBB_MEAS_H33_DEFAULT, \
                                    SBB_MEAS_H33_RD_MASK, "SBB_MEAS_H33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L33_OFFSET, \
                                    SBB_MEAS_L33_DEFAULT, \
                                    SBB_MEAS_L33_RD_MASK, "SBB_MEAS_L33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H34_OFFSET, \
                                    SBB_MEAS_H34_DEFAULT, \
                                    SBB_MEAS_H34_RD_MASK, "SBB_MEAS_H34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L34_OFFSET, \
                                    SBB_MEAS_L34_DEFAULT, \
                                    SBB_MEAS_L34_RD_MASK, "SBB_MEAS_L34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H35_OFFSET, \
                                    SBB_MEAS_H35_DEFAULT, \
                                    SBB_MEAS_H35_RD_MASK, "SBB_MEAS_H35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L35_OFFSET, \
                                    SBB_MEAS_L35_DEFAULT, \
                                    SBB_MEAS_L35_RD_MASK, "SBB_MEAS_L35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H36_OFFSET, \
                                    SBB_MEAS_H36_DEFAULT, \
                                    SBB_MEAS_H36_RD_MASK, "SBB_MEAS_H36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L36_OFFSET, \
                                    SBB_MEAS_L36_DEFAULT, \
                                    SBB_MEAS_L36_RD_MASK, "SBB_MEAS_L36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H37_OFFSET, \
                                    SBB_MEAS_H37_DEFAULT, \
                                    SBB_MEAS_H37_RD_MASK, "SBB_MEAS_H37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L37_OFFSET, \
                                    SBB_MEAS_L37_DEFAULT, \
                                    SBB_MEAS_L37_RD_MASK, "SBB_MEAS_L37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H38_OFFSET, \
                                    SBB_MEAS_H38_DEFAULT, \
                                    SBB_MEAS_H38_RD_MASK, "SBB_MEAS_H38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L38_OFFSET, \
                                    SBB_MEAS_L38_DEFAULT, \
                                    SBB_MEAS_L38_RD_MASK, "SBB_MEAS_L38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H39_OFFSET, \
                                    SBB_MEAS_H39_DEFAULT, \
                                    SBB_MEAS_H39_RD_MASK, "SBB_MEAS_H39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L39_OFFSET, \
                                    SBB_MEAS_L39_DEFAULT, \
                                    SBB_MEAS_L39_RD_MASK, "SBB_MEAS_L39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H40_OFFSET, \
                                    SBB_MEAS_H40_DEFAULT, \
                                    SBB_MEAS_H40_RD_MASK, "SBB_MEAS_H40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L40_OFFSET, \
                                    SBB_MEAS_L40_DEFAULT, \
                                    SBB_MEAS_L40_RD_MASK, "SBB_MEAS_L40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H41_OFFSET, \
                                    SBB_MEAS_H41_DEFAULT, \
                                    SBB_MEAS_H41_RD_MASK, "SBB_MEAS_H41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L41_OFFSET, \
                                    SBB_MEAS_L41_DEFAULT, \
                                    SBB_MEAS_L41_RD_MASK, "SBB_MEAS_L41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H42_OFFSET, \
                                    SBB_MEAS_H42_DEFAULT, \
                                    SBB_MEAS_H42_RD_MASK, "SBB_MEAS_H42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L42_OFFSET, \
                                    SBB_MEAS_L42_DEFAULT, \
                                    SBB_MEAS_L42_RD_MASK, "SBB_MEAS_L42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H43_OFFSET, \
                                    SBB_MEAS_H43_DEFAULT, \
                                    SBB_MEAS_H43_RD_MASK, "SBB_MEAS_H43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L43_OFFSET, \
                                    SBB_MEAS_L43_DEFAULT, \
                                    SBB_MEAS_L43_RD_MASK, "SBB_MEAS_L43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H44_OFFSET, \
                                    SBB_MEAS_H44_DEFAULT, \
                                    SBB_MEAS_H44_RD_MASK, "SBB_MEAS_H44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L44_OFFSET, \
                                    SBB_MEAS_L44_DEFAULT, \
                                    SBB_MEAS_L44_RD_MASK, "SBB_MEAS_L44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H45_OFFSET, \
                                    SBB_MEAS_H45_DEFAULT, \
                                    SBB_MEAS_H45_RD_MASK, "SBB_MEAS_H45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L45_OFFSET, \
                                    SBB_MEAS_L45_DEFAULT, \
                                    SBB_MEAS_L45_RD_MASK, "SBB_MEAS_L45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H46_OFFSET, \
                                    SBB_MEAS_H46_DEFAULT, \
                                    SBB_MEAS_H46_RD_MASK, "SBB_MEAS_H46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L46_OFFSET, \
                                    SBB_MEAS_L46_DEFAULT, \
                                    SBB_MEAS_L46_RD_MASK, "SBB_MEAS_L46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H47_OFFSET, \
                                    SBB_MEAS_H47_DEFAULT, \
                                    SBB_MEAS_H47_RD_MASK, "SBB_MEAS_H47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L47_OFFSET, \
                                    SBB_MEAS_L47_DEFAULT, \
                                    SBB_MEAS_L47_RD_MASK, "SBB_MEAS_L47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H48_OFFSET, \
                                    SBB_MEAS_H48_DEFAULT, \
                                    SBB_MEAS_H48_RD_MASK, "SBB_MEAS_H48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L48_OFFSET, \
                                    SBB_MEAS_L48_DEFAULT, \
                                    SBB_MEAS_L48_RD_MASK, "SBB_MEAS_L48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H49_OFFSET, \
                                    SBB_MEAS_H49_DEFAULT, \
                                    SBB_MEAS_H49_RD_MASK, "SBB_MEAS_H49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L49_OFFSET, \
                                    SBB_MEAS_L49_DEFAULT, \
                                    SBB_MEAS_L49_RD_MASK, "SBB_MEAS_L49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H50_OFFSET, \
                                    SBB_MEAS_H50_DEFAULT, \
                                    SBB_MEAS_H50_RD_MASK, "SBB_MEAS_H50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L50_OFFSET, \
                                    SBB_MEAS_L50_DEFAULT, \
                                    SBB_MEAS_L50_RD_MASK, "SBB_MEAS_L50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H51_OFFSET, \
                                    SBB_MEAS_H51_DEFAULT, \
                                    SBB_MEAS_H51_RD_MASK, "SBB_MEAS_H51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L51_OFFSET, \
                                    SBB_MEAS_L51_DEFAULT, \
                                    SBB_MEAS_L51_RD_MASK, "SBB_MEAS_L51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H52_OFFSET, \
                                    SBB_MEAS_H52_DEFAULT, \
                                    SBB_MEAS_H52_RD_MASK, "SBB_MEAS_H52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L52_OFFSET, \
                                    SBB_MEAS_L52_DEFAULT, \
                                    SBB_MEAS_L52_RD_MASK, "SBB_MEAS_L52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H53_OFFSET, \
                                    SBB_MEAS_H53_DEFAULT, \
                                    SBB_MEAS_H53_RD_MASK, "SBB_MEAS_H53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L53_OFFSET, \
                                    SBB_MEAS_L53_DEFAULT, \
                                    SBB_MEAS_L53_RD_MASK, "SBB_MEAS_L53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H54_OFFSET, \
                                    SBB_MEAS_H54_DEFAULT, \
                                    SBB_MEAS_H54_RD_MASK, "SBB_MEAS_H54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L54_OFFSET, \
                                    SBB_MEAS_L54_DEFAULT, \
                                    SBB_MEAS_L54_RD_MASK, "SBB_MEAS_L54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H55_OFFSET, \
                                    SBB_MEAS_H55_DEFAULT, \
                                    SBB_MEAS_H55_RD_MASK, "SBB_MEAS_H55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L55_OFFSET, \
                                    SBB_MEAS_L55_DEFAULT, \
                                    SBB_MEAS_L55_RD_MASK, "SBB_MEAS_L55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H56_OFFSET, \
                                    SBB_MEAS_H56_DEFAULT, \
                                    SBB_MEAS_H56_RD_MASK, "SBB_MEAS_H56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L56_OFFSET, \
                                    SBB_MEAS_L56_DEFAULT, \
                                    SBB_MEAS_L56_RD_MASK, "SBB_MEAS_L56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H57_OFFSET, \
                                    SBB_MEAS_H57_DEFAULT, \
                                    SBB_MEAS_H57_RD_MASK, "SBB_MEAS_H57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L57_OFFSET, \
                                    SBB_MEAS_L57_DEFAULT, \
                                    SBB_MEAS_L57_RD_MASK, "SBB_MEAS_L57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H58_OFFSET, \
                                    SBB_MEAS_H58_DEFAULT, \
                                    SBB_MEAS_H58_RD_MASK, "SBB_MEAS_H58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L58_OFFSET, \
                                    SBB_MEAS_L58_DEFAULT, \
                                    SBB_MEAS_L58_RD_MASK, "SBB_MEAS_L58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H59_OFFSET, \
                                    SBB_MEAS_H59_DEFAULT, \
                                    SBB_MEAS_H59_RD_MASK, "SBB_MEAS_H59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L59_OFFSET, \
                                    SBB_MEAS_L59_DEFAULT, \
                                    SBB_MEAS_L59_RD_MASK, "SBB_MEAS_L59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H60_OFFSET, \
                                    SBB_MEAS_H60_DEFAULT, \
                                    SBB_MEAS_H60_RD_MASK, "SBB_MEAS_H60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L60_OFFSET, \
                                    SBB_MEAS_L60_DEFAULT, \
                                    SBB_MEAS_L60_RD_MASK, "SBB_MEAS_L60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H61_OFFSET, \
                                    SBB_MEAS_H61_DEFAULT, \
                                    SBB_MEAS_H61_RD_MASK, "SBB_MEAS_H61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L61_OFFSET, \
                                    SBB_MEAS_L61_DEFAULT, \
                                    SBB_MEAS_L61_RD_MASK, "SBB_MEAS_L61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H62_OFFSET, \
                                    SBB_MEAS_H62_DEFAULT, \
                                    SBB_MEAS_H62_RD_MASK, "SBB_MEAS_H62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L62_OFFSET, \
                                    SBB_MEAS_L62_DEFAULT, \
                                    SBB_MEAS_L62_RD_MASK, "SBB_MEAS_L62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H63_OFFSET, \
                                    SBB_MEAS_H63_DEFAULT, \
                                    SBB_MEAS_H63_RD_MASK, "SBB_MEAS_H63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L63_OFFSET, \
                                    SBB_MEAS_L63_DEFAULT, \
                                    SBB_MEAS_L63_RD_MASK, "SBB_MEAS_L63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H64_OFFSET, \
                                    SBB_MEAS_H64_DEFAULT, \
                                    SBB_MEAS_H64_RD_MASK, "SBB_MEAS_H64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L64_OFFSET, \
                                    SBB_MEAS_L64_DEFAULT, \
                                    SBB_MEAS_L64_RD_MASK, "SBB_MEAS_L64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H65_OFFSET, \
                                    SBB_MEAS_H65_DEFAULT, \
                                    SBB_MEAS_H65_RD_MASK, "SBB_MEAS_H65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L65_OFFSET, \
                                    SBB_MEAS_L65_DEFAULT, \
                                    SBB_MEAS_L65_RD_MASK, "SBB_MEAS_L65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H66_OFFSET, \
                                    SBB_MEAS_H66_DEFAULT, \
                                    SBB_MEAS_H66_RD_MASK, "SBB_MEAS_H66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L66_OFFSET, \
                                    SBB_MEAS_L66_DEFAULT, \
                                    SBB_MEAS_L66_RD_MASK, "SBB_MEAS_L66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H67_OFFSET, \
                                    SBB_MEAS_H67_DEFAULT, \
                                    SBB_MEAS_H67_RD_MASK, "SBB_MEAS_H67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L67_OFFSET, \
                                    SBB_MEAS_L67_DEFAULT, \
                                    SBB_MEAS_L67_RD_MASK, "SBB_MEAS_L67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H68_OFFSET, \
                                    SBB_MEAS_H68_DEFAULT, \
                                    SBB_MEAS_H68_RD_MASK, "SBB_MEAS_H68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L68_OFFSET, \
                                    SBB_MEAS_L68_DEFAULT, \
                                    SBB_MEAS_L68_RD_MASK, "SBB_MEAS_L68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H69_OFFSET, \
                                    SBB_MEAS_H69_DEFAULT, \
                                    SBB_MEAS_H69_RD_MASK, "SBB_MEAS_H69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L69_OFFSET, \
                                    SBB_MEAS_L69_DEFAULT, \
                                    SBB_MEAS_L69_RD_MASK, "SBB_MEAS_L69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H70_OFFSET, \
                                    SBB_MEAS_H70_DEFAULT, \
                                    SBB_MEAS_H70_RD_MASK, "SBB_MEAS_H70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L70_OFFSET, \
                                    SBB_MEAS_L70_DEFAULT, \
                                    SBB_MEAS_L70_RD_MASK, "SBB_MEAS_L70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H71_OFFSET, \
                                    SBB_MEAS_H71_DEFAULT, \
                                    SBB_MEAS_H71_RD_MASK, "SBB_MEAS_H71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L71_OFFSET, \
                                    SBB_MEAS_L71_DEFAULT, \
                                    SBB_MEAS_L71_RD_MASK, "SBB_MEAS_L71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H72_OFFSET, \
                                    SBB_MEAS_H72_DEFAULT, \
                                    SBB_MEAS_H72_RD_MASK, "SBB_MEAS_H72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L72_OFFSET, \
                                    SBB_MEAS_L72_DEFAULT, \
                                    SBB_MEAS_L72_RD_MASK, "SBB_MEAS_L72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H73_OFFSET, \
                                    SBB_MEAS_H73_DEFAULT, \
                                    SBB_MEAS_H73_RD_MASK, "SBB_MEAS_H73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L73_OFFSET, \
                                    SBB_MEAS_L73_DEFAULT, \
                                    SBB_MEAS_L73_RD_MASK, "SBB_MEAS_L73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H74_OFFSET, \
                                    SBB_MEAS_H74_DEFAULT, \
                                    SBB_MEAS_H74_RD_MASK, "SBB_MEAS_H74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L74_OFFSET, \
                                    SBB_MEAS_L74_DEFAULT, \
                                    SBB_MEAS_L74_RD_MASK, "SBB_MEAS_L74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H75_OFFSET, \
                                    SBB_MEAS_H75_DEFAULT, \
                                    SBB_MEAS_H75_RD_MASK, "SBB_MEAS_H75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L75_OFFSET, \
                                    SBB_MEAS_L75_DEFAULT, \
                                    SBB_MEAS_L75_RD_MASK, "SBB_MEAS_L75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H76_OFFSET, \
                                    SBB_MEAS_H76_DEFAULT, \
                                    SBB_MEAS_H76_RD_MASK, "SBB_MEAS_H76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L76_OFFSET, \
                                    SBB_MEAS_L76_DEFAULT, \
                                    SBB_MEAS_L76_RD_MASK, "SBB_MEAS_L76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H77_OFFSET, \
                                    SBB_MEAS_H77_DEFAULT, \
                                    SBB_MEAS_H77_RD_MASK, "SBB_MEAS_H77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L77_OFFSET, \
                                    SBB_MEAS_L77_DEFAULT, \
                                    SBB_MEAS_L77_RD_MASK, "SBB_MEAS_L77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H78_OFFSET, \
                                    SBB_MEAS_H78_DEFAULT, \
                                    SBB_MEAS_H78_RD_MASK, "SBB_MEAS_H78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L78_OFFSET, \
                                    SBB_MEAS_L78_DEFAULT, \
                                    SBB_MEAS_L78_RD_MASK, "SBB_MEAS_L78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H79_OFFSET, \
                                    SBB_MEAS_H79_DEFAULT, \
                                    SBB_MEAS_H79_RD_MASK, "SBB_MEAS_H79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L79_OFFSET, \
                                    SBB_MEAS_L79_DEFAULT, \
                                    SBB_MEAS_L79_RD_MASK, "SBB_MEAS_L79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H80_OFFSET, \
                                    SBB_MEAS_H80_DEFAULT, \
                                    SBB_MEAS_H80_RD_MASK, "SBB_MEAS_H80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L80_OFFSET, \
                                    SBB_MEAS_L80_DEFAULT, \
                                    SBB_MEAS_L80_RD_MASK, "SBB_MEAS_L80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H81_OFFSET, \
                                    SBB_MEAS_H81_DEFAULT, \
                                    SBB_MEAS_H81_RD_MASK, "SBB_MEAS_H81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L81_OFFSET, \
                                    SBB_MEAS_L81_DEFAULT, \
                                    SBB_MEAS_L81_RD_MASK, "SBB_MEAS_L81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H82_OFFSET, \
                                    SBB_MEAS_H82_DEFAULT, \
                                    SBB_MEAS_H82_RD_MASK, "SBB_MEAS_H82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L82_OFFSET, \
                                    SBB_MEAS_L82_DEFAULT, \
                                    SBB_MEAS_L82_RD_MASK, "SBB_MEAS_L82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H83_OFFSET, \
                                    SBB_MEAS_H83_DEFAULT, \
                                    SBB_MEAS_H83_RD_MASK, "SBB_MEAS_H83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L83_OFFSET, \
                                    SBB_MEAS_L83_DEFAULT, \
                                    SBB_MEAS_L83_RD_MASK, "SBB_MEAS_L83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H84_OFFSET, \
                                    SBB_MEAS_H84_DEFAULT, \
                                    SBB_MEAS_H84_RD_MASK, "SBB_MEAS_H84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L84_OFFSET, \
                                    SBB_MEAS_L84_DEFAULT, \
                                    SBB_MEAS_L84_RD_MASK, "SBB_MEAS_L84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H85_OFFSET, \
                                    SBB_MEAS_H85_DEFAULT, \
                                    SBB_MEAS_H85_RD_MASK, "SBB_MEAS_H85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L85_OFFSET, \
                                    SBB_MEAS_L85_DEFAULT, \
                                    SBB_MEAS_L85_RD_MASK, "SBB_MEAS_L85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H86_OFFSET, \
                                    SBB_MEAS_H86_DEFAULT, \
                                    SBB_MEAS_H86_RD_MASK, "SBB_MEAS_H86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L86_OFFSET, \
                                    SBB_MEAS_L86_DEFAULT, \
                                    SBB_MEAS_L86_RD_MASK, "SBB_MEAS_L86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H87_OFFSET, \
                                    SBB_MEAS_H87_DEFAULT, \
                                    SBB_MEAS_H87_RD_MASK, "SBB_MEAS_H87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L87_OFFSET, \
                                    SBB_MEAS_L87_DEFAULT, \
                                    SBB_MEAS_L87_RD_MASK, "SBB_MEAS_L87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H88_OFFSET, \
                                    SBB_MEAS_H88_DEFAULT, \
                                    SBB_MEAS_H88_RD_MASK, "SBB_MEAS_H88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L88_OFFSET, \
                                    SBB_MEAS_L88_DEFAULT, \
                                    SBB_MEAS_L88_RD_MASK, "SBB_MEAS_L88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H89_OFFSET, \
                                    SBB_MEAS_H89_DEFAULT, \
                                    SBB_MEAS_H89_RD_MASK, "SBB_MEAS_H89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L89_OFFSET, \
                                    SBB_MEAS_L89_DEFAULT, \
                                    SBB_MEAS_L89_RD_MASK, "SBB_MEAS_L89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H90_OFFSET, \
                                    SBB_MEAS_H90_DEFAULT, \
                                    SBB_MEAS_H90_RD_MASK, "SBB_MEAS_H90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L90_OFFSET, \
                                    SBB_MEAS_L90_DEFAULT, \
                                    SBB_MEAS_L90_RD_MASK, "SBB_MEAS_L90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H91_OFFSET, \
                                    SBB_MEAS_H91_DEFAULT, \
                                    SBB_MEAS_H91_RD_MASK, "SBB_MEAS_H91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L91_OFFSET, \
                                    SBB_MEAS_L91_DEFAULT, \
                                    SBB_MEAS_L91_RD_MASK, "SBB_MEAS_L91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H92_OFFSET, \
                                    SBB_MEAS_H92_DEFAULT, \
                                    SBB_MEAS_H92_RD_MASK, "SBB_MEAS_H92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L92_OFFSET, \
                                    SBB_MEAS_L92_DEFAULT, \
                                    SBB_MEAS_L92_RD_MASK, "SBB_MEAS_L92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H93_OFFSET, \
                                    SBB_MEAS_H93_DEFAULT, \
                                    SBB_MEAS_H93_RD_MASK, "SBB_MEAS_H93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L93_OFFSET, \
                                    SBB_MEAS_L93_DEFAULT, \
                                    SBB_MEAS_L93_RD_MASK, "SBB_MEAS_L93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H94_OFFSET, \
                                    SBB_MEAS_H94_DEFAULT, \
                                    SBB_MEAS_H94_RD_MASK, "SBB_MEAS_H94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L94_OFFSET, \
                                    SBB_MEAS_L94_DEFAULT, \
                                    SBB_MEAS_L94_RD_MASK, "SBB_MEAS_L94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H95_OFFSET, \
                                    SBB_MEAS_H95_DEFAULT, \
                                    SBB_MEAS_H95_RD_MASK, "SBB_MEAS_H95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L95_OFFSET, \
                                    SBB_MEAS_L95_DEFAULT, \
                                    SBB_MEAS_L95_RD_MASK, "SBB_MEAS_L95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H96_OFFSET, \
                                    SBB_MEAS_H96_DEFAULT, \
                                    SBB_MEAS_H96_RD_MASK, "SBB_MEAS_H96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L96_OFFSET, \
                                    SBB_MEAS_L96_DEFAULT, \
                                    SBB_MEAS_L96_RD_MASK, "SBB_MEAS_L96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H97_OFFSET, \
                                    SBB_MEAS_H97_DEFAULT, \
                                    SBB_MEAS_H97_RD_MASK, "SBB_MEAS_H97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L97_OFFSET, \
                                    SBB_MEAS_L97_DEFAULT, \
                                    SBB_MEAS_L97_RD_MASK, "SBB_MEAS_L97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H98_OFFSET, \
                                    SBB_MEAS_H98_DEFAULT, \
                                    SBB_MEAS_H98_RD_MASK, "SBB_MEAS_H98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L98_OFFSET, \
                                    SBB_MEAS_L98_DEFAULT, \
                                    SBB_MEAS_L98_RD_MASK, "SBB_MEAS_L98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H99_OFFSET, \
                                    SBB_MEAS_H99_DEFAULT, \
                                    SBB_MEAS_H99_RD_MASK, "SBB_MEAS_H99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L99_OFFSET, \
                                    SBB_MEAS_L99_DEFAULT, \
                                    SBB_MEAS_L99_RD_MASK, "SBB_MEAS_L99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H100_OFFSET, \
                                    SBB_MEAS_H100_DEFAULT, \
                                    SBB_MEAS_H100_RD_MASK, "SBB_MEAS_H100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L100_OFFSET, \
                                    SBB_MEAS_L100_DEFAULT, \
                                    SBB_MEAS_L100_RD_MASK, "SBB_MEAS_L100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H101_OFFSET, \
                                    SBB_MEAS_H101_DEFAULT, \
                                    SBB_MEAS_H101_RD_MASK, "SBB_MEAS_H101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L101_OFFSET, \
                                    SBB_MEAS_L101_DEFAULT, \
                                    SBB_MEAS_L101_RD_MASK, "SBB_MEAS_L101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H102_OFFSET, \
                                    SBB_MEAS_H102_DEFAULT, \
                                    SBB_MEAS_H102_RD_MASK, "SBB_MEAS_H102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L102_OFFSET, \
                                    SBB_MEAS_L102_DEFAULT, \
                                    SBB_MEAS_L102_RD_MASK, "SBB_MEAS_L102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H103_OFFSET, \
                                    SBB_MEAS_H103_DEFAULT, \
                                    SBB_MEAS_H103_RD_MASK, "SBB_MEAS_H103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L103_OFFSET, \
                                    SBB_MEAS_L103_DEFAULT, \
                                    SBB_MEAS_L103_RD_MASK, "SBB_MEAS_L103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H104_OFFSET, \
                                    SBB_MEAS_H104_DEFAULT, \
                                    SBB_MEAS_H104_RD_MASK, "SBB_MEAS_H104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L104_OFFSET, \
                                    SBB_MEAS_L104_DEFAULT, \
                                    SBB_MEAS_L104_RD_MASK, "SBB_MEAS_L104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H105_OFFSET, \
                                    SBB_MEAS_H105_DEFAULT, \
                                    SBB_MEAS_H105_RD_MASK, "SBB_MEAS_H105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L105_OFFSET, \
                                    SBB_MEAS_L105_DEFAULT, \
                                    SBB_MEAS_L105_RD_MASK, "SBB_MEAS_L105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H106_OFFSET, \
                                    SBB_MEAS_H106_DEFAULT, \
                                    SBB_MEAS_H106_RD_MASK, "SBB_MEAS_H106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L106_OFFSET, \
                                    SBB_MEAS_L106_DEFAULT, \
                                    SBB_MEAS_L106_RD_MASK, "SBB_MEAS_L106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H107_OFFSET, \
                                    SBB_MEAS_H107_DEFAULT, \
                                    SBB_MEAS_H107_RD_MASK, "SBB_MEAS_H107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L107_OFFSET, \
                                    SBB_MEAS_L107_DEFAULT, \
                                    SBB_MEAS_L107_RD_MASK, "SBB_MEAS_L107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H108_OFFSET, \
                                    SBB_MEAS_H108_DEFAULT, \
                                    SBB_MEAS_H108_RD_MASK, "SBB_MEAS_H108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L108_OFFSET, \
                                    SBB_MEAS_L108_DEFAULT, \
                                    SBB_MEAS_L108_RD_MASK, "SBB_MEAS_L108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H109_OFFSET, \
                                    SBB_MEAS_H109_DEFAULT, \
                                    SBB_MEAS_H109_RD_MASK, "SBB_MEAS_H109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L109_OFFSET, \
                                    SBB_MEAS_L109_DEFAULT, \
                                    SBB_MEAS_L109_RD_MASK, "SBB_MEAS_L109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H110_OFFSET, \
                                    SBB_MEAS_H110_DEFAULT, \
                                    SBB_MEAS_H110_RD_MASK, "SBB_MEAS_H110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L110_OFFSET, \
                                    SBB_MEAS_L110_DEFAULT, \
                                    SBB_MEAS_L110_RD_MASK, "SBB_MEAS_L110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H111_OFFSET, \
                                    SBB_MEAS_H111_DEFAULT, \
                                    SBB_MEAS_H111_RD_MASK, "SBB_MEAS_H111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L111_OFFSET, \
                                    SBB_MEAS_L111_DEFAULT, \
                                    SBB_MEAS_L111_RD_MASK, "SBB_MEAS_L111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H112_OFFSET, \
                                    SBB_MEAS_H112_DEFAULT, \
                                    SBB_MEAS_H112_RD_MASK, "SBB_MEAS_H112_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L112_OFFSET, \
                                    SBB_MEAS_L112_DEFAULT, \
                                    SBB_MEAS_L112_RD_MASK, "SBB_MEAS_L112_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H113_OFFSET, \
                                    SBB_MEAS_H113_DEFAULT, \
                                    SBB_MEAS_H113_RD_MASK, "SBB_MEAS_H113_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L113_OFFSET, \
                                    SBB_MEAS_L113_DEFAULT, \
                                    SBB_MEAS_L113_RD_MASK, "SBB_MEAS_L113_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H114_OFFSET, \
                                    SBB_MEAS_H114_DEFAULT, \
                                    SBB_MEAS_H114_RD_MASK, "SBB_MEAS_H114_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L114_OFFSET, \
                                    SBB_MEAS_L114_DEFAULT, \
                                    SBB_MEAS_L114_RD_MASK, "SBB_MEAS_L114_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H115_OFFSET, \
                                    SBB_MEAS_H115_DEFAULT, \
                                    SBB_MEAS_H115_RD_MASK, "SBB_MEAS_H115_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L115_OFFSET, \
                                    SBB_MEAS_L115_DEFAULT, \
                                    SBB_MEAS_L115_RD_MASK, "SBB_MEAS_L115_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H116_OFFSET, \
                                    SBB_MEAS_H116_DEFAULT, \
                                    SBB_MEAS_H116_RD_MASK, "SBB_MEAS_H116_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L116_OFFSET, \
                                    SBB_MEAS_L116_DEFAULT, \
                                    SBB_MEAS_L116_RD_MASK, "SBB_MEAS_L116_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H117_OFFSET, \
                                    SBB_MEAS_H117_DEFAULT, \
                                    SBB_MEAS_H117_RD_MASK, "SBB_MEAS_H117_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L117_OFFSET, \
                                    SBB_MEAS_L117_DEFAULT, \
                                    SBB_MEAS_L117_RD_MASK, "SBB_MEAS_L117_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H118_OFFSET, \
                                    SBB_MEAS_H118_DEFAULT, \
                                    SBB_MEAS_H118_RD_MASK, "SBB_MEAS_H118_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L118_OFFSET, \
                                    SBB_MEAS_L118_DEFAULT, \
                                    SBB_MEAS_L118_RD_MASK, "SBB_MEAS_L118_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H119_OFFSET, \
                                    SBB_MEAS_H119_DEFAULT, \
                                    SBB_MEAS_H119_RD_MASK, "SBB_MEAS_H119_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L119_OFFSET, \
                                    SBB_MEAS_L119_DEFAULT, \
                                    SBB_MEAS_L119_RD_MASK, "SBB_MEAS_L119_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H120_OFFSET, \
                                    SBB_MEAS_H120_DEFAULT, \
                                    SBB_MEAS_H120_RD_MASK, "SBB_MEAS_H120_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L120_OFFSET, \
                                    SBB_MEAS_L120_DEFAULT, \
                                    SBB_MEAS_L120_RD_MASK, "SBB_MEAS_L120_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H121_OFFSET, \
                                    SBB_MEAS_H121_DEFAULT, \
                                    SBB_MEAS_H121_RD_MASK, "SBB_MEAS_H121_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L121_OFFSET, \
                                    SBB_MEAS_L121_DEFAULT, \
                                    SBB_MEAS_L121_RD_MASK, "SBB_MEAS_L121_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H122_OFFSET, \
                                    SBB_MEAS_H122_DEFAULT, \
                                    SBB_MEAS_H122_RD_MASK, "SBB_MEAS_H122_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L122_OFFSET, \
                                    SBB_MEAS_L122_DEFAULT, \
                                    SBB_MEAS_L122_RD_MASK, "SBB_MEAS_L122_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H123_OFFSET, \
                                    SBB_MEAS_H123_DEFAULT, \
                                    SBB_MEAS_H123_RD_MASK, "SBB_MEAS_H123_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L123_OFFSET, \
                                    SBB_MEAS_L123_DEFAULT, \
                                    SBB_MEAS_L123_RD_MASK, "SBB_MEAS_L123_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H124_OFFSET, \
                                    SBB_MEAS_H124_DEFAULT, \
                                    SBB_MEAS_H124_RD_MASK, "SBB_MEAS_H124_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L124_OFFSET, \
                                    SBB_MEAS_L124_DEFAULT, \
                                    SBB_MEAS_L124_RD_MASK, "SBB_MEAS_L124_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H125_OFFSET, \
                                    SBB_MEAS_H125_DEFAULT, \
                                    SBB_MEAS_H125_RD_MASK, "SBB_MEAS_H125_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L125_OFFSET, \
                                    SBB_MEAS_L125_DEFAULT, \
                                    SBB_MEAS_L125_RD_MASK, "SBB_MEAS_L125_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H126_OFFSET, \
                                    SBB_MEAS_H126_DEFAULT, \
                                    SBB_MEAS_H126_RD_MASK, "SBB_MEAS_H126_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L126_OFFSET, \
                                    SBB_MEAS_L126_DEFAULT, \
                                    SBB_MEAS_L126_RD_MASK, "SBB_MEAS_L126_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H127_OFFSET, \
                                    SBB_MEAS_H127_DEFAULT, \
                                    SBB_MEAS_H127_RD_MASK, "SBB_MEAS_H127_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L127_OFFSET, \
                                    SBB_MEAS_L127_DEFAULT, \
                                    SBB_MEAS_L127_RD_MASK, "SBB_MEAS_L127_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H128_OFFSET, \
                                    SBB_MEAS_H128_DEFAULT, \
                                    SBB_MEAS_H128_RD_MASK, "SBB_MEAS_H128_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L128_OFFSET, \
                                    SBB_MEAS_L128_DEFAULT, \
                                    SBB_MEAS_L128_RD_MASK, "SBB_MEAS_L128_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H129_OFFSET, \
                                    SBB_MEAS_H129_DEFAULT, \
                                    SBB_MEAS_H129_RD_MASK, "SBB_MEAS_H129_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L129_OFFSET, \
                                    SBB_MEAS_L129_DEFAULT, \
                                    SBB_MEAS_L129_RD_MASK, "SBB_MEAS_L129_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H130_OFFSET, \
                                    SBB_MEAS_H130_DEFAULT, \
                                    SBB_MEAS_H130_RD_MASK, "SBB_MEAS_H130_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L130_OFFSET, \
                                    SBB_MEAS_L130_DEFAULT, \
                                    SBB_MEAS_L130_RD_MASK, "SBB_MEAS_L130_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H131_OFFSET, \
                                    SBB_MEAS_H131_DEFAULT, \
                                    SBB_MEAS_H131_RD_MASK, "SBB_MEAS_H131_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L131_OFFSET, \
                                    SBB_MEAS_L131_DEFAULT, \
                                    SBB_MEAS_L131_RD_MASK, "SBB_MEAS_L131_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H132_OFFSET, \
                                    SBB_MEAS_H132_DEFAULT, \
                                    SBB_MEAS_H132_RD_MASK, "SBB_MEAS_H132_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L132_OFFSET, \
                                    SBB_MEAS_L132_DEFAULT, \
                                    SBB_MEAS_L132_RD_MASK, "SBB_MEAS_L132_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H133_OFFSET, \
                                    SBB_MEAS_H133_DEFAULT, \
                                    SBB_MEAS_H133_RD_MASK, "SBB_MEAS_H133_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L133_OFFSET, \
                                    SBB_MEAS_L133_DEFAULT, \
                                    SBB_MEAS_L133_RD_MASK, "SBB_MEAS_L133_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H134_OFFSET, \
                                    SBB_MEAS_H134_DEFAULT, \
                                    SBB_MEAS_H134_RD_MASK, "SBB_MEAS_H134_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L134_OFFSET, \
                                    SBB_MEAS_L134_DEFAULT, \
                                    SBB_MEAS_L134_RD_MASK, "SBB_MEAS_L134_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H135_OFFSET, \
                                    SBB_MEAS_H135_DEFAULT, \
                                    SBB_MEAS_H135_RD_MASK, "SBB_MEAS_H135_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L135_OFFSET, \
                                    SBB_MEAS_L135_DEFAULT, \
                                    SBB_MEAS_L135_RD_MASK, "SBB_MEAS_L135_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H136_OFFSET, \
                                    SBB_MEAS_H136_DEFAULT, \
                                    SBB_MEAS_H136_RD_MASK, "SBB_MEAS_H136_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L136_OFFSET, \
                                    SBB_MEAS_L136_DEFAULT, \
                                    SBB_MEAS_L136_RD_MASK, "SBB_MEAS_L136_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H137_OFFSET, \
                                    SBB_MEAS_H137_DEFAULT, \
                                    SBB_MEAS_H137_RD_MASK, "SBB_MEAS_H137_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L137_OFFSET, \
                                    SBB_MEAS_L137_DEFAULT, \
                                    SBB_MEAS_L137_RD_MASK, "SBB_MEAS_L137_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H138_OFFSET, \
                                    SBB_MEAS_H138_DEFAULT, \
                                    SBB_MEAS_H138_RD_MASK, "SBB_MEAS_H138_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L138_OFFSET, \
                                    SBB_MEAS_L138_DEFAULT, \
                                    SBB_MEAS_L138_RD_MASK, "SBB_MEAS_L138_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H139_OFFSET, \
                                    SBB_MEAS_H139_DEFAULT, \
                                    SBB_MEAS_H139_RD_MASK, "SBB_MEAS_H139_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L139_OFFSET, \
                                    SBB_MEAS_L139_DEFAULT, \
                                    SBB_MEAS_L139_RD_MASK, "SBB_MEAS_L139_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H140_OFFSET, \
                                    SBB_MEAS_H140_DEFAULT, \
                                    SBB_MEAS_H140_RD_MASK, "SBB_MEAS_H140_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L140_OFFSET, \
                                    SBB_MEAS_L140_DEFAULT, \
                                    SBB_MEAS_L140_RD_MASK, "SBB_MEAS_L140_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H141_OFFSET, \
                                    SBB_MEAS_H141_DEFAULT, \
                                    SBB_MEAS_H141_RD_MASK, "SBB_MEAS_H141_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L141_OFFSET, \
                                    SBB_MEAS_L141_DEFAULT, \
                                    SBB_MEAS_L141_RD_MASK, "SBB_MEAS_L141_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H142_OFFSET, \
                                    SBB_MEAS_H142_DEFAULT, \
                                    SBB_MEAS_H142_RD_MASK, "SBB_MEAS_H142_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L142_OFFSET, \
                                    SBB_MEAS_L142_DEFAULT, \
                                    SBB_MEAS_L142_RD_MASK, "SBB_MEAS_L142_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_H143_OFFSET, \
                                    SBB_MEAS_H143_DEFAULT, \
                                    SBB_MEAS_H143_RD_MASK, "SBB_MEAS_H143_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_MEAS_L143_OFFSET, \
                                    SBB_MEAS_L143_DEFAULT, \
                                    SBB_MEAS_L143_RD_MASK, "SBB_MEAS_L143_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H0_OFFSET, \
                                    SBB_PCR_H0_DEFAULT, \
                                    SBB_PCR_H0_RD_MASK, "SBB_PCR_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L0_OFFSET, \
                                    SBB_PCR_L0_DEFAULT, \
                                    SBB_PCR_L0_RD_MASK, "SBB_PCR_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H1_OFFSET, \
                                    SBB_PCR_H1_DEFAULT, \
                                    SBB_PCR_H1_RD_MASK, "SBB_PCR_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L1_OFFSET, \
                                    SBB_PCR_L1_DEFAULT, \
                                    SBB_PCR_L1_RD_MASK, "SBB_PCR_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H2_OFFSET, \
                                    SBB_PCR_H2_DEFAULT, \
                                    SBB_PCR_H2_RD_MASK, "SBB_PCR_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L2_OFFSET, \
                                    SBB_PCR_L2_DEFAULT, \
                                    SBB_PCR_L2_RD_MASK, "SBB_PCR_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H3_OFFSET, \
                                    SBB_PCR_H3_DEFAULT, \
                                    SBB_PCR_H3_RD_MASK, "SBB_PCR_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L3_OFFSET, \
                                    SBB_PCR_L3_DEFAULT, \
                                    SBB_PCR_L3_RD_MASK, "SBB_PCR_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H4_OFFSET, \
                                    SBB_PCR_H4_DEFAULT, \
                                    SBB_PCR_H4_RD_MASK, "SBB_PCR_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L4_OFFSET, \
                                    SBB_PCR_L4_DEFAULT, \
                                    SBB_PCR_L4_RD_MASK, "SBB_PCR_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H5_OFFSET, \
                                    SBB_PCR_H5_DEFAULT, \
                                    SBB_PCR_H5_RD_MASK, "SBB_PCR_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L5_OFFSET, \
                                    SBB_PCR_L5_DEFAULT, \
                                    SBB_PCR_L5_RD_MASK, "SBB_PCR_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H6_OFFSET, \
                                    SBB_PCR_H6_DEFAULT, \
                                    SBB_PCR_H6_RD_MASK, "SBB_PCR_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L6_OFFSET, \
                                    SBB_PCR_L6_DEFAULT, \
                                    SBB_PCR_L6_RD_MASK, "SBB_PCR_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H7_OFFSET, \
                                    SBB_PCR_H7_DEFAULT, \
                                    SBB_PCR_H7_RD_MASK, "SBB_PCR_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L7_OFFSET, \
                                    SBB_PCR_L7_DEFAULT, \
                                    SBB_PCR_L7_RD_MASK, "SBB_PCR_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_H8_OFFSET, \
                                    SBB_PCR_H8_DEFAULT, \
                                    SBB_PCR_H8_RD_MASK, "SBB_PCR_H8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PCR_L8_OFFSET, \
                                    SBB_PCR_L8_DEFAULT, \
                                    SBB_PCR_L8_RD_MASK, "SBB_PCR_L8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_INT_STS_OFFSET, \
                                    SBB_INT_STS_DEFAULT, \
                                    SBB_INT_STS_RD_MASK, "SBB_INT_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_INT_EN_OFFSET, \
                                    SBB_INT_EN_DEFAULT, \
                                    SBB_INT_EN_RD_MASK, "SBB_INT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_INT_FRC_OFFSET, \
                                    SBB_INT_FRC_DEFAULT, \
                                    SBB_INT_FRC_RD_MASK, "SBB_INT_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_H0_OFFSET, \
                                    SBB_VER_H0_DEFAULT, \
                                    SBB_VER_H0_RD_MASK, "SBB_VER_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_L0_OFFSET, \
                                    SBB_VER_L0_DEFAULT, \
                                    SBB_VER_L0_RD_MASK, "SBB_VER_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_H1_OFFSET, \
                                    SBB_VER_H1_DEFAULT, \
                                    SBB_VER_H1_RD_MASK, "SBB_VER_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_L1_OFFSET, \
                                    SBB_VER_L1_DEFAULT, \
                                    SBB_VER_L1_RD_MASK, "SBB_VER_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_H2_OFFSET, \
                                    SBB_VER_H2_DEFAULT, \
                                    SBB_VER_H2_RD_MASK, "SBB_VER_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_L2_OFFSET, \
                                    SBB_VER_L2_DEFAULT, \
                                    SBB_VER_L2_RD_MASK, "SBB_VER_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_H3_OFFSET, \
                                    SBB_VER_H3_DEFAULT, \
                                    SBB_VER_H3_RD_MASK, "SBB_VER_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_VER_L3_OFFSET, \
                                    SBB_VER_L3_DEFAULT, \
                                    SBB_VER_L3_RD_MASK, "SBB_VER_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H0_OFFSET, \
                                    SBB_EFUSE_H0_DEFAULT, \
                                    SBB_EFUSE_H0_RD_MASK, "SBB_EFUSE_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L0_OFFSET, \
                                    SBB_EFUSE_L0_DEFAULT, \
                                    SBB_EFUSE_L0_RD_MASK, "SBB_EFUSE_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H1_OFFSET, \
                                    SBB_EFUSE_H1_DEFAULT, \
                                    SBB_EFUSE_H1_RD_MASK, "SBB_EFUSE_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L1_OFFSET, \
                                    SBB_EFUSE_L1_DEFAULT, \
                                    SBB_EFUSE_L1_RD_MASK, "SBB_EFUSE_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H2_OFFSET, \
                                    SBB_EFUSE_H2_DEFAULT, \
                                    SBB_EFUSE_H2_RD_MASK, "SBB_EFUSE_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L2_OFFSET, \
                                    SBB_EFUSE_L2_DEFAULT, \
                                    SBB_EFUSE_L2_RD_MASK, "SBB_EFUSE_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H3_OFFSET, \
                                    SBB_EFUSE_H3_DEFAULT, \
                                    SBB_EFUSE_H3_RD_MASK, "SBB_EFUSE_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L3_OFFSET, \
                                    SBB_EFUSE_L3_DEFAULT, \
                                    SBB_EFUSE_L3_RD_MASK, "SBB_EFUSE_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H4_OFFSET, \
                                    SBB_EFUSE_H4_DEFAULT, \
                                    SBB_EFUSE_H4_RD_MASK, "SBB_EFUSE_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L4_OFFSET, \
                                    SBB_EFUSE_L4_DEFAULT, \
                                    SBB_EFUSE_L4_RD_MASK, "SBB_EFUSE_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H5_OFFSET, \
                                    SBB_EFUSE_H5_DEFAULT, \
                                    SBB_EFUSE_H5_RD_MASK, "SBB_EFUSE_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L5_OFFSET, \
                                    SBB_EFUSE_L5_DEFAULT, \
                                    SBB_EFUSE_L5_RD_MASK, "SBB_EFUSE_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H6_OFFSET, \
                                    SBB_EFUSE_H6_DEFAULT, \
                                    SBB_EFUSE_H6_RD_MASK, "SBB_EFUSE_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L6_OFFSET, \
                                    SBB_EFUSE_L6_DEFAULT, \
                                    SBB_EFUSE_L6_RD_MASK, "SBB_EFUSE_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H7_OFFSET, \
                                    SBB_EFUSE_H7_DEFAULT, \
                                    SBB_EFUSE_H7_RD_MASK, "SBB_EFUSE_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L7_OFFSET, \
                                    SBB_EFUSE_L7_DEFAULT, \
                                    SBB_EFUSE_L7_RD_MASK, "SBB_EFUSE_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H8_OFFSET, \
                                    SBB_EFUSE_H8_DEFAULT, \
                                    SBB_EFUSE_H8_RD_MASK, "SBB_EFUSE_H8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L8_OFFSET, \
                                    SBB_EFUSE_L8_DEFAULT, \
                                    SBB_EFUSE_L8_RD_MASK, "SBB_EFUSE_L8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H9_OFFSET, \
                                    SBB_EFUSE_H9_DEFAULT, \
                                    SBB_EFUSE_H9_RD_MASK, "SBB_EFUSE_H9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L9_OFFSET, \
                                    SBB_EFUSE_L9_DEFAULT, \
                                    SBB_EFUSE_L9_RD_MASK, "SBB_EFUSE_L9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H10_OFFSET, \
                                    SBB_EFUSE_H10_DEFAULT, \
                                    SBB_EFUSE_H10_RD_MASK, "SBB_EFUSE_H10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L10_OFFSET, \
                                    SBB_EFUSE_L10_DEFAULT, \
                                    SBB_EFUSE_L10_RD_MASK, "SBB_EFUSE_L10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H11_OFFSET, \
                                    SBB_EFUSE_H11_DEFAULT, \
                                    SBB_EFUSE_H11_RD_MASK, "SBB_EFUSE_H11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L11_OFFSET, \
                                    SBB_EFUSE_L11_DEFAULT, \
                                    SBB_EFUSE_L11_RD_MASK, "SBB_EFUSE_L11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H12_OFFSET, \
                                    SBB_EFUSE_H12_DEFAULT, \
                                    SBB_EFUSE_H12_RD_MASK, "SBB_EFUSE_H12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L12_OFFSET, \
                                    SBB_EFUSE_L12_DEFAULT, \
                                    SBB_EFUSE_L12_RD_MASK, "SBB_EFUSE_L12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H13_OFFSET, \
                                    SBB_EFUSE_H13_DEFAULT, \
                                    SBB_EFUSE_H13_RD_MASK, "SBB_EFUSE_H13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L13_OFFSET, \
                                    SBB_EFUSE_L13_DEFAULT, \
                                    SBB_EFUSE_L13_RD_MASK, "SBB_EFUSE_L13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H14_OFFSET, \
                                    SBB_EFUSE_H14_DEFAULT, \
                                    SBB_EFUSE_H14_RD_MASK, "SBB_EFUSE_H14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L14_OFFSET, \
                                    SBB_EFUSE_L14_DEFAULT, \
                                    SBB_EFUSE_L14_RD_MASK, "SBB_EFUSE_L14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H15_OFFSET, \
                                    SBB_EFUSE_H15_DEFAULT, \
                                    SBB_EFUSE_H15_RD_MASK, "SBB_EFUSE_H15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L15_OFFSET, \
                                    SBB_EFUSE_L15_DEFAULT, \
                                    SBB_EFUSE_L15_RD_MASK, "SBB_EFUSE_L15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H16_OFFSET, \
                                    SBB_EFUSE_H16_DEFAULT, \
                                    SBB_EFUSE_H16_RD_MASK, "SBB_EFUSE_H16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L16_OFFSET, \
                                    SBB_EFUSE_L16_DEFAULT, \
                                    SBB_EFUSE_L16_RD_MASK, "SBB_EFUSE_L16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H17_OFFSET, \
                                    SBB_EFUSE_H17_DEFAULT, \
                                    SBB_EFUSE_H17_RD_MASK, "SBB_EFUSE_H17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L17_OFFSET, \
                                    SBB_EFUSE_L17_DEFAULT, \
                                    SBB_EFUSE_L17_RD_MASK, "SBB_EFUSE_L17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H18_OFFSET, \
                                    SBB_EFUSE_H18_DEFAULT, \
                                    SBB_EFUSE_H18_RD_MASK, "SBB_EFUSE_H18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L18_OFFSET, \
                                    SBB_EFUSE_L18_DEFAULT, \
                                    SBB_EFUSE_L18_RD_MASK, "SBB_EFUSE_L18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H19_OFFSET, \
                                    SBB_EFUSE_H19_DEFAULT, \
                                    SBB_EFUSE_H19_RD_MASK, "SBB_EFUSE_H19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L19_OFFSET, \
                                    SBB_EFUSE_L19_DEFAULT, \
                                    SBB_EFUSE_L19_RD_MASK, "SBB_EFUSE_L19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H20_OFFSET, \
                                    SBB_EFUSE_H20_DEFAULT, \
                                    SBB_EFUSE_H20_RD_MASK, "SBB_EFUSE_H20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L20_OFFSET, \
                                    SBB_EFUSE_L20_DEFAULT, \
                                    SBB_EFUSE_L20_RD_MASK, "SBB_EFUSE_L20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H21_OFFSET, \
                                    SBB_EFUSE_H21_DEFAULT, \
                                    SBB_EFUSE_H21_RD_MASK, "SBB_EFUSE_H21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L21_OFFSET, \
                                    SBB_EFUSE_L21_DEFAULT, \
                                    SBB_EFUSE_L21_RD_MASK, "SBB_EFUSE_L21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H22_OFFSET, \
                                    SBB_EFUSE_H22_DEFAULT, \
                                    SBB_EFUSE_H22_RD_MASK, "SBB_EFUSE_H22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L22_OFFSET, \
                                    SBB_EFUSE_L22_DEFAULT, \
                                    SBB_EFUSE_L22_RD_MASK, "SBB_EFUSE_L22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H23_OFFSET, \
                                    SBB_EFUSE_H23_DEFAULT, \
                                    SBB_EFUSE_H23_RD_MASK, "SBB_EFUSE_H23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L23_OFFSET, \
                                    SBB_EFUSE_L23_DEFAULT, \
                                    SBB_EFUSE_L23_RD_MASK, "SBB_EFUSE_L23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H24_OFFSET, \
                                    SBB_EFUSE_H24_DEFAULT, \
                                    SBB_EFUSE_H24_RD_MASK, "SBB_EFUSE_H24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L24_OFFSET, \
                                    SBB_EFUSE_L24_DEFAULT, \
                                    SBB_EFUSE_L24_RD_MASK, "SBB_EFUSE_L24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H25_OFFSET, \
                                    SBB_EFUSE_H25_DEFAULT, \
                                    SBB_EFUSE_H25_RD_MASK, "SBB_EFUSE_H25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L25_OFFSET, \
                                    SBB_EFUSE_L25_DEFAULT, \
                                    SBB_EFUSE_L25_RD_MASK, "SBB_EFUSE_L25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H26_OFFSET, \
                                    SBB_EFUSE_H26_DEFAULT, \
                                    SBB_EFUSE_H26_RD_MASK, "SBB_EFUSE_H26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L26_OFFSET, \
                                    SBB_EFUSE_L26_DEFAULT, \
                                    SBB_EFUSE_L26_RD_MASK, "SBB_EFUSE_L26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H27_OFFSET, \
                                    SBB_EFUSE_H27_DEFAULT, \
                                    SBB_EFUSE_H27_RD_MASK, "SBB_EFUSE_H27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L27_OFFSET, \
                                    SBB_EFUSE_L27_DEFAULT, \
                                    SBB_EFUSE_L27_RD_MASK, "SBB_EFUSE_L27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H28_OFFSET, \
                                    SBB_EFUSE_H28_DEFAULT, \
                                    SBB_EFUSE_H28_RD_MASK, "SBB_EFUSE_H28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L28_OFFSET, \
                                    SBB_EFUSE_L28_DEFAULT, \
                                    SBB_EFUSE_L28_RD_MASK, "SBB_EFUSE_L28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H29_OFFSET, \
                                    SBB_EFUSE_H29_DEFAULT, \
                                    SBB_EFUSE_H29_RD_MASK, "SBB_EFUSE_H29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L29_OFFSET, \
                                    SBB_EFUSE_L29_DEFAULT, \
                                    SBB_EFUSE_L29_RD_MASK, "SBB_EFUSE_L29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H30_OFFSET, \
                                    SBB_EFUSE_H30_DEFAULT, \
                                    SBB_EFUSE_H30_RD_MASK, "SBB_EFUSE_H30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L30_OFFSET, \
                                    SBB_EFUSE_L30_DEFAULT, \
                                    SBB_EFUSE_L30_RD_MASK, "SBB_EFUSE_L30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H31_OFFSET, \
                                    SBB_EFUSE_H31_DEFAULT, \
                                    SBB_EFUSE_H31_RD_MASK, "SBB_EFUSE_H31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L31_OFFSET, \
                                    SBB_EFUSE_L31_DEFAULT, \
                                    SBB_EFUSE_L31_RD_MASK, "SBB_EFUSE_L31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H32_OFFSET, \
                                    SBB_EFUSE_H32_DEFAULT, \
                                    SBB_EFUSE_H32_RD_MASK, "SBB_EFUSE_H32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L32_OFFSET, \
                                    SBB_EFUSE_L32_DEFAULT, \
                                    SBB_EFUSE_L32_RD_MASK, "SBB_EFUSE_L32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H33_OFFSET, \
                                    SBB_EFUSE_H33_DEFAULT, \
                                    SBB_EFUSE_H33_RD_MASK, "SBB_EFUSE_H33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L33_OFFSET, \
                                    SBB_EFUSE_L33_DEFAULT, \
                                    SBB_EFUSE_L33_RD_MASK, "SBB_EFUSE_L33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H34_OFFSET, \
                                    SBB_EFUSE_H34_DEFAULT, \
                                    SBB_EFUSE_H34_RD_MASK, "SBB_EFUSE_H34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L34_OFFSET, \
                                    SBB_EFUSE_L34_DEFAULT, \
                                    SBB_EFUSE_L34_RD_MASK, "SBB_EFUSE_L34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H35_OFFSET, \
                                    SBB_EFUSE_H35_DEFAULT, \
                                    SBB_EFUSE_H35_RD_MASK, "SBB_EFUSE_H35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L35_OFFSET, \
                                    SBB_EFUSE_L35_DEFAULT, \
                                    SBB_EFUSE_L35_RD_MASK, "SBB_EFUSE_L35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H36_OFFSET, \
                                    SBB_EFUSE_H36_DEFAULT, \
                                    SBB_EFUSE_H36_RD_MASK, "SBB_EFUSE_H36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L36_OFFSET, \
                                    SBB_EFUSE_L36_DEFAULT, \
                                    SBB_EFUSE_L36_RD_MASK, "SBB_EFUSE_L36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H37_OFFSET, \
                                    SBB_EFUSE_H37_DEFAULT, \
                                    SBB_EFUSE_H37_RD_MASK, "SBB_EFUSE_H37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L37_OFFSET, \
                                    SBB_EFUSE_L37_DEFAULT, \
                                    SBB_EFUSE_L37_RD_MASK, "SBB_EFUSE_L37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H38_OFFSET, \
                                    SBB_EFUSE_H38_DEFAULT, \
                                    SBB_EFUSE_H38_RD_MASK, "SBB_EFUSE_H38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L38_OFFSET, \
                                    SBB_EFUSE_L38_DEFAULT, \
                                    SBB_EFUSE_L38_RD_MASK, "SBB_EFUSE_L38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H39_OFFSET, \
                                    SBB_EFUSE_H39_DEFAULT, \
                                    SBB_EFUSE_H39_RD_MASK, "SBB_EFUSE_H39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L39_OFFSET, \
                                    SBB_EFUSE_L39_DEFAULT, \
                                    SBB_EFUSE_L39_RD_MASK, "SBB_EFUSE_L39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H40_OFFSET, \
                                    SBB_EFUSE_H40_DEFAULT, \
                                    SBB_EFUSE_H40_RD_MASK, "SBB_EFUSE_H40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L40_OFFSET, \
                                    SBB_EFUSE_L40_DEFAULT, \
                                    SBB_EFUSE_L40_RD_MASK, "SBB_EFUSE_L40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H41_OFFSET, \
                                    SBB_EFUSE_H41_DEFAULT, \
                                    SBB_EFUSE_H41_RD_MASK, "SBB_EFUSE_H41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L41_OFFSET, \
                                    SBB_EFUSE_L41_DEFAULT, \
                                    SBB_EFUSE_L41_RD_MASK, "SBB_EFUSE_L41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H42_OFFSET, \
                                    SBB_EFUSE_H42_DEFAULT, \
                                    SBB_EFUSE_H42_RD_MASK, "SBB_EFUSE_H42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L42_OFFSET, \
                                    SBB_EFUSE_L42_DEFAULT, \
                                    SBB_EFUSE_L42_RD_MASK, "SBB_EFUSE_L42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H43_OFFSET, \
                                    SBB_EFUSE_H43_DEFAULT, \
                                    SBB_EFUSE_H43_RD_MASK, "SBB_EFUSE_H43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L43_OFFSET, \
                                    SBB_EFUSE_L43_DEFAULT, \
                                    SBB_EFUSE_L43_RD_MASK, "SBB_EFUSE_L43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H44_OFFSET, \
                                    SBB_EFUSE_H44_DEFAULT, \
                                    SBB_EFUSE_H44_RD_MASK, "SBB_EFUSE_H44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L44_OFFSET, \
                                    SBB_EFUSE_L44_DEFAULT, \
                                    SBB_EFUSE_L44_RD_MASK, "SBB_EFUSE_L44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H45_OFFSET, \
                                    SBB_EFUSE_H45_DEFAULT, \
                                    SBB_EFUSE_H45_RD_MASK, "SBB_EFUSE_H45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L45_OFFSET, \
                                    SBB_EFUSE_L45_DEFAULT, \
                                    SBB_EFUSE_L45_RD_MASK, "SBB_EFUSE_L45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H46_OFFSET, \
                                    SBB_EFUSE_H46_DEFAULT, \
                                    SBB_EFUSE_H46_RD_MASK, "SBB_EFUSE_H46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L46_OFFSET, \
                                    SBB_EFUSE_L46_DEFAULT, \
                                    SBB_EFUSE_L46_RD_MASK, "SBB_EFUSE_L46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H47_OFFSET, \
                                    SBB_EFUSE_H47_DEFAULT, \
                                    SBB_EFUSE_H47_RD_MASK, "SBB_EFUSE_H47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L47_OFFSET, \
                                    SBB_EFUSE_L47_DEFAULT, \
                                    SBB_EFUSE_L47_RD_MASK, "SBB_EFUSE_L47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H48_OFFSET, \
                                    SBB_EFUSE_H48_DEFAULT, \
                                    SBB_EFUSE_H48_RD_MASK, "SBB_EFUSE_H48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L48_OFFSET, \
                                    SBB_EFUSE_L48_DEFAULT, \
                                    SBB_EFUSE_L48_RD_MASK, "SBB_EFUSE_L48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H49_OFFSET, \
                                    SBB_EFUSE_H49_DEFAULT, \
                                    SBB_EFUSE_H49_RD_MASK, "SBB_EFUSE_H49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L49_OFFSET, \
                                    SBB_EFUSE_L49_DEFAULT, \
                                    SBB_EFUSE_L49_RD_MASK, "SBB_EFUSE_L49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H50_OFFSET, \
                                    SBB_EFUSE_H50_DEFAULT, \
                                    SBB_EFUSE_H50_RD_MASK, "SBB_EFUSE_H50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L50_OFFSET, \
                                    SBB_EFUSE_L50_DEFAULT, \
                                    SBB_EFUSE_L50_RD_MASK, "SBB_EFUSE_L50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H51_OFFSET, \
                                    SBB_EFUSE_H51_DEFAULT, \
                                    SBB_EFUSE_H51_RD_MASK, "SBB_EFUSE_H51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L51_OFFSET, \
                                    SBB_EFUSE_L51_DEFAULT, \
                                    SBB_EFUSE_L51_RD_MASK, "SBB_EFUSE_L51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H52_OFFSET, \
                                    SBB_EFUSE_H52_DEFAULT, \
                                    SBB_EFUSE_H52_RD_MASK, "SBB_EFUSE_H52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L52_OFFSET, \
                                    SBB_EFUSE_L52_DEFAULT, \
                                    SBB_EFUSE_L52_RD_MASK, "SBB_EFUSE_L52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H53_OFFSET, \
                                    SBB_EFUSE_H53_DEFAULT, \
                                    SBB_EFUSE_H53_RD_MASK, "SBB_EFUSE_H53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L53_OFFSET, \
                                    SBB_EFUSE_L53_DEFAULT, \
                                    SBB_EFUSE_L53_RD_MASK, "SBB_EFUSE_L53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H54_OFFSET, \
                                    SBB_EFUSE_H54_DEFAULT, \
                                    SBB_EFUSE_H54_RD_MASK, "SBB_EFUSE_H54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L54_OFFSET, \
                                    SBB_EFUSE_L54_DEFAULT, \
                                    SBB_EFUSE_L54_RD_MASK, "SBB_EFUSE_L54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H55_OFFSET, \
                                    SBB_EFUSE_H55_DEFAULT, \
                                    SBB_EFUSE_H55_RD_MASK, "SBB_EFUSE_H55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L55_OFFSET, \
                                    SBB_EFUSE_L55_DEFAULT, \
                                    SBB_EFUSE_L55_RD_MASK, "SBB_EFUSE_L55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H56_OFFSET, \
                                    SBB_EFUSE_H56_DEFAULT, \
                                    SBB_EFUSE_H56_RD_MASK, "SBB_EFUSE_H56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L56_OFFSET, \
                                    SBB_EFUSE_L56_DEFAULT, \
                                    SBB_EFUSE_L56_RD_MASK, "SBB_EFUSE_L56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H57_OFFSET, \
                                    SBB_EFUSE_H57_DEFAULT, \
                                    SBB_EFUSE_H57_RD_MASK, "SBB_EFUSE_H57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L57_OFFSET, \
                                    SBB_EFUSE_L57_DEFAULT, \
                                    SBB_EFUSE_L57_RD_MASK, "SBB_EFUSE_L57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H58_OFFSET, \
                                    SBB_EFUSE_H58_DEFAULT, \
                                    SBB_EFUSE_H58_RD_MASK, "SBB_EFUSE_H58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L58_OFFSET, \
                                    SBB_EFUSE_L58_DEFAULT, \
                                    SBB_EFUSE_L58_RD_MASK, "SBB_EFUSE_L58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H59_OFFSET, \
                                    SBB_EFUSE_H59_DEFAULT, \
                                    SBB_EFUSE_H59_RD_MASK, "SBB_EFUSE_H59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L59_OFFSET, \
                                    SBB_EFUSE_L59_DEFAULT, \
                                    SBB_EFUSE_L59_RD_MASK, "SBB_EFUSE_L59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H60_OFFSET, \
                                    SBB_EFUSE_H60_DEFAULT, \
                                    SBB_EFUSE_H60_RD_MASK, "SBB_EFUSE_H60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L60_OFFSET, \
                                    SBB_EFUSE_L60_DEFAULT, \
                                    SBB_EFUSE_L60_RD_MASK, "SBB_EFUSE_L60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H61_OFFSET, \
                                    SBB_EFUSE_H61_DEFAULT, \
                                    SBB_EFUSE_H61_RD_MASK, "SBB_EFUSE_H61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L61_OFFSET, \
                                    SBB_EFUSE_L61_DEFAULT, \
                                    SBB_EFUSE_L61_RD_MASK, "SBB_EFUSE_L61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H62_OFFSET, \
                                    SBB_EFUSE_H62_DEFAULT, \
                                    SBB_EFUSE_H62_RD_MASK, "SBB_EFUSE_H62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L62_OFFSET, \
                                    SBB_EFUSE_L62_DEFAULT, \
                                    SBB_EFUSE_L62_RD_MASK, "SBB_EFUSE_L62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H63_OFFSET, \
                                    SBB_EFUSE_H63_DEFAULT, \
                                    SBB_EFUSE_H63_RD_MASK, "SBB_EFUSE_H63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L63_OFFSET, \
                                    SBB_EFUSE_L63_DEFAULT, \
                                    SBB_EFUSE_L63_RD_MASK, "SBB_EFUSE_L63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H64_OFFSET, \
                                    SBB_EFUSE_H64_DEFAULT, \
                                    SBB_EFUSE_H64_RD_MASK, "SBB_EFUSE_H64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L64_OFFSET, \
                                    SBB_EFUSE_L64_DEFAULT, \
                                    SBB_EFUSE_L64_RD_MASK, "SBB_EFUSE_L64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H65_OFFSET, \
                                    SBB_EFUSE_H65_DEFAULT, \
                                    SBB_EFUSE_H65_RD_MASK, "SBB_EFUSE_H65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L65_OFFSET, \
                                    SBB_EFUSE_L65_DEFAULT, \
                                    SBB_EFUSE_L65_RD_MASK, "SBB_EFUSE_L65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H66_OFFSET, \
                                    SBB_EFUSE_H66_DEFAULT, \
                                    SBB_EFUSE_H66_RD_MASK, "SBB_EFUSE_H66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L66_OFFSET, \
                                    SBB_EFUSE_L66_DEFAULT, \
                                    SBB_EFUSE_L66_RD_MASK, "SBB_EFUSE_L66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H67_OFFSET, \
                                    SBB_EFUSE_H67_DEFAULT, \
                                    SBB_EFUSE_H67_RD_MASK, "SBB_EFUSE_H67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L67_OFFSET, \
                                    SBB_EFUSE_L67_DEFAULT, \
                                    SBB_EFUSE_L67_RD_MASK, "SBB_EFUSE_L67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H68_OFFSET, \
                                    SBB_EFUSE_H68_DEFAULT, \
                                    SBB_EFUSE_H68_RD_MASK, "SBB_EFUSE_H68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L68_OFFSET, \
                                    SBB_EFUSE_L68_DEFAULT, \
                                    SBB_EFUSE_L68_RD_MASK, "SBB_EFUSE_L68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H69_OFFSET, \
                                    SBB_EFUSE_H69_DEFAULT, \
                                    SBB_EFUSE_H69_RD_MASK, "SBB_EFUSE_H69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L69_OFFSET, \
                                    SBB_EFUSE_L69_DEFAULT, \
                                    SBB_EFUSE_L69_RD_MASK, "SBB_EFUSE_L69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H70_OFFSET, \
                                    SBB_EFUSE_H70_DEFAULT, \
                                    SBB_EFUSE_H70_RD_MASK, "SBB_EFUSE_H70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L70_OFFSET, \
                                    SBB_EFUSE_L70_DEFAULT, \
                                    SBB_EFUSE_L70_RD_MASK, "SBB_EFUSE_L70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H71_OFFSET, \
                                    SBB_EFUSE_H71_DEFAULT, \
                                    SBB_EFUSE_H71_RD_MASK, "SBB_EFUSE_H71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L71_OFFSET, \
                                    SBB_EFUSE_L71_DEFAULT, \
                                    SBB_EFUSE_L71_RD_MASK, "SBB_EFUSE_L71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H72_OFFSET, \
                                    SBB_EFUSE_H72_DEFAULT, \
                                    SBB_EFUSE_H72_RD_MASK, "SBB_EFUSE_H72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L72_OFFSET, \
                                    SBB_EFUSE_L72_DEFAULT, \
                                    SBB_EFUSE_L72_RD_MASK, "SBB_EFUSE_L72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H73_OFFSET, \
                                    SBB_EFUSE_H73_DEFAULT, \
                                    SBB_EFUSE_H73_RD_MASK, "SBB_EFUSE_H73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L73_OFFSET, \
                                    SBB_EFUSE_L73_DEFAULT, \
                                    SBB_EFUSE_L73_RD_MASK, "SBB_EFUSE_L73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H74_OFFSET, \
                                    SBB_EFUSE_H74_DEFAULT, \
                                    SBB_EFUSE_H74_RD_MASK, "SBB_EFUSE_H74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L74_OFFSET, \
                                    SBB_EFUSE_L74_DEFAULT, \
                                    SBB_EFUSE_L74_RD_MASK, "SBB_EFUSE_L74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H75_OFFSET, \
                                    SBB_EFUSE_H75_DEFAULT, \
                                    SBB_EFUSE_H75_RD_MASK, "SBB_EFUSE_H75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L75_OFFSET, \
                                    SBB_EFUSE_L75_DEFAULT, \
                                    SBB_EFUSE_L75_RD_MASK, "SBB_EFUSE_L75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H76_OFFSET, \
                                    SBB_EFUSE_H76_DEFAULT, \
                                    SBB_EFUSE_H76_RD_MASK, "SBB_EFUSE_H76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L76_OFFSET, \
                                    SBB_EFUSE_L76_DEFAULT, \
                                    SBB_EFUSE_L76_RD_MASK, "SBB_EFUSE_L76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H77_OFFSET, \
                                    SBB_EFUSE_H77_DEFAULT, \
                                    SBB_EFUSE_H77_RD_MASK, "SBB_EFUSE_H77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L77_OFFSET, \
                                    SBB_EFUSE_L77_DEFAULT, \
                                    SBB_EFUSE_L77_RD_MASK, "SBB_EFUSE_L77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H78_OFFSET, \
                                    SBB_EFUSE_H78_DEFAULT, \
                                    SBB_EFUSE_H78_RD_MASK, "SBB_EFUSE_H78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L78_OFFSET, \
                                    SBB_EFUSE_L78_DEFAULT, \
                                    SBB_EFUSE_L78_RD_MASK, "SBB_EFUSE_L78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H79_OFFSET, \
                                    SBB_EFUSE_H79_DEFAULT, \
                                    SBB_EFUSE_H79_RD_MASK, "SBB_EFUSE_H79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L79_OFFSET, \
                                    SBB_EFUSE_L79_DEFAULT, \
                                    SBB_EFUSE_L79_RD_MASK, "SBB_EFUSE_L79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H80_OFFSET, \
                                    SBB_EFUSE_H80_DEFAULT, \
                                    SBB_EFUSE_H80_RD_MASK, "SBB_EFUSE_H80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L80_OFFSET, \
                                    SBB_EFUSE_L80_DEFAULT, \
                                    SBB_EFUSE_L80_RD_MASK, "SBB_EFUSE_L80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H81_OFFSET, \
                                    SBB_EFUSE_H81_DEFAULT, \
                                    SBB_EFUSE_H81_RD_MASK, "SBB_EFUSE_H81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L81_OFFSET, \
                                    SBB_EFUSE_L81_DEFAULT, \
                                    SBB_EFUSE_L81_RD_MASK, "SBB_EFUSE_L81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H82_OFFSET, \
                                    SBB_EFUSE_H82_DEFAULT, \
                                    SBB_EFUSE_H82_RD_MASK, "SBB_EFUSE_H82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L82_OFFSET, \
                                    SBB_EFUSE_L82_DEFAULT, \
                                    SBB_EFUSE_L82_RD_MASK, "SBB_EFUSE_L82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H83_OFFSET, \
                                    SBB_EFUSE_H83_DEFAULT, \
                                    SBB_EFUSE_H83_RD_MASK, "SBB_EFUSE_H83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L83_OFFSET, \
                                    SBB_EFUSE_L83_DEFAULT, \
                                    SBB_EFUSE_L83_RD_MASK, "SBB_EFUSE_L83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H84_OFFSET, \
                                    SBB_EFUSE_H84_DEFAULT, \
                                    SBB_EFUSE_H84_RD_MASK, "SBB_EFUSE_H84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L84_OFFSET, \
                                    SBB_EFUSE_L84_DEFAULT, \
                                    SBB_EFUSE_L84_RD_MASK, "SBB_EFUSE_L84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H85_OFFSET, \
                                    SBB_EFUSE_H85_DEFAULT, \
                                    SBB_EFUSE_H85_RD_MASK, "SBB_EFUSE_H85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L85_OFFSET, \
                                    SBB_EFUSE_L85_DEFAULT, \
                                    SBB_EFUSE_L85_RD_MASK, "SBB_EFUSE_L85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H86_OFFSET, \
                                    SBB_EFUSE_H86_DEFAULT, \
                                    SBB_EFUSE_H86_RD_MASK, "SBB_EFUSE_H86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L86_OFFSET, \
                                    SBB_EFUSE_L86_DEFAULT, \
                                    SBB_EFUSE_L86_RD_MASK, "SBB_EFUSE_L86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H87_OFFSET, \
                                    SBB_EFUSE_H87_DEFAULT, \
                                    SBB_EFUSE_H87_RD_MASK, "SBB_EFUSE_H87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L87_OFFSET, \
                                    SBB_EFUSE_L87_DEFAULT, \
                                    SBB_EFUSE_L87_RD_MASK, "SBB_EFUSE_L87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H88_OFFSET, \
                                    SBB_EFUSE_H88_DEFAULT, \
                                    SBB_EFUSE_H88_RD_MASK, "SBB_EFUSE_H88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L88_OFFSET, \
                                    SBB_EFUSE_L88_DEFAULT, \
                                    SBB_EFUSE_L88_RD_MASK, "SBB_EFUSE_L88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H89_OFFSET, \
                                    SBB_EFUSE_H89_DEFAULT, \
                                    SBB_EFUSE_H89_RD_MASK, "SBB_EFUSE_H89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L89_OFFSET, \
                                    SBB_EFUSE_L89_DEFAULT, \
                                    SBB_EFUSE_L89_RD_MASK, "SBB_EFUSE_L89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H90_OFFSET, \
                                    SBB_EFUSE_H90_DEFAULT, \
                                    SBB_EFUSE_H90_RD_MASK, "SBB_EFUSE_H90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L90_OFFSET, \
                                    SBB_EFUSE_L90_DEFAULT, \
                                    SBB_EFUSE_L90_RD_MASK, "SBB_EFUSE_L90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H91_OFFSET, \
                                    SBB_EFUSE_H91_DEFAULT, \
                                    SBB_EFUSE_H91_RD_MASK, "SBB_EFUSE_H91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L91_OFFSET, \
                                    SBB_EFUSE_L91_DEFAULT, \
                                    SBB_EFUSE_L91_RD_MASK, "SBB_EFUSE_L91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H92_OFFSET, \
                                    SBB_EFUSE_H92_DEFAULT, \
                                    SBB_EFUSE_H92_RD_MASK, "SBB_EFUSE_H92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L92_OFFSET, \
                                    SBB_EFUSE_L92_DEFAULT, \
                                    SBB_EFUSE_L92_RD_MASK, "SBB_EFUSE_L92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H93_OFFSET, \
                                    SBB_EFUSE_H93_DEFAULT, \
                                    SBB_EFUSE_H93_RD_MASK, "SBB_EFUSE_H93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L93_OFFSET, \
                                    SBB_EFUSE_L93_DEFAULT, \
                                    SBB_EFUSE_L93_RD_MASK, "SBB_EFUSE_L93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H94_OFFSET, \
                                    SBB_EFUSE_H94_DEFAULT, \
                                    SBB_EFUSE_H94_RD_MASK, "SBB_EFUSE_H94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L94_OFFSET, \
                                    SBB_EFUSE_L94_DEFAULT, \
                                    SBB_EFUSE_L94_RD_MASK, "SBB_EFUSE_L94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H95_OFFSET, \
                                    SBB_EFUSE_H95_DEFAULT, \
                                    SBB_EFUSE_H95_RD_MASK, "SBB_EFUSE_H95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L95_OFFSET, \
                                    SBB_EFUSE_L95_DEFAULT, \
                                    SBB_EFUSE_L95_RD_MASK, "SBB_EFUSE_L95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H96_OFFSET, \
                                    SBB_EFUSE_H96_DEFAULT, \
                                    SBB_EFUSE_H96_RD_MASK, "SBB_EFUSE_H96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L96_OFFSET, \
                                    SBB_EFUSE_L96_DEFAULT, \
                                    SBB_EFUSE_L96_RD_MASK, "SBB_EFUSE_L96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H97_OFFSET, \
                                    SBB_EFUSE_H97_DEFAULT, \
                                    SBB_EFUSE_H97_RD_MASK, "SBB_EFUSE_H97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L97_OFFSET, \
                                    SBB_EFUSE_L97_DEFAULT, \
                                    SBB_EFUSE_L97_RD_MASK, "SBB_EFUSE_L97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H98_OFFSET, \
                                    SBB_EFUSE_H98_DEFAULT, \
                                    SBB_EFUSE_H98_RD_MASK, "SBB_EFUSE_H98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L98_OFFSET, \
                                    SBB_EFUSE_L98_DEFAULT, \
                                    SBB_EFUSE_L98_RD_MASK, "SBB_EFUSE_L98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H99_OFFSET, \
                                    SBB_EFUSE_H99_DEFAULT, \
                                    SBB_EFUSE_H99_RD_MASK, "SBB_EFUSE_H99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L99_OFFSET, \
                                    SBB_EFUSE_L99_DEFAULT, \
                                    SBB_EFUSE_L99_RD_MASK, "SBB_EFUSE_L99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H100_OFFSET, \
                                    SBB_EFUSE_H100_DEFAULT, \
                                    SBB_EFUSE_H100_RD_MASK, "SBB_EFUSE_H100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L100_OFFSET, \
                                    SBB_EFUSE_L100_DEFAULT, \
                                    SBB_EFUSE_L100_RD_MASK, "SBB_EFUSE_L100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H101_OFFSET, \
                                    SBB_EFUSE_H101_DEFAULT, \
                                    SBB_EFUSE_H101_RD_MASK, "SBB_EFUSE_H101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L101_OFFSET, \
                                    SBB_EFUSE_L101_DEFAULT, \
                                    SBB_EFUSE_L101_RD_MASK, "SBB_EFUSE_L101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H102_OFFSET, \
                                    SBB_EFUSE_H102_DEFAULT, \
                                    SBB_EFUSE_H102_RD_MASK, "SBB_EFUSE_H102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L102_OFFSET, \
                                    SBB_EFUSE_L102_DEFAULT, \
                                    SBB_EFUSE_L102_RD_MASK, "SBB_EFUSE_L102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H103_OFFSET, \
                                    SBB_EFUSE_H103_DEFAULT, \
                                    SBB_EFUSE_H103_RD_MASK, "SBB_EFUSE_H103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L103_OFFSET, \
                                    SBB_EFUSE_L103_DEFAULT, \
                                    SBB_EFUSE_L103_RD_MASK, "SBB_EFUSE_L103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H104_OFFSET, \
                                    SBB_EFUSE_H104_DEFAULT, \
                                    SBB_EFUSE_H104_RD_MASK, "SBB_EFUSE_H104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L104_OFFSET, \
                                    SBB_EFUSE_L104_DEFAULT, \
                                    SBB_EFUSE_L104_RD_MASK, "SBB_EFUSE_L104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H105_OFFSET, \
                                    SBB_EFUSE_H105_DEFAULT, \
                                    SBB_EFUSE_H105_RD_MASK, "SBB_EFUSE_H105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L105_OFFSET, \
                                    SBB_EFUSE_L105_DEFAULT, \
                                    SBB_EFUSE_L105_RD_MASK, "SBB_EFUSE_L105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H106_OFFSET, \
                                    SBB_EFUSE_H106_DEFAULT, \
                                    SBB_EFUSE_H106_RD_MASK, "SBB_EFUSE_H106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L106_OFFSET, \
                                    SBB_EFUSE_L106_DEFAULT, \
                                    SBB_EFUSE_L106_RD_MASK, "SBB_EFUSE_L106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H107_OFFSET, \
                                    SBB_EFUSE_H107_DEFAULT, \
                                    SBB_EFUSE_H107_RD_MASK, "SBB_EFUSE_H107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L107_OFFSET, \
                                    SBB_EFUSE_L107_DEFAULT, \
                                    SBB_EFUSE_L107_RD_MASK, "SBB_EFUSE_L107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H108_OFFSET, \
                                    SBB_EFUSE_H108_DEFAULT, \
                                    SBB_EFUSE_H108_RD_MASK, "SBB_EFUSE_H108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L108_OFFSET, \
                                    SBB_EFUSE_L108_DEFAULT, \
                                    SBB_EFUSE_L108_RD_MASK, "SBB_EFUSE_L108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H109_OFFSET, \
                                    SBB_EFUSE_H109_DEFAULT, \
                                    SBB_EFUSE_H109_RD_MASK, "SBB_EFUSE_H109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L109_OFFSET, \
                                    SBB_EFUSE_L109_DEFAULT, \
                                    SBB_EFUSE_L109_RD_MASK, "SBB_EFUSE_L109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H110_OFFSET, \
                                    SBB_EFUSE_H110_DEFAULT, \
                                    SBB_EFUSE_H110_RD_MASK, "SBB_EFUSE_H110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L110_OFFSET, \
                                    SBB_EFUSE_L110_DEFAULT, \
                                    SBB_EFUSE_L110_RD_MASK, "SBB_EFUSE_L110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_H111_OFFSET, \
                                    SBB_EFUSE_H111_DEFAULT, \
                                    SBB_EFUSE_H111_RD_MASK, "SBB_EFUSE_H111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_EFUSE_L111_OFFSET, \
                                    SBB_EFUSE_L111_DEFAULT, \
                                    SBB_EFUSE_L111_RD_MASK, "SBB_EFUSE_L111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H0_OFFSET, \
                                    SBB_PARAM_EXT_H0_DEFAULT, \
                                    SBB_PARAM_EXT_H0_RD_MASK, "SBB_PARAM_EXT_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L0_OFFSET, \
                                    SBB_PARAM_EXT_L0_DEFAULT, \
                                    SBB_PARAM_EXT_L0_RD_MASK, "SBB_PARAM_EXT_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H1_OFFSET, \
                                    SBB_PARAM_EXT_H1_DEFAULT, \
                                    SBB_PARAM_EXT_H1_RD_MASK, "SBB_PARAM_EXT_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L1_OFFSET, \
                                    SBB_PARAM_EXT_L1_DEFAULT, \
                                    SBB_PARAM_EXT_L1_RD_MASK, "SBB_PARAM_EXT_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H2_OFFSET, \
                                    SBB_PARAM_EXT_H2_DEFAULT, \
                                    SBB_PARAM_EXT_H2_RD_MASK, "SBB_PARAM_EXT_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L2_OFFSET, \
                                    SBB_PARAM_EXT_L2_DEFAULT, \
                                    SBB_PARAM_EXT_L2_RD_MASK, "SBB_PARAM_EXT_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H3_OFFSET, \
                                    SBB_PARAM_EXT_H3_DEFAULT, \
                                    SBB_PARAM_EXT_H3_RD_MASK, "SBB_PARAM_EXT_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L3_OFFSET, \
                                    SBB_PARAM_EXT_L3_DEFAULT, \
                                    SBB_PARAM_EXT_L3_RD_MASK, "SBB_PARAM_EXT_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H4_OFFSET, \
                                    SBB_PARAM_EXT_H4_DEFAULT, \
                                    SBB_PARAM_EXT_H4_RD_MASK, "SBB_PARAM_EXT_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L4_OFFSET, \
                                    SBB_PARAM_EXT_L4_DEFAULT, \
                                    SBB_PARAM_EXT_L4_RD_MASK, "SBB_PARAM_EXT_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H5_OFFSET, \
                                    SBB_PARAM_EXT_H5_DEFAULT, \
                                    SBB_PARAM_EXT_H5_RD_MASK, "SBB_PARAM_EXT_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L5_OFFSET, \
                                    SBB_PARAM_EXT_L5_DEFAULT, \
                                    SBB_PARAM_EXT_L5_RD_MASK, "SBB_PARAM_EXT_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H6_OFFSET, \
                                    SBB_PARAM_EXT_H6_DEFAULT, \
                                    SBB_PARAM_EXT_H6_RD_MASK, "SBB_PARAM_EXT_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L6_OFFSET, \
                                    SBB_PARAM_EXT_L6_DEFAULT, \
                                    SBB_PARAM_EXT_L6_RD_MASK, "SBB_PARAM_EXT_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H7_OFFSET, \
                                    SBB_PARAM_EXT_H7_DEFAULT, \
                                    SBB_PARAM_EXT_H7_RD_MASK, "SBB_PARAM_EXT_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L7_OFFSET, \
                                    SBB_PARAM_EXT_L7_DEFAULT, \
                                    SBB_PARAM_EXT_L7_RD_MASK, "SBB_PARAM_EXT_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H8_OFFSET, \
                                    SBB_PARAM_EXT_H8_DEFAULT, \
                                    SBB_PARAM_EXT_H8_RD_MASK, "SBB_PARAM_EXT_H8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L8_OFFSET, \
                                    SBB_PARAM_EXT_L8_DEFAULT, \
                                    SBB_PARAM_EXT_L8_RD_MASK, "SBB_PARAM_EXT_L8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H9_OFFSET, \
                                    SBB_PARAM_EXT_H9_DEFAULT, \
                                    SBB_PARAM_EXT_H9_RD_MASK, "SBB_PARAM_EXT_H9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L9_OFFSET, \
                                    SBB_PARAM_EXT_L9_DEFAULT, \
                                    SBB_PARAM_EXT_L9_RD_MASK, "SBB_PARAM_EXT_L9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H10_OFFSET, \
                                    SBB_PARAM_EXT_H10_DEFAULT, \
                                    SBB_PARAM_EXT_H10_RD_MASK, "SBB_PARAM_EXT_H10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L10_OFFSET, \
                                    SBB_PARAM_EXT_L10_DEFAULT, \
                                    SBB_PARAM_EXT_L10_RD_MASK, "SBB_PARAM_EXT_L10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H11_OFFSET, \
                                    SBB_PARAM_EXT_H11_DEFAULT, \
                                    SBB_PARAM_EXT_H11_RD_MASK, "SBB_PARAM_EXT_H11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L11_OFFSET, \
                                    SBB_PARAM_EXT_L11_DEFAULT, \
                                    SBB_PARAM_EXT_L11_RD_MASK, "SBB_PARAM_EXT_L11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H12_OFFSET, \
                                    SBB_PARAM_EXT_H12_DEFAULT, \
                                    SBB_PARAM_EXT_H12_RD_MASK, "SBB_PARAM_EXT_H12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L12_OFFSET, \
                                    SBB_PARAM_EXT_L12_DEFAULT, \
                                    SBB_PARAM_EXT_L12_RD_MASK, "SBB_PARAM_EXT_L12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H13_OFFSET, \
                                    SBB_PARAM_EXT_H13_DEFAULT, \
                                    SBB_PARAM_EXT_H13_RD_MASK, "SBB_PARAM_EXT_H13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L13_OFFSET, \
                                    SBB_PARAM_EXT_L13_DEFAULT, \
                                    SBB_PARAM_EXT_L13_RD_MASK, "SBB_PARAM_EXT_L13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H14_OFFSET, \
                                    SBB_PARAM_EXT_H14_DEFAULT, \
                                    SBB_PARAM_EXT_H14_RD_MASK, "SBB_PARAM_EXT_H14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L14_OFFSET, \
                                    SBB_PARAM_EXT_L14_DEFAULT, \
                                    SBB_PARAM_EXT_L14_RD_MASK, "SBB_PARAM_EXT_L14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H15_OFFSET, \
                                    SBB_PARAM_EXT_H15_DEFAULT, \
                                    SBB_PARAM_EXT_H15_RD_MASK, "SBB_PARAM_EXT_H15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L15_OFFSET, \
                                    SBB_PARAM_EXT_L15_DEFAULT, \
                                    SBB_PARAM_EXT_L15_RD_MASK, "SBB_PARAM_EXT_L15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H16_OFFSET, \
                                    SBB_PARAM_EXT_H16_DEFAULT, \
                                    SBB_PARAM_EXT_H16_RD_MASK, "SBB_PARAM_EXT_H16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L16_OFFSET, \
                                    SBB_PARAM_EXT_L16_DEFAULT, \
                                    SBB_PARAM_EXT_L16_RD_MASK, "SBB_PARAM_EXT_L16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H17_OFFSET, \
                                    SBB_PARAM_EXT_H17_DEFAULT, \
                                    SBB_PARAM_EXT_H17_RD_MASK, "SBB_PARAM_EXT_H17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L17_OFFSET, \
                                    SBB_PARAM_EXT_L17_DEFAULT, \
                                    SBB_PARAM_EXT_L17_RD_MASK, "SBB_PARAM_EXT_L17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H18_OFFSET, \
                                    SBB_PARAM_EXT_H18_DEFAULT, \
                                    SBB_PARAM_EXT_H18_RD_MASK, "SBB_PARAM_EXT_H18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L18_OFFSET, \
                                    SBB_PARAM_EXT_L18_DEFAULT, \
                                    SBB_PARAM_EXT_L18_RD_MASK, "SBB_PARAM_EXT_L18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H19_OFFSET, \
                                    SBB_PARAM_EXT_H19_DEFAULT, \
                                    SBB_PARAM_EXT_H19_RD_MASK, "SBB_PARAM_EXT_H19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L19_OFFSET, \
                                    SBB_PARAM_EXT_L19_DEFAULT, \
                                    SBB_PARAM_EXT_L19_RD_MASK, "SBB_PARAM_EXT_L19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H20_OFFSET, \
                                    SBB_PARAM_EXT_H20_DEFAULT, \
                                    SBB_PARAM_EXT_H20_RD_MASK, "SBB_PARAM_EXT_H20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L20_OFFSET, \
                                    SBB_PARAM_EXT_L20_DEFAULT, \
                                    SBB_PARAM_EXT_L20_RD_MASK, "SBB_PARAM_EXT_L20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H21_OFFSET, \
                                    SBB_PARAM_EXT_H21_DEFAULT, \
                                    SBB_PARAM_EXT_H21_RD_MASK, "SBB_PARAM_EXT_H21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L21_OFFSET, \
                                    SBB_PARAM_EXT_L21_DEFAULT, \
                                    SBB_PARAM_EXT_L21_RD_MASK, "SBB_PARAM_EXT_L21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H22_OFFSET, \
                                    SBB_PARAM_EXT_H22_DEFAULT, \
                                    SBB_PARAM_EXT_H22_RD_MASK, "SBB_PARAM_EXT_H22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L22_OFFSET, \
                                    SBB_PARAM_EXT_L22_DEFAULT, \
                                    SBB_PARAM_EXT_L22_RD_MASK, "SBB_PARAM_EXT_L22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H23_OFFSET, \
                                    SBB_PARAM_EXT_H23_DEFAULT, \
                                    SBB_PARAM_EXT_H23_RD_MASK, "SBB_PARAM_EXT_H23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L23_OFFSET, \
                                    SBB_PARAM_EXT_L23_DEFAULT, \
                                    SBB_PARAM_EXT_L23_RD_MASK, "SBB_PARAM_EXT_L23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H24_OFFSET, \
                                    SBB_PARAM_EXT_H24_DEFAULT, \
                                    SBB_PARAM_EXT_H24_RD_MASK, "SBB_PARAM_EXT_H24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L24_OFFSET, \
                                    SBB_PARAM_EXT_L24_DEFAULT, \
                                    SBB_PARAM_EXT_L24_RD_MASK, "SBB_PARAM_EXT_L24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H25_OFFSET, \
                                    SBB_PARAM_EXT_H25_DEFAULT, \
                                    SBB_PARAM_EXT_H25_RD_MASK, "SBB_PARAM_EXT_H25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L25_OFFSET, \
                                    SBB_PARAM_EXT_L25_DEFAULT, \
                                    SBB_PARAM_EXT_L25_RD_MASK, "SBB_PARAM_EXT_L25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H26_OFFSET, \
                                    SBB_PARAM_EXT_H26_DEFAULT, \
                                    SBB_PARAM_EXT_H26_RD_MASK, "SBB_PARAM_EXT_H26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L26_OFFSET, \
                                    SBB_PARAM_EXT_L26_DEFAULT, \
                                    SBB_PARAM_EXT_L26_RD_MASK, "SBB_PARAM_EXT_L26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H27_OFFSET, \
                                    SBB_PARAM_EXT_H27_DEFAULT, \
                                    SBB_PARAM_EXT_H27_RD_MASK, "SBB_PARAM_EXT_H27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L27_OFFSET, \
                                    SBB_PARAM_EXT_L27_DEFAULT, \
                                    SBB_PARAM_EXT_L27_RD_MASK, "SBB_PARAM_EXT_L27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H28_OFFSET, \
                                    SBB_PARAM_EXT_H28_DEFAULT, \
                                    SBB_PARAM_EXT_H28_RD_MASK, "SBB_PARAM_EXT_H28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L28_OFFSET, \
                                    SBB_PARAM_EXT_L28_DEFAULT, \
                                    SBB_PARAM_EXT_L28_RD_MASK, "SBB_PARAM_EXT_L28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H29_OFFSET, \
                                    SBB_PARAM_EXT_H29_DEFAULT, \
                                    SBB_PARAM_EXT_H29_RD_MASK, "SBB_PARAM_EXT_H29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L29_OFFSET, \
                                    SBB_PARAM_EXT_L29_DEFAULT, \
                                    SBB_PARAM_EXT_L29_RD_MASK, "SBB_PARAM_EXT_L29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H30_OFFSET, \
                                    SBB_PARAM_EXT_H30_DEFAULT, \
                                    SBB_PARAM_EXT_H30_RD_MASK, "SBB_PARAM_EXT_H30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L30_OFFSET, \
                                    SBB_PARAM_EXT_L30_DEFAULT, \
                                    SBB_PARAM_EXT_L30_RD_MASK, "SBB_PARAM_EXT_L30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H31_OFFSET, \
                                    SBB_PARAM_EXT_H31_DEFAULT, \
                                    SBB_PARAM_EXT_H31_RD_MASK, "SBB_PARAM_EXT_H31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L31_OFFSET, \
                                    SBB_PARAM_EXT_L31_DEFAULT, \
                                    SBB_PARAM_EXT_L31_RD_MASK, "SBB_PARAM_EXT_L31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H32_OFFSET, \
                                    SBB_PARAM_EXT_H32_DEFAULT, \
                                    SBB_PARAM_EXT_H32_RD_MASK, "SBB_PARAM_EXT_H32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L32_OFFSET, \
                                    SBB_PARAM_EXT_L32_DEFAULT, \
                                    SBB_PARAM_EXT_L32_RD_MASK, "SBB_PARAM_EXT_L32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H33_OFFSET, \
                                    SBB_PARAM_EXT_H33_DEFAULT, \
                                    SBB_PARAM_EXT_H33_RD_MASK, "SBB_PARAM_EXT_H33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L33_OFFSET, \
                                    SBB_PARAM_EXT_L33_DEFAULT, \
                                    SBB_PARAM_EXT_L33_RD_MASK, "SBB_PARAM_EXT_L33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H34_OFFSET, \
                                    SBB_PARAM_EXT_H34_DEFAULT, \
                                    SBB_PARAM_EXT_H34_RD_MASK, "SBB_PARAM_EXT_H34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L34_OFFSET, \
                                    SBB_PARAM_EXT_L34_DEFAULT, \
                                    SBB_PARAM_EXT_L34_RD_MASK, "SBB_PARAM_EXT_L34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H35_OFFSET, \
                                    SBB_PARAM_EXT_H35_DEFAULT, \
                                    SBB_PARAM_EXT_H35_RD_MASK, "SBB_PARAM_EXT_H35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L35_OFFSET, \
                                    SBB_PARAM_EXT_L35_DEFAULT, \
                                    SBB_PARAM_EXT_L35_RD_MASK, "SBB_PARAM_EXT_L35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H36_OFFSET, \
                                    SBB_PARAM_EXT_H36_DEFAULT, \
                                    SBB_PARAM_EXT_H36_RD_MASK, "SBB_PARAM_EXT_H36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L36_OFFSET, \
                                    SBB_PARAM_EXT_L36_DEFAULT, \
                                    SBB_PARAM_EXT_L36_RD_MASK, "SBB_PARAM_EXT_L36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H37_OFFSET, \
                                    SBB_PARAM_EXT_H37_DEFAULT, \
                                    SBB_PARAM_EXT_H37_RD_MASK, "SBB_PARAM_EXT_H37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L37_OFFSET, \
                                    SBB_PARAM_EXT_L37_DEFAULT, \
                                    SBB_PARAM_EXT_L37_RD_MASK, "SBB_PARAM_EXT_L37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H38_OFFSET, \
                                    SBB_PARAM_EXT_H38_DEFAULT, \
                                    SBB_PARAM_EXT_H38_RD_MASK, "SBB_PARAM_EXT_H38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L38_OFFSET, \
                                    SBB_PARAM_EXT_L38_DEFAULT, \
                                    SBB_PARAM_EXT_L38_RD_MASK, "SBB_PARAM_EXT_L38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H39_OFFSET, \
                                    SBB_PARAM_EXT_H39_DEFAULT, \
                                    SBB_PARAM_EXT_H39_RD_MASK, "SBB_PARAM_EXT_H39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L39_OFFSET, \
                                    SBB_PARAM_EXT_L39_DEFAULT, \
                                    SBB_PARAM_EXT_L39_RD_MASK, "SBB_PARAM_EXT_L39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H40_OFFSET, \
                                    SBB_PARAM_EXT_H40_DEFAULT, \
                                    SBB_PARAM_EXT_H40_RD_MASK, "SBB_PARAM_EXT_H40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L40_OFFSET, \
                                    SBB_PARAM_EXT_L40_DEFAULT, \
                                    SBB_PARAM_EXT_L40_RD_MASK, "SBB_PARAM_EXT_L40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H41_OFFSET, \
                                    SBB_PARAM_EXT_H41_DEFAULT, \
                                    SBB_PARAM_EXT_H41_RD_MASK, "SBB_PARAM_EXT_H41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L41_OFFSET, \
                                    SBB_PARAM_EXT_L41_DEFAULT, \
                                    SBB_PARAM_EXT_L41_RD_MASK, "SBB_PARAM_EXT_L41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H42_OFFSET, \
                                    SBB_PARAM_EXT_H42_DEFAULT, \
                                    SBB_PARAM_EXT_H42_RD_MASK, "SBB_PARAM_EXT_H42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L42_OFFSET, \
                                    SBB_PARAM_EXT_L42_DEFAULT, \
                                    SBB_PARAM_EXT_L42_RD_MASK, "SBB_PARAM_EXT_L42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H43_OFFSET, \
                                    SBB_PARAM_EXT_H43_DEFAULT, \
                                    SBB_PARAM_EXT_H43_RD_MASK, "SBB_PARAM_EXT_H43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L43_OFFSET, \
                                    SBB_PARAM_EXT_L43_DEFAULT, \
                                    SBB_PARAM_EXT_L43_RD_MASK, "SBB_PARAM_EXT_L43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H44_OFFSET, \
                                    SBB_PARAM_EXT_H44_DEFAULT, \
                                    SBB_PARAM_EXT_H44_RD_MASK, "SBB_PARAM_EXT_H44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L44_OFFSET, \
                                    SBB_PARAM_EXT_L44_DEFAULT, \
                                    SBB_PARAM_EXT_L44_RD_MASK, "SBB_PARAM_EXT_L44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H45_OFFSET, \
                                    SBB_PARAM_EXT_H45_DEFAULT, \
                                    SBB_PARAM_EXT_H45_RD_MASK, "SBB_PARAM_EXT_H45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L45_OFFSET, \
                                    SBB_PARAM_EXT_L45_DEFAULT, \
                                    SBB_PARAM_EXT_L45_RD_MASK, "SBB_PARAM_EXT_L45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H46_OFFSET, \
                                    SBB_PARAM_EXT_H46_DEFAULT, \
                                    SBB_PARAM_EXT_H46_RD_MASK, "SBB_PARAM_EXT_H46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L46_OFFSET, \
                                    SBB_PARAM_EXT_L46_DEFAULT, \
                                    SBB_PARAM_EXT_L46_RD_MASK, "SBB_PARAM_EXT_L46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H47_OFFSET, \
                                    SBB_PARAM_EXT_H47_DEFAULT, \
                                    SBB_PARAM_EXT_H47_RD_MASK, "SBB_PARAM_EXT_H47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L47_OFFSET, \
                                    SBB_PARAM_EXT_L47_DEFAULT, \
                                    SBB_PARAM_EXT_L47_RD_MASK, "SBB_PARAM_EXT_L47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H48_OFFSET, \
                                    SBB_PARAM_EXT_H48_DEFAULT, \
                                    SBB_PARAM_EXT_H48_RD_MASK, "SBB_PARAM_EXT_H48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L48_OFFSET, \
                                    SBB_PARAM_EXT_L48_DEFAULT, \
                                    SBB_PARAM_EXT_L48_RD_MASK, "SBB_PARAM_EXT_L48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H49_OFFSET, \
                                    SBB_PARAM_EXT_H49_DEFAULT, \
                                    SBB_PARAM_EXT_H49_RD_MASK, "SBB_PARAM_EXT_H49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L49_OFFSET, \
                                    SBB_PARAM_EXT_L49_DEFAULT, \
                                    SBB_PARAM_EXT_L49_RD_MASK, "SBB_PARAM_EXT_L49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H50_OFFSET, \
                                    SBB_PARAM_EXT_H50_DEFAULT, \
                                    SBB_PARAM_EXT_H50_RD_MASK, "SBB_PARAM_EXT_H50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L50_OFFSET, \
                                    SBB_PARAM_EXT_L50_DEFAULT, \
                                    SBB_PARAM_EXT_L50_RD_MASK, "SBB_PARAM_EXT_L50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H51_OFFSET, \
                                    SBB_PARAM_EXT_H51_DEFAULT, \
                                    SBB_PARAM_EXT_H51_RD_MASK, "SBB_PARAM_EXT_H51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L51_OFFSET, \
                                    SBB_PARAM_EXT_L51_DEFAULT, \
                                    SBB_PARAM_EXT_L51_RD_MASK, "SBB_PARAM_EXT_L51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H52_OFFSET, \
                                    SBB_PARAM_EXT_H52_DEFAULT, \
                                    SBB_PARAM_EXT_H52_RD_MASK, "SBB_PARAM_EXT_H52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L52_OFFSET, \
                                    SBB_PARAM_EXT_L52_DEFAULT, \
                                    SBB_PARAM_EXT_L52_RD_MASK, "SBB_PARAM_EXT_L52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H53_OFFSET, \
                                    SBB_PARAM_EXT_H53_DEFAULT, \
                                    SBB_PARAM_EXT_H53_RD_MASK, "SBB_PARAM_EXT_H53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L53_OFFSET, \
                                    SBB_PARAM_EXT_L53_DEFAULT, \
                                    SBB_PARAM_EXT_L53_RD_MASK, "SBB_PARAM_EXT_L53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H54_OFFSET, \
                                    SBB_PARAM_EXT_H54_DEFAULT, \
                                    SBB_PARAM_EXT_H54_RD_MASK, "SBB_PARAM_EXT_H54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L54_OFFSET, \
                                    SBB_PARAM_EXT_L54_DEFAULT, \
                                    SBB_PARAM_EXT_L54_RD_MASK, "SBB_PARAM_EXT_L54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H55_OFFSET, \
                                    SBB_PARAM_EXT_H55_DEFAULT, \
                                    SBB_PARAM_EXT_H55_RD_MASK, "SBB_PARAM_EXT_H55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L55_OFFSET, \
                                    SBB_PARAM_EXT_L55_DEFAULT, \
                                    SBB_PARAM_EXT_L55_RD_MASK, "SBB_PARAM_EXT_L55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H56_OFFSET, \
                                    SBB_PARAM_EXT_H56_DEFAULT, \
                                    SBB_PARAM_EXT_H56_RD_MASK, "SBB_PARAM_EXT_H56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L56_OFFSET, \
                                    SBB_PARAM_EXT_L56_DEFAULT, \
                                    SBB_PARAM_EXT_L56_RD_MASK, "SBB_PARAM_EXT_L56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H57_OFFSET, \
                                    SBB_PARAM_EXT_H57_DEFAULT, \
                                    SBB_PARAM_EXT_H57_RD_MASK, "SBB_PARAM_EXT_H57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L57_OFFSET, \
                                    SBB_PARAM_EXT_L57_DEFAULT, \
                                    SBB_PARAM_EXT_L57_RD_MASK, "SBB_PARAM_EXT_L57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H58_OFFSET, \
                                    SBB_PARAM_EXT_H58_DEFAULT, \
                                    SBB_PARAM_EXT_H58_RD_MASK, "SBB_PARAM_EXT_H58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L58_OFFSET, \
                                    SBB_PARAM_EXT_L58_DEFAULT, \
                                    SBB_PARAM_EXT_L58_RD_MASK, "SBB_PARAM_EXT_L58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H59_OFFSET, \
                                    SBB_PARAM_EXT_H59_DEFAULT, \
                                    SBB_PARAM_EXT_H59_RD_MASK, "SBB_PARAM_EXT_H59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L59_OFFSET, \
                                    SBB_PARAM_EXT_L59_DEFAULT, \
                                    SBB_PARAM_EXT_L59_RD_MASK, "SBB_PARAM_EXT_L59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H60_OFFSET, \
                                    SBB_PARAM_EXT_H60_DEFAULT, \
                                    SBB_PARAM_EXT_H60_RD_MASK, "SBB_PARAM_EXT_H60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L60_OFFSET, \
                                    SBB_PARAM_EXT_L60_DEFAULT, \
                                    SBB_PARAM_EXT_L60_RD_MASK, "SBB_PARAM_EXT_L60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H61_OFFSET, \
                                    SBB_PARAM_EXT_H61_DEFAULT, \
                                    SBB_PARAM_EXT_H61_RD_MASK, "SBB_PARAM_EXT_H61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L61_OFFSET, \
                                    SBB_PARAM_EXT_L61_DEFAULT, \
                                    SBB_PARAM_EXT_L61_RD_MASK, "SBB_PARAM_EXT_L61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H62_OFFSET, \
                                    SBB_PARAM_EXT_H62_DEFAULT, \
                                    SBB_PARAM_EXT_H62_RD_MASK, "SBB_PARAM_EXT_H62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L62_OFFSET, \
                                    SBB_PARAM_EXT_L62_DEFAULT, \
                                    SBB_PARAM_EXT_L62_RD_MASK, "SBB_PARAM_EXT_L62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_H63_OFFSET, \
                                    SBB_PARAM_EXT_H63_DEFAULT, \
                                    SBB_PARAM_EXT_H63_RD_MASK, "SBB_PARAM_EXT_H63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_EXT_L63_OFFSET, \
                                    SBB_PARAM_EXT_L63_DEFAULT, \
                                    SBB_PARAM_EXT_L63_RD_MASK, "SBB_PARAM_EXT_L63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H0_OFFSET, \
                                    SBB_PARAM_H0_DEFAULT, \
                                    SBB_PARAM_H0_RD_MASK, "SBB_PARAM_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L0_OFFSET, \
                                    SBB_PARAM_L0_DEFAULT, \
                                    SBB_PARAM_L0_RD_MASK, "SBB_PARAM_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H1_OFFSET, \
                                    SBB_PARAM_H1_DEFAULT, \
                                    SBB_PARAM_H1_RD_MASK, "SBB_PARAM_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L1_OFFSET, \
                                    SBB_PARAM_L1_DEFAULT, \
                                    SBB_PARAM_L1_RD_MASK, "SBB_PARAM_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H2_OFFSET, \
                                    SBB_PARAM_H2_DEFAULT, \
                                    SBB_PARAM_H2_RD_MASK, "SBB_PARAM_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L2_OFFSET, \
                                    SBB_PARAM_L2_DEFAULT, \
                                    SBB_PARAM_L2_RD_MASK, "SBB_PARAM_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H3_OFFSET, \
                                    SBB_PARAM_H3_DEFAULT, \
                                    SBB_PARAM_H3_RD_MASK, "SBB_PARAM_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L3_OFFSET, \
                                    SBB_PARAM_L3_DEFAULT, \
                                    SBB_PARAM_L3_RD_MASK, "SBB_PARAM_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H4_OFFSET, \
                                    SBB_PARAM_H4_DEFAULT, \
                                    SBB_PARAM_H4_RD_MASK, "SBB_PARAM_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L4_OFFSET, \
                                    SBB_PARAM_L4_DEFAULT, \
                                    SBB_PARAM_L4_RD_MASK, "SBB_PARAM_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H5_OFFSET, \
                                    SBB_PARAM_H5_DEFAULT, \
                                    SBB_PARAM_H5_RD_MASK, "SBB_PARAM_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L5_OFFSET, \
                                    SBB_PARAM_L5_DEFAULT, \
                                    SBB_PARAM_L5_RD_MASK, "SBB_PARAM_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H6_OFFSET, \
                                    SBB_PARAM_H6_DEFAULT, \
                                    SBB_PARAM_H6_RD_MASK, "SBB_PARAM_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L6_OFFSET, \
                                    SBB_PARAM_L6_DEFAULT, \
                                    SBB_PARAM_L6_RD_MASK, "SBB_PARAM_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H7_OFFSET, \
                                    SBB_PARAM_H7_DEFAULT, \
                                    SBB_PARAM_H7_RD_MASK, "SBB_PARAM_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L7_OFFSET, \
                                    SBB_PARAM_L7_DEFAULT, \
                                    SBB_PARAM_L7_RD_MASK, "SBB_PARAM_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H8_OFFSET, \
                                    SBB_PARAM_H8_DEFAULT, \
                                    SBB_PARAM_H8_RD_MASK, "SBB_PARAM_H8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L8_OFFSET, \
                                    SBB_PARAM_L8_DEFAULT, \
                                    SBB_PARAM_L8_RD_MASK, "SBB_PARAM_L8_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H9_OFFSET, \
                                    SBB_PARAM_H9_DEFAULT, \
                                    SBB_PARAM_H9_RD_MASK, "SBB_PARAM_H9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L9_OFFSET, \
                                    SBB_PARAM_L9_DEFAULT, \
                                    SBB_PARAM_L9_RD_MASK, "SBB_PARAM_L9_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H10_OFFSET, \
                                    SBB_PARAM_H10_DEFAULT, \
                                    SBB_PARAM_H10_RD_MASK, "SBB_PARAM_H10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L10_OFFSET, \
                                    SBB_PARAM_L10_DEFAULT, \
                                    SBB_PARAM_L10_RD_MASK, "SBB_PARAM_L10_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H11_OFFSET, \
                                    SBB_PARAM_H11_DEFAULT, \
                                    SBB_PARAM_H11_RD_MASK, "SBB_PARAM_H11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L11_OFFSET, \
                                    SBB_PARAM_L11_DEFAULT, \
                                    SBB_PARAM_L11_RD_MASK, "SBB_PARAM_L11_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H12_OFFSET, \
                                    SBB_PARAM_H12_DEFAULT, \
                                    SBB_PARAM_H12_RD_MASK, "SBB_PARAM_H12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L12_OFFSET, \
                                    SBB_PARAM_L12_DEFAULT, \
                                    SBB_PARAM_L12_RD_MASK, "SBB_PARAM_L12_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H13_OFFSET, \
                                    SBB_PARAM_H13_DEFAULT, \
                                    SBB_PARAM_H13_RD_MASK, "SBB_PARAM_H13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L13_OFFSET, \
                                    SBB_PARAM_L13_DEFAULT, \
                                    SBB_PARAM_L13_RD_MASK, "SBB_PARAM_L13_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H14_OFFSET, \
                                    SBB_PARAM_H14_DEFAULT, \
                                    SBB_PARAM_H14_RD_MASK, "SBB_PARAM_H14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L14_OFFSET, \
                                    SBB_PARAM_L14_DEFAULT, \
                                    SBB_PARAM_L14_RD_MASK, "SBB_PARAM_L14_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H15_OFFSET, \
                                    SBB_PARAM_H15_DEFAULT, \
                                    SBB_PARAM_H15_RD_MASK, "SBB_PARAM_H15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L15_OFFSET, \
                                    SBB_PARAM_L15_DEFAULT, \
                                    SBB_PARAM_L15_RD_MASK, "SBB_PARAM_L15_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H16_OFFSET, \
                                    SBB_PARAM_H16_DEFAULT, \
                                    SBB_PARAM_H16_RD_MASK, "SBB_PARAM_H16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L16_OFFSET, \
                                    SBB_PARAM_L16_DEFAULT, \
                                    SBB_PARAM_L16_RD_MASK, "SBB_PARAM_L16_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H17_OFFSET, \
                                    SBB_PARAM_H17_DEFAULT, \
                                    SBB_PARAM_H17_RD_MASK, "SBB_PARAM_H17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L17_OFFSET, \
                                    SBB_PARAM_L17_DEFAULT, \
                                    SBB_PARAM_L17_RD_MASK, "SBB_PARAM_L17_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H18_OFFSET, \
                                    SBB_PARAM_H18_DEFAULT, \
                                    SBB_PARAM_H18_RD_MASK, "SBB_PARAM_H18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L18_OFFSET, \
                                    SBB_PARAM_L18_DEFAULT, \
                                    SBB_PARAM_L18_RD_MASK, "SBB_PARAM_L18_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H19_OFFSET, \
                                    SBB_PARAM_H19_DEFAULT, \
                                    SBB_PARAM_H19_RD_MASK, "SBB_PARAM_H19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L19_OFFSET, \
                                    SBB_PARAM_L19_DEFAULT, \
                                    SBB_PARAM_L19_RD_MASK, "SBB_PARAM_L19_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H20_OFFSET, \
                                    SBB_PARAM_H20_DEFAULT, \
                                    SBB_PARAM_H20_RD_MASK, "SBB_PARAM_H20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L20_OFFSET, \
                                    SBB_PARAM_L20_DEFAULT, \
                                    SBB_PARAM_L20_RD_MASK, "SBB_PARAM_L20_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H21_OFFSET, \
                                    SBB_PARAM_H21_DEFAULT, \
                                    SBB_PARAM_H21_RD_MASK, "SBB_PARAM_H21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L21_OFFSET, \
                                    SBB_PARAM_L21_DEFAULT, \
                                    SBB_PARAM_L21_RD_MASK, "SBB_PARAM_L21_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H22_OFFSET, \
                                    SBB_PARAM_H22_DEFAULT, \
                                    SBB_PARAM_H22_RD_MASK, "SBB_PARAM_H22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L22_OFFSET, \
                                    SBB_PARAM_L22_DEFAULT, \
                                    SBB_PARAM_L22_RD_MASK, "SBB_PARAM_L22_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H23_OFFSET, \
                                    SBB_PARAM_H23_DEFAULT, \
                                    SBB_PARAM_H23_RD_MASK, "SBB_PARAM_H23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L23_OFFSET, \
                                    SBB_PARAM_L23_DEFAULT, \
                                    SBB_PARAM_L23_RD_MASK, "SBB_PARAM_L23_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H24_OFFSET, \
                                    SBB_PARAM_H24_DEFAULT, \
                                    SBB_PARAM_H24_RD_MASK, "SBB_PARAM_H24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L24_OFFSET, \
                                    SBB_PARAM_L24_DEFAULT, \
                                    SBB_PARAM_L24_RD_MASK, "SBB_PARAM_L24_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H25_OFFSET, \
                                    SBB_PARAM_H25_DEFAULT, \
                                    SBB_PARAM_H25_RD_MASK, "SBB_PARAM_H25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L25_OFFSET, \
                                    SBB_PARAM_L25_DEFAULT, \
                                    SBB_PARAM_L25_RD_MASK, "SBB_PARAM_L25_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H26_OFFSET, \
                                    SBB_PARAM_H26_DEFAULT, \
                                    SBB_PARAM_H26_RD_MASK, "SBB_PARAM_H26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L26_OFFSET, \
                                    SBB_PARAM_L26_DEFAULT, \
                                    SBB_PARAM_L26_RD_MASK, "SBB_PARAM_L26_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H27_OFFSET, \
                                    SBB_PARAM_H27_DEFAULT, \
                                    SBB_PARAM_H27_RD_MASK, "SBB_PARAM_H27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L27_OFFSET, \
                                    SBB_PARAM_L27_DEFAULT, \
                                    SBB_PARAM_L27_RD_MASK, "SBB_PARAM_L27_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H28_OFFSET, \
                                    SBB_PARAM_H28_DEFAULT, \
                                    SBB_PARAM_H28_RD_MASK, "SBB_PARAM_H28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L28_OFFSET, \
                                    SBB_PARAM_L28_DEFAULT, \
                                    SBB_PARAM_L28_RD_MASK, "SBB_PARAM_L28_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H29_OFFSET, \
                                    SBB_PARAM_H29_DEFAULT, \
                                    SBB_PARAM_H29_RD_MASK, "SBB_PARAM_H29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L29_OFFSET, \
                                    SBB_PARAM_L29_DEFAULT, \
                                    SBB_PARAM_L29_RD_MASK, "SBB_PARAM_L29_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H30_OFFSET, \
                                    SBB_PARAM_H30_DEFAULT, \
                                    SBB_PARAM_H30_RD_MASK, "SBB_PARAM_H30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L30_OFFSET, \
                                    SBB_PARAM_L30_DEFAULT, \
                                    SBB_PARAM_L30_RD_MASK, "SBB_PARAM_L30_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H31_OFFSET, \
                                    SBB_PARAM_H31_DEFAULT, \
                                    SBB_PARAM_H31_RD_MASK, "SBB_PARAM_H31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L31_OFFSET, \
                                    SBB_PARAM_L31_DEFAULT, \
                                    SBB_PARAM_L31_RD_MASK, "SBB_PARAM_L31_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H32_OFFSET, \
                                    SBB_PARAM_H32_DEFAULT, \
                                    SBB_PARAM_H32_RD_MASK, "SBB_PARAM_H32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L32_OFFSET, \
                                    SBB_PARAM_L32_DEFAULT, \
                                    SBB_PARAM_L32_RD_MASK, "SBB_PARAM_L32_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H33_OFFSET, \
                                    SBB_PARAM_H33_DEFAULT, \
                                    SBB_PARAM_H33_RD_MASK, "SBB_PARAM_H33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L33_OFFSET, \
                                    SBB_PARAM_L33_DEFAULT, \
                                    SBB_PARAM_L33_RD_MASK, "SBB_PARAM_L33_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H34_OFFSET, \
                                    SBB_PARAM_H34_DEFAULT, \
                                    SBB_PARAM_H34_RD_MASK, "SBB_PARAM_H34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L34_OFFSET, \
                                    SBB_PARAM_L34_DEFAULT, \
                                    SBB_PARAM_L34_RD_MASK, "SBB_PARAM_L34_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H35_OFFSET, \
                                    SBB_PARAM_H35_DEFAULT, \
                                    SBB_PARAM_H35_RD_MASK, "SBB_PARAM_H35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L35_OFFSET, \
                                    SBB_PARAM_L35_DEFAULT, \
                                    SBB_PARAM_L35_RD_MASK, "SBB_PARAM_L35_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H36_OFFSET, \
                                    SBB_PARAM_H36_DEFAULT, \
                                    SBB_PARAM_H36_RD_MASK, "SBB_PARAM_H36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L36_OFFSET, \
                                    SBB_PARAM_L36_DEFAULT, \
                                    SBB_PARAM_L36_RD_MASK, "SBB_PARAM_L36_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H37_OFFSET, \
                                    SBB_PARAM_H37_DEFAULT, \
                                    SBB_PARAM_H37_RD_MASK, "SBB_PARAM_H37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L37_OFFSET, \
                                    SBB_PARAM_L37_DEFAULT, \
                                    SBB_PARAM_L37_RD_MASK, "SBB_PARAM_L37_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H38_OFFSET, \
                                    SBB_PARAM_H38_DEFAULT, \
                                    SBB_PARAM_H38_RD_MASK, "SBB_PARAM_H38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L38_OFFSET, \
                                    SBB_PARAM_L38_DEFAULT, \
                                    SBB_PARAM_L38_RD_MASK, "SBB_PARAM_L38_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H39_OFFSET, \
                                    SBB_PARAM_H39_DEFAULT, \
                                    SBB_PARAM_H39_RD_MASK, "SBB_PARAM_H39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L39_OFFSET, \
                                    SBB_PARAM_L39_DEFAULT, \
                                    SBB_PARAM_L39_RD_MASK, "SBB_PARAM_L39_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H40_OFFSET, \
                                    SBB_PARAM_H40_DEFAULT, \
                                    SBB_PARAM_H40_RD_MASK, "SBB_PARAM_H40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L40_OFFSET, \
                                    SBB_PARAM_L40_DEFAULT, \
                                    SBB_PARAM_L40_RD_MASK, "SBB_PARAM_L40_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H41_OFFSET, \
                                    SBB_PARAM_H41_DEFAULT, \
                                    SBB_PARAM_H41_RD_MASK, "SBB_PARAM_H41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L41_OFFSET, \
                                    SBB_PARAM_L41_DEFAULT, \
                                    SBB_PARAM_L41_RD_MASK, "SBB_PARAM_L41_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H42_OFFSET, \
                                    SBB_PARAM_H42_DEFAULT, \
                                    SBB_PARAM_H42_RD_MASK, "SBB_PARAM_H42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L42_OFFSET, \
                                    SBB_PARAM_L42_DEFAULT, \
                                    SBB_PARAM_L42_RD_MASK, "SBB_PARAM_L42_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H43_OFFSET, \
                                    SBB_PARAM_H43_DEFAULT, \
                                    SBB_PARAM_H43_RD_MASK, "SBB_PARAM_H43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L43_OFFSET, \
                                    SBB_PARAM_L43_DEFAULT, \
                                    SBB_PARAM_L43_RD_MASK, "SBB_PARAM_L43_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H44_OFFSET, \
                                    SBB_PARAM_H44_DEFAULT, \
                                    SBB_PARAM_H44_RD_MASK, "SBB_PARAM_H44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L44_OFFSET, \
                                    SBB_PARAM_L44_DEFAULT, \
                                    SBB_PARAM_L44_RD_MASK, "SBB_PARAM_L44_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H45_OFFSET, \
                                    SBB_PARAM_H45_DEFAULT, \
                                    SBB_PARAM_H45_RD_MASK, "SBB_PARAM_H45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L45_OFFSET, \
                                    SBB_PARAM_L45_DEFAULT, \
                                    SBB_PARAM_L45_RD_MASK, "SBB_PARAM_L45_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H46_OFFSET, \
                                    SBB_PARAM_H46_DEFAULT, \
                                    SBB_PARAM_H46_RD_MASK, "SBB_PARAM_H46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L46_OFFSET, \
                                    SBB_PARAM_L46_DEFAULT, \
                                    SBB_PARAM_L46_RD_MASK, "SBB_PARAM_L46_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H47_OFFSET, \
                                    SBB_PARAM_H47_DEFAULT, \
                                    SBB_PARAM_H47_RD_MASK, "SBB_PARAM_H47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L47_OFFSET, \
                                    SBB_PARAM_L47_DEFAULT, \
                                    SBB_PARAM_L47_RD_MASK, "SBB_PARAM_L47_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H48_OFFSET, \
                                    SBB_PARAM_H48_DEFAULT, \
                                    SBB_PARAM_H48_RD_MASK, "SBB_PARAM_H48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L48_OFFSET, \
                                    SBB_PARAM_L48_DEFAULT, \
                                    SBB_PARAM_L48_RD_MASK, "SBB_PARAM_L48_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H49_OFFSET, \
                                    SBB_PARAM_H49_DEFAULT, \
                                    SBB_PARAM_H49_RD_MASK, "SBB_PARAM_H49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L49_OFFSET, \
                                    SBB_PARAM_L49_DEFAULT, \
                                    SBB_PARAM_L49_RD_MASK, "SBB_PARAM_L49_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H50_OFFSET, \
                                    SBB_PARAM_H50_DEFAULT, \
                                    SBB_PARAM_H50_RD_MASK, "SBB_PARAM_H50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L50_OFFSET, \
                                    SBB_PARAM_L50_DEFAULT, \
                                    SBB_PARAM_L50_RD_MASK, "SBB_PARAM_L50_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H51_OFFSET, \
                                    SBB_PARAM_H51_DEFAULT, \
                                    SBB_PARAM_H51_RD_MASK, "SBB_PARAM_H51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L51_OFFSET, \
                                    SBB_PARAM_L51_DEFAULT, \
                                    SBB_PARAM_L51_RD_MASK, "SBB_PARAM_L51_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H52_OFFSET, \
                                    SBB_PARAM_H52_DEFAULT, \
                                    SBB_PARAM_H52_RD_MASK, "SBB_PARAM_H52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L52_OFFSET, \
                                    SBB_PARAM_L52_DEFAULT, \
                                    SBB_PARAM_L52_RD_MASK, "SBB_PARAM_L52_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H53_OFFSET, \
                                    SBB_PARAM_H53_DEFAULT, \
                                    SBB_PARAM_H53_RD_MASK, "SBB_PARAM_H53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L53_OFFSET, \
                                    SBB_PARAM_L53_DEFAULT, \
                                    SBB_PARAM_L53_RD_MASK, "SBB_PARAM_L53_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H54_OFFSET, \
                                    SBB_PARAM_H54_DEFAULT, \
                                    SBB_PARAM_H54_RD_MASK, "SBB_PARAM_H54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L54_OFFSET, \
                                    SBB_PARAM_L54_DEFAULT, \
                                    SBB_PARAM_L54_RD_MASK, "SBB_PARAM_L54_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H55_OFFSET, \
                                    SBB_PARAM_H55_DEFAULT, \
                                    SBB_PARAM_H55_RD_MASK, "SBB_PARAM_H55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L55_OFFSET, \
                                    SBB_PARAM_L55_DEFAULT, \
                                    SBB_PARAM_L55_RD_MASK, "SBB_PARAM_L55_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H56_OFFSET, \
                                    SBB_PARAM_H56_DEFAULT, \
                                    SBB_PARAM_H56_RD_MASK, "SBB_PARAM_H56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L56_OFFSET, \
                                    SBB_PARAM_L56_DEFAULT, \
                                    SBB_PARAM_L56_RD_MASK, "SBB_PARAM_L56_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H57_OFFSET, \
                                    SBB_PARAM_H57_DEFAULT, \
                                    SBB_PARAM_H57_RD_MASK, "SBB_PARAM_H57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L57_OFFSET, \
                                    SBB_PARAM_L57_DEFAULT, \
                                    SBB_PARAM_L57_RD_MASK, "SBB_PARAM_L57_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H58_OFFSET, \
                                    SBB_PARAM_H58_DEFAULT, \
                                    SBB_PARAM_H58_RD_MASK, "SBB_PARAM_H58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L58_OFFSET, \
                                    SBB_PARAM_L58_DEFAULT, \
                                    SBB_PARAM_L58_RD_MASK, "SBB_PARAM_L58_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H59_OFFSET, \
                                    SBB_PARAM_H59_DEFAULT, \
                                    SBB_PARAM_H59_RD_MASK, "SBB_PARAM_H59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L59_OFFSET, \
                                    SBB_PARAM_L59_DEFAULT, \
                                    SBB_PARAM_L59_RD_MASK, "SBB_PARAM_L59_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H60_OFFSET, \
                                    SBB_PARAM_H60_DEFAULT, \
                                    SBB_PARAM_H60_RD_MASK, "SBB_PARAM_H60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L60_OFFSET, \
                                    SBB_PARAM_L60_DEFAULT, \
                                    SBB_PARAM_L60_RD_MASK, "SBB_PARAM_L60_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H61_OFFSET, \
                                    SBB_PARAM_H61_DEFAULT, \
                                    SBB_PARAM_H61_RD_MASK, "SBB_PARAM_H61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L61_OFFSET, \
                                    SBB_PARAM_L61_DEFAULT, \
                                    SBB_PARAM_L61_RD_MASK, "SBB_PARAM_L61_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H62_OFFSET, \
                                    SBB_PARAM_H62_DEFAULT, \
                                    SBB_PARAM_H62_RD_MASK, "SBB_PARAM_H62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L62_OFFSET, \
                                    SBB_PARAM_L62_DEFAULT, \
                                    SBB_PARAM_L62_RD_MASK, "SBB_PARAM_L62_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H63_OFFSET, \
                                    SBB_PARAM_H63_DEFAULT, \
                                    SBB_PARAM_H63_RD_MASK, "SBB_PARAM_H63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L63_OFFSET, \
                                    SBB_PARAM_L63_DEFAULT, \
                                    SBB_PARAM_L63_RD_MASK, "SBB_PARAM_L63_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H64_OFFSET, \
                                    SBB_PARAM_H64_DEFAULT, \
                                    SBB_PARAM_H64_RD_MASK, "SBB_PARAM_H64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L64_OFFSET, \
                                    SBB_PARAM_L64_DEFAULT, \
                                    SBB_PARAM_L64_RD_MASK, "SBB_PARAM_L64_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H65_OFFSET, \
                                    SBB_PARAM_H65_DEFAULT, \
                                    SBB_PARAM_H65_RD_MASK, "SBB_PARAM_H65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L65_OFFSET, \
                                    SBB_PARAM_L65_DEFAULT, \
                                    SBB_PARAM_L65_RD_MASK, "SBB_PARAM_L65_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H66_OFFSET, \
                                    SBB_PARAM_H66_DEFAULT, \
                                    SBB_PARAM_H66_RD_MASK, "SBB_PARAM_H66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L66_OFFSET, \
                                    SBB_PARAM_L66_DEFAULT, \
                                    SBB_PARAM_L66_RD_MASK, "SBB_PARAM_L66_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H67_OFFSET, \
                                    SBB_PARAM_H67_DEFAULT, \
                                    SBB_PARAM_H67_RD_MASK, "SBB_PARAM_H67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L67_OFFSET, \
                                    SBB_PARAM_L67_DEFAULT, \
                                    SBB_PARAM_L67_RD_MASK, "SBB_PARAM_L67_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H68_OFFSET, \
                                    SBB_PARAM_H68_DEFAULT, \
                                    SBB_PARAM_H68_RD_MASK, "SBB_PARAM_H68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L68_OFFSET, \
                                    SBB_PARAM_L68_DEFAULT, \
                                    SBB_PARAM_L68_RD_MASK, "SBB_PARAM_L68_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H69_OFFSET, \
                                    SBB_PARAM_H69_DEFAULT, \
                                    SBB_PARAM_H69_RD_MASK, "SBB_PARAM_H69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L69_OFFSET, \
                                    SBB_PARAM_L69_DEFAULT, \
                                    SBB_PARAM_L69_RD_MASK, "SBB_PARAM_L69_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H70_OFFSET, \
                                    SBB_PARAM_H70_DEFAULT, \
                                    SBB_PARAM_H70_RD_MASK, "SBB_PARAM_H70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L70_OFFSET, \
                                    SBB_PARAM_L70_DEFAULT, \
                                    SBB_PARAM_L70_RD_MASK, "SBB_PARAM_L70_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H71_OFFSET, \
                                    SBB_PARAM_H71_DEFAULT, \
                                    SBB_PARAM_H71_RD_MASK, "SBB_PARAM_H71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L71_OFFSET, \
                                    SBB_PARAM_L71_DEFAULT, \
                                    SBB_PARAM_L71_RD_MASK, "SBB_PARAM_L71_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H72_OFFSET, \
                                    SBB_PARAM_H72_DEFAULT, \
                                    SBB_PARAM_H72_RD_MASK, "SBB_PARAM_H72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L72_OFFSET, \
                                    SBB_PARAM_L72_DEFAULT, \
                                    SBB_PARAM_L72_RD_MASK, "SBB_PARAM_L72_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H73_OFFSET, \
                                    SBB_PARAM_H73_DEFAULT, \
                                    SBB_PARAM_H73_RD_MASK, "SBB_PARAM_H73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L73_OFFSET, \
                                    SBB_PARAM_L73_DEFAULT, \
                                    SBB_PARAM_L73_RD_MASK, "SBB_PARAM_L73_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H74_OFFSET, \
                                    SBB_PARAM_H74_DEFAULT, \
                                    SBB_PARAM_H74_RD_MASK, "SBB_PARAM_H74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L74_OFFSET, \
                                    SBB_PARAM_L74_DEFAULT, \
                                    SBB_PARAM_L74_RD_MASK, "SBB_PARAM_L74_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H75_OFFSET, \
                                    SBB_PARAM_H75_DEFAULT, \
                                    SBB_PARAM_H75_RD_MASK, "SBB_PARAM_H75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L75_OFFSET, \
                                    SBB_PARAM_L75_DEFAULT, \
                                    SBB_PARAM_L75_RD_MASK, "SBB_PARAM_L75_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H76_OFFSET, \
                                    SBB_PARAM_H76_DEFAULT, \
                                    SBB_PARAM_H76_RD_MASK, "SBB_PARAM_H76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L76_OFFSET, \
                                    SBB_PARAM_L76_DEFAULT, \
                                    SBB_PARAM_L76_RD_MASK, "SBB_PARAM_L76_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H77_OFFSET, \
                                    SBB_PARAM_H77_DEFAULT, \
                                    SBB_PARAM_H77_RD_MASK, "SBB_PARAM_H77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L77_OFFSET, \
                                    SBB_PARAM_L77_DEFAULT, \
                                    SBB_PARAM_L77_RD_MASK, "SBB_PARAM_L77_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H78_OFFSET, \
                                    SBB_PARAM_H78_DEFAULT, \
                                    SBB_PARAM_H78_RD_MASK, "SBB_PARAM_H78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L78_OFFSET, \
                                    SBB_PARAM_L78_DEFAULT, \
                                    SBB_PARAM_L78_RD_MASK, "SBB_PARAM_L78_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H79_OFFSET, \
                                    SBB_PARAM_H79_DEFAULT, \
                                    SBB_PARAM_H79_RD_MASK, "SBB_PARAM_H79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L79_OFFSET, \
                                    SBB_PARAM_L79_DEFAULT, \
                                    SBB_PARAM_L79_RD_MASK, "SBB_PARAM_L79_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H80_OFFSET, \
                                    SBB_PARAM_H80_DEFAULT, \
                                    SBB_PARAM_H80_RD_MASK, "SBB_PARAM_H80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L80_OFFSET, \
                                    SBB_PARAM_L80_DEFAULT, \
                                    SBB_PARAM_L80_RD_MASK, "SBB_PARAM_L80_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H81_OFFSET, \
                                    SBB_PARAM_H81_DEFAULT, \
                                    SBB_PARAM_H81_RD_MASK, "SBB_PARAM_H81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L81_OFFSET, \
                                    SBB_PARAM_L81_DEFAULT, \
                                    SBB_PARAM_L81_RD_MASK, "SBB_PARAM_L81_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H82_OFFSET, \
                                    SBB_PARAM_H82_DEFAULT, \
                                    SBB_PARAM_H82_RD_MASK, "SBB_PARAM_H82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L82_OFFSET, \
                                    SBB_PARAM_L82_DEFAULT, \
                                    SBB_PARAM_L82_RD_MASK, "SBB_PARAM_L82_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H83_OFFSET, \
                                    SBB_PARAM_H83_DEFAULT, \
                                    SBB_PARAM_H83_RD_MASK, "SBB_PARAM_H83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L83_OFFSET, \
                                    SBB_PARAM_L83_DEFAULT, \
                                    SBB_PARAM_L83_RD_MASK, "SBB_PARAM_L83_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H84_OFFSET, \
                                    SBB_PARAM_H84_DEFAULT, \
                                    SBB_PARAM_H84_RD_MASK, "SBB_PARAM_H84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L84_OFFSET, \
                                    SBB_PARAM_L84_DEFAULT, \
                                    SBB_PARAM_L84_RD_MASK, "SBB_PARAM_L84_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H85_OFFSET, \
                                    SBB_PARAM_H85_DEFAULT, \
                                    SBB_PARAM_H85_RD_MASK, "SBB_PARAM_H85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L85_OFFSET, \
                                    SBB_PARAM_L85_DEFAULT, \
                                    SBB_PARAM_L85_RD_MASK, "SBB_PARAM_L85_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H86_OFFSET, \
                                    SBB_PARAM_H86_DEFAULT, \
                                    SBB_PARAM_H86_RD_MASK, "SBB_PARAM_H86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L86_OFFSET, \
                                    SBB_PARAM_L86_DEFAULT, \
                                    SBB_PARAM_L86_RD_MASK, "SBB_PARAM_L86_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H87_OFFSET, \
                                    SBB_PARAM_H87_DEFAULT, \
                                    SBB_PARAM_H87_RD_MASK, "SBB_PARAM_H87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L87_OFFSET, \
                                    SBB_PARAM_L87_DEFAULT, \
                                    SBB_PARAM_L87_RD_MASK, "SBB_PARAM_L87_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H88_OFFSET, \
                                    SBB_PARAM_H88_DEFAULT, \
                                    SBB_PARAM_H88_RD_MASK, "SBB_PARAM_H88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L88_OFFSET, \
                                    SBB_PARAM_L88_DEFAULT, \
                                    SBB_PARAM_L88_RD_MASK, "SBB_PARAM_L88_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H89_OFFSET, \
                                    SBB_PARAM_H89_DEFAULT, \
                                    SBB_PARAM_H89_RD_MASK, "SBB_PARAM_H89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L89_OFFSET, \
                                    SBB_PARAM_L89_DEFAULT, \
                                    SBB_PARAM_L89_RD_MASK, "SBB_PARAM_L89_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H90_OFFSET, \
                                    SBB_PARAM_H90_DEFAULT, \
                                    SBB_PARAM_H90_RD_MASK, "SBB_PARAM_H90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L90_OFFSET, \
                                    SBB_PARAM_L90_DEFAULT, \
                                    SBB_PARAM_L90_RD_MASK, "SBB_PARAM_L90_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H91_OFFSET, \
                                    SBB_PARAM_H91_DEFAULT, \
                                    SBB_PARAM_H91_RD_MASK, "SBB_PARAM_H91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L91_OFFSET, \
                                    SBB_PARAM_L91_DEFAULT, \
                                    SBB_PARAM_L91_RD_MASK, "SBB_PARAM_L91_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H92_OFFSET, \
                                    SBB_PARAM_H92_DEFAULT, \
                                    SBB_PARAM_H92_RD_MASK, "SBB_PARAM_H92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L92_OFFSET, \
                                    SBB_PARAM_L92_DEFAULT, \
                                    SBB_PARAM_L92_RD_MASK, "SBB_PARAM_L92_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H93_OFFSET, \
                                    SBB_PARAM_H93_DEFAULT, \
                                    SBB_PARAM_H93_RD_MASK, "SBB_PARAM_H93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L93_OFFSET, \
                                    SBB_PARAM_L93_DEFAULT, \
                                    SBB_PARAM_L93_RD_MASK, "SBB_PARAM_L93_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H94_OFFSET, \
                                    SBB_PARAM_H94_DEFAULT, \
                                    SBB_PARAM_H94_RD_MASK, "SBB_PARAM_H94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L94_OFFSET, \
                                    SBB_PARAM_L94_DEFAULT, \
                                    SBB_PARAM_L94_RD_MASK, "SBB_PARAM_L94_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H95_OFFSET, \
                                    SBB_PARAM_H95_DEFAULT, \
                                    SBB_PARAM_H95_RD_MASK, "SBB_PARAM_H95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L95_OFFSET, \
                                    SBB_PARAM_L95_DEFAULT, \
                                    SBB_PARAM_L95_RD_MASK, "SBB_PARAM_L95_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H96_OFFSET, \
                                    SBB_PARAM_H96_DEFAULT, \
                                    SBB_PARAM_H96_RD_MASK, "SBB_PARAM_H96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L96_OFFSET, \
                                    SBB_PARAM_L96_DEFAULT, \
                                    SBB_PARAM_L96_RD_MASK, "SBB_PARAM_L96_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H97_OFFSET, \
                                    SBB_PARAM_H97_DEFAULT, \
                                    SBB_PARAM_H97_RD_MASK, "SBB_PARAM_H97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L97_OFFSET, \
                                    SBB_PARAM_L97_DEFAULT, \
                                    SBB_PARAM_L97_RD_MASK, "SBB_PARAM_L97_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H98_OFFSET, \
                                    SBB_PARAM_H98_DEFAULT, \
                                    SBB_PARAM_H98_RD_MASK, "SBB_PARAM_H98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L98_OFFSET, \
                                    SBB_PARAM_L98_DEFAULT, \
                                    SBB_PARAM_L98_RD_MASK, "SBB_PARAM_L98_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H99_OFFSET, \
                                    SBB_PARAM_H99_DEFAULT, \
                                    SBB_PARAM_H99_RD_MASK, "SBB_PARAM_H99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L99_OFFSET, \
                                    SBB_PARAM_L99_DEFAULT, \
                                    SBB_PARAM_L99_RD_MASK, "SBB_PARAM_L99_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H100_OFFSET, \
                                    SBB_PARAM_H100_DEFAULT, \
                                    SBB_PARAM_H100_RD_MASK, "SBB_PARAM_H100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L100_OFFSET, \
                                    SBB_PARAM_L100_DEFAULT, \
                                    SBB_PARAM_L100_RD_MASK, "SBB_PARAM_L100_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H101_OFFSET, \
                                    SBB_PARAM_H101_DEFAULT, \
                                    SBB_PARAM_H101_RD_MASK, "SBB_PARAM_H101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L101_OFFSET, \
                                    SBB_PARAM_L101_DEFAULT, \
                                    SBB_PARAM_L101_RD_MASK, "SBB_PARAM_L101_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H102_OFFSET, \
                                    SBB_PARAM_H102_DEFAULT, \
                                    SBB_PARAM_H102_RD_MASK, "SBB_PARAM_H102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L102_OFFSET, \
                                    SBB_PARAM_L102_DEFAULT, \
                                    SBB_PARAM_L102_RD_MASK, "SBB_PARAM_L102_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H103_OFFSET, \
                                    SBB_PARAM_H103_DEFAULT, \
                                    SBB_PARAM_H103_RD_MASK, "SBB_PARAM_H103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L103_OFFSET, \
                                    SBB_PARAM_L103_DEFAULT, \
                                    SBB_PARAM_L103_RD_MASK, "SBB_PARAM_L103_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H104_OFFSET, \
                                    SBB_PARAM_H104_DEFAULT, \
                                    SBB_PARAM_H104_RD_MASK, "SBB_PARAM_H104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L104_OFFSET, \
                                    SBB_PARAM_L104_DEFAULT, \
                                    SBB_PARAM_L104_RD_MASK, "SBB_PARAM_L104_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H105_OFFSET, \
                                    SBB_PARAM_H105_DEFAULT, \
                                    SBB_PARAM_H105_RD_MASK, "SBB_PARAM_H105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L105_OFFSET, \
                                    SBB_PARAM_L105_DEFAULT, \
                                    SBB_PARAM_L105_RD_MASK, "SBB_PARAM_L105_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H106_OFFSET, \
                                    SBB_PARAM_H106_DEFAULT, \
                                    SBB_PARAM_H106_RD_MASK, "SBB_PARAM_H106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L106_OFFSET, \
                                    SBB_PARAM_L106_DEFAULT, \
                                    SBB_PARAM_L106_RD_MASK, "SBB_PARAM_L106_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H107_OFFSET, \
                                    SBB_PARAM_H107_DEFAULT, \
                                    SBB_PARAM_H107_RD_MASK, "SBB_PARAM_H107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L107_OFFSET, \
                                    SBB_PARAM_L107_DEFAULT, \
                                    SBB_PARAM_L107_RD_MASK, "SBB_PARAM_L107_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H108_OFFSET, \
                                    SBB_PARAM_H108_DEFAULT, \
                                    SBB_PARAM_H108_RD_MASK, "SBB_PARAM_H108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L108_OFFSET, \
                                    SBB_PARAM_L108_DEFAULT, \
                                    SBB_PARAM_L108_RD_MASK, "SBB_PARAM_L108_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H109_OFFSET, \
                                    SBB_PARAM_H109_DEFAULT, \
                                    SBB_PARAM_H109_RD_MASK, "SBB_PARAM_H109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L109_OFFSET, \
                                    SBB_PARAM_L109_DEFAULT, \
                                    SBB_PARAM_L109_RD_MASK, "SBB_PARAM_L109_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H110_OFFSET, \
                                    SBB_PARAM_H110_DEFAULT, \
                                    SBB_PARAM_H110_RD_MASK, "SBB_PARAM_H110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L110_OFFSET, \
                                    SBB_PARAM_L110_DEFAULT, \
                                    SBB_PARAM_L110_RD_MASK, "SBB_PARAM_L110_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H111_OFFSET, \
                                    SBB_PARAM_H111_DEFAULT, \
                                    SBB_PARAM_H111_RD_MASK, "SBB_PARAM_H111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L111_OFFSET, \
                                    SBB_PARAM_L111_DEFAULT, \
                                    SBB_PARAM_L111_RD_MASK, "SBB_PARAM_L111_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H112_OFFSET, \
                                    SBB_PARAM_H112_DEFAULT, \
                                    SBB_PARAM_H112_RD_MASK, "SBB_PARAM_H112_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L112_OFFSET, \
                                    SBB_PARAM_L112_DEFAULT, \
                                    SBB_PARAM_L112_RD_MASK, "SBB_PARAM_L112_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H113_OFFSET, \
                                    SBB_PARAM_H113_DEFAULT, \
                                    SBB_PARAM_H113_RD_MASK, "SBB_PARAM_H113_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L113_OFFSET, \
                                    SBB_PARAM_L113_DEFAULT, \
                                    SBB_PARAM_L113_RD_MASK, "SBB_PARAM_L113_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H114_OFFSET, \
                                    SBB_PARAM_H114_DEFAULT, \
                                    SBB_PARAM_H114_RD_MASK, "SBB_PARAM_H114_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L114_OFFSET, \
                                    SBB_PARAM_L114_DEFAULT, \
                                    SBB_PARAM_L114_RD_MASK, "SBB_PARAM_L114_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H115_OFFSET, \
                                    SBB_PARAM_H115_DEFAULT, \
                                    SBB_PARAM_H115_RD_MASK, "SBB_PARAM_H115_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L115_OFFSET, \
                                    SBB_PARAM_L115_DEFAULT, \
                                    SBB_PARAM_L115_RD_MASK, "SBB_PARAM_L115_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H116_OFFSET, \
                                    SBB_PARAM_H116_DEFAULT, \
                                    SBB_PARAM_H116_RD_MASK, "SBB_PARAM_H116_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L116_OFFSET, \
                                    SBB_PARAM_L116_DEFAULT, \
                                    SBB_PARAM_L116_RD_MASK, "SBB_PARAM_L116_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H117_OFFSET, \
                                    SBB_PARAM_H117_DEFAULT, \
                                    SBB_PARAM_H117_RD_MASK, "SBB_PARAM_H117_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L117_OFFSET, \
                                    SBB_PARAM_L117_DEFAULT, \
                                    SBB_PARAM_L117_RD_MASK, "SBB_PARAM_L117_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H118_OFFSET, \
                                    SBB_PARAM_H118_DEFAULT, \
                                    SBB_PARAM_H118_RD_MASK, "SBB_PARAM_H118_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L118_OFFSET, \
                                    SBB_PARAM_L118_DEFAULT, \
                                    SBB_PARAM_L118_RD_MASK, "SBB_PARAM_L118_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H119_OFFSET, \
                                    SBB_PARAM_H119_DEFAULT, \
                                    SBB_PARAM_H119_RD_MASK, "SBB_PARAM_H119_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L119_OFFSET, \
                                    SBB_PARAM_L119_DEFAULT, \
                                    SBB_PARAM_L119_RD_MASK, "SBB_PARAM_L119_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H120_OFFSET, \
                                    SBB_PARAM_H120_DEFAULT, \
                                    SBB_PARAM_H120_RD_MASK, "SBB_PARAM_H120_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L120_OFFSET, \
                                    SBB_PARAM_L120_DEFAULT, \
                                    SBB_PARAM_L120_RD_MASK, "SBB_PARAM_L120_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H121_OFFSET, \
                                    SBB_PARAM_H121_DEFAULT, \
                                    SBB_PARAM_H121_RD_MASK, "SBB_PARAM_H121_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L121_OFFSET, \
                                    SBB_PARAM_L121_DEFAULT, \
                                    SBB_PARAM_L121_RD_MASK, "SBB_PARAM_L121_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H122_OFFSET, \
                                    SBB_PARAM_H122_DEFAULT, \
                                    SBB_PARAM_H122_RD_MASK, "SBB_PARAM_H122_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L122_OFFSET, \
                                    SBB_PARAM_L122_DEFAULT, \
                                    SBB_PARAM_L122_RD_MASK, "SBB_PARAM_L122_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H123_OFFSET, \
                                    SBB_PARAM_H123_DEFAULT, \
                                    SBB_PARAM_H123_RD_MASK, "SBB_PARAM_H123_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L123_OFFSET, \
                                    SBB_PARAM_L123_DEFAULT, \
                                    SBB_PARAM_L123_RD_MASK, "SBB_PARAM_L123_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H124_OFFSET, \
                                    SBB_PARAM_H124_DEFAULT, \
                                    SBB_PARAM_H124_RD_MASK, "SBB_PARAM_H124_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L124_OFFSET, \
                                    SBB_PARAM_L124_DEFAULT, \
                                    SBB_PARAM_L124_RD_MASK, "SBB_PARAM_L124_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H125_OFFSET, \
                                    SBB_PARAM_H125_DEFAULT, \
                                    SBB_PARAM_H125_RD_MASK, "SBB_PARAM_H125_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L125_OFFSET, \
                                    SBB_PARAM_L125_DEFAULT, \
                                    SBB_PARAM_L125_RD_MASK, "SBB_PARAM_L125_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H126_OFFSET, \
                                    SBB_PARAM_H126_DEFAULT, \
                                    SBB_PARAM_H126_RD_MASK, "SBB_PARAM_H126_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L126_OFFSET, \
                                    SBB_PARAM_L126_DEFAULT, \
                                    SBB_PARAM_L126_RD_MASK, "SBB_PARAM_L126_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H127_OFFSET, \
                                    SBB_PARAM_H127_DEFAULT, \
                                    SBB_PARAM_H127_RD_MASK, "SBB_PARAM_H127_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L127_OFFSET, \
                                    SBB_PARAM_L127_DEFAULT, \
                                    SBB_PARAM_L127_RD_MASK, "SBB_PARAM_L127_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H128_OFFSET, \
                                    SBB_PARAM_H128_DEFAULT, \
                                    SBB_PARAM_H128_RD_MASK, "SBB_PARAM_H128_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L128_OFFSET, \
                                    SBB_PARAM_L128_DEFAULT, \
                                    SBB_PARAM_L128_RD_MASK, "SBB_PARAM_L128_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H129_OFFSET, \
                                    SBB_PARAM_H129_DEFAULT, \
                                    SBB_PARAM_H129_RD_MASK, "SBB_PARAM_H129_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L129_OFFSET, \
                                    SBB_PARAM_L129_DEFAULT, \
                                    SBB_PARAM_L129_RD_MASK, "SBB_PARAM_L129_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H130_OFFSET, \
                                    SBB_PARAM_H130_DEFAULT, \
                                    SBB_PARAM_H130_RD_MASK, "SBB_PARAM_H130_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L130_OFFSET, \
                                    SBB_PARAM_L130_DEFAULT, \
                                    SBB_PARAM_L130_RD_MASK, "SBB_PARAM_L130_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H131_OFFSET, \
                                    SBB_PARAM_H131_DEFAULT, \
                                    SBB_PARAM_H131_RD_MASK, "SBB_PARAM_H131_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L131_OFFSET, \
                                    SBB_PARAM_L131_DEFAULT, \
                                    SBB_PARAM_L131_RD_MASK, "SBB_PARAM_L131_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H132_OFFSET, \
                                    SBB_PARAM_H132_DEFAULT, \
                                    SBB_PARAM_H132_RD_MASK, "SBB_PARAM_H132_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L132_OFFSET, \
                                    SBB_PARAM_L132_DEFAULT, \
                                    SBB_PARAM_L132_RD_MASK, "SBB_PARAM_L132_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H133_OFFSET, \
                                    SBB_PARAM_H133_DEFAULT, \
                                    SBB_PARAM_H133_RD_MASK, "SBB_PARAM_H133_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L133_OFFSET, \
                                    SBB_PARAM_L133_DEFAULT, \
                                    SBB_PARAM_L133_RD_MASK, "SBB_PARAM_L133_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H134_OFFSET, \
                                    SBB_PARAM_H134_DEFAULT, \
                                    SBB_PARAM_H134_RD_MASK, "SBB_PARAM_H134_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L134_OFFSET, \
                                    SBB_PARAM_L134_DEFAULT, \
                                    SBB_PARAM_L134_RD_MASK, "SBB_PARAM_L134_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H135_OFFSET, \
                                    SBB_PARAM_H135_DEFAULT, \
                                    SBB_PARAM_H135_RD_MASK, "SBB_PARAM_H135_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L135_OFFSET, \
                                    SBB_PARAM_L135_DEFAULT, \
                                    SBB_PARAM_L135_RD_MASK, "SBB_PARAM_L135_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H136_OFFSET, \
                                    SBB_PARAM_H136_DEFAULT, \
                                    SBB_PARAM_H136_RD_MASK, "SBB_PARAM_H136_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L136_OFFSET, \
                                    SBB_PARAM_L136_DEFAULT, \
                                    SBB_PARAM_L136_RD_MASK, "SBB_PARAM_L136_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H137_OFFSET, \
                                    SBB_PARAM_H137_DEFAULT, \
                                    SBB_PARAM_H137_RD_MASK, "SBB_PARAM_H137_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L137_OFFSET, \
                                    SBB_PARAM_L137_DEFAULT, \
                                    SBB_PARAM_L137_RD_MASK, "SBB_PARAM_L137_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H138_OFFSET, \
                                    SBB_PARAM_H138_DEFAULT, \
                                    SBB_PARAM_H138_RD_MASK, "SBB_PARAM_H138_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L138_OFFSET, \
                                    SBB_PARAM_L138_DEFAULT, \
                                    SBB_PARAM_L138_RD_MASK, "SBB_PARAM_L138_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H139_OFFSET, \
                                    SBB_PARAM_H139_DEFAULT, \
                                    SBB_PARAM_H139_RD_MASK, "SBB_PARAM_H139_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L139_OFFSET, \
                                    SBB_PARAM_L139_DEFAULT, \
                                    SBB_PARAM_L139_RD_MASK, "SBB_PARAM_L139_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H140_OFFSET, \
                                    SBB_PARAM_H140_DEFAULT, \
                                    SBB_PARAM_H140_RD_MASK, "SBB_PARAM_H140_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L140_OFFSET, \
                                    SBB_PARAM_L140_DEFAULT, \
                                    SBB_PARAM_L140_RD_MASK, "SBB_PARAM_L140_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H141_OFFSET, \
                                    SBB_PARAM_H141_DEFAULT, \
                                    SBB_PARAM_H141_RD_MASK, "SBB_PARAM_H141_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L141_OFFSET, \
                                    SBB_PARAM_L141_DEFAULT, \
                                    SBB_PARAM_L141_RD_MASK, "SBB_PARAM_L141_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H142_OFFSET, \
                                    SBB_PARAM_H142_DEFAULT, \
                                    SBB_PARAM_H142_RD_MASK, "SBB_PARAM_H142_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L142_OFFSET, \
                                    SBB_PARAM_L142_DEFAULT, \
                                    SBB_PARAM_L142_RD_MASK, "SBB_PARAM_L142_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H143_OFFSET, \
                                    SBB_PARAM_H143_DEFAULT, \
                                    SBB_PARAM_H143_RD_MASK, "SBB_PARAM_H143_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L143_OFFSET, \
                                    SBB_PARAM_L143_DEFAULT, \
                                    SBB_PARAM_L143_RD_MASK, "SBB_PARAM_L143_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H144_OFFSET, \
                                    SBB_PARAM_H144_DEFAULT, \
                                    SBB_PARAM_H144_RD_MASK, "SBB_PARAM_H144_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L144_OFFSET, \
                                    SBB_PARAM_L144_DEFAULT, \
                                    SBB_PARAM_L144_RD_MASK, "SBB_PARAM_L144_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H145_OFFSET, \
                                    SBB_PARAM_H145_DEFAULT, \
                                    SBB_PARAM_H145_RD_MASK, "SBB_PARAM_H145_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L145_OFFSET, \
                                    SBB_PARAM_L145_DEFAULT, \
                                    SBB_PARAM_L145_RD_MASK, "SBB_PARAM_L145_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H146_OFFSET, \
                                    SBB_PARAM_H146_DEFAULT, \
                                    SBB_PARAM_H146_RD_MASK, "SBB_PARAM_H146_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L146_OFFSET, \
                                    SBB_PARAM_L146_DEFAULT, \
                                    SBB_PARAM_L146_RD_MASK, "SBB_PARAM_L146_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H147_OFFSET, \
                                    SBB_PARAM_H147_DEFAULT, \
                                    SBB_PARAM_H147_RD_MASK, "SBB_PARAM_H147_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L147_OFFSET, \
                                    SBB_PARAM_L147_DEFAULT, \
                                    SBB_PARAM_L147_RD_MASK, "SBB_PARAM_L147_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H148_OFFSET, \
                                    SBB_PARAM_H148_DEFAULT, \
                                    SBB_PARAM_H148_RD_MASK, "SBB_PARAM_H148_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L148_OFFSET, \
                                    SBB_PARAM_L148_DEFAULT, \
                                    SBB_PARAM_L148_RD_MASK, "SBB_PARAM_L148_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H149_OFFSET, \
                                    SBB_PARAM_H149_DEFAULT, \
                                    SBB_PARAM_H149_RD_MASK, "SBB_PARAM_H149_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L149_OFFSET, \
                                    SBB_PARAM_L149_DEFAULT, \
                                    SBB_PARAM_L149_RD_MASK, "SBB_PARAM_L149_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H150_OFFSET, \
                                    SBB_PARAM_H150_DEFAULT, \
                                    SBB_PARAM_H150_RD_MASK, "SBB_PARAM_H150_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L150_OFFSET, \
                                    SBB_PARAM_L150_DEFAULT, \
                                    SBB_PARAM_L150_RD_MASK, "SBB_PARAM_L150_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H151_OFFSET, \
                                    SBB_PARAM_H151_DEFAULT, \
                                    SBB_PARAM_H151_RD_MASK, "SBB_PARAM_H151_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L151_OFFSET, \
                                    SBB_PARAM_L151_DEFAULT, \
                                    SBB_PARAM_L151_RD_MASK, "SBB_PARAM_L151_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H152_OFFSET, \
                                    SBB_PARAM_H152_DEFAULT, \
                                    SBB_PARAM_H152_RD_MASK, "SBB_PARAM_H152_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L152_OFFSET, \
                                    SBB_PARAM_L152_DEFAULT, \
                                    SBB_PARAM_L152_RD_MASK, "SBB_PARAM_L152_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H153_OFFSET, \
                                    SBB_PARAM_H153_DEFAULT, \
                                    SBB_PARAM_H153_RD_MASK, "SBB_PARAM_H153_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L153_OFFSET, \
                                    SBB_PARAM_L153_DEFAULT, \
                                    SBB_PARAM_L153_RD_MASK, "SBB_PARAM_L153_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H154_OFFSET, \
                                    SBB_PARAM_H154_DEFAULT, \
                                    SBB_PARAM_H154_RD_MASK, "SBB_PARAM_H154_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L154_OFFSET, \
                                    SBB_PARAM_L154_DEFAULT, \
                                    SBB_PARAM_L154_RD_MASK, "SBB_PARAM_L154_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H155_OFFSET, \
                                    SBB_PARAM_H155_DEFAULT, \
                                    SBB_PARAM_H155_RD_MASK, "SBB_PARAM_H155_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L155_OFFSET, \
                                    SBB_PARAM_L155_DEFAULT, \
                                    SBB_PARAM_L155_RD_MASK, "SBB_PARAM_L155_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H156_OFFSET, \
                                    SBB_PARAM_H156_DEFAULT, \
                                    SBB_PARAM_H156_RD_MASK, "SBB_PARAM_H156_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L156_OFFSET, \
                                    SBB_PARAM_L156_DEFAULT, \
                                    SBB_PARAM_L156_RD_MASK, "SBB_PARAM_L156_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H157_OFFSET, \
                                    SBB_PARAM_H157_DEFAULT, \
                                    SBB_PARAM_H157_RD_MASK, "SBB_PARAM_H157_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L157_OFFSET, \
                                    SBB_PARAM_L157_DEFAULT, \
                                    SBB_PARAM_L157_RD_MASK, "SBB_PARAM_L157_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H158_OFFSET, \
                                    SBB_PARAM_H158_DEFAULT, \
                                    SBB_PARAM_H158_RD_MASK, "SBB_PARAM_H158_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L158_OFFSET, \
                                    SBB_PARAM_L158_DEFAULT, \
                                    SBB_PARAM_L158_RD_MASK, "SBB_PARAM_L158_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H159_OFFSET, \
                                    SBB_PARAM_H159_DEFAULT, \
                                    SBB_PARAM_H159_RD_MASK, "SBB_PARAM_H159_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L159_OFFSET, \
                                    SBB_PARAM_L159_DEFAULT, \
                                    SBB_PARAM_L159_RD_MASK, "SBB_PARAM_L159_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H160_OFFSET, \
                                    SBB_PARAM_H160_DEFAULT, \
                                    SBB_PARAM_H160_RD_MASK, "SBB_PARAM_H160_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L160_OFFSET, \
                                    SBB_PARAM_L160_DEFAULT, \
                                    SBB_PARAM_L160_RD_MASK, "SBB_PARAM_L160_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H161_OFFSET, \
                                    SBB_PARAM_H161_DEFAULT, \
                                    SBB_PARAM_H161_RD_MASK, "SBB_PARAM_H161_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L161_OFFSET, \
                                    SBB_PARAM_L161_DEFAULT, \
                                    SBB_PARAM_L161_RD_MASK, "SBB_PARAM_L161_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H162_OFFSET, \
                                    SBB_PARAM_H162_DEFAULT, \
                                    SBB_PARAM_H162_RD_MASK, "SBB_PARAM_H162_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L162_OFFSET, \
                                    SBB_PARAM_L162_DEFAULT, \
                                    SBB_PARAM_L162_RD_MASK, "SBB_PARAM_L162_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H163_OFFSET, \
                                    SBB_PARAM_H163_DEFAULT, \
                                    SBB_PARAM_H163_RD_MASK, "SBB_PARAM_H163_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L163_OFFSET, \
                                    SBB_PARAM_L163_DEFAULT, \
                                    SBB_PARAM_L163_RD_MASK, "SBB_PARAM_L163_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H164_OFFSET, \
                                    SBB_PARAM_H164_DEFAULT, \
                                    SBB_PARAM_H164_RD_MASK, "SBB_PARAM_H164_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L164_OFFSET, \
                                    SBB_PARAM_L164_DEFAULT, \
                                    SBB_PARAM_L164_RD_MASK, "SBB_PARAM_L164_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H165_OFFSET, \
                                    SBB_PARAM_H165_DEFAULT, \
                                    SBB_PARAM_H165_RD_MASK, "SBB_PARAM_H165_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L165_OFFSET, \
                                    SBB_PARAM_L165_DEFAULT, \
                                    SBB_PARAM_L165_RD_MASK, "SBB_PARAM_L165_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H166_OFFSET, \
                                    SBB_PARAM_H166_DEFAULT, \
                                    SBB_PARAM_H166_RD_MASK, "SBB_PARAM_H166_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L166_OFFSET, \
                                    SBB_PARAM_L166_DEFAULT, \
                                    SBB_PARAM_L166_RD_MASK, "SBB_PARAM_L166_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H167_OFFSET, \
                                    SBB_PARAM_H167_DEFAULT, \
                                    SBB_PARAM_H167_RD_MASK, "SBB_PARAM_H167_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L167_OFFSET, \
                                    SBB_PARAM_L167_DEFAULT, \
                                    SBB_PARAM_L167_RD_MASK, "SBB_PARAM_L167_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H168_OFFSET, \
                                    SBB_PARAM_H168_DEFAULT, \
                                    SBB_PARAM_H168_RD_MASK, "SBB_PARAM_H168_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L168_OFFSET, \
                                    SBB_PARAM_L168_DEFAULT, \
                                    SBB_PARAM_L168_RD_MASK, "SBB_PARAM_L168_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H169_OFFSET, \
                                    SBB_PARAM_H169_DEFAULT, \
                                    SBB_PARAM_H169_RD_MASK, "SBB_PARAM_H169_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L169_OFFSET, \
                                    SBB_PARAM_L169_DEFAULT, \
                                    SBB_PARAM_L169_RD_MASK, "SBB_PARAM_L169_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H170_OFFSET, \
                                    SBB_PARAM_H170_DEFAULT, \
                                    SBB_PARAM_H170_RD_MASK, "SBB_PARAM_H170_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L170_OFFSET, \
                                    SBB_PARAM_L170_DEFAULT, \
                                    SBB_PARAM_L170_RD_MASK, "SBB_PARAM_L170_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H171_OFFSET, \
                                    SBB_PARAM_H171_DEFAULT, \
                                    SBB_PARAM_H171_RD_MASK, "SBB_PARAM_H171_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L171_OFFSET, \
                                    SBB_PARAM_L171_DEFAULT, \
                                    SBB_PARAM_L171_RD_MASK, "SBB_PARAM_L171_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H172_OFFSET, \
                                    SBB_PARAM_H172_DEFAULT, \
                                    SBB_PARAM_H172_RD_MASK, "SBB_PARAM_H172_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L172_OFFSET, \
                                    SBB_PARAM_L172_DEFAULT, \
                                    SBB_PARAM_L172_RD_MASK, "SBB_PARAM_L172_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H173_OFFSET, \
                                    SBB_PARAM_H173_DEFAULT, \
                                    SBB_PARAM_H173_RD_MASK, "SBB_PARAM_H173_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L173_OFFSET, \
                                    SBB_PARAM_L173_DEFAULT, \
                                    SBB_PARAM_L173_RD_MASK, "SBB_PARAM_L173_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H174_OFFSET, \
                                    SBB_PARAM_H174_DEFAULT, \
                                    SBB_PARAM_H174_RD_MASK, "SBB_PARAM_H174_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L174_OFFSET, \
                                    SBB_PARAM_L174_DEFAULT, \
                                    SBB_PARAM_L174_RD_MASK, "SBB_PARAM_L174_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H175_OFFSET, \
                                    SBB_PARAM_H175_DEFAULT, \
                                    SBB_PARAM_H175_RD_MASK, "SBB_PARAM_H175_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L175_OFFSET, \
                                    SBB_PARAM_L175_DEFAULT, \
                                    SBB_PARAM_L175_RD_MASK, "SBB_PARAM_L175_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H176_OFFSET, \
                                    SBB_PARAM_H176_DEFAULT, \
                                    SBB_PARAM_H176_RD_MASK, "SBB_PARAM_H176_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L176_OFFSET, \
                                    SBB_PARAM_L176_DEFAULT, \
                                    SBB_PARAM_L176_RD_MASK, "SBB_PARAM_L176_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H177_OFFSET, \
                                    SBB_PARAM_H177_DEFAULT, \
                                    SBB_PARAM_H177_RD_MASK, "SBB_PARAM_H177_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L177_OFFSET, \
                                    SBB_PARAM_L177_DEFAULT, \
                                    SBB_PARAM_L177_RD_MASK, "SBB_PARAM_L177_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H178_OFFSET, \
                                    SBB_PARAM_H178_DEFAULT, \
                                    SBB_PARAM_H178_RD_MASK, "SBB_PARAM_H178_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L178_OFFSET, \
                                    SBB_PARAM_L178_DEFAULT, \
                                    SBB_PARAM_L178_RD_MASK, "SBB_PARAM_L178_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H179_OFFSET, \
                                    SBB_PARAM_H179_DEFAULT, \
                                    SBB_PARAM_H179_RD_MASK, "SBB_PARAM_H179_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L179_OFFSET, \
                                    SBB_PARAM_L179_DEFAULT, \
                                    SBB_PARAM_L179_RD_MASK, "SBB_PARAM_L179_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H180_OFFSET, \
                                    SBB_PARAM_H180_DEFAULT, \
                                    SBB_PARAM_H180_RD_MASK, "SBB_PARAM_H180_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L180_OFFSET, \
                                    SBB_PARAM_L180_DEFAULT, \
                                    SBB_PARAM_L180_RD_MASK, "SBB_PARAM_L180_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H181_OFFSET, \
                                    SBB_PARAM_H181_DEFAULT, \
                                    SBB_PARAM_H181_RD_MASK, "SBB_PARAM_H181_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L181_OFFSET, \
                                    SBB_PARAM_L181_DEFAULT, \
                                    SBB_PARAM_L181_RD_MASK, "SBB_PARAM_L181_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H182_OFFSET, \
                                    SBB_PARAM_H182_DEFAULT, \
                                    SBB_PARAM_H182_RD_MASK, "SBB_PARAM_H182_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L182_OFFSET, \
                                    SBB_PARAM_L182_DEFAULT, \
                                    SBB_PARAM_L182_RD_MASK, "SBB_PARAM_L182_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H183_OFFSET, \
                                    SBB_PARAM_H183_DEFAULT, \
                                    SBB_PARAM_H183_RD_MASK, "SBB_PARAM_H183_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L183_OFFSET, \
                                    SBB_PARAM_L183_DEFAULT, \
                                    SBB_PARAM_L183_RD_MASK, "SBB_PARAM_L183_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H184_OFFSET, \
                                    SBB_PARAM_H184_DEFAULT, \
                                    SBB_PARAM_H184_RD_MASK, "SBB_PARAM_H184_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L184_OFFSET, \
                                    SBB_PARAM_L184_DEFAULT, \
                                    SBB_PARAM_L184_RD_MASK, "SBB_PARAM_L184_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H185_OFFSET, \
                                    SBB_PARAM_H185_DEFAULT, \
                                    SBB_PARAM_H185_RD_MASK, "SBB_PARAM_H185_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L185_OFFSET, \
                                    SBB_PARAM_L185_DEFAULT, \
                                    SBB_PARAM_L185_RD_MASK, "SBB_PARAM_L185_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H186_OFFSET, \
                                    SBB_PARAM_H186_DEFAULT, \
                                    SBB_PARAM_H186_RD_MASK, "SBB_PARAM_H186_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L186_OFFSET, \
                                    SBB_PARAM_L186_DEFAULT, \
                                    SBB_PARAM_L186_RD_MASK, "SBB_PARAM_L186_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H187_OFFSET, \
                                    SBB_PARAM_H187_DEFAULT, \
                                    SBB_PARAM_H187_RD_MASK, "SBB_PARAM_H187_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L187_OFFSET, \
                                    SBB_PARAM_L187_DEFAULT, \
                                    SBB_PARAM_L187_RD_MASK, "SBB_PARAM_L187_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H188_OFFSET, \
                                    SBB_PARAM_H188_DEFAULT, \
                                    SBB_PARAM_H188_RD_MASK, "SBB_PARAM_H188_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L188_OFFSET, \
                                    SBB_PARAM_L188_DEFAULT, \
                                    SBB_PARAM_L188_RD_MASK, "SBB_PARAM_L188_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H189_OFFSET, \
                                    SBB_PARAM_H189_DEFAULT, \
                                    SBB_PARAM_H189_RD_MASK, "SBB_PARAM_H189_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L189_OFFSET, \
                                    SBB_PARAM_L189_DEFAULT, \
                                    SBB_PARAM_L189_RD_MASK, "SBB_PARAM_L189_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H190_OFFSET, \
                                    SBB_PARAM_H190_DEFAULT, \
                                    SBB_PARAM_H190_RD_MASK, "SBB_PARAM_H190_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L190_OFFSET, \
                                    SBB_PARAM_L190_DEFAULT, \
                                    SBB_PARAM_L190_RD_MASK, "SBB_PARAM_L190_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H191_OFFSET, \
                                    SBB_PARAM_H191_DEFAULT, \
                                    SBB_PARAM_H191_RD_MASK, "SBB_PARAM_H191_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L191_OFFSET, \
                                    SBB_PARAM_L191_DEFAULT, \
                                    SBB_PARAM_L191_RD_MASK, "SBB_PARAM_L191_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H192_OFFSET, \
                                    SBB_PARAM_H192_DEFAULT, \
                                    SBB_PARAM_H192_RD_MASK, "SBB_PARAM_H192_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L192_OFFSET, \
                                    SBB_PARAM_L192_DEFAULT, \
                                    SBB_PARAM_L192_RD_MASK, "SBB_PARAM_L192_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H193_OFFSET, \
                                    SBB_PARAM_H193_DEFAULT, \
                                    SBB_PARAM_H193_RD_MASK, "SBB_PARAM_H193_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L193_OFFSET, \
                                    SBB_PARAM_L193_DEFAULT, \
                                    SBB_PARAM_L193_RD_MASK, "SBB_PARAM_L193_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H194_OFFSET, \
                                    SBB_PARAM_H194_DEFAULT, \
                                    SBB_PARAM_H194_RD_MASK, "SBB_PARAM_H194_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L194_OFFSET, \
                                    SBB_PARAM_L194_DEFAULT, \
                                    SBB_PARAM_L194_RD_MASK, "SBB_PARAM_L194_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H195_OFFSET, \
                                    SBB_PARAM_H195_DEFAULT, \
                                    SBB_PARAM_H195_RD_MASK, "SBB_PARAM_H195_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L195_OFFSET, \
                                    SBB_PARAM_L195_DEFAULT, \
                                    SBB_PARAM_L195_RD_MASK, "SBB_PARAM_L195_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H196_OFFSET, \
                                    SBB_PARAM_H196_DEFAULT, \
                                    SBB_PARAM_H196_RD_MASK, "SBB_PARAM_H196_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L196_OFFSET, \
                                    SBB_PARAM_L196_DEFAULT, \
                                    SBB_PARAM_L196_RD_MASK, "SBB_PARAM_L196_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H197_OFFSET, \
                                    SBB_PARAM_H197_DEFAULT, \
                                    SBB_PARAM_H197_RD_MASK, "SBB_PARAM_H197_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L197_OFFSET, \
                                    SBB_PARAM_L197_DEFAULT, \
                                    SBB_PARAM_L197_RD_MASK, "SBB_PARAM_L197_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H198_OFFSET, \
                                    SBB_PARAM_H198_DEFAULT, \
                                    SBB_PARAM_H198_RD_MASK, "SBB_PARAM_H198_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L198_OFFSET, \
                                    SBB_PARAM_L198_DEFAULT, \
                                    SBB_PARAM_L198_RD_MASK, "SBB_PARAM_L198_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H199_OFFSET, \
                                    SBB_PARAM_H199_DEFAULT, \
                                    SBB_PARAM_H199_RD_MASK, "SBB_PARAM_H199_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L199_OFFSET, \
                                    SBB_PARAM_L199_DEFAULT, \
                                    SBB_PARAM_L199_RD_MASK, "SBB_PARAM_L199_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H200_OFFSET, \
                                    SBB_PARAM_H200_DEFAULT, \
                                    SBB_PARAM_H200_RD_MASK, "SBB_PARAM_H200_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L200_OFFSET, \
                                    SBB_PARAM_L200_DEFAULT, \
                                    SBB_PARAM_L200_RD_MASK, "SBB_PARAM_L200_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H201_OFFSET, \
                                    SBB_PARAM_H201_DEFAULT, \
                                    SBB_PARAM_H201_RD_MASK, "SBB_PARAM_H201_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L201_OFFSET, \
                                    SBB_PARAM_L201_DEFAULT, \
                                    SBB_PARAM_L201_RD_MASK, "SBB_PARAM_L201_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H202_OFFSET, \
                                    SBB_PARAM_H202_DEFAULT, \
                                    SBB_PARAM_H202_RD_MASK, "SBB_PARAM_H202_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L202_OFFSET, \
                                    SBB_PARAM_L202_DEFAULT, \
                                    SBB_PARAM_L202_RD_MASK, "SBB_PARAM_L202_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H203_OFFSET, \
                                    SBB_PARAM_H203_DEFAULT, \
                                    SBB_PARAM_H203_RD_MASK, "SBB_PARAM_H203_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L203_OFFSET, \
                                    SBB_PARAM_L203_DEFAULT, \
                                    SBB_PARAM_L203_RD_MASK, "SBB_PARAM_L203_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H204_OFFSET, \
                                    SBB_PARAM_H204_DEFAULT, \
                                    SBB_PARAM_H204_RD_MASK, "SBB_PARAM_H204_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L204_OFFSET, \
                                    SBB_PARAM_L204_DEFAULT, \
                                    SBB_PARAM_L204_RD_MASK, "SBB_PARAM_L204_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H205_OFFSET, \
                                    SBB_PARAM_H205_DEFAULT, \
                                    SBB_PARAM_H205_RD_MASK, "SBB_PARAM_H205_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L205_OFFSET, \
                                    SBB_PARAM_L205_DEFAULT, \
                                    SBB_PARAM_L205_RD_MASK, "SBB_PARAM_L205_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H206_OFFSET, \
                                    SBB_PARAM_H206_DEFAULT, \
                                    SBB_PARAM_H206_RD_MASK, "SBB_PARAM_H206_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L206_OFFSET, \
                                    SBB_PARAM_L206_DEFAULT, \
                                    SBB_PARAM_L206_RD_MASK, "SBB_PARAM_L206_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H207_OFFSET, \
                                    SBB_PARAM_H207_DEFAULT, \
                                    SBB_PARAM_H207_RD_MASK, "SBB_PARAM_H207_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L207_OFFSET, \
                                    SBB_PARAM_L207_DEFAULT, \
                                    SBB_PARAM_L207_RD_MASK, "SBB_PARAM_L207_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H208_OFFSET, \
                                    SBB_PARAM_H208_DEFAULT, \
                                    SBB_PARAM_H208_RD_MASK, "SBB_PARAM_H208_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L208_OFFSET, \
                                    SBB_PARAM_L208_DEFAULT, \
                                    SBB_PARAM_L208_RD_MASK, "SBB_PARAM_L208_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H209_OFFSET, \
                                    SBB_PARAM_H209_DEFAULT, \
                                    SBB_PARAM_H209_RD_MASK, "SBB_PARAM_H209_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L209_OFFSET, \
                                    SBB_PARAM_L209_DEFAULT, \
                                    SBB_PARAM_L209_RD_MASK, "SBB_PARAM_L209_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H210_OFFSET, \
                                    SBB_PARAM_H210_DEFAULT, \
                                    SBB_PARAM_H210_RD_MASK, "SBB_PARAM_H210_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L210_OFFSET, \
                                    SBB_PARAM_L210_DEFAULT, \
                                    SBB_PARAM_L210_RD_MASK, "SBB_PARAM_L210_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H211_OFFSET, \
                                    SBB_PARAM_H211_DEFAULT, \
                                    SBB_PARAM_H211_RD_MASK, "SBB_PARAM_H211_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L211_OFFSET, \
                                    SBB_PARAM_L211_DEFAULT, \
                                    SBB_PARAM_L211_RD_MASK, "SBB_PARAM_L211_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H212_OFFSET, \
                                    SBB_PARAM_H212_DEFAULT, \
                                    SBB_PARAM_H212_RD_MASK, "SBB_PARAM_H212_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L212_OFFSET, \
                                    SBB_PARAM_L212_DEFAULT, \
                                    SBB_PARAM_L212_RD_MASK, "SBB_PARAM_L212_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H213_OFFSET, \
                                    SBB_PARAM_H213_DEFAULT, \
                                    SBB_PARAM_H213_RD_MASK, "SBB_PARAM_H213_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L213_OFFSET, \
                                    SBB_PARAM_L213_DEFAULT, \
                                    SBB_PARAM_L213_RD_MASK, "SBB_PARAM_L213_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H214_OFFSET, \
                                    SBB_PARAM_H214_DEFAULT, \
                                    SBB_PARAM_H214_RD_MASK, "SBB_PARAM_H214_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L214_OFFSET, \
                                    SBB_PARAM_L214_DEFAULT, \
                                    SBB_PARAM_L214_RD_MASK, "SBB_PARAM_L214_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H215_OFFSET, \
                                    SBB_PARAM_H215_DEFAULT, \
                                    SBB_PARAM_H215_RD_MASK, "SBB_PARAM_H215_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L215_OFFSET, \
                                    SBB_PARAM_L215_DEFAULT, \
                                    SBB_PARAM_L215_RD_MASK, "SBB_PARAM_L215_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H216_OFFSET, \
                                    SBB_PARAM_H216_DEFAULT, \
                                    SBB_PARAM_H216_RD_MASK, "SBB_PARAM_H216_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L216_OFFSET, \
                                    SBB_PARAM_L216_DEFAULT, \
                                    SBB_PARAM_L216_RD_MASK, "SBB_PARAM_L216_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H217_OFFSET, \
                                    SBB_PARAM_H217_DEFAULT, \
                                    SBB_PARAM_H217_RD_MASK, "SBB_PARAM_H217_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L217_OFFSET, \
                                    SBB_PARAM_L217_DEFAULT, \
                                    SBB_PARAM_L217_RD_MASK, "SBB_PARAM_L217_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H218_OFFSET, \
                                    SBB_PARAM_H218_DEFAULT, \
                                    SBB_PARAM_H218_RD_MASK, "SBB_PARAM_H218_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L218_OFFSET, \
                                    SBB_PARAM_L218_DEFAULT, \
                                    SBB_PARAM_L218_RD_MASK, "SBB_PARAM_L218_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H219_OFFSET, \
                                    SBB_PARAM_H219_DEFAULT, \
                                    SBB_PARAM_H219_RD_MASK, "SBB_PARAM_H219_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L219_OFFSET, \
                                    SBB_PARAM_L219_DEFAULT, \
                                    SBB_PARAM_L219_RD_MASK, "SBB_PARAM_L219_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H220_OFFSET, \
                                    SBB_PARAM_H220_DEFAULT, \
                                    SBB_PARAM_H220_RD_MASK, "SBB_PARAM_H220_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L220_OFFSET, \
                                    SBB_PARAM_L220_DEFAULT, \
                                    SBB_PARAM_L220_RD_MASK, "SBB_PARAM_L220_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H221_OFFSET, \
                                    SBB_PARAM_H221_DEFAULT, \
                                    SBB_PARAM_H221_RD_MASK, "SBB_PARAM_H221_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L221_OFFSET, \
                                    SBB_PARAM_L221_DEFAULT, \
                                    SBB_PARAM_L221_RD_MASK, "SBB_PARAM_L221_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H222_OFFSET, \
                                    SBB_PARAM_H222_DEFAULT, \
                                    SBB_PARAM_H222_RD_MASK, "SBB_PARAM_H222_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L222_OFFSET, \
                                    SBB_PARAM_L222_DEFAULT, \
                                    SBB_PARAM_L222_RD_MASK, "SBB_PARAM_L222_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H223_OFFSET, \
                                    SBB_PARAM_H223_DEFAULT, \
                                    SBB_PARAM_H223_RD_MASK, "SBB_PARAM_H223_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L223_OFFSET, \
                                    SBB_PARAM_L223_DEFAULT, \
                                    SBB_PARAM_L223_RD_MASK, "SBB_PARAM_L223_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H224_OFFSET, \
                                    SBB_PARAM_H224_DEFAULT, \
                                    SBB_PARAM_H224_RD_MASK, "SBB_PARAM_H224_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L224_OFFSET, \
                                    SBB_PARAM_L224_DEFAULT, \
                                    SBB_PARAM_L224_RD_MASK, "SBB_PARAM_L224_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H225_OFFSET, \
                                    SBB_PARAM_H225_DEFAULT, \
                                    SBB_PARAM_H225_RD_MASK, "SBB_PARAM_H225_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L225_OFFSET, \
                                    SBB_PARAM_L225_DEFAULT, \
                                    SBB_PARAM_L225_RD_MASK, "SBB_PARAM_L225_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H226_OFFSET, \
                                    SBB_PARAM_H226_DEFAULT, \
                                    SBB_PARAM_H226_RD_MASK, "SBB_PARAM_H226_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L226_OFFSET, \
                                    SBB_PARAM_L226_DEFAULT, \
                                    SBB_PARAM_L226_RD_MASK, "SBB_PARAM_L226_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H227_OFFSET, \
                                    SBB_PARAM_H227_DEFAULT, \
                                    SBB_PARAM_H227_RD_MASK, "SBB_PARAM_H227_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L227_OFFSET, \
                                    SBB_PARAM_L227_DEFAULT, \
                                    SBB_PARAM_L227_RD_MASK, "SBB_PARAM_L227_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H228_OFFSET, \
                                    SBB_PARAM_H228_DEFAULT, \
                                    SBB_PARAM_H228_RD_MASK, "SBB_PARAM_H228_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L228_OFFSET, \
                                    SBB_PARAM_L228_DEFAULT, \
                                    SBB_PARAM_L228_RD_MASK, "SBB_PARAM_L228_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H229_OFFSET, \
                                    SBB_PARAM_H229_DEFAULT, \
                                    SBB_PARAM_H229_RD_MASK, "SBB_PARAM_H229_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L229_OFFSET, \
                                    SBB_PARAM_L229_DEFAULT, \
                                    SBB_PARAM_L229_RD_MASK, "SBB_PARAM_L229_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H230_OFFSET, \
                                    SBB_PARAM_H230_DEFAULT, \
                                    SBB_PARAM_H230_RD_MASK, "SBB_PARAM_H230_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L230_OFFSET, \
                                    SBB_PARAM_L230_DEFAULT, \
                                    SBB_PARAM_L230_RD_MASK, "SBB_PARAM_L230_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H231_OFFSET, \
                                    SBB_PARAM_H231_DEFAULT, \
                                    SBB_PARAM_H231_RD_MASK, "SBB_PARAM_H231_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L231_OFFSET, \
                                    SBB_PARAM_L231_DEFAULT, \
                                    SBB_PARAM_L231_RD_MASK, "SBB_PARAM_L231_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H232_OFFSET, \
                                    SBB_PARAM_H232_DEFAULT, \
                                    SBB_PARAM_H232_RD_MASK, "SBB_PARAM_H232_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L232_OFFSET, \
                                    SBB_PARAM_L232_DEFAULT, \
                                    SBB_PARAM_L232_RD_MASK, "SBB_PARAM_L232_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H233_OFFSET, \
                                    SBB_PARAM_H233_DEFAULT, \
                                    SBB_PARAM_H233_RD_MASK, "SBB_PARAM_H233_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L233_OFFSET, \
                                    SBB_PARAM_L233_DEFAULT, \
                                    SBB_PARAM_L233_RD_MASK, "SBB_PARAM_L233_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H234_OFFSET, \
                                    SBB_PARAM_H234_DEFAULT, \
                                    SBB_PARAM_H234_RD_MASK, "SBB_PARAM_H234_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L234_OFFSET, \
                                    SBB_PARAM_L234_DEFAULT, \
                                    SBB_PARAM_L234_RD_MASK, "SBB_PARAM_L234_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H235_OFFSET, \
                                    SBB_PARAM_H235_DEFAULT, \
                                    SBB_PARAM_H235_RD_MASK, "SBB_PARAM_H235_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L235_OFFSET, \
                                    SBB_PARAM_L235_DEFAULT, \
                                    SBB_PARAM_L235_RD_MASK, "SBB_PARAM_L235_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H236_OFFSET, \
                                    SBB_PARAM_H236_DEFAULT, \
                                    SBB_PARAM_H236_RD_MASK, "SBB_PARAM_H236_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L236_OFFSET, \
                                    SBB_PARAM_L236_DEFAULT, \
                                    SBB_PARAM_L236_RD_MASK, "SBB_PARAM_L236_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H237_OFFSET, \
                                    SBB_PARAM_H237_DEFAULT, \
                                    SBB_PARAM_H237_RD_MASK, "SBB_PARAM_H237_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L237_OFFSET, \
                                    SBB_PARAM_L237_DEFAULT, \
                                    SBB_PARAM_L237_RD_MASK, "SBB_PARAM_L237_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H238_OFFSET, \
                                    SBB_PARAM_H238_DEFAULT, \
                                    SBB_PARAM_H238_RD_MASK, "SBB_PARAM_H238_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L238_OFFSET, \
                                    SBB_PARAM_L238_DEFAULT, \
                                    SBB_PARAM_L238_RD_MASK, "SBB_PARAM_L238_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H239_OFFSET, \
                                    SBB_PARAM_H239_DEFAULT, \
                                    SBB_PARAM_H239_RD_MASK, "SBB_PARAM_H239_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L239_OFFSET, \
                                    SBB_PARAM_L239_DEFAULT, \
                                    SBB_PARAM_L239_RD_MASK, "SBB_PARAM_L239_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H240_OFFSET, \
                                    SBB_PARAM_H240_DEFAULT, \
                                    SBB_PARAM_H240_RD_MASK, "SBB_PARAM_H240_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L240_OFFSET, \
                                    SBB_PARAM_L240_DEFAULT, \
                                    SBB_PARAM_L240_RD_MASK, "SBB_PARAM_L240_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H241_OFFSET, \
                                    SBB_PARAM_H241_DEFAULT, \
                                    SBB_PARAM_H241_RD_MASK, "SBB_PARAM_H241_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L241_OFFSET, \
                                    SBB_PARAM_L241_DEFAULT, \
                                    SBB_PARAM_L241_RD_MASK, "SBB_PARAM_L241_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H242_OFFSET, \
                                    SBB_PARAM_H242_DEFAULT, \
                                    SBB_PARAM_H242_RD_MASK, "SBB_PARAM_H242_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L242_OFFSET, \
                                    SBB_PARAM_L242_DEFAULT, \
                                    SBB_PARAM_L242_RD_MASK, "SBB_PARAM_L242_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H243_OFFSET, \
                                    SBB_PARAM_H243_DEFAULT, \
                                    SBB_PARAM_H243_RD_MASK, "SBB_PARAM_H243_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L243_OFFSET, \
                                    SBB_PARAM_L243_DEFAULT, \
                                    SBB_PARAM_L243_RD_MASK, "SBB_PARAM_L243_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H244_OFFSET, \
                                    SBB_PARAM_H244_DEFAULT, \
                                    SBB_PARAM_H244_RD_MASK, "SBB_PARAM_H244_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L244_OFFSET, \
                                    SBB_PARAM_L244_DEFAULT, \
                                    SBB_PARAM_L244_RD_MASK, "SBB_PARAM_L244_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H245_OFFSET, \
                                    SBB_PARAM_H245_DEFAULT, \
                                    SBB_PARAM_H245_RD_MASK, "SBB_PARAM_H245_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L245_OFFSET, \
                                    SBB_PARAM_L245_DEFAULT, \
                                    SBB_PARAM_L245_RD_MASK, "SBB_PARAM_L245_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H246_OFFSET, \
                                    SBB_PARAM_H246_DEFAULT, \
                                    SBB_PARAM_H246_RD_MASK, "SBB_PARAM_H246_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L246_OFFSET, \
                                    SBB_PARAM_L246_DEFAULT, \
                                    SBB_PARAM_L246_RD_MASK, "SBB_PARAM_L246_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H247_OFFSET, \
                                    SBB_PARAM_H247_DEFAULT, \
                                    SBB_PARAM_H247_RD_MASK, "SBB_PARAM_H247_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L247_OFFSET, \
                                    SBB_PARAM_L247_DEFAULT, \
                                    SBB_PARAM_L247_RD_MASK, "SBB_PARAM_L247_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H248_OFFSET, \
                                    SBB_PARAM_H248_DEFAULT, \
                                    SBB_PARAM_H248_RD_MASK, "SBB_PARAM_H248_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L248_OFFSET, \
                                    SBB_PARAM_L248_DEFAULT, \
                                    SBB_PARAM_L248_RD_MASK, "SBB_PARAM_L248_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H249_OFFSET, \
                                    SBB_PARAM_H249_DEFAULT, \
                                    SBB_PARAM_H249_RD_MASK, "SBB_PARAM_H249_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L249_OFFSET, \
                                    SBB_PARAM_L249_DEFAULT, \
                                    SBB_PARAM_L249_RD_MASK, "SBB_PARAM_L249_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H250_OFFSET, \
                                    SBB_PARAM_H250_DEFAULT, \
                                    SBB_PARAM_H250_RD_MASK, "SBB_PARAM_H250_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L250_OFFSET, \
                                    SBB_PARAM_L250_DEFAULT, \
                                    SBB_PARAM_L250_RD_MASK, "SBB_PARAM_L250_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H251_OFFSET, \
                                    SBB_PARAM_H251_DEFAULT, \
                                    SBB_PARAM_H251_RD_MASK, "SBB_PARAM_H251_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L251_OFFSET, \
                                    SBB_PARAM_L251_DEFAULT, \
                                    SBB_PARAM_L251_RD_MASK, "SBB_PARAM_L251_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H252_OFFSET, \
                                    SBB_PARAM_H252_DEFAULT, \
                                    SBB_PARAM_H252_RD_MASK, "SBB_PARAM_H252_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L252_OFFSET, \
                                    SBB_PARAM_L252_DEFAULT, \
                                    SBB_PARAM_L252_RD_MASK, "SBB_PARAM_L252_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H253_OFFSET, \
                                    SBB_PARAM_H253_DEFAULT, \
                                    SBB_PARAM_H253_RD_MASK, "SBB_PARAM_H253_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L253_OFFSET, \
                                    SBB_PARAM_L253_DEFAULT, \
                                    SBB_PARAM_L253_RD_MASK, "SBB_PARAM_L253_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H254_OFFSET, \
                                    SBB_PARAM_H254_DEFAULT, \
                                    SBB_PARAM_H254_RD_MASK, "SBB_PARAM_H254_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L254_OFFSET, \
                                    SBB_PARAM_L254_DEFAULT, \
                                    SBB_PARAM_L254_RD_MASK, "SBB_PARAM_L254_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H255_OFFSET, \
                                    SBB_PARAM_H255_DEFAULT, \
                                    SBB_PARAM_H255_RD_MASK, "SBB_PARAM_H255_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L255_OFFSET, \
                                    SBB_PARAM_L255_DEFAULT, \
                                    SBB_PARAM_L255_RD_MASK, "SBB_PARAM_L255_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H256_OFFSET, \
                                    SBB_PARAM_H256_DEFAULT, \
                                    SBB_PARAM_H256_RD_MASK, "SBB_PARAM_H256_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L256_OFFSET, \
                                    SBB_PARAM_L256_DEFAULT, \
                                    SBB_PARAM_L256_RD_MASK, "SBB_PARAM_L256_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H257_OFFSET, \
                                    SBB_PARAM_H257_DEFAULT, \
                                    SBB_PARAM_H257_RD_MASK, "SBB_PARAM_H257_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L257_OFFSET, \
                                    SBB_PARAM_L257_DEFAULT, \
                                    SBB_PARAM_L257_RD_MASK, "SBB_PARAM_L257_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H258_OFFSET, \
                                    SBB_PARAM_H258_DEFAULT, \
                                    SBB_PARAM_H258_RD_MASK, "SBB_PARAM_H258_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L258_OFFSET, \
                                    SBB_PARAM_L258_DEFAULT, \
                                    SBB_PARAM_L258_RD_MASK, "SBB_PARAM_L258_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H259_OFFSET, \
                                    SBB_PARAM_H259_DEFAULT, \
                                    SBB_PARAM_H259_RD_MASK, "SBB_PARAM_H259_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L259_OFFSET, \
                                    SBB_PARAM_L259_DEFAULT, \
                                    SBB_PARAM_L259_RD_MASK, "SBB_PARAM_L259_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H260_OFFSET, \
                                    SBB_PARAM_H260_DEFAULT, \
                                    SBB_PARAM_H260_RD_MASK, "SBB_PARAM_H260_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L260_OFFSET, \
                                    SBB_PARAM_L260_DEFAULT, \
                                    SBB_PARAM_L260_RD_MASK, "SBB_PARAM_L260_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H261_OFFSET, \
                                    SBB_PARAM_H261_DEFAULT, \
                                    SBB_PARAM_H261_RD_MASK, "SBB_PARAM_H261_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L261_OFFSET, \
                                    SBB_PARAM_L261_DEFAULT, \
                                    SBB_PARAM_L261_RD_MASK, "SBB_PARAM_L261_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H262_OFFSET, \
                                    SBB_PARAM_H262_DEFAULT, \
                                    SBB_PARAM_H262_RD_MASK, "SBB_PARAM_H262_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L262_OFFSET, \
                                    SBB_PARAM_L262_DEFAULT, \
                                    SBB_PARAM_L262_RD_MASK, "SBB_PARAM_L262_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H263_OFFSET, \
                                    SBB_PARAM_H263_DEFAULT, \
                                    SBB_PARAM_H263_RD_MASK, "SBB_PARAM_H263_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L263_OFFSET, \
                                    SBB_PARAM_L263_DEFAULT, \
                                    SBB_PARAM_L263_RD_MASK, "SBB_PARAM_L263_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H264_OFFSET, \
                                    SBB_PARAM_H264_DEFAULT, \
                                    SBB_PARAM_H264_RD_MASK, "SBB_PARAM_H264_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L264_OFFSET, \
                                    SBB_PARAM_L264_DEFAULT, \
                                    SBB_PARAM_L264_RD_MASK, "SBB_PARAM_L264_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H265_OFFSET, \
                                    SBB_PARAM_H265_DEFAULT, \
                                    SBB_PARAM_H265_RD_MASK, "SBB_PARAM_H265_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L265_OFFSET, \
                                    SBB_PARAM_L265_DEFAULT, \
                                    SBB_PARAM_L265_RD_MASK, "SBB_PARAM_L265_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H266_OFFSET, \
                                    SBB_PARAM_H266_DEFAULT, \
                                    SBB_PARAM_H266_RD_MASK, "SBB_PARAM_H266_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L266_OFFSET, \
                                    SBB_PARAM_L266_DEFAULT, \
                                    SBB_PARAM_L266_RD_MASK, "SBB_PARAM_L266_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H267_OFFSET, \
                                    SBB_PARAM_H267_DEFAULT, \
                                    SBB_PARAM_H267_RD_MASK, "SBB_PARAM_H267_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L267_OFFSET, \
                                    SBB_PARAM_L267_DEFAULT, \
                                    SBB_PARAM_L267_RD_MASK, "SBB_PARAM_L267_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H268_OFFSET, \
                                    SBB_PARAM_H268_DEFAULT, \
                                    SBB_PARAM_H268_RD_MASK, "SBB_PARAM_H268_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L268_OFFSET, \
                                    SBB_PARAM_L268_DEFAULT, \
                                    SBB_PARAM_L268_RD_MASK, "SBB_PARAM_L268_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H269_OFFSET, \
                                    SBB_PARAM_H269_DEFAULT, \
                                    SBB_PARAM_H269_RD_MASK, "SBB_PARAM_H269_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L269_OFFSET, \
                                    SBB_PARAM_L269_DEFAULT, \
                                    SBB_PARAM_L269_RD_MASK, "SBB_PARAM_L269_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H270_OFFSET, \
                                    SBB_PARAM_H270_DEFAULT, \
                                    SBB_PARAM_H270_RD_MASK, "SBB_PARAM_H270_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L270_OFFSET, \
                                    SBB_PARAM_L270_DEFAULT, \
                                    SBB_PARAM_L270_RD_MASK, "SBB_PARAM_L270_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H271_OFFSET, \
                                    SBB_PARAM_H271_DEFAULT, \
                                    SBB_PARAM_H271_RD_MASK, "SBB_PARAM_H271_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L271_OFFSET, \
                                    SBB_PARAM_L271_DEFAULT, \
                                    SBB_PARAM_L271_RD_MASK, "SBB_PARAM_L271_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H272_OFFSET, \
                                    SBB_PARAM_H272_DEFAULT, \
                                    SBB_PARAM_H272_RD_MASK, "SBB_PARAM_H272_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L272_OFFSET, \
                                    SBB_PARAM_L272_DEFAULT, \
                                    SBB_PARAM_L272_RD_MASK, "SBB_PARAM_L272_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H273_OFFSET, \
                                    SBB_PARAM_H273_DEFAULT, \
                                    SBB_PARAM_H273_RD_MASK, "SBB_PARAM_H273_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L273_OFFSET, \
                                    SBB_PARAM_L273_DEFAULT, \
                                    SBB_PARAM_L273_RD_MASK, "SBB_PARAM_L273_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H274_OFFSET, \
                                    SBB_PARAM_H274_DEFAULT, \
                                    SBB_PARAM_H274_RD_MASK, "SBB_PARAM_H274_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L274_OFFSET, \
                                    SBB_PARAM_L274_DEFAULT, \
                                    SBB_PARAM_L274_RD_MASK, "SBB_PARAM_L274_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H275_OFFSET, \
                                    SBB_PARAM_H275_DEFAULT, \
                                    SBB_PARAM_H275_RD_MASK, "SBB_PARAM_H275_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L275_OFFSET, \
                                    SBB_PARAM_L275_DEFAULT, \
                                    SBB_PARAM_L275_RD_MASK, "SBB_PARAM_L275_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H276_OFFSET, \
                                    SBB_PARAM_H276_DEFAULT, \
                                    SBB_PARAM_H276_RD_MASK, "SBB_PARAM_H276_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L276_OFFSET, \
                                    SBB_PARAM_L276_DEFAULT, \
                                    SBB_PARAM_L276_RD_MASK, "SBB_PARAM_L276_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H277_OFFSET, \
                                    SBB_PARAM_H277_DEFAULT, \
                                    SBB_PARAM_H277_RD_MASK, "SBB_PARAM_H277_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L277_OFFSET, \
                                    SBB_PARAM_L277_DEFAULT, \
                                    SBB_PARAM_L277_RD_MASK, "SBB_PARAM_L277_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H278_OFFSET, \
                                    SBB_PARAM_H278_DEFAULT, \
                                    SBB_PARAM_H278_RD_MASK, "SBB_PARAM_H278_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L278_OFFSET, \
                                    SBB_PARAM_L278_DEFAULT, \
                                    SBB_PARAM_L278_RD_MASK, "SBB_PARAM_L278_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H279_OFFSET, \
                                    SBB_PARAM_H279_DEFAULT, \
                                    SBB_PARAM_H279_RD_MASK, "SBB_PARAM_H279_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L279_OFFSET, \
                                    SBB_PARAM_L279_DEFAULT, \
                                    SBB_PARAM_L279_RD_MASK, "SBB_PARAM_L279_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H280_OFFSET, \
                                    SBB_PARAM_H280_DEFAULT, \
                                    SBB_PARAM_H280_RD_MASK, "SBB_PARAM_H280_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L280_OFFSET, \
                                    SBB_PARAM_L280_DEFAULT, \
                                    SBB_PARAM_L280_RD_MASK, "SBB_PARAM_L280_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H281_OFFSET, \
                                    SBB_PARAM_H281_DEFAULT, \
                                    SBB_PARAM_H281_RD_MASK, "SBB_PARAM_H281_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L281_OFFSET, \
                                    SBB_PARAM_L281_DEFAULT, \
                                    SBB_PARAM_L281_RD_MASK, "SBB_PARAM_L281_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H282_OFFSET, \
                                    SBB_PARAM_H282_DEFAULT, \
                                    SBB_PARAM_H282_RD_MASK, "SBB_PARAM_H282_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L282_OFFSET, \
                                    SBB_PARAM_L282_DEFAULT, \
                                    SBB_PARAM_L282_RD_MASK, "SBB_PARAM_L282_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H283_OFFSET, \
                                    SBB_PARAM_H283_DEFAULT, \
                                    SBB_PARAM_H283_RD_MASK, "SBB_PARAM_H283_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L283_OFFSET, \
                                    SBB_PARAM_L283_DEFAULT, \
                                    SBB_PARAM_L283_RD_MASK, "SBB_PARAM_L283_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H284_OFFSET, \
                                    SBB_PARAM_H284_DEFAULT, \
                                    SBB_PARAM_H284_RD_MASK, "SBB_PARAM_H284_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L284_OFFSET, \
                                    SBB_PARAM_L284_DEFAULT, \
                                    SBB_PARAM_L284_RD_MASK, "SBB_PARAM_L284_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H285_OFFSET, \
                                    SBB_PARAM_H285_DEFAULT, \
                                    SBB_PARAM_H285_RD_MASK, "SBB_PARAM_H285_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L285_OFFSET, \
                                    SBB_PARAM_L285_DEFAULT, \
                                    SBB_PARAM_L285_RD_MASK, "SBB_PARAM_L285_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H286_OFFSET, \
                                    SBB_PARAM_H286_DEFAULT, \
                                    SBB_PARAM_H286_RD_MASK, "SBB_PARAM_H286_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L286_OFFSET, \
                                    SBB_PARAM_L286_DEFAULT, \
                                    SBB_PARAM_L286_RD_MASK, "SBB_PARAM_L286_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H287_OFFSET, \
                                    SBB_PARAM_H287_DEFAULT, \
                                    SBB_PARAM_H287_RD_MASK, "SBB_PARAM_H287_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L287_OFFSET, \
                                    SBB_PARAM_L287_DEFAULT, \
                                    SBB_PARAM_L287_RD_MASK, "SBB_PARAM_L287_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H288_OFFSET, \
                                    SBB_PARAM_H288_DEFAULT, \
                                    SBB_PARAM_H288_RD_MASK, "SBB_PARAM_H288_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L288_OFFSET, \
                                    SBB_PARAM_L288_DEFAULT, \
                                    SBB_PARAM_L288_RD_MASK, "SBB_PARAM_L288_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H289_OFFSET, \
                                    SBB_PARAM_H289_DEFAULT, \
                                    SBB_PARAM_H289_RD_MASK, "SBB_PARAM_H289_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L289_OFFSET, \
                                    SBB_PARAM_L289_DEFAULT, \
                                    SBB_PARAM_L289_RD_MASK, "SBB_PARAM_L289_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H290_OFFSET, \
                                    SBB_PARAM_H290_DEFAULT, \
                                    SBB_PARAM_H290_RD_MASK, "SBB_PARAM_H290_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L290_OFFSET, \
                                    SBB_PARAM_L290_DEFAULT, \
                                    SBB_PARAM_L290_RD_MASK, "SBB_PARAM_L290_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H291_OFFSET, \
                                    SBB_PARAM_H291_DEFAULT, \
                                    SBB_PARAM_H291_RD_MASK, "SBB_PARAM_H291_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L291_OFFSET, \
                                    SBB_PARAM_L291_DEFAULT, \
                                    SBB_PARAM_L291_RD_MASK, "SBB_PARAM_L291_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H292_OFFSET, \
                                    SBB_PARAM_H292_DEFAULT, \
                                    SBB_PARAM_H292_RD_MASK, "SBB_PARAM_H292_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L292_OFFSET, \
                                    SBB_PARAM_L292_DEFAULT, \
                                    SBB_PARAM_L292_RD_MASK, "SBB_PARAM_L292_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H293_OFFSET, \
                                    SBB_PARAM_H293_DEFAULT, \
                                    SBB_PARAM_H293_RD_MASK, "SBB_PARAM_H293_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L293_OFFSET, \
                                    SBB_PARAM_L293_DEFAULT, \
                                    SBB_PARAM_L293_RD_MASK, "SBB_PARAM_L293_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H294_OFFSET, \
                                    SBB_PARAM_H294_DEFAULT, \
                                    SBB_PARAM_H294_RD_MASK, "SBB_PARAM_H294_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L294_OFFSET, \
                                    SBB_PARAM_L294_DEFAULT, \
                                    SBB_PARAM_L294_RD_MASK, "SBB_PARAM_L294_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H295_OFFSET, \
                                    SBB_PARAM_H295_DEFAULT, \
                                    SBB_PARAM_H295_RD_MASK, "SBB_PARAM_H295_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L295_OFFSET, \
                                    SBB_PARAM_L295_DEFAULT, \
                                    SBB_PARAM_L295_RD_MASK, "SBB_PARAM_L295_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H296_OFFSET, \
                                    SBB_PARAM_H296_DEFAULT, \
                                    SBB_PARAM_H296_RD_MASK, "SBB_PARAM_H296_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L296_OFFSET, \
                                    SBB_PARAM_L296_DEFAULT, \
                                    SBB_PARAM_L296_RD_MASK, "SBB_PARAM_L296_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H297_OFFSET, \
                                    SBB_PARAM_H297_DEFAULT, \
                                    SBB_PARAM_H297_RD_MASK, "SBB_PARAM_H297_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L297_OFFSET, \
                                    SBB_PARAM_L297_DEFAULT, \
                                    SBB_PARAM_L297_RD_MASK, "SBB_PARAM_L297_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H298_OFFSET, \
                                    SBB_PARAM_H298_DEFAULT, \
                                    SBB_PARAM_H298_RD_MASK, "SBB_PARAM_H298_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L298_OFFSET, \
                                    SBB_PARAM_L298_DEFAULT, \
                                    SBB_PARAM_L298_RD_MASK, "SBB_PARAM_L298_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H299_OFFSET, \
                                    SBB_PARAM_H299_DEFAULT, \
                                    SBB_PARAM_H299_RD_MASK, "SBB_PARAM_H299_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L299_OFFSET, \
                                    SBB_PARAM_L299_DEFAULT, \
                                    SBB_PARAM_L299_RD_MASK, "SBB_PARAM_L299_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H300_OFFSET, \
                                    SBB_PARAM_H300_DEFAULT, \
                                    SBB_PARAM_H300_RD_MASK, "SBB_PARAM_H300_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L300_OFFSET, \
                                    SBB_PARAM_L300_DEFAULT, \
                                    SBB_PARAM_L300_RD_MASK, "SBB_PARAM_L300_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H301_OFFSET, \
                                    SBB_PARAM_H301_DEFAULT, \
                                    SBB_PARAM_H301_RD_MASK, "SBB_PARAM_H301_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L301_OFFSET, \
                                    SBB_PARAM_L301_DEFAULT, \
                                    SBB_PARAM_L301_RD_MASK, "SBB_PARAM_L301_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H302_OFFSET, \
                                    SBB_PARAM_H302_DEFAULT, \
                                    SBB_PARAM_H302_RD_MASK, "SBB_PARAM_H302_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L302_OFFSET, \
                                    SBB_PARAM_L302_DEFAULT, \
                                    SBB_PARAM_L302_RD_MASK, "SBB_PARAM_L302_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H303_OFFSET, \
                                    SBB_PARAM_H303_DEFAULT, \
                                    SBB_PARAM_H303_RD_MASK, "SBB_PARAM_H303_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L303_OFFSET, \
                                    SBB_PARAM_L303_DEFAULT, \
                                    SBB_PARAM_L303_RD_MASK, "SBB_PARAM_L303_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H304_OFFSET, \
                                    SBB_PARAM_H304_DEFAULT, \
                                    SBB_PARAM_H304_RD_MASK, "SBB_PARAM_H304_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L304_OFFSET, \
                                    SBB_PARAM_L304_DEFAULT, \
                                    SBB_PARAM_L304_RD_MASK, "SBB_PARAM_L304_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H305_OFFSET, \
                                    SBB_PARAM_H305_DEFAULT, \
                                    SBB_PARAM_H305_RD_MASK, "SBB_PARAM_H305_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L305_OFFSET, \
                                    SBB_PARAM_L305_DEFAULT, \
                                    SBB_PARAM_L305_RD_MASK, "SBB_PARAM_L305_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H306_OFFSET, \
                                    SBB_PARAM_H306_DEFAULT, \
                                    SBB_PARAM_H306_RD_MASK, "SBB_PARAM_H306_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L306_OFFSET, \
                                    SBB_PARAM_L306_DEFAULT, \
                                    SBB_PARAM_L306_RD_MASK, "SBB_PARAM_L306_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H307_OFFSET, \
                                    SBB_PARAM_H307_DEFAULT, \
                                    SBB_PARAM_H307_RD_MASK, "SBB_PARAM_H307_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L307_OFFSET, \
                                    SBB_PARAM_L307_DEFAULT, \
                                    SBB_PARAM_L307_RD_MASK, "SBB_PARAM_L307_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H308_OFFSET, \
                                    SBB_PARAM_H308_DEFAULT, \
                                    SBB_PARAM_H308_RD_MASK, "SBB_PARAM_H308_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L308_OFFSET, \
                                    SBB_PARAM_L308_DEFAULT, \
                                    SBB_PARAM_L308_RD_MASK, "SBB_PARAM_L308_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H309_OFFSET, \
                                    SBB_PARAM_H309_DEFAULT, \
                                    SBB_PARAM_H309_RD_MASK, "SBB_PARAM_H309_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L309_OFFSET, \
                                    SBB_PARAM_L309_DEFAULT, \
                                    SBB_PARAM_L309_RD_MASK, "SBB_PARAM_L309_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H310_OFFSET, \
                                    SBB_PARAM_H310_DEFAULT, \
                                    SBB_PARAM_H310_RD_MASK, "SBB_PARAM_H310_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L310_OFFSET, \
                                    SBB_PARAM_L310_DEFAULT, \
                                    SBB_PARAM_L310_RD_MASK, "SBB_PARAM_L310_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H311_OFFSET, \
                                    SBB_PARAM_H311_DEFAULT, \
                                    SBB_PARAM_H311_RD_MASK, "SBB_PARAM_H311_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L311_OFFSET, \
                                    SBB_PARAM_L311_DEFAULT, \
                                    SBB_PARAM_L311_RD_MASK, "SBB_PARAM_L311_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H312_OFFSET, \
                                    SBB_PARAM_H312_DEFAULT, \
                                    SBB_PARAM_H312_RD_MASK, "SBB_PARAM_H312_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L312_OFFSET, \
                                    SBB_PARAM_L312_DEFAULT, \
                                    SBB_PARAM_L312_RD_MASK, "SBB_PARAM_L312_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H313_OFFSET, \
                                    SBB_PARAM_H313_DEFAULT, \
                                    SBB_PARAM_H313_RD_MASK, "SBB_PARAM_H313_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L313_OFFSET, \
                                    SBB_PARAM_L313_DEFAULT, \
                                    SBB_PARAM_L313_RD_MASK, "SBB_PARAM_L313_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H314_OFFSET, \
                                    SBB_PARAM_H314_DEFAULT, \
                                    SBB_PARAM_H314_RD_MASK, "SBB_PARAM_H314_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L314_OFFSET, \
                                    SBB_PARAM_L314_DEFAULT, \
                                    SBB_PARAM_L314_RD_MASK, "SBB_PARAM_L314_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H315_OFFSET, \
                                    SBB_PARAM_H315_DEFAULT, \
                                    SBB_PARAM_H315_RD_MASK, "SBB_PARAM_H315_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L315_OFFSET, \
                                    SBB_PARAM_L315_DEFAULT, \
                                    SBB_PARAM_L315_RD_MASK, "SBB_PARAM_L315_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H316_OFFSET, \
                                    SBB_PARAM_H316_DEFAULT, \
                                    SBB_PARAM_H316_RD_MASK, "SBB_PARAM_H316_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L316_OFFSET, \
                                    SBB_PARAM_L316_DEFAULT, \
                                    SBB_PARAM_L316_RD_MASK, "SBB_PARAM_L316_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H317_OFFSET, \
                                    SBB_PARAM_H317_DEFAULT, \
                                    SBB_PARAM_H317_RD_MASK, "SBB_PARAM_H317_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L317_OFFSET, \
                                    SBB_PARAM_L317_DEFAULT, \
                                    SBB_PARAM_L317_RD_MASK, "SBB_PARAM_L317_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H318_OFFSET, \
                                    SBB_PARAM_H318_DEFAULT, \
                                    SBB_PARAM_H318_RD_MASK, "SBB_PARAM_H318_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L318_OFFSET, \
                                    SBB_PARAM_L318_DEFAULT, \
                                    SBB_PARAM_L318_RD_MASK, "SBB_PARAM_L318_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H319_OFFSET, \
                                    SBB_PARAM_H319_DEFAULT, \
                                    SBB_PARAM_H319_RD_MASK, "SBB_PARAM_H319_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L319_OFFSET, \
                                    SBB_PARAM_L319_DEFAULT, \
                                    SBB_PARAM_L319_RD_MASK, "SBB_PARAM_L319_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H320_OFFSET, \
                                    SBB_PARAM_H320_DEFAULT, \
                                    SBB_PARAM_H320_RD_MASK, "SBB_PARAM_H320_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L320_OFFSET, \
                                    SBB_PARAM_L320_DEFAULT, \
                                    SBB_PARAM_L320_RD_MASK, "SBB_PARAM_L320_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H321_OFFSET, \
                                    SBB_PARAM_H321_DEFAULT, \
                                    SBB_PARAM_H321_RD_MASK, "SBB_PARAM_H321_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L321_OFFSET, \
                                    SBB_PARAM_L321_DEFAULT, \
                                    SBB_PARAM_L321_RD_MASK, "SBB_PARAM_L321_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H322_OFFSET, \
                                    SBB_PARAM_H322_DEFAULT, \
                                    SBB_PARAM_H322_RD_MASK, "SBB_PARAM_H322_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L322_OFFSET, \
                                    SBB_PARAM_L322_DEFAULT, \
                                    SBB_PARAM_L322_RD_MASK, "SBB_PARAM_L322_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H323_OFFSET, \
                                    SBB_PARAM_H323_DEFAULT, \
                                    SBB_PARAM_H323_RD_MASK, "SBB_PARAM_H323_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L323_OFFSET, \
                                    SBB_PARAM_L323_DEFAULT, \
                                    SBB_PARAM_L323_RD_MASK, "SBB_PARAM_L323_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H324_OFFSET, \
                                    SBB_PARAM_H324_DEFAULT, \
                                    SBB_PARAM_H324_RD_MASK, "SBB_PARAM_H324_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L324_OFFSET, \
                                    SBB_PARAM_L324_DEFAULT, \
                                    SBB_PARAM_L324_RD_MASK, "SBB_PARAM_L324_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H325_OFFSET, \
                                    SBB_PARAM_H325_DEFAULT, \
                                    SBB_PARAM_H325_RD_MASK, "SBB_PARAM_H325_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L325_OFFSET, \
                                    SBB_PARAM_L325_DEFAULT, \
                                    SBB_PARAM_L325_RD_MASK, "SBB_PARAM_L325_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H326_OFFSET, \
                                    SBB_PARAM_H326_DEFAULT, \
                                    SBB_PARAM_H326_RD_MASK, "SBB_PARAM_H326_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L326_OFFSET, \
                                    SBB_PARAM_L326_DEFAULT, \
                                    SBB_PARAM_L326_RD_MASK, "SBB_PARAM_L326_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H327_OFFSET, \
                                    SBB_PARAM_H327_DEFAULT, \
                                    SBB_PARAM_H327_RD_MASK, "SBB_PARAM_H327_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L327_OFFSET, \
                                    SBB_PARAM_L327_DEFAULT, \
                                    SBB_PARAM_L327_RD_MASK, "SBB_PARAM_L327_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H328_OFFSET, \
                                    SBB_PARAM_H328_DEFAULT, \
                                    SBB_PARAM_H328_RD_MASK, "SBB_PARAM_H328_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L328_OFFSET, \
                                    SBB_PARAM_L328_DEFAULT, \
                                    SBB_PARAM_L328_RD_MASK, "SBB_PARAM_L328_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H329_OFFSET, \
                                    SBB_PARAM_H329_DEFAULT, \
                                    SBB_PARAM_H329_RD_MASK, "SBB_PARAM_H329_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L329_OFFSET, \
                                    SBB_PARAM_L329_DEFAULT, \
                                    SBB_PARAM_L329_RD_MASK, "SBB_PARAM_L329_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H330_OFFSET, \
                                    SBB_PARAM_H330_DEFAULT, \
                                    SBB_PARAM_H330_RD_MASK, "SBB_PARAM_H330_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L330_OFFSET, \
                                    SBB_PARAM_L330_DEFAULT, \
                                    SBB_PARAM_L330_RD_MASK, "SBB_PARAM_L330_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H331_OFFSET, \
                                    SBB_PARAM_H331_DEFAULT, \
                                    SBB_PARAM_H331_RD_MASK, "SBB_PARAM_H331_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L331_OFFSET, \
                                    SBB_PARAM_L331_DEFAULT, \
                                    SBB_PARAM_L331_RD_MASK, "SBB_PARAM_L331_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H332_OFFSET, \
                                    SBB_PARAM_H332_DEFAULT, \
                                    SBB_PARAM_H332_RD_MASK, "SBB_PARAM_H332_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L332_OFFSET, \
                                    SBB_PARAM_L332_DEFAULT, \
                                    SBB_PARAM_L332_RD_MASK, "SBB_PARAM_L332_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H333_OFFSET, \
                                    SBB_PARAM_H333_DEFAULT, \
                                    SBB_PARAM_H333_RD_MASK, "SBB_PARAM_H333_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L333_OFFSET, \
                                    SBB_PARAM_L333_DEFAULT, \
                                    SBB_PARAM_L333_RD_MASK, "SBB_PARAM_L333_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H334_OFFSET, \
                                    SBB_PARAM_H334_DEFAULT, \
                                    SBB_PARAM_H334_RD_MASK, "SBB_PARAM_H334_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L334_OFFSET, \
                                    SBB_PARAM_L334_DEFAULT, \
                                    SBB_PARAM_L334_RD_MASK, "SBB_PARAM_L334_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H335_OFFSET, \
                                    SBB_PARAM_H335_DEFAULT, \
                                    SBB_PARAM_H335_RD_MASK, "SBB_PARAM_H335_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L335_OFFSET, \
                                    SBB_PARAM_L335_DEFAULT, \
                                    SBB_PARAM_L335_RD_MASK, "SBB_PARAM_L335_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H336_OFFSET, \
                                    SBB_PARAM_H336_DEFAULT, \
                                    SBB_PARAM_H336_RD_MASK, "SBB_PARAM_H336_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L336_OFFSET, \
                                    SBB_PARAM_L336_DEFAULT, \
                                    SBB_PARAM_L336_RD_MASK, "SBB_PARAM_L336_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H337_OFFSET, \
                                    SBB_PARAM_H337_DEFAULT, \
                                    SBB_PARAM_H337_RD_MASK, "SBB_PARAM_H337_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L337_OFFSET, \
                                    SBB_PARAM_L337_DEFAULT, \
                                    SBB_PARAM_L337_RD_MASK, "SBB_PARAM_L337_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H338_OFFSET, \
                                    SBB_PARAM_H338_DEFAULT, \
                                    SBB_PARAM_H338_RD_MASK, "SBB_PARAM_H338_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L338_OFFSET, \
                                    SBB_PARAM_L338_DEFAULT, \
                                    SBB_PARAM_L338_RD_MASK, "SBB_PARAM_L338_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H339_OFFSET, \
                                    SBB_PARAM_H339_DEFAULT, \
                                    SBB_PARAM_H339_RD_MASK, "SBB_PARAM_H339_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L339_OFFSET, \
                                    SBB_PARAM_L339_DEFAULT, \
                                    SBB_PARAM_L339_RD_MASK, "SBB_PARAM_L339_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H340_OFFSET, \
                                    SBB_PARAM_H340_DEFAULT, \
                                    SBB_PARAM_H340_RD_MASK, "SBB_PARAM_H340_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L340_OFFSET, \
                                    SBB_PARAM_L340_DEFAULT, \
                                    SBB_PARAM_L340_RD_MASK, "SBB_PARAM_L340_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H341_OFFSET, \
                                    SBB_PARAM_H341_DEFAULT, \
                                    SBB_PARAM_H341_RD_MASK, "SBB_PARAM_H341_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L341_OFFSET, \
                                    SBB_PARAM_L341_DEFAULT, \
                                    SBB_PARAM_L341_RD_MASK, "SBB_PARAM_L341_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H342_OFFSET, \
                                    SBB_PARAM_H342_DEFAULT, \
                                    SBB_PARAM_H342_RD_MASK, "SBB_PARAM_H342_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L342_OFFSET, \
                                    SBB_PARAM_L342_DEFAULT, \
                                    SBB_PARAM_L342_RD_MASK, "SBB_PARAM_L342_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H343_OFFSET, \
                                    SBB_PARAM_H343_DEFAULT, \
                                    SBB_PARAM_H343_RD_MASK, "SBB_PARAM_H343_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L343_OFFSET, \
                                    SBB_PARAM_L343_DEFAULT, \
                                    SBB_PARAM_L343_RD_MASK, "SBB_PARAM_L343_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H344_OFFSET, \
                                    SBB_PARAM_H344_DEFAULT, \
                                    SBB_PARAM_H344_RD_MASK, "SBB_PARAM_H344_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L344_OFFSET, \
                                    SBB_PARAM_L344_DEFAULT, \
                                    SBB_PARAM_L344_RD_MASK, "SBB_PARAM_L344_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H345_OFFSET, \
                                    SBB_PARAM_H345_DEFAULT, \
                                    SBB_PARAM_H345_RD_MASK, "SBB_PARAM_H345_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L345_OFFSET, \
                                    SBB_PARAM_L345_DEFAULT, \
                                    SBB_PARAM_L345_RD_MASK, "SBB_PARAM_L345_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H346_OFFSET, \
                                    SBB_PARAM_H346_DEFAULT, \
                                    SBB_PARAM_H346_RD_MASK, "SBB_PARAM_H346_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L346_OFFSET, \
                                    SBB_PARAM_L346_DEFAULT, \
                                    SBB_PARAM_L346_RD_MASK, "SBB_PARAM_L346_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H347_OFFSET, \
                                    SBB_PARAM_H347_DEFAULT, \
                                    SBB_PARAM_H347_RD_MASK, "SBB_PARAM_H347_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L347_OFFSET, \
                                    SBB_PARAM_L347_DEFAULT, \
                                    SBB_PARAM_L347_RD_MASK, "SBB_PARAM_L347_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H348_OFFSET, \
                                    SBB_PARAM_H348_DEFAULT, \
                                    SBB_PARAM_H348_RD_MASK, "SBB_PARAM_H348_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L348_OFFSET, \
                                    SBB_PARAM_L348_DEFAULT, \
                                    SBB_PARAM_L348_RD_MASK, "SBB_PARAM_L348_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H349_OFFSET, \
                                    SBB_PARAM_H349_DEFAULT, \
                                    SBB_PARAM_H349_RD_MASK, "SBB_PARAM_H349_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L349_OFFSET, \
                                    SBB_PARAM_L349_DEFAULT, \
                                    SBB_PARAM_L349_RD_MASK, "SBB_PARAM_L349_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H350_OFFSET, \
                                    SBB_PARAM_H350_DEFAULT, \
                                    SBB_PARAM_H350_RD_MASK, "SBB_PARAM_H350_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L350_OFFSET, \
                                    SBB_PARAM_L350_DEFAULT, \
                                    SBB_PARAM_L350_RD_MASK, "SBB_PARAM_L350_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H351_OFFSET, \
                                    SBB_PARAM_H351_DEFAULT, \
                                    SBB_PARAM_H351_RD_MASK, "SBB_PARAM_H351_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L351_OFFSET, \
                                    SBB_PARAM_L351_DEFAULT, \
                                    SBB_PARAM_L351_RD_MASK, "SBB_PARAM_L351_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H352_OFFSET, \
                                    SBB_PARAM_H352_DEFAULT, \
                                    SBB_PARAM_H352_RD_MASK, "SBB_PARAM_H352_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L352_OFFSET, \
                                    SBB_PARAM_L352_DEFAULT, \
                                    SBB_PARAM_L352_RD_MASK, "SBB_PARAM_L352_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H353_OFFSET, \
                                    SBB_PARAM_H353_DEFAULT, \
                                    SBB_PARAM_H353_RD_MASK, "SBB_PARAM_H353_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L353_OFFSET, \
                                    SBB_PARAM_L353_DEFAULT, \
                                    SBB_PARAM_L353_RD_MASK, "SBB_PARAM_L353_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H354_OFFSET, \
                                    SBB_PARAM_H354_DEFAULT, \
                                    SBB_PARAM_H354_RD_MASK, "SBB_PARAM_H354_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L354_OFFSET, \
                                    SBB_PARAM_L354_DEFAULT, \
                                    SBB_PARAM_L354_RD_MASK, "SBB_PARAM_L354_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H355_OFFSET, \
                                    SBB_PARAM_H355_DEFAULT, \
                                    SBB_PARAM_H355_RD_MASK, "SBB_PARAM_H355_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L355_OFFSET, \
                                    SBB_PARAM_L355_DEFAULT, \
                                    SBB_PARAM_L355_RD_MASK, "SBB_PARAM_L355_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H356_OFFSET, \
                                    SBB_PARAM_H356_DEFAULT, \
                                    SBB_PARAM_H356_RD_MASK, "SBB_PARAM_H356_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L356_OFFSET, \
                                    SBB_PARAM_L356_DEFAULT, \
                                    SBB_PARAM_L356_RD_MASK, "SBB_PARAM_L356_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H357_OFFSET, \
                                    SBB_PARAM_H357_DEFAULT, \
                                    SBB_PARAM_H357_RD_MASK, "SBB_PARAM_H357_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L357_OFFSET, \
                                    SBB_PARAM_L357_DEFAULT, \
                                    SBB_PARAM_L357_RD_MASK, "SBB_PARAM_L357_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H358_OFFSET, \
                                    SBB_PARAM_H358_DEFAULT, \
                                    SBB_PARAM_H358_RD_MASK, "SBB_PARAM_H358_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L358_OFFSET, \
                                    SBB_PARAM_L358_DEFAULT, \
                                    SBB_PARAM_L358_RD_MASK, "SBB_PARAM_L358_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H359_OFFSET, \
                                    SBB_PARAM_H359_DEFAULT, \
                                    SBB_PARAM_H359_RD_MASK, "SBB_PARAM_H359_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L359_OFFSET, \
                                    SBB_PARAM_L359_DEFAULT, \
                                    SBB_PARAM_L359_RD_MASK, "SBB_PARAM_L359_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H360_OFFSET, \
                                    SBB_PARAM_H360_DEFAULT, \
                                    SBB_PARAM_H360_RD_MASK, "SBB_PARAM_H360_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L360_OFFSET, \
                                    SBB_PARAM_L360_DEFAULT, \
                                    SBB_PARAM_L360_RD_MASK, "SBB_PARAM_L360_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H361_OFFSET, \
                                    SBB_PARAM_H361_DEFAULT, \
                                    SBB_PARAM_H361_RD_MASK, "SBB_PARAM_H361_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L361_OFFSET, \
                                    SBB_PARAM_L361_DEFAULT, \
                                    SBB_PARAM_L361_RD_MASK, "SBB_PARAM_L361_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H362_OFFSET, \
                                    SBB_PARAM_H362_DEFAULT, \
                                    SBB_PARAM_H362_RD_MASK, "SBB_PARAM_H362_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L362_OFFSET, \
                                    SBB_PARAM_L362_DEFAULT, \
                                    SBB_PARAM_L362_RD_MASK, "SBB_PARAM_L362_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H363_OFFSET, \
                                    SBB_PARAM_H363_DEFAULT, \
                                    SBB_PARAM_H363_RD_MASK, "SBB_PARAM_H363_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L363_OFFSET, \
                                    SBB_PARAM_L363_DEFAULT, \
                                    SBB_PARAM_L363_RD_MASK, "SBB_PARAM_L363_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H364_OFFSET, \
                                    SBB_PARAM_H364_DEFAULT, \
                                    SBB_PARAM_H364_RD_MASK, "SBB_PARAM_H364_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L364_OFFSET, \
                                    SBB_PARAM_L364_DEFAULT, \
                                    SBB_PARAM_L364_RD_MASK, "SBB_PARAM_L364_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H365_OFFSET, \
                                    SBB_PARAM_H365_DEFAULT, \
                                    SBB_PARAM_H365_RD_MASK, "SBB_PARAM_H365_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L365_OFFSET, \
                                    SBB_PARAM_L365_DEFAULT, \
                                    SBB_PARAM_L365_RD_MASK, "SBB_PARAM_L365_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H366_OFFSET, \
                                    SBB_PARAM_H366_DEFAULT, \
                                    SBB_PARAM_H366_RD_MASK, "SBB_PARAM_H366_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L366_OFFSET, \
                                    SBB_PARAM_L366_DEFAULT, \
                                    SBB_PARAM_L366_RD_MASK, "SBB_PARAM_L366_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H367_OFFSET, \
                                    SBB_PARAM_H367_DEFAULT, \
                                    SBB_PARAM_H367_RD_MASK, "SBB_PARAM_H367_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L367_OFFSET, \
                                    SBB_PARAM_L367_DEFAULT, \
                                    SBB_PARAM_L367_RD_MASK, "SBB_PARAM_L367_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H368_OFFSET, \
                                    SBB_PARAM_H368_DEFAULT, \
                                    SBB_PARAM_H368_RD_MASK, "SBB_PARAM_H368_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L368_OFFSET, \
                                    SBB_PARAM_L368_DEFAULT, \
                                    SBB_PARAM_L368_RD_MASK, "SBB_PARAM_L368_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H369_OFFSET, \
                                    SBB_PARAM_H369_DEFAULT, \
                                    SBB_PARAM_H369_RD_MASK, "SBB_PARAM_H369_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L369_OFFSET, \
                                    SBB_PARAM_L369_DEFAULT, \
                                    SBB_PARAM_L369_RD_MASK, "SBB_PARAM_L369_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H370_OFFSET, \
                                    SBB_PARAM_H370_DEFAULT, \
                                    SBB_PARAM_H370_RD_MASK, "SBB_PARAM_H370_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L370_OFFSET, \
                                    SBB_PARAM_L370_DEFAULT, \
                                    SBB_PARAM_L370_RD_MASK, "SBB_PARAM_L370_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H371_OFFSET, \
                                    SBB_PARAM_H371_DEFAULT, \
                                    SBB_PARAM_H371_RD_MASK, "SBB_PARAM_H371_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L371_OFFSET, \
                                    SBB_PARAM_L371_DEFAULT, \
                                    SBB_PARAM_L371_RD_MASK, "SBB_PARAM_L371_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H372_OFFSET, \
                                    SBB_PARAM_H372_DEFAULT, \
                                    SBB_PARAM_H372_RD_MASK, "SBB_PARAM_H372_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L372_OFFSET, \
                                    SBB_PARAM_L372_DEFAULT, \
                                    SBB_PARAM_L372_RD_MASK, "SBB_PARAM_L372_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H373_OFFSET, \
                                    SBB_PARAM_H373_DEFAULT, \
                                    SBB_PARAM_H373_RD_MASK, "SBB_PARAM_H373_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L373_OFFSET, \
                                    SBB_PARAM_L373_DEFAULT, \
                                    SBB_PARAM_L373_RD_MASK, "SBB_PARAM_L373_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H374_OFFSET, \
                                    SBB_PARAM_H374_DEFAULT, \
                                    SBB_PARAM_H374_RD_MASK, "SBB_PARAM_H374_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L374_OFFSET, \
                                    SBB_PARAM_L374_DEFAULT, \
                                    SBB_PARAM_L374_RD_MASK, "SBB_PARAM_L374_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H375_OFFSET, \
                                    SBB_PARAM_H375_DEFAULT, \
                                    SBB_PARAM_H375_RD_MASK, "SBB_PARAM_H375_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L375_OFFSET, \
                                    SBB_PARAM_L375_DEFAULT, \
                                    SBB_PARAM_L375_RD_MASK, "SBB_PARAM_L375_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H376_OFFSET, \
                                    SBB_PARAM_H376_DEFAULT, \
                                    SBB_PARAM_H376_RD_MASK, "SBB_PARAM_H376_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L376_OFFSET, \
                                    SBB_PARAM_L376_DEFAULT, \
                                    SBB_PARAM_L376_RD_MASK, "SBB_PARAM_L376_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H377_OFFSET, \
                                    SBB_PARAM_H377_DEFAULT, \
                                    SBB_PARAM_H377_RD_MASK, "SBB_PARAM_H377_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L377_OFFSET, \
                                    SBB_PARAM_L377_DEFAULT, \
                                    SBB_PARAM_L377_RD_MASK, "SBB_PARAM_L377_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H378_OFFSET, \
                                    SBB_PARAM_H378_DEFAULT, \
                                    SBB_PARAM_H378_RD_MASK, "SBB_PARAM_H378_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L378_OFFSET, \
                                    SBB_PARAM_L378_DEFAULT, \
                                    SBB_PARAM_L378_RD_MASK, "SBB_PARAM_L378_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H379_OFFSET, \
                                    SBB_PARAM_H379_DEFAULT, \
                                    SBB_PARAM_H379_RD_MASK, "SBB_PARAM_H379_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L379_OFFSET, \
                                    SBB_PARAM_L379_DEFAULT, \
                                    SBB_PARAM_L379_RD_MASK, "SBB_PARAM_L379_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H380_OFFSET, \
                                    SBB_PARAM_H380_DEFAULT, \
                                    SBB_PARAM_H380_RD_MASK, "SBB_PARAM_H380_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L380_OFFSET, \
                                    SBB_PARAM_L380_DEFAULT, \
                                    SBB_PARAM_L380_RD_MASK, "SBB_PARAM_L380_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H381_OFFSET, \
                                    SBB_PARAM_H381_DEFAULT, \
                                    SBB_PARAM_H381_RD_MASK, "SBB_PARAM_H381_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L381_OFFSET, \
                                    SBB_PARAM_L381_DEFAULT, \
                                    SBB_PARAM_L381_RD_MASK, "SBB_PARAM_L381_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H382_OFFSET, \
                                    SBB_PARAM_H382_DEFAULT, \
                                    SBB_PARAM_H382_RD_MASK, "SBB_PARAM_H382_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L382_OFFSET, \
                                    SBB_PARAM_L382_DEFAULT, \
                                    SBB_PARAM_L382_RD_MASK, "SBB_PARAM_L382_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H383_OFFSET, \
                                    SBB_PARAM_H383_DEFAULT, \
                                    SBB_PARAM_H383_RD_MASK, "SBB_PARAM_H383_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L383_OFFSET, \
                                    SBB_PARAM_L383_DEFAULT, \
                                    SBB_PARAM_L383_RD_MASK, "SBB_PARAM_L383_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H384_OFFSET, \
                                    SBB_PARAM_H384_DEFAULT, \
                                    SBB_PARAM_H384_RD_MASK, "SBB_PARAM_H384_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L384_OFFSET, \
                                    SBB_PARAM_L384_DEFAULT, \
                                    SBB_PARAM_L384_RD_MASK, "SBB_PARAM_L384_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H385_OFFSET, \
                                    SBB_PARAM_H385_DEFAULT, \
                                    SBB_PARAM_H385_RD_MASK, "SBB_PARAM_H385_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L385_OFFSET, \
                                    SBB_PARAM_L385_DEFAULT, \
                                    SBB_PARAM_L385_RD_MASK, "SBB_PARAM_L385_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H386_OFFSET, \
                                    SBB_PARAM_H386_DEFAULT, \
                                    SBB_PARAM_H386_RD_MASK, "SBB_PARAM_H386_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L386_OFFSET, \
                                    SBB_PARAM_L386_DEFAULT, \
                                    SBB_PARAM_L386_RD_MASK, "SBB_PARAM_L386_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H387_OFFSET, \
                                    SBB_PARAM_H387_DEFAULT, \
                                    SBB_PARAM_H387_RD_MASK, "SBB_PARAM_H387_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L387_OFFSET, \
                                    SBB_PARAM_L387_DEFAULT, \
                                    SBB_PARAM_L387_RD_MASK, "SBB_PARAM_L387_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H388_OFFSET, \
                                    SBB_PARAM_H388_DEFAULT, \
                                    SBB_PARAM_H388_RD_MASK, "SBB_PARAM_H388_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L388_OFFSET, \
                                    SBB_PARAM_L388_DEFAULT, \
                                    SBB_PARAM_L388_RD_MASK, "SBB_PARAM_L388_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H389_OFFSET, \
                                    SBB_PARAM_H389_DEFAULT, \
                                    SBB_PARAM_H389_RD_MASK, "SBB_PARAM_H389_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L389_OFFSET, \
                                    SBB_PARAM_L389_DEFAULT, \
                                    SBB_PARAM_L389_RD_MASK, "SBB_PARAM_L389_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H390_OFFSET, \
                                    SBB_PARAM_H390_DEFAULT, \
                                    SBB_PARAM_H390_RD_MASK, "SBB_PARAM_H390_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L390_OFFSET, \
                                    SBB_PARAM_L390_DEFAULT, \
                                    SBB_PARAM_L390_RD_MASK, "SBB_PARAM_L390_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H391_OFFSET, \
                                    SBB_PARAM_H391_DEFAULT, \
                                    SBB_PARAM_H391_RD_MASK, "SBB_PARAM_H391_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L391_OFFSET, \
                                    SBB_PARAM_L391_DEFAULT, \
                                    SBB_PARAM_L391_RD_MASK, "SBB_PARAM_L391_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H392_OFFSET, \
                                    SBB_PARAM_H392_DEFAULT, \
                                    SBB_PARAM_H392_RD_MASK, "SBB_PARAM_H392_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L392_OFFSET, \
                                    SBB_PARAM_L392_DEFAULT, \
                                    SBB_PARAM_L392_RD_MASK, "SBB_PARAM_L392_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H393_OFFSET, \
                                    SBB_PARAM_H393_DEFAULT, \
                                    SBB_PARAM_H393_RD_MASK, "SBB_PARAM_H393_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L393_OFFSET, \
                                    SBB_PARAM_L393_DEFAULT, \
                                    SBB_PARAM_L393_RD_MASK, "SBB_PARAM_L393_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H394_OFFSET, \
                                    SBB_PARAM_H394_DEFAULT, \
                                    SBB_PARAM_H394_RD_MASK, "SBB_PARAM_H394_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L394_OFFSET, \
                                    SBB_PARAM_L394_DEFAULT, \
                                    SBB_PARAM_L394_RD_MASK, "SBB_PARAM_L394_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H395_OFFSET, \
                                    SBB_PARAM_H395_DEFAULT, \
                                    SBB_PARAM_H395_RD_MASK, "SBB_PARAM_H395_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L395_OFFSET, \
                                    SBB_PARAM_L395_DEFAULT, \
                                    SBB_PARAM_L395_RD_MASK, "SBB_PARAM_L395_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H396_OFFSET, \
                                    SBB_PARAM_H396_DEFAULT, \
                                    SBB_PARAM_H396_RD_MASK, "SBB_PARAM_H396_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L396_OFFSET, \
                                    SBB_PARAM_L396_DEFAULT, \
                                    SBB_PARAM_L396_RD_MASK, "SBB_PARAM_L396_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H397_OFFSET, \
                                    SBB_PARAM_H397_DEFAULT, \
                                    SBB_PARAM_H397_RD_MASK, "SBB_PARAM_H397_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L397_OFFSET, \
                                    SBB_PARAM_L397_DEFAULT, \
                                    SBB_PARAM_L397_RD_MASK, "SBB_PARAM_L397_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H398_OFFSET, \
                                    SBB_PARAM_H398_DEFAULT, \
                                    SBB_PARAM_H398_RD_MASK, "SBB_PARAM_H398_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L398_OFFSET, \
                                    SBB_PARAM_L398_DEFAULT, \
                                    SBB_PARAM_L398_RD_MASK, "SBB_PARAM_L398_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H399_OFFSET, \
                                    SBB_PARAM_H399_DEFAULT, \
                                    SBB_PARAM_H399_RD_MASK, "SBB_PARAM_H399_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L399_OFFSET, \
                                    SBB_PARAM_L399_DEFAULT, \
                                    SBB_PARAM_L399_RD_MASK, "SBB_PARAM_L399_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H400_OFFSET, \
                                    SBB_PARAM_H400_DEFAULT, \
                                    SBB_PARAM_H400_RD_MASK, "SBB_PARAM_H400_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L400_OFFSET, \
                                    SBB_PARAM_L400_DEFAULT, \
                                    SBB_PARAM_L400_RD_MASK, "SBB_PARAM_L400_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H401_OFFSET, \
                                    SBB_PARAM_H401_DEFAULT, \
                                    SBB_PARAM_H401_RD_MASK, "SBB_PARAM_H401_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L401_OFFSET, \
                                    SBB_PARAM_L401_DEFAULT, \
                                    SBB_PARAM_L401_RD_MASK, "SBB_PARAM_L401_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H402_OFFSET, \
                                    SBB_PARAM_H402_DEFAULT, \
                                    SBB_PARAM_H402_RD_MASK, "SBB_PARAM_H402_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L402_OFFSET, \
                                    SBB_PARAM_L402_DEFAULT, \
                                    SBB_PARAM_L402_RD_MASK, "SBB_PARAM_L402_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H403_OFFSET, \
                                    SBB_PARAM_H403_DEFAULT, \
                                    SBB_PARAM_H403_RD_MASK, "SBB_PARAM_H403_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L403_OFFSET, \
                                    SBB_PARAM_L403_DEFAULT, \
                                    SBB_PARAM_L403_RD_MASK, "SBB_PARAM_L403_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H404_OFFSET, \
                                    SBB_PARAM_H404_DEFAULT, \
                                    SBB_PARAM_H404_RD_MASK, "SBB_PARAM_H404_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L404_OFFSET, \
                                    SBB_PARAM_L404_DEFAULT, \
                                    SBB_PARAM_L404_RD_MASK, "SBB_PARAM_L404_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H405_OFFSET, \
                                    SBB_PARAM_H405_DEFAULT, \
                                    SBB_PARAM_H405_RD_MASK, "SBB_PARAM_H405_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L405_OFFSET, \
                                    SBB_PARAM_L405_DEFAULT, \
                                    SBB_PARAM_L405_RD_MASK, "SBB_PARAM_L405_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H406_OFFSET, \
                                    SBB_PARAM_H406_DEFAULT, \
                                    SBB_PARAM_H406_RD_MASK, "SBB_PARAM_H406_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L406_OFFSET, \
                                    SBB_PARAM_L406_DEFAULT, \
                                    SBB_PARAM_L406_RD_MASK, "SBB_PARAM_L406_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H407_OFFSET, \
                                    SBB_PARAM_H407_DEFAULT, \
                                    SBB_PARAM_H407_RD_MASK, "SBB_PARAM_H407_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L407_OFFSET, \
                                    SBB_PARAM_L407_DEFAULT, \
                                    SBB_PARAM_L407_RD_MASK, "SBB_PARAM_L407_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H408_OFFSET, \
                                    SBB_PARAM_H408_DEFAULT, \
                                    SBB_PARAM_H408_RD_MASK, "SBB_PARAM_H408_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L408_OFFSET, \
                                    SBB_PARAM_L408_DEFAULT, \
                                    SBB_PARAM_L408_RD_MASK, "SBB_PARAM_L408_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H409_OFFSET, \
                                    SBB_PARAM_H409_DEFAULT, \
                                    SBB_PARAM_H409_RD_MASK, "SBB_PARAM_H409_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L409_OFFSET, \
                                    SBB_PARAM_L409_DEFAULT, \
                                    SBB_PARAM_L409_RD_MASK, "SBB_PARAM_L409_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H410_OFFSET, \
                                    SBB_PARAM_H410_DEFAULT, \
                                    SBB_PARAM_H410_RD_MASK, "SBB_PARAM_H410_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L410_OFFSET, \
                                    SBB_PARAM_L410_DEFAULT, \
                                    SBB_PARAM_L410_RD_MASK, "SBB_PARAM_L410_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H411_OFFSET, \
                                    SBB_PARAM_H411_DEFAULT, \
                                    SBB_PARAM_H411_RD_MASK, "SBB_PARAM_H411_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L411_OFFSET, \
                                    SBB_PARAM_L411_DEFAULT, \
                                    SBB_PARAM_L411_RD_MASK, "SBB_PARAM_L411_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H412_OFFSET, \
                                    SBB_PARAM_H412_DEFAULT, \
                                    SBB_PARAM_H412_RD_MASK, "SBB_PARAM_H412_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L412_OFFSET, \
                                    SBB_PARAM_L412_DEFAULT, \
                                    SBB_PARAM_L412_RD_MASK, "SBB_PARAM_L412_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H413_OFFSET, \
                                    SBB_PARAM_H413_DEFAULT, \
                                    SBB_PARAM_H413_RD_MASK, "SBB_PARAM_H413_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L413_OFFSET, \
                                    SBB_PARAM_L413_DEFAULT, \
                                    SBB_PARAM_L413_RD_MASK, "SBB_PARAM_L413_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H414_OFFSET, \
                                    SBB_PARAM_H414_DEFAULT, \
                                    SBB_PARAM_H414_RD_MASK, "SBB_PARAM_H414_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L414_OFFSET, \
                                    SBB_PARAM_L414_DEFAULT, \
                                    SBB_PARAM_L414_RD_MASK, "SBB_PARAM_L414_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H415_OFFSET, \
                                    SBB_PARAM_H415_DEFAULT, \
                                    SBB_PARAM_H415_RD_MASK, "SBB_PARAM_H415_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L415_OFFSET, \
                                    SBB_PARAM_L415_DEFAULT, \
                                    SBB_PARAM_L415_RD_MASK, "SBB_PARAM_L415_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H416_OFFSET, \
                                    SBB_PARAM_H416_DEFAULT, \
                                    SBB_PARAM_H416_RD_MASK, "SBB_PARAM_H416_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L416_OFFSET, \
                                    SBB_PARAM_L416_DEFAULT, \
                                    SBB_PARAM_L416_RD_MASK, "SBB_PARAM_L416_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H417_OFFSET, \
                                    SBB_PARAM_H417_DEFAULT, \
                                    SBB_PARAM_H417_RD_MASK, "SBB_PARAM_H417_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L417_OFFSET, \
                                    SBB_PARAM_L417_DEFAULT, \
                                    SBB_PARAM_L417_RD_MASK, "SBB_PARAM_L417_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H418_OFFSET, \
                                    SBB_PARAM_H418_DEFAULT, \
                                    SBB_PARAM_H418_RD_MASK, "SBB_PARAM_H418_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L418_OFFSET, \
                                    SBB_PARAM_L418_DEFAULT, \
                                    SBB_PARAM_L418_RD_MASK, "SBB_PARAM_L418_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H419_OFFSET, \
                                    SBB_PARAM_H419_DEFAULT, \
                                    SBB_PARAM_H419_RD_MASK, "SBB_PARAM_H419_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L419_OFFSET, \
                                    SBB_PARAM_L419_DEFAULT, \
                                    SBB_PARAM_L419_RD_MASK, "SBB_PARAM_L419_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H420_OFFSET, \
                                    SBB_PARAM_H420_DEFAULT, \
                                    SBB_PARAM_H420_RD_MASK, "SBB_PARAM_H420_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L420_OFFSET, \
                                    SBB_PARAM_L420_DEFAULT, \
                                    SBB_PARAM_L420_RD_MASK, "SBB_PARAM_L420_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H421_OFFSET, \
                                    SBB_PARAM_H421_DEFAULT, \
                                    SBB_PARAM_H421_RD_MASK, "SBB_PARAM_H421_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L421_OFFSET, \
                                    SBB_PARAM_L421_DEFAULT, \
                                    SBB_PARAM_L421_RD_MASK, "SBB_PARAM_L421_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H422_OFFSET, \
                                    SBB_PARAM_H422_DEFAULT, \
                                    SBB_PARAM_H422_RD_MASK, "SBB_PARAM_H422_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L422_OFFSET, \
                                    SBB_PARAM_L422_DEFAULT, \
                                    SBB_PARAM_L422_RD_MASK, "SBB_PARAM_L422_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H423_OFFSET, \
                                    SBB_PARAM_H423_DEFAULT, \
                                    SBB_PARAM_H423_RD_MASK, "SBB_PARAM_H423_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L423_OFFSET, \
                                    SBB_PARAM_L423_DEFAULT, \
                                    SBB_PARAM_L423_RD_MASK, "SBB_PARAM_L423_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H424_OFFSET, \
                                    SBB_PARAM_H424_DEFAULT, \
                                    SBB_PARAM_H424_RD_MASK, "SBB_PARAM_H424_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L424_OFFSET, \
                                    SBB_PARAM_L424_DEFAULT, \
                                    SBB_PARAM_L424_RD_MASK, "SBB_PARAM_L424_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H425_OFFSET, \
                                    SBB_PARAM_H425_DEFAULT, \
                                    SBB_PARAM_H425_RD_MASK, "SBB_PARAM_H425_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L425_OFFSET, \
                                    SBB_PARAM_L425_DEFAULT, \
                                    SBB_PARAM_L425_RD_MASK, "SBB_PARAM_L425_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H426_OFFSET, \
                                    SBB_PARAM_H426_DEFAULT, \
                                    SBB_PARAM_H426_RD_MASK, "SBB_PARAM_H426_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L426_OFFSET, \
                                    SBB_PARAM_L426_DEFAULT, \
                                    SBB_PARAM_L426_RD_MASK, "SBB_PARAM_L426_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H427_OFFSET, \
                                    SBB_PARAM_H427_DEFAULT, \
                                    SBB_PARAM_H427_RD_MASK, "SBB_PARAM_H427_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L427_OFFSET, \
                                    SBB_PARAM_L427_DEFAULT, \
                                    SBB_PARAM_L427_RD_MASK, "SBB_PARAM_L427_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H428_OFFSET, \
                                    SBB_PARAM_H428_DEFAULT, \
                                    SBB_PARAM_H428_RD_MASK, "SBB_PARAM_H428_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L428_OFFSET, \
                                    SBB_PARAM_L428_DEFAULT, \
                                    SBB_PARAM_L428_RD_MASK, "SBB_PARAM_L428_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H429_OFFSET, \
                                    SBB_PARAM_H429_DEFAULT, \
                                    SBB_PARAM_H429_RD_MASK, "SBB_PARAM_H429_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L429_OFFSET, \
                                    SBB_PARAM_L429_DEFAULT, \
                                    SBB_PARAM_L429_RD_MASK, "SBB_PARAM_L429_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H430_OFFSET, \
                                    SBB_PARAM_H430_DEFAULT, \
                                    SBB_PARAM_H430_RD_MASK, "SBB_PARAM_H430_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L430_OFFSET, \
                                    SBB_PARAM_L430_DEFAULT, \
                                    SBB_PARAM_L430_RD_MASK, "SBB_PARAM_L430_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H431_OFFSET, \
                                    SBB_PARAM_H431_DEFAULT, \
                                    SBB_PARAM_H431_RD_MASK, "SBB_PARAM_H431_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L431_OFFSET, \
                                    SBB_PARAM_L431_DEFAULT, \
                                    SBB_PARAM_L431_RD_MASK, "SBB_PARAM_L431_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H432_OFFSET, \
                                    SBB_PARAM_H432_DEFAULT, \
                                    SBB_PARAM_H432_RD_MASK, "SBB_PARAM_H432_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L432_OFFSET, \
                                    SBB_PARAM_L432_DEFAULT, \
                                    SBB_PARAM_L432_RD_MASK, "SBB_PARAM_L432_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H433_OFFSET, \
                                    SBB_PARAM_H433_DEFAULT, \
                                    SBB_PARAM_H433_RD_MASK, "SBB_PARAM_H433_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L433_OFFSET, \
                                    SBB_PARAM_L433_DEFAULT, \
                                    SBB_PARAM_L433_RD_MASK, "SBB_PARAM_L433_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H434_OFFSET, \
                                    SBB_PARAM_H434_DEFAULT, \
                                    SBB_PARAM_H434_RD_MASK, "SBB_PARAM_H434_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L434_OFFSET, \
                                    SBB_PARAM_L434_DEFAULT, \
                                    SBB_PARAM_L434_RD_MASK, "SBB_PARAM_L434_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H435_OFFSET, \
                                    SBB_PARAM_H435_DEFAULT, \
                                    SBB_PARAM_H435_RD_MASK, "SBB_PARAM_H435_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L435_OFFSET, \
                                    SBB_PARAM_L435_DEFAULT, \
                                    SBB_PARAM_L435_RD_MASK, "SBB_PARAM_L435_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H436_OFFSET, \
                                    SBB_PARAM_H436_DEFAULT, \
                                    SBB_PARAM_H436_RD_MASK, "SBB_PARAM_H436_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L436_OFFSET, \
                                    SBB_PARAM_L436_DEFAULT, \
                                    SBB_PARAM_L436_RD_MASK, "SBB_PARAM_L436_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H437_OFFSET, \
                                    SBB_PARAM_H437_DEFAULT, \
                                    SBB_PARAM_H437_RD_MASK, "SBB_PARAM_H437_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L437_OFFSET, \
                                    SBB_PARAM_L437_DEFAULT, \
                                    SBB_PARAM_L437_RD_MASK, "SBB_PARAM_L437_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H438_OFFSET, \
                                    SBB_PARAM_H438_DEFAULT, \
                                    SBB_PARAM_H438_RD_MASK, "SBB_PARAM_H438_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L438_OFFSET, \
                                    SBB_PARAM_L438_DEFAULT, \
                                    SBB_PARAM_L438_RD_MASK, "SBB_PARAM_L438_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H439_OFFSET, \
                                    SBB_PARAM_H439_DEFAULT, \
                                    SBB_PARAM_H439_RD_MASK, "SBB_PARAM_H439_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L439_OFFSET, \
                                    SBB_PARAM_L439_DEFAULT, \
                                    SBB_PARAM_L439_RD_MASK, "SBB_PARAM_L439_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H440_OFFSET, \
                                    SBB_PARAM_H440_DEFAULT, \
                                    SBB_PARAM_H440_RD_MASK, "SBB_PARAM_H440_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L440_OFFSET, \
                                    SBB_PARAM_L440_DEFAULT, \
                                    SBB_PARAM_L440_RD_MASK, "SBB_PARAM_L440_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H441_OFFSET, \
                                    SBB_PARAM_H441_DEFAULT, \
                                    SBB_PARAM_H441_RD_MASK, "SBB_PARAM_H441_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L441_OFFSET, \
                                    SBB_PARAM_L441_DEFAULT, \
                                    SBB_PARAM_L441_RD_MASK, "SBB_PARAM_L441_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H442_OFFSET, \
                                    SBB_PARAM_H442_DEFAULT, \
                                    SBB_PARAM_H442_RD_MASK, "SBB_PARAM_H442_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L442_OFFSET, \
                                    SBB_PARAM_L442_DEFAULT, \
                                    SBB_PARAM_L442_RD_MASK, "SBB_PARAM_L442_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H443_OFFSET, \
                                    SBB_PARAM_H443_DEFAULT, \
                                    SBB_PARAM_H443_RD_MASK, "SBB_PARAM_H443_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L443_OFFSET, \
                                    SBB_PARAM_L443_DEFAULT, \
                                    SBB_PARAM_L443_RD_MASK, "SBB_PARAM_L443_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H444_OFFSET, \
                                    SBB_PARAM_H444_DEFAULT, \
                                    SBB_PARAM_H444_RD_MASK, "SBB_PARAM_H444_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L444_OFFSET, \
                                    SBB_PARAM_L444_DEFAULT, \
                                    SBB_PARAM_L444_RD_MASK, "SBB_PARAM_L444_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H445_OFFSET, \
                                    SBB_PARAM_H445_DEFAULT, \
                                    SBB_PARAM_H445_RD_MASK, "SBB_PARAM_H445_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L445_OFFSET, \
                                    SBB_PARAM_L445_DEFAULT, \
                                    SBB_PARAM_L445_RD_MASK, "SBB_PARAM_L445_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H446_OFFSET, \
                                    SBB_PARAM_H446_DEFAULT, \
                                    SBB_PARAM_H446_RD_MASK, "SBB_PARAM_H446_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L446_OFFSET, \
                                    SBB_PARAM_L446_DEFAULT, \
                                    SBB_PARAM_L446_RD_MASK, "SBB_PARAM_L446_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H447_OFFSET, \
                                    SBB_PARAM_H447_DEFAULT, \
                                    SBB_PARAM_H447_RD_MASK, "SBB_PARAM_H447_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L447_OFFSET, \
                                    SBB_PARAM_L447_DEFAULT, \
                                    SBB_PARAM_L447_RD_MASK, "SBB_PARAM_L447_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H448_OFFSET, \
                                    SBB_PARAM_H448_DEFAULT, \
                                    SBB_PARAM_H448_RD_MASK, "SBB_PARAM_H448_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L448_OFFSET, \
                                    SBB_PARAM_L448_DEFAULT, \
                                    SBB_PARAM_L448_RD_MASK, "SBB_PARAM_L448_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H449_OFFSET, \
                                    SBB_PARAM_H449_DEFAULT, \
                                    SBB_PARAM_H449_RD_MASK, "SBB_PARAM_H449_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L449_OFFSET, \
                                    SBB_PARAM_L449_DEFAULT, \
                                    SBB_PARAM_L449_RD_MASK, "SBB_PARAM_L449_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H450_OFFSET, \
                                    SBB_PARAM_H450_DEFAULT, \
                                    SBB_PARAM_H450_RD_MASK, "SBB_PARAM_H450_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L450_OFFSET, \
                                    SBB_PARAM_L450_DEFAULT, \
                                    SBB_PARAM_L450_RD_MASK, "SBB_PARAM_L450_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H451_OFFSET, \
                                    SBB_PARAM_H451_DEFAULT, \
                                    SBB_PARAM_H451_RD_MASK, "SBB_PARAM_H451_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L451_OFFSET, \
                                    SBB_PARAM_L451_DEFAULT, \
                                    SBB_PARAM_L451_RD_MASK, "SBB_PARAM_L451_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H452_OFFSET, \
                                    SBB_PARAM_H452_DEFAULT, \
                                    SBB_PARAM_H452_RD_MASK, "SBB_PARAM_H452_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L452_OFFSET, \
                                    SBB_PARAM_L452_DEFAULT, \
                                    SBB_PARAM_L452_RD_MASK, "SBB_PARAM_L452_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H453_OFFSET, \
                                    SBB_PARAM_H453_DEFAULT, \
                                    SBB_PARAM_H453_RD_MASK, "SBB_PARAM_H453_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L453_OFFSET, \
                                    SBB_PARAM_L453_DEFAULT, \
                                    SBB_PARAM_L453_RD_MASK, "SBB_PARAM_L453_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H454_OFFSET, \
                                    SBB_PARAM_H454_DEFAULT, \
                                    SBB_PARAM_H454_RD_MASK, "SBB_PARAM_H454_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L454_OFFSET, \
                                    SBB_PARAM_L454_DEFAULT, \
                                    SBB_PARAM_L454_RD_MASK, "SBB_PARAM_L454_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H455_OFFSET, \
                                    SBB_PARAM_H455_DEFAULT, \
                                    SBB_PARAM_H455_RD_MASK, "SBB_PARAM_H455_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L455_OFFSET, \
                                    SBB_PARAM_L455_DEFAULT, \
                                    SBB_PARAM_L455_RD_MASK, "SBB_PARAM_L455_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H456_OFFSET, \
                                    SBB_PARAM_H456_DEFAULT, \
                                    SBB_PARAM_H456_RD_MASK, "SBB_PARAM_H456_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L456_OFFSET, \
                                    SBB_PARAM_L456_DEFAULT, \
                                    SBB_PARAM_L456_RD_MASK, "SBB_PARAM_L456_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H457_OFFSET, \
                                    SBB_PARAM_H457_DEFAULT, \
                                    SBB_PARAM_H457_RD_MASK, "SBB_PARAM_H457_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L457_OFFSET, \
                                    SBB_PARAM_L457_DEFAULT, \
                                    SBB_PARAM_L457_RD_MASK, "SBB_PARAM_L457_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H458_OFFSET, \
                                    SBB_PARAM_H458_DEFAULT, \
                                    SBB_PARAM_H458_RD_MASK, "SBB_PARAM_H458_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L458_OFFSET, \
                                    SBB_PARAM_L458_DEFAULT, \
                                    SBB_PARAM_L458_RD_MASK, "SBB_PARAM_L458_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H459_OFFSET, \
                                    SBB_PARAM_H459_DEFAULT, \
                                    SBB_PARAM_H459_RD_MASK, "SBB_PARAM_H459_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L459_OFFSET, \
                                    SBB_PARAM_L459_DEFAULT, \
                                    SBB_PARAM_L459_RD_MASK, "SBB_PARAM_L459_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H460_OFFSET, \
                                    SBB_PARAM_H460_DEFAULT, \
                                    SBB_PARAM_H460_RD_MASK, "SBB_PARAM_H460_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L460_OFFSET, \
                                    SBB_PARAM_L460_DEFAULT, \
                                    SBB_PARAM_L460_RD_MASK, "SBB_PARAM_L460_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H461_OFFSET, \
                                    SBB_PARAM_H461_DEFAULT, \
                                    SBB_PARAM_H461_RD_MASK, "SBB_PARAM_H461_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L461_OFFSET, \
                                    SBB_PARAM_L461_DEFAULT, \
                                    SBB_PARAM_L461_RD_MASK, "SBB_PARAM_L461_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H462_OFFSET, \
                                    SBB_PARAM_H462_DEFAULT, \
                                    SBB_PARAM_H462_RD_MASK, "SBB_PARAM_H462_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L462_OFFSET, \
                                    SBB_PARAM_L462_DEFAULT, \
                                    SBB_PARAM_L462_RD_MASK, "SBB_PARAM_L462_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H463_OFFSET, \
                                    SBB_PARAM_H463_DEFAULT, \
                                    SBB_PARAM_H463_RD_MASK, "SBB_PARAM_H463_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L463_OFFSET, \
                                    SBB_PARAM_L463_DEFAULT, \
                                    SBB_PARAM_L463_RD_MASK, "SBB_PARAM_L463_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H464_OFFSET, \
                                    SBB_PARAM_H464_DEFAULT, \
                                    SBB_PARAM_H464_RD_MASK, "SBB_PARAM_H464_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L464_OFFSET, \
                                    SBB_PARAM_L464_DEFAULT, \
                                    SBB_PARAM_L464_RD_MASK, "SBB_PARAM_L464_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H465_OFFSET, \
                                    SBB_PARAM_H465_DEFAULT, \
                                    SBB_PARAM_H465_RD_MASK, "SBB_PARAM_H465_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L465_OFFSET, \
                                    SBB_PARAM_L465_DEFAULT, \
                                    SBB_PARAM_L465_RD_MASK, "SBB_PARAM_L465_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H466_OFFSET, \
                                    SBB_PARAM_H466_DEFAULT, \
                                    SBB_PARAM_H466_RD_MASK, "SBB_PARAM_H466_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L466_OFFSET, \
                                    SBB_PARAM_L466_DEFAULT, \
                                    SBB_PARAM_L466_RD_MASK, "SBB_PARAM_L466_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H467_OFFSET, \
                                    SBB_PARAM_H467_DEFAULT, \
                                    SBB_PARAM_H467_RD_MASK, "SBB_PARAM_H467_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L467_OFFSET, \
                                    SBB_PARAM_L467_DEFAULT, \
                                    SBB_PARAM_L467_RD_MASK, "SBB_PARAM_L467_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H468_OFFSET, \
                                    SBB_PARAM_H468_DEFAULT, \
                                    SBB_PARAM_H468_RD_MASK, "SBB_PARAM_H468_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L468_OFFSET, \
                                    SBB_PARAM_L468_DEFAULT, \
                                    SBB_PARAM_L468_RD_MASK, "SBB_PARAM_L468_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H469_OFFSET, \
                                    SBB_PARAM_H469_DEFAULT, \
                                    SBB_PARAM_H469_RD_MASK, "SBB_PARAM_H469_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L469_OFFSET, \
                                    SBB_PARAM_L469_DEFAULT, \
                                    SBB_PARAM_L469_RD_MASK, "SBB_PARAM_L469_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H470_OFFSET, \
                                    SBB_PARAM_H470_DEFAULT, \
                                    SBB_PARAM_H470_RD_MASK, "SBB_PARAM_H470_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L470_OFFSET, \
                                    SBB_PARAM_L470_DEFAULT, \
                                    SBB_PARAM_L470_RD_MASK, "SBB_PARAM_L470_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H471_OFFSET, \
                                    SBB_PARAM_H471_DEFAULT, \
                                    SBB_PARAM_H471_RD_MASK, "SBB_PARAM_H471_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L471_OFFSET, \
                                    SBB_PARAM_L471_DEFAULT, \
                                    SBB_PARAM_L471_RD_MASK, "SBB_PARAM_L471_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H472_OFFSET, \
                                    SBB_PARAM_H472_DEFAULT, \
                                    SBB_PARAM_H472_RD_MASK, "SBB_PARAM_H472_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L472_OFFSET, \
                                    SBB_PARAM_L472_DEFAULT, \
                                    SBB_PARAM_L472_RD_MASK, "SBB_PARAM_L472_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H473_OFFSET, \
                                    SBB_PARAM_H473_DEFAULT, \
                                    SBB_PARAM_H473_RD_MASK, "SBB_PARAM_H473_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L473_OFFSET, \
                                    SBB_PARAM_L473_DEFAULT, \
                                    SBB_PARAM_L473_RD_MASK, "SBB_PARAM_L473_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H474_OFFSET, \
                                    SBB_PARAM_H474_DEFAULT, \
                                    SBB_PARAM_H474_RD_MASK, "SBB_PARAM_H474_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L474_OFFSET, \
                                    SBB_PARAM_L474_DEFAULT, \
                                    SBB_PARAM_L474_RD_MASK, "SBB_PARAM_L474_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H475_OFFSET, \
                                    SBB_PARAM_H475_DEFAULT, \
                                    SBB_PARAM_H475_RD_MASK, "SBB_PARAM_H475_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L475_OFFSET, \
                                    SBB_PARAM_L475_DEFAULT, \
                                    SBB_PARAM_L475_RD_MASK, "SBB_PARAM_L475_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H476_OFFSET, \
                                    SBB_PARAM_H476_DEFAULT, \
                                    SBB_PARAM_H476_RD_MASK, "SBB_PARAM_H476_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L476_OFFSET, \
                                    SBB_PARAM_L476_DEFAULT, \
                                    SBB_PARAM_L476_RD_MASK, "SBB_PARAM_L476_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H477_OFFSET, \
                                    SBB_PARAM_H477_DEFAULT, \
                                    SBB_PARAM_H477_RD_MASK, "SBB_PARAM_H477_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L477_OFFSET, \
                                    SBB_PARAM_L477_DEFAULT, \
                                    SBB_PARAM_L477_RD_MASK, "SBB_PARAM_L477_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H478_OFFSET, \
                                    SBB_PARAM_H478_DEFAULT, \
                                    SBB_PARAM_H478_RD_MASK, "SBB_PARAM_H478_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L478_OFFSET, \
                                    SBB_PARAM_L478_DEFAULT, \
                                    SBB_PARAM_L478_RD_MASK, "SBB_PARAM_L478_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H479_OFFSET, \
                                    SBB_PARAM_H479_DEFAULT, \
                                    SBB_PARAM_H479_RD_MASK, "SBB_PARAM_H479_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L479_OFFSET, \
                                    SBB_PARAM_L479_DEFAULT, \
                                    SBB_PARAM_L479_RD_MASK, "SBB_PARAM_L479_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H480_OFFSET, \
                                    SBB_PARAM_H480_DEFAULT, \
                                    SBB_PARAM_H480_RD_MASK, "SBB_PARAM_H480_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L480_OFFSET, \
                                    SBB_PARAM_L480_DEFAULT, \
                                    SBB_PARAM_L480_RD_MASK, "SBB_PARAM_L480_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H481_OFFSET, \
                                    SBB_PARAM_H481_DEFAULT, \
                                    SBB_PARAM_H481_RD_MASK, "SBB_PARAM_H481_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L481_OFFSET, \
                                    SBB_PARAM_L481_DEFAULT, \
                                    SBB_PARAM_L481_RD_MASK, "SBB_PARAM_L481_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H482_OFFSET, \
                                    SBB_PARAM_H482_DEFAULT, \
                                    SBB_PARAM_H482_RD_MASK, "SBB_PARAM_H482_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L482_OFFSET, \
                                    SBB_PARAM_L482_DEFAULT, \
                                    SBB_PARAM_L482_RD_MASK, "SBB_PARAM_L482_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H483_OFFSET, \
                                    SBB_PARAM_H483_DEFAULT, \
                                    SBB_PARAM_H483_RD_MASK, "SBB_PARAM_H483_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L483_OFFSET, \
                                    SBB_PARAM_L483_DEFAULT, \
                                    SBB_PARAM_L483_RD_MASK, "SBB_PARAM_L483_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H484_OFFSET, \
                                    SBB_PARAM_H484_DEFAULT, \
                                    SBB_PARAM_H484_RD_MASK, "SBB_PARAM_H484_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L484_OFFSET, \
                                    SBB_PARAM_L484_DEFAULT, \
                                    SBB_PARAM_L484_RD_MASK, "SBB_PARAM_L484_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H485_OFFSET, \
                                    SBB_PARAM_H485_DEFAULT, \
                                    SBB_PARAM_H485_RD_MASK, "SBB_PARAM_H485_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L485_OFFSET, \
                                    SBB_PARAM_L485_DEFAULT, \
                                    SBB_PARAM_L485_RD_MASK, "SBB_PARAM_L485_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H486_OFFSET, \
                                    SBB_PARAM_H486_DEFAULT, \
                                    SBB_PARAM_H486_RD_MASK, "SBB_PARAM_H486_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L486_OFFSET, \
                                    SBB_PARAM_L486_DEFAULT, \
                                    SBB_PARAM_L486_RD_MASK, "SBB_PARAM_L486_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H487_OFFSET, \
                                    SBB_PARAM_H487_DEFAULT, \
                                    SBB_PARAM_H487_RD_MASK, "SBB_PARAM_H487_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L487_OFFSET, \
                                    SBB_PARAM_L487_DEFAULT, \
                                    SBB_PARAM_L487_RD_MASK, "SBB_PARAM_L487_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H488_OFFSET, \
                                    SBB_PARAM_H488_DEFAULT, \
                                    SBB_PARAM_H488_RD_MASK, "SBB_PARAM_H488_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L488_OFFSET, \
                                    SBB_PARAM_L488_DEFAULT, \
                                    SBB_PARAM_L488_RD_MASK, "SBB_PARAM_L488_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H489_OFFSET, \
                                    SBB_PARAM_H489_DEFAULT, \
                                    SBB_PARAM_H489_RD_MASK, "SBB_PARAM_H489_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L489_OFFSET, \
                                    SBB_PARAM_L489_DEFAULT, \
                                    SBB_PARAM_L489_RD_MASK, "SBB_PARAM_L489_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H490_OFFSET, \
                                    SBB_PARAM_H490_DEFAULT, \
                                    SBB_PARAM_H490_RD_MASK, "SBB_PARAM_H490_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L490_OFFSET, \
                                    SBB_PARAM_L490_DEFAULT, \
                                    SBB_PARAM_L490_RD_MASK, "SBB_PARAM_L490_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H491_OFFSET, \
                                    SBB_PARAM_H491_DEFAULT, \
                                    SBB_PARAM_H491_RD_MASK, "SBB_PARAM_H491_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L491_OFFSET, \
                                    SBB_PARAM_L491_DEFAULT, \
                                    SBB_PARAM_L491_RD_MASK, "SBB_PARAM_L491_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H492_OFFSET, \
                                    SBB_PARAM_H492_DEFAULT, \
                                    SBB_PARAM_H492_RD_MASK, "SBB_PARAM_H492_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L492_OFFSET, \
                                    SBB_PARAM_L492_DEFAULT, \
                                    SBB_PARAM_L492_RD_MASK, "SBB_PARAM_L492_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H493_OFFSET, \
                                    SBB_PARAM_H493_DEFAULT, \
                                    SBB_PARAM_H493_RD_MASK, "SBB_PARAM_H493_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L493_OFFSET, \
                                    SBB_PARAM_L493_DEFAULT, \
                                    SBB_PARAM_L493_RD_MASK, "SBB_PARAM_L493_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H494_OFFSET, \
                                    SBB_PARAM_H494_DEFAULT, \
                                    SBB_PARAM_H494_RD_MASK, "SBB_PARAM_H494_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L494_OFFSET, \
                                    SBB_PARAM_L494_DEFAULT, \
                                    SBB_PARAM_L494_RD_MASK, "SBB_PARAM_L494_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H495_OFFSET, \
                                    SBB_PARAM_H495_DEFAULT, \
                                    SBB_PARAM_H495_RD_MASK, "SBB_PARAM_H495_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L495_OFFSET, \
                                    SBB_PARAM_L495_DEFAULT, \
                                    SBB_PARAM_L495_RD_MASK, "SBB_PARAM_L495_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H496_OFFSET, \
                                    SBB_PARAM_H496_DEFAULT, \
                                    SBB_PARAM_H496_RD_MASK, "SBB_PARAM_H496_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L496_OFFSET, \
                                    SBB_PARAM_L496_DEFAULT, \
                                    SBB_PARAM_L496_RD_MASK, "SBB_PARAM_L496_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H497_OFFSET, \
                                    SBB_PARAM_H497_DEFAULT, \
                                    SBB_PARAM_H497_RD_MASK, "SBB_PARAM_H497_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L497_OFFSET, \
                                    SBB_PARAM_L497_DEFAULT, \
                                    SBB_PARAM_L497_RD_MASK, "SBB_PARAM_L497_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H498_OFFSET, \
                                    SBB_PARAM_H498_DEFAULT, \
                                    SBB_PARAM_H498_RD_MASK, "SBB_PARAM_H498_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L498_OFFSET, \
                                    SBB_PARAM_L498_DEFAULT, \
                                    SBB_PARAM_L498_RD_MASK, "SBB_PARAM_L498_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H499_OFFSET, \
                                    SBB_PARAM_H499_DEFAULT, \
                                    SBB_PARAM_H499_RD_MASK, "SBB_PARAM_H499_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L499_OFFSET, \
                                    SBB_PARAM_L499_DEFAULT, \
                                    SBB_PARAM_L499_RD_MASK, "SBB_PARAM_L499_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H500_OFFSET, \
                                    SBB_PARAM_H500_DEFAULT, \
                                    SBB_PARAM_H500_RD_MASK, "SBB_PARAM_H500_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L500_OFFSET, \
                                    SBB_PARAM_L500_DEFAULT, \
                                    SBB_PARAM_L500_RD_MASK, "SBB_PARAM_L500_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H501_OFFSET, \
                                    SBB_PARAM_H501_DEFAULT, \
                                    SBB_PARAM_H501_RD_MASK, "SBB_PARAM_H501_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L501_OFFSET, \
                                    SBB_PARAM_L501_DEFAULT, \
                                    SBB_PARAM_L501_RD_MASK, "SBB_PARAM_L501_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H502_OFFSET, \
                                    SBB_PARAM_H502_DEFAULT, \
                                    SBB_PARAM_H502_RD_MASK, "SBB_PARAM_H502_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L502_OFFSET, \
                                    SBB_PARAM_L502_DEFAULT, \
                                    SBB_PARAM_L502_RD_MASK, "SBB_PARAM_L502_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H503_OFFSET, \
                                    SBB_PARAM_H503_DEFAULT, \
                                    SBB_PARAM_H503_RD_MASK, "SBB_PARAM_H503_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L503_OFFSET, \
                                    SBB_PARAM_L503_DEFAULT, \
                                    SBB_PARAM_L503_RD_MASK, "SBB_PARAM_L503_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H504_OFFSET, \
                                    SBB_PARAM_H504_DEFAULT, \
                                    SBB_PARAM_H504_RD_MASK, "SBB_PARAM_H504_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L504_OFFSET, \
                                    SBB_PARAM_L504_DEFAULT, \
                                    SBB_PARAM_L504_RD_MASK, "SBB_PARAM_L504_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H505_OFFSET, \
                                    SBB_PARAM_H505_DEFAULT, \
                                    SBB_PARAM_H505_RD_MASK, "SBB_PARAM_H505_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L505_OFFSET, \
                                    SBB_PARAM_L505_DEFAULT, \
                                    SBB_PARAM_L505_RD_MASK, "SBB_PARAM_L505_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H506_OFFSET, \
                                    SBB_PARAM_H506_DEFAULT, \
                                    SBB_PARAM_H506_RD_MASK, "SBB_PARAM_H506_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L506_OFFSET, \
                                    SBB_PARAM_L506_DEFAULT, \
                                    SBB_PARAM_L506_RD_MASK, "SBB_PARAM_L506_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H507_OFFSET, \
                                    SBB_PARAM_H507_DEFAULT, \
                                    SBB_PARAM_H507_RD_MASK, "SBB_PARAM_H507_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L507_OFFSET, \
                                    SBB_PARAM_L507_DEFAULT, \
                                    SBB_PARAM_L507_RD_MASK, "SBB_PARAM_L507_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H508_OFFSET, \
                                    SBB_PARAM_H508_DEFAULT, \
                                    SBB_PARAM_H508_RD_MASK, "SBB_PARAM_H508_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L508_OFFSET, \
                                    SBB_PARAM_L508_DEFAULT, \
                                    SBB_PARAM_L508_RD_MASK, "SBB_PARAM_L508_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H509_OFFSET, \
                                    SBB_PARAM_H509_DEFAULT, \
                                    SBB_PARAM_H509_RD_MASK, "SBB_PARAM_H509_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L509_OFFSET, \
                                    SBB_PARAM_L509_DEFAULT, \
                                    SBB_PARAM_L509_RD_MASK, "SBB_PARAM_L509_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H510_OFFSET, \
                                    SBB_PARAM_H510_DEFAULT, \
                                    SBB_PARAM_H510_RD_MASK, "SBB_PARAM_H510_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L510_OFFSET, \
                                    SBB_PARAM_L510_DEFAULT, \
                                    SBB_PARAM_L510_RD_MASK, "SBB_PARAM_L510_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_H511_OFFSET, \
                                    SBB_PARAM_H511_DEFAULT, \
                                    SBB_PARAM_H511_RD_MASK, "SBB_PARAM_H511_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PARAM_L511_OFFSET, \
                                    SBB_PARAM_L511_DEFAULT, \
                                    SBB_PARAM_L511_RD_MASK, "SBB_PARAM_L511_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_DBG_STAT_OFFSET, \
                                    SBB_DBG_STAT_DEFAULT, \
                                    SBB_DBG_STAT_RD_MASK, "SBB_DBG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_INVLD_INST_ADDR_OFFSET, \
                                    SBB_INVLD_INST_ADDR_DEFAULT, \
                                    SBB_INVLD_INST_ADDR_RD_MASK, "SBB_INVLD_INST_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_PC_DATA_ADDR_OFFSET, \
                                    SBB_PC_DATA_ADDR_DEFAULT, \
                                    SBB_PC_DATA_ADDR_RD_MASK, "SBB_PC_DATA_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_DEC_STG_PC_OFFSET, \
                                    SBB_DEC_STG_PC_DEFAULT, \
                                    SBB_DEC_STG_PC_RD_MASK, "SBB_DEC_STG_PC_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_DEC_STG_OPCODE_OFFSET, \
                                    SBB_DEC_STG_OPCODE_DEFAULT, \
                                    SBB_DEC_STG_OPCODE_RD_MASK, "SBB_DEC_STG_OPCODE_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_ISS_STG_PC_OFFSET, \
                                    SBB_ISS_STG_PC_DEFAULT, \
                                    SBB_ISS_STG_PC_RD_MASK, "SBB_ISS_STG_PC_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_ISS_STG_OPCODE_OFFSET, \
                                    SBB_ISS_STG_OPCODE_DEFAULT, \
                                    SBB_ISS_STG_OPCODE_RD_MASK, "SBB_ISS_STG_OPCODE_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_STG_STAT_OFFSET, \
                                    SBB_STG_STAT_DEFAULT, \
                                    SBB_STG_STAT_RD_MASK, "SBB_STG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_FREG_HEADPTR_OFFSET, \
                                    SBB_FREG_HEADPTR_DEFAULT, \
                                    SBB_FREG_HEADPTR_RD_MASK, "SBB_FREG_HEADPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_FREG_TAILPTR_OFFSET, \
                                    SBB_FREG_TAILPTR_DEFAULT, \
                                    SBB_FREG_TAILPTR_RD_MASK, "SBB_FREG_TAILPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_HEADPTR_OFFSET, \
                                    SBB_IN_FIFO_HEADPTR_DEFAULT, \
                                    SBB_IN_FIFO_HEADPTR_RD_MASK, "SBB_IN_FIFO_HEADPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_TAILPTR_OFFSET, \
                                    SBB_IN_FIFO_TAILPTR_DEFAULT, \
                                    SBB_IN_FIFO_TAILPTR_RD_MASK, "SBB_IN_FIFO_TAILPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_HEADPTR_OFFSET, \
                                    SBB_OUT_FIFO_HEADPTR_DEFAULT, \
                                    SBB_OUT_FIFO_HEADPTR_RD_MASK, "SBB_OUT_FIFO_HEADPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_TAILPTR_OFFSET, \
                                    SBB_OUT_FIFO_TAILPTR_DEFAULT, \
                                    SBB_OUT_FIFO_TAILPTR_RD_MASK, "SBB_OUT_FIFO_TAILPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_STGMEM_FIFO_HEADPTR_OFFSET, \
                                    SBB_STGMEM_FIFO_HEADPTR_DEFAULT, \
                                    SBB_STGMEM_FIFO_HEADPTR_RD_MASK, "SBB_STGMEM_FIFO_HEADPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_STGMEM_FIFO_TAILPTR_OFFSET, \
                                    SBB_STGMEM_FIFO_TAILPTR_DEFAULT, \
                                    SBB_STGMEM_FIFO_TAILPTR_RD_MASK, "SBB_STGMEM_FIFO_TAILPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_CPI_H_OFFSET, \
                                    SBB_CPI_H_DEFAULT, \
                                    SBB_CPI_H_RD_MASK, "SBB_CPI_H_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_CPI_L_OFFSET, \
                                    SBB_CPI_L_DEFAULT, \
                                    SBB_CPI_L_RD_MASK, "SBB_CPI_L_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IREG_H_OFFSET, \
                                    SBB_IREG_H_DEFAULT, \
                                    SBB_IREG_H_RD_MASK, "SBB_IREG_H_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IREG_L_OFFSET, \
                                    SBB_IREG_L_DEFAULT, \
                                    SBB_IREG_L_RD_MASK, "SBB_IREG_L_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_HOF_H_OFFSET, \
                                    SBB_IN_FIFO_HOF_H_DEFAULT, \
                                    SBB_IN_FIFO_HOF_H_RD_MASK, "SBB_IN_FIFO_HOF_H_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_HOF_L_OFFSET, \
                                    SBB_IN_FIFO_HOF_L_DEFAULT, \
                                    SBB_IN_FIFO_HOF_L_RD_MASK, "SBB_IN_FIFO_HOF_L_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_HOF_H_OFFSET, \
                                    SBB_OUT_FIFO_HOF_H_DEFAULT, \
                                    SBB_OUT_FIFO_HOF_H_RD_MASK, "SBB_OUT_FIFO_HOF_H_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_HOF_L_OFFSET, \
                                    SBB_OUT_FIFO_HOF_L_DEFAULT, \
                                    SBB_OUT_FIFO_HOF_L_RD_MASK, "SBB_OUT_FIFO_HOF_L_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_FIFO_OU_STS_OFFSET, \
                                    SBB_FIFO_OU_STS_DEFAULT, \
                                    SBB_FIFO_OU_STS_RD_MASK, "SBB_FIFO_OU_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_FIFO_FE_STS_OFFSET, \
                                    SBB_FIFO_FE_STS_DEFAULT, \
                                    SBB_FIFO_FE_STS_RD_MASK, "SBB_FIFO_FE_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_GENERAL_STAT_OFFSET, \
                                    SBB_GENERAL_STAT_DEFAULT, \
                                    SBB_GENERAL_STAT_RD_MASK, "SBB_GENERAL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_CLR_MEM_OFFSET, \
                                    SBB_CLR_MEM_DEFAULT, \
                                    SBB_CLR_MEM_RD_MASK, "SBB_CLR_MEM_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_AXI_CTRL_OFFSET, \
                                    SBB_AXI_CTRL_DEFAULT, \
                                    SBB_AXI_CTRL_RD_MASK, "SBB_AXI_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_NS_RESEED_CNTER_OFFSET, \
                                    SBB_NS_RESEED_CNTER_DEFAULT, \
                                    SBB_NS_RESEED_CNTER_RD_MASK, "SBB_NS_RESEED_CNTER_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H0_OFFSET, \
                                    SBB_IN_FIFO_H0_DEFAULT, \
                                    SBB_IN_FIFO_H0_RD_MASK, "SBB_IN_FIFO_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L0_OFFSET, \
                                    SBB_IN_FIFO_L0_DEFAULT, \
                                    SBB_IN_FIFO_L0_RD_MASK, "SBB_IN_FIFO_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H1_OFFSET, \
                                    SBB_IN_FIFO_H1_DEFAULT, \
                                    SBB_IN_FIFO_H1_RD_MASK, "SBB_IN_FIFO_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L1_OFFSET, \
                                    SBB_IN_FIFO_L1_DEFAULT, \
                                    SBB_IN_FIFO_L1_RD_MASK, "SBB_IN_FIFO_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H2_OFFSET, \
                                    SBB_IN_FIFO_H2_DEFAULT, \
                                    SBB_IN_FIFO_H2_RD_MASK, "SBB_IN_FIFO_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L2_OFFSET, \
                                    SBB_IN_FIFO_L2_DEFAULT, \
                                    SBB_IN_FIFO_L2_RD_MASK, "SBB_IN_FIFO_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H3_OFFSET, \
                                    SBB_IN_FIFO_H3_DEFAULT, \
                                    SBB_IN_FIFO_H3_RD_MASK, "SBB_IN_FIFO_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L3_OFFSET, \
                                    SBB_IN_FIFO_L3_DEFAULT, \
                                    SBB_IN_FIFO_L3_RD_MASK, "SBB_IN_FIFO_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H4_OFFSET, \
                                    SBB_IN_FIFO_H4_DEFAULT, \
                                    SBB_IN_FIFO_H4_RD_MASK, "SBB_IN_FIFO_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L4_OFFSET, \
                                    SBB_IN_FIFO_L4_DEFAULT, \
                                    SBB_IN_FIFO_L4_RD_MASK, "SBB_IN_FIFO_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H5_OFFSET, \
                                    SBB_IN_FIFO_H5_DEFAULT, \
                                    SBB_IN_FIFO_H5_RD_MASK, "SBB_IN_FIFO_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L5_OFFSET, \
                                    SBB_IN_FIFO_L5_DEFAULT, \
                                    SBB_IN_FIFO_L5_RD_MASK, "SBB_IN_FIFO_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H6_OFFSET, \
                                    SBB_IN_FIFO_H6_DEFAULT, \
                                    SBB_IN_FIFO_H6_RD_MASK, "SBB_IN_FIFO_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L6_OFFSET, \
                                    SBB_IN_FIFO_L6_DEFAULT, \
                                    SBB_IN_FIFO_L6_RD_MASK, "SBB_IN_FIFO_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_H7_OFFSET, \
                                    SBB_IN_FIFO_H7_DEFAULT, \
                                    SBB_IN_FIFO_H7_RD_MASK, "SBB_IN_FIFO_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_IN_FIFO_L7_OFFSET, \
                                    SBB_IN_FIFO_L7_DEFAULT, \
                                    SBB_IN_FIFO_L7_RD_MASK, "SBB_IN_FIFO_L7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H0_OFFSET, \
                                    SBB_OUT_FIFO_H0_DEFAULT, \
                                    SBB_OUT_FIFO_H0_RD_MASK, "SBB_OUT_FIFO_H0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L0_OFFSET, \
                                    SBB_OUT_FIFO_L0_DEFAULT, \
                                    SBB_OUT_FIFO_L0_RD_MASK, "SBB_OUT_FIFO_L0_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H1_OFFSET, \
                                    SBB_OUT_FIFO_H1_DEFAULT, \
                                    SBB_OUT_FIFO_H1_RD_MASK, "SBB_OUT_FIFO_H1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L1_OFFSET, \
                                    SBB_OUT_FIFO_L1_DEFAULT, \
                                    SBB_OUT_FIFO_L1_RD_MASK, "SBB_OUT_FIFO_L1_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H2_OFFSET, \
                                    SBB_OUT_FIFO_H2_DEFAULT, \
                                    SBB_OUT_FIFO_H2_RD_MASK, "SBB_OUT_FIFO_H2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L2_OFFSET, \
                                    SBB_OUT_FIFO_L2_DEFAULT, \
                                    SBB_OUT_FIFO_L2_RD_MASK, "SBB_OUT_FIFO_L2_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H3_OFFSET, \
                                    SBB_OUT_FIFO_H3_DEFAULT, \
                                    SBB_OUT_FIFO_H3_RD_MASK, "SBB_OUT_FIFO_H3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L3_OFFSET, \
                                    SBB_OUT_FIFO_L3_DEFAULT, \
                                    SBB_OUT_FIFO_L3_RD_MASK, "SBB_OUT_FIFO_L3_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H4_OFFSET, \
                                    SBB_OUT_FIFO_H4_DEFAULT, \
                                    SBB_OUT_FIFO_H4_RD_MASK, "SBB_OUT_FIFO_H4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L4_OFFSET, \
                                    SBB_OUT_FIFO_L4_DEFAULT, \
                                    SBB_OUT_FIFO_L4_RD_MASK, "SBB_OUT_FIFO_L4_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H5_OFFSET, \
                                    SBB_OUT_FIFO_H5_DEFAULT, \
                                    SBB_OUT_FIFO_H5_RD_MASK, "SBB_OUT_FIFO_H5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L5_OFFSET, \
                                    SBB_OUT_FIFO_L5_DEFAULT, \
                                    SBB_OUT_FIFO_L5_RD_MASK, "SBB_OUT_FIFO_L5_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H6_OFFSET, \
                                    SBB_OUT_FIFO_H6_DEFAULT, \
                                    SBB_OUT_FIFO_H6_RD_MASK, "SBB_OUT_FIFO_H6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L6_OFFSET, \
                                    SBB_OUT_FIFO_L6_DEFAULT, \
                                    SBB_OUT_FIFO_L6_RD_MASK, "SBB_OUT_FIFO_L6_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_H7_OFFSET, \
                                    SBB_OUT_FIFO_H7_DEFAULT, \
                                    SBB_OUT_FIFO_H7_RD_MASK, "SBB_OUT_FIFO_H7_OFFSET");

        read_reg_expect_18a(base_address[i]+SBB_OUT_FIFO_L7_OFFSET, \
                                    SBB_OUT_FIFO_L7_DEFAULT, \
                                    SBB_OUT_FIFO_L7_RD_MASK, "SBB_OUT_FIFO_L7_OFFSET");

    }

}
