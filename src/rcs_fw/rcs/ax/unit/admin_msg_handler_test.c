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
 * @file    tx_msg_handler_test.c
 * @brief   Unit test code for tx_msg_handler
 * @details Unit test code for tx_msg_handler
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_event.h"
#include "com_msg_handler_utils.h"
#include "com_print.h"
#include "com_queue.h"
#include "com_timing.h"
#include "com_bfn.h"
#include "admin_msg.h"
#include "readback_msg.h"
#include "admin_msg_handler.h"
#include "com_shared_memory.h"
#include <stdbool.h>
#include <string.h>
#include <xtensa/config/core.h>
#include <xtensa/core-macros.h>
#include <xtensa/corebits.h>
#include <xtensa/xtruntime.h>
#include "ax_jesd_config.h"
#include "ax_rx_msg_handler.h"
#include "ax_tx_msg_handler.h"
#include "com_rf_def.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern msg_hdlr_t admin_hdlr_lut[];
extern msg_hdlr_t ax_rx_hdlr_lut[];
extern msg_hdlr_t ax_tx_hdlr_lut[];
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void event_exit_fun (void *data)
{
    char const *const fmt = (char *)data;
    FW_PRINT (FW_INFO, fmt, xthal_get_ccount ());
    com_event_exit_event_loop ();
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    FW_PRINT (FW_INFO, "admin_msg_handler_test");
    g_assertion_counter = 0;

    msg_t test_msg, test_tx_msg, read_test_msg;
    uint32_t read_test_msg_len = 0;

    FW_PRINT (FW_INFO, "**Scheduling Messages**");

    xthal_enable_interrupts ();
    com_event_init_events ();

    int event_idx2 = com_event_new_event ();
    event_t *p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_exit_fun;
    strcpy ((char *)p_event2->context, "Exiting Event Loop ");
    com_bfn_set_clk_sel (e_CLK_983M);
    // msg_t test_msg;
    ul_config_ant_grp_bf_t ul_config_msg;
    ul_config_msg.opcode = e_UL_CONFIG_ANT_GRP_OPCODE;
    ul_config_msg.timestamp = 210000;
    ul_config_msg.timing = e_TS_TYPE_IMM_TIMESTAMP;
    ul_config_msg.ant_group_ul_ant_mask = 0x000F;
    ul_config_msg.ant_group_ul_band_freq0 = 0xCDE;
    ul_config_msg.ant_group_ul_band_freq1 = 0xAAB;
    ul_config_msg.drf_latency = 0xED;
    ul_config_msg.vha_ul_latency = 0xEAB;
    ul_config_msg.jesd_ul_idx = 25;
    ul_config_msg.q0_j = 0;
    ul_config_msg.q1_j = 1;
    ul_config_msg.q2_j = 2;
    ul_config_msg.q3_j = 3;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_msg_schedule_macro (&test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);

    ul_config_msg.ant_group_ul_ant_mask = 0x0010;
    ul_config_msg.jesd_ul_idx = 20;
    ul_config_msg.q0_j = 1;
    ul_config_msg.q1_j = 2;
    ul_config_msg.q2_j = 2;
    ul_config_msg.q3_j = 1;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_msg_schedule_macro (&test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);

    ul_config_msg.ant_group_ul_ant_mask = 0x0100;
    ul_config_msg.jesd_ul_idx = 12;
    ul_config_msg.q0_j = 3;
    ul_config_msg.q1_j = 2;
    ul_config_msg.q2_j = 2;
    ul_config_msg.q3_j = 1;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_msg_schedule_macro (&test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);

    ul_config_msg.ant_group_ul_ant_mask = 0x1000;
    ul_config_msg.jesd_ul_idx = 13;
    ul_config_msg.q0_j = 3;
    ul_config_msg.q1_j = 2;
    ul_config_msg.q2_j = 2;
    ul_config_msg.q3_j = 1;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_msg_schedule_macro (&test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);

    ul_config_msg.ant_group_ul_ant_mask = 0x0001;
    ul_config_msg.jesd_ul_idx = 25;
    ul_config_msg.q0_j = 3;
    ul_config_msg.q1_j = 2;
    ul_config_msg.q2_j = 2;
    ul_config_msg.q3_j = 1;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_msg_schedule_macro (&test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);

    //    warmup_bf_t warmup_msg;
    //    warmup_msg.opcode = e_WARMUP_OPCODE;
    //
    //    warmup_msg.ul_quad_en_mask = 1;
    //    warmup_msg.dl_quad_en_mask = 0;
    //    test_msg.warmup = warmup_msg;
    //    com_msg_schedule_macro (&test_msg, admin_hdlr_lut, e_NUM_UL_QUEUE_MSGS, e_RX_QUEUE);

    dl_config_ant_grp_bf_t dl_config_msg;
    dl_config_msg.opcode = e_DL_CONFIG_ANT_GRP_OPCODE;
    ul_config_msg.timestamp = 210000;
    dl_config_msg.timing = e_TS_TYPE_IMM_TIMESTAMP;
    dl_config_msg.ant_group_dl_ant_mask = 0x000F;
    dl_config_msg.ant_group_dl_band_freq0 = 0xCDE;
    dl_config_msg.ant_group_dl_band_freq1 = 0xAAB;
    dl_config_msg.jesd_latency = 0xFED;
    dl_config_msg.vha_dl_latency = 0xEAB;

    dl_config_msg.jesd_dl_idx = 25;
    dl_config_msg.q0_j = 0;
    dl_config_msg.q1_j = 1;
    dl_config_msg.q2_j = 2;
    dl_config_msg.q3_j = 3;
    test_tx_msg.dl_config_ant_grp = dl_config_msg;

    com_msg_schedule_macro (&test_tx_msg, ax_tx_hdlr_lut, e_TX_QUEUE);

    dl_config_msg.ant_group_dl_ant_mask = 0x0010;
    dl_config_msg.jesd_dl_idx = 20;
    dl_config_msg.q0_j = 1;
    dl_config_msg.q1_j = 2;
    dl_config_msg.q2_j = 2;
    dl_config_msg.q3_j = 1;
    test_tx_msg.dl_config_ant_grp = dl_config_msg;
    com_msg_schedule_macro (&test_tx_msg, ax_tx_hdlr_lut, e_TX_QUEUE);

    dl_config_msg.ant_group_dl_ant_mask = 0x0100;
    dl_config_msg.jesd_dl_idx = 13;
    dl_config_msg.q0_j = 1;
    dl_config_msg.q1_j = 2;
    dl_config_msg.q2_j = 1;
    dl_config_msg.q3_j = 1;
    test_tx_msg.dl_config_ant_grp = dl_config_msg;
    com_msg_schedule_macro (&test_tx_msg, ax_tx_hdlr_lut, e_TX_QUEUE);

    dl_config_msg.ant_group_dl_ant_mask = 0x1000;
    dl_config_msg.jesd_dl_idx = 4;
    dl_config_msg.q0_j = 1;
    dl_config_msg.q1_j = 2;
    dl_config_msg.q2_j = 2;
    dl_config_msg.q3_j = 3;
    test_tx_msg.dl_config_ant_grp = dl_config_msg;
    com_msg_schedule_macro (&test_tx_msg, ax_tx_hdlr_lut, e_TX_QUEUE);

    dl_config_msg.ant_group_dl_ant_mask = 0x1000;
    dl_config_msg.jesd_dl_idx = 4;
    dl_config_msg.q0_j = 1;
    dl_config_msg.q1_j = 2;
    dl_config_msg.q2_j = 2;
    dl_config_msg.q3_j = 0;
    test_tx_msg.dl_config_ant_grp = dl_config_msg;
    com_msg_schedule_macro (&test_tx_msg, ax_tx_hdlr_lut, e_TX_QUEUE);

    //    warmup_bf_t warmup_msg;
    //    warmup_msg.opcode = e_WARMUP_OPCODE;
    //
    //    warmup_msg.ul_quad_en_mask = 0;
    //    warmup_msg.dl_quad_en_mask = 1;
    //    test_msg.warmup = warmup_msg;
    //    com_msg_schedule_macro (&test_msg, admin_hdlr_lut, e_NUM_DL_QUEUE_MSGS, e_TX_QUEUE);

    com_event_schedule_event (event_idx2, 10000);

    FW_PRINT (FW_INFO, "Scheduling events");

    com_event_event_loop ();

    FW_PRINT (FW_INFO, "ADMIN Message handler Test Complete");

    return (0);
}
