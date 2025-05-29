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
 * @file    tx_msg_handler.c
 * @brief   Functions to handle tx messages.
 * @details TX message handling and TX range check.
 */

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_bfn.h"
#include "com_event.h"
#include "com_isr.h"
#include "com_msgs_enum.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "rcs_gpreg.h"
#include "com_timing.h"
#include "com_fsm.h"
#include "com_msg_timing.h"
#include "com_error.h"
#include "com_trace_buffer.h"
#include "tx_daco.h"
#include "tx_lineup.h"
#include "tx_v2d.h" // for v2d loopback
#include "tx_msg_handler.h"
#include "com_static_data_table.h"

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
static void tx_spi_power_msg_handler_irq (void *unused);
static void tx_rm_handler_irq (void *unused);

/**
 * @brief           TX configuration msg handler, polulating tx daco parameters
 * @param [in]      p_cfg_msg: pointer to configure message
 * @return          none
 */
static void tx_cfg_msg_handler (dl_config_ant_grp_bf_t *const p_cfg_msg);
static void tx_warmup_msg_handler (warmup_bf_t *const p_warmup_msg);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
void tx_cfg_msg_handler (dl_config_ant_grp_bf_t *const p_cfg_msg)
{
    uint16_t ant_mask = p_cfg_msg->ant_group_dl_ant_mask;
    uint8_t quad_idx = 0;
    uint32_t quad_stat[4] = {0};
    quad_params_t *p_quad_params = NULL;
    sys_params_t *p_sys_params = &tx_daco.sys_params;
    if (ant_mask & p_sys_params->rf_ant_mask)
    {
        FW_PRINT (FW_ERR, "trying to config already configured ANTs");
        return;
    }
    else
    {
        p_sys_params->rf_ant_mask |= ant_mask;
    }

    if (tx_daco.is_first_cfg)
    {
        e_sys_clk_t const f_clk = get_tf (com_drf_rate_conf_lut, p_cfg_msg->drf_rate, f_clk);
        com_bfn_set_clk_sel (f_clk);
        tx_daco.is_first_cfg = false;
    }

    while (ant_mask)
    {
        if (ant_mask & 0xf)
        {
            p_quad_params = &tx_daco.quad_params[quad_idx];

            p_quad_params->com_params.topology = p_cfg_msg->topology;
            p_quad_params->com_params.drf_rate = p_cfg_msg->drf_rate;
            p_quad_params->com_params.drf_filter_mode = p_cfg_msg->drf_filter_mode;
            p_quad_params->com_params.fifo_delay = p_cfg_msg->fifo_delay;
            p_quad_params->com_params.drf_mixer_freq = p_cfg_msg->digrf_mixer_freq;

            p_quad_params->v2d_params.strm_cfg = p_cfg_msg->strm_cfg;
            p_quad_params->v2d_params.pdpd_delay = p_cfg_msg->pdpd_delay;
            p_quad_params->v2d_params.pdpd_op_mode = p_cfg_msg->pdpd_op_mode;
            p_quad_params->v2d_params.pdpd_mode = p_cfg_msg->pdpd_mode;
            p_quad_params->v2d_params.pdpd_rate = p_cfg_msg->pdpd_rate;

            p_quad_params->vha_params.vha_rate = p_cfg_msg->vha_rate;
            p_quad_params->vha_params.vha_filter_mode = p_cfg_msg->vha_filter_mode;
            p_quad_params->vha_params.band0_freq = p_cfg_msg->ant_group_dl_band_freq0;
            p_quad_params->vha_params.band1_freq = p_cfg_msg->ant_group_dl_band_freq1;
            quad_stat[quad_idx] = 1;
            p_sys_params->quad_mask |= 1 << quad_idx;
        }
        ant_mask >>= NUM_STRM_PER_QUAD;
        quad_idx++;
    }
    tx_lineup_cfg (p_cfg_msg->ant_group_dl_ant_mask);

    // readback enabled
    if (p_cfg_msg->rb)
    {
        // Readback message  for CONFIG
        msg_t rb_msg;
        uint32_t rb_msg_len_byte = sizeof (dl_config_readback_bf_t);
        memset (&rb_msg.dl_config_readback, 0, rb_msg_len_byte);
        rb_msg.dl_config_readback.timestamp = com_timing_get_current_bfn_time ();
        rb_msg.dl_config_readback.opcode = e_RB_CONFIG_DL_OPCODE;
        rb_msg.ul_config_readback.src = RCS_CPU;
        rb_msg.dl_config_readback.config_status = 1;
        rb_msg.dl_config_readback.quad0 = quad_stat[0];
        rb_msg.dl_config_readback.quad1 = quad_stat[1];
        rb_msg.dl_config_readback.quad2 = quad_stat[2];
        rb_msg.dl_config_readback.quad3 = quad_stat[3];
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (rb_msg_len_byte));
    }

    FW_PRINT (FW_DEBUG, "tx_cfg_msg_handler called");
}

