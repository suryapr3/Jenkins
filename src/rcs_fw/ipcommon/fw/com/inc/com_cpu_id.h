/* INTEL CONFIDENTIAL
 *
 * Copyright  2024 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/

#ifndef _COMMON_CPU_ID_H_
#define _COMMON_CPU_ID_H_

typedef enum
{
    e_RCS_CPU0,
    e_CPUID_AX = e_RCS_CPU0,
    e_RCS_CPU1,
    e_CPUID_RX = e_RCS_CPU1,
    e_RCS_CPU2,
    e_CPUID_TX = e_RCS_CPU2,
    e_RCS_CPU3,
    e_CPUID_CAL = e_RCS_CPU3,
    e_CPUID_NUM_CPUID
} e_cpu_id_t;

#define RCS_CPU0_IRAM_AXI_ADDRESS 0x000C0000
#define RCS_CPU0_DRAM_AXI_ADDRESS 0x000E0000
#define RCS_CPU1_IRAM_AXI_ADDRESS 0x00100000
#define RCS_CPU1_DRAM_AXI_ADDRESS 0x00120000
#define RCS_CPU2_IRAM_AXI_ADDRESS 0x00140000
#define RCS_CPU2_DRAM_AXI_ADDRESS 0x00160000
#define RCS_CPU3_IRAM_AXI_ADDRESS 0x00180000
#define RCS_CPU3_DRAM_AXI_ADDRESS 0x001C0000

#endif // _COMMON_CPU_ID_H_
