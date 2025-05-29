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
    DLNK_JESD0_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD1_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD2_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD3_PHY_PCS_SERDES_CMN_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_REVISION_OFFSET, \
                                    PCS_SERDES_CMN_MSG_REVISION_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_REVISION_RD_MASK, "PCS_SERDES_CMN_MSG_REVISION_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_JTAG_VER_OFFSET, \
                                    PCS_SERDES_CMN_MSG_JTAG_VER_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_JTAG_VER_RD_MASK, "PCS_SERDES_CMN_MSG_JTAG_VER_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_RD_MASK, "PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_RD_MASK, "PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_0_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_0_RD_MASK, "PCS_SERDES_CMN_MSG_RW_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_1_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_1_RD_MASK, "PCS_SERDES_CMN_MSG_RW_SPARE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_2_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_2_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_2_RD_MASK, "PCS_SERDES_CMN_MSG_RW_SPARE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_3_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_3_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_3_RD_MASK, "PCS_SERDES_CMN_MSG_RW_SPARE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RO_SPARE_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_0_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_0_RD_MASK, "PCS_SERDES_CMN_MSG_RO_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RO_SPARE_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_1_DEFAULT, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_1_RD_MASK, "PCS_SERDES_CMN_MSG_RO_SPARE_1_OFFSET");

    }

}
