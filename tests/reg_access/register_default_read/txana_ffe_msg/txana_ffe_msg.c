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
    DLNK_JESD0_PHY_PMA0_TXANA_FFE_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_TXANA_FFE_Q0_BASE, DLNK_JESD0_PHY_PMA0_TXANA_FFE_Q1_BASE, DLNK_JESD0_PHY_PMA0_TXANA_FFE_Q2_BASE, DLNK_JESD0_PHY_PMA0_TXANA_FFE_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_TXANA_FFE_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_TXANA_FFE_Q0_BASE, DLNK_JESD1_PHY_PMA0_TXANA_FFE_Q1_BASE, DLNK_JESD1_PHY_PMA0_TXANA_FFE_Q2_BASE, DLNK_JESD1_PHY_PMA0_TXANA_FFE_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_TXANA_FFE_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_TXANA_FFE_Q0_BASE, DLNK_JESD2_PHY_PMA0_TXANA_FFE_Q1_BASE, DLNK_JESD2_PHY_PMA0_TXANA_FFE_Q2_BASE, DLNK_JESD2_PHY_PMA0_TXANA_FFE_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_TXANA_FFE_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_TXANA_FFE_Q0_BASE, DLNK_JESD3_PHY_PMA0_TXANA_FFE_Q1_BASE, DLNK_JESD3_PHY_PMA0_TXANA_FFE_Q2_BASE, DLNK_JESD3_PHY_PMA0_TXANA_FFE_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKPATH_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKPATH_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKPATH_CTRL0_RD_MASK, "TXANA_FFE_MSG_TXCLKPATH_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLK_REFGEN0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLK_REFGEN0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLK_REFGEN0_RD_MASK, "TXANA_FFE_MSG_TXCLK_REFGEN0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLK_REFGEN1_OFFSET, \
                                    TXANA_FFE_MSG_TXCLK_REFGEN1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLK_REFGEN1_RD_MASK, "TXANA_FFE_MSG_TXCLK_REFGEN1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLK_SENSE0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLK_SENSE0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLK_SENSE0_RD_MASK, "TXANA_FFE_MSG_TXCLK_SENSE0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKMUX_CTUNE0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKMUX_CTUNE0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKMUX_CTUNE0_RD_MASK, "TXANA_FFE_MSG_TXCLKMUX_CTUNE0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKMUX_THR0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKMUX_THR0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKMUX_THR0_RD_MASK, "TXANA_FFE_MSG_TXCLKMUX_THR0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST1_CTUNE0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE0_RD_MASK, "TXANA_FFE_MSG_TXCLKST1_CTUNE0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST1_CTUNE1_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE1_RD_MASK, "TXANA_FFE_MSG_TXCLKST1_CTUNE1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST1_CTUNE2_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE2_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST1_CTUNE2_RD_MASK, "TXANA_FFE_MSG_TXCLKST1_CTUNE2_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE0_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE1_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE1_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_THR0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_THR0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_THR0_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_THR0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE2_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE2_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE2_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE2_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE3_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE3_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE3_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE3_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_THR1_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_THR1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_THR1_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_THR1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE4_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE4_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE4_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE4_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE5_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE5_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE5_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE5_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_THR2_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_THR2_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_THR2_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_THR2_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE6_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE6_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE6_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE6_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_CTUNE7_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE7_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_CTUNE7_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_CTUNE7_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKST2_THR3_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKST2_THR3_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKST2_THR3_RD_MASK, "TXANA_FFE_MSG_TXCLKST2_THR3_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCOMP_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL0_RD_MASK, "TXANA_FFE_MSG_TXCOMP_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCOMP_CTRL1_OFFSET, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL1_RD_MASK, "TXANA_FFE_MSG_TXCOMP_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCOMP_CTRL2_OFFSET, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL2_DEFAULT, \
                                    TXANA_FFE_MSG_TXCOMP_CTRL2_RD_MASK, "TXANA_FFE_MSG_TXCOMP_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXDRV_SENSE0_OFFSET, \
                                    TXANA_FFE_MSG_TXDRV_SENSE0_DEFAULT, \
                                    TXANA_FFE_MSG_TXDRV_SENSE0_RD_MASK, "TXANA_FFE_MSG_TXDRV_SENSE0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXDRV_SENSE1_OFFSET, \
                                    TXANA_FFE_MSG_TXDRV_SENSE1_DEFAULT, \
                                    TXANA_FFE_MSG_TXDRV_SENSE1_RD_MASK, "TXANA_FFE_MSG_TXDRV_SENSE1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXDRV_SENSE2_OFFSET, \
                                    TXANA_FFE_MSG_TXDRV_SENSE2_DEFAULT, \
                                    TXANA_FFE_MSG_TXDRV_SENSE2_RD_MASK, "TXANA_FFE_MSG_TXDRV_SENSE2_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXREG_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TXREG_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TXREG_CTRL0_RD_MASK, "TXANA_FFE_MSG_TXREG_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_MISC_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TX_MISC_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_MISC_CTRL0_RD_MASK, "TXANA_FFE_MSG_TX_MISC_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_DFX0_OFFSET, \
                                    TXANA_FFE_MSG_TX_DFX0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_DFX0_RD_MASK, "TXANA_FFE_MSG_TX_DFX0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_DFX1_OFFSET, \
                                    TXANA_FFE_MSG_TX_DFX1_DEFAULT, \
                                    TXANA_FFE_MSG_TX_DFX1_RD_MASK, "TXANA_FFE_MSG_TX_DFX1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS0_OFFSET, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS0_RD_MASK, "TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS1_OFFSET, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS1_DEFAULT, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS1_RD_MASK, "TXANA_FFE_MSG_TX_BIAS_TRIM_PMOS1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS0_OFFSET, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS0_RD_MASK, "TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS1_OFFSET, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS1_DEFAULT, \
                                    TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS1_RD_MASK, "TXANA_FFE_MSG_TX_BIAS_TRIM_NMOS1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_BIAS_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TX_BIAS_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_BIAS_CTRL0_RD_MASK, "TXANA_FFE_MSG_TX_BIAS_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKDIV_CTRL0_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKDIV_CTRL0_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKDIV_CTRL0_RD_MASK, "TXANA_FFE_MSG_TXCLKDIV_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TXCLKDIV_CTRL1_OFFSET, \
                                    TXANA_FFE_MSG_TXCLKDIV_CTRL1_DEFAULT, \
                                    TXANA_FFE_MSG_TXCLKDIV_CTRL1_RD_MASK, "TXANA_FFE_MSG_TXCLKDIV_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+TXANA_FFE_MSG_TX_SPARE0_OFFSET, \
                                    TXANA_FFE_MSG_TX_SPARE0_DEFAULT, \
                                    TXANA_FFE_MSG_TX_SPARE0_RD_MASK, "TXANA_FFE_MSG_TX_SPARE0_OFFSET");

    }

}
