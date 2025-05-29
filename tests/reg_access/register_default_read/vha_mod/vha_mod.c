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
    VHA0_ANT0_MOD_BASE, VHA0_ANT1_MOD_BASE, VHA1_ANT0_MOD_BASE, VHA1_ANT1_MOD_BASE, VHA2_ANT0_MOD_BASE,
    VHA2_ANT1_MOD_BASE, VHA3_ANT0_MOD_BASE, VHA3_ANT1_MOD_BASE, VHA4_ANT0_MOD_BASE, VHA4_ANT1_MOD_BASE,
    VHA5_ANT0_MOD_BASE, VHA5_ANT1_MOD_BASE, VHA6_ANT0_MOD_BASE, VHA6_ANT1_MOD_BASE, VHA7_ANT0_MOD_BASE,
    VHA7_ANT1_MOD_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+VHA_MOD_SCRATCH_OFFSET, \
                                    VHA_MOD_SCRATCH_DEFAULT, \
                                    VHA_MOD_SCRATCH_RD_MASK, "VHA_MOD_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_MOD_CFG_OFFSET, \
                                    VHA_MOD_CFG_DEFAULT, \
                                    VHA_MOD_CFG_RD_MASK, "VHA_MOD_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+VHA_MOD_EN_OFFSET, \
                                    VHA_MOD_EN_DEFAULT, \
                                    VHA_MOD_EN_RD_MASK, "VHA_MOD_EN_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+VHA_MOD_APB_BRDG_STAT_OFFSET, \
                                    VHA_MOD_APB_BRDG_STAT_DEFAULT, \
                                    VHA_MOD_APB_BRDG_STAT_RD_MASK, "VHA_MOD_APB_BRDG_STAT_OFFSET");

    }

}
