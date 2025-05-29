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
 * @file    ax_rx_msg_handler.c
 * @brief   Functions to handle rx messages in admin core
 * @details RX interrupt service routines and range checking by ax core.
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rcs_gpreg.h"
#include "com_bfn.h"
#include "com_event.h"
#include "com_isr.h"
#include "com_msg_handler_utils.h"
#include "com_msgs_enum.h"
#include "com_print.h"
#include "com_timing.h"
#include "com_shared_memory.h"
#include "com_msg_timing.h"
#include "com_trace_buffer.h"
#include "ax_rx_msg_handler.h"
#include "ax_jesd_config.h"
#include "ax_daco.h"
#include "ax_clk_rst.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define QUAD_BITS (4)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void ax_ul_config_handler (void *data);
static void ax_rx_spi_delayed_handler (void *p_msg);
static void ax_ul_jesd_config_handler (ul_config_ant_grp_bf_t *ul_config_ant_grp);

static void ul_config_ant_grp_range_check (msg_t *const p_msg);
static void ul_on_range_check (msg_t *const p_msg);
static void ul_update_control_range_check (msg_t *const p_msg);
static void ul_off_range_check (msg_t *const p_msg);

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
msg_hdlr_t ax_rx_hdlr_lut[] = {
    {.p_msg_hdlr_f = ax_ul_config_handler,
     .p_range_check_f = ul_config_ant_grp_range_check,
     .opcode = e_UL_CONFIG_ANT_GRP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = ul_on_range_check,
     .opcode = e_UL_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = ul_on_range_check,
     .opcode = e_UL_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = ul_update_control_range_check,
     .opcode = e_UL_UPDATE_CONTROL_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_UPDATE_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_UPDATE_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = ul_off_range_check,
     .opcode = e_UL_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = ul_off_range_check,
     .opcode = e_UL_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = NULL,
     .p_range_check_f = NULL,
     .opcode = 0,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = false},
};

msg_hdlr_t ax_rx_spi_hdlr_lut[] = {

    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_rx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_UL_SPI_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (UL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (UL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = NULL,
     .p_range_check_f = NULL,
     .opcode = 0,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = false},
};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           copies the message into the Radio message queue and configures JESD
 * @param [in]      message
 * @return          none
 */
static void ax_ul_config_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside AX UL Config handler");
    msg_t *p_msg = (msg_t *)data;
    ul_config_ant_grp_bf_t *ul_config_ant_grp = &p_msg->ul_config_ant_grp;
    ax_daco_t *p_ax_daco = ax_daco_get_addr ();
    if (ax_daco_set_quad_antenna_mask (ul_config_ant_grp->ant_group_ul_ant_mask, (uint32_t)ul_config_ant_grp->opcode,
                                       &p_ax_daco->rx_cfg_quads)
        == e_CFG_SUCCESS)
    {
        if (p_ax_daco->is_first_cfg)
        {
            p_ax_daco->cfg_pll_info.ewpll_sel =
                (ul_config_ant_grp->ant_group_ul_ant_mask & 0xFF) ? e_EWPLL_SEL_EAST : e_EWPLL_SEL_WEST; // todo: need update

            platform_clk_sel_t const clk_sel = {.clk_sys = e_CLK_983M,                   // todo: need update
                                                .clk_ref_desel = e_CLK_REF_DESEL_PLL,    // todo: need update
                                                .pll_band_sel = e_PLL_BAND_SEL_BOTH_16G, // todo: need update
                                                .ewpll_sel = p_ax_daco->cfg_pll_info.ewpll_sel,
                                                .en_jesd = false, // set to false to allow component owner manage clock/rst
                                                .en_v2d = false,  // set to false to allow component owner manage clock/rst
                                                .jesd_mask = 0x0,
                                                .ant_mask = (uint16_t)ul_config_ant_grp->ant_group_ul_ant_mask};

            ax_clk_rst_init (&clk_sel);
            com_bfn_set_clk_sel (clk_sel.clk_sys);
            com_bfn_init (); // start main bfn only
            p_ax_daco->is_first_cfg = false;
        }

        ax_ul_jesd_config_handler (ul_config_ant_grp);
        ax_rx_activate_handler (p_msg);
    }
}

/**
 * @brief          Delayed Service Routine takes the message from event context and runs the macro_scheduling routine to parse/check and
 * schedule the execution.
 * @param [in]      none
 * @return          none
 */
static void ax_rx_spi_delayed_handler (void *p_msg)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_RX_DELAY_SMSG);
    com_msg_schedule_macro (p_msg, ax_rx_spi_hdlr_lut, e_RX_SPI_REG_QUEUE);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_RX_DELAY_SMSG);
}

/**
 * @brief           checks for violations in RX ant_grp config message range spec
 * @param [in]      RX config ant_grp message
 * @return          none
 */

static void ul_config_ant_grp_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside UL_CONFIG  ANT GRP range check ");
    ul_config_ant_grp_bf_t ul_config_ant_grp = p_msg->ul_config_ant_grp;
    FW_PRINT (FW_INFO, "ant_group_ul_band_freq0 = %d", ul_config_ant_grp.ant_group_ul_band_freq0);
}

