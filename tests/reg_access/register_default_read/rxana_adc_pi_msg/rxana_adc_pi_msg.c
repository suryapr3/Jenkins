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
    DLNK_JESD0_PHY_PMA0_RXANA_ADC_PI_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_PI_Q0_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_PI_Q1_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_PI_Q2_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_PI_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RXANA_ADC_PI_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_PI_Q0_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_PI_Q1_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_PI_Q2_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_PI_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RXANA_ADC_PI_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_PI_Q0_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_PI_Q1_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_PI_Q2_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_PI_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RXANA_ADC_PI_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_PI_Q0_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_PI_Q1_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_PI_Q2_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_PI_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PHASE_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PHASE_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PHASE_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PHASE_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PHASE_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PREBUF_OFC_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_OFC_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_OFC_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PREBUF_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q0_PREBUF_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PHASE_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PHASE_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PHASE_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PHASE_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PHASE_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PREBUF_OFC_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_OFC_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_OFC_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PREBUF_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q1_PREBUF_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PHASE_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PHASE_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PHASE_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PHASE_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PHASE_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PREBUF_OFC_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_OFC_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_OFC_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PREBUF_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q2_PREBUF_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PHASE_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PHASE_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PHASE_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PHASE_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PHASE_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PREBUF_OFC_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_OFC_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_OFC_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PREBUF_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL1_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL1_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL1_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL2_OFFSET, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL2_DEFAULT, \
                                    RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL2_RD_MASK, "RXANA_ADC_PI_MSG_Q3_PREBUF_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_SHARED_CTRL0_OFFSET, \
                                    RXANA_ADC_PI_MSG_SHARED_CTRL0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_SHARED_CTRL0_RD_MASK, "RXANA_ADC_PI_MSG_SHARED_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_PI_MSG_SPARE0_OFFSET, \
                                    RXANA_ADC_PI_MSG_SPARE0_DEFAULT, \
                                    RXANA_ADC_PI_MSG_SPARE0_RD_MASK, "RXANA_ADC_PI_MSG_SPARE0_OFFSET");

    }

}
