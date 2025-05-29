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
#if (CPU_RX)
#else
#error "Not RX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "ul_req_msg.h"
#include "rx_daco.h"
#include "rx_gain.h"
#include "rx_lineup.h"
#include "com_assert.h"
#include "com_print.h"
#include "com_rf_def.h"
#include "com_print.h"
#include "com_swg.h"
#include "rx_v2d.h"

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
static void rx_drf_cfg (uint32_t drf_idx, uint32_t ant_mask_in_drf);
static void rx_drf_with_chain_cfg (uint32_t drf_idx, uint32_t chain_idx, uint32_t ant_mask_in_drf);
static void fb_ant_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf);
static void fb_sys_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf);
static void mem_cap_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf);
static void mem_fb_cap_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf);

static void rx_quad_cfg (uint32_t quad_idx, uint32_t ant_mask_in_quad);
static void drf_ant_cfg_seq (uint32_t quad_idx, uint32_t ant_mask_in_quad);
static void rx_grp_cfg (uint32_t grp_idx, uint32_t ant_mask_in_grp);
static void trx_ant_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx);
static void trx_sys_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx);
static void rx_vha_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void drf_ant_cfg_seq (uint32_t quad_idx, uint32_t ant_mask_in_quad) {}
static void rx_drf_with_chain_cfg (uint32_t drf_idx, uint32_t chain_idx, uint32_t ant_mask_in_drf)
{
    rx_gain_fbsys_cfg (drf_idx, chain_idx);
}

static void trx_ant_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx) {}

static void trx_sys_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx)
{
    rx_gain_trxsys_cfg (grp_idx, chnl_idx);
}

static void rx_vha_cfg_seq (uint32_t grp_idx, uint32_t chnl_idx) {}
static void fb_ant_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf) {}
static void fb_sys_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf) {}
static void mem_cap_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf) {}
static void mem_fb_cap_cfg_seq (uint32_t drf_idx, uint32_t ant_mask_in_drf) {}

static void rx_drf_cfg (uint32_t drf_idx, uint32_t ant_mask_in_drf)
{
    if (ant_mask_in_drf)
    {
        volatile fb_ant_t *const p_fb_ant = &rx_daco.hw.fb_ant[drf_idx];
        volatile fb_sys_t *const p_fb_sys = &rx_daco.hw.fb_sys[drf_idx];
        fb_ant_swg_cfg (drf_idx, ant_mask_in_drf);
        com_sys_swg_cfg (drf_idx, ant_mask_in_drf);

        fb_ant_cfg_seq (drf_idx, ant_mask_in_drf);
        fb_sys_cfg_seq (drf_idx, ant_mask_in_drf);
        mem_cap_cfg_seq (drf_idx, ant_mask_in_drf);
        mem_fb_cap_cfg_seq (drf_idx, ant_mask_in_drf);

        uint32_t quad_idx = drf_idx * NUM_QUAD_PER_DRF;
        // go over each QUAD in this DRF
        // do RXG in the drf_config
        while (ant_mask_in_drf)
        {
            uint32_t const ant_mask_quad = ant_mask_in_drf & ((1 << NUM_STRM_PER_QUAD) - 1);
            if (ant_mask_quad)
            {
                rx_quad_cfg (quad_idx, ant_mask_quad);
                rx_drf_with_chain_cfg (drf_idx, quad_idx % NUM_QUAD_PER_DRF, ant_mask_quad);
            }

            ant_mask_in_drf >>= NUM_STRM_PER_QUAD; // next quad in one DRF
            quad_idx++;
        }
    }
}

static void rx_quad_cfg (uint32_t quad_idx, uint32_t ant_mask_in_quad)
{
    if (ant_mask_in_quad)
    {
        drf_ant_cfg_seq (quad_idx, ant_mask_in_quad);

        uint32_t g_idx = quad_idx * NUM_GRP_PER_QUAD;
        // go over each GROUP in this QUAD
        while (ant_mask_in_quad)
        {
            rx_grp_cfg (g_idx, ant_mask_in_quad & ((1 << NUM_CHNL_PER_GRP) - 1));

            ant_mask_in_quad >>= NUM_CHNL_PER_GRP; // next GROUP in one QUAD
            g_idx++;
        }
    }
}

static void rx_grp_cfg (uint32_t grp_idx, uint32_t ant_mask_in_grp)
{
    if (ant_mask_in_grp)
    {
        quad_params_t *const p_quad_params = &rx_daco.quad_params[grp_idx % NUM_GRP_PER_QUAD];
        volatile v2d_t *const p_v2d = &rx_daco.hw.v2d[grp_idx];
        volatile vha_hw_t *const p_vha = &rx_daco.hw.vha_hw[grp_idx];
        com_vha_nco_cfg (p_quad_params, p_vha);

        uint32_t chnl_idx = 0;
        // go over each channel/ANT in this GROUP
        while (ant_mask_in_grp)
        {
            if (ant_mask_in_grp & 1)
            {
                trx_ant_cfg_seq (grp_idx, chnl_idx);
                trx_sys_cfg_seq (grp_idx, chnl_idx);
                rx_v2d_cfg_seq (p_quad_params, p_v2d, chnl_idx);
                rx_vha_cfg_seq (grp_idx, chnl_idx);
            }
            ant_mask_in_grp >>= 1; // next channel/ANT in one GROUP
            chnl_idx++;
        }
    }
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
// void rx_cfg_msg_handler (ul_config_ant_grp_bf_t msg);

/**
 * @brief           Setup RX lineup
 * @param [in]      ant_mask: RX antenna mask.
 * @return          none.
 */
void rx_lineup_cfg (uint32_t ant_mask)
{
    uint32_t drf_idx = 0;
    // go over each DRF
    while (ant_mask)
    {
        rx_drf_cfg (drf_idx, ant_mask & ((1 << NUM_ANT_PER_DRF) - 1));

        ant_mask >>= NUM_ANT_PER_DRF; // next DRF
        drf_idx++;
    }
}
