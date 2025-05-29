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


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    int i;
    init();

    uint32_t base_address[] = {
    DLNK_JESD0_PHY_PMA0_ANATXPLL_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_ANATXPLL_Q0_BASE, DLNK_JESD0_PHY_PMA0_ANATXPLL_Q1_BASE, DLNK_JESD0_PHY_PMA0_ANATXPLL_Q2_BASE, DLNK_JESD0_PHY_PMA0_ANATXPLL_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_ANATXPLL_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_ANATXPLL_Q0_BASE, DLNK_JESD1_PHY_PMA0_ANATXPLL_Q1_BASE, DLNK_JESD1_PHY_PMA0_ANATXPLL_Q2_BASE, DLNK_JESD1_PHY_PMA0_ANATXPLL_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_ANATXPLL_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_ANATXPLL_Q0_BASE, DLNK_JESD2_PHY_PMA0_ANATXPLL_Q1_BASE, DLNK_JESD2_PHY_PMA0_ANATXPLL_Q2_BASE, DLNK_JESD2_PHY_PMA0_ANATXPLL_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_ANATXPLL_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_ANATXPLL_Q0_BASE, DLNK_JESD3_PHY_PMA0_ANATXPLL_Q1_BASE, DLNK_JESD3_PHY_PMA0_ANATXPLL_Q2_BASE, DLNK_JESD3_PHY_PMA0_ANATXPLL_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DIV0_OFFSET, \
                                    PMA_ANATXPLL_MSG_DIV0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DIV0_RD_MASK, "PMA_ANATXPLL_MSG_DIV0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DIV1_OFFSET, \
                                    PMA_ANATXPLL_MSG_DIV1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DIV1_RD_MASK, "PMA_ANATXPLL_MSG_DIV1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_ADL0_OFFSET, \
                                    PMA_ANATXPLL_MSG_ADL0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_ADL0_RD_MASK, "PMA_ANATXPLL_MSG_ADL0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_ADL1_OFFSET, \
                                    PMA_ANATXPLL_MSG_ADL1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_ADL1_RD_MASK, "PMA_ANATXPLL_MSG_ADL1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_FRAC_LOCK0_OFFSET, \
                                    PMA_ANATXPLL_MSG_FRAC_LOCK0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_FRAC_LOCK0_RD_MASK, "PMA_ANATXPLL_MSG_FRAC_LOCK0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_FRAC_LOCK1_OFFSET, \
                                    PMA_ANATXPLL_MSG_FRAC_LOCK1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_FRAC_LOCK1_RD_MASK, "PMA_ANATXPLL_MSG_FRAC_LOCK1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TDC0_OFFSET, \
                                    PMA_ANATXPLL_MSG_TDC0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TDC0_RD_MASK, "PMA_ANATXPLL_MSG_TDC0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TDC1_OFFSET, \
                                    PMA_ANATXPLL_MSG_TDC1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TDC1_RD_MASK, "PMA_ANATXPLL_MSG_TDC1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TDC2_OFFSET, \
                                    PMA_ANATXPLL_MSG_TDC2_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TDC2_RD_MASK, "PMA_ANATXPLL_MSG_TDC2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TDC3_OFFSET, \
                                    PMA_ANATXPLL_MSG_TDC3_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TDC3_RD_MASK, "PMA_ANATXPLL_MSG_TDC3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TAP_OVRD_OFFSET, \
                                    PMA_ANATXPLL_MSG_TAP_OVRD_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TAP_OVRD_RD_MASK, "PMA_ANATXPLL_MSG_TAP_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DFX_DCO_OFFSET, \
                                    PMA_ANATXPLL_MSG_DFX_DCO_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DFX_DCO_RD_MASK, "PMA_ANATXPLL_MSG_DFX_DCO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DFX_TDC_CRO_OFFSET, \
                                    PMA_ANATXPLL_MSG_DFX_TDC_CRO_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DFX_TDC_CRO_RD_MASK, "PMA_ANATXPLL_MSG_DFX_TDC_CRO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_VISA_CTRL_OFFSET, \
                                    PMA_ANATXPLL_MSG_VISA_CTRL_DEFAULT, \
                                    PMA_ANATXPLL_MSG_VISA_CTRL_RD_MASK, "PMA_ANATXPLL_MSG_VISA_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_VISA_LANE0_SEL_OFFSET, \
                                    PMA_ANATXPLL_MSG_VISA_LANE0_SEL_DEFAULT, \
                                    PMA_ANATXPLL_MSG_VISA_LANE0_SEL_RD_MASK, "PMA_ANATXPLL_MSG_VISA_LANE0_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_VISA_LANE1_SEL_OFFSET, \
                                    PMA_ANATXPLL_MSG_VISA_LANE1_SEL_DEFAULT, \
                                    PMA_ANATXPLL_MSG_VISA_LANE1_SEL_RD_MASK, "PMA_ANATXPLL_MSG_VISA_LANE1_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_CNTR_BIST_SETTINGS_OFFSET, \
                                    PMA_ANATXPLL_MSG_CNTR_BIST_SETTINGS_DEFAULT, \
                                    PMA_ANATXPLL_MSG_CNTR_BIST_SETTINGS_RD_MASK, "PMA_ANATXPLL_MSG_CNTR_BIST_SETTINGS_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_TDC_DCO0_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO0_RD_MASK, "PMA_ANATXPLL_MSG_RO_TDC_DCO0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_TDC_DCO1_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO1_RD_MASK, "PMA_ANATXPLL_MSG_RO_TDC_DCO1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_TDC_DCO2_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO2_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO2_RD_MASK, "PMA_ANATXPLL_MSG_RO_TDC_DCO2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_TDC_DCO3_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO3_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DCO3_RD_MASK, "PMA_ANATXPLL_MSG_RO_TDC_DCO3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_CALIB0_OFFSET, \
                                    PMA_ANATXPLL_MSG_CALIB0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_CALIB0_RD_MASK, "PMA_ANATXPLL_MSG_CALIB0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_CALIB1_OFFSET, \
                                    PMA_ANATXPLL_MSG_CALIB1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_CALIB1_RD_MASK, "PMA_ANATXPLL_MSG_CALIB1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_CALIB2_OFFSET, \
                                    PMA_ANATXPLL_MSG_CALIB2_DEFAULT, \
                                    PMA_ANATXPLL_MSG_CALIB2_RD_MASK, "PMA_ANATXPLL_MSG_CALIB2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_PLL_FSM_CTRL_OFFSET, \
                                    PMA_ANATXPLL_MSG_PLL_FSM_CTRL_DEFAULT, \
                                    PMA_ANATXPLL_MSG_PLL_FSM_CTRL_RD_MASK, "PMA_ANATXPLL_MSG_PLL_FSM_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TEMP_TRACKING_OFFSET, \
                                    PMA_ANATXPLL_MSG_TEMP_TRACKING_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TEMP_TRACKING_RD_MASK, "PMA_ANATXPLL_MSG_TEMP_TRACKING_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_ANA_CTRL1_OFFSET, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL1_RD_MASK, "PMA_ANATXPLL_MSG_ANA_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_ANA_CTRL2_OFFSET, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL2_DEFAULT, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL2_RD_MASK, "PMA_ANATXPLL_MSG_ANA_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_ANA_CTRL3_OFFSET, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL3_DEFAULT, \
                                    PMA_ANATXPLL_MSG_ANA_CTRL3_RD_MASK, "PMA_ANATXPLL_MSG_ANA_CTRL3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DFX0_OFFSET, \
                                    PMA_ANATXPLL_MSG_DFX0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DFX0_RD_MASK, "PMA_ANATXPLL_MSG_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DFX1_OFFSET, \
                                    PMA_ANATXPLL_MSG_DFX1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DFX1_RD_MASK, "PMA_ANATXPLL_MSG_DFX1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_LDO0_OFFSET, \
                                    PMA_ANATXPLL_MSG_LDO0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_LDO0_RD_MASK, "PMA_ANATXPLL_MSG_LDO0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_LDO1_OFFSET, \
                                    PMA_ANATXPLL_MSG_LDO1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_LDO1_RD_MASK, "PMA_ANATXPLL_MSG_LDO1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_KVCC0_OFFSET, \
                                    PMA_ANATXPLL_MSG_KVCC0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_KVCC0_RD_MASK, "PMA_ANATXPLL_MSG_KVCC0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_KVCC1_OFFSET, \
                                    PMA_ANATXPLL_MSG_KVCC1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_KVCC1_RD_MASK, "PMA_ANATXPLL_MSG_KVCC1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_KVCC2_OFFSET, \
                                    PMA_ANATXPLL_MSG_KVCC2_DEFAULT, \
                                    PMA_ANATXPLL_MSG_KVCC2_RD_MASK, "PMA_ANATXPLL_MSG_KVCC2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_SPARE0_OFFSET, \
                                    PMA_ANATXPLL_MSG_SPARE0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_SPARE0_RD_MASK, "PMA_ANATXPLL_MSG_SPARE0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_VISA_LOCKCNT_RCOMP_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_VISA_LOCKCNT_RCOMP_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_VISA_LOCKCNT_RCOMP_RD_MASK, "PMA_ANATXPLL_MSG_RO_VISA_LOCKCNT_RCOMP_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_DIV_BIAS_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_DIV_BIAS_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_DIV_BIAS_RD_MASK, "PMA_ANATXPLL_MSG_RO_DIV_BIAS_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_BWM_LF_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_BWM_LF_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_BWM_LF_RD_MASK, "PMA_ANATXPLL_MSG_RO_BWM_LF_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_DCO_CALIB_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_DCO_CALIB_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_DCO_CALIB_RD_MASK, "PMA_ANATXPLL_MSG_RO_DCO_CALIB_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_RO_TDC_OFFSET, \
                                    PMA_ANATXPLL_MSG_RO_TDC_DEFAULT, \
                                    PMA_ANATXPLL_MSG_RO_TDC_RD_MASK, "PMA_ANATXPLL_MSG_RO_TDC_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_STAT_OFFSET, \
                                    PMA_ANATXPLL_MSG_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_STAT_RD_MASK, "PMA_ANATXPLL_MSG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_STAT1_OFFSET, \
                                    PMA_ANATXPLL_MSG_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_STAT_RD_MASK, "PMA_ANATXPLL_MSG_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_STAT2_OFFSET, \
                                    PMA_ANATXPLL_MSG_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_STAT_RD_MASK, "PMA_ANATXPLL_MSG_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_STAT3_OFFSET, \
                                    PMA_ANATXPLL_MSG_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_STAT_RD_MASK, "PMA_ANATXPLL_MSG_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_SPARE1_OFFSET, \
                                    PMA_ANATXPLL_MSG_SPARE1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_SPARE1_RD_MASK, "PMA_ANATXPLL_MSG_SPARE1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_SPARE_STAT_OFFSET, \
                                    PMA_ANATXPLL_MSG_SPARE_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_SPARE_STAT_RD_MASK, "PMA_ANATXPLL_MSG_SPARE_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DCO_SWING0_OFFSET, \
                                    PMA_ANATXPLL_MSG_DCO_SWING0_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DCO_SWING0_RD_MASK, "PMA_ANATXPLL_MSG_DCO_SWING0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_DCO_SWING1_OFFSET, \
                                    PMA_ANATXPLL_MSG_DCO_SWING1_DEFAULT, \
                                    PMA_ANATXPLL_MSG_DCO_SWING1_RD_MASK, "PMA_ANATXPLL_MSG_DCO_SWING1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_TDC4_OFFSET, \
                                    PMA_ANATXPLL_MSG_TDC4_DEFAULT, \
                                    PMA_ANATXPLL_MSG_TDC4_RD_MASK, "PMA_ANATXPLL_MSG_TDC4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_ANATXPLL_MSG_STAT4_OFFSET, \
                                    PMA_ANATXPLL_MSG_STAT_DEFAULT, \
                                    PMA_ANATXPLL_MSG_STAT_RD_MASK, "PMA_ANATXPLL_MSG_STAT4_OFFSET");

    }

}
