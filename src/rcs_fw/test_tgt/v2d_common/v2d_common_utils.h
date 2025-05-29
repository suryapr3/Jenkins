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
 * @file    bfn_test.h
 * @brief   Trigger the delayed start of for the Ch0 of given quad along with start the corresponding vex cores.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#ifndef __V2D_COMMON_UTIL_H__
#define __V2D_COMMON_UTIL_H__

#include "com_definitions.h"
#include "com_event.h"
#include "com_shared_memory.h"
#include "rcs_gpreg.h"

#include "bfn_csr.h"
#include "av2d_csr.h"
#include "nsip_hbi.h"
#include "ve32_bp_cfg_dmem.h"
#include "av2d_axi4.h"
#include "ve32_cell.h"
#include "rcs_timer_gpreg.h"
#include "sram.h"
#include "timerx8.h"
#include "mem_fb.h"
#include "rcs_dmac.h"

#include "v2d_host_rcs_common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
// BFN related Macros
#define FOLLOWER_INCREMENT_CMD     0x00000003
#define FOLLOWER_NORMAL_CMD        0x00000000
#define BFN_COM_ISYNC_CLEAR        0x00000000
#define BFN_COM_ISYNC_TRIG         0x00000080
#define BFN_COM_ISYNC_LOAD         0x00000100
#define BFN_COM_ISYNC_READ         0x00000000
#define BFN_COM_ISYNC_VAL_DEF      0x00000000
#define BFN_COM_ISYNC_VAL_INC      0x00000010
#define BFN_COM_ISYNC_VAL_DEC      0x00000020
#define BFN_COM_ISYNC_VAL_CMD      0x00000030
#define BFN_COM_ISYNC_CMD_INC_LCNT 0x00000000
#define BFN_COM_ISYNC_CMD_INIT     0x00000002
#define BFN_COM_ISYNC_CMD_PRESET   0x00000001
#define BFN_COM_ISYNC_CMD_RESET    0x00000003
#define BFN_COM_ISYNC_CMD_INC_PRE  0x00000003
#define BFN_COM_ISYNC_CMD_ADJ      0x00000005
#define BFN_COM_ISYNC_CMD_CAP      0x00000007
#define BFN_COM_ISYNC_CMD          (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_CMD)   // 0x000000B0
#define BFN_COM_SYNC_PRESET        (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_PRESET) // 0x000000B1
#define BFN_COM_SYNC_INIT          (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_INIT)   // 0x000000B2
#define BFN_COM_SYNC_RESET         (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_RESET)  // 0x000000B3
#define BFN_COM_SYNC_CAP           (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_CAP)    // 0x000000B7
#define BFN_COM_SYNC_INC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_INC)   // 0x00000090
#define BFN_COM_SYNC_DEC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_DEC)   // 0x000000A0
#define TIMESYNC_CTRL   0x00030031

#define V2D_PER_QUAD    2
#define VEX_PER_V2D     4
#define QUAD_PER_ABC    4

#define VEX_BASE(vex_num)   VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE))
#define V2D_BFN_BASE(v2d_num)    (V2D0_BFN_CSR_BASE + (v2d_num) * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE))
#define V2D_CH0_NSIP0_BASE(v2d_num)         (V2D0_AV2D_APB_0_NSIP_HBI_0_BASE + ((v2d_num) * (V2D1_AV2D_APB_0_NSIP_HBI_0_BASE - V2D0_AV2D_APB_0_NSIP_HBI_0_BASE)))
#define V2D_CH0_NSIP1_BASE(v2d_num)         (V2D0_AV2D_APB_0_NSIP_HBI_1_BASE + ((v2d_num) * (V2D1_AV2D_APB_0_NSIP_HBI_1_BASE - V2D0_AV2D_APB_0_NSIP_HBI_1_BASE)))
#define V2D_CH0_CSR_BASE(v2d_num)           (V2D0_AV2D_APB_0_CSR_BASE + ((v2d_num) * (V2D1_AV2D_APB_0_CSR_BASE - V2D0_AV2D_APB_0_CSR_BASE)))
#define V2D_AXI_BASE(v2d_num, apb_num)      ((V2D0_AV2D_AXI4_0_BASE + ((v2d_num) * (V2D1_AV2D_AXI4_0_BASE - V2D0_AV2D_AXI4_0_BASE))) + APB_OFFSET(apb_num))
#define APB_OFFSET(apb_num)                 (apb_num * (V2D0_AV2D_APB_1_CSR_BASE - V2D0_AV2D_APB_0_CSR_BASE))
#define SAMPLES_TO_V2D_CAP_SIZE(samples)    (samples / 8)