void tx_warmup_msg_handler (warmup_bf_t *const p_warmup_msg)
{
    uint8_t quad_mask = p_warmup_msg->dl_quad_en_mask;
    uint8_t quad_idx = 0;
    sys_params_t *const p_sys_params = &tx_daco.sys_params;
    uint16_t ant_mask = p_sys_params->rf_ant_mask; // configured ANT mask
    // p_warmup_msg->timing // e_TS_TYPE_IMM_TIMESTAMP, e_TS_TYPE_REL_TIMESTAMP, e_TS_TYPE_ABS_TIMESTAMP
    // p_warmup_msg->ref_index
    // p_warmup_msg->timestamp

    while (quad_mask)
    {
        quad_params_t *const p_quad_params = &tx_daco.quad_params[quad_idx];
        p_quad_params->com_params.lpbk_mode = p_warmup_msg->loopback_mode_en;
        uint8_t ant_mask_in_quad = ant_mask & 0xf;
        if ((quad_mask & 1) && ant_mask_in_quad)
        {
            tx_v2d_en (quad_idx, ant_mask_in_quad);
            tx_v2d_lpbk_cfg (quad_idx, ant_mask_in_quad);
        }

        ant_mask >>= NUM_STRM_PER_QUAD;
        quad_mask >>= 1;
        quad_idx++;
    }

    FW_PRINT (FW_DEBUG, "tx_warmup_msg_handler called");
}

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
msg_hdlr_t tx_hdlr_lut[] = {
    {.p_msg_hdlr_f = dl_spi_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_spi_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_spi_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_spi_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_update_control_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_UPDATE_CONTROL_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_UPDATE_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_UPDATE_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_config_ant_grp_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_CONFIG_ANT_GRP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = true},
    {.p_msg_hdlr_f = dl_warmup_handler,
     .p_range_check_f = NULL,
     .opcode = e_WARMUP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = false},
    {.p_msg_hdlr_f = NULL, .p_range_check_f = NULL, .opcode = 0, .ref_act_ts = 0, .set_up_ts = 0, .is_schedulable = false},
};

msg_irq_hdlr_map_t tx_msg_irq_hdlr_map[e_NUM_TX_MB_IRQ] = {
    {.msg_mb_irq = e_TX_SPI_PWR_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)tx_spi_power_msg_handler_irq},
    {.msg_mb_irq = e_AX_TO_TX_RM_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)tx_rm_handler_irq},
};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           interrupt handler for RX Radio Message Handler
 * @param [in]      none
 * @return          none
 */

void tx_rm_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_IRQ_RM_MSG);

    com_mb_isr_clear ((e_com_int_mb_sel_t)e_AX_TO_TX_RM_MB_IRQ);
    FW_PRINT (FW_INFO, "Enter TX RM Handler IRQ");
    msg_t read_test_msg;
    uint32_t read_test_msg_len = 0;
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_TX_RM_QUEUE);
    while (e_RET_QUEUE_EMPTY != com_queue_read (p_msg_queue, &read_test_msg, &read_test_msg_len))
    {
        uint32_t const opcode = com_msg_get_opcode (&read_test_msg);
        msg_hdlr_t const *msg_hdlr = com_msg_init_handler (opcode, tx_hdlr_lut);
        if (msg_hdlr)
            msg_hdlr->p_msg_hdlr_f (&read_test_msg);
        else
        {
            FW_SEND_ERR_RB (e_INVALID_OPCODE_ERR, opcode, e_TX_RM_QUEUE);
        }
    }
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_IRQ_RM_MSG);
}

/**
 * @brief           message handler for TX spi Power  messages
 * @param [in]      none
 * @return          none
 */

static void tx_spi_power_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_UC_SMSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_TX_SPI_PWR_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter TX SPI Power Msg Handler IRQ");

    msg_t read_test_msg;
    uint32_t reg_data[4];

    // needs discussion on power messages contents
    reg_data[0] = RCS_GPREG_EXT_TO_RCS_MB6_MBDATA0_REG->value;
    reg_data[1] = RCS_GPREG_EXT_TO_RCS_MB6_MBDATA1_REG->value;
    reg_data[2] = RCS_GPREG_EXT_TO_RCS_MB6_MBDATA2_REG->value;
    reg_data[3] = RCS_GPREG_EXT_TO_RCS_MB6_MBDATA3_REG->value;

    FW_PRINT (FW_INFO, " reg_data[0] = %u", reg_data[0]);
    FW_PRINT (FW_INFO, " reg_data[1] = %u", reg_data[1]);
    FW_PRINT (FW_INFO, " reg_data[2] = %u", reg_data[2]);
    FW_PRINT (FW_INFO, " reg_data[3] = %u", reg_data[3]);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_UC_SMSG);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           callback function for TX config ant_grp message
 * @param [in]      TX config ant_grp0 message
 * @return          none
 */

