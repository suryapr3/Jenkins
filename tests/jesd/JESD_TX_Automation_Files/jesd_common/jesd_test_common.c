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
 * @file    jesd_test_common.c
 * @brief   This file contains the common functionality used across jesd tests.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "jesd_test_common.h"

#define jesd_rx_4kb_dump           0

#define dnrt_to_jesd_ip_path_en    1  // jesd_ip or parallel lpbk
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
// Array of Struct to hold TC config    : Refer TC config
struct jesd_tc_config_t jesd_tc_config_arr[42] = 
{
    // testcase_id, usecase_id, flow_id, vex_id, jesd_id
    
    //16G usecases TC_0-TC_7(4 streams; 8 streams; 16 streams)
    //TC0-TC1 - RX 16G 4 stream usecseas
    {TC_0, UC_3A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_1, UC_7C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    //TC2-TC4 - RX 16G 8 stream usecseas
    {TC_2, UC_5C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_3, UC_2B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_4, UC_3B, flow_rx_dnrt_to_vex, vex_0, jesd_0},

    //TC5-TC6 - RX 16G 16 stream usecseas
    {TC_5, UC_2C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_6, UC_3D, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    //RX 32G usecases TC_7-TC_20(1 stream; 2 streams; 4 streams ; 8 streams ;16 streams)
    //TC7-TC9 - RX 32G 1 stream usecseas
    {TC_7, UC_9A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_8, UC_11A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_9, UC_13A, flow_rx_dnrt_to_vex, vex_0, jesd_0},

    //TC10-TC12 - RX 32G 2 stream usecseas
    {TC_10, UC_7B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_11, UC_9B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_12, UC_11C, flow_rx_dnrt_to_vex, vex_0, jesd_0},

    //TC13-TC15 - RX 32G 4 stream usecseas
    {TC_13, UC_5B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_14, UC_7E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_15, UC_9C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    //TC16-TC18 - RX 32G 8 stream usecseas
    {TC_16, UC_5E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_17, UC_3C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_18, UC_7G, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    //TC19-TC20 - RX 32G 16 stream usecseas
    {TC_19, UC_3E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_20, UC_5F, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    //TC21-TC22 - TX 16G 4 stream usecseas
    {TC_21, UC_3A, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_22, UC_7C, flow_tx_vex_to_dnrt, vex_0, jesd_0},
	
    //TC23-TC24 - TX 16G 8 stream usecseas
    {TC_23, UC_5C, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_24, UC_2B, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_25, UC_3B, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //TC26 - TC28 TX 32G 8 stream usecseas
    {TC_26, UC_5E, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_27, UC_3C, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_28, UC_7G, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //TC29 - TC31 TX 32G 4 stream usecseas
    {TC_29, UC_5B, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_30, UC_7E, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_31, UC_9C, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //TC32 - TX 32G 1 stream usecseas
    {TC_32, UC_9A, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //TC33 - TC34 TX 32G 2 stream usecseas
    {TC_33, UC_7B, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_34, UC_9B, flow_tx_vex_to_dnrt, vex_0, jesd_0},

	//Glue level lpbk 5c 
	{TC_35, UC_5C, flow_lpbk_glue, vex_0, jesd_0},
    
    //NSIP level lpbk 5c 
	{TC_36, UC_5C, flow_lpbk_nsip, vex_0, jesd_0},
    
    //IP level lpbk 5c 
	{TC_37, UC_5C, flow_lpbk_ip, vex_0, jesd_0},
    
    //DNRT to RSB capture
    {TC_38, UC_5C, flow_rsb_capt, vex_0, jesd_0},
    
    //rx_ip_4k_capture
    {TC_39, UC_5C, flow_rx_ip_4k_capture, vex_0, jesd_0},

    //DNRT to RSB source mode
    {TC_40, UC_5C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //tsb capture mode
    {TC_41, UC_5C, flow_tx_tsb_cap_mode, vex_0, jesd_0},
};

// Array of Struct to hold link config  : Refer UC config
struct jesd_config_t jesd_config_arr[22] = 
{
    /* jesd_config
    arr[i]={
        jesd_link_config ->         {usecase_id, Sample rate, L, M, F, S, N', JESD04C/D, Serdes rate, E, Soni, clk ratio, smpl_pos/neg, link_iq_bw},
        jesd_hbi_config_t->         {hbi_int_high_en, hbi_int_low_en},
        
        jesd_rx_ip_config ->        {{crc3_enable, crc12_enable, rx_emb_err_thresh, rx_sh_err_thresh, cmd_enable}, jesd_ip_enable, jesd_rx_ip_sysref_enable} ,
        jesd_rx_cmn_csr_config_t->  {rx_ip_clk_ctrl, rx_sysref_tsad, rx_sync_point_ctrl, rx_bfn_sysref_tsad, rx_bfn_sync_point_ctrl, rx_clk_1p5g_div_en, rx_clk_gen, rx_sync_point_cnt_en, rx_bfn_sync_point_cnt_en},
        jesd_rx_glue_config_t->     {rx_dp_gate_sel,rx_dp_init_cyc_cnt},
        jesd_h2b_config_t->         {h2b_fifo_ctrl,h2b_credit_ready},
        
        jesd_tx_ip_config_t->       {{crc3_enable, crc12_enable, tx_tl_latency, tx_smpl_req, cmd_enable},jesd_ip_enable,jesd_rx_ip_sysref_enable}
        jesd_tx_cmn_csr_config_t->  {tx_ip_clk_ctrl, tx_sysref_tsad, tx_sync_point_ctrl, tx_bfn_sysref_tsad, tx_bfn_sync_point_ctrl, tx_clk_1p5g_div_en, tx_clk_gen, tx_sync_point_cnt_en, tx_bfn_sync_point_cnt_en},
        jesd_tx_glue_config_t->     {tx_conv_dp_cfg, tx_srg_pat_cfg_low, tx_srg_pat_period_cfg, tx_srg_pat_del_cfg, tx_min_max_occupn_cp_en, tx_dp_gate_sel, tx_strm_phm_en, tx_srg_pat_en},
        jesd_b2h_config_t->         {b2h_fifo_ctrl,b2h_credit_ready},
    */

    //RX 16G usecases TC_0-TC_6(4 streams; 8 streams; 16 streams)
    //TC0-TC1 - RX 16G 4 stream usecseas
    //UC_3A -> arr[0]
    {
        //cmn
        {UC_3A, sample_rate_122P88, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1, 512},
        {0xFFFFF, 0xFFFFF},
    
        //rx
        {{disable, disable, err_thresh_3, err_thresh_3, disable }, enable, enable },
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x00000101, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_7C -> arr[1]
    {
        //cmn
        {UC_7C, sample_rate_491P52, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_2_1, smpl_trans_1_0, 2048},
        {0xFFFFF, 0xFFFFF},
    
        //rx
        {  {disable, disable, err_thresh_4, err_thresh_4, disable }, enable, enable },
        {0x00000014, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000009, 0x00000000, disable},enable,enable},
        {0x00000014, 0x00000001, 0x00010001, 0x00000001, 0x00010001, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //TC2-TC4 - RX 16G 8 stream usecseas
    //UC_5C -> arr[2]
    {
        //cmn
        {UC_5C, sample_rate_245P76, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0, 2048},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000018, 0x0000000f, 0x001f007f, 0x0000000f, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},
        
        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },
    
    //UC_2B -> arr[3]
    {
        //cmn
        {UC_2B, sample_rate_61P44, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3, 512},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000018, 0x00000013, 0x0003001f, 0x00000013, 0x0003001f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000010, 0x00000301, disable},enable,enable},
        {0x00000018, 0x00000017, 0x00170023, 0x00000017, 0x00170023, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_3B -> arr[4]
    {
        //cmn
        {UC_3B, sample_rate_122P88, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1, 1024},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x00000101, disable},enable,enable},
        {0x00000018, 0x00000017, 0x00170023, 0x00000017, 0x00170023, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //TC5-TC6 - RX 16G 16 stream usecseas
    //UC_2C -> arr[5]
    {
        //cmn
        {UC_2C, sample_rate_61P44, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
    
        //rx
        {  {disable, disable, err_thresh_3, err_thresh_3, disable }, enable, enable },
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_3D -> arr[6]
    {
       //cmn 
        {UC_3D, sample_rate_122P88, l_4, m_32, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
        {0xFFFFF, 0xFFFFF},
    
       //rx
        {  {disable, disable, err_thresh_9, err_thresh_9, disable }, enable, enable },
        {0x00000018, 0x00000007, 0x0003000b, 0x00000007, 0x0003000b, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    
    },
    
    //RX 32G usecases TC_7-TC_20(1 stream; 2 streams; 4 streams ; 8 streams ;16 streams)
    //TC7-TC9 - RX 32G 1 stream usecseas
    //UC_9A -> arr[7]
    {
        //cmn
        {UC_9A, sample_rate_983P04, l_1, m_2, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_2_1, smpl_trans_1_0, 1024},
        {0xFFFFF, 0xFFFFF},
    
        //rx
        {  {disable, disable, err_thresh_9, err_thresh_9, disable }, enable, enable },
        {0x00000000, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000009, 0x00000000, disable},enable,enable},
        {0x00000000, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_11A -> arr[8]
    {
        //cmn
        {UC_11A, sample_rate_1966P08, l_2, m_2, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_trans_1_0, 2048},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_3, err_thresh_3, disable}, enable, enable},
        {0x00000004, 0x00000003, 0x00030013, 0x00000003, 0x00030013, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
        
        //tx
        {{disable, disable, 0x0000000a, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000f, 0x000f007f, 0x0000000f, 0x000f007f, enable, enable, enable, enable},
        {0x00000122, 0x00000003, 0x00000001, 0x00000000, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },
    
    //UC_13A -> arr[9]
    {
            //cmn
            {UC_13A, sample_rate_3932P16, l_4, m_2, f_1, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_2_1, smpl_trans_1_0},
            {0xFFFFF, 0xFFFFF},
        
            //rx
            {  {disable, disable, err_thresh_4, err_thresh_4, disable }, enable, enable },
            {0x00000000, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
    },
    
    //TC10-TC12 - RX 32G 2 stream usecseas
    //UC_7B -> arr[10]
    {
        //cmn
        {UC_7B, sample_rate_491P52, l_1, m_4, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0, 1024},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_9B -> arr[11]
    {
        //cmn
        {UC_9B, sample_rate_983P04, l_2, m_4, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_2, clk_ratio_1_1, smpl_trans_1_0, 2048},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x00000005, 0x00030007, 0x00000005, 0x00030007, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_11C -> arr[12]
    {
        //cmn
        {UC_11C, sample_rate_1966P08, l_4, m_4, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_trans_1_0, 4096},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
        
        //tx
        {{disable, disable, 0x0000000a, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000122, 0x00000003, 0x00000001, 0x00000000, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },
    
    //TC13-TC15 - RX 32G 4 stream usecseas
    //UC_5B -> arr[13]
    {
        //cmn
        {UC_5B, sample_rate_245P76, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1, 1024},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_7E -> arr[14]
    {
        //cmn
        {UC_7E, sample_rate_491P52, l_2, m_8, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0, 2048},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000010, 0x00000001, disable},enable,enable},
        {0x00000004, 0x00000009, 0x0007000f, 0x00000009, 0x0007000f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_9C -> arr[15]
    {
        //cmn
        {UC_9C, sample_rate_983P04, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_2, clk_ratio_1_1, smpl_trans_1_0, 4096},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x0000000c, disable},enable,enable},
        {0x00000004, 0x00000009, 0x0007000f, 0x00000009, 0x0007000f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //TC16-TC18 - RX 32G 8 stream usecseas
    //UC_5E -> arr[16]
    {
        //cmn
        {UC_5E, sample_rate_245P76, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1, 2048},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0x8}
    },
    
    //UC_3C -> arr[17]
    {
        //cmn
        {UC_3C, sample_rate_122P88, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3, 1024},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000010, 0x00000301, disable},enable,enable},
        {0x00000004, 0x0000000b, 0x000b0011, 0x0000000b, 0x000b0011, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    //UC_7G -> arr[18]
    {
        //cmn
        {UC_7G, sample_rate_491P52, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0, 4096},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},

        //tx
        {{disable, disable, 0x00000010, 0x00000001, disable},enable,enable},
        {0x00000004, 0x0000000b, 0x000b0011, 0x0000000b, 0x000b0011, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0x8}
    },
    
    //TC19-TC20 - RX 32G 16 stream usecseas
    //UC_3E -> arr[19]
    {
        //cmn
        {UC_3E, sample_rate_122P88, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000003, 0x00010005, 0x00000003, 0x00010005, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_5F -> arr[20]
    {
        //cmn
        {UC_5F, sample_rate_245P76, l_4, m_32, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000003, 0x00010005, 0x00000003, 0x00010005, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    }
    
};

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
struct vex_strm2cio_config_t   vex_strm2cio_config;
struct vex_cio2strm_config_t   vex_cio2strm_config;
struct jesd_config_t           jesd_config;
struct jesd_tc_config_t        jesd_tc_config;

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
 * @brief           Function for assigning TC specific values to jesd_tc_config struct
 * @param [in]      jesd_tc_config_arr[],testcase_id
 * @return          
 */
void assign_tc_config(struct jesd_tc_config_t *jesd_tc_config_arr_ptr, uint32_t testcase)
{
    
    printf("Assigning TC config \n");
     // JESD TC selection
    jesd_tc_config.testcase_id                                                  = jesd_tc_config_arr_ptr[testcase].testcase_id;
    jesd_tc_config.usecase_id                                                   = jesd_tc_config_arr_ptr[testcase].usecase_id;
    jesd_tc_config.flow_id                                                      = jesd_tc_config_arr_ptr[testcase].flow_id;
    jesd_tc_config.vex_id                                                       = jesd_tc_config_arr_ptr[testcase].vex_id;
    jesd_tc_config.jesd_id                                                      = jesd_tc_config_arr_ptr[testcase].jesd_id;
}

/**
 * @brief           Function for assigning UC specific values to jesd_link_config struct
 * @param [in]      jesd_config_arr[],usecase_id
 * @return          
 */
 // todo: change the name of function it is not just link_config anymore
void assign_jesd_config(struct jesd_config_t *jesd_config_arr_ptr, uint32_t usecase) 
{
    // Select usecase from tbl 
    printf("Assigning link config \n");
    printf("usecase %d \n",usecase);
    
    // JESD link config : Refer UC table
    jesd_config.jesd_link_config.usecase_id                                     = jesd_config_arr_ptr[usecase].jesd_link_config.usecase_id;
    jesd_config.jesd_link_config.sample_rate                                    = jesd_config_arr_ptr[usecase].jesd_link_config.sample_rate;
    jesd_config.jesd_link_config.lanes                                          = jesd_config_arr_ptr[usecase].jesd_link_config.lanes;
    jesd_config.jesd_link_config.converters                                     = jesd_config_arr_ptr[usecase].jesd_link_config.converters;
    jesd_config.jesd_link_config.frames                                         = jesd_config_arr_ptr[usecase].jesd_link_config.frames;
    jesd_config.jesd_link_config.smpl_per_frame                                 = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_per_frame;
    jesd_config.jesd_link_config.smpl_total_bits                                = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_total_bits;
    jesd_config.jesd_link_config.serdes_rate                                    = jesd_config_arr_ptr[usecase].jesd_link_config.serdes_rate;
    jesd_config.jesd_link_config.min_e                                          = jesd_config_arr_ptr[usecase].jesd_link_config.min_e;
    jesd_config.jesd_link_config.sonif                                          = jesd_config_arr_ptr[usecase].jesd_link_config.sonif;
    jesd_config.jesd_link_config.smpl_char_clk_ratio                            = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_char_clk_ratio;
    jesd_config.jesd_link_config.smpl_trans_pos_neg                             = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_trans_pos_neg;
    jesd_config.jesd_link_config.link_iq_bw                                     = jesd_config_arr_ptr[usecase].jesd_link_config.link_iq_bw;
    
     // JESD HBI
    jesd_config.jesd_hbi_config.hbi_int_high_en                                 = jesd_config_arr_ptr[usecase].jesd_hbi_config.hbi_int_high_en;  
    jesd_config.jesd_hbi_config.hbi_int_low_en                                  = jesd_config_arr_ptr[usecase].jesd_hbi_config.hbi_int_low_en;  

    
    // JESD 204C ONLY REG - RX 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable               = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable              = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable;     
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh         = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh          = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh; 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable                = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable;
    
    // JESD RX IP EN AND SYSREF EN
    jesd_config.jesd_rx_ip_config.jesd_ip_enable                                = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_ip_enable;                   
    jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable                      = jesd_config_arr_ptr[usecase].jesd_rx_ip_config.jesd_rx_ip_sysref_enable;
    
    // JESD CMN CSR - RX
    jesd_config.jesd_rx_cmn_csr_config.rx_ip_clk_ctrl                           = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_ip_clk_ctrl;              
    jesd_config.jesd_rx_cmn_csr_config.rx_sysref_tsad                           = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_sysref_tsad;             
    jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_ctrl                       = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_sync_point_ctrl;          
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad                       = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad;          
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl                   = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl;
    jesd_config.jesd_rx_cmn_csr_config.rx_clk_1p5g_div_en                       = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_clk_1p5g_div_en;
    jesd_config.jesd_rx_cmn_csr_config.rx_clk_gen                               = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_clk_gen;  
    jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_cnt_en                     = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_sync_point_cnt_en; 
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en                 = jesd_config_arr_ptr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en;    

    // JESD GLUE - RX 
    jesd_config.jesd_rx_glue_config.rx_dp_gate_sel                              = jesd_config_arr_ptr[usecase].jesd_rx_glue_config.rx_dp_gate_sel;
    jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt                          = jesd_config_arr_ptr[usecase].jesd_rx_glue_config.rx_dp_init_cyc_cnt;
    
     // JESD H2B - RX
    jesd_config.jesd_h2b_config.h2b_fifo_ctrl                                   = jesd_config_arr_ptr[usecase].jesd_h2b_config.h2b_fifo_ctrl;    
    jesd_config.jesd_h2b_config.h2b_credit_ready                                = jesd_config_arr_ptr[usecase].jesd_h2b_config.h2b_credit_ready;
    
    // JESD 204C ONLY REG - TX
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable               = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable              = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable;     
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency             = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req               = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req; 
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable                = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable;
    
     // JESD TX IP EN
    jesd_config.jesd_tx_ip_config.jesd_ip_enable                                = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_ip_enable; 
    jesd_config.jesd_tx_ip_config.jesd_tx_ip_sysref_enable                      = jesd_config_arr_ptr[usecase].jesd_tx_ip_config.jesd_tx_ip_sysref_enable;
    
    // JESD CMN CSR - TX
    jesd_config.jesd_tx_cmn_csr_config.tx_ip_clk_ctrl                           = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_ip_clk_ctrl;              
    jesd_config.jesd_tx_cmn_csr_config.tx_sysref_tsad                           = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_sysref_tsad;             
    jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_ctrl                       = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_sync_point_ctrl;          
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad                       = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad;          
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl                   = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl;
    jesd_config.jesd_tx_cmn_csr_config.tx_clk_1p5g_div_en                       = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_clk_1p5g_div_en;
    jesd_config.jesd_tx_cmn_csr_config.tx_clk_gen                           	= jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_clk_gen;
    jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_cnt_en                     = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_sync_point_cnt_en; 
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en                 = jesd_config_arr_ptr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en;    

    // JESD GLUE - TX 
    jesd_config.jesd_tx_glue_config.tx_conv_dp_cfg                              = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_conv_dp_cfg;
    jesd_config.jesd_tx_glue_config.tx_srg_pat_cfg_low                          = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_srg_pat_cfg_low;
    jesd_config.jesd_tx_glue_config.tx_srg_pat_period_cfg                       = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_srg_pat_period_cfg;
    jesd_config.jesd_tx_glue_config.tx_srg_pat_del_cfg                          = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_srg_pat_del_cfg;
    jesd_config.jesd_tx_glue_config.tx_tsb_min_max_occupancy_capt_en            = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_tsb_min_max_occupancy_capt_en;
    jesd_config.jesd_tx_glue_config.tx_dp_gate_sel                              = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_dp_gate_sel;
    jesd_config.jesd_tx_glue_config.tx_strm_phm_en                              = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_strm_phm_en;
    jesd_config.jesd_tx_glue_config.tx_srg_pat_en                               = jesd_config_arr_ptr[usecase].jesd_tx_glue_config.tx_srg_pat_en;
    
    // JESD B2H - TX
    jesd_config.jesd_b2h_config.b2h_fifo_ctrl                                   = jesd_config_arr_ptr[usecase].jesd_b2h_config.b2h_fifo_ctrl;    
    jesd_config.jesd_b2h_config.b2h_credit_ready                                = jesd_config_arr_ptr[usecase].jesd_b2h_config.b2h_credit_ready;
    
}

/**
 * @brief           Function for assigning default values to jesd_config struct
 * @param [in]      jesd_link_config_arr[],use_case_id
 * @return          
 */
void assign_defaults()
{
    printf("Assigning default values \n");
    
    // JESD LINK CONFIG
    jesd_config.jesd_link_config.subclass                                       = subclass_1;
    jesd_config.jesd_link_config.ctrl_frames_cf                                 = cf_0;
    jesd_config.jesd_link_config.ctrl_bits_cs                                   = cs_0;
    jesd_config.jesd_link_config.smpl_res                                       = n_16;
    jesd_config.jesd_link_config.high_density                                   = hd_0;
    jesd_config.jesd_link_config.scr                                            = enable;
    jesd_config.jesd_link_config.fec.fec_enable                                 = disable;
    jesd_config.jesd_link_config.bit_order.bitorder                             = bitorder_3;
    jesd_config.jesd_link_config.tl_testmode                                    = disable;
    
    // VEX - STRM2CIO
    vex_strm2cio_config.strm2cio_int_en                                         = 0xF;              
    vex_strm2cio_config.strm2cio_fifo_sts_ctrl                                  = 0x00000001;                   
    vex_strm2cio_config.strm2cio_wrd_cnt_ctrl                                   = 0x00000001;    

    // VEX - CIO2STRM
    vex_cio2strm_config.cio2strm_int_en                                         = 0x3F;              
    vex_cio2strm_config.cio2strm_fifo_sts_ctrl                                  = 0x00000001;                   
    vex_cio2strm_config.cio2strm_wrd_cnt_ctrl                                   = 0x00000001;   
}

/**
 * @brief           Function for configuring fpga clk and sysref period
 * @param [in]      serdes_rate_sel, clk_ratio
 * @return          
 */
void fpga_clk_and_sysref_period(uint32_t serdes_rate_sel, uint32_t clk_ratio)
{ 

    printf("INFO : Starting fpga_clk_and_sysref_period \n");
    printf("INFO : Starting serdes_rate_sel_before_switch:%d, %d \n",serdes_rate_sel, clk_ratio);
    switch (serdes_rate_sel)
    {
        case serdes_rate_8P11008: 
        case serdes_rate_24P33024: 
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 
        
            printf("ERROR: Configure clocks for serdes rate id %d - selection failed \n ", serdes_rate_sel);
            break;
            
        case serdes_rate_16P22016: //TODO : provide enum name instead of value
            
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("16G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x10");
                    break;

                case clk_ratio_2_1:
                    printf("16G clk_ratio 2_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x00");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x00");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x00");
                    break;
                    
                default:
                printf("16G default\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x10");
                    break;
            } 
            
            printf("16G_after def \n");  
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
            
            printf("16G IP \n");
            //enable jesd_ip path or serial or parallel lpbk
            system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
            //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
            //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
            break;
        
        case serdes_rate_32P44032:
            switch (clk_ratio)
            {
                
                case clk_ratio_1_1:
                    printf("32G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x14");
                    break;
                    
                case clk_ratio_2_1:
                    printf("32G clk_ratio 2_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x04");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x04");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x04");
                    break;
                    
                default:
                    printf("32G clk_ratio 1_1 default \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b3 -P 0x20000 0x14");
                    break;
            }
            
            printf("32G after def \n");
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
                
            printf("32G IP \n");
            //enable jesd_ip path or serial or parallel lpbk
            system("frioPciWrite -F s5a3 -P 0x20000 0x06"); //IP
            //system("frioPciWrite -F s5a3 -P 0x20000 0x04"); //Serial
            //system("frioPciWrite -F s5a3 -P 0x20000 0x05"); //Parallel
            break;
        
        default:
            printf("ERROR : Unexpected serdes rate \n");
            break;
    }
}

/**
 * @brief           Function for enabling sysref
 * @param [in]      serdes_rate_sel, clk_ratio
 * @return          
 */
void fpga_provided_sysref(uint32_t serdes_rate_sel,uint32_t clk_ratio)
{
    printf("INFO : Starting fpga_provided_sysref \n");
    printf("INFO : Starting serdes_rate_sel_before_switch:%d, %d \n",serdes_rate_sel, clk_ratio);

    //Enable sysref
    switch (serdes_rate_sel)
    {
        case serdes_rate_8P11008: 
        case serdes_rate_24P33024: 
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 
        
        printf("ERROR : Configure clocks for serdes rate id %d - selection failed \n", serdes_rate_sel);
        break;
        case serdes_rate_16P22016:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("16G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
                    break;
                    
                case clk_ratio_2_1:
                    printf("16G clk_ratio 2_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x80");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x80");
                    break;
                    
                default:
                    printf("16G clk_ratio 1_1 default \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
                    break;
            }
          break;

        
        case serdes_rate_32P44032:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("32G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x94");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x94");
                    break;
                    
                case clk_ratio_2_1:
                    printf("32G clk_ratio 2_1 \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x84");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x84");
                    break;
                    
                default:
                    printf("32G clk_ratio 1_1 default \n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x94");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x94");
                    break;
            }
            break;
       
       default:
            printf("ERROR: Unexpected Serdes rate \n");
            break;
    }
} 

/**
 * @brief           Function for calculating delay 
 * @param [in]      milliseconds
 * @return          
 */
void delay(unsigned int milliseconds)
{
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

/**
 * @brief           Function for Init sequence :Jesd
 * @param [in]      jesd_id, serdes_rate_sel, clk_ratio 
 * @return          status
 */      
int init_jesd(uint32_t jesd_id,uint32_t serdes_rate_sel,uint32_t clk_ratio )
{
	int rv = 0;

    printf("serdes_rate %d\n",serdes_rate_sel);
    fpga_clk_and_sysref_period(serdes_rate_sel,clk_ratio);
    printf("INFO : Clock and Sysref Done\n");
    delay(100);
    
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
    delay(100);
    
    printf("INFO : Initialize srp\n");
	init(); // Initialize the srp
	delay(1000);
    
    jesd_reset(1 << jesd_id,0);
    delay(1000);
    
    fpga_provided_sysref(jesd_config.jesd_link_config.serdes_rate, jesd_config.jesd_link_config.smpl_char_clk_ratio);
    printf("INFO : fpga_provided_sysref Done\n");
    delay(100);
	return rv;
}

/**
 * @brief           Function for Init sequence : Vex
 * @param [in]      vex_id
 * @return          status
 */      
int init_vex(uint32_t tx_vex_id)
{

    int rv = 0;

    //clear vex memory
    printf("INFO : Starting to clear vex mem from VEX%d\n",tx_vex_id);
    vex_mem_clear(tx_vex_id, srp);
    printf("INFO : Done clearing vex mem from VEX%d\n",tx_vex_id);
    
   /*  printf("\n########Starting to clear vex mem from 1\n");
    vex_mem_clear(rx_vex_id + 0x1, srp);
    printf("########Done clearing vex mem 1\n\n"); */
    delay(1000);

}
	
/**
 * @brief           Function configuring VEX CIO: STRM2CIO for receiving vex
 * @param [in]      rx_vex_id
 * @return          status
 */
int configure_vex_strm2cio(uint32_t rx_vex_id)
{
    int i = 0, rv;
    int strm2cio_base = VE32_CELL_BASE(rx_vex_id) + VE32_TILE_STRM2CIO_OFFSET;
    
    register_config_tbl_t ve_strm2cio_config_tbl[] =
    {
        // STRM2CIO Interrupt Enable 
        {STRM2CIO_INT_EN_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_int_en, STRM2CIO_INT_EN_WR_MASK, "STRM2CIO_INT_EN"},
        
        // STRM2CIO  FIFO Status Enable 
        {STRM2CIO_FIFO_STAT_CTL_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_fifo_sts_ctrl, STRM2CIO_FIFO_STAT_CTL_WR_MASK, "STRM2CIO_FIFO_STAT_CTL"},
        
        // STRM2CIO Word Counter Enable
        {STRM2CIO_WORD_CNT_CTL_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_wrd_cnt_ctrl, STRM2CIO_WORD_CNT_CTL_WR_MASK, "STRM2CIO_WORD_CNT_CTL"}
    }; 
    
    for(i = 0; i < ARRAY_SIZE(ve_strm2cio_config_tbl); i++)
    {
        if(rv = write_reg_18a(ve_strm2cio_config_tbl[i].addr,
                              ve_strm2cio_config_tbl[i].value,
                              ve_strm2cio_config_tbl[i].mask,
                              ve_strm2cio_config_tbl[i].name))
            return rv;
    }
    
    print("INFO: STRM2CIO configuration completed for VEX%d in Rx path \n", rx_vex_id );
    return rv;
}

/**
 * @brief           Function configuring VEX CIO: CIO2STRM for transmitting vex
 * @param [in]      tx_vex_id, tx_jesd_id
 * @return          status
 */
int configure_vex_cio2strm(uint32_t tx_vex_id, uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int cio2strm_base = VE32_CELL_BASE(tx_vex_id) + VE32_TILE_CIO2STRM_OFFSET;
    int jesd_host_id  = g_jesd_host_ids[tx_jesd_id];
    
    uint32_t cio2strm_range_en                 = 0x0;
    uint32_t str_reg_addr_offset               = 0x4;
    uint32_t num_of_streams                    = jesd_config.jesd_link_config.converters / 2;
    uint32_t str_id                            = 0x0;
    
    uint32_t cio2strm_mem_addr_low_value       = 0x00000000;
    uint32_t cio2strm_mem_addr_low_offset      = 0x20000;
    
    uint32_t cio2strm_mem_addr_high_offset     = 0x1FFFF;
    uint32_t cio2strm_mem_addr_offset_value    = 0x00000000;
    uint32_t cio2strm_mem_addr_dest_value      = jesd_host_id;
    
    switch (num_of_streams)
    {
        case 0x8:
                cio2strm_range_en              = 0xff;
                break;
        
        case 0x4:
                cio2strm_range_en              = 0xf;
                break;
        
        case 0x2:
                cio2strm_range_en              = 0x3;
                break;

        case 0x1:
                cio2strm_range_en              = 0x1;
                break;
            
        default:
                cio2strm_range_en              = 0x1;
                break;
    }
    
    register_config_tbl_t ve_cio2strm_cmn_config_tbl[] = 
    {
        // CIO2STRM Interrupt Enable
        {CIO2STRM_INT_EN_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_int_en,
            CIO2STRM_INT_EN_WR_MASK,
            "CIO2STRM_INT_EN"},
            
        // Fifo_status_enable    
		{CIO2STRM_FIFO_STAT_CTL_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_fifo_sts_ctrl,
            CIO2STRM_FIFO_STAT_CTL_WR_MASK,
            "CIO2STRM_FIFO_STATUS_CTL"},
        
        //Word Counter Enable        
		{CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_wrd_cnt_ctrl,
            CIO2STRM_WORD_CNT_CTL_WR_MASK,
            "CIO2STRM_WORD_CNT_CTL"},
            
        // CIO Memory Address Range Compare Enable    
		{CIO2STRM_RANGE_EN_ADR(cio2strm_base),
            cio2strm_range_en,
            CIO2STRM_RANGE_EN_WR_MASK,
            "CIO2STRM_RANGE_EN"},
        
        // CIO Streaming Credit Counter Max Value
		{CIO2STRM_CREDIT_CNT_ADR(cio2strm_base),
            0xf,
            CIO2STRM_CREDIT_CNT_WR_MASK,
            "CIO2STRM_CREDIT_CNT"}
	};
    
    for(i = 0; i < ARRAY_SIZE(ve_cio2strm_cmn_config_tbl); i++)
    {
        if(rv = write_reg_18a(ve_cio2strm_cmn_config_tbl[i].addr,
                              ve_cio2strm_cmn_config_tbl[i].value,
                              ve_cio2strm_cmn_config_tbl[i].mask,
                              ve_cio2strm_cmn_config_tbl[i].name))
            return rv;
    }
    
    for (str_id = 0x0 ; str_id < num_of_streams ; str_id++)
    {
        register_config_tbl_t ve_cio2strm_strm_config_tbl[] = 
        {
            // Low Range of the CIO Memory Address Compare Register
            {(CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                (cio2strm_mem_addr_low_value + (str_id * cio2strm_mem_addr_low_offset)),
                CIO2STRM_MEM_ADDR_LOW_WR_MASK,
                "CIO2STRM_MEM_ADDR_LOW"},
                
            // High Range of the CIO Memory Address Compare Register    
            {(CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                (cio2strm_mem_addr_low_value + (str_id * cio2strm_mem_addr_low_offset)) + cio2strm_mem_addr_high_offset,
                CIO2STRM_MEM_ADDR_HIGH_WR_MASK,
                "CIO2STRM_MEM_ADDR_HIGH"},
            
            // Memory Address Offset for a byte address            
            {(CIO2STRM_MEM_OFFSET0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                cio2strm_mem_addr_offset_value,
                CIO2STRM_MEM_OFFSET_WR_MASK,
                "CIO2STRM_MEM_OFFSET"},
                
            // Streaming Destination id ,INTF id    
            {(CIO2STRM_STRM_DEST0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                cio2strm_mem_addr_dest_value,
                CIO2STRM_STRM_DEST_WR_MASK,
                "CIO2STRM_STRM_DEST"}
        };
        
        for(i = 0; i < ARRAY_SIZE(ve_cio2strm_strm_config_tbl); i++)
        {
            if(rv = write_reg_18a(ve_cio2strm_strm_config_tbl[i].addr,
                                  ve_cio2strm_strm_config_tbl[i].value,
                                  ve_cio2strm_strm_config_tbl[i].mask,
                                  ve_cio2strm_strm_config_tbl[i].name))
                return rv;
        }
    }
    
    print("INFO: CIO2STRM configuration completed for VEX%d in Tx path \n", tx_vex_id );
    return rv;
}

/**
 * @brief           Function configuring JESD NSIP HBI Commmon: Interrupt en
 * @param [in]      jesd_id
 * @return          status
 */
int configure_jesd_nsip_common(uint32_t jesd_id)
{
    int i = 0, rv;
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_id];
    
    register_config_tbl_t jesd_hbi_cmn_config_tbl[] = 
    {
        // NSIP_HBI interrupt high en
        {NSIP_HBI_INTR_INT_HIGH_EN_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_hbi_config.hbi_int_high_en,
            NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK,
            "NSIP_HBI_INTR_INT_HIGH_EN"},
            
        // NSIP_HBI interrupt low en    
        {NSIP_HBI_INTR_INT_LOW_EN_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_hbi_config.hbi_int_low_en,
            NSIP_HBI_INTR_INT_LOW_EN_WR_MASK,
            "NSIP_HBI_INTR_INT_LOW_EN"}
   };
    
    for(i = 0; i < ARRAY_SIZE(jesd_hbi_cmn_config_tbl); i++)
    {
        if(rv = write_reg_18a(jesd_hbi_cmn_config_tbl[i].addr,
                              jesd_hbi_cmn_config_tbl[i].value,
                              jesd_hbi_cmn_config_tbl[i].mask,
                              jesd_hbi_cmn_config_tbl[i].name))
            return rv;
    }

    print("INFO: NSIP HBI Commmon configuration completed for JESD%d\n", jesd_id);
    return rv;
}

/**
 * @brief           Function configuring NSIP HBI: H2B for JESD in Rx path
 * @param [in]      rx_jesd_id, rx_vex_id
 * @return          status
 */
int configure_jesd_h2b(uint32_t rx_jesd_id, uint32_t rx_vex_id)
{
    int i = 0, rv;
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[rx_jesd_id];
    
    uint32_t str_reg_addr_offset                = 0x4;
    uint32_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint32_t str_id                             = 0x0;
    
    uint32_t h2b_buf_sz_hw_tbl_value            = 0x0;
    uint32_t h2b_tk_route_tbl_value             = rx_vex_id;
    uint32_t h2b_route_tbl_value                = rx_vex_id;
    uint32_t h2b_md_route_tbl_value             = rx_vex_id;
    
    uint32_t h2b_addr_lkup_tbl_value            = 0x80000000;
    uint32_t h2b_tk_addr_lkup_tbl_value         = 0x18000;
    uint32_t h2b_md_ctrl_tbl_value              = 0x1f;
    //uint32_t h2b_md_ctrl_tbl_value            = 0x4000001F;
    //uint32_t h2b_md_ctrl_tbl_value            = 0x40000000;
    
    uint32_t h2b_addr_lkup_tbl_offset           = 0x800;
    uint32_t h2b_tk_addr_lkup_tbl_offset        = 0x4;
      
    switch (num_of_streams)
    {
        case 0x10:         
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
        
        case 0x8:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
        
        case 0x4:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
			break;
				
        case 0x2:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
			
        case 0x1:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
			
        default:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
    }
    
    register_config_tbl_t jesd_h2b_cmn_config_tbl[] = 
    {
        // H2B Registers
        // Set high and low watermarks and soft resets for the 16-entry clock crossing FIFO.
        {NSIP_HBI_H2B_FF_FIFO_CTRL_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_h2b_config.h2b_fifo_ctrl,
            NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK,
            "NSIP_HBI_H2B_FF_FIFO_CTRL"},
        
        // H2B Credit and Ready signal Control and Status
        {NSIP_HBI_H2B_CREDIT_READY_CS_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_h2b_config.h2b_credit_ready,
            NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK,
            "NSIP_HBI_H2B_CREDIT_READY_CS"}
    };
    
    for(i = 0; i < ARRAY_SIZE(jesd_h2b_cmn_config_tbl); i++)
    {
            if(rv = write_reg_18a(jesd_h2b_cmn_config_tbl[i].addr,
                                  jesd_h2b_cmn_config_tbl[i].value,
                                  jesd_h2b_cmn_config_tbl[i].mask,
                                  jesd_h2b_cmn_config_tbl[i].name))
                return rv;
    }
    
    for (str_id = 0x0 ; str_id < num_of_streams ; str_id++)
    {
        register_config_tbl_t jesd_h2b_strm_config_tbl[] = 
        {
            // H2B Stream Config - Vector/Sample Data Buffer Size LUT
            {(NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)), 
                h2b_buf_sz_hw_tbl_value, 
                NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, 
                "H2B_BUF_SZ_HW_TBL"},

            // Vector/Sample Data Routing LUT.
            {(NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_route_tbl_value,
                NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_ROUTE_LKUP_TBL"},
            
             // Token Address LUT. 
            {(NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (h2b_tk_addr_lkup_tbl_value + (str_id * h2b_tk_addr_lkup_tbl_offset)),
                NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK,
                "H2B_TK_ADDR_LKUP_TBL"},
            
            // Token Routing LUT.
            {(NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_tk_route_tbl_value,
                NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_TK_ROUTE_LKUP_TBL"},
                
            // Metadata Base Address LUT
            /*{(NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)), 
                    0x10000,
                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK,
                    "H2B_MD_ADDR_LKUP_TBL"}, */
            
            // Metadata Routing LUT
            {(NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_md_route_tbl_value,
                NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_MD_ROUTE_LKUP_TBL"},
                
            // Metadata Control tbl
            {(NSIP_HBI_H2B_MD_CTRL_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_md_ctrl_tbl_value,
                NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK,
                "H2B_MD_CONTROL_TBL"},
            
            // Valid Address and Routing Entry in Data/Token/Metadata Lookup Registers.Vector/Sample Base address
            // This register should be written LAST since it validates all of the other registers.
            {(NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * 0x4)),
                (h2b_addr_lkup_tbl_value + str_id * h2b_addr_lkup_tbl_offset ),
                NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK,
                "H2B_ADDR_LKUP_TBL"}
          
        };
        
        for(i = 0; i < ARRAY_SIZE(jesd_h2b_strm_config_tbl); i++)
        {
            if(rv = write_reg_18a(jesd_h2b_strm_config_tbl[i].addr,
                                  jesd_h2b_strm_config_tbl[i].value,
                                  jesd_h2b_strm_config_tbl[i].mask,
                                  jesd_h2b_strm_config_tbl[i].name))
                return rv;
        }
    }
    
    print("INFO: NSIP H2B configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring NSIP HBI: B2H for JESD in Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */
int configure_jesd_b2h(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[tx_jesd_id];
    
    uint32_t str_reg_addr_offset                = 0x4;
    uint32_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint32_t str_id                             = 0x0;
    
    uint32_t b2h_addr_map_tbl_value             = 0x80000000;
    uint32_t b2h_addr_mask_tbl_value            = 0x1FFFF;

    uint32_t b2h_addr_map_tbl_offset            = 0x20000;
    
    switch (num_of_streams)
    {
        case 0x10:         
                b2h_addr_map_tbl_offset         = 0x20000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
        
        case 0x8:
                b2h_addr_map_tbl_offset         = 0x20000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
        
        case 0x4:
                b2h_addr_map_tbl_offset         = 0x20000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;

        case 0x2:
                b2h_addr_map_tbl_offset         = 0x20000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
        
        case 0x1:
                b2h_addr_map_tbl_offset         = 0x00000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
            
        default:
                b2h_addr_map_tbl_offset         = 0x00000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
    }
    
    register_config_tbl_t jesd_b2h_cmn_config_tbl[] = 
    {
        // B2H Registers
        // Set high (almost full) and low (almost empty) watermarks 
        {NSIP_HBI_B2H_FF_FIFO_CTRL_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_b2h_config.b2h_fifo_ctrl,
            NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK,
            "B2H_FIFO_CONTROL"},
            
        // Set maximum credit value
		{NSIP_HBI_B2H_CSR_CREDIT_CS_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_b2h_config.b2h_credit_ready,
            NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK,
            "B2H_CREDIT_CS"}
    };
    
    for(i = 0; i < ARRAY_SIZE(jesd_b2h_cmn_config_tbl); i++)
    {
            if(rv = write_reg_18a(jesd_b2h_cmn_config_tbl[i].addr,
                                  jesd_b2h_cmn_config_tbl[i].value,
                                  jesd_b2h_cmn_config_tbl[i].mask,
                                  jesd_b2h_cmn_config_tbl[i].name))
                return rv;
    }
    
    //B2H Stream config - Configure up to 32 address mappings and corresponding address masks
    for (str_id = 0x0 ; str_id < num_of_streams ; str_id++)
    {
        register_config_tbl_t jesd_b2h_strm_config_tbl[] = 
        {
            // ADDR MAP TBL: Specify the 28-bit byte address (or range using the B2H_ADDR_MASK_TBL reg) to be compared with the received address. Bit 31, VALID=1
            {(NSIP_HBI_B2H_CSR_ADDR_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (b2h_addr_map_tbl_value + (str_id * b2h_addr_map_tbl_offset)),
                NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK,
                "B2H_ADDR_MAP_TBL"},
                
            // ADDR MASK TBL: 28-bit Mask bits (‘1’=address bit is masked out) for the address range specified in the B2H_ADDR_MAP_TBL reg       
            {(NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                b2h_addr_mask_tbl_value,
                NSIP_HBI_B2H_CSR_ADDR_MASK_TBL_WR,
                "B2H_ADDR_MASK_TBL"}
        };
        
        for(i = 0; i < ARRAY_SIZE(jesd_b2h_strm_config_tbl); i++)
        {
            if(rv = write_reg_18a(jesd_b2h_strm_config_tbl[i].addr,
                                  jesd_b2h_strm_config_tbl[i].value,
                                  jesd_b2h_strm_config_tbl[i].mask,
                                  jesd_b2h_strm_config_tbl[i].name))
                return rv;
        }
    }
    
    print("INFO: NSIP B2H configuration completed for JESD%d in Tx path\n", tx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CMN CSR: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_rx_cmn_csr(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_cmn_csr_base = g_jesd_cmn_csr_base_addr[rx_jesd_id];
    
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_IP_CLK_CTRL_OFFSET, 
                            jesd_config.jesd_rx_cmn_csr_config.rx_ip_clk_ctrl, 
                            JESD_CMN_CSR_RX_IP_CLK_CTRL_WR_MASK,
                            "JESD_CMN_CSR_RX_IP_CLK_CTRL"))
        return rv;               
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_sysref_tsad,
                            JESD_CMN_CSR_RX_SYSREF_TSAD_WR_MASK,
                            "JESD_CMN_CSR_RX_SYSREF_TSAD"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_ctrl,
                            JESD_CMN_CSR_RX_SYNC_POINT_CTRL_WR_MASK,
                            "JESD_CMN_CSR_RX_SYNC_POINT_CTRL"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad,
                            JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_WR_MASK,
                            "JESD_CMN_CSR_RX_BFN_SYSREF_TSAD"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl,
                            JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_WR_MASK,
                            "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL"))
        return rv;
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_clk_1p5g_div_en,
                            JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_WR_MASK,
                            "JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN"))
        return rv;
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_CLK_GEN_EN_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_clk_gen,
                            JESD_CMN_CSR_RX_CLK_GEN_EN_WR_MASK,
                            "JESD_CMN_CSR_RX_CLK_GEN_EN"))
        return rv;  
    
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_cnt_en,
                            JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_WR_MASK,
                            "JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN"))
        return rv; 

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en,
                            JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_WR_MASK,
                            "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN"))
        return rv;
    
    print("INFO: JESD CMN CSR configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CMN CSR: JESD in Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */
int configure_jesd_tx_cmn_csr(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_cmn_csr_base = g_jesd_cmn_csr_base_addr[tx_jesd_id];
    
    uint32_t num_of_streams   = jesd_config.jesd_link_config.converters / 2;
    uint32_t str_id           = 0x0;
    
    // TX IP sample, character and RS FEC clocks source control register
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_IP_CLK_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_ip_clk_ctrl,
                            JESD_CMN_CSR_TX_IP_CLK_CTRL_WR_MASK,
                            "JESD_CMN_CSR_TX_IP_CLK_CTRL"))
        return rv;               
    
    // Sysref Delay counter  
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_sysref_tsad,
                            JESD_CMN_CSR_TX_SYSREF_TSAD_WR_MASK,
                            "JESD_CMN_CSR_TX_SYSREF_TSAD"))
        return rv;               
    
    // SYNC pulse generation counter logic
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_ctrl,
                            JESD_CMN_CSR_TX_SYNC_POINT_CTRL_WR_MASK,
                            "JESD_CMN_CSR_TX_SYNC_POINT_CTRL"))
        return rv;               
    
    // BFN Sysref Delay counter
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad,
                            JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_WR_MASK,
                            "JESD_CMN_CSR_TX_BFN_SYSREF_TSAD"))
        return rv;               
    // SYSREF input select Signal for BFN clock syncpoint Logic
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_BFN_SYSREF_SEL_OFFSET,
                            0x00000000,
                            JESD_CMN_CSR_TX_BFN_SYSREF_SEL_WR_MASK,
                            "JESD_CMN_CSR_TX_BFN_SYSREF_SEL"))
        return rv;  
        
    // BFN SYNC pulse generation counter logic
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl,
                            JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_WR_MASK,
                            "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL"))
        return rv;               
    
    // Enables the clock 1p5G division. Used to synchronize the divided clock edges with sysref
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_OFFSET,
                                jesd_config.jesd_tx_cmn_csr_config.tx_clk_1p5g_div_en,
                                JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_WR_MASK,
                                "JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN"))
        return rv;     
    
    // Enables the clock division required for JESD IP sample and character clock. Used to synchronize the divided clock edges with sysref
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_CLK_GEN_EN_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_clk_gen,
                            JESD_CMN_CSR_TX_CLK_GEN_EN_WR_MASK,
                            "JESD_CMN_CSR_TX_CLK_GEN_EN"))
        return rv;               
    
    // Enables the sync point counter and sync pulse generation. Used to synchronize the sync point counter with sysref    
	if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_cnt_en,
                            JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_WR_MASK,
                            "JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN"))
        return rv;
    
    // BFN : Enables the sync point counter and sync pulse generation. Used to synchronize the sync point counter with sysref  
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en,
                            JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_WR_MASK,
                            "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN"))
        return rv;               
        
    print("INFO: JESD CMN CSR configuration completed for JESD%d in Tx path\n", tx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CRUX CLK CSR: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_rx_crux_clk_csr(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_crux_clk_csr_base = g_jesd_crux_clk_csr_base_addr[rx_jesd_id];
    
    uint32_t rx_wr_mem_tbl          = 0x00000000;
    uint32_t rx_rd_mem_tbl          = 0x00000000;
    uint32_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;;
    uint32_t str_reg_addr_offset    = 0x4;
    uint32_t str_id                 = 0x0;
    uint32_t rx_wr_mem_tbl_offset   = 0x0;
    uint32_t rx_rd_mem_tbl_offset   = 0x0;
    uint32_t rx_mem_strm_cfg        = 0x0;
    uint32_t rx_strm_cfg            = 0x0;
    
    switch (num_of_streams)
    {
        case 0x10:
            rx_wr_mem_tbl_offset    = 0x20;
            rx_rd_mem_tbl_offset    = 0x220;
            rx_mem_strm_cfg         = 0x1f;
            rx_strm_cfg             = 0xf0;
            break;
        
        case 0x8:
            rx_wr_mem_tbl_offset    = 0x40;
            rx_rd_mem_tbl_offset    = 0x240;
            rx_mem_strm_cfg         = 0x3f;
            rx_strm_cfg             = 0xe8;
            break;
        
        case 0x4:
            rx_wr_mem_tbl_offset    = 0x80;
            rx_rd_mem_tbl_offset    = 0x280;
            rx_mem_strm_cfg         = 0x7f;
            rx_strm_cfg             = 0xe4;
            break;
        
        case 0x2:
            rx_wr_mem_tbl_offset    = 0x100;
            rx_rd_mem_tbl_offset    = 0x300;
            rx_mem_strm_cfg         = 0xff;
            rx_strm_cfg             = 0xe2;
            break;
       
       case 0x1:
            rx_wr_mem_tbl_offset    = 0x0;
            rx_rd_mem_tbl_offset    = 0x0;
            rx_mem_strm_cfg         = 0x1ff;
            rx_strm_cfg             = 0xe1;
            break;
        default:
            rx_wr_mem_tbl_offset    = 0x0;
            rx_rd_mem_tbl_offset    = 0x0;
            rx_mem_strm_cfg         = 0x0;
            rx_strm_cfg             = 0x0;
            break;
    }
    
    // For each JESD I/Q stream (up to 16), provide the write and read memory base addresses for each stream
    for (str_id = 0x0; str_id < num_of_streams; str_id++)
    {
        // Specify NSIP write base address for each JESD stream
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)),
                                 (rx_wr_mem_tbl + (str_id * rx_wr_mem_tbl_offset)),
                                 JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL"))
            return rv;                               
    
        // Specify NSIP read base address and Stream ID
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)), 
                                 (rx_rd_mem_tbl + (str_id * rx_rd_mem_tbl_offset)),
                                 JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL"))
            return rv;  
    }
    
    // Configure remaining parameters that are common to all streams
    // FLITS_PER_STRM: Typically 7 (for 8 flits) before beginning read of RSB , NUM_STRM: : Refer UC table
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_STRM_CFG_OFFSET,
                            rx_strm_cfg,
                            JESD_CRUX_CLK_CSR_RX_STRM_CFG_WR_MASK,
                            "JESD_CRUX_CLK_CSR_RX_STRM_CFG"))
        return rv;                   
    
    // Specify max flits/depth allocated to memory minus 1. 
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET,
                            rx_mem_strm_cfg,
                            JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_WR_MASK,
                            "JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG"))
        return rv; 
    
    print("INFO: JESD CRUX CLK CSR configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CRUX CLK CSR: JESD in Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */
int configure_jesd_tx_crux_clk_csr(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_crux_clk_csr_base = g_jesd_crux_clk_csr_base_addr[tx_jesd_id];
    
    uint32_t tx_strm_mem_addr          = 0x00000000;
    uint32_t tx_strm_mem_addr_offset   = 0x00000000;
    uint32_t tx_strm_mem_size          = 0x00000000;
    uint32_t tx_tsb_trig_en            = 0x00000000;
    uint32_t tx_strm_tsb_rd_trig       = 0x00000000;
    
    uint32_t num_of_streams            = jesd_config.jesd_link_config.converters / 2;;
    uint32_t str_reg_addr_offset       = 0x4;
    uint32_t str_id                    = 0x0;
    uint32_t tx_num_valid_str          = 0x0;
    uint32_t tx_tsb_cfg                = 0x0;

    // Note: The size should be set the same for all streams, and should only be 4k, 8k, 16k, 32k or 64k to align with the reading as defined in reg STRM_MEM_INST_CNT
    switch (num_of_streams)
    {
        case 0x10:
            tx_strm_mem_addr_offset    = 0x00001000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0xffffffff;          
            tx_tsb_cfg                 = 0x0;    
            break;
        
        case 0x8:
            tx_strm_mem_addr_offset    = 0x00001000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0x00ff00ff;          
            tx_tsb_cfg                 = 0x0;               
            break;
        
        case 0x4:
            tx_strm_mem_addr_offset    = 0x00001000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0x000f000f;          
            tx_tsb_cfg                 = 0x0;   
            break;
        
        case 0x2:
            tx_strm_mem_addr_offset    = 0x00001000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0x00030003;          
            tx_tsb_cfg                 = 0x0;   
            break;
        
        case 0x1:
            tx_strm_mem_addr_offset    = 0x00000000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0x00010001;          
            tx_tsb_cfg                 = 0x0; 
            
        default:
            tx_strm_mem_addr_offset    = 0x00000000;
            tx_strm_mem_size           = 0x00000fff;
            tx_tsb_trig_en             = 0x000307ff;
            tx_strm_tsb_rd_trig        = 0x000007ff;        
            tx_num_valid_str           = 0x00010001;          
            tx_tsb_cfg                 = 0x0;  
            break;
    }
    
    // JESD TX number of valid buffers and valid streams
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_OFFSET,
                            tx_num_valid_str,
                            JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_WR_MASK,
                            "JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR"))
        return rv;               

    // For each stream (up to 16), provide the stream memory base and size & number of chains/converters : Refer UC table
    for (str_id = 0x0; str_id < num_of_streams; str_id++)
    {
        // Configure the mapping table from NSIP ID # to the TSB ID# (memory address and size)
        // Specify stream memory base address for each stream.Mapping table from NSIP ID # to JESD controller port
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_OFFSET + (str_id * str_reg_addr_offset)),
                                 (tx_strm_mem_addr + (str_id * tx_strm_mem_addr_offset)),
                                 JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR"))
            return rv;                               
    
        // Specify stream memory size for each stream
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_OFFSET + (str_id * str_reg_addr_offset)), 
                                 tx_strm_mem_size,
                                 JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE"))
            return rv; 
        
