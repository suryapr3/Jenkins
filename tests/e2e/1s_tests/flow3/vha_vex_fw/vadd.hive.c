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
 * @file    vadd_hive.c
 * @brief   Vex FW code to send a block of data to other Vex Core.
 * @details Detailed description if necessary.
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(0) vbuffer[256];
vec32i32 AT(0x8000) vbuffer_out[256];
unsigned int AT(0x4) vbuffer_base;
int scalar_val;
int num_vecs;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function sending a block of data to other
 *                  Vex Core after incrementing the data.
 * @param [in]      none
 * @return          none
 */
void v_add_s32_prog() ENTRY
{
  int i,offset =0;
  OP___dump(__LINE__, scalar_val);
  OP___dump(__LINE__, num_vecs);
  for(i=0;i<num_vecs;i++)
  {
    vec32i32 vin1, vin2, vout;
    vin1= vbuffer[i];
    OP___dump(__LINE__, i);
    OP___dump(__LINE__, vin1);

    V_CLONE_32(scalar_val, vin2);
    V_ADD_32(vin1, vin2, vout);

    //v_sto_1024(Any,vbuffer_base,i*128,vout);
    //v_xsto_1024(Any,vbuffer_base,i,vout);
    v_xstomi_1024(Any, vbuffer_base,offset, 1023, vout,offset);
    OP___dump(__LINE__,offset);
    //vbuffer_out [i] = vout;
    OP___dump(__LINE__, vout);
  }

  OP___printstring( "\n" );
  OP___printstring( "------------core:END------------\n" );
}
