/* INTEL CONFIDENTIAL
 *
 * Copyright  2023 Intel Corporation All Rights Reserved.
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
#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "tx_daco.h"
#include "com_assert.h"
#include "com_print.h"
#include "com_swg.h"

#include "tx_lineup.h"
#include "tx_v2d.h"

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

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
// TODO: below functions should be defined in its corresponding modules
static void fb_ant_cfg_seq (volatile fb_ant_t *const p_fb_ant, uint8_t ant_mask_in_drf)
{
    ;
}
static void fb_sys_cfg_seq (volatile fb_sys_t *const p_fb_sys, uint8_t ant_mask_in_drf)
{
    ;
}
static void mem_cap_cfg_seq (volatile mem_cap_t *const p_mem_cap, uint8_t ant_mask_in_drf)
{
    ;
}
static void mem_fb_cap_cfg_seq (volatile mem_fb_cap_t *const p_mem_fb_cap, uint8_t ant_mask_in_drf)
{
    ;
}
static void tx_ana_init_seq (volatile drf_ant_blk_t *p_drf_ant, uint8_t const strm)
{
    ;
}
static void trx_ant_cfg_seq (const quad_params_t *const p_quad_params, volatile trx_ant_t *const p_trx_ant, uint8_t const chnl_idx)
{
    ;
}
static void trx_sys_cfg_seq (const quad_params_t *const p_quad_params, volatile trx_sys_t *const p_trx_sys, uint8_t const chnl_idx)
{
    ;
}
static void tx_vha_cfg_seq (const quad_params_t *const p_quad_params, volatile vha_hw_t *const p_vha, uint8_t const chnl_idx)
{
    ;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           TX lineup configuration
 * @param [in]      ant_mask: 16-bit mask specifying which ANTs to use
 * @return          none
 */
void tx_lineup_cfg (uint16_t ant_mask)
{
    uint8_t drf_idx = 0;
    // go over each DRF
    while (ant_mask)
    {
        tx_drf_cfg (drf_idx, ant_mask & ((1 << NUM_ANT_PER_DRF) - 1));

        ant_mask >>= NUM_ANT_PER_DRF; // next DRF
        drf_idx++;
    }
}

/**
 * @brief           TX lineup DRF level configuration
 * @param [in]      drf_idx: DRF index to indicate which DRF (east/west) to use
 * @param [in]      ant_mask_in_drf: 8-bit mask specifying whcih ANTs (local) to use in one DRF
 * @return          none
 */
void tx_drf_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf)
{
    if (ant_mask_in_drf)
    {
        volatile fb_ant_t *const p_fb_ant = &tx_daco.hw.fb_ant[drf_idx];
        volatile fb_sys_t *const p_fb_sys = &tx_daco.hw.fb_sys[drf_idx];
        volatile mem_cap_t *const p_mem_cap = &tx_daco.hw.mem_cap[drf_idx];
        volatile mem_fb_cap_t *const p_mem_fb_cap = &tx_daco.hw.mem_fb_cap[drf_idx];

        fb_ant_swg_cfg (drf_idx, ant_mask_in_drf);
        com_sys_swg_cfg (drf_idx, ant_mask_in_drf);

        fb_ant_cfg_seq (p_fb_ant, ant_mask_in_drf);
        fb_sys_cfg_seq (p_fb_sys, ant_mask_in_drf);
        mem_cap_cfg_seq (p_mem_cap, ant_mask_in_drf);
        mem_fb_cap_cfg_seq (p_mem_fb_cap, ant_mask_in_drf);

        uint8_t quad_idx = drf_idx * NUM_QUAD_PER_DRF;
        // go over each QUAD in this DRF
        while (ant_mask_in_drf)
        {
            tx_quad_cfg (quad_idx, ant_mask_in_drf & ((1 << NUM_STRM_PER_QUAD) - 1));

            ant_mask_in_drf >>= NUM_STRM_PER_QUAD; // next quad in one DRF
            quad_idx++;
        }
    }
}