        // Indicates TSB fill level when read trigger is triggered
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL0_OFFSET + (str_id * str_reg_addr_offset)), 
                                 tx_strm_tsb_rd_trig,
                                 JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL"))
            return rv;     
    }
    
    // Specify tsb_rd_trig_en, tsb_rd_trig_on_half_fill, tsb_rd_trig_fill_lvl
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_OFFSET,
                            tx_tsb_trig_en,
                            JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_WR_MASK,
                            "JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN"))
        return rv;
        
    // TX TSB Buffers config : indicates the mode of write operation when tsb buffer is full
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_TSB_CFG_OFFSET,
                            tx_tsb_cfg,
                            JESD_CRUX_CLK_CSR_TX_TSB_CFG_WR_MASK,
                            "JESD_CRUX_CLK_CSR_TX_TSB_CFG"))
        return rv;   
    
    print("INFO: JESD CRUX CLK CSR configuration completed for JESD%d in Tx path\n", tx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring GLUE: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_rx_glue(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_rx_glue_base = g_jesd_rx_glue_base_addr[rx_jesd_id];
    
    if(rv = write_reg_18a(jesd_rx_glue_base + JESD_RX_GLUE_SONI_OFFSET,
                            jesd_config.jesd_link_config.sonif,
                            JESD_RX_GLUE_SONI_WR_MASK,
                            "RX_GLUE_MEM_RX_GLUE_SONI"))
        return rv;
    
    // dp_gate_sel, as per simval log
    if(rv = write_reg_18a(jesd_rx_glue_base + JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_gate_sel,
                            JESD_RX_GLUE_DATAPATH_GATE_SEL_WR_MASK,
                            "RX_DATAPATH_GATE_SEL"))
        return rv;
    // dp_init_cyc_cnt enable, as per simval log   
    if(rv = write_reg_18a(jesd_rx_glue_base + JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt,
                            JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_WR_MASK,
                            "RX_DATAPATH_INIT_CYC_CNT"))
        return rv;                    

    print("INFO: JESD GLUE configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring GLUE: JESD in Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */
int configure_jesd_tx_glue(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_tx_glue_base = g_jesd_tx_glue_base_addr[tx_jesd_id];
    
    uint32_t tx_strm_mem_inst_cnt      = 0x00000000;
    uint32_t num_of_streams            = jesd_config.jesd_link_config.converters / 2;;
    uint32_t str_reg_addr_offset       = 0x4;
    uint32_t str_id                    = 0x0;
    
    // Note: This should align with the assignments for the NSIP assignments in reg STRM_ID_MEM_ADDR/SIZE
    switch (num_of_streams)
    {
        case 0x10:
            tx_strm_mem_inst_cnt       = 0x01;
            break;
        
        case 0x8:
            tx_strm_mem_inst_cnt       = 0x01; 
            break;
        
        case 0x4:
            tx_strm_mem_inst_cnt       = 0x01;
            break;
        
        case 0x2:
            tx_strm_mem_inst_cnt       = 0x01;
            break;
            
        default:
            tx_strm_mem_inst_cnt       = 0x01;
            break;
    }
    
    // Specify number of 4kB memory blocks assigned for each stream (same for all streams)
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_STRM_INST_CNT_OFFSET,
                            tx_strm_mem_inst_cnt,
                            JESD_TX_GLUE_STRM_INST_CNT_WR_MASK,
                            "JESD_TX_GLUE_STRM_INST_CNT"))
        return rv;
        
    // Specify sample width, SonI and shift size : Refer UC table
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_CONV_DP_CFG_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_conv_dp_cfg,
                            JESD_TX_GLUE_CONV_DP_CFG_WR_MASK,
                            "JESD_TX_GLUE_CONV_DP_CFG"))
        return rv;
    
    // TX Datapath Gating logic   
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_DATAPATH_GATE_SEL_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_dp_gate_sel,
                            JESD_TX_GLUE_DATAPATH_GATE_SEL_WR_MASK,
                            "JESD_TX_GLUE_DATAPATH_GATE_SEL"))
        return rv;
    
    // TX Stream PHM enable   
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_STRM_PHM_EN_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_strm_phm_en,
                            JESD_TX_GLUE_STRM_PHM_EN_WR_MASK,
                            "JESD_TX_GLUE_STRM_PHM_EN"))
        return rv;
    
    // TX Stream FOVR enable   
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_STRM_FOVR_EN_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_strm_phm_en,
                            JESD_TX_GLUE_FOVR_CFG_WR_MASK,
                            "JESD_TX_GLUE_STRM_FOVR_EN"))
        return rv;
        
    // TX Sample request gen config : TX Stream read Flit Count
    // holds the request pattern from IP -> first 32 clock cycle pattern 
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_SRG_PAT_CFG_LOW_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_srg_pat_cfg_low,
                            JESD_TX_GLUE_SRG_PAT_CFG_LOW_WR_MASK,
                            "JESD_TX_GLUE_SRG_PAT_CFG_LOW"))
        return rv;

    // TX Sample request gen period config : TX Stream read Flit Count
    // holds the number of bits selected from tx_srg_pat_cfg_low/high combined to generate request
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_SRG_PAT_PERIOD_CFG_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_srg_pat_period_cfg,
                            JESD_TX_GLUE_SRG_PAT_PERIOD_CFG_WR_MASK,
                            "JESD_TX_GLUE_SRG_PAT_PERIOD_CFG"))
        return rv;

    // TX Sample request gen delay config : TX Stream read Flit Count
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_SRG_PAT_DEL_CFG_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_srg_pat_del_cfg,
                            JESD_TX_GLUE_SRG_PAT_DEL_CFG_WR_MASK,
                            "JESD_TX_GLUE_SRG_PAT_DEL_CFG"))
        return rv;
    
    // TX Sample request gen enable : TX Stream read Flit Count
    // enables the request pattern generation, enable once all cfg for srg_pat is programmed
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_SRG_PAT_EN_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_srg_pat_en,
                            JESD_TX_GLUE_SRG_PAT_EN_WR_MASK,
                            "JESD_TX_GLUE_SRG_PAT_EN"))
        return rv;
    
    // TX TSB min max occupancy capture en
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_TSB_MIN_MAX_OCCUPANCY_CAPT_EN_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_tsb_min_max_occupancy_capt_en,
                            JESD_TX_GLUE_TSB_MIN_MAX_OCCUPANCY_CAPT_EN_WR_MASK,
                            "JESD_TX_GLUE_TSB_MIN_MAX_OCCUPANCY_CAPT_EN"))
        return rv;

    // TX glue conv smpl intlv
    /*
    if(rv = write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_CONV_SMPL_INTRLV_CTRL_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_smpl_intrlv_ctrl,
                            JESD_TX_GLUE_CONV_SMPL_INTRLV_CTRL_WR_MASK,
                            "JESD_TX_GLUE_CONV_SMPL_INTRLV_CTRL"))
        return rv;
    */
    print("INFO: JESD GLUE configuration completed for JESD%d in Tx path\n", tx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring JESD IP Resgisters for Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */     
// JESD RX reg
int configure_jesd_rx_ip(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    
    int jesd_rx_ip_base = g_jesd_rx_ip_base_addr[rx_jesd_id];
    int sample_x8_ratio = 0x0;
    int soni            = 0x0;
    
    sample_x8_ratio = (jesd_config.jesd_link_config.smpl_per_frame*8) / (jesd_config.jesd_link_config.sonif);
    soni 			= (jesd_config.jesd_link_config.sonif) - 0x1;
    soni 			= (sample_x8_ratio<<5) | soni;
    
    // Pre-configure JESD receiver per the particular use chain
    // Set to subclass 1
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SUBCLASS_OFFSET, 
                            jesd_config.jesd_link_config.subclass, 
                            JESD_XIP_204C_RX_SUBCLASS_WR_MASK,
                            "JESD_XIP_204C_RX_SUBCLASS"))
        return rv;
        
    // Number of Control Frames (CF). No Control bits, so keep default register value.
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CF_OFFSET,
                            jesd_config.jesd_link_config.ctrl_frames_cf,
                            JESD_XIP_204C_RX_CF_WR_MASK,
                            "JESD_XIP_204C_RX_CF"))
        return rv;
    
    // Number of control bits per sample (CS). No Control bits are used for JESD Rx (CS = 0).    
     if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CS_OFFSET,
                            jesd_config.jesd_link_config.ctrl_bits_cs,
                            JESD_XIP_204C_RX_CS_WR_MASK,
                            "JESD_XIP_204C_RX_CS"))
        return rv;
        
    // Number of octets per Frame (F) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_RX_F_WR_MASK,
                            "JESD_XIP_204C_RX_F"))
        return rv;
        
    // Number of Lanes (L) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_RX_L_WR_MASK,
                            "JESD_XIP_204C_RX_L"))
        return rv;
        
    // Sample resolution (N) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_RX_N_WR_MASK,
                            "JESD_XIP_204C_RX_N"))
        return rv;
        
    // Number of converters (M) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_RX_M_WR_MASK,
                            "JESD_XIP_204C_RX_M"))
        return rv;
    
    // Total number of bits per sample (N’) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_RX_NTOTAL_WR_MASK,
                            "JESD_XIP_204C_RX_NTOTAL"))
        return rv;
   
    // Number of samples (S) – 1 per converter : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_S_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_per_frame) - 1),
                            JESD_XIP_204C_RX_S_WR_MASK,
                            "JESD_XIP_204C_RX_S"))
        return rv;
    
    // Enable High Density (HD) format : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_HD_OFFSET,
                            jesd_config.jesd_link_config.high_density,
                            JESD_XIP_204C_RX_HD_WR_MASK,
                            "JESD_XIP_204C_RX_HD"))
        return rv;
    
    // Enable scrambling
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SCR_OFFSET,
                            jesd_config.jesd_link_config.scr,
                            JESD_XIP_204C_RX_SCR_WR_MASK,
                            "JESD_XIP_204C_RX_SCR"))
        return rv;
        
    // Sample-to-Character Clock ratio : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CLK_RATIO_OFFSET,
                            jesd_config.jesd_link_config.smpl_char_clk_ratio,
                            JESD_XIP_204C_RX_CLK_RATIO_WR_MASK,
                            "JESD_XIP_204C_RX_CLK_RATIO"))
        return rv;
   
    // 204C -FEC en, 204D - FEC mode, FEC bypass
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_FEC_OFFSET,
                            jesd_config.jesd_link_config.fec.fec_enable,
                            JESD_XIP_204C_RX_FEC_WR_MASK,
                            "JESD_XIP_204C_RX_FEC"))
        return rv; 
        
    // Bit order Serdes and En  
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_BIT_ORDER_OFFSET, 
                            jesd_config.jesd_link_config.bit_order.bitorder,
                            JESD_XIP_204C_RX_BIT_ORDER_WR_MASK,
                            "JESD_XIP_204C_RX_BIT_ORDER"))
        return rv;
    
    // Transport Layer test mode En
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_TL_TEST_MODE_OFFSET,
                            jesd_config.jesd_link_config.tl_testmode,
                            JESD_XIP_204C_RX_TL_TEST_MODE_WR_MASK,
                            "JESD_XIP_204C_RX_TL_TEST_MODE"))
        return rv;
    
    // Samples on Interface (SONI). Set to SONI – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SONIF_OFFSET,
                            soni,
                            JESD_XIP_204C_RX_SONIF_WR_MASK,
                            "JESD_XIP_204C_RX_SONIF"))
        return rv;
    
    // JESD 204C-Only Registers
    // CRC-3 error checking
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CRC3_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable,
                            JESD_XIP_204C_RX_CRC3_EN_WR_MASK,
                            "JESD_XIP_204C_RX_CRC3_EN"))
        return rv;
     
    // Enable CRC-12 per use case
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CRC12_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable, 
                            JESD_XIP_204C_RX_CRC12_EN_WR_MASK,
                            "JESD_XIP_204C_RX_CRC12_EN"))
        return rv;
        
    //Number of Multiblocks per Extended Multiblocks (E) – 1 
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_E_OFFSET,
                            ((jesd_config.jesd_link_config.min_e) - 1),
                            JESD_XIP_204C_RX_E_WR_MASK,
                            "JESD_XIP_204C_RX_E"))
        return rv;
    
    // Extended Multi Block state machine error threshold. Use default value (8)
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_THRESH_EMB_ERR_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh,
                            JESD_XIP_204C_RX_THRESH_EMB_ERR_WR_MASK,
                            "JESD_XIP_204C_RX_THRESH_EMB_ERR"))
        return rv;
        
    // Sync header state machine error threshold. Use default value (16)
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_THRESH_SH_ERR_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh,
                            JESD_XIP_204C_RX_THRESH_SH_ERR_WR_MASK,
                            "JESD_XIP_204C_RX_THRESH_SH_ERR"))
        return rv;
        
    // Command Channel not used
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CMD_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable,
                            JESD_XIP_204C_RX_CMD_EN_WR_MASK,
                            "JESD_XIP_204C_RX_CMD_EN"))
        return rv;
    
    print("INFO: JESD IP configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring JESD IP Resgisters for Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */     
// JESD TX reg
int configure_jesd_tx_ip(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_tx_ip_base = g_jesd_tx_ip_base_addr[tx_jesd_id];
    int sample_x8_ratio =0x0;
    int soni = 0x0;
    
    sample_x8_ratio = (jesd_config.jesd_link_config.smpl_per_frame*8) / (jesd_config.jesd_link_config.sonif);
    soni            = (jesd_config.jesd_link_config.sonif) - 0x1;
    soni            = (sample_x8_ratio<<5) | soni;
    
    // Pre-configure JESD receiver per the particular use chain
    // Set to subclass 1
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_SUBCLASS_OFFSET, 
                            jesd_config.jesd_link_config.subclass, 
                            JESD_XIP_204C_TX_SUBCLASS_WR_MASK,
                            "JESD_XIP_204C_TX_SUBCLASS"))
        return rv;
        
    // Number of Control Frames (CF). No Control bits, so keep default register value.
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CF_OFFSET,
                            jesd_config.jesd_link_config.ctrl_frames_cf,
                            JESD_XIP_204C_TX_CF_WR_MASK,
                            "JESD_XIP_204C_TX_CF"))
        return rv;
    
    // Number of control bits per sample (CS). No Control bits are used for JESD Rx (CS = 0).    
     if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CS_OFFSET,
                            jesd_config.jesd_link_config.ctrl_bits_cs,
                            JESD_XIP_204C_TX_CS_WR_MASK,
                            "JESD_XIP_204C_TX_CS"))
        return rv;
        
    // Number of octets per Frame (F) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_TX_F_WR_MASK,
                            "JESD_XIP_204C_TX_F"))
        return rv;
        
    // Number of Lanes (L) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_TX_L_WR_MASK,
                            "JESD_XIP_204C_TX_L"))
        return rv;
        
    // Sample resolution (N) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_TX_N_WR_MASK,
                            "JESD_XIP_204C_TX_N"))
        return rv;
        
    // Number of converters (M) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_TX_M_WR_MASK,
                            "JESD_XIP_204C_TX_M"))
        return rv;
    
    // Total number of bits per sample (N’) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_TX_NTOTAL_WR_MASK,
                            "JESD_XIP_204C_TX_NTOTAL"))
        return rv;
   
    // Number of samples (S) – 1 per converter : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_S_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_per_frame) - 1),
                            JESD_XIP_204C_TX_S_WR_MASK,
                            "JESD_XIP_204C_TX_S"))
        return rv;
    
    // Enable High Density (HD) format : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_HD_OFFSET,
                            jesd_config.jesd_link_config.high_density,
                            JESD_XIP_204C_TX_HD_WR_MASK,
                            "JESD_XIP_204C_TX_HD"))
        return rv;
    
    // Enable scrambling
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_SCR_OFFSET,
                            jesd_config.jesd_link_config.scr,
                            JESD_XIP_204C_TX_SCR_WR_MASK,
                            "JESD_XIP_204C_TX_SCR"))
        return rv;
        
    // Sample-to-Character Clock ratio : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CLK_RATIO_OFFSET,
                            jesd_config.jesd_link_config.smpl_char_clk_ratio,
                            JESD_XIP_204C_TX_CLK_RATIO_WR_MASK,
                            "JESD_XIP_204C_TX_CLK_RATIO"))
        return rv;
   
    // 204C -FEC en, 204D - FEC mode, FEC bypass
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_FEC_OFFSET,
                            jesd_config.jesd_link_config.fec.fec_enable,
                            JESD_XIP_204C_TX_FEC_WR_MASK,
                            "JESD_XIP_204C_TX_FEC"))
        return rv; 
        
    // Bit order Serdes and En  
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_BIT_ORDER_OFFSET, 
                            jesd_config.jesd_link_config.bit_order.bitorder,
                            JESD_XIP_204C_TX_BIT_ORDER_WR_MASK,
                            "JESD_XIP_204C_TX_BIT_ORDER"))
        return rv;
    
    // Transport Layer test mode En
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_TL_TEST_MODE_OFFSET,
                            jesd_config.jesd_link_config.tl_testmode,
                            JESD_XIP_204C_TX_TL_TEST_MODE_WR_MASK,
                            "JESD_XIP_204C_TX_TL_TEST_MODE"))
        return rv;
    
    // Samples on Interface (SONI). Set to SONI – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_SONIF_OFFSET,
                            soni,
                            JESD_XIP_204C_TX_SONIF_WR_MASK,
                            "JESD_XIP_204C_TX_SONIF"))
        return rv;
    
    // JESD 204C-Only Registers
    // CRC-3 error checking
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CRC3_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable,
                            JESD_XIP_204C_TX_CRC3_EN_WR_MASK,
                            "JESD_XIP_204C_TX_CRC3_EN"))
        return rv;
     
    // Enable CRC-12 per use case
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CRC12_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable, 
                            JESD_XIP_204C_TX_CRC12_EN_WR_MASK,
                            "JESD_XIP_204C_TX_CRC12_EN"))
        return rv;
        
    //Number of Multiblocks per Extended Multiblocks (E) – 1 
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_E_OFFSET,
                            ((jesd_config.jesd_link_config.min_e) - 1),
                            JESD_XIP_204C_TX_E_WR_MASK,
                            "JESD_XIP_204C_TX_E"))
        return rv;
    
    // Extended Multi Block state machine error threshold. Use default value (8)
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_TL_LATENCY_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency,
                            JESD_XIP_204C_TX_TL_LATENCY_WR_MASK,
                            "JESD_XIP_204C_TX_TL_LATENCY"))
        return rv;
        
    // Sync header state machine error threshold. Use default value (16)
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_SAMPLE_REQ_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req,
                            JESD_XIP_204C_TX_SAMPLE_REQ_WR_MASK,
                            "JESD_XIP_204C_TX_SAMPLE_REQ"))
        return rv;
        
    // Command Channel not used
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_CMD_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable,
                            JESD_XIP_204C_TX_CMD_EN_WR_MASK,
                            "JESD_XIP_204C_TX_CMD_EN"))
        return rv;
    
    print("INFO: JESD IP configuration completed for JESD%d in Tx path\n", tx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring loopback ctrl: JESD 
 * @param [in]      jesd_id,flow_id
 * @return          status
 */
int configure_jesd_lpbk(uint32_t jesd_id,uint32_t flow_id)
{
    int i = 0, rv;
    int jesd_crux_clk_csr_base   = g_jesd_crux_clk_csr_base_addr[jesd_id];
    
    //Configure the JESD SS Loopback Control reg
    switch(flow_id)
    {
        case flow_lpbk_glue:
                if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET,
                                        0x2,
                                        JESD_CRUX_CLK_CSR_LPBK_CTL_WR_MASK,
                                        "JESD_CRUX_CLK_CSR_LPBK_CTL"))
                    return rv;                    
                printf("INFO: Glue lpbk is enabled\n");
            
            break;
        
        case flow_lpbk_nsip:
        
                // Loopback connection between NSIP output to TX Glue and NSIP input from RX glue 
                if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET,
                                        0x1,
                                        JESD_CRUX_CLK_CSR_LPBK_CTL_WR_MASK,
                                        "JESD_CRUX_CLK_CSR_LPBK_CTL"))
                    return rv;                    
                printf("INFO: NSIP lpbk is enabled\n");
            
            break;
    }
    
    print("INFO: JESD lpbk ctrl configuration completed for JESD%d\n", jesd_id);
    return rv;
}

