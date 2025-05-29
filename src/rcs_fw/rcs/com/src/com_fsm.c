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
 * @file    com_fsm.c
 * @brief   Finite State Machine for Overall and Quad level transitions
 * @details State transitions of Messaging /Timing Events
 */
#include "com_assert.h"
#include "com_print.h"
#include "com_definitions.h"
#include "com_error.h"
#include "com_fsm.h"
#include "com_shared_memory.h"
#include <string.h>

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
#define OFF_MODE_CAL  0x1
#define OFF_MODE_STOP 0x2
/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Initialize overall and quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          void.
 */

void com_fsm_init (e_fsm_type_t fsm_id)
{
    fsm_data_t *p_fsm_data = com_shared_mem_get_fsm_status_block (fsm_id);
    p_fsm_data->fsm_curr_state = e_STATE_RESET;
    com_fsm_quad_init (fsm_id);
}

/**
 * @brief           Initialize quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          void.
 */

void com_fsm_quad_init (e_fsm_type_t fsm_id)
{
    for (int i = 0; i < e_MAX_NUM_QUAD; i++)
    {
        fsm_quad_data_t *p_fsm_quad_data_addr = com_shared_mem_get_fsm_quad_status_block (fsm_id);
        p_fsm_quad_data_addr->fsm_quad_curr_state[i] = e_QUAD_STATE_RESET;
    }
}

/*
 * @brief           gets the current quad FSM status from shared memory
 * @param [in]      fsm_id : TX/ RX, quad id
 * @return          current quad FSM status .
 */

e_fsm_quad_state_type_t com_fsm_quad_get_status (e_fsm_type_t fsm_id, e_quad_id_t quad_id)
{
    fsm_quad_data_t *p_fsm_quad_data_addr = com_shared_mem_get_fsm_quad_status_block (fsm_id);

    return (p_fsm_quad_data_addr->fsm_quad_curr_state[quad_id]);
}

/**
 * @brief           Update quad FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX, quad id,Overall FSM state
 * @return          void.
 */

void com_fsm_quad_update_status (e_fsm_type_t fsm_id, e_quad_id_t quad_id, e_fsm_quad_state_type_t fsm_quad_data)
{
    fsm_quad_data_t *p_fsm_quad_data_addr = com_shared_mem_get_fsm_quad_status_block (fsm_id);
    if (p_fsm_quad_data_addr->fsm_quad_curr_state[quad_id] != fsm_quad_data)
    {
        p_fsm_quad_data_addr->fsm_quad_curr_state[quad_id] = fsm_quad_data;
    }
    FW_PRINT (FW_INFO, "Quad FSM quad_id : %d FSM add  :%d  FSM Data: %d  ", quad_id,(uint32_t) &p_fsm_quad_data_addr->fsm_quad_curr_state[quad_id],
            (uint32_t)p_fsm_quad_data_addr->fsm_quad_curr_state[quad_id]);
    INTRINSIC_BARRIER;
}

/*
 * @brief           get the current Overall FSM status from shared memory
 * @param [in]      fsm_id : TX/ RX
 * @return          current overall FSM status .
 */

e_fsm_state_type_t com_fsm_get_status (e_fsm_type_t fsm_id)
{
    fsm_data_t *p_fsm_data = com_shared_mem_get_fsm_status_block (fsm_id);
    return (p_fsm_data->fsm_curr_state);
}

/**
 * @brief           Update Overall FSM status in shared memory
 * @param [in]      fsm_id : TX/ RX, Overall FSM state
 * @return          returns fsm transition success or failure..
 */

void com_fsm_update_status (e_fsm_type_t fsm_id, e_fsm_state_type_t fsm_data)
{
    fsm_data_t *p_fsm_data = com_shared_mem_get_fsm_status_block (fsm_id);
    if (p_fsm_data->fsm_curr_state != fsm_data)
    {
        p_fsm_data->fsm_curr_state = fsm_data;
    }
    FW_PRINT (FW_INFO, "Overall FSM Update  Add : %d  FSM Data: %d  ", (uint32_t)&p_fsm_data->fsm_curr_state,(uint32_t) p_fsm_data->fsm_curr_state);
}

