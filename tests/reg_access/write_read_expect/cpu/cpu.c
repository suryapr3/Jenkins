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
    ANT0_CPU_BASE, ANT1_CPU_BASE, ANT2_CPU_BASE, ANT3_CPU_BASE
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
            write_read_expect_18a(base_address[i]+CPU_SCRATCH_OFFSET, \
                                    CPU_SCRATCH_DEFAULT, write_data, expected_data, \
                                    CPU_SCRATCH_RD_MASK, CPU_SCRATCH_WR_MASK, \
                                    "CPU_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_CTRL_OFFSET, \
                                    CPU_ADC_CPU_CTRL_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_CTRL_RD_MASK, CPU_ADC_CPU_CTRL_WR_MASK, \
                                    "CPU_ADC_CPU_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_DBG_CTRL_OFFSET, \
                                    CPU_ADC_CPU_DBG_CTRL_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_DBG_CTRL_RD_MASK, CPU_ADC_CPU_DBG_CTRL_WR_MASK, \
                                    "CPU_ADC_CPU_DBG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_EN_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_EN_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_EN_RD_MASK, CPU_ADC_CPU_TP_PDBG_EN_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_RCS_START_CAL_OFFSET, \
                                    CPU_RCS_START_CAL_DEFAULT, write_data, expected_data, \
                                    CPU_RCS_START_CAL_RD_MASK, CPU_RCS_START_CAL_WR_MASK, \
                                    "CPU_RCS_START_CAL_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ATSA_START_CAL_OFFSET, \
                                    CPU_ATSA_START_CAL_DEFAULT, write_data, expected_data, \
                                    CPU_ATSA_START_CAL_RD_MASK, CPU_ATSA_START_CAL_WR_MASK, \
                                    "CPU_ATSA_START_CAL_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_CPU2RCS_MAILBOX_OFFSET, \
                                    CPU_CPU2RCS_MAILBOX_DEFAULT, write_data, expected_data, \
                                    CPU_CPU2RCS_MAILBOX_RD_MASK, CPU_CPU2RCS_MAILBOX_WR_MASK, \
                                    "CPU_CPU2RCS_MAILBOX_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_RCS2CPU_MAILBOX_OFFSET, \
                                    CPU_RCS2CPU_MAILBOX_DEFAULT, write_data, expected_data, \
                                    CPU_RCS2CPU_MAILBOX_RD_MASK, CPU_RCS2CPU_MAILBOX_WR_MASK, \
                                    "CPU_RCS2CPU_MAILBOX_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CAL_TIME_INT0_OFFSET, \
                                    CPU_ADC_CAL_TIME_INT0_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CAL_TIME_INT0_RD_MASK, CPU_ADC_CAL_TIME_INT0_WR_MASK, \
                                    "CPU_ADC_CAL_TIME_INT0_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CAL_TIME_INT1_OFFSET, \
                                    CPU_ADC_CAL_TIME_INT1_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CAL_TIME_INT1_RD_MASK, CPU_ADC_CAL_TIME_INT1_WR_MASK, \
                                    "CPU_ADC_CAL_TIME_INT1_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CAL_TIME_INT2_OFFSET, \
                                    CPU_ADC_CAL_TIME_INT2_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CAL_TIME_INT2_RD_MASK, CPU_ADC_CAL_TIME_INT2_WR_MASK, \
                                    "CPU_ADC_CAL_TIME_INT2_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CAL_TIME_INT3_OFFSET, \
                                    CPU_ADC_CAL_TIME_INT3_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CAL_TIME_INT3_RD_MASK, CPU_ADC_CAL_TIME_INT3_WR_MASK, \
                                    "CPU_ADC_CAL_TIME_INT3_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_STAT_OFFSET, \
                                    CPU_ADC_CPU_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_STAT_RD_MASK, CPU_ADC_CPU_STAT_WR_MASK, \
                                    "CPU_ADC_CPU_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_DBG_STAT_OFFSET, \
                                    CPU_ADC_CPU_DBG_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_DBG_STAT_RD_MASK, CPU_ADC_CPU_DBG_STAT_WR_MASK, \
                                    "CPU_ADC_CPU_DBG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_DATA_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_DATA_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_DATA_RD_MASK, CPU_ADC_CPU_TP_PDBG_DATA_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_INST_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_INST_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_INST_RD_MASK, CPU_ADC_CPU_TP_PDBG_INST_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_INST_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_INBPIF_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_INBPIF_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_INBPIF_RD_MASK, CPU_ADC_CPU_TP_PDBG_INBPIF_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_INBPIF_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_LS0STAT_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_LS0STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_LS0STAT_RD_MASK, CPU_ADC_CPU_TP_PDBG_LS0STAT_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_LS0STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_PC_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_PC_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_PC_RD_MASK, CPU_ADC_CPU_TP_PDBG_PC_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_PC_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_TP_PDBG_STAT_OFFSET, \
                                    CPU_ADC_CPU_TP_PDBG_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_TP_PDBG_STAT_RD_MASK, CPU_ADC_CPU_TP_PDBG_STAT_WR_MASK, \
                                    "CPU_ADC_CPU_TP_PDBG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_PFAULT_INFO_MSB_OFFSET, \
                                    CPU_ADC_CPU_PFAULT_INFO_MSB_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_PFAULT_INFO_MSB_RD_MASK, CPU_ADC_CPU_PFAULT_INFO_MSB_WR_MASK, \
                                    "CPU_ADC_CPU_PFAULT_INFO_MSB_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_PFAULT_INFO_LSB_OFFSET, \
                                    CPU_ADC_CPU_PFAULT_INFO_LSB_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_PFAULT_INFO_LSB_RD_MASK, CPU_ADC_CPU_PFAULT_INFO_LSB_WR_MASK, \
                                    "CPU_ADC_CPU_PFAULT_INFO_LSB_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_MEM_ERR_STAT_OFFSET, \
                                    CPU_ADC_CPU_MEM_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_MEM_ERR_STAT_RD_MASK, CPU_ADC_CPU_MEM_ERR_STAT_WR_MASK, \
                                    "CPU_ADC_CPU_MEM_ERR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ADC_CPU_MEM_ERR_CLR_OFFSET, \
                                    CPU_ADC_CPU_MEM_ERR_CLR_DEFAULT, write_data, expected_data, \
                                    CPU_ADC_CPU_MEM_ERR_CLR_RD_MASK, CPU_ADC_CPU_MEM_ERR_CLR_WR_MASK, \
                                    "CPU_ADC_CPU_MEM_ERR_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_APB_BRDG_STAT_OFFSET, \
                                    CPU_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_APB_BRDG_STAT_RD_MASK, CPU_APB_BRDG_STAT_WR_MASK, \
                                    "CPU_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ANT_INT_STAT_OFFSET, \
                                    CPU_ANT_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CPU_ANT_INT_STAT_RD_MASK, CPU_ANT_INT_STAT_WR_MASK, \
                                    "CPU_ANT_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ANT_INT_HIGH_EN_OFFSET, \
                                    CPU_ANT_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    CPU_ANT_INT_HIGH_EN_RD_MASK, CPU_ANT_INT_HIGH_EN_WR_MASK, \
                                    "CPU_ANT_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ANT_INT_LOW_EN_OFFSET, \
                                    CPU_ANT_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    CPU_ANT_INT_LOW_EN_RD_MASK, CPU_ANT_INT_LOW_EN_WR_MASK, \
                                    "CPU_ANT_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ANT_INT_CLR_OFFSET, \
                                    CPU_ANT_INT_CLR_DEFAULT, write_data, expected_data, \
                                    CPU_ANT_INT_CLR_RD_MASK, CPU_ANT_INT_CLR_WR_MASK, \
                                    "CPU_ANT_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+CPU_ANT_INT_FORCE_OFFSET, \
                                    CPU_ANT_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    CPU_ANT_INT_FORCE_RD_MASK, CPU_ANT_INT_FORCE_WR_MASK, \
                                    "CPU_ANT_INT_FORCE_OFFSET");

        }

    }

}
