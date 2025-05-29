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

#define write_data0 0xA5A5A5A5
#define write_data1 0x5a5a5a5a


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    uint32_t error = 0;
    uint32_t write_status = 0;
    uint32_t write_iteration;
    uint32_t write_data;
    uint32_t expected_data;
    int i;
    init();

    uint32_t base_address[] = {
    FB_ANT0_CSR_BASE, FB_ANT1_CSR_BASE
    };


    for (write_iteration = 0;write_iteration < 1; write_iteration++)
    {
        if (write_iteration == 0 )
        {
            write_data = write_data0;
        }
        else
        {
            write_data = write_data1;
        }

        expected_data = write_data;


        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
        {
            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ANT_RATE_0_OFFSET, \
                                    FB_ANT_LOCAL_ANT_RATE_0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ANT_RATE_0_RD_MASK, FB_ANT_LOCAL_ANT_RATE_0_WR_MASK, \
                                    "FB_ANT_LOCAL_ANT_RATE_0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ANT_RATE_1_OFFSET, \
                                    FB_ANT_LOCAL_ANT_RATE_1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ANT_RATE_1_RD_MASK, FB_ANT_LOCAL_ANT_RATE_1_WR_MASK, \
                                    "FB_ANT_LOCAL_ANT_RATE_1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_INT_HI_STAT_OFFSET, \
                                    FB_ANT_LOCAL_INT_HI_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_INT_HI_STAT_RD_MASK, FB_ANT_LOCAL_INT_HI_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_INT_HI_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_INT_LO_STAT_OFFSET, \
                                    FB_ANT_LOCAL_INT_LO_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_INT_LO_STAT_RD_MASK, FB_ANT_LOCAL_INT_LO_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_INT_LO_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BRDG_STAT_OFFSET, \
                                    FB_ANT_LOCAL_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BRDG_STAT_RD_MASK, FB_ANT_LOCAL_BRDG_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_SMC_CTLT_OFFSET, \
                                    FB_ANT_LOCAL_SMC_CTLT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_SMC_CTLT_RD_MASK, FB_ANT_LOCAL_SMC_CTLT_WR_MASK, \
                                    "FB_ANT_LOCAL_SMC_CTLT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_SMC_CTLB_OFFSET, \
                                    FB_ANT_LOCAL_SMC_CTLB_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_SMC_CTLB_RD_MASK, FB_ANT_LOCAL_SMC_CTLB_WR_MASK, \
                                    "FB_ANT_LOCAL_SMC_CTLB_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_DIG_LPK_OFFSET, \
                                    FB_ANT_LOCAL_DIG_LPK_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_DIG_LPK_RD_MASK, FB_ANT_LOCAL_DIG_LPK_WR_MASK, \
                                    "FB_ANT_LOCAL_DIG_LPK_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_DP_INIT_OFFSET, \
                                    FB_ANT_LOCAL_DP_INIT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_DP_INIT_RD_MASK, FB_ANT_LOCAL_DP_INIT_WR_MASK, \
                                    "FB_ANT_LOCAL_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_CTRL_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_CTRL_RD_MASK, FB_ANT_LOCAL_ISYNC_CTRL_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_LCNT_INC_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_LCNT_INC_RD_MASK, FB_ANT_LOCAL_ISYNC_LCNT_INC_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_RD_MASK, FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_INC_PRE_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_INC_PRE_RD_MASK, FB_ANT_LOCAL_ISYNC_INC_PRE_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_CNT_ADJ_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_CNT_ADJ_RD_MASK, FB_ANT_LOCAL_ISYNC_CNT_ADJ_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_RD_MASK, FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ISYNC_BFN_CNT_OFFSET, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ISYNC_BFN_CNT_RD_MASK, FB_ANT_LOCAL_ISYNC_BFN_CNT_WR_MASK, \
                                    "FB_ANT_LOCAL_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_RD_MASK, FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_ENA_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE0_RD_MASK, FB_ANT_LOCAL_UL_RXM_PS_LIVE0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_PS_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_RD_MASK, FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_ENA_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_PS_LIVE1_RD_MASK, FB_ANT_LOCAL_UL_RXM_PS_LIVE1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_PS_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_RD_MASK, FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_RD_MASK, FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_RD_MASK, FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_ENA_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW0_RD_MASK, FB_ANT_LOCAL_UL_RXM_PS_SHDW0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_PS_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_RD_MASK, FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_ENA_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_RXM_PS_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_RXM_PS_SHDW1_RD_MASK, FB_ANT_LOCAL_UL_RXM_PS_SHDW1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_RXM_PS_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_RD_MASK, FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_RD_MASK, FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_WR_MASK, \
                                    "FB_ANT_LOCAL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_ULDL_STAT_OFFSET, \
                                    FB_ANT_LOCAL_ULDL_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_ULDL_STAT_RD_MASK, FB_ANT_LOCAL_ULDL_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_ULDL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG8_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG9_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG10_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG11_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG12_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG13_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG14_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG15_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG16_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG17_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG18_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG19_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG20_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_CFG21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_CFG_RD_MASK, FB_ANT_LOCAL_BFNE_CFG_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_CFG21_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR8_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR9_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR10_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR11_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR12_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR13_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR14_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR15_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR16_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR17_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR18_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR19_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR20_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_INCR21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_INCR_RD_MASK, FB_ANT_LOCAL_BFNE_INCR_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_INCR21_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START8_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START9_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START10_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START11_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START12_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START13_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START14_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START15_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START16_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START17_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START18_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START19_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START20_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_START21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_START_RD_MASK, FB_ANT_LOCAL_BFNE_START_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_START21_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT0_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT1_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT2_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT3_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT4_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT5_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT6_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT7_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT8_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT9_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT10_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT10_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT11_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT11_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT12_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT12_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT13_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT13_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT14_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT14_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT15_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT15_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT16_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT16_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT17_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT17_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT18_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT18_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT19_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT19_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT20_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT20_OFFSET");

            write_read_expect_18a(base_address[i]+FB_ANT_LOCAL_BFNE_STAT21_OFFSET, \
                                    FB_ANT_LOCAL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    FB_ANT_LOCAL_BFNE_STAT_RD_MASK, FB_ANT_LOCAL_BFNE_STAT_WR_MASK, \
                                    "FB_ANT_LOCAL_BFNE_STAT21_OFFSET");

        }

    }

}
