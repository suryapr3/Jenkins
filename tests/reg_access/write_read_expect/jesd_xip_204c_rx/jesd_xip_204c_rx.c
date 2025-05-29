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
    DLNK_JESD0_XIP_204C_RX_BASE, DLNK_JESD1_XIP_204C_RX_BASE, DLNK_JESD2_XIP_204C_RX_BASE, DLNK_JESD3_XIP_204C_RX_BASE
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
            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_OFFSET, \
                                    JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_RD_MASK, JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_WR_MASK, \
                                    "JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SUBCLASS_OFFSET, \
                                    JESD_XIP_204C_RX_SUBCLASS_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SUBCLASS_RD_MASK, JESD_XIP_204C_RX_SUBCLASS_WR_MASK, \
                                    "JESD_XIP_204C_RX_SUBCLASS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CF_OFFSET, \
                                    JESD_XIP_204C_RX_CF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CF_RD_MASK, JESD_XIP_204C_RX_CF_WR_MASK, \
                                    "JESD_XIP_204C_RX_CF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CS_OFFSET, \
                                    JESD_XIP_204C_RX_CS_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CS_RD_MASK, JESD_XIP_204C_RX_CS_WR_MASK, \
                                    "JESD_XIP_204C_RX_CS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_F_OFFSET, \
                                    JESD_XIP_204C_RX_F_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_F_RD_MASK, JESD_XIP_204C_RX_F_WR_MASK, \
                                    "JESD_XIP_204C_RX_F_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_L_OFFSET, \
                                    JESD_XIP_204C_RX_L_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_L_RD_MASK, JESD_XIP_204C_RX_L_WR_MASK, \
                                    "JESD_XIP_204C_RX_L_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_N_OFFSET, \
                                    JESD_XIP_204C_RX_N_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_N_RD_MASK, JESD_XIP_204C_RX_N_WR_MASK, \
                                    "JESD_XIP_204C_RX_N_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_M_OFFSET, \
                                    JESD_XIP_204C_RX_M_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_M_RD_MASK, JESD_XIP_204C_RX_M_WR_MASK, \
                                    "JESD_XIP_204C_RX_M_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_NTOTAL_OFFSET, \
                                    JESD_XIP_204C_RX_NTOTAL_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_NTOTAL_RD_MASK, JESD_XIP_204C_RX_NTOTAL_WR_MASK, \
                                    "JESD_XIP_204C_RX_NTOTAL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_S_OFFSET, \
                                    JESD_XIP_204C_RX_S_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_S_RD_MASK, JESD_XIP_204C_RX_S_WR_MASK, \
                                    "JESD_XIP_204C_RX_S_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_HD_OFFSET, \
                                    JESD_XIP_204C_RX_HD_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_HD_RD_MASK, JESD_XIP_204C_RX_HD_WR_MASK, \
                                    "JESD_XIP_204C_RX_HD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SCR_OFFSET, \
                                    JESD_XIP_204C_RX_SCR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SCR_RD_MASK, JESD_XIP_204C_RX_SCR_WR_MASK, \
                                    "JESD_XIP_204C_RX_SCR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ENMODULE_OFFSET, \
                                    JESD_XIP_204C_RX_ENMODULE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ENMODULE_RD_MASK, JESD_XIP_204C_RX_ENMODULE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ENMODULE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CORE_INTR_MASK_OFFSET, \
                                    JESD_XIP_204C_RX_CORE_INTR_MASK_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CORE_INTR_MASK_RD_MASK, JESD_XIP_204C_RX_CORE_INTR_MASK_WR_MASK, \
                                    "JESD_XIP_204C_RX_CORE_INTR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CORE_INTR_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_CORE_INTR_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CORE_INTR_STAT_RD_MASK, JESD_XIP_204C_RX_CORE_INTR_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_CORE_INTR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CLK_RATIO_OFFSET, \
                                    JESD_XIP_204C_RX_CLK_RATIO_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CLK_RATIO_RD_MASK, JESD_XIP_204C_RX_CLK_RATIO_WR_MASK, \
                                    "JESD_XIP_204C_RX_CLK_RATIO_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_FEC_OFFSET, \
                                    JESD_XIP_204C_RX_FEC_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_FEC_RD_MASK, JESD_XIP_204C_RX_FEC_WR_MASK, \
                                    "JESD_XIP_204C_RX_FEC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CRC3_EN_OFFSET, \
                                    JESD_XIP_204C_RX_CRC3_EN_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CRC3_EN_RD_MASK, JESD_XIP_204C_RX_CRC3_EN_WR_MASK, \
                                    "JESD_XIP_204C_RX_CRC3_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CRC12_EN_OFFSET, \
                                    JESD_XIP_204C_RX_CRC12_EN_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CRC12_EN_RD_MASK, JESD_XIP_204C_RX_CRC12_EN_WR_MASK, \
                                    "JESD_XIP_204C_RX_CRC12_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_E_OFFSET, \
                                    JESD_XIP_204C_RX_E_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_E_RD_MASK, JESD_XIP_204C_RX_E_WR_MASK, \
                                    "JESD_XIP_204C_RX_E_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_BIT_ORDER_OFFSET, \
                                    JESD_XIP_204C_RX_BIT_ORDER_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_BIT_ORDER_RD_MASK, JESD_XIP_204C_RX_BIT_ORDER_WR_MASK, \
                                    "JESD_XIP_204C_RX_BIT_ORDER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_TL_TEST_MODE_OFFSET, \
                                    JESD_XIP_204C_RX_TL_TEST_MODE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_TL_TEST_MODE_RD_MASK, JESD_XIP_204C_RX_TL_TEST_MODE_WR_MASK, \
                                    "JESD_XIP_204C_RX_TL_TEST_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_LEMC_DELAY_OFFSET, \
                                    JESD_XIP_204C_RX_LEMC_DELAY_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_LEMC_DELAY_RD_MASK, JESD_XIP_204C_RX_LEMC_DELAY_WR_MASK, \
                                    "JESD_XIP_204C_RX_LEMC_DELAY_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SYSREF_CFG_OFFSET, \
                                    JESD_XIP_204C_RX_SYSREF_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SYSREF_CFG_RD_MASK, JESD_XIP_204C_RX_SYSREF_CFG_WR_MASK, \
                                    "JESD_XIP_204C_RX_SYSREF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SH_LOCK_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_SH_LOCK_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SH_LOCK_STAT_RD_MASK, JESD_XIP_204C_RX_SH_LOCK_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_SH_LOCK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_RD_MASK, JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_EMB_LOCK_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_EMB_LOCK_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_EMB_LOCK_STAT_RD_MASK, JESD_XIP_204C_RX_EMB_LOCK_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_EMB_LOCK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_RD_MASK, JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ERR_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ERR_RPT_LANE_RD_MASK, JESD_XIP_204C_RX_ERR_RPT_LANE_WR_MASK, \
                                    "JESD_XIP_204C_RX_ERR_RPT_LANE_REG23_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_THRESH_EMB_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_THRESH_EMB_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_THRESH_EMB_ERR_RD_MASK, JESD_XIP_204C_RX_THRESH_EMB_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_THRESH_EMB_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_THRESH_SH_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_THRESH_SH_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_THRESH_SH_ERR_RD_MASK, JESD_XIP_204C_RX_THRESH_SH_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_THRESH_SH_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SONIF_OFFSET, \
                                    JESD_XIP_204C_RX_SONIF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SONIF_RD_MASK, JESD_XIP_204C_RX_SONIF_WR_MASK, \
                                    "JESD_XIP_204C_RX_SONIF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_CMD_EN_OFFSET, \
                                    JESD_XIP_204C_RX_CMD_EN_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_CMD_EN_RD_MASK, JESD_XIP_204C_RX_CMD_EN_WR_MASK, \
                                    "JESD_XIP_204C_RX_CMD_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SYSREF_CNTER_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_SYSREF_CNTER_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SYSREF_CNTER_STAT_RD_MASK, JESD_XIP_204C_RX_SYSREF_CNTER_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_SYSREF_CNTER_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE0_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE0_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE0_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE0_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE1_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE1_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE1_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE1_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE2_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE2_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE2_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE2_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE3_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE3_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE3_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE3_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE4_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE4_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE4_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE4_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE5_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE5_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE5_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE5_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE6_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE6_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE6_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE6_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE7_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE7_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE7_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE7_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE8_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE8_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE8_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE8_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE9_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE9_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE9_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE9_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE10_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE10_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE10_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE10_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE11_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE11_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE11_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE11_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE12_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE12_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE12_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE12_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE13_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE13_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE13_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE13_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE14_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE14_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE14_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE14_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE15_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE15_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE15_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE15_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE16_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE16_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE16_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE16_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE17_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE17_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE17_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE17_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE18_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE18_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE18_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE18_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE19_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE19_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE19_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE19_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE20_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE20_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE20_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE20_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE21_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE21_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE21_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE21_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE22_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE22_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE22_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE22_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ICNTER_RPT_LANE23_OFFSET, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE23_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ICNTER_RPT_LANE23_RD_MASK, JESD_XIP_204C_RX_ICNTER_RPT_LANE23_WR_MASK, \
                                    "JESD_XIP_204C_RX_ICNTER_RPT_LANE23_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_OFFSET, \
                                    JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_RD_MASK, JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_WR_MASK, \
                                    "JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_RBD_LENGTH_OCTETS_OFFSET, \
                                    JESD_XIP_204C_RX_RBD_LENGTH_OCTETS_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_RBD_LENGTH_OCTETS_RD_MASK, JESD_XIP_204C_RX_RBD_LENGTH_OCTETS_WR_MASK, \
                                    "JESD_XIP_204C_RX_RBD_LENGTH_OCTETS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_GEN_SYSREF_OFFSET, \
                                    JESD_XIP_204C_RX_GEN_SYSREF_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_GEN_SYSREF_RD_MASK, JESD_XIP_204C_RX_GEN_SYSREF_WR_MASK, \
                                    "JESD_XIP_204C_RX_GEN_SYSREF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_RD_MASK, JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_GEARBOX_FULL_STAT_OFFSET, \
                                    JESD_XIP_204C_RX_GEARBOX_FULL_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_GEARBOX_FULL_STAT_RD_MASK, JESD_XIP_204C_RX_GEARBOX_FULL_STAT_WR_MASK, \
                                    "JESD_XIP_204C_RX_GEARBOX_FULL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_TXRX_FIFO_WAIT_CNT_OFFSET, \
                                    JESD_XIP_204C_RX_TXRX_FIFO_WAIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_TXRX_FIFO_WAIT_CNT_RD_MASK, JESD_XIP_204C_RX_TXRX_FIFO_WAIT_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_TXRX_FIFO_WAIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_SLOW_LN_DELAY_CNTER_OFFSET, \
                                    JESD_XIP_204C_RX_SLOW_LN_DELAY_CNTER_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_SLOW_LN_DELAY_CNTER_RD_MASK, JESD_XIP_204C_RX_SLOW_LN_DELAY_CNTER_WR_MASK, \
                                    "JESD_XIP_204C_RX_SLOW_LN_DELAY_CNTER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_CTRL_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_CTRL_RD_MASK, JESD_XIP_204C_RX_ALARM_CTRL_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TYPE_MASK_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TYPE_MASK_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TYPE_MASK_RD_MASK, JESD_XIP_204C_RX_ALARM_TYPE_MASK_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TYPE_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_LANE_MASK_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_LANE_MASK_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_LANE_MASK_RD_MASK, JESD_XIP_204C_RX_ALARM_LANE_MASK_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_LANE_MASK_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TSHOLD_INV_SYNC_HDR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_INV_SYNC_HDR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_INV_SYNC_HDR_RD_MASK, JESD_XIP_204C_RX_ALARM_TSHOLD_INV_SYNC_HDR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TSHOLD_INV_SYNC_HDR_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TSHOLD_CRC_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_CRC_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_CRC_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_TSHOLD_CRC_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TSHOLD_CRC_ERR_OFFSET");

