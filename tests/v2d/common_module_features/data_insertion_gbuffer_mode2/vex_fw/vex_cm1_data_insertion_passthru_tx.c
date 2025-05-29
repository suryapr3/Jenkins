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
 * @file    vex_cm1_data_insertion_gbuffer_tx.c
 * @brief   Vex FW code to validate V2D Path A.
 * @details 1. VEX will send g_num_blocks of data to CM.
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
vec32i32 AT(INPUT_VMEM_LOCATION) vbuffer[VEX_IN_BUF_SIZE];
vec32i32 AT(TX_PASSTHRU_BUFFER_BASE) v_passthru_gain[1];
volatile unsigned int AT(0x4) g_vex_indicator;
volatile int AT(0x10) g_host_indicator;
volatile int AT(0x14) g_passthru_coeff_base;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/


/**
 * @brief           Function sending pre defined blocks of data to HOST
 * @param [in]      none
 * @return          none
 */
void cm1_data_insertion_gbuffer_tx() ENTRY
{
    int i = 0, j = 0, s_offset = 0;
    g_host_indicator = 0;

    while (g_vex_indicator != 1)
    {
        // Wait till the value became 1
    }

    vec32i32 v_passthru;
    v_passthru = v_passthru_gain[0];
    v_xsto_512(Any, g_passthru_coeff_base, s_offset, v_passthru);

    g_host_indicator = 2;

} // v2d_flow1() ends



