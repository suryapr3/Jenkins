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
    int i,j;
    init();

    uint32_t base_address1[] = {
    FB_SYS0_DDC0_BASE, FB_SYS0_DDC1_BASE, FB_SYS1_DDC0_BASE, FB_SYS1_DDC1_BASE};


    uint32_t base_address2[] = {
    TRX_SYS0_DDC0_BASE,TRX_SYS0_DDC1_BASE, TRX_SYS1_DDC0_BASE, TRX_SYS1_DDC1_BASE, TRX_SYS2_DDC0_BASE, TRX_SYS2_DDC1_BASE,
    TRX_SYS3_DDC0_BASE, TRX_SYS3_DDC1_BASE, TRX_SYS4_DDC0_BASE, TRX_SYS4_DDC1_BASE, TRX_SYS5_DDC0_BASE,
    TRX_SYS5_DDC1_BASE, TRX_SYS6_DDC0_BASE, TRX_SYS6_DDC1_BASE, TRX_SYS7_DDC0_BASE, TRX_SYS7_DDC1_BASE
    };

    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {
        for(j=0; j<size[i]; j++)
        {
            read_reg_expect_18a(base_addresses[i][j]+DDC_SCRATCH_OFFSET, \
                                        DDC_SCRATCH_DEFAULT, \
                                        DDC_SCRATCH_RD_MASK, "DDC_SCRATCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+DDC_CFG_OFFSET, \
                                        DDC_CFG_DEFAULT, \
                                        DDC_CFG_RD_MASK, "DDC_CFG_OFFSET");
#if 0
            //RO(V) Register

            read_reg_expect_18a(base_addresses[i][j]+DDC_STAT_OFFSET, \
                                        DDC_STAT_DEFAULT, \
                                        DDC_STAT_RD_MASK, "DDC_STAT_OFFSET");
#endif

            read_reg_expect_18a(base_addresses[i][j]+DDC_APB_BRDG_STAT_OFFSET, \
                                        DDC_APB_BRDG_STAT_DEFAULT, \
                                        DDC_APB_BRDG_STAT_RD_MASK, "DDC_APB_BRDG_STAT_OFFSET");
        }

    }

}
