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

    uint32_t base_address1[] = {
     ANT0_DDAC0_BASE,  ANT0_DDAC1_BASE,  ANT0_DDAC2_BASE,  ANT0_DDAC3_BASE,  ANT1_DDAC0_BASE,
     ANT1_DDAC1_BASE,  ANT1_DDAC2_BASE,  ANT1_DDAC3_BASE,  ANT2_DDAC0_BASE,  ANT2_DDAC1_BASE,
     ANT2_DDAC2_BASE,  ANT2_DDAC3_BASE,  ANT3_DDAC0_BASE,  ANT3_DDAC1_BASE,  ANT3_DDAC2_BASE,
    ANT3_DDAC3_BASE};

     uint32_t base_address2[] = { FB_ANT0_DDAC_TOP_BASE,  FB_ANT0_DDAC_BOT_BASE,  FB_ANT1_DDAC_TOP_BASE,  FB_ANT1_DDAC_BOT_BASE
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
                write_read_expect_18a(base_addresses[i][j]+DDAC_SCRATCH_OFFSET, \
                                        DDAC_SCRATCH_DEFAULT, write_data, expected_data, \
                                        DDAC_SCRATCH_RD_MASK, DDAC_SCRATCH_WR_MASK, \
                                        "DDAC_SCRATCH_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ0_CTRL_OFFSET, \
                                        DDAC_SEQ0_CTRL_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CTRL_RD_MASK, DDAC_SEQ0_CTRL_WR_MASK, \
                                        "DDAC_SEQ0_CTRL_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ0_ITER_OFFSET, \
                                        DDAC_SEQ0_ITER_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_ITER_RD_MASK, DDAC_SEQ0_ITER_WR_MASK, \
                                        "DDAC_SEQ0_ITER_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ0_STAT_OFFSET, \
                                        DDAC_SEQ0_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_STAT_RD_MASK, DDAC_SEQ0_STAT_WR_MASK, \
                                        "DDAC_SEQ0_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ1_CTRL_OFFSET, \
                                        DDAC_SEQ1_CTRL_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CTRL_RD_MASK, DDAC_SEQ1_CTRL_WR_MASK, \
                                        "DDAC_SEQ1_CTRL_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ1_ITER_OFFSET, \
                                        DDAC_SEQ1_ITER_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_ITER_RD_MASK, DDAC_SEQ1_ITER_WR_MASK, \
                                        "DDAC_SEQ1_ITER_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ1_STAT_OFFSET, \
                                        DDAC_SEQ1_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_STAT_RD_MASK, DDAC_SEQ1_STAT_WR_MASK, \
                                        "DDAC_SEQ1_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SL_TCTL_OFFSET, \
                                        DDAC_SL_TCTL_DEFAULT, write_data, expected_data, \
                                        DDAC_SL_TCTL_RD_MASK, DDAC_SL_TCTL_WR_MASK, \
                                        "DDAC_SL_TCTL_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF0_OFFSET, \
                                        DDAC_TX_ENCX_CONF0_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF0_RD_MASK, DDAC_TX_ENCX_CONF0_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF1_OFFSET, \
                                        DDAC_TX_ENCX_CONF1_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF1_RD_MASK, DDAC_TX_ENCX_CONF1_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF2_OFFSET, \
                                        DDAC_TX_ENCX_CONF2_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF2_RD_MASK, DDAC_TX_ENCX_CONF2_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF3_OFFSET, \
                                        DDAC_TX_ENCX_CONF3_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF3_RD_MASK, DDAC_TX_ENCX_CONF3_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF4_OFFSET, \
                                        DDAC_TX_ENCX_CONF4_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF4_RD_MASK, DDAC_TX_ENCX_CONF4_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF5_OFFSET, \
                                        DDAC_TX_ENCX_CONF5_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF5_RD_MASK, DDAC_TX_ENCX_CONF5_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF6_OFFSET, \
                                        DDAC_TX_ENCX_CONF6_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF6_RD_MASK, DDAC_TX_ENCX_CONF6_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF7_OFFSET, \
                                        DDAC_TX_ENCX_CONF7_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF7_RD_MASK, DDAC_TX_ENCX_CONF7_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF7_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_ENCX_CONF8_OFFSET, \
                                        DDAC_TX_ENCX_CONF8_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_ENCX_CONF8_RD_MASK, DDAC_TX_ENCX_CONF8_WR_MASK, \
                                        "DDAC_TX_ENCX_CONF8_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF0_OFFSET, \
                                        DDAC_TX_DAC_CONF0_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF0_RD_MASK, DDAC_TX_DAC_CONF0_WR_MASK, \
                                        "DDAC_TX_DAC_CONF0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF1_OFFSET, \
                                        DDAC_TX_DAC_CONF1_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF1_RD_MASK, DDAC_TX_DAC_CONF1_WR_MASK, \
                                        "DDAC_TX_DAC_CONF1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF2_OFFSET, \
                                        DDAC_TX_DAC_CONF2_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF2_RD_MASK, DDAC_TX_DAC_CONF2_WR_MASK, \
                                        "DDAC_TX_DAC_CONF2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF3_OFFSET, \
                                        DDAC_TX_DAC_CONF3_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF3_RD_MASK, DDAC_TX_DAC_CONF3_WR_MASK, \
                                        "DDAC_TX_DAC_CONF3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF4_OFFSET, \
                                        DDAC_TX_DAC_CONF4_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF4_RD_MASK, DDAC_TX_DAC_CONF4_WR_MASK, \
                                        "DDAC_TX_DAC_CONF4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF5_OFFSET, \
                                        DDAC_TX_DAC_CONF5_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF5_RD_MASK, DDAC_TX_DAC_CONF5_WR_MASK, \
                                        "DDAC_TX_DAC_CONF5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_TX_DAC_CONF6_OFFSET, \
                                        DDAC_TX_DAC_CONF6_DEFAULT, write_data, expected_data, \
                                        DDAC_TX_DAC_CONF6_RD_MASK, DDAC_TX_DAC_CONF6_WR_MASK, \
                                        "DDAC_TX_DAC_CONF6_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI0_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI1_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI2_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI3_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI4_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPI5_OFFSET, \
                                        DDAC_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPI_RD_MASK, DDAC_CSAPI_WR_MASK, \
                                        "DDAC_CSAPI5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO0_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO0_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO1_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO1_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO2_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO2_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO3_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO3_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO4_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO4_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_CSAPO5_OFFSET, \
                                        DDAC_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_CSAPO_RD_MASK, DDAC_CSAPO_WR_MASK, \
                                        "DDAC_CSAPO5_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_DSAS_OFFSET, \
                                        DDAC_DSAS_DEFAULT, write_data, expected_data, \
                                        DDAC_DSAS_RD_MASK, DDAC_DSAS_WR_MASK, \
                                        "DDAC_DSAS_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_DSAL_OFFSET, \
                                        DDAC_DSAL_DEFAULT, write_data, expected_data, \
                                        DDAC_DSAL_RD_MASK, DDAC_DSAL_WR_MASK, \
                                        "DDAC_DSAL_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_DSA_FG_OFFSET, \
                                        DDAC_DSA_FG_DEFAULT, write_data, expected_data, \
                                        DDAC_DSA_FG_RD_MASK, DDAC_DSA_FG_WR_MASK, \
                                        "DDAC_DSA_FG_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_STAT_OFFSET, \
                                        DDAC_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_STAT_RD_MASK, DDAC_STAT_WR_MASK, \
                                        "DDAC_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ00_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ00_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ00_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ00_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ01_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ01_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ01_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ01_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ02_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ02_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ02_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ02_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ03_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ03_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ03_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ03_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ04_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ04_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ04_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ04_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ05_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ05_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ05_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ05_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ06_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ06_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ06_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ06_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ07_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ07_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ07_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ07_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ08_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ08_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ08_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ08_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ09_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ09_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ09_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ09_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ010_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ010_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ010_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ010_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ011_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ011_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ011_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ011_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ012_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ012_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ012_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ012_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ013_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ013_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ013_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ013_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ014_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ014_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ014_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ014_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ015_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ015_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ015_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ015_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ016_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ016_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ016_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ016_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ017_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ017_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ017_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ017_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ018_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ018_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ018_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ018_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ019_SEQ0_CMD_DATA_OFFSET, \
                                        DDAC_SEQ0_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_DATA_RD_MASK, DDAC_SEQ0_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ019_SEQ0_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ019_SEQ0_CMD_AW_OFFSET, \
                                        DDAC_SEQ0_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ0_CMD_AW_RD_MASK, DDAC_SEQ0_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ019_SEQ0_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ10_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ10_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ10_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ10_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ11_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ11_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ11_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ11_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ12_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ12_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ12_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ12_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ13_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ13_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ13_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ13_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ14_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ14_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ14_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ14_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ15_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ15_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ15_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ15_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ16_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ16_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ16_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ16_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ17_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ17_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ17_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ17_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ18_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ18_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ18_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ18_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ19_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ19_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ19_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ19_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ110_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ110_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ110_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ110_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ111_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ111_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ111_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ111_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ112_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ112_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ112_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ112_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ113_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ113_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ113_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ113_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ114_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ114_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ114_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ114_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ115_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ115_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ115_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ115_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ116_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ116_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ116_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ116_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ117_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ117_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ117_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ117_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ118_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ118_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ118_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ118_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ119_SEQ1_CMD_DATA_OFFSET, \
                                        DDAC_SEQ1_CMD_DATA_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_DATA_RD_MASK, DDAC_SEQ1_CMD_DATA_WR_MASK, \
                                        "DDAC_SEQ119_SEQ1_CMD_DATA_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SEQ119_SEQ1_CMD_AW_OFFSET, \
                                        DDAC_SEQ1_CMD_AW_DEFAULT, write_data, expected_data, \
                                        DDAC_SEQ1_CMD_AW_RD_MASK, DDAC_SEQ1_CMD_AW_WR_MASK, \
                                        "DDAC_SEQ119_SEQ1_CMD_AW_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_SL_TSTAT_OFFSET, \
                                        DDAC_SL_TSTAT_DEFAULT, write_data, expected_data, \
                                        DDAC_SL_TSTAT_RD_MASK, DDAC_SL_TSTAT_WR_MASK, \
                                        "DDAC_SL_TSTAT_OFFSET");
    //Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
    //            write_read_expect_18a(base_addresses[i][j]+DDAC_COLL_STAT_OFFSET, \
                                        DDAC_COLL_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_COLL_STAT_RD_MASK, DDAC_COLL_STAT_WR_MASK, \
                                        "DDAC_COLL_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_SEQ0A_OFFSET, \
                                        DDAC_PAR_ERR_SEQ0A_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_SEQ0A_RD_MASK, DDAC_PAR_ERR_SEQ0A_WR_MASK, \
                                        "DDAC_PAR_ERR_SEQ0A_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_SEQ0D_OFFSET, \
                                        DDAC_PAR_ERR_SEQ0D_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_SEQ0D_RD_MASK, DDAC_PAR_ERR_SEQ0D_WR_MASK, \
                                        "DDAC_PAR_ERR_SEQ0D_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_SEQ1A_OFFSET, \
                                        DDAC_PAR_ERR_SEQ1A_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_SEQ1A_RD_MASK, DDAC_PAR_ERR_SEQ1A_WR_MASK, \
                                        "DDAC_PAR_ERR_SEQ1A_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_SEQ1D_OFFSET, \
                                        DDAC_PAR_ERR_SEQ1D_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_SEQ1D_RD_MASK, DDAC_PAR_ERR_SEQ1D_WR_MASK, \
                                        "DDAC_PAR_ERR_SEQ1D_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_CSAPI_OFFSET, \
                                        DDAC_PAR_ERR_CSAPI_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_CSAPI_RD_MASK, DDAC_PAR_ERR_CSAPI_WR_MASK, \
                                        "DDAC_PAR_ERR_CSAPI_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_CSAPO_OFFSET, \
                                        DDAC_PAR_ERR_CSAPO_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_CSAPO_RD_MASK, DDAC_PAR_ERR_CSAPO_WR_MASK, \
                                        "DDAC_PAR_ERR_CSAPO_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_TX_ENCX_OFFSET, \
                                        DDAC_PAR_ERR_TX_ENCX_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_TX_ENCX_RD_MASK, DDAC_PAR_ERR_TX_ENCX_WR_MASK, \
                                        "DDAC_PAR_ERR_TX_ENCX_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_PAR_ERR_TX_DAC_OFFSET, \
                                        DDAC_PAR_ERR_TX_DAC_DEFAULT, write_data, expected_data, \
                                        DDAC_PAR_ERR_TX_DAC_RD_MASK, DDAC_PAR_ERR_TX_DAC_WR_MASK, \
                                        "DDAC_PAR_ERR_TX_DAC_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_INT_STAT_OFFSET, \
                                        DDAC_INT_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_INT_STAT_RD_MASK, DDAC_INT_STAT_WR_MASK, \
                                        "DDAC_INT_STAT_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_INT_HI_EN_OFFSET, \
                                        DDAC_INT_HI_EN_DEFAULT, write_data, expected_data, \
                                        DDAC_INT_HI_EN_RD_MASK, DDAC_INT_HI_EN_WR_MASK, \
                                        "DDAC_INT_HI_EN_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_INT_LO_EN_OFFSET, \
                                        DDAC_INT_LO_EN_DEFAULT, write_data, expected_data, \
                                        DDAC_INT_LO_EN_RD_MASK, DDAC_INT_LO_EN_WR_MASK, \
                                        "DDAC_INT_LO_EN_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_INT_CLR_OFFSET, \
                                        DDAC_INT_CLR_DEFAULT, write_data, expected_data, \
                                        DDAC_INT_CLR_RD_MASK, DDAC_INT_CLR_WR_MASK, \
                                        "DDAC_INT_CLR_OFFSET");

                write_read_expect_18a(base_addresses[i][j]+DDAC_INT_FORCE_OFFSET, \
                                        DDAC_INT_FORCE_DEFAULT, write_data, expected_data, \
                                        DDAC_INT_FORCE_RD_MASK, DDAC_INT_FORCE_WR_MASK, \
                                        "DDAC_INT_FORCE_OFFSET");
    //Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
    //            write_read_expect_18a(base_addresses[i][j]+DDAC_APB_BRDG_STAT_OFFSET, \
                                        DDAC_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                        DDAC_APB_BRDG_STAT_RD_MASK, DDAC_APB_BRDG_STAT_WR_MASK, \
                                        "DDAC_APB_BRDG_STAT_OFFSET");
            }

        }

    }

}