/**
 * @brief           Function configuring IP enable: JESD TX and RX IP enable
 * @param [in]      jesd_id
 * @return          status
 */
int configure_jesd_ip_enable(uint32_t jesd_id)
{
    int i = 0, rv;
    int jesd_rx_ip_base     = g_jesd_rx_ip_base_addr[jesd_id];
    int jesd_tx_ip_base     = g_jesd_tx_ip_base_addr[jesd_id];
    int jesd_cmn_csr_base   = g_jesd_cmn_csr_base_addr[jesd_id];
    
    // Enable the JESD transmitter and receiver
    
    // Enable JESD Receiver
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ENMODULE_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_ip_enable,
                            JESD_XIP_204C_RX_ENMODULE_WR_MASK,
                            "JESD_XIP_204C_RX_ENMODULE"))
        return rv;
        
    // Enable JESD transmitter
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_ENMODULE_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_ip_enable,
                            JESD_XIP_204C_TX_ENMODULE_WR_MASK,
                            "JESD_XIP_204C_TX_ENMODULE"))
        return rv;                    
    
    // Cmn_csr sysref enable, as per simval log
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_RX_IP_SYSREF_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable,
                            JESD_CMN_CSR_RX_IP_SYSREF_CFG_WR_MASK,
                            "JESD_CMN_CSR_RX_IP_SYSREF_EN"))
        return rv;
    
    // Cmn_csr sysref enable, as per simval log
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESD_CMN_CSR_TX_IP_SYSREF_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_tx_ip_sysref_enable,
                            JESD_CMN_CSR_TX_IP_SYSREF_CFG_WR_MASK,
                            "JESD_CMN_CSR_TX_IP_SYSREF_EN"))
        return rv;
    
    print("INFO: JESD RX and TX IP en configuration completed for JESD%d\n", jesd_id);
    return rv;
}

