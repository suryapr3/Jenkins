#ifndef _ADC_CPU_H_

// ******************************************************************************
// ------------------------------------------------------------------------------
//                               INTEL CONFIDENTIAL
// ------------------------------------------------------------------------------
//    Copyright (c) 2018 - 2024 Intel Corporation
//
//    This software and the related documents are Intel copyrighted materials,
//    and your use of them is governed by the express license under which they
//    were provided to you ("License").
//    Unless the License provides otherwise, you may not use, modify, copy, publish,
//    distribute, disclose or transmit this software or the related documents
//    without Intel's prior written permission.
//
//    This software and the related documents are provided as is, with no express or
//    implied warranties, other than those that are expressly stated in the License.
// ------------------------------------------------------------------------------
//
//    DO NOT EDIT THIS FILE !!!
//
//    This file has been automatically generated by OneSource
//
// ******************************************************************************

#ifndef __KERNEL__
#include <stdint.h>
#endif // __KERNEL__
// ******************************************* Base address macros

#define ANT0_CPU_SRAM_BASE    ( 0x049a0000 )
#define ANT1_CPU_SRAM_BASE    ( 0x04ba0000 )
#define ANT2_CPU_SRAM_BASE    ( 0x04da0000 )
#define ANT3_CPU_SRAM_BASE    ( 0x04fa0000 )

// ******************************************* /Base address macros

#define ADC_CPU_DRAM0_ARR_SZ0 (16384)
#define ADC_CPU_IRAM0_ARR_SZ0 (16384)
// ******************************************* AddressSpace struct
typedef struct
{
    uint32_t DRAM0[16384];   /*< Address offset = 0x0 (32 bit) */
    uint32_t IRAM0[16384];   /*< Address offset = 0x10000 (32 bit) */
} adc_cpu_t;     // size: 0x0008

// AddressSpace struct pointer
//
#define ANT0_CPU_SRAM    ((adc_cpu_t*) ANT0_CPU_SRAM_BASE)
#define ANT1_CPU_SRAM    ((adc_cpu_t*) ANT1_CPU_SRAM_BASE)
#define ANT2_CPU_SRAM    ((adc_cpu_t*) ANT2_CPU_SRAM_BASE)
#define ANT3_CPU_SRAM    ((adc_cpu_t*) ANT3_CPU_SRAM_BASE)

// ******************************************* /Address Space

#endif      // _ADC_CPU_H_

