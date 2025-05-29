/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2023 Intel Corporation
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
 * @file    ax_jesd.c
 * @brief   Functions related to JESD activity.
 * @details This file contains JESD related functions
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_definitions.h"
#include "com_boot.h"
#include "com_print.h"
#include "ax_jesd_config.h"
#include "dlnk_hub_apb.h"
#include "jesd_cmn_csr.h"
#include "jesd_xip_204c_tx.h"
#include "jesd_xip_204c_rx.h"
#include "jesd_xip_204d_tx.h"
#include "jesd_xip_204d_rx.h"
#include "jesd_tx_glue.h"
#include "jesd_rx_glue.h"
#include "jesd_crux_clk_csr.h"
#include "jesd_bfn_events.h"
#include "ax_static_data_table.h"
#include "ax_jesd_config.h"
#include "com_fsm.h"
#include "ax_daco.h"
#include "com_timing.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define QUAD_MAX_NUM              4
#define JESD_CLK                  2
#define SYSREF_CLK                4
#define JESD_CHAR_AND_SMPL_CLK    9
#define JESD_NUM_OF_CONV          6
#define HUB_REG_LINK_OFFSET       4
#define JESD_CMN_REG_LINK_OFFSET  0x00800000
#define STRM_NUM_MAX              16
#define TSB_MEM_SIZE              0x10000
#define RSB_MEM_SIZE              0x100
#define JESD_REG_OFFSET           0x00000004
#define DECOMP_MTSSA_TBL_OFFSET   2
#define DECOMP_EXP_TBL_OFFSET     34
#define COMP_BITFORMAT_TBL_OFFSET 3
#define SYSREF_CLKREF_COMBO       4
#define SMPL_CHR_RATIO            8
#define SMPL_WIDTH                2
#define SMPL_SHFT_CONST           512 / 32
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct
{
    bool is_jlink_used;
    bool is_jlink_enabled;
    uint32_t use_case;
} jesd_track_info;

bool hub_dlink_status[4] = {false, false, false, false};
jesd_track_info rx_link_status[4] = {
    {false, false},
    {false, false},
    {false, false},
    {false, false},
};

uint32_t rx_link_quad_map[4];
uint32_t tx_link_quad_map[4];

jesd_track_info tx_link_status[4] = {
    {false, false},
    {false, false},
    {false, false},
    {false, false},
};

jesd_char_clk_div_t const jesd_clk_to_char_div_lut[JESD_CLK][JESD_CHAR_AND_SMPL_CLK] = {
    [jesd_clk_1ghz] = {[e_JESD_123_MHZ] = div_char_clk_by_eight,
                       [e_JESD_246_MHZ] = div_char_clk_by_four,
                       [e_JESD_307_MHZ] = div_char_clk_by_two,
                       [e_JESD_492_MHZ] = div_char_clk_by_two},
    [jesd_clk_1p5ghz] = {[e_JESD_184_MHZ] = div_char_clk_by_four, [e_JESD_369_MHZ] = div_char_clk_by_two},
};

jesd_smpl_clk_div_t const jesd_sample_to_char_div_lut[JESD_CLK][JESD_CHAR_AND_SMPL_CLK] = {
    [jesd_clk_1ghz] = {[e_JESD_123_MHZ] = div_smpl_clk_by_eight,
                       [e_JESD_246_MHZ] = div_smpl_clk_by_four,
                       [e_JESD_307_MHZ] = div_smpl_clk_by_two,
                       [e_JESD_492_MHZ] = div_smpl_clk_by_two,
                       [e_JESD_614_MHZ] = div_smpl_clk_by_one,
                       [e_JESD_983_MHZ] = div_smpl_clk_by_one},
    [jesd_clk_1p5ghz] =
        {[e_JESD_184_MHZ] = div_smpl_clk_by_four, [e_JESD_369_MHZ] = div_smpl_clk_by_two, [e_JESD_737_MHZ] = div_smpl_clk_by_one},
};