/**
 * @brief           Function configuring VEX: Tx path
 * @param [in]      tx_vex_id
 * @return          status
 */
int configure_vex_tx(uint32_t tx_vex_id)
{

    int rv          = 0;
	int flags       = 0;
	int lc, i, j;
    
	unsigned int vex_dmem_offset    = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (tx_vex_id * vex_dmem_offset);
    
    unsigned int vex_vmem_offset    = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (tx_vex_id * vex_vmem_offset);
    
	int host_flag   = 1;
	
	//VEX time out cycles calculation
	int no_of_vector_per_block_per_stream   = 2;
	int vex_speed_mhz                       = 1024;
	int p5us_cycle_count                    = (vex_speed_mhz)/2; // 512
	int SAMPLE_PER_VECTOR                   = 32;
    uint32_t num_of_streams                 = jesd_config.jesd_link_config.converters / 2;
	int num_of_sample_p5us_per_stream       = (jesd_config.jesd_link_config.link_iq_bw/2)/num_of_streams;
	int num_of_vector_per_p5us_per_stream   = num_of_sample_p5us_per_stream/SAMPLE_PER_VECTOR;
    
	printf("num_of_vector_per_p5us_per_stream = %d \n", num_of_vector_per_p5us_per_stream);
    
	int ret_cycle_val                       = p5us_cycle_count* no_of_vector_per_block_per_stream/(num_of_vector_per_p5us_per_stream);
	ret_cycle_val                           = ret_cycle_val - 1;
	
    
    int vex_tx_offset_val[]       = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,
                                     HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
                                     HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
                                     HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base,
                                     HIVE_ADDR_jesd_tx_g_timeout_cycles};
    
    unsigned vex_tx_val_kargs[]   = {0x00000, 0x20000,
                                     0x40000, 0x60000,
                                     0x80000, 0xA0000,
                                     0xC0000, 0xE0000,
                                     ret_cycle_val};
    
    unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
                                     HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
                                     HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
                                     HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
									
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
	unsigned int add_val[1];
    
    printf("Host: Start Vex tx program load for Vex%d\n",tx_vex_id);
    if ((rv = vex_loader(tx_vex_id, "vex_fw/sim_m64/jesd_tx.fw")))
            return rv;
    printf("Host: Vex program load - done for Vex%d\n",tx_vex_id);
    
    
    printf("Host: Loading the host parameters to Vex%d\n",tx_vex_id);
    for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++)
    {
       write_mem_18a(vex_dmem_base_addr + vex_tx_offset_val[lc], 1, &vex_tx_val_kargs[lc], "gscalar");
    }                  
    printf("Host: Host parameters loaded to Vex%d\n",tx_vex_id);
    
    
    printf("Host: Input vectors generation start for Vex0 \n");
    // Input Vector Generation VEX
	for (lc = 0; lc < num_of_streams; lc++)
	{
        printf("DEBUG: vex_id %d, lc = %d\n",tx_vex_id, lc);
        for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
        {
            
            for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
            {
				val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
				val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
				val_inp[i][j] = val_inp[i][j] | (lc << 28 | lc << 12);

                write_mem_18a((vex_vmem_base_addr + vex_tx_buffer_addr[lc] + (j * sizeof(int)) + (i * NUM_OF_ELEMENTS_PER_VEC * sizeof(int))) ,//local_addr
                                1,
                                &(val_inp[i][j]),
                                "input vector gen");
                                
                printf("DEBUG: vex_id %d, addr = 0x%x , data = 0x%x\n",
                            tx_vex_id,
                            (vex_vmem_base_addr + vex_tx_buffer_addr[lc] + (j * sizeof(int)) + (i * NUM_OF_ELEMENTS_PER_VEC * sizeof(int))),
                            val_inp[i][j]);                 
                                           
            }
        }
    }
    printf("Host: Input vectors generated for Vex%d\n",tx_vex_id);
     
    printf("Host: Vex program start for Vex%d\n",tx_vex_id);
    vex_start(tx_vex_id, 0); // vex_0 start
    printf("Host: Vex program start - done for Vex%d\n",tx_vex_id);
    
    // Signal VEX to start continuous flow
    write_mem_18a(vex_dmem_base_addr + HIVE_ADDR_jesd_tx_g_host_indicator, 1, &host_flag, "tx_g_host_indicator");
    
    printf("dumping status reg in vex_tx api\n");
    printf("dumping VEX0 cio2strm_word_cnt - FIFO Word Counter\n");
	system("srpRead 0x02801024  1");
	printf("\n");
	
	printf("reading vex time_out cycles\n");
	system("srpRead 0x63.0.0x4030 1");
    printf("\n");
    
    printf("dumping jesd B2H flit count\n");
    system("srpRead 0x06704014 1");
    printf("\n");
    
    printf("dumping VEX1 strm2cio_word_cnt - FIFO Word Counter\n");
	system("srpRead 0x02842024 1");
	printf("\n");
    
    printf("dumping jesd H2B flit count\n");
    system("srpRead 0x06704314 1");
    printf("\n");
    
    //To VEX0
    printf("To VEX0 1 stream\n");
    system("srpRead 0x63.0.0x28000 64");
    printf("\n");
    
     //To VEX0
    printf("To VEX1 1 stream\n");
    system("srpRead 0x63.1.0x28000 64");
    printf("\n");
}
/**
 * @brief           Function to dump jesd registers EOT in Rx path
 * @param [in]      jesd_id
 * @return          status
 */
