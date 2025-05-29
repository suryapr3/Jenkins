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
 * @file    vex_underrun_B.c
 * @brief   Vex FW code to write the 1 block of data to V2D.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define INITIAL_BLOCK_SIZE 1
#define V2D_BUFFER_SIZE 1023    // In vectors

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

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function sending INITIAL_BLOCK_SIZE blocks of data to HOST V2D
 * @param [in]      none
 * @return          none
 */

void underrun_B() ENTRY
{
   int i,j,offset =0, add_offset = 0;
   for (j = 0; j < INITIAL_BLOCK_SIZE; j++)
   {
        vec32i32 vin2;
        add_offset = add_offset + g_scalar_val;
        V_CLONE_32(g_scalar_val, vin2);
        for(i = 0; i < g_num_vecs_in; i++)
        {
          vec32i32 vin1, vout;
          vin1= vbuffer[i];
#if 0
          OP___dump(__LINE__, i);
          OP___dump(__LINE__, vin1);
#endif
          V_ADD_32(vin1, vin2, vout);

          //v_sto_1024(Any,vbuffer_base,i*128,vout);
          //v_xsto_1024(Any,vbuffer_base,i,vout);
          v_xstomi_1024(Any, g_dest_buffer_base, offset, V2D_BUFFER_SIZE, vout, offset);
          //temp_cnt ++;
        }
   }
#if 0
   OP___printstring( "\n" );
   OP___printstring( "------------core:END------------\n" );
#endif
}
