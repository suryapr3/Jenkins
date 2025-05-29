
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
#include "com_assert.h"
#include "rx_static_data_table.h"
#include "rx_gain.h"
#include "rxg.h"
#include "rx_daco.h"

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
extern daco_t rx_daco;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Set RX gain coefficient for FB_SYS
 * @param [in]      uint32_t: DRF index.
 * @param [in]      uint32_t: chain index.
 * @return          None.
 */
void INTRINSIC_ALWAYS_INLINE rx_gain_fbsys_cfg (uint32_t const drf_idx, uint32_t const chain_idx)
{
    RT_ASSERT (drf_idx < NUM_DRF);
    RT_ASSERT (chain_idx < NUM_FBR_CHAIN_PER_DRF);
    rxg_t *const p_rxg = rx_daco.hw.fb_sys[drf_idx].fbr_chain[chain_idx].p_rxg;
    p_rxg->GAIN_COEFF_SHDW.value = get_tl (rx_gain_lut, 0).value;
    p_rxg->SEL.value = 0;
}

/**
 * @brief           Set RX gain coefficient for TRX
 * @param [in]      uint32_t: group index.
 * @param [in]      uint32_t: channel index.
 * @return          None.
 */
void INTRINSIC_ALWAYS_INLINE rx_gain_trxsys_cfg (uint32_t const grp_idx, uint32_t const chnl_idx)
{
    RT_ASSERT (grp_idx < NUM_TRX_GRP);
    RT_ASSERT (chnl_idx < NUM_CHNL_PER_GRP);
    rxg_t *const p_rxg = rx_daco.hw.trx_sys[grp_idx].chnl[chnl_idx].p_rxg;
    p_rxg->GAIN_COEFF_SHDW.value = get_tl (rx_gain_lut, 0).value;
    p_rxg->SEL.value = 0;
}
