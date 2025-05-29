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
 * @file    com_shared_memory.c
 * @brief   Common functions for handling the shared memory block.
 * @details Detailed description if necessary.
 * @todo
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_shared_memory.h"
#include "com_assert.h"
#include "com_definitions.h"
#include "rcs_gpreg.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define RSM_LOOP_LIMIT (500) // About 32us

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
// Using the __attribute__ will put this section into the ELF and it gets loaded/initialized.
// Referencing the linker symbol _sram_system_status_data_start put the structure at the same place without preloading.
// TODO: For both RTL and ASE environments, loading shared memory is not yet implemented.
// struct rcs_system_status_memory __attribute__ ((section(".sram.system_status.data"))) system_data;
extern unsigned _sram_system_status_data_start;
struct rcs_system_status_memory *p_system_data = (struct rcs_system_status_memory *)&_sram_system_status_data_start;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static rcs_sys_status_block_t *com_shared_mem_get_sys_status_block (e_cpu_id_t cpu_idx)
{
    RT_ASSERT ((e_CPUID_NUM_CPUID > cpu_idx) && (e_RCS_CPU0 <= cpu_idx));

    rcs_sys_status_block_t *p_sys_info = (rcs_sys_status_block_t *)(p_system_data->rcs_sys_status);
    return (&p_sys_info[cpu_idx]);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Update CPU status in the shared memory status block..
 * @param [in]      cpu_idx:   CPU being updated.
 * @param [in]      status:  New CPU status.
 * @return          nothing.
 */
void com_shared_mem_set_sys_status (e_cpu_id_t const cpu_idx, e_rcs_sys_status_t const status)
{
    rcs_sys_status_block_t *p_sys_info = com_shared_mem_get_sys_status_block (cpu_idx);
    p_sys_info->sys_status = status;
}

/** ---------------------------------------------------------------------------------------------------------------------
 * @brief           Get CPU status in the shared memory status block..
 * @param [in]      cpu_idx:   CPU being updated.
 * @return          status:  CPU status.
 */
e_rcs_sys_status_t com_shared_mem_get_sys_status (e_cpu_id_t const cpu_idx)
{
    rcs_sys_status_block_t *p_sys_info = com_shared_mem_get_sys_status_block (cpu_idx);
    return p_sys_info->sys_status;
}

/**
 * @brief           Update CPU loop_count in the shared memory status block.
 * @param [in]      cpu_idx:   CPU being updated.
 * @param [in]      status:  New CPU counter.
 * @return          nothing.
 */
void com_shared_mem_set_cpu_loop_count (e_cpu_id_t const cpu_idx, uint32_t count)
{
    rcs_sys_status_block_t *p_sys_info = com_shared_mem_get_sys_status_block (cpu_idx);
    p_sys_info->loop_count = count;
}

/**
 * @brief           After power-up RSM may be busy while it zeros the content. Wait for RSM to be stable. For AX core only.
 * @param [in]      none
 * @return          true, memory ready.   false, timeout.
 */
bool com_shared_mem_wait_for_ready (void)
{
    int timeout_limit = RSM_LOOP_LIMIT;
    volatile rcs_gpreg_ext_irq_grp_reg_t *p_ext_irq_grp = RCS_GPREG_EXT_IRQ_GRP_REG;

    while (timeout_limit > 0)
    {
        if (p_ext_irq_grp->RCS_RSM_ZEROIZE_BUSY)
        {
            timeout_limit--;
        }
        else
        {
            volatile rcs_gpreg_rcs_cfg_reg_t gpreg_rcs_cfg = *RCS_GPREG_RCS_CFG_REG;
            gpreg_rcs_cfg.RCS_RSM_ZEROIZE = 0;
            *RCS_GPREG_RCS_CFG_REG = gpreg_rcs_cfg;
            return (true);
        }
    }
    return (false);
}

/**
 * @brief           Get queue address from memory
 * @param [in]      queue type
 * @return          address of the passed in queue
 */

msg_queue_t *com_shared_mem_get_queue_block (e_queue_type_t queue_idx)
{
    msg_queue_t *p_msg_queue_addr = (msg_queue_t *)&(p_system_data->rcs_msg_queue[queue_idx]);
    return (p_msg_queue_addr);
}

/**
 * @brief           Get quad status from memory
 * @param [in]      fsm id TX/RX , quad type
 * @return          address of the passed in quad
 */

fsm_quad_data_t *com_shared_mem_get_fsm_quad_status_block (e_fsm_type_t fsm_id)
{
    fsm_quad_data_t *p_fsm_quad_data_addr = (fsm_quad_data_t *)&(p_system_data->fsm_quad_data[fsm_id]);
    return (p_fsm_quad_data_addr);
}

/**
 * @brief           Get fsm status from memory
 * @param [in]      fsm id TX/RX
 * @return          address of fsm status
 */

fsm_data_t *com_shared_mem_get_fsm_status_block (e_fsm_type_t fsm_id)
{
    fsm_data_t *p_fsm_data_addr = (fsm_data_t *)&(p_system_data->fsm_data[fsm_id]);
    return (p_fsm_data_addr);
}
