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
 * @file    com_lock.c
 * @brief   Common functions for handling exclusive resource access..
 * @details Detailed description if necessary.
 * @todo
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_lock.h"
#include <stddef.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile int32_t *com_shm_lock_first_addr = NULL;
volatile int32_t *com_shm_lock_last_addr = NULL;

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
void com_lock_init ()
{
    if (RCS_CPU == e_CPUID_AX)
    {
        for (int i = 0; i < e_LOCK_NUM; i++) { p_system_data->shm_lock[i] = e_UNLOCKED; }
        XT_CLREX (); // clear EXCLMON
    }
}

void com_lock_boundary_check_init ()
{
    com_shm_lock_first_addr = &p_system_data->shm_lock[0];
    com_shm_lock_last_addr = &p_system_data->shm_lock[e_LOCK_NUM - 1];
}
