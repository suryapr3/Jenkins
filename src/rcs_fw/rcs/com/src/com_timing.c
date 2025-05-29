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
 * @file    com_timing.c
 * @brief   Common functions for timing calculations.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define FW_PRINT_DISABLE 1

#include "com_timing.h"
#include "com_bfn.h"
#include "com_print.h"
#include <stdbool.h>
#include <stdint.h>
#include <xtensa/core-macros.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define NEGATIVE_ZERO    (0x80000000)
#define EPOCH_ROLL_10MS  (8912896)
#define EPOCH_ROLL_FRAME (436)
#define BFN_32BIT_PERIOD (0x96000000)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
uint32_t g_com_timing_epoch = 0;
uint32_t g_com_timing_prev_tick = 0;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static int32_t bfn_compare (uint32_t const bfn1, uint32_t const bfn2)
{
    int f_delta = (bfn1 & BFN_FRAME_MASK) - (bfn2 & BFN_FRAME_MASK);
    if (f_delta == 0 || f_delta == NEGATIVE_ZERO)
    {
        int t_delta = bfn1 - bfn2;
        FW_PRINT (FW_DEBUG, "BFN1=0x%08x BFN2=0x%08x  t_delta=%d", bfn1, bfn2, t_delta);
        return (t_delta);
    }

    FW_PRINT (FW_DEBUG, "BFN1=0x%08x BFN2=0x%08x  f_delta=%d", bfn1, bfn2, f_delta);
    return (f_delta);
}

__attribute__ ((always_inline)) inline uint32_t convert_tick_to_bfn (unsigned ticks)
{
    uint32_t bfn_frame = ticks / BFN_MAX_TIMER_COUNT;
    uint32_t bfn_10ms = ticks - (bfn_frame * BFN_MAX_TIMER_COUNT);
    return BFN_TIME (bfn_frame, bfn_10ms);
}