int dump_reg_jesd_rx(uint32_t jesd_id)
{
    uint32_t read_value;
    int i, j;
    extern void * srp;
    uint32_t error = 0;
    uint32_t write_status = 0;
    uint32_t dev_id =0;
    uint32_t dev_flags = 0;
    uint32_t tx_gb_empty_reg = 0;
    uint32_t tx_gb_full_reg = 0;
    uint32_t rx_gb_empty_reg = 0;
    uint32_t rx_gb_full_reg = 0;
    uint32_t sh_lock_status_reg = 0;
    uint32_t emb_lock_status_reg = 0;
    uint32_t sh_lock_loss_status_reg = 0;
    uint32_t emb_lock_loss_status_reg = 0;
    uint32_t rx_err_report_lane_reg0 = 0;
    uint32_t rx_err_report_lane_reg1 = 0;
    uint32_t rx_err_report_lane_reg2 = 0;
    uint32_t rx_err_report_lane_reg3 = 0;
    uint32_t rx_core_interrupt_mask = 0;
    uint32_t rx_core_interrupt_status = 0;
    uint32_t rx_lemc_boundary_phase = 0;
    uint32_t rx_sysref_cntr_status = 0;
    uint32_t nsip_hbi_intr_int_status = 0;
    uint32_t nsip_hbi_h2b_flit_cnt = 0;
    uint32_t rx_fec = 0;
    uint32_t rx_crc3_en = 0;
    uint32_t rx_crc12_en = 0;
    uint32_t stream0_buffer = 0;
    uint32_t stream1_buffer = 0;
    uint32_t stream2_buffer = 0;
    uint32_t stream3_buffer = 0;
    uint32_t stream4_buffer = 0;
    uint32_t stream5_buffer = 0;
    uint32_t stream6_buffer = 0;
    uint32_t stream7_buffer = 0;
    uint32_t stream8_buffer = 0;
    uint32_t stream9_buffer = 0;
    uint32_t stream10_buffer = 0;
    uint32_t stream11_buffer = 0;
    uint32_t stream12_buffer = 0;
    uint32_t stream13_buffer = 0;
    uint32_t stream14_buffer = 0;
    uint32_t stream15_buffer = 0;

    uint32_t rx_icounter_report_lane0 = 0;
    uint32_t rx_icounter_report_lane1  = 0;
    uint32_t rx_icounter_report_lane2  = 0;
    uint32_t rx_icounter_report_lane3  = 0;
    uint32_t rx_icounter_report_lane4  = 0;
    uint32_t rx_icounter_report_lane5  = 0;
    uint32_t rx_icounter_report_lane6  = 0;
    uint32_t rx_icounter_report_lane7  = 0;
    uint32_t rx_icounter_report_lane8  = 0;
    uint32_t rx_icounter_report_lane9  = 0;
    uint32_t rx_icounter_report_lane10 = 0;
    uint32_t rx_icounter_report_lane11 = 0;
    uint32_t rx_icounter_report_lane12 = 0;
    uint32_t rx_icounter_report_lane13 = 0;
    uint32_t rx_icounter_report_lane14 = 0;
    uint32_t rx_icounter_report_lane15 = 0;
    uint32_t rx_icounter_report_lane16 = 0;
    uint32_t rx_icounter_report_lane17 = 0;
    uint32_t rx_icounter_report_lane18 = 0;
    uint32_t rx_icounter_report_lane19 = 0;
    uint32_t rx_icounter_report_lane20 = 0;
    uint32_t rx_icounter_report_lane21 = 0;
    uint32_t rx_icounter_report_lane22 = 0;
    uint32_t rx_icounter_report_lane23 = 0;

    uint32_t curr_icounter_report_lane0  = 0;
    uint32_t curr_icounter_report_lane1  = 0;
    uint32_t curr_icounter_report_lane2  = 0;
    uint32_t curr_icounter_report_lane3  = 0;
    uint32_t curr_icounter_report_lane4  = 0;
    uint32_t curr_icounter_report_lane5  = 0;
    uint32_t curr_icounter_report_lane6  = 0;
    uint32_t curr_icounter_report_lane7  = 0;
    uint32_t curr_icounter_report_lane8  = 0;
    uint32_t curr_icounter_report_lane9  = 0;
    uint32_t curr_icounter_report_lane10 = 0;
    uint32_t curr_icounter_report_lane11 = 0;
    uint32_t curr_icounter_report_lane12 = 0;
    uint32_t curr_icounter_report_lane13 = 0;
    uint32_t curr_icounter_report_lane14 = 0;
    uint32_t curr_icounter_report_lane15 = 0;
    uint32_t curr_icounter_report_lane16 = 0;
    uint32_t curr_icounter_report_lane17 = 0;
    uint32_t curr_icounter_report_lane18 = 0;
    uint32_t curr_icounter_report_lane19 = 0;
    uint32_t curr_icounter_report_lane20 = 0;
    uint32_t curr_icounter_report_lane21 = 0;
    uint32_t curr_icounter_report_lane22 = 0;
    uint32_t curr_icounter_report_lane23 = 0;
    uint32_t curr_tx_gb_empty_reg = 0;
    uint32_t curr_tx_gb_full_reg = 0;
    uint32_t curr_rx_gb_empty_reg = 0;
    uint32_t curr_rx_gb_full_reg = 0;
    uint32_t curr_rx_err_report_lane_reg0 = 0;
    uint32_t curr_rx_err_report_lane_reg1 = 0;
    uint32_t curr_rx_err_report_lane_reg2 = 0;
    uint32_t curr_rx_err_report_lane_reg3 = 0;
    uint32_t curr_rx_core_interrupt_mask = 0;
    uint32_t curr_rx_core_interrupt_status = 0;
    uint32_t curr_rx_lemc_boundary_phase = 0;
    uint32_t curr_rx_sysref_cntr_status = 0;

    uint32_t prev_icounter_report_lane0   = 0;
    uint32_t prev_icounter_report_lane1  = 0;
    uint32_t prev_icounter_report_lane2  = 0;
    uint32_t prev_icounter_report_lane3  = 0;
    uint32_t prev_icounter_report_lane4  = 0;
    uint32_t prev_icounter_report_lane5  = 0;
    uint32_t prev_icounter_report_lane6  = 0;
    uint32_t prev_icounter_report_lane7  = 0;
    uint32_t prev_icounter_report_lane8  = 0;
    uint32_t prev_icounter_report_lane9  = 0;
    uint32_t prev_icounter_report_lane10 = 0;
    uint32_t prev_icounter_report_lane11 = 0;
    uint32_t prev_icounter_report_lane12 = 0;
    uint32_t prev_icounter_report_lane13 = 0;
    uint32_t prev_icounter_report_lane14 = 0;
    uint32_t prev_icounter_report_lane15 = 0;
    uint32_t prev_icounter_report_lane16 = 0;
    uint32_t prev_icounter_report_lane17 = 0;
    uint32_t prev_icounter_report_lane18 = 0;
    uint32_t prev_icounter_report_lane19 = 0;
    uint32_t prev_icounter_report_lane20 = 0;
    uint32_t prev_icounter_report_lane21 = 0;
    uint32_t prev_icounter_report_lane22 = 0;
    uint32_t prev_icounter_report_lane23 = 0;
    uint32_t prev_tx_gb_empty_reg = 0;
    uint32_t prev_tx_gb_full_reg = 0;
    uint32_t prev_rx_gb_empty_reg = 0;
    uint32_t prev_rx_gb_full_reg = 0;
    uint32_t prev_rx_err_report_lane_reg0 = 0;
    uint32_t prev_rx_err_report_lane_reg1 = 0;
    uint32_t prev_rx_err_report_lane_reg2 = 0;
    uint32_t prev_rx_err_report_lane_reg3 = 0;
    uint32_t prev_rx_core_interrupt_mask = 0;
    uint32_t prev_rx_core_interrupt_status = 0;
    uint32_t prev_rx_lemc_boundary_phase = 0;
    uint32_t prev_rx_sysref_cntr_status = 0;

    uint32_t print  = 0;
    uint32_t print1  = 0;
    uint32_t print2  = 0;
    uint32_t print3  = 0;
    uint32_t print4  = 0;
    uint32_t print5  = 0;
    uint32_t print6  = 0;
    uint32_t print7  = 0;
    uint32_t print8  = 0;
    uint32_t print9  = 0;
    uint32_t print10 = 0;
    uint32_t print11 = 0;
    uint32_t print12 = 0;
    uint32_t print13 = 0;
    uint32_t print14 = 0;
    uint32_t print15 = 0;
    uint32_t print16 = 0;
    uint32_t print17 = 0;
    uint32_t print18 = 0;
    uint32_t print19 = 0;
    uint32_t print20 = 0;
    uint32_t print21 = 0;
    uint32_t print22 = 0;
    uint32_t print23 = 0;
    uint32_t print24 = 0;
    uint32_t print25 = 0;
    uint32_t print26 = 0;
    uint32_t print27 = 0;
    uint32_t print38 = 0;
    uint32_t print39 = 0;
    uint32_t print40 = 0;
    uint32_t print41 = 0;
    uint32_t print42 = 0;
    uint32_t print43 = 0;
    uint32_t print44 = 0;
    uint32_t print45 = 0;

    uint32_t count = 0;
    
    int jesd_rx_ip_base     = g_jesd_rx_ip_base_addr[jesd_id];
    int jesd_tx_ip_base     = g_jesd_tx_ip_base_addr[jesd_id];
    int jesd_nsip_hbi_base  = g_jesd_nsip_base_addr[jesd_id];
    
    srp_dev_open(dev_id, dev_flags, &srp);

    delay(2000);
    while(count < 1)
    //while(1)
    {
       
        tx_gb_empty_reg             = read_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_GEARBOX_EMPTY_STAT_OFFSET, "JESD_XIP_204C_TX_GEARBOX_EMPTY_STAT");
        tx_gb_full_reg              = read_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_GEARBOX_FULL_STAT_OFFSET, "JESD_XIP_204C_TX_GEARBOX_FULL_STAT");
        
        rx_gb_empty_reg             = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_OFFSET, "JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT");
        rx_gb_full_reg              = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_GEARBOX_FULL_STAT_OFFSET, "JESD_XIP_204C_RX_GEARBOX_FULL_STAT");
        
        sh_lock_status_reg          = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SH_LOCK_STAT_OFFSET, "JESD_XIP_204C_RX_SH_LOCK_STAT");
        emb_lock_status_reg         = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_EMB_LOCK_STAT_OFFSET, "JESD_XIP_204C_RX_EMB_LOCK_STAT");
        
        sh_lock_loss_status_reg     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_OFFSET, "JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT");
        emb_lock_loss_status_reg    = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_OFFSET, "JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT");
        
        rx_err_report_lane_reg0     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ERR_RPT_LANE_REG0_OFFSET, "JESD_XIP_204C_RX_ERR_RPT_LANE_REG0");
        rx_err_report_lane_reg1     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ERR_RPT_LANE_REG1_OFFSET, "JESD_XIP_204C_RX_ERR_RPT_LANE_REG1");
        rx_err_report_lane_reg2     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ERR_RPT_LANE_REG2_OFFSET, "JESD_XIP_204C_RX_ERR_RPT_LANE_REG2");
        rx_err_report_lane_reg3     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ERR_RPT_LANE_REG3_OFFSET, "JESD_XIP_204C_RX_ERR_RPT_LANE_REG3");
        
        rx_fec                      = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_FEC_OFFSET, "JESD_XIP_204C_RX_FEC");
        rx_crc3_en                  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CRC3_EN_OFFSET, "JESD_XIP_204C_RX_CRC3_EN");
        rx_crc12_en                 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CRC12_EN_OFFSET, "JESD_XIP_204C_RX_CRC12_EN");
        
        //INT STATUS -if jesd 204c and rx cfg en  
        rx_core_interrupt_mask      = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CORE_INTR_MASK_OFFSET, "JESD_XIP_204C_RX_CORE_INTR_MASK");
        rx_core_interrupt_status    = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_CORE_INTR_STAT_OFFSET, "JESD_XIP_204C_RX_CORE_INTR_STAT");
        
        //lemc boundary phase TODO: can these be predicted?-if jesd 204c and rx cfg en 
        rx_lemc_boundary_phase      = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE_OFFSET, "JESD_XIP_204C_RX_LEMC_BOUNDARY_PHASE");
        
        //Sysref-  One shot sysref / periodic sysre -if jesd 204c and rx cfg en 
        rx_sysref_cntr_status       = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SYSREF_CNTER_STAT_OFFSET, "JESD_XIP_204C_RX_SYSREF_CNTER_STAT");
        
        //hbi
        nsip_hbi_intr_int_status    = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_INTR_INT_STAT_OFFSET, "NSIP_HBI_INTR_INT_STAT");
        nsip_hbi_h2b_flit_cnt       = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "NSIP_HBI_H2B_FLIT");

        printf("\n\n");
        printf("//############################################################\n");
        printf("Present value of TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
        printf("Present value of TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
        
        printf("Present value of RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
        printf("Present value of for RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
        
        printf("\n");
        printf("Present value of SH lock of Link0 is 0x%x \n",sh_lock_status_reg);
        printf("Present value of EMB lock of Link0 is 0x%x \n",emb_lock_status_reg);
        
        printf("Present value of SH lock loss of Link0 is 0x%x \n",sh_lock_loss_status_reg);
        printf("Present value of EMB lock loss of Link0 is 0x%x \n",emb_lock_loss_status_reg);
        
        printf("Present value of RX_ERROR_REPORT_LANE_REG0 of Link0 is 0x%x \n",rx_err_report_lane_reg0);
        printf("Present value of RX_ERROR_REPORT_LANE_REG1 of Link0 is 0x%x \n",rx_err_report_lane_reg1);
        printf("Present value of RX_ERROR_REPORT_LANE_REG2 of Link0 is 0x%x \n",rx_err_report_lane_reg2);
        printf("Present value of RX_ERROR_REPORT_LANE_REG3 of Link0 is 0x%x \n",rx_err_report_lane_reg3);
        
        printf("Present value of JESD_XIP_204C_RX_MEM_RX_FEC of Link0 is 0x%x \n",rx_fec);
        printf("Present value of JESD_XIP_204C_RX_MEM_RX_CRC3_EN of Link0 is 0x%x \n",rx_crc3_en);
        printf("Present value of JESD_XIP_204C_RX_MEM_RX_CRC12_EN of Link0 is 0x%x \n",rx_crc12_en);
        
        printf("Present value of RX_CORE_INTERRUPT_MASK of Link0 is 0x%x \n",rx_core_interrupt_mask);
        printf("Present value of RX_CORE_INTERRUPT_STATUS of Link0 is 0x%x \n",rx_core_interrupt_status);
        
        printf("Present value of RX_LEMC_BOUNDARY_PHASE of Link0 is 0x%x \n",rx_lemc_boundary_phase);
        
        printf("Present value of RX_SYSREF_COUNTER_STATUS of Link0 is 0x%x \n",rx_sysref_cntr_status);
        
        printf("Present value of NSIP_HBI_INTR_INT_STATUS of Link0 is 0x%x \n",nsip_hbi_intr_int_status);
        printf("Present value of NSIP_HBI_H2B_FLIT_COUNT of Link0 is 0x%x \n",nsip_hbi_h2b_flit_cnt);
        printf("\n");

        
        rx_icounter_report_lane0  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE0_OFFSET, "ICOUNTER_REPORT_LANE0");
        rx_icounter_report_lane1  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE1_OFFSET, "ICOUNTER_REPORT_LANE1");
        rx_icounter_report_lane2  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE2_OFFSET, "ICOUNTER_REPORT_LANE2");
        rx_icounter_report_lane3  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE3_OFFSET, "ICOUNTER_REPORT_LANE3");
        rx_icounter_report_lane4  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE4_OFFSET, "ICOUNTER_REPORT_LANE4");
        rx_icounter_report_lane5  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE5_OFFSET, "ICOUNTER_REPORT_LANE5");
        rx_icounter_report_lane6  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE6_OFFSET, "ICOUNTER_REPORT_LANE6");
        rx_icounter_report_lane7  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE7_OFFSET, "ICOUNTER_REPORT_LANE7");
        rx_icounter_report_lane8  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE8_OFFSET, "ICOUNTER_REPORT_LANE8");
        rx_icounter_report_lane9  = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE9_OFFSET, "ICOUNTER_REPORT_LANE9");
        rx_icounter_report_lane10 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE10_OFFSET, "ICOUNTER_REPORT_LANE10");
        rx_icounter_report_lane11 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE11_OFFSET, "ICOUNTER_REPORT_LANE11");
        rx_icounter_report_lane12 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE12_OFFSET, "ICOUNTER_REPORT_LANE12");
        rx_icounter_report_lane13 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE13_OFFSET, "ICOUNTER_REPORT_LANE13");
        rx_icounter_report_lane14 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE14_OFFSET, "ICOUNTER_REPORT_LANE14");
        rx_icounter_report_lane15 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE15_OFFSET, "ICOUNTER_REPORT_LANE15");
        rx_icounter_report_lane16 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE16_OFFSET, "ICOUNTER_REPORT_LANE16");
        rx_icounter_report_lane17 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE17_OFFSET, "ICOUNTER_REPORT_LANE17");
        rx_icounter_report_lane18 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE18_OFFSET, "ICOUNTER_REPORT_LANE18");
        rx_icounter_report_lane19 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE19_OFFSET, "ICOUNTER_REPORT_LANE19");
        rx_icounter_report_lane20 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE20_OFFSET, "ICOUNTER_REPORT_LANE20");
        rx_icounter_report_lane21 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE21_OFFSET, "ICOUNTER_REPORT_LANE21");
        rx_icounter_report_lane22 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE22_OFFSET, "ICOUNTER_REPORT_LANE22");
        rx_icounter_report_lane23 = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_ICNTER_RPT_LANE23_OFFSET, "ICOUNTER_REPORT_LANE23");
        
        rx_gb_empty_reg           = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT_OFFSET, "JESD_XIP_204C_RX_GEARBOX_EMPTY_STAT");
        rx_gb_full_reg            = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_GEARBOX_FULL_STAT_OFFSET, "JESD_XIP_204C_RX_GEARBOX_FULL_STAT");
        
        tx_gb_empty_reg           = read_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_GEARBOX_EMPTY_STAT_OFFSET, "JESD_XIP_204C_TX_GEARBOX_EMPTY_STAT");
        tx_gb_full_reg            = read_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_GEARBOX_FULL_STAT_OFFSET, "JESD_XIP_204C_TX_GEARBOX_FULL_STAT");
           
        if( count == 0 )
        {
            printf("\n");
            printf("\n");

            printf(" Present value of ICOUNTER_REPORT_LANE0  is 0x%x \n",  rx_icounter_report_lane0);
            printf(" Present value of ICOUNTER_REPORT_LANE1  is 0x%x \n",  rx_icounter_report_lane1);
            printf(" Present value of ICOUNTER_REPORT_LANE2  is 0x%x \n",  rx_icounter_report_lane2);
            printf(" Present value of ICOUNTER_REPORT_LANE3  is 0x%x \n",  rx_icounter_report_lane3);
            printf(" Present value of ICOUNTER_REPORT_LANE4  is 0x%x \n",  rx_icounter_report_lane4);
            printf(" Present value of ICOUNTER_REPORT_LANE5  is 0x%x \n",  rx_icounter_report_lane5);
            printf(" Present value of ICOUNTER_REPORT_LANE6  is 0x%x \n",  rx_icounter_report_lane6);
            printf(" Present value of ICOUNTER_REPORT_LANE7  is 0x%x \n",  rx_icounter_report_lane7);
            printf(" Present value of ICOUNTER_REPORT_LANE8  is 0x%x \n",  rx_icounter_report_lane8);
            printf(" Present value of ICOUNTER_REPORT_LANE9  is 0x%x \n",  rx_icounter_report_lane9);
            printf(" Present value of ICOUNTER_REPORT_LANE10 is 0x%x \n", rx_icounter_report_lane10);
            printf(" Present value of ICOUNTER_REPORT_LANE11 is 0x%x \n", rx_icounter_report_lane11);
            printf(" Present value of ICOUNTER_REPORT_LANE12 is 0x%x \n", rx_icounter_report_lane12);
            printf(" Present value of ICOUNTER_REPORT_LANE13 is 0x%x \n", rx_icounter_report_lane13);
            printf(" Present value of ICOUNTER_REPORT_LANE14 is 0x%x \n", rx_icounter_report_lane14);
            printf(" Present value of ICOUNTER_REPORT_LANE15 is 0x%x \n", rx_icounter_report_lane15);
            printf(" Present value of ICOUNTER_REPORT_LANE16 is 0x%x \n", rx_icounter_report_lane16);
            printf(" Present value of ICOUNTER_REPORT_LANE17 is 0x%x \n", rx_icounter_report_lane17);
            printf(" Present value of ICOUNTER_REPORT_LANE18 is 0x%x \n", rx_icounter_report_lane18);
            printf(" Present value of ICOUNTER_REPORT_LANE19 is 0x%x \n", rx_icounter_report_lane19);
            printf(" Present value of ICOUNTER_REPORT_LANE20 is 0x%x \n", rx_icounter_report_lane20);
            printf(" Present value of ICOUNTER_REPORT_LANE21 is 0x%x \n", rx_icounter_report_lane21);
            printf(" Present value of ICOUNTER_REPORT_LANE22 is 0x%x \n", rx_icounter_report_lane22);
            printf(" Present value of ICOUNTER_REPORT_LANE23 is 0x%x \n", rx_icounter_report_lane23);
            
            printf(" Present value of RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
            printf(" Present value of RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
            
            printf(" Present value of TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
            printf(" Present value of TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
        }
        
        if(rx_icounter_report_lane0)
        {
            curr_icounter_report_lane0 = rx_icounter_report_lane0;
            if(prev_icounter_report_lane0 != curr_icounter_report_lane0)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE0 are 0x%x, 0x%x\n", prev_icounter_report_lane0, curr_icounter_report_lane0);
                print = 1;
                prev_icounter_report_lane0 = curr_icounter_report_lane0;
            }
        }

        if(rx_icounter_report_lane1)
        {
            curr_icounter_report_lane1 = rx_icounter_report_lane1;
            if(prev_icounter_report_lane1 != curr_icounter_report_lane1)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE1 are 0x%x, 0x%x\n", prev_icounter_report_lane1, curr_icounter_report_lane0);
                print1 = 1;
                prev_icounter_report_lane1 = curr_icounter_report_lane0;
            }
        }

        if(rx_icounter_report_lane2)
        {
            curr_icounter_report_lane2 = rx_icounter_report_lane2;
            if(prev_icounter_report_lane2 != curr_icounter_report_lane2)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE2 are 0x%x, 0x%x\n", prev_icounter_report_lane2, curr_icounter_report_lane2);
                print2 = 1;
                prev_icounter_report_lane2 = curr_icounter_report_lane2;
            }
        }

        if(rx_icounter_report_lane3)
        {
            curr_icounter_report_lane3 = rx_icounter_report_lane3;
            if(prev_icounter_report_lane3 != curr_icounter_report_lane3)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE3 are 0x%x, 0x%x\n", prev_icounter_report_lane3, curr_icounter_report_lane3);
                print3 = 1;
                prev_icounter_report_lane3 = curr_icounter_report_lane3;
            }
        }

        if(rx_icounter_report_lane4)
        {
            curr_icounter_report_lane4 = rx_icounter_report_lane4;
            if(prev_icounter_report_lane4 != curr_icounter_report_lane4)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE4 are 0x%x, 0x%x\n", prev_icounter_report_lane4, curr_icounter_report_lane4);
                print4 = 1;
                prev_icounter_report_lane4 = curr_icounter_report_lane4;
            }
        }

        if(rx_icounter_report_lane5)
        {
            curr_icounter_report_lane5 = rx_icounter_report_lane5;
            if(prev_icounter_report_lane5 != curr_icounter_report_lane5)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE5 are 0x%x, 0x%x\n", prev_icounter_report_lane5, curr_icounter_report_lane5);
                print5 = 1;
                prev_icounter_report_lane5 = curr_icounter_report_lane5;
            }
        }

        if(rx_icounter_report_lane6)
        {
            curr_icounter_report_lane6 = rx_icounter_report_lane6;
            if(prev_icounter_report_lane6 != curr_icounter_report_lane6)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE6 are 0x%x, 0x%x\n", prev_icounter_report_lane6, curr_icounter_report_lane6);
                print6 = 1;
                prev_icounter_report_lane6 = curr_icounter_report_lane6;
            }
        }

        if(rx_icounter_report_lane7)
        {
            curr_icounter_report_lane7 = rx_icounter_report_lane7;
            if(prev_icounter_report_lane7 != curr_icounter_report_lane7)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE7 are 0x%x, 0x%x\n", prev_icounter_report_lane7, curr_icounter_report_lane7);
                print7 = 1;
                prev_icounter_report_lane7 = curr_icounter_report_lane7;
            }
        }

        if(rx_icounter_report_lane8)
        {
            curr_icounter_report_lane8 = rx_icounter_report_lane8;
            if(prev_icounter_report_lane8 != curr_icounter_report_lane8)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE8 are 0x%x, 0x%x\n", prev_icounter_report_lane8, curr_icounter_report_lane8);
                print8 = 1;
                prev_icounter_report_lane8 = curr_icounter_report_lane8;
            }
        }

        if(rx_icounter_report_lane9)
        {
            curr_icounter_report_lane9 = rx_icounter_report_lane9;
            if(prev_icounter_report_lane9 != curr_icounter_report_lane9)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE9 are 0x%x, 0x%x\n", prev_icounter_report_lane9, curr_icounter_report_lane9);
                print9 = 1;
                prev_icounter_report_lane9 = curr_icounter_report_lane9;
            }
        }

        if(rx_icounter_report_lane10)
        {
            curr_icounter_report_lane10 = rx_icounter_report_lane10;
            if(prev_icounter_report_lane10 != curr_icounter_report_lane10)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE10 are 0x%x, 0x%x\n", prev_icounter_report_lane10, curr_icounter_report_lane10);
                print10 = 1;
                prev_icounter_report_lane10 = curr_icounter_report_lane10;
            }
        }

        if(rx_icounter_report_lane11)
        {
            curr_icounter_report_lane11 = rx_icounter_report_lane11;
            if(prev_icounter_report_lane11 != curr_icounter_report_lane11)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE11 are 0x%x, 0x%x\n", prev_icounter_report_lane11, curr_icounter_report_lane11);
                print11 = 1;
                prev_icounter_report_lane11 = curr_icounter_report_lane11;
            }
        }

        if(rx_icounter_report_lane12)
        {
            curr_icounter_report_lane12 = rx_icounter_report_lane12;
            if(prev_icounter_report_lane12 != curr_icounter_report_lane12)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE12 are 0x%x, 0x%x\n", prev_icounter_report_lane12, curr_icounter_report_lane12);
                print12 = 1;
                prev_icounter_report_lane12 = curr_icounter_report_lane12;
            }
        }

        if(rx_icounter_report_lane13)
        {
            curr_icounter_report_lane13 = rx_icounter_report_lane13;
            if(prev_icounter_report_lane13 != curr_icounter_report_lane13)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE13 are 0x%x, 0x%x\n", prev_icounter_report_lane13, curr_icounter_report_lane13);
                print13 = 1;
                prev_icounter_report_lane13 = curr_icounter_report_lane13;
            }
        }

        if(rx_icounter_report_lane14)
        {
            curr_icounter_report_lane14 = rx_icounter_report_lane14;
            if(prev_icounter_report_lane14 != curr_icounter_report_lane14)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE14 are 0x%x, 0x%x\n", prev_icounter_report_lane14, curr_icounter_report_lane14);
                print14 = 1;
                prev_icounter_report_lane14 = curr_icounter_report_lane14;
            }
        }

        if(rx_icounter_report_lane15)
        {
            curr_icounter_report_lane15 = rx_icounter_report_lane15;
            if(prev_icounter_report_lane15 != curr_icounter_report_lane15)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE15 are 0x%x, 0x%x\n", prev_icounter_report_lane15, curr_icounter_report_lane15);
                print15 = 1;
                prev_icounter_report_lane15 = curr_icounter_report_lane15;
            }
        }

        if(rx_icounter_report_lane16)
        {
            curr_icounter_report_lane16 = rx_icounter_report_lane16;
            if(prev_icounter_report_lane16 != curr_icounter_report_lane16)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE16 are 0x%x, 0x%x\n", prev_icounter_report_lane16, curr_icounter_report_lane16);
                print16 = 1;
                prev_icounter_report_lane16 = curr_icounter_report_lane16;
            }
        }

        if(rx_icounter_report_lane17)
        {
            curr_icounter_report_lane17 = rx_icounter_report_lane17;
            if(prev_icounter_report_lane17 != curr_icounter_report_lane17)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE17 are 0x%x, 0x%x\n", prev_icounter_report_lane17, curr_icounter_report_lane17);
                print17 = 1;
                prev_icounter_report_lane17 = curr_icounter_report_lane17;
            }
        }

        if(rx_icounter_report_lane18)
        {
            curr_icounter_report_lane18 = rx_icounter_report_lane18;
            if(prev_icounter_report_lane18 != curr_icounter_report_lane18)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE18 are 0x%x, 0x%x\n", prev_icounter_report_lane18, curr_icounter_report_lane18);
                print18 = 1;
                prev_icounter_report_lane18 = curr_icounter_report_lane18;
            }
        }

        if(rx_icounter_report_lane19)
        {
            curr_icounter_report_lane19 = rx_icounter_report_lane19;
            if(prev_icounter_report_lane19 != curr_icounter_report_lane19)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE19 are 0x%x, 0x%x\n", prev_icounter_report_lane19, curr_icounter_report_lane19);
                print19 = 1;
                prev_icounter_report_lane19 = curr_icounter_report_lane19;
            }
        }

        if(rx_icounter_report_lane20)
        {
            curr_icounter_report_lane20 = rx_icounter_report_lane20;
            if(prev_icounter_report_lane20 != curr_icounter_report_lane20)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE20 are 0x%x, 0x%x\n", prev_icounter_report_lane20, curr_icounter_report_lane20);
                print20 = 1;
                prev_icounter_report_lane20 = curr_icounter_report_lane20;
            }
        }

        if(rx_icounter_report_lane21)
        {
            curr_icounter_report_lane21 = rx_icounter_report_lane21;
            if(prev_icounter_report_lane21 != curr_icounter_report_lane21)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE21 are 0x%x, 0x%x\n", prev_icounter_report_lane21, curr_icounter_report_lane21);
                print21 = 1;
                prev_icounter_report_lane21 = curr_icounter_report_lane21;
            }
        }

        if(rx_icounter_report_lane22)
        {
            curr_icounter_report_lane22 = rx_icounter_report_lane22;
            if(prev_icounter_report_lane22 != curr_icounter_report_lane22)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE22 are 0x%x, 0x%x\n", prev_icounter_report_lane22, curr_icounter_report_lane22);
                print22 = 1;
                prev_icounter_report_lane22 = curr_icounter_report_lane22;
            }
        }

        if(rx_icounter_report_lane23)
        {
            curr_icounter_report_lane23 = rx_icounter_report_lane23;
            if(prev_icounter_report_lane23 != curr_icounter_report_lane23)
            {
                printf(" \nprevious and current value for ICOUNTER_REPORT_LANE23 are 0x%x, 0x%x\n", prev_icounter_report_lane23, curr_icounter_report_lane23);
                print23 = 1;
                prev_icounter_report_lane23 = curr_icounter_report_lane23;
            }
        }

        if(tx_gb_empty_reg)
        {
            curr_tx_gb_empty_reg = tx_gb_empty_reg;
            if(prev_tx_gb_empty_reg != curr_tx_gb_empty_reg)
            {
                printf(" \nprevious and current value for TX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_tx_gb_empty_reg, curr_tx_gb_empty_reg);
                print24 = 1;
                prev_tx_gb_empty_reg = curr_tx_gb_empty_reg;
            }
        }

        if(tx_gb_full_reg)
        {
            curr_tx_gb_full_reg = tx_gb_full_reg;
            if(prev_tx_gb_full_reg != curr_tx_gb_full_reg)
            {
                printf(" \nprevious and current value for TX_GB_FULL_REG are 0x%x, 0x%x\n", prev_tx_gb_full_reg, curr_tx_gb_full_reg);
                print25 = 1;
                prev_tx_gb_full_reg = curr_tx_gb_full_reg;
            }
        }

        if(rx_gb_empty_reg)
        {
            curr_rx_gb_empty_reg = rx_gb_empty_reg;
            if(prev_rx_gb_empty_reg != curr_rx_gb_empty_reg)
            {
                printf(" \nprevious and current value for RX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_rx_gb_empty_reg, curr_rx_gb_empty_reg);
                print26 = 1;
                prev_rx_gb_empty_reg = curr_rx_gb_empty_reg;
            }
        }

        if(rx_gb_full_reg)
        {
            curr_rx_gb_full_reg = rx_gb_full_reg;
            if(prev_rx_gb_full_reg != curr_rx_gb_full_reg)
            {
                printf(" \nprevious and current value for RX_GB_FULL_REG are 0x%x, 0x%x\n", prev_rx_gb_full_reg, curr_rx_gb_full_reg);
                print27 = 1;
                prev_rx_gb_full_reg = curr_rx_gb_full_reg;
            }
        }

            if(rx_err_report_lane_reg0)
            {
                curr_rx_err_report_lane_reg0 = rx_err_report_lane_reg0;
                if(prev_rx_err_report_lane_reg0 != curr_rx_err_report_lane_reg0)
                {
                printf(" \nprevious and current value for RX_ERROR_REPORT_LANE_REG0 are 0x%x, 0x%x\n", prev_rx_err_report_lane_reg0, curr_rx_err_report_lane_reg0);
                    print38 = 1;
                    prev_rx_err_report_lane_reg0 = curr_rx_err_report_lane_reg0;
                }
            }
            
            if(rx_err_report_lane_reg1)
            {
                curr_rx_err_report_lane_reg1 = rx_err_report_lane_reg1;
                if(prev_rx_err_report_lane_reg1 != curr_rx_err_report_lane_reg1)
                {
                printf(" \nprevious and current value for RX_ERROR_REPORT_LANE_REG1 are 0x%x, 0x%x\n", prev_rx_err_report_lane_reg1, curr_rx_err_report_lane_reg1);
                    print39 = 1;
                    prev_rx_err_report_lane_reg1 = curr_rx_err_report_lane_reg1;
                }
            }

            if(rx_err_report_lane_reg2)
            {
                curr_rx_err_report_lane_reg2 = rx_err_report_lane_reg2;
                if(prev_rx_err_report_lane_reg2 != curr_rx_err_report_lane_reg2)
                {
                printf(" \nprevious and current value for RX_ERROR_REPORT_LANE_REG2 are 0x%x, 0x%x\n", prev_rx_err_report_lane_reg2, curr_rx_err_report_lane_reg2);
                    print40 = 1;
                    prev_rx_err_report_lane_reg2 = curr_rx_err_report_lane_reg2;
                }
            }

            if(rx_err_report_lane_reg3)
            {
                curr_rx_err_report_lane_reg3 = rx_err_report_lane_reg3;
                if(prev_rx_err_report_lane_reg3 != curr_rx_err_report_lane_reg3)
                {
                printf(" \nprevious and current value for RX_ERROR_REPORT_LANE_REG3 are 0x%x, 0x%x\n", prev_rx_err_report_lane_reg3, curr_rx_err_report_lane_reg3);
                    print41 = 1;
                    prev_rx_err_report_lane_reg3 = curr_rx_err_report_lane_reg0;
                }
            }

            if(rx_core_interrupt_mask)
            {
                curr_rx_core_interrupt_mask = rx_core_interrupt_mask;
                if(prev_rx_core_interrupt_mask != curr_rx_core_interrupt_mask)
                {
                printf(" \nprevious and current value for RX_CORE_INTERRUPT_MASK_OFFSET are 0x%x, 0x%x\n", prev_rx_core_interrupt_mask, curr_rx_core_interrupt_mask);
                    print42 = 1;
                    prev_rx_core_interrupt_mask = curr_rx_core_interrupt_mask;
                }
            }

            if(rx_core_interrupt_status)
            {
                curr_rx_core_interrupt_status = rx_core_interrupt_status;
                if(prev_rx_core_interrupt_status != curr_rx_core_interrupt_status)
                {
                printf(" \nprevious and current value for RX_CORE_INTERRUPT_STATUS_OFFSET are 0x%x, 0x%x\n", prev_rx_core_interrupt_status, curr_rx_core_interrupt_status);
                    print43 = 1;
                    prev_rx_core_interrupt_status = curr_rx_core_interrupt_status;
                }
            }

            if(rx_lemc_boundary_phase)
            {
                curr_rx_lemc_boundary_phase = rx_lemc_boundary_phase;
                if(prev_rx_lemc_boundary_phase != curr_rx_lemc_boundary_phase)
                {
                printf(" \nprevious and current value for RX_LEMC_BOUNDARY_PHASE are 0x%x, 0x%x\n", prev_rx_lemc_boundary_phase, curr_rx_lemc_boundary_phase);
                    print44 = 1;
                    prev_rx_lemc_boundary_phase = curr_rx_lemc_boundary_phase;
                }
            }

            if(rx_sysref_cntr_status)
            {
                curr_rx_sysref_cntr_status = rx_sysref_cntr_status;
                if(prev_rx_sysref_cntr_status != curr_rx_sysref_cntr_status)
                {
                printf(" \nprevious and current value for RX_SYSREF_COUNTER_STATUS are 0x%x, 0x%x\n", prev_rx_sysref_cntr_status, curr_rx_sysref_cntr_status);
                    print45 = 1;
                    prev_rx_sysref_cntr_status = curr_rx_sysref_cntr_status;
                }
            }

        if((print == 1) || (print1 == 1) || (print2 == 1) || (print3 == 1) || (print4 == 1) || (print5 == 1) || (print6 == 1) || (print7 == 1) || (print8 == 1) || (print9 == 1) || (print10 == 1) || (print11 == 1) || (print12 == 1) || (print13 == 1) || (print14 == 1) || (print15 == 1) || (print16 == 1) || (print17 == 1) || (print18 == 1) || (print19 == 1) || (print20 == 1) || (print21 == 1) || (print22 == 1) || (print23 == 1) || (print24 == 1) || (print25 == 1) || (print26 == 1) || (print27 == 1) || (print38 == 1)  || (print39 == 1)  || (print40 == 1)  || (print41 == 1)  || (print42 == 1)  || (print43 == 1)  || (print44 == 1)  || (print45 == 1))
        {
            printf("\n\n");
            printf("\n");
            printf("\n\n");
            print   = 0;
            print1  = 0;
            print2  = 0;
            print3  = 0;
            print4  = 0;
            print5  = 0;
            print6  = 0;
            print7  = 0;
            print8  = 0;
            print9  = 0;
            print10 = 0;
            print11 = 0;
            print12 = 0;
            print13 = 0;
            print14 = 0;
            print15 = 0;
            print16 = 0;
            print17 = 0;
            print18 = 0;
            print19 = 0;
            print20 = 0;
            print21 = 0;
            print22 = 0;
            print23 = 0;
            print24 = 0;
            print25 = 0;
            print26 = 0;
            print27 = 0;
            print38 = 0;
            print39 = 0;
            print40 = 0;
            print41 = 0;
            print42 = 0;
            print43 = 0;
            print44 = 0;
            print45 = 0;
            count   = 1;
        }
        else
        {
            if((count % 3000) == 0)
            printf(" no change in errors and no change in fifo empty or full at both rx and tx \n");
        }
        //if((count % 1000) == 0)
        //    printf("########count is %d \n",count);
        //delay(10000);
        delay(1000);
        count = count + 1;
    }
    
    //read NSIP_FLIT_COUNT
    //uint32_t nsip_hbi_h2b_flit_cnt  = 0;
    nsip_hbi_h2b_flit_cnt  = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "NSIP_HBI_H2B_FLIT_CNT");
    printf("Present value of NSIP_HBI_H2B_FLIT_CNT is 0x%x \n",nsip_hbi_h2b_flit_cnt);
    printf("\n");
    i=0;
    while(i < 5)
    {
        delay(1000);
        nsip_hbi_h2b_flit_cnt  = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "NSIP_HBI_H2B_FLIT_CNT");
        printf("Present value of NSIP_HBI_H2B_FLIT_CNT is 0x%x \n",nsip_hbi_h2b_flit_cnt);
        delay(1000);
        i++;
    }
    
}
/**
 * @brief           Function to dump jesd registers EOT in Tx path
 * @param [in]      jesd_id
 * @return          status
 */
