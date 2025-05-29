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
    RCS_DMAC_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_DMAC_IDREG_OFFSET, \
                                    RCS_DMAC_IDREG_DEFAULT, \
                                    RCS_DMAC_IDREG_RD_MASK, "RCS_DMAC_IDREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_COMPVERREG_OFFSET, \
                                    RCS_DMAC_COMPVERREG_DEFAULT, \
                                    RCS_DMAC_COMPVERREG_RD_MASK, "RCS_DMAC_COMPVERREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CFGREG_OFFSET, \
                                    RCS_DMAC_CFGREG_DEFAULT, \
                                    RCS_DMAC_CFGREG_RD_MASK, "RCS_DMAC_CFGREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CHENREG_OFFSET, \
                                    RCS_DMAC_CHENREG_DEFAULT, \
                                    RCS_DMAC_CHENREG_RD_MASK, "RCS_DMAC_CHENREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_INTSTATREG_OFFSET, \
                                    RCS_DMAC_INTSTATREG_DEFAULT, \
                                    RCS_DMAC_INTSTATREG_RD_MASK, "RCS_DMAC_INTSTATREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CMNREG_INTCLRREG_OFFSET, \
                                    RCS_DMAC_CMNREG_INTCLRREG_DEFAULT, \
                                    RCS_DMAC_CMNREG_INTCLRREG_RD_MASK, "RCS_DMAC_CMNREG_INTCLRREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CMNREG_INTSTAT_ENREG_OFFSET, \
                                    RCS_DMAC_CMNREG_INTSTAT_ENREG_DEFAULT, \
                                    RCS_DMAC_CMNREG_INTSTAT_ENREG_RD_MASK, "RCS_DMAC_CMNREG_INTSTAT_ENREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CMNREG_INTSIGNAL_ENREG_OFFSET, \
                                    RCS_DMAC_CMNREG_INTSIGNAL_ENREG_DEFAULT, \
                                    RCS_DMAC_CMNREG_INTSIGNAL_ENREG_RD_MASK, "RCS_DMAC_CMNREG_INTSIGNAL_ENREG_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+RCS_DMAC_CMNREG_INTSTATREG_OFFSET, \
                                    RCS_DMAC_CMNREG_INTSTATREG_DEFAULT, \
                                    RCS_DMAC_CMNREG_INTSTATREG_RD_MASK, "RCS_DMAC_CMNREG_INTSTATREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_RSTREG_OFFSET, \
                                    RCS_DMAC_RSTREG_DEFAULT, \
                                    RCS_DMAC_RSTREG_RD_MASK, "RCS_DMAC_RSTREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_SAR_OFFSET, \
                                    RCS_DMAC_CH1_SAR_DEFAULT, \
                                    RCS_DMAC_CH1_SAR_RD_MASK, "RCS_DMAC_CH1_SAR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_DAR_OFFSET, \
                                    RCS_DMAC_CH1_DAR_DEFAULT, \
                                    RCS_DMAC_CH1_DAR_RD_MASK, "RCS_DMAC_CH1_DAR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_BLK_TS_OFFSET, \
                                    RCS_DMAC_CH1_BLK_TS_DEFAULT, \
                                    RCS_DMAC_CH1_BLK_TS_RD_MASK, "RCS_DMAC_CH1_BLK_TS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_CTL_OFFSET, \
                                    RCS_DMAC_CH1_CTL_DEFAULT, \
                                    RCS_DMAC_CH1_CTL_RD_MASK, "RCS_DMAC_CH1_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_CFG_OFFSET, \
                                    RCS_DMAC_CH1_CFG_DEFAULT, \
                                    RCS_DMAC_CH1_CFG_RD_MASK, "RCS_DMAC_CH1_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_LLP_OFFSET, \
                                    RCS_DMAC_CH1_LLP_DEFAULT, \
                                    RCS_DMAC_CH1_LLP_RD_MASK, "RCS_DMAC_CH1_LLP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_STATREG_OFFSET, \
                                    RCS_DMAC_CH1_STATREG_DEFAULT, \
                                    RCS_DMAC_CH1_STATREG_RD_MASK, "RCS_DMAC_CH1_STATREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_SWHSSRCREG_OFFSET, \
                                    RCS_DMAC_CH1_SWHSSRCREG_DEFAULT, \
                                    RCS_DMAC_CH1_SWHSSRCREG_RD_MASK, "RCS_DMAC_CH1_SWHSSRCREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_SWHSDSTREG_OFFSET, \
                                    RCS_DMAC_CH1_SWHSDSTREG_DEFAULT, \
                                    RCS_DMAC_CH1_SWHSDSTREG_RD_MASK, "RCS_DMAC_CH1_SWHSDSTREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_BLK_TFR_RESUMEREQREG_OFFSET, \
                                    RCS_DMAC_CH1_BLK_TFR_RESUMEREQREG_DEFAULT, \
                                    RCS_DMAC_CH1_BLK_TFR_RESUMEREQREG_RD_MASK, "RCS_DMAC_CH1_BLK_TFR_RESUMEREQREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_IDREG_OFFSET, \
                                    RCS_DMAC_CH1_IDREG_DEFAULT, \
                                    RCS_DMAC_CH1_IDREG_RD_MASK, "RCS_DMAC_CH1_IDREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_QOSREG_OFFSET, \
                                    RCS_DMAC_CH1_QOSREG_DEFAULT, \
                                    RCS_DMAC_CH1_QOSREG_RD_MASK, "RCS_DMAC_CH1_QOSREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_INTSTAT_ENREG_OFFSET, \
                                    RCS_DMAC_CH1_INTSTAT_ENREG_DEFAULT, \
                                    RCS_DMAC_CH1_INTSTAT_ENREG_RD_MASK, "RCS_DMAC_CH1_INTSTAT_ENREG_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_INTSTAT_OFFSET, \
                                    RCS_DMAC_CH1_INTSTAT_DEFAULT, \
                                    RCS_DMAC_CH1_INTSTAT_RD_MASK, "RCS_DMAC_CH1_INTSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_INTSIGNAL_ENREG_OFFSET, \
                                    RCS_DMAC_CH1_INTSIGNAL_ENREG_DEFAULT, \
                                    RCS_DMAC_CH1_INTSIGNAL_ENREG_RD_MASK, "RCS_DMAC_CH1_INTSIGNAL_ENREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_INTCLRREG_OFFSET, \
                                    RCS_DMAC_CH1_INTCLRREG_DEFAULT, \
                                    RCS_DMAC_CH1_INTCLRREG_RD_MASK, "RCS_DMAC_CH1_INTCLRREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH1_CFG_EXTD_OFFSET, \
                                    RCS_DMAC_CH1_CFG_EXTD_DEFAULT, \
                                    RCS_DMAC_CH1_CFG_EXTD_RD_MASK, "RCS_DMAC_CH1_CFG_EXTD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_SAR_OFFSET, \
                                    RCS_DMAC_CH2_SAR_DEFAULT, \
                                    RCS_DMAC_CH2_SAR_RD_MASK, "RCS_DMAC_CH2_SAR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_DAR_OFFSET, \
                                    RCS_DMAC_CH2_DAR_DEFAULT, \
                                    RCS_DMAC_CH2_DAR_RD_MASK, "RCS_DMAC_CH2_DAR_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_BLK_TS_OFFSET, \
                                    RCS_DMAC_CH2_BLK_TS_DEFAULT, \
                                    RCS_DMAC_CH2_BLK_TS_RD_MASK, "RCS_DMAC_CH2_BLK_TS_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_CTL_OFFSET, \
                                    RCS_DMAC_CH2_CTL_DEFAULT, \
                                    RCS_DMAC_CH2_CTL_RD_MASK, "RCS_DMAC_CH2_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_CFG_OFFSET, \
                                    RCS_DMAC_CH2_CFG_DEFAULT, \
                                    RCS_DMAC_CH2_CFG_RD_MASK, "RCS_DMAC_CH2_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_LLP_OFFSET, \
                                    RCS_DMAC_CH2_LLP_DEFAULT, \
                                    RCS_DMAC_CH2_LLP_RD_MASK, "RCS_DMAC_CH2_LLP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_STATREG_OFFSET, \
                                    RCS_DMAC_CH2_STATREG_DEFAULT, \
                                    RCS_DMAC_CH2_STATREG_RD_MASK, "RCS_DMAC_CH2_STATREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_SWHSSRCREG_OFFSET, \
                                    RCS_DMAC_CH2_SWHSSRCREG_DEFAULT, \
                                    RCS_DMAC_CH2_SWHSSRCREG_RD_MASK, "RCS_DMAC_CH2_SWHSSRCREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_SWHSDSTREG_OFFSET, \
                                    RCS_DMAC_CH2_SWHSDSTREG_DEFAULT, \
                                    RCS_DMAC_CH2_SWHSDSTREG_RD_MASK, "RCS_DMAC_CH2_SWHSDSTREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_BLK_TFR_RESUMEREQREG_OFFSET, \
                                    RCS_DMAC_CH2_BLK_TFR_RESUMEREQREG_DEFAULT, \
                                    RCS_DMAC_CH2_BLK_TFR_RESUMEREQREG_RD_MASK, "RCS_DMAC_CH2_BLK_TFR_RESUMEREQREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_IDREG_OFFSET, \
                                    RCS_DMAC_CH2_IDREG_DEFAULT, \
                                    RCS_DMAC_CH2_IDREG_RD_MASK, "RCS_DMAC_CH2_IDREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_QOSREG_OFFSET, \
                                    RCS_DMAC_CH2_QOSREG_DEFAULT, \
                                    RCS_DMAC_CH2_QOSREG_RD_MASK, "RCS_DMAC_CH2_QOSREG_OFFSET");
        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_INTSTAT_ENREG_OFFSET, \
                                    RCS_DMAC_CH2_INTSTAT_ENREG_DEFAULT, \
                                    RCS_DMAC_CH2_INTSTAT_ENREG_RD_MASK, "RCS_DMAC_CH2_INTSTAT_ENREG_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_INTSTAT_OFFSET, \
                                    RCS_DMAC_CH2_INTSTAT_DEFAULT, \
                                    RCS_DMAC_CH2_INTSTAT_RD_MASK, "RCS_DMAC_CH2_INTSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_INTSIGNAL_ENREG_OFFSET, \
                                    RCS_DMAC_CH2_INTSIGNAL_ENREG_DEFAULT, \
                                    RCS_DMAC_CH2_INTSIGNAL_ENREG_RD_MASK, "RCS_DMAC_CH2_INTSIGNAL_ENREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_INTCLRREG_OFFSET, \
                                    RCS_DMAC_CH2_INTCLRREG_DEFAULT, \
                                    RCS_DMAC_CH2_INTCLRREG_RD_MASK, "RCS_DMAC_CH2_INTCLRREG_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_DMAC_CH2_CFG_EXTD_OFFSET, \
                                    RCS_DMAC_CH2_CFG_EXTD_DEFAULT, \
                                    RCS_DMAC_CH2_CFG_EXTD_RD_MASK, "RCS_DMAC_CH2_CFG_EXTD_OFFSET");

    }

}
