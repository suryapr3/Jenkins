/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2023 Intel Corporation
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
 * @file    ax_main.c
 * @brief   This file contains description of the entry function for auxiliary core
 * @details AX core main function.
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_definitions.h"
#include "com_boot.h"
#include "com_print.h"
#include "car.h"
#include "com_fsm.h"
#include "rcs_gpreg.h"
#include "com_queue.h"
#include "com_event.h"
#include "com_bfn.h"
#include "com_fsm.h"
#include "com_lock.h"
#include "admin_msg_handler.h"
#include "com_isr.h"
#include "sys_ctrl.h"
#include "ax_clk_rst.h"

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
 * @brief           initializing boot status used to record boot status in each core
 * @param [in]      none
 * @return          none
 */
static void init_boot_status ();

/**
 * @brief           start other cores by removing RUNSTALL bits in corresponding core control reg
 * @param [in]      none
 * @return          none
 */
static void start_cores ();

/**
 * @brief           phase 1 of bootup. boot status init, check FW loaded match running processor, start trace and set trace level
 *                  common init done only once by AX core, plus init message queue
 * @param [in]      none
 * @return          none
 */
static void boot_phase1 ();

/**
 * @brief           phase 2 of bootup. enable interrupt, start other cores, registering bootup ISRs, common boot init, check
 *                  core-sync-up
 * @param [in]      none
 * @return          none
 */
static void boot_phase2 ();

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
void init_boot_status ()
{
    // FIXME: check RSM readness: should not do this check in product, only for pre-sil test, should not in prod code
    if (!com_shared_mem_wait_for_ready ())
    {
        FW_PRINT (FW_WARN, "RSM Not ready.");
    }

    // init boot_status
    for (uint32_t cpu_idx = e_RCS_CPU0; cpu_idx < e_CPUID_NUM_CPUID; cpu_idx++)
    {
        com_shared_mem_set_sys_status (cpu_idx, e_SYS_STATUS_UNKNOWN);
        com_shared_mem_set_cpu_loop_count (cpu_idx, 0);
    }
}

void start_cores ()
{
    // remove RUNSTALL for other cores:
    // core1:
    rcs_gpreg_core1_ctrl_reg_t core1_start_reg = {.value = RCS_GPREG_CORE1_CTRL_DEFAULT};
    core1_start_reg.CORE_RUNSTALL = 0;
    *RCS_GPREG_CORE1_CTRL_REG = core1_start_reg;
    // core2:
    rcs_gpreg_core2_ctrl_reg_t core2_start_reg = {.value = RCS_GPREG_CORE2_CTRL_DEFAULT};
    core2_start_reg.CORE_RUNSTALL = 0;
    *RCS_GPREG_CORE2_CTRL_REG = core2_start_reg;
    // core3
    rcs_gpreg_core3_ctrl_reg_t core3_start_reg = {.value = RCS_GPREG_CORE3_CTRL_DEFAULT};
    core3_start_reg.CORE_RUNSTALL = 0;
    *RCS_GPREG_CORE3_CTRL_REG = core3_start_reg;

    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_CORES_START);
}

void boot_phase1 ()
{
    core_fw_mismatch_check ();

    init_boot_status ();
    dbg_n_trace ();

    // AX specific msg Q init
    msg_queue_t *p_rb_msg_queue = com_shared_mem_get_queue_block (e_RB_QUEUE);
    com_queue_init (p_rb_msg_queue);
    msg_queue_t *p_admin_msg_queue = com_shared_mem_get_queue_block (e_ADMIN_QUEUE);
    com_queue_init (p_admin_msg_queue);
    msg_queue_t *p_rx0_msg_queue = com_shared_mem_get_queue_block (e_RX_QUEUE);
    com_queue_init (p_rx0_msg_queue);
    msg_queue_t *p_tx0_msg_queue = com_shared_mem_get_queue_block (e_TX_QUEUE);
    com_queue_init (p_tx0_msg_queue);
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_MSG_Q_INIT);

    com_isr_init ();
    com_lock_init ();
}

void boot_phase2 ()
{
    // disable all interrupts:
    xthal_disable_interrupts ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_XTHAL_DIS_INT);

    start_cores ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_BFN_INIT);

    com_boot_init ();

    // registering msg handler ISR for specific core:
    com_msg_init_mb_irq (admin_msg_irq_hdlr_map, e_NUM_AD_MB_IRQ);
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_MSG_ISR);

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

    com_event_event_loop ();

    FW_PRINT (FW_ERR, "Event Loop Exited.");
    com_shared_mem_set_sys_status (RCS_CPU, e_SYS_EXITED);
#if (PRINT_CUSTOM_DEBUGCALL)
    com_test_FW (false);
#endif

    while (1) { INTRINSIC_WAIT_FOR_IRQ; }
    return (0);
}
