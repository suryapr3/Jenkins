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
 * @file    common_utils.c
 * @details common utilitis for V2D Test Cases.
 * @todo    Write documentation for source file sample_source.h
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include "common_utils.h"
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const uint32_t g_v2d_host_id[][2][2] = {
    {{NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D0_Port0 and V2D0_Port1
     {NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D0_Port2 and V2D0_Port3
    {{NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D1_Port0 and V2D1_Port1
     {NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D1_Port2 and V2D1_Port3
    {{NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D2_Port0 and V2D2_Port1
     {NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D2_Port2 and V2D2_Port3
    {{NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D3_Port0 and V2D3_Port1
     {NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D3_Port2 and V2D3_Port3
    {{NOC_BRDG_V2D_4_P0_94_62_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_4_P1_95_62_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D4_Port0 and V2D4_Port1
     {NOC_BRDG_V2D_4_P2_96_62_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_4_P3_97_62_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D4_Port2 and V2D4_Port3
    {{NOC_BRDG_V2D_5_P0_100_64_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_5_P1_101_64_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D5_Port0 and V2D5_Port1
     {NOC_BRDG_V2D_5_P2_102_64_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_5_P3_103_64_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D5_Port2 and V2D5_Port3
    {{NOC_BRDG_V2D_6_P0_106_66_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_6_P1_107_66_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D6_Port0 and V2D6_Port1
     {NOC_BRDG_V2D_6_P2_108_66_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_6_P3_109_66_STRTX_BRDG_ID_VAL_DEFAULT}},   // Host ID for V2D6_Port2 and V2D6_Port3
    {{NOC_BRDG_V2D_7_P0_112_68_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_7_P1_113_68_STRTX_BRDG_ID_VAL_DEFAULT},   // Host ID for V2D7_Port0 and V2D7_Port1
     {NOC_BRDG_V2D_7_P2_114_68_STRTX_BRDG_ID_VAL_DEFAULT, NOC_BRDG_V2D_7_P3_115_68_STRTX_BRDG_ID_VAL_DEFAULT}}   // Host ID for V2D7_Port2 and V2D7_Port3
};

/*This array with below configurations
 * DPD input sampling rate, DPD output sampling rate, total LUT's, max DDR terms and max GMP terms*/
#if Z0_USE_CASE
/*for Z0 use case the max LUT is 24*/
const uint32_t g_test_config_tbl[][5] = {
    /*Normal Sampling Rate Mode*/
    {0, 0, PDPD_LUT_24, 8, 16},
    {1, 1, PDPD_LUT_24, 8, 16},
    {2, 2, PDPD_LUT_24, 8, 16},
    {3, 3, PDPD_LUT_24, 8, 16},
    {4, 4, PDPD_LUT_12, 4, 8},
    /*Low Sampling Rate & Low power Mode*/
    {2, 1, PDPD_LUT_24, 8, 16},
    {3, 2, PDPD_LUT_24, 8, 16},
    {3, 1, PDPD_LUT_24, 8, 16},
    {4, 3, PDPD_LUT_12, 4, 8},
    {4, 2, PDPD_LUT_12, 4, 8},
    {4, 1, PDPD_LUT_12, 4, 8},
    /*Enhanced Low Sampling Rate Mode*/
    {2, 1, PDPD_LUT_24, 8, 16},
    {3, 2, PDPD_LUT_24, 8, 16},
    {3, 1, PDPD_LUT_24, 8, 16},
    {4, 3, PDPD_LUT_24, 8, 16},
    {4, 2, PDPD_LUT_24, 8, 16},
    {4, 1, PDPD_LUT_24, 8, 16}
};
#else
const uint32_t g_test_config_tbl[][5] = {
    /*Normal Sampling Rate Mode*/
    {0, 0, PDPD_LUT_48, 16, 32},
    {1, 1, PDPD_LUT_48, 16, 32},
    {2, 2, PDPD_LUT_48, 16, 32},
    {3, 3, PDPD_LUT_24, 8, 16},
    {4, 4, PDPD_LUT_12, 4, 8},
    /*Low Sampling Rate & Low power Mode*/
    {2, 1, PDPD_LUT_48, 16, 32},
    {3, 2, PDPD_LUT_24, 8, 16},
    {3, 1, PDPD_LUT_24, 8, 16},
    {4, 3, PDPD_LUT_12, 4, 8},
    {4, 2, PDPD_LUT_12, 4, 8},
    {4, 1, PDPD_LUT_12, 4, 8},
    /*Enhanced Low Sampling Rate Mode*/
    {2, 1, PDPD_LUT_48, 16, 32},
    {3, 2, PDPD_LUT_48, 16, 32},
    {3, 1, PDPD_LUT_48, 16, 32},
    {4, 3, PDPD_LUT_24, 8, 16},
    {4, 2, PDPD_LUT_48, 16, 32},
    {4, 1, PDPD_LUT_48, 16, 32}
};
#endif

const int g_v2d_instance_in_quad[][V2D_PER_QUAD] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7}
};

/*In a given TC for a given QUAD the Rx and Tx VEX cores are hard coded
 * if flexiblity w.r.t the vex cores needed within a quad it can be modified later*/
const int g_vex_instance_in_v2d[][VEX_PER_V2D] = {
    /*Tx Ch0, Rx Ch0, Tx Ch1, Rx Ch1*/
    {0, 1, 8, 9},
    {2, 3, 10, 11},
    {4, 5, 12, 13},
    {6, 7, 14, 15}
};

/* Vectors per block for the given sample rate which was defined as per order in sys_rate_t enum*/
const int g_flow1_vectors_per_block[] = {4, 6, 8, 12, 16, 24, 32, 48, 64, 96, 128, 192, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 32, 48, 64, 96, 128, 144, 192};

/* The value should be (number of flits per data block -1) and the MSB bit should be set to enable the corresponding
 * stream*/
const uint32_t g_flow1_tx_strm_cnt0_offset[] = {0x80000007, 0x8000000B, 0x8000000F, 0x80000017, 0x8000001F, 0x8000002F, 0x8000003F,
        0x8000005F, 0x8000007F, 0x800000BF, 0x800000FF, 0x8000017F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x8000002F, 0x8000003F, 0x8000005F,
        0x8000007F, 0x800000BF, 0x800000FF, 0x8000011F, 0x8000017F};

/* Bit 0 to 7 indicates number of flits in a processing block and the value should be (number of flits - 1) defined as per
 * order in sys_rate_t enum*/
const uint32_t g_flow1_md_control_tbl[] = {0x7, 0xB, 0xF, 0x17, 0x1F, 0x2F, 0x3F, 0x5F, 0x7F, 0xBF, 0xFF, 0x17F, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0x2F, 0x3F, 0x5F, 0x7F, 0xBF, 0xFF, 0x11F, 0x17F};

/* Vectors per block for the given sample rate which was defined as per order in pdpd_rate_t enum*/
#ifdef E2E_FLOW_EN
const int g_v2d_vectors_per_block[][PDPD_NUM_SAMPLE_RATES] = {
#else // !E2E_FLOW_EN
const int g_vectors_per_block[][PDPD_NUM_SAMPLE_RATES] = {
#endif // !E2E_FLOW_EN
    {8, 16, 32, 64, 128},
    {12, 24, 48, 96, 192}
};

/* The value should be (number of flits per data block -1) and the MSB bit should be set to enable the corresponding
 * stream*/
const uint32_t g_tx_strm_cnt0_value[][PDPD_NUM_SAMPLE_RATES] = {
    {0x8000000F, 0x8000001F, 0x8000003F, 0x8000007F, 0x800000FF},
    {0x80000017, 0x8000002F, 0x8000005F, 0x800000BF, 0x8000017F},
};

/* Bit 0 to 7 indicates the Block size in flits which should be equal to corresponding elements in g_vectors_per_block
 * array*/
#ifdef E2E_FLOW_EN
const int g_v2d_md_control_tbl[][PDPD_NUM_SAMPLE_RATES] = {
#else // !E2E_FLOW_EN
const int g_md_control_tbl[][PDPD_NUM_SAMPLE_RATES] = {
#endif // !E2E_FLOW_EN
    {0xF, 0x1F, 0x3F, 0x7F, 0xFF},
    {0x17, 0x2F, 0x5F, 0xBF, 0x17F}
};

/*Mapping of PDPD rate enum to sys_rate enum*/
const int g_pdpd_rate_sys_rate_map[][PDPD_NUM_SAMPLE_RATES] = {
    {2/*p5*/, 4/*1G*/, 6/*2G*/, 8/*4G*/, 10/*8G*/},
    {3/*p75*/, 5/*1P5G*/, 7/*3G*/, 9/*6G*/, 11/*12G*/},
};

/*start sector for an instance of FB memory*/
const int g_fb_mem_start_sector_per_v2d[4] = {
    8, 10, 12, 14
};

/* Number of vectors in the G Buffer as per LUT_MODE*/
const int g_vectors_g_buf_lut_mode[PDPD_NUM_LUTS] = {120, 60, 30};

const char *pdpd_rate_str[] = {"IQ_P5", "IQ_1", "IQ_2", "IQ_4", "IQ_8"};

#ifdef E2E_FLOW_EN
const char *v2d_sys_rate_str[] =
#else // !E2E_FLOW_EN
const char *sys_rate_str[] =
#endif // !E2E_FLOW_EN
{"IQ_P25", "IQ_P375", "IQ_P5", "IQ_P75", "IQ_1", "IQ_1P5", "IQ_2", "IQ_3", "IQ_4", "IQ_6", "IQ_8", "IQ_12",
    "", "", "", "", "", "", "", "", "", "R_3", "R_4", "R_6", "R_8", "R_12", "R_16", "R_18", "R_24"};
const char *drf_clock_str[] = {"983MHz", "1.5GHz"};
const int num_lut[] = {48, 24, 12};
const char *split_method_str[] = {"EQUAL SPLIT", "UN-EQUAL SPLIT"};
const char *post_filter_mode_str[] = {"PASSTHRU_MODE", "FILTER_MODE"};

char* g_rcs_file_path[] = { "rcs_fw/ax_hw.elf"};

static v2d_flow_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

// The last entry should be CIO2STRM_STRM_DEST0_OFFSET
v2d_flow_tbl_t g_cio2strm_config_tbl[] = {
// INT Enable
    {CIO2STRM_OFFSET + CIO2STRM_INT_EN_OFFSET, CIO2STRM_INT_EN_VALUE, \
        CIO2STRM_INT_EN_WR_MASK, "CIO2STRM_INT_ENABLE"},

//VE00 cio2strm
    {CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE,
        CIO2STRM_FIFO_STAT_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, \
        CIO2STRM_WORD_CNT_CTL_WR_MASK, "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the single stream from vex core to CRUX*/
    {CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET, 0x00000001, CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, \
        CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW0"},
    {CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET, 0x0FFFFFFF, \
        CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in bytes
    {CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[0] - mapped to V2D_0_Port_0
    {CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET, 0x00000044, CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"}

};

v2d_flow_tbl_t g_strm2cio_config_tbl[] = {
// INT Enable
    {STRM2CIO_OFFSET + STRM2CIO_INT_EN_OFFSET, STRM2CIO_INT_ENABLE_VALUE, STRM2CIO_INT_EN_WR_MASK, \
        "STRM2CIO_INT_ENABLE"},

// VE00 strm2cio
    {STRM2CIO_OFFSET + STRM2CIO_FIFO_STAT_CTL_OFFSET, STRM2CIO_FIFO_STATUS_CTL_VALUE, \
        STRM2CIO_FIFO_STAT_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
    {STRM2CIO_OFFSET + STRM2CIO_WORD_CNT_CTL_OFFSET, STRM2CIO_WORD_CNT_CTL_VALUE, \
        STRM2CIO_WORD_CNT_CTL_WR_MASK, "STRM2CIO_MEM_WORD_CNT_CTL"}
};

v2d_flow_tbl_t g_v2d_pdpd_passthru_config_tbl[] = {
    //I[31:16]Q[15:0]. I= 2^13, Q=0
    {PDPD_PASSTHRU_C_SHDW_OFFSET, ((0x2<<13)<<16), PDPD_PASSTHRU_C_SHDW_WR_MASK , "PDPD_PASSTHRU_C_SHDW"},
    {PDPD_PASSTHRU_C_LIVE_OFFSET, ((0x2<<13)<<16), PDPD_PASSTHRU_C_LIVE_WR_MASK, "PDPD_PASSTHRU_C_LIVE"}
};

v2d_flow_tbl_t g_v2d_pdpd_cfg_config_tbl[] = {
    //PASSTHRU_DLY =0, pdpd_rate-> run time param
    {PDPD_CFG_OFFSET, 0x7, PDPD_CFG_WR_MASK, "PDPD_CONFIG"}
};

v2d_flow_tbl_t g_v2d_pdpd_ctrl_config_tbl[] = {
    {PDPD_CTRL_OFFSET, 0x0, PDPD_CTRL_WR_MASK, "PDPD_CONTROL"}
};

v2d_flow_tbl_t g_v2d_pdpd_post_c_center_config_tbl[] = {
    {PDPD_POST_C_CENTER_OFFSET, 0x0, PDPD_POST_C_CENTER_WR_MASK, "POST_C_CENTER"}
};

v2d_flow_tbl_t g_v2d_pdpd_post_c_config_tbl[V2D_PDPD_MAX_POST_C_TERMS] = {
// OFFSET values from V2D PDPD BASE address
    {PDPD_POST_C0_OFFSET, 0x0, PDPD_POST_C_WR_MASK, "POST_C"}
};

v2d_flow_tbl_t g_v2d_pdpd_gmp_static_config_tbl[V2D_PDPD_MAX_GMP_TERMS] = {
    {PDPD_GMP_STATIC0_OFFSET, 0x0, PDPD_GMP_STATIC_WR_MASK, "V2D_PDPD_GMP_STATIC"}
};

v2d_flow_tbl_t g_v2d_pdpd_ddr_static_config_tbl[V2D_PDPD_MAX_DDR_TERMS] = {
    {PDPD_DDR_STATIC0_OFFSET, 0x0, PDPD_DDR_STATIC_WR_MASK, "DDR_STATIC"}
};

v2d_flow_tbl_t g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[V2D_PDPD_MAX_GMP_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_GMP_DYNAMIC_SHDW0_GMP_C_SHDW0_OFFSET, 0x0, PDPD_GMP_DYNAMIC_SHDW_GMP_C_SHDW_WR_MASK, "GMP_DYNAMIC_SHDW_GMP_C_SHDW"}
};

v2d_flow_tbl_t g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[V2D_PDPD_MAX_GMP_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_GMP_DYNAMIC_LIVE0_GMP_C_LIVE0_OFFSET, 0x0, PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_WR_MASK, "GMP_DYNAMIC_LIVE_GMP_C_LIVE"}
};

v2d_flow_tbl_t g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[V2D_PDPD_MAX_GMP_TERMS]= {
    {PDPD_GMP_DYNAMIC_SHDW0_GMP_SHIFT_SHDW_OFFSET, 0x0, PDPD_GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_WR_MASK, \
        "GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW"}
};

v2d_flow_tbl_t g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[V2D_PDPD_MAX_GMP_TERMS]= {
    {PDPD_GMP_DYNAMIC_LIVE0_GMP_SHIFT_LIVE_OFFSET, 0x0, PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_WR_MASK, \
        "GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE"}  ,
};

v2d_flow_tbl_t g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[V2D_PDPD_MAX_DDR_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_DDR_DYNAMIC_SHDW0_DDR_C_SHDW0_OFFSET, 0x0, PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_WR_MASK, "DDR_DYNAMIC_SHDW_DDR_C_SHDW"}
};

v2d_flow_tbl_t g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[V2D_PDPD_MAX_DDR_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_DDR_DYNAMIC_LIVE0_DDR_C_LIVE0_OFFSET, 0x0, PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_WR_MASK, "DDR_DYNAMIC_LIVE_DDR_C_LIVE"}
};

v2d_flow_tbl_t g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[V2D_PDPD_MAX_DDR_TERMS] = {
    {PDPD_DDR_DYNAMIC_SHDW0_DDR_SHIFT_SHDW_OFFSET, 0x0, PDPD_DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_WR_MASK, \
        "DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW"}
};

v2d_flow_tbl_t g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[V2D_PDPD_MAX_DDR_TERMS] = {
    {PDPD_DDR_DYNAMIC_LIVE0_DDR_SHIFT_LIVE_OFFSET, 0x0, PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK, \
        "DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE"}
};

v2d_flow_tbl_t g_pdpd_nl_c_shdw_config_tbl[V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_NL_C_SHDW0_OFFSET, 0x0, PDPD_NL_C_SHDW_WR_MASK, "PDPD_NL_C_SHDW"}
};

v2d_flow_tbl_t g_pdpd_nl_c_live_config_tbl[V2D_PDPD_MAX_C_LUT_SEGMENTS] = {
    {PDPD_NL_C_LIVE0_OFFSET, 0x0, PDPD_NL_C_LIVE_WR_MASK, "PDPD_NL_C_LIVE"}
};

v2d_flow_tbl_t g_v2d_pdpd_extra_static_config_tbl[] = {
    {PDPD_EXTRA_STATIC_OFFSET, 0x0, PDPD_EXTRA_STATIC_WR_MASK, "PDPD_EXTRA_STATIC"}
};

v2d_flow_tbl_t g_v2d_pdpd_passthru_shdw_config_tbl[] = {
// OFFSET values from V2D PDPD BASE address
    //I[31:16]Q[15:0]. I= 2^13, Q=0
    {PDPD_PASSTHRU_C_SHDW_OFFSET, ((0x2<<13)<<16), PDPD_PASSTHRU_C_SHDW_WR_MASK , "PDPD_PASSTHRU_C_SHDW"},
};

v2d_flow_tbl_t g_v2d_pdpd_passthru_live_config_tbl[] = {
// OFFSET values from V2D PDPD BASE address
    //I[31:16]Q[15:0]. I= 2^13, Q=0
    {PDPD_PASSTHRU_C_LIVE_OFFSET, ((0x2<<13)<<16), PDPD_PASSTHRU_C_LIVE_WR_MASK, "PDPD_PASSTHRU_C_LIVE"}
};

v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_passthru_config_tbl[] = {
// OFFSET values from V2D PDPD BASE address
    {PDPD_TCNT_UPDATE_PASSTHRU_OFFSET, 0x0, PDPD_TCNT_UPDATE_PASSTHRU_WR_MASK, "TCNT_UPDATE_PASSTHRU"}
};

v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_nl_config_tbl[] = {
// OFFSET values from V2D PDPD BASE address
    {PDPD_TCNT_UPDATE_NL_LUT_OFFSET, 0x0, PDPD_TCNT_UPDATE_NL_LUT_WR_MASK, "TCNT_UPDATE_NL_LUT"}
};

v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_c_config_tbl[] = {
// OFFSET values from V2D PDPD BASE address
    {PDPD_TCNT_UPDATE_C_LUT_OFFSET, 0x0, PDPD_TCNT_UPDATE_C_LUT_WR_MASK, "TCNT_UPDATE_C_LUT"}
};


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function to get v2d interrupt status
 * @param [in]      srp
 * @return          status value
 */
int get_v2d_interrupt_status (int v2d_num, int apb_num)
{
    return read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_STAT_OFFSET), \
            "V2D_INT_STATUS");
}

/**
 * @brief           Function to compare the data
 * @param [in]      srp
 * @return          status value
 */
int data_compare (int *underrun_sample, int *underrun_sample_new, int size)
{
    int i, result = 0;

    for (i = 0; i < size; i++)
    {
        if ((underrun_sample[i] != underrun_sample_new[i]))
            result |= (1 << i);
    }
    return result;
}

/**
 * @brief           Function configuring the pdpd config egsiter from host
 * @param [in]      V2d Id , APB Id , passthru delay value and pdpd_rate
 * @return          status
 */
int pdpd_cfg_reg_config(int v2d_num, int apb_num, int passthru_value, pdpd_rate_t pdpd_rate)
{
    int rv = 0;
    static pdpd_cfg_reg_t pdpd_cfg_reg;

    printf("INFO: PDPD configuration Started");
    //config regsiter bit fileds

    /*External Bypass Enable
      0: Bypass mode is controlled by the CONTROL register
      1: Bypass mode is controlled externally, e.g. via sample count
     */
    unsigned int EXT_CTRL_BYPASS = 0;

   /*0: Zero stuffing mode is controlled by the CONTROL register
     1: Zero Stuffing mode is controlled externally, e.g. via sample count
    */
    unsigned int EXT_CTRL_ZERO_STUFF = 0;

    /*0: GMP/DDR Coefficient LUT live update is controlled by the CONTROL register
    1: GMP/DDR Coefficient LUT live update is controlled externally, e.g. via sample count*/
    unsigned int EXT_CTRL_UPDATE_C_LUT  = 0 ;

    /*External Non-linear Magnitude Mapping LUT Update Enable
      0: Non-linear magnitude mapping LUT live update is controlled by the CONTROL register
      1: Non-linear magnitude mapping LUT live update is controlled externally, e.g. via sample count*/
    unsigned int EXT_CTRL_UPDATE_NL_LUT = 0 ;

    /*External Passthru Coefficient Update Enable
      0: Passthru coefficient live update is controlled by the CONTROL register
      1: Passthru coefficient live update is controlled externally, e.g. via sample coun
     */
    unsigned int EXT_CTRL_UPDATE_PASSTHRU = 0;

    /*Non-linear Magnitude Enable
      0: Non-linear magnitude mapping is NOT enabled
      1: Non-linear magnitude mapping is enabled
    */
    unsigned int NLMAG_ENABLE = 0;

    /*Non-linear Magnitude Interpolation
      0: Non-linear magnitude mapping LUT interpolation is NOT enabled
      1: Non-linear magnitude mapping LUT interpolation is enabled
     */
    unsigned int NLMAG_INTERP = 0;

    /*Coefficient LUT Segmnts
      0: All GMP/DDR Coefficient LUTs have 64 segments (all 65 entries are used).
      1: All GMP/DDR Coefficient LUTs have 32 segments (only entries 0..32 are used)
     */
    unsigned int CLUT_SEGMENTS = 0;

    /*Coefficient LUT Interpolation
      0: GMP/DDR Coefficient LUT interpolation is NOT enabled
      1: GMP/DDR Coefficient LUT interpolation is enabled
     */
    /* In Matlab this value was 1 by default , however with value 0 it will work for special LUT*
       Check HSD https://hsdes.intel.com/resource/14022595772*/
    unsigned int CLUT_INTERP = 1;

    /*0: No duplication. Each LUT is unique.
    1: Duplication factor of 2. GMP[0..15] are also written to GMP[16..31]; DDR[0..7] are also written to DDR[8..15].
    2: Duplication factor of 4. GMP[0..7] are also written to GMP{[8..15], [16..23], [24..31]}; DDR[0..3] are also written to DDR{[4..7], [8..11], [12..15]}.
    3: No Duplication.
    */
    unsigned int CLUT_DUPL = 0;

    /*Select Passthru Delay
      Passthru sample delay
      *NOTE: // this should be greater than the m & q delay, to be taken care in
    */
    unsigned int PASSTHRU_DLY = passthru_value;

    /*0: Ganged terms are NOT included in the final output.
      1: Ganged terms are included in the final output.
      In a ganged configuration this bit should be set to 1 for the primary (PDPD0) instance.
    */
    unsigned int GANG_IN_EN = 0;

    /*0: Ganged terms are NOT output to the partner PDPD instance.
      1: Ganged terms are output to the partner PDPD instance.
      In a ganged configuration this bit should be set to 1 for the secondary (PDPD1) instance.
    */
    unsigned int GANG_OUT_EN = 0;

    switch(pdpd_rate)
    {
        case PDPD_RATE_IQ_4:
            CLUT_DUPL = 1;
            break;
        case PDPD_RATE_IQ_8:
            CLUT_DUPL = 2;
            break;
    }

    pdpd_cfg_reg.EXT_CTRL_BYPASS = EXT_CTRL_BYPASS; //1
    pdpd_cfg_reg.EXT_CTRL_ZERO_STUFF= EXT_CTRL_ZERO_STUFF; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_C_LUT = EXT_CTRL_UPDATE_C_LUT; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_NL_LUT = EXT_CTRL_UPDATE_NL_LUT; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_PASSTHRU = EXT_CTRL_UPDATE_PASSTHRU; //1
    pdpd_cfg_reg.NLMAG_ENABLE = NLMAG_ENABLE; //1
    pdpd_cfg_reg.NLMAG_INTERP = NLMAG_INTERP; //1
    pdpd_cfg_reg.CLUT_SEGMENTS = CLUT_SEGMENTS; //1
    pdpd_cfg_reg.CLUT_INTERP = CLUT_INTERP; //1
    pdpd_cfg_reg.CLUT_DUPL = CLUT_DUPL; //1
    pdpd_cfg_reg.PASSTHRU_DLY = PASSTHRU_DLY; //7
    pdpd_cfg_reg.GANG_IN_EN = GANG_IN_EN; //1
    pdpd_cfg_reg.GANG_OUT_EN = GANG_OUT_EN; //1
    g_v2d_pdpd_cfg_config_tbl[0].value = pdpd_cfg_reg.value;

    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_cfg_config_tbl[0].offset), \
            g_v2d_pdpd_cfg_config_tbl[0].value, g_v2d_pdpd_cfg_config_tbl[0].mask, g_v2d_pdpd_cfg_config_tbl[0].name))
        return rv;

    return rv;
}


/**
 * @brief           Function configuring the pdpd config egsiter from host
 * @param [in]      V2d Id , APB Id , passthru delay value and pdpd_rate
 * @return          status
 */
int ganging_pdpd_cfg_reg_config(int v2d_num, int apb_num, int passthru_value, pdpd_rate_t pdpd_rate)
{
    int rv = 0;
    static pdpd_cfg_reg_t pdpd_cfg_reg;

    printf("INFO: PDPD configuration Started");
    //config regsiter bit fileds

    /*External Bypass Enable
      0: Bypass mode is controlled by the CONTROL register
      1: Bypass mode is controlled externally, e.g. via sample count
     */
    unsigned int EXT_CTRL_BYPASS = 0;

   /*0: Zero stuffing mode is controlled by the CONTROL register
     1: Zero Stuffing mode is controlled externally, e.g. via sample count
    */
    unsigned int EXT_CTRL_ZERO_STUFF = 0;

    /*0: GMP/DDR Coefficient LUT live update is controlled by the CONTROL register
    1: GMP/DDR Coefficient LUT live update is controlled externally, e.g. via sample count*/
    unsigned int EXT_CTRL_UPDATE_C_LUT  = 0 ;

    /*External Non-linear Magnitude Mapping LUT Update Enable
      0: Non-linear magnitude mapping LUT live update is controlled by the CONTROL register
      1: Non-linear magnitude mapping LUT live update is controlled externally, e.g. via sample count*/
    unsigned int EXT_CTRL_UPDATE_NL_LUT = 0 ;

    /*External Passthru Coefficient Update Enable
      0: Passthru coefficient live update is controlled by the CONTROL register
      1: Passthru coefficient live update is controlled externally, e.g. via sample coun
     */
    unsigned int EXT_CTRL_UPDATE_PASSTHRU = 0;

    /*Non-linear Magnitude Enable
      0: Non-linear magnitude mapping is NOT enabled
      1: Non-linear magnitude mapping is enabled
    */
    unsigned int NLMAG_ENABLE = 0;

    /*Non-linear Magnitude Interpolation
      0: Non-linear magnitude mapping LUT interpolation is NOT enabled
      1: Non-linear magnitude mapping LUT interpolation is enabled
     */
    unsigned int NLMAG_INTERP = 0;

    /*Coefficient LUT Segmnts
      0: All GMP/DDR Coefficient LUTs have 64 segments (all 65 entries are used).
      1: All GMP/DDR Coefficient LUTs have 32 segments (only entries 0..32 are used)
     */
    unsigned int CLUT_SEGMENTS = 0;

    /*Coefficient LUT Interpolation
      0: GMP/DDR Coefficient LUT interpolation is NOT enabled
      1: GMP/DDR Coefficient LUT interpolation is enabled
     */
    unsigned int CLUT_INTERP = 0;

    /*0: No duplication. Each LUT is unique.
    1: Duplication factor of 2. GMP[0..15] are also written to GMP[16..31]; DDR[0..7] are also written to DDR[8..15].
    2: Duplication factor of 4. GMP[0..7] are also written to GMP{[8..15], [16..23], [24..31]}; DDR[0..3] are also written to DDR{[4..7], [8..11], [12..15]}.
    3: No Duplication.
    */
    unsigned int CLUT_DUPL = 0;

    /*Select Passthru Delay
      Passthru sample delay
      *NOTE: // this should be greater than the m & q delay, to be taken care in
    */
    unsigned int PASSTHRU_DLY = passthru_value;

    /*0: Ganged terms are NOT included in the final output.
      1: Ganged terms are included in the final output.
      In a ganged configuration this bit should be set to 1 for the primary (PDPD0) instance.
    */
    unsigned int GANG_IN_EN = 0;

    /*0: Ganged terms are NOT output to the partner PDPD instance.
      1: Ganged terms are output to the partner PDPD instance.
      In a ganged configuration this bit should be set to 1 for the secondary (PDPD1) instance.
    */
    unsigned int GANG_OUT_EN = 0;

    switch(pdpd_rate)
    {
        case PDPD_RATE_IQ_4:
            CLUT_DUPL = 1;
            break;
        case PDPD_RATE_IQ_8:
            CLUT_DUPL = 2;
            break;
    }

    switch(apb_num)
    {
        case PDPD_MAIN_INSTANCE:
            GANG_IN_EN = 1;
            break;
        case PDPD_SECONDARY_INSTANCE:
            GANG_OUT_EN = 1;
            break;
    }

    pdpd_cfg_reg.EXT_CTRL_BYPASS = EXT_CTRL_BYPASS; //1
    pdpd_cfg_reg.EXT_CTRL_ZERO_STUFF= EXT_CTRL_ZERO_STUFF; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_C_LUT = EXT_CTRL_UPDATE_C_LUT; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_NL_LUT = EXT_CTRL_UPDATE_NL_LUT; //1
    pdpd_cfg_reg.EXT_CTRL_UPDATE_PASSTHRU = EXT_CTRL_UPDATE_PASSTHRU; //1
    pdpd_cfg_reg.NLMAG_ENABLE = NLMAG_ENABLE; //1
    pdpd_cfg_reg.NLMAG_INTERP = NLMAG_INTERP; //1
    pdpd_cfg_reg.CLUT_SEGMENTS = CLUT_SEGMENTS; //1
    pdpd_cfg_reg.CLUT_INTERP = CLUT_INTERP; //1
    pdpd_cfg_reg.CLUT_DUPL = CLUT_DUPL; //1
    pdpd_cfg_reg.PASSTHRU_DLY = PASSTHRU_DLY; //7
    pdpd_cfg_reg.GANG_IN_EN = GANG_IN_EN; //1
    pdpd_cfg_reg.GANG_OUT_EN = GANG_OUT_EN; //1
    g_v2d_pdpd_cfg_config_tbl[0].value = pdpd_cfg_reg.value;

    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_cfg_config_tbl[0].offset), \
            g_v2d_pdpd_cfg_config_tbl[0].value, g_v2d_pdpd_cfg_config_tbl[0].mask, g_v2d_pdpd_cfg_config_tbl[0].name))
        return rv;

    return rv;
}


/**
 * @brief           Function configuring the pdpd config egsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_ctrl_reg_config(int v2d_num, int apb_num, int update_passthru_bit, int update_c_lut_bit)
{
    static pdpd_ctrl_reg_t pdpd_ctrl_reg;
    int rv = 0;

    uint32_t UPDATE_C_LUT = update_c_lut_bit; // : 1;
    ///< Writing a 1 to this bit causes all of the GMP/DDR shadow coefficient
    ///< registers to be copied to their live counterparts. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="0" ResetValue="0x0"

    uint32_t UPDATE_NL_LUT = 0; // : 1;
    ///< Writing a 1 to this bit causes all of the NL_MAG LUT shadow coefficient
    ///< registers to be copied to their live counterparts. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="1" ResetValue="0x0"

    uint32_t UPDATE_PASSTHRU  = update_passthru_bit ;//: 1;
    ///< Writing a 1 to this bit causes the PASSTHRU shadow coefficient register
    ///< to be copied to its live counterpart. This bit is self-clearing.
    ///< AccessType="RW/AC" BitOffset="2" ResetValue="0x0"

    uint32_t BYPASS  = 0; //: 1;
    ///< 0: All statically enabled terms are included in the final output.
    ///< 1: Only the passthru term is included in the final output.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"

    uint32_t ZERO_STUFF = 0; // : 1;
    ///0: Valid samples on the main data input bus are processed normally.
    ///1: Valid samples on the main data input bus are replaced with zeros.
    ///< AccessType="RW" BitOffset="4 ResetValue="0x0"


    pdpd_ctrl_reg.UPDATE_C_LUT = UPDATE_C_LUT;
    pdpd_ctrl_reg.UPDATE_NL_LUT = UPDATE_NL_LUT;
    pdpd_ctrl_reg.UPDATE_PASSTHRU = UPDATE_PASSTHRU;
    pdpd_ctrl_reg.BYPASS = BYPASS;
    pdpd_ctrl_reg.ZERO_STUFF = ZERO_STUFF;
    g_v2d_pdpd_ctrl_config_tbl[0].value = pdpd_ctrl_reg.value;

    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_ctrl_config_tbl[0].offset), \
                g_v2d_pdpd_ctrl_config_tbl[0].value, g_v2d_pdpd_ctrl_config_tbl[0].mask, g_v2d_pdpd_ctrl_config_tbl[0].name))
        return rv;
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient regsiter from host
 * @param [in]      V2d Id , APB Id, i value and q value
 * @return          status
 */
int pdpd_passthru_c_reg_config(int v2d_num, int apb_num, int i_value, int q_value)
{
    int i, rv = 0;
    pdpd_passthru_c_shdw_reg_t pdpd_passthru_c_shdw_reg;
    /* rom MATLAB
     *  passthru_coeff_i = 2^13;  % real part
        passthru_coeff_q = 0;  % imaginary part
     * */

    uint32_t Q  = q_value; //: 15;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="15" ResetValue="None"

    uint32_t I  = i_value; //: 15;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="31" ResetValue="None"

    pdpd_passthru_c_shdw_reg.Q = Q;
    pdpd_passthru_c_shdw_reg.I = I;

#if 0
    g_v2d_pdpd_passthru_config_tbl[0].value = bpdpd_passthru_c_shdw_reg.value; // shadow register
    g_v2d_pdpd_passthru_config_tbl[1].value = bpdpd_passthru_c_shdw_reg.value; // live register
#else
    g_v2d_pdpd_passthru_config_tbl[0].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
    g_v2d_pdpd_passthru_config_tbl[1].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
#endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_passthru_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_passthru_config_tbl[i].offset), \
                g_v2d_pdpd_passthru_config_tbl[i].value, g_v2d_pdpd_passthru_config_tbl[i].mask, g_v2d_pdpd_passthru_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function for pdpd post_c center config
 * @param [in]      v2d_num, apb_num and value
 * @return          status value
 */
int pdpd_post_c_center_config(int v2d_num, int apb_num, int value)
{
    int i, rv = 0;
    pdpd_post_c_center_reg_t pdpd_post_c_center_reg;

    uint32_t C = value;
    ///< Post Filter Center Tap Coefficient
    ///< AccessType="RW" BitOffset="0" ResetValue="0x7FF"
    //uint32_t  : 20;
    ///< Reserved
    ///< AccessType="RO" BitOffset="12" ResetValue="None"

    pdpd_post_c_center_reg.C = C;

    g_v2d_pdpd_post_c_center_config_tbl[0].value = pdpd_post_c_center_reg.value;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_post_c_center_config_tbl[0].offset, \
                g_v2d_pdpd_post_c_center_config_tbl[0].value, g_v2d_pdpd_post_c_center_config_tbl[0].mask, \
                g_v2d_pdpd_post_c_center_config_tbl[0].name))
        return rv;
}

/**
 * @brief           Function for pdpd post filter config
 * @param [in]      v2d_num, apb_num, value
 * @return          status value
 */
int pdpd_post_c_reg_config(int v2d_num, int apb_num, int value)
{
    int i, rv = 0;
    pdpd_post_c_reg_t pdpd_post_c_reg;

/*
    typedef union {
      struct {
        uint32_t C : 12;
        ///< Post Filter Tap Coefficient
        ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
        uint32_t  : 20;
        ///< Reserved
        ///< AccessType="RO" BitOffset="12" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_post_c_reg_t;
*/
    uint32_t C = value;
    pdpd_post_c_reg.C = C;

    g_v2d_pdpd_post_c_config_tbl[0].value = pdpd_post_c_reg.value;

    for (i = 0; i < V2D_PDPD_MAX_POST_C_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_post_c_config_tbl[0].offset + (0x4 * i), \
                    g_v2d_pdpd_post_c_config_tbl[0].value, g_v2d_pdpd_post_c_config_tbl[0].mask, \
                    g_v2d_pdpd_post_c_config_tbl[0].name))
            return rv;
    }

}

/**
 * @brief           Function configuring the pdpd GMP static regsiter from host

 * @param [in]      V2d Id , APB Id ,num_gmp_terms and passthru delay value
 * @return          Status
 */
int pdpd_gmp_static_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value)
{
    int i, rv = 0;
    /* GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg;

/*
typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */

/* The below parameters need to be varied while testing , currently set to these specific values for specific testing*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;

#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    /* populating the entire applicable num_gmp_terms GMP_STATIC with the same value
     * this can be randomised later for the value and GMP positions*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    return rv;
}

#if LIVEIQ_SAMPLES // this is the working version of the function
/**
 * @brief           Function configuring the pdpd GMP static regsiter from host

 * @param [in]      V2d Id , APB Id ,num_gmp_terms and passthru delay value
 * @return          Status
 */
int pdpd_gmp_ddr_config_p5_1_2_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param)
{

  
    /*
    
?	At=0 : F(x(n)) = x(n) * LUT(mag(x(n)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY
?	SEL_LIN = PASSTHRU_DLY
?	CONJ_EN = 0
?	At=1 : F(x(n)) = x(n-q) * LUT(mag(x(n-q)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = SEL_MAG
?	CONJ_EN = 0
?	At=2 : F(x(n)) = x(n-q-m) * LUT(mag(x(n-q)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q + m
?	CONJ_EN = 0
?	At=3 : F(x(n)) = (x(n-q)^2) * conj(x(n-q-m)) * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q + m
?	SEL_SQU = PASSTHRU_DLY + q
?	CONJ_EN = 1
?	SQU_EN  = 1
?	SQU_SRC = 1
?	At=4 : F(x(n)) = x(n-q) * (mag(x(n-q-m)))^2 * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q
?	SEL_SQU = PASSTHRU_DLY + q + m
?	CONJ_EN = 0
?	SQU_EN  = 1
?	SQU_SRC = 0
?	At=5 : F(x(n)) = (x(n-q-m)^2) * conj(x(n-q)) * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q
?	SEL_SQU = PASSTHRU_DLY + q + m
?	CONJ_EN = 1
?	SQU_EN  = 1
?	SQU_SRC = 1
    
    */
 
/*

typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */
 
    /*
        typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;

*/

/*
gmp clut
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

*/

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)
*/    
    /*
    typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;
*/

/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */


    int i,rv = 0,j = 0;
    
    if (v2d_liveIQ_param->num_gmp_terms > V2D_PDPD_MAX_GMP_TERMS){
		printf("number of GMP terms >V2D_PDPD_MAX_GMP_TERMS");
		rv=-1;
		return rv;
	}
	
    if (v2d_liveIQ_param->num_ddr_terms > V2D_PDPD_MAX_DDR_TERMS){
		printf("number of DDR terms >V2D_PDPD_MAX_DDR_TERMS");
		rv=-1;
		return rv;
	}
	printf(" in wrapper: number of GMP = %d DDR  = %d terms \n",v2d_liveIQ_param->num_gmp_terms,v2d_liveIQ_param->num_ddr_terms);
	/* The below parameters are needed for GMP and DDR static configuration, based on the termTypes*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = 0;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = 0;
    uint32_t SEL_SQU = 0;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0; 
    
	/* GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg[V2D_PDPD_MAX_GMP_TERMS];
	/* GMP CLUT shadow */
	pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[V2D_PDPD_MAX_GMP_TERMS][65];
    /* GMP shift */
    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[V2D_PDPD_MAX_GMP_TERMS];	
	    
	for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++){  //32
	/* GMP Static */		
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
        pdpd_gmp_static_reg[i].value = 0;
	/* GMP CLUT shadow */        
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65

            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value = 0;
            pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[i][j].value = 0;
		}  
    /* GMP shift */			
        pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[i].value = 0;
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;			      
        g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value = 0;		        
		
	}    

    /* DDR static */
    pdpd_ddr_static_reg_t pdpd_ddr_static_reg[V2D_PDPD_MAX_DDR_TERMS];
    /* DDR C LUT Shadow */
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[V2D_PDPD_MAX_DDR_TERMS][65];    
    /* DDR shift */
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[V2D_PDPD_MAX_DDR_TERMS];
        
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++){ //16
		/* DDR static */
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
        pdpd_ddr_static_reg[i].value = 0;
		/* DDR C LUT Shadow */ 
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value = 0;            
            pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[i][j].value = 0;
        }	
    /* DDR shift */        
		pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[i].value = 0;
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;        	       
        g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value = 0;        
    }    


   /*update the paramters from liveIQ data
   The term types are all mixed up GMP and DDR> Care should be taken to upddate the static, C_LUT all correctly. */
   int gmp_index = 0, ddr_index = 0;	
   //for (i=0; i< (v2d_liveIQ_param->num_gmp_terms+v2d_liveIQ_param->num_ddr_terms);i++ ){
   for (i=0; i< (48);i++ ){
   //for (i=0; i< 1;i++ ){
		
		switch(v2d_liveIQ_param->term_types[i])
		{
			case PDPD_AT_0:  //GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly;
				SEL_LIN = v2d_liveIQ_param->passthru_dly;
				printf("v2d_liveIQ_param->passthru_dly = %d\n",v2d_liveIQ_param->passthru_dly);
				CONJ_EN = 0;
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				/* static */
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;
				
				/* lut_c_i and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
				}
 
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT =  v2d_liveIQ_param->lut_s[i]; // TBD the sign of this is till to be understood proerpy. in the actual HW, it is a right shift, postive value shift right, need to check it.
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				
				gmp_index++;						
				break;
			case PDPD_AT_1://GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = SEL_MAG;
				CONJ_EN = 0;		
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;					
				/* lut_c_ and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = v2d_liveIQ_param->lut_s[i]; // TBD the sign of this is till to be understood proerpy. in the actual HW, it is a right shift, postive value shift right, need to check it.
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;	


				printf("PDPD_AT_1 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);										
				gmp_index++;					
				break;
				
			case PDPD_AT_2://GMP or DDR but keeing it as GMP
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;	
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;	
				
				/* lut_c_ and lut_c_q to GMP_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = 	v2d_liveIQ_param->lut_s[i]; // TBD the sign of this is till to be understood proerpy. in the actual HW, it is a right shift, postive value shift right, need to check it.
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				printf("PDPD_AT_2 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);							
				gmp_index++;						
				break;
				
			case PDPD_AT_3: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;
				
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;
				}
				
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;
								
				ddr_index++;
				printf("JELLI LIVEIQ PDPD_AT_3\n"); 				
				break;
						
			case PDPD_AT_4: //DDR only
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;
				SQU_EN = 1;
				SQU_SRC = 0;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;	
				
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;
			
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				
				ddr_index++;
				break;	
				
			case PDPD_AT_5: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;	
				
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;
				
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;
				
				
				ddr_index++;
				
				break;	
				
			default :
            printf("ERROR: TermType[%d]=%d not supported \n",v2d_liveIQ_param->term_types[i],i);
            rv = -1;   // or is it 1 for error case ? jelli
            break;										
		}

	}


	
#if 1
	//GMP static
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
  
    // writing GMP C live
    
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /*(g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \  */
                        (g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    /* GMP shift  live */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                   /*  (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
  
    //writing DDR static
    
    /* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
	* this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    //g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg[0].value; 
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";


   for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }
        
	//writing DDR C live
	for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /* (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \ */
                        (g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    
    //DDR shift live
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    /* (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }

#else
	//GMP static
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    

    // writing GMP C Shadow
    
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    /* GMP shift */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
  
    //writing DDR static
    
    /* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
	* this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    //g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg[0].value; 
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";


   for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }
        
	//writing DDR C shadow
	for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    
    //DDR shift
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }

#endif //1
    return rv;
}

#endif //LIVEIQ_SAMPLES


#if LIVEIQ_SAMPLES 
/**
 * @brief           Function configuring the pdpd GMP static regsiter from host for 5gsps 

 * @param [in]      V2d Id , APB Id ,num_gmp_terms and passthru delay value
 * @return          Status
 */
int pdpd_gmp_ddr_config_iq_4_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param)
{
  
    /*
    
?	At=0 : F(x(n)) = x(n) * LUT(mag(x(n)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY
?	SEL_LIN = PASSTHRU_DLY
?	CONJ_EN = 0
?	At=1 : F(x(n)) = x(n-q) * LUT(mag(x(n-q)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = SEL_MAG
?	CONJ_EN = 0
?	At=2 : F(x(n)) = x(n-q-m) * LUT(mag(x(n-q)))
?	GMP or DDR
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q + m
?	CONJ_EN = 0
?	At=3 : F(x(n)) = (x(n-q)^2) * conj(x(n-q-m)) * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q + m
?	SEL_SQU = PASSTHRU_DLY + q
?	CONJ_EN = 1
?	SQU_EN  = 1
?	SQU_SRC = 1
?	At=4 : F(x(n)) = x(n-q) * (mag(x(n-q-m)))^2 * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q
?	SEL_SQU = PASSTHRU_DLY + q + m
?	CONJ_EN = 0
?	SQU_EN  = 1
?	SQU_SRC = 0
?	At=5 : F(x(n)) = (x(n-q-m)^2) * conj(x(n-q)) * LUT(mag(x(n-q)))
?	DDR only
?	SEL_MAG = PASSTHRU_DLY + q
?	SEL_LIN = PASSTHRU_DLY + q
?	SEL_SQU = PASSTHRU_DLY + q + m
?	CONJ_EN = 1
?	SQU_EN  = 1
?	SQU_SRC = 1
    
    */
 
/*

typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */
 
    /*
        typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;

*/

/*
gmp clut
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

*/

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)
*/    
    /*
    typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;
*/

/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */


    int i,rv = 0,j = 0;
    
    if (v2d_liveIQ_param->num_gmp_terms > V2D_PDPD_MAX_GMP_TERMS_4GSPS){
		printf("number of GMP terms >V2D_PDPD_MAX_GMP_TERMS_4GSPS");
		rv=-1;
		return rv;
	}
	
    if (v2d_liveIQ_param->num_ddr_terms > V2D_PDPD_MAX_DDR_TERMS_4GSPS){
		printf("number of DDR terms >V2D_PDPD_MAX_DDR_TERMS_4GSPS");
		rv=-1;
		return rv;
	}
	printf(" in 4gsps wrapper: number of GMP = %d DDR  = %d terms \n",v2d_liveIQ_param->num_gmp_terms,v2d_liveIQ_param->num_ddr_terms);
	/* The below parameters are needed for GMP and DDR static configuration, based on the termTypes*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = 0;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = 0;
    uint32_t SEL_SQU = 0;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0; 
    
	/* GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg[V2D_PDPD_MAX_GMP_TERMS];
	/* GMP CLUT shadow */
	pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[V2D_PDPD_MAX_GMP_TERMS][65];
    /* GMP shift */
    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[V2D_PDPD_MAX_GMP_TERMS];	
	    
	for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++){  //32
	/* GMP Static */		
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
        pdpd_gmp_static_reg[i].value = 0;
	/* GMP CLUT shadow */        
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65

            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value = 0;
            pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[i][j].value = 0;
		}  
    /* GMP shift */			
        pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[i].value = 0;
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;			      
        g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value = 0;		        
		
	}    

    /* DDR static */
    pdpd_ddr_static_reg_t pdpd_ddr_static_reg[V2D_PDPD_MAX_DDR_TERMS];
    /* DDR C LUT Shadow */
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[V2D_PDPD_MAX_DDR_TERMS][65];    
    /* DDR shift */
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[V2D_PDPD_MAX_DDR_TERMS];
        
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++){ //16
		/* DDR static */
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
        pdpd_ddr_static_reg[i].value = 0;
		/* DDR C LUT Shadow */ 
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value = 0;            
            pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[i][j].value = 0;
        }	
    /* DDR shift */        
		pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[i].value = 0;
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;        	       
        g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value = 0;        
    }    


   /*update the paramters from liveIQ data
   The term types are all mixed up GMP and DDR> Care should be taken to upddate the static, C_LUT all correctly.
   for the 4GSPS case, the duplication also need to be take care as per MAS */
   int gmp_index = 0, ddr_index = 0;	
   //for (i=0; i< (v2d_liveIQ_param->num_gmp_terms+v2d_liveIQ_param->num_ddr_terms);i++ ){
   for (i=0; i< (48);i++ ){
		if (gmp_index<16) {
		
			switch(v2d_liveIQ_param->term_types[i])
			{
			case PDPD_AT_0:  //GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly;
				SEL_LIN = v2d_liveIQ_param->passthru_dly;
				printf("v2d_liveIQ_param->passthru_dly = %d\n",v2d_liveIQ_param->passthru_dly);
				/* static */				
				CONJ_EN = 0;
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;				
				//duplciation to index+16
				printf("PDPD_AT_0 duplciation to gmp_index+16 =  %d\n",gmp_index+16);
				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-2;				
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;
				
				/* lut_c_i and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
										
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value	;				
				}
 
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT =  v2d_liveIQ_param->lut_s[i]; // TBD the sign of this is till to be understood proerpy. in the actual HW, it is a right shift, postive value shift right, need to check it.
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT =  v2d_liveIQ_param->lut_s[i];				
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;				
			
				gmp_index++;						
				break;
			case PDPD_AT_1://GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = SEL_MAG;
				CONJ_EN = 0;		
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;

				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;					
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-2;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;								
				/* lut_c_ and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value;					
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;	

				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;

				printf("PDPD_AT_1 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);										
				

				gmp_index++;					
				break;
				
			case PDPD_AT_2://GMP or DDR but keeing it as GMP
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;	
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;
				
				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-2;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;					
				
				/* lut_c_ and lut_c_q to GMP_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value;					
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;
								
				printf("PDPD_AT_2 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);							
				gmp_index++;						
				break;
				
			default :
            //printf("ERROR:  GMP TermType[%d]=%d not supported \n",v2d_liveIQ_param->term_types[i],i);
            //rv = -1;   // or is it 1 for error case ? jelli
            break;	
			}
		}

}		
#if 1		
		for (i=0; i< (48);i++ ){
			if (ddr_index<8){
			switch(v2d_liveIQ_param->term_types[i])
			{
			case PDPD_AT_3: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;

				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value; 
								
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;
					
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;					
				}
				
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;
												
				ddr_index++;
				printf("JELLI LIVEIQ PDPD_AT_3\n"); 				
				break;
						
			case PDPD_AT_4: //DDR only
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;
				SQU_EN = 1;
				SQU_SRC = 0;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;	


				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value;
								
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;			
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;
				
				ddr_index++;
				break;	
				
			case PDPD_AT_5: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value = 	pdpd_ddr_static_reg[ddr_index].value;
				
				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value;					
				
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;				
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;				
				
				ddr_index++;
				
				break;	
				
			default :
           // printf("ERROR: DDR TermType[%d]=%d not supported \n",v2d_liveIQ_param->term_types[i],i);
           // rv = -1;   // or is it 1 for error case ? jelli
            break;		
		}								
	}
	

	}

#endif //0

	// writing to the live regsiter directly
	//GMP static
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    

    // writing GMP C live
    
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /*(g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \  */
                        (g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    /* GMP shift  live*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                   /*  (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
    FILE *fp_i = NULL ,*fp_q = NULL;
	fp_i = fopen("liveIQ_FP_lut_c_i_4gsps.txt","w");	
	fp_q = fopen("liveIQ_FP_lut_c_q_4gsps.txt","w");   	

    //writing DDR static
    
    /* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
	* this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    //g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg[0].value; 
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";


   for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }
        
	//writing DDR C live
	for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /* (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \ */
                        (g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    
    //DDR shift live
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    /* (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }


    return rv;
}
#endif //LIVEIQ_SAMPLES
/**
 * @brief           Function configuring the pdpd GMP static regsiter from host

 * @param [in]      V2d Id , APB Id ,num_gmp_terms , passthru delay value and pdpd_in_rate
 * @return          Status
 */
int pdpd_gmp_static_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value, pdpd_rate_t pdpd_in_rate)
{
    int i, rv = 0;
    /*int 1;
    unsigned int APB_OFFSET_GEN(apb_num) = PDPD_BASE_ADDR_GEN(v2d_num,apb_num);
    * GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg;

/*
typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */

/* The below parameters need to be varied while testing , currently set to these specific values for specific testing*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    /* populating the entire applicable num_gmp_terms GMP_STATIC with the same value
     * this can be randomised later for the value and GMP positions*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    if (PDPD_RATE_IQ_4 == pdpd_in_rate)
    {
        ENABLE = 0x1;
        SEL_MAG = passthru_delay_value - 2;
        CONJ_EN = 0;
        SEL_LIN = passthru_delay_value - 2;
    }
    else if (PDPD_RATE_IQ_8 == pdpd_in_rate)
    {
        ENABLE = 0x1;
        SEL_MAG = passthru_delay_value - 4;
        CONJ_EN = 0;
        SEL_LIN = passthru_delay_value - 4;
    }
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if(rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    return rv;
}
#if LIVEIQ_SAMPLES // this is the working version of the function
/**
 * @brief           Function configuring the pdpd GMP static regsiter from host for 5gsps 

 * @param [in]      V2d Id , APB Id ,num_gmp_terms and passthru delay value
 * @return          Status
 */
int pdpd_gmp_ddr_config_iq_8_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param)
{
  
    /*
    
	At=0 : F(x(n)) = x(n) * LUT(mag(x(n)))
	GMP or DDR
	SEL_MAG = PASSTHRU_DLY
	SEL_LIN = PASSTHRU_DLY
	CONJ_EN = 0
	At=1 : F(x(n)) = x(n-q) * LUT(mag(x(n-q)))
	GMP or DDR
	SEL_MAG = PASSTHRU_DLY + q
	SEL_LIN = SEL_MAG
	CONJ_EN = 0
	At=2 : F(x(n)) = x(n-q-m) * LUT(mag(x(n-q)))
	GMP or DDR
	SEL_MAG = PASSTHRU_DLY + q
	SEL_LIN = PASSTHRU_DLY + q + m
	CONJ_EN = 0
	At=3 : F(x(n)) = (x(n-q)^2) * conj(x(n-q-m)) * LUT(mag(x(n-q)))
	DDR only
	SEL_MAG = PASSTHRU_DLY + q
	SEL_LIN = PASSTHRU_DLY + q + m
	SEL_SQU = PASSTHRU_DLY + q
	CONJ_EN = 1
	SQU_EN  = 1
	SQU_SRC = 1
	At=4 : F(x(n)) = x(n-q) * (mag(x(n-q-m)))^2 * LUT(mag(x(n-q)))
	DDR only
	SEL_MAG = PASSTHRU_DLY + q
	SEL_LIN = PASSTHRU_DLY + q
	SEL_SQU = PASSTHRU_DLY + q + m
	CONJ_EN = 0
	SQU_EN  = 1
	SQU_SRC = 0
	At=5 : F(x(n)) = (x(n-q-m)^2) * conj(x(n-q)) * LUT(mag(x(n-q)))
	DDR only
	SEL_MAG = PASSTHRU_DLY + q
	SEL_LIN = PASSTHRU_DLY + q
	SEL_SQU = PASSTHRU_DLY + q + m
	CONJ_EN = 1
	SQU_EN  = 1
	SQU_SRC = 1
    
    */
 
/*

typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */
 
    /*
        typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;

*/

/*
gmp clut
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

*/

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)
*/    
    /*
    typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;
*/

/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */


    int i,rv = 0,j = 0;
    
    if (v2d_liveIQ_param->num_gmp_terms > V2D_PDPD_MAX_GMP_TERMS_8GSPS){
		printf("number of GMP terms >V2D_PDPD_MAX_GMP_TERMS_8GSPS  %d\n ",v2d_liveIQ_param->num_gmp_terms);
		rv=-1;
		return rv;
	}
	
    if (v2d_liveIQ_param->num_ddr_terms > V2D_PDPD_MAX_GMP_TERMS_8GSPS){
		printf("number of DDR terms >V2D_PDPD_MAX_GMP_TERMS_8GSPS %d\n", v2d_liveIQ_param->num_ddr_terms);
		rv=-1;
		return rv;
	}
	printf(" in 8gsps wrapper: number of GMP = %d DDR  = %d terms \n",v2d_liveIQ_param->num_gmp_terms,v2d_liveIQ_param->num_ddr_terms);
	/* The below parameters are needed for GMP and DDR static configuration, based on the termTypes*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = 0;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = 0;
    uint32_t SEL_SQU = 0;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0; 
    
	/* GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg[V2D_PDPD_MAX_GMP_TERMS];
	/* GMP CLUT shadow */
	pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[V2D_PDPD_MAX_GMP_TERMS][65];
    /* GMP shift */
    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[V2D_PDPD_MAX_GMP_TERMS];	
	    
	for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++){  //32
	/* GMP Static */		
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
        pdpd_gmp_static_reg[i].value = 0;
	/* GMP CLUT shadow */        
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65

            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value = 0;
            pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[i][j].value = 0;
		}  
    /* GMP shift */			
        pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[i].value = 0;
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;			      
        g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value = 0;		        
		
	}    

    /* DDR static */
    pdpd_ddr_static_reg_t pdpd_ddr_static_reg[V2D_PDPD_MAX_DDR_TERMS];
    /* DDR C LUT Shadow */
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[V2D_PDPD_MAX_DDR_TERMS][65];    
    /* DDR shift */
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[V2D_PDPD_MAX_DDR_TERMS];
        
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++){ //16
		/* DDR static */
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
        pdpd_ddr_static_reg[i].value = 0;
		/* DDR C LUT Shadow */ 
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++){  //65
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
            g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value = 0;            
            pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[i][j].value = 0;
        }	
    /* DDR shift */        
		pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[i].value = 0;
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;        	       
        g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value = 0;        
    }    


   /*update the paramters from liveIQ data
   The term types are all mixed up GMP and DDR> Care should be taken to upddate the static, C_LUT all correctly.
   for the 4GSPS case, the duplication also need to be take care as per MAS */
   int gmp_index = 0, ddr_index = 0;	
   //for (i=0; i< (v2d_liveIQ_param->num_gmp_terms+v2d_liveIQ_param->num_ddr_terms);i++ ){
   for (i=0; i< (48);i++ ){
	   if(gmp_index<8){
		switch(v2d_liveIQ_param->term_types[i]){
				case PDPD_AT_0:  //GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly;
				SEL_LIN = v2d_liveIQ_param->passthru_dly;
				printf("v2d_liveIQ_param->passthru_dly = %d\n",v2d_liveIQ_param->passthru_dly);
				/* static */				
				CONJ_EN = 0;
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;				
				//duplciation to index+8
				printf("PDPD_AT_0 duplciation to gmp_index+8 =  %d\n",gmp_index+16);
				pdpd_gmp_static_reg[gmp_index+8].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+8].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+8].SEL_LIN= SEL_LIN-2;				
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+8].value = pdpd_gmp_static_reg[gmp_index+8].value;
				
				//duplciation to index+16
				printf("PDPD_AT_0 duplciation to gmp_index+16 =  %d\n",gmp_index+16);
				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-4;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-4;				
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;

				//duplciation to index+24
				printf("PDPD_AT_0 duplciation to gmp_index24 =  %d\n",gmp_index+16);
				pdpd_gmp_static_reg[gmp_index+24].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+24].SEL_MAG = SEL_MAG-6;
				pdpd_gmp_static_reg[gmp_index+24].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+24].SEL_LIN= SEL_LIN-6;				
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+24].value = pdpd_gmp_static_reg[gmp_index+24].value;								
				/* lut_c_i and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
//+8
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+8][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].value	;
					
//16					
															
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value	;	
//+24	

					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+24][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].value	;							
				}
 
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT =  v2d_liveIQ_param->lut_s[i]; // TBD the sign of this is till to be understood proerpy. in the actual HW, it is a right shift, postive value shift right, need to check it.
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].SHIFT =  v2d_liveIQ_param->lut_s[i];				
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+8].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT =  v2d_liveIQ_param->lut_s[i];				
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].SHIFT =  v2d_liveIQ_param->lut_s[i];				
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+24].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].value;								
			
				gmp_index++;						
				break;
			case PDPD_AT_1://GMP or DDR but keeing it as GMP
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = SEL_MAG;
				CONJ_EN = 0;		
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;

				pdpd_gmp_static_reg[gmp_index+8].ENABLE = ENABLE;					
				pdpd_gmp_static_reg[gmp_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+8].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+8].SEL_LIN= SEL_LIN-2;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+8].value = pdpd_gmp_static_reg[gmp_index+8].value;
				
				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;					
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-4;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-4;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;
				

				pdpd_gmp_static_reg[gmp_index+24].ENABLE = ENABLE;					
				pdpd_gmp_static_reg[gmp_index+24].SEL_MAG = SEL_MAG-6;
				pdpd_gmp_static_reg[gmp_index+24].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+24].SEL_LIN= SEL_LIN-6;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+24].value = pdpd_gmp_static_reg[gmp_index+24].value;																
				/* lut_c_ and lut_c_q*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+8][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].value;	
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value;	
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+24][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].value;															
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;	

				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+8].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;				

				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].SHIFT = v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+24].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].value;
				printf("PDPD_AT_1 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);										
				

				gmp_index++;					
				break;
				
			case PDPD_AT_2://GMP or DDR but keeing it as GMP
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;	
				pdpd_gmp_static_reg[gmp_index].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index].SEL_MAG = SEL_MAG;
				pdpd_gmp_static_reg[gmp_index].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index].SEL_LIN= SEL_LIN;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index].value = pdpd_gmp_static_reg[gmp_index].value;
				
				pdpd_gmp_static_reg[gmp_index+8].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+8].SEL_MAG = SEL_MAG-2;
				pdpd_gmp_static_reg[gmp_index+8].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+8].SEL_LIN= SEL_LIN-2;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+8].value = pdpd_gmp_static_reg[gmp_index+8].value;

				pdpd_gmp_static_reg[gmp_index+16].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+16].SEL_MAG = SEL_MAG-4;
				pdpd_gmp_static_reg[gmp_index+16].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+16].SEL_LIN= SEL_LIN-4;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+16].value = pdpd_gmp_static_reg[gmp_index+16].value;
				
				pdpd_gmp_static_reg[gmp_index+24].ENABLE = ENABLE;
				pdpd_gmp_static_reg[gmp_index+24].SEL_MAG = SEL_MAG-6;
				pdpd_gmp_static_reg[gmp_index+24].CONJ_EN = CONJ_EN;
				pdpd_gmp_static_reg[gmp_index+24].SEL_LIN= SEL_LIN-6;
				g_v2d_pdpd_gmp_static_config_tbl[gmp_index+24].value = pdpd_gmp_static_reg[gmp_index+24].value;													
				
				/* lut_c_ and lut_c_q to GMP_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index][j].value;
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+8][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+8][j].value;	
					
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+16][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+16][j].value;
					
					
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[gmp_index+24][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg[gmp_index+24][j].value;														
				}
				/* shift */
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+8].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+8].value;

				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+16].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+16].value;
				
				pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].SHIFT = 	v2d_liveIQ_param->lut_s[i]; 
				g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[gmp_index+24].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg[gmp_index+24].value	;			
								
				printf("PDPD_AT_2 v2d_liveIQ_param->passthru_dly = %d, gmp_index=%d\n",v2d_liveIQ_param->passthru_dly,gmp_index);							
				gmp_index++;						
				break;
			case PDPD_AT_3: //DDR only . no action
			case PDPD_AT_4: //DDR only
			case PDPD_AT_5: //DDR only

				break;				
			default :
            printf("ERROR: TermType[%d]=%d not supported \n",v2d_liveIQ_param->term_types[i],i);
            rv = -1;   // or is it 1 for error case ? 
            break;						
			}
		}
					printf("INFO: 8gsps GMP switch finished i=%d \n",i);
		}
		
		printf("INFO: 8gsps GMP loop finished  \n");
		
		for (i=0; i< (48);i++ ){
			printf("INFO: 8gsps DDR loop \n");
			if(ddr_index<4){
			switch(v2d_liveIQ_param->term_types[i]){			
			case PDPD_AT_3: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i] + v2d_liveIQ_param->m_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;

				pdpd_ddr_static_reg[ddr_index+4].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+4].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+4].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+4].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+4].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+4].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+4].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+4].value	 = 	pdpd_ddr_static_reg[ddr_index+4].value; 
				
				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-4;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-4;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-4;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value; 
				
				pdpd_ddr_static_reg[ddr_index+12].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+12].SEL_MAG = SEL_MAG-6;
				pdpd_ddr_static_reg[ddr_index+12].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+12].SEL_LIN = SEL_LIN-6;
				pdpd_ddr_static_reg[ddr_index+12].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+12].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+12].SEL_SQU = SEL_SQU-6;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+12].value = 	pdpd_ddr_static_reg[ddr_index+12].value; 								
								
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;
					
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+4][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].value;	
					
					
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;
					
					
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+12][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].value;														
				}
				
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+4].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].value;
				
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;
				
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+12].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].value;								
				printf("PDPD_AT_3 v2d_liveIQ_param->passthru_dly = %d, ddr_index=%d\n",v2d_liveIQ_param->passthru_dly,ddr_index);													
				ddr_index++;
			
				break;
						
			case PDPD_AT_4: //DDR only
	
				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 0 ;
				SQU_EN = 1;
				SQU_SRC = 0;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value	 = 	pdpd_ddr_static_reg[ddr_index].value;	


				pdpd_ddr_static_reg[ddr_index+4].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+4].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+4].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+4].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+4].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+4].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+4].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+4].value	 = 	pdpd_ddr_static_reg[ddr_index+4].value;
				
				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-4;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-4;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-4;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value;
				
				pdpd_ddr_static_reg[ddr_index+12].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+12].SEL_MAG = SEL_MAG-6;
				pdpd_ddr_static_reg[ddr_index+12].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+12].SEL_LIN = SEL_LIN-6;
				pdpd_ddr_static_reg[ddr_index+12].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+12].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+12].SEL_SQU = SEL_SQU-6;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+12].value	 = 	pdpd_ddr_static_reg[ddr_index+12].value;								
								
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+4][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].value;	
					

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;	
					

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+12][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].value;													
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+4].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].value;
				
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;
				
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+12].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].value;								
				printf("PDPD_AT_4 v2d_liveIQ_param->passthru_dly = %d, ddr_index=%d\n",v2d_liveIQ_param->passthru_dly,ddr_index);					
				ddr_index++;
				break;	
				
			case PDPD_AT_5: //DDR only

				SEL_MAG = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_LIN = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i];
				SEL_SQU = v2d_liveIQ_param->passthru_dly + v2d_liveIQ_param->q_delay[i]+ v2d_liveIQ_param->m_delay[i];
				CONJ_EN = 1 ;
				SQU_EN = 1;
				SQU_SRC = 1;	
				
				pdpd_ddr_static_reg[ddr_index].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index].SEL_MAG = SEL_MAG;
				pdpd_ddr_static_reg[ddr_index].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index].SEL_LIN = SEL_LIN;
				pdpd_ddr_static_reg[ddr_index].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index].SEL_SQU = SEL_SQU;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index].value = 	pdpd_ddr_static_reg[ddr_index].value;
				
				pdpd_ddr_static_reg[ddr_index+4].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+4].SEL_MAG = SEL_MAG-2;
				pdpd_ddr_static_reg[ddr_index+4].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+4].SEL_LIN = SEL_LIN-2;
				pdpd_ddr_static_reg[ddr_index+4].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+4].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+4].SEL_SQU = SEL_SQU-2;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+4].value	 = 	pdpd_ddr_static_reg[ddr_index+4].value;
				
				pdpd_ddr_static_reg[ddr_index+8].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+8].SEL_MAG = SEL_MAG-4;
				pdpd_ddr_static_reg[ddr_index+8].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+8].SEL_LIN = SEL_LIN-4;
				pdpd_ddr_static_reg[ddr_index+8].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+8].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+8].SEL_SQU = SEL_SQU-4;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+8].value	 = 	pdpd_ddr_static_reg[ddr_index+8].value;
				
				pdpd_ddr_static_reg[ddr_index+12].ENABLE = ENABLE;
				pdpd_ddr_static_reg[ddr_index+12].SEL_MAG = SEL_MAG-6;
				pdpd_ddr_static_reg[ddr_index+12].CONJ_EN = CONJ_EN;
				pdpd_ddr_static_reg[ddr_index+12].SEL_LIN = SEL_LIN-6;
				pdpd_ddr_static_reg[ddr_index+12].SQU_EN = SQU_EN;
				pdpd_ddr_static_reg[ddr_index+12].SQU_SRC = SQU_SRC;
				pdpd_ddr_static_reg[ddr_index+12].SEL_SQU = SEL_SQU-6;
				g_v2d_pdpd_ddr_static_config_tbl[ddr_index+12].value	 = 	pdpd_ddr_static_reg[ddr_index+12].value;													
				
				/* lut_c_ and lut_c_q to DDR_C_SHADOW*/
				for (j=0;j<65;j++){
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index][j].value;

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+4][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+4][j].value;	
					

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+8][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+8][j].value;
					
					

					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].I = v2d_liveIQ_param->lut_c_i[i][j];
					pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].Q = v2d_liveIQ_param->lut_c_q[i][j];
					
					g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[ddr_index+12][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg[ddr_index+12][j].value;													
				}
				//DDR shift
				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index].value;

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+4].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+4].value;				


				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+8].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+8].value;	
				

				pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].SHIFT = v2d_liveIQ_param->lut_s[i];
				g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[ddr_index+12].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg[ddr_index+12].value;
				
				printf("PDPD_AT_5 v2d_liveIQ_param->passthru_dly = %d, ddr_index=%d\n",v2d_liveIQ_param->passthru_dly,ddr_index);										
				ddr_index++;
				
				break;	
			case PDPD_AT_0: //GMP only . no action
			case PDPD_AT_1: //GMP only
			case PDPD_AT_2: //GMP only

				break;
			default :
            printf("ERROR: TermType[%d]=%d not supported \n",v2d_liveIQ_param->term_types[i],i);
            rv = -1;   // or is it 1 for error case ? 
            break;										
		}
	}

	}



	// writing to the live regsiter directly
	//GMP static
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    

    // writing GMP C live
    
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /*(g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \  */
                        (g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    /* GMP shift  live*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                   /*  (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
  
    //writing DDR static
    
    /* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
	* this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    //g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg[0].value; 
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";


   for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }
        
	//writing DDR C live
	for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        /* (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \ */
                        (g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    
    //DDR shift live
    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    /* (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \ */
                    (g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }


    return rv;
}
#endif //LIVEIQ_SAMPLES
/**
 * @brief           Function configuring the pdpd GMP static regsiter from host

 * @param [in]      V2d Id , APB Id ,num_gmp_terms and passthru delay value
 * @return          Status
 */
int pdpd_gmp_static_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value)
{
    int i, rv = 0;
    /*int 1;
    unsigned int APB_OFFSET_GEN(apb_num) = PDPD_BASE_ADDR_GEN(v2d_num,apb_num);
    * GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg;

/*
typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */

/* The below parameters need to be varied while testing , currently set to these specific values for specific testing*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    /* populating the entire applicable num_gmp_terms GMP_STATIC with the same value
     * this can be randomised later for the value and GMP positions*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    ENABLE = 0x1;
    SEL_MAG = passthru_delay_value - 2;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 2;
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    for (i = 8; i < (8 + num_gmp_terms); i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    ENABLE = 0x1;
    SEL_MAG = passthru_delay_value - 4;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 4;
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    ENABLE = 0x1;
    SEL_MAG = passthru_delay_value - 6;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 6;
#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg.SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    for (i = 24; i < (24 + num_gmp_terms); i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the DDR static regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms and passthru delay
 * @return           Status
 */
int pdpd_ddr_static_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value)
{
    int i, rv = 0;

    /* DDR  Static */

/*
    typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;
*/

    pdpd_ddr_static_reg_t pdpd_ddr_static_reg ;

    uint32_t ENABLE = 1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0;
    uint32_t SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

/* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
 * this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg.value; //set to 0 right now as no DDR term is configured
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the DDR static regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms, passthru delay value and pdpd_in_rate
 * @return           Status
 */
int pdpd_ddr_static_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value, pdpd_rate_t pdpd_in_rate)
{
    int i, rv = 0;

    /* DDR  Static */

/*
    typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;
*/

    pdpd_ddr_static_reg_t pdpd_ddr_static_reg ;

    uint32_t ENABLE = 1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0;
    uint32_t SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

/* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
 * this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg.value; //set to 0 right now as no DDR term is configured
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";

    printf("DDR_STATIC_VALUE: %x\n", pdpd_ddr_static_reg.value);

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    if (PDPD_RATE_IQ_4 == pdpd_in_rate)
    {
        ENABLE = 1;
        SEL_MAG = passthru_delay_value - 2;
        CONJ_EN = 0;
        SEL_LIN = passthru_delay_value - 2;
        SQU_EN = 0;
        SQU_SRC = 0;
        SEL_SQU = 0;
    }
    else if (PDPD_RATE_IQ_8 == pdpd_in_rate)
    {
        ENABLE = 1;
        SEL_MAG = passthru_delay_value - 4;
        CONJ_EN = 0;
        SEL_LIN = passthru_delay_value - 4;
        SQU_EN = 0;
        SQU_SRC = 0;
        SEL_SQU = 0;
    }

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }

    return rv;
}

/**
 * @brief           Function configuring the DDR static regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and  num_ddr_terms
 * @return           Status
 */
int pdpd_ddr_static_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value)
{
    int i, rv = 0;

    /* DDR  Static */

/*
    typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;
*/

    pdpd_ddr_static_reg_t pdpd_ddr_static_reg ;

    uint32_t ENABLE = 1;
    uint32_t SEL_MAG = passthru_delay_value;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = passthru_delay_value;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0;
    uint32_t SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

/* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
 * this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg.value; //set to 0 right now as no DDR term is configured
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";

    printf("DDR_STATIC_VALUE: %x\n", pdpd_ddr_static_reg.value);

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    ENABLE = 1;
    SEL_MAG = passthru_delay_value - 4;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 4;
    SQU_EN = 0;
    SQU_SRC = 0;
    SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    ENABLE = 1;
    SEL_MAG = passthru_delay_value - 2;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 2;
    SQU_EN = 0;
    SQU_SRC = 0;
    SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

    for (i = 4; i < (4 + num_ddr_terms); i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    ENABLE = 1;
    SEL_MAG = passthru_delay_value - 6;
    CONJ_EN = 0;
    SEL_LIN = passthru_delay_value - 6;
    SQU_EN = 0;
    SQU_SRC = 0;
    SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

    for (i = 12; i < (12 + num_ddr_terms); i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }

    return rv;
}
/**
 * @brief           Function configuring the GMP Dynamic reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms, i_value and q_value
 * @return          Status
 */
int pdpd_gmp_dynamic_live_gmp_c_config(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

  /*
   *
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_live_gmp_c_live_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_RD_MASK (0x1fff1fffU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_WR_MASK (0x1fff1fffU)
* */
    pdpd_gmp_dynamic_live_gmp_c_live_reg_t pdpd_gmp_dynamic_live_gmp_c_live_reg;
    uint32_t Q = q_value;
    uint32_t I = i_value;
#if 0
    pdpd_gmp_dynamic_live_gmp_c_live_reg.Q = Q;
    pdpd_gmp_dynamic_live_gmp_c_live_reg.I = I;
#else
    pdpd_gmp_dynamic_live_gmp_c_live_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    /* initialuse all coeffcients nad SHIFT values to zero , then set only the required coefficinets as explained above
     * then do the regwrite at the correct offset */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value = 0;
        }
    }

    //the first two coefficients set for 2^11 only for the real values, the rest all set to zero. this is as per the MATLAB model
    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value = pdpd_gmp_dynamic_live_gmp_c_live_reg.value;
        }
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[i][j].value, \
                        g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].mask, \
                        g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;
}