#define CYCLES_PER_BLOCK_1P5G          (768)
#define CYCLES_PER_BLOCK_983M          (512)

#define TEN_MS_CNT_VALUE_1P5      (0xE0FFFF)

#define NUM_OF_ELEMENTS_PER_VEC (32)
#define BITS_128_PER_VEC        (8)
/*241 flits and each flit is of 16 words*/
#define LUT_MEM_SIZE            (241 * 16)
/*This size should be in 256 bits or 32 bytes, 0 = 1 256 bit entry*/
#define SAMPLES_TO_FB_MEM_SIZE(num_samples) (((num_samples) * 4) / 32)

extern const int g_v2d_instance_in_quad[QUAD_PER_ABC][V2D_PER_QUAD];
extern const int g_vex_instance_in_v2d[][VEX_PER_V2D];
extern const int g_samples_per_blk[2][5];
extern volatile uint32_t dram_buff[32];

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef enum
{
    BFN_EVENT_MODE_SINGLE = 0,
    BFN_EVENT_MODE_DOUBLE,
    BFN_EVENT_MODE_REPEAT
}bfn_event_mode_t;

typedef enum
{
    BFN_EVENT_OUTPUT_MODE_TOGGLE = 0,
    BFN_EVENT_OUTPUT_MODE_PULSE
}bfn_event_output_mode_t;

typedef enum
{
    e_V2D_HIGH_INTERRUPT = 48,
    e_V2D_LOW_INTERRUPT = 272
}e_v2d_irq_t;

typedef struct fb_mem_compare_param
{
    int *ref_pattern;
    int add_factor;
    int skip_cycles;
    int num_captures;
    int capture_start_value;
    int v2d_num;    /*To get the ping and pong addresses*/
    int capture_blocks;
    int clks_per_blk;
    int capture_delay_value;
    int samples_per_block;
}fb_mem_compare_t;

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

extern rcs_dmac_ch1_ctl_reg_t dmac_ctl_reg;
extern rcs_dmac_ch2_ctl_reg_t dmac_ctl2_reg;
extern rcs_dmac_ch1_cfg_reg_t dmac_cfg_reg;
extern rcs_dmac_ch2_cfg_reg_t dmac_cfg2_reg;
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
void quad_configure_v2d_bfn(int quad_instance, int capture_enable, int size, int match_value);
void quad_bfn_sync_ver(int quad_instance, int drf_clock);
void quad_v2d_bfn_capture(int quad_instance);
void configure_v2d_bfn(int v2d_num, int apb_num, int capture_enable, int size, int match_value);
int get_quad_instance(int v2d_num);
void configure_v2d_bfn_config(int v2d_num, int reg_instance, bfn_event_output_mode_t output_mode, bfn_event_mode_t event_mode);
void configure_v2d_bfn_incr(int v2d_num, int reg_instance, int value);
void quad_configure_v2d_bfn_config(int quad_instance, int reg_instance, bfn_event_output_mode_t output_mode, bfn_event_mode_t event_mode);
void quad_configure_v2d_bfn_incr(int quad_instance, int reg_instance, int value);
void generate_ref_block(int *ref_pattern, int samples_per_block);
int mem_fb_compare_repeat(fb_mem_compare_t *fb_mem_compare);
int quad_mem_fb_compare_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_param);
int get_current_time(int v2d_num);
int x_capture_compare(int *start_address, int *ref_pattern, int samples, int add_val);
void configure_v2d_cap_mode_ctrl(int v2d_num, int on_off_mode_en, int continuous_mode_en, int off_set_count, int on_set_count);
int quad_mem_fb_compare_2_ch_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_param);
int quad_mem_fb_compare_3_ch_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_params);
int rcs_gpdma_test_LLI(
        uint32_t descr_buffer,
        int block_size,
        m_size_value_t src_msize,
        m_size_value_t dst_msize,
        tr_width_value_t src_tr_width,
        tr_width_value_t dst_tr_width,
        int src_addr,
        int dest_addr);
void rcs_gpdma_set_descr(uint32_t descr_address, int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size);
#endif