/**
 * @brief           Check for active quad masks to transition
 * @param [in]      fsm_id : TX/ RX, quad masks , fsm quad event
 * @return          void.
 */

e_fsm_status_ret_type_t com_fsm_transition_check_quadmask_transition (e_fsm_type_t fsm_id, uint8_t quad_mask0, uint8_t quad_mask1,
                                                                      uint8_t quad_mask2, uint8_t quad_mask3,
                                                                      e_fsm_quad_event_type_t fsm_event)
{
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    if (quad_mask0)
    {
        status = com_fsm_transition_quadmask (fsm_id, quad_mask0, fsm_event);
    }
    if (quad_mask1)
    {
        status = com_fsm_transition_quadmask (fsm_id, quad_mask1, fsm_event);
    }
    if (quad_mask2)
    {
        status = com_fsm_transition_quadmask (fsm_id, quad_mask2, fsm_event);
    }
    if (quad_mask3)
    {
        status = com_fsm_transition_quadmask (fsm_id, quad_mask3, fsm_event);
    }
    return (status);
}
/**
 * @brief           Get active quads and transition
 * @param [in]      fsm_id : TX/ RX, quad mask , fsm quad event
 * @return          returns fsm transition success or failure..
 */

e_fsm_status_ret_type_t com_fsm_transition_quadmask (e_fsm_type_t fsm_id, uint8_t quad_mask, e_fsm_quad_event_type_t fsm_event)
{
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    for (uint32_t i = 0; i < e_MAX_NUM_QUAD; i++)
    {
        if (quad_mask & (1 << i))
        {
            status = com_fsm_quad_transition (fsm_id, com_fsm_quad_get_status (fsm_id, i), fsm_event, i);
            if (status == e_FSM_TRANSITION_RET_FAIL)
            {
                return (status);
            }
        }
    }
    return (status);
}

/**
 * @brief           Transition the overall statemachine to First Quad On
 * @param [in]      fsm_id : TX/ RX
 * @return          returns fsm transition success or failure..
 */

e_fsm_status_ret_type_t com_fsm_transition_run (e_fsm_type_t fsm_id)
{
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    if (com_fsm_get_status (fsm_id) != e_STATE_RUN)
    {
        status = com_fsm_transition (fsm_id, com_fsm_get_status (fsm_id), e_EVENT_FIRST_QUAD_ON);
    }
    return (status);
}

/**
 * @brief           Checks for all the quads to be turned off to transition the overall FSM to configure
 * @param [in]      fsm_id : TX/ RX
 * @return          returns fsm transition success or failure..
 */

e_fsm_status_ret_type_t com_fsm_transition_off_stop (e_fsm_type_t fsm_id)

{
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    e_fsm_quad_state_type_t fsm_quad0 = com_fsm_quad_get_status (fsm_id, e_QUAD0);
    e_fsm_quad_state_type_t fsm_quad1 = com_fsm_quad_get_status (fsm_id, e_QUAD1);
    e_fsm_quad_state_type_t fsm_quad2 = com_fsm_quad_get_status (fsm_id, e_QUAD2);
    e_fsm_quad_state_type_t fsm_quad3 = com_fsm_quad_get_status (fsm_id, e_QUAD3);

    FW_PRINT (FW_INFO, "fsm_quad0 : %d  fsm_quad1: %d fsm_quad2:  %d fsm_quad3 : %d ", fsm_quad0, fsm_quad1, fsm_quad2, fsm_quad3);
    if ((fsm_quad0 == e_QUAD_STATE_CONFIG || fsm_quad0 == e_STATE_RESET) && (fsm_quad1 == e_QUAD_STATE_CONFIG || fsm_quad1 == e_STATE_RESET)
        && (fsm_quad2 == e_QUAD_STATE_CONFIG || fsm_quad2 == e_STATE_RESET)
        && (fsm_quad3 == e_QUAD_STATE_CONFIG || fsm_quad3 == e_STATE_RESET))
    {
        status = com_fsm_transition (fsm_id, com_fsm_get_status (fsm_id), e_EVENT_LAST_QUAD_OFF);
    }
    return (status);
}

