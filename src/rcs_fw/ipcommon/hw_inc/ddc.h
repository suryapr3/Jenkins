#ifndef _DDC_H_
#define _DDC_H_

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

#define FB_SYS0_DDC0_BASE     ( 0x05101000 )
#define FB_SYS0_DDC1_BASE     ( 0x05109000 )
#define FB_SYS1_DDC0_BASE     ( 0x05111000 )
#define FB_SYS1_DDC1_BASE     ( 0x05119000 )
#define TRX_SYS0_DDC0_BASE    ( 0x05261000 )
#define TRX_SYS0_DDC1_BASE    ( 0x05271000 )
#define TRX_SYS1_DDC0_BASE    ( 0x05281000 )
#define TRX_SYS1_DDC1_BASE    ( 0x05291000 )
#define TRX_SYS2_DDC0_BASE    ( 0x052a1000 )
#define TRX_SYS2_DDC1_BASE    ( 0x052b1000 )
#define TRX_SYS3_DDC0_BASE    ( 0x052c1000 )
#define TRX_SYS3_DDC1_BASE    ( 0x052d1000 )
#define TRX_SYS4_DDC0_BASE    ( 0x052e1000 )
#define TRX_SYS4_DDC1_BASE    ( 0x052f1000 )
#define TRX_SYS5_DDC0_BASE    ( 0x05301000 )
#define TRX_SYS5_DDC1_BASE    ( 0x05311000 )
#define TRX_SYS6_DDC0_BASE    ( 0x05321000 )
#define TRX_SYS6_DDC1_BASE    ( 0x05331000 )
#define TRX_SYS7_DDC0_BASE    ( 0x05341000 )
#define TRX_SYS7_DDC1_BASE    ( 0x05351000 )

// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define DDC_SCRATCH_OFFSET       ( 0x00000000U )
#define DDC_CFG_OFFSET        ( 0x00000004U )
#define DDC_STAT_OFFSET        ( 0x00000008U )
#define DDC_APB_BRDG_STAT_OFFSET ( 0x0000000cU )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define DDC_SCRATCH_ADR(_BASE)          (( ( _BASE ) + ( DDC_SCRATCH_OFFSET ) ))
#define DDC_CFG_ADR(_BASE)           (( ( _BASE ) + ( DDC_CFG_OFFSET ) ))
#define DDC_STAT_ADR(_BASE)           (( ( _BASE ) + ( DDC_STAT_OFFSET ) ))
#define DDC_APB_BRDG_STAT_ADR(_BASE) (( ( _BASE ) + ( DDC_APB_BRDG_STAT_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief DDC_MAP_REG_SCRATCH register description at address offset 0x0
  *
  * Register default value:        0x00000000
  * Register full path in IP: ddc_map/reg/SCRATCH
  * DDC scratchpad register.
  */

