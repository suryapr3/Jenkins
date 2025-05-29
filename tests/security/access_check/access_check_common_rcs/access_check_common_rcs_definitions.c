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
 * @file    access_check_common_rcs_definitions.c
 * @brief   this file is a container for all the RCS common functions that are used for access check
 *          tests
 */

#include "access_check_common_rcs_definitions.h"

volatile drf_dma_desc_t __attribute__ ((section (".sram.rx.rw"))) drf_descr_buffer[100];
volatile gpdma_desc_t __attribute__ ((section (".sram.ax.rw"))) descr_buffer[100];

rcs_dmac_ch1_ctl_reg_t dmac_ctl_reg = {
    .SRC_TR_WIDTH = 4,
    .DST_TR_WIDTH = 4,
    .SHADOWREG_OR_LLI_VALID = 1,
    .SRC_MSIZE = 4,
    .DST_MSIZE = 4,
    .ARLEN_EN = 1,                                         // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1,                                         // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR = 1,
    .DST_STAT_EN = 1,
    .SRC_STAT_EN = 1,
    .NONPOSTED_LASTWRITE_EN = 0,
};

rcs_dmac_ch2_ctl_reg_t dmac_ctl2_reg = {
    .SRC_TR_WIDTH = 4,
    .DST_TR_WIDTH = 4,
    .SHADOWREG_OR_LLI_VALID = 1,
    .SRC_MSIZE = 4,
    .DST_MSIZE = 4,
    .ARLEN_EN = 1,                                         // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1,                                         // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR = 1,
    .DST_STAT_EN = 1,
    .SRC_STAT_EN = 1,
    .NONPOSTED_LASTWRITE_EN = 0,
};

