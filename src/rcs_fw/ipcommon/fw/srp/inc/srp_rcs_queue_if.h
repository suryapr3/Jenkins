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

/*! @file      srp_rcs_queue_if.h
 *  @brief     Radio Control Subsystem
 */

#ifndef __SRP_RCS_QUEUE_IF_H__
#define __SRP_RCS_QUEUE_IF_H__

/*!
 *  @addtogroup _rcs_ Radio Control Subsystem
 *
 *  @{
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "srp_status.h"
#include "com_msg_def.h"
#include "com_queue_def.h"

// Readback Functions
/*! @fn srp_st_t srp_rcs_read_back_msg(void *srp, msg_queue_t *p_msg_queue, msg_t *read_msg)
 *   @brief gives the contents of Readback message queue
 *   @param srp Incoming handle of the SRP instance
 *   @param p_msg_queue pointer to the message queue
 *   @param p_msg pointer to the message that is read from queue
 * @return Success Code:
 *  \li ::SRP_ST_SUCCESS
 * @return Error Codes:
 *  \li ::SRP_ST_RCS_SHM_RB_QUEUE_EMPTY
 */
srp_st_t srp_rcs_fw_msg_read(void *srp, msg_queue_t *p_msg_queue, msg_t *read_msg);

/*! @fn srp_rcs_set_tx_mailbox_interrupt(void *srp);
 *	@brief sends TX mailbox interrupt to RCS
 *	@param srp Incoming handle of the SRP instance
 *
 */
void srp_rcs_set_tx_mailbox_interrupt(void *srp);

/*! @fn srp_rcs_set_rx_mailbox_interrupt(void *srp);
 *	@brief sends RX mailbox interrupt to RCS
 *	@param srp Incoming handle of the SRP instance
 *
 */
void srp_rcs_set_rx_mailbox_interrupt(void *srp);

/*! @fn srp_rcs_set_admin_mailbox_interrupt(void *srp);
 *	@brief sends ADMIN mailbox interrupt to RCS
 *	@param srp Incoming handle of the SRP instance
 *
 */
void srp_rcs_set_admin_mailbox_interrupt(void *srp);

// Queue Functions

/*! @fn msg_queue_t *srp_rcs_get_shared_mem_get_queue_block (queue_type_t queue_idx)
 *	@brief get the shared memory allocation for the  message queue type
 *	@param queue_idx :TX/RX/ADMIN/RB refer to com_queue_def.h
 *	@retval pointer to the  message queue
 */
msg_queue_t *srp_rcs_get_shared_mem_get_queue_block(e_queue_type_t queue_idx);

#ifdef __cplusplus
}
#endif

/*!
 *  @}
 *
 */

#endif /* __SRP_RCS_FW_IF_H__ */
