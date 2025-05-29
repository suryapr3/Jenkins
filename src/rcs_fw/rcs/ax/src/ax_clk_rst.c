/* INTEL CONFIDENTIAL
 *
 * Copyright 2023 Intel Corporation All Rights Reserved.
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

/**
 * @file    ax_clk_rst.c
 * @brief   common clock and reset functions.
 * @details Enable clocks and bring sub-component out of reset.
 * @todo    none.
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_definitions.h"
#include "com_print.h"
#include "com_assert.h"
#include "ax_clk_rst.h"
#include "bfn_csr.h"
#include "car.h"
#include "dlnk_hub_apb.h"
#include "hub_drf_apb.h"
#include "sys_ctrl.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
// Enable clk source
PRIVATE bool const RST_VEX_ENABLE = 0;
PRIVATE bool const RST_NOC_ENABLE = 1;
PRIVATE bool const RST_DBG_ENABLE = 0;

// V2D
// !! JESD code need to read modify write BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK when writing to GENERAL_CSR !!
#define V2D_BFN_BLK_EN                                                                                                                    \
    (BFN_CSR_GENERAL_CSR_CH_0_CRUX_CLK_EN_BF_MSK | BFN_CSR_GENERAL_CSR_CH_1_CRUX_CLK_EN_BF_MSK                                            \
     | BFN_CSR_GENERAL_CSR_CH_0_DRF_CLK_EN_BF_MSK | BFN_CSR_GENERAL_CSR_CH_1_DRF_CLK_EN_BF_MSK | BFN_CSR_GENERAL_CSR_PDPD_0_CLK_EN_BF_MSK \
     | BFN_CSR_GENERAL_CSR_PDPD_1_CLK_EN_BF_MSK)

// HUB_DRF
#define HUB_DRF_EN (HUB_DRF_APB_HUB_CLK_EN_WR_MASK | 1 << 25) // bit added.  see: Jira HFU-254

// SysCon
#define SYS_CTRL_RESET                                                                                                         \
    (SYS_CTRL_RST_CTRL_RST_DLNK_SUBFC_BF_MSK | SYS_CTRL_RST_CTRL_RST_VEX_SUBFC_BF_MSK | SYS_CTRL_RST_CTRL_RST_DRF_SUBFC_BF_MSK \
     | SYS_CTRL_RST_CTRL_RST_PLL_BF_MSK | SYS_CTRL_RST_CTRL_RST_CORESIGHT_BF_MSK)

// JESD
#define DLNK_JESD_MEM_EN (0x00000000)
#define DLNK_JESD_CLK_EN                                                                                    \
    (DLNK_HUB_APB_JESD_CLK_EN_CLK_BFN_DLNK_EN_BF_MSK | DLNK_HUB_APB_JESD_CLK_EN_CLK_CRUX_DLNK_EN_BF_MSK     \
     | DLNK_HUB_APB_JESD_CLK_EN_CLK_JESD_1G_EN_BF_MSK | DLNK_HUB_APB_JESD_CLK_EN_CLK_JESD_1P5G_EN_BF_MSK    \
     | DLNK_HUB_APB_JESD_CLK_EN_CLK_AXI_S_ACLK_EN_BF_MSK | DLNK_HUB_APB_JESD_CLK_EN_CLK_JESD_122M_EN_BF_MSK \
     | DLNK_HUB_APB_JESD_CLK_EN_CLK_JESD_PHM_FOVR_EN_BF_MSK)

#define DLNK_JESD_GLITCH_SUPRESS_N                                     \
    (DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_AXIS_GLITCH_SUPPRESS_N_BF_MSK \
     | DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_NON_AXIS_GLITCH_SUPPRESS_N_BF_MSK)

#define DLNK_JESD_JESD_RST_N                                                                      \
    (DLNK_HUB_APB_JESD_SW_RST_N_SW_RST_N_BF_MSK | DLNK_HUB_APB_JESD_SW_RST_N_SW_AXIS_RST_N_BF_MSK \
     | DLNK_HUB_APB_JESD_SW_RST_N_SW_PHY_LANE_RST_N_BF_MSK)

#define SIZE_V2D_BFN_CSR (sizeof (gp_v2d_bfn_csr) / sizeof (bfn_csr_t *))
#define SIZE_HUB_DRF     (sizeof (gp_hub_drf) / sizeof (hub_drf_apb_t *))

#define CAR_CLK0_EN          (0x00000000)
#define CAR_CLK1_EN          (0x00000000)
#define CAR_CLK0_DIS         (0xFFFFFFFF)
#define CAR_CLK1_DIS         (0x000000FF)
#define CAR_SOFT_RST0_EN     (0x00000000)
#define CAR_SOFT_RST1_EN     (0x00000000)
#define CAR_SOFT_RST0_DIS    (0xFFFFFFFF)
#define CAR_SOFT_RST1_DIS    (0x000000FF)
#define CAR_NOC_SOFT_RST     (0x00000000)
#define CAR_NOC_CLK_GATE_DIS (0x00000000)
#define CAR_NOC_CLK_GATE_EN  (CAR_NOC_CLK_GATE_DEFAULT)
#define CAR_PD0_MEM_EN       (CAR_PD0_WR_MASK)
#define CAR_PD1_MEM_EN       (CAR_PD1_WR_MASK)
#define CAR_PD0_MEM_DIS      (CAR_PD0_DEFAULT)
#define CAR_PD1_MEM_DIS      (CAR_PD1_DEFAULT)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct
{
    volatile dlnk_hub_apb_jesd_mem_dis_reg_t MEM_DIS;
    volatile dlnk_hub_apb_jesd_clk_en_reg_t CLK_EN;
    volatile dlnk_hub_apb_jesd_glitch_suppress_n_reg_t GLITCH_SUPPRESS_N;
    volatile dlnk_hub_apb_jesd_sw_rst_n_reg_t SW_RESET_N;
} dlnk_hub_apb_jesd_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
PRIVATE volatile bfn_csr_t *const gp_v2d_bfn_csr[] = {V2D0_BFN_CSR, V2D1_BFN_CSR, V2D2_BFN_CSR, V2D3_BFN_CSR,
                                                      V2D4_BFN_CSR, V2D5_BFN_CSR, V2D6_BFN_CSR, V2D7_BFN_CSR};
PRIVATE dlnk_hub_apb_jesd_t *const gp_dlnk_hub_apb_jesd = (dlnk_hub_apb_jesd_t *)DLNK_HUB_APB_JESD_MAP0_JESD_MEM_DIS_REG;
PRIVATE hub_drf_apb_t *const gp_hub_drf[] = {HUB_DRF0_APB, HUB_DRF1_APB};
PRIVATE uint8_t g_rst_jesd_mask = 0;
PRIVATE uint8_t g_rst_v2d_mask = 0;
PRIVATE uint16_t g_rst_antenna_mask = 0;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
PRIVATE uint8_t com_v2d_get_mask (uint16_t ant_mask);
PRIVATE void ax_clk_src_sel (platform_clk_sel_t const *const p_freq_sel);
PRIVATE void com_syscon_en ();
PRIVATE void com_hub_drf_en (bool en);
PRIVATE void dlnk_jesd_en (bool en, uint8_t const jesd_mask); // enable_dlnk
PRIVATE void com_vex_en (bool en);
PRIVATE void com_noc_en (bool en);
PRIVATE void com_dbg_en ();
PRIVATE void com_v2d_en (bool en, uint8_t v2d_mask); // vwrap

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/* Keep this for now
PRIVATE uint8_t com_jesd_get_mask (uint16_t ant_mask, uint8_t const jesd_idx[RST_JESD_NUM_MAX])
{
    uint8_t jesd_mask = g_rst_jesd_mask;

    for (uint32_t idx = 0; idx < RST_JESD_NUM_MAX; idx++)
    {
        if (ant_mask & 0xF)
            jesd_mask |= (1 << jesd_idx[idx]);
        ant_mask >>= 4;
    }
    return g_rst_jesd_mask ^ jesd_mask;
}
*/

