/**************************************************************************
** INTEL CONFIDENTIAL
** Copyright 2024 Intel Corporation All Rights Reserved.
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
#include <elf.h>
#include <stdbool.h>

#include "srp.h"
#include "com_shared_memory_def.h"
#include "rcs_gpreg.h"
#include "srp_status.h"

#include "com_msg_def.h"

#include "srp_rcs_queue_if.h"

#define SHARED_MEM_BASE 0x00200000

struct rcs_system_status_memory *p_system_data = (struct rcs_system_status_memory *) (SHARED_MEM_BASE);

// tx functions
srp_st_t
srp_rcs_send_dl_config_ant_grp_msg(void *srp, msg_queue_t *p_msg_queue, dl_config_ant_grp_bf_t *dl_config_ant_grp_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(dl_config_ant_grp_bf_t));
	msg.dl_config_ant_grp = *dl_config_ant_grp_msg;
	if ((msg.dl_config_ant_grp.digrf_mixer_freq > 16777215) || (msg.dl_config_ant_grp.digrf_mixer_freq < 0)) {
		return SRP_ST_RCS_INVALID_DIGRF_MIXER_FREQ;
	}
	if ((msg.dl_config_ant_grp.drf_rate > 128) || (msg.dl_config_ant_grp.drf_rate < 0)) {
		return SRP_ST_RCS_INVALID_DRF_RATE;
	}
	if ((msg.dl_config_ant_grp.hw_tdd > 1) || (msg.dl_config_ant_grp.hw_tdd < 0)) {
		return SRP_ST_RCS_INVALID_HW_TDD;
	}
	if ((msg.dl_config_ant_grp.pdpd_rate > 7) || (msg.dl_config_ant_grp.pdpd_rate < 0)) {
		return SRP_ST_RCS_INVALID_PDPD_RATE;
	}
	if ((msg.dl_config_ant_grp.pdpd_mode > 7) || (msg.dl_config_ant_grp.pdpd_mode < 0)) {
		return SRP_ST_RCS_INVALID_PDPD_MODE;
	}
	if ((msg.dl_config_ant_grp.drf_filter_mode > 1) || (msg.dl_config_ant_grp.drf_filter_mode < 0)) {
		return SRP_ST_RCS_INVALID_DRF_FILTER_MODE;
	}
	if ((msg.dl_config_ant_grp.jesd_dl_idx > 95) || (msg.dl_config_ant_grp.jesd_dl_idx < 0)) {
		return SRP_ST_RCS_INVALID_JESD_DL_IDX;
	}
	if ((msg.dl_config_ant_grp.ant_group_dl_band_freq0 > 16777215) || (msg.dl_config_ant_grp.ant_group_dl_band_freq0 < 0)) {
		return SRP_ST_RCS_INVALID_ANT_GROUP_DL_BAND_FREQ;
	}
	if ((msg.dl_config_ant_grp.vha_rate > 10) || (msg.dl_config_ant_grp.vha_rate < 0)) {
		return SRP_ST_RCS_INVALID_VHA_RATE;
	}
	if ((msg.dl_config_ant_grp.ant_group_dl_band_freq1 > 16777215) || (msg.dl_config_ant_grp.ant_group_dl_band_freq1 < 0)) {
		return SRP_ST_RCS_INVALID_ANT_GROUP_DL_BAND_FREQ;
	}
	if ((msg.dl_config_ant_grp.vha_filter_mode > 1) || (msg.dl_config_ant_grp.vha_filter_mode < 0)) {
		return SRP_ST_RCS_INVALID_VHA_FILTER_MODE;
	}
	if ((msg.dl_config_ant_grp.pdpd_op_mode > 2) || (msg.dl_config_ant_grp.pdpd_op_mode < 0)) {
		return SRP_ST_RCS_INVALID_PDPD_OP_MODE;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_tx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_dl_off_msg(void *srp, msg_queue_t *p_msg_queue, dl_off_bf_t *dl_off_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(dl_off_bf_t));
	msg.dl_off = *dl_off_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_tx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_dl_on_msg(void *srp, msg_queue_t *p_msg_queue, dl_on_bf_t *dl_on_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(dl_on_bf_t));
	msg.dl_on = *dl_on_msg;
	if ((msg.dl_on.power_ant0 > 127) || (msg.dl_on.power_ant0 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant1 > 127) || (msg.dl_on.power_ant1 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant2 > 127) || (msg.dl_on.power_ant2 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant3 > 127) || (msg.dl_on.power_ant3 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant4 > 127) || (msg.dl_on.power_ant4 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant5 > 127) || (msg.dl_on.power_ant5 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant6 > 127) || (msg.dl_on.power_ant6 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant7 > 127) || (msg.dl_on.power_ant7 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant8 > 127) || (msg.dl_on.power_ant8 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant9 > 127) || (msg.dl_on.power_ant9 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant10 > 127) || (msg.dl_on.power_ant10 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant11 > 127) || (msg.dl_on.power_ant11 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant12 > 127) || (msg.dl_on.power_ant12 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant13 > 127) || (msg.dl_on.power_ant13 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant14 > 127) || (msg.dl_on.power_ant14 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_on.power_ant15 > 127) || (msg.dl_on.power_ant15 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_tx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_dl_update_control_msg(void *srp, msg_queue_t *p_msg_queue, dl_update_control_bf_t *dl_update_control_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(dl_update_control_bf_t));
	msg.dl_update_control = *dl_update_control_msg;
	if ((msg.dl_update_control.power_ant0 > 127) || (msg.dl_update_control.power_ant0 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant1 > 127) || (msg.dl_update_control.power_ant1 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant2 > 127) || (msg.dl_update_control.power_ant2 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant3 > 127) || (msg.dl_update_control.power_ant3 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant4 > 127) || (msg.dl_update_control.power_ant4 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant5 > 127) || (msg.dl_update_control.power_ant5 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant6 > 127) || (msg.dl_update_control.power_ant6 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant7 > 127) || (msg.dl_update_control.power_ant7 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant8 > 127) || (msg.dl_update_control.power_ant8 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant9 > 127) || (msg.dl_update_control.power_ant9 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant10 > 127) || (msg.dl_update_control.power_ant10 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant11 > 127) || (msg.dl_update_control.power_ant11 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant12 > 127) || (msg.dl_update_control.power_ant12 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant13 > 127) || (msg.dl_update_control.power_ant13 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant14 > 127) || (msg.dl_update_control.power_ant14 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	if ((msg.dl_update_control.power_ant15 > 127) || (msg.dl_update_control.power_ant15 < -128)) {
		return SRP_ST_RCS_INVALID_POWER_ANT;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_tx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

// rx functions
srp_st_t
srp_rcs_send_ul_config_ant_grp_msg(void *srp, msg_queue_t *p_msg_queue, ul_config_ant_grp_bf_t *ul_config_ant_grp_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(ul_config_ant_grp_bf_t));
	msg.ul_config_ant_grp = *ul_config_ant_grp_msg;
	if ((msg.ul_config_ant_grp.digrf_mixer_freq > 16777215) || (msg.ul_config_ant_grp.digrf_mixer_freq < 0)) {
		return SRP_ST_RCS_INVALID_DIGRF_MIXER_FREQ;
	}
	if ((msg.ul_config_ant_grp.drf_rate > 128) || (msg.ul_config_ant_grp.drf_rate < 0)) {
		return SRP_ST_RCS_INVALID_DRF_RATE;
	}
	if ((msg.ul_config_ant_grp.jesd_ul_idx > 95) || (msg.ul_config_ant_grp.jesd_ul_idx < 0)) {
		return SRP_ST_RCS_INVALID_JESD_UL_IDX;
	}
	if ((msg.ul_config_ant_grp.ant_group_ul_band_freq0 > 16777215) || (msg.ul_config_ant_grp.ant_group_ul_band_freq0 < 0)) {
		return SRP_ST_RCS_INVALID_ANT_GROUP_UL_BAND_FREQ;
	}
	if ((msg.ul_config_ant_grp.vha_rate > 10) || (msg.ul_config_ant_grp.vha_rate < 0)) {
		return SRP_ST_RCS_INVALID_VHA_RATE;
	}
	if ((msg.ul_config_ant_grp.vha_filter_mode > 1) || (msg.ul_config_ant_grp.vha_filter_mode < 0)) {
		return SRP_ST_RCS_INVALID_VHA_FILTER_MODE;
	}
	if ((msg.ul_config_ant_grp.ant_group_ul_band_freq1 > 16777215) || (msg.ul_config_ant_grp.ant_group_ul_band_freq1 < 0)) {
		return SRP_ST_RCS_INVALID_ANT_GROUP_UL_BAND_FREQ;
	}
	if ((msg.ul_config_ant_grp.hw_tdd > 1) || (msg.ul_config_ant_grp.hw_tdd < 0)) {
		return SRP_ST_RCS_INVALID_HW_TDD;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_rx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_ul_off_msg(void *srp, msg_queue_t *p_msg_queue, ul_off_bf_t *ul_off_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(ul_off_bf_t));
	msg.ul_off = *ul_off_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_rx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_ul_on_msg(void *srp, msg_queue_t *p_msg_queue, ul_on_bf_t *ul_on_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(ul_on_bf_t));
	msg.ul_on = *ul_on_msg;
	if ((msg.ul_on.gain_ant0 > 127) || (msg.ul_on.gain_ant0 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant1 > 127) || (msg.ul_on.gain_ant1 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant2 > 127) || (msg.ul_on.gain_ant2 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant3 > 127) || (msg.ul_on.gain_ant3 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant4 > 127) || (msg.ul_on.gain_ant4 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant5 > 127) || (msg.ul_on.gain_ant5 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant6 > 127) || (msg.ul_on.gain_ant6 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant7 > 127) || (msg.ul_on.gain_ant7 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant8 > 127) || (msg.ul_on.gain_ant8 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant9 > 127) || (msg.ul_on.gain_ant9 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant10 > 127) || (msg.ul_on.gain_ant10 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant11 > 127) || (msg.ul_on.gain_ant11 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant12 > 127) || (msg.ul_on.gain_ant12 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant13 > 127) || (msg.ul_on.gain_ant13 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant14 > 127) || (msg.ul_on.gain_ant14 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_on.gain_ant15 > 127) || (msg.ul_on.gain_ant15 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_rx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_ul_update_control_msg(void *srp, msg_queue_t *p_msg_queue, ul_update_control_bf_t *ul_update_control_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(ul_update_control_bf_t));
	msg.ul_update_control = *ul_update_control_msg;
	if ((msg.ul_update_control.gain_ant0 > 127) || (msg.ul_update_control.gain_ant0 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant1 > 127) || (msg.ul_update_control.gain_ant1 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant2 > 127) || (msg.ul_update_control.gain_ant2 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant3 > 127) || (msg.ul_update_control.gain_ant3 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant4 > 127) || (msg.ul_update_control.gain_ant4 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant5 > 127) || (msg.ul_update_control.gain_ant5 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant6 > 127) || (msg.ul_update_control.gain_ant6 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant7 > 127) || (msg.ul_update_control.gain_ant7 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant8 > 127) || (msg.ul_update_control.gain_ant8 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant9 > 127) || (msg.ul_update_control.gain_ant9 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant10 > 127) || (msg.ul_update_control.gain_ant10 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant11 > 127) || (msg.ul_update_control.gain_ant11 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant12 > 127) || (msg.ul_update_control.gain_ant12 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant13 > 127) || (msg.ul_update_control.gain_ant13 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant14 > 127) || (msg.ul_update_control.gain_ant14 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	if ((msg.ul_update_control.gain_ant15 > 127) || (msg.ul_update_control.gain_ant15 < -128)) {
		return SRP_ST_RCS_INVALID_GAIN_ANT;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_rx_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

// ad functions
srp_st_t
srp_rcs_send_bfn_sync_msg(void *srp, msg_queue_t *p_msg_queue, bfn_sync_bf_t *bfn_sync_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(bfn_sync_bf_t));
	msg.bfn_sync = *bfn_sync_msg;
	if ((msg.bfn_sync.bfn_sync_type > 1) || (msg.bfn_sync.bfn_sync_type < 0)) {
		return SRP_ST_RCS_INVALID_BFN_SYNC_TYPE;
	}
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_cal_config_msg(void *srp, msg_queue_t *p_msg_queue, cal_config_bf_t *cal_config_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(cal_config_bf_t));
	msg.cal_config = *cal_config_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_reconfig_msg(void *srp, msg_queue_t *p_msg_queue, reconfig_bf_t *reconfig_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(reconfig_bf_t));
	msg.reconfig = *reconfig_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_shutdown_msg(void *srp, msg_queue_t *p_msg_queue, shutdown_bf_t *shutdown_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(shutdown_bf_t));
	msg.shutdown = *shutdown_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_sleep_control_msg(void *srp, msg_queue_t *p_msg_queue, sleep_control_bf_t *sleep_control_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(sleep_control_bf_t));
	msg.sleep_control = *sleep_control_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

srp_st_t
srp_rcs_send_warmup_msg(void *srp, msg_queue_t *p_msg_queue, warmup_bf_t *warmup_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(warmup_bf_t));
	msg.warmup = *warmup_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}

// set functions
srp_st_t
srp_rcs_send_set_time_ref_msg(void *srp, msg_queue_t *p_msg_queue, set_time_ref_bf_t *set_time_ref_msg)
{
	msg_t msg;
	srp_uint32_t msg_len = LEN_IN_WORD(sizeof(set_time_ref_bf_t));
	msg.set_time_ref = *set_time_ref_msg;
	fw_msg_queue_insert(srp, p_msg_queue, &msg, msg_len);
	srp_rcs_set_admin_mailbox_interrupt(srp);
	return SRP_ST_SUCCESS;
}
