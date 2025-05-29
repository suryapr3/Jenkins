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

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rx_daco.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
// Note: those macros are only used for initializing hw_t struct members (in daco_t) to link them to the right register blocks defined in
// hw_inc/*.h
#define DRF_ANT_STRM(quad_idx, strm_idx)                                                                                       \
    {                                                                                                                          \
        DACO_MC_5_PARAM (.p_adc_dig, ANT, ADC_DIG, quad_idx, strm_idx), DACO_MC_5_PARAM (.p_asc, ANT, ASC, quad_idx, strm_idx) \
    }

#define DRF_ANT(quad_idx)                                                                                                       \
    .strm = {DRF_ANT_STRM (quad_idx, 0), DRF_ANT_STRM (quad_idx, 1)}, DACO_MC_4_PARAM (.adc_cpu, ANT, CPU_SRAM_BASE, quad_idx), \
    DACO_MC_4_PARAM (.p_adc_dig_fb, ANT, ADC_DIG_FB, quad_idx), DACO_MC_4_PARAM (.p_asc_fb, ANT, ASC_FB, quad_idx),             \
    DACO_MC_4_PARAM (.p_csr, ANT, CSR, quad_idx)

#define TRX_ANT_CHNL(trx_ant_idx, chnl_idx)                                                                                             \
    {                                                                                                                                   \
        DACO_MC_5_PARAM (.p_nleq, TRX_ANT, NLEQ, trx_ant_idx, chnl_idx), DACO_MC_5_PARAM (.p_smc, TRX_ANT, SMC, trx_ant_idx, chnl_idx), \
            DACO_MC_5_PARAM (.p_rxm, TRX_ANT, RXM, trx_ant_idx, chnl_idx)                                                               \
    }
#define TRX_ANT(trx_ant_idx) \
    .chnl = {TRX_ANT_CHNL (trx_ant_idx, 0), TRX_ANT_CHNL (trx_ant_idx, 1)}, DACO_MC_4_PARAM (.p_ctl, TRX_ANT, CTL, trx_ant_idx)

#define TRX_SYS_CHNL(trx_sys_idx, chnl_idx)                                                                                          \
    {                                                                                                                                \
        DACO_MC_5_PARAM (.p_rxg, TRX_SYS, RXG, trx_sys_idx, chnl_idx), DACO_MC_5_PARAM (.p_ddc, TRX_SYS, DDC, trx_sys_idx, chnl_idx) \
    }
#define TRX_SYS(trx_sys_idx)                                                                                                       \
    .chnl = {TRX_SYS_CHNL (trx_sys_idx, 0), TRX_SYS_CHNL (trx_sys_idx, 1)}, DACO_MC_4_PARAM (.p_dmod, TRX_SYS, DMOD, trx_sys_idx), \
    DACO_MC_4_PARAM (.p_trx_sys_csr, TRX_SYS, CSR, trx_sys_idx)

#define FB_ANT_CHAIN(fb_idx, chain_idx)                                                                                          \
    {                                                                                                                            \
        DACO_MC_6_PARAM (.cmem_sram, FB_ANT, CMEM, SRAM_BASE, fb_idx, chain_idx),                                                \
            DACO_MC_5_PARAM (.p_cmem_cfg, FB_ANT, CMEM_CFG, fb_idx, chain_idx),                                                  \
            DACO_MC_5_PARAM (.p_nleq, FB_ANT, NLEQ, fb_idx, chain_idx), DACO_MC_5_PARAM (.p_rxm, FB_ANT, RXM, fb_idx, chain_idx) \
    }
