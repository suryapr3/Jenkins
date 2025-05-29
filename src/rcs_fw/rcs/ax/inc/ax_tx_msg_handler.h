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
#ifndef AX_TX_MSG_HANDLER_H
#define AX_TX_MSG_HANDLER_H

#include <stdbool.h>
#include <stdint.h>
#include "com_msg_handler_utils.h"

extern msg_hdlr_t ax_tx_hdlr_lut[];
/**
 * @brief           message handler for TX queue messages
 * @param [in]      none
 * @return          none
 */
void ax_tx_queue_msg_handler_irq (void *unused);

/**
 * @brief           ISR for DL SPI messages.Reads the data, store the message in an event.
 * @param [in]      none
 * @return          none
 */

void ax_tx_spi_msg_handler_irq (void *unused);

/**
 * @brief           copies the message into the Radio message queue
 * @param [in]      message
 * @return          none
 */

void ax_tx_activate_handler (void *data);

#endif
