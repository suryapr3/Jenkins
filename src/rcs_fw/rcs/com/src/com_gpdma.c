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
 * @file    com_gpdma.c
 * @brief   gpDMA common functions.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_definitions.h"
#include "com_gpdma.h"
#include "com_isr.h"
#include "com_lock.h"
#include "com_print.h" // todo: remove this later

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define GPDMA_NO_INTR            (e_MAX_IRQ)
#define GPDMA_IDX_CH2INST(x)     (x >> 1)
#define GPMDA_PCH_INST2CH1(x)    ((com_gpdma_ch_t *)&(gpdma_cfg[x].gpdma->CH1_SAR)) // x=idx_inst_gpdma
#define GPMDA_TO_RCSINST(x)      ((rcs_dmac_t *)x)
#define GPDMA_CH_OFFSET(x)       ((x % MAX_GPDMA_CH_PER_INST) ? 1 : 0)
#define GPDMA_TRW_ENUM2BYTE(x)   (1 << U32 (x))
#define GPDMA_LLP_ALIGN_MASK     (0x0000003F) // must aligned to a 64-byte boundary
#define MAX_GPDMA_RCS_BLK_BYTE   (16384)      // in bytes, 16KB
#define MAX_GPDMA_MEMFB_BLK_BYTE (65536)      // in bytes, 64KB
#define MAX_GPDMA_BLK_TRF_SZ     (MAX_GPDMA_BLOCK_TS_VAL + 1)
#define MAX_GPDMA_CH_PER_INST    (2)

#if HAVE_MEM_FB_GPDMA
// #define MAX_GPDMA_INST 5                     // todo: restore this when enable memfb_gpdma, 1 RCS + 4 MEM_FB gpdma
#define MAX_GPDMA_INST 1                       // todo: when enable memfb gpdma, remove this
#define MAX_GPDMA_CH   U32 (e_GPDMA_MEMFB_MAX) // 2 RCS ch + 8 MEM_FB gpdma ch
#else
#define MAX_GPDMA_INST 1                     // 1 RCS
#define MAX_GPDMA_CH   U32 (e_GPDMA_RCS_MAX) // 2 RCS ch
#endif                                       // HAVE_MEM_FB_GPDMA

#define GPDMA_RCS0    (ENUM2U32 (e_GPDMA_RCS_0))
#define GPDMA_RCS1    (ENUM2U32 (e_GPDMA_RCS_1))
#define GPDMA_RCS_MAX (ENUM2U32 (e_GPDMA_RCS_MAX))
#if HAVE_MEM_FB_GPDMA
#define GPDMA_MEMFB0_0  (ENUM2U32 (e_GPDMA_MEMFB0_0))
#define GPDMA_MEMFB0_1  (ENUM2U32 (e_GPDMA_MEMFB0_1))
#define GPDMA_MEMFB0_2  (ENUM2U32 (e_GPDMA_MEMFB0_2))
#define GPDMA_MEMFB0_3  (ENUM2U32 (e_GPDMA_MEMFB0_3))
#define GPDMA_MEMFB1_0  (ENUM2U32 (e_GPDMA_MEMFB1_0))
#define GPDMA_MEMFB1_1  (ENUM2U32 (e_GPDMA_MEMFB1_1))
#define GPDMA_MEMFB1_2  (ENUM2U32 (e_GPDMA_MEMFB1_2))
#define GPDMA_MEMFB1_3  (ENUM2U32 (e_GPDMA_MEMFB1_3))
#define GPDMA_MEMFB_MAX (ENUM2U32 (e_GPDMA_MEMFB_MAX))
#endif // HAVE_MEM_FB_GPDMA

#define GPDMA_RCS_CTL_DEFAULT   U64 (RCS_DMAC_CH1_CTL_DEFAULT)    // ch1 and ch2 has the same default
#define GPDMA_MEMFB_CTL_DEFAULT U64 (MEM_FB_DMAC_CH1_CTL_DEFAULT) // ch1 and ch2 has the same default

#define GPDMA_CFGREG_CH1_DEFAULT    U64 (RCS_DMAC_CH1_CFG_DEFAULT) // rcs and fb have the same default
#define GPDMA_CFGREG_CH2_DEFAULT    U64 (RCS_DMAC_CH2_CFG_DEFAULT) // rcs and fb have the same default
#define GPDMA_CFGREG_EN_DMAC        U64 (RCS_DMAC_CFGREG_DMAC_EN_BF_MSK)
#define GPDMA_CFGREG_EN_INT         U64 (RCS_DMAC_CFGREG_INT_EN_BF_MSK)
#define GPDMA_CFGREG_EN             U64 (GPDMA_CFGREG_EN_DMAC | GPDMA_CFGREG_EN_INT)
#define GPDMA_CFPREG_DIS            U64 (0x0)
#define GPDMA_CH_START              U64 (RCS_DMAC_CHENREG_CH1_EN_WE_BF_MSK | RCS_DMAC_CHENREG_CH1_EN_BF_MSK)
#define GPDMA_CH_INTSTATUS_TFR_DONE U64 (RCS_DMAC_CH1_INTSTAT_ENREG_EN_DMA_TFR_DONE_INTSTAT_BF_MSK)
#define GPDMA_CH_INTSTATUS_ERR                                                                                                   \
    U64 (ERR_GPDMA_CH_SRC_DEC_ERR | ERR_GPDMA_CH_DST_DEC_ERR | ERR_GPDMA_CH_SRC_SLV_ERR | ERR_GPDMA_CH_DST_SLV_ERR               \
         | ERR_GPDMA_CH_LLI_RD_DEC_ERR | ERR_GPDMA_CH_LLI_WR_DEC_ERR | ERR_GPDMA_CH_LLI_RD_SLV_ERR | ERR_GPDMA_CH_LLI_WR_SLV_ERR \
         | ERR_GPDMA_CH_SHADOWREG_OR_LLI_INVALID_ERR | ERR_GPDMA_CH_SLVIF_MULTIBLKTYPE_ERR | ERR_GPDMA_CH_SLVIF_DEC_ERR          \
         | ERR_GPDMA_CH_SLVIF_WR2RO_ERR | ERR_GPDMA_CH_SLVIF_RD2RWO_ERR | ERR_GPDMA_CH_SLVIF_WRONCHEN_ERR                        \
         | ERR_GPDMA_CH_SLVIF_SHADOWREG_WRON_VALID_ERR | ERR_GPDMA_CH_SLVIF_WRONHOLD_ERR | ERR_GPDMA_CH_SLVIF_WRPARITY_ERR       \
         | ERR_GPDMA_CH_CH_LOCK_CLEARED | ERR_GPDMA_CH_CH_SRC_SUSPENDED | ERR_GPDMA_CH_CH_SUSPENDED | ERR_GPDMA_CH_CH_DISABLED   \
         | ERR_GPDMA_CH_CH_ABORTED | ERR_GPDMA_CH_ECC_PROT_CHMEM_CORRERR | ERR_GPDMA_CH_ECC_PROT_CHMEM_UNCORRERR                 \
         | ERR_GPDMA_CH_ECC_PROT_UIDMEM_CORRERR | ERR_GPDMA_CH_ECC_PROT_UIDMEM_UNCORRERR)

