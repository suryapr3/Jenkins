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
#ifndef COMMON_GPDMA_H
#define COMMON_GPDMA_H

#include <stdint.h>
#include "rcs_dmac.h"

#if (CPU_TX || CPU_AX)
#include "mem_fb_dmac.h"
#define HAVE_MEM_FB_GPDMA 1
#endif // CPU_TX

#define MAX_GPDMA_BLOCK_TS_VAL (1023)

#define ERR_GPDMA_CH_OK                             (0x0000000000000000)
#define ERR_GPDMA_CH_MISSING_INTR_ERR               (0x1111111111111111)

#define ERR_GPDMA_CH_SRC_DEC_ERR                    (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SRC_DEC_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_DST_DEC_ERR                    (RCS_DMAC_CH1_INTSTAT_ENREG_EN_DST_DEC_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SRC_SLV_ERR                    (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SRC_SLV_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_DST_SLV_ERR                    (RCS_DMAC_CH1_INTSTAT_ENREG_EN_DST_SLV_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_LLI_RD_DEC_ERR                 (RCS_DMAC_CH1_INTSTAT_ENREG_EN_LLI_RD_DEC_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_LLI_WR_DEC_ERR                 (RCS_DMAC_CH1_INTSTAT_ENREG_EN_LLI_WR_DEC_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_LLI_RD_SLV_ERR                 (RCS_DMAC_CH1_INTSTAT_ENREG_EN_LLI_RD_SLV_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_LLI_WR_SLV_ERR                 (RCS_DMAC_CH1_INTSTAT_ENREG_EN_LLI_WR_SLV_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SHADOWREG_OR_LLI_INVALID_ERR   (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SHDWREG_OR_LLI_INVALID_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_MULTIBLKTYPE_ERR         (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_MULTIBLKTYPE_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_DEC_ERR                  (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_DEC_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_WR2RO_ERR                (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_WR2RO_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_RD2RWO_ERR               (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_RD2RWO_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_WRONCHEN_ERR             (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_WRONCHEN_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_SHADOWREG_WRON_VALID_ERR (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_SHDWREG_WRON_VALID_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_WRONHOLD_ERR             (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_WRONHOLD_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_SLVIF_WRPARITY_ERR             (RCS_DMAC_CH1_INTSTAT_ENREG_EN_SLVIF_WRPARITY_ERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_CH_LOCK_CLEARED                (RCS_DMAC_CH1_INTSTAT_ENREG_EN_CH_LOCK_CLRED_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_CH_SRC_SUSPENDED               (RCS_DMAC_CH1_INTSTAT_ENREG_EN_CH_SRC_SUSPENDED_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_CH_SUSPENDED                   (RCS_DMAC_CH1_INTSTAT_ENREG_EN_CH_SUSPENDED_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_CH_DISABLED                    (RCS_DMAC_CH1_INTSTAT_ENREG_EN_CH_DISD_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_CH_ABORTED                     (RCS_DMAC_CH1_INTSTAT_ENREG_EN_CH_ABORTED_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_ECC_PROT_CHMEM_CORRERR         (RCS_DMAC_CH1_INTSTAT_ENREG_EN_ECC_PROT_CHMEM_CORRERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_ECC_PROT_CHMEM_UNCORRERR       (RCS_DMAC_CH1_INTSTAT_ENREG_EN_ECC_PROT_CHMEM_UNCORRERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_ECC_PROT_UIDMEM_CORRERR        (RCS_DMAC_CH1_INTSTAT_ENREG_EN_ECC_PROT_UIDMEM_CORRERR_INTSTAT_BF_MSK)
#define ERR_GPDMA_CH_ECC_PROT_UIDMEM_UNCORRERR      (RCS_DMAC_CH1_INTSTAT_ENREG_EN_ECC_PROT_UIDMEM_UNCORRERR_INTSTAT_BF_MSK)

typedef enum
{
    e_GPDMA_TR_WIDTH_8 = 0,
    e_GPDMA_TR_WIDTH_16 = 1,
    e_GPDMA_TR_WIDTH_32 = 2,
    e_GPDMA_TR_WIDTH_64 = 3,
    e_GPDMA_TR_WIDTH_128 = 4,
#if HAVE_MEM_FB_GPDMA // only MEM_FB_GPDMA support value 5 & 6
    e_GPDMA_TR_WIDTH_256 = 5,
    e_GPDMA_TR_WIDTH_512 = 6,
#endif // HAVE_MEM_FB_GPDMA
    e_GPDMA_TR_WIDTH_MAX
} e_gpdma_tr_width_t;

typedef enum
{
    e_GPDMA_MSIZE_ITEMS_1 = 0,
    e_GPDMA_MSIZE_ITEMS_4 = 1,
    e_GPDMA_MSIZE_ITEMS_8 = 2,  // only RCS CH0 and CH1 allow to use this.
    e_GPDMA_MSIZE_ITEMS_16 = 3, // only RCS CH0 allow to use this
    e_GPDMA_MSIZE_MAX
} e_gpdma_msize_t;

typedef enum
{
    e_GPDMA_TTFC_MEM2MEM_DMAC = 0,
    e_GPDMA_TTFC_MEM2PER_DMAC = 1,
    e_GPDMA_TTFC_PER2MEM_DMAC = 2,
    e_GPDMA_TTFC_PER2PER_DMAC = 3,
    e_GPDMA_TTFC_MAX
} e_gpdma_ttfc_t;

