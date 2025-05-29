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
/**
 * @file    vex_timer.c
 * @brief   Vex FW code to validate vex timer when notification is disabled
 * @details Vex will program the timer using Performance counters in single 
 *          shot watchdog mode when notification is disabled 
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>
#include "defines.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile int AT(0x0) g_timeout_dut_cycles;
volatile int AT(0x4) g_timeout_perf_start_cycles;
volatile int AT(0x8) g_timeout_perf_stop_cycles;
volatile int AT(0xC) g_timeout_perf_snap_cycles;

volatile int AT(0x10) g_timer_dut_id;
volatile int AT(0x14) g_timer_perf_start_id;
volatile int AT(0x18) g_timer_perf_stop_id;
volatile int AT(0x1C) g_timer_perf_snap_id;


/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function checks the timer counter cycles 
 *                  when notification is disabled in a single shot watchdog mode
 * @param [in]      num of cycles
 * @return          none
 */


inline void init_timer(int cycles , int notif_data, int timer_id)
{

    // set reg_timer_tmdcfgr0, single shot watchdog
    s_xsto_32(Any, 0, TIMER_TMDCFGR(timer_id), TMD_ONE_SHOT_WATCHDOG);
    
    
    // set reg_timer_tmdinitr0, set the timeout val
    s_xsto_32(Any, 0, TIMER_TMDINITR(timer_id), cycles);
    // set reg_timer_tmdwdnotr0, enable notif
    s_xsto_32(Any, 0, TIMER_TMDWDNOTR(timer_id), 0x1);
    // set reg_timer_tmdwdaddrr0, 0x4000 is mapped to DRAM start
    s_xsto_32(Any, 0, TIMER_TMDWDADDRR(timer_id), 0 );
    // set reg_timer_tmdwddatar0, data will be written to above address
    s_xsto_32(Any, 0, TIMER_TMDWDDATAR(timer_id), notif_data);
}



void vex_timer() ENTRY
{
    volatile int timer_tmdvalr;
   
    init_timer(g_timeout_dut_cycles, 0, g_timer_dut_id); // 0x200
    init_timer(g_timeout_perf_start_cycles, 0x2008, g_timer_perf_start_id); // 0x100
    init_timer(g_timeout_perf_stop_cycles, 0x4008, g_timer_perf_stop_id); // 0x280
    init_timer(g_timeout_perf_snap_cycles, 0x10008, g_timer_perf_snap_id); // 0x290
    

    s_xsto_32(Any, 0, TIMER_TMDWDNOTR(g_timer_dut_id),0x0); // notif disabled
    
    s_xsto_32(Any, 0, TIMER_TMDCMDR(0), TMD_COMMAND_START); // start the timer
    s_xsto_32(Any, 0, TIMER_TMDCMDR(1), TMD_COMMAND_START); // start the timer
    s_xsto_32(Any, 0, TIMER_TMDCMDR(2), TMD_COMMAND_START); // start the timer
    s_xsto_32(Any, 0, TIMER_TMDCMDR(3), TMD_COMMAND_START); // start the timer

    do {
        s_xldo_32(Any, 0, TIMER_TMDVALR(g_timer_dut_id), timer_tmdvalr);
        
    } while (timer_tmdvalr );
 
}





   



