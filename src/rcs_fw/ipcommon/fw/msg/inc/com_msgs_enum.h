/* INTEL CONFIDENTIAL
 *
 * Copyright 2023 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/

#ifndef __COM_MSGS_ENUM__
#define __COM_MSGS_ENUM__

#include <stdint.h>

typedef enum
{
    e_DL_CONFIG_ANT_GRP_OPCODE = 0xFFF1,
    e_DL_ON_OPCODE = 0xFFF3,
    e_DL_FAST_ON_OPCODE = 0xFF23,
    e_DL_UPDATE_CONTROL_OPCODE = 0xFFF4,
    e_DL_OFF_OPCODE = 0xFFF5,
    e_DL_FAST_OFF_OPCODE = 0xFF25,
    // DL SPI messages
    e_DL_SPI_ON_OPCODE = 0xFF33,
    e_DL_SPI_FAST_ON_OPCODE = 0xFF43,
    e_DL_SPI_OFF_OPCODE = 0xFF35,
    e_DL_SPI_FAST_OFF_OPCODE = 0xFF45,

    e_UL_CONFIG_ANT_GRP_OPCODE = 0xFFF6,
    e_UL_ON_OPCODE = 0xFFF8,
    e_UL_FAST_ON_OPCODE = 0xFF28,
    e_UL_UPDATE_CONTROL_OPCODE = 0xFFF9,
    e_UL_OFF_OPCODE = 0xFFFA,
    e_UL_FAST_OFF_OPCODE = 0xFF2A,
    // UL SPI messages
    e_UL_SPI_ON_OPCODE = 0xFF38,
    e_UL_SPI_FAST_ON_OPCODE = 0xFF48,
    e_UL_SPI_OFF_OPCODE = 0xFF3A,
    e_UL_SPI_FAST_OFF_OPCODE = 0xFF4A,

    e_RB_ON_DL_OPCODE = 0xFFFB,
    e_RB_ON_UL_OPCODE = 0xFFFC,
    e_RB_DBG_OPCODE = 0xFFFD,
    e_RB_ERR_OPCODE = 0xFFFE,
    e_RB_BOOT_OPCODE = 0xFFFF,
    e_RB_CONFIG_DL_OPCODE = 0xFFEB,
    e_RB_CONFIG_UL_OPCODE = 0xFFEC,
    e_RB_WARMUP_OPCODE = 0xFFEE,

    e_BFN_SYNC_OPCODE = 0xFF10,
    e_CAL_CONFIG_OPCODE = 0xFF11,
    e_SLEEP_CONTROL_OPCODE = 0xFF12,
    e_RECONFIG_OPCODE = 0xFF13,
    e_SHUTDOWN_OPCODE = 0xFF14,
    e_WARMUP_OPCODE = 0xFF15,

    e_SET_TIME_REF_OPCODE = 0xFF16,
} e_opcode_type_t;

typedef enum
{
    e_TS_TYPE_IMM_TIMESTAMP = 0, // MC_TIMESTAMP is interpreted as immediate time stamp value.
    e_TS_TYPE_REL_TIMESTAMP = 1, // MC_TIMESTAMP is interpreted as relative time stamp value.
    e_TS_TYPE_ABS_TIMESTAMP = 2, // MC_TIMESTAMP is interpreted as absolute time stamp value.
    e_TS_TYPE_MAX = 3            // maximum enum value

} e_timing_type_t;

typedef enum
{
    e_DPD_LEARN_DIRECT,
    e_DPD_LEARN_INDIRECT
} e_dpd_learn_t;

typedef enum
{
    e_UL_CAL_UPDATE_NONE,
    e_UL_CAL_ADC_SLICE_UPDATE,
    e_UL_CAL_NLEQ_UPDATE,
    e_UL_CAL_GAIN_UPDATE
} e_ul_cal_update_type_t;

typedef enum
{
    e_DL_CAL_UPDATE_NONE,
    e_DL_CAL_CDAC_SMC_UPDATE,
    e_DL_CAL_CDAC_DPD_UPDATE,
    e_DL_CAL_CDAC_DESKEW_UPDATE,
    e_DL_CAL_PA_DPD_UPDATE
} e_dl_cal_update_type_t;

typedef enum
{
    e_INFO,
    e_WARN,
    e_ERROR,
    e_FATAL,
    // E_ERROR_MAX
} e_error_type_t; // Error Level

typedef enum
{
    e_INVALID_OPCODE_ERR,
    e_MSG_TIMING_ERR,
    e_EXCEPTION_ERR,
    e_EVENT_HANDLER_ERR,
    e_IRQ_ERR,
    e_FSM_TRANSITION_ERR,
    e_QUAD_FSM_TRANSITION_ERR,
    e_BOOT_ERR,
    e_CONFIG_MSG_ERR,
    e_ERROR_CODE_MAX
} e_error_code_type_t; // module level info

typedef enum
{
    e_REASON_CODE_NA = -1,
    e_MSG_MAX_LEAD_TIME_ERR = 10,
    e_MSG_MIN_LEAD_TIME_ERR = 11,
    e_MSG_TS2TS_ERR = 12,
    e_USER_EXCEPTION = 20,
    e_KERNEL_EXCEPTION = 21,
    e_DOUBLE_EXCEPTION = 22,
    e_INVALID_EVENT_IDX = 30,
    e_EVENT_OVERFLOW = 31,
    e_EVENT_STATE_ERR = 32,
    e_UNHANDLED_IRQ_ERR = 40,
    e_FSM_TRANSITION_STATE_ERR = 51,
    e_QUAD_FSM_TRANSITION_STATE_ERR = 61,
    e_CORE_SYNC_TIMEOUT = 70,        // core sync timeout during bootup
    e_CORE_FW_MISMATCH = 71,         // core and FW mismatch
    e_CFG_ANTENNA_MASK_QUAD_ERR = 80 // quad already configured
} e_reason_code_type_t;              // Error Type within Module

typedef enum
{
    e_CGS_MAX
} e_cgs_type_t;

typedef enum
{
    e_CPS_MAX
} e_cps_type_t;

typedef enum
{
    e_DBG_TRACE,
    e_DBG_LOW,
    e_DBG_MEDIUM,
    e_DBG_HIGH,
    // E_DBG_ERROR_MAX
} e_debug_level_type_t; // Error Level

typedef enum
{
    e_NO_LOOPBACK,
    e_JESD_LOOPBACK,
    e_V2D_LOOPBACK,
    e_VEX_LOOPBACK,
    e_DIGRF_LOOPBACK,
    e_DIGRF2_LOOPBACK,
    e_ANTENNA_LOOPBACK,
    e_LOOPBACK_MODE_MAX
} e_loopback_mode_type_t;

typedef enum
{
    e_BFN_SYNC_TYPE_EXT,
    e_BFN_SYNC_TYPE_SOFT,
} e_bfn_sync_type_t;

#endif // __COM_MSGS_ENUM__
