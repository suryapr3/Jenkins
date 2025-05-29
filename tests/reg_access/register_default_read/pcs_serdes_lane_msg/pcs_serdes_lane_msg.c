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
    DLNK_JESD0_PHY_PCS_SERDES_LANE_GLOBAL_BASE, DLNK_JESD0_PHY_PCS_SERDES_LANE0_BASE, DLNK_JESD0_PHY_PCS_SERDES_LANE1_BASE, DLNK_JESD0_PHY_PCS_SERDES_LANE2_BASE, DLNK_JESD0_PHY_PCS_SERDES_LANE3_BASE,
    DLNK_JESD1_PHY_PCS_SERDES_LANE_GLOBAL_BASE, DLNK_JESD1_PHY_PCS_SERDES_LANE0_BASE, DLNK_JESD1_PHY_PCS_SERDES_LANE1_BASE, DLNK_JESD1_PHY_PCS_SERDES_LANE2_BASE, DLNK_JESD1_PHY_PCS_SERDES_LANE3_BASE,
    DLNK_JESD2_PHY_PCS_SERDES_LANE_GLOBAL_BASE, DLNK_JESD2_PHY_PCS_SERDES_LANE0_BASE, DLNK_JESD2_PHY_PCS_SERDES_LANE1_BASE, DLNK_JESD2_PHY_PCS_SERDES_LANE2_BASE, DLNK_JESD2_PHY_PCS_SERDES_LANE3_BASE,
    DLNK_JESD3_PHY_PCS_SERDES_LANE_GLOBAL_BASE, DLNK_JESD3_PHY_PCS_SERDES_LANE0_BASE, DLNK_JESD3_PHY_PCS_SERDES_LANE1_BASE, DLNK_JESD3_PHY_PCS_SERDES_LANE2_BASE, DLNK_JESD3_PHY_PCS_SERDES_LANE3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PHYSTAT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PHYSTAT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PHYSTAT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PHYSTAT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_TX_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_TX_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_TX_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_TX_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_RX_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_RX_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_RX_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_RX_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_MBUS_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_MBUS_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_MBUS_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_MBUS_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_MBUS_STAT_OFFSET, \
                                    PCS_SERDES_LANE_MSG_MBUS_STAT_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_MBUS_STAT_RD_MASK, "PCS_SERDES_LANE_MSG_MBUS_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_TX_RATE_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_TX_RATE_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_TX_RATE_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_TX_RATE_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_TX_RATE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_TX_RATE_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_TX_RATE_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_TX_RATE_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_TX_RATE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_PCIE_RX_RATE_CFG_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_USB_RX_RATE_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSIF2PMA_UPI_RX_RATE_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN1_CFG_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN1_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_C0_GEN2_CFG_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTXDRV_TXFFE_CP1_GEN2_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST8_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST8_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST8_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST8_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST9_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST9_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST9_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST9_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST10_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST10_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST10_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN3_PRST10_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST8_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST8_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST8_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST8_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST9_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST9_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST9_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST9_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST10_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST10_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST10_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN4_PRST10_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST8_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST8_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST8_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST8_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST9_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST9_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST9_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST9_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST10_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST10_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST10_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN5_PRST10_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST0_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST1_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST2_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST3_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST4_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST4_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST4_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST5_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST5_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST5_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST6_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST6_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST6_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST6_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST7_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST7_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST7_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST7_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST8_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST8_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST8_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST8_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST9_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST9_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST9_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST9_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST10_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST10_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST10_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_GEN6_PRST10_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSLFPS_CTRL_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSLFPS_CTRL_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSLFPS_CTRL_RD_MASK, "PCS_SERDES_LANE_MSG_PCSLFPS_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN34_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN34_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN34_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN34_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN56_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN56_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN56_RD_MASK, "PCS_SERDES_LANE_MSG_PCSTX_LOCAL_FSLF_GEN56_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSPIPE_STAT_CLR_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSPIPE_STAT_CLR_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSPIPE_STAT_CLR_RD_MASK, "PCS_SERDES_LANE_MSG_PCSPIPE_STAT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_UPDATE_CTRL_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_UPDATE_CTRL_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_UPDATE_CTRL_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_UPDATE_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_EN_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_EN_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_EN_0_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_EN_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_0_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_1_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_2_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_2_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_2_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_OVRD_3_OFFSET, \
                                    PCS_SERDES_LANE_MSG_OVRD_3_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_OVRD_3_RD_MASK, "PCS_SERDES_LANE_MSG_OVRD_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCSFSM_RO_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCSFSM_RO_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCSFSM_RO_RD_MASK, "PCS_SERDES_LANE_MSG_PCSFSM_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_CFG_RO_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_0_RD_MASK, "PCS_SERDES_LANE_MSG_CFG_RO_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_CFG_RO_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_1_RD_MASK, "PCS_SERDES_LANE_MSG_CFG_RO_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_CFG_RO_CLR_OFFSET, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_CLR_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_CFG_RO_CLR_RD_MASK, "PCS_SERDES_LANE_MSG_CFG_RO_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_TX_RO_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_TX_RO_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_TX_RO_0_RD_MASK, "PCS_SERDES_LANE_MSG_TX_RO_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_TX_RO_1_OFFSET, \
                                    PCS_SERDES_LANE_MSG_TX_RO_1_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_TX_RO_1_RD_MASK, "PCS_SERDES_LANE_MSG_TX_RO_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_RX_RO_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_RX_RO_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_RX_RO_0_RD_MASK, "PCS_SERDES_LANE_MSG_RX_RO_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_TSTBUS_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_TSTBUS_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_TSTBUS_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_TSTBUS_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_TESTBUS_STAT_0_OFFSET, \
                                    PCS_SERDES_LANE_MSG_TESTBUS_STAT_0_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_TESTBUS_STAT_0_RD_MASK, "PCS_SERDES_LANE_MSG_TESTBUS_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_DEEPPM_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_DEEPPM_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_DEEPPM_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_DEEPPM_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_LINKFBDIRCHG_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_LINKFBDIRCHG_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_LINKFBDIRCHG_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_LINKFBDIRCHG_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_UPI1_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_UPI1_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_UPI1_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_UPI1_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_UPI2PLUS_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_UPI2PLUS_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_UPI2PLUS_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_UPI2PLUS_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_UPI1_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_UPI1_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_UPI1_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_UPI1_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_UPI2PLUS_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_UPI2PLUS_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_UPI2PLUS_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_UPI2PLUS_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE12_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE12_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE12_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE12_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE3PLUS_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE3PLUS_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE3PLUS_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE3PLUS_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE12_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE12_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE12_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE12_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE34_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE34_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE34_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE34_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE5_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE5_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE5_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE5_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_PCIE6_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_PCIE6_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_PCIE6_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_PCIE6_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_USB1_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_USB1_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_USB1_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_USB1_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_USB2_TXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_USB2_TXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_USB2_TXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_USB2_TXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_USB1_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_USB1_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_USB1_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_USB1_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_USB2_RXWIDTH_LUT_CFG_OFFSET, \
                                    PCS_SERDES_LANE_MSG_USB2_RXWIDTH_LUT_CFG_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_USB2_RXWIDTH_LUT_CFG_RD_MASK, "PCS_SERDES_LANE_MSG_USB2_RXWIDTH_LUT_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_MISC_RW_OFFSET, \
                                    PCS_SERDES_LANE_MSG_MISC_RW_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_MISC_RW_RD_MASK, "PCS_SERDES_LANE_MSG_MISC_RW_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_MISC_RO_OFFSET, \
                                    PCS_SERDES_LANE_MSG_MISC_RO_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_MISC_RO_RD_MASK, "PCS_SERDES_LANE_MSG_MISC_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_RW_SPARE_OFFSET, \
                                    PCS_SERDES_LANE_MSG_RW_SPARE_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_RW_SPARE_RD_MASK, "PCS_SERDES_LANE_MSG_RW_SPARE_OFFSET");

        read_reg_expect_18a(base_address[i]+PCS_SERDES_LANE_MSG_RO_SPARE_OFFSET, \
                                    PCS_SERDES_LANE_MSG_RO_SPARE_DEFAULT, \
                                    PCS_SERDES_LANE_MSG_RO_SPARE_RD_MASK, "PCS_SERDES_LANE_MSG_RO_SPARE_OFFSET");

    }

}
