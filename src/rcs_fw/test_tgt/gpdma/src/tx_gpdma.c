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
 * @file    tx_lock.c
 * @brief   lock test file on TX core
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "rcs_axi_dmac.h"
#include "string.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

typedef struct
{
    uint32_t sar_lsb;
    uint32_t sar_msb;
    uint32_t dar_lsb;
    uint32_t dar_msb;
    uint32_t block_ts;
    uint32_t res14;
    uint32_t llp_lsb;
    uint32_t llp_msb;
    rcs_axi_dmac_ch1_ctl_reg_t ctl;
    uint32_t wb_lsb;
    uint32_t wb_msb;
    uint32_t llp_stat_lsb;
    uint32_t llp_stat_msb;
    uint32_t res38;
    uint32_t res3c;
} gpdma_desc_t;

uint32_t __attribute__ ((section (".sram.reserved"))) x_source_buffer[8192]; // 8k samples.
uint32_t __attribute__ ((section (".sram.reserved"))) y_source_buffer[8192]; // 8k samples.
uint32_t __attribute__ ((section (".sram.reserved"))) x_dest_buffer[2048];   // 2k samples.
uint32_t __attribute__ ((section (".sram.reserved"))) y_dest_buffer[2048];   // 2k samples.
gpdma_desc_t __attribute__ ((section (".sram.reserved"))) descr_buffer[8];

rcs_axi_dmac_ch1_ctl_reg_t dmac_ctl_reg = {
    .SRC_TR_WIDTH = 4, // 128 bit.
    .DST_TR_WIDTH = 4,
    .SHADOWREG_OR_LLI_VALID = 1, // valid.
    .SRC_MSIZE = 1,              // 4x128 burst.
    .DST_MSIZE = 1,
    .ARLEN_EN = 0, // hw choose burst.
    .ARLEN = 0,
    .AWLEN_EN = 0, // hw choose burst.
    .AWLEN = 0,
};

#define GPDMA_CTL_LSB      ((4 << 8) | (4 << 11))  // 128-bit xfer.
#define GPDMA_CTL_MSB_LAST ((1 << 31) | (1 << 30)) // valid/Last descriptor.
#define GPDMA_CTL_MSB      (1 << 31)               // valid
#define GPDMA_BLOCK_TS     511                     // 512 * 128b = 2k samples.

rcs_axi_dmac_ch1_cfg_reg_t dmac_cfg_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
                                           .DST_MULTBLK_TYPE = 3, // LLI
                                           .RD_UID = 0,
                                           .WR_UID = 0,
                                           .TT_FC = 0,        // Flow control select: M2M
                                           .HS_SEL_SRC = 1,   // SW handshake
                                           .HS_SEL_DST = 1,   //
                                           .SRC_HWHS_POL = 0, // HS polarity
                                           .DST_HWHS_POL = 0, //
                                           .SRC_PER = 0,      // HS interface sel
                                           .DST_PER = 0,
                                           .CH_PRIOR = 0,    // Prio (don't care).
                                           .LOCK_CH = 0,     // Keep channel (don't care).
                                           .LOCK_CH_L = 0,   // Keep channel duration (don't care).
                                           .SRC_OSR_LMT = 0, // Outstanding transaction limit
                                           .DST_OSR_LMT = 0};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr)
{
    gpdma_desc_t desc;

    memset ((void *)&desc, 0, sizeof (gpdma_desc_t));

    desc.sar_lsb = src_addr;
    desc.dar_lsb = dst_addr;
    desc.block_ts = GPDMA_BLOCK_TS;
    desc.ctl = dmac_ctl_reg;
    if (desc_idx == 7)
        desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    desc.llp_lsb = (uint32_t)&descr_buffer[desc_idx + 1];

    memcpy (&descr_buffer[desc_idx], &desc, sizeof (gpdma_desc_t));
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    if (!com_shared_mem_wait_for_ready ())
        FW_PRINT (FW_WARN, "RSM Not ready.");
    com_shared_mem_set_cpu_status (E_CPUID_TX0, E_CPU_STATUS_MAIN);

    for (int i = 0; i < 4; i++)
    {
        gpdma_set_descr ((i * 2), (uint32_t)x_dest_buffer, ((uint32_t)x_source_buffer) + (2048 * i));
        gpdma_set_descr ((i * 2) + 1, (uint32_t)y_dest_buffer, ((uint32_t)y_source_buffer) + (2048 * i));
    }

    for (int i = 0; i < 8192; i++)
    {
        x_source_buffer[i] = 0x0F0F0000 | i;
        y_source_buffer[i] = 0x5A5A0000 | i;
    }
    x_dest_buffer[2047] = 0x11111111;
    y_dest_buffer[2047] = 0x22222222;

    FW_PRINT (FW_INFO, "INITIAL BUFFER VALUES: X=%x  Y=%x", x_dest_buffer[2047], y_dest_buffer[2047]);

    // Main DMAC Enable.
    RCS_AXI_DMAC_CFGREG_REG->value = 1;

    // Channel configuration.
    *RCS_AXI_DMAC_CH1_CFG_REG = dmac_cfg_reg;

    // Descr address.
    rcs_axi_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_AXI_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enable.
    rcs_axi_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_AXI_DMAC_CHENREG_REG = chen_reg;

    com_timing_wait_ns (50000);
    FW_PRINT (FW_INFO, "FINAL BUFFER VALUES: X=%x  Y=%x", x_dest_buffer[2047], y_dest_buffer[2047]);

    return (0);
}
