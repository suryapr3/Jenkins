/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
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
 * @file    jesd_test_common.h
 * @brief   jesd_test_common will contain
 *          
 */

#ifndef JESD_TEST_COMMON_H
#define JESD_TEST_COMMON_H

/***********************************************
 * GLOBAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "srp.h"
#include "cli.h"
#include "init.h"

#include <stdio.h>
#include <stdbool.h>
#include <time.h> 
#include <stdint.h>

#include "logger.h"
#include "srp_block_ids.h"

#include "common_functions.h"
#include "all_comps.h"
#include "ve32_cell.h"
#include <srp_vex.h>
#include "host_utils.h"

#define HIVE_MULTIPLE_PROGRAMS


#ifndef E2E_FLOW_EN
#include "vex_fw/sim_m64/jesd_tx.map.h"
#include "vex_fw/sim_m64/jesd_rx.map.h"
#include "vex_fw/sim_m64/jesd_rx_tx_lpbk.map.h"
#endif // !E2E_FLOW_EN

/***********************************************
 * GLOBAL MACROS AND DEFINES            *
 ***********************************************/
#define print(...)                      LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x)                  (sizeof(x) / sizeof((x)[0]))

#define VEX_BASE(vex_num)              (VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000))
#define VE32_CELL_BASE(vex_num)        (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_STRM2CIO_OFFSET      (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */
#define VE32_TILE_CIO2STRM_OFFSET      (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */

#define NUM_TOTAL_VEC_PER_STREAM        64
#define NUM_OF_ELEMENTS_PER_VEC         32
#define MAX_STREAM_COUNT_PER_VEX        (8)
/***********************************************
 * GLOBAL TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef enum {
        JESD_SUCCESS = 0,
        JESD_GENERIC_FAIL = -1,
              }jesd_error_code_t;   
// JESD_config Enums
typedef enum {
              //RX 16G usecases TC_0-TC_6(4 streams; 8 streams; 16 streams)
              //TC0-TC1 - RX 16G 4 stream usecseas
              TC_0 = 0,                                               
              TC_1 = 1,
              
              //TC2-TC4 - RX 16G 8 stream usecseas
              TC_2 = 2,
              TC_3 = 3,
              TC_4 = 4,
             
             //TC5-TC6 - RX 16G 16 stream usecseas
              TC_5 = 5,
              TC_6 = 6,
             
             //RX 32G usecases TC_7-TC_20(1 stream; 2 streams; 4 streams ; 8 streams ;16 streams)
             //TC7-TC9 - RX 32G 1 stream usecseas
              TC_7 = 7,
              TC_8 = 8,
              TC_9 = 9,
             
             //TC10-TC12 - RX 32G 2 stream usecseas
              TC_10 = 10,
              TC_11 = 11,
              TC_12 = 12,
              
             //TC13-TC15 - RX 32G 4 stream usecseas
              TC_13 = 13,
              TC_14 = 14,
              TC_15 = 15,
              
             //TC16-TC18 - RX 32G 8 stream usecseas
              TC_16 = 16,
              TC_17 = 17,
              TC_18 = 18,
              
             //TC19-TC20 - RX 32G 16 stream usecseas
              TC_19 = 19,
              TC_20 = 20,
              
              //TX 16G usecases (4 streams; 8 streams; 16 streams)
              //TC21-TC22 - TX 16G 4 stream usecseas
              TC_21 = 21,                                               
              TC_22 = 22,
              
              //TC23-TC25 - TX 16G 8 stream usecseas
              TC_23 = 23,
              TC_24 = 24,
              TC_25 = 25,
              
              //TC26 - TC28 TX 32G 8 stream usecseas
              TC_26 = 26,
              TC_27 = 27,
              TC_28 = 28,

              //TC29 - TC31 TX 32G 4 stream usecseas
              TC_29 = 29,
              TC_30 = 30,
              TC_31 = 31,

              //TC32 - TX 32G 1 stream usecseas
              TC_32 = 32,

              //TC33 - TC34 TX 32G 2 stream usecseas
              TC_33 = 33,
              TC_34 = 34,

              //Glue level lpbk 5c 
              TC_35 = 35,

              //Nsip level lpbk 5c 
              TC_36 = 36,

              //IP level lpbk 5c 
              TC_37 = 37,

              //DNRT to RSB capture 5c 
              TC_38 = 38,

              //DNRT to jesd_rx ip 4k capture - 5c 
              TC_39 = 39,

              //RSB to vex capture - 5c 
              TC_40 = 40,

              //tsb capture mode - 5c
              TC_41 = 41,

              //Glue level lpbk 9a 
              TC_42 = 42,

              //e2e 5c
              TC_43 = 43,

              //RSB to vex capture - 7c 
              TC_44 = 44,

              //RSB to vex capture - 3a 
              TC_45 = 45,

              //RSB to vex capture - 3b
              TC_46 = 46,

              //RSB to vex capture - 3d 
              TC_47 = 47,

              //RSB to vex capture - 2c 
              TC_48 = 48,

              //RSB to vex capture - 2b 
              TC_49 = 49,

              //RSB to vex capture - 11a
              TC_50 = 50,

              //RSB to vex capture - 9b 
              TC_51 = 51,
              
              //JESD_Tx to JESD_Rx lpbk - 5c 
              TC_52 = 52,
              
              //JESD_Tx to JESD_Rx lpbk - 5e
              TC_53 = 53,
              TC_54 = 54, //vex lpbk - 5C
              TC_55 = 55,  //vex lpbk -7C
              //tsb capture mode - 3d
              TC_56 = 56,

              //dnrt to RSB capture, 32g  - 5e
              TC_57 = 57,

              //TC32 - TX 32G 1 stream usecseas
              TC_58 = 58,
              TC_59 = 59,

              //TC33 - TC34 TX 32G 2 stream usecseas
              TC_60 = 60,

              //TX_IP_4K_Capture mode - UC11A
              TC_61 = 61,

              //tsb capture mode - UC11A
              TC_62 = 62,

              //TSB source - dnrt rx - 11a
              TC_63 = 63,

              //TC64 RX 16G 4 stream usecseas
              // loopback at vex rx to tx - 3A
              TC_64 = 64,

              //TC65 RX 16G 8 stream usecseas
              // loopback at vex rx to tx - 3B,
              TC_65 = 65,

              //TC66 RX 16G 8 stream usecseas
              // loopback at vex rx to tx - 2B,
              TC_66 = 66,

              //TC67 RX 16G 16 stream usecseas
              // loopback at vex rx to tx - 3D,
              TC_67 = 67,

              //TC68 RX 16G 16 stream usecseas
              // loopback at vex rx to tx -2C
              TC_68 = 68,

              //TC69 RX 32G 1 stream usecase
              // loopback at vex rx to tx - 9A
              TC_69 = 69,

              //TC70 RX 32G 1 stream usecase
              // loopback at vex rx to tx -11A
              TC_70 = 70,

              //TC71 RX 32G 1 stream usecseas
              // loopback at vex rx to tx -13A
              TC_71 = 71,

              //TC72 RX 32G 2 stream usecseas
              // loopback at vex rx to tx - 7B,9B,11C
              TC_72 = 72,

              //TTC73 RX 32G 2 stream usecseas
              // loopback at vex rx to tx -9B
              TC_73 = 73,

              //TC74 RX 32G 2 stream usecseas
              // loopback at vex rx to tx -11C
              TC_74 = 74,

              //TC75 RX 32G 4 stream usecseas
              // loopback at vex rx to tx - 5B
              TC_75 = 75,
              //TC76 RX 32G 4 stream usecseas
              // loopback at vex rx to tx - 7E
              TC_76 = 76,
              //TC77 RX 32G 4 stream usecseas
              // loopback at vex rx to tx - 9C
              TC_77 = 77,

              //TC78 RX 32G 8 stream usecseas
              // loopback at vex rx to tx - 5E
              TC_78 = 78,
              //TC79 RX 32G 8 stream usecseas
              // loopback at vex rx to tx - 3C
              TC_79 = 79,
              //TC80 RX 32G 8 stream usecseas
              // loopback at vex rx to tx - 7G
              TC_80 = 80,

              //TC81 RX 32G 16 stream usecseas
              // loopback at vex rx to tx - 3E
              TC_81 = 81,
              //TC82 RX 32G 16 stream usecseas
              // loopback at vex rx to tx - 5f
              TC_82 = 82,

              //vex to dnrt 3D
              TC_83 = 83,
              // vex to TSB 3D
              TC_84 = 84,

              //13a, rsb to vex
              TC_85 = 85,

              //6a, dnrt to vex,
              TC_86 = 86,
              //6a, rsb to vex
              TC_87 = 87,

              //11c, rsb to vex
              TC_88 = 88,

              //6a, dnrt to vex
              TC_89 = 89,

              //6a, jesd_tx to jesd_rx lpbk, vex to rsb
              TC_90 = 90,

              //6a, tsb to rsb
              TC_91 = 91,

              //6a, tsb to dnrt
              TC_92 = 92,

              //tsb to tx_ip_4k_cap
              TC_93 = 93,

              //6a, vex to tx_ip_4k_cap
              TC_94 = 94,

              //6a, vex to dnrt
              TC_95 = 95,

              //11a, tsb to rsb
              TC_96 = 96,

              //7e, tsb to rsb
              TC_97 = 97,

              //11a, tsb to tx_ip_4k_cap
              TC_98 = 98,

              //3a, tsb to rsb
              TC_99 = 99,

              //5c, tsb to rsb
              TC_100 = 100,

              //5a, dnrt to rsb
              TC_101 = 101,

              //5a, tsb to rsb
              TC_102 = 102,

              //5a, tsb to dnrt
              TC_103 = 103,

              //3a, jesd-tx to jesd-rx lpbk, vex to rsb
              TC_104 = 104,

              //6c, rsb src mode
              TC_105 = 105,

              //8a, rsb src mode
              TC_106 = 106,

              //1a, rsb src mode
              TC_107 = 107,

              //1a, dnrt to rsb
              TC_108 = 108,

              //1a, jesd-tx to jesd-rx lpbk, vex to rsb
              TC_109 = 109,

              //1a, tsb to rsb, jesd-tx to jesd-rx lpbk
              TC_110 = 110,

              //6c, dnrt to rsb
              TC_111 = 111,

              //6a, glue lpbk
              TC_112 = 112,

              //1a, tsb to dnrt
              TC_113 = 113,

              //1a, tsb to tx_ip_4k_cap
              TC_114 = 114,

              //5c, vex to tsb
              TC_115 = 115,

              //5c, vex to tsb
              TC_116 = 116,

              //5c, vex to tsb
              TC_117 = 117,

              TC_MAX = 118       //KEEP it at the end, and update it accordingly as you add new test case.
              }testcase_id_t;    //JESD testcase selection

typedef enum {
    #include "usecase_list.h"
            //  //16G usecases TC_0-TC_7(4 streams; 8 streams; 16 streams)
            //   //TC0-TC1 - RX 16G 4 stream usecseas
            //   UC_3A = 0,                                                 
            //   UC_7C = 1,

            //   //TC2-TC4 - RX 16G 8 stream usecseas
            //   UC_5C = 2,
            //   UC_2B = 3,
            //   UC_3B = 4,

            //  //TC5-TC6 - RX 16G 16 stream usecseas
            //   UC_2C = 5,
            //   UC_3D = 6,

            //  //RX 32G usecases TC_7-TC_20(1 stream; 2 streams; 4 streams ; 8 streams ;16 streams)
            //  //TC7-TC9 - RX 32G 1 stream usecseas
            //   UC_9A = 7,
            //   UC_11A = 8,
            //   UC_13A = 9,

            //  //TC10-TC12 - RX 32G 2 stream usecseas
            //   UC_7B = 10,
            //   UC_9B = 11,
            //   UC_11C = 12,

            //  //TC13-TC15 - RX 32G 4 stream usecseas
            //   UC_5B = 13,
            //   UC_7E = 14,
            //   UC_9C = 15,

            //  //TC16-TC18 - RX 32G 8 stream usecseas
            //   UC_5E = 16,
            //   UC_3C = 17,
            //   UC_7G = 18,

            //   //TC19-TC20 - RX 32G 16 stream usecseas
            //   UC_3E = 19,
            //   UC_5F = 20
              } usecase_id_t;                                  //Link config UC 
              
typedef enum {flow_tx_vex_to_dnrt       = 0,          //vex_tx -> b2h -> jesd_tx -> dnrt_rx
              flow_rx_dnrt_to_vex       = 1,          //dnrt -> jesd_rx -> h2b -> vex_capture
              flow_tsb_dsm              = 2,          //same as flow 17,18,19, to be allocated for some other flow
              flow_tsb_capt             = 3,          //same as flow 11,16, to be allocated for some other flow
              flow_rsb_dsm              = 4,          //same as flow 10, to be allocated for some other flow
              flow_rsb_capt             = 5,          //dnrt -> jesd_rx -> rsb cap
              flow_lpbk_glue            = 6,          //dnrt -> jesd_rx -> glue lpbk -> jesd_tx -> dnrt
              flow_lpbk_nsip            = 7,          //vex_tx -> b2h -> h2b -> vex_rx
              flow_lpbk_ip              = 8,          //dnrt -> jesd_rx -> ip lpbk -> jesd_tx -> dnrt
              flow_rx_ip_4k_capture     = 9,          //dnrt -> jesd_rx -> rx_ip4k_capture
              flow_rx_rsb_src_mode      = 10,         //rsb -> h2b -> vex capture
              flow_tx_tsb_cap_mode      = 11,         //rsb src -> glue lpbk -> tsb capture 
              flow_e2e                  = 12,         //e2e team implementation
              flow_lpbk_jesdTx_jesdRx   = 13,         //vex -> jesd_tx -> jesd-tx to jesd-rx lpbk -> jesd_rx -> rsb capture
              flow_vex_loopback         = 14,         //dnrt -> jesd_rx -> h2b -> vex_rx -> vex _tx -> b2h -> jesd_tx -> dnrt
              flow_tx_ip_4k_capture     = 15,         //vex -> b2h -> tx_ip_4k_capture
              flow_vex_tx_tsb_cap_mode  = 16,         //vex -> b2h -> tsb capture        
              flow_tsb_src_dnrt         = 17,         //tsb source -> dnrt capture,
              flow_tsb_src_rsb              = 18,     //tsb -> jesd_tx  -> jesd-tx to jesd-rx lpbk -> jesd_rx -> rsb capture
              flow_tsb_src_tx_ip_4k_capture = 19,     //tsb source mode -> tx_ip_4k_capture, 
              } flow_id_t;                     //Flow selection

typedef enum {vex_0 = 0x0,
              vex_1 = 0x1,
              vex_2 = 0x2,
              vex_3 = 0x3} vex_id_t;                                    //Vex host id

typedef enum {jesd_0 = 0x0,
              jesd_1 = 0x1,
              jesd_2 = 0x2,
              jesd_3 = 0x3} jesd_id_t;                                  //Jesd host id

typedef struct jesd_tc_config_t
{
    testcase_id_t       testcase_id;
    usecase_id_t        usecase_id;
    flow_id_t           flow_id;
    vex_id_t            vex_id;
    jesd_id_t           jesd_id;
}jesd_tc_config_t;


typedef enum {disable = 0x0,
              enable  = 0x1} states_t;                                   //States - en/dis

// VEX CIO config structs - CIO
typedef struct vex_strm2cio_config_t                                    //VEX STRM2CIO 
{
    int strm2cio_int_en;                                                //STRM2CIO Interrupt Enable 
    int strm2cio_fifo_sts_ctrl;                                         //Streaming FIFO Status Control
    int strm2cio_wrd_cnt_ctrl;                                          //FIFO Word Counter Control 
} vex_strm2cio_config_t;

typedef struct vex_cio2strm_config_t 
{
    int cio2strm_int_en;                                                //CIO2STRM Interrupt Enable 
    int cio2strm_fifo_sts_ctrl;                                         //Streaming FIFO Status Control
    int cio2strm_wrd_cnt_ctrl;                                          //FIFO Word Counter Control 
} vex_cio2strm_config_t;


// JESD_config structs - NSIP 
typedef struct jesd_hbi_config_t                                        //JESD NSIP cmn
{
    int hbi_int_high_en;                                                //HBI High Priority Interrupt Enable 
    int hbi_int_low_en;                                                 //HBI Low Priority Interrupt Enable Register
} jesd_hbi_config_t;

typedef struct jesd_h2b_config_t                                        //JESD NSIP H2B
{
    int h2b_fifo_ctrl;                                                  //H2B_FIFO_CONTROL
    int h2b_credit_ready;                                               //H2B Credit and Ready signal Control and Status 
} jesd_h2b_config_t;

typedef struct jesd_b2h_config_t                                        //JESD NSIP H2B
{
    int b2h_fifo_ctrl;                                                  //B2H_FIFO_CONTROL
    int b2h_credit_ready;                                               //B2H Credit and Ready signal Control and Status 
} jesd_b2h_config_t;


// JESD_config structs - GLUE                                           
typedef struct jesd_rx_glue_config_t                                    //JESD rx glue
{
    states_t rx_dp_gate_sel;                                              
    int rx_dp_init_cyc_cnt;
} jesd_rx_glue_config_t;

typedef struct jesd_tx_glue_config_t                                     //JESD tx glue
{
    int tx_conv_dp_cfg;
    int tx_srg_pat_cfg_low;
    int tx_srg_pat_period_cfg;
    int tx_srg_pat_del_cfg;
    int tx_tsb_min_max_occupancy_capt_en;
    int tx_dp_gate_sel;                                                               
    states_t tx_strm_phm_en;
    states_t tx_srg_pat_en;
} jesd_tx_glue_config_t;


// JESD_config structs - CMN CSR
typedef struct jesd_rx_cmn_csr_config_t                                  //JESD RX cmn csr
{
    int rx_ip_clk_ctrl;
    int rx_sysref_tsad;
    int rx_sync_point_ctrl;
    int rx_bfn_sysref_tsad;
    int rx_bfn_sync_point_ctrl;
    states_t rx_clk_1p5g_div_en;
    states_t rx_clk_gen;
    states_t rx_sync_point_cnt_en;
    states_t rx_bfn_sync_point_cnt_en;
}jesd_rx_cmn_csr_config_t;

typedef struct jesd_tx_cmn_csr_config_t                                  //JESD TX cmn csr
{
    int tx_ip_clk_ctrl;
    int tx_sysref_tsad;
    int tx_sync_point_ctrl;
    int tx_bfn_sysref_tsad;
    int tx_bfn_sync_point_ctrl;
    states_t tx_clk_1p5g_div_en;
    states_t tx_clk_gen;
    states_t tx_sync_point_cnt_en;
    states_t tx_bfn_sync_point_cnt_en;
}jesd_tx_cmn_csr_config_t;


// JESD Link Config enums                                                //Refer JESD204C/D Link Configurations              
typedef enum {sample_rate_30P72       = 30,
              sample_rate_61P44       = 61,
              sample_rate_122P88      = 122,
              sample_rate_184P32      = 184,
              sample_rate_245P76      = 245,
              sample_rate_368P64      = 368,
              sample_rate_491P52      = 491,
              sample_rate_737P28      = 737,
              sample_rate_983P04      = 983,
              sample_rate_1474P56     = 1474,
              sample_rate_1966P08     = 1966,
              sample_rate_2949P12     = 2949, 
              sample_rate_3932P16     = 3932,
              sample_rate_5898P24     = 5898,
              sample_rate_7864P32     = 7864} sample_rate_t;            //Sample Rate (Msps) 

typedef enum {l_1 = 1,
              l_2 = 2,
              l_3 = 3,
              l_4 = 4} lanes_t;                                         //Number of Lanes(L) = 1,2,3,4

typedef enum {m_2   = 2,
              m_4   = 4,
              m_8   = 8,
              m_16  = 16,
              m_32  = 32} converters_t;                                 //Number of converters (2 / AxC) (M) = 2,4,8,16,32

typedef enum {f_1   = 1,
              f_2   = 2,
              f_3   = 3,
              f_4   = 4,
              f_5   = 5,
              f_6   = 6,
              f_8   = 8,
              f_12  = 12,
              f_16  = 16,
              f_20  = 20,
              f_24  = 24,
              f_32  = 32} frames_t;                                     //Number of octets per Frame (F)

typedef enum {s_1  = 1,
              s_2  = 2} smpl_per_frame_t;                               //Number of samples(S) per converter

typedef enum {n_tot_16  = 16,
              n_tot_24  = 24} smpl_total_bits_t;                        //Total number of bits per sample (Ntot) N'

typedef enum {jesd_204c = 1,
              jesd_204d = 2} jesd_204_std_t;                            //JESD 204 Standard : 204C/204D

typedef enum {serdes_rate_8P11008   = 0,
              serdes_rate_16P22016  = 1,
              serdes_rate_24P33024  = 2,
              serdes_rate_32P44032  = 3,
              serdes_rate_50P13504  = 4,
              serdes_rate_66P84672  = 5,
              serdes_rate_83P5584   = 6,
              serdes_rate_100P27008 = 7} serdes_rate_t;               //Serdes Rate (Gbps)

typedef enum {e_1 = 1,
              e_3 = 3} min_e_t;                                         //Least #Blocks in EMB, LAC (Emin, Amin)

typedef enum {soni_1  = 1,
              soni_2  = 2,
              soni_4  = 4,
              soni_8  = 8} sonif_t;                                     //SONIF Samples on Interface (SonI)

typedef enum {clk_ratio_1_1 = 0,
              clk_ratio_2_1 = 1,
              clk_ratio_4_1 = 2,
              clk_ratio_8_1 = 3} smpl_char_clk_ratio_t;                 //Sample to Char Clock Ratio 0=1:1, 1=2:1, 2=4:1, 3=8:1



typedef enum {smpl_req_pos_cycle_1 = 1,
              smpl_req_pos_cycle_2 = 2,
              smpl_req_pos_cycle_4 = 4}smpl_trans_pos_t;

typedef enum {smpl_req_neg_cycle_0 = 0,
              smpl_req_neg_cycle_1 = 1,
              smpl_req_neg_cycle_3 = 3}smpl_trans_neg_t;


// typedef enum {link_iq_bw_512  =  512,
//               link_iq_bw_1024 = 1024,
//               link_iq_bw_1536 = 1536,
//               link_iq_bw_2048 = 2048,
//               link_iq_bw_2969 = 2969,
//               link_iq_bw_3993 = 3993}link_iq_bw_t;                      //roshan added 08/07/24

typedef enum
{
    //1G
    e_LINK_IQ_BW_GSPS_0P25 = 0x0,
    e_LINK_IQ_BW_GSPS_0P5,   // = 0x1,
    e_LINK_IQ_BW_GSPS_1P0,   // = 0x2,
    e_LINK_IQ_BW_GSPS_2P0,   // = 0x3
    e_LINK_IQ_BW_GSPS_4P0,   // = 0x4
    e_LINK_IQ_BW_GSPS_8P0,   // = 0x5
    //1.5G
    e_LINK_IQ_BW_GSPS_0P187, // = 0x6
    e_LINK_IQ_BW_GSPS_0P375, // = 0x7
    e_LINK_IQ_BW_GSPS_0P75,  // = 0x8
    e_LINK_IQ_BW_GSPS_1P5,   // = 0x9
    e_LINK_IQ_BW_GSPS_3P0,   // = 0xa
    e_LINK_IQ_BW_GSPS_6P0,   // = 0xb
} link_iq_bw_t; 


// Pre-configure JESD receiver per the particular use chain
typedef enum {n_16 = 16,
              n_15 = 15,
              n_14 = 14} smpl_res_t;                                    //Sample resolution(N)

typedef enum {rs_136_130 = 0,
              rs_144_130 = 1,
              rs_272_258 = 2,
              rs_544_514 = 3,
              rs_528_514 = 4} fec_mode_t;                               //JESD204D FEC_MODE: Per use case 0: RS(136,130), 1: RS(144,130) (not supported), 2: RS(272,258), 3: RS(544,514), 4: RS(528,514) (not supported)                     

typedef enum {fec_no_bypass = 0,
              fec_bypass    = 1} fec_bypass_sel_t;                      //FEC_BYPASS : Set to ‘1’ to bypass FEC

typedef struct fec_t                                                    
{
    states_t    fec_enable;
    fec_mode_t  fec_mode;
    fec_bypass_sel_t fec_bypass_sel;
} fec_t;                                                                //FEC

typedef enum {no_serdes_bit_reversing = 0,
              serdes_bit_reversing = 1} bitorder_serdes_t;              //BITORDER SERDES : ‘0’ No Serdes bit reversing

typedef enum {bitorder_0 = 0,
              bitorder_1 = 1,
              bitorder_2 = 2,
              bitorder_3 = 3} bitorder_t;                               //BITORDER : Enables bit reversing on scrambled and/or descrambled data side

typedef struct bit_order_t
{
    bitorder_serdes_t bitorder_serdes;
    bitorder_t bitorder;
} bit_order_t;                                                          //Bitorder

typedef enum {subclass_1 = 0x1} subclass_t;                             //Subclass

typedef enum {cf_0 = 0x0} ctrl_frames_cf_t;                             //Number of Control Frames (CF)

typedef enum {cs_0 = 0x0} ctrl_bits_cs_t;                               //Number of control bits per sample (CS)

typedef enum {hd_0 = 0x0,
              hd_1 = 0x1} high_density_t;                               //High Density (HD) format

// JESD Link Config Struct  
typedef struct jesd_link_config_t 
{
    usecase_id_t            usecase_id;                                 //Link config UC
    sample_rate_t           sample_rate;                                //Sample Rate
    lanes_t                 lanes;                                      //L
    converters_t            converters;                                 //M
    frames_t                frames;                                     //F
    smpl_per_frame_t        smpl_per_frame;                             //S
    smpl_total_bits_t       smpl_total_bits;                            //N'
    jesd_204_std_t          jesd_204_std;                               //204C/D
    serdes_rate_t           serdes_rate;                                //Serdes Rate
    min_e_t                 min_e;                                      //E
    sonif_t                 sonif;                                      //Samples/Sample Clock (SonI)
    smpl_char_clk_ratio_t   smpl_char_clk_ratio;                        //Sample clk ratio
    smpl_trans_pos_t        smpl_trans_pos;                             //Sample Trans Pos/
    smpl_trans_neg_t        smpl_trans_neg;                             //Sample Trans Neg/
    link_iq_bw_t            link_iq_bw;                                 //Link IQ Bandwidth

    subclass_t              subclass;                                   //Subclass
    ctrl_frames_cf_t        ctrl_frames_cf;                             //CF
    ctrl_bits_cs_t          ctrl_bits_cs;                               //CS 
    smpl_res_t              smpl_res;                                   //N
    high_density_t          high_density;                               //HD
    states_t                scr;                                        //SCR
    fec_t                   fec;                                        //FEC
    bit_order_t             bit_order;                                  //Bitorder
    states_t                tl_testmode;                                //TL_testmode
} jesd_link_config_t;

// JESD 204C-Only Registers - RX enums
typedef enum {err_thresh_2  = 0x2,
              err_thresh_3  = 0x3,
              err_thresh_4  = 0x4,
              err_thresh_5  = 0x5,
              err_thresh_9 = 0x9} err_thresh_t;                        //Err_threshold

// JESD 204C-Only Registers 
typedef struct jesd_204c_rx_config_t                                    //204c Rx
{
    states_t                crc3_enable;                                //CRC3_EN
    states_t                crc12_enable;                               //CRC12_EN
    err_thresh_t            rx_emb_err_thresh;                          //Rx_Emb_err_threshold
    err_thresh_t            rx_sh_err_thresh;                           //Rx_Sh_err_threshold
    states_t                cmd_enable;                                 //CMD_EN
} jesd_204c_rx_config_t;

typedef struct jesd_204c_tx_config_t                                    //204c Rx
{
    states_t                crc3_enable;                                //CRC3_EN
    states_t                crc12_enable;                               //CRC12_EN
    int tx_tl_latency;                                                  //tx_tl_latency
    int tx_smpl_req;                                                    //tx_smpl_req
    states_t                cmd_enable;                                 //CMD_EN
} jesd_204c_tx_config_t;

// JESD IP CONFIG 
typedef struct jesd_rx_ip_config_t                                      //JESD RX IP
{
    jesd_204c_rx_config_t       jesd_204c_rx_config;                    //CRC,ERR_THRESH,CMD
    states_t                    jesd_ip_enable;                         //COMCORES_IP_EN    
    states_t                    jesd_rx_ip_sysref_enable;               //Rx_ip_sysref_en
} jesd_rx_ip_config_t;

typedef struct jesd_tx_ip_config_t                                      //JESD TX IP 
{
    jesd_204c_tx_config_t       jesd_204c_tx_config;                    //CRC,CMD
    states_t                    jesd_ip_enable;                         //COMCORES_IP_EN
    states_t                    jesd_tx_ip_sysref_enable;               //Tx_ip_sysref_en
} jesd_tx_ip_config_t;

typedef struct jesd_config_t
{
    jesd_link_config_t              jesd_link_config;                  //LMFS and other link config
    jesd_hbi_config_t               jesd_hbi_config;

    //Rx path config
    jesd_rx_ip_config_t             jesd_rx_ip_config;
    jesd_rx_cmn_csr_config_t        jesd_rx_cmn_csr_config;
    jesd_rx_glue_config_t           jesd_rx_glue_config;
    jesd_h2b_config_t               jesd_h2b_config;

    //Tx path config
    jesd_tx_ip_config_t             jesd_tx_ip_config;
    jesd_tx_cmn_csr_config_t        jesd_tx_cmn_csr_config;
    jesd_tx_glue_config_t           jesd_tx_glue_config;
    jesd_b2h_config_t               jesd_b2h_config;
} jesd_config_t;

// Data type to hold reg configurations 
typedef struct register_config_tbl_t {
    uint32_t addr;
    uint32_t value;
    uint32_t mask;
    char *name;
} register_config_tbl_t;

// Data type to hold table for NOC data
typedef struct noc_tbl_t {
    unsigned  address;
    unsigned  value;
    unsigned  core;
} noc_tbl_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
// JESD_Base Addresses for reg config 
static int g_jesd_host_ids[4]               = {0x40, 0x41, 0x42, 0x43};
static int g_jesd_nsip_base_addr[4]         = {DLNK_JESD0_NSIP_HBI_CSR_BASE, DLNK_JESD1_NSIP_HBI_CSR_BASE, DLNK_JESD2_NSIP_HBI_CSR_BASE, DLNK_JESD3_NSIP_HBI_CSR_BASE};
static int g_jesd_cmn_csr_base_addr[4]      = {DLNK_JESD0_CMN_CSR_BASE, DLNK_JESD1_CMN_CSR_BASE, DLNK_JESD2_CMN_CSR_BASE, DLNK_JESD3_CMN_CSR_BASE};
static int g_jesd_crux_clk_csr_base_addr[4] = {DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE};

static int g_jesd_rx_ip_base_addr[4]        = {DLNK_JESD0_XIP_204C_RX_BASE, DLNK_JESD1_XIP_204C_RX_BASE, DLNK_JESD2_XIP_204C_RX_BASE, DLNK_JESD3_XIP_204C_RX_BASE};
static int g_jesd_rx_glue_base_addr[4]      = {DLNK_JESD0_RX_GLUE_BASE, DLNK_JESD1_RX_GLUE_BASE, DLNK_JESD2_RX_GLUE_BASE, DLNK_JESD3_RX_GLUE_BASE};

static int g_jesd_tx_ip_base_addr[4]        = {DLNK_JESD0_XIP_204C_TX_BASE, DLNK_JESD1_XIP_204C_TX_BASE, DLNK_JESD2_XIP_204C_TX_BASE, DLNK_JESD3_XIP_204C_TX_BASE};
static int g_jesd_tx_glue_base_addr[4]      = {DLNK_JESD0_TX_GLUE_BASE,  DLNK_JESD1_TX_GLUE_BASE,  DLNK_JESD2_TX_GLUE_BASE,  DLNK_JESD3_TX_GLUE_BASE};

/***********************************************
 * GLOBAL FUNCTION PROTOTYPES                  *
 ***********************************************/
