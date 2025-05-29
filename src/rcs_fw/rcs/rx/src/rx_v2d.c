/* INTEL CONFIDENTIAL
 *
 * Copyright  2024 Intel Corporation All Rights Reserved.
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
#include <stddef.h>
#include "com_print.h"
#include "rx_v2d.h"
#include "com_static_data_table.h"
#include "com_lock.h"
#include "com_msgs_enum.h"

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
/**
 * @brief           enable V2D RX configuration
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static void INTRINSIC_ALWAYS_INLINE v2d_en (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
void v2d_en (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL

    av2d_csr_rx_csr_rx_gnrl_csr_reg_t csr = p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_GNRL_CSR;
    csr.RX_CFG_COMPLETE = 1;
    // csr.RX_STARTED
    // csr.RX_PD_CFG_COMPLETE
    // csr.RX_PD_STARTED
    // csr.RX_PD_EN
    p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_GNRL_CSR = csr;

    com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    FW_PRINT (FW_DEBUG, "v2d_en is done for RX on chnl %d", chnl);
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
// V2D cfg toplevel routine:
void rx_v2d_cfg_seq (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    // for F flow:
    uint8_t const strm_cfg = p_quad_params->v2d_params.strm_cfg;
    e_proc_blk_sz_t const blk_sz = get_tf (com_v2d_strm_cfg_lut, strm_cfg, blk_sz);
    uint8_t const num_strm = get_tf (com_v2d_strm_cfg_lut, strm_cfg, f);
    uint8_t const drf_rate = p_quad_params->com_params.drf_rate;

    com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_PKT_SZ

    // STREAM_CNT bitfield should be the number of flits expected for the VEX block size, and it should be a multiple of the
    for (uint8_t v = 0; v < num_strm; v++)
    {
        av2d_csr_rx_csr_rx_strm_cnt_reg_t cnt = p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_STRM_CNT[v];
        cnt.STREAM_CNT = get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf (com_drf_rate_conf_lut, drf_rate, sys_rate), strm_cnt);
        cnt.STREAM_EN = 1;
        p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_STRM_CNT[v] = cnt;
        FW_PRINT (FW_DEBUG, "Write to reg: %p, val: %x", &p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_STRM_CNT[v], (cnt.value));
    }

    // RX_PKT_SZ_STREAM_0 packet size defined in register RX_PACKET_SZ. (Note: For single streams, any one of the 4 streams may be
    // chosen, but typically stream ID #0 would be used.)
    av2d_csr_rx_csr_rx_packet_sz_reg_t sz = p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PACKET_SZ;
    // TODO: register should use 8-bit vector
    // TODO: check with Arch to see using fixed value or usecase dependent.
    // set it to 1 flits now to simplify thing
    sz.RX_PKT_SZ_STREAM_0 = 0;
    sz.RX_PKT_SZ_STREAM_1 = 0;
    sz.RX_PKT_SZ_STREAM_2 = 0;
    sz.RX_PKT_SZ_STREAM_3 = 0;
    p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PACKET_SZ = sz;
    FW_PRINT (FW_DEBUG, "Write to reg: %p, val: %x", &p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PACKET_SZ, (sz.value));

    com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_PKT_SZ
    FW_PRINT (FW_DEBUG, "rx_v2d_cfg_seq is done");
}

// called in warmup seqence to make sure all V2D configuration is done before enabling V2D
void rx_v2d_en (uint8_t const quad_idx, uint8_t ant_mask_in_quad)
{
    const quad_params_t *const p_quad_params = &rx_daco.quad_params[quad_idx];
    uint8_t g_idx = quad_idx * NUM_GRP_PER_QUAD;

    while (ant_mask_in_quad)
    {
        volatile v2d_t *const p_v2d = &rx_daco.hw.v2d[g_idx];
        uint8_t ant_mask_in_grp = ant_mask_in_quad & 0x3;
        uint8_t chnl = 0;
        while (ant_mask_in_grp)
        {
            if (ant_mask_in_grp & 1)
            {
                v2d_en (p_quad_params, p_v2d, chnl);
            }
            ant_mask_in_grp >>= 1;
            chnl++;
        }

        ant_mask_in_quad >>= NUM_GRP_PER_QUAD;
        g_idx++;
    }
}
