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
 * @file    tx_bfn.c
 * @brief   BFN test file on TX core
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_bfn.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "rcs_timer_gpreg.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void test_main_bfn_inc_dec (com_bfn_cnt_t const inc_pre_val)
{
    TIMER_GPREG->REG_INC_PRE_REG0.value = inc_pre_val.CNT_LOW.value;
    TIMER_GPREG->REG_INC_PRE_REG1.value = inc_pre_val.CNT_HIGH.value;
    TIMER_GPREG->REG_ICTRL.value = 0x000000B2; // execute initialize command, so that above INC_PRE values are captured.
    // 28 NOPs
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;

    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    //	INTRINSIC_BARRIER;

    TIMER_GPREG->REG_ICTRL.value = 0x00000000;
    TIMER_GPREG->REG_ICTRL.value = 0x000000B3;
    //  28 NOPs
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;

    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;

    //	INTRINSIC_BARRIER;
    TIMER_GPREG->REG_ICTRL.value = 0x00000000;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    FW_PRINT (FW_INFO, "BFN started");
    if (!com_shared_mem_wait_for_ready ())
        FW_PRINT (FW_WARN, "RSM Not ready.");
    com_shared_mem_set_cpu_status (E_CPUID_TX0, E_CPU_STATUS_MAIN);

    com_bfn_cnt_t const inc_pre_inc = {// increase 2 ticks
                                       .CNT_LOW.value = 2,
                                       .CNT_HIGH.value = 0};

    com_bfn_cnt_t const inc_pre_dec = {                             // decrease 2 ticks, not considering roll over
                                       .CNT_LOW.value = 0xFF95FFFE, // just a basic test.
                                       .CNT_HIGH.value = 0xFFFFFFFF};

    com_bfn_init ();
    // com_bfn_set_ant_mask (0x0000FFFF); // only need to test remote
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;
    INTRINSIC_NOP;

    test_main_bfn_inc_dec (inc_pre_inc);
    // test_main_bfn_inc_dec (inc_pre_dec);
    // com_bfn_time_adjust (2);
    // com_bfn_time_adjust (-2);

    com_timing_wait_ns (50000);
    FW_PRINT (FW_INFO, "BFN complete");

    return (0);
}
