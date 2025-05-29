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
 * @brief   Vex FW code to validate vex timer when timer 0 is stopped 
 *          from RCS
 * @details Vex will program the timer in normal count up mode and is 
 *          force started and stopped from RCS
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

volatile int AT(0x0) g_timer_dut_cycles;
volatile int AT(0x10) g_timer_dut_id;
volatile int AT(0x20) g_timer_start;



/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/


inline void init_timer(int cycles , int notif_data, int timer_id)
{

    // set reg_timer_tmdcfgr0, normal count up 
    s_xsto_32(Any, 0, TIMER_TMDCFGR(timer_id), TMD_NORMAL_COUNT);
    
    
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
    volatile unsigned int timer_tmdvalr ;
    
    
    init_timer(g_timer_dut_cycles, 0x1004, g_timer_dut_id);
    
    do {    
       
       s_xldo_32(Any, 0, TIMER_TMDVALR(g_timer_dut_id), timer_tmdvalr);
  
    } while (!timer_tmdvalr);
    
    s_xldo_32(Any, 0, TIMER_TMDVALR(g_timer_dut_id), g_timer_start);
  
    
    do
    { 
        
        if(timer_tmdvalr == 0xFFFF)
        break;
        s_xldo_32(Any, 0, TIMER_TMDVALR(g_timer_dut_id), timer_tmdvalr);
        
    }while(timer_tmdvalr < 0xFFFF);
            
      
}





   



