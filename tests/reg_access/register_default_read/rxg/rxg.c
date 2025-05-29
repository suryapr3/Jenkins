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
    int i,j;
    init();

    uint32_t base_address1[] = {FB_SYS0_RXG0_BASE,  FB_SYS0_RXG1_BASE,  FB_SYS1_RXG0_BASE,  FB_SYS1_RXG1_BASE};

    uint32_t base_address2[] = {TRX_SYS0_RXG0_BASE, TRX_SYS0_RXG1_BASE,  TRX_SYS1_RXG0_BASE,  TRX_SYS1_RXG1_BASE,  TRX_SYS2_RXG0_BASE,  TRX_SYS2_RXG1_BASE,
     TRX_SYS3_RXG0_BASE,  TRX_SYS3_RXG1_BASE,  TRX_SYS4_RXG0_BASE,  TRX_SYS4_RXG1_BASE,  TRX_SYS5_RXG0_BASE,
     TRX_SYS5_RXG1_BASE,  TRX_SYS6_RXG0_BASE,  TRX_SYS6_RXG1_BASE,  TRX_SYS7_RXG0_BASE,  TRX_SYS7_RXG1_BASE
    };

    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {
        for(j=0; j<size[i]; j++)
        {
            read_reg_expect_18a(base_addresses[i][j]+RXG_GAIN_COEFF_SHDW_OFFSET, \
                                        RXG_GAIN_COEFF_SHDW_DEFAULT, \
                                        RXG_GAIN_COEFF_SHDW_RD_MASK, "RXG_GAIN_COEFF_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_GAIN_COEFF_LIVE_OFFSET, \
                                        RXG_GAIN_COEFF_LIVE_DEFAULT, \
                                        RXG_GAIN_COEFF_LIVE_RD_MASK, "RXG_GAIN_COEFF_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_SCRATCH_OFFSET, \
                                        RXG_SCRATCH_DEFAULT, \
                                        RXG_SCRATCH_RD_MASK, "RXG_SCRATCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_BFN_UPDATE_OFFSET, \
                                        RXG_BFN_UPDATE_DEFAULT, \
                                        RXG_BFN_UPDATE_RD_MASK, "RXG_BFN_UPDATE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_SEL_OFFSET, \
                                        RXG_SEL_DEFAULT, \
                                        RXG_SEL_RD_MASK, "RXG_SEL_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_SWITCH_OFFSET, \
                                        RXG_SWITCH_DEFAULT, \
                                        RXG_SWITCH_RD_MASK, "RXG_SWITCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_CSR_CFG_OFFSET, \
                                        RXG_CSR_CFG_DEFAULT, \
                                        RXG_CSR_CFG_RD_MASK, "RXG_CSR_CFG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_CSR_ERR_OFFSET, \
                                        RXG_CSR_ERR_DEFAULT, \
                                        RXG_CSR_ERR_RD_MASK, "RXG_CSR_ERR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_INT_STAT_OFFSET, \
                                        RXG_INT_STAT_DEFAULT, \
                                        RXG_INT_STAT_RD_MASK, "RXG_INT_STAT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_INT_HIGH_EN_OFFSET, \
                                        RXG_INT_HIGH_EN_DEFAULT, \
                                        RXG_INT_HIGH_EN_RD_MASK, "RXG_INT_HIGH_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_INT_LOW_EN_OFFSET, \
                                        RXG_INT_LOW_EN_DEFAULT, \
                                        RXG_INT_LOW_EN_RD_MASK, "RXG_INT_LOW_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_INT_CLR_OFFSET, \
                                        RXG_INT_CLR_DEFAULT, \
                                        RXG_INT_CLR_RD_MASK, "RXG_INT_CLR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_INT_FORCE_OFFSET, \
                                        RXG_INT_FORCE_DEFAULT, \
                                        RXG_INT_FORCE_RD_MASK, "RXG_INT_FORCE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXG_APB_BRDG_STAT_OFFSET, \
                                        RXG_APB_BRDG_STAT_DEFAULT, \
                                        RXG_APB_BRDG_STAT_RD_MASK, "RXG_APB_BRDG_STAT_OFFSET");
        }

    }

}
