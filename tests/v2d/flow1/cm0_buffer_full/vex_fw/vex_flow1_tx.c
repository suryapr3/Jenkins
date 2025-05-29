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
 * @file    vex_flow1_tx.c
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
vec32i32 AT(0) vbuffer[128];
vec32i32 AT(0x4000) vbuffer_out[384];
volatile unsigned int AT(0x4) g_dest_buffer_base;
volatile int g_scalar_val;
volatile int g_num_vecs_in;
volatile int AT (0x8) g_num_blocks;
volatile int AT(0xC) g_host_debug;
volatile int AT(0x10) g_host_indicator;

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
void v2d_flow1_tx() ENTRY
{
    int i, j, offset =0;
    g_host_debug = 0;
    int dest_address = g_dest_buffer_base;
    int iter_max = g_num_vecs_in;
    g_host_indicator = 0;
#if DEBUG
    OP___dump(__LINE__, g_scalar_val);
    OP___dump(__LINE__, g_num_vecs_in);
    OP___dump(__LINE__, g_num_blocks);
#endif

    for (j = 0; j < INITIAL_BLOCK_SIZE; j++)
    {
        vec32i32 vin2;
        V_CLONE_32(g_scalar_val+j, vin2);
        //V_CLONE_32(g_scalar_val, vin2);
        for(i = 0; i < iter_max; i++)
        {
            vec32i32 vin1, vout;
            vin1= vbuffer[i];
#if DEBUG
            OP___dump(__LINE__, i);
            OP___dump(__LINE__, vin1);
#endif
            V_ADD_32(vin1, vin2, vout);

            //v_sto_1024(Any,vbuffer_base,i*128,vout);
            //v_xsto_1024(Any,vbuffer_base,i,vout);
            v_xstomi_1024(Any, dest_address, offset, 1023, vout, offset);
        }   // for(i = 0; i < g_num_vecs_in; i++) ends
    }   // for (j=0; j < 3; j++) ends

    while (g_host_indicator == 0)
    {
        // wait here till host_indicator becomes 1
    }
    /* This loop of 4 cycles will generate Tx blocks at the rate of 8GSPS
     * Same loop is used for testing all rates as we are testing the entire
     * 32K sample SRAM space for V2D -> A0- 32K samples*/
    for (; j < g_num_blocks; j++)
    {
        vec32i32 vin2;
        V_CLONE_32(g_scalar_val+j, vin2);

#ifdef VOLCANO
#pragma hive pipeline ii=4
//#pragma hive force_unroll=4
#endif
        for(i = 0; i < iter_max; i++)
        {
            vec32i32 vin1, vout;
            vin1= vbuffer[i];
#if DEBUG
            OP___dump(__LINE__, i);
            OP___dump(__LINE__, vin1);
#endif
            V_ADD_32(vin1, vin2, vout);

            //v_sto_1024(Any,vbuffer_base,i*128,vout);
            //v_xsto_1024(Any,vbuffer_base,i,vout);
            v_xstomi_1024(Any, dest_address, offset, 1023, vout, offset);
        }   // for(i = 0; i < g_num_vecs_in; i++) ends
#if 0
        for (i = 0; i < 4; i++)
        {
            debug = debug + 1;
        }
#endif

    }   // for (j=0; j < g_num_blocks; j++) ends


#if DEBUG
    OP___printstring("vex_flow1: 3 bloks sent:");
    OP___dump(__LINE__,0xFFFF);
#endif
} // v2d_flow1() ends
