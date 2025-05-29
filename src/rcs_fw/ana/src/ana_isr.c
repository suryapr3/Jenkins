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

/**
 * @file    ana_isr.c
 * @brief   Interrupt handling routines for ADC CPU
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "ana_isr.h"
#include <xtensa/core-macros.h>
#include <xtensa/xtruntime.h>
#include "com_print.h"
#include "ant_csr.h"
#include "cpu.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define NUM_OF_ADC_CPU_INTRPT_GRP (19)
#define BUFF_FIX_LOC_1            0x49ABFFA

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
extern uint32_t csr_base;
extern uint32_t ant_cpu_base;

// clang-format off
adc_cpu_irq_handler_map_t adc_cpu_irq_handler_map[NUM_OF_ADC_CPU_INTRPT_GRP] = {
    {.cpu_irq = 6, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 7, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 8, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 9, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 10, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 11, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 12, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 13, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 14, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 15, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 16, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 17, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 18, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 0, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 1, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 2, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 3, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 4, .irq_handler = NULL, .data = (void *)0},
    {.cpu_irq = 5, .irq_handler = NULL, .data = (void *)0},
};
// clang-format on

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static status_readback_t cal_rb_buff __attribute__ ((section (".dram0.rb.data")));

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void ana_cal_int_handler (void *data);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void ana_cal_int_handler (void *data)
{
    uint32_t const ant_cpu = (uint32_t)data;
    FW_PRINT (FW_INFO, "ADC CAL %d handler", ant_cpu);
    /*
        ant_csr_scratch_reg_t ant_scratch_reg = {.value = ANT_CSR_SCRATCH_DEFAULT};
        adc_cal_cfg_t cal_cfg;

        // decode the scratch reg to get cal info
        cal_cfg.cal_reg = ANT_CSR_SCRATCH_REG (csr_base)->value;
        cal_cfg.type = cal_cfg.cal_reg & 0x7;
        cal_cfg.data_size = (cal_cfg.cal_reg >> 3) & 0xFF;
        cal_cfg.data_path = (cal_cfg.cal_reg >> 11) & 0x7; // Why 7?
        cal_cfg.intrp_prio = (cal_cfg.cal_reg >> 13) & 0x1;

        // Begin cal
        if (cal_cfg.type == e_ANA_SAR_CAL)
        {
            // function for cal 1, return the pointer to the interrupt status
            // cal_rb_buff = cal_sar();
        }
        else if (cal_cfg.type == e_ANA_XTALK_CAL)
        {
            // Function for cal 2
        }
        else
        {
            // ASSERT
        }
    */
    // overwrite the cal_rb_buff mem location with readback data and store in scratch reg.
    // ant_scratch_reg.SCRATCH = (uint32_t)&cal_rb_buff;
    //*ANT_CSR_SCRATCH_REG (csr_base) = ant_scratch_reg;

    // Update scratch reg with cal done status on bit 32.
    // ant_scratch_reg.SCRATCH = 0x80000000;
    // ANT_CSR_SCRATCH_REG (csr_base)->value = (ANT_CSR_SCRATCH_REG (csr_base)->value) | ant_scratch_reg.value;
    cpu_adc_cal_time_int0_reg_t cal_time_int0_reg = {.value = CPU_ADC_CAL_TIME_INT0_DEFAULT};
    cal_time_int0_reg.ADC_CAL_TIME_INTR0 = 0;
    *CPU_ADC_CAL_TIME_INT0_REG (ant_cpu_base) = cal_time_int0_reg;
    INTRINSIC_BARRIER;
}

/*
 * @brief           Configure interrupt handler for ADC CPU.
 * @param [in]      irq: Interrupt number.
 * @param [in]      irq_handler: handler function
 * @param [in]      data: data received with interrupt
 * @return          none.
 */
void ana_isr_event (uint32_t irq, f_isr_handler_t irq_handler, void *data)
{
    FW_PRINT (FW_INFO, "ANA_ISR_EVENT.");
    adc_cpu_irq_handler_map[irq].irq_handler = irq_handler;
    adc_cpu_irq_handler_map[irq].data = data;
    xtos_set_interrupt_handler (adc_cpu_irq_handler_map[irq].cpu_irq, (xtos_handler)adc_cpu_irq_handler_map[irq].irq_handler, (void *)data,
                                NULL);
}

