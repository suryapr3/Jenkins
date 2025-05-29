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

#if (CPU_CAL)
#else
#error "Not CAL CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_boot.h"
#include "com_print.h"
#include "com_event.h"
#include "com_bfn.h"

#include "rf_calib_nleq_driver.h"
#include "rf_calib_static_data_table.h"

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
/**
 * @brief           phase 1 of bootup. check FW loaded match running processor, start trace and set trace level
 * @param [in]      none
 * @return          none
 */
static void boot_phase1 ();

/**
 * @brief           phase 2 of bootup. enable interrupt, common boot init, check core-sync-up
 * @param [in]      none
 * @return          none
 */
static void boot_phase2 ();

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
void boot_phase1 ()
{
    core_fw_mismatch_check ();

    dbg_n_trace ();
}

void boot_phase2 ()
{
    // disable all interrupts:
    xthal_disable_interrupts ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_XTHAL_DIS_INT);

    com_boot_init ();
    com_bfn_set_clk_sel (e_CLK_983M); // todo: when move to config message, update accordingly, All cores.

    // enable all interrupts:
    xthal_enable_interrupts ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_XTHAL_EN_INT);

    core_sync_up (BOOT_SYNC_WAIT_CYCLE, BOOT_SYNC_PAUSE_IN_NS);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    boot_phase1 ();

    // TODO: keep it here now but to be moved once MSG frame work is ready
    // do NLEQ cal:
    if (get_tf (rf_calib_control_lut, 0, nleq_calibration_enable))
    {
        FW_PRINT (FW_INFO, "Performing NLEQ calibration.");
        rf_calib_nleq_driver (0, NULL);
        com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_NLEQ_CAL);
    }

    boot_phase2 ();

    com_event_event_loop ();

    FW_PRINT (FW_ERR, "Event Loop Exited.");
    com_shared_mem_set_sys_status (RCS_CPU, e_SYS_EXITED);
#if (PRINT_CUSTOM_DEBUGCALL)
    com_test_FW (false);
#endif

    while (1) { INTRINSIC_WAIT_FOR_IRQ; }
    return (0);
}
