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
// Derived from:
//
// user-vector-min.S  -  Minimal User Vector for General Exceptions
//	Takes less table space, but does not allow registering new handlers.
// $Id: //depot/rel/Homewood/ib.8/Xtensa/OS/xtos/xea2/user-vector-min.S#1 $

// Copyright (c) 2003-2018 Cadence Design Systems, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <xtensa/coreasm.h>
#include <xtensa/config/system.h>
#include "xtos-internal.h"


// Defined in com/com_exception.c
.global com_cpu_user_exception
.global com_cpu_kernel_exception
.global com_cpu_double_exception
.global com_unhandled_interrupt

//
//  Level 1 IRQ will flow through the same handler and will save minimal state.
//  For exceptions, save more state to the frame before calling the C handler for diagnostics.
//
.macro invoke_c_exception_handler c_handler
    // Save additional information to the stack.
    rsr.ps a2
    s32i   a2, a1, UEXC_ps
    rsr.epc1 a2
    s32i   a2, a1, UEXC_pc
    s32i   a0, a1, UEXC_vpri
    s32i   a4, a1, UEXC_a4
    s32i   a5, a1, UEXC_a5

    // Enable Window exceptions prior to invoking C handler.
    // Note: It is possible for some prior context to be clobbered by subsequent C calls as we didn't properly spill
    //       pre-exception registers.   Since we never return from here anyhow, this context is no longer needed.
    //
    movi   a2, PS_WOECALL4_ABI|PS_UM|PS_INTLEVEL(XCHAL_EXCM_LEVEL)
    wsr.ps a2
    # Argument (a6) points to he saved stack frame.
    mov a6, a1
    movi  a3, \c_handler
    callx4 a3
    // No return.
.endm

// keep a counter for exception 11:
.section .data
.global exception_11_cnt
.align 4
exception_11_cnt:
    .word   0x00000000

// defined in com_lock.c
.global com_shm_lock_first_addr
.global com_shm_lock_last_addr

//
//  Provide minimal environment to call a C routine to diagnose a User CPU Exception.
//  A legitimate handler is required here to interface with the XTOS UserVector processing.
//  This condition is fatal, the execption handler is not expected to return.
//
.section .iram0.text

_user_exception_c_trampoline:
    invoke_c_exception_handler com_cpu_user_exception
    // No return.

// Note: workaround for exclusive access HW bug:
//       Shared memory may report exclusive error, retry if the access in in the designated area.
//
.align 4
.global _user_exception_11_handler
_user_exception_11_handler:
    // count num of occur:
    movi    a2, exception_11_cnt
    l32i    a3, a2, 0
    addi    a3, a3, 1
    s32i    a3, a2, 0

    // lock used RSM boundary check:
    rsr.excvaddr    a2              // get exception addr
    movi    a3, com_shm_lock_first_addr
    l32i    a3, a3, 0               // lower boundary
    blt     a2, a3, 2f
    movi    a3, com_shm_lock_last_addr
    l32i    a3, a3, 0               // upper boundary
    blt     a3, a2, 2f

    l32i    a4, a1, UEXC_a4         // restore a4
    l32i    a3, a1, UEXC_a3         // restore a3
    l32i    a2, a1, UEXC_a2         // restore a2
    addi    a1, a1, ESF_TOTALSIZE   // restore a1
    rfe
2:
    l32i    a3, a3, 0
    jx      a3                      // jump to Illegal Instruction handler
.size   _user_exception_11_handler, . - _user_exception_11_handler

/*
 *  Read-only minimal table of assembly-level exception handlers for user vectored exceptions.
 *  Provides entries for SYSCALL, MOVSP, level-1 interrupt, and exclusive error causes.
 *  Other errors will be routed to FW error reporting routine for failure analysis.
 */
.section .dram0.rodata, "a"
.align 4

__handler_table:
    .word  _user_exception_c_trampoline // 0 Illegal Instruction, and causes > 11
    .word  _xtos_syscall_handler        // 1 SYSCALL Instruction
    .word  _user_exception_c_trampoline // 2 Instruction Fetch Error
    .word  _user_exception_c_trampoline // 3 Load/Store Error
    .word  _xtos_l1int_handler          // 4 Level-1 Interrupt
