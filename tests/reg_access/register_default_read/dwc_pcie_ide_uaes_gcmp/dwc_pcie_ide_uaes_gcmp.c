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
    DLNK_PCIE_DWC_IDE_UAES_GCMP_APB_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_NUM_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CORE_VER_TYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_KEY_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_LSW_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_INITIAL_IV_MSW_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_LINK_DIS_STRM_KEYS_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_HOST_AES_TX_SELIVE_DIS_STRM_KEYS_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_SOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_EOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CTR_IV_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_AAD_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_MSG_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_CTX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_CMD_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_CMD_AES_TX_TEST_MODE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_IN_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_INPUT_AES_TX_DATA_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_SOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_EOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_AAD_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MSG_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_DATA_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_OUTPUT_AES_TX_OUT_MAC_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_TX_FIPS_SEL_AES_TX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_NUM_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CORE_VER_TYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_IRQ_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_KEY_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_LSW_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_INITIAL_IV_MSW_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_LINK_DIS_STRM_KEYS_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_HOST_AES_RX_SELIVE_DIS_STRM_KEYS_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_SOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_EOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CTR_IV_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_AAD_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_MSG_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_CTX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_CMD_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_CMD_AES_RX_TEST_MODE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_IN_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_INPUT_AES_RX_DATA_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_READY_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_VALID_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_SOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_EOP_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_AAD_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MSG_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_DATA_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_OUTPUT_AES_RX_OUT_MAC_CHUNK_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_AES_RX_FIPS_SEL_AES_RX_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_STAT_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_STAT_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_STAT_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_0_31_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_TX_32_63_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_0_31_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_TIMESTAMP_RX1_32_63_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_ERR_LOG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_0_31_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_TX_32_63_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_0_31_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_OFFSET, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_DEFAULT, \
                                    PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_RD_MASK, "PCIE_IDE_UAES_GCMP_ID_BIST_LOG_TIMESTAMP_RX1_32_63_OFFSET");

    }

}