void dl_config_ant_grp_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_CONFIG_MSG);
    FW_PRINT (FW_INFO, "Inside DL_CONFIG ANT GRP message handler");
    msg_t *p_msg = (msg_t *)data;
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    dl_config_ant_grp_bf_t dl_config_ant_grp = p_msg->dl_config_ant_grp;

    for (uint32_t i = 0; i < e_MAX_NUM_QUAD; i++)
    {
        if (dl_config_ant_grp.ant_group_dl_ant_mask & (0xF << (i * 4)))
        {
            status = com_fsm_quad_transition (e_FSM_TX, com_fsm_quad_get_status (e_FSM_TX, i), e_QUAD_EVENT_CONFIG, i);
            if (status == e_FSM_TRANSITION_RET_FAIL)
            {
                FW_PRINT (FW_ERR, "Quad FSM Transition failed");
                return;
            }
        }
    }

    status = com_fsm_transition (e_FSM_TX, com_fsm_get_status (e_FSM_TX), e_EVENT_CONFIG);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }

    tx_cfg_msg_handler (&dl_config_ant_grp);

    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_CONFIG_MSG);
}

/**
 * @brief           callback function for TX WARMUP message
 * @param [in]      TX WARMUP message
 * @return          none
 */

void dl_warmup_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside DL_WARMUP message handler");
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_WARMUP_MSG);

    msg_t *p_msg = (msg_t *)data;
    warmup_bf_t warmup_msg = p_msg->warmup;
    com_fsm_transition_run (e_FSM_TX);
    com_fsm_transition_quadmask (e_FSM_TX, warmup_msg.dl_quad_en_mask, e_QUAD_EVENT_WARMUP);

    tx_warmup_msg_handler (&warmup_msg);

    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_WARMUP_MSG);
}

/**
 * @brief           callback function for TX ON message
 * @param [in]      TX ON message
 * @return          none
 */

void dl_on_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_ON_MSG);
    FW_PRINT (FW_INFO, "Inside DL_ON message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    dl_on_bf_t dl_on_msg = p_msg->dl_on;
    FW_PRINT (FW_INFO, "dl_on_msg->power_ant0 = %d", dl_on_msg.power_ant0);

    e_fsm_quad_event_type_t on_event = (dl_on_msg.opcode == e_DL_FAST_ON_OPCODE) ? e_QUAD_EVENT_ON_FAST : e_QUAD_EVENT_ON;

    status = com_fsm_transition_check_quadmask_transition (e_FSM_TX, dl_on_msg.quad_mask0, dl_on_msg.quad_mask1, dl_on_msg.quad_mask2,
                                                           dl_on_msg.quad_mask3, on_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    // readback enabled
    if (dl_on_msg.rb)
    {
        msg_t rb_msg;
        memset (&rb_msg.dl_on_readback, 0, sizeof (dl_on_readback_bf_t));
        rb_msg.dl_on_readback.opcode = e_RB_ON_DL_OPCODE;
        rb_msg.dl_on_readback.avg_0 = dl_on_msg.power_ant0;
        rb_msg.dl_on_readback.avg_1 = dl_on_msg.power_ant1;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (dl_on_readback_bf_t)));
    }
    const uint32_t time_debug = dl_on_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, TX_ON_MSG, 1, TX_ON_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_ON_MSG);
}

/**
 * @brief           callback function for TX Update Control message
 * @param [in]      TX Update Control message
 * @return          none
 */

void dl_update_control_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_UC_MSG);
    FW_PRINT (FW_INFO, "Inside DL_Update Control message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    dl_update_control_bf_t dl_upd_ctrl = p_msg->dl_update_control;
    FW_PRINT (FW_INFO, "dl_update_ctrl_msg->power_ant0 = %d", dl_upd_ctrl.power_ant0);

    status = com_fsm_transition_check_quadmask_transition (e_FSM_TX, dl_upd_ctrl.quad_mask0, dl_upd_ctrl.quad_mask1, dl_upd_ctrl.quad_mask2,
                                                           dl_upd_ctrl.quad_mask3, e_QUAD_EVENT_UPDATE);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    // readback enabled
    if (dl_upd_ctrl.rb)
    {
        msg_t rb_msg;
        memset (&rb_msg.dl_on_readback, 0, sizeof (dl_on_readback_bf_t));
        rb_msg.dl_on_readback.opcode = e_RB_ON_DL_OPCODE;
        rb_msg.dl_on_readback.avg_0 = dl_upd_ctrl.power_ant0;
        rb_msg.dl_on_readback.avg_1 = dl_upd_ctrl.power_ant1;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (dl_on_readback_bf_t)));
    }
    const uint32_t time_debug = dl_upd_ctrl.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, TX_UC_MSG, 1, TX_UC_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_UC_MSG);
}

