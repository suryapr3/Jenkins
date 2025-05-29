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
 * @brief   Vex FW code to validate VEX timer in Single Shot Watchdog mode.
 * @details VEX will program the timer in Single Shot Watchdog mode.
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

#define TIMER_NOTIF_LOCATION (0x14)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

volatile int AT(0x0) g_run_forever;
volatile int AT(0x4) g_timeout_count;
volatile int AT(0x8) g_timeout_cycles;
volatile int AT(0xC) g_notif_data;
volatile int AT(0x10) g_timer_id;
volatile int AT(TIMER_NOTIF_LOCATION) g_timer_debug;


/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function Initialzing the timer with required number
 *                  of clock cycles in continuous watchdog mode
 * @param [in]      num of cycles
 * @return          none
 */

inline void init_timer(int cycles , int notif_data, int timer_id)
{

    // set reg_timer_tmdcfgr0, single shot watchdog
    s_xsto_32(Any, 0, TIMER_TMDCFGR(timer_id),TMD_ONE_SHOT_WATCHDOG);
    
    
    // set reg_timer_tmdinitr0, set the timeout val
    s_xsto_32(Any, 0, TIMER_TMDINITR(timer_id), cycles);
    // set reg_timer_tmdwdnotr0, enable notif
    s_xsto_32(Any, 0, TIMER_TMDWDNOTR(timer_id), 0x1);
    // set reg_timer_tmdwdaddrr0, 0x4000 is mapped to DRAM start
    s_xsto_32(Any, 0, TIMER_TMDWDADDRR(timer_id), 0x4000 + TIMER_NOTIF_LOCATION );
    // set reg_timer_tmdwddatar0, data will be written to above address
    s_xsto_32(Any, 0, TIMER_TMDWDDATAR(timer_id), notif_data);
}


void vex_timer() ENTRY
{
    volatile int *timer_debug_ptr = &g_timer_debug;

    g_timeout_count = 0;
    init_timer(g_timeout_cycles, g_notif_data, g_timer_id);
    s_xsto_32(Any, 0, TIMER_TMDCMDR(g_timer_id), TMD_COMMAND_START);           // start the timer

    do
    {
        // This flag will be set by Timer once the configured clocks were elapsed
        while (*timer_debug_ptr != g_notif_data)
        {
        }

        g_timeout_count++;
        timer_debug_ptr++;
    
        s_xsto_32(Any, 0, TIMER_TMDWDADDRR(g_timer_id), 0x4000 + TIMER_NOTIF_LOCATION + (g_timeout_count * 4));
        s_xsto_32(Any, 0, TIMER_TMDCMDR(g_timer_id), TMD_COMMAND_START);         

        
    } while(g_timeout_count < 10);

    s_xsto_32(Any, 0, TIMER_TMDCMDR(g_timer_id), TMD_COMMAND_STOP);           // stop the timer

} 




