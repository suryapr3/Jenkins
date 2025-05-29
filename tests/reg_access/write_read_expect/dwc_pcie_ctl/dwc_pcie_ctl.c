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
    DLNK_PCIE_DWC_DBI_USP_BASE
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
            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DEVICE_ID_VENDOR_ID_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DEVICE_ID_VENDOR_ID_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DEVICE_ID_VENDOR_ID_RD_MASK, PCIE_CTL_TYPE0_HDR_DEVICE_ID_VENDOR_ID_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DEVICE_ID_VENDOR_ID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_STAT_CMD_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_STAT_CMD_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_STAT_CMD_RD_MASK, PCIE_CTL_TYPE0_HDR_STAT_CMD_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_STAT_CMD_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_CLASS_CODE_REVISION_ID_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_CLASS_CODE_REVISION_ID_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_CLASS_CODE_REVISION_ID_RD_MASK, PCIE_CTL_TYPE0_HDR_CLASS_CODE_REVISION_ID_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_CLASS_CODE_REVISION_ID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_RD_MASK, PCIE_CTL_TYPE0_HDR_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BIST_HEADER_TYPE_LATENCY_CACHE_LINE_SIZE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR0_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR0_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR0_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR1_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR1_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR1_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR2_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR2_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR2_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR3_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR3_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR3_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR4_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR4_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR4_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_BAR5_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_BAR5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_BAR5_RD_MASK, PCIE_CTL_TYPE0_HDR_BAR5_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_BAR5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_CARDBUS_CIS_PTR_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_CARDBUS_CIS_PTR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_CARDBUS_CIS_PTR_RD_MASK, PCIE_CTL_TYPE0_HDR_CARDBUS_CIS_PTR_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_CARDBUS_CIS_PTR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_SUBSYS_ID_SUBSYS_VENDOR_ID_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_SUBSYS_ID_SUBSYS_VENDOR_ID_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_SUBSYS_ID_SUBSYS_VENDOR_ID_RD_MASK, PCIE_CTL_TYPE0_HDR_SUBSYS_ID_SUBSYS_VENDOR_ID_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_SUBSYS_ID_SUBSYS_VENDOR_ID_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_EXP_ROM_BASE_ADDR_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_EXP_ROM_BASE_ADDR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_EXP_ROM_BASE_ADDR_RD_MASK, PCIE_CTL_TYPE0_HDR_EXP_ROM_BASE_ADDR_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_EXP_ROM_BASE_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_PCI_CAP_PTR_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_PCI_CAP_PTR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_PCI_CAP_PTR_RD_MASK, PCIE_CTL_TYPE0_HDR_PCI_CAP_PTR_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_PCI_CAP_PTR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_MAX_LATENCY_MIN_GRANT_INTR_PIN_INTR_LINE_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_MAX_LATENCY_MIN_GRANT_INTR_PIN_INTR_LINE_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_MAX_LATENCY_MIN_GRANT_INTR_PIN_INTR_LINE_RD_MASK, PCIE_CTL_TYPE0_HDR_MAX_LATENCY_MIN_GRANT_INTR_PIN_INTR_LINE_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_MAX_LATENCY_MIN_GRANT_INTR_PIN_INTR_LINE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PM_CAP_ID_NXT_PTR_OFFSET, \
                                    PCIE_CTL_PM_CAP_ID_NXT_PTR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PM_CAP_ID_NXT_PTR_RD_MASK, PCIE_CTL_PM_CAP_ID_NXT_PTR_WR_MASK, \
                                    "PCIE_CTL_PM_CAP_ID_NXT_PTR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PM_CAP_CON_STAT_OFFSET, \
                                    PCIE_CTL_PM_CAP_CON_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PM_CAP_CON_STAT_RD_MASK, PCIE_CTL_PM_CAP_CON_STAT_WR_MASK, \
                                    "PCIE_CTL_PM_CAP_CON_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_PCI_MSI_CAP_ID_NEXT_CTRL_OFFSET, \
                                    PCIE_CTL_MSI_CAP_PCI_MSI_CAP_ID_NEXT_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_PCI_MSI_CAP_ID_NEXT_CTRL_RD_MASK, PCIE_CTL_MSI_CAP_PCI_MSI_CAP_ID_NEXT_CTRL_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_PCI_MSI_CAP_ID_NEXT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_MSI_CAP_OFF_04H_OFFSET, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_04H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_04H_RD_MASK, PCIE_CTL_MSI_CAP_MSI_CAP_OFF_04H_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_MSI_CAP_OFF_04H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_MSI_CAP_OFF_08H_OFFSET, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_08H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_08H_RD_MASK, PCIE_CTL_MSI_CAP_MSI_CAP_OFF_08H_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_MSI_CAP_OFF_08H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_MSI_CAP_OFF_0CH_OFFSET, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_0CH_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_0CH_RD_MASK, PCIE_CTL_MSI_CAP_MSI_CAP_OFF_0CH_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_MSI_CAP_OFF_0CH_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_MSI_CAP_OFF_10H_OFFSET, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_10H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_10H_RD_MASK, PCIE_CTL_MSI_CAP_MSI_CAP_OFF_10H_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_MSI_CAP_OFF_10H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSI_CAP_MSI_CAP_OFF_14H_OFFSET, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_14H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSI_CAP_MSI_CAP_OFF_14H_RD_MASK, PCIE_CTL_MSI_CAP_MSI_CAP_OFF_14H_WR_MASK, \
                                    "PCIE_CTL_MSI_CAP_MSI_CAP_OFF_14H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_RD_MASK, PCIE_CTL_PCIE_CAP_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_PCIE_CAP_ID_PCIE_NEXT_CAP_PTR_PCIE_CAP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_RD_MASK, PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_RD_MASK, PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_RD_MASK, PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_RD_MASK, PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES2_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_RD_MASK, PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_DEVICE_CAPABILITIES2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_DEVICE_CTRL2_DEVICE_STAT2_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_RD_MASK, PCIE_CTL_PCIE_CAP_DEVICE_CTRL_DEVICE_STAT_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_DEVICE_CTRL2_DEVICE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES2_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_RD_MASK, PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_LINK_CAPABILITIES2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_LINK_CTRL2_LINK_STAT2_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_RD_MASK, PCIE_CTL_PCIE_CAP_LINK_CTRL_LINK_STAT_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_LINK_CTRL2_LINK_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSIX_CAP_PCI_MSIX_CAP_ID_NEXT_CTRL_OFFSET, \
                                    PCIE_CTL_MSIX_CAP_PCI_MSIX_CAP_ID_NEXT_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSIX_CAP_PCI_MSIX_CAP_ID_NEXT_CTRL_RD_MASK, PCIE_CTL_MSIX_CAP_PCI_MSIX_CAP_ID_NEXT_CTRL_WR_MASK, \
                                    "PCIE_CTL_MSIX_CAP_PCI_MSIX_CAP_ID_NEXT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSIX_CAP_MSIX_TBL_OFFSET, \
                                    PCIE_CTL_MSIX_CAP_MSIX_TBL_OFFSET_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSIX_CAP_MSIX_TBL_OFFSET_RD_MASK, PCIE_CTL_MSIX_CAP_MSIX_TBL_OFFSET_WR_MASK, \
                                    "PCIE_CTL_MSIX_CAP_MSIX_TBL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MSIX_CAP_MSIX_PBA_OFFSET, \
                                    PCIE_CTL_MSIX_CAP_MSIX_PBA_OFFSET_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MSIX_CAP_MSIX_PBA_OFFSET_RD_MASK, PCIE_CTL_MSIX_CAP_MSIX_PBA_OFFSET_WR_MASK, \
                                    "PCIE_CTL_MSIX_CAP_MSIX_PBA_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_AER_EXT_CAP_HDR_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_AER_EXT_CAP_HDR_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_AER_EXT_CAP_HDR_OFF_RD_MASK, PCIE_CTL_AER_CAP_AER_EXT_CAP_HDR_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_AER_EXT_CAP_HDR_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_UNCORR_ERR_STAT_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_STAT_OFF_RD_MASK, PCIE_CTL_AER_CAP_UNCORR_ERR_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_UNCORR_ERR_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_UNCORR_ERR_MASK_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_MASK_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_MASK_OFF_RD_MASK, PCIE_CTL_AER_CAP_UNCORR_ERR_MASK_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_UNCORR_ERR_MASK_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_UNCORR_ERR_SEV_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_SEV_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_UNCORR_ERR_SEV_OFF_RD_MASK, PCIE_CTL_AER_CAP_UNCORR_ERR_SEV_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_UNCORR_ERR_SEV_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_CORR_ERR_STAT_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_CORR_ERR_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_CORR_ERR_STAT_OFF_RD_MASK, PCIE_CTL_AER_CAP_CORR_ERR_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_CORR_ERR_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_CORR_ERR_MASK_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_CORR_ERR_MASK_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_CORR_ERR_MASK_OFF_RD_MASK, PCIE_CTL_AER_CAP_CORR_ERR_MASK_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_CORR_ERR_MASK_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_ADV_ERR_CAP_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_ADV_ERR_CAP_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_ADV_ERR_CAP_CTRL_OFF_RD_MASK, PCIE_CTL_AER_CAP_ADV_ERR_CAP_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_ADV_ERR_CAP_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_HDR_LOG_0_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_0_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_0_OFF_RD_MASK, PCIE_CTL_AER_CAP_HDR_LOG_0_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_HDR_LOG_0_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_HDR_LOG_1_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_1_OFF_RD_MASK, PCIE_CTL_AER_CAP_HDR_LOG_1_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_HDR_LOG_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_HDR_LOG_2_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_2_OFF_RD_MASK, PCIE_CTL_AER_CAP_HDR_LOG_2_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_HDR_LOG_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_HDR_LOG_3_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_3_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_HDR_LOG_3_OFF_RD_MASK, PCIE_CTL_AER_CAP_HDR_LOG_3_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_HDR_LOG_3_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_1_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_1_OFF_RD_MASK, PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_1_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_2_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_2_OFF_RD_MASK, PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_2_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_3_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_3_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_3_OFF_RD_MASK, PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_3_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_3_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_4_OFF_OFFSET, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_4_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_4_OFF_RD_MASK, PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_4_OFF_WR_MASK, \
                                    "PCIE_CTL_AER_CAP_TLP_PREFIX_LOG_4_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_SPCIE_CAP_SPCIE_CAP_HEADER_OFFSET, \
                                    PCIE_CTL_SPCIE_CAP_SPCIE_CAP_HEADER_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_SPCIE_CAP_SPCIE_CAP_HEADER_RD_MASK, PCIE_CTL_SPCIE_CAP_SPCIE_CAP_HEADER_WR_MASK, \
                                    "PCIE_CTL_SPCIE_CAP_SPCIE_CAP_HEADER_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_SPCIE_CAP_LINK_CTRL3_OFFSET, \
                                    PCIE_CTL_SPCIE_CAP_LINK_CTRL3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_SPCIE_CAP_LINK_CTRL3_RD_MASK, PCIE_CTL_SPCIE_CAP_LINK_CTRL3_WR_MASK, \
                                    "PCIE_CTL_SPCIE_CAP_LINK_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_SPCIE_CAP_LANE_ERR_STAT_OFFSET, \
                                    PCIE_CTL_SPCIE_CAP_LANE_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_SPCIE_CAP_LANE_ERR_STAT_RD_MASK, PCIE_CTL_SPCIE_CAP_LANE_ERR_STAT_WR_MASK, \
                                    "PCIE_CTL_SPCIE_CAP_LANE_ERR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_SPCIE_CAP_SPCIE_CAP_OFF_0CH_OFFSET, \
                                    PCIE_CTL_SPCIE_CAP_SPCIE_CAP_OFF_0CH_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_SPCIE_CAP_SPCIE_CAP_OFF_0CH_RD_MASK, PCIE_CTL_SPCIE_CAP_SPCIE_CAP_OFF_0CH_WR_MASK, \
                                    "PCIE_CTL_SPCIE_CAP_SPCIE_CAP_OFF_0CH_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_EXT_CAP_HDR_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_EXT_CAP_HDR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_EXT_CAP_HDR_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_EXT_CAP_HDR_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_EXT_CAP_HDR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_CAPABILITY_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CAPABILITY_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CAPABILITY_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_CAPABILITY_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_CAPABILITY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_CTRL_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CTRL_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_CTRL_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_STAT_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_STAT_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_STAT_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_LC_DPAR_STAT_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_LC_DPAR_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_LC_DPAR_STAT_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_LC_DPAR_STAT_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_LC_DPAR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_FIRST_RETIMER_DPAR_STAT_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_FIRST_RETIMER_DPAR_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_FIRST_RETIMER_DPAR_STAT_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_FIRST_RETIMER_DPAR_STAT_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_FIRST_RETIMER_DPAR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_SECOND_RETIMER_DPAR_STAT_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_SECOND_RETIMER_DPAR_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_SECOND_RETIMER_DPAR_STAT_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_SECOND_RETIMER_DPAR_STAT_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_SECOND_RETIMER_DPAR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL16G_CAP_PL16G_CAP_OFF_20H_OFFSET, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CAP_OFF_20H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL16G_CAP_PL16G_CAP_OFF_20H_RD_MASK, PCIE_CTL_PL16G_CAP_PL16G_CAP_OFF_20H_WR_MASK, \
                                    "PCIE_CTL_PL16G_CAP_PL16G_CAP_OFF_20H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MARGIN_CAP_MARGIN_EXT_CAP_HDR_OFFSET, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_EXT_CAP_HDR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_EXT_CAP_HDR_RD_MASK, PCIE_CTL_MARGIN_CAP_MARGIN_EXT_CAP_HDR_WR_MASK, \
                                    "PCIE_CTL_MARGIN_CAP_MARGIN_EXT_CAP_HDR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MARGIN_CAP_MARGIN_PORT_CAPABILITIES_STAT_OFFSET, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_PORT_CAPABILITIES_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_PORT_CAPABILITIES_STAT_RD_MASK, PCIE_CTL_MARGIN_CAP_MARGIN_PORT_CAPABILITIES_STAT_WR_MASK, \
                                    "PCIE_CTL_MARGIN_CAP_MARGIN_PORT_CAPABILITIES_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT0_OFFSET, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT0_RD_MASK, PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT0_WR_MASK, \
                                    "PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT1_OFFSET, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT1_RD_MASK, PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT1_WR_MASK, \
                                    "PCIE_CTL_MARGIN_CAP_MARGIN_LANE_CNTRL_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_EXT_CAP_HDR_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_EXT_CAP_HDR_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_EXT_CAP_HDR_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_EXT_CAP_HDR_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_EXT_CAP_HDR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_CAPABILITY_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CAPABILITY_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CAPABILITY_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_CAPABILITY_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_CAPABILITY_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_CTRL_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CTRL_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_CTRL_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_STAT_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_STAT_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_STAT_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA1_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA1_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA1_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA2_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA2_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA2_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_RCVD_MOD_TS_DATA2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA1_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA1_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA1_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA2_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA2_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA2_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_TX_MOD_TS_DATA2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PL32G_CAP_PL32G_CAP_OFF_20H_OFFSET, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CAP_OFF_20H_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PL32G_CAP_PL32G_CAP_OFF_20H_RD_MASK, PCIE_CTL_PL32G_CAP_PL32G_CAP_OFF_20H_WR_MASK, \
                                    "PCIE_CTL_PL32G_CAP_PL32G_CAP_OFF_20H_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_RAS_DES_CAP_HEADER_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_RAS_DES_CAP_HEADER_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_RAS_DES_CAP_HEADER_RD_MASK, PCIE_CTL_RAS_DES_CAP_RAS_DES_CAP_HEADER_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_RAS_DES_CAP_HEADER_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_VENDOR_SPECIFIC_HEADER_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_VENDOR_SPECIFIC_HEADER_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_VENDOR_SPECIFIC_HEADER_RD_MASK, PCIE_CTL_RAS_DES_CAP_VENDOR_SPECIFIC_HEADER_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_VENDOR_SPECIFIC_HEADER_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_CTRL_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_CTRL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_CTRL_RD_MASK, PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_CTRL_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_DATA_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_DATA_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_DATA_RD_MASK, PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_DATA_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EVENT_CNTER_DATA_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ_EN_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ_EN_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ_EN_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ0_CRC_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ0_CRC_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ0_CRC_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ0_CRC_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ0_CRC_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ1_SEQNUM_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ1_SEQNUM_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ1_SEQNUM_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ1_SEQNUM_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ1_SEQNUM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ2_DLLP_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ2_DLLP_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ2_DLLP_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ2_DLLP_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ2_DLLP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ3_SYMBOL_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ3_SYMBOL_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ3_SYMBOL_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ3_SYMBOL_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ3_SYMBOL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ4_FC_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ4_FC_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ4_FC_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ4_FC_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ4_FC_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ5_SP_TLP_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ5_SP_TLP_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ5_SP_TLP_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ5_SP_TLP_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ5_SP_TLP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H0_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H0_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H0_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H1_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H2_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H3_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_POINT_H3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H0_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H0_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H0_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H1_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H2_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H3_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CMP_VAL_H3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H0_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H0_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H0_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H1_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H2_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H3_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_POINT_H3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H0_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H0_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H0_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H1_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H2_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H3_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_CHANGE_VAL_H3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_EINJ6_TLP_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_TLP_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_EINJ6_TLP_RD_MASK, PCIE_CTL_RAS_DES_CAP_EINJ6_TLP_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_EINJ6_TLP_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_CTRL1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_CTRL1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_CTRL1_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_CTRL1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_CTRL2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_CTRL2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_CTRL2_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_CTRL2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LANE_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LANE_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LANE_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LANE_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LANE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LTSSM_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LTSSM_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LTSSM_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LTSSM_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_L1LTSSM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_PM_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_PM_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_PM_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_PM_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_PM_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_L2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L2_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_L2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_L2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_L3FC_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L3FC_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L3FC_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_L3FC_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_L3FC_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_STAT_L3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_STAT_L3_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_STAT_L3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_STAT_L3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL1_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL2_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL3_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT1_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT1_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT1_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT2_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT2_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT2_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT3_OFFSET, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT3_RD_MASK, PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT3_WR_MASK, \
                                    "PCIE_CTL_RAS_DES_CAP_SD_EQ_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_EXT_HDR_OFF_OFFSET, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_EXT_HDR_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_EXT_HDR_OFF_RD_MASK, PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_EXT_HDR_OFF_WR_MASK, \
                                    "PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_EXT_HDR_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_CAP_OFF_OFFSET, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_CAP_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_CAP_OFF_RD_MASK, PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_CAP_OFF_WR_MASK, \
                                    "PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_CAP_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_STAT_OFF_OFFSET, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_STAT_OFF_RD_MASK, PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_DLINK_CAP_DATA_LINK_FEATURE_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_EXT_CAP_HDR_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_EXT_CAP_HDR_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_EXT_CAP_HDR_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_EXT_CAP_HDR_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_EXT_CAP_HDR_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_VENDOR_SPECIFIC_HDR_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_VENDOR_SPECIFIC_HDR_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_VENDOR_SPECIFIC_HDR_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_VENDOR_SPECIFIC_HDR_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_VENDOR_SPECIFIC_HDR_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_DEVICE_INFORMATION_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_DEVICE_INFORMATION_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_DEVICE_INFORMATION_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_DEVICE_INFORMATION_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_DEVICE_INFORMATION_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_NUM_CHAN_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_NUM_CHAN_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_NUM_CHAN_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_NUM_CHAN_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_NUM_CHAN_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_LOW_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_LOW_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_LOW_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_LOW_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_LOW_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_HIGH_OFF_OFFSET, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_HIGH_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_HIGH_OFF_RD_MASK, PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_HIGH_OFF_WR_MASK, \
                                    "PCIE_CTL_VSECDMA_CAP_VSECDMA_UNROLL_ADDR_OFFSET_HIGH_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_ACK_LATENCY_TIMER_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_ACK_LATENCY_TIMER_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_ACK_LATENCY_TIMER_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_ACK_LATENCY_TIMER_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_ACK_LATENCY_TIMER_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VENDOR_SPEC_DLLP_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VENDOR_SPEC_DLLP_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VENDOR_SPEC_DLLP_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VENDOR_SPEC_DLLP_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VENDOR_SPEC_DLLP_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PORT_FORCE_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PORT_FORCE_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PORT_FORCE_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PORT_FORCE_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PORT_FORCE_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_ACK_F_ASPM_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_ACK_F_ASPM_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_ACK_F_ASPM_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_ACK_F_ASPM_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_ACK_F_ASPM_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PORT_LINK_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PORT_LINK_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PORT_LINK_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PORT_LINK_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PORT_LINK_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_LANE_SKEW_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_LANE_SKEW_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_LANE_SKEW_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_LANE_SKEW_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_LANE_SKEW_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TIMER_CTRL_MAX_FUNC_NUM_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TIMER_CTRL_MAX_FUNC_NUM_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TIMER_CTRL_MAX_FUNC_NUM_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TIMER_CTRL_MAX_FUNC_NUM_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TIMER_CTRL_MAX_FUNC_NUM_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_SYMBOL_TIMER_FILTER_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_SYMBOL_TIMER_FILTER_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_SYMBOL_TIMER_FILTER_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_SYMBOL_TIMER_FILTER_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_SYMBOL_TIMER_FILTER_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_FILTER_MASK_2_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_FILTER_MASK_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_FILTER_MASK_2_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_FILTER_MASK_2_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_FILTER_MASK_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PL_DBG0_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PL_DBG0_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PL_DBG0_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PL_DBG0_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PL_DBG0_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PL_DBG1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PL_DBG1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PL_DBG1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PL_DBG1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PL_DBG1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TX_P_FC_CREDIT_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TX_P_FC_CREDIT_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TX_P_FC_CREDIT_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TX_P_FC_CREDIT_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TX_P_FC_CREDIT_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TX_NP_FC_CREDIT_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TX_NP_FC_CREDIT_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TX_NP_FC_CREDIT_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TX_NP_FC_CREDIT_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TX_NP_FC_CREDIT_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TX_CPL_FC_CREDIT_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TX_CPL_FC_CREDIT_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TX_CPL_FC_CREDIT_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TX_CPL_FC_CREDIT_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TX_CPL_FC_CREDIT_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_QUE_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_QUE_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_QUE_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_QUE_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_QUE_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_2_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_2_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_2_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VC_TX_ARBI_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VC0_P_RX_Q_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VC0_P_RX_Q_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VC0_P_RX_Q_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VC0_P_RX_Q_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VC0_P_RX_Q_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VC0_NP_RX_Q_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VC0_NP_RX_Q_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VC0_NP_RX_Q_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VC0_NP_RX_Q_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VC0_NP_RX_Q_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_VC0_CPL_RX_Q_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_VC0_CPL_RX_Q_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_VC0_CPL_RX_Q_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_VC0_CPL_RX_Q_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_VC0_CPL_RX_Q_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN2_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN2_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN2_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN2_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN2_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PHY_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PHY_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PHY_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PHY_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PHY_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PHY_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PHY_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PHY_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PHY_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PHY_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TRGT_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TRGT_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TRGT_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TRGT_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TRGT_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_CLK_GATING_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_CLK_GATING_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_CLK_GATING_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_CLK_GATING_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_CLK_GATING_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_RELATED_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_RELATED_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_RELATED_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_RELATED_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_RELATED_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_EQ_LOCAL_FS_LF_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_LOCAL_FS_LF_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_LOCAL_FS_LF_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_EQ_LOCAL_FS_LF_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_EQ_LOCAL_FS_LF_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_COEF__0_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_COEF__0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_COEF__0_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_COEF__0_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_COEF__0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_INDEX_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_INDEX_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_INDEX_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_INDEX_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_EQ_PSET_INDEX_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_EQ_COEFF_LEGALITY_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_COEFF_LEGALITY_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_COEFF_LEGALITY_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_EQ_COEFF_LEGALITY_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_EQ_COEFF_LEGALITY_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN3_EQ_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN3_EQ_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN3_EQ_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN3_EQ_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_ORDER_RULE_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_ORDER_RULE_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_ORDER_RULE_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_ORDER_RULE_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_ORDER_RULE_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PIPE_LOOPBACK_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PIPE_LOOPBACK_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PIPE_LOOPBACK_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PIPE_LOOPBACK_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PIPE_LOOPBACK_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MISC_CTRL_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MISC_CTRL_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MISC_CTRL_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MISC_CTRL_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MISC_CTRL_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MULTI_LANE_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MULTI_LANE_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MULTI_LANE_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MULTI_LANE_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MULTI_LANE_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_TRGT_CPL_LUT_DELETE_ENTRY_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_TRGT_CPL_LUT_DELETE_ENTRY_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_TRGT_CPL_LUT_DELETE_ENTRY_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_TRGT_CPL_LUT_DELETE_ENTRY_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_TRGT_CPL_LUT_DELETE_ENTRY_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_LINK_FLUSH_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_LINK_FLUSH_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_LINK_FLUSH_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_LINK_FLUSH_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_LINK_FLUSH_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AMBA_ERR_RSP_DEFAULT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_ERR_RSP_DEFAULT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_ERR_RSP_DEFAULT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AMBA_ERR_RSP_DEFAULT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AMBA_ERR_RSP_DEFAULT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AMBA_LINK_TIMEOUT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_LINK_TIMEOUT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_LINK_TIMEOUT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AMBA_LINK_TIMEOUT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AMBA_LINK_TIMEOUT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AMBA_ORDERING_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_ORDERING_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AMBA_ORDERING_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AMBA_ORDERING_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AMBA_ORDERING_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_3_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_3_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_3_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_3_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_COHERENCY_CTRL_3_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_LOW_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_LOW_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_LOW_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_LOW_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_LOW_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_HIGH_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_HIGH_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_HIGH_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_HIGH_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AXI_MSTR_MSG_ADDR_HIGH_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PCIE_VER_NUMBER_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PCIE_VER_NUMBER_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PCIE_VER_NUMBER_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PCIE_VER_NUMBER_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PCIE_VER_NUMBER_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PCIE_VER_TYPE_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PCIE_VER_TYPE_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PCIE_VER_TYPE_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PCIE_VER_TYPE_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PCIE_VER_TYPE_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MSIX_MATCH_LOW_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_MATCH_LOW_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_MATCH_LOW_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MSIX_MATCH_LOW_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MSIX_MATCH_LOW_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MSIX_MATCH_HIGH_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_MATCH_HIGH_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_MATCH_HIGH_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MSIX_MATCH_HIGH_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MSIX_MATCH_HIGH_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MSIX_DOORBELL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_DOORBELL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_DOORBELL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MSIX_DOORBELL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MSIX_DOORBELL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_MSIX_RAM_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_RAM_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_MSIX_RAM_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_MSIX_RAM_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_MSIX_RAM_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PL_APP_BUS_DEV_NUM_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PL_APP_BUS_DEV_NUM_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PL_APP_BUS_DEV_NUM_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PL_APP_BUS_DEV_NUM_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PL_APP_BUS_DEV_NUM_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PCIPM_TRAFFIC_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PCIPM_TRAFFIC_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PCIPM_TRAFFIC_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PCIPM_TRAFFIC_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PCIPM_TRAFFIC_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_AUX_CLK_FREQ_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_AUX_CLK_FREQ_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_AUX_CLK_FREQ_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_AUX_CLK_FREQ_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_AUX_CLK_FREQ_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PWRDOWN_CTRL_STAT_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PWRDOWN_CTRL_STAT_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PWRDOWN_CTRL_STAT_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PWRDOWN_CTRL_STAT_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PWRDOWN_CTRL_STAT_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_2_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_2_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_2_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PHY_INTEROP_CTRL_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_2_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_2_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_2_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN4_LANE_MARGINING_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_1_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_1_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_1_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_1_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_1_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_2_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_2_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_2_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_2_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_GEN5_LANE_MARGINING_2_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PIPE_RELATED_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PIPE_RELATED_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PIPE_RELATED_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PIPE_RELATED_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PIPE_RELATED_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_DBI_FUNCTION_BANK_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_DBI_FUNCTION_BANK_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_DBI_FUNCTION_BANK_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_DBI_FUNCTION_BANK_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_DBI_FUNCTION_BANK_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_UTILITY_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_UTILITY_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_UTILITY_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_UTILITY_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_UTILITY_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PM_UTILITY_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PM_UTILITY_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PM_UTILITY_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PM_UTILITY_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PM_UTILITY_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_IDE_CTRL_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_IDE_CTRL_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_IDE_CTRL_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_IDE_CTRL_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_IDE_CTRL_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PORT_LOGIC_PRBS_LOOPBACK_TEST_OFF_OFFSET, \
                                    PCIE_CTL_PORT_LOGIC_PRBS_LOOPBACK_TEST_OFF_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PORT_LOGIC_PRBS_LOOPBACK_TEST_OFF_RD_MASK, PCIE_CTL_PORT_LOGIC_PRBS_LOOPBACK_TEST_OFF_WR_MASK, \
                                    "PCIE_CTL_PORT_LOGIC_PRBS_LOOPBACK_TEST_OFF_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR0_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR0_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR0_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR0_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR0_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR1_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR1_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR1_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR1_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR1_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR2_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR2_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR2_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR2_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR2_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR3_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR3_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR3_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR3_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR3_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR4_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR4_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR4_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR4_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR4_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_BAR5_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR5_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_BAR5_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_BAR5_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_BAR5_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_TYPE0_HDR_DBI2_EXP_ROM_BAR_MASK_OFFSET, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_EXP_ROM_BAR_MASK_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_TYPE0_HDR_DBI2_EXP_ROM_BAR_MASK_RD_MASK, PCIE_CTL_TYPE0_HDR_DBI2_EXP_ROM_BAR_MASK_WR_MASK, \
                                    "PCIE_CTL_TYPE0_HDR_DBI2_EXP_ROM_BAR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_PCIE_CAP_DBI2_SHDW_LINK_CAPABILITIES_OFFSET, \
                                    PCIE_CTL_PCIE_CAP_DBI2_SHDW_LINK_CAPABILITIES_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_PCIE_CAP_DBI2_SHDW_LINK_CAPABILITIES_RD_MASK, PCIE_CTL_PCIE_CAP_DBI2_SHDW_LINK_CAPABILITIES_WR_MASK, \
                                    "PCIE_CTL_PCIE_CAP_DBI2_SHDW_LINK_CAPABILITIES_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_6_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_6_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_6_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_7_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_7_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_7_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_8_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_8_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_8_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_9_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_9_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_9_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_9_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_10_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_10_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_10_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_11_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_11_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_11_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_12_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_12_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_12_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_13_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_13_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_13_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_14_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_14_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_14_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_14_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_TARGET_ADDR_OFF_OUTBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_15_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_15_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_15_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_15_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_16_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_16_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_16_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_16_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_17_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_17_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_17_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_18_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_18_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_18_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_1_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_REGION_CTRL_2_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_BASE_ADDR_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_UPPER_BASE_ADDR_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LIMIT_ADDR_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_19_OFFSET, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_19_RD_MASK, PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_19_WR_MASK, \
                                    "PCIE_CTL_ATU_CAP_IATU_LWR_TARGET_ADDR_OFF_INBOUND_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_0_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_0_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_0_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_WRCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_EN_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DOORBELL_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_ELEM_PF_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_LLP_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CYCLE_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_XFERSIZE_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_SAR_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_DAR_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_WATERMARK_EN_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_CTRL1_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_FUNC_NUM_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_QOS_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_STAT_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_STAT_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_SETUP_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_INT_CLR_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_STOP_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_WATERMARK_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_LOW_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_ABORT_HIGH_OFF_RDCH_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_1_OFFSET, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_1_RD_MASK, PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_1_WR_MASK, \
                                    "PCIE_CTL_HDMA_CAP_HDMA_MSI_MSGD_OFF_RDCH_1_OFFSET");

        }

    }

}
