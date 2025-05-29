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
    V2D0_AV2D_AXI4_0_BASE, V2D0_AV2D_AXI4_1_BASE, V2D1_AV2D_AXI4_0_BASE, V2D1_AV2D_AXI4_1_BASE, V2D2_AV2D_AXI4_0_BASE,
    V2D2_AV2D_AXI4_1_BASE, V2D3_AV2D_AXI4_0_BASE, V2D3_AV2D_AXI4_1_BASE, V2D4_AV2D_AXI4_0_BASE, V2D4_AV2D_AXI4_1_BASE,
    V2D5_AV2D_AXI4_0_BASE, V2D5_AV2D_AXI4_1_BASE, V2D6_AV2D_AXI4_0_BASE, V2D6_AV2D_AXI4_1_BASE, V2D7_AV2D_AXI4_0_BASE,
    V2D7_AV2D_AXI4_1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+AV2D_AXI4_AV2D_AXI4_PC_M1_OFFSET, \
                                    AV2D_AXI4_AV2D_AXI4_PC_M1_DEFAULT, \
                                    AV2D_AXI4_AV2D_AXI4_PC_M1_RD_MASK, "AV2D_AXI4_AV2D_AXI4_PC_M1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_AXI4_AV2D_AXI4_PC_M2_OFFSET, \
                                    AV2D_AXI4_AV2D_AXI4_PC_M2_DEFAULT, \
                                    AV2D_AXI4_AV2D_AXI4_PC_M2_RD_MASK, "AV2D_AXI4_AV2D_AXI4_PC_M2_OFFSET");

    }

}
