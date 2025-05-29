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
 * @file    com_error.c
 * @brief   Error Message Creation
 * @details Create Error Messages
 */
#include "com_assert.h"
#include "com_print.h"
#include "com_msgs_enum.h"
#include "readback_msg.h"
#include "com_queue_def.h"
#include "com_shared_memory.h"
#include "com_queue.h"
#include "rcs_gpreg.h"
#include "com_definitions.h"
#include "com_error.h"
#include "com_timing.h"
#include "com_msg_handler_utils.h"
#include <string.h>

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
#define ERROR_DATA_LEN_MAX 13

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

static void com_send_error_msg (e_error_type_t error_level, e_error_code_type_t error_code, e_reason_code_type_t reason_code,
                                uint32_t *error_data, uint32_t error_data_len)
{
    msg_t rb_msg;
    memset (&rb_msg.error_readback, 0, sizeof (error_readback_bf_t));
    rb_msg.error_readback.opcode = e_RB_ERR_OPCODE;
    rb_msg.error_readback.src = RCS_CPU;
    rb_msg.error_readback.level = error_level;
    rb_msg.error_readback.error_code = error_code;
    rb_msg.error_readback.reason_code = reason_code;
    rb_msg.error_readback.timestamp = com_timing_get_current_bfn_time ();
    RT_ASSERT (error_data_len <= ERROR_DATA_LEN_MAX); // maximum length of Error data array
    memcpy (&rb_msg.error_readback.value[3], error_data, LEN_IN_BYTE (error_data_len));
    com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (error_readback_bf_t)));
}
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           sends error message for invalid opcode
 * @param [in]      opcode and queue id which contains the opcode
 * @return          void.
 */
void com_send_rb_e_INVALID_OPCODE_ERR (uint32_t opcode, uint32_t queue_id)
{
    uint32_t error_data_len = 2;
    uint32_t error_data[error_data_len];
    error_data[0] = opcode;
    error_data[1] = queue_id;
    com_send_error_msg (e_ERROR, e_INVALID_OPCODE_ERR, e_REASON_CODE_NA, error_data, error_data_len);
}

/**
 * @brief           sends message timing errors.
 * @param [in]      reason code, opcode of the msg, variable args, data length
 * @return          void.
 */

void com_send_rb_e_MSG_TIMING_ERR (e_reason_code_type_t reason_code, uint32_t opcode, uint32_t arg1, uint32_t arg2, uint32_t arg3,
                                   uint32_t arg4, uint32_t arg5)
{
    uint32_t error_data_len = 6;
    uint32_t error_data[error_data_len];
    error_data[0] = opcode;
    error_data[1] = arg1;
    error_data[2] = arg2;
    error_data[3] = arg3;
    error_data[4] = arg4;
    error_data[5] = arg5;
    com_send_error_msg (e_ERROR, e_MSG_TIMING_ERR, reason_code, error_data,
                        error_data_len); // do we need different error sev based on reason code ?
}

/**
 * @brief           sends exception errors.
 * @param [in]      reason code, cause , frame_pc, addr , frame_ps(processor state), frame_a0,frame_a2,frame_a3, frame_a4, frame_a5
 * @return          void.
 */

void com_send_rb_e_EXCEPTION_ERR (e_reason_code_type_t reason_code, uint32_t cause, uint32_t frame_pc, uint32_t addr, uint32_t frame_ps,
                                  uint32_t frame_a0, uint32_t frame_a2, uint32_t frame_a3, uint32_t frame_a4, uint32_t frame_a5)
{
    uint32_t error_data_len = 10;
    uint32_t error_data[error_data_len];
    error_data[0] = cause;
    error_data[1] = frame_pc;
    error_data[2] = addr;
    error_data[3] = frame_ps;
    error_data[4] = frame_a0;
    error_data[5] = frame_a2;
    error_data[6] = frame_a3;
    error_data[7] = frame_a4;
    error_data[8] = frame_a5;
    error_data[9] = error_data_len;
    com_send_error_msg (e_ERROR, e_EXCEPTION_ERR, reason_code, error_data, error_data_len);
}

