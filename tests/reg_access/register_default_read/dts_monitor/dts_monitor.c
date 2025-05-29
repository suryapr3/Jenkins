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
    SYSCON_DTS_MONITOR_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+DTS_EN_OFFSET, \
                                    DTS_EN_DEFAULT, \
                                    DTS_EN_RD_MASK, "DTS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_EN_OFFSET, \
                                    DTS_MON_EN_DEFAULT, \
                                    DTS_MON_EN_RD_MASK, "DTS_MON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_TIMEOUT_CYCLE_OFFSET, \
                                    DTS_MON_TIMEOUT_CYCLE_DEFAULT, \
                                    DTS_MON_TIMEOUT_CYCLE_RD_MASK, "DTS_MON_TIMEOUT_CYCLE_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_EN_OFFSET, \
                                    DTS_ATSA_EN_DEFAULT, \
                                    DTS_ATSA_EN_RD_MASK, "DTS_ATSA_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_CAPT_OFFSET, \
                                    DTS_ATSA_ADC_CAPT_DEFAULT, \
                                    DTS_ATSA_ADC_CAPT_RD_MASK, "DTS_ATSA_ADC_CAPT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_CAPT_OFFSET, \
                                    DTS_ATSA_DAC_CAPT_DEFAULT, \
                                    DTS_ATSA_DAC_CAPT_RD_MASK, "DTS_ATSA_DAC_CAPT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_CAPT_OFFSET, \
                                    DTS_ATSA_AGC_CAPT_DEFAULT, \
                                    DTS_ATSA_AGC_CAPT_RD_MASK, "DTS_ATSA_AGC_CAPT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_FAULT_STAT_OFFSET, \
                                    DTS_ATSA_FAULT_STAT_DEFAULT, \
                                    DTS_ATSA_FAULT_STAT_RD_MASK, "DTS_ATSA_FAULT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_INT_STAT_OFFSET, \
                                    DTS_MON_INT_STAT_DEFAULT, \
                                    DTS_MON_INT_STAT_RD_MASK, "DTS_MON_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_INT_EN_OFFSET, \
                                    DTS_MON_INT_EN_DEFAULT, \
                                    DTS_MON_INT_EN_RD_MASK, "DTS_MON_INT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_INT_CLR_OFFSET, \
                                    DTS_MON_INT_CLR_DEFAULT, \
                                    DTS_MON_INT_CLR_RD_MASK, "DTS_MON_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_INT_FORCE_OFFSET, \
                                    DTS_MON_INT_FORCE_DEFAULT, \
                                    DTS_MON_INT_FORCE_RD_MASK, "DTS_MON_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_MON_INT_MASKED_STAT_OFFSET, \
                                    DTS_MON_INT_MASKED_STAT_DEFAULT, \
                                    DTS_MON_INT_MASKED_STAT_RD_MASK, "DTS_MON_INT_MASKED_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL0_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL1_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL2_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL3_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL4_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL5_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL6_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_UL7_OFFSET, \
                                    DTS_ATSA_ADC_UL_DEFAULT, \
                                    DTS_ATSA_ADC_UL_RD_MASK, "DTS_ATSA_ADC_UL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL0_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL1_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL2_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL3_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL4_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL5_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL6_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_ADC_LL7_OFFSET, \
                                    DTS_ATSA_ADC_LL_DEFAULT, \
                                    DTS_ATSA_ADC_LL_RD_MASK, "DTS_ATSA_ADC_LL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL0_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL1_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL2_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL3_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL4_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL5_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL6_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_UL7_OFFSET, \
                                    DTS_ATSA_DAC_UL_DEFAULT, \
                                    DTS_ATSA_DAC_UL_RD_MASK, "DTS_ATSA_DAC_UL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL0_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL1_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL2_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL3_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL4_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL5_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL6_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_DAC_LL7_OFFSET, \
                                    DTS_ATSA_DAC_LL_DEFAULT, \
                                    DTS_ATSA_DAC_LL_RD_MASK, "DTS_ATSA_DAC_LL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL0_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL1_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL2_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL3_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL4_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL5_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL6_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_UL7_OFFSET, \
                                    DTS_ATSA_AGC_UL_DEFAULT, \
                                    DTS_ATSA_AGC_UL_RD_MASK, "DTS_ATSA_AGC_UL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL0_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL1_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL2_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL3_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL4_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL5_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL6_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_AGC_LL7_OFFSET, \
                                    DTS_ATSA_AGC_LL_DEFAULT, \
                                    DTS_ATSA_AGC_LL_RD_MASK, "DTS_ATSA_AGC_LL7_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR0_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR0_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR1_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR1_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR2_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR2_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR3_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR3_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR4_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR4_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR5_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR5_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR6_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR6_OFFSET");

        read_reg_expect_18a(base_address[i]+DTS_ATSA_SENSOR7_OFFSET, \
                                    DTS_ATSA_SENSOR_DEFAULT, \
                                    DTS_ATSA_SENSOR_RD_MASK, "DTS_ATSA_SENSOR7_OFFSET");

    }

}