/**
 * @brief           Checks for off mode check and identifies the stop mode
 * @param [in]      off mode
 * @return          quad event type .
 */

e_fsm_quad_event_type_t com_fsm_off_mode_check (uint8_t offmode)
{
    e_fsm_quad_event_type_t quad_event = e_QUAD_EVENT_NA;
    if (offmode == 0)
    {
        quad_event = e_QUAD_EVENT_OFF;
    }
    if (offmode & OFF_MODE_STOP)
    {
        quad_event = e_QUAD_EVENT_OFF_STOP;
    }
    if (offmode & OFF_MODE_CAL)
    {
        quad_event = e_QUAD_EVENT_OFF; // have to check what to do here
    }
    return quad_event;
}

/**
 * @brief           Overall State transition Function
 * @param [in]      fsm_id : TX/ RX, Current fsm state, FSM event
 * @return          returns fsm transition success or failure..
 */

e_fsm_status_ret_type_t com_fsm_transition (e_fsm_type_t fsm_id, e_fsm_state_type_t fsm_data, e_fsm_event_type_t fsm_event)
{
    e_fsm_state_type_t curr_fsm_state = fsm_data;
    e_fsm_state_type_t next_fsm_state = e_STATE_NA;
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    switch (fsm_event)
    {
        case e_EVENT_BOOT:
            if (curr_fsm_state == e_STATE_RESET)
            {
                next_fsm_state = e_STATE_SETUP;
            }
            break;

        case e_EVENT_FIRST_QUAD_ON: // warm up message
            if (curr_fsm_state == e_STATE_SETUP)
            {
                next_fsm_state = e_STATE_RUN;
            }
            break;

        case e_EVENT_CALIBRATE:
            if (curr_fsm_state == e_STATE_SETUP || curr_fsm_state == e_STATE_RUN)
            {
                next_fsm_state = curr_fsm_state;
            }
            break;

        case e_EVENT_CONFIG:
        case e_EVENT_BFN_SYNC:
            //  case e_EVENT_SHUTDOWN:
            if (curr_fsm_state == e_STATE_SETUP)
            {
                next_fsm_state = curr_fsm_state;
            }
            break;

        case e_EVENT_SLEEP:
            if (curr_fsm_state == e_STATE_SETUP)
            {
                next_fsm_state = e_STATE_DEEP_SLEEP;
            }
            break;
        case e_EVENT_WAKE:
            if (curr_fsm_state == e_STATE_DEEP_SLEEP)
            {
                next_fsm_state = e_STATE_SETUP;
            }
            break;
        case e_EVENT_LAST_QUAD_OFF:
            if (curr_fsm_state == e_STATE_RUN)
            {
                next_fsm_state = e_STATE_SETUP;
            }
            break;
        default:
            RT_ASSERT_HERE ();
            FW_PRINT (FW_INFO, "Invalid FSM Event");
            break;
    }
    if (next_fsm_state == e_STATE_NA)
    {
        FW_SEND_ERR_RB (e_FSM_TRANSITION_ERR, e_FSM_TRANSITION_STATE_ERR, fsm_id, curr_fsm_state, fsm_event);
        status = e_FSM_TRANSITION_RET_FAIL;
        return (status);
    }
    com_fsm_update_status (fsm_id, next_fsm_state);
    return (status);
}

/**
 * @brief           Quad State transition Function
 * @param [in]      fsm_id : TX/ RX, Current quad fsm state, fsm event, quad id
 * @return          returns fsm transition success or failure..
 */