/**
 * @brief           jesd_sample_common_function_1: to demonstrate the global function prototype template to follow.
 * @param [in]      caller function called from
 * @param [out]     none ( you can omit if not available)
 * @return          0 on sunccess or error code otherwise
 */
// FPGA
void fpga_clk_and_sysref_period(uint32_t serdes_rate_sel, uint32_t clk_ratio);
void fpga_provided_sysref(uint32_t serdes_rate_sel, uint32_t clk_ratio);
void delay(unsigned int milliseconds );

// INIT
int init_jesd(uint32_t jesd_id, uint32_t serdes_rate, uint32_t clk_ratio);
int init_vex(uint32_t vex_id);

// VEX CIO
int configure_vex_strm2cio(uint32_t rx_vex_id);
int configure_vex_cio2strm(uint32_t tx_vex_id, uint32_t tx_jesd_id);

int configure_jesd_nsip_common(uint32_t jesd_id);

// JESD RX top
int configure_jesd_h2b(uint32_t rx_jesd_id, uint32_t rx_vex_id);
int configure_jesd_rx_cmn_csr(uint32_t rx_jesd_id);
int configure_jesd_rx_crux_clk_csr(uint32_t rx_jesd_id);
int configure_jesd_rx_glue(uint32_t rx_jesd_id);
int configure_jesd_rx_ip(uint32_t rx_jesd_id);

