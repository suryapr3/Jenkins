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
    DLNK_JESD0_PHY_PMA0_TXPLLCFGLOADER_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_TXPLLCFGLOADER_Q0_BASE, DLNK_JESD0_PHY_PMA0_TXPLLCFGLOADER_Q1_BASE, DLNK_JESD0_PHY_PMA0_TXPLLCFGLOADER_Q2_BASE, DLNK_JESD0_PHY_PMA0_TXPLLCFGLOADER_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_TXPLLCFGLOADER_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_TXPLLCFGLOADER_Q0_BASE, DLNK_JESD1_PHY_PMA0_TXPLLCFGLOADER_Q1_BASE, DLNK_JESD1_PHY_PMA0_TXPLLCFGLOADER_Q2_BASE, DLNK_JESD1_PHY_PMA0_TXPLLCFGLOADER_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_TXPLLCFGLOADER_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_TXPLLCFGLOADER_Q0_BASE, DLNK_JESD2_PHY_PMA0_TXPLLCFGLOADER_Q1_BASE, DLNK_JESD2_PHY_PMA0_TXPLLCFGLOADER_Q2_BASE, DLNK_JESD2_PHY_PMA0_TXPLLCFGLOADER_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_TXPLLCFGLOADER_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_TXPLLCFGLOADER_Q0_BASE, DLNK_JESD3_PHY_PMA0_TXPLLCFGLOADER_Q1_BASE, DLNK_JESD3_PHY_PMA0_TXPLLCFGLOADER_Q2_BASE, DLNK_JESD3_PHY_PMA0_TXPLLCFGLOADER_Q3_BASE
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
            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CFG_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CFG_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CFG_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_STAT_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_STAT_RD_MASK, PMA_TXPLLCFGLOADER_MSG_STAT_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_AMODE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_BMODE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_CMODE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_DMODE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DWMASK_EMODE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC2_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC2_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC2_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC3_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC3_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC3_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_DCO_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_DCO_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_DCO_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB2_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB2_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB2_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC2_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC2_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC2_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC4_AMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_AMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_AMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC4_AMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC4_AMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC2_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC2_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC2_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC3_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC3_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC3_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_DCO_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_DCO_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_DCO_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB2_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB2_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB2_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC2_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC2_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC2_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC4_BMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_BMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_BMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC4_BMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC4_BMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC2_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC2_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC2_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC3_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC3_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC3_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_DCO_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_DCO_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_DCO_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB2_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB2_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB2_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC2_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC2_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC2_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC4_CMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_CMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_CMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC4_CMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC4_CMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC2_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC2_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC2_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC3_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC3_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC3_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_DCO_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_DCO_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_DCO_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB2_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB2_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB2_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC2_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC2_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC2_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC4_DMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_DMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_DMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC4_DMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC4_DMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DIV1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DIV1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DIV1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DIV1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ADL1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ADL1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ADL1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ADL1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_FRAC_LOCK1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC2_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC2_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC2_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC2_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC3_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC3_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC3_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC3_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TAP_OVRD_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_DCO_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_DCO_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_DCO_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_DCO_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX_TDC_CRO_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_CTRL_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE0_SEL_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_VISA_LANE1_SEL_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CNTR_BIST_SETTINGS_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_CALIB2_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_CALIB2_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_CALIB2_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_CALIB2_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_PLL_FSM_CTRL_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TEMP_TRACKING_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL2_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_ANA_CTRL3_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DFX1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DFX1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DFX1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DFX1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_LDO1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_LDO1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_LDO1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_LDO1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_KVCC2_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_KVCC2_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_KVCC2_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_KVCC2_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_SPARE1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_SPARE1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_SPARE1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_SPARE1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING0_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_DCO_SWING1_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_TDC4_EMODE_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_EMODE_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_TDC4_EMODE_RD_MASK, PMA_TXPLLCFGLOADER_MSG_TDC4_EMODE_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_TDC4_EMODE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RW_SPARE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RW_SPARE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RW_SPARE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RW_SPARE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RW_SPARE_2_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_2_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RW_SPARE_2_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RW_SPARE_3_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RW_SPARE_3_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RW_SPARE_3_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RO_SPARE_0_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RO_SPARE_0_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RO_SPARE_0_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_TXPLLCFGLOADER_MSG_RO_SPARE_1_OFFSET, \
                                    PMA_TXPLLCFGLOADER_MSG_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_TXPLLCFGLOADER_MSG_RO_SPARE_1_RD_MASK, PMA_TXPLLCFGLOADER_MSG_RO_SPARE_1_WR_MASK, \
                                    "PMA_TXPLLCFGLOADER_MSG_RO_SPARE_1_OFFSET");

        }

    }

}
