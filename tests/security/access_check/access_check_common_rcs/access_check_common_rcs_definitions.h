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
#ifndef ACCESS_CHECK_COMMON_RCS_DEFINITIONS_H
#define ACCESS_CHECK_COMMON_RCS_DEFINITIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "com_definitions.h"
#include "all_comps.h"
#include "common_macro.h"
#include "rcs_timer_gpreg.h"
#include "rcs_gpreg.h"
#include "com_event.h"
#include "rcs_dmac.h"
#include "noc.h"
#include "noc_orion.h"

#define SUCCESS                        ( 0 )
#define FAILURE                        ( -1 )
#define ACCESS_ALLOWED                 ( 1 )
#define ACCESS_NOT_ALLOWED             ( 0 )
// About 32us
#define RSM_LOOP_LIMIT                 ( 500 )


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
    mem_fb_dmac_ch1_ctl_reg_t drf_ctl;
    uint32_t wb_lsb;
    uint32_t wb_msb;
    uint32_t llp_stat_lsb;
    uint32_t llp_stat_msb;
    uint32_t res38;
    uint32_t res3c;
} drf_dma_desc_t;

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

// Function prototypes
bool com_shared_mem_wait_for_ready(void);
void gpdma_set_descr(int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size);
int gpdma_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr);
int gpdma_negative_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr);
void drf_dma_set_descr(int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size);
int drf_dma_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr);
int drf_dma_negative_test_LLI(int block_size, uint32_t dest_addr, uint32_t src_addr);


#endif
