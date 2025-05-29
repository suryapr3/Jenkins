/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022-2024 Intel Corporation
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
 * @file    com_event.c
 * @brief   Implementation of the event processing loop and timed/scheduled events.
 */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_definitions.h"
#include "com_event.h"
#include "com_isr.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "com_error.h"
#include "com_bfn.h"
#include "com_trace_buffer.h"

#include <xtensa/core-macros.h>
#include <xtensa/xtruntime.h>
#if EVENT_USE_CPU_TIMER == 0
#include "int_cfg.h"
#include "timerx8.h"
#endif // EVENT_USE_CPU_TIMER == 0

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NUM_DBG_EVENTS (4)
#define DISABLE_SCHEDULER_LOG (1)
#define EVENT_PHI_IRQ  e_EVENT_CPU_TIMER0_IRQ // high priority event use cpu timer 0

#if EVENT_USE_CPU_TIMER == 1
#define EVENT_TIMER_IRQ e_EVENT_CPU_TIMER1_IRQ // event handler use cpu timer 1
#else

#if CPU_AX
#define TIMER_BASE_ADDR   RCS_TIMER_GRP0_TMR0_BASE
#define INT_AGG_BASE_ADDR RCS_GPREG_CORE0_BASE
#define RCS_TIMER_INT_IRQ e_RCS_TIMER_INT0_IRQ
#elif CPU_RX
#define TIMER_BASE_ADDR   RCS_TIMER_GRP0_TMR1_BASE
#define INT_AGG_BASE_ADDR RCS_GPREG_CORE1_BASE
#define RCS_TIMER_INT_IRQ e_RCS_TIMER_INT1_IRQ
#elif CPU_TX
#define TIMER_BASE_ADDR   RCS_TIMER_GRP1_TMR0_BASE
#define INT_AGG_BASE_ADDR RCS_GPREG_CORE2_BASE
#define RCS_TIMER_INT_IRQ e_RCS_TIMER_INT2_IRQ
#elif CPU_CAL
#define TIMER_BASE_ADDR   RCS_TIMER_GRP1_TMR1_BASE
#define INT_AGG_BASE_ADDR RCS_GPREG_CORE3_BASE
#define RCS_TIMER_INT_IRQ e_RCS_TIMER_INT3_IRQ
#endif // CPU_AX

#endif // EVENT_USE_CPU_TIMER

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
#define EVENT_SCHEDULING_LATENCY 600
#define EVENT_SCHED_PHI_LATENCY  200

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
PRIVATE event_t event_table[MAX_NUM_EVENTS];
PRIVATE uint32_t next_free_event = E_NO_EVENT;
PRIVATE volatile bool event_loop_continue = true;

