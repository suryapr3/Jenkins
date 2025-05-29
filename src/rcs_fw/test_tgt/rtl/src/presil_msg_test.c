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
 * @file    presil_msg_test.c
 * @brief   Pre-Silicon Test Case for message handler
 * @details The testcase writes the message to the shared memory
 *          and triggers message event handler
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include "presil_com_assert.h"
#include "presil_com_print.h"
#include "presil_com_shared_memory_read_write.h"
#include "rtl_api.h"
#include <stdint.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define MSG_LEN         16
#define SHARED_MEM_BASE 0x00200000

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

uint32_t msg_data_word[MSG_LEN];
uint32_t read_msg_data_word[MSG_LEN];
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
 * @brief      msg_handler_test writes
 * @param [in]
 * @return          none
 */

void msg_handler_test ()
{
    int size_test = 100, *p_test;
    p_test = 0;
    int epoch = 333, bfn = 45, timer_value = 77;
    char error = 't';
    FW_PRINT (FW_INFO, "Test stub fw info");
    FW_PRINT (FW_WARN, "size_test  = %d", size_test);
    FW_PRINT (FW_DEBUG, "epoch:0x%08x bfn:0x%08x --> tick: 0x%08x", epoch, bfn, timer_value);
    FW_PRINT (FW_ERR, "%c", error);
    FW_PRINT (FW_NOTE, "error = %c  epoch = %d ", error, epoch);
    // assert tests
    RT_ASSERT_HERE ();
    RT_ASSERT_IN_RANGE (epoch, 1, 255);
    RT_ASSERT_EQUAL (bfn, 0);
    RT_ASSERT_NOT_EQUAL (epoch, 333);
    RT_ASSERT_POINTER (p_test);
    // shared memory read write tests
    for (int i = 0; i < MSG_LEN; i++) { msg_data_word[i] = MSG_LEN + i; }
    int mem_addr = SHARED_MEM_BASE + MSG_LEN;
    FW_PRINT (FW_INFO, "0x%x", mem_addr);
    com_shared_mem_write (&mem_addr, msg_data_word, MSG_LEN);
    com_shared_mem_read (read_msg_data_word, &mem_addr, MSG_LEN);
    for (int i = 0; i < MSG_LEN; i++) { FW_PRINT (FW_INFO, " read data [%d]: %u", i, read_msg_data_word[i]); }
    mem_addr = SHARED_MEM_BASE + 0x40;
    com_shared_mem_write (&mem_addr, &epoch, 1);
    mem_addr = SHARED_MEM_BASE + 0x44;
    com_shared_mem_write (&mem_addr, &bfn, 1);
    mem_addr = SHARED_MEM_BASE + MSG_LEN;
    com_shared_mem_read (read_msg_data_word, &mem_addr, MSG_LEN);
    for (int i = 0; i < MSG_LEN; i++)
    {
        FW_PRINT (FW_INFO, " read data [%d]: %u", i, read_msg_data_word[i]);
    }

    FW_PRINT (FW_INFO, "exit msg handler");
}