/**
 * @brief           callback function for TX off message
 * @param [in]      TX off message
 * @return          none
 */

void dl_off_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_OFF_MSG);
    FW_PRINT (FW_INFO, "Inside DL_OFF message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    dl_off_bf_t dl_off_msg = p_msg->dl_off;
    FW_PRINT (FW_INFO, "dl_off_msg->mode = %d", dl_off_msg.mode);

    e_fsm_quad_event_type_t off_event = com_fsm_off_mode_check (dl_off_msg.mode);
    off_event = (dl_off_msg.opcode == e_DL_FAST_OFF_OPCODE) ? e_QUAD_EVENT_OFF_FAST : off_event;
    status = com_fsm_transition_check_quadmask_transition (e_FSM_TX, dl_off_msg.quad_mask0, dl_off_msg.quad_mask1, dl_off_msg.quad_mask2,
                                                           dl_off_msg.quad_mask3, off_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    status = com_fsm_transition_off_stop (e_FSM_TX);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }
    const uint32_t time_debug = dl_off_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, TX_OFF_MSG, 1, TX_OFF_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_OFF_MSG);
}

/**
 * @brief           callback function for TX set reference message
 * @param [in]      TX set reference message
 * @return          none
 */

void dl_set_time_ref_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside DL_SET_REF message handler");
    msg_t *p_msg = (msg_t *)data;
    set_time_ref_bf_t set_time_ref_msg = p_msg->set_time_ref;
    uint32_t curr_time = com_timing_get_current_bfn_time ();
    FW_PRINT (FW_INFO, "set_time_ref_msg.ref_index = %d,curr_time = %u ", set_time_ref_msg.ref_index, curr_time);
    com_msg_ref_timestamp_set (set_time_ref_msg.ref_index, curr_time);
}

/**
 * @brief           callback function for TX SPI ON message
 * @param [in]      TX SPI ON message
 * @return          none
 */

void dl_spi_on_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_ON_SMSG);
    FW_PRINT (FW_INFO, "Inside DL_SPI_ON message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    dl_spi_on_bf_t dl_spi_on_msg = p_msg->dl_spi_on;
    FW_PRINT (FW_INFO, "dl_spi_on_msg->quad_mask = %d", dl_spi_on_msg.quad_mask);

    status = com_fsm_transition_check_quadmask_transition (e_FSM_TX, dl_spi_on_msg.quad_mask, 0, 0, 0, e_QUAD_EVENT_ON);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    // readback enabled
    if (dl_spi_on_msg.rb)
    {
        msg_t rb_msg;
        memset (&rb_msg.dl_on_readback, 0, sizeof (dl_on_readback_bf_t));
        rb_msg.dl_on_readback.opcode = e_RB_ON_DL_OPCODE;
        rb_msg.dl_on_readback.avg_0 = 20; // place holder
        rb_msg.dl_on_readback.avg_1 = 30; // place holder
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (dl_on_readback_bf_t)));
    }
    const uint32_t time_debug = dl_spi_on_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, TX_ON_SMSG, 1, TX_ON_SMSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_ON_SMSG);
}

/**
 * @brief           callback function for TX SPI off message
 * @param [in]      TX SPI off message
 * @return          none
 */

void dl_spi_off_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, TX_OFF_SMSG);
    FW_PRINT (FW_INFO, "Inside DL_SPI_OFF message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    dl_spi_off_bf_t dl_spi_off_msg = p_msg->dl_spi_off;
    FW_PRINT (FW_INFO, "dl_spi_off_msg->mode = %d", dl_spi_off_msg.mode);

    e_fsm_quad_event_type_t off_event = com_fsm_off_mode_check (dl_spi_off_msg.mode);
    status = com_fsm_transition_check_quadmask_transition (e_FSM_TX, dl_spi_off_msg.quad_mask, 0, 0, 0, off_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    status = com_fsm_transition_off_stop (e_FSM_TX);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }
    const uint32_t time_debug = dl_spi_off_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, TX_OFF_SMSG, 1, TX_OFF_SMSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, TX_OFF_SMSG);
}

// todo: need to add tx shutdown message
// todo: tx shutdown message have
//       tx_daco->is_first_cfg = true;
