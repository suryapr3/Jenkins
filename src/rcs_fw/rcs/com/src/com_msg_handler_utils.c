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
 * @file    com_msg_handler_utils.c
 * @brief   Common functions for handling timing and range checks on messages
 * @details Contains the APIs for for handling timing and range checks on messages
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_msg_handler_utils.h"
#include "com_assert.h"
#include "com_event.h"
#include "com_print.h"
#include "com_queue.h"
#include "com_timing.h"
#include "com_error.h"
#include "com_shared_memory.h"
#include "com_lock.h"
#include "rcs_gpreg.h"
#include "com_msg_timing.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xtensa/core-macros.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define T_LEAD_GRACE_PERIOD   (US_TO_BFN_TICKS (1))    // 1us
#define T_LEAD_MAX            (MS_TO_BFN_TICKS (1250)) // 1.25s
#define SCHED_OVERHEAD_OFFSET (US_TO_BFN_TICKS (4))    // 4us
#define NR_OF_REFERENCES      (16)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static uint32_t ref_timestamps[NR_OF_REFERENCES];
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static uint32_t com_msg_timingstamp_rel2abs_calc (uint32_t const ref_id, uint32_t const msg_ts_offset);
static void com_msg_timingstamp_rel2abs (msg_t *const p_msg);
static bool com_msg_is_max_lead_time_violation (uint32_t const t_lead_act);
static bool com_msg_is_min_lead_time_violation (uint32_t const t_lead_act, uint32_t const t_lead_min);
static bool com_msg_is_direct_execution (uint32_t const t_ts_lead_start);
static uint32_t com_msg_get_activation_timestamp (msg_t const *const p_msg);
static uint32_t com_msg_timings_get_lead_time (msg_hdlr_t const *msg_hdlr);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           calculates absolute time from ref_id and time offset
 * @param [in]      ref_id , time offset
 * @return          absolute time
 */

static uint32_t com_msg_timingstamp_rel2abs_calc (uint32_t const ref_id, uint32_t const msg_ts_offset)
{
    return (ref_timestamps[ref_id] + msg_ts_offset);
}

/**
 * @brief           relative to absolute time conversion
 * @param [in]      message
 * @return          absolute time
 */

static void com_msg_timingstamp_rel2abs (msg_t *const p_msg)
{
    if (p_msg->dl_config_ant_grp.timing == e_TS_TYPE_REL_TIMESTAMP)
    {
        p_msg->dl_config_ant_grp.timestamp =
            com_msg_timingstamp_rel2abs_calc (p_msg->dl_config_ant_grp.ref_index, p_msg->dl_config_ant_grp.timestamp);
    }
}

/**
 * @brief           checks for max lead time violation
 * @param [in]      lead time
 * @return          status -true if max lead time requirement is not met
 */

static bool com_msg_is_max_lead_time_violation (uint32_t const t_lead_act)
{
    uint32_t const t_lead_max = T_LEAD_MAX;
    bool const ret = !com_timing_is_bfn1_earlier_bfn2 (t_lead_act, t_lead_max);

    if (ret)
    {
        FW_PRINT (FW_INFO, "t_lead_max: %u", t_lead_max);
        FW_PRINT (FW_INFO, "t_lead_act: %u", t_lead_act);
        FW_PRINT (FW_INFO, "violation: %d", t_lead_act - t_lead_max);
        FW_PRINT (FW_WARN, "Maximum lead time violation!");
    }

    return ret;
}

/**
 * @brief           checks for minimum lead time violation
 * @param [in]      lead time and min lead time
 * @return          status -true if min lead time requirement is not met
 */
static bool com_msg_is_min_lead_time_violation (uint32_t const t_lead_act, uint32_t const t_lead_min)
{
    bool const ret = com_timing_is_bfn1_earlier_bfn2 (t_lead_act, t_lead_min);

    if (ret)
    {
        FW_PRINT (FW_INFO, "t_lead_min: %u", t_lead_min);
        FW_PRINT (FW_INFO, "t_lead_act: %u", t_lead_act);
        FW_PRINT (FW_INFO, "violation: %d", t_lead_act - t_lead_min);
        FW_PRINT (FW_WARN, "Minimum lead time violation!");
    }

    return ret;
}
/**
 * @brief           checks if message is intended for immediate or scheduled execution
 * @param [in]      lead time
 * @return          status - true for immediate/ false for scheduled
 */

static bool com_msg_is_direct_execution (uint32_t const t_ts_lead_start)
{
    uint32_t const lt = com_timing_get_current_bfn_time ();
    bool const ret = com_timing_is_bfn1_earlier_bfn2 (t_ts_lead_start, lt + SCHED_OVERHEAD_OFFSET);

    FW_PRINT (FW_INFO, "Direct activation threshold: %u, now: %u", t_ts_lead_start - SCHED_OVERHEAD_OFFSET, lt);

    if (ret)
    {
        FW_PRINT (FW_INFO, "Immediate execution.");
    }
    else
    {
        FW_PRINT (FW_INFO, "No immediate execution.");
    }

    return ret;
}

