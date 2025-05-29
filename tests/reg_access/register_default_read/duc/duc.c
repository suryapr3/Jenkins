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
    TRX_SYS0_DUC0_BASE, TRX_SYS0_DUC1_BASE, TRX_SYS1_DUC0_BASE, TRX_SYS1_DUC1_BASE, TRX_SYS2_DUC0_BASE,
    TRX_SYS2_DUC1_BASE, TRX_SYS3_DUC0_BASE, TRX_SYS3_DUC1_BASE, TRX_SYS4_DUC0_BASE, TRX_SYS4_DUC1_BASE,
    TRX_SYS5_DUC0_BASE, TRX_SYS5_DUC1_BASE, TRX_SYS6_DUC0_BASE, TRX_SYS6_DUC1_BASE, TRX_SYS7_DUC0_BASE,
    TRX_SYS7_DUC1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+DUC_SCRATCH_OFFSET, \
                                    DUC_SCRATCH_DEFAULT, \
                                    DUC_SCRATCH_RD_MASK, "DUC_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+DUC_CFG_OFFSET, \
                                    DUC_CFG_DEFAULT, \
                                    DUC_CFG_RD_MASK, "DUC_CFG_OFFSET");


//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+DUC_STAT_OFFSET, \
                                    DUC_STAT_DEFAULT, \
                                    DUC_STAT_RD_MASK, "DUC_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+DUC_APB_BRDG_STAT_OFFSET, \
                                    DUC_APB_BRDG_STAT_DEFAULT, \
                                    DUC_APB_BRDG_STAT_RD_MASK, "DUC_APB_BRDG_STAT_OFFSET");

    }

}
