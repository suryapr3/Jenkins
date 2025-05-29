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

#define VEX_DEST_BUF_SIZE 256   // In vectors
#define VEX_IN_BUF_SIZE 256 // In vectors



#define SAMPLES_PER_VEC (32)
#define BYTES_PER_VEC (128)    //0x80// Each vector is of 1024 bits
#define NUM_TOTAL_VEC_PER_STREAM 64
#define MAX_STREAM_COUNT (16)

#define JESD_MAX_SAMPLE_SIZE (4096)    // for 8gsps IQ rate and .5us window
#define JESD_MAX_SAMPLE_SIZE_VECTORS (JESD_MAX_SAMPLE_SIZE / SAMPLES_PER_VEC)
#define JESD_MAX_SAMPLE_SIZE_BYTE (JESD_MAX_SAMPLE_SIZE * 4)

#define NUM_MAX_VEC_PER_STREAM (JESD_MAX_SAMPLE_SIZE / SAMPLES_PER_VEC) // 

// vmem partition 
/**
 * VMEM partitation calculation					
	                        collectively		"per stream ( case of single stream)"		remarks
	                        Sample	    bytes	    sample	    bytes	
max sample size  	        4K	        16K	        4K	        16K	                        8 gsps IQ link rate is max for jesd
max src buffer required	    4K	        16K	        4K	        16K	                        to store expected pattern
max dest buffer required	8K	        32K	        8K	        32K	                        ping pong buffer=> doubles
					
Total Vmem buffer Availa: 	16K	        64K		

Partition Detail	purpose     	"start address (vex code)"	    "start address(host code)"	        size	
0-16K	            src buffer	        0x0000_0000	                    0x8000_0000	                    0x4000	
16K-32K	            DEBUG/MISC          0x0000_4000	                    0x8000_4000	                    0x4000	
32K-64K	            dest buffer	        0x0000_8000	                    0x8000_8000	                    0x8000	
 */


#define RX_SRC_BUFFER_OFFSET        (0x0)
#define RX_DEBUG_BUFFER_OFFSET      (0x4000)    // 16384
#define RX_DEST_BUFFER_OFFSET       (0x8000)

#define VMEM_BASE_HOST              (0x80000000)
#define RX_SRC_BUFFER_BASE_HOST     (VMEM_BASE_HOST + RX_SRC_BUFFER_OFFSET)
#define RX_DEBUG_BUFFER_BASE_HOST   (VMEM_BASE_HOST + RX_DEBUG_BUFFER_OFFSET)    // 16384
#define RX_DEST_BUFFER_BASE_HOST    (VMEM_BASE_HOST + RX_DEST_BUFFER_OFFSET)

#define VMEM_BASE_SRP               (0x28000)
#define RX_SRC_BUFFER_BASE_SRP      (VMEM_BASE_SRP + RX_SRC_BUFFER_OFFSET)
#define RX_DEBUG_BUFFER_BASE_SRP    (VMEM_BASE_SRP + RX_DEBUG_BUFFER_OFFSET)    // 16384
#define RX_DEST_BUFFER_BASE_SRP     (VMEM_BASE_SRP + RX_DEST_BUFFER_OFFSET)

#define VEX_SRC_BUF_SIZE_BYTES      (0x4000) // 16K
#define VEX_DEBUG_BUF_SIZE_BYTES    (0x4000) // 16K
#define VEX_DEST_BUF_SIZE_BYTES     (0x8000) // 32K

#define VEX_SRC_BUF_SIZE_IN_VECTORS     (VEX_SRC_BUF_SIZE_BYTES/BYTES_PER_VEC)   // 128 (0x80) for 16K SRC_BUFFER
#define VEX_DEST_BUF_SIZE_IN_VECTORS    (VEX_DEST_BUF_SIZE_BYTES/BYTES_PER_VEC)   // 256 (0x80) for 32K SRC_BUFFER


#define DEBUG_BLOCK_DUMP_SIZE_IN_VECTORS    (32)   
#define DEBUG_BLOCK_DUMP_SIZE_IN_BYTES      (DEBUG_BLOCK_DUMP_SIZE_IN_VECTORS* BYTES_PER_VEC)   

// #define LD_CTL1 ((BYTES_PER_VEC << 20) | ((VEX_DEST_BUF_SIZE_BYTES) - (BYTES_PER_VEC)))
// #define LD_CTL2 (VEX_DEST_BUF_SIZE_BYTES) - BYTES_PER_VEC
// #define LD_OFFSET_MAX   1023
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
