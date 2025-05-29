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
    DLNK_JESD0_PHY_PMA0_RXWORD_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RXWORD_Q0_BASE, DLNK_JESD0_PHY_PMA0_RXWORD_Q1_BASE, DLNK_JESD0_PHY_PMA0_RXWORD_Q2_BASE, DLNK_JESD0_PHY_PMA0_RXWORD_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RXWORD_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RXWORD_Q0_BASE, DLNK_JESD1_PHY_PMA0_RXWORD_Q1_BASE, DLNK_JESD1_PHY_PMA0_RXWORD_Q2_BASE, DLNK_JESD1_PHY_PMA0_RXWORD_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RXWORD_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RXWORD_Q0_BASE, DLNK_JESD2_PHY_PMA0_RXWORD_Q1_BASE, DLNK_JESD2_PHY_PMA0_RXWORD_Q2_BASE, DLNK_JESD2_PHY_PMA0_RXWORD_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RXWORD_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RXWORD_Q0_BASE, DLNK_JESD3_PHY_PMA0_RXWORD_Q1_BASE, DLNK_JESD3_PHY_PMA0_RXWORD_Q2_BASE, DLNK_JESD3_PHY_PMA0_RXWORD_Q3_BASE
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
            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET0_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET1_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET2_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET3_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET4_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET5_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET6_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET7_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET8_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET9_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET10_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET11_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET12_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET13_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET14_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_SLICE_LVL_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_SLICE_LVL_SET15_RD_MASK, PMA_RXWORD_MSG_FFE_SLICE_LVL_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_SLICE_LVL_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET1_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET1_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET2_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET2_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET3_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET3_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET4_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET4_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET5_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET5_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET6_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET6_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET7_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET7_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET8_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET8_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET9_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET9_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET10_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET10_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET11_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET11_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET12_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET12_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET13_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET13_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET14_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET14_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET15_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_M1M3_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET15_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_P1P3_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_DUMP_MEM_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_CTRL_RD_MASK, PMA_RXWORD_MSG_RX_DUMP_MEM_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_DUMP_MEM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_DATA_OFFSET, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_DATA_RD_MASK, PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_DATA_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_EN_OFFSET, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_EN_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_EN_RD_MASK, PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_EN_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_DUMP_MEM_APB_RD_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_DUMP_MEM_APB_EN_OFFSET, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_EN_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_DUMP_MEM_APB_EN_RD_MASK, PMA_RXWORD_MSG_RX_DUMP_MEM_APB_EN_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_DUMP_MEM_APB_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_DATA_PATH_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_RX_DATA_PATH_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_DATA_PATH_CTRL_1_RD_MASK, PMA_RXWORD_MSG_RX_DATA_PATH_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_DATA_PATH_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADP_MSB_LSB_SWAP_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADP_MSB_LSB_SWAP_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADP_MSB_LSB_SWAP_CTRL_RD_MASK, PMA_RXWORD_MSG_ADP_MSB_LSB_SWAP_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADP_MSB_LSB_SWAP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION1_RD_MASK, PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION2_RD_MASK, PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION3_RD_MASK, PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_FLOAT_TAP_POSITION3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_0_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_1_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_2_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_3_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_4_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_6_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_7_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_7_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_8_OFFSET, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_8_RD_MASK, PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_8_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXEQ_CLK_GATING_CTRL_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET0_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET0_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET0_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET0_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET0_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET1_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET1_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET1_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET1_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET1_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET2_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET2_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET2_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET2_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET2_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET3_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET3_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET3_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET3_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET3_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET4_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET4_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET4_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET4_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET4_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET5_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET5_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET5_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET5_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET5_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET6_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET6_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET6_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET6_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET6_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET7_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET7_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET7_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET7_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET7_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET8_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET8_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET8_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET8_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET8_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET9_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET9_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET9_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET9_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET9_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET10_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET10_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET10_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET10_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET10_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET11_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET11_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET11_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET11_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET11_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET12_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET12_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET12_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET12_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET12_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET13_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET13_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET13_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET13_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET13_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET14_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET14_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET14_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET14_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET14_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_SLICER_LVL_SET15_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET15_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_SLICER_LVL_SET15_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_SLICER_LVL_SET15_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_SLICER_LVL_SET15_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET0_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET0_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET0_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET0_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET0_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET1_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET1_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET1_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET1_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET1_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET2_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET2_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET2_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET2_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET2_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET3_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET3_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET3_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET3_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET3_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET4_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET4_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET4_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET4_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET4_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET5_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET5_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET5_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET5_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET5_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET6_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET6_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET6_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET6_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET6_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET7_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET7_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET7_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET7_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET7_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET8_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET8_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET8_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET8_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET8_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET9_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET9_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET9_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET9_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET9_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET10_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET10_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET10_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET10_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET10_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET11_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET11_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET11_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET11_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET11_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET12_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET12_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET12_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET12_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET12_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET13_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET13_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET13_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET13_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET13_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET14_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET14_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET14_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET14_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET14_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_SET15_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET15_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_SET15_CTRL_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_SET15_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_SET15_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL0_OFFSET, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL0_RD_MASK, PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL0_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL1_OFFSET, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL1_RD_MASK, PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL2_OFFSET, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL2_RD_MASK, PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL2_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_STAT_OFFSET, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_STAT_RD_MASK, PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_STAT_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSARARRAY_VALID_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSAR_CALASSIST_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_RXSAR_CALASSIST_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSAR_CALASSIST_CTRL_RD_MASK, PMA_RXWORD_MSG_RXSAR_CALASSIST_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSAR_CALASSIST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXSAR_CALASSIST_STAT_OFFSET, \
                                    PMA_RXWORD_MSG_RXSAR_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXSAR_CALASSIST_STAT_RD_MASK, PMA_RXWORD_MSG_RXSAR_CALASSIST_STAT_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXSAR_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_6_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_0_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_STAT_0_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_1_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_2_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_3_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_TAPS_SET_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_TAPS_SET_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_TAPS_SET_CTRL_RD_MASK, PMA_RXWORD_MSG_TAPS_SET_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_TAPS_SET_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_GEARBOX_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_RX_GEARBOX_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_GEARBOX_CTRL_RD_MASK, PMA_RXWORD_MSG_RX_GEARBOX_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_GEARBOX_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_4_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_MAIN_FSM_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_MAIN_FSM_CTRL_5_RD_MASK, PMA_RXWORD_MSG_MAIN_FSM_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_MAIN_FSM_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_1_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_2_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_3_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_4_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_5_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_CTRL_6_RD_MASK, PMA_RXWORD_MSG_VREF_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VREF_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_VREF_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VREF_STAT_0_RD_MASK, PMA_RXWORD_MSG_VREF_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_VREF_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_6_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_5_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_4_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_0_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_1_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_2_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_CTRL_3_RD_MASK, PMA_RXWORD_MSG_VGA_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_VGA_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_VGA_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_VGA_STAT_0_RD_MASK, PMA_RXWORD_MSG_VGA_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_VGA_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_JPP_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_JPP_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_JPP_CTRL_1_RD_MASK, PMA_RXWORD_MSG_JPP_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_JPP_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_JPP_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_JPP_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_JPP_CTRL_2_RD_MASK, PMA_RXWORD_MSG_JPP_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_JPP_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_0_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_1_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_2_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_3_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_4_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_CTRL_5_RD_MASK, PMA_RXWORD_MSG_FFE_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_STAT_0_RD_MASK, PMA_RXWORD_MSG_FFE_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_0_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_1_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_2_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_3_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_4_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_5_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_6_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_7_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_7_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_8_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_8_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_8_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_9_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_9_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_9_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_10_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_10_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_10_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_11_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_11_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_11_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_12_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_12_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_12_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_CTRL_13_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_CTRL_13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_CTRL_13_RD_MASK, PMA_RXWORD_MSG_HIST_CTRL_13_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_CTRL_13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_0_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_1_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_1_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_2_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_2_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_3_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_3_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_4_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_4_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_5_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_5_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_6_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_6_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_7_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_7_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_8_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_8_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_8_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_9_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_9_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_9_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_10_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_10_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_10_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_11_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_11_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_11_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_12_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_12_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_12_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_13_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_13_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_13_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_14_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_14_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_14_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_HIST_STAT_15_OFFSET, \
                                    PMA_RXWORD_MSG_HIST_STAT_15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_HIST_STAT_15_RD_MASK, PMA_RXWORD_MSG_HIST_STAT_15_WR_MASK, \
                                    "PMA_RXWORD_MSG_HIST_STAT_15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_CTRL_1_RD_MASK, PMA_RXWORD_MSG_OPS_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_CTRL_2_RD_MASK, PMA_RXWORD_MSG_OPS_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_CTRL_3_RD_MASK, PMA_RXWORD_MSG_OPS_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_CTRL_4_RD_MASK, PMA_RXWORD_MSG_OPS_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_STAT_1_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_STAT_1_RD_MASK, PMA_RXWORD_MSG_OPS_STAT_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_STAT_2_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_STAT_2_RD_MASK, PMA_RXWORD_MSG_OPS_STAT_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_1_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_2_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_3_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_4_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_5_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_CTRL_6_RD_MASK, PMA_RXWORD_MSG_ADCVREF_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCVREF_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADCVREF_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCVREF_STAT_0_RD_MASK, PMA_RXWORD_MSG_ADCVREF_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCVREF_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_0_RD_MASK, PMA_RXWORD_MSG_AFFE_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_1_RD_MASK, PMA_RXWORD_MSG_AFFE_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_2_RD_MASK, PMA_RXWORD_MSG_AFFE_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_CTRL_3_RD_MASK, PMA_RXWORD_MSG_AFFE_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_STAT_0_RD_MASK, PMA_RXWORD_MSG_AFFE_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_0_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_1A_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_1A_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_1A_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_1A_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_1A_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_1B_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_1B_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_1B_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_1B_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_1B_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_2_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_3_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_STAT_0_RD_MASK, PMA_RXWORD_MSG_OFC_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET0_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET1_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET2_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET3_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET4_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET5_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET6_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET7_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET8_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET9_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET10_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET11_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET12_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET13_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET14_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_0_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_1_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_1_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_2_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_2_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_3_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_3_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_4_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_4_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_5_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_5_RD_MASK, PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_COEFF_SET15_FRAC_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET0_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET0_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET0_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET0_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET0_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET1_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET1_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET1_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET1_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET2_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET2_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET2_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET2_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET3_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET3_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET3_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET3_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET3_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET4_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET4_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET4_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET4_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET4_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET5_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET5_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET5_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET5_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET5_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET6_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET6_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET6_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET6_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET6_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET7_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET7_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET7_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET7_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET8_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET8_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET8_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET8_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET8_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET9_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET9_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET9_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET9_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET9_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET10_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET10_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET10_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET10_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET10_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET11_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET11_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET11_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET11_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET11_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET12_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET12_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET12_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET12_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET12_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET13_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET13_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET13_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET13_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET13_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET14_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET14_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET14_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET14_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET14_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET15_0_OFFSET, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET15_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET15_0_RD_MASK, PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET15_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_FFE_ERR_LVL_FRAC_SET15_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET0_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET0_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET0_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET0_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET0_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET1_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET1_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET1_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET1_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET2_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET2_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET2_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET2_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET3_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET3_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET3_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET3_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET3_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET4_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET4_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET4_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET4_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET4_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET5_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET5_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET5_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET5_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET5_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET6_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET6_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET6_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET6_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET6_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET7_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET7_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET7_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET7_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET8_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET8_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET8_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET8_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET8_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET9_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET9_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET9_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET9_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET9_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET10_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET10_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET10_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET10_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET10_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET11_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET11_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET11_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET11_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET11_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET12_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET12_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET12_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET12_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET12_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET13_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET13_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET13_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET13_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET13_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET14_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET14_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET14_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET14_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET14_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET15_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET15_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET15_0_RD_MASK, PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET15_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADC_ERR_LVL_FRAC_SET15_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET0_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET1_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET2_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET3_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET4_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET5_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET6_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET7_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET8_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET9_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET10_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET11_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET12_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET13_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET14_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_SET15_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET0_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET1_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET2_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET3_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET4_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET5_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET6_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET7_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET8_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET9_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET10_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET11_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET12_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET13_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET14_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET15_RD_MASK, PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_LMS_FRAC_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_SATURATION_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_0_RD_MASK, PMA_RXWORD_MSG_SATURATION_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_SATURATION_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_SATURATION_STAT_1_OFFSET, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_1_RD_MASK, PMA_RXWORD_MSG_SATURATION_STAT_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_SATURATION_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_SATURATION_STAT_3_OFFSET, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_3_RD_MASK, PMA_RXWORD_MSG_SATURATION_STAT_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_SATURATION_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ZEROAVG_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_0_RD_MASK, PMA_RXWORD_MSG_ZEROAVG_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ZEROAVG_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ZEROAVG_STAT_1_OFFSET, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_1_RD_MASK, PMA_RXWORD_MSG_ZEROAVG_STAT_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_ZEROAVG_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ZEROAVG_STAT_3_OFFSET, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ZEROAVG_STAT_3_RD_MASK, PMA_RXWORD_MSG_ZEROAVG_STAT_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_ZEROAVG_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_0_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_1_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_2_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_3_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_STAT_0_RD_MASK, PMA_RXWORD_MSG_ADCOFC_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICE_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICE_CTRL_0_RD_MASK, PMA_RXWORD_MSG_EDG_SLICE_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET0_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET0_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET0_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET0_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET0_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET1_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET1_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET1_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET1_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET1_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET2_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET2_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET2_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET2_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET2_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET3_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET3_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET3_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET3_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET3_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET4_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET4_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET4_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET4_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET4_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET5_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET5_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET5_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET5_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET5_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET6_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET6_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET6_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET6_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET6_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDG_SLICER_LVL_SET7_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET7_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDG_SLICER_LVL_SET7_CTRL_RD_MASK, PMA_RXWORD_MSG_EDG_SLICER_LVL_SET7_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDG_SLICER_LVL_SET7_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_1_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_2_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_3_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_4_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_5_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_CTRL_6_RD_MASK, PMA_RXWORD_MSG_EDGVREF_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET0_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET1_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET2_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET3_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET4_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET5_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET6_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_EDGVREF_FRAC_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_EDGVREF_FRAC_SET7_RD_MASK, PMA_RXWORD_MSG_EDGVREF_FRAC_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_EDGVREF_FRAC_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_JPP_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_JPP_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_JPP_CTRL_0_RD_MASK, PMA_RXWORD_MSG_JPP_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_JPP_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_0_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_1_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_2_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_CTRL_3_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_STAT_0_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET0TO3_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET4TO7_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET8TO11_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_SET12TO15_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_FRAC_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET0TO3_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_FRAC_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_FRAC_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_FRAC_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET4TO7_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_FRAC_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_FRAC_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_FRAC_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET8TO11_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_FRAC_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_FRAC_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_LMS_FRAC_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_LMS_FRAC_SET12TO15_RD_MASK, PMA_RXWORD_MSG_DFE_LMS_FRAC_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_LMS_FRAC_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_DFE_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_DFE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_DFE_CTRL_0_RD_MASK, PMA_RXWORD_MSG_DFE_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_DFE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SARARRAY_VALID_0_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SARARRAY_VALID_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SARARRAY_VALID_0_RD_MASK, PMA_RXWORD_MSG_RX_SARARRAY_VALID_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SARARRAY_VALID_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SARARRAY_VALID_1_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SARARRAY_VALID_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SARARRAY_VALID_1_RD_MASK, PMA_RXWORD_MSG_RX_SARARRAY_VALID_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SARARRAY_VALID_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET0_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET0_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET0_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET0_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET0_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET1_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET1_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET1_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET1_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET1_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET2_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET2_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET2_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET2_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET2_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET3_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET3_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET3_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET3_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET3_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET4_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET4_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET4_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET4_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET4_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET5_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET5_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET5_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET5_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET5_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET6_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET6_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET6_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET6_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET6_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET7_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET7_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET7_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET7_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET7_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET8_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET8_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET8_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET8_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET8_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET9_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET9_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET9_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET9_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET9_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET10_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET10_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET10_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET10_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET10_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET11_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET11_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET11_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET11_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET11_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET12_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET12_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET12_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET12_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET12_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET13_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET13_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET13_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET13_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET13_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET14_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET14_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET14_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET14_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET14_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET15_CTRL_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET15_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET15_CTRL_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET15_CTRL_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_SLICER_LVL_SET15_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET1_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET1_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET1_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET1_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET2_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET2_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET2_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET2_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET4_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET4_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET4_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET4_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET5_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET5_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET5_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET5_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET6_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET6_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET6_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET6_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET8_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET8_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET8_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET8_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET8_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET9_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET9_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET9_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET9_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET9_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET10_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET10_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET10_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET10_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET10_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET12_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET12_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET12_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET12_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET12_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET13_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET13_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET13_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET13_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET13_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET14_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET14_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET14_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET14_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET14_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_M1M3_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_P1P3_SET15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_1_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_2_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_LMS_AVG_UPDN_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_LMS_AVG_UPDN_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_LMS_AVG_UPDN_STAT_0_RD_MASK, PMA_RXWORD_MSG_LMS_AVG_UPDN_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_LMS_AVG_UPDN_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_1_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_1_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_2_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_4_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_5_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_6_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_VREF_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1A_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1A_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1A_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1A_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1A_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1B_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1B_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1B_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1B_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_1B_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_2_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_2_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_STAT_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_STAT_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_STAT_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE1_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST1_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET0_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET0_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET0_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET0_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET0_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET1_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET1_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET1_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET1_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET2_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET2_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET2_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET2_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET3_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET3_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET3_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET3_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET3_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET4_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET4_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET4_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET4_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET4_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET5_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET5_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET5_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET5_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET5_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET6_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET6_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET6_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET6_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET6_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET7_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET7_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET7_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET7_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET8_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET8_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET8_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET8_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET8_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET9_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET9_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET9_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET9_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET9_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET10_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET10_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET10_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET10_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET10_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET11_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET11_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET11_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET11_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET11_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET12_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET12_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET12_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET12_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET12_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET13_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET13_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET13_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET13_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET13_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET14_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET14_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET14_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET14_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET14_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET15_0_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET15_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET15_0_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET15_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_ERR_LVL_FRAC_SET15_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_CTRL_3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_CTRL_3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_CTRL_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE3_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_PRE2_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST2_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST3_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET0TO3_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET4TO7_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET8TO11_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_FRAC_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_FRAC_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_FRAC_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_FRAC_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_POST4_SET12TO15_FRAC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_SATURATION_STAT_4_OFFSET, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_SATURATION_STAT_4_RD_MASK, PMA_RXWORD_MSG_SATURATION_STAT_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_SATURATION_STAT_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_AFFE_IF_CTRL_0_OFFSET, \
                                    PMA_RXWORD_MSG_AFFE_IF_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_AFFE_IF_CTRL_0_RD_MASK, PMA_RXWORD_MSG_AFFE_IF_CTRL_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_AFFE_IF_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B0_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B1_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B2_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B3_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B4_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_B5_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B0_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B1_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B2_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B3_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B4_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_0TO3_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_0TO3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_0TO3_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_0TO3_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_0TO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_4TO7_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_4TO7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_4TO7_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_4TO7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_4TO7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_8TO11_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_8TO11_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_8TO11_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_8TO11_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_8TO11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_12TO15_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_12TO15_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_12TO15_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_12TO15_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_12TO15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_16TO19_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_16TO19_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_16TO19_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_16TO19_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_16TO19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_20TO23_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_20TO23_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_20TO23_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_20TO23_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_20TO23_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_24TO27_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_24TO27_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_24TO27_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_24TO27_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_24TO27_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_28TO31_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_28TO31_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_28TO31_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_28TO31_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_28TO31_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_32TO35_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_32TO35_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_32TO35_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_32TO35_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_32TO35_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_36TO39_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_36TO39_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_36TO39_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_36TO39_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_36TO39_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_40TO43_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_40TO43_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_40TO43_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_40TO43_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_40TO43_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_44TO47_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_44TO47_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_44TO47_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_44TO47_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_44TO47_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_48TO51_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_48TO51_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_48TO51_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_48TO51_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_48TO51_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_52TO55_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_52TO55_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_52TO55_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_52TO55_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_52TO55_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_56TO59_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_56TO59_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_56TO59_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_56TO59_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_56TO59_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_60TO63_OFFSET, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_60TO63_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_60TO63_RD_MASK, PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_60TO63_WR_MASK, \
                                    "PMA_RXWORD_MSG_OPS_TAPS_FRA_B5_SAR_60TO63_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_4_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_5_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_6_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_OFC_CTRL_7_OFFSET, \
                                    PMA_RXWORD_MSG_OFC_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_OFC_CTRL_7_RD_MASK, PMA_RXWORD_MSG_OFC_CTRL_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_OFC_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_4_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_5_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_6_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_7_OFFSET, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_7_RD_MASK, PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_CDR_FFE_OFC_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_4_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_4_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_4_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_5_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_5_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_5_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_6_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_6_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_6_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_ADCOFC_CTRL_7_OFFSET, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_ADCOFC_CTRL_7_RD_MASK, PMA_RXWORD_MSG_ADCOFC_CTRL_7_WR_MASK, \
                                    "PMA_RXWORD_MSG_ADCOFC_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL1_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL1_RD_MASK, PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL2_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL2_RD_MASK, PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL2_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL3_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL3_RD_MASK, PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL3_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SIGDET_VENV_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_RD_MASK, PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_CLR_OFFSET, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_CLR_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_CLR_RD_MASK, PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_CLR_WR_MASK, \
                                    "PMA_RXWORD_MSG_RX_SIGDET_VENV_STAT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RW_SPARE_0_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_0_RD_MASK, PMA_RXWORD_MSG_RXWORD_RW_SPARE_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RW_SPARE_1_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_1_RD_MASK, PMA_RXWORD_MSG_RXWORD_RW_SPARE_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RW_SPARE_2_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_2_RD_MASK, PMA_RXWORD_MSG_RXWORD_RW_SPARE_2_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RW_SPARE_3_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RW_SPARE_3_RD_MASK, PMA_RXWORD_MSG_RXWORD_RW_SPARE_3_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RO_SPARE_0_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RO_SPARE_0_RD_MASK, PMA_RXWORD_MSG_RXWORD_RO_SPARE_0_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RXWORD_MSG_RXWORD_RO_SPARE_1_OFFSET, \
                                    PMA_RXWORD_MSG_RXWORD_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_RXWORD_MSG_RXWORD_RO_SPARE_1_RD_MASK, PMA_RXWORD_MSG_RXWORD_RO_SPARE_1_WR_MASK, \
                                    "PMA_RXWORD_MSG_RXWORD_RO_SPARE_1_OFFSET");

        }

    }

}
