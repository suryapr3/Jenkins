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
 * @file    admin_msg_handler.c
 * @brief   Functions to handle admin messages.
 * @details Admin message handling routines.
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif
#include <string.h>
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "admin_msg_handler.h"
#include "admin_msg.h"
#include "com_bfn.h"
#include "com_isr.h"
#include "com_msgs_enum.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_fsm.h"
#include "com_timing.h"
#include "ax_rx_msg_handler.h"
#include "ax_tx_msg_handler.h"
#include "ax_jesd_config.h"
#include "ax_daco.h"

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
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void admin_queue_msg_handler_irq (void *unused);
static void admin_set_time_ref_handler (void *data);

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
msg_hdlr_t admin_hdlr_lut[] = {{.p_msg_hdlr_f = bfn_sync_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_BFN_SYNC_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false},
                                               {.p_msg_hdlr_f = warmup_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_WARMUP_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = true},
                                               {.p_msg_hdlr_f = cal_config_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_CAL_CONFIG_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false},
                                               {.p_msg_hdlr_f = reconfig_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_RECONFIG_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false},
                                               {.p_msg_hdlr_f = sleep_control_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_SLEEP_CONTROL_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false},
                                               {.p_msg_hdlr_f = shutdown_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_SHUTDOWN_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = true},
                                               {.p_msg_hdlr_f = admin_set_time_ref_handler,
                                                .p_range_check_f = NULL,
                                                .opcode = e_SET_TIME_REF_OPCODE,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false},
                                               {.p_msg_hdlr_f = NULL,
                                                .p_range_check_f = NULL,
                                                .opcode = 0,
                                                .ref_act_ts = 0,
                                                .set_up_ts = 0,
                                                .is_schedulable = false}};

msg_irq_hdlr_map_t admin_msg_irq_hdlr_map[e_NUM_AD_MB_IRQ] = {
    {.msg_mb_irq = e_AD_QUEUE_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)admin_queue_msg_handler_irq},
    {.msg_mb_irq = e_RX_SPI_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)ax_rx_spi_msg_handler_irq},
    {.msg_mb_irq = e_RX_QUEUE_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)ax_rx_queue_msg_handler_irq},
    {.msg_mb_irq = e_TX_SPI_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)ax_tx_spi_msg_handler_irq},
    {.msg_mb_irq = e_TX_QUEUE_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)ax_tx_queue_msg_handler_irq}};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Interrupt Service Routine for ADMIN messages
 * @param [in]      none
 * @return          none
 */

static void admin_queue_msg_handler_irq (void *unused)
{
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_AD_QUEUE_MB_IRQ);
    FW_PRINT (FW_INFO, "Enter ADMIN Msg Handler IRQ");
    msg_t read_test_msg;
    msg_hdlr_t msg_hdlr;
    uint32_t read_test_msg_len = 0;
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_ADMIN_QUEUE);

    while (e_RET_QUEUE_EMPTY != com_queue_read (p_msg_queue, &read_test_msg, &read_test_msg_len))
    {
        com_msg_schedule_macro (&read_test_msg, admin_hdlr_lut, e_ADMIN_QUEUE);
    }
}

/**
 * @brief           callback function for admin set reference message
 * @param [in]      TX set reference message
 * @return          none
 */

static void admin_set_time_ref_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside ADMIN_SET_REF message handler");
    msg_t *p_msg = (msg_t *)data;
    set_time_ref_bf_t set_time_ref_msg = p_msg->set_time_ref;
    uint32_t curr_time = com_timing_get_current_bfn_time ();
    FW_PRINT (FW_INFO, "admin_time_ref_msg.ref_index = %d,curr_time = %u ", set_time_ref_msg.ref_index, curr_time);
    com_msg_ref_timestamp_set (set_time_ref_msg.ref_index, curr_time);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           callback function for bfn synch message
 * @param [in]      BFN synch message
 * @return          none
 */

void bfn_sync_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside bfn_sync_handler");
    msg_t *p_msg = (msg_t *)data;
    bfn_sync_bf_t bfn_sync = p_msg->bfn_sync;
    ax_daco_t *const p_ax_daco = ax_daco_get_addr ();
    FW_PRINT (FW_INFO, "bfn_sync.timestamp_msb = %d bfn_sync.timestamp = %d ", bfn_sync.timestamp_msb, bfn_sync.timestamp);
    com_bfn_set_ant_mask (p_ax_daco->rx_cfg_quads.ant_mask | p_ax_daco->tx_cfg_quads.ant_mask,
                          p_ax_daco->jesd_rx_cfg.mask | p_ax_daco->jesd_tx_cfg.mask);

    if (bfn_sync.bfn_sync_type == e_BFN_SYNC_TYPE_EXT)
    	com_bfn_sysref_sync (bfn_sync.timestamp_msb, bfn_sync.timestamp);
    else
    	com_bfn_soft_sync (bfn_sync.timestamp_msb, bfn_sync.timestamp);
}

/**
 * @brief           callback function for warmup message
 * @param [in]      warm up message
 * @return          none
 */