uint32_t const jesd_strm_mem_inst_cnt[STRM_NUM_MAX] = {[0] = 0x10, [1] = 0x08, [3] = 0x04, [7] = 0x02, [15] = 0x01};
uint32_t const jesd_strm_mem_size[STRM_NUM_MAX] = {[0] = 0xFFFF, [1] = 0x7FFF, [3] = 0x3FFF, [7] = 0x1FFF, [15] = 0x0FFF};
uint32_t const jesd_rx_mem_strm_cfg_lut[STRM_NUM_MAX] = {[0] = 0x1FF, [1] = 0xFF, [3] = 0x7F, [7] = 0x3F, [15] = 0x1F};
uint32_t const jesd_smpl_resn_n_lut[SMPL_WIDTH] = {15, 23}; // N-1
uint32_t const sample_to_char_lut[SMPL_CHR_RATIO] = {[0] = 0, [1] = 1, [3] = 2, [7] = 3};
uint32_t const tsad_map_lut[JESD_CLK][SYSREF_CLK] = {
    [jesd_clk_1ghz] = {128, 256, 1280, 2560},
    [jesd_clk_1p5ghz] = {192, 384, 1920, 3840},
};

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
 * @brief
 * @param [in]
 * @return
 */

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
// Common to both TX and RX JESD config
static void config_jesd_hub (uint32_t j_link)
{
    dlnk_hub_apb_jesd_mem_dis_reg_t jesd_mem_dis_reg = {.value = DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT};
    jesd_mem_dis_reg.MEM_DISABLE = 0;
    *(DLNK_HUB_APB_JESD_MAP0_JESD_MEM_DIS_REG + (j_link * HUB_REG_LINK_OFFSET)) = jesd_mem_dis_reg;
    INTRINSIC_BARRIER;

    dlnk_hub_apb_jesd_clk_en_reg_t jesd_clk_en_reg = {.value = DLNK_HUB_APB_JESD_CLK_EN_DEFAULT};
    jesd_clk_en_reg.CLK_BFN_DLNK_EN = 1;
    jesd_clk_en_reg.CLK_CRUX_DLNK_EN = 1;
    jesd_clk_en_reg.CLK_JESD_1G_EN = 1;
    jesd_clk_en_reg.CLK_JESD_1P5G_EN = 1;
    jesd_clk_en_reg.CLK_AXI_S_ACLK_EN = 1;
    jesd_clk_en_reg.CLK_JESD_122M_EN = 1;
    jesd_clk_en_reg.CLK_JESD_PHM_FOVR_EN = 1;
    *(DLNK_HUB_APB_JESD_MAP0_JESD_CLK_EN_REG + (j_link * HUB_REG_LINK_OFFSET)) = jesd_clk_en_reg;
    INTRINSIC_BARRIER;

    dlnk_hub_apb_jesd_glitch_suppress_n_reg_t jesd_glitch_suprss_reg = {.value = DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT};
    jesd_glitch_suprss_reg.AXIS_GLITCH_SUPPRESS_N = 1;
    jesd_glitch_suprss_reg.NON_AXIS_GLITCH_SUPPRESS_N = 1;
    *(DLNK_HUB_APB_JESD_MAP0_JESD_GLITCH_SUPPRESS_N_REG + (j_link * HUB_REG_LINK_OFFSET)) = jesd_glitch_suprss_reg;
    INTRINSIC_BARRIER;

    dlnk_hub_apb_jesd_sw_rst_n_reg_t jesd_sw_rst_reg = {.value = DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT};
    jesd_sw_rst_reg.SW_RESET_N = 1;
    jesd_sw_rst_reg.SW_AXIS_RESET_N = 1;
    jesd_sw_rst_reg.SW_PHY_LANE_RESET_N = 1;
    *(DLNK_HUB_APB_JESD_MAP0_JESD_SW_RST_N_REG + (j_link * HUB_REG_LINK_OFFSET)) = jesd_sw_rst_reg;
    INTRINSIC_BARRIER;
    com_timing_wait_ns (30);
}

static void config_jesd_rx_204c (uint32_t jesd_dl_idx, uint32_t link_offset)
{
    // JESD_XIP_204C_RX_ENMODULE_REG=default
    // JESD_XIP_204C_RX_SUBCLASS_REG=1=default
    // JESD_XIP_204C_RX_CF_REG = default
    // JESD_XIP_204C_RX_CS_REG = default
    JESD_XIP_204C_RX_DATAPATH_INTERCONNECT_REG (link_offset)->value = 0;
    JESD_XIP_204C_RX_F_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_octets_per_frame_f);
    JESD_XIP_204C_RX_L_REG (link_offset)->value = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_lanes_l) - 1;

    jesd_xip_204c_rx_n_reg_t n_reg = {.value = JESD_XIP_204C_RX_N_DEFAULT};

    uint8_t smpl_resn = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_width_n);
    JESD_XIP_204C_RX_N_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    uint32_t m_param = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_converters_m);
    JESD_XIP_204C_RX_M_REG (link_offset)->value = m_param - 1;

    JESD_XIP_204C_RX_NTOTAL_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    JESD_XIP_204C_RX_S_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s);

    JESD_XIP_204C_RX_HD_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_hd_flag);

    JESD_XIP_204C_RX_SCR_REG (link_offset)->value = 1;

    uint32_t ratio = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_to_char_ratio) - 1;
    JESD_XIP_204C_RX_CLK_RATIO_REG (link_offset)->value = sample_to_char_lut[ratio];

    JESD_XIP_204C_RX_BIT_ORDER_REG (link_offset)->value = 0;

    uint32_t soni = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
    uint32_t t1 = soni - 1;
    uint32_t t2 = (get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s) * 8) / soni;
    jesd_xip_204c_rx_sonif_reg_t sonif_reg = {.value = JESD_XIP_204C_RX_SONIF_DEFAULT};
    sonif_reg.SONIF = (t2 << 5) | t1;
    *JESD_XIP_204C_RX_SONIF_REG (link_offset) = sonif_reg;

    //*_RBD_LENGTH_OCTETS_REG= default

    // 204C only reg config
    JESD_XIP_204C_RX_FEC_REG (link_offset)->value = 1;
    JESD_XIP_204C_RX_CRC12_EN_REG (link_offset)->value = 1;
    JESD_XIP_204C_RX_E_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_num_min_emb) - 1;

    // JESD_XIP_204C_RX_THRESH_EMB_ERR_REG==default
    // JESD_XIP_204C_RX_THRESH_SH_ERR_REG=default
}

