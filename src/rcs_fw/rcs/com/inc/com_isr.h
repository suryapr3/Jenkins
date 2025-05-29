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
#ifndef COMMON_ISR_H
#define COMMON_ISR_H

#include <stdint.h>
#include <xtensa/core-macros.h>
#include <xtensa/xtruntime.h>
#include "int_cfg.h"
#include "rcs_gpreg.h"

// enums for all HW and SW interrupts
// Bits 11-15: Bit places in Edge triggered interrupts
//
// enums 0 through 564 are for HW interrupts, 566 through 573 are for SW interrupts.
// enums 574 through 576 are HW interrupts connected directly to CPU, bypassing the aggregator.
// Bits 1-5: reserved for irq bit places in the register
// Bits 6-10: reserved for identifying the aggregator register and also re-used to identify bits in edge registers
// Bits 11-13: Reserved for identifying the edge registers
typedef enum
{
    // register 0, 0
    // This enum definition need to be modified for 18A to match the hwc_rcs_interrupt_external.xlsx
    e_REG0_IRQ0 = 0,
    // register 1, 32
    e_REG1_IRQ0 = 32,
    // register 2, 64
    e_DRF0_HI_TX_INT_TRX_ANT_0_IRQ = 64,
    e_DRF0_HI_TX_INT_TRX_ANT_1_IRQ,
    e_DRF0_HI_TX_INT_TRX_ANT_2_IRQ,
    e_DRF0_HI_TX_INT_TRX_ANT_3_IRQ,
    e_DRF0_HI_TX_INT_TRX_SYS_0_IRQ,
    e_DRF0_HI_TX_INT_TRX_SYS_1_IRQ,
    e_DRF0_HI_TX_INT_TRX_SYS_2_IRQ,
    e_DRF0_HI_TX_INT_TRX_SYS_3_IRQ,
    e_DRF0_HI_TX_INT_ANT_0_RX_IRQ,
    e_DRF0_HI_TX_INT_ANT_1_RX_IRQ,
    e_DRF1_HI_TX_INT_TRX_ANT_0_IRQ = 80,
    e_DRF1_HI_TX_INT_TRX_ANT_1_IRQ,
    e_DRF1_HI_TX_INT_TRX_ANT_2_IRQ,
    e_DRF1_HI_TX_INT_TRX_ANT_3_IRQ,
    e_DRF1_HI_TX_INT_TRX_SYS_0_IRQ,
    e_DRF1_HI_TX_INT_TRX_SYS_1_IRQ,
    e_DRF1_HI_TX_INT_TRX_SYS_2_IRQ,
    e_DRF1_HI_TX_INT_TRX_SYS_3_IRQ,
    e_DRF1_HI_TX_INT_ANT_0_RX_IRQ,
    e_DRF1_HI_TX_INT_ANT_1_RX_IRQ,
    // register 3, 96
    //    REG3_IRQ0 = 96,
    e_DRF0_HI_RX_INT_TRX_ANT_0_IRQ = 96,
    e_DRF0_HI_RX_INT_TRX_ANT_1_IRQ,
    e_DRF0_HI_RX_INT_TRX_ANT_2_IRQ,
    e_DRF0_HI_RX_INT_TRX_ANT_3_IRQ,
    e_DRF0_HI_RX_INT_TRX_SYS_0_IRQ,
    e_DRF0_HI_RX_INT_TRX_SYS_1_IRQ,
    e_DRF0_HI_RX_INT_TRX_SYS_2_IRQ,
    e_DRF0_HI_RX_INT_TRX_SYS_3_IRQ,
    e_DRF0_HI_RX_INT_ANT_0_RX_IRQ,
    e_DRF0_HI_RX_INT_ANT_1_RX_IRQ,
    e_DRF1_HI_RX_INT_TRX_ANT_0_IRQ = 112,
    e_DRF1_HI_RX_INT_TRX_ANT_1_IRQ,
    e_DRF1_HI_RX_INT_TRX_ANT_2_IRQ,
    e_DRF1_HI_RX_INT_TRX_ANT_3_IRQ,
    e_DRF1_HI_RX_INT_TRX_SYS_0_IRQ,
    e_DRF1_HI_RX_INT_TRX_SYS_1_IRQ,
    e_DRF1_HI_RX_INT_TRX_SYS_2_IRQ,
    e_DRF1_HI_RX_INT_TRX_SYS_3_IRQ,
    e_DRF1_HI_RX_INT_ANT_0_RX_IRQ,
    e_DRF1_HI_RX_INT_ANT_1_RX_IRQ,
    // register 4, 128
    e_REG4_IRQ0 = 128,
    e_REG4_END_IRQ0 = 159,
    // register 5, 160
    e_DRF0_HI_MISC_INT_MEM_FB_IRQ,
    e_DRF0_HI_MISC_INT_MEM_CAL_IRQ,
    e_DRF0_HI_MISC_INT_MEM_TEST_IRQ,
    e_DRF0_HI_MISC_INT_FB_ANT_IRQ,
    e_DRF0_HI_MISC_INT_FB_SYS_IRQ,
    e_DRF0_LO_MISC_INT_MEM_FB_IRQ,
    e_DRF0_LO_MISC_INT_MEM_CAL_IRQ,
    e_DRF0_LO_MISC_INT_MEM_TEST_IRQ,
    e_DRF0_LO_MISC_INT_FB_ANT_IRQ,
    e_DRF0_LO_MISC_INT_FB_SYS_IRQ,       // bit 9
    e_DRF1_HI_MISC_INT_MEM_FB_IRQ = 176, // bit 16
    e_DRF1_HI_MISC_INT_MEM_CAL_IRQ,
    e_DRF1_HI_MISC_INT_MEM_TEST_IRQ,
    e_DRF1_HI_MISC_INT_FB_ANT_IRQ,
    e_DRF1_HI_MISC_INT_FB_SYS_IRQ,
    e_DRF1_LO_MISC_INT_MEM_FB_IRQ,
    e_DRF1_LO_MISC_INT_MEM_CAL_IRQ,
    e_DRF1_LO_MISC_INT_MEM_TEST_IRQ,
    e_DRF1_LO_MISC_INT_FB_ANT_IRQ,
    e_DRF1_LO_MISC_INT_FB_SYS_IRQ,
    // register 6, 192
    e_DRF0_LO_RX_INT_TRX_ANT_0_IRQ = 192,
    e_DRF0_LO_RX_INT_TRX_ANT_1_IRQ,
    e_DRF0_LO_RX_INT_TRX_ANT_2_IRQ,
    e_DRF0_LO_RX_INT_TRX_ANT_3_IRQ,
    e_DRF0_LO_RX_INT_TRX_SYS_0_IRQ,
    e_DRF0_LO_RX_INT_TRX_SYS_1_IRQ,
    e_DRF0_LO_RX_INT_TRX_SYS_2_IRQ,
    e_DRF0_LO_RX_INT_TRX_SYS_3_IRQ,
    e_DRF0_LO_RX_INT_ANT_0_RX_IRQ,
    e_DRF0_LO_RX_INT_ANT_1_RX_IRQ,
    e_DRF1_LO_RX_INT_TRX_ANT_0_IRQ = 208,
    e_DRF1_LO_RX_INT_TRX_ANT_1_IRQ,
    e_DRF1_LO_RX_INT_TRX_ANT_2_IRQ,
    e_DRF1_LO_RX_INT_TRX_ANT_3_IRQ,
    e_DRF1_LO_RX_INT_TRX_SYS_0_IRQ,
    e_DRF1_LO_RX_INT_TRX_SYS_1_IRQ,
    e_DRF1_LO_RX_INT_TRX_SYS_2_IRQ,
    e_DRF1_LO_RX_INT_TRX_SYS_3_IRQ,
    e_DRF1_LO_RX_INT_ANT_0_RX_IRQ,
    e_DRF1_LO_RX_INT_ANT_1_RX_IRQ,
    // register 7, 224
    e_DRF0_LO_TX_INT_TRX_ANT_0_IRQ = 224,
    e_DRF0_LO_TX_INT_TRX_ANT_1_IRQ,
    e_DRF0_LO_TX_INT_TRX_ANT_2_IRQ,
    e_DRF0_LO_TX_INT_TRX_ANT_3_IRQ,
    e_DRF0_LO_TX_INT_TRX_SYS_0_IRQ,
    e_DRF0_LO_TX_INT_TRX_SYS_1_IRQ,
    e_DRF0_LO_TX_INT_TRX_SYS_2_IRQ,
    e_DRF0_LO_TX_INT_TRX_SYS_3_IRQ,
    e_DRF0_LO_TX_INT_ANT_0_RX_IRQ,
    e_DRF0_LO_TX_INT_ANT_1_RX_IRQ,
    e_DRF1_LO_TX_INT_TRX_ANT_0_IRQ = 208,
    e_DRF1_LO_TX_INT_TRX_ANT_1_IRQ,
    e_DRF1_LO_TX_INT_TRX_ANT_2_IRQ,
    e_DRF1_LO_TX_INT_TRX_ANT_3_IRQ,
    e_DRF1_LO_TX_INT_TRX_SYS_0_IRQ,
    e_DRF1_LO_TX_INT_TRX_SYS_1_IRQ,
    e_DRF1_LO_TX_INT_TRX_SYS_2_IRQ,
    e_DRF1_LO_TX_INT_TRX_SYS_3_IRQ,
    e_DRF1_LO_TX_INT_ANT_0_RX_IRQ,
    e_DRF1_LO_TX_INT_ANT_1_RX_IRQ,
    // register 8, 256
    e_REG8_IRQ0 = 224,
    // register 9, 288
    e_REG9_IRQ0 = 224,
    // register 10
    e_RCS_BFN_TIMESTAMP_INT_IRQ = 320,
    e_RCS_BFN_GPREG_INT_IRQ,
    e_RCS_GPREG_INT0_IRQ, // GPREQ EDGE INTERRUPTS
    e_RCS_GPREG_INT1_IRQ,
    e_RCS_GPREG_INT2_IRQ,
    e_RCS_DMAC_INT_IRQ,
    e_CRUX_H2B_TX_OV_INT_IRQ,
    e_CRUX_B2H_RX_NEMPTY_INT_IRQ,
    e_CRUX_H2B_TS_OV_INT_IRQ,
    e_LOGGER_ERR_INT_IRQ,
    e_LOGGER_NE_INT_IRQ,
    e_LOGGER_FULL_INT_IRQ,
    e_I3CM_SSP_MUX_INT0_IRQ,
    e_UNDEFINED,
    e_NSIP_INTR0_IRQ,
    e_NSIP_INTR1_IRQ,
    // register 11, Timer interrupts
    e_RCS_TIMER_INT0_IRQ = 352,
    e_RCS_TIMER_INT1_IRQ,
    e_RCS_TIMER_INT2_IRQ,
    e_RCS_TIMER_INT3_IRQ,
    // register 12, GPIO interrupts
    e_RCS_GPIO_INT0_IRQ = 384,
    e_RCS_GPIO_INT1_IRQ,
    e_RCS_GPIO_INT2_IRQ,
    e_RCS_GPIO_INT3_IRQ,
    e_RCS_GPIO_INT4_IRQ,
    e_RCS_GPIO_INT5_IRQ,
    e_RCS_GPIO_INT6_IRQ,
    e_RCS_GPIO_INT7_IRQ,
    e_RCS_GPIO_INT8_IRQ,
    e_RCS_GPIO_INT9_IRQ,
    e_RCS_GPIO_INT10_IRQ,
    e_RCS_GPIO_INT11_IRQ,
    // register 13, Mailbox interrupts
    e_EXT_TO_RCS_MB_INT0_IRQ = 416, // TX0
    e_EXT_TO_RCS_MB_INT1_IRQ,       // TX1
    e_EXT_TO_RCS_MB_INT2_IRQ,       // RX0
    e_EXT_TO_RCS_MB_INT3_IRQ,       // RX1
    e_EXT_TO_RCS_MB_INT4_IRQ,       // AD
    e_EXT_TO_RCS_MB_INT5_IRQ,       // RB
    e_EXT_TO_RCS_MB_INT6_IRQ,
    e_EXT_TO_RCS_MB_INT7_IRQ,
    e_RCS_TO_RCS_MB_INT0_IRQ,
    e_RCS_TO_RCS_MB_INT1_IRQ,
    e_RCS_TO_RCS_MB_INT2_IRQ,
    e_RCS_TO_RCS_MB_INT3_IRQ,
    e_RCS_TO_RCS_MB_INT4_IRQ,
    e_RCS_TO_RCS_MB_INT5_IRQ,
    e_RCS_TO_RCS_MB_INT6_IRQ,
    e_RCS_TO_RCS_MB_INT7_IRQ,
    e_RCS_TO_RCS_MB_INT8_IRQ,
    e_RCS_TO_RCS_MB_INT9_IRQ,
    e_RCS_TO_RCS_MB_INT10_IRQ,
    e_RCS_TO_RCS_MB_INT11_IRQ,
    // register 14, PHM0 interrupts
    e_PHM0_INT_IRQ = 448,
    e_PHM0_NOT_EMPTY_INT0_IRQ,
    e_PHM0_NOT_EMPTY_INT1_IRQ,
    e_PHM0_NOT_EMPTY_INT2_IRQ,
    e_PHM0_NOT_EMPTY_INT3_IRQ,
    e_PHM0_NOT_EMPTY_INT4_IRQ,
    e_PHM0_NOT_EMPTY_INT5_IRQ,
    e_PHM0_NOT_EMPTY_INT6_IRQ,
    e_PHM0_NOT_EMPTY_INT7_IRQ,
    e_PHM0_NOT_EMPTY_INT8_IRQ,
    e_PHM0_NOT_EMPTY_INT9_IRQ,
    e_PHM0_WM_INT0_IRQ,
    e_PHM0_WM_INT1_IRQ,
    e_PHM0_WM_INT2_IRQ,
    e_PHM0_WM_INT3_IRQ,
    e_PHM0_WM_INT4_IRQ,
    e_PHM0_WM_INT5_IRQ,
    e_PHM0_WM_INT6_IRQ,
    e_PHM0_WM_INT7_IRQ,
    e_PHM0_WM_INT8_IRQ,
    e_PHM0_WM_INT9_IRQ,
    e_PHM0_FULL_INT0_IRQ,
    e_PHM0_FULL_INT1_IRQ,
    e_PHM0_FULL_INT2_IRQ,
    e_PHM0_FULL_INT3_IRQ,
    e_PHM0_FULL_INT4_IRQ,
    e_PHM0_FULL_INT5_IRQ,
    e_PHM0_FULL_INT6_IRQ,
    e_PHM0_FULL_INT7_IRQ,
    e_PHM0_FULL_INT8_IRQ,
    e_PHM0_FULL_INT9_IRQ,
    // register 15, PHM1 interrupts
    e_PHM1_INT_IRQ = 480,
    e_PHM1_NOT_EMPTY_INT0_IRQ,
    e_PHM1_NOT_EMPTY_INT1_IRQ,
    e_PHM1_NOT_EMPTY_INT2_IRQ,
    e_PHM1_NOT_EMPTY_INT3_IRQ,
    e_PHM1_NOT_EMPTY_INT4_IRQ,
    e_PHM1_NOT_EMPTY_INT5_IRQ,
    e_PHM1_NOT_EMPTY_INT6_IRQ,
    e_PHM1_NOT_EMPTY_INT7_IRQ,
    e_PHM1_NOT_EMPTY_INT8_IRQ,
    e_PHM1_NOT_EMPTY_INT9_IRQ,
    e_PHM1_WM_INT0_IRQ,
    e_PHM1_WM_INT1_IRQ,
    e_PHM1_WM_INT2_IRQ,
    e_PHM1_WM_INT3_IRQ,
    e_PHM1_WM_INT4_IRQ,
    e_PHM1_WM_INT5_IRQ,
    e_PHM1_WM_INT6_IRQ,
    e_PHM1_WM_INT7_IRQ,
    e_PHM1_WM_INT8_IRQ,
    e_PHM1_WM_INT9_IRQ,
    e_PHM1_FULL_INT0_IRQ,
    e_PHM1_FULL_INT1_IRQ,
    e_PHM1_FULL_INT2_IRQ,
    e_PHM1_FULL_INT3_IRQ,
    e_PHM1_FULL_INT4_IRQ,
    e_PHM1_FULL_INT5_IRQ,
    e_PHM1_FULL_INT6_IRQ,
    e_PHM1_FULL_INT7_IRQ,
    e_PHM1_FULL_INT8_IRQ,
    e_PHM1_FULL_INT9_IRQ,
    // register 16, Overload0/1 interrupts
    e_OVERLOAD0_INT0_IRQ = 512,
    e_OVERLOAD0_INT1_IRQ,
    e_OVERLOAD0_INT2_IRQ,
    e_OVERLOAD0_INT3_IRQ,
    e_OVERLOAD0_INT4_IRQ,
    e_OVERLOAD0_INT5_IRQ,
    e_OVERLOAD0_INT6_IRQ,
    e_OVERLOAD0_INT7_IRQ,
    e_OVERLOAD1_INT0_IRQ,
    e_OVERLOAD1_INT1_IRQ,
    e_OVERLOAD1_INT2_IRQ,
    e_OVERLOAD1_INT3_IRQ,
    e_OVERLOAD1_INT4_IRQ,
    e_OVERLOAD1_INT5_IRQ,
    e_OVERLOAD1_INT6_IRQ,
    e_OVERLOAD1_INT7_IRQ,
    e_OVERLOAD0_FBR0_IRQ,
    e_OVERLOAD0_FBR1_IRQ,
    e_OVERLOAD1_FBR0_IRQ,
    e_OVERLOAD1_FBR1_IRQ,
    // register 17, FOVR0/1 interrupts
    e_FOVR0_INT0_IRQ = 544,
    e_FOVR0_INT1_IRQ,
    e_FOVR0_INT2_IRQ,
    e_FOVR0_INT3_IRQ,
    e_FOVR0_INT4_IRQ,
    e_FOVR0_INT5_IRQ,
    e_FOVR0_INT6_IRQ,
    e_FOVR0_INT7_IRQ,
    e_FOVR1_INT0_IRQ,
    e_FOVR1_INT1_IRQ,
    e_FOVR1_INT2_IRQ,
    e_FOVR1_INT3_IRQ,
    e_FOVR1_INT4_IRQ,
    e_FOVR1_INT5_IRQ,
    e_FOVR1_INT6_IRQ,
    e_FOVR1_INT7_IRQ,
    e_FOVR0_FBR0_IRQ,
    e_FOVR0_FBR1_IRQ,
    e_FOVR1_FBR0_IRQ,
    e_FOVR1_FBR1_IRQ,
    e_AGGRGTR_INTERRUPTS,
    // SW Interrupts
    e_EVENT_CPU_TIMER0_IRQ,
    e_EVENT_CPU_TIMER1_IRQ,
    e_WRITE_ERR_IRQ,
    e_IDMA_CH0_ERR_IRQ,
    e_IDMA_CH0_DONE_IRQ,
    e_PROFILING_IRQ,
    e_SW_IRQ,
    e_NMI_IRQ,
    // HW interrupts directly connected to CPU, bypassing the aggregator.
    e_RCS_TIMER_INT0_DIRECT_IRQ,
    e_RCS_TIMER_INT1_DIRECT_IRQ,
    e_RCS_TIMER_INT2_DIRECT_IRQ,
    e_RCS_TIMER_INT3_DIRECT_IRQ,
    e_PHM0_INT_DIRECT_IRQ,
    e_PHM1_INT_DIRECT_IRQ,
    e_DIRECT_HW_AND_SW_INTERRUPTS,
    // Edge triggered interrupts
    // Edge IRQ register 0
    e_EDGE_0_REG0_IRQ = 1344,
    // Edge IRQ register 1
    e_EDGE_0_REG1_IRQ = 2368,
    // Edge IRQ register 2,
    e_EDGE_0_REG2_IRQ = 3392,
    e_BFN_TIMESYNC_STRECHED_EDGE_IRQ2 = 3411,
    e_MAX_IRQ
} e_rcs_irq_t;