int dump_reg_jesd_tx(uint32_t jesd_id)
{
    int b2h_flit_count,rv  = 0;
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_id];
    
    extern void * srp;
    uint32_t dev_id =0;
    uint32_t dev_flags = 0;
    
    srp_dev_open(dev_id, dev_flags, &srp);
    
    b2h_flit_count  = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_B2H_CSR_FLIT_CNT_OFFSET, "NSIP_HBI_B2H_CSR_FLIT_CNT");
    printf("Present value of NSIP_HBI_B2H_CSR_FLIT_CNT is 0x%x \n",b2h_flit_count);
    
    printf("dumping jesd b2h flit count\n");
    system("srpRead 0x06704014 1");
    
    printf("dumping jesd H2B flit count\n");
    system("srpRead 0x06704314 1");
    
	printf("reading mem_size\n");
    system("srpRead 0x06709280 1");
    
	printf("dumping Map Drop - NSIP_HBI_INTR_INT_STAT\n");
    system("srpRead 0x06704080  1");	
	 
    return rv;
}
/**
 * @brief           Function to dump RX VEX mem to check captured data
 * @param [in]      
 * @return          status
 */
int dump_vmem_vex_rx()
{
    int i = 0, rv;
    uint32_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;
    
    switch (num_of_streams)
    {
        case 0x10:
            //To VEX0 1st 8 streams
            printf("To VEX0 8 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x28800 64");
            printf("\n");
            system("srpRead 0x63.0.0x29000 64");
            printf("\n");
            system("srpRead 0x63.0.0x29800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2b000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2b800 64");
            printf("\n");
            
            //To VEX0 NEXT 8 streams
            printf("To VEX0 -NEXT 8 streams \n");
            system("srpRead 0x63.0.0x2c000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2c800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2d000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2d800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2e000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2e800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2f000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2f800 64");
            printf("\n");
            break;
        
        case 0x8:
            //To VEX0
            printf("To VEX0 8 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x28800 64");
            printf("\n");
            system("srpRead 0x63.0.0x29000 64");
            printf("\n");
            system("srpRead 0x63.0.0x29800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a800 64");
            printf("\n");
            system("srpRead 0x63.0.0x2b000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2b800 64");
            printf("\n");
            break;
        
        case 0x4:
            //To VEX0
            printf("To VEX0 4 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x28800 64");
            printf("\n");
            system("srpRead 0x63.0.0x29000 64");
            printf("\n");
            system("srpRead 0x63.0.0x29800 64");
            printf("\n");
            
            break;
        
        case 0x2:
            //To VEX0
            printf("To VEX0 2 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x28800 64");
            printf("\n");
            break;
        
        case 0x1:
            //To VEX0
            printf("To VEX0 1 stream\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            break; 
        default:
            //To VEX0
            printf("To VEX0 2 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            break;
    }
    
    return rv;
}       

/**
 * @brief           Function to dump TX VEX mem to check transmitted data
 * @param [in]      
 * @return          status
 */
int dump_vmem_vex_tx()
{
    int i = 0, rv;
    uint32_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;
    
    switch (num_of_streams)
    {
        case 0x10:
            //To VEX0 1st 8 streams
            printf("To VEX0 8 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2c000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2e000 64");
            printf("\n");
            system("srpRead 0x63.0.0x30000 64");
            printf("\n");
            system("srpRead 0x63.0.0x32000 64");
            printf("\n");
            system("srpRead 0x63.0.0x34000 64");
            printf("\n");
            system("srpRead 0x63.0.0x36000 64");
            printf("\n");
            
            //To VEX1 2dd 8 streams
            printf("To VEX1 8 streams\n");
            system("srpRead 0x63.1.0x28000 64");
            printf("\n");
            system("srpRead 0x63.1.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.1.0x2c000 64");
            printf("\n");
            system("srpRead 0x63.1.0x2e000 64");
            printf("\n");
            system("srpRead 0x63.1.0x30000 64");
            printf("\n");
            system("srpRead 0x63.1.0x32000 64");
            printf("\n");
            system("srpRead 0x63.1.0x34000 64");
            printf("\n");
            system("srpRead 0x63.1.0x36000 64");
            printf("\n");
            break;
        
        case 0x8:
            //To VEX0
            printf("To VEX0 8 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2c000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2e000 64");
            printf("\n");
            system("srpRead 0x63.0.0x30000 64");
            printf("\n");
            system("srpRead 0x63.0.0x32000 64");
            printf("\n");
            system("srpRead 0x63.0.0x34000 64");
            printf("\n");
            system("srpRead 0x63.0.0x36000 64");
            printf("\n");
            break;
        
        case 0x4:
            //To VEX0
            printf("To VEX0 4 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2c000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2e000 64");
            printf("\n");
            
            break;
        
        case 0x2:
            //To VEX0
            printf("To VEX0 2 streams\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            system("srpRead 0x63.0.0x2a000 64");
            printf("\n");
            break;
        
        case 0x1:
            //To VEX0
            printf("To VEX0 1 stream\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            break; 
            
        default:
            //To VEX0
            printf("To VEX0 1 stream\n");
            system("srpRead 0x63.0.0x28000 64");
            printf("\n");
            break;
    }
    
    return rv;
}

//dump jesd_rx_4k samples
static int dump_rx_ip_4k()
{
    uint32_t red_reg0 = 0, red_reg1 = 0, red_reg2 = 0, red_reg3 = 0, red_reg4 = 0, red_reg5 = 0, red_reg6 = 0, red_reg7 = 0, red_reg8 = 0, red_reg9 = 0, red_reg10 = 0, red_reg11 = 0;
    uint32_t red_reg12 = 0, red_reg13 = 0, red_reg14 = 0, red_reg15 = 0, red_reg16 = 0, red_reg17 = 0, red_reg18 = 0, red_reg19 = 0, red_reg20 = 0, red_reg21 = 0, red_reg22 = 0, red_reg23 = 0;
    uint32_t red_reg24 = 0, red_reg25 = 0, red_reg26 = 0, red_reg27 = 0, red_reg28 = 0, red_reg29 = 0, red_reg30 = 0, red_reg31 = 0, red_reg32 = 0, red_reg33 = 0,  red_reg34 = 0, red_reg35 = 0;
    uint32_t red_reg36 = 0, red_reg37 = 0, red_reg38 = 0, red_reg39 = 0, red_reg40 = 0, red_reg41 = 0, red_reg42 = 0, red_reg43 = 0, red_reg44 = 0, red_reg45 = 0, red_reg46 = 0, red_reg47 = 0;
    uint32_t red_reg48 = 0, red_reg49 = 0, red_reg50 = 0, red_reg51 = 0, red_reg52 = 0, red_reg53 = 0, red_reg54 = 0, red_reg55 = 0, red_reg56 = 0, red_reg57 = 0,  red_reg58 = 0, red_reg59 = 0;
    uint32_t red_reg60 = 0, red_reg61 = 0, red_reg62 = 0, red_reg63 = 0, red_reg64 = 0;
    uint32_t capture_clear = 0;
    uint32_t capture_status = 0;
    static int g_jesd_rx_glue_base_addr[4]      = {DLNK_JESD0_RX_GLUE_BASE, DLNK_JESD1_RX_GLUE_BASE, DLNK_JESD2_RX_GLUE_BASE, DLNK_JESD3_RX_GLUE_BASE};

    uint32_t count = 0;
    while(1)
    //while(count < 5)
    {
        //printf("####\n");
        capture_status = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_STS_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_STS");
        printf("\n\n####capture status is %x \n",capture_status);
        if(capture_status == 1)
        {
            red_reg0 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA0_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA0");
            red_reg1 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA1_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA1");
            red_reg2 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA2_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA2");
            red_reg3 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA3_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA3");
            red_reg4 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA4_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA4");
            red_reg5 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA5_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA5");
            red_reg6 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA6_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA6");
            red_reg7 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA7_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA7");
            red_reg8 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA8_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA8");
            red_reg9 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA9_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA9");
            red_reg10 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA10_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA10");
            red_reg11 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA11_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA11");
            red_reg12 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA12_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA12");
            red_reg13 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA13_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA13");
            red_reg14 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA14_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA14");
            red_reg15 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA15_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA15");
            red_reg16 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA16_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA16");
            red_reg17 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA17_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA17");
            red_reg18 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA18_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA18");
            red_reg19 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA19_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA19");
            red_reg20 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA20_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA20");
            red_reg21 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA21_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA21");
            red_reg22 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA22_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA22");
            red_reg23 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA23_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA23");
            red_reg24 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA24_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA24");
            red_reg25 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA25_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA25");
            red_reg26 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA26_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA26");
            red_reg27 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA27_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA27");
            red_reg28 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA28_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA28");
            red_reg29 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA29_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA29");
            red_reg30 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA30_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA30");
            red_reg31 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA31_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA31");
            red_reg32 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA32_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA32");
            red_reg33 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA33_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA33");
            red_reg34 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA34_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA34");
            red_reg35 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA35_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA35");
            red_reg36 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA36_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA36");
            red_reg37 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA37_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA37");
            red_reg38 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA38_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA38");
            red_reg39 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA39_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA39");
            red_reg40 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA40_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA40");
            red_reg41 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA41_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA41");
            red_reg42 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA42_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA42");
            red_reg43 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA43_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA43");
            red_reg44 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA44_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA44");
            red_reg45 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA45_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA45");
            red_reg46 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA46_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA46");
            red_reg47 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA47_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA47");
            red_reg48 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA48_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA48");
            red_reg49 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA49_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA49");
            red_reg50 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA50_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA50");
            red_reg51 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA51_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA51");
            red_reg52 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA52_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA52");
            red_reg53 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA53_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA53");
            red_reg54 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA54_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA54");
            red_reg55 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA55_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA55");
            red_reg56 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA56_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA56");
            red_reg57 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA57_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA57");
            red_reg58 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA58_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA58");
            red_reg59 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA59_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA59");
            red_reg60 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA60_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA60");
            red_reg61 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA61_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA61");
            red_reg62 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA62_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA62");
            red_reg63 = read_reg_18a(g_jesd_rx_glue_base_addr[0] + JESD_RX_GLUE_SMPL_INTF_CAP_DATA63_OFFSET, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA63");
            
            printf("jesd rx 4k reg is as follows\n");
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg0, red_reg1, red_reg2, red_reg3);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg4, red_reg5, red_reg6, red_reg7);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg8, red_reg9, red_reg10, red_reg11);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg12, red_reg13, red_reg14, red_reg15);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg16, red_reg17, red_reg18, red_reg19);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg20, red_reg21, red_reg22, red_reg23);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg24, red_reg25, red_reg26, red_reg27);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg28, red_reg29, red_reg30, red_reg31);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg32, red_reg33, red_reg34, red_reg35);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg36, red_reg37, red_reg38, red_reg39);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg40, red_reg41, red_reg42, red_reg43);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg44, red_reg45, red_reg46, red_reg47);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg48, red_reg49, red_reg50, red_reg51);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg52, red_reg53, red_reg54, red_reg55);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg56, red_reg57, red_reg58, red_reg59);
            printf("0x%x    0x%x    0x%x    0x%x    \n",red_reg60, red_reg61, red_reg62, red_reg63);
            
            write_read_expect_18a(g_jesd_rx_glue_base_addr[0]+JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_DEFAULT, 0x01, 0x01, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_WR_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_CLR");
            write_read_expect_18a(g_jesd_rx_glue_base_addr[0]+JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_DEFAULT, 0x00, 0x00, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_WR_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_CLR");
            
        }
        else
        {
            printf("status is still zero :\n");
        }
        count = count + 1;
    }
}

