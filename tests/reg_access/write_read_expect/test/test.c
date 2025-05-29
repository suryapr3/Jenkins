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
    MEM_CAP0_TEST_BASE, MEM_CAP1_TEST_BASE
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
            write_read_expect_18a(base_address[i]+TEST_MEM_SCRATCH_OFFSET, \
                                    TEST_MEM_SCRATCH_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_SCRATCH_RD_MASK, TEST_MEM_SCRATCH_WR_MASK, \
                                    "TEST_MEM_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_ACTIVE_OFFSET, \
                                    TEST_MEM_MSI_ACTIVE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_ACTIVE_RD_MASK, TEST_MEM_MSI_ACTIVE_WR_MASK, \
                                    "TEST_MEM_MSI_ACTIVE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RD_EN_OFFSET, \
                                    TEST_MEM_RD_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RD_EN_RD_MASK, TEST_MEM_RD_EN_WR_MASK, \
                                    "TEST_MEM_RD_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_WR_EN_OFFSET, \
                                    TEST_MEM_WR_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_WR_EN_RD_MASK, TEST_MEM_WR_EN_WR_MASK, \
                                    "TEST_MEM_WR_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RXBAR_SEL0_OFFSET, \
                                    TEST_MEM_RXBAR_SEL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RXBAR_SEL_RD_MASK, TEST_MEM_RXBAR_SEL_WR_MASK, \
                                    "TEST_MEM_RXBAR_SEL0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RXBAR_SEL1_OFFSET, \
                                    TEST_MEM_RXBAR_SEL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RXBAR_SEL_RD_MASK, TEST_MEM_RXBAR_SEL_WR_MASK, \
                                    "TEST_MEM_RXBAR_SEL1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RXBAR_SEL2_OFFSET, \
                                    TEST_MEM_RXBAR_SEL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RXBAR_SEL_RD_MASK, TEST_MEM_RXBAR_SEL_WR_MASK, \
                                    "TEST_MEM_RXBAR_SEL2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RXBAR_SEL3_OFFSET, \
                                    TEST_MEM_RXBAR_SEL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RXBAR_SEL_RD_MASK, TEST_MEM_RXBAR_SEL_WR_MASK, \
                                    "TEST_MEM_RXBAR_SEL3_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_RXBAR_SEL4_OFFSET, \
                                    TEST_MEM_RXBAR_SEL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_RXBAR_SEL_RD_MASK, TEST_MEM_RXBAR_SEL_WR_MASK, \
                                    "TEST_MEM_RXBAR_SEL4_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_WM0_OFFSET, \
                                    TEST_MEM_MSO_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_WM_RD_MASK, TEST_MEM_MSO_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_WM0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_WM1_OFFSET, \
                                    TEST_MEM_MSO_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_WM_RD_MASK, TEST_MEM_MSO_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_WM1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_WM2_OFFSET, \
                                    TEST_MEM_MSO_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_WM_RD_MASK, TEST_MEM_MSO_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_WM2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_ADC_MODE_OFFSET, \
                                    TEST_MEM_BIST_ADC_MODE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_ADC_MODE_RD_MASK, TEST_MEM_BIST_ADC_MODE_WR_MASK, \
                                    "TEST_MEM_BIST_ADC_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_ADC_CTRL_OFFSET, \
                                    TEST_MEM_BIST_ADC_CTRL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_ADC_CTRL_RD_MASK, TEST_MEM_BIST_ADC_CTRL_WR_MASK, \
                                    "TEST_MEM_BIST_ADC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_STAT_OFFSET, \
                                    TEST_MEM_BIST_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_STAT_RD_MASK, TEST_MEM_BIST_STAT_WR_MASK, \
                                    "TEST_MEM_BIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_WAIT_TIME_OFFSET, \
                                    TEST_MEM_BIST_WAIT_TIME_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_WAIT_TIME_RD_MASK, TEST_MEM_BIST_WAIT_TIME_WR_MASK, \
                                    "TEST_MEM_BIST_WAIT_TIME_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_TEST_TIME_OFFSET, \
                                    TEST_MEM_BIST_TEST_TIME_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_TEST_TIME_RD_MASK, TEST_MEM_BIST_TEST_TIME_WR_MASK, \
                                    "TEST_MEM_BIST_TEST_TIME_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_PLL_BYP_PHASE_OFFSET, \
                                    TEST_MEM_BIST_PLL_BYP_PHASE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_PLL_BYP_PHASE_RD_MASK, TEST_MEM_BIST_PLL_BYP_PHASE_WR_MASK, \
                                    "TEST_MEM_BIST_PLL_BYP_PHASE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_PLL_BYP_MULT_OFFSET, \
                                    TEST_MEM_BIST_PLL_BYP_MULT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_PLL_BYP_MULT_RD_MASK, TEST_MEM_BIST_PLL_BYP_MULT_WR_MASK, \
                                    "TEST_MEM_BIST_PLL_BYP_MULT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_BIST_AMPLITUDE_MULTIPLIER_OFFSET, \
                                    TEST_MEM_BIST_AMPLITUDE_MULTIPLIER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_BIST_AMPLITUDE_MULTIPLIER_RD_MASK, TEST_MEM_BIST_AMPLITUDE_MULTIPLIER_WR_MASK, \
                                    "TEST_MEM_BIST_AMPLITUDE_MULTIPLIER_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TPACK_FIFO_WM_OFFSET, \
                                    TEST_MEM_TPACK_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TPACK_FIFO_WM_RD_MASK, TEST_MEM_TPACK_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_TPACK_FIFO_WM_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TDPACK_CFG_OFFSET, \
                                    TEST_MEM_TDPACK_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TDPACK_CFG_RD_MASK, TEST_MEM_TDPACK_CFG_WR_MASK, \
                                    "TEST_MEM_TDPACK_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_STAT0_OFFSET, \
                                    TEST_MEM_MSO_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_STAT_RD_MASK, TEST_MEM_MSO_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_STAT1_OFFSET, \
                                    TEST_MEM_MSO_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_STAT_RD_MASK, TEST_MEM_MSO_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSO_FIFO_STAT2_OFFSET, \
                                    TEST_MEM_MSO_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSO_FIFO_STAT_RD_MASK, TEST_MEM_MSO_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSO_FIFO_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_DBGM_FIFO_STAT_OFFSET, \
                                    TEST_MEM_PLL_DBGM_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_DBGM_FIFO_STAT_RD_MASK, TEST_MEM_PLL_DBGM_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_PLL_DBGM_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TPACK_FIFO_STAT_OFFSET, \
                                    TEST_MEM_TPACK_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TPACK_FIFO_STAT_RD_MASK, TEST_MEM_TPACK_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_TPACK_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_FIFO_FLUSH_OFFSET, \
                                    TEST_MEM_FIFO_FLUSH_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_FIFO_FLUSH_RD_MASK, TEST_MEM_FIFO_FLUSH_WR_MASK, \
                                    "TEST_MEM_FIFO_FLUSH_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TEST_ERR_OFFSET, \
                                    TEST_MEM_TEST_ERR_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TEST_ERR_RD_MASK, TEST_MEM_TEST_ERR_WR_MASK, \
                                    "TEST_MEM_TEST_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PACKER_CFG_OFFSET, \
                                    TEST_MEM_PACKER_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PACKER_CFG_RD_MASK, TEST_MEM_PACKER_CFG_WR_MASK, \
                                    "TEST_MEM_PACKER_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_INT_STAT_OFFSET, \
                                    TEST_MEM_INT_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_INT_STAT_RD_MASK, TEST_MEM_INT_STAT_WR_MASK, \
                                    "TEST_MEM_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_INT_HIGH_EN_OFFSET, \
                                    TEST_MEM_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_INT_HIGH_EN_RD_MASK, TEST_MEM_INT_HIGH_EN_WR_MASK, \
                                    "TEST_MEM_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_INT_LOW_EN_OFFSET, \
                                    TEST_MEM_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_INT_LOW_EN_RD_MASK, TEST_MEM_INT_LOW_EN_WR_MASK, \
                                    "TEST_MEM_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_INT_CLR_OFFSET, \
                                    TEST_MEM_INT_CLR_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_INT_CLR_RD_MASK, TEST_MEM_INT_CLR_WR_MASK, \
                                    "TEST_MEM_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_INT_FORCE_OFFSET, \
                                    TEST_MEM_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_INT_FORCE_RD_MASK, TEST_MEM_INT_FORCE_WR_MASK, \
                                    "TEST_MEM_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_EN0_OFFSET, \
                                    TEST_MEM_TTSG_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_EN_RD_MASK, TEST_MEM_TTSG_EN_WR_MASK, \
                                    "TEST_MEM_TTSG_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_EN1_OFFSET, \
                                    TEST_MEM_TTSG_EN_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_EN_RD_MASK, TEST_MEM_TTSG_EN_WR_MASK, \
                                    "TEST_MEM_TTSG_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_MODE_OFFSET, \
                                    TEST_MEM_TTSG_MODE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_MODE_RD_MASK, TEST_MEM_TTSG_MODE_WR_MASK, \
                                    "TEST_MEM_TTSG_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_CDAC_CFG_OFFSET, \
                                    TEST_MEM_CDAC_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_CDAC_CFG_RD_MASK, TEST_MEM_CDAC_CFG_WR_MASK, \
                                    "TEST_MEM_CDAC_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER2_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER3_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER3_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER4_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER4_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER5_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER5_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER6_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER6_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER7_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER7_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER8_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER8_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER9_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER9_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER10_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER10_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER11_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER11_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER12_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER12_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER13_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER13_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER14_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER14_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER15_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER15_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER16_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER16_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER17_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER17_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER18_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER18_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER19_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER19_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER20_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER20_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER21_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER21_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER22_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER22_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER23_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER23_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER24_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER24_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER25_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER25_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER26_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER26_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER27_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER27_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER28_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER28_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER29_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER29_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER30_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER30_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_UPPER31_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_UPPER31_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER2_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER3_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER3_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER4_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER4_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER5_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER5_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER6_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER6_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER7_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER7_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER8_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER8_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER9_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER9_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER10_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER10_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER11_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER11_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER12_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER12_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER13_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER13_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER14_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER14_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER15_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER15_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER16_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER16_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER17_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER17_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER18_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER18_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER19_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER19_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER20_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER20_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER21_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER21_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER22_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER22_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER23_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER23_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER24_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER24_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER25_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER25_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER26_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER26_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER27_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER27_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER28_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER28_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER29_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER29_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER30_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER30_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INIT_LOWER31_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INIT_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INIT_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INIT_LOWER31_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR_UPPER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR_UPPER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR_UPPER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR_UPPER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR_LOWER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR_LOWER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR_LOWER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR_LOWER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR1_UPPER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR1_UPPER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR1_UPPER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_UPPER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_UPPER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR1_UPPER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR1_LOWER0_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR1_LOWER0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TTSG_CORDIC_INCR1_LOWER1_OFFSET, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TTSG_CORDIC_INCR_LOWER_RD_MASK, TEST_MEM_TTSG_CORDIC_INCR_LOWER_WR_MASK, \
                                    "TEST_MEM_TTSG_CORDIC_INCR1_LOWER1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_WM0_OFFSET, \
                                    TEST_MEM_MSI_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_WM_RD_MASK, TEST_MEM_MSI_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_WM0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_WM1_OFFSET, \
                                    TEST_MEM_MSI_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_WM_RD_MASK, TEST_MEM_MSI_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_WM1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_WM2_OFFSET, \
                                    TEST_MEM_MSI_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_WM_RD_MASK, TEST_MEM_MSI_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_WM2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_WM3_OFFSET, \
                                    TEST_MEM_MSI_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_WM_RD_MASK, TEST_MEM_MSI_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_WM3_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_WM4_OFFSET, \
                                    TEST_MEM_MSI_FIFO_WM_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_WM_RD_MASK, TEST_MEM_MSI_FIFO_WM_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_WM4_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_STAT0_OFFSET, \
                                    TEST_MEM_MSI_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_STAT_RD_MASK, TEST_MEM_MSI_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_STAT1_OFFSET, \
                                    TEST_MEM_MSI_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_STAT_RD_MASK, TEST_MEM_MSI_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_STAT2_OFFSET, \
                                    TEST_MEM_MSI_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_STAT_RD_MASK, TEST_MEM_MSI_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_STAT3_OFFSET, \
                                    TEST_MEM_MSI_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_STAT_RD_MASK, TEST_MEM_MSI_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_MSI_FIFO_STAT4_OFFSET, \
                                    TEST_MEM_MSI_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_MSI_FIFO_STAT_RD_MASK, TEST_MEM_MSI_FIFO_STAT_WR_MASK, \
                                    "TEST_MEM_MSI_FIFO_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_ERR_PHASE_OFFSET, \
                                    TEST_MEM_ERR_PHASE_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_ERR_PHASE_RD_MASK, TEST_MEM_ERR_PHASE_WR_MASK, \
                                    "TEST_MEM_ERR_PHASE_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_ERR_AMPL_OFFSET, \
                                    TEST_MEM_ERR_AMPL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_ERR_AMPL_RD_MASK, TEST_MEM_ERR_AMPL_WR_MASK, \
                                    "TEST_MEM_ERR_AMPL_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_TEST_TX_CFG_OFFSET, \
                                    TEST_MEM_TEST_TX_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_TEST_TX_CFG_RD_MASK, TEST_MEM_TEST_TX_CFG_WR_MASK, \
                                    "TEST_MEM_TEST_TX_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_DUAL_FCW_CFG0_OFFSET, \
                                    TEST_MEM_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_DUAL_FCW_CFG_RD_MASK, TEST_MEM_DUAL_FCW_CFG_WR_MASK, \
                                    "TEST_MEM_DUAL_FCW_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_DUAL_FCW_CFG1_OFFSET, \
                                    TEST_MEM_DUAL_FCW_CFG_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_DUAL_FCW_CFG_RD_MASK, TEST_MEM_DUAL_FCW_CFG_WR_MASK, \
                                    "TEST_MEM_DUAL_FCW_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_APB_BRDG_STAT_OFFSET, \
                                    TEST_MEM_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_APB_BRDG_STAT_RD_MASK, TEST_MEM_APB_BRDG_STAT_WR_MASK, \
                                    "TEST_MEM_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_FUNCTION_OFFSET, \
                                    TEST_MEM_PLL_FUNCTION_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_FUNCTION_RD_MASK, TEST_MEM_PLL_FUNCTION_WR_MASK, \
                                    "TEST_MEM_PLL_FUNCTION_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_STAT_OFFSET, \
                                    TEST_MEM_PLL_STAT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_STAT_RD_MASK, TEST_MEM_PLL_STAT_WR_MASK, \
                                    "TEST_MEM_PLL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_CNTER_OFFSET, \
                                    TEST_MEM_PLL_CNTER_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_CNTER_RD_MASK, TEST_MEM_PLL_CNTER_WR_MASK, \
                                    "TEST_MEM_PLL_CNTER_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_WAIT_CNT_OFFSET, \
                                    TEST_MEM_PLL_WAIT_CNT_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_WAIT_CNT_RD_MASK, TEST_MEM_PLL_WAIT_CNT_WR_MASK, \
                                    "TEST_MEM_PLL_WAIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_CNT_HIGH_OFFSET, \
                                    TEST_MEM_PLL_CNT_HIGH_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_CNT_HIGH_RD_MASK, TEST_MEM_PLL_CNT_HIGH_WR_MASK, \
                                    "TEST_MEM_PLL_CNT_HIGH_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_PLL_CNT_LOW_OFFSET, \
                                    TEST_MEM_PLL_CNT_LOW_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_PLL_CNT_LOW_RD_MASK, TEST_MEM_PLL_CNT_LOW_WR_MASK, \
                                    "TEST_MEM_PLL_CNT_LOW_OFFSET");

            write_read_expect_18a(base_address[i]+TEST_MEM_APB_BRDG_STAT_PLL_OFFSET, \
                                    TEST_MEM_APB_BRDG_STAT_PLL_DEFAULT, write_data, expected_data, \
                                    TEST_MEM_APB_BRDG_STAT_PLL_RD_MASK, TEST_MEM_APB_BRDG_STAT_PLL_WR_MASK, \
                                    "TEST_MEM_APB_BRDG_STAT_PLL_OFFSET");

        }

    }

}