// JESD TX top
int configure_jesd_tx_cmn_csr(uint32_t tx_jesd_id);
int configure_jesd_tx_crux_clk_csr(uint32_t tx_jesd_id);
int configure_jesd_tx_glue(uint32_t tx_jesd_id);
int configure_jesd_tx_ip(uint32_t tx_jesd_id);

int configure_jesd_lpbk(uint32_t jesd_id,uint32_t flow_id);
int configure_jesd_ip_enable(uint32_t jesd_id);

// JESD config 
int configure_jesd_flow(uint32_t flow_id);
int configure_jesd(uint32_t testcase);
int configure_jesd_generic ( usecase_id_t usecase_id, flow_id_t flow_id, vex_id_t  vex_id, jesd_id_t jesd_id );

// VEX config
int configure_vex_tx(uint32_t tx_vex_id);
int configure_vex_rx(uint32_t rx_vex_id);
int configure_vex_rx_tx_lpbk(uint32_t rx_vex_id);

// TEST FLOW
int32_t assign_defaults();
int32_t assign_tc_config(struct jesd_tc_config_t jesd_tc_config_arr[38], uint32_t testcase); 
int32_t assign_jesd_config(struct jesd_config_t jesd_config_arr[22], uint32_t usecase);

// EOT - VEX MEM / REG DUMP 
int dump_reg_jesd_rx(uint32_t jesd_id);
int dump_vmem_vex_rx();
int dump_vmem_vex_rx_2(uint32_t rx_vex_id);
void print_mem(uint32_t base_address, uint32_t display_size);

int dump_reg_jesd_tx(uint32_t jesd_id);
int dump_vmem_vex_tx();
int get_samples_for_stream( unsigned sample_count, unsigned stream_id, unsigned *input_stream_0_array_ptr, unsigned * output_stream_array_ptr);
int read_samples_from_file( char * file_name, unsigned sample_count, unsigned *output_stream_array_ptr);
#endif //__JESD_TEST_COMMON_H__