static void config_jesd_rx_204d (uint32_t jesd_dl_idx, uint32_t link_offset)
{
    // JESD_XIP_204C_RX_ENMODULE_REG=default
    // JESD_XIP_204C_RX_SUBCLASS_REG=1=default
    // JESD_XIP_204C_RX_CF_REG = default
    // JESD_XIP_204C_RX_CS_REG = default
    JESD_XIP_204D_RX_DATAPATH_INTERCONNECT_REG (link_offset)->value = 2;
    JESD_XIP_204D_RX_F_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_octets_per_frame_f);

    JESD_XIP_204D_RX_L_REG (link_offset)->value = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_lanes_l) - 1;

    uint8_t smpl_resn = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_width_n);
    JESD_XIP_204D_RX_N_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    uint32_t m_param = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_converters_m);
    JESD_XIP_204D_RX_M_REG (link_offset)->value = m_param - 1;

    JESD_XIP_204D_RX_NTOTAL_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    jesd_xip_204d_rx_s_reg_t s_reg = {.value = JESD_XIP_204D_RX_S_DEFAULT};
    s_reg.S = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s);
    JESD_XIP_204D_RX_S_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s);

    JESD_XIP_204D_RX_HD_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_hd_flag);

    JESD_XIP_204D_RX_SCR_REG (link_offset)->value = 1;

    uint32_t ratio = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_to_char_ratio) - 1;
    JESD_XIP_204D_RX_CLK_RATIO_REG (link_offset)->value = sample_to_char_lut[ratio];

    uint32_t soni = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
    uint32_t t1 = soni - 1;
    uint32_t t2 = (get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s) * 8) / soni;
    jesd_xip_204d_rx_sonif_reg_t sonif_reg = {.value = JESD_XIP_204D_RX_SONIF_DEFAULT};
    sonif_reg.SONIF = (t2 << 5) | t1;
    *JESD_XIP_204D_RX_SONIF_REG (link_offset) = sonif_reg;
    // 204D only config
    jesd_xip_204d_rx_fec_reg_t rx_fec_reg = {.value = JESD_XIP_204D_RX_FEC_DEFAULT};
    rx_fec_reg.FEC_MODE = 0x1; //@todo, map to system use case provided to FW
    *JESD_XIP_204D_RX_FEC_REG (link_offset) = rx_fec_reg;

    jesd_xip_204d_rx_a_reg_t a_reg = {.value = JESD_XIP_204D_RX_A_DEFAULT};
    a_reg.A = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_num_min_emb) - 1;
    JESD_XIP_204D_RX_A_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_num_min_emb) - 1;
}

static void config_jesd_rx_com (uint32_t jesd_dl_idx, uint32_t lnk_offset)
{
    JESD_CMN_CSR_RX_JESD_MODE_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);

    // JESD RX clock config
    uint32_t jesd_clk = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_1p5g_clk);
    uint32_t char_clk = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_char_clk);
    uint32_t sample_clk = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_sample_clk);
    uint32_t sysref_clk = get_tf (ax_jesd_input_param_lut, 0, sysref_rate);

    jesd_cmn_csr_rx_ip_clk_ctrl_reg_t jesd_rx_clk_reg = {.value = JESD_CMN_CSR_RX_IP_CLK_CTRL_DEFAULT};
    jesd_rx_clk_reg.CLK_GEN_MODE = 0;
    jesd_rx_clk_reg.CHAR_CLK_DIV = jesd_clk_to_char_div_lut[jesd_clk][char_clk];
    jesd_rx_clk_reg.SMPL_CLK_DIV = jesd_sample_to_char_div_lut[jesd_clk][sample_clk];

    if (jesd_clk == e_CLK_983M) // 2 more cases depending on serdes PLL sel
        jesd_rx_clk_reg.DEV_CLK_MUX_SEL = 0;
    else if (jesd_clk == e_CLK_1474M)
        jesd_rx_clk_reg.DEV_CLK_MUX_SEL = 1;

    *JESD_CMN_CSR_RX_IP_CLK_CTRL_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset)) = jesd_rx_clk_reg;

    // Enable clocks and SYSREF
    if (jesd_clk == e_CLK_1474M)
    {
        jesd_cmn_csr_rx_clk_1p5g_div_en_reg_t clk_div_en_reg = {.value = JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_DEFAULT};
        clk_div_en_reg.CLK_1P5G_DIV_ENABLE = 1;
        *JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset)) = clk_div_en_reg;
    }
    JESD_CMN_CSR_RX_CLK_GEN_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    JESD_CMN_CSR_RX_IP_SYSREF_CFG_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    JESD_CMN_CSR_RX_IP_SYSREF_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    // Configure SyncPoint Counter for synchronization
    JESD_CMN_CSR_RX_SYNC_POINT_CTRL_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x0004000B; // sync_point_ctrl_reg;
    JESD_CMN_CSR_RX_SYSREF_TSAD_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = tsad_map_lut[jesd_clk][sysref_clk];

    JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x1;

    if (char_clk == e_JESD_307_MHZ) // in 204D case, configure Fractional Divider, 5 to 8
    {
        JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x00030005;
        JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x1;
    }
}

