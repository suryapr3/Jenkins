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
#ifndef COMMON_TIMING_H
#define COMMON_TIMING_H

#include <stdbool.h>
#include <stdint.h>

// #define BFN_TICKS_TO_US(bfn)    ((bfn*25)/24576)  Not enabled due to potential for rounding problems.  Use NS.
#define MS_TO_BFN_TICKS(ms)  ((ms)*983040)
#define US_TO_BFN_TICKS(us)  (((us)*24576) / 25)
#define BFN_TICKS_TO_NS(bfn) (((bfn)*3125) / 3072)
#define NS_TO_BFN_TICKS(ns)  (((ns)*3072) / 3125)

#define BFN_FRAME_MASK      (0xFF000000)
#define BFN_FRAME_SHIFT     (24)
#define BFN_TIMER_MASK      (0x00FFFFFF)
#define BFN_TIMER_SHIFT     (0)
#define BFN_MAX_TIMER_COUNT (0x960000) //  US_TO_BFN_TICKS(10000)

#define BFN_FRAME_COUNT(bfn)   (bfn >> BFN_FRAME_SHIFT)
#define BFN_TIMER_COUNT(bfn)   (bfn & BFN_TIMER_MASK)
#define BFN_TIME(f, t)         ((f << BFN_FRAME_SHIFT) | BFN_TIMER_COUNT (t))
#define BFN_TIME_TO_TICKS(bfn) ((BFN_FRAME_COUNT (bfn) * BFN_MAX_TIMER_COUNT) + BFN_TIMER_COUNT (bfn))

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Return the current BFN time..
 * @param [in]      none
 * @return          current BFN time.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_timing_get_current_bfn_time ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Compare two BFN timestamps, return true if bfn1 is earlier than bfn2.
 * @param [in]      bfn1: Earlier timestamp.
 * @param  [in]     bfn2: Later timestamp.
 * @return          true if bfn1 is earlier than bfn2.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_timing_is_bfn1_earlier_bfn2 (uint32_t const bfn1, uint32_t const bfn2);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Compare two BFN timestamps, return true if bfn1 is earlier than bfn2, or equal.
 * @param [in]      bfn1: Earlier timestamp.
 * @param [in]      bfn2: Later timestamp.
 * @return          true if bfn1 is earlier or equal to bfn2.
 * -------------------------------------------------------------------------------------------------------------------*/
bool com_timing_is_bfn1_earlier_or_equal_bfn2 (uint32_t const bfn1, uint32_t const bfn2);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', convert the CPU timer value to an equivalent BFN value.
 * @param [in]      epoch: BFN time corresponding to tick == 0.
 * @param [in]      ticks: number of ticks elapsed since the epoch.
 * @return          updated BFN.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_timing_convert_ticks_to_bfn_epoch (uint32_t epoch, uint32_t ticks);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', convert a BFN time value to a tick value.
 * @param [in]      epoch: BFN time corresponding to tick == 0.
 * @param [in]      bfn: BFN to convert to ticks.
 * @return          tick count corresponding to passed BFN.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_timing_convert_bfn_to_ticks_epoch (uint32_t epoch, uint32_t bfn);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Given an 'epoch', increment to the next epoch when the ticks roll over.
 *                  Does not update the current epoch.
 * @param [in]      prior_bfn_epoch: BFN time corresponding to tick == 0.
 * @return          updated BFN epoch for the next time tick == 0..
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_timing_increment_epoch (uint32_t prior_bfn_epoch);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Retrieve the current epoch.
 * @param [in]      none.
 * @return          current BFN epoch.
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_timing_get_current_epoch ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Retrieve the current epoch.
 * @param [in]      new BFN epoch.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_timing_set_current_epoch (uint32_t epoch);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Wait for a period of time.
 * @param [in]      NS to wait.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_timing_wait_ns (uint32_t ns_wait);

#endif
