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
 * @file    tx_main.c
 * @brief   This file contains description of the entry function for TX core.
 * @details TX core main function with boot phases.
 */

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_boot.h"
#include "com_print.h"
#include "com_event.h"
#include "com_isr.h"
#include "com_bfn.h"
#include "tx_msg_handler.h"
#include "com_fsm.h"

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
 *                  also init message queue
 * @param [in]      none
 * @return          none
 */
static void boot_phase1 ();

/**
 * @brief           phase 2 of bootup. enable interrupt, registering bootup ISRs, common boot init, FSM init, check core-sync-up,
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

    msg_queue_t *p_tx_rm_queue = com_shared_mem_get_queue_block (e_TX_RM_QUEUE);
    com_queue_init (p_tx_rm_queue);

    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_MSG_Q_INIT);
}

void boot_phase2 ()
{
    // disable all interrupts:
    xthal_disable_interrupts ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_XTHAL_DIS_INT);

    com_boot_init ();

    // registering msg handler ISR for specific core:
    com_msg_init_mb_irq (tx_msg_irq_hdlr_map, e_NUM_TX_MB_IRQ);
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_MSG_ISR);

    com_fsm_init (e_FSM_TX);
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_FSM_INIT);

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
    boot_phase2 ();

    com_fsm_transition (e_FSM_TX, com_fsm_get_status (e_FSM_TX), e_EVENT_BOOT);

    com_event_event_loop ();

    FW_PRINT (FW_ERR, "Event Loop Exited.");
    com_shared_mem_set_sys_status (RCS_CPU, e_SYS_EXITED);
#if (PRINT_CUSTOM_DEBUGCALL)
    com_test_FW (false);
#endif

    while (1) { INTRINSIC_WAIT_FOR_IRQ; }
    return (0);
}
