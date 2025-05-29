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
 * @file    rcs_fw.c
 * @brief   This test is to validate read access to all RBM registers.
 * @details This test is trying to access all the available RBM registers
 *          of all master bridges and slave bridges.
 */

/***********************************************
 * HEADERS     *
 ***********************************************/
#include "com_event.h"
#include "com_isr.h"
#include "com_shared_memory.h"
/***********************************************
 * DEFINES (consts, vars)      *
 ***********************************************/
#define RSM_BUF_SIZE          ( 4 )
#define RCS_READY             ( 0xc001babe )
#define RCS_FINISHED          ( 0xdeaddead )
#define RCS_INIT_ERROR        ( 0x12345678 )
#define ISR_SERVICED          ( 0x0000dead )
#define ISR_ACKNOWLEDGED      ( 0x00000101 )
#define TEST_DONE             ( 0x01010101 )

#define VHA0_LOW_INT          ( 264 )
#define VHA0_HIGH_INT         (  40 )

typedef enum
{
    e_VHA_LOW_INTERRUPT = 0,
    e_VHA_HIGH_INTERRUPT
}e_vha_irq_t;

// Global variables
volatile uint32_t g_rsm_buf[RSM_BUF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t g_rsm_handshake __attribute__((section(".sram.ax.flag")));
volatile uint32_t g_rsm_flag __attribute__((section(".sram.tx.flag")));
uint32_t vha_irq;

// Function prototypes
int test_init(void);
void vha_irq_handler(void* arg);

int main()
{
    xthal_enable_interrupts();

    uint32_t wait_cnt = 0;
    if(!com_shared_mem_wait_for_ready ())
    {
        wait_cnt++;
    }

    int rv;
    do
    {
        if((rv = test_init()) != 0)                        // Enable interrupt and set up the handler
        {
            g_rsm_handshake = RCS_INIT_ERROR;
            return -1;
        }

        g_rsm_handshake = RCS_READY;

        while((g_rsm_handshake != ISR_ACKNOWLEDGED) && (g_rsm_handshake != TEST_DONE));
                                                           // Wait for the ISR to get executed

    }while(g_rsm_handshake != TEST_DONE);

    g_rsm_handshake = RCS_FINISHED;

    return 0;
}


/*
 * function   : vha_irq_handler()
 * details    : this routine is the handler that will get called when an VHA interrupt is generated
 */
void vha_irq_handler(void* arg)
{
    UNUSED(arg);

    com_isr_interrupt_disable(vha_irq);
    g_rsm_handshake = ISR_SERVICED;
    g_rsm_flag++;
}

/*
 * function   : test_init()
 * details    : this is a helper routine to enable VHA interrupt and register the handler
 */
int test_init(void)
{
    e_vha_irq_t irq_type;
    uint32_t vha_num;

    vha_num = g_rsm_buf[0];
    irq_type = (e_vha_irq_t)g_rsm_buf[1];

    if(irq_type == e_VHA_LOW_INTERRUPT)
    {
        vha_irq = (VHA0_LOW_INT + vha_num);
    } else if(irq_type == e_VHA_HIGH_INTERRUPT)
    {
        vha_irq = (VHA0_HIGH_INT + vha_num);
    }

    com_isr_event(vha_irq, vha_irq_handler, (void*)0);     // register the vha interrupt handler

    com_isr_interrupt_enable(vha_irq);                     // enable vha interrupt

    return 0;

}

// End of file

