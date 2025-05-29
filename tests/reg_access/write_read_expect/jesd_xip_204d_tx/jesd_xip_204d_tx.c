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
    DLNK_JESD0_XIP_204D_TX_BASE, DLNK_JESD1_XIP_204D_TX_BASE, DLNK_JESD2_XIP_204D_TX_BASE, DLNK_JESD3_XIP_204D_TX_BASE
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

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_OFFSET, \
                                    JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_RD_MASK, JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_WR_MASK, \
                                    "JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SUBCLASS_OFFSET, \
                                    JESD_XIP_204D_TX_SUBCLASS_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SUBCLASS_RD_MASK, JESD_XIP_204D_TX_SUBCLASS_WR_MASK, \
                                    "JESD_XIP_204D_TX_SUBCLASS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_CF_OFFSET, \
                                    JESD_XIP_204D_TX_CF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_CF_RD_MASK, JESD_XIP_204D_TX_CF_WR_MASK, \
                                    "JESD_XIP_204D_TX_CF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_CS_OFFSET, \
                                    JESD_XIP_204D_TX_CS_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_CS_RD_MASK, JESD_XIP_204D_TX_CS_WR_MASK, \
                                    "JESD_XIP_204D_TX_CS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_F_OFFSET, \
                                    JESD_XIP_204D_TX_F_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_F_RD_MASK, JESD_XIP_204D_TX_F_WR_MASK, \
                                    "JESD_XIP_204D_TX_F_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_L_OFFSET, \
                                    JESD_XIP_204D_TX_L_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_L_RD_MASK, JESD_XIP_204D_TX_L_WR_MASK, \
                                    "JESD_XIP_204D_TX_L_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_N_OFFSET, \
                                    JESD_XIP_204D_TX_N_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_N_RD_MASK, JESD_XIP_204D_TX_N_WR_MASK, \
                                    "JESD_XIP_204D_TX_N_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_M_OFFSET, \
                                    JESD_XIP_204D_TX_M_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_M_RD_MASK, JESD_XIP_204D_TX_M_WR_MASK, \
                                    "JESD_XIP_204D_TX_M_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_NTOTAL_OFFSET, \
                                    JESD_XIP_204D_TX_NTOTAL_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_NTOTAL_RD_MASK, JESD_XIP_204D_TX_NTOTAL_WR_MASK, \
                                    "JESD_XIP_204D_TX_NTOTAL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_S_OFFSET, \
                                    JESD_XIP_204D_TX_S_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_S_RD_MASK, JESD_XIP_204D_TX_S_WR_MASK, \
                                    "JESD_XIP_204D_TX_S_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_HD_OFFSET, \
                                    JESD_XIP_204D_TX_HD_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_HD_RD_MASK, JESD_XIP_204D_TX_HD_WR_MASK, \
                                    "JESD_XIP_204D_TX_HD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SCR_OFFSET, \
                                    JESD_XIP_204D_TX_SCR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SCR_RD_MASK, JESD_XIP_204D_TX_SCR_WR_MASK, \
                                    "JESD_XIP_204D_TX_SCR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_ENMODULE_OFFSET, \
                                    JESD_XIP_204D_TX_ENMODULE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_ENMODULE_RD_MASK, JESD_XIP_204D_TX_ENMODULE_WR_MASK, \
                                    "JESD_XIP_204D_TX_ENMODULE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_CORE_INTR_MASK_OFFSET, \
                                    JESD_XIP_204D_TX_CORE_INTR_MASK_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_CORE_INTR_MASK_RD_MASK, JESD_XIP_204D_TX_CORE_INTR_MASK_WR_MASK, \
                                    "JESD_XIP_204D_TX_CORE_INTR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_CORE_INTR_STAT_OFFSET, \
                                    JESD_XIP_204D_TX_CORE_INTR_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_CORE_INTR_STAT_RD_MASK, JESD_XIP_204D_TX_CORE_INTR_STAT_WR_MASK, \
                                    "JESD_XIP_204D_TX_CORE_INTR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_CLK_RATIO_OFFSET, \
                                    JESD_XIP_204D_TX_CLK_RATIO_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_CLK_RATIO_RD_MASK, JESD_XIP_204D_TX_CLK_RATIO_WR_MASK, \
                                    "JESD_XIP_204D_TX_CLK_RATIO_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_TL_LATENCY_OFFSET, \
                                    JESD_XIP_204D_TX_TL_LATENCY_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_TL_LATENCY_RD_MASK, JESD_XIP_204D_TX_TL_LATENCY_WR_MASK, \
                                    "JESD_XIP_204D_TX_TL_LATENCY_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_FEC_OFFSET, \
                                    JESD_XIP_204D_TX_FEC_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_FEC_RD_MASK, JESD_XIP_204D_TX_FEC_WR_MASK, \
                                    "JESD_XIP_204D_TX_FEC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_A_OFFSET, \
                                    JESD_XIP_204D_TX_A_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_A_RD_MASK, JESD_XIP_204D_TX_A_WR_MASK, \
                                    "JESD_XIP_204D_TX_A_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_BIT_ORDER_OFFSET, \
                                    JESD_XIP_204D_TX_BIT_ORDER_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_BIT_ORDER_RD_MASK, JESD_XIP_204D_TX_BIT_ORDER_WR_MASK, \
                                    "JESD_XIP_204D_TX_BIT_ORDER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_TL_TEST_MODE_OFFSET, \
                                    JESD_XIP_204D_TX_TL_TEST_MODE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_TL_TEST_MODE_RD_MASK, JESD_XIP_204D_TX_TL_TEST_MODE_WR_MASK, \
                                    "JESD_XIP_204D_TX_TL_TEST_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_BUFF_DELAY_OFFSET, \
                                    JESD_XIP_204D_TX_BUFF_DELAY_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_BUFF_DELAY_RD_MASK, JESD_XIP_204D_TX_BUFF_DELAY_WR_MASK, \
                                    "JESD_XIP_204D_TX_BUFF_DELAY_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SYSREF_CFG_OFFSET, \
                                    JESD_XIP_204D_TX_SYSREF_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SYSREF_CFG_RD_MASK, JESD_XIP_204D_TX_SYSREF_CFG_WR_MASK, \
                                    "JESD_XIP_204D_TX_SYSREF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SONIF_OFFSET, \
                                    JESD_XIP_204D_TX_SONIF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SONIF_RD_MASK, JESD_XIP_204D_TX_SONIF_WR_MASK, \
                                    "JESD_XIP_204D_TX_SONIF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SYSREF_CNTER_STAT_OFFSET, \
                                    JESD_XIP_204D_TX_SYSREF_CNTER_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SYSREF_CNTER_STAT_RD_MASK, JESD_XIP_204D_TX_SYSREF_CNTER_STAT_WR_MASK, \
                                    "JESD_XIP_204D_TX_SYSREF_CNTER_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_SAMPLE_REQ_OFFSET, \
                                    JESD_XIP_204D_TX_SAMPLE_REQ_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_SAMPLE_REQ_RD_MASK, JESD_XIP_204D_TX_SAMPLE_REQ_WR_MASK, \
                                    "JESD_XIP_204D_TX_SAMPLE_REQ_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_GEN_SYSREF_OFFSET, \
                                    JESD_XIP_204D_TX_GEN_SYSREF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_GEN_SYSREF_RD_MASK, JESD_XIP_204D_TX_GEN_SYSREF_WR_MASK, \
                                    "JESD_XIP_204D_TX_GEN_SYSREF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_GEARBOX_EMPTY_STAT_OFFSET, \
                                    JESD_XIP_204D_TX_GEARBOX_EMPTY_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_GEARBOX_EMPTY_STAT_RD_MASK, JESD_XIP_204D_TX_GEARBOX_EMPTY_STAT_WR_MASK, \
                                    "JESD_XIP_204D_TX_GEARBOX_EMPTY_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_GEARBOX_FULL_STAT_OFFSET, \
                                    JESD_XIP_204D_TX_GEARBOX_FULL_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_GEARBOX_FULL_STAT_RD_MASK, JESD_XIP_204D_TX_GEARBOX_FULL_STAT_WR_MASK, \
                                    "JESD_XIP_204D_TX_GEARBOX_FULL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_TXRX_FIFO_WAIT_CNT_OFFSET, \
                                    JESD_XIP_204D_TX_TXRX_FIFO_WAIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_TXRX_FIFO_WAIT_CNT_RD_MASK, JESD_XIP_204D_TX_TXRX_FIFO_WAIT_CNT_WR_MASK, \
                                    "JESD_XIP_204D_TX_TXRX_FIFO_WAIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_ERR_INJECT_CTRL_OFFSET, \
                                    JESD_XIP_204D_TX_ERR_INJECT_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_ERR_INJECT_CTRL_RD_MASK, JESD_XIP_204D_TX_ERR_INJECT_CTRL_WR_MASK, \
                                    "JESD_XIP_204D_TX_ERR_INJECT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_ERR_INJECT_PERIOD_OFFSET, \
                                    JESD_XIP_204D_TX_ERR_INJECT_PERIOD_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_ERR_INJECT_PERIOD_RD_MASK, JESD_XIP_204D_TX_ERR_INJECT_PERIOD_WR_MASK, \
                                    "JESD_XIP_204D_TX_ERR_INJECT_PERIOD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_TEST_PATTERN_LSB_OFFSET, \
                                    JESD_XIP_204D_TX_TEST_PATTERN_LSB_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_TEST_PATTERN_LSB_RD_MASK, JESD_XIP_204D_TX_TEST_PATTERN_LSB_WR_MASK, \
                                    "JESD_XIP_204D_TX_TEST_PATTERN_LSB_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_TEST_PATTERN_MSB_OFFSET, \
                                    JESD_XIP_204D_TX_TEST_PATTERN_MSB_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_TEST_PATTERN_MSB_RD_MASK, JESD_XIP_204D_TX_TEST_PATTERN_MSB_WR_MASK, \
                                    "JESD_XIP_204D_TX_TEST_PATTERN_MSB_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204D_TX_PRBS_CFG_OFFSET, \
                                    JESD_XIP_204D_TX_PRBS_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204D_TX_PRBS_CFG_RD_MASK, JESD_XIP_204D_TX_PRBS_CFG_WR_MASK, \
                                    "JESD_XIP_204D_TX_PRBS_CFG_OFFSET");

      

    }

   }
}

