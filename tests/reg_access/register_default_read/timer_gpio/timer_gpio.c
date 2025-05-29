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
    RCS_TIMER_GRP0_GPIO_BASE, RCS_TIMER_GRP1_GPIO_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TIMER_GPIO_CFG_OFFSET, \
                                    TIMER_GPIO_CFG_DEFAULT, \
                                    TIMER_GPIO_CFG_RD_MASK, "TIMER_GPIO_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_DEB_CNT_SEL_OFFSET, \
                                    TIMER_GPIO_DEB_CNT_SEL_DEFAULT, \
                                    TIMER_GPIO_DEB_CNT_SEL_RD_MASK, "TIMER_GPIO_DEB_CNT_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_POLARITY_OFFSET, \
                                    TIMER_GPIO_POLARITY_DEFAULT, \
                                    TIMER_GPIO_POLARITY_RD_MASK, "TIMER_GPIO_POLARITY_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_INOUT_OFFSET, \
                                    TIMER_GPIO_INOUT_DEFAULT, \
                                    TIMER_GPIO_INOUT_RD_MASK, "TIMER_GPIO_INOUT_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_CURR_OUT_OFFSET, \
                                    TIMER_GPIO_CURR_OUT_DEFAULT, \
                                    TIMER_GPIO_CURR_OUT_RD_MASK, "TIMER_GPIO_CURR_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_CURR_IN_OFFSET, \
                                    TIMER_GPIO_CURR_IN_DEFAULT, \
                                    TIMER_GPIO_CURR_IN_RD_MASK, "TIMER_GPIO_CURR_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_SET_VAL_15_0_OFFSET, \
                                    TIMER_GPIO_SET_VAL_15_0_DEFAULT, \
                                    TIMER_GPIO_SET_VAL_15_0_RD_MASK, "TIMER_GPIO_SET_VAL_15_0_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_SET_VAL_31_16_OFFSET, \
                                    TIMER_GPIO_SET_VAL_31_16_DEFAULT, \
                                    TIMER_GPIO_SET_VAL_31_16_RD_MASK, "TIMER_GPIO_SET_VAL_31_16_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_IN_DELTA_OFFSET, \
                                    TIMER_GPIO_IN_DELTA_DEFAULT, \
                                    TIMER_GPIO_IN_DELTA_RD_MASK, "TIMER_GPIO_IN_DELTA_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_IN_MASK_OFFSET, \
                                    TIMER_GPIO_IN_MASK_DEFAULT, \
                                    TIMER_GPIO_IN_MASK_RD_MASK, "TIMER_GPIO_IN_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_IN_MASKED_DELTA_OFFSET, \
                                    TIMER_GPIO_IN_MASKED_DELTA_DEFAULT, \
                                    TIMER_GPIO_IN_MASKED_DELTA_RD_MASK, "TIMER_GPIO_IN_MASKED_DELTA_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_DR_7_0_OFFSET, \
                                    TIMER_GPIO_DR_7_0_DEFAULT, \
                                    TIMER_GPIO_DR_7_0_RD_MASK, "TIMER_GPIO_DR_7_0_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_DR_15_8_OFFSET, \
                                    TIMER_GPIO_DR_15_8_DEFAULT, \
                                    TIMER_GPIO_DR_15_8_RD_MASK, "TIMER_GPIO_DR_15_8_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_DR_23_16_OFFSET, \
                                    TIMER_GPIO_DR_23_16_DEFAULT, \
                                    TIMER_GPIO_DR_23_16_RD_MASK, "TIMER_GPIO_DR_23_16_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_DR_31_24_OFFSET, \
                                    TIMER_GPIO_DR_31_24_DEFAULT, \
                                    TIMER_GPIO_DR_31_24_RD_MASK, "TIMER_GPIO_DR_31_24_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_LPR_15_0_OFFSET, \
                                    TIMER_GPIO_LPR_15_0_DEFAULT, \
                                    TIMER_GPIO_LPR_15_0_RD_MASK, "TIMER_GPIO_LPR_15_0_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_LPR_31_16_OFFSET, \
                                    TIMER_GPIO_LPR_31_16_DEFAULT, \
                                    TIMER_GPIO_LPR_31_16_RD_MASK, "TIMER_GPIO_LPR_31_16_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_PDE_15_0_OFFSET, \
                                    TIMER_GPIO_PDE_15_0_DEFAULT, \
                                    TIMER_GPIO_PDE_15_0_RD_MASK, "TIMER_GPIO_PDE_15_0_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_PDE_31_16_OFFSET, \
                                    TIMER_GPIO_PDE_31_16_DEFAULT, \
                                    TIMER_GPIO_PDE_31_16_RD_MASK, "TIMER_GPIO_PDE_31_16_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_PUE_15_0_OFFSET, \
                                    TIMER_GPIO_PUE_15_0_DEFAULT, \
                                    TIMER_GPIO_PUE_15_0_RD_MASK, "TIMER_GPIO_PUE_15_0_OFFSET");

        read_reg_expect_18a(base_address[i]+TIMER_GPIO_PUE_31_16_OFFSET, \
                                    TIMER_GPIO_PUE_31_16_DEFAULT, \
                                    TIMER_GPIO_PUE_31_16_RD_MASK, "TIMER_GPIO_PUE_31_16_OFFSET");

    }

}
