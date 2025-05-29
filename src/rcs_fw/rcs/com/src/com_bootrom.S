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
.section    .srom.text, "ax"
                             // a = allocatable
                             // x = executable
.global __BootRom

//
//   The productive FW is linked for VECTOR_SELECT == 1 where the Reset Vector is in ISRAM.
//   This BootROM image/code will simply jump to the ISRAM reset vector location.  In this way,
//   if VECTOR_SELECT in HW is 0 (ROM boot), and this binary is linked as VECTOR_SELECT == 1, we
//   still get out of reset.
//
//
//   Compute the address of the reset vector using no literals.  When using literals here, the
//   compiler is placing them before the code, and it's important that this code is located at
//   address 0.
//
//   ResetVector location is 0x1000_0400 (for all RCS CPUs).   If this address changes (due to HW re-define)
//   this must also change.
//

.align 4
__BootRom:
movi a0, 1
slli a0, a0, 28    // Shift left 1->0x10000000
jx  a0

