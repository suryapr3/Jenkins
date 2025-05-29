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
    DLNK_JESD0_XIP_204D_RX_BASE, DLNK_JESD1_XIP_204D_RX_BASE, DLNK_JESD2_XIP_204D_RX_BASE, DLNK_JESD3_XIP_204D_RX_BASE
    };


        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
	{
        
        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DATAPATH_INTERCONNECT_OFFSET, \
                                    JESD_XIP_204D_RX_DATAPATH_INTERCONNECT_DEFAULT, \
                                    JESD_XIP_204D_RX_DATAPATH_INTERCONNECT_RD_MASK, "JESD_XIP_204D_RX_DATAPATH_INTERCONNECT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SUBCLASS_OFFSET, \
                                    JESD_XIP_204D_RX_SUBCLASS_DEFAULT, \
                                    JESD_XIP_204D_RX_SUBCLASS_RD_MASK, "JESD_XIP_204D_RX_SUBCLASS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_CF_OFFSET, \
                                    JESD_XIP_204D_RX_CF_DEFAULT, \
                                    JESD_XIP_204D_RX_CF_RD_MASK, "JESD_XIP_204D_RX_CF_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_CS_OFFSET, \
                                    JESD_XIP_204D_RX_CS_DEFAULT, \
                                    JESD_XIP_204D_RX_CS_RD_MASK, "JESD_XIP_204D_RX_CS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_F_OFFSET, \
                                    JESD_XIP_204D_RX_F_DEFAULT, \
                                    JESD_XIP_204D_RX_F_RD_MASK, "JESD_XIP_204D_RX_F_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_L_OFFSET, \
                                    JESD_XIP_204D_RX_L_DEFAULT, \
                                    JESD_XIP_204D_RX_L_RD_MASK, "JESD_XIP_204D_RX_L_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_N_OFFSET, \
                                    JESD_XIP_204D_RX_N_DEFAULT, \
                                    JESD_XIP_204D_RX_N_RD_MASK, "JESD_XIP_204D_RX_N_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_M_OFFSET, \
                                    JESD_XIP_204D_RX_M_DEFAULT, \
                                    JESD_XIP_204D_RX_M_RD_MASK, "JESD_XIP_204D_RX_M_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_NTOTAL_OFFSET, \
                                    JESD_XIP_204D_RX_NTOTAL_DEFAULT, \
                                    JESD_XIP_204D_RX_NTOTAL_RD_MASK, "JESD_XIP_204D_RX_NTOTAL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_S_OFFSET, \
                                    JESD_XIP_204D_RX_S_DEFAULT, \
                                    JESD_XIP_204D_RX_S_RD_MASK, "JESD_XIP_204D_RX_S_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_HD_OFFSET, \
                                    JESD_XIP_204D_RX_HD_DEFAULT, \
                                    JESD_XIP_204D_RX_HD_RD_MASK, "JESD_XIP_204D_RX_HD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SCR_OFFSET, \
                                    JESD_XIP_204D_RX_SCR_DEFAULT, \
                                    JESD_XIP_204D_RX_SCR_RD_MASK, "JESD_XIP_204D_RX_SCR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ENMODULE_OFFSET, \
                                    JESD_XIP_204D_RX_ENMODULE_DEFAULT, \
                                    JESD_XIP_204D_RX_ENMODULE_RD_MASK, "JESD_XIP_204D_RX_ENMODULE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_CORE_INTR_MASK_OFFSET, \
                                    JESD_XIP_204D_RX_CORE_INTR_MASK_DEFAULT, \
                                    JESD_XIP_204D_RX_CORE_INTR_MASK_RD_MASK, "JESD_XIP_204D_RX_CORE_INTR_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_CORE_INTR_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_CORE_INTR_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_CORE_INTR_STAT_RD_MASK, "JESD_XIP_204D_RX_CORE_INTR_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_CLK_RATIO_OFFSET, \
                                    JESD_XIP_204D_RX_CLK_RATIO_DEFAULT, \
                                    JESD_XIP_204D_RX_CLK_RATIO_RD_MASK, "JESD_XIP_204D_RX_CLK_RATIO_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_FEC_OFFSET, \
                                    JESD_XIP_204D_RX_FEC_DEFAULT, \
                                    JESD_XIP_204D_RX_FEC_RD_MASK, "JESD_XIP_204D_RX_FEC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_A_OFFSET, \
                                    JESD_XIP_204D_RX_A_DEFAULT, \
                                    JESD_XIP_204D_RX_A_RD_MASK, "JESD_XIP_204D_RX_A_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_BIT_ORDER_OFFSET, \
                                    JESD_XIP_204D_RX_BIT_ORDER_DEFAULT, \
                                    JESD_XIP_204D_RX_BIT_ORDER_RD_MASK, "JESD_XIP_204D_RX_BIT_ORDER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_TL_TEST_MODE_OFFSET, \
                                    JESD_XIP_204D_RX_TL_TEST_MODE_DEFAULT, \
                                    JESD_XIP_204D_RX_TL_TEST_MODE_RD_MASK, "JESD_XIP_204D_RX_TL_TEST_MODE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_BUFF_DELAY_OFFSET, \
                                    JESD_XIP_204D_RX_BUFF_DELAY_DEFAULT, \
                                    JESD_XIP_204D_RX_BUFF_DELAY_RD_MASK, "JESD_XIP_204D_RX_BUFF_DELAY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SYSREF_CFG_OFFSET, \
                                    JESD_XIP_204D_RX_SYSREF_CFG_DEFAULT, \
                                    JESD_XIP_204D_RX_SYSREF_CFG_RD_MASK, "JESD_XIP_204D_RX_SYSREF_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SHB_LOCK_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_SHB_LOCK_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_SHB_LOCK_STAT_RD_MASK, "JESD_XIP_204D_RX_SHB_LOCK_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SHB_LOCK_LOSS_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_SHB_LOCK_LOSS_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_SHB_LOCK_LOSS_STAT_RD_MASK, "JESD_XIP_204D_RX_SHB_LOCK_LOSS_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_AB_LOCK_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_AB_LOCK_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_AB_LOCK_STAT_RD_MASK, "JESD_XIP_204D_RX_AB_LOCK_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_AB_LOCK_LOSS_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_AB_LOCK_LOSS_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_AB_LOCK_LOSS_STAT_RD_MASK, "JESD_XIP_204D_RX_AB_LOCK_LOSS_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ERR_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_ERR_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_ERR_RPT_LANE_REG23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_THRESH_EOAB_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_THRESH_EOAB_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_THRESH_EOAB_ERR_RD_MASK, "JESD_XIP_204D_RX_THRESH_EOAB_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_THRESH_SHB_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_THRESH_SHB_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_THRESH_SHB_ERR_RD_MASK, "JESD_XIP_204D_RX_THRESH_SHB_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SONIF_OFFSET, \
                                    JESD_XIP_204D_RX_SONIF_DEFAULT, \
                                    JESD_XIP_204D_RX_SONIF_RD_MASK, "JESD_XIP_204D_RX_SONIF_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SYSREF_CNTER_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_SYSREF_CNTER_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_SYSREF_CNTER_STAT_RD_MASK, "JESD_XIP_204D_RX_SYSREF_CNTER_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_LAC_BOUNDARY_PHASE_OFFSET, \
                                    JESD_XIP_204D_RX_LAC_BOUNDARY_PHASE_DEFAULT, \
                                    JESD_XIP_204D_RX_LAC_BOUNDARY_PHASE_RD_MASK, "JESD_XIP_204D_RX_LAC_BOUNDARY_PHASE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_RBD_LENGTH_OCTETS_OFFSET, \
                                    JESD_XIP_204D_RX_RBD_LENGTH_OCTETS_DEFAULT, \
                                    JESD_XIP_204D_RX_RBD_LENGTH_OCTETS_RD_MASK, "JESD_XIP_204D_RX_RBD_LENGTH_OCTETS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_GEN_SYSREF_OFFSET, \
                                    JESD_XIP_204D_RX_GEN_SYSREF_DEFAULT, \
                                    JESD_XIP_204D_RX_GEN_SYSREF_RD_MASK, "JESD_XIP_204D_RX_GEN_SYSREF_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_GEARBOX_EMPTY_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_GEARBOX_EMPTY_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_GEARBOX_EMPTY_STAT_RD_MASK, "JESD_XIP_204D_RX_GEARBOX_EMPTY_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_GEARBOX_FULL_STAT_OFFSET, \
                                    JESD_XIP_204D_RX_GEARBOX_FULL_STAT_DEFAULT, \
                                    JESD_XIP_204D_RX_GEARBOX_FULL_STAT_RD_MASK, "JESD_XIP_204D_RX_GEARBOX_FULL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_TXRX_FIFO_WAIT_CNT_OFFSET, \
                                    JESD_XIP_204D_RX_TXRX_FIFO_WAIT_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_TXRX_FIFO_WAIT_CNT_RD_MASK, "JESD_XIP_204D_RX_TXRX_FIFO_WAIT_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_SLOW_LN_DELAY_CNTER_OFFSET, \
                                    JESD_XIP_204D_RX_SLOW_LN_DELAY_CNTER_DEFAULT, \
                                    JESD_XIP_204D_RX_SLOW_LN_DELAY_CNTER_RD_MASK, "JESD_XIP_204D_RX_SLOW_LN_DELAY_CNTER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_DEC_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_DEC_CW_RPT_LANE_REG23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_CW_RPT_LANE_REG23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_COR_SYM_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_COR_SYM_RPT_LANE_REG23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_DEFAULT, \
                                    JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_RD_MASK, "JESD_XIP_204D_RX_UNCOR_CW_RPT_LANE_REG23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_CTRL_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_CTRL_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_CTRL_RD_MASK, "JESD_XIP_204D_RX_ALARM_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_TYPE_MASK_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_TYPE_MASK_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_TYPE_MASK_RD_MASK, "JESD_XIP_204D_RX_ALARM_TYPE_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_LANE_MASK_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_LANE_MASK_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_LANE_MASK_RD_MASK, "JESD_XIP_204D_RX_ALARM_LANE_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_TSHOLD_INV_SYNC_HDR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_INV_SYNC_HDR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_INV_SYNC_HDR_RD_MASK, "JESD_XIP_204D_RX_ALARM_TSHOLD_INV_SYNC_HDR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_TSHOLD_AB_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_AB_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_AB_ERR_RD_MASK, "JESD_XIP_204D_RX_ALARM_TSHOLD_AB_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_TSHOLD_UNC_FEC_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_UNC_FEC_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_TSHOLD_UNC_FEC_ERR_RD_MASK, "JESD_XIP_204D_RX_ALARM_TSHOLD_UNC_FEC_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_WND_INV_SYNC_HDR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_WND_INV_SYNC_HDR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_WND_INV_SYNC_HDR_RD_MASK, "JESD_XIP_204D_RX_ALARM_WND_INV_SYNC_HDR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_WND_AB_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_WND_AB_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_WND_AB_ERR_RD_MASK, "JESD_XIP_204D_RX_ALARM_WND_AB_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_WND_UNC_FEC_ERR_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_WND_UNC_FEC_ERR_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_WND_UNC_FEC_ERR_RD_MASK, "JESD_XIP_204D_RX_ALARM_WND_UNC_FEC_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_ALARM_TIMER_OFFSET, \
                                    JESD_XIP_204D_RX_ALARM_TIMER_DEFAULT, \
                                    JESD_XIP_204D_RX_ALARM_TIMER_RD_MASK, "JESD_XIP_204D_RX_ALARM_TIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_TEST_PATTERN_LSB_OFFSET, \
                                    JESD_XIP_204D_RX_TEST_PATTERN_LSB_DEFAULT, \
                                    JESD_XIP_204D_RX_TEST_PATTERN_LSB_RD_MASK, "JESD_XIP_204D_RX_TEST_PATTERN_LSB_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_TEST_PATTERN_MSB_OFFSET, \
                                    JESD_XIP_204D_RX_TEST_PATTERN_MSB_DEFAULT, \
                                    JESD_XIP_204D_RX_TEST_PATTERN_MSB_RD_MASK, "JESD_XIP_204D_RX_TEST_PATTERN_MSB_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_CFG_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_CFG_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_CFG_RD_MASK, "JESD_XIP_204D_RX_PRBS_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG0_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG1_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG2_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG3_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG4_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG5_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG6_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG7_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG8_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG9_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG10_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG11_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG12_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG13_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG14_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG15_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG16_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG17_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG18_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG19_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG20_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG21_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG22_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_XIP_204D_RX_PRBS_ERR_CNT_REG23_OFFSET, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_DEFAULT, \
                                    JESD_XIP_204D_RX_PRBS_ERR_CNT_RD_MASK, "JESD_XIP_204D_RX_PRBS_ERR_CNT_REG23_OFFSET");
	
    }

}


