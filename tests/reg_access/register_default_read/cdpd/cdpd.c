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
    TRX_ANT0_CDPD0_BASE, TRX_ANT0_CDPD1_BASE, TRX_ANT1_CDPD0_BASE, TRX_ANT1_CDPD1_BASE, TRX_ANT2_CDPD0_BASE,
    TRX_ANT2_CDPD1_BASE, TRX_ANT3_CDPD0_BASE, TRX_ANT3_CDPD1_BASE, TRX_ANT4_CDPD0_BASE, TRX_ANT4_CDPD1_BASE,
    TRX_ANT5_CDPD0_BASE, TRX_ANT5_CDPD1_BASE, TRX_ANT6_CDPD0_BASE, TRX_ANT6_CDPD1_BASE, TRX_ANT7_CDPD0_BASE,
    TRX_ANT7_CDPD1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW0_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW1_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW2_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW3_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW4_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW5_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW6_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW7_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW8_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW9_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW10_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW11_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW12_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW13_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW14_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW15_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW16_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW17_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW18_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW19_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW20_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW21_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW22_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW23_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW24_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW25_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW26_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW27_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW28_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW29_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW30_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW31_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_SHDW32_OFFSET, \
                                    CDPD_D00_SHDW_DEFAULT, \
                                    CDPD_D00_SHDW_RD_MASK, "CDPD_D00_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW0_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW1_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW2_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW3_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW4_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW5_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW6_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW7_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW8_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW9_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW10_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW11_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW12_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW13_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW14_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW15_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW16_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW17_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW18_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW19_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW20_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW21_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW22_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW23_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW24_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW25_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW26_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW27_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW28_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW29_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW30_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW31_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_SHDW32_OFFSET, \
                                    CDPD_D01_SHDW_DEFAULT, \
                                    CDPD_D01_SHDW_RD_MASK, "CDPD_D01_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW0_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW1_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW2_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW3_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW4_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW5_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW6_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW7_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW8_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW9_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW10_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW11_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW12_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW13_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW14_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW15_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW16_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW17_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW18_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW19_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW20_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW21_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW22_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW23_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW24_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW25_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW26_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW27_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW28_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW29_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW30_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW31_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_SHDW32_OFFSET, \
                                    CDPD_D10_SHDW_DEFAULT, \
                                    CDPD_D10_SHDW_RD_MASK, "CDPD_D10_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW0_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW1_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW2_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW3_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW4_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW5_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW6_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW7_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW8_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW9_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW10_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW11_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW12_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW13_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW14_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW15_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW16_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW17_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW18_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW19_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW20_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW21_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW22_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW23_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW24_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW25_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW26_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW27_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW28_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW29_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW30_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW31_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_SHDW32_OFFSET, \
                                    CDPD_D11_SHDW_DEFAULT, \
                                    CDPD_D11_SHDW_RD_MASK, "CDPD_D11_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW0_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW1_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW2_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW3_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW4_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW5_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW6_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW7_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW8_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW9_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW10_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW11_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW12_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW13_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW14_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW15_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW16_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW17_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW18_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW19_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW20_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW21_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW22_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW23_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW24_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW25_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW26_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW27_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW28_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW29_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW30_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW31_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_SHDW32_OFFSET, \
                                    CDPD_D20_SHDW_DEFAULT, \
                                    CDPD_D20_SHDW_RD_MASK, "CDPD_D20_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW0_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW1_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW2_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW3_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW4_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW5_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW6_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW7_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW8_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW9_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW10_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW11_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW12_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW13_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW14_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW15_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW16_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW17_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW18_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW19_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW20_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW21_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW22_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW23_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW24_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW25_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW26_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW27_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW28_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW29_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW30_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW31_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_SHDW32_OFFSET, \
                                    CDPD_D21_SHDW_DEFAULT, \
                                    CDPD_D21_SHDW_RD_MASK, "CDPD_D21_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW0_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW1_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW2_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW3_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW4_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW5_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW6_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW7_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW8_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW9_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW10_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW11_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW12_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW13_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW14_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW15_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW16_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW17_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW18_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW19_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW20_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW21_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW22_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW23_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW24_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW25_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW26_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW27_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW28_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW29_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW30_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW31_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_SHDW32_OFFSET, \
                                    CDPD_D30_SHDW_DEFAULT, \
                                    CDPD_D30_SHDW_RD_MASK, "CDPD_D30_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW0_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW1_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW2_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW3_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW4_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW5_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW6_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW7_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW8_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW9_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW10_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW11_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW12_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW13_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW14_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW15_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW16_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW17_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW18_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW19_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW20_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW21_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW22_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW23_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW24_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW25_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW26_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW27_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW28_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW29_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW30_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW31_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_SHDW32_OFFSET, \
                                    CDPD_D31_SHDW_DEFAULT, \
                                    CDPD_D31_SHDW_RD_MASK, "CDPD_D31_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW0_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW1_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW2_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW3_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW4_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW5_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW6_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW7_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW8_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW9_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW10_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW11_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW12_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW13_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW14_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW15_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW16_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW17_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW18_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW19_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW20_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW21_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW22_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW23_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW24_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW25_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW26_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW27_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW28_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW29_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW30_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW31_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_SHDW32_OFFSET, \
                                    CDPD_D40_SHDW_DEFAULT, \
                                    CDPD_D40_SHDW_RD_MASK, "CDPD_D40_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW0_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW1_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW2_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW3_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW4_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW5_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW6_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW7_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW8_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW9_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW10_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW11_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW12_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW13_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW14_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW15_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW16_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW17_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW18_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW19_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW20_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW21_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW22_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW23_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW24_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW25_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW26_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW27_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW28_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW29_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW30_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW31_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_SHDW32_OFFSET, \
                                    CDPD_D41_SHDW_DEFAULT, \
                                    CDPD_D41_SHDW_RD_MASK, "CDPD_D41_SHDW32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_SHDW0_OFFSET, \
                                    CDPD_F_SHDW_DEFAULT, \
                                    CDPD_F_SHDW_RD_MASK, "CDPD_F_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_SHDW1_OFFSET, \
                                    CDPD_F_SHDW_DEFAULT, \
                                    CDPD_F_SHDW_RD_MASK, "CDPD_F_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_SHDW2_OFFSET, \
                                    CDPD_F_SHDW_DEFAULT, \
                                    CDPD_F_SHDW_RD_MASK, "CDPD_F_SHDW2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_SHDW3_OFFSET, \
                                    CDPD_F_SHDW_DEFAULT, \
                                    CDPD_F_SHDW_RD_MASK, "CDPD_F_SHDW3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_SHDW4_OFFSET, \
                                    CDPD_F_SHDW_DEFAULT, \
                                    CDPD_F_SHDW_RD_MASK, "CDPD_F_SHDW4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_LUT_GAIN_SHDW_OFFSET, \
                                    CDPD_LUT_GAIN_SHDW_DEFAULT, \
                                    CDPD_LUT_GAIN_SHDW_RD_MASK, "CDPD_LUT_GAIN_SHDW_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE0_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE1_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE2_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE3_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE4_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE5_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE6_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE7_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE8_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE9_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE10_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE11_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE12_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE13_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE14_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE15_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE16_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE17_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE18_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE19_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE20_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE21_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE22_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE23_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE24_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE25_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE26_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE27_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE28_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE29_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE30_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE31_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D00_LIVE32_OFFSET, \
                                    CDPD_D00_LIVE_DEFAULT, \
                                    CDPD_D00_LIVE_RD_MASK, "CDPD_D00_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE0_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE1_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE2_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE3_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE4_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE5_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE6_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE7_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE8_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE9_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE10_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE11_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE12_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE13_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE14_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE15_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE16_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE17_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE18_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE19_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE20_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE21_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE22_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE23_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE24_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE25_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE26_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE27_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE28_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE29_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE30_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE31_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D01_LIVE32_OFFSET, \
                                    CDPD_D01_LIVE_DEFAULT, \
                                    CDPD_D01_LIVE_RD_MASK, "CDPD_D01_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE0_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE1_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE2_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE3_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE4_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE5_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE6_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE7_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE8_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE9_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE10_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE11_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE12_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE13_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE14_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE15_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE16_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE17_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE18_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE19_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE20_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE21_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE22_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE23_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE24_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE25_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE26_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE27_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE28_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE29_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE30_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE31_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D10_LIVE32_OFFSET, \
                                    CDPD_D10_LIVE_DEFAULT, \
                                    CDPD_D10_LIVE_RD_MASK, "CDPD_D10_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE0_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE1_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE2_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE3_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE4_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE5_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE6_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE7_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE8_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE9_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE10_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE11_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE12_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE13_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE14_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE15_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE16_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE17_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE18_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE19_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE20_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE21_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE22_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE23_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE24_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE25_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE26_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE27_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE28_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE29_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE30_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE31_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D11_LIVE32_OFFSET, \
                                    CDPD_D11_LIVE_DEFAULT, \
                                    CDPD_D11_LIVE_RD_MASK, "CDPD_D11_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE0_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE1_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE2_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE3_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE4_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE5_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE6_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE7_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE8_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE9_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE10_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE11_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE12_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE13_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE14_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE15_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE16_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE17_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE18_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE19_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE20_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE21_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE22_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE23_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE24_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE25_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE26_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE27_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE28_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE29_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE30_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE31_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D20_LIVE32_OFFSET, \
                                    CDPD_D20_LIVE_DEFAULT, \
                                    CDPD_D20_LIVE_RD_MASK, "CDPD_D20_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE0_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE1_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE2_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE3_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE4_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE5_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE6_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE7_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE8_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE9_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE10_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE11_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE12_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE13_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE14_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE15_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE16_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE17_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE18_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE19_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE20_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE21_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE22_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE23_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE24_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE25_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE26_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE27_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE28_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE29_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE30_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE31_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D21_LIVE32_OFFSET, \
                                    CDPD_D21_LIVE_DEFAULT, \
                                    CDPD_D21_LIVE_RD_MASK, "CDPD_D21_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE0_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE1_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE2_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE3_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE4_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE5_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE6_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE7_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE8_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE9_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE10_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE11_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE12_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE13_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE14_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE15_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE16_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE17_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE18_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE19_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE20_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE21_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE22_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE23_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE24_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE25_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE26_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE27_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE28_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE29_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE30_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE31_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D30_LIVE32_OFFSET, \
                                    CDPD_D30_LIVE_DEFAULT, \
                                    CDPD_D30_LIVE_RD_MASK, "CDPD_D30_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE0_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE1_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE2_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE3_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE4_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE5_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE6_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE7_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE8_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE9_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE10_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE11_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE12_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE13_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE14_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE15_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE16_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE17_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE18_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE19_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE20_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE21_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE22_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE23_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE24_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE25_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE26_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE27_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE28_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE29_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE30_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE31_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D31_LIVE32_OFFSET, \
                                    CDPD_D31_LIVE_DEFAULT, \
                                    CDPD_D31_LIVE_RD_MASK, "CDPD_D31_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE0_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE1_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE2_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE3_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE4_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE5_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE6_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE7_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE8_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE9_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE10_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE11_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE12_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE13_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE14_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE15_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE16_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE17_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE18_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE19_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE20_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE21_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE22_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE23_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE24_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE25_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE26_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE27_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE28_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE29_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE30_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE31_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D40_LIVE32_OFFSET, \
                                    CDPD_D40_LIVE_DEFAULT, \
                                    CDPD_D40_LIVE_RD_MASK, "CDPD_D40_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE0_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE1_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE2_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE3_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE4_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE5_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE5_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE6_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE6_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE7_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE7_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE8_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE8_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE9_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE9_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE10_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE10_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE11_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE11_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE12_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE12_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE13_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE13_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE14_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE14_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE15_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE15_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE16_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE16_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE17_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE17_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE18_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE18_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE19_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE19_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE20_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE20_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE21_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE21_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE22_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE22_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE23_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE23_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE24_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE24_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE25_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE25_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE26_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE26_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE27_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE27_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE28_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE28_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE29_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE29_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE30_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE30_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE31_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE31_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_D41_LIVE32_OFFSET, \
                                    CDPD_D41_LIVE_DEFAULT, \
                                    CDPD_D41_LIVE_RD_MASK, "CDPD_D41_LIVE32_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_LIVE0_OFFSET, \
                                    CDPD_F_LIVE_DEFAULT, \
                                    CDPD_F_LIVE_RD_MASK, "CDPD_F_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_LIVE1_OFFSET, \
                                    CDPD_F_LIVE_DEFAULT, \
                                    CDPD_F_LIVE_RD_MASK, "CDPD_F_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_LIVE2_OFFSET, \
                                    CDPD_F_LIVE_DEFAULT, \
                                    CDPD_F_LIVE_RD_MASK, "CDPD_F_LIVE2_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_LIVE3_OFFSET, \
                                    CDPD_F_LIVE_DEFAULT, \
                                    CDPD_F_LIVE_RD_MASK, "CDPD_F_LIVE3_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_F_LIVE4_OFFSET, \
                                    CDPD_F_LIVE_DEFAULT, \
                                    CDPD_F_LIVE_RD_MASK, "CDPD_F_LIVE4_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_LUT_GAIN_LIVE_OFFSET, \
                                    CDPD_LUT_GAIN_LIVE_DEFAULT, \
                                    CDPD_LUT_GAIN_LIVE_RD_MASK, "CDPD_LUT_GAIN_LIVE_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_SCRATCH_OFFSET, \
                                    CDPD_SCRATCH_DEFAULT, \
                                    CDPD_SCRATCH_RD_MASK, "CDPD_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_CFG_OFFSET, \
                                    CDPD_CFG_DEFAULT, \
                                    CDPD_CFG_RD_MASK, "CDPD_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_CTRL_OFFSET, \
                                    CDPD_CTRL_DEFAULT, \
                                    CDPD_CTRL_RD_MASK, "CDPD_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_TMR_CFG_OFFSET, \
                                    CDPD_TMR_CFG_DEFAULT, \
                                    CDPD_TMR_CFG_RD_MASK, "CDPD_TMR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_TMR_ERR_OFFSET, \
                                    CDPD_TMR_ERR_DEFAULT, \
                                    CDPD_TMR_ERR_RD_MASK, "CDPD_TMR_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_APB_BRDG_STAT_OFFSET, \
                                    CDPD_APB_BRDG_STAT_DEFAULT, \
                                    CDPD_APB_BRDG_STAT_RD_MASK, "CDPD_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_INT_STAT_OFFSET, \
                                    CDPD_INT_STAT_DEFAULT, \
                                    CDPD_INT_STAT_RD_MASK, "CDPD_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_INT_HIGH_EN_OFFSET, \
                                    CDPD_INT_HIGH_EN_DEFAULT, \
                                    CDPD_INT_HIGH_EN_RD_MASK, "CDPD_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_INT_LOW_EN_OFFSET, \
                                    CDPD_INT_LOW_EN_DEFAULT, \
                                    CDPD_INT_LOW_EN_RD_MASK, "CDPD_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_INT_CLR_OFFSET, \
                                    CDPD_INT_CLR_DEFAULT, \
                                    CDPD_INT_CLR_RD_MASK, "CDPD_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CDPD_INT_FORCE_OFFSET, \
                                    CDPD_INT_FORCE_DEFAULT, \
                                    CDPD_INT_FORCE_RD_MASK, "CDPD_INT_FORCE_OFFSET");

    }

}
