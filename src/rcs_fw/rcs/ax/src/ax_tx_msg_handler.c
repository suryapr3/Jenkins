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
 * @file    ax_tx_msg_handler.c
 * @brief   Functions to handle tx messages in admin core
 * @details TX interrupt service routines and range checking by ax core.
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
#include "com_assert.h"
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
#include "com_rm_def.h"
#include "ax_clk_rst.h"
#include "ax_jesd_config.h"
#include "ax_daco.h"
#include "ax_tx_msg_handler.h"

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
static void ax_dl_config_handler (void *data);
static void ax_tx_spi_delayed_handler (void *p_msg);
static void ax_tx_jesd_config_handler (dl_config_ant_grp_bf_t *dl_config_ant_grp);

static void dl_config_ant_grp_range_check (msg_t *const p_msg);
static void dl_on_range_check (msg_t *const p_msg);
static void dl_update_control_range_check (msg_t *const p_msg);
static void dl_off_range_check (msg_t *const p_msg);
static void rm_fbr_cfg (dl_config_ant_grp_bf_t *const p_dl_config_ant_grp);

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern void ax_rx_activate_handler (void *data);
msg_hdlr_t ax_tx_hdlr_lut[] = {
    {.p_msg_hdlr_f = ax_dl_config_handler,
     .p_range_check_f = dl_config_ant_grp_range_check,
     .opcode = e_DL_CONFIG_ANT_GRP_OPCODE,
     .ref_act_ts = 0,
     .set_up_ts = 0,
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = dl_on_range_check,
     .opcode = e_DL_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = dl_on_range_check,
     .opcode = e_DL_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = dl_update_control_range_check,
     .opcode = e_DL_UPDATE_CONTROL_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_UPDATE_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_UPDATE_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = dl_off_range_check,
     .opcode = e_DL_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = dl_off_range_check,
     .opcode = e_DL_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = NULL, .p_range_check_f = NULL, .opcode = 0, .ref_act_ts = 0, .set_up_ts = 0, .is_schedulable = false},
};

msg_hdlr_t ax_tx_spi_hdlr_lut[] = {

    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_FAST_ON_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_ON_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_ON_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = ax_tx_activate_handler,
     .p_range_check_f = NULL,
     .opcode = e_DL_SPI_FAST_OFF_OPCODE,
     .ref_act_ts = US_TO_BFN_TICKS (DL_FAST_OFF_REF_ACT_TS_US),
     .set_up_ts = US_TO_BFN_TICKS (DL_FAST_OFF_SET_UP_TS_US),
     .is_schedulable = true},
    {.p_msg_hdlr_f = NULL, .p_range_check_f = NULL, .opcode = 0, .ref_act_ts = 0, .set_up_ts = 0, .is_schedulable = false},
};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           copies the message into the Radio message queue and configures JESD
 * @param [in]      message
 * @return          none
 */
static void ax_dl_config_handler (void *data)
{
    FW_PRINT (FW_INFO, "Inside AX DL Config handler");
    msg_t *p_msg = (msg_t *)data;
    dl_config_ant_grp_bf_t *dl_config_ant_grp = &p_msg->dl_config_ant_grp;

    ax_daco_t *p_ax_daco = ax_daco_get_addr ();
    if (ax_daco_set_quad_antenna_mask (dl_config_ant_grp->ant_group_dl_ant_mask, (uint32_t)dl_config_ant_grp->opcode,
                                       &p_ax_daco->tx_cfg_quads)
        == e_CFG_SUCCESS)
    {
        if (p_ax_daco->is_first_cfg)
        {
            p_ax_daco->cfg_pll_info.ewpll_sel =
                (dl_config_ant_grp->ant_group_dl_ant_mask & 0xFF) ? e_EWPLL_SEL_EAST : e_EWPLL_SEL_WEST; // todo: need update

            platform_clk_sel_t const clk_sel = {.clk_sys = e_CLK_983M,                          // todo: need update
                                                .clk_ref_desel = e_CLK_REF_DESEL_PLL,           // todo: need update
                                                .pll_band_sel = e_PLL_BAND_SEL_BOTH_16G,        // todo: need update
                                                .ewpll_sel = p_ax_daco->cfg_pll_info.ewpll_sel, // todo: need update
                                                .en_jesd = false, // set to false to allow component owner manage clock/rst
                                                .en_v2d = false,  // set to false to allow component owner manage clock/rst
                                                .jesd_mask = 0x0,
                                                .ant_mask = (uint16_t)dl_config_ant_grp->ant_group_dl_ant_mask};

            ax_clk_rst_init (&clk_sel);
            com_bfn_set_clk_sel (clk_sel.clk_sys);
            com_bfn_init (); // start main bfn only
            p_ax_daco->is_first_cfg = false;
        }

        ax_tx_jesd_config_handler (dl_config_ant_grp); // JESD clk is turned on here
        ax_tx_activate_handler (p_msg);

        if (dl_config_ant_grp->fbr_mask)
        {
            rm_fbr_cfg (dl_config_ant_grp);
        }
    };
}