/**
 * @brief           Function configuring the GMP Dynamic live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms and shift_val
 * @return          Status
 */
int pdpd_gmp_dynamic_live_gmp_shift_live_reg_config(int v2d_num, int apb_num, int num_gmp_terms, int shift_val)
{
    int i, rv = 0;

/*

typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_live_gmp_shift_live_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_RD_MASK (0x0000000fU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_WR_MASK (0x0000000fU)
*/

    pdpd_gmp_dynamic_live_gmp_shift_live_reg_t pdpd_gmp_dynamic_live_gmp_shift_live_reg ;
    uint32_t SHIFT = shift_val;

    pdpd_gmp_dynamic_live_gmp_shift_live_reg.SHIFT = SHIFT ;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value = pdpd_gmp_dynamic_live_gmp_shift_live_reg.value;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[0].name))
            return rv;
    }
    return rv;
}
/**
 * @brief           Function configuring the DDR  Dynamic Shift Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms and shift value
 * @return          Status
 */
int pdpd_ddr_dynamic_live_ddr_shift_live_reg_config(int v2d_num, int apb_num, int num_ddr_terms, int shift_val)
{
    int i, rv = 0;
/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_live_ddr_shift_live_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */
    uint32_t SHIFT = shift_val;
    pdpd_ddr_dynamic_live_ddr_shift_live_reg_t pdpd_ddr_dynamic_live_ddr_shift_live_reg ;
    pdpd_ddr_dynamic_live_ddr_shift_live_reg.SHIFT = SHIFT;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value = pdpd_ddr_dynamic_live_ddr_shift_live_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[0].name))
            return rv;
    }

    return rv;
}

