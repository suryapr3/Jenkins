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
#ifndef COMMON_ERROR_H
#define COMMON_ERROR_H

#include "com_queue_def.h"
#include "com_msgs_enum.h"
#include "com_print.h"
#include "com_fsm_def.h"
#include <stdbool.h>
#include <stdint.h>

#define MACRO_CREATOR(func, err_code) func##err_code
#define FW_SEND_ERR_RB(code, ...)                         \
    do {                                                  \
        MACRO_CREATOR (com_send_rb_, code) (__VA_ARGS__); \
    } while (0)

/**
 * @brief           sends error message for invalid opcode
 * @param [in]      opcode and queue id which contains the opcode
 * @return          void.
 */
void com_send_rb_e_INVALID_OPCODE_ERR (uint32_t opcode, uint32_t queue_id);
/**
 * @brief           sends message timing errors.
 * @param [in]      reason code, opcode of the msg, variable args
 * @return          void.
 */

void com_send_rb_e_MSG_TIMING_ERR (e_reason_code_type_t reason_code, uint32_t opcode, uint32_t arg1, uint32_t arg2, uint32_t arg3,
                                   uint32_t arg4, uint32_t arg5);
/**
 * @brief           sends exception errors.
 * @param [in]      reason code, cause , frame_pc, addr , frame_ps(processor state), frame_a0,frame_a2,frame_a3, frame_a4, frame_a5
 * @return          void.
 */

void com_send_rb_e_EXCEPTION_ERR (e_reason_code_type_t reason_code, uint32_t cause, uint32_t frame_pc, uint32_t addr, uint32_t frame_ps,
                                  uint32_t frame_a0, uint32_t frame_a2, uint32_t frame_a3, uint32_t frame_a4, uint32_t frame_a5);
/**
 * @brief           sends exception errors.
 * @param [in]      reason code,event id, current event state(if applicable)and expected event state (if applicable)
 * @return          void.
 */
void com_send_rb_e_EVENT_HANDLER_ERR (e_reason_code_type_t reason_code, uint32_t event_id, uint32_t arg1, uint32_t arg2);

/**
 * @brief           sends default interrupt handler errors.
 * @param [in]      reason code,interrupt id)
 * @return          void.
 */
void com_send_rb_e_IRQ_ERR (e_reason_code_type_t reason_code, uint32_t interrupt_id);

/**
 * @brief           sends FSM transition error
 * @param [in]      current FSM state , FSM event
 * @return          void.
 */
void com_send_rb_e_FSM_TRANSITION_ERR (e_reason_code_type_t reason_code, e_fsm_type_t fsm_id, e_fsm_state_type_t curr_state,
                                       e_fsm_event_type_t fsm_event);

/**
 * @brief           sends Quad FSM transition error
 * @param [in]      current Quad FSM state , FSM event
 * @return          void.
 */
void com_send_rb_e_QUAD_FSM_TRANSITION_ERR (e_reason_code_type_t reason_code, e_fsm_type_t fsm_id, e_fsm_quad_state_type_t curr_state,
                                            e_fsm_quad_event_type_t fsm_event, e_quad_id_t quad_id);

/**
 * @brief           sends core sync-up timeout error in bootup
 * @param [in]      cpu index of which timeout to enter ready status, plus its current status
 * @return          void.
 */
void com_send_rb_e_BOOT_ERR (e_reason_code_type_t reason_code, uint32_t cpu_idx, uint32_t cpu_status);

/**
 * @brief           send Config Message Error
 * @param [in]      reason code, opcode of the message and additional variable argument
 * @return          void.
 */
void com_send_rb_e_CONFIG_MSG_ERR (e_reason_code_type_t reason_code, uint32_t opcode, uint32_t arg1);

#endif
