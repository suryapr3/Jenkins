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
 * @file    rf_calib_com_heap.cpp
 * @brief   Heap management functions for Eigen.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_com_heap.cpp
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_heap.h"
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
 * @brief           Create the heap.
 * @param [in]      uint8_t* heap_storage - Pointer to the heap storage area
 *                  size - size of the heap in bytes
 *                  Both heap_storage and size must be multiple of 32
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
bool rf_calib_heap_create (uint8_t *heap_storage, uint32_t size)
{
    return (com_heap_create (heap_storage, size));
}
