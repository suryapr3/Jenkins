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
#include "com_bfn.h"
#include "com_event.h"
#include "com_msg_handler_utils.h"
#include "com_print.h"
#include "com_queue.h"
#include "com_timing.h"
#include "dl_req_msg.h"
#include "readback_msg.h"
#include "tx_msg_handler.h"
#include "com_shared_memory.h"
#include "com_fsm.h"
#include <stdbool.h>
#include <string.h>
#include <xtensa/config/core.h>
#include <xtensa/core-macros.h>
#include <xtensa/corebits.h>
#include <xtensa/xtruntime.h>

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
extern msg_hdlr_t tx_hdlr_lut[];

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

static void test_check_lead_time ()
{
    msg_hdlr_t msg_hdlr = {
        .opcode = 0, .p_msg_hdlr_f = NULL, .p_range_check_f = NULL, .ref_act_ts = 0, .set_up_ts = 0, .is_schedulable = false};
    uint32_t activation_timestamp = 139000;
    uint32_t t_lead_time = 27525;

    msg_hdlr.ref_act_ts = US_TO_BFN_TICKS (tx_hdlr_lut[9].ref_act_ts);
    msg_hdlr.set_up_ts = US_TO_BFN_TICKS (tx_hdlr_lut[9].set_up_ts);

    com_msg_check_lead_time (activation_timestamp, t_lead_time, &msg_hdlr);
    activation_timestamp = 58628;
    com_msg_check_lead_time (activation_timestamp, t_lead_time, &msg_hdlr);
}
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

int main (int argc, char **argv)
{
    FW_PRINT (FW_INFO, "tx_msg_handler_test");
    g_assertion_counter = 0;
    test_check_lead_time ();
    msg_t test_msg, read_test_msg;
    uint32_t read_test_msg_len = 0;

    FW_PRINT (FW_INFO, "**Scheduling Messages**");

    xthal_enable_interrupts ();
    com_event_init_events ();
    com_bfn_set_clk_sel (e_CLK_983M);

    com_fsm_init (e_FSM_TX);
    // Force Overall FSM to Booted state
    com_fsm_transition (e_FSM_TX, com_fsm_get_status (e_FSM_TX), e_EVENT_BOOT);

    int event_idx2 = com_event_new_event ();
    event_t *p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_exit_fun;
    strcpy ((char *)p_event2->context, "Exiting Event Loop ");

    dl_config_ant_grp_bf_t dl_config_msg;
    dl_config_msg.opcode = e_DL_CONFIG_ANT_GRP_OPCODE;
    dl_config_msg.timing = e_TS_TYPE_IMM_TIMESTAMP;
    dl_config_msg.ant_group_dl_ant_mask = 0xF;
    dl_config_msg.ant_group_dl_band_freq0 = 0xCDE;
    dl_config_msg.ant_group_dl_band_freq1 = 0xAAB;
    dl_config_msg.jesd_latency = 0xFED;
    dl_config_msg.vha_dl_latency = 0xEAB;
    // Force config message to be non schedulable for unit test
    tx_hdlr_lut[9].is_schedulable = false;
    test_msg.dl_config_ant_grp = dl_config_msg;
    com_msg_schedule_macro (&test_msg, tx_hdlr_lut, e_TX_QUEUE);

    warmup_bf_t warmup_msg;
    warmup_msg.opcode = e_WARMUP_OPCODE;

    warmup_msg.ul_quad_en_mask = 0;
    warmup_msg.dl_quad_en_mask = 1;
    test_msg.warmup = warmup_msg;

    // Warm up in AX core - so FSM fix for testing
    com_fsm_transition_run (e_FSM_TX);
    if (warmup_msg.dl_quad_en_mask)
    {
        com_fsm_transition_quadmask (e_FSM_TX, warmup_msg.dl_quad_en_mask, e_QUAD_EVENT_WARMUP);
    }

    dl_on_bf_t test_dl_on;
    test_dl_on.opcode = e_DL_ON_OPCODE;
    test_dl_on.timing = e_TS_TYPE_ABS_TIMESTAMP;
    test_dl_on.timestamp = 450000;
    test_dl_on.rb = 0;
    test_dl_on.quad_mask0 = 0x1;
    test_dl_on.quad_mask1 = 0;
    test_dl_on.quad_mask2 = 0;
    test_dl_on.quad_mask3 = 0;
    test_dl_on.power_ant0 = 0x0B;
    test_dl_on.power_ant1 = 0x0C;
    test_msg.dl_on = test_dl_on;
    com_msg_schedule_macro (&test_msg, tx_hdlr_lut, e_TX_QUEUE);

    dl_update_control_bf_t test_dl_upd;
    test_dl_upd.opcode = e_DL_UPDATE_CONTROL_OPCODE;
    test_dl_upd.timing = e_TS_TYPE_ABS_TIMESTAMP;
    test_dl_upd.timestamp = test_dl_on.timestamp + 100000;
    test_dl_upd.power_ant0 = 0x0D;
    test_dl_upd.power_ant1 = 0x0E;
    test_dl_upd.quad_mask0 = 0x1;
    test_dl_upd.quad_mask1 = 0;
    test_dl_upd.quad_mask2 = 0;
    test_dl_upd.quad_mask3 = 0;
    test_msg.dl_update_control = test_dl_upd;
    com_msg_schedule_macro (&test_msg, tx_hdlr_lut, e_TX_QUEUE);

    uint32_t curr_time = com_timing_get_current_bfn_time ();
    FW_PRINT (FW_INFO, "ref_index = %d,curr_time = %u ", 1, curr_time);
    com_msg_ref_timestamp_set (0x01, curr_time);

    test_dl_upd.opcode = e_DL_UPDATE_CONTROL_OPCODE;
    test_dl_upd.ref_index = 0x01;
    test_dl_upd.timing = e_TS_TYPE_REL_TIMESTAMP;
    test_dl_upd.rb = 0;
    test_dl_on.quad_mask0 = 0x1;
    test_dl_upd.quad_mask1 = 0;
    test_dl_upd.quad_mask2 = 0;
    test_dl_upd.quad_mask3 = 0;
    test_dl_upd.timestamp = 255000;
    test_dl_upd.power_ant0 = 0x0D;
    test_dl_upd.power_ant1 = 0x0E;
    test_msg.dl_update_control = test_dl_upd;
    com_msg_schedule_macro (&test_msg, tx_hdlr_lut, e_TX_QUEUE);

    dl_off_bf_t test_dl_off;
    test_dl_off.opcode = e_DL_OFF_OPCODE;
    test_dl_off.timestamp = 285000;
    test_dl_off.ref_index = 0x01;
    test_dl_off.timing = e_TS_TYPE_REL_TIMESTAMP;
    test_dl_off.mode = 0x02;
    test_dl_off.quad_mask0 = 0x1;
    test_dl_off.quad_mask1 = 0;
    test_dl_off.quad_mask2 = 0;
    test_dl_off.quad_mask3 = 0;
    test_msg.dl_off = test_dl_off;
    com_msg_schedule_macro (&test_msg, tx_hdlr_lut, e_TX_QUEUE);

    com_event_schedule_event (event_idx2, test_dl_off.timestamp + 20000);

    FW_PRINT (FW_INFO, "Scheduling events");

    com_event_event_loop ();

    FW_PRINT (FW_INFO, "TX Message handler Test Complete");

    return (0);
}
