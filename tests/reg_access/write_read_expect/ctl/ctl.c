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
    TRX_ANT0_CTL_BASE, TRX_ANT1_CTL_BASE, TRX_ANT2_CTL_BASE, TRX_ANT3_CTL_BASE, TRX_ANT4_CTL_BASE,
    TRX_ANT5_CTL_BASE, TRX_ANT6_CTL_BASE, TRX_ANT7_CTL_BASE
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
            write_read_expect_18a(base_address[i]+CTL_TX_ANT_RATE_OFFSET, \
                                    CTL_TX_ANT_RATE_DEFAULT, write_data, expected_data, \
                                    CTL_TX_ANT_RATE_RD_MASK, CTL_TX_ANT_RATE_WR_MASK, \
                                    "CTL_TX_ANT_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_RX_ANT_RATE_OFFSET, \
                                    CTL_RX_ANT_RATE_DEFAULT, write_data, expected_data, \
                                    CTL_RX_ANT_RATE_RD_MASK, CTL_RX_ANT_RATE_WR_MASK, \
                                    "CTL_RX_ANT_RATE_OFFSET");

//            write_read_expect_18a(base_address[i]+CTL_DP_INIT_OFFSET, \
                                    CTL_DP_INIT_DEFAULT, write_data, expected_data, \
                                    CTL_DP_INIT_RD_MASK, CTL_DP_INIT_WR_MASK, \
                                    "CTL_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_RX_INT_HI_SUM_OFFSET, \
                                    CTL_RX_INT_HI_SUM_DEFAULT, write_data, expected_data, \
                                    CTL_RX_INT_HI_SUM_RD_MASK, CTL_RX_INT_HI_SUM_WR_MASK, \
                                    "CTL_RX_INT_HI_SUM_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_RX_INT_LO_SUM_OFFSET, \
                                    CTL_RX_INT_LO_SUM_DEFAULT, write_data, expected_data, \
                                    CTL_RX_INT_LO_SUM_RD_MASK, CTL_RX_INT_LO_SUM_WR_MASK, \
                                    "CTL_RX_INT_LO_SUM_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_TX_INT_HI_SUM_OFFSET, \
                                    CTL_TX_INT_HI_SUM_DEFAULT, write_data, expected_data, \
                                    CTL_TX_INT_HI_SUM_RD_MASK, CTL_TX_INT_HI_SUM_WR_MASK, \
                                    "CTL_TX_INT_HI_SUM_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_TX_INT_LO_SUM_OFFSET, \
                                    CTL_TX_INT_LO_SUM_DEFAULT, write_data, expected_data, \
                                    CTL_TX_INT_LO_SUM_RD_MASK, CTL_TX_INT_LO_SUM_WR_MASK, \
                                    "CTL_TX_INT_LO_SUM_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+CTL_BRDG_STAT_OFFSET, \
                                    CTL_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BRDG_STAT_RD_MASK, CTL_BRDG_STAT_WR_MASK, \
                                    "CTL_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_LOOPBK_CTL_OFFSET, \
                                    CTL_LOOPBK_CTL_DEFAULT, write_data, expected_data, \
                                    CTL_LOOPBK_CTL_RD_MASK, CTL_LOOPBK_CTL_WR_MASK, \
                                    "CTL_LOOPBK_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_INT_STAT_OFFSET, \
                                    CTL_SMON_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_INT_STAT_RD_MASK, CTL_SMON_INT_STAT_WR_MASK, \
                                    "CTL_SMON_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_INT_HI_EN_OFFSET, \
                                    CTL_SMON_INT_HI_EN_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_INT_HI_EN_RD_MASK, CTL_SMON_INT_HI_EN_WR_MASK, \
                                    "CTL_SMON_INT_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_INT_LO_EN_OFFSET, \
                                    CTL_SMON_INT_LO_EN_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_INT_LO_EN_RD_MASK, CTL_SMON_INT_LO_EN_WR_MASK, \
                                    "CTL_SMON_INT_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_INT_CLR_OFFSET, \
                                    CTL_SMON_INT_CLR_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_INT_CLR_RD_MASK, CTL_SMON_INT_CLR_WR_MASK, \
                                    "CTL_SMON_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_INT_FORCE_OFFSET, \
                                    CTL_SMON_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_INT_FORCE_RD_MASK, CTL_SMON_INT_FORCE_WR_MASK, \
                                    "CTL_SMON_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_DITHER_SHDW0_OFFSET, \
                                    CTL_DL_SMC_DITHER_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_DITHER_SHDW0_RD_MASK, CTL_DL_SMC_DITHER_SHDW0_WR_MASK, \
                                    "CTL_DL_SMC_DITHER_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_LSB_OFFSET_SHDW0_OFFSET, \
                                    CTL_DL_SMC_LSB_OFFSET_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_LSB_OFFSET_SHDW0_RD_MASK, CTL_DL_SMC_LSB_OFFSET_SHDW0_WR_MASK, \
                                    "CTL_DL_SMC_LSB_OFFSET_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_TXM_ENA_SHDW0_OFFSET, \
                                    CTL_DL_TXM_ENA_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_TXM_ENA_SHDW0_RD_MASK, CTL_DL_TXM_ENA_SHDW0_WR_MASK, \
                                    "CTL_DL_TXM_ENA_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_ENA_SHDW0_OFFSET, \
                                    CTL_UL_RXM_ENA_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_ENA_SHDW0_RD_MASK, CTL_UL_RXM_ENA_SHDW0_WR_MASK, \
                                    "CTL_UL_RXM_ENA_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_PS_SHDW0_OFFSET, \
                                    CTL_UL_RXM_PS_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_PS_SHDW0_RD_MASK, CTL_UL_RXM_PS_SHDW0_WR_MASK, \
                                    "CTL_UL_RXM_PS_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET, \
                                    CTL_UL_NLEQ_ZERO_STUFF_SHDW0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_NLEQ_ZERO_STUFF_SHDW0_RD_MASK, CTL_UL_NLEQ_ZERO_STUFF_SHDW0_WR_MASK, \
                                    "CTL_UL_NLEQ_ZERO_STUFF_SHDW0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_DITHER_SHDW1_OFFSET, \
                                    CTL_DL_SMC_DITHER_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_DITHER_SHDW1_RD_MASK, CTL_DL_SMC_DITHER_SHDW1_WR_MASK, \
                                    "CTL_DL_SMC_DITHER_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_LSB_OFFSET_SHDW1_OFFSET, \
                                    CTL_DL_SMC_LSB_OFFSET_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_LSB_OFFSET_SHDW1_RD_MASK, CTL_DL_SMC_LSB_OFFSET_SHDW1_WR_MASK, \
                                    "CTL_DL_SMC_LSB_OFFSET_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_TXM_ENA_SHDW1_OFFSET, \
                                    CTL_DL_TXM_ENA_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_TXM_ENA_SHDW1_RD_MASK, CTL_DL_TXM_ENA_SHDW1_WR_MASK, \
                                    "CTL_DL_TXM_ENA_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_ENA_SHDW1_OFFSET, \
                                    CTL_UL_RXM_ENA_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_ENA_SHDW1_RD_MASK, CTL_UL_RXM_ENA_SHDW1_WR_MASK, \
                                    "CTL_UL_RXM_ENA_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_PS_SHDW1_OFFSET, \
                                    CTL_UL_RXM_PS_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_PS_SHDW1_RD_MASK, CTL_UL_RXM_PS_SHDW1_WR_MASK, \
                                    "CTL_UL_RXM_PS_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET, \
                                    CTL_UL_NLEQ_ZERO_STUFF_SHDW1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_NLEQ_ZERO_STUFF_SHDW1_RD_MASK, CTL_UL_NLEQ_ZERO_STUFF_SHDW1_WR_MASK, \
                                    "CTL_UL_NLEQ_ZERO_STUFF_SHDW1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_DITHER_LIVE0_OFFSET, \
                                    CTL_DL_SMC_DITHER_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_DITHER_LIVE0_RD_MASK, CTL_DL_SMC_DITHER_LIVE0_WR_MASK, \
                                    "CTL_DL_SMC_DITHER_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_LSB_OFFSET_LIVE0_OFFSET, \
                                    CTL_DL_SMC_LSB_OFFSET_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_LSB_OFFSET_LIVE0_RD_MASK, CTL_DL_SMC_LSB_OFFSET_LIVE0_WR_MASK, \
                                    "CTL_DL_SMC_LSB_OFFSET_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_TXM_ENA_LIVE0_OFFSET, \
                                    CTL_DL_TXM_ENA_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_DL_TXM_ENA_LIVE0_RD_MASK, CTL_DL_TXM_ENA_LIVE0_WR_MASK, \
                                    "CTL_DL_TXM_ENA_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_ENA_LIVE0_OFFSET, \
                                    CTL_UL_RXM_ENA_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_ENA_LIVE0_RD_MASK, CTL_UL_RXM_ENA_LIVE0_WR_MASK, \
                                    "CTL_UL_RXM_ENA_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_PS_LIVE0_OFFSET, \
                                    CTL_UL_RXM_PS_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_PS_LIVE0_RD_MASK, CTL_UL_RXM_PS_LIVE0_WR_MASK, \
                                    "CTL_UL_RXM_PS_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET, \
                                    CTL_UL_NLEQ_ZERO_STUFF_LIVE0_DEFAULT, write_data, expected_data, \
                                    CTL_UL_NLEQ_ZERO_STUFF_LIVE0_RD_MASK, CTL_UL_NLEQ_ZERO_STUFF_LIVE0_WR_MASK, \
                                    "CTL_UL_NLEQ_ZERO_STUFF_LIVE0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_DITHER_LIVE1_OFFSET, \
                                    CTL_DL_SMC_DITHER_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_DITHER_LIVE1_RD_MASK, CTL_DL_SMC_DITHER_LIVE1_WR_MASK, \
                                    "CTL_DL_SMC_DITHER_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_SMC_LSB_OFFSET_LIVE1_OFFSET, \
                                    CTL_DL_SMC_LSB_OFFSET_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_SMC_LSB_OFFSET_LIVE1_RD_MASK, CTL_DL_SMC_LSB_OFFSET_LIVE1_WR_MASK, \
                                    "CTL_DL_SMC_LSB_OFFSET_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_DL_TXM_ENA_LIVE1_OFFSET, \
                                    CTL_DL_TXM_ENA_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_DL_TXM_ENA_LIVE1_RD_MASK, CTL_DL_TXM_ENA_LIVE1_WR_MASK, \
                                    "CTL_DL_TXM_ENA_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_ENA_LIVE1_OFFSET, \
                                    CTL_UL_RXM_ENA_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_ENA_LIVE1_RD_MASK, CTL_UL_RXM_ENA_LIVE1_WR_MASK, \
                                    "CTL_UL_RXM_ENA_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_RXM_PS_LIVE1_OFFSET, \
                                    CTL_UL_RXM_PS_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_RXM_PS_LIVE1_RD_MASK, CTL_UL_RXM_PS_LIVE1_WR_MASK, \
                                    "CTL_UL_RXM_PS_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET, \
                                    CTL_UL_NLEQ_ZERO_STUFF_LIVE1_DEFAULT, write_data, expected_data, \
                                    CTL_UL_NLEQ_ZERO_STUFF_LIVE1_RD_MASK, CTL_UL_NLEQ_ZERO_STUFF_LIVE1_WR_MASK, \
                                    "CTL_UL_NLEQ_ZERO_STUFF_LIVE1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ULDL_STAT_OFFSET, \
                                    CTL_ULDL_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_ULDL_STAT_RD_MASK, CTL_ULDL_STAT_WR_MASK, \
                                    "CTL_ULDL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R0_OFFSET, \
                                    CTL_SMON_R0_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R0_RD_MASK, CTL_SMON_R0_WR_MASK, \
                                    "CTL_SMON_R0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R1_OFFSET, \
                                    CTL_SMON_R1_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R1_RD_MASK, CTL_SMON_R1_WR_MASK, \
                                    "CTL_SMON_R1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R2_OFFSET, \
                                    CTL_SMON_R2_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R2_RD_MASK, CTL_SMON_R2_WR_MASK, \
                                    "CTL_SMON_R2_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R3_OFFSET, \
                                    CTL_SMON_R3_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R3_RD_MASK, CTL_SMON_R3_WR_MASK, \
                                    "CTL_SMON_R3_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R4_OFFSET, \
                                    CTL_SMON_R4_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R4_RD_MASK, CTL_SMON_R4_WR_MASK, \
                                    "CTL_SMON_R4_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R5_OFFSET, \
                                    CTL_SMON_R5_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R5_RD_MASK, CTL_SMON_R5_WR_MASK, \
                                    "CTL_SMON_R5_OFFSET");

