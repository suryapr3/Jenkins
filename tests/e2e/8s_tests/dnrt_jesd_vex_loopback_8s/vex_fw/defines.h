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
#ifndef _DEFINES_H_
#define _DEFINES_H_

#define PRODUCER_TOKEN_PER_REQUEST  ( 1 )
#define CONSUMER_SM_BUF_ID          ( 0 )
#define PRODUCER_SM_BUF_ID          ( 1 )
#define CONSUMER_TOKEN_PER_REQUEST  ( 1 )
#define VEX_COMPARE                 ( 1 )
#define DEBUG                       ( 1 )
#define INITIAL_BLOCK_SIZE          ( 3 )
#define BYTES_PER_VEC               ( 0x80 )      // Each vector is of 1024 bits
#define VEX_DEST_BUF_SIZE           ( 32  )      // In vectors
#define VEX_IN_BUF_SIZE             ( 128  )      // In vectors
#define VEX_DEST_BUF_SIZE_BYTES     ( VEX_DEST_BUF_SIZE * BYTES_PER_VEC )
#define LD_CTL1                     ( (BYTES_PER_VEC << 20) | ((VEX_DEST_BUF_SIZE_BYTES) - (BYTES_PER_VEC)) )
#define LD_CTL2                     ( VEX_DEST_BUF_SIZE_BYTES - BYTES_PER_VEC )

#endif /* _DEFINES_H_ */
