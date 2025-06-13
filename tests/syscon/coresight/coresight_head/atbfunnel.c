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
/**************************************************************************************
 * @file  atbfunnel.c
****************************************************************************************/

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
#include "coresight_common.h"
#include "coresight_head.h"

#define NUM_ROWS                4
#define NUM_COLUMNS             4

css600_atbfunnel_4to1_64bit_addrblk_0_funnelctrl_reg_t FUNNEL_CTRL_4to1;
css600_atbfunnel_2to1_64bit_addrblk_0_funnelctrl_reg_t FUNNEL_CTRL_2to1;
cs_soc_css600_atbfunnel_4to1_64bit_addrblk_0_funnelctrl_reg_t CS_SOC_FUNNEL_CTRL_4to1;

coreblock core_grid[NUM_ROWS][NUM_COLUMNS] = {

          {
              {VEXABCCS0_ETMB_VE32_TILE_BASE, VEXABCCS1_ETMB_VE32_TILE_BASE, VEXABCCS8_ETMB_VE32_TILE_BASE, VEXABCCS9_ETMB_VE32_TILE_BASE},
              {VEXABCCS2_ETMB_VE32_TILE_BASE, VEXABCCS3_ETMB_VE32_TILE_BASE, VEXABCCS10_ETMB_VE32_TILE_BASE, VEXABCCS11_ETMB_VE32_TILE_BASE},
              {VEXABCCS4_ETMB_VE32_TILE_BASE, VEXABCCS5_ETMB_VE32_TILE_BASE, VEXABCCS12_ETMB_VE32_TILE_BASE, VEXABCCS13_ETMB_VE32_TILE_BASE},
              {VEXABCCS6_ETMB_VE32_TILE_BASE, VEXABCCS7_ETMB_VE32_TILE_BASE, VEXABCCS14_ETMB_VE32_TILE_BASE, VEXABCCS15_ETMB_VE32_TILE_BASE}
          },

          {
              {VEXABCCS16_ETMB_VE32_TILE_BASE, VEXABCCS17_ETMB_VE32_TILE_BASE, VEXABCCS24_ETMB_VE32_TILE_BASE, VEXABCCS25_ETMB_VE32_TILE_BASE},
              {VEXABCCS18_ETMB_VE32_TILE_BASE, VEXABCCS19_ETMB_VE32_TILE_BASE, VEXABCCS26_ETMB_VE32_TILE_BASE, VEXABCCS27_ETMB_VE32_TILE_BASE},
              {VEXABCCS20_ETMB_VE32_TILE_BASE, VEXABCCS21_ETMB_VE32_TILE_BASE, VEXABCCS28_ETMB_VE32_TILE_BASE, VEXABCCS29_ETMB_VE32_TILE_BASE},
              {VEXABCCS22_ETMB_VE32_TILE_BASE, VEXABCCS23_ETMB_VE32_TILE_BASE, VEXABCCS30_ETMB_VE32_TILE_BASE, VEXABCCS31_ETMB_VE32_TILE_BASE}
          },

          {
              {VEXABCCS32_ETMB_VE32_TILE_BASE, VEXABCCS33_ETMB_VE32_TILE_BASE},
              {VEXABCCS34_ETMB_VE32_TILE_BASE, VEXABCCS35_ETMB_VE32_TILE_BASE},
              {VEXABCCS36_ETMB_VE32_TILE_BASE, VEXABCCS37_ETMB_VE32_TILE_BASE},
              {VEXABCCS38_ETMB_VE32_TILE_BASE, VEXABCCS39_ETMB_VE32_TILE_BASE}
          },

          {
              {RPC_LX7_0_ETMB_BASE, RPC_LX7_1_ETMB_BASE, RPC_LX7_2_ETMB_BASE, RPC_KP1_ETMB_BASE}
          }
      };

