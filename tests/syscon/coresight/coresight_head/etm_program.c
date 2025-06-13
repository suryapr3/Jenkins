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
 * @file  etm_program.c
****************************************************************************************/

#include "srp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_functions.h"
#include "com_definitions.h"
#include "all_comps.h"
#include "init.h"
#include "cli.h"
#include "logger.h"
#include "common_macro.h"
#include "srp_block_ids.h"
#include "coresight_common.h"
#include "coresight_head.h"

// Array of vex etmb addresses
core_num_address_t vex_address_map[40] =
{
    {0, VEXABCCS0_ETMB_VE32_TILE_BASE},   {1, VEXABCCS1_ETMB_VE32_TILE_BASE},
    {2, VEXABCCS2_ETMB_VE32_TILE_BASE},   {3, VEXABCCS3_ETMB_VE32_TILE_BASE},
    {4, VEXABCCS4_ETMB_VE32_TILE_BASE},   {5, VEXABCCS5_ETMB_VE32_TILE_BASE},
    {6, VEXABCCS6_ETMB_VE32_TILE_BASE},   {7, VEXABCCS7_ETMB_VE32_TILE_BASE},
    {8, VEXABCCS8_ETMB_VE32_TILE_BASE},   {9, VEXABCCS9_ETMB_VE32_TILE_BASE},
    {10, VEXABCCS10_ETMB_VE32_TILE_BASE}, {11, VEXABCCS11_ETMB_VE32_TILE_BASE},
    {12, VEXABCCS12_ETMB_VE32_TILE_BASE}, {13, VEXABCCS13_ETMB_VE32_TILE_BASE},
    {14, VEXABCCS14_ETMB_VE32_TILE_BASE}, {15, VEXABCCS15_ETMB_VE32_TILE_BASE},
    {16, VEXABCCS16_ETMB_VE32_TILE_BASE}, {17, VEXABCCS17_ETMB_VE32_TILE_BASE},
    {18, VEXABCCS18_ETMB_VE32_TILE_BASE}, {19, VEXABCCS19_ETMB_VE32_TILE_BASE},
    {20, VEXABCCS20_ETMB_VE32_TILE_BASE}, {21, VEXABCCS21_ETMB_VE32_TILE_BASE},
    {22, VEXABCCS22_ETMB_VE32_TILE_BASE}, {23, VEXABCCS23_ETMB_VE32_TILE_BASE},
    {24, VEXABCCS24_ETMB_VE32_TILE_BASE}, {25, VEXABCCS25_ETMB_VE32_TILE_BASE},
    {26, VEXABCCS26_ETMB_VE32_TILE_BASE}, {27, VEXABCCS27_ETMB_VE32_TILE_BASE},
    {28, VEXABCCS28_ETMB_VE32_TILE_BASE}, {29, VEXABCCS29_ETMB_VE32_TILE_BASE},
    {30, VEXABCCS30_ETMB_VE32_TILE_BASE}, {31, VEXABCCS31_ETMB_VE32_TILE_BASE},
    {32, VEXABCCS32_ETMB_VE32_TILE_BASE}, {33, VEXABCCS33_ETMB_VE32_TILE_BASE},
    {34, VEXABCCS34_ETMB_VE32_TILE_BASE}, {35, VEXABCCS35_ETMB_VE32_TILE_BASE},
    {36, VEXABCCS36_ETMB_VE32_TILE_BASE}, {37, VEXABCCS37_ETMB_VE32_TILE_BASE},
    {38, VEXABCCS38_ETMB_VE32_TILE_BASE}, {39, VEXABCCS39_ETMB_VE32_TILE_BASE}
};

// Array of RCS etmb addresses
core_num_address_t rcs_address_map[4] =
{
    {0, RPC_LX7_0_ETMB_BASE}, {1, RPC_LX7_1_ETMB_BASE},
    {2, RPC_LX7_2_ETMB_BASE}, {3, RPC_KP1_ETMB_BASE}
};

// Function to get status of ETM
uint32_t etm_status(int core_num, char core_name[])
{
    uint32_t etmb_base_address = get_etmb_core_address(core_num, core_name);
    LOG_PRINT("etmb_base_address: 0x%x", etmb_base_address);
    print("etmb_base_address: 0x%x\n", etmb_base_address);

    uint32_t buffer = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCSTATR_OFFSET, SECURE, "STATUS REG");
    print("ETM_STS: 0x%x\n", buffer);

    // Check if trace unit is idle
    if((buffer & 0x1) == 1)
        LOG_PRINT("Trace Unit is idle for address: 0x%x, core: %d", etmb_base_address, core_num);
    else
        LOG_PRINT("Trace Unit is not idle for address: 0x%x, core: %d", etmb_base_address, core_num);

    return buffer;
}

// Function to enable branch broadcasting, cycle count and timestamp
void etm_config(int core_num, char core_name[], uint32_t trace_id)
{
    ve32_tile_etmb_trcconfigr_reg_t configr;
    ve32_tile_etmb_trcccctlr_reg_t ccc;

    uint32_t etmb_base_address = get_etmb_core_address(core_num, core_name);

    print("etmb_base_address: 0x%x\n", etmb_base_address);
    LOG_PRINT("Setting etmb configurations for address: 0x%x\n", etmb_base_address);

    configr.value = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCONFIGR_OFFSET, SECURE, "CONFIGR REG");

    // Enabling branch broadcasting, cycle counting and timestamp
    //configr.value = 0x818
    configr.BB = 1;
    configr.CCI = 1;
    configr.TS = 1;
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCONFIGR_OFFSET, configr.value, SECURE, "CONFIG REG");

    // Enable trace synchronization for every 64kb trace
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCSYNCPR_OFFSET, ETMB_TRCSYNCPR_REQ, SECURE, "SYNCPR REG");

    // Setting Cycle count
    // Setting to 1000 cycles
     ccc.THRESHOLD = 0x1000 ;
     write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCCCTLR_OFFSET, ccc.value , SECURE, "CYCLE COUNT CTRL REG");

    // Setting Trace ID
    // trace_id = 0x2a
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCTRACEIDR_OFFSET, trace_id, SECURE, "TRACE ID REG");
}

// Enable/ Disable etmb
void etm_switch(int core_num, char core_name[], etm_disable_enable_t ctrl)
{
    ve32_tile_etmb_trcprgctlr_reg_t prog_ctlr;
    uint32_t etmb_base_address = get_etmb_core_address(core_num, core_name);

    prog_ctlr.value = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCPRGCTLR_OFFSET, SECURE, "PROG REG");

    print("TRCPRGCTLR: 0x%x\n", prog_ctlr.value);
    // Set or clear the enable bit based on the ctrl parameter
    if(ctrl == ENABLE)
    {
        prog_ctlr.EN = 1;
        // Enable ETM
        write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCPRGCTLR_OFFSET, prog_ctlr.value, SECURE, "PROG CTRL REG");
    }
    else
    {
        prog_ctlr.EN = 0;
        // Disable ETM
        write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCPRGCTLR_OFFSET, prog_ctlr.value, SECURE, "PROG CTRL REG");
        prog_ctlr.value = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCPRGCTLR_OFFSET, SECURE, "PROG REG");
    }
    print("TRCPRGCTLR: 0x%x\n", prog_ctlr.value);
}
