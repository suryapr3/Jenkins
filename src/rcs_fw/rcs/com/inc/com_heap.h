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

#ifndef COM_HEAP__H
#define COM_HEAP__H

#include "stdint.h"
#include "stdbool.h" // IWYU pragma: keep
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Allocate memory from the heap.
 * @param [in]      count: uint32_t specifying the number of objects to be allocated
 * @param [in]      size_obj: uint32_t specifying the size of each object
 * @return          Pointer to the allocated storage. NULL if the operation is a failure
 * -------------------------------------------------------------------------------------------------------------------*/
#if __cplusplus
extern "C" void *com_calloc (uint32_t count, uint32_t obj_size); // Our version of calloc
#else
extern void *com_calloc (uint32_t count, uint32_t obj_size); // Our version of calloc
#endif
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Free the allocated memory.
 * @param [in]      ptr - Generic pointer to be freed
 * @return          boolean indicating whether the operation was successful or not
 * -------------------------------------------------------------------------------------------------------------------*/
#if __cplusplus
extern "C" bool com_free (void *ptr); // Our version of free

#else
extern bool com_free (void *ptr); // Our version of free
#endif
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Create heap.
 * @param [in]      p_heap - pointer to the heap area.
 *                  size - Size of the heap
 *                  p_heap and size must be a multiple of 32
 * @return          boolean indicating whether the operation was successful or not
 * -------------------------------------------------------------------------------------------------------------------*/
#if __cplusplus
extern "C" bool com_heap_create (uint8_t *p_heap, uint32_t size);

#else
extern bool com_heap_create (uint8_t *p_heap, uint32_t size);
#endif
#endif
