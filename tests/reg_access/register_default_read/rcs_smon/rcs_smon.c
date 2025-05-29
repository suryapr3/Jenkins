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
    RCS_SMON_ORION_MAIN_KP1_BASE, RCS_SMON_CORES_DMA_BASE, RCS_SMON_RSM_ROM_PHM_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_SMON_READ_ID_CMP_OFFSET, \
                                    RCS_SMON_READ_ID_CMP_DEFAULT, \
                                    RCS_SMON_READ_ID_CMP_RD_MASK, "RCS_SMON_READ_ID_CMP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_WRITE_ID_CMP_OFFSET, \
                                    RCS_SMON_WRITE_ID_CMP_DEFAULT, \
                                    RCS_SMON_WRITE_ID_CMP_RD_MASK, "RCS_SMON_WRITE_ID_CMP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON00_OFFSET, \
                                    RCS_SMON_SMON00_DEFAULT, \
                                    RCS_SMON_SMON00_RD_MASK, "RCS_SMON_SMON00_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON01_OFFSET, \
                                    RCS_SMON_SMON01_DEFAULT, \
                                    RCS_SMON_SMON01_RD_MASK, "RCS_SMON_SMON01_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON02_OFFSET, \
                                    RCS_SMON_SMON02_DEFAULT, \
                                    RCS_SMON_SMON02_RD_MASK, "RCS_SMON_SMON02_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON03_OFFSET, \
                                    RCS_SMON_SMON03_DEFAULT, \
                                    RCS_SMON_SMON03_RD_MASK, "RCS_SMON_SMON03_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON04_OFFSET, \
                                    RCS_SMON_SMON04_DEFAULT, \
                                    RCS_SMON_SMON04_RD_MASK, "RCS_SMON_SMON04_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON05_OFFSET, \
                                    RCS_SMON_SMON05_DEFAULT, \
                                    RCS_SMON_SMON05_RD_MASK, "RCS_SMON_SMON05_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON06_OFFSET, \
                                    RCS_SMON_SMON06_DEFAULT, \
                                    RCS_SMON_SMON06_RD_MASK, "RCS_SMON_SMON06_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SMON_SMON07_OFFSET, \
                                    RCS_SMON_SMON07_DEFAULT, \
                                    RCS_SMON_SMON07_RD_MASK, "RCS_SMON_SMON07_OFFSET");

    }

}
