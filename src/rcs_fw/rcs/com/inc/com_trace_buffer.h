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
#ifndef COMMON_TRACE_BUFFER_H
#define COMMON_TRACE_BUFFER_H

#include "com_msgs_enum.h"

#define TRACE_BUFF_LUT_SIZE_WORDS (256)

#define DEBUG_TRACE_TIME_SYNC 0

#define TIMER_IRQ_HANDLER 0
#define GPDMA_IRQ_HANDLER 1
#define MB_IRQ_HANDLER    2

#define TX_MSG       (0x20)
#define RX_MSG       (0x40)
#define AX_RX_MSG    (0x60)
#define AX_TX_MSG    (0x80)
#define SPI_MSG      (0x08)
#define DIRQ_MSG     (0x10)
#define IRQ_MSG      (0x18)
#define ON_MSG       (0x01)
#define OFF_MSG      (0x02)
#define CFG_MSG      (0x03)
#define UC_MSG       (0x04) // update control
#define ACTIVATE_MSG (0x05)
#define RM_MSG       (0x06)
#define WARMUP_MSG   (0x07)

#define TX_ON_MSG     (TX_MSG | ON_MSG)
#define TX_OFF_MSG    (TX_MSG | OFF_MSG)
#define TX_ON_SMSG    (TX_MSG | ON_MSG | SPI_MSG)
#define TX_OFF_SMSG   (TX_MSG | OFF_MSG | SPI_MSG)
#define TX_DIRQ_MSG   (TX_MSG | DIRQ_MSG)
#define TX_IRQ_RM_MSG (TX_MSG | IRQ_MSG | RM_MSG)
#define TX_CONFIG_MSG (TX_MSG | CFG_MSG)
#define TX_UC_MSG     (TX_MSG | UC_MSG)
#define TX_UC_SMSG    (TX_MSG | UC_MSG | SPI_MSG)
#define TX_WARMUP_MSG (TX_MSG | WARMUP_MSG)

#define RX_ON_MSG     (RX_MSG | ON_MSG)
#define RX_OFF_MSG    (RX_MSG | OFF_MSG)
#define RX_ON_SMSG    (RX_MSG | ON_MSG | SPI_MSG)
#define RX_OFF_SMSG   (RX_MSG | OFF_MSG | SPI_MSG)
#define RX_DIRQ_MSG   (RX_MSG | DIRQ_MSG)
#define RX_IRQ_RM_MSG (RX_MSG | IRQ_MSG | RM_MSG)
#define RX_CONFIG_MSG (RX_MSG | CFG_MSG)
#define RX_UC_MSG     (RX_MSG | UC_MSG)
#define RX_UC_SMSG    (RX_MSG | UC_MSG | SPI_MSG)
#define RX_WARMUP_MSG (RX_MSG | WARMUP_MSG)

#define AX_RX_IRQ_SMSG      (AX_RX_MSG | SPI_MSG)
#define AX_RX_IRQ_MSG       (AX_RX_MSG | IRQ_MSG)
#define AX_RX_DELAY_SMSG    (AX_RX_MSG | DIRQ_MSG)
#define AX_RX_ACTIVATE_SMSG (AX_RX_MSG | ACTIVATE_MSG)

#define AX_TX_IRQ_SMSG      (AX_TX_MSG | SPI_MSG)
#define AX_TX_IRQ_MSG       (AX_TX_MSG | IRQ_MSG)
#define AX_TX_DELAY_SMSG    (AX_TX_MSG | DIRQ_MSG)
#define AX_TX_ACTIVATE_SMSG (AX_TX_MSG | ACTIVATE_MSG)

extern uint32_t com_trace_bfn_cpu_offset;

typedef enum
{
    e_TRACE_FUNC_START,
    e_TRACE_FUNC_END,
    e_TRACE_DEBUG,
    e_TRACE_EXT_DBG_BITS,
    e_TRACE_MSG,
    e_TRACE_USER_DEF = 5,
    e_TRACE_TIMESTAMP,
    e_TRACE_ERR_CODE = 7
} e_trace_buff_type_t;

typedef union {
    struct
    {
        uint32_t TIMESTAMP : 18; // Timestamp/4.
        uint32_t FUNCTION_ID : 11;
        e_trace_buff_type_t TYPE : 3;
    };
    uint32_t value;
} func_trace_t;

typedef union {
    struct
    {
        uint32_t TRACE_INFO : 18;
        uint32_t MSG_ID : 11;
        e_trace_buff_type_t TYPE : 3;
    };
    uint32_t value;
} msg_trace_t;

typedef union {
    struct
    {
        uint32_t DATA : 16;
        uint32_t DATA_COUNT : 4;
        uint32_t DEBUG_LOCATION_ID : 9;
        e_trace_buff_type_t TYPE : 3;
    };
    uint32_t value;
} debug_trace_t;

typedef union {
    struct
    {
        uint32_t RES : 9;
        uint32_t DATA_COUNT : 4;
        e_error_type_t LVL : 2;
        e_error_code_type_t CODE : 14;
        e_trace_buff_type_t TYPE : 3;
    };
    uint32_t value;
} err_code_trace_t;

typedef union {
    struct
    {
        uint32_t DATA : 16;
        uint32_t DATA_COUNT : 4;
        uint32_t DEBUG_LOCATION_ID : 9;
        e_trace_buff_type_t TYPE : 3;
    };
    uint32_t value;
} user_defined_trace_t;

/*
 * @brief           Trace functions/handlers and record Timestamp
 * @param [in]      Trace_type, function Id, timestamp
 * @return          none.
 */
void com_func_ts_trace_buffer (uint32_t trc_type, uint32_t trc_info);

/*
 * @brief           Trace messages/events sequence
 * @param [in]      Trace_type, function Id, trace_info
 * @return          none.
 */
void com_msg_trace_buffer (uint32_t trc_type, uint32_t trc_info, uint32_t trace_info);

/*
 * @brief           Trace to report error code
 * @param [in]      Trace_type, error code, error level
 * @return          none.
 */
void com_err_code_trace_buffer (uint32_t trc_type, e_error_code_type_t err_code, e_error_type_t err_level, uint32_t data_count);

/*
 * @brief           Trace used for debug purpose
 * @param [in]      Trace_type, debug location, no.of debug data, info, data
 * @return          none.
 */
void com_debug_trace_buffer (uint32_t trc_type, uint32_t dbg_location, uint32_t data_count, uint32_t info, const uint32_t data[]);

#endif
