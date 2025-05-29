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
 * @file    com_exception.c
 * @brief   Exception handler for debug.
 * @details Catch exceptional events from the CPU and provide as much post-mortem analysis as possible.
 * @todo    Trax..
 */
#include "com_assert.h"
#include "com_print.h"
#include "com_trax.h"
#include "com_error.h"
#include "com_msgs_enum.h"
#include "xtensa/core-macros.h"
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

enum exception_t
{
    USER_EXCEPTION = 0,
    KERNEL_EXCEPTION = 1,
    DOUBLE_EXCEPTION = 2,
    DEBUG_EXCEPTION = 3
};

struct exception_frame
{
    uint32_t pc;
    uint32_t ps;
    uint32_t unused;
    uint32_t a0;
    uint32_t a2;
    uint32_t a3;
    uint32_t a4;
    uint32_t a5;
};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Handler for all CPU exceptions.   Perform appropriate diagnostics.
 * @param [in]      exception_vector:  vector level causing the exception.
 * @param [in]      frame: CPU/stack frame information assembled by low-level handlers.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_cpu_exception (enum exception_t const exception_vector, struct exception_frame *frame)
{
    uint32_t const cause = XT_RSR_EXCCAUSE ();
    uint32_t const addr = XT_RSR_EXCVADDR ();

    if (com_trax_stop ())
        com_trax_store_trace ();

    FW_PRINT (FW_ERR, "CPU exception %d cause: 0x%X  pc: 0x%X  addr: 0x%X", exception_vector, cause, frame->pc, addr);
    FW_PRINT (FW_INFO, "    pc  : %x", frame->pc);
    FW_PRINT (FW_INFO, "    ps  : %x", frame->ps);
    FW_PRINT (FW_INFO, "    a0  : %x", frame->a0);
    FW_PRINT (FW_INFO, "    a2  : %x", frame->a2);
    FW_PRINT (FW_INFO, "    a3  : %x", frame->a3);
    FW_PRINT (FW_INFO, "    a4  : %x", frame->a4);
    FW_PRINT (FW_INFO, "    a5  : %x", frame->a5);

    FW_SEND_ERR_RB (e_EXCEPTION_ERR, (e_reason_code_type_t) (int)exception_vector, cause, frame->pc, addr, frame->ps, frame->a0, frame->a2,
                    frame->a3, frame->a4, frame->a5);

    RT_ASSERT_HERE ();
    for (;;) { INTRINSIC_WAIT_FOR_IRQ; } // infinite loop
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

void com_cpu_user_exception (void *arg)
{
    com_cpu_exception (USER_EXCEPTION, (struct exception_frame *)arg);
}

void com_cpu_kernel_exception (void *arg)
{
    com_cpu_exception (KERNEL_EXCEPTION, (struct exception_frame *)arg);
}

void com_cpu_double_exception (void *arg)
{
    com_cpu_exception (DOUBLE_EXCEPTION, (struct exception_frame *)arg);
}

void com_cpu_debug_exception (void *arg)
{
    com_cpu_exception (DEBUG_EXCEPTION, (struct exception_frame *)arg);
}
