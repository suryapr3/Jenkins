/* INTEL CONFIDENTIAL
 *
 * Copyright 2023 Intel Corporation All Rights Reserved.
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

#ifndef CPU_ANA
#error "Not ANA CPU"
#endif

#ifndef ADC_ADDR_OFFSET_H
#define ADC_ADDR_OFFSET_H

#define WRP_ADC_DIGRF_BASE   0x04000000
#define WRP_ADC_DIGRF_OFFSET 0x00030000

#define WRP_ADC_ANT0_OFFSET 0x00800000
#define WRP_ADC_ANT1_OFFSET 0x00A00000
#define WRP_ADC_ANT2_OFFSET 0x00C00000
#define WRP_ADC_ANT3_OFFSET 0x00E00000

#endif // ADC_ADDR_OFFSET_H