//            write_read_expect_18a(base_address[i]+CTL_SMON_R6_OFFSET, \
                                    CTL_SMON_R6_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R6_RD_MASK, CTL_SMON_R6_WR_MASK, \
                                    "CTL_SMON_R6_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_SMON_R7_OFFSET, \
                                    CTL_SMON_R7_DEFAULT, write_data, expected_data, \
                                    CTL_SMON_R7_RD_MASK, CTL_SMON_R7_WR_MASK, \
                                    "CTL_SMON_R7_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_CTRL_OFFSET, \
                                    CTL_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_CTRL_RD_MASK, CTL_ISYNC_CTRL_WR_MASK, \
                                    "CTL_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_LCNT_INC_OFFSET, \
                                    CTL_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_LCNT_INC_RD_MASK, CTL_ISYNC_LCNT_INC_WR_MASK, \
                                    "CTL_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_TEN_MS_CNT_OFFSET, \
                                    CTL_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_TEN_MS_CNT_RD_MASK, CTL_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "CTL_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_INC_PRE_OFFSET, \
                                    CTL_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_INC_PRE_RD_MASK, CTL_ISYNC_INC_PRE_WR_MASK, \
                                    "CTL_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_CNT_ADJ_OFFSET, \
                                    CTL_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_CNT_ADJ_RD_MASK, CTL_ISYNC_CNT_ADJ_WR_MASK, \
                                    "CTL_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    CTL_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_BFN_CNT_SYNC_RD_MASK, CTL_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "CTL_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_ISYNC_BFN_CNT_OFFSET, \
                                    CTL_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    CTL_ISYNC_BFN_CNT_RD_MASK, CTL_ISYNC_BFN_CNT_WR_MASK, \
                                    "CTL_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG0_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG1_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG2_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG3_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG4_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG5_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG6_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG7_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG8_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG8_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG9_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG9_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG10_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG10_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG11_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG11_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_CFG12_OFFSET, \
                                    CTL_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_CFG_RD_MASK, CTL_BFNE_CFG_WR_MASK, \
                                    "CTL_BFNE_CFG12_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR0_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR1_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR2_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR3_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR4_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR5_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR6_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR7_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR8_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR8_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR9_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR9_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR10_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR10_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR11_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR11_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_INCR12_OFFSET, \
                                    CTL_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_INCR_RD_MASK, CTL_BFNE_INCR_WR_MASK, \
                                    "CTL_BFNE_INCR12_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START0_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START1_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START2_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START3_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START4_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START5_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START6_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START7_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START8_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START8_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START9_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START9_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START10_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START10_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START11_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START11_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_START12_OFFSET, \
                                    CTL_BFNE_START_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_START_RD_MASK, CTL_BFNE_START_WR_MASK, \
                                    "CTL_BFNE_START12_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT0_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT1_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT2_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT3_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT4_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT5_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT6_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT7_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT8_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT9_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT10_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT10_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT11_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT11_OFFSET");

            write_read_expect_18a(base_address[i]+CTL_BFNE_STAT12_OFFSET, \
                                    CTL_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    CTL_BFNE_STAT_RD_MASK, CTL_BFNE_STAT_WR_MASK, \
                                    "CTL_BFNE_STAT12_OFFSET");

        }

    }

}
