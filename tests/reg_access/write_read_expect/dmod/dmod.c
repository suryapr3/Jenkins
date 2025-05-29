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
    int i,j;
    init();

    uint32_t base_address1[] = {FB_SYS0_DMOD_BASE,  FB_SYS1_DMOD_BASE};

    uint32_t base_address2[] = {TRX_SYS0_DMOD_BASE,  TRX_SYS1_DMOD_BASE,  TRX_SYS2_DMOD_BASE,
     TRX_SYS3_DMOD_BASE,  TRX_SYS4_DMOD_BASE,  TRX_SYS5_DMOD_BASE,  TRX_SYS6_DMOD_BASE,  TRX_SYS7_DMOD_BASE
    };


    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

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


        for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
        {
            for(j=0; j<size[i]; j++)
            {

                write_read_expect_18a(base_addresses[i][j]+DMOD_SCRATCH_OFFSET, \
                                        DMOD_SCRATCH_DEFAULT, write_data, expected_data, \
                                        DMOD_SCRATCH_RD_MASK, DMOD_SCRATCH_WR_MASK, \
                                        "DMOD_SCRATCH_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DMOD_CFG_OFFSET, \
                                        DMOD_CFG_DEFAULT, write_data, expected_data, \
                                        DMOD_CFG_RD_MASK, DMOD_CFG_WR_MASK, \
                                        "DMOD_CFG_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DMOD_EN_OFFSET, \
                                        DMOD_EN_DEFAULT, write_data, expected_data, \
                                        DMOD_EN_RD_MASK, DMOD_EN_WR_MASK, \
                                        "DMOD_EN_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DMOD_SAT_VAL_OFFSET, \
                                        DMOD_SAT_VAL_DEFAULT, write_data, expected_data, \
                                        DMOD_SAT_VAL_RD_MASK, DMOD_SAT_VAL_WR_MASK, \
                                        "DMOD_SAT_VAL_OFFSET");

#if 0
                //Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
                write_read_expect_18a(base_addresses[i][j]+DMOD_APB_BRDG_STAT_OFFSET, \
                                        DMOD_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                        DMOD_APB_BRDG_STAT_RD_MASK, DMOD_APB_BRDG_STAT_WR_MASK, \
                                        "DMOD_APB_BRDG_STAT_OFFSET");
#endif
            }

        }

    }

}