static void config_jesd_tx_com (uint32_t jesd_dl_idx, uint32_t lnk_offset)
{
    JESD_CMN_CSR_TX_JESD_MODE_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);

    // JESD TX clock config
    uint32_t jesd_clk = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_1p5g_clk);
    uint32_t char_clk = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_char_clk);
    uint32_t sample_clk = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_sample_clk);
    uint32_t sysref_clk = get_tf (ax_jesd_input_param_lut, 0, sysref_rate);

    jesd_cmn_csr_tx_ip_clk_ctrl_reg_t jesd_tx_clk_reg = {.value = JESD_CMN_CSR_TX_IP_CLK_CTRL_DEFAULT};
    jesd_tx_clk_reg.CLK_GEN_MODE = 0;
    jesd_tx_clk_reg.CHAR_CLK_DIV = jesd_clk_to_char_div_lut[jesd_clk][char_clk];
    jesd_tx_clk_reg.SMPL_CLK_DIV = jesd_sample_to_char_div_lut[jesd_clk][sample_clk];
    if (jesd_clk == e_CLK_983M) // 2 more cases depending on serdes PLL sel
        jesd_tx_clk_reg.DEV_CLK_MUX_SEL = 0;
    else if (jesd_clk == e_CLK_1474M)
        jesd_tx_clk_reg.DEV_CLK_MUX_SEL = 1;

    *JESD_CMN_CSR_TX_IP_CLK_CTRL_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset)) = jesd_tx_clk_reg;

    // Enable clocks and SYSREF
    if (jesd_clk == e_CLK_1474M)
    {
        jesd_cmn_csr_tx_clk_1p5g_div_en_reg_t clk_div_en_reg = {.value = JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_DEFAULT};
        clk_div_en_reg.CLK_1P5G_DIV_ENABLE = 1;
        *JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset)) = clk_div_en_reg;
    }
    jesd_cmn_csr_tx_clk_gen_en_reg_t clk_gen_en_reg = {.value = JESD_CMN_CSR_TX_CLK_GEN_EN_DEFAULT};
    clk_gen_en_reg.CLK_GEN_ENABLE = 1;
    JESD_CMN_CSR_TX_CLK_GEN_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    jesd_cmn_csr_tx_ip_sysref_cfg_reg_t sysref_cfg_reg = {.value = JESD_CMN_CSR_TX_IP_SYSREF_CFG_DEFAULT};
    sysref_cfg_reg.IP_SYSREF_CFG = 1;
    JESD_CMN_CSR_TX_IP_SYSREF_CFG_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    jesd_cmn_csr_tx_ip_sysref_en_reg_t sysref_en_reg = {.value = JESD_CMN_CSR_TX_IP_SYSREF_EN_DEFAULT};
    sysref_en_reg.SYSREF_ENABLE = 1;
    JESD_CMN_CSR_TX_IP_SYSREF_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 1;

    // Configure SyncPoint Counter for synchronization
    JESD_CMN_CSR_TX_SYNC_POINT_CTRL_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x0004000B; // sync_point_ctrl_reg;
    JESD_CMN_CSR_TX_SYSREF_TSAD_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = tsad_map_lut[jesd_clk][sysref_clk];
    JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x1;
    JESD_TX_GLUE_ANTENNA_RX_STARTED_SP_BYP_REG (DLNK_JESD0_TX_GLUE_BASE + (lnk_offset))->value = 0x1;
    if (char_clk == e_JESD_307_MHZ) // in 204D case, configure Fractional Divider, 5 to 8
    {
        // JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_REG = default
        JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x00030005;
        JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_REG (DLNK_JESD0_CMN_CSR_BASE + (lnk_offset))->value = 0x01;
    }

    //@todo: waiting for update in PG: Configure the Sample Request Generator (SRG) (supports proper pipelining from TSB to JESD TX IP)

    //    JESD_CMN_CSR_CLK_OBS_CNT_EN_REG @todo disable in functional mode, refer to PG
}

static void config_jesd_tx_204c (uint32_t jesd_dl_idx, uint32_t link_offset)
{
    // JESD_XIP_204C_TX_ENMODULE_REG=default
    // JESD_XIP_204C_TX_SUBCLASS_REG=1=default
    // JESD_XIP_204C_TX_CF_REG = default

    JESD_XIP_204C_TX_CS_REG (link_offset)->value = 0; //@todo: value is based on use of PHM or FOVR
    JESD_XIP_204C_TX_DATAPATH_INTERCONNECT_REG (link_offset)->value = 0;
    JESD_XIP_204C_TX_F_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_octets_per_frame_f);

    JESD_XIP_204C_TX_L_REG (link_offset)->value = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_lanes_l) - 1;

    uint8_t smpl_resn = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_width_n);
    JESD_XIP_204C_TX_N_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    jesd_xip_204c_tx_m_reg_t m_reg = {.value = JESD_XIP_204C_TX_M_DEFAULT};
    uint32_t m_param = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_converters_m);
    m_reg.M = m_param - 1;
    *JESD_XIP_204C_TX_M_REG (link_offset) = m_reg;

    JESD_XIP_204C_TX_NTOTAL_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    jesd_xip_204c_tx_s_reg_t s_reg = {.value = JESD_XIP_204C_TX_S_DEFAULT};
    s_reg.S = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s);
    *JESD_XIP_204C_TX_S_REG (link_offset) = s_reg;

    JESD_XIP_204C_TX_HD_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_hd_flag);

    JESD_XIP_204C_TX_SCR_REG (link_offset)->value = 1;

    jesd_xip_204c_tx_clk_ratio_reg_t clk_ratio_reg = {.value = JESD_XIP_204C_TX_CLK_RATIO_DEFAULT};
    uint32_t ratio = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_to_char_ratio) - 1;
    clk_ratio_reg.CLK_RATIO = sample_to_char_lut[ratio];
    *JESD_XIP_204C_TX_CLK_RATIO_REG (link_offset) = clk_ratio_reg;

    jesd_xip_204c_tx_tl_latency_reg_t tl_latency_reg = {.value = JESD_XIP_204C_TX_TL_LATENCY_DEFAULT};
    tl_latency_reg.TX_TL_LATENCY = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_latency_delay);
    *JESD_XIP_204C_TX_TL_LATENCY_REG (link_offset) = tl_latency_reg;

    JESD_XIP_204C_TX_BIT_ORDER_REG (link_offset)->value = 0;

    uint32_t soni = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
    uint32_t t1 = soni - 1;
    uint32_t t2 = (get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s) * 8) / soni;
    jesd_xip_204c_tx_sonif_reg_t sonif_reg = {.value = JESD_XIP_204C_TX_SONIF_DEFAULT};
    sonif_reg.SONIF = (t2 << 5) | t1;
    *JESD_XIP_204C_TX_SONIF_REG (link_offset) = sonif_reg;

    jesd_xip_204c_tx_sample_req_reg_t smpl_req_reg = {.value = JESD_XIP_204C_TX_SAMPLE_REQ_DEFAULT};
    smpl_req_reg.POS_CYCLES = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_pos);
    smpl_req_reg.NEG_CYCLES = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_neg);
    *JESD_XIP_204C_TX_SAMPLE_REQ_REG (link_offset) = smpl_req_reg;

    // 204C only reg config
    JESD_XIP_204C_TX_FEC_REG (link_offset)->value = 1;

    JESD_XIP_204C_TX_CRC12_EN_REG (link_offset)->value = 1;

    JESD_XIP_204C_TX_E_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_num_min_emb) - 1;
}