// return <0 if tick1 is 'earlier' than tick2.
static int32_t tick_compare (uint32_t const tick1, uint32_t const tick2)
{
    int32_t delta = (tick1 - tick2);
    FW_PRINT (FW_DEBUG, "TICK1=0x%08x TICK2=0x%08x  delta=%d", tick1, tick2, delta);
    return (delta);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Get the current BFN time from HW.
 * @param [in]      none
 * @return          current BFN.
 */
uint32_t com_timing_get_current_bfn_time ()
{
    uint32_t bfn;

#if UNIT == 1
    uint32_t ticks = xthal_get_ccount ();
    if (ticks < g_com_timing_prev_tick)
        com_timing_set_current_epoch (com_timing_increment_epoch (g_com_timing_epoch));
    bfn = com_timing_convert_ticks_to_bfn_epoch (g_com_timing_epoch, ticks);
    g_com_timing_prev_tick = ticks;
#else
    bfn = com_bfn_get_live_time ();
#endif
    return (bfn);
}

/**
 * @brief           Checks if timestamp1 is earlier than timestamp2.
 * @param [in]      bfn1 timestamp1.
 * @param [in]      bfn2 timestamp2
 * @return          true if bfn1 is earlier than bfn2.
 */
bool com_timing_is_bfn1_earlier_bfn2 (uint32_t const bfn1, uint32_t const bfn2)
{
    return bfn_compare (bfn1, bfn2) < 0;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Checks if timestamp1 is earlier than or equal timestamp2.
 * @param [in]      bfn1 timestamp1.
 * @param [in]      bfn2 timestamp2
 * @return          true if bfn1 is earlier than or equal bfn2.
 */
bool com_timing_is_bfn1_earlier_or_equal_bfn2 (uint32_t const bfn1, uint32_t const bfn2)
{
    return bfn_compare (bfn1, bfn2) <= 0;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', convert the CPU timer value to an equivalent BFN value.
 * @param [in]      epoch: BFN time corresponding to tick == 0.
 * @param [in]      ticks: number of ticks elapsed since the epoch.
 * @return          updated BFN.
 */
uint32_t com_timing_convert_ticks_to_bfn_epoch (uint32_t epoch, uint32_t ticks)
{
    uint32_t bfn_offset = convert_tick_to_bfn (ticks);
    uint32_t bfn_10ms = BFN_TIMER_COUNT (epoch) + BFN_TIMER_COUNT (bfn_offset);
    uint32_t bfn_frame = BFN_FRAME_COUNT (epoch) + BFN_FRAME_COUNT (bfn_offset);
    while (bfn_10ms >= BFN_MAX_TIMER_COUNT)
    {
        bfn_10ms -= BFN_MAX_TIMER_COUNT;
        bfn_frame++;
    }

    uint32_t bfn_time = BFN_TIME (bfn_frame, bfn_10ms);
    FW_PRINT (FW_DEBUG, "epoch:0x%08x tick:0x%08x --> bfn: 0x%08x", epoch, ticks, bfn_time);

    return bfn_time;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', convert a BFN time value to a tick value.   It is assumed that the bfn time passed in
 *                  is "in the future".
 * @param [in]      epoch: BFN time corresponding to tick == 0.
 * @param [in]      bfn: BFN to convert to ticks.
 * @return          tick count corresponding to passed BFN.
 */
uint32_t com_timing_convert_bfn_to_ticks_epoch (uint32_t epoch, uint32_t bfn)
{
    int bfn_frame_delta = BFN_FRAME_COUNT (bfn) - BFN_FRAME_COUNT (epoch);
    int bfn_10ms_delta = BFN_TIMER_COUNT (bfn) - BFN_TIMER_COUNT (epoch);

    // Conversion is somewhat arbitrary, calculate two candidates for tick time.
    uint32_t timer_value0 = bfn_frame_delta * BFN_MAX_TIMER_COUNT + bfn_10ms_delta;
    if ((bfn_frame_delta < 0) || ((bfn_frame_delta == 0) && (bfn_10ms_delta < 0)))
        timer_value0 += BFN_32BIT_PERIOD;

    uint32_t const timer_value1 = timer_value0 + BFN_32BIT_PERIOD;

    // Compare the results to the current time, assume we desire a value in the future.
    uint32_t const current_tick = xthal_get_ccount ();
    uint32_t timer_value = timer_value0;

    // If one converted BFN appears to be in the past, and one in the future, we want the later (future) value.
    // If both appear in the future, we want the "nearest".
    int32_t const timer0_compare = tick_compare (timer_value0, current_tick);
    int32_t const timer1_compare = tick_compare (timer_value1, current_tick);

    if (timer0_compare < 0)
    {
        if (timer1_compare < 0)
            FW_PRINT (FW_ERR, "Unable to convert ticks from BFN, both candidates in the past.");
        timer_value = timer_value1;
    }
    else
    {
        // Take the future, or "nearest value in the future" between the candidates if both are future times.
        if (timer1_compare > 0 && (timer0_compare > timer1_compare))
            timer_value = timer_value1;
    }

    FW_PRINT (FW_DEBUG, "epoch:0x%08x bfn:0x%08x --> tick: 0x%08x", epoch, bfn, timer_value);

    return timer_value;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', increment to the next epoch when the ticks roll over.
 *                  Does not update the current epoch.
 * @param [in]      prior_bfn_epoch: BFN time corresponding to tick == 0.
 * @return          updated BFN epoch for the next time tick == 0..
 */
uint32_t com_timing_increment_epoch (uint32_t prior_bfn_epoch)
{
    uint32_t bfn_10ms = BFN_TIMER_COUNT (prior_bfn_epoch);
    uint32_t bfn_frame = BFN_FRAME_COUNT (prior_bfn_epoch);

    bfn_10ms += EPOCH_ROLL_10MS;
    bfn_frame += EPOCH_ROLL_FRAME;
    while (bfn_10ms >= BFN_MAX_TIMER_COUNT)
    {
        bfn_10ms -= BFN_MAX_TIMER_COUNT;
        bfn_frame++;
    }
    return BFN_TIME (bfn_frame, bfn_10ms);
}

/**
 * @brief           Retrieve the current epoch.
 * @param [in]      none.
 * @return          current BFN epoch.
 */
uint32_t com_timing_get_current_epoch ()
{
    return (g_com_timing_epoch);
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set the current epoch.
 * @param [in]      new BFN epoch.
 * @return          none
 */
void com_timing_set_current_epoch (uint32_t epoch)
{
    FW_PRINT (FW_NOTE, "TIMING EPOCH UPDATE 0x%08x  %d", epoch, xthal_get_ccount ());
    g_com_timing_epoch = epoch;
}

void com_timing_wait_ns (uint32_t ns_wait)
{
    uint32_t now = xthal_get_ccount ();
    uint32_t later = now + NS_TO_BFN_TICKS (ns_wait);

    while (tick_compare (now, later) < 0) now = xthal_get_ccount ();
}
