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
#ifndef COMMON_RF_DEF_H
#define COMMON_RF_DEF_H

typedef enum
{
    e_JESD_31_MSPS,
    e_JESD_61_MSPS,
    e_JESD_123_MSPS,
    e_JESD_184_MSPS,
    e_JESD_246_MSPS,
    e_JESD_369_MSPS,
    e_JESD_492_MSPS,
    e_JESD_737_MSPS,
    e_JESD_983_MSPS,
    e_JESD_1475_MSPS,
    e_JESD_1966_MSPS,
    e_JESD_2949_MSPS,
    e_JESD_3932_MSPS,
    e_JESD_5898_MSPS,
    e_JESD_7864_MSPS,
} e_jesd_sample_rate_t;

typedef enum
{
    e_JESD_123_MHZ,
    e_JESD_184_MHZ,
    e_JESD_246_MHZ,
    e_JESD_307_MHZ,
    e_JESD_369_MHZ,
    e_JESD_492_MHZ,
    e_JESD_614_MHZ,
    e_JESD_737_MHZ,
    e_JESD_983_MHZ,
} e_jesd_char_clock_t;

typedef enum
{
    e_SYSREF_0p384_MHZ,
    e_SYSREF_0p768_MHZ,
    e_SYSREF_3p84_MHZ,
    e_SYSREF_7p68_MHZ,
} e_jesd_sysref_clk_t;

typedef enum
{
    e_PHY_8_GBPS,
    e_PHY_16_GBPS,
    e_PHY_24_GBPS,
    e_PHY_32_GBPS,
    e_PHY_50_GBPS,
    e_PHY_66_GBPS,
    e_PHY_83_GBPS,
    e_PHY_100_GBPS,
} e_serdes_phy_data_rate_t;

// f_clk: operation clock; DRF/VHA/V2D all on same clock, JESD clock is independent of them
typedef enum
{
    e_CLK_983M,  // 983.04 MHz, default
    e_CLK_1474M, // 1474.56 MHz
} e_sys_clk_t;
typedef e_sys_clk_t e_jesd_clk_t;

typedef enum
{
    e_SMPL_FMT_IQ, // data sample in IQ (complex)
    e_SMPL_FMT_R,  // data sample in real
} e_smpl_fmt_t;

typedef enum
{
    e_PROC_BLK_SZ_P5US, // process block size 0.52us
    e_PROC_BLK_SZ_1US   // process block size 1us
} e_proc_blk_sz_t;

typedef enum
{
    e_PLL_CLK_16_GHZ, // 15.72864 GHz
    e_PLL_CLK_18_GHZ, // 17.69472 GHz, for cm-wave case
    e_PLL_CLK_24_GHZ, // 23.59296 GHz
} e_pll_clk_t;

// supported DAC/ADC rate
typedef enum
{
    e_ANT_RATE_0, // 3 samples per clock
    e_ANT_RATE_1, // 4 samples per clock
    e_ANT_RATE_2, // 6 samples per clock
    e_ANT_RATE_3, // 8 samples per clock
    e_ANT_RATE_4, // 12 samples per clock
    e_ANT_RATE_5, // 16 samples per clock
} e_ant_rate_t;

