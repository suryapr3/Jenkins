#ifndef _RXANA_RXREGULATOR_MSG_H_
#define _RXANA_RXREGULATOR_MSG_H_

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

#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE  ( 0x06027c00 )
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE      ( 0x0602bc00 )
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE      ( 0x0602fc00 )
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE      ( 0x06033c00 )
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE      ( 0x06037c00 )
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE  ( 0x06827c00 )
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE      ( 0x0682bc00 )
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE      ( 0x0682fc00 )
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE      ( 0x06833c00 )
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE      ( 0x06837c00 )
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE  ( 0x07027c00 )
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE      ( 0x0702bc00 )
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE      ( 0x0702fc00 )
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE      ( 0x07033c00 )
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE      ( 0x07037c00 )
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE  ( 0x07827c00 )
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE      ( 0x0782bc00 )
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE      ( 0x0782fc00 )
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE      ( 0x07833c00 )
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE      ( 0x07837c00 )

// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_OFFSET ( 0x00000000U )
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_OFFSET ( 0x00000004U )
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_OFFSET ( 0x00000008U )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_ADR(_BASE) (( ( _BASE ) + ( RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_OFFSET ) ))
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_ADR(_BASE) (( ( _BASE ) + ( RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_OFFSET ) ))
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_ADR(_BASE) (( ( _BASE ) + ( RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief RXANA_RXREGULATOR_REGS_MSG_RXANA_RXREGULATOR_REGS_RXREGULATOR_CTRL0 register description at address offset 0x0
  *
  * Register default value:        0x00012400
  * Register full path in IP: RXANA_RXREGULATOR_regs_MSG/RXANA_RXREGULATOR_regs/rxregulator_ctrl0
  * rxregulator_ctrl0
  */

typedef union {
  struct {
    uint32_t REGSAR_DAC_PD_B : 1;
    ///< enable dacdrv amp
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t REGSAR_TH2_PD_B : 1;
    ///< enable th2 boost amp
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t REGSAR_OFC_HIGH_PD_B : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="2" ResetValue="0x0"
    uint32_t REGSAR_OFC_LOW_PD_B : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"
    uint32_t REGSAR_DAC_BYP_EN : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
    uint32_t REGSAR_TH2_BYP_EN : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="5" ResetValue="0x0"
    uint32_t REGSAR_OFC_HIGH_STG1_BYP_EN : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="6" ResetValue="0x0"
    uint32_t REGSAR_OFC_HIGH_STG2_BYP_EN : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="7" ResetValue="0x0"
    uint32_t REGSAR_OFC_LOW_BYP_EN : 1;
    ///< ---
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t REGSAR_OFC_HIGH_BLEED_TUNE : 3;
    ///< ---
    ///< AccessType="RW" BitOffset="9" ResetValue="0x2"
    uint32_t REGSAR_OFC_LOW_BLEED_TUNE : 3;
    ///< ---
    ///< AccessType="RW" BitOffset="12" ResetValue="0x2"
    uint32_t REGSAR_TH2_BLEED_TUNE : 3;
    ///< ---
    ///< AccessType="RW" BitOffset="15" ResetValue="0x2"
    uint32_t  : 14;
    ///< Reserved
    ///< AccessType="RO" BitOffset="18" ResetValue="None"
  } ;
  uint32_t value;
} rxana_rxregulator_msg_rxregulator_ctrl0_reg_t;

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_DEFAULT (0x00012400U)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_RD_MASK (0x0003ffffU)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_WR_MASK (0x0003ffffU)


///< enable dacdrv amp
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_PD_B_BF_OFF ( 0)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_PD_B_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_PD_B_BF_MSK (0x00000001)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_PD_B_BF_DEF (0x00000000)

///< enable th2 boost amp
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_PD_B_BF_OFF ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_PD_B_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_PD_B_BF_MSK (0x00000002)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_PD_B_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_PD_B_BF_OFF ( 2)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_PD_B_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_PD_B_BF_MSK (0x00000004)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_PD_B_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_PD_B_BF_OFF ( 3)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_PD_B_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_PD_B_BF_MSK (0x00000008)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_PD_B_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_BYP_EN_BF_OFF ( 4)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_BYP_EN_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_BYP_EN_BF_MSK (0x00000010)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_DAC_BYP_EN_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BYP_EN_BF_OFF ( 5)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BYP_EN_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BYP_EN_BF_MSK (0x00000020)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BYP_EN_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG1_BYP_EN_BF_OFF ( 6)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG1_BYP_EN_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG1_BYP_EN_BF_MSK (0x00000040)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG1_BYP_EN_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG2_BYP_EN_BF_OFF ( 7)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG2_BYP_EN_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG2_BYP_EN_BF_MSK (0x00000080)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_STG2_BYP_EN_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BYP_EN_BF_OFF ( 8)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BYP_EN_BF_WID ( 1)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BYP_EN_BF_MSK (0x00000100)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BYP_EN_BF_DEF (0x00000000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_BLEED_TUNE_BF_OFF ( 9)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_BLEED_TUNE_BF_WID ( 3)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_BLEED_TUNE_BF_MSK (0x00000E00)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_HIGH_BLEED_TUNE_BF_DEF (0x00000400)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BLEED_TUNE_BF_OFF (12)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BLEED_TUNE_BF_WID ( 3)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BLEED_TUNE_BF_MSK (0x00007000)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_OFC_LOW_BLEED_TUNE_BF_DEF (0x00002000)

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BLEED_TUNE_BF_OFF (15)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BLEED_TUNE_BF_WID ( 3)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BLEED_TUNE_BF_MSK (0x00038000)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REGSAR_TH2_BLEED_TUNE_BF_DEF (0x00010000)


/** @brief RXANA_RXREGULATOR_REGS_MSG_RXANA_RXREGULATOR_REGS_RXREGULATOR_CTRL1 register description at address offset 0x4
  *
  * Register default value:        0x00000000
  * Register full path in IP: RXANA_RXREGULATOR_regs_MSG/RXANA_RXREGULATOR_regs/rxregulator_ctrl1
  * rxregulator_ctrl1
  */

typedef union {
  struct {
    uint32_t REGSAR_DCMON_SEL : 6;
    ///< ---
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t  : 26;
    ///< Reserved
    ///< AccessType="RO" BitOffset="6" ResetValue="None"
  } ;
  uint32_t value;
} rxana_rxregulator_msg_rxregulator_ctrl1_reg_t;

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_DEFAULT (0x00000000U)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_RD_MASK (0x0000003fU)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_WR_MASK (0x0000003fU)


#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_REGSAR_DCMON_SEL_BF_OFF ( 0)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_REGSAR_DCMON_SEL_BF_WID ( 6)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_REGSAR_DCMON_SEL_BF_MSK (0x0000003F)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_REGSAR_DCMON_SEL_BF_DEF (0x00000000)


/** @brief RXANA_RXREGULATOR_REGS_MSG_RXANA_RXREGULATOR_REGS_RXREGULATOR_SPARE0 register description at address offset 0x8
  *
  * Register default value:        0x00000000
  * Register full path in IP: RXANA_RXREGULATOR_regs_MSG/RXANA_RXREGULATOR_regs/rxregulator_spare0
  * rxregulator_spare0
  */

typedef union {
  struct {
    uint32_t REGSAR_SPARE : 8;
    ///< ---
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t  : 24;
    ///< Reserved
    ///< AccessType="RO" BitOffset="8" ResetValue="None"
  } ;
  uint32_t value;
} rxana_rxregulator_msg_rxregulator_spare0_reg_t;

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_DEFAULT (0x00000000U)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_RD_MASK (0x000000ffU)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_WR_MASK (0x000000ffU)


#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_REGSAR_SPARE_BF_OFF ( 0)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_REGSAR_SPARE_BF_WID ( 8)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_REGSAR_SPARE_BF_MSK (0x000000FF)
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_REGSAR_SPARE_BF_DEF (0x00000000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_REG(_BASE) ((rxana_rxregulator_msg_rxregulator_ctrl0_reg_t*) RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL0_ADR(_BASE))
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_REG(_BASE) ((rxana_rxregulator_msg_rxregulator_ctrl1_reg_t*) RXANA_RXREGULATOR_MSG_RXREGULATOR_CTRL1_ADR(_BASE))
#define RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_REG(_BASE) ((rxana_rxregulator_msg_rxregulator_spare0_reg_t*) RXANA_RXREGULATOR_MSG_RXREGULATOR_SPARE0_ADR(_BASE))

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    rxana_rxregulator_msg_rxregulator_ctrl0_reg_t RXREGULATOR_CTRL0; /*< Address offset = 0x0 */
    rxana_rxregulator_msg_rxregulator_ctrl1_reg_t RXREGULATOR_CTRL1; /*< Address offset = 0x4 */
    rxana_rxregulator_msg_rxregulator_spare0_reg_t RXREGULATOR_SPARE0; /*< Address offset = 0x8 */
} rxana_rxregulator_msg_t;     // size: 0x000c

// AddressSpace struct pointer
//
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL  ((rxana_rxregulator_msg_t*) DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE)
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q0      ((rxana_rxregulator_msg_t*) DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE)
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q1      ((rxana_rxregulator_msg_t*) DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE)
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q2      ((rxana_rxregulator_msg_t*) DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE)
#define DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q3      ((rxana_rxregulator_msg_t*) DLNK_JESD0_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE)
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL  ((rxana_rxregulator_msg_t*) DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE)
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q0      ((rxana_rxregulator_msg_t*) DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE)
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q1      ((rxana_rxregulator_msg_t*) DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE)
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q2      ((rxana_rxregulator_msg_t*) DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE)
#define DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q3      ((rxana_rxregulator_msg_t*) DLNK_JESD1_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE)
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL  ((rxana_rxregulator_msg_t*) DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE)
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q0      ((rxana_rxregulator_msg_t*) DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE)
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q1      ((rxana_rxregulator_msg_t*) DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE)
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q2      ((rxana_rxregulator_msg_t*) DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE)
#define DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q3      ((rxana_rxregulator_msg_t*) DLNK_JESD2_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE)
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL  ((rxana_rxregulator_msg_t*) DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_GLOBAL_BASE)
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q0      ((rxana_rxregulator_msg_t*) DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q0_BASE)
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q1      ((rxana_rxregulator_msg_t*) DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q1_BASE)
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q2      ((rxana_rxregulator_msg_t*) DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q2_BASE)
#define DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q3      ((rxana_rxregulator_msg_t*) DLNK_JESD3_PHY_PMA0_RXANA_RXREGULATOR_Q3_BASE)

// ******************************************* /Address Space

#endif      // _RXANA_RXREGULATOR_MSG_H_

