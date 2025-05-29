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
    VEXABC0_C2S_CIO2STRM_BASE, VEXABC1_C2S_CIO2STRM_BASE, VEXABC2_C2S_CIO2STRM_BASE, VEXABC3_C2S_CIO2STRM_BASE, VEXABC4_C2S_CIO2STRM_BASE,
    VEXABC5_C2S_CIO2STRM_BASE, VEXABC6_C2S_CIO2STRM_BASE, VEXABC7_C2S_CIO2STRM_BASE, VEXABC8_C2S_CIO2STRM_BASE, VEXABC9_C2S_CIO2STRM_BASE,
    VEXABC10_C2S_CIO2STRM_BASE, VEXABC11_C2S_CIO2STRM_BASE, VEXABC12_C2S_CIO2STRM_BASE, VEXABC13_C2S_CIO2STRM_BASE, VEXABC14_C2S_CIO2STRM_BASE,
    VEXABC15_C2S_CIO2STRM_BASE, VEXABC16_C2S_CIO2STRM_BASE, VEXABC17_C2S_CIO2STRM_BASE, VEXABC18_C2S_CIO2STRM_BASE, VEXABC19_C2S_CIO2STRM_BASE,
    VEXABC20_C2S_CIO2STRM_BASE, VEXABC21_C2S_CIO2STRM_BASE, VEXABC22_C2S_CIO2STRM_BASE, VEXABC23_C2S_CIO2STRM_BASE, VEXABC24_C2S_CIO2STRM_BASE,
    VEXABC25_C2S_CIO2STRM_BASE, VEXABC26_C2S_CIO2STRM_BASE, VEXABC27_C2S_CIO2STRM_BASE, VEXABC28_C2S_CIO2STRM_BASE, VEXABC29_C2S_CIO2STRM_BASE,
    VEXABC30_C2S_CIO2STRM_BASE, VEXABC31_C2S_CIO2STRM_BASE, VEXABC32_C2S_CIO2STRM_BASE, VEXABC33_C2S_CIO2STRM_BASE, VEXABC34_C2S_CIO2STRM_BASE,
    VEXABC35_C2S_CIO2STRM_BASE, VEXABC36_C2S_CIO2STRM_BASE, VEXABC37_C2S_CIO2STRM_BASE, VEXABC38_C2S_CIO2STRM_BASE, VEXABC39_C2S_CIO2STRM_BASE
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
           LOG_PRINT("i is %d", i);
            if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
                continue;
            }
            else
            {
		   write_read_expect_18a(base_address[i]+CIO2STRM_CREDIT_CNT_OFFSET, \
                                    CIO2STRM_CREDIT_CNT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_CREDIT_CNT_RD_MASK, CIO2STRM_CREDIT_CNT_WR_MASK, \
                                    "CIO2STRM_CREDIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_CREDIT_CNT_STAT_OFFSET, \
                                    CIO2STRM_CREDIT_CNT_STAT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_CREDIT_CNT_STAT_RD_MASK, CIO2STRM_CREDIT_CNT_STAT_WR_MASK, \
                                    "CIO2STRM_CREDIT_CNT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_FIFO_STAT_CTL_OFFSET, \
                                    CIO2STRM_FIFO_STAT_CTL_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_FIFO_STAT_CTL_RD_MASK, CIO2STRM_FIFO_STAT_CTL_WR_MASK, \
                                    "CIO2STRM_FIFO_STAT_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_FIFO_STAT_OFFSET, \
                                    CIO2STRM_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_FIFO_STAT_RD_MASK, CIO2STRM_FIFO_STAT_WR_MASK, \
                                    "CIO2STRM_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_WORD_CNT_CTL_OFFSET, \
                                    CIO2STRM_WORD_CNT_CTL_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_WORD_CNT_CTL_RD_MASK, CIO2STRM_WORD_CNT_CTL_WR_MASK, \
                                    "CIO2STRM_WORD_CNT_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_WORD_CNT_OFFSET, \
                                    CIO2STRM_WORD_CNT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_WORD_CNT_RD_MASK, CIO2STRM_WORD_CNT_WR_MASK, \
                                    "CIO2STRM_WORD_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STALL_CNT_CTL_OFFSET, \
                                    CIO2STRM_STALL_CNT_CTL_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STALL_CNT_CTL_RD_MASK, CIO2STRM_STALL_CNT_CTL_WR_MASK, \
                                    "CIO2STRM_STALL_CNT_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STALL_CNT_OFFSET, \
                                    CIO2STRM_STALL_CNT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STALL_CNT_RD_MASK, CIO2STRM_STALL_CNT_WR_MASK, \
                                    "CIO2STRM_STALL_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_READY_FORCE_OFFSET, \
                                    CIO2STRM_STRM_READY_FORCE_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_READY_FORCE_RD_MASK, CIO2STRM_STRM_READY_FORCE_WR_MASK, \
                                    "CIO2STRM_STRM_READY_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_INT_STAT_OFFSET, \
                                    CIO2STRM_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_INT_STAT_RD_MASK, CIO2STRM_INT_STAT_WR_MASK, \
                                    "CIO2STRM_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_INT_EN_OFFSET, \
                                    CIO2STRM_INT_EN_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_INT_EN_RD_MASK, CIO2STRM_INT_EN_WR_MASK, \
                                    "CIO2STRM_INT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_INT_CLR_OFFSET, \
                                    CIO2STRM_INT_CLR_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_INT_CLR_RD_MASK, CIO2STRM_INT_CLR_WR_MASK, \
                                    "CIO2STRM_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_INT_FORCE_OFFSET, \
                                    CIO2STRM_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_INT_FORCE_RD_MASK, CIO2STRM_INT_FORCE_WR_MASK, \
                                    "CIO2STRM_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_INT_MASKED_STAT_OFFSET, \
                                    CIO2STRM_INT_MASKED_STAT_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_INT_MASKED_STAT_RD_MASK, CIO2STRM_INT_MASKED_STAT_WR_MASK, \
                                    "CIO2STRM_INT_MASKED_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_RANGE_EN_OFFSET, \
                                    CIO2STRM_RANGE_EN_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_RANGE_EN_RD_MASK, CIO2STRM_RANGE_EN_WR_MASK, \
                                    "CIO2STRM_RANGE_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_RANGE_ERR_OFFSET, \
                                    CIO2STRM_RANGE_ERR_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_RANGE_ERR_RD_MASK, CIO2STRM_RANGE_ERR_WR_MASK, \
                                    "CIO2STRM_RANGE_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW0_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW0_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW1_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW1_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW2_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW2_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW3_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW3_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW4_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW4_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW5_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW5_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW6_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW6_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW7_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW7_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW8_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW8_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW9_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW9_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW10_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW10_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW11_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW11_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW12_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW12_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW13_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW13_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW14_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW14_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_LOW15_OFFSET, \
                                    CIO2STRM_MEM_ADDR_LOW_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_LOW_RD_MASK, CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_LOW15_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH0_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH0_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH1_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH1_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH2_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH2_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH3_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH3_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH4_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH4_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH5_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH5_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH6_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH6_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH7_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH7_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH8_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH8_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH9_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH9_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH10_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH10_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH11_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH11_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH12_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH12_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH13_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH13_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH14_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH14_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_ADDR_HIGH15_OFFSET, \
                                    CIO2STRM_MEM_ADDR_HIGH_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_ADDR_HIGH_RD_MASK, CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
                                    "CIO2STRM_MEM_ADDR_HIGH15_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET0_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET0_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET1_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET1_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET2_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET2_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET3_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET3_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET4_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET4_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET5_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET5_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET6_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET6_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET7_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET7_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET8_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET8_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET9_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET9_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET10_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET10_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET11_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET11_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET12_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET12_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET13_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET13_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET14_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET14_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_MEM_OFFSET15_OFFSET, \
                                    CIO2STRM_MEM_OFFSET_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_MEM_OFFSET_RD_MASK, CIO2STRM_MEM_OFFSET_WR_MASK, \
                                    "CIO2STRM_MEM_OFFSET15_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST0_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST0_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST1_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST1_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST2_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST2_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST3_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST3_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST4_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST4_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST5_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST5_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST6_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST6_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST7_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST7_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST8_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST8_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST9_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST9_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST10_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST10_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST11_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST11_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST12_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST12_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST13_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST13_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST14_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST14_OFFSET");

            write_read_expect_18a(base_address[i]+CIO2STRM_STRM_DEST15_OFFSET, \
                                    CIO2STRM_STRM_DEST_DEFAULT, write_data, expected_data, \
                                    CIO2STRM_STRM_DEST_RD_MASK, CIO2STRM_STRM_DEST_WR_MASK, \
                                    "CIO2STRM_STRM_DEST15_OFFSET");

        }

    }

}
}
