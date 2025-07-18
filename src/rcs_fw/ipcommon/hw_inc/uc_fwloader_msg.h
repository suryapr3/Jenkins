#ifndef _UC_FWLOADER_MSG_H_
#define _UC_FWLOADER_MSG_H_

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

#define DLNK_JESD0_PHY_UC_FWLOADER_BASE  ( 0x06000300 )
#define DLNK_JESD1_PHY_UC_FWLOADER_BASE  ( 0x06800300 )
#define DLNK_JESD2_PHY_UC_FWLOADER_BASE  ( 0x07000300 )
#define DLNK_JESD3_PHY_UC_FWLOADER_BASE  ( 0x07800300 )

// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define UC_FWLOADER_MSG_ADDR_OFFSET ( 0x00000000U )
#define UC_FWLOADER_MSG_LOAD_DATA_OFFSET ( 0x00000004U )
#define UC_FWLOADER_MSG_FWLOADER_CTRL_OFFSET ( 0x00000008U )
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_OFFSET ( 0x0000000cU )
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_OFFSET ( 0x00000010U )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define UC_FWLOADER_MSG_ADDR_OFFSET_ADR(_BASE) (( ( _BASE ) + ( UC_FWLOADER_MSG_ADDR_OFFSET ) ))
#define UC_FWLOADER_MSG_LOAD_DATA_ADR(_BASE) (( ( _BASE ) + ( UC_FWLOADER_MSG_LOAD_DATA_OFFSET ) ))
#define UC_FWLOADER_MSG_FWLOADER_CTRL_ADR(_BASE) (( ( _BASE ) + ( UC_FWLOADER_MSG_FWLOADER_CTRL_OFFSET ) ))
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_ADR(_BASE) (( ( _BASE ) + ( UC_FWLOADER_MSG_FWLOADER_APB_CTRL_OFFSET ) ))
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_ADR(_BASE) (( ( _BASE ) + ( UC_FWLOADER_MSG_FWLOADER_APB_STAT_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief UC_FWLOADER_REGS_MSG_UC_FWLOADER_REGS_ADDR_OFFSET register description at address offset 0x0
  *
  * Register default value:        0x00000000
  * Register full path in IP: UC_FWLOADER_regs_MSG/UC_FWLOADER_regs/addr_offset
  * placeholder
  */

typedef union {
  struct {
    uint32_t ADDR_OFFSET : 32;
    ///< Indirect Access Address Offset
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} uc_fwloader_msg_addr_offset_reg_t;

#define UC_FWLOADER_MSG_ADDR_OFFSET_DEFAULT (0x00000000U)
#define UC_FWLOADER_MSG_ADDR_OFFSET_RD_MASK (0xffffffffU)
#define UC_FWLOADER_MSG_ADDR_OFFSET_WR_MASK (0xffffffffU)


///< Indirect Access Address Offset
#define UC_FWLOADER_MSG_ADDR_OFFSET_ADDR_OFFSET_BF_OFF ( 0)
#define UC_FWLOADER_MSG_ADDR_OFFSET_ADDR_OFFSET_BF_WID (32)
#define UC_FWLOADER_MSG_ADDR_OFFSET_ADDR_OFFSET_BF_MSK (0xFFFFFFFF)
#define UC_FWLOADER_MSG_ADDR_OFFSET_ADDR_OFFSET_BF_DEF (0x00000000)


/** @brief UC_FWLOADER_REGS_MSG_UC_FWLOADER_REGS_LOAD_DATA register description at address offset 0x4
  *
  * Register default value:        0x00000000
  * Register full path in IP: UC_FWLOADER_regs_MSG/UC_FWLOADER_regs/load_data
  * placeholder
  */

typedef union {
  struct {
    uint32_t LOAD_DATA : 32;
    ///< Indirect Access Data
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} uc_fwloader_msg_load_data_reg_t;

#define UC_FWLOADER_MSG_LOAD_DATA_DEFAULT (0x00000000U)
#define UC_FWLOADER_MSG_LOAD_DATA_RD_MASK (0xffffffffU)
#define UC_FWLOADER_MSG_LOAD_DATA_WR_MASK (0xffffffffU)


///< Indirect Access Data
#define UC_FWLOADER_MSG_LOAD_DATA_LOAD_DATA_BF_OFF ( 0)
#define UC_FWLOADER_MSG_LOAD_DATA_LOAD_DATA_BF_WID (32)
#define UC_FWLOADER_MSG_LOAD_DATA_LOAD_DATA_BF_MSK (0xFFFFFFFF)
#define UC_FWLOADER_MSG_LOAD_DATA_LOAD_DATA_BF_DEF (0x00000000)


/** @brief UC_FWLOADER_REGS_MSG_UC_FWLOADER_REGS_FWLOADER_CTRL register description at address offset 0x8
  *
  * Register default value:        0x00000000
  * Register full path in IP: UC_FWLOADER_regs_MSG/UC_FWLOADER_regs/fwloader_ctrl
  * placeholder
  */

typedef union {
  struct {
    uint32_t FWLOADER_EN : 1;
    ///< FW Loader Enable
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SINGLE_MODE_EN : 1;
    ///< FW Loader Single Mode - address will not auto-increment.
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t  : 30;
    ///< Reserved
    ///< AccessType="RO" BitOffset="2" ResetValue="None"
  } ;
  uint32_t value;
} uc_fwloader_msg_fwloader_ctrl_reg_t;

#define UC_FWLOADER_MSG_FWLOADER_CTRL_DEFAULT (0x00000000U)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_RD_MASK (0x00000003U)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_WR_MASK (0x00000003U)


///< FW Loader Enable
#define UC_FWLOADER_MSG_FWLOADER_CTRL_FWLOADER_EN_BF_OFF ( 0)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_FWLOADER_EN_BF_WID ( 1)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_FWLOADER_EN_BF_MSK (0x00000001)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_FWLOADER_EN_BF_DEF (0x00000000)

///< FW Loader Single Mode - address will not auto-increment.
#define UC_FWLOADER_MSG_FWLOADER_CTRL_SINGLE_MODE_EN_BF_OFF ( 1)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_SINGLE_MODE_EN_BF_WID ( 1)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_SINGLE_MODE_EN_BF_MSK (0x00000002)
#define UC_FWLOADER_MSG_FWLOADER_CTRL_SINGLE_MODE_EN_BF_DEF (0x00000000)


/** @brief UC_FWLOADER_REGS_MSG_UC_FWLOADER_REGS_FWLOADER_APB_CTRL register description at address offset 0xc
  *
  * Register default value:        0x00000000
  * Register full path in IP: UC_FWLOADER_regs_MSG/UC_FWLOADER_regs/fwloader_apb_ctrl
  * APB Control
  */

typedef union {
  struct {
    uint32_t APB_LATENCY_MEASURE_EN : 1;
    ///< Enable FW loader APB latency measurment
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t APB_PSTATUS_CLEAR : 1;
    ///< To clear the FW loader apb_pstatus RO register
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t  : 30;
    ///< Reserved
    ///< AccessType="RO" BitOffset="2" ResetValue="None"
  } ;
  uint32_t value;
} uc_fwloader_msg_fwloader_apb_ctrl_reg_t;

#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_DEFAULT (0x00000000U)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_RD_MASK (0x00000003U)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_WR_MASK (0x00000003U)


///< Enable FW loader APB latency measurment
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_LATENCY_MEAS_EN_BF_OFF ( 0)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_LATENCY_MEAS_EN_BF_WID ( 1)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_LATENCY_MEAS_EN_BF_MSK (0x00000001)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_LATENCY_MEAS_EN_BF_DEF (0x00000000)

///< To clear the FW loader apb_pstatus RO register
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_PSTAT_CLR_BF_OFF ( 1)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_PSTAT_CLR_BF_WID ( 1)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_PSTAT_CLR_BF_MSK (0x00000002)
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_APB_PSTAT_CLR_BF_DEF (0x00000000)


/** @brief UC_FWLOADER_REGS_MSG_UC_FWLOADER_REGS_FWLOADER_APB_STATUS register description at address offset 0x10
  *
  * Register default value:        0x00000000
  * Register full path in IP: UC_FWLOADER_regs_MSG/UC_FWLOADER_regs/fwloader_apb_status
  * APB Status
  */

typedef union {
  struct {
    uint32_t APB_LATENCY_MEASURE_RESULT : 15;
    ///< Report the largest latency for FW loader Fabric since apb latency
    ///< measurment block is enabled.  The result will be cleared when the
    ///< measrument block is disabled
    ///< AccessType="RO/V" BitOffset="0" ResetValue="0x0"
    uint32_t APB_WDT_RUN : 1;
    ///< To indicate is the FW loader APB watch dog timer has been turned on
    ///< AccessType="RO/V" BitOffset="15" ResetValue="0x0"
    uint32_t APB_PSTATUS : 4;
    ///< To indicate the last FW loader apb transcation status.
    ///< Bit 0: Security miss
    ///< Bit 1: Address miss
    ///< Bit 2: General AHB error
    ///< Bit 3: Timeout
    ///< AccessType="RO/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 12;
    ///< Reserved
    ///< AccessType="RO" BitOffset="20" ResetValue="None"
  } ;
  uint32_t value;
} uc_fwloader_msg_fwloader_apb_stat_reg_t;

#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_DEFAULT (0x00000000U)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_RD_MASK (0x000fffffU)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_WR_MASK (0x00000000U)


///< Report the largest latency for FW loader Fabric since apb latency
///< measurment block is enabled.  The result will be cleared when the
///< measrument block is disabled
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_LATENCY_MEAS_RSLT_BF_OFF ( 0)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_LATENCY_MEAS_RSLT_BF_WID (15)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_LATENCY_MEAS_RSLT_BF_MSK (0x00007FFF)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_LATENCY_MEAS_RSLT_BF_DEF (0x00000000)

///< To indicate is the FW loader APB watch dog timer has been turned on
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_WDT_RUN_BF_OFF (15)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_WDT_RUN_BF_WID ( 1)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_WDT_RUN_BF_MSK (0x00008000)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_WDT_RUN_BF_DEF (0x00000000)

///< To indicate the last FW loader apb transcation status.
///< Bit 0: Security miss
///< Bit 1: Address miss
///< Bit 2: General AHB error
///< Bit 3: Timeout
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_PSTAT_BF_OFF (16)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_PSTAT_BF_WID ( 4)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_PSTAT_BF_MSK (0x000F0000)
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_APB_PSTAT_BF_DEF (0x00000000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define UC_FWLOADER_MSG_ADDR_OFFSET_REG(_BASE) ((uc_fwloader_msg_addr_offset_reg_t*) UC_FWLOADER_MSG_ADDR_OFFSET_ADR(_BASE))
#define UC_FWLOADER_MSG_LOAD_DATA_REG(_BASE) ((uc_fwloader_msg_load_data_reg_t*) UC_FWLOADER_MSG_LOAD_DATA_ADR(_BASE))
#define UC_FWLOADER_MSG_FWLOADER_CTRL_REG(_BASE) ((uc_fwloader_msg_fwloader_ctrl_reg_t*) UC_FWLOADER_MSG_FWLOADER_CTRL_ADR(_BASE))
#define UC_FWLOADER_MSG_FWLOADER_APB_CTRL_REG(_BASE) ((uc_fwloader_msg_fwloader_apb_ctrl_reg_t*) UC_FWLOADER_MSG_FWLOADER_APB_CTRL_ADR(_BASE))
#define UC_FWLOADER_MSG_FWLOADER_APB_STAT_REG(_BASE) ((uc_fwloader_msg_fwloader_apb_stat_reg_t*) UC_FWLOADER_MSG_FWLOADER_APB_STAT_ADR(_BASE))

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    uc_fwloader_msg_addr_offset_reg_t ADDR_OFFSET; /*< Address offset = 0x0 */
    uc_fwloader_msg_load_data_reg_t LOAD_DATA; /*< Address offset = 0x4 */
    uc_fwloader_msg_fwloader_ctrl_reg_t FWLOADER_CTRL; /*< Address offset = 0x8 */
    uc_fwloader_msg_fwloader_apb_ctrl_reg_t FWLOADER_APB_CTRL; /*< Address offset = 0xc */
    uc_fwloader_msg_fwloader_apb_stat_reg_t FWLOADER_APB_STAT; /*< Address offset = 0x10 */
} uc_fwloader_msg_t;     // size: 0x0014

// AddressSpace struct pointer
//
#define DLNK_JESD0_PHY_UC_FWLOADER  ((uc_fwloader_msg_t*) DLNK_JESD0_PHY_UC_FWLOADER_BASE)
#define DLNK_JESD1_PHY_UC_FWLOADER  ((uc_fwloader_msg_t*) DLNK_JESD1_PHY_UC_FWLOADER_BASE)
#define DLNK_JESD2_PHY_UC_FWLOADER  ((uc_fwloader_msg_t*) DLNK_JESD2_PHY_UC_FWLOADER_BASE)
#define DLNK_JESD3_PHY_UC_FWLOADER  ((uc_fwloader_msg_t*) DLNK_JESD3_PHY_UC_FWLOADER_BASE)

// ******************************************* /Address Space

#endif      // _UC_FWLOADER_MSG_H_

