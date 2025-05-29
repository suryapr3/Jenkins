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
    DLNK_JESD0_PHY_PMA0_CMNANA_BIASTRIM_BASE, DLNK_JESD1_PHY_PMA0_CMNANA_BIASTRIM_BASE, DLNK_JESD2_PHY_PMA0_CMNANA_BIASTRIM_BASE, DLNK_JESD3_PHY_PMA0_CMNANA_BIASTRIM_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIASCTRL1_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIASCTRL1_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIASCTRL1_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIASCTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_NMOS0_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_NMOS0_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_NMOS0_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_NMOS0_OFFSET");

        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS0_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS0_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS0_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS0_OFFSET");

        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS1_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS1_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS1_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS1_OFFSET");

        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS2_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS2_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS2_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNGLOBAL_BIAS_TRIM_PMOS2_OFFSET");

        read_reg_expect_18a(base_address[i]+CMNANA_BIASTRIM_MSG_CMNBIASTRIM_SPARE0_OFFSET, \
                                    CMNANA_BIASTRIM_MSG_CMNBIASTRIM_SPARE0_DEFAULT, \
                                    CMNANA_BIASTRIM_MSG_CMNBIASTRIM_SPARE0_RD_MASK, "CMNANA_BIASTRIM_MSG_CMNBIASTRIM_SPARE0_OFFSET");

    }

}
