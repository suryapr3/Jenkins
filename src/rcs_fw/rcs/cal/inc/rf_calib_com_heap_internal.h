/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/

#ifndef RF_CALIB_COM_HEAP_INTERNAL__H
#define RF_CALIB_COM_HEAP_INTERNAL__H

#include "stdalign.h"
#include "stdint.h"
#define TASK_HEAP_SIZE  153600 // Needs to be multiple of header size (128 bytes)
#define BLOCK_ALLOCATED 0
#define BLOCK_FREE      1

typedef union header {
    struct
    {
        union header *ptr;
        union header *Prev_free_block;
        uint32_t size;
        uint32_t status;
        union header *Prev_allocated_block;
        union header *Next_allocated_block;
    } s;
    uint8_t x[128]; // To force alignment on a 32 bit boundry
} Header;

typedef struct alignas (128) heap_task
{
    Header base;
    Header *freep;
    uint32_t Heap_Size;
    uint32_t dummy[126];
    Header heap[TASK_HEAP_SIZE / sizeof (Header)];
} Task_Heap;
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the pointer to the Task_Heap structure.
 * @param [in]      None.
 * @return          Pointer to the Task_Heap structur.
 * -------------------------------------------------------------------------------------------------------------------*/
Task_Heap *rf_calib_get_task_heap_ptr (void);
#endif
