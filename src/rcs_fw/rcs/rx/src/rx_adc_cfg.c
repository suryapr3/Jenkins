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
 * @file    rx_adc_cfg.c
 * @brief   Common functions for ADC calibration using DIgital core.
 */
#if (CPU_RX)
#else
#error "Not RX CPU"
#endif

// #include <stdbool.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
#include "com_isr.h"
#include "com_rx_ana.h"
#include "com_print.h"
#include "com_event.h"
#include "com_timing.h"
#include "com_bfn.h"
#include "com_rx_ana.h"
#include "ant_csr.h"
#include "rx_adc_cfg.h"
#include "rx_daco.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define DIG_RF_OFFSET 0x200000

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
/*
typedef struct
{
    e_ana_cpu_t and_cpu_id;
    uint32_t intrpt_num;
} adc_cfg_t;
*/
/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static uint32_t const adc_mb_intr_cfg[] = {
    e_DRF0_HI_RX_INT_ANT_0_RX_IRQ, // e_ANA_CPU0
    e_DRF0_HI_RX_INT_ANT_1_RX_IRQ, // e_ANA_CPU1
    e_DRF1_HI_RX_INT_ANT_0_RX_IRQ, // e_ANA_CPU2
    e_DRF1_HI_RX_INT_ANT_1_RX_IRQ, // e_ANA_CPU3
};

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
cpu_t *const p_adc_cpu[] = {ANT0_CPU, ANT1_CPU, ANT2_CPU, ANT3_CPU};

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void rx_adc_cal_handler (void *data);

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void rx_adc_cal_handler (void *data)
{
    uint32_t adc_id = (uint32_t)data;
    FW_PRINT (FW_INFO, "Entered RX ANTENNAE CAL HANDLER %d", adc_id);

    // clear interrupt
    static cpu_ant_int_clr_reg_t const int_clear_reg = {.value = (CPU_ANT_INT_CLR_DEFAULT | CPU_ANT_INT_CLR_CPU2RCS_MAILBOX_BF_MSK)};
    // int_clear_reg.CPU2RCS_MAILBOX = 1;
    // CPU_ANT_INT_CLR_REG (ANT0_CPU_BASE + (adc_id * DIG_RF_OFFSET))->value =
    //     CPU_ANT_INT_CLR_REG (ANT0_CPU_BASE + (adc_id * DIG_RF_OFFSET))->value | int_clear_reg.value;
    p_adc_cpu[adc_id]->ANT_INT_CLR = int_clear_reg;

    // uint32_t const mb_val = CPU_CPU2RCS_MAILBOX_REG (ANT0_CPU_BASE + (adc_id * DIG_RF_OFFSET))->MAIL_MESSAGE;
    uint32_t const mb_val = p_adc_cpu[adc_id]->CPU2RCS_MAILBOX.value;
    if (mb_val & 0x80000000)
    {
        FW_PRINT (FW_INFO, "ANA READY %d from %d", adc_id, mb_val & 0x3); // todo: remove

        ATOMIC_BEGIN;
        rx_daco.adc_params[adc_id].adc_fsm = e_ADC_FSM_IDLE;
        ATOMIC_END;

        // send interrupt to ana
        // todo: check and pop que
        /*
                if (adc_id)
                {
                    com_timing_wait_ns (adc_id * 10 * 1000);
                }
        */
        static cpu_adc_cal_time_int0_reg_t const cal_time_int0_reg = {
            .value = (CPU_ADC_CAL_TIME_INT0_DEFAULT | CPU_ADC_CAL_TIME_INT0_ADC_CAL_TIME_INTR0_BF_MSK)};
        p_adc_cpu[adc_id]->ADC_CAL_TIME_INT0 = cal_time_int0_reg;
        // cal_time_int0_reg.ADC_CAL_TIME_INTR0 = 1;
        //*CPU_ADC_CAL_TIME_INT0_REG (ANT0_CPU_BASE) = cal_time_int0_reg;
    }
    else
    {
        FW_PRINT (FW_INFO, "get CAL status %d", (uint32_t)data);
        uint32_t rb_data;
        rb_data = (uint32_t)(ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE + (adc_id * DIG_RF_OFFSET))->value) & 0x1F;
        // todo: check for que

        // Process the readback
    }
    INTRINSIC_BARRIER;
}
/*
static void keepalive_event_adc_callback (void *data)
{
    static int loops = 0;

    ka_adc_context_t *ctx = (ka_adc_context_t *)data;

    if (ctx->limit && (loops >= ctx->limit))
    {
        FW_PRINT (FW_INFO, "ANT%d ADC calibration did not complete \n", ctx->proc_id);
    }
    else
    {
        if (cal_report[ctx->proc_id].cal_done == true)
        {
            FW_PRINT (FW_INFO, "ANT%d ADC calibration is Successful\n", ctx->proc_id);
            // Report the calibration results.
        }
        else
        {
            FW_PRINT (FW_INFO, "Wait further for interrupt\n");
            //event_schedule_adc_keepalive_event (ctx->period_us, ctx->limit, ctx->proc_id);
        }
    }
    loops++;
}
*/
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Initialize the interrupts and associate handlers
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void rx_adc_cal_isr_initialize ()
{
    /*
        com_isr_event (e_DRF0_HI_RX_INT_ANT_0_RX_IRQ, (f_isr_handler_t)rx_adc_cal_handler, (void *)e_ANA_CPU0);
        com_isr_interrupt_enable (e_DRF0_HI_RX_INT_ANT_0_RX_IRQ);

        com_isr_event (e_DRF0_HI_RX_INT_ANT_1_RX_IRQ, (f_isr_handler_t)rx_adc_cal_handler, (void *)e_ANA_CPU1);
        com_isr_interrupt_enable (e_DRF0_HI_RX_INT_ANT_1_RX_IRQ);

        com_isr_event (e_DRF1_HI_RX_INT_ANT_0_RX_IRQ, (f_isr_handler_t)rx_adc_cal_handler, (void *)e_ANA_CPU2);
        com_isr_interrupt_enable (e_DRF1_HI_RX_INT_ANT_0_RX_IRQ);

        com_isr_event (e_DRF1_HI_RX_INT_ANT_1_RX_IRQ, (f_isr_handler_t)rx_adc_cal_handler, (void *)e_ANA_CPU3);
        com_isr_interrupt_enable (e_DRF1_HI_RX_INT_ANT_1_RX_IRQ);
    */
    for (uint32_t idx = 0; idx < sizeof (adc_mb_intr_cfg) / sizeof (uint32_t); idx++)
    {
        uint32_t const intrpt_num = adc_mb_intr_cfg[idx];
        com_isr_event (intrpt_num, (f_isr_handler_t)rx_adc_cal_handler, (void *)idx);
        com_isr_interrupt_enable (intrpt_num);
    }
}
/*
bool rx_chk_ana_cpu_ready (uint32_t proc_id)
{
    uint32_t loops;
    loops = 0;
    while (cal_report[proc_id].is_ana_ready == false)
    {
        loops++;
        com_timing_wait_ns (1000);
        if (loops == 5)
        {
            FW_PRINT (FW_INFO, "RUNSTALL on ANALOG CPU = %d is not achieved", proc_id);
            return 0;
        }
    }
    FW_PRINT (FW_INFO, "RUNSTALL on ANALOG CPU=%d is achieved, loops=%d", proc_id, loops);
    return 1;
}

void event_schedule_adc_keepalive_event (int period_us, int num_cycles, uint32_t proc_id)
{
    FW_PRINT (FW_INFO, "ADC keepalive func \n");
    int ka_event_idx = com_event_new_event ();
    event_t *p_event = com_event_get_event_p (ka_event_idx);
    p_event->p_event_f = keepalive_event_adc_callback;

    uint32_t const timestamp_now = com_timing_get_current_bfn_time ();
    uint32_t const bfn_delay = US_TO_BFN_TICKS (period_us / 1000) + US_TO_BFN_TICKS (period_us % 1000);
    uint32_t const timestamp_run = com_bfn_add_time (timestamp_now, bfn_delay);
    ka_adc_context_t *ctx = (ka_adc_context_t *)p_event->context;
    ctx->bfn_time = timestamp_run;
    ctx->period_us = period_us;
    ctx->limit = num_cycles;
    ctx->proc_id = proc_id;

    com_event_schedule_event (ka_event_idx, timestamp_run);
}

void rx_adc_cpu_trigger_intrpt (e_adc_cal_type_t cal_type, e_rx_adc_cal_cfg_t proc_id, uint32_t *data, uint32_t data_size,
                                uint8_t data_path, uint8_t intrpt_prio)
{

    // scratch register bit discription
    //[2:0] -cal type
    //[10:3] - data size, nBlocks
    //[13:11]- data_path, 4 ADC datapath+ FB path
    //[14]- Interrupt priority: 0-low, 1-High
    //[31]  - Cal status, 0-begin cal. 1-cal done

    ant_csr_scratch_reg_t ant_scratch_reg = {.value = ANT_CSR_SCRATCH_DEFAULT};
    // Assign scartch reg with start cal value: bit 31 to 0
    *ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE) = ant_scratch_reg;
    *ANT_CSR_SCRATCH_REG (ANT1_CSR_BASE) = ant_scratch_reg;
    *ANT_CSR_SCRATCH_REG (ANT2_CSR_BASE) = ant_scratch_reg;
    *ANT_CSR_SCRATCH_REG (ANT3_CSR_BASE) = ant_scratch_reg;

    if (cal_type == e_SAR_CAL)
    {
        if (proc_id == e_ANA_CPU_FULL)
        {
            // Update scratch reg with interrupt priority
            ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE)->value =
                (ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE)->value) | (data_path << 11) | (intrpt_prio << 13);
            ANT_CSR_SCRATCH_REG (ANT1_CSR_BASE)->value =
                (ANT_CSR_SCRATCH_REG (ANT1_CSR_BASE)->value) | (data_path << 11) | (intrpt_prio << 13);
            ANT_CSR_SCRATCH_REG (ANT2_CSR_BASE)->value =
                (ANT_CSR_SCRATCH_REG (ANT2_CSR_BASE)->value) | (data_path << 11) | (intrpt_prio << 13);
            ANT_CSR_SCRATCH_REG (ANT3_CSR_BASE)->value =
                (ANT_CSR_SCRATCH_REG (ANT3_CSR_BASE)->value) | (data_path << 11) | (intrpt_prio << 13);

            // Trigger interrupt
            cpu_adc_cal_time_int0_reg_t cal_time_int0_reg = {.value = CPU_ADC_CAL_TIME_INT0_DEFAULT};
            cal_time_int0_reg.ADC_CAL_TIME_INTR0 = 1;
            *CPU_ADC_CAL_TIME_INT0_REG (ANT0_CPU_BASE) = cal_time_int0_reg;
            *CPU_ADC_CAL_TIME_INT0_REG (ANT1_CPU_BASE) = cal_time_int0_reg;
            *CPU_ADC_CAL_TIME_INT0_REG (ANT2_CPU_BASE) = cal_time_int0_reg;
            *CPU_ADC_CAL_TIME_INT0_REG (ANT3_CPU_BASE) = cal_time_int0_reg;
        }
        else // If one DSP is chosen for cal
        {
            FW_PRINT (FW_INFO, "Single ADC CPU selected CPU=%d", proc_id);
            // Update scratch reg with interrupt priority
            ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE + proc_id * DIG_RF_OFFSET)->value =
                (ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE + proc_id * DIG_RF_OFFSET)->value) | (data_path << 11) | (intrpt_prio << 13);

            // Trigger Interrupt
            cpu_adc_cal_time_int0_reg_t cal_time_int0_reg = {.value = CPU_ADC_CAL_TIME_INT0_DEFAULT};
            cal_time_int0_reg.ADC_CAL_TIME_INTR0 = 1;
            *CPU_ADC_CAL_TIME_INT0_REG (ANT0_CPU_BASE + proc_id * DIG_RF_OFFSET) = cal_time_int0_reg;
        }
    }
    else if (cal_type == e_XTALK_CAL)
    {
        uint32_t *p_buffer;
        uint32_t *p_data;
        uint32_t *p_temp;
        if (proc_id == e_ANA_CPU_FULL)
        {
            for (uint8_t i = 0; i < e_ANA_CPU_FULL; i++)
            {
                // store the capture data in adc dram buffer
                p_buffer = (uint32_t *)(0x49A0000 + i * DIG_RF_OFFSET); // Store the capture data at location '0' of DIG CORE dram memory
                *(p_buffer) = *data;

                // update the scratch reg
                ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE + i * DIG_RF_OFFSET)->value =
                    (ANT_CSR_SCRATCH_REG (ANT0_CSR_BASE + i * DIG_RF_OFFSET)->value) | (cal_type) | (data_size << 0x3) | (data_path << 11)
                    | (intrpt_prio << 13);
                cpu_adc_cal_time_int0_reg_t cal_time_int0_reg = {.value = CPU_ADC_CAL_TIME_INT0_DEFAULT};
                cal_time_int0_reg.ADC_CAL_TIME_INTR0 = 1;
                *CPU_ADC_CAL_TIME_INT0_REG (ANT0_CPU_BASE + i * DIG_RF_OFFSET) = cal_time_int0_reg;
            }
        }
        // else //for single cpu scenario
    }
    else
    {
        FW_PRINT (FW_INFO, "CAL not supported");
    }
}
*/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Boot a specific ana core based.
 * @param [in]      uint32_t: which ana core to boot.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void INTRINSIC_ALWAYS_INLINE boot_ana (uint32_t const quad_idx)
{
    static cpu_adc_cpu_ctrl_reg_t const adc_start_reg = {.RUN_STALL = 0, .STATVECTORSEL = CPU_ADC_CPU_CTRL_STATVECTORSEL_BF_DEF};
    rx_daco.adc_params[quad_idx].adc_fsm = e_ADC_FSM_BOOTING;
    p_adc_cpu[quad_idx]->ADC_CPU_CTRL = adc_start_reg;
}