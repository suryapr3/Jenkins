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
#ifndef RX_MSG_HANDLER_H
#define RX_MSG_HANDLER_H

#include "com_queue.h"
#include "com_msg_handler_utils.h"
#include <stdbool.h>
#include <stdint.h>

extern msg_irq_hdlr_map_t rx_msg_irq_hdlr_map[e_NUM_RX_MB_IRQ];

/**
 * @brief           callback function for RX config ant_grp message
 * @param [in]      RX config ant_grp message
 * @return          none
 */

void ul_config_ant_grp_handler (void *data);

/**
 * @brief           callback function for RX warmup message
 * @param [in]      TX TX warmup message
 * @return          none
 */

void ul_warmup_handler (void *data);

/**
 * @brief           callback function for RX ON message
 * @param [in]      RX ON message
 * @return          none
 */

void ul_on_handler (void *data);

/**
 * @brief           callback function for RX Update Control message
 * @param [in]      RX Update Control message
 * @return          none
 */

void ul_update_control_handler (void *data);

/**
 * @brief           callback function for RX off message
 * @param [in]      RX off message
 * @return          none
 */

void ul_off_handler (void *data);

/**
 * @brief           checks for violations in RX ant_grp0 config message range spec
 * @param [in]      RX config ant_grp0 message
 * @return          none
 */

/**
 * @brief           callback function for RX set reference message
 * @param [in]      RX set reference message
 * @return          none
 */

void ul_set_time_ref_handler (void *data);

/**
 * @brief           message handler for RX messages
 * @param [in]      none
 * @return          none
 */

void ul_spi_on_handler (void *data);

/**
 * @brief           callback function for RX SPI off message
 * @param [in]      RX SPI off message
 * @return          none
 */

void ul_spi_off_handler (void *data);

#endif