rcs_dmac_ch1_cfg_reg_t dmac_cfg_reg = {.SRC_MULTBLK_TYPE = 3,
    .DST_MULTBLK_TYPE = 3,
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,                                            // Flow control select: M2M
    .HS_SEL_SRC = 0,                                       // SW handshake
    .HS_SEL_DST = 1,
    .SRC_HWHS_POL = 0,                                     // HS polarity
    .DST_HWHS_POL = 0,
    .SRC_PER = 1,                                          // HS interface sel
    .DST_PER = 1,
    .CH_PRIOR = 0x7,                                       // Prio (don't care).
    .LOCK_CH = 0,                                          // Keep channel (don't care).
    .LOCK_CH_L = 1,                                        // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF,                                    // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};

rcs_dmac_ch2_cfg_reg_t dmac_cfg2_reg = {.SRC_MULTBLK_TYPE = 3,
    .DST_MULTBLK_TYPE = 3,
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,
    .HS_SEL_SRC = 0,
    .HS_SEL_DST = 1,
    .SRC_HWHS_POL = 0,
    .DST_HWHS_POL = 0,
    .SRC_PER = 1,
    .DST_PER = 1,
    .CH_PRIOR = 0x7,
    .LOCK_CH = 0,
    .LOCK_CH_L = 1,
    .SRC_OSR_LMT = 0xF,
    .DST_OSR_LMT = 0x6
};

mem_fb_dmac_ch1_ctl_reg_t drf_dmac_ctl_reg = {
    .SRC_TR_WIDTH = 4,
    .DST_TR_WIDTH = 4,
    .SHADOWREG_OR_LLI_VALID = 1,
    .SRC_MSIZE = 4,
    .DST_MSIZE = 4,
    .ARLEN_EN = 1,
    .ARLEN = 0x5,
    .AWLEN_EN = 1,
    .AWLEN = 0x3,
    .IOC_BLKTFR = 1,
    .DST_STAT_EN = 1,
    .SRC_STAT_EN = 1,
    .NONPOSTED_LASTWRITE_EN = 0,
};

mem_fb_dmac_ch2_ctl_reg_t drf_dmac_ctl2_reg = {
    .SRC_TR_WIDTH = 4,
    .DST_TR_WIDTH = 4,
    .SHADOWREG_OR_LLI_VALID = 1,
    .SRC_MSIZE = 4,
    .DST_MSIZE = 4,
    .ARLEN_EN = 1,
    .ARLEN = 0x5,
    .AWLEN_EN = 1,
    .AWLEN = 0x3,
    .IOC_BLKTFR = 1,
    .DST_STAT_EN = 1,
    .SRC_STAT_EN = 1,
    .NONPOSTED_LASTWRITE_EN = 0,
};

mem_fb_dmac_ch1_cfg_reg_t drf_dmac_cfg_reg = {
    .SRC_MULTBLK_TYPE = 3,
    .DST_MULTBLK_TYPE = 3,
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,
    .HS_SEL_SRC = 0,
    .HS_SEL_DST = 1,
    .SRC_HWHS_POL = 0,
    .DST_HWHS_POL = 0,
    .SRC_PER = 1,
    .DST_PER = 1,
    .CH_PRIOR = 0x7,
    .LOCK_CH = 0,
    .LOCK_CH_L = 1,
    .SRC_OSR_LMT = 0xF,
    .DST_OSR_LMT = 0x6
};

mem_fb_dmac_ch2_cfg_reg_t drf_dmac_cfg2_reg = {
    .SRC_MULTBLK_TYPE = 3,
    .DST_MULTBLK_TYPE = 3,
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,                                            // Flow control select: M2M
    .HS_SEL_SRC = 0,                                       // SW handshake
    .HS_SEL_DST = 1,                                       // HS polarity
    .SRC_HWHS_POL = 0,
    .DST_HWHS_POL = 0,
    .SRC_PER = 1,
    .DST_PER = 1,
    .CH_PRIOR = 0x7,
    .LOCK_CH = 0,
    .LOCK_CH_L = 1,                                        // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF,                                    // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};

/**
 * function         gpdma_set_descr()
 * @brief           Sets up a GPDMA transfer descriptor. This function initializes and sets up a DRF DMA
 *                  (General Purpose Direct Memory Access transfer descriptor with the given parameters.
 *                  It zeroes out the descriptor structure,sets the source and destination addresses,
 *                  block transfer size, and control register value. It also marks the descriptor as the
 *                  last in a linked list and copies the descriptor settings to the descriptor buffer.
 * @param [in]      desc_idx, dst_addr, src_addr, block_size
 */

void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr, uint32_t block_size)
{
    // The below  line declares a variable desc of type gpdma_desc_t,
    // which is presumably a structure that holds the details of a DMA transfer descriptor.
    gpdma_desc_t desc;
    // The below line initializes the desc structure to zero.
    // It ensures that all fields in the descriptor are set to zero before setting specific fields.
    memset ((void *)&desc, 0, sizeof (gpdma_desc_t));
    // The below  line sets the source address (least significant bits) in the descriptor to the value provided by src_addr
    desc.sar_lsb = src_addr;
    // The below  line sets the destination address (least significant bits) in the descriptor to the value provided by dst_addr
    desc.dar_lsb = dst_addr;
    // This  below line sets the block transfer size in the descriptor to the value provided by block_size.
    desc.block_ts = block_size;
    // This line sets the control register value in the descriptor to a value dmac_ctl_reg
    desc.ctl = dmac_ctl_reg;
    // This line sets a specific field within the control register,
    // this descriptor is the last in a linked list or that it should use shadow registers
    // while 1 indicates that the shadow register contents are valid
    desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    // This line copies the contents of the desc structure into another memory location, presumably a buffer called descr_buffer.
    // This buffer might be an array or a memory-mapped register that the DMA controller uses to read the descriptor settings.
    memcpy ((void*)&descr_buffer, &desc, sizeof (gpdma_desc_t));
}

/**
 * function         gpdma_test_LLI()
 * @brief           Function for configuring and initiating a DMA (Direct Memory Access) transfer using a linked list item
 *                  (LLI) on a specific DMA channel (Channel 1 in this case). It sets up the DMA transfer parameters, starts
 *                  the transfer, and then waits for the transfer to complete. It also waits for DMA INTSTAT bit16 to set for
 *                  indicating a DEC ERROR in case of access denied to the target.
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */

int gpdma_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr)
{
    int cnt;
    volatile rcs_dmac_ch1_intstat_reg_t rcs_dmac_ch1_intstat_reg = {.value = RCS_DMAC_CH1_INTSTAT_DEFAULT};

    dmac_ctl_reg.SRC_TR_WIDTH = BITS_32 ;
    dmac_ctl_reg.DST_TR_WIDTH = BITS_32 ;
    dmac_ctl_reg.SRC_MSIZE = DATA_ITEM_1 ;
    dmac_ctl_reg.DST_MSIZE = DATA_ITEM_1 ;

    //Set the GPDMA descriptor
    gpdma_set_descr (0, (uint32_t)(dest_addr)/*dest address*/, ((uint32_t)src_addr), block_size);
    RCS_DMAC_CFGREG_REG->value = 1;

    // Channel1 configuration.
    *RCS_DMAC_CH1_CFG_REG = dmac_cfg_reg;
    *RCS_DMAC_CH1_CTL_REG = dmac_ctl_reg;

    // Descr address.
    rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enable
    rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_DMAC_CHENREG_REG = chen_reg;

    // Wait till the transfer is done
    cnt = 0;
    do
    {
        rcs_dmac_ch1_intstat_reg = *(RCS_DMAC_CH1_INTSTAT_REG);
        cnt++;
    }while((0 == (rcs_dmac_ch1_intstat_reg.value & 0x1)) && (cnt < 512));

    if(cnt >= 512)
    {
        // Here means, the DMA transfer is not getting completed even after waiting for 512 cycles, so return FAILURE
        return -1;
    }

    return 0;
}

