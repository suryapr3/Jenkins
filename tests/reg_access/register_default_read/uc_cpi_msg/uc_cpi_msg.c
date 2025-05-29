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
    DLNK_JESD0_PHY_UC_CPI0_BASE, DLNK_JESD0_PHY_UC_CPI1_BASE, DLNK_JESD0_PHY_UC_CPI2_BASE, DLNK_JESD1_PHY_UC_CPI0_BASE, DLNK_JESD1_PHY_UC_CPI1_BASE,
    DLNK_JESD1_PHY_UC_CPI2_BASE, DLNK_JESD2_PHY_UC_CPI0_BASE, DLNK_JESD2_PHY_UC_CPI1_BASE, DLNK_JESD2_PHY_UC_CPI2_BASE, DLNK_JESD3_PHY_UC_CPI0_BASE,
    DLNK_JESD3_PHY_UC_CPI1_BASE, DLNK_JESD3_PHY_UC_CPI2_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_LM_CMD_DATA_OFFSET, \
                                    UC_CPI_MSG_CPI_LM_CMD_DATA_DEFAULT, \
                                    UC_CPI_MSG_CPI_LM_CMD_DATA_RD_MASK, "UC_CPI_MSG_CPI_LM_CMD_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_PHY_CMD_DATA_OFFSET, \
                                    UC_CPI_MSG_CPI_PHY_CMD_DATA_DEFAULT, \
                                    UC_CPI_MSG_CPI_PHY_CMD_DATA_RD_MASK, "UC_CPI_MSG_CPI_PHY_CMD_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_PHY_OWNER_OFFSET, \
                                    UC_CPI_MSG_CPI_PHY_OWNER_DEFAULT, \
                                    UC_CPI_MSG_CPI_PHY_OWNER_RD_MASK, "UC_CPI_MSG_CPI_PHY_OWNER_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_RESERVED_OFFSET, \
                                    UC_CPI_MSG_CPI_RESERVED_DEFAULT, \
                                    UC_CPI_MSG_CPI_RESERVED_RD_MASK, "UC_CPI_MSG_CPI_RESERVED_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_STAT_0_OFFSET, \
                                    UC_CPI_MSG_CPI_STAT_0_DEFAULT, \
                                    UC_CPI_MSG_CPI_STAT_0_RD_MASK, "UC_CPI_MSG_CPI_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_STAT_1_OFFSET, \
                                    UC_CPI_MSG_CPI_STAT_1_DEFAULT, \
                                    UC_CPI_MSG_CPI_STAT_1_RD_MASK, "UC_CPI_MSG_CPI_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_CPI_MSG_CPI_STAT_2_OFFSET, \
                                    UC_CPI_MSG_CPI_STAT_2_DEFAULT, \
                                    UC_CPI_MSG_CPI_STAT_2_RD_MASK, "UC_CPI_MSG_CPI_STAT_2_OFFSET");

    }

}
