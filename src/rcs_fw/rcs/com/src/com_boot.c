/* INTEL CONFIDENTIAL
 *
 * Copyright  2023 Intel Corporation All Rights Reserved.
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
#include "com_definitions.h"
#include "com_trax.h"
#include "com_error.h"
#include "com_boot.h"
#include "com_gpdma.h"
#include "com_idma.h"
#include "com_timing.h"
#include <xtensa/core-macros.h>
#include "com_static_data_table.h"
#include <string.h>
#include "com_event.h"
#include "com_lock.h"
#include "com_trace_buffer.h"
#include "com_msg_handler_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
//static volatile uint32_t ver_commit_id = VERSION_COMMIT_ID;
static volatile uint32_t ver_commit_id = 2424;
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern ver_fw_t ver_fw;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/


/**
 * @brief           Handler for boot_wait.   Disable and clear the timer IRQ.
 * @param [in]      unused :  unused.
 * @return          none.
 */
static void com_boot_wait_handler (void *unused)
{
    // Disable and clear the IRQ.
    com_isr_interrupt_disable (e_EVENT_CPU_TIMER1_IRQ);
    xthal_set_ccompare (1, 0);
}


/**
 * @brief           Wait for some ticks using an IRQ sleep/wakeup.   The IRQ wait is required for ASE to yield the thread.
 * @param [in]      duration_ticks :  Number of CPU clock ticks to wait before function return..
 * @return          none.
 */
static void com_boot_wait (uint32_t duration_ticks)
{
    com_isr_event (e_EVENT_CPU_TIMER1_IRQ, (f_isr_handler_t)com_boot_wait_handler, (void *)0);
    ATOMIC_BEGIN
        xthal_set_ccompare (1, xthal_get_ccount() + duration_ticks );
        com_isr_interrupt_enable (e_EVENT_CPU_TIMER1_IRQ);
        INTRINSIC_WAIT_FOR_IRQ;
    ATOMIC_END
}


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
void core_fw_mismatch_check ()
{
    uint32_t prid = xthal_get_prid () & 0x3; // the two LSB bits are PRID

    // when core/fw mismatch, PRINT won't work properly, so no use of PRINT here.
    // prid: id of the running core
    // RCS_CPU: id of FW image
    if (prid != RCS_CPU)
    {
        if (!com_shared_mem_wait_for_ready ())
        {
            ; // FIXME: check RSM readness: only for pre-sil test, should not in prod code
        }
        // set boot status for the real running core:
        com_shared_mem_set_sys_status (prid, e_BOOT_CORE_FW_MISMATCH);

        // if mismatch in core0, just notify RTE, as no other core will be started
        if (prid == e_CPUID_AX)
        {
            // have to init RB msg queue here as the FW loaded to AX core is incorrect, and we want to send RB to notify RTE:
            msg_queue_t *p_rb_msg_queue = com_shared_mem_get_queue_block (e_RB_QUEUE);
            com_queue_init (p_rb_msg_queue);
            FW_SEND_ERR_RB (e_BOOT_ERR, e_CORE_FW_MISMATCH, prid, e_BOOT_CORE_FW_MISMATCH);
        }

        // in all case, waiting in endless loop for the mismatched running core
        // for non-core0 case, eventually this will cause timeout
        // RTE will get notification from core0 for either e_CORE_FW_MISMATCH if core0 has mismatch,
        // or e_CORE_SYNC_TIMEOUT if any other core has mismatch
        while (1) { INTRINSIC_WAIT_FOR_IRQ; }
    }
}

void com_get_fw_version ()
{
    FW_PRINT (FW_INFO, "FW version details: "
                       "  Release Tag: " VERSION_TAG "  New Commits: " VERSION_INFO_COMMITS "  Date: " VERSION_BUILD_DATE
                       "  M/C: " VERSION_BUILD_MACHINE);
    FW_PRINT (FW_INFO, " Commit ID: 0x%x", ver_commit_id);
    FW_PRINT (FW_INFO, " Major: %d Minor: %d Year: %d Month: %d Day: %d", ver_fw.MAJOR, ver_fw.MINOR, ver_fw.YEAR, ver_fw.MONTH,
              ver_fw.DAY);
    FW_PRINT (FW_INFO, " eb: %d, iter: %d", ver_fw.EB, ver_fw.ITER);
    com_debug_trace_buffer (e_TRACE_EXT_DBG_BITS, 0, 0, ver_commit_id, 0);
}

