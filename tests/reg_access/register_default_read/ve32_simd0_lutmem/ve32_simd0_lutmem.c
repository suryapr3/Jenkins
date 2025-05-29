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
    VEXABC0_LUTMEM_VE32_SIMD0_BASE, VEXABC1_LUTMEM_VE32_SIMD0_BASE, VEXABC2_LUTMEM_VE32_SIMD0_BASE, VEXABC3_LUTMEM_VE32_SIMD0_BASE, VEXABC4_LUTMEM_VE32_SIMD0_BASE,
    VEXABC5_LUTMEM_VE32_SIMD0_BASE, VEXABC6_LUTMEM_VE32_SIMD0_BASE, VEXABC7_LUTMEM_VE32_SIMD0_BASE, VEXABC8_LUTMEM_VE32_SIMD0_BASE, VEXABC9_LUTMEM_VE32_SIMD0_BASE,
    VEXABC10_LUTMEM_VE32_SIMD0_BASE, VEXABC11_LUTMEM_VE32_SIMD0_BASE, VEXABC12_LUTMEM_VE32_SIMD0_BASE, VEXABC13_LUTMEM_VE32_SIMD0_BASE, VEXABC14_LUTMEM_VE32_SIMD0_BASE,
    VEXABC15_LUTMEM_VE32_SIMD0_BASE, VEXABC16_LUTMEM_VE32_SIMD0_BASE, VEXABC17_LUTMEM_VE32_SIMD0_BASE, VEXABC18_LUTMEM_VE32_SIMD0_BASE, VEXABC19_LUTMEM_VE32_SIMD0_BASE,
    VEXABC20_LUTMEM_VE32_SIMD0_BASE, VEXABC21_LUTMEM_VE32_SIMD0_BASE, VEXABC22_LUTMEM_VE32_SIMD0_BASE, VEXABC23_LUTMEM_VE32_SIMD0_BASE, VEXABC24_LUTMEM_VE32_SIMD0_BASE,
    VEXABC25_LUTMEM_VE32_SIMD0_BASE, VEXABC26_LUTMEM_VE32_SIMD0_BASE, VEXABC27_LUTMEM_VE32_SIMD0_BASE, VEXABC28_LUTMEM_VE32_SIMD0_BASE, VEXABC29_LUTMEM_VE32_SIMD0_BASE,
    VEXABC30_LUTMEM_VE32_SIMD0_BASE, VEXABC31_LUTMEM_VE32_SIMD0_BASE, VEXABC32_LUTMEM_VE32_SIMD0_BASE, VEXABC33_LUTMEM_VE32_SIMD0_BASE, VEXABC34_LUTMEM_VE32_SIMD0_BASE,
    VEXABC35_LUTMEM_VE32_SIMD0_BASE, VEXABC36_LUTMEM_VE32_SIMD0_BASE, VEXABC37_LUTMEM_VE32_SIMD0_BASE, VEXABC38_LUTMEM_VE32_SIMD0_BASE, VEXABC39_LUTMEM_VE32_SIMD0_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_FIRST_OFFSET, \
                                    VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_FIRST_DEFAULT, \
                                    VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_FIRST_RD_MASK, "VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_FIRST_OFFSET");

        read_reg_expect_18a(base_address[i]+VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_LAST_OFFSET, \
                                    VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_LAST_DEFAULT, \
                                    VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_LAST_RD_MASK, "VE32_SIMD0_LUTMEM_MEM_VE32_SIMD0_LUTMEM_LAST_OFFSET");

    }

}
