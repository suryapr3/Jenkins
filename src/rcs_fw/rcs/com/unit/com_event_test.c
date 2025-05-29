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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#if (CPU_AX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <stdbool.h>
#include <string.h>
#include <xtensa/config/core.h>
#include <xtensa/core-macros.h>
#include <xtensa/corebits.h>
#include <xtensa/xtruntime.h>

#include "com_event.h"
#include "com_print.h"
#include "com_timing.h"
#include "com_assert.h"
#include "com_bfn.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define IDX_LAST_TBL_EVENT                 (MAX_NUM_EVENTS - 1)
#define EVENT_QUE_VERIFY_WORKING(head, sz) event_queue_verify (head, sz, true)
#define EVENT_QUE_VERIFY_FREE(sz)          event_queue_verify (next_free_event, sz, false)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern event_t event_table[MAX_NUM_EVENTS];
extern uint32_t next_free_event;
extern volatile bool event_loop_continue;

extern uint32_t next_scheduled_event;
extern uint32_t next_plo_pending_event;
extern uint32_t next_phi_pending_event;

// next_scheduled_event = future
// next_x_pending_event =  current

extern uint32_t com_event_pop_next_pending_event (uint32_t *const p_head_idx);
extern void com_event_print_event_scheduler ();
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
uint32_t irq_count = 0;

void ticker_irq1 (void *unused)
{
    UNUSED (unused);

    // xthal_interrupt_clear (XCHAL_TIMER0_INTERRUPT);
    xthal_set_ccompare (0, 0); // clear interrupt

    uint32_t tick = xthal_get_ccount ();
    FW_PRINT (FW_INFO, "ticker1 irq @%d (0x%x)", tick, tick);

    //    xthal_set_ccompare (0, tick + 500000);
    irq_count++;
    if (irq_count > 0)
        com_event_exit_event_loop ();
}

static void event_func1 (void *data)
{
    uint32_t *p_data = (uint32_t *)data;
    uint32_t idata = p_data[0];
    FW_PRINT (FW_INFO, "func1: %d @%d", idata, xthal_get_ccount ());

    // com_event_print_event_scheduler();
}

static void event_func2 (void *data)
{
    char const *const fmt = (char *)data;
    FW_PRINT (FW_INFO, fmt, xthal_get_ccount ());

    com_event_exit_event_loop ();
}

static void event_queue_verify (uint32_t idx_head, uint32_t const sz, bool const verify_time)
{ // Not considering wrap around
    uint32_t cnt = 0;
    uint32_t ts_prev = 0;

    if (sz == 0)
    {
        RT_ASSERT (idx_head == E_NO_EVENT);
    }
    else
    {
        while (idx_head != E_NO_EVENT)
        {
            cnt++;
            ts_prev = event_table[idx_head].timestamp;
            idx_head = event_table[idx_head].next_event;
            if ((idx_head != E_NO_EVENT) && (verify_time))
            {
                RT_ASSERT (ts_prev <= event_table[idx_head].timestamp);
                if (cnt == (sz - 1))
                {
                    RT_ASSERT_EX (event_table[idx_head].next_event == E_NO_EVENT, "last next_event != E_NO_EVENT, cnt=%d, sz=%d", cnt, sz);
                }
            }
        }
        RT_ASSERT_EX (cnt == sz, "Event list actual cnt=%d, expected=%d", cnt, sz);
    }
}

static void event_queue_pend_incr ()
{                             // Not considering wrap around
    com_event_init_events (); // to clear the queue

    RT_ASSERT (E_NO_EVENT != next_free_event);
    for (uint32_t idx = 0; idx < MAX_NUM_EVENTS; idx++)
    {
        uint32_t idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;
        com_event_schedule_event (idx_event, idx * 10);
    }

    RT_ASSERT (0 == next_plo_pending_event);
    RT_ASSERT (E_NO_EVENT == next_scheduled_event);
    RT_ASSERT (E_NO_EVENT == next_free_event);
    EVENT_QUE_VERIFY_WORKING (next_plo_pending_event, MAX_NUM_EVENTS);
}

