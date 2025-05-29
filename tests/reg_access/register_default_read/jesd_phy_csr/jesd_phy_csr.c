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
    DLNK_JESD0_PHY_CSR_BASE, DLNK_JESD1_PHY_CSR_BASE, DLNK_JESD2_PHY_CSR_BASE, DLNK_JESD3_PHY_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_PLL_FORCE_PWR_UP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_PLL_FORCE_PWR_UP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_RATE_DIV_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_RATE_DIV_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_DATA_CLK_DIV_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_DATA_CLK_DIV_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_ELEC_IDLE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_ELEC_IDLE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_FFE_COEFF_CM_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_FFE_COEFF_CM_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_FFE_COEFF_CP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_FFE_COEFF_CP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_MODE_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_MODE_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_OVR_SMPL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_OVR_SMPL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EQ_PRECAL_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EQ_PRECAL_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EQ_STATIC_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EQ_STATIC_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EQ_ADPAT_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EQ_ADPAT_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EYE_MEAS_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EYE_MEAS_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_PLL_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_PLL_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_TX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_TX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_CDR_LK2_DATA_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_CDR_LK2_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_SIG_DETECT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_SIG_DETECT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_CDR_FREQ_LK_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_CDR_FREQ_LK_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EQ_ADAPT_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EQ_ADAPT_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_EYE_MEAS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_EYE_MEAS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_RX_TERM_HIZ_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_RX_TERM_HIZ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_EQ_INPROGRESS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_EQ_INPROGRESS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_EQ_TRAINING_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_EQ_TRAINING_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_TXDETECTRX_REQ_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_TXDETECTRX_REQ_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_L1SS_RXDET_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_L1SS_RXDET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_SRIS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_SRIS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_LFPS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_LFPS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_TXBEACON_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_TXBEACON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PIPEPCS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PIPEPCS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PMA_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PMA_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PCS_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PCS_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PMA_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PMA_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE0_PCS_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE0_PCS_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_PLL_FORCE_PWR_UP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_PLL_FORCE_PWR_UP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_RATE_DIV_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_RATE_DIV_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_DATA_CLK_DIV_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_DATA_CLK_DIV_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_ELEC_IDLE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_ELEC_IDLE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_FFE_COEFF_CM_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_FFE_COEFF_CM_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_FFE_COEFF_CP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_FFE_COEFF_CP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_MODE_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_MODE_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_OVR_SMPL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_OVR_SMPL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EQ_PRECAL_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EQ_PRECAL_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EQ_STATIC_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EQ_STATIC_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EQ_ADPAT_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EQ_ADPAT_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EYE_MEAS_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EYE_MEAS_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_PLL_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_PLL_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_TX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_TX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_CDR_LK2_DATA_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_CDR_LK2_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_SIG_DETECT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_SIG_DETECT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_CDR_FREQ_LK_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_CDR_FREQ_LK_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EQ_ADAPT_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EQ_ADAPT_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_EYE_MEAS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_EYE_MEAS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_RX_TERM_HIZ_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_RX_TERM_HIZ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_EQ_INPROGRESS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_EQ_INPROGRESS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_EQ_TRAINING_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_EQ_TRAINING_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_TXDETECTRX_REQ_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_TXDETECTRX_REQ_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_L1SS_RXDET_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_L1SS_RXDET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_SRIS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_SRIS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_LFPS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_LFPS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_TXBEACON_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_TXBEACON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PIPEPCS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PIPEPCS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PMA_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PMA_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PCS_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PCS_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PMA_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PMA_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE1_PCS_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE1_PCS_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_PLL_FORCE_PWR_UP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_PLL_FORCE_PWR_UP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_RATE_DIV_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_RATE_DIV_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_DATA_CLK_DIV_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_DATA_CLK_DIV_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_ELEC_IDLE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_ELEC_IDLE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_FFE_COEFF_CM_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_FFE_COEFF_CM_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_FFE_COEFF_CP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_FFE_COEFF_CP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_MODE_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_MODE_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_OVR_SMPL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_OVR_SMPL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EQ_PRECAL_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EQ_PRECAL_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EQ_STATIC_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EQ_STATIC_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EQ_ADPAT_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EQ_ADPAT_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EYE_MEAS_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EYE_MEAS_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_PLL_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_PLL_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_TX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_TX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_CDR_LK2_DATA_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_CDR_LK2_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_SIG_DETECT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_SIG_DETECT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_CDR_FREQ_LK_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_CDR_FREQ_LK_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EQ_ADAPT_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EQ_ADAPT_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_EYE_MEAS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_EYE_MEAS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_RX_TERM_HIZ_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_RX_TERM_HIZ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_EQ_INPROGRESS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_EQ_INPROGRESS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_EQ_TRAINING_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_EQ_TRAINING_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_TXDETECTRX_REQ_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_TXDETECTRX_REQ_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_L1SS_RXDET_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_L1SS_RXDET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_SRIS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_SRIS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_LFPS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_LFPS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_TXBEACON_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_TXBEACON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PIPEPCS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PIPEPCS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PMA_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PMA_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PCS_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PCS_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PMA_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PMA_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE2_PCS_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE2_PCS_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_PLL_FORCE_PWR_UP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_FORCE_PWR_UP_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_PLL_FORCE_PWR_UP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_RATE_DIV_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_RATE_DIV_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_RATE_DIV_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_DATA_CLK_DIV_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_DATA_CLK_DIV_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_DATA_CLK_DIV_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_ELEC_IDLE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_ELEC_IDLE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_ELEC_IDLE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_FFE_COEFF_CM_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CM_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_FFE_COEFF_CM_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_FFE_COEFF_CP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_FFE_COEFF_CP_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_FFE_COEFF_CP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_PSTATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_PSTATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_PSTATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_FREQ_RATE_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_FREQ_RATE_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_FREQ_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_MODE_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MODE_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_MODE_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_MOD_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_MOD_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_OVR_SMPL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_OVR_SMPL_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_OVR_SMPL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EQ_PRECAL_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_PRECAL_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EQ_PRECAL_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EQ_STATIC_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_STATIC_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EQ_STATIC_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EQ_ADPAT_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADPAT_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EQ_ADPAT_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EYE_MEAS_START_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_START_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EYE_MEAS_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_PLL_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_PLL_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_PLL_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_TX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_TX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_TX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_CFG_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CFG_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_CFG_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_CDR_LK2_DATA_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_LK2_DATA_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_CDR_LK2_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_SIG_DETECT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_SIG_DETECT_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_SIG_DETECT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_CDR_FREQ_LK_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_CDR_FREQ_LK_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_CDR_FREQ_LK_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EQ_ADAPT_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EQ_ADAPT_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EQ_ADAPT_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_EYE_MEAS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_EYE_MEAS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_EYE_MEAS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_RX_TERM_HIZ_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_RX_TERM_HIZ_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_RX_TERM_HIZ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_EQ_INPROGRESS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_INPROGRESS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_EQ_INPROGRESS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_EQ_TRAINING_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_EQ_TRAINING_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_EQ_TRAINING_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_TXDETECTRX_REQ_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXDETECTRX_REQ_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_TXDETECTRX_REQ_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_L1SS_RXDET_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_RXDET_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_L1SS_RXDET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_L1SS_TXCMNMODE_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_L1SS_TXCMNMODE_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_SRIS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_SRIS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_SRIS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_LFPS_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_LFPS_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_LFPS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_TXBEACON_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_TXBEACON_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_TXBEACON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_RXEIOSDETECTSTAT_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_RXEIOSDETECTSTAT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PIPEPCS_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PIPEPCS_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PIPEPCS_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PMA_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PMA_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PCS_LN_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PCS_LN_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PMA_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PMA_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PMA_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE3_PCS_LN_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_PCS_LN_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE3_PCS_LN_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_FORCE_PWRUP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_FORCE_PWRUP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_FORCE_PWRUP_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_FORCE_PWRUP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PLLA_FORCE_PWRUP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLA_FORCE_PWRUP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLA_FORCE_PWRUP_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PLLA_FORCE_PWRUP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PLLB_FORCE_PWRUP_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLB_FORCE_PWRUP_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLB_FORCE_PWRUP_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PLLB_FORCE_PWRUP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PLLA_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLA_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLA_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PLLA_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PLLB_RDY_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLB_RDY_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PLLB_RDY_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PLLB_RDY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_UCSS_SPARE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PMA_SPARE_CMN_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_IN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_IN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_IN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_IN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_OUT_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_OUT_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_OUT_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PCS_SPARE_CMN_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_RX_LANE_MUX_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_RX_LANE_MUX_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_RX_LANE_MUX_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_RX_LANE_MUX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_TX_LANE_MUX_SEL_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_TX_LANE_MUX_SEL_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_TX_LANE_MUX_SEL_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_TX_LANE_MUX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PMA_REF_HIGHZ_TERM_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_REF_HIGHZ_TERM_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PMA_REF_HIGHZ_TERM_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PMA_REF_HIGHZ_TERM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_IRQ_INTR_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_IRQ_INTR_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_IRQ_INTR_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_IRQ_INTR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_HIGH_INTR_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_HIGH_INTR_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_HIGH_INTR_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_HIGH_INTR_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_LOW_INTR_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_LOW_INTR_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_LOW_INTR_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_LOW_INTR_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_ALARM_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_ALARM_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_ALARM_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PCS_EVENT_ALARM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_STS_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_STS_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_STS_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_HIGH_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_HIGH_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_HIGH_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_LOW_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_LOW_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_LOW_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_ALM_EN_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_ALM_EN_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_ALM_EN_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_ALM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_CLR_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_CLR_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_CLR_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_FRC_OFFSET, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_FRC_DEFAULT, \
                                    JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_FRC_RD_MASK, "JESD_PHY_CSR_PHY_LANE_CMN_PHY_ERR_FRC_OFFSET");

    }

}
