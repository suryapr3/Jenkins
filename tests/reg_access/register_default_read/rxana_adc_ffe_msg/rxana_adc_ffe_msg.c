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
    DLNK_JESD0_PHY_PMA0_RXANA_ADC_FFE_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_FFE_Q0_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_FFE_Q1_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_FFE_Q2_BASE, DLNK_JESD0_PHY_PMA0_RXANA_ADC_FFE_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RXANA_ADC_FFE_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_FFE_Q0_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_FFE_Q1_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_FFE_Q2_BASE, DLNK_JESD1_PHY_PMA0_RXANA_ADC_FFE_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RXANA_ADC_FFE_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_FFE_Q0_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_FFE_Q1_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_FFE_Q2_BASE, DLNK_JESD2_PHY_PMA0_RXANA_ADC_FFE_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RXANA_ADC_FFE_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_FFE_Q0_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_FFE_Q1_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_FFE_Q2_BASE, DLNK_JESD3_PHY_PMA0_RXANA_ADC_FFE_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE0_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE0_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE0_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE0_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE1_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE1_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE1_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE1_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE2_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE2_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE2_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE2_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE3_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE3_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE3_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE3_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE_DCD0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_DCD0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_DCD0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE_DCD0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE_DCD1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_DCD1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_DCD1_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE_DCD1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE_CAP_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_CAP_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_CAP_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE_CAP_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_DFX0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_DFX0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_DFX0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_DFX2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_DFX2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_DFX2_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_DFX2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_NEXTPHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_NEXTPHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_NEXTPHASE_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_NEXTPHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM1_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM2_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM3_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM3_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM3_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM3_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM4_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM4_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM4_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_BIAS_TRIM4_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_OFC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_OFC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_OFC_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_CMFB_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CMFB_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CMFB_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_CMFB_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_RES_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_RES_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_RES_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_RES_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_VCASC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_VCASC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_VCASC_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_VCASC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL1_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_SUMMER_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q0_FFE_SPARE0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_SPARE0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q0_FFE_SPARE0_RD_MASK, "RXANA_ADC_FFE_MSG_Q0_FFE_SPARE0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE0_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE0_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE0_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE0_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE1_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE1_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE1_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE1_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE2_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE2_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE2_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE2_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE3_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE3_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE3_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE3_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE_DCD0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_DCD0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_DCD0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE_DCD0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE_DCD1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_DCD1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_DCD1_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE_DCD1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE_CAP_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_CAP_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_CAP_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE_CAP_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_DFX0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_DFX0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_DFX0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_DFX2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_DFX2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_DFX2_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_DFX2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_NEXTPHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_NEXTPHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_NEXTPHASE_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_NEXTPHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM1_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM2_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM3_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM3_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM3_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM3_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM4_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM4_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM4_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_BIAS_TRIM4_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_OFC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_OFC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_OFC_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_CMFB_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CMFB_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CMFB_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_CMFB_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_RES_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_RES_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_RES_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_RES_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_VCASC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_VCASC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_VCASC_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_VCASC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL1_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_SUMMER_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q1_FFE_SPARE0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_SPARE0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q1_FFE_SPARE0_RD_MASK, "RXANA_ADC_FFE_MSG_Q1_FFE_SPARE0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE0_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE0_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE0_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE0_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE1_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE1_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE1_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE1_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE2_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE2_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE2_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE2_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE3_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE3_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE3_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE3_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE_DCD0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_DCD0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_DCD0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE_DCD0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE_DCD1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_DCD1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_DCD1_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE_DCD1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE_CAP_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_CAP_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_CAP_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE_CAP_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_DFX0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_DFX0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_DFX0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_DFX2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_DFX2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_DFX2_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_DFX2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_NEXTPHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_NEXTPHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_NEXTPHASE_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_NEXTPHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM1_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM2_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM3_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM3_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM3_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM3_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM4_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM4_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM4_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_BIAS_TRIM4_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_OFC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_OFC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_OFC_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_CMFB_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CMFB_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CMFB_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_CMFB_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_RES_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_RES_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_RES_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_RES_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_VCASC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_VCASC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_VCASC_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_VCASC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL1_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_SUMMER_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q2_FFE_SPARE0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_SPARE0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q2_FFE_SPARE0_RD_MASK, "RXANA_ADC_FFE_MSG_Q2_FFE_SPARE0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE0_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE0_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE0_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE0_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE1_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE1_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE1_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE1_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE2_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE2_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE2_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE2_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE3_COEFF_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE3_COEFF_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE3_COEFF_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE3_COEFF_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE_DCD0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_DCD0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_DCD0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE_DCD0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE_DCD1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_DCD1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_DCD1_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE_DCD1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE_CAP_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_CAP_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_CAP_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE_CAP_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_DFX0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_DFX0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_DFX0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_DFX2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_DFX2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_DFX2_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_DFX2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_NEXTPHASE_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_NEXTPHASE_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_NEXTPHASE_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_NEXTPHASE_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM1_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM2_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM2_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM2_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM2_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM3_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM3_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM3_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM3_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM4_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM4_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM4_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_BIAS_TRIM4_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_OFC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_OFC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_OFC_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_OFC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_CMFB_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CMFB_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CMFB_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_CMFB_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_RES_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_RES_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_RES_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_RES_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_VCASC_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_VCASC_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_VCASC_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_VCASC_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL1_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL1_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL1_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_SUMMER_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RXANA_ADC_FFE_MSG_Q3_FFE_SPARE0_OFFSET, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_SPARE0_DEFAULT, \
                                    RXANA_ADC_FFE_MSG_Q3_FFE_SPARE0_RD_MASK, "RXANA_ADC_FFE_MSG_Q3_FFE_SPARE0_OFFSET");

    }

}
