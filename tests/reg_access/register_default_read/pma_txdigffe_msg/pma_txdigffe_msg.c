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
    DLNK_JESD0_PHY_PMA0_TXDIGFFE_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_TXDIGFFE_Q0_BASE, DLNK_JESD0_PHY_PMA0_TXDIGFFE_Q1_BASE, DLNK_JESD0_PHY_PMA0_TXDIGFFE_Q2_BASE, DLNK_JESD0_PHY_PMA0_TXDIGFFE_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_TXDIGFFE_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_TXDIGFFE_Q0_BASE, DLNK_JESD1_PHY_PMA0_TXDIGFFE_Q1_BASE, DLNK_JESD1_PHY_PMA0_TXDIGFFE_Q2_BASE, DLNK_JESD1_PHY_PMA0_TXDIGFFE_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_TXDIGFFE_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_TXDIGFFE_Q0_BASE, DLNK_JESD2_PHY_PMA0_TXDIGFFE_Q1_BASE, DLNK_JESD2_PHY_PMA0_TXDIGFFE_Q2_BASE, DLNK_JESD2_PHY_PMA0_TXDIGFFE_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_TXDIGFFE_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_TXDIGFFE_Q0_BASE, DLNK_JESD3_PHY_PMA0_TXDIGFFE_Q1_BASE, DLNK_JESD3_PHY_PMA0_TXDIGFFE_Q2_BASE, DLNK_JESD3_PHY_PMA0_TXDIGFFE_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RST_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RST_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RST_RD_MASK, "PMA_TXDIGFFE_MSG_RST_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMOD_OVR_STAT0_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMOD_OVR_STAT0_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMOD_OVR_STAT0_RD_MASK, "PMA_TXDIGFFE_MSG_CMOD_OVR_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMOD_OVR_STAT1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMOD_OVR_STAT1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMOD_OVR_STAT1_RD_MASK, "PMA_TXDIGFFE_MSG_CMOD_OVR_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_FFE1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_FFE1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_FFE1_RD_MASK, "PMA_TXDIGFFE_MSG_FFE1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_FFE2_OFFSET, \
                                    PMA_TXDIGFFE_MSG_FFE2_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_FFE2_RD_MASK, "PMA_TXDIGFFE_MSG_FFE2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_FFE3_OFFSET, \
                                    PMA_TXDIGFFE_MSG_FFE3_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_FFE3_RD_MASK, "PMA_TXDIGFFE_MSG_FFE3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_FFE4_OFFSET, \
                                    PMA_TXDIGFFE_MSG_FFE4_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_FFE4_RD_MASK, "PMA_TXDIGFFE_MSG_FFE4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_HW_ASSIST1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST1_RD_MASK, "PMA_TXDIGFFE_MSG_HW_ASSIST1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_HW_ASSIST2_OFFSET, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST2_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST2_RD_MASK, "PMA_TXDIGFFE_MSG_HW_ASSIST2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_HW_ASSIST3_OFFSET, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST3_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST3_RD_MASK, "PMA_TXDIGFFE_MSG_HW_ASSIST3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_HW_ASSIST4_OFFSET, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST4_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_HW_ASSIST4_RD_MASK, "PMA_TXDIGFFE_MSG_HW_ASSIST4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL0_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL0_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL0_RD_MASK, "PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL1_RD_MASK, "PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL2_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL2_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL2_RD_MASK, "PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_STAT_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_STAT_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_STAT_RD_MASK, "PMA_TXDIGFFE_MSG_CMPOUT_CALASSIST_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_DFX2_OFFSET, \
                                    PMA_TXDIGFFE_MSG_DFX2_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_DFX2_RD_MASK, "PMA_TXDIGFFE_MSG_DFX2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_OFFSET, \
                                    PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_RD_MASK, "PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_RO_OFFSET, \
                                    PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_RO_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_RO_RD_MASK, "PMA_TXDIGFFE_MSG_TXDETECTRX_CTRL_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_CTRL_OUT_OFFSET, \
                                    PMA_TXDIGFFE_MSG_CTRL_OUT_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_CTRL_OUT_RD_MASK, "PMA_TXDIGFFE_MSG_CTRL_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT0_OFFSET, \
                                    PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT0_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT0_RD_MASK, "PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT1_RD_MASK, "PMA_TXDIGFFE_MSG_ADD_RSLT_OVR_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RW_SPARE_0_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_0_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_0_RD_MASK, "PMA_TXDIGFFE_MSG_RW_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RW_SPARE_1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_1_RD_MASK, "PMA_TXDIGFFE_MSG_RW_SPARE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RW_SPARE_2_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_2_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_2_RD_MASK, "PMA_TXDIGFFE_MSG_RW_SPARE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RW_SPARE_3_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_3_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RW_SPARE_3_RD_MASK, "PMA_TXDIGFFE_MSG_RW_SPARE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RO_SPARE_0_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RO_SPARE_0_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RO_SPARE_0_RD_MASK, "PMA_TXDIGFFE_MSG_RO_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXDIGFFE_MSG_RO_SPARE_1_OFFSET, \
                                    PMA_TXDIGFFE_MSG_RO_SPARE_1_DEFAULT, \
                                    PMA_TXDIGFFE_MSG_RO_SPARE_1_RD_MASK, "PMA_TXDIGFFE_MSG_RO_SPARE_1_OFFSET");

    }

}
