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
    int i,j;
    init();

   uint32_t base_address1[] = {
    FB_ANT0_NLEQ0_BASE, FB_ANT0_NLEQ1_BASE, FB_ANT1_NLEQ0_BASE, FB_ANT1_NLEQ1_BASE};

    uint32_t base_address2[] = {
    TRX_ANT0_NLEQ0_BASE,TRX_ANT0_NLEQ1_BASE, TRX_ANT1_NLEQ0_BASE, TRX_ANT1_NLEQ1_BASE, TRX_ANT2_NLEQ0_BASE, TRX_ANT2_NLEQ1_BASE,
    TRX_ANT3_NLEQ0_BASE, TRX_ANT3_NLEQ1_BASE, TRX_ANT4_NLEQ0_BASE, TRX_ANT4_NLEQ1_BASE, TRX_ANT5_NLEQ0_BASE,
    TRX_ANT5_NLEQ1_BASE, TRX_ANT6_NLEQ0_BASE, TRX_ANT6_NLEQ1_BASE, TRX_ANT7_NLEQ0_BASE, TRX_ANT7_NLEQ1_BASE
    };

    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {

        for(j=0; j<size[i]; j++)
        {
            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW0_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW1_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW2_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW3_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW4_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW5_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW6_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW7_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW8_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW9_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW10_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW11_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW12_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW13_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW14_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_DC_SHDW_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_DC_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_DC_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW0_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW1_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW2_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW3_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW4_OFFSET, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_DEFAULT, \
                                        NLEQ_C_SLICE_SHDW_C_LINEAR_SHDW_RD_MASK, "NLEQ_C_SLICE_SHDW15_C_LINEAR_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW0_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW1_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW2_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW3_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW4_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW5_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_SQUARE_SHDW5_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW0_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW1_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW2_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW3_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW4_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW5_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW5_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW6_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW6_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW7_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW7_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW8_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW8_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW9_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW9_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW10_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW10_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW11_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW11_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW12_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW12_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW13_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW13_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW14_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW14_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW15_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW15_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW16_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW16_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW17_OFFSET, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_DEFAULT, \
                                        NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW_RD_MASK, "NLEQ_C_BUFF_SHDW_C_CUBIC_SHDW17_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE0_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE1_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE2_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE3_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE4_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE5_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE6_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE7_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE8_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE9_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE10_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE11_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE12_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE13_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE14_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_DC_LIVE_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_DC_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_DC_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE0_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE1_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE2_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE3_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE4_OFFSET, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_DEFAULT, \
                                        NLEQ_C_SLICE_LIVE_C_LINEAR_LIVE_RD_MASK, "NLEQ_C_SLICE_LIVE15_C_LINEAR_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE0_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE1_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE2_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE3_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE4_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE5_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_SQUARE_LIVE5_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE0_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE1_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE2_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE3_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE3_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE4_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE4_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE5_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE5_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE6_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE6_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE7_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE7_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE8_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE8_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE9_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE9_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE10_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE10_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE11_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE11_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE12_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE12_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE13_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE13_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE14_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE14_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE15_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE15_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE16_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE16_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE17_OFFSET, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_DEFAULT, \
                                        NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE_RD_MASK, "NLEQ_C_BUFF_LIVE_C_CUBIC_LIVE17_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_SCRATCH_OFFSET, \
                                        NLEQ_SCRATCH_DEFAULT, \
                                        NLEQ_SCRATCH_RD_MASK, "NLEQ_SCRATCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_CFG_OFFSET, \
                                        NLEQ_CFG_DEFAULT, \
                                        NLEQ_CFG_RD_MASK, "NLEQ_CFG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_CTRL_OFFSET, \
                                        NLEQ_CTRL_DEFAULT, \
                                        NLEQ_CTRL_RD_MASK, "NLEQ_CTRL_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_CSR_CFG_OFFSET, \
                                        NLEQ_CSR_CFG_DEFAULT, \
                                        NLEQ_CSR_CFG_RD_MASK, "NLEQ_CSR_CFG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_CSR_ERR_OFFSET, \
                                        NLEQ_CSR_ERR_DEFAULT, \
                                        NLEQ_CSR_ERR_RD_MASK, "NLEQ_CSR_ERR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_COEFF_EN_NORMAL_OFFSET, \
                                        NLEQ_COEFF_EN_NORMAL_DEFAULT, \
                                        NLEQ_COEFF_EN_NORMAL_RD_MASK, "NLEQ_COEFF_EN_NORMAL_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_COEFF_EN_LP0_OFFSET, \
                                        NLEQ_COEFF_EN_LP0_DEFAULT, \
                                        NLEQ_COEFF_EN_LP0_RD_MASK, "NLEQ_COEFF_EN_LP0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_COEFF_EN_LP1_OFFSET, \
                                        NLEQ_COEFF_EN_LP1_DEFAULT, \
                                        NLEQ_COEFF_EN_LP1_RD_MASK, "NLEQ_COEFF_EN_LP1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_SPWR_INIT_OFFSET, \
                                        NLEQ_LP_SPWR_INIT_DEFAULT, \
                                        NLEQ_LP_SPWR_INIT_RD_MASK, "NLEQ_LP_SPWR_INIT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_FPWR_INIT_OFFSET, \
                                        NLEQ_LP_FPWR_INIT_DEFAULT, \
                                        NLEQ_LP_FPWR_INIT_RD_MASK, "NLEQ_LP_FPWR_INIT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_THR_L0_OFFSET, \
                                        NLEQ_LP_THR_L0_DEFAULT, \
                                        NLEQ_LP_THR_L0_RD_MASK, "NLEQ_LP_THR_L0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_THR_H0_OFFSET, \
                                        NLEQ_LP_THR_H0_DEFAULT, \
                                        NLEQ_LP_THR_H0_RD_MASK, "NLEQ_LP_THR_H0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_THR_L1_OFFSET, \
                                        NLEQ_LP_THR_L1_DEFAULT, \
                                        NLEQ_LP_THR_L1_RD_MASK, "NLEQ_LP_THR_L1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_THR_H1_OFFSET, \
                                        NLEQ_LP_THR_H1_DEFAULT, \
                                        NLEQ_LP_THR_H1_RD_MASK, "NLEQ_LP_THR_H1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_DBG0_OFFSET, \
                                        NLEQ_LP_DBG0_DEFAULT, \
                                        NLEQ_LP_DBG0_RD_MASK, "NLEQ_LP_DBG0_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_LP_DBG1_OFFSET, \
                                        NLEQ_LP_DBG1_DEFAULT, \
                                        NLEQ_LP_DBG1_RD_MASK, "NLEQ_LP_DBG1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_INT_STAT_OFFSET, \
                                        NLEQ_INT_STAT_DEFAULT, \
                                        NLEQ_INT_STAT_RD_MASK, "NLEQ_INT_STAT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_INT_HIGH_EN_OFFSET, \
                                        NLEQ_INT_HIGH_EN_DEFAULT, \
                                        NLEQ_INT_HIGH_EN_RD_MASK, "NLEQ_INT_HIGH_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_INT_LOW_EN_OFFSET, \
                                        NLEQ_INT_LOW_EN_DEFAULT, \
                                        NLEQ_INT_LOW_EN_RD_MASK, "NLEQ_INT_LOW_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_INT_CLR_OFFSET, \
                                        NLEQ_INT_CLR_DEFAULT, \
                                        NLEQ_INT_CLR_RD_MASK, "NLEQ_INT_CLR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_INT_FORCE_OFFSET, \
                                        NLEQ_INT_FORCE_DEFAULT, \
                                        NLEQ_INT_FORCE_RD_MASK, "NLEQ_INT_FORCE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+NLEQ_APB_BRDG_STAT_OFFSET, \
                                        NLEQ_APB_BRDG_STAT_DEFAULT, \
                                        NLEQ_APB_BRDG_STAT_RD_MASK, "NLEQ_APB_BRDG_STAT_OFFSET");
        }

    }

}
