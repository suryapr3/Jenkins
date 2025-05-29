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
    VEXABC0_GP_VE32_TILE_CTRL_BASE, VEXABC1_GP_VE32_TILE_CTRL_BASE, VEXABC2_GP_VE32_TILE_CTRL_BASE, VEXABC3_GP_VE32_TILE_CTRL_BASE, VEXABC4_GP_VE32_TILE_CTRL_BASE,
    VEXABC5_GP_VE32_TILE_CTRL_BASE, VEXABC6_GP_VE32_TILE_CTRL_BASE, VEXABC7_GP_VE32_TILE_CTRL_BASE, VEXABC8_GP_VE32_TILE_CTRL_BASE, VEXABC9_GP_VE32_TILE_CTRL_BASE,
    VEXABC10_GP_VE32_TILE_CTRL_BASE, VEXABC11_GP_VE32_TILE_CTRL_BASE, VEXABC12_GP_VE32_TILE_CTRL_BASE, VEXABC13_GP_VE32_TILE_CTRL_BASE, VEXABC14_GP_VE32_TILE_CTRL_BASE,
    VEXABC15_GP_VE32_TILE_CTRL_BASE, VEXABC16_GP_VE32_TILE_CTRL_BASE, VEXABC17_GP_VE32_TILE_CTRL_BASE, VEXABC18_GP_VE32_TILE_CTRL_BASE, VEXABC19_GP_VE32_TILE_CTRL_BASE,
    VEXABC20_GP_VE32_TILE_CTRL_BASE, VEXABC21_GP_VE32_TILE_CTRL_BASE, VEXABC22_GP_VE32_TILE_CTRL_BASE, VEXABC23_GP_VE32_TILE_CTRL_BASE, VEXABC24_GP_VE32_TILE_CTRL_BASE,
    VEXABC25_GP_VE32_TILE_CTRL_BASE, VEXABC26_GP_VE32_TILE_CTRL_BASE, VEXABC27_GP_VE32_TILE_CTRL_BASE, VEXABC28_GP_VE32_TILE_CTRL_BASE, VEXABC29_GP_VE32_TILE_CTRL_BASE,
    VEXABC30_GP_VE32_TILE_CTRL_BASE, VEXABC31_GP_VE32_TILE_CTRL_BASE, VEXABC32_GP_VE32_TILE_CTRL_BASE, VEXABC33_GP_VE32_TILE_CTRL_BASE, VEXABC34_GP_VE32_TILE_CTRL_BASE,
    VEXABC35_GP_VE32_TILE_CTRL_BASE, VEXABC36_GP_VE32_TILE_CTRL_BASE, VEXABC37_GP_VE32_TILE_CTRL_BASE, VEXABC38_GP_VE32_TILE_CTRL_BASE, VEXABC39_GP_VE32_TILE_CTRL_BASE
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
			LOG_PRINT("i is %d", i);
            if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
                continue;
            }
            else
            {
            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_GPIO0_OFFSET, \
                                    VE32_TILE_CTRL_GPIO0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_GPIO0_RD_MASK, VE32_TILE_CTRL_GPIO0_WR_MASK, \
                                    "VE32_TILE_CTRL_GPIO0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_GPIO1_OFFSET, \
                                    VE32_TILE_CTRL_GPIO1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_GPIO1_RD_MASK, VE32_TILE_CTRL_GPIO1_WR_MASK, \
                                    "VE32_TILE_CTRL_GPIO1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_GPIO2_OFFSET, \
                                    VE32_TILE_CTRL_GPIO2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_GPIO2_RD_MASK, VE32_TILE_CTRL_GPIO2_WR_MASK, \
                                    "VE32_TILE_CTRL_GPIO2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_GPIO3_OFFSET, \
                                    VE32_TILE_CTRL_GPIO3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_GPIO3_RD_MASK, VE32_TILE_CTRL_GPIO3_WR_MASK, \
                                    "VE32_TILE_CTRL_GPIO3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_WDTIRQ_OFFSET, \
                                    VE32_TILE_CTRL_WDTIRQ_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_WDTIRQ_RD_MASK, VE32_TILE_CTRL_WDTIRQ_WR_MASK, \
                                    "VE32_TILE_CTRL_WDTIRQ_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_CID_OFFSET, \
                                    VE32_TILE_CTRL_CID_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_CID_RD_MASK, VE32_TILE_CTRL_CID_WR_MASK, \
                                    "VE32_TILE_CTRL_CID_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_CTRL_TMRCTL_OFFSET, \
                                    VE32_TILE_CTRL_TMRCTL_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_CTRL_TMRCTL_RD_MASK, VE32_TILE_CTRL_TMRCTL_WR_MASK, \
                                    "VE32_TILE_CTRL_TMRCTL_OFFSET");

        }

    }

}
}