#define GPDMA_CH_INTSTATUS_EN  U64 (GPDMA_CH_INTSTATUS_ERR | GPDMA_CH_INTSTATUS_TFR_DONE)
#define GPDMA_CH_INTSTATUS_DIS U64 (0x0)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef enum
{
    e_GPDMA_MULTBLK_CONTIGUOUS = 0,
    e_GPDMA_MULTBLK_RELOAD = 1,
    e_GPDMA_MULTBLK_REGISTER = 2,
    e_GPDMA_MULTBLK_LINKED_LIST = 3,
    e_GPDMA_MULTBLK_MAX
} e_gpdma_multblk_type_t;

typedef struct
{
    rcs_dmac_ch1_sar_reg_t SAR;                                /*< Address offset = 0x100 */
    rcs_dmac_ch1_dar_reg_t DAR;                                /*< Address offset = 0x108 */
    rcs_dmac_ch1_blk_ts_reg_t BLOCK_TS;                        /*< Address offset = 0x110 */
    rcs_dmac_ch1_ctl_reg_t CTL;                                /*< Address offset = 0x118 */
    rcs_dmac_ch1_cfg_reg_t CFG;                                /*< Address offset = 0x120 */
    rcs_dmac_ch1_llp_reg_t LLP;                                /*< Address offset = 0x128 */
    rcs_dmac_ch1_statreg_reg_t STATUS;                         /*< Address offset = 0x130 */
    rcs_dmac_ch1_swhssrcreg_reg_t SWHSSRC;                     /*< Address offset = 0x138 */
    rcs_dmac_ch1_swhsdstreg_reg_t SWHSDST;                     /*< Address offset = 0x140 */
    rcs_dmac_ch1_blk_tfr_resumereqreg_reg_t BLK_TFR_RESUMEREQ; /*< Address offset = 0x148 */
    rcs_dmac_ch1_idreg_reg_t ID;                               /*< Address offset = 0x150 */
    rcs_dmac_ch1_qosreg_reg_t QOS;                             /*< Address offset = 0x158 */
    const uint8_t reservedArea[32];                            /*< Address offset = 0x160 */
    rcs_dmac_ch1_intstat_enreg_reg_t INTSTATUS_ENABLE;         /*< Address offset = 0x180 */
    rcs_dmac_ch1_intstat_reg_t INTSTATUS;                      /*< Address offset = 0x188 */
    rcs_dmac_ch1_intsignal_enreg_reg_t INTSIGNAL_ENABLE;       /*< Address offset = 0x190 */
    rcs_dmac_ch1_intclrreg_reg_t INTCLEAR;                     /*< Address offset = 0x198 */
    rcs_dmac_ch1_cfg_extd_reg_t CFG_EXTD;                      /*< Address offset = 0x1A0 */
    const uint8_t reservedArea2[88];                           /*< Address offset = 0x1A8 */
} com_gpdma_ch_t;

typedef struct
{
    uint32_t bytes;
    e_gpdma_tr_width_t e_tr_width;
} com_gpdma_trw_info_t;

typedef struct
{
    rcs_dmac_t *const gpdma;
    e_rcs_irq_t const irq_num;
} com_gpdma_cfg_t;

typedef struct
{
    uint32_t const idx_gpdma_ch;
    e_cpu_id_t cpu_id;
    uint64_t last_err;
    gpdma_task_info_t *p_task_gpdma;
} com_gpdma_isr_info_t;

typedef struct
{
    uint16_t sinc;
    uint16_t dinc;
} com_gpdma_ctl_inc_t;