PRIVATE uint8_t com_v2d_get_mask (uint16_t ant_mask)
{
    uint32_t idx = 0;
    uint8_t v2d_mask = g_rst_v2d_mask;

    while (ant_mask)
    {
        if (ant_mask & 0x3)
            v2d_mask |= (1 << idx);
        ant_mask >>= 2;
        idx++;
    }
    return v2d_mask ^ g_rst_v2d_mask;
}

PRIVATE void ax_clk_src_sel (platform_clk_sel_t const *const p_freq_sel)
{
    volatile sys_ctrl_sys_ctrl_reg_t sys_ctrl = {.value = SYSCON_CTRL->SYS_CTRL.value};

    if (p_freq_sel->clk_ref_desel == e_CLK_REF_DESEL_PLL) // if clk_ref_desel==e_CLK_REF_DESEL_REF, PLL_BAND_SEL is read only
        sys_ctrl.PLL_BAND_SEL = ENUM2U32 (p_freq_sel->pll_band_sel);
    sys_ctrl.CLK_VEX_SELECT = ENUM2U32 (p_freq_sel->clk_sys);
    sys_ctrl.CLK_DRF_SELECT = ENUM2U32 (p_freq_sel->clk_sys);
    sys_ctrl.REF_CLK_DESELECT = ENUM2U32 (p_freq_sel->clk_ref_desel);
    sys_ctrl.PLL_SELECT = ENUM2U32 (p_freq_sel->ewpll_sel);
    REG_WRITE (SYS_CTRL_SYS_CTRL_REG, sys_ctrl.value);
}