/**
 * @brief           Function configuring the DDR  Dynamic Coeff Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id, num_ddr_terms, i_value and q_value
 * @return          Status
 */
int pdpd_ddr_dynamic_live_ddr_c_live_reg_config(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_live_ddr_c_live_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)

* */
    uint32_t Q = q_value;
    uint32_t I = i_value;

    pdpd_ddr_dynamic_live_ddr_c_live_reg_t pdpd_ddr_dynamic_live_ddr_c_live_reg;
#if 0
    pdpd_ddr_dynamic_live_ddr_c_live_reg.Q  = Q;
    pdpd_ddr_dynamic_live_ddr_c_live_reg.I = I;
#else
    pdpd_ddr_dynamic_live_ddr_c_live_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value = 0;
        }
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value = pdpd_ddr_dynamic_live_ddr_c_live_reg.value;
        }
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;
}

/**
 * @brief           Function configuring the NL_C reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          Status
 */
int pdpd_nl_c_live_reg_config(int v2d_num, int apb_num)
{
    int i, rv = 0;
    /*

    typedef union {
      struct {
        uint32_t NL : 13;
        ///< Nonlinear Magnitude LUT Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 19;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_nl_c_live_reg_t;

    #define PDPD_NL_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_NL_C_LIVE_RD_MASK (0x00001fffU)
    #define PDPD_NL_C_LIVE_WR_MASK (0x00001fffU)
    * PDPD_NL_C_LIVE0_OFFSET
    *
    * */
    pdpd_nl_c_live_reg_t pdpd_nl_c_live_reg;
    uint32_t NL = NL_C_VALUE;
    pdpd_nl_c_live_reg.NL = NL;

    for (i = 0; i < V2D_PDPD_MAX_C_LUT_SEGMENTS ; i++)
    {
        g_pdpd_nl_c_live_config_tbl[i].value = pdpd_nl_c_live_reg.value;

        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (g_pdpd_nl_c_live_config_tbl[0].offset + (4 * i)), \
                    g_pdpd_nl_c_live_config_tbl[i].value, g_pdpd_nl_c_live_config_tbl[0].mask, g_pdpd_nl_c_live_config_tbl[0].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the GMP shdw reg from host
 * @param [in]      V2d Id , APB Id ,num_gmp_terms, i_value and q_value
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

  /*
   *
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_RD_MASK (0x1fff1fffU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_WR_MASK (0x1fff1fffU)
* */
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg;

    uint32_t Q = q_value;
    uint32_t I = i_value;
#if 0
    pdpd_gmp_dynamic_live_gmp_c_live_reg.Q = Q;
    pdpd_gmp_dynamic_live_gmp_c_live_reg.I = I;
#else
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    /* initialuse all coeffcients nad SHIFT values to zero , then set only the required coefficinets as explained above
     * then do the regwrite at the correct offset */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    //the first two coefficients set for 2^11 only for the real values, the rest all set to zero. this is as per the MATLAB model
    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value;
        }
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;
}


