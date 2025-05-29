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
#ifndef COMMON_FSM_DEF_H
#define COMMON_FSM_DEF_H

#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    e_QUAD0,
    e_QUAD1,
    e_QUAD2,
    e_QUAD3,
    e_MAX_NUM_QUAD
} e_quad_id_t;

typedef enum
{
    e_FSM_TX,
    e_FSM_RX,
    e_MAX_NUM_FSM
} e_fsm_type_t;

typedef enum
{
    e_STATE_NA,
    e_STATE_RESET,
    e_STATE_SETUP,
    e_STATE_RUN,
    e_STATE_DEEP_SLEEP,
    e_STATE_MAX
} e_fsm_state_type_t;

typedef enum
{
    e_EVENT_NA,
    e_EVENT_BOOT,
    e_EVENT_CONFIG,
    e_EVENT_CALIBRATE,
    e_EVENT_BFN_SYNC,
    e_EVENT_FIRST_QUAD_ON,
    e_EVENT_LAST_QUAD_OFF,
    e_EVENT_OFF_STOP,
    e_EVENT_SHUTDOWN,
    e_EVENT_SLEEP,
    e_EVENT_WAKE,
    e_EVENT_MAX
} e_fsm_event_type_t;

typedef enum
{
    e_QUAD_STATE_NA,
    e_QUAD_STATE_RESET,
    e_QUAD_STATE_CONFIG,
    e_QUAD_STATE_READY_EVCC,
    e_QUAD_STATE_ACTIVE,
    e_QUAD_STATE_IDLE,
    e_QUAD_STATE_RAMP_DOWN,
    e_QUAD_STATE_GAP_EVCC,
    e_QUAD_STATE_MAX
} e_fsm_quad_state_type_t;

typedef enum
{
    e_QUAD_EVENT_NA,
    e_QUAD_EVENT_CONFIG,
    e_QUAD_EVENT_CALIBRATE,
    e_QUAD_EVENT_RECONFIG,
    e_QUAD_EVENT_WARMUP,
    e_QUAD_EVENT_ON,
    e_QUAD_EVENT_UPDATE,
    e_QUAD_EVENT_ON_FAST,
    e_QUAD_EVENT_OFF,
    e_QUAD_EVENT_OFF_FAST,
    e_QUAD_EVENT_OFF_STOP,
    e_QUAD_EVENT_TIMEOUT,
    e_QUAD_EVENT_ERR,
    e_QUAD_EVENT_FATAL_ERR,
    e_QUAD_EVENT_SHUTDOWN,
    e_QUAD_EVENT_MAX
} e_fsm_quad_event_type_t;

typedef struct
{
    e_fsm_quad_state_type_t fsm_quad_curr_state[e_MAX_NUM_QUAD];
} fsm_quad_data_t;

typedef struct
{
    e_fsm_state_type_t fsm_curr_state;
} fsm_data_t;

#endif
