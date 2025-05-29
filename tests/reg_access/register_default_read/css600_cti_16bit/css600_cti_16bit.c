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
    VEXARRAYCS16_00_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_01_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_10_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_11_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_20_CTI16BIT_APB4_SLAVE_0_MM_BASE,
    VEXARRAYCS16_21_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_30_CTI16BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_31_CTI16BIT_APB4_SLAVE_0_MM_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTICTRL_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICTRL_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICTRL_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTICTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINTACK_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINTACK_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINTACK_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINTACK_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN0_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN0_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN1_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN1_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN2_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN2_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN3_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN3_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN4_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN4_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN5_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN5_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN6_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN6_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN7_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN7_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN8_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN8_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN8_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN9_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN9_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN9_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN10_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN10_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN10_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN11_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN11_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN11_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN12_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN12_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN12_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN13_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN13_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN13_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN14_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN14_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN14_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN15_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN15_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIINEN15_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CTIGATE_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIGATE_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CTIGATE_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CTIGATE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ASICCTRL_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ASICCTRL_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ASICCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ITCHOUT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCHOUT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ITCHOUT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ITCHIN_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCHIN_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCHIN_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ITCHIN_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_ITCTRL_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCTRL_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_ITCTRL_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_ITCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CLAIMSET_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CLAIMSET_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CLAIMSET_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF0_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF0_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF0_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF1_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF1_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF1_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_DEVAFF1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVARCH_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVARCH_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_DEVARCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVID_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVID_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_DEVID_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_DEVTYPE_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVTYPE_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_DEVTYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR4_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR4_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR5_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR5_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR6_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR6_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR7_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR7_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR0_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR0_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR1_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR1_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR2_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR2_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR3_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_PIDR3_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_PIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR0_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR0_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR1_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR1_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR2_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR2_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_CTI_16BIT_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR3_DEFAULT, \
                                    CSS600_CTI_16BIT_ADDRBLK_0_CIDR3_RD_MASK, "CSS600_CTI_16BIT_ADDRBLK_0_CIDR3_OFFSET");

    }

}
