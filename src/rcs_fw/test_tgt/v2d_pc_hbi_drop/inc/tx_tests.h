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
 * @file    tx_tests.h
 * @brief   Header configuration for RCS code.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#include "rcs_dmac.h"

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
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
    rcs_dmac_ch1_ctl_reg_t ctl;
    uint32_t wb_lsb;
    uint32_t wb_msb;
    uint32_t llp_stat_lsb;
    uint32_t llp_stat_msb;
    uint32_t res38;
    uint32_t res3c;
} gpdma_desc_t;

rcs_dmac_ch1_ctl_reg_t dmac_ctl_reg = {
    .SRC_TR_WIDTH = 4,//2,//1,//4, // 128 bit.
    .DST_TR_WIDTH = 4,//2,//1,//4,
    .SHADOWREG_OR_LLI_VALID = 1	, // valid.
    .SRC_MSIZE = 4,              // 4x128 burst.
    .DST_MSIZE = 4,
    .ARLEN_EN = 1, // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1, // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR=1,
    .DST_STAT_EN=1,
    .SRC_STAT_EN=1,
    .NONPOSTED_LASTWRITE_EN=0,
};
rcs_dmac_ch2_ctl_reg_t dmac_ctl2_reg = {
    .SRC_TR_WIDTH = 4,//2,//1,//4, // 128 bit.
    .DST_TR_WIDTH = 4,//2,//1,//4,
    .SHADOWREG_OR_LLI_VALID = 1	, // valid.
    .SRC_MSIZE = 4,              // 4x128 burst.
    .DST_MSIZE = 4,
    .ARLEN_EN = 1, // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1, // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR=1,
    .DST_STAT_EN=1,
    .SRC_STAT_EN=1,
    .NONPOSTED_LASTWRITE_EN=0,
};
rcs_dmac_ch1_cfg_reg_t dmac_cfg_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
    .DST_MULTBLK_TYPE = 3, // LLI
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,        // Flow control select: M2M
    .HS_SEL_SRC = 0,   // SW handshake
    .HS_SEL_DST = 1,   //
    .SRC_HWHS_POL = 0, // HS polarity
    .DST_HWHS_POL = 0, //
    .SRC_PER = 1,      // HS interface sel
    .DST_PER = 1,
    .CH_PRIOR = 0x7,    // Prio (don't care).
    .LOCK_CH = 0,     // Keep channel (don't care).
    .LOCK_CH_L = 1,   // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF, // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};
rcs_dmac_ch2_cfg_reg_t dmac_cfg2_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
    .DST_MULTBLK_TYPE = 3, // LLI
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,        // Flow control select: M2M
    .HS_SEL_SRC = 0,   // SW handshake
    .HS_SEL_DST = 1,   //
    .SRC_HWHS_POL = 0, // HS polarity
    .DST_HWHS_POL = 0, //
    .SRC_PER = 1,      // HS interface sel
    .DST_PER = 1,
    .CH_PRIOR = 0x7,    // Prio (don't care).
    .LOCK_CH = 0,     // Keep channel (don't care).
    .LOCK_CH_L = 1,   // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF, // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};

typedef enum {
    DATA_ITEM_1 = 0,
    DATA_ITEMS_4,
    DATA_ITEMS_8,
    DATA_ITEMS_16,
    DATA_ITEMS_32,
    DATA_ITEMS_64,
    DATA_ITEMS_128,
    DATA_ITEMS_256,
    DATA_ITEMS_512,
    DATA_ITEMS_1024
}m_size_value_t;

typedef enum {
    BITS_8 = 0,
    BITS_16,
    BITS_32,
    BITS_64,
    BITS_128,
    BITS_256
} tr_width_value_t;

int gpdma_test_LLI(int block_size, m_size_value_t src_msize, m_size_value_t dst_msize,tr_width_value_t src_tr_width,tr_width_value_t dst_tr_width, int addr, uint32_t dest_offset);

