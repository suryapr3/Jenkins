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
    V2D0_BFN_CSR_BASE, V2D1_BFN_CSR_BASE, V2D2_BFN_CSR_BASE, V2D3_BFN_CSR_BASE, V2D4_BFN_CSR_BASE,
    V2D5_BFN_CSR_BASE, V2D6_BFN_CSR_BASE, V2D7_BFN_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+BFN_CSR_BFN_SCRATCH_OFFSET, \
                                    BFN_CSR_BFN_SCRATCH_DEFAULT, \
                                    BFN_CSR_BFN_SCRATCH_RD_MASK, "BFN_CSR_BFN_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_APB_BRI_STAT_OFFSET, \
                                    BFN_CSR_APB_BRI_STAT_DEFAULT, \
                                    BFN_CSR_APB_BRI_STAT_RD_MASK, "BFN_CSR_APB_BRI_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+BFN_CSR_GENERAL_CSR_OFFSET, \
                                    BFN_CSR_GENERAL_CSR_DEFAULT, \
                                    BFN_CSR_GENERAL_CSR_RD_MASK, "BFN_CSR_GENERAL_CSR_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN0_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN1_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN2_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN3_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN4_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN4_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN5_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN5_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN6_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN6_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN7_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN7_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN8_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN8_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN9_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN9_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN10_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN10_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_BFN11_OFFSET, \
                                    BFN_CSR_CAP_BFN_DEFAULT, \
                                    BFN_CSR_CAP_BFN_RD_MASK, "BFN_CSR_CAP_BFN11_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_CTRL_OFFSET, \
                                    BFN_CSR_AW_ISYNC_CTRL_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_CTRL_RD_MASK, "BFN_CSR_AW_ISYNC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_LCNT_INC_OFFSET, \
                                    BFN_CSR_AW_ISYNC_LCNT_INC_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_LCNT_INC_RD_MASK, "BFN_CSR_AW_ISYNC_LCNT_INC_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_TEN_MS_CNT_OFFSET, \
                                    BFN_CSR_AW_ISYNC_TEN_MS_CNT_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_TEN_MS_CNT_RD_MASK, "BFN_CSR_AW_ISYNC_TEN_MS_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_INC_PRE_OFFSET, \
                                    BFN_CSR_AW_ISYNC_INC_PRE_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_INC_PRE_RD_MASK, "BFN_CSR_AW_ISYNC_INC_PRE_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_CNT_ADJ_OFFSET, \
                                    BFN_CSR_AW_ISYNC_CNT_ADJ_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_CNT_ADJ_RD_MASK, "BFN_CSR_AW_ISYNC_CNT_ADJ_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    BFN_CSR_AW_ISYNC_BFN_CNT_SYNC_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_BFN_CNT_SYNC_RD_MASK, "BFN_CSR_AW_ISYNC_BFN_CNT_SYNC_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_AW_ISYNC_BFN_CNT_OFFSET, \
                                    BFN_CSR_AW_ISYNC_BFN_CNT_DEFAULT, \
                                    BFN_CSR_AW_ISYNC_BFN_CNT_RD_MASK, "BFN_CSR_AW_ISYNC_BFN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_CFG0_OFFSET, \
                                    BFN_CSR_BFNE_CFG_DEFAULT, \
                                    BFN_CSR_BFNE_CFG_RD_MASK, "BFN_CSR_BFNE_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_CFG1_OFFSET, \
                                    BFN_CSR_BFNE_CFG_DEFAULT, \
                                    BFN_CSR_BFNE_CFG_RD_MASK, "BFN_CSR_BFNE_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_CFG2_OFFSET, \
                                    BFN_CSR_BFNE_CFG_DEFAULT, \
                                    BFN_CSR_BFNE_CFG_RD_MASK, "BFN_CSR_BFNE_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_CFG3_OFFSET, \
                                    BFN_CSR_BFNE_CFG_DEFAULT, \
                                    BFN_CSR_BFNE_CFG_RD_MASK, "BFN_CSR_BFNE_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_INCR0_OFFSET, \
                                    BFN_CSR_BFNE_INCR_DEFAULT, \
                                    BFN_CSR_BFNE_INCR_RD_MASK, "BFN_CSR_BFNE_INCR0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_INCR1_OFFSET, \
                                    BFN_CSR_BFNE_INCR_DEFAULT, \
                                    BFN_CSR_BFNE_INCR_RD_MASK, "BFN_CSR_BFNE_INCR1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_INCR2_OFFSET, \
                                    BFN_CSR_BFNE_INCR_DEFAULT, \
                                    BFN_CSR_BFNE_INCR_RD_MASK, "BFN_CSR_BFNE_INCR2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_INCR3_OFFSET, \
                                    BFN_CSR_BFNE_INCR_DEFAULT, \
                                    BFN_CSR_BFNE_INCR_RD_MASK, "BFN_CSR_BFNE_INCR3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_START0_OFFSET, \
                                    BFN_CSR_BFNE_START_DEFAULT, \
                                    BFN_CSR_BFNE_START_RD_MASK, "BFN_CSR_BFNE_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_START1_OFFSET, \
                                    BFN_CSR_BFNE_START_DEFAULT, \
                                    BFN_CSR_BFNE_START_RD_MASK, "BFN_CSR_BFNE_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_START2_OFFSET, \
                                    BFN_CSR_BFNE_START_DEFAULT, \
                                    BFN_CSR_BFNE_START_RD_MASK, "BFN_CSR_BFNE_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_START3_OFFSET, \
                                    BFN_CSR_BFNE_START_DEFAULT, \
                                    BFN_CSR_BFNE_START_RD_MASK, "BFN_CSR_BFNE_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_STAT0_OFFSET, \
                                    BFN_CSR_BFNE_STAT_DEFAULT, \
                                    BFN_CSR_BFNE_STAT_RD_MASK, "BFN_CSR_BFNE_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_STAT1_OFFSET, \
                                    BFN_CSR_BFNE_STAT_DEFAULT, \
                                    BFN_CSR_BFNE_STAT_RD_MASK, "BFN_CSR_BFNE_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_STAT2_OFFSET, \
                                    BFN_CSR_BFNE_STAT_DEFAULT, \
                                    BFN_CSR_BFNE_STAT_RD_MASK, "BFN_CSR_BFNE_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_BFNE_STAT3_OFFSET, \
                                    BFN_CSR_BFNE_STAT_DEFAULT, \
                                    BFN_CSR_BFNE_STAT_RD_MASK, "BFN_CSR_BFNE_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_LM0_OFFSET, \
                                    BFN_CSR_START_LM_DEFAULT, \
                                    BFN_CSR_START_LM_RD_MASK, "BFN_CSR_START_LM0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_LM1_OFFSET, \
                                    BFN_CSR_START_LM_DEFAULT, \
                                    BFN_CSR_START_LM_RD_MASK, "BFN_CSR_START_LM1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_LM2_OFFSET, \
                                    BFN_CSR_START_LM_DEFAULT, \
                                    BFN_CSR_START_LM_RD_MASK, "BFN_CSR_START_LM2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_LM3_OFFSET, \
                                    BFN_CSR_START_LM_DEFAULT, \
                                    BFN_CSR_START_LM_RD_MASK, "BFN_CSR_START_LM3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_L_CNT0_OFFSET, \
                                    BFN_CSR_START_L_CNT_DEFAULT, \
                                    BFN_CSR_START_L_CNT_RD_MASK, "BFN_CSR_START_L_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_L_CNT1_OFFSET, \
                                    BFN_CSR_START_L_CNT_DEFAULT, \
                                    BFN_CSR_START_L_CNT_RD_MASK, "BFN_CSR_START_L_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_L_CNT2_OFFSET, \
                                    BFN_CSR_START_L_CNT_DEFAULT, \
                                    BFN_CSR_START_L_CNT_RD_MASK, "BFN_CSR_START_L_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_START_L_CNT3_OFFSET, \
                                    BFN_CSR_START_L_CNT_DEFAULT, \
                                    BFN_CSR_START_L_CNT_RD_MASK, "BFN_CSR_START_L_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_MODE_CTRL_OFFSET, \
                                    BFN_CSR_CAP_MODE_CTRL_DEFAULT, \
                                    BFN_CSR_CAP_MODE_CTRL_RD_MASK, "BFN_CSR_CAP_MODE_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_CAP_DATA_CTRL_OFFSET, \
                                    BFN_CSR_CAP_DATA_CTRL_DEFAULT, \
                                    BFN_CSR_CAP_DATA_CTRL_RD_MASK, "BFN_CSR_CAP_DATA_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R0_OFFSET, \
                                    BFN_CSR_SMON_R0_DEFAULT, \
                                    BFN_CSR_SMON_R0_RD_MASK, "BFN_CSR_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R1_OFFSET, \
                                    BFN_CSR_SMON_R1_DEFAULT, \
                                    BFN_CSR_SMON_R1_RD_MASK, "BFN_CSR_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R2_OFFSET, \
                                    BFN_CSR_SMON_R2_DEFAULT, \
                                    BFN_CSR_SMON_R2_RD_MASK, "BFN_CSR_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R3_OFFSET, \
                                    BFN_CSR_SMON_R3_DEFAULT, \
                                    BFN_CSR_SMON_R3_RD_MASK, "BFN_CSR_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R4_OFFSET, \
                                    BFN_CSR_SMON_R4_DEFAULT, \
                                    BFN_CSR_SMON_R4_RD_MASK, "BFN_CSR_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R5_OFFSET, \
                                    BFN_CSR_SMON_R5_DEFAULT, \
                                    BFN_CSR_SMON_R5_RD_MASK, "BFN_CSR_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R6_OFFSET, \
                                    BFN_CSR_SMON_R6_DEFAULT, \
                                    BFN_CSR_SMON_R6_RD_MASK, "BFN_CSR_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SMON_R7_OFFSET, \
                                    BFN_CSR_SMON_R7_DEFAULT, \
                                    BFN_CSR_SMON_R7_RD_MASK, "BFN_CSR_SMON_R7_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SUBB_LO_INTR_OFFSET, \
                                    BFN_CSR_SUBB_LO_INTR_DEFAULT, \
                                    BFN_CSR_SUBB_LO_INTR_RD_MASK, "BFN_CSR_SUBB_LO_INTR_OFFSET");

        read_reg_expect_18a(base_address[i]+BFN_CSR_SUBB_HI_INTR_OFFSET, \
                                    BFN_CSR_SUBB_HI_INTR_DEFAULT, \
                                    BFN_CSR_SUBB_HI_INTR_RD_MASK, "BFN_CSR_SUBB_HI_INTR_OFFSET");

    }

}