//           write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TSHOLD_UNC_FEC_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_UNC_FEC_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_UNC_FEC_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_TSHOLD_UNC_FEC_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TSHOLD_UNC_FEC_ERR_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TSHOLD_UNEXP_PILOT_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_UNEXP_PILOT_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TSHOLD_UNEXP_PILOT_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_TSHOLD_UNEXP_PILOT_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TSHOLD_UNEXP_PILOT_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_WND_INV_SYNC_HDR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_WND_INV_SYNC_HDR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_WND_INV_SYNC_HDR_RD_MASK, JESD_XIP_204C_RX_ALARM_WND_INV_SYNC_HDR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_WND_INV_SYNC_HDR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_WND_CRC_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_WND_CRC_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_WND_CRC_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_WND_CRC_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_WND_CRC_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_WND_UNC_FEC_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_WND_UNC_FEC_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_WND_UNC_FEC_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_WND_UNC_FEC_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_WND_UNC_FEC_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_WND_UNEXP_PILOT_ERR_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_WND_UNEXP_PILOT_ERR_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_WND_UNEXP_PILOT_ERR_RD_MASK, JESD_XIP_204C_RX_ALARM_WND_UNEXP_PILOT_ERR_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_WND_UNEXP_PILOT_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_ALARM_TIMER_OFFSET, \
                                    JESD_XIP_204C_RX_ALARM_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_ALARM_TIMER_RD_MASK, JESD_XIP_204C_RX_ALARM_TIMER_WR_MASK, \
                                    "JESD_XIP_204C_RX_ALARM_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_TEST_PATTERN_LSB_OFFSET, \
                                    JESD_XIP_204C_RX_TEST_PATTERN_LSB_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_TEST_PATTERN_LSB_RD_MASK, JESD_XIP_204C_RX_TEST_PATTERN_LSB_WR_MASK, \
                                    "JESD_XIP_204C_RX_TEST_PATTERN_LSB_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_TEST_PATTERN_MSB_OFFSET, \
                                    JESD_XIP_204C_RX_TEST_PATTERN_MSB_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_TEST_PATTERN_MSB_RD_MASK, JESD_XIP_204C_RX_TEST_PATTERN_MSB_WR_MASK, \
                                    "JESD_XIP_204C_RX_TEST_PATTERN_MSB_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_CFG_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_CFG_RD_MASK, JESD_XIP_204C_RX_PRBS_CFG_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG0_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG1_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG2_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG3_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG4_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG5_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG6_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG7_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG8_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG9_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG10_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG11_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG12_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG13_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG14_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG15_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG16_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG17_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG18_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG19_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG20_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG21_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG22_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_XIP_204C_RX_PRBS_ERR_CNT_REG23_OFFSET, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_XIP_204C_RX_PRBS_ERR_CNT_RD_MASK, JESD_XIP_204C_RX_PRBS_ERR_CNT_WR_MASK, \
                                    "JESD_XIP_204C_RX_PRBS_ERR_CNT_REG23_OFFSET");

        }

    }

}
