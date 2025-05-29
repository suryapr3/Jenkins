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
    RCS_GPREG_CORE0_BASE, RCS_GPREG_CORE1_BASE, RCS_GPREG_CORE2_BASE, RCS_GPREG_CORE3_BASE, RCS_GPREG_EXT_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+INT_CFG0_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG0_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG0_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG0_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG0_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG0_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG0_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG0_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG1_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG1_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG1_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG1_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG1_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG1_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG1_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG1_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG2_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG2_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG2_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG2_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG2_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG2_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG2_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG2_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG3_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG3_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG3_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG3_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG3_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG3_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG3_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG3_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG4_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG4_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG4_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG4_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG4_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG4_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG4_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG4_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG5_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG5_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG5_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG5_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG5_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG5_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG5_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG5_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG6_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG6_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG6_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG6_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG6_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG6_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG6_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG6_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG7_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG7_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG7_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG7_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG7_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG7_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG7_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG7_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG8_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG8_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG8_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG8_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG8_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG8_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG8_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG8_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG9_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG9_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG9_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG9_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG9_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG9_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG9_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG9_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG10_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG10_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG10_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG10_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG10_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG10_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG10_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG10_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG11_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG11_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG11_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG11_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG11_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG11_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG11_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG11_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG12_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG12_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG12_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG12_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG12_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG12_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG12_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG12_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG13_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG13_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG13_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG13_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG13_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG13_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG13_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG13_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG14_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG14_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG14_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG14_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG14_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG14_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG14_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG14_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG15_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG15_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG15_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG15_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG15_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG15_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG15_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG15_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG16_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG16_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG16_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG16_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG16_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG16_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG16_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG16_GPREG_LVL_IRQ_NOMASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG17_GPREG_LVL_IRQ_STAT_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_STAT_RD_MASK, "INT_CFG17_GPREG_LVL_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG17_GPREG_LVL_IRQ_MASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_MASK_RD_MASK, "INT_CFG17_GPREG_LVL_IRQ_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG17_GPREG_LVL_IRQ_INV_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_INV_RD_MASK, "INT_CFG17_GPREG_LVL_IRQ_INV_OFFSET");

        read_reg_expect_18a(base_address[i]+INT_CFG17_GPREG_LVL_IRQ_NOMASK_OFFSET, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_DEFAULT, \
                                    INT_CFG_GPREG_LVL_IRQ_NOMASK_RD_MASK, "INT_CFG17_GPREG_LVL_IRQ_NOMASK_OFFSET");

    }

}