static void event_queue_sched_desc ()
{
    com_event_init_events (); // clear the queue

    uint32_t const ts_total = 0x80000000;
    for (uint32_t idx = 0; idx < MAX_NUM_EVENTS; idx++)
    {
        uint32_t idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;
        com_event_schedule_event (idx_event, ts_total - (idx * 10));
    }

    RT_ASSERT (IDX_LAST_TBL_EVENT == next_scheduled_event);
    RT_ASSERT (E_NO_EVENT == next_plo_pending_event);
    RT_ASSERT (E_NO_EVENT == next_free_event);
    EVENT_QUE_VERIFY_WORKING (next_scheduled_event, MAX_NUM_EVENTS);
}

static void event_queue_both ()
{
    com_event_init_events (); // clear the queue

    uint32_t const ts_total = 0x80000000;
    uint32_t const sz_list = MAX_NUM_EVENTS / 2;
    for (uint32_t idx = 0; idx < MAX_NUM_EVENTS; idx++)
    {
        uint32_t idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;

        if (idx % 2) // next_scheduled_event increase 1, 3, 5 => (1)
        {
            com_event_schedule_event (idx_event, idx * 10);
        }
        else // next_plo_pending_event decrease, 14, 12, 10 => (14)
        {
            com_event_schedule_event (idx_event, ts_total - (idx * 10));
        }
    }

    RT_ASSERT_EX (next_scheduled_event == IDX_LAST_TBL_EVENT - 1, "Both queue, schedule head actual=%d, expected=%d", next_scheduled_event,
                  IDX_LAST_TBL_EVENT - 1);
    RT_ASSERT_EX (next_plo_pending_event == 1, "Both queue, pending head actual=%d, expected=%d", next_plo_pending_event, 1);
    RT_ASSERT (E_NO_EVENT == next_free_event);
    EVENT_QUE_VERIFY_WORKING (next_plo_pending_event, sz_list);
    EVENT_QUE_VERIFY_WORKING (next_scheduled_event, sz_list);
}

static void event_queue_free_list ()
{
    com_event_init_events (); // clear the queue

    for (uint32_t idx = 0; idx < 2; idx++)
    {
        uint32_t idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;

        if (idx % 2) // next_scheduled_event decrease (0)
        {
            uint32_t const ts_current = com_timing_get_current_bfn_time ();
            com_event_schedule_event (idx_event, com_bfn_add_time (ts_current, 800000));
        }
        else // next_plo_pending_event increase (1)
        {
            com_event_schedule_event (idx_event, 10);
        }
    }

    RT_ASSERT_EX (next_scheduled_event == 1, "Free queue, schedule head actual=%d, expected=%d", next_scheduled_event, 1);
    RT_ASSERT_EX (next_plo_pending_event == 0, "Free queue, pending head actual=%d, expected=%d", next_plo_pending_event, 0);
    RT_ASSERT_EX (next_free_event == 2, "Free queue, free head actual=%d, expected=%d", next_free_event, 2);
    EVENT_QUE_VERIFY_WORKING (next_plo_pending_event, 1);
    EVENT_QUE_VERIFY_WORKING (next_scheduled_event, 1);
}

static void event_queue_pending_pop ()
{
    com_event_init_events (); // clear the queue

    uint32_t const sz = 2;
    uint32_t sz_free = MAX_NUM_EVENTS - (sz * 2);
    for (uint32_t idx = 0; idx < sz; idx++)
    { // Adding pending queue
        uint32_t const idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;
        com_event_schedule_event (idx_event, idx * 10);
    }

    for (uint32_t idx = 0; idx < sz; idx++)
    { // Adding schedule queue
        uint32_t const idx_event = com_event_new_event ();
        event_t *p_event1 = com_event_get_event_p (idx_event);
        p_event1->p_event_f = NULL;
        uint32_t const ts_current = com_timing_get_current_bfn_time ();
        com_event_schedule_event (idx_event, com_bfn_add_time (ts_current, 800000));
    }

    RT_ASSERT_EX (next_free_event == sz * 2, "Pop queue, free head actual=%d, expected=%d", next_free_event, sz * 2);
    EVENT_QUE_VERIFY_FREE (sz_free);

    sz_free += 1;
    uint32_t const idx_pop = com_event_pop_next_pending_event (&next_plo_pending_event);
    com_event_free_event (idx_pop);
    EVENT_QUE_VERIFY_WORKING (next_plo_pending_event, 1);
    RT_ASSERT_EX (next_free_event == 0, "Pop queue, free head actual=%d, expected=%d", next_free_event, 0);
    EVENT_QUE_VERIFY_FREE (sz_free);
}