/*
 * @brief           Configure interrupt handler for ADC CPU.
 * @param [in]      irq: Interrupt number.
 * @param [in]      irq_handler: handler function
 * @param [in]      data: data received with interrupt
 * @return          none.
 */
void ana_isr_initialize (uint32_t const ana_cpu_id)
{
    //    ana_isr_event (e_RCS2CPU_MAILBOX_IRQ, ana_rcs2cpu_mb_handler, 0);
    //    ana_isr_interrupt_enable (e_RCS2CPU_MAILBOX_IRQ);
    //
    //    ana_isr_event (e_RCS_START_CAL_IRQ, ana_start_cal_handler, 0);
    //    ana_isr_interrupt_enable (e_RCS_START_CAL_IRQ);
    //
    //    ana_isr_event (e_ATSA_START_CAL_IRQ, ana_atsa_start_cal_handler, 0);
    //    ana_isr_interrupt_enable (e_ATSA_START_CAL_IRQ);

    e_adc_irq_t const adc_cal_time_irq = (e_adc_irq_t)((uint32_t)e_ADC_CAL_TIME_INTR0_IRQ + ana_cpu_id);
    ana_isr_event (adc_cal_time_irq, ana_cal_int_handler, (void *)ana_cpu_id);
    ana_isr_interrupt_enable (adc_cal_time_irq);

    //    ana_isr_event (e_ADC_CAL_TIME_INTR1_IRQ, ana_cal_int_handler, 0);
    //    ana_isr_interrupt_enable (e_ADC_CAL_TIME_INTR1_IRQ);
    //
    //    ana_isr_event (e_ADC_CAL_TIME_INTR2_IRQ, ana_cal_int_handler, 0);
    //    ana_isr_interrupt_enable (e_ADC_CAL_TIME_INTR2_IRQ);
    //
    //    ana_isr_event (e_ADC_CAL_TIME_INTR3_IRQ, ana_cal_int_handler, 0);
    //    ana_isr_interrupt_enable (e_ADC_CAL_TIME_INTR3_IRQ);
    //
    //    ana_isr_event (e_HW_SEQ_DONE_IRQ, ana_hw_seq_done_handler, 0);
    //    ana_isr_interrupt_enable (e_HW_SEQ_DONE_IRQ);
    //
    //    ana_isr_event (e_CMFF_FIFO_ERR_IRQ, ana_cmff_fifo_err_handler, 0);
    //    ana_isr_interrupt_enable (e_CMFF_FIFO_ERR_IRQ);
}
/*
 * @brief           Enable interrupt.
 * @param [in]      irq: Interrupt number.
 * @return          none.l
 */
void ana_isr_interrupt_enable (uint32_t irq)
{
    xtos_interrupt_enable (adc_cpu_irq_handler_map[irq].cpu_irq);
}

/*
 * @brief           Disable interrupt.
 * @param [in]      irq: Interrupt number.
 * @return          none.
 */
void ana_isr_interrupt_disable (uint32_t irq)
{
    xtos_interrupt_disable (adc_cpu_irq_handler_map[irq].cpu_irq);
}

void ana_rcs2cpu_mb_handler (void *unused)
{
    FW_PRINT (FW_INFO, "ADC CAL interrupt\n");
}

void ana_start_cal_handler (void *unused)
{
    FW_PRINT (FW_INFO, "ADC START CAL interrupt\n");
}

void ana_atsa_start_cal_handler (void *unused)
{
    FW_PRINT (FW_INFO, "ADC ATSA CAL interrupt\n");
}

void ana_hw_seq_done_handler (void *unused)
{
    FW_PRINT (FW_INFO, "ADC HW SEQ DONE interrupt\n");
}

void ana_cmff_fifo_err_handler (void *unused)
{
    FW_PRINT (FW_INFO, "ADC CMFF FIFO ERROR interrupt\n");
}
