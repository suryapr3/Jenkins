#ifndef _HUB_RCS_APB_H_
#define _HUB_RCS_APB_H_

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

#define HUB_RCS_APB_BASE      ( 0x01b02000 )

// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define HUB_RCS_APB_HUB_SCRATCH_OFFSET ( 0x00000000U )
#define HUB_RCS_APB_HUB_GPIO_INTR_OFFSET ( 0x00000010U )
#define HUB_RCS_APB_HUB_GPIO_RCS_0_OFFSET ( 0x00000014U )
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_OFFSET ( 0x00000018U )
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_OFFSET ( 0x0000001cU )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define HUB_RCS_APB_HUB_SCRATCH_ADR (( ( HUB_RCS_APB_BASE ) + ( HUB_RCS_APB_HUB_SCRATCH_OFFSET ) ))
#define HUB_RCS_APB_HUB_GPIO_INTR_ADR (( ( HUB_RCS_APB_BASE ) + ( HUB_RCS_APB_HUB_GPIO_INTR_OFFSET ) ))
#define HUB_RCS_APB_HUB_GPIO_RCS_0_ADR (( ( HUB_RCS_APB_BASE ) + ( HUB_RCS_APB_HUB_GPIO_RCS_0_OFFSET ) ))
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_ADR (( ( HUB_RCS_APB_BASE ) + ( HUB_RCS_APB_HUB_GPIO_RCS_1_0_OFFSET ) ))
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_ADR (( ( HUB_RCS_APB_BASE ) + ( HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief HUB_RCS_APB_REG_HUB_MAP_SCRATCH register description at address offset 0x0
  *
  * Register default value:        0x00000000
  * Register full path in IP: hub_rcs_apb/reg/HUB_MAP/Scratch
  * SYSCON Control scratchpad register.
  */

typedef union {
  struct {
    uint32_t SCRATCHPAD_L : 8;
    ///< Scratchpad low (warm reset)
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SCRATCHPAD_M : 8;
    ///< Scratchpad low (cold reset)
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SCRATCHPAD_H : 16;
    ///< Scratchpad high (sticky, power-up reset)
    ///< AccessType="RW/P" BitOffset="16" ResetValue="0x0"
  } ;
  uint32_t value;
} hub_rcs_apb_hub_scratch_reg_t;

#define HUB_RCS_APB_HUB_SCRATCH_DEFAULT (0x00000000U)
#define HUB_RCS_APB_HUB_SCRATCH_RD_MASK (0xffffffffU)
#define HUB_RCS_APB_HUB_SCRATCH_WR_MASK (0xffffffffU)


///< Scratchpad low (warm reset)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_L_BF_OFF ( 0)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_L_BF_WID ( 8)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_L_BF_MSK (0x000000FF)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_L_BF_DEF (0x00000000)

///< Scratchpad low (cold reset)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_M_BF_OFF ( 8)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_M_BF_WID ( 8)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_M_BF_MSK (0x0000FF00)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_M_BF_DEF (0x00000000)

///< Scratchpad high (sticky, power-up reset)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_H_BF_OFF (16)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_H_BF_WID (16)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_H_BF_MSK (0xFFFF0000)
#define HUB_RCS_APB_HUB_SCRATCH_SCRATCHPAD_H_BF_DEF (0x00000000)


/** @brief HUB_RCS_APB_REG_HUB_MAP_GPIO_INTERRUPT register description at address offset 0x10
  *
  * Register default value:        0x0000000D
  * Register full path in IP: hub_rcs_apb/reg/HUB_MAP/gpio_interrupt
  * GPIO Interrupt I/O Control Register
  */

typedef union {
  struct {
    uint32_t DR : 2;
    ///< Output impedance.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x1"
    uint32_t POE : 1;
    ///< When set to 1, the GPIO interrupt pin is an output. When set to 0,
    ///< the GPIO interrupt pin is an input.
    ///< AccessType="RW" BitOffset="2" ResetValue="0x1"
    uint32_t LPR : 1;
    ///< When set to 1, the receiver of GPIO interrupt pin is powered down.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x1"
    uint32_t WKPDE : 1;
    ///< When set to 1, enables weak pull-down on the GPIO interrupt pin. This
    ///< should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t WKPUE : 1;
    ///< When set to 1, enables weak pull-up on the GPIO interrupt pin. This
    ///< should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t  : 10;
    ///< Reserved
    ///< AccessType="RO" BitOffset="6" ResetValue="None"
    uint32_t MASK : 16;
    ///< Maskable
    ///< AccessType="WO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} hub_rcs_apb_hub_gpio_intr_reg_t;

#define HUB_RCS_APB_HUB_GPIO_INTR_DEFAULT (0x0000000dU)
#define HUB_RCS_APB_HUB_GPIO_INTR_RD_MASK (0x0000003fU)
#define HUB_RCS_APB_HUB_GPIO_INTR_WR_MASK (0xffff003fU)


///< Output impedance.
#define HUB_RCS_APB_HUB_GPIO_INTR_DR_BF_OFF ( 0)
#define HUB_RCS_APB_HUB_GPIO_INTR_DR_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_INTR_DR_BF_MSK (0x00000003)
#define HUB_RCS_APB_HUB_GPIO_INTR_DR_BF_DEF (0x00000001)

///< When set to 1, the GPIO interrupt pin is an output. When set to 0,
///< the GPIO interrupt pin is an input.
#define HUB_RCS_APB_HUB_GPIO_INTR_POE_BF_OFF ( 2)
#define HUB_RCS_APB_HUB_GPIO_INTR_POE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_INTR_POE_BF_MSK (0x00000004)
#define HUB_RCS_APB_HUB_GPIO_INTR_POE_BF_DEF (0x00000004)

///< When set to 1, the receiver of GPIO interrupt pin is powered down.
#define HUB_RCS_APB_HUB_GPIO_INTR_LPR_BF_OFF ( 3)
#define HUB_RCS_APB_HUB_GPIO_INTR_LPR_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_INTR_LPR_BF_MSK (0x00000008)
#define HUB_RCS_APB_HUB_GPIO_INTR_LPR_BF_DEF (0x00000008)

///< When set to 1, enables weak pull-down on the GPIO interrupt pin. This
///< should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPDE_BF_OFF ( 4)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPDE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPDE_BF_MSK (0x00000010)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPDE_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO interrupt pin. This
///< should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPUE_BF_OFF ( 5)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPUE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPUE_BF_MSK (0x00000020)
#define HUB_RCS_APB_HUB_GPIO_INTR_WKPUE_BF_DEF (0x00000000)
#define HUB_RCS_APB_HUB_GPIO_INTR_MASK_BF_OFF (16)
#define HUB_RCS_APB_HUB_GPIO_INTR_MASK_BF_WID (16)
#define HUB_RCS_APB_HUB_GPIO_INTR_MASK_BF_MSK (0xFFFF0000)


/** @brief HUB_RCS_APB_REG_HUB_MAP_GPIO_RCS_0 register description at address offset 0x14
  *
  * Register default value:        0x0000000D
  * Register full path in IP: hub_rcs_apb/reg/HUB_MAP/gpio_rcs_0
  * GPIO RCS 0 [31:0] I/O Control Register
  */

typedef union {
  struct {
    uint32_t DR : 2;
    ///< Output impedance.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x1"
    uint32_t POE : 1;
    ///< When set to 1, the GPIO RCS 0 [31:0] pins are outputs. When set to
    ///< 0, the GPIO RCS 0 [31:0] pins are inputs.
    ///< AccessType="RW" BitOffset="2" ResetValue="0x1"
    uint32_t LPR : 1;
    ///< When set to 1, the receiver of GPIO RCS 0 [31:0] pins are powered
    ///< down.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x1"
    uint32_t WKPDE : 1;
    ///< When set to 1, enables weak pull-down on the GPIO RCS 0 [31:0] pins.
    ///< This should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t WKPUE : 1;
    ///< When set to 1, enables weak pull-up on the GPIO RCS 0 [31:0] pins.
    ///< This should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t  : 10;
    ///< Reserved
    ///< AccessType="RO" BitOffset="6" ResetValue="None"
    uint32_t MASK : 16;
    ///< Maskable
    ///< AccessType="WO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} hub_rcs_apb_hub_gpio_rcs_0_reg_t;

#define HUB_RCS_APB_HUB_GPIO_RCS_0_DEFAULT (0x0000000dU)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_RD_MASK (0x0000003fU)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WR_MASK (0xffff003fU)


///< Output impedance.
#define HUB_RCS_APB_HUB_GPIO_RCS_0_DR_BF_OFF ( 0)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_DR_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_DR_BF_MSK (0x00000003)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_DR_BF_DEF (0x00000001)

///< When set to 1, the GPIO RCS 0 [31:0] pins are outputs. When set to
///< 0, the GPIO RCS 0 [31:0] pins are inputs.
#define HUB_RCS_APB_HUB_GPIO_RCS_0_POE_BF_OFF ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_POE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_POE_BF_MSK (0x00000004)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_POE_BF_DEF (0x00000004)

///< When set to 1, the receiver of GPIO RCS 0 [31:0] pins are powered
///< down.
#define HUB_RCS_APB_HUB_GPIO_RCS_0_LPR_BF_OFF ( 3)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_LPR_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_LPR_BF_MSK (0x00000008)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_LPR_BF_DEF (0x00000008)

///< When set to 1, enables weak pull-down on the GPIO RCS 0 [31:0] pins.
///< This should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPDE_BF_OFF ( 4)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPDE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPDE_BF_MSK (0x00000010)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPDE_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO RCS 0 [31:0] pins.
///< This should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPUE_BF_OFF ( 5)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPUE_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPUE_BF_MSK (0x00000020)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_WKPUE_BF_DEF (0x00000000)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_MASK_BF_OFF (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_MASK_BF_WID (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_MASK_BF_MSK (0xFFFF0000)


/** @brief HUB_RCS_APB_REG_HUB_MAP_GPIO_RCS_1_1_0 register description at address offset 0x18
  *
  * Register default value:        0x00000D0D
  * Register full path in IP: hub_rcs_apb/reg/HUB_MAP/gpio_rcs_1_1_0
  * GPIO RCS 1 [1:0] I/O Control Register
  */

typedef union {
  struct {
    uint32_t DR0 : 2;
    ///< Output impedance pin 0.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x1"
    uint32_t POE0 : 1;
    ///< When set to 1, the GPIO RCS 1 pin 0 is an output. When set to 0, the
    ///< GPIO RCS 1 pin 0 is an input.
    ///< AccessType="RW" BitOffset="2" ResetValue="0x1"
    uint32_t LPR0 : 1;
    ///< When set to 1, the receiver of GPIO RCS 1 pin 0 is powered down.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x1"
    uint32_t WKPDE0 : 1;
    ///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 0. This
    ///< should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t WKPUE0 : 1;
    ///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 0. This
    ///< should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t  : 2;
    ///< Reserved
    ///< AccessType="RO" BitOffset="6" ResetValue="None"
    uint32_t DR1 : 2;
    ///< Output impedance pin 1.
    ///< AccessType="RW" BitOffset="8" ResetValue="0x1"
    uint32_t POE1 : 1;
    ///< When set to 1, the GPIO RCS 1 pin 1 is an output. When set to 0, the
    ///< GPIO RCS 1 pin 1 is an input.
    ///< AccessType="RW" BitOffset="10" ResetValue="0x1"
    uint32_t LPR1 : 1;
    ///< When set to 1, the receiver of GPIO RCS 1 pin 1 is powered down.
    ///< AccessType="RW" BitOffset="11" ResetValue="0x1"
    uint32_t WKPDE1 : 1;
    ///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 1. This
    ///< should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="12" ResetValue="0x0"
    uint32_t WKPUE1 : 1;
    ///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 1. This
    ///< should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="13" ResetValue="0x0"
    uint32_t  : 2;
    ///< Reserved
    ///< AccessType="RO" BitOffset="14" ResetValue="None"
    uint32_t MASK : 16;
    ///< Maskable
    ///< AccessType="WO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} hub_rcs_apb_hub_gpio_rcs_1_0_reg_t;

#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DEFAULT (0x00000d0dU)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_RD_MASK (0x00003f3fU)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WR_MASK (0xffff3f3fU)


///< Output impedance pin 0.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR0_BF_OFF ( 0)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR0_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR0_BF_MSK (0x00000003)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR0_BF_DEF (0x00000001)

///< When set to 1, the GPIO RCS 1 pin 0 is an output. When set to 0, the
///< GPIO RCS 1 pin 0 is an input.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE0_BF_OFF ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE0_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE0_BF_MSK (0x00000004)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE0_BF_DEF (0x00000004)

///< When set to 1, the receiver of GPIO RCS 1 pin 0 is powered down.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR0_BF_OFF ( 3)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR0_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR0_BF_MSK (0x00000008)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR0_BF_DEF (0x00000008)

///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 0. This
///< should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE0_BF_OFF ( 4)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE0_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE0_BF_MSK (0x00000010)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE0_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 0. This
///< should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE0_BF_OFF ( 5)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE0_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE0_BF_MSK (0x00000020)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE0_BF_DEF (0x00000000)

///< Output impedance pin 1.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR1_BF_OFF ( 8)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR1_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR1_BF_MSK (0x00000300)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_DR1_BF_DEF (0x00000100)

///< When set to 1, the GPIO RCS 1 pin 1 is an output. When set to 0, the
///< GPIO RCS 1 pin 1 is an input.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE1_BF_OFF (10)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE1_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE1_BF_MSK (0x00000400)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_POE1_BF_DEF (0x00000400)

///< When set to 1, the receiver of GPIO RCS 1 pin 1 is powered down.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR1_BF_OFF (11)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR1_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR1_BF_MSK (0x00000800)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_LPR1_BF_DEF (0x00000800)

///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 1. This
///< should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE1_BF_OFF (12)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE1_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE1_BF_MSK (0x00001000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPDE1_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 1. This
///< should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE1_BF_OFF (13)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE1_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE1_BF_MSK (0x00002000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_WKPUE1_BF_DEF (0x00000000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_MASK_BF_OFF (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_MASK_BF_WID (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_MASK_BF_MSK (0xFFFF0000)


/** @brief HUB_RCS_APB_REG_HUB_MAP_GPIO_RCS_1_3_2 register description at address offset 0x1c
  *
  * Register default value:        0x00000D0D
  * Register full path in IP: hub_rcs_apb/reg/HUB_MAP/gpio_rcs_1_3_2
  * GPIO RCS 1 [3:2] I/O Control Register
  */

typedef union {
  struct {
    uint32_t DR2 : 2;
    ///< Output impedance pin 2.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x1"
    uint32_t POE2 : 1;
    ///< When set to 1, the GPIO RCS 1 pin 2 is an output. When set to 0, the
    ///< GPIO RCS 1 pin 2 is an input.
    ///< AccessType="RW" BitOffset="2" ResetValue="0x1"
    uint32_t LPR2 : 1;
    ///< When set to 1, the receiver of GPIO RCS 1 pin 2 is powered down.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x1"
    uint32_t WKPDE2 : 1;
    ///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 2. This
    ///< should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t WKPUE2 : 1;
    ///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 2. This
    ///< should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t  : 2;
    ///< Reserved
    ///< AccessType="RO" BitOffset="6" ResetValue="None"
    uint32_t DR3 : 2;
    ///< Output impedance pin 3.
    ///< AccessType="RW" BitOffset="8" ResetValue="0x1"
    uint32_t POE3 : 1;
    ///< When set to 1, the GPIO RCS 1 pin 3 is an output. When set to 0, the
    ///< GPIO RCS 1 pin 3 is an input.
    ///< AccessType="RW" BitOffset="10" ResetValue="0x1"
    uint32_t LPR3 : 1;
    ///< When set to 1, the receiver of GPIO RCS 1 pin 3 is powered down.
    ///< AccessType="RW" BitOffset="11" ResetValue="0x1"
    uint32_t WKPDE3 : 1;
    ///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 3. This
    ///< should not be enabled at the same time as wkpue.
    ///< AccessType="RW" BitOffset="12" ResetValue="0x0"
    uint32_t WKPUE3 : 1;
    ///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 3. This
    ///< should not be enabled at the same time as wkdue.
    ///< AccessType="RW" BitOffset="13" ResetValue="0x0"
    uint32_t  : 2;
    ///< Reserved
    ///< AccessType="RO" BitOffset="14" ResetValue="None"
    uint32_t MASK : 16;
    ///< Maskable
    ///< AccessType="WO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} hub_rcs_apb_hub_gpio_rcs_1_3_2_reg_t;

#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DEFAULT (0x00000d0dU)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_RD_MASK (0x00003f3fU)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WR_MASK (0xffff3f3fU)


///< Output impedance pin 2.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR2_BF_OFF ( 0)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR2_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR2_BF_MSK (0x00000003)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR2_BF_DEF (0x00000001)

///< When set to 1, the GPIO RCS 1 pin 2 is an output. When set to 0, the
///< GPIO RCS 1 pin 2 is an input.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE2_BF_OFF ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE2_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE2_BF_MSK (0x00000004)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE2_BF_DEF (0x00000004)

///< When set to 1, the receiver of GPIO RCS 1 pin 2 is powered down.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR2_BF_OFF ( 3)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR2_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR2_BF_MSK (0x00000008)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR2_BF_DEF (0x00000008)

///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 2. This
///< should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE2_BF_OFF ( 4)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE2_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE2_BF_MSK (0x00000010)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE2_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 2. This
///< should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE2_BF_OFF ( 5)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE2_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE2_BF_MSK (0x00000020)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE2_BF_DEF (0x00000000)

///< Output impedance pin 3.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR3_BF_OFF ( 8)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR3_BF_WID ( 2)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR3_BF_MSK (0x00000300)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_DR3_BF_DEF (0x00000100)

///< When set to 1, the GPIO RCS 1 pin 3 is an output. When set to 0, the
///< GPIO RCS 1 pin 3 is an input.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE3_BF_OFF (10)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE3_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE3_BF_MSK (0x00000400)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_POE3_BF_DEF (0x00000400)

///< When set to 1, the receiver of GPIO RCS 1 pin 3 is powered down.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR3_BF_OFF (11)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR3_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR3_BF_MSK (0x00000800)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_LPR3_BF_DEF (0x00000800)

///< When set to 1, enables weak pull-down on the GPIO RCS 1 pin 3. This
///< should not be enabled at the same time as wkpue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE3_BF_OFF (12)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE3_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE3_BF_MSK (0x00001000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPDE3_BF_DEF (0x00000000)

///< When set to 1, enables weak pull-up on the GPIO RCS 1 pin 3. This
///< should not be enabled at the same time as wkdue.
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE3_BF_OFF (13)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE3_BF_WID ( 1)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE3_BF_MSK (0x00002000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_WKPUE3_BF_DEF (0x00000000)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_MASK_BF_OFF (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_MASK_BF_WID (16)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_MASK_BF_MSK (0xFFFF0000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define HUB_RCS_APB_HUB_SCRATCH_REG ((hub_rcs_apb_hub_scratch_reg_t*) HUB_RCS_APB_HUB_SCRATCH_ADR)
#define HUB_RCS_APB_HUB_GPIO_INTR_REG ((hub_rcs_apb_hub_gpio_intr_reg_t*) HUB_RCS_APB_HUB_GPIO_INTR_ADR)
#define HUB_RCS_APB_HUB_GPIO_RCS_0_REG ((hub_rcs_apb_hub_gpio_rcs_0_reg_t*) HUB_RCS_APB_HUB_GPIO_RCS_0_ADR)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_0_REG ((hub_rcs_apb_hub_gpio_rcs_1_0_reg_t*) HUB_RCS_APB_HUB_GPIO_RCS_1_0_ADR)
#define HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_REG ((hub_rcs_apb_hub_gpio_rcs_1_3_2_reg_t*) HUB_RCS_APB_HUB_GPIO_RCS_1_3_2_ADR)

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    hub_rcs_apb_hub_scratch_reg_t HUB_SCRATCH; /*< Address offset = 0x0 */
    const uint8_t        reservedArea0 [12];  /*< Address offset = 0x4 */
    hub_rcs_apb_hub_gpio_intr_reg_t HUB_GPIO_INTR; /*< Address offset = 0x10 */
    hub_rcs_apb_hub_gpio_rcs_0_reg_t HUB_GPIO_RCS_0; /*< Address offset = 0x14 */
    hub_rcs_apb_hub_gpio_rcs_1_0_reg_t HUB_GPIO_RCS_1_0; /*< Address offset = 0x18 */
    hub_rcs_apb_hub_gpio_rcs_1_3_2_reg_t HUB_GPIO_RCS_1_3_2; /*< Address offset = 0x1c */
} hub_rcs_apb_t;     // size: 0x0014

// AddressSpace struct pointer
//
#define HUB_RCS_APB      ((hub_rcs_apb_t*) HUB_RCS_APB_BASE)

// ******************************************* /Address Space

#endif      // _HUB_RCS_APB_H_