static void config_jesd_tx_204d (uint32_t jesd_dl_idx, uint32_t link_offset)
{
    // JESD_XIP_204C_TX_ENMODULE_REG=default
    // JESD_XIP_204C_TX_SUBCLASS_REG=1=default
    // JESD_XIP_204C_TX_CF_REG = default
    JESD_XIP_204D_TX_CS_REG (link_offset)->value = 0; //@todo: value is based on use of PHM or FOVR
    JESD_XIP_204D_TX_DATAPATH_INTERCONNECT_REG (link_offset)->value = 2;
    jesd_xip_204d_tx_f_reg_t f_reg = {.value = JESD_XIP_204D_TX_F_DEFAULT};
    f_reg.F = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_octets_per_frame_f);
    *JESD_XIP_204D_TX_F_REG (link_offset) = f_reg;

    jesd_xip_204d_tx_l_reg_t l_reg = {.value = JESD_XIP_204D_TX_L_DEFAULT};
    l_reg.L = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_lanes_l) - 1;
    *JESD_XIP_204D_TX_L_REG (link_offset) = l_reg;

    uint8_t smpl_resn = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_width_n);
    JESD_XIP_204D_TX_N_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    jesd_xip_204d_tx_m_reg_t m_reg = {.value = JESD_XIP_204D_TX_M_DEFAULT};
    uint32_t m_param = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_converters_m);
    m_reg.M = m_param - 1;
    *JESD_XIP_204D_TX_M_REG (link_offset) = m_reg;

    JESD_XIP_204D_TX_NTOTAL_REG (link_offset)->value = jesd_smpl_resn_n_lut[smpl_resn];

    jesd_xip_204d_tx_s_reg_t s_reg = {.value = JESD_XIP_204D_TX_S_DEFAULT};
    s_reg.S = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s);
    *JESD_XIP_204D_TX_S_REG (link_offset) = s_reg;

    JESD_XIP_204D_TX_HD_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_hd_flag);
    JESD_XIP_204D_TX_SCR_REG (link_offset)->value = 1;

    jesd_xip_204d_tx_clk_ratio_reg_t clk_ratio_reg = {.value = JESD_XIP_204D_TX_CLK_RATIO_DEFAULT};
    uint32_t ratio = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_to_char_ratio) - 1;
    clk_ratio_reg.CLK_RATIO = sample_to_char_lut[ratio];
    *JESD_XIP_204D_TX_CLK_RATIO_REG (link_offset) = clk_ratio_reg;

    jesd_xip_204d_tx_tl_latency_reg_t tl_latency_reg = {.value = JESD_XIP_204D_TX_TL_LATENCY_DEFAULT};
    tl_latency_reg.TX_TL_LATENCY = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_latency_delay);
    *JESD_XIP_204D_TX_TL_LATENCY_REG (link_offset) = tl_latency_reg;

    JESD_XIP_204D_TX_BIT_ORDER_REG (link_offset)->value = 0;

    uint32_t soni = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
    uint32_t t1 = soni - 1;
    uint32_t t2 = (get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_samples_per_frame_s) * 32) / soni;
    jesd_xip_204d_tx_sonif_reg_t sonif_reg = {.value = JESD_XIP_204D_TX_SONIF_DEFAULT};
    sonif_reg.SONIF = (t2 << 5) | t1;
    *JESD_XIP_204D_TX_SONIF_REG (link_offset) = sonif_reg;

    jesd_xip_204d_tx_sample_req_reg_t smpl_req_reg = {.value = JESD_XIP_204D_TX_SAMPLE_REQ_DEFAULT};
    smpl_req_reg.POS_CYCLES = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_pos);
    smpl_req_reg.NEG_CYCLES = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_neg);
    *JESD_XIP_204D_TX_SAMPLE_REQ_REG (link_offset) = smpl_req_reg;

    // 204D only config
    jesd_xip_204d_tx_fec_reg_t tx_fec_reg = {.value = JESD_XIP_204D_TX_FEC_DEFAULT};
    tx_fec_reg.FEC_MODE = 0x3; //@todo, map it to the system use case, an i/p to FW, revisit
    *JESD_XIP_204D_TX_FEC_REG (link_offset) = tx_fec_reg;

    JESD_XIP_204D_TX_A_REG (link_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_num_min_emb) - 1;
}

/*
 * tx_compress_type : System use case provided
 * ant_start_dly_cnt TX_ANTENNA_START_DELAY_CNT
 * dp_start_trig0_dly_cnt TX_DP_START_TRIG0_DELAY_CNT
 */