void warmup_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside warmup_handler");
    msg_t *p_msg = (msg_t *)data;
    warmup_bf_t warmup_msg = p_msg->warmup;
    ax_daco_t *const p_ax_daco = ax_daco_get_addr ();
    uint32_t quad_stat_dl[MAX_NUM_QUAD] = {0, 0, 0, 0};
    uint32_t quad_stat_ul[MAX_NUM_QUAD] = {0, 0, 0, 0};
    FW_PRINT (FW_INFO, "warmup_msg.ul_quad_en_mask = %d warmup_msg.dl_quad_en_mask = %d ", warmup_msg.ul_quad_en_mask,
              warmup_msg.dl_quad_en_mask);

    if (!com_bfn_is_ant_mask_set ())
    {
        com_bfn_set_ant_mask (p_ax_daco->rx_cfg_quads.ant_mask | p_ax_daco->tx_cfg_quads.ant_mask,
                              p_ax_daco->jesd_rx_cfg.mask | p_ax_daco->jesd_tx_cfg.mask);
        com_bfn_self_sync ();
    }

    if (warmup_msg.dl_quad_en_mask)
    {
        ax_tx_activate_handler (p_msg);                 // copy warmup msg TX queue and notify TX core
        ax_jesd_rx_enable (warmup_msg.dl_quad_en_mask); // RF downlink is JESD uplink
    }
    if (warmup_msg.ul_quad_en_mask)
    {
        ax_jesd_tx_enable (warmup_msg.ul_quad_en_mask); // RF uplink is JESD downlink
        ax_rx_activate_handler (p_msg);                 // copy warmup msg RX queue and notify RX core
    }
    for (uint32_t i = 0; i < MAX_NUM_QUAD; i++)
    {
        if (warmup_msg.dl_quad_en_mask & (1 << i))
        {
        	quad_stat_dl[i] = 1;
        }

        if (warmup_msg.ul_quad_en_mask & (1 << i))
        {
        	quad_stat_ul[i] = 1;
        }
    }
    if (warmup_msg.rb)
    {
        // Readback message  for WARMUP
        msg_t rb_msg;
        uint32_t rb_msg_len_byte = sizeof (warmup_readback_bf_t);
        memset (&rb_msg.warmup_readback, 0, rb_msg_len_byte);
        rb_msg.warmup_readback.timestamp = com_timing_get_current_bfn_time ();
        rb_msg.warmup_readback.opcode = e_RB_WARMUP_OPCODE;
        rb_msg.warmup_readback.quad0_ul_status = quad_stat_ul[0];
        rb_msg.warmup_readback.quad1_ul_status = quad_stat_ul[1];
        rb_msg.warmup_readback.quad2_ul_status = quad_stat_ul[2];
        rb_msg.warmup_readback.quad3_ul_status = quad_stat_ul[3];
        rb_msg.warmup_readback.quad0_ul_latency = 0;
        rb_msg.warmup_readback.quad1_ul_latency = 0;
        rb_msg.warmup_readback.quad2_ul_latency = 0;
        rb_msg.warmup_readback.quad3_ul_latency = 0;
        rb_msg.warmup_readback.quad0_dl_status = quad_stat_dl[0];
        rb_msg.warmup_readback.quad1_dl_status = quad_stat_dl[1];
        rb_msg.warmup_readback.quad2_dl_status = quad_stat_dl[2];
        rb_msg.warmup_readback.quad3_dl_status = quad_stat_dl[3];
        rb_msg.warmup_readback.quad0_dl_latency = 0;
        rb_msg.warmup_readback.quad1_dl_latency = 0;
        rb_msg.warmup_readback.quad2_dl_latency = 0;
        rb_msg.warmup_readback.quad3_dl_latency = 0;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (rb_msg_len_byte));
    }
}

/**
 * @brief           callback function for cal_config message
 * @param [in]      cal_config message
 * @return          none
 */

void cal_config_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside cal_config_handler");
    msg_t *p_msg = (msg_t *)data;
    cal_config_bf_t cal_config = p_msg->cal_config;
    FW_PRINT (FW_INFO, "cal_config.sc_adc_en = %d cal_config.quad_mask_sc_adc = %d ", cal_config.sc_adc_en, cal_config.quad_mask_sc_adc);
}

/**
 * @brief           callback function for reconfig message
 * @param [in]      reconfig message handler
 * @return          none
 */

void reconfig_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside reconfig_handler");
    msg_t *p_msg = (msg_t *)data;
    reconfig_bf_t reconfig = p_msg->reconfig;
    FW_PRINT (FW_INFO, "reconfig.ul_quad = %d reconfig.dl_quad = %d ", reconfig.ul_quad, reconfig.dl_quad);
}

/**
 * @brief           callback function for sleep control message
 * @param [in]      sleep control message
 * @return          none
 */

void sleep_control_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside sleep_control_handler");
    msg_t *p_msg = (msg_t *)data;
    sleep_control_bf_t sleep_control = p_msg->sleep_control;
    FW_PRINT (FW_INFO, "sleep_control.state = %d ", sleep_control.state);
}

/**
 * @brief           callback function for shutdown message
 * @param [in]      shutdown message
 * @return          none
 */

void shutdown_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside shutdown_handler");
    msg_t *p_msg = (msg_t *)data;
    shutdown_bf_t shutdown = p_msg->shutdown;
    FW_PRINT (FW_INFO, " shutdown.timestamp = %d ", shutdown.timestamp);

    com_fsm_quad_init (e_FSM_TX);
    com_fsm_quad_init (e_FSM_RX);
    com_fsm_update_status (e_FSM_TX, e_STATE_SETUP);
    com_fsm_update_status (e_FSM_RX, e_STATE_SETUP);
    com_bfn_shutdown ();
    ax_daco_clear (ax_daco_get_addr ());
}
