/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2024 Intel Corporation All Rights Reserved.
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

#include "com_queue_def.h"
#include "srp.h"

/*
 * This function implements device memory read on behalf of ipcommon/fw utilities.
 * It is not to be called from the RTE, it is intended only for ipcommon->RTE callback.
 */
int
dev_mem_read(void *srp, void *data, void *dev_mem_addr, uint32_t data_len_bytes)
{
	srp_int32_t io_flags = 0;
	srp_int32_t rv;
	srp_int32_t device_address = (long) dev_mem_addr;

	if (data_len_bytes < 4)
		return (0);

	rv = srp_dev_buf_read32(srp,
				device_address,
				(srp_uint32_t *) data,
				LEN_IN_WORD(data_len_bytes),
				io_flags);
	if (rv < 0) {
		printf("reading failed");
	}
	return rv;
}

/*
 * This function implements device memory write on behalf of ipcommon/fw utilities.
 * It is not to be called from the RTE, it is intended only for ipcommon->RTE callback.
 */
int
dev_mem_write(void *srp, void *dev_mem_addr, void *data, uint32_t data_len_bytes)
{
	srp_int32_t io_flags = 0;
	srp_int32_t rv;
	srp_int32_t device_address = (long) dev_mem_addr;

	if (data_len_bytes < 4)
		return (0);

	rv = srp_dev_buf_write32(srp,
				 device_address,
				 (srp_uint32_t *) data,
				 LEN_IN_WORD(data_len_bytes),
				 io_flags);

	if (rv < 0) {
		printf("writing failed");
	}
	return rv;
}
