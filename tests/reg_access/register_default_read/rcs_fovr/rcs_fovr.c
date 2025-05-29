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
    RCS_FOVR_METER0_BASE, RCS_FOVR_METER1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS0_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS0_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS0_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS0_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS1_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS1_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS1_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS1_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS2_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS2_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS2_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS2_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS3_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS3_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS3_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS3_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS4_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS4_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS4_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS4_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS5_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS5_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS5_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS5_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS6_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS6_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS6_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS6_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS7_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS7_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS7_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS7_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS8_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS8_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS8_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS8_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS9_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS9_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS9_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS9_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS10_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS10_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS10_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS10_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS11_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS11_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS11_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS11_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS12_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS12_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS12_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS12_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS13_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS13_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS13_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS13_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS14_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS14_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS14_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS14_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS15_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS15_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS15_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS15_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS16_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS16_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS16_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS16_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS17_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS17_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS17_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS17_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS18_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS18_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS18_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS18_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS19_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS19_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS19_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS19_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS20_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS20_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS20_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS20_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS21_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS21_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS21_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS21_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS22_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS22_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS22_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS22_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS23_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS23_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS23_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS23_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS24_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS24_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS24_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS24_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS25_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS25_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS25_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS25_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS26_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS26_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS26_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS26_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS27_CNTER_CTL_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_CTL_RD_MASK, "RCS_FOVR_ALARMS27_CNTER_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALARMS27_CNTER_RSLT_OFFSET, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_DEFAULT, \
                                    RCS_FOVR_ALARMS_CNTER_RSLT_RD_MASK, "RCS_FOVR_ALARMS27_CNTER_RSLT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_ALL_ALARMS_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_ALL_ALARMS_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_ALL_ALARMS_RD_MASK, "RCS_FOVR_ALL_ALARMS_ALL_ALARMS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_FOVR_OVERLOAD_DIS_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_FOVR_OVERLOAD_DIS_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_FOVR_OVERLOAD_DIS_RD_MASK, "RCS_FOVR_ALL_ALARMS_FOVR_OVERLOAD_DIS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_GPIOSEL_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_GPIOSEL_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_GPIOSEL_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_GPIOSEL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_MODE_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_MODE_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_MODE_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_MODE_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_STS_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_STS_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_STS_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_SET_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_SET_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_SET_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_SET_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_CLR_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_CLR_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_CLR_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_EN_OFFSET, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_EN_DEFAULT, \
                                    RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_EN_RD_MASK, "RCS_FOVR_ALL_ALARMS_TX_ALARM_IN_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET0_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET0_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET1_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET1_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET2_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET2_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET3_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET3_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET4_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET4_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET5_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET5_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET6_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET6_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET7_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET7_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET8_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET8_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET9_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET9_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET10_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET10_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET11_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET11_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET12_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET12_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET13_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET13_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET14_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET14_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET15_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET15_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET16_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET16_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET17_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET17_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET18_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET18_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET19_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET19_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET20_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET20_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET21_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET21_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET22_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET22_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET23_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET23_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET24_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET24_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET25_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET25_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET26_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET26_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET27_GPIO_SET_EN_OFFSET, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_GPIO_SET_EN_RD_MASK, "RCS_FOVR_GPIO_SET27_GPIO_SET_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET_CTL_FOVR_GPIO_SET_CTL_OFFSET, \
                                    RCS_FOVR_GPIO_SET_CTL_FOVR_GPIO_SET_CTL_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_CTL_FOVR_GPIO_SET_CTL_RD_MASK, "RCS_FOVR_GPIO_SET_CTL_FOVR_GPIO_SET_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET_CTL_OVERLOAD_GPIO_SET_CTL_OFFSET, \
                                    RCS_FOVR_GPIO_SET_CTL_OVERLOAD_GPIO_SET_CTL_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_CTL_OVERLOAD_GPIO_SET_CTL_RD_MASK, "RCS_FOVR_GPIO_SET_CTL_OVERLOAD_GPIO_SET_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_FOVR_GPIO_SET_CTL_TXALARM_GPIO_SET_CTL_OFFSET, \
                                    RCS_FOVR_GPIO_SET_CTL_TXALARM_GPIO_SET_CTL_DEFAULT, \
                                    RCS_FOVR_GPIO_SET_CTL_TXALARM_GPIO_SET_CTL_RD_MASK, "RCS_FOVR_GPIO_SET_CTL_TXALARM_GPIO_SET_CTL_OFFSET");

    }

}