funnelblock_t funnel_grid[NUM_ROWS][NUM_COLUMNS] = {
          {
            {VEXARRAYCS16_00_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE , VEXARRAYCS16_00_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {VEXARRAYCS16_10_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_10_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {VEXARRAYCS16_20_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_20_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {0x0, VEXARRAYCS16_30_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
          },
          {
            {VEXARRAYCS16_01_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_01_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {VEXARRAYCS16_11_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_11_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {VEXARRAYCS16_21_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_21_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
            {0x0, VEXARRAYCS16_31_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0},
          },
          {
            {VEXARRAYCS8_0_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE, 0x0, VEXARRAYCS8_0_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE},
            {VEXARRAYCS8_1_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE, 0x0, VEXARRAYCS8_1_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE},
            {VEXARRAYCS8_2_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE, 0x0, VEXARRAYCS8_2_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE},
            {VEXARRAYCS8_3_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE},
          },
          {
            {0x0, RCS_CS_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, 0x0}
          }
};

// Function to find the port and funnel base address based on the core address
funnelconfig_t get_funnel_port_and_base_by_core(uint32_t core_addr) {
    int row, column, port;
    funnelconfig_t config;

    // Intialize with invalid values
    config.port = -1;
    config.row = -1;

    for (row = 0; row < NUM_ROWS; ++row)
    {
        for (column = 0; column < NUM_COLUMNS; ++column)
        {
            for (port = 0; port < 4; ++port)
            {
                if (core_grid[row][column].core_addr[port] == core_addr)
                {
                    // The position of the core address within the array determines the port
                    // Set the base address of the 4-to-1 funnel for the found row and column
                    config.funnel_addr = funnel_grid[row][column];
                    config.port = port;
                    config.row = row;
                    config.column = column;
                    return config;
                }
            }
        }
    }
    return config; // Core not found
}


// Function to set the enable bits of funnel ctrl register for a given 2-to-1 funnel address
void set_funnel_enable(uint32_t funnel_addr, int enable_port)
{
    if (funnel_addr != 0)
    {
        // To set the funnel control register to default value
        write_m_cs_dbg_18a(funnel_addr , CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_DEFAULT, SECURE, \
                           "2to1_funnel_ctrl");

        // to set the enable port of the funnel
        FUNNEL_CTRL_2to1.value = read_m_cs_dbg_18a(funnel_addr, SECURE, "funnel_2to1_funnel_ctrl_reg");
        if (enable_port == 0)
        {
            FUNNEL_CTRL_2to1.ENS0 = 1;
        }
        else if (enable_port == 1)
        {
            FUNNEL_CTRL_2to1.ENS1 = 1;
        }
        write_m_cs_dbg_18a(funnel_addr, FUNNEL_CTRL_2to1.value, SECURE, "funnel_2to1_funnel_ctrl_reg");
    }
}

// Function to configure 2to1 funnel of resepective slice based on core_num
void configure_2to1_funnel_by_core(int core_num, char core_name[])
{
    uint32_t core_addr;
    int column;
    uint32_t funnel_ctrl;
    funnelconfig_t config;

    core_addr = get_etmb_core_address(core_num, core_name);
    print("core_addr: 0x%x\n", core_addr);

    // to get the 2to1 funnel address
    config = get_funnel_port_and_base_by_core(core_addr);

    // Set the priority and enable for the associated funnel
    if(config.funnel_addr.funnel_2to1_addr_1 != 0)
    {
        set_funnel_enable(config.funnel_addr.funnel_2to1_addr_1, 0);
        print("2to1 funnel of: 0x%x is set\n", config.funnel_addr.funnel_2to1_addr_1);
        funnel_ctrl = read_m_cs_dbg_18a(config.funnel_addr.funnel_2to1_addr_1, SECURE, "2to1_funnel_ctrl");
        LOG_PRINT("Funnel ctrl reg 2to1: 0x%x", funnel_ctrl);
    }
    if(config.funnel_addr.funnel_2to1_addr_2 != 0)
    {
        set_funnel_enable(config.funnel_addr.funnel_2to1_addr_2, 0);
        print("2to1 funnel of: 0x%x is set", config.funnel_addr.funnel_2to1_addr_2);
    }

    // Now, set port 1 of the other 2-to-1 funnels in the same row based on the column
    for (column = 0; column < config.column; column++) {
        if (funnel_grid[config.row][column].funnel_2to1_addr_1 != 0 &&
            funnel_grid[config.row][column].funnel_2to1_addr_1 != config.funnel_addr.funnel_2to1_addr_1) {
            set_funnel_enable(funnel_grid[config.row][column].funnel_2to1_addr_1, 1);
            print("2to1 funnel of: 0x%x is set\n", funnel_grid[config.row][column].funnel_2to1_addr_1);
            funnel_ctrl = read_m_cs_dbg_18a(funnel_grid[config.row][column].funnel_2to1_addr_1, SECURE, "2to1_funnel_ctrl");
            LOG_PRINT("Funnel ctrl reg 2to1_1: 0x%x", funnel_ctrl);
        }
        if (funnel_grid[config.row][column].funnel_2to1_addr_2 != 0 &&
            funnel_grid[config.row][column].funnel_2to1_addr_2 != config.funnel_addr.funnel_2to1_addr_2) {
            set_funnel_enable(funnel_grid[config.row][column].funnel_2to1_addr_2, 1);
            print("2to1 funnel of: 0x%x is set\n", funnel_grid[config.row][column].funnel_2to1_addr_2);
            funnel_ctrl = read_m_cs_dbg_18a(funnel_grid[config.row][column].funnel_2to1_addr_2, SECURE, "2to1_funnel_ctrl");
            LOG_PRINT("Funnel ctrl reg 2to1_2: 0x%x", funnel_ctrl);
        }
    }
}

// Function to configure the slave enable for the 4-to-1 funnel based on the core address for the coresight modules
void configure_4to1_funnel_by_core(int core_num, char core_name[])
{
    uint32_t funnel_ctrl;
    uint32_t core_addr;
    funnelconfig_t config;

    core_addr = get_etmb_core_address(core_num, core_name);

    // to get the port number of 4to1 funnel of particular slice based on core addr
    config = get_funnel_port_and_base_by_core(core_addr);

    int port = config.port;

    // To set the funnel control register to default value
    write_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr , CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_FUNNELCTRL_DEFAULT, SECURE, \
                        "4to1_funnel_ctrl");

    // to read the funnel control register
    FUNNEL_CTRL_4to1.value = read_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr, SECURE, "4to1_funnel_ctrl");

    if (port == -1) {
        print("Invalid port number for 4to1 funnel\n");
        return;                 // exit if didn't received proper port number
    }

    else if(config.funnel_addr.funnel_4to1_addr != 0)
    {
        switch(port)
        {
            case 0:
                LOG_PRINT("port %d of funnel 4to1 for core %d at address 0x%x is selected", port, core_num, core_addr);
                // to set the enable port 0 of 4to1 funnel
                FUNNEL_CTRL_4to1.ENS0 = 1;
                write_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr , FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 1:
                LOG_PRINT("port %d of funnel 4to1 for core %d at address 0x%x is selected", port, core_num, core_addr);
                // to set the enable port 1 of 4to1 funnel
                FUNNEL_CTRL_4to1.ENS1 = 1;
                write_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr , FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 2:
                LOG_PRINT("port %d of funnel 4 to1 for core %d at address 0x%x is selected", port, core_num, core_addr);
                // to set the enable port 2 of 4to1 funnel
                FUNNEL_CTRL_4to1.ENS2 = 1;
                write_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr , FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 3:
                LOG_PRINT("port %d of funnel 4to1 for core %d at address 0x%x is selected", port, core_num, core_addr);
                // to set the enable port 3 of 4to1 funnel
                FUNNEL_CTRL_4to1.ENS3 = 1;
                write_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr , FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            default:
                LOG_PRINT("No port selected");
        }
        funnel_ctrl = read_m_cs_dbg_18a(config.funnel_addr.funnel_4to1_addr, SECURE, "4to1_funnel_ctrl");
        LOG_PRINT("Funnel ctrl reg 4to1: 0x%x", funnel_ctrl);
    }
}

// Function to configure cs soc 4to1 funnel
void configure_4to1_funnel_by_cs_core(int core_num, char core_name[])
{
    uint32_t core_addr, funnel_ctrl;
    funnelconfig_t config;

    core_addr = get_etmb_core_address(core_num, core_name);

    // to get the port number of 4to1 funnel of particular slice based on core addr
    config = get_funnel_port_and_base_by_core(core_addr);

    int row = config.row;

    // To read the funnel control register
    CS_SOC_FUNNEL_CTRL_4to1.value = read_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR, SECURE, "4to1_funnel_ctrl_cs_soc");

    if (row == -1) {
        return;                 // exit if didn't received proper port number
    }

    if(CS_SOC_4TO1_FUNNEL_ADDR != 0)
    {
        switch(row)
        {
            case 0:
                LOG_PRINT("port 0 of CS SOC is selected");
                // to set the enable port 0 of 4to1 funnel
                CS_SOC_FUNNEL_CTRL_4to1.ENS0 = 1;
                write_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR , CS_SOC_FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 1:
                LOG_PRINT("port 1 of CS SOC is selected");

                // to set the enable port 1 of 4to1 funnel
                CS_SOC_FUNNEL_CTRL_4to1.ENS1 = 1;
                write_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR , CS_SOC_FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 2:
                LOG_PRINT("port 2 of CS SOC is selected");
                // to set the enable port 2 of 4to1 funnel
                CS_SOC_FUNNEL_CTRL_4to1.ENS2 = 1;
                write_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR , CS_SOC_FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            case 3:
                LOG_PRINT("port 3 of CS SOC is selected");
                // to set the enable port 3 of 4to1 funnel
                CS_SOC_FUNNEL_CTRL_4to1.ENS3 = 1;
                write_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR , CS_SOC_FUNNEL_CTRL_4to1.value, SECURE, "4to1_funnel_ctrl");
                break;

            default:
                LOG_PRINT("No port selected");
        }
    }
    funnel_ctrl = read_m_cs_dbg_18a(CS_SOC_4TO1_FUNNEL_ADDR, SECURE, "4to1_funnel_ctrl");
    LOG_PRINT("CS SOC Funnel ctrl reg 4to1: 0x%x", funnel_ctrl);
}

void  atbfunnel_main(int core_num, char core_name[])
{
    // Select and configure 2to1 funnel
    configure_2to1_funnel_by_core(core_num, core_name);

    // Select and configure a specific funnel block
    configure_4to1_funnel_by_core(core_num, core_name);

    //Select and configure cs_soc funnel
    configure_4to1_funnel_by_cs_core(core_num, core_name);
}
