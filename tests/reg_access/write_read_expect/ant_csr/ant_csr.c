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
    ANT0_CSR_BASE, ANT1_CSR_BASE, ANT2_CSR_BASE, ANT3_CSR_BASE
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
            write_read_expect_18a(base_address[i]+ANT_CSR_SCRATCH_OFFSET, \
                                    ANT_CSR_SCRATCH_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_SCRATCH_RD_MASK, ANT_CSR_SCRATCH_WR_MASK, \
                                    "ANT_CSR_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ASC_ANT_RATE_OFFSET, \
                                    ANT_CSR_ASC_ANT_RATE_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ASC_ANT_RATE_RD_MASK, ANT_CSR_ASC_ANT_RATE_WR_MASK, \
                                    "ANT_CSR_ASC_ANT_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ASC_XT_BYP_OFFSET, \
                                    ANT_CSR_ASC_XT_BYP_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ASC_XT_BYP_RD_MASK, ANT_CSR_ASC_XT_BYP_WR_MASK, \
                                    "ANT_CSR_ASC_XT_BYP_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_FB_ASC_ANT_RATE_OFFSET, \
                                    ANT_CSR_FB_ASC_ANT_RATE_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_FB_ASC_ANT_RATE_RD_MASK, ANT_CSR_FB_ASC_ANT_RATE_WR_MASK, \
                                    "ANT_CSR_FB_ASC_ANT_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_DCSRC_CONF0_OFFSET, \
                                    ANT_CSR_ANT_DCSRC_CONF0_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_DCSRC_CONF0_RD_MASK, ANT_CSR_ANT_DCSRC_CONF0_WR_MASK, \
                                    "ANT_CSR_ANT_DCSRC_CONF0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_DCSRC_CONF1_OFFSET, \
                                    ANT_CSR_ANT_DCSRC_CONF1_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_DCSRC_CONF1_RD_MASK, ANT_CSR_ANT_DCSRC_CONF1_WR_MASK, \
                                    "ANT_CSR_ANT_DCSRC_CONF1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_DPATH_CONF_OFFSET, \
                                    ANT_CSR_ANT_DPATH_CONF_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_DPATH_CONF_RD_MASK, ANT_CSR_ANT_DPATH_CONF_WR_MASK, \
                                    "ANT_CSR_ANT_DPATH_CONF_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_BSG_CFG_OFFSET, \
                                    ANT_CSR_ANT_BSG_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_BSG_CFG_RD_MASK, ANT_CSR_ANT_BSG_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_BSG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_BSG_DC_VAL_OFFSET, \
                                    ANT_CSR_ANT_BSG_DC_VAL_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_BSG_DC_VAL_RD_MASK, ANT_CSR_ANT_BSG_DC_VAL_WR_MASK, \
                                    "ANT_CSR_ANT_BSG_DC_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CAPT_TMUX_CTRL_OFFSET, \
                                    ANT_CSR_ANT_CAPT_TMUX_CTRL_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CAPT_TMUX_CTRL_RD_MASK, ANT_CSR_ANT_CAPT_TMUX_CTRL_WR_MASK, \
                                    "ANT_CSR_ANT_CAPT_TMUX_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_INIT_OFFSET, \
                                    ANT_CSR_ANT_CCF_INIT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_INIT_RD_MASK, ANT_CSR_ANT_CCF_INIT_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_DP_INIT_OFFSET, \
                                    ANT_CSR_ANT_DP_INIT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_DP_INIT_RD_MASK, ANT_CSR_ANT_DP_INIT_WR_MASK, \
                                    "ANT_CSR_ANT_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ0_CFG0_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ0_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ0_CFG1_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ0_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ0_CFG2_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ0_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ0_CFG3_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ0_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ1_CFG0_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ1_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ1_CFG1_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ1_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ1_CFG2_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ1_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_SEQ1_CFG3_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_SEQ1_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_PAUSE_CFG0_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_PAUSE_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_PAUSE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_PAUSE_CFG1_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_PAUSE_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_PAUSE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_PAUSE_CFG2_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_PAUSE_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_PAUSE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_PAUSE_CFG3_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_PAUSE_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_PAUSE_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_PAUSE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_RESUME_CFG0_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_RESUME_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_RESUME_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_RESUME_CFG1_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_RESUME_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_RESUME_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_RESUME_CFG2_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_RESUME_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_RESUME_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_RESUME_CFG3_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_RESUME_CFG_RD_MASK, ANT_CSR_ANT_RX_EN_RESUME_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_RESUME_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ0_CFG0_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ0_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ0_CFG1_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ0_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ0_CFG2_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ0_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ0_CFG3_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ0_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ1_CFG0_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ1_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ1_CFG1_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ1_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ1_CFG2_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ1_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_SEQ1_CFG3_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_TX_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_SEQ1_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_EN_SEQ0_CFG_OFFSET, \
                                    ANT_CSR_ANT_FB_EN_SEQ0_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_EN_SEQ0_CFG_RD_MASK, ANT_CSR_ANT_FB_EN_SEQ0_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_FB_EN_SEQ0_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_EN_SEQ1_CFG_OFFSET, \
                                    ANT_CSR_ANT_FB_EN_SEQ1_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_EN_SEQ1_CFG_RD_MASK, ANT_CSR_ANT_FB_EN_SEQ1_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_FB_EN_SEQ1_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_EN_PAUSE_CFG_OFFSET, \
                                    ANT_CSR_ANT_FB_EN_PAUSE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_EN_PAUSE_CFG_RD_MASK, ANT_CSR_ANT_FB_EN_PAUSE_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_FB_EN_PAUSE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_EN_RESUME_CFG_OFFSET, \
                                    ANT_CSR_ANT_FB_EN_RESUME_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_EN_RESUME_CFG_RD_MASK, ANT_CSR_ANT_FB_EN_RESUME_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_FB_EN_RESUME_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_RX_OUT_CFG_OFFSET, \
                                    ANT_CSR_ANT_CCF_RX_OUT_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_RX_OUT_CFG_RD_MASK, ANT_CSR_ANT_CCF_RX_OUT_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_RX_OUT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_RX_IN_CFG_OFFSET, \
                                    ANT_CSR_ANT_CCF_RX_IN_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_RX_IN_CFG_RD_MASK, ANT_CSR_ANT_CCF_RX_IN_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_RX_IN_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_FB_RX_OUT_CFG_OFFSET, \
                                    ANT_CSR_ANT_CCF_FB_RX_OUT_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_FB_RX_OUT_CFG_RD_MASK, ANT_CSR_ANT_CCF_FB_RX_OUT_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_FB_RX_OUT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_FB_RX_IN_CFG_OFFSET, \
                                    ANT_CSR_ANT_CCF_FB_RX_IN_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_FB_RX_IN_CFG_RD_MASK, ANT_CSR_ANT_CCF_FB_RX_IN_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_FB_RX_IN_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_CCF_DCSRC_IN_CFG_OFFSET, \
                                    ANT_CSR_ANT_CCF_DCSRC_IN_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_CCF_DCSRC_IN_CFG_RD_MASK, ANT_CSR_ANT_CCF_DCSRC_IN_CFG_WR_MASK, \
                                    "ANT_CSR_ANT_CCF_DCSRC_IN_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CMFF_CFG_OFFSET, \
                                    ANT_CSR_CMFF_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CMFF_CFG_RD_MASK, ANT_CSR_CMFF_CFG_WR_MASK, \
                                    "ANT_CSR_CMFF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CMFF_CTRL_OFFSET, \
                                    ANT_CSR_CMFF_CTRL_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CMFF_CTRL_RD_MASK, ANT_CSR_CMFF_CTRL_WR_MASK, \
                                    "ANT_CSR_CMFF_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_BSG_DC_INCR_OFFSET, \
                                    ANT_CSR_ANT_BSG_DC_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_BSG_DC_INCR_RD_MASK, ANT_CSR_ANT_BSG_DC_INCR_WR_MASK, \
                                    "ANT_CSR_ANT_BSG_DC_INCR_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_CTRL_OFFSET, \
                                    ANT_CSR_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_CTRL_RD_MASK, ANT_CSR_ISYNC_CTRL_WR_MASK, \
                                    "ANT_CSR_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_LCNT_INC_OFFSET, \
                                    ANT_CSR_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_LCNT_INC_RD_MASK, ANT_CSR_ISYNC_LCNT_INC_WR_MASK, \
                                    "ANT_CSR_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_TEN_MS_CNT_OFFSET, \
                                    ANT_CSR_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_TEN_MS_CNT_RD_MASK, ANT_CSR_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "ANT_CSR_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_INC_PRE_OFFSET, \
                                    ANT_CSR_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_INC_PRE_RD_MASK, ANT_CSR_ISYNC_INC_PRE_WR_MASK, \
                                    "ANT_CSR_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_CNT_ADJ_OFFSET, \
                                    ANT_CSR_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_CNT_ADJ_RD_MASK, ANT_CSR_ISYNC_CNT_ADJ_WR_MASK, \
                                    "ANT_CSR_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    ANT_CSR_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_BFN_CNT_SYNC_RD_MASK, ANT_CSR_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "ANT_CSR_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ISYNC_BFN_CNT_OFFSET, \
                                    ANT_CSR_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ISYNC_BFN_CNT_RD_MASK, ANT_CSR_ISYNC_BFN_CNT_WR_MASK, \
                                    "ANT_CSR_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG0_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG1_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG2_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG3_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG4_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG5_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG6_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG7_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG8_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG8_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG9_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG9_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG10_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG10_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG11_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG11_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG12_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG12_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG13_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG13_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG14_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG14_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG15_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG15_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG16_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG16_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG17_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG17_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG18_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG18_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG19_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG19_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG20_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG20_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG21_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG21_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG22_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG22_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG23_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG23_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG24_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG24_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG25_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG25_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG26_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG26_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG27_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG27_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG28_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG28_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG29_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG29_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG30_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG30_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG31_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG31_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG32_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG32_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG33_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG33_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG34_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG34_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG35_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG35_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG36_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG36_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG37_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG37_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG38_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG38_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG39_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG39_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG40_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG40_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_CFG41_OFFSET, \
                                    ANT_CSR_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_CFG_RD_MASK, ANT_CSR_BFNE_CFG_WR_MASK, \
                                    "ANT_CSR_BFNE_CFG41_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR0_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR1_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR2_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR3_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR4_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR5_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR6_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR7_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR8_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR8_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR9_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR9_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR10_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR10_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR11_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR11_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR12_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR12_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR13_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR13_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR14_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR14_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR15_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR15_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR16_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR16_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR17_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR17_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR18_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR18_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR19_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR19_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR20_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR20_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR21_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR21_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR22_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR22_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR23_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR23_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR24_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR24_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR25_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR25_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR26_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR26_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR27_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR27_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR28_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR28_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR29_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR29_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR30_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR30_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR31_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR31_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR32_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR32_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR33_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR33_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR34_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR34_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR35_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR35_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR36_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR36_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR37_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR37_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR38_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR38_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR39_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR39_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR40_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR40_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_INCR41_OFFSET, \
                                    ANT_CSR_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_INCR_RD_MASK, ANT_CSR_BFNE_INCR_WR_MASK, \
                                    "ANT_CSR_BFNE_INCR41_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START0_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START1_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START2_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START3_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START4_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START5_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START6_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START7_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START8_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START8_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START9_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START9_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START10_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START10_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START11_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START11_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START12_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START12_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START13_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START13_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START14_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START14_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START15_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START15_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START16_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START16_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START17_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START17_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START18_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START18_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START19_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START19_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START20_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START20_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START21_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START21_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START22_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START22_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START23_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START23_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START24_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START24_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START25_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START25_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START26_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START26_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START27_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START27_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START28_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START28_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START29_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START29_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START30_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START30_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START31_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START31_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START32_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START32_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START33_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START33_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START34_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START34_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START35_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START35_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START36_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START36_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START37_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START37_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START38_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START38_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START39_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START39_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START40_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START40_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_START41_OFFSET, \
                                    ANT_CSR_BFNE_START_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_START_RD_MASK, ANT_CSR_BFNE_START_WR_MASK, \
                                    "ANT_CSR_BFNE_START41_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT0_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT1_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT2_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT3_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT4_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT5_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT6_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT7_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT8_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT9_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT10_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT10_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT11_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT11_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT12_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT12_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT13_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT13_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT14_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT14_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT15_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT15_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT16_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT16_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT17_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT17_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT18_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT18_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT19_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT19_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT20_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT20_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT21_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT21_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT22_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT22_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT23_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT23_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT24_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT24_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT25_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT25_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT26_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT26_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT27_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT27_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT28_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT28_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT29_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT29_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT30_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT30_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT31_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT31_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT32_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT32_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT33_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT33_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT34_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT34_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT35_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT35_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT36_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT36_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT37_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT37_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT38_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT38_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT39_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT39_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT40_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT40_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_BFNE_STAT41_OFFSET, \
                                    ANT_CSR_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_BFNE_STAT_RD_MASK, ANT_CSR_BFNE_STAT_WR_MASK, \
                                    "ANT_CSR_BFNE_STAT41_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_BSG_STAT_OFFSET, \
                                    ANT_CSR_ANT_BSG_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_BSG_STAT_RD_MASK, ANT_CSR_ANT_BSG_STAT_WR_MASK, \
                                    "ANT_CSR_ANT_BSG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CMFF_FIFO_STAT_OFFSET, \
                                    ANT_CSR_CMFF_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CMFF_FIFO_STAT_RD_MASK, ANT_CSR_CMFF_FIFO_STAT_WR_MASK, \
                                    "ANT_CSR_CMFF_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_RX_INTR_LO_STAT_OFFSET, \
                                    ANT_CSR_RX_INTR_LO_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_RX_INTR_LO_STAT_RD_MASK, ANT_CSR_RX_INTR_LO_STAT_WR_MASK, \
                                    "ANT_CSR_RX_INTR_LO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_RX_INTR_HI_STAT_OFFSET, \
                                    ANT_CSR_RX_INTR_HI_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_RX_INTR_HI_STAT_RD_MASK, ANT_CSR_RX_INTR_HI_STAT_WR_MASK, \
                                    "ANT_CSR_RX_INTR_HI_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_FB_INTR_LO_STAT_OFFSET, \
                                    ANT_CSR_FB_INTR_LO_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_FB_INTR_LO_STAT_RD_MASK, ANT_CSR_FB_INTR_LO_STAT_WR_MASK, \
                                    "ANT_CSR_FB_INTR_LO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_FB_INTR_HI_STAT_OFFSET, \
                                    ANT_CSR_FB_INTR_HI_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_FB_INTR_HI_STAT_RD_MASK, ANT_CSR_FB_INTR_HI_STAT_WR_MASK, \
                                    "ANT_CSR_FB_INTR_HI_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_TX_INTR_LO_STAT_OFFSET, \
                                    ANT_CSR_TX_INTR_LO_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_TX_INTR_LO_STAT_RD_MASK, ANT_CSR_TX_INTR_LO_STAT_WR_MASK, \
                                    "ANT_CSR_TX_INTR_LO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_TX_INTR_HI_STAT_OFFSET, \
                                    ANT_CSR_TX_INTR_HI_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_TX_INTR_HI_STAT_RD_MASK, ANT_CSR_TX_INTR_HI_STAT_WR_MASK, \
                                    "ANT_CSR_TX_INTR_HI_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_DP_INIT_STAT_OFFSET, \
                                    ANT_CSR_ANT_DP_INIT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_DP_INIT_STAT_RD_MASK, ANT_CSR_ANT_DP_INIT_STAT_WR_MASK, \
                                    "ANT_CSR_ANT_DP_INIT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_ADC_START_BFN_OFFSET, \
                                    ANT_CSR_ANT_RX_ADC_START_BFN_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_ADC_START_BFN_RD_MASK, ANT_CSR_ANT_RX_ADC_START_BFN_WR_MASK, \
                                    "ANT_CSR_ANT_RX_ADC_START_BFN_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_ADC_START_BFN_OFFSET, \
                                    ANT_CSR_ANT_FB_ADC_START_BFN_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_ADC_START_BFN_RD_MASK, ANT_CSR_ANT_FB_ADC_START_BFN_WR_MASK, \
                                    "ANT_CSR_ANT_FB_ADC_START_BFN_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_INT_STAT_R_OFFSET, \
                                    ANT_CSR_CCF_RX_INT_STAT_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_INT_STAT_R_RD_MASK, ANT_CSR_CCF_RX_INT_STAT_R_WR_MASK, \
                                    "ANT_CSR_CCF_RX_INT_STAT_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_INT_HIGH_R_OFFSET, \
                                    ANT_CSR_CCF_RX_INT_HIGH_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_INT_HIGH_R_RD_MASK, ANT_CSR_CCF_RX_INT_HIGH_R_WR_MASK, \
                                    "ANT_CSR_CCF_RX_INT_HIGH_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_INT_LOW_R_OFFSET, \
                                    ANT_CSR_CCF_RX_INT_LOW_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_INT_LOW_R_RD_MASK, ANT_CSR_CCF_RX_INT_LOW_R_WR_MASK, \
                                    "ANT_CSR_CCF_RX_INT_LOW_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_INT_CLR_R_OFFSET, \
                                    ANT_CSR_CCF_RX_INT_CLR_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_INT_CLR_R_RD_MASK, ANT_CSR_CCF_RX_INT_CLR_R_WR_MASK, \
                                    "ANT_CSR_CCF_RX_INT_CLR_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_INT_FORCE_R_OFFSET, \
                                    ANT_CSR_CCF_RX_INT_FORCE_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_INT_FORCE_R_RD_MASK, ANT_CSR_CCF_RX_INT_FORCE_R_WR_MASK, \
                                    "ANT_CSR_CCF_RX_INT_FORCE_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_INT_STAT_R_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_INT_STAT_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_INT_STAT_R_RD_MASK, ANT_CSR_CCF_FB_RX_INT_STAT_R_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_INT_STAT_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_INT_HIGH_R_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_INT_HIGH_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_INT_HIGH_R_RD_MASK, ANT_CSR_CCF_FB_RX_INT_HIGH_R_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_INT_HIGH_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_INT_LOW_R_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_INT_LOW_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_INT_LOW_R_RD_MASK, ANT_CSR_CCF_FB_RX_INT_LOW_R_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_INT_LOW_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_INT_CLR_R_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_INT_CLR_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_INT_CLR_R_RD_MASK, ANT_CSR_CCF_FB_RX_INT_CLR_R_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_INT_CLR_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_INT_FORCE_R_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_INT_FORCE_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_INT_FORCE_R_RD_MASK, ANT_CSR_CCF_FB_RX_INT_FORCE_R_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_INT_FORCE_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_INT_STAT_R_OFFSET, \
                                    ANT_CSR_CCF_TX_INT_STAT_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_INT_STAT_R_RD_MASK, ANT_CSR_CCF_TX_INT_STAT_R_WR_MASK, \
                                    "ANT_CSR_CCF_TX_INT_STAT_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_INT_HIGH_R_OFFSET, \
                                    ANT_CSR_CCF_TX_INT_HIGH_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_INT_HIGH_R_RD_MASK, ANT_CSR_CCF_TX_INT_HIGH_R_WR_MASK, \
                                    "ANT_CSR_CCF_TX_INT_HIGH_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_INT_LOW_R_OFFSET, \
                                    ANT_CSR_CCF_TX_INT_LOW_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_INT_LOW_R_RD_MASK, ANT_CSR_CCF_TX_INT_LOW_R_WR_MASK, \
                                    "ANT_CSR_CCF_TX_INT_LOW_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_INT_CLR_R_OFFSET, \
                                    ANT_CSR_CCF_TX_INT_CLR_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_INT_CLR_R_RD_MASK, ANT_CSR_CCF_TX_INT_CLR_R_WR_MASK, \
                                    "ANT_CSR_CCF_TX_INT_CLR_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_INT_FORCE_R_OFFSET, \
                                    ANT_CSR_CCF_TX_INT_FORCE_R_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_INT_FORCE_R_RD_MASK, ANT_CSR_CCF_TX_INT_FORCE_R_WR_MASK, \
                                    "ANT_CSR_CCF_TX_INT_FORCE_R_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_OUT_STAT0_OFFSET, \
                                    ANT_CSR_CCF_RX_OUT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_OUT_STAT_RD_MASK, ANT_CSR_CCF_RX_OUT_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_OUT_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_OUT_STAT1_OFFSET, \
                                    ANT_CSR_CCF_RX_OUT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_OUT_STAT_RD_MASK, ANT_CSR_CCF_RX_OUT_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_OUT_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_OUT_STAT2_OFFSET, \
                                    ANT_CSR_CCF_RX_OUT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_OUT_STAT_RD_MASK, ANT_CSR_CCF_RX_OUT_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_OUT_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_OUT_STAT3_OFFSET, \
                                    ANT_CSR_CCF_RX_OUT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_OUT_STAT_RD_MASK, ANT_CSR_CCF_RX_OUT_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_OUT_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_IN_STAT0_OFFSET, \
                                    ANT_CSR_CCF_RX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_IN_STAT_RD_MASK, ANT_CSR_CCF_RX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_IN_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_IN_STAT1_OFFSET, \
                                    ANT_CSR_CCF_RX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_IN_STAT_RD_MASK, ANT_CSR_CCF_RX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_IN_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_IN_STAT2_OFFSET, \
                                    ANT_CSR_CCF_RX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_IN_STAT_RD_MASK, ANT_CSR_CCF_RX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_IN_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_RX_IN_STAT3_OFFSET, \
                                    ANT_CSR_CCF_RX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_RX_IN_STAT_RD_MASK, ANT_CSR_CCF_RX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_RX_IN_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_IN_STAT0_OFFSET, \
                                    ANT_CSR_CCF_TX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_IN_STAT_RD_MASK, ANT_CSR_CCF_TX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_TX_IN_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_IN_STAT1_OFFSET, \
                                    ANT_CSR_CCF_TX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_IN_STAT_RD_MASK, ANT_CSR_CCF_TX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_TX_IN_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_IN_STAT2_OFFSET, \
                                    ANT_CSR_CCF_TX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_IN_STAT_RD_MASK, ANT_CSR_CCF_TX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_TX_IN_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_TX_IN_STAT3_OFFSET, \
                                    ANT_CSR_CCF_TX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_TX_IN_STAT_RD_MASK, ANT_CSR_CCF_TX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_TX_IN_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_OUT_STAT_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_OUT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_OUT_STAT_RD_MASK, ANT_CSR_CCF_FB_RX_OUT_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_OUT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_FB_RX_IN_STAT_OFFSET, \
                                    ANT_CSR_CCF_FB_RX_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_FB_RX_IN_STAT_RD_MASK, ANT_CSR_CCF_FB_RX_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_FB_RX_IN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_CCF_DCSRC_IN_STAT_OFFSET, \
                                    ANT_CSR_CCF_DCSRC_IN_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_CCF_DCSRC_IN_STAT_RD_MASK, ANT_CSR_CCF_DCSRC_IN_STAT_WR_MASK, \
                                    "ANT_CSR_CCF_DCSRC_IN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_RX_EN_EVENT_STAT_OFFSET, \
                                    ANT_CSR_ANT_RX_EN_EVENT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_RX_EN_EVENT_STAT_RD_MASK, ANT_CSR_ANT_RX_EN_EVENT_STAT_WR_MASK, \
                                    "ANT_CSR_ANT_RX_EN_EVENT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_TX_EN_EVENT_STAT_OFFSET, \
                                    ANT_CSR_ANT_TX_EN_EVENT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_TX_EN_EVENT_STAT_RD_MASK, ANT_CSR_ANT_TX_EN_EVENT_STAT_WR_MASK, \
                                    "ANT_CSR_ANT_TX_EN_EVENT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+ANT_CSR_ANT_FB_EN_EVENT_STAT_OFFSET, \
                                    ANT_CSR_ANT_FB_EN_EVENT_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_ANT_FB_EN_EVENT_STAT_RD_MASK, ANT_CSR_ANT_FB_EN_EVENT_STAT_WR_MASK, \
                                    "ANT_CSR_ANT_FB_EN_EVENT_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+ANT_CSR_APB_BRDG_STAT_OFFSET, \
                                    ANT_CSR_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    ANT_CSR_APB_BRDG_STAT_RD_MASK, ANT_CSR_APB_BRDG_STAT_WR_MASK, \
                                    "ANT_CSR_APB_BRDG_STAT_OFFSET");

        }

    }

}
