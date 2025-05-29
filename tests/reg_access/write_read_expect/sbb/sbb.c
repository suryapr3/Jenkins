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
    SYSCON_SBB_MODULE_BASE
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
            write_read_expect_18a(base_address[i]+SBB_SEMAPHORE_OFFSET, \
                                    SBB_SEMAPHORE_DEFAULT, write_data, expected_data, \
                                    SBB_SEMAPHORE_RD_MASK, SBB_SEMAPHORE_WR_MASK, \
                                    "SBB_SEMAPHORE_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_FUNCTION_OFFSET, \
                                    SBB_FUNCTION_DEFAULT, write_data, expected_data, \
                                    SBB_FUNCTION_RD_MASK, SBB_FUNCTION_WR_MASK, \
                                    "SBB_FUNCTION_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_AUTH_STAT_PARAM_OFFSET, \
                                    SBB_AUTH_STAT_PARAM_DEFAULT, write_data, expected_data, \
                                    SBB_AUTH_STAT_PARAM_RD_MASK, SBB_AUTH_STAT_PARAM_WR_MASK, \
                                    "SBB_AUTH_STAT_PARAM_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_AUTH_STAT_OFFSET, \
                                    SBB_AUTH_STAT_DEFAULT, write_data, expected_data, \
                                    SBB_AUTH_STAT_RD_MASK, SBB_AUTH_STAT_WR_MASK, \
                                    "SBB_AUTH_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_STAT0_OFFSET, \
                                    SBB_STAT0_DEFAULT, write_data, expected_data, \
                                    SBB_STAT0_RD_MASK, SBB_STAT0_WR_MASK, \
                                    "SBB_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_STAT1_OFFSET, \
                                    SBB_STAT1_DEFAULT, write_data, expected_data, \
                                    SBB_STAT1_RD_MASK, SBB_STAT1_WR_MASK, \
                                    "SBB_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_DBG0_OFFSET, \
                                    SBB_DBG0_DEFAULT, write_data, expected_data, \
                                    SBB_DBG0_RD_MASK, SBB_DBG0_WR_MASK, \
                                    "SBB_DBG0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_DBG1_OFFSET, \
                                    SBB_DBG1_DEFAULT, write_data, expected_data, \
                                    SBB_DBG1_RD_MASK, SBB_DBG1_WR_MASK, \
                                    "SBB_DBG1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VENDOR0_OFFSET, \
                                    SBB_VENDOR0_DEFAULT, write_data, expected_data, \
                                    SBB_VENDOR0_RD_MASK, SBB_VENDOR0_WR_MASK, \
                                    "SBB_VENDOR0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VENDOR1_OFFSET, \
                                    SBB_VENDOR1_DEFAULT, write_data, expected_data, \
                                    SBB_VENDOR1_RD_MASK, SBB_VENDOR1_WR_MASK, \
                                    "SBB_VENDOR1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_RSLT0_OFFSET, \
                                    SBB_RSLT0_DEFAULT, write_data, expected_data, \
                                    SBB_RSLT0_RD_MASK, SBB_RSLT0_WR_MASK, \
                                    "SBB_RSLT0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_RSLT1_OFFSET, \
                                    SBB_RSLT1_DEFAULT, write_data, expected_data, \
                                    SBB_RSLT1_RD_MASK, SBB_RSLT1_WR_MASK, \
                                    "SBB_RSLT1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_ACTRL_VERIF_OFFSET, \
                                    SBB_MEAS_ACTRL_VERIF_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_ACTRL_VERIF_RD_MASK, SBB_MEAS_ACTRL_VERIF_WR_MASK, \
                                    "SBB_MEAS_ACTRL_VERIF_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_ACTRL_SBB_OFFSET, \
                                    SBB_MEAS_ACTRL_SBB_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_ACTRL_SBB_RD_MASK, SBB_MEAS_ACTRL_SBB_WR_MASK, \
                                    "SBB_MEAS_ACTRL_SBB_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_ACTRL_EXT_OFFSET, \
                                    SBB_MEAS_ACTRL_EXT_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_ACTRL_EXT_RD_MASK, SBB_MEAS_ACTRL_EXT_WR_MASK, \
                                    "SBB_MEAS_ACTRL_EXT_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_ACTRL_CLR_OFFSET, \
                                    SBB_MEAS_ACTRL_CLR_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_ACTRL_CLR_RD_MASK, SBB_MEAS_ACTRL_CLR_WR_MASK, \
                                    "SBB_MEAS_ACTRL_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_UNIQUE_ID0_OFFSET, \
                                    SBB_UNIQUE_ID0_DEFAULT, write_data, expected_data, \
                                    SBB_UNIQUE_ID0_RD_MASK, SBB_UNIQUE_ID0_WR_MASK, \
                                    "SBB_UNIQUE_ID0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_UNIQUE_ID1_OFFSET, \
                                    SBB_UNIQUE_ID1_DEFAULT, write_data, expected_data, \
                                    SBB_UNIQUE_ID1_RD_MASK, SBB_UNIQUE_ID1_WR_MASK, \
                                    "SBB_UNIQUE_ID1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_HW_VER0_OFFSET, \
                                    SBB_HW_VER0_DEFAULT, write_data, expected_data, \
                                    SBB_HW_VER0_RD_MASK, SBB_HW_VER0_WR_MASK, \
                                    "SBB_HW_VER0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_HW_VER1_OFFSET, \
                                    SBB_HW_VER1_DEFAULT, write_data, expected_data, \
                                    SBB_HW_VER1_RD_MASK, SBB_HW_VER1_WR_MASK, \
                                    "SBB_HW_VER1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H0_OFFSET, \
                                    SBB_MEAS_H0_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H0_RD_MASK, SBB_MEAS_H0_WR_MASK, \
                                    "SBB_MEAS_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L0_OFFSET, \
                                    SBB_MEAS_L0_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L0_RD_MASK, SBB_MEAS_L0_WR_MASK, \
                                    "SBB_MEAS_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H1_OFFSET, \
                                    SBB_MEAS_H1_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H1_RD_MASK, SBB_MEAS_H1_WR_MASK, \
                                    "SBB_MEAS_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L1_OFFSET, \
                                    SBB_MEAS_L1_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L1_RD_MASK, SBB_MEAS_L1_WR_MASK, \
                                    "SBB_MEAS_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H2_OFFSET, \
                                    SBB_MEAS_H2_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H2_RD_MASK, SBB_MEAS_H2_WR_MASK, \
                                    "SBB_MEAS_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L2_OFFSET, \
                                    SBB_MEAS_L2_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L2_RD_MASK, SBB_MEAS_L2_WR_MASK, \
                                    "SBB_MEAS_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H3_OFFSET, \
                                    SBB_MEAS_H3_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H3_RD_MASK, SBB_MEAS_H3_WR_MASK, \
                                    "SBB_MEAS_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L3_OFFSET, \
                                    SBB_MEAS_L3_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L3_RD_MASK, SBB_MEAS_L3_WR_MASK, \
                                    "SBB_MEAS_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H4_OFFSET, \
                                    SBB_MEAS_H4_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H4_RD_MASK, SBB_MEAS_H4_WR_MASK, \
                                    "SBB_MEAS_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L4_OFFSET, \
                                    SBB_MEAS_L4_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L4_RD_MASK, SBB_MEAS_L4_WR_MASK, \
                                    "SBB_MEAS_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H5_OFFSET, \
                                    SBB_MEAS_H5_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H5_RD_MASK, SBB_MEAS_H5_WR_MASK, \
                                    "SBB_MEAS_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L5_OFFSET, \
                                    SBB_MEAS_L5_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L5_RD_MASK, SBB_MEAS_L5_WR_MASK, \
                                    "SBB_MEAS_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H6_OFFSET, \
                                    SBB_MEAS_H6_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H6_RD_MASK, SBB_MEAS_H6_WR_MASK, \
                                    "SBB_MEAS_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L6_OFFSET, \
                                    SBB_MEAS_L6_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L6_RD_MASK, SBB_MEAS_L6_WR_MASK, \
                                    "SBB_MEAS_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H7_OFFSET, \
                                    SBB_MEAS_H7_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H7_RD_MASK, SBB_MEAS_H7_WR_MASK, \
                                    "SBB_MEAS_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L7_OFFSET, \
                                    SBB_MEAS_L7_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L7_RD_MASK, SBB_MEAS_L7_WR_MASK, \
                                    "SBB_MEAS_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H8_OFFSET, \
                                    SBB_MEAS_H8_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H8_RD_MASK, SBB_MEAS_H8_WR_MASK, \
                                    "SBB_MEAS_H8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L8_OFFSET, \
                                    SBB_MEAS_L8_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L8_RD_MASK, SBB_MEAS_L8_WR_MASK, \
                                    "SBB_MEAS_L8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H9_OFFSET, \
                                    SBB_MEAS_H9_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H9_RD_MASK, SBB_MEAS_H9_WR_MASK, \
                                    "SBB_MEAS_H9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L9_OFFSET, \
                                    SBB_MEAS_L9_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L9_RD_MASK, SBB_MEAS_L9_WR_MASK, \
                                    "SBB_MEAS_L9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H10_OFFSET, \
                                    SBB_MEAS_H10_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H10_RD_MASK, SBB_MEAS_H10_WR_MASK, \
                                    "SBB_MEAS_H10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L10_OFFSET, \
                                    SBB_MEAS_L10_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L10_RD_MASK, SBB_MEAS_L10_WR_MASK, \
                                    "SBB_MEAS_L10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H11_OFFSET, \
                                    SBB_MEAS_H11_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H11_RD_MASK, SBB_MEAS_H11_WR_MASK, \
                                    "SBB_MEAS_H11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L11_OFFSET, \
                                    SBB_MEAS_L11_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L11_RD_MASK, SBB_MEAS_L11_WR_MASK, \
                                    "SBB_MEAS_L11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H12_OFFSET, \
                                    SBB_MEAS_H12_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H12_RD_MASK, SBB_MEAS_H12_WR_MASK, \
                                    "SBB_MEAS_H12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L12_OFFSET, \
                                    SBB_MEAS_L12_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L12_RD_MASK, SBB_MEAS_L12_WR_MASK, \
                                    "SBB_MEAS_L12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H13_OFFSET, \
                                    SBB_MEAS_H13_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H13_RD_MASK, SBB_MEAS_H13_WR_MASK, \
                                    "SBB_MEAS_H13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L13_OFFSET, \
                                    SBB_MEAS_L13_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L13_RD_MASK, SBB_MEAS_L13_WR_MASK, \
                                    "SBB_MEAS_L13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H14_OFFSET, \
                                    SBB_MEAS_H14_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H14_RD_MASK, SBB_MEAS_H14_WR_MASK, \
                                    "SBB_MEAS_H14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L14_OFFSET, \
                                    SBB_MEAS_L14_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L14_RD_MASK, SBB_MEAS_L14_WR_MASK, \
                                    "SBB_MEAS_L14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H15_OFFSET, \
                                    SBB_MEAS_H15_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H15_RD_MASK, SBB_MEAS_H15_WR_MASK, \
                                    "SBB_MEAS_H15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L15_OFFSET, \
                                    SBB_MEAS_L15_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L15_RD_MASK, SBB_MEAS_L15_WR_MASK, \
                                    "SBB_MEAS_L15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H16_OFFSET, \
                                    SBB_MEAS_H16_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H16_RD_MASK, SBB_MEAS_H16_WR_MASK, \
                                    "SBB_MEAS_H16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L16_OFFSET, \
                                    SBB_MEAS_L16_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L16_RD_MASK, SBB_MEAS_L16_WR_MASK, \
                                    "SBB_MEAS_L16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H17_OFFSET, \
                                    SBB_MEAS_H17_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H17_RD_MASK, SBB_MEAS_H17_WR_MASK, \
                                    "SBB_MEAS_H17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L17_OFFSET, \
                                    SBB_MEAS_L17_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L17_RD_MASK, SBB_MEAS_L17_WR_MASK, \
                                    "SBB_MEAS_L17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H18_OFFSET, \
                                    SBB_MEAS_H18_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H18_RD_MASK, SBB_MEAS_H18_WR_MASK, \
                                    "SBB_MEAS_H18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L18_OFFSET, \
                                    SBB_MEAS_L18_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L18_RD_MASK, SBB_MEAS_L18_WR_MASK, \
                                    "SBB_MEAS_L18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H19_OFFSET, \
                                    SBB_MEAS_H19_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H19_RD_MASK, SBB_MEAS_H19_WR_MASK, \
                                    "SBB_MEAS_H19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L19_OFFSET, \
                                    SBB_MEAS_L19_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L19_RD_MASK, SBB_MEAS_L19_WR_MASK, \
                                    "SBB_MEAS_L19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H20_OFFSET, \
                                    SBB_MEAS_H20_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H20_RD_MASK, SBB_MEAS_H20_WR_MASK, \
                                    "SBB_MEAS_H20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L20_OFFSET, \
                                    SBB_MEAS_L20_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L20_RD_MASK, SBB_MEAS_L20_WR_MASK, \
                                    "SBB_MEAS_L20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H21_OFFSET, \
                                    SBB_MEAS_H21_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H21_RD_MASK, SBB_MEAS_H21_WR_MASK, \
                                    "SBB_MEAS_H21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L21_OFFSET, \
                                    SBB_MEAS_L21_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L21_RD_MASK, SBB_MEAS_L21_WR_MASK, \
                                    "SBB_MEAS_L21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H22_OFFSET, \
                                    SBB_MEAS_H22_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H22_RD_MASK, SBB_MEAS_H22_WR_MASK, \
                                    "SBB_MEAS_H22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L22_OFFSET, \
                                    SBB_MEAS_L22_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L22_RD_MASK, SBB_MEAS_L22_WR_MASK, \
                                    "SBB_MEAS_L22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H23_OFFSET, \
                                    SBB_MEAS_H23_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H23_RD_MASK, SBB_MEAS_H23_WR_MASK, \
                                    "SBB_MEAS_H23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L23_OFFSET, \
                                    SBB_MEAS_L23_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L23_RD_MASK, SBB_MEAS_L23_WR_MASK, \
                                    "SBB_MEAS_L23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H24_OFFSET, \
                                    SBB_MEAS_H24_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H24_RD_MASK, SBB_MEAS_H24_WR_MASK, \
                                    "SBB_MEAS_H24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L24_OFFSET, \
                                    SBB_MEAS_L24_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L24_RD_MASK, SBB_MEAS_L24_WR_MASK, \
                                    "SBB_MEAS_L24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H25_OFFSET, \
                                    SBB_MEAS_H25_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H25_RD_MASK, SBB_MEAS_H25_WR_MASK, \
                                    "SBB_MEAS_H25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L25_OFFSET, \
                                    SBB_MEAS_L25_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L25_RD_MASK, SBB_MEAS_L25_WR_MASK, \
                                    "SBB_MEAS_L25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H26_OFFSET, \
                                    SBB_MEAS_H26_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H26_RD_MASK, SBB_MEAS_H26_WR_MASK, \
                                    "SBB_MEAS_H26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L26_OFFSET, \
                                    SBB_MEAS_L26_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L26_RD_MASK, SBB_MEAS_L26_WR_MASK, \
                                    "SBB_MEAS_L26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H27_OFFSET, \
                                    SBB_MEAS_H27_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H27_RD_MASK, SBB_MEAS_H27_WR_MASK, \
                                    "SBB_MEAS_H27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L27_OFFSET, \
                                    SBB_MEAS_L27_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L27_RD_MASK, SBB_MEAS_L27_WR_MASK, \
                                    "SBB_MEAS_L27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H28_OFFSET, \
                                    SBB_MEAS_H28_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H28_RD_MASK, SBB_MEAS_H28_WR_MASK, \
                                    "SBB_MEAS_H28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L28_OFFSET, \
                                    SBB_MEAS_L28_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L28_RD_MASK, SBB_MEAS_L28_WR_MASK, \
                                    "SBB_MEAS_L28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H29_OFFSET, \
                                    SBB_MEAS_H29_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H29_RD_MASK, SBB_MEAS_H29_WR_MASK, \
                                    "SBB_MEAS_H29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L29_OFFSET, \
                                    SBB_MEAS_L29_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L29_RD_MASK, SBB_MEAS_L29_WR_MASK, \
                                    "SBB_MEAS_L29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H30_OFFSET, \
                                    SBB_MEAS_H30_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H30_RD_MASK, SBB_MEAS_H30_WR_MASK, \
                                    "SBB_MEAS_H30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L30_OFFSET, \
                                    SBB_MEAS_L30_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L30_RD_MASK, SBB_MEAS_L30_WR_MASK, \
                                    "SBB_MEAS_L30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H31_OFFSET, \
                                    SBB_MEAS_H31_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H31_RD_MASK, SBB_MEAS_H31_WR_MASK, \
                                    "SBB_MEAS_H31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L31_OFFSET, \
                                    SBB_MEAS_L31_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L31_RD_MASK, SBB_MEAS_L31_WR_MASK, \
                                    "SBB_MEAS_L31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H32_OFFSET, \
                                    SBB_MEAS_H32_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H32_RD_MASK, SBB_MEAS_H32_WR_MASK, \
                                    "SBB_MEAS_H32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L32_OFFSET, \
                                    SBB_MEAS_L32_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L32_RD_MASK, SBB_MEAS_L32_WR_MASK, \
                                    "SBB_MEAS_L32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H33_OFFSET, \
                                    SBB_MEAS_H33_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H33_RD_MASK, SBB_MEAS_H33_WR_MASK, \
                                    "SBB_MEAS_H33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L33_OFFSET, \
                                    SBB_MEAS_L33_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L33_RD_MASK, SBB_MEAS_L33_WR_MASK, \
                                    "SBB_MEAS_L33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H34_OFFSET, \
                                    SBB_MEAS_H34_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H34_RD_MASK, SBB_MEAS_H34_WR_MASK, \
                                    "SBB_MEAS_H34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L34_OFFSET, \
                                    SBB_MEAS_L34_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L34_RD_MASK, SBB_MEAS_L34_WR_MASK, \
                                    "SBB_MEAS_L34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H35_OFFSET, \
                                    SBB_MEAS_H35_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H35_RD_MASK, SBB_MEAS_H35_WR_MASK, \
                                    "SBB_MEAS_H35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L35_OFFSET, \
                                    SBB_MEAS_L35_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L35_RD_MASK, SBB_MEAS_L35_WR_MASK, \
                                    "SBB_MEAS_L35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H36_OFFSET, \
                                    SBB_MEAS_H36_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H36_RD_MASK, SBB_MEAS_H36_WR_MASK, \
                                    "SBB_MEAS_H36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L36_OFFSET, \
                                    SBB_MEAS_L36_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L36_RD_MASK, SBB_MEAS_L36_WR_MASK, \
                                    "SBB_MEAS_L36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H37_OFFSET, \
                                    SBB_MEAS_H37_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H37_RD_MASK, SBB_MEAS_H37_WR_MASK, \
                                    "SBB_MEAS_H37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L37_OFFSET, \
                                    SBB_MEAS_L37_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L37_RD_MASK, SBB_MEAS_L37_WR_MASK, \
                                    "SBB_MEAS_L37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H38_OFFSET, \
                                    SBB_MEAS_H38_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H38_RD_MASK, SBB_MEAS_H38_WR_MASK, \
                                    "SBB_MEAS_H38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L38_OFFSET, \
                                    SBB_MEAS_L38_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L38_RD_MASK, SBB_MEAS_L38_WR_MASK, \
                                    "SBB_MEAS_L38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H39_OFFSET, \
                                    SBB_MEAS_H39_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H39_RD_MASK, SBB_MEAS_H39_WR_MASK, \
                                    "SBB_MEAS_H39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L39_OFFSET, \
                                    SBB_MEAS_L39_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L39_RD_MASK, SBB_MEAS_L39_WR_MASK, \
                                    "SBB_MEAS_L39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H40_OFFSET, \
                                    SBB_MEAS_H40_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H40_RD_MASK, SBB_MEAS_H40_WR_MASK, \
                                    "SBB_MEAS_H40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L40_OFFSET, \
                                    SBB_MEAS_L40_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L40_RD_MASK, SBB_MEAS_L40_WR_MASK, \
                                    "SBB_MEAS_L40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H41_OFFSET, \
                                    SBB_MEAS_H41_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H41_RD_MASK, SBB_MEAS_H41_WR_MASK, \
                                    "SBB_MEAS_H41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L41_OFFSET, \
                                    SBB_MEAS_L41_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L41_RD_MASK, SBB_MEAS_L41_WR_MASK, \
                                    "SBB_MEAS_L41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H42_OFFSET, \
                                    SBB_MEAS_H42_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H42_RD_MASK, SBB_MEAS_H42_WR_MASK, \
                                    "SBB_MEAS_H42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L42_OFFSET, \
                                    SBB_MEAS_L42_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L42_RD_MASK, SBB_MEAS_L42_WR_MASK, \
                                    "SBB_MEAS_L42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H43_OFFSET, \
                                    SBB_MEAS_H43_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H43_RD_MASK, SBB_MEAS_H43_WR_MASK, \
                                    "SBB_MEAS_H43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L43_OFFSET, \
                                    SBB_MEAS_L43_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L43_RD_MASK, SBB_MEAS_L43_WR_MASK, \
                                    "SBB_MEAS_L43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H44_OFFSET, \
                                    SBB_MEAS_H44_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H44_RD_MASK, SBB_MEAS_H44_WR_MASK, \
                                    "SBB_MEAS_H44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L44_OFFSET, \
                                    SBB_MEAS_L44_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L44_RD_MASK, SBB_MEAS_L44_WR_MASK, \
                                    "SBB_MEAS_L44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H45_OFFSET, \
                                    SBB_MEAS_H45_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H45_RD_MASK, SBB_MEAS_H45_WR_MASK, \
                                    "SBB_MEAS_H45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L45_OFFSET, \
                                    SBB_MEAS_L45_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L45_RD_MASK, SBB_MEAS_L45_WR_MASK, \
                                    "SBB_MEAS_L45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H46_OFFSET, \
                                    SBB_MEAS_H46_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H46_RD_MASK, SBB_MEAS_H46_WR_MASK, \
                                    "SBB_MEAS_H46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L46_OFFSET, \
                                    SBB_MEAS_L46_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L46_RD_MASK, SBB_MEAS_L46_WR_MASK, \
                                    "SBB_MEAS_L46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H47_OFFSET, \
                                    SBB_MEAS_H47_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H47_RD_MASK, SBB_MEAS_H47_WR_MASK, \
                                    "SBB_MEAS_H47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L47_OFFSET, \
                                    SBB_MEAS_L47_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L47_RD_MASK, SBB_MEAS_L47_WR_MASK, \
                                    "SBB_MEAS_L47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H48_OFFSET, \
                                    SBB_MEAS_H48_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H48_RD_MASK, SBB_MEAS_H48_WR_MASK, \
                                    "SBB_MEAS_H48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L48_OFFSET, \
                                    SBB_MEAS_L48_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L48_RD_MASK, SBB_MEAS_L48_WR_MASK, \
                                    "SBB_MEAS_L48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H49_OFFSET, \
                                    SBB_MEAS_H49_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H49_RD_MASK, SBB_MEAS_H49_WR_MASK, \
                                    "SBB_MEAS_H49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L49_OFFSET, \
                                    SBB_MEAS_L49_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L49_RD_MASK, SBB_MEAS_L49_WR_MASK, \
                                    "SBB_MEAS_L49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H50_OFFSET, \
                                    SBB_MEAS_H50_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H50_RD_MASK, SBB_MEAS_H50_WR_MASK, \
                                    "SBB_MEAS_H50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L50_OFFSET, \
                                    SBB_MEAS_L50_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L50_RD_MASK, SBB_MEAS_L50_WR_MASK, \
                                    "SBB_MEAS_L50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H51_OFFSET, \
                                    SBB_MEAS_H51_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H51_RD_MASK, SBB_MEAS_H51_WR_MASK, \
                                    "SBB_MEAS_H51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L51_OFFSET, \
                                    SBB_MEAS_L51_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L51_RD_MASK, SBB_MEAS_L51_WR_MASK, \
                                    "SBB_MEAS_L51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H52_OFFSET, \
                                    SBB_MEAS_H52_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H52_RD_MASK, SBB_MEAS_H52_WR_MASK, \
                                    "SBB_MEAS_H52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L52_OFFSET, \
                                    SBB_MEAS_L52_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L52_RD_MASK, SBB_MEAS_L52_WR_MASK, \
                                    "SBB_MEAS_L52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H53_OFFSET, \
                                    SBB_MEAS_H53_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H53_RD_MASK, SBB_MEAS_H53_WR_MASK, \
                                    "SBB_MEAS_H53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L53_OFFSET, \
                                    SBB_MEAS_L53_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L53_RD_MASK, SBB_MEAS_L53_WR_MASK, \
                                    "SBB_MEAS_L53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H54_OFFSET, \
                                    SBB_MEAS_H54_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H54_RD_MASK, SBB_MEAS_H54_WR_MASK, \
                                    "SBB_MEAS_H54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L54_OFFSET, \
                                    SBB_MEAS_L54_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L54_RD_MASK, SBB_MEAS_L54_WR_MASK, \
                                    "SBB_MEAS_L54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H55_OFFSET, \
                                    SBB_MEAS_H55_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H55_RD_MASK, SBB_MEAS_H55_WR_MASK, \
                                    "SBB_MEAS_H55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L55_OFFSET, \
                                    SBB_MEAS_L55_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L55_RD_MASK, SBB_MEAS_L55_WR_MASK, \
                                    "SBB_MEAS_L55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H56_OFFSET, \
                                    SBB_MEAS_H56_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H56_RD_MASK, SBB_MEAS_H56_WR_MASK, \
                                    "SBB_MEAS_H56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L56_OFFSET, \
                                    SBB_MEAS_L56_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L56_RD_MASK, SBB_MEAS_L56_WR_MASK, \
                                    "SBB_MEAS_L56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H57_OFFSET, \
                                    SBB_MEAS_H57_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H57_RD_MASK, SBB_MEAS_H57_WR_MASK, \
                                    "SBB_MEAS_H57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L57_OFFSET, \
                                    SBB_MEAS_L57_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L57_RD_MASK, SBB_MEAS_L57_WR_MASK, \
                                    "SBB_MEAS_L57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H58_OFFSET, \
                                    SBB_MEAS_H58_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H58_RD_MASK, SBB_MEAS_H58_WR_MASK, \
                                    "SBB_MEAS_H58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L58_OFFSET, \
                                    SBB_MEAS_L58_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L58_RD_MASK, SBB_MEAS_L58_WR_MASK, \
                                    "SBB_MEAS_L58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H59_OFFSET, \
                                    SBB_MEAS_H59_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H59_RD_MASK, SBB_MEAS_H59_WR_MASK, \
                                    "SBB_MEAS_H59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L59_OFFSET, \
                                    SBB_MEAS_L59_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L59_RD_MASK, SBB_MEAS_L59_WR_MASK, \
                                    "SBB_MEAS_L59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H60_OFFSET, \
                                    SBB_MEAS_H60_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H60_RD_MASK, SBB_MEAS_H60_WR_MASK, \
                                    "SBB_MEAS_H60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L60_OFFSET, \
                                    SBB_MEAS_L60_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L60_RD_MASK, SBB_MEAS_L60_WR_MASK, \
                                    "SBB_MEAS_L60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H61_OFFSET, \
                                    SBB_MEAS_H61_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H61_RD_MASK, SBB_MEAS_H61_WR_MASK, \
                                    "SBB_MEAS_H61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L61_OFFSET, \
                                    SBB_MEAS_L61_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L61_RD_MASK, SBB_MEAS_L61_WR_MASK, \
                                    "SBB_MEAS_L61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H62_OFFSET, \
                                    SBB_MEAS_H62_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H62_RD_MASK, SBB_MEAS_H62_WR_MASK, \
                                    "SBB_MEAS_H62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L62_OFFSET, \
                                    SBB_MEAS_L62_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L62_RD_MASK, SBB_MEAS_L62_WR_MASK, \
                                    "SBB_MEAS_L62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H63_OFFSET, \
                                    SBB_MEAS_H63_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H63_RD_MASK, SBB_MEAS_H63_WR_MASK, \
                                    "SBB_MEAS_H63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L63_OFFSET, \
                                    SBB_MEAS_L63_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L63_RD_MASK, SBB_MEAS_L63_WR_MASK, \
                                    "SBB_MEAS_L63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H64_OFFSET, \
                                    SBB_MEAS_H64_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H64_RD_MASK, SBB_MEAS_H64_WR_MASK, \
                                    "SBB_MEAS_H64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L64_OFFSET, \
                                    SBB_MEAS_L64_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L64_RD_MASK, SBB_MEAS_L64_WR_MASK, \
                                    "SBB_MEAS_L64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H65_OFFSET, \
                                    SBB_MEAS_H65_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H65_RD_MASK, SBB_MEAS_H65_WR_MASK, \
                                    "SBB_MEAS_H65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L65_OFFSET, \
                                    SBB_MEAS_L65_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L65_RD_MASK, SBB_MEAS_L65_WR_MASK, \
                                    "SBB_MEAS_L65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H66_OFFSET, \
                                    SBB_MEAS_H66_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H66_RD_MASK, SBB_MEAS_H66_WR_MASK, \
                                    "SBB_MEAS_H66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L66_OFFSET, \
                                    SBB_MEAS_L66_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L66_RD_MASK, SBB_MEAS_L66_WR_MASK, \
                                    "SBB_MEAS_L66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H67_OFFSET, \
                                    SBB_MEAS_H67_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H67_RD_MASK, SBB_MEAS_H67_WR_MASK, \
                                    "SBB_MEAS_H67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L67_OFFSET, \
                                    SBB_MEAS_L67_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L67_RD_MASK, SBB_MEAS_L67_WR_MASK, \
                                    "SBB_MEAS_L67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H68_OFFSET, \
                                    SBB_MEAS_H68_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H68_RD_MASK, SBB_MEAS_H68_WR_MASK, \
                                    "SBB_MEAS_H68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L68_OFFSET, \
                                    SBB_MEAS_L68_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L68_RD_MASK, SBB_MEAS_L68_WR_MASK, \
                                    "SBB_MEAS_L68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H69_OFFSET, \
                                    SBB_MEAS_H69_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H69_RD_MASK, SBB_MEAS_H69_WR_MASK, \
                                    "SBB_MEAS_H69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L69_OFFSET, \
                                    SBB_MEAS_L69_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L69_RD_MASK, SBB_MEAS_L69_WR_MASK, \
                                    "SBB_MEAS_L69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H70_OFFSET, \
                                    SBB_MEAS_H70_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H70_RD_MASK, SBB_MEAS_H70_WR_MASK, \
                                    "SBB_MEAS_H70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L70_OFFSET, \
                                    SBB_MEAS_L70_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L70_RD_MASK, SBB_MEAS_L70_WR_MASK, \
                                    "SBB_MEAS_L70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H71_OFFSET, \
                                    SBB_MEAS_H71_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H71_RD_MASK, SBB_MEAS_H71_WR_MASK, \
                                    "SBB_MEAS_H71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L71_OFFSET, \
                                    SBB_MEAS_L71_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L71_RD_MASK, SBB_MEAS_L71_WR_MASK, \
                                    "SBB_MEAS_L71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H72_OFFSET, \
                                    SBB_MEAS_H72_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H72_RD_MASK, SBB_MEAS_H72_WR_MASK, \
                                    "SBB_MEAS_H72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L72_OFFSET, \
                                    SBB_MEAS_L72_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L72_RD_MASK, SBB_MEAS_L72_WR_MASK, \
                                    "SBB_MEAS_L72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H73_OFFSET, \
                                    SBB_MEAS_H73_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H73_RD_MASK, SBB_MEAS_H73_WR_MASK, \
                                    "SBB_MEAS_H73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L73_OFFSET, \
                                    SBB_MEAS_L73_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L73_RD_MASK, SBB_MEAS_L73_WR_MASK, \
                                    "SBB_MEAS_L73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H74_OFFSET, \
                                    SBB_MEAS_H74_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H74_RD_MASK, SBB_MEAS_H74_WR_MASK, \
                                    "SBB_MEAS_H74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L74_OFFSET, \
                                    SBB_MEAS_L74_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L74_RD_MASK, SBB_MEAS_L74_WR_MASK, \
                                    "SBB_MEAS_L74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H75_OFFSET, \
                                    SBB_MEAS_H75_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H75_RD_MASK, SBB_MEAS_H75_WR_MASK, \
                                    "SBB_MEAS_H75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L75_OFFSET, \
                                    SBB_MEAS_L75_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L75_RD_MASK, SBB_MEAS_L75_WR_MASK, \
                                    "SBB_MEAS_L75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H76_OFFSET, \
                                    SBB_MEAS_H76_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H76_RD_MASK, SBB_MEAS_H76_WR_MASK, \
                                    "SBB_MEAS_H76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L76_OFFSET, \
                                    SBB_MEAS_L76_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L76_RD_MASK, SBB_MEAS_L76_WR_MASK, \
                                    "SBB_MEAS_L76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H77_OFFSET, \
                                    SBB_MEAS_H77_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H77_RD_MASK, SBB_MEAS_H77_WR_MASK, \
                                    "SBB_MEAS_H77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L77_OFFSET, \
                                    SBB_MEAS_L77_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L77_RD_MASK, SBB_MEAS_L77_WR_MASK, \
                                    "SBB_MEAS_L77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H78_OFFSET, \
                                    SBB_MEAS_H78_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H78_RD_MASK, SBB_MEAS_H78_WR_MASK, \
                                    "SBB_MEAS_H78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L78_OFFSET, \
                                    SBB_MEAS_L78_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L78_RD_MASK, SBB_MEAS_L78_WR_MASK, \
                                    "SBB_MEAS_L78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H79_OFFSET, \
                                    SBB_MEAS_H79_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H79_RD_MASK, SBB_MEAS_H79_WR_MASK, \
                                    "SBB_MEAS_H79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L79_OFFSET, \
                                    SBB_MEAS_L79_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L79_RD_MASK, SBB_MEAS_L79_WR_MASK, \
                                    "SBB_MEAS_L79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H80_OFFSET, \
                                    SBB_MEAS_H80_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H80_RD_MASK, SBB_MEAS_H80_WR_MASK, \
                                    "SBB_MEAS_H80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L80_OFFSET, \
                                    SBB_MEAS_L80_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L80_RD_MASK, SBB_MEAS_L80_WR_MASK, \
                                    "SBB_MEAS_L80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H81_OFFSET, \
                                    SBB_MEAS_H81_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H81_RD_MASK, SBB_MEAS_H81_WR_MASK, \
                                    "SBB_MEAS_H81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L81_OFFSET, \
                                    SBB_MEAS_L81_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L81_RD_MASK, SBB_MEAS_L81_WR_MASK, \
                                    "SBB_MEAS_L81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H82_OFFSET, \
                                    SBB_MEAS_H82_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H82_RD_MASK, SBB_MEAS_H82_WR_MASK, \
                                    "SBB_MEAS_H82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L82_OFFSET, \
                                    SBB_MEAS_L82_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L82_RD_MASK, SBB_MEAS_L82_WR_MASK, \
                                    "SBB_MEAS_L82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H83_OFFSET, \
                                    SBB_MEAS_H83_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H83_RD_MASK, SBB_MEAS_H83_WR_MASK, \
                                    "SBB_MEAS_H83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L83_OFFSET, \
                                    SBB_MEAS_L83_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L83_RD_MASK, SBB_MEAS_L83_WR_MASK, \
                                    "SBB_MEAS_L83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H84_OFFSET, \
                                    SBB_MEAS_H84_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H84_RD_MASK, SBB_MEAS_H84_WR_MASK, \
                                    "SBB_MEAS_H84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L84_OFFSET, \
                                    SBB_MEAS_L84_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L84_RD_MASK, SBB_MEAS_L84_WR_MASK, \
                                    "SBB_MEAS_L84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H85_OFFSET, \
                                    SBB_MEAS_H85_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H85_RD_MASK, SBB_MEAS_H85_WR_MASK, \
                                    "SBB_MEAS_H85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L85_OFFSET, \
                                    SBB_MEAS_L85_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L85_RD_MASK, SBB_MEAS_L85_WR_MASK, \
                                    "SBB_MEAS_L85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H86_OFFSET, \
                                    SBB_MEAS_H86_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H86_RD_MASK, SBB_MEAS_H86_WR_MASK, \
                                    "SBB_MEAS_H86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L86_OFFSET, \
                                    SBB_MEAS_L86_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L86_RD_MASK, SBB_MEAS_L86_WR_MASK, \
                                    "SBB_MEAS_L86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H87_OFFSET, \
                                    SBB_MEAS_H87_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H87_RD_MASK, SBB_MEAS_H87_WR_MASK, \
                                    "SBB_MEAS_H87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L87_OFFSET, \
                                    SBB_MEAS_L87_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L87_RD_MASK, SBB_MEAS_L87_WR_MASK, \
                                    "SBB_MEAS_L87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H88_OFFSET, \
                                    SBB_MEAS_H88_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H88_RD_MASK, SBB_MEAS_H88_WR_MASK, \
                                    "SBB_MEAS_H88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L88_OFFSET, \
                                    SBB_MEAS_L88_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L88_RD_MASK, SBB_MEAS_L88_WR_MASK, \
                                    "SBB_MEAS_L88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H89_OFFSET, \
                                    SBB_MEAS_H89_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H89_RD_MASK, SBB_MEAS_H89_WR_MASK, \
                                    "SBB_MEAS_H89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L89_OFFSET, \
                                    SBB_MEAS_L89_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L89_RD_MASK, SBB_MEAS_L89_WR_MASK, \
                                    "SBB_MEAS_L89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H90_OFFSET, \
                                    SBB_MEAS_H90_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H90_RD_MASK, SBB_MEAS_H90_WR_MASK, \
                                    "SBB_MEAS_H90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L90_OFFSET, \
                                    SBB_MEAS_L90_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L90_RD_MASK, SBB_MEAS_L90_WR_MASK, \
                                    "SBB_MEAS_L90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H91_OFFSET, \
                                    SBB_MEAS_H91_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H91_RD_MASK, SBB_MEAS_H91_WR_MASK, \
                                    "SBB_MEAS_H91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L91_OFFSET, \
                                    SBB_MEAS_L91_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L91_RD_MASK, SBB_MEAS_L91_WR_MASK, \
                                    "SBB_MEAS_L91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H92_OFFSET, \
                                    SBB_MEAS_H92_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H92_RD_MASK, SBB_MEAS_H92_WR_MASK, \
                                    "SBB_MEAS_H92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L92_OFFSET, \
                                    SBB_MEAS_L92_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L92_RD_MASK, SBB_MEAS_L92_WR_MASK, \
                                    "SBB_MEAS_L92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H93_OFFSET, \
                                    SBB_MEAS_H93_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H93_RD_MASK, SBB_MEAS_H93_WR_MASK, \
                                    "SBB_MEAS_H93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L93_OFFSET, \
                                    SBB_MEAS_L93_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L93_RD_MASK, SBB_MEAS_L93_WR_MASK, \
                                    "SBB_MEAS_L93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H94_OFFSET, \
                                    SBB_MEAS_H94_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H94_RD_MASK, SBB_MEAS_H94_WR_MASK, \
                                    "SBB_MEAS_H94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L94_OFFSET, \
                                    SBB_MEAS_L94_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L94_RD_MASK, SBB_MEAS_L94_WR_MASK, \
                                    "SBB_MEAS_L94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H95_OFFSET, \
                                    SBB_MEAS_H95_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H95_RD_MASK, SBB_MEAS_H95_WR_MASK, \
                                    "SBB_MEAS_H95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L95_OFFSET, \
                                    SBB_MEAS_L95_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L95_RD_MASK, SBB_MEAS_L95_WR_MASK, \
                                    "SBB_MEAS_L95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H96_OFFSET, \
                                    SBB_MEAS_H96_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H96_RD_MASK, SBB_MEAS_H96_WR_MASK, \
                                    "SBB_MEAS_H96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L96_OFFSET, \
                                    SBB_MEAS_L96_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L96_RD_MASK, SBB_MEAS_L96_WR_MASK, \
                                    "SBB_MEAS_L96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H97_OFFSET, \
                                    SBB_MEAS_H97_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H97_RD_MASK, SBB_MEAS_H97_WR_MASK, \
                                    "SBB_MEAS_H97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L97_OFFSET, \
                                    SBB_MEAS_L97_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L97_RD_MASK, SBB_MEAS_L97_WR_MASK, \
                                    "SBB_MEAS_L97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H98_OFFSET, \
                                    SBB_MEAS_H98_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H98_RD_MASK, SBB_MEAS_H98_WR_MASK, \
                                    "SBB_MEAS_H98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L98_OFFSET, \
                                    SBB_MEAS_L98_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L98_RD_MASK, SBB_MEAS_L98_WR_MASK, \
                                    "SBB_MEAS_L98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H99_OFFSET, \
                                    SBB_MEAS_H99_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H99_RD_MASK, SBB_MEAS_H99_WR_MASK, \
                                    "SBB_MEAS_H99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L99_OFFSET, \
                                    SBB_MEAS_L99_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L99_RD_MASK, SBB_MEAS_L99_WR_MASK, \
                                    "SBB_MEAS_L99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H100_OFFSET, \
                                    SBB_MEAS_H100_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H100_RD_MASK, SBB_MEAS_H100_WR_MASK, \
                                    "SBB_MEAS_H100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L100_OFFSET, \
                                    SBB_MEAS_L100_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L100_RD_MASK, SBB_MEAS_L100_WR_MASK, \
                                    "SBB_MEAS_L100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H101_OFFSET, \
                                    SBB_MEAS_H101_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H101_RD_MASK, SBB_MEAS_H101_WR_MASK, \
                                    "SBB_MEAS_H101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L101_OFFSET, \
                                    SBB_MEAS_L101_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L101_RD_MASK, SBB_MEAS_L101_WR_MASK, \
                                    "SBB_MEAS_L101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H102_OFFSET, \
                                    SBB_MEAS_H102_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H102_RD_MASK, SBB_MEAS_H102_WR_MASK, \
                                    "SBB_MEAS_H102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L102_OFFSET, \
                                    SBB_MEAS_L102_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L102_RD_MASK, SBB_MEAS_L102_WR_MASK, \
                                    "SBB_MEAS_L102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H103_OFFSET, \
                                    SBB_MEAS_H103_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H103_RD_MASK, SBB_MEAS_H103_WR_MASK, \
                                    "SBB_MEAS_H103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L103_OFFSET, \
                                    SBB_MEAS_L103_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L103_RD_MASK, SBB_MEAS_L103_WR_MASK, \
                                    "SBB_MEAS_L103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H104_OFFSET, \
                                    SBB_MEAS_H104_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H104_RD_MASK, SBB_MEAS_H104_WR_MASK, \
                                    "SBB_MEAS_H104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L104_OFFSET, \
                                    SBB_MEAS_L104_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L104_RD_MASK, SBB_MEAS_L104_WR_MASK, \
                                    "SBB_MEAS_L104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H105_OFFSET, \
                                    SBB_MEAS_H105_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H105_RD_MASK, SBB_MEAS_H105_WR_MASK, \
                                    "SBB_MEAS_H105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L105_OFFSET, \
                                    SBB_MEAS_L105_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L105_RD_MASK, SBB_MEAS_L105_WR_MASK, \
                                    "SBB_MEAS_L105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H106_OFFSET, \
                                    SBB_MEAS_H106_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H106_RD_MASK, SBB_MEAS_H106_WR_MASK, \
                                    "SBB_MEAS_H106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L106_OFFSET, \
                                    SBB_MEAS_L106_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L106_RD_MASK, SBB_MEAS_L106_WR_MASK, \
                                    "SBB_MEAS_L106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H107_OFFSET, \
                                    SBB_MEAS_H107_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H107_RD_MASK, SBB_MEAS_H107_WR_MASK, \
                                    "SBB_MEAS_H107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L107_OFFSET, \
                                    SBB_MEAS_L107_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L107_RD_MASK, SBB_MEAS_L107_WR_MASK, \
                                    "SBB_MEAS_L107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H108_OFFSET, \
                                    SBB_MEAS_H108_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H108_RD_MASK, SBB_MEAS_H108_WR_MASK, \
                                    "SBB_MEAS_H108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L108_OFFSET, \
                                    SBB_MEAS_L108_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L108_RD_MASK, SBB_MEAS_L108_WR_MASK, \
                                    "SBB_MEAS_L108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H109_OFFSET, \
                                    SBB_MEAS_H109_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H109_RD_MASK, SBB_MEAS_H109_WR_MASK, \
                                    "SBB_MEAS_H109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L109_OFFSET, \
                                    SBB_MEAS_L109_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L109_RD_MASK, SBB_MEAS_L109_WR_MASK, \
                                    "SBB_MEAS_L109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H110_OFFSET, \
                                    SBB_MEAS_H110_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H110_RD_MASK, SBB_MEAS_H110_WR_MASK, \
                                    "SBB_MEAS_H110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L110_OFFSET, \
                                    SBB_MEAS_L110_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L110_RD_MASK, SBB_MEAS_L110_WR_MASK, \
                                    "SBB_MEAS_L110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H111_OFFSET, \
                                    SBB_MEAS_H111_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H111_RD_MASK, SBB_MEAS_H111_WR_MASK, \
                                    "SBB_MEAS_H111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L111_OFFSET, \
                                    SBB_MEAS_L111_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L111_RD_MASK, SBB_MEAS_L111_WR_MASK, \
                                    "SBB_MEAS_L111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H112_OFFSET, \
                                    SBB_MEAS_H112_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H112_RD_MASK, SBB_MEAS_H112_WR_MASK, \
                                    "SBB_MEAS_H112_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L112_OFFSET, \
                                    SBB_MEAS_L112_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L112_RD_MASK, SBB_MEAS_L112_WR_MASK, \
                                    "SBB_MEAS_L112_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H113_OFFSET, \
                                    SBB_MEAS_H113_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H113_RD_MASK, SBB_MEAS_H113_WR_MASK, \
                                    "SBB_MEAS_H113_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L113_OFFSET, \
                                    SBB_MEAS_L113_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L113_RD_MASK, SBB_MEAS_L113_WR_MASK, \
                                    "SBB_MEAS_L113_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H114_OFFSET, \
                                    SBB_MEAS_H114_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H114_RD_MASK, SBB_MEAS_H114_WR_MASK, \
                                    "SBB_MEAS_H114_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L114_OFFSET, \
                                    SBB_MEAS_L114_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L114_RD_MASK, SBB_MEAS_L114_WR_MASK, \
                                    "SBB_MEAS_L114_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H115_OFFSET, \
                                    SBB_MEAS_H115_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H115_RD_MASK, SBB_MEAS_H115_WR_MASK, \
                                    "SBB_MEAS_H115_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L115_OFFSET, \
                                    SBB_MEAS_L115_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L115_RD_MASK, SBB_MEAS_L115_WR_MASK, \
                                    "SBB_MEAS_L115_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H116_OFFSET, \
                                    SBB_MEAS_H116_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H116_RD_MASK, SBB_MEAS_H116_WR_MASK, \
                                    "SBB_MEAS_H116_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L116_OFFSET, \
                                    SBB_MEAS_L116_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L116_RD_MASK, SBB_MEAS_L116_WR_MASK, \
                                    "SBB_MEAS_L116_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H117_OFFSET, \
                                    SBB_MEAS_H117_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H117_RD_MASK, SBB_MEAS_H117_WR_MASK, \
                                    "SBB_MEAS_H117_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L117_OFFSET, \
                                    SBB_MEAS_L117_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L117_RD_MASK, SBB_MEAS_L117_WR_MASK, \
                                    "SBB_MEAS_L117_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H118_OFFSET, \
                                    SBB_MEAS_H118_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H118_RD_MASK, SBB_MEAS_H118_WR_MASK, \
                                    "SBB_MEAS_H118_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L118_OFFSET, \
                                    SBB_MEAS_L118_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L118_RD_MASK, SBB_MEAS_L118_WR_MASK, \
                                    "SBB_MEAS_L118_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H119_OFFSET, \
                                    SBB_MEAS_H119_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H119_RD_MASK, SBB_MEAS_H119_WR_MASK, \
                                    "SBB_MEAS_H119_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L119_OFFSET, \
                                    SBB_MEAS_L119_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L119_RD_MASK, SBB_MEAS_L119_WR_MASK, \
                                    "SBB_MEAS_L119_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H120_OFFSET, \
                                    SBB_MEAS_H120_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H120_RD_MASK, SBB_MEAS_H120_WR_MASK, \
                                    "SBB_MEAS_H120_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L120_OFFSET, \
                                    SBB_MEAS_L120_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L120_RD_MASK, SBB_MEAS_L120_WR_MASK, \
                                    "SBB_MEAS_L120_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H121_OFFSET, \
                                    SBB_MEAS_H121_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H121_RD_MASK, SBB_MEAS_H121_WR_MASK, \
                                    "SBB_MEAS_H121_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L121_OFFSET, \
                                    SBB_MEAS_L121_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L121_RD_MASK, SBB_MEAS_L121_WR_MASK, \
                                    "SBB_MEAS_L121_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H122_OFFSET, \
                                    SBB_MEAS_H122_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H122_RD_MASK, SBB_MEAS_H122_WR_MASK, \
                                    "SBB_MEAS_H122_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L122_OFFSET, \
                                    SBB_MEAS_L122_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L122_RD_MASK, SBB_MEAS_L122_WR_MASK, \
                                    "SBB_MEAS_L122_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H123_OFFSET, \
                                    SBB_MEAS_H123_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H123_RD_MASK, SBB_MEAS_H123_WR_MASK, \
                                    "SBB_MEAS_H123_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L123_OFFSET, \
                                    SBB_MEAS_L123_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L123_RD_MASK, SBB_MEAS_L123_WR_MASK, \
                                    "SBB_MEAS_L123_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H124_OFFSET, \
                                    SBB_MEAS_H124_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H124_RD_MASK, SBB_MEAS_H124_WR_MASK, \
                                    "SBB_MEAS_H124_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L124_OFFSET, \
                                    SBB_MEAS_L124_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L124_RD_MASK, SBB_MEAS_L124_WR_MASK, \
                                    "SBB_MEAS_L124_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H125_OFFSET, \
                                    SBB_MEAS_H125_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H125_RD_MASK, SBB_MEAS_H125_WR_MASK, \
                                    "SBB_MEAS_H125_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L125_OFFSET, \
                                    SBB_MEAS_L125_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L125_RD_MASK, SBB_MEAS_L125_WR_MASK, \
                                    "SBB_MEAS_L125_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H126_OFFSET, \
                                    SBB_MEAS_H126_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H126_RD_MASK, SBB_MEAS_H126_WR_MASK, \
                                    "SBB_MEAS_H126_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L126_OFFSET, \
                                    SBB_MEAS_L126_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L126_RD_MASK, SBB_MEAS_L126_WR_MASK, \
                                    "SBB_MEAS_L126_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H127_OFFSET, \
                                    SBB_MEAS_H127_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H127_RD_MASK, SBB_MEAS_H127_WR_MASK, \
                                    "SBB_MEAS_H127_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L127_OFFSET, \
                                    SBB_MEAS_L127_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L127_RD_MASK, SBB_MEAS_L127_WR_MASK, \
                                    "SBB_MEAS_L127_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H128_OFFSET, \
                                    SBB_MEAS_H128_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H128_RD_MASK, SBB_MEAS_H128_WR_MASK, \
                                    "SBB_MEAS_H128_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L128_OFFSET, \
                                    SBB_MEAS_L128_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L128_RD_MASK, SBB_MEAS_L128_WR_MASK, \
                                    "SBB_MEAS_L128_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H129_OFFSET, \
                                    SBB_MEAS_H129_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H129_RD_MASK, SBB_MEAS_H129_WR_MASK, \
                                    "SBB_MEAS_H129_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L129_OFFSET, \
                                    SBB_MEAS_L129_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L129_RD_MASK, SBB_MEAS_L129_WR_MASK, \
                                    "SBB_MEAS_L129_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H130_OFFSET, \
                                    SBB_MEAS_H130_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H130_RD_MASK, SBB_MEAS_H130_WR_MASK, \
                                    "SBB_MEAS_H130_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L130_OFFSET, \
                                    SBB_MEAS_L130_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L130_RD_MASK, SBB_MEAS_L130_WR_MASK, \
                                    "SBB_MEAS_L130_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H131_OFFSET, \
                                    SBB_MEAS_H131_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H131_RD_MASK, SBB_MEAS_H131_WR_MASK, \
                                    "SBB_MEAS_H131_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L131_OFFSET, \
                                    SBB_MEAS_L131_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L131_RD_MASK, SBB_MEAS_L131_WR_MASK, \
                                    "SBB_MEAS_L131_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H132_OFFSET, \
                                    SBB_MEAS_H132_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H132_RD_MASK, SBB_MEAS_H132_WR_MASK, \
                                    "SBB_MEAS_H132_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L132_OFFSET, \
                                    SBB_MEAS_L132_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L132_RD_MASK, SBB_MEAS_L132_WR_MASK, \
                                    "SBB_MEAS_L132_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H133_OFFSET, \
                                    SBB_MEAS_H133_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H133_RD_MASK, SBB_MEAS_H133_WR_MASK, \
                                    "SBB_MEAS_H133_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L133_OFFSET, \
                                    SBB_MEAS_L133_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L133_RD_MASK, SBB_MEAS_L133_WR_MASK, \
                                    "SBB_MEAS_L133_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H134_OFFSET, \
                                    SBB_MEAS_H134_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H134_RD_MASK, SBB_MEAS_H134_WR_MASK, \
                                    "SBB_MEAS_H134_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L134_OFFSET, \
                                    SBB_MEAS_L134_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L134_RD_MASK, SBB_MEAS_L134_WR_MASK, \
                                    "SBB_MEAS_L134_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H135_OFFSET, \
                                    SBB_MEAS_H135_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H135_RD_MASK, SBB_MEAS_H135_WR_MASK, \
                                    "SBB_MEAS_H135_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L135_OFFSET, \
                                    SBB_MEAS_L135_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L135_RD_MASK, SBB_MEAS_L135_WR_MASK, \
                                    "SBB_MEAS_L135_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H136_OFFSET, \
                                    SBB_MEAS_H136_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H136_RD_MASK, SBB_MEAS_H136_WR_MASK, \
                                    "SBB_MEAS_H136_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L136_OFFSET, \
                                    SBB_MEAS_L136_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L136_RD_MASK, SBB_MEAS_L136_WR_MASK, \
                                    "SBB_MEAS_L136_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H137_OFFSET, \
                                    SBB_MEAS_H137_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H137_RD_MASK, SBB_MEAS_H137_WR_MASK, \
                                    "SBB_MEAS_H137_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L137_OFFSET, \
                                    SBB_MEAS_L137_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L137_RD_MASK, SBB_MEAS_L137_WR_MASK, \
                                    "SBB_MEAS_L137_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H138_OFFSET, \
                                    SBB_MEAS_H138_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H138_RD_MASK, SBB_MEAS_H138_WR_MASK, \
                                    "SBB_MEAS_H138_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L138_OFFSET, \
                                    SBB_MEAS_L138_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L138_RD_MASK, SBB_MEAS_L138_WR_MASK, \
                                    "SBB_MEAS_L138_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H139_OFFSET, \
                                    SBB_MEAS_H139_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H139_RD_MASK, SBB_MEAS_H139_WR_MASK, \
                                    "SBB_MEAS_H139_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L139_OFFSET, \
                                    SBB_MEAS_L139_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L139_RD_MASK, SBB_MEAS_L139_WR_MASK, \
                                    "SBB_MEAS_L139_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H140_OFFSET, \
                                    SBB_MEAS_H140_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H140_RD_MASK, SBB_MEAS_H140_WR_MASK, \
                                    "SBB_MEAS_H140_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L140_OFFSET, \
                                    SBB_MEAS_L140_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L140_RD_MASK, SBB_MEAS_L140_WR_MASK, \
                                    "SBB_MEAS_L140_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H141_OFFSET, \
                                    SBB_MEAS_H141_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H141_RD_MASK, SBB_MEAS_H141_WR_MASK, \
                                    "SBB_MEAS_H141_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L141_OFFSET, \
                                    SBB_MEAS_L141_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L141_RD_MASK, SBB_MEAS_L141_WR_MASK, \
                                    "SBB_MEAS_L141_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H142_OFFSET, \
                                    SBB_MEAS_H142_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H142_RD_MASK, SBB_MEAS_H142_WR_MASK, \
                                    "SBB_MEAS_H142_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L142_OFFSET, \
                                    SBB_MEAS_L142_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L142_RD_MASK, SBB_MEAS_L142_WR_MASK, \
                                    "SBB_MEAS_L142_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_H143_OFFSET, \
                                    SBB_MEAS_H143_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_H143_RD_MASK, SBB_MEAS_H143_WR_MASK, \
                                    "SBB_MEAS_H143_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_MEAS_L143_OFFSET, \
                                    SBB_MEAS_L143_DEFAULT, write_data, expected_data, \
                                    SBB_MEAS_L143_RD_MASK, SBB_MEAS_L143_WR_MASK, \
                                    "SBB_MEAS_L143_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H0_OFFSET, \
                                    SBB_PCR_H0_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H0_RD_MASK, SBB_PCR_H0_WR_MASK, \
                                    "SBB_PCR_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L0_OFFSET, \
                                    SBB_PCR_L0_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L0_RD_MASK, SBB_PCR_L0_WR_MASK, \
                                    "SBB_PCR_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H1_OFFSET, \
                                    SBB_PCR_H1_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H1_RD_MASK, SBB_PCR_H1_WR_MASK, \
                                    "SBB_PCR_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L1_OFFSET, \
                                    SBB_PCR_L1_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L1_RD_MASK, SBB_PCR_L1_WR_MASK, \
                                    "SBB_PCR_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H2_OFFSET, \
                                    SBB_PCR_H2_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H2_RD_MASK, SBB_PCR_H2_WR_MASK, \
                                    "SBB_PCR_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L2_OFFSET, \
                                    SBB_PCR_L2_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L2_RD_MASK, SBB_PCR_L2_WR_MASK, \
                                    "SBB_PCR_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H3_OFFSET, \
                                    SBB_PCR_H3_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H3_RD_MASK, SBB_PCR_H3_WR_MASK, \
                                    "SBB_PCR_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L3_OFFSET, \
                                    SBB_PCR_L3_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L3_RD_MASK, SBB_PCR_L3_WR_MASK, \
                                    "SBB_PCR_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H4_OFFSET, \
                                    SBB_PCR_H4_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H4_RD_MASK, SBB_PCR_H4_WR_MASK, \
                                    "SBB_PCR_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L4_OFFSET, \
                                    SBB_PCR_L4_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L4_RD_MASK, SBB_PCR_L4_WR_MASK, \
                                    "SBB_PCR_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H5_OFFSET, \
                                    SBB_PCR_H5_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H5_RD_MASK, SBB_PCR_H5_WR_MASK, \
                                    "SBB_PCR_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L5_OFFSET, \
                                    SBB_PCR_L5_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L5_RD_MASK, SBB_PCR_L5_WR_MASK, \
                                    "SBB_PCR_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H6_OFFSET, \
                                    SBB_PCR_H6_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H6_RD_MASK, SBB_PCR_H6_WR_MASK, \
                                    "SBB_PCR_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L6_OFFSET, \
                                    SBB_PCR_L6_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L6_RD_MASK, SBB_PCR_L6_WR_MASK, \
                                    "SBB_PCR_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H7_OFFSET, \
                                    SBB_PCR_H7_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H7_RD_MASK, SBB_PCR_H7_WR_MASK, \
                                    "SBB_PCR_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L7_OFFSET, \
                                    SBB_PCR_L7_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L7_RD_MASK, SBB_PCR_L7_WR_MASK, \
                                    "SBB_PCR_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_H8_OFFSET, \
                                    SBB_PCR_H8_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_H8_RD_MASK, SBB_PCR_H8_WR_MASK, \
                                    "SBB_PCR_H8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PCR_L8_OFFSET, \
                                    SBB_PCR_L8_DEFAULT, write_data, expected_data, \
                                    SBB_PCR_L8_RD_MASK, SBB_PCR_L8_WR_MASK, \
                                    "SBB_PCR_L8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_INT_STS_OFFSET, \
                                    SBB_INT_STS_DEFAULT, write_data, expected_data, \
                                    SBB_INT_STS_RD_MASK, SBB_INT_STS_WR_MASK, \
                                    "SBB_INT_STS_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_INT_EN_OFFSET, \
                                    SBB_INT_EN_DEFAULT, write_data, expected_data, \
                                    SBB_INT_EN_RD_MASK, SBB_INT_EN_WR_MASK, \
                                    "SBB_INT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_INT_FRC_OFFSET, \
                                    SBB_INT_FRC_DEFAULT, write_data, expected_data, \
                                    SBB_INT_FRC_RD_MASK, SBB_INT_FRC_WR_MASK, \
                                    "SBB_INT_FRC_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_H0_OFFSET, \
                                    SBB_VER_H0_DEFAULT, write_data, expected_data, \
                                    SBB_VER_H0_RD_MASK, SBB_VER_H0_WR_MASK, \
                                    "SBB_VER_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_L0_OFFSET, \
                                    SBB_VER_L0_DEFAULT, write_data, expected_data, \
                                    SBB_VER_L0_RD_MASK, SBB_VER_L0_WR_MASK, \
                                    "SBB_VER_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_H1_OFFSET, \
                                    SBB_VER_H1_DEFAULT, write_data, expected_data, \
                                    SBB_VER_H1_RD_MASK, SBB_VER_H1_WR_MASK, \
                                    "SBB_VER_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_L1_OFFSET, \
                                    SBB_VER_L1_DEFAULT, write_data, expected_data, \
                                    SBB_VER_L1_RD_MASK, SBB_VER_L1_WR_MASK, \
                                    "SBB_VER_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_H2_OFFSET, \
                                    SBB_VER_H2_DEFAULT, write_data, expected_data, \
                                    SBB_VER_H2_RD_MASK, SBB_VER_H2_WR_MASK, \
                                    "SBB_VER_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_L2_OFFSET, \
                                    SBB_VER_L2_DEFAULT, write_data, expected_data, \
                                    SBB_VER_L2_RD_MASK, SBB_VER_L2_WR_MASK, \
                                    "SBB_VER_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_H3_OFFSET, \
                                    SBB_VER_H3_DEFAULT, write_data, expected_data, \
                                    SBB_VER_H3_RD_MASK, SBB_VER_H3_WR_MASK, \
                                    "SBB_VER_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_VER_L3_OFFSET, \
                                    SBB_VER_L3_DEFAULT, write_data, expected_data, \
                                    SBB_VER_L3_RD_MASK, SBB_VER_L3_WR_MASK, \
                                    "SBB_VER_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H0_OFFSET, \
                                    SBB_EFUSE_H0_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H0_RD_MASK, SBB_EFUSE_H0_WR_MASK, \
                                    "SBB_EFUSE_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L0_OFFSET, \
                                    SBB_EFUSE_L0_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L0_RD_MASK, SBB_EFUSE_L0_WR_MASK, \
                                    "SBB_EFUSE_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H1_OFFSET, \
                                    SBB_EFUSE_H1_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H1_RD_MASK, SBB_EFUSE_H1_WR_MASK, \
                                    "SBB_EFUSE_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L1_OFFSET, \
                                    SBB_EFUSE_L1_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L1_RD_MASK, SBB_EFUSE_L1_WR_MASK, \
                                    "SBB_EFUSE_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H2_OFFSET, \
                                    SBB_EFUSE_H2_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H2_RD_MASK, SBB_EFUSE_H2_WR_MASK, \
                                    "SBB_EFUSE_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L2_OFFSET, \
                                    SBB_EFUSE_L2_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L2_RD_MASK, SBB_EFUSE_L2_WR_MASK, \
                                    "SBB_EFUSE_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H3_OFFSET, \
                                    SBB_EFUSE_H3_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H3_RD_MASK, SBB_EFUSE_H3_WR_MASK, \
                                    "SBB_EFUSE_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L3_OFFSET, \
                                    SBB_EFUSE_L3_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L3_RD_MASK, SBB_EFUSE_L3_WR_MASK, \
                                    "SBB_EFUSE_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H4_OFFSET, \
                                    SBB_EFUSE_H4_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H4_RD_MASK, SBB_EFUSE_H4_WR_MASK, \
                                    "SBB_EFUSE_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L4_OFFSET, \
                                    SBB_EFUSE_L4_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L4_RD_MASK, SBB_EFUSE_L4_WR_MASK, \
                                    "SBB_EFUSE_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H5_OFFSET, \
                                    SBB_EFUSE_H5_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H5_RD_MASK, SBB_EFUSE_H5_WR_MASK, \
                                    "SBB_EFUSE_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L5_OFFSET, \
                                    SBB_EFUSE_L5_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L5_RD_MASK, SBB_EFUSE_L5_WR_MASK, \
                                    "SBB_EFUSE_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H6_OFFSET, \
                                    SBB_EFUSE_H6_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H6_RD_MASK, SBB_EFUSE_H6_WR_MASK, \
                                    "SBB_EFUSE_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L6_OFFSET, \
                                    SBB_EFUSE_L6_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L6_RD_MASK, SBB_EFUSE_L6_WR_MASK, \
                                    "SBB_EFUSE_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H7_OFFSET, \
                                    SBB_EFUSE_H7_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H7_RD_MASK, SBB_EFUSE_H7_WR_MASK, \
                                    "SBB_EFUSE_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L7_OFFSET, \
                                    SBB_EFUSE_L7_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L7_RD_MASK, SBB_EFUSE_L7_WR_MASK, \
                                    "SBB_EFUSE_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H8_OFFSET, \
                                    SBB_EFUSE_H8_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H8_RD_MASK, SBB_EFUSE_H8_WR_MASK, \
                                    "SBB_EFUSE_H8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L8_OFFSET, \
                                    SBB_EFUSE_L8_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L8_RD_MASK, SBB_EFUSE_L8_WR_MASK, \
                                    "SBB_EFUSE_L8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H9_OFFSET, \
                                    SBB_EFUSE_H9_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H9_RD_MASK, SBB_EFUSE_H9_WR_MASK, \
                                    "SBB_EFUSE_H9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L9_OFFSET, \
                                    SBB_EFUSE_L9_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L9_RD_MASK, SBB_EFUSE_L9_WR_MASK, \
                                    "SBB_EFUSE_L9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H10_OFFSET, \
                                    SBB_EFUSE_H10_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H10_RD_MASK, SBB_EFUSE_H10_WR_MASK, \
                                    "SBB_EFUSE_H10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L10_OFFSET, \
                                    SBB_EFUSE_L10_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L10_RD_MASK, SBB_EFUSE_L10_WR_MASK, \
                                    "SBB_EFUSE_L10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H11_OFFSET, \
                                    SBB_EFUSE_H11_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H11_RD_MASK, SBB_EFUSE_H11_WR_MASK, \
                                    "SBB_EFUSE_H11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L11_OFFSET, \
                                    SBB_EFUSE_L11_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L11_RD_MASK, SBB_EFUSE_L11_WR_MASK, \
                                    "SBB_EFUSE_L11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H12_OFFSET, \
                                    SBB_EFUSE_H12_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H12_RD_MASK, SBB_EFUSE_H12_WR_MASK, \
                                    "SBB_EFUSE_H12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L12_OFFSET, \
                                    SBB_EFUSE_L12_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L12_RD_MASK, SBB_EFUSE_L12_WR_MASK, \
                                    "SBB_EFUSE_L12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H13_OFFSET, \
                                    SBB_EFUSE_H13_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H13_RD_MASK, SBB_EFUSE_H13_WR_MASK, \
                                    "SBB_EFUSE_H13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L13_OFFSET, \
                                    SBB_EFUSE_L13_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L13_RD_MASK, SBB_EFUSE_L13_WR_MASK, \
                                    "SBB_EFUSE_L13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H14_OFFSET, \
                                    SBB_EFUSE_H14_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H14_RD_MASK, SBB_EFUSE_H14_WR_MASK, \
                                    "SBB_EFUSE_H14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L14_OFFSET, \
                                    SBB_EFUSE_L14_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L14_RD_MASK, SBB_EFUSE_L14_WR_MASK, \
                                    "SBB_EFUSE_L14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H15_OFFSET, \
                                    SBB_EFUSE_H15_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H15_RD_MASK, SBB_EFUSE_H15_WR_MASK, \
                                    "SBB_EFUSE_H15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L15_OFFSET, \
                                    SBB_EFUSE_L15_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L15_RD_MASK, SBB_EFUSE_L15_WR_MASK, \
                                    "SBB_EFUSE_L15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H16_OFFSET, \
                                    SBB_EFUSE_H16_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H16_RD_MASK, SBB_EFUSE_H16_WR_MASK, \
                                    "SBB_EFUSE_H16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L16_OFFSET, \
                                    SBB_EFUSE_L16_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L16_RD_MASK, SBB_EFUSE_L16_WR_MASK, \
                                    "SBB_EFUSE_L16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H17_OFFSET, \
                                    SBB_EFUSE_H17_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H17_RD_MASK, SBB_EFUSE_H17_WR_MASK, \
                                    "SBB_EFUSE_H17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L17_OFFSET, \
                                    SBB_EFUSE_L17_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L17_RD_MASK, SBB_EFUSE_L17_WR_MASK, \
                                    "SBB_EFUSE_L17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H18_OFFSET, \
                                    SBB_EFUSE_H18_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H18_RD_MASK, SBB_EFUSE_H18_WR_MASK, \
                                    "SBB_EFUSE_H18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L18_OFFSET, \
                                    SBB_EFUSE_L18_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L18_RD_MASK, SBB_EFUSE_L18_WR_MASK, \
                                    "SBB_EFUSE_L18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H19_OFFSET, \
                                    SBB_EFUSE_H19_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H19_RD_MASK, SBB_EFUSE_H19_WR_MASK, \
                                    "SBB_EFUSE_H19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L19_OFFSET, \
                                    SBB_EFUSE_L19_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L19_RD_MASK, SBB_EFUSE_L19_WR_MASK, \
                                    "SBB_EFUSE_L19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H20_OFFSET, \
                                    SBB_EFUSE_H20_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H20_RD_MASK, SBB_EFUSE_H20_WR_MASK, \
                                    "SBB_EFUSE_H20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L20_OFFSET, \
                                    SBB_EFUSE_L20_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L20_RD_MASK, SBB_EFUSE_L20_WR_MASK, \
                                    "SBB_EFUSE_L20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H21_OFFSET, \
                                    SBB_EFUSE_H21_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H21_RD_MASK, SBB_EFUSE_H21_WR_MASK, \
                                    "SBB_EFUSE_H21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L21_OFFSET, \
                                    SBB_EFUSE_L21_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L21_RD_MASK, SBB_EFUSE_L21_WR_MASK, \
                                    "SBB_EFUSE_L21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H22_OFFSET, \
                                    SBB_EFUSE_H22_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H22_RD_MASK, SBB_EFUSE_H22_WR_MASK, \
                                    "SBB_EFUSE_H22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L22_OFFSET, \
                                    SBB_EFUSE_L22_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L22_RD_MASK, SBB_EFUSE_L22_WR_MASK, \
                                    "SBB_EFUSE_L22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H23_OFFSET, \
                                    SBB_EFUSE_H23_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H23_RD_MASK, SBB_EFUSE_H23_WR_MASK, \
                                    "SBB_EFUSE_H23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L23_OFFSET, \
                                    SBB_EFUSE_L23_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L23_RD_MASK, SBB_EFUSE_L23_WR_MASK, \
                                    "SBB_EFUSE_L23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H24_OFFSET, \
                                    SBB_EFUSE_H24_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H24_RD_MASK, SBB_EFUSE_H24_WR_MASK, \
                                    "SBB_EFUSE_H24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L24_OFFSET, \
                                    SBB_EFUSE_L24_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L24_RD_MASK, SBB_EFUSE_L24_WR_MASK, \
                                    "SBB_EFUSE_L24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H25_OFFSET, \
                                    SBB_EFUSE_H25_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H25_RD_MASK, SBB_EFUSE_H25_WR_MASK, \
                                    "SBB_EFUSE_H25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L25_OFFSET, \
                                    SBB_EFUSE_L25_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L25_RD_MASK, SBB_EFUSE_L25_WR_MASK, \
                                    "SBB_EFUSE_L25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H26_OFFSET, \
                                    SBB_EFUSE_H26_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H26_RD_MASK, SBB_EFUSE_H26_WR_MASK, \
                                    "SBB_EFUSE_H26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L26_OFFSET, \
                                    SBB_EFUSE_L26_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L26_RD_MASK, SBB_EFUSE_L26_WR_MASK, \
                                    "SBB_EFUSE_L26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H27_OFFSET, \
                                    SBB_EFUSE_H27_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H27_RD_MASK, SBB_EFUSE_H27_WR_MASK, \
                                    "SBB_EFUSE_H27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L27_OFFSET, \
                                    SBB_EFUSE_L27_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L27_RD_MASK, SBB_EFUSE_L27_WR_MASK, \
                                    "SBB_EFUSE_L27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H28_OFFSET, \
                                    SBB_EFUSE_H28_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H28_RD_MASK, SBB_EFUSE_H28_WR_MASK, \
                                    "SBB_EFUSE_H28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L28_OFFSET, \
                                    SBB_EFUSE_L28_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L28_RD_MASK, SBB_EFUSE_L28_WR_MASK, \
                                    "SBB_EFUSE_L28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H29_OFFSET, \
                                    SBB_EFUSE_H29_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H29_RD_MASK, SBB_EFUSE_H29_WR_MASK, \
                                    "SBB_EFUSE_H29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L29_OFFSET, \
                                    SBB_EFUSE_L29_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L29_RD_MASK, SBB_EFUSE_L29_WR_MASK, \
                                    "SBB_EFUSE_L29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H30_OFFSET, \
                                    SBB_EFUSE_H30_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H30_RD_MASK, SBB_EFUSE_H30_WR_MASK, \
                                    "SBB_EFUSE_H30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L30_OFFSET, \
                                    SBB_EFUSE_L30_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L30_RD_MASK, SBB_EFUSE_L30_WR_MASK, \
                                    "SBB_EFUSE_L30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H31_OFFSET, \
                                    SBB_EFUSE_H31_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H31_RD_MASK, SBB_EFUSE_H31_WR_MASK, \
                                    "SBB_EFUSE_H31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L31_OFFSET, \
                                    SBB_EFUSE_L31_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L31_RD_MASK, SBB_EFUSE_L31_WR_MASK, \
                                    "SBB_EFUSE_L31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H32_OFFSET, \
                                    SBB_EFUSE_H32_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H32_RD_MASK, SBB_EFUSE_H32_WR_MASK, \
                                    "SBB_EFUSE_H32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L32_OFFSET, \
                                    SBB_EFUSE_L32_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L32_RD_MASK, SBB_EFUSE_L32_WR_MASK, \
                                    "SBB_EFUSE_L32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H33_OFFSET, \
                                    SBB_EFUSE_H33_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H33_RD_MASK, SBB_EFUSE_H33_WR_MASK, \
                                    "SBB_EFUSE_H33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L33_OFFSET, \
                                    SBB_EFUSE_L33_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L33_RD_MASK, SBB_EFUSE_L33_WR_MASK, \
                                    "SBB_EFUSE_L33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H34_OFFSET, \
                                    SBB_EFUSE_H34_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H34_RD_MASK, SBB_EFUSE_H34_WR_MASK, \
                                    "SBB_EFUSE_H34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L34_OFFSET, \
                                    SBB_EFUSE_L34_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L34_RD_MASK, SBB_EFUSE_L34_WR_MASK, \
                                    "SBB_EFUSE_L34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H35_OFFSET, \
                                    SBB_EFUSE_H35_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H35_RD_MASK, SBB_EFUSE_H35_WR_MASK, \
                                    "SBB_EFUSE_H35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L35_OFFSET, \
                                    SBB_EFUSE_L35_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L35_RD_MASK, SBB_EFUSE_L35_WR_MASK, \
                                    "SBB_EFUSE_L35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H36_OFFSET, \
                                    SBB_EFUSE_H36_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H36_RD_MASK, SBB_EFUSE_H36_WR_MASK, \
                                    "SBB_EFUSE_H36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L36_OFFSET, \
                                    SBB_EFUSE_L36_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L36_RD_MASK, SBB_EFUSE_L36_WR_MASK, \
                                    "SBB_EFUSE_L36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H37_OFFSET, \
                                    SBB_EFUSE_H37_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H37_RD_MASK, SBB_EFUSE_H37_WR_MASK, \
                                    "SBB_EFUSE_H37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L37_OFFSET, \
                                    SBB_EFUSE_L37_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L37_RD_MASK, SBB_EFUSE_L37_WR_MASK, \
                                    "SBB_EFUSE_L37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H38_OFFSET, \
                                    SBB_EFUSE_H38_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H38_RD_MASK, SBB_EFUSE_H38_WR_MASK, \
                                    "SBB_EFUSE_H38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L38_OFFSET, \
                                    SBB_EFUSE_L38_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L38_RD_MASK, SBB_EFUSE_L38_WR_MASK, \
                                    "SBB_EFUSE_L38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H39_OFFSET, \
                                    SBB_EFUSE_H39_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H39_RD_MASK, SBB_EFUSE_H39_WR_MASK, \
                                    "SBB_EFUSE_H39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L39_OFFSET, \
                                    SBB_EFUSE_L39_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L39_RD_MASK, SBB_EFUSE_L39_WR_MASK, \
                                    "SBB_EFUSE_L39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H40_OFFSET, \
                                    SBB_EFUSE_H40_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H40_RD_MASK, SBB_EFUSE_H40_WR_MASK, \
                                    "SBB_EFUSE_H40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L40_OFFSET, \
                                    SBB_EFUSE_L40_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L40_RD_MASK, SBB_EFUSE_L40_WR_MASK, \
                                    "SBB_EFUSE_L40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H41_OFFSET, \
                                    SBB_EFUSE_H41_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H41_RD_MASK, SBB_EFUSE_H41_WR_MASK, \
                                    "SBB_EFUSE_H41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L41_OFFSET, \
                                    SBB_EFUSE_L41_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L41_RD_MASK, SBB_EFUSE_L41_WR_MASK, \
                                    "SBB_EFUSE_L41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H42_OFFSET, \
                                    SBB_EFUSE_H42_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H42_RD_MASK, SBB_EFUSE_H42_WR_MASK, \
                                    "SBB_EFUSE_H42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L42_OFFSET, \
                                    SBB_EFUSE_L42_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L42_RD_MASK, SBB_EFUSE_L42_WR_MASK, \
                                    "SBB_EFUSE_L42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H43_OFFSET, \
                                    SBB_EFUSE_H43_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H43_RD_MASK, SBB_EFUSE_H43_WR_MASK, \
                                    "SBB_EFUSE_H43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L43_OFFSET, \
                                    SBB_EFUSE_L43_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L43_RD_MASK, SBB_EFUSE_L43_WR_MASK, \
                                    "SBB_EFUSE_L43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H44_OFFSET, \
                                    SBB_EFUSE_H44_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H44_RD_MASK, SBB_EFUSE_H44_WR_MASK, \
                                    "SBB_EFUSE_H44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L44_OFFSET, \
                                    SBB_EFUSE_L44_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L44_RD_MASK, SBB_EFUSE_L44_WR_MASK, \
                                    "SBB_EFUSE_L44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H45_OFFSET, \
                                    SBB_EFUSE_H45_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H45_RD_MASK, SBB_EFUSE_H45_WR_MASK, \
                                    "SBB_EFUSE_H45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L45_OFFSET, \
                                    SBB_EFUSE_L45_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L45_RD_MASK, SBB_EFUSE_L45_WR_MASK, \
                                    "SBB_EFUSE_L45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H46_OFFSET, \
                                    SBB_EFUSE_H46_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H46_RD_MASK, SBB_EFUSE_H46_WR_MASK, \
                                    "SBB_EFUSE_H46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L46_OFFSET, \
                                    SBB_EFUSE_L46_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L46_RD_MASK, SBB_EFUSE_L46_WR_MASK, \
                                    "SBB_EFUSE_L46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H47_OFFSET, \
                                    SBB_EFUSE_H47_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H47_RD_MASK, SBB_EFUSE_H47_WR_MASK, \
                                    "SBB_EFUSE_H47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L47_OFFSET, \
                                    SBB_EFUSE_L47_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L47_RD_MASK, SBB_EFUSE_L47_WR_MASK, \
                                    "SBB_EFUSE_L47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H48_OFFSET, \
                                    SBB_EFUSE_H48_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H48_RD_MASK, SBB_EFUSE_H48_WR_MASK, \
                                    "SBB_EFUSE_H48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L48_OFFSET, \
                                    SBB_EFUSE_L48_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L48_RD_MASK, SBB_EFUSE_L48_WR_MASK, \
                                    "SBB_EFUSE_L48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H49_OFFSET, \
                                    SBB_EFUSE_H49_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H49_RD_MASK, SBB_EFUSE_H49_WR_MASK, \
                                    "SBB_EFUSE_H49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L49_OFFSET, \
                                    SBB_EFUSE_L49_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L49_RD_MASK, SBB_EFUSE_L49_WR_MASK, \
                                    "SBB_EFUSE_L49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H50_OFFSET, \
                                    SBB_EFUSE_H50_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H50_RD_MASK, SBB_EFUSE_H50_WR_MASK, \
                                    "SBB_EFUSE_H50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L50_OFFSET, \
                                    SBB_EFUSE_L50_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L50_RD_MASK, SBB_EFUSE_L50_WR_MASK, \
                                    "SBB_EFUSE_L50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H51_OFFSET, \
                                    SBB_EFUSE_H51_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H51_RD_MASK, SBB_EFUSE_H51_WR_MASK, \
                                    "SBB_EFUSE_H51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L51_OFFSET, \
                                    SBB_EFUSE_L51_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L51_RD_MASK, SBB_EFUSE_L51_WR_MASK, \
                                    "SBB_EFUSE_L51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H52_OFFSET, \
                                    SBB_EFUSE_H52_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H52_RD_MASK, SBB_EFUSE_H52_WR_MASK, \
                                    "SBB_EFUSE_H52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L52_OFFSET, \
                                    SBB_EFUSE_L52_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L52_RD_MASK, SBB_EFUSE_L52_WR_MASK, \
                                    "SBB_EFUSE_L52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H53_OFFSET, \
                                    SBB_EFUSE_H53_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H53_RD_MASK, SBB_EFUSE_H53_WR_MASK, \
                                    "SBB_EFUSE_H53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L53_OFFSET, \
                                    SBB_EFUSE_L53_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L53_RD_MASK, SBB_EFUSE_L53_WR_MASK, \
                                    "SBB_EFUSE_L53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H54_OFFSET, \
                                    SBB_EFUSE_H54_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H54_RD_MASK, SBB_EFUSE_H54_WR_MASK, \
                                    "SBB_EFUSE_H54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L54_OFFSET, \
                                    SBB_EFUSE_L54_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L54_RD_MASK, SBB_EFUSE_L54_WR_MASK, \
                                    "SBB_EFUSE_L54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H55_OFFSET, \
                                    SBB_EFUSE_H55_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H55_RD_MASK, SBB_EFUSE_H55_WR_MASK, \
                                    "SBB_EFUSE_H55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L55_OFFSET, \
                                    SBB_EFUSE_L55_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L55_RD_MASK, SBB_EFUSE_L55_WR_MASK, \
                                    "SBB_EFUSE_L55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H56_OFFSET, \
                                    SBB_EFUSE_H56_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H56_RD_MASK, SBB_EFUSE_H56_WR_MASK, \
                                    "SBB_EFUSE_H56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L56_OFFSET, \
                                    SBB_EFUSE_L56_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L56_RD_MASK, SBB_EFUSE_L56_WR_MASK, \
                                    "SBB_EFUSE_L56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H57_OFFSET, \
                                    SBB_EFUSE_H57_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H57_RD_MASK, SBB_EFUSE_H57_WR_MASK, \
                                    "SBB_EFUSE_H57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L57_OFFSET, \
                                    SBB_EFUSE_L57_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L57_RD_MASK, SBB_EFUSE_L57_WR_MASK, \
                                    "SBB_EFUSE_L57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H58_OFFSET, \
                                    SBB_EFUSE_H58_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H58_RD_MASK, SBB_EFUSE_H58_WR_MASK, \
                                    "SBB_EFUSE_H58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L58_OFFSET, \
                                    SBB_EFUSE_L58_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L58_RD_MASK, SBB_EFUSE_L58_WR_MASK, \
                                    "SBB_EFUSE_L58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H59_OFFSET, \
                                    SBB_EFUSE_H59_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H59_RD_MASK, SBB_EFUSE_H59_WR_MASK, \
                                    "SBB_EFUSE_H59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L59_OFFSET, \
                                    SBB_EFUSE_L59_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L59_RD_MASK, SBB_EFUSE_L59_WR_MASK, \
                                    "SBB_EFUSE_L59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H60_OFFSET, \
                                    SBB_EFUSE_H60_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H60_RD_MASK, SBB_EFUSE_H60_WR_MASK, \
                                    "SBB_EFUSE_H60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L60_OFFSET, \
                                    SBB_EFUSE_L60_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L60_RD_MASK, SBB_EFUSE_L60_WR_MASK, \
                                    "SBB_EFUSE_L60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H61_OFFSET, \
                                    SBB_EFUSE_H61_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H61_RD_MASK, SBB_EFUSE_H61_WR_MASK, \
                                    "SBB_EFUSE_H61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L61_OFFSET, \
                                    SBB_EFUSE_L61_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L61_RD_MASK, SBB_EFUSE_L61_WR_MASK, \
                                    "SBB_EFUSE_L61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H62_OFFSET, \
                                    SBB_EFUSE_H62_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H62_RD_MASK, SBB_EFUSE_H62_WR_MASK, \
                                    "SBB_EFUSE_H62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L62_OFFSET, \
                                    SBB_EFUSE_L62_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L62_RD_MASK, SBB_EFUSE_L62_WR_MASK, \
                                    "SBB_EFUSE_L62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H63_OFFSET, \
                                    SBB_EFUSE_H63_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H63_RD_MASK, SBB_EFUSE_H63_WR_MASK, \
                                    "SBB_EFUSE_H63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L63_OFFSET, \
                                    SBB_EFUSE_L63_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L63_RD_MASK, SBB_EFUSE_L63_WR_MASK, \
                                    "SBB_EFUSE_L63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H64_OFFSET, \
                                    SBB_EFUSE_H64_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H64_RD_MASK, SBB_EFUSE_H64_WR_MASK, \
                                    "SBB_EFUSE_H64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L64_OFFSET, \
                                    SBB_EFUSE_L64_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L64_RD_MASK, SBB_EFUSE_L64_WR_MASK, \
                                    "SBB_EFUSE_L64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H65_OFFSET, \
                                    SBB_EFUSE_H65_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H65_RD_MASK, SBB_EFUSE_H65_WR_MASK, \
                                    "SBB_EFUSE_H65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L65_OFFSET, \
                                    SBB_EFUSE_L65_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L65_RD_MASK, SBB_EFUSE_L65_WR_MASK, \
                                    "SBB_EFUSE_L65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H66_OFFSET, \
                                    SBB_EFUSE_H66_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H66_RD_MASK, SBB_EFUSE_H66_WR_MASK, \
                                    "SBB_EFUSE_H66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L66_OFFSET, \
                                    SBB_EFUSE_L66_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L66_RD_MASK, SBB_EFUSE_L66_WR_MASK, \
                                    "SBB_EFUSE_L66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H67_OFFSET, \
                                    SBB_EFUSE_H67_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H67_RD_MASK, SBB_EFUSE_H67_WR_MASK, \
                                    "SBB_EFUSE_H67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L67_OFFSET, \
                                    SBB_EFUSE_L67_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L67_RD_MASK, SBB_EFUSE_L67_WR_MASK, \
                                    "SBB_EFUSE_L67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H68_OFFSET, \
                                    SBB_EFUSE_H68_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H68_RD_MASK, SBB_EFUSE_H68_WR_MASK, \
                                    "SBB_EFUSE_H68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L68_OFFSET, \
                                    SBB_EFUSE_L68_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L68_RD_MASK, SBB_EFUSE_L68_WR_MASK, \
                                    "SBB_EFUSE_L68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H69_OFFSET, \
                                    SBB_EFUSE_H69_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H69_RD_MASK, SBB_EFUSE_H69_WR_MASK, \
                                    "SBB_EFUSE_H69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L69_OFFSET, \
                                    SBB_EFUSE_L69_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L69_RD_MASK, SBB_EFUSE_L69_WR_MASK, \
                                    "SBB_EFUSE_L69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H70_OFFSET, \
                                    SBB_EFUSE_H70_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H70_RD_MASK, SBB_EFUSE_H70_WR_MASK, \
                                    "SBB_EFUSE_H70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L70_OFFSET, \
                                    SBB_EFUSE_L70_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L70_RD_MASK, SBB_EFUSE_L70_WR_MASK, \
                                    "SBB_EFUSE_L70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H71_OFFSET, \
                                    SBB_EFUSE_H71_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H71_RD_MASK, SBB_EFUSE_H71_WR_MASK, \
                                    "SBB_EFUSE_H71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L71_OFFSET, \
                                    SBB_EFUSE_L71_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L71_RD_MASK, SBB_EFUSE_L71_WR_MASK, \
                                    "SBB_EFUSE_L71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H72_OFFSET, \
                                    SBB_EFUSE_H72_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H72_RD_MASK, SBB_EFUSE_H72_WR_MASK, \
                                    "SBB_EFUSE_H72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L72_OFFSET, \
                                    SBB_EFUSE_L72_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L72_RD_MASK, SBB_EFUSE_L72_WR_MASK, \
                                    "SBB_EFUSE_L72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H73_OFFSET, \
                                    SBB_EFUSE_H73_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H73_RD_MASK, SBB_EFUSE_H73_WR_MASK, \
                                    "SBB_EFUSE_H73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L73_OFFSET, \
                                    SBB_EFUSE_L73_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L73_RD_MASK, SBB_EFUSE_L73_WR_MASK, \
                                    "SBB_EFUSE_L73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H74_OFFSET, \
                                    SBB_EFUSE_H74_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H74_RD_MASK, SBB_EFUSE_H74_WR_MASK, \
                                    "SBB_EFUSE_H74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L74_OFFSET, \
                                    SBB_EFUSE_L74_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L74_RD_MASK, SBB_EFUSE_L74_WR_MASK, \
                                    "SBB_EFUSE_L74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H75_OFFSET, \
                                    SBB_EFUSE_H75_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H75_RD_MASK, SBB_EFUSE_H75_WR_MASK, \
                                    "SBB_EFUSE_H75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L75_OFFSET, \
                                    SBB_EFUSE_L75_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L75_RD_MASK, SBB_EFUSE_L75_WR_MASK, \
                                    "SBB_EFUSE_L75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H76_OFFSET, \
                                    SBB_EFUSE_H76_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H76_RD_MASK, SBB_EFUSE_H76_WR_MASK, \
                                    "SBB_EFUSE_H76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L76_OFFSET, \
                                    SBB_EFUSE_L76_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L76_RD_MASK, SBB_EFUSE_L76_WR_MASK, \
                                    "SBB_EFUSE_L76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H77_OFFSET, \
                                    SBB_EFUSE_H77_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H77_RD_MASK, SBB_EFUSE_H77_WR_MASK, \
                                    "SBB_EFUSE_H77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L77_OFFSET, \
                                    SBB_EFUSE_L77_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L77_RD_MASK, SBB_EFUSE_L77_WR_MASK, \
                                    "SBB_EFUSE_L77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H78_OFFSET, \
                                    SBB_EFUSE_H78_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H78_RD_MASK, SBB_EFUSE_H78_WR_MASK, \
                                    "SBB_EFUSE_H78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L78_OFFSET, \
                                    SBB_EFUSE_L78_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L78_RD_MASK, SBB_EFUSE_L78_WR_MASK, \
                                    "SBB_EFUSE_L78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H79_OFFSET, \
                                    SBB_EFUSE_H79_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H79_RD_MASK, SBB_EFUSE_H79_WR_MASK, \
                                    "SBB_EFUSE_H79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L79_OFFSET, \
                                    SBB_EFUSE_L79_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L79_RD_MASK, SBB_EFUSE_L79_WR_MASK, \
                                    "SBB_EFUSE_L79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H80_OFFSET, \
                                    SBB_EFUSE_H80_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H80_RD_MASK, SBB_EFUSE_H80_WR_MASK, \
                                    "SBB_EFUSE_H80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L80_OFFSET, \
                                    SBB_EFUSE_L80_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L80_RD_MASK, SBB_EFUSE_L80_WR_MASK, \
                                    "SBB_EFUSE_L80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H81_OFFSET, \
                                    SBB_EFUSE_H81_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H81_RD_MASK, SBB_EFUSE_H81_WR_MASK, \
                                    "SBB_EFUSE_H81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L81_OFFSET, \
                                    SBB_EFUSE_L81_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L81_RD_MASK, SBB_EFUSE_L81_WR_MASK, \
                                    "SBB_EFUSE_L81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H82_OFFSET, \
                                    SBB_EFUSE_H82_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H82_RD_MASK, SBB_EFUSE_H82_WR_MASK, \
                                    "SBB_EFUSE_H82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L82_OFFSET, \
                                    SBB_EFUSE_L82_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L82_RD_MASK, SBB_EFUSE_L82_WR_MASK, \
                                    "SBB_EFUSE_L82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H83_OFFSET, \
                                    SBB_EFUSE_H83_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H83_RD_MASK, SBB_EFUSE_H83_WR_MASK, \
                                    "SBB_EFUSE_H83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L83_OFFSET, \
                                    SBB_EFUSE_L83_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L83_RD_MASK, SBB_EFUSE_L83_WR_MASK, \
                                    "SBB_EFUSE_L83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H84_OFFSET, \
                                    SBB_EFUSE_H84_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H84_RD_MASK, SBB_EFUSE_H84_WR_MASK, \
                                    "SBB_EFUSE_H84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L84_OFFSET, \
                                    SBB_EFUSE_L84_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L84_RD_MASK, SBB_EFUSE_L84_WR_MASK, \
                                    "SBB_EFUSE_L84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H85_OFFSET, \
                                    SBB_EFUSE_H85_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H85_RD_MASK, SBB_EFUSE_H85_WR_MASK, \
                                    "SBB_EFUSE_H85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L85_OFFSET, \
                                    SBB_EFUSE_L85_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L85_RD_MASK, SBB_EFUSE_L85_WR_MASK, \
                                    "SBB_EFUSE_L85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H86_OFFSET, \
                                    SBB_EFUSE_H86_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H86_RD_MASK, SBB_EFUSE_H86_WR_MASK, \
                                    "SBB_EFUSE_H86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L86_OFFSET, \
                                    SBB_EFUSE_L86_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L86_RD_MASK, SBB_EFUSE_L86_WR_MASK, \
                                    "SBB_EFUSE_L86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H87_OFFSET, \
                                    SBB_EFUSE_H87_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H87_RD_MASK, SBB_EFUSE_H87_WR_MASK, \
                                    "SBB_EFUSE_H87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L87_OFFSET, \
                                    SBB_EFUSE_L87_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L87_RD_MASK, SBB_EFUSE_L87_WR_MASK, \
                                    "SBB_EFUSE_L87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H88_OFFSET, \
                                    SBB_EFUSE_H88_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H88_RD_MASK, SBB_EFUSE_H88_WR_MASK, \
                                    "SBB_EFUSE_H88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L88_OFFSET, \
                                    SBB_EFUSE_L88_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L88_RD_MASK, SBB_EFUSE_L88_WR_MASK, \
                                    "SBB_EFUSE_L88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H89_OFFSET, \
                                    SBB_EFUSE_H89_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H89_RD_MASK, SBB_EFUSE_H89_WR_MASK, \
                                    "SBB_EFUSE_H89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L89_OFFSET, \
                                    SBB_EFUSE_L89_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L89_RD_MASK, SBB_EFUSE_L89_WR_MASK, \
                                    "SBB_EFUSE_L89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H90_OFFSET, \
                                    SBB_EFUSE_H90_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H90_RD_MASK, SBB_EFUSE_H90_WR_MASK, \
                                    "SBB_EFUSE_H90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L90_OFFSET, \
                                    SBB_EFUSE_L90_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L90_RD_MASK, SBB_EFUSE_L90_WR_MASK, \
                                    "SBB_EFUSE_L90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H91_OFFSET, \
                                    SBB_EFUSE_H91_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H91_RD_MASK, SBB_EFUSE_H91_WR_MASK, \
                                    "SBB_EFUSE_H91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L91_OFFSET, \
                                    SBB_EFUSE_L91_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L91_RD_MASK, SBB_EFUSE_L91_WR_MASK, \
                                    "SBB_EFUSE_L91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H92_OFFSET, \
                                    SBB_EFUSE_H92_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H92_RD_MASK, SBB_EFUSE_H92_WR_MASK, \
                                    "SBB_EFUSE_H92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L92_OFFSET, \
                                    SBB_EFUSE_L92_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L92_RD_MASK, SBB_EFUSE_L92_WR_MASK, \
                                    "SBB_EFUSE_L92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H93_OFFSET, \
                                    SBB_EFUSE_H93_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H93_RD_MASK, SBB_EFUSE_H93_WR_MASK, \
                                    "SBB_EFUSE_H93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L93_OFFSET, \
                                    SBB_EFUSE_L93_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L93_RD_MASK, SBB_EFUSE_L93_WR_MASK, \
                                    "SBB_EFUSE_L93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H94_OFFSET, \
                                    SBB_EFUSE_H94_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H94_RD_MASK, SBB_EFUSE_H94_WR_MASK, \
                                    "SBB_EFUSE_H94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L94_OFFSET, \
                                    SBB_EFUSE_L94_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L94_RD_MASK, SBB_EFUSE_L94_WR_MASK, \
                                    "SBB_EFUSE_L94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H95_OFFSET, \
                                    SBB_EFUSE_H95_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H95_RD_MASK, SBB_EFUSE_H95_WR_MASK, \
                                    "SBB_EFUSE_H95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L95_OFFSET, \
                                    SBB_EFUSE_L95_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L95_RD_MASK, SBB_EFUSE_L95_WR_MASK, \
                                    "SBB_EFUSE_L95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H96_OFFSET, \
                                    SBB_EFUSE_H96_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H96_RD_MASK, SBB_EFUSE_H96_WR_MASK, \
                                    "SBB_EFUSE_H96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L96_OFFSET, \
                                    SBB_EFUSE_L96_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L96_RD_MASK, SBB_EFUSE_L96_WR_MASK, \
                                    "SBB_EFUSE_L96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H97_OFFSET, \
                                    SBB_EFUSE_H97_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H97_RD_MASK, SBB_EFUSE_H97_WR_MASK, \
                                    "SBB_EFUSE_H97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L97_OFFSET, \
                                    SBB_EFUSE_L97_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L97_RD_MASK, SBB_EFUSE_L97_WR_MASK, \
                                    "SBB_EFUSE_L97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H98_OFFSET, \
                                    SBB_EFUSE_H98_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H98_RD_MASK, SBB_EFUSE_H98_WR_MASK, \
                                    "SBB_EFUSE_H98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L98_OFFSET, \
                                    SBB_EFUSE_L98_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L98_RD_MASK, SBB_EFUSE_L98_WR_MASK, \
                                    "SBB_EFUSE_L98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H99_OFFSET, \
                                    SBB_EFUSE_H99_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H99_RD_MASK, SBB_EFUSE_H99_WR_MASK, \
                                    "SBB_EFUSE_H99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L99_OFFSET, \
                                    SBB_EFUSE_L99_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L99_RD_MASK, SBB_EFUSE_L99_WR_MASK, \
                                    "SBB_EFUSE_L99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H100_OFFSET, \
                                    SBB_EFUSE_H100_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H100_RD_MASK, SBB_EFUSE_H100_WR_MASK, \
                                    "SBB_EFUSE_H100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L100_OFFSET, \
                                    SBB_EFUSE_L100_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L100_RD_MASK, SBB_EFUSE_L100_WR_MASK, \
                                    "SBB_EFUSE_L100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H101_OFFSET, \
                                    SBB_EFUSE_H101_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H101_RD_MASK, SBB_EFUSE_H101_WR_MASK, \
                                    "SBB_EFUSE_H101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L101_OFFSET, \
                                    SBB_EFUSE_L101_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L101_RD_MASK, SBB_EFUSE_L101_WR_MASK, \
                                    "SBB_EFUSE_L101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H102_OFFSET, \
                                    SBB_EFUSE_H102_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H102_RD_MASK, SBB_EFUSE_H102_WR_MASK, \
                                    "SBB_EFUSE_H102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L102_OFFSET, \
                                    SBB_EFUSE_L102_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L102_RD_MASK, SBB_EFUSE_L102_WR_MASK, \
                                    "SBB_EFUSE_L102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H103_OFFSET, \
                                    SBB_EFUSE_H103_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H103_RD_MASK, SBB_EFUSE_H103_WR_MASK, \
                                    "SBB_EFUSE_H103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L103_OFFSET, \
                                    SBB_EFUSE_L103_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L103_RD_MASK, SBB_EFUSE_L103_WR_MASK, \
                                    "SBB_EFUSE_L103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H104_OFFSET, \
                                    SBB_EFUSE_H104_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H104_RD_MASK, SBB_EFUSE_H104_WR_MASK, \
                                    "SBB_EFUSE_H104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L104_OFFSET, \
                                    SBB_EFUSE_L104_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L104_RD_MASK, SBB_EFUSE_L104_WR_MASK, \
                                    "SBB_EFUSE_L104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H105_OFFSET, \
                                    SBB_EFUSE_H105_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H105_RD_MASK, SBB_EFUSE_H105_WR_MASK, \
                                    "SBB_EFUSE_H105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L105_OFFSET, \
                                    SBB_EFUSE_L105_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L105_RD_MASK, SBB_EFUSE_L105_WR_MASK, \
                                    "SBB_EFUSE_L105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H106_OFFSET, \
                                    SBB_EFUSE_H106_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H106_RD_MASK, SBB_EFUSE_H106_WR_MASK, \
                                    "SBB_EFUSE_H106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L106_OFFSET, \
                                    SBB_EFUSE_L106_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L106_RD_MASK, SBB_EFUSE_L106_WR_MASK, \
                                    "SBB_EFUSE_L106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H107_OFFSET, \
                                    SBB_EFUSE_H107_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H107_RD_MASK, SBB_EFUSE_H107_WR_MASK, \
                                    "SBB_EFUSE_H107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L107_OFFSET, \
                                    SBB_EFUSE_L107_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L107_RD_MASK, SBB_EFUSE_L107_WR_MASK, \
                                    "SBB_EFUSE_L107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H108_OFFSET, \
                                    SBB_EFUSE_H108_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H108_RD_MASK, SBB_EFUSE_H108_WR_MASK, \
                                    "SBB_EFUSE_H108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L108_OFFSET, \
                                    SBB_EFUSE_L108_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L108_RD_MASK, SBB_EFUSE_L108_WR_MASK, \
                                    "SBB_EFUSE_L108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H109_OFFSET, \
                                    SBB_EFUSE_H109_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H109_RD_MASK, SBB_EFUSE_H109_WR_MASK, \
                                    "SBB_EFUSE_H109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L109_OFFSET, \
                                    SBB_EFUSE_L109_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L109_RD_MASK, SBB_EFUSE_L109_WR_MASK, \
                                    "SBB_EFUSE_L109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H110_OFFSET, \
                                    SBB_EFUSE_H110_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H110_RD_MASK, SBB_EFUSE_H110_WR_MASK, \
                                    "SBB_EFUSE_H110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L110_OFFSET, \
                                    SBB_EFUSE_L110_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L110_RD_MASK, SBB_EFUSE_L110_WR_MASK, \
                                    "SBB_EFUSE_L110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_H111_OFFSET, \
                                    SBB_EFUSE_H111_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_H111_RD_MASK, SBB_EFUSE_H111_WR_MASK, \
                                    "SBB_EFUSE_H111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_EFUSE_L111_OFFSET, \
                                    SBB_EFUSE_L111_DEFAULT, write_data, expected_data, \
                                    SBB_EFUSE_L111_RD_MASK, SBB_EFUSE_L111_WR_MASK, \
                                    "SBB_EFUSE_L111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H0_OFFSET, \
                                    SBB_PARAM_EXT_H0_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H0_RD_MASK, SBB_PARAM_EXT_H0_WR_MASK, \
                                    "SBB_PARAM_EXT_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L0_OFFSET, \
                                    SBB_PARAM_EXT_L0_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L0_RD_MASK, SBB_PARAM_EXT_L0_WR_MASK, \
                                    "SBB_PARAM_EXT_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H1_OFFSET, \
                                    SBB_PARAM_EXT_H1_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H1_RD_MASK, SBB_PARAM_EXT_H1_WR_MASK, \
                                    "SBB_PARAM_EXT_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L1_OFFSET, \
                                    SBB_PARAM_EXT_L1_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L1_RD_MASK, SBB_PARAM_EXT_L1_WR_MASK, \
                                    "SBB_PARAM_EXT_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H2_OFFSET, \
                                    SBB_PARAM_EXT_H2_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H2_RD_MASK, SBB_PARAM_EXT_H2_WR_MASK, \
                                    "SBB_PARAM_EXT_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L2_OFFSET, \
                                    SBB_PARAM_EXT_L2_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L2_RD_MASK, SBB_PARAM_EXT_L2_WR_MASK, \
                                    "SBB_PARAM_EXT_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H3_OFFSET, \
                                    SBB_PARAM_EXT_H3_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H3_RD_MASK, SBB_PARAM_EXT_H3_WR_MASK, \
                                    "SBB_PARAM_EXT_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L3_OFFSET, \
                                    SBB_PARAM_EXT_L3_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L3_RD_MASK, SBB_PARAM_EXT_L3_WR_MASK, \
                                    "SBB_PARAM_EXT_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H4_OFFSET, \
                                    SBB_PARAM_EXT_H4_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H4_RD_MASK, SBB_PARAM_EXT_H4_WR_MASK, \
                                    "SBB_PARAM_EXT_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L4_OFFSET, \
                                    SBB_PARAM_EXT_L4_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L4_RD_MASK, SBB_PARAM_EXT_L4_WR_MASK, \
                                    "SBB_PARAM_EXT_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H5_OFFSET, \
                                    SBB_PARAM_EXT_H5_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H5_RD_MASK, SBB_PARAM_EXT_H5_WR_MASK, \
                                    "SBB_PARAM_EXT_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L5_OFFSET, \
                                    SBB_PARAM_EXT_L5_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L5_RD_MASK, SBB_PARAM_EXT_L5_WR_MASK, \
                                    "SBB_PARAM_EXT_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H6_OFFSET, \
                                    SBB_PARAM_EXT_H6_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H6_RD_MASK, SBB_PARAM_EXT_H6_WR_MASK, \
                                    "SBB_PARAM_EXT_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L6_OFFSET, \
                                    SBB_PARAM_EXT_L6_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L6_RD_MASK, SBB_PARAM_EXT_L6_WR_MASK, \
                                    "SBB_PARAM_EXT_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H7_OFFSET, \
                                    SBB_PARAM_EXT_H7_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H7_RD_MASK, SBB_PARAM_EXT_H7_WR_MASK, \
                                    "SBB_PARAM_EXT_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L7_OFFSET, \
                                    SBB_PARAM_EXT_L7_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L7_RD_MASK, SBB_PARAM_EXT_L7_WR_MASK, \
                                    "SBB_PARAM_EXT_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H8_OFFSET, \
                                    SBB_PARAM_EXT_H8_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H8_RD_MASK, SBB_PARAM_EXT_H8_WR_MASK, \
                                    "SBB_PARAM_EXT_H8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L8_OFFSET, \
                                    SBB_PARAM_EXT_L8_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L8_RD_MASK, SBB_PARAM_EXT_L8_WR_MASK, \
                                    "SBB_PARAM_EXT_L8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H9_OFFSET, \
                                    SBB_PARAM_EXT_H9_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H9_RD_MASK, SBB_PARAM_EXT_H9_WR_MASK, \
                                    "SBB_PARAM_EXT_H9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L9_OFFSET, \
                                    SBB_PARAM_EXT_L9_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L9_RD_MASK, SBB_PARAM_EXT_L9_WR_MASK, \
                                    "SBB_PARAM_EXT_L9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H10_OFFSET, \
                                    SBB_PARAM_EXT_H10_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H10_RD_MASK, SBB_PARAM_EXT_H10_WR_MASK, \
                                    "SBB_PARAM_EXT_H10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L10_OFFSET, \
                                    SBB_PARAM_EXT_L10_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L10_RD_MASK, SBB_PARAM_EXT_L10_WR_MASK, \
                                    "SBB_PARAM_EXT_L10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H11_OFFSET, \
                                    SBB_PARAM_EXT_H11_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H11_RD_MASK, SBB_PARAM_EXT_H11_WR_MASK, \
                                    "SBB_PARAM_EXT_H11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L11_OFFSET, \
                                    SBB_PARAM_EXT_L11_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L11_RD_MASK, SBB_PARAM_EXT_L11_WR_MASK, \
                                    "SBB_PARAM_EXT_L11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H12_OFFSET, \
                                    SBB_PARAM_EXT_H12_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H12_RD_MASK, SBB_PARAM_EXT_H12_WR_MASK, \
                                    "SBB_PARAM_EXT_H12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L12_OFFSET, \
                                    SBB_PARAM_EXT_L12_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L12_RD_MASK, SBB_PARAM_EXT_L12_WR_MASK, \
                                    "SBB_PARAM_EXT_L12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H13_OFFSET, \
                                    SBB_PARAM_EXT_H13_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H13_RD_MASK, SBB_PARAM_EXT_H13_WR_MASK, \
                                    "SBB_PARAM_EXT_H13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L13_OFFSET, \
                                    SBB_PARAM_EXT_L13_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L13_RD_MASK, SBB_PARAM_EXT_L13_WR_MASK, \
                                    "SBB_PARAM_EXT_L13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H14_OFFSET, \
                                    SBB_PARAM_EXT_H14_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H14_RD_MASK, SBB_PARAM_EXT_H14_WR_MASK, \
                                    "SBB_PARAM_EXT_H14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L14_OFFSET, \
                                    SBB_PARAM_EXT_L14_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L14_RD_MASK, SBB_PARAM_EXT_L14_WR_MASK, \
                                    "SBB_PARAM_EXT_L14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H15_OFFSET, \
                                    SBB_PARAM_EXT_H15_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H15_RD_MASK, SBB_PARAM_EXT_H15_WR_MASK, \
                                    "SBB_PARAM_EXT_H15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L15_OFFSET, \
                                    SBB_PARAM_EXT_L15_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L15_RD_MASK, SBB_PARAM_EXT_L15_WR_MASK, \
                                    "SBB_PARAM_EXT_L15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H16_OFFSET, \
                                    SBB_PARAM_EXT_H16_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H16_RD_MASK, SBB_PARAM_EXT_H16_WR_MASK, \
                                    "SBB_PARAM_EXT_H16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L16_OFFSET, \
                                    SBB_PARAM_EXT_L16_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L16_RD_MASK, SBB_PARAM_EXT_L16_WR_MASK, \
                                    "SBB_PARAM_EXT_L16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H17_OFFSET, \
                                    SBB_PARAM_EXT_H17_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H17_RD_MASK, SBB_PARAM_EXT_H17_WR_MASK, \
                                    "SBB_PARAM_EXT_H17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L17_OFFSET, \
                                    SBB_PARAM_EXT_L17_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L17_RD_MASK, SBB_PARAM_EXT_L17_WR_MASK, \
                                    "SBB_PARAM_EXT_L17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H18_OFFSET, \
                                    SBB_PARAM_EXT_H18_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H18_RD_MASK, SBB_PARAM_EXT_H18_WR_MASK, \
                                    "SBB_PARAM_EXT_H18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L18_OFFSET, \
                                    SBB_PARAM_EXT_L18_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L18_RD_MASK, SBB_PARAM_EXT_L18_WR_MASK, \
                                    "SBB_PARAM_EXT_L18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H19_OFFSET, \
                                    SBB_PARAM_EXT_H19_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H19_RD_MASK, SBB_PARAM_EXT_H19_WR_MASK, \
                                    "SBB_PARAM_EXT_H19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L19_OFFSET, \
                                    SBB_PARAM_EXT_L19_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L19_RD_MASK, SBB_PARAM_EXT_L19_WR_MASK, \
                                    "SBB_PARAM_EXT_L19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H20_OFFSET, \
                                    SBB_PARAM_EXT_H20_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H20_RD_MASK, SBB_PARAM_EXT_H20_WR_MASK, \
                                    "SBB_PARAM_EXT_H20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L20_OFFSET, \
                                    SBB_PARAM_EXT_L20_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L20_RD_MASK, SBB_PARAM_EXT_L20_WR_MASK, \
                                    "SBB_PARAM_EXT_L20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H21_OFFSET, \
                                    SBB_PARAM_EXT_H21_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H21_RD_MASK, SBB_PARAM_EXT_H21_WR_MASK, \
                                    "SBB_PARAM_EXT_H21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L21_OFFSET, \
                                    SBB_PARAM_EXT_L21_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L21_RD_MASK, SBB_PARAM_EXT_L21_WR_MASK, \
                                    "SBB_PARAM_EXT_L21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H22_OFFSET, \
                                    SBB_PARAM_EXT_H22_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H22_RD_MASK, SBB_PARAM_EXT_H22_WR_MASK, \
                                    "SBB_PARAM_EXT_H22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L22_OFFSET, \
                                    SBB_PARAM_EXT_L22_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L22_RD_MASK, SBB_PARAM_EXT_L22_WR_MASK, \
                                    "SBB_PARAM_EXT_L22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H23_OFFSET, \
                                    SBB_PARAM_EXT_H23_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H23_RD_MASK, SBB_PARAM_EXT_H23_WR_MASK, \
                                    "SBB_PARAM_EXT_H23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L23_OFFSET, \
                                    SBB_PARAM_EXT_L23_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L23_RD_MASK, SBB_PARAM_EXT_L23_WR_MASK, \
                                    "SBB_PARAM_EXT_L23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H24_OFFSET, \
                                    SBB_PARAM_EXT_H24_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H24_RD_MASK, SBB_PARAM_EXT_H24_WR_MASK, \
                                    "SBB_PARAM_EXT_H24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L24_OFFSET, \
                                    SBB_PARAM_EXT_L24_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L24_RD_MASK, SBB_PARAM_EXT_L24_WR_MASK, \
                                    "SBB_PARAM_EXT_L24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H25_OFFSET, \
                                    SBB_PARAM_EXT_H25_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H25_RD_MASK, SBB_PARAM_EXT_H25_WR_MASK, \
                                    "SBB_PARAM_EXT_H25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L25_OFFSET, \
                                    SBB_PARAM_EXT_L25_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L25_RD_MASK, SBB_PARAM_EXT_L25_WR_MASK, \
                                    "SBB_PARAM_EXT_L25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H26_OFFSET, \
                                    SBB_PARAM_EXT_H26_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H26_RD_MASK, SBB_PARAM_EXT_H26_WR_MASK, \
                                    "SBB_PARAM_EXT_H26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L26_OFFSET, \
                                    SBB_PARAM_EXT_L26_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L26_RD_MASK, SBB_PARAM_EXT_L26_WR_MASK, \
                                    "SBB_PARAM_EXT_L26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H27_OFFSET, \
                                    SBB_PARAM_EXT_H27_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H27_RD_MASK, SBB_PARAM_EXT_H27_WR_MASK, \
                                    "SBB_PARAM_EXT_H27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L27_OFFSET, \
                                    SBB_PARAM_EXT_L27_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L27_RD_MASK, SBB_PARAM_EXT_L27_WR_MASK, \
                                    "SBB_PARAM_EXT_L27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H28_OFFSET, \
                                    SBB_PARAM_EXT_H28_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H28_RD_MASK, SBB_PARAM_EXT_H28_WR_MASK, \
                                    "SBB_PARAM_EXT_H28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L28_OFFSET, \
                                    SBB_PARAM_EXT_L28_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L28_RD_MASK, SBB_PARAM_EXT_L28_WR_MASK, \
                                    "SBB_PARAM_EXT_L28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H29_OFFSET, \
                                    SBB_PARAM_EXT_H29_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H29_RD_MASK, SBB_PARAM_EXT_H29_WR_MASK, \
                                    "SBB_PARAM_EXT_H29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L29_OFFSET, \
                                    SBB_PARAM_EXT_L29_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L29_RD_MASK, SBB_PARAM_EXT_L29_WR_MASK, \
                                    "SBB_PARAM_EXT_L29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H30_OFFSET, \
                                    SBB_PARAM_EXT_H30_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H30_RD_MASK, SBB_PARAM_EXT_H30_WR_MASK, \
                                    "SBB_PARAM_EXT_H30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L30_OFFSET, \
                                    SBB_PARAM_EXT_L30_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L30_RD_MASK, SBB_PARAM_EXT_L30_WR_MASK, \
                                    "SBB_PARAM_EXT_L30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H31_OFFSET, \
                                    SBB_PARAM_EXT_H31_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H31_RD_MASK, SBB_PARAM_EXT_H31_WR_MASK, \
                                    "SBB_PARAM_EXT_H31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L31_OFFSET, \
                                    SBB_PARAM_EXT_L31_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L31_RD_MASK, SBB_PARAM_EXT_L31_WR_MASK, \
                                    "SBB_PARAM_EXT_L31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H32_OFFSET, \
                                    SBB_PARAM_EXT_H32_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H32_RD_MASK, SBB_PARAM_EXT_H32_WR_MASK, \
                                    "SBB_PARAM_EXT_H32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L32_OFFSET, \
                                    SBB_PARAM_EXT_L32_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L32_RD_MASK, SBB_PARAM_EXT_L32_WR_MASK, \
                                    "SBB_PARAM_EXT_L32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H33_OFFSET, \
                                    SBB_PARAM_EXT_H33_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H33_RD_MASK, SBB_PARAM_EXT_H33_WR_MASK, \
                                    "SBB_PARAM_EXT_H33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L33_OFFSET, \
                                    SBB_PARAM_EXT_L33_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L33_RD_MASK, SBB_PARAM_EXT_L33_WR_MASK, \
                                    "SBB_PARAM_EXT_L33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H34_OFFSET, \
                                    SBB_PARAM_EXT_H34_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H34_RD_MASK, SBB_PARAM_EXT_H34_WR_MASK, \
                                    "SBB_PARAM_EXT_H34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L34_OFFSET, \
                                    SBB_PARAM_EXT_L34_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L34_RD_MASK, SBB_PARAM_EXT_L34_WR_MASK, \
                                    "SBB_PARAM_EXT_L34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H35_OFFSET, \
                                    SBB_PARAM_EXT_H35_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H35_RD_MASK, SBB_PARAM_EXT_H35_WR_MASK, \
                                    "SBB_PARAM_EXT_H35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L35_OFFSET, \
                                    SBB_PARAM_EXT_L35_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L35_RD_MASK, SBB_PARAM_EXT_L35_WR_MASK, \
                                    "SBB_PARAM_EXT_L35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H36_OFFSET, \
                                    SBB_PARAM_EXT_H36_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H36_RD_MASK, SBB_PARAM_EXT_H36_WR_MASK, \
                                    "SBB_PARAM_EXT_H36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L36_OFFSET, \
                                    SBB_PARAM_EXT_L36_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L36_RD_MASK, SBB_PARAM_EXT_L36_WR_MASK, \
                                    "SBB_PARAM_EXT_L36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H37_OFFSET, \
                                    SBB_PARAM_EXT_H37_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H37_RD_MASK, SBB_PARAM_EXT_H37_WR_MASK, \
                                    "SBB_PARAM_EXT_H37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L37_OFFSET, \
                                    SBB_PARAM_EXT_L37_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L37_RD_MASK, SBB_PARAM_EXT_L37_WR_MASK, \
                                    "SBB_PARAM_EXT_L37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H38_OFFSET, \
                                    SBB_PARAM_EXT_H38_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H38_RD_MASK, SBB_PARAM_EXT_H38_WR_MASK, \
                                    "SBB_PARAM_EXT_H38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L38_OFFSET, \
                                    SBB_PARAM_EXT_L38_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L38_RD_MASK, SBB_PARAM_EXT_L38_WR_MASK, \
                                    "SBB_PARAM_EXT_L38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H39_OFFSET, \
                                    SBB_PARAM_EXT_H39_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H39_RD_MASK, SBB_PARAM_EXT_H39_WR_MASK, \
                                    "SBB_PARAM_EXT_H39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L39_OFFSET, \
                                    SBB_PARAM_EXT_L39_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L39_RD_MASK, SBB_PARAM_EXT_L39_WR_MASK, \
                                    "SBB_PARAM_EXT_L39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H40_OFFSET, \
                                    SBB_PARAM_EXT_H40_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H40_RD_MASK, SBB_PARAM_EXT_H40_WR_MASK, \
                                    "SBB_PARAM_EXT_H40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L40_OFFSET, \
                                    SBB_PARAM_EXT_L40_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L40_RD_MASK, SBB_PARAM_EXT_L40_WR_MASK, \
                                    "SBB_PARAM_EXT_L40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H41_OFFSET, \
                                    SBB_PARAM_EXT_H41_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H41_RD_MASK, SBB_PARAM_EXT_H41_WR_MASK, \
                                    "SBB_PARAM_EXT_H41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L41_OFFSET, \
                                    SBB_PARAM_EXT_L41_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L41_RD_MASK, SBB_PARAM_EXT_L41_WR_MASK, \
                                    "SBB_PARAM_EXT_L41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H42_OFFSET, \
                                    SBB_PARAM_EXT_H42_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H42_RD_MASK, SBB_PARAM_EXT_H42_WR_MASK, \
                                    "SBB_PARAM_EXT_H42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L42_OFFSET, \
                                    SBB_PARAM_EXT_L42_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L42_RD_MASK, SBB_PARAM_EXT_L42_WR_MASK, \
                                    "SBB_PARAM_EXT_L42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H43_OFFSET, \
                                    SBB_PARAM_EXT_H43_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H43_RD_MASK, SBB_PARAM_EXT_H43_WR_MASK, \
                                    "SBB_PARAM_EXT_H43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L43_OFFSET, \
                                    SBB_PARAM_EXT_L43_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L43_RD_MASK, SBB_PARAM_EXT_L43_WR_MASK, \
                                    "SBB_PARAM_EXT_L43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H44_OFFSET, \
                                    SBB_PARAM_EXT_H44_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H44_RD_MASK, SBB_PARAM_EXT_H44_WR_MASK, \
                                    "SBB_PARAM_EXT_H44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L44_OFFSET, \
                                    SBB_PARAM_EXT_L44_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L44_RD_MASK, SBB_PARAM_EXT_L44_WR_MASK, \
                                    "SBB_PARAM_EXT_L44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H45_OFFSET, \
                                    SBB_PARAM_EXT_H45_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H45_RD_MASK, SBB_PARAM_EXT_H45_WR_MASK, \
                                    "SBB_PARAM_EXT_H45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L45_OFFSET, \
                                    SBB_PARAM_EXT_L45_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L45_RD_MASK, SBB_PARAM_EXT_L45_WR_MASK, \
                                    "SBB_PARAM_EXT_L45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H46_OFFSET, \
                                    SBB_PARAM_EXT_H46_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H46_RD_MASK, SBB_PARAM_EXT_H46_WR_MASK, \
                                    "SBB_PARAM_EXT_H46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L46_OFFSET, \
                                    SBB_PARAM_EXT_L46_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L46_RD_MASK, SBB_PARAM_EXT_L46_WR_MASK, \
                                    "SBB_PARAM_EXT_L46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H47_OFFSET, \
                                    SBB_PARAM_EXT_H47_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H47_RD_MASK, SBB_PARAM_EXT_H47_WR_MASK, \
                                    "SBB_PARAM_EXT_H47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L47_OFFSET, \
                                    SBB_PARAM_EXT_L47_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L47_RD_MASK, SBB_PARAM_EXT_L47_WR_MASK, \
                                    "SBB_PARAM_EXT_L47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H48_OFFSET, \
                                    SBB_PARAM_EXT_H48_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H48_RD_MASK, SBB_PARAM_EXT_H48_WR_MASK, \
                                    "SBB_PARAM_EXT_H48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L48_OFFSET, \
                                    SBB_PARAM_EXT_L48_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L48_RD_MASK, SBB_PARAM_EXT_L48_WR_MASK, \
                                    "SBB_PARAM_EXT_L48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H49_OFFSET, \
                                    SBB_PARAM_EXT_H49_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H49_RD_MASK, SBB_PARAM_EXT_H49_WR_MASK, \
                                    "SBB_PARAM_EXT_H49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L49_OFFSET, \
                                    SBB_PARAM_EXT_L49_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L49_RD_MASK, SBB_PARAM_EXT_L49_WR_MASK, \
                                    "SBB_PARAM_EXT_L49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H50_OFFSET, \
                                    SBB_PARAM_EXT_H50_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H50_RD_MASK, SBB_PARAM_EXT_H50_WR_MASK, \
                                    "SBB_PARAM_EXT_H50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L50_OFFSET, \
                                    SBB_PARAM_EXT_L50_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L50_RD_MASK, SBB_PARAM_EXT_L50_WR_MASK, \
                                    "SBB_PARAM_EXT_L50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H51_OFFSET, \
                                    SBB_PARAM_EXT_H51_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H51_RD_MASK, SBB_PARAM_EXT_H51_WR_MASK, \
                                    "SBB_PARAM_EXT_H51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L51_OFFSET, \
                                    SBB_PARAM_EXT_L51_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L51_RD_MASK, SBB_PARAM_EXT_L51_WR_MASK, \
                                    "SBB_PARAM_EXT_L51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H52_OFFSET, \
                                    SBB_PARAM_EXT_H52_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H52_RD_MASK, SBB_PARAM_EXT_H52_WR_MASK, \
                                    "SBB_PARAM_EXT_H52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L52_OFFSET, \
                                    SBB_PARAM_EXT_L52_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L52_RD_MASK, SBB_PARAM_EXT_L52_WR_MASK, \
                                    "SBB_PARAM_EXT_L52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H53_OFFSET, \
                                    SBB_PARAM_EXT_H53_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H53_RD_MASK, SBB_PARAM_EXT_H53_WR_MASK, \
                                    "SBB_PARAM_EXT_H53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L53_OFFSET, \
                                    SBB_PARAM_EXT_L53_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L53_RD_MASK, SBB_PARAM_EXT_L53_WR_MASK, \
                                    "SBB_PARAM_EXT_L53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H54_OFFSET, \
                                    SBB_PARAM_EXT_H54_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H54_RD_MASK, SBB_PARAM_EXT_H54_WR_MASK, \
                                    "SBB_PARAM_EXT_H54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L54_OFFSET, \
                                    SBB_PARAM_EXT_L54_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L54_RD_MASK, SBB_PARAM_EXT_L54_WR_MASK, \
                                    "SBB_PARAM_EXT_L54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H55_OFFSET, \
                                    SBB_PARAM_EXT_H55_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H55_RD_MASK, SBB_PARAM_EXT_H55_WR_MASK, \
                                    "SBB_PARAM_EXT_H55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L55_OFFSET, \
                                    SBB_PARAM_EXT_L55_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L55_RD_MASK, SBB_PARAM_EXT_L55_WR_MASK, \
                                    "SBB_PARAM_EXT_L55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H56_OFFSET, \
                                    SBB_PARAM_EXT_H56_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H56_RD_MASK, SBB_PARAM_EXT_H56_WR_MASK, \
                                    "SBB_PARAM_EXT_H56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L56_OFFSET, \
                                    SBB_PARAM_EXT_L56_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L56_RD_MASK, SBB_PARAM_EXT_L56_WR_MASK, \
                                    "SBB_PARAM_EXT_L56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H57_OFFSET, \
                                    SBB_PARAM_EXT_H57_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H57_RD_MASK, SBB_PARAM_EXT_H57_WR_MASK, \
                                    "SBB_PARAM_EXT_H57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L57_OFFSET, \
                                    SBB_PARAM_EXT_L57_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L57_RD_MASK, SBB_PARAM_EXT_L57_WR_MASK, \
                                    "SBB_PARAM_EXT_L57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H58_OFFSET, \
                                    SBB_PARAM_EXT_H58_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H58_RD_MASK, SBB_PARAM_EXT_H58_WR_MASK, \
                                    "SBB_PARAM_EXT_H58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L58_OFFSET, \
                                    SBB_PARAM_EXT_L58_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L58_RD_MASK, SBB_PARAM_EXT_L58_WR_MASK, \
                                    "SBB_PARAM_EXT_L58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H59_OFFSET, \
                                    SBB_PARAM_EXT_H59_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H59_RD_MASK, SBB_PARAM_EXT_H59_WR_MASK, \
                                    "SBB_PARAM_EXT_H59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L59_OFFSET, \
                                    SBB_PARAM_EXT_L59_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L59_RD_MASK, SBB_PARAM_EXT_L59_WR_MASK, \
                                    "SBB_PARAM_EXT_L59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H60_OFFSET, \
                                    SBB_PARAM_EXT_H60_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H60_RD_MASK, SBB_PARAM_EXT_H60_WR_MASK, \
                                    "SBB_PARAM_EXT_H60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L60_OFFSET, \
                                    SBB_PARAM_EXT_L60_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L60_RD_MASK, SBB_PARAM_EXT_L60_WR_MASK, \
                                    "SBB_PARAM_EXT_L60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H61_OFFSET, \
                                    SBB_PARAM_EXT_H61_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H61_RD_MASK, SBB_PARAM_EXT_H61_WR_MASK, \
                                    "SBB_PARAM_EXT_H61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L61_OFFSET, \
                                    SBB_PARAM_EXT_L61_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L61_RD_MASK, SBB_PARAM_EXT_L61_WR_MASK, \
                                    "SBB_PARAM_EXT_L61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H62_OFFSET, \
                                    SBB_PARAM_EXT_H62_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H62_RD_MASK, SBB_PARAM_EXT_H62_WR_MASK, \
                                    "SBB_PARAM_EXT_H62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L62_OFFSET, \
                                    SBB_PARAM_EXT_L62_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L62_RD_MASK, SBB_PARAM_EXT_L62_WR_MASK, \
                                    "SBB_PARAM_EXT_L62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_H63_OFFSET, \
                                    SBB_PARAM_EXT_H63_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_H63_RD_MASK, SBB_PARAM_EXT_H63_WR_MASK, \
                                    "SBB_PARAM_EXT_H63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_EXT_L63_OFFSET, \
                                    SBB_PARAM_EXT_L63_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_EXT_L63_RD_MASK, SBB_PARAM_EXT_L63_WR_MASK, \
                                    "SBB_PARAM_EXT_L63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H0_OFFSET, \
                                    SBB_PARAM_H0_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H0_RD_MASK, SBB_PARAM_H0_WR_MASK, \
                                    "SBB_PARAM_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L0_OFFSET, \
                                    SBB_PARAM_L0_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L0_RD_MASK, SBB_PARAM_L0_WR_MASK, \
                                    "SBB_PARAM_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H1_OFFSET, \
                                    SBB_PARAM_H1_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H1_RD_MASK, SBB_PARAM_H1_WR_MASK, \
                                    "SBB_PARAM_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L1_OFFSET, \
                                    SBB_PARAM_L1_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L1_RD_MASK, SBB_PARAM_L1_WR_MASK, \
                                    "SBB_PARAM_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H2_OFFSET, \
                                    SBB_PARAM_H2_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H2_RD_MASK, SBB_PARAM_H2_WR_MASK, \
                                    "SBB_PARAM_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L2_OFFSET, \
                                    SBB_PARAM_L2_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L2_RD_MASK, SBB_PARAM_L2_WR_MASK, \
                                    "SBB_PARAM_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H3_OFFSET, \
                                    SBB_PARAM_H3_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H3_RD_MASK, SBB_PARAM_H3_WR_MASK, \
                                    "SBB_PARAM_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L3_OFFSET, \
                                    SBB_PARAM_L3_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L3_RD_MASK, SBB_PARAM_L3_WR_MASK, \
                                    "SBB_PARAM_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H4_OFFSET, \
                                    SBB_PARAM_H4_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H4_RD_MASK, SBB_PARAM_H4_WR_MASK, \
                                    "SBB_PARAM_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L4_OFFSET, \
                                    SBB_PARAM_L4_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L4_RD_MASK, SBB_PARAM_L4_WR_MASK, \
                                    "SBB_PARAM_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H5_OFFSET, \
                                    SBB_PARAM_H5_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H5_RD_MASK, SBB_PARAM_H5_WR_MASK, \
                                    "SBB_PARAM_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L5_OFFSET, \
                                    SBB_PARAM_L5_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L5_RD_MASK, SBB_PARAM_L5_WR_MASK, \
                                    "SBB_PARAM_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H6_OFFSET, \
                                    SBB_PARAM_H6_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H6_RD_MASK, SBB_PARAM_H6_WR_MASK, \
                                    "SBB_PARAM_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L6_OFFSET, \
                                    SBB_PARAM_L6_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L6_RD_MASK, SBB_PARAM_L6_WR_MASK, \
                                    "SBB_PARAM_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H7_OFFSET, \
                                    SBB_PARAM_H7_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H7_RD_MASK, SBB_PARAM_H7_WR_MASK, \
                                    "SBB_PARAM_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L7_OFFSET, \
                                    SBB_PARAM_L7_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L7_RD_MASK, SBB_PARAM_L7_WR_MASK, \
                                    "SBB_PARAM_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H8_OFFSET, \
                                    SBB_PARAM_H8_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H8_RD_MASK, SBB_PARAM_H8_WR_MASK, \
                                    "SBB_PARAM_H8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L8_OFFSET, \
                                    SBB_PARAM_L8_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L8_RD_MASK, SBB_PARAM_L8_WR_MASK, \
                                    "SBB_PARAM_L8_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H9_OFFSET, \
                                    SBB_PARAM_H9_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H9_RD_MASK, SBB_PARAM_H9_WR_MASK, \
                                    "SBB_PARAM_H9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L9_OFFSET, \
                                    SBB_PARAM_L9_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L9_RD_MASK, SBB_PARAM_L9_WR_MASK, \
                                    "SBB_PARAM_L9_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H10_OFFSET, \
                                    SBB_PARAM_H10_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H10_RD_MASK, SBB_PARAM_H10_WR_MASK, \
                                    "SBB_PARAM_H10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L10_OFFSET, \
                                    SBB_PARAM_L10_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L10_RD_MASK, SBB_PARAM_L10_WR_MASK, \
                                    "SBB_PARAM_L10_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H11_OFFSET, \
                                    SBB_PARAM_H11_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H11_RD_MASK, SBB_PARAM_H11_WR_MASK, \
                                    "SBB_PARAM_H11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L11_OFFSET, \
                                    SBB_PARAM_L11_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L11_RD_MASK, SBB_PARAM_L11_WR_MASK, \
                                    "SBB_PARAM_L11_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H12_OFFSET, \
                                    SBB_PARAM_H12_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H12_RD_MASK, SBB_PARAM_H12_WR_MASK, \
                                    "SBB_PARAM_H12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L12_OFFSET, \
                                    SBB_PARAM_L12_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L12_RD_MASK, SBB_PARAM_L12_WR_MASK, \
                                    "SBB_PARAM_L12_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H13_OFFSET, \
                                    SBB_PARAM_H13_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H13_RD_MASK, SBB_PARAM_H13_WR_MASK, \
                                    "SBB_PARAM_H13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L13_OFFSET, \
                                    SBB_PARAM_L13_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L13_RD_MASK, SBB_PARAM_L13_WR_MASK, \
                                    "SBB_PARAM_L13_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H14_OFFSET, \
                                    SBB_PARAM_H14_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H14_RD_MASK, SBB_PARAM_H14_WR_MASK, \
                                    "SBB_PARAM_H14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L14_OFFSET, \
                                    SBB_PARAM_L14_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L14_RD_MASK, SBB_PARAM_L14_WR_MASK, \
                                    "SBB_PARAM_L14_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H15_OFFSET, \
                                    SBB_PARAM_H15_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H15_RD_MASK, SBB_PARAM_H15_WR_MASK, \
                                    "SBB_PARAM_H15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L15_OFFSET, \
                                    SBB_PARAM_L15_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L15_RD_MASK, SBB_PARAM_L15_WR_MASK, \
                                    "SBB_PARAM_L15_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H16_OFFSET, \
                                    SBB_PARAM_H16_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H16_RD_MASK, SBB_PARAM_H16_WR_MASK, \
                                    "SBB_PARAM_H16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L16_OFFSET, \
                                    SBB_PARAM_L16_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L16_RD_MASK, SBB_PARAM_L16_WR_MASK, \
                                    "SBB_PARAM_L16_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H17_OFFSET, \
                                    SBB_PARAM_H17_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H17_RD_MASK, SBB_PARAM_H17_WR_MASK, \
                                    "SBB_PARAM_H17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L17_OFFSET, \
                                    SBB_PARAM_L17_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L17_RD_MASK, SBB_PARAM_L17_WR_MASK, \
                                    "SBB_PARAM_L17_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H18_OFFSET, \
                                    SBB_PARAM_H18_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H18_RD_MASK, SBB_PARAM_H18_WR_MASK, \
                                    "SBB_PARAM_H18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L18_OFFSET, \
                                    SBB_PARAM_L18_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L18_RD_MASK, SBB_PARAM_L18_WR_MASK, \
                                    "SBB_PARAM_L18_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H19_OFFSET, \
                                    SBB_PARAM_H19_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H19_RD_MASK, SBB_PARAM_H19_WR_MASK, \
                                    "SBB_PARAM_H19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L19_OFFSET, \
                                    SBB_PARAM_L19_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L19_RD_MASK, SBB_PARAM_L19_WR_MASK, \
                                    "SBB_PARAM_L19_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H20_OFFSET, \
                                    SBB_PARAM_H20_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H20_RD_MASK, SBB_PARAM_H20_WR_MASK, \
                                    "SBB_PARAM_H20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L20_OFFSET, \
                                    SBB_PARAM_L20_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L20_RD_MASK, SBB_PARAM_L20_WR_MASK, \
                                    "SBB_PARAM_L20_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H21_OFFSET, \
                                    SBB_PARAM_H21_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H21_RD_MASK, SBB_PARAM_H21_WR_MASK, \
                                    "SBB_PARAM_H21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L21_OFFSET, \
                                    SBB_PARAM_L21_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L21_RD_MASK, SBB_PARAM_L21_WR_MASK, \
                                    "SBB_PARAM_L21_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H22_OFFSET, \
                                    SBB_PARAM_H22_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H22_RD_MASK, SBB_PARAM_H22_WR_MASK, \
                                    "SBB_PARAM_H22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L22_OFFSET, \
                                    SBB_PARAM_L22_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L22_RD_MASK, SBB_PARAM_L22_WR_MASK, \
                                    "SBB_PARAM_L22_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H23_OFFSET, \
                                    SBB_PARAM_H23_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H23_RD_MASK, SBB_PARAM_H23_WR_MASK, \
                                    "SBB_PARAM_H23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L23_OFFSET, \
                                    SBB_PARAM_L23_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L23_RD_MASK, SBB_PARAM_L23_WR_MASK, \
                                    "SBB_PARAM_L23_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H24_OFFSET, \
                                    SBB_PARAM_H24_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H24_RD_MASK, SBB_PARAM_H24_WR_MASK, \
                                    "SBB_PARAM_H24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L24_OFFSET, \
                                    SBB_PARAM_L24_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L24_RD_MASK, SBB_PARAM_L24_WR_MASK, \
                                    "SBB_PARAM_L24_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H25_OFFSET, \
                                    SBB_PARAM_H25_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H25_RD_MASK, SBB_PARAM_H25_WR_MASK, \
                                    "SBB_PARAM_H25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L25_OFFSET, \
                                    SBB_PARAM_L25_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L25_RD_MASK, SBB_PARAM_L25_WR_MASK, \
                                    "SBB_PARAM_L25_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H26_OFFSET, \
                                    SBB_PARAM_H26_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H26_RD_MASK, SBB_PARAM_H26_WR_MASK, \
                                    "SBB_PARAM_H26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L26_OFFSET, \
                                    SBB_PARAM_L26_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L26_RD_MASK, SBB_PARAM_L26_WR_MASK, \
                                    "SBB_PARAM_L26_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H27_OFFSET, \
                                    SBB_PARAM_H27_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H27_RD_MASK, SBB_PARAM_H27_WR_MASK, \
                                    "SBB_PARAM_H27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L27_OFFSET, \
                                    SBB_PARAM_L27_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L27_RD_MASK, SBB_PARAM_L27_WR_MASK, \
                                    "SBB_PARAM_L27_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H28_OFFSET, \
                                    SBB_PARAM_H28_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H28_RD_MASK, SBB_PARAM_H28_WR_MASK, \
                                    "SBB_PARAM_H28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L28_OFFSET, \
                                    SBB_PARAM_L28_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L28_RD_MASK, SBB_PARAM_L28_WR_MASK, \
                                    "SBB_PARAM_L28_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H29_OFFSET, \
                                    SBB_PARAM_H29_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H29_RD_MASK, SBB_PARAM_H29_WR_MASK, \
                                    "SBB_PARAM_H29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L29_OFFSET, \
                                    SBB_PARAM_L29_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L29_RD_MASK, SBB_PARAM_L29_WR_MASK, \
                                    "SBB_PARAM_L29_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H30_OFFSET, \
                                    SBB_PARAM_H30_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H30_RD_MASK, SBB_PARAM_H30_WR_MASK, \
                                    "SBB_PARAM_H30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L30_OFFSET, \
                                    SBB_PARAM_L30_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L30_RD_MASK, SBB_PARAM_L30_WR_MASK, \
                                    "SBB_PARAM_L30_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H31_OFFSET, \
                                    SBB_PARAM_H31_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H31_RD_MASK, SBB_PARAM_H31_WR_MASK, \
                                    "SBB_PARAM_H31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L31_OFFSET, \
                                    SBB_PARAM_L31_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L31_RD_MASK, SBB_PARAM_L31_WR_MASK, \
                                    "SBB_PARAM_L31_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H32_OFFSET, \
                                    SBB_PARAM_H32_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H32_RD_MASK, SBB_PARAM_H32_WR_MASK, \
                                    "SBB_PARAM_H32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L32_OFFSET, \
                                    SBB_PARAM_L32_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L32_RD_MASK, SBB_PARAM_L32_WR_MASK, \
                                    "SBB_PARAM_L32_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H33_OFFSET, \
                                    SBB_PARAM_H33_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H33_RD_MASK, SBB_PARAM_H33_WR_MASK, \
                                    "SBB_PARAM_H33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L33_OFFSET, \
                                    SBB_PARAM_L33_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L33_RD_MASK, SBB_PARAM_L33_WR_MASK, \
                                    "SBB_PARAM_L33_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H34_OFFSET, \
                                    SBB_PARAM_H34_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H34_RD_MASK, SBB_PARAM_H34_WR_MASK, \
                                    "SBB_PARAM_H34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L34_OFFSET, \
                                    SBB_PARAM_L34_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L34_RD_MASK, SBB_PARAM_L34_WR_MASK, \
                                    "SBB_PARAM_L34_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H35_OFFSET, \
                                    SBB_PARAM_H35_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H35_RD_MASK, SBB_PARAM_H35_WR_MASK, \
                                    "SBB_PARAM_H35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L35_OFFSET, \
                                    SBB_PARAM_L35_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L35_RD_MASK, SBB_PARAM_L35_WR_MASK, \
                                    "SBB_PARAM_L35_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H36_OFFSET, \
                                    SBB_PARAM_H36_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H36_RD_MASK, SBB_PARAM_H36_WR_MASK, \
                                    "SBB_PARAM_H36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L36_OFFSET, \
                                    SBB_PARAM_L36_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L36_RD_MASK, SBB_PARAM_L36_WR_MASK, \
                                    "SBB_PARAM_L36_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H37_OFFSET, \
                                    SBB_PARAM_H37_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H37_RD_MASK, SBB_PARAM_H37_WR_MASK, \
                                    "SBB_PARAM_H37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L37_OFFSET, \
                                    SBB_PARAM_L37_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L37_RD_MASK, SBB_PARAM_L37_WR_MASK, \
                                    "SBB_PARAM_L37_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H38_OFFSET, \
                                    SBB_PARAM_H38_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H38_RD_MASK, SBB_PARAM_H38_WR_MASK, \
                                    "SBB_PARAM_H38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L38_OFFSET, \
                                    SBB_PARAM_L38_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L38_RD_MASK, SBB_PARAM_L38_WR_MASK, \
                                    "SBB_PARAM_L38_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H39_OFFSET, \
                                    SBB_PARAM_H39_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H39_RD_MASK, SBB_PARAM_H39_WR_MASK, \
                                    "SBB_PARAM_H39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L39_OFFSET, \
                                    SBB_PARAM_L39_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L39_RD_MASK, SBB_PARAM_L39_WR_MASK, \
                                    "SBB_PARAM_L39_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H40_OFFSET, \
                                    SBB_PARAM_H40_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H40_RD_MASK, SBB_PARAM_H40_WR_MASK, \
                                    "SBB_PARAM_H40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L40_OFFSET, \
                                    SBB_PARAM_L40_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L40_RD_MASK, SBB_PARAM_L40_WR_MASK, \
                                    "SBB_PARAM_L40_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H41_OFFSET, \
                                    SBB_PARAM_H41_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H41_RD_MASK, SBB_PARAM_H41_WR_MASK, \
                                    "SBB_PARAM_H41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L41_OFFSET, \
                                    SBB_PARAM_L41_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L41_RD_MASK, SBB_PARAM_L41_WR_MASK, \
                                    "SBB_PARAM_L41_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H42_OFFSET, \
                                    SBB_PARAM_H42_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H42_RD_MASK, SBB_PARAM_H42_WR_MASK, \
                                    "SBB_PARAM_H42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L42_OFFSET, \
                                    SBB_PARAM_L42_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L42_RD_MASK, SBB_PARAM_L42_WR_MASK, \
                                    "SBB_PARAM_L42_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H43_OFFSET, \
                                    SBB_PARAM_H43_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H43_RD_MASK, SBB_PARAM_H43_WR_MASK, \
                                    "SBB_PARAM_H43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L43_OFFSET, \
                                    SBB_PARAM_L43_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L43_RD_MASK, SBB_PARAM_L43_WR_MASK, \
                                    "SBB_PARAM_L43_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H44_OFFSET, \
                                    SBB_PARAM_H44_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H44_RD_MASK, SBB_PARAM_H44_WR_MASK, \
                                    "SBB_PARAM_H44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L44_OFFSET, \
                                    SBB_PARAM_L44_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L44_RD_MASK, SBB_PARAM_L44_WR_MASK, \
                                    "SBB_PARAM_L44_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H45_OFFSET, \
                                    SBB_PARAM_H45_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H45_RD_MASK, SBB_PARAM_H45_WR_MASK, \
                                    "SBB_PARAM_H45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L45_OFFSET, \
                                    SBB_PARAM_L45_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L45_RD_MASK, SBB_PARAM_L45_WR_MASK, \
                                    "SBB_PARAM_L45_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H46_OFFSET, \
                                    SBB_PARAM_H46_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H46_RD_MASK, SBB_PARAM_H46_WR_MASK, \
                                    "SBB_PARAM_H46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L46_OFFSET, \
                                    SBB_PARAM_L46_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L46_RD_MASK, SBB_PARAM_L46_WR_MASK, \
                                    "SBB_PARAM_L46_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H47_OFFSET, \
                                    SBB_PARAM_H47_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H47_RD_MASK, SBB_PARAM_H47_WR_MASK, \
                                    "SBB_PARAM_H47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L47_OFFSET, \
                                    SBB_PARAM_L47_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L47_RD_MASK, SBB_PARAM_L47_WR_MASK, \
                                    "SBB_PARAM_L47_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H48_OFFSET, \
                                    SBB_PARAM_H48_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H48_RD_MASK, SBB_PARAM_H48_WR_MASK, \
                                    "SBB_PARAM_H48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L48_OFFSET, \
                                    SBB_PARAM_L48_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L48_RD_MASK, SBB_PARAM_L48_WR_MASK, \
                                    "SBB_PARAM_L48_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H49_OFFSET, \
                                    SBB_PARAM_H49_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H49_RD_MASK, SBB_PARAM_H49_WR_MASK, \
                                    "SBB_PARAM_H49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L49_OFFSET, \
                                    SBB_PARAM_L49_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L49_RD_MASK, SBB_PARAM_L49_WR_MASK, \
                                    "SBB_PARAM_L49_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H50_OFFSET, \
                                    SBB_PARAM_H50_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H50_RD_MASK, SBB_PARAM_H50_WR_MASK, \
                                    "SBB_PARAM_H50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L50_OFFSET, \
                                    SBB_PARAM_L50_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L50_RD_MASK, SBB_PARAM_L50_WR_MASK, \
                                    "SBB_PARAM_L50_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H51_OFFSET, \
                                    SBB_PARAM_H51_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H51_RD_MASK, SBB_PARAM_H51_WR_MASK, \
                                    "SBB_PARAM_H51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L51_OFFSET, \
                                    SBB_PARAM_L51_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L51_RD_MASK, SBB_PARAM_L51_WR_MASK, \
                                    "SBB_PARAM_L51_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H52_OFFSET, \
                                    SBB_PARAM_H52_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H52_RD_MASK, SBB_PARAM_H52_WR_MASK, \
                                    "SBB_PARAM_H52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L52_OFFSET, \
                                    SBB_PARAM_L52_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L52_RD_MASK, SBB_PARAM_L52_WR_MASK, \
                                    "SBB_PARAM_L52_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H53_OFFSET, \
                                    SBB_PARAM_H53_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H53_RD_MASK, SBB_PARAM_H53_WR_MASK, \
                                    "SBB_PARAM_H53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L53_OFFSET, \
                                    SBB_PARAM_L53_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L53_RD_MASK, SBB_PARAM_L53_WR_MASK, \
                                    "SBB_PARAM_L53_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H54_OFFSET, \
                                    SBB_PARAM_H54_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H54_RD_MASK, SBB_PARAM_H54_WR_MASK, \
                                    "SBB_PARAM_H54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L54_OFFSET, \
                                    SBB_PARAM_L54_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L54_RD_MASK, SBB_PARAM_L54_WR_MASK, \
                                    "SBB_PARAM_L54_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H55_OFFSET, \
                                    SBB_PARAM_H55_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H55_RD_MASK, SBB_PARAM_H55_WR_MASK, \
                                    "SBB_PARAM_H55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L55_OFFSET, \
                                    SBB_PARAM_L55_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L55_RD_MASK, SBB_PARAM_L55_WR_MASK, \
                                    "SBB_PARAM_L55_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H56_OFFSET, \
                                    SBB_PARAM_H56_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H56_RD_MASK, SBB_PARAM_H56_WR_MASK, \
                                    "SBB_PARAM_H56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L56_OFFSET, \
                                    SBB_PARAM_L56_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L56_RD_MASK, SBB_PARAM_L56_WR_MASK, \
                                    "SBB_PARAM_L56_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H57_OFFSET, \
                                    SBB_PARAM_H57_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H57_RD_MASK, SBB_PARAM_H57_WR_MASK, \
                                    "SBB_PARAM_H57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L57_OFFSET, \
                                    SBB_PARAM_L57_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L57_RD_MASK, SBB_PARAM_L57_WR_MASK, \
                                    "SBB_PARAM_L57_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H58_OFFSET, \
                                    SBB_PARAM_H58_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H58_RD_MASK, SBB_PARAM_H58_WR_MASK, \
                                    "SBB_PARAM_H58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L58_OFFSET, \
                                    SBB_PARAM_L58_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L58_RD_MASK, SBB_PARAM_L58_WR_MASK, \
                                    "SBB_PARAM_L58_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H59_OFFSET, \
                                    SBB_PARAM_H59_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H59_RD_MASK, SBB_PARAM_H59_WR_MASK, \
                                    "SBB_PARAM_H59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L59_OFFSET, \
                                    SBB_PARAM_L59_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L59_RD_MASK, SBB_PARAM_L59_WR_MASK, \
                                    "SBB_PARAM_L59_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H60_OFFSET, \
                                    SBB_PARAM_H60_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H60_RD_MASK, SBB_PARAM_H60_WR_MASK, \
                                    "SBB_PARAM_H60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L60_OFFSET, \
                                    SBB_PARAM_L60_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L60_RD_MASK, SBB_PARAM_L60_WR_MASK, \
                                    "SBB_PARAM_L60_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H61_OFFSET, \
                                    SBB_PARAM_H61_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H61_RD_MASK, SBB_PARAM_H61_WR_MASK, \
                                    "SBB_PARAM_H61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L61_OFFSET, \
                                    SBB_PARAM_L61_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L61_RD_MASK, SBB_PARAM_L61_WR_MASK, \
                                    "SBB_PARAM_L61_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H62_OFFSET, \
                                    SBB_PARAM_H62_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H62_RD_MASK, SBB_PARAM_H62_WR_MASK, \
                                    "SBB_PARAM_H62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L62_OFFSET, \
                                    SBB_PARAM_L62_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L62_RD_MASK, SBB_PARAM_L62_WR_MASK, \
                                    "SBB_PARAM_L62_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H63_OFFSET, \
                                    SBB_PARAM_H63_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H63_RD_MASK, SBB_PARAM_H63_WR_MASK, \
                                    "SBB_PARAM_H63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L63_OFFSET, \
                                    SBB_PARAM_L63_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L63_RD_MASK, SBB_PARAM_L63_WR_MASK, \
                                    "SBB_PARAM_L63_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H64_OFFSET, \
                                    SBB_PARAM_H64_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H64_RD_MASK, SBB_PARAM_H64_WR_MASK, \
                                    "SBB_PARAM_H64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L64_OFFSET, \
                                    SBB_PARAM_L64_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L64_RD_MASK, SBB_PARAM_L64_WR_MASK, \
                                    "SBB_PARAM_L64_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H65_OFFSET, \
                                    SBB_PARAM_H65_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H65_RD_MASK, SBB_PARAM_H65_WR_MASK, \
                                    "SBB_PARAM_H65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L65_OFFSET, \
                                    SBB_PARAM_L65_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L65_RD_MASK, SBB_PARAM_L65_WR_MASK, \
                                    "SBB_PARAM_L65_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H66_OFFSET, \
                                    SBB_PARAM_H66_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H66_RD_MASK, SBB_PARAM_H66_WR_MASK, \
                                    "SBB_PARAM_H66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L66_OFFSET, \
                                    SBB_PARAM_L66_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L66_RD_MASK, SBB_PARAM_L66_WR_MASK, \
                                    "SBB_PARAM_L66_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H67_OFFSET, \
                                    SBB_PARAM_H67_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H67_RD_MASK, SBB_PARAM_H67_WR_MASK, \
                                    "SBB_PARAM_H67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L67_OFFSET, \
                                    SBB_PARAM_L67_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L67_RD_MASK, SBB_PARAM_L67_WR_MASK, \
                                    "SBB_PARAM_L67_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H68_OFFSET, \
                                    SBB_PARAM_H68_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H68_RD_MASK, SBB_PARAM_H68_WR_MASK, \
                                    "SBB_PARAM_H68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L68_OFFSET, \
                                    SBB_PARAM_L68_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L68_RD_MASK, SBB_PARAM_L68_WR_MASK, \
                                    "SBB_PARAM_L68_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H69_OFFSET, \
                                    SBB_PARAM_H69_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H69_RD_MASK, SBB_PARAM_H69_WR_MASK, \
                                    "SBB_PARAM_H69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L69_OFFSET, \
                                    SBB_PARAM_L69_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L69_RD_MASK, SBB_PARAM_L69_WR_MASK, \
                                    "SBB_PARAM_L69_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H70_OFFSET, \
                                    SBB_PARAM_H70_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H70_RD_MASK, SBB_PARAM_H70_WR_MASK, \
                                    "SBB_PARAM_H70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L70_OFFSET, \
                                    SBB_PARAM_L70_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L70_RD_MASK, SBB_PARAM_L70_WR_MASK, \
                                    "SBB_PARAM_L70_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H71_OFFSET, \
                                    SBB_PARAM_H71_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H71_RD_MASK, SBB_PARAM_H71_WR_MASK, \
                                    "SBB_PARAM_H71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L71_OFFSET, \
                                    SBB_PARAM_L71_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L71_RD_MASK, SBB_PARAM_L71_WR_MASK, \
                                    "SBB_PARAM_L71_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H72_OFFSET, \
                                    SBB_PARAM_H72_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H72_RD_MASK, SBB_PARAM_H72_WR_MASK, \
                                    "SBB_PARAM_H72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L72_OFFSET, \
                                    SBB_PARAM_L72_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L72_RD_MASK, SBB_PARAM_L72_WR_MASK, \
                                    "SBB_PARAM_L72_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H73_OFFSET, \
                                    SBB_PARAM_H73_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H73_RD_MASK, SBB_PARAM_H73_WR_MASK, \
                                    "SBB_PARAM_H73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L73_OFFSET, \
                                    SBB_PARAM_L73_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L73_RD_MASK, SBB_PARAM_L73_WR_MASK, \
                                    "SBB_PARAM_L73_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H74_OFFSET, \
                                    SBB_PARAM_H74_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H74_RD_MASK, SBB_PARAM_H74_WR_MASK, \
                                    "SBB_PARAM_H74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L74_OFFSET, \
                                    SBB_PARAM_L74_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L74_RD_MASK, SBB_PARAM_L74_WR_MASK, \
                                    "SBB_PARAM_L74_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H75_OFFSET, \
                                    SBB_PARAM_H75_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H75_RD_MASK, SBB_PARAM_H75_WR_MASK, \
                                    "SBB_PARAM_H75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L75_OFFSET, \
                                    SBB_PARAM_L75_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L75_RD_MASK, SBB_PARAM_L75_WR_MASK, \
                                    "SBB_PARAM_L75_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H76_OFFSET, \
                                    SBB_PARAM_H76_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H76_RD_MASK, SBB_PARAM_H76_WR_MASK, \
                                    "SBB_PARAM_H76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L76_OFFSET, \
                                    SBB_PARAM_L76_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L76_RD_MASK, SBB_PARAM_L76_WR_MASK, \
                                    "SBB_PARAM_L76_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H77_OFFSET, \
                                    SBB_PARAM_H77_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H77_RD_MASK, SBB_PARAM_H77_WR_MASK, \
                                    "SBB_PARAM_H77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L77_OFFSET, \
                                    SBB_PARAM_L77_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L77_RD_MASK, SBB_PARAM_L77_WR_MASK, \
                                    "SBB_PARAM_L77_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H78_OFFSET, \
                                    SBB_PARAM_H78_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H78_RD_MASK, SBB_PARAM_H78_WR_MASK, \
                                    "SBB_PARAM_H78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L78_OFFSET, \
                                    SBB_PARAM_L78_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L78_RD_MASK, SBB_PARAM_L78_WR_MASK, \
                                    "SBB_PARAM_L78_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H79_OFFSET, \
                                    SBB_PARAM_H79_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H79_RD_MASK, SBB_PARAM_H79_WR_MASK, \
                                    "SBB_PARAM_H79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L79_OFFSET, \
                                    SBB_PARAM_L79_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L79_RD_MASK, SBB_PARAM_L79_WR_MASK, \
                                    "SBB_PARAM_L79_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H80_OFFSET, \
                                    SBB_PARAM_H80_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H80_RD_MASK, SBB_PARAM_H80_WR_MASK, \
                                    "SBB_PARAM_H80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L80_OFFSET, \
                                    SBB_PARAM_L80_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L80_RD_MASK, SBB_PARAM_L80_WR_MASK, \
                                    "SBB_PARAM_L80_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H81_OFFSET, \
                                    SBB_PARAM_H81_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H81_RD_MASK, SBB_PARAM_H81_WR_MASK, \
                                    "SBB_PARAM_H81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L81_OFFSET, \
                                    SBB_PARAM_L81_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L81_RD_MASK, SBB_PARAM_L81_WR_MASK, \
                                    "SBB_PARAM_L81_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H82_OFFSET, \
                                    SBB_PARAM_H82_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H82_RD_MASK, SBB_PARAM_H82_WR_MASK, \
                                    "SBB_PARAM_H82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L82_OFFSET, \
                                    SBB_PARAM_L82_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L82_RD_MASK, SBB_PARAM_L82_WR_MASK, \
                                    "SBB_PARAM_L82_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H83_OFFSET, \
                                    SBB_PARAM_H83_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H83_RD_MASK, SBB_PARAM_H83_WR_MASK, \
                                    "SBB_PARAM_H83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L83_OFFSET, \
                                    SBB_PARAM_L83_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L83_RD_MASK, SBB_PARAM_L83_WR_MASK, \
                                    "SBB_PARAM_L83_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H84_OFFSET, \
                                    SBB_PARAM_H84_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H84_RD_MASK, SBB_PARAM_H84_WR_MASK, \
                                    "SBB_PARAM_H84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L84_OFFSET, \
                                    SBB_PARAM_L84_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L84_RD_MASK, SBB_PARAM_L84_WR_MASK, \
                                    "SBB_PARAM_L84_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H85_OFFSET, \
                                    SBB_PARAM_H85_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H85_RD_MASK, SBB_PARAM_H85_WR_MASK, \
                                    "SBB_PARAM_H85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L85_OFFSET, \
                                    SBB_PARAM_L85_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L85_RD_MASK, SBB_PARAM_L85_WR_MASK, \
                                    "SBB_PARAM_L85_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H86_OFFSET, \
                                    SBB_PARAM_H86_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H86_RD_MASK, SBB_PARAM_H86_WR_MASK, \
                                    "SBB_PARAM_H86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L86_OFFSET, \
                                    SBB_PARAM_L86_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L86_RD_MASK, SBB_PARAM_L86_WR_MASK, \
                                    "SBB_PARAM_L86_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H87_OFFSET, \
                                    SBB_PARAM_H87_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H87_RD_MASK, SBB_PARAM_H87_WR_MASK, \
                                    "SBB_PARAM_H87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L87_OFFSET, \
                                    SBB_PARAM_L87_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L87_RD_MASK, SBB_PARAM_L87_WR_MASK, \
                                    "SBB_PARAM_L87_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H88_OFFSET, \
                                    SBB_PARAM_H88_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H88_RD_MASK, SBB_PARAM_H88_WR_MASK, \
                                    "SBB_PARAM_H88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L88_OFFSET, \
                                    SBB_PARAM_L88_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L88_RD_MASK, SBB_PARAM_L88_WR_MASK, \
                                    "SBB_PARAM_L88_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H89_OFFSET, \
                                    SBB_PARAM_H89_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H89_RD_MASK, SBB_PARAM_H89_WR_MASK, \
                                    "SBB_PARAM_H89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L89_OFFSET, \
                                    SBB_PARAM_L89_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L89_RD_MASK, SBB_PARAM_L89_WR_MASK, \
                                    "SBB_PARAM_L89_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H90_OFFSET, \
                                    SBB_PARAM_H90_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H90_RD_MASK, SBB_PARAM_H90_WR_MASK, \
                                    "SBB_PARAM_H90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L90_OFFSET, \
                                    SBB_PARAM_L90_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L90_RD_MASK, SBB_PARAM_L90_WR_MASK, \
                                    "SBB_PARAM_L90_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H91_OFFSET, \
                                    SBB_PARAM_H91_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H91_RD_MASK, SBB_PARAM_H91_WR_MASK, \
                                    "SBB_PARAM_H91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L91_OFFSET, \
                                    SBB_PARAM_L91_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L91_RD_MASK, SBB_PARAM_L91_WR_MASK, \
                                    "SBB_PARAM_L91_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H92_OFFSET, \
                                    SBB_PARAM_H92_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H92_RD_MASK, SBB_PARAM_H92_WR_MASK, \
                                    "SBB_PARAM_H92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L92_OFFSET, \
                                    SBB_PARAM_L92_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L92_RD_MASK, SBB_PARAM_L92_WR_MASK, \
                                    "SBB_PARAM_L92_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H93_OFFSET, \
                                    SBB_PARAM_H93_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H93_RD_MASK, SBB_PARAM_H93_WR_MASK, \
                                    "SBB_PARAM_H93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L93_OFFSET, \
                                    SBB_PARAM_L93_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L93_RD_MASK, SBB_PARAM_L93_WR_MASK, \
                                    "SBB_PARAM_L93_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H94_OFFSET, \
                                    SBB_PARAM_H94_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H94_RD_MASK, SBB_PARAM_H94_WR_MASK, \
                                    "SBB_PARAM_H94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L94_OFFSET, \
                                    SBB_PARAM_L94_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L94_RD_MASK, SBB_PARAM_L94_WR_MASK, \
                                    "SBB_PARAM_L94_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H95_OFFSET, \
                                    SBB_PARAM_H95_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H95_RD_MASK, SBB_PARAM_H95_WR_MASK, \
                                    "SBB_PARAM_H95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L95_OFFSET, \
                                    SBB_PARAM_L95_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L95_RD_MASK, SBB_PARAM_L95_WR_MASK, \
                                    "SBB_PARAM_L95_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H96_OFFSET, \
                                    SBB_PARAM_H96_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H96_RD_MASK, SBB_PARAM_H96_WR_MASK, \
                                    "SBB_PARAM_H96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L96_OFFSET, \
                                    SBB_PARAM_L96_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L96_RD_MASK, SBB_PARAM_L96_WR_MASK, \
                                    "SBB_PARAM_L96_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H97_OFFSET, \
                                    SBB_PARAM_H97_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H97_RD_MASK, SBB_PARAM_H97_WR_MASK, \
                                    "SBB_PARAM_H97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L97_OFFSET, \
                                    SBB_PARAM_L97_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L97_RD_MASK, SBB_PARAM_L97_WR_MASK, \
                                    "SBB_PARAM_L97_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H98_OFFSET, \
                                    SBB_PARAM_H98_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H98_RD_MASK, SBB_PARAM_H98_WR_MASK, \
                                    "SBB_PARAM_H98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L98_OFFSET, \
                                    SBB_PARAM_L98_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L98_RD_MASK, SBB_PARAM_L98_WR_MASK, \
                                    "SBB_PARAM_L98_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H99_OFFSET, \
                                    SBB_PARAM_H99_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H99_RD_MASK, SBB_PARAM_H99_WR_MASK, \
                                    "SBB_PARAM_H99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L99_OFFSET, \
                                    SBB_PARAM_L99_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L99_RD_MASK, SBB_PARAM_L99_WR_MASK, \
                                    "SBB_PARAM_L99_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H100_OFFSET, \
                                    SBB_PARAM_H100_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H100_RD_MASK, SBB_PARAM_H100_WR_MASK, \
                                    "SBB_PARAM_H100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L100_OFFSET, \
                                    SBB_PARAM_L100_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L100_RD_MASK, SBB_PARAM_L100_WR_MASK, \
                                    "SBB_PARAM_L100_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H101_OFFSET, \
                                    SBB_PARAM_H101_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H101_RD_MASK, SBB_PARAM_H101_WR_MASK, \
                                    "SBB_PARAM_H101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L101_OFFSET, \
                                    SBB_PARAM_L101_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L101_RD_MASK, SBB_PARAM_L101_WR_MASK, \
                                    "SBB_PARAM_L101_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H102_OFFSET, \
                                    SBB_PARAM_H102_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H102_RD_MASK, SBB_PARAM_H102_WR_MASK, \
                                    "SBB_PARAM_H102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L102_OFFSET, \
                                    SBB_PARAM_L102_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L102_RD_MASK, SBB_PARAM_L102_WR_MASK, \
                                    "SBB_PARAM_L102_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H103_OFFSET, \
                                    SBB_PARAM_H103_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H103_RD_MASK, SBB_PARAM_H103_WR_MASK, \
                                    "SBB_PARAM_H103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L103_OFFSET, \
                                    SBB_PARAM_L103_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L103_RD_MASK, SBB_PARAM_L103_WR_MASK, \
                                    "SBB_PARAM_L103_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H104_OFFSET, \
                                    SBB_PARAM_H104_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H104_RD_MASK, SBB_PARAM_H104_WR_MASK, \
                                    "SBB_PARAM_H104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L104_OFFSET, \
                                    SBB_PARAM_L104_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L104_RD_MASK, SBB_PARAM_L104_WR_MASK, \
                                    "SBB_PARAM_L104_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H105_OFFSET, \
                                    SBB_PARAM_H105_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H105_RD_MASK, SBB_PARAM_H105_WR_MASK, \
                                    "SBB_PARAM_H105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L105_OFFSET, \
                                    SBB_PARAM_L105_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L105_RD_MASK, SBB_PARAM_L105_WR_MASK, \
                                    "SBB_PARAM_L105_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H106_OFFSET, \
                                    SBB_PARAM_H106_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H106_RD_MASK, SBB_PARAM_H106_WR_MASK, \
                                    "SBB_PARAM_H106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L106_OFFSET, \
                                    SBB_PARAM_L106_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L106_RD_MASK, SBB_PARAM_L106_WR_MASK, \
                                    "SBB_PARAM_L106_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H107_OFFSET, \
                                    SBB_PARAM_H107_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H107_RD_MASK, SBB_PARAM_H107_WR_MASK, \
                                    "SBB_PARAM_H107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L107_OFFSET, \
                                    SBB_PARAM_L107_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L107_RD_MASK, SBB_PARAM_L107_WR_MASK, \
                                    "SBB_PARAM_L107_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H108_OFFSET, \
                                    SBB_PARAM_H108_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H108_RD_MASK, SBB_PARAM_H108_WR_MASK, \
                                    "SBB_PARAM_H108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L108_OFFSET, \
                                    SBB_PARAM_L108_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L108_RD_MASK, SBB_PARAM_L108_WR_MASK, \
                                    "SBB_PARAM_L108_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H109_OFFSET, \
                                    SBB_PARAM_H109_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H109_RD_MASK, SBB_PARAM_H109_WR_MASK, \
                                    "SBB_PARAM_H109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L109_OFFSET, \
                                    SBB_PARAM_L109_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L109_RD_MASK, SBB_PARAM_L109_WR_MASK, \
                                    "SBB_PARAM_L109_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H110_OFFSET, \
                                    SBB_PARAM_H110_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H110_RD_MASK, SBB_PARAM_H110_WR_MASK, \
                                    "SBB_PARAM_H110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L110_OFFSET, \
                                    SBB_PARAM_L110_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L110_RD_MASK, SBB_PARAM_L110_WR_MASK, \
                                    "SBB_PARAM_L110_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H111_OFFSET, \
                                    SBB_PARAM_H111_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H111_RD_MASK, SBB_PARAM_H111_WR_MASK, \
                                    "SBB_PARAM_H111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L111_OFFSET, \
                                    SBB_PARAM_L111_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L111_RD_MASK, SBB_PARAM_L111_WR_MASK, \
                                    "SBB_PARAM_L111_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H112_OFFSET, \
                                    SBB_PARAM_H112_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H112_RD_MASK, SBB_PARAM_H112_WR_MASK, \
                                    "SBB_PARAM_H112_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L112_OFFSET, \
                                    SBB_PARAM_L112_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L112_RD_MASK, SBB_PARAM_L112_WR_MASK, \
                                    "SBB_PARAM_L112_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H113_OFFSET, \
                                    SBB_PARAM_H113_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H113_RD_MASK, SBB_PARAM_H113_WR_MASK, \
                                    "SBB_PARAM_H113_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L113_OFFSET, \
                                    SBB_PARAM_L113_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L113_RD_MASK, SBB_PARAM_L113_WR_MASK, \
                                    "SBB_PARAM_L113_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H114_OFFSET, \
                                    SBB_PARAM_H114_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H114_RD_MASK, SBB_PARAM_H114_WR_MASK, \
                                    "SBB_PARAM_H114_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L114_OFFSET, \
                                    SBB_PARAM_L114_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L114_RD_MASK, SBB_PARAM_L114_WR_MASK, \
                                    "SBB_PARAM_L114_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H115_OFFSET, \
                                    SBB_PARAM_H115_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H115_RD_MASK, SBB_PARAM_H115_WR_MASK, \
                                    "SBB_PARAM_H115_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L115_OFFSET, \
                                    SBB_PARAM_L115_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L115_RD_MASK, SBB_PARAM_L115_WR_MASK, \
                                    "SBB_PARAM_L115_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H116_OFFSET, \
                                    SBB_PARAM_H116_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H116_RD_MASK, SBB_PARAM_H116_WR_MASK, \
                                    "SBB_PARAM_H116_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L116_OFFSET, \
                                    SBB_PARAM_L116_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L116_RD_MASK, SBB_PARAM_L116_WR_MASK, \
                                    "SBB_PARAM_L116_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H117_OFFSET, \
                                    SBB_PARAM_H117_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H117_RD_MASK, SBB_PARAM_H117_WR_MASK, \
                                    "SBB_PARAM_H117_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L117_OFFSET, \
                                    SBB_PARAM_L117_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L117_RD_MASK, SBB_PARAM_L117_WR_MASK, \
                                    "SBB_PARAM_L117_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H118_OFFSET, \
                                    SBB_PARAM_H118_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H118_RD_MASK, SBB_PARAM_H118_WR_MASK, \
                                    "SBB_PARAM_H118_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L118_OFFSET, \
                                    SBB_PARAM_L118_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L118_RD_MASK, SBB_PARAM_L118_WR_MASK, \
                                    "SBB_PARAM_L118_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H119_OFFSET, \
                                    SBB_PARAM_H119_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H119_RD_MASK, SBB_PARAM_H119_WR_MASK, \
                                    "SBB_PARAM_H119_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L119_OFFSET, \
                                    SBB_PARAM_L119_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L119_RD_MASK, SBB_PARAM_L119_WR_MASK, \
                                    "SBB_PARAM_L119_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H120_OFFSET, \
                                    SBB_PARAM_H120_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H120_RD_MASK, SBB_PARAM_H120_WR_MASK, \
                                    "SBB_PARAM_H120_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L120_OFFSET, \
                                    SBB_PARAM_L120_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L120_RD_MASK, SBB_PARAM_L120_WR_MASK, \
                                    "SBB_PARAM_L120_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H121_OFFSET, \
                                    SBB_PARAM_H121_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H121_RD_MASK, SBB_PARAM_H121_WR_MASK, \
                                    "SBB_PARAM_H121_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L121_OFFSET, \
                                    SBB_PARAM_L121_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L121_RD_MASK, SBB_PARAM_L121_WR_MASK, \
                                    "SBB_PARAM_L121_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H122_OFFSET, \
                                    SBB_PARAM_H122_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H122_RD_MASK, SBB_PARAM_H122_WR_MASK, \
                                    "SBB_PARAM_H122_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L122_OFFSET, \
                                    SBB_PARAM_L122_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L122_RD_MASK, SBB_PARAM_L122_WR_MASK, \
                                    "SBB_PARAM_L122_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H123_OFFSET, \
                                    SBB_PARAM_H123_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H123_RD_MASK, SBB_PARAM_H123_WR_MASK, \
                                    "SBB_PARAM_H123_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L123_OFFSET, \
                                    SBB_PARAM_L123_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L123_RD_MASK, SBB_PARAM_L123_WR_MASK, \
                                    "SBB_PARAM_L123_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H124_OFFSET, \
                                    SBB_PARAM_H124_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H124_RD_MASK, SBB_PARAM_H124_WR_MASK, \
                                    "SBB_PARAM_H124_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L124_OFFSET, \
                                    SBB_PARAM_L124_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L124_RD_MASK, SBB_PARAM_L124_WR_MASK, \
                                    "SBB_PARAM_L124_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H125_OFFSET, \
                                    SBB_PARAM_H125_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H125_RD_MASK, SBB_PARAM_H125_WR_MASK, \
                                    "SBB_PARAM_H125_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L125_OFFSET, \
                                    SBB_PARAM_L125_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L125_RD_MASK, SBB_PARAM_L125_WR_MASK, \
                                    "SBB_PARAM_L125_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H126_OFFSET, \
                                    SBB_PARAM_H126_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H126_RD_MASK, SBB_PARAM_H126_WR_MASK, \
                                    "SBB_PARAM_H126_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L126_OFFSET, \
                                    SBB_PARAM_L126_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L126_RD_MASK, SBB_PARAM_L126_WR_MASK, \
                                    "SBB_PARAM_L126_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H127_OFFSET, \
                                    SBB_PARAM_H127_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H127_RD_MASK, SBB_PARAM_H127_WR_MASK, \
                                    "SBB_PARAM_H127_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L127_OFFSET, \
                                    SBB_PARAM_L127_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L127_RD_MASK, SBB_PARAM_L127_WR_MASK, \
                                    "SBB_PARAM_L127_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H128_OFFSET, \
                                    SBB_PARAM_H128_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H128_RD_MASK, SBB_PARAM_H128_WR_MASK, \
                                    "SBB_PARAM_H128_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L128_OFFSET, \
                                    SBB_PARAM_L128_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L128_RD_MASK, SBB_PARAM_L128_WR_MASK, \
                                    "SBB_PARAM_L128_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H129_OFFSET, \
                                    SBB_PARAM_H129_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H129_RD_MASK, SBB_PARAM_H129_WR_MASK, \
                                    "SBB_PARAM_H129_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L129_OFFSET, \
                                    SBB_PARAM_L129_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L129_RD_MASK, SBB_PARAM_L129_WR_MASK, \
                                    "SBB_PARAM_L129_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H130_OFFSET, \
                                    SBB_PARAM_H130_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H130_RD_MASK, SBB_PARAM_H130_WR_MASK, \
                                    "SBB_PARAM_H130_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L130_OFFSET, \
                                    SBB_PARAM_L130_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L130_RD_MASK, SBB_PARAM_L130_WR_MASK, \
                                    "SBB_PARAM_L130_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H131_OFFSET, \
                                    SBB_PARAM_H131_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H131_RD_MASK, SBB_PARAM_H131_WR_MASK, \
                                    "SBB_PARAM_H131_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L131_OFFSET, \
                                    SBB_PARAM_L131_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L131_RD_MASK, SBB_PARAM_L131_WR_MASK, \
                                    "SBB_PARAM_L131_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H132_OFFSET, \
                                    SBB_PARAM_H132_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H132_RD_MASK, SBB_PARAM_H132_WR_MASK, \
                                    "SBB_PARAM_H132_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L132_OFFSET, \
                                    SBB_PARAM_L132_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L132_RD_MASK, SBB_PARAM_L132_WR_MASK, \
                                    "SBB_PARAM_L132_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H133_OFFSET, \
                                    SBB_PARAM_H133_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H133_RD_MASK, SBB_PARAM_H133_WR_MASK, \
                                    "SBB_PARAM_H133_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L133_OFFSET, \
                                    SBB_PARAM_L133_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L133_RD_MASK, SBB_PARAM_L133_WR_MASK, \
                                    "SBB_PARAM_L133_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H134_OFFSET, \
                                    SBB_PARAM_H134_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H134_RD_MASK, SBB_PARAM_H134_WR_MASK, \
                                    "SBB_PARAM_H134_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L134_OFFSET, \
                                    SBB_PARAM_L134_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L134_RD_MASK, SBB_PARAM_L134_WR_MASK, \
                                    "SBB_PARAM_L134_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H135_OFFSET, \
                                    SBB_PARAM_H135_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H135_RD_MASK, SBB_PARAM_H135_WR_MASK, \
                                    "SBB_PARAM_H135_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L135_OFFSET, \
                                    SBB_PARAM_L135_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L135_RD_MASK, SBB_PARAM_L135_WR_MASK, \
                                    "SBB_PARAM_L135_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H136_OFFSET, \
                                    SBB_PARAM_H136_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H136_RD_MASK, SBB_PARAM_H136_WR_MASK, \
                                    "SBB_PARAM_H136_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L136_OFFSET, \
                                    SBB_PARAM_L136_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L136_RD_MASK, SBB_PARAM_L136_WR_MASK, \
                                    "SBB_PARAM_L136_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H137_OFFSET, \
                                    SBB_PARAM_H137_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H137_RD_MASK, SBB_PARAM_H137_WR_MASK, \
                                    "SBB_PARAM_H137_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L137_OFFSET, \
                                    SBB_PARAM_L137_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L137_RD_MASK, SBB_PARAM_L137_WR_MASK, \
                                    "SBB_PARAM_L137_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H138_OFFSET, \
                                    SBB_PARAM_H138_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H138_RD_MASK, SBB_PARAM_H138_WR_MASK, \
                                    "SBB_PARAM_H138_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L138_OFFSET, \
                                    SBB_PARAM_L138_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L138_RD_MASK, SBB_PARAM_L138_WR_MASK, \
                                    "SBB_PARAM_L138_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H139_OFFSET, \
                                    SBB_PARAM_H139_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H139_RD_MASK, SBB_PARAM_H139_WR_MASK, \
                                    "SBB_PARAM_H139_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L139_OFFSET, \
                                    SBB_PARAM_L139_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L139_RD_MASK, SBB_PARAM_L139_WR_MASK, \
                                    "SBB_PARAM_L139_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H140_OFFSET, \
                                    SBB_PARAM_H140_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H140_RD_MASK, SBB_PARAM_H140_WR_MASK, \
                                    "SBB_PARAM_H140_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L140_OFFSET, \
                                    SBB_PARAM_L140_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L140_RD_MASK, SBB_PARAM_L140_WR_MASK, \
                                    "SBB_PARAM_L140_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H141_OFFSET, \
                                    SBB_PARAM_H141_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H141_RD_MASK, SBB_PARAM_H141_WR_MASK, \
                                    "SBB_PARAM_H141_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L141_OFFSET, \
                                    SBB_PARAM_L141_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L141_RD_MASK, SBB_PARAM_L141_WR_MASK, \
                                    "SBB_PARAM_L141_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H142_OFFSET, \
                                    SBB_PARAM_H142_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H142_RD_MASK, SBB_PARAM_H142_WR_MASK, \
                                    "SBB_PARAM_H142_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L142_OFFSET, \
                                    SBB_PARAM_L142_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L142_RD_MASK, SBB_PARAM_L142_WR_MASK, \
                                    "SBB_PARAM_L142_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H143_OFFSET, \
                                    SBB_PARAM_H143_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H143_RD_MASK, SBB_PARAM_H143_WR_MASK, \
                                    "SBB_PARAM_H143_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L143_OFFSET, \
                                    SBB_PARAM_L143_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L143_RD_MASK, SBB_PARAM_L143_WR_MASK, \
                                    "SBB_PARAM_L143_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H144_OFFSET, \
                                    SBB_PARAM_H144_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H144_RD_MASK, SBB_PARAM_H144_WR_MASK, \
                                    "SBB_PARAM_H144_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L144_OFFSET, \
                                    SBB_PARAM_L144_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L144_RD_MASK, SBB_PARAM_L144_WR_MASK, \
                                    "SBB_PARAM_L144_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H145_OFFSET, \
                                    SBB_PARAM_H145_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H145_RD_MASK, SBB_PARAM_H145_WR_MASK, \
                                    "SBB_PARAM_H145_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L145_OFFSET, \
                                    SBB_PARAM_L145_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L145_RD_MASK, SBB_PARAM_L145_WR_MASK, \
                                    "SBB_PARAM_L145_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H146_OFFSET, \
                                    SBB_PARAM_H146_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H146_RD_MASK, SBB_PARAM_H146_WR_MASK, \
                                    "SBB_PARAM_H146_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L146_OFFSET, \
                                    SBB_PARAM_L146_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L146_RD_MASK, SBB_PARAM_L146_WR_MASK, \
                                    "SBB_PARAM_L146_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H147_OFFSET, \
                                    SBB_PARAM_H147_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H147_RD_MASK, SBB_PARAM_H147_WR_MASK, \
                                    "SBB_PARAM_H147_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L147_OFFSET, \
                                    SBB_PARAM_L147_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L147_RD_MASK, SBB_PARAM_L147_WR_MASK, \
                                    "SBB_PARAM_L147_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H148_OFFSET, \
                                    SBB_PARAM_H148_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H148_RD_MASK, SBB_PARAM_H148_WR_MASK, \
                                    "SBB_PARAM_H148_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L148_OFFSET, \
                                    SBB_PARAM_L148_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L148_RD_MASK, SBB_PARAM_L148_WR_MASK, \
                                    "SBB_PARAM_L148_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H149_OFFSET, \
                                    SBB_PARAM_H149_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H149_RD_MASK, SBB_PARAM_H149_WR_MASK, \
                                    "SBB_PARAM_H149_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L149_OFFSET, \
                                    SBB_PARAM_L149_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L149_RD_MASK, SBB_PARAM_L149_WR_MASK, \
                                    "SBB_PARAM_L149_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H150_OFFSET, \
                                    SBB_PARAM_H150_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H150_RD_MASK, SBB_PARAM_H150_WR_MASK, \
                                    "SBB_PARAM_H150_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L150_OFFSET, \
                                    SBB_PARAM_L150_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L150_RD_MASK, SBB_PARAM_L150_WR_MASK, \
                                    "SBB_PARAM_L150_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H151_OFFSET, \
                                    SBB_PARAM_H151_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H151_RD_MASK, SBB_PARAM_H151_WR_MASK, \
                                    "SBB_PARAM_H151_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L151_OFFSET, \
                                    SBB_PARAM_L151_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L151_RD_MASK, SBB_PARAM_L151_WR_MASK, \
                                    "SBB_PARAM_L151_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H152_OFFSET, \
                                    SBB_PARAM_H152_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H152_RD_MASK, SBB_PARAM_H152_WR_MASK, \
                                    "SBB_PARAM_H152_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L152_OFFSET, \
                                    SBB_PARAM_L152_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L152_RD_MASK, SBB_PARAM_L152_WR_MASK, \
                                    "SBB_PARAM_L152_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H153_OFFSET, \
                                    SBB_PARAM_H153_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H153_RD_MASK, SBB_PARAM_H153_WR_MASK, \
                                    "SBB_PARAM_H153_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L153_OFFSET, \
                                    SBB_PARAM_L153_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L153_RD_MASK, SBB_PARAM_L153_WR_MASK, \
                                    "SBB_PARAM_L153_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H154_OFFSET, \
                                    SBB_PARAM_H154_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H154_RD_MASK, SBB_PARAM_H154_WR_MASK, \
                                    "SBB_PARAM_H154_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L154_OFFSET, \
                                    SBB_PARAM_L154_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L154_RD_MASK, SBB_PARAM_L154_WR_MASK, \
                                    "SBB_PARAM_L154_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H155_OFFSET, \
                                    SBB_PARAM_H155_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H155_RD_MASK, SBB_PARAM_H155_WR_MASK, \
                                    "SBB_PARAM_H155_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L155_OFFSET, \
                                    SBB_PARAM_L155_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L155_RD_MASK, SBB_PARAM_L155_WR_MASK, \
                                    "SBB_PARAM_L155_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H156_OFFSET, \
                                    SBB_PARAM_H156_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H156_RD_MASK, SBB_PARAM_H156_WR_MASK, \
                                    "SBB_PARAM_H156_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L156_OFFSET, \
                                    SBB_PARAM_L156_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L156_RD_MASK, SBB_PARAM_L156_WR_MASK, \
                                    "SBB_PARAM_L156_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H157_OFFSET, \
                                    SBB_PARAM_H157_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H157_RD_MASK, SBB_PARAM_H157_WR_MASK, \
                                    "SBB_PARAM_H157_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L157_OFFSET, \
                                    SBB_PARAM_L157_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L157_RD_MASK, SBB_PARAM_L157_WR_MASK, \
                                    "SBB_PARAM_L157_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H158_OFFSET, \
                                    SBB_PARAM_H158_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H158_RD_MASK, SBB_PARAM_H158_WR_MASK, \
                                    "SBB_PARAM_H158_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L158_OFFSET, \
                                    SBB_PARAM_L158_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L158_RD_MASK, SBB_PARAM_L158_WR_MASK, \
                                    "SBB_PARAM_L158_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H159_OFFSET, \
                                    SBB_PARAM_H159_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H159_RD_MASK, SBB_PARAM_H159_WR_MASK, \
                                    "SBB_PARAM_H159_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L159_OFFSET, \
                                    SBB_PARAM_L159_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L159_RD_MASK, SBB_PARAM_L159_WR_MASK, \
                                    "SBB_PARAM_L159_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H160_OFFSET, \
                                    SBB_PARAM_H160_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H160_RD_MASK, SBB_PARAM_H160_WR_MASK, \
                                    "SBB_PARAM_H160_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L160_OFFSET, \
                                    SBB_PARAM_L160_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L160_RD_MASK, SBB_PARAM_L160_WR_MASK, \
                                    "SBB_PARAM_L160_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H161_OFFSET, \
                                    SBB_PARAM_H161_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H161_RD_MASK, SBB_PARAM_H161_WR_MASK, \
                                    "SBB_PARAM_H161_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L161_OFFSET, \
                                    SBB_PARAM_L161_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L161_RD_MASK, SBB_PARAM_L161_WR_MASK, \
                                    "SBB_PARAM_L161_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H162_OFFSET, \
                                    SBB_PARAM_H162_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H162_RD_MASK, SBB_PARAM_H162_WR_MASK, \
                                    "SBB_PARAM_H162_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L162_OFFSET, \
                                    SBB_PARAM_L162_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L162_RD_MASK, SBB_PARAM_L162_WR_MASK, \
                                    "SBB_PARAM_L162_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H163_OFFSET, \
                                    SBB_PARAM_H163_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H163_RD_MASK, SBB_PARAM_H163_WR_MASK, \
                                    "SBB_PARAM_H163_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L163_OFFSET, \
                                    SBB_PARAM_L163_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L163_RD_MASK, SBB_PARAM_L163_WR_MASK, \
                                    "SBB_PARAM_L163_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H164_OFFSET, \
                                    SBB_PARAM_H164_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H164_RD_MASK, SBB_PARAM_H164_WR_MASK, \
                                    "SBB_PARAM_H164_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L164_OFFSET, \
                                    SBB_PARAM_L164_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L164_RD_MASK, SBB_PARAM_L164_WR_MASK, \
                                    "SBB_PARAM_L164_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H165_OFFSET, \
                                    SBB_PARAM_H165_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H165_RD_MASK, SBB_PARAM_H165_WR_MASK, \
                                    "SBB_PARAM_H165_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L165_OFFSET, \
                                    SBB_PARAM_L165_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L165_RD_MASK, SBB_PARAM_L165_WR_MASK, \
                                    "SBB_PARAM_L165_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H166_OFFSET, \
                                    SBB_PARAM_H166_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H166_RD_MASK, SBB_PARAM_H166_WR_MASK, \
                                    "SBB_PARAM_H166_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L166_OFFSET, \
                                    SBB_PARAM_L166_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L166_RD_MASK, SBB_PARAM_L166_WR_MASK, \
                                    "SBB_PARAM_L166_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H167_OFFSET, \
                                    SBB_PARAM_H167_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H167_RD_MASK, SBB_PARAM_H167_WR_MASK, \
                                    "SBB_PARAM_H167_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L167_OFFSET, \
                                    SBB_PARAM_L167_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L167_RD_MASK, SBB_PARAM_L167_WR_MASK, \
                                    "SBB_PARAM_L167_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H168_OFFSET, \
                                    SBB_PARAM_H168_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H168_RD_MASK, SBB_PARAM_H168_WR_MASK, \
                                    "SBB_PARAM_H168_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L168_OFFSET, \
                                    SBB_PARAM_L168_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L168_RD_MASK, SBB_PARAM_L168_WR_MASK, \
                                    "SBB_PARAM_L168_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H169_OFFSET, \
                                    SBB_PARAM_H169_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H169_RD_MASK, SBB_PARAM_H169_WR_MASK, \
                                    "SBB_PARAM_H169_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L169_OFFSET, \
                                    SBB_PARAM_L169_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L169_RD_MASK, SBB_PARAM_L169_WR_MASK, \
                                    "SBB_PARAM_L169_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H170_OFFSET, \
                                    SBB_PARAM_H170_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H170_RD_MASK, SBB_PARAM_H170_WR_MASK, \
                                    "SBB_PARAM_H170_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L170_OFFSET, \
                                    SBB_PARAM_L170_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L170_RD_MASK, SBB_PARAM_L170_WR_MASK, \
                                    "SBB_PARAM_L170_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H171_OFFSET, \
                                    SBB_PARAM_H171_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H171_RD_MASK, SBB_PARAM_H171_WR_MASK, \
                                    "SBB_PARAM_H171_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L171_OFFSET, \
                                    SBB_PARAM_L171_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L171_RD_MASK, SBB_PARAM_L171_WR_MASK, \
                                    "SBB_PARAM_L171_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H172_OFFSET, \
                                    SBB_PARAM_H172_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H172_RD_MASK, SBB_PARAM_H172_WR_MASK, \
                                    "SBB_PARAM_H172_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L172_OFFSET, \
                                    SBB_PARAM_L172_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L172_RD_MASK, SBB_PARAM_L172_WR_MASK, \
                                    "SBB_PARAM_L172_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H173_OFFSET, \
                                    SBB_PARAM_H173_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H173_RD_MASK, SBB_PARAM_H173_WR_MASK, \
                                    "SBB_PARAM_H173_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L173_OFFSET, \
                                    SBB_PARAM_L173_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L173_RD_MASK, SBB_PARAM_L173_WR_MASK, \
                                    "SBB_PARAM_L173_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H174_OFFSET, \
                                    SBB_PARAM_H174_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H174_RD_MASK, SBB_PARAM_H174_WR_MASK, \
                                    "SBB_PARAM_H174_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L174_OFFSET, \
                                    SBB_PARAM_L174_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L174_RD_MASK, SBB_PARAM_L174_WR_MASK, \
                                    "SBB_PARAM_L174_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H175_OFFSET, \
                                    SBB_PARAM_H175_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H175_RD_MASK, SBB_PARAM_H175_WR_MASK, \
                                    "SBB_PARAM_H175_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L175_OFFSET, \
                                    SBB_PARAM_L175_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L175_RD_MASK, SBB_PARAM_L175_WR_MASK, \
                                    "SBB_PARAM_L175_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H176_OFFSET, \
                                    SBB_PARAM_H176_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H176_RD_MASK, SBB_PARAM_H176_WR_MASK, \
                                    "SBB_PARAM_H176_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L176_OFFSET, \
                                    SBB_PARAM_L176_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L176_RD_MASK, SBB_PARAM_L176_WR_MASK, \
                                    "SBB_PARAM_L176_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H177_OFFSET, \
                                    SBB_PARAM_H177_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H177_RD_MASK, SBB_PARAM_H177_WR_MASK, \
                                    "SBB_PARAM_H177_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L177_OFFSET, \
                                    SBB_PARAM_L177_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L177_RD_MASK, SBB_PARAM_L177_WR_MASK, \
                                    "SBB_PARAM_L177_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H178_OFFSET, \
                                    SBB_PARAM_H178_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H178_RD_MASK, SBB_PARAM_H178_WR_MASK, \
                                    "SBB_PARAM_H178_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L178_OFFSET, \
                                    SBB_PARAM_L178_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L178_RD_MASK, SBB_PARAM_L178_WR_MASK, \
                                    "SBB_PARAM_L178_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H179_OFFSET, \
                                    SBB_PARAM_H179_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H179_RD_MASK, SBB_PARAM_H179_WR_MASK, \
                                    "SBB_PARAM_H179_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L179_OFFSET, \
                                    SBB_PARAM_L179_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L179_RD_MASK, SBB_PARAM_L179_WR_MASK, \
                                    "SBB_PARAM_L179_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H180_OFFSET, \
                                    SBB_PARAM_H180_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H180_RD_MASK, SBB_PARAM_H180_WR_MASK, \
                                    "SBB_PARAM_H180_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L180_OFFSET, \
                                    SBB_PARAM_L180_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L180_RD_MASK, SBB_PARAM_L180_WR_MASK, \
                                    "SBB_PARAM_L180_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H181_OFFSET, \
                                    SBB_PARAM_H181_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H181_RD_MASK, SBB_PARAM_H181_WR_MASK, \
                                    "SBB_PARAM_H181_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L181_OFFSET, \
                                    SBB_PARAM_L181_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L181_RD_MASK, SBB_PARAM_L181_WR_MASK, \
                                    "SBB_PARAM_L181_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H182_OFFSET, \
                                    SBB_PARAM_H182_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H182_RD_MASK, SBB_PARAM_H182_WR_MASK, \
                                    "SBB_PARAM_H182_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L182_OFFSET, \
                                    SBB_PARAM_L182_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L182_RD_MASK, SBB_PARAM_L182_WR_MASK, \
                                    "SBB_PARAM_L182_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H183_OFFSET, \
                                    SBB_PARAM_H183_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H183_RD_MASK, SBB_PARAM_H183_WR_MASK, \
                                    "SBB_PARAM_H183_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L183_OFFSET, \
                                    SBB_PARAM_L183_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L183_RD_MASK, SBB_PARAM_L183_WR_MASK, \
                                    "SBB_PARAM_L183_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H184_OFFSET, \
                                    SBB_PARAM_H184_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H184_RD_MASK, SBB_PARAM_H184_WR_MASK, \
                                    "SBB_PARAM_H184_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L184_OFFSET, \
                                    SBB_PARAM_L184_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L184_RD_MASK, SBB_PARAM_L184_WR_MASK, \
                                    "SBB_PARAM_L184_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H185_OFFSET, \
                                    SBB_PARAM_H185_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H185_RD_MASK, SBB_PARAM_H185_WR_MASK, \
                                    "SBB_PARAM_H185_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L185_OFFSET, \
                                    SBB_PARAM_L185_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L185_RD_MASK, SBB_PARAM_L185_WR_MASK, \
                                    "SBB_PARAM_L185_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H186_OFFSET, \
                                    SBB_PARAM_H186_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H186_RD_MASK, SBB_PARAM_H186_WR_MASK, \
                                    "SBB_PARAM_H186_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L186_OFFSET, \
                                    SBB_PARAM_L186_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L186_RD_MASK, SBB_PARAM_L186_WR_MASK, \
                                    "SBB_PARAM_L186_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H187_OFFSET, \
                                    SBB_PARAM_H187_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H187_RD_MASK, SBB_PARAM_H187_WR_MASK, \
                                    "SBB_PARAM_H187_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L187_OFFSET, \
                                    SBB_PARAM_L187_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L187_RD_MASK, SBB_PARAM_L187_WR_MASK, \
                                    "SBB_PARAM_L187_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H188_OFFSET, \
                                    SBB_PARAM_H188_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H188_RD_MASK, SBB_PARAM_H188_WR_MASK, \
                                    "SBB_PARAM_H188_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L188_OFFSET, \
                                    SBB_PARAM_L188_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L188_RD_MASK, SBB_PARAM_L188_WR_MASK, \
                                    "SBB_PARAM_L188_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H189_OFFSET, \
                                    SBB_PARAM_H189_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H189_RD_MASK, SBB_PARAM_H189_WR_MASK, \
                                    "SBB_PARAM_H189_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L189_OFFSET, \
                                    SBB_PARAM_L189_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L189_RD_MASK, SBB_PARAM_L189_WR_MASK, \
                                    "SBB_PARAM_L189_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H190_OFFSET, \
                                    SBB_PARAM_H190_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H190_RD_MASK, SBB_PARAM_H190_WR_MASK, \
                                    "SBB_PARAM_H190_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L190_OFFSET, \
                                    SBB_PARAM_L190_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L190_RD_MASK, SBB_PARAM_L190_WR_MASK, \
                                    "SBB_PARAM_L190_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H191_OFFSET, \
                                    SBB_PARAM_H191_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H191_RD_MASK, SBB_PARAM_H191_WR_MASK, \
                                    "SBB_PARAM_H191_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L191_OFFSET, \
                                    SBB_PARAM_L191_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L191_RD_MASK, SBB_PARAM_L191_WR_MASK, \
                                    "SBB_PARAM_L191_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H192_OFFSET, \
                                    SBB_PARAM_H192_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H192_RD_MASK, SBB_PARAM_H192_WR_MASK, \
                                    "SBB_PARAM_H192_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L192_OFFSET, \
                                    SBB_PARAM_L192_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L192_RD_MASK, SBB_PARAM_L192_WR_MASK, \
                                    "SBB_PARAM_L192_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H193_OFFSET, \
                                    SBB_PARAM_H193_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H193_RD_MASK, SBB_PARAM_H193_WR_MASK, \
                                    "SBB_PARAM_H193_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L193_OFFSET, \
                                    SBB_PARAM_L193_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L193_RD_MASK, SBB_PARAM_L193_WR_MASK, \
                                    "SBB_PARAM_L193_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H194_OFFSET, \
                                    SBB_PARAM_H194_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H194_RD_MASK, SBB_PARAM_H194_WR_MASK, \
                                    "SBB_PARAM_H194_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L194_OFFSET, \
                                    SBB_PARAM_L194_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L194_RD_MASK, SBB_PARAM_L194_WR_MASK, \
                                    "SBB_PARAM_L194_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H195_OFFSET, \
                                    SBB_PARAM_H195_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H195_RD_MASK, SBB_PARAM_H195_WR_MASK, \
                                    "SBB_PARAM_H195_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L195_OFFSET, \
                                    SBB_PARAM_L195_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L195_RD_MASK, SBB_PARAM_L195_WR_MASK, \
                                    "SBB_PARAM_L195_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H196_OFFSET, \
                                    SBB_PARAM_H196_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H196_RD_MASK, SBB_PARAM_H196_WR_MASK, \
                                    "SBB_PARAM_H196_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L196_OFFSET, \
                                    SBB_PARAM_L196_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L196_RD_MASK, SBB_PARAM_L196_WR_MASK, \
                                    "SBB_PARAM_L196_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H197_OFFSET, \
                                    SBB_PARAM_H197_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H197_RD_MASK, SBB_PARAM_H197_WR_MASK, \
                                    "SBB_PARAM_H197_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L197_OFFSET, \
                                    SBB_PARAM_L197_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L197_RD_MASK, SBB_PARAM_L197_WR_MASK, \
                                    "SBB_PARAM_L197_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H198_OFFSET, \
                                    SBB_PARAM_H198_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H198_RD_MASK, SBB_PARAM_H198_WR_MASK, \
                                    "SBB_PARAM_H198_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L198_OFFSET, \
                                    SBB_PARAM_L198_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L198_RD_MASK, SBB_PARAM_L198_WR_MASK, \
                                    "SBB_PARAM_L198_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H199_OFFSET, \
                                    SBB_PARAM_H199_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H199_RD_MASK, SBB_PARAM_H199_WR_MASK, \
                                    "SBB_PARAM_H199_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L199_OFFSET, \
                                    SBB_PARAM_L199_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L199_RD_MASK, SBB_PARAM_L199_WR_MASK, \
                                    "SBB_PARAM_L199_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H200_OFFSET, \
                                    SBB_PARAM_H200_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H200_RD_MASK, SBB_PARAM_H200_WR_MASK, \
                                    "SBB_PARAM_H200_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L200_OFFSET, \
                                    SBB_PARAM_L200_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L200_RD_MASK, SBB_PARAM_L200_WR_MASK, \
                                    "SBB_PARAM_L200_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H201_OFFSET, \
                                    SBB_PARAM_H201_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H201_RD_MASK, SBB_PARAM_H201_WR_MASK, \
                                    "SBB_PARAM_H201_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L201_OFFSET, \
                                    SBB_PARAM_L201_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L201_RD_MASK, SBB_PARAM_L201_WR_MASK, \
                                    "SBB_PARAM_L201_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H202_OFFSET, \
                                    SBB_PARAM_H202_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H202_RD_MASK, SBB_PARAM_H202_WR_MASK, \
                                    "SBB_PARAM_H202_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L202_OFFSET, \
                                    SBB_PARAM_L202_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L202_RD_MASK, SBB_PARAM_L202_WR_MASK, \
                                    "SBB_PARAM_L202_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H203_OFFSET, \
                                    SBB_PARAM_H203_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H203_RD_MASK, SBB_PARAM_H203_WR_MASK, \
                                    "SBB_PARAM_H203_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L203_OFFSET, \
                                    SBB_PARAM_L203_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L203_RD_MASK, SBB_PARAM_L203_WR_MASK, \
                                    "SBB_PARAM_L203_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H204_OFFSET, \
                                    SBB_PARAM_H204_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H204_RD_MASK, SBB_PARAM_H204_WR_MASK, \
                                    "SBB_PARAM_H204_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L204_OFFSET, \
                                    SBB_PARAM_L204_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L204_RD_MASK, SBB_PARAM_L204_WR_MASK, \
                                    "SBB_PARAM_L204_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H205_OFFSET, \
                                    SBB_PARAM_H205_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H205_RD_MASK, SBB_PARAM_H205_WR_MASK, \
                                    "SBB_PARAM_H205_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L205_OFFSET, \
                                    SBB_PARAM_L205_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L205_RD_MASK, SBB_PARAM_L205_WR_MASK, \
                                    "SBB_PARAM_L205_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H206_OFFSET, \
                                    SBB_PARAM_H206_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H206_RD_MASK, SBB_PARAM_H206_WR_MASK, \
                                    "SBB_PARAM_H206_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L206_OFFSET, \
                                    SBB_PARAM_L206_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L206_RD_MASK, SBB_PARAM_L206_WR_MASK, \
                                    "SBB_PARAM_L206_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H207_OFFSET, \
                                    SBB_PARAM_H207_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H207_RD_MASK, SBB_PARAM_H207_WR_MASK, \
                                    "SBB_PARAM_H207_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L207_OFFSET, \
                                    SBB_PARAM_L207_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L207_RD_MASK, SBB_PARAM_L207_WR_MASK, \
                                    "SBB_PARAM_L207_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H208_OFFSET, \
                                    SBB_PARAM_H208_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H208_RD_MASK, SBB_PARAM_H208_WR_MASK, \
                                    "SBB_PARAM_H208_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L208_OFFSET, \
                                    SBB_PARAM_L208_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L208_RD_MASK, SBB_PARAM_L208_WR_MASK, \
                                    "SBB_PARAM_L208_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H209_OFFSET, \
                                    SBB_PARAM_H209_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H209_RD_MASK, SBB_PARAM_H209_WR_MASK, \
                                    "SBB_PARAM_H209_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L209_OFFSET, \
                                    SBB_PARAM_L209_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L209_RD_MASK, SBB_PARAM_L209_WR_MASK, \
                                    "SBB_PARAM_L209_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H210_OFFSET, \
                                    SBB_PARAM_H210_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H210_RD_MASK, SBB_PARAM_H210_WR_MASK, \
                                    "SBB_PARAM_H210_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L210_OFFSET, \
                                    SBB_PARAM_L210_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L210_RD_MASK, SBB_PARAM_L210_WR_MASK, \
                                    "SBB_PARAM_L210_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H211_OFFSET, \
                                    SBB_PARAM_H211_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H211_RD_MASK, SBB_PARAM_H211_WR_MASK, \
                                    "SBB_PARAM_H211_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L211_OFFSET, \
                                    SBB_PARAM_L211_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L211_RD_MASK, SBB_PARAM_L211_WR_MASK, \
                                    "SBB_PARAM_L211_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H212_OFFSET, \
                                    SBB_PARAM_H212_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H212_RD_MASK, SBB_PARAM_H212_WR_MASK, \
                                    "SBB_PARAM_H212_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L212_OFFSET, \
                                    SBB_PARAM_L212_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L212_RD_MASK, SBB_PARAM_L212_WR_MASK, \
                                    "SBB_PARAM_L212_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H213_OFFSET, \
                                    SBB_PARAM_H213_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H213_RD_MASK, SBB_PARAM_H213_WR_MASK, \
                                    "SBB_PARAM_H213_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L213_OFFSET, \
                                    SBB_PARAM_L213_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L213_RD_MASK, SBB_PARAM_L213_WR_MASK, \
                                    "SBB_PARAM_L213_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H214_OFFSET, \
                                    SBB_PARAM_H214_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H214_RD_MASK, SBB_PARAM_H214_WR_MASK, \
                                    "SBB_PARAM_H214_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L214_OFFSET, \
                                    SBB_PARAM_L214_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L214_RD_MASK, SBB_PARAM_L214_WR_MASK, \
                                    "SBB_PARAM_L214_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H215_OFFSET, \
                                    SBB_PARAM_H215_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H215_RD_MASK, SBB_PARAM_H215_WR_MASK, \
                                    "SBB_PARAM_H215_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L215_OFFSET, \
                                    SBB_PARAM_L215_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L215_RD_MASK, SBB_PARAM_L215_WR_MASK, \
                                    "SBB_PARAM_L215_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H216_OFFSET, \
                                    SBB_PARAM_H216_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H216_RD_MASK, SBB_PARAM_H216_WR_MASK, \
                                    "SBB_PARAM_H216_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L216_OFFSET, \
                                    SBB_PARAM_L216_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L216_RD_MASK, SBB_PARAM_L216_WR_MASK, \
                                    "SBB_PARAM_L216_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H217_OFFSET, \
                                    SBB_PARAM_H217_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H217_RD_MASK, SBB_PARAM_H217_WR_MASK, \
                                    "SBB_PARAM_H217_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L217_OFFSET, \
                                    SBB_PARAM_L217_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L217_RD_MASK, SBB_PARAM_L217_WR_MASK, \
                                    "SBB_PARAM_L217_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H218_OFFSET, \
                                    SBB_PARAM_H218_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H218_RD_MASK, SBB_PARAM_H218_WR_MASK, \
                                    "SBB_PARAM_H218_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L218_OFFSET, \
                                    SBB_PARAM_L218_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L218_RD_MASK, SBB_PARAM_L218_WR_MASK, \
                                    "SBB_PARAM_L218_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H219_OFFSET, \
                                    SBB_PARAM_H219_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H219_RD_MASK, SBB_PARAM_H219_WR_MASK, \
                                    "SBB_PARAM_H219_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L219_OFFSET, \
                                    SBB_PARAM_L219_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L219_RD_MASK, SBB_PARAM_L219_WR_MASK, \
                                    "SBB_PARAM_L219_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H220_OFFSET, \
                                    SBB_PARAM_H220_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H220_RD_MASK, SBB_PARAM_H220_WR_MASK, \
                                    "SBB_PARAM_H220_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L220_OFFSET, \
                                    SBB_PARAM_L220_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L220_RD_MASK, SBB_PARAM_L220_WR_MASK, \
                                    "SBB_PARAM_L220_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H221_OFFSET, \
                                    SBB_PARAM_H221_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H221_RD_MASK, SBB_PARAM_H221_WR_MASK, \
                                    "SBB_PARAM_H221_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L221_OFFSET, \
                                    SBB_PARAM_L221_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L221_RD_MASK, SBB_PARAM_L221_WR_MASK, \
                                    "SBB_PARAM_L221_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H222_OFFSET, \
                                    SBB_PARAM_H222_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H222_RD_MASK, SBB_PARAM_H222_WR_MASK, \
                                    "SBB_PARAM_H222_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L222_OFFSET, \
                                    SBB_PARAM_L222_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L222_RD_MASK, SBB_PARAM_L222_WR_MASK, \
                                    "SBB_PARAM_L222_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H223_OFFSET, \
                                    SBB_PARAM_H223_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H223_RD_MASK, SBB_PARAM_H223_WR_MASK, \
                                    "SBB_PARAM_H223_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L223_OFFSET, \
                                    SBB_PARAM_L223_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L223_RD_MASK, SBB_PARAM_L223_WR_MASK, \
                                    "SBB_PARAM_L223_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H224_OFFSET, \
                                    SBB_PARAM_H224_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H224_RD_MASK, SBB_PARAM_H224_WR_MASK, \
                                    "SBB_PARAM_H224_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L224_OFFSET, \
                                    SBB_PARAM_L224_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L224_RD_MASK, SBB_PARAM_L224_WR_MASK, \
                                    "SBB_PARAM_L224_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H225_OFFSET, \
                                    SBB_PARAM_H225_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H225_RD_MASK, SBB_PARAM_H225_WR_MASK, \
                                    "SBB_PARAM_H225_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L225_OFFSET, \
                                    SBB_PARAM_L225_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L225_RD_MASK, SBB_PARAM_L225_WR_MASK, \
                                    "SBB_PARAM_L225_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H226_OFFSET, \
                                    SBB_PARAM_H226_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H226_RD_MASK, SBB_PARAM_H226_WR_MASK, \
                                    "SBB_PARAM_H226_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L226_OFFSET, \
                                    SBB_PARAM_L226_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L226_RD_MASK, SBB_PARAM_L226_WR_MASK, \
                                    "SBB_PARAM_L226_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H227_OFFSET, \
                                    SBB_PARAM_H227_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H227_RD_MASK, SBB_PARAM_H227_WR_MASK, \
                                    "SBB_PARAM_H227_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L227_OFFSET, \
                                    SBB_PARAM_L227_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L227_RD_MASK, SBB_PARAM_L227_WR_MASK, \
                                    "SBB_PARAM_L227_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H228_OFFSET, \
                                    SBB_PARAM_H228_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H228_RD_MASK, SBB_PARAM_H228_WR_MASK, \
                                    "SBB_PARAM_H228_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L228_OFFSET, \
                                    SBB_PARAM_L228_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L228_RD_MASK, SBB_PARAM_L228_WR_MASK, \
                                    "SBB_PARAM_L228_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H229_OFFSET, \
                                    SBB_PARAM_H229_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H229_RD_MASK, SBB_PARAM_H229_WR_MASK, \
                                    "SBB_PARAM_H229_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L229_OFFSET, \
                                    SBB_PARAM_L229_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L229_RD_MASK, SBB_PARAM_L229_WR_MASK, \
                                    "SBB_PARAM_L229_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H230_OFFSET, \
                                    SBB_PARAM_H230_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H230_RD_MASK, SBB_PARAM_H230_WR_MASK, \
                                    "SBB_PARAM_H230_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L230_OFFSET, \
                                    SBB_PARAM_L230_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L230_RD_MASK, SBB_PARAM_L230_WR_MASK, \
                                    "SBB_PARAM_L230_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H231_OFFSET, \
                                    SBB_PARAM_H231_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H231_RD_MASK, SBB_PARAM_H231_WR_MASK, \
                                    "SBB_PARAM_H231_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L231_OFFSET, \
                                    SBB_PARAM_L231_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L231_RD_MASK, SBB_PARAM_L231_WR_MASK, \
                                    "SBB_PARAM_L231_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H232_OFFSET, \
                                    SBB_PARAM_H232_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H232_RD_MASK, SBB_PARAM_H232_WR_MASK, \
                                    "SBB_PARAM_H232_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L232_OFFSET, \
                                    SBB_PARAM_L232_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L232_RD_MASK, SBB_PARAM_L232_WR_MASK, \
                                    "SBB_PARAM_L232_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H233_OFFSET, \
                                    SBB_PARAM_H233_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H233_RD_MASK, SBB_PARAM_H233_WR_MASK, \
                                    "SBB_PARAM_H233_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L233_OFFSET, \
                                    SBB_PARAM_L233_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L233_RD_MASK, SBB_PARAM_L233_WR_MASK, \
                                    "SBB_PARAM_L233_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H234_OFFSET, \
                                    SBB_PARAM_H234_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H234_RD_MASK, SBB_PARAM_H234_WR_MASK, \
                                    "SBB_PARAM_H234_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L234_OFFSET, \
                                    SBB_PARAM_L234_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L234_RD_MASK, SBB_PARAM_L234_WR_MASK, \
                                    "SBB_PARAM_L234_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H235_OFFSET, \
                                    SBB_PARAM_H235_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H235_RD_MASK, SBB_PARAM_H235_WR_MASK, \
                                    "SBB_PARAM_H235_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L235_OFFSET, \
                                    SBB_PARAM_L235_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L235_RD_MASK, SBB_PARAM_L235_WR_MASK, \
                                    "SBB_PARAM_L235_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H236_OFFSET, \
                                    SBB_PARAM_H236_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H236_RD_MASK, SBB_PARAM_H236_WR_MASK, \
                                    "SBB_PARAM_H236_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L236_OFFSET, \
                                    SBB_PARAM_L236_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L236_RD_MASK, SBB_PARAM_L236_WR_MASK, \
                                    "SBB_PARAM_L236_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H237_OFFSET, \
                                    SBB_PARAM_H237_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H237_RD_MASK, SBB_PARAM_H237_WR_MASK, \
                                    "SBB_PARAM_H237_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L237_OFFSET, \
                                    SBB_PARAM_L237_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L237_RD_MASK, SBB_PARAM_L237_WR_MASK, \
                                    "SBB_PARAM_L237_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H238_OFFSET, \
                                    SBB_PARAM_H238_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H238_RD_MASK, SBB_PARAM_H238_WR_MASK, \
                                    "SBB_PARAM_H238_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L238_OFFSET, \
                                    SBB_PARAM_L238_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L238_RD_MASK, SBB_PARAM_L238_WR_MASK, \
                                    "SBB_PARAM_L238_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H239_OFFSET, \
                                    SBB_PARAM_H239_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H239_RD_MASK, SBB_PARAM_H239_WR_MASK, \
                                    "SBB_PARAM_H239_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L239_OFFSET, \
                                    SBB_PARAM_L239_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L239_RD_MASK, SBB_PARAM_L239_WR_MASK, \
                                    "SBB_PARAM_L239_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H240_OFFSET, \
                                    SBB_PARAM_H240_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H240_RD_MASK, SBB_PARAM_H240_WR_MASK, \
                                    "SBB_PARAM_H240_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L240_OFFSET, \
                                    SBB_PARAM_L240_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L240_RD_MASK, SBB_PARAM_L240_WR_MASK, \
                                    "SBB_PARAM_L240_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H241_OFFSET, \
                                    SBB_PARAM_H241_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H241_RD_MASK, SBB_PARAM_H241_WR_MASK, \
                                    "SBB_PARAM_H241_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L241_OFFSET, \
                                    SBB_PARAM_L241_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L241_RD_MASK, SBB_PARAM_L241_WR_MASK, \
                                    "SBB_PARAM_L241_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H242_OFFSET, \
                                    SBB_PARAM_H242_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H242_RD_MASK, SBB_PARAM_H242_WR_MASK, \
                                    "SBB_PARAM_H242_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L242_OFFSET, \
                                    SBB_PARAM_L242_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L242_RD_MASK, SBB_PARAM_L242_WR_MASK, \
                                    "SBB_PARAM_L242_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H243_OFFSET, \
                                    SBB_PARAM_H243_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H243_RD_MASK, SBB_PARAM_H243_WR_MASK, \
                                    "SBB_PARAM_H243_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L243_OFFSET, \
                                    SBB_PARAM_L243_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L243_RD_MASK, SBB_PARAM_L243_WR_MASK, \
                                    "SBB_PARAM_L243_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H244_OFFSET, \
                                    SBB_PARAM_H244_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H244_RD_MASK, SBB_PARAM_H244_WR_MASK, \
                                    "SBB_PARAM_H244_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L244_OFFSET, \
                                    SBB_PARAM_L244_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L244_RD_MASK, SBB_PARAM_L244_WR_MASK, \
                                    "SBB_PARAM_L244_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H245_OFFSET, \
                                    SBB_PARAM_H245_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H245_RD_MASK, SBB_PARAM_H245_WR_MASK, \
                                    "SBB_PARAM_H245_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L245_OFFSET, \
                                    SBB_PARAM_L245_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L245_RD_MASK, SBB_PARAM_L245_WR_MASK, \
                                    "SBB_PARAM_L245_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H246_OFFSET, \
                                    SBB_PARAM_H246_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H246_RD_MASK, SBB_PARAM_H246_WR_MASK, \
                                    "SBB_PARAM_H246_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L246_OFFSET, \
                                    SBB_PARAM_L246_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L246_RD_MASK, SBB_PARAM_L246_WR_MASK, \
                                    "SBB_PARAM_L246_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H247_OFFSET, \
                                    SBB_PARAM_H247_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H247_RD_MASK, SBB_PARAM_H247_WR_MASK, \
                                    "SBB_PARAM_H247_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L247_OFFSET, \
                                    SBB_PARAM_L247_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L247_RD_MASK, SBB_PARAM_L247_WR_MASK, \
                                    "SBB_PARAM_L247_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H248_OFFSET, \
                                    SBB_PARAM_H248_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H248_RD_MASK, SBB_PARAM_H248_WR_MASK, \
                                    "SBB_PARAM_H248_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L248_OFFSET, \
                                    SBB_PARAM_L248_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L248_RD_MASK, SBB_PARAM_L248_WR_MASK, \
                                    "SBB_PARAM_L248_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H249_OFFSET, \
                                    SBB_PARAM_H249_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H249_RD_MASK, SBB_PARAM_H249_WR_MASK, \
                                    "SBB_PARAM_H249_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L249_OFFSET, \
                                    SBB_PARAM_L249_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L249_RD_MASK, SBB_PARAM_L249_WR_MASK, \
                                    "SBB_PARAM_L249_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H250_OFFSET, \
                                    SBB_PARAM_H250_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H250_RD_MASK, SBB_PARAM_H250_WR_MASK, \
                                    "SBB_PARAM_H250_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L250_OFFSET, \
                                    SBB_PARAM_L250_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L250_RD_MASK, SBB_PARAM_L250_WR_MASK, \
                                    "SBB_PARAM_L250_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H251_OFFSET, \
                                    SBB_PARAM_H251_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H251_RD_MASK, SBB_PARAM_H251_WR_MASK, \
                                    "SBB_PARAM_H251_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L251_OFFSET, \
                                    SBB_PARAM_L251_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L251_RD_MASK, SBB_PARAM_L251_WR_MASK, \
                                    "SBB_PARAM_L251_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H252_OFFSET, \
                                    SBB_PARAM_H252_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H252_RD_MASK, SBB_PARAM_H252_WR_MASK, \
                                    "SBB_PARAM_H252_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L252_OFFSET, \
                                    SBB_PARAM_L252_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L252_RD_MASK, SBB_PARAM_L252_WR_MASK, \
                                    "SBB_PARAM_L252_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H253_OFFSET, \
                                    SBB_PARAM_H253_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H253_RD_MASK, SBB_PARAM_H253_WR_MASK, \
                                    "SBB_PARAM_H253_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L253_OFFSET, \
                                    SBB_PARAM_L253_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L253_RD_MASK, SBB_PARAM_L253_WR_MASK, \
                                    "SBB_PARAM_L253_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H254_OFFSET, \
                                    SBB_PARAM_H254_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H254_RD_MASK, SBB_PARAM_H254_WR_MASK, \
                                    "SBB_PARAM_H254_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L254_OFFSET, \
                                    SBB_PARAM_L254_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L254_RD_MASK, SBB_PARAM_L254_WR_MASK, \
                                    "SBB_PARAM_L254_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H255_OFFSET, \
                                    SBB_PARAM_H255_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H255_RD_MASK, SBB_PARAM_H255_WR_MASK, \
                                    "SBB_PARAM_H255_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L255_OFFSET, \
                                    SBB_PARAM_L255_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L255_RD_MASK, SBB_PARAM_L255_WR_MASK, \
                                    "SBB_PARAM_L255_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H256_OFFSET, \
                                    SBB_PARAM_H256_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H256_RD_MASK, SBB_PARAM_H256_WR_MASK, \
                                    "SBB_PARAM_H256_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L256_OFFSET, \
                                    SBB_PARAM_L256_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L256_RD_MASK, SBB_PARAM_L256_WR_MASK, \
                                    "SBB_PARAM_L256_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H257_OFFSET, \
                                    SBB_PARAM_H257_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H257_RD_MASK, SBB_PARAM_H257_WR_MASK, \
                                    "SBB_PARAM_H257_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L257_OFFSET, \
                                    SBB_PARAM_L257_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L257_RD_MASK, SBB_PARAM_L257_WR_MASK, \
                                    "SBB_PARAM_L257_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H258_OFFSET, \
                                    SBB_PARAM_H258_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H258_RD_MASK, SBB_PARAM_H258_WR_MASK, \
                                    "SBB_PARAM_H258_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L258_OFFSET, \
                                    SBB_PARAM_L258_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L258_RD_MASK, SBB_PARAM_L258_WR_MASK, \
                                    "SBB_PARAM_L258_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H259_OFFSET, \
                                    SBB_PARAM_H259_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H259_RD_MASK, SBB_PARAM_H259_WR_MASK, \
                                    "SBB_PARAM_H259_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L259_OFFSET, \
                                    SBB_PARAM_L259_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L259_RD_MASK, SBB_PARAM_L259_WR_MASK, \
                                    "SBB_PARAM_L259_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H260_OFFSET, \
                                    SBB_PARAM_H260_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H260_RD_MASK, SBB_PARAM_H260_WR_MASK, \
                                    "SBB_PARAM_H260_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L260_OFFSET, \
                                    SBB_PARAM_L260_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L260_RD_MASK, SBB_PARAM_L260_WR_MASK, \
                                    "SBB_PARAM_L260_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H261_OFFSET, \
                                    SBB_PARAM_H261_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H261_RD_MASK, SBB_PARAM_H261_WR_MASK, \
                                    "SBB_PARAM_H261_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L261_OFFSET, \
                                    SBB_PARAM_L261_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L261_RD_MASK, SBB_PARAM_L261_WR_MASK, \
                                    "SBB_PARAM_L261_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H262_OFFSET, \
                                    SBB_PARAM_H262_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H262_RD_MASK, SBB_PARAM_H262_WR_MASK, \
                                    "SBB_PARAM_H262_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L262_OFFSET, \
                                    SBB_PARAM_L262_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L262_RD_MASK, SBB_PARAM_L262_WR_MASK, \
                                    "SBB_PARAM_L262_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H263_OFFSET, \
                                    SBB_PARAM_H263_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H263_RD_MASK, SBB_PARAM_H263_WR_MASK, \
                                    "SBB_PARAM_H263_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L263_OFFSET, \
                                    SBB_PARAM_L263_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L263_RD_MASK, SBB_PARAM_L263_WR_MASK, \
                                    "SBB_PARAM_L263_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H264_OFFSET, \
                                    SBB_PARAM_H264_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H264_RD_MASK, SBB_PARAM_H264_WR_MASK, \
                                    "SBB_PARAM_H264_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L264_OFFSET, \
                                    SBB_PARAM_L264_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L264_RD_MASK, SBB_PARAM_L264_WR_MASK, \
                                    "SBB_PARAM_L264_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H265_OFFSET, \
                                    SBB_PARAM_H265_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H265_RD_MASK, SBB_PARAM_H265_WR_MASK, \
                                    "SBB_PARAM_H265_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L265_OFFSET, \
                                    SBB_PARAM_L265_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L265_RD_MASK, SBB_PARAM_L265_WR_MASK, \
                                    "SBB_PARAM_L265_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H266_OFFSET, \
                                    SBB_PARAM_H266_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H266_RD_MASK, SBB_PARAM_H266_WR_MASK, \
                                    "SBB_PARAM_H266_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L266_OFFSET, \
                                    SBB_PARAM_L266_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L266_RD_MASK, SBB_PARAM_L266_WR_MASK, \
                                    "SBB_PARAM_L266_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H267_OFFSET, \
                                    SBB_PARAM_H267_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H267_RD_MASK, SBB_PARAM_H267_WR_MASK, \
                                    "SBB_PARAM_H267_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L267_OFFSET, \
                                    SBB_PARAM_L267_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L267_RD_MASK, SBB_PARAM_L267_WR_MASK, \
                                    "SBB_PARAM_L267_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H268_OFFSET, \
                                    SBB_PARAM_H268_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H268_RD_MASK, SBB_PARAM_H268_WR_MASK, \
                                    "SBB_PARAM_H268_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L268_OFFSET, \
                                    SBB_PARAM_L268_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L268_RD_MASK, SBB_PARAM_L268_WR_MASK, \
                                    "SBB_PARAM_L268_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H269_OFFSET, \
                                    SBB_PARAM_H269_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H269_RD_MASK, SBB_PARAM_H269_WR_MASK, \
                                    "SBB_PARAM_H269_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L269_OFFSET, \
                                    SBB_PARAM_L269_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L269_RD_MASK, SBB_PARAM_L269_WR_MASK, \
                                    "SBB_PARAM_L269_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H270_OFFSET, \
                                    SBB_PARAM_H270_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H270_RD_MASK, SBB_PARAM_H270_WR_MASK, \
                                    "SBB_PARAM_H270_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L270_OFFSET, \
                                    SBB_PARAM_L270_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L270_RD_MASK, SBB_PARAM_L270_WR_MASK, \
                                    "SBB_PARAM_L270_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H271_OFFSET, \
                                    SBB_PARAM_H271_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H271_RD_MASK, SBB_PARAM_H271_WR_MASK, \
                                    "SBB_PARAM_H271_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L271_OFFSET, \
                                    SBB_PARAM_L271_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L271_RD_MASK, SBB_PARAM_L271_WR_MASK, \
                                    "SBB_PARAM_L271_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H272_OFFSET, \
                                    SBB_PARAM_H272_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H272_RD_MASK, SBB_PARAM_H272_WR_MASK, \
                                    "SBB_PARAM_H272_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L272_OFFSET, \
                                    SBB_PARAM_L272_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L272_RD_MASK, SBB_PARAM_L272_WR_MASK, \
                                    "SBB_PARAM_L272_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H273_OFFSET, \
                                    SBB_PARAM_H273_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H273_RD_MASK, SBB_PARAM_H273_WR_MASK, \
                                    "SBB_PARAM_H273_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L273_OFFSET, \
                                    SBB_PARAM_L273_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L273_RD_MASK, SBB_PARAM_L273_WR_MASK, \
                                    "SBB_PARAM_L273_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H274_OFFSET, \
                                    SBB_PARAM_H274_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H274_RD_MASK, SBB_PARAM_H274_WR_MASK, \
                                    "SBB_PARAM_H274_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L274_OFFSET, \
                                    SBB_PARAM_L274_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L274_RD_MASK, SBB_PARAM_L274_WR_MASK, \
                                    "SBB_PARAM_L274_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H275_OFFSET, \
                                    SBB_PARAM_H275_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H275_RD_MASK, SBB_PARAM_H275_WR_MASK, \
                                    "SBB_PARAM_H275_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L275_OFFSET, \
                                    SBB_PARAM_L275_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L275_RD_MASK, SBB_PARAM_L275_WR_MASK, \
                                    "SBB_PARAM_L275_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H276_OFFSET, \
                                    SBB_PARAM_H276_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H276_RD_MASK, SBB_PARAM_H276_WR_MASK, \
                                    "SBB_PARAM_H276_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L276_OFFSET, \
                                    SBB_PARAM_L276_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L276_RD_MASK, SBB_PARAM_L276_WR_MASK, \
                                    "SBB_PARAM_L276_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H277_OFFSET, \
                                    SBB_PARAM_H277_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H277_RD_MASK, SBB_PARAM_H277_WR_MASK, \
                                    "SBB_PARAM_H277_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L277_OFFSET, \
                                    SBB_PARAM_L277_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L277_RD_MASK, SBB_PARAM_L277_WR_MASK, \
                                    "SBB_PARAM_L277_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H278_OFFSET, \
                                    SBB_PARAM_H278_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H278_RD_MASK, SBB_PARAM_H278_WR_MASK, \
                                    "SBB_PARAM_H278_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L278_OFFSET, \
                                    SBB_PARAM_L278_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L278_RD_MASK, SBB_PARAM_L278_WR_MASK, \
                                    "SBB_PARAM_L278_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H279_OFFSET, \
                                    SBB_PARAM_H279_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H279_RD_MASK, SBB_PARAM_H279_WR_MASK, \
                                    "SBB_PARAM_H279_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L279_OFFSET, \
                                    SBB_PARAM_L279_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L279_RD_MASK, SBB_PARAM_L279_WR_MASK, \
                                    "SBB_PARAM_L279_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H280_OFFSET, \
                                    SBB_PARAM_H280_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H280_RD_MASK, SBB_PARAM_H280_WR_MASK, \
                                    "SBB_PARAM_H280_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L280_OFFSET, \
                                    SBB_PARAM_L280_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L280_RD_MASK, SBB_PARAM_L280_WR_MASK, \
                                    "SBB_PARAM_L280_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H281_OFFSET, \
                                    SBB_PARAM_H281_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H281_RD_MASK, SBB_PARAM_H281_WR_MASK, \
                                    "SBB_PARAM_H281_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L281_OFFSET, \
                                    SBB_PARAM_L281_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L281_RD_MASK, SBB_PARAM_L281_WR_MASK, \
                                    "SBB_PARAM_L281_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H282_OFFSET, \
                                    SBB_PARAM_H282_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H282_RD_MASK, SBB_PARAM_H282_WR_MASK, \
                                    "SBB_PARAM_H282_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L282_OFFSET, \
                                    SBB_PARAM_L282_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L282_RD_MASK, SBB_PARAM_L282_WR_MASK, \
                                    "SBB_PARAM_L282_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H283_OFFSET, \
                                    SBB_PARAM_H283_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H283_RD_MASK, SBB_PARAM_H283_WR_MASK, \
                                    "SBB_PARAM_H283_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L283_OFFSET, \
                                    SBB_PARAM_L283_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L283_RD_MASK, SBB_PARAM_L283_WR_MASK, \
                                    "SBB_PARAM_L283_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H284_OFFSET, \
                                    SBB_PARAM_H284_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H284_RD_MASK, SBB_PARAM_H284_WR_MASK, \
                                    "SBB_PARAM_H284_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L284_OFFSET, \
                                    SBB_PARAM_L284_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L284_RD_MASK, SBB_PARAM_L284_WR_MASK, \
                                    "SBB_PARAM_L284_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H285_OFFSET, \
                                    SBB_PARAM_H285_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H285_RD_MASK, SBB_PARAM_H285_WR_MASK, \
                                    "SBB_PARAM_H285_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L285_OFFSET, \
                                    SBB_PARAM_L285_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L285_RD_MASK, SBB_PARAM_L285_WR_MASK, \
                                    "SBB_PARAM_L285_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H286_OFFSET, \
                                    SBB_PARAM_H286_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H286_RD_MASK, SBB_PARAM_H286_WR_MASK, \
                                    "SBB_PARAM_H286_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L286_OFFSET, \
                                    SBB_PARAM_L286_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L286_RD_MASK, SBB_PARAM_L286_WR_MASK, \
                                    "SBB_PARAM_L286_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H287_OFFSET, \
                                    SBB_PARAM_H287_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H287_RD_MASK, SBB_PARAM_H287_WR_MASK, \
                                    "SBB_PARAM_H287_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L287_OFFSET, \
                                    SBB_PARAM_L287_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L287_RD_MASK, SBB_PARAM_L287_WR_MASK, \
                                    "SBB_PARAM_L287_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H288_OFFSET, \
                                    SBB_PARAM_H288_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H288_RD_MASK, SBB_PARAM_H288_WR_MASK, \
                                    "SBB_PARAM_H288_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L288_OFFSET, \
                                    SBB_PARAM_L288_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L288_RD_MASK, SBB_PARAM_L288_WR_MASK, \
                                    "SBB_PARAM_L288_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H289_OFFSET, \
                                    SBB_PARAM_H289_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H289_RD_MASK, SBB_PARAM_H289_WR_MASK, \
                                    "SBB_PARAM_H289_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L289_OFFSET, \
                                    SBB_PARAM_L289_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L289_RD_MASK, SBB_PARAM_L289_WR_MASK, \
                                    "SBB_PARAM_L289_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H290_OFFSET, \
                                    SBB_PARAM_H290_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H290_RD_MASK, SBB_PARAM_H290_WR_MASK, \
                                    "SBB_PARAM_H290_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L290_OFFSET, \
                                    SBB_PARAM_L290_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L290_RD_MASK, SBB_PARAM_L290_WR_MASK, \
                                    "SBB_PARAM_L290_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H291_OFFSET, \
                                    SBB_PARAM_H291_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H291_RD_MASK, SBB_PARAM_H291_WR_MASK, \
                                    "SBB_PARAM_H291_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L291_OFFSET, \
                                    SBB_PARAM_L291_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L291_RD_MASK, SBB_PARAM_L291_WR_MASK, \
                                    "SBB_PARAM_L291_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H292_OFFSET, \
                                    SBB_PARAM_H292_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H292_RD_MASK, SBB_PARAM_H292_WR_MASK, \
                                    "SBB_PARAM_H292_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L292_OFFSET, \
                                    SBB_PARAM_L292_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L292_RD_MASK, SBB_PARAM_L292_WR_MASK, \
                                    "SBB_PARAM_L292_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H293_OFFSET, \
                                    SBB_PARAM_H293_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H293_RD_MASK, SBB_PARAM_H293_WR_MASK, \
                                    "SBB_PARAM_H293_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L293_OFFSET, \
                                    SBB_PARAM_L293_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L293_RD_MASK, SBB_PARAM_L293_WR_MASK, \
                                    "SBB_PARAM_L293_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H294_OFFSET, \
                                    SBB_PARAM_H294_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H294_RD_MASK, SBB_PARAM_H294_WR_MASK, \
                                    "SBB_PARAM_H294_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L294_OFFSET, \
                                    SBB_PARAM_L294_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L294_RD_MASK, SBB_PARAM_L294_WR_MASK, \
                                    "SBB_PARAM_L294_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H295_OFFSET, \
                                    SBB_PARAM_H295_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H295_RD_MASK, SBB_PARAM_H295_WR_MASK, \
                                    "SBB_PARAM_H295_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L295_OFFSET, \
                                    SBB_PARAM_L295_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L295_RD_MASK, SBB_PARAM_L295_WR_MASK, \
                                    "SBB_PARAM_L295_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H296_OFFSET, \
                                    SBB_PARAM_H296_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H296_RD_MASK, SBB_PARAM_H296_WR_MASK, \
                                    "SBB_PARAM_H296_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L296_OFFSET, \
                                    SBB_PARAM_L296_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L296_RD_MASK, SBB_PARAM_L296_WR_MASK, \
                                    "SBB_PARAM_L296_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H297_OFFSET, \
                                    SBB_PARAM_H297_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H297_RD_MASK, SBB_PARAM_H297_WR_MASK, \
                                    "SBB_PARAM_H297_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L297_OFFSET, \
                                    SBB_PARAM_L297_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L297_RD_MASK, SBB_PARAM_L297_WR_MASK, \
                                    "SBB_PARAM_L297_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H298_OFFSET, \
                                    SBB_PARAM_H298_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H298_RD_MASK, SBB_PARAM_H298_WR_MASK, \
                                    "SBB_PARAM_H298_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L298_OFFSET, \
                                    SBB_PARAM_L298_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L298_RD_MASK, SBB_PARAM_L298_WR_MASK, \
                                    "SBB_PARAM_L298_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H299_OFFSET, \
                                    SBB_PARAM_H299_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H299_RD_MASK, SBB_PARAM_H299_WR_MASK, \
                                    "SBB_PARAM_H299_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L299_OFFSET, \
                                    SBB_PARAM_L299_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L299_RD_MASK, SBB_PARAM_L299_WR_MASK, \
                                    "SBB_PARAM_L299_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H300_OFFSET, \
                                    SBB_PARAM_H300_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H300_RD_MASK, SBB_PARAM_H300_WR_MASK, \
                                    "SBB_PARAM_H300_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L300_OFFSET, \
                                    SBB_PARAM_L300_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L300_RD_MASK, SBB_PARAM_L300_WR_MASK, \
                                    "SBB_PARAM_L300_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H301_OFFSET, \
                                    SBB_PARAM_H301_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H301_RD_MASK, SBB_PARAM_H301_WR_MASK, \
                                    "SBB_PARAM_H301_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L301_OFFSET, \
                                    SBB_PARAM_L301_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L301_RD_MASK, SBB_PARAM_L301_WR_MASK, \
                                    "SBB_PARAM_L301_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H302_OFFSET, \
                                    SBB_PARAM_H302_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H302_RD_MASK, SBB_PARAM_H302_WR_MASK, \
                                    "SBB_PARAM_H302_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L302_OFFSET, \
                                    SBB_PARAM_L302_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L302_RD_MASK, SBB_PARAM_L302_WR_MASK, \
                                    "SBB_PARAM_L302_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H303_OFFSET, \
                                    SBB_PARAM_H303_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H303_RD_MASK, SBB_PARAM_H303_WR_MASK, \
                                    "SBB_PARAM_H303_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L303_OFFSET, \
                                    SBB_PARAM_L303_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L303_RD_MASK, SBB_PARAM_L303_WR_MASK, \
                                    "SBB_PARAM_L303_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H304_OFFSET, \
                                    SBB_PARAM_H304_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H304_RD_MASK, SBB_PARAM_H304_WR_MASK, \
                                    "SBB_PARAM_H304_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L304_OFFSET, \
                                    SBB_PARAM_L304_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L304_RD_MASK, SBB_PARAM_L304_WR_MASK, \
                                    "SBB_PARAM_L304_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H305_OFFSET, \
                                    SBB_PARAM_H305_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H305_RD_MASK, SBB_PARAM_H305_WR_MASK, \
                                    "SBB_PARAM_H305_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L305_OFFSET, \
                                    SBB_PARAM_L305_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L305_RD_MASK, SBB_PARAM_L305_WR_MASK, \
                                    "SBB_PARAM_L305_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H306_OFFSET, \
                                    SBB_PARAM_H306_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H306_RD_MASK, SBB_PARAM_H306_WR_MASK, \
                                    "SBB_PARAM_H306_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L306_OFFSET, \
                                    SBB_PARAM_L306_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L306_RD_MASK, SBB_PARAM_L306_WR_MASK, \
                                    "SBB_PARAM_L306_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H307_OFFSET, \
                                    SBB_PARAM_H307_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H307_RD_MASK, SBB_PARAM_H307_WR_MASK, \
                                    "SBB_PARAM_H307_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L307_OFFSET, \
                                    SBB_PARAM_L307_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L307_RD_MASK, SBB_PARAM_L307_WR_MASK, \
                                    "SBB_PARAM_L307_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H308_OFFSET, \
                                    SBB_PARAM_H308_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H308_RD_MASK, SBB_PARAM_H308_WR_MASK, \
                                    "SBB_PARAM_H308_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L308_OFFSET, \
                                    SBB_PARAM_L308_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L308_RD_MASK, SBB_PARAM_L308_WR_MASK, \
                                    "SBB_PARAM_L308_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H309_OFFSET, \
                                    SBB_PARAM_H309_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H309_RD_MASK, SBB_PARAM_H309_WR_MASK, \
                                    "SBB_PARAM_H309_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L309_OFFSET, \
                                    SBB_PARAM_L309_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L309_RD_MASK, SBB_PARAM_L309_WR_MASK, \
                                    "SBB_PARAM_L309_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H310_OFFSET, \
                                    SBB_PARAM_H310_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H310_RD_MASK, SBB_PARAM_H310_WR_MASK, \
                                    "SBB_PARAM_H310_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L310_OFFSET, \
                                    SBB_PARAM_L310_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L310_RD_MASK, SBB_PARAM_L310_WR_MASK, \
                                    "SBB_PARAM_L310_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H311_OFFSET, \
                                    SBB_PARAM_H311_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H311_RD_MASK, SBB_PARAM_H311_WR_MASK, \
                                    "SBB_PARAM_H311_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L311_OFFSET, \
                                    SBB_PARAM_L311_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L311_RD_MASK, SBB_PARAM_L311_WR_MASK, \
                                    "SBB_PARAM_L311_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H312_OFFSET, \
                                    SBB_PARAM_H312_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H312_RD_MASK, SBB_PARAM_H312_WR_MASK, \
                                    "SBB_PARAM_H312_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L312_OFFSET, \
                                    SBB_PARAM_L312_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L312_RD_MASK, SBB_PARAM_L312_WR_MASK, \
                                    "SBB_PARAM_L312_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H313_OFFSET, \
                                    SBB_PARAM_H313_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H313_RD_MASK, SBB_PARAM_H313_WR_MASK, \
                                    "SBB_PARAM_H313_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L313_OFFSET, \
                                    SBB_PARAM_L313_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L313_RD_MASK, SBB_PARAM_L313_WR_MASK, \
                                    "SBB_PARAM_L313_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H314_OFFSET, \
                                    SBB_PARAM_H314_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H314_RD_MASK, SBB_PARAM_H314_WR_MASK, \
                                    "SBB_PARAM_H314_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L314_OFFSET, \
                                    SBB_PARAM_L314_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L314_RD_MASK, SBB_PARAM_L314_WR_MASK, \
                                    "SBB_PARAM_L314_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H315_OFFSET, \
                                    SBB_PARAM_H315_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H315_RD_MASK, SBB_PARAM_H315_WR_MASK, \
                                    "SBB_PARAM_H315_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L315_OFFSET, \
                                    SBB_PARAM_L315_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L315_RD_MASK, SBB_PARAM_L315_WR_MASK, \
                                    "SBB_PARAM_L315_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H316_OFFSET, \
                                    SBB_PARAM_H316_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H316_RD_MASK, SBB_PARAM_H316_WR_MASK, \
                                    "SBB_PARAM_H316_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L316_OFFSET, \
                                    SBB_PARAM_L316_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L316_RD_MASK, SBB_PARAM_L316_WR_MASK, \
                                    "SBB_PARAM_L316_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H317_OFFSET, \
                                    SBB_PARAM_H317_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H317_RD_MASK, SBB_PARAM_H317_WR_MASK, \
                                    "SBB_PARAM_H317_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L317_OFFSET, \
                                    SBB_PARAM_L317_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L317_RD_MASK, SBB_PARAM_L317_WR_MASK, \
                                    "SBB_PARAM_L317_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H318_OFFSET, \
                                    SBB_PARAM_H318_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H318_RD_MASK, SBB_PARAM_H318_WR_MASK, \
                                    "SBB_PARAM_H318_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L318_OFFSET, \
                                    SBB_PARAM_L318_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L318_RD_MASK, SBB_PARAM_L318_WR_MASK, \
                                    "SBB_PARAM_L318_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H319_OFFSET, \
                                    SBB_PARAM_H319_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H319_RD_MASK, SBB_PARAM_H319_WR_MASK, \
                                    "SBB_PARAM_H319_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L319_OFFSET, \
                                    SBB_PARAM_L319_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L319_RD_MASK, SBB_PARAM_L319_WR_MASK, \
                                    "SBB_PARAM_L319_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H320_OFFSET, \
                                    SBB_PARAM_H320_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H320_RD_MASK, SBB_PARAM_H320_WR_MASK, \
                                    "SBB_PARAM_H320_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L320_OFFSET, \
                                    SBB_PARAM_L320_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L320_RD_MASK, SBB_PARAM_L320_WR_MASK, \
                                    "SBB_PARAM_L320_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H321_OFFSET, \
                                    SBB_PARAM_H321_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H321_RD_MASK, SBB_PARAM_H321_WR_MASK, \
                                    "SBB_PARAM_H321_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L321_OFFSET, \
                                    SBB_PARAM_L321_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L321_RD_MASK, SBB_PARAM_L321_WR_MASK, \
                                    "SBB_PARAM_L321_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H322_OFFSET, \
                                    SBB_PARAM_H322_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H322_RD_MASK, SBB_PARAM_H322_WR_MASK, \
                                    "SBB_PARAM_H322_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L322_OFFSET, \
                                    SBB_PARAM_L322_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L322_RD_MASK, SBB_PARAM_L322_WR_MASK, \
                                    "SBB_PARAM_L322_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H323_OFFSET, \
                                    SBB_PARAM_H323_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H323_RD_MASK, SBB_PARAM_H323_WR_MASK, \
                                    "SBB_PARAM_H323_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L323_OFFSET, \
                                    SBB_PARAM_L323_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L323_RD_MASK, SBB_PARAM_L323_WR_MASK, \
                                    "SBB_PARAM_L323_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H324_OFFSET, \
                                    SBB_PARAM_H324_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H324_RD_MASK, SBB_PARAM_H324_WR_MASK, \
                                    "SBB_PARAM_H324_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L324_OFFSET, \
                                    SBB_PARAM_L324_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L324_RD_MASK, SBB_PARAM_L324_WR_MASK, \
                                    "SBB_PARAM_L324_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H325_OFFSET, \
                                    SBB_PARAM_H325_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H325_RD_MASK, SBB_PARAM_H325_WR_MASK, \
                                    "SBB_PARAM_H325_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L325_OFFSET, \
                                    SBB_PARAM_L325_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L325_RD_MASK, SBB_PARAM_L325_WR_MASK, \
                                    "SBB_PARAM_L325_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H326_OFFSET, \
                                    SBB_PARAM_H326_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H326_RD_MASK, SBB_PARAM_H326_WR_MASK, \
                                    "SBB_PARAM_H326_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L326_OFFSET, \
                                    SBB_PARAM_L326_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L326_RD_MASK, SBB_PARAM_L326_WR_MASK, \
                                    "SBB_PARAM_L326_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H327_OFFSET, \
                                    SBB_PARAM_H327_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H327_RD_MASK, SBB_PARAM_H327_WR_MASK, \
                                    "SBB_PARAM_H327_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L327_OFFSET, \
                                    SBB_PARAM_L327_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L327_RD_MASK, SBB_PARAM_L327_WR_MASK, \
                                    "SBB_PARAM_L327_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H328_OFFSET, \
                                    SBB_PARAM_H328_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H328_RD_MASK, SBB_PARAM_H328_WR_MASK, \
                                    "SBB_PARAM_H328_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L328_OFFSET, \
                                    SBB_PARAM_L328_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L328_RD_MASK, SBB_PARAM_L328_WR_MASK, \
                                    "SBB_PARAM_L328_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H329_OFFSET, \
                                    SBB_PARAM_H329_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H329_RD_MASK, SBB_PARAM_H329_WR_MASK, \
                                    "SBB_PARAM_H329_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L329_OFFSET, \
                                    SBB_PARAM_L329_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L329_RD_MASK, SBB_PARAM_L329_WR_MASK, \
                                    "SBB_PARAM_L329_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H330_OFFSET, \
                                    SBB_PARAM_H330_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H330_RD_MASK, SBB_PARAM_H330_WR_MASK, \
                                    "SBB_PARAM_H330_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L330_OFFSET, \
                                    SBB_PARAM_L330_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L330_RD_MASK, SBB_PARAM_L330_WR_MASK, \
                                    "SBB_PARAM_L330_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H331_OFFSET, \
                                    SBB_PARAM_H331_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H331_RD_MASK, SBB_PARAM_H331_WR_MASK, \
                                    "SBB_PARAM_H331_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L331_OFFSET, \
                                    SBB_PARAM_L331_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L331_RD_MASK, SBB_PARAM_L331_WR_MASK, \
                                    "SBB_PARAM_L331_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H332_OFFSET, \
                                    SBB_PARAM_H332_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H332_RD_MASK, SBB_PARAM_H332_WR_MASK, \
                                    "SBB_PARAM_H332_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L332_OFFSET, \
                                    SBB_PARAM_L332_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L332_RD_MASK, SBB_PARAM_L332_WR_MASK, \
                                    "SBB_PARAM_L332_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H333_OFFSET, \
                                    SBB_PARAM_H333_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H333_RD_MASK, SBB_PARAM_H333_WR_MASK, \
                                    "SBB_PARAM_H333_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L333_OFFSET, \
                                    SBB_PARAM_L333_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L333_RD_MASK, SBB_PARAM_L333_WR_MASK, \
                                    "SBB_PARAM_L333_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H334_OFFSET, \
                                    SBB_PARAM_H334_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H334_RD_MASK, SBB_PARAM_H334_WR_MASK, \
                                    "SBB_PARAM_H334_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L334_OFFSET, \
                                    SBB_PARAM_L334_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L334_RD_MASK, SBB_PARAM_L334_WR_MASK, \
                                    "SBB_PARAM_L334_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H335_OFFSET, \
                                    SBB_PARAM_H335_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H335_RD_MASK, SBB_PARAM_H335_WR_MASK, \
                                    "SBB_PARAM_H335_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L335_OFFSET, \
                                    SBB_PARAM_L335_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L335_RD_MASK, SBB_PARAM_L335_WR_MASK, \
                                    "SBB_PARAM_L335_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H336_OFFSET, \
                                    SBB_PARAM_H336_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H336_RD_MASK, SBB_PARAM_H336_WR_MASK, \
                                    "SBB_PARAM_H336_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L336_OFFSET, \
                                    SBB_PARAM_L336_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L336_RD_MASK, SBB_PARAM_L336_WR_MASK, \
                                    "SBB_PARAM_L336_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H337_OFFSET, \
                                    SBB_PARAM_H337_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H337_RD_MASK, SBB_PARAM_H337_WR_MASK, \
                                    "SBB_PARAM_H337_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L337_OFFSET, \
                                    SBB_PARAM_L337_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L337_RD_MASK, SBB_PARAM_L337_WR_MASK, \
                                    "SBB_PARAM_L337_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H338_OFFSET, \
                                    SBB_PARAM_H338_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H338_RD_MASK, SBB_PARAM_H338_WR_MASK, \
                                    "SBB_PARAM_H338_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L338_OFFSET, \
                                    SBB_PARAM_L338_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L338_RD_MASK, SBB_PARAM_L338_WR_MASK, \
                                    "SBB_PARAM_L338_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H339_OFFSET, \
                                    SBB_PARAM_H339_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H339_RD_MASK, SBB_PARAM_H339_WR_MASK, \
                                    "SBB_PARAM_H339_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L339_OFFSET, \
                                    SBB_PARAM_L339_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L339_RD_MASK, SBB_PARAM_L339_WR_MASK, \
                                    "SBB_PARAM_L339_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H340_OFFSET, \
                                    SBB_PARAM_H340_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H340_RD_MASK, SBB_PARAM_H340_WR_MASK, \
                                    "SBB_PARAM_H340_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L340_OFFSET, \
                                    SBB_PARAM_L340_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L340_RD_MASK, SBB_PARAM_L340_WR_MASK, \
                                    "SBB_PARAM_L340_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H341_OFFSET, \
                                    SBB_PARAM_H341_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H341_RD_MASK, SBB_PARAM_H341_WR_MASK, \
                                    "SBB_PARAM_H341_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L341_OFFSET, \
                                    SBB_PARAM_L341_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L341_RD_MASK, SBB_PARAM_L341_WR_MASK, \
                                    "SBB_PARAM_L341_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H342_OFFSET, \
                                    SBB_PARAM_H342_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H342_RD_MASK, SBB_PARAM_H342_WR_MASK, \
                                    "SBB_PARAM_H342_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L342_OFFSET, \
                                    SBB_PARAM_L342_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L342_RD_MASK, SBB_PARAM_L342_WR_MASK, \
                                    "SBB_PARAM_L342_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H343_OFFSET, \
                                    SBB_PARAM_H343_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H343_RD_MASK, SBB_PARAM_H343_WR_MASK, \
                                    "SBB_PARAM_H343_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L343_OFFSET, \
                                    SBB_PARAM_L343_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L343_RD_MASK, SBB_PARAM_L343_WR_MASK, \
                                    "SBB_PARAM_L343_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H344_OFFSET, \
                                    SBB_PARAM_H344_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H344_RD_MASK, SBB_PARAM_H344_WR_MASK, \
                                    "SBB_PARAM_H344_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L344_OFFSET, \
                                    SBB_PARAM_L344_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L344_RD_MASK, SBB_PARAM_L344_WR_MASK, \
                                    "SBB_PARAM_L344_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H345_OFFSET, \
                                    SBB_PARAM_H345_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H345_RD_MASK, SBB_PARAM_H345_WR_MASK, \
                                    "SBB_PARAM_H345_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L345_OFFSET, \
                                    SBB_PARAM_L345_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L345_RD_MASK, SBB_PARAM_L345_WR_MASK, \
                                    "SBB_PARAM_L345_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H346_OFFSET, \
                                    SBB_PARAM_H346_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H346_RD_MASK, SBB_PARAM_H346_WR_MASK, \
                                    "SBB_PARAM_H346_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L346_OFFSET, \
                                    SBB_PARAM_L346_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L346_RD_MASK, SBB_PARAM_L346_WR_MASK, \
                                    "SBB_PARAM_L346_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H347_OFFSET, \
                                    SBB_PARAM_H347_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H347_RD_MASK, SBB_PARAM_H347_WR_MASK, \
                                    "SBB_PARAM_H347_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L347_OFFSET, \
                                    SBB_PARAM_L347_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L347_RD_MASK, SBB_PARAM_L347_WR_MASK, \
                                    "SBB_PARAM_L347_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H348_OFFSET, \
                                    SBB_PARAM_H348_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H348_RD_MASK, SBB_PARAM_H348_WR_MASK, \
                                    "SBB_PARAM_H348_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L348_OFFSET, \
                                    SBB_PARAM_L348_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L348_RD_MASK, SBB_PARAM_L348_WR_MASK, \
                                    "SBB_PARAM_L348_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H349_OFFSET, \
                                    SBB_PARAM_H349_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H349_RD_MASK, SBB_PARAM_H349_WR_MASK, \
                                    "SBB_PARAM_H349_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L349_OFFSET, \
                                    SBB_PARAM_L349_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L349_RD_MASK, SBB_PARAM_L349_WR_MASK, \
                                    "SBB_PARAM_L349_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H350_OFFSET, \
                                    SBB_PARAM_H350_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H350_RD_MASK, SBB_PARAM_H350_WR_MASK, \
                                    "SBB_PARAM_H350_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L350_OFFSET, \
                                    SBB_PARAM_L350_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L350_RD_MASK, SBB_PARAM_L350_WR_MASK, \
                                    "SBB_PARAM_L350_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H351_OFFSET, \
                                    SBB_PARAM_H351_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H351_RD_MASK, SBB_PARAM_H351_WR_MASK, \
                                    "SBB_PARAM_H351_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L351_OFFSET, \
                                    SBB_PARAM_L351_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L351_RD_MASK, SBB_PARAM_L351_WR_MASK, \
                                    "SBB_PARAM_L351_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H352_OFFSET, \
                                    SBB_PARAM_H352_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H352_RD_MASK, SBB_PARAM_H352_WR_MASK, \
                                    "SBB_PARAM_H352_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L352_OFFSET, \
                                    SBB_PARAM_L352_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L352_RD_MASK, SBB_PARAM_L352_WR_MASK, \
                                    "SBB_PARAM_L352_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H353_OFFSET, \
                                    SBB_PARAM_H353_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H353_RD_MASK, SBB_PARAM_H353_WR_MASK, \
                                    "SBB_PARAM_H353_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L353_OFFSET, \
                                    SBB_PARAM_L353_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L353_RD_MASK, SBB_PARAM_L353_WR_MASK, \
                                    "SBB_PARAM_L353_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H354_OFFSET, \
                                    SBB_PARAM_H354_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H354_RD_MASK, SBB_PARAM_H354_WR_MASK, \
                                    "SBB_PARAM_H354_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L354_OFFSET, \
                                    SBB_PARAM_L354_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L354_RD_MASK, SBB_PARAM_L354_WR_MASK, \
                                    "SBB_PARAM_L354_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H355_OFFSET, \
                                    SBB_PARAM_H355_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H355_RD_MASK, SBB_PARAM_H355_WR_MASK, \
                                    "SBB_PARAM_H355_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L355_OFFSET, \
                                    SBB_PARAM_L355_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L355_RD_MASK, SBB_PARAM_L355_WR_MASK, \
                                    "SBB_PARAM_L355_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H356_OFFSET, \
                                    SBB_PARAM_H356_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H356_RD_MASK, SBB_PARAM_H356_WR_MASK, \
                                    "SBB_PARAM_H356_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L356_OFFSET, \
                                    SBB_PARAM_L356_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L356_RD_MASK, SBB_PARAM_L356_WR_MASK, \
                                    "SBB_PARAM_L356_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H357_OFFSET, \
                                    SBB_PARAM_H357_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H357_RD_MASK, SBB_PARAM_H357_WR_MASK, \
                                    "SBB_PARAM_H357_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L357_OFFSET, \
                                    SBB_PARAM_L357_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L357_RD_MASK, SBB_PARAM_L357_WR_MASK, \
                                    "SBB_PARAM_L357_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H358_OFFSET, \
                                    SBB_PARAM_H358_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H358_RD_MASK, SBB_PARAM_H358_WR_MASK, \
                                    "SBB_PARAM_H358_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L358_OFFSET, \
                                    SBB_PARAM_L358_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L358_RD_MASK, SBB_PARAM_L358_WR_MASK, \
                                    "SBB_PARAM_L358_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H359_OFFSET, \
                                    SBB_PARAM_H359_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H359_RD_MASK, SBB_PARAM_H359_WR_MASK, \
                                    "SBB_PARAM_H359_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L359_OFFSET, \
                                    SBB_PARAM_L359_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L359_RD_MASK, SBB_PARAM_L359_WR_MASK, \
                                    "SBB_PARAM_L359_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H360_OFFSET, \
                                    SBB_PARAM_H360_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H360_RD_MASK, SBB_PARAM_H360_WR_MASK, \
                                    "SBB_PARAM_H360_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L360_OFFSET, \
                                    SBB_PARAM_L360_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L360_RD_MASK, SBB_PARAM_L360_WR_MASK, \
                                    "SBB_PARAM_L360_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H361_OFFSET, \
                                    SBB_PARAM_H361_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H361_RD_MASK, SBB_PARAM_H361_WR_MASK, \
                                    "SBB_PARAM_H361_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L361_OFFSET, \
                                    SBB_PARAM_L361_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L361_RD_MASK, SBB_PARAM_L361_WR_MASK, \
                                    "SBB_PARAM_L361_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H362_OFFSET, \
                                    SBB_PARAM_H362_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H362_RD_MASK, SBB_PARAM_H362_WR_MASK, \
                                    "SBB_PARAM_H362_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L362_OFFSET, \
                                    SBB_PARAM_L362_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L362_RD_MASK, SBB_PARAM_L362_WR_MASK, \
                                    "SBB_PARAM_L362_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H363_OFFSET, \
                                    SBB_PARAM_H363_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H363_RD_MASK, SBB_PARAM_H363_WR_MASK, \
                                    "SBB_PARAM_H363_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L363_OFFSET, \
                                    SBB_PARAM_L363_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L363_RD_MASK, SBB_PARAM_L363_WR_MASK, \
                                    "SBB_PARAM_L363_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H364_OFFSET, \
                                    SBB_PARAM_H364_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H364_RD_MASK, SBB_PARAM_H364_WR_MASK, \
                                    "SBB_PARAM_H364_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L364_OFFSET, \
                                    SBB_PARAM_L364_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L364_RD_MASK, SBB_PARAM_L364_WR_MASK, \
                                    "SBB_PARAM_L364_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H365_OFFSET, \
                                    SBB_PARAM_H365_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H365_RD_MASK, SBB_PARAM_H365_WR_MASK, \
                                    "SBB_PARAM_H365_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L365_OFFSET, \
                                    SBB_PARAM_L365_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L365_RD_MASK, SBB_PARAM_L365_WR_MASK, \
                                    "SBB_PARAM_L365_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H366_OFFSET, \
                                    SBB_PARAM_H366_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H366_RD_MASK, SBB_PARAM_H366_WR_MASK, \
                                    "SBB_PARAM_H366_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L366_OFFSET, \
                                    SBB_PARAM_L366_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L366_RD_MASK, SBB_PARAM_L366_WR_MASK, \
                                    "SBB_PARAM_L366_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H367_OFFSET, \
                                    SBB_PARAM_H367_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H367_RD_MASK, SBB_PARAM_H367_WR_MASK, \
                                    "SBB_PARAM_H367_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L367_OFFSET, \
                                    SBB_PARAM_L367_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L367_RD_MASK, SBB_PARAM_L367_WR_MASK, \
                                    "SBB_PARAM_L367_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H368_OFFSET, \
                                    SBB_PARAM_H368_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H368_RD_MASK, SBB_PARAM_H368_WR_MASK, \
                                    "SBB_PARAM_H368_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L368_OFFSET, \
                                    SBB_PARAM_L368_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L368_RD_MASK, SBB_PARAM_L368_WR_MASK, \
                                    "SBB_PARAM_L368_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H369_OFFSET, \
                                    SBB_PARAM_H369_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H369_RD_MASK, SBB_PARAM_H369_WR_MASK, \
                                    "SBB_PARAM_H369_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L369_OFFSET, \
                                    SBB_PARAM_L369_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L369_RD_MASK, SBB_PARAM_L369_WR_MASK, \
                                    "SBB_PARAM_L369_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H370_OFFSET, \
                                    SBB_PARAM_H370_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H370_RD_MASK, SBB_PARAM_H370_WR_MASK, \
                                    "SBB_PARAM_H370_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L370_OFFSET, \
                                    SBB_PARAM_L370_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L370_RD_MASK, SBB_PARAM_L370_WR_MASK, \
                                    "SBB_PARAM_L370_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H371_OFFSET, \
                                    SBB_PARAM_H371_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H371_RD_MASK, SBB_PARAM_H371_WR_MASK, \
                                    "SBB_PARAM_H371_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L371_OFFSET, \
                                    SBB_PARAM_L371_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L371_RD_MASK, SBB_PARAM_L371_WR_MASK, \
                                    "SBB_PARAM_L371_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H372_OFFSET, \
                                    SBB_PARAM_H372_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H372_RD_MASK, SBB_PARAM_H372_WR_MASK, \
                                    "SBB_PARAM_H372_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L372_OFFSET, \
                                    SBB_PARAM_L372_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L372_RD_MASK, SBB_PARAM_L372_WR_MASK, \
                                    "SBB_PARAM_L372_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H373_OFFSET, \
                                    SBB_PARAM_H373_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H373_RD_MASK, SBB_PARAM_H373_WR_MASK, \
                                    "SBB_PARAM_H373_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L373_OFFSET, \
                                    SBB_PARAM_L373_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L373_RD_MASK, SBB_PARAM_L373_WR_MASK, \
                                    "SBB_PARAM_L373_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H374_OFFSET, \
                                    SBB_PARAM_H374_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H374_RD_MASK, SBB_PARAM_H374_WR_MASK, \
                                    "SBB_PARAM_H374_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L374_OFFSET, \
                                    SBB_PARAM_L374_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L374_RD_MASK, SBB_PARAM_L374_WR_MASK, \
                                    "SBB_PARAM_L374_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H375_OFFSET, \
                                    SBB_PARAM_H375_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H375_RD_MASK, SBB_PARAM_H375_WR_MASK, \
                                    "SBB_PARAM_H375_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L375_OFFSET, \
                                    SBB_PARAM_L375_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L375_RD_MASK, SBB_PARAM_L375_WR_MASK, \
                                    "SBB_PARAM_L375_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H376_OFFSET, \
                                    SBB_PARAM_H376_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H376_RD_MASK, SBB_PARAM_H376_WR_MASK, \
                                    "SBB_PARAM_H376_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L376_OFFSET, \
                                    SBB_PARAM_L376_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L376_RD_MASK, SBB_PARAM_L376_WR_MASK, \
                                    "SBB_PARAM_L376_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H377_OFFSET, \
                                    SBB_PARAM_H377_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H377_RD_MASK, SBB_PARAM_H377_WR_MASK, \
                                    "SBB_PARAM_H377_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L377_OFFSET, \
                                    SBB_PARAM_L377_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L377_RD_MASK, SBB_PARAM_L377_WR_MASK, \
                                    "SBB_PARAM_L377_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H378_OFFSET, \
                                    SBB_PARAM_H378_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H378_RD_MASK, SBB_PARAM_H378_WR_MASK, \
                                    "SBB_PARAM_H378_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L378_OFFSET, \
                                    SBB_PARAM_L378_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L378_RD_MASK, SBB_PARAM_L378_WR_MASK, \
                                    "SBB_PARAM_L378_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H379_OFFSET, \
                                    SBB_PARAM_H379_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H379_RD_MASK, SBB_PARAM_H379_WR_MASK, \
                                    "SBB_PARAM_H379_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L379_OFFSET, \
                                    SBB_PARAM_L379_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L379_RD_MASK, SBB_PARAM_L379_WR_MASK, \
                                    "SBB_PARAM_L379_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H380_OFFSET, \
                                    SBB_PARAM_H380_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H380_RD_MASK, SBB_PARAM_H380_WR_MASK, \
                                    "SBB_PARAM_H380_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L380_OFFSET, \
                                    SBB_PARAM_L380_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L380_RD_MASK, SBB_PARAM_L380_WR_MASK, \
                                    "SBB_PARAM_L380_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H381_OFFSET, \
                                    SBB_PARAM_H381_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H381_RD_MASK, SBB_PARAM_H381_WR_MASK, \
                                    "SBB_PARAM_H381_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L381_OFFSET, \
                                    SBB_PARAM_L381_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L381_RD_MASK, SBB_PARAM_L381_WR_MASK, \
                                    "SBB_PARAM_L381_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H382_OFFSET, \
                                    SBB_PARAM_H382_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H382_RD_MASK, SBB_PARAM_H382_WR_MASK, \
                                    "SBB_PARAM_H382_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L382_OFFSET, \
                                    SBB_PARAM_L382_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L382_RD_MASK, SBB_PARAM_L382_WR_MASK, \
                                    "SBB_PARAM_L382_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H383_OFFSET, \
                                    SBB_PARAM_H383_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H383_RD_MASK, SBB_PARAM_H383_WR_MASK, \
                                    "SBB_PARAM_H383_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L383_OFFSET, \
                                    SBB_PARAM_L383_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L383_RD_MASK, SBB_PARAM_L383_WR_MASK, \
                                    "SBB_PARAM_L383_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H384_OFFSET, \
                                    SBB_PARAM_H384_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H384_RD_MASK, SBB_PARAM_H384_WR_MASK, \
                                    "SBB_PARAM_H384_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L384_OFFSET, \
                                    SBB_PARAM_L384_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L384_RD_MASK, SBB_PARAM_L384_WR_MASK, \
                                    "SBB_PARAM_L384_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H385_OFFSET, \
                                    SBB_PARAM_H385_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H385_RD_MASK, SBB_PARAM_H385_WR_MASK, \
                                    "SBB_PARAM_H385_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L385_OFFSET, \
                                    SBB_PARAM_L385_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L385_RD_MASK, SBB_PARAM_L385_WR_MASK, \
                                    "SBB_PARAM_L385_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H386_OFFSET, \
                                    SBB_PARAM_H386_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H386_RD_MASK, SBB_PARAM_H386_WR_MASK, \
                                    "SBB_PARAM_H386_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L386_OFFSET, \
                                    SBB_PARAM_L386_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L386_RD_MASK, SBB_PARAM_L386_WR_MASK, \
                                    "SBB_PARAM_L386_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H387_OFFSET, \
                                    SBB_PARAM_H387_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H387_RD_MASK, SBB_PARAM_H387_WR_MASK, \
                                    "SBB_PARAM_H387_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L387_OFFSET, \
                                    SBB_PARAM_L387_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L387_RD_MASK, SBB_PARAM_L387_WR_MASK, \
                                    "SBB_PARAM_L387_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H388_OFFSET, \
                                    SBB_PARAM_H388_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H388_RD_MASK, SBB_PARAM_H388_WR_MASK, \
                                    "SBB_PARAM_H388_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L388_OFFSET, \
                                    SBB_PARAM_L388_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L388_RD_MASK, SBB_PARAM_L388_WR_MASK, \
                                    "SBB_PARAM_L388_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H389_OFFSET, \
                                    SBB_PARAM_H389_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H389_RD_MASK, SBB_PARAM_H389_WR_MASK, \
                                    "SBB_PARAM_H389_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L389_OFFSET, \
                                    SBB_PARAM_L389_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L389_RD_MASK, SBB_PARAM_L389_WR_MASK, \
                                    "SBB_PARAM_L389_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H390_OFFSET, \
                                    SBB_PARAM_H390_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H390_RD_MASK, SBB_PARAM_H390_WR_MASK, \
                                    "SBB_PARAM_H390_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L390_OFFSET, \
                                    SBB_PARAM_L390_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L390_RD_MASK, SBB_PARAM_L390_WR_MASK, \
                                    "SBB_PARAM_L390_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H391_OFFSET, \
                                    SBB_PARAM_H391_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H391_RD_MASK, SBB_PARAM_H391_WR_MASK, \
                                    "SBB_PARAM_H391_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L391_OFFSET, \
                                    SBB_PARAM_L391_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L391_RD_MASK, SBB_PARAM_L391_WR_MASK, \
                                    "SBB_PARAM_L391_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H392_OFFSET, \
                                    SBB_PARAM_H392_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H392_RD_MASK, SBB_PARAM_H392_WR_MASK, \
                                    "SBB_PARAM_H392_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L392_OFFSET, \
                                    SBB_PARAM_L392_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L392_RD_MASK, SBB_PARAM_L392_WR_MASK, \
                                    "SBB_PARAM_L392_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H393_OFFSET, \
                                    SBB_PARAM_H393_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H393_RD_MASK, SBB_PARAM_H393_WR_MASK, \
                                    "SBB_PARAM_H393_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L393_OFFSET, \
                                    SBB_PARAM_L393_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L393_RD_MASK, SBB_PARAM_L393_WR_MASK, \
                                    "SBB_PARAM_L393_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H394_OFFSET, \
                                    SBB_PARAM_H394_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H394_RD_MASK, SBB_PARAM_H394_WR_MASK, \
                                    "SBB_PARAM_H394_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L394_OFFSET, \
                                    SBB_PARAM_L394_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L394_RD_MASK, SBB_PARAM_L394_WR_MASK, \
                                    "SBB_PARAM_L394_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H395_OFFSET, \
                                    SBB_PARAM_H395_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H395_RD_MASK, SBB_PARAM_H395_WR_MASK, \
                                    "SBB_PARAM_H395_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L395_OFFSET, \
                                    SBB_PARAM_L395_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L395_RD_MASK, SBB_PARAM_L395_WR_MASK, \
                                    "SBB_PARAM_L395_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H396_OFFSET, \
                                    SBB_PARAM_H396_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H396_RD_MASK, SBB_PARAM_H396_WR_MASK, \
                                    "SBB_PARAM_H396_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L396_OFFSET, \
                                    SBB_PARAM_L396_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L396_RD_MASK, SBB_PARAM_L396_WR_MASK, \
                                    "SBB_PARAM_L396_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H397_OFFSET, \
                                    SBB_PARAM_H397_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H397_RD_MASK, SBB_PARAM_H397_WR_MASK, \
                                    "SBB_PARAM_H397_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L397_OFFSET, \
                                    SBB_PARAM_L397_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L397_RD_MASK, SBB_PARAM_L397_WR_MASK, \
                                    "SBB_PARAM_L397_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H398_OFFSET, \
                                    SBB_PARAM_H398_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H398_RD_MASK, SBB_PARAM_H398_WR_MASK, \
                                    "SBB_PARAM_H398_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L398_OFFSET, \
                                    SBB_PARAM_L398_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L398_RD_MASK, SBB_PARAM_L398_WR_MASK, \
                                    "SBB_PARAM_L398_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H399_OFFSET, \
                                    SBB_PARAM_H399_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H399_RD_MASK, SBB_PARAM_H399_WR_MASK, \
                                    "SBB_PARAM_H399_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L399_OFFSET, \
                                    SBB_PARAM_L399_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L399_RD_MASK, SBB_PARAM_L399_WR_MASK, \
                                    "SBB_PARAM_L399_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H400_OFFSET, \
                                    SBB_PARAM_H400_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H400_RD_MASK, SBB_PARAM_H400_WR_MASK, \
                                    "SBB_PARAM_H400_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L400_OFFSET, \
                                    SBB_PARAM_L400_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L400_RD_MASK, SBB_PARAM_L400_WR_MASK, \
                                    "SBB_PARAM_L400_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H401_OFFSET, \
                                    SBB_PARAM_H401_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H401_RD_MASK, SBB_PARAM_H401_WR_MASK, \
                                    "SBB_PARAM_H401_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L401_OFFSET, \
                                    SBB_PARAM_L401_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L401_RD_MASK, SBB_PARAM_L401_WR_MASK, \
                                    "SBB_PARAM_L401_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H402_OFFSET, \
                                    SBB_PARAM_H402_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H402_RD_MASK, SBB_PARAM_H402_WR_MASK, \
                                    "SBB_PARAM_H402_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L402_OFFSET, \
                                    SBB_PARAM_L402_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L402_RD_MASK, SBB_PARAM_L402_WR_MASK, \
                                    "SBB_PARAM_L402_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H403_OFFSET, \
                                    SBB_PARAM_H403_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H403_RD_MASK, SBB_PARAM_H403_WR_MASK, \
                                    "SBB_PARAM_H403_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L403_OFFSET, \
                                    SBB_PARAM_L403_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L403_RD_MASK, SBB_PARAM_L403_WR_MASK, \
                                    "SBB_PARAM_L403_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H404_OFFSET, \
                                    SBB_PARAM_H404_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H404_RD_MASK, SBB_PARAM_H404_WR_MASK, \
                                    "SBB_PARAM_H404_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L404_OFFSET, \
                                    SBB_PARAM_L404_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L404_RD_MASK, SBB_PARAM_L404_WR_MASK, \
                                    "SBB_PARAM_L404_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H405_OFFSET, \
                                    SBB_PARAM_H405_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H405_RD_MASK, SBB_PARAM_H405_WR_MASK, \
                                    "SBB_PARAM_H405_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L405_OFFSET, \
                                    SBB_PARAM_L405_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L405_RD_MASK, SBB_PARAM_L405_WR_MASK, \
                                    "SBB_PARAM_L405_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H406_OFFSET, \
                                    SBB_PARAM_H406_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H406_RD_MASK, SBB_PARAM_H406_WR_MASK, \
                                    "SBB_PARAM_H406_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L406_OFFSET, \
                                    SBB_PARAM_L406_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L406_RD_MASK, SBB_PARAM_L406_WR_MASK, \
                                    "SBB_PARAM_L406_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H407_OFFSET, \
                                    SBB_PARAM_H407_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H407_RD_MASK, SBB_PARAM_H407_WR_MASK, \
                                    "SBB_PARAM_H407_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L407_OFFSET, \
                                    SBB_PARAM_L407_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L407_RD_MASK, SBB_PARAM_L407_WR_MASK, \
                                    "SBB_PARAM_L407_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H408_OFFSET, \
                                    SBB_PARAM_H408_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H408_RD_MASK, SBB_PARAM_H408_WR_MASK, \
                                    "SBB_PARAM_H408_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L408_OFFSET, \
                                    SBB_PARAM_L408_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L408_RD_MASK, SBB_PARAM_L408_WR_MASK, \
                                    "SBB_PARAM_L408_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H409_OFFSET, \
                                    SBB_PARAM_H409_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H409_RD_MASK, SBB_PARAM_H409_WR_MASK, \
                                    "SBB_PARAM_H409_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L409_OFFSET, \
                                    SBB_PARAM_L409_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L409_RD_MASK, SBB_PARAM_L409_WR_MASK, \
                                    "SBB_PARAM_L409_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H410_OFFSET, \
                                    SBB_PARAM_H410_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H410_RD_MASK, SBB_PARAM_H410_WR_MASK, \
                                    "SBB_PARAM_H410_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L410_OFFSET, \
                                    SBB_PARAM_L410_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L410_RD_MASK, SBB_PARAM_L410_WR_MASK, \
                                    "SBB_PARAM_L410_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H411_OFFSET, \
                                    SBB_PARAM_H411_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H411_RD_MASK, SBB_PARAM_H411_WR_MASK, \
                                    "SBB_PARAM_H411_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L411_OFFSET, \
                                    SBB_PARAM_L411_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L411_RD_MASK, SBB_PARAM_L411_WR_MASK, \
                                    "SBB_PARAM_L411_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H412_OFFSET, \
                                    SBB_PARAM_H412_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H412_RD_MASK, SBB_PARAM_H412_WR_MASK, \
                                    "SBB_PARAM_H412_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L412_OFFSET, \
                                    SBB_PARAM_L412_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L412_RD_MASK, SBB_PARAM_L412_WR_MASK, \
                                    "SBB_PARAM_L412_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H413_OFFSET, \
                                    SBB_PARAM_H413_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H413_RD_MASK, SBB_PARAM_H413_WR_MASK, \
                                    "SBB_PARAM_H413_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L413_OFFSET, \
                                    SBB_PARAM_L413_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L413_RD_MASK, SBB_PARAM_L413_WR_MASK, \
                                    "SBB_PARAM_L413_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H414_OFFSET, \
                                    SBB_PARAM_H414_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H414_RD_MASK, SBB_PARAM_H414_WR_MASK, \
                                    "SBB_PARAM_H414_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L414_OFFSET, \
                                    SBB_PARAM_L414_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L414_RD_MASK, SBB_PARAM_L414_WR_MASK, \
                                    "SBB_PARAM_L414_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H415_OFFSET, \
                                    SBB_PARAM_H415_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H415_RD_MASK, SBB_PARAM_H415_WR_MASK, \
                                    "SBB_PARAM_H415_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L415_OFFSET, \
                                    SBB_PARAM_L415_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L415_RD_MASK, SBB_PARAM_L415_WR_MASK, \
                                    "SBB_PARAM_L415_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H416_OFFSET, \
                                    SBB_PARAM_H416_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H416_RD_MASK, SBB_PARAM_H416_WR_MASK, \
                                    "SBB_PARAM_H416_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L416_OFFSET, \
                                    SBB_PARAM_L416_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L416_RD_MASK, SBB_PARAM_L416_WR_MASK, \
                                    "SBB_PARAM_L416_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H417_OFFSET, \
                                    SBB_PARAM_H417_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H417_RD_MASK, SBB_PARAM_H417_WR_MASK, \
                                    "SBB_PARAM_H417_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L417_OFFSET, \
                                    SBB_PARAM_L417_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L417_RD_MASK, SBB_PARAM_L417_WR_MASK, \
                                    "SBB_PARAM_L417_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H418_OFFSET, \
                                    SBB_PARAM_H418_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H418_RD_MASK, SBB_PARAM_H418_WR_MASK, \
                                    "SBB_PARAM_H418_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L418_OFFSET, \
                                    SBB_PARAM_L418_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L418_RD_MASK, SBB_PARAM_L418_WR_MASK, \
                                    "SBB_PARAM_L418_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H419_OFFSET, \
                                    SBB_PARAM_H419_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H419_RD_MASK, SBB_PARAM_H419_WR_MASK, \
                                    "SBB_PARAM_H419_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L419_OFFSET, \
                                    SBB_PARAM_L419_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L419_RD_MASK, SBB_PARAM_L419_WR_MASK, \
                                    "SBB_PARAM_L419_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H420_OFFSET, \
                                    SBB_PARAM_H420_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H420_RD_MASK, SBB_PARAM_H420_WR_MASK, \
                                    "SBB_PARAM_H420_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L420_OFFSET, \
                                    SBB_PARAM_L420_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L420_RD_MASK, SBB_PARAM_L420_WR_MASK, \
                                    "SBB_PARAM_L420_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H421_OFFSET, \
                                    SBB_PARAM_H421_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H421_RD_MASK, SBB_PARAM_H421_WR_MASK, \
                                    "SBB_PARAM_H421_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L421_OFFSET, \
                                    SBB_PARAM_L421_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L421_RD_MASK, SBB_PARAM_L421_WR_MASK, \
                                    "SBB_PARAM_L421_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H422_OFFSET, \
                                    SBB_PARAM_H422_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H422_RD_MASK, SBB_PARAM_H422_WR_MASK, \
                                    "SBB_PARAM_H422_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L422_OFFSET, \
                                    SBB_PARAM_L422_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L422_RD_MASK, SBB_PARAM_L422_WR_MASK, \
                                    "SBB_PARAM_L422_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H423_OFFSET, \
                                    SBB_PARAM_H423_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H423_RD_MASK, SBB_PARAM_H423_WR_MASK, \
                                    "SBB_PARAM_H423_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L423_OFFSET, \
                                    SBB_PARAM_L423_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L423_RD_MASK, SBB_PARAM_L423_WR_MASK, \
                                    "SBB_PARAM_L423_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H424_OFFSET, \
                                    SBB_PARAM_H424_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H424_RD_MASK, SBB_PARAM_H424_WR_MASK, \
                                    "SBB_PARAM_H424_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L424_OFFSET, \
                                    SBB_PARAM_L424_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L424_RD_MASK, SBB_PARAM_L424_WR_MASK, \
                                    "SBB_PARAM_L424_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H425_OFFSET, \
                                    SBB_PARAM_H425_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H425_RD_MASK, SBB_PARAM_H425_WR_MASK, \
                                    "SBB_PARAM_H425_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L425_OFFSET, \
                                    SBB_PARAM_L425_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L425_RD_MASK, SBB_PARAM_L425_WR_MASK, \
                                    "SBB_PARAM_L425_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H426_OFFSET, \
                                    SBB_PARAM_H426_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H426_RD_MASK, SBB_PARAM_H426_WR_MASK, \
                                    "SBB_PARAM_H426_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L426_OFFSET, \
                                    SBB_PARAM_L426_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L426_RD_MASK, SBB_PARAM_L426_WR_MASK, \
                                    "SBB_PARAM_L426_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H427_OFFSET, \
                                    SBB_PARAM_H427_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H427_RD_MASK, SBB_PARAM_H427_WR_MASK, \
                                    "SBB_PARAM_H427_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L427_OFFSET, \
                                    SBB_PARAM_L427_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L427_RD_MASK, SBB_PARAM_L427_WR_MASK, \
                                    "SBB_PARAM_L427_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H428_OFFSET, \
                                    SBB_PARAM_H428_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H428_RD_MASK, SBB_PARAM_H428_WR_MASK, \
                                    "SBB_PARAM_H428_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L428_OFFSET, \
                                    SBB_PARAM_L428_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L428_RD_MASK, SBB_PARAM_L428_WR_MASK, \
                                    "SBB_PARAM_L428_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H429_OFFSET, \
                                    SBB_PARAM_H429_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H429_RD_MASK, SBB_PARAM_H429_WR_MASK, \
                                    "SBB_PARAM_H429_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L429_OFFSET, \
                                    SBB_PARAM_L429_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L429_RD_MASK, SBB_PARAM_L429_WR_MASK, \
                                    "SBB_PARAM_L429_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H430_OFFSET, \
                                    SBB_PARAM_H430_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H430_RD_MASK, SBB_PARAM_H430_WR_MASK, \
                                    "SBB_PARAM_H430_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L430_OFFSET, \
                                    SBB_PARAM_L430_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L430_RD_MASK, SBB_PARAM_L430_WR_MASK, \
                                    "SBB_PARAM_L430_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H431_OFFSET, \
                                    SBB_PARAM_H431_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H431_RD_MASK, SBB_PARAM_H431_WR_MASK, \
                                    "SBB_PARAM_H431_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L431_OFFSET, \
                                    SBB_PARAM_L431_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L431_RD_MASK, SBB_PARAM_L431_WR_MASK, \
                                    "SBB_PARAM_L431_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H432_OFFSET, \
                                    SBB_PARAM_H432_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H432_RD_MASK, SBB_PARAM_H432_WR_MASK, \
                                    "SBB_PARAM_H432_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L432_OFFSET, \
                                    SBB_PARAM_L432_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L432_RD_MASK, SBB_PARAM_L432_WR_MASK, \
                                    "SBB_PARAM_L432_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H433_OFFSET, \
                                    SBB_PARAM_H433_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H433_RD_MASK, SBB_PARAM_H433_WR_MASK, \
                                    "SBB_PARAM_H433_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L433_OFFSET, \
                                    SBB_PARAM_L433_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L433_RD_MASK, SBB_PARAM_L433_WR_MASK, \
                                    "SBB_PARAM_L433_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H434_OFFSET, \
                                    SBB_PARAM_H434_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H434_RD_MASK, SBB_PARAM_H434_WR_MASK, \
                                    "SBB_PARAM_H434_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L434_OFFSET, \
                                    SBB_PARAM_L434_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L434_RD_MASK, SBB_PARAM_L434_WR_MASK, \
                                    "SBB_PARAM_L434_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H435_OFFSET, \
                                    SBB_PARAM_H435_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H435_RD_MASK, SBB_PARAM_H435_WR_MASK, \
                                    "SBB_PARAM_H435_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L435_OFFSET, \
                                    SBB_PARAM_L435_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L435_RD_MASK, SBB_PARAM_L435_WR_MASK, \
                                    "SBB_PARAM_L435_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H436_OFFSET, \
                                    SBB_PARAM_H436_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H436_RD_MASK, SBB_PARAM_H436_WR_MASK, \
                                    "SBB_PARAM_H436_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L436_OFFSET, \
                                    SBB_PARAM_L436_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L436_RD_MASK, SBB_PARAM_L436_WR_MASK, \
                                    "SBB_PARAM_L436_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H437_OFFSET, \
                                    SBB_PARAM_H437_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H437_RD_MASK, SBB_PARAM_H437_WR_MASK, \
                                    "SBB_PARAM_H437_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L437_OFFSET, \
                                    SBB_PARAM_L437_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L437_RD_MASK, SBB_PARAM_L437_WR_MASK, \
                                    "SBB_PARAM_L437_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H438_OFFSET, \
                                    SBB_PARAM_H438_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H438_RD_MASK, SBB_PARAM_H438_WR_MASK, \
                                    "SBB_PARAM_H438_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L438_OFFSET, \
                                    SBB_PARAM_L438_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L438_RD_MASK, SBB_PARAM_L438_WR_MASK, \
                                    "SBB_PARAM_L438_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H439_OFFSET, \
                                    SBB_PARAM_H439_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H439_RD_MASK, SBB_PARAM_H439_WR_MASK, \
                                    "SBB_PARAM_H439_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L439_OFFSET, \
                                    SBB_PARAM_L439_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L439_RD_MASK, SBB_PARAM_L439_WR_MASK, \
                                    "SBB_PARAM_L439_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H440_OFFSET, \
                                    SBB_PARAM_H440_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H440_RD_MASK, SBB_PARAM_H440_WR_MASK, \
                                    "SBB_PARAM_H440_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L440_OFFSET, \
                                    SBB_PARAM_L440_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L440_RD_MASK, SBB_PARAM_L440_WR_MASK, \
                                    "SBB_PARAM_L440_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H441_OFFSET, \
                                    SBB_PARAM_H441_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H441_RD_MASK, SBB_PARAM_H441_WR_MASK, \
                                    "SBB_PARAM_H441_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L441_OFFSET, \
                                    SBB_PARAM_L441_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L441_RD_MASK, SBB_PARAM_L441_WR_MASK, \
                                    "SBB_PARAM_L441_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H442_OFFSET, \
                                    SBB_PARAM_H442_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H442_RD_MASK, SBB_PARAM_H442_WR_MASK, \
                                    "SBB_PARAM_H442_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L442_OFFSET, \
                                    SBB_PARAM_L442_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L442_RD_MASK, SBB_PARAM_L442_WR_MASK, \
                                    "SBB_PARAM_L442_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H443_OFFSET, \
                                    SBB_PARAM_H443_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H443_RD_MASK, SBB_PARAM_H443_WR_MASK, \
                                    "SBB_PARAM_H443_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L443_OFFSET, \
                                    SBB_PARAM_L443_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L443_RD_MASK, SBB_PARAM_L443_WR_MASK, \
                                    "SBB_PARAM_L443_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H444_OFFSET, \
                                    SBB_PARAM_H444_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H444_RD_MASK, SBB_PARAM_H444_WR_MASK, \
                                    "SBB_PARAM_H444_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L444_OFFSET, \
                                    SBB_PARAM_L444_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L444_RD_MASK, SBB_PARAM_L444_WR_MASK, \
                                    "SBB_PARAM_L444_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H445_OFFSET, \
                                    SBB_PARAM_H445_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H445_RD_MASK, SBB_PARAM_H445_WR_MASK, \
                                    "SBB_PARAM_H445_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L445_OFFSET, \
                                    SBB_PARAM_L445_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L445_RD_MASK, SBB_PARAM_L445_WR_MASK, \
                                    "SBB_PARAM_L445_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H446_OFFSET, \
                                    SBB_PARAM_H446_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H446_RD_MASK, SBB_PARAM_H446_WR_MASK, \
                                    "SBB_PARAM_H446_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L446_OFFSET, \
                                    SBB_PARAM_L446_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L446_RD_MASK, SBB_PARAM_L446_WR_MASK, \
                                    "SBB_PARAM_L446_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H447_OFFSET, \
                                    SBB_PARAM_H447_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H447_RD_MASK, SBB_PARAM_H447_WR_MASK, \
                                    "SBB_PARAM_H447_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L447_OFFSET, \
                                    SBB_PARAM_L447_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L447_RD_MASK, SBB_PARAM_L447_WR_MASK, \
                                    "SBB_PARAM_L447_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H448_OFFSET, \
                                    SBB_PARAM_H448_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H448_RD_MASK, SBB_PARAM_H448_WR_MASK, \
                                    "SBB_PARAM_H448_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L448_OFFSET, \
                                    SBB_PARAM_L448_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L448_RD_MASK, SBB_PARAM_L448_WR_MASK, \
                                    "SBB_PARAM_L448_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H449_OFFSET, \
                                    SBB_PARAM_H449_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H449_RD_MASK, SBB_PARAM_H449_WR_MASK, \
                                    "SBB_PARAM_H449_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L449_OFFSET, \
                                    SBB_PARAM_L449_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L449_RD_MASK, SBB_PARAM_L449_WR_MASK, \
                                    "SBB_PARAM_L449_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H450_OFFSET, \
                                    SBB_PARAM_H450_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H450_RD_MASK, SBB_PARAM_H450_WR_MASK, \
                                    "SBB_PARAM_H450_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L450_OFFSET, \
                                    SBB_PARAM_L450_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L450_RD_MASK, SBB_PARAM_L450_WR_MASK, \
                                    "SBB_PARAM_L450_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H451_OFFSET, \
                                    SBB_PARAM_H451_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H451_RD_MASK, SBB_PARAM_H451_WR_MASK, \
                                    "SBB_PARAM_H451_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L451_OFFSET, \
                                    SBB_PARAM_L451_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L451_RD_MASK, SBB_PARAM_L451_WR_MASK, \
                                    "SBB_PARAM_L451_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H452_OFFSET, \
                                    SBB_PARAM_H452_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H452_RD_MASK, SBB_PARAM_H452_WR_MASK, \
                                    "SBB_PARAM_H452_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L452_OFFSET, \
                                    SBB_PARAM_L452_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L452_RD_MASK, SBB_PARAM_L452_WR_MASK, \
                                    "SBB_PARAM_L452_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H453_OFFSET, \
                                    SBB_PARAM_H453_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H453_RD_MASK, SBB_PARAM_H453_WR_MASK, \
                                    "SBB_PARAM_H453_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L453_OFFSET, \
                                    SBB_PARAM_L453_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L453_RD_MASK, SBB_PARAM_L453_WR_MASK, \
                                    "SBB_PARAM_L453_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H454_OFFSET, \
                                    SBB_PARAM_H454_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H454_RD_MASK, SBB_PARAM_H454_WR_MASK, \
                                    "SBB_PARAM_H454_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L454_OFFSET, \
                                    SBB_PARAM_L454_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L454_RD_MASK, SBB_PARAM_L454_WR_MASK, \
                                    "SBB_PARAM_L454_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H455_OFFSET, \
                                    SBB_PARAM_H455_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H455_RD_MASK, SBB_PARAM_H455_WR_MASK, \
                                    "SBB_PARAM_H455_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L455_OFFSET, \
                                    SBB_PARAM_L455_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L455_RD_MASK, SBB_PARAM_L455_WR_MASK, \
                                    "SBB_PARAM_L455_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H456_OFFSET, \
                                    SBB_PARAM_H456_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H456_RD_MASK, SBB_PARAM_H456_WR_MASK, \
                                    "SBB_PARAM_H456_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L456_OFFSET, \
                                    SBB_PARAM_L456_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L456_RD_MASK, SBB_PARAM_L456_WR_MASK, \
                                    "SBB_PARAM_L456_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H457_OFFSET, \
                                    SBB_PARAM_H457_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H457_RD_MASK, SBB_PARAM_H457_WR_MASK, \
                                    "SBB_PARAM_H457_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L457_OFFSET, \
                                    SBB_PARAM_L457_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L457_RD_MASK, SBB_PARAM_L457_WR_MASK, \
                                    "SBB_PARAM_L457_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H458_OFFSET, \
                                    SBB_PARAM_H458_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H458_RD_MASK, SBB_PARAM_H458_WR_MASK, \
                                    "SBB_PARAM_H458_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L458_OFFSET, \
                                    SBB_PARAM_L458_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L458_RD_MASK, SBB_PARAM_L458_WR_MASK, \
                                    "SBB_PARAM_L458_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H459_OFFSET, \
                                    SBB_PARAM_H459_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H459_RD_MASK, SBB_PARAM_H459_WR_MASK, \
                                    "SBB_PARAM_H459_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L459_OFFSET, \
                                    SBB_PARAM_L459_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L459_RD_MASK, SBB_PARAM_L459_WR_MASK, \
                                    "SBB_PARAM_L459_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H460_OFFSET, \
                                    SBB_PARAM_H460_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H460_RD_MASK, SBB_PARAM_H460_WR_MASK, \
                                    "SBB_PARAM_H460_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L460_OFFSET, \
                                    SBB_PARAM_L460_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L460_RD_MASK, SBB_PARAM_L460_WR_MASK, \
                                    "SBB_PARAM_L460_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H461_OFFSET, \
                                    SBB_PARAM_H461_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H461_RD_MASK, SBB_PARAM_H461_WR_MASK, \
                                    "SBB_PARAM_H461_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L461_OFFSET, \
                                    SBB_PARAM_L461_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L461_RD_MASK, SBB_PARAM_L461_WR_MASK, \
                                    "SBB_PARAM_L461_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H462_OFFSET, \
                                    SBB_PARAM_H462_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H462_RD_MASK, SBB_PARAM_H462_WR_MASK, \
                                    "SBB_PARAM_H462_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L462_OFFSET, \
                                    SBB_PARAM_L462_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L462_RD_MASK, SBB_PARAM_L462_WR_MASK, \
                                    "SBB_PARAM_L462_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H463_OFFSET, \
                                    SBB_PARAM_H463_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H463_RD_MASK, SBB_PARAM_H463_WR_MASK, \
                                    "SBB_PARAM_H463_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L463_OFFSET, \
                                    SBB_PARAM_L463_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L463_RD_MASK, SBB_PARAM_L463_WR_MASK, \
                                    "SBB_PARAM_L463_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H464_OFFSET, \
                                    SBB_PARAM_H464_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H464_RD_MASK, SBB_PARAM_H464_WR_MASK, \
                                    "SBB_PARAM_H464_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L464_OFFSET, \
                                    SBB_PARAM_L464_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L464_RD_MASK, SBB_PARAM_L464_WR_MASK, \
                                    "SBB_PARAM_L464_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H465_OFFSET, \
                                    SBB_PARAM_H465_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H465_RD_MASK, SBB_PARAM_H465_WR_MASK, \
                                    "SBB_PARAM_H465_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L465_OFFSET, \
                                    SBB_PARAM_L465_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L465_RD_MASK, SBB_PARAM_L465_WR_MASK, \
                                    "SBB_PARAM_L465_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H466_OFFSET, \
                                    SBB_PARAM_H466_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H466_RD_MASK, SBB_PARAM_H466_WR_MASK, \
                                    "SBB_PARAM_H466_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L466_OFFSET, \
                                    SBB_PARAM_L466_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L466_RD_MASK, SBB_PARAM_L466_WR_MASK, \
                                    "SBB_PARAM_L466_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H467_OFFSET, \
                                    SBB_PARAM_H467_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H467_RD_MASK, SBB_PARAM_H467_WR_MASK, \
                                    "SBB_PARAM_H467_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L467_OFFSET, \
                                    SBB_PARAM_L467_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L467_RD_MASK, SBB_PARAM_L467_WR_MASK, \
                                    "SBB_PARAM_L467_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H468_OFFSET, \
                                    SBB_PARAM_H468_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H468_RD_MASK, SBB_PARAM_H468_WR_MASK, \
                                    "SBB_PARAM_H468_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L468_OFFSET, \
                                    SBB_PARAM_L468_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L468_RD_MASK, SBB_PARAM_L468_WR_MASK, \
                                    "SBB_PARAM_L468_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H469_OFFSET, \
                                    SBB_PARAM_H469_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H469_RD_MASK, SBB_PARAM_H469_WR_MASK, \
                                    "SBB_PARAM_H469_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L469_OFFSET, \
                                    SBB_PARAM_L469_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L469_RD_MASK, SBB_PARAM_L469_WR_MASK, \
                                    "SBB_PARAM_L469_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H470_OFFSET, \
                                    SBB_PARAM_H470_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H470_RD_MASK, SBB_PARAM_H470_WR_MASK, \
                                    "SBB_PARAM_H470_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L470_OFFSET, \
                                    SBB_PARAM_L470_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L470_RD_MASK, SBB_PARAM_L470_WR_MASK, \
                                    "SBB_PARAM_L470_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H471_OFFSET, \
                                    SBB_PARAM_H471_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H471_RD_MASK, SBB_PARAM_H471_WR_MASK, \
                                    "SBB_PARAM_H471_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L471_OFFSET, \
                                    SBB_PARAM_L471_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L471_RD_MASK, SBB_PARAM_L471_WR_MASK, \
                                    "SBB_PARAM_L471_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H472_OFFSET, \
                                    SBB_PARAM_H472_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H472_RD_MASK, SBB_PARAM_H472_WR_MASK, \
                                    "SBB_PARAM_H472_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L472_OFFSET, \
                                    SBB_PARAM_L472_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L472_RD_MASK, SBB_PARAM_L472_WR_MASK, \
                                    "SBB_PARAM_L472_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H473_OFFSET, \
                                    SBB_PARAM_H473_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H473_RD_MASK, SBB_PARAM_H473_WR_MASK, \
                                    "SBB_PARAM_H473_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L473_OFFSET, \
                                    SBB_PARAM_L473_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L473_RD_MASK, SBB_PARAM_L473_WR_MASK, \
                                    "SBB_PARAM_L473_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H474_OFFSET, \
                                    SBB_PARAM_H474_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H474_RD_MASK, SBB_PARAM_H474_WR_MASK, \
                                    "SBB_PARAM_H474_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L474_OFFSET, \
                                    SBB_PARAM_L474_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L474_RD_MASK, SBB_PARAM_L474_WR_MASK, \
                                    "SBB_PARAM_L474_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H475_OFFSET, \
                                    SBB_PARAM_H475_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H475_RD_MASK, SBB_PARAM_H475_WR_MASK, \
                                    "SBB_PARAM_H475_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L475_OFFSET, \
                                    SBB_PARAM_L475_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L475_RD_MASK, SBB_PARAM_L475_WR_MASK, \
                                    "SBB_PARAM_L475_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H476_OFFSET, \
                                    SBB_PARAM_H476_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H476_RD_MASK, SBB_PARAM_H476_WR_MASK, \
                                    "SBB_PARAM_H476_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L476_OFFSET, \
                                    SBB_PARAM_L476_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L476_RD_MASK, SBB_PARAM_L476_WR_MASK, \
                                    "SBB_PARAM_L476_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H477_OFFSET, \
                                    SBB_PARAM_H477_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H477_RD_MASK, SBB_PARAM_H477_WR_MASK, \
                                    "SBB_PARAM_H477_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L477_OFFSET, \
                                    SBB_PARAM_L477_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L477_RD_MASK, SBB_PARAM_L477_WR_MASK, \
                                    "SBB_PARAM_L477_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H478_OFFSET, \
                                    SBB_PARAM_H478_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H478_RD_MASK, SBB_PARAM_H478_WR_MASK, \
                                    "SBB_PARAM_H478_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L478_OFFSET, \
                                    SBB_PARAM_L478_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L478_RD_MASK, SBB_PARAM_L478_WR_MASK, \
                                    "SBB_PARAM_L478_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H479_OFFSET, \
                                    SBB_PARAM_H479_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H479_RD_MASK, SBB_PARAM_H479_WR_MASK, \
                                    "SBB_PARAM_H479_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L479_OFFSET, \
                                    SBB_PARAM_L479_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L479_RD_MASK, SBB_PARAM_L479_WR_MASK, \
                                    "SBB_PARAM_L479_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H480_OFFSET, \
                                    SBB_PARAM_H480_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H480_RD_MASK, SBB_PARAM_H480_WR_MASK, \
                                    "SBB_PARAM_H480_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L480_OFFSET, \
                                    SBB_PARAM_L480_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L480_RD_MASK, SBB_PARAM_L480_WR_MASK, \
                                    "SBB_PARAM_L480_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H481_OFFSET, \
                                    SBB_PARAM_H481_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H481_RD_MASK, SBB_PARAM_H481_WR_MASK, \
                                    "SBB_PARAM_H481_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L481_OFFSET, \
                                    SBB_PARAM_L481_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L481_RD_MASK, SBB_PARAM_L481_WR_MASK, \
                                    "SBB_PARAM_L481_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H482_OFFSET, \
                                    SBB_PARAM_H482_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H482_RD_MASK, SBB_PARAM_H482_WR_MASK, \
                                    "SBB_PARAM_H482_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L482_OFFSET, \
                                    SBB_PARAM_L482_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L482_RD_MASK, SBB_PARAM_L482_WR_MASK, \
                                    "SBB_PARAM_L482_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H483_OFFSET, \
                                    SBB_PARAM_H483_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H483_RD_MASK, SBB_PARAM_H483_WR_MASK, \
                                    "SBB_PARAM_H483_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L483_OFFSET, \
                                    SBB_PARAM_L483_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L483_RD_MASK, SBB_PARAM_L483_WR_MASK, \
                                    "SBB_PARAM_L483_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H484_OFFSET, \
                                    SBB_PARAM_H484_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H484_RD_MASK, SBB_PARAM_H484_WR_MASK, \
                                    "SBB_PARAM_H484_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L484_OFFSET, \
                                    SBB_PARAM_L484_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L484_RD_MASK, SBB_PARAM_L484_WR_MASK, \
                                    "SBB_PARAM_L484_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H485_OFFSET, \
                                    SBB_PARAM_H485_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H485_RD_MASK, SBB_PARAM_H485_WR_MASK, \
                                    "SBB_PARAM_H485_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L485_OFFSET, \
                                    SBB_PARAM_L485_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L485_RD_MASK, SBB_PARAM_L485_WR_MASK, \
                                    "SBB_PARAM_L485_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H486_OFFSET, \
                                    SBB_PARAM_H486_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H486_RD_MASK, SBB_PARAM_H486_WR_MASK, \
                                    "SBB_PARAM_H486_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L486_OFFSET, \
                                    SBB_PARAM_L486_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L486_RD_MASK, SBB_PARAM_L486_WR_MASK, \
                                    "SBB_PARAM_L486_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H487_OFFSET, \
                                    SBB_PARAM_H487_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H487_RD_MASK, SBB_PARAM_H487_WR_MASK, \
                                    "SBB_PARAM_H487_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L487_OFFSET, \
                                    SBB_PARAM_L487_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L487_RD_MASK, SBB_PARAM_L487_WR_MASK, \
                                    "SBB_PARAM_L487_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H488_OFFSET, \
                                    SBB_PARAM_H488_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H488_RD_MASK, SBB_PARAM_H488_WR_MASK, \
                                    "SBB_PARAM_H488_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L488_OFFSET, \
                                    SBB_PARAM_L488_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L488_RD_MASK, SBB_PARAM_L488_WR_MASK, \
                                    "SBB_PARAM_L488_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H489_OFFSET, \
                                    SBB_PARAM_H489_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H489_RD_MASK, SBB_PARAM_H489_WR_MASK, \
                                    "SBB_PARAM_H489_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L489_OFFSET, \
                                    SBB_PARAM_L489_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L489_RD_MASK, SBB_PARAM_L489_WR_MASK, \
                                    "SBB_PARAM_L489_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H490_OFFSET, \
                                    SBB_PARAM_H490_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H490_RD_MASK, SBB_PARAM_H490_WR_MASK, \
                                    "SBB_PARAM_H490_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L490_OFFSET, \
                                    SBB_PARAM_L490_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L490_RD_MASK, SBB_PARAM_L490_WR_MASK, \
                                    "SBB_PARAM_L490_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H491_OFFSET, \
                                    SBB_PARAM_H491_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H491_RD_MASK, SBB_PARAM_H491_WR_MASK, \
                                    "SBB_PARAM_H491_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L491_OFFSET, \
                                    SBB_PARAM_L491_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L491_RD_MASK, SBB_PARAM_L491_WR_MASK, \
                                    "SBB_PARAM_L491_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H492_OFFSET, \
                                    SBB_PARAM_H492_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H492_RD_MASK, SBB_PARAM_H492_WR_MASK, \
                                    "SBB_PARAM_H492_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L492_OFFSET, \
                                    SBB_PARAM_L492_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L492_RD_MASK, SBB_PARAM_L492_WR_MASK, \
                                    "SBB_PARAM_L492_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H493_OFFSET, \
                                    SBB_PARAM_H493_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H493_RD_MASK, SBB_PARAM_H493_WR_MASK, \
                                    "SBB_PARAM_H493_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L493_OFFSET, \
                                    SBB_PARAM_L493_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L493_RD_MASK, SBB_PARAM_L493_WR_MASK, \
                                    "SBB_PARAM_L493_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H494_OFFSET, \
                                    SBB_PARAM_H494_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H494_RD_MASK, SBB_PARAM_H494_WR_MASK, \
                                    "SBB_PARAM_H494_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L494_OFFSET, \
                                    SBB_PARAM_L494_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L494_RD_MASK, SBB_PARAM_L494_WR_MASK, \
                                    "SBB_PARAM_L494_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H495_OFFSET, \
                                    SBB_PARAM_H495_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H495_RD_MASK, SBB_PARAM_H495_WR_MASK, \
                                    "SBB_PARAM_H495_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L495_OFFSET, \
                                    SBB_PARAM_L495_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L495_RD_MASK, SBB_PARAM_L495_WR_MASK, \
                                    "SBB_PARAM_L495_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H496_OFFSET, \
                                    SBB_PARAM_H496_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H496_RD_MASK, SBB_PARAM_H496_WR_MASK, \
                                    "SBB_PARAM_H496_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L496_OFFSET, \
                                    SBB_PARAM_L496_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L496_RD_MASK, SBB_PARAM_L496_WR_MASK, \
                                    "SBB_PARAM_L496_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H497_OFFSET, \
                                    SBB_PARAM_H497_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H497_RD_MASK, SBB_PARAM_H497_WR_MASK, \
                                    "SBB_PARAM_H497_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L497_OFFSET, \
                                    SBB_PARAM_L497_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L497_RD_MASK, SBB_PARAM_L497_WR_MASK, \
                                    "SBB_PARAM_L497_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H498_OFFSET, \
                                    SBB_PARAM_H498_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H498_RD_MASK, SBB_PARAM_H498_WR_MASK, \
                                    "SBB_PARAM_H498_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L498_OFFSET, \
                                    SBB_PARAM_L498_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L498_RD_MASK, SBB_PARAM_L498_WR_MASK, \
                                    "SBB_PARAM_L498_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H499_OFFSET, \
                                    SBB_PARAM_H499_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H499_RD_MASK, SBB_PARAM_H499_WR_MASK, \
                                    "SBB_PARAM_H499_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L499_OFFSET, \
                                    SBB_PARAM_L499_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L499_RD_MASK, SBB_PARAM_L499_WR_MASK, \
                                    "SBB_PARAM_L499_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H500_OFFSET, \
                                    SBB_PARAM_H500_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H500_RD_MASK, SBB_PARAM_H500_WR_MASK, \
                                    "SBB_PARAM_H500_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L500_OFFSET, \
                                    SBB_PARAM_L500_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L500_RD_MASK, SBB_PARAM_L500_WR_MASK, \
                                    "SBB_PARAM_L500_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H501_OFFSET, \
                                    SBB_PARAM_H501_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H501_RD_MASK, SBB_PARAM_H501_WR_MASK, \
                                    "SBB_PARAM_H501_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L501_OFFSET, \
                                    SBB_PARAM_L501_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L501_RD_MASK, SBB_PARAM_L501_WR_MASK, \
                                    "SBB_PARAM_L501_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H502_OFFSET, \
                                    SBB_PARAM_H502_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H502_RD_MASK, SBB_PARAM_H502_WR_MASK, \
                                    "SBB_PARAM_H502_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L502_OFFSET, \
                                    SBB_PARAM_L502_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L502_RD_MASK, SBB_PARAM_L502_WR_MASK, \
                                    "SBB_PARAM_L502_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H503_OFFSET, \
                                    SBB_PARAM_H503_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H503_RD_MASK, SBB_PARAM_H503_WR_MASK, \
                                    "SBB_PARAM_H503_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L503_OFFSET, \
                                    SBB_PARAM_L503_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L503_RD_MASK, SBB_PARAM_L503_WR_MASK, \
                                    "SBB_PARAM_L503_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H504_OFFSET, \
                                    SBB_PARAM_H504_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H504_RD_MASK, SBB_PARAM_H504_WR_MASK, \
                                    "SBB_PARAM_H504_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L504_OFFSET, \
                                    SBB_PARAM_L504_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L504_RD_MASK, SBB_PARAM_L504_WR_MASK, \
                                    "SBB_PARAM_L504_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H505_OFFSET, \
                                    SBB_PARAM_H505_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H505_RD_MASK, SBB_PARAM_H505_WR_MASK, \
                                    "SBB_PARAM_H505_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L505_OFFSET, \
                                    SBB_PARAM_L505_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L505_RD_MASK, SBB_PARAM_L505_WR_MASK, \
                                    "SBB_PARAM_L505_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H506_OFFSET, \
                                    SBB_PARAM_H506_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H506_RD_MASK, SBB_PARAM_H506_WR_MASK, \
                                    "SBB_PARAM_H506_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L506_OFFSET, \
                                    SBB_PARAM_L506_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L506_RD_MASK, SBB_PARAM_L506_WR_MASK, \
                                    "SBB_PARAM_L506_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H507_OFFSET, \
                                    SBB_PARAM_H507_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H507_RD_MASK, SBB_PARAM_H507_WR_MASK, \
                                    "SBB_PARAM_H507_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L507_OFFSET, \
                                    SBB_PARAM_L507_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L507_RD_MASK, SBB_PARAM_L507_WR_MASK, \
                                    "SBB_PARAM_L507_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H508_OFFSET, \
                                    SBB_PARAM_H508_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H508_RD_MASK, SBB_PARAM_H508_WR_MASK, \
                                    "SBB_PARAM_H508_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L508_OFFSET, \
                                    SBB_PARAM_L508_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L508_RD_MASK, SBB_PARAM_L508_WR_MASK, \
                                    "SBB_PARAM_L508_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H509_OFFSET, \
                                    SBB_PARAM_H509_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H509_RD_MASK, SBB_PARAM_H509_WR_MASK, \
                                    "SBB_PARAM_H509_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L509_OFFSET, \
                                    SBB_PARAM_L509_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L509_RD_MASK, SBB_PARAM_L509_WR_MASK, \
                                    "SBB_PARAM_L509_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H510_OFFSET, \
                                    SBB_PARAM_H510_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H510_RD_MASK, SBB_PARAM_H510_WR_MASK, \
                                    "SBB_PARAM_H510_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L510_OFFSET, \
                                    SBB_PARAM_L510_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L510_RD_MASK, SBB_PARAM_L510_WR_MASK, \
                                    "SBB_PARAM_L510_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_H511_OFFSET, \
                                    SBB_PARAM_H511_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_H511_RD_MASK, SBB_PARAM_H511_WR_MASK, \
                                    "SBB_PARAM_H511_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PARAM_L511_OFFSET, \
                                    SBB_PARAM_L511_DEFAULT, write_data, expected_data, \
                                    SBB_PARAM_L511_RD_MASK, SBB_PARAM_L511_WR_MASK, \
                                    "SBB_PARAM_L511_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_DBG_STAT_OFFSET, \
                                    SBB_DBG_STAT_DEFAULT, write_data, expected_data, \
                                    SBB_DBG_STAT_RD_MASK, SBB_DBG_STAT_WR_MASK, \
                                    "SBB_DBG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_INVLD_INST_ADDR_OFFSET, \
                                    SBB_INVLD_INST_ADDR_DEFAULT, write_data, expected_data, \
                                    SBB_INVLD_INST_ADDR_RD_MASK, SBB_INVLD_INST_ADDR_WR_MASK, \
                                    "SBB_INVLD_INST_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_PC_DATA_ADDR_OFFSET, \
                                    SBB_PC_DATA_ADDR_DEFAULT, write_data, expected_data, \
                                    SBB_PC_DATA_ADDR_RD_MASK, SBB_PC_DATA_ADDR_WR_MASK, \
                                    "SBB_PC_DATA_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_DEC_STG_PC_OFFSET, \
                                    SBB_DEC_STG_PC_DEFAULT, write_data, expected_data, \
                                    SBB_DEC_STG_PC_RD_MASK, SBB_DEC_STG_PC_WR_MASK, \
                                    "SBB_DEC_STG_PC_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_DEC_STG_OPCODE_OFFSET, \
                                    SBB_DEC_STG_OPCODE_DEFAULT, write_data, expected_data, \
                                    SBB_DEC_STG_OPCODE_RD_MASK, SBB_DEC_STG_OPCODE_WR_MASK, \
                                    "SBB_DEC_STG_OPCODE_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_ISS_STG_PC_OFFSET, \
                                    SBB_ISS_STG_PC_DEFAULT, write_data, expected_data, \
                                    SBB_ISS_STG_PC_RD_MASK, SBB_ISS_STG_PC_WR_MASK, \
                                    "SBB_ISS_STG_PC_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_ISS_STG_OPCODE_OFFSET, \
                                    SBB_ISS_STG_OPCODE_DEFAULT, write_data, expected_data, \
                                    SBB_ISS_STG_OPCODE_RD_MASK, SBB_ISS_STG_OPCODE_WR_MASK, \
                                    "SBB_ISS_STG_OPCODE_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_STG_STAT_OFFSET, \
                                    SBB_STG_STAT_DEFAULT, write_data, expected_data, \
                                    SBB_STG_STAT_RD_MASK, SBB_STG_STAT_WR_MASK, \
                                    "SBB_STG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_FREG_HEADPTR_OFFSET, \
                                    SBB_FREG_HEADPTR_DEFAULT, write_data, expected_data, \
                                    SBB_FREG_HEADPTR_RD_MASK, SBB_FREG_HEADPTR_WR_MASK, \
                                    "SBB_FREG_HEADPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_FREG_TAILPTR_OFFSET, \
                                    SBB_FREG_TAILPTR_DEFAULT, write_data, expected_data, \
                                    SBB_FREG_TAILPTR_RD_MASK, SBB_FREG_TAILPTR_WR_MASK, \
                                    "SBB_FREG_TAILPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_HEADPTR_OFFSET, \
                                    SBB_IN_FIFO_HEADPTR_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_HEADPTR_RD_MASK, SBB_IN_FIFO_HEADPTR_WR_MASK, \
                                    "SBB_IN_FIFO_HEADPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_TAILPTR_OFFSET, \
                                    SBB_IN_FIFO_TAILPTR_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_TAILPTR_RD_MASK, SBB_IN_FIFO_TAILPTR_WR_MASK, \
                                    "SBB_IN_FIFO_TAILPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_HEADPTR_OFFSET, \
                                    SBB_OUT_FIFO_HEADPTR_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_HEADPTR_RD_MASK, SBB_OUT_FIFO_HEADPTR_WR_MASK, \
                                    "SBB_OUT_FIFO_HEADPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_TAILPTR_OFFSET, \
                                    SBB_OUT_FIFO_TAILPTR_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_TAILPTR_RD_MASK, SBB_OUT_FIFO_TAILPTR_WR_MASK, \
                                    "SBB_OUT_FIFO_TAILPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_STGMEM_FIFO_HEADPTR_OFFSET, \
                                    SBB_STGMEM_FIFO_HEADPTR_DEFAULT, write_data, expected_data, \
                                    SBB_STGMEM_FIFO_HEADPTR_RD_MASK, SBB_STGMEM_FIFO_HEADPTR_WR_MASK, \
                                    "SBB_STGMEM_FIFO_HEADPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_STGMEM_FIFO_TAILPTR_OFFSET, \
                                    SBB_STGMEM_FIFO_TAILPTR_DEFAULT, write_data, expected_data, \
                                    SBB_STGMEM_FIFO_TAILPTR_RD_MASK, SBB_STGMEM_FIFO_TAILPTR_WR_MASK, \
                                    "SBB_STGMEM_FIFO_TAILPTR_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_CPI_H_OFFSET, \
                                    SBB_CPI_H_DEFAULT, write_data, expected_data, \
                                    SBB_CPI_H_RD_MASK, SBB_CPI_H_WR_MASK, \
                                    "SBB_CPI_H_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_CPI_L_OFFSET, \
                                    SBB_CPI_L_DEFAULT, write_data, expected_data, \
                                    SBB_CPI_L_RD_MASK, SBB_CPI_L_WR_MASK, \
                                    "SBB_CPI_L_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IREG_H_OFFSET, \
                                    SBB_IREG_H_DEFAULT, write_data, expected_data, \
                                    SBB_IREG_H_RD_MASK, SBB_IREG_H_WR_MASK, \
                                    "SBB_IREG_H_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IREG_L_OFFSET, \
                                    SBB_IREG_L_DEFAULT, write_data, expected_data, \
                                    SBB_IREG_L_RD_MASK, SBB_IREG_L_WR_MASK, \
                                    "SBB_IREG_L_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_HOF_H_OFFSET, \
                                    SBB_IN_FIFO_HOF_H_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_HOF_H_RD_MASK, SBB_IN_FIFO_HOF_H_WR_MASK, \
                                    "SBB_IN_FIFO_HOF_H_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_HOF_L_OFFSET, \
                                    SBB_IN_FIFO_HOF_L_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_HOF_L_RD_MASK, SBB_IN_FIFO_HOF_L_WR_MASK, \
                                    "SBB_IN_FIFO_HOF_L_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_HOF_H_OFFSET, \
                                    SBB_OUT_FIFO_HOF_H_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_HOF_H_RD_MASK, SBB_OUT_FIFO_HOF_H_WR_MASK, \
                                    "SBB_OUT_FIFO_HOF_H_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_HOF_L_OFFSET, \
                                    SBB_OUT_FIFO_HOF_L_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_HOF_L_RD_MASK, SBB_OUT_FIFO_HOF_L_WR_MASK, \
                                    "SBB_OUT_FIFO_HOF_L_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_FIFO_OU_STS_OFFSET, \
                                    SBB_FIFO_OU_STS_DEFAULT, write_data, expected_data, \
                                    SBB_FIFO_OU_STS_RD_MASK, SBB_FIFO_OU_STS_WR_MASK, \
                                    "SBB_FIFO_OU_STS_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_FIFO_FE_STS_OFFSET, \
                                    SBB_FIFO_FE_STS_DEFAULT, write_data, expected_data, \
                                    SBB_FIFO_FE_STS_RD_MASK, SBB_FIFO_FE_STS_WR_MASK, \
                                    "SBB_FIFO_FE_STS_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_GENERAL_STAT_OFFSET, \
                                    SBB_GENERAL_STAT_DEFAULT, write_data, expected_data, \
                                    SBB_GENERAL_STAT_RD_MASK, SBB_GENERAL_STAT_WR_MASK, \
                                    "SBB_GENERAL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_CLR_MEM_OFFSET, \
                                    SBB_CLR_MEM_DEFAULT, write_data, expected_data, \
                                    SBB_CLR_MEM_RD_MASK, SBB_CLR_MEM_WR_MASK, \
                                    "SBB_CLR_MEM_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_AXI_CTRL_OFFSET, \
                                    SBB_AXI_CTRL_DEFAULT, write_data, expected_data, \
                                    SBB_AXI_CTRL_RD_MASK, SBB_AXI_CTRL_WR_MASK, \
                                    "SBB_AXI_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_NS_RESEED_CNTER_OFFSET, \
                                    SBB_NS_RESEED_CNTER_DEFAULT, write_data, expected_data, \
                                    SBB_NS_RESEED_CNTER_RD_MASK, SBB_NS_RESEED_CNTER_WR_MASK, \
                                    "SBB_NS_RESEED_CNTER_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H0_OFFSET, \
                                    SBB_IN_FIFO_H0_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H0_RD_MASK, SBB_IN_FIFO_H0_WR_MASK, \
                                    "SBB_IN_FIFO_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L0_OFFSET, \
                                    SBB_IN_FIFO_L0_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L0_RD_MASK, SBB_IN_FIFO_L0_WR_MASK, \
                                    "SBB_IN_FIFO_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H1_OFFSET, \
                                    SBB_IN_FIFO_H1_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H1_RD_MASK, SBB_IN_FIFO_H1_WR_MASK, \
                                    "SBB_IN_FIFO_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L1_OFFSET, \
                                    SBB_IN_FIFO_L1_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L1_RD_MASK, SBB_IN_FIFO_L1_WR_MASK, \
                                    "SBB_IN_FIFO_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H2_OFFSET, \
                                    SBB_IN_FIFO_H2_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H2_RD_MASK, SBB_IN_FIFO_H2_WR_MASK, \
                                    "SBB_IN_FIFO_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L2_OFFSET, \
                                    SBB_IN_FIFO_L2_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L2_RD_MASK, SBB_IN_FIFO_L2_WR_MASK, \
                                    "SBB_IN_FIFO_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H3_OFFSET, \
                                    SBB_IN_FIFO_H3_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H3_RD_MASK, SBB_IN_FIFO_H3_WR_MASK, \
                                    "SBB_IN_FIFO_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L3_OFFSET, \
                                    SBB_IN_FIFO_L3_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L3_RD_MASK, SBB_IN_FIFO_L3_WR_MASK, \
                                    "SBB_IN_FIFO_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H4_OFFSET, \
                                    SBB_IN_FIFO_H4_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H4_RD_MASK, SBB_IN_FIFO_H4_WR_MASK, \
                                    "SBB_IN_FIFO_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L4_OFFSET, \
                                    SBB_IN_FIFO_L4_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L4_RD_MASK, SBB_IN_FIFO_L4_WR_MASK, \
                                    "SBB_IN_FIFO_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H5_OFFSET, \
                                    SBB_IN_FIFO_H5_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H5_RD_MASK, SBB_IN_FIFO_H5_WR_MASK, \
                                    "SBB_IN_FIFO_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L5_OFFSET, \
                                    SBB_IN_FIFO_L5_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L5_RD_MASK, SBB_IN_FIFO_L5_WR_MASK, \
                                    "SBB_IN_FIFO_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H6_OFFSET, \
                                    SBB_IN_FIFO_H6_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H6_RD_MASK, SBB_IN_FIFO_H6_WR_MASK, \
                                    "SBB_IN_FIFO_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L6_OFFSET, \
                                    SBB_IN_FIFO_L6_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L6_RD_MASK, SBB_IN_FIFO_L6_WR_MASK, \
                                    "SBB_IN_FIFO_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_H7_OFFSET, \
                                    SBB_IN_FIFO_H7_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_H7_RD_MASK, SBB_IN_FIFO_H7_WR_MASK, \
                                    "SBB_IN_FIFO_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_IN_FIFO_L7_OFFSET, \
                                    SBB_IN_FIFO_L7_DEFAULT, write_data, expected_data, \
                                    SBB_IN_FIFO_L7_RD_MASK, SBB_IN_FIFO_L7_WR_MASK, \
                                    "SBB_IN_FIFO_L7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H0_OFFSET, \
                                    SBB_OUT_FIFO_H0_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H0_RD_MASK, SBB_OUT_FIFO_H0_WR_MASK, \
                                    "SBB_OUT_FIFO_H0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L0_OFFSET, \
                                    SBB_OUT_FIFO_L0_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L0_RD_MASK, SBB_OUT_FIFO_L0_WR_MASK, \
                                    "SBB_OUT_FIFO_L0_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H1_OFFSET, \
                                    SBB_OUT_FIFO_H1_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H1_RD_MASK, SBB_OUT_FIFO_H1_WR_MASK, \
                                    "SBB_OUT_FIFO_H1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L1_OFFSET, \
                                    SBB_OUT_FIFO_L1_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L1_RD_MASK, SBB_OUT_FIFO_L1_WR_MASK, \
                                    "SBB_OUT_FIFO_L1_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H2_OFFSET, \
                                    SBB_OUT_FIFO_H2_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H2_RD_MASK, SBB_OUT_FIFO_H2_WR_MASK, \
                                    "SBB_OUT_FIFO_H2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L2_OFFSET, \
                                    SBB_OUT_FIFO_L2_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L2_RD_MASK, SBB_OUT_FIFO_L2_WR_MASK, \
                                    "SBB_OUT_FIFO_L2_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H3_OFFSET, \
                                    SBB_OUT_FIFO_H3_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H3_RD_MASK, SBB_OUT_FIFO_H3_WR_MASK, \
                                    "SBB_OUT_FIFO_H3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L3_OFFSET, \
                                    SBB_OUT_FIFO_L3_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L3_RD_MASK, SBB_OUT_FIFO_L3_WR_MASK, \
                                    "SBB_OUT_FIFO_L3_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H4_OFFSET, \
                                    SBB_OUT_FIFO_H4_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H4_RD_MASK, SBB_OUT_FIFO_H4_WR_MASK, \
                                    "SBB_OUT_FIFO_H4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L4_OFFSET, \
                                    SBB_OUT_FIFO_L4_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L4_RD_MASK, SBB_OUT_FIFO_L4_WR_MASK, \
                                    "SBB_OUT_FIFO_L4_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H5_OFFSET, \
                                    SBB_OUT_FIFO_H5_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H5_RD_MASK, SBB_OUT_FIFO_H5_WR_MASK, \
                                    "SBB_OUT_FIFO_H5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L5_OFFSET, \
                                    SBB_OUT_FIFO_L5_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L5_RD_MASK, SBB_OUT_FIFO_L5_WR_MASK, \
                                    "SBB_OUT_FIFO_L5_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H6_OFFSET, \
                                    SBB_OUT_FIFO_H6_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H6_RD_MASK, SBB_OUT_FIFO_H6_WR_MASK, \
                                    "SBB_OUT_FIFO_H6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L6_OFFSET, \
                                    SBB_OUT_FIFO_L6_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L6_RD_MASK, SBB_OUT_FIFO_L6_WR_MASK, \
                                    "SBB_OUT_FIFO_L6_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_H7_OFFSET, \
                                    SBB_OUT_FIFO_H7_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_H7_RD_MASK, SBB_OUT_FIFO_H7_WR_MASK, \
                                    "SBB_OUT_FIFO_H7_OFFSET");

            write_read_expect_18a(base_address[i]+SBB_OUT_FIFO_L7_OFFSET, \
                                    SBB_OUT_FIFO_L7_DEFAULT, write_data, expected_data, \
                                    SBB_OUT_FIFO_L7_RD_MASK, SBB_OUT_FIFO_L7_WR_MASK, \
                                    "SBB_OUT_FIFO_L7_OFFSET");

        }

    }

}
