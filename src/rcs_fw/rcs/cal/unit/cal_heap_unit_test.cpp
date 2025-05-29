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
 * @file    cal_heap_unit_test.cpp
 * @brief   Unit test for the heap functionality
 * @details Detailed description if necessary
 * @todo    Write documentation for source file cal_heap_unit_test.cpp
 */

#include <cstdint>
#if (CPU_CAL)
#else
#error "Not CAL CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"
#include "rf_calib_com_heap.h"
#include "stdlib.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

#define TASK_HEAP_SIZE 153600 // Needs to be multiple of 32
static uint8_t heap_storage[TASK_HEAP_SIZE] __attribute__ ((section (".dram0.calib_matrix")));

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
int main (int argc, char *argv[])
{
    uint8_t heap_check[101];
    if (rf_calib_heap_create (heap_check, 101))
    {
        FW_PRINT (FW_ERR, "FAIL: heap create must have returned error ");
        return (-1);
    }
    FW_PRINT (FW_INFO, "PASS: heap creation check. Error print is expected");
    if (rf_calib_heap_create (heap_storage, TASK_HEAP_SIZE))
    {
        FW_PRINT (FW_INFO, "PASS: Maximum heap size creation successful");
    }
    else
    {
        FW_PRINT (FW_ERR, "FAIL: Maximum heap size creation should have been successful");
        return (-1);
    }
    // Check for the maximum available allocation.
    // The maximum allocation possible is heap_size-32 bytes
    uint8_t *p_test;
    if ((p_test = (uint8_t *)rf_calib_calloc (TASK_HEAP_SIZE - 32, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_ERR, "FAIL: Maximum heap size allocation test failed");
        return (-1);
    }
    FW_PRINT (FW_INFO, "PASS: Maximum heap size allocation");
    // Try allocation when heap is full
    uint8_t *p_test1;
    if ((p_test1 = (uint8_t *)rf_calib_calloc (1, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_INFO, "PASS: allocation when heap is full test passed with NULL pointer return");
    }
    else
    {
        FW_PRINT (FW_INFO, "FAIL: allocation when heap is full test failed");
        return (-1);
    }
    if (rf_calib_free (p_test))
    {
        FW_PRINT (FW_INFO, "PASS: free test with proper pointer test passed");
    }
    else
    {
        FW_PRINT (FW_ERR, "FAIL: free test with proper pointer test failed");
        return (-1);
    }
    // Try to free a pointer outside the heap area
    p_test = &heap_storage[TASK_HEAP_SIZE];
    p_test += 32;
    if (rf_calib_free (p_test))
    {
        FW_PRINT (FW_ERR, "FAIL: Freeing outside the heap area should have failed");
        return (-1);
    }
    FW_PRINT (FW_INFO, "PASS: Freeing pointer outside the heap area returned false. Error print expected");
    if ((p_test = (uint8_t *)rf_calib_calloc (10, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to allocate pointer");
    }
    if ((p_test1 = (uint8_t *)rf_calib_calloc (10, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to allocate pointer");
    }
    // Corrupt the heap outside the allocated area
    // Make p_test1 to write to the p_test header area
    uint32_t *temp;
    temp = (uint32_t *)p_test1;
    temp[8] = 0x5;
    temp[9] = 0x34;
    temp[10] = 0x56;
    if (rf_calib_free (p_test))
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to catch the magic corruption");
        return (-1);
    }
    else
    {
        FW_PRINT (FW_INFO, "PASS: Magic corruption is caught. Error print is expected");
    }
    // recreate the heap
    if (!rf_calib_heap_create (heap_storage, TASK_HEAP_SIZE))
    {
        {
            FW_PRINT (FW_ERR, "FAIL: Recreation of Maximum heap size creation should have been successful");
            return (-1);
        }
    }
    if ((p_test = (uint8_t *)rf_calib_calloc (10, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to allocate pointer");
    }
    if ((p_test1 = (uint8_t *)rf_calib_calloc (10, sizeof (uint8_t))) == NULL)
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to allocate pointer");
    }
    // Corrupt the size in the header to point to outside the heap area
    temp = (uint32_t *)p_test1;
    temp[10] = 0x3000;
    if (rf_calib_free (p_test))
    {
        FW_PRINT (FW_ERR, "FAIL: Unable to catch the size corruption");
        return (-1);
    }
    else
    {
        FW_PRINT (FW_INFO, "PASS: size corruption is caught. Error print is expected");
    }
    return (0);
}
