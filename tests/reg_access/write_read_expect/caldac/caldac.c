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
    FB_ANT0_CALDAC_BASE, FB_ANT1_CALDAC_BASE
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
            write_read_expect_18a(base_address[i]+CALDAC_SCRATCH_OFFSET, \
                                    CALDAC_SCRATCH_DEFAULT, write_data, expected_data, \
                                    CALDAC_SCRATCH_RD_MASK, CALDAC_SCRATCH_WR_MASK, \
                                    "CALDAC_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_WM_TOP_OFFSET, \
                                    CALDAC_FIFOE_WM_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_WM_TOP_RD_MASK, CALDAC_FIFOE_WM_TOP_WR_MASK, \
                                    "CALDAC_FIFOE_WM_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_WM_TOP_OFFSET, \
                                    CALDAC_FIFOO_WM_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_WM_TOP_RD_MASK, CALDAC_FIFOO_WM_TOP_WR_MASK, \
                                    "CALDAC_FIFOO_WM_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_CTL_TOP_OFFSET, \
                                    CALDAC_FIFOE_CTL_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_CTL_TOP_RD_MASK, CALDAC_FIFOE_CTL_TOP_WR_MASK, \
                                    "CALDAC_FIFOE_CTL_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_CTL_TOP_OFFSET, \
                                    CALDAC_FIFOO_CTL_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_CTL_TOP_RD_MASK, CALDAC_FIFOO_CTL_TOP_WR_MASK, \
                                    "CALDAC_FIFOO_CTL_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_STAT_TOP_OFFSET, \
                                    CALDAC_FIFOE_STAT_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_STAT_TOP_RD_MASK, CALDAC_FIFOE_STAT_TOP_WR_MASK, \
                                    "CALDAC_FIFOE_STAT_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_STAT_TOP_OFFSET, \
                                    CALDAC_FIFOO_STAT_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_STAT_TOP_RD_MASK, CALDAC_FIFOO_STAT_TOP_WR_MASK, \
                                    "CALDAC_FIFOO_STAT_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_WM_BOT_OFFSET, \
                                    CALDAC_FIFOE_WM_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_WM_BOT_RD_MASK, CALDAC_FIFOE_WM_BOT_WR_MASK, \
                                    "CALDAC_FIFOE_WM_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_WM_BOT_OFFSET, \
                                    CALDAC_FIFOO_WM_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_WM_BOT_RD_MASK, CALDAC_FIFOO_WM_BOT_WR_MASK, \
                                    "CALDAC_FIFOO_WM_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_CTL_BOT_OFFSET, \
                                    CALDAC_FIFOE_CTL_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_CTL_BOT_RD_MASK, CALDAC_FIFOE_CTL_BOT_WR_MASK, \
                                    "CALDAC_FIFOE_CTL_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_CTL_BOT_OFFSET, \
                                    CALDAC_FIFOO_CTL_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_CTL_BOT_RD_MASK, CALDAC_FIFOO_CTL_BOT_WR_MASK, \
                                    "CALDAC_FIFOO_CTL_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOE_STAT_BOT_OFFSET, \
                                    CALDAC_FIFOE_STAT_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOE_STAT_BOT_RD_MASK, CALDAC_FIFOE_STAT_BOT_WR_MASK, \
                                    "CALDAC_FIFOE_STAT_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFOO_STAT_BOT_OFFSET, \
                                    CALDAC_FIFOO_STAT_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFOO_STAT_BOT_RD_MASK, CALDAC_FIFOO_STAT_BOT_WR_MASK, \
                                    "CALDAC_FIFOO_STAT_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_GAIN0_EVEN_OFFSET, \
                                    CALDAC_GAIN0_EVEN_DEFAULT, write_data, expected_data, \
                                    CALDAC_GAIN0_EVEN_RD_MASK, CALDAC_GAIN0_EVEN_WR_MASK, \
                                    "CALDAC_GAIN0_EVEN_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_GAIN1_EVEN_OFFSET, \
                                    CALDAC_GAIN1_EVEN_DEFAULT, write_data, expected_data, \
                                    CALDAC_GAIN1_EVEN_RD_MASK, CALDAC_GAIN1_EVEN_WR_MASK, \
                                    "CALDAC_GAIN1_EVEN_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_GAIN0_ODD_OFFSET, \
                                    CALDAC_GAIN0_ODD_DEFAULT, write_data, expected_data, \
                                    CALDAC_GAIN0_ODD_RD_MASK, CALDAC_GAIN0_ODD_WR_MASK, \
                                    "CALDAC_GAIN0_ODD_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_GAIN1_ODD_OFFSET, \
                                    CALDAC_GAIN1_ODD_DEFAULT, write_data, expected_data, \
                                    CALDAC_GAIN1_ODD_RD_MASK, CALDAC_GAIN1_ODD_WR_MASK, \
                                    "CALDAC_GAIN1_ODD_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_CTRL_SWG_DITHER_OFFSET, \
                                    CALDAC_CTRL_SWG_DITHER_DEFAULT, write_data, expected_data, \
                                    CALDAC_CTRL_SWG_DITHER_RD_MASK, CALDAC_CTRL_SWG_DITHER_WR_MASK, \
                                    "CALDAC_CTRL_SWG_DITHER_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_CTRL_SWG_SIGN_OFFSET, \
                                    CALDAC_CTRL_SWG_SIGN_DEFAULT, write_data, expected_data, \
                                    CALDAC_CTRL_SWG_SIGN_RD_MASK, CALDAC_CTRL_SWG_SIGN_WR_MASK, \
                                    "CALDAC_CTRL_SWG_SIGN_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_MAX_ABS_OFFSET, \
                                    CALDAC_MAX_ABS_DEFAULT, write_data, expected_data, \
                                    CALDAC_MAX_ABS_RD_MASK, CALDAC_MAX_ABS_WR_MASK, \
                                    "CALDAC_MAX_ABS_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_SMC_RATE_OFFSET, \
                                    CALDAC_SMC_RATE_DEFAULT, write_data, expected_data, \
                                    CALDAC_SMC_RATE_RD_MASK, CALDAC_SMC_RATE_WR_MASK, \
                                    "CALDAC_SMC_RATE_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_FIFO_RST_OFFSET, \
                                    CALDAC_FIFO_RST_DEFAULT, write_data, expected_data, \
                                    CALDAC_FIFO_RST_RD_MASK, CALDAC_FIFO_RST_WR_MASK, \
                                    "CALDAC_FIFO_RST_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_INT_STAT_OFFSET, \
                                    CALDAC_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CALDAC_INT_STAT_RD_MASK, CALDAC_INT_STAT_WR_MASK, \
                                    "CALDAC_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_INT_HI_EN_OFFSET, \
                                    CALDAC_INT_HI_EN_DEFAULT, write_data, expected_data, \
                                    CALDAC_INT_HI_EN_RD_MASK, CALDAC_INT_HI_EN_WR_MASK, \
                                    "CALDAC_INT_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_INT_LO_EN_OFFSET, \
                                    CALDAC_INT_LO_EN_DEFAULT, write_data, expected_data, \
                                    CALDAC_INT_LO_EN_RD_MASK, CALDAC_INT_LO_EN_WR_MASK, \
                                    "CALDAC_INT_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_INT_CLR_OFFSET, \
                                    CALDAC_INT_CLR_DEFAULT, write_data, expected_data, \
                                    CALDAC_INT_CLR_RD_MASK, CALDAC_INT_CLR_WR_MASK, \
                                    "CALDAC_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_INT_FORCE_OFFSET, \
                                    CALDAC_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    CALDAC_INT_FORCE_RD_MASK, CALDAC_INT_FORCE_WR_MASK, \
                                    "CALDAC_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAP_OFFSET, \
                                    CALDAC_DBG_SNAP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAP_RD_MASK, CALDAC_DBG_SNAP_WR_MASK, \
                                    "CALDAC_DBG_SNAP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAP_PCNT_TOP_OFFSET, \
                                    CALDAC_DBG_SNAP_PCNT_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAP_PCNT_TOP_RD_MASK, CALDAC_DBG_SNAP_PCNT_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAP_PCNT_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAP_CNT_TOP_OFFSET, \
                                    CALDAC_DBG_SNAP_CNT_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAP_CNT_TOP_RD_MASK, CALDAC_DBG_SNAP_CNT_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAP_CNT_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP0_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP0_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP1_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP1_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP2_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP2_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP3_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP3_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP4_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP4_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP5_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP5_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP6_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP6_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_TOP7_OFFSET, \
                                    CALDAC_DBG_SNAPO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_TOP_RD_MASK, CALDAC_DBG_SNAPO_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_TOP7_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP0_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP0_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP1_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP1_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP2_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP2_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP3_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP3_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP4_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP4_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP5_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP5_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP6_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP6_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_TOP7_OFFSET, \
                                    CALDAC_DBG_SNAPE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_TOP_RD_MASK, CALDAC_DBG_SNAPE_TOP_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_TOP7_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAP_PCNT_BOT_OFFSET, \
                                    CALDAC_DBG_SNAP_PCNT_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAP_PCNT_BOT_RD_MASK, CALDAC_DBG_SNAP_PCNT_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAP_PCNT_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAP_CNT_BOT_OFFSET, \
                                    CALDAC_DBG_SNAP_CNT_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAP_CNT_BOT_RD_MASK, CALDAC_DBG_SNAP_CNT_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAP_CNT_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT0_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT0_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT1_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT1_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT2_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT2_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT3_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT3_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT4_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT4_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT5_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT5_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT6_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT6_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPO_BOT7_OFFSET, \
                                    CALDAC_DBG_SNAPO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPO_BOT_RD_MASK, CALDAC_DBG_SNAPO_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPO_BOT7_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT0_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT0_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT1_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT1_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT2_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT2_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT3_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT3_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT4_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT4_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT5_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT5_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT6_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT6_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_SNAPE_BOT7_OFFSET, \
                                    CALDAC_DBG_SNAPE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_SNAPE_BOT_RD_MASK, CALDAC_DBG_SNAPE_BOT_WR_MASK, \
                                    "CALDAC_DBG_SNAPE_BOT7_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_FFS_BFN_TOP_OFFSET, \
                                    CALDAC_DBG_FFS_BFN_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_FFS_BFN_TOP_RD_MASK, CALDAC_DBG_FFS_BFN_TOP_WR_MASK, \
                                    "CALDAC_DBG_FFS_BFN_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_FFS_BFN_BOT_OFFSET, \
                                    CALDAC_DBG_FFS_BFN_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_FFS_BFN_BOT_RD_MASK, CALDAC_DBG_FFS_BFN_BOT_WR_MASK, \
                                    "CALDAC_DBG_FFS_BFN_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_FFS_LVL_OFFSET, \
                                    CALDAC_DBG_FFS_LVL_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_FFS_LVL_RD_MASK, CALDAC_DBG_FFS_LVL_WR_MASK, \
                                    "CALDAC_DBG_FFS_LVL_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_VALS_BFNO_TOP_OFFSET, \
                                    CALDAC_DBG_VALS_BFNO_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_VALS_BFNO_TOP_RD_MASK, CALDAC_DBG_VALS_BFNO_TOP_WR_MASK, \
                                    "CALDAC_DBG_VALS_BFNO_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_VALS_BFNE_TOP_OFFSET, \
                                    CALDAC_DBG_VALS_BFNE_TOP_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_VALS_BFNE_TOP_RD_MASK, CALDAC_DBG_VALS_BFNE_TOP_WR_MASK, \
                                    "CALDAC_DBG_VALS_BFNE_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_VALS_BFNO_BOT_OFFSET, \
                                    CALDAC_DBG_VALS_BFNO_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_VALS_BFNO_BOT_RD_MASK, CALDAC_DBG_VALS_BFNO_BOT_WR_MASK, \
                                    "CALDAC_DBG_VALS_BFNO_BOT_OFFSET");

            write_read_expect_18a(base_address[i]+CALDAC_DBG_VALS_BFNE_BOT_OFFSET, \
                                    CALDAC_DBG_VALS_BFNE_BOT_DEFAULT, write_data, expected_data, \
                                    CALDAC_DBG_VALS_BFNE_BOT_RD_MASK, CALDAC_DBG_VALS_BFNE_BOT_WR_MASK, \
                                    "CALDAC_DBG_VALS_BFNE_BOT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+CALDAC_APB_BRDG_STAT_OFFSET, \
                                    CALDAC_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    CALDAC_APB_BRDG_STAT_RD_MASK, CALDAC_APB_BRDG_STAT_WR_MASK, \
                                    "CALDAC_APB_BRDG_STAT_OFFSET");

        }

    }

}