typedef void (*f_isr_handler_t) (void *arg);

typedef struct
{
    uint32_t cpu_irq;
    f_isr_handler_t irq_handler;
    void *data;
    uint32_t reg_idx;
    int_cfg_gpreg_lvl_irq_mask_reg_t mask_reg;
} irq_num_handler_map_t;

typedef struct
{
    f_isr_handler_t irq_handler;
    void *data;
} irq_reg_handler_map_t;

typedef struct
{
    uint32_t cpu_irq;
} irq_map_t;

typedef struct
{
    f_isr_handler_t irq_handler;
    void *data;
} irq_edge_handler_map_t;

typedef enum
{
    e_EXT_TO_RCS0,
    e_EXT_TO_RCS1,
    e_EXT_TO_RCS2,
    e_EXT_TO_RCS3,
    e_EXT_TO_RCS4,
    e_EXT_TO_RCS5,
    e_EXT_TO_RCS6,
    e_EXT_TO_RCS7,
    e_NUM_EXT_TO_RCS = 8,
    e_RCS_TO_RCS0 = 8,
    e_RCS_TO_RCS1,
    e_RCS_TO_RCS2,
    e_RCS_TO_RCS3,
    e_RCS_TO_RCS4,
    e_RCS_TO_RCS5,
    e_RCS_TO_RCS6,
    e_RCS_TO_RCS7,
    e_RCS_TO_RCS8,
    e_RCS_TO_RCS9,
    e_RCS_TO_RCS10,
    e_RCS_TO_RCS11,
    e_NUM_COM_INT_MB_SEL = 20,
} e_com_int_mb_sel_t;

