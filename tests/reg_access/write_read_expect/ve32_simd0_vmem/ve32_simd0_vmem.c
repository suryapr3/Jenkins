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
    VEXABC0_VMEM_VE32_SIMD0_BASE, VEXABC1_VMEM_VE32_SIMD0_BASE, VEXABC2_VMEM_VE32_SIMD0_BASE, VEXABC3_VMEM_VE32_SIMD0_BASE, VEXABC4_VMEM_VE32_SIMD0_BASE,
    VEXABC5_VMEM_VE32_SIMD0_BASE, VEXABC6_VMEM_VE32_SIMD0_BASE, VEXABC7_VMEM_VE32_SIMD0_BASE, VEXABC8_VMEM_VE32_SIMD0_BASE, VEXABC9_VMEM_VE32_SIMD0_BASE,
    VEXABC10_VMEM_VE32_SIMD0_BASE, VEXABC11_VMEM_VE32_SIMD0_BASE, VEXABC12_VMEM_VE32_SIMD0_BASE, VEXABC13_VMEM_VE32_SIMD0_BASE, VEXABC14_VMEM_VE32_SIMD0_BASE,
    VEXABC15_VMEM_VE32_SIMD0_BASE, VEXABC16_VMEM_VE32_SIMD0_BASE, VEXABC17_VMEM_VE32_SIMD0_BASE, VEXABC18_VMEM_VE32_SIMD0_BASE, VEXABC19_VMEM_VE32_SIMD0_BASE,
    VEXABC20_VMEM_VE32_SIMD0_BASE, VEXABC21_VMEM_VE32_SIMD0_BASE, VEXABC22_VMEM_VE32_SIMD0_BASE, VEXABC23_VMEM_VE32_SIMD0_BASE, VEXABC24_VMEM_VE32_SIMD0_BASE,
    VEXABC25_VMEM_VE32_SIMD0_BASE, VEXABC26_VMEM_VE32_SIMD0_BASE, VEXABC27_VMEM_VE32_SIMD0_BASE, VEXABC28_VMEM_VE32_SIMD0_BASE, VEXABC29_VMEM_VE32_SIMD0_BASE,
    VEXABC30_VMEM_VE32_SIMD0_BASE, VEXABC31_VMEM_VE32_SIMD0_BASE, VEXABC32_VMEM_VE32_SIMD0_BASE, VEXABC33_VMEM_VE32_SIMD0_BASE, VEXABC34_VMEM_VE32_SIMD0_BASE,
    VEXABC35_VMEM_VE32_SIMD0_BASE, VEXABC36_VMEM_VE32_SIMD0_BASE, VEXABC37_VMEM_VE32_SIMD0_BASE, VEXABC38_VMEM_VE32_SIMD0_BASE, VEXABC39_VMEM_VE32_SIMD0_BASE
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
            write_read_expect_18a(base_address[i]+VE32_SIMD0_VMEM_FIRST_OFFSET, \
                                    VE32_SIMD0_VMEM_FIRST_DEFAULT, write_data, expected_data, \
                                    VE32_SIMD0_VMEM_FIRST_RD_MASK, VE32_SIMD0_VMEM_FIRST_WR_MASK, \
                                    "VE32_SIMD0_VMEM_FIRST_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_SIMD0_VMEM_LAST_OFFSET, \
                                    VE32_SIMD0_VMEM_LAST_DEFAULT, write_data, expected_data, \
                                    VE32_SIMD0_VMEM_LAST_RD_MASK, VE32_SIMD0_VMEM_LAST_WR_MASK, \
                                    "VE32_SIMD0_VMEM_LAST_OFFSET");

        }

    }

}
