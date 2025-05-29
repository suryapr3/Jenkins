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
#ifndef ANA_ISR_H
#define ANA_ISR_H

#include <stdint.h>
#include <xtensa/core-macros.h>
#include <xtensa/xtruntime.h>
#include "int_cfg.h"

/* ---------------------------------------------------------------------------------------------------------------------
 * 0-12 corresonds to CPU B-interrpts
 * -------------------------------------------------------------------------------------------------------------------*/

typedef enum
{
    e_RCS2CPU_MAILBOX_IRQ = 1,
    e_RCS_START_CAL_IRQ,
    e_ATSA_START_CAL_IRQ,
    e_ADC_CAL_TIME_INTR0_IRQ,
    e_ADC_CAL_TIME_INTR1_IRQ,
    e_ADC_CAL_TIME_INTR2_IRQ,
    e_ADC_CAL_TIME_INTR3_IRQ,
    e_HW_SEQ_DONE_IRQ,
    e_CMFF_FIFO_ERR_IRQ,
    e_UNUSED_9_IRQ,
    e_UNUSED_10_IRQ,
    e_UNUSED_11_IRQ,
    e_UNUSED_12_IRQ,
    e_HW_INTERRUPTS,
    e_CPU_TIMER0_IRQ,
    e_CPU_TIMER1_IRQ,
    e_CPU_TIMER2_IRQ,
    e_SW_IRQ,
    e_WRITE_ERR_IRQ,
    e_PROFILING_IRQ,
} e_adc_irq_t;

typedef enum
{
    e_ANA_SAR_CAL,
    e_ANA_XTALK_CAL,
} e_ana_cal_type_t;

typedef enum
{
    e_ANT0,
    e_ANT1,
    e_ANT2,
    e_ANT3,
    e_FB_ANT,
} e_ana_cal_data_path_t;

typedef void (*f_isr_handler_t) (void *arg);

typedef struct
{
    uint8_t cpu_irq;
    f_isr_handler_t irq_handler;
    void *data;
} adc_cpu_irq_handler_map_t;

typedef struct
{
    uint32_t cal_reg;
    e_ana_cal_type_t type;
    uint32_t data_size;
    e_ana_cal_data_path_t data_path;
    uint8_t intrp_prio;
} adc_cal_cfg_t;

// Place holder for status readback. This info will be available in the table
typedef struct
{

} status_readback_t;

void ana_isr_initialize (uint32_t const ana_cpu_id);
void ana_isr_event (uint32_t irq, f_isr_handler_t irq_handler, void *data);
void ana_isr_interrupt_enable (uint32_t irq);
void ana_start_cal_handler (void *unused);
void ana_rcs2cpu_mb_handler (void *unused);
void ana_atsa_start_cal_handler (void *unused);
void ana_hw_seq_done_handler (void *unused);
void ana_cmff_fifo_err_handler (void *unused);

#endif
