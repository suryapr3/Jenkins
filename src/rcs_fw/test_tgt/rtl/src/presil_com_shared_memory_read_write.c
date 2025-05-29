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
 * @file    presil_com_shared_memory_read_write.c
 * @brief   Wrapper for handling the shared memory block read write operations.
 */

#include "presil_com_shared_memory_read_write.h"
#include "presil_com_print.h"
#include "rtl_api.h"
#include <string.h>

#define SHARED_MEM_BASE_MASK 0x000FFFFC // shared memory base address 0x00200000 , also masking LSB for byte alignment

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           write data into shared memory
 * @param [in]      address where data needs to be written to , data_len and data
 * @return          void.
 */
void com_shared_mem_write (void *shared_mem_addr, void *data, uint32_t data_len)
{
    FW_PRINT (FW_INFO, " shared_mem_addr: x%x", *((int *)(shared_mem_addr)));
    int shared_mem_offset = (SHARED_MEM_BASE_MASK & *((int *)(shared_mem_addr)));
    FW_PRINT (FW_INFO, " shared_mem_offset :0x%x", shared_mem_offset);

    // fix for testbench : write_mem only writes 4 integers at a time.
    int *temp_data = (int *)data;
    int temp_data_len = data_len / 4;
    if (temp_data_len == 0)
    {
        write_mem ("RSM", (shared_mem_offset), data_len, temp_data);
    }
    else
    {
        for (int i = 0; i < temp_data_len; i++)
        {
            write_mem ("RSM", (shared_mem_offset + (16 * i)), 4, &temp_data[4 * i]);
        }
    }
}
/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           read data from shared memory
 * @param [in]      address where data needs to be read from , data_len and data
 * @return          void.
 */

void com_shared_mem_read (void *data, void *shared_mem_addr, uint32_t data_len)
{
    FW_PRINT (FW_INFO, " shared_mem_addr x%x", *((int *)(shared_mem_addr)));
    int shared_mem_offset = (SHARED_MEM_BASE_MASK & *((int *)(shared_mem_addr)));
    FW_PRINT (FW_INFO, "shared_mem_offset :x%x", shared_mem_offset);
    read_mem ("RSM", shared_mem_offset, data_len, (int *)data);
}
