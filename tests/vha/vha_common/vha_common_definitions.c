/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
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
 *
 *********************************************************************************************/

/*
 * @file     This file contains functions and declarations that are applicable for all the VHA tests.
 * **/
#include <stdio.h>
#include "vha_common_definitions.h"
#include "common_functions.h"

// Global definitions

extern char g_abc_build_name[];
extern int g_abc_build_version;

int g_vha_ve_list[][NUM_VE_PER_VHA] =
    {
     {0, 1, 8, 9, 16, 17, 24, 25, 32, 33},                 // VHA0, 4
     {2, 3, 10, 11, 18, 19, 26, 27, 34, 35},               // VHA1, 5
     {4, 5, 12, 13, 20, 21, 28, 29, 36, 37},               // VHA2, 6
     {6, 7, 14, 15, 22, 23, 30, 31, 38, 39},               // VHA3, 7
    };

const uint32_t vha_host_id[8][2] =
    {
      { 0x44, 0x45 },                                      // Host ID for VHA0_Port0 and VHA0_Port1
      { 0x4a, 0x4b },                                      // Host ID for VHA1_Port0 and VHA1_Port1
      { 0x50, 0x51 },                                      // Host ID for VHA2_Port0 and VHA2_Port1
      { 0x56, 0x57 },                                      // Host ID for VHA3_Port0 and VHA3_Port1
      { 0x5c, 0x5d },                                      // Host ID for VHA4_Port0 and VHA4_Port1
      { 0x62, 0x63 },                                      // Host ID for VHA5_Port0 and VHA5_Port1
      { 0x68, 0x69 },                                      // Host ID for VHA6_Port0 and VHA6_Port1
      { 0x6e, 0x6f },                                      // Host ID for VHA7_Port0 and VHA7_Port1
    };

const char *sys_rate_str[2][6] =
    {
     {"0.125Gsps", "0.25Gsps", "0.5Gsps", "1Gsps", "2Gsps", "4Gsps"},
     {"0.187Gsps", "0.375Gsps", "0.750Gsps", "1.5Gsps", "3Gsps", "6Gsps"}
    };
const char *vha_dl_clk[2] = {"983.04MHz", "1.474GHz"};
const char *vha_ul_clk[2] = {"983.04MHz", "1.474GHz"};
const char *duc_mode_str[2] = {"AUTO", "MANUAL"};
const char *ddc_mode_str[2] = {"AUTO", "MANUAL"};

/* Vectors per block for the given sample rate which was defined as per order in sys_rate_t enum*/
const int g_vectors_per_block[2][6] =
    {
     {2/*p125 gsps*/, 4/*p25*/, 8/*p5*/, 16/*1*/, 32/*2*/, 64/*4*/},
     {3/*p187*/, 6/*p375*/, 12/*75*/, 24/*1.5*/, 48/*3*/, 96/*6*/}
    };
const int g_md_control_tbl[2][6] =
    {
     {3, 7, 15, 31, 63, 127},
     {5, 11, 23, 47, 95, 191}
    };
const uint32_t g_max_blocks = 1;

// 18a 0p5 specific
int g_18a_0p5_vha_list[4]  = {0, 1, 2, 3};                 // Only VHA0-3 are present on 18a 0p5
int g_18a_0p5_vex_list[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 34, 36, 38};
                                                           // Only VEX0_0-0_7, VEX1_0-1_7, VEX4_x (x = 0, 4, 6, 8)
                                                           //  are present on 18a 0p5

/**
 * @function       : is_vha_present()
 * @brief          : Function to check a vha instance is prsent on a build.
 * @param [in]     : vha_num
 * @return         : status
 */
int is_vha_present(uint32_t vha_num)
{
    int (*vha_list)[4];
    int num_vha_instances;
    int i, rv;

    num_vha_instances = 0;
    vha_list = NULL;
    if((g_abc_build_version == ABC_18A_0P8_0_1) || (g_abc_build_version == ABC_18A_0P8_0_2) ||
       (g_abc_build_version == ABC_18A_0P8_0_3) || (g_abc_build_version == ABC_18A_0P8_0_4) ||
       (g_abc_build_version == ABC_18A_0P8B_0_1) || (g_abc_build_version == ABC_18A_0P8B_0_2))
    {
        // No change in VHA list from 0p5, 0p6 and 0p8
        vha_list = &(g_18a_0p5_vha_list);
        num_vha_instances = 4;
    }
    rv = FAILURE;
    if(vha_list != NULL)
    {
        for(i = 0; i < num_vha_instances; i++)
        {
            if(vha_num == *((*vha_list) + i))
            {
                 // VHA instance is present
                 rv = SUCCESS;
            }
        }
    }
    if(FAILURE == rv)
        LOG_PRINT("ERROR: VHA%d is NOT present on this build-%s\n", vha_num, g_abc_build_name);

    if((vha_num == 2) && ((g_abc_build_version == ABC_18A_0P8_0_2) ||
                          (g_abc_build_version == ABC_18A_0P8_0_3) ||
                          (g_abc_build_version == ABC_18A_0P8_0_4)))
    {
        LOG_PRINT("ERROR: VHA2 is not working properly on 0p8 0.2/0.3/0.4 build. HSD-16024452702\n");
        rv = FAILURE;
    }

    return rv;
}

