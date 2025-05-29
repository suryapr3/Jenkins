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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#include "vex_interrupt.h"

#include "com_bfn.h"
#include "com_timing.h"
#include "com_event.h"
#include "com_isr.h"
#include "rcs_timer_gpreg.h"
#include "timerx8.h"
#include "com_shared_memory.h"
#include "rcs_timestamp.h"
#include "timer_gpio.h"
#include "nsip_hbi.h"
#include "strm2cio.h"
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


uint32_t const SIZE = 32;
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t dram_buff[128]  __attribute__((section(".dram0.data")));

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;

uint32_t vex_irq = 0;

typedef enum
{
    e_VEX_LOW_INTERRUPT,
    e_VEX_HIGH_INTERRUPT,
    e_VEX_CRUX_NOC_INTERRUPT,
    e_VEX_ORION_NOC_INTERRUPT,
}e_vex_irq_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

int main(int argc, char **argv)
{
    xthal_enable_interrupts();
    uint32_t waitCnt, loopCnt, loopPassCnt = 0;
    uint32_t vex_id;
    e_vex_irq_t irq_type;
    
    if (!com_shared_mem_wait_for_ready ())
    {
        waitCnt++;
    }
    rsm_ax_shared_flag=0xC000C0C0;
    
    write_rsm[4] = 0;
    write_rsm[0] = 0;
    
    vex_id = write_rsm[1];
    irq_type = write_rsm[2];
    
    if (irq_type == e_VEX_HIGH_INTERRUPT)
    {
        vex_irq = e_REG0_IRQ0 + vex_id;
    }
    else if (irq_type == e_VEX_LOW_INTERRUPT)
    {
        if (vex_id < 32)
        {
            vex_irq = 288 + vex_id; // e_REG9_IRQ0
        }
        else if (vex_id < 40)
        {
            vex_irq = 256 + vex_id - 32; //e_REG8_IRQ0
        }
    }
    else if (irq_type == e_VEX_CRUX_NOC_INTERRUPT)
    {
        vex_irq = e_REG4_IRQ0;
    }
    else if (irq_type == e_VEX_ORION_NOC_INTERRUPT)
    {
        vex_irq = e_REG4_IRQ0 + 1;
    }
    
    dram_buff[4] = vex_irq;
    
    //vex_interrupt_test();
    // register irq handler
    com_isr_event (vex_irq, vex_irq_handler, (void *)0);        
    // enable interrupt
    com_isr_interrupt_enable (vex_irq);
    
    // trigger host for bfn_start test results check
    rsm_ax_shared_flag = 0xC000C001;
#if 1
    // wait for interrupt ISR
    waitCnt = 0;
    do
    {
        waitCnt++;
        
    } while(write_rsm[0] != 0x9876);
    
#endif    
    write_rsm[4] = 0xABCD;
    
    return (0);
}

void vex_irq_handler (void *arg)
{
    UNUSED (arg);
    com_isr_interrupt_disable(vex_irq);
    //com_isr_interrupt_disable(e_RCS_TIMER_INT0_DIRECT_IRQ);

    // int flag
    write_rsm[0] = 0x9876;
}