PRIVATE uint32_t next_scheduled_event = E_NO_EVENT;
PRIVATE uint32_t next_plo_pending_event = E_NO_EVENT;
PRIVATE uint32_t next_phi_pending_event = E_NO_EVENT;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Debug print for the state of the event scheduler.
 * @param [in]      none
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_event_print_event_scheduler (void)
{
    if (DISABLE_SCHEDULER_LOG || (com_get_print_level () < FW_DEBUG))
        return;

    uint32_t events[NUM_DBG_EVENTS] = {0};

    uint32_t e_idx = next_scheduled_event;
    uint32_t p_idx = 0;
    while ((E_NO_EVENT != e_idx) && (p_idx < NUM_DBG_EVENTS))
    {
        events[p_idx++] = e_idx;
        e_idx = event_table[e_idx].next_event;
    }
    FW_PRINT (FW_DEBUG, "next_scheduled_event=%d:  %d %d %d %d", next_scheduled_event, events[0], events[1], events[2], events[3]);

    memset (events, 0, sizeof (events));
    e_idx = next_plo_pending_event;
    p_idx = 0;
    while ((E_NO_EVENT != e_idx) && (p_idx < NUM_DBG_EVENTS))
    {
        events[p_idx++] = e_idx;
        e_idx = event_table[e_idx].next_event;
    }
    FW_PRINT (FW_DEBUG, "next_plo_pending=%d:  %d %d %d %d", next_plo_pending_event, events[0], events[1], events[2], events[3]);

    memset (events, 0, sizeof (events));
    e_idx = next_phi_pending_event;
    p_idx = 0;
    while ((E_NO_EVENT != e_idx) && (p_idx < NUM_DBG_EVENTS))
    {
        events[p_idx++] = e_idx;
        e_idx = event_table[e_idx].next_event;
    }
    FW_PRINT (FW_DEBUG, "next_phi_pending=%d:  %d %d %d %d", next_phi_pending_event, events[0], events[1], events[2], events[3]);

    memset (events, 0, sizeof (events));
    e_idx = next_free_event;
    p_idx = 0;
    while ((E_NO_EVENT != e_idx) && (p_idx < NUM_DBG_EVENTS))
    {
        events[p_idx++] = e_idx;
        e_idx = event_table[e_idx].next_event;
    }
    FW_PRINT (FW_DEBUG, "next_free=%d:  %d %d %d %d", next_free_event, events[0], events[1], events[2], events[3]);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add the event index to the tail of the pending event list.
 * @param [in]      event_idx: Event to add to the list.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_event_set_pending_event (uint32_t event_idx)
{
    RT_ASSERT (MAX_NUM_EVENTS > event_idx);

    e_event_state_t start_state = event_table[event_idx].state;
    if (e_EVENT_SCHEDULED != start_state)
    {
        FW_PRINT (FW_ERR, "Attempting to execute non-scheduled event_idx:%d state:%d", event_idx, start_state);
        FW_SEND_ERR_RB (e_EVENT_HANDLER_ERR, e_EVENT_STATE_ERR, event_idx, start_state, e_EVENT_SCHEDULED);
        return;
    }

    ATOMIC_BEGIN
    uint32_t *p_next_pending_event =
        (e_EVENT_PRIORITY_HIGH == event_table[event_idx].priority) ? &next_phi_pending_event : &next_plo_pending_event;

    FW_PRINT (FW_DEBUG, "set_pending_event priority %d (%d onto %d)", event_table[event_idx].priority, event_idx, *p_next_pending_event);

    // Empty list:
    if ((E_NO_EVENT == *p_next_pending_event))
    {
        *p_next_pending_event = event_idx;
        FW_PRINT (FW_DEBUG, "set_pending_event -- NO EVENT");
    }
    else
    {
        FW_PRINT (FW_DEBUG, "set_pending_event -- ADD EVENT at %d", event_idx);
        // Add the event to the end of the list, go find the tail.
        uint32_t e_idx = *p_next_pending_event;
        uint32_t e_prev = *p_next_pending_event;
        while (E_NO_EVENT != e_idx)
        {
            e_prev = e_idx;
            e_idx = event_table[e_idx].next_event;
        }
        event_table[e_prev].next_event = event_idx;
    }

    event_table[event_idx].state = e_EVENT_PENDING;
    event_table[event_idx].next_event = E_NO_EVENT;
    ATOMIC_END

    com_event_print_event_scheduler ();
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Schedule high priority events pending list.
 * @param [in]      none
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_event_phi_pending_schedule ()
{ // use CPU timer instead of BFN to start high priority execution
    ATOMIC_BEGIN
    uint32_t const tick = xthal_get_ccount ();
    xthal_set_ccompare (EVENT_PHI_TIMER_NUM, tick + EVENT_SCHED_PHI_LATENCY);
    com_isr_interrupt_enable (EVENT_PHI_IRQ);
    ATOMIC_END
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Check the schedules events versus the current time, and move those events to the pending list.
 * @param [in]      none
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool com_event_check_scheduled_events ()
{
    bool task_found = false;
    int task_count = 0;

    // This loop structure allows interrupts to be more timely in the case multiple events are ready at the same time.
    // It will allow an IRQ as each event is added to the pending list.
    do {
        task_found = false;
        ATOMIC_BEGIN
        uint32_t timestamp = com_timing_get_current_bfn_time ();
        timestamp = com_bfn_add_time (timestamp, EVENT_SCHEDULING_LATENCY);
        if ((E_NO_EVENT != next_scheduled_event)
            && com_timing_is_bfn1_earlier_or_equal_bfn2 (event_table[next_scheduled_event].timestamp, timestamp))
        {
            uint32_t e_idx = next_scheduled_event;
            next_scheduled_event = event_table[next_scheduled_event].next_event;
            com_event_set_pending_event (e_idx);
            task_found = true;
            task_count++;
        }

        ATOMIC_END
    } while (task_found);

    return (task_count > 0);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Get the head of the pending list and increment the list.
 * @param [in]      p_head_idx: pointer to pending list
 * @return          event index from the front of the list.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_event_pop_next_pending_event (uint32_t *const p_head_idx)
{
    RT_ASSERT_POINTER (p_head_idx);
    uint32_t event_idx = E_NO_EVENT;

    ATOMIC_BEGIN
    if (*p_head_idx != E_NO_EVENT)
    {
        event_idx = *p_head_idx;
        *p_head_idx = event_table[event_idx].next_event;
        event_table[event_idx].state = e_EVENT_RUNNING;
    }
    ATOMIC_END

    FW_PRINT (FW_DEBUG, "get_next_pending_event=>%d", event_idx);
    return event_idx;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Configure the event timer to interrupt at the specified BFN time.
 * @param [in]      bfn_time: next event trigger time.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_event_configure_timer_irq (uint32_t bfn_time)
{
    uint32_t const current_bfn = com_timing_get_current_bfn_time ();
    // FW_PRINT (FW_INFO, "set_event_timer_irq @bfn %08x to bfn %08x", current_bfn, bfn_time);

#if EVENT_USE_CPU_TIMER == 1
    uint32_t const epoch = com_timing_get_current_epoch ();
    uint32_t const tick = com_timing_convert_bfn_to_ticks_epoch (epoch, bfn_time);
    FW_PRINT (FW_DEBUG, "set_event_timer_irq @cpu_tick %u", tick);
    xthal_set_ccompare (EVENT_CPU_TIMER_NUM, tick);
    com_isr_interrupt_enable (EVENT_TIMER_IRQ);
#else
    FW_PRINT (FW_DEBUG, "set_event_timer_irq @bfn %08x to bfn %08x", current_bfn, bfn_time);
    TIMERX8_T0_TRIG_REG (TIMER_BASE_ADDR)->value = bfn_time;
    timerx8_t_cfg_reg_t timer_cfg = {.INT_EN = 1, .ENABLE = 1};
    TIMERX8_T0_CFG_REG (TIMER_BASE_ADDR)->value = timer_cfg.value;
    com_isr_interrupt_enable (RCS_TIMER_INT_IRQ);
#endif
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Disable the event timer irq.
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_event_disable_timer_irq (void)
{
    FW_PRINT (FW_DEBUG, "disable_event_timer_irq");
#if EVENT_USE_CPU_TIMER == 1
    com_isr_interrupt_disable (EVENT_TIMER_IRQ);
#else
    com_isr_interrupt_disable (RCS_TIMER_INT_IRQ);
#endif
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Timer IRQ handler for event processing.
 * @param [in]      unused: Interrupt context.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/

static void com_event_handle_timer_irq (void *unused)
{
    UNUSED (unused);
    // FW_PRINT (FW_DEBUG, "timing_irq (bfn: 0x%08x) @%x", com_timing_get_current_bfn_time (), xthal_get_ccount ());

#if EVENT_USE_CPU_TIMER == 1
    xthal_set_ccompare (EVENT_CPU_TIMER_NUM, 0); // Clears the timer IRQ.
#else
    // Skipping read of the top-timer status register, only one timer enabled, expect this one is asserted.
    // Clears the timer IRQ.
    timerx8_t_cfg_reg_t const timer_status = {.value = INTRINSIC_READ32 ((void *)TIMERX8_T0_CFG_REG (TIMER_BASE_ADDR))};
    RT_ASSERT_EQUAL (timer_status.EXPIRED, 1);
#endif

    com_event_check_scheduled_events ();
    if (E_NO_EVENT != next_scheduled_event)
        com_event_configure_timer_irq (event_table[next_scheduled_event].timestamp);

    if (E_NO_EVENT != next_phi_pending_event)
        com_event_phi_pending_schedule ();
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           High priority queue execution handler.
 * @param [in]      unused: Interrupt context.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_event_handle_phi_irq (void *unused)
{
    com_isr_interrupt_disable (EVENT_PHI_IRQ);
    xthal_set_ccompare (EVENT_PHI_TIMER_NUM, 0); // Clears the timer IRQ.
    // FW_PRINT (FW_INFO, "Executing high priority !!!");
    uint32_t event_idx = com_event_pop_next_pending_event (&next_phi_pending_event);

    while (event_idx != E_NO_EVENT)
    {
        if (event_table[event_idx].p_event_f)
            event_table[event_idx].p_event_f (event_table[event_idx].context);
        com_event_free_event (event_idx);
        event_idx = com_event_pop_next_pending_event (&next_phi_pending_event);
    }

    com_isr_interrupt_enable (EVENT_PHI_IRQ);
}

////////////////////////////////////////
// Keep-Alive Event.
////////////////////////////////////////

struct ka_context
{
    uint32_t bfn_time;
    uint32_t period_us;
    uint32_t limit;
};

static void keepalive_event_callback (void *data);

static void keepalive_event_callback (void *data)
{
    static uint32_t loops = 0;
    static uint32_t count = 0;
    static uint32_t total = 0;
    static uint32_t max = 0;
    static uint32_t min = 100000;

    struct ka_context *ctx = (struct ka_context *)data;

    uint32_t ka_time = xthal_get_ccount ();
    uint32_t ka_bfn = com_timing_get_current_bfn_time ();

    FW_PRINT (FW_INFO, "KA%d @%08x  (%08x)  [%lu]", loops, ka_bfn, ctx->bfn_time, ka_time);

    if (BFN_FRAME_COUNT (ctx->bfn_time) == BFN_FRAME_COUNT (ka_bfn))
    {
        uint32_t latency = BFN_TIMER_COUNT (ka_bfn) - BFN_TIMER_COUNT (ctx->bfn_time);
        if (latency > max)
            max = latency;
        if (latency < min)
            min = latency;
        total += latency;
        count++;
        FW_PRINT (FW_INFO, "latency: %d  (avg: %d  min: %d   max: %d)", latency, total / count, min, max);
    }

    if (ctx->limit && (loops >= ctx->limit))
    {
        com_event_exit_event_loop ();
    }
    else
    {
        com_event_schedule_keepalive_event (ctx->period_us, ctx->limit);
    }

    loops++;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 *
 ***********************************************/
/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Schedule a do-nothing event to occur every specified period in micro-seconds.
 * @param [in]      period_us: Length of time between keep-alive events.
 * @param [in]      num_cycles: Number of times to interrupt, 0 means run forever..
 * @return          nothing.
 **/
void com_event_schedule_keepalive_event (uint32_t period_us, uint32_t num_cycles)
{
    uint32_t ka_event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (ka_event_idx);
    p_event->p_event_f = keepalive_event_callback;

    uint32_t const timestamp_now = com_timing_get_current_bfn_time ();
    uint32_t const bfn_delay = MS_TO_BFN_TICKS (period_us / 1000) + US_TO_BFN_TICKS (period_us % 1000);
    uint32_t const timestamp_run = com_bfn_add_time (timestamp_now, bfn_delay);
    struct ka_context *ctx = (struct ka_context *)p_event->context;
    ctx->bfn_time = timestamp_run;
    ctx->period_us = period_us;
    ctx->limit = num_cycles;

    com_event_schedule_event (ka_event_idx, timestamp_run);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Get a pointer to the specified event by index.
 * @param [in]      event_idx: Index of the event to retrieve.
 * @return          pointer to the requested index.
 **/
event_t *com_event_get_event_p (uint32_t event_idx)
{
    if (MAX_NUM_EVENTS <= event_idx)
    {
        FW_SEND_ERR_RB (e_EVENT_HANDLER_ERR, e_INVALID_EVENT_IDX, event_idx, 0, 0);
        return NULL;
    }
    return (&event_table[event_idx]);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Calling this function causes the event loop to exit.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_exit_event_loop ()
{
    FW_PRINT (FW_WARN, "Requesting exit of event loop.");
    event_loop_continue = false;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Initialize the free event list.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_init_events ()
{
    for (uint32_t i = 0; i < MAX_NUM_EVENTS; i++)
    {
        event_table[i].state = e_EVENT_FREE;
        event_table[i].next_event = i + 1;
    }

    event_table[MAX_NUM_EVENTS - 1].next_event = E_NO_EVENT;
    next_free_event = 0;
    next_scheduled_event = E_NO_EVENT;
    next_plo_pending_event = E_NO_EVENT;
    next_phi_pending_event = E_NO_EVENT;

#if EVENT_USE_CPU_TIMER == 1
    com_isr_event (EVENT_TIMER_IRQ, (f_isr_handler_t)com_event_handle_timer_irq, (void *)0);
#else
    com_isr_event (RCS_TIMER_INT_IRQ, (f_isr_handler_t)com_event_handle_timer_irq, (void *)0);
    INT_CFG11_GPREG_LVL_IRQ_MASK_REG (INT_AGG_BASE_ADDR)->value = 1 << RCS_CPU;
#endif

    com_isr_event (EVENT_PHI_IRQ, (f_isr_handler_t)com_event_handle_phi_irq, (void *)0);
    com_isr_interrupt_disable (EVENT_PHI_IRQ);
    com_event_print_event_scheduler ();
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Remove an event from the free list and return the index.
 * @param [in]      none
 * @return          Index of the event allocated.
 **/
uint32_t com_event_new_event (void)
{
    uint32_t event_idx = E_NO_EVENT;
    ATOMIC_BEGIN
    if (E_NO_EVENT != next_free_event)
    {
        event_idx = next_free_event;
        next_free_event = event_table[event_idx].next_event;
        event_table[event_idx].state = e_EVENT_ALLOCATED;
        event_table[event_idx].next_event = E_NO_EVENT;
        event_table[event_idx].priority = e_EVENT_PRIORITY_LOW;
    }
    ATOMIC_END
    if (E_NO_EVENT == event_idx)
    { // event overflow reason code
        FW_SEND_ERR_RB (e_EVENT_HANDLER_ERR, e_EVENT_OVERFLOW, event_idx, 0, 0);
    }

    com_event_print_event_scheduler ();
    return (event_idx);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add an event to the free list and return the index.
 * @param [in]      event_idx: The event to add to the free list.
 * @return          Index of the event freed.
 **/
uint32_t com_event_free_event (uint32_t event_idx)
{
    if (MAX_NUM_EVENTS <= event_idx)
        return E_NO_EVENT;

    ATOMIC_BEGIN
    event_table[event_idx].next_event = next_free_event;
    next_free_event = event_idx;
    event_table[event_idx].state = e_EVENT_FREE;
    ATOMIC_END

    return (event_idx);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add the event index to the sorted scheduled event list.
 * @param [in]      event_idx: Event to add to the list.
 * @param [in]      timestamp: Time to execute the event..
 * @return          event index that was scheduled.
 **/
uint32_t com_event_schedule_event (uint32_t event_idx, uint32_t timestamp)
{
    RT_ASSERT (MAX_NUM_EVENTS > event_idx);
    RT_ASSERT (E_NO_EVENT != event_idx);

    e_event_state_t start_state = event_table[event_idx].state;
    if (e_EVENT_ALLOCATED != start_state)
    {
        FW_PRINT (FW_ERR, "Attempting to schedule non-allocated event_idx:%d state:%d", event_idx, start_state);
        FW_SEND_ERR_RB (e_EVENT_HANDLER_ERR, e_EVENT_STATE_ERR, event_idx, start_state, e_EVENT_ALLOCATED);
        return E_NO_EVENT;
    }

    com_event_disable_timer_irq ();

    ATOMIC_BEGIN
    // Empty or first on the list:
    if ((E_NO_EVENT == next_scheduled_event)
        || com_timing_is_bfn1_earlier_or_equal_bfn2 (timestamp, event_table[next_scheduled_event].timestamp))
    {
        event_table[event_idx].state = e_EVENT_SCHEDULED;
        event_table[event_idx].next_event = next_scheduled_event;
        event_table[event_idx].timestamp = timestamp;
        next_scheduled_event = event_idx;
    }
    else
    {
        // Event will be placed between e_prev and e_idx.   e_prev guaranteed to != E_NO_EVENT.
        uint32_t e_idx = next_scheduled_event;
        uint32_t e_prev = next_scheduled_event;
        while ((E_NO_EVENT != e_idx) && com_timing_is_bfn1_earlier_bfn2 (event_table[e_idx].timestamp, timestamp))
        {
            e_prev = e_idx;
            e_idx = event_table[e_idx].next_event;
        }

        event_table[event_idx].state = e_EVENT_SCHEDULED;
        event_table[event_idx].next_event = e_idx;
        event_table[event_idx].timestamp = timestamp;

        event_table[e_prev].next_event = event_idx;
    }

    com_event_check_scheduled_events ();

    if (E_NO_EVENT != next_scheduled_event)
        com_event_configure_timer_irq (event_table[next_scheduled_event].timestamp);

    if (E_NO_EVENT != next_phi_pending_event)
        com_event_phi_pending_schedule ();
    ATOMIC_END

    com_event_print_event_scheduler ();

    return (event_idx);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Add the event index to the pending event list.
 * @param [in]      event_idx: Event to add to the list.
 * @return          event index that was scheduled.
 **/
uint32_t com_event_execute_immediate_event (uint32_t event_idx)
{
    RT_ASSERT (MAX_NUM_EVENTS > event_idx);
    RT_ASSERT (E_NO_EVENT != event_idx);

    e_event_state_t start_state = event_table[event_idx].state;
    if (e_EVENT_ALLOCATED != start_state)
    {
        FW_PRINT (FW_ERR, "Attempting to execute non-allocated event_idx:%d state:%d", event_idx, start_state);
        FW_SEND_ERR_RB (e_EVENT_HANDLER_ERR, e_EVENT_STATE_ERR, event_idx, start_state, e_EVENT_ALLOCATED);
        return E_NO_EVENT;
    }

    event_table[event_idx].state = e_EVENT_SCHEDULED;

    com_event_set_pending_event( event_idx );
    return( event_idx );
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Loop for event processing. *Use this API in main thread only*. Routine does not exit normally.
 * @param [in]      none.
 * @return          none.
 **/
void com_event_event_loop ()
{
    uint32_t event_idx = E_NO_EVENT;
    uint32_t loops = 0;
    event_loop_continue = true;

    // Debug Trace 0, compare BFN to CCOUNT.
    uint32_t const trace_size = 2;
    uint32_t time_base[trace_size];
    time_base[0] = com_timing_get_current_bfn_time ();
    time_base[1] = xthal_get_ccount ();
    com_debug_trace_buffer (e_TRACE_DEBUG, DEBUG_TRACE_TIME_SYNC, trace_size, 0, time_base);

    do {
        com_shared_mem_set_cpu_loop_count (RCS_CPU, loops++);

        ATOMIC_BEGIN
        event_idx = com_event_pop_next_pending_event (&next_plo_pending_event);
        if (event_idx == E_NO_EVENT)
        {
            if (!com_event_check_scheduled_events ())
            {
                // unmask all interrupts and wait.
                // code from here to ATOMIC_END and back to top of do-while can be interrupted.
                INTRINSIC_WAIT_FOR_IRQ;
            }
        }
        ATOMIC_END

        if (event_idx != E_NO_EVENT)
        {
            if (event_table[event_idx].p_event_f)
                event_table[event_idx].p_event_f (event_table[event_idx].context);
            com_event_free_event (event_idx);
        }
    } while (event_loop_continue);
}
