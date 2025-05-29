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
    DLNK_JESD0_PHY_PMA0_ANACMNPLLA_BASE, DLNK_JESD0_PHY_PMA0_ANACMNPLLB_BASE, DLNK_JESD1_PHY_PMA0_ANACMNPLLA_BASE, DLNK_JESD1_PHY_PMA0_ANACMNPLLB_BASE, DLNK_JESD2_PHY_PMA0_ANACMNPLLA_BASE,
    DLNK_JESD2_PHY_PMA0_ANACMNPLLB_BASE, DLNK_JESD3_PHY_PMA0_ANACMNPLLA_BASE, DLNK_JESD3_PHY_PMA0_ANACMNPLLB_BASE
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
            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DIV0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DIV0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DIV0_RD_MASK, PMA_ANACMNPLL_MSG_DIV0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DIV0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DIV1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DIV1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DIV1_RD_MASK, PMA_ANACMNPLL_MSG_DIV1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DIV1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_ADL0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_ADL0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_ADL0_RD_MASK, PMA_ANACMNPLL_MSG_ADL0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_ADL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_ADL1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_ADL1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_ADL1_RD_MASK, PMA_ANACMNPLL_MSG_ADL1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_ADL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_FRAC_LOCK0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_FRAC_LOCK0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_FRAC_LOCK0_RD_MASK, PMA_ANACMNPLL_MSG_FRAC_LOCK0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_FRAC_LOCK0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_FRAC_LOCK1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_FRAC_LOCK1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_FRAC_LOCK1_RD_MASK, PMA_ANACMNPLL_MSG_FRAC_LOCK1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_FRAC_LOCK1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TDC0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TDC0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TDC0_RD_MASK, PMA_ANACMNPLL_MSG_TDC0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TDC0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TDC1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TDC1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TDC1_RD_MASK, PMA_ANACMNPLL_MSG_TDC1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TDC1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TDC2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TDC2_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TDC2_RD_MASK, PMA_ANACMNPLL_MSG_TDC2_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TDC2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TDC3_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TDC3_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TDC3_RD_MASK, PMA_ANACMNPLL_MSG_TDC3_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TDC3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TAP_OVRD_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TAP_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TAP_OVRD_RD_MASK, PMA_ANACMNPLL_MSG_TAP_OVRD_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TAP_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DFX_DCO_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DFX_DCO_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DFX_DCO_RD_MASK, PMA_ANACMNPLL_MSG_DFX_DCO_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DFX_DCO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DFX_TDC_CRO_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DFX_TDC_CRO_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DFX_TDC_CRO_RD_MASK, PMA_ANACMNPLL_MSG_DFX_TDC_CRO_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DFX_TDC_CRO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_VISA_CTRL_OFFSET, \
                                    PMA_ANACMNPLL_MSG_VISA_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_VISA_CTRL_RD_MASK, PMA_ANACMNPLL_MSG_VISA_CTRL_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_VISA_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_VISA_LANE0_SEL_OFFSET, \
                                    PMA_ANACMNPLL_MSG_VISA_LANE0_SEL_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_VISA_LANE0_SEL_RD_MASK, PMA_ANACMNPLL_MSG_VISA_LANE0_SEL_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_VISA_LANE0_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_VISA_LANE1_SEL_OFFSET, \
                                    PMA_ANACMNPLL_MSG_VISA_LANE1_SEL_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_VISA_LANE1_SEL_RD_MASK, PMA_ANACMNPLL_MSG_VISA_LANE1_SEL_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_VISA_LANE1_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_CNTR_BIST_SETTINGS_OFFSET, \
                                    PMA_ANACMNPLL_MSG_CNTR_BIST_SETTINGS_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_CNTR_BIST_SETTINGS_RD_MASK, PMA_ANACMNPLL_MSG_CNTR_BIST_SETTINGS_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_CNTR_BIST_SETTINGS_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_TDC_DCO0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO0_RD_MASK, PMA_ANACMNPLL_MSG_RO_TDC_DCO0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_TDC_DCO0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_TDC_DCO1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO1_RD_MASK, PMA_ANACMNPLL_MSG_RO_TDC_DCO1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_TDC_DCO1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_TDC_DCO2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO2_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO2_RD_MASK, PMA_ANACMNPLL_MSG_RO_TDC_DCO2_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_TDC_DCO2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_TDC_DCO3_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO3_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DCO3_RD_MASK, PMA_ANACMNPLL_MSG_RO_TDC_DCO3_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_TDC_DCO3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_CALIB0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_CALIB0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_CALIB0_RD_MASK, PMA_ANACMNPLL_MSG_CALIB0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_CALIB0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_CALIB1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_CALIB1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_CALIB1_RD_MASK, PMA_ANACMNPLL_MSG_CALIB1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_CALIB1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_CALIB2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_CALIB2_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_CALIB2_RD_MASK, PMA_ANACMNPLL_MSG_CALIB2_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_CALIB2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_PLL_FSM_CTRL_OFFSET, \
                                    PMA_ANACMNPLL_MSG_PLL_FSM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_PLL_FSM_CTRL_RD_MASK, PMA_ANACMNPLL_MSG_PLL_FSM_CTRL_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_PLL_FSM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TEMP_TRACKING_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TEMP_TRACKING_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TEMP_TRACKING_RD_MASK, PMA_ANACMNPLL_MSG_TEMP_TRACKING_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TEMP_TRACKING_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_ANA_CTRL1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL1_RD_MASK, PMA_ANACMNPLL_MSG_ANA_CTRL1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_ANA_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_ANA_CTRL2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL2_RD_MASK, PMA_ANACMNPLL_MSG_ANA_CTRL2_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_ANA_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_ANA_CTRL3_OFFSET, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL3_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_ANA_CTRL3_RD_MASK, PMA_ANACMNPLL_MSG_ANA_CTRL3_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_ANA_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DFX0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DFX0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DFX0_RD_MASK, PMA_ANACMNPLL_MSG_DFX0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DFX0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DFX1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DFX1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DFX1_RD_MASK, PMA_ANACMNPLL_MSG_DFX1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DFX1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_LDO0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_LDO0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_LDO0_RD_MASK, PMA_ANACMNPLL_MSG_LDO0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_LDO0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_LDO1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_LDO1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_LDO1_RD_MASK, PMA_ANACMNPLL_MSG_LDO1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_LDO1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_KVCC0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_KVCC0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_KVCC0_RD_MASK, PMA_ANACMNPLL_MSG_KVCC0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_KVCC0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_KVCC1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_KVCC1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_KVCC1_RD_MASK, PMA_ANACMNPLL_MSG_KVCC1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_KVCC1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_KVCC2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_KVCC2_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_KVCC2_RD_MASK, PMA_ANACMNPLL_MSG_KVCC2_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_KVCC2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_SPARE0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_SPARE0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_SPARE0_RD_MASK, PMA_ANACMNPLL_MSG_SPARE0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_SPARE0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_VISA_LOCKCNT_RCOMP_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_VISA_LOCKCNT_RCOMP_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_VISA_LOCKCNT_RCOMP_RD_MASK, PMA_ANACMNPLL_MSG_RO_VISA_LOCKCNT_RCOMP_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_VISA_LOCKCNT_RCOMP_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_DIV_BIAS_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_DIV_BIAS_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_DIV_BIAS_RD_MASK, PMA_ANACMNPLL_MSG_RO_DIV_BIAS_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_DIV_BIAS_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_BWM_LF_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_BWM_LF_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_BWM_LF_RD_MASK, PMA_ANACMNPLL_MSG_RO_BWM_LF_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_BWM_LF_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_DCO_CALIB_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_DCO_CALIB_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_DCO_CALIB_RD_MASK, PMA_ANACMNPLL_MSG_RO_DCO_CALIB_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_DCO_CALIB_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_RO_TDC_OFFSET, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_RO_TDC_RD_MASK, PMA_ANACMNPLL_MSG_RO_TDC_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_RO_TDC_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_STAT_OFFSET, \
                                    PMA_ANACMNPLL_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_STAT_RD_MASK, PMA_ANACMNPLL_MSG_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_STAT1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_STAT_RD_MASK, PMA_ANACMNPLL_MSG_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_STAT2_OFFSET, \
                                    PMA_ANACMNPLL_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_STAT_RD_MASK, PMA_ANACMNPLL_MSG_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_STAT3_OFFSET, \
                                    PMA_ANACMNPLL_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_STAT_RD_MASK, PMA_ANACMNPLL_MSG_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_SPARE1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_SPARE1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_SPARE1_RD_MASK, PMA_ANACMNPLL_MSG_SPARE1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_SPARE1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_SPARE_STAT_OFFSET, \
                                    PMA_ANACMNPLL_MSG_SPARE_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_SPARE_STAT_RD_MASK, PMA_ANACMNPLL_MSG_SPARE_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_SPARE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DCO_SWING0_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DCO_SWING0_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DCO_SWING0_RD_MASK, PMA_ANACMNPLL_MSG_DCO_SWING0_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DCO_SWING0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_DCO_SWING1_OFFSET, \
                                    PMA_ANACMNPLL_MSG_DCO_SWING1_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_DCO_SWING1_RD_MASK, PMA_ANACMNPLL_MSG_DCO_SWING1_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_DCO_SWING1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_TDC4_OFFSET, \
                                    PMA_ANACMNPLL_MSG_TDC4_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_TDC4_RD_MASK, PMA_ANACMNPLL_MSG_TDC4_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_TDC4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_ANACMNPLL_MSG_STAT4_OFFSET, \
                                    PMA_ANACMNPLL_MSG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_ANACMNPLL_MSG_STAT_RD_MASK, PMA_ANACMNPLL_MSG_STAT_WR_MASK, \
                                    "PMA_ANACMNPLL_MSG_STAT4_OFFSET");

        }

    }

}