/**
 * @brief          Delayed Service Routine takes the message from event context and runs the macro_scheddling routine to parse/check and
 * scheddle the execution.
 * @param [in]      none
 * @return          none
 */
static void ax_tx_spi_delayed_handler (void *p_msg)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_TX_DELAY_SMSG);
    com_msg_schedule_macro (p_msg, ax_tx_spi_hdlr_lut, e_TX_SPI_REG_QUEUE);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_TX_DELAY_SMSG);
}

/**
 * @brief           checks for violations in TX ant_grp config message range spec
 * @param [in]      TX config ant_grp message
 * @return          none
 */

static void dl_config_ant_grp_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside DL_CONFIG  ANT GRP range check ");
    dl_config_ant_grp_bf_t dl_config_ant_grp = p_msg->dl_config_ant_grp;
    FW_PRINT (FW_INFO, "ant_group_dl_band_freq0 = %d", dl_config_ant_grp.ant_group_dl_band_freq0);
}

/**
 * @brief           checks for violations in TX ON message range spec
 * @param [in]      TX ON message
 * @return          none
 */
static void dl_on_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside DL_ON range check");
    dl_on_bf_t dl_on_msg = p_msg->dl_on;
    FW_PRINT (FW_INFO, "dl_on_msg->power_ant0 = %d", dl_on_msg.power_ant0);
}

/**
 * @brief           checks for violations in TX Update Control message range spec
 * @param [in]      TX Update Control message
 * @return          none
 */
static void dl_update_control_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside DL_Update Control range check");
    dl_update_control_bf_t dl_upd_ctrl = p_msg->dl_update_control;
    FW_PRINT (FW_INFO, "dl_upd_ctrl_msg->power_ant0 = %d", dl_upd_ctrl.power_ant0);
}

/**
 * @brief           checks for violations in TX OFF message range spec
 * @param [in]      TX OFF message
 * @return          none
 */
static void dl_off_range_check (msg_t *const p_msg)
{
    FW_PRINT (FW_INFO, "Inside DL_OFF range check");
    dl_off_bf_t dl_off_msg = p_msg->dl_off;
    FW_PRINT (FW_INFO, "dl_off_msg->mode = %d", dl_off_msg.mode);
}

/**
 * @brief           Handler for TX JESD config messages
 * @param [in]      JESD config data
 * @return          none
 */
static void ax_tx_jesd_config_handler (dl_config_ant_grp_bf_t *dl_config_ant_grp)
{
    FW_PRINT (FW_INFO, "Inside RF TX, JESD RX config handler");

    uint32_t ant_enabled = dl_config_ant_grp->ant_group_dl_ant_mask;

    ax_daco_t *p_ax_daco = ax_daco_get_addr ();
    cfg_jesd_t *jesd_rx_cfg = &p_ax_daco->jesd_rx_cfg;

    jesd_rx_cfg->use_case_idx = dl_config_ant_grp->jesd_dl_idx;
    uint32_t quad_id = 0;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_rx_cfg->jesd_quad_map[0] = dl_config_ant_grp->q0_j;
        jesd_rx_cfg->mask = 1 << dl_config_ant_grp->q0_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_rx_cfg->jesd_quad_map[1] = dl_config_ant_grp->q1_j;
        jesd_rx_cfg->mask = 1 << dl_config_ant_grp->q1_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_rx_cfg->jesd_quad_map[2] = dl_config_ant_grp->q2_j;
        jesd_rx_cfg->mask = 1 << dl_config_ant_grp->q2_j;
    }
    quad_id = quad_id + QUAD_BITS;
    if (ant_enabled & (0xF << (quad_id)))
    {
        jesd_rx_cfg->jesd_quad_map[3] = dl_config_ant_grp->q3_j;
        jesd_rx_cfg->mask = 1 << dl_config_ant_grp->q3_j;
    }
    ax_config_jesd_rx ();
}

