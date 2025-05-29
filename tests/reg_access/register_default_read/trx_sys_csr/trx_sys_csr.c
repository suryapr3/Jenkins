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
    TRX_SYS0_CSR_BASE, TRX_SYS1_CSR_BASE, TRX_SYS2_CSR_BASE, TRX_SYS3_CSR_BASE, TRX_SYS4_CSR_BASE,
    TRX_SYS5_CSR_BASE, TRX_SYS6_CSR_BASE, TRX_SYS7_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_RATE_CFG_OFFSET, \
                                    TRX_SYS_CSR_TRX_RATE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_TRX_RATE_CFG_RD_MASK, "TRX_SYS_CSR_TRX_RATE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INT_HI_AGGR_OFFSET, \
                                    TRX_SYS_CSR_TX_INT_HI_AGGR_DEFAULT, \
                                    TRX_SYS_CSR_TX_INT_HI_AGGR_RD_MASK, "TRX_SYS_CSR_TX_INT_HI_AGGR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INT_LO_AGGR_OFFSET, \
                                    TRX_SYS_CSR_TX_INT_LO_AGGR_DEFAULT, \
                                    TRX_SYS_CSR_TX_INT_LO_AGGR_RD_MASK, "TRX_SYS_CSR_TX_INT_LO_AGGR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_RX_CAPMUX_SEL_OFFSET, \
                                    TRX_SYS_CSR_RX_CAPMUX_SEL_DEFAULT, \
                                    TRX_SYS_CSR_RX_CAPMUX_SEL_RD_MASK, "TRX_SYS_CSR_RX_CAPMUX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_RX_INT_HI_AGGR_OFFSET, \
                                    TRX_SYS_CSR_RX_INT_HI_AGGR_DEFAULT, \
                                    TRX_SYS_CSR_RX_INT_HI_AGGR_RD_MASK, "TRX_SYS_CSR_RX_INT_HI_AGGR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_RX_INT_LO_AGGR_OFFSET, \
                                    TRX_SYS_CSR_RX_INT_LO_AGGR_DEFAULT, \
                                    TRX_SYS_CSR_RX_INT_LO_AGGR_RD_MASK, "TRX_SYS_CSR_RX_INT_LO_AGGR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT0_SRC0_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT0_SRC0_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT0_SRC0_RD_MASK, "TRX_SYS_CSR_TX_INSERT0_SRC0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT0_SRC1_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT0_SRC1_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT0_SRC1_RD_MASK, "TRX_SYS_CSR_TX_INSERT0_SRC1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT1_SRC0_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT1_SRC0_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT1_SRC0_RD_MASK, "TRX_SYS_CSR_TX_INSERT1_SRC0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT1_SRC1_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT1_SRC1_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT1_SRC1_RD_MASK, "TRX_SYS_CSR_TX_INSERT1_SRC1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT_VALSRC_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT_VALSRC_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT_VALSRC_RD_MASK, "TRX_SYS_CSR_TX_INSERT_VALSRC_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT0_CFG_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT0_CFG_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT0_CFG_RD_MASK, "TRX_SYS_CSR_TX_INSERT0_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_INSERT1_CFG_OFFSET, \
                                    TRX_SYS_CSR_TX_INSERT1_CFG_DEFAULT, \
                                    TRX_SYS_CSR_TX_INSERT1_CFG_RD_MASK, "TRX_SYS_CSR_TX_INSERT1_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_FORCE_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_FORCE_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_FORCE_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_MASK_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_MASK_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_MASK_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_STAT_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_STAT_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_STICKY_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_STICKY_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_ETIMER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_ETIMER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_ETIMER_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_ETIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_PNTIMER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_PNTIMER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_PNTIMER_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_PNTIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_FORCE_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_FORCE_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_FORCE_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_MASK_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_MASK_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_MASK_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_STAT_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_STAT_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_STAT_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_STICKY_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_STICKY_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_STICKY_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_STICKY_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_ETIMER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_ETIMER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_ETIMER_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_ETIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_PNTIMER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_PNTIMER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_PNTIMER_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_PNTIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_CS0_I_OFFSET, \
                                    TRX_SYS_CSR_CVA_CS0_I_DEFAULT, \
                                    TRX_SYS_CSR_CVA_CS0_I_RD_MASK, "TRX_SYS_CSR_CVA_CS0_I_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_CS0_Q_OFFSET, \
                                    TRX_SYS_CSR_CVA_CS0_Q_DEFAULT, \
                                    TRX_SYS_CSR_CVA_CS0_Q_RD_MASK, "TRX_SYS_CSR_CVA_CS0_Q_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_CS1_I_OFFSET, \
                                    TRX_SYS_CSR_CVA_CS1_I_DEFAULT, \
                                    TRX_SYS_CSR_CVA_CS1_I_RD_MASK, "TRX_SYS_CSR_CVA_CS1_I_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_CS1_Q_OFFSET, \
                                    TRX_SYS_CSR_CVA_CS1_Q_DEFAULT, \
                                    TRX_SYS_CSR_CVA_CS1_Q_RD_MASK, "TRX_SYS_CSR_CVA_CS1_Q_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_ERR_OFFSET, \
                                    TRX_SYS_CSR_CVA_ERR_DEFAULT, \
                                    TRX_SYS_CSR_CVA_ERR_RD_MASK, "TRX_SYS_CSR_CVA_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_CVA_CFG_OFFSET, \
                                    TRX_SYS_CSR_CVA_CFG_DEFAULT, \
                                    TRX_SYS_CSR_CVA_CFG_RD_MASK, "TRX_SYS_CSR_CVA_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_MOD_AC_CAL_ENA_OFFSET, \
                                    TRX_SYS_CSR_MOD_AC_CAL_ENA_DEFAULT, \
                                    TRX_SYS_CSR_MOD_AC_CAL_ENA_RD_MASK, "TRX_SYS_CSR_MOD_AC_CAL_ENA_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_MOD_CAPMUX_SEL_OFFSET, \
                                    TRX_SYS_CSR_MOD_CAPMUX_SEL_DEFAULT, \
                                    TRX_SYS_CSR_MOD_CAPMUX_SEL_RD_MASK, "TRX_SYS_CSR_MOD_CAPMUX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_DMOD_AC_CAL_ENA_OFFSET, \
                                    TRX_SYS_CSR_DMOD_AC_CAL_ENA_DEFAULT, \
                                    TRX_SYS_CSR_DMOD_AC_CAL_ENA_RD_MASK, "TRX_SYS_CSR_DMOD_AC_CAL_ENA_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM0_CNTER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM0_CNTER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM0_CNTER_RD_MASK, "TRX_SYS_CSR_TX_ALARM0_CNTER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TX_ALARM1_CNTER_OFFSET, \
                                    TRX_SYS_CSR_TX_ALARM1_CNTER_DEFAULT, \
                                    TRX_SYS_CSR_TX_ALARM1_CNTER_RD_MASK, "TRX_SYS_CSR_TX_ALARM1_CNTER_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_DP_INIT_ENB_OFFSET, \
                                    TRX_SYS_CSR_DP_INIT_ENB_DEFAULT, \
                                    TRX_SYS_CSR_DP_INIT_ENB_RD_MASK, "TRX_SYS_CSR_DP_INIT_ENB_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_DP_DONE_STAT_OFFSET, \
                                    TRX_SYS_CSR_DP_DONE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_DP_DONE_STAT_RD_MASK, "TRX_SYS_CSR_DP_DONE_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_INT_STAT_OFFSET, \
                                    TRX_SYS_CSR_TRX_INT_STAT_DEFAULT, \
                                    TRX_SYS_CSR_TRX_INT_STAT_RD_MASK, "TRX_SYS_CSR_TRX_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_INT_HI_EN_OFFSET, \
                                    TRX_SYS_CSR_TRX_INT_HI_EN_DEFAULT, \
                                    TRX_SYS_CSR_TRX_INT_HI_EN_RD_MASK, "TRX_SYS_CSR_TRX_INT_HI_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_INT_LO_EN_OFFSET, \
                                    TRX_SYS_CSR_TRX_INT_LO_EN_DEFAULT, \
                                    TRX_SYS_CSR_TRX_INT_LO_EN_RD_MASK, "TRX_SYS_CSR_TRX_INT_LO_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_INT_CLR_OFFSET, \
                                    TRX_SYS_CSR_TRX_INT_CLR_DEFAULT, \
                                    TRX_SYS_CSR_TRX_INT_CLR_RD_MASK, "TRX_SYS_CSR_TRX_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_TRX_INT_FORCE_OFFSET, \
                                    TRX_SYS_CSR_TRX_INT_FORCE_DEFAULT, \
                                    TRX_SYS_CSR_TRX_INT_FORCE_RD_MASK, "TRX_SYS_CSR_TRX_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R0_OFFSET, \
                                    TRX_SYS_CSR_SMON_R0_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R0_RD_MASK, "TRX_SYS_CSR_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R1_OFFSET, \
                                    TRX_SYS_CSR_SMON_R1_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R1_RD_MASK, "TRX_SYS_CSR_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R2_OFFSET, \
                                    TRX_SYS_CSR_SMON_R2_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R2_RD_MASK, "TRX_SYS_CSR_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R3_OFFSET, \
                                    TRX_SYS_CSR_SMON_R3_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R3_RD_MASK, "TRX_SYS_CSR_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R4_OFFSET, \
                                    TRX_SYS_CSR_SMON_R4_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R4_RD_MASK, "TRX_SYS_CSR_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R5_OFFSET, \
                                    TRX_SYS_CSR_SMON_R5_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R5_RD_MASK, "TRX_SYS_CSR_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R6_OFFSET, \
                                    TRX_SYS_CSR_SMON_R6_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R6_RD_MASK, "TRX_SYS_CSR_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_SMON_R7_OFFSET, \
                                    TRX_SYS_CSR_SMON_R7_DEFAULT, \
                                    TRX_SYS_CSR_SMON_R7_RD_MASK, "TRX_SYS_CSR_SMON_R7_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_APB_BRDG_STAT_OFFSET, \
                                    TRX_SYS_CSR_APB_BRDG_STAT_DEFAULT, \
                                    TRX_SYS_CSR_APB_BRDG_STAT_RD_MASK, "TRX_SYS_CSR_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_CTRL_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_CTRL_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_CTRL_RD_MASK, "TRX_SYS_CSR_ISYNC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_LCNT_INC_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_LCNT_INC_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_LCNT_INC_RD_MASK, "TRX_SYS_CSR_ISYNC_LCNT_INC_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_TEN_MS_CNT_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_TEN_MS_CNT_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_TEN_MS_CNT_RD_MASK, "TRX_SYS_CSR_ISYNC_TEN_MS_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_INC_PRE_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_INC_PRE_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_INC_PRE_RD_MASK, "TRX_SYS_CSR_ISYNC_INC_PRE_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_CNT_ADJ_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_CNT_ADJ_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_CNT_ADJ_RD_MASK, "TRX_SYS_CSR_ISYNC_CNT_ADJ_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_BFN_CNT_SYNC_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_BFN_CNT_SYNC_RD_MASK, "TRX_SYS_CSR_ISYNC_BFN_CNT_SYNC_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_ISYNC_BFN_CNT_OFFSET, \
                                    TRX_SYS_CSR_ISYNC_BFN_CNT_DEFAULT, \
                                    TRX_SYS_CSR_ISYNC_BFN_CNT_RD_MASK, "TRX_SYS_CSR_ISYNC_BFN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG0_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG1_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG2_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG3_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG4_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG4_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG5_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG5_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG6_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG6_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG7_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG7_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG8_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG8_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG9_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG9_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_CFG10_OFFSET, \
                                    TRX_SYS_CSR_BFNE_CFG_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_CFG_RD_MASK, "TRX_SYS_CSR_BFNE_CFG10_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR0_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR1_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR2_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR2_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR3_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR3_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR4_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR4_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR5_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR5_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR6_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR6_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR7_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR7_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR8_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR8_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR9_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR9_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_INCR10_OFFSET, \
                                    TRX_SYS_CSR_BFNE_INCR_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_INCR_RD_MASK, "TRX_SYS_CSR_BFNE_INCR10_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START0_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START1_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START2_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START3_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START4_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START4_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START5_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START5_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START6_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START6_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START7_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START7_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START8_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START8_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START9_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START9_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_START10_OFFSET, \
                                    TRX_SYS_CSR_BFNE_START_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_START_RD_MASK, "TRX_SYS_CSR_BFNE_START10_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT0_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT1_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT2_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT3_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT4_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT5_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT5_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT6_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT6_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT7_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT7_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT8_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT8_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT9_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT9_OFFSET");

        read_reg_expect_18a(base_address[i]+TRX_SYS_CSR_BFNE_STAT10_OFFSET, \
                                    TRX_SYS_CSR_BFNE_STAT_DEFAULT, \
                                    TRX_SYS_CSR_BFNE_STAT_RD_MASK, "TRX_SYS_CSR_BFNE_STAT10_OFFSET");

    }

}
