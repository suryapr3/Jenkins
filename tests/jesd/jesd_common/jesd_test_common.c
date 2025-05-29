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

#ifndef E2E_FLOW_EN
#include "defines.h"
#endif //!E2E_FLOW_EN

// #define STRM_16_SUPPORT_PER_VEX (1)
#define OFFSET_20000 (1)
#define TX_BUFFER_SIZE_BYTE  (0x10000) //64k
#define TEST_BLOCK_COUNT (10) //(1024)

#define SAMPLES_PER_FLIT (16)
// #define SAMPLES_PER_VECTOR (32)
#define SAMPLE_SIZE_BYTE (4)
#define MAX_VECTOR_COUNT (128) // for 8gsps

#define MIN_VEC_PER_BLOCK 1

#define PAYLOAD_SIZE_SAMPLES_PER_STREAM (256)
#define MAX_VMEM_SAMPLE_DUMP_COUNT  (1024)

#define VEX_PATTERN_FILE "IQ_4K_SAMPLES.txt"

// #if PAYLOAD_SIZE_SAMPLES_PER_STREAM == 128
// #define VEX_PATTERN_FILE "save_payload_stream_0.txt"
// #elif PAYLOAD_SIZE_SAMPLES_PER_STREAM == 256
// #define VEX_PATTERN_FILE "vex_patterns_256_samples.txt"
// #endif
/***********************************************

 * LOCAL/PRIVATE MACROS AND DEFINES            *

 ***********************************************/
// VEX-RX related decs and defs below

#define NSIP_HBI_INT_CSR_INT_VALUE 0xFFF
#define FIFO_CONTROL_VALUE 0x00000184
#define CREDIT_CS_VALUE 0x3

#define STRM2CIO_INT_ENABLE_VALUE 0xF
#define STRM2CIO_FIFO_STATUS_CTL_VALUE 0x00000001
#define STRM2CIO_WORD_CNT_CTL_VALUE 0x00000001

// common definition ref: vha_common_definitions.h // todo : rename and move to jesd_common
#define NUM_VE_PER_VHA (10)

//define how many flits of TSB should be dumped
#define MAX_FLIT_COUNT_TO_FILL 4

#define NUMBER_OF_VECTORS_INPUT (4) // for 512 bytes
// #define NUMBER_OF_VECTORS_INPUT (8) // for 1kb
// #define NUMBER_OF_VECTORS_INPUT (16) // for 2kb

// #define NUM_OF_ELEMENTS_PER_VEC (32)
// #define NUM_OF_ELEMENTS_PER_VEC (32)

#define VEX_MAX_BUF_SIZE (256) // in vectors and it should be power of 2
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))

// #define WAIT_COUNT (256 * 100) // (128)
// #define WAIT_COUNT (256 * 128) // (128)

#define WAIT_COUNT (128) //(256 * 128) // (128)

#ifndef E2E_FLOW_EN

uint32_t g_max_blocks = TEST_BLOCK_COUNT; // 1;


const int g_vectors_per_block[2][6] = // for .5 us  window/block
    {
        {4 /*p25 gsps*/, 8 /*p5*/, 16 /*1*/, 32 /*2*/, 64 /*4*/, 128 /*8*/},  // 1G device clock based rate's block size
        {3 /*p187*/, 6 /*p375*/, 12 /*75*/, 24 /*1.5*/, 48 /*3*/, 96 /*6*/}}; // 1.5G device clock based rate's block size
#endif // !E2E_FLOW_EN

const int g_flits_per_block[2][6] = // for .5 us  window/block
    {
        {8 /*p25 gsps*/, 16 /*p5*/, 32 /*1*/, 64 /*2*/, 128 /*4*/, 256 /*8*/},  // 1G device clock based rate's block size
        {6 /*p187*/, 12 /*p375*/, 24 /*75*/, 48 /*1.5*/, 96 /*3*/, 192 /*6*/}}; // 1.5G device clock based rate's block size

const int g_samples_per_block[2][6] = // for .5 us  window/block
    { 
        {128 /*p25 gsps*/, 256 /*p5*/, 512 /*1*/, 1024 /*2*/, 2048 /*4*/, 4096 /*8*/},  // 1G device clock based rate's block size
        {96 /*p187*/, 192 /*p375*/, 384 /*75*/, 768 /*1.5*/, 1536 /*3*/, 3072 /*6*/}}; // 1.5G device clock based rate's block size


// VEX-RX related decs and defs above