typedef struct
{
    uint32_t tr_width;
    uint32_t block_ts;
    bool is_last;
    uint64_t src;
    uint64_t dst;
} com_gpdma_size_info_t;

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
// clang-format off
PRIVATE com_gpdma_cfg_t const gpdma_cfg[] = {
    {RCS_DMAC, e_RCS_DMAC_INT_IRQ},
#if HAVE_MEM_FB_GPDMA
	// todo: do we need intrrupt at all for mem_fb gpdma? put GPDMA_NO_INTR for now
    {GPMDA_TO_RCSINST(MEM_FB0_DMAC_0), GPDMA_NO_INTR},
    {GPMDA_TO_RCSINST(MEM_FB0_DMAC_1), GPDMA_NO_INTR},
    {GPMDA_TO_RCSINST(MEM_FB1_DMAC_0), GPDMA_NO_INTR},
    {GPMDA_TO_RCSINST(MEM_FB1_DMAC_1), GPDMA_NO_INTR},
#endif // HAVE_MEM_FB_GPDMA
};

PRIVATE com_gpdma_isr_info_t gpdma_irq_info[] = {
    {GPDMA_RCS0, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_RCS1, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
#if HAVE_MEM_FB_GPDMA
    {GPDMA_MEMFB0_0, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB0_1, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB0_2, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB0_3, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB1_0, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB1_1, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB1_2, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
    {GPDMA_MEMFB1_3, e_CPUID_NUM_CPUID, ERR_GPDMA_CH_MISSING_INTR_ERR, NULL},
#endif // HAVE_MEM_FB_GPDMA
};

PRIVATE com_gpdma_trw_info_t const com_gpdma_trw_info[] = {
#if HAVE_MEM_FB_GPDMA
    {64, e_GPDMA_TR_WIDTH_512},
	{32, e_GPDMA_TR_WIDTH_256},
#endif // HAVE_MEM_FB_GPDMA
	{16, e_GPDMA_TR_WIDTH_128},
	{8,  e_GPDMA_TR_WIDTH_64},
	{4,  e_GPDMA_TR_WIDTH_32},
	{2,  e_GPDMA_TR_WIDTH_16},
	{1,  e_GPDMA_TR_WIDTH_8},
};

PRIVATE e_lock_t const com_gpdma_e_lock[] = {
    e_LOCK_GPDMA_RCS0,
    e_LOCK_GPDMA_RCS1,
};
// clang-format on

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
PRIVATE void com_gpdma_irq_handler (void *p_arg);
PRIVATE void com_gpdma_init_irq (xtos_handler const p_gpdma_handler);
PRIVATE void com_gpdma_irq_en (uint32_t const idx_inst_gpdma);

PRIVATE void com_gpdma_llp (uint32_t const idx_ch_gpdma, uint64_t const addr_desc, gpdma_task_info_t const *const p_task);
PRIVATE void com_gpdma_reg (uint32_t const idx_ch_gpdma, com_gpdma_size_info_t const *const p_size_info);
PRIVATE void com_gpdma_verify_desc (uint32_t const idx_ch_gpdma, gpdma_desc_t const *p_desc, uint32_t const desc_cnt);
PRIVATE void com_gpdma_lock_release (uint32_t const idx_ch_gpdma);
PRIVATE void com_gpdma_set_isr_info (uint32_t const idx_ch_gpdma, gpdma_task_info_t *p_task);
PRIVATE com_gpdma_trw_info_t const *com_gpdma_get_trw_info (uint32_t const idx_ch_gpdma, uint32_t const bytes, uint64_t const dst,
                                                            uint64_t const src);
PRIVATE e_gpdma_tr_width_t com_gpdma_get_trw (uint32_t const idx_ch_gpdma, int const bytes, uint64_t const dst, uint64_t const src);
PRIVATE com_gpdma_ctl_inc_t com_gpdma_get_inc (e_gpdma_ttfc_t const ttfc);
PRIVATE uint64_t com_gpdma_desc_addr_convert (gpdma_desc_t *p_desc, uint32_t const desc_cnt);
PRIVATE uint64_t com_gpdma_get_cfg (uint32_t const idx_ch_gpdma, e_gpdma_multblk_type_t const multblk_type, e_gpdma_ttfc_t const ttfc);

PRIVATE void com_gpdma_trans (uint32_t const idx_ch_gpdma, void const *const dst, void const *const src, uint32_t const bytes,
                              gpdma_task_info_t *p_task);
PRIVATE void com_gpdma_trans_desc (uint32_t const idx_ch_gpdma, gpdma_desc_t *p_desc, uint32_t const desc_cnt, gpdma_task_info_t *p_task);
PRIVATE void com_gpdma_wait_done (uint32_t const idx_ch_gpdma);
PRIVATE void com_gpdma_wait_start (uint32_t const idx_ch_gpdma);

PRIVATE uint32_t INTRINSIC_ALWAYS_INLINE com_gpdma_get_msize (uint32_t const idx_ch_gpdma);
PRIVATE uint64_t INTRINSIC_ALWAYS_INLINE com_gpdma_addr_convert (uint64_t const addr);

#if CPU_AX
PRIVATE void com_gpdma_en_all ();
#endif // #if CPU_AX

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
PRIVATE void com_gpdma_irq_handler (void *p_arg)
{
    com_gpdma_isr_info_t *const p_gpdma_isr_main = (com_gpdma_isr_info_t *)p_arg;
    uint32_t const idx_inst_gpdma = GPDMA_IDX_CH2INST (p_gpdma_isr_main->idx_gpdma_ch);
    com_gpdma_ch_t volatile *p_gpdma_ch = (com_gpdma_ch_t volatile *)GPMDA_PCH_INST2CH1 (idx_inst_gpdma);

    // FW_PRINT (FW_INFO, "---ISR cpu %d gpdma inst idx %d", RCS_CPU, idx_inst_gpdma);
    for (uint32_t idx = 0; idx < MAX_GPDMA_CH_PER_INST; idx++)
    {
        com_gpdma_isr_info_t *const p_gpdma_isr_info = p_gpdma_isr_main + idx;
        gpdma_task_info_t *const p_gpdma_task = p_gpdma_isr_info->p_task_gpdma;
        uint32_t const idx_ch_gpdma = p_gpdma_isr_info->idx_gpdma_ch;
        volatile uint64_t status_ch_int = REG_READ64 (&p_gpdma_ch->INTSTATUS);

        if ((p_gpdma_isr_info->cpu_id == RCS_CPU) && (status_ch_int))
        {
            REG_WRITE64 (&p_gpdma_ch->INTCLEAR, status_ch_int);
            REG_WRITE64 (&p_gpdma_ch->INTSTATUS_ENABLE, GPDMA_CH_INTSTATUS_DIS);

            uint64_t const err_ch_int_status = status_ch_int & GPDMA_CH_INTSTATUS_ERR;
            p_gpdma_isr_info->cpu_id = e_CPUID_NUM_CPUID;
            p_gpdma_isr_info->last_err = err_ch_int_status;

            // condition -not- to disable interrupt is
            // 1. gpdma_irq_info[idx 0 and 1].cpu_id != current cpu
            if ((p_gpdma_isr_main->cpu_id == e_CPUID_NUM_CPUID) && ((p_gpdma_isr_main + 1)->cpu_id == e_CPUID_NUM_CPUID))
            {
                com_isr_interrupt_disable (gpdma_cfg[idx_inst_gpdma].irq_num);
            }

            com_gpdma_lock_release (idx_ch_gpdma);
            if (err_ch_int_status)
            {
                FW_PRINT (FW_INFO, "ISR2 Issue, ch =%d, upper=%x lower=%x", idx_ch_gpdma, U32 (status_ch_int >> 32),
                          U32 (status_ch_int)); // todo: remove this and send message !!!
            }
            else if ((p_gpdma_task != NULL) && (p_gpdma_task->pfunc_gpdma_callback != NULL))
            {
                p_gpdma_task->pfunc_gpdma_callback (p_gpdma_task->p_arg);
            }
            p_gpdma_isr_info->p_task_gpdma = NULL;
        }
        p_gpdma_ch++;
    }
}

PRIVATE void com_gpdma_init_irq (xtos_handler const p_gpdma_handler)
{
    for (uint32_t idx = 0; idx < MAX_GPDMA_INST; idx++)
    {
        if (gpdma_cfg[idx].irq_num != GPDMA_NO_INTR)
        {
            com_isr_event (gpdma_cfg[idx].irq_num, p_gpdma_handler, &gpdma_irq_info[idx * MAX_GPDMA_CH_PER_INST]);
            com_isr_interrupt_disable (gpdma_cfg[idx].irq_num);
        }
    }
}

PRIVATE void com_gpdma_irq_en (uint32_t const idx_inst_gpdma)
{
    if (gpdma_cfg[idx_inst_gpdma].irq_num != GPDMA_NO_INTR)
        com_isr_interrupt_enable (gpdma_cfg[idx_inst_gpdma].irq_num);
}

PRIVATE void com_gpdma_verify_desc (uint32_t const idx_ch_gpdma, gpdma_desc_t const *p_desc, uint32_t const desc_cnt)
{
    uint64_t const addr_desc = U64 (p_desc);
    uint32_t const max_msize = com_gpdma_get_msize (idx_ch_gpdma);

#if HAVE_MEM_FB_GPDMA
    uint32_t const max_tr_width = (idx_ch_gpdma < GPDMA_RCS_MAX) ? ENUM2U32 (e_GPDMA_TR_WIDTH_128) : ENUM2U32 (e_GPDMA_TR_WIDTH_512);
#else
    uint32_t const max_tr_width = ENUM2U32 (e_GPDMA_TR_WIDTH_128);
#endif // HAVE_MEM_FB_GPDMA

    RT_ASSERT (addr_desc != NULL);
    RT_ASSERT_EQUAL (U32 (addr_desc & GPDMA_LLP_ALIGN_MASK), 0);

    for (uint32_t idx = 0; idx < desc_cnt; idx++)
    {
        uint32_t const is_last = (idx == desc_cnt - 1) ? 1 : 0;
        uint32_t const trw_byte_src = GPDMA_TRW_ENUM2BYTE (p_desc->ctl.SRC_TR_WIDTH);
        uint32_t const trw_byte_dst = GPDMA_TRW_ENUM2BYTE (p_desc->ctl.DST_TR_WIDTH);
        RT_ASSERT (p_desc->src != 0);
        RT_ASSERT (p_desc->dst != 0);
        RT_ASSERT (p_desc->src != p_desc->dst);
        RT_ASSERT (p_desc->ctl.SHADOWREG_OR_LLI_LAST == is_last);
        RT_ASSERT (p_desc->ctl.SHADOWREG_OR_LLI_VALID == 1);
        RT_ASSERT (p_desc->ctl.SRC_TR_WIDTH <= max_tr_width);
        RT_ASSERT (p_desc->ctl.DST_TR_WIDTH <= max_tr_width);
        RT_ASSERT (p_desc->ctl.SRC_MSIZE <= max_msize);
        RT_ASSERT (p_desc->ctl.DST_MSIZE <= max_msize);
        RT_ASSERT (p_desc->block_ts < MAX_GPDMA_BLK_TRF_SZ);
        if (trw_byte_src != 1)
        {
            RT_ASSERT_EX ((p_desc->src % trw_byte_src) == 0, "src addr is not %d aligned", trw_byte_src);
        }
        if (trw_byte_dst != 1)
        {
            RT_ASSERT_EX ((p_desc->dst % trw_byte_dst) == 0, "dst addr is not %d aligned", trw_byte_src);
        }
        p_desc = (gpdma_desc_t const *)p_desc->llp;
    }
}

PRIVATE void com_gpdma_lock_release (uint32_t const idx_ch_gpdma)
{
    if (idx_ch_gpdma < GPDMA_RCS_MAX)
    {
        com_lock_release (com_gpdma_e_lock[idx_ch_gpdma]);
    }
}

PRIVATE void com_gpdma_set_isr_info (uint32_t const idx_ch_gpdma, gpdma_task_info_t *p_task)
{
    gpdma_irq_info[idx_ch_gpdma].p_task_gpdma = p_task;
    gpdma_irq_info[idx_ch_gpdma].cpu_id = RCS_CPU;
    gpdma_irq_info[idx_ch_gpdma].last_err = ERR_GPDMA_CH_MISSING_INTR_ERR;
    INTRINSIC_BARRIER;
}

PRIVATE com_gpdma_trw_info_t const *com_gpdma_get_trw_info (uint32_t const idx_ch_gpdma, uint32_t const bytes, uint64_t const dst,
                                                            uint64_t const src)
{
    uint32_t trw_info_idx = sizeof (com_gpdma_trw_info) / sizeof (com_gpdma_trw_info_t) - 1;
    com_gpdma_trw_info_t const *p_trw_info = com_gpdma_trw_info;

#if HAVE_MEM_FB_GPDMA
    if (idx_ch_gpdma < GPDMA_RCS_MAX)
    {
        p_trw_info += 2;
        trw_info_idx -= 2;
    }
#endif // HAVE_MEM_FB_GPDMA

    while ((trw_info_idx) && ((p_trw_info->bytes > bytes) || (bytes % p_trw_info->bytes) || (dst % 4) || (src % 4)))
    {
        p_trw_info++;
        trw_info_idx--;
    }
    return p_trw_info;
}

PRIVATE e_gpdma_tr_width_t com_gpdma_get_trw (uint32_t const idx_ch_gpdma, int const bytes, uint64_t const dst, uint64_t const src)
{
    com_gpdma_trw_info_t const *const p_trw_info = com_gpdma_get_trw_info (idx_ch_gpdma, bytes, dst, src);
    return p_trw_info->e_tr_width;
}

PRIVATE com_gpdma_ctl_inc_t com_gpdma_get_inc (e_gpdma_ttfc_t const ttfc)
{
    com_gpdma_ctl_inc_t ctl_inc = {.sinc = ((ttfc == e_GPDMA_TTFC_PER2PER_DMAC) || (ttfc == e_GPDMA_TTFC_PER2MEM_DMAC)) ? 1 : 0,
                                   .dinc = ((ttfc == e_GPDMA_TTFC_PER2PER_DMAC) || (ttfc == e_GPDMA_TTFC_MEM2PER_DMAC)) ? 1 : 0};
    return ctl_inc;
}

PRIVATE uint64_t com_gpdma_desc_addr_convert (gpdma_desc_t *p_desc, uint32_t const desc_cnt)
{
    uint32_t idx = 0;
    uint32_t is_last = 0;
    uint64_t const desc_addr = com_gpdma_addr_convert (U64 (p_desc));

    do {
        gpdma_desc_t *const p_desc_llp = (gpdma_desc_t *)p_desc->llp;
        is_last = p_desc->ctl.SHADOWREG_OR_LLI_LAST;
        p_desc->dst = com_gpdma_addr_convert (p_desc->dst);
        p_desc->src = com_gpdma_addr_convert (p_desc->src);
        p_desc->llp = com_gpdma_addr_convert (p_desc->llp);
        p_desc = p_desc_llp;
        idx++;
    } while ((!is_last) && (idx < desc_cnt));

    return desc_addr;
}

PRIVATE uint64_t com_gpdma_get_cfg (uint32_t const idx_ch_gpdma, e_gpdma_multblk_type_t const multblk_type, e_gpdma_ttfc_t const ttfc)
{
    RT_ASSERT (multblk_type < e_GPDMA_MULTBLK_MAX);
    RT_ASSERT (ttfc < e_GPDMA_TTFC_MAX);

    // rcs and memfb has the same  default.
    rcs_dmac_ch1_cfg_reg_t dmac_cfg = {.value =
                                           (idx_ch_gpdma % MAX_GPDMA_CH_PER_INST) ? GPDMA_CFGREG_CH1_DEFAULT : GPDMA_CFGREG_CH2_DEFAULT};
    dmac_cfg.DST_MULTBLK_TYPE = ENUM2U32 (multblk_type);
    dmac_cfg.SRC_MULTBLK_TYPE = ENUM2U32 (multblk_type);
    dmac_cfg.TT_FC = ENUM2U32 (ttfc);
    dmac_cfg.DST_PER = 1; // 0 and 1 goes in pair
    dmac_cfg.SRC_PER = 0;
    dmac_cfg.DST_OSR_LMT = 15;
    dmac_cfg.SRC_OSR_LMT = 15;

    // set HS_SEL_SRC
    if ((ttfc == e_GPDMA_TTFC_MEM2MEM_DMAC) || (ttfc == e_GPDMA_TTFC_MEM2PER_DMAC))
        dmac_cfg.HS_SEL_SRC = 1;
    else
        dmac_cfg.HS_SEL_SRC = 0;

    // set HS_SEL_DST
    if ((ttfc == e_GPDMA_TTFC_MEM2MEM_DMAC) || (ttfc == e_GPDMA_TTFC_PER2MEM_DMAC))
        dmac_cfg.HS_SEL_DST = 1;
    else
        dmac_cfg.HS_SEL_DST = 0;
    return dmac_cfg.value;
}

PRIVATE uint32_t INTRINSIC_ALWAYS_INLINE com_gpdma_get_msize (uint32_t const idx_ch_gpdma)
{
    return (idx_ch_gpdma == GPDMA_RCS1) ? ENUM2U32 (e_GPDMA_MSIZE_ITEMS_8) : ENUM2U32 (e_GPDMA_MSIZE_ITEMS_4);
}

PRIVATE uint64_t INTRINSIC_ALWAYS_INLINE com_gpdma_addr_convert (uint64_t const addr)
{
    return (addr >= 0x10000000) ? addr - 0x10000000 + RCS_CPU_ADDR_START : addr;
}

PRIVATE void com_gpdma_llp (uint32_t const idx_ch_gpdma, uint64_t const addr_desc, gpdma_task_info_t const *const p_task)
{
    uint32_t const idx_inst_gpdma = GPDMA_IDX_CH2INST (idx_ch_gpdma);
    uint32_t const ch_offset = GPDMA_CH_OFFSET (idx_ch_gpdma);
    rcs_dmac_t *const p_gpdma = gpdma_cfg[idx_inst_gpdma].gpdma;
    com_gpdma_ch_t *p_gpdma_ch = GPMDA_PCH_INST2CH1 (idx_inst_gpdma);
    uint64_t const dmac_cfg_val = com_gpdma_get_cfg (idx_ch_gpdma, e_GPDMA_MULTBLK_LINKED_LIST, e_GPDMA_TTFC_MEM2MEM_DMAC);
    uint64_t const chenreg = GPDMA_CH_START << ch_offset;

    p_gpdma_ch += ch_offset;

    REG_WRITE64 (&p_gpdma_ch->CFG, dmac_cfg_val);
    INTRINSIC_EXT_WAIT;
    REG_WRITE64 (&p_gpdma_ch->LLP, addr_desc);
    REG_WRITE64 (&p_gpdma_ch->INTSTATUS_ENABLE,
                 (gpdma_cfg[idx_inst_gpdma].irq_num == GPDMA_NO_INTR) ? GPDMA_CH_INTSTATUS_DIS : GPDMA_CH_INTSTATUS_EN);
    INTRINSIC_EXT_WAIT;
    REG_WRITE64 (&p_gpdma->CHENREG, chenreg); // start
}

PRIVATE void com_gpdma_reg (uint32_t const idx_ch_gpdma, com_gpdma_size_info_t const *const p_size_info)
{
    uint32_t const msize = com_gpdma_get_msize (idx_ch_gpdma);
    uint32_t const ch_offset = GPDMA_CH_OFFSET (idx_ch_gpdma);
    uint32_t const idx_inst_gpdma = GPDMA_IDX_CH2INST (idx_ch_gpdma);
    rcs_dmac_t *const p_gpdma = gpdma_cfg[idx_inst_gpdma].gpdma;
    com_gpdma_ch_t *p_gpdma_ch = GPMDA_PCH_INST2CH1 (idx_inst_gpdma);
    uint64_t const dmac_cfg_val = com_gpdma_get_cfg (idx_ch_gpdma, e_GPDMA_MULTBLK_REGISTER, e_GPDMA_TTFC_MEM2MEM_DMAC);
    uint64_t const chenreg = GPDMA_CH_START << ch_offset;

#if HAVE_MEM_FB_GPDMA
    com_gpdma_ctl_t dmac_ctl = {.value = (idx_ch_gpdma < GPDMA_RCS_MAX) ? GPDMA_RCS_CTL_DEFAULT : GPDMA_MEMFB_CTL_DEFAULT};
#else
    com_gpdma_ctl_t dmac_ctl = {.value = GPDMA_RCS_CTL_DEFAULT};
#endif // HAVE_MEM_FB_GPDMA

    p_gpdma_ch += ch_offset;

    dmac_ctl.SHADOWREG_OR_LLI_VALID = 1;
    dmac_ctl.SHADOWREG_OR_LLI_LAST = 1; // com_gpdma_reg only support 1 descriptor,
    dmac_ctl.DST_MSIZE = msize;
    dmac_ctl.SRC_MSIZE = msize;
    dmac_ctl.SINC = 0; // todo: need to be updated when enable peripheral
    dmac_ctl.DINC = 0; // todo: need to be updated when enable peripheral
    dmac_ctl.DST_TR_WIDTH = p_size_info->tr_width;
    dmac_ctl.SRC_TR_WIDTH = p_size_info->tr_width;

    INTRINSIC_BARRIER;
    REG_WRITE64 (&p_gpdma_ch->CFG, dmac_cfg_val);
    INTRINSIC_EXT_WAIT;
    REG_WRITE64 (&p_gpdma_ch->SAR, p_size_info->src);
    REG_WRITE64 (&p_gpdma_ch->DAR, p_size_info->dst);
    REG_WRITE64 (&p_gpdma_ch->BLOCK_TS, p_size_info->block_ts); // HW always +1
    REG_WRITE64 (&p_gpdma_ch->INTSTATUS_ENABLE,
                 (gpdma_cfg[idx_inst_gpdma].irq_num == GPDMA_NO_INTR) ? GPDMA_CH_INTSTATUS_DIS : GPDMA_CH_INTSTATUS_EN);
    //
    // NOTICE: the SHADOWREG_OR_LLI_VALID/LAST must be written last.   This forces the proper 32-bit write order.
    //
    uint32_t const dmac_ctl_upper = dmac_ctl.value >> 32;
    uint32_t const dmac_ctl_lower = dmac_ctl.value & 0xffffffff;
    REG_WRITE (((uint32_t *)&p_gpdma_ch->CTL), dmac_ctl_lower);
    INTRINSIC_BARRIER;
    REG_WRITE (((uint32_t *)&p_gpdma_ch->CTL) + 1, dmac_ctl_upper);
    INTRINSIC_EXT_WAIT;

    REG_WRITE64 (&p_gpdma->CHENREG, chenreg); // start
}

PRIVATE void com_gpdma_trans (uint32_t const idx_ch_gpdma, void const *const dst, void const *const src, uint32_t const bytes,
                              gpdma_task_info_t *p_task)
{
    RT_ASSERT (idx_ch_gpdma < MAX_GPDMA_CH);
    RT_ASSERT_POINTER (dst);
    RT_ASSERT_POINTER (src);
    com_gpdma_size_info_t size_info = {0};

#if HAVE_MEM_FB_GPDMA
    uint32_t const max_bytes = (idx_ch_gpdma < GPDMA_RCS_MAX) ? MAX_GPDMA_RCS_BLK_BYTE : MAX_GPDMA_MEMFB_BLK_BYTE;
#else
    uint32_t const max_bytes = MAX_GPDMA_RCS_BLK_BYTE;
#endif // HAVE_MEM_FB_GPDMA

    RT_ASSERT ((bytes != 0) && (bytes <= max_bytes));

    uint64_t const addr_src = U64 (src);
    uint64_t const addr_dst = U64 (dst);
    com_gpdma_trw_info_t const *const p_trw_info = com_gpdma_get_trw_info (idx_ch_gpdma, bytes, addr_dst, addr_src);
    uint32_t block_ts = MIN (MAX_GPDMA_BLK_TRF_SZ, bytes / p_trw_info->bytes);

    size_info.is_last = true;
    size_info.src = com_gpdma_addr_convert (addr_src);
    size_info.dst = com_gpdma_addr_convert (addr_dst);
    size_info.block_ts = block_ts - 1;
    size_info.tr_width = ENUM2U32 (p_trw_info->e_tr_width);
    com_gpdma_wait_start (idx_ch_gpdma);
    com_gpdma_set_isr_info (idx_ch_gpdma, p_task);
    com_gpdma_reg (idx_ch_gpdma, &size_info);
    com_gpdma_irq_en (GPDMA_IDX_CH2INST (idx_ch_gpdma));
}

PRIVATE void com_gpdma_trans_desc (uint32_t const idx_ch_gpdma, gpdma_desc_t *p_desc, uint32_t const desc_cnt, gpdma_task_info_t *p_task)
{
    RT_ASSERT (idx_ch_gpdma < MAX_GPDMA_CH);
    RT_ASSERT_POINTER (p_desc);
    uint64_t addr_desc = U64 (p_desc);

    com_gpdma_verify_desc (idx_ch_gpdma, p_desc, desc_cnt);
    addr_desc = com_gpdma_desc_addr_convert (p_desc, desc_cnt);
    com_gpdma_wait_start (idx_ch_gpdma);
    com_gpdma_set_isr_info (idx_ch_gpdma, p_task);
    com_gpdma_llp (idx_ch_gpdma, addr_desc, p_task);
    com_gpdma_irq_en (GPDMA_IDX_CH2INST (idx_ch_gpdma));
}

PRIVATE void com_gpdma_wait_done (uint32_t const idx_ch_gpdma)
{
    volatile rcs_dmac_chenreg_reg_t dmac_chenreg = {.value = 0};
    rcs_dmac_t *const p_com_gpdma = gpdma_cfg[GPDMA_IDX_CH2INST (idx_ch_gpdma)].gpdma;
    uint64_t const ch_en_msk = (idx_ch_gpdma % MAX_GPDMA_CH_PER_INST) ? RCS_DMAC_CHENREG_CH2_EN_BF_MSK : RCS_DMAC_CHENREG_CH1_EN_BF_MSK;

    do {
        dmac_chenreg.value = REG_READ64 (&p_com_gpdma->CHENREG);
    } while (dmac_chenreg.value & ch_en_msk);
}

PRIVATE void com_gpdma_wait_start (uint32_t const idx_ch_gpdma)
{
    if (idx_ch_gpdma < GPDMA_RCS_MAX)
        com_lock_acquire (com_gpdma_e_lock[idx_ch_gpdma]);
    else
    {
        com_gpdma_wait_done (idx_ch_gpdma);
    }
}

#if CPU_AX
PRIVATE void com_gpdma_en_all ()
{
    for (uint32_t idx = 0; idx < MAX_GPDMA_INST; idx++)
    {
        gpdma_cfg[idx].gpdma->CFGREG.value = (gpdma_cfg[idx].irq_num != GPDMA_NO_INTR) ? GPDMA_CFGREG_EN : GPDMA_CFGREG_EN_DMAC;
    }
}
#endif // #if CPU_AX

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
COMPILE_ASSERT (sizeof (gpdma_desc_t) == 64);

/**
 * @brief           gpDMA fill 1 descriptor, fill up everything EXCEPT llp field. Use need to chain the descriptors.
 * @param [in]      e_gpdma_rcs: Which RCS GPDMA instance.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      bytes: Bytes to transfer.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      is_last: Is this the last descriptor.
 * @param [in]      ttfc: Type of transfer.
 * @return          none.
 */
void com_gpdma_rcs_fill_desc (e_gpdma_rcs_t const e_gpdma_rcs, gpdma_desc_t *const p_desc, uint32_t const bytes, void const *const dst,
                              void const *const src, bool const is_last, e_gpdma_ttfc_t const ttfc)
{
    RT_ASSERT (e_gpdma_rcs < e_GPDMA_RCS_MAX);
    RT_ASSERT_POINTER (p_desc);
    RT_ASSERT_POINTER (dst);
    RT_ASSERT_POINTER (src);
    RT_ASSERT (bytes);

    uint32_t const idx_ch_gpdma = U32 (e_gpdma_rcs);
    uint64_t const addr_src = U64 (src);
    uint64_t const addr_dst = U64 (dst);
    com_gpdma_trw_info_t const *const p_trw_info = com_gpdma_get_trw_info (idx_ch_gpdma, bytes, addr_dst, addr_src);
    com_gpdma_ctl_inc_t ctl_inc = com_gpdma_get_inc (ttfc);
    uint32_t const block_ts = bytes / p_trw_info->bytes;
    uint32_t const msize = com_gpdma_get_msize (idx_ch_gpdma);

    RT_ASSERT ((block_ts) && (block_ts <= MAX_GPDMA_BLK_TRF_SZ));

    p_desc->src = addr_src;
    p_desc->dst = addr_dst;
    p_desc->sstat = 0;
    p_desc->dstat = 0;
    p_desc->llp_status = 0;
    p_desc->block_ts = block_ts - 1;
    p_desc->ctl.value = GPDMA_RCS_CTL_DEFAULT;
    p_desc->ctl.SINC = ctl_inc.sinc;
    p_desc->ctl.DINC = ctl_inc.dinc;
    p_desc->ctl.SRC_MSIZE = msize;
    p_desc->ctl.DST_MSIZE = msize;
    p_desc->ctl.SRC_TR_WIDTH = ENUM2U32 (p_trw_info->e_tr_width);
    p_desc->ctl.DST_TR_WIDTH = ENUM2U32 (p_trw_info->e_tr_width);
    p_desc->ctl.SHADOWREG_OR_LLI_VALID = 1;

    if (is_last == true)
    {
        p_desc->ctl.SHADOWREG_OR_LLI_LAST = 1;
        p_desc->llp = 0x0;
    }
    else
    {
        p_desc->ctl.SHADOWREG_OR_LLI_LAST = 0;
    }
}

/**
 * @brief           Initialize gpDMA. Call only once during boot
 * @param [in]      none.
 * @return          none.
 */
void com_gpdma_init ()
{
    com_gpdma_init_irq (com_gpdma_irq_handler);
#if CPU_AX
    com_gpdma_en_all ();
#endif // CPU_AX
}

/**
 * @brief           Wait until gpDma transfer completed.
 * @param [in]      e_gpdma_rcs_t: Which RCS GPDMA instance.
 * @return          uint64_t: error status. 0=success, non-zero=fail
 */
uint64_t com_gpdma_rcs_wait (e_gpdma_rcs_t const e_gpdma_rcs)
{
    RT_ASSERT (e_gpdma_rcs < e_GPDMA_RCS_MAX);
    uint32_t const idx_ch_gpdma = U32 (e_gpdma_rcs);

    com_gpdma_wait_done (idx_ch_gpdma);
    return gpdma_irq_info[idx_ch_gpdma].last_err;
}

/**
 * @brief           Get last gpDMA error code. Function is read to clear.
 * @param [in]      e_gpdma_rcs_t: Which RCS GPDMA instance.
 * @return          uint64_t: gpDMA error code.
 */
uint64_t com_gpdma_rcs_get_last_errcode (e_gpdma_rcs_t const e_gpdma_rcs)
{
    RT_ASSERT (e_gpdma_rcs < e_GPDMA_RCS_MAX);
    uint32_t const idx_ch_gpdma = U32 (e_gpdma_rcs);

    uint64_t const last_err = gpdma_irq_info[idx_ch_gpdma].last_err;
    gpdma_irq_info[idx_ch_gpdma].last_err = ERR_GPDMA_CH_OK;
    return last_err;
}

/**
 * @brief           gpDMA transfer
 * @param [in]      gpdma_inst: Which RCS GPDMA instance.
 * @param [in]      dst: Pointer to destination buffer.
 * @param [in]      src: Pointer to source buffer.
 * @param [in]      bytes: Bytes to transfer.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_rcs (e_gpdma_rcs_t const e_gpdma_rcs, void const *const dst, void const *const src, uint32_t const bytes,
                    gpdma_task_info_t *p_task)
{
    RT_ASSERT (e_gpdma_rcs < e_GPDMA_RCS_MAX);
    com_gpdma_trans (ENUM2U32 (e_gpdma_rcs), dst, src, bytes, p_task);
}

/**
 * @brief           gpDMA transfer using descriptor
 * @param [in]      gpdma_inst: Which RCS GPDMA instance.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_rcs_desc (e_gpdma_rcs_t const e_gpdma_rcs, gpdma_desc_t *p_desc, uint32_t const desc_cnt, gpdma_task_info_t *p_task)
{
    RT_ASSERT (e_gpdma_rcs < e_GPDMA_RCS_MAX);
    com_gpdma_trans_desc (ENUM2U32 (e_gpdma_rcs), p_desc, desc_cnt, p_task);
}

#if HAVE_MEM_FB_GPDMA
/**
 * @brief           gpDMA transfer using descriptor
 * @param [in]      e_gpdma_memfb: Which MEMFB GPDMA instance.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_memfb_desc (e_gpdma_memfb_t const e_gpdma_memfb, gpdma_desc_t *p_desc, uint32_t const desc_cnt)
{
    RT_ASSERT_IN_RANGE (e_gpdma_memfb, e_GPDMA_MEMFB0_0, e_GPDMA_MEMFB1_3);
    com_gpdma_trans_desc (ENUM2U32 (e_gpdma_memfb), p_desc, desc_cnt, NULL);
}

#endif // HAVE_MEM_FB_GPDMA