/**
 * function         gpdma_negative_test_LLI()
 * @brief           Function for negative testing: by configuring and initiating a DMA (Direct Memory Access) transfer using
 *                  a linked list item (LLI) on a specific DMA channel (Channel 1 in this case). It sets up the DMA transfer
 *                  parameters, starts the transfer, and then waits for the transfer to complete. It also waits for DMA INTSTAT
 *                  bit16 to set for indicating a DEC ERROR in case of access denied to the target.
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */

int gpdma_negative_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr)
{
    int cnt;
    volatile rcs_dmac_ch1_intstat_reg_t rcs_dmac_ch1_intstat_reg = {.value = RCS_DMAC_CH1_INTSTAT_DEFAULT};

    dmac_ctl_reg.SRC_TR_WIDTH = BITS_32;
    dmac_ctl_reg.DST_TR_WIDTH = BITS_32;
    dmac_ctl_reg.SRC_MSIZE = DATA_ITEM_1;
    dmac_ctl_reg.DST_MSIZE = DATA_ITEM_1;

    // Set the GPDMA descriptor
    gpdma_set_descr (0, (uint32_t)(dest_addr)/*dest address*/, ((uint32_t)src_addr), block_size);
    RCS_DMAC_CFGREG_REG->value = 1;

    // Channel1 configuration.
    *RCS_DMAC_CH1_CFG_REG = dmac_cfg_reg;
    *RCS_DMAC_CH1_CTL_REG = dmac_ctl_reg;

    // Descr address.
    rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enable
    rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_DMAC_CHENREG_REG = chen_reg;

    // Wait for the DMA INTSTAT bit16 to get set indicating a DEC ERROR
    cnt = 0;
    do
    {
        rcs_dmac_ch1_intstat_reg = *(RCS_DMAC_CH1_INTSTAT_REG);
        cnt++;
    }while(((rcs_dmac_ch1_intstat_reg.value & (1 << 16)) != (1 << 16)) && (cnt < 512));

    if(cnt >= 512)
    {
        // Here means, the DMA INTSTAT bit16 is not getting set even after waiting for 512 cycles, so return FAILURE
        return -1;
    }

    return 0;

 }
/**
 * function         com_shared_mem_wait_for_ready()
 * @brief           Waits for the shared memory to become ready.
 * @return          Returns true if the shared memory becomes ready within the timeout limit, otherwise returns false.
 */

