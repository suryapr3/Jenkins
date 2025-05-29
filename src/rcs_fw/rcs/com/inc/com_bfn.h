/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
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
#ifndef COMMON_BFN_H
#define COMMON_BFN_H

#include "com_definitions.h"
#include "com_platform.h"

typedef union {
    struct
    {
        uint32_t OFFSET : 24;
        uint32_t FRAME_P0 : 8;
        ///< Part 0 of TIMER_INC_PRE for Upper BFN Counter.
    };
    uint32_t value;
} com_bfn_cnt_low_t;

typedef union {
    struct
    {
        uint32_t FRAME_P1 : 32;
        ///< Part 1 of TIMER_INC_PRE for Upper BFN Counter.
    };
    uint32_t value;
} com_bfn_cnt_high_t;

typedef union {
    struct
    {
        com_bfn_cnt_low_t CNT_LOW;
        com_bfn_cnt_high_t CNT_HIGH;
    };
    struct
    {
        uint64_t OFFSET : 24;
        uint64_t FRAME : 40;
    };
    uint64_t value;
} com_bfn_cnt_t;

typedef com_bfn_cnt_t com_bfn_time_full_t;
typedef com_bfn_cnt_low_t com_bfn_time_t;

// BFNE_CONFIG.OUTPUT_MODE
#define COM_BFNE_CONFIG_OUTPUT_MODE_TOGGLE 0x0
#define COM_BFNE_CONFIG_OUTPUT_MODE_PULSE  0x1

// BFNE_CONFIG.MODE
#define COM_BFNE_CONFIG_MODE_SINGLE 0x0
#define COM_BFNE_CONFIG_MODE_DOUBLE 0x1
#define COM_BFNE_CONFIG_MODE_REPEAT 0x2

#if CPU_AX
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Check remote BFN, adjust if required. AX only.
 * @param [in]      none.
 * @return          bool: return true if has mismatch.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_bfn_chk_adj_remote ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Initialize BFN. AX only.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_timecom_bfn_sync_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_sync (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read BFN sysref time. AX only.
 * @param [in]      none.
 * @return          uint64_t: sysref BFN time.
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t com_bfn_get_sysref_time ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Adjust main and remote time. AX only.
 * @param [in]      offset_adj: offset adjustment, positive number to increase offset and negative number to decrease offset
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_time_adjust (int32_t const offset_adj);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set BFN antenna mask. AX only.
 * @param [in]      antenna_mask: Antenna mask.
 * @param [in]      jesd_mask: JESD mask.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_set_ant_mask (uint32_t const antenna_mask, uint32_t const jesd_mask);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Check whether remote mask is set.
 * @param [in]      none.
 * @return          true is remote is set, otherwise false.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_bfn_is_ant_mask_set ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           BFN initialization. AX only.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_init ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Reset BFN main time while it is running, no remote time involved. AX only.
 * @param [in]      int32_t bfn_sync_time_high, new high count
 * @param [in]      int32_t bfn_sync_time_low, new low count
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_main_reset_time (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Sync BFN time at boot time initialization. AX only.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_timecom_bfn_sync_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_sysref_sync (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           BFN shutdown.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_shutdown ();
#endif // CPU_AX

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set BFN clk freq and antenna mask. Called from both ATRX. AX must call after com_bfn_set_ant_mask.
 * @param [in]      drf_sel: drf clock select.
 * @param [in]      antenna_mask: antenna mask.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_set_clk_sel (e_sys_clk_t const drf_sel);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read live BFN time. For internal FW used only.
 * @param [in]      none.
 * @return          uint32_t: current bfn time, only low 32 bit count only.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t INTRINSIC_ALWAYS_INLINE com_bfn_get_live_time ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read live BFN time. For internal FW used only.
 * @param [in]      none.
 * @return          uint64_t: current bfn time, full 64 bit count
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t INTRINSIC_ALWAYS_INLINE com_bfn_get_live_time_full ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add 2 BFN time, base time is partial BFN time.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint32_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_bfn_add_time (uint32_t const time_base, uint32_t const time_offset);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add 2 BFN time, base time is full 64 bit.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint64_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t com_bfn_add_time_full (uint64_t const time_base, uint32_t const time_offset);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Subtract 2 BFN time.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint32_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_bfn_sub_time (uint32_t const time_base, uint32_t const time_offset);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Sync BFN time at using software without sysref. Dont call this until have the full antenna mask.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_timecom_bfn_sync_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_soft_sync (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set all remote time based on main time.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_self_sync ();
#endif // COMMON_BFN_H

/*
BFN sequence (for main + remotes start all at the same time)
1) During config, collect all TRX antenna mask
2) During warmup do, com_bfn_set_ant_mask -> bfn_init

BFN sequence (for main start first, then remotes start later)
1) During config do com_bfn_init first(1 time), then collect all TRX antenna mask
2) During warmup do, com_bfn_set_ant_mask -> sync (either com_bfn_sysref_sync or com_bfn_soft_sync)
*/