/**
 * @brief           Function configuring the GMP shdw reg from host
 * @param [in]      V2d Id , APB Id ,num_gmp_terms, i_value and q_value
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

  /*
   *
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_RD_MASK (0x1fff1fffU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_WR_MASK (0x1fff1fffU)
* */
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg;

    uint32_t Q = q_value;
    uint32_t I = i_value;
#if 0
    pdpd_gmp_dynamic_live_gmp_c_live_reg.Q = Q;
    pdpd_gmp_dynamic_live_gmp_c_live_reg.I = I;
#else
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    /* initialuse all coeffcients nad SHIFT values to zero , then set only the required coefficinets as explained above
     * then do the regwrite at the correct offset */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    //the first two coefficients set for 2^11 only for the real values, the rest all set to zero. this is as per the MATLAB model
    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value;
        }
    }

    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value;
        }
    }


    for (i = 0; i < num_gmp_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }

    // Write the Duplication values
    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                         g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }

    return rv;
}


/**
 * @brief           Function configuring the GMP shdw reg from host
 * @param [in]      V2d Id , APB Id ,num_gmp_terms, i_value and q_value
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value)
{
    int i, j, k, rv = 0;

  /*
   *
typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_RD_MASK (0x1fff1fffU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_C_LIVE_WR_MASK (0x1fff1fffU)
* */
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg;

    uint32_t Q = q_value;
    uint32_t I = i_value;
#if 0
    pdpd_gmp_dynamic_live_gmp_c_live_reg.Q = Q;
    pdpd_gmp_dynamic_live_gmp_c_live_reg.I = I;
#else
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    /* initialuse all coeffcients nad SHIFT values to zero , then set only the required coefficinets as explained above
     * then do the regwrite at the correct offset */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (k = 0; k < 32; k = (k + 8))
    {
        for (i = 0; i < num_gmp_terms; i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i + k][j].value = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value;
            }

        }
    }

    for (k = 0; k < 32; k = (k + 8))
    {
        for (i = 0; i < num_gmp_terms; i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                            (g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * (i + k)) + (4 * j)), \
                             g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i + k][j].value, \
                             g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                             g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                    return rv;
            }
        }
    }

    return rv;
}


/**
 * @brief           Function configuring the DDR  Dynamic Coeff Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id, num_ddr_terms, i_value and q_value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)

* */
    uint32_t Q = q_value;
    uint32_t I = i_value;

    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg;
#if 0
    pdpd_ddr_dynamic_live_ddr_c_live_reg.Q  = Q;
    pdpd_ddr_dynamic_live_ddr_c_live_reg.I = I;
#else
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value;
        }
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;
}


/**
 * @brief           Function configuring the DDR  Dynamic Coeff Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id, num_ddr_terms, i_value and q_value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value)
{
    int i, j, rv = 0;

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)

* */
    uint32_t Q = q_value;
    uint32_t I = i_value;

    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg;
#if 0
    pdpd_ddr_dynamic_live_ddr_c_live_reg.Q  = Q;
    pdpd_ddr_dynamic_live_ddr_c_live_reg.I = I;
#else
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value;
        }
    }

    // For Duplication
    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value;
        }
    }


    for (i = 0; i < num_ddr_terms; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }

    // For Duplication
    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }


    return rv;
}


/**
 * @brief           Function configuring the DDR  Dynamic Coeff Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id, num_ddr_terms, i_value and q_value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value)
{
    int i, j, k, rv = 0;

/*

    typedef union {
      struct {
        uint32_t Q : 13;
        ///< Quadrature Phase Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
        uint32_t I : 13;
        ///< In Phase Coefficient
        ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
        uint32_t  : 3;
        ///< Reserved
        ///< AccessType="RO" BitOffset="29" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_C_LIVE_RD_MASK (0x1fff1fffU)

* */
    uint32_t Q = q_value;
    uint32_t I = i_value;

    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg;
