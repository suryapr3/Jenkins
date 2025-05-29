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
	//rcs_dmac_ch2_ctl_reg_t ctl_ch2;
	uint32_t wb_lsb;
	uint32_t wb_msb;
	uint32_t llp_stat_lsb;
	uint32_t llp_stat_msb;
	uint32_t res38;
	uint32_t res3c;
} gpdma_desc_t;



rcs_dmac_ch1_ctl_reg_t dmac_ch1_ctl_reg = {
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
rcs_dmac_ch2_ctl_reg_t dmac_ch2_ctl_reg = {
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
rcs_dmac_ch1_cfg_reg_t dmac_ch1_cfg_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
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
rcs_dmac_ch2_cfg_reg_t dmac_ch2_cfg_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
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
uint32_t gpdma_test_rcs2vex_crux();
int gpdma_combinations_test();
int gpdma_vex_vmem_config();
int gpdma_test();
uint32_t gpdma_vex2rcs_crux_test(int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
uint32_t gpdma_test_vex2rcs_axi(int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
uint32_t gpdma_test_rcs2vex_axi(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
uint32_t rcs2vex_transfer_test(int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
int gpdma_test_shadow_mode(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
int gpdma_test_LLI(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
int gpdma_test_single_block(int dmac_channe,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width);
volatile unsigned long int* gpdma_status_reg_2 = (unsigned long int*) 0x270010 ;
volatile unsigned long int* gpdma_ctl_reg = (unsigned long int*) 0x270118 ;
volatile unsigned long int* gpdma_ctl_reg1 = (unsigned long int*) 0x27011c ;
volatile unsigned long int* gpdma_cfg_reg = (unsigned long int*) 0x270120 ;
volatile unsigned long int* gpdma_cfg_reg1 = (unsigned long int*) 0x270124 ;
volatile unsigned long int* rsm_soft_reset = (unsigned long int*) 0x26c02c ;
volatile unsigned long int* ch1_block_ts = (unsigned long int*) 0x270110 ;
volatile unsigned long int* src_adrss = (unsigned long int*) 0x270100 ;
volatile unsigned long int* dst_adrss = (unsigned long int*) 0x270108 ;
volatile unsigned long int* reg_strm2cio_fifo_status_ctl= (unsigned long int*) 0x0280C010; 
volatile unsigned long int* reg_strm2cio_word_cnt_ctl= (unsigned long int*) 0x0280C020; 
volatile unsigned long int* gpdma_chen_reg = (unsigned long int*) 0x270018 ;
volatile unsigned long int* gpdma_status_reg = (unsigned long int*) 0x270188 ;
volatile unsigned long int* gpdma_intclear_reg = (unsigned long int*) 0x270198 ;
volatile unsigned long int* gpdma_intstatus_ch2_reg = (unsigned long int*) 0x270288 ;
volatile unsigned long int* gpdma_intclear_ch2_reg = (unsigned long int*) 0x270298 ;
volatile unsigned long int* rcs_config_reg = (unsigned long int*) 0x26c004 ;