PRIVATE void com_syscon_en ()
{
    sys_ctrl_rst_ctrl_reg_t sys_ctrl_reset = {.value = SYS_CTRL_RST_CTRL_DEFAULT};

    sys_ctrl_reset.value |= SYS_CTRL_RESET;
    REG_WRITE (SYS_CTRL_RST_CTRL_REG, sys_ctrl_reset.value);
}

PRIVATE void com_hub_drf_en (bool en)
{
    uint32_t idx = 0;
    uint32_t const hub_clk_en_val = (en) ? HUB_DRF_EN : HUB_DRF_APB_HUB_CLK_EN_DEFAULT;

    for (idx = 0; idx < SIZE_HUB_DRF; idx++) { REG_WRITE (&gp_hub_drf[idx]->HUB_CLK_EN, hub_clk_en_val); }
}

PRIVATE void dlnk_jesd_en (bool en, uint8_t const jesd_mask)
{
    uint32_t idx = 0;

    if (en)
    {
        // enable jesd memory
        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
                REG_WRITE (&gp_dlnk_hub_apb_jesd[idx].MEM_DIS, DLNK_JESD_MEM_EN);
        }
        INTRINSIC_BARRIER;

        // enable jesd clock
        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
                REG_WRITE (&gp_dlnk_hub_apb_jesd[idx].CLK_EN, DLNK_JESD_CLK_EN);
        }
        INTRINSIC_BARRIER;

        // jesd_resets
        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
            {
                REG_WRITE (&gp_dlnk_hub_apb_jesd[idx].GLITCH_SUPPRESS_N, DLNK_JESD_GLITCH_SUPRESS_N);
                REG_WRITE (&gp_dlnk_hub_apb_jesd[idx].SW_RESET_N, DLNK_JESD_JESD_RST_N);
            }
        }
    }
    else
    {
        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
            {
                gp_dlnk_hub_apb_jesd[idx].GLITCH_SUPPRESS_N.value = DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT;
                gp_dlnk_hub_apb_jesd[idx].SW_RESET_N.value = DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT;
            }
        }

        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
                gp_dlnk_hub_apb_jesd[idx].CLK_EN.value = DLNK_HUB_APB_JESD_CLK_EN_DEFAULT;
        }

        for (idx = 0; idx < RST_JESD_NUM_MAX; idx++)
        {
            if (jesd_mask & (1 << idx))
                gp_dlnk_hub_apb_jesd[idx].MEM_DIS.value = DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT;
        }
    }
}

