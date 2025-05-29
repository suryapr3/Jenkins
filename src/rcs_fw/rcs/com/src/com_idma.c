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
 * @file    com_idma.c
 * @brief   iDMA common functions.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#include <stdbool.h>
#include <string.h>
#include <xtensa/xtruntime.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_definitions.h"
#include "com_idma.h"
#include "com_idma_reg.h"
#include "com_isr.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static xtos_handler gp_idma_done_handler = NULL;
static xtos_handler gp_idma_err_handler = NULL;
static idma_desc2d_t g_idma_desc2d __attribute__ ((__aligned__ (8))) __attribute__ ((section (".dram0.data")));
static idma_desc1d_t g_idma_desc_memcpy __attribute__ ((__aligned__ (8))) __attribute__ ((section (".dram0.data")));

static idma_task_info_t const *g_idma_que_task = NULL;
static uint32_t g_idma_last_err = ERR_IDMD_MISSING_INTR;
static idma_settings_reg_t const g_idma_settings = {.BLOCK = e_IDMA_BLOCK16, .HALTABLE = 0, .FETCH_START = 1, .NUM_OUT = 0};

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
PRIVATE void com_idma_done_irq_handler (void *arg);
PRIVATE void com_idma_err_irq_handler (void *arg);
PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_done_intr_enable ();
PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_done_intr_disable ();
PRIVATE void com_idma_interrupts_enable ();
PRIVATE void com_idma_interrupts_disable ();
PRIVATE void com_idma_init_irq (xtos_handler const p_idma_done_handler, xtos_handler const p_idma_err_handler);

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_wait_poll ();
PRIVATE void com_idma_wait_intr ();
PRIVATE void com_idma_reset ();
PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_en (bool en);
PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_task_clear ();

PRIVATE void com_idma_verify_desc (void const *p_desc, uint32_t const desc_cnt);
PRIVATE uint32_t INTRINSIC_ALWAYS_INLINE com_idma_get_errcode ();

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
__attribute__ ((always_inline)) inline void idma_reg_write (void const *const p_addr, uint32_t const val)
{
    __asm__ volatile("wer %0, %1" ::"a"(val), "a"((uint32_t)p_addr));
}

__attribute__ ((always_inline)) inline uint32_t idma_reg_read (void const *const p_addr)
{
    uint32_t val = 0;
    __asm__ volatile("rer %0, %1" : "=a"(val) : "a"((uint32_t)p_addr));
    return val;
}

PRIVATE void com_idma_done_irq_handler (void *arg)
{
    UNUSED (arg);
    com_idma_en (false);

    g_idma_last_err = ERR_IDMA_OK;
    if ((g_idma_que_task) && (g_idma_que_task->pfunc_idma_callback))
    {
        g_idma_que_task->pfunc_idma_callback (g_idma_que_task->p_arg);
    }
}

PRIVATE void com_idma_err_irq_handler (void *arg)
{
    UNUSED (arg);
    g_idma_last_err = com_idma_get_errcode ();
    // FW_PRINT (FW_ERR, "idma err 0x%08X\n", U32 (g_idma_last_err));
    // TODO: send error message to host
    com_idma_reset ();
}

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_done_intr_enable ()
{
    if (gp_idma_done_handler)
        com_isr_interrupt_enable (e_IDMA_CH0_DONE_IRQ);
}

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_done_intr_disable ()
{
    com_isr_interrupt_disable (e_IDMA_CH0_DONE_IRQ);
}

PRIVATE void com_idma_interrupts_enable ()
{
    com_idma_done_intr_enable ();
    if (gp_idma_err_handler)
        com_isr_interrupt_enable (e_IDMA_CH0_ERR_IRQ);
}

PRIVATE void com_idma_interrupts_disable ()
{
    com_idma_done_intr_disable ();
    com_isr_interrupt_disable (e_IDMA_CH0_ERR_IRQ);
}