/**
 * @brief           returns timestamp field from the message
 * @param [in]      pointer to message
 * @return          timestamp field in the message.
 */

static uint32_t com_msg_get_activation_timestamp (msg_t const *const p_msg)
{
    return (p_msg->dl_config_ant_grp.timestamp);
}

/**
 * @brief           returns lead time
 * @param [in]      pointer to message handler
 * @return          total lead time from ref LUT
 */

static uint32_t com_msg_timings_get_lead_time (msg_hdlr_t const *msg_hdlr)
{
    return (CALC_LEAD_TIME (msg_hdlr->set_up_ts, msg_hdlr->ref_act_ts));
}

/**
 * @brief           returns opcode field from the message
 * @param [in]      pointer to message
 * @return          opcode field in the message.
 */
uint32_t com_msg_get_opcode (msg_t const *const p_msg)
{
    return (p_msg->dl_config_ant_grp.opcode);
}

/**
 * @brief           retrieves internal timings and callback functions from LUT
 * @param [in]      opcode, pointer to ref LUT and lut length
 * @return          values from LUT
 */
msg_hdlr_t const *com_msg_init_handler (uint32_t opcode, msg_hdlr_t *msg_hdlr_lut)
{
    int hdlr_idx = 0;
    int hdlr_opcode = 0;
    do
    {
        hdlr_opcode = msg_hdlr_lut[hdlr_idx].opcode;
        if (opcode == hdlr_opcode)
        {
            return &msg_hdlr_lut[hdlr_idx];
        }
        hdlr_idx++;
    } while( hdlr_opcode );

    return NULL;
}

/**
 * @brief           create a delayed event structure to run the message handler.
 * @param [in]      p_msg, pointer to the message.
 * @param [in]      handler_f, function to call to handle the message.
 * @return          event index.
 */

static int com_msg_create_event(msg_t *const p_msg, msg_hdlr_func_t handler_f )
{
    int msg_event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (msg_event_idx);
    p_event->p_event_f = handler_f;
    *(msg_t *)p_event->context = *p_msg;
    p_event->priority = e_EVENT_PRIORITY_LOW;

    return msg_event_idx;
}


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           initializes reference timestamp LUT
 * @param [in]      none
 * @return          none
 */
void com_msg_timestamp_init ()
{
    memset (ref_timestamps, 0, sizeof (ref_timestamps));
}

/**
 * @brief           sets the time ref_time stamp
 * @param [in]      ref_id , time offset
 * @return          absolute time
 */

void com_msg_ref_timestamp_set (uint32_t const ref_id, uint32_t const new_ref)
{
    ref_timestamps[ref_id] = new_ref;
}

/**
 * @brief           Checks if the lead time passes the min ,max and direct execution thresholds
 * @param [in]      activation_timestamp, lead time and message handler struct which holds LUT values
 * @return          status -error / direct execution/ schedulable
 */

uint32_t com_msg_check_lead_time (uint32_t activation_timestamp, uint32_t t_lead_time, msg_hdlr_t const *msg_hdlr)
{
    uint32_t result = 0;
    uint32_t const t_lead_ref = t_lead_time - T_LEAD_GRACE_PERIOD;
    uint32_t const t_ts_activation = activation_timestamp;
    uint32_t const t_ts_lead_start = t_ts_activation - t_lead_time;
    uint32_t const t_ts_reception = com_timing_get_current_bfn_time ();
    uint32_t const t_lead_act = t_ts_activation - t_ts_reception;

    if (com_msg_is_max_lead_time_violation (t_lead_act)) // actual lead time span > plausible time span
    {
        FW_PRINT (FW_INFO, "t_ts_reception = %d, t_ts_activation = %d", t_ts_reception, t_ts_activation);
        result |= e_ERR_MAX_LEAD_TIME_VIOLATION;

        FW_SEND_ERR_RB (e_MSG_TIMING_ERR, e_MSG_MAX_LEAD_TIME_ERR, msg_hdlr->opcode, t_ts_reception, t_ts_activation, t_lead_act,
                        T_LEAD_MAX, t_lead_act - T_LEAD_MAX);
    }
    else if (com_msg_is_min_lead_time_violation (t_lead_act, msg_hdlr->set_up_ts)) // actual lead time span < internal setup time span
    {
        FW_PRINT (FW_INFO, "t_ts_reception = %d, t_ts_activation = %d", t_ts_reception, t_ts_activation);
        result |= e_ERR_INTERNAL_SETUP_TIME_VIOLATION;
        FW_SEND_ERR_RB (e_MSG_TIMING_ERR, e_MSG_MIN_LEAD_TIME_ERR, msg_hdlr->opcode, t_ts_reception, t_ts_activation, t_lead_act,
                        msg_hdlr->set_up_ts, t_lead_act - msg_hdlr->set_up_ts);
    }
    else if (com_msg_is_min_lead_time_violation (t_lead_act, t_lead_ref)) // lead time violated by more than T_LEAD_GRACE_PERIOD
    {
        FW_PRINT (FW_INFO, "t_ts_reception = %d, t_ts_activation = %d", t_ts_reception, t_ts_activation);
        result |= e_ERR_MIN_LEAD_TIME_VIOLATION | e_IMMEDIATE_EXEC;
    }
    else if (com_msg_is_direct_execution (t_ts_lead_start)) // not enough time to schedule macro at begin of lead time
    {
        result |= e_IMMEDIATE_EXEC;
    }
    else // schedule macro at begin of lead time
    {
        FW_PRINT (FW_DEBUG, "Lead time observed, margin: %d", t_lead_act - t_lead_ref);
        result |= e_SCHEDULED;
    }
    return result;
}