#if 0
    pdpd_ddr_dynamic_live_ddr_c_live_reg.Q  = Q;
    pdpd_ddr_dynamic_live_ddr_c_live_reg.I = I;
#else
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (k = 0; k < 16; k = (k + 4))
    {
        for (i = 0; i < num_ddr_terms; i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i + k][j].value = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value;
            }
        }

    }

    for (k = 0; k < 16; k = (k + 4))
    {
        for (i = 0; i < num_ddr_terms; i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                            (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * (i + k)) + (4 * j)), \
                            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i + k][j].value, \
                            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                    return rv;
            }
        }
    }


    return rv;
}


/**
 * @brief           Function configuring the GMP Dynamic live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms and shift_val
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int shift_val)
{
    int i, rv = 0;

/*

typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_RD_MASK (0x0000000fU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_WR_MASK (0x0000000fU)
*/

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg ;
    uint32_t SHIFT = shift_val;

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.SHIFT = SHIFT ;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.value;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
    return rv;
}


/**
 * @brief           Function configuring the GMP Dynamic live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms and shift_val
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int shift_val)
{
    int i, rv = 0;

/*

typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_RD_MASK (0x0000000fU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_WR_MASK (0x0000000fU)
*/

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg ;
    uint32_t SHIFT = shift_val;

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.SHIFT = SHIFT ;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.value;
    }

    // for Duplication
    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.value;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }

    // for Duplication
    for (i = 16; i < (16 + num_gmp_terms); i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + \
                    APB_OFFSET_GEN(apb_num) + (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the GMP Dynamic live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms and shift_val
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int shift_val)
{
    int i, k, rv = 0;

/*

typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_RD_MASK (0x0000000fU)
#define PDPD_GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_WR_MASK (0x0000000fU)
*/

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg ;
    uint32_t SHIFT = shift_val;

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.SHIFT = SHIFT ;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;
    }

    for (k = 0; k < 32; k = (k + 8))
    {
        for (i = 0; i < num_gmp_terms; i++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i + k].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.value;
        }
    }


    for (k = 0; k < 32; k = (k + 8))
    {
        for (i = 0; i < num_gmp_terms; i++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * (i + k))), \
                        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i + k].value, \
                        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
                return rv;
        }
    }

    return rv;
}


/**
 * @brief           Function configuring the DDR  Dynamic Shift Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms and shift value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int shift_val)
{
    int i, rv = 0;
/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */
    uint32_t SHIFT = shift_val;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg ;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.SHIFT = SHIFT;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.value;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }

    return rv;
}

/**
 * @brief           Function configuring the DDR  Dynamic Shift Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms and shift value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int shift_val)
{
    int i, rv = 0;
/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */
    uint32_t SHIFT = shift_val;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg ;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.SHIFT = SHIFT;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.value;
    }

    // For Duplication
    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.value;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }

    // For Duplication
    for (i = 8; i < (8 + num_ddr_terms); i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                    (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the DDR  Dynamic Shift Live reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_ddr_terms and shift value
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int shift_val)
{
    int i, k, rv = 0;
/*
 *
    typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
      uint32_t value;
    } pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_WR_MASK (0x0000000fU)
 * */
    uint32_t SHIFT = shift_val;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg ;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.SHIFT = SHIFT;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;
    }

    for (k = 0; k < 16; k = (k + 4))
    {
        for (i = 0; i < num_ddr_terms; i++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i + k].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.value;
        }
    }


    for (k = 0; k < 16; k = (k + 4))
    {
        for (i = 0; i < num_ddr_terms; i++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + \
                        (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * (i + k))), \
                        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i + k].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
                return rv;
        }
    }


    return rv;
}


/**
 * @brief           Function configuring Extra Static Config reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          Status
 */
int pdpd_extra_static_reg_config (int v2d_num, int apb_num, int passthru_delay)
{
    int i, rv = 0;
/*
 *
 * PDPD_EXTRA_STATIC_OFFSET
 *
typedef union {
  struct {
    uint32_t EN : 1;
    ///< 0: The extra terms are not enabled
    ///< 1: The extra terms are enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL : 7;
    ///< Extra terms delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t ADVANCE : 1;
    ///0: Extra terms are delayed with respect to the other terms by the SEL value
    ///1: Extra terms are advanced with respect to the other terms by the SEL value
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t  : 23;
    ///< Reserved
    ///< AccessType="RO" BitOffset="9" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_extra_static_reg_t;

#define PDPD_EXTRA_STATIC_DEFAULT (0x00000000U)
#define PDPD_EXTRA_STATIC_RD_MASK (0x000000ffU)
#define PDPD_EXTRA_STATIC_WR_MASK (0x000000ffU)
* PDPD.EXTRA_STATIC=0x15 -->0001 0101 from Sanojs model
*
*/
    pdpd_extra_static_reg_t pdpd_extra_static_reg;

    uint32_t EN = 1;
    /* Extra Terms Enable
    0: The extra terms are not enabled
    1: The extra terms are enabled */
    uint32_t SEL = passthru_delay;
    /* Select Delay
    Extra terms delay */
    uint32_t ADVANCE = 0;

    pdpd_extra_static_reg.EN = EN;
    pdpd_extra_static_reg.SEL = SEL;
    pdpd_extra_static_reg.ADVANCE = ADVANCE;

    g_v2d_pdpd_extra_static_config_tbl[0].value = pdpd_extra_static_reg.value;

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_extra_static_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_extra_static_config_tbl[i].offset), \
                g_v2d_pdpd_extra_static_config_tbl[i].value, g_v2d_pdpd_extra_static_config_tbl[i].mask, \
                g_v2d_pdpd_extra_static_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient regsiter from host
 * @param [in]      V2d Id , APB Id, i_value and q_value
 * @return          status
 */
int pdpd_passthru_c_live_reg_config(int v2d_num, int apb_num, int i_value, int q_value)
{
    int i, rv = 0;
    pdpd_passthru_c_shdw_reg_t pdpd_passthru_c_live_reg;
    /* rom MATLAB
     *  passthru_coeff_i = 2^13;  % real part
        passthru_coeff_q = 0;  % imaginary part
     * */

    uint32_t Q  = q_value; //: 15;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="15" ResetValue="None"

    uint32_t I  = i_value; //: 15;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="31" ResetValue="None"

    pdpd_passthru_c_live_reg.Q = Q;
    pdpd_passthru_c_live_reg.I = I;

#if 0
    g_v2d_pdpd_passthru_config_tbl[0].value = bpdpd_passthru_c_shdw_reg.value; // shadow register
    g_v2d_pdpd_passthru_config_tbl[1].value = bpdpd_passthru_c_shdw_reg.value; // live register
#else
    g_v2d_pdpd_passthru_live_config_tbl[0].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
    printf ("passthru shdw reg: %x\n", g_v2d_pdpd_passthru_live_config_tbl[0].value);
#endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_passthru_live_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_passthru_live_config_tbl[i].offset), \
                g_v2d_pdpd_passthru_live_config_tbl[i].value, g_v2d_pdpd_passthru_live_config_tbl[i].mask, \
                g_v2d_pdpd_passthru_live_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient regsiter from host
 * @param [in]      V2d Id , APB Id, i_value and q_value
 * @return          status
 */
int pdpd_passthru_c_shdw_reg_config(int v2d_num, int apb_num, int i_value, int q_value)
{
    int i, rv = 0;
    pdpd_passthru_c_shdw_reg_t pdpd_passthru_c_shdw_reg;
    /* rom MATLAB
     *  passthru_coeff_i = 2^13;  % real part
        passthru_coeff_q = 0;  % imaginary part
     * */

    uint32_t Q  = q_value; //: 15;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="15" ResetValue="None"

    uint32_t I  = i_value; //: 15;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    //uint32_t  : 1;
    ///< Reserved
    ///< AccessType="RO" BitOffset="31" ResetValue="None"

    pdpd_passthru_c_shdw_reg.Q = Q;
    pdpd_passthru_c_shdw_reg.I = I;

#if 0
    g_v2d_pdpd_passthru_config_tbl[0].value = bpdpd_passthru_c_shdw_reg.value; // shadow register
    g_v2d_pdpd_passthru_config_tbl[1].value = bpdpd_passthru_c_shdw_reg.value; // live register
#else
    g_v2d_pdpd_passthru_shdw_config_tbl[0].value = (Q & 0x7FFF) | ((I & 0x7FFF) << 16);
    printf ("passthru shdw reg: %x\n", g_v2d_pdpd_passthru_shdw_config_tbl[0].value);
#endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_pdpd_passthru_shdw_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_passthru_shdw_config_tbl[i].offset), \
                g_v2d_pdpd_passthru_shdw_config_tbl[i].value, g_v2d_pdpd_passthru_shdw_config_tbl[i].mask, \
                g_v2d_pdpd_passthru_shdw_config_tbl[i].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and sample count value
 * @return          status
 */
int pdpd_tcnt_update_passthru_config(int v2d_num, int apb_num, int sample_cnt_value)
{
    int i, rv = 0;
    pdpd_tcnt_update_passthru_reg_t pdpd_tcnt_update_passthru_reg;
/*
    typedef union {
      struct {
        uint32_t COUNT : 32;
        ///< Sample Count Trigger Value
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
      } ;
      uint32_t value;
    } pdpd_tcnt_update_passthru_reg_t;
*/
    uint32_t COUNT = sample_cnt_value;

    pdpd_tcnt_update_passthru_reg.COUNT = COUNT;
    g_v2d_pdpd_tcnt_update_passthru_config_tbl[0].value = pdpd_tcnt_update_passthru_reg.value;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_tcnt_update_passthru_config_tbl[0].offset, \
                g_v2d_pdpd_tcnt_update_passthru_config_tbl[0].value, g_v2d_pdpd_tcnt_update_passthru_config_tbl[0].mask, \
                g_v2d_pdpd_tcnt_update_passthru_config_tbl[0].name))
        return rv;
}

/**
 * @brief           Function configuring the nl lut coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and sample count vlaue
 * @return          status
 */
int pdpd_tcnt_update_nl_lut_config(int v2d_num, int apb_num, int sample_cnt_value)
{
    int i, rv = 0;
    pdpd_tcnt_update_nl_lut_reg_t pdpd_tcnt_update_nl_lut_reg;

/*
    typedef union {
      struct {
        uint32_t COUNT : 32;
        ///< Sample Count Trigger Value
        ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
      } ;
      uint32_t value;
    } pdpd_tcnt_update_nl_lut_reg_t;
*/

    uint32_t COUNT = sample_cnt_value;

    pdpd_tcnt_update_nl_lut_reg.COUNT = COUNT;
    g_v2d_pdpd_tcnt_update_nl_config_tbl[0].value = pdpd_tcnt_update_nl_lut_reg.value;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_tcnt_update_nl_config_tbl[0].offset, \
                g_v2d_pdpd_tcnt_update_nl_config_tbl[0].value, g_v2d_pdpd_tcnt_update_nl_config_tbl[0].mask, \
                g_v2d_pdpd_tcnt_update_nl_config_tbl[0].name))
        return rv;
}

/**
 * @brief           Function configuring the C lut coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and sample count vlaue
 * @return          status
 */
int pdpd_tcnt_update_c_lut_config(int v2d_num, int apb_num, int sample_cnt_value)
{
    int i, rv = 0;
    pdpd_tcnt_update_c_lut_reg_t pdpd_tcnt_update_c_lut_reg;

/*
    typedef union {
      struct {
        uint32_t COUNT : 32;
        ///< Sample Count Trigger Value
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
      } ;
      uint32_t value;
    } pdpd_tcnt_update_c_lut_reg_t;
*/
    uint32_t COUNT = sample_cnt_value;

    pdpd_tcnt_update_c_lut_reg.COUNT = COUNT;
    g_v2d_pdpd_tcnt_update_c_config_tbl[0].value = pdpd_tcnt_update_c_lut_reg.value;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_tcnt_update_c_config_tbl[0].offset, \
                g_v2d_pdpd_tcnt_update_c_config_tbl[0].value, g_v2d_pdpd_tcnt_update_c_config_tbl[0].mask, \
                g_v2d_pdpd_tcnt_update_c_config_tbl[0].name))
        return rv;
}



/**
 * @brief           Function for noc reset
 * @param [in]      srp
 * @return          status value
 */
int release_reset_abc_noc (void *srp)
{
    int i, rv = 0, flags = 0;
    // Not required as it will be taken care in init() function
#if 0
    for (i = 0; i < ARRAY_SIZE(g_vex_noc_config); i++)
    {
        if (rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CFG_CTRL,
                        0,
                        g_vex_noc_config[i].offset,
                        &g_vex_noc_config[i].value,
                        1,
                        flags))
            return rv;

    }
#endif
    return rv;
}

/**
 * @brief           Function for triggering the BFN
 * @param [in]      v2d_num and apb_num
 * @return          status value
 */
int tx_start_bfn_trigger(int v2d_num, int apb_num)
{
    int rv = 0, read_value = 0;

    if (0 == apb_num)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_START_LM0_OFFSET, BFN_CSR_START_LM_MATCH_EN_BF_MSK, \
                BFN_CSR_START_LM_WR_MASK, "BFNE_START_LM"))
            return rv;
    }
    else if (1 == apb_num)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_START_LM1_OFFSET, BFN_CSR_START_LM_MATCH_EN_BF_MSK, \
                BFN_CSR_START_LM_WR_MASK, "BFNE_START_LM"))
            return rv;
    }

    /* if it is ODD V2D configure the corresponding even V2D*/
    v2d_num = (v2d_num % 2) ? (v2d_num - 1) : v2d_num;

    read_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_GENERAL_CSR_OFFSET, "BFN_GENERAL_CSR_OFFSET");

    if (0 == (read_value & BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK))
    {
        read_value = read_value | BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_GENERAL_CSR_OFFSET, read_value, \
                BFN_CSR_GENERAL_CSR_WR_MASK, "BFNE_GENERAL_CSR_OFFSET"))
            return rv;
    }

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_BFNE_CFG0_OFFSET, 0x1, \
            BFN_CSR_BFNE_CFG_WR_MASK, "BFNE_CONFIG0"))
        return rv;
#if QUAD_DELAYED_CAL       
	printf(" QUAD_DELAYED_CAL:tx_start_bfn_trigger BFN config done\n");        
#endif 
    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_BFNE_START0_OFFSET, 0xFFFFFFFF, \
            BFN_CSR_BFNE_START_WR_MASK, "BFNE_START0"))
        return rv;

    return rv;
}

/**
 * @brief           Function for forced BFN trigger for PDPD
 * @param [in]      v2d_num, apb_num
 * @return          status value
 */
int pdpd_start_bfn_force_trigger(int v2d_num, int apb_num)
{

    int rv = 0, read_value = 0;

    if (0 == apb_num)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_START_LM2_OFFSET, BFN_CSR_START_LM_MATCH_EN_BF_MSK, \
                BFN_CSR_START_LM_WR_MASK, "BFNE_START_LM"))
            return rv;
    }
    else if (1 == apb_num)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_START_LM3_OFFSET, BFN_CSR_START_LM_MATCH_EN_BF_MSK, \
                BFN_CSR_START_LM_WR_MASK, "BFNE_START_LM"))
            return rv;
    }

    /* if it is ODD V2D configure the corresponding even V2D*/
    v2d_num = (v2d_num % 2) ? (v2d_num - 1) : v2d_num;

    read_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_GENERAL_CSR_OFFSET, "BFN_GENERAL_CSR_OFFSET");

    if (0 == (read_value & BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK))
    {
        read_value = read_value | BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_GENERAL_CSR_OFFSET, read_value, \
                BFN_CSR_GENERAL_CSR_WR_MASK, "BFNE_GENERAL_CSR_OFFSET"))
            return rv;
    }

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_BFNE_CFG0_OFFSET, 0x1, \
            BFN_CSR_BFNE_CFG_WR_MASK, "BFNE_CONFIG0"))
        return rv;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_BFNE_START0_OFFSET, 0xFFFFFFFF, \
            BFN_CSR_BFNE_START_WR_MASK, "BFNE_START0"))
        return rv;

    return rv;
}


/**
 * @brief           Function for interrupt status check
 * @param [in]      v2d_num ,apb_num, v2d_exp_value, nsip0_exp_value and nsip1_exp_value
 * @return          status value
 */
int interrupt_status_check(int v2d_num, int apb_num, int v2d_exp_value, int nsip0_exp_value, int nsip1_exp_value)
{
    int rv = 0;
    int v2d_interrupt_value = 0, nsip_interrupt_value = 0;
    if ((v2d_interrupt_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_STAT_OFFSET, \
                    "V2D_CSR_INT_STATUS")) != v2d_exp_value)
    {
        rv += 1;
        printf("HOST: Interrupt value : %x\n", v2d_interrupt_value);
        printf("ERROR: unwanted interrupt was set for v2d\n");
    }
    if ((nsip_interrupt_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_STAT_OFFSET, \
                    "NSIP_HBI_0_INT_STATUS")) != nsip0_exp_value)
    {
        rv += 1;
        printf("HOST: Interrupt value : %x\n", nsip_interrupt_value);
        printf("ERROR: unwanted interrupt was set for nsip\n");
    }
    if ((nsip_interrupt_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_STAT_OFFSET, \
                    "NSIP_HBI_1_INT_STATUS")) != nsip1_exp_value)
    {
        rv |= 1;
        printf("HOST: NSIP_1 Interrupt value : %x\n", nsip_interrupt_value);
        printf("ERROR: unwanted interrupt was set for nsip_HBI1\n");
    }

    return rv;
}

/**
 * @brief           Function for fill level trigger check
 * @param [in]      v2d_num ,apb_num and fill_level value
 * @return          void
 */
void fill_level_check(int v2d_num, int apb_num, int fill_level_value)
{
    int rv = 0, fill_trigger_value = 0;

    fill_trigger_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START0_OFFSET, "TX_BUF_WM_START");

    fill_trigger_value = (fill_trigger_value & 0xFFF);

    if ((fill_trigger_value > (fill_level_value + 5)) || (fill_trigger_value < fill_level_value))
    {
        printf("WARNING: Triggered fill level 0x%x value is not proper, fill_level_value: 0x%x", fill_trigger_value, fill_level_value);
    }

}

/**
 * @brief           Function for fill level trigger check
 * @param [in]      v2d_num ,apb_num and fill_level value
 * @return          void
 */
void pdpd_fill_level_check(int v2d_num, int apb_num, int fill_level_value)
{
    int rv = 0, fill_trigger_value = 0;

    fill_trigger_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START2_OFFSET, "TX_BUF_WM_START");

    fill_trigger_value = (fill_trigger_value & 0xFFF);
#if QUAD_DELAYED_CAL 
     printf("QUAD_DELAYED_CAL: Triggered fill level 0x%x value is not proper, fill_level_value: 0x%x", fill_trigger_value, fill_level_value);
#endif //QUAD_DELAYED_CAL
    if ((fill_trigger_value > (fill_level_value + 5)) || (fill_trigger_value < fill_level_value))
    {
        printf("WARNING: Triggered fill level 0x%x value is not proper, fill_level_value: 0x%x", fill_trigger_value, fill_level_value);
    }

}


/**
 * @brief           Function for checking the shadow to live transition
 * @param [in]      pointer to a structure
 * @return          success or failure
 */
int gmp_ddr_shdw_live_reg_check(v2d_shdw_live_reg_check_t *reg_check)
{

    int i = 0, j = 0, k = 0, rv = 0, gmp_value = 0, ddr_value = 0, num_lut = 0, ddr_terms_used = 0, gmp_terms_used = 0;
    int gmp_c_value[V2D_PDPD_MAX_GMP_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {0};
    int ddr_c_value[V2D_PDPD_MAX_DDR_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS] = {0};
    int gmp_shift_value[V2D_PDPD_MAX_GMP_TERMS] = {0};
    int ddr_shift_value[V2D_PDPD_MAX_DDR_TERMS] = {0};
    pdpd_rate_t pdpd_out_rate;

    gmp_value = (((reg_check->gmp_c_i_value) & 0x1FFF) << 16) | (reg_check->gmp_c_q_value);
    ddr_value = (((reg_check->ddr_c_i_value) & 0x1FFF) << 16) | (reg_check->ddr_c_q_value);
    pdpd_out_rate = g_test_config_tbl[reg_check->test_config][1];
    ddr_terms_used = reg_check->num_ddr_terms;
    gmp_terms_used = reg_check->num_gmp_terms;

    for (i = 0; i < gmp_terms_used; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            gmp_c_value[i][j] = gmp_value;
        }

        gmp_shift_value[i] = reg_check->gmp_shift_value;
    }

    /*DDR terms population*/
    for (i = 0; i < ddr_terms_used; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            ddr_c_value[i][j] = ddr_value;
        }

        ddr_shift_value[i] = reg_check->ddr_shift_value;
    }

    if (PDPD_RATE_IQ_4 == pdpd_out_rate)
    {
        for (i = 16; i < (16 + gmp_terms_used); i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                gmp_c_value[i][j] = gmp_value;
            }

            gmp_shift_value[i] = reg_check->gmp_shift_value;
        }

        /*DDR terms population*/
        for (i = 8; i < (8 + ddr_terms_used); i++)
        {
            for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
            {
                ddr_c_value[i][j] = ddr_value;
            }

            ddr_shift_value[i] = reg_check->ddr_shift_value;
        }
    }

    if (PDPD_RATE_IQ_8 == pdpd_out_rate)
    {
        for (k = 0; k < 32; k = (k + 8))
        {
            for (i = 0; i < gmp_terms_used; i++)
            {
                for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
                {
                    gmp_c_value[(i + k)][j] = gmp_value;
                }

                gmp_shift_value[i + k] = reg_check->gmp_shift_value;
            }
        }

        /*DDR terms population*/
        for (k = 0; k < 16; k = (k + 4))
        {
            for (i = 0; i < ddr_terms_used; i++)
            {
                for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
                {
                    ddr_c_value[(i + k)][j] = ddr_value;
                }
                ddr_shift_value[i + k] = reg_check->ddr_shift_value;
            }

        }

    }

    if (gmp_reg_check((reg_check->v2d_num), (reg_check->apb_num), gmp_c_value))
        rv |= 1;

    if (ddr_reg_check((reg_check->v2d_num), (reg_check->apb_num), ddr_c_value))
        rv |= 1;

    if (gmp_shift_reg_check((reg_check->v2d_num), (reg_check->apb_num), gmp_shift_value))
        rv |= 1;

    if (ddr_shift_reg_check((reg_check->v2d_num), (reg_check->apb_num), ddr_shift_value))
        rv |= 1;

    return rv;

}