PRIVATE void com_idma_init_irq (xtos_handler const p_idma_done_handler, xtos_handler const p_idma_err_handler)
{
    if (p_idma_done_handler)
    {
        gp_idma_done_handler = p_idma_done_handler;
        com_isr_event (e_IDMA_CH0_DONE_IRQ, com_idma_done_irq_handler, (void *)0);
        com_isr_interrupt_enable (e_IDMA_CH0_DONE_IRQ);
    }
    if (p_idma_err_handler)
    {
        gp_idma_err_handler = p_idma_err_handler;
        com_isr_event (e_IDMA_CH0_ERR_IRQ, com_idma_err_irq_handler, (void *)0);
        com_isr_interrupt_enable (e_IDMA_CH0_ERR_IRQ);
    }
}

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_wait_poll ()
{
    volatile idma_num_desc_reg_t idma_num_desc = {.value = 0};

    do {
        idma_num_desc.value = idma_reg_read (IDMA_NUM_DESC_REG);
    } while (idma_num_desc.NUM_DESC);
}

PRIVATE void com_idma_wait_intr ()
{
    volatile idma_ctrl_reg_t idma_ctrl = {.value = 0};

    do {
        idma_ctrl.value = idma_reg_read (IDMA_CTRL_REG);
    } while (idma_ctrl.ENABLE_IDMA);
}

PRIVATE void com_idma_reset ()
{
    com_idma_interrupts_disable ();
    com_idma_task_clear ();
    idma_ctrl_reg_t idma_ctrl = {.value = 0};
    idma_ctrl.RESET_IDMA = 1;
    idma_reg_write (IDMA_CTRL_REG, idma_ctrl.value);
    idma_ctrl.RESET_IDMA = 0;
    idma_reg_write (IDMA_CTRL_REG, idma_ctrl.value);
    com_idma_interrupts_enable ();
}

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_en (bool en)
{
    uint32_t const idma_ctrl = (en) ? 1 : 0;
    idma_reg_write (IDMA_CTRL_REG, idma_ctrl);
}

PRIVATE void INTRINSIC_ALWAYS_INLINE com_idma_task_clear ()
{
    g_idma_que_task = NULL;
}

PRIVATE void com_idma_verify_desc (void const *p_desc, uint32_t const desc_cnt)
{
    RT_ASSERT_IN_RANGE (desc_cnt, 1, 255);

    uint32_t idx = 0;
    uint32_t const sz1d = sizeof (idma_desc1d_t);
    uint32_t const sz2d = sizeof (idma_desc2d_t);
    uint8_t const *p_generic = (uint8_t const *)p_desc;
    idma_desc1d_t const *p_desc1d = (idma_desc1d_t const *)p_generic;

    if (desc_cnt > 1)
    {
        do {
            p_desc1d = (idma_desc1d_t *)((uint64_t)p_generic);
            RT_ASSERT_EQUAL (p_desc1d->ctrl.INTR, 0);
            if (!(p_desc1d->ctrl.DESCRIPTOR & 0x3))
            {
                p_generic = (uint8_t const *)(p_desc1d->jump);
            }
            else
            {
                if ((p_desc1d->ctrl.DESCRIPTOR & 0x7) == 0x7) // 2D
                    p_generic += sz2d;
                else // 1d
                    p_generic += sz1d;
            }
            idx++;
        } while (idx < desc_cnt - 1);
    }
    RT_ASSERT_EQUAL (((idma_desc1d_t const *)p_generic)->ctrl.INTR, 1);
}

