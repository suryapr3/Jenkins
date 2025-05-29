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
#ifndef COMMON_FSM_H
#define COMMON_FSM_H

#include <stdbool.h>
#include <stdint.h>
#include "com_fsm_def.h"

typedef enum
{
    e_FSM_TRANSITION_RET_FAIL,
    e_FSM_TRANSITION_RET_SUCCESS

} e_fsm_status_ret_type_t;
/**
 * @brief           Initialize overall and quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          void.
 */

void com_fsm_init (e_fsm_type_t fsm_id);

/**
 * @brief           Initialize quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          void.
 */

void com_fsm_quad_init (e_fsm_type_t fsm_id);

/*
 * @brief           gets the current quad FSM status from shared memory
 * @param [in]      fsm_id : TX/ RX, quad id
 * @return          current quad FSM status .
 */

e_fsm_quad_state_type_t com_fsm_quad_get_status (e_fsm_type_t fsm_id, e_quad_id_t quad_id);

/*
 * @brief           get the current Overall FSM status from shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          current overall FSM status .
 */

e_fsm_state_type_t com_fsm_get_status (e_fsm_type_t fsm_id);

/**
 * @brief           Update quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX, quad id,Overall FSM state
 * @return          void.
 */

void com_fsm_quad_update_status (e_fsm_type_t fsm_id, e_quad_id_t quad_id, e_fsm_quad_state_type_t fsm_quad_data);

/**
 * @brief           Update Overall FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX,Overall FSM state
 * @return          void.
 */

void com_fsm_update_status (e_fsm_type_t fsm_id, e_fsm_state_type_t fsm_data);

/**
 * @brief           Overall State transition Function
 * @param [in]      fsm_id : TX/ RX, Current fsm state, FSM event
 * @return          returns fsm transition success or failure
 */

e_fsm_status_ret_type_t com_fsm_transition (e_fsm_type_t fsm_id, e_fsm_state_type_t fsm_data, e_fsm_event_type_t fsm_event);

/**
 * @brief           Quad State transition Function
 * @param [in]      Current quad fsm state, fsm event, quad id
 * @return          returns fsm transition success or failure.
 */

e_fsm_status_ret_type_t com_fsm_quad_transition (e_fsm_type_t fsm_id, e_fsm_quad_state_type_t fsm_quad_data, e_fsm_quad_event_type_t fsm_event,
                                                 e_quad_id_t quad_id);

/**
 * @brief           Get active quads and transition
 * @param [in]      fsm_id : TX/ RX, quad mask , fsm quad event
 * @return          returns fsm transition success or failure.
 */

e_fsm_status_ret_type_t com_fsm_transition_quadmask (e_fsm_type_t fsm_id, uint8_t quad_mask, e_fsm_quad_event_type_t fsm_event);

/**
 * @brief           Checks for all the quads to be turned off to transition the overall FSM to configure
 * @param [in]      fsm_id : TX/ RX
 * @return          returns fsm transition success or failure.
 */

e_fsm_status_ret_type_t com_fsm_transition_off_stop (e_fsm_type_t fsm_id);

/**
 * @brief           Checks for off mode check and identifies the stop mode
 * @param [in]      off mode
 * @return          quad event type .
 */

e_fsm_quad_event_type_t com_fsm_off_mode_check (uint8_t offmode);

/**
 * @brief           Transition the overall statemachine to First Quad On
 * @param [in]      fsm_id : TX/ RX
 * @return          returns fsm transition success or failure.
 */

e_fsm_status_ret_type_t com_fsm_transition_run (e_fsm_type_t fsm_id);

/**
 * @brief           Check for active quad masks to transition
 * @param [in]      fsm_id : TX/ RX, quad masks , fsm quad event
 * @return          returns fsm transition success or failure.
 */

e_fsm_status_ret_type_t com_fsm_transition_check_quadmask_transition (e_fsm_type_t fsm_id, uint8_t quad_mask0, uint8_t quad_mask1, uint8_t quad_mask2,
                                                                      uint8_t quad_mask3, e_fsm_quad_event_type_t fsm_event);

#endif
