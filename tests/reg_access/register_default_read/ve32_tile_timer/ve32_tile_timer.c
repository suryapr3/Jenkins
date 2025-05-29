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
    VEXABC0_TM_VE32_TILE_TIMER_BASE, VEXABC1_TM_VE32_TILE_TIMER_BASE, VEXABC2_TM_VE32_TILE_TIMER_BASE, VEXABC3_TM_VE32_TILE_TIMER_BASE, VEXABC4_TM_VE32_TILE_TIMER_BASE,
    VEXABC5_TM_VE32_TILE_TIMER_BASE, VEXABC6_TM_VE32_TILE_TIMER_BASE, VEXABC7_TM_VE32_TILE_TIMER_BASE, VEXABC8_TM_VE32_TILE_TIMER_BASE, VEXABC9_TM_VE32_TILE_TIMER_BASE,
    VEXABC10_TM_VE32_TILE_TIMER_BASE, VEXABC11_TM_VE32_TILE_TIMER_BASE, VEXABC12_TM_VE32_TILE_TIMER_BASE, VEXABC13_TM_VE32_TILE_TIMER_BASE, VEXABC14_TM_VE32_TILE_TIMER_BASE,
    VEXABC15_TM_VE32_TILE_TIMER_BASE, VEXABC16_TM_VE32_TILE_TIMER_BASE, VEXABC17_TM_VE32_TILE_TIMER_BASE, VEXABC18_TM_VE32_TILE_TIMER_BASE, VEXABC19_TM_VE32_TILE_TIMER_BASE,
    VEXABC20_TM_VE32_TILE_TIMER_BASE, VEXABC21_TM_VE32_TILE_TIMER_BASE, VEXABC22_TM_VE32_TILE_TIMER_BASE, VEXABC23_TM_VE32_TILE_TIMER_BASE, VEXABC24_TM_VE32_TILE_TIMER_BASE,
    VEXABC25_TM_VE32_TILE_TIMER_BASE, VEXABC26_TM_VE32_TILE_TIMER_BASE, VEXABC27_TM_VE32_TILE_TIMER_BASE, VEXABC28_TM_VE32_TILE_TIMER_BASE, VEXABC29_TM_VE32_TILE_TIMER_BASE,
    VEXABC30_TM_VE32_TILE_TIMER_BASE, VEXABC31_TM_VE32_TILE_TIMER_BASE, VEXABC32_TM_VE32_TILE_TIMER_BASE, VEXABC33_TM_VE32_TILE_TIMER_BASE, VEXABC34_TM_VE32_TILE_TIMER_BASE,
    VEXABC35_TM_VE32_TILE_TIMER_BASE, VEXABC36_TM_VE32_TILE_TIMER_BASE, VEXABC37_TM_VE32_TILE_TIMER_BASE, VEXABC38_TM_VE32_TILE_TIMER_BASE, VEXABC39_TM_VE32_TILE_TIMER_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
            LOG_PRINT("i is %d", i);
            if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
                continue;
            }
            else
            {
        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDPARAMSR_OFFSET, \
                                    VE32_TILE_TIMER_TMDPARAMSR_DEFAULT, \
                                    VE32_TILE_TIMER_TMDPARAMSR_RD_MASK, "VE32_TILE_TIMER_TMDPARAMSR_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDVALR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDVALR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDVALR0_RD_MASK, "VE32_TILE_TIMER_TMDVALR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCFGR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDCFGR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCFGR0_RD_MASK, "VE32_TILE_TIMER_TMDCFGR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDINITR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDINITR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDINITR0_RD_MASK, "VE32_TILE_TIMER_TMDINITR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDNOTR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDNOTR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDNOTR0_RD_MASK, "VE32_TILE_TIMER_TMDWDNOTR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDADDRR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDADDRR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDADDRR0_RD_MASK, "VE32_TILE_TIMER_TMDWDADDRR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDDATAR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDDATAR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDDATAR0_RD_MASK, "VE32_TILE_TIMER_TMDWDDATAR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCMDR0_OFFSET, \
                                    VE32_TILE_TIMER_TMDCMDR0_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCMDR0_RD_MASK, "VE32_TILE_TIMER_TMDCMDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDVALR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDVALR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDVALR1_RD_MASK, "VE32_TILE_TIMER_TMDVALR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCFGR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDCFGR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCFGR1_RD_MASK, "VE32_TILE_TIMER_TMDCFGR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDINITR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDINITR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDINITR1_RD_MASK, "VE32_TILE_TIMER_TMDINITR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDNOTR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDNOTR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDNOTR1_RD_MASK, "VE32_TILE_TIMER_TMDWDNOTR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDADDRR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDADDRR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDADDRR1_RD_MASK, "VE32_TILE_TIMER_TMDWDADDRR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDDATAR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDDATAR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDDATAR1_RD_MASK, "VE32_TILE_TIMER_TMDWDDATAR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCMDR1_OFFSET, \
                                    VE32_TILE_TIMER_TMDCMDR1_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCMDR1_RD_MASK, "VE32_TILE_TIMER_TMDCMDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDVALR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDVALR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDVALR2_RD_MASK, "VE32_TILE_TIMER_TMDVALR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCFGR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDCFGR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCFGR2_RD_MASK, "VE32_TILE_TIMER_TMDCFGR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDINITR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDINITR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDINITR2_RD_MASK, "VE32_TILE_TIMER_TMDINITR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDNOTR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDNOTR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDNOTR2_RD_MASK, "VE32_TILE_TIMER_TMDWDNOTR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDADDRR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDADDRR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDADDRR2_RD_MASK, "VE32_TILE_TIMER_TMDWDADDRR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDDATAR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDDATAR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDDATAR2_RD_MASK, "VE32_TILE_TIMER_TMDWDDATAR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCMDR2_OFFSET, \
                                    VE32_TILE_TIMER_TMDCMDR2_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCMDR2_RD_MASK, "VE32_TILE_TIMER_TMDCMDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDVALR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDVALR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDVALR3_RD_MASK, "VE32_TILE_TIMER_TMDVALR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCFGR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDCFGR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCFGR3_RD_MASK, "VE32_TILE_TIMER_TMDCFGR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDINITR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDINITR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDINITR3_RD_MASK, "VE32_TILE_TIMER_TMDINITR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDNOTR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDNOTR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDNOTR3_RD_MASK, "VE32_TILE_TIMER_TMDWDNOTR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDADDRR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDADDRR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDADDRR3_RD_MASK, "VE32_TILE_TIMER_TMDWDADDRR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDWDDATAR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDWDDATAR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDWDDATAR3_RD_MASK, "VE32_TILE_TIMER_TMDWDDATAR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDCMDR3_OFFSET, \
                                    VE32_TILE_TIMER_TMDCMDR3_DEFAULT, \
                                    VE32_TILE_TIMER_TMDCMDR3_RD_MASK, "VE32_TILE_TIMER_TMDCMDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_TILE_TIMER_TMDGLOBALCTLR_OFFSET, \
                                    VE32_TILE_TIMER_TMDGLOBALCTLR_DEFAULT, \
                                    VE32_TILE_TIMER_TMDGLOBALCTLR_RD_MASK, "VE32_TILE_TIMER_TMDGLOBALCTLR_OFFSET");

    }

}
}

