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
    RCS_TIMER_GRP0_GPIO_BASE, RCS_TIMER_GRP1_GPIO_BASE
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
            write_read_expect_18a(base_address[i]+TIMER_GPIO_CFG_OFFSET, \
                                    TIMER_GPIO_CFG_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_CFG_RD_MASK, TIMER_GPIO_CFG_WR_MASK, \
                                    "TIMER_GPIO_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_DEB_CNT_SEL_OFFSET, \
                                    TIMER_GPIO_DEB_CNT_SEL_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_DEB_CNT_SEL_RD_MASK, TIMER_GPIO_DEB_CNT_SEL_WR_MASK, \
                                    "TIMER_GPIO_DEB_CNT_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_POLARITY_OFFSET, \
                                    TIMER_GPIO_POLARITY_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_POLARITY_RD_MASK, TIMER_GPIO_POLARITY_WR_MASK, \
                                    "TIMER_GPIO_POLARITY_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_INOUT_OFFSET, \
                                    TIMER_GPIO_INOUT_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_INOUT_RD_MASK, TIMER_GPIO_INOUT_WR_MASK, \
                                    "TIMER_GPIO_INOUT_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_CURR_OUT_OFFSET, \
                                    TIMER_GPIO_CURR_OUT_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_CURR_OUT_RD_MASK, TIMER_GPIO_CURR_OUT_WR_MASK, \
                                    "TIMER_GPIO_CURR_OUT_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_CURR_IN_OFFSET, \
                                    TIMER_GPIO_CURR_IN_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_CURR_IN_RD_MASK, TIMER_GPIO_CURR_IN_WR_MASK, \
                                    "TIMER_GPIO_CURR_IN_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_SET_VAL_15_0_OFFSET, \
                                    TIMER_GPIO_SET_VAL_15_0_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_SET_VAL_15_0_RD_MASK, TIMER_GPIO_SET_VAL_15_0_WR_MASK, \
                                    "TIMER_GPIO_SET_VAL_15_0_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_SET_VAL_31_16_OFFSET, \
                                    TIMER_GPIO_SET_VAL_31_16_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_SET_VAL_31_16_RD_MASK, TIMER_GPIO_SET_VAL_31_16_WR_MASK, \
                                    "TIMER_GPIO_SET_VAL_31_16_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_IN_DELTA_OFFSET, \
                                    TIMER_GPIO_IN_DELTA_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_IN_DELTA_RD_MASK, TIMER_GPIO_IN_DELTA_WR_MASK, \
                                    "TIMER_GPIO_IN_DELTA_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_IN_MASK_OFFSET, \
                                    TIMER_GPIO_IN_MASK_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_IN_MASK_RD_MASK, TIMER_GPIO_IN_MASK_WR_MASK, \
                                    "TIMER_GPIO_IN_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_IN_MASKED_DELTA_OFFSET, \
                                    TIMER_GPIO_IN_MASKED_DELTA_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_IN_MASKED_DELTA_RD_MASK, TIMER_GPIO_IN_MASKED_DELTA_WR_MASK, \
                                    "TIMER_GPIO_IN_MASKED_DELTA_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_DR_7_0_OFFSET, \
                                    TIMER_GPIO_DR_7_0_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_DR_7_0_RD_MASK, TIMER_GPIO_DR_7_0_WR_MASK, \
                                    "TIMER_GPIO_DR_7_0_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_DR_15_8_OFFSET, \
                                    TIMER_GPIO_DR_15_8_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_DR_15_8_RD_MASK, TIMER_GPIO_DR_15_8_WR_MASK, \
                                    "TIMER_GPIO_DR_15_8_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_DR_23_16_OFFSET, \
                                    TIMER_GPIO_DR_23_16_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_DR_23_16_RD_MASK, TIMER_GPIO_DR_23_16_WR_MASK, \
                                    "TIMER_GPIO_DR_23_16_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_DR_31_24_OFFSET, \
                                    TIMER_GPIO_DR_31_24_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_DR_31_24_RD_MASK, TIMER_GPIO_DR_31_24_WR_MASK, \
                                    "TIMER_GPIO_DR_31_24_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_LPR_15_0_OFFSET, \
                                    TIMER_GPIO_LPR_15_0_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_LPR_15_0_RD_MASK, TIMER_GPIO_LPR_15_0_WR_MASK, \
                                    "TIMER_GPIO_LPR_15_0_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_LPR_31_16_OFFSET, \
                                    TIMER_GPIO_LPR_31_16_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_LPR_31_16_RD_MASK, TIMER_GPIO_LPR_31_16_WR_MASK, \
                                    "TIMER_GPIO_LPR_31_16_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_PDE_15_0_OFFSET, \
                                    TIMER_GPIO_PDE_15_0_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_PDE_15_0_RD_MASK, TIMER_GPIO_PDE_15_0_WR_MASK, \
                                    "TIMER_GPIO_PDE_15_0_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TIMER_GPIO_PDE_31_16_OFFSET, \
                                    TIMER_GPIO_PDE_31_16_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_PDE_31_16_RD_MASK, TIMER_GPIO_PDE_31_16_WR_MASK, \
                                    "TIMER_GPIO_PDE_31_16_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_PUE_15_0_OFFSET, \
                                    TIMER_GPIO_PUE_15_0_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_PUE_15_0_RD_MASK, TIMER_GPIO_PUE_15_0_WR_MASK, \
                                    "TIMER_GPIO_PUE_15_0_OFFSET");

            write_read_expect_18a(base_address[i]+TIMER_GPIO_PUE_31_16_OFFSET, \
                                    TIMER_GPIO_PUE_31_16_DEFAULT, write_data, expected_data, \
                                    TIMER_GPIO_PUE_31_16_RD_MASK, TIMER_GPIO_PUE_31_16_WR_MASK, \
                                    "TIMER_GPIO_PUE_31_16_OFFSET");

        }

    }

}