# if XCHAL_HAVE_WINDOWED && !defined(__XTENSA_CALL0_ABI__)
    .word  _xtos_alloca_handler         // 5 Alloca (MOVSP Instruction)
# else
    .word  _user_exception_c_trampoline // 5 Alloca (MOVSP Instruction) (not configured)
# endif
    .word  _user_exception_c_trampoline // 6
    .word  _user_exception_c_trampoline // 7
    .word  _user_exception_c_trampoline // 8
    .word  _user_exception_c_trampoline // 9
    .word  _user_exception_c_trampoline // 10
    .word  _user_exception_11_handler   // 11 exclusive access violation exception

.size   __handler_table, . - __handler_table
.text
//
//  Exception Vectors.    These vectors are placed by the linker where the CPU needs them.
//  Still using XTOS for L1 IRQ, however exeptions are handled by the FW handler structure.
//
.begin   literal_prefix  .UserExceptionVector
.section  .UserExceptionVector.text, "ax"
.align 4
.global _UserExceptionVector

_UserExceptionVector:
    // DO NOT CHANGE, Xtensa handlers assume the state set up here.
    addi    a1, a1, -ESF_TOTALSIZE  // allocate exception stack frame, etc.
    s32i    a2, a1, UEXC_a2
    s32i    a3, a1, UEXC_a3
    rsr.exccause    a2              // get exception cause
    movi    a3, __handler_table
    bgeui   a2, 12, 1f              // causes 12 and above map to zero
    addx4   a3, a2, a3              // index by cause if 1 .. 11
1:
    l32i    a3, a3, 0
    s32i    a4, a1, UEXC_a4
    jx      a3                      // jump to cause-specific handler

.size   _UserExceptionVector, . - _UserExceptionVector
.end   literal_prefix


.begin  literal_prefix  .DoubleExceptionVector
.section  .DoubleExceptionVector.text, "ax"

.align 4
.global _DoubleExceptionVector
_DoubleExceptionVector:
    // Allocate exception stack frame, etc for consistency with User Ex.
    addi   a1, a1, -ESF_TOTALSIZE
    s32i   a2, a1, UEXC_a2
    s32i   a3, a1, UEXC_a3

    invoke_c_exception_handler com_cpu_double_exception
    // Does not Return.
    .size   _DoubleExceptionVector, . - _DoubleExceptionVector
.end  literal_prefix




.begin  literal_prefix  .KernelExceptionVector
.section   .KernelExceptionVector.text, "ax"

.align 4
.global _KernelExceptionVector
_KernelExceptionVector:
    // Allocate exception stack frame, etc for consistency with User Ex.
    // Note this not expected to ever be reached as Kernel mode isn't enabled in this FW.
    addi   a1, a1, -ESF_TOTALSIZE
    s32i   a2, a1, UEXC_a2
    s32i   a3, a1, UEXC_a3

    invoke_c_exception_handler com_cpu_kernel_exception
    // Does not Return.
    .size   _KernelExceptionVector, . - _KernelExceptionVector
.end  literal_prefix


.begin  literal_prefix  .DebugExceptionVector
.section   .DebugExceptionVector.text, "ax"

.align 4
.global _DebuglExceptionVector
_DebugExceptionVector:
    // Allocate exception stack frame, etc for consistency with User Ex.
    addi   a1, a1, -ESF_TOTALSIZE
    s32i   a2, a1, UEXC_a2
    s32i   a3, a1, UEXC_a3

    invoke_c_exception_handler com_cpu_debug_exception
    // Does not Return.
    .size   _DebugExceptionVector, . - _DebugExceptionVector
.end  literal_prefix


#if XCHAL_HAVE_INTERRUPTS

	.data

	.global	_xtos_intstruct
	.align	8

_xtos_intstruct:
# if XTOS_VIRTUAL_INTENABLE
	.global	xtos_enabled
	.type	xtos_enabled,@object
	.size	xtos_enabled,4
	.global	xtos_vpri_enabled
	.type	xtos_vpri_enabled,@object
	.size	xtos_vpri_enabled,4