/**
 * @brief           Schedules the macro after checking for range and lead time considerations
 * @param [in]      message , reference LUT and LUT length
 * @return          status of scheduling.
 */
uint32_t com_msg_schedule_macro (msg_t *const p_msg, msg_hdlr_t *msg_hdlr_lut, e_queue_type_t queue_id)
{
    uint32_t const opcode = com_msg_get_opcode (p_msg);

    // message handler event initialization and call back function
    msg_hdlr_t const *msg_hdlr = com_msg_init_handler (opcode, msg_hdlr_lut);

    if (msg_hdlr == NULL)
    {
        FW_PRINT (FW_ERR, "Unsupported Opcode %d ", opcode);
        FW_SEND_ERR_RB (e_INVALID_OPCODE_ERR, opcode, queue_id);
        return 0;
    }

    // Range check based on message type
    if (msg_hdlr->p_range_check_f != NULL)
    {
        msg_hdlr->p_range_check_f (p_msg);
    }

    com_msg_timingstamp_rel2abs (p_msg);

    uint32_t activation_timestamp = com_msg_get_activation_timestamp (p_msg); // in BFN
    uint32_t lead_time = com_msg_timings_get_lead_time (msg_hdlr);
    uint32_t const t_lead_start = activation_timestamp - lead_time;

    uint32_t result = 0;

    ATOMIC_BEGIN
    if (msg_hdlr->is_schedulable)
    {
        if (p_msg->dl_config_ant_grp.timing == e_TS_TYPE_IMM_TIMESTAMP)
        {
            result = e_IMMEDIATE_EXEC;
        }
        else
        {
            result = com_msg_check_lead_time (activation_timestamp, lead_time, msg_hdlr);
        }
    }
    else
    {
        msg_hdlr->p_msg_hdlr_f (p_msg);
    }

    if (e_SCHEDULED & result)
    {
        FW_PRINT (FW_NOTE, "[%d]Schedulable.at begin of lead time, MacroActivation - MacroTS: %u - %u ", com_timing_get_current_bfn_time (),
                  t_lead_start, activation_timestamp);
        int const msg_event_idx = com_msg_create_event( p_msg, msg_hdlr->p_msg_hdlr_f );
        com_event_schedule_event (msg_event_idx, t_lead_start);
    }
    else if (e_IMMEDIATE_EXEC & result)
    {
        FW_PRINT (FW_NOTE, "[%d]SCHEDULABLE, already within lead time, immediate execution, MacroActivation - MacroTS: %u - %u ",
                  com_timing_get_current_bfn_time (), t_lead_start, activation_timestamp);
        int const msg_event_idx = com_msg_create_event( p_msg, msg_hdlr->p_msg_hdlr_f );
        com_event_execute_immediate_event (msg_event_idx);
    }
    ATOMIC_END
    return (result);
}

/**
 * @brief           sends readback message
 * @param [in]      message , length of message in words
 * @return          none
 */
void com_msg_send_readback (msg_t *const msg, const uint32_t msg_len_word)
{
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_RB_QUEUE);

    com_lock_acquire (e_LOCK_RB_MSG);
    com_queue_insert (p_msg_queue, msg, msg_len_word);
    com_lock_release (e_LOCK_RB_MSG);
    com_mb_isr_trigger ((e_com_int_mb_sel_t)e_RB_QUEUE_MB_IRQ, 0xBEEF);
}

/**
 * @brief           initializes the message mailbox ISRs and enables the corresponding interrupt
 * @param [in]      pointer to msg irq LUT and lut length
 * @return          none
 */
void com_msg_init_mb_irq (msg_irq_hdlr_map_t *msg_irq_hdlr_map, uint32_t lut_length)
{
    for (int i = 0; i < lut_length; i++)
    {
        uint32_t irq_num = msg_irq_hdlr_map[i].msg_mb_irq + e_EXT_TO_RCS_MB_INT0_IRQ;
        com_isr_event (irq_num, msg_irq_hdlr_map[i].msg_isr_handler, (void *)0);
        com_isr_interrupt_enable (irq_num);
    }
}

