#ifndef _VHA_DUC_H_
#define _VHA_DUC_H_

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

#define VHA0_ANT0_DUC0_BASE   ( 0x03c00000 )
#define VHA0_ANT0_DUC1_BASE   ( 0x03c08000 )
#define VHA0_ANT1_DUC0_BASE   ( 0x03c10000 )
#define VHA0_ANT1_DUC1_BASE   ( 0x03c18000 )
#define VHA1_ANT0_DUC0_BASE   ( 0x03c20000 )
#define VHA1_ANT0_DUC1_BASE   ( 0x03c28000 )
#define VHA1_ANT1_DUC0_BASE   ( 0x03c30000 )
#define VHA1_ANT1_DUC1_BASE   ( 0x03c38000 )
#define VHA2_ANT0_DUC0_BASE   ( 0x03c40000 )
#define VHA2_ANT0_DUC1_BASE   ( 0x03c48000 )
#define VHA2_ANT1_DUC0_BASE   ( 0x03c50000 )
#define VHA2_ANT1_DUC1_BASE   ( 0x03c58000 )
#define VHA3_ANT0_DUC0_BASE   ( 0x03c60000 )
#define VHA3_ANT0_DUC1_BASE   ( 0x03c68000 )
#define VHA3_ANT1_DUC0_BASE   ( 0x03c70000 )
#define VHA3_ANT1_DUC1_BASE   ( 0x03c78000 )
#define VHA4_ANT0_DUC0_BASE   ( 0x03c80000 )
#define VHA4_ANT0_DUC1_BASE   ( 0x03c88000 )
#define VHA4_ANT1_DUC0_BASE   ( 0x03c90000 )
#define VHA4_ANT1_DUC1_BASE   ( 0x03c98000 )
#define VHA5_ANT0_DUC0_BASE   ( 0x03ca0000 )
#define VHA5_ANT0_DUC1_BASE   ( 0x03ca8000 )
#define VHA5_ANT1_DUC0_BASE   ( 0x03cb0000 )
#define VHA5_ANT1_DUC1_BASE   ( 0x03cb8000 )
#define VHA6_ANT0_DUC0_BASE   ( 0x03cc0000 )
#define VHA6_ANT0_DUC1_BASE   ( 0x03cc8000 )
#define VHA6_ANT1_DUC0_BASE   ( 0x03cd0000 )
#define VHA6_ANT1_DUC1_BASE   ( 0x03cd8000 )
#define VHA7_ANT0_DUC0_BASE   ( 0x03ce0000 )
#define VHA7_ANT0_DUC1_BASE   ( 0x03ce8000 )
#define VHA7_ANT1_DUC0_BASE   ( 0x03cf0000 )
#define VHA7_ANT1_DUC1_BASE   ( 0x03cf8000 )

// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define VHA_DUC_SCRATCH_OFFSET   ( 0x00000000U )
#define VHA_DUC_CFG_OFFSET    ( 0x00000004U )
#define VHA_DUC_APB_BRDG_STAT_OFFSET ( 0x00000008U )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define VHA_DUC_SCRATCH_ADR(_BASE)      (( ( _BASE ) + ( VHA_DUC_SCRATCH_OFFSET ) ))
#define VHA_DUC_CFG_ADR(_BASE)       (( ( _BASE ) + ( VHA_DUC_CFG_OFFSET ) ))
#define VHA_DUC_APB_BRDG_STAT_ADR(_BASE) (( ( _BASE ) + ( VHA_DUC_APB_BRDG_STAT_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief VHA_DUC_MAP_REG_SCRATCH register description at address offset 0x0
  *
  * Register default value:        0x00000000
  * Register full path in IP: vha_duc_map/reg/SCRATCH
  * VHA DUC scratchpad register.
  */

