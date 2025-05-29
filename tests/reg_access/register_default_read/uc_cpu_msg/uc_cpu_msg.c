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
    DLNK_JESD0_PHY_UC_CPU_BASE, DLNK_JESD1_PHY_UC_CPU_BASE, DLNK_JESD2_PHY_UC_CPU_BASE, DLNK_JESD3_PHY_UC_CPU_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_CTRL0_OFFSET, \
                                    UC_CPU_MSG_CPU_CTRL0_DEFAULT, \
                                    UC_CPU_MSG_CPU_CTRL0_RD_MASK, "UC_CPU_MSG_CPU_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_TB0_OFFSET, \
                                    UC_CPU_MSG_CPU_TB0_DEFAULT, \
                                    UC_CPU_MSG_CPU_TB0_RD_MASK, "UC_CPU_MSG_CPU_TB0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_TB1_OFFSET, \
                                    UC_CPU_MSG_CPU_TB1_DEFAULT, \
                                    UC_CPU_MSG_CPU_TB1_RD_MASK, "UC_CPU_MSG_CPU_TB1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_TB2_OFFSET, \
                                    UC_CPU_MSG_CPU_TB2_DEFAULT, \
                                    UC_CPU_MSG_CPU_TB2_RD_MASK, "UC_CPU_MSG_CPU_TB2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_TB3_OFFSET, \
                                    UC_CPU_MSG_CPU_TB3_DEFAULT, \
                                    UC_CPU_MSG_CPU_TB3_RD_MASK, "UC_CPU_MSG_CPU_TB3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_TB4_OFFSET, \
                                    UC_CPU_MSG_CPU_TB4_DEFAULT, \
                                    UC_CPU_MSG_CPU_TB4_RD_MASK, "UC_CPU_MSG_CPU_TB4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_INFO_OFFSET, \
                                    UC_CPU_MSG_CPU_INFO_DEFAULT, \
                                    UC_CPU_MSG_CPU_INFO_RD_MASK, "UC_CPU_MSG_CPU_INFO_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_CTRL1_OFFSET, \
                                    UC_CPU_MSG_CPU_CTRL1_DEFAULT, \
                                    UC_CPU_MSG_CPU_CTRL1_RD_MASK, "UC_CPU_MSG_CPU_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_FW_STAT_OFFSET, \
                                    UC_CPU_MSG_FW_STAT_DEFAULT, \
                                    UC_CPU_MSG_FW_STAT_RD_MASK, "UC_CPU_MSG_FW_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_CTRL2_OFFSET, \
                                    UC_CPU_MSG_CPU_CTRL2_DEFAULT, \
                                    UC_CPU_MSG_CPU_CTRL2_RD_MASK, "UC_CPU_MSG_CPU_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_RAM_CTRL_OFFSET, \
                                    UC_CPU_MSG_RAM_CTRL_DEFAULT, \
                                    UC_CPU_MSG_RAM_CTRL_RD_MASK, "UC_CPU_MSG_RAM_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_IRAM0_OFFSET, \
                                    UC_CPU_MSG_IRAM0_DEFAULT, \
                                    UC_CPU_MSG_IRAM0_RD_MASK, "UC_CPU_MSG_IRAM0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_DRAM0_OFFSET, \
                                    UC_CPU_MSG_DRAM0_DEFAULT, \
                                    UC_CPU_MSG_DRAM0_RD_MASK, "UC_CPU_MSG_DRAM0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_TRACE_OFFSET, \
                                    UC_CPU_MSG_TRACE_DEFAULT, \
                                    UC_CPU_MSG_TRACE_RD_MASK, "UC_CPU_MSG_TRACE_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_FIFO_OFFSET, \
                                    UC_CPU_MSG_FIFO_DEFAULT, \
                                    UC_CPU_MSG_FIFO_RD_MASK, "UC_CPU_MSG_FIFO_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_STAT0_OFFSET, \
                                    UC_CPU_MSG_CPU_STAT0_DEFAULT, \
                                    UC_CPU_MSG_CPU_STAT0_RD_MASK, "UC_CPU_MSG_CPU_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_STAT1_OFFSET, \
                                    UC_CPU_MSG_CPU_STAT1_DEFAULT, \
                                    UC_CPU_MSG_CPU_STAT1_RD_MASK, "UC_CPU_MSG_CPU_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_FIFO_OFFSET, \
                                    UC_CPU_MSG_CPU_FIFO_DEFAULT, \
                                    UC_CPU_MSG_CPU_FIFO_RD_MASK, "UC_CPU_MSG_CPU_FIFO_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_APB_CTRL0_OFFSET, \
                                    UC_CPU_MSG_CPU_APB_CTRL0_DEFAULT, \
                                    UC_CPU_MSG_CPU_APB_CTRL0_RD_MASK, "UC_CPU_MSG_CPU_APB_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPU_MSG_CPU_APB_CTRL1_OFFSET, \
                                    UC_CPU_MSG_CPU_APB_CTRL1_DEFAULT, \
                                    UC_CPU_MSG_CPU_APB_CTRL1_RD_MASK, "UC_CPU_MSG_CPU_APB_CTRL1_OFFSET");

    }

}