PRIVATE uint32_t INTRINSIC_ALWAYS_INLINE com_idma_get_errcode ()
{
    idma_stat_reg_t status = {.value = idma_reg_read (IDMA_STATUS_REG)};
    return status.ERR_CODES;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Initialize iDMA. Call only once during boot
 * @param [in]      none.
 * @return          none.
 */
void com_idma_init ()
{
    com_idma_task_clear ();
    com_idma_en (false);
    com_idma_init_irq (com_idma_done_irq_handler, com_idma_err_irq_handler);
}

/**
 * @brief           Fill control field in iDMA descriptors.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      decs_cnt: Number of descriptor
 * @param [in]      desc_type: 1D or 2D descriptor
 * @param [in]      p_ctrl: Unused
 * @return          none.
 */
void com_idma_fill_ctrl (void *p_desc, uint32_t const decs_cnt, e_idma_desc_type_t const desc_type, idma_desc_ctrl const *const p_ctrl)
{
    UNUSED (p_ctrl);
    RT_ASSERT_POINTER (p_desc);
    RT_ASSERT_EQUAL ((uint32_t) (p_desc)&3, 0);
    RT_ASSERT ((desc_type == e_IDMA_DESC_TYPE_1D) || (desc_type == e_IDMA_DESC_TYPE_2D));
    RT_ASSERT_IN_RANGE (decs_cnt, 1, 255);

    uint8_t sz = (desc_type == e_IDMA_DESC_TYPE_2D) ? sizeof (idma_desc2d_t) : sizeof (idma_desc1d_t);
    uint8_t *p_desc_generic = (uint8_t *)p_desc;
    for (uint32_t idx = 0; idx < decs_cnt; idx++)
    {
        idma_desc1d_t *p_idma_desc = (idma_desc1d_t *)p_desc_generic;
        idma_desc_ctrl_t *p_ctrl = &p_idma_desc->ctrl;
        p_ctrl->value = 0;
        p_ctrl->DESCRIPTOR = desc_type;
        p_ctrl->INTR = (idx == decs_cnt - 1) ? 1 : 0;
        p_desc_generic += sz;
    }
}

/**
 * @brief           Get iDMA status, busy, done, error.
 * @param [in]      none.
 * @return          e_idma_stat_t: iDMA status.
 */
e_idma_stat_t com_idma_get_status ()
{
    idma_stat_reg_t status = {.value = idma_reg_read (IDMA_STATUS_REG)};
    return (e_idma_stat_t)status.RUN_MODE;
}

/**
 * @brief           Get last iDMA error code. Function is read to clear.
 * @param [in]      none.
 * @return          uint32_t: iDMA error code.
 */
uint32_t com_idma_get_last_errcode ()
{
    uint32_t last_err = g_idma_last_err;
    g_idma_last_err = ERR_IDMA_OK;
    return last_err;
}

/**
 * @brief           Wait until iDma transfer completed, when not using interrupt.
 * @param [in]      none.
 * @return          uint32_t: iDMA error code or ERR_IDMA_OK when no error.
 */
uint32_t com_idma_wait_done ()
{
    com_idma_wait_intr ();
    return g_idma_last_err;
}

/**
 * @brief           Legacy DMA transfer, using 1D descriptor, support call back and non-blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_1d (void const *const dst, void const *const src, uint32_t const bytes, idma_task_info_t const *const p_task)
{
    idma_desc1d_t *p_idma_desc1d = (idma_desc1d_t *)&g_idma_desc2d;

    RT_ASSERT_POINTER (dst);
    RT_ASSERT_POINTER (src);
    RT_ASSERT_NOT_EQUAL (bytes, 0);

    memset (&g_idma_desc2d, 0, sizeof (idma_desc2d_t));
    com_idma_fill_ctrl (p_idma_desc1d, 1, e_IDMA_DESC_TYPE_1D, NULL);
    p_idma_desc1d->src = U32 (src);
    p_idma_desc1d->dst = U32 (dst);
    p_idma_desc1d->row_bytes = bytes;

    com_idma_trans_desc (p_idma_desc1d, 1, p_task);
}

/**
 * @brief           IDMA 2D transfer, support call back and non-blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer per row.
 * @param [in]      rows: Number of row to transfer.
 * @param [in]      src_pitch: Source pitch.
 * @param [in]      dst_pitch: Destination pitch.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_2d (void const *const dst, void const *const src, uint32_t const bytes, uint32_t const rows, uint32_t const src_pitch,
                        uint32_t const dst_pitch, idma_task_info_t const *const p_task)
{
    RT_ASSERT_POINTER (dst);
    RT_ASSERT_POINTER (src);
    RT_ASSERT_NOT_EQUAL (bytes, 0);

    memset (&g_idma_desc2d, 0, sizeof (idma_desc2d_t));
    com_idma_fill_ctrl (&g_idma_desc2d, 1, e_IDMA_DESC_TYPE_2D, NULL);
    g_idma_desc2d.src = U32 (src);
    g_idma_desc2d.dst = U32 (dst);
    g_idma_desc2d.row_bytes = bytes;
    g_idma_desc2d.rows = rows;
    g_idma_desc2d.src_pitch = src_pitch;
    g_idma_desc2d.dst_pitch = dst_pitch;

    com_idma_trans_desc (&g_idma_desc2d, 1, p_task);
}

/**
 * @brief           IDMA broadcast, support call back and non-blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer per row.
 * @param [in]      rows: Number of row to transfer.
 * @param [in]      dst_pitch: Destination pitch.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_broadcast (void const *const dst, void const *const src, uint32_t const bytes, uint32_t const rows, uint32_t const dst_pitch,
                         idma_task_info_t const *const p_task)
{
    com_idma_trans_2d (dst, src, bytes, rows, 0, dst_pitch, p_task);
}

/**
 * @brief           IDMA transfer using descriptor, support call back and non-blocking.
 * @param [in]      p_desc: Pointer to descriptor buffer. Last descriptor need to set ctrl.INTR=1. The rest are 0.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_desc (void const *const p_desc, uint32_t const desc_cnt, idma_task_info_t const *const p_task)
{
    idma_ctrl_reg_t idma_ctrl = {.value = 0};

    RT_ASSERT_POINTER (p_desc);
    RT_ASSERT_EQUAL ((uint32_t) (p_desc)&3, 0);
    RT_ASSERT_IN_RANGE (desc_cnt, 1, 255);
    com_idma_verify_desc (p_desc, desc_cnt);

    com_idma_wait_intr ();

    g_idma_last_err = ERR_IDMD_MISSING_INTR;
    g_idma_que_task = p_task;
    idma_reg_write (IDMA_DESC_ADDR_REG, U32 (p_desc));
    idma_reg_write (IDMA_SETTINGS_REG, g_idma_settings.value);
    com_idma_en (true);
    idma_reg_write (IDMA_NUM_DESC_INCR_REG, desc_cnt);
}

/**
 * @brief           IDMA memcpy, no call back support and is blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer.
 * @return          uint32_t: error status. 0=success, non-zero=fail.
 */
uint32_t com_idma_memcpy (void const *const dst, void const *const src, uint32_t const bytes)
{
    RT_ASSERT_POINTER (dst);
    RT_ASSERT_POINTER (src);
    RT_ASSERT_NOT_EQUAL (bytes, 0);

    g_idma_desc_memcpy.ctrl.value = 0;
    g_idma_desc_memcpy.ctrl.DESCRIPTOR = (uint8_t)e_IDMA_DESC_TYPE_1D;
    g_idma_desc_memcpy.src = U32 (src);
    g_idma_desc_memcpy.dst = U32 (dst);
    g_idma_desc_memcpy.row_bytes = bytes;

    com_idma_wait_poll ();
    idma_reg_write (IDMA_DESC_ADDR_REG, U32 (&g_idma_desc_memcpy));
    idma_reg_write (IDMA_SETTINGS_REG, g_idma_settings.value);
    com_idma_en (true);
    idma_reg_write (IDMA_NUM_DESC_INCR_REG, 1);
    com_idma_wait_poll (); // blocking

    g_idma_last_err = com_idma_get_errcode ();
    if (g_idma_last_err != ERR_IDMA_OK)
    {
        com_idma_reset ();
    }

    com_idma_en (false);
    return g_idma_last_err;
}