bool com_shared_mem_wait_for_ready (void)
{
    int timeout_limit = RSM_LOOP_LIMIT;
    volatile rcs_gpreg_ext_irq_grp_reg_t *p_ext_irq_grp = RCS_GPREG_EXT_IRQ_GRP_REG;

    while (timeout_limit > 0)
    {
        if (p_ext_irq_grp->RCS_RSM_ZEROIZE_BUSY)
        {
            timeout_limit--;
        }
        else
        {
            volatile rcs_gpreg_rcs_cfg_reg_t gpreg_rcs_cfg = *RCS_GPREG_RCS_CFG_REG;
            gpreg_rcs_cfg.RCS_RSM_ZEROIZE = 0;
            *RCS_GPREG_RCS_CFG_REG = gpreg_rcs_cfg;
            return (true);
        }
    }
    return (false);
}


/**
 * function         drf_dma_set_descr()
 * @brief           Sets up a DRF DMA transfer descriptor. This function initializes and sets up a DRF DMA
 *                  (General Purpose Direct Memory Access transfer descriptor with the given parameters.
 *                  It zeroes out the descriptor structure,sets the source and destination addresses,
 *                  block transfer size, and control register value. It also marks the descriptor as the
 *                  last in a linked list and copies the descriptor settings to the descriptor buffer.
 * @param [in]      desc_idx, dst_addr, src_addr, block_size
 */

void drf_dma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr, uint32_t block_size)
{
    // The below  line declares a variable desc of type gpdma_desc_t,
    // which is presumably a structure that holds the details of a DMA transfer descriptor.
    drf_dma_desc_t desc;
    // The below line initializes the desc structure to zero.
    // It ensures that all fields in the descriptor are set to zero before setting specific fields.
    memset ((void *)&desc, 0, sizeof (drf_dma_desc_t));
    // The below  line sets the source address (least significant bits) in the descriptor to the value provided by src_addr
    desc.sar_lsb = src_addr;
    // The below  line sets the destination address (least significant bits) in the descriptor to the value provided by dst_addr
    desc.dar_lsb = dst_addr;
    // This  below line sets the block transfer size in the descriptor to the value provided by block_size.
    desc.block_ts = block_size;
    // This line sets the control register value in the descriptor to a value dmac_ctl_reg
    desc.drf_ctl = drf_dmac_ctl_reg;
    // This line sets a specific field within the control register,
    // this descriptor is the last in a linked list or that it should use shadow registers
    desc.drf_ctl.SHADOWREG_OR_LLI_LAST = 1;
    // This line copies the contents of the desc structure into another memory location, presumably a buffer called descr_buffer.
    // This buffer might be an array or a memory-mapped register that the DMA controller uses to read the descriptor settings.
    memcpy ((void*)&drf_descr_buffer, &desc, sizeof (drf_dma_desc_t));
    memcpy ((void*)MEM_FB0_DESC_BASE, &desc, sizeof (drf_dma_desc_t));
}

/**
 * function         drf_dma_test_LLI()
 * @brief           Function for configuring and initiating a DMA (Direct Memory Access) transfer using a linked list item
 *                  (LLI) on a specific DMA channel (Channel 1 in this case). It sets up the DMA transfer parameters, starts
 *                  the transfer, and then waits for the transfer to complete.
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */

int drf_dma_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr)
{
    int cnt;
    volatile mem_fb_dmac_ch1_intstat_reg_t mem_fb_dmac_ch1_intstat_reg = {.value = MEM_FB_DMAC_CH1_INTSTAT_DEFAULT};

    drf_dmac_ctl_reg.SRC_TR_WIDTH = BITS_8;
    drf_dmac_ctl_reg.DST_TR_WIDTH = BITS_8;
    drf_dmac_ctl_reg.SRC_MSIZE = DATA_ITEM_1;
    drf_dmac_ctl_reg.DST_MSIZE = DATA_ITEM_1;

    drf_dma_set_descr (0, (uint32_t)(dest_addr), ((uint32_t)src_addr), block_size);
    MEM_FB_DMAC_CFGREG_REG(MEM_FB0_DMAC_0_BASE)->value = 1;

    // Channel 1 configuration.
    *MEM_FB_DMAC_CH1_CFG_REG(MEM_FB0_DMAC_0_BASE) = drf_dmac_cfg_reg;
    *MEM_FB_DMAC_CH1_CTL_REG(MEM_FB0_DMAC_0_BASE) = drf_dmac_ctl_reg;

    // Descr address.
    mem_fb_dmac_ch1_llp_reg_t drf_llp_reg = {.value = (uint64_t)0x110000};
    *MEM_FB_DMAC_CH1_LLP_REG(MEM_FB0_DMAC_0_BASE) = drf_llp_reg;

    // Channel 1 enable
    mem_fb_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *MEM_FB_DMAC_CHENREG_REG(MEM_FB0_DMAC_0_BASE) = chen_reg;

    // Wait till the transfer is done
    cnt = 0;
    do
    {
        mem_fb_dmac_ch1_intstat_reg = *(MEM_FB_DMAC_CH1_INTSTAT_REG(MEM_FB0_DMAC_0_BASE));
        cnt++;
    }while((0 == (mem_fb_dmac_ch1_intstat_reg.value & 0x1)) && (cnt < 512));

    if(cnt >= 512)
    {
        // Here means, the DMA transfer is not getting completed even after waiting for 512 cycles, so return FAILURE
        return -1;
    }

    return 0;
}

/**
 * function         drf_dma_negative_test_LLI()
 * @brief           Function for negative testing: by configuring and initiating a DMA (Direct Memory Access) transfer using
 *                  a linked list item (LLI) on a specific DMA channel (Channel 1 in this case). It sets up the DMA transfer
 *                  parameters, starts the transfer, and then waits for the transfer to complete. It also waits for DMA INTSTAT
 *                  bit16 to set for indicating a DEC ERROR in case of access denied to the target.
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */

int drf_dma_negative_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr)
{
    int cnt;
    volatile mem_fb_dmac_ch1_intstat_reg_t mem_fb_dmac_ch1_intstat_reg = {.value = MEM_FB_DMAC_CH1_INTSTAT_DEFAULT};

    drf_dmac_ctl_reg.SRC_TR_WIDTH = BITS_8;
    drf_dmac_ctl_reg.DST_TR_WIDTH = BITS_8;
    drf_dmac_ctl_reg.SRC_MSIZE = DATA_ITEM_1;
    drf_dmac_ctl_reg.DST_MSIZE = DATA_ITEM_1;

    drf_dma_set_descr (0, (uint32_t)(dest_addr), ((uint32_t)src_addr), block_size);
    MEM_FB_DMAC_CFGREG_REG(MEM_FB0_DMAC_0_BASE)->value = 1;

    // Channel 1 configuration.
    *MEM_FB_DMAC_CH1_CFG_REG(MEM_FB0_DMAC_0_BASE) = drf_dmac_cfg_reg;
    *MEM_FB_DMAC_CH1_CTL_REG(MEM_FB0_DMAC_0_BASE) = drf_dmac_ctl_reg;

    // Descr address.
    mem_fb_dmac_ch1_llp_reg_t drf_llp_reg = {.value = (uint64_t)0x110000};
    *MEM_FB_DMAC_CH1_LLP_REG(MEM_FB0_DMAC_0_BASE) = drf_llp_reg;

    // Channel 1 enable
    mem_fb_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *MEM_FB_DMAC_CHENREG_REG(MEM_FB0_DMAC_0_BASE) = chen_reg;

    // Wait for the DMA INTSTAT bit16 to get set indicating a DEC ERROR
    cnt = 0;
    do
    {
        mem_fb_dmac_ch1_intstat_reg = *(MEM_FB_DMAC_CH1_INTSTAT_REG(MEM_FB0_DMAC_0_BASE));
        cnt++;
    }while((0 == (mem_fb_dmac_ch1_intstat_reg.value & (1 << 16)) != (1 << 16)) && (cnt < 512));

    if(cnt >= 512)
    {
        // Here means, the DMA INTSTAT bit16 is not getting set even after waiting for 512 cycles, so return FAILURE
        return -1;
    }

    return 0;
 }