static void config_jesd_tx_nsip_routing (uint32_t jesd_dl_idx, uint32_t lnk_offset, uint32_t bfn_trg0_ts, uint32_t bfn_trg1_ts,
                                         uint32_t start_trg_delay, uint32_t start_trg0_delay)
{
    uint32_t clk_csr_lnk_offset;
    uint32_t tx_glue_offset;
    uint32_t jesd_bfn_event_offset;
    {
        tx_glue_offset = (DLNK_JESD0_TX_GLUE_BASE + (lnk_offset));
        clk_csr_lnk_offset = (DLNK_JESD0_CRUX_CLK_CSR_BASE + (lnk_offset));
        jesd_bfn_event_offset = (DLNK_JESD0_BFN_EVENTS_BASE + (lnk_offset));

        uint32_t streams_num = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_streams);

        jesd_tx_glue_strm_inst_cnt_reg_t strm_inst_cnt_reg = {.value = JESD_TX_GLUE_STRM_INST_CNT_DEFAULT};
        strm_inst_cnt_reg.STRM_MEM_INST_UL = jesd_strm_mem_inst_cnt[streams_num - 1];
        *JESD_TX_GLUE_STRM_INST_CNT_REG (tx_glue_offset) = strm_inst_cnt_reg;
        jesd_crux_clk_csr_tx_strm_mem_size_reg_t strm_mem_size_reg = {.value = JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT};
        strm_mem_size_reg.TX_MEM_SIZE = jesd_strm_mem_size[streams_num - 1];
        jesd_crux_clk_csr_tx_strm_mem_size_reg_t *p_mem_size;
        p_mem_size = JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_REG (clk_csr_lnk_offset);
        for (uint32_t i = 0; i < STRM_NUM_MAX; i++) { *p_mem_size++ = strm_mem_size_reg; }

        uint32_t offset = TSB_MEM_SIZE / (streams_num);
        for (uint32_t i = 0; i < streams_num; i++)
        {
            JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET))->value = (i * offset);
        }
        uint32_t sonl = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
        uint32_t smpl_shift_size = SMPL_SHFT_CONST / sonl;
        jesd_tx_glue_conv_dp_cfg_reg_t conv_dp_cfg_reg = {.value = JESD_TX_GLUE_CONV_DP_CFG_DEFAULT};
        conv_dp_cfg_reg.TX_SONI_UL = sonl - 1;
        conv_dp_cfg_reg.SMPL_WIDTH_UL = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_sample_width_n);
        conv_dp_cfg_reg.SMPL_SHIFT_SIZE_UL = smpl_shift_size;
        *JESD_TX_GLUE_CONV_DP_CFG_REG (tx_glue_offset) = conv_dp_cfg_reg;

        if (jesd_dl_idx == 10) // Use case# I-122-32C4-32
            JESD_TX_GLUE_CONV_SMPL_INTRLV_CTRL_REG (tx_glue_offset)->value = 0x00F78650;

        //_TX_TSB_TRIG_EN_REG = default
        //_TX_TSB_FULL_WATER_MARK = default
        JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_REG (clk_csr_lnk_offset)->value = 0x0000ffff;
        // TX_TSB_EMPTY_WATER_MARK= default
        //_TX_TSB_CFG=default

        uint32_t smpl_pos = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_pos);
        uint32_t smpl_neg = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, tx_sample_neg);
        uint32_t rd_freq = (smpl_pos + smpl_neg) * (smpl_shift_size / sonl) - 1;

        //@todo, revisit this
        jesd_tx_glue_datapath_gate_sel_reg_t datapath_sel_reg = {.value = JESD_TX_GLUE_DATAPATH_GATE_SEL_DEFAULT};
        uint32_t usecase = get_tf (ax_jesd_input_param_lut, 0, jesd_tx_start_type);
        if (usecase == bfn_event) // via BFN
        {
            datapath_sel_reg.TX_START_TRIG0_SEL = 2;
            datapath_sel_reg.TX_START_TRIG1_SEL = 1;
            *JESD_TX_GLUE_DATAPATH_GATE_SEL_REG (tx_glue_offset) = datapath_sel_reg;

            //@todo Figure out which register among 8 registers
            JESD_BFNE_CFG0_REG (jesd_bfn_event_offset)->value = 0x1;
            JESD_BFNE_CFG1_REG (jesd_bfn_event_offset)->value = 0x1;
            JESD_BFNE_START0_REG (jesd_bfn_event_offset)->value = bfn_trg0_ts;
            JESD_BFNE_START1_REG (jesd_bfn_event_offset)->value = bfn_trg1_ts;
        }
        else if (usecase == rxantenna_start) // via Antennarx_start
        {
            datapath_sel_reg.TX_START_TRIG0_SEL = 0;
            datapath_sel_reg.TX_START_TRIG1_SEL = 0;
            *JESD_TX_GLUE_DATAPATH_GATE_SEL_REG (tx_glue_offset) = datapath_sel_reg;

            JESD_TX_GLUE_ANTENNA_START_DELAY_CNT_REG (tx_glue_offset)->value = start_trg_delay;
            JESD_TX_GLUE_DP_START_TRIG0_DELAY_CNT_REG (tx_glue_offset)->value = start_trg0_delay;
        }

        // configure below 2 regs when FB is enabled
        //_TX_FB_EN_EVENT_DLY
        //_TX_FB_CONV_DP_CFG
        uint32_t tx_comp_type = get_tf (ax_jesd_input_param_lut, 0, compression_type);
        JESD_CRUX_CLK_CSR_TX_TOP_REG (clk_csr_lnk_offset)->value = get_tf (ax_jesd_comp_param_lut, tx_comp_type, comp_top_reg);
        JESD_CRUX_CLK_CSR_TX_VMLGA_REG (clk_csr_lnk_offset)->value = get_tf (ax_jesd_comp_param_lut, tx_comp_type, comp_vmlga_reg);
        JESD_CRUX_CLK_CSR_TX_VNSH_REG (clk_csr_lnk_offset)->value = get_tf (ax_jesd_comp_param_lut, tx_comp_type, comp_vnsh_reg);

        for (uint32_t i = 0; i < JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_ARR_SZ0; i++)
        {
            JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET))->value =
                p_ax_jesd_comp_param_lut->ax_jesd_comp_param_lut[tx_comp_type].value[COMP_BITFORMAT_TBL_OFFSET + i];
        }
    }
}