/**
 * @brief           Function for checking the GMP live registers
 * @param [in]      v2d_num, apb_num and pointer to array of expected GMP values
 * @return          number of failures
 */
int gmp_reg_check(int v2d_num, int apb_num, int (*gmp_c_value)[V2D_PDPD_MAX_C_LUT_SEGMENTS])
{
    int cnt = 0, i = 0, j = 0;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_GMP_DYNAMIC_LIVE0_GMP_C_LIVE0_OFFSET + (0x200 * i) + (4 * j), \
                        "GMP_C_LIVE") != gmp_c_value[i][j])
            {
                cnt++;
                printf("expected: %x, index: %d", gmp_c_value[i][j], i);
            }
        }
    }
    if (cnt)
        printf("WARNING: %d GMP terms check was failed\n", cnt);

    return cnt;

}

/**
 * @brief           Function for checking the GMP live registers
 * @param [in]      v2d_num, apb_num and pointer to array of expected DDR values
 * @return          number of failures
 */
int ddr_reg_check(int v2d_num, int apb_num, int (*ddr_c_value)[V2D_PDPD_MAX_C_LUT_SEGMENTS])
{
    int cnt = 0, i = 0, j = 0;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_DDR_DYNAMIC_LIVE0_DDR_C_LIVE0_OFFSET + (0x200 * i) + (4 * j), \
                        "DDR_C_LIVE") != ddr_c_value[i][j])
            {
                cnt++;
                printf("expected: %x, index: %d\n", ddr_c_value[i][j], i);
            }
        }
    }
    if (cnt)
        printf("WARNING: %d DDR terms check was failed\n", cnt);

    return cnt;

}

/**
 * @brief           Function for checking the GMP SHIFT live registers
 * @param [in]      v2d_num, apb_num and pointer to array of expected GMP SHIFT values
 * @return          number of failures
 */
int gmp_shift_reg_check(int v2d_num, int apb_num, int *gmp_shift_value)
{
    int cnt = 0, i = 0;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_GMP_DYNAMIC_LIVE0_GMP_SHIFT_LIVE_OFFSET + (0x200 * i), \
                    "GMP_SHIFT_LIVE") != gmp_shift_value[i])
        {
            cnt++;
            printf("expected: %x, index: %d\n", gmp_shift_value[i], i);
        }
    }
    if (cnt)
        printf("WARNING: %d GMP SHIFT check was failed\n", cnt);

    return cnt;
}

/**
 * @brief           Function for checking the DDR SHIFT live registers
 * @param [in]      v2d_num, apb_num and pointer to array of expected DDR SHIFT values
 * @return          number of failures
 */
int ddr_shift_reg_check(int v2d_num, int apb_num, int *ddr_shift_value)
{
    int cnt = 0, i = 0;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_DDR_DYNAMIC_LIVE0_DDR_SHIFT_LIVE_OFFSET + (0x200 * i), \
                    "DDR_SHIFT_LIVE") != ddr_shift_value[i])
        {
            cnt++;
            printf("expected: %x, index: %d\n", ddr_shift_value[i], i);
        }
    }
    if (cnt)
        printf("WARNING: %d DDR SHIFT check was failed\n", cnt);

    return cnt;
}

/**
 * @brief           Function for checking the PASSTHRU live registers
 * @param [in]      v2d_num, apb_num and passthru value
 * @return          status
 */
int passthru_reg_check(int v2d_num, int apb_num, int value)
{
    int passthru_value = 0, rv = 0;
    passthru_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_PASSTHRU_C_LIVE_OFFSET, "PDPD_PASSTHRU_C_LIVE");

    if(passthru_value != value)
    {
        printf("expected: 0x%x, actual : 0x%x\n", value, passthru_value);
        rv = 1;
    }
    return rv;
}

/**
 * @brief           Function for checking the PASSTHRU shdw registers
 * @param [in]      v2d_num, apb_num and passthru value
 * @return          status
 */
int passthru_shdw_reg_check(int v2d_num, int apb_num, int value)
{
    int passthru_value = 0, rv = 0;
    passthru_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_PASSTHRU_C_SHDW_OFFSET, "PDPD_PASSTHRU_C_SHDW");

    if(passthru_value != value)
    {
        printf("expected: 0x%x, actual : 0x%x\n", value, passthru_value);
        rv = 1;
    }
    return rv;
}

/**
 * @brief           Function for reading the watermark registers for PDPD streams
 * @param [in]      v2d_num, apb_num, num_streams and buffer to watermark valus
 * @return          status
 */
int get_tx_pdpd_wm_hilo(int v2d_num, int apb_num, int num_streams, int *watermark_buf)
{
    int rv = 0, i = 0;

    for(i = 0; i < num_streams; i++)
    {
        watermark_buf[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + \
                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO4_OFFSET + (i * 4)), "TX_BUF_WM_HILO");
        if (1 == watermark_buf[i])
            rv |= 1;
    }
    return rv;
}

/**
 * @brief           Function for reading the watermark registers for PDPD Tx in QUAD
 * @param [in]      quad_instance, num_streams and buffer to watermark valus
 * @return          NONE
 */
void get_quad_pdpd_tx_wm_hilo(int quad_instance, int num_streams, int (*watermark_buf)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS])
{

    int i = 0, rv = 0, apb_num = 0, quad_v2d_index = 0, status = 0;

    for (quad_v2d_index = 0; quad_v2d_index < V2D_PER_QUAD; quad_v2d_index++)
    {
        for (apb_num = PDPD_MAIN_INSTANCE; apb_num < PDPD_MAX_INSTANCE; apb_num++)
        {
            get_tx_pdpd_wm_hilo(g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num, num_streams,
                    watermark_buf[quad_v2d_index][apb_num]);
        }
    }
}

/**
 * @brief           Function for reading the watermark registers for PDPD streams
 * @param [in]      v2d_num, apb_num, num_streams and buffer to watermark valus
 * @return          status
 */
int get_tx_wm_hilo(int v2d_num, int apb_num, int num_streams, int *watermark_buf)
{
    int rv = 0, i = 0;

    for(i = 0; i < num_streams; i++)
    {
        watermark_buf[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + \
                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO0_OFFSET + (i * 4)), "TX_BUF_WM_HILO");
        //if (1 == watermark_buf[i])
          //  rv |= 1;
    }
    return rv;
}

/**
 * @brief           Function for reading the watermark registers for QUAD
 * @param [in]      quad_instance, num_streams and buffer to watermark valus
 * @return          NONE
 */
void get_quad_tx_wm_hilo(int quad_instance, int num_streams, int (*watermark_buf)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS])
{

    int i = 0, rv = 0, apb_num = 0, quad_v2d_index = 0, status = 0;

    for (quad_v2d_index = 0; quad_v2d_index < V2D_PER_QUAD; quad_v2d_index++)
    {
        for (apb_num = PDPD_MAIN_INSTANCE; apb_num < PDPD_MAX_INSTANCE; apb_num++)
        {
            get_tx_wm_hilo(g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num, num_streams,
                    watermark_buf[quad_v2d_index][apb_num]);
        }
    }
}

/**
 * @brief           Function for reading the triggered fill level value for Tx streams
 * @param [in]      v2d_num, apb_num, num_streams and buffer to watermark valus
 * @return          none
 */
void get_tx_trigger_fill_level(int v2d_num, int apb_num, int num_stream, int *value)
{
    int rv = 0, i = 0, loop_cnt = 0;

    loop_cnt = (num_stream > 2) ? 2 : 1;    // single register will contain fill level value of 2 streams

    for(i = 0; i < loop_cnt; i++)
    {
        value[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START0_OFFSET + \
                    (i * 4)), "TX_BUF_WM_START");
    }

}

/**
 * @brief           Function for reading the triggered fill level value for Tx streams in a quad
 * @param [in]      quad_instance, num_streams and buffer to watermark valus
 * @return          none
 */
void get_quad_tx_trigger_fill_level(int quad_instance, int num_stream, int (*value)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS])
{

    int i = 0, rv = 0, apb_num = 0, quad_v2d_index = 0, status = 0;

    for (quad_v2d_index = 0; quad_v2d_index < V2D_PER_QUAD; quad_v2d_index++)
    {
        for (apb_num = PDPD_MAIN_INSTANCE; apb_num < PDPD_MAX_INSTANCE; apb_num++)
        {
            get_tx_trigger_fill_level(g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num, num_stream,
                    value[quad_v2d_index][apb_num]);
        }
    }
}

/**
 * @brief           Function for reading the triggered fill level value for PDPD Tx streams
 * @param [in]      v2d_num, apb_num, num_streams and buffer to watermark valus
 * @return          none
 */
void get_pdpd_tx_trigger_fill_level(int v2d_num, int apb_num, int num_stream, int *value)
{
    int rv = 0, i = 0, loop_cnt = 0;

    loop_cnt = (num_stream > 2) ? 2 : 1;    // single register will contain fill level value of 2 streams

    for(i = 0; i < loop_cnt; i++)
    {
        value[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START2_OFFSET + \
                    (i * 4)), "TX_BUF_WM_START");
    }

}

/**
 * @brief           Function for reading the triggered fill level value for PDPD Tx streams in a quad
 * @param [in]      quad_instance, num_streams and buffer to watermark valus
 * @return          none
 */
void get_quad_pdpd_tx_trigger_fill_level(int quad_instance, int num_stream, int (*value)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS])
{

    int i = 0, rv = 0, apb_num = 0, quad_v2d_index = 0, status = 0;

    for (quad_v2d_index = 0; quad_v2d_index < V2D_PER_QUAD; quad_v2d_index++)
    {
        for (apb_num = PDPD_MAIN_INSTANCE; apb_num < PDPD_MAX_INSTANCE; apb_num++)
        {
            get_pdpd_tx_trigger_fill_level(g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num, num_stream,
                    value[quad_v2d_index][apb_num]);
        }
    }
}

/**
 * @brief           Function for populating the G buffer
 * @param [in]      pointer to dpd_coeff_buffer, pointer to structure of reg_check and lut_mode
 * @return          none
 */
void populate_g_buffer(unsigned int (*dpd_coeff_buffer)[NUM_WORDS_PER_LUT], v2d_shdw_live_reg_check_t *reg_check, lut_mode_t lut_mode)
{
    int i, j, k, gmp_index = 0, ddr_index = 0, buffer_index = 0, num_gmp_terms = 0, num_ddr_terms = 0, num_tiles = 0;
    unsigned int gmp_value = ((reg_check -> gmp_c_i_value & 0x1FFF) << 16) | (reg_check -> gmp_c_q_value & 0x1FFF);
    unsigned int ddr_value = (((reg_check->ddr_c_i_value & 0x1FFF) << 16) | (reg_check->ddr_c_q_value));
    unsigned int gmp_shift_value = reg_check -> gmp_shift_value;
    unsigned int ddr_shift_value = reg_check -> ddr_shift_value;
    num_gmp_terms = reg_check -> num_gmp_terms;
    num_ddr_terms = reg_check -> num_ddr_terms;

    /*num tiles will vary based on the TOTAL LUT configuration, refer HAS rev0p8 fig 393, fig 396 and fig 397*/
    switch(lut_mode)
    {
        case PDPD_LUT_48:
            num_tiles = 8;
            break;
        case PDPD_LUT_24:
            num_tiles = 4;
            break;
        case PDPD_LUT_12:
            num_tiles = 2;
            break;
    }

    /*populating the buffer*/
    for (i = 0; i < num_tiles; i++)
    {
        for (j = 0; j < GMP_LUT_TILE; j++)
        {
            if (gmp_index < num_gmp_terms)
            {
                for (k = 0; k < V2D_PDPD_MAX_C_LUT_SEGMENTS; k++)
                {
                    dpd_coeff_buffer[buffer_index][k] = gmp_value;
                }
                dpd_coeff_buffer[buffer_index][k] = gmp_shift_value;
            }
            gmp_index++;
            buffer_index++;
        }
        for (j = 0; j < DDR_LUT_TILE; j++)
        {
            if (ddr_index < num_ddr_terms)
            {
                for (k = 0; k < V2D_PDPD_MAX_C_LUT_SEGMENTS; k++)
                {
                    dpd_coeff_buffer[buffer_index][k] = ddr_value;
                }
                dpd_coeff_buffer[buffer_index][k] = ddr_shift_value;
            }
            ddr_index++;
            buffer_index++;
        }
    }
}

/**
 * @brief           Function for reading the fifo ptr
 * @param [in]      v2d_num, apb_num, number of command queues and pointer to fifo
 * @return          None
 */
void get_nsip0_insert_fifo_ptr(int v2d_num, int apb_num, int num_cmd_queue, int *fifo_ptr)
{
    int rv = 0, i = 0;

    for(i = 0; i < num_cmd_queue; i++)
    {
        fifo_ptr[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + \
                    NSIP_HBI_INSERT_QUE_CSR0_B2H_CSR_OFFSET + (i * 0x10)), "HBI0_INSERT_CSR_OFFSET");
        fifo_ptr[i] = ((fifo_ptr[i] >> 24) & 0x7);
    }
}

/**
 * @brief           Function for reading the fifo ptr
 * @param [in]      v2d_num, apb_num, number of command queues and pointer to fifo
 * @return          None
 */
void get_nsip1_insert_fifo_ptr(int v2d_num, int apb_num, int num_cmd_queue, int *fifo_ptr)
{
    int rv = 0, i = 0;

    for(i = 0; i < num_cmd_queue; i++)
    {
        fifo_ptr[i] = read_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + \
                    NSIP_HBI_INSERT_QUE_CSR0_B2H_CSR_OFFSET + (i * 0x10)), "HBI1_INSERT_CSR_OFFSET");
        fifo_ptr[i] = ((fifo_ptr[i] >> 24) & 0x7);
    }
}

/**
 * @brief           Function for initializig the srp during v2d all testing
 * @param [in]      None
 * @return          None
 */
int v2d_all_test_init()
{
    uint32_t dev_id =0;
    uint32_t dev_flags = 0;

    /* open the core, first function to call before initiating any read/write */
    srp_dev_open(dev_id, dev_flags, &srp);
    return 0;

}

/**
 * @brief           Function for getting the interrupt status for all V2D's and APB's
 * @param [in]      number of V2D instances
 * @return          status value
 */
int get_all_v2d_int_status(int num_v2d, int value)
{
    int rv = 0, lc = 0, apb_num = 0;

    for (lc = 0; lc < num_v2d; lc++)
    {
        for (apb_num = 0; apb_num < 2; apb_num++)
        {
            if (rv = interrupt_status_check(lc/*v2d_num*/, apb_num, value/*V2D interrupt value*/, 0/*nsip0 interrupt value*/, 0/*nsip1 interrupt value*/))
            {
                printf("ERROR: interrupt check failed");
                rv |= 1;
            }
        }
    }
    return rv;
}

/**
 * @brief           Function for wrting the host indication to VEX
 * @param [in]      vex num , address and value to be written
 * @return          status value
 */
int vex_dmem_write(int vex_num, int address, int value)
{
    int rv = 0, ve_dmem_base_addr = 0;

    ve_dmem_base_addr = VEX_DMEM(vex_num);

    if (rv = write_reg_18a(ve_dmem_base_addr + address , value, VE32_BP_CFG_DMEM_FIRST_WR_MASK, "VEX_DMEM"))
        return rv;

    return rv;
}

/**
 * @brief           Function for checking the VEX DMEM value
 * @param [in]      vex num , address and exp value
 * @return          status value
 */
int vex_dmem_check(int vex_num, int address, int exp_value)
{
    int rv = 0, ve_dmem_base_addr = 0, status = 0;

    ve_dmem_base_addr = VEX_DMEM(vex_num);

    if ((status = read_reg_18a(ve_dmem_base_addr + address, "VEX_DMEM")) != exp_value)
    {
        printf("ERROR: Data integrity check failed for vex %d", vex_num);
        rv |= 1;
    }
    return rv;

}

/**
 * @brief           Function for enabling the QUAD v2d clock
 * @param [in]      quad instance
 * @return          status value
 */
int v2d_quad_clk_enable(int quad_instance)
{
    int rv = 0, i = 0;

    for (i = 0; i < V2D_PER_QUAD; i++)
    {
        if (rv = v2d_clk_enable(g_v2d_instance_in_quad[quad_instance][i], DRF_CHANNEL_BOTH))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function for checking the interrupt for V2D QUAD
 * @param [in]      quad instance, expected interrupt value, expected nsip0 int value, expected nsip1 int value
 * @return          status value
 */
int quad_interrupt_status_check(int quad_instance, int (*exp_interrupt_value)[PDPD_MAX_INSTANCE], int nsip0_exp_value, int nsip1_exp_value)
{
    int i = 0, rv = 0, apb_num = 0, quad_v2d_index = 0, status = 0;

    for (quad_v2d_index = 0; quad_v2d_index < V2D_PER_QUAD; quad_v2d_index++)
    {
        for (apb_num = PDPD_MAIN_INSTANCE; apb_num < PDPD_MAX_INSTANCE; apb_num++)
        {
            if (rv = interrupt_status_check(g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num,
                        exp_interrupt_value[quad_v2d_index][apb_num], nsip0_exp_value, nsip1_exp_value))
            {
                printf("ERROR: interrupt check failed for v2d%d, apb%d", g_v2d_instance_in_quad[quad_instance][quad_v2d_index], apb_num);
                status |= 1;
            }
        }
    }
    return status;
}

/**
 * @brief           Function for checking the interrupt status for V2D BFN sub block
 * @param [in]      v2d_num, apb_num, expected low interrupt value, expected high interrupt value
 * @return          status value
 */
int bfn_interrupt_status_check(int v2d_num, int apb_num, uint32_t subb_lo_value, uint32_t subb_hi_value)
{
    int rv = 0;

    if (read_reg_18a((PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_SUBB_LO_INTR_OFFSET), "BFN_CSR_SUBB_LO_INTR_OFFSET") != subb_lo_value)
    {
        rv |= 1;
    }

    if (read_reg_18a((PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_SUBB_HI_INTR_OFFSET), "BFN_CSR_SUBB_HI_INTR_OFFSET") != subb_hi_value)
    {
        rv |= 1;
    }

    return rv;
}

/**
 * @brief           Function for clearing the interrupt
 * @param [in]      v2d_num ,apb_num, v2d_exp_value, nsip0_exp_value and nsip1_exp_value
 * @return          status value
 */
int write_interrupt_clear(int v2d_num, int apb_num, uint32_t v2d_int_value, uint32_t nsip_0_int_value, uint32_t nsip_1_int_value)
{
    int rv = 0;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_CLR_OFFSET, v2d_int_value, \
                AV2D_CSR_INT_CSR_INT_CLR_WR_MASK, "V2D_CSR_INT_CLEAR"))
    {
        rv |= 1;
    }

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET + NSIP_HBI_INTR_INT_STAT_OFFSET, nsip_0_int_value, \
                NSIP_HBI_INTR_INT_CLR_OFFSET, "HBI_0_INT_CLEAR"))
    {
        rv |= 1;
    }

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET + NSIP_HBI_INTR_INT_STAT_OFFSET, nsip_1_int_value, \
                NSIP_HBI_INTR_INT_CLR_OFFSET, "HBI_1_INT_CLEAR"))
    {
        rv |= 1;
    }

    return rv;
}


int get_start_l_cnt_value(int v2d_num, int *value)
{
}

/**
 * @brief           Function for checking the TX start to DRF for a quad
 * @param [in]      quad_instance
 * @return          status value
 */
