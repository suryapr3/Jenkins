/* INTEL CONFIDENTIAL
 *
 * Copyright  2022-2024 Intel Corporation All Rights Reserved.
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
#ifndef COMMON_EVENT_H
#define COMMON_EVENT_H

#include <stdint.h>
#include <xtensa/core-macros.h>

#if UNIT == 1
#define EVENT_USE_CPU_TIMER (1)
#define EVENT_CPU_TIMER_NUM (1)
#else
#define EVENT_USE_CPU_TIMER (0)
#endif // UNIT

// !! In FW enviroment CPU timer 0 is reserved for high priority event, no one should use !!

#define EVENT_PHI_TIMER_NUM      (0)
#define EVENT_CONTEXT_SIZE_BYTES (64)
#define MAX_NUM_EVENTS           (24)

typedef void (*p_event_func_t) (void *data);

typedef enum
{
    e_EVENT_FREE,
    e_EVENT_ALLOCATED,
    e_EVENT_SCHEDULED,
    e_EVENT_PENDING,
    e_EVENT_RUNNING
} e_event_state_t;

enum
{
    E_NO_EVENT = 0xFFFFFFFF
};

typedef enum
{
    e_EVENT_PRIORITY_LOW = 0,
    e_EVENT_PRIORITY_HIGH,
    e_EVENT_PRIORITY_MAX
} e_event_priority_t;

typedef struct
{
    p_event_func_t p_event_f;
    uint32_t timestamp;
    e_event_state_t state;
    e_event_priority_t priority;
    uint32_t next_event;
    unsigned char context[EVENT_CONTEXT_SIZE_BYTES];
} event_t;

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Initialize the free event list.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_init_events (void);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Remove an event from the free list and return the index.
 * @param [in]      none
 * @return          Index of the event allocated.
 **/
uint32_t com_event_new_event (void);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add an event to the free list and return the index.
 * @param [in]      event_idx: The event to add to the free list.
 * @return          Index of the event freed.
 **/
uint32_t com_event_free_event (uint32_t event_idx);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Get a pointer to the specified event by index.
 * @param [in]      event_idx: Index of the event to retrieve.
 * @return          pointer to the requested index.
 **/
event_t *com_event_get_event_p (uint32_t event_idx);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add the event index to the sorted scheduled event list.
 * @param [in]      event_idx: Event to add to the list.
 * @param [in]      timestamp: Time to execute the event..
 * @return          event index that was scheduled.
 **/
uint32_t com_event_schedule_event (uint32_t event_idx, uint32_t timestamp);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add the event index to the pending event list.
 * @param [in]      event_idx: Event to add to the list.
 * @return          event index that was scheduled.
 **/
uint32_t com_event_execute_immediate_event (uint32_t event_idx);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add a do-nothing keep-alive event that runs per some ms.
 *                  If num_cycles > 0 event loop will exit after num_cycles keep-alive runs.
 * @param [in]      period_us: How often to wake in micro-seconds.
 * @param [in]      num_cycles: After this many cycles, exit the event loop.
 * @return          none.
 **/
void com_event_schedule_keepalive_event (uint32_t period_us, uint32_t num_cycles);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Calling this function causes the event loop to exit.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_exit_event_loop (void);

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Loop for event processing.    Routine does not exit normally.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_event_loop (void);


#endif
