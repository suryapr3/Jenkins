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
    RCS_GPREG_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_CFG_OFFSET, \
                                    RCS_GPREG_RCS_CFG_DEFAULT, \
                                    RCS_GPREG_RCS_CFG_RD_MASK, "RCS_GPREG_RCS_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE0_CTRL_OFFSET, \
                                    RCS_GPREG_CORE0_CTRL_DEFAULT, \
                                    RCS_GPREG_CORE0_CTRL_RD_MASK, "RCS_GPREG_CORE0_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE1_CTRL_OFFSET, \
                                    RCS_GPREG_CORE1_CTRL_DEFAULT, \
                                    RCS_GPREG_CORE1_CTRL_RD_MASK, "RCS_GPREG_CORE1_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE2_CTRL_OFFSET, \
                                    RCS_GPREG_CORE2_CTRL_DEFAULT, \
                                    RCS_GPREG_CORE2_CTRL_RD_MASK, "RCS_GPREG_CORE2_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE3_CTRL_OFFSET, \
                                    RCS_GPREG_CORE3_CTRL_DEFAULT, \
                                    RCS_GPREG_CORE3_CTRL_RD_MASK, "RCS_GPREG_CORE3_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE0_ALTRSTVEC_OFFSET, \
                                    RCS_GPREG_CORE0_ALTRSTVEC_DEFAULT, \
                                    RCS_GPREG_CORE0_ALTRSTVEC_RD_MASK, "RCS_GPREG_CORE0_ALTRSTVEC_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE1_ALTRSTVEC_OFFSET, \
                                    RCS_GPREG_CORE1_ALTRSTVEC_DEFAULT, \
                                    RCS_GPREG_CORE1_ALTRSTVEC_RD_MASK, "RCS_GPREG_CORE1_ALTRSTVEC_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE2_ALTRSTVEC_OFFSET, \
                                    RCS_GPREG_CORE2_ALTRSTVEC_DEFAULT, \
                                    RCS_GPREG_CORE2_ALTRSTVEC_RD_MASK, "RCS_GPREG_CORE2_ALTRSTVEC_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_CORE3_ALTRSTVEC_OFFSET, \
                                    RCS_GPREG_CORE3_ALTRSTVEC_DEFAULT, \
                                    RCS_GPREG_CORE3_ALTRSTVEC_RD_MASK, "RCS_GPREG_CORE3_ALTRSTVEC_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SOFT_RST_OFFSET, \
                                    RCS_GPREG_SOFT_RST_DEFAULT, \
                                    RCS_GPREG_SOFT_RST_RD_MASK, "RCS_GPREG_SOFT_RST_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_MAILBOX_MASK_OFFSET, \
                                    RCS_GPREG_MAILBOX_MASK_DEFAULT, \
                                    RCS_GPREG_MAILBOX_MASK_RD_MASK, "RCS_GPREG_MAILBOX_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_CLK_DISS_OFFSET, \
                                    RCS_GPREG_RCS_CLK_DISS_DEFAULT, \
                                    RCS_GPREG_RCS_CLK_DISS_RD_MASK, "RCS_GPREG_RCS_CLK_DISS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_SCRATCH_OFFSET, \
                                    RCS_GPREG_RCS_SCRATCH_DEFAULT, \
                                    RCS_GPREG_RCS_SCRATCH_RD_MASK, "RCS_GPREG_RCS_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB0_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB0_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB0_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB0_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB0_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB0_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB0_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB0_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB1_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB1_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB1_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB1_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB1_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB1_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB1_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB1_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB2_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB2_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB2_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB2_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB2_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB2_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB2_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB2_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB3_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB3_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB3_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB3_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB3_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB3_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB3_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB3_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB4_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB4_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB4_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB4_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB4_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB4_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB4_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB4_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB5_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB5_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB5_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB5_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB5_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB5_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB5_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB5_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB6_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB6_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB6_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB6_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB6_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB6_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB6_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB6_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB7_MBDATA0_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB7_MBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB7_MBDATA1_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB7_MBDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB7_MBDATA2_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB7_MBDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_TO_RCS_MB7_MBDATA3_OFFSET, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_DEFAULT, \
                                    RCS_GPREG_EXT_TO_RCS_MB_MBDATA_RD_MASK, "RCS_GPREG_EXT_TO_RCS_MB7_MBDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB0_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB1_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB2_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB3_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB4_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB4_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB5_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB5_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB6_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB6_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB7_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB7_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB8_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB8_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB9_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB9_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB10_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB10_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RCS_TO_RCS_MB11_OFFSET, \
                                    RCS_GPREG_RCS_TO_RCS_MB_DEFAULT, \
                                    RCS_GPREG_RCS_TO_RCS_MB_RD_MASK, "RCS_GPREG_RCS_TO_RCS_MB11_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+RCS_GPREG_EXT_IRQ_GRP_OFFSET, \
                                    RCS_GPREG_EXT_IRQ_GRP_DEFAULT, \
                                    RCS_GPREG_EXT_IRQ_GRP_RD_MASK, "RCS_GPREG_EXT_IRQ_GRP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DOUBLEEXCEPTION_OUT_LX70_OFFSET, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX70_DEFAULT, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX70_RD_MASK, "RCS_GPREG_DOUBLEEXCEPTION_OUT_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX70_RD_MASK, "RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_CORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX70_RD_MASK, "RCS_GPREG_SYNCIRAM_CORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX70_RD_MASK, "RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_CORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX70_RD_MASK, "RCS_GPREG_SYNCDRAM_CORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_CORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX70_RD_MASK, "RCS_GPREG_ASYNCDRAM_CORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX70_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX70_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX70_RD_MASK, "RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX70_OFFSET, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX70_DEFAULT, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX70_RD_MASK, "RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_CORRECTBL_ERR_LX70_OFFSET, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX70_DEFAULT, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX70_RD_MASK, "RCS_GPREG_IRAM_CORRECTBL_ERR_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX70_OFFSET, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX70_DEFAULT, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX70_RD_MASK, "RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_CORRECTBL_ERR_LX70_OFFSET, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX70_DEFAULT, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX70_RD_MASK, "RCS_GPREG_DRAM_CORRECTBL_ERR_LX70_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DOUBLEEXCEPTION_OUT_LX71_OFFSET, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX71_DEFAULT, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX71_RD_MASK, "RCS_GPREG_DOUBLEEXCEPTION_OUT_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX71_RD_MASK, "RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_CORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX71_RD_MASK, "RCS_GPREG_SYNCIRAM_CORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX71_RD_MASK, "RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_CORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX71_RD_MASK, "RCS_GPREG_SYNCDRAM_CORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_CORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX71_RD_MASK, "RCS_GPREG_ASYNCDRAM_CORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX71_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX71_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX71_RD_MASK, "RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX71_OFFSET, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX71_DEFAULT, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX71_RD_MASK, "RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_CORRECTBL_ERR_LX71_OFFSET, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX71_DEFAULT, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX71_RD_MASK, "RCS_GPREG_IRAM_CORRECTBL_ERR_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX71_OFFSET, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX71_DEFAULT, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX71_RD_MASK, "RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_CORRECTBL_ERR_LX71_OFFSET, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX71_DEFAULT, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX71_RD_MASK, "RCS_GPREG_DRAM_CORRECTBL_ERR_LX71_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DOUBLEEXCEPTION_OUT_LX72_OFFSET, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX72_DEFAULT, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_LX72_RD_MASK, "RCS_GPREG_DOUBLEEXCEPTION_OUT_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX72_RD_MASK, "RCS_GPREG_SYNCIRAM_UNCORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_CORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_LX72_RD_MASK, "RCS_GPREG_SYNCIRAM_CORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX72_RD_MASK, "RCS_GPREG_SYNCDRAM_UNCORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_CORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_LX72_RD_MASK, "RCS_GPREG_SYNCDRAM_CORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_CORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_LX72_RD_MASK, "RCS_GPREG_ASYNCDRAM_CORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX72_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX72_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX72_RD_MASK, "RCS_GPREG_ASYNCDRAM_UNCORRECTBL_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX72_OFFSET, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX72_DEFAULT, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX72_RD_MASK, "RCS_GPREG_IRAM_UNCORRECTBL_ERR_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_CORRECTBL_ERR_LX72_OFFSET, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX72_DEFAULT, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_LX72_RD_MASK, "RCS_GPREG_IRAM_CORRECTBL_ERR_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX72_OFFSET, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX72_DEFAULT, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX72_RD_MASK, "RCS_GPREG_DRAM_UNCORRECTBL_ERR_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_CORRECTBL_ERR_LX72_OFFSET, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX72_DEFAULT, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_LX72_RD_MASK, "RCS_GPREG_DRAM_CORRECTBL_ERR_LX72_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DOUBLEEXCEPTION_OUT_KP1_OFFSET, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_KP1_DEFAULT, \
                                    RCS_GPREG_DOUBLEEXCEPTION_OUT_KP1_RD_MASK, "RCS_GPREG_DOUBLEEXCEPTION_OUT_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_UNCORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_UNCORRECTBL_KP1_RD_MASK, "RCS_GPREG_SYNCIRAM_UNCORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCIRAM_CORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_SYNCIRAM_CORRECTBL_KP1_RD_MASK, "RCS_GPREG_SYNCIRAM_CORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_UNCORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_UNCORRECTBL_KP1_RD_MASK, "RCS_GPREG_SYNCDRAM_UNCORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_SYNCDRAM_CORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_SYNCDRAM_CORRECTBL_KP1_RD_MASK, "RCS_GPREG_SYNCDRAM_CORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_CORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_CORRECTBL_KP1_RD_MASK, "RCS_GPREG_ASYNCDRAM_CORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_ASYNCDRAM_UNCORRECTBL_KP1_OFFSET, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_KP1_DEFAULT, \
                                    RCS_GPREG_ASYNCDRAM_UNCORRECTBL_KP1_RD_MASK, "RCS_GPREG_ASYNCDRAM_UNCORRECTBL_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_UNCORRECTBL_ERR_KP1_OFFSET, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_KP1_DEFAULT, \
                                    RCS_GPREG_IRAM_UNCORRECTBL_ERR_KP1_RD_MASK, "RCS_GPREG_IRAM_UNCORRECTBL_ERR_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_IRAM_CORRECTBL_ERR_KP1_OFFSET, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_KP1_DEFAULT, \
                                    RCS_GPREG_IRAM_CORRECTBL_ERR_KP1_RD_MASK, "RCS_GPREG_IRAM_CORRECTBL_ERR_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_UNCORRECTBL_ERR_KP1_OFFSET, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_KP1_DEFAULT, \
                                    RCS_GPREG_DRAM_UNCORRECTBL_ERR_KP1_RD_MASK, "RCS_GPREG_DRAM_UNCORRECTBL_ERR_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_DRAM_CORRECTBL_ERR_KP1_OFFSET, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_KP1_DEFAULT, \
                                    RCS_GPREG_DRAM_CORRECTBL_ERR_KP1_RD_MASK, "RCS_GPREG_DRAM_CORRECTBL_ERR_KP1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_RPC_FAULTSERVERITYLVL_OFFSET, \
                                    RCS_GPREG_RPC_FAULTSERVERITYLVL_DEFAULT, \
                                    RCS_GPREG_RPC_FAULTSERVERITYLVL_RD_MASK, "RCS_GPREG_RPC_FAULTSERVERITYLVL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_MAILBOX_CLR_OFFSET, \
                                    RCS_GPREG_MAILBOX_CLR_DEFAULT, \
                                    RCS_GPREG_MAILBOX_CLR_RD_MASK, "RCS_GPREG_MAILBOX_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_STAT_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_STAT_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_STAT_0_RD_MASK, "RCS_GPREG_EDG_IRQ_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_MASK_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_MASK_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_MASK_0_RD_MASK, "RCS_GPREG_EDG_IRQ_MASK_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_INV_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_INV_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_INV_0_RD_MASK, "RCS_GPREG_EDG_IRQ_INV_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_NOMASK_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_0_RD_MASK, "RCS_GPREG_EDG_IRQ_NOMASK_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_RAW_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_RAW_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_RAW_0_RD_MASK, "RCS_GPREG_EDG_IRQ_RAW_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_STAT_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_0_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_MASK_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_0_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_MASK_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_STAT_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_0_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_MASK_0_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_0_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_0_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_MASK_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_OSAZ_OFFSET, \
                                    RCS_GPREG_OSAZ_DEFAULT, \
                                    RCS_GPREG_OSAZ_RD_MASK, "RCS_GPREG_OSAZ_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_STAT_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_STAT_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_STAT_1_RD_MASK, "RCS_GPREG_EDG_IRQ_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_MASK_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_MASK_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_MASK_1_RD_MASK, "RCS_GPREG_EDG_IRQ_MASK_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_INV_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_INV_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_INV_1_RD_MASK, "RCS_GPREG_EDG_IRQ_INV_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_NOMASK_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_1_RD_MASK, "RCS_GPREG_EDG_IRQ_NOMASK_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_RAW_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_RAW_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_RAW_1_RD_MASK, "RCS_GPREG_EDG_IRQ_RAW_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_STAT_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_1_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_MASK_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_1_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_MASK_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_STAT_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_1_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_MASK_1_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_1_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_1_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_MASK_1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_STAT_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_STAT_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_STAT_2_RD_MASK, "RCS_GPREG_EDG_IRQ_STAT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_MASK_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_MASK_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_MASK_2_RD_MASK, "RCS_GPREG_EDG_IRQ_MASK_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_INV_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_INV_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_INV_2_RD_MASK, "RCS_GPREG_EDG_IRQ_INV_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_NOMASK_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_NOMASK_2_RD_MASK, "RCS_GPREG_EDG_IRQ_NOMASK_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_RAW_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_RAW_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_RAW_2_RD_MASK, "RCS_GPREG_EDG_IRQ_RAW_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_STAT_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_STAT_2_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_STAT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_HI_MASK_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_HI_MASK_2_RD_MASK, "RCS_GPREG_EDG_IRQ_HI_MASK_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_STAT_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_STAT_2_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_STAT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_GPREG_EDG_IRQ_TX_MASK_2_OFFSET, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_2_DEFAULT, \
                                    RCS_GPREG_EDG_IRQ_TX_MASK_2_RD_MASK, "RCS_GPREG_EDG_IRQ_TX_MASK_2_OFFSET");

    }

}
