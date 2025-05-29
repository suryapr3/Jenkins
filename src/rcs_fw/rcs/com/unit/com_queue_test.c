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
 * @file    com_queue_test.c
 * @brief   Unit test code for queue functions.
 * @details Unit test code for queue functions.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_print.h"
#include "com_queue.h"
#include <stdbool.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

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

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

int main (int argc, char **argv)
{
    FW_PRINT (FW_INFO, "com_queue_test");

    g_assertion_counter = 0;
    uint32_t queue_start_addr = 0;

    uint32_t read_test_msg_len = 0;
    msg_queue_t test_msg_queue;

    msg_t test_msg, read_test_msg;

    com_queue_init (&test_msg_queue);

    dl_config_ant_grp_bf_t dl_config_msg, read_dl_config_msg;

    dl_config_msg.timestamp = 0x87654321;
    dl_config_msg.ant_group_dl_ant_mask = 0xF;
    dl_config_msg.ant_group_dl_band_freq0 = 0xCDE;
    dl_config_msg.ant_group_dl_band_freq1 = 0xAAB;
    dl_config_msg.jesd_latency = 0xFED;
    dl_config_msg.vha_dl_latency = 0xEAB;
    test_msg.dl_config_ant_grp = dl_config_msg;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_config_msg)));


    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_config_msg)));

    dl_on_bf_t test_dl_on, read_dl_on_msg;
    test_dl_on.timestamp = 0x12345678;
    test_dl_on.power_ant0 = 0x0B;
    test_dl_on.power_ant1 = 0x0C;
    test_msg.dl_on = test_dl_on;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_dl_on)));

    dl_off_bf_t test_dl_off, read_dl_off_msg;
    test_dl_off.mode = 0x2;
    test_dl_off.timestamp = 0xDEADBEEF;
    test_msg.dl_off = test_dl_off;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_dl_off)));

    // adding RX messages
    ul_config_ant_grp_bf_t ul_config_msg, read_ul_config_msg;
    ul_config_msg.timestamp = 0x87654321;
    ul_config_msg.ant_group_ul_ant_mask = 0xF;
    ul_config_msg.ant_group_ul_band_freq0 = 0xCDE;
    ul_config_msg.ant_group_ul_band_freq1 = 0xAAB;
    ul_config_msg.drf_latency = 0xED;
    ul_config_msg.vha_ul_latency = 0xEAB;
    test_msg.ul_config_ant_grp = ul_config_msg;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (ul_config_msg)));


    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (ul_config_msg)));

    ul_update_control_bf_t test_ul_on, read_ul_on_msg;
    test_ul_on.timestamp = 0x12345678;
    test_ul_on.gain_ant0 = 0x0B;
    test_ul_on.gain_ant1 = 0x0C;
    test_msg.ul_update_control = test_ul_on;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_ul_on)));

    ul_off_bf_t test_ul_off, read_ul_off_msg;
    test_ul_off.mode = 0x1;
    test_ul_off.timestamp = 0xDEADBEEF;
    test_msg.ul_off = test_ul_off;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_ul_off)));

    test_msg.dl_config_ant_grp = dl_config_msg;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_config_msg)));



    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_config_msg)));


    test_msg.dl_on = test_dl_on;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_dl_on)));

    test_msg.dl_off = test_dl_off;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_dl_off)));

    // adding RX messages

    test_msg.ul_config_ant_grp = ul_config_msg;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (ul_config_msg)));



    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (ul_config_msg)));


    test_msg.ul_update_control = test_ul_on;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_ul_on)));


    test_msg.ul_off = test_ul_off;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_ul_off)));


    test_msg.dl_config_ant_grp = dl_config_msg;
    FW_PRINT (FW_NOTE, "Expecting queue full.");
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_config_msg))); // queue  full

    com_queue_dump (&test_msg_queue);

    /**********************Queue Read *****************************************/
    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_config_msg = read_test_msg.dl_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_dl_config_msg.timestamp = 0x%x", read_dl_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_ant_mask = 0x%x", read_dl_config_msg.ant_group_dl_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_dl_band_freq0= 0x%x ", read_dl_config_msg.ant_group_dl_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_band_freq1= 0x%x", read_dl_config_msg.ant_group_dl_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg jesd_latency = 0x%x ", read_dl_config_msg.jesd_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_dl_latency  = 0x%x ", read_dl_config_msg.vha_dl_latency);


    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_config_msg = read_test_msg.dl_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_dl_config_msg.timestamp = 0x%x", read_dl_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_ant_mask = 0x%x", read_dl_config_msg.ant_group_dl_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_dl_band_freq0= 0x%x ", read_dl_config_msg.ant_group_dl_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_band_freq1= 0x%x", read_dl_config_msg.ant_group_dl_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg jesd_latency = 0x%x ", read_dl_config_msg.jesd_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_dl_latency  = 0x%x ", read_dl_config_msg.vha_dl_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_on_msg = read_test_msg.dl_on;
    FW_PRINT (FW_INFO, "read_dl_on_msg.timestamp = 0x%x", read_dl_on_msg.timestamp);
    FW_PRINT (FW_INFO, "read_dl_on_msg.power_ant0 = 0x%x", read_dl_on_msg.power_ant0);
    FW_PRINT (FW_INFO, "read_dl_on_msg.power_ant1 = 0x%x", read_dl_on_msg.power_ant1);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_off_msg = read_test_msg.dl_off;

    FW_PRINT (FW_INFO, "read_dl_off_msg.timestamp = 0x%x", read_dl_off_msg.timestamp);
    FW_PRINT (FW_INFO, "read_dl_off_msg.mode = 0x%x", read_dl_off_msg.mode);

    // Read RX messages
    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_config_msg = read_test_msg.ul_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_ant_mask = 0x%x", read_ul_config_msg.ant_group_ul_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_ul_band_freq0= 0x%x ", read_ul_config_msg.ant_group_ul_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_band_freq1= 0x%x", read_ul_config_msg.ant_group_ul_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg drf_latency = 0x%x ", read_ul_config_msg.drf_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_ul_latency  = 0x%x ", read_ul_config_msg.vha_ul_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_config_msg = read_test_msg.ul_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_ant_mask = 0x%x", read_ul_config_msg.ant_group_ul_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_ul_band_freq0= 0x%x ", read_ul_config_msg.ant_group_ul_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_band_freq1= 0x%x", read_ul_config_msg.ant_group_ul_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg drf_latency = 0x%x ", read_ul_config_msg.drf_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_ul_latency  = 0x%x ", read_ul_config_msg.vha_ul_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_on_msg = read_test_msg.ul_update_control;
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_on_msg.timestamp);
    FW_PRINT (FW_INFO, "read_ul_on_msg.gain_ant0 = 0x%x", read_ul_on_msg.gain_ant0);
    FW_PRINT (FW_INFO, "read_ul_on_msg.gain_ant1 = 0x%x", read_ul_on_msg.gain_ant1);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_off_msg = read_test_msg.ul_off;
    FW_PRINT (FW_INFO, "read_ul_off_msg.timestamp = 0x%x", read_ul_off_msg.timestamp);
    FW_PRINT (FW_INFO, "read_ul_off_msg.mode = 0x%x", read_ul_off_msg.mode);


    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_config_msg = read_test_msg.dl_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_dl_config_msg.timestamp = 0x%x", read_dl_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_ant_mask = 0x%x", read_dl_config_msg.ant_group_dl_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_dl_band_freq0= 0x%x ", read_dl_config_msg.ant_group_dl_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_band_freq1= 0x%x", read_dl_config_msg.ant_group_dl_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg jesd_latency = 0x%x ", read_dl_config_msg.jesd_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_dl_latency  = 0x%x ", read_dl_config_msg.vha_dl_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_config_msg = read_test_msg.dl_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_dl_config_msg.timestamp = 0x%x", read_dl_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_ant_mask = 0x%x", read_dl_config_msg.ant_group_dl_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_dl_band_freq0= 0x%x ", read_dl_config_msg.ant_group_dl_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_dl_band_freq1= 0x%x", read_dl_config_msg.ant_group_dl_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg jesd_latency = 0x%x ", read_dl_config_msg.jesd_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_dl_latency  = 0x%x ", read_dl_config_msg.vha_dl_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_on_msg = read_test_msg.dl_on;
    FW_PRINT (FW_INFO, "read_dl_on_msg.timestamp = 0x%x", read_dl_on_msg.timestamp);
    FW_PRINT (FW_INFO, "read_dl_on_msg.power_ant0 = 0x%x", read_dl_on_msg.power_ant0);
    FW_PRINT (FW_INFO, "read_dl_on_msg.power_ant1 = 0x%x", read_dl_on_msg.power_ant1);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_dl_off_msg = read_test_msg.dl_off;

    FW_PRINT (FW_INFO, "read_dl_off_msg.timestamp = 0x%x", read_dl_off_msg.timestamp);
    FW_PRINT (FW_INFO, "read_dl_off_msg.mode = 0x%x", read_dl_off_msg.mode);

    // Read RX messages
    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_config_msg = read_test_msg.ul_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_ant_mask = 0x%x", read_ul_config_msg.ant_group_ul_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_ul_band_freq0= 0x%x ", read_ul_config_msg.ant_group_ul_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_band_freq1= 0x%x", read_ul_config_msg.ant_group_ul_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg drf_latency = 0x%x ", read_ul_config_msg.drf_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_ul_latency  = 0x%x ", read_ul_config_msg.vha_ul_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_config_msg = read_test_msg.ul_config_ant_grp;

    FW_PRINT (FW_INFO, "read_test_msg_len = %d ", read_test_msg_len);
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_config_msg.timestamp);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_ant_mask = 0x%x", read_ul_config_msg.ant_group_ul_ant_mask);
    FW_PRINT (FW_INFO, "read_test_msg  ant_group_ul_band_freq0= 0x%x ", read_ul_config_msg.ant_group_ul_band_freq0);
    FW_PRINT (FW_INFO, "read_test_msg ant_group_ul_band_freq1= 0x%x", read_ul_config_msg.ant_group_ul_band_freq1);
    FW_PRINT (FW_INFO, "read_test_msg drf_latency = 0x%x ", read_ul_config_msg.drf_latency);
    FW_PRINT (FW_INFO, "read_test_msg vha_ul_latency  = 0x%x ", read_ul_config_msg.vha_ul_latency);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_on_msg = read_test_msg.ul_update_control;
    FW_PRINT (FW_INFO, "read_ul_on_msg.timestamp = 0x%x", read_ul_on_msg.timestamp);
    FW_PRINT (FW_INFO, "read_ul_on_msg.gain_ant0 = 0x%x", read_ul_on_msg.gain_ant0);
    FW_PRINT (FW_INFO, "read_ul_on_msg.gain_ant1 = 0x%x", read_ul_on_msg.gain_ant1);

    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);
    read_ul_off_msg = read_test_msg.ul_off;
    FW_PRINT (FW_INFO, "read_ul_off_msg.timestamp = 0x%x", read_ul_off_msg.timestamp);
    FW_PRINT (FW_INFO, "read_ul_off_msg.mode = 0x%x", read_ul_off_msg.mode);

    FW_PRINT (FW_NOTE, "Expecting queue empty.");
    com_queue_read (&test_msg_queue, &read_test_msg, &read_test_msg_len);

    /***************************************************************/
    // Reinserting into queue
    dl_update_control_bf_t test_dl_upd;
    test_dl_upd.timestamp = 0x23456781;
    test_dl_upd.power_ant0 = 0x0B;
    test_dl_upd.power_ant1 = 0x0C;
    test_msg.dl_update_control = test_dl_upd;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_dl_upd)));

    ul_on_bf_t test_ul_on1;
    test_ul_on1.timestamp = 0x34567821;
    test_ul_on1.gain_ant0 = 0x0D;
    test_ul_on1.gain_ant1 = 0x0E;
    test_msg.ul_on = test_ul_on1;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (test_ul_on1)));

    dl_on_readback_bf_t dl_readback;
    dl_readback.timestamp = 0x45678213;
    dl_readback.avg_0 = 0x0B;
    dl_readback.avg_1= 0x0D;
    test_msg.dl_on_readback = dl_readback;
    com_queue_insert (&test_msg_queue, &test_msg, LEN_IN_WORD (sizeof (dl_readback)));


    com_queue_dump (&test_msg_queue);

    FW_PRINT (FW_INFO, "Queue Test Complete");

    return (0);
}
