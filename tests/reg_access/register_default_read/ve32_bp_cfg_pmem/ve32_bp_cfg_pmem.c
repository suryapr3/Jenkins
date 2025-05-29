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
    VEXABC0_PMEM_VE32_BP_CFG_BASE, VEXABC1_PMEM_VE32_BP_CFG_BASE, VEXABC2_PMEM_VE32_BP_CFG_BASE, VEXABC3_PMEM_VE32_BP_CFG_BASE, VEXABC4_PMEM_VE32_BP_CFG_BASE,
    VEXABC5_PMEM_VE32_BP_CFG_BASE, VEXABC6_PMEM_VE32_BP_CFG_BASE, VEXABC7_PMEM_VE32_BP_CFG_BASE, VEXABC8_PMEM_VE32_BP_CFG_BASE, VEXABC9_PMEM_VE32_BP_CFG_BASE,
    VEXABC10_PMEM_VE32_BP_CFG_BASE, VEXABC11_PMEM_VE32_BP_CFG_BASE, VEXABC12_PMEM_VE32_BP_CFG_BASE, VEXABC13_PMEM_VE32_BP_CFG_BASE, VEXABC14_PMEM_VE32_BP_CFG_BASE,
    VEXABC15_PMEM_VE32_BP_CFG_BASE, VEXABC16_PMEM_VE32_BP_CFG_BASE, VEXABC17_PMEM_VE32_BP_CFG_BASE, VEXABC18_PMEM_VE32_BP_CFG_BASE, VEXABC19_PMEM_VE32_BP_CFG_BASE,
    VEXABC20_PMEM_VE32_BP_CFG_BASE, VEXABC21_PMEM_VE32_BP_CFG_BASE, VEXABC22_PMEM_VE32_BP_CFG_BASE, VEXABC23_PMEM_VE32_BP_CFG_BASE, VEXABC24_PMEM_VE32_BP_CFG_BASE,
    VEXABC25_PMEM_VE32_BP_CFG_BASE, VEXABC26_PMEM_VE32_BP_CFG_BASE, VEXABC27_PMEM_VE32_BP_CFG_BASE, VEXABC28_PMEM_VE32_BP_CFG_BASE, VEXABC29_PMEM_VE32_BP_CFG_BASE,
    VEXABC30_PMEM_VE32_BP_CFG_BASE, VEXABC31_PMEM_VE32_BP_CFG_BASE, VEXABC32_PMEM_VE32_BP_CFG_BASE, VEXABC33_PMEM_VE32_BP_CFG_BASE, VEXABC34_PMEM_VE32_BP_CFG_BASE,
    VEXABC35_PMEM_VE32_BP_CFG_BASE, VEXABC36_PMEM_VE32_BP_CFG_BASE, VEXABC37_PMEM_VE32_BP_CFG_BASE, VEXABC38_PMEM_VE32_BP_CFG_BASE, VEXABC39_PMEM_VE32_BP_CFG_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+VE32_BP_CFG_PMEM_FIRST_OFFSET, \
                                    VE32_BP_CFG_PMEM_FIRST_DEFAULT, \
                                    VE32_BP_CFG_PMEM_FIRST_RD_MASK, "VE32_BP_CFG_PMEM_FIRST_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_BP_CFG_PMEM_LAST_OFFSET, \
                                    VE32_BP_CFG_PMEM_LAST_DEFAULT, \
                                    VE32_BP_CFG_PMEM_LAST_RD_MASK, "VE32_BP_CFG_PMEM_LAST_OFFSET");

    }

}