xtos_enabled:		.word	0
xtos_vpri_enabled:	.word	0xFFFFFFFF
# endif

# if XTOS_VIRTUAL_INTERRUPT
#  error Virtualized INTERRUPT register not yet supported.
	.global	xtos_pending
	.type	xtos_pending,@object
	.size	xtos_pending,4
xtos_pending:		.word	0
# endif

/*
 *  Table of C-level interrupt handlers (and args, etc) for each interrupt.
 *  NOTE:  if the NSA/NSAU instructions are configured, then to save a few
 *  cycles in the interrupt dispatcher code, this table is filled in reverse.
 *  C code uses the MAPINT() macro defined in xtos-internal.h to index entries.
 *  NOTE:  Under some conditions (turned off by default in xtos-params.h),
 *  this table gets properly initialized by the _xtos_init() function in
 *  init.c .  NOTA:  A future enhancement may be to always configure
 *  and build this table at build-time rather than ever doing it at run-time.
 */
#define i	.Li	/* workaround a silly GDB testsuite regression */
.begin  literal_prefix  .rtos
.section   .rtos.text, "ax"
.data
.align	8
.global	xtos_interrupt_table
.type xtos_interrupt_table,@object

xtos_interrupt_table:
	.set	i, XCHAL_HAVE_NSA*(XCHAL_NUM_INTERRUPTS-1)
	.rept	XCHAL_NUM_INTERRUPTS
	 .word	com_unhandled_interrupt
	 .word	i			// parameter: interrupt number
	 .set	i, i+1-(XCHAL_HAVE_NSA*2)
	.endr

	.size	xtos_interrupt_table, . - xtos_interrupt_table
.end literal_prefix

# if XIE_EXTEND
	/*  MUST *IMMEDIATELY* follow xtos_interrupt_table:  */
	.global	xtos_interrupt_mask_table
	.type	xtos_interrupt_mask_table,@object


xtos_interrupt_mask_table:
	.set	i, XCHAL_HAVE_NSA*(XCHAL_NUM_INTERRUPTS-1)
	.rept	XCHAL_NUM_INTERRUPTS
	/*  Default to all low-priority (level-one) interrupts at their own virtual priority:  */
#  if XTOS_SUBPRI_ORDER == XTOS_SPO_ZERO_HI
	 .word	((1<<i)-1) | ~XCHAL_LOWPRI_MASK	// vpri_mask default - lower-numbered ints (and high/medium-pri ints) pre-empt other low-pri ints
#  else
	 .word	(-2*(1<<i)) | ~XCHAL_LOWPRI_MASK // vpri_mask default - higher-numbered ints (and high/medium-pri ints) pre-empt other low-pri ints
#  endif
	 .word	(1<<i)		// level_mask default - each low-pri (level-one) interrupt at its own subpriority
	 .set	i, i+1-(XCHAL_HAVE_NSA*2)
	.endr

	.size	xtos_interrupt_mask_table, . - xtos_interrupt_mask_table
# endif /*XIE_EXTEND*/

.text
.align 4
.global xtos_unhandled_interrupt
.type      xtos_unhandled_interrupt,@function
xtos_unhandled_interrupt:
    // This is overwritten by User defined handler
    //Should not be accessed
    .size   xtos_unhandled_interrupt, . - xtos_unhandled_interrupt

#endif /* XCHAL_HAVE_INTERRUPTS */


//
//  Provide a Reset Hook for system initialization prior to CRT or stack initialization.
//   - Initialize the stack area to a constant.   In pre-sil this fixes some aggressive X-propagation.
//

_stack_sentry_ptr:
.word _stack_sentry   // stack end.
.word 0xC0DE5AFE      // stack fill value.


.text
.align 4
.global __reset_hook
__reset_hook:
    movi a2, _stack_sentry_ptr     // a2 end of stack.
    movi a3, __stack               // a3 start of stack.
    addi a3, a3, -4
    l32i a4, a2, 4                 // a4 constant to initialize stack.
    //movi a4, 0
    l32i a2, a2, 0
1:
    s32i a4, a3, 0
    addi a3, a3, -4                // decrement stack until we hit end of stack.
    bgeu a3, a2, 1b
    ret                            // Call0 ABI return.

