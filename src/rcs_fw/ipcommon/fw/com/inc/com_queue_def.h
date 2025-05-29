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
#ifndef COMMON_QUEUE_DEF_H
#define COMMON_QUEUE_DEF_H

#include <stdbool.h>
#include <stdint.h>

#define QUEUE_LEN_MAX    16 // number of messages in queue
#define MSG_LEN_MAX      16 // max length of message in words
#define LEN_IN_WORD(len) (len / 4)
#define LEN_IN_BYTE(len) (len * 4)

typedef enum
{
    e_ADMIN_QUEUE,
    e_TX_QUEUE,
    e_RX_QUEUE,
    e_RB_QUEUE,
    e_TX_RM_QUEUE,
    e_RX_RM_QUEUE,
    e_RM2_QUEUE,
    e_RM3_QUEUE,
    e_MAX_NUM_QUEUE,
    e_TX_SPI_REG_QUEUE, // not a queue , but MB register block
    e_RX_SPI_REG_QUEUE, // not a queue , but MB register block
} e_queue_type_t;

typedef enum
{
    e_RET_QUEUE_SUCCESS,
    e_RET_QUEUE_FULL,
    e_RET_QUEUE_EMPTY,
    e_RET_QUEUE_ERR
} e_queue_ret_status_t;

typedef union {
    struct
    {
        uint32_t msg_len_word : 8; // length of received msg in words
        uint32_t msg_time : 24;    // message reception time
    };
    uint32_t value;
} queue_msg_metadata_t;

typedef struct
{
    queue_msg_metadata_t queue_msg_metadata;
    uint32_t msg_data_word[MSG_LEN_MAX];
} queue_msg_element_t;

typedef struct
{
    uint32_t get_index;     // read ptr
    uint32_t get_indicator; // read indicator
} msg_queue_get_idx_t;

typedef struct
{
    uint32_t put_index;     // write ptr
    uint32_t put_indicator; // write_indicator
} msg_queue_put_idx_t;

typedef struct
{
    msg_queue_get_idx_t msg_queue_get_idx;
    msg_queue_put_idx_t msg_queue_put_idx;
    queue_msg_element_t queue_msg_element[QUEUE_LEN_MAX];
} msg_queue_t;

#ifndef RCS
/*! @fn e_queue_ret_status_t fw_msg_queue_insert (void *dev_handle, msg_queue_t *p_msg_queue, void *const p_msg, const int32_t
   msg_len_word);
    @brief Insert a message into a message queue, host-side interface.
    @param dev_handle Incoming handle of the current device module instance, opaquely passed through to device read/write.
    @param p_msg_queue pointer to the message queue
    @param p_msg pointer to the message
    @param msg_len_word length of the message in words (4-byte quantities).
*/

e_queue_ret_status_t fw_msg_queue_insert (void *dev_handle, msg_queue_t *p_msg_queue, void *const p_msg, const int32_t msg_len_word);

/*! @fn e_queue_ret_status_t fw_msg_queue_read (void *dev_handle, msg_queue_t *p_msg_queue, void *p_msg, int32_t *msg_len);
    @brief Read a message from a message queue, host-side interface.
    @param dev_handle Incoming handle of the current device module instance, opaquely passed through to device read/write.
    @param p_msg_queue pointer to the message queue
    @param p_msg pointer to the message
    @param msg_len length of the message retrieved in words (4-byte quantities).
*/

e_queue_ret_status_t fw_msg_queue_read (void *dev_handle, msg_queue_t *p_msg_queue, void *p_msg, int32_t *msg_len);

/*! @fn fw_msg_queue_dump (void *dev_handle, msg_queue_t *p_msg_queue, msg_queue_t *p_msg_queue_local);
    @brief Read the entire queue structure and return it to a local buffer.
    @param dev_handle Incoming handle of the current device module instance, opaquely passed through to device read/write.
    @param p_msg_queue pointer to the message queue
    @param p_msg_queue_local pointer to the local buffer to copy the message queue into.
*/

void fw_msg_queue_dump (void *dev_handle, msg_queue_t *p_msg_queue, msg_queue_t *p_msg_queue_local);

#endif

#endif
