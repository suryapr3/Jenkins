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
 * @file    com_trace_buffer.c
 * @brief   Trace Buffer common functions.
 * @details Controls for CPU trace buffer.
 * @todo
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define FW_PRINT_DISABLE 1

#include "com_definitions.h"
#include "com_cpu_id.h"
#include "com_print.h"
#include "com_trace_buffer.h"
#include <xtensa/core-macros.h>
#include "com_static_data_table.h"
#include "com_shared_memory.h"
#include "com_timing.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define DBG_BIT_EXT 28

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
uint32_t com_trace_bfn_cpu_offset = 0; 

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

uint32_t get_com_trace_bfn_cpu_offset(){
    return xthal_get_ccount() - (BFN_TIME_TO_TICKS(com_timing_get_current_bfn_time()));
}

static void com_write_trace_buffer (uint32_t trc_info)
{
    static uint32_t idx = 0;
    uint32_t *p_trace_lut = &p_system_data->trace_buff_lut[RCS_CPU * TRACE_BUFF_LUT_SIZE_WORDS];
    com_trace_bfn_cpu_offset = get_com_trace_bfn_cpu_offset();
    if ( idx == 0 )
    {
        uint8_t const core_ID = (U8 (RCS_CPU) & 0xF);
        p_trace_lut[0] = 0xBBBA0000 + core_ID;
        idx = 2;
    }
    ATOMIC_BEGIN
    if (idx == TRACE_BUFF_LUT_SIZE_WORDS)
    {
        idx = 2;
    }
    p_trace_lut[1] = idx;
    p_trace_lut[idx++] = trc_info;
    // Since idx is in DRAM, waiting for these writes to finish isn't necessary and causes excessive run times.
    // Side effect is users of the log must guard against last entry potentially being incorrect.
    //INTRINSIC_BARRIER;
    ATOMIC_END
    FW_PRINT (FW_INFO, "index %d addr: 0x%x, value:%d ", p_trace_lut[1], U32(&p_trace_lut[idx]), trc_info);
}

/*
 * @brief           Trace functions/handlers and record Timestamp
 * @param [in]      Trace_type, function Id, timestamp
 * @return          none.
 */
void com_func_ts_trace_buffer (uint32_t trc_type, uint32_t trc_info)
{
    FW_PRINT (FW_INFO, "Function Trace With Timestamp");
    func_trace_t trace;
    trace.TYPE = trc_type;
    trace.FUNCTION_ID = trc_info;
    trace.TIMESTAMP = xthal_get_ccount () / 4;
    uint32_t const trace_buff_config = get_tf (com_fw_config_lut, 0, fw_trace_buffer_config);
    if (!(trace_buff_config & (1 << trace.TYPE)))
    {
        com_write_trace_buffer (trace.value);
    }
}

/*
 * @brief           Trace messages/events sequence
 * @param [in]      Trace_type, function Id, trace_info
 * @return          none.
 */
void com_msg_trace_buffer (uint32_t trc_type, uint32_t msg_type, uint32_t msg_info)
{
    FW_PRINT (FW_INFO, "Message Trace Buffer, Message: %d", msg_type);
    msg_trace_t msg_trace;
    msg_trace.TYPE = trc_type;
    msg_trace.MSG_ID = msg_type;
    msg_trace.TRACE_INFO = msg_info;
    uint32_t const trace_buff_config = get_tf (com_fw_config_lut, 0, fw_trace_buffer_config);
    if (!(trace_buff_config & (1 << msg_trace.TYPE)))
    {
        com_write_trace_buffer (msg_trace.value);
    }
}

/*
 * @brief           Trace to report error code
 * @param [in]      Trace_type, error code, error level
 * @return          none.
 */
void com_err_code_trace_buffer (uint32_t trc_type, e_error_code_type_t err_code, e_error_type_t err_level, uint32_t data_count)
{
    FW_PRINT (FW_INFO, " Err Code Trace Buffer, _code: %d", err_code);

    err_code_trace_t trace = {.value = 0};
    trace.TYPE = trc_type;
    trace.CODE = err_code;
    trace.LVL = err_level;
    trace.DATA_COUNT = data_count;
    uint32_t const trace_buff_config = get_tf (com_fw_config_lut, 0, fw_trace_buffer_config);
    if (!(trace_buff_config & (1 << trace.TYPE)))
    {
        com_write_trace_buffer (trace.value);
    }
}

/*
 * @brief           Trace used for debug purpose and user defined debug(from test side)
 * @param [in]      Trace_type, debug location, no.of debug data, info, data
 * @return          none.
 */
void com_debug_trace_buffer (uint32_t trc_type, uint32_t dbg_location, uint32_t data_count, uint32_t info, const uint32_t data[])
{
    FW_PRINT (FW_INFO, "Debug Trace Buffer");
    debug_trace_t dbg_trace = {.value = 0};
    if (trc_type == e_TRACE_EXT_DBG_BITS) // Use 28 lower bits to store the debug trace info.
    {
        dbg_trace.value = (trc_type << DBG_BIT_EXT) | info;
    }
    else
    {
        dbg_trace.DATA = info;
        dbg_trace.TYPE = trc_type;
        dbg_trace.DEBUG_LOCATION_ID = dbg_location;
        dbg_trace.DATA_COUNT = data_count;
    }
    uint32_t count = data_count;
    uint32_t const trace_buff_config = get_tf (com_fw_config_lut, 0, fw_trace_buffer_config);
    if (!(trace_buff_config & (1 << trc_type)))
    {
        ATOMIC_BEGIN
        com_write_trace_buffer (dbg_trace.value);
        uint32_t i = 0;
        while (count)
        {
            com_write_trace_buffer (data[i]);
            i++;
            count--;
        }
        ATOMIC_END
    }
}
