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
    RCS_I3CM0_MIPI_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
		
        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEVICE_CTRL_OFFSET, \
                                    MIPI_I3C_DEVICE_CTRL_DEFAULT, \
                                    MIPI_I3C_DEVICE_CTRL_RD_MASK, "MIPI_I3C_DEVICE_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEVICE_ADDR_OFFSET, \
                                    MIPI_I3C_DEVICE_ADDR_DEFAULT, \
                                    MIPI_I3C_DEVICE_ADDR_RD_MASK, "MIPI_I3C_DEVICE_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_HW_CAPABILITY_OFFSET, \
                                    MIPI_I3C_HW_CAPABILITY_DEFAULT, \
                                    MIPI_I3C_HW_CAPABILITY_RD_MASK, "MIPI_I3C_HW_CAPABILITY_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_CMD_QUE_PORT_XXX_OFFSET, \
                                    MIPI_I3C_CMD_QUE_PORT_XXX_DEFAULT, \
                                    MIPI_I3C_CMD_QUE_PORT_XXX_RD_MASK, "MIPI_I3C_CMD_QUE_PORT_XXX_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_RSP_QUE_PORT_OFFSET, \
                                    MIPI_I3C_RSP_QUE_PORT_DEFAULT, \
                                    MIPI_I3C_RSP_QUE_PORT_RD_MASK, "MIPI_I3C_RSP_QUE_PORT_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_RX_TX_DATA_PORT_OFFSET, \
                                    MIPI_I3C_RX_TX_DATA_PORT_DEFAULT, \
                                    MIPI_I3C_RX_TX_DATA_PORT_RD_MASK, "MIPI_I3C_RX_TX_DATA_PORT_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_IBI_DATA_STAT_OFFSET, \
                                    MIPI_I3C_IBI_DATA_STAT_DEFAULT, \
                                    MIPI_I3C_IBI_DATA_STAT_RD_MASK, "MIPI_I3C_IBI_DATA_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_QUE_THLD_CTRL_OFFSET, \
                                    MIPI_I3C_QUE_THLD_CTRL_DEFAULT, \
                                    MIPI_I3C_QUE_THLD_CTRL_RD_MASK, "MIPI_I3C_QUE_THLD_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DATA_BUFF_THLD_CTRL_OFFSET, \
                                    MIPI_I3C_DATA_BUFF_THLD_CTRL_DEFAULT, \
                                    MIPI_I3C_DATA_BUFF_THLD_CTRL_RD_MASK, "MIPI_I3C_DATA_BUFF_THLD_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_IBI_QUE_CTRL_OFFSET, \
                                    MIPI_I3C_IBI_QUE_CTRL_DEFAULT, \
                                    MIPI_I3C_IBI_QUE_CTRL_RD_MASK, "MIPI_I3C_IBI_QUE_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_RST_CTRL_OFFSET, \
                                    MIPI_I3C_RST_CTRL_DEFAULT, \
                                    MIPI_I3C_RST_CTRL_RD_MASK, "MIPI_I3C_RST_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SLV_EVENT_STAT_OFFSET, \
                                    MIPI_I3C_SLV_EVENT_STAT_DEFAULT, \
                                    MIPI_I3C_SLV_EVENT_STAT_RD_MASK, "MIPI_I3C_SLV_EVENT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_INTR_STAT_OFFSET, \
                                    MIPI_I3C_INTR_STAT_DEFAULT, \
                                    MIPI_I3C_INTR_STAT_RD_MASK, "MIPI_I3C_INTR_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_INTR_STAT_EN_OFFSET, \
                                    MIPI_I3C_INTR_STAT_EN_DEFAULT, \
                                    MIPI_I3C_INTR_STAT_EN_RD_MASK, "MIPI_I3C_INTR_STAT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_INTR_SIGNAL_EN_OFFSET, \
                                    MIPI_I3C_INTR_SIGNAL_EN_DEFAULT, \
                                    MIPI_I3C_INTR_SIGNAL_EN_RD_MASK, "MIPI_I3C_INTR_SIGNAL_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_INTR_FORCE_OFFSET, \
                                    MIPI_I3C_INTR_FORCE_DEFAULT, \
                                    MIPI_I3C_INTR_FORCE_RD_MASK, "MIPI_I3C_INTR_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_QUE_STAT_LVL_OFFSET, \
                                    MIPI_I3C_QUE_STAT_LVL_DEFAULT, \
                                    MIPI_I3C_QUE_STAT_LVL_RD_MASK, "MIPI_I3C_QUE_STAT_LVL_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DATA_BUFF_STAT_LVL_OFFSET, \
                                    MIPI_I3C_DATA_BUFF_STAT_LVL_DEFAULT, \
                                    MIPI_I3C_DATA_BUFF_STAT_LVL_RD_MASK, "MIPI_I3C_DATA_BUFF_STAT_LVL_OFFSET");

