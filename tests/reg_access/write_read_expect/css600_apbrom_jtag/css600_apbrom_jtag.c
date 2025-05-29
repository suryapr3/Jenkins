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
    SYSCON_CS_SOC_APBROM_APB4_SLAVE_0_MM_BASE
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
            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_RD_MASK, CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_WR_MASK, \
                                    "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_OFFSET");

        }

    }

}