PRIVATE void com_vex_en (bool en)
{
    volatile uint32_t vex_rst_rel0 = 0;
    volatile uint32_t vex_rst_rel1 = 0;

    if (en)
    {
        // enable vex mem
        REG_WRITE (CAR_PD0_REG, CAR_PD0_MEM_EN);
        REG_WRITE (CAR_PD1_REG, CAR_PD1_MEM_EN);

        // enable vex clock
        REG_WRITE (CAR_CLK_DIS0_REG, CAR_CLK0_EN);
        REG_WRITE (CAR_CLK_DIS1_REG, CAR_CLK1_EN);

        // vex reset
        REG_WRITE (CAR_SOFT_RST0_REG, CAR_SOFT_RST0_EN);
        REG_WRITE (CAR_SOFT_RST1_REG, CAR_SOFT_RST1_EN);
        INTRINSIC_BARRIER;

        // wait for vex out of reset
        do {
            vex_rst_rel0 = REG_READ (CAR_VEX_RST_RELEASE0_REG);
            vex_rst_rel1 = REG_READ (CAR_VEX_RST_RELEASE1_REG);
        } while ((vex_rst_rel0 != CAR_VEX_RST_RELEASE0_RD_MASK) || (vex_rst_rel1 != CAR_VEX_RST_RELEASE1_RD_MASK));
    }
    else
    {
        REG_WRITE (CAR_SOFT_RST0_REG, CAR_SOFT_RST0_DIS);
        REG_WRITE (CAR_SOFT_RST1_REG, CAR_SOFT_RST1_DIS);

        REG_WRITE (CAR_CLK_DIS0_REG, CAR_CLK0_DIS);
        REG_WRITE (CAR_CLK_DIS1_REG, CAR_CLK1_DIS);

        REG_WRITE (CAR_PD0_REG, CAR_PD0_MEM_DIS);
        REG_WRITE (CAR_PD1_REG, CAR_PD1_MEM_DIS);
    }
}

PRIVATE void com_noc_en (bool en)
{
    volatile car_noc_rst_release_reg_t noc_rst_rel = {.value = 0};
    uint32_t cnt_wait = 0;

    if (en)
    {
        // enable noc
        REG_WRITE (CAR_NOC_CLK_GATE_REG, CAR_NOC_CLK_GATE_DIS);

        // reset NOC
        REG_WRITE (CAR_NOC_SOFT_RST_REG, CAR_NOC_SOFT_RST);
        INTRINSIC_BARRIER;

        // Wait for NOC to reset
        do {
            cnt_wait++;
            noc_rst_rel.value = REG_READ (CAR_NOC_RST_RELEASE_REG);
        } while ((!noc_rst_rel.NOC_RESET_RELEASE) && (cnt_wait < 5));
    }
    else
    {
        REG_WRITE (CAR_NOC_SOFT_RST_REG, CAR_NOC_SOFT_RST_DEFAULT); // default is reset state
        REG_WRITE (CAR_NOC_CLK_GATE_REG, CAR_NOC_CLK_GATE_EN);
    }
}

void com_dbg_en ()
{
    volatile uint32_t rst_ctrl = REG_READ (SYS_CTRL_RST_CTRL_REG);
    rst_ctrl |= SYS_CTRL_RST_CTRL_RST_CORESIGHT_BF_MSK;
    REG_WRITE (SYS_CTRL_RST_CTRL_REG, rst_ctrl);
}