static void event_queue_philo_pend_incr ()
{
    com_event_init_events (); // to clear the queue

    uint32_t idx_event1 = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (idx_event1);
    p_event->p_event_f = NULL;
    p_event->priority = e_EVENT_PRIORITY_LOW;

    uint32_t idx_event2 = com_event_new_event ();
    p_event = com_event_get_event_p (idx_event2);
    p_event->p_event_f = NULL;
    p_event->priority = e_EVENT_PRIORITY_HIGH;

    com_event_schedule_event (idx_event1, 10);
    com_event_schedule_event (idx_event2, 20);

    RT_ASSERT (E_NO_EVENT == next_scheduled_event);
    RT_ASSERT (1 == next_free_event); // next_free_event only 1 instead of 2 due to  phi pending execute and removed from pending list
    RT_ASSERT (0 == next_plo_pending_event);
    RT_ASSERT (E_NO_EVENT
               == next_phi_pending_event); // next_phi_pending_event is E_NO_EVENT due to event execute and removed from pending list
    EVENT_QUE_VERIFY_WORKING (next_plo_pending_event, 1);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    g_assertion_counter = 0;
    //    for(uint32_t i=0; i<argc; i++)
    //    {
    //        FW_PRINT(FW_INFO, "argv[%d]=%s", i, argv[i]);
    //    }
    if (argc > 1)
        com_set_print_level (argv[1][0] - '0');

    //    xtos_set_interrupt_handler(XCHAL_TIMER1_INTERRUPT,
    //            (xtos_handler) ticker_irq1, (void *)0, NULL);
    //    xtos_set_interrupt_handler(XCHAL_TIMER0_INTERRUPT,
    //            (xtos_handler) ticker_irq0, (void *)0, NULL);

    com_bfn_set_clk_sel (e_CLK_983M); // need to set this for com_bfn_add_time to work

    // Queue test, dont change the test sequence here as it is timing sensitive.
    // Adding print will cause failure as well due to timing sensitive
    event_queue_pend_incr ();
    event_queue_sched_desc ();
    event_queue_both ();
    event_queue_free_list ();
    event_queue_pending_pop ();
    event_queue_philo_pend_incr ();

    if (g_assertion_counter)
    { // Queue test fail and exit
        FW_PRINT (FW_ERR, "Event queue asserts: %d", g_assertion_counter);
        return g_assertion_counter;
    }

    // --- Low priority test, legacy stuff ---
    xthal_enable_interrupts ();
    com_event_init_events (); // clear the queue

    uint32_t event_idx1 = com_event_new_event ();
    event_t *p_event1 = com_event_get_event_p (event_idx1);
    p_event1->p_event_f = event_func1;
    p_event1->priority = e_EVENT_PRIORITY_LOW;
    *(uint32_t *)(p_event1->context) = 5;

    uint32_t event_idx2 = com_event_new_event ();
    event_t *p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_func2;
    p_event2->priority = e_EVENT_PRIORITY_LOW;
    strcpy ((char *)p_event2->context, "This is a format string: CPU_COUNT=%d");

    uint32_t bfn_time = com_timing_get_current_bfn_time ();

    // xthal_interrupt_enable(XCHAL_TIMER0_INTERRUPT);
    // xthal_set_ccompare(1, bfn_time+200000);
    // xthal_set_ccompare(0, bfn_time+200000);

    uint32_t run_time1 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (800));
    uint32_t run_time2 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (1200));
    FW_PRINT (FW_INFO, "Current time: 0x%x   f=%d  ms=%d", bfn_time, BFN_FRAME_COUNT (bfn_time), BFN_TIMER_COUNT (bfn_time));
    FW_PRINT (FW_INFO, "RUN1: 0x%x   f=%d  ms=%d", run_time1, BFN_FRAME_COUNT (run_time1), BFN_TIMER_COUNT (run_time1));
    FW_PRINT (FW_INFO, "RUN2: 0x%x   f=%d  ms=%d", run_time2, BFN_FRAME_COUNT (run_time2), BFN_TIMER_COUNT (run_time2));

    com_event_schedule_event (event_idx2, run_time2);
    com_event_schedule_event (event_idx1, run_time1);

    FW_PRINT (FW_INFO, "Scheduling events %d, %d at %x, %x", event_idx1, event_idx2, run_time1, run_time2);
    com_event_event_loop ();

    // --- Low and high priority test ---
    event_idx1 = com_event_new_event ();
    p_event1 = com_event_get_event_p (event_idx1);
    p_event1->p_event_f = event_func1;
    p_event1->priority = e_EVENT_PRIORITY_LOW;
    *(uint32_t *)(p_event1->context) = 5;

    event_idx2 = com_event_new_event ();
    p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_func2;
    p_event2->priority = e_EVENT_PRIORITY_HIGH;
    strcpy ((char *)p_event2->context, "High priority: CPU_COUNT=%d");

    bfn_time = com_timing_get_current_bfn_time ();
    run_time1 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (800));
    run_time2 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (1200));
    FW_PRINT (FW_INFO, "H/L Current time: 0x%x   f=%d  ms=%d", bfn_time, BFN_FRAME_COUNT (bfn_time), BFN_TIMER_COUNT (bfn_time));
    FW_PRINT (FW_INFO, "H/L RUN1: 0x%x   f=%d  ms=%d", run_time1, BFN_FRAME_COUNT (run_time1), BFN_TIMER_COUNT (run_time1));
    FW_PRINT (FW_INFO, "H/L RUN2: 0x%x   f=%d  ms=%d", run_time2, BFN_FRAME_COUNT (run_time2), BFN_TIMER_COUNT (run_time2));

    com_event_schedule_event (event_idx2, run_time2);
    com_event_schedule_event (event_idx1, run_time1);

    FW_PRINT (FW_INFO, "Scheduling H/L events %d, %d at %x, %x", event_idx1, event_idx2, run_time1, run_time2);
    com_event_event_loop ();

    // === All low and high priority test must be completed before this line interlude section will reload handler ===
    FW_PRINT (FW_INFO, "***** INTERLUDE ***** ");

    // No longer using "phi worker thread", use it as timer 0 will be used as interlude stuff.
    xthal_interrupt_disable (XCHAL_TIMER0_INTERRUPT);
    xtos_set_interrupt_handler (XCHAL_TIMER0_INTERRUPT, (xtos_handler)ticker_irq1, (void *)0, NULL);
    xthal_interrupt_enable (XCHAL_TIMER0_INTERRUPT);
    xthal_set_ccompare (0, 0x96000000);

    com_event_event_loop ();

    FW_PRINT (FW_INFO, "***** PART TWO ***** ");

    event_idx1 = com_event_new_event ();
    p_event1 = com_event_get_event_p (event_idx1);
    p_event1->p_event_f = event_func1;
    p_event1->priority = e_EVENT_PRIORITY_LOW;
    *(uint32_t *)(p_event1->context) = 5;

    event_idx2 = com_event_new_event ();
    p_event2 = com_event_get_event_p (event_idx2);
    p_event2->p_event_f = event_func2;
    p_event2->priority = e_EVENT_PRIORITY_LOW;
    strcpy ((char *)p_event2->context, "Part 2 format string: CPU_COUNT=%d");

    bfn_time = com_timing_get_current_bfn_time ();

    run_time1 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (800));
    run_time2 = com_bfn_add_time (bfn_time, US_TO_BFN_TICKS (1200));
    FW_PRINT (FW_INFO, "Current time: 0x%x   f=%d  ms=%d", bfn_time, BFN_FRAME_COUNT (bfn_time), BFN_TIMER_COUNT (bfn_time));
    FW_PRINT (FW_INFO, "RUN1: 0x%x   f=%d  ms=%d", run_time1, BFN_FRAME_COUNT (run_time1), BFN_TIMER_COUNT (run_time1));
    FW_PRINT (FW_INFO, "RUN2: 0x%x   f=%d  ms=%d", run_time2, BFN_FRAME_COUNT (run_time2), BFN_TIMER_COUNT (run_time2));

    com_event_schedule_event (event_idx2, run_time2);
    com_event_schedule_event (event_idx1, run_time1);

    FW_PRINT (FW_INFO, "Scheduling events %d, %d at %x, %x", event_idx1, event_idx2, run_time1, run_time2);
    com_event_event_loop ();

    if (g_assertion_counter)
    {
        FW_PRINT (FW_ERR, "Total asserts: %d", g_assertion_counter);
    }
    return (g_assertion_counter);
}
