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
    ANT0_ADC_DIG0_BASE, ANT0_ADC_DIG1_BASE, ANT0_ADC_DIG2_BASE, ANT0_ADC_DIG3_BASE, ANT0_ADC_DIG_FB_BASE,
    ANT1_ADC_DIG0_BASE, ANT1_ADC_DIG1_BASE, ANT1_ADC_DIG2_BASE, ANT1_ADC_DIG3_BASE, ANT1_ADC_DIG_FB_BASE,
    ANT2_ADC_DIG0_BASE, ANT2_ADC_DIG1_BASE, ANT2_ADC_DIG2_BASE, ANT2_ADC_DIG3_BASE, ANT2_ADC_DIG_FB_BASE,
    ANT3_ADC_DIG0_BASE, ANT3_ADC_DIG1_BASE, ANT3_ADC_DIG2_BASE, ANT3_ADC_DIG3_BASE, ANT3_ADC_DIG_FB_BASE
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
            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM0_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM0_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM0_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM0_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM1_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM1_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM1_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM1_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM2_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM2_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM2_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM2_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM3_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM3_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM3_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM3_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM4_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM4_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM4_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM4_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM5_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM5_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM5_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM5_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM6_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM6_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM6_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM6_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM7_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM7_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM7_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM7_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM8_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM8_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM8_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM8_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM9_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM9_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM9_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM9_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM10_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM10_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM10_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM10_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM11_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM11_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM11_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM11_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM12_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM12_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM12_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM12_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM13_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM13_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM13_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM13_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM14_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM14_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM14_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM14_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM15_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM15_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM15_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM15_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM16_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM16_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM16_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM16_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM17_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM17_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM17_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM17_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM18_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM18_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM18_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM18_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM19_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM19_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ0_MEM19_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ0_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ0_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ0_MEM19_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM0_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM0_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM0_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM0_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM1_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM1_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM1_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM1_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM2_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM2_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM2_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM2_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM3_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM3_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM3_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM3_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM4_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM4_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM4_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM4_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM5_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM5_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM5_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM5_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM6_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM6_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM6_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM6_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM7_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM7_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM7_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM7_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM8_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM8_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM8_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM8_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM9_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM9_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM9_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM9_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM10_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM10_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM10_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM10_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM11_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM11_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM11_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM11_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM12_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM12_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM12_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM12_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM13_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM13_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM13_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM13_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM14_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM14_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM14_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM14_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM15_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM15_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM15_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM15_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM16_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM16_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM16_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM16_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM17_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM17_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM17_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM17_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM18_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM18_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM18_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM18_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM19_CMD_DATA_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_DATA_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM19_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ1_MEM19_CMD_AW_OFFSET, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ1_MEM_CMD_AW_RD_MASK, ADC_DIG_SEQ1_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_SEQ1_MEM19_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCRATCHPADD_OFFSET, \
                                    ADC_DIG_SCRATCHPADD_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCRATCHPADD_RD_MASK, ADC_DIG_SCRATCHPADD_WR_MASK, \
                                    "ADC_DIG_SCRATCHPADD_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFGD_OFFSET, \
                                    ADC_DIG_CFGD_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFGD_RD_MASK, ADC_DIG_CFGD_WR_MASK, \
                                    "ADC_DIG_CFGD_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_ITER0_OFFSET, \
                                    ADC_DIG_SEQ_ITER_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_ITER_RD_MASK, ADC_DIG_SEQ_ITER_WR_MASK, \
                                    "ADC_DIG_SEQ_ITER0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_ITER1_OFFSET, \
                                    ADC_DIG_SEQ_ITER_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_ITER_RD_MASK, ADC_DIG_SEQ_ITER_WR_MASK, \
                                    "ADC_DIG_SEQ_ITER1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_CTRL0_OFFSET, \
                                    ADC_DIG_SEQ_CTRL_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_CTRL_RD_MASK, ADC_DIG_SEQ_CTRL_WR_MASK, \
                                    "ADC_DIG_SEQ_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_CTRL1_OFFSET, \
                                    ADC_DIG_SEQ_CTRL_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_CTRL_RD_MASK, ADC_DIG_SEQ_CTRL_WR_MASK, \
                                    "ADC_DIG_SEQ_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG0_OFFSET, \
                                    ADC_DIG_CFG0_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG0_RD_MASK, ADC_DIG_CFG0_WR_MASK, \
                                    "ADC_DIG_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG1_OFFSET, \
                                    ADC_DIG_CFG1_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG1_RD_MASK, ADC_DIG_CFG1_WR_MASK, \
                                    "ADC_DIG_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG2_OFFSET, \
                                    ADC_DIG_CFG2_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG2_RD_MASK, ADC_DIG_CFG2_WR_MASK, \
                                    "ADC_DIG_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG3_OFFSET, \
                                    ADC_DIG_CFG3_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG3_RD_MASK, ADC_DIG_CFG3_WR_MASK, \
                                    "ADC_DIG_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG4_OFFSET, \
                                    ADC_DIG_CFG4_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG4_RD_MASK, ADC_DIG_CFG4_WR_MASK, \
                                    "ADC_DIG_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG5_OFFSET, \
                                    ADC_DIG_CFG5_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG5_RD_MASK, ADC_DIG_CFG5_WR_MASK, \
                                    "ADC_DIG_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG6_OFFSET, \
                                    ADC_DIG_CFG6_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG6_RD_MASK, ADC_DIG_CFG6_WR_MASK, \
                                    "ADC_DIG_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG7_OFFSET, \
                                    ADC_DIG_CFG7_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG7_RD_MASK, ADC_DIG_CFG7_WR_MASK, \
                                    "ADC_DIG_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG8_OFFSET, \
                                    ADC_DIG_CFG8_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG8_RD_MASK, ADC_DIG_CFG8_WR_MASK, \
                                    "ADC_DIG_CFG8_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG9_OFFSET, \
                                    ADC_DIG_CFG9_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG9_RD_MASK, ADC_DIG_CFG9_WR_MASK, \
                                    "ADC_DIG_CFG9_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG10_OFFSET, \
                                    ADC_DIG_CFG10_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG10_RD_MASK, ADC_DIG_CFG10_WR_MASK, \
                                    "ADC_DIG_CFG10_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG11_OFFSET, \
                                    ADC_DIG_CFG11_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG11_RD_MASK, ADC_DIG_CFG11_WR_MASK, \
                                    "ADC_DIG_CFG11_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG12_OFFSET, \
                                    ADC_DIG_CFG12_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG12_RD_MASK, ADC_DIG_CFG12_WR_MASK, \
                                    "ADC_DIG_CFG12_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG13_OFFSET, \
                                    ADC_DIG_CFG13_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG13_RD_MASK, ADC_DIG_CFG13_WR_MASK, \
                                    "ADC_DIG_CFG13_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG14_OFFSET, \
                                    ADC_DIG_CFG14_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG14_RD_MASK, ADC_DIG_CFG14_WR_MASK, \
                                    "ADC_DIG_CFG14_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG15_OFFSET, \
                                    ADC_DIG_CFG15_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG15_RD_MASK, ADC_DIG_CFG15_WR_MASK, \
                                    "ADC_DIG_CFG15_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG16_OFFSET, \
                                    ADC_DIG_CFG16_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG16_RD_MASK, ADC_DIG_CFG16_WR_MASK, \
                                    "ADC_DIG_CFG16_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG17_OFFSET, \
                                    ADC_DIG_CFG17_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG17_RD_MASK, ADC_DIG_CFG17_WR_MASK, \
                                    "ADC_DIG_CFG17_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG18_OFFSET, \
                                    ADC_DIG_CFG18_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG18_RD_MASK, ADC_DIG_CFG18_WR_MASK, \
                                    "ADC_DIG_CFG18_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG19_OFFSET, \
                                    ADC_DIG_CFG19_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG19_RD_MASK, ADC_DIG_CFG19_WR_MASK, \
                                    "ADC_DIG_CFG19_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG20_OFFSET, \
                                    ADC_DIG_CFG20_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG20_RD_MASK, ADC_DIG_CFG20_WR_MASK, \
                                    "ADC_DIG_CFG20_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG21_OFFSET, \
                                    ADC_DIG_CFG21_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG21_RD_MASK, ADC_DIG_CFG21_WR_MASK, \
                                    "ADC_DIG_CFG21_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG22_OFFSET, \
                                    ADC_DIG_CFG22_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG22_RD_MASK, ADC_DIG_CFG22_WR_MASK, \
                                    "ADC_DIG_CFG22_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG23_OFFSET, \
                                    ADC_DIG_CFG23_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG23_RD_MASK, ADC_DIG_CFG23_WR_MASK, \
                                    "ADC_DIG_CFG23_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG24_OFFSET, \
                                    ADC_DIG_CFG24_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG24_RD_MASK, ADC_DIG_CFG24_WR_MASK, \
                                    "ADC_DIG_CFG24_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_APB_BRDG_DCLK_STAT_OFFSET, \
                                    ADC_DIG_APB_BRDG_DCLK_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_APB_BRDG_DCLK_STAT_RD_MASK, ADC_DIG_APB_BRDG_DCLK_STAT_WR_MASK, \
                                    "ADC_DIG_APB_BRDG_DCLK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_SEQ_CMD_DATA0_OFFSET, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_DATA_RD_MASK, ADC_DIG_PROT_STAT_SEQ_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_SEQ_CMD_DATA0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_SEQ_CMD_DATA1_OFFSET, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_DATA_RD_MASK, ADC_DIG_PROT_STAT_SEQ_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_SEQ_CMD_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_SEQ_CMD_AW0_OFFSET, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_AW_RD_MASK, ADC_DIG_PROT_STAT_SEQ_CMD_AW_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_SEQ_CMD_AW0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_SEQ_CMD_AW1_OFFSET, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_SEQ_CMD_AW_RD_MASK, ADC_DIG_PROT_STAT_SEQ_CMD_AW_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_SEQ_CMD_AW1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_CFG_OFFSET, \
                                    ADC_DIG_PROT_STAT_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_CFG_RD_MASK, ADC_DIG_PROT_STAT_CFG_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_COLLISION_STAT_OFFSET, \
                                    ADC_DIG_COLLISION_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_COLLISION_STAT_RD_MASK, ADC_DIG_COLLISION_STAT_WR_MASK, \
                                    "ADC_DIG_COLLISION_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_STAT0_OFFSET, \
                                    ADC_DIG_SEQ_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_STAT_RD_MASK, ADC_DIG_SEQ_STAT_WR_MASK, \
                                    "ADC_DIG_SEQ_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SEQ_STAT1_OFFSET, \
                                    ADC_DIG_SEQ_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SEQ_STAT_RD_MASK, ADC_DIG_SEQ_STAT_WR_MASK, \
                                    "ADC_DIG_SEQ_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_STAT0_OFFSET, \
                                    ADC_DIG_STAT0_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_STAT0_RD_MASK, ADC_DIG_STAT0_WR_MASK, \
                                    "ADC_DIG_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_STAT1_OFFSET, \
                                    ADC_DIG_STAT1_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_STAT1_RD_MASK, ADC_DIG_STAT1_WR_MASK, \
                                    "ADC_DIG_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_STAT2_OFFSET, \
                                    ADC_DIG_STAT2_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_STAT2_RD_MASK, ADC_DIG_STAT2_WR_MASK, \
                                    "ADC_DIG_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_STAT3_OFFSET, \
                                    ADC_DIG_STAT3_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_STAT3_RD_MASK, ADC_DIG_STAT3_WR_MASK, \
                                    "ADC_DIG_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_INT_STAT_OFFSET, \
                                    ADC_DIG_INT_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_INT_STAT_RD_MASK, ADC_DIG_INT_STAT_WR_MASK, \
                                    "ADC_DIG_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_INT_HIGH_EN_OFFSET, \
                                    ADC_DIG_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_INT_HIGH_EN_RD_MASK, ADC_DIG_INT_HIGH_EN_WR_MASK, \
                                    "ADC_DIG_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_INT_LOW_EN_OFFSET, \
                                    ADC_DIG_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_INT_LOW_EN_RD_MASK, ADC_DIG_INT_LOW_EN_WR_MASK, \
                                    "ADC_DIG_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_INT_CLR_OFFSET, \
                                    ADC_DIG_INT_CLR_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_INT_CLR_RD_MASK, ADC_DIG_INT_CLR_WR_MASK, \
                                    "ADC_DIG_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_INT_FORCE_OFFSET, \
                                    ADC_DIG_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_INT_FORCE_RD_MASK, ADC_DIG_INT_FORCE_WR_MASK, \
                                    "ADC_DIG_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM0_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM0_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM0_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM0_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM1_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM1_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM1_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM1_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM2_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM2_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM2_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM2_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM3_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM3_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM3_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM3_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM4_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM4_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM4_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM4_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM5_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM5_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM5_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM5_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM6_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM6_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM6_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM6_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM7_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM7_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM7_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM7_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM8_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM8_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM8_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM8_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM9_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM9_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM9_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM9_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM10_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM10_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM10_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM10_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM11_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM11_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM11_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM11_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM12_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM12_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM12_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM12_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM13_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM13_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM13_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM13_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM14_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM14_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM14_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM14_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM15_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM15_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM15_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM15_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM16_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM16_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM16_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM16_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM17_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM17_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM17_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM17_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM18_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM18_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM18_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM18_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM19_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM19_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM19_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM19_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM20_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM20_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM20_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM20_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM21_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM21_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM21_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM21_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM22_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM22_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM22_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM22_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM23_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM23_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM23_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM23_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM24_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM24_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM24_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM24_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM25_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM25_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM25_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM25_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM26_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM26_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM26_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM26_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM27_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM27_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM27_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM27_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM28_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM28_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM28_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM28_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM29_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM29_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM29_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM29_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM30_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM30_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM30_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM30_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM31_CMD_DATA_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_DATA_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM31_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_MEM31_CMD_AW_OFFSET, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_MEM_CMD_AW_RD_MASK, ADC_DIG_CAL_SEQ_MEM_CMD_AW_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_MEM31_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCRATCHPAD_OFFSET, \
                                    ADC_DIG_SCRATCHPAD_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCRATCHPAD_RD_MASK, ADC_DIG_SCRATCHPAD_WR_MASK, \
                                    "ADC_DIG_SCRATCHPAD_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CFG_OFFSET, \
                                    ADC_DIG_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CFG_RD_MASK, ADC_DIG_CFG_WR_MASK, \
                                    "ADC_DIG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_ITER_OFFSET, \
                                    ADC_DIG_CAL_SEQ_ITER_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_ITER_RD_MASK, ADC_DIG_CAL_SEQ_ITER_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_ITER_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_CFG_OFFSET, \
                                    ADC_DIG_OSS_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_CFG_RD_MASK, ADC_DIG_OSS_CFG_WR_MASK, \
                                    "ADC_DIG_OSS_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_CFG2_OFFSET, \
                                    ADC_DIG_OSS_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_CFG_RD_MASK, ADC_DIG_OSS_CFG_WR_MASK, \
                                    "ADC_DIG_OSS_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_LFSR_INIT_OFFSET, \
                                    ADC_DIG_OSS_LFSR_INIT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_LFSR_INIT_RD_MASK, ADC_DIG_OSS_LFSR_INIT_WR_MASK, \
                                    "ADC_DIG_OSS_LFSR_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCHED_CTRL_SHDW_OFFSET, \
                                    ADC_DIG_SCHED_CTRL_SHDW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCHED_CTRL_SHDW_RD_MASK, ADC_DIG_SCHED_CTRL_SHDW_WR_MASK, \
                                    "ADC_DIG_SCHED_CTRL_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_DSA_SHDW_OFFSET, \
                                    ADC_DIG_DSA_SHDW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_DSA_SHDW_RD_MASK, ADC_DIG_DSA_SHDW_WR_MASK, \
                                    "ADC_DIG_DSA_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_CTRL_SHDW_OFFSET, \
                                    ADC_DIG_OSS_CTRL_SHDW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_CTRL_SHDW_RD_MASK, ADC_DIG_OSS_CTRL_SHDW_WR_MASK, \
                                    "ADC_DIG_OSS_CTRL_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCFG0_OFFSET, \
                                    ADC_DIG_SCFG0_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCFG0_RD_MASK, ADC_DIG_SCFG0_WR_MASK, \
                                    "ADC_DIG_SCFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCFG1_OFFSET, \
                                    ADC_DIG_SCFG1_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCFG1_RD_MASK, ADC_DIG_SCFG1_WR_MASK, \
                                    "ADC_DIG_SCFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCFG2_OFFSET, \
                                    ADC_DIG_SCFG2_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCFG2_RD_MASK, ADC_DIG_SCFG2_WR_MASK, \
                                    "ADC_DIG_SCFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCFG3_OFFSET, \
                                    ADC_DIG_SCFG3_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCFG3_RD_MASK, ADC_DIG_SCFG3_WR_MASK, \
                                    "ADC_DIG_SCFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_CFG_OFFSET, \
                                    ADC_DIG_FIFO_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_CFG_RD_MASK, ADC_DIG_FIFO_CFG_WR_MASK, \
                                    "ADC_DIG_FIFO_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_BSG_DC_INCR_OFFSET, \
                                    ADC_DIG_BSG_DC_INCR_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_BSG_DC_INCR_RD_MASK, ADC_DIG_BSG_DC_INCR_WR_MASK, \
                                    "ADC_DIG_BSG_DC_INCR_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_CTRL_OFFSET, \
                                    ADC_DIG_CAL_SEQ_CTRL_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_CTRL_RD_MASK, ADC_DIG_CAL_SEQ_CTRL_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_CLR_OFFSET, \
                                    ADC_DIG_FIFO_CLR_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_CLR_RD_MASK, ADC_DIG_FIFO_CLR_WR_MASK, \
                                    "ADC_DIG_FIFO_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PAUSE_CFG_OFFSET, \
                                    ADC_DIG_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PAUSE_CFG_RD_MASK, ADC_DIG_PAUSE_CFG_WR_MASK, \
                                    "ADC_DIG_PAUSE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCHED_CTRL_LIVE_OFFSET, \
                                    ADC_DIG_SCHED_CTRL_LIVE_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCHED_CTRL_LIVE_RD_MASK, ADC_DIG_SCHED_CTRL_LIVE_WR_MASK, \
                                    "ADC_DIG_SCHED_CTRL_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_DSA_LIVE_OFFSET, \
                                    ADC_DIG_DSA_LIVE_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_DSA_LIVE_RD_MASK, ADC_DIG_DSA_LIVE_WR_MASK, \
                                    "ADC_DIG_DSA_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_CTRL_LIVE_OFFSET, \
                                    ADC_DIG_OSS_CTRL_LIVE_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_CTRL_LIVE_RD_MASK, ADC_DIG_OSS_CTRL_LIVE_WR_MASK, \
                                    "ADC_DIG_OSS_CTRL_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_APB_BRDG_STAT_OFFSET, \
                                    ADC_DIG_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_APB_BRDG_STAT_RD_MASK, ADC_DIG_APB_BRDG_STAT_WR_MASK, \
                                    "ADC_DIG_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_CAL_SEQ_CMD_DATA_OFFSET, \
                                    ADC_DIG_PROT_STAT_CAL_SEQ_CMD_DATA_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_CAL_SEQ_CMD_DATA_RD_MASK, ADC_DIG_PROT_STAT_CAL_SEQ_CMD_DATA_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_CAL_SEQ_CMD_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_CAL_SEQ_CMD_AW_OFFSET, \
                                    ADC_DIG_PROT_STAT_CAL_SEQ_CMD_AW_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_CAL_SEQ_CMD_AW_RD_MASK, ADC_DIG_PROT_STAT_CAL_SEQ_CMD_AW_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_CAL_SEQ_CMD_AW_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PROT_STAT_REGISTER_OFFSET, \
                                    ADC_DIG_PROT_STAT_REGISTER_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PROT_STAT_REGISTER_RD_MASK, ADC_DIG_PROT_STAT_REGISTER_WR_MASK, \
                                    "ADC_DIG_PROT_STAT_REGISTER_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_COLLISION_STAT_OFFSET, \
                                    ADC_DIG_CAL_COLLISION_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_COLLISION_STAT_RD_MASK, ADC_DIG_CAL_COLLISION_STAT_WR_MASK, \
                                    "ADC_DIG_CAL_COLLISION_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_SCHED_STAT_OFFSET, \
                                    ADC_DIG_SCHED_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_SCHED_STAT_RD_MASK, ADC_DIG_SCHED_STAT_WR_MASK, \
                                    "ADC_DIG_SCHED_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_PAUSE_STAT_OFFSET, \
                                    ADC_DIG_PAUSE_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_PAUSE_STAT_RD_MASK, ADC_DIG_PAUSE_STAT_WR_MASK, \
                                    "ADC_DIG_PAUSE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OBS_FIFO_STAT_OFFSET, \
                                    ADC_DIG_OBS_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OBS_FIFO_STAT_RD_MASK, ADC_DIG_OBS_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_OBS_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_CAL_SEQ_STAT_OFFSET, \
                                    ADC_DIG_CAL_SEQ_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_CAL_SEQ_STAT_RD_MASK, ADC_DIG_CAL_SEQ_STAT_WR_MASK, \
                                    "ADC_DIG_CAL_SEQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_OSS_STAT_OFFSET, \
                                    ADC_DIG_OSS_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_OSS_STAT_RD_MASK, ADC_DIG_OSS_STAT_WR_MASK, \
                                    "ADC_DIG_OSS_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT0_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT1_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT2_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT3_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT4_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT5_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT6_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT7_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT8_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT9_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT10_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT10_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT11_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT11_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT12_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT12_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT13_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT13_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT14_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT14_OFFSET");

            write_read_expect_18a(base_address[i]+ADC_DIG_FIFO_STAT15_OFFSET, \
                                    ADC_DIG_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ADC_DIG_FIFO_STAT_RD_MASK, ADC_DIG_FIFO_STAT_WR_MASK, \
                                    "ADC_DIG_FIFO_STAT15_OFFSET");

        }

    }

}
