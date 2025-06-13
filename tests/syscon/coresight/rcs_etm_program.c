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
#include "rcs_etmb.h"


// Function to get status of ETM
uint32_t rcs_etm_status(int core_num)
{
    uint32_t etmb_base_address = rcs_get_core_address(core_num);
    LOG_PRINT("etmb_base_address: 0x%x", etmb_base_address);

    uint32_t buffer = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCSTATR_OFFSET, SECURE, "STATUS REG");

    // Check if trace unit is idle
    if((buffer & 0x1) == 1)
        LOG_PRINT("Trace Unit is idle for address: 0x%x, core: %d", etmb_base_address, core_num);
    else
        LOG_PRINT("Trace Unit is not idle for address: 0x%x, core: %d", etmb_base_address, core_num);

    return buffer;
}

// Function to enable branch broadcasting, cycle count and timestamp
void rcs_etm_config(int core_num, uint32_t trace_id)
{
    rcs_etmb_trcconfigr_reg_t configr;
    rcs_etmb_trcsyncpr_reg_t syncpr;
    rcs_etmb_trcccctlr_reg_t ccc;
    rcs_etmb_trcprgctlr_reg_t prog_ctlr;

    uint32_t etmb_base_address = rcs_get_core_address(core_num);

    LOG_PRINT("Setting etmb configurations for address: 0x%x", etmb_base_address);

    configr.value = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCONFIGR_OFFSET, SECURE, "CONFIGR REG");

    // Enabling branch broadcasting, cycle counting and timestamp
    //configr.value = 0x818
    configr.BB = 1;
    configr.CCI = 1;
    configr.TS = 1;
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCONFIGR_OFFSET, configr.value, SECURE, "CONFIG REG");

    // Enable trace synchronization for every 4kb trace
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCSYNCPR_OFFSET, 0x10, SECURE, "SYNCPR REG");

    // Setting Cycle count
    // Setting to 1000 cycles
     ccc.THRESHOLD = 0x1000 ;
     write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCCCCTLR_OFFSET, ccc.value , SECURE, "CYCLE COUNT CTRL REG");

    // Setting Trace ID
    // trace_id = 0x2a
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCTRACEIDR_OFFSET, trace_id, SECURE, "TRACE ID REG");

    // ViewInst enable for instruction tracing
    write_m_cs_dbg_18a(etmb_base_address + ETMB_TRCVICTLR_OFFSET, 0x201, SECURE, "VIEWINST REG");
}

// Enable/ Disable etmb
void rcs_etm_switch(int core_num, etm_disable_enable_t ctrl)
{
    uint32_t etmb_base_address = rcs_get_core_address(core_num);

    rcs_etmb_trcprgctlr_reg_t prog_ctlr;

    prog_ctlr.value = read_m_cs_dbg_18a(etmb_base_address + ETMB_TRCPRGCTLR_OFFSET, SECURE, "PROG REG");

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
    }
}

// To switch the debug controller
void rcs_debug_on(int core_num, etm_disable_enable_t debug_ctrl)
{
    uint32_t etmb_base_address = rcs_get_core_address(core_num);

    if(debug_ctrl == ENABLE)
    {
        write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_ON, SECURE, "DEBUG COMMAND REG");
        LOG_PRINT("Debug Controller is ON");
    }
    else if(debug_ctrl == DISABLE)
    {
        write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_OFF, SECURE, "DEBUG COMMAND REG");
        LOG_PRINT("Debug Controller is OFF");
    }
    else
    {
        write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_CONTINUE, SECURE, "DEBUG COMMAND REG");
        LOG_PRINT("Debug Controller is Continue");
    }
}
