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
#ifndef COM_MSG_HANDLER_UTILS_H
#define COM_MSG_HANDLER_UTILS_H

#include "com_queue.h"
#include "com_isr.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum
{
    e_SCHEDULED = 1,                          /** the macro has been scheduled */
    e_IMMEDIATE_EXEC = 2,                     /** the macro has been scheduled for immediate execution */
    e_ERR_MAX_LEAD_TIME_VIOLATION = 4,        /** the macro's max lead time has been violated (macro ts too far in the future) */
    e_ERR_MIN_LEAD_TIME_VIOLATION = 8,        /** the macro's max lead time has been violated (macro received too late) */
    e_ERR_INTERNAL_SETUP_TIME_VIOLATION = 16, /** the macro's internal setup time has been violated (macro received too late) */
    e_ERR_TIMERS_NOT_SYNCED = 32              /** macro received while timers are not synced */
} e_schedule_type_t;

typedef enum
{
    e_TX_QUEUE_MB_IRQ = e_EXT_TO_RCS0,
    e_TX_SPI_MB_IRQ = e_EXT_TO_RCS1,
    e_RX_QUEUE_MB_IRQ = e_EXT_TO_RCS2,
    e_RX_SPI_MB_IRQ = e_EXT_TO_RCS3,
    e_AD_QUEUE_MB_IRQ = e_EXT_TO_RCS4,
    e_RB_QUEUE_MB_IRQ = e_EXT_TO_RCS5,
    e_TX_SPI_PWR_MB_IRQ = e_EXT_TO_RCS6,
    e_RX_SPI_GAIN_MB_IRQ = e_EXT_TO_RCS7 ,
    e_NUM_EXT_TO_RCS_MB_IRQ = e_NUM_EXT_TO_RCS,
    e_AX_TO_TX_RM_MB_IRQ = e_RCS_TO_RCS0,
    e_AX_TO_RX_RM_MB_IRQ = e_RCS_TO_RCS1,
    e_NUM_TX_MB_IRQ = 2,
    e_NUM_RX_MB_IRQ = 2,
    e_NUM_AD_MB_IRQ = 5,
    e_NUM_MB_IRQ = e_NUM_COM_INT_MB_SEL
} e_msg_mb_irq_type_t;

typedef void (*msg_hdlr_func_t) (void *data);
typedef void (*msg_range_check_func_t) (msg_t *const p_msg);

typedef struct
{
    msg_hdlr_func_t p_msg_hdlr_f;           // callback function for message handling
    msg_range_check_func_t p_range_check_f; // call back function for range checking
    uint32_t opcode;                        // opcode from message
    uint32_t ref_act_ts;                    // reference activation timestamp as per spec
    uint32_t set_up_ts;                     // set up time stamp as per spec
    bool is_schedulable;
} msg_hdlr_t;

typedef struct
{
    e_msg_mb_irq_type_t msg_mb_irq;
    f_isr_handler_t msg_isr_handler;
} msg_irq_hdlr_map_t;

/**
 * @brief           returns opcode field from the message
 * @param [in]      pointer to message
 * @return          opcode field in the message.
 */
uint32_t com_msg_get_opcode (msg_t const *const p_msg);

/**
 * @brief           retrieves internal timings and callback functions from LUT
 * @param [in]      opcode, pointer to ref LUT
 * @return          values from LUT
 */
msg_hdlr_t const *com_msg_init_handler (uint32_t opcode, msg_hdlr_t *msg_hdlr_lut);

/**
 * @brief           Evaluate the message and schedule execution at a later time, or execute in-line.
 * @param [in]      the message to process, possible message handlers, and the originating message queue.
 * @return          status -error / direct execution/ schedulable
 */

uint32_t com_msg_schedule_macro (msg_t *const p_msg, msg_hdlr_t *msg_hdlr_lut, e_queue_type_t queue_id);

/**
 * @brief           Checks if the lead time passes the min ,max and direct execution thresholds
 * @param [in]      activation_timestamp, lead time and message handler struct which holds LUT values
 * @return          status -error / direct execution/ schedulable
 */

uint32_t com_msg_check_lead_time (uint32_t activation_timestamp, uint32_t t_lead_time, msg_hdlr_t const *msg_hdlr);

/**
 * @brief           initializes reference timestamp LUT
 * @param [in]      none
 * @return          none
 */
void com_msg_timestamp_init ();

/**
 * @brief           sets the time ref_time stamp
 * @param [in]      ref_id , time offset
 * @return          absolute time
 */

void com_msg_ref_timestamp_set (uint32_t const ref_id, uint32_t const new_ref);

/**
 * @brief           sends readback message
 * @param [in]      message , length of message in words
 * @return          none
 */

void com_msg_send_readback (msg_t *const msg, const uint32_t msg_len_word);

/**
 * @brief           initializes the message mailbox ISRs and enables the corresponding interrupt
 * @param [in]      pointer to msg irq LUT and lut length
 * @return          none
 */
void com_msg_init_mb_irq (msg_irq_hdlr_map_t *msg_irq_hdlr_map, uint32_t lut_length);

/**
 * @brief           clears the msg mb irq
 * @param [in]      msg irq num
 * @return          none
 */
void com_msg_clear_mb_irq (e_msg_mb_irq_type_t msg_mb_irq_num);

#endif
