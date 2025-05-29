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
    MEM_CAP0_CFG_BASE, MEM_CAP1_CFG_BASE
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
            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, MEM_CAP_CFG_BFNE_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_CFG16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, MEM_CAP_CFG_BFNE_INCR_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_INCR16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, MEM_CAP_CFG_BFNE_START_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_START16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, MEM_CAP_CFG_BFNE_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_BFNE_STAT16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_RD_MASK, MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_JESD_IN0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_RD_MASK, MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_TX_JESD_IN0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_JESD_IN1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_RD_MASK, MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_TX_JESD_IN1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_TX_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_TX_OUT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_TX_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_TX_OUT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RX_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_RX_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_RX_OUT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RX_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_RX_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_RX_OUT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RXFB_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_RXFB_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_RXFB_OUT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RXFB_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_RD_MASK, MEM_CAP_CFG_BFN_CAP_RXFB_OUT_WR_MASK, \
                                    "MEM_CAP_CFG_BFN_CAP_RXFB_OUT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_CTRL_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_CTRL_RD_MASK, MEM_CAP_CFG_ISYNC_CTRL_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_LCNT_INC_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_LCNT_INC_RD_MASK, MEM_CAP_CFG_ISYNC_LCNT_INC_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_TEN_MS_CNT_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_TEN_MS_CNT_RD_MASK, MEM_CAP_CFG_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_INC_PRE_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_INC_PRE_RD_MASK, MEM_CAP_CFG_ISYNC_INC_PRE_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_CNT_ADJ_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_CNT_ADJ_RD_MASK, MEM_CAP_CFG_ISYNC_CNT_ADJ_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_RD_MASK, MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_BFN_CNT_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_RD_MASK, MEM_CAP_CFG_ISYNC_BFN_CNT_WR_MASK, \
                                    "MEM_CAP_CFG_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_TX_RATE_OFFSET, \
                                    MEM_CAP_CFG_TX_RATE_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_TX_RATE_RD_MASK, MEM_CAP_CFG_TX_RATE_WR_MASK, \
                                    "MEM_CAP_CFG_TX_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_RX_RATE_OFFSET, \
                                    MEM_CAP_CFG_RX_RATE_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_RX_RATE_RD_MASK, MEM_CAP_CFG_RX_RATE_WR_MASK, \
                                    "MEM_CAP_CFG_RX_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_PLL_CTL_OFFSET, \
                                    MEM_CAP_CFG_PLL_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_PLL_CTL_RD_MASK, MEM_CAP_CFG_PLL_CTL_WR_MASK, \
                                    "MEM_CAP_CFG_PLL_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_AC_NCO_CFG_OFFSET, \
                                    MEM_CAP_CFG_AC_NCO_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_AC_NCO_CFG_RD_MASK, MEM_CAP_CFG_AC_NCO_CFG_WR_MASK, \
                                    "MEM_CAP_CFG_AC_NCO_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_DP_INIT_OFFSET, \
                                    MEM_CAP_CFG_DP_INIT_DEFAULT, write_data, expected_data, \
                                    0x3, MEM_CAP_CFG_DP_INIT_WR_MASK, \
                                    "MEM_CAP_CFG_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R0_OFFSET, \
                                    MEM_CAP_CFG_SMON_R0_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R0_RD_MASK, MEM_CAP_CFG_SMON_R0_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R1_OFFSET, \
                                    MEM_CAP_CFG_SMON_R1_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R1_RD_MASK, MEM_CAP_CFG_SMON_R1_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R2_OFFSET, \
                                    MEM_CAP_CFG_SMON_R2_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R2_RD_MASK, MEM_CAP_CFG_SMON_R2_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R3_OFFSET, \
                                    MEM_CAP_CFG_SMON_R3_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R3_RD_MASK, MEM_CAP_CFG_SMON_R3_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R4_OFFSET, \
                                    MEM_CAP_CFG_SMON_R4_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R4_RD_MASK, MEM_CAP_CFG_SMON_R4_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R5_OFFSET, \
                                    MEM_CAP_CFG_SMON_R5_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R5_RD_MASK, MEM_CAP_CFG_SMON_R5_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R5_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R6_OFFSET, \
                                    MEM_CAP_CFG_SMON_R6_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R6_RD_MASK, MEM_CAP_CFG_SMON_R6_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R7_OFFSET, \
                                    MEM_CAP_CFG_SMON_R7_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_SMON_R7_RD_MASK, MEM_CAP_CFG_SMON_R7_WR_MASK, \
                                    "MEM_CAP_CFG_SMON_R7_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test cases
//            write_read_expect_18a(base_address[i]+MEM_CAP_CFG_APB_BRDG_STAT_OFFSET, \
                                    MEM_CAP_CFG_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_CAP_CFG_APB_BRDG_STAT_RD_MASK, MEM_CAP_CFG_APB_BRDG_STAT_WR_MASK, \
                                    "MEM_CAP_CFG_APB_BRDG_STAT_OFFSET");

        }

    }

}
