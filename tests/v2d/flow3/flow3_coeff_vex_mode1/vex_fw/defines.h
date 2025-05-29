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

#define PRODUCER_TOKEN_PER_REQUEST 1
#define CONSUMER_SM_BUF_ID 0
#define PRODUCER_SM_BUF_ID 1
#define CONSUMER_TOKEN_PER_REQUEST 1
#define VEX_COMPARE 1
#define DEBUG 0
#define VEX_HOST_DEBUG 0
#define BYTES_PER_VEC 0x80    // Each vector is of 1024 bits
#define VEX_DEST_BUF_SIZE 256   // In vectors
#define VEX_IN_BUF_SIZE 256// In vectors
#define VMEM_IN_VEC 512
#define VEX_DEST_BUF_SIZE_BYTES (VEX_DEST_BUF_SIZE * BYTES_PER_VEC)
#define LD_CTL1 ((BYTES_PER_VEC << 20) | ((VEX_DEST_BUF_SIZE_BYTES) - (BYTES_PER_VEC)))
#define LD_CTL2 (VEX_DEST_BUF_SIZE_BYTES) - BYTES_PER_VEC
#define LD_OFFSET_MAX   1023

#define G_BUF_VECTORS   (120)
#define RX_DEST_BUFFER_BASE 0x8000
#define RX_SRC_BUFFER_BASE  0x0
#define TX_G_BUFFER_BASE    0x8000
#define TX_PASSTHRU_BUFFER_BASE 0xBC00  // 256 + 120 vectors of INPUT buffer and G BUFFER
// Timer related Macros

#define TIMER_DEBUG_LOCATION 0x0

/* config */
#define TMD_NORMAL_COUNT          0
#define TMD_ONE_SHOT_WATCHDOG     2
#define TMD_CONTINUOUS_WATCHDOG   3

/* commands */
#define TMD_COMMAND_NOP           0
#define TMD_COMMAND_START         1
#define TMD_COMMAND_STOP          2
#define TMD_COMMAND_CONTINUE      3

/* register offsets */
#define TIMER_TMDCFGR0      3
#define TIMER_TMDINITR0     4
#define TIMER_TMDWDNOTR0    6
#define TIMER_TMDWDADDRR0   7
#define TIMER_TMDWDDATAR0   8
#define TIMER_TMDCMDR0  9

#endif /* _DEFINES_H_ */