typedef union {
  struct {
    uint32_t SCRATCHPAD : 32;
    ///< Do anything with this field.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} vha_duc_scratch_reg_t;

#define VHA_DUC_SCRATCH_DEFAULT (0x00000000U)
#define VHA_DUC_SCRATCH_RD_MASK (0xffffffffU)
#define VHA_DUC_SCRATCH_WR_MASK (0xffffffffU)


///< Do anything with this field.
#define VHA_DUC_SCRATCH_SCRATCHPAD_BF_OFF ( 0)
#define VHA_DUC_SCRATCH_SCRATCHPAD_BF_WID (32)
#define VHA_DUC_SCRATCH_SCRATCHPAD_BF_MSK (0xFFFFFFFF)
#define VHA_DUC_SCRATCH_SCRATCHPAD_BF_DEF (0x00000000)


/** @brief VHA_DUC_MAP_REG_CONFIG register description at address offset 0x4
  *
  * Register default value:        0x00000000
  * Register full path in IP: vha_duc_map/reg/CONFIG
  * VHA DUC configuration register.
  */

typedef union {
  struct {
    uint32_t MODE : 1;
    ///< 0: Automatically select active filter stages based on INPUT_RATE and
    ///< OUTPUT_RATE.                                         1: Manually select
    ///< active filter stages based on STAGE_ACTIVE.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t STAGE_ACTIVE : 4;
    ///< These bits determine which filter stages are active when MODE is 1.
    ///< When a STAGE_ACTIVE bit is 1 the corresponding filter stage is active,
    ///< otherwise it is bypassed:
    ///< 0: 63-tap HBF stage W1                                         1:
    ///< 19-tap HBF stage W2                                         2: 11-tap
    ///< HBF stage W3                                         3: 7-tap HBF
    ///< stage W4
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t  : 27;
    ///< Reserved
    ///< AccessType="RO" BitOffset="5" ResetValue="None"
  } ;
  uint32_t value;
} vha_duc_cfg_reg_t;

#define VHA_DUC_CFG_DEFAULT (0x00000000U)
#define VHA_DUC_CFG_RD_MASK (0x0000001fU)
#define VHA_DUC_CFG_WR_MASK (0x0000001fU)


///< 0: Automatically select active filter stages based on INPUT_RATE and
///< OUTPUT_RATE.                                         1: Manually select
///< active filter stages based on STAGE_ACTIVE.
#define VHA_DUC_CFG_MODE_BF_OFF ( 0)
#define VHA_DUC_CFG_MODE_BF_WID ( 1)
#define VHA_DUC_CFG_MODE_BF_MSK (0x00000001)
#define VHA_DUC_CFG_MODE_BF_DEF (0x00000000)

///< These bits determine which filter stages are active when MODE is 1.
///< When a STAGE_ACTIVE bit is 1 the corresponding filter stage is active,
///< otherwise it is bypassed:
///< 0: 63-tap HBF stage W1                                         1:
///< 19-tap HBF stage W2                                         2: 11-tap
///< HBF stage W3                                         3: 7-tap HBF
///< stage W4
#define VHA_DUC_CFG_STAGE_ACTIVE_BF_OFF ( 1)
#define VHA_DUC_CFG_STAGE_ACTIVE_BF_WID ( 4)
#define VHA_DUC_CFG_STAGE_ACTIVE_BF_MSK (0x0000001E)
#define VHA_DUC_CFG_STAGE_ACTIVE_BF_DEF (0x00000000)


/** @brief VHA_DUC_MAP_REG_APB_BRIDGE_STATUS register description at address offset 0x8
  *
  * Register default value:        0x00010000
  * Register full path in IP: vha_duc_map/reg/APB_BRIDGE_STATUS
  * APB Bridge Status Register
  */

typedef union {
  struct {
    uint32_t TIMEOUT_VALUE : 20;
    ///< Number of core clocks to wait before timing out an APB request
    ///< AccessType="RW/L" BitOffset="0" ResetValue="0x10000"
    uint32_t REVISION : 8;
    ///< Module Revision Number
    ///< AccessType="RO" BitOffset="20" ResetValue="0x0"
    uint32_t SW_LOCK_CTRL : 1;
    ///< Block software writes to timeout_value if set
    ///< AccessType="RW/1S/V/L" BitOffset="28" ResetValue="0x0"
    uint32_t UNSOL_ACK : 1;
    ///< An unsolicited acknowledge was received
    ///< AccessType="RW/1C/V" BitOffset="29" ResetValue="0x0"
    uint32_t ACK_ERROR : 1;
    ///< Acknowledgement had error bit set
    ///< AccessType="RW/1C/V" BitOffset="30" ResetValue="0x0"
    uint32_t TIMEOUT : 1;
    ///< An APB request has timed out
    ///< AccessType="RW/1C/V" BitOffset="31" ResetValue="0x0"
  } ;
  uint32_t value;
} vha_duc_apb_brdg_stat_reg_t;

#define VHA_DUC_APB_BRDG_STAT_DEFAULT (0x00010000U)
#define VHA_DUC_APB_BRDG_STAT_RD_MASK (0xffffffffU)
#define VHA_DUC_APB_BRDG_STAT_WR_MASK (0xf00fffffU)


///< Number of core clocks to wait before timing out an APB request
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_VAL_BF_OFF ( 0)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_VAL_BF_WID (20)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_VAL_BF_MSK (0x000FFFFF)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_VAL_BF_DEF (0x00010000)

///< Module Revision Number
#define VHA_DUC_APB_BRDG_STAT_REVISION_BF_OFF (20)
#define VHA_DUC_APB_BRDG_STAT_REVISION_BF_WID ( 8)
#define VHA_DUC_APB_BRDG_STAT_REVISION_BF_MSK (0x0FF00000)
#define VHA_DUC_APB_BRDG_STAT_REVISION_BF_DEF (0x00000000)

///< Block software writes to timeout_value if set
#define VHA_DUC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_OFF (28)
#define VHA_DUC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_WID ( 1)
#define VHA_DUC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_MSK (0x10000000)
#define VHA_DUC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_DEF (0x00000000)

///< An unsolicited acknowledge was received
#define VHA_DUC_APB_BRDG_STAT_UNSOL_ACK_BF_OFF (29)
#define VHA_DUC_APB_BRDG_STAT_UNSOL_ACK_BF_WID ( 1)
#define VHA_DUC_APB_BRDG_STAT_UNSOL_ACK_BF_MSK (0x20000000)
#define VHA_DUC_APB_BRDG_STAT_UNSOL_ACK_BF_DEF (0x00000000)

///< Acknowledgement had error bit set
#define VHA_DUC_APB_BRDG_STAT_ACK_ERR_BF_OFF (30)
#define VHA_DUC_APB_BRDG_STAT_ACK_ERR_BF_WID ( 1)
#define VHA_DUC_APB_BRDG_STAT_ACK_ERR_BF_MSK (0x40000000)
#define VHA_DUC_APB_BRDG_STAT_ACK_ERR_BF_DEF (0x00000000)

///< An APB request has timed out
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_BF_OFF (31)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_BF_WID ( 1)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_BF_MSK (0x80000000)
#define VHA_DUC_APB_BRDG_STAT_TIMEOUT_BF_DEF (0x00000000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define VHA_DUC_SCRATCH_REG(_BASE) ((vha_duc_scratch_reg_t*) VHA_DUC_SCRATCH_ADR(_BASE))
#define VHA_DUC_CFG_REG(_BASE) ((vha_duc_cfg_reg_t*) VHA_DUC_CFG_ADR(_BASE))
#define VHA_DUC_APB_BRDG_STAT_REG(_BASE) ((vha_duc_apb_brdg_stat_reg_t*) VHA_DUC_APB_BRDG_STAT_ADR(_BASE))

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    vha_duc_scratch_reg_t SCRATCH;         /*< Address offset = 0x0 */
    vha_duc_cfg_reg_t CFG;          /*< Address offset = 0x4 */
    vha_duc_apb_brdg_stat_reg_t APB_BRDG_STAT; /*< Address offset = 0x8 */
} vha_duc_t;     // size: 0x000c

// AddressSpace struct pointer
//
#define VHA0_ANT0_DUC0   ((vha_duc_t*) VHA0_ANT0_DUC0_BASE)
#define VHA0_ANT0_DUC1   ((vha_duc_t*) VHA0_ANT0_DUC1_BASE)
#define VHA0_ANT1_DUC0   ((vha_duc_t*) VHA0_ANT1_DUC0_BASE)
#define VHA0_ANT1_DUC1   ((vha_duc_t*) VHA0_ANT1_DUC1_BASE)
#define VHA1_ANT0_DUC0   ((vha_duc_t*) VHA1_ANT0_DUC0_BASE)
#define VHA1_ANT0_DUC1   ((vha_duc_t*) VHA1_ANT0_DUC1_BASE)
#define VHA1_ANT1_DUC0   ((vha_duc_t*) VHA1_ANT1_DUC0_BASE)
#define VHA1_ANT1_DUC1   ((vha_duc_t*) VHA1_ANT1_DUC1_BASE)
#define VHA2_ANT0_DUC0   ((vha_duc_t*) VHA2_ANT0_DUC0_BASE)
#define VHA2_ANT0_DUC1   ((vha_duc_t*) VHA2_ANT0_DUC1_BASE)
#define VHA2_ANT1_DUC0   ((vha_duc_t*) VHA2_ANT1_DUC0_BASE)
#define VHA2_ANT1_DUC1   ((vha_duc_t*) VHA2_ANT1_DUC1_BASE)
#define VHA3_ANT0_DUC0   ((vha_duc_t*) VHA3_ANT0_DUC0_BASE)
#define VHA3_ANT0_DUC1   ((vha_duc_t*) VHA3_ANT0_DUC1_BASE)
#define VHA3_ANT1_DUC0   ((vha_duc_t*) VHA3_ANT1_DUC0_BASE)
#define VHA3_ANT1_DUC1   ((vha_duc_t*) VHA3_ANT1_DUC1_BASE)
#define VHA4_ANT0_DUC0   ((vha_duc_t*) VHA4_ANT0_DUC0_BASE)
#define VHA4_ANT0_DUC1   ((vha_duc_t*) VHA4_ANT0_DUC1_BASE)
#define VHA4_ANT1_DUC0   ((vha_duc_t*) VHA4_ANT1_DUC0_BASE)
#define VHA4_ANT1_DUC1   ((vha_duc_t*) VHA4_ANT1_DUC1_BASE)
#define VHA5_ANT0_DUC0   ((vha_duc_t*) VHA5_ANT0_DUC0_BASE)
#define VHA5_ANT0_DUC1   ((vha_duc_t*) VHA5_ANT0_DUC1_BASE)
#define VHA5_ANT1_DUC0   ((vha_duc_t*) VHA5_ANT1_DUC0_BASE)
#define VHA5_ANT1_DUC1   ((vha_duc_t*) VHA5_ANT1_DUC1_BASE)
#define VHA6_ANT0_DUC0   ((vha_duc_t*) VHA6_ANT0_DUC0_BASE)
#define VHA6_ANT0_DUC1   ((vha_duc_t*) VHA6_ANT0_DUC1_BASE)
#define VHA6_ANT1_DUC0   ((vha_duc_t*) VHA6_ANT1_DUC0_BASE)
#define VHA6_ANT1_DUC1   ((vha_duc_t*) VHA6_ANT1_DUC1_BASE)
#define VHA7_ANT0_DUC0   ((vha_duc_t*) VHA7_ANT0_DUC0_BASE)
#define VHA7_ANT0_DUC1   ((vha_duc_t*) VHA7_ANT0_DUC1_BASE)
#define VHA7_ANT1_DUC0   ((vha_duc_t*) VHA7_ANT1_DUC0_BASE)
#define VHA7_ANT1_DUC1   ((vha_duc_t*) VHA7_ANT1_DUC1_BASE)

// ******************************************* /Address Space

#endif      // _VHA_DUC_H_

