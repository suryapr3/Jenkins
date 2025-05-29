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
 * @file    rx_msg_handler.c
 * @brief   Functions to handle rx messages.
 * @details RX message handling and RX range check.
 */

#if (CPU_RX)
#else
#error "Not RX CPU"
#endif

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_bfn.h"
#include "com_event.h"
#include "com_isr.h"
#include "com_msg_handler_utils.h"
#include "com_msgs_enum.h"
#include "com_print.h"
#include "com_timing.h"
#include "com_shared_memory.h"
#include "com_fsm.h"
#include "com_msg_timing.h"
#include "com_error.h"
#include "com_trace_buffer.h"
#include "com_rm_def.h"
#include "com_static_data_table.h"
#include "rx_daco.h"
#include "rx_v2d.h"
#include "rx_lineup.h"
#include "rx_msg_handler.h"
#include "rx_adc_cfg.h"

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
static void rx_spi_gain_msg_handler_irq (void *unused);
static void rx_rm_handler_irq (void *unused);
static void rx_warmup_msg_handler (warmup_bf_t *const p_warmup_msg);
static void rx_cfg_msg_handler (ul_config_ant_grp_bf_t *const p_cfg_msg);
static void rm_fbr_cfg_handler (void *data);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                  *
 ***********************************************/
void rx_warmup_msg_handler (warmup_bf_t *const p_warmup_msg)
{
    uint8_t quad_mask = p_warmup_msg->dl_quad_en_mask;
    uint8_t quad_idx = 0;
    sys_params_t *const p_sys_params = &rx_daco.sys_params;
    uint16_t ant_mask = p_sys_params->rf_ant_mask; // configured ANT mask
    // p_warmup_msg->timing // e_TS_TYPE_IMM_TIMESTAMP, e_TS_TYPE_REL_TIMESTAMP, e_TS_TYPE_ABS_TIMESTAMP
    // p_warmup_msg->ref_index
    // p_warmup_msg->timestamp

    while (quad_mask)
    {
        quad_params_t *const p_quad_params = &rx_daco.quad_params[quad_idx];
        p_quad_params->com_params.lpbk_mode = p_warmup_msg->loopback_mode_en;
        uint8_t ant_mask_in_quad = ant_mask & 0xf;
        if (ant_mask_in_quad)
        {
            rx_v2d_en (quad_idx, ant_mask_in_quad);
        }

        ant_mask >>= NUM_STRM_PER_QUAD;
        quad_mask >>= 1;
        quad_idx++;
    }

    FW_PRINT (FW_DEBUG, "rx_warmup_msg_handler called");
}

void rm_fbr_cfg_handler (void *data)
{
    rm_fbr_config_bf_t const *const p_fbr_cfg = (rm_fbr_config_bf_t *)data;
    uint32_t quad = 0;
    uint32_t fbr_mask = p_fbr_cfg->fbr_mask;
    FW_PRINT (FW_INFO, "Inside rm_fbr_cfg_handler fbr_mask=%d", fbr_mask);

    while (fbr_mask)
    {
        if (fbr_mask & 0x1)
        {
#ifdef DIG_CORE_CAL_EN
            ATOMIC_BEGIN;
            // todo: insert FBR cal to que
            if (rx_daco.adc_params[quad_idx].adc_fsm == e_ADC_FSM_RESET)
            {
                boot_ana (quad_idx);
            }
            // todo: if (fsm is e_ADC_FSM_IDLE && que not empty)
            ATOMIC_END;
#endif // DIG_CORE_CAL_EN

            rx_daco.adc_params[quad].digrf_mixer_freq = p_fbr_cfg->digrf_mixer_freq;
            rx_daco.adc_params[quad].fbr_idx = p_fbr_cfg->fbr_idx;
            // todo: setup adc fbr
        }
        quad++;
        fbr_mask >>= 1;
    }
    // todo: send cal interrupt per quad
}

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
msg_hdlr_t rx_hdlr_lut[] = {
    {.p_msg_hdlr_f = ul_spi_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_spi_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_spi_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_spi_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_on_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_update_control_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_UPDATE_CONTROL_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_UPDATE_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_UPDATE_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_off_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_config_ant_grp_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_CONFIG_ANT_GRP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = true},
    {.p_msg_hdlr_f = ul_warmup_handler,
     .p_range_check_f = NULL,
     .opcode = e_WARMUP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = false},
    {.p_msg_hdlr_f = rm_fbr_cfg_handler,
     .p_range_check_f = NULL,
     .opcode = e_RM_FBR_CONFIG_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = false},
    {.p_msg_hdlr_f = NULL, .p_range_check_f = NULL, .opcode = 0, .ref_act_ts = 0, .set_up_ts = 0, .is_schedulable = false}};

