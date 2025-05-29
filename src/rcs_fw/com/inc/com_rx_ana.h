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
#ifndef COM_RX_ANA_H
#define COM_RX_ANA_H

typedef enum
{
    e_ANA_CPU0 = 0,
    e_ANA_CPU1,
    e_ANA_CPU2,
    e_ANA_CPU3,
    e_ANA_MAX
} e_ana_cpu_t;

typedef enum
{
    e_ADC_CAL_TYPE_SLICE_ANT = 0,
    e_ADC_CAL_TYPE_SLICE_FBR,
    e_ADC_CAL_TYPE_MAX
} e_adc_cal_type_t;

typedef enum
{
    e_ADC_CAL_STAT_COMPLETE = 0,
    e_ADC_CAL_STAT_FAIL,
    // Additional cal status goes here
    e_ADC_CAL_STAT_MAX
} e_adc_cal_stat_t;

typedef union {
    struct
    {
        uint32_t CAL_TYPE : 4; // e_adc_cal_type_t
        uint32_t CAL_SUBTYPE : 4;
        uint32_t ANT_MASK : 5; // 4x ant + 1 FBR
        uint32_t CAL_STAT : 3; // e_adc_cal_stat_t
        uint32_t : 16;
    };
    uint32_t value;
} e_adc_cal_info_t;

#endif // COM_RX_ANA_H
