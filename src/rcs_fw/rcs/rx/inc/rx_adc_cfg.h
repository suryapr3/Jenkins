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

#ifndef RX_ADC_CFG_H_
#define RX_ADC_CFG_H_

#include "cpu.h"
/*
typedef enum
{
    e_ANA_CPU0,
    e_ANA_CPU1,
    e_ANA_CPU2,
    e_ANA_CPU3,
    e_ANA_CPU_FULL,
} e_rx_adc_cal_cfg_t;

typedef enum
{
    e_SAR_CAL,
    e_XTALK_CAL,
} e_adc_cal_type_t;

typedef struct
{
    uint32_t bfn_time;
    uint32_t period_us;
    uint32_t limit;
    uint32_t proc_id;
} ka_adc_context_t;

typedef struct
{
    uint32_t proc_id;
    uint32_t intrpt_num;
} cal_report_t;
*/
extern cpu_t *const p_adc_cpu[];

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Initialize the interrupts and associate handlers
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void rx_adc_cal_isr_initialize ();

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Boot a specific ana core based.
 * @param [in]      uint32_t: which ana core to boot.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void INTRINSIC_ALWAYS_INLINE boot_ana (uint32_t const quad_idx);

// bool rx_chk_ana_cpu_ready (uint32_t proc_id);
#endif
