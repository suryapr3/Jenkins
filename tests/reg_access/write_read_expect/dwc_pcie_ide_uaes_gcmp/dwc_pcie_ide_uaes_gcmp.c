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
    DLNK_PCIE_DWC_IDE_UAES_GCMP_APB_BASE
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
            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_RD_MASK, PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_STAT_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_STAT_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_DEFAULT, write_data, expected_data, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_RD_MASK, PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_WR_MASK, \
                                    "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_OFFSET");

        }

    }

}