/**
 * @brief           Send FBR config message to RX
 * @param [in]      JESD config data
 * @return          none
 */
static void rm_fbr_cfg (dl_config_ant_grp_bf_t *const p_dl_config_ant_grp)
{
    static rm_fbr_config_bf_t fbr_cfg_msg = {.opcode = e_RM_FBR_CONFIG_OPCODE};
    fbr_cfg_msg.digrf_mixer_freq = p_dl_config_ant_grp->digrf_mixer_freq;
    fbr_cfg_msg.fbr_idx = p_dl_config_ant_grp->fbr_idx;
    fbr_cfg_msg.fbr_mask = p_dl_config_ant_grp->fbr_mask;
    ax_rx_activate_handler (&fbr_cfg_msg);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
COMPILE_ASSERT (sizeof (msg_rm_t) <= sizeof (msg_t));

/**
 * @brief           message handler for TX queue messages
 * @param [in]      none
 * @return          none
 */

void ax_tx_queue_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_TX_IRQ_MSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_TX_QUEUE_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter  TX Msg Handler IRQ");
    msg_t read_test_msg;
    msg_hdlr_t msg_hdlr;
    uint32_t read_test_msg_len = 0;
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_TX_QUEUE);
    while (e_RET_QUEUE_EMPTY != com_queue_read (p_msg_queue, &read_test_msg, &read_test_msg_len))
    {
        com_msg_schedule_macro (&read_test_msg, ax_tx_hdlr_lut, e_TX_QUEUE);
    }
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_TX_IRQ_MSG);
}

/**
 * @brief           ISR for DL SPI messages.Reads the data, store the message in an event.
 * @param [in]      none
 * @return          none
 */

void ax_tx_spi_msg_handler_irq (void *unused)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_TX_IRQ_SMSG);
    com_mb_isr_clear ((e_com_int_mb_sel_t)e_TX_SPI_MB_IRQ);

    FW_PRINT (FW_INFO, "Enter TX SPI Msg Handler IRQ");

    int event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (event_idx);

    uint32_t *reg_data = (uint32_t *)p_event->context;
    reg_data[0] = RCS_GPREG_EXT_TO_RCS_MB1_MBDATA2_REG->value;
    reg_data[1] = RCS_GPREG_EXT_TO_RCS_MB1_MBDATA3_REG->value;
    FW_PRINT (FW_INFO, " reg_data[0] = %x", reg_data[0]);
    FW_PRINT (FW_INFO, " reg_data[1] = %x", reg_data[1]);

    p_event->p_event_f = ax_tx_spi_delayed_handler;
    com_event_execute_immediate_event (event_idx);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_TX_IRQ_SMSG);
}

/**
 * @brief           copies the message into the Radio message queue
 * @param [in]      message
 * @return          none
 */

void ax_tx_activate_handler (void *data)
{
    com_func_ts_trace_buffer (e_TRACE_FUNC_START, AX_TX_ACTIVATE_SMSG);
    FW_PRINT (FW_INFO, "Inside SPI_ACTIVATE handler");
    msg_t *p_msg = (msg_t *)data;

    // Send RM to TX.
    msg_queue_t *p_msg_queue = com_shared_mem_get_queue_block (e_TX_RM_QUEUE);
    com_queue_insert (p_msg_queue, p_msg, LEN_IN_WORD (sizeof (msg_t)));

    com_mb_isr_trigger ((e_com_int_mb_sel_t)e_AX_TO_TX_RM_MB_IRQ, 0xBEEF);
    com_func_ts_trace_buffer (e_TRACE_FUNC_END, AX_TX_ACTIVATE_SMSG);
}