//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+MIPI_I3C_PRESENT_STATE_OFFSET, \
                                    MIPI_I3C_PRESENT_STATE_DEFAULT, \
                                    MIPI_I3C_PRESENT_STATE_RD_MASK, "MIPI_I3C_PRESENT_STATE_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEVICE_ADDR_TBL_PTR_OFFSET, \
                                    MIPI_I3C_DEVICE_ADDR_TBL_PTR_DEFAULT, \
                                    MIPI_I3C_DEVICE_ADDR_TBL_PTR_RD_MASK, "MIPI_I3C_DEVICE_ADDR_TBL_PTR_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL_PTR_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL_PTR_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL_PTR_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL_PTR_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_VENDOR_SPECIFIC_PTR_OFFSET, \
                                    MIPI_I3C_VENDOR_SPECIFIC_PTR_DEFAULT, \
                                    MIPI_I3C_VENDOR_SPECIFIC_PTR_RD_MASK, "MIPI_I3C_VENDOR_SPECIFIC_PTR_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEVICE_CTRL_EXTENDED_OFFSET, \
                                    MIPI_I3C_DEVICE_CTRL_EXTENDED_DEFAULT, \
                                    MIPI_I3C_DEVICE_CTRL_EXTENDED_RD_MASK, "MIPI_I3C_DEVICE_CTRL_EXTENDED_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_I3C_OD_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_I3C_OD_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_I3C_OD_TIMING_RD_MASK, "MIPI_I3C_SCL_I3C_OD_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_I3C_PP_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_I3C_PP_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_I3C_PP_TIMING_RD_MASK, "MIPI_I3C_SCL_I3C_PP_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_I2C_FM_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_I2C_FM_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_I2C_FM_TIMING_RD_MASK, "MIPI_I3C_SCL_I2C_FM_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_I2C_FMP_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_I2C_FMP_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_I2C_FMP_TIMING_RD_MASK, "MIPI_I3C_SCL_I2C_FMP_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_EXT_LCNT_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_EXT_LCNT_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_EXT_LCNT_TIMING_RD_MASK, "MIPI_I3C_SCL_EXT_LCNT_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SCL_EXT_TERMN_LCNT_TIMING_OFFSET, \
                                    MIPI_I3C_SCL_EXT_TERMN_LCNT_TIMING_DEFAULT, \
                                    MIPI_I3C_SCL_EXT_TERMN_LCNT_TIMING_RD_MASK, "MIPI_I3C_SCL_EXT_TERMN_LCNT_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_SDA_HOLD_DLY_TIMING_OFFSET, \
                                    MIPI_I3C_SDA_HOLD_DLY_TIMING_DEFAULT, \
                                    MIPI_I3C_SDA_HOLD_DLY_TIMING_RD_MASK, "MIPI_I3C_SDA_HOLD_DLY_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_BUS_FREE_AVAIL_TIMING_OFFSET, \
                                    MIPI_I3C_BUS_FREE_AVAIL_TIMING_DEFAULT, \
                                    MIPI_I3C_BUS_FREE_AVAIL_TIMING_RD_MASK, "MIPI_I3C_BUS_FREE_AVAIL_TIMING_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_VER_ID_OFFSET, \
                                    MIPI_I3C_VER_ID_DEFAULT, \
                                    MIPI_I3C_VER_ID_RD_MASK, "MIPI_I3C_VER_ID_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_VER_TYPE_OFFSET, \
                                    MIPI_I3C_VER_TYPE_DEFAULT, \
                                    MIPI_I3C_VER_TYPE_RD_MASK, "MIPI_I3C_VER_TYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_QUE_SIZE_CAPABILITY_OFFSET, \
                                    MIPI_I3C_QUE_SIZE_CAPABILITY_DEFAULT, \
                                    MIPI_I3C_QUE_SIZE_CAPABILITY_RD_MASK, "MIPI_I3C_QUE_SIZE_CAPABILITY_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL1_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL1_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL1_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL1_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL1_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL1_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL1_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL1_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL1_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL2_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL2_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL2_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL2_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL2_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL2_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL2_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL2_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL2_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL3_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL3_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL3_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL3_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL3_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL3_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL3_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL3_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL3_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL4_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL4_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL4_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL4_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL4_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL4_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL4_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL4_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL4_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL5_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL5_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL5_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL5_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL5_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL5_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL5_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL5_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL5_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL6_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL6_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL6_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL6_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL6_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL6_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL6_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL6_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL6_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL7_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL7_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL7_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL7_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL7_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL7_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL7_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL7_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL7_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL8_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC1_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL8_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL8_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC2_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL8_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL8_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC3_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL8_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_CHAR_TBL8_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_CHAR_TBL8_LOC4_RD_MASK, "MIPI_I3C_DEV_CHAR_TBL8_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC1_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC1_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC1_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC1_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC2_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC2_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC2_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC2_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC3_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC3_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC3_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC3_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC4_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC4_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC4_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC4_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC5_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC5_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC5_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC5_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC6_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC6_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC6_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC6_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC7_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC7_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC7_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC7_OFFSET");

        read_reg_expect_18a(base_address[i]+MIPI_I3C_DEV_ADDR_TBL_LOC8_OFFSET, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC8_DEFAULT, \
                                    MIPI_I3C_DEV_ADDR_TBL_LOC8_RD_MASK, "MIPI_I3C_DEV_ADDR_TBL_LOC8_OFFSET");

    }

}