// cores sync-up with timeout support:
void core_sync_up (uint32_t cycles, uint32_t pause_in_ns)
{
    e_rcs_sys_status_t core_status;
    uint32_t timeout_check = 0;

    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_SYS_READY);

    while (timeout_check < cycles)
    {
        uint8_t test = 0;
        com_boot_wait ( pause_in_ns );
        for (uint32_t core = e_RCS_CPU0; core < e_CPUID_NUM_CPUID; core++)
        {
            // check other cores' readness:
            if ((core != RCS_CPU) && (com_shared_mem_get_sys_status (core) == e_BOOT_SYS_READY))
            {
                test |= 1 << core;
            }
        }
        // break out if all other cores are in e_BOOT_SYS_READY
        if (test == (0xf & ~(1 << RCS_CPU)))
        {
            break;
        }
        timeout_check++;
    }

    // if timeout does happen:
    if (timeout_check == cycles)
    { // timeout: cycles * pause_in_ns ns
        for (uint32_t core = e_RCS_CPU0; core < e_CPUID_NUM_CPUID; core++)
        {
            if (core != RCS_CPU)
            { // only report the first checked core not in ready status
                core_status = com_shared_mem_get_sys_status (core);
                if (core_status != e_BOOT_SYS_READY)
                {
                    FW_PRINT (FW_ERR, "core%u timeout waiting for core%u sync-up", RCS_CPU, core);
                    FW_SEND_ERR_RB (e_BOOT_ERR, e_CORE_SYNC_TIMEOUT, core, core_status);
                    break;
                }
            }
        }

        while (1) { INTRINSIC_WAIT_FOR_IRQ; } // stay in endless loop when timeout happens
    }

    // from core0 indicates to RTE all RCS cores are booted and ready to receive msgs
    if (RCS_CPU == e_CPUID_AX)
    {
        msg_t rb_msg;
        memset (&rb_msg.boot_readback, 0, sizeof (boot_readback_bf_t));
        rb_msg.boot_readback.opcode = e_RB_BOOT_OPCODE; // add in e_opcode_type_t
        rb_msg.boot_readback.src = RCS_CPU;
        rb_msg.boot_readback.boot_status = 1;
        rb_msg.boot_readback.commit_id = ver_commit_id;
        rb_msg.boot_readback.major = ver_fw.MAJOR;
        rb_msg.boot_readback.minor = ver_fw.MINOR;
        rb_msg.boot_readback.year = ver_fw.YEAR;
        rb_msg.boot_readback.month = ver_fw.MONTH;
        rb_msg.boot_readback.day = ver_fw.DAY;
        rb_msg.boot_readback.eb = ver_fw.EB;
        rb_msg.boot_readback.iter = ver_fw.ITER;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (boot_readback_bf_t)));
    }
}

void dbg_n_trace ()
{
    // set debug print level:
    int const dbg_level = get_tf (com_fw_config_lut, 0, fw_debug_level);
    FW_PRINT (FW_INFO, "debug level: %d", dbg_level);
    com_set_print_level (dbg_level);

    // trace and debug init
    com_trax_init ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_TRAX_INIT);
    // trace and debug start
    com_trax_start ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_TRAX_START);
}

void com_boot_init ()
{
    com_lock_boundary_check_init ();
    com_idma_init ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_IDMA_INIT);
    com_gpdma_init ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_GPDMA_INIT);
    com_event_init_events ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_EVENT_INIT);
    com_msg_timestamp_init ();
    com_shared_mem_set_sys_status (RCS_CPU, e_BOOT_TS_INIT);
}