/**
 * @brief           sends event handler errors.
 * @param [in]      reason code,event id, current event state(if applicable)and expected event state (if applicable)
 * @return          void.
 */
void com_send_rb_e_EVENT_HANDLER_ERR (e_reason_code_type_t reason_code, uint32_t event_id, uint32_t arg1, uint32_t arg2)
{
    uint32_t error_data_len = 3;
    uint32_t error_data[error_data_len];
    error_data[0] = event_id;
    error_data[1] = arg1;
    error_data[2] = arg2;
    com_send_error_msg (e_ERROR, e_EVENT_HANDLER_ERR, reason_code, error_data, error_data_len);
}

/**
 * @brief           sends default interrupt handler errors.
 * @param [in]      reason code,interrupt id
 * @return          void.
 */
void com_send_rb_e_IRQ_ERR (e_reason_code_type_t reason_code, uint32_t interrupt_id)
{
    uint32_t error_data_len = 1;
    uint32_t error_data[error_data_len];
    error_data[0] = interrupt_id;
    com_send_error_msg (e_ERROR, e_IRQ_ERR, reason_code, error_data, error_data_len);
}

/**
 * @brief           sends FSM transition error
 * @param [in]      current FSM state , FSM event
 * @return          void.
 */
void com_send_rb_e_FSM_TRANSITION_ERR (e_reason_code_type_t reason_code, e_fsm_type_t fsm_id, e_fsm_state_type_t curr_state,
                                       e_fsm_event_type_t fsm_event)
{
    uint32_t error_data_len = 3;
    uint32_t error_data[error_data_len];
    error_data[0] = fsm_id;
    error_data[1] = curr_state;
    error_data[2] = fsm_event;
    com_send_error_msg (e_ERROR, e_FSM_TRANSITION_ERR, reason_code, error_data, error_data_len);
}

/**
 * @brief           sends Quad FSM transition error
 * @param [in]      current quad FSM state , quad FSM event
 * @return          void.
 */
void com_send_rb_e_QUAD_FSM_TRANSITION_ERR (e_reason_code_type_t reason_code, e_fsm_type_t fsm_id, e_fsm_quad_state_type_t curr_state,
                                            e_fsm_quad_event_type_t fsm_event, e_quad_id_t quad_id)
{
    uint32_t error_data_len = 4;
    uint32_t error_data[error_data_len];
    error_data[0] = fsm_id;
    error_data[1] = curr_state;
    error_data[2] = fsm_event;
    error_data[3] = quad_id;
    com_send_error_msg (e_ERROR, e_QUAD_FSM_TRANSITION_ERR, reason_code, error_data, error_data_len);
}

/**
 * @brief           sends error in case bootup error happens
 * @param [in]      cpu index of which error happens, plus its current status
 * @return          void.
 */
void com_send_rb_e_BOOT_ERR (e_reason_code_type_t reason_code, uint32_t cpu_idx, uint32_t cpu_status)
{
    uint32_t error_data_len = 2;
    uint32_t error_data[error_data_len];
    error_data[0] = cpu_idx;
    error_data[1] = cpu_status;
    com_send_error_msg (e_ERROR, e_BOOT_ERR, reason_code, error_data, error_data_len);
}


/**
 * @brief           send Config Message Error
 * @param [in]      reason code, opcode of the message and additional variable argument
 * @return          void.
 */
void com_send_rb_e_CONFIG_MSG_ERR (e_reason_code_type_t reason_code, uint32_t opcode, uint32_t arg1)
{
    uint32_t error_data_len = 2;
    uint32_t error_data[error_data_len];
    error_data[0] = opcode;
    error_data[1] = arg1;
    com_send_error_msg (e_ERROR, e_CONFIG_MSG_ERR, reason_code, error_data, error_data_len);
}