typedef union {
  struct {
    uint32_t SCRATCHPAD : 32;
    ///< Do anything with this field.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} ddc_scratch_reg_t;

#define DDC_SCRATCH_DEFAULT (0x00000000U)
#define DDC_SCRATCH_RD_MASK (0xffffffffU)
#define DDC_SCRATCH_WR_MASK (0xffffffffU)


///< Do anything with this field.
#define DDC_SCRATCH_SCRATCHPAD_BF_OFF ( 0)
#define DDC_SCRATCH_SCRATCHPAD_BF_WID (32)
#define DDC_SCRATCH_SCRATCHPAD_BF_MSK (0xFFFFFFFF)
#define DDC_SCRATCH_SCRATCHPAD_BF_DEF (0x00000000)


/** @brief DDC_MAP_REG_CONFIG register description at address offset 0x4
  *
  * Register default value:        0x00000000
  * Register full path in IP: ddc_map/reg/CONFIG
  * DDC configuration register.
  */

typedef union {
  struct {
    uint32_t MODE : 1;
    ///< 0: Automatically select active filter stages based on SYS_RATE and
    ///< ANT_RATE.                                         1: Manually select
    ///< active filter stages based on STAGE_ACTIVE.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t TBF1 : 1;
    ///< 0: TBF1 is bypassed in manual mode.
    ///< 1: TBF1 is active in manual mode.
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t TBF1I : 1;
    ///< 0: TBF1 interpolation is disabled in manual mode.
    ///< 1: TBF1 interpolation is enabled in manual mode (ignored if TBF1 is
    ///< not active).
    ///< AccessType="RW" BitOffset="2" ResetValue="0x0"
    uint32_t TBF2 : 1;
    ///< 0: TBF2 is bypassed in manual mode.
    ///< 1: TBF2 is active in manual mode.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"
    uint32_t TBF2I : 1;
    ///< 0: TBF2 interpolation is disabled in manual mode.
    ///< 1: TBF2 interpolation is enabled in manual mode (ignored if TBF1 is
    ///< not active).
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t HBF1 : 1;
    ///< 0: HBF1 is bypassed in manual mode.
    ///< 1: HBF1 is active in manual mode.
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t FBF1 : 1;
    ///< 0: FBF1 is bypassed in manual mode.
    ///< 1: FBF1 is active in manual mode.
    ///< AccessType="RW" BitOffset="6" ResetValue="0x0"
    uint32_t HBF2 : 1;
    ///< 0: HBF2 is bypassed in manual mode.
    ///< 1: HBF2 is active in manual mode.
    ///< AccessType="RW" BitOffset="7" ResetValue="0x0"
    uint32_t HBF3 : 1;
    ///< 0: HBF3 is bypassed in manual mode.
    ///< 1: HBF3 is active in manual mode.
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t HBF4 : 1;
    ///< 0: HBF4 is bypassed in manual mode.
    ///< 1: HBF4 is active in manual mode.
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t HBF5 : 1;
    ///< 0: HBF5 is bypassed in manual mode.
    ///< 1: HBF5 is active in manual mode.
    ///< AccessType="RW" BitOffset="10" ResetValue="0x0"
    uint32_t HBF6 : 1;
    ///< 0: HBF6 is bypassed in manual mode.
    ///< 1: HBF6 is active in manual mode.
    ///< AccessType="RW" BitOffset="11" ResetValue="0x0"
    uint32_t  : 20;
    ///< Reserved
    ///< AccessType="RO" BitOffset="12" ResetValue="None"
  } ;
  uint32_t value;
} ddc_cfg_reg_t;

#define DDC_CFG_DEFAULT (0x00000000U)
#define DDC_CFG_RD_MASK (0x00000fffU)
#define DDC_CFG_WR_MASK (0x00000fffU)


///< 0: Automatically select active filter stages based on SYS_RATE and
///< ANT_RATE.                                         1: Manually select
///< active filter stages based on STAGE_ACTIVE.
#define DDC_CFG_MODE_BF_OFF ( 0)
#define DDC_CFG_MODE_BF_WID ( 1)
#define DDC_CFG_MODE_BF_MSK (0x00000001)
#define DDC_CFG_MODE_BF_DEF (0x00000000)

///< 0: TBF1 is bypassed in manual mode.
///< 1: TBF1 is active in manual mode.
#define DDC_CFG_TBF1_BF_OFF ( 1)
#define DDC_CFG_TBF1_BF_WID ( 1)
#define DDC_CFG_TBF1_BF_MSK (0x00000002)
#define DDC_CFG_TBF1_BF_DEF (0x00000000)

///< 0: TBF1 interpolation is disabled in manual mode.
///< 1: TBF1 interpolation is enabled in manual mode (ignored if TBF1 is
///< not active).
#define DDC_CFG_TBF1I_BF_OFF ( 2)
#define DDC_CFG_TBF1I_BF_WID ( 1)
#define DDC_CFG_TBF1I_BF_MSK (0x00000004)
#define DDC_CFG_TBF1I_BF_DEF (0x00000000)

///< 0: TBF2 is bypassed in manual mode.
///< 1: TBF2 is active in manual mode.
#define DDC_CFG_TBF2_BF_OFF ( 3)
#define DDC_CFG_TBF2_BF_WID ( 1)
#define DDC_CFG_TBF2_BF_MSK (0x00000008)
#define DDC_CFG_TBF2_BF_DEF (0x00000000)

///< 0: TBF2 interpolation is disabled in manual mode.
///< 1: TBF2 interpolation is enabled in manual mode (ignored if TBF1 is
///< not active).
#define DDC_CFG_TBF2I_BF_OFF ( 4)
#define DDC_CFG_TBF2I_BF_WID ( 1)
#define DDC_CFG_TBF2I_BF_MSK (0x00000010)
#define DDC_CFG_TBF2I_BF_DEF (0x00000000)

///< 0: HBF1 is bypassed in manual mode.
///< 1: HBF1 is active in manual mode.
#define DDC_CFG_HBF1_BF_OFF ( 5)
#define DDC_CFG_HBF1_BF_WID ( 1)
#define DDC_CFG_HBF1_BF_MSK (0x00000020)
#define DDC_CFG_HBF1_BF_DEF (0x00000000)

///< 0: FBF1 is bypassed in manual mode.
///< 1: FBF1 is active in manual mode.
#define DDC_CFG_FBF1_BF_OFF ( 6)
#define DDC_CFG_FBF1_BF_WID ( 1)
#define DDC_CFG_FBF1_BF_MSK (0x00000040)
#define DDC_CFG_FBF1_BF_DEF (0x00000000)

///< 0: HBF2 is bypassed in manual mode.
///< 1: HBF2 is active in manual mode.
#define DDC_CFG_HBF2_BF_OFF ( 7)
#define DDC_CFG_HBF2_BF_WID ( 1)
#define DDC_CFG_HBF2_BF_MSK (0x00000080)
#define DDC_CFG_HBF2_BF_DEF (0x00000000)

///< 0: HBF3 is bypassed in manual mode.
///< 1: HBF3 is active in manual mode.
#define DDC_CFG_HBF3_BF_OFF ( 8)
#define DDC_CFG_HBF3_BF_WID ( 1)
#define DDC_CFG_HBF3_BF_MSK (0x00000100)
#define DDC_CFG_HBF3_BF_DEF (0x00000000)

///< 0: HBF4 is bypassed in manual mode.
///< 1: HBF4 is active in manual mode.
#define DDC_CFG_HBF4_BF_OFF ( 9)
#define DDC_CFG_HBF4_BF_WID ( 1)
#define DDC_CFG_HBF4_BF_MSK (0x00000200)
#define DDC_CFG_HBF4_BF_DEF (0x00000000)

///< 0: HBF5 is bypassed in manual mode.
///< 1: HBF5 is active in manual mode.
#define DDC_CFG_HBF5_BF_OFF (10)
#define DDC_CFG_HBF5_BF_WID ( 1)
#define DDC_CFG_HBF5_BF_MSK (0x00000400)
#define DDC_CFG_HBF5_BF_DEF (0x00000000)

///< 0: HBF6 is bypassed in manual mode.
///< 1: HBF6 is active in manual mode.
#define DDC_CFG_HBF6_BF_OFF (11)
#define DDC_CFG_HBF6_BF_WID ( 1)
#define DDC_CFG_HBF6_BF_MSK (0x00000800)
#define DDC_CFG_HBF6_BF_DEF (0x00000000)


/** @brief DDC_MAP_REG_STATUS register description at address offset 0x8
  *
  * Register default value:        0x00000000
  * Register full path in IP: ddc_map/reg/STATUS
  * DDC status register.
  */

typedef union {
  struct {
    uint32_t MODE : 1;
    ///< 0: Filter stage selection is being done automatically.
    ///< 1: Filter stage selection is being done manually.
    ///< AccessType="RO/V" BitOffset="0" ResetValue="0x0"
    uint32_t TBF1 : 1;
    ///< 0: TBF1 is bypassed.                                         1: TBF1
    ///< is active.
    ///< AccessType="RO/V" BitOffset="1" ResetValue="0x0"
    uint32_t TBF1I : 1;
    ///< 0: TBF1 interpolation is disabled.
    ///< 1: TBF1 interpolation is enabled.
    ///< AccessType="RO/V" BitOffset="2" ResetValue="0x0"
    uint32_t TBF2 : 1;
    ///< 0: TBF2 is bypassed.                                         1: TBF2
    ///< is active.
    ///< AccessType="RO/V" BitOffset="3" ResetValue="0x0"
    uint32_t TBF2I : 1;
    ///< 0: TBF2 interpolation is disabled.
    ///< 1: TBF2 interpolation is enabled.
    ///< AccessType="RO/V" BitOffset="4" ResetValue="0x0"
    uint32_t HBF1 : 1;
    ///< 0: HBF1 is bypassed.                                         1: HBF1
    ///< is active.
    ///< AccessType="RO/V" BitOffset="5" ResetValue="0x0"
    uint32_t FBF1 : 1;
    ///< 0: FBF1 is bypassed.                                         1: FBF1
    ///< is active.
    ///< AccessType="RO/V" BitOffset="6" ResetValue="0x0"
    uint32_t HBF2 : 1;
    ///< 0: HBF2 is bypassed.                                         1: HBF2
    ///< is active.
    ///< AccessType="RO/V" BitOffset="7" ResetValue="0x0"
    uint32_t HBF3 : 1;
    ///< 0: HBF3 is bypassed.                                         1: HBF3
    ///< is active.
    ///< AccessType="RO/V" BitOffset="8" ResetValue="0x0"
    uint32_t HBF4 : 1;
    ///< 0: HBF4 is bypassed.                                         1: HBF4
    ///< is active.
    ///< AccessType="RO/V" BitOffset="9" ResetValue="0x0"
    uint32_t HBF5 : 1;
    ///< 0: HBF5 is bypassed.                                         1: HBF5
    ///< is active.
    ///< AccessType="RO/V" BitOffset="10" ResetValue="0x0"
    uint32_t HBF6 : 1;
    ///< 0: HBF6 is bypassed.                                         1: HBF6
    ///< is active.
    ///< AccessType="RO/V" BitOffset="11" ResetValue="0x0"
    uint32_t  : 20;
    ///< Reserved
    ///< AccessType="RO" BitOffset="12" ResetValue="None"
  } ;
  uint32_t value;
} ddc_stat_reg_t;

#define DDC_STAT_DEFAULT (0x00000000U)
#define DDC_STAT_RD_MASK (0x00000fffU)
#define DDC_STAT_WR_MASK (0x00000000U)


///< 0: Filter stage selection is being done automatically.
///< 1: Filter stage selection is being done manually.
#define DDC_STAT_MODE_BF_OFF ( 0)
#define DDC_STAT_MODE_BF_WID ( 1)
#define DDC_STAT_MODE_BF_MSK (0x00000001)
#define DDC_STAT_MODE_BF_DEF (0x00000000)

///< 0: TBF1 is bypassed.                                         1: TBF1
///< is active.
#define DDC_STAT_TBF1_BF_OFF ( 1)
#define DDC_STAT_TBF1_BF_WID ( 1)
#define DDC_STAT_TBF1_BF_MSK (0x00000002)
#define DDC_STAT_TBF1_BF_DEF (0x00000000)

///< 0: TBF1 interpolation is disabled.
///< 1: TBF1 interpolation is enabled.
#define DDC_STAT_TBF1I_BF_OFF ( 2)
#define DDC_STAT_TBF1I_BF_WID ( 1)
#define DDC_STAT_TBF1I_BF_MSK (0x00000004)
#define DDC_STAT_TBF1I_BF_DEF (0x00000000)

///< 0: TBF2 is bypassed.                                         1: TBF2
///< is active.
#define DDC_STAT_TBF2_BF_OFF ( 3)
#define DDC_STAT_TBF2_BF_WID ( 1)
#define DDC_STAT_TBF2_BF_MSK (0x00000008)
#define DDC_STAT_TBF2_BF_DEF (0x00000000)

///< 0: TBF2 interpolation is disabled.
///< 1: TBF2 interpolation is enabled.
#define DDC_STAT_TBF2I_BF_OFF ( 4)
#define DDC_STAT_TBF2I_BF_WID ( 1)
#define DDC_STAT_TBF2I_BF_MSK (0x00000010)
#define DDC_STAT_TBF2I_BF_DEF (0x00000000)

///< 0: HBF1 is bypassed.                                         1: HBF1
///< is active.
#define DDC_STAT_HBF1_BF_OFF ( 5)
#define DDC_STAT_HBF1_BF_WID ( 1)
#define DDC_STAT_HBF1_BF_MSK (0x00000020)
#define DDC_STAT_HBF1_BF_DEF (0x00000000)

///< 0: FBF1 is bypassed.                                         1: FBF1
///< is active.
#define DDC_STAT_FBF1_BF_OFF ( 6)
#define DDC_STAT_FBF1_BF_WID ( 1)
#define DDC_STAT_FBF1_BF_MSK (0x00000040)
#define DDC_STAT_FBF1_BF_DEF (0x00000000)

///< 0: HBF2 is bypassed.                                         1: HBF2
///< is active.
#define DDC_STAT_HBF2_BF_OFF ( 7)
#define DDC_STAT_HBF2_BF_WID ( 1)
#define DDC_STAT_HBF2_BF_MSK (0x00000080)
#define DDC_STAT_HBF2_BF_DEF (0x00000000)

///< 0: HBF3 is bypassed.                                         1: HBF3
///< is active.
#define DDC_STAT_HBF3_BF_OFF ( 8)
#define DDC_STAT_HBF3_BF_WID ( 1)
#define DDC_STAT_HBF3_BF_MSK (0x00000100)
#define DDC_STAT_HBF3_BF_DEF (0x00000000)

///< 0: HBF4 is bypassed.                                         1: HBF4
///< is active.
#define DDC_STAT_HBF4_BF_OFF ( 9)
#define DDC_STAT_HBF4_BF_WID ( 1)
#define DDC_STAT_HBF4_BF_MSK (0x00000200)
#define DDC_STAT_HBF4_BF_DEF (0x00000000)

///< 0: HBF5 is bypassed.                                         1: HBF5
///< is active.
#define DDC_STAT_HBF5_BF_OFF (10)
#define DDC_STAT_HBF5_BF_WID ( 1)
#define DDC_STAT_HBF5_BF_MSK (0x00000400)
#define DDC_STAT_HBF5_BF_DEF (0x00000000)

///< 0: HBF6 is bypassed.                                         1: HBF6
///< is active.
#define DDC_STAT_HBF6_BF_OFF (11)
#define DDC_STAT_HBF6_BF_WID ( 1)
#define DDC_STAT_HBF6_BF_MSK (0x00000800)
#define DDC_STAT_HBF6_BF_DEF (0x00000000)


/** @brief DDC_MAP_REG_APB_BRIDGE_STATUS register description at address offset 0xc
  *
  * Register default value:        0x00010000
  * Register full path in IP: ddc_map/reg/APB_BRIDGE_STATUS
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
} ddc_apb_brdg_stat_reg_t;

#define DDC_APB_BRDG_STAT_DEFAULT (0x00010000U)
#define DDC_APB_BRDG_STAT_RD_MASK (0xffffffffU)
#define DDC_APB_BRDG_STAT_WR_MASK (0xf00fffffU)


///< Number of core clocks to wait before timing out an APB request
#define DDC_APB_BRDG_STAT_TIMEOUT_VAL_BF_OFF ( 0)
#define DDC_APB_BRDG_STAT_TIMEOUT_VAL_BF_WID (20)
#define DDC_APB_BRDG_STAT_TIMEOUT_VAL_BF_MSK (0x000FFFFF)
#define DDC_APB_BRDG_STAT_TIMEOUT_VAL_BF_DEF (0x00010000)

///< Module Revision Number
#define DDC_APB_BRDG_STAT_REVISION_BF_OFF (20)
#define DDC_APB_BRDG_STAT_REVISION_BF_WID ( 8)
#define DDC_APB_BRDG_STAT_REVISION_BF_MSK (0x0FF00000)
#define DDC_APB_BRDG_STAT_REVISION_BF_DEF (0x00000000)

///< Block software writes to timeout_value if set
#define DDC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_OFF (28)
#define DDC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_WID ( 1)
#define DDC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_MSK (0x10000000)
#define DDC_APB_BRDG_STAT_SW_LOCK_CTRL_BF_DEF (0x00000000)

///< An unsolicited acknowledge was received
#define DDC_APB_BRDG_STAT_UNSOL_ACK_BF_OFF (29)
#define DDC_APB_BRDG_STAT_UNSOL_ACK_BF_WID ( 1)
#define DDC_APB_BRDG_STAT_UNSOL_ACK_BF_MSK (0x20000000)
#define DDC_APB_BRDG_STAT_UNSOL_ACK_BF_DEF (0x00000000)

///< Acknowledgement had error bit set
#define DDC_APB_BRDG_STAT_ACK_ERR_BF_OFF (30)
#define DDC_APB_BRDG_STAT_ACK_ERR_BF_WID ( 1)
#define DDC_APB_BRDG_STAT_ACK_ERR_BF_MSK (0x40000000)
#define DDC_APB_BRDG_STAT_ACK_ERR_BF_DEF (0x00000000)

///< An APB request has timed out
#define DDC_APB_BRDG_STAT_TIMEOUT_BF_OFF (31)
#define DDC_APB_BRDG_STAT_TIMEOUT_BF_WID ( 1)
#define DDC_APB_BRDG_STAT_TIMEOUT_BF_MSK (0x80000000)
#define DDC_APB_BRDG_STAT_TIMEOUT_BF_DEF (0x00000000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define DDC_SCRATCH_REG(_BASE) ((ddc_scratch_reg_t*) DDC_SCRATCH_ADR(_BASE))
#define DDC_CFG_REG(_BASE) ((ddc_cfg_reg_t*) DDC_CFG_ADR(_BASE))
#define DDC_STAT_REG(_BASE) ((ddc_stat_reg_t*) DDC_STAT_ADR(_BASE))
#define DDC_APB_BRDG_STAT_REG(_BASE) ((ddc_apb_brdg_stat_reg_t*) DDC_APB_BRDG_STAT_ADR(_BASE))

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    ddc_scratch_reg_t SCRATCH;         /*< Address offset = 0x0 */
    ddc_cfg_reg_t CFG;          /*< Address offset = 0x4 */
    ddc_stat_reg_t STAT;          /*< Address offset = 0x8 */
    ddc_apb_brdg_stat_reg_t APB_BRDG_STAT; /*< Address offset = 0xc */
} ddc_t;     // size: 0x0010

// AddressSpace struct pointer
//
#define FB_SYS0_DDC0     ((ddc_t*) FB_SYS0_DDC0_BASE)
#define FB_SYS0_DDC1     ((ddc_t*) FB_SYS0_DDC1_BASE)
#define FB_SYS1_DDC0     ((ddc_t*) FB_SYS1_DDC0_BASE)
#define FB_SYS1_DDC1     ((ddc_t*) FB_SYS1_DDC1_BASE)
#define TRX_SYS0_DDC0    ((ddc_t*) TRX_SYS0_DDC0_BASE)
#define TRX_SYS0_DDC1    ((ddc_t*) TRX_SYS0_DDC1_BASE)
#define TRX_SYS1_DDC0    ((ddc_t*) TRX_SYS1_DDC0_BASE)
#define TRX_SYS1_DDC1    ((ddc_t*) TRX_SYS1_DDC1_BASE)
#define TRX_SYS2_DDC0    ((ddc_t*) TRX_SYS2_DDC0_BASE)
#define TRX_SYS2_DDC1    ((ddc_t*) TRX_SYS2_DDC1_BASE)
#define TRX_SYS3_DDC0    ((ddc_t*) TRX_SYS3_DDC0_BASE)
#define TRX_SYS3_DDC1    ((ddc_t*) TRX_SYS3_DDC1_BASE)
#define TRX_SYS4_DDC0    ((ddc_t*) TRX_SYS4_DDC0_BASE)
#define TRX_SYS4_DDC1    ((ddc_t*) TRX_SYS4_DDC1_BASE)
#define TRX_SYS5_DDC0    ((ddc_t*) TRX_SYS5_DDC0_BASE)
#define TRX_SYS5_DDC1    ((ddc_t*) TRX_SYS5_DDC1_BASE)
#define TRX_SYS6_DDC0    ((ddc_t*) TRX_SYS6_DDC0_BASE)
#define TRX_SYS6_DDC1    ((ddc_t*) TRX_SYS6_DDC1_BASE)
#define TRX_SYS7_DDC0    ((ddc_t*) TRX_SYS7_DDC0_BASE)
#define TRX_SYS7_DDC1    ((ddc_t*) TRX_SYS7_DDC1_BASE)

// ******************************************* /Address Space

#endif      // _DDC_H_

