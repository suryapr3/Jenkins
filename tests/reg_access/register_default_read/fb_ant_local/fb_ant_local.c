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
    FB_ANT0_CSR_BASE, FB_ANT1_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ANT_RATE_0_OFFSET, \
                                    FB_ANT_LOCAL_ANT_RATE_0_DEFAULT, \
                                    FB_ANT_LOCAL_ANT_RATE_0_RD_MASK, "FB_ANT_LOCAL_ANT_RATE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ANT_RATE_1_OFFSET, \
                                    FB_ANT_LOCAL_ANT_RATE_1_DEFAULT, \
                                    FB_ANT_LOCAL_ANT_RATE_1_RD_MASK, "FB_ANT_LOCAL_ANT_RATE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_INT_HI_STAT_OFFSET, \
                                    FB_ANT_LOCAL_INT_HI_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_INT_HI_STAT_RD_MASK, "FB_ANT_LOCAL_INT_HI_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_INT_LO_STAT_OFFSET, \
                                    FB_ANT_LOCAL_INT_LO_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_INT_LO_STAT_RD_MASK, "FB_ANT_LOCAL_INT_LO_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BRDG_STAT_OFFSET, \
                                    FB_ANT_LOCAL_BRDG_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BRDG_STAT_RD_MASK, "FB_ANT_LOCAL_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_SMC_CTLT_OFFSET, \
                                    FB_ANT_LOCAL_SMC_CTLT_DEFAULT, \
                                    FB_ANT_LOCAL_SMC_CTLT_RD_MASK, "FB_ANT_LOCAL_SMC_CTLT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_SMC_CTLB_OFFSET, \
                                    FB_ANT_LOCAL_SMC_CTLB_DEFAULT, \
                                    FB_ANT_LOCAL_SMC_CTLB_RD_MASK, "FB_ANT_LOCAL_SMC_CTLB_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_DIG_LPK_OFFSET, \
                                    FB_ANT_LOCAL_DIG_LPK_DEFAULT, \
                                    FB_ANT_LOCAL_DIG_LPK_RD_MASK, "FB_ANT_LOCAL_DIG_LPK_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_DP_INIT_OFFSET, \
                                    FB_ANT_LOCAL_DP_INIT_DEFAULT, \
                                    FB_ANT_LOCAL_DP_INIT_RD_MASK, "FB_ANT_LOCAL_DP_INIT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_CTRL_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_CTRL_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_CTRL_RD_MASK, "FB_ANT_LOCAL_ISYNC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_LCNT_INC_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_LCNT_INC_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_LCNT_INC_RD_MASK, "FB_ANT_LOCAL_ISYNC_LCNT_INC_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_RD_MASK, "FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_INC_PRE_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_INC_PRE_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_INC_PRE_RD_MASK, "FB_ANT_LOCAL_ISYNC_INC_PRE_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_CNT_ADJ_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_CNT_ADJ_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_CNT_ADJ_RD_MASK, "FB_ANT_LOCAL_ISYNC_CNT_ADJ_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_RD_MASK, "FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_BFN_CNT_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_DEFAULT, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_RD_MASK, "FB_ANT_LOCAL_ISYNC_BFN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_RD_MASK, "FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE0_RD_MASK, "FB_ANT_LOCAL_UL_RXM_PS_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_RD_MASK, "FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE1_RD_MASK, "FB_ANT_LOCAL_UL_RXM_PS_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_RD_MASK, "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_RD_MASK, "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_RD_MASK, "FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW0_RD_MASK, "FB_ANT_LOCAL_UL_RXM_PS_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_RD_MASK, "FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW1_RD_MASK, "FB_ANT_LOCAL_UL_RXM_PS_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_DEFAULT, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_RD_MASK, "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_DEFAULT, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_RD_MASK, "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_ULDL_STAT_OFFSET, \
                                    FB_ANT_LOCAL_ULDL_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_ULDL_STAT_RD_MASK, "FB_ANT_LOCAL_ULDL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG4_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG5_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG6_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG7_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG8_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG9_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG10_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG11_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG12_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG13_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG14_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG15_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG16_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG17_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG18_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG19_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG20_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, "FB_ANT_LOCAL_BFNE_CFG21_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR2_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR3_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR4_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR5_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR6_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR7_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR8_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR9_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR10_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR11_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR12_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR13_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR14_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR15_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR16_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR17_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR18_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR19_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR20_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, "FB_ANT_LOCAL_BFNE_INCR21_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START4_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START5_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START6_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START7_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START8_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START9_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START10_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START11_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START12_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START13_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START14_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START15_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START16_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START17_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START18_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START19_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START20_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, "FB_ANT_LOCAL_BFNE_START21_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT5_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT6_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT7_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT8_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT9_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT10_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT11_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT12_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT13_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT14_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT15_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT16_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT17_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT18_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT19_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT20_OFFSET");

        read_reg_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, "FB_ANT_LOCAL_BFNE_STAT21_OFFSET");

    }

}