/**
 * @brief           TX lineup QUAD level configuration
 * @param [in]      quad_idx: QUADS index to indicate which QUAD (0 to 3) to use
 * @param [in]      ant_mask_in_quad: 4-bit (LSB) mask specifying whcih ANTs (local) to use in one QUAD
 * @return          none
 */
void tx_quad_cfg (uint8_t const quad_idx, uint8_t ant_mask_in_quad)
{

    if (ant_mask_in_quad)
    {
        drf_ant_cfg_seq (quad_idx, ant_mask_in_quad);

        uint8_t g_idx = quad_idx * NUM_GRP_PER_QUAD;
        // go over each GROUP in this QUAD
        while (ant_mask_in_quad)
        {
            tx_grp_cfg (g_idx, ant_mask_in_quad & ((1 << NUM_CHNL_PER_GRP) - 1));

            ant_mask_in_quad >>= NUM_CHNL_PER_GRP; // next GROUP in one QUAD
            g_idx++;
        }
    }
}

/**
 * @brief           DRF ANT block GROUP level configuration
 * @param [in]      quad_idx: QUADS index to indicate which QUAD (0 to 3) to use
 * @param [in]      ant_mask_in_quad: 4-bit (LSB) mask specifying whcih ANTs (local) to use in one QUAD
 * @return          none
 */
void drf_ant_cfg_seq (uint8_t const quad_idx, uint8_t ant_mask_in_quad)
{
    const quad_params_t *const p_quad_params = &tx_daco.quad_params[quad_idx];
    volatile drf_ant_blk_t *p_drf_ant = &tx_daco.hw.drf_ant[quad_idx];

    uint8_t strm = 0;
    while (ant_mask_in_quad & 1)
    {
        tx_ana_init_seq (p_drf_ant, strm); // TX Initial Configuration Sequence

        ant_mask_in_quad >>= 1;
        strm++;
    }
}

/**
 * @brief           TX lineup GROUP level configuration
 * @param [in]      grp_idx: GROUP index to indicate which GROUP (0 to 7) to use
 * @param [in]      ant_mask_in_grp: 2-bit (LSB) mask specifying whcih ANTs (local) to use in one GROUP
 * @return          none
 */
void tx_grp_cfg (uint8_t const grp_idx, uint8_t ant_mask_in_grp)
{
    if (ant_mask_in_grp)
    {
        // group pre
        quad_params_t *const p_quad_params = &tx_daco.quad_params[grp_idx % NUM_GRP_PER_QUAD];
        volatile v2d_t *const p_v2d = &tx_daco.hw.v2d[grp_idx];
        volatile trx_sys_t *const p_trx_sys = &tx_daco.hw.trx_sys[grp_idx];
        volatile trx_ant_t *const p_trx_ant = &tx_daco.hw.trx_ant[grp_idx];
        volatile vha_hw_t *const p_vha = &tx_daco.hw.vha_hw[grp_idx];

        com_vha_nco_cfg (p_quad_params, p_vha);
        tx_v2d_en_clk (p_quad_params, p_v2d, ant_mask_in_grp);

        uint8_t chnl_idx = 0;
        // go over each channel/ANT in this GROUP
        while (ant_mask_in_grp)
        {
            if (ant_mask_in_grp & 1)
            {
                trx_ant_cfg_seq (p_quad_params, p_trx_ant, chnl_idx);
                trx_sys_cfg_seq (p_quad_params, p_trx_sys, chnl_idx);
                tx_v2d_cfg_seq (p_quad_params, p_v2d, chnl_idx);
                tx_vha_cfg_seq (p_quad_params, p_vha, chnl_idx);
            }
            ant_mask_in_grp >>= 1; // next channel/ANT in one GROUP
            chnl_idx++;
        }
        // group level post
    }
}
