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
#ifndef ASC_WRAP_H
#define ASC_WRAP_H

#include "asc.h"

#define ASC_SLICE_TOTAL   ASC_SLICE_W_ARR_SZ0
#define ASC_SLICE_W_TOTAL ASC_SLICE_W_ARR_SZ1
#define ASC_ANT_FB_TOTAL  5

typedef struct
{
    asc_slice_w_lut_reg_t W_LUT[32];
    asc_slice_w_reg_t W[ASC_SLICE_W_TOTAL];
    asc_slice_c_reg_t C;
    const uint8_t reserved[52];
} asc_slice_t;

typedef struct
{
    asc_slice_t SLICE[ASC_SLICE_TOTAL];        /*< Address offset = 0x0 */
    asc_xtalk_m1_shdw_reg_t XTALK_M1_SHDW[16]; /*< Address offset = 0x900 */
    asc_xtalk_n0_shdw_reg_t XTALK_N0_SHDW[16]; /*< Address offset = 0x940 */
    asc_xtalk_p1_shdw_reg_t XTALK_P1_SHDW[16]; /*< Address offset = 0x980 */
    const uint8_t reservedArea17[64];          /*< Address offset = 0x9c0 */
    asc_xtalk_m1_live_reg_t XTALK_M1_LIVE[16]; /*< Address offset = 0xa00 */
    asc_xtalk_n0_live_reg_t XTALK_N0_LIVE[16]; /*< Address offset = 0xa40 */
    asc_xtalk_p1_live_reg_t XTALK_P1_LIVE[16]; /*< Address offset = 0xa80 */
    const uint8_t reservedArea18[64];          /*< Address offset = 0xac0 */
    asc_scratch_reg_t SCRATCH;                 /*< Address offset = 0xb00 */
    asc_cfg_reg_t CFG;                         /*< Address offset = 0xb04 */
    asc_ctrl_reg_t CTRL;                       /*< Address offset = 0xb08 */
    asc_csr_cfg_reg_t CSR_CFG;                 /*< Address offset = 0xb0c */
    asc_csr_err_reg_t CSR_ERR;                 /*< Address offset = 0xb10 */
    asc_apb_brdg_stat_reg_t APB_BRDG_STAT;     /*< Address offset = 0xb14 */
    const uint8_t reservedArea19[40];          /*< Address offset = 0xb18 */
    asc_int_stat_reg_t INT_STAT;               /*< Address offset = 0xb40 */
    asc_int_high_en_reg_t INT_HIGH_EN;         /*< Address offset = 0xb44 */
    asc_int_low_en_reg_t INT_LOW_EN;           /*< Address offset = 0xb48 */
    asc_int_clr_reg_t INT_CLR;                 /*< Address offset = 0xb4c */
    asc_int_force_reg_t INT_FORCE;             /*< Address offset = 0xb50 */
} asc_wrap_t;                                  // size: 0x00cc

typedef struct
{
    asc_wrap_t *ant[ASC_ANT_FB_TOTAL];
} asc_quad_ant_t;

/*
#define ASC_MAKE_SLICES(ASC_NUM) \
    {(asc_wrap_t *)ANT0_ASC##ASC_NUM##_BASE, \
     (asc_wrap_t *)ANT1_ASC##ASC_NUM##_BASE, \
     (asc_wrap_t *)ANT2_ASC##ASC_NUM##_BASE, \
     (asc_wrap_t *)ANT3_ASC##ASC_NUM##_BASE, \
     (asc_wrap_t *)ANT##ASC_NUM##_ASC_FB_BASE}

#define ASC_QUAD_TOTAL 4
asc_quad_ant_t asc_quad_ant[ASC_QUAD_TOTAL] = {
    [0] = ASC_MAKE_SLICES(0),
    [1] = ASC_MAKE_SLICES(1),
    [2] = ASC_MAKE_SLICES(2),
    [3] = ASC_MAKE_SLICES(3)
};

for (int idx_quad=0; idx_quad<ASC_QUAD_TOTAL; idx_quad++) // loop all quad
{
    for (int idx_ant=0; idx_ant<ASC_ANT_FB_TOTAL; idx_ant++) // loop all ant, 4 + 1
    {
        for (int idx_slice=0; idx_slice<ASC_SLICE_TOTAL; idx_slice++) // loop all slice
        {
            asc_quad_ant[idx_quad].ant[idx_ant]->SLICE[idx_slice].C.value = 123;
            for (int idx_slice_w=0; idx_slice_w<ASC_SLICE_W_TOTAL; idx_slice_w++) // loop all slice_w
            {
                // Sample code
                // asc_quad_ant[idx_quad].ant[idx_ant]->SLICE[idx_slice].W[idx_slice_w].value = 456;
            }
        }
    }
}
*/

#endif // ASC_WRAP_H
