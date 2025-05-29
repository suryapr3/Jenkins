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
#ifndef _COM_LOCK_H_
#define _COM_LOCK_H_

#include <stdbool.h>
#include "com_definitions.h"
#include "com_shared_memory.h"
#include <xtensa/tie/xt_core.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOCK_SPIN_DELAY (16)

typedef enum
{
    e_UNLOCKED,
    e_LOCKED
} e_lock_state_t;

// counter defined in custom_vectors.S to track num of times exception 11 occurs:
extern uint32_t exception_11_cnt;
extern volatile int32_t *com_shm_lock_first_addr;
extern volatile int32_t *com_shm_lock_last_addr;

/**
 * @brief           delay with NOP instruction
 * @param [in]      int : count of cycles
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void com_lock_spin_delay (int delay_cnt)
{
    for (int i = 0; i < delay_cnt; i++) { __asm__ volatile ("_nop"); }
}

/**
 * @brief           using exclusive access instructions to set LOCK
 * @param [in]      p_lock: pointer to lock mem
 * @return          int32_t : 1 if set LOCK success, 0 otherwise
 */
static INTRINSIC_ALWAYS_INLINE int32_t com_lock_exclusive_set (volatile int32_t *p_lock)
{
    int32_t result = 0;
    int32_t tmp = e_LOCKED;
    ATOMIC_BEGIN
    int32_t val = XT_L32EX (p_lock);
    if (val == e_UNLOCKED)
    {
        XT_S32EX (tmp, (volatile int32_t *)p_lock); // 1st parameter of XT_S32EX needs to be a variable
        XT_GETEX (result);
    }
    ATOMIC_END

    return result;
}

/**
 * @brief           spin to acquire lock. this is a blocking call
 *                  Note, the acquired LOCK must be released with call to com_lock_release
 * @param [in]      enum: specify which lock to acquire
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void com_lock_acquire (e_lock_t lock)
{
#if UNIT == 0
    while (com_lock_exclusive_set ((volatile int32_t *)&p_system_data->shm_lock[lock]) == 0) { com_lock_spin_delay (LOCK_SPIN_DELAY); }
#endif
}

/**
 * @brief           release an acquired lock. this is an unblocking call
 * @param [in]      enum: specify which lock to release
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void com_lock_release (e_lock_t lock)
{
#if UNIT == 0
    /* Flush all previous writes before releasing lock with L32EX/S32EX */
    INTRINSIC_BARRIER;
    p_system_data->shm_lock[lock] = e_UNLOCKED;
#endif
}

/**
 * @brief           check lock state. this is an unblocking call
 * @param [in]      enum: specify which lock to check
 * @return          bool: true if in LOCK state, false otherwise
 */
static INTRINSIC_ALWAYS_INLINE bool com_lock_is_locked (e_lock_t lock)
{
    return (p_system_data->shm_lock[lock] == e_LOCKED) ? true : false;
}

/**
 * @brief           initializing shm_lock[], clear EXCLMON.
 *                  should be called in powerup/init stage, and only called from one core in multi-core case
 * @param [in]      none
 * @return          none
 */
void com_lock_init (void);

/**
 * @brief           initializing boundary check flags, should be called in powerup/init stage
 * @param [in]      none
 * @return          none
 */
void com_lock_boundary_check_init ();

#ifdef __cplusplus
}
#endif

#endif /* _COM_LOCK_H_ */

