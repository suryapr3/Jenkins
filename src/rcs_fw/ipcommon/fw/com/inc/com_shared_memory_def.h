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

#ifndef COM_SHARED_MEMORY_DEF_H_
#define COM_SHARED_MEMORY_DEF_H_

#include "com_queue_def.h"
#include "com_fsm_def.h"
#include "com_cpu_id.h"

#define TRAX_MEM_SIZE_WORDS       (128)
#define TRAX_HEADER_SIZE_WORDS    (32)
#define TRAX_LUT_SIZE_WORDS       (TRAX_HEADER_SIZE_WORDS + TRAX_MEM_SIZE_WORDS)
#define TRACE_BUFF_LUT_SIZE_WORDS (256)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
#ifdef EX_LOCK_TEST
    e_LOCK_TEST,
#endif
    e_LOCK_RB_MSG,
    e_LOCK_RADIO_MSG,
    e_LOCK_NLEQ,
    e_LOCK_CDAC_DPD0,
    e_LOCK_CDAC_DPD1,
    e_LOCK_CDAC_DPD2,
    e_LOCK_DL_STATE,
    e_LOCK_UL_STATE,
    e_LOCK_GPDMA_RCS0,
    e_LOCK_GPDMA_RCS1,
    e_LOCK_TRX_SHARED_REG, // registers accessed by both UL/DL

    e_LOCK_NUM
} e_lock_t;

typedef enum
{
    e_SYS_STATUS_UNKNOWN,
    e_BOOT_CORE_FW_MISMATCH,
    e_BOOT_TRAX_INIT,
    e_BOOT_TRAX_START,
    e_BOOT_LOCK_INIT,
    e_BOOT_VEX_INIT,
    e_BOOT_FSM_INIT,
    e_BOOT_MSG_Q_INIT,
    e_BOOT_CORES_START,
    e_BOOT_XTHAL_DIS_INT,
    e_BOOT_XTHAL_EN_INT,
    e_BOOT_BFN_INIT,
    e_BOOT_IDMA_INIT,
    e_BOOT_GPDMA_INIT,
    e_BOOT_EVENT_INIT,
    e_BOOT_MSG_ISR,
    e_BOOT_TS_INIT,
    e_BOOT_NLEQ_CAL,
    e_BOOT_ADC_CAL,
    e_BOOT_SYS_READY,

    e_SYS_EXITED,
} e_rcs_sys_status_t;

typedef struct
{
    e_rcs_sys_status_t sys_status;
    uint32_t loop_count;
} rcs_sys_status_block_t;

/**
 * The below structure is mapped to the "system status block" in the shared SRAM.
 * It can be accessed from the external system (RTE) or from other CPUs.
 *
 * We need to make sure that for every CPU this structure is aligned to the same base address.
 * This is currently done in the shared mem C file.
 */
struct rcs_system_status_memory
{
    volatile int32_t shm_lock[e_LOCK_NUM]; // shared mem locks
                                           //// lock protected data blocks begin
#ifdef EX_LOCK_TEST
    volatile int32_t test; // e_LOCK_TEST
#endif

    volatile rcs_sys_status_block_t rcs_sys_status[e_CPUID_NUM_CPUID];
    volatile fsm_data_t fsm_data[e_MAX_NUM_FSM];
    volatile fsm_quad_data_t fsm_quad_data[e_MAX_NUM_FSM];
    volatile msg_queue_t rcs_msg_queue[e_MAX_NUM_QUEUE];

    uint32_t trax_lut[e_CPUID_NUM_CPUID * (TRAX_LUT_SIZE_WORDS)];
    uint32_t trace_buff_lut[e_CPUID_NUM_CPUID * (TRACE_BUFF_LUT_SIZE_WORDS)];
};

// exported to other modules for accessing lock protected data in SRAM:
extern struct rcs_system_status_memory *p_system_data;

#ifdef __cplusplus
}
#endif

#endif /* COM_SHARED_MEMORY_H_ */
