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

#include "srp.h"
#include "com_shared_memory_def.h"
#include "com_msg_def.h"
#include "rcs_gpreg.h"
#include "com_queue_def.h"
#include "com_device_api.h"

// Readback function
srp_st_t
srp_rcs_fw_msg_read(void *srp, msg_queue_t *p_msg_queue, msg_t *read_msg)
{
	int32_t read_msg_len = 0;
	srp_st_t ret_status = SRP_ST_SUCCESS;

	if (fw_msg_queue_read(srp, p_msg_queue, read_msg, &read_msg_len) == e_RET_QUEUE_EMPTY) {
		ret_status = SRP_ST_RCS_SHM_RB_QUEUE_EMPTY;
	}
	return ret_status;
}

msg_queue_t *
srp_rcs_get_shared_mem_get_queue_block(e_queue_type_t queue_idx)
{
	msg_queue_t *p_msg_queue_addr =
	    (msg_queue_t *) &(p_system_data->rcs_msg_queue[queue_idx]);
	return p_msg_queue_addr;
}

// Mailbox Interrupts
#define TX_MAILBOX_INTERRUPT RCS_GPREG_EXT_TO_RCS_MB0_MBDATA3_ADR
#define RX_MAILBOX_INTERRUPT RCS_GPREG_EXT_TO_RCS_MB2_MBDATA3_ADR
#define ADM_MAILBOX_INTERRUPT RCS_GPREG_EXT_TO_RCS_MB4_MBDATA3_ADR

// wrapper function for setting EXT to RCS mailbox interrupts:
static void
srp_rcs_set_mailbox_interrupt(void *srp, srp_uint32_t adr)
{
	srp_int32_t data32 = 1;
	const int mb_address = adr;
	dev_mem_write(srp, (void *) (long long) mb_address, &data32, sizeof(data32));
}

void
srp_rcs_set_tx_mailbox_interrupt(void *srp)
{
	srp_rcs_set_mailbox_interrupt(srp, TX_MAILBOX_INTERRUPT);
}

void
srp_rcs_set_rx_mailbox_interrupt(void *srp)
{
	srp_rcs_set_mailbox_interrupt(srp, RX_MAILBOX_INTERRUPT);
}

void
srp_rcs_set_admin_mailbox_interrupt(void *srp)
{
	srp_rcs_set_mailbox_interrupt(srp, ADM_MAILBOX_INTERRUPT);
}