/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
// Array of Struct to hold TC config    : Refer TC config
struct jesd_tc_config_t jesd_tc_config_arr[] = 
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

    //RSB source mode to vex- 5c
    {TC_40, UC_5C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //tsb capture mode
    {TC_41, UC_5C, flow_tx_tsb_cap_mode, vex_0, jesd_0},

    //Glue level lpbk 9a 
    {TC_42, UC_9A, flow_lpbk_glue, vex_0, jesd_0},

    // e2e flow
    {TC_43, UC_5C, flow_e2e, vex_0, jesd_0},

    //RSB source mode to vex- 7c
    {TC_44, UC_7C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 3a
    {TC_45, UC_3A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 3b
    {TC_46, UC_3B, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 3d
    {TC_47, UC_3D, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 2c
    {TC_48, UC_2C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 2b
    {TC_49, UC_2B, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 11a
    {TC_50, UC_11A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 9b
    {TC_51, UC_9B, flow_rx_rsb_src_mode, vex_0, jesd_0},

    // JESD_Tx to JESD_Rx lpbk - 5c
    {TC_52, UC_5C, flow_lpbk_jesdTx_jesdRx, vex_0, jesd_0},

    // JESD_Tx to JESD_Rx lpbk - 5e
    {TC_53, UC_5E, flow_lpbk_jesdTx_jesdRx, vex_0, jesd_0},

    // loopback at vex rx to tx - 5C
    {TC_54, UC_5C, flow_vex_loopback, vex_0, jesd_0},

    // loopback at vex rx to tx - 7C
    {TC_55, UC_7C, flow_vex_loopback, vex_0, jesd_0},
    
    //tsb capture mode
    {TC_56, UC_3D, flow_tx_tsb_cap_mode, vex_0, jesd_0},
    
    //DNRT to RSB capture, 32g, 5e
    {TC_57, UC_5E, flow_rsb_capt, vex_0, jesd_0},
    
    //TC58 - TC59 TX 32G 1 stream usecseas
    {TC_58, UC_11A, flow_tx_vex_to_dnrt, vex_0, jesd_0},
    {TC_59, UC_13A, flow_tx_vex_to_dnrt, vex_0, jesd_0},
        
   //TC60 TX 32G 2 stream usecseas
    {TC_60, UC_11C, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //tx_ip_4k_capture
    {TC_61, UC_11A, flow_tx_ip_4k_capture, vex_0, jesd_0},
        
    //tsb capture mode
    {TC_62, UC_11A, flow_vex_tx_tsb_cap_mode, vex_0, jesd_0},

    //TSB source mode to DNRT Rx - 11a
    {TC_63, UC_11A, flow_tsb_src_dnrt, vex_0, jesd_0},

    
   //TC64 RX 16G 4 stream usecseas
   // loopback at vex rx to tx - 3A
    {TC_64, UC_3A, flow_vex_loopback, vex_0, jesd_0},

   //TC65 - TC66 RX 16G 8 stream usecseas
    // loopback at vex rx to tx - 3B
    {TC_65, UC_3B, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 2B
    {TC_66, UC_2B, flow_vex_loopback, vex_0, jesd_0},
    
   //TC67 - TC68 RX 16G 16 stream usecseas
    // loopback at vex rx to tx - 3D
    {TC_67, UC_3D, flow_vex_loopback, vex_0, jesd_0},

    // loopback at vex rx to tx - 2C
    {TC_68, UC_2C, flow_vex_loopback, vex_0, jesd_0},
   
   //TC69 - TC71 RX 32G 1 stream usecseas
    // loopback at vex rx to tx - 9A
    {TC_69, UC_9A, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 11A
    {TC_70, UC_11A, flow_vex_loopback, vex_0, jesd_0},

    // loopback at vex rx to tx - 13A
    {TC_71, UC_13A, flow_vex_loopback, vex_0, jesd_0},
   
   //TC72 - TC74 RX 32G 2 stream usecseas
    // loopback at vex rx to tx - 7B
    {TC_72, UC_7B, flow_vex_loopback, vex_0, jesd_0},

    // loopback at vex rx to tx - 9B
    {TC_73, UC_9B, flow_vex_loopback, vex_0, jesd_0},

    // loopback at vex rx to tx - 11C
    {TC_74, UC_11C, flow_vex_loopback, vex_0, jesd_0},

   //TC75 - TC77 RX 32G 4 stream usecseas
    // loopback at vex rx to tx - 5B
    {TC_75, UC_5B, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 7E
    {TC_76, UC_7E, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 9C
    {TC_77, UC_9C, flow_vex_loopback, vex_0, jesd_0},

   //TC78 - TC80 RX 32G 8 stream usecseas
    // loopback at vex rx to tx - 5E
    {TC_78, UC_5E, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 3C
    {TC_79, UC_3C, flow_vex_loopback, vex_0, jesd_0},
    
    // loopback at vex rx to tx - 7G
    {TC_80, UC_7G, flow_vex_loopback, vex_0, jesd_0},
    
   //TC81 - TC82 RX 32G 16 stream usecseas
    // loopback at vex rx to tx - 3E
    {TC_81, UC_3E, flow_vex_loopback, vex_0, jesd_0},
        
    // loopback at vex rx to tx - 5F
    {TC_82, UC_5F, flow_vex_loopback, vex_0, jesd_0},

    // vex rx to dnrt - 3d
    {TC_83, UC_3D, flow_tx_vex_to_dnrt, vex_0, jesd_0},

    //tsb capture mode
    {TC_84, UC_3D, flow_vex_tx_tsb_cap_mode, vex_0, jesd_0},

    //RSB source mode to vex- 13a
    {TC_85, UC_13A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //DNRT to vex, rx path usecase 6a, 24g
    {TC_86, UC_6A, flow_rx_dnrt_to_vex, vex_0, jesd_0},

    //RSB source mode to vex- 6a, 24g
    {TC_87, UC_6A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB source mode to vex- 11c, 32g, 2 streams
    {TC_88, UC_11C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //DNRT to RSB capture
    {TC_89, UC_6A, flow_rsb_capt, vex_0, jesd_0},

    // JESD_Tx to JESD_Rx lpbk - 6a, 24g, 1.5g
    {TC_90, UC_6A, flow_lpbk_jesdTx_jesdRx, vex_0, jesd_0},

    //TSB source mode to RSB capture, 24g, 1.5g, 6a
    {TC_91, UC_6A, flow_tsb_src_rsb, vex_0, jesd_0},

    //TSB source mode to DNRT Rx - 06a
    {TC_92, UC_6A, flow_tsb_src_dnrt, vex_0, jesd_0},  //tsb to dnrt

    //tx_ip_4k_capture, TSB to Tx ip 4k capture, 24g, 1.5g, 6a
    {TC_93, UC_6A, flow_tsb_src_tx_ip_4k_capture, vex_0, jesd_0},  //tsb to tx ip4k capture

    //tx_ip_4k_capture, vex to Tx ip 4k capture, 24g, 1.5g, 6a
    {TC_94, UC_6A, flow_tx_ip_4k_capture, vex_0, jesd_0},  //vex to tx ip4k capture

    //vex to dnrt - 24g, 1.5g, 6a
    {TC_95, UC_6A, flow_tx_vex_to_dnrt, vex_0, jesd_0},

     //TSB source mode to RSB capt (Tx - Rx lpbk) - 11a, 32g
    {TC_96, UC_11A, flow_tsb_src_rsb, vex_0, jesd_0},

    //TSB source mode to RSB capt (Tx - Rx lpbk) - 11a, 32g
    {TC_97, UC_7E, flow_tsb_src_rsb, vex_0, jesd_0},

    //tx_ip_4k_capture, TSB to Tx ip 4k capture, 24g, 1.5g, 6a
    {TC_98, UC_11A, flow_tsb_src_tx_ip_4k_capture, vex_0, jesd_0},  //tsb to tx ip4k capture

    //TSB source mode to RSB capture, 16g, 3a
    {TC_99, UC_3A, flow_tsb_src_rsb, vex_0, jesd_0}, 

    //TSB source mode to RSB capture, 16g, 5c
    {TC_100, UC_5C, flow_tsb_src_rsb, vex_0, jesd_0},

    //DNRT to RSB, 24g,1.5G,5a
    {TC_101, UC_5A, flow_rsb_capt, vex_0, jesd_0},

    //TSB source mode to RSB capture, 24g, 1.5g 5a
    {TC_102, UC_5A, flow_tsb_src_rsb, vex_0, jesd_0},

    //TSB source mode to DNRT capture, 24g, 1.5g 5a
    {TC_103, UC_5A, flow_tsb_src_dnrt, vex_0, jesd_0},

    //tx to rx lpbk, vex to rsb capture, 16g, 1g 3a
    {TC_104, UC_3A, flow_lpbk_jesdTx_jesdRx, vex_0, jesd_0},

    //RSB to vex capture, 24g, 6c
    {TC_105, UC_6C, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB to vex capture, 24g, 8a, 1 lane,
    {TC_106, UC_8A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //RSB to vex capture, 8g, 1a
    {TC_107, UC_1A, flow_rx_rsb_src_mode, vex_0, jesd_0},

    //DNRT to RSB capture
    {TC_108, UC_1A, flow_rsb_capt, vex_0, jesd_0},

    //jesd_tx to jesd_rx lpbk, vex to rsb capture, check 8g implementation in vex.
    {TC_109, UC_1A, flow_lpbk_jesdTx_jesdRx, vex_0, jesd_0},

    //TSB source mode to RSB capture, 8g, 1.5g 1a
    {TC_110, UC_1A, flow_tsb_src_rsb, vex_0, jesd_0},

    //DNRT to RSB capture, 24g, 1.5g, 4 lane,
    {TC_111, UC_6C, flow_rsb_capt, vex_0, jesd_0},

    //DNRT to DNRT glue lpbk, 24g, 1.5g, 6a
    {TC_112, UC_6A, flow_lpbk_glue, vex_0, jesd_0},

    //TSB source mode to DNRT capture, 8g, 1a
    {TC_113, UC_1A, flow_tsb_src_dnrt, vex_0, jesd_0},

    //tx_ip_4k_capture, TSB to Tx ip 4k capture, 8g,1a
    {TC_114, UC_1A, flow_tsb_src_tx_ip_4k_capture, vex_0, jesd_0},  //tsb to tx ip4k capture

    //vex to tsb capture mode
    {TC_115, UC_5C, flow_vex_tx_tsb_cap_mode, vex_0, jesd_0},

    //tx_ip_4k_capture
    {TC_116, UC_5C, flow_tx_ip_4k_capture, vex_0, jesd_0},

    //tx_ip_4k_capture, TSB to Tx ip 4k capture, 16g, 1g, 5c
    {TC_117, UC_5C, flow_tsb_src_tx_ip_4k_capture, vex_0, jesd_0},  //tsb to tx ip4k capture
};

// Array of Struct to hold link config  : Refer UC config
struct jesd_config_t jesd_config_arr[] =
{
    /* jesd_config
    arr[i]={
        jesd_link_config ->         {usecase_id, Sample rate, L, M, F, S, N', JESD04C/D, Serdes rate, E, Soni, clk ratio, smpl_trans_pos, smpl_trans_neg, link_iq_bw},
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
        {UC_3A, sample_rate_122P88, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_0P5},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable }, enable, enable },
        {0x00000018, 0x00000013, 0x001f007f, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000101, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_7C -> arr[1]
    {
        //cmn
        {UC_7C, sample_rate_491P52, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_2_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {  {disable, disable, err_thresh_4, err_thresh_4, disable }, enable, enable },
        {0x00000014, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000009, 0x00000000, disable},enable,enable},
        {0x00000014, 0x00000001, 0x00010001, 0x00000001, 0x00010001, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0xf}
    },


    /* jesd_config
    arr[i]={
        jesd_link_config ->         {usecase_id, Sample rate, L, M, F, S, N', JESD04C/D, Serdes rate, E, Soni, clk ratio, smpl_trans_pos, smpl_trans_neg, link_iq_bw},
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

    //TC2-TC4 - RX 16G 8 stream usecseas
    //UC_5C -> arr[2]
    {
        //cmn
        {UC_5C, sample_rate_245P76, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000018, 0x0000000f, 0x001f007f, 0x0000000f, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x000f007f, 0x0000001b, 0x000f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000000, 0x00000000, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_2B -> arr[3]
    {
        //cmn
        {UC_2B, sample_rate_61P44, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_3, e_LINK_IQ_BW_GSPS_0P5},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000018, 0x00000013, 0x001f007f, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000301, disable},enable,enable},
        {0x00000018, 0x00000017, 0x00170023, 0x00000017, 0x00170023, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, enable, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_3B -> arr[4]
    {
        //cmn
        {UC_3B, sample_rate_122P88, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000018, 0x00000013, 0x001f007f, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },
    
    //TC5-TC6 - RX 16G 16 stream usecseas
    //UC_2C -> arr[5]
    {
        //cmn
        {UC_2C, sample_rate_61P44, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_3, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {  {disable, disable, err_thresh_2, err_thresh_2, disable }, enable, enable },
        {0x00000018, 0x00000013, 0x001f007f, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
            {0x00000184, 0x8},

            // tx
            {{disable, disable, 0x00000010, 0x00000000, disable}, enable, enable},
            {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
            {0x00000180, 0x00000003, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
            {0x00000184, 0xf}
    },

    //UC_3D -> arr[6]
    {
       //cmn 
        {UC_3D, sample_rate_122P88, l_4, m_32, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

       //rx
        {  {disable, disable, err_thresh_2, err_thresh_2, disable }, enable, enable },
        {0x00000018, 0x00000013, 0x001f007f, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
            {0x00000184, 0x8},
            // tx
            {{disable, disable, 0x0000000c, 0x00000000, disable}, enable, enable},
            {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
            {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
            {0x00000184, 0xf}
            //jesd_tx_ip_config_t->       {{crc3_enable, crc12_enable, tx_tl_latency, tx_smpl_req, cmd_enable},jesd_ip_enable,jesd_rx_ip_sysref_enable}
            // jesd_tx_cmn_csr_config_t->  {tx_ip_clk_ctrl, tx_sysref_tsad, tx_sync_point_ctrl, tx_bfn_sysref_tsad, tx_bfn_sync_point_ctrl, tx_clk_1p5g_div_en, tx_clk_gen, tx_sync_point_cnt_en, tx_bfn_sync_point_cnt_en},
            // jesd_tx_glue_config_t->     {tx_conv_dp_cfg, tx_srg_pat_cfg_low, tx_srg_pat_period_cfg, tx_srg_pat_del_cfg, tx_min_max_occupn_cp_en, tx_dp_gate_sel, tx_strm_phm_en, tx_srg_pat_en},
            // jesd_b2h_config_t->         {b2h_fifo_ctrl,b2h_credit_ready},
        },
    
    //RX 32G usecases TC_7-TC_20(1 stream; 2 streams; 4 streams ; 8 streams ;16 streams)
    //TC7-TC9 - RX 32G 1 stream usecseas
    //UC_9A -> arr[7]
    {
        //cmn
        {UC_9A, sample_rate_983P04, l_1, m_2, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_2_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},
    
        //0p8
        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000000, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000009, 0x00000000, disable},enable,enable},
        {0x00000000, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        //{0x00000180, 0x00000000, 0x00000001, disable},  //Before automating new regs of 0p8
        {0x00000184, 0xf}

        /*
                 //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000018, 0x0000001b, 0x001f007f, 0x0000001b, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
        */
    },

    //UC_11A -> arr[8]
    {
        //cmn
        {UC_11A, sample_rate_1966P08, l_2, m_2, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000a, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000f, 0x000f007f, 0x0000000f, 0x000f007f, enable, enable, enable, enable},
        {0x00000122, 0x00000003, 0x00000001, 0x00000000, 0x00000007, 0x00000001, disable, enable}, //changing tx glue dp sel - s/w triggers -tsb src 
        {0x00000184, 0xf}
    },

    //UC_13A -> arr[9]
    {
        //cmn
        {UC_13A, sample_rate_3932P16, l_4, m_2, f_1, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_2_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_4P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable }, enable, enable },
        {0x00000000, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000006, 0x00000000, disable},enable,enable},
        {0x00000000, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000122, 0x00000003, 0x00000001, 0x00000000, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //TC10-TC12 - RX 32G 2 stream usecseas
    //UC_7B -> arr[10]
    {
        //cmn
        {UC_7B, sample_rate_491P52, l_1, m_4, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_9B -> arr[11]
    {
        //cmn
        {UC_9B, sample_rate_983P04, l_2, m_4, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_2, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x000d007f, 0x0000000d, 0x000d007f, enable, enable, enable, enable},
        {0x00000141, 0x0000000f, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_11C -> arr[12]
    {
        //cmn
        {UC_11C, sample_rate_1966P08, l_4, m_4, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_4P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

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
        {UC_5B, sample_rate_245P76, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_7E -> arr[14]
    {
        //cmn
        {UC_7E, sample_rate_491P52, l_2, m_8, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000001, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_9C -> arr[15]
    {
        //cmn
        {UC_9C, sample_rate_983P04, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_2, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_4P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000141, 0x0000000f, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}

    },
    
    //TC16-TC18 - RX 32G 8 stream usecseas
    //UC_5E -> arr[16]
    {
        //cmn
        {UC_5E, sample_rate_245P76, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000003, 0x00000002, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //UC_3C -> arr[17]
    {
        //cmn
        {UC_3C, sample_rate_122P88, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_3, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },
    //UC_7G -> arr[18]
    {
        //cmn
        {UC_7G, sample_rate_491P52, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_4P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000004, 0x0000000d, 0x0007007f, 0x0000000d, 0x0007007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //TC19-TC20 - RX 32G 16 stream usecseas
    //UC_3E -> arr[19]
    {
        //cmn
        {UC_3E, sample_rate_122P88, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_3, e_LINK_IQ_BW_GSPS_2P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2 , err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},
    },

    //UC_5F -> arr[20]
    {
        //cmn
        {UC_5F, sample_rate_245P76, l_4, m_32, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_4P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x000f007f, 0x00000009, 0x000f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},
    },
    //TC59-UC21 - RX 24G,1.5g, 4 stream usecseas
    //UC_6a -> arr[21]
    {
        //cmn
        {UC_6A, sample_rate_368P64, l_2, m_8, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_24P33024, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_1P5},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000005, 0x0000003b, 0x005f00bf, 0x00000027, 0x003f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x00000005, 0x0000006b, 0x005f00bf, 0x00000047, 0x003f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //RX 24G 4 stream usecseas
    //bringup up rx path for rsb source mode, tx parameters not configured here, roshan 12/08/24
    //UC_6c -> arr[22]
    {
        //cmn
        {UC_6C, sample_rate_368P64, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_24P33024, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_3P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000005, 0x0000003b, 0x005f00bf, 0x00000027, 0x003f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000005, 0x00000053, 0x002f00bf, 0x00000037, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //RX 24G 4 stream usecseas
    //bringup up rx path for rsb source mode, tx parameters not configured here, roshan 12/08/24
    //UC_8a -> arr[23]
    {
        //cmn
        {UC_8A, sample_rate_737P28, l_1, m_2, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_24P33024, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_0, e_LINK_IQ_BW_GSPS_0P75},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000001, 0x0000001d, 0x002f00bf, 0x00000013, 0x001f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000c, 0x00000000, disable},enable,enable},
        {0x00000005, 0x00000053, 0x002f00bf, 0x00000037, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x000000ff, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },


    //TC82-UC22 - RX 24G,1.5g, 4 stream usecseas
    //UC_5a -> arr[24]
    {
        //cmn
        {UC_5A, sample_rate_245P76, l_2, m_8, f_12, s_1, n_tot_24, jesd_204c, serdes_rate_24P33024, e_3, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_2, smpl_req_neg_cycle_1, e_LINK_IQ_BW_GSPS_1P0},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000005, 0x0000003b, 0x005f00bf, 0x00000027, 0x003f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x0000000b, 0x00000000, disable},enable,enable},
        {0x00000005, 0x00000053, 0x002f00bf, 0x00000037, 0x001f007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000002, 0x00000001, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

    //RX 8G 8 stream usecseas
    //bringup up rx path for rsb source mode, tx also updated, roshan 22/08/24
    //UC_1a -> arr[25]
    {
        //cmn
        {UC_1A, sample_rate_30P72, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_8P11008, e_1, soni_1, clk_ratio_1_1, smpl_req_pos_cycle_1, smpl_req_neg_cycle_3, e_LINK_IQ_BW_GSPS_0P25},
        {0xFFFFF, 0xFFFFF},

        //rx
        {{disable, disable, err_thresh_2, err_thresh_2, disable}, enable, enable},
        {0x00000002c, 0x00000027, 0x003f007f, 0x00000027, 0x003f007f, enable, enable, enable, enable},
        {enable, 0x00000100},
        {0x00000184, 0x8},

        //tx
        {{disable, disable, 0x00000010, 0x00000000, disable},enable,enable},
        {0x0000002c, 0x0000003f, 0x003f007f, 0x0000003f, 0x003f007f, enable, enable, enable, enable},
        {0x00000180, 0x00000003, 0x00000007, 0x00000006, 0x00000007, 0x00000001, disable, enable},
        {0x00000184, 0xf}
    },

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
int32_t assign_tc_config(struct jesd_tc_config_t *jesd_tc_config_arr_ptr, uint32_t testcase)
{
    int32_t ret_value= JESD_SUCCESS;
    if ( testcase >= TC_MAX ) {
        printf("WARNING: Reached MAX supported TC LIMIT; returning \n");

        return JESD_GENERIC_FAIL;
    }

    printf("Assigning TC config \n");
     // JESD TC selection
    jesd_tc_config.testcase_id                                                  = jesd_tc_config_arr_ptr[testcase].testcase_id;
    jesd_tc_config.usecase_id                                                   = jesd_tc_config_arr_ptr[testcase].usecase_id;
    jesd_tc_config.flow_id                                                      = jesd_tc_config_arr_ptr[testcase].flow_id;
    jesd_tc_config.vex_id                                                       = jesd_tc_config_arr_ptr[testcase].vex_id;
    jesd_tc_config.jesd_id                                                      = jesd_tc_config_arr_ptr[testcase].jesd_id;
    printf("jesd_tc_config.testcase_id = %d\n", jesd_tc_config.testcase_id);
    printf("jesd_tc_config.usecase_id = %d\n", jesd_tc_config.usecase_id);
    printf("jesd_tc_config.flow_id = %d\n", jesd_tc_config.flow_id);
    printf("jesd_tc_config.vex_id = %d\n", jesd_tc_config.vex_id);
    printf("jesd_tc_config.jesd_id = %d\n", jesd_tc_config.jesd_id);

    return ret_value;
}

/**
 * @brief           Function for assigning UC specific values to jesd_link_config struct
 * @param [in]      jesd_config_arr[],usecase_id
 * @return          
 */
 // todo: change the name of function it is not just link_config anymore
int32_t assign_jesd_config(struct jesd_config_t *jesd_config_arr_ptr, uint32_t usecase) 
{
    // Select usecase from tbl 
    printf("Assigning jesd config \n");
    printf("usecase %d \n",usecase);
    int32_t ret_value= JESD_SUCCESS;
    if (usecase >= UC_MAX)
    {
        printf("WARNING: Reached MAX supported UC  LIMIT; returning \n");

        return JESD_GENERIC_FAIL;
    }
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
    //jesd_config.jesd_link_config.smpl_trans_pos_neg                             = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_trans_pos_neg; //roshan added below 2 lines, 07/07/24
    jesd_config.jesd_link_config.smpl_trans_pos                                 = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_trans_pos;
    jesd_config.jesd_link_config.smpl_trans_neg                                 = jesd_config_arr_ptr[usecase].jesd_link_config.smpl_trans_neg;
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

    return ret_value;
}

/**
 * @brief           Function for assigning default values to jesd_config struct
 * @param [in]      jesd_link_config_arr[],use_case_id
 * @return          
 */
int32_t assign_defaults()
{
    int32_t ret_value= JESD_SUCCESS;
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
    return ret_value;
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

    uint32_t flow_value  = jesd_tc_config.flow_id;

    switch (serdes_rate_sel)
    {
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 

            printf("ERROR: Configure clocks for serdes rate id %d - selection failed \n ", serdes_rate_sel);
            break;

        case serdes_rate_8P11008:
            switch (clk_ratio)
            {

                case clk_ratio_1_1:
                    printf("08G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s4a1 -P 0x20000 0x18");
                    //for s4a3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s4a3 -P 0x20000 0x18");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x18");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x18");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x18");
                    //for s5b3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s5b3 -P 0x20000 0x18");
                    break;

                case clk_ratio_2_1:
                    printf("###08G clk_ratio 2_1 is not programmed yet, PLS EXIT THE TEST###\n");
                    break;

                default:
                    printf("08G clk_ratio 1_1 default \n");
                    system("frioPciWrite -F s4a1 -P 0x20000 0x18");
                    //for s4a3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s4a3 -P 0x20000 0x18");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x18");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x18");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x18");
                    //for s5b3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s5b3 -P 0x20000 0x18");
                    break;
            }

            printf("08G after def \n");
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s4a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s4b1 -P 0x20004 0x1900190");

            printf("08G IP \n");

            if((flow_value == flow_lpbk_jesdTx_jesdRx) || (flow_value == flow_tsb_src_rsb))
            {
                //enable "jesd_ip path", "serial/parallel lpbk" or "jesd-tx to jesd-rx lpbk"
                printf("\n###$$$For 08G JESD Tx to JESD Rx lpbk is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x0B"); //IP
            }
            else
            {
                //enable jesd_ip path or serial or parallel lpbk
                printf("\n###For 08G DNRT to JESD_IP path is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x0A"); //IP
                //printf("\n###For 08G DNRT to DNRT serial lpbk is enabled \n\n");
                //system("frioPciWrite -F s5a3 -P 0x20000 0x08"); //Serial
                //printf("\n###For 08G DNRT to DNRT parallel lpbk is enabled \n\n");
                //system("frioPciWrite -F s5a3 -P 0x20000 0x09"); //Parallel
            }

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
            if((flow_value == flow_lpbk_jesdTx_jesdRx) || (flow_value == flow_tsb_src_rsb))
            {
                //enable "jesd_ip path", "serial/parallel lpbk" or "jesd-tx to jesd-rx lpbk"
                printf("\n###$$$For 16G JESD Tx to JESD Rx lpbk is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x03"); //IP
            }
            else
            {
                //enable jesd_ip path or serial or parallel lpbk
                printf("\n###For 16G DNRT to JESD_IP path is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
                //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
                //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
            }
            break;

        case serdes_rate_24P33024:
            switch (clk_ratio)
            {

                case clk_ratio_1_1:
                    printf("24G clk_ratio 1_1 \n");
                    system("frioPciWrite -F s4a1 -P 0x20000 0x1C");
                    //for s4a3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s4a3 -P 0x20000 0x1C");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x1C");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x1C");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x1C");
                    //for s5b3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s5b3 -P 0x20000 0x1C");
                    break;

                case clk_ratio_2_1:
                    printf("###24G clk_ratio 2_1 is not programmed yet, PLS EXIT THE TEST###\n");
                    break;

                default:
                    printf("24G clk_ratio 1_1 default \n");
                    system("frioPciWrite -F s4a1 -P 0x20000 0x1C");
                    //for s4a3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s4a3 -P 0x20000 0x1C");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x1C");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x1C");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x1C");
                    //for s5b3, bit 2,3,4,5 only as per fpga release sheet,
                    system("frioPciWrite -F s5b3 -P 0x20000 0x1C");
                    break;
            }

            printf("24G after def \n");
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s4a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s4b1 -P 0x20004 0x1900190");
            printf("24G IP \n");

            if((flow_value == flow_lpbk_jesdTx_jesdRx) || (flow_value == flow_tsb_src_rsb))
            {
                //enable "jesd_ip path", "serial/parallel lpbk" or "jesd-tx to jesd-rx lpbk"
                printf("\n###$$$####For 24G JESD Tx to JESD Rx lpbk is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x0F"); //IP
            }
            else
            {
                //enable jesd_ip path or serial or parallel lpbk
                printf("\n###For 24G DNRT to JESD_IP path is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x0E"); //IP
                //printf("\n###For 24G DNRT to DNRT serial lpbk is enabled \n\n");
                //system("frioPciWrite -F s5a3 -P 0x20000 0x0C"); //Serial
                //printf("\n###For 24G DNRT to DNRT parallel lpbk is enabled \n\n");
                //system("frioPciWrite -F s5a3 -P 0x20000 0x0D"); //Parallel
            }

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

            if((flow_value == flow_lpbk_jesdTx_jesdRx) || (flow_value == flow_tsb_src_rsb))
            {
                //enable "jesd_ip path", "serial/parallel lpbk" or "jesd-tx to jesd-rx lpbk"
                printf("\n###$$$For 32G JESD Tx to JESD Rx lpbk is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x07"); //IP
            }
            else
            {
                //enable jesd_ip path or serial or parallel lpbk
                printf("\n###For 32G DNRT to JESD_IP path is enabled \n\n");
                system("frioPciWrite -F s5a3 -P 0x20000 0x06"); //IP
                //system("frioPciWrite -F s5a3 -P 0x20000 0x04"); //Serial
                //system("frioPciWrite -F s5a3 -P 0x20000 0x05"); //Parallel
            }

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
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 

        printf("ERROR : Configure clocks for serdes rate id %d - selection failed \n", serdes_rate_sel);
        break;

        case serdes_rate_8P11008:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("08G clk_ratio 1_1 \n");
                    //s4a3 and s5b3 don’t have bit 7 in release sheet for sysref
                    system("frioPciWrite -F s4a1 -P 0x20000 0x98");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x98");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x98");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x98");
                    break;

                case clk_ratio_2_1:
                    printf("##########08G clk_ratio 2_1 yet to be configured, STOP TEST\n");
                    //system("frioPciWrite -F s5a1 -P 0x20000 0x80");
                    //system("frioPciWrite -F s5b1 -P 0x20000 0x80");
                    break;

                default:
                    printf("08G clk_ratio 1_1 default \n");
                    //s4a3 and s5b3 don’t have bit 7 in release sheet for sysref
                    system("frioPciWrite -F s4a1 -P 0x20000 0x98");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x98");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x98");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x98");
                    break;
            }
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

        case serdes_rate_24P33024:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("24G clk_ratio 1_1 \n");
                    //s4a3 and s5b3 don’t have bit 7 in release sheet for sysref
                    system("frioPciWrite -F s4a1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x9C");
                    break;

                case clk_ratio_2_1:
                    printf("##########24G clk_ratio 2_1 yet to be configured, STOP TEST\n");
                    //system("frioPciWrite -F s5a1 -P 0x20000 0x80");
                    //system("frioPciWrite -F s5b1 -P 0x20000 0x80");
                    break;

                default:
                    printf("24G clk_ratio 1_1 default \n");
                    //s4a3 and s5b3 don’t have bit 7 in release sheet for sysref
                    system("frioPciWrite -F s4a1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s4b1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x9C");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x9C");
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
int init_vex(uint32_t vex_id)
{

    int rv = 0;

    //clear vex memory
    printf("INFO : Starting to clear vex mem from VEX%d\n",vex_id);
    vex_mem_clear(vex_id, srp);
    printf("INFO : Done clearing vex mem from VEX%d\n", vex_id);

   /*  printf("\n########Starting to clear vex mem from 1\n");
    vex_mem_clear(rx_vex_id + 0x1, srp);
    printf("########Done clearing vex mem 1\n\n"); */
    delay(1000);
    return rv;
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
    // uint32_t cio2strm_mem_addr_low_value       = 0x00100000; //// TODO: to remove only for test
#ifdef OFFSET_20000
    uint32_t cio2strm_mem_addr_low_offset      = 0x20000;
    uint32_t cio2strm_mem_addr_high_offset     = 0x1FFFF;
#else
    uint32_t cio2strm_mem_addr_low_offset      = 0x10000;
    uint32_t cio2strm_mem_addr_high_offset     = 0x0FFFF;
#endif
    uint32_t cio2strm_mem_addr_offset_value    = 0x00000000;
    uint32_t cio2strm_mem_addr_dest_value      = jesd_host_id;




    if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)  
    {
        if  ( tx_vex_id == 0) // todo: to generalized hardcoded assuming first vex will always be 0; 
        {
            num_of_streams = MAX_STREAM_COUNT_PER_VEX;
            // cio2strm_mem_addr_low_value = 0x00000000;
        }
        else 
        {
            num_of_streams = num_of_streams - MAX_STREAM_COUNT_PER_VEX;
            cio2strm_mem_addr_low_value = cio2strm_mem_addr_low_value + (cio2strm_mem_addr_low_offset * MAX_STREAM_COUNT_PER_VEX);
        }
    }

    cio2strm_range_en = (1 << num_of_streams) -1; 

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
	uint32_t da_value_per_flit_count[] = { 1/*2*/, 2/*4*/, 3/*8*/, 4/*16*/, 5/*32*/, 6/*64*/, 7/*128*/, 8/*256*/};
    uint32_t str_reg_addr_offset                = 0x4;
    uint32_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2; 
    uint32_t flits_per_stream                = (((uint32_t *)g_flits_per_block)[jesd_config.jesd_link_config.link_iq_bw])/num_of_streams ;  
   uint32_t samples_per_stream              = (((uint32_t *)g_samples_per_block)[jesd_config.jesd_link_config.link_iq_bw])/num_of_streams ; 
   
    uint32_t str_id                             = 0x0;
#if(0)
    uint32_t h2b_buf_sz_hw_tbl_value            = 0x0;
#else
    uint32_t h2b_buf_sz_hw_tbl_value            = 0x1;
#endif
    uint32_t h2b_tk_route_tbl_value             = rx_vex_id;
    uint32_t h2b_route_tbl_value                = rx_vex_id;
    uint32_t h2b_md_route_tbl_value             = rx_vex_id;

//  uint32_t h2b_addr_lkup_tbl_value            = 0x80000000;
    uint32_t h2b_addr_lkup_tbl_value            = 0x80008000;  
//  uint32_t h2b_tk_addr_lkup_tbl_value         = 0x18000;
    uint32_t h2b_tk_addr_lkup_tbl_value         = 0x18000 + 0x80; // STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_v2d_flow3_rx_consumer_sm_gate
//  uint32_t h2b_md_ctrl_tbl_value              = 0x1f; // supposed to be size of flit/strm or flit/combined_strm
    // uint32_t h2b_md_ctrl_tbl_value              = (PAYLOAD_SIZE_SAMPLES_PER_STREAM / SAMPLES_PER_FLIT) - 1; // 15;
    int32_t h2b_md_ctrl_tbl_value = flits_per_stream - 1; // root2(flits_per_stream)

    //adding temporary for usecase- 1a, roshan 24/08/24
    if(jesd_tc_config.usecase_id == 25)
    {
        h2b_md_ctrl_tbl_value     = 1;
        printf("###usecase 1a assigning md_cntrl_tbl value of 1\n");
    }
    //uint32_t h2b_md_ctrl_tbl_value            = 0x4000001F;
    //uint32_t h2b_md_ctrl_tbl_value            = 0x40000000;

    // uint32_t h2b_addr_lkup_tbl_offset           = 0x800;
    // uint32_t h2b_addr_lkup_tbl_offset = PAYLOAD_SIZE_SAMPLES_PER_STREAM * SAMPLE_SIZE_BYTE * (1 << h2b_buf_sz_hw_tbl_value); // 0x800; // 0x400;
    uint32_t h2b_addr_lkup_tbl_offset = samples_per_stream * SAMPLE_SIZE_BYTE * (1 << h2b_buf_sz_hw_tbl_value); // 0x800; // 0x400;
    uint32_t h2b_tk_addr_lkup_tbl_offset        = 0x4;

    printf("#####Debug - effective samples per stream is %x\n",samples_per_stream);
    printf("#####Debug - effective sflits_per_stream is %x\n", flits_per_stream);
    printf("#####Debug - SAMPLE_SIZE_BYTE is %x\n",SAMPLE_SIZE_BYTE);
    printf("#####Debug - effective h2b_buf_sz_hw_tbl_value is %x\n",h2b_buf_sz_hw_tbl_value);
    printf("#####Debug - effective h2b_addr_lkup_tbl_offset is %x\n",h2b_addr_lkup_tbl_offset);
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
        // Valid Address and Routing Entry in Data/Token/Metadata Lookup Registers.Vector/Sample Base address

        register_config_tbl_t jesd_h2b_strm_config_tbl[] = 
        {
            // H2B Stream Config - Vector/Sample Data Buffer Size LUT
            {(NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)), 
                h2b_buf_sz_hw_tbl_value, 
                NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, 
                "H2B_BUF_SZ_HW_TBL"},

            // Vector/Sample Data Routing LUT.
            {(NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (str_id < MAX_STREAM_COUNT_PER_VEX ) ? h2b_route_tbl_value : (h2b_route_tbl_value+1),
                NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_ROUTE_LKUP_TBL"},

             // Token Address LUT. 
            {(NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (h2b_tk_addr_lkup_tbl_value + ((str_id % MAX_STREAM_COUNT_PER_VEX) * h2b_tk_addr_lkup_tbl_offset)),
                NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK,
                "H2B_TK_ADDR_LKUP_TBL"},

            // Token Routing LUT.
            {(NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (str_id < MAX_STREAM_COUNT_PER_VEX ) ? h2b_tk_route_tbl_value:(h2b_tk_route_tbl_value+1),
                NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_TK_ROUTE_LKUP_TBL"},

            // Metadata Base Address LUT
            /*{(NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)), 
                    0x10000,
                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK,
                    "H2B_MD_ADDR_LKUP_TBL"}, */

            // Metadata Routing LUT
            {(NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (str_id < MAX_STREAM_COUNT_PER_VEX ) ? h2b_md_route_tbl_value: (h2b_md_route_tbl_value+1),
                NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_MD_ROUTE_LKUP_TBL"},

            // Metadata Control tbl
            {(NSIP_HBI_H2B_MD_CTRL_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_md_ctrl_tbl_value,
                NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK,
                "H2B_MD_CONTROL_TBL"},

            // NOTE! This register should be written LAST since it validates all of the other registers.
            {(NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * 0x4)),
                (h2b_addr_lkup_tbl_value + (str_id % MAX_STREAM_COUNT_PER_VEX) * h2b_addr_lkup_tbl_offset ),
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
    printf("\n\n#############md_cntrl value is %d \n",h2b_md_ctrl_tbl_value);
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
    //uint32_t b2h_addr_map_tbl_value             = 0x80100000; // TODO: to remove only for test
#ifdef OFFSET_20000
    uint32_t b2h_addr_map_tbl_offset            = 0x20000;
    uint32_t b2h_addr_mask_tbl_value            = 0x1FFFF;
#else
    uint32_t b2h_addr_map_tbl_offset            = 0x10000;
    uint32_t b2h_addr_mask_tbl_value            = 0x0FFFF;
#endif
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

            // ADDR MASK TBL: 28-bit Mask bits (ï¿½1ï¿½=address bit is masked out) for the address range specified in the B2H_ADDR_MAP_TBL reg       
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
 #define MAX_FLIT_COUNT_NSIP_SUPPORTS   (8)
int configure_jesd_rx_crux_clk_csr(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_crux_clk_csr_base = g_jesd_crux_clk_csr_base_addr[rx_jesd_id];

    uint32_t rx_mem_address_range   = 0x200; //512d
    uint32_t rx_wr_mem_tbl          = 0x00000000;
    uint32_t rx_rd_mem_tbl          = 0x00000000;
    uint32_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;
    uint32_t flits_per_stream       = (((uint32_t *)g_flits_per_block)[jesd_config.jesd_link_config.link_iq_bw])/num_of_streams ;

    uint32_t str_reg_addr_offset    = 0x4;
    uint32_t str_id                 = 0x0;
    uint32_t rx_mem_tbl_offset  = (rx_mem_address_range / num_of_streams) % rx_mem_address_range;  ;
    uint32_t mem_depth_per_str = (rx_mem_address_range / num_of_streams) - 1;
    uint32_t rx_strm_cfg        = 0;

    if(flits_per_stream > MAX_FLIT_COUNT_NSIP_SUPPORTS )
        flits_per_stream = MAX_FLIT_COUNT_NSIP_SUPPORTS;


    rx_strm_cfg = 
    ((num_of_streams << JESD_CRUX_CLK_CSR_RX_STRM_CFG_NUM_STRM_BF_OFF) & JESD_CRUX_CLK_CSR_RX_STRM_CFG_NUM_STRM_BF_MSK) | 
    (((flits_per_stream-1) << JESD_CRUX_CLK_CSR_RX_STRM_CFG_FLITS_PER_STRM_BF_OFF) & JESD_CRUX_CLK_CSR_RX_STRM_CFG_FLITS_PER_STRM_BF_MSK) ; 

    //adding temporary till calculaiton are verified for usecase- 1a,6a,6c,
    //will revisit after imp bringups
    //TODO - FIXME, roshan 26/08/24
    if(jesd_tc_config.usecase_id == 25)
    {    
        rx_strm_cfg     = 0x28;
        printf("###usecase 1a assigning rx_strm_cfg value to 0x28\n");
    }
    else if(jesd_tc_config.usecase_id == 21)  //usecase 6a
    {    
        rx_strm_cfg     = 0x64;
        printf("###usecase 6a assigning rx_strm_cfg value to 0x64\n");
    }
    else if(jesd_tc_config.usecase_id == 23)  //usecase 6c
    {    
        rx_strm_cfg     = 0x68;
        printf("###usecase 6c assigning rx_strm_cfg value to 0x68\n");
    }
    else
    {
        //using default value
    }

    
    // For each JESD I/Q stream (up to 16), provide the write and read memory base addresses for each stream
    for (str_id = 0x0; str_id < num_of_streams; str_id++)
    {
        // Specify NSIP write base address for each JESD stream
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)),
                                 (rx_wr_mem_tbl + (str_id * rx_mem_tbl_offset)),
                                 JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK,
                                 "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL"))
            return rv;

        // Specify NSIP read base address and Stream ID
        if (rv = write_reg_18a((jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)),
                               (((rx_rd_mem_tbl + (str_id * rx_mem_tbl_offset)) & JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RX_MEM_BASE_ADDR_BF_MSK) | ((str_id << JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_STRM_ID_BF_OFF) & JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_STRM_ID_BF_MSK)),
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
    if (rv = write_reg_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET,
                           ( mem_depth_per_str & JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_MEM_DEPTH_PER_STR_BF_MSK ),
                           JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_WR_MASK,
                           "JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG"))
        return rv;

    printf("####print rx_strm_cfg\n");
    system("srpRead 0x0670c010 1");

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

    // tx_strm_mem_addr_offset = TX_BUFFER_SIZE_BYTE / num_of_streams;
    // tx_strm_mem_size = tx_strm_mem_addr_offset -1;
    // tx_tsb_trig_en =  0x000307ff;
    // tx_strm_tsb_rd_trig = 0x000007ff;

    // Note: The size should be set the same for all streams, and should only be 4k, 8k, 16k, 32k or 64k to align with the reading as defined in reg STRM_MEM_INST_CNT
    // TODO: remove this switch and have formula based derivation of these value
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
            tx_strm_mem_addr_offset    = 0x00002000;
            tx_strm_mem_size           = 0x00001fff;
            tx_tsb_trig_en             = 0x00030fff;
            tx_strm_tsb_rd_trig        = 0x00000fff;
            tx_num_valid_str           = 0xffff00ff;
            tx_tsb_cfg                 = 0x0;
            break;

        case 0x4:
            tx_strm_mem_addr_offset    = 0x00004000;
            tx_strm_mem_size           = 0x00003fff;
            tx_tsb_trig_en             = 0x00031fff;
            tx_strm_tsb_rd_trig        = 0x00001fff;
            tx_num_valid_str           = 0xffff000f;
            tx_tsb_cfg                 = 0x0;
            break;

        case 0x2:
            tx_strm_mem_addr_offset    = 0x00008000;
            tx_strm_mem_size           = 0x00007fff;
            tx_tsb_trig_en             = 0x00033fff;
            tx_strm_tsb_rd_trig        = 0x00003fff;        
            tx_num_valid_str           = 0xffff0003;          
            tx_tsb_cfg                 = 0x0;   
            break;

        case 0x1:
            // str0 - addr 0
            tx_strm_mem_addr_offset    = 0x00000000;
            // str0 - 64kb
            tx_strm_mem_size           = 0x0000ffff;
            // trig en, half fill en, fill level 32kb
            tx_tsb_trig_en             = 0x00037fff;
            // trig on half full 32kb
            tx_strm_tsb_rd_trig        = 0x00007fff;
            // all 16 buffers 64kb , str0
            tx_num_valid_str           = 0xffff0001;
            tx_tsb_cfg                 = 0x0; 
            break;

        default:
            tx_strm_mem_addr_offset    = 0x00000000;
            tx_strm_mem_size           = 0x0000ffff;
            tx_tsb_trig_en             = 0x00037fff;
            tx_strm_tsb_rd_trig        = 0x00007fff;
            tx_num_valid_str           = 0xffff0001;
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
        // if ( str_id < MAX_STREAM_COUNT_PER_VEX ) { // to swap the stream set in TSB
        //     tx_strm_mem_addr = MAX_STREAM_COUNT_PER_VEX * tx_strm_mem_addr_offset; // todo: to remove: only for test
        // }
        // else {
        //     tx_strm_mem_addr = 0x00000000;
        // }
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
            tx_strm_mem_inst_cnt       = 0x02; 
            break;

        case 0x4:
           tx_strm_mem_inst_cnt       = 0x04;
            break;

        case 0x2:
            tx_strm_mem_inst_cnt       = 0x08;
            break;
            
        case 0x1:
            // str0 - all 16 buffers - 64kb
            tx_strm_mem_inst_cnt       = 0x10;
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
    soni            = (jesd_config.jesd_link_config.sonif) - 0x1;
    soni            = (sample_x8_ratio<<5) | soni;

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

    // Number of octets per Frame (F) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_RX_F_WR_MASK,
                            "JESD_XIP_204C_RX_F"))
        return rv;

    // Number of Lanes (L) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_RX_L_WR_MASK,
                            "JESD_XIP_204C_RX_L"))
        return rv;

    // Sample resolution (N) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_RX_N_WR_MASK,
                            "JESD_XIP_204C_RX_N"))
        return rv;

    // Number of converters (M) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_RX_M_WR_MASK,
                            "JESD_XIP_204C_RX_M"))
        return rv;

    // Total number of bits per sample (Nï¿½) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_RX_NTOTAL_WR_MASK,
                            "JESD_XIP_204C_RX_NTOTAL"))
        return rv;

    // Number of samples (S) ï¿½ 1 per converter : Refer UC table
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

    // Samples on Interface (SONI). Set to SONI ï¿½ 1 : Refer UC table
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

    //Number of Multiblocks per Extended Multiblocks (E) ï¿½ 1 
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

    // Number of octets per Frame (F) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_TX_F_WR_MASK,
                            "JESD_XIP_204C_TX_F"))
        return rv;

    // Number of Lanes (L) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_TX_L_WR_MASK,
                            "JESD_XIP_204C_TX_L"))
        return rv;

    // Sample resolution (N) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_TX_N_WR_MASK,
                            "JESD_XIP_204C_TX_N"))
        return rv;

    // Number of converters (M) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_TX_M_WR_MASK,
                            "JESD_XIP_204C_TX_M"))
        return rv;

    // Total number of bits per sample (Nï¿½) ï¿½ 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_TX_NTOTAL_WR_MASK,
                            "JESD_XIP_204C_TX_NTOTAL"))
        return rv;

    // Number of samples (S) ï¿½ 1 per converter : Refer UC table
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

    // Samples on Interface (SONI). Set to SONI ï¿½ 1 : Refer UC table
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

    //Number of Multiblocks per Extended Multiblocks (E) ï¿½ 1 
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
 * @brief           Function configuring VEX: Rx path
 * @param [in]      rx_vex_id
 * @return          status
 */
int configure_vex_rx(uint32_t rx_vex_id)
{
#ifdef E2E_FLOW_EN
    UNUSED(rx_vex_id);
    return 0;
#else
    unsigned int vex_dmem_offset    = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (rx_vex_id * vex_dmem_offset);
    
    unsigned int vex_vmem_offset    = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (rx_vex_id * vex_vmem_offset);

    unsigned int stream_count = jesd_config.jesd_link_config.converters/2;

    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_tc_config.jesd_id];

    int vectors_per_block = ((int *)g_vectors_per_block)[jesd_config.jesd_link_config.link_iq_bw];
    int flits_per_block = ((int *)g_flits_per_block)[jesd_config.jesd_link_config.link_iq_bw];


    char *vex_rx_fw_file_path = "vex_fw/sim_m64/jesd_rx.fw"; // keep it as macro above to the file
    char file_name[100] = VEX_PATTERN_FILE;
    FILE *fptr;

    uint32_t rv = 0,
    val = 0, dev_id = 0, host_flag = 0xF;
    srp_uint32_t flags = 0;
    int rx_in_list, vex_combo_good;
    srp_vex_config_t vex_params;
    uint64_t base_addr;
    uint32_t vha_num, ant_num;
    // int out_rate = 0; // to select vector per block for 2gsps

    // filter_mode_t mode;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;
    srp_uint32_t host_vec_processed = 0, host_blocks_processed = 0, host_blocks_passed = 0, host_vectors_passed = 0, host_result = 0;
    int cnt, lc, i, j, k;
    int vex_num =0;//, dl_clk = 0;

    int dmem_offset = 0x4000;
    int wait_for_flit_count = (stream_count > MAX_STREAM_COUNT_PER_VEX) ? (g_max_blocks * flits_per_block / 2) : (g_max_blocks * flits_per_block); // for 16 stream only half of the flits to be checked per vex

    g_max_blocks = 1; // for oneshot only one block to poll for
    int vectors_per_block_per_stream_count = vectors_per_block/stream_count;
    //adding after seeing issue for 1a,
    //https://hsdes.intel.com/appstore/article/#/16025203405
    if(vectors_per_block_per_stream_count < MIN_VEC_PER_BLOCK)
        vectors_per_block_per_stream_count = MIN_VEC_PER_BLOCK;  //create #define, roshan 13/08/24    


    // unsigned val_kargs[4] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0};
    int vex_rx_offset_val[] = {
        HIVE_ADDR_jesd_rx_g_rx_stream_count,
        HIVE_ADDR_jesd_rx_g_rx_num_vecs_in,
        HIVE_ADDR_jesd_rx_g_rx_num_blocks,
        HIVE_ADDR_jesd_rx_g_rx_tbs_in_blk};
    // unsigned vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64};
    unsigned vex_rx_val_kargs[] = { (stream_count > MAX_STREAM_COUNT_PER_VEX ? MAX_STREAM_COUNT_PER_VEX : stream_count),
                                //    (PAYLOAD_SIZE_SAMPLES_PER_STREAM / SAMPLES_PER_VEC), // NUMBER_OF_VECTORS_INPUT,
                                   vectors_per_block_per_stream_count, // NUMBER_OF_VECTORS_INPUT, // TODO: Here vectors are per stream, tx/lbk has per block undivided
                                   g_max_blocks,
                                   2};

    unsigned val_out[MAX_VECTOR_COUNT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned val_out_stream[MAX_VECTOR_COUNT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];


    LOG_PRINT("INFO: config beginning\n");


    // SDF init
    if(rv = write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(VEX_BASE(rx_vex_id)),
                          HIVE_ADDR_jesd_rx_consumer_sm_gate,
                          VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                          "BPCA_BP_DMEM"))
        return rv;

    printf("HOST:  SDF init done for vex %d\n", rx_vex_id);

 //roshan commenting for debug 18/07/24
/*    for (i = 0; i < 1; i++)
    {
        //~ if(1 == i) vex_num = tx_vex;

        if (vex_mem_clear(rx_vex_id, srp))
        {
            printf("ERROR: Failed to clear memories of VEX%d\n", rx_vex_id);
            return -1;
        }
        printf("HOST: Cleared memories of VEX%d\n", rx_vex_id);
    }
*/

    {
        if ((rv = vex_loader( rx_vex_id,
                                 // "vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
                                 vex_rx_fw_file_path)))
            return rv;
        printf("HOST: Loaded %s to vex core %d\n", vex_rx_fw_file_path, rx_vex_id);
    }
    printf("HOST: VEX program load - done\n");

    write_reg_18a(vex_dmem_base_addr+ HIVE_ADDR_jesd_rx_consumer_sm_gate + (CONSUMER_SM_BUF_ID * 4), 0, 1, "consumer_sm_gate_clear");

    for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        write_mem_18a(vex_dmem_base_addr + vex_rx_offset_val[lc], 1, &vex_rx_val_kargs[lc], "Val_kargs");
        printf("HOST: Loaded offset 0x%x with value 0x%x\n", vex_dmem_base_addr + vex_rx_offset_val[lc], vex_rx_val_kargs[lc]);
    }
    printf("HOST: Loaded host params to Rx vex core %d\n", rx_vex_id);

    int temp = 0;

    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_num_vecs_in, 1, &temp, "num_vecs_in");
    printf("HOST: value @ HIVE_ADDR_jesd_rx_g_rx_num_vecs_in = %d\n", temp);

    int sample_count = vex_rx_val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC;
    printf("HOST: sample_count = %d\n", sample_count);

#if(0) // commenting out vex pattern fill, not required for onshot

#if(0) // old way of prefill

    printf("HOST: Output reference sample file : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if (NULL == fptr)
    {
        printf("ERROR: Not able to open the output file\n");
        fclose(fptr);
        return -1;
    }


    if (vector_read_hex_u32(fptr,
                            (int *)val_out,
                            sample_count) < sample_count) // 32 *32 = 1024
    {
        printf("ERROR: Insufficient output samples\n");
        fclose(fptr);
        return -1;
    }
    fclose(fptr);



    write_mem_18a(vex_vmem_base_addr + HIVE_ADDR_jesd_rx_vbuffer, sample_count, val_out, "num_vecs_in");


#else // new way of prefill using write_mem_18a
    read_samples_from_file(file_name, sample_count, val_out);

    // unsigned int src_stream_buffer_offset = vex_rx_val_kargs[3] * vex_rx_val_kargs[1] * BYTES_PER_VEC;
    unsigned int src_stream_buffer_offset = vex_rx_val_kargs[1] * BYTES_PER_VEC;
    for( int stream_id = 0; stream_id < stream_count; stream_id++)
    {
        get_samples_for_stream(sample_count, stream_id, val_out, val_out_stream);
        for (int ii = 0; ii < sample_count; ii++)
        {
            //roshan commenting as prints filling up terminal, 18/07/24
            //printf("HOST: val_out= 0x%0.8x,  val_out_stream= 0x%0.8x\n", ((int *)val_out)[ii], ((int *)val_out_stream)[ii]);
        }
        write_mem_18a(vex_vmem_base_addr + HIVE_ADDR_jesd_rx_vbuffer + stream_id * src_stream_buffer_offset, sample_count, val_out_stream, "num_vecs_in");
    }

#endif // commenting out vex pattern fill, not required for onshot

    printf("HOST: Initialized pattern into the vector memory of vex core %d at addr 0x%x\n", rx_vex_id, (vex_vmem_base_addr + HIVE_ADDR_jesd_rx_vbuffer));
#endif

    // clearing h2b_flit_count before starting vex
    h2b_flit_cnt = read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "NSIP_HBI_H2B_FLIT_CNT");
    printf(" H2B_FLIT_CNT = %d at addr 0x%x \n", h2b_flit_cnt, jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET);

    vex_start(rx_vex_id, 0);

    printf("HOST: Waiting for the H2B flit count to be atleast %d\n", wait_for_flit_count); // 64
    cnt = 0;
    // h2b_flit_cnt = read_reg_18a(NSIP_HBI_H2B_FLIT_COUNT_ADR(DLNK_JESDABC0_NSIP_HBI_CSR_BASE), "H2B_FLIT_COUNT");
    // // value47  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "NSIP_HBI_H2B_FLIT_COUNT");
    // printf(" H2B_FLIT_CNT = %d at addr 0x%x \n", h2b_flit_cnt, NSIP_HBI_H2B_FLIT_COUNT_ADR(DLNK_JESDABC0_NSIP_HBI_CSR_BASE));



    h2b_flit_cnt = 0;
    while (1)
    {
        // h2b_flit_cnt += read_reg_18a(NSIP_HBI_H2B_FLIT_COUNT_ADR(DLNK_JESDABC0_NSIP_HBI_CSR_BASE), "H2B_FLIT_COUNT");
        // value47  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "NSIP_HBI_H2B_FLIT_COUNT");
        // printf(" H2B_FLIT_CNT \n");
        h2b_flit_cnt += read_reg_18a(jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "NSIP_HBI_H2B_FLIT_CNT");

        if (h2b_flit_cnt > wait_for_flit_count) // 64
        {
            break;
        }
        sleep(1);
        cnt++;
#if (1) // 0 = waiting indefinitely
        if (WAIT_COUNT == cnt)
        {
            printf("ERROR: Waited for %d cycles, but h2b_flit_cnt is NOT reaching %d\n", cnt, wait_for_flit_count); // 64
            break;
        }
#endif
    }
    printf(" H2B_FLIT_CNT = %d at addr 0x%x \n", h2b_flit_cnt, jesd_nsip_hbi_base + NSIP_HBI_H2B_FLIT_CNT_OFFSET);

#if(0)
    printf("HOST: Waiting for the Rx VEX to receive and compare %d vectors\n", (g_max_blocks * vectors_per_block)); // 32
    cnt = 0;
    while (1)
    {
        // if ((rv = srp_dev_block_read32(srp,
        //                                SRP_BLOCK_VEX_CORE,
        //                                rx_vex_id,
        //                                //  dmem_offset + HIVE_ADDR_vha2vex_p5_8iq_g_count1,
        //                                dmem_offset + HIVE_ADDR_jesd_rx_g_rx_processed_vector_count,
        //                                &host_vec_processed,
        //                                1,
        //                                flags)))
        //     return rv;
        read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_processed_vector_count, 1, &host_vec_processed, "host_vec_processed");

        if (host_vec_processed >= (g_max_blocks * vectors_per_block))
        {
            break;
        }
        cnt++;
#if (1) // 0 = waiting indefinitely
        if (WAIT_COUNT == cnt)
        {
            printf("ERROR: Waited for %d cycles, but host_vec_processed is NOT reaching %d\n", cnt, (g_max_blocks * vectors_per_block));
            break; // return -1;
        }
#endif
    }
    printf("HOST: host_vec_processed = %d\n", host_vec_processed);

    printf("HOST: Reading the vector comparison results from the VEX core %d\n", rx_vex_id);
    // if ((rv = srp_dev_block_read32(srp,
    //                                SRP_BLOCK_VEX_CORE,
    //                                rx_vex_id,
    //                                //   dmem_offset + HIVE_ADDR_vha2vex_p5_8iq_g_compare_result,
    //                                dmem_offset + HIVE_ADDR_jesd_rx_g_rx_compare_result,
    //                                &host_result,
    //                                1,
    //                                flags)))
    //     return rv;
    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_compare_result, 1, &host_result, "host_result");



    // if ((rv = srp_dev_block_read32(srp,
    //                                SRP_BLOCK_VEX_CORE,
    //                                rx_vex_id,
    //                                //   dmem_offset + HIVE_ADDR_vha2vex_p5_8iq_g_add_val_out,
    //                                dmem_offset + HIVE_ADDR_jesd_rx_g_rx_processed_block_count,
    //                                &host_blocks_processed,
    //                                1,
    //                                flags)))
    //     return rv;
    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_processed_block_count, 1, &host_blocks_processed, "host_blocks_processed");

    // if ((rv = srp_dev_block_read32(srp,
    //                                SRP_BLOCK_VEX_CORE,
    //                                rx_vex_id,
    //                                //   dmem_offset + HIVE_ADDR_vha2vex_p5_8iq_g_fail_cnt,
    //                                dmem_offset + HIVE_ADDR_jesd_rx_g_rx_passed_block_count,
    //                                &host_blocks_passed,
    //                                1,
    //                                flags)))
    //     return rv;
    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_passed_block_count, 1, &host_blocks_passed, "host_blocks_passed");

    // if ((rv = srp_dev_block_read32(srp,
    //                                SRP_BLOCK_VEX_CORE,
    //                                rx_vex_id,
    //                                //   dmem_offset + HIVE_ADDR_vha2vex_p5_8iq_g_countx,
    //                                dmem_offset + HIVE_ADDR_jesd_rx_g_rx_passed_vector_count,
    //                                &host_vectors_passed,
    //                                1,
    //                                flags)))
    //     return rv;
    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_jesd_rx_g_rx_passed_vector_count, 1, &host_vectors_passed, "host_vectors_passed");

    char *test_status = "FAILURE";
    // if((0xffffffff != host_result) || (!host_vec_processed))
    //     test_status = "FAILURE";
    if ((0xffffffff == host_result) && (host_blocks_processed == host_blocks_passed) && (host_vec_processed == host_vectors_passed))
    {
        test_status = "SUCCESS";
    }
    else if (0xffffffff != host_result)
    {
        printf("ERROR: last samples Mismatched\n");
        rv = -1;
    }
    else if (host_blocks_processed != host_blocks_passed)
    {
        printf("ERROR: Some Vectors have Mismatched Sample\n");
        rv = -1;
    }
    else if (host_blocks_processed != host_blocks_passed)
    {
        printf("ERROR: Some blocks have Mismatched vectors\n");
        rv = -1;
    }
    else
    {
        printf("ERROR: some other error\n");
        rv = -1;
    }

    printf("HOST: Comparison result : 0x%x --> %s\n", host_result, test_status);
    // printf("      Processed blocks  : 0x%x\n", host_blocks_processed - add_val[0]);
    printf("      Processed blocks  : 0x%x\n", host_blocks_processed);
    printf("      Passed blocks  : 0x%x\n", host_blocks_passed);
    printf("      Processed vectors : 0x%x\n", host_vec_processed);
    printf("      Passed vectors  : 0x%x\n", host_vectors_passed);

    //~ // Looking for any abnormal statuses post a test run
    //~ printf("HOST: Checking registers after a test completion\n");
    //~ if(rv = test_check_status(tx_vex, rx_vex_id, vha_num, ant_num))
    //~ {
    //~ printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
    //~ rv = -1;
    //~ }

    if (0 == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    }
    else
    {
        printf("Test Result:------ FAIL -----!\n\n");
    }

    printf("HOST: End of the Test execution....!\n");
#endif

    return rv;
#endif
}
/**
 * @brief           Function configuring VEX: Tx path
 * @param [in]      tx_vex_id
 * @return          status
 */
int configure_vex_tx(uint32_t tx_vex_id)
{
#ifdef E2E_FLOW_EN
    UNUSED(tx_vex_id);
    return 0;
#else
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
    // int num_of_sample_p5us_per_stream       = (jesd_config.jesd_link_config.link_iq_bw/2)/num_of_streams;
    int num_of_sample_p5us_per_stream       = (((int* )g_samples_per_block)[jesd_config.jesd_link_config.link_iq_bw] ) /num_of_streams;
    int num_of_vector_per_p5us_per_stream   = num_of_sample_p5us_per_stream/SAMPLE_PER_VECTOR;

    printf("num_of_vector_per_p5us_per_stream = %d \n", num_of_vector_per_p5us_per_stream);
    
    int ret_cycle_val                       = p5us_cycle_count* no_of_vector_per_block_per_stream/(num_of_vector_per_p5us_per_stream);
    ret_cycle_val                           = ret_cycle_val - 1;
#define  VEX_TX_PARAM_COUNT  (9)
    
    printf("VEX Timeout Cycles = %d \n", ret_cycle_val);
    int vex_tx_offset_val[VEX_TX_PARAM_COUNT] = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,

                                     HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
                                     HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
                                     HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base,
                                     HIVE_ADDR_jesd_tx_g_timeout_cycles};
    unsigned *vex_tx_val_kargs = NULL;
    unsigned vex_tx_val_kargs_arr[2][VEX_TX_PARAM_COUNT] = 
    {
#ifdef OFFSET_20000
        {
        0x00000, 0x20000,
        0x40000, 0x60000,
        0x80000, 0xA0000,
        0xC0000, 0xE0000,
        // 0x100000, 0x120000,
        // 0x140000, 0x160000,
        // 0x180000, 0x1A0000,
        // 0x1C0000, 0x1E0000,
        ret_cycle_val
        },
        {
        0x100000, 0x120000,
        0x140000, 0x160000,
        0x180000, 0x1A0000,
        0x1C0000, 0x1E0000,
        // 0x00000, 0x20000,
        // 0x40000, 0x60000,
        // 0x80000, 0xA0000,
        // 0xC0000, 0xE0000,
        ret_cycle_val
        }
#else
        {
        0x00000, 0x10000,
        0x20000, 0x30000,
        0x40000, 0x50000,
        0x60000, 0x70000,
        ret_cycle_val
        },
        {
        0x80000, 0x90000,
        0xa0000, 0xb0000,
        0xc0000, 0xd0000,
        0xe0000, 0xf0000,
        ret_cycle_val
        }
#endif
    };

    vex_tx_val_kargs = (uint32_t *) (&(vex_tx_val_kargs_arr[tx_vex_id]));
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
      printf("Host: address: 0x%0.8x, value: %d \n", (vex_dmem_base_addr + vex_tx_offset_val[lc]), vex_tx_val_kargs[lc]);

    }                  
    printf("Host: Host parameters loaded to Vex%d\n",tx_vex_id);

    printf("Host: Input vectors generation start for Vex%d\n", tx_vex_id);
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
                //val_inp[i][j] = val_inp[i][j] | (tx_vex_id << 28 | lc << 12); // TODO : to remove only fortest

                write_mem_18a((vex_vmem_base_addr + vex_tx_buffer_addr[lc] + (j * sizeof(int)) + (i * NUM_OF_ELEMENTS_PER_VEC * sizeof(int))) ,//local_addr
                                1,
                                &(val_inp[i][j]),
                                "input vector gen");

//                printf("DEBUG: vex_id %d, addr = 0x%x , data = 0x%x\n",
//                            tx_vex_id,
//                            (vex_vmem_base_addr + vex_tx_buffer_addr[lc] + (j * sizeof(int)) + (i * NUM_OF_ELEMENTS_PER_VEC * sizeof(int))),
//                            val_inp[i][j]);

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

     //To VEX1
    printf("To VEX1 1 stream\n");
    system("srpRead 0x63.1.0x28000 64");
    printf("\n");
#endif // E2E_FLOW_EN
}

/**
 * @brief           Configuring VEX for loopback at vex: Rx-tx path
 * @param [in]      rx_vex_id
 * @return          status
 */
int configure_vex_rx_tx_lpbk(uint32_t rx_vex_id)
{
#ifdef E2E_FLOW_EN
    UNUSED(rx_vex_id);
    return 0;
#else
    uint32_t rv = 0;
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (rx_vex_id * vex_dmem_offset);

    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (rx_vex_id * vex_vmem_offset);

    unsigned int stream_count = jesd_config.jesd_link_config.converters / 2;

    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_tc_config.jesd_id];

    int vectors_per_block = ((int *)g_vectors_per_block)[jesd_config.jesd_link_config.link_iq_bw];

    char *vex_fw_file_path = "vex_fw/sim_m64/jesd_rx_tx_lpbk.fw"; // keep it as macro above to the file
    char file_name[100] = VEX_PATTERN_FILE;
    FILE *fptr;

    uint32_t  val = 0, dev_id = 0, host_flag = 0xF;
    srp_uint32_t flags = 0;
    int rx_in_list, vex_combo_good;
    srp_vex_config_t vex_params;
    uint64_t base_addr;
    uint32_t vha_num, ant_num;
    // int out_rate =  3; // TODO : currently hard codeing for 5c // need tp change link_iq_bw to represnt it in config


    // int dl_clk = 0; // TODO : currently hardcoding for 1G// need to have it part of config

    // filter_mode_t mode;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;
    srp_uint32_t host_vec_processed = 0, host_blocks_processed = 0, host_blocks_passed = 0, host_vectors_passed = 0, host_result = 0;
    int cnt, lc, i, j, k;
    int vex_num = 0;

    int dmem_offset = 0x4000;
    uint32_t *vex_rx_val_kargs = NULL;
#define  VEX_PARAM_COUNT  (21)
    uint32_t vex_rx_offset_val[VEX_PARAM_COUNT] = {
        // Rx path inputs
        HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_stream_count,
        HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_num_vecs_in,
        HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_num_blocks,
        HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_tbs_in_blk,

        // Tx path inputs
        HIVE_ADDR_jesd_rx_tx_lpbk_g_timeout_cycles,
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address,
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (1 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (2 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (3 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (4 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (5 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (6 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (7 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (8 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (9 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (10 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (11 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (12 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (13 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (14 * 4),
        HIVE_ADDR_jesd_rx_tx_lpbk_g_tx_dest_address + (15 * 4)

    };

    uint32_t vex_rx_val_kargs_arr[2][VEX_PARAM_COUNT] = // vex_id are index 0 for vex 0 1 for vex 1
    // {
    //         {// Rx path inputs
    //          (stream_count > MAX_STREAM_COUNT_PER_VEX ? MAX_STREAM_COUNT_PER_VEX : stream_count),
    //          vectors_per_block / stream_count,
    //          g_max_blocks,
    //          2, // ping pong double buffer

    //          // Tx path inputs
    //          0, // ret_cycle_val, // not being used for now
    // #ifdef OFFSET_20000 // 0x20000 offset
    //          0x00000, 0x20000,
    //          0x40000, 0x60000,
    //          0x80000, 0xA0000,
    //          0xC0000, 0xE0000,
    // #else // 0x10000 offset
    //          0x00000, 0x10000,
    //          0x20000, 0x30000,
    //          0x40000, 0x50000,
    //          0x60000, 0x70000,
    // #endif
    //          0, 0,
    //          0, 0,
    //          0, 0,
    //          0, 0
    //         },
    //         {// Rx path inputs
    //          stream_count,
    //          vectors_per_block / stream_count,
    //          g_max_blocks,
    //          2, // ping pong double buffer

    //          // Tx path inputs
    //          0, // ret_cycle_val, // not being used for now

    // #ifdef OFFSET_20000 // 0x20000 offset
    //          0x100000, 0x120000,
    //          0x140000, 0x160000,
    //          0x180000, 0x1A0000,
    //          0x1C0000, 0x1E0000,
    // #else // 0x10000 offset
    //          0x80000, 0x90000,
    //          0xa0000, 0xb0000,
    //          0xc0000, 0xd0000,
    //          0xe0000, 0xf0000,
    // #endif
    //          0, 0,
    //          0, 0,
    //          0, 0,
    //          0, 0}
    // };
    {
#ifdef OFFSET_20000
        {// Rx path inputs // vex0
             (stream_count > MAX_STREAM_COUNT_PER_VEX ? MAX_STREAM_COUNT_PER_VEX : stream_count),
             vectors_per_block / stream_count,
             g_max_blocks,
             2, // ping pong double buffer

             // Tx path inputs
             0, // ret_cycle_val, // not being used for now
        0x00000, 0x20000,
        0x40000, 0x60000,
        0x80000, 0xA0000,
        0xC0000, 0xE0000,
             0, 0,
             0, 0,
             0, 0,
             0, 0
        },
        { // vex1
             (stream_count - MAX_STREAM_COUNT_PER_VEX),
             vectors_per_block / stream_count,
             g_max_blocks,
             2, // ping pong double buffer

             // Tx path inputs
             0, // ret_cycle_val, // not being used for now
        0x100000, 0x120000,
        0x140000, 0x160000,
        0x180000, 0x1A0000,
        0x1C0000, 0x1E0000,
             0, 0,
             0, 0,
             0, 0,
             0, 0
        }
#else
        { // vex0
             (stream_count > MAX_STREAM_COUNT_PER_VEX ? MAX_STREAM_COUNT_PER_VEX : stream_count),
             vectors_per_block / stream_count,
             g_max_blocks,
             2, // ping pong double buffer

             // Tx path inputs
             0, // ret_cycle_val, // not being used for now
        0x00000, 0x10000,
        0x20000, 0x30000,
        0x40000, 0x50000,
        0x60000, 0x70000,
             0, 0,
             0, 0,
             0, 0,
             0, 0
        },
        { // vex1
             (stream_count - MAX_STREAM_COUNT_PER_VEX),
             vectors_per_block / stream_count,
             g_max_blocks,
             2, // ping pong double buffer

             // Tx path inputs
             0, // ret_cycle_val, // not being used for now
        0x80000, 0x90000,
        0xa0000, 0xb0000,
        0xc0000, 0xd0000,
        0xe0000, 0xf0000,
             0, 0,
             0, 0,
             0, 0,
             0, 0
        }
#endif
    };
    vex_rx_val_kargs = (uint32_t *) (&(vex_rx_val_kargs_arr[rx_vex_id]));

    unsigned val_out[MAX_VECTOR_COUNT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned val_out_stream[MAX_VECTOR_COUNT * NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];

    LOG_PRINT("INFO: config begins\n");

    // SDF init
    if (rv = write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(VEX_BASE(rx_vex_id)),
                           HIVE_ADDR_jesd_rx_tx_lpbk_consumer_sm_gate,
                           VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                           "BPCA_BP_DMEM"))
        return rv;

    printf("HOST:  SDF init done for vex %d\n", rx_vex_id);

    // for (i = 0; i < 1; i++)
    // {
    //     //~ if(1 == i) vex_num = tx_vex;

    //     if (vex_mem_clear(rx_vex_id, srp))
    //     {
    //         printf("ERROR: Failed to clear memories of VEX%d\n", rx_vex_id);
    //         return -1;
    //     }
    //     printf("HOST: Cleared memories of VEX%d\n", rx_vex_id);
    // }

    {
        if ((rv = vex_loader(rx_vex_id,
                             // "vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
                             vex_fw_file_path)))
            return rv;
        printf("HOST: Loaded %s to vex core %d\n", vex_fw_file_path, rx_vex_id);
    }
    printf("HOST: VEX program load - done\n");

    write_reg_18a(vex_dmem_base_addr + HIVE_ADDR_jesd_rx_tx_lpbk_consumer_sm_gate + (CONSUMER_SM_BUF_ID * 4), 0, 1, "consumer_sm_gate_clear");

    for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        write_mem_18a(vex_dmem_base_addr + vex_rx_offset_val[lc], 1, &vex_rx_val_kargs[lc], "Val_kargs");
        printf("HOST: Loaded offset 0x%x with value  0x%x\n", vex_dmem_base_addr + vex_rx_offset_val[lc], vex_rx_val_kargs[lc]);
    }
    printf("HOST: Loaded host params to Rx vex core %d\n", rx_vex_id);

    int temp = 0;

    read_mem_18a(vex_dmem_base_addr + HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_num_vecs_in, 1, &temp, "num_vecs_in");
    printf("HOST: value @ HIVE_ADDR_jesd_rx_tx_lpbk_g_rx_num_vecs_in = %d\n", temp);

    int sample_count = vex_rx_val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC;
    printf("HOST: sample_count = %d\n", sample_count);

    vex_start(rx_vex_id, 0);
    printf("dumping VEX-%d cio2strm_word_cnt - FIFO Word Counter\n",rx_vex_id);
	system("srpRead 0x02801024  1");
	printf("\n");

	printf("reading vex time_out cycles\n");
	system("srpRead 0x63.0.0x4030 1");
    printf("\n");

    printf("dumping jesd B2H flit count\n");
    system("srpRead 0x06704014 1");
    printf("\n");

    return rv;
#endif
}
/**
 * @brief           Function to dump jesd registers EOT in Rx path
 * @param [in]      jesd_id
 * @return          status
 */

int dump_rx_registers()
{
 printf("\n");
    printf("printing cio2strm_credit_count  \n");
        system("srpRead 0x02801008  1");
    printf("printing cio2strm_credit_count_stat  \n");
        system("srpRead 0x0280100c  1");
    printf("printing cio2strm_fifo_status_ctl  \n");
        system("srpRead 0x02801010   1");
    printf("printing cio2strm_fifo_status_ctl  \n");
        system("srpRead 0x02801010   1");
    printf("printing cio2strm_fifo_status  \n");
        system("srpRead 0x02801014    1");
    printf("printing cio2strm_int_status  \n");
        system("srpRead 0x02801040     1");

 printf("\n");
    printf("printing B2H_FIFO_STATUS  \n");
        system("srpRead 0x0670400c   1");
    printf("printing B2H_CREDIT_CS  \n");
        system("srpRead 0x06704010    1");
    printf("printing B2H_FLIT_COUNT  \n");
        system("srpRead 0x06704014    1");

 printf("\n");
    printf("printing H2B_FIFO_CONTROL  \n");
        system("srpRead 0x6704308 1");
    printf("printing H2B_FIFO_STATUS  \n");
        system("srpRead 0x0670430c  1");
    printf("printing H2B_FLIT_COUNT  \n");
        system("srpRead 0x06704314  1");

    printf("printing NSIP_HBI_H2B_CREDIT_READY_CS  \n");
        system("srpRead 0x6704310 1");
    printf("printing NSIP_HBI_INST_STATUS  \n");
        system("srpRead 0x6704080 1");
    printf("\n");
    printf("printing H2B_BUF_SZ_HW_TBL0  \n");
        system("srpRead 0x6704380 1");
    printf("printing H2B_BUF_SZ_HW_TBL1  \n");
        system("srpRead 0x6704384 1");
    printf("printing H2B_BUF_SZ_HW_TBL2  \n");
        system("srpRead 0x6704388 1");
    printf("printing H2B_BUF_SZ_HW_TBL3  \n");
        system("srpRead 0x670438c 1");
    printf("printing H2B_BUF_SZ_HW_TBL4  \n");
        system("srpRead 0x6704390 1");
    printf("printing H2B_BUF_SZ_HW_TBL5  \n");
        system("srpRead 0x6704394 1");
    printf("printing H2B_BUF_SZ_HW_TBL6  \n");
        system("srpRead 0x6704398 1");
    printf("printing H2B_BUF_SZ_HW_TBL7  \n");
        system("srpRead 0x670439c 1");
    printf("\n");

    printf("printing H2B_ROUTE_LKUP_TBL0  \n");
        system("srpRead 0x6704480 1");
    printf("printing H2B_ROUTE_LKUP_TBL1  \n");
        system("srpRead 0x6704484 1");
    printf("printing H2B_ROUTE_LKUP_TBL2  \n");
        system("srpRead 0x6704488 1");
    printf("printing H2B_ROUTE_LKUP_TBL3  \n");
        system("srpRead 0x670448c 1");
    printf("printing H2B_ROUTE_LKUP_TBL4  \n");
        system("srpRead 0x6704490 1");
    printf("printing H2B_ROUTE_LKUP_TBL5  \n");
        system("srpRead 0x6704494 1");
    printf("printing H2B_ROUTE_LKUP_TBL6  \n");
        system("srpRead 0x6704498 1");
    printf("printing H2B_ROUTE_LKUP_TBL7  \n");
        system("srpRead 0x670449c 1");
    printf("\n");

    printf("printing H2B_TK_ADDR_LKUP_TBL0  \n");
        system("srpRead 0x6704500 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL1  \n");
        system("srpRead 0x6704504 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL2  \n");
        system("srpRead 0x6704508 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL3  \n");
        system("srpRead 0x670450c 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL4  \n");
        system("srpRead 0x6704510 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL5  \n");
        system("srpRead 0x6704514 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL6  \n");
        system("srpRead 0x6704518 1");
    printf("printing H2B_TK_ADDR_LKUP_TBL7  \n");
        system("srpRead 0x670451c 1");
    printf("\n");

    printf("printing H2B_TK_ROUTE_LKUP_TBL0  \n");
        system("srpRead 0x6704580 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL1  \n");
        system("srpRead 0x6704584 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL2  \n");
        system("srpRead 0x6704588 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL3  \n");
        system("srpRead 0x670458c 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL4  \n");
        system("srpRead 0x6704590 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL5  \n");
        system("srpRead 0x6704594 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL6  \n");
        system("srpRead 0x6704598 1");
    printf("printing H2B_TK_ROUTE_LKUP_TBL7  \n");
        system("srpRead 0x670459c 1");
    printf("\n");

    printf("printing H2B_MD_ROUTE_LKUP_TBL0  \n");
        system("srpRead 0x6704680 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL1  \n");
        system("srpRead 0x6704684 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL2 \n");
        system("srpRead 0x6704688 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL3 \n");
        system("srpRead 0x670468c 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL4 \n");
        system("srpRead 0x6704690 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL5 \n");
        system("srpRead 0x6704694 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL6 \n");
        system("srpRead 0x6704698 1");
    printf("printing H2B_MD_ROUTE_LKUP_TBL7 \n");
        system("srpRead 0x670469c 1");
    printf("\n");

    printf("printing H2B_MD_CONTROL_TBL0  \n");
        system("srpRead 0x6704700 1");
    printf("printing H2B_MD_CONTROL_TBL1  \n");
        system("srpRead 0x6704704 1");
    printf("printing H2B_MD_CONTROL_TBL2  \n");
        system("srpRead 0x6704708 1");
    printf("printing H2B_MD_CONTROL_TBL3  \n");
        system("srpRead 0x670470c 1");
    printf("printing H2B_MD_CONTROL_TBL4  \n");
        system("srpRead 0x6704710 1");
    printf("printing H2B_MD_CONTROL_TBL5  \n");
        system("srpRead 0x6704714 1");
    printf("printing H2B_MD_CONTROL_TBL6  \n");
        system("srpRead 0x6704718 1");
    printf("printing H2B_MD_CONTROL_TBL7  \n");
        system("srpRead 0x670471c 1");
    printf("\n");

    printf("printing H2B_ADDR_LKUP_TBL0  \n");
        system("srpRead 0x6704400 1");
    printf("printing H2B_ADDR_LKUP_TBL1  \n");
        system("srpRead 0x6704404 1");
    printf("printing H2B_ADDR_LKUP_TBL2  \n");
        system("srpRead 0x6704408 1");
    printf("printing H2B_ADDR_LKUP_TBL3  \n");
        system("srpRead 0x670440c 1");
    printf("printing H2B_ADDR_LKUP_TBL4  \n");
        system("srpRead 0x6704410 1");
    printf("printing H2B_ADDR_LKUP_TBL5  \n");
        system("srpRead 0x6704414 1");
    printf("printing H2B_ADDR_LKUP_TBL6  \n");
        system("srpRead 0x6704418 1");
    printf("printing H2B_ADDR_LKUP_TBL7  \n");
        system("srpRead 0x670441c 1");
    printf("\n");

    printf("printing STRM2CIO_INT_EN  \n");
        system("srpRead 0x2802044 1");
    printf("printing STRM2CIO_FIFO_STAT_CTL  \n");
        system("srpRead 0x2802010 1");
    printf("printing STRM2CIO_WORD_CNT_CTL  \n");
        system("srpRead 0x2802020 1");
    printf("\n");

 printf("\n");
    printf("printing RX CMN/CSR registers  \n");
    printf("printing RX IP CLK_CTRL   \n");
        system("srpRead 0x06706090  1");
    printf("printing RX_SYSREF_TSAD \n");
        system("srpRead 0x06706094  1");
    printf("printing RX_SYNC_POINT_CTRL   \n");
        system("srpRead 0x06706098  1");
    printf("printing RX_CLK_1P5G_DIV_ENABLE \n");
        system("srpRead 0x067060a0 1");
    printf("printing RX_CLK_GEN_ENABLE   \n");
        system("srpRead 0x067060a4  1");
    printf("printing RX_BFN_SYNC_POINT_CTRL   \n");
        system("srpRead 0x067060c8  1");
    printf("printing RX_BFN_SYNC_POINT_CNT_ENABLE   \n");
        system("srpRead 0x067060cc  1");

 printf("\n");
    printf("printing RX JESD CRUX Clock registers  \n");
    printf("printing RX_STRM_CFG   \n");
        system("srpRead 0x0670c010  1");
    printf("printing RX_MEM_STREAM_CFG   \n");
        system("srpRead 0x0670c014   1");
    printf("printing RX_WR_MEM_TBL0   \n");
        system("srpRead 0x0670c180  1");
    printf("printing RX_WR_MEM_TBL1   \n");
        system("srpRead 0x0670c184  1");
    printf("printing RX_WR_MEM_TBL2   \n");
        system("srpRead 0x0670c188  1");
    printf("printing RX_WR_MEM_TBL3   \n");
        system("srpRead 0x0670c18c  1");
    printf("printing RX_WR_MEM_TBL4   \n");
        system("srpRead 0x0670c190  1");
    printf("printing RX_WR_MEM_TBL5   \n");
        system("srpRead 0x0670c194  1");
    printf("printing RX_WR_MEM_TBL6   \n");
        system("srpRead 0x0670c198  1");
    printf("printing RX_WR_MEM_TBL7   \n");
        system("srpRead 0x0670c19c  1");

    printf("printing RX_RD_MEM_TBL0   \n");
        system("srpRead 0x0670c1c0  1");
    printf("printing RX_RD_MEM_TBL1   \n");
        system("srpRead 0x0670c1c4  1");
    printf("printing RX_RD_MEM_TBL2   \n");
        system("srpRead 0x0670c1c8  1");
    printf("printing RX_RD_MEM_TBL3   \n");
        system("srpRead 0x0670c1cc  1");
    printf("printing RX_RD_MEM_TBL4   \n");
        system("srpRead 0x0670c1d0  1");
    printf("printing RX_RD_MEM_TBL5   \n");
        system("srpRead 0x0670c1d4  1");
    printf("printing RX_RD_MEM_TBL6   \n");
        system("srpRead 0x0670c1d8  1");
    printf("printing RX_RD_MEM_TBL7   \n");
        system("srpRead 0x0670c1dc  1");

 printf("\n");
    printf("printing strm2cio_reg_map  \n");
    printf("printing strm2cio_credit_count   \n");
        system("srpRead 0x0280200c    1");
    printf("printing strm2cio_fifo_status_ctl   \n");
        system("srpRead 0x02802010     1");
    printf("printing strm2cio_fifo_status   \n");
        system("srpRead 0x02802014     1");
    printf("printing strm2cio_int_status   \n");
        system("srpRead 0x02802040      1");



 printf("\n");
    printf("printing RX JESD GLUE registers  \n");
    printf("printing RX_GLUE_SONI   \n");
        system("srpRead 0x06707010   1");
    printf("printing RX_DATAPATH_GATE_SEL   \n");
        system("srpRead 0x06707014    1");
    printf("printing RX_DATAPATH_INIT_CYC_CNT   \n");
        system("srpRead 0x0670701c     1");

 printf("\n");
    printf("printing RX JESD IP registers  \n");
    printf("printing L_REG   \n");
        system("srpRead 0x06702030   1");
    printf("printing M_REG   \n");
        system("srpRead 0x06702038   1");
    printf("printing F_REG   \n");
        system("srpRead 0x06702028   1");
    printf("printing RX_THRESH_EMB_ERR_REG   \n");
        system("srpRead 0x06702360   1");
    printf("printing RX_THRESH_SH_ERR_REG   \n");
        system("srpRead 0x06702364   1");
    printf("printing SONIF_REG   \n");
        system("srpRead 0x06702368   1");
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
 * @brief           Function to dump memory using rad_mem_18a to avoid srp_read call
 * @param           [in] base_address start address
 * @param           [in] display_size number of word ( 32bit) value to be display
 * @return          none
 */
void print_mem(uint32_t base_address, uint32_t display_size)
{
    uint32_t dump_array[MAX_VMEM_SAMPLE_DUMP_COUNT] ={0};
    // memset(dump_array, 0, sizeof(dump_array))
    if( display_size > MAX_VMEM_SAMPLE_DUMP_COUNT )
    {
		// put the log - display size exceeds limit of MAX_VMEM_SAMPLE_DUMP_COUNT. limiting the dump to MAX_VMEM_SAMPLE_DUMP_COUNT.
		display_size = MAX_VMEM_SAMPLE_DUMP_COUNT;
	}
    read_mem_18a(base_address, display_size, dump_array, "num_vecs_in");
    for ( int i = 0; i< display_size; i++){
        printf(" 0x%0.8x:", (base_address+i)*4); // byte aligned address
        printf(" %0.8x ", dump_array[i++]); // word aligned value
        if (i < display_size)
            printf(" %0.8x ", dump_array[i++]); // word aligned value
        if (i < display_size)
            printf(" %0.8x ", dump_array[i++]); // word aligned value
        if (i < display_size)
            printf(" %0.8x ", dump_array[i]); // word aligned value
        printf("\n");
    }    
}

/**
 * @brief           Function to customized dump RX VEX mem to check captured data
 * @param [in]
 * @return          status
 */
int dump_vmem_vex_rx_2(uint32_t rx_vex_id)
{
#ifdef E2E_FLOW_EN
    UNUSED(rx_vex_id);
    return 0;
#else //!E2E_FLOW_EN
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (rx_vex_id * vex_dmem_offset);

    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (rx_vex_id * vex_vmem_offset);
    char srp_read_cmd[50] = {0};
    int base_address = RX_SRC_BUFFER_BASE_SRP;//0x28000;
    int buffer_size = 512; 
    int samples_per_block = ((int *)g_samples_per_block)[jesd_config.jesd_link_config.link_iq_bw];

    // int buffer_size = 1024;
    // int display_size = PAYLOAD_SIZE_SAMPLES_PER_STREAM + 32;
    int display_size = 64;
    int it = 0;
    int no_of_stream = 1;
    int next_address = 0;
    uint32_t iter_count = 0;

    no_of_stream = jesd_config.jesd_link_config.converters/2;
    buffer_size = ((samples_per_block*SAMPLE_SIZE_BYTE) / no_of_stream) ; // bytes // decide based on usecase'rate and stream count  
    display_size = samples_per_block / no_of_stream; // 128 //samples
    printf("DMem dump for vex_id=%d\n", rx_vex_id);
    print_mem(vex_dmem_base_addr, 64);


    printf("VEX filled pattern for vex_id=%d\n", rx_vex_id);
    print_mem(vex_vmem_base_addr+RX_SRC_BUFFER_OFFSET,64);

    printf("\n===========\n");

    // 64 flits
    printf("incoming  streams for vex_id=%d\n", rx_vex_id);

    base_address = vex_vmem_base_addr + RX_DEST_BUFFER_OFFSET;
    next_address = 0;
    iter_count = (no_of_stream > MAX_STREAM_COUNT_PER_VEX) ? MAX_STREAM_COUNT_PER_VEX: no_of_stream;
    for (it = 0; it < iter_count; it++)
    {
        next_address = base_address + buffer_size * it *2; // *2 for ping pong buffer
        print_mem(next_address, display_size*2); // *2 for ping pong buffer
        printf("\n===========\n");
    }

    printf("Debug block dump for vex_id=%d\n", rx_vex_id);
    base_address = vex_vmem_base_addr+RX_DEBUG_BUFFER_OFFSET;
    next_address = 0;
    for (it = 0; it < iter_count; it++)
    {
        next_address = base_address + buffer_size * it;
        printf("\n=====Stream %d======\n", it);
        print_mem(next_address, display_size);
        printf("\n===========\n");
    }
	

#endif // !E2E_FLOW_EN
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


//dump jesd_tx_4k samples
static int dump_tx_ip_4k()
{
    uint32_t red_reg0 = 0, red_reg1 = 0, red_reg2 = 0, red_reg3 = 0, red_reg4 = 0, red_reg5 = 0, red_reg6 = 0, red_reg7 = 0, red_reg8 = 0, red_reg9 = 0, red_reg10 = 0, red_reg11 = 0;
    uint32_t red_reg12 = 0, red_reg13 = 0, red_reg14 = 0, red_reg15 = 0, red_reg16 = 0, red_reg17 = 0, red_reg18 = 0, red_reg19 = 0, red_reg20 = 0, red_reg21 = 0, red_reg22 = 0, red_reg23 = 0;
    uint32_t red_reg24 = 0, red_reg25 = 0, red_reg26 = 0, red_reg27 = 0, red_reg28 = 0, red_reg29 = 0, red_reg30 = 0, red_reg31 = 0, red_reg32 = 0, red_reg33 = 0,  red_reg34 = 0, red_reg35 = 0;
    uint32_t red_reg36 = 0, red_reg37 = 0, red_reg38 = 0, red_reg39 = 0, red_reg40 = 0, red_reg41 = 0, red_reg42 = 0, red_reg43 = 0, red_reg44 = 0, red_reg45 = 0, red_reg46 = 0, red_reg47 = 0;
    uint32_t red_reg48 = 0, red_reg49 = 0, red_reg50 = 0, red_reg51 = 0, red_reg52 = 0, red_reg53 = 0, red_reg54 = 0, red_reg55 = 0, red_reg56 = 0, red_reg57 = 0,  red_reg58 = 0, red_reg59 = 0;
    uint32_t red_reg60 = 0, red_reg61 = 0, red_reg62 = 0, red_reg63 = 0, red_reg64 = 0;
    uint32_t capture_clear = 0;
    uint32_t capture_status = 0;
    static int g_jesd_tx_glue_base_addr[4]      = {DLNK_JESD0_TX_GLUE_BASE, DLNK_JESD1_TX_GLUE_BASE, DLNK_JESD2_TX_GLUE_BASE, DLNK_JESD3_TX_GLUE_BASE};

    uint32_t count = 0;
    // while(1)
    while(count < 5)
    {
        //printf("####\n");
        capture_status = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_CAP_STAT_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_CAP_STAT");
        printf("\n\n####capture status is %x \n",capture_status);
        delay(1000);
        //if(capture_status == 0)
        //{
            red_reg0 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA0_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA0");
            red_reg1 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA1_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA1");
            red_reg2 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA2_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA2");
            red_reg3 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA3_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA3");
            red_reg4 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA4_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA4");
            red_reg5 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA5_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA5");
            red_reg6 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA6_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA6");
            red_reg7 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA7_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA7");
            red_reg8 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA8_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA8");
            red_reg9 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA9_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA9");
            red_reg10 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA10_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA10");
            red_reg11 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA11_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA11");
            red_reg12 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA12_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA12");
            red_reg13 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA13_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA13");
            red_reg14 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA14_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA14");
            red_reg15 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA15_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA15");
            red_reg16 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA16_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA16");
            red_reg17 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA17_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA17");
            red_reg18 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA18_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA18");
            red_reg19 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA19_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA19");
            red_reg20 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA20_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA20");
            red_reg21 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA21_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA21");
            red_reg22 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA22_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA22");
            red_reg23 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA23_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA23");
            red_reg24 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA24_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA24");
            red_reg25 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA25_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA25");
            red_reg26 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA26_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA26");
            red_reg27 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA27_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA27");
            red_reg28 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA28_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA28");
            red_reg29 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA29_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA29");
            red_reg30 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA30_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA30");
            red_reg31 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA31_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA31");
            red_reg32 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA32_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA32");
            red_reg33 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA33_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA33");
            red_reg34 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA34_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA34");
            red_reg35 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA35_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA35");
            red_reg36 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA36_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA36");
            red_reg37 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA37_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA37");
            red_reg38 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA38_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA38");
            red_reg39 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA39_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA39");
            red_reg40 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA40_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA40");
            red_reg41 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA41_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA41");
            red_reg42 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA42_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA42");
            red_reg43 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA43_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA43");
            red_reg44 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA44_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA44");
            red_reg45 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA45_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA45");
            red_reg46 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA46_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA46");
            red_reg47 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA47_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA47");
            red_reg48 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA48_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA48");
            red_reg49 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA49_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA49");
            red_reg50 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA50_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA50");
            red_reg51 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA51_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA51");
            red_reg52 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA52_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA52");
            red_reg53 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA53_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA53");
            red_reg54 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA54_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA54");
            red_reg55 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA55_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA55");
            red_reg56 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA56_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA56");
            red_reg57 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA57_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA57");
            red_reg58 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA58_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA58");
            red_reg59 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA59_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA59");
            red_reg60 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA60_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA60");
            red_reg61 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA61_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA61");
            red_reg62 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA62_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA62");
            red_reg63 = read_reg_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_INTF_DATA63_OFFSET, "JESD_TX_GLUE_IP_SMPL_INTF_DATA63");
            
            printf("jesd tx 4k reg is as follows\n");
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
            
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_OFFSET, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_DEFAULT, 0x01, 0x01, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_RD_MASK, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_WR_MASK, "JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT");
            write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_OFFSET, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_DEFAULT, 0x00, 0x00, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_RD_MASK, JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_WR_MASK, "JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT");
            
        /*}
        else
        {
            printf("status is still zero :\n");
        }*/
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

//for capturing 4k at Tx
int tx_smpl_intf_cap_en(uint32_t tx_jesd_id)
{
    int jesd_tx_glue_base = g_jesd_tx_glue_base_addr[tx_jesd_id];
    
    
    
    write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_IP_SMPL_INTF_CAP_EN_OFFSET,
                            0x1,
                            JESD_TX_GLUE_IP_SMPL_INTF_CAP_EN_WR_MASK,
                            "JESD_TX_GLUE_IP_SMPL_INTF_CAP_EN");
    
    //Added by Aditya for debug
    write_reg_18a(jesd_tx_glue_base + JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_OFFSET,
                            0x1,
                            JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT_WR_MASK,
                            "JESD_TX_GLUE_IP_SMPL_INTF_CAP_CLR_STAT");
}

int read_samples_from_file( char * file_name, unsigned sample_count, unsigned *output_stream_array_ptr)
{
    int ret_value= 0;
    FILE *fptr;


    if( file_name == NULL || output_stream_array_ptr == NULL )
        return -1;

    printf("HOST: Output reference sample file : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if (NULL == fptr)
    {
        printf("ERROR: Not able to open the output file\n");
        fclose(fptr);
        return -1;
    }

    // sample_count = vex_rx_val_kargs[1] * NUM_OF_ELEMENTS_PER_VEC;

    if (vector_read_hex_u32(fptr,
                            (int *)output_stream_array_ptr,
                            sample_count) < sample_count) // 32 *32 = 1024
    {
        printf("ERROR: Insufficient output samples\n");
        fclose(fptr);
        return -1;
    }
    fclose(fptr);

    printf("HOST: sample_count = %d\n", sample_count);

    // int ii = 0;
    // for (ii = 0; ii < sample_count; ii++)
    // {
    //     printf("HOST:  = 0x%0.8x\n", ((int *)val_out)[ii]);
    // }

    return ret_value;
}
int get_samples_for_stream( unsigned sample_count, unsigned stream_id, unsigned *input_stream_0_array_ptr, unsigned *output_stream_array_ptr)
{
    int ret_value= 0;
    int ii = 0;

    if( input_stream_0_array_ptr == NULL || output_stream_array_ptr == NULL )
        return -1;

    // for (ii = 0; ii < sample_count; ii++)
    // {
    //     printf("HOST:  = 0x%0.8x\n", ((int *)val_out)[ii]);
    // }

    for (ii = 0; ii < sample_count; ii++)
    {
        // printf("HOST:  = 0x%0.8x\n", ((int *)val_out)[ii]);

        output_stream_array_ptr[ii] = (input_stream_0_array_ptr[ii] & 0x0FFF0FFF) | ((stream_id << 12)& 0x0000F000) | ((stream_id << 28)& 0xF0000000);
    }

    return ret_value;
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
        printf("########Prefil of 512 flits of RSB to 0 done\n\n");
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

    uint32_t no_of_strms = jesd_config.jesd_link_config.converters / 2;
    uint32_t total_no_flits = 512;
    uint32_t flits_per_stream = total_no_flits/no_of_strms;
    uint32_t start_offset = 0;
    uint32_t end_offset = 0;
    uint32_t loop = 0;
    int shift =0x0;
    
    printf("\n########Starting to prefil 512 flits of RSB to unique data with unique stream ID\n");
    while(loop < no_of_strms)
    {
        end_offset = start_offset + flits_per_stream;
        for(i=0; i<1; i++)
        {
            flit_data = 0;
            test  = shift << 28;
            flit_data = (flit_data | test);
            //printf("flit data is %x \n",flit_data);
            for(flit_count_pre = start_offset; flit_count_pre < end_offset; flit_count_pre++)
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
        }
        start_offset = end_offset;
        loop++;
        shift++;
    }
    printf("########Prefil of RSB to unique data with unique stream id done\n");
}


//fuction to dump rsb
//pass 0 - to dump all flits
//pass 1 - to dump 4 flits only
static int dump_rsb(int four_flits_only)
{
    //going to dump RSB 8 streams
    int fill_level_array[16];
    int dump_only_4_flits = 0;
    int i = 0;
    int flit_count = 0;
    uint32_t value38=0; uint32_t value39=0; uint32_t value40=0; uint32_t value41=0; uint32_t value42=0; uint32_t value43=0; uint32_t value44=0; uint32_t value45=0;
    uint32_t value46, value47, value48, value49, value50, value51, value52, value53 = 0;
    uint32_t stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer = 0;
    uint32_t stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer = 0;
    int base_address_crux_clk_csr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};

    printf("\n\n###Going to dump RSB buffer\n");
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
        value46 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS8_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS8");
        value47 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS9_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS9");
        value48 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS10_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS10");
        value49 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS11_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS11");
        value50 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS12_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS12");
        value51 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS13_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS13");
        value52 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS14_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS14");
        value53 = read_reg_18a(base_address_crux_clk_csr[i] + JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS15_OFFSET, "JESDABC_CRUX_CLK_CSR_RX_STRM_STS15");
    }

    fill_level_array[0] = ((value38 & 0x400) >> 10);
    fill_level_array[1] = ((value39 & 0x400) >> 10);
    fill_level_array[2] = ((value40 & 0x400) >> 10);
    fill_level_array[3] = ((value41 & 0x400) >> 10);
    fill_level_array[4] = ((value42 & 0x400) >> 10);
    fill_level_array[5] = ((value43 & 0x400) >> 10);
    fill_level_array[6] = ((value44 & 0x400) >> 10);
    fill_level_array[7] = ((value45 & 0x400) >> 10);
    fill_level_array[8] = ((value45 & 0x400) >> 10);
    fill_level_array[9] = ((value45 & 0x400) >> 10);
    fill_level_array[10] = ((value45 & 0x400) >> 10);
    fill_level_array[11] = ((value45 & 0x400) >> 10);
    fill_level_array[12] = ((value45 & 0x400) >> 10);
    fill_level_array[13] = ((value45 & 0x400) >> 10);
    fill_level_array[14] = ((value45 & 0x400) >> 10);
    fill_level_array[15] = ((value45 & 0x400) >> 10);

    uint32_t flow_value      = 0;
    uint32_t loop            = 0;
    uint32_t no_of_strms     = jesd_config.jesd_link_config.converters / 2;
    flow_value               = jesd_tc_config.flow_id;

    //if rsb source mode, then make all fill level = 1, roshan 08/07/24
    if((flow_value == flow_rx_rsb_src_mode) || (flow_value == flow_tx_tsb_cap_mode))
    {
        printf("###RSB source mode is configured, so making all RSB fill status for all streams to '1', to enable RSB dump\n");
        for(loop =0; loop < no_of_strms; loop ++)
        {
            fill_level_array[loop] = 1;
        }
    }

    loop = 0;
    uint32_t total_no_flits = 512;
    uint32_t flits_per_stream = total_no_flits/no_of_strms;
    uint32_t start_offset = 0;
    uint32_t end_offset = 0;

    //check if dumping 4 flits is enabled or not
    dump_only_4_flits = four_flits_only;

    while(loop < no_of_strms)
    {
        if(fill_level_array[loop] == 1)
        {
            printf("\n###buffer %d is full \n",loop);
            i=0;
            end_offset = start_offset + flits_per_stream;
            for(i=0; i<1; i++)
            {
                for(flit_count = start_offset; flit_count < end_offset; flit_count++)
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
                    
                    if(dump_only_4_flits == 1)
                    {
                        if(flit_count < (start_offset + 4))
                        {    
                            printf("flit count is %d \n",flit_count);
                            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
                        }
                    }
                    else if(dump_only_4_flits == 0)
                    {
                        printf("flit count is %d \n",flit_count);
                        printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
                    }
                    else
                    {
                        printf("$$$$$$$ select between either dumping all flits or four flits per stream \n");
                    }
                }
            }
        }
        else
        {
            printf("###buffer %d is not full \n",loop);
        }
        start_offset = end_offset;
        loop++;
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
    uint32_t flow_value  = jesd_tc_config.flow_id;

    if((flow_value == flow_tsb_src_rsb) || (flow_value == flow_tsb_src_dnrt))
    {
        value38 = 1;
        printf("\n#####TSB dump is enabled for TSB SRC mode\n");
    }

    if(value38 == 0)
    {
        printf("#######buffer is not full\n");
    }
    else
    {
        printf("###############buffer 0 is full\n");
        printf("###TSB buffer0 0-64 flits \n");

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

        for(flit_count=0; flit_count < MAX_FLIT_COUNT_TO_FILL; flit_count++)
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

static int prefill_tsb_uniq_data()
{
    int i=0;

    int jesd_crux_clk_csr_base = g_jesd_crux_clk_csr_base_addr[0];

    uint32_t no_of_strms = jesd_config.jesd_link_config.converters / 2;
    uint32_t str_id = 0;

    uint32_t buff_id = 0;
    uint32_t tot_tx_mem_blk = 0x10;
    uint32_t tx_mem_blk_per_stream = tot_tx_mem_blk/no_of_strms;

    uint32_t wr_addr_max = 64;
    uint32_t wr_addr = 0;
    uint32_t wr_buff_sel_bit = 0;
    uint32_t wr_buff_en = 0;
    uint32_t tx_wr_addr = 0;
    uint32_t rd_addr = 0;

    uint32_t data_count = 0;
    uint32_t str_id_data = 0;

    uint32_t buff_id_data = 0;
    uint32_t buff_data = 0;
    int buff_data_array[16];

    uint32_t stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer = 0;
    uint32_t stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer = 0;

    printf("\n########Starting to prefill TSB to unique data with unique stream ID\n");

    for(str_id = 0; str_id < no_of_strms; str_id++)
    {
        for(buff_id = 0; buff_id < tx_mem_blk_per_stream; buff_id++)
        {
            for(wr_addr = 0; wr_addr < wr_addr_max; wr_addr++)
            {
                wr_buff_sel_bit = buff_id + 0x6;
                wr_buff_en = (1 << wr_buff_sel_bit);
                tx_wr_addr = (wr_addr | wr_buff_en);

                //printf("wr_addr is %x \n",wr_addr);       //roshan commenting, filling up terminal 05/08/24
                //printf("tx_wr_addr is %x \n",tx_wr_addr); //roshan commenting, filling up terminal 05/08/24

                //rd_buff_sel_bit = buff_id + 0x6;
                //rd_buff_en = (1 << rd_buff_sel_bit);
                //rd_addr = (wr_addr | rd_buff_en);
                rd_addr = wr_addr;

                for(data_count = 0; data_count < 16; data_count++)
                {
                    /*buff_id_data  = (buff_id << 28);
                    buff_data = (buff_id_data | buff_data);
                    buff_data_array[data_count] = buff_data;
                    //print("buff_data_array[%d] is %x\n",data_count, buff_data_array[data_count]);
                    buff_data++;*/

                    buff_data_array[data_count] = buff_data;
                    //print("buff_data_array[%d] is %x\n",data_count, buff_data_array[data_count]); //roshan commenting, filling up terminal 05/08/24
                    buff_data++;
                }

                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_OFFSET, JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_DEFAULT, tx_wr_addr, tx_wr_addr, JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_WR_MASK, "JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR");

                // 16 registers *32 bit = 512 bit data 
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[0], buff_data_array[0], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[1], buff_data_array[1], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[2], buff_data_array[2], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[3], buff_data_array[3], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[4], buff_data_array[4], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[5], buff_data_array[5], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[6], buff_data_array[6], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[7], buff_data_array[7], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[8], buff_data_array[8], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[9], buff_data_array[9], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[10], buff_data_array[10], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[11], buff_data_array[11], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[12], buff_data_array[12], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[13], buff_data_array[13], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[14], buff_data_array[14], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, buff_data_array[15], buff_data_array[15], JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15");

                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");   
                //printf("########Prefil of TSB to unique data with unique stream id done\n"); //roshan commenting, filling up terminal 05/08/24

               /*
                //TSB capture mode is enabled
                printf("\ntsb capture is enabled\n");
                write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");

                // Read back through APB 
                printf("########Read back of TSB stream id 0 buff 0 done\n");
                write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");

                write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_APB_RADDR_OFFSET, JESD_TX_GLUE_APB_RADDR_DEFAULT, rd_addr, rd_addr, JESD_TX_GLUE_APB_RADDR_RD_MASK, JESD_TX_GLUE_APB_RADDR_WR_MASK, "JESD_TX_GLUE_APB_RADDR");
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
*/
            }
        }
    }
    write_read_expect_18a(jesd_crux_clk_csr_base + JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");
    printf("########Prefil of TSB to unique data with unique stream id done\n");


}


int calc_timer()
{
    /* timer value =((sample_req_pos_cycles+sample_req_neg_cycles)*(512/(soni*8))*(number_of_flits_per_stream)*(sample_clk_div_ratio)); */

    uint32_t soni                          = 0;
    uint32_t num_of_streams                = 0;
    uint32_t number_of_flits_per_stream    = 0;
    double   sample_clk                    = 0;
    double   crux_clk                      = 0;
    uint32_t sample_transactions_pos       = 0;
    uint32_t sample_transactions_neg       = 0;
    uint32_t sum_pos_sample_and_neg_sample = 0;
    uint32_t link_bw                       = 0;
    uint32_t l_value_in_flits              = 0; 
    uint32_t timer                         = 0;
    double sample_clk_div_ratio            = 0;

    soni                          = jesd_config.jesd_link_config.sonif;
    num_of_streams                = jesd_config.jesd_link_config.converters / 2;
    sample_clk                    = jesd_config.jesd_link_config.sample_rate;
    sample_transactions_pos       = jesd_config.jesd_link_config.smpl_trans_pos;
    sample_transactions_neg       = jesd_config.jesd_link_config.smpl_trans_neg;
    sum_pos_sample_and_neg_sample = sample_transactions_pos + sample_transactions_neg;
    // link_bw                       = jesd_config.jesd_link_config.link_iq_bw; //
    crux_clk                      = 983.00;

    //timer calculations will update in next code push, roshan 24/08/24
    //will revisit after imp bringups
    //TODO fix me
    if(jesd_tc_config.usecase_id  == 25)
    {    
        sample_clk                    = 245.76;   //hardcoded for 8g, usecase 1a
        printf("###usecase 1a is selected assigning clk of 245.76 \n");
    }

    sample_clk_div_ratio          = crux_clk/sample_clk;

    // if(e_LINK_IQ_BW_GSPS_2P0 == link_bw)
    //     l_value_in_flits = 64;
    // else if(e_LINK_IQ_BW_GSPS_1P0 == link_bw)
    //     l_value_in_flits = 32;
    // else if(e_LINK_IQ_BW_GSPS_0P5 == link_bw)
    //     l_value_in_flits = 16;
    // else if(e_LINK_IQ_BW_GSPS_4P0 == link_bw)
    //     l_value_in_flits = 128;
    // else l_value_in_flits = 64;

    l_value_in_flits = ((uint32_t *)g_flits_per_block)[jesd_config.jesd_link_config.link_iq_bw];
    number_of_flits_per_stream = l_value_in_flits/num_of_streams;

    //timer calculations will update in next code push, roshan 24/08/24
    //will revisit after imp bringups
    //TODO fix me
    if(jesd_tc_config.usecase_id  == 25)
    {    
        number_of_flits_per_stream = 2;               //hardcoded for 8g, usecase 1a
        printf("###usecase 1a is selected number_of_flits_per_stream is assigned 2\n");
    }

    printf("l value in flits is %d\n", l_value_in_flits);
    printf("flits per stream is %d\n", number_of_flits_per_stream);
    printf("sum_pos_sample_and_neg_sample is %d\n", sum_pos_sample_and_neg_sample);
    printf("soni is %d\n", soni);
    printf("sample_clk is %d\n", sample_clk);
    printf("sample_clk_div_ratio is %d\n", sample_clk_div_ratio);
    timer =   sum_pos_sample_and_neg_sample * (512/(soni * 8)) * number_of_flits_per_stream * sample_clk_div_ratio;
    printf("timer is %d\n", timer);
    return timer;
}


void emb_and_sh_lock_check()
{
    uint32_t sh_lock_status_reg       = 0;
    uint32_t emb_lock_status_reg      = 0;
    uint32_t sh_lock_loss_status_reg  = 0;
    uint32_t emb_lock_loss_status_reg = 0;
    //int jesd_rx_ip_base         = g_jesd_rx_ip_base_addr[jesd_id];
    int jesd_rx_ip_base         = g_jesd_rx_ip_base_addr[0];

    sh_lock_status_reg          = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SH_LOCK_STAT_OFFSET, "JESD_XIP_204C_RX_SH_LOCK_STAT");
    emb_lock_status_reg         = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_EMB_LOCK_STAT_OFFSET, "JESD_XIP_204C_RX_EMB_LOCK_STAT");

    sh_lock_loss_status_reg     = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT_OFFSET, "JESD_XIP_204C_RX_SH_LOCK_LOSS_STAT");
    emb_lock_loss_status_reg    = read_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT_OFFSET, "JESD_XIP_204C_RX_EMB_LOCK_LOSS_STAT");

    printf("\n");
    printf("Present value of SH lock of Link0 is 0x%x \n",sh_lock_status_reg);
    printf("Present value of EMB lock of Link0 is 0x%x \n",emb_lock_status_reg);
    printf("Present value of SH lock loss of Link0 is 0x%x \n",sh_lock_loss_status_reg);
    printf("Present value of EMB lock loss of Link0 is 0x%x \n",emb_lock_loss_status_reg);
}
/**
 * @brief           Function configuring JESD: As per flow id selected
 * @param [in]      flow_id
 * @return          status
 */
int configure_jesd_flow(uint32_t flow_id)
{
    int32_t ret_value = JESD_SUCCESS;
    //Select Test flow
    uint32_t num_of_streams = jesd_config.jesd_link_config.converters / 2;

    switch (flow_id)
    {
		case flow_e2e: /* E2E flow */
					// Config CIO2STRM registers of tx_vex
					//configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
					//configure_vex_strm2cio(jesd_tc_config.vex_id);

					// Config JESD NSIP - as per UC
					//configure_jesd_nsip_common(jesd_tc_config.jesd_id);
					//configure_jesd_b2h(jesd_tc_config.jesd_id);
					//configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);
							
				
					// Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
					configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
					configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
					configure_jesd_rx_glue(jesd_tc_config.jesd_id);
					configure_jesd_rx_ip(jesd_tc_config.jesd_id);

					// End of the test - reg dump rx
					//dump_reg_jesd_rx(jesd_tc_config.jesd_id);

					// Dump the captured data at rx_vex 
					//dump_vmem_vex_rx();
							
					// Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
					configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
					configure_jesd_tx_ip(jesd_tc_config.jesd_id);
					configure_jesd_tx_glue(jesd_tc_config.jesd_id);
					configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);
							

					// Enable jesd
					configure_jesd_ip_enable(jesd_tc_config.jesd_id);
							
					// Config Vex Tx and start Vex
					//configure_vex_tx(jesd_tc_config.vex_id);
							
					// End of the test - reg dump tx
					//dump_reg_jesd_tx(jesd_tc_config.jesd_id);

					// Dump the transferred data from tx_vex 
					//dump_vmem_vex_tx();

					break;
        case flow_vex_loopback: /* loopback at vex */
        {
            printf ("flow_vex_loopback \n");
            /* common configuration */
            configure_jesd_nsip_common(jesd_tc_config.jesd_id); // Config JESD NSIP - as per UC


            /* RX Part configuration */
            configure_jesd_h2b(jesd_tc_config.jesd_id, jesd_tc_config.vex_id);
            configure_vex_strm2cio(jesd_tc_config.vex_id); // Config STRM2CIO registers of rx_vex_id as per UC
            if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
            {
                configure_vex_strm2cio(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
            }
            configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id); // Config JESD cmn csr as per UC
            configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id); // Config JESD crux clk csr as per UC
            configure_jesd_rx_glue(jesd_tc_config.jesd_id); // // Config JESD glue as per U
            configure_jesd_rx_ip(jesd_tc_config.jesd_id); // Config JESD comcores RX IP on Rx path - as per UC


            /* TX Part configuration */
            configure_vex_cio2strm(jesd_tc_config.vex_id, jesd_tc_config.jesd_id); // Config JESD as per UC
            if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
            {
                configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
            }
            configure_jesd_b2h(jesd_tc_config.jesd_id); // Config JESD as per UC

            configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id); // Config JESD tx cmn_csr as per UC
            configure_jesd_tx_ip(jesd_tc_config.jesd_id); // Config JESD comcores tx ip as per UC
            configure_jesd_tx_glue(jesd_tc_config.jesd_id); // Config JESD tx glue as per UC
            configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id); // Config JESD  tx crux as per UC

            /* Enables IPs */
            configure_jesd_ip_enable(jesd_tc_config.jesd_id);

            /* vex configurations */
            configure_vex_rx_tx_lpbk(jesd_tc_config.vex_id);
            if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
            {
                configure_vex_rx_tx_lpbk(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
            }
            /* debug dumps */
            dump_reg_jesd_rx(jesd_tc_config.jesd_id);
            dump_reg_jesd_tx(jesd_tc_config.jesd_id);
            dump_vmem_vex_rx_2(jesd_tc_config.vex_id);
            if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
            {
                dump_vmem_vex_rx_2(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
            }
            printf("printing cio2strm_int_status  \n");
            system("srpRead 0x02801040     1");
            //printf("\n\n#############md_cntrl value is %d \n",h2b_md_ctrl_tbl_value);
            printf("printing H2B_MD_CONTROL_TBL0  \n");
            system("srpRead 0x6704700 1");            
            printf("printing NSIP_HBI_INST_STATUS  \n");
            system("srpRead 0x6704080 1");
            
            printf("printing RX JESD CRUX Clock registers  \n");
            printf("printing RX_STRM_CFG   \n");
            system("srpRead 0x0670c010  1");
            printf("printing RX_MEM_STREAM_CFG   \n");
            system("srpRead 0x0670c014   1");
        }
            break;
        case flow_rx_dnrt_to_vex:
        {
                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);

                    // Config STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);
                    if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_strm2cio(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    delay(100);
                    emb_and_sh_lock_check();
                    configure_vex_rx(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_rx(jesd_tc_config.vex_id+1);// use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    // End of the test - reg dump rx
                    dump_reg_jesd_rx(jesd_tc_config.jesd_id);

                    // End of the test - reg dump rx
                    dump_rx_registers();                   

                    // Dump the captured data at rx_vex_id 
                    // dump_vmem_vex_rx();

                    dump_vmem_vex_rx_2(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        dump_vmem_vex_rx_2(jesd_tc_config.vex_id+1);// use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
        }
                    break;

        case flow_tx_vex_to_dnrt:

                    // Config CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
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
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_tx(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }

                    // End of the test - reg dump tx
                    dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_tx();

                    tx_smpl_intf_cap_en(jesd_tc_config.jesd_id);
                    dump_tx_ip_4k();             // enable capture freeze

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

                    //Configure CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    // Configure STRM2CIO registers of rx_vex
                    // configure_vex_strm2cio(((jesd_tc_config.vex_id)+ 0x1)); // rx vex 1 
                    configure_vex_strm2cio(jesd_tc_config.vex_id); // rx vex 1 
                    if (num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_strm2cio(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
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
                    delay(100);
                    emb_and_sh_lock_check();
                    dump_reg_jesd_rx(jesd_tc_config.jesd_id);

                    //pass 0 - dump all registers,
                    //pass 1 - dump only 4 flits
                    dump_rsb(1);
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
        {
                    printf("hello from roshan \n");

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);

                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);

                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_strm2cio(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    //configure_jesd_rx_ip(jesd_tc_config.jesd_id);                         //roshan 10/06/24
                    printf("####print rx_strm_cfg\n");
                    system("srpRead 0x0670c010 1");

                    // Enable jesd
                    //configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    //prefill_rsb_zeros();
                    delay(100);

                    //calculate the timer value for rsb source mode
                    int timer = calc_timer();
                    printf("####timer value is %x\n",timer);

                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, timer, timer, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR");
#if(0)//single shot mode
                    printf("####single shot RSB source\n");

                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
#else//continous mode
                     printf("####Cont RSB source\n");

                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x3, 0x3, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
#endif
                    delay(100);

                    //prefill rsb with unique stream and data
                    prefill_rsb_uniq_data();
                    delay(100);

                    //dump rsb prefilled data,
                    printf("\n\n#### dumping RSB before RSB start \n");
                    //pass 1 - to dump only 4 flits, pass(0) to dump all flits
                    dump_rsb(1);

                    printf("dumping jesd H2B flit count before RSB source start\n");
                    system("srpRead 0x06704314 1");
                    printf("\n");

                    printf("dumping vex0 flit count before RSB source start\n");
                    system("srpRead 0x02802024 1");
                    printf("\n");
                    delay(1000);

                    //start rsb streaming
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START");
                    delay(1000);

                    printf("dumping jesd H2B flit count after RSB source start\n");
                    system("srpRead 0x06704314 1");
                    printf("\n");

                    printf("dumping vex0 flit count after RSB source start\n");
                    system("srpRead 0x02802024 1");
                    printf("printing strm2cio_int_status   \n");
                    system("srpRead 0x02802040 1");
                    printf("printing h2b_int_status   \n");
                    system("srpRead 0x06704080 1");
                    printf("printing rx_strm_cfg   \n");
                    system("srpRead 0x0670c010 1");

                    printf("\n");
                    delay(1000);

//                  dump_reg_jesd_rx(jesd_tc_config.jesd_id);
//                  dump_rx_registers();
                    configure_vex_rx(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_rx(jesd_tc_config.vex_id+1);// use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }

                    //Dump the captured data at rx_vex
//                    printf("\n\n#### dumping vex after RSB source start \n");
//                    dump_vmem_vex_rx();

                    //Dump as per new vex_rx code
                    dump_vmem_vex_rx_2(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        dump_vmem_vex_rx_2(jesd_tc_config.vex_id+1);// use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    delay(100);
        }
            break;

        case flow_tx_tsb_cap_mode: // glue level
        {

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

                    //calculate the timer value for rsb source mode
                    int timer = calc_timer();
                    printf("####timer value is %x\n",timer);

                    //adding rsb src mode configure code,
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, timer, timer, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR");
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x3, 0x3, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
                    delay(100);

                    //prefill rsb with constant data of '5'
                    prefill_rsb_uniq_data();
                    delay(100);

                    //dump rsb prefilled data,
                    //pass 0 - to dump all flits,
                    //pass 1 - to dump only 4 flits
                    dump_rsb(1);

                    //start rsb streaming
                    write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START");
                    delay(100);

                    //######adding tsb capture code
                    //enable capture freeze
                    //dump tsb
                    dump_tsb();
        }
                    break;

        case flow_lpbk_jesdTx_jesdRx:
                    printf("\n####starting jesd_tx to Jesd_rx lpbk \n\n");

                    // Config CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
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

                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);                    

                    prefill_rsb_zeros();

                    rsb_capture_en(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    // Config Vex Tx and start Vex
                    configure_vex_tx(jesd_tc_config.vex_id);

                    // End of the test - reg dump tx
                    //dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    //dump_vmem_vex_tx();

                    emb_and_sh_lock_check();
                    //pass 0 - dump all flits,
                    //pass 1 - dump only 4 flits
                    dump_rsb(1);
                    //enable capture freeze
                    //dump tsb
                    //dump_tsb();
                    break;
                    
        case flow_vex_tx_tsb_cap_mode:

                    // Config CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_b2h(jesd_tc_config.jesd_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    // clearing TSB
                    // prefill_tsb_uniq_data();// todo: fill is not working//revert the change made for clearing the TSB

                    //TSB capture mode is enabled
                    //printf("\ntsb capture is enabled\n");
                    //write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");

                    // Configure JESD Loopback ctrl regsiter 
                    //configure_jesd_lpbk(jesd_tc_config.jesd_id,jesd_tc_config.flow_id);
                    //write_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET, 0x2, JESD_CRUX_CLK_CSR_LPBK_CTL_WR_MASK, "JESD_CRUX_CLK_CSR_LPBK_CTL");
                    //print("Glue lpbk enabled:\n");

                    //TSB capture mode is enabled
                    printf("\ntsb capture is enabled\n");
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");

                    dump_tsb();

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    // Config Vex Tx and start Vex
                    configure_vex_tx(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_tx(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }

                    // End of the test - reg dump tx
                    //dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_tx();

                    //adding rsb src mode configure code,
                    //write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, 0x800, 0x800, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR");
                    //write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, 0x3, 0x3, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG");
                    //delay(100);

                    //prefill rsb with constant data of '5'
                    //prefill_rsb_const_data();
                    //delay(100);

                    //dump rsb prefilled data,
                    //dump_rsb();

                  //for debug
                    // uint32_t h2b_flit_count = 0;
                    // uint32_t rx_strm_data0 =0;
                    // uint32_t rx_strm_data1 =0;
                    // uint32_t rx_strm_data2 =0;
                    // uint32_t rx_strm_data3 =0;
                    // uint32_t rx_strm_data8 =0;
                    // h2b_flit_count = read_reg_18a(g_jesd_nsip_base_addr[0] + NSIP_HBI_H2B_FLIT_CNT_OFFSET, "JESD0_nsip_hbi_h2b_flit_cnt");
                    // printf("\n########## h2b flit count before rsb source start is %x \n",h2b_flit_count);

                    //reading rx sent flit to nsip
                    // rx_strm_data0 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0");
                    // rx_strm_data1 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1");
                    // rx_strm_data2 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2");
                    // rx_strm_data3 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3");
                    // rx_strm_data8 = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8_OFFSET, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8");
                    // printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0 is %x \n",rx_strm_data0);
                    // printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1 is %x \n",rx_strm_data1);
                    // printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2 is %x \n",rx_strm_data2);
                    // printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data3);
                    // printf("\n########## JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3 is %x \n",rx_strm_data8);

                    uint32_t tx_strm_data_glue =0;
                    for (int i = 0; i<16; i++) {
                        uint32_t TX_STRM_RCV_FLIT_CNT_ADDR = g_jesd_crux_clk_csr_base_addr[0] + JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT0_OFFSET + i * 4;
                        tx_strm_data_glue = read_reg_18a(TX_STRM_RCV_FLIT_CNT_ADDR, "_CSR_TX_STRM_RCV_FLIT_CNT");
                        printf("\n##########strm (%d) _CSR_TX_RCV_FLIT_CNT:   0x%x, addr = 0x%0.8x \n", i, tx_strm_data_glue, TX_STRM_RCV_FLIT_CNT_ADDR);
                    }
                    delay(1000);

                    //start rsb streaming
                    //write_read_expect_18a(g_jesd_crux_clk_csr_base_addr[0]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, 0x1, 0x1, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START");
                    //delay(100);

/*                  //for debug
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

        case flow_tx_ip_4k_capture:

                    // Config CIO2STRM registers of tx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_cio2strm(jesd_tc_config.vex_id + 1, jesd_tc_config.jesd_id); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }
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
                    //configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    // Config Vex Tx and start Vex -Commented for Debug
                    //configure_vex_tx(jesd_tc_config.vex_id);

                    // End of the test - reg dump tx
                    //dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex -Commented for Debug
                    //dump_vmem_vex_tx();

                    //Commented for Debug
                    //tx_smpl_intf_cap_en(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    // Config Vex Tx and start Vex -Commented for Debug
                    configure_vex_tx(jesd_tc_config.vex_id);
                    if(num_of_streams > MAX_STREAM_COUNT_PER_VEX)
                    {
                        configure_vex_tx(jesd_tc_config.vex_id + 1); // use next vex for stream above MAX_STREAM_COUNT_PER_VEX(8) count
                    }

                    // Dump the transferred data from tx_vex 
                    dump_vmem_vex_tx();

                    tx_smpl_intf_cap_en(jesd_tc_config.jesd_id);


                    dump_tx_ip_4k();

                    //enable capture freeze
                    //dump tsb
                    //dump_tsb();
                    break;

/*
                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Tx path - as per UC
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);      
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    tx_smpl_intf_cap_en(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    dump_tx_ip_4k();
                    break;
*/

        case flow_tsb_src_dnrt:

                    printf("\n####Starting flow_tsb_src_dnrt \n\n");

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    // TX Datapath Gating logic - Select TX path Trig 0 and Trig1 - Software triggers   
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_DATAPATH_GATE_SEL_OFFSET, JESD_TX_GLUE_DATAPATH_GATE_SEL_DEFAULT, 0x0000000f, 0x0000000f, JESD_TX_GLUE_DATAPATH_GATE_SEL_RD_MASK, JESD_TX_GLUE_DATAPATH_GATE_SEL_WR_MASK, "JESD_TX_GLUE_DATAPATH_GATE_SEL");

                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);


                    //Step1: write "1" to TX_DATA_SRC_EN register and enable TX_IP by writing value "1" to register tx.enablemodule_reg[0].
                    //tsb_source_mode_en
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET, JESD_TX_GLUE_DATA_SRC_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_DATA_SRC_EN_RD_MASK, JESD_TX_GLUE_DATA_SRC_EN_WR_MASK, "JESD_TX_GLUE_DATA_SRC_EN");

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    //Step2:pre load the TSB through APB
                    //prefill_tsb();
                    prefill_tsb_uniq_data();

                    printf("\ntsb capture is enabled\n");
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");
                    //dump tsb : Read TSB through APB
                    dump_tsb();
                    printf("\ntsb capture is disabled and starting TSB streaming\n");
                    delay(1000);
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000000, 0x00000000, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");

                    //Step3: Once the memory is pre filled with data then write "1" to TX_IP_SMPL_TSB_DATA_EN register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_OFFSET, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_RD_MASK, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_WR_MASK, "JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN");

                    //Step4: write "1" to TX_TSB_RD_TRIG register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_TSB_RD_TRIG_OFFSET, JESD_TX_GLUE_TSB_RD_TRIG_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_TSB_RD_TRIG_RD_MASK, JESD_TX_GLUE_TSB_RD_TRIG_WR_MASK, "JESD_TX_GLUE_TSB_RD_TRIG");

                    //Debug: Read TSB through APB
                    //dump_tsb();

        break;


        case flow_tsb_src_rsb:
                    printf("\n####starting jesd_tx to Jesd_rx lpbk \n\n");

                    //  //Config CIO2STRM registers of tx_vex
                    //  configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);

                    //  //Config JESD NSIP - as per UC
                    //  configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    //  configure_jesd_b2h(jesd_tc_config.jesd_id);

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    // TX Datapath Gating logic - Select TX path Trig 0 and Trig1 - Software triggers   
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_DATAPATH_GATE_SEL_OFFSET, JESD_TX_GLUE_DATAPATH_GATE_SEL_DEFAULT, 0x0000000f, 0x0000000f, JESD_TX_GLUE_DATAPATH_GATE_SEL_RD_MASK, JESD_TX_GLUE_DATAPATH_GATE_SEL_WR_MASK, "JESD_TX_GLUE_DATAPATH_GATE_SEL");

                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    //TSB capture mode is enabled
                    //printf("\ntsb capture is enabled\n");
                    //write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");

                    // Config JESD cmn csr, glue, crux clk csr, comcores IP on Rx path - as per UC 
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);                    

                    //PRE-fill RSB to zero
                    prefill_rsb_zeros();

                    rsb_capture_en(jesd_tc_config.jesd_id);

                    //Step1: write "1" to TX_DATA_SRC_EN register and enable TX_IP by writing value "1" to register tx.enablemodule_reg[0].
                    //tsb_source_mode_en
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_DATA_SRC_EN_OFFSET, JESD_TX_GLUE_DATA_SRC_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_DATA_SRC_EN_RD_MASK, JESD_TX_GLUE_DATA_SRC_EN_WR_MASK, "JESD_TX_GLUE_DATA_SRC_EN");

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    //Step2:pre load the TSB through APB
                    //prefill_tsb();
                    prefill_tsb_uniq_data();

                    printf("\ntsb capture is enabled\n");
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");
                    //dump tsb : Read TSB through APB
                    dump_tsb();
                    printf("\ntsb capture is disabled and starting TSB streaming\n");
                    delay(1000);
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0]+JESD_TX_GLUE_CAP_FRZ_EN_OFFSET, JESD_TX_GLUE_CAP_FRZ_EN_DEFAULT, 0x00000000, 0x00000000, JESD_TX_GLUE_CAP_FRZ_EN_RD_MASK, JESD_TX_GLUE_CAP_FRZ_EN_WR_MASK, "JESD_TX_GLUE_CAP_FRZ_EN");


            //      // Config Vex Tx and start Vex
            //      configure_vex_tx(jesd_tc_config.vex_id);

                    // End of the test - reg dump tx
                    //dump_reg_jesd_tx(jesd_tc_config.jesd_id);

                    // Dump the transferred data from tx_vex 
                    //dump_vmem_vex_tx();

                    //Once the memory is pre filled with data then write "1" to TX_IP_SMPL_TSB_DATA_EN register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_OFFSET, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_RD_MASK, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_WR_MASK, "JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN");

                    //write "1" to TX_TSB_RD_TRIG register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_TSB_RD_TRIG_OFFSET, JESD_TX_GLUE_TSB_RD_TRIG_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_TSB_RD_TRIG_RD_MASK, JESD_TX_GLUE_TSB_RD_TRIG_WR_MASK, "JESD_TX_GLUE_TSB_RD_TRIG");


                    emb_and_sh_lock_check();
                    //pass 0 - dump all flits,
                    //pass 1 - dump only 4 flits
                    dump_rsb(1);

                    //dump Rx registers
                    dump_reg_jesd_rx(jesd_tc_config.jesd_id);

            break;

        case flow_tsb_src_tx_ip_4k_capture:

                    // Config JESD cmn csr, glue,crux clk csr, comcores IP on Tx path - as per UC 
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    // TX Datapath Gating logic - Select TX path Trig 0 and Trig1 - Software triggers   
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[jesd_tc_config.jesd_id] + JESD_TX_GLUE_DATAPATH_GATE_SEL_OFFSET, JESD_TX_GLUE_DATAPATH_GATE_SEL_DEFAULT, 0x0000000f, 0x0000000f, JESD_TX_GLUE_DATAPATH_GATE_SEL_RD_MASK, JESD_TX_GLUE_DATAPATH_GATE_SEL_WR_MASK, "JESD_TX_GLUE_DATAPATH_GATE_SEL");

                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    tx_smpl_intf_cap_en(jesd_tc_config.jesd_id);

                    // Enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);

                    //Step2:pre load the TSB through APB
                    //prefill_tsb();
                    prefill_tsb_uniq_data();

                    //Once the memory is pre filled with data then write "1" to TX_IP_SMPL_TSB_DATA_EN register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_OFFSET, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_RD_MASK, JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN_WR_MASK, "JESD_TX_GLUE_IP_SMPL_TSB_DATA_EN");

                    //write "1" to TX_TSB_RD_TRIG register.
                    write_read_expect_18a(g_jesd_tx_glue_base_addr[0] + JESD_TX_GLUE_TSB_RD_TRIG_OFFSET, JESD_TX_GLUE_TSB_RD_TRIG_DEFAULT, 0x00000001, 0x00000001, JESD_TX_GLUE_TSB_RD_TRIG_RD_MASK, JESD_TX_GLUE_TSB_RD_TRIG_WR_MASK, "JESD_TX_GLUE_TSB_RD_TRIG");


                    dump_tx_ip_4k();
        break;

        default:
                printf("\n WARNING: Flow handling does not exist; check flow id again \n\n");
                return JESD_GENERIC_FAIL;
        break;
    }
    return ret_value;
}

/**
 * @brief           Function configuring JESD: As per testcase selected
 * @param [in]      flow_id
 * @return          status
 */ 
int configure_jesd(uint32_t testcase)
{
    int32_t ret_value = JESD_SUCCESS;
    printf("INFO : Configure JESD \n");
    memset(&jesd_config, 0, sizeof(jesd_config));
    //memset(&vex_strm2cio_config, 0, sizeof(vex_strm2cio_config));

    // Assign default values to JESD Testcase config and Jesd config structures 
    printf("INFO : Assign defaults to jesd_config struct\n");
    ret_value =  assign_defaults();
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: assign_defaults failed with error = %d\n", ret_value);
        return ret_value;
    }

    // Parse from command line - JESD Testcase config -as per TC
    printf("INFO : update/fill/assign jesd_tc_config struct as per TC\n");
    ret_value =  assign_tc_config(jesd_tc_config_arr, testcase);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: assign_tc_config failed with error = %d\n", ret_value);
        return ret_value;
    }

    // Configure jesd config struct as per UC
    printf("INFO: update/fill/assign jesd_config struct as per UC\n");
    ret_value =  assign_jesd_config(jesd_config_arr, jesd_tc_config.usecase_id);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: assign_jesd_config failed with error = %d\n", ret_value);
        return ret_value;
    }

    //Initialize Test - fpga clk, fpga provided sysref for jesd, reset cycle for jesd,vex,other SS, clearing vex/jesd mem
    printf("INFO : Initialize Jesd%d\n", jesd_tc_config.jesd_id);
    ret_value =  init_jesd(jesd_tc_config.jesd_id, jesd_config.jesd_link_config.serdes_rate, jesd_config.jesd_link_config.smpl_char_clk_ratio);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_jesd failed with error = %d\n", ret_value);
        return ret_value;
    }

    printf("INFO: Initialize Vex%d\n", jesd_tc_config.vex_id);
    ret_value =  init_vex(jesd_tc_config.vex_id);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_vex failed with error = %d\n", ret_value);
        return ret_value;
    }

    printf("INFO: Initialize Vex%d\n", jesd_tc_config.vex_id+1);
    init_vex(jesd_tc_config.vex_id+1);

    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_vex failed with error = %d\n", ret_value);
        return ret_value;
    }

    //Configure jesd TC as per flow selected
    ret_value =  configure_jesd_flow (jesd_tc_config.flow_id);   
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: configure_jesd_flow failed with error = %d\n", ret_value);
        return ret_value;
    }

    return ret_value;
}


/**
 * @brief           Function configuring JESD: As per testcase selected
 * @param [in]      testcase
 * @return          status
 */ 
int configure_jesd_generic
(
    usecase_id_t        usecase_id,
    flow_id_t           flow_id,
    vex_id_t            vex_id,
    jesd_id_t           jesd_id
)
{
    int32_t ret_value = 0;

    printf("INFO : Configure JESD Generically\n");
    memset(&jesd_config, 0, sizeof(jesd_config));
    //memset(&vex_strm2cio_config, 0, sizeof(vex_strm2cio_config));

    // Assign default values to JESD Testcase config and Jesd config structures 
    printf("INFO : Assign defaults to jesd_config struct\n");
    assign_defaults();
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: assign_defaults failed with error = %d\n", ret_value);
        return ret_value;
    }

    // Parse from command line - JESD Testcase config -as per TC
    jesd_tc_config.testcase_id  = 0xffffffff;
    jesd_tc_config.usecase_id   = usecase_id;
    jesd_tc_config.flow_id      = flow_id;
    jesd_tc_config.vex_id       = vex_id;
    jesd_tc_config.jesd_id      = jesd_id;

    printf("jesd_tc_config.testcase_id = %d\n", jesd_tc_config.testcase_id);
    printf("jesd_tc_config.usecase_id = %d\n", jesd_tc_config.usecase_id);
    printf("jesd_tc_config.flow_id = %d\n", jesd_tc_config.flow_id);
    printf("jesd_tc_config.vex_id = %d\n", jesd_tc_config.vex_id);
    printf("jesd_tc_config.jesd_id = %d\n", jesd_tc_config.jesd_id);

    // Configure jesd config struct as per UC
    printf("INFO: update/fill/assign jesd_config struct as per UC\n");
    ret_value =  assign_jesd_config(jesd_config_arr, jesd_tc_config.usecase_id);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: assign_jesd_config failed with error = %d\n", ret_value);
        return ret_value;
    }

    //Initialize Test - fpga clk, fpga provided sysref for jesd, reset cycle for jesd,vex,other SS, clearing vex/jesd mem
    printf("INFO : Initialize Jesd%d\n", jesd_tc_config.jesd_id);
    ret_value =  init_jesd(jesd_tc_config.jesd_id, jesd_config.jesd_link_config.serdes_rate, jesd_config.jesd_link_config.smpl_char_clk_ratio);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_jesd failed with error = %d\n", ret_value);
        return ret_value;
    }

    printf("INFO: Initialize Vex%d\n", jesd_tc_config.vex_id);
    ret_value =  init_vex(jesd_tc_config.vex_id);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_vex failed with error = %d\n", ret_value);
        return ret_value;
    }

    printf("INFO: Initialize Vex%d\n", jesd_tc_config.vex_id+1);
    init_vex(jesd_tc_config.vex_id+1);
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: init_vex failed with error = %d\n", ret_value);
        return ret_value;
    }

    //Configure jesd TC as per flow selected
    ret_value =  configure_jesd_flow (jesd_tc_config.flow_id);   
    if (JESD_SUCCESS != ret_value) {
        printf("WARNING: configure_jesd_flow failed with error = %d\n", ret_value);
        return ret_value;
    }

    return ret_value;
}