int quad_tx_drf_check(int quad_instance)
{
    int rv = 0, v2d_num = 0, apb_num = 0, v2d_index = 0;
    uint32_t tx_drf_cnt[V2D_PER_QUAD][2] = {0};

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        apb_num = 0;
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];

        tx_drf_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN2_OFFSET, "BFN_CAP2");
        apb_num++;
        tx_drf_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN8_OFFSET, "BFN_CAP2");

        printf("BFN count for V2D%d Ch%d:%d, Ch%d:%d", v2d_num, 0,tx_drf_cnt[v2d_index][0], 1, tx_drf_cnt[v2d_index][1]);
    }

    if ((0 == tx_drf_cnt[0][0]) || (0 == tx_drf_cnt[0][1]) || (0 == tx_drf_cnt[1][0]) || (0 == tx_drf_cnt[1][1]))
    {
        printf("ERROR: BFN CAP value was zero");
        rv |= 1;
    }

    if ((tx_drf_cnt[0][0] != tx_drf_cnt[0][1]) || (tx_drf_cnt[0][0] != tx_drf_cnt[1][0]) || (tx_drf_cnt[0][0] != tx_drf_cnt[1][1]) ||
            (tx_drf_cnt[0][1] != tx_drf_cnt[1][0]) || (tx_drf_cnt[0][1] != tx_drf_cnt[1][1]) || tx_drf_cnt[1][0] != tx_drf_cnt[1][1])
    {
        rv |= 1;
    }

    return rv;
}

/**
 * @brief           Function for checking the TX start to DRF for a quad
 * @param [in]      quad_instance and apb_num
 * @return          status value
 */
int quad_2_channel_tx_drf_check(int quad_instance, int apb_num)
{
    int rv = 0, v2d_num = 0, apb_cnt = 0, v2d_index = 0;
    uint32_t tx_drf_cnt[V2D_PER_QUAD][2] = {0};

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        apb_cnt = 0;
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];

        if (PDPD_MAIN_INSTANCE == apb_num)
        {
            tx_drf_cnt[v2d_index][apb_cnt] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN2_OFFSET, "BFN_CAP2");
        }
        else
        {
            apb_cnt++;
            tx_drf_cnt[v2d_index][apb_cnt] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN8_OFFSET, "BFN_CAP2");
        }

        printf("BFN count for DRF trigger V2D%d Ch%d:%d", v2d_num, apb_num, tx_drf_cnt[v2d_index][apb_num]);
    }

    if ((0 == tx_drf_cnt[0][apb_num]) || (0 == tx_drf_cnt[1][apb_num]))
    {
        printf("ERROR: BFN CAP value was zero");
        rv |= 1;
    }

    if ((tx_drf_cnt[0][apb_num] != tx_drf_cnt[1][apb_num]))
    {
        rv |= 1;
    }

    return rv;
}

/**
 * @brief           Function for checking the TX start of PDPD for a quad
 * @param [in]      quad_instance
 * @return          status value
 */
int quad_tx_pdpd_check(int quad_instance)
{
    int rv = 0, v2d_num = 0, apb_num = 0, v2d_index = 0;
    uint32_t tx_pdpd_cnt[V2D_PER_QUAD][2] = {0};
#if QUAD_DELAYED_CAL    
    uint32_t nsip1_cnt[V2D_PER_QUAD][2] = {0};  //Register 1 = BFN count for abc_v2d 0, Tx stream data with configured index is seen on Path 1 from NSIP 1, for B path
#endif //QUAD_DELAYED_CAL

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        apb_num = 0;
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];

        tx_pdpd_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN3_OFFSET, "BFN_CAP3");
        apb_num++;
        tx_pdpd_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN9_OFFSET, "BFN_CAP9");

        printf("BFN count for PDPD TX capture V2D%d Ch%d:%d, Ch%d:%d", v2d_num, 0,tx_pdpd_cnt[v2d_index][0], 1, tx_pdpd_cnt[v2d_index][1]);
    }
#if   QUAD_DELAYED_CAL
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        apb_num = 0;
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];

        nsip1_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN1_OFFSET, "BFN_CAP1");
        apb_num++;
        nsip1_cnt[v2d_index][apb_num] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN7_OFFSET, "BFN_CAP7");

        printf("BFN count for NSIP1 capture V2D%d Ch%d:%d, Ch%d:%d", v2d_num, 0,nsip1_cnt[v2d_index][0], 1, nsip1_cnt[v2d_index][1]);
        printf("QUAD_DELAYED_CAL: first_sample _Out -first_sample_In V2D%d Ch%d:%d, Ch%d:%d", v2d_num, 0,(tx_pdpd_cnt[v2d_index][0] - nsip1_cnt[v2d_index][0]), 1, (tx_pdpd_cnt[v2d_index][1] - nsip1_cnt[v2d_index][1]));
    }
#endif   //QUAD_DELAYED_CAL

    if ((0 == tx_pdpd_cnt[0][0]) || (0 == tx_pdpd_cnt[0][1]) || (0 == tx_pdpd_cnt[1][0]) || (0 == tx_pdpd_cnt[1][1]))
    {
        printf("ERROR: BFN CAP value was zero");
        rv |= 1;
    }

    if ((tx_pdpd_cnt[0][0] != tx_pdpd_cnt[0][1]) || (tx_pdpd_cnt[0][0] != tx_pdpd_cnt[1][0]) || (tx_pdpd_cnt[0][0] != tx_pdpd_cnt[1][1]) ||
            (tx_pdpd_cnt[0][1] != tx_pdpd_cnt[1][0]) || (tx_pdpd_cnt[0][1] != tx_pdpd_cnt[1][1]) || tx_pdpd_cnt[1][0] != tx_pdpd_cnt[1][1])
    {
        rv |= 1;
    }

    return rv;
}


/**
 * @brief           Function for checking the TX start of PDPD for a quad
 * @param [in]      quad_instance and apb_num
 * @return          status value
 */
int quad_2_channel_tx_pdpd_check(int quad_instance, int apb_num)
{
    int rv = 0, v2d_num = 0, apb_cnt = 0, v2d_index = 0;
    uint32_t tx_pdpd_cnt[V2D_PER_QUAD][2] = {0};

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        apb_cnt= 0;
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];

        if (PDPD_MAIN_INSTANCE == apb_num)
        {
            tx_pdpd_cnt[v2d_index][apb_cnt] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN3_OFFSET, "BFN_CAP2");
        }
        else
        {
            apb_cnt++;
            tx_pdpd_cnt[v2d_index][apb_cnt] = read_reg_18a(PDPD_BASE_ADDR(v2d_num, 0) + V2D_BFN_OFFSET + BFN_CSR_CAP_BFN9_OFFSET, "BFN_CAP2");
        }

        printf("BFN count for PDPD trigger V2D%d Ch%d:%d,", v2d_num, apb_num, tx_pdpd_cnt[v2d_index][apb_num]);
    }

    if ((0 == tx_pdpd_cnt[0][apb_num]) || (0 == tx_pdpd_cnt[1][apb_num]))
    {
        printf("ERROR: BFN CAP value was zero");
        rv |= 1;
    }

    if ((tx_pdpd_cnt[0][apb_num] != tx_pdpd_cnt[1][apb_num]))
    {
        rv |= 1;
    }

    return rv;
}


/**
 * @brief           Function for reading the DMAC Ch1 interrupt
 * @param [in]      none
 * @return          reg value
 */
uint64_t get_rcs_dmac_ch1_int_status()
{
    uint64_t value = 0;

    value = read_reg64_18a(RCS_DMAC_CH1_INTSTAT_ADR, "DMAC_CH1_INTSTATUS");
    return value;
}

/**
 * @brief           Function for writing to the DMAC Ch1 interrupt clear reg
 * @param [in]      value to be written
 * @return          status
 */
int clear_rcs_dmac_ch1_int(uint64_t value)
{
    int rv = 0;
    rv = write_reg64_18a(RCS_DMAC_CH1_INTCLRREG_ADR, value, RCS_DMAC_CH1_INTCLRREG_WR_MASK, "DMAC_CH1_INTCLEAR");
    return rv;
}

/**
 * @brief           Function for writing the Work around for follower BFN
 * @param [in]      none
 * @return          status
 */
int follower_bfn_wa_fpga()
{
    int rv = 0;

    if (abc_platform_detect())
    {
        printf("WARNING: abc_platform_detect failed\n");
        rv = 1;
    }

    if ((ABC_18A_0P6_1_0 == g_abc_build_version) || (ABC_18A_0P6_1_1 == g_abc_build_version))
    {
        //Workaround for follower BFN functionality
        system("frioPciWrite -F s6a1 -P 0x20000 0x3");
    }

    return rv;
}

/**
 * @brief           Function polling for the RSM flag update
 * @param [in]      read_address and expected_value
 * @return          status value
 */
int poll_rsm_flag_rcs(uint32_t address, uint32_t expected_value)
{
    int val_out = 0, loop_count = 0, rv = 0, flags = 0;

    while (val_out != expected_value)
    {
        val_out = read_reg_18a(address, "SRAM_AX_FLAG");

        if (loop_count > 100)
        {
            LOG_ERROR("RCS execution didn't complete");
            rv = 1;
            break;
        }
        usleep(10000);
        loop_count++;
    }
    return rv;
}

/**
 * @brief           Function for comparing the FB MEM data for QUAD
 * @param [in]      pointer to quad_mem_compare_t structure.
 * @return          status value
 */
int quad_pdpd_ingress_cap_mem_compare(quad_mem_compare_t *mem_compare)
{
    int rv = 0, fb_mem_instance = 0, fb_mem_base_address = 0, data_index = 0, add_val = 0, blocks_to_compare = 0, i = 0, j = 0, lc = 0,
        cnt = 0;
    uint32_t ref_data[(mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC], read_address = 0, ant_num = 0;
    int skipped_blocks = 0, address_offset = 0, skipped_blocks_between_antenna = 0, num_samples = 0, clks_per_blk = 0,
        skipped_blocks_consecutive_captures = 0;

    fb_mem_instance = ((mem_compare->quad_instance) > 1) ? 1 : 0;
    read_address = (fb_mem_instance) ? FB1_SRAM_START : FB0_SRAM_START;
    clks_per_blk = (mem_compare->drf_clk) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);

    // Blocks skipped due to capture delay value and delay between antenna captures
    skipped_blocks = (mem_compare->capture_delay_value) / CYCLES_PER_BLOCK_983M;
    skipped_blocks_between_antenna = (mem_compare->delay_value_between_antenna) / clks_per_blk;
    skipped_blocks_consecutive_captures = (mem_compare->consecutive_capture_delay) / clks_per_blk;

    // Number of blocks based on the data rate
    blocks_to_compare = (mem_compare->samples_per_antenna) / ((mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC);

    //Add value based on the capture delay value, for every block of delay add_val should be incremented by additional factor
    add_val = (mem_compare->additional_factor) + (skipped_blocks * (mem_compare->additional_factor));

    for (cnt = 0; cnt < (mem_compare->num_iter); cnt++)
    {
        for (ant_num = 0; ant_num < (mem_compare->num_antenna); ant_num++)
        {
            for (lc = 0; lc < blocks_to_compare; lc++)
            {
                /*Generating the REF pattern*/
                for (i = 0; i < (mem_compare->num_vectors_per_block); i++)
                {
                    for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
                    {
                        ref_data[data_index] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)))
                                               + add_val;
                        data_index++;
                    }
                }

                if (0 == lc)
                {
                    /*Get the index from which the REF matches with output*/
                    address_offset = get_match_offset(read_address,
                                                      ref_data[0],
                                                      ((mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC));

                    if (address_offset)
                    {
                        LOG_WARNING("offset value is 0x%x", address_offset);
                    }

                    if (-1 == address_offset)
                    {
                        LOG_ERROR("COMARISON FAILED address_offset was not found");
                        return 1;
                    }

                    if (address_offset)
                    {
                        if (stale_value_compare(read_address, address_offset, (add_val - (mem_compare->additional_factor)),
                                                (mem_compare->num_vectors_per_block)))
                            LOG_ERROR("stale value comparison failed");
                    }

                    /*Convert the index to bytes address*/
                    read_address += (address_offset * 4);
                }

                /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance,
                 * the solution will be to update the SRP API to read the complete memory instead of word by word*/
                if ((mem_compare->num_vectors_per_block) <= 64)
                {
                    num_samples = ((mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC);

                    //If address_offset is nonzero the last block should be less than the actual samples
                    num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

                    rv |= read_mem_expect_18a(read_address,
                                              num_samples,
                                              ref_data,
                                              "fb_mem");
                }
                else
                {
                    rv |= read_mem_expect_18a(read_address,
                                              (64 * NUM_OF_ELEMENTS_PER_VEC),
                                              ref_data,
                                              "fb_mem");

                    num_samples = (((mem_compare->num_vectors_per_block) - 64) * NUM_OF_ELEMENTS_PER_VEC);

                    //If address_offset is nonzero the last block should be less than the actual samples
                    num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

                    rv |= read_mem_expect_18a(read_address + (64 * BYTES_PER_VEC),
                                              num_samples,
                                              ref_data + (64 * NUM_OF_ELEMENTS_PER_VEC),
                                              "fb_mem");
                }

                /*After every block compare read_address should be incremented*/
                read_address = read_address + ((mem_compare->num_vectors_per_block) * BYTES_PER_VEC);
                data_index = 0;
                /*add value should be incremented by additional factor*/
                add_val += (mem_compare->additional_factor);
            }

            LOG_INFO("Antenna %d integrity check completed with value: %d for blocks: %d", ant_num, rv, blocks_to_compare);

            /*add value should be incremented by skipped blocks time of additional factor*/
            add_val = add_val + (skipped_blocks_between_antenna) * (mem_compare->additional_factor);
            LOG_DEBUG("add_val: 0x%x", add_val);
        }

        add_val += (skipped_blocks_consecutive_captures * (mem_compare->additional_factor));
        LOG_INFO("iteration %d was done with value %d",cnt, rv);
    }

    return rv;
}

/**
 * @brief           Function for comparing the FB MEM data
 * @param [in]      v2d_num, add_factor and num_vectors per block.
 * @return          status value
 */