PRIVATE void com_v2d_en (bool en, uint8_t v2d_mask) // vwrap
{
    uint32_t idx = 0;
    uint32_t const csr_val = (en) ? V2D_BFN_BLK_EN : BFN_CSR_GENERAL_CSR_DEFAULT;

    while (v2d_mask)
    {
        if (v2d_mask & 0x1)
            REG_WRITE (&gp_v2d_bfn_csr[idx]->GENERAL_CSR, csr_val);
        v2d_mask >>= 1;
        idx++;
    }
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Enable clocks and bring components out of reset.
 * @param [in]      none.
 * @return          none.
 */
void ax_clk_rst_init (platform_clk_sel_t const *const p_freq_sel)
{
    RT_ASSERT (p_freq_sel->clk_sys <= e_CLK_1474M);
    RT_ASSERT (p_freq_sel->clk_ref_desel <= e_CLK_REF_DESEL_PLL);
    // Wait for PLL lock

    if (!g_rst_antenna_mask)
    {
        ax_clk_src_sel (p_freq_sel);
        INTRINSIC_BARRIER;
        com_syscon_en (); // Need to do syscon enable before touching other clocks
        INTRINSIC_BARRIER;
        com_hub_drf_en (true);
        INTRINSIC_BARRIER;
        FW_PRINT (FW_INFO, "Clk sel: ewpll_sel=%d, clk_sys=%d, clk_ref_desel=%d", U32 (p_freq_sel->ewpll_sel), U32 (p_freq_sel->clk_sys),
                  U32 (p_freq_sel->clk_ref_desel));
    }

    // Skip PCIE configuration
    if ((p_freq_sel->en_jesd) && (p_freq_sel->jesd_mask) && (g_rst_jesd_mask != 0xF))
    {
        dlnk_jesd_en (true, g_rst_jesd_mask ^ p_freq_sel->jesd_mask);
        g_rst_jesd_mask |= p_freq_sel->jesd_mask;
        INTRINSIC_BARRIER;
    }

    if (!g_rst_antenna_mask)
    {

        if (RST_VEX_ENABLE)
        {
            com_vex_en (true);
            INTRINSIC_BARRIER;
        }

        if (RST_NOC_ENABLE)
        {
            com_noc_en (true);
            INTRINSIC_BARRIER;
        }
        if (RST_DBG_ENABLE)
        {
            com_dbg_en ();
            INTRINSIC_BARRIER;
        }
    }

    // Skip SPI configuration
    if ((p_freq_sel->en_v2d) && (p_freq_sel->ant_mask) && (g_rst_v2d_mask != 0xFF))
    {
        uint8_t const rst_v2d_mask = com_v2d_get_mask (p_freq_sel->ant_mask); // Do this due to dont double enable.
        g_rst_v2d_mask |= rst_v2d_mask;
        com_v2d_en (true, rst_v2d_mask);
    }

    g_rst_antenna_mask |= p_freq_sel->ant_mask;
}

/**
 * @brief           Clear reset sequence internal state.
 * @param [in]      none.
 * @return          none.
 */
void ax_clk_rst_shutdown ()
{
    if (g_rst_v2d_mask)
        com_v2d_en (false, g_rst_v2d_mask);

    // need not disable com_dbg_en as debug clock will be disable in reset control below
    if (RST_NOC_ENABLE)
        com_noc_en (false);

    if (RST_VEX_ENABLE)
        com_vex_en (false);

    if (g_rst_jesd_mask)
        dlnk_jesd_en (false, g_rst_jesd_mask);

    com_hub_drf_en (false);
    REG_WRITE (SYS_CTRL_RST_CTRL_REG, SYS_CTRL_RST_CTRL_DEFAULT); // restore reset control to default
    REG_WRITE (SYS_CTRL_SYS_CTRL_REG, SYS_CTRL_SYS_CTRL_DEFAULT); // restore clock select to default

    g_rst_v2d_mask = 0;
    g_rst_jesd_mask = 0;
    g_rst_antenna_mask = 0;
}
