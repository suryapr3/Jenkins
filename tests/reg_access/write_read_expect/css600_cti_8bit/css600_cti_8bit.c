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
    VEXARRAYCS8_0_CTI8BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_1_CTI8BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_2_CTI8BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_3_CTI8BIT_APB4_SLAVE_0_MM_BASE, RCS_CS_CTI8BIT_APB4_SLAVE_0_MM_BASE
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
            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTICTRL_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICTRL_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTICTRL_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTICTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINTACK_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINTACK_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINTACK_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINTACK_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINTACK_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPSET_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPSET_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPSET_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPSET_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPSET_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPCLR_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPCLR_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPCLR_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPCLR_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPCLR_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPPULSE_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPPULSE_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPPULSE_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN0_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN0_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN0_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN0_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN1_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN1_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN1_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN1_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN2_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN2_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN2_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN2_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN3_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN3_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN3_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN3_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN4_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN4_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN4_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN4_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN5_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN5_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN5_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN5_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN6_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN6_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN6_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN6_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN7_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN7_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN7_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN7_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIINEN7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN0_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN0_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN0_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN0_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN1_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN1_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN1_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN1_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN2_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN2_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN2_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN2_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN3_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN3_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN3_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN3_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN4_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN4_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN4_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN4_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN5_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN5_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN5_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN5_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN6_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN6_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN6_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN6_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN7_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN7_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN7_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN7_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIOUTEN7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGINSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGINSTAT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGINSTAT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGOUTSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGOUTSTAT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGOUTSTAT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTICHINSTAT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICHINSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICHINSTAT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTICHINSTAT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTICHINSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICHOUTSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTICHOUTSTAT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTICHOUTSTAT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CTIGATE_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIGATE_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CTIGATE_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CTIGATE_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CTIGATE_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ASICCTRL_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ASICCTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ASICCTRL_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ASICCTRL_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ASICCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ITCHOUT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCHOUT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCHOUT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ITCHOUT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ITCHOUT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGOUT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGOUT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGOUT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGOUT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGOUT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ITCHIN_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCHIN_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCHIN_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ITCHIN_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ITCHIN_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGIN_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGIN_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGIN_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGIN_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ITTRIGIN_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_ITCTRL_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_ITCTRL_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_ITCTRL_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_ITCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CLAIMSET_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CLAIMSET_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CLAIMSET_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CLAIMSET_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CLAIMSET_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CLAIMCLR_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CLAIMCLR_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CLAIMCLR_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CLAIMCLR_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CLAIMCLR_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF0_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF0_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF0_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF0_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF1_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF1_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF1_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF1_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_DEVAFF1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_AUTHSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_AUTHSTAT_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_AUTHSTAT_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_AUTHSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVARCH_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVARCH_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_DEVARCH_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_DEVARCH_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVID_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVID_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_DEVID_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_DEVID_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_DEVTYPE_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVTYPE_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_DEVTYPE_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_DEVTYPE_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_DEVTYPE_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR4_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR4_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR4_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR5_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR5_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR5_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR6_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR6_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR6_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR7_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR7_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR7_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR0_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR0_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR1_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR1_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR2_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR2_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_PIDR3_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_PIDR3_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_PIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR0_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CIDR0_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR1_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CIDR1_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR2_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CIDR2_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_CTI_8BIT_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_CTI_8BIT_ADDRBLK_0_CIDR3_RD_MASK, CSS600_CTI_8BIT_ADDRBLK_0_CIDR3_WR_MASK, \
                                    "CSS600_CTI_8BIT_ADDRBLK_0_CIDR3_OFFSET");

        }

    }

}
