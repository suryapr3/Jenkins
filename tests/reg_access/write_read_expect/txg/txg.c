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
    TRX_SYS0_TXG0_BASE, TRX_SYS0_TXG1_BASE, TRX_SYS1_TXG0_BASE, TRX_SYS1_TXG1_BASE, TRX_SYS2_TXG0_BASE,
    TRX_SYS2_TXG1_BASE, TRX_SYS3_TXG0_BASE, TRX_SYS3_TXG1_BASE, TRX_SYS4_TXG0_BASE, TRX_SYS4_TXG1_BASE,
    TRX_SYS5_TXG0_BASE, TRX_SYS5_TXG1_BASE, TRX_SYS6_TXG0_BASE, TRX_SYS6_TXG1_BASE, TRX_SYS7_TXG0_BASE,
    TRX_SYS7_TXG1_BASE
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
			write_read_expect_18a(base_address[i]+TXG_AC_FAST_GAIN_I_OFFSET, \
                                    TXG_AC_FAST_GAIN_I_DEFAULT, write_data, expected_data, \
                                    TXG_AC_FAST_GAIN_I_RD_MASK, TXG_AC_FAST_GAIN_I_WR_MASK, \
                                    "TXG_AC_FAST_GAIN_I_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_AC_FAST_GAIN_Q_OFFSET, \
                                    TXG_AC_FAST_GAIN_Q_DEFAULT, write_data, expected_data, \
                                    TXG_AC_FAST_GAIN_Q_RD_MASK, TXG_AC_FAST_GAIN_Q_WR_MASK, \
                                    "TXG_AC_FAST_GAIN_Q_OFFSET");
									
            write_read_expect_18a(base_address[i]+TXG_STEP_SIZE_SHDW_OFFSET, \
                                    TXG_STEP_SIZE_SHDW_DEFAULT, write_data, expected_data, \
                                    TXG_STEP_SIZE_SHDW_RD_MASK, TXG_STEP_SIZE_SHDW_WR_MASK, \
                                    "TXG_STEP_SIZE_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_GAIN_RAMP_VAL_SHDW_OFFSET, \
                                    TXG_GAIN_RAMP_VAL_SHDW_DEFAULT, write_data, expected_data, \
                                    TXG_GAIN_RAMP_VAL_SHDW_RD_MASK, TXG_GAIN_RAMP_VAL_SHDW_WR_MASK, \
                                    "TXG_GAIN_RAMP_VAL_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_PHASE_VAL_SHDW_OFFSET, \
                                    TXG_PHASE_VAL_SHDW_DEFAULT, write_data, expected_data, \
                                    TXG_PHASE_VAL_SHDW_RD_MASK, TXG_PHASE_VAL_SHDW_WR_MASK, \
                                    "TXG_PHASE_VAL_SHDW_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_STEP_SIZE_LIVE_OFFSET, \
                                    TXG_STEP_SIZE_LIVE_DEFAULT, write_data, expected_data, \
                                    TXG_STEP_SIZE_LIVE_RD_MASK, TXG_STEP_SIZE_LIVE_WR_MASK, \
                                    "TXG_STEP_SIZE_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_GAIN_RAMP_VAL_LIVE_OFFSET, \
                                    TXG_GAIN_RAMP_VAL_LIVE_DEFAULT, write_data, expected_data, \
                                    TXG_GAIN_RAMP_VAL_LIVE_RD_MASK, TXG_GAIN_RAMP_VAL_LIVE_WR_MASK, \
                                    "TXG_GAIN_RAMP_VAL_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_PHASE_VAL_LIVE_OFFSET, \
                                    TXG_PHASE_VAL_LIVE_DEFAULT, write_data, expected_data, \
                                    TXG_PHASE_VAL_LIVE_RD_MASK, TXG_PHASE_VAL_LIVE_WR_MASK, \
                                    "TXG_PHASE_VAL_LIVE_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_SCRATCH_OFFSET, \
                                    TXG_SCRATCH_DEFAULT, write_data, expected_data, \
                                    TXG_SCRATCH_RD_MASK, TXG_SCRATCH_WR_MASK, \
                                    "TXG_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_BFN_UPDATE_OFFSET, \
                                    TXG_BFN_UPDATE_DEFAULT, write_data, expected_data, \
                                    TXG_BFN_UPDATE_RD_MASK, TXG_BFN_UPDATE_WR_MASK, \
                                    "TXG_BFN_UPDATE_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXG_SEL_OFFSET, \
                                    TXG_SEL_DEFAULT, write_data, expected_data, \
                                    TXG_SEL_RD_MASK, TXG_SEL_WR_MASK, \
                                    "TXG_SEL_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXG_SWITCH_OFFSET, \
                                    TXG_SWITCH_DEFAULT, write_data, expected_data, \
                                    TXG_SWITCH_RD_MASK, TXG_SWITCH_WR_MASK, \
                                    "TXG_SWITCH_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_TMR_CFG_OFFSET, \
                                    TXG_TMR_CFG_DEFAULT, write_data, expected_data, \
                                    TXG_TMR_CFG_RD_MASK, TXG_TMR_CFG_WR_MASK, \
                                    "TXG_TMR_CFG_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXG_TMR_ERR_OFFSET, \
                                    TXG_TMR_ERR_DEFAULT, write_data, expected_data, \
                                    TXG_TMR_ERR_RD_MASK, TXG_TMR_ERR_WR_MASK, \
                                    "TXG_TMR_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_BYP_OFFSET, \
                                    TXG_BYP_DEFAULT, write_data, expected_data, \
                                    TXG_BYP_RD_MASK, TXG_BYP_WR_MASK, \
                                    "TXG_BYP_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXG_TXE_RAMP_VAL_OFFSET, \
                                    TXG_TXE_RAMP_VAL_DEFAULT, write_data, expected_data, \
                                    TXG_TXE_RAMP_VAL_RD_MASK, TXG_TXE_RAMP_VAL_WR_MASK, \
                                    "TXG_TXE_RAMP_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_TX_SM_STATE_OFFSET, \
                                    TXG_TX_SM_STATE_DEFAULT, write_data, expected_data, \
                                    TXG_TX_SM_STATE_RD_MASK, TXG_TX_SM_STATE_WR_MASK, \
                                    "TXG_TX_SM_STATE_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_GAIN_SEL_OFFSET, \
                                    TXG_GAIN_SEL_DEFAULT, write_data, expected_data, \
                                    TXG_GAIN_SEL_RD_MASK, TXG_GAIN_SEL_WR_MASK, \
                                    "TXG_GAIN_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_INT_STAT_OFFSET, \
                                    TXG_INT_STAT_DEFAULT, write_data, expected_data, \
                                    TXG_INT_STAT_RD_MASK, TXG_INT_STAT_WR_MASK, \
                                    "TXG_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_INT_HIGH_EN_OFFSET, \
                                    TXG_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    TXG_INT_HIGH_EN_RD_MASK, TXG_INT_HIGH_EN_WR_MASK, \
                                    "TXG_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_INT_LOW_EN_OFFSET, \
                                    TXG_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    TXG_INT_LOW_EN_RD_MASK, TXG_INT_LOW_EN_WR_MASK, \
                                    "TXG_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_INT_CLR_OFFSET, \
                                    TXG_INT_CLR_DEFAULT, write_data, expected_data, \
                                    TXG_INT_CLR_RD_MASK, TXG_INT_CLR_WR_MASK, \
                                    "TXG_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_INT_FORCE_OFFSET, \
                                    TXG_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    TXG_INT_FORCE_RD_MASK, TXG_INT_FORCE_WR_MASK, \
                                    "TXG_INT_FORCE_OFFSET");

            

            write_read_expect_18a(base_address[i]+TXG_AC_FAST_GAIN_EN_OFFSET, \
                                    TXG_AC_FAST_GAIN_EN_DEFAULT, write_data, expected_data, \
                                    TXG_AC_FAST_GAIN_EN_RD_MASK, TXG_AC_FAST_GAIN_EN_WR_MASK, \
                                    "TXG_AC_FAST_GAIN_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_STATIC_HOLD_MASK_OFFSET, \
                                    TXG_STATIC_HOLD_MASK_DEFAULT, write_data, expected_data, \
                                    TXG_STATIC_HOLD_MASK_RD_MASK, TXG_STATIC_HOLD_MASK_WR_MASK, \
                                    "TXG_STATIC_HOLD_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_TXE_DELAY_OFFSET, \
                                    TXG_TXE_DELAY_DEFAULT, write_data, expected_data, \
                                    TXG_TXE_DELAY_RD_MASK, TXG_TXE_DELAY_WR_MASK, \
                                    "TXG_TXE_DELAY_OFFSET");

            write_read_expect_18a(base_address[i]+TXG_TXE_DELTA_DELAY_OFFSET, \
                                    TXG_TXE_DELTA_DELAY_DEFAULT, write_data, expected_data, \
                                    TXG_TXE_DELTA_DELAY_RD_MASK, TXG_TXE_DELTA_DELAY_WR_MASK, \
                                    "TXG_TXE_DELTA_DELAY_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXG_APB_BRDG_STAT_OFFSET, \
                                    TXG_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    TXG_APB_BRDG_STAT_RD_MASK, TXG_APB_BRDG_STAT_WR_MASK, \
                                    "TXG_APB_BRDG_STAT_OFFSET");

        }

    }

}