static void config_jesd_rx_nsip_routing (uint32_t jesd_dl_idx, uint32_t lnk_offset)
{
    uint32_t clk_csr_lnk_offset;
    uint32_t rx_glue_offset;

    rx_glue_offset = (DLNK_JESD0_RX_GLUE_BASE + (lnk_offset));
    clk_csr_lnk_offset = (DLNK_JESD0_CRUX_CLK_CSR_BASE + (lnk_offset));

    uint32_t streams_num = 1 << get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_num_streams);
    uint32_t offset = RSB_MEM_SIZE / (streams_num);
    for (uint32_t i = 0; i < streams_num; i++)
    {
        JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET))->value = (i * offset);
    }

    jesd_crux_clk_csr_rx_rd_mem_tbl_reg_t rd_mem_tbl_reg = {.value = JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT};
    for (uint32_t i = 0; i < streams_num; i++)
    {
        rd_mem_tbl_reg.RX_MEM_BASE_ADDR = (i * offset);
        rd_mem_tbl_reg.STREAM_ID = i;
        *JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET)) = rd_mem_tbl_reg;
    }

    jesd_crux_clk_csr_rx_strm_cfg_reg_t strm_cfg_reg = {.value = JESD_CRUX_CLK_CSR_RX_STRM_CFG_DEFAULT};
    strm_cfg_reg.FLITS_PER_STRM = 0x7;
    strm_cfg_reg.NUM_STRM = streams_num;
    *JESD_CRUX_CLK_CSR_RX_STRM_CFG_REG (clk_csr_lnk_offset) = strm_cfg_reg;

    jesd_crux_clk_csr_rx_mem_strm_cfg_reg_t mem_strm_cfg_reg = {.value = JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_DEFAULT};
    JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_REG (clk_csr_lnk_offset)->value = jesd_rx_mem_strm_cfg_lut[streams_num - 1];

    JESD_RX_GLUE_SONI_REG (rx_glue_offset)->value = get_tf (ax_jesd_configuration_lut, jesd_dl_idx, jesd_soni);
    //_RX_CONV_SMPL_INTRLV_CTRL

    // Optional: Configure the ability to force the JESD RX output data to 0’s, @todo)
    // RX_UL_EN_EVENT_DLY
    // RX_ZERO_INS_EN

    jesd_rx_glue_datapath_gate_sel_reg_t gate_sel_reg = {.value = JESD_RX_GLUE_DATAPATH_GATE_SEL_DEFAULT};
    gate_sel_reg.RX_DP_GATE_SEL = get_tf (ax_jesd_input_param_lut, 0, jesd_rx_start_type);
    *JESD_RX_GLUE_DATAPATH_GATE_SEL_REG (rx_glue_offset) = gate_sel_reg;

    uint32_t rx_decomp_type = get_tf (ax_jesd_input_param_lut, 0, decompression_type);
    JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_REG (clk_csr_lnk_offset)->value = get_tf (ax_jesd_decomp_param_lut, rx_decomp_type, decomp_top_reg);
    JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_REG (clk_csr_lnk_offset)->value =
        get_tf (ax_jesd_decomp_param_lut, rx_decomp_type, decomp_vnsh_ctl);

    for (uint32_t i = 0; i < JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_ARR_SZ0; i++)
    {
        JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET))->value =
            p_ax_jesd_decomp_param_lut->ax_jesd_decomp_param_lut[rx_decomp_type].value[DECOMP_MTSSA_TBL_OFFSET + i];
    }

    for (uint32_t i = 0; i < JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_ARR_SZ0; i++)
    {
        JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL0_REG (clk_csr_lnk_offset + (i * JESD_REG_OFFSET))->value =
            p_ax_jesd_decomp_param_lut->ax_jesd_decomp_param_lut[rx_decomp_type].value[DECOMP_EXP_TBL_OFFSET + i];
    }
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief JESD TX enable
 * @param [in]  jesd_cfg: JESD TX config data
 * @return
 */
void ax_jesd_tx_enable (uint8_t quad_mask)
{
    uint32_t jesd_dl_idx;
    uint32_t jesd_mode;
    uint32_t jesd_link_id;
    for (uint32_t i = 0; i < QUAD_MAX_NUM; i++)
    {
        if (quad_mask & (1 << i))
        {
            jesd_link_id = tx_link_quad_map[i];
            if (!tx_link_status[jesd_link_id].is_jlink_enabled)
            {
                jesd_dl_idx = tx_link_status[jesd_link_id].use_case;
                jesd_mode = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);
                {
                    FW_PRINT (FW_INFO, "JESD TX Enable, quad id %d, assigned JESD link %d, use case %d", i, jesd_link_id, jesd_dl_idx);
                    if (jesd_mode == jesd_204c)
                    {
                        JESD_XIP_204C_TX_ENMODULE_REG (DLNK_JESD0_XIP_204C_TX_BASE + (jesd_link_id * JESD_CMN_REG_LINK_OFFSET))->value = 1;
                    }
                    else if (jesd_mode == jesd_204d)
                    {
                        JESD_XIP_204D_TX_ENMODULE_REG (DLNK_JESD0_XIP_204D_TX_BASE + (jesd_link_id * JESD_CMN_REG_LINK_OFFSET))->value = 1;
                    }
                }
                tx_link_status[jesd_link_id].is_jlink_enabled = true;
            }
        }
    }
}

void ax_jesd_rx_enable (uint8_t quad_mask)
{
    uint32_t jesd_dl_idx;
    uint32_t jesd_mode;
    uint32_t jesd_link_id;
    for (uint32_t i = 0; i < QUAD_MAX_NUM; i++)
    {
        if (quad_mask & (1 << i))
        {
            jesd_link_id = rx_link_quad_map[i];
            if (!rx_link_status[jesd_link_id].is_jlink_enabled)
            {
                jesd_dl_idx = rx_link_status[jesd_link_id].use_case;
                jesd_mode = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);
                {
                    FW_PRINT (FW_INFO, "JESD RX Enable, quad id %d, assigned JESD link %d, use case %d", i, jesd_link_id, jesd_dl_idx);
                    if (jesd_mode == jesd_204c)
                    {
                        JESD_XIP_204C_RX_ENMODULE_REG (DLNK_JESD0_XIP_204C_RX_BASE + (jesd_link_id * JESD_CMN_REG_LINK_OFFSET))->value = 1;
                    }
                    else if (jesd_mode == jesd_204d)
                    {
                        JESD_XIP_204D_RX_ENMODULE_REG (DLNK_JESD0_XIP_204D_RX_BASE + (jesd_link_id * JESD_CMN_REG_LINK_OFFSET))->value = 1;
                    }
                }
                rx_link_status[jesd_link_id].is_jlink_enabled = true;
            }
        }
    }
}

