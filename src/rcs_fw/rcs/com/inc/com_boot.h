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
#ifndef COMMON_BOOT_H
#define COMMON_BOOT_H

#include <stdint.h>

#include "com_shared_memory.h"
#include "com_isr.h"
#include "com_queue.h"
#include "com_msg_handler_utils.h"
#include "com_static_data_table.h"

#define BOOT_SYNC_WAIT_CYCLE  (get_tf(com_fw_config_lut,0,fw_boot_iterations))
#define BOOT_SYNC_PAUSE_IN_NS (1000*(get_tf(com_fw_config_lut,0,fw_boot_iteration_delay)))
/**
 * @brief           check loaded FW matching running processor. two cases:
 *                  1. processor with id=0 loaded wrong FW:
 *                     send error readback with cause as e_CORE_FW_MISMATCH to RTE, then enter endless loop
 *                  2. other processor other than id=0 loaded wrong FW:
 *                     just set status to e_BOOT_CORE_FW_MISMATCH for the real running core, then enter endless loop, this
 *                     will eventually cause system timeout, and report to RTE by AX core
 * @param [in]      none
 * @return          none
 */
void core_fw_mismatch_check ();

/*
 * @brief			Get the current FW version
 * @param [in]      none
 * @return          none
 */
void com_get_fw_version ();

/**
 * @brief           check sync-up among all cores with timeout support:
 *                  1. for core0:
 *                     if timeout doesn't happen waiting for other cores:
 *                       update its status to e_BOOT_SYS_READY, sending readback to RTE indicating all cores are ready
 *                     if timeout happens:
 *                       send error readback with cause as e_CORE_SYNC_TIMEOUT to RTE, then enter endless loop
 *                  2. for cores other than core0:
 *                     update its boot status as e_BOOT_SYS_READY
 *                     if timeout doesn't happen waiting for core0 to be ready:
 *                       continue
 *                     if timeout happens:
 *                       send error readback with cause e_CORE_SYNC_TIMEOUT for core0
 * @param [in]      cycles: how many check cycles for timeout check
 *                  pause_in_ns: how long to pause in nano seconds in each check cycle
 * @return          none
 */
void core_sync_up (uint32_t cycles, uint32_t pause_in_ns);

/**
 * @brief           start trace and set trace level
 * @param [in]      none
 * @return          none
 */
void dbg_n_trace ();

/**
 * @brief           common initialization need to be done at boot time
 * @param [in]      none
 * @return          none
 */
void com_boot_init ();

#endif // COMMON_BOOT_H
