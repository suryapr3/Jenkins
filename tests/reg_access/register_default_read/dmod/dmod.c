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

    uint32_t base_address1[] = {FB_SYS0_DMOD_BASE,  FB_SYS1_DMOD_BASE};

    uint32_t base_address2[] = {TRX_SYS0_DMOD_BASE,  TRX_SYS1_DMOD_BASE,  TRX_SYS2_DMOD_BASE,
     TRX_SYS3_DMOD_BASE,  TRX_SYS4_DMOD_BASE,  TRX_SYS5_DMOD_BASE,  TRX_SYS6_DMOD_BASE,  TRX_SYS7_DMOD_BASE
    };


    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {
        for(j=0; j<size[i]; j++)
        {
        read_reg_expect_18a(base_addresses[i][j]+DMOD_SCRATCH_OFFSET, \
                                    DMOD_SCRATCH_DEFAULT, \
                                    DMOD_SCRATCH_RD_MASK, "DMOD_SCRATCH_OFFSET");

        read_reg_expect_18a(base_addresses[i][j]+DMOD_CFG_OFFSET, \
                                    DMOD_CFG_DEFAULT, \
                                    DMOD_CFG_RD_MASK, "DMOD_CFG_OFFSET");

        read_reg_expect_18a(base_addresses[i][j]+DMOD_EN_OFFSET, \
                                    DMOD_EN_DEFAULT, \
                                    DMOD_EN_RD_MASK, "DMOD_EN_OFFSET");

        read_reg_expect_18a(base_addresses[i][j]+DMOD_SAT_VAL_OFFSET, \
                                    DMOD_SAT_VAL_DEFAULT, \
                                    DMOD_SAT_VAL_RD_MASK, "DMOD_SAT_VAL_OFFSET");

        read_reg_expect_18a(base_addresses[i][j]+DMOD_APB_BRDG_STAT_OFFSET, \
                                    DMOD_APB_BRDG_STAT_DEFAULT, \
                                    DMOD_APB_BRDG_STAT_RD_MASK, "DMOD_APB_BRDG_STAT_OFFSET");
        }

    }

}

