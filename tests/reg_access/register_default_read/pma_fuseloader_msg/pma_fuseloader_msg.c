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
    DLNK_JESD0_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD1_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD2_PHY_PMA0_FUSELOADER_BASE, DLNK_JESD3_PHY_PMA0_FUSELOADER_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_CTRL_STAT_OFFSET, \
                                    PMA_FUSELOADER_MSG_CTRL_STAT_DEFAULT, \
                                    PMA_FUSELOADER_MSG_CTRL_STAT_RD_MASK, "PMA_FUSELOADER_MSG_CTRL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_CTRL_OFFSET, \
                                    PMA_FUSELOADER_MSG_CTRL_DEFAULT, \
                                    PMA_FUSELOADER_MSG_CTRL_RD_MASK, "PMA_FUSELOADER_MSG_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_0_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_0_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_0_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_0_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_0_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_0_RD_MASK, "PMA_FUSELOADER_MSG_VAL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_1_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_1_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_1_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_1_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_1_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_1_RD_MASK, "PMA_FUSELOADER_MSG_VAL_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_2_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_2_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_2_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_2_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_2_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_2_RD_MASK, "PMA_FUSELOADER_MSG_VAL_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_3_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_3_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_3_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_3_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_3_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_3_RD_MASK, "PMA_FUSELOADER_MSG_VAL_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_4_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_4_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_4_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_4_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_4_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_4_RD_MASK, "PMA_FUSELOADER_MSG_VAL_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_5_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_5_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_5_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_5_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_5_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_5_RD_MASK, "PMA_FUSELOADER_MSG_VAL_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_6_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_6_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_6_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_6_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_6_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_6_RD_MASK, "PMA_FUSELOADER_MSG_VAL_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_ADDR_7_OFFSET, \
                                    PMA_FUSELOADER_MSG_ADDR_7_DEFAULT, \
                                    PMA_FUSELOADER_MSG_ADDR_7_RD_MASK, "PMA_FUSELOADER_MSG_ADDR_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_FUSELOADER_MSG_VAL_7_OFFSET, \
                                    PMA_FUSELOADER_MSG_VAL_7_DEFAULT, \
                                    PMA_FUSELOADER_MSG_VAL_7_RD_MASK, "PMA_FUSELOADER_MSG_VAL_7_OFFSET");

    }

}
