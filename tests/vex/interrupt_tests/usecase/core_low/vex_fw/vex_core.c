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
 * @file    vex_core.c
 * @brief   Vex FW code to validate VEX core interrupts.
 * @details VEX wait in loop, sleep, wake up.
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

volatile int AT(0x0) g_wait_in_loop;



/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/


void vex_core() ENTRY
{
  
    while(g_wait_in_loop);
    
    s_sleep();
} 




