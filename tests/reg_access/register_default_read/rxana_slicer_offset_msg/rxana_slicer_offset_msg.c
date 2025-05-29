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
    DLNK_JESD0_PHY_PMA0_RXANA_SLICER_OFFSET_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RXANA_SLICER_OFFSET_Q0_BASE, DLNK_JESD0_PHY_PMA0_RXANA_SLICER_OFFSET_Q1_BASE, DLNK_JESD0_PHY_PMA0_RXANA_SLICER_OFFSET_Q2_BASE, DLNK_JESD0_PHY_PMA0_RXANA_SLICER_OFFSET_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RXANA_SLICER_OFFSET_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RXANA_SLICER_OFFSET_Q0_BASE, DLNK_JESD1_PHY_PMA0_RXANA_SLICER_OFFSET_Q1_BASE, DLNK_JESD1_PHY_PMA0_RXANA_SLICER_OFFSET_Q2_BASE, DLNK_JESD1_PHY_PMA0_RXANA_SLICER_OFFSET_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RXANA_SLICER_OFFSET_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RXANA_SLICER_OFFSET_Q0_BASE, DLNK_JESD2_PHY_PMA0_RXANA_SLICER_OFFSET_Q1_BASE, DLNK_JESD2_PHY_PMA0_RXANA_SLICER_OFFSET_Q2_BASE, DLNK_JESD2_PHY_PMA0_RXANA_SLICER_OFFSET_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RXANA_SLICER_OFFSET_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RXANA_SLICER_OFFSET_Q0_BASE, DLNK_JESD3_PHY_PMA0_RXANA_SLICER_OFFSET_Q1_BASE, DLNK_JESD3_PHY_PMA0_RXANA_SLICER_OFFSET_Q2_BASE, DLNK_JESD3_PHY_PMA0_RXANA_SLICER_OFFSET_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT0_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT1_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT2_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q0_QRT3_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT0_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT1_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT2_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q1_QRT3_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT0_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT1_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT2_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q2_QRT3_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT0_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT1_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT2_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR0_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR1_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR2_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_0_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_0_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_0_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_1_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_1_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_1_RD_MASK, "RXANA_SLICER_OFFSET_MSG_Q3_QRT3_SAR3_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_SLICER_OFFSET_MSG_CTRL_OFFSET, \
                                    RXANA_SLICER_OFFSET_MSG_CTRL_DEFAULT, \
                                    RXANA_SLICER_OFFSET_MSG_CTRL_RD_MASK, "RXANA_SLICER_OFFSET_MSG_CTRL_OFFSET");

    }

}
