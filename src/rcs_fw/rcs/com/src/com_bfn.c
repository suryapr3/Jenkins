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

/**
 * @file    com_bfn.c
 * @brief   BFN common functions.
 * @details All common BFN APIs.
 * @todo    None.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "ant_csr.h"
#include "bfn_csr.h"
#include "com_assert.h"
#include "com_bfn.h"
#include "com_isr.h"
#include "com_print.h"
#include "ax_static_data_table.h"
#include "ctl.h"
#include "fb_ant_local.h"
#include "fb_sys_local.h"
#include "jesd_bfn_events.h"
#include "mem_cap_cfg.h"
#include "mem_fb.h"
#include "rcs_gpreg.h"
#include "rcs_timer_gpreg.h"
#include "trx_sys_csr.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define BFN_ISYNC_2COM_BFN(x)  ((com_bfn_clnt_isync_ctrl_t *)(x))
#define BFN_TEN_MS_2COM_BFN(x) ((com_bfn_ten_ms_cnt_t *)(x))
#define BFN_CNTLOW_2COM_BFN(x) ((com_bfn_cnt_low_t *)(x))

#define COM_BFN_INST1 1
#define COM_BFN_INST2 2
#define COM_BFN_INST4 4
#define COM_BFN_INST8 8

#define COM_BFN_INST_TBL_NAME(X)       (com_bfn_##X##inst_tbl)
#define COM_BFN_COMP_CNT(BFN_INST_CNT) (sizeof (COM_BFN_INST_TBL_NAME (BFN_INST_CNT)) / sizeof (com_bfn_remote_t) / BFN_INST_CNT)

#define COM_BFN_983_CNTL_TOTAL  0x960000
#define COM_BFN_1474_CNTL_TOTAL 0xE10000
#define COM_BFN_CNTL_INVALID    0
#define COM_BFN_ANT_MASK_NONE   0

#define COM_BFN_INC_PRE_DEFAULT BFN_CSR_AW_ISYNC_INC_PRE_DEFAULT
#define COM_BFN_OVAL_EXT_DIS_MASK \
    (~(RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_EXTSYNC_EN_BF_MSK | RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_SYSREFEN_BF_MSK))
#define COM_BFN_OVAL_SYSREF_EN  (g_bfn_oops_cfg | RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_ONEPPS_VAL_BF_DEF)
#define COM_BFN_OVAL_SYSREF_DIS ((g_bfn_oops_cfg & COM_BFN_OVAL_EXT_DIS_MASK) | RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_ONEPPS_VAL_BF_DEF)
#define COM_BFN_SYNC_INTR       e_BFN_TIMESYNC_STRECHED_EDGE_IRQ2
#define COM_BFN_INTR_STAT       (1 << 19)

#define BFN_SELFSYNC_OFFSET_983  get_tf (ax_bfn_selfsync_lut, 0, self_sync_offset)
#define BFN_SELFSYNC_OFFSET_1474 get_tf (ax_bfn_selfsync_lut, 1, self_sync_offset)

// clang-format off
// Configure BFN tbl by component name
#define COM_BFN_1INST_CFG(BFN_NAME)                                                 \
    {{BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG),                               \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG),                        \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG),                           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG)}

#define COM_BFN_2INST_CFG(BFN_NAME, BASE_ADDR0, BASE_ADDR1)                         \
    {{BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR0)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR0)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR0)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR0))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR1)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR1)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR1)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR1))}}

#define COM_BFN_4INST_CFG(BFN_NAME, BASE_ADDR0, BASE_ADDR1, BASE_ADDR2, BASE_ADDR3) \
    {{BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR0)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR0)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR0)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR0))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR1)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR1)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR1)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR1))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR2)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR2)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR2)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR2))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR3)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR3)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR3)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR3))}}

#define COM_BFN_8INST_CFG(BFN_NAME, BASE_ADDR0, BASE_ADDR1, BASE_ADDR2, BASE_ADDR3, \
                          BASE_ADDR4, BASE_ADDR5, BASE_ADDR6, BASE_ADDR7)           \
    {{BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR0)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR0)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR0)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR0))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR1)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR1)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR1)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR1))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR2)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR2)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR2)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR2))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR3)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR3)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR3)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR3))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR4)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR4)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR4)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR4))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR5)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR5)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR5)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR5))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR6)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR6)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR6)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR6))},        \
     {BFN_ISYNC_2COM_BFN (BFN_NAME##_ISYNC_CTRL_REG (BASE_ADDR7)),                  \
      BFN_TEN_MS_2COM_BFN (BFN_NAME##_ISYNC_TEN_MS_CNT_REG (BASE_ADDR7)),           \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_INC_PRE_REG (BASE_ADDR7)),              \
      BFN_CNTLOW_2COM_BFN (BFN_NAME##_ISYNC_BFN_CNT_SYNC_REG (BASE_ADDR7))}}
// clang-format on

#define MAX_BFN_ANT               (16)
#define BFN_RMT_CMD_BF_OFF        (BFN_CSR_AW_ISYNC_CTRL_TIMER_CMD_BF_OFF)
#define BFN_RMT_LOAD_READ_BF_OFF  (BFN_CSR_AW_ISYNC_CTRL_LOAD_READ_BF_OFF)
#define BFN_RMT_CNT_SAMPLE_BF_OFF (BFN_CSR_AW_ISYNC_CTRL_BFN_CNT_SAMPLE_BF_OFF)
#define BFN_RMT_SOFT_RST_BF_OFF   (BFN_CSR_AW_ISYNC_CTRL_SOFT_RST_BF_OFF)

#define BFN_COM_ISYNC_CMD_INC_LCNT (0x0)
#define BFN_COM_ISYNC_CMD_PRESET   (0x1)
#define BFN_COM_ISYNC_CMD_INIT     (0x2)
#define BFN_COM_ISYNC_CMD_INC      (0x3)
#define BFN_COM_ISYNC_CMD_SYNC_ADJ (0x5)
#define BFN_COM_ISYNC_CMD_CAP      (0x7)
#define BFN_COM_ISYNC_CLEAR        (0x00000000)

#define BFN_MAIN_ISYNC_CLEAR        (BFN_COM_ISYNC_CLEAR)                                                  // 0x00000000
#define BFN_MAIN_ISYNC_TRIG         (0x1 << RCS_TIMER_GPREG_ICTRL_ISYNC_TRIG_BF_OFF)                       // 0x00000080
#define BFN_MAIN_ISYNC_LOAD         (0x1 << RCS_TIMER_GPREG_ICTRL_LOAD_READ_BF_OFF)                        // 0x00000100
#define BFN_MAIN_ISYNC_READ         (0x0 << RCS_TIMER_GPREG_ICTRL_LOAD_READ_BF_OFF)                        // 0x00000000
#define BFN_MAIN_ISYNC_SOFT_RST     (0x1 << RCS_TIMER_GPREG_ICTRL_SOFT_RST_BF_OFF)                         // 0x00008000
#define BFN_MAIN_ISYNC_VAL_DEF      (0x0 << RCS_TIMER_GPREG_ICTRL_ISYNC_VAL_BF_OFF)                        // 0x00000000
#define BFN_MAIN_ISYNC_VAL_INC      (0x1 << RCS_TIMER_GPREG_ICTRL_ISYNC_VAL_BF_OFF)                        // 0x00000010
#define BFN_MAIN_ISYNC_VAL_DEC      (0x2 << RCS_TIMER_GPREG_ICTRL_ISYNC_VAL_BF_OFF)                        // 0x00000020
#define BFN_MAIN_ISYNC_VAL_CMD      (0x3 << RCS_TIMER_GPREG_ICTRL_ISYNC_VAL_BF_OFF)                        // 0x00000030
#define BFN_MAIN_ISYNC_SOFT_RESET   (0x1 << RCS_TIMER_GPREG_ICTRL_SOFT_RST_BF_OFF)                         // 0x00008000
#define BFN_MAIN_ISYNC_CMD_INC_LCNT (BFN_COM_ISYNC_CMD_INC_LCNT << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF) // 0x00000000
#define BFN_MAIN_ISYNC_CMD_PRESET   (BFN_COM_ISYNC_CMD_PRESET << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF)   // 0x00000001
#define BFN_MAIN_ISYNC_CMD_INIT     (BFN_COM_ISYNC_CMD_INIT << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF)     // 0x00000002
#define BFN_MAIN_ISYNC_CMD_INC_PRE  (BFN_COM_ISYNC_CMD_INC << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF)      // 0x00000003
#define BFN_MAIN_ISYNC_CMD_ADJ      (BFN_COM_ISYNC_CMD_SYNC_ADJ << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF) // 0x00000005
#define BFN_MAIN_ISYNC_CMD_CAP      (BFN_COM_ISYNC_CMD_CAP << RCS_TIMER_GPREG_ICTRL_TIMER_CMD_BF_OFF)      // 0x00000007

#define BFN_RMT_ISYNC_CLEAR        (BFN_COM_ISYNC_CLEAR)                              // 0x00000000
#define BFN_RMT_ISYNC_LOAD         (0x1 << BFN_RMT_LOAD_READ_BF_OFF)                  // 0x00000010
#define BFN_RMT_ISYNC_READ         (0x0 << BFN_RMT_LOAD_READ_BF_OFF)                  // 0x00000000
#define BFN_RMT_ISYNC_RESET        (0x1 << BFN_CSR_AW_ISYNC_CTRL_SOFT_RST_BF_OFF)     // 0x00008000
#define BFN_RMT_ISYNC_CMD_INC_LCNT (BFN_COM_ISYNC_CMD_INC_LCNT << BFN_RMT_CMD_BF_OFF) // 0x00000000
#define BFN_RMT_ISYNC_CMD_PRESET   (BFN_COM_ISYNC_CMD_PRESET << BFN_RMT_CMD_BF_OFF)   // 0x00000001
#define BFN_RMT_ISYNC_CMD_INIT     (BFN_COM_ISYNC_CMD_INIT << BFN_RMT_CMD_BF_OFF)     // 0x00000002
#define BFN_RMT_ISYNC_CMD_INC_PRE  (BFN_COM_ISYNC_CMD_INC << BFN_RMT_CMD_BF_OFF)      // 0x00000003
#define BFN_RMT_ISYNC_CMD_ADJ      (BFN_COM_ISYNC_CMD_SYNC_ADJ << BFN_RMT_CMD_BF_OFF) // 0x00000005
#define BFN_RMT_ISYNC_CMD_CAP      (BFN_COM_ISYNC_CMD_CAP << BFN_RMT_CMD_BF_OFF)      // 0x00000007

// main
#define BFN_MAIN_ISYNC_CMD    (BFN_MAIN_ISYNC_TRIG | BFN_MAIN_ISYNC_VAL_CMD)   // 0x000000B0
#define BFN_MAIN_ISYNC_PRESET (BFN_MAIN_ISYNC_CMD | BFN_MAIN_ISYNC_CMD_PRESET) // 0x000000B1
#define BFN_MAIN_ISYNC_INIT   (BFN_MAIN_ISYNC_CMD | BFN_MAIN_ISYNC_CMD_INIT)   // 0x000000B2
#define BFN_MAIN_ISYNC_CAP    (BFN_MAIN_ISYNC_CMD | BFN_MAIN_ISYNC_CMD_CAP)    // 0x000000B7
#define BFN_MAIN_ISYNC_INC    (BFN_MAIN_ISYNC_TRIG | BFN_MAIN_ISYNC_VAL_INC)   // 0x00000090
#define BFN_MAIN_ISYNC_DEC    (BFN_MAIN_ISYNC_TRIG | BFN_MAIN_ISYNC_VAL_DEC)   // 0x000000A0

// remote
#define BFN_RMT_ISYNC_PRESET (BFN_RMT_ISYNC_CMD_PRESET) // 0x00000001
#define BFN_RMT_ISYNC_INIT   (BFN_RMT_ISYNC_CMD_INIT)   // 0x00000002
#define BFN_RMT_ISYNC_CAP    (BFN_RMT_ISYNC_CMD_CAP)    // 0x00000007

// !!! Delay Needed in between BFN command is at least 20 NOPS (no margin at all), recommended 28 NOPS !!!

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
// use bfn_csr as common
typedef bfn_csr_aw_isync_ctrl_reg_t com_bfn_clnt_isync_ctrl_t;
typedef bfn_csr_aw_isync_ten_ms_cnt_reg_t com_bfn_ten_ms_cnt_t;

typedef struct
{
    com_bfn_clnt_isync_ctrl_t *const com_bfn_isync_ctrl;
    com_bfn_ten_ms_cnt_t *const com_bfn_ten_ms_cnt;
    com_bfn_cnt_low_t *const com_bfn_inc_pre;
    com_bfn_cnt_low_t const *const com_bfn_cnt_sync;
} com_bfn_remote_t;

typedef struct
{
    bool com_bfn_in_use;
} com_bfn_cfg_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
PRIVATE uint32_t g_bfn_cntl_total = COM_BFN_CNTL_INVALID;

#if CPU_AX
PRIVATE uint32_t g_bfn_oops_cfg = 0;
PRIVATE bool g_bfn_have_rmt = false;
PRIVATE bool g_bfn_rmt_check = true;
PRIVATE bool g_bfn_rmt_started = false;
PRIVATE bool g_bfn_is_ext_sync = false;
#endif // CPU_AX

// No com_bfn_1inst_tbl
PRIVATE com_bfn_remote_t com_bfn_2inst_tbl[][COM_BFN_INST2] = {COM_BFN_2INST_CFG (FB_ANT_LOCAL, FB_ANT0_CSR_BASE, FB_ANT1_CSR_BASE),
                                                               COM_BFN_2INST_CFG (FB_SYS_LOCAL, FB_SYS0_CTL_BASE, FB_SYS1_CTL_BASE),
                                                               COM_BFN_2INST_CFG (MEM_CAP_CFG, MEM_CAP0_CFG_BASE, MEM_CAP1_CFG_BASE),
                                                               COM_BFN_2INST_CFG (MEM_FB, MEM_FB0_CFG_BASE, MEM_FB1_CFG_BASE)};

PRIVATE com_bfn_remote_t com_bfn_4inst_tbl[][COM_BFN_INST4] = {
    COM_BFN_4INST_CFG (ANT_CSR, ANT0_CSR_BASE, ANT1_CSR_BASE, ANT2_CSR_BASE, ANT3_CSR_BASE)};

PRIVATE com_bfn_remote_t com_bfn_8inst_tbl[][COM_BFN_INST8] = {
    COM_BFN_8INST_CFG (BFN_CSR_AW, V2D0_BFN_CSR_BASE, V2D1_BFN_CSR_BASE, V2D2_BFN_CSR_BASE, V2D3_BFN_CSR_BASE, V2D4_BFN_CSR_BASE,
                       V2D5_BFN_CSR_BASE, V2D6_BFN_CSR_BASE, V2D7_BFN_CSR_BASE),
    COM_BFN_8INST_CFG (TRX_SYS_CSR, TRX_SYS0_CSR_BASE, TRX_SYS1_CSR_BASE, TRX_SYS2_CSR_BASE, TRX_SYS3_CSR_BASE, TRX_SYS4_CSR_BASE,
                       TRX_SYS5_CSR_BASE, TRX_SYS6_CSR_BASE, TRX_SYS7_CSR_BASE),
    COM_BFN_8INST_CFG (CTL, TRX_ANT0_CTL_BASE, TRX_ANT1_CTL_BASE, TRX_ANT2_CTL_BASE, TRX_ANT3_CTL_BASE, TRX_ANT4_CTL_BASE,
                       TRX_ANT5_CTL_BASE, TRX_ANT6_CTL_BASE, TRX_ANT7_CTL_BASE)};

PRIVATE com_bfn_remote_t com_bfn_jesd_tbl[][COM_BFN_INST4] = {COM_BFN_4INST_CFG (
    JESD_BFNE, DLNK_JESD0_BFN_EVENTS_BASE, DLNK_JESD1_BFN_EVENTS_BASE, DLNK_JESD2_BFN_EVENTS_BASE, DLNK_JESD3_BFN_EVENTS_BASE)};

PRIVATE com_bfn_cfg_t com_bfn_2inst_cfg[COM_BFN_INST2] = {false};
PRIVATE com_bfn_cfg_t com_bfn_4inst_cfg[COM_BFN_INST4] = {false};
PRIVATE com_bfn_cfg_t com_bfn_8inst_cfg[COM_BFN_INST8] = {false};
PRIVATE com_bfn_cfg_t com_bfn_jesd_cfg[COM_BFN_INST4] = {false};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
#if CPU_AX
PRIVATE void INTRINSIC_ALWAYS_INLINE com_bfn_sync_intr_clr ();

PRIVATE void com_bfn_sync_intr_init ();
PRIVATE void com_bfn_armed_clear ();
PRIVATE void com_bfn_soft_reset ();
PRIVATE void com_bfn_remote_start ();
PRIVATE void com_bfn_main_set_pre_time (uint32_t const bfn_sync_time_upper, uint32_t const bfn_sync_time_lower);
PRIVATE void com_bfn_remote_set_pre_time (uint32_t const bfn_sync_time_low);
PRIVATE void com_bfn_remote_set_isync_ctrl (uint32_t const isync_ctrl);
PRIVATE void com_bfn_remote_ten_ms_cnt (uint32_t const bfn_ten_ms_cnt);
PRIVATE void com_bfn_set_ten_ms_cnt (uint32_t const bfn_ten_ms_cnt);
PRIVATE void com_bfn_arm (bool const load_syref);
PRIVATE void com_bfn_loop_set_pre_time (uint32_t const bfn_sync_time_low, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                        com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                        com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst]);
PRIVATE void com_bfn_loop_set_isync_ctrl (uint32_t const isync_ctrl, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                          com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                          com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst]);
PRIVATE void com_bfn_loop_set_ten_ms_cnt (uint32_t const ten_ms_cnt, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                          com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                          com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst]);
PRIVATE void com_bfn_set_in_use (uint32_t const cnt_inst, uint32_t const ant_mask, com_bfn_cfg_t p_com_bfn_cfg_tbl[cnt_inst]);
PRIVATE void com_bfn_set_jesd_in_use (uint32_t const cnt_inst, uint32_t const ant_mask, com_bfn_cfg_t p_com_bfn_cfg_tbl[cnt_inst]);

PRIVATE void com_bfn_sync_handler (void *p_arg);
PRIVATE bool com_bfn_loop_chk_remote_time (com_bfn_cnt_low_t const time_main, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                           com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                           com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst]);
PRIVATE bool bfn_in_use (uint32_t const cnt_inst, uint32_t const current_inst, uint32_t const bfn_ant_mask);
PRIVATE com_bfn_cnt_t com_bfn_main_get_snapshot_time ();
PRIVATE void inline com_bfn_sysref_en (bool const en);
#endif // CPU_AX

PRIVATE com_bfn_time_t com_bfn_get_time_diff (com_bfn_time_t const time_main, com_bfn_time_t const time_remote);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
#if CPU_AX
PRIVATE void INTRINSIC_ALWAYS_INLINE com_bfn_sync_intr_clr ()
{
    if (RCS_GPREG_EDG_IRQ_NOMASK_2_REG->value & COM_BFN_INTR_STAT)
        RCS_GPREG_EDG_IRQ_NOMASK_2_REG->value = COM_BFN_INTR_STAT;
}

PRIVATE void com_bfn_sync_intr_init ()
{
    com_isr_event (COM_BFN_SYNC_INTR, com_bfn_sync_handler, (void *)0);
    com_isr_interrupt_disable (COM_BFN_SYNC_INTR);
}

PRIVATE void com_bfn_main_set_pre_time (uint32_t const bfn_sync_time_upper, uint32_t const bfn_sync_time_lower)
{
    RCS_TIMER_GPREG->INC_PRE_REG0.value = bfn_sync_time_lower;
    RCS_TIMER_GPREG->INC_PRE_REG1.value = bfn_sync_time_upper;
}

PRIVATE void com_bfn_loop_set_pre_time (uint32_t const bfn_sync_time_low, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                        com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                        com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst])
{
    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        if (p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use)
        {
            for (int idx_comp = 0; idx_comp < cnt_comp; idx_comp++)
            {
                p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_inc_pre->value = bfn_sync_time_low;
            }
        }
    }
}

PRIVATE void com_bfn_loop_set_isync_ctrl (uint32_t const isync_ctrl, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                          com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                          com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst])
{
    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        if (p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use)
        {
            for (int idx_comp = 0; idx_comp < cnt_comp; idx_comp++)
            {
                p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_isync_ctrl->value = isync_ctrl;
            }
        }
    }
}

PRIVATE void com_bfn_loop_set_ten_ms_cnt (uint32_t const ten_ms_cnt, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                          com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                          com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst])
{
    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        if (p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use)
        {
            for (int idx_comp = 0; idx_comp < cnt_comp; idx_comp++)
            {
                p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_ten_ms_cnt->value = ten_ms_cnt;
            }
        }
    }
}

PRIVATE bool bfn_in_use (uint32_t const cnt_inst, uint32_t const current_inst, uint32_t const bfn_ant_mask)
{
    uint32_t bfn_inst_mask = 0;
    RT_ASSERT (bfn_ant_mask);
    RT_ASSERT (current_inst < cnt_inst);

    if (cnt_inst == 1)
    {
        return true;
    }
    else if (cnt_inst == 2)
    {
        bfn_inst_mask = 0xFF;
    }
    else if (cnt_inst == 4)
    {
        bfn_inst_mask = 0x0F;
    }
    else if (cnt_inst == 8)
    {
        bfn_inst_mask = 0x03;
    }

    bfn_inst_mask <<= (MAX_BFN_ANT / cnt_inst) * current_inst;
    return (bfn_ant_mask & bfn_inst_mask) ? true : false;
}

PRIVATE bool com_bfn_loop_chk_remote_time (com_bfn_cnt_low_t const time_main, uint32_t const cnt_comp, uint32_t const cnt_inst,
                                           com_bfn_remote_t const p_com_bfn_inst_tbl[][cnt_inst],
                                           com_bfn_cfg_t const p_com_bfn_cfg_tbl[cnt_inst])
{
    bool remote_mismatch = false;

    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        if (p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use)
        {
            for (int idx_comp = 0; idx_comp < cnt_comp; idx_comp++)
            {
                com_bfn_time_t const time_remote = {.value = p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_cnt_sync->value};

                if (time_main.value != time_remote.value)
                {
                    com_bfn_clnt_isync_ctrl_t *const p_isync_ctrl = p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_isync_ctrl;
                    com_bfn_time_t const time_diff_inc_pre = com_bfn_get_time_diff (time_main, time_remote);
                    remote_mismatch = true;
                    p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_inc_pre->value = time_diff_inc_pre.value;
                    FW_PRINT (FW_INFO, "BFN remote mismatch at 0x%08x, inst=%d, comp=%d", U32 (p_isync_ctrl), idx_inst, idx_comp);
                    FW_PRINT (FW_INFO, "BFN remote=0x%08x, main=0x%08X", time_remote.value, time_main.value);
                    FW_PRINT (FW_INFO, "BFN inc_pre_cnt=0x%08x", time_diff_inc_pre.value);
                }
                else
                {
                    p_com_bfn_inst_tbl[idx_comp][idx_inst].com_bfn_inc_pre->value = 0;
                }
            }
        }
    }

    return remote_mismatch;
}

PRIVATE void com_bfn_set_in_use (uint32_t const cnt_inst, uint32_t const ant_mask, com_bfn_cfg_t p_com_bfn_cfg_tbl[cnt_inst])
{
    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use = bfn_in_use (cnt_inst, idx_inst, ant_mask);
    }
}

PRIVATE void com_bfn_set_jesd_in_use (uint32_t const cnt_inst, uint32_t const jesd_mask, com_bfn_cfg_t p_com_bfn_cfg_tbl[cnt_inst])
{
    for (int idx_inst = 0; idx_inst < cnt_inst; idx_inst++)
    {
        p_com_bfn_cfg_tbl[idx_inst].com_bfn_in_use = (jesd_mask & (1 << idx_inst)) ? true : false;
    }
}

PRIVATE void com_bfn_remote_set_isync_ctrl (uint32_t const isync_ctrl)
{
    com_bfn_loop_set_isync_ctrl (isync_ctrl, COM_BFN_COMP_CNT (COM_BFN_INST2), COM_BFN_INST2, com_bfn_2inst_tbl, com_bfn_2inst_cfg);
    com_bfn_loop_set_isync_ctrl (isync_ctrl, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_4inst_tbl, com_bfn_4inst_cfg);
    com_bfn_loop_set_isync_ctrl (isync_ctrl, COM_BFN_COMP_CNT (COM_BFN_INST8), COM_BFN_INST8, com_bfn_8inst_tbl, com_bfn_8inst_cfg);
    com_bfn_loop_set_isync_ctrl (isync_ctrl, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_jesd_tbl, com_bfn_jesd_cfg);
}

PRIVATE void com_bfn_remote_set_pre_time (uint32_t const bfn_sync_time_low)
{
    com_bfn_loop_set_pre_time (bfn_sync_time_low, COM_BFN_COMP_CNT (COM_BFN_INST2), COM_BFN_INST2, com_bfn_2inst_tbl, com_bfn_2inst_cfg);
    com_bfn_loop_set_pre_time (bfn_sync_time_low, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_4inst_tbl, com_bfn_4inst_cfg);
    com_bfn_loop_set_pre_time (bfn_sync_time_low, COM_BFN_COMP_CNT (COM_BFN_INST8), COM_BFN_INST8, com_bfn_8inst_tbl, com_bfn_8inst_cfg);
    com_bfn_loop_set_pre_time (bfn_sync_time_low, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_jesd_tbl, com_bfn_jesd_cfg);
}

PRIVATE void com_bfn_remote_ten_ms_cnt (uint32_t const bfn_ten_ms_cnt)
{
    com_bfn_loop_set_ten_ms_cnt (bfn_ten_ms_cnt, COM_BFN_COMP_CNT (COM_BFN_INST2), COM_BFN_INST2, com_bfn_2inst_tbl, com_bfn_2inst_cfg);
    com_bfn_loop_set_ten_ms_cnt (bfn_ten_ms_cnt, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_4inst_tbl, com_bfn_4inst_cfg);
    com_bfn_loop_set_ten_ms_cnt (bfn_ten_ms_cnt, COM_BFN_COMP_CNT (COM_BFN_INST8), COM_BFN_INST8, com_bfn_8inst_tbl, com_bfn_8inst_cfg);
    com_bfn_loop_set_ten_ms_cnt (bfn_ten_ms_cnt, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_jesd_tbl, com_bfn_jesd_cfg);
}

PRIVATE void com_bfn_armed_clear ()
{
    com_bfn_main_set_pre_time (COM_BFN_INC_PRE_DEFAULT, COM_BFN_INC_PRE_DEFAULT);
    if (g_bfn_have_rmt)
    {
        com_bfn_remote_set_pre_time (COM_BFN_INC_PRE_DEFAULT);
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_INIT); // 0x2
    }
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INIT;
    if (g_bfn_have_rmt)
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CMD_INC_PRE); // 0x3
    }
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CMD;
    if (g_bfn_have_rmt)
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CLEAR);
    }
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CLEAR;
}

PRIVATE void com_bfn_soft_reset ()
{
    if (g_bfn_have_rmt)
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_RESET);
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_SOFT_RESET;
}

PRIVATE void com_bfn_remote_start ()
{
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    com_bfn_remote_ten_ms_cnt (g_bfn_cntl_total - 1);
    com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_INIT);
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INIT; // send ISYNC_TRIGGER
    g_bfn_rmt_started = true;
}

PRIVATE void com_bfn_set_ten_ms_cnt (uint32_t const bfn_ten_ms_cnt)
{
    if (g_bfn_have_rmt)
        com_bfn_remote_ten_ms_cnt (bfn_ten_ms_cnt);
    RCS_TIMER_GPREG->TEN_MS_CNT.value = bfn_ten_ms_cnt;
}

PRIVATE void com_bfn_arm (bool const load_syref)
{
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    if (load_syref)
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_INIT);
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INIT;
    if (load_syref) // do remote first then main, dont switch the seq
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_LOAD); // arm remote BFN
        INTRINSIC_BARRIER;
        RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_LOAD; // arm main BFN
    }
    else
    {
        com_bfn_remote_set_isync_ctrl (BFN_COM_ISYNC_CLEAR);
        RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    }
}

PRIVATE void com_bfn_sync_handler (void *p_arg)
{
    UNUSED (p_arg);
    if (g_bfn_is_ext_sync)
    {
        com_bfn_sysref_en (false);
        g_bfn_is_ext_sync = false;
        RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;

        // Disable interrupt
        com_isr_interrupt_disable (COM_BFN_SYNC_INTR);

        if ((g_bfn_rmt_check) && (g_bfn_have_rmt))
        {
            com_bfn_chk_adj_remote ();
        }
        com_bfn_armed_clear ();

        // Interrupt = edge2, 0x80000
        RCS_GPREG_EDG_IRQ_NOMASK_2_REG->value = COM_BFN_INTR_STAT;
        // FW_PRINT (FW_INFO, "--- edge2 intr no mask stat = 0x%08x", RCS_GPREG_EDG_IRQ_NOMASK_2_REG->value);
        com_bfn_sysref_en (true);
    }
}

PRIVATE com_bfn_cnt_t com_bfn_main_get_snapshot_time ()
{
    volatile com_bfn_cnt_t sync_time = {.value = 0};

    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CLEAR;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CAP;
    INTRINSIC_BARRIER; // this is needed
    sync_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
    sync_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CLEAR;

    return sync_time;
}

PRIVATE void inline com_bfn_sysref_en (bool const en)
{
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value = (en) ? COM_BFN_OVAL_SYSREF_EN : COM_BFN_OVAL_SYSREF_DIS;
}
#endif // CPU_AX

PRIVATE com_bfn_time_t com_bfn_get_time_diff (com_bfn_time_t const time_main, com_bfn_time_t const time_remote)
{
    com_bfn_time_t bfn_diff = {.value = 0};
    uint8_t frame_offset = 0;

    if (time_main.OFFSET < time_remote.OFFSET)
    {
        bfn_diff.OFFSET = g_bfn_cntl_total - time_remote.OFFSET + time_main.OFFSET;
        frame_offset -= 1;
    }
    else
    {
        bfn_diff.OFFSET = time_main.OFFSET - time_remote.OFFSET;
    }
    bfn_diff.FRAME_P0 = (time_main.FRAME_P0 - time_remote.FRAME_P0 + frame_offset);
    return bfn_diff;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
#if CPU_AX
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Check remote BFN, adjust if required.
 * @param [in]      none.
 * @return          bool: return true if has mismatch.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_bfn_chk_adj_remote ()
{
    bool remote_mismatch = false;
    com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CMD_CAP);
    INTRINSIC_BARRIER;
    com_bfn_cnt_t const time_main = com_bfn_main_get_snapshot_time ();
    remote_mismatch |= com_bfn_loop_chk_remote_time (time_main.CNT_LOW, COM_BFN_COMP_CNT (COM_BFN_INST2), COM_BFN_INST2, com_bfn_2inst_tbl,
                                                     com_bfn_2inst_cfg);
    remote_mismatch |= com_bfn_loop_chk_remote_time (time_main.CNT_LOW, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_4inst_tbl,
                                                     com_bfn_4inst_cfg);
    remote_mismatch |= com_bfn_loop_chk_remote_time (time_main.CNT_LOW, COM_BFN_COMP_CNT (COM_BFN_INST8), COM_BFN_INST8, com_bfn_8inst_tbl,
                                                     com_bfn_8inst_cfg);
    remote_mismatch |= com_bfn_loop_chk_remote_time (time_main.CNT_LOW, COM_BFN_COMP_CNT (COM_BFN_INST4), COM_BFN_INST4, com_bfn_jesd_tbl,
                                                     com_bfn_jesd_cfg);

    if (remote_mismatch)
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CMD_INIT);
        INTRINSIC_BARRIER;
        RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CMD; // 0xB0 for remote cmd 0x2
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CMD_INC_PRE);
        INTRINSIC_BARRIER;
        RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_CMD; // 0xB0 for remote cmd 0x3
        INTRINSIC_BARRIER;
        com_bfn_remote_set_isync_ctrl (BFN_COM_ISYNC_CLEAR);
    }
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    return remote_mismatch;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           BFN sync using sysref.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_time_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_sync (uint32_t const bfn_sync_time_upper, uint32_t const bfn_sync_time_lower)
{
    com_bfn_main_set_pre_time (bfn_sync_time_upper, bfn_sync_time_lower);
    com_bfn_remote_set_pre_time (bfn_sync_time_lower);
    com_bfn_arm (true);
    INTRINSIC_BARRIER;
    com_bfn_sysref_en (true);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read BFN sysref time.
 * @param [in]      none.
 * @return          uint64_t: sysref BFN time.
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t com_bfn_get_sysref_time ()
{
    volatile com_bfn_cnt_t time_sysref = {.value = 0};
    time_sysref.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL1_REG0.value;
    time_sysref.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL1_REG1.value;
    return time_sysref.value;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Adjust main and remote time
 * @param [in]      int32_t offset adjustment, positive number to increase offset and negative number to decrease offset
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_time_adjust (int32_t const offset_adj)
{
    int32_t const cnt = abs (offset_adj);
    int32_t idx = 0;

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    if (offset_adj > 0)
    {
        for (idx = 0; idx < cnt; idx++) { RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INC; }
    }
    else if (offset_adj < 0)
    {
        for (idx = 0; idx < cnt; idx++) { RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_DEC; }
    }
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set BFN antenna mask. Only allowed to call once.
 * @param [in]      antenna_mask: Antenna mask.
 * @param [in]      jesd_mask: JESD mask.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_set_ant_mask (uint32_t const antenna_mask, uint32_t const jesd_mask)
{
    RT_ASSERT (g_bfn_have_rmt == false); // only allow com_bfn_set_ant_mask to be called once only
    uint32_t const ant_msk = (antenna_mask & 0x0000FFFF);
    uint32_t const jesd_msk = (jesd_mask & 0x0000000F);
    g_bfn_have_rmt = ((ant_msk) || (jesd_msk)) ? true : false;
    // set in use
    com_bfn_set_in_use (COM_BFN_INST2, ant_msk, com_bfn_2inst_cfg);
    com_bfn_set_in_use (COM_BFN_INST4, ant_msk, com_bfn_4inst_cfg);
    com_bfn_set_in_use (COM_BFN_INST8, ant_msk, com_bfn_8inst_cfg);
    com_bfn_set_jesd_in_use (COM_BFN_INST4, jesd_msk, com_bfn_jesd_cfg);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Check whether remote mask is set.
 * @param [in]      none.
 * @return          true is remote is set, otherwise false.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_bfn_is_ant_mask_set ()
{
    return g_bfn_have_rmt;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           BFN initialization
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_init ()
{
    uint32_t const bfn_ext_src_sel = get_tf (ax_bfn_config_lut, 0, ext_src_sel);
    uint32_t const bfn_ext_gpio_sel = get_tf (ax_bfn_config_lut, 0, extsync_gpio_sel);
    g_bfn_rmt_check = get_tf (ax_bfn_config_lut, 0, bfn_rmt_chk_en);

    RT_ASSERT (g_bfn_cntl_total != COM_BFN_CNTL_INVALID);
    if (g_bfn_cntl_total == COM_BFN_1474_CNTL_TOTAL)
    {
        com_bfn_set_ten_ms_cnt (g_bfn_cntl_total - 1);
        INTRINSIC_BARRIER;
    }

    // cannot assign here, can only or
    g_bfn_oops_cfg |= (bfn_ext_src_sel << RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_SYSREFEN_BF_OFF);
    if (bfn_ext_src_sel & 0x2)
        g_bfn_oops_cfg |= (bfn_ext_gpio_sel << RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_EXTSYNC_GPIO_SEL_BF_OFF);

    com_bfn_sync_intr_init ();
    com_bfn_sysref_en (false);
    // Dont use com_bfn_remote_start here.

    if (g_bfn_have_rmt)
    {
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_INIT);
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INIT;
    INTRINSIC_BARRIER;

    if ((g_bfn_rmt_check) && (g_bfn_have_rmt))
    {
        com_bfn_chk_adj_remote ();
        com_bfn_armed_clear (); // always com_bfn_armed_clear after com_bfn_chk_adj_remote
    }
    else
        RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;

    if (g_bfn_have_rmt)
        g_bfn_rmt_started = true;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Reset BFN main time while it is running, no remote time involved
 * @param [in]      int32_t bfn_sync_time_high, new high count
 * @param [in]      int32_t bfn_sync_time_low, new low count
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_main_reset_time (uint32_t const bfn_sync_time_high,
                              uint32_t const bfn_sync_time_low) // todo: need this API, to be removed?
{
    com_bfn_main_set_pre_time (bfn_sync_time_high, bfn_sync_time_low);
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    RCS_TIMER_GPREG->ICTRL.value = 0x000001B2;
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_TS_CAP_BF_MSK;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Sync BFN time at boot time initialization.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_timecom_bfn_sync_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_sysref_sync (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low)
{
    g_bfn_is_ext_sync = true;
    com_bfn_sync_intr_clr ();
    com_isr_interrupt_enable (COM_BFN_SYNC_INTR);
    if ((g_bfn_have_rmt) && (!g_bfn_rmt_started))
        com_bfn_remote_start ();
    com_bfn_sync (bfn_sync_time_high, bfn_sync_time_low);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Sync BFN time at using software without sysref. Dont call this until have the full antenna mask.
 * @param [in]      bfn_sync_time_high: time high 32 bit.
 * @param [in]      bfn_sync_timecom_bfn_sync_low: time low 32 bit.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_soft_sync (uint32_t const bfn_sync_time_high, uint32_t const bfn_sync_time_low)
{
    g_bfn_is_ext_sync = false;
    com_bfn_sysref_en (false);
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CLEAR;
    com_bfn_main_set_pre_time (bfn_sync_time_high, bfn_sync_time_low);

    if (g_bfn_have_rmt)
    {
        com_bfn_remote_set_pre_time (bfn_sync_time_low);
        com_bfn_remote_start ();
    }
    else
        RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_INIT;

    if (g_bfn_have_rmt)
        com_bfn_remote_set_isync_ctrl (BFN_RMT_ISYNC_CMD_PRESET);

    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_MAIN_ISYNC_PRESET;

    INTRINSIC_BARRIER;
    if ((g_bfn_rmt_check) && (g_bfn_have_rmt))
    {
        com_bfn_chk_adj_remote ();
    }

    com_bfn_armed_clear ();
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           BFN shutdown.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_shutdown ()
{
    g_bfn_cntl_total = COM_BFN_CNTL_INVALID;
    g_bfn_have_rmt = false;
    g_bfn_oops_cfg = 0;
    g_bfn_rmt_started = false;
    memset (com_bfn_2inst_cfg, false, sizeof (com_bfn_cfg_t) * COM_BFN_INST2); // todo: use memset_s ??
    memset (com_bfn_4inst_cfg, false, sizeof (com_bfn_cfg_t) * COM_BFN_INST4);
    memset (com_bfn_8inst_cfg, false, sizeof (com_bfn_cfg_t) * COM_BFN_INST8);
    memset (com_bfn_jesd_cfg, false, sizeof (com_bfn_cfg_t) * COM_BFN_INST4);
    com_bfn_soft_reset ();
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set all remote time based on main time.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_self_sync ()
{
    if (g_bfn_have_rmt)
    {
        uint32_t const offset = (g_bfn_cntl_total == COM_BFN_1474_CNTL_TOTAL) ? BFN_SELFSYNC_OFFSET_1474 : BFN_SELFSYNC_OFFSET_983;
        ATOMIC_BEGIN;
        com_bfn_cnt_t const cnt_new = {.value = com_bfn_add_time_full (com_bfn_get_live_time_full (), offset)};
        com_bfn_soft_sync (cnt_new.CNT_HIGH.value, cnt_new.CNT_LOW.value);
        ATOMIC_END;
    }
}
#endif // CPU_AX

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set BFN clk freq and antenna mask. Called from TRX and CAL. Must be called before com_bfn_init. Only called once
 * @param [in]      drf_sel: drf clock select.
 * @param [in]      antenna_mask: antenna mask.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_bfn_set_clk_sel (e_sys_clk_t const drf_sel)
{
    RT_ASSERT (drf_sel <= e_CLK_1474M);
    g_bfn_cntl_total = (drf_sel == e_CLK_1474M) ? COM_BFN_1474_CNTL_TOTAL : COM_BFN_983_CNTL_TOTAL;
#if CPU_AX
    g_bfn_oops_cfg = ENUM2U32 (drf_sel) << RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_SYSREF_SEL_BF_OFF;
#endif // CPU_AX
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read live BFN time. For internal FW used only.
 * @param [in]      none.
 * @return          uint32_t: current bfn time, only low 32 bit count only.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t INTRINSIC_ALWAYS_INLINE com_bfn_get_live_time ()
{
    return RCS_TIMER_GPREG->BFN_LIVE_CNT_LO.value;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read live BFN time. For internal FW used only.
 * @param [in]      none.
 * @return          uint64_t: current bfn time, full 64 bit count
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t INTRINSIC_ALWAYS_INLINE com_bfn_get_live_time_full ()
{
    com_bfn_cnt_t full_cnt = {.CNT_LOW.value = RCS_TIMER_GPREG->BFN_LIVE_CNT_LO.value};
    full_cnt.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_LIVE_CNT_HI.value;
    return full_cnt.value;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add 2 BFN time, base time is partial BFN time.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint32_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_bfn_add_time (uint32_t const time_base, uint32_t const time_offset)
{
    return (uint32_t)com_bfn_add_time_full (time_base, time_offset);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add 2 BFN time, base time is full 64 bit.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint64_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint64_t com_bfn_add_time_full (uint64_t const time_base, uint32_t const time_offset)
{
    uint32_t offset_new = ((com_bfn_cnt_t)time_base).OFFSET + ((com_bfn_cnt_low_t)time_offset).OFFSET;
    com_bfn_cnt_t bfn_time_new = {.FRAME = ((com_bfn_cnt_t)time_base).FRAME + ((com_bfn_cnt_low_t)time_offset).FRAME_P0};

    if (offset_new >= g_bfn_cntl_total)
    {
        offset_new -= g_bfn_cntl_total;
        bfn_time_new.FRAME++;
    }

    bfn_time_new.OFFSET = offset_new;
    return bfn_time_new.value;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Subtract 2 BFN time.
 * @param [in]      time_base: com_bfn_time_t input time. Must be in BFN format.
 * @param [in]      time_offset: com_bfn_time_t offset. Must be in BFN format.
 * @return          uint32_t: new time, in BFN format.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_bfn_sub_time (uint32_t const time_base, uint32_t const time_offset)
{
    RT_ASSERT (g_bfn_cntl_total != COM_BFN_CNTL_INVALID);
    return com_bfn_get_time_diff ((com_bfn_cnt_low_t)time_base, (com_bfn_cnt_low_t)time_offset).value;
}
