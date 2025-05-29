/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2024 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to
 ** the source code ("Material") are owned by Intel Corporation or its
 ** suppliers or licensors. Title to the Material remains with
 ** Intel Corporation or its suppliers and licensors.
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is
 ** protected by worldwide copyright and trade secret laws and treaty
 ** provisions. No part of the Material may be used, copied, reproduced,
 ** modified, published, uploaded, posted, transmitted, distributed, or
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other
 ** intellectual property right is granted to or conferred upon you by
 ** disclosure or delivery of the Materials, either expressly, by implication,
 ** inducement, estoppel or otherwise. Any license under such intellectual
 ** property rights must be express and approved by Intel in writing.
 *************************************************************************/
#include <stdbool.h>
#include <string.h>

#include "com_queue_def.h"
#include "com_device_api.h"

static uint32_t fw_msg_queue_get_next_index (int32_t indicator)
{
    return ((indicator) % (QUEUE_LEN_MAX));
}

static uint32_t fw_msg_queue_get_next_indicator (int32_t indicator)
{
    return ((indicator + 1) % (2 * QUEUE_LEN_MAX));
}
static bool fw_msg_queue_check_empty (int32_t const put_indicator, int32_t const get_indicator)
{
    return (put_indicator == get_indicator);
}

static bool fw_msg_queue_check_full (int32_t const put_indicator, int32_t const get_indicator)
{
    return ((put_indicator - get_indicator) == QUEUE_LEN_MAX);
}

e_queue_ret_status_t fw_msg_queue_insert (void *dev_handle, msg_queue_t *p_msg_queue, void *const p_msg, const int32_t msg_len_word)
{
    e_queue_ret_status_t status = e_RET_QUEUE_SUCCESS;
    msg_queue_put_idx_t write_ptr;
    msg_queue_get_idx_t read_ptr;

    dev_mem_read (dev_handle, &write_ptr, &p_msg_queue->msg_queue_put_idx, sizeof (msg_queue_put_idx_t));
    dev_mem_read (dev_handle, &read_ptr, &p_msg_queue->msg_queue_get_idx, sizeof (msg_queue_get_idx_t));

    if (fw_msg_queue_check_full (write_ptr.put_indicator, read_ptr.get_indicator))
    {
        status = e_RET_QUEUE_FULL;
    }
    else
    {
        queue_msg_metadata_t queue_msg_metadata;

        if (write_ptr.put_index >= QUEUE_LEN_MAX)
        {
            status = e_RET_QUEUE_ERR;
        }
        else
        {
            queue_msg_metadata.msg_len_word = msg_len_word;
            queue_msg_metadata.msg_time = 0;
            queue_msg_element_t queue_msg_elem;

            memset (&queue_msg_elem, 0, sizeof (queue_msg_element_t));

            // error check - buffer sizing
            queue_msg_elem.queue_msg_metadata = queue_msg_metadata;

            memcpy (queue_msg_elem.msg_data_word, p_msg, LEN_IN_BYTE (msg_len_word));

            dev_mem_write (dev_handle, &p_msg_queue->queue_msg_element[write_ptr.put_index], &queue_msg_elem, sizeof (queue_msg_element_t));
            // Barrier
            write_ptr.put_indicator = fw_msg_queue_get_next_indicator (write_ptr.put_indicator);
            write_ptr.put_index = fw_msg_queue_get_next_index (write_ptr.put_indicator);
            dev_mem_write (dev_handle, &p_msg_queue->msg_queue_put_idx, &write_ptr, sizeof (msg_queue_put_idx_t));
        }
    }

    return status;
}

e_queue_ret_status_t fw_msg_queue_read (void *dev_handle, msg_queue_t *p_msg_queue, void *p_msg, int32_t *msg_len)
{
    e_queue_ret_status_t status = e_RET_QUEUE_SUCCESS;
    msg_queue_put_idx_t write_ptr;
    msg_queue_get_idx_t read_ptr;

    dev_mem_read (dev_handle, &write_ptr, &p_msg_queue->msg_queue_put_idx, sizeof (msg_queue_put_idx_t));
    dev_mem_read (dev_handle, &read_ptr, &p_msg_queue->msg_queue_get_idx, sizeof (msg_queue_get_idx_t));

    if (fw_msg_queue_check_empty (write_ptr.put_indicator, read_ptr.get_indicator))
    {
        status = e_RET_QUEUE_EMPTY;
    }
    else
    {
        queue_msg_metadata_t queue_msg_metadata;

        if (read_ptr.get_index >= QUEUE_LEN_MAX)
        {
            status = e_RET_QUEUE_ERR;
        }
        else
        {
            dev_mem_read (dev_handle, &queue_msg_metadata, &p_msg_queue->queue_msg_element[read_ptr.get_index].queue_msg_metadata,
                          sizeof (queue_msg_metadata_t));
            dev_mem_read (dev_handle, p_msg, &p_msg_queue->queue_msg_element[read_ptr.get_index].msg_data_word,
                          LEN_IN_BYTE (queue_msg_metadata.msg_len_word));
            *msg_len = queue_msg_metadata.msg_len_word;
            // Barrier ?
            read_ptr.get_indicator = fw_msg_queue_get_next_indicator (read_ptr.get_indicator);
            read_ptr.get_index = fw_msg_queue_get_next_index (read_ptr.get_indicator);
            dev_mem_write (dev_handle, &p_msg_queue->msg_queue_get_idx, &read_ptr, sizeof (msg_queue_get_idx_t));
        }
    }

    return status;
}

void fw_msg_queue_dump (void *dev_handle, msg_queue_t *p_msg_queue, msg_queue_t *p_msg_queue_local)
{
    int i;
    for (i = 0; i < QUEUE_LEN_MAX; i++)
    {
        dev_mem_read (dev_handle, &p_msg_queue_local->queue_msg_element[i], &p_msg_queue->queue_msg_element[i],
                      sizeof (queue_msg_element_t));

        // Leave logging to the caller.
        // printf ("p_msg_queue->queue_msg_element[i].queue_msg_metadata.msg_len  = %d\n", queue_msg_elem.queue_msg_metadata.msg_len_word);
        // for (int j = 0; j < MSG_LEN_MAX; j++) { printf ("data [%d][%d]= 0x%x\n", i, j, queue_msg_elem.msg_data_word[j]); }
    }
}