msg_irq_hdlr_map_t rx_msg_irq_hdlr_map[e_NUM_RX_MB_IRQ] = {
    {.msg_mb_irq = e_RX_SPI_GAIN_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)rx_spi_gain_msg_handler_irq},
    {.msg_mb_irq = e_AX_TO_RX_RM_MB_IRQ, .msg_isr_handler = (f_isr_handler_t)rx_rm_handler_irq},
};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           interrupt handler for RX Radio Message Handler
 * @param [in]      none
 * @return          none
 */

void rx_rm_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_IRQ_RM_MSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_AX_TO_RX_RM_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter RX RM Handler IRQ");
    msg_t read_test_msg;
    uint32_t read_test_msg_len = 0;
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_RX_RM_QUEUE);
    while (e_RET_QUEUE_EMPTY != com_queue_read (p_msg_queue, &read_test_msg, &read_test_msg_len))
    {
        uint32_t const opcode = com_msg_get_opcode (&read_test_msg);
        msg_hdlr_t const *msg_hdlr = com_msg_init_handler (opcode, rx_hdlr_lut);
        if (msg_hdlr)
            msg_hdlr->p_msg_hdlr_f (&read_test_msg);
        else
        {
            FW_SEND_ERR_RB (e_INVALID_OPCODE_ERR, opcode, e_RX_RM_QUEUE);
        }
    }
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_IRQ_RM_MSG);
}

/**
 * @brief           message handler for RX spi Gain  messages
 * @param [in]      none
 * @return          none
 */

void rx_spi_gain_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_UC_SMSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_RX_SPI_GAIN_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter RX SPI Gain Msg Handler IRQ");

    msg_t read_test_msg;
    uint32_t reg_data[4];

    // needs discussion on gain messages contents
    reg_data[0] = RCS_GPREG_EXT_TO_RCS_MB7_MBDATA0_REG->value;
    reg_data[1] = RCS_GPREG_EXT_TO_RCS_MB7_MBDATA1_REG->value;
    reg_data[2] = RCS_GPREG_EXT_TO_RCS_MB7_MBDATA2_REG->value;
    reg_data[3] = RCS_GPREG_EXT_TO_RCS_MB7_MBDATA3_REG->value;

    FW_PRINT (FW_INFO, " reg_data[0] = %u", reg_data[0]);
    FW_PRINT (FW_INFO, " reg_data[1] = %u", reg_data[1]);
    FW_PRINT (FW_INFO, " reg_data[2] = %u", reg_data[2]);
    FW_PRINT (FW_INFO, " reg_data[3] = %u", reg_data[3]);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_UC_SMSG);
}