/**
 * @brief JESD TX config routine
 * @param [in]  jesd_cfg: JESD TX config data
 * @return
 */
void ax_config_jesd_tx ()
{
    ax_daco_t *p_ax_daco = ax_daco_get_addr ();
    cfg_jesd_t *jesd_cfg = &p_ax_daco->jesd_tx_cfg;
    uint32_t jesd_dl_idx = jesd_cfg->use_case_idx;
    uint32_t lnk_offset;
    uint32_t jesd_mode_offset = 0;
    uint32_t jesd_link_id;

    for (uint32_t quad = 0; quad < QUAD_MAX_NUM; quad++)
    {
        jesd_link_id = jesd_cfg->jesd_quad_map[quad];
        if (jesd_link_id == QUAD_NOT_USED)
        {
            FW_PRINT (FW_INFO, "JESD TX config, QUAD%  is inactive", quad);
        }
        else
        {
            FW_PRINT (FW_INFO, "JESD TX config, QUAD %d assigned JESD link %d", quad, jesd_link_id);
            lnk_offset = jesd_link_id * JESD_CMN_REG_LINK_OFFSET;
            // common to both TX and RX, for all JESD links requested
            if (!hub_dlink_status[jesd_link_id])
            {
                config_jesd_hub (jesd_link_id);
                hub_dlink_status[jesd_link_id] = true;
            }

            // JESD TX only Config
            if (!tx_link_status[jesd_link_id].is_jlink_used)
            {
                config_jesd_tx_com (jesd_dl_idx, lnk_offset);

                uint32_t jesd_mode = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);
                // Pre-configure JESD RX per use chain, do the below per chain. 204C/204D
                if (jesd_mode == jesd_204c)
                {
                    jesd_mode_offset = (DLNK_JESD0_XIP_204C_TX_BASE + lnk_offset);
                    config_jesd_tx_204c (jesd_dl_idx, jesd_mode_offset);
                }
                else if (jesd_mode == jesd_204d)
                {
                    jesd_mode_offset = (DLNK_JESD0_XIP_204D_TX_BASE + lnk_offset);
                    config_jesd_tx_204d (jesd_dl_idx, jesd_mode_offset);
                }
                tx_link_status[jesd_link_id].is_jlink_used = true;
                tx_link_status[jesd_link_id].use_case = jesd_dl_idx;
                tx_link_quad_map[quad] = jesd_link_id;
                config_jesd_tx_nsip_routing (jesd_dl_idx, lnk_offset, 0, 0, 0, 0);
            }
        }
    }
}

/**
 * @brief JESD RX config routine
 * @param [in]  jesd_cfg: JESD RX config data
 * @return
 */
void ax_config_jesd_rx ()
{
    ax_daco_t *p_ax_daco = ax_daco_get_addr ();
    cfg_jesd_t *jesd_cfg = &p_ax_daco->jesd_rx_cfg;

    uint32_t jesd_dl_idx = jesd_cfg->use_case_idx;
    uint32_t lnk_offset;
    uint32_t jesd_mode_offset = 0;
    uint32_t jesd_link_id;

    for (uint32_t quad = 0; quad < QUAD_MAX_NUM; quad++)
    {
        jesd_link_id = jesd_cfg->jesd_quad_map[quad];
        if (jesd_link_id == QUAD_NOT_USED)
        {
            FW_PRINT (FW_INFO, "JESD RX config, QUAD% is inactive", quad);
        }
        else
        {
            FW_PRINT (FW_INFO, "JESD RX config, QUAD %d assigned JESD link %d", quad, jesd_link_id);
            lnk_offset = jesd_link_id * JESD_CMN_REG_LINK_OFFSET;
            // common to both TX and RX, for all JESD links requested
            if (!hub_dlink_status[jesd_link_id])
            {
                config_jesd_hub (jesd_link_id);
                hub_dlink_status[jesd_link_id] = true;
            }

            // JESD RX only Config
            if (!rx_link_status[jesd_link_id].is_jlink_used)
            {
                config_jesd_rx_com (jesd_dl_idx, lnk_offset);

                uint32_t jesd_mode = get_tf (ax_jesd_rate_index_lut, jesd_dl_idx, jesd_204d);
                // Pre-configure JESD RX per use chain, do the below per chain. 204C/204D
                if (jesd_mode == jesd_204c)
                {
                    jesd_mode_offset = (DLNK_JESD0_XIP_204C_RX_BASE + lnk_offset);
                    config_jesd_rx_204c (jesd_dl_idx, jesd_mode_offset);
                }
                else if (jesd_mode == jesd_204d)
                {
                    jesd_mode_offset = (DLNK_JESD0_XIP_204D_RX_BASE + lnk_offset);
                    config_jesd_rx_204d (jesd_dl_idx, jesd_mode_offset);
                }
                rx_link_status[jesd_link_id].is_jlink_used = true;
                rx_link_status[jesd_link_id].use_case = jesd_dl_idx;
                rx_link_quad_map[quad] = jesd_link_id;
                config_jesd_rx_nsip_routing (jesd_dl_idx, lnk_offset);
            }
        }
    }
}