e_fsm_status_ret_type_t com_fsm_quad_transition (e_fsm_type_t fsm_id, e_fsm_quad_state_type_t fsm_quad_data,
                                                 e_fsm_quad_event_type_t fsm_event, e_quad_id_t quad_id)
{
    e_fsm_quad_state_type_t curr_fsm_state = fsm_quad_data;
    e_fsm_quad_state_type_t next_fsm_state = e_QUAD_STATE_NA;
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    switch (fsm_event)
    {
        case e_QUAD_EVENT_CONFIG:
            if (curr_fsm_state == e_QUAD_STATE_RESET)
            {
                next_fsm_state = e_QUAD_STATE_CONFIG;
            }
            break;

        case e_QUAD_EVENT_WARMUP:
            if (curr_fsm_state == e_QUAD_STATE_CONFIG)
            {
                next_fsm_state = e_QUAD_STATE_READY_EVCC;
            }
            break;

        case e_QUAD_EVENT_CALIBRATE:
        case e_QUAD_EVENT_RECONFIG:
            if (curr_fsm_state == e_QUAD_STATE_CONFIG)
            {
                next_fsm_state = curr_fsm_state; // continue in the same state
            }
            break;

        case e_QUAD_EVENT_ON:
            if (curr_fsm_state == e_QUAD_STATE_READY_EVCC || curr_fsm_state == e_QUAD_STATE_IDLE)
            {
                next_fsm_state = e_QUAD_STATE_ACTIVE;
            }
            break;
        case e_QUAD_EVENT_OFF:
            if (curr_fsm_state == e_QUAD_STATE_ACTIVE)
            {
                next_fsm_state = e_QUAD_STATE_IDLE;
            }
            break;
        case e_QUAD_EVENT_ON_FAST:
            if (curr_fsm_state == e_QUAD_STATE_GAP_EVCC)
            {
                next_fsm_state = e_QUAD_STATE_ACTIVE;
            }
            break;

        case e_QUAD_EVENT_UPDATE:
            if (curr_fsm_state == e_QUAD_STATE_ACTIVE || curr_fsm_state == e_QUAD_STATE_RAMP_DOWN
                || curr_fsm_state == e_QUAD_STATE_GAP_EVCC)
            {
                next_fsm_state = curr_fsm_state; // continue in the same state
            }
            break;

        case e_QUAD_EVENT_ERR:
            if (curr_fsm_state == e_QUAD_STATE_ACTIVE)
            {
                next_fsm_state = e_QUAD_STATE_RAMP_DOWN;
            }
            break;

        case e_QUAD_EVENT_TIMEOUT:
            if (curr_fsm_state == e_QUAD_STATE_RAMP_DOWN)
            {
                next_fsm_state = e_QUAD_STATE_GAP_EVCC;
            }
            break;
        case e_QUAD_EVENT_OFF_FAST:
            if (curr_fsm_state == e_QUAD_STATE_ACTIVE)
            {
                next_fsm_state = e_QUAD_STATE_GAP_EVCC;
            }
            break;
        case e_QUAD_EVENT_OFF_STOP:
            if (curr_fsm_state == e_QUAD_STATE_READY_EVCC || curr_fsm_state == e_QUAD_STATE_ACTIVE || curr_fsm_state == e_QUAD_STATE_IDLE
                || curr_fsm_state == e_QUAD_STATE_RAMP_DOWN || curr_fsm_state == e_QUAD_STATE_GAP_EVCC)
            {
                next_fsm_state = e_QUAD_STATE_CONFIG;
            }
            break;

        case e_QUAD_EVENT_FATAL_ERR:
            if (curr_fsm_state == e_QUAD_STATE_READY_EVCC || curr_fsm_state == e_QUAD_STATE_ACTIVE || curr_fsm_state == e_QUAD_STATE_IDLE
                || curr_fsm_state == e_QUAD_STATE_RAMP_DOWN || curr_fsm_state == e_QUAD_STATE_GAP_EVCC)
            {
                next_fsm_state = e_QUAD_STATE_CONFIG;
            }
            break;
        default:
            RT_ASSERT_HERE ();
            FW_PRINT (FW_INFO, "Invalid Quad FSM Event");
            break;
    }
    if (next_fsm_state == e_QUAD_STATE_NA)
    {
        FW_SEND_ERR_RB (e_QUAD_FSM_TRANSITION_ERR, e_QUAD_FSM_TRANSITION_STATE_ERR, fsm_id, curr_fsm_state, fsm_event, quad_id);
        status = e_FSM_TRANSITION_RET_FAIL;
        return (status);
    }
    com_fsm_quad_update_status (fsm_id, quad_id, next_fsm_state);
    return (status);
}