#define FB_ANT(fb_idx)                                                                                                              \
    .fbr_chain = {FB_ANT_CHAIN (fb_idx, 0), FB_ANT_CHAIN (fb_idx, 1)}, DACO_MC_4_PARAM (.p_ddac_top, FB_ANT, DDAC_TOP, fb_idx),     \
    DACO_MC_4_PARAM (.p_ddac_bot, FB_ANT, DDAC_BOT, fb_idx), DACO_MC_4_PARAM (.p_smc_even_top, FB_ANT, SMC_EVEN_TOP, fb_idx),       \
    DACO_MC_4_PARAM (.p_smc_even_bot, FB_ANT, SMC_EVEN_BOT, fb_idx), DACO_MC_4_PARAM (.p_smc_odd_top, FB_ANT, SMC_ODD_TOP, fb_idx), \
    DACO_MC_4_PARAM (.p_smc_odd_bot, FB_ANT, SMC_ODD_BOT, fb_idx), DACO_MC_4_PARAM (.p_swg_even, FB_ANT, SWG_EVEN, fb_idx),         \
    DACO_MC_4_PARAM (.p_swg_odd, FB_ANT, SWG_ODD, fb_idx), DACO_MC_4_PARAM (.p_caldac, FB_ANT, CALDAC, fb_idx),                     \
    DACO_MC_4_PARAM (.p_csr, FB_ANT, CSR, fb_idx)

#define FB_SYS_CHAIN(fb_idx, chain_idx)                                                                                    \
    {                                                                                                                      \
        DACO_MC_5_PARAM (.p_rxg, FB_SYS, RXG, fb_idx, chain_idx), DACO_MC_5_PARAM (.p_ddc, FB_SYS, DDC, fb_idx, chain_idx) \
    }
#define FB_SYS(fb_idx)                                                                                                  \
    .fbr_chain = {FB_SYS_CHAIN (fb_idx, 0), FB_SYS_CHAIN (fb_idx, 1)}, DACO_MC_4_PARAM (.p_dmod, FB_SYS, DMOD, fb_idx), \
    DACO_MC_4_PARAM (.p_swg0, FB_SYS, SWG0, fb_idx), DACO_MC_4_PARAM (.p_ctl, FB_SYS, CTL, fb_idx)

#define MEM_CAP(fb_idx)                                                                                                   \
    DACO_MC_4_PARAM (.mem_cap_sram, MEM_CAP, SRAM_BASE, fb_idx), DACO_MC_3_PARAM (.p_mem_cap, MEM_CAP, fb_idx),           \
        DACO_MC_4_PARAM (.p_mem_cap_cfg, MEM_CAP, CFG, fb_idx), DACO_MC_4_PARAM (.p_mem_cap_test, MEM_CAP, TEST, fb_idx), \
        DACO_MC_4_PARAM (.p_pll_local, MEM_CAP, ANALOG_PLL, fb_idx)

#define V2D_CHNL(v2d_idx, chnl_idx)                                                            \
    {                                                                                          \
        DACO_MC_6_PARAM (.av2d_apb.p_nsip_hbi, V2D, AV2D_APB_, NSIP_HBI_0, v2d_idx, chnl_idx), \
            DACO_MC_6_PARAM (.av2d_apb.p_av2d_csr, V2D, AV2D_APB_, CSR, v2d_idx, chnl_idx)     \
    }
#define V2D(v2d_idx) .chnl = {V2D_CHNL (v2d_idx, 0), V2D_CHNL (v2d_idx, 1)}, DACO_MC_4_PARAM (.p_bfn_csr, V2D, BFN_CSR, v2d_idx)

#define VHA_HW_CHNL(vha_idx, chnl_idx)                                                                                                  \
    {                                                                                                                                   \
        DACO_MC_6_PARAM (.p_ddc[0], VHA, ANT, DDC0, vha_idx, chnl_idx), DACO_MC_6_PARAM (.p_ddc[1], VHA, ANT, DDC1, vha_idx, chnl_idx), \
            DACO_MC_6_PARAM (.p_dmod, VHA, ANT, DMOD, vha_idx, chnl_idx), DACO_MC_5_PARAM (.p_vha_ant, VHA, ANT, vha_idx, chnl_idx),    \
            DACO_MC_6_PARAM (.p_nsip_hbi_csr, VHA, ANT, NSIP_HBI_CSR, vha_idx, chnl_idx)                                                \
    }
