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
 * @file    spl_unpack.s
 * @brief   unpacks the spl code
 * @details  SPL code is loaded into SRAM start location.
 * This file has the code to unpack the SPL code and place into IRAM and DRAM
 */
.section    .sram0.text, "ax"
                         // a = allocatable
                         // x = executable
.global __Unpack_SPL
.align 4

__Unpack_SPL:
    j   __Unpack_SPL_start
   .size   __Unpack_SPL, . - __Unpack_SPL
.align  4
.literal_position   // tells the assembler/linker to place literals here
.align  4
.global __Unpack_SPL_start

__Unpack_SPL_start:
    movi    a2,_rom_store_table //_rom_store_table
    beqz    a2, unpackdone
unpack: l32i    a3, a2, 0   // start vaddr
    l32i    a4, a2, 4   // end vaddr
    l32i    a5, a2, 8   // store vaddr
    addi    a2, a2, 12
    bgeu    a3, a4, upnext  // skip unless start < end
uploop: l32i    a6, a5, 0
    addi    a5, a5, 4
    s32i    a6, a3, 0
    addi    a3, a3, 4
    bltu    a3, a4, uploop
    j   unpack
upnext: bnez    a3, unpack
    bnez    a5, unpack
unpackdone:

/*
 *  For processors with relocatable vectors, apply any alternate
 *  vector base given to xt-genldscripts, which sets the
 *  _memmap_vecbase_reset symbol accordingly.
 */

    movi    a2, _memmap_vecbase_reset   /* note: absolute symbol, not a ptr */
    wsr.vecbase a2

//  Windowed register init, so we can call windowed code (eg. C code).
    movi    a1, 1
    wsr.windowstart a1
    wsr.windowbase  a0
    rsync
    movi    a0, _start           // possibly a different a0, clear it
    callx0   a0      // jump to _start (in crt1-*.S)


