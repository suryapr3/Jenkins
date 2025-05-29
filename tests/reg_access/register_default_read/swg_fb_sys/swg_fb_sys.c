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

    uint32_t base_address[] = { FB_SYS0_SWG0_BASE, FB_SYS1_SWG0_BASE };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D0_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D0_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D1_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D1_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D2_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D2_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D3_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D3_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D4_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D4_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER0_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER1_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER2_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER3_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER4_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER5_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER6_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER7_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER8_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER9_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER10_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER11_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER12_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER13_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER14_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_UPPER_2D5_INIT_UPPER15_OFFSET, \
                                        SWG_INIT_UPPER_2D_DEFAULT, \
                                        SWG_INIT_UPPER_2D_RD_MASK, "SWG_INIT_UPPER_2D5_INIT_UPPER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D0_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D0_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D1_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D1_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D2_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D2_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D3_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D3_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D4_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D4_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER0_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER1_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER2_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER3_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER4_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER5_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER6_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER6_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER7_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER7_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER8_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER8_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER9_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER9_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER10_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER10_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER11_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER11_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER12_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER12_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER13_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER13_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER14_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER14_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INIT_LOWER_2D5_INIT_LOWER15_OFFSET, \
                                        SWG_INIT_LOWER_2D_DEFAULT, \
                                        SWG_INIT_LOWER_2D_RD_MASK, "SWG_INIT_LOWER_2D5_INIT_LOWER15_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER0_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER1_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER2_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER3_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER4_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_UPPER5_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER0_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER1_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER2_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER3_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER4_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR_LOWER5_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER0_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER1_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER2_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER3_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER4_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_UPPER5_OFFSET, \
                                        SWG_INCR_UPPER_DEFAULT, \
                                        SWG_INCR_UPPER_RD_MASK, "SWG_INCR1_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER0_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER1_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER2_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER3_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER4_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INCR1_LOWER5_OFFSET, \
                                        SWG_INCR_LOWER_DEFAULT, \
                                        SWG_INCR_LOWER_RD_MASK, "SWG_INCR1_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN0_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN1_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN2_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN3_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN4_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN5_OFFSET, \
                                        SWG_EN_DEFAULT, \
                                        SWG_EN_RD_MASK, "SWG_EN5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_CLR_ERR_OFFSET, \
                                        SWG_PAR_CLR_ERR_DEFAULT, \
                                        SWG_PAR_CLR_ERR_RD_MASK, "SWG_PAR_CLR_ERR_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_TEST_CTRL_OFFSET, \
                                        SWG_PAR_TEST_CTRL_DEFAULT, \
                                        SWG_PAR_TEST_CTRL_RD_MASK, "SWG_PAR_TEST_CTRL_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EN_PER_SWG_OFFSET, \
                                        SWG_EN_PER_SWG_DEFAULT, \
                                        SWG_EN_PER_SWG_RD_MASK, "SWG_EN_PER_SWG_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_EXT_BYP_OFFSET, \
                                        SWG_EXT_BYP_DEFAULT, \
                                        SWG_EXT_BYP_RD_MASK, "SWG_EXT_BYP_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_TMR_CFG_OFFSET, \
                                        SWG_TMR_CFG_DEFAULT, \
                                        SWG_TMR_CFG_RD_MASK, "SWG_TMR_CFG_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_TMR_ERR_OFFSET, \
                                        SWG_TMR_ERR_DEFAULT, \
                                        SWG_TMR_ERR_RD_MASK, "SWG_TMR_ERR_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INT_STAT_OFFSET, \
                                        SWG_INT_STAT_DEFAULT, \
                                        SWG_INT_STAT_RD_MASK, "SWG_INT_STAT_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INT_HIGH_EN_OFFSET, \
                                        SWG_INT_HIGH_EN_DEFAULT, \
                                        SWG_INT_HIGH_EN_RD_MASK, "SWG_INT_HIGH_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INT_LOW_EN_OFFSET, \
                                        SWG_INT_LOW_EN_DEFAULT, \
                                        SWG_INT_LOW_EN_RD_MASK, "SWG_INT_LOW_EN_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INT_CLR_OFFSET, \
                                        SWG_INT_CLR_DEFAULT, \
                                        SWG_INT_CLR_RD_MASK, "SWG_INT_CLR_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_INT_FORCE_OFFSET, \
                                        SWG_INT_FORCE_DEFAULT, \
                                        SWG_INT_FORCE_RD_MASK, "SWG_INT_FORCE_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_TMR_ERR_INCR_UPPER_OFFSET, \
                                        SWG_TMR_ERR_INCR_UPPER_DEFAULT, \
                                        SWG_TMR_ERR_INCR_UPPER_RD_MASK, "SWG_TMR_ERR_INCR_UPPER_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_TMR_ERR_INCR_LOWER_OFFSET, \
                                        SWG_TMR_ERR_INCR_LOWER_DEFAULT, \
                                        SWG_TMR_ERR_INCR_LOWER_RD_MASK, "SWG_TMR_ERR_INCR_LOWER_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_SCRATCH_OFFSET, \
                                        SWG_SCRATCH_DEFAULT, \
                                        SWG_SCRATCH_RD_MASK, "SWG_SCRATCH_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER0_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER1_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER2_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER3_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER4_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_UPPER5_OFFSET, \
                                        SWG_PAR_ERR_INIT_UPPER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_UPPER_RD_MASK, "SWG_PAR_ERR_INIT_UPPER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER0_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER1_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER2_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER3_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER4_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_PAR_ERR_INIT_LOWER5_OFFSET, \
                                        SWG_PAR_ERR_INIT_LOWER_DEFAULT, \
                                        SWG_PAR_ERR_INIT_LOWER_RD_MASK, "SWG_PAR_ERR_INIT_LOWER5_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG0_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG0_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG1_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG1_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG2_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG2_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG3_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG3_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG4_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG4_OFFSET");

            read_reg_expect_18a(base_address[i]+SWG_DUAL_FCW_CFG5_OFFSET, \
                                        SWG_DUAL_FCW_CFG_DEFAULT, \
                                        SWG_DUAL_FCW_CFG_RD_MASK, "SWG_DUAL_FCW_CFG5_OFFSET");


    }

}