/**
 * @brief           checks for violations in RX ON message range spec
 * @param [in]      RX ON message
 * @return          none
 */
static void ul_on_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside UL_ON range check");
    ul_on_bf_t ul_on_msg = p_msg->ul_on;
    FW_PRINT (FW_INFO, "ul_on_msg->gain_ant0 = %d", ul_on_msg.gain_ant0);
}

/**
 * @brief           checks for violations in RX Update Control message range spec
 * @param [in]      RX Update Control message
 * @return          none
 */
static void ul_update_control_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside UL_Update Control range check");
    ul_update_control_bf_t ul_upd_ctrl = p_msg->ul_update_control;
    FW_PRINT (FW_INFO, "ul_upd_ctrl_msg->gain_ant0 = %d", ul_upd_ctrl.gain_ant0);
}

/**
 * @brief           checks for violations in RX OFF message range spec
 * @param [in]      RX OFF message
 * @return          none
 */
static void ul_off_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside UL_OFF range check");
    ul_off_bf_t ul_off_msg = p_msg->ul_off;
    FW_PRINT (FW_INFO, "ul_off_msg->mode = %d", ul_off_msg.mode);
}

/**
 * @brief           Handler for RX JESD config messages
 * @param [in]      JESD config data
 * @return          none
 */

static void ax_ul_jesd_config_handler (ul_config_ant_grp_bf_t *ul_config_ant_grp)
{
    FW_PRINT (FW_INFO, "Inside RF RX, JESD TX config handler");

    uint32_t ant_enabled = ul_config_ant_grp->ant_group_ul_ant_mask;

    ax_daco_t *const p_ax_daco = ax_daco_get_addr ();
    cfg_jesd_t *const jesd_tx_cfg = &p_ax_daco->jesd_tx_cfg;

    jesd_tx_cfg->use_case_idx = (uint32_t)ul_config_ant_grp->jesd_ul_idx;
    uint32_t quad_id = 0;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_tx_cfg->jesd_quad_map[0] = ul_config_ant_grp->q0_j;
        jesd_tx_cfg->mask |= 1 << ul_config_ant_grp->q0_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_tx_cfg->jesd_quad_map[1] = ul_config_ant_grp->q1_j;
        jesd_tx_cfg->mask = 1 << ul_config_ant_grp->q1_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_tx_cfg->jesd_quad_map[2] = ul_config_ant_grp->q2_j;
        jesd_tx_cfg->mask = 1 << ul_config_ant_grp->q2_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_tx_cfg->jesd_quad_map[3] = ul_config_ant_grp->q3_j;
        jesd_tx_cfg->mask = 1 << ul_config_ant_grp->q3_j;
    }
    ax_config_jesd_tx ();
}
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           message handler for RX queue messages
 * @param [in]      none
 * @return          none
 */

void ax_rx_queue_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_RX_IRQ_MSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_RX_QUEUE_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter  RX Msg Handler IRQ");
    msg_t read_test_msg;
    msg_hdlr_t msg_hdlr;
    uint32_t read_test_msg_len = 0;
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_RX_QUEUE);
    while (e_RET_QUEUE_EMPTY != com_queue_read (p_msg_queue, &read_test_msg, &read_test_msg_len))
    {
        com_msg_schedule_macro (&read_test_msg, ax_rx_hdlr_lut, e_RX_QUEUE);
    }
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_RX_IRQ_MSG);
}

/**
 * @brief           ISR for UL SPI messages.Reads the data, store the message in an event.
 * @param [in]      none
 * @return          none
 */

void ax_rx_spi_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_RX_IRQ_SMSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_RX_SPI_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter RX SPI Msg Handler IRQ");

    int event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (event_idx);

    uint32_t *reg_data = (uint32_t *)p_event->context;
    reg_data[0] = RCS_GPREG_EXT_TO_RCS_MB3_MBDATA2_REG->value;
    reg_data[1] = RCS_GPREG_EXT_TO_RCS_MB3_MBDATA3_REG->value;
    FW_PRINT (FW_INFO, " reg_data[0] = %x", reg_data[0]);
    FW_PRINT (FW_INFO, " reg_data[1] = %x", reg_data[1]);

    p_event->p_event_f = ax_rx_spi_delayed_handler;
    com_event_execute_immediate_event (event_idx);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_RX_IRQ_SMSG);
}

/**
 * @brief           copies the message into the Radio message queue
 * @param [in]      message
 * @return          none
 */

void ax_rx_activate_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_RX_ACTIVATE_SMSG);
    FW_PRINT (FW_INFO, "Inside SPI_ACTIVATE handler");
    msg_t *p_msg = (msg_t *)data;

    // Send RM to RX.
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_RX_RM_QUEUE);
    com_queue_insert (p_msg_queue, p_msg, LEN_IN_WORD (sizeof (msg_t)));

    com_mb_isr_trigger ((e_com_int_mb_sel_t)e_AX_TO_RX_RM_MB_IRQ, 0xBEEF);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_RX_ACTIVATE_SMSG);
}
