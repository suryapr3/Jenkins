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

    uint32_t base_address1[] = {
    FB_ANT0_SMC_ODD_TOP_BASE, FB_ANT0_SMC_EVEN_TOP_BASE, FB_ANT0_SMC_ODD_BOT_BASE, FB_ANT0_SMC_EVEN_BOT_BASE, FB_ANT1_SMC_ODD_TOP_BASE,
    FB_ANT1_SMC_EVEN_TOP_BASE, FB_ANT1_SMC_ODD_BOT_BASE, FB_ANT1_SMC_EVEN_BOT_BASE};

    uint32_t base_address2[] = {TRX_ANT0_SMC0_BASE, TRX_ANT0_SMC1_BASE,
    TRX_ANT1_SMC0_BASE, TRX_ANT1_SMC1_BASE, TRX_ANT2_SMC0_BASE, TRX_ANT2_SMC1_BASE, TRX_ANT3_SMC0_BASE,
    TRX_ANT3_SMC1_BASE, TRX_ANT4_SMC0_BASE, TRX_ANT4_SMC1_BASE, TRX_ANT5_SMC0_BASE, TRX_ANT5_SMC1_BASE,
    TRX_ANT6_SMC0_BASE, TRX_ANT6_SMC1_BASE, TRX_ANT7_SMC0_BASE, TRX_ANT7_SMC1_BASE
    };

    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {

        for(j=0; j<size[i]; j++)
        {
            read_reg_expect_18a(base_addresses[i][j]+SMC_A0_SHDW_OFFSET, \
                                        SMC_A0_SHDW_DEFAULT, \
                                        SMC_A0_SHDW_RD_MASK, "SMC_A0_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B0_SHDW_OFFSET, \
                                        SMC_B0_SHDW_DEFAULT, \
                                        SMC_B0_SHDW_RD_MASK, "SMC_B0_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B1_SHDW_OFFSET, \
                                        SMC_B1_SHDW_DEFAULT, \
                                        SMC_B1_SHDW_RD_MASK, "SMC_B1_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B2_SHDW_OFFSET, \
                                        SMC_B2_SHDW_DEFAULT, \
                                        SMC_B2_SHDW_RD_MASK, "SMC_B2_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B3_SHDW_OFFSET, \
                                        SMC_B3_SHDW_DEFAULT, \
                                        SMC_B3_SHDW_RD_MASK, "SMC_B3_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B4_SHDW_OFFSET, \
                                        SMC_B4_SHDW_DEFAULT, \
                                        SMC_B4_SHDW_RD_MASK, "SMC_B4_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B5_SHDW_OFFSET, \
                                        SMC_B5_SHDW_DEFAULT, \
                                        SMC_B5_SHDW_RD_MASK, "SMC_B5_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B6_SHDW_OFFSET, \
                                        SMC_B6_SHDW_DEFAULT, \
                                        SMC_B6_SHDW_RD_MASK, "SMC_B6_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_C0_SHDW_OFFSET, \
                                        SMC_C0_SHDW_DEFAULT, \
                                        SMC_C0_SHDW_RD_MASK, "SMC_C0_SHDW_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_A0_LIVE_OFFSET, \
                                        SMC_A0_LIVE_DEFAULT, \
                                        SMC_A0_LIVE_RD_MASK, "SMC_A0_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B0_LIVE_OFFSET, \
                                        SMC_B0_LIVE_DEFAULT, \
                                        SMC_B0_LIVE_RD_MASK, "SMC_B0_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B1_LIVE_OFFSET, \
                                        SMC_B1_LIVE_DEFAULT, \
                                        SMC_B1_LIVE_RD_MASK, "SMC_B1_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B2_LIVE_OFFSET, \
                                        SMC_B2_LIVE_DEFAULT, \
                                        SMC_B2_LIVE_RD_MASK, "SMC_B2_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B3_LIVE_OFFSET, \
                                        SMC_B3_LIVE_DEFAULT, \
                                        SMC_B3_LIVE_RD_MASK, "SMC_B3_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B4_LIVE_OFFSET, \
                                        SMC_B4_LIVE_DEFAULT, \
                                        SMC_B4_LIVE_RD_MASK, "SMC_B4_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B5_LIVE_OFFSET, \
                                        SMC_B5_LIVE_DEFAULT, \
                                        SMC_B5_LIVE_RD_MASK, "SMC_B5_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_B6_LIVE_OFFSET, \
                                        SMC_B6_LIVE_DEFAULT, \
                                        SMC_B6_LIVE_RD_MASK, "SMC_B6_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_C0_LIVE_OFFSET, \
                                        SMC_C0_LIVE_DEFAULT, \
                                        SMC_C0_LIVE_RD_MASK, "SMC_C0_LIVE_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_SCRATCH_OFFSET, \
                                        SMC_SCRATCH_DEFAULT, \
                                        SMC_SCRATCH_RD_MASK, "SMC_SCRATCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_CFG_OFFSET, \
                                        SMC_CFG_DEFAULT, \
                                        SMC_CFG_RD_MASK, "SMC_CFG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_DITHER_CFG1_OFFSET, \
                                        SMC_DITHER_CFG1_DEFAULT, \
                                        SMC_DITHER_CFG1_RD_MASK, "SMC_DITHER_CFG1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_DITHER_CFG2_OFFSET, \
                                        SMC_DITHER_CFG2_DEFAULT, \
                                        SMC_DITHER_CFG2_RD_MASK, "SMC_DITHER_CFG2_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_CTRL_OFFSET, \
                                        SMC_CTRL_DEFAULT, \
                                        SMC_CTRL_RD_MASK, "SMC_CTRL_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_TMR_CFG_OFFSET, \
                                        SMC_TMR_CFG_DEFAULT, \
                                        SMC_TMR_CFG_RD_MASK, "SMC_TMR_CFG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_TMR_ERR_OFFSET, \
                                        SMC_TMR_ERR_DEFAULT, \
                                        SMC_TMR_ERR_RD_MASK, "SMC_TMR_ERR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_APB_BRDG_STAT_OFFSET, \
                                        SMC_APB_BRDG_STAT_DEFAULT, \
                                        SMC_APB_BRDG_STAT_RD_MASK, "SMC_APB_BRDG_STAT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_INT_STAT_OFFSET, \
                                        SMC_INT_STAT_DEFAULT, \
                                        SMC_INT_STAT_RD_MASK, "SMC_INT_STAT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_INT_HIGH_EN_OFFSET, \
                                        SMC_INT_HIGH_EN_DEFAULT, \
                                        SMC_INT_HIGH_EN_RD_MASK, "SMC_INT_HIGH_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_INT_LOW_EN_OFFSET, \
                                        SMC_INT_LOW_EN_DEFAULT, \
                                        SMC_INT_LOW_EN_RD_MASK, "SMC_INT_LOW_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_INT_CLR_OFFSET, \
                                        SMC_INT_CLR_DEFAULT, \
                                        SMC_INT_CLR_RD_MASK, "SMC_INT_CLR_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+SMC_INT_FORCE_OFFSET, \
                                        SMC_INT_FORCE_DEFAULT, \
                                        SMC_INT_FORCE_RD_MASK, "SMC_INT_FORCE_OFFSET");
        }

    }

}
