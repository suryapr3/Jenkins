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
 * @file    com_shared_memory_read_write.c
 * @brief   Common functions for handling the shared memory block read write operations.
 */

#include "com_shared_memory_read_write.h"
#include <string.h>

#ifdef PRE_SIL_TEST

#include "presil_com_print.h"

#else

#include "com_print.h"

#endif

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           write data into shared memory
 * @param [in]      address where data needs to be written to , data_len(in bytes) and data
 * @return          void.
 */
void com_shared_mem_write (void *shared_mem_addr, void *data, uint32_t data_len_bytes)
{
    memcpy (shared_mem_addr, data, data_len_bytes);
}
/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           read data from shared memory
 * @param [in]      address where data needs to be read from , data_len and data
 * @return          void.
 */

void com_shared_mem_read (void *data, void *shared_mem_addr, uint32_t data_len_bytes)
{
    memcpy (data, shared_mem_addr, data_len_bytes);
}