typedef enum
{
    e_GPDMA_RCS_0 = 0,
    e_GPDMA_RCS_1 = 1,
    e_GPDMA_RCS_MAX
} e_gpdma_rcs_t;

#if HAVE_MEM_FB_GPDMA
typedef enum
{
    e_GPDMA_MEMFB0_0 = 2,
    e_GPDMA_MEMFB0_1 = 3,
    e_GPDMA_MEMFB0_2 = 4,
    e_GPDMA_MEMFB0_3 = 5,
    e_GPDMA_MEMFB1_0 = 6,
    e_GPDMA_MEMFB1_1 = 7,
    e_GPDMA_MEMFB1_2 = 8,
    e_GPDMA_MEMFB1_3 = 9,
    e_GPDMA_MEMFB_MAX
} e_gpdma_memfb_t;
#endif // HAVE_MEM_FB_GPDMA

typedef union {
    struct
    {
        uint64_t SMS : 1;
        uint64_t : 1;
        uint64_t DMS : 1;
        uint64_t : 1;
        uint64_t SINC : 1;
        uint64_t : 1;
        uint64_t DINC : 1;
        uint64_t : 1;
        uint64_t SRC_TR_WIDTH : 3;
        uint64_t DST_TR_WIDTH : 3;
        uint64_t SRC_MSIZE : 4;
        uint64_t DST_MSIZE : 4;
        uint64_t AR_CACHE : 4;
        uint64_t AW_CACHE : 4;
        uint64_t NONPOSTED_LASTWRITE_EN : 1;
        uint64_t : 1;
        uint64_t AR_PROT : 3;
        uint64_t AW_PROT : 3;
        uint64_t ARLEN_EN : 1;
        uint64_t ARLEN : 8;
        uint64_t AWLEN_EN : 1;
        uint64_t AWLEN : 8;
        uint64_t SRC_STAT_EN : 1;
        uint64_t DST_STAT_EN : 1;
        uint64_t IOC_BLKTFR : 1;
        uint64_t : 3;
        uint64_t SHADOWREG_OR_LLI_LAST : 1;
        uint64_t SHADOWREG_OR_LLI_VALID : 1;
    };
    uint64_t value;
} com_gpdma_ctl_t;

typedef struct
{
    uint64_t src;
    uint64_t dst;
    struct
    {
        uint64_t block_ts : 22;
        uint64_t : 42;
    };
    uint64_t llp; // next descriptor
    com_gpdma_ctl_t ctl;
    uint32_t sstat;      // CHx_SSTAT
    uint32_t dstat;      // CHx_DSTAT
    uint64_t llp_status; // CHx_LLP_STATUS
    uint64_t : 64;       // Reserved
} gpdma_desc_t;

typedef void (*gpdma_task_cb) (void *p_arg);

typedef struct
{
    gpdma_task_cb pfunc_gpdma_callback;
    void *p_arg;
} gpdma_task_info_t;

/**
 * @brief           gpDMA fill 1 descriptor, will fill up everything EXCEPT llp field. User need to chain the descriptors.
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
                              void const *const src, bool const is_last, e_gpdma_ttfc_t const ttfc);
/**
 * @brief           Initialize gpDMA. Call only once during boot.
 * @param [in]      none.
 * @return          none.
 */
void com_gpdma_init ();

/**
 * @brief           Poll until gpDma transfer completed.
 * @param [in]      e_gpdma_rcs_t: Which RCS GPDMA instance.
 * @return          uint64_t: error status. 0=success, non-zero=fail
 */
uint64_t com_gpdma_rcs_wait (e_gpdma_rcs_t const e_gpdma_rcs);

/**
 * @brief           Get last gpDMA error code. Function is read to clear.
 * @param [in]      e_gpdma_rcs_t: Which RCS GPDMA instance.
 * @return          uint64_t: gpDMA error code.
 */
uint64_t com_gpdma_rcs_get_last_errcode (e_gpdma_rcs_t const e_gpdma_rcs);

/**
 * @brief           gpDMA transfer. Only support up to 16KB transfer. Use descriptor mode if more data need to be transfered.
 * @param [in]      e_gpdma_rcs: Which RCS GPDMA instance.
 * @param [in]      dst: Pointer to destination buffer.
 * @param [in]      src: Pointer to source buffer.
 * @param [in]      bytes: Bytes to transfer.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_rcs (e_gpdma_rcs_t const e_gpdma_rcs, void const *const dst, void const *const src, uint32_t const bytes,
                    gpdma_task_info_t *p_task);

/**
 * @brief           gpDMA transfer using descriptor
 * @param [in]      e_gpdma_rcs: Which RCS GPDMA instance.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_rcs_desc (e_gpdma_rcs_t const e_gpdma_rcs, gpdma_desc_t *p_desc, uint32_t const desc_cnt, gpdma_task_info_t *p_task);

// --- HAVE_MEM_FB_GPDMA start here ---
#if HAVE_MEM_FB_GPDMA
/**
 * @brief           gpDMA transfer using descriptor
 * @param [in]      e_gpdma_memfb: Which MEMFB GPDMA instance.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. gpdma_task_info_t need to be static or global variable.
 * @return          none.
 */
void com_gpdma_memfb_desc (e_gpdma_memfb_t const e_gpdma_memfb, gpdma_desc_t *p_desc, uint32_t const desc_cnt);

#endif // HAVE_MEM_FB_GPDMA
// --- HAVE_MEM_FB_GPDMA end here ---

#endif // COMMON_GPDMA_H