int pdpd_ingress_cap_mem_compare(int v2d_num, int additional_factor, int num_vectors_per_block, int capture_delay_value,
        drf_clock_t drf_clock, uint32_t blocks_to_compare)
{
    int rv = 0, fb_mem_instance = 0, fb_mem_base_address = 0, data_index = 0, add_val = 0, i = 0, j = 0, lc = 0;
    uint32_t ref_data[num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC], read_address = 0, num_samples = 0;
    int skipped_blocks = 0, address_offset = 0, clks_per_blk = 0;

    fb_mem_instance = (v2d_num > V2D3) ? 1 : 0;
    fb_mem_base_address = (fb_mem_instance) ? FB1_SRAM_START : FB0_SRAM_START;
    clks_per_blk = (drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    skipped_blocks = capture_delay_value / clks_per_blk;   // Blocks skipped due to capture delay value

    // Reading 1MB of Capture Memory
    add_val = additional_factor + (skipped_blocks * additional_factor);

    for (lc = 0; lc < blocks_to_compare; lc++)
    {
        for (i = 0; i < num_vectors_per_block; i++)
        {
            for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
            {
                ref_data[data_index] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)))
                                       + add_val;
                data_index++;
            }
        }

        read_address = fb_mem_base_address + (lc * num_vectors_per_block * BYTES_PER_VEC) + (address_offset * 4);

        if (0 == lc)
        {
            address_offset = get_match_offset(read_address, ref_data[0], (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC));

            if (address_offset)
            {
                LOG_WARNING("offset value is 0x%x", address_offset);
            }

            if (-1 == address_offset)
            {
                LOG_ERROR("COMARISON FAILED address_offset was not found");
                return 1;
            }

            if (address_offset)
            {
                if (stale_value_compare(read_address, address_offset, (add_val - additional_factor), num_vectors_per_block))
                    LOG_ERROR("stale value comparison failed");
            }

            read_address += address_offset * 4;
        }

        /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance,
         * the solution will be to update the SRP API to read the complete memory instead of word by word*/
        if (num_vectors_per_block <= 64)
        {
            num_samples = ((num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC);

            //If address_offset is nonzero the last block should be less than the actual samples
            num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

            rv |= read_mem_expect_18a(read_address,
                                      num_samples,
                                      ref_data,
                                      "fb_mem");
        }
        else
        {
            rv |= read_mem_expect_18a(read_address,
                                      (64 * NUM_OF_ELEMENTS_PER_VEC),
                                      ref_data,
                                      "fb_mem");

            num_samples = (((num_vectors_per_block) - 64) * NUM_OF_ELEMENTS_PER_VEC);

            //If address_offset is nonzero the last block should be less than the actual samples
            num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

            rv |= read_mem_expect_18a(read_address + (64 * BYTES_PER_VEC),
                                      num_samples,
                                      ref_data + (64 * NUM_OF_ELEMENTS_PER_VEC),
                                      "fb_mem");
        }

        data_index = 0;
        add_val += additional_factor;
    }

    return rv;
}
#if LIVEIQ_SAMPLES
int liveIQ_pdpd_egress_cap_mem_read(int v2d_num, int *ref_data, int* y_out,  int num_vectors_per_block, drf_clock_t drf_clock, uint32_t blocks_to_compare)
{
    int rv = 0, fb_mem_instance = 0, fb_mem_base_address = 0, i = 0, j = 0, lc = 0;
    uint32_t read_address = 0, num_samples = 0;
    int  clks_per_blk = 0;

    fb_mem_instance = (v2d_num > V2D3) ? 1 : 0;
    fb_mem_base_address = (fb_mem_instance) ? FB1_SRAM_START : FB0_SRAM_START;
    clks_per_blk = (drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
 	read_address = fb_mem_base_address;

	num_samples = 0;
    for (lc = 0; lc < blocks_to_compare; lc++)
    {

		printf("read_address=0x%x",read_address);

        /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance,
         * the solution will be to update the SRP API to read the complete memory instead of word by word*/
        if (num_vectors_per_block <= 64)
        {
            num_samples = ((num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC);
            read_mem_18a( read_address, num_samples, y_out, "fb_mem");

        }
        else
        {
			read_mem_18a( read_address, (64 * NUM_OF_ELEMENTS_PER_VEC), y_out, "fb_mem");
            num_samples = (((num_vectors_per_block) - 64) * NUM_OF_ELEMENTS_PER_VEC);
            read_mem_18a( read_address+(64 * NUM_OF_ELEMENTS_PER_VEC*4), num_samples, (y_out + ( 64*NUM_OF_ELEMENTS_PER_VEC)) , "fb_mem");

        }
		read_address = read_address + (num_vectors_per_block*NUM_OF_ELEMENTS_PER_VEC*4);
		y_out = y_out + (num_vectors_per_block*NUM_OF_ELEMENTS_PER_VEC);


    }

    return rv;
}


#endif //LIVEIQ_SAMPLES

/**
 * @brief           Function for comparing the FB MEM data
 * @param [in]      v2d_num, add_factor and num_vectors per block.
 * @return          status value
 */
int pdpd_egress_cap_mem_compare(int v2d_num, int num_vectors_per_block, int capture_delay_value,
        drf_clock_t drf_clock, uint32_t blocks_to_compare, int lut_block_duration, lut_mode_t lut_mode, FILE *fp_ref)
{
    int rv = 0, fb_mem_instance = 0, fb_mem_base_address = 0, add_val = 0, i = 0, j = 0, lc = 0, iter = 0;
    uint32_t ref_data[num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC], read_address = 0, num_samples = 0;
    int skipped_blocks = 0, address_offset = 0, clks_per_blk = 0, skipped_blocks_consecutive_updates = 0,
        skipped_blocks_before_lut_update = 0, skipped_blocks_after_lut_update = 0;
    char tref_file[100] = {'\0'};

    fb_mem_instance = (v2d_num > V2D3) ? 1 : 0;
    fb_mem_base_address = (fb_mem_instance) ? FB1_SRAM_START : FB0_SRAM_START;
    clks_per_blk = (drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    skipped_blocks = capture_delay_value / clks_per_blk;   // Blocks skipped due to capture delay value

    /*First block has to be ignored*/
    if (0 == skipped_blocks)
    {
        skipped_blocks = 1;
        skipped_blocks_consecutive_updates = 1;
    }

    /*reading the first block worth of samples from REF file*/
    for (i = 0; i < skipped_blocks; i++)
    {
            if (vector_read_hex_u32(fp_ref,
                        ref_data,
                        num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC) < \
                        (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC))
            {
                printf("ERROR: Insufficient Output REF data");
                return -1;
            }
    }

    if (PDPD_LUT_48 == lut_mode)
    {
        skipped_blocks_before_lut_update = 0;
        skipped_blocks_after_lut_update = 10;
    }
    else if (PDPD_LUT_24 == lut_mode)
    {
        skipped_blocks_before_lut_update = 1;
        skipped_blocks_after_lut_update = 10;
    }
    else
    {
        skipped_blocks_before_lut_update = 2;
        skipped_blocks_after_lut_update = 10;
    }

    /*Incrementing the read address for exclusion of first block*/
    read_address = fb_mem_base_address + (skipped_blocks * num_vectors_per_block * BYTES_PER_VEC) + (address_offset * 4);

    for (iter = 0; iter < (blocks_to_compare / lut_block_duration); iter++)
    {
        /*We need to exclude last two blocks during transition*/
        for (lc = (0 + skipped_blocks_consecutive_updates); lc < (lut_block_duration - skipped_blocks_before_lut_update); lc++)
        {
            if (vector_read_hex_u32(fp_ref,
                        ref_data,
                        num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC) < \
                        (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC))
            {
                printf("ERROR: Insufficient Output REF data");
                return -1;
            }

            if (0 == lc)
            {
                address_offset = get_match_offset(read_address, ref_data[0], (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC));

                if (address_offset)
                {
                    LOG_WARNING("offset value is 0x%x", address_offset);
                }

                if (-1 == address_offset)
                {
                    LOG_ERROR("COMARISON FAILED address_offset was not found");
                    return 1;
                }

                read_address += address_offset * 4;
            }

            /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance,
             * the solution will be to update the SRP API to read the complete memory instead of word by word*/
            if (num_vectors_per_block <= 64)
            {
                num_samples = ((num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC);

                //If address_offset is nonzero the last block should be less than the actual samples
                num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

                if (rv |= read_mem_expect_18a(read_address,
                                          num_samples,
                                          ref_data,
                                          "fb_mem"))
                {
                    LOG_ERROR("Failed for block %d", (iter + 1) * lc);
                    return rv;
                }
            }
            else
            {
                rv |= read_mem_expect_18a(read_address,
                                          (64 * NUM_OF_ELEMENTS_PER_VEC),
                                          ref_data,
                                          "fb_mem");

                num_samples = (((num_vectors_per_block) - 64) * NUM_OF_ELEMENTS_PER_VEC);

                //If address_offset is nonzero the last block should be less than the actual samples
                num_samples = (lc == (blocks_to_compare - 1)) ? (num_samples - address_offset) : (num_samples);

                if (rv |= read_mem_expect_18a(read_address + (64 * BYTES_PER_VEC),
                                          num_samples,
                                          ref_data + (64 * NUM_OF_ELEMENTS_PER_VEC),
                                          "fb_mem"))
                {
                    LOG_ERROR("Failed for block %d", (iter + 1) * lc);
                    return rv;
                }
            }
            read_address += (num_vectors_per_block * BYTES_PER_VEC);
        }

        /*ten blocks needs to be excluded during transition phase*/
        skipped_blocks_consecutive_updates = skipped_blocks_after_lut_update;

        if (iter != ((blocks_to_compare / lut_block_duration) - 1))
        {
            for (i = 0; i < skipped_blocks_consecutive_updates; i++)
            {
                    if (vector_read_hex_u32(fp_ref,
                                ref_data,
                                num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC) < \
                                (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC))
                    {
                        printf("ERROR: Insufficient Output REF data");
                        return -1;
                    }
            }
        }

        read_address += (skipped_blocks_consecutive_updates * num_vectors_per_block * BYTES_PER_VEC);
        LOG_INFO("iteration passed: %d", iter);
    }

    return rv;
}

/**
 * @brief           Function for comparing the FB MEM data in repeat mode
 * @param [in]      v2d_num, add_factor and num_vectors per block.
 * @return          status value
 */
int pdpd_ingress_cap_mem_compare_repeat(repeat_mem_compare_t *mem_compare)
{
    int rv = 0, fb_mem_instance = 0, data_index = 0, add_val = 0, i = 0, j = 0, lc = 0, cnt = 0;
    uint32_t ref_data[(mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC], read_address = 0, num_samples = 0;
    int skipped_blocks = 0, address_offset = 0, clks_per_blk = 0, additional_factor = 0, skipped_blocks_consecutive_captures = 0;

    read_address = get_mem_fb_base_address(mem_compare->v2d_num);
    clks_per_blk = (mem_compare->drf_clk) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    skipped_blocks = (mem_compare->capture_delay_value) / clks_per_blk;   // Blocks skipped due to capture delay value
    skipped_blocks_consecutive_captures = (mem_compare->skip_cycles) / clks_per_blk;
    additional_factor = (mem_compare->additional_factor);

    // Reading 1MB of Capture Memory
    add_val = additional_factor + (skipped_blocks * additional_factor);

    for (cnt = 0 ; cnt < (mem_compare->num_repeat); cnt++)
    {
        for (lc = 0; lc < (mem_compare->num_blocks); lc++)
        {
            for (i = 0; i < (mem_compare->num_vectors_per_block); i++)
            {
                for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
                {
                    ref_data[data_index] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)))
                                           + add_val;
                    data_index++;
                }
            }

            if (0 == lc)
            {
                address_offset = get_match_offset(read_address, ref_data[0], ((mem_compare->num_vectors_per_block) * NUM_OF_ELEMENTS_PER_VEC));

                if (address_offset)
                {
                    LOG_WARNING("offset value is 0x%x", address_offset);
                }

                if (-1 == address_offset)
                {
                    LOG_ERROR("COMARISON FAILED address_offset was not found");
                    return 1;
                }

                if (address_offset)
                {
                    if (stale_value_compare(read_address, address_offset, (add_val - additional_factor), (mem_compare->num_vectors_per_block)))
                        LOG_ERROR("stale value comparison failed");
                }

                read_address += address_offset * 4;
            }

            /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance,
             * the solution will be to update the SRP API to read the complete memory instead of word by word*/
            if ((mem_compare->num_vectors_per_block) <= 64)
            {
                num_samples = (((mem_compare->num_vectors_per_block)) * NUM_OF_ELEMENTS_PER_VEC);

                //If address_offset is nonzero the last block should be less than the actual samples
                num_samples = (lc == ((mem_compare->num_blocks) - 1)) ? (num_samples - address_offset) : (num_samples);

                rv |= read_mem_expect_18a(read_address,
                                          num_samples,
                                          ref_data,
                                          "fb_mem");
            }
            else
            {
                rv |= read_mem_expect_18a(read_address,
                                          (64 * NUM_OF_ELEMENTS_PER_VEC),
                                          ref_data,
                                          "fb_mem");

                num_samples = ((((mem_compare->num_vectors_per_block)) - 64) * NUM_OF_ELEMENTS_PER_VEC);

                //If address_offset is nonzero the last block should be less than the actual samples
                num_samples = (lc == ((mem_compare->num_blocks) - 1)) ? (num_samples - address_offset) : (num_samples);

                rv |= read_mem_expect_18a(read_address + (64 * BYTES_PER_VEC),
                                          num_samples,
                                          ref_data + (64 * NUM_OF_ELEMENTS_PER_VEC),
                                          "fb_mem");
            }

            data_index = 0;
            add_val += additional_factor;
            read_address += ((mem_compare->num_vectors_per_block) * BYTES_PER_VEC);
        }
        add_val += (skipped_blocks_consecutive_captures * additional_factor);
        LOG_INFO("first capture was done with value %d", rv);
    }

    return rv;
}

/**
 * @brief           Function for configure the MEM_FB in repeat mode capture
 * @param [in]      size_per_sector, v2d_num and apb_num.
 * @return          status value
 */
int mem_fb_x_capture_repeat_mode_configuration(int size_per_sector, int v2d_num, int apb_num)
{

    int mem_fb_base_address = 0, power_down_control_value = MEM_FB_PWR_DOWN_CTRL_DEFAULT, mem_fb_instance = 0, start_sector = 0,
        rv = 0, sectors_per_capture_size = 0, i = 0;
    uint32_t ping_base_address = 0;

    mem_fb_instance = (v2d_num > V2D3) ? 1 : 0;
    mem_fb_base_address = (mem_fb_instance) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;

    /*How many sectors required for the given size*/
    sectors_per_capture_size = (size_per_sector / FB_MEM_SECTOR_SIZE);
    sectors_per_capture_size = (size_per_sector % FB_MEM_SECTOR_SIZE) ? (sectors_per_capture_size + 1) : (sectors_per_capture_size);

    /*Ping address always starts from Sector 0*/
    ping_base_address = start_sector * FB_MEM_SECTOR_SIZE;

    for (i = 0; i < (2 * sectors_per_capture_size); i++)
    {
        power_down_control_value &= ~(1 << i);
    }

    if (mem_fb_general_config(mem_fb_base_address, power_down_control_value))
        LOG_ERROR("MEM_FB basic configuration failed");

    if ((v2d_num % 4) < 2)
    {
        /*V2D0 and V2D1 should go to PORT0*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT0_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT0_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT2"))
            return rv;
    }
    else
    {
        /*V2D2 and V2D3 should go to PORT1*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT1_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT1_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT3"))
            return rv;

    }

    /*for ping pong buffers*/
    for (i = 0; i < 2; i++)
    {
        if (write_reg_18a(mem_fb_base_address + SECTOR_END_PTR(start_sector + i),
                          ((FB_MEM_SECTOR_SIZE * i) + size_per_sector - 1),
                          MEM_FB_SECTOR_END_PTR_WR_MASK,
                          "SECTOR_END_PTR"))
            return rv;

        if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + i),
                          (sectors_per_capture_size * FB_MEM_SECTOR_SIZE),
                          MEM_FB_SECTOR_NEXT_PTR_WR_MASK,
                          "SECTOR_NEXT_PTR"))
            return rv;
    }

    /*The next ptr for the last sector should be pointed back to start of first sector*/
    if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + (i - 1)),
                      ping_base_address,
                      MEM_FB_SECTOR_NEXT_PTR_WR_MASK,
                      "SECTOR_NEXT_PTR"))
        return rv;

    // Enable the FB MEM, this should be last register of FB_MEM to be configured
    if (write_reg_18a(MEM_FB_EN_ADR(mem_fb_base_address),
                      0x1,
                      MEM_FB_EN_WR_MASK,
                      "MEM_FB_MEM_ENABLE"))
        return rv;
}

/**
 * @brief           Function for configure the MEM_FB in repeat mode capture for QUAD
 * @param [in]      quad_instance, num_antennas and size_per_antenna.
 * @return          status value
 */
int quad_mem_fb_x_capture_repeat_mode_configuration(int quad_instance, int num_antennas, int size_per_antenna)
{

    int mem_fb_base_address = 0, power_down_control_value = MEM_FB_PWR_DOWN_CTRL_DEFAULT, mem_fb_instance = 0, start_sector = 0,
        rv = 0, i = 0, sectors_per_capture_size = 0, num_buffers = 0, lc = 0;
    uint32_t ping_base_address = 0;

    LOG_INFO("size_per_antenna: 0x%x", size_per_antenna);

    mem_fb_instance = (quad_instance > 1) ? 1 : 0;
    mem_fb_base_address = (mem_fb_instance) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;

    /*How many sectors required for the given size*/
    sectors_per_capture_size = (size_per_antenna / FB_MEM_SECTOR_SIZE);
    sectors_per_capture_size = (size_per_antenna % FB_MEM_SECTOR_SIZE) ? (sectors_per_capture_size + 1) : (sectors_per_capture_size);

    /*Ping address always starts from Sector 0*/
    ping_base_address = start_sector * FB_MEM_SECTOR_SIZE;

    /*As we require ping and pong memories for each antenna*/
    for (i = 0; i < (2 * num_antennas * sectors_per_capture_size); i++)
    {
        power_down_control_value &= ~(1 << i);
    }

    if (mem_fb_general_config(mem_fb_base_address, power_down_control_value))
        LOG_ERROR("MEM_FB basic configuration failed");

    if (0 == (quad_instance % 2))
    {
        /*V2D0 and V2D1 should go to PORT0*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT0_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT0_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT2"))
            return rv;
    }
    else
    {
        /*V2D2 and V2D3 should go to PORT1*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT1_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT1_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT3"))
            return rv;
    }

    for (lc = 0; lc < 2; lc++)
    {
        for (i = 0; i < num_antennas; i++)
        {

            if (write_reg_18a(mem_fb_base_address + SECTOR_END_PTR(start_sector + num_buffers),
                              ((FB_MEM_SECTOR_SIZE * num_buffers) + size_per_antenna - 1),
                              MEM_FB_SECTOR_END_PTR_WR_MASK,
                              "SECTOR_END_PTR"))
                return rv;

            if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + num_buffers),
                              ((num_buffers + 1) * sectors_per_capture_size * FB_MEM_SECTOR_SIZE),
                              MEM_FB_SECTOR_NEXT_PTR_WR_MASK,
                              "SECTOR_NEXT_PTR"))
                return rv;

            num_buffers++;
        }
    }

    /*The Next Ptr should point to start of first block*/
    if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + (num_buffers - 1)),
                      ping_base_address,
                      MEM_FB_SECTOR_NEXT_PTR_WR_MASK,
                      "SECTOR_NEXT_PTR"))
        return rv;

    // Enable the FB MEM, this should be last register of FB_MEM to be configured
    if (write_reg_18a(MEM_FB_EN_ADR(mem_fb_base_address),
                      0x1,
                      MEM_FB_EN_WR_MASK,
                      "MEM_FB_MEM_ENABLE"))
        return rv;
}

/**
 * @brief           Function for getting the index offset where the match found
 * @param [in]      address, ref_data and size.
 * @return          offset value
 */
int get_match_offset(uint32_t address, uint32_t ref_data, int size)
{
    int offset = 0, read_value = 0;
    uint32_t buffer[size];

    /*This Work around is required as FRIO is going bad if we read more than 2K samples at a single instance, the solution will be to update
     * the SRP API to read the complete memory instead of word by word*/
    if (size < 2048)
    {
        read_mem_18a(address, size, buffer, "FB_MEM");
    }
    else
    {
        read_mem_18a(address, 2048, buffer, "FB_MEM");
        read_mem_18a(address, (size - 2048), buffer + 2048, "FB_MEM");
    }

    /*Compare the data to get the offset match*/
    for (offset = 0; offset < size; offset++)
    {
        if (ref_data == buffer[offset])
            return offset;
    }

    return -1;
}

/**
 * @brief           Function for comparing the part of the block data
 * @param [in]      address, offset in the block, add_val and num_vectors_per_block.
 * @return          status
 */
int stale_value_compare(uint32_t address, int offset, int add_val, int num_vectors_per_block)
{
    int i = 0, j = 0, data_index = 0, compare_start_offset = 0, ref_data_index = 0, rv = 0;
    uint32_t ref_data[offset];

    compare_start_offset = (num_vectors_per_block * NUM_OF_ELEMENTS_PER_VEC) - offset;

    for (i = 0; i < num_vectors_per_block; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            if (data_index >= compare_start_offset)
            {
                ref_data[ref_data_index] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)))
                                           + add_val;
                ref_data_index++;
            }
            data_index++;
        }
    }

    rv = read_mem_expect_18a(address, offset, ref_data, "FB_MEM");

    return rv;
}

/**
 * @brief           Function for filling the MEM_FB
 * @param [in]      v2d_num and fill value
 * @return          none
 */
void fill_mem_fb(int v2d_num, uint32_t value)
{
    uint32_t buffer[MEM_FB_ACCESS_SIZE / 4], address = 0;
    int lc = 0, fb_mem_instance = 0, base_address = 0;

    base_address = get_mem_fb_base_address(v2d_num);

    fill_buffer(buffer, (MEM_FB_ACCESS_SIZE / 4), value);

    for (lc = 0; lc < (MEM_FB_SIZE / MEM_FB_ACCESS_SIZE); lc++)
    {
        write_mem_18a(base_address, (MEM_FB_ACCESS_SIZE / 4), buffer, "MEM_FB");
        base_address += (MEM_FB_ACCESS_SIZE);
    }
}

/**
 * @brief           compare one block of the MEM_FB
 * @param [in]      v2d_num, num_vectors_per_block, fill value and block_num
 * @return          status value
 */
int fb_mem_compare_extra_block(int v2d_num, int num_vectors, uint32_t value, int block_num)
{
    uint32_t ref_data[num_vectors * NUM_OF_ELEMENTS_PER_VEC], read_address = 0, num_samples = 0;
    int rv = 0;

    read_address = get_mem_fb_base_address(v2d_num);
    read_address += (block_num * num_vectors * NUM_OF_ELEMENTS_PER_VEC * 4);

    fill_buffer(ref_data, num_vectors * NUM_OF_ELEMENTS_PER_VEC, value);

    rv = read_mem_expect_18a(read_address, num_vectors * NUM_OF_ELEMENTS_PER_VEC, ref_data, "MEM_FB");
    return rv;
}

/**
 * @brief           function to get the MEM_FB base address based on V2D num
 * @param [in]      v2d_num
 * @return          MEM_FB base address
 */
uint32_t get_mem_fb_base_address(int v2d_num)
{
    int mem_fb_instance = 0;
    uint32_t mem_fb_base_address = 0;

    mem_fb_instance = (v2d_num > V2D3) ? 1 : 0;
    mem_fb_base_address = (mem_fb_instance) ? FB1_SRAM_START : FB0_SRAM_START;

    return mem_fb_base_address;
}

/**
 * @brief           Function for loading the vex params to it's DMEM
 * @param [in]      vex_core_id, size, pointer to array of offset, pointer to array of values
 * @return          status value
 */
int load_vex_param(int vex_core_id, int size, unsigned int *offset, unsigned int *val)
{
    int i = 0, rv = 0;
    unsigned int vex_dmem_addr = VEX_DMEM(vex_core_id);

    for (i = 0; i < size; i++)
    {
        rv |= write_reg_18a((vex_dmem_addr + offset[i]), val[i], 0xFFFFFFFF, "VEX_DMEM_WRITE");
    }

    return rv;
}

/**
 * @brief           Function to check whether 1us VEX granularity is required or not
 * @param [in]      drf_clock and test_config
 * @return          bool value
 */
bool get_us_granularity_status(drf_clock_t drf_clock, int test_config)
{
    bool result = FALSE;
    pdpd_rate_t pdpd_in_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];

    if ((CLOCK_983M == drf_clock) && (pdpd_in_rate <= 2))
    {
        result = TRUE;
    }
    else if ((CLOCK_1P5G == drf_clock) && (pdpd_in_rate <= 1))
    {
        result = TRUE;
    }
    return result;
}

/**
 * @brief           Function to read the input pattern
 * @param [in]      pointer to integer and char pointer
 * @return          status value 0 - SUCCESS.
 */
int input_pattern_read(int *input_data, char *file)
{
    FILE *fp_input = NULL;

    LOG_INFO("input_file: %s", file);

    fp_input = fopen(file, "r");

    if (NULL == fp_input)
    {
        LOG_ERROR("Not able to open the file");
        return -1;
    }

    if (vector_read_hex_u32(fp_input,
                input_data,
                VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC) < \
                (VEX_VMEM_IN_VEC * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_ERROR("Insufficient input REF data");
        return -1;
    }

    fclose(fp_input);
    return 0;
}

/**
 * @brief           Function to get the frac_os
 * @param [in]      test_config
 * @return          frac_os value.
 */
int get_frac_os(int test_config)
{
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    int frac_os = 0;
    int rate_array[PDPD_NUM_SAMPLE_RATES] = {0, 1, 2, 4, 8};

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    frac_os = (pdpd_in_rate == pdpd_out_rate) ? 1 : (rate_array[pdpd_in_rate] / rate_array[pdpd_out_rate]);
    return frac_os;
}

#ifndef E2E_FLOW_EN
/**
 * @brief           Function for resetting and loading elf to RCS
 * @param [in]      pointers to srp and rcs_hdl
 * @return          status value
 */
int rcsHaltsoftReset(void)
{
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
    unsigned rcs_ctrl = 0;
    int rv;

    rcs_gpreg_rcs_cfg_reg_t  rcs_config_reg = {.value = RCS_GPREG_RCS_CFG_DEFAULT};
    rcs_gpreg_core0_ctrl_reg_t core0_control_reg = {.value = RCS_GPREG_CORE0_CTRL_DEFAULT};
    rcs_gpreg_core1_ctrl_reg_t core1_control_reg = {.value = RCS_GPREG_CORE1_CTRL_DEFAULT};
    rcs_gpreg_core2_ctrl_reg_t core2_control_reg = {.value = RCS_GPREG_CORE2_CTRL_DEFAULT};
    rcs_gpreg_core3_ctrl_reg_t core3_control_reg = {.value = RCS_GPREG_CORE3_CTRL_DEFAULT};
    rcs_gpreg_soft_rst_reg_t soft_reset_reg = {.value = RCS_GPREG_SOFT_RST_DEFAULT};

    // halt core0/1/2/3
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
    write_reg_18a(RCS_GPREG_CORE1_CTRL_ADR, RCS_GPREG_CORE1_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE1_CONTROL_ADR");
    write_reg_18a(RCS_GPREG_CORE2_CTRL_ADR, RCS_GPREG_CORE2_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE2_CONTROL_ADR");
    write_reg_18a(RCS_GPREG_CORE3_CTRL_ADR, RCS_GPREG_CORE3_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE3_CONTROL_ADR");

    // enable soft reset
    rcs_config_reg.SOFT_RST_LOCK = 0xFA;
    write_reg_18a(RCS_GPREG_RCS_CFG_ADR, rcs_config_reg.value,0xFFFFFFFF, "RCS_GPREG_RCS_CONFIG_ADR");

    // soft reset core0
    core0_control_reg.SOFT_RESET_CORE0 = 0x1;
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, soft_reset_reg.value,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
    //soft reset core 1/2/3
    soft_reset_reg.CORE1_CPU_SFT_RST = 0x1;
    soft_reset_reg.CORE2_CPU_SFT_RST = 0x1;
    soft_reset_reg.CORE3_CPU_SFT_RST = 0x1;
    write_reg_18a(RCS_GPREG_SOFT_RST_ADR, soft_reset_reg.value,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

    sleep(1);

    // remove soft reset core0
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
    // remove soft reset of cores 1/2/3
    write_reg_18a(RCS_GPREG_SOFT_RST_ADR, RCS_GPREG_SOFT_RST_DEFAULT,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

    sleep(1);

    return rv;
}
#endif
