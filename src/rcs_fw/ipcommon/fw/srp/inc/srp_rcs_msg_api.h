/**************************************************************************
** INTEL CONFIDENTIAL
** Copyright 2023 Intel Corporation All Rights Reserved.
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

/*! @file      srp_rcs_msg_api.h
 *  @brief     Radio Control Subsystem FW Message handlers
 *
 *  @addtogroup _rcs_ Radio Control Subsystem
 *
 *  @{
 */

#ifndef __SRP_RCS_MSG_API_H__
#define __SRP_RCS_MSG_API_H__

#include "dl_req_msg.h"
#include "ul_req_msg.h"
#include "readback_msg.h"
#include "com_queue_def.h"

//TX FUNCTIONS

/*! @fn srp_st_t srp_rcs_send_dl_config_ant_grp_msg (void *srp, msg_queue_t *p_msg_queue, dl_config_ant_grp_bf_t *dl_config_ant_grp_msg);
    @brief Send the TX config ant grp message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param dl_config_ant_grp_msg TX config ant grp message structure
*/

srp_st_t srp_rcs_send_dl_config_ant_grp_msg (void *srp, msg_queue_t *p_msg_queue, dl_config_ant_grp_bf_t *dl_config_ant_grp_msg);


/*! @fn srp_st_t srp_rcs_send_dl_off_msg (void *srp, msg_queue_t *p_msg_queue, dl_off_bf_t *dl_off_msg);
    @brief Send the TX off message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param dl_off_msg TX off message structure
*/

srp_st_t srp_rcs_send_dl_off_msg (void *srp, msg_queue_t *p_msg_queue, dl_off_bf_t *dl_off_msg);


/*! @fn srp_st_t srp_rcs_send_dl_on_msg (void *srp, msg_queue_t *p_msg_queue, dl_on_bf_t *dl_on_msg);
    @brief Send the TX on message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param dl_on_msg TX on message structure
*/

srp_st_t srp_rcs_send_dl_on_msg (void *srp, msg_queue_t *p_msg_queue, dl_on_bf_t *dl_on_msg);


/*! @fn srp_st_t srp_rcs_send_dl_update_control_msg (void *srp, msg_queue_t *p_msg_queue, dl_update_control_bf_t *dl_update_control_msg);
    @brief Send the TX update control message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param dl_update_control_msg TX update control message structure
*/

srp_st_t srp_rcs_send_dl_update_control_msg (void *srp, msg_queue_t *p_msg_queue, dl_update_control_bf_t *dl_update_control_msg);


//RX FUNCTIONS

/*! @fn srp_st_t srp_rcs_send_ul_config_ant_grp_msg (void *srp, msg_queue_t *p_msg_queue, ul_config_ant_grp_bf_t *ul_config_ant_grp_msg);
    @brief Send the RX config ant grp message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param ul_config_ant_grp_msg RX config ant grp message structure
*/

srp_st_t srp_rcs_send_ul_config_ant_grp_msg (void *srp, msg_queue_t *p_msg_queue, ul_config_ant_grp_bf_t *ul_config_ant_grp_msg);


/*! @fn srp_st_t srp_rcs_send_ul_off_msg (void *srp, msg_queue_t *p_msg_queue, ul_off_bf_t *ul_off_msg);
    @brief Send the RX off message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param ul_off_msg RX off message structure
*/

srp_st_t srp_rcs_send_ul_off_msg (void *srp, msg_queue_t *p_msg_queue, ul_off_bf_t *ul_off_msg);


/*! @fn srp_st_t srp_rcs_send_ul_on_msg (void *srp, msg_queue_t *p_msg_queue, ul_on_bf_t *ul_on_msg);
    @brief Send the RX on message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param ul_on_msg RX on message structure
*/

srp_st_t srp_rcs_send_ul_on_msg (void *srp, msg_queue_t *p_msg_queue, ul_on_bf_t *ul_on_msg);


/*! @fn srp_st_t srp_rcs_send_ul_update_control_msg (void *srp, msg_queue_t *p_msg_queue, ul_update_control_bf_t *ul_update_control_msg);
    @brief Send the RX update control message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param ul_update_control_msg RX update control message structure
*/

srp_st_t srp_rcs_send_ul_update_control_msg (void *srp, msg_queue_t *p_msg_queue, ul_update_control_bf_t *ul_update_control_msg);


//AD FUNCTIONS

/*! @fn srp_st_t srp_rcs_send_bfn_sync_msg (void *srp, msg_queue_t *p_msg_queue, bfn_sync_bf_t *bfn_sync_msg);
    @brief Send the  sync message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param bfn_sync_msg  sync message structure
*/

srp_st_t srp_rcs_send_bfn_sync_msg (void *srp, msg_queue_t *p_msg_queue, bfn_sync_bf_t *bfn_sync_msg);


/*! @fn srp_st_t srp_rcs_send_cal_config_msg (void *srp, msg_queue_t *p_msg_queue, cal_config_bf_t *cal_config_msg);
    @brief Send the  config message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param cal_config_msg  config message structure
*/

srp_st_t srp_rcs_send_cal_config_msg (void *srp, msg_queue_t *p_msg_queue, cal_config_bf_t *cal_config_msg);


/*! @fn srp_st_t srp_rcs_send_reconfig_msg (void *srp, msg_queue_t *p_msg_queue, reconfig_bf_t *reconfig_msg);
    @brief Send the  reconfig message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param reconfig_msg  reconfig message structure
*/

srp_st_t srp_rcs_send_reconfig_msg (void *srp, msg_queue_t *p_msg_queue, reconfig_bf_t *reconfig_msg);


/*! @fn srp_st_t srp_rcs_send_shutdown_msg (void *srp, msg_queue_t *p_msg_queue, shutdown_bf_t *shutdown_msg);
    @brief Send the  shutdown message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param shutdown_msg  shutdown message structure
*/

srp_st_t srp_rcs_send_shutdown_msg (void *srp, msg_queue_t *p_msg_queue, shutdown_bf_t *shutdown_msg);


/*! @fn srp_st_t srp_rcs_send_sleep_control_msg (void *srp, msg_queue_t *p_msg_queue, sleep_control_bf_t *sleep_control_msg);
    @brief Send the  control message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param sleep_control_msg  control message structure
*/

srp_st_t srp_rcs_send_sleep_control_msg (void *srp, msg_queue_t *p_msg_queue, sleep_control_bf_t *sleep_control_msg);


/*! @fn srp_st_t srp_rcs_send_warmup_msg (void *srp, msg_queue_t *p_msg_queue, warmup_bf_t *warmup_msg);
    @brief Send the  warmup message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param warmup_msg  warmup message structure
*/

srp_st_t srp_rcs_send_warmup_msg (void *srp, msg_queue_t *p_msg_queue, warmup_bf_t *warmup_msg);


//SET FUNCTIONS

/*! @fn srp_st_t srp_rcs_send_set_time_ref_msg (void *srp, msg_queue_t *p_msg_queue, set_time_ref_bf_t *set_time_ref_msg);
    @brief Send the  time ref message
    @param srp Incoming handle of the current RCS module instance
    @param p_msg_queue pointer to the message queue
    @param set_time_ref_msg  time ref message structure
*/

srp_st_t srp_rcs_send_set_time_ref_msg (void *srp, msg_queue_t *p_msg_queue, set_time_ref_bf_t *set_time_ref_msg);


#endif