/**
 * @function       : is_vex_present()
 * @brief          : Function to check a vex instance is prsent on a build.
 * @param [in]     : vex_num
 * @return         : status
 */
int is_vex_present(uint32_t vex_num)
{
    int (*vex_list)[20];
    int num_vex_cores;
    int i, rv;

    num_vex_cores = 0;
    vex_list = NULL;
    if((g_abc_build_version == ABC_18A_0P8_0_1) || (g_abc_build_version == ABC_18A_0P8_0_2) ||
       (g_abc_build_version == ABC_18A_0P8_0_3) || (g_abc_build_version == ABC_18A_0P8_0_4) ||
       (g_abc_build_version == ABC_18A_0P8B_0_1) || (g_abc_build_version == ABC_18A_0P8B_0_2))
    {
        // No change in VEX list from 0p5, 0p6 and 0p8
        vex_list = &(g_18a_0p5_vex_list);
        num_vex_cores = 20;
    }
    rv = FAILURE;
    if(vex_list != NULL)
    {
        for(i = 0; i < num_vex_cores; i++)
        {
            if(vex_num == *((*vex_list) + i))
            {
                 // VEX instance is present
                 rv = SUCCESS;
            }
        }
    }
    if(FAILURE == rv)
        LOG_PRINT("ERROR: VEX%d is NOT preset on this build-%s\n", vex_num, g_abc_build_name);

    return rv;
}

/**
 * @function       : vha_init()
 * @brief          : Function to check and set the power and clocks of the VHA properly.
 * @param [in]     : vha_num
 * @return         : status
 */
int vha_init(uint32_t vha_num)
{
    uint64_t base_addr;
    uint32_t rv;
    vha_cfg_reg_t config;

    rv = 0;
    if(rv = vha_reset(vha_num, RESET_ASSERT))
        return rv;
    if(rv = vha_reset(vha_num, RESET_DEASSERT))
        return rv;

    // Now enable the clocks
    config.value = (3 << VHA_CFG_DL_CLK_EN_BF_OFF)     |
                   (3 << VHA_CFG_UL_CLK_EN_BF_OFF)     |
                   (1 << VHA_CFG_DL_SWG_CLK_EN_BF_OFF) |
                   (1 << VHA_CFG_UL_SWG_CLK_EN_BF_OFF) |
                   (3 << VHA_CFG_CRUX_CLK_EN_BF_OFF);

    if(rv = vha_clock_config(vha_num, config.value))
        return rv;

    return rv;
}

/*
 * @function       : vha_check_status()
 * @brief          : this routine checks various status register checks of VHA
 * @param[in]      : vha instance number and antenna number
 * @return         : status
 */
