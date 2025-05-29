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
    V2D0_AV2D_APB_0_NSIP_HBI_0_BASE, V2D0_AV2D_APB_0_NSIP_HBI_1_BASE, V2D0_AV2D_APB_1_NSIP_HBI_0_BASE, V2D0_AV2D_APB_1_NSIP_HBI_1_BASE, V2D1_AV2D_APB_0_NSIP_HBI_0_BASE,
    V2D1_AV2D_APB_0_NSIP_HBI_1_BASE, V2D1_AV2D_APB_1_NSIP_HBI_0_BASE, V2D1_AV2D_APB_1_NSIP_HBI_1_BASE, V2D2_AV2D_APB_0_NSIP_HBI_0_BASE, V2D2_AV2D_APB_0_NSIP_HBI_1_BASE,
    V2D2_AV2D_APB_1_NSIP_HBI_0_BASE, V2D2_AV2D_APB_1_NSIP_HBI_1_BASE, V2D3_AV2D_APB_0_NSIP_HBI_0_BASE, V2D3_AV2D_APB_0_NSIP_HBI_1_BASE, V2D3_AV2D_APB_1_NSIP_HBI_0_BASE,
    V2D3_AV2D_APB_1_NSIP_HBI_1_BASE, V2D4_AV2D_APB_0_NSIP_HBI_0_BASE, V2D4_AV2D_APB_0_NSIP_HBI_1_BASE, V2D4_AV2D_APB_1_NSIP_HBI_0_BASE, V2D4_AV2D_APB_1_NSIP_HBI_1_BASE,
    V2D5_AV2D_APB_0_NSIP_HBI_0_BASE, V2D5_AV2D_APB_0_NSIP_HBI_1_BASE, V2D5_AV2D_APB_1_NSIP_HBI_0_BASE, V2D5_AV2D_APB_1_NSIP_HBI_1_BASE, V2D6_AV2D_APB_0_NSIP_HBI_0_BASE,
    V2D6_AV2D_APB_0_NSIP_HBI_1_BASE, V2D6_AV2D_APB_1_NSIP_HBI_0_BASE, V2D6_AV2D_APB_1_NSIP_HBI_1_BASE, V2D7_AV2D_APB_0_NSIP_HBI_0_BASE, V2D7_AV2D_APB_0_NSIP_HBI_1_BASE,
    V2D7_AV2D_APB_1_NSIP_HBI_0_BASE, V2D7_AV2D_APB_1_NSIP_HBI_1_BASE};


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
            write_read_expect_18a(base_address[i]+NSIP_HBI_SCRATCH_OFFSET, \
                                    NSIP_HBI_SCRATCH_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SCRATCH_RD_MASK, NSIP_HBI_SCRATCH_WR_MASK, \
                                    "NSIP_HBI_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET, \
                                    NSIP_HBI_B2H_FF_FIFO_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_FF_FIFO_CTRL_RD_MASK, NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK, \
                                    "NSIP_HBI_B2H_FF_FIFO_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_FF_FIFO_STAT_OFFSET, \
                                    NSIP_HBI_B2H_FF_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_FF_FIFO_STAT_RD_MASK, NSIP_HBI_B2H_FF_FIFO_STAT_WR_MASK, \
                                    "NSIP_HBI_B2H_FF_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET, \
                                    NSIP_HBI_B2H_CSR_CREDIT_CS_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_CREDIT_CS_RD_MASK, NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_CREDIT_CS_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, \
                                    NSIP_HBI_B2H_CSR_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_FLIT_CNT_RD_MASK, NSIP_HBI_B2H_CSR_FLIT_CNT_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_INSERT_STRM_OFFSET, \
                                    NSIP_HBI_B2H_CSR_INSERT_STRM_DEFAULT, write_data, expected_data, \
                                    0x7, 0x7, \
                                    "NSIP_HBI_B2H_CSR_INSERT_STRM_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_INSERT_STATE_OFFSET, \
                                    NSIP_HBI_B2H_CSR_INSERT_STATE_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_INSERT_STATE_RD_MASK, NSIP_HBI_B2H_CSR_INSERT_STATE_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_INSERT_STATE_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_INSERT_CTRL_OFFSET, \
                                    NSIP_HBI_B2H_CSR_INSERT_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_INSERT_CTRL_RD_MASK, NSIP_HBI_B2H_CSR_INSERT_CTRL_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_INSERT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR0_B2H_CSR_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_B2H_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR0_B2H_CSR_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR0_B2H_NULL_SAMPLE_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR0_B2H_NULL_SAMPLE_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR0_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_STRM_EN_DEFAULT, write_data, expected_data, \
                                     0x7, 0x7, \
                                    "NSIP_HBI_INSERT_QUE_CSR0_CMD_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR0_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR0_CMD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR1_B2H_CSR_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_B2H_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR1_B2H_CSR_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR1_B2H_NULL_SAMPLE_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_B2H_NULL_SAMPLE_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR1_B2H_NULL_SAMPLE_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR1_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_STRM_EN_DEFAULT, write_data, expected_data, \
                                    0x7, 0x7, \
                                    "NSIP_HBI_INSERT_QUE_CSR1_CMD_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INSERT_QUE_CSR1_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_RD_MASK, NSIP_HBI_INSERT_QUE_CSR_CMD_CTRL_WR_MASK, \
                                    "NSIP_HBI_INSERT_QUE_CSR1_CMD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_STAT_OFFSET, \
                                    NSIP_HBI_INTR_INT_STAT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INTR_INT_STAT_RD_MASK, NSIP_HBI_INTR_INT_STAT_WR_MASK, \
                                    "NSIP_HBI_INTR_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, \
                                    NSIP_HBI_INTR_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INTR_INT_HIGH_EN_RD_MASK, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
                                    "NSIP_HBI_INTR_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_LOW_EN_OFFSET, \
                                    NSIP_HBI_INTR_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INTR_INT_LOW_EN_RD_MASK, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
                                    "NSIP_HBI_INTR_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_CLR_OFFSET, \
                                    NSIP_HBI_INTR_INT_CLR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INTR_INT_CLR_RD_MASK, NSIP_HBI_INTR_INT_CLR_WR_MASK, \
                                    "NSIP_HBI_INTR_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_INTR_INT_FORCE_OFFSET, \
                                    NSIP_HBI_INTR_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_INTR_INT_FORCE_RD_MASK, NSIP_HBI_INTR_INT_FORCE_WR_MASK, \
                                    "NSIP_HBI_INTR_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON00_OFFSET, \
                                    NSIP_HBI_SMON_SMON00_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON00_RD_MASK, NSIP_HBI_SMON_SMON00_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON00_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON01_OFFSET, \
                                    NSIP_HBI_SMON_SMON01_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON01_RD_MASK, NSIP_HBI_SMON_SMON01_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON01_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON02_OFFSET, \
                                    NSIP_HBI_SMON_SMON02_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON02_RD_MASK, NSIP_HBI_SMON_SMON02_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON02_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON03_OFFSET, \
                                    NSIP_HBI_SMON_SMON03_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON03_RD_MASK, NSIP_HBI_SMON_SMON03_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON03_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON04_OFFSET, \
                                    NSIP_HBI_SMON_SMON04_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON04_RD_MASK, NSIP_HBI_SMON_SMON04_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON04_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON05_OFFSET, \
                                    NSIP_HBI_SMON_SMON05_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON05_RD_MASK, NSIP_HBI_SMON_SMON05_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON05_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SMON_SMON07_OFFSET, \
                                    NSIP_HBI_SMON_SMON07_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SMON_SMON07_RD_MASK, NSIP_HBI_SMON_SMON07_WR_MASK, \
                                    "NSIP_HBI_SMON_SMON07_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_RD_MASK, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_ADDR_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_TBL1_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_RD_MASK, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_ADDR_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_TBL2_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_RD_MASK, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_ADDR_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_TBL3_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_TBL_RD_MASK, NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK, \
                                    "NSIP_HBI_B2H_CSR_ADDR_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_RD, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
                                    "NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_MASK_TBL1_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_RD, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
                                    "NSIP_HBI_B2H_CSR_ADDR_MASK_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_MASK_TBL2_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_RD, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
                                    "NSIP_HBI_B2H_CSR_ADDR_MASK_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_B2H_CSR_ADDR_MASK_TBL3_OFFSET, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_RD, NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR, \
                                    "NSIP_HBI_B2H_CSR_ADDR_MASK_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET, \
                                    NSIP_HBI_H2B_FF_FIFO_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_FF_FIFO_CTRL_RD_MASK, NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK, \
                                    "NSIP_HBI_H2B_FF_FIFO_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_FF_FIFO_STAT_OFFSET, \
                                    NSIP_HBI_H2B_FF_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_FF_FIFO_STAT_RD_MASK, NSIP_HBI_H2B_FF_FIFO_STAT_WR_MASK, \
                                    "NSIP_HBI_H2B_FF_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, \
                                    NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_CREDIT_READY_CS_RD_MASK, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
                                    "NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_FLIT_CNT_OFFSET, \
                                    NSIP_HBI_H2B_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_FLIT_CNT_RD_MASK, NSIP_HBI_H2B_FLIT_CNT_WR_MASK, \
                                    "NSIP_HBI_H2B_FLIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MISC_CSR_OFFSET, \
                                    NSIP_HBI_H2B_MISC_CSR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MISC_CSR_RD_MASK, NSIP_HBI_H2B_MISC_CSR_WR_MASK, \
                                    "NSIP_HBI_H2B_MISC_CSR_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_MD_CMD_STRM_EN_DEFAULT, write_data, expected_data, \
                                    0xf, 0xf, \
                                    "NSIP_HBI_MD_CMD_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_MSG_OFFSET, \
                                    NSIP_HBI_MD_CMD_MSG_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_MD_CMD_MSG_RD_MASK, NSIP_HBI_MD_CMD_MSG_WR_MASK, \
                                    "NSIP_HBI_MD_CMD_MSG_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_MD_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_MD_CMD_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_MD_CMD_CTRL_RD_MASK, NSIP_HBI_MD_CMD_CTRL_WR_MASK, \
                                    "NSIP_HBI_MD_CMD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SCNT_PRL_SEQ_CNT_OFFSET, \
                                    NSIP_HBI_SCNT_PRL_SEQ_CNT_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_SCNT_PRL_SEQ_CNT_RD_MASK, NSIP_HBI_SCNT_PRL_SEQ_CNT_WR_MASK, \
                                    "NSIP_HBI_SCNT_PRL_SEQ_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_SCNT_PRL_STRM_EN_OFFSET, \
                                    NSIP_HBI_SCNT_PRL_STRM_EN_DEFAULT, write_data, expected_data, \
                                    0xf, 0xf, \
                                    "NSIP_HBI_SCNT_PRL_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_DROP_CMD0_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_DROP_CMD_STRM_EN_DEFAULT, write_data, expected_data, \
                                    0xf, 0xf, \
                                    "NSIP_HBI_DROP_CMD0_CMD_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_DROP_CMD0_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_DROP_CMD_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_DROP_CMD_CTRL_RD_MASK, NSIP_HBI_DROP_CMD_CTRL_WR_MASK, \
                                    "NSIP_HBI_DROP_CMD0_CMD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_DROP_CMD1_CMD_STRM_EN_OFFSET, \
                                    NSIP_HBI_DROP_CMD_STRM_EN_DEFAULT, write_data, expected_data, \
                                    0xf, 0xf, \
                                    "NSIP_HBI_DROP_CMD1_CMD_STRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_DROP_CMD1_CMD_CTRL_OFFSET, \
                                    NSIP_HBI_DROP_CMD_CTRL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_DROP_CMD_CTRL_RD_MASK, NSIP_HBI_DROP_CMD_CTRL_WR_MASK, \
                                    "NSIP_HBI_DROP_CMD1_CMD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_DROP_STATE_OFFSET, \
                                    NSIP_HBI_H2B_DROP_STATE_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_DROP_STATE_RD_MASK, NSIP_HBI_H2B_DROP_STATE_WR_MASK, \
                                    "NSIP_HBI_H2B_DROP_STATE_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_BUF_SZ_HW_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_BUF_SZ_HW_TBL3_OFFSET");


            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ADDR_LKUP_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_ROUTE_LKUP_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ADDR_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL3_OFFSET, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, \
                                    "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL3_OFFSET");

           write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR0_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, NSIP_HBI_H2B_SCNT_TK_PTR_WR_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR0_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR1_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, NSIP_HBI_H2B_SCNT_TK_PTR_WR_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR1_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR2_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, NSIP_HBI_H2B_SCNT_TK_PTR_WR_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR2_OFFSET");

            write_read_expect_18a(base_address[i]+NSIP_HBI_H2B_SCNT_TK_PTR3_OFFSET, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_DEFAULT, write_data, expected_data, \
                                    NSIP_HBI_H2B_SCNT_TK_PTR_RD_MASK, NSIP_HBI_H2B_SCNT_TK_PTR_WR_MASK, \
                                    "NSIP_HBI_H2B_SCNT_TK_PTR3_OFFSET");


        }

    }

}
