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
#ifndef ADMIN_MSG_HANDLER_H
#define ADMIN_MSG_HANDLER_H

#include "com_queue.h"
#include "com_msg_handler_utils.h"

#include <stdbool.h>
#include <stdint.h>

extern msg_hdlr_t admin_hdlr_lut[];
extern msg_irq_hdlr_map_t admin_msg_irq_hdlr_map[e_NUM_AD_MB_IRQ];
/**
 * @brief           callback function for bfn synch message
 * @param [in]      BFN synch message
 * @return          none
 */

void bfn_sync_handler (void *data);

/**
 * @brief           callback function for warmup message
 * @param [in]      warm up message
 * @return          none
 */

void warmup_handler (void *data);

/**
 * @brief           callback function for cal_config message
 * @param [in]      cal_config message
 * @return          none
 */

void cal_config_handler (void *data);

/**
 * @brief           callback function for reconfig message
 * @param [in]      reconfig message handler
 * @return          none
 */

void reconfig_handler (void *data);

/**
 * @brief           callback function for sleep control message
 * @param [in]      sleep control message
 * @return          none
 */

void sleep_control_handler (void *data);

/**
 * @brief           callback function for shutdown message
 * @param [in]      shutdown message
 * @return          none
 */

void shutdown_handler (void *data);

#endif
