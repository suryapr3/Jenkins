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
 * @file    com_queue.c
 * @brief   Common functions for handling message queues.
 * @details Contains the APIs for message queues.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_queue.h"

#ifdef PRE_SIL_TEST
#include "presil_com_assert.h"
#include "presil_com_print.h"
#include "presil_com_shared_memory_read_write.h"
#else
#include "com_assert.h"
#include "com_print.h"
#include "com_shared_memory_read_write.h"
#include <xtensa/core-macros.h>
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define QUEUE_WRPTR_INIT_VALUE (0)
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

static uint32_t get_next_index (int32_t indicator)
{
    return ((indicator) % (QUEUE_LEN_MAX));
}

static uint32_t get_next_indicator (int32_t indicator)
{
    return ((indicator + 1) % (2 * QUEUE_LEN_MAX));
}
static bool com_queue_check_empty (uint32_t const put_indicator, uint32_t const get_indicator)
{
    return (put_indicator == get_indicator);
}

static bool com_queue_check_full (uint32_t const put_indicator, uint32_t const get_indicator)
{
    return ((put_indicator - get_indicator) == QUEUE_LEN_MAX);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Initializes the queue.
 * @param [in]      pointer to queue , max number of messages that can be inserted into queue , max message length in words
 * @return          void.
 */

void com_queue_init (msg_queue_t *p_msg_queue)
{
    msg_queue_get_idx_t queue_get_idx = {.get_index = QUEUE_WRPTR_INIT_VALUE, .get_indicator = QUEUE_WRPTR_INIT_VALUE};
    msg_queue_put_idx_t queue_put_idx = {.put_index = QUEUE_WRPTR_INIT_VALUE, .put_indicator = QUEUE_WRPTR_INIT_VALUE};

    com_shared_mem_write (&p_msg_queue->msg_queue_get_idx, &queue_get_idx, sizeof (msg_queue_get_idx_t));
    com_shared_mem_write (&p_msg_queue->msg_queue_put_idx, &queue_put_idx, sizeof (msg_queue_put_idx_t));

}

/**
 * @brief           Insert elements to queue.
 * @param [in]      pointer to queue , message input, message length in words
 * @return          status of insert operation- success / queue full.
 */
e_queue_ret_status_t com_queue_insert (msg_queue_t *p_msg_queue, msg_t *const msg, const uint32_t msg_len_word)
{
    e_queue_ret_status_t status = e_RET_QUEUE_SUCCESS;
    msg_queue_put_idx_t write_ptr;
    msg_queue_get_idx_t read_ptr;

    com_shared_mem_read (&write_ptr, &p_msg_queue->msg_queue_put_idx, sizeof (msg_queue_put_idx_t));
    com_shared_mem_read (&read_ptr, &p_msg_queue->msg_queue_get_idx, sizeof (msg_queue_get_idx_t));


    if (com_queue_check_full (write_ptr.put_indicator, read_ptr.get_indicator))
    {
        RT_ASSERT_HERE ();
        FW_PRINT (FW_INFO, "Queue is FULL !!");
        status = e_RET_QUEUE_FULL;
        return (status);
    }
    else
    {
        queue_msg_element_t queue_msg_elem;
        memset (&queue_msg_elem, 0, sizeof (queue_msg_element_t));

        FW_PRINT (FW_INFO, "Filling queue");
        // error check - buffer sizing
        queue_msg_elem.queue_msg_metadata.msg_len_word = msg_len_word;
        queue_msg_elem.queue_msg_metadata.msg_time = 0;
        memcpy (queue_msg_elem.msg_data_word, msg, LEN_IN_BYTE (msg_len_word));
        FW_PRINT (FW_INFO, "message size = %d", msg_len_word);

        com_shared_mem_write (&p_msg_queue->queue_msg_element[write_ptr.put_index], &queue_msg_elem, sizeof (queue_msg_element_t));
#ifndef PRE_SIL_TEST
        INTRINSIC_BARRIER;
#endif
        write_ptr.put_indicator = get_next_indicator (write_ptr.put_indicator);
        write_ptr.put_index = get_next_index ( write_ptr.put_indicator);
        com_shared_mem_write (&p_msg_queue->msg_queue_put_idx, &write_ptr, sizeof (msg_queue_put_idx_t));

        FW_PRINT (FW_INFO, "put_indicator = %d rear = %d front = %d ", write_ptr.put_indicator, write_ptr.put_index, read_ptr.get_index);

        return (status);
    }
}

/**
 * @brief           Reads elements from queue.
 * @param [in]      pointer to queue to be read, pointer to store read message , length of message read
 * @return          status of read operation - success/ queue empty.
 */
e_queue_ret_status_t com_queue_read (msg_queue_t *p_msg_queue, msg_t *p_msg, uint32_t *msg_len)
{

    e_queue_ret_status_t status = e_RET_QUEUE_SUCCESS;
    msg_queue_put_idx_t write_ptr;
    msg_queue_get_idx_t read_ptr;
    com_shared_mem_read (&write_ptr, &p_msg_queue->msg_queue_put_idx, sizeof (msg_queue_put_idx_t));
    com_shared_mem_read (&read_ptr, &p_msg_queue->msg_queue_get_idx, sizeof (msg_queue_get_idx_t));

    if (com_queue_check_empty (write_ptr.put_indicator, read_ptr.get_indicator))
    {
       // RT_ASSERT_HERE ();
        FW_PRINT (FW_INFO, "Queue is EMPTY !!");
        status = e_RET_QUEUE_EMPTY;
        return (status);
    }
    else
    {

        queue_msg_metadata_t queue_msg_metadata;

        com_shared_mem_read (&queue_msg_metadata, &p_msg_queue->queue_msg_element[read_ptr.get_index].queue_msg_metadata,
                             sizeof (queue_msg_metadata_t));
        com_shared_mem_read (p_msg, &p_msg_queue->queue_msg_element[read_ptr.get_index].msg_data_word,
                             LEN_IN_BYTE (queue_msg_metadata.msg_len_word));
        *msg_len = queue_msg_metadata.msg_len_word;
#ifndef PRE_SIL_TEST
        INTRINSIC_BARRIER;
#endif
        read_ptr.get_indicator = get_next_indicator (read_ptr.get_indicator);
        read_ptr.get_index = get_next_index (read_ptr.get_indicator);
        com_shared_mem_write (&p_msg_queue->msg_queue_get_idx, &read_ptr, sizeof (msg_queue_get_idx_t));

        FW_PRINT (FW_INFO, "get_indicator = %d  rear = %d front = %d", read_ptr.get_indicator, write_ptr.put_index, read_ptr.get_index);

        return (status);
    }
}

/**
 * @brief           Dumps all elements in the queue.
 * @param [in]      pointer to queue
 * @return          void.
 */
void com_queue_dump (msg_queue_t *p_msg_queue)
{
    for (int i = 0; i < QUEUE_LEN_MAX; i++)
    {
        queue_msg_element_t queue_msg_elem;
        com_shared_mem_read (&queue_msg_elem, &p_msg_queue->queue_msg_element[i], sizeof (queue_msg_element_t));
        FW_PRINT (FW_INFO, "p_msg_queue->queue_msg_element[i].queue_msg_metadata.msg_len  = %d",
                  queue_msg_elem.queue_msg_metadata.msg_len_word);
        for (int j = 0; j < MSG_LEN_MAX; j++) { FW_PRINT (FW_INFO, "data [%d][%d]= 0x%x", i, j, queue_msg_elem.msg_data_word[j]); }
    }
}
