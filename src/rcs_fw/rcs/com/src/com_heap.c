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
 * @file    com_heap.cpp
 * @brief   Heap management functions.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file com_heap.cpp
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_heap.h"
#include "com_print.h"
#include "stdint.h"
#include "stdlib.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define BLOCK_ALLOCATED 0
#define BLOCK_FREE      1
#define MAGIC_1         0xAAAAAAAA
#define MAGIC_2         0x55555555
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

typedef union header {
    struct
    {
        uint32_t magic_1;
        uint32_t magic_2;
        uint32_t size;
        union header *ptr;
        union header *Prev_free_block;
        uint32_t status;
        union header *Prev_allocated_block;
        union header *Next_allocated_block;
    };
    uint8_t x[32]; // To force alignment on a 256 bit (2*128 bits) (32 byte) that is closest to the size of struct s boundry.
                   // KP1 vector processor is a 128 bit SIMD and all data allocations must be 128 bit aligned
} Header;

typedef struct heap_task
{
    Header *heap;
    Header base;
    Header *freep;
    uint32_t Heap_Size;
} Task_Heap;

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static Task_Heap heap;
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
 * @param [in]      None
 * @return          boolean indicating whether the operation was successful or not
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_heap_create (uint8_t *heap_storage, uint32_t size)
{
    if ((size & 0x3f) || ((uintptr_t)heap_storage & 0x3f))
    {
        FW_PRINT (FW_ERR, "Both pointer to the heap storage area and the heap size must be multiple of 32");
        return (false);
    }
    Task_Heap *p_heap = &heap;
    p_heap->heap = (Header *)heap_storage;
    p_heap->base.ptr = p_heap->freep = &(p_heap->heap[0]);
    p_heap->base.Prev_free_block = &(p_heap->heap[0]);
    p_heap->base.size = 0;
    p_heap->base.status = BLOCK_ALLOCATED;
    p_heap->base.Prev_allocated_block = &(p_heap->heap[0]);
    p_heap->base.Next_allocated_block = &(p_heap->heap[0]);
    p_heap->heap[0].ptr = &(p_heap->base);
    p_heap->heap[0].Prev_free_block = &(p_heap->base);
    // p_heap->heap[0].size = TASK_HEAP_SIZE / sizeof (Header);
    p_heap->heap[0].size = size / sizeof (Header);
    p_heap->heap[0].Prev_allocated_block = &(p_heap->base);
    p_heap->heap[0].Next_allocated_block = &(p_heap->base);
    p_heap->heap[0].status = BLOCK_FREE;
    p_heap->heap[0].magic_1 = MAGIC_1;
    p_heap->heap[0].magic_2 = MAGIC_2;
    // p_heap->Heap_Size = (uintptr_t) & (p_heap->heap[TASK_HEAP_SIZE / sizeof (Header)]);
    p_heap->Heap_Size = (uint32_t)(uintptr_t) & (p_heap->heap[size / sizeof (Header)]);
    FW_PRINT (FW_INFO, "Heap size is %d units\n", p_heap->heap[0].size);
    return (true);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implementation of local calloc functionality. Based on the idea from Kernigham and Ritchie
 * @param [in]      count: uint32_t specifying the number of objects to be allocated
 * @param [in]      size_obj: uint32_t specifying the size of each object.
 * @return          void* pointing to the allocated memory or NULL if no memory allocation is possible
 * -------------------------------------------------------------------------------------------------------------------*/

void *com_calloc (uint32_t count, uint32_t size_obj)
{
    uint32_t remaining_units;
    Header *p;
    Header *prevp;
    Header *curp;

    unsigned nunits;
    uint32_t nbytes = count * size_obj;
    Task_Heap *p_heap = &heap;
    nunits = (nbytes + sizeof (Header) - 1) / sizeof (Header) + 1;
    FW_PRINT (FW_INFO, "Requested units = %d\n", nunits);
    prevp = p_heap->freep;
    for (p = prevp->ptr;; prevp = p, p = p->ptr)
    {
        if (p->size >= nunits)
        {
            if (p->size == nunits)
            {
                p->status = BLOCK_ALLOCATED;
                prevp->ptr = p->ptr;
                p->ptr->Prev_free_block = prevp;
            }
            else
            {
                p->size -= nunits;
                remaining_units = p->size;
                FW_PRINT (FW_INFO, "Remaining units = %d\n", remaining_units);
                curp = p;
                p += p->size;
                p->size = nunits;
                p->Next_allocated_block = curp->Next_allocated_block;
                curp->Next_allocated_block = p;
                p->Prev_allocated_block = curp;
                p->Next_allocated_block->Prev_allocated_block = p;
                p->status = BLOCK_ALLOCATED;
                p->magic_1 = MAGIC_1;
                p->magic_2 = MAGIC_2;
            }
            p_heap->freep = prevp;
            FW_PRINT (FW_INFO, "Allocated units = %d\n", nunits);
            return (void *)(p + 1);
        }
        if (p == p_heap->freep)
        {
            FW_PRINT (FW_INFO, "Allocated units = %d\n", 0);
            return NULL;
        }
    }
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Free the memory pointed by the passed input
 * @param [in]      ap: generic pointer pointing to the start of the allocated memory
 * @return          boolean indicating whether the operation was successful or not
 * -------------------------------------------------------------------------------------------------------------------*/

bool com_free (void *ap)
{
    Header *bp, *p;
    Task_Heap *p_heap = &heap;
    uint32_t remaining_units;

    if (ap == NULL)
    {
        /* If ap is NULL nothing to free */
        return (true);
    }
    bp = (Header *)ap - 1;
    if ((uintptr_t)bp & 0x1f)
    {
        FW_PRINT (FW_ERR, "The Malloced pointer must be 32 byte aligned");
        return (false);
    }
    if (bp < (&p_heap->heap[0]) || bp >= ((Header *)(uintptr_t)p_heap->Heap_Size))
    {
        FW_PRINT (FW_ERR, "Heap corrupted - block outside the heap area");
        return (false);
    }
    if ((bp->magic_1 != MAGIC_1) || (bp->magic_2 != MAGIC_2))
    {
        FW_PRINT (FW_ERR, "Heap corrupted. Magic values overwritten");
        return (false);
    }
    if (bp + bp->size > ((Header *)(uintptr_t)p_heap->Heap_Size))
    {
        FW_PRINT (FW_ERR, "Heap size element corrupted - wrong size");
        return (false);
    }

    FW_PRINT (FW_INFO, "\nfreeing %d units\n", bp->size);
    p = p_heap->freep;
    if (bp->Next_allocated_block->status == BLOCK_FREE)
    {
        bp->size += bp->Next_allocated_block->size;
        remaining_units = bp->size;
        FW_PRINT (FW_INFO, "Remaining units = %d\n", remaining_units);
        bp->Next_allocated_block->Next_allocated_block->Prev_allocated_block = bp;
        bp->ptr = bp->Next_allocated_block->ptr;
        bp->Prev_free_block = bp->Next_allocated_block->Prev_free_block;
        bp->Next_allocated_block->ptr->Prev_free_block = bp;
        bp->Next_allocated_block->Prev_free_block->ptr = bp;
        bp->Next_allocated_block = bp->Next_allocated_block->Next_allocated_block;
        bp->status = BLOCK_FREE;
    }
    if (bp->Prev_allocated_block->status == BLOCK_FREE)
    {
        bp->Prev_allocated_block->size += bp->size;
        remaining_units = bp->Prev_allocated_block->size;
        bp->Next_allocated_block->Prev_allocated_block = bp->Prev_allocated_block;
        bp->Prev_allocated_block->Next_allocated_block = bp->Next_allocated_block;
        if (bp->status == BLOCK_FREE)
        {
            bp->Prev_free_block->ptr = bp->ptr;
            bp->ptr->Prev_free_block = bp->Prev_free_block;
        }
        FW_PRINT (FW_INFO, "Remaining units = %d\n", remaining_units);
        bp->status = BLOCK_FREE;
    }
    if (bp->status == BLOCK_ALLOCATED)
    {
        bp->status = BLOCK_FREE;
        bp->ptr = p->ptr;
        p->ptr->Prev_free_block = bp;
        p->ptr = bp;
        bp->Prev_free_block = p;
    }
    p_heap->freep = p_heap->freep->ptr;
    return (true);
}