// system sampling rate for VEX to DRF direction, for mem cap, or @DUC input or DDC output
// The described numbers of clock cycles, N/M, are based on clock rates 983M/1.474G Hz
typedef enum
{
    e_SYS_RATE_IQ_P25 = 0x0,  // 245 MSPS, 8 IQ samples every 32/48 clock cycles.
    e_SYS_RATE_IQ_P375 = 0x1, // 368 MSPS, 8 IQ samples every {21,21,22}/32 clock cycles.

    e_SYS_RATE_IQ_P5 = 0x2,  // 491 MSPS, 8 IQ samples every 16/24 clock cycles.
    e_SYS_RATE_IQ_P75 = 0x3, // 737 MSPS, 8 IQ samples every {10,11,11}/16 clock cycles.

    e_SYS_RATE_IQ_1 = 0x4,   // 983 MSPS, 8 IQ samples every 8/12 clock cycles.
    e_SYS_RATE_IQ_1P5 = 0x5, // 1.474 GSPS, 8 IQ samples every {5,5,6}/8 clock cycles.

    e_SYS_RATE_IQ_2 = 0x6, // 1.966 GSPS, 8 IQ samples every 4/6 clock cycles.
    e_SYS_RATE_IQ_3 = 0x7, // 2.949 GSPS, 8 IQ samples every {2,3,3}/4 clock cycles.

    e_SYS_RATE_IQ_4 = 0x08, // 3.932 GSPS, 8 IQ samples every 2/3 clock cycles.
    e_SYS_RATE_IQ_6 = 0x09, // 5.898 GSPS, 8 IQ samples every {1,1,2}/2 clock cycles.

    e_SYS_RATE_IQ_8 = 0x0a,  // 7.864 GSPS, 8 IQ samples every 1/{1,2} clock cycles.
    e_SYS_RATE_IQ_12 = 0x0b, // 11.796 GSPS, 8 IQ samples every (n/a)/1 clock cycle.

    e_SYS_RATE_R_3 = 0x15,  // 2.949 GSPS, 16 Real samples every {5,5,6}/{n/a} clock cycles.
                            // ant_rate = e_ANT_RATE_0
    e_SYS_RATE_R_4 = 0x16,  // 3.932 GSPS, 16 Real samples every 4/{n/a} clock cycles.
                            // ant_rate = e_ANT_RATE_1
    e_SYS_RATE_R_6 = 0x17,  // 5.898 GSPS, 16 Real samples every {2,3,3}/4 clock cycles.
                            // ant_rate = e_ANT_RATE_2,e_ANT_RATE_1
    e_SYS_RATE_R_8 = 0x18,  // 7.864 GSPS, 16 Real samples every 2/{n/a} clock cycles.
                            // ant_rate = e_ANT_RATE_3
    e_SYS_RATE_R_12 = 0x19, // 11.796 GSPS, 16 Real samples every {1,1,2}/2 clock cycles.
                            // ant_rate = e_ANT_RATE_4,e_ANT_RATE_3
    e_SYS_RATE_R_16 = 0x1a, // 15.728 GSPS, 16 Real samples every 1/{n/a} clock cycles.
                            // ant_rate = e_ANT_RATE_5
    // below two rates not currently supported in DRF:
    e_SYS_RATE_R_18 = 0x1b, // 17.694 GSPS, 18 Real samples every {n/a}/{1,1,2} clock cycles.
    e_SYS_RATE_R_24 = 0x1c, // 23.592 GSPS, 24 Real samples every {n/a}/1 clock cycles.
} e_sys_rate_t;

// used by VHA in both UL & DL and f_clk = 983.04/1474.56MHz cases:
typedef enum
{
    e_VHA_RATE_P125, // 4 I+Q every 32 clocks (0.125 samples per clock) = 122.88/184.32 msps
    e_VHA_RATE_P25,  // 4 I+Q every 16 clocks (0.25 samples per clock) = 245.76/368.64 msps
    e_VHA_RATE_P5,   // 4 I+Q every 8 clocks (0.5 samples per clock) = 491.52/737.28 msps
    e_VHA_RATE_1,    // 4 I+Q every 4 clocks (1 samples per clock) = 983.04/1474.56 msps
    e_VHA_RATE_2,    // 4 I+Q every 2 clocks (2 samples per clock) = 1966.08/2949.12 msps
    e_VHA_RATE_4,    // 4 I+Q every 1 clocks (4 samples per clock) = 3932.16/5898.24 msps
    e_VHA_NO_MIX     // when mod/demod not used
} e_vha_rate_t;

// VHA NCO (modem) selection
typedef enum
{
    e_VHA_MIX_BYPASS,           // Only Band0 is enabled (Band1 off).
    e_VHA_MIX_SINGLE_BAND,      // SWG0 is enabled (SWG1 is off) for Band0 only
    e_VHA_MIX_DUAL_BAND,        // SWG0 and SWG1 are both enabled with Band0 and Band1
    e_VHA_MIX_DUAL_BAND_SHARED, // SWG0 is enabled (DL_SWG1 off) and shared for both bands
} e_vha_mix_sel_t;