#define VHA_HW(vha_idx)                                                                                   \
    .chnl = {VHA_HW_CHNL (vha_idx, 0), VHA_HW_CHNL (vha_idx, 1)}, DACO_MC_3_PARAM (.p_vha, VHA, vha_idx), \
    DACO_MC_4_PARAM (.p_swg, VHA, UL_SWG, vha_idx)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
daco_t rx_daco = {.is_first_cfg = true,
                  .hw = {.drf_ant[0] = {DRF_ANT (0)},
                         .drf_ant[1] = {DRF_ANT (1)},
                         .drf_ant[2] = {DRF_ANT (2)},
                         .drf_ant[3] = {DRF_ANT (3)},

                         .trx_ant[0] = {TRX_ANT (0)},
                         .trx_ant[1] = {TRX_ANT (1)},
                         .trx_ant[2] = {TRX_ANT (2)},
                         .trx_ant[3] = {TRX_ANT (3)},
                         .trx_ant[4] = {TRX_ANT (4)},
                         .trx_ant[5] = {TRX_ANT (5)},
                         .trx_ant[6] = {TRX_ANT (6)},
                         .trx_ant[7] = {TRX_ANT (7)},

                         .trx_sys[0] = {TRX_SYS (0)},
                         .trx_sys[1] = {TRX_SYS (1)},
                         .trx_sys[2] = {TRX_SYS (2)},
                         .trx_sys[3] = {TRX_SYS (3)},
                         .trx_sys[4] = {TRX_SYS (4)},
                         .trx_sys[5] = {TRX_SYS (5)},
                         .trx_sys[6] = {TRX_SYS (6)},
                         .trx_sys[7] = {TRX_SYS (7)},

                         .fb_ant[0] = {FB_ANT (0)},
                         .fb_ant[1] = {FB_ANT (1)},

                         .fb_sys[0] = {FB_SYS (0)},
                         .fb_sys[1] = {FB_SYS (1)},

                         .v2d[0] = {V2D (0)},
                         .v2d[1] = {V2D (1)},
                         .v2d[2] = {V2D (2)},
                         .v2d[3] = {V2D (3)},
                         .v2d[4] = {V2D (4)},
                         .v2d[5] = {V2D (5)},
                         .v2d[6] = {V2D (6)},
                         .v2d[7] = {V2D (7)},

                         .vha_hw[0] = {VHA_HW (0)},
                         .vha_hw[1] = {VHA_HW (1)},
                         .vha_hw[2] = {VHA_HW (2)},
                         .vha_hw[3] = {VHA_HW (3)},
                         .vha_hw[4] = {VHA_HW (4)},
                         .vha_hw[5] = {VHA_HW (5)},
                         .vha_hw[6] = {VHA_HW (6)},
                         .vha_hw[7] = {VHA_HW (7)},

                         .mem_cap[0] = {MEM_CAP (0)},
                         .mem_cap[1] = {MEM_CAP (1)}},

                  .sys_params = {.act_ant_mask = 0, .jesd_ant_mask = 0, .rf_ant_mask = 0, .quad_mask = 0}, // be updated in cfg message
                  .quad_params = {{0}, {0}, {0}, {0}},
                  .adc_params = {{0}, {0}, {0}, {0}}};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           clear rx core daco
 * @param [in]      none
 * @return          none
 */
void rx_daco_clear ()
{
    rx_daco.is_first_cfg = true;
    memset (&rx_daco.sys_params, 0, sizeof (sys_params_t));
    memset (&rx_daco.quad_params, 0, sizeof (quad_params_t) * NUM_QUAD);
    memset (&rx_daco.adc_params, 0, sizeof (quad_params_t) * NUM_QUAD);
}