void rx_cfg_msg_handler (ul_config_ant_grp_bf_t *const p_cfg_msg)
{
    uint16_t ant_mask = p_cfg_msg->ant_group_ul_ant_mask;
    uint8_t quad_idx = 0;
    uint32_t quad_stat[4] = {0};
    quad_params_t *p_quad_params = NULL;
    sys_params_t *p_sys_params = &rx_daco.sys_params;

    if (ant_mask & p_sys_params->rf_ant_mask)
    {
        FW_PRINT (FW_ERR, "trying to config already configured ANTs");
        return;
    }
    else
    {
        p_sys_params->rf_ant_mask |= ant_mask;
    }

    if (rx_daco.is_first_cfg)
    {
        e_sys_clk_t const f_clk = get_tf (com_drf_rate_conf_lut, p_cfg_msg->drf_rate, f_clk);
        com_bfn_set_clk_sel (f_clk);
        rx_daco.is_first_cfg = false;
        /*
                static cpu_adc_cpu_ctrl_reg_t const adc_start_reg = {.RUN_STALL = 0, .STATVECTORSEL =
           CPU_ADC_CPU_CTRL_STATVECTORSEL_BF_DEF}; *CPU_ADC_CPU_CTRL_REG (ANT0_CPU_BASE) = adc_start_reg; *CPU_ADC_CPU_CTRL_REG
           (ANT1_CPU_BASE) = adc_start_reg; *CPU_ADC_CPU_CTRL_REG (ANT2_CPU_BASE) = adc_start_reg; *CPU_ADC_CPU_CTRL_REG (ANT3_CPU_BASE) =
           adc_start_reg;
        */
    }
    /*
    #ifdef DIG_CORE_CAL_EN
        // ADC core boot and cal setup
        cpu_adc_cpu_ctrl_reg_t adc_start_reg = {.value = CPU_ADC_CPU_CTRL_DEFAULT};
        adc_start_reg.RUN_STALL = 0;
        *CPU_ADC_CPU_CTRL_REG (ANT0_CPU_BASE) = adc_start_reg;
        // uncomment below section if all antennae calibration is requested
        //    adc_start_reg.RUN_STALL = 0;
        //    *ANT_CSR_ADC_CPU_CONTROL_REG (ANT1_CSR_BASE) = adc_start_reg;
        //
        //    adc_start_reg.RUN_STALL = 0;
        //    *ANT_CSR_ADC_CPU_CONTROL_REG (ANT2_CSR_BASE) = adc_start_reg;
        //
        //    adc_start_reg.RUN_STALL = 0;
        //    *ANT_CSR_ADC_CPU_CONTROL_REG (ANT3_CSR_BASE) = adc_start_reg;

        uint32_t ant_request = 1; // For ANT0
        for (uint32_t i = 0; i < ant_request; i++)
        {
            if (rx_chk_ana_cpu_ready (i)) // Check for ANA CPU boot and ready
            {
                rx_adc_cpu_trigger_intrpt (e_SAR_CAL, i, 0, 0, 0, 1);
                event_schedule_adc_keepalive_event (5, 155, i); // todo: wait for: 5 us period X 155 cycles
            }
        }
    #endif
    */
    while (ant_mask)
    {
        if (ant_mask & 0xf)
        {
#ifdef DIG_CORE_CAL_EN
            ATOMIC_BEGIN;
            // todo: insert RX cal to que
            if (rx_daco.adc_params[quad_idx].adc_fsm == e_ADC_FSM_RESET)
            {
                boot_ana (quad_idx);
            }
            // todo: if (fsm is e_ADC_FSM_IDLE && que not empty)
            ATOMIC_END;
#endif // DIG_CORE_CAL_EN

            p_quad_params = &rx_daco.quad_params[quad_idx];
            // populating params:
            p_quad_params->com_params.drf_rate = p_cfg_msg->drf_rate;
            p_quad_params->com_params.drf_mixer_freq = p_cfg_msg->digrf_mixer_freq;

            p_quad_params->v2d_params.strm_cfg = p_cfg_msg->strm_cfg;

            p_quad_params->vha_params.band0_freq = p_cfg_msg->ant_group_ul_band_freq0;
            p_quad_params->vha_params.band1_freq = p_cfg_msg->ant_group_ul_band_freq1;
            quad_stat[quad_idx] = 1;
            p_sys_params->quad_mask |= 1 << quad_idx;
        }
        ant_mask >>= NUM_STRM_PER_QUAD;
        quad_idx++;
    }

    rx_lineup_cfg (p_cfg_msg->ant_group_ul_ant_mask);

    // readback enabled
    if (p_cfg_msg->rb)
    {
        // Readback message for CONFIG
        msg_t rb_msg;
        uint32_t rb_msg_len_byte = sizeof (ul_config_readback_bf_t);
        memset (&rb_msg.ul_config_readback, 0, rb_msg_len_byte);
        rb_msg.ul_config_readback.timestamp = com_timing_get_current_bfn_time ();
        rb_msg.ul_config_readback.opcode = e_RB_CONFIG_UL_OPCODE;
        rb_msg.ul_config_readback.src = RCS_CPU;
        rb_msg.ul_config_readback.config_status = 1;
        rb_msg.ul_config_readback.quad0 = quad_stat[0];
        rb_msg.ul_config_readback.quad1 = quad_stat[1];
        rb_msg.ul_config_readback.quad2 = quad_stat[2];
        rb_msg.ul_config_readback.quad3 = quad_stat[3];
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (rb_msg_len_byte));
    }

    FW_PRINT (FW_DEBUG, "rx_cfg_msg_handler called");
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX config ant_grp message
 * @param [in]      RX config ant_grp message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_config_ant_grp_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_CONFIG_MSG);
    FW_PRINT (FW_INFO, "Inside UL_CONFIG ANT GRP message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_config_ant_grp_bf_t ul_config_ant_grp = p_msg->ul_config_ant_grp;

    for (uint32_t i = 0; i < e_MAX_NUM_QUAD; i++)
    {
        if (ul_config_ant_grp.ant_group_ul_ant_mask & (0xF << (i * 4)))
        {
            status = com_fsm_quad_transition (e_FSM_RX, com_fsm_quad_get_status (e_FSM_RX, i), e_QUAD_EVENT_CONFIG, i);
            if (status == e_FSM_TRANSITION_RET_FAIL)
            {
                FW_PRINT (FW_ERR, "Quad FSM Transition failed");
                return;
            }
        }
    }

    status = com_fsm_transition (e_FSM_RX, com_fsm_get_status (e_FSM_RX), e_EVENT_CONFIG);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }

    int event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (event_idx);
    p_event->p_event_f = (p_event_func_t)rx_cfg_msg_handler;
    memcpy (p_event->context, &ul_config_ant_grp, sizeof (ul_config_ant_grp));
    com_event_execute_immediate_event (event_idx);

    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_CONFIG_MSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX WARMUP message
 * @param [in]      RX warmup message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void ul_warmup_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside UL_WARMUP message handler");
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_WARMUP_MSG);

    msg_t *p_msg = (msg_t *)data;
    warmup_bf_t warmup_msg = p_msg->warmup;
    com_fsm_transition_run (e_FSM_RX);
    com_fsm_transition_quadmask (e_FSM_RX, warmup_msg.ul_quad_en_mask, e_QUAD_EVENT_WARMUP);

    rx_warmup_msg_handler (&warmup_msg);

    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_WARMUP_MSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX ON message
 * @param [in]      RX ON message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_on_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_ON_MSG);
    FW_PRINT (FW_INFO, "Inside UL_ON message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_on_bf_t ul_on_msg = p_msg->ul_on;
    FW_PRINT (FW_INFO, "ul_on_msg->gain_ant0 = %d", ul_on_msg.gain_ant0);
    e_fsm_quad_event_type_t on_event = (ul_on_msg.opcode == e_UL_FAST_ON_OPCODE) ? e_QUAD_EVENT_ON_FAST : e_QUAD_EVENT_ON;

    status = com_fsm_transition_check_quadmask_transition (e_FSM_RX, ul_on_msg.quad_mask0, ul_on_msg.quad_mask1, ul_on_msg.quad_mask2,
                                                           ul_on_msg.quad_mask3, on_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    // readback enabled
    if (ul_on_msg.rb)
    {
        // Readback message  for ON
        msg_t rb_msg;
        uint32_t rb_msg_len_byte = sizeof (ul_on_readback_bf_t);
        memset (&rb_msg.ul_on_readback, 0, rb_msg_len_byte);
        rb_msg.ul_on_readback.opcode = e_RB_ON_UL_OPCODE;
        rb_msg.ul_on_readback.avg_0 = ul_on_msg.gain_ant0;
        rb_msg.ul_on_readback.avg_1 = ul_on_msg.gain_ant1;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (rb_msg_len_byte));
    }
    const uint32_t time_debug = ul_on_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, RX_ON_MSG, 1, RX_ON_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_ON_MSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX Update Control message
 * @param [in]      RX Update Control message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_update_control_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_UC_MSG);
    FW_PRINT (FW_INFO, "Inside UL_Update Control message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_update_control_bf_t ul_upd_ctrl = p_msg->ul_update_control;
    FW_PRINT (FW_INFO, "ul_update_ctrl_msg->gain_ant0 = %d", ul_upd_ctrl.gain_ant0);
    status = com_fsm_transition_check_quadmask_transition (e_FSM_RX, ul_upd_ctrl.quad_mask0, ul_upd_ctrl.quad_mask1, ul_upd_ctrl.quad_mask2,
                                                           ul_upd_ctrl.quad_mask3, e_QUAD_EVENT_UPDATE);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }
    // readback enabled
    if (ul_upd_ctrl.rb)
    {
        // sending readback
        msg_t rb_msg;
        memset (&rb_msg.ul_on_readback, 0, sizeof (ul_on_readback_bf_t));
        rb_msg.ul_on_readback.opcode = e_RB_ON_UL_OPCODE;
        rb_msg.ul_on_readback.avg_0 = ul_upd_ctrl.gain_ant0;
        rb_msg.ul_on_readback.avg_1 = ul_upd_ctrl.gain_ant1;
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (ul_on_readback_bf_t)));
    }
    const uint32_t time_debug = ul_upd_ctrl.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, RX_UC_MSG, 1, RX_UC_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_UC_MSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX off message
 * @param [in]      RX off message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_off_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_OFF_MSG);
    FW_PRINT (FW_INFO, "Inside UL_OFF message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_off_bf_t ul_off_msg = p_msg->ul_off;
    FW_PRINT (FW_INFO, "ul_off_msg->mode = %d", ul_off_msg.mode);
    e_fsm_quad_event_type_t off_event = com_fsm_off_mode_check (ul_off_msg.mode);
    off_event = (ul_off_msg.opcode == e_UL_FAST_OFF_OPCODE) ? e_QUAD_EVENT_OFF_FAST : off_event;
    status = com_fsm_transition_check_quadmask_transition (e_FSM_RX, ul_off_msg.quad_mask0, ul_off_msg.quad_mask1, ul_off_msg.quad_mask2,
                                                           ul_off_msg.quad_mask3, off_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    status = com_fsm_transition_off_stop (e_FSM_RX);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }
    const uint32_t time_debug = ul_off_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, RX_OFF_MSG, 1, RX_OFF_MSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_OFF_MSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX set reference message
 * @param [in]      RX set reference message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_set_time_ref_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside UL_SET_REF message handler");
    msg_t *p_msg = (msg_t *)data;
    set_time_ref_bf_t set_time_ref_msg = p_msg->set_time_ref;
    uint32_t curr_time = com_timing_get_current_bfn_time ();
    FW_PRINT (FW_INFO, "set_time_ref_msg.ref_index = %d,curr_time = %u ", set_time_ref_msg.ref_index, curr_time);
    com_msg_ref_timestamp_set (set_time_ref_msg.ref_index, curr_time);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX SPI ON message
 * @param [in]      RX SPI ON message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_spi_on_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_ON_SMSG);
    FW_PRINT (FW_INFO, "Inside UL_SPI_ON message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_spi_on_bf_t ul_spi_on_msg = p_msg->ul_spi_on;
    FW_PRINT (FW_INFO, "ul_spi_on_msg->quad_mask = %d", ul_spi_on_msg.quad_mask);

    status = com_fsm_transition_check_quadmask_transition (e_FSM_RX, ul_spi_on_msg.quad_mask, 0, 0, 0, e_QUAD_EVENT_ON);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    // readback enabled
    if (ul_spi_on_msg.rb)
    {
        msg_t rb_msg;
        memset (&rb_msg.ul_on_readback, 0, sizeof (ul_on_readback_bf_t));
        rb_msg.ul_on_readback.opcode = e_RB_ON_UL_OPCODE;
        rb_msg.ul_on_readback.avg_0 = 20; // place holder
        rb_msg.ul_on_readback.avg_1 = 30; // place holder
        com_msg_send_readback (&rb_msg, LEN_IN_WORD (sizeof (ul_on_readback_bf_t)));
    }
    const uint32_t time_debug = ul_spi_on_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, RX_ON_SMSG, 1, RX_ON_SMSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_ON_SMSG);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           callback function for RX SPI off message
 * @param [in]      RX SPI off message
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void ul_spi_off_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, RX_OFF_SMSG);
    FW_PRINT (FW_INFO, "Inside UL_SPI_OFF message handler");
    e_fsm_status_ret_type_t status = e_FSM_TRANSITION_RET_SUCCESS;
    msg_t *p_msg = (msg_t *)data;
    ul_spi_off_bf_t ul_spi_off_msg = p_msg->ul_spi_off;
    FW_PRINT (FW_INFO, "ul_spi_off_msg->mode = %d", ul_spi_off_msg.mode);

    e_fsm_quad_event_type_t off_event = com_fsm_off_mode_check (ul_spi_off_msg.mode);
    status = com_fsm_transition_check_quadmask_transition (e_FSM_RX, ul_spi_off_msg.quad_mask, 0, 0, 0, off_event);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Quad FSM Transition failed");
        return;
    }

    status = com_fsm_transition_off_stop (e_FSM_RX);
    if (status == e_FSM_TRANSITION_RET_FAIL)
    {
        FW_PRINT (FW_ERR, "Overall FSM Transition failed");
        return;
    }
    const uint32_t time_debug = ul_spi_off_msg.timestamp + com_trace_bfn_cpu_offset;
    com_debug_trace_buffer (e_TRACE_TIMESTAMP, RX_OFF_SMSG, 1, RX_OFF_SMSG, &time_debug);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, RX_OFF_SMSG);
}

// todo: need to add rx shutdown message
// todo: rx shutdown message have
//       rx_daco.is_first_cfg = true;