/*
 * @brief           Configure interrupt handler.
 * @param [in]      irq: Interrupt number. data: data
 * @return          none.
 */
void com_isr_event (uint32_t irq_num, xtos_handler irq_handler, void *data);

/*
 * @brief           Enable interrupt.
 * @param [in]      irq: Interrupt number. data: data
 * @return          none.
 */
void com_isr_interrupt_enable (uint32_t irq_num);

/*
 * @brief           Disable interrupt.
 * @param [in]      irq: Interrupt number. data: data
 * @return          none.
 */
void com_isr_interrupt_disable (uint32_t irq_num);

/*
 * @brief           Trigger interrupt external to ABC.
 * @param [in]      irq: Interrupt number.
 * @return          none.
 */
void com_isr_ext_int (uint32_t irq);

/*
 * @brief           Trigger interrupt with Mailbox registers.
 * @param [in]      mb_irq:  MailBox Interrupt number.
 * @return          none.
 */
void com_mb_isr_trigger (e_com_int_mb_sel_t mb_irq, uint32_t data);

/*
 * @brief           Clear interrupt with Mailbox registers.
 * @param [in]      mb_irq:  MailBox Interrupt number.
 * @return          none.
 */
void com_mb_isr_clear (e_com_int_mb_sel_t mb_irq);

/*
 * @brief           Initialize interrupt.
 * @param [in]      none.
 * @return          none.
 */
void com_isr_init ();
#endif
