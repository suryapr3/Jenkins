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
vec32i32 AT(TX_G_BUFFER_BASE) v_gbuffer[G_BUF_VECTORS];
vec32i32 AT(TX_PASSTHRU_BUFFER_BASE) v_passthru_gain[1];
volatile unsigned int AT(0x4) g_vex_indicator;
volatile int AT(0x10) g_host_indicator;
volatile int AT(0x24) g_vectors_g_buf;
volatile int AT(0x28) g_dpd_coeff_base;
volatile int AT(0x2c) g_passthru_coeff_base;

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

    for (i = 0; i < g_vectors_g_buf; i++)
    {
        vec32i32 v_dpd_coeff;
        v_dpd_coeff = v_gbuffer[i];
#if DEBUG
        OP___dump(__LINE__, v_dpd_coeff);
        OP___printstring("\n");
        OP___dump(__LINE__, i);
#endif
        v_xstoi_1024(Any, g_dpd_coeff_base, s_offset, v_dpd_coeff, s_offset);
    }

    /* for writing the 241st entry of G buffer*/
    vec32i32 v_passthru;
    v_passthru = v_passthru_gain[0];
    s_offset = s_offset * 2;    // is required because s_offset is in 1024 bits but in the next instruction we are using 512 bit transfer
    v_xsto_512(Any, g_dpd_coeff_base, s_offset, v_passthru);

    g_host_indicator = 2;

} // v2d_flow1() ends



