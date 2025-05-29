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

#ifndef COM_SHARED_MEMORY_H_
#define COM_SHARED_MEMORY_H_

#include "com_definitions.h"
#include "com_shared_memory_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief           Get sys status in the shared memory status block..
 * @param [in]      cpu_idx:   CPU being updated.
 * @return          status:  CPU status.
 */
e_rcs_sys_status_t com_shared_mem_get_sys_status (e_cpu_id_t const cpu_idx);

/**
 * @brief           Update sys status in the shared memory status block..
 * @param [in]      cpu_idx: CPU being updated.
 * @param [in]      status: New CPU status.
 * @return          nothing.
 */
void com_shared_mem_set_sys_status (e_cpu_id_t const cpu_idx, e_rcs_sys_status_t status);

/**
 * @brief           Update CPU loop_count in the shared memory status block..
 * @param [in]      cpu_idx:   CPU being updated.
 * @param [in]      status:  New CPU counter.
 * @return          nothing.
 */
void com_shared_mem_set_cpu_loop_count (e_cpu_id_t const cpu_idx, uint32_t count);

/**
 * @brief           After power-up RSM may be busy while it zeros the content.   Wait for RSM to be stable
 * @param [in]      none
 * @return          true, memory ready.   false, timeout.
 */
bool com_shared_mem_wait_for_ready (void);

/**
 * @brief           Get queue address from memory
 * @param [in]      queue type
 * @return          address of the passed in queue
 */

msg_queue_t *com_shared_mem_get_queue_block (e_queue_type_t queue_idx);

/**
 * @brief           Get quad status from memory
 * @param [in]      fsm id TX/RX
 * @return          address of the passed in quad
 */

fsm_quad_data_t *com_shared_mem_get_fsm_quad_status_block (e_fsm_type_t fsm_id);

/**
 * @brief           Get fsm status from memory
 * @param [in]      fsm id TX/RX
 * @return          address of fsm status
 */

fsm_data_t *com_shared_mem_get_fsm_status_block (e_fsm_type_t fsm_id);

#ifdef __cplusplus
}
#endif

#endif /* COM_SHARED_MEMORY_H_ */