// PDPD Capture Memory Source Select. This bit selects the data source going to Capture Memory.
typedef enum
{
    e_PDPD_INGRESS_B,     // Select PDPD ingress main term, the B path data.
    e_PDPD_INGRESS_C,     // Select PDPD ingress extra term, the C path data.
    e_PDPD_EGRESS,        // Select PDPD egress data.
    e_SAMPLE_INTERFACE_A, // Select DRF Sampling Interface A path data.
} e_pd_cap_mem_sel_t;

// PDPD sampling rate
typedef enum
{
    e_PDPD_RATE_IQ_P5, // 0.5 IQ sample per clock, 491/737MSPS
    e_PDPD_RATE_IQ_1,  // 1 IQ sample per clock, 983/1475MSPS
    e_PDPD_RATE_IQ_2,  // 2 IQ samples per clock, 1.966/2.949GSPS
    e_PDPD_RATE_IQ_4,  // 4 IQ samples per clock, 3.93/5.90GSPS
    e_PDPD_RATE_IQ_8,  // 8 IQ samples per clock, 7.86/11.80GSPS
} e_pdpd_rate_t;

// PDPD Coefficient Update LUT Mode. This field controls the number of Look-Up Tables in PDPD coefficient update Mode 1 data.
typedef enum
{
    e_PDPD_LUT_48, // 48 LUTs (32 GMP + 16 DDR)
    e_PDPD_LUT_24, // 24 LUTs (16 GMP + 8 DDR)
    e_PDPD_LUT_12, // 12 LUTs (8 GMP + 4 DDR)
} e_pc_lut_mod_t;

// PDPD processing flow selection
typedef enum
{
    e_PDPD_MOD_ND,   // Non-DPD
    e_PDPD_MOD_DNE,  // DPD + No Extra Terms
    e_PDPD_MOD_DE,   // DPD Extra Terms from VEX
    e_PDPD_MOD_DGNE, // DPD Ganging  & No Extra Terms
    e_PDPD_MOD_DGE,  // DPD Ganging with Extra Terms in PDPD0 only
    e_PDPD_MOD_DPP,  // DPD + Post Processing in VEX
    e_PDPD_MOD_DGPP, // DPD Ganging + Post Processing in VEX
    e_PDPD_MOD_NDPF, // Non-DPD + Post-Filtering
} e_pdpd_mod_sel_t;

// PDPD operating mode
typedef enum
{
    e_PDPD_OP_MOD_NOR, // PDPD operating in normal mode
    e_PDPD_OP_MOD_LP,  // PDPD operating in low-power mode
    e_PDPD_OP_MOD_ELP, // PDPD operating in enhanced low-power mode
} e_pdpd_op_mod_t;

typedef enum
{
    e_CLK_REF_DESEL_REF = 0,
    e_CLK_REF_DESEL_PLL = 1,
} e_clk_ref_desel_t;

typedef enum
{
    e_EWPLL_SEL_EAST = 0,
    e_EWPLL_SEL_WEST = 1,
} e_ewpll_sel_t;

typedef enum
{
    e_DRF_EAST = 0,
    e_DRF_WEST = 1,
} e_drf_sel_t;

typedef enum
{
    e_PLL_BAND_SEL_BOTH_16G = 0,
    e_PLL_BAND_SEL_W16G_E24G = 1,
    e_PLL_BAND_SEL_W24G_E16G = 2,
    e_PLL_BAND_SEL_BOTH_24G = 3,
} e_pll_band_sel_t;

typedef enum
{
    e_CHIP_MODE_0016 = 0,
    e_CHIP_MODE_4016 = 1,
} e_chip_mode_t;

typedef union {
    struct
    {
        uint32_t ITER : 4;
        uint32_t EB : 1;
        uint32_t DAY : 5;
        uint32_t MONTH : 4;
        uint32_t YEAR : 8;
        uint32_t MINOR : 6;
        uint32_t MAJOR : 4;
    };
    uint32_t value;
} ver_fw_t;
#endif
