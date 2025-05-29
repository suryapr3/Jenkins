/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents "Material" are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you "License". Unless the License provides otherwise, you may not use, modify,
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
 * @file    cal_postprocess.c
 * @brief   Perform post processing for the cal. tests in the RTL testing
 * @details The input for the multiplication comes from the 2 fixed point arrays
 *          stored in the shared memory
 * @todo    Write documentation for source file cal_postprocess.c
 */


/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "cal_rtl_param.h"
#include "stdint.h"
#include "rtl_api.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static int32_t read_scratch_buffer[CALTEST_MATRIX_SIZE];
static int32_t output_start_address;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           
 * @param [in]      
 * @param [in]      
 * @param [in]      
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void cal_eigentest_post_process()
{
    read_mem("RSM",CALTEST_TRACE_ADDRESS-SHARED_MEMORY_START_ADDRESS, 1, &output_start_address);
    output_start_address -= SHARED_MEMORY_START_ADDRESS;
    //int output_start_address = address_result_int_output - SHARED_MEMORY_START_ADDRESS;
    read_mem("RSM",output_start_address, CALTEST_MATRIX_SIZE, &read_scratch_buffer[0]);
    #if TEMP_DISABLED
    for(int i=0; i <CALTEST_MATRIX_SIZE; ++i)
    {
        write_info("%d\n",read_scratch_buffer[i]);
    }
    #endif
    return;
}

 