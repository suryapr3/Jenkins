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
    DLNK_PCIE_DWC_IDE_HCFG_APB_BASE
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


        for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
        {
            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_NUM_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_NUM_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_NUM_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_NUM_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_NUM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_TYPE_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_TYPE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_TYPE_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_TYPE_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_CORE_VER_TYPE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_GLBL_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_GLBL_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_GLBL_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_GLBL_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_GLBL_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_SYNC_MSG_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_SYNC_MSG_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_SYNC_MSG_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_SYNC_MSG_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_SYNC_MSG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_LINK_TBIT_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LINK_TBIT_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LINK_TBIT_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_LINK_TBIT_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_LINK_TBIT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_SLT_TBIT1_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_TBIT1_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_TBIT1_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_SLT_TBIT1_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_SLT_TBIT1_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT1_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT1_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT1_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT1_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT1_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT1_CFG_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT1_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT1_CFG_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT1_CFG_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT1_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_KEY_THRESH_EN_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_THRESH_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_THRESH_EN_RD_MASK, PCIE_IDE_ID_IDE_CFG_KEY_THRESH_EN_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_KEY_THRESH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_REKEY_REQ_STAT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_REKEY_REQ_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_REKEY_REQ_STAT_RD_MASK, PCIE_IDE_ID_IDE_CFG_REKEY_REQ_STAT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_REKEY_REQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_LOW_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_TSHOLD_HIGH_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_LOW_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_TSHOLD_HIGH_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_STAT_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_CNTER_OVERFLOW_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CNTER_OVERFLOW_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_CNTER_OVERFLOW_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_CNTER_OVERFLOW_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_CNTER_OVERFLOW_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_IRQ_EN_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_IRQ_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_IRQ_EN_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_IRQ_EN_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_IRQ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_IRQ_EN_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_IRQ_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_IRQ_EN_RD_MASK, PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_IRQ_EN_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_KEY_SECURITY_IRQ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_IO_IRQ_STAT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_IO_IRQ_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_IO_IRQ_STAT_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_IO_IRQ_STAT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_IO_IRQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_LNK_SND_STRM_INSECURE_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_LNK_SND_STRM_INSECURE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_LNK_SND_STRM_INSECURE_RD_MASK, PCIE_IDE_ID_IDE_CFG_LNK_SND_STRM_INSECURE_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_LNK_SND_STRM_INSECURE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_SLT_SND_STRM_INSECURE_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_SLT_SND_STRM_INSECURE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_SLT_SND_STRM_INSECURE_RD_MASK, PCIE_IDE_ID_IDE_CFG_SLT_SND_STRM_INSECURE_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_SLT_SND_STRM_INSECURE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_TOGGLED_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_TOGGLED_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_TOGGLED_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_TOGGLED_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_LNK_KBIT_TOGGLED_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_TOGGLED_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_TOGGLED_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_TOGGLED_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_TOGGLED_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_TOGGLED_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CURRENT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CURRENT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CURRENT_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CURRENT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_LNK_KBIT_CURRENT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT_TOGGLED_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT_TOGGLED_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT_TOGGLED_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT_TOGGLED_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_SLT_KBIT_TOGGLED_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_TOGGLED_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_TOGGLED_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_TOGGLED_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_TOGGLED_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_TOGGLED_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_CURRENT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_CURRENT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_CURRENT_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_CURRENT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_SLT_KBIT_CURRENT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S0_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_LOW_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_TX_KEY_USAGE_CNTER_HIGH_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_LOW_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S1_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S1_RD_MASK, PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S1_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_RX_KEY_USAGE_CNTER_HIGH_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_MASK_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_MASK_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_MASK_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_CNT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_CNT_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_CNT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_TX_PCRC_ERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_MASK_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_MASK_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_MASK_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_CNT_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_CNT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_CNT_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_CNT_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_RX_PCRC_ERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_TDISP_ON_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TDISP_ON_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_TDISP_ON_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_TDISP_ON_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_TDISP_ON_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_DISCARD_OVRD_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_DISCARD_OVRD_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_DISCARD_OVRD_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_DISCARD_OVRD_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_DISCARD_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CFG_IDE_MSG_ON_SELIVE_EN_OFFSET, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_MSG_ON_SELIVE_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CFG_IDE_MSG_ON_SELIVE_EN_RD_MASK, PCIE_IDE_ID_IDE_CFG_IDE_MSG_ON_SELIVE_EN_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CFG_IDE_MSG_ON_SELIVE_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_EXT_CAP_HDR_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_EXT_CAP_HDR_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_EXT_CAP_HDR_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_EXT_CAP_HDR_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_EXT_CAP_HDR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_CAP_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_CAP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_CAP_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_CAP_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_CAP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_CTRL_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_CTRL_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_CTRL_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STRM_CTRL_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STRM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STRM_CTRL_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STRM_CTRL_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STRM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STAT_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STAT_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STAT_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STAT_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_LINK_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CAP_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CAP_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CAP_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CAP_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CAP_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CTRL_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CTRL_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CTRL_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_STAT_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_STAT_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_STAT_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_STAT_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_SLCT_IDE_STRM_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG1_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG1_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG1_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG1_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG2_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG2_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG2_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG2_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_RID_ASSOS_REG2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG1_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG1_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG1_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG1_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG1_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG2_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG2_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG2_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG2_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG2_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG3_0_OFFSET, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG3_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG3_0_RD_MASK, PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG3_0_WR_MASK, \
                                    "PCIE_IDE_ID_IDE_CAPS_IDE_ADDR_ASSOS_REG3_0_OFFSET");

        }

    }

}
