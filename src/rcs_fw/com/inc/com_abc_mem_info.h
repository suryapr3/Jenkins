/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
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
#ifndef COMMON_ABC_MEM_INFO_H
#define COMMON_ABC_MEM_INFO_H

#include "com_definitions.h"

#include "adc_cpu.h"
#include "sram.h"
#include "sram_cap.h"

#define SIZE_1MB (1048576) // 1MB
#define SIZE_1KB (1024)    // 1KB

// Feedback memory information
#define MAX_MEMFB_FB_MEM_SZ (1 * SIZE_1MB) // 1MB

#define COM_MEMFB_MEM_FB0_BASE (SRAM_FB0_FB_BASE)
#define COM_MEMFB_MEM_FB1_BASE (SRAM_FB1_FB_BASE)

// Capture memory information
#define MAX_MEMFB_CAP_MEM_SZ (2 * SIZE_1MB) // 2MB

#define COM_MEMFB_MEM_CAP0_BASE (SRAM_CAP0_FB_BASE)
#define COM_MEMFB_MEM_CAP1_BASE (SRAM_CAP1_FB_BASE)

// Capture memory information
#define MAX_MEMFB_DESC_MEM_SZ (16 * SIZE_1KB) // 16KB

// todo: update the following using generated header if available in future
#define COM_MEMFB_MEM_DESC0_BASE (0x0430C000)
#define COM_MEMFB_MEM_DESC1_BASE (0x0470C000)

// PCIE memory information
#define MAX_PCIE_PHY_MEM_SZ (16 * SIZE_1KB) // 16KB

#define COM_PCIE_PHY_MEM_CELL0_BASE (PCIE_PHY_BASE + 0x10000)
#define COM_PCIE_PHY_MEM_CELL1_BASE (PCIE_PHY_BASE + 0x20000)

// ADC CPU memory information
#define MAX_ADC_DRAM_MEM_SZ     (64 * SIZE_1KB) // 64KB
#define MAX_ADC_IRAM_MEM_SZ     (64 * SIZE_1KB) // 64KB
#define COM_ADC_CPU_DRAM_OFFSET (0x00000)
#define COM_ADC_CPU_IRAM_OFFSET (0x10000)

#define COM_ADC_CPU0_DRAM_BASE (CPU_ANT0_BASE + COM_ADC_CPU_DRAM_OFFSET)
#define COM_ADC_CPU0_IRAM_BASE (CPU_ANT0_BASE + COM_ADC_CPU_IRAM_OFFSET)
#define COM_ADC_CPU1_DRAM_BASE (CPU_ANT1_BASE + COM_ADC_CPU_DRAM_OFFSET)
#define COM_ADC_CPU1_IRAM_BASE (CPU_ANT1_BASE + COM_ADC_CPU_IRAM_OFFSET)
#define COM_ADC_CPU2_DRAM_BASE (CPU_ANT2_BASE + COM_ADC_CPU_DRAM_OFFSET)
#define COM_ADC_CPU2_IRAM_BASE (CPU_ANT2_BASE + COM_ADC_CPU_IRAM_OFFSET)
#define COM_ADC_CPU3_DRAM_BASE (CPU_ANT3_BASE + COM_ADC_CPU_DRAM_OFFSET)
#define COM_ADC_CPU3_IRAM_BASE (CPU_ANT3_BASE + COM_ADC_CPU_IRAM_OFFSET)

#endif // COMMON_ABC_MEM_INFO_H
