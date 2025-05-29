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
 * @file    rx_msg_handler_test.c
 * @brief   Unit test code for rx_msg_handler
 * @details Unit test code for rx_msg_handler
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
#include "rx_msg_handler.h"
#include "ul_req_msg.h"
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
extern msg_hdlr_t rx_hdlr_lut[];

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

    msg_hdlr.ref_act_ts = rx_hdlr_lut[9].ref_act_ts;
    msg_hdlr.set_up_ts = rx_hdlr_lut[9].set_up_ts;

    com_msg_check_lead_time (activation_timestamp, t_lead_time, &msg_hdlr);
    activation_timestamp = 58628;
    com_msg_check_lead_time (activation_timestamp, t_lead_time, &msg_hdlr);
}
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

int main (int argc, char **argv)
{
    FW_PRINT (FW_INFO, "rx_msg_handler_test");

    g_assertion_counter = 0;
    test_check_lead_time ();

    FW_PRINT (FW_INFO, "**Scheduling Messages**");

    xthal_enable_interrupts ();
    com_event_init_events ();
    com_bfn_set_clk_sel (e_CLK_983M);

    com_fsm_init (e_FSM_RX);
    // Force Overall FSM to Booted state
    com_fsm_transition (e_FSM_RX, com_fsm_get_status (e_FSM_RX), e_EVENT_BOOT);

    int event_idx2 = com_event_new_event ();
    event_t *p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_exit_fun;
    strcpy ((char *)p_event2->context, "Exiting Event Loop ");

    msg_t test_msg;
    ul_config_ant_grp_bf_t ul_config_msg;
    ul_config_msg.opcode = e_UL_CONFIG_ANT_GRP_OPCODE;
    ul_config_msg.timestamp = 210000;
    ul_config_msg.timing = e_TS_TYPE_IMM_TIMESTAMP;
    ul_config_msg.ant_group_ul_ant_mask = 0x11F;
    ul_config_msg.ant_group_ul_band_freq0 = 0xCDE;
    ul_config_msg.ant_group_ul_band_freq1 = 0xAAB;
    ul_config_msg.drf_latency = 0xED;
    ul_config_msg.vha_ul_latency = 0xEAB;
    test_msg.ul_config_ant_grp = ul_config_msg;
    // Force config message to be non schedulable for unit test
    rx_hdlr_lut[9].is_schedulable = false;
    com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX_QUEUE);

    warmup_bf_t warmup_msg;
    warmup_msg.opcode = e_WARMUP_OPCODE;
    warmup_msg.ul_quad_en_mask = 0x7;
    warmup_msg.dl_quad_en_mask = 0;

    // Warm up in TX core - so FSM fix for testing

    com_fsm_transition_run (e_FSM_RX);
    if (warmup_msg.ul_quad_en_mask)
    {
        com_fsm_transition_quadmask (e_FSM_RX, warmup_msg.ul_quad_en_mask, e_QUAD_EVENT_WARMUP);
    }

    // Disabled  RB Locks won't work in Unit test Environment
    ul_on_bf_t test_ul_on;
    test_ul_on.opcode = e_UL_ON_OPCODE;
    test_ul_on.timing = e_TS_TYPE_ABS_TIMESTAMP;
    test_ul_on.timestamp = 550000;
    test_ul_on.rb = 0;
    test_ul_on.quad_mask0 = 0x3;
    test_ul_on.quad_mask1 = 0x4;
    test_ul_on.quad_mask2 = 0;
    test_ul_on.quad_mask3 = 0;
    test_ul_on.gain_ant0 = 0x0B;
    test_ul_on.gain_ant1 = 0x0C;
    test_msg.ul_on = test_ul_on;
    com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX_QUEUE);

    ul_update_control_bf_t test_ul_upd;
    test_ul_upd.opcode = e_UL_UPDATE_CONTROL_OPCODE;
    test_ul_upd.timing = e_TS_TYPE_ABS_TIMESTAMP;
    test_ul_upd.timestamp = test_ul_on.timestamp + 100000;
    test_ul_upd.quad_mask0 = 0x3;
    test_ul_upd.quad_mask1 = 0x4;
    test_ul_upd.quad_mask2 = 0;
    test_ul_upd.quad_mask3 = 0;
    test_ul_upd.gain_ant0 = 0x0D;
    test_ul_upd.gain_ant1 = 0x0E;
    test_msg.ul_update_control = test_ul_upd;
    com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX_QUEUE);

    uint32_t curr_time = com_timing_get_current_bfn_time ();
    FW_PRINT (FW_INFO, "ref_index = %d,curr_time = %u ", 1, curr_time);
    com_msg_ref_timestamp_set (0x01, curr_time);

    // Disabled  RB Locks won't work in Unit test Environment
    /*  test_ul_on.opcode = e_UL_ON_OPCODE;
      test_ul_on.ref_index = 0x01;
      test_ul_on.timing = e_TS_TYPE_REL_TIMESTAMP;
      test_ul_on.timestamp = 110000;
      test_ul_on.gain_ant0 = 0x0D;
      test_ul_on.gain_ant1 = 0x0E;
      test_msg.ul_on = test_ul_on;
      com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX0_QUEUE);

      // trying an unsupported opcode
      test_ul_on.opcode = e_DL_ON_OPCODE;
      test_ul_on.ref_index = 0x01;
      test_ul_on.timestamp = 110000;
      test_ul_on.gain_ant0 = 0x0D;
      test_ul_on.gain_ant1 = 0x0E;
      test_msg.ul_on = test_ul_on;
      com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX0_QUEUE);*/

    test_ul_upd.opcode = e_UL_UPDATE_CONTROL_OPCODE;
    test_ul_upd.ref_index = 0x01;
    test_ul_upd.timing = e_TS_TYPE_REL_TIMESTAMP;
    test_ul_upd.timestamp = test_ul_on.timestamp + 100000;
    test_ul_upd.quad_mask0 = 0x3;
    test_ul_upd.quad_mask1 = 0x4;
    test_ul_upd.quad_mask2 = 0;
    test_ul_upd.quad_mask3 = 0;
    test_ul_upd.gain_ant0 = 0x0D;
    test_ul_upd.gain_ant1 = 0x0E;
    test_msg.ul_update_control = test_ul_upd;
    com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX_QUEUE);

    ul_off_bf_t test_ul_off;
    test_ul_off.opcode = e_UL_OFF_OPCODE;
    test_ul_off.timestamp = 285000;
    test_ul_off.ref_index = 0x01;
    test_ul_off.timing = e_TS_TYPE_REL_TIMESTAMP;
    test_ul_off.quad_mask0 = 0x3;
    test_ul_off.quad_mask1 = 0x4;
    test_ul_off.quad_mask2 = 0;
    test_ul_off.quad_mask3 = 0;
    test_ul_off.mode = 0x02;
    test_msg.ul_off = test_ul_off;
    com_msg_schedule_macro (&test_msg, rx_hdlr_lut, e_RX_QUEUE);

    com_event_schedule_event (event_idx2, test_ul_off.timestamp + 10000);

    FW_PRINT (FW_INFO, "Scheduling events");

    com_event_event_loop ();

    FW_PRINT (FW_INFO, "RX Message handler Test Complete");

    return (0);
}
