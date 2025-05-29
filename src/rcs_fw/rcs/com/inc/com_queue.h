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
#ifndef COMMON_QUEUE_H
#define COMMON_QUEUE_H

#include "com_queue_def.h"
#include "com_msg_def.h"
#include <stdbool.h>
#include <stdint.h>

void com_queue_init (msg_queue_t *p_msg_queue);
e_queue_ret_status_t com_queue_insert (msg_queue_t *p_msg_queue, msg_t *const msg, const uint32_t msg_len_word);
e_queue_ret_status_t com_queue_read (msg_queue_t *p_msg_queue, msg_t *p_msg, uint32_t *msg_len);
void com_queue_dump (msg_queue_t *p_msg_queue);

#endif
