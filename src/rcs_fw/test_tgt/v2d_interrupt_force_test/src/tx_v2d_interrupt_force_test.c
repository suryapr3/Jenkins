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
 * @file    ax_v2d_interrupt_force_test.c
 * @brief   Register IRQ's and clear the interrupts in the ISR.
 * @details Detailed description if necessary.
 *
 */

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "v2d_common_utils.h"
#include "v2d_host_rcs_common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile uint32_t rsm_buf[TEST_BUFF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t dram_buff[TEST_BUFF_SIZE]  __attribute__((section(".dram0.data")));
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));

int v2d_high_irq = 0, v2d_low_irq = 0;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
void v2d_high_irq_handler(void *arg);
void v2d_low_irq_handler(void *arg);
void process_interrupt(int bfn_int_value);
void process_nsip0_int();
void process_nsip1_int();
void process_v2d_int();

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */
int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    int v2d_num = 0, apb_num = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];

    v2d_high_irq = e_V2D_HIGH_INTERRUPT + v2d_num;

    // register irq handler for high interrupt
    com_isr_event(v2d_high_irq, v2d_high_irq_handler, (void *)0);
    // enable interrupt
    com_isr_interrupt_enable(v2d_high_irq);

    v2d_low_irq = e_V2D_LOW_INTERRUPT + v2d_num;

    // register irq handler for low interrupt
    com_isr_event(v2d_low_irq, v2d_low_irq_handler, (void *)0);
    // enable interrupt
    com_isr_interrupt_enable(v2d_low_irq);

    // Indicate HOST RCS has completed ISR registration
    rsm_ax_shared_flag = RCS_READY;

    while (HOST_TEST_COMPLETE != rsm_ax_shared_flag)
    {
        //wait in this while loop
    }

    // Diabling the ISR's
    com_isr_interrupt_disable(v2d_high_irq);
    com_isr_interrupt_disable(v2d_low_irq);

    // Indicate HOST that RCS completed it's execution
    rsm_ax_shared_flag = RCS_COMPLETE;

    return (0);
}

/**
 * @brief           high irq handler function
 * @param [in]      *argv
 * @return          NONE
 */
void v2d_high_irq_handler(void *arg)
{
    UNUSED (arg);
    com_isr_interrupt_disable(v2d_high_irq);

    int v2d_num = 0, apb_num = 0, bfn_high_int_value = 0;
    uint32_t v2d_bfn_base = 0, v2d_nsip_base = 0, v2d_csr_base = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];
    v2d_bfn_base = V2D_BFN_BASE(v2d_num);
    bfn_high_int_value = ((bfn_csr_t*) v2d_bfn_base) -> SUBB_HI_INTR.value;

    process_interrupt(bfn_high_int_value);
    com_isr_interrupt_enable(v2d_high_irq);

    rsm_ax_shared_flag = RCS_INTERRUPT_DONE;
}

/**
 * @brief           low irq handler function
 * @param [in]      *argv
 * @return          NONE
 */
void v2d_low_irq_handler(void *arg)
{

    UNUSED (arg);
    com_isr_interrupt_disable(v2d_low_irq);

    int v2d_num = 0, apb_num = 0, bfn_low_int_value = 0;
    uint32_t v2d_bfn_base = 0, v2d_nsip_base = 0, v2d_csr_base = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];
    v2d_bfn_base = V2D_BFN_BASE(v2d_num);
    bfn_low_int_value = ((bfn_csr_t*) v2d_bfn_base) -> SUBB_LO_INTR.value;

    process_interrupt(bfn_low_int_value);
    com_isr_interrupt_enable(v2d_low_irq);

    rsm_ax_shared_flag = RCS_INTERRUPT_DONE;
}

/**
 * @brief           process interrupt
 * @param [in]      interrupt_value
 * @return          NONE
 */
void process_interrupt(int bfn_int_value)
{
    switch(bfn_int_value)
    {
        case 1:
        case 16:
            {
                process_nsip0_int();
                break;
            }
        case 2:
        case 32:
            {
                process_nsip1_int();
                break;
            }
        case 4:
        case 64:
            {
                process_v2d_int();
                break;
            }
        case 8:
        case 128:
            {
                process_v2d_int();
                break;
            }
    }

}

/**
 * @brief           process nsip0 interrupt
 * @param [in]      NONE
 * @return          NONE
 */
void process_nsip0_int()
{
    int v2d_num = 0, apb_num = 0;
    uint32_t nsip_base = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];

    nsip_base = V2D_CH0_NSIP0_BASE(v2d_num) + APB_OFFSET(apb_num);
    dram_buff[0] = ((nsip_hbi_t*) nsip_base) -> INTR_INT_STAT.value;
    ((nsip_hbi_t*) nsip_base) -> INTR_INT_CLR.value = dram_buff[0];
}

/**
 * @brief           process nsip1 interrupt
 * @param [in]      NONE
 * @return          NONE
 */
void process_nsip1_int()
{
    int v2d_num = 0, apb_num = 0;
    uint32_t nsip_base = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];

    nsip_base = V2D_CH0_NSIP1_BASE(v2d_num) + APB_OFFSET(apb_num);
    dram_buff[0] = ((nsip_hbi_t*) nsip_base) -> INTR_INT_STAT.value;
    ((nsip_hbi_t*) nsip_base) -> INTR_INT_CLR.value = dram_buff[0];
}

/**
 * @brief           process v2d interrupt
 * @param [in]      NONE
 * @return          NONE
 */
void process_v2d_int()
{
    int v2d_num = 0, apb_num = 0;
    uint32_t v2d_base = 0;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];

    v2d_base = V2D_CH0_CSR_BASE(v2d_num) + APB_OFFSET(apb_num);
    dram_buff[0] = ((av2d_csr_t*) v2d_base) -> INT_CSR_INT_STAT.value;
    ((av2d_csr_t*) v2d_base) -> INT_CSR_INT_CLR.value = dram_buff[0];
}

// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