//for RSB capture mode
int rsb_capture_en(uint32_t rx_jesd_id)
{
    int jesd_crux_clk_csr_base = g_jesd_crux_clk_csr_base_addr[rx_jesd_id];

    write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_OFFSET,
                                        0x1,
                                        JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_WR_MASK,
                                        "JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN");
}

//for capturing 4k at Rx
int rx_smpl_intf_cap_en(uint32_t rx_jesd_id)
{
    int jesd_rx_glue_base = g_jesd_rx_glue_base_addr[rx_jesd_id];
    write_reg_18a(jesd_rx_glue_base + JESD_RX_GLUE_SMPL_INTF_CAP_EN_OFFSET,
                            0x1,
                            JESD_RX_GLUE_SMPL_INTF_CAP_EN_WR_MASK,
                            "JESD_RX_GLUE_SMPL_INTF_CAP_EN");
}

static int prefill_rsb_zeros()
{
    int i=0;
    uint32_t flit_count_pre = 0;
    int base_address_crux_clk_csr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};
    for(i=0; i<1; i++)
    {
        write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x01, 0x01, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
        printf("\n########Starting to prefil 512 flits of RSB to 0\n");
        for(flit_count_pre=0; flit_count_pre<512; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x00, 0x00, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
        printf("########Prefil of 512 flits of RSB to 0 done\n");
    }
}