int vha_check_status(uint32_t vha_num, uint32_t ant_num)
{
    uint64_t base_addr;
    uint32_t reg_val, mask;
    int rv = SUCCESS;
    char *msg = "ERROR";

    // VHA registers
    base_addr = VHA_BASE(vha_num) + VHA_REG_OFFSET;
    reg_val = read_reg_18a(VHA_DL_STAT_ADR(base_addr), "VHA_DL_STAT");
    LOG_PRINT("VHA_DL_STAT = 0x%x\n", reg_val);
    if(reg_val & (0xf << 0)) LOG_PRINT("VHA_DL_STAT.DL_EN_STAT is set, [3:0]=0x%x\n", (reg_val & 0xf));
    if(reg_val & (3 << 4)) LOG_PRINT("VHA_DL_STAT.DL_SWG_EN_STAT is set, [1:0]=0x%x\n", ((reg_val >> 4) & 3));
    if(reg_val & (0xf << 6)) LOG_PRINT("VHA_DL_STAT.DL_IF_AFULL is set, [3:0]=0x%x\n", ((reg_val >> 6) & 0xf));

    reg_val = read_reg_18a(VHA_UL_STAT_ADR(base_addr), "VHA_UL_STAT");
    LOG_PRINT("VHA_UL_STAT = 0x%x\n", reg_val);
    if(reg_val & (3 << 0)) LOG_PRINT("VHA_UL_STAT.UL_EN_STAT is set, [1:0]=0x%x\n", (reg_val & 3));
    if(reg_val & (3 << 2)) LOG_PRINT("VHA_UL_STAT.UL_SWG_EN_STAT is set, [1:0]=0x%x\n", ((reg_val >> 2) & 3));
    if(reg_val & (3 << 4)) LOG_PRINT("VHA_UL_STAT.UL_IF_AFULL is set, [1:0]=0x%x\n", ((reg_val >> 4) & 3));

    // VHA antenna registers
    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_ANT_REG_OFFSET;
    reg_val = read_reg_18a(VHA_ANT_DL_IF_STAT0_ADR(base_addr), "VHA_ANT_DL_IF_STAT0");
    LOG_PRINT("VHA_ANT_DL_IF_STAT0 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_IF_STAT0.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_IF_STAT0.DEPTH is 0x%x\n", ((reg_val >> 6) & 0xff));

    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_ANT_REG_OFFSET;
    reg_val = read_reg_18a(VHA_ANT_DL_IF_STAT1_ADR(base_addr), "VHA_ANT_DL_IF_STAT1");
    LOG_PRINT("VHA_ANT_DL_IF_STAT1 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_IF_STAT1.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_IF_STAT1.DEPTH is 0x%x\n", ((reg_val >> 6) & 0xff));

    reg_val = read_reg_18a(VHA_ANT_DL_CC_IF_STAT0_ADR(base_addr), "VHA_ANT_DL_CC_IF_STAT0");
    LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_CC_IF_STAT0.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x7));

    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_ANT_REG_OFFSET;
    reg_val = read_reg_18a(VHA_ANT_DL_CC_IF_STAT1_ADR(base_addr), "VHA_ANT_DL_CC_IF_STAT1");
    LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_CC_IF_STAT1.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x7));

    reg_val = read_reg_18a(VHA_ANT_DL_OF_STAT0_ADR(base_addr), "VHA_ANT_DL_OF_STAT0");
    LOG_PRINT("VHA_ANT_DL_OF_STAT0 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_OF_STAT0.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_OF_STAT0.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));
    reg_val = read_reg_18a(VHA_ANT_DL_OF_STAT1_ADR(base_addr), "VHA_ANT_DL_OF_STAT1");
    LOG_PRINT("VHA_ANT_DL_OF_STAT1 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_DL_OF_STAT1.FULL is set\n");
    LOG_PRINT("VHA_ANT_DL_OF_STAT1.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));

    reg_val = read_reg_18a(VHA_ANT_UL_IF_STAT_ADR(base_addr), "VHA_ANT_UL_IF_STAT");
    LOG_PRINT("VHA_ANT_UL_IF_STAT = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_UL_IF_STAT.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_UL_IF_STAT.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_UL_IF_STAT.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_UL_IF_STAT.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_UL_IF_STAT.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_UL_IF_STAT.FULL is set\n");
    LOG_PRINT("VHA_ANT_UL_IF_STAT.DEPTH is 0x%x\n", ((reg_val >> 6) & 0xff));

    reg_val = read_reg_18a(VHA_ANT_UL_CC_IF_STAT_ADR(base_addr), "VHA_ANT_UL_CC_IF_STAT");
    LOG_PRINT("VHA_ANT_UL_CC_IF_STAT = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.FULL is set\n");
    LOG_PRINT("VHA_ANT_UL_CC_IF_STAT.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x7));

    reg_val = read_reg_18a(VHA_ANT_UL_OF_STAT0_ADR(base_addr), "VHA_ANT_UL_OF_STAT0");
    LOG_PRINT("VHA_ANT_UL_OF_STAT0 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_UL_OF_STAT0.FULL is set\n");
    LOG_PRINT("VHA_ANT_UL_OF_STAT0.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));
    reg_val = read_reg_18a(VHA_ANT_UL_OF_STAT1_ADR(base_addr), "VHA_ANT_UL_OF_STAT1");
    LOG_PRINT("VHA_ANT_UL_OF_STAT1 = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("VHA_ANT_UL_OF_STAT1.FULL is set\n");
    LOG_PRINT("VHA_ANT_UL_OF_STAT1.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));

    reg_val = read_reg_18a(VHA_ANT_INT_STAT_ADR(base_addr), "VHA_ANT_INT_STATUS");
    LOG_PRINT("VHA_ANT_INT_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.UL_IF_ERROR is set\n", msg);
    if(reg_val & (3 << 1)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.DL_IF_ERROR is set, [1:0]=0x%x\n", msg, ((reg_val >> 1) & 3));
    if(reg_val & (3 << 3)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.DL_IF_ECC_SBE is set, [1:0]=0x%x\n", msg, ((reg_val >> 3) & 3));
    if(reg_val & (3 << 5)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.DL_IF_ECC_MBE is set, [1:0]=0x%x\n",  msg, ((reg_val >> 5) & 3));
    if(reg_val & (3 << 7)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.UL_OF_ERROR is set, [1:0]=0x%x\n", msg, ((reg_val >> 7) & 3));
    if(reg_val & (3 << 9)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.DL_OF_ERROR is set, [1:0]=%x\n", msg, ((reg_val >> 9) & 3));
    mask = 0x7ff;
    if(reg_val & mask) rv = FAILURE;                       // there is an ERROR condition

    // NSIP registers
    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_NSIP_OFFSET;
    reg_val = read_reg_18a(NSIP_HBI_B2H_FF_FIFO_STAT_ADR(base_addr), "B2H_FIFO_STATUS");
    LOG_PRINT("B2H_FIFO_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("B2H_FIFO_STATUS.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("B2H_FIFO_STATUS.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("B2H_FIFO_STATUS.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("B2H_FIFO_STATUS.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("B2H_FIFO_STATUS.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("B2H_FIFO_STATUS.FULL is set\n");
    LOG_PRINT("B2H_FIFO_STATUS.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));

    reg_val = read_reg_18a(NSIP_HBI_H2B_FF_FIFO_STAT_ADR(base_addr), "H2B_FIFO_STATUS");
    LOG_PRINT("H2B_FIFO_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("H2B_FIFO_STATUS.UFLOW is set\n");
    if(reg_val & (1 << 1)) LOG_PRINT("H2B_FIFO_STATUS.OFLOW is set\n");
    if(reg_val & (1 << 2)) LOG_PRINT("H2B_FIFO_STATUS.EMPTY is set\n");
    if(reg_val & (1 << 3)) LOG_PRINT("H2B_FIFO_STATUS.AEMPTY is set\n");
    if(reg_val & (1 << 4)) LOG_PRINT("H2B_FIFO_STATUS.AFULL is set\n");
    if(reg_val & (1 << 5)) LOG_PRINT("H2B_FIFO_STATUS.FULL is set\n");
    LOG_PRINT("H2B_FIFO_STATUS.DEPTH is 0x%x\n", ((reg_val >> 6) & 0x1f));

    reg_val = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(base_addr), "NSIP_INT_STATUS");
    LOG_PRINT("NSIP_INT_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_FF_FULL_DROP_ERROR is set\n", msg);
    if(reg_val & (1 << 1)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_NOMAP_DROP_ERROR is set\n", msg);
    if(reg_val & (1 << 2)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_MATCH_ERROR is set\n", msg);
    if(reg_val & (1 << 3)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_TYPE_ERROR is set\n", msg);
    if(reg_val & (1 << 6)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_NOLKUP_DROP_ERROR is set\n", msg);
    if(reg_val & (1 << 7)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_CQ_FF_OVFL_ERROR is set\n", msg);
    if(reg_val & (1 << 8)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_TK_IN_PKT_ERROR is set\n", msg);
    if(reg_val & (1 << 9)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_FIFO_ERROR is set\n", msg);
    if(reg_val & (1 << 10)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_FIFO_ERROR is set\n", msg);
    if(reg_val & (1 << 11)) LOG_PRINT("%s: NSIP_INT_STATUS.SMON_INT_ERROR is set\n", msg);
    if(reg_val & (3 << 12)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.H2B_DROP_FF_OVFL is set, [1:0]=0x%x\n", msg, ((reg_val >> 12) & 3));
    if(reg_val & (3 << 14)) LOG_PRINT("%s: VHA_ANT_INT_STATUS.B2H_INSERT_FF_OVFL is set, [1:0]=0x%x\n", msg, ((reg_val >> 14) & 3));
    if(reg_val & (1 << 16)) LOG_PRINT("%s: NSIP_INT_STATUS.B2H_INSERT_VEX_DROP is set\n", msg);
    if(reg_val & (1 << 17)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_NO_SOP_ERROR is set\n", msg);
    if(reg_val & (1 << 18)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_NO_EOP_ERROR is set\n", msg);
    if(reg_val & (1 << 19)) LOG_PRINT("%s: NSIP_INT_STATUS.H2B_LEN_ERROR is set\n", msg);
    if(reg_val & 0xfffff) rv = FAILURE;                    // there is an ERROR condition

    // SWG registers
    base_addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
    reg_val = read_reg_18a(SWG_INT_STAT_ADR(base_addr), "DL_SWG_INT_STATUS");
    LOG_PRINT("DL_SWG_INT_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("%s: DL_SWG_INT_STATUS.PAR_ERR is set\n", msg);
    if(reg_val & (1 << 1)) LOG_PRINT("%s: DL_SWG_INT_STATUS.TMR_INCR_ERR is set\n", msg);
    if(reg_val & (1 << 2)) LOG_PRINT("%s: DL_SWG_INT_STATUS.TMR_CONFIG_ERR is set\n", msg);
    if(reg_val & 7) rv = FAILURE;                          // there is an ERROR condition

    base_addr = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;
    reg_val = read_reg_18a(SWG_INT_STAT_ADR(base_addr), "UL_SWG_INT_STATUS");
    LOG_PRINT("UL_SWG_INT_STATUS = 0x%x\n", reg_val);
    if(reg_val & (1 << 0)) LOG_PRINT("%s: UL_SWG_INT_STATUS.PAR_ERR is set\n", msg);
    if(reg_val & (1 << 1)) LOG_PRINT("%s: UL_SWG_INT_STATUS.TMR_INCR_ERR is set\n", msg);
    if(reg_val & (1 << 2)) LOG_PRINT("%s: UL_SWG_INT_STATUS.TMR_CONFIG_ERR is set\n", msg);
    if(reg_val & 7) rv = FAILURE;                          // there is an ERROR condition

    return rv;
}

/**
 * function         vex_cio2strm_configure()
 * @brief           Function configuring all the required CIO2STRM registers to run this test
 * @param [in]      vex_num, host_id
 * @return          status
 */

int vex_cio2strm_configure(
    uint32_t vex_num,
    uint32_t host_id)
{
    cio2strm_t *c2s, cio2strm;
    uint64_t c2s_base_addr;
    int rv;

    rv = 0;
    c2s = &cio2strm;
    c2s_base_addr = CIO2STRM_BASE(vex_num);
    c2s->CIO2STRM_INT_EN.value = 0x3f;                     // enable all interrupts
    c2s->CIO2STRM_WORD_CNT_CTL.value = 1;                  // enable word count
    c2s->CIO2STRM_RANGE_EN.value = 1;                      // enable memory address range compare for set0
    c2s->CIO2STRM_MEM_ADDR_LOW[0].value = 0x0;             // mem_addr_low
    c2s->CIO2STRM_MEM_ADDR_HIGH[0].value = 0x0FFFFFFF;     // mem_addr_high
    c2s->CIO2STRM_MEM_OFFSET[0].value = 0x0;               // no offset addition, so keep 0
    c2s->CIO2STRM_STRM_DEST[0].value = host_id;            // VHA host_id
    if(rv = write_reg_18a(CIO2STRM_INT_EN_ADR(c2s_base_addr),
                          c2s->CIO2STRM_INT_EN.value,
                          CIO2STRM_INT_EN_WR_MASK,
                          "CIO2STRM_INT_ENABLE"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_WORD_CNT_CTL_ADR(c2s_base_addr),
                          c2s->CIO2STRM_WORD_CNT_CTL.value,
                          CIO2STRM_WORD_CNT_CTL_WR_MASK,
                          "CIO2STRM_WORD_CNT_CTL"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_RANGE_EN_ADR(c2s_base_addr),
                          c2s->CIO2STRM_RANGE_EN.value,
                          CIO2STRM_RANGE_EN_WR_MASK,
                          "CIO2STRM_RANGE_EN"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_LOW0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_LOW[0].value,
                          CIO2STRM_MEM_ADDR_LOW_WR_MASK,
                          "CIO2STRM_MEM_ADDR_LOW0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_HIGH0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_HIGH[0].value,
                          CIO2STRM_MEM_ADDR_HIGH_WR_MASK,
                          "CIO2STRM_MEM_ADDR_HIGH0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_OFFSET0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_OFFSET[0].value,
                          CIO2STRM_MEM_OFFSET_WR_MASK,
                          "CIO2STRM_MEM_ADDR_OFFSET0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_STRM_DEST0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_STRM_DEST[0].value,
                          CIO2STRM_STRM_DEST_WR_MASK,
                          "CIO2STRM_STRM_DEST0"))
        return rv;

    LOG_PRINT("INFO: CIO2STRM configuration completed for VEX%d\n", vex_num);

    return rv;
}

/**
 * function         vex_strm2cio_configure()
 * @brief           Function configuring all the required STRM2CIO registers to run this test
 * @param [in]      vex_num
 * @return          status
 */

int vex_strm2cio_configure(
    uint32_t vex_num)
{
    strm2cio_t *s2c, strm2cio;
    uint64_t s2c_base_addr;
    int rv;

    rv = 0;
    s2c = &strm2cio;
    s2c_base_addr = STRM2CIO_BASE(vex_num);
    s2c->STRM2CIO_INT_EN.value = 0xf;                      // enable all interrupts
    s2c->STRM2CIO_FIFO_STAT_CTL.value = 0x1;               // fifo_status_enable
    s2c->STRM2CIO_WORD_CNT_CTL.value = 0x1;                // word_cnt_enable
    if(rv = write_reg_18a(STRM2CIO_INT_EN_ADR(s2c_base_addr),
                          s2c->STRM2CIO_INT_EN.value,
                          STRM2CIO_INT_EN_WR_MASK,
                          "STRM2CIO_INT_ENABLE"))
        return rv;
    if(rv = write_reg_18a(STRM2CIO_FIFO_STAT_CTL_ADR(s2c_base_addr),
                          s2c->STRM2CIO_FIFO_STAT_CTL.value,
                          STRM2CIO_FIFO_STAT_CTL_WR_MASK,
                          "STRM2CIO_FIFO_STATUS_CTL"))
        return rv;
    if(rv = write_reg_18a(STRM2CIO_WORD_CNT_CTL_ADR(s2c_base_addr),
                          s2c->STRM2CIO_WORD_CNT_CTL.value,
                          STRM2CIO_WORD_CNT_CTL_WR_MASK,
                          "STRM2CIO_WORD_CNT_CTL"))
        return rv;

    LOG_PRINT("INFO: STRM2CIO configuration completed for VEX%d\n", vex_num);

    return rv;
}

/*
 * @function       : vha_show_regs()
 * @brief          : this routine is to dump out the VHA registers
 * @param[in]      : vha instance number and antenna number
 * @return         : void
 */
void vha_show_regs(uint32_t vha_num, uint32_t ant_num)
{
    uint64_t addr;

    LOG_PRINT("\n");
    // VHA top level registers
    addr = VHA_BASE(vha_num) + VHA_REG_OFFSET;
    print_registers(addr, 0x3c/4, "VHA_REGS");

    // VHA DUC registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_DUC_OFFSET(0);
    print_registers(addr, 0xc/4, "VHA_DUC0_REGS");
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_DUC_OFFSET(1);
    print_registers(addr, 0xc/4, "VHA_DUC1_REGS");

    // VHA Modulator registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_MOD_OFFSET;
    print_registers(addr, 0xc/4, "VHA_ANT_MOD_REGS");

    // VHA DDC registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_DDC_OFFSET(0);
    print_registers(addr, 0xc/4, "VHA_DDC0_REGS");
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_DDC_OFFSET(1);
    print_registers(addr, 0xc/4, "VHA_DDC1_REGS");

    // VHA De-Modulator registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_DMOD_OFFSET;
    print_registers(addr, 0xc/4, "VHA_ANT_DMOD_REGS");

    // VHA Antenna registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_ANT_REG_OFFSET;
    print_registers(addr, 0xe0/4, "VHA_ANT_REGS");

    // VHA SWG registers
    addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
    print_registers(addr, 0x800/4, "VHA_DL_SWG_REGS");
    addr = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;
    print_registers(addr, 0x800/4, "VHA_UL_SWG_REGS");

    // VHA Antenna NSIP registers
    addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_NSIP_OFFSET;
    print_registers(addr, 0x7a0/4, "VHA_ANT_NSIP_REGS");

}

/*
 * @function       : vex_cio2strm_check_status()
 * @brief          : this routine checks various status registers of CIO2STRM interface of VEX
 * @param          : VEX instance number
 * @return         : status
 */
int vex_cio2strm_check_status(uint32_t vex_num)
{
    uint64_t base_addr;
    uint32_t reg_val;
    int rv = SUCCESS;
    char *msg = "ERROR";

    base_addr = CIO2STRM_BASE(vex_num);
    reg_val = read_reg_18a(CIO2STRM_FIFO_STAT_ADR(base_addr), "CIO2STRM_FIFO_STATUS");
    LOG_PRINT("VEX%d.CIO2STRM_FIFO_STATUS = 0x%x\n", vex_num, reg_val);
    if(reg_val & 0xf) LOG_PRINT("CIO2STRM_FIFO_STATUS.FIFO_DEPTH = 0x%x\n", (reg_val & 0xf));
    if(reg_val & (1 << 4)) LOG_PRINT("%s: CIO2STRM_FIFO_STATUS.UNDERFLOW is set\n", msg);
    if(reg_val & (1 << 5)) LOG_PRINT("%s: CIO2STRM_FIFO_STATUS.OVERFLOW is set\n", msg);
    if(reg_val & (1 << 6)) LOG_PRINT("%s: CIO2STRM_FIFO_STATUS.DATA_TYPE_ERR is set\n", msg);
    if(reg_val & 0x70) rv = FAILURE;                       // there is an ERROR condition

    reg_val = read_reg_18a(CIO2STRM_INT_STAT_ADR(base_addr), "CIO2STRM_INT_STATUS");
    LOG_PRINT("VEX%d.CIO2STRM_INT_STATUS = 0x%x\n", vex_num, reg_val);
    if(reg_val & 1) LOG_PRINT("%s: CIO2STRM_INT_STATUS.UNDERFLOW is set\n", msg);
    if(reg_val & (1 << 1)) LOG_PRINT("%s: CIO2STRM_INT_STATUS.OVERFLOW is set\n", msg);
    if(reg_val & (1 << 2)) LOG_PRINT("%s: CIO2STRM_INT_STATUS.PROTOCOL_FIRST_ERR is set\n", msg);
    if(reg_val & (1 << 3)) LOG_PRINT("%s: CIO2STRM_INT_STATUS.PROTOCOL_LAST_ERR is set\n", msg);
    if(reg_val & (1 << 4)) LOG_PRINT("%s: CIO2STRM_INT_STATUS.RANGE_ERROR is set\n", msg);
    if(reg_val & (1 << 5)) LOG_PRINT("%s: CIO2STRM_INT_STATUS.CREDIT_COUNT is set\n", msg);
    if(reg_val & 0x3f) rv = FAILURE;                       // there is an ERROR condition

    return rv;

}

/*
 * @function       : vex_strm2cio_check_status()
 * @brief          : this routine checks various status registers of STRM2CIO interface of VEX
 * @param          : VEX instance number
 * @return         : status
 */
int vex_strm2cio_check_status(uint32_t vex_num)
{
    uint64_t base_addr;
    uint32_t reg_val;
    int rv = SUCCESS;
    char *msg = "ERROR";

    base_addr = STRM2CIO_BASE(vex_num);
    reg_val = read_reg_18a(STRM2CIO_FIFO_STAT_ADR(base_addr), "STRM2CIO_FIFO_STATUS");
    LOG_PRINT("VEX%d.STRM2CIO_FIFO_STATUS = 0x%x\n", vex_num, reg_val);
    if(reg_val & 0xf) LOG_PRINT("STRM2CIO_FIFO_STATUS.FIFO_DEPTH = 0x%x\n", (reg_val & 0xf));
    if(reg_val & (1 << 4)) LOG_PRINT("%s: STRM2CIO_FIFO_STATUS.UNDERFLOW is set\n", msg);
    if(reg_val & (1 << 5)) LOG_PRINT("%s: STRM2CIO_FIFO_STATUS.OVERFLOW is set\n", msg);
    if(reg_val & (1 << 6)) LOG_PRINT("%s: STRM2CIO_FIFO_STATUS.DATA_TYPE_ERR is set\n", msg);
    if(reg_val & 0x70) rv = FAILURE;                       // there is an ERROR condition

    reg_val = read_reg_18a(STRM2CIO_INT_STAT_ADR(base_addr), "STRM2CIO_INT_STATUS");
    LOG_PRINT("VEX%d.STRM2CIO_INT_STATUS = 0x%x\n", vex_num, reg_val);
    if(reg_val & 1) LOG_PRINT("%s: STRM2CIO_INT_STATUS.UNDERFLOW is set\n", msg);
    if(reg_val & (1 << 1)) LOG_PRINT("%s: STRM2CIO_INT_STATUS.OVERFLOW is set\n", msg);
    if(reg_val & (1 << 2)) LOG_PRINT("%s: STRM2CIO_INT_STATUS.PROTOCOL_SOP_INT is set\n", msg);
    if(reg_val & (1 << 3)) LOG_PRINT("%s: STRM2CIO_INT_STATUS.PROTOCOL_EOP_INT is set\n", msg);
    if(reg_val & 0xf) rv = FAILURE;                        // there is an ERROR condition

    return rv;

}

/*
 * @function       : vex_cio2strm_show_regs()
 * @brief          : this routine checks various status registers of CIO2STRM interface of VEX
 * @param          : VEX instance number
 * @return         : void
 */
void vex_cio2strm_show_regs(uint32_t vex_num)
{
    uint64_t addr;

    addr = CIO2STRM_BASE(vex_num);
    print_registers(addr, 0x184/4, "CIO2STRM_REGS");

}

/*
 * @function       : vex_strm2cio_show_regs()
 * @brief          : this routine checks various status registers of STRM2CIO interface of VEX
 * @param          : VEX instance number
 * @return         : void
 */
void vex_strm2cio_show_regs(uint32_t vex_num)
{
    uint64_t addr;

    addr = STRM2CIO_BASE(vex_num);
    print_registers(addr, 0x74/4, "STRM2CIO_REGS");
}

/*
 * function  : print_registers()
 * @breif    : this function dumps out registers in groups of 4
 *             i. prints 4 first & last registers even if they're all same
 *             ii. skips print if all the 4 consecutive registers are 0's unless it's the starting offset
 *
 * */

void print_registers(uint64_t address, uint32_t size, char name[])
{
    uint32_t buffer[size];
    int print;
    int i, j;

    if(size > MAX_READ_SIZE) size = MAX_READ_SIZE;

    LOG_PRINT("HOST: Dumping %s from address (%x - %x)\n", name, address, (address + ((size - 1) * 4)));
    read_mem_18a(address, size, (uint32_t*)&buffer, name);

    for(i = 0, j = 0; i < size; i+=4, j++)
    {
        print = (!i) || (i == (size - 4)) ||
                (!((buffer[i] == buffer[i + 1]) && (buffer[i] ==  buffer[i + 2]) && (buffer[i] == buffer[i + 3])));
        if(print)
        {
            LOG_PRINT("[%x] %x %x %x %x\n", (address + (j * 0x10)), buffer[i], buffer[i + 1], buffer[i + 2], buffer[i + 3]);
        }
    }
    LOG_PRINT("\n");
}

int vex_cio2strm_configure_for_2_streams(
    uint32_t vex_num,
    uint32_t host_id)
{
    cio2strm_t *c2s, cio2strm;
    uint64_t c2s_base_addr;
    int rv;

    rv = 0;
    c2s = &cio2strm;
    c2s_base_addr = CIO2STRM_BASE(vex_num);
    c2s->CIO2STRM_INT_EN.value = 0x3f;                     // enable all interrupts
    c2s->CIO2STRM_WORD_CNT_CTL.value = 1;                  // enable word count
    c2s->CIO2STRM_RANGE_EN.value = 3;                      // enable memory address range compare for set0
    c2s->CIO2STRM_MEM_ADDR_LOW[0].value = 0x0;             // mem_addr_low
    c2s->CIO2STRM_MEM_ADDR_HIGH[0].value = 0x0000FFFF;     // mem_addr_high
    c2s->CIO2STRM_MEM_OFFSET[0].value = 0x0;               // no offset addition, so keep 0
    c2s->CIO2STRM_STRM_DEST[0].value = host_id;            // VHA host_id
    c2s->CIO2STRM_MEM_ADDR_LOW[1].value = 0x10000;         // mem_addr_low
    c2s->CIO2STRM_MEM_ADDR_HIGH[1].value = 0x0001FFFF;     // mem_addr_high
    c2s->CIO2STRM_MEM_OFFSET[1].value = 0x0;               // no offset addition, so keep 0
    c2s->CIO2STRM_STRM_DEST[1].value = host_id;            // VHA host_id
    if(rv = write_reg_18a(CIO2STRM_INT_EN_ADR(c2s_base_addr),
                          c2s->CIO2STRM_INT_EN.value,
                          CIO2STRM_INT_EN_WR_MASK,
                          "CIO2STRM_INT_ENABLE"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_WORD_CNT_CTL_ADR(c2s_base_addr),
                          c2s->CIO2STRM_WORD_CNT_CTL.value,
                          CIO2STRM_WORD_CNT_CTL_WR_MASK,
                          "CIO2STRM_WORD_CNT_CTL"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_RANGE_EN_ADR(c2s_base_addr),
                          c2s->CIO2STRM_RANGE_EN.value,
                          CIO2STRM_RANGE_EN_WR_MASK,
                          "CIO2STRM_RANGE_EN"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_LOW0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_LOW[0].value,
                          CIO2STRM_MEM_ADDR_LOW_WR_MASK,
                          "CIO2STRM_MEM_ADDR_LOW0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_HIGH0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_HIGH[0].value,
                          CIO2STRM_MEM_ADDR_HIGH_WR_MASK,
                          "CIO2STRM_MEM_ADDR_HIGH0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_OFFSET0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_OFFSET[0].value,
                          CIO2STRM_MEM_OFFSET_WR_MASK,
                          "CIO2STRM_MEM_ADDR_OFFSET0"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_STRM_DEST0_ADR(c2s_base_addr),
                          c2s->CIO2STRM_STRM_DEST[0].value,
                          CIO2STRM_STRM_DEST_WR_MASK,
                          "CIO2STRM_STRM_DEST0"))
        return rv;

    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_LOW1_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_LOW[1].value,
                          CIO2STRM_MEM_ADDR_LOW_WR_MASK,
                          "CIO2STRM_MEM_ADDR_LOW1"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_ADDR_HIGH1_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_ADDR_HIGH[1].value,
                          CIO2STRM_MEM_ADDR_HIGH_WR_MASK,
                          "CIO2STRM_MEM_ADDR_HIGH1"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_MEM_OFFSET1_ADR(c2s_base_addr),
                          c2s->CIO2STRM_MEM_OFFSET[1].value,
                          CIO2STRM_MEM_OFFSET_WR_MASK,
                          "CIO2STRM_MEM_ADDR_OFFSET1"))
        return rv;
    if(rv = write_reg_18a(CIO2STRM_STRM_DEST1_ADR(c2s_base_addr),
                          c2s->CIO2STRM_STRM_DEST[1].value,
                          CIO2STRM_STRM_DEST_WR_MASK,
                          "CIO2STRM_STRM_DEST1"))
        return rv;

    LOG_PRINT("INFO: CIO2STRM configuration completed for VEX%d\n", vex_num);

    return rv;
}

// End of file
