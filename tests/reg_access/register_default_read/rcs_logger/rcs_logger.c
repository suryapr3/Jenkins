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
    RCS_LOGGER_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDCRN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDCRN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDCRN_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDCRN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDSR1N_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDSR1N_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDSR1N_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDSR1N_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDSR2N_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDSR2N_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDSR2N_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDSR2N_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDEARN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDEARN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDEARN_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDEARN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_ECCSBECN_OFFSET, \
                                    RCS_LOGGER_RSM_ECCSBECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ECCSBECN_RD_MASK, "RCS_LOGGER_RSM0_ECCSBECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_ECCDBECN_OFFSET, \
                                    RCS_LOGGER_RSM_ECCDBECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ECCDBECN_RD_MASK, "RCS_LOGGER_RSM0_ECCDBECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AWPECN_OFFSET, \
                                    RCS_LOGGER_RSM_AWPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_AWPECN_RD_MASK, "RCS_LOGGER_RSM0_AWPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_WPECN_OFFSET, \
                                    RCS_LOGGER_RSM_WPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_WPECN_RD_MASK, "RCS_LOGGER_RSM0_WPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_ARPECN_OFFSET, \
                                    RCS_LOGGER_RSM_ARPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ARPECN_RD_MASK, "RCS_LOGGER_RSM0_ARPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDIMTN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIMTN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIMTN_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDIMTN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDIMTON_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIMTON_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIMTON_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDIMTON_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDFIFOSRN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDFIFOSRN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDFIFOSRN_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDFIFOSRN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDFIFON_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDFIFON_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDFIFON_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDFIFON_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM0_AXI2EDIDN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIDN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIDN_RD_MASK, "RCS_LOGGER_RSM0_AXI2EDIDN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDCRN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDCRN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDCRN_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDCRN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDSR1N_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDSR1N_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDSR1N_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDSR1N_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDSR2N_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDSR2N_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDSR2N_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDSR2N_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDEARN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDEARN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDEARN_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDEARN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_ECCSBECN_OFFSET, \
                                    RCS_LOGGER_RSM_ECCSBECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ECCSBECN_RD_MASK, "RCS_LOGGER_RSM1_ECCSBECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_ECCDBECN_OFFSET, \
                                    RCS_LOGGER_RSM_ECCDBECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ECCDBECN_RD_MASK, "RCS_LOGGER_RSM1_ECCDBECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AWPECN_OFFSET, \
                                    RCS_LOGGER_RSM_AWPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_AWPECN_RD_MASK, "RCS_LOGGER_RSM1_AWPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_WPECN_OFFSET, \
                                    RCS_LOGGER_RSM_WPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_WPECN_RD_MASK, "RCS_LOGGER_RSM1_WPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_ARPECN_OFFSET, \
                                    RCS_LOGGER_RSM_ARPECN_DEFAULT, \
                                    RCS_LOGGER_RSM_ARPECN_RD_MASK, "RCS_LOGGER_RSM1_ARPECN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDIMTN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIMTN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIMTN_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDIMTN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDIMTON_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIMTON_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIMTON_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDIMTON_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDFIFOSRN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDFIFOSRN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDFIFOSRN_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDFIFOSRN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDFIFON_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDFIFON_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDFIFON_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDFIFON_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_RSM1_AXI2EDIDN_OFFSET, \
                                    RCS_LOGGER_RSM_AXI2EDIDN_DEFAULT, \
                                    RCS_LOGGER_RSM_AXI2EDIDN_RD_MASK, "RCS_LOGGER_RSM1_AXI2EDIDN_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_PID_OFFSET, \
                                    RCS_LOGGER_PID_DEFAULT, \
                                    RCS_LOGGER_PID_RD_MASK, "RCS_LOGGER_PID_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_PEIWER_OFFSET, \
                                    RCS_LOGGER_PEIWER_DEFAULT, \
                                    RCS_LOGGER_PEIWER_RD_MASK, "RCS_LOGGER_PEIWER_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_EMCR_OFFSET, \
                                    RCS_LOGGER_EMCR_DEFAULT, \
                                    RCS_LOGGER_EMCR_RD_MASK, "RCS_LOGGER_EMCR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_ADBESR_OFFSET, \
                                    RCS_LOGGER_ADBESR_DEFAULT, \
                                    RCS_LOGGER_ADBESR_RD_MASK, "RCS_LOGGER_ADBESR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_LOGGER_APESR_OFFSET, \
                                    RCS_LOGGER_APESR_DEFAULT, \
                                    RCS_LOGGER_APESR_RD_MASK, "RCS_LOGGER_APESR_OFFSET");

    }

}