static int prefill_rsb_const_data()
{
    int i=0;
    uint32_t flit_count_pre = 0;
    int base_address_crux_clk_csr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};
    for(i=0; i<1; i++)
    {
        printf("\n########Starting to prefil 512 flits of RSB to constant data with unique stream ID\n");
        for(flit_count_pre=0; flit_count_pre<64; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x00000001, 0x00000001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
    
        for(flit_count_pre=64; flit_count_pre<128; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x10021001, 0x10021001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=128; flit_count_pre<192; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x20022001, 0x20022001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=192; flit_count_pre<256; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x30023001, 0x30023001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=256; flit_count_pre<320; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x40024001, 0x40024001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=320; flit_count_pre<384; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x50025001, 0x50025001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=384; flit_count_pre<448; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x60026001, 0x60026001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        
        for(flit_count_pre=448; flit_count_pre<512; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, 0x70027001, 0x70027001, JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        printf("########Prefil of 512 flits of RSB to 0 done\n");
    }
}

static int prefill_rsb_uniq_data()
{
    int i=0;
    uint32_t flit_count_pre = 0;
    int flit_data_array[16];
    int flit_data = 0;
    int test = 0x0;
    uint32_t data_count = 0;
    int base_address_crux_clk_csr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};
    for(i=0; i<1; i++)
    {
        printf("\n########Starting to prefil 512 flits of RSB to unique data with unique stream ID\n");
        flit_data = 0;
        for(flit_count_pre=0; flit_count_pre<64; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %d\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
            
            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");
            
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
    
        flit_data = 0x00000000;
        test  = 0x1 << 28;
        flit_data = (flit_data | test);
        //printf("flit data is %x \n",flit_data);

        for(flit_count_pre=64; flit_count_pre<128; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x2 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=128; flit_count_pre<192; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x3 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=192; flit_count_pre<256; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x4 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=256; flit_count_pre<320; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x5 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=320; flit_count_pre<384; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x6 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=384; flit_count_pre<448; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }

        flit_data = 0x00000000;
        test  = 0x7 << 28;
        flit_data = (flit_data | test);
        for(flit_count_pre=448; flit_count_pre<512; flit_count_pre++)
        {
            //printf("flit count is %d\n",flit_count_pre);
            for(data_count = 0; data_count < 16; data_count++)
            {
                flit_data_array[data_count] = flit_data;
                //print("flit_data_array[%d] is %x\n",data_count, flit_data_array[data_count]);
                flit_data++;
            }

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");

            // 16 registers *32 bit = 512 bit data 
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[0], flit_data_array[0], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA0");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[1], flit_data_array[1], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA1");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[2], flit_data_array[2], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA2");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[3], flit_data_array[3], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA3");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[4], flit_data_array[4], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA4");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[5], flit_data_array[5], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA5");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[6], flit_data_array[6], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA6");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[7], flit_data_array[7], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA7");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[8], flit_data_array[8], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA8");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[9], flit_data_array[9], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA9");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[10], flit_data_array[10], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA10");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[11], flit_data_array[11], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA11");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[12], flit_data_array[12], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA12");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[13], flit_data_array[13], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA13");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[14], flit_data_array[14], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA14");
            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, flit_data_array[15], flit_data_array[15], JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_RSB_WR_DATA15");

            write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
        }
        printf("########Prefil of 512 flits of RSB to 0 done\n");
    }
}


//funtion to dump tsb
static int dump_tsb()
{    
    printf("\n#####TSB dump is enabled\n");
    //dump tsb buffer, roshan 21/02/24
    //===============================================================
    uint32_t stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer = 0;
    uint32_t value38, fill_level0, wr_addr, flit_count = 0;
    uint32_t stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer = 0;
    value38  = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_OFFSET, "JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT");
    printf("\n#######TSB buffer fill status register value is 0x%x \n", value38);
    fill_level0 = (value38 & 0x02);
    printf("#######JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT register's buffer full value is 0x%x \n", fill_level0);
    wr_addr = 0x0;

    if(value38 == 0)
    {
        printf("#######buffer is not full\n");
    }
    else
    {
        printf("###############buffer 0 is full\n");
        printf("###TSB buffer0 0-64 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count;
            printf("###flit count of buffer 0 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.1 64 to 128 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (1 << 6);
            printf("###flit count of buffer 0.1 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.2 128 to 192 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (2 << 6);
            printf("###flit count of buffer 0.2 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.3 192 to 256 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (3 << 6);
            printf("###flit count of buffer 0.3 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.4 256 to 320 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (4<<6);
            printf("###flit count of buffer 0.4 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.5 320 to 384 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (5<<6);
            printf("###flit count of buffer 0.5 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.6 384 to 448 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (6<<6);
            printf("###flit count of buffer 0.6 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.7 448 to 512 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (7<<6);
            printf("###flit count of buffer 0.7 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.8 512 to 576 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (8<<6);
            printf("###flit count of buffer 0.8 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.9 576 to 640 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (9<<6);
            printf("###flit count of buffer 0.9 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            //this register is not needed as per 0p8 tsb cap config, roshan 18/06/24
            //write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.10 640 to 704 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (10<<6);
            printf("###flit count of buffer 0.10 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.11 704 to 768 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (11<<6);
            printf("###flit count of buffer 0.11 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.12 768 to 832 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (12<<6);
            printf("###flit count of buffer 0.12 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.13 832 to 896 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (13<<6);
            printf("###flit count of buffer 0.13 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.14 896 to 960 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (14<<6);
            printf("###flit count of buffer 0.14 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer0.15 960 to 1024 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (15<<6);
            printf("###flit count of buffer 0.15 is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, wr_addr, wr_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RD_OFFSET, JESD_TX_GLUE_APB_RD_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_APB_RD_MASK, JESD_TX_GLUE_APB_RD_WR_MASK, "JESD_TX_GLUE_APB_RD");
            stream0_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA0_OFFSET, "JESD_TX_GLUE_APB_RDATA0");
            stream1_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA1_OFFSET, "JESD_TX_GLUE_APB_RDATA1");
            stream2_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA2_OFFSET, "JESD_TX_GLUE_APB_RDATA2");
            stream3_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA3_OFFSET, "JESD_TX_GLUE_APB_RDATA3");
            stream4_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA4_OFFSET, "JESD_TX_GLUE_APB_RDATA4");
            stream5_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA5_OFFSET, "JESD_TX_GLUE_APB_RDATA5");
            stream6_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA6_OFFSET, "JESD_TX_GLUE_APB_RDATA6");
            stream7_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA7_OFFSET, "JESD_TX_GLUE_APB_RDATA7");
            stream8_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA8_OFFSET, "JESD_TX_GLUE_APB_RDATA8");
            stream9_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA9_OFFSET, "JESD_TX_GLUE_APB_RDATA9");
            stream10_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA10_OFFSET, "JESD_TX_GLUE_APB_RDATA10");
            stream11_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA11_OFFSET, "JESD_TX_GLUE_APB_RDATA11");
            stream12_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA12_OFFSET, "JESD_TX_GLUE_APB_RDATA12");
            stream13_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA13_OFFSET, "JESD_TX_GLUE_APB_RDATA13");
            stream14_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA14_OFFSET, "JESD_TX_GLUE_APB_RDATA14");
            stream15_buffer = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_APB_RDATA15_OFFSET, "JESD_TX_GLUE_APB_RDATA15"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }
    }
}

//fuction to dump rsb
static int dump_rsb()
{
    //going to dump RSB 8 streams
    uint32_t fill_level_0 = 0;
    uint32_t fill_level_1 = 0;
    uint32_t fill_level_2 = 0;
    uint32_t fill_level_3 = 0;
    uint32_t fill_level_4 = 0;
    uint32_t fill_level_5 = 0;
    uint32_t fill_level_6 = 0;
    uint32_t fill_level_7 = 0;
    int i = 0;
    int flit_count = 0;
    uint32_t value38=0; uint32_t value39=0; uint32_t value40=0; uint32_t value41=0; uint32_t value42=0; uint32_t value43=0; uint32_t value44=0; uint32_t value45=0;
    uint32_t stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer = 0;
    uint32_t stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer = 0;
    int base_address_crux_clk_csr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};

    delay(2000);
    for(i=0; i<1; i++)
    {
        value38 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS0_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS0");
        value39 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS1_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS1");
        value40 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS2_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS2");
        value41 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS3_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS3");
        value42 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS4_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS4");
        value43 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS5_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS5");
        value44 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS6_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS6");
        value45 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS7_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS7");
    }
    
    fill_level_0 = ((value38 & 0x400) >> 10);
    fill_level_1 = ((value39 & 0x400) >> 10);
    fill_level_2 = ((value40 & 0x400) >> 10);
    fill_level_3 = ((value41 & 0x400) >> 10);
    fill_level_4 = ((value42 & 0x400) >> 10);
    fill_level_5 = ((value43 & 0x400) >> 10);
    fill_level_6 = ((value44 & 0x400) >> 10);
    fill_level_7 = ((value45 & 0x400) >> 10);
        
    //stream0 buffer0
    if(fill_level_0 ==1)
    {
        printf("\n###buffer 0 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 0-63 flits of stream 0 are \n");
            //for(flit_count=0; flit_count<64; flit_count++)
            for(flit_count=0; flit_count<4; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 0 is not full \n");
    }
    
    //stream1 buffer1
    if(fill_level_1 ==1)
    {
        printf("\n###buffer 1 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 64-128 flits of stream 1 are \n");
            //for(flit_count=64; flit_count<128; flit_count++)
            for(flit_count=64; flit_count<68; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 1 is not full \n");
    }
    
    //stream2 buffer2
    if(fill_level_2 ==1)
    {
        printf("\n###buffer 2 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 128-191 flits of stream 2 are \n");
            //for(flit_count=128; flit_count<192; flit_count++)
            for(flit_count=128; flit_count<132; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 2 is not full \n");
    }
    
    //stream3 buffer3
    if(fill_level_3 ==1)
    {
        printf("\n###buffer 3 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 192-255 flits of stream 3 are \n");
            //for(flit_count=192; flit_count<256; flit_count++)
            for(flit_count=192; flit_count<196; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 3 is not full \n");
    }
    
    //stream4 buffer4
    if(fill_level_4 ==1)
    {
        printf("\n###buffer 4 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 256-319 flits of stream 4 are \n");
            //for(flit_count=256; flit_count<320; flit_count++)
            for(flit_count=256; flit_count<260; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 4 is not full \n");
    }
    
    //stream5 buffer5
    if(fill_level_5 ==1)
    {
        printf("\n###buffer 5 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 320-383 flits of stream 5 are \n");
            //for(flit_count=320; flit_count<384; flit_count++)
            for(flit_count=320; flit_count<324; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 5 is not full \n");
    }
    
    //stream6 buffer6
    if(fill_level_6 ==1)
    {
        printf("\n###buffer 6 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 384-447 flits of stream 6 are \n");
            //for(flit_count=384; flit_count<448; flit_count++)
            for(flit_count=384; flit_count<388; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 6 is not full \n");
    }
    
    //stream7 buffer7
    if(fill_level_7 ==1)
    {
        printf("\n###buffer 7 is full \n");
        i=0;
        for(i=0; i<1; i++)
        {
            printf("###RSB 448-511 flits of stream 7 are \n");
            //for(flit_count=448; flit_count<512; flit_count++)
            for(flit_count=448; flit_count<452; flit_count++)
            {
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR");
                write_read_expect_18a(base_address_crux_clk_csr[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR");
                stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0");
                stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1");
                stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2");
                stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3");
                stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4");
                stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5");
                stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6");
                stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7");
                stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8");
                stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9");
                stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10");
                stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11");
                stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12");
                stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13");
                stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14");
                stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15");
                printf("flit count is %d \n",flit_count);
                printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
            }
        }
    }
    else
    {
        printf("###buffer 7 is not full \n");
    }
    
}

/**
 * @brief           Function configuring JESD: As per flow id selected
 * @param [in]      flow_id
 * @return          status
 */
int configure_jesd_flow(uint32_t flow_id)
{
    //Select Test flow
    switch (flow_id)
    {
        case flow_rx_dnrt_to_vex:

                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);

                    // Config STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    // End of the test - reg dump rx
                    dump_reg_jesd_rx(jesd_tc_config.jesd_id);

                    // Dump the captured data at rx_vex 
                    dump_vmem_vex_rx();
                    
                    break;
        
        case flow_tx_vex_to_dnrt:
        
                    // Config CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);

                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_b2h(jesd_tc_config.jesd_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);
                    
                    //TSB capture mode is enabled
                    //printf("\ntsb capture is enabled\n");
                    //write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");
                   
                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    
                    // Config Vex Tx and start Vex
                    configure_vex_tx(jesd_tc_config.vex_id);
                    
                    // End of the test - reg dump tx
                    //dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_tx();
                    
                    //enable capture freeze
                    //dump tsb
                    //dump_tsb();
                    break;
        
        case flow_lpbk_glue:

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);
                  
                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);
                    
                    // Config JESD Loopback ctrl regsiter 
                    configure_jesd_lpbk(jesd_tc_config.jesd_id,jesd_tc_config.flow_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    break;

        case flow_lpbk_nsip:
        
                    // Configure CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    
                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(((jesd_tc_config.vex_id)+ 0x1)); // rx vex 1 
                    
                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
              
                    configure_jesd_b2h(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,((jesd_tc_config.vex_id)+ 0x1));

                    // Config JESD Loopback ctrl regsiter 
                    configure_jesd_lpbk(jesd_tc_config.jesd_id,jesd_tc_config.flow_id);

                    // Config Vex Tx and start Vex
                    configure_vex_tx(jesd_tc_config.vex_id);
                    
                    // End of the test - reg dump tx
                    dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_tx();
                    
                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_rx();

                    break;
        
        case flow_lpbk_ip:

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);
                    
                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);
                    
                    // Config JESD Loopback ctrl regsiter 
                    configure_jesd_lpbk(jesd_tc_config.jesd_id,jesd_tc_config.flow_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    
                    break;
                    
        case flow_rsb_capt:
        
                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);                    

                    prefill_rsb_zeros();
                    
                    rsb_capture_en(jesd_tc_config.jesd_id);
                    
                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    
                    dump_rsb();
                    break;

        case flow_rx_ip_4k_capture:
                    
                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Tx path - as per UC
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);      
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);                    

                    rx_smpl_intf_cap_en(jesd_tc_config.jesd_id);
                    
                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    
                    dump_rx_ip_4k();
                    break;
        
        case flow_rx_rsb_src_mode:
                    // Config JESD NSIP - as per UC
                    printf("hello from roshan \n");
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);

                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    //configure_jesd_rx_ip(jesd_tc_config.jesd_id);                         //roshan 10/06/24

                    // Enable jesd
                    //configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, 0x800, 0x800, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR");
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
                    delay(100);
                    
                    //prefill rsb with constant data of '5'
                    prefill_rsb_const_data();
                    delay(100);
                    
                    //dump rsb prefilled data,
                    dump_rsb();

                /*  //for debug
                    uint32_t h2b_flit_count = 0;
                    uint32_t rx_strm_data0 =0;
                    uint32_t rx_strm_data1 =0;
                    uint32_t rx_strm_data2 =0;
                    uint32_t rx_strm_data3 =0;
                    h2b_flit_count = read_reg_18a(g_jesd_nsip_base_addr[0] + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "JESD0_nsip_hbi_h2b_flit_cnt");
                    printf("\n########## h2b flit count before rsb source start is %x \n",h2b_flit_count);
                    
                    //reading rx sent flit to nsip
                    rx_strm_data0 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0");
                    rx_strm_data1 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1");
                    rx_strm_data2 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2");
                    rx_strm_data3 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3");
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0 is %x \n",rx_strm_data0);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1 is %x \n",rx_strm_data1);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2 is %x \n",rx_strm_data2);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data3);
                    delay(1000);
                */
                    //start rsb streaming
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START");
                    delay(100);

                /*  //for debug
                    h2b_flit_count = read_reg_18a(g_jesd_nsip_base_addr[0] + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "JESD0_nsip_hbi_h2b_flit_cnt");
                    printf("\n########## h2b flit count after rsb source start is %x \n",h2b_flit_count);
                    rx_strm_data0 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0");
                    rx_strm_data1 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1");
                    rx_strm_data2 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2");
                    rx_strm_data3 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3");
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0 is %x \n",rx_strm_data0);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1 is %x \n",rx_strm_data1);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2 is %x \n",rx_strm_data2);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data3);
                    delay(3000);
                */    
                    // Dump the captured data at rx_vex                    
                    dump_vmem_vex_rx();
                    
					break;

        case flow_tx_tsb_cap_mode:

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);
            
                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    //commenting out rx ip code as not need for rsb source mode, roshan 13/06/24
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);
                    
                    // Configure JESD Loopback ctrl regsiter 
                    //configure_jesd_lpbk(jesd_tc_config.jesd_id,jesd_tc_config.flow_id);
                    write_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET, 0x2, JESD_CRUX_CLK_CSR_LPBK_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_LPBK_CTL");
                    print("Glue lpbk enabled:\n");
                    
                    //TSB capture mode is enabled
                    printf("\ntsb capture is enabled\n");
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");
                    
                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                  
                    //adding rsb src mode configure code,
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, 0x800, 0x800, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR");
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x3, 0x3, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
                    delay(100);
                    
                    //prefill rsb with constant data of '5'
                    prefill_rsb_const_data();
                    delay(100);
                    
                    //dump rsb prefilled data,
                    dump_rsb();

                /*  //for debug
                    h2b_flit_count = 0;
                    rx_strm_data0 =0;
                    rx_strm_data1 =0;
                    rx_strm_data2 =0;
                    rx_strm_data3 =0;
                    h2b_flit_count = read_reg_18a(g_jesd_nsip_base_addr[0] + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "JESD0_nsip_hbi_h2b_flit_cnt");
                    printf("\n########## h2b flit count before rsb source start is %x \n",h2b_flit_count);
                    
                    //reading rx sent flit to nsip
                    rx_strm_data0 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0");
                    rx_strm_data1 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1");
                    rx_strm_data2 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2");
                    rx_strm_data3 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3");
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0 is %x \n",rx_strm_data0);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1 is %x \n",rx_strm_data1);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2 is %x \n",rx_strm_data2);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data3);
                    delay(1000);
                */

                    //start rsb streaming
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START");
                    delay(100);

                /*  //for debug
                    h2b_flit_count = read_reg_18a(g_jesd_nsip_base_addr[0] + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "JESD0_nsip_hbi_h2b_flit_cnt");
                    printf("\n########## h2b flit count after rsb source start is %x \n",h2b_flit_count);
                    rx_strm_data0 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0");
                    rx_strm_data1 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1");
                    rx_strm_data2 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2");
                    rx_strm_data3 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3");
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0 is %x \n",rx_strm_data0);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1 is %x \n",rx_strm_data1);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2 is %x \n",rx_strm_data2);
                    printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data3);
                    delay(100);
                */

                    //######adding tsb capture code
                    //enable capture freeze
                    //dump tsb
                    dump_tsb();
                    break;
    }
}
/**
 * @brief           Function configuring JESD: As per testcase selected
 * @param [in]      flow_id
 * @return          status
 */ 
int configure_jesd(uint32_t testcase)
{
    printf("INFO : Configure JESD \n");
    memset(&jesd_config, 0, sizeof(jesd_config));
    //memset(&vex_strm2cio_config, 0, sizeof(vex_strm2cio_config));
    
    // Assign default values to JESD Testcase config and Jesd config structures 
    printf("INFO : Assign defaults to jesd_config struct\n");
    assign_defaults();
    
    // Parse from command line - JESD Testcase config -as per TC
    printf("INFO : update/fill/assign jesd_tc_config struct as per TC\n");
    assign_tc_config(jesd_tc_config_arr, testcase);
    
    // Configure jesd config struct as per UC
    printf("INFO: update/fill/assign jesd_config struct as per UC\n");
    assign_jesd_config(jesd_config_arr, jesd_tc_config.usecase_id);

    //Initialize Test - fpga clk, fpga provided sysref for jesd, reset cycle for jesd,vex,other SS, clearing vex/jesd mem
    printf("INFO : Initialize Jesd%d\n", jesd_tc_config.jesd_id);
    init_jesd(jesd_tc_config.jesd_id, jesd_config.jesd_link_config.serdes_rate, jesd_config.jesd_link_config.smpl_char_clk_ratio);
    
    printf("INFO: Initialize Vex%d\n", jesd_tc_config.vex_id);
    init_vex(jesd_tc_config.vex_id);
    
    //Configure jesd TC as per flow selected
    configure_jesd_flow (jesd_tc_config.flow_id);
}   
