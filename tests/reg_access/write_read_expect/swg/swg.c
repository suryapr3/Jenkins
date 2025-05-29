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
    int i,j;
    init();

    uint32_t base_address1[] = {
    VHA0_DL_SWG_BASE, VHA0_UL_SWG_BASE, VHA1_DL_SWG_BASE, VHA1_UL_SWG_BASE, VHA2_DL_SWG_BASE,
    VHA2_UL_SWG_BASE, VHA3_DL_SWG_BASE, VHA3_UL_SWG_BASE, VHA4_DL_SWG_BASE, VHA4_UL_SWG_BASE,
    VHA5_DL_SWG_BASE, VHA5_UL_SWG_BASE, VHA6_DL_SWG_BASE, VHA6_UL_SWG_BASE, VHA7_DL_SWG_BASE,
    VHA7_UL_SWG_BASE};

    uint32_t base_address2[] = {
    FB_ANT0_SWG_EVEN_BASE, FB_ANT0_SWG_ODD_BASE, FB_ANT1_SWG_EVEN_BASE, FB_ANT1_SWG_ODD_BASE
    };

    uint32_t base_address3[] = { FB_SYS0_SWG0_BASE, FB_SYS1_SWG0_BASE };

    uint32_t* base_addresses[] = {base_address1,base_address2, base_address3};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2), sizeof(base_address3)/(sizeof(base_address3[0])*2)};

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


        for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
        {

            for(j=0; j<size[i]; j++)
            {
                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D0_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D0_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D1_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D1_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D2_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D2_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D3_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D3_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D4_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D4_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_UPPER_2D5_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_UPPER_2D_RD_MASK, SWG_INIT_UPPER_2D_WR_MASK, \
                                        "SWG_INIT_UPPER_2D5_INIT_UPPER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D0_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D0_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D1_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D1_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D2_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D2_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D3_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D3_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D4_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D4_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER9_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER10_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER11_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER12_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER13_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER14_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INIT_LOWER_2D5_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, write_data, expected_data, \
                                        SWG_INIT_LOWER_2D_RD_MASK, SWG_INIT_LOWER_2D_WR_MASK, \
                                        "SWG_INIT_LOWER_2D5_INIT_LOWER15_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER0_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER1_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER2_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER3_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER4_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_UPPER5_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER0_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER1_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER2_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER3_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER4_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR_LOWER5_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER0_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER1_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER2_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER3_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER4_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_UPPER5_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_UPPER_RD_MASK, SWG_INCR_UPPER_WR_MASK, \
                                        "SWG_INCR1_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER0_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER1_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER2_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER3_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER4_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INCR1_LOWER5_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_INCR_LOWER_RD_MASK, SWG_INCR_LOWER_WR_MASK, \
                                        "SWG_INCR1_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN0_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN1_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN2_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN3_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN4_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN5_OFFSET, \
                                        SWG_EN_DEFAULT, write_data, expected_data, \
                                        SWG_EN_RD_MASK, SWG_EN_WR_MASK, \
                                        "SWG_EN5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_CLR_ERR_OFFSET, \
                                        SWG_PAR_CLR_ERR_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_CLR_ERR_RD_MASK, SWG_PAR_CLR_ERR_WR_MASK, \
                                        "SWG_PAR_CLR_ERR_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_TEST_CTRL_OFFSET, \
                                        SWG_PAR_TEST_CTRL_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_TEST_CTRL_RD_MASK, SWG_PAR_TEST_CTRL_WR_MASK, \
                                        "SWG_PAR_TEST_CTRL_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EN_PER_SWG_OFFSET, \
                                        SWG_EN_PER_SWG_DEFAULT, write_data, expected_data, \
                                        SWG_EN_PER_SWG_RD_MASK, SWG_EN_PER_SWG_WR_MASK, \
                                        "SWG_EN_PER_SWG_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_EXT_BYP_OFFSET, \
                                        SWG_EXT_BYP_DEFAULT, write_data, expected_data, \
                                        SWG_EXT_BYP_RD_MASK, SWG_EXT_BYP_WR_MASK, \
                                        "SWG_EXT_BYP_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_TMR_CFG_OFFSET, \
                                        SWG_TMR_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_TMR_CFG_RD_MASK, SWG_TMR_CFG_WR_MASK, \
                                        "SWG_TMR_CFG_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_TMR_ERR_OFFSET, \
                                        SWG_TMR_ERR_DEFAULT, write_data, expected_data, \
                                        SWG_TMR_ERR_RD_MASK, SWG_TMR_ERR_WR_MASK, \
                                        "SWG_TMR_ERR_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INT_STAT_OFFSET, \
                                        SWG_INT_STAT_DEFAULT, write_data, expected_data, \
                                        SWG_INT_STAT_RD_MASK, SWG_INT_STAT_WR_MASK, \
                                        "SWG_INT_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INT_HIGH_EN_OFFSET, \
                                        SWG_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                        SWG_INT_HIGH_EN_RD_MASK, SWG_INT_HIGH_EN_WR_MASK, \
                                        "SWG_INT_HIGH_EN_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INT_LOW_EN_OFFSET, \
                                        SWG_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                        SWG_INT_LOW_EN_RD_MASK, SWG_INT_LOW_EN_WR_MASK, \
                                        "SWG_INT_LOW_EN_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INT_CLR_OFFSET, \
                                        SWG_INT_CLR_DEFAULT, write_data, expected_data, \
                                        SWG_INT_CLR_RD_MASK, SWG_INT_CLR_WR_MASK, \
                                        "SWG_INT_CLR_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_INT_FORCE_OFFSET, \
                                        SWG_INT_FORCE_DEFAULT, write_data, expected_data, \
                                        SWG_INT_FORCE_RD_MASK, SWG_INT_FORCE_WR_MASK, \
                                        "SWG_INT_FORCE_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_TMR_ERR_INCR_UPPER_OFFSET, \
                                        SWG_TMR_ERR_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_TMR_ERR_INCR_UPPER_RD_MASK, SWG_TMR_ERR_INCR_UPPER_WR_MASK, \
                                        "SWG_TMR_ERR_INCR_UPPER_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_TMR_ERR_INCR_LOWER_OFFSET, \
                                        SWG_TMR_ERR_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_TMR_ERR_INCR_LOWER_RD_MASK, SWG_TMR_ERR_INCR_LOWER_WR_MASK, \
                                        "SWG_TMR_ERR_INCR_LOWER_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_SCRATCH_OFFSET, \
                                        SWG_SCRATCH_DEFAULT, write_data, expected_data, \
                                        SWG_SCRATCH_RD_MASK, SWG_SCRATCH_WR_MASK, \
                                        "SWG_SCRATCH_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER0_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER1_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER2_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER3_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER4_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_UPPER5_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, SWG_PAR_ERR_INIT_UPPER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_UPPER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER0_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER1_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER2_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER3_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER4_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_PAR_ERR_INIT_LOWER5_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, SWG_PAR_ERR_INIT_LOWER_WR_MASK, \
                                        "SWG_PAR_ERR_INIT_LOWER5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG0_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG1_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG2_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG3_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG4_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+SWG_DUAL_FCW_CFG5_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, SWG_DUAL_FCW_CFG_WR_MASK, \
                                        "SWG_DUAL_FCW_CFG5_OFFSET");

            }

        }

    }

}
