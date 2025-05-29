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
 * @file    vex_jesd_nsip_lpbk_8s.c
 * @brief   HOST Configuration code for sending the data from VEX0 to JESD0 and receiving it back at VEX 1 by enabling loopback at JESD NSIP level.
 * @details     1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
                   and receving it back to VEX for all the Sample Rates
                2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
                1. 256 samples (8 vectors) for given data rate will be streamed to JESD from 
                   configured VEX core.
                2. With JESD NSIP loop back enabled between 
                   NSIP output to Tx glue and NSIP input from Rx glue 
                   the data was expected to reach the other VEX core where comparison will be performed.
                4. VEX core on which comparison algo was running will update the comparison result for
                   every vector comparison and once the total 8 vector comparison was done HOST will
                   read the result.
                5. Host will be waiting on a memory location where VEX will update the number of vectors
                   it was processed.
 */
 
/*********************************************** 

 * LOCAL INCLUDE STATEMENTS                    * 

 ***********************************************/ 

#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"

#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"

#include<time.h> 
#include "vex_fw/sim_m64/jesd_tx.map.h"
//#include "vex_producer.map.h"

/***********************************************

 * LOCAL/PRIVATE MACROS AND DEFINES            *
 
 ***********************************************/

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */

#define NUM_TOTAL_VEC_PER_STREAM 64
#define NUM_OF_ELEMENTS_PER_VEC 32
/***********************************************

 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 
 ***********************************************/
// JESD_config Enums
typedef enum {TC_0 = 0,
              TC_1 = 1,
              TC_2 = 2,
              TC_3 = 3,
              TC_4 = 4,
              TC_5 = 5,
              TC_6 = 6,
              TC_7 = 7,
              TC_8 = 8,
              TC_9 = 9,
              TC_10 = 10,
              TC_11 = 11,
              TC_12 = 12,
              TC_13 = 13,
              TC_14 = 14,
              TC_15 = 15,
              TC_16 = 16,
              TC_17 = 17,
              TC_18 = 18,
              TC_19 = 19,
              TC_20 = 20,
              TC_21 = 21} testcase_id_t;                                 //JESD testcase selection
              
typedef enum {UC_5C = 0,
              UC_3A = 1,
              UC_9A = 2,
              UC_2C = 3,
              UC_7C = 4,
              UC_13A = 5,
              UC_3D = 6,
              UC_2B = 7,
              UC_3B = 8,
              UC_5E = 9,
              UC_3C = 10,
              UC_7G = 11,
              UC_5B = 12,
              UC_7E = 13,
              UC_9C = 14,
              UC_7B = 15,
              UC_9B = 16,
              UC_11C = 17,
              UC_11A = 18,
              UC_3E = 19,
              UC_5F = 20} usecase_id_t;                                  //Link config UC 
              
typedef enum {flow_tx_vex_to_dnrt = 0, 
              flow_rx_dnrt_to_vex = 1, 
              flow_tsb_dsm        = 2,
              flow_tsb_capt       = 3,
              flow_rsb_dsm        = 4,
              flow_rsb_capt       = 5, 
              flow_lpbk           = 6} flow_id_t;                       //Flow selection
              
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
    int tx_mem_rd_freq_cfg;
    states_t tx_dp_gate_sel;                                                               
    states_t tx_strm_phm_en;
} jesd_tx_glue_config_t;


// JESD_config structs - CMN CSR
typedef struct jesd_rx_cmn_csr_config_t                                  //JESD RX cmn csr
{
    int rx_ip_clk_ctrl;
    int rx_sysref_tsad;
    int rx_sync_point_ctrl;
    int rx_bfn_sysref_tsad;
    int rx_bfn_sync_point_ctrl;
    states_t rx_clk_gen;
    states_t rx_bfn_sync_point_cnt_en;
}jesd_rx_cmn_csr_config_t;

typedef struct jesd_tx_cmn_csr_config_t                                  //JESD TX cmn csr
{
    int tx_ip_clk_ctrl;
    int tx_sysref_tsad;
    int tx_sync_point_ctrl;
    int tx_bfn_sysref_tsad;
    int tx_bfn_sync_point_ctrl;
    states_t tx_clk_gen;
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
              
typedef enum {smpl_trans_1_0 = 10,
              smpl_trans_1_1 = 11,
              smpl_trans_1_3 = 13,
              smpl_trans_2_1 = 21, 
              smpl_trans_4_1 = 41} smpl_trans_pos_neg_t;                //Sample Transactions Pos/Neg : 1/0, 1/1, 1/3, 2/1, 4/1
              
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
    smpl_trans_pos_neg_t    smpl_trans_pos_neg;                         //Sample Trans Pos/Neg
    
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
typedef enum {err_thresh_3  = 0x3,
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

// Array of Struct to hold TC config    : Refer TC config
struct jesd_tc_config_t jesd_tc_config_arr[22] = 
{
    // testcase_id, usecase_id, flow_id, vex_id, jesd_id
    
    //TC_0 -> arr[0]
    {TC_0, UC_5C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_1, UC_3A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_2, UC_9A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_3, UC_2C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_4, UC_7C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_5, UC_13A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_6, UC_3D, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_7, UC_2B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_8, UC_3B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_9, UC_5E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_10, UC_3C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_11, UC_7G, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_12, UC_5B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_13, UC_7E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_14, UC_9C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_15, UC_7B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_16, UC_9B, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_17, UC_11C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_18, UC_11A, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_19, UC_3E, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    {TC_20, UC_5F, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    
    {TC_21, UC_5C, flow_tx_vex_to_dnrt, vex_0, jesd_0}
};

// Array of Struct to hold link config  : Refer UC config
struct jesd_config_t jesd_config_arr[22] = 
{
    /* jesd_config
    arr[i]={
        jesd_link_config ->         {usecase_id, Sample rate, L, M, F, S, N', JESD04C/D, Serdes rate, E, Soni, clk ratio, smpl_pos/neg},
        jesd_hbi_config_t->         {hbi_int_high_en, hbi_int_low_en},
        
        jesd_rx_ip_config ->        {{crc3_enable, crc12_enable, rx_emb_err_thresh, rx_sh_err_thresh, cmd_enable}, jesd_ip_enable, jesd_rx_ip_sysref_enable} ,
        jesd_rx_cmn_csr_config_t->  {rx_ip_clk_ctrl, rx_sysref_tsad, rx_sync_point_ctrl, rx_bfn_sysref_tsad, rx_bfn_sync_point_ctrl, rx_clk_gen, rx_bfn_sync_point_cnt_en},
        jesd_rx_glue_config_t->     {rx_dp_gate_sel,rx_dp_init_cyc_cnt},
        jesd_h2b_config_t->         {h2b_fifo_ctrl,h2b_credit_ready},
        
        jesd_tx_ip_config_t->       {{crc3_enable, crc12_enable, tx_tl_latency, tx_smpl_req, cmd_enable},jesd_ip_enable,jesd_rx_ip_sysref_enable}
        jesd_tx_cmn_csr_config_t->  {tx_ip_clk_ctrl, tx_sysref_tsad, tx_sync_point_ctrl, tx_bfn_sysref_tsad, tx_bfn_sync_point_ctrl, tx_clk_gen, tx_bfn_sync_point_cnt_en},
        jesd_tx_glue_config_t->     {tx_conv_dp_cfg, tx_mem_rd_freq_cfg, tx_dp_gate_sel, tx_strm_phm_en},
        jesd_b2h_config_t->         {b2h_fifo_ctrl,b2h_credit_ready},
    */
    
    //UC_5C -> arr[0]
    {
        //cmn
        {UC_5C, sample_rate_245P76, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_3, err_thresh_3, disable}, enable, enable},
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
        
        //tx
        {{disable, disable, 0x00000010, 0x00000001, disable},enable,enable},
        {0x00000018, 0x00000017, 0x00170023, 0x00000017, 0x00170023, enable, enable},
        {0x00000181, 0x0000000f, 0x00000004, disable},
        {0x00000184, 0x8},
            
    },

     //UC_3A -> arr[1]
        //cmn
    {
            
        {UC_3A, sample_rate_122P88, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
        {0xFFFFF, 0xFFFFF},
    
        //rx
        {{disable, disable, err_thresh_3, err_thresh_3, disable }, enable, enable },
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    
    },
        
    //UC_9A -> arr[2]
        //cmn
    {
        
            {UC_9A, sample_rate_983P04, l_1, m_2, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_2_1, smpl_trans_1_0},
            {0xFFFFF, 0xFFFFF},
        
        //rx
            {  {disable, disable, err_thresh_9, err_thresh_9, disable }, enable, enable },
            {0x00000000, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
    
    },
        
    //UC_2C -> arr[3]
        //cmn
    {
        
            {UC_2C, sample_rate_61P44, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
            {0xFFFFF, 0xFFFFF},
        
        //rx
            {  {disable, disable, err_thresh_3, err_thresh_3, disable }, enable, enable },
            {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable,enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
    
    },
        
    //UC_7C -> arr[4]
        //cmn
    {
        
            {UC_7C, sample_rate_491P52, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_2_1, smpl_trans_1_0},
            {0xFFFFF, 0xFFFFF},
        
        //rx
            {  {disable, disable, err_thresh_4, err_thresh_4, disable }, enable, enable },
            {0x00000014, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable,enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
   
    },
        
    //UC_13A -> arr[5]
        //cmn
    {
        
            {UC_13A, sample_rate_3932P16, l_4, m_2, f_1, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_2_1, smpl_trans_1_0},
            {0xFFFFF, 0xFFFFF},
        
        //rx
            {  {disable, disable, err_thresh_4, err_thresh_4, disable }, enable, enable },
            {0x00000000, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
        
    },
        
    //UC_3D -> arr[6]
        //cmn
    {
            
            {UC_3D, sample_rate_122P88, l_4, m_32, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
            {0xFFFFF, 0xFFFFF},
        
        //rx
            {  {disable, disable, err_thresh_9, err_thresh_9, disable }, enable, enable },
            {0x00000018, 0x00000007, 0x0003000b, 0x00000007, 0x0003000b, enable,enable},
            {enable, 0x00000100},
            {0x00000184, 0x3},
    
    },
        
    //UC_2B -> arr[7]
    {
        //cmn
        {UC_2B, sample_rate_61P44, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000018, 0x00000013, 0x0003001f, 0x00000013, 0x0003001f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },

    //UC_3B -> arr[8]
    {
        //cmn
        {UC_3B, sample_rate_122P88, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000018, 0x0000000f, 0x000b001b, 0x0000000f, 0x000b001b, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_5E -> arr[9]
    {
        //cmn
        {UC_5E, sample_rate_245P76, l_2, m_16, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_3C -> arr[10]
    {
        //cmn
        {UC_3C, sample_rate_122P88, l_1, m_16, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_7G -> arr[11]
    {
        //cmn
        {UC_7G, sample_rate_491P52, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_5B -> arr[12]
    {
        //cmn
        {UC_5B, sample_rate_245P76, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_7E -> arr[13]
    {
        //cmn
        {UC_7E, sample_rate_491P52, l_2, m_8, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_9C -> arr[14]
    {
        //cmn
        {UC_9C, sample_rate_983P04, l_4, m_8, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_2, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_7B -> arr[15]
    {
        //cmn
        {UC_7B, sample_rate_491P52, l_1, m_4, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_9B -> arr[16]
    {
        //cmn
        {UC_7B, sample_rate_983P04, l_2, m_4, f_4, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_11C -> arr[17]
    {
        //cmn
        {UC_11C, sample_rate_1966P08, l_4, m_4, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_4, err_thresh_4, disable}, enable, enable},
        {0x00000004, 0x00000009, 0x0001000f, 0x00000009, 0x0001000f, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_11A -> arr[18]
    {
        //cmn
        {UC_11A, sample_rate_1966P08, l_2, m_2, f_2, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_4, clk_ratio_1_1, smpl_trans_1_0},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_3, err_thresh_3, disable}, enable, enable},
        {0x00000004, 0x00000003, 0x00030013, 0x00000003, 0x00030013, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    },
    
    //UC_3E -> arr[19]
    {
        //cmn
        {UC_3E, sample_rate_122P88, l_2, m_32, f_32, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_3},
        {0xFFFFF, 0xFFFFF},
        
        //rx
        {{disable, disable, err_thresh_9, err_thresh_9, disable}, enable, enable},
        {0x00000004, 0x00000003, 0x00010005, 0x00000003, 0x00010005, enable,enable},
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
        {0x00000004, 0x00000003, 0x00010005, 0x00000003, 0x00010005, enable,enable},
        {enable, 0x00000100},
        {0x00000184, 0x3},
    }
};

register_config_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};
/***********************************************

 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 
 ***********************************************/
void *g_vex_hdl;
srp_vex_config_t g_vex_params;
srp_vex_t g_srp_vex_hdl;

// JESD_Base Addresses for reg config 
static int g_jesd_host_ids[4]               = {0x40, 0x41, 0x42, 0x43};
static int g_jesd_nsip_base_addr[4]         = {DLNK_JESDABC0_NSIP_HBI_CSR_BASE, DLNK_JESDABC1_NSIP_HBI_CSR_BASE, DLNK_JESDABC2_NSIP_HBI_CSR_BASE, DLNK_JESDABC3_NSIP_HBI_CSR_BASE};
static int g_jesd_cmn_csr_base_addr[4]      = {DLNK_JESDABC0_CMN_CSR_BASE, DLNK_JESDABC1_CMN_CSR_BASE, DLNK_JESDABC2_CMN_CSR_BASE, DLNK_JESDABC3_CMN_CSR_BASE};
static int g_jesd_crux_clk_csr_base_addr[4] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE, DLNK_JESDABC1_CRUX_CLK_CSR_BASE, DLNK_JESDABC2_CRUX_CLK_CSR_BASE, DLNK_JESDABC3_CRUX_CLK_CSR_BASE};

static int g_jesd_rx_ip_base_addr[4]        = {DLNK_JESDABC0_XIP_204C_RX_BASE, DLNK_JESDABC1_XIP_204C_RX_BASE, DLNK_JESDABC2_XIP_204C_RX_BASE, DLNK_JESDABC3_XIP_204C_RX_BASE};
static int g_jesd_rx_glue_base_addr[4]      = {DLNK_JESDABC0_RX_GLUE_BASE, DLNK_JESDABC1_RX_GLUE_BASE, DLNK_JESDABC2_RX_GLUE_BASE, DLNK_JESDABC3_RX_GLUE_BASE};

static int g_jesd_tx_ip_base_addr[4]        = {DLNK_JESDABC0_XIP_204C_TX_BASE, DLNK_JESDABC1_XIP_204C_TX_BASE, DLNK_JESDABC2_XIP_204C_TX_BASE, DLNK_JESDABC3_XIP_204C_TX_BASE};
static int g_jesd_tx_glue_base_addr[4]      = {DLNK_JESDABC0_TX_GLUE_BASE,  DLNK_JESDABC1_TX_GLUE_BASE,  DLNK_JESDABC2_TX_GLUE_BASE,  DLNK_JESDABC3_TX_GLUE_BASE};

vex_strm2cio_config_t vex_strm2cio_config;
vex_cio2strm_config_t vex_cio2strm_config;
jesd_config_t jesd_config;
jesd_tc_config_t jesd_tc_config;
/*********************************************** 

 * STATIC FUNCTION PROTOTYPES                  * 

 ***********************************************/ 
void fpga_clk_and_sysref_period();
void fpga_provided_sysref();
void delay(unsigned int milliseconds );

int init_jesd(uint32_t jesd_id, uint32_t serdes_rate, uint32_t clk_ratio);
int init_vex(uint32_t vex_id);

int configure_vex_strm2cio(uint32_t rx_vex_id);
int configure_vex_cio2strm(uint32_t tx_vex_id, uint32_t tx_jesd_id);

int configure_jesd_nsip_common(uint32_t jesd_id);

int configure_jesd_h2b(uint32_t rx_jesd_id, uint32_t rx_vex_id);
int configure_jesd_rx_cmn_csr(uint32_t rx_jesd_id);
int configure_jesd_rx_crux_clk_csr(uint32_t rx_jesd_id);
int configure_jesd_rx_glue(uint32_t rx_jesd_id);
int configure_jesd_rx_ip(uint32_t rx_jesd_id);


int configure_jesd_tx_cmn_csr(uint32_t tx_jesd_id);
int configure_jesd_tx_crux_clk_csr(uint32_t tx_jesd_id);
int configure_jesd_tx_glue(uint32_t tx_jesd_id);
int configure_jesd_tx_ip(uint32_t tx_jesd_id);

int configure_jesd_ip_enable(uint32_t jesd_id);

int configure_jesd_flow(uint32_t flow_id);
int configure_jesd(uint32_t testcase);

void assign_defaults();
//void assign_link_config(struct jesd_tc_config_t jesd_tc_config_arr[2], uint64_t testcase); 
//void assign_tc_config(struct jesd_link_config_t jesd_link_config_arr[2], uint64_t usecase);

int jesd_eot_reg_dump();
int rx_vex_mem_dump();

/***********************************************

 * STATIC FUNCTION DEFINITIONS                 *
 
 ***********************************************/
/**
 * @brief           Function for assigning TC specific values to jesd_tc_config struct
 * @param [in]      jesd_tc_config_arr[],testcase_id
 * @return          
 */
void assign_tc_config(struct jesd_tc_config_t jesd_tc_config_arr[2], uint64_t testcase)
{
    printf("Assigning TC config \n");
     // JESD TC selection
    jesd_tc_config.testcase_id                                                  = jesd_tc_config_arr[testcase].testcase_id;
    jesd_tc_config.usecase_id                                                   = jesd_tc_config_arr[testcase].usecase_id;
    jesd_tc_config.flow_id                                                      = jesd_tc_config_arr[testcase].flow_id;
    jesd_tc_config.vex_id                                                       = jesd_tc_config_arr[testcase].vex_id;
    jesd_tc_config.jesd_id                                                      = jesd_tc_config_arr[testcase].jesd_id;
}

/**
 * @brief           Function for assigning UC specific values to jesd_link_config struct
 * @param [in]      jesd_config_arr[],usecase_id
 * @return          
 */
 // todo: change the name of function it is not just link_config anymore
void assign_jesd_config(struct jesd_config_t *jesd_config_arr, uint64_t usecase) 
{
    // Select usecase from tbl 
    printf("Assigning link config \n");
    printf("usecase %d \n",usecase);
    
    // JESD link config : Refer UC table
    jesd_config.jesd_link_config.usecase_id                                     = jesd_config_arr[usecase].jesd_link_config.usecase_id;
    jesd_config.jesd_link_config.sample_rate                                    = jesd_config_arr[usecase].jesd_link_config.sample_rate;
    jesd_config.jesd_link_config.lanes                                          = jesd_config_arr[usecase].jesd_link_config.lanes;
    jesd_config.jesd_link_config.converters                                     = jesd_config_arr[usecase].jesd_link_config.converters;
    jesd_config.jesd_link_config.frames                                         = jesd_config_arr[usecase].jesd_link_config.frames;
    jesd_config.jesd_link_config.smpl_per_frame                                 = jesd_config_arr[usecase].jesd_link_config.smpl_per_frame;
    jesd_config.jesd_link_config.smpl_total_bits                                = jesd_config_arr[usecase].jesd_link_config.smpl_total_bits;
    jesd_config.jesd_link_config.serdes_rate                                    = jesd_config_arr[usecase].jesd_link_config.serdes_rate;
    jesd_config.jesd_link_config.min_e                                          = jesd_config_arr[usecase].jesd_link_config.min_e;
    jesd_config.jesd_link_config.sonif                                          = jesd_config_arr[usecase].jesd_link_config.sonif;
    jesd_config.jesd_link_config.smpl_char_clk_ratio                            = jesd_config_arr[usecase].jesd_link_config.smpl_char_clk_ratio;
    jesd_config.jesd_link_config.smpl_trans_pos_neg                             = jesd_config_arr[usecase].jesd_link_config.smpl_trans_pos_neg;
    
     // JESD HBI
    jesd_config.jesd_hbi_config.hbi_int_high_en                                 = jesd_config_arr[usecase].jesd_hbi_config.hbi_int_high_en;  
    jesd_config.jesd_hbi_config.hbi_int_low_en                                  = jesd_config_arr[usecase].jesd_hbi_config.hbi_int_low_en;  

    
    // JESD 204C ONLY REG - RX 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable               = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable              = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable;     
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh         = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh          = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh; 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable                = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable;
    
    // JESD RX IP EN AND SYSREF EN
    jesd_config.jesd_rx_ip_config.jesd_ip_enable                                = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_ip_enable;                   
    jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable                      = jesd_config_arr[usecase].jesd_rx_ip_config.jesd_rx_ip_sysref_enable;
    
    // JESD CMN CSR - RX
    jesd_config.jesd_rx_cmn_csr_config.rx_ip_clk_ctrl                           = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_ip_clk_ctrl;              
    jesd_config.jesd_rx_cmn_csr_config.rx_sysref_tsad                           = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_sysref_tsad;             
    jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_ctrl                       = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_sync_point_ctrl;          
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad                       = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad;          
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl                   = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl;      
    jesd_config.jesd_rx_cmn_csr_config.rx_clk_gen                           	= jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_clk_gen;              
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en                 = jesd_config_arr[usecase].jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en;    

    // JESD GLUE - RX 
    jesd_config.jesd_rx_glue_config.rx_dp_gate_sel                              = jesd_config_arr[usecase].jesd_rx_glue_config.rx_dp_gate_sel;
    jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt                          = jesd_config_arr[usecase].jesd_rx_glue_config.rx_dp_init_cyc_cnt;
    
     // JESD H2B - RX
    jesd_config.jesd_h2b_config.h2b_fifo_ctrl                                   = jesd_config_arr[usecase].jesd_h2b_config.h2b_fifo_ctrl;    
    jesd_config.jesd_h2b_config.h2b_credit_ready                                = jesd_config_arr[usecase].jesd_h2b_config.h2b_credit_ready;
    
    // JESD 204C ONLY REG - TX
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable               = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable              = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable;     
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency             = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req               = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req; 
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable                = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable;
    
     // JESD TX IP EN
    jesd_config.jesd_tx_ip_config.jesd_ip_enable                                = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_ip_enable; 
    jesd_config.jesd_tx_ip_config.jesd_tx_ip_sysref_enable                      = jesd_config_arr[usecase].jesd_tx_ip_config.jesd_tx_ip_sysref_enable;
    
    // JESD CMN CSR - TX
    jesd_config.jesd_tx_cmn_csr_config.tx_ip_clk_ctrl                           = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_ip_clk_ctrl;              
    jesd_config.jesd_tx_cmn_csr_config.tx_sysref_tsad                           = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_sysref_tsad;             
    jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_ctrl                       = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_sync_point_ctrl;          
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad                       = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad;          
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl                   = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl;      
    jesd_config.jesd_tx_cmn_csr_config.tx_clk_gen                           	= jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_clk_gen;              
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en                 = jesd_config_arr[usecase].jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en;    

    // JESD GLUE - TX 
    jesd_config.jesd_tx_glue_config.tx_conv_dp_cfg                              = jesd_config_arr[usecase].jesd_tx_glue_config.tx_conv_dp_cfg;
    jesd_config.jesd_tx_glue_config.tx_mem_rd_freq_cfg                          = jesd_config_arr[usecase].jesd_tx_glue_config.tx_mem_rd_freq_cfg;
    jesd_config.jesd_tx_glue_config.tx_dp_gate_sel                              = jesd_config_arr[usecase].jesd_tx_glue_config.tx_dp_gate_sel;
    jesd_config.jesd_tx_glue_config.tx_strm_phm_en                              = jesd_config_arr[usecase].jesd_tx_glue_config.tx_strm_phm_en;
    
    // JESD B2H - TX
    jesd_config.jesd_b2h_config.b2h_fifo_ctrl                                   = jesd_config_arr[usecase].jesd_b2h_config.b2h_fifo_ctrl;    
    jesd_config.jesd_b2h_config.b2h_credit_ready                                = jesd_config_arr[usecase].jesd_b2h_config.b2h_credit_ready;
    
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
    jesd_config.jesd_link_config.high_density                                   = hd_1;
    jesd_config.jesd_link_config.scr                                            = enable;
    jesd_config.jesd_link_config.fec.fec_enable                                 = disable;
    jesd_config.jesd_link_config.bit_order.bitorder                             = bitorder_3;
    jesd_config.jesd_link_config.tl_testmode                                    = disable;
    
    // JESD HBI
    jesd_config.jesd_hbi_config.hbi_int_high_en                                 = 0xFFFFF;
    jesd_config.jesd_hbi_config.hbi_int_low_en                                  = 0xFFFFF;
   
   
    // JESD 204C ONLY REG - RX 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable               = disable;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable              = disable;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh         = err_thresh_3;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh          = err_thresh_3;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable                = disable;
    
    // JESD RX IP EN AND SYSREF EN
    jesd_config.jesd_rx_ip_config.jesd_ip_enable                                = enable;
    jesd_config.jesd_tx_ip_config.jesd_ip_enable                                = enable;
    jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable                      = enable;
    
    // JESD CMN CSR - RX
    jesd_config.jesd_rx_cmn_csr_config.rx_ip_clk_ctrl                           = 0x00000018;
    jesd_config.jesd_rx_cmn_csr_config.rx_sysref_tsad                           = 0x0000000f;
    jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_ctrl                       = 0x000b001b;
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad                       = 0x0000000f;
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl                   = 0x000b001b;
    jesd_config.jesd_rx_cmn_csr_config.rx_clk_gen                               = enable;
    jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en                 = enable;
    
     // JESD GLUE - RX 
    jesd_config.jesd_rx_glue_config.rx_dp_gate_sel                              = enable;
    jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt                          = 0x00000100;
    
    // JESD H2B - RX
    jesd_config.jesd_h2b_config.h2b_fifo_ctrl                                   = 0x00000184;
    jesd_config.jesd_h2b_config.h2b_credit_ready                                = 0x3;
   
   // JESD 204C ONLY REG - TX
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable               = disable;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable              = disable;  
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency             = 0x00000010;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req               = 0x00000001;
    jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable                = disable;
    
    // JESD TX IP EN
    jesd_config.jesd_tx_ip_config.jesd_ip_enable                                = enable;
    
    // JESD CMN CSR - TX
    jesd_config.jesd_tx_cmn_csr_config.tx_ip_clk_ctrl                           = 0x00000018;
    jesd_config.jesd_tx_cmn_csr_config.tx_sysref_tsad                           = 0x00000017;
    jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_ctrl                       = 0x00170023;
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad                       = 0x00000017;
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl                   = 0x00170023;
    jesd_config.jesd_tx_cmn_csr_config.tx_clk_gen                               = enable;
    jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en                 = enable;
    
    // JESD GLUE - TX 
    jesd_config.jesd_tx_glue_config.tx_conv_dp_cfg                              = 0x00000181;
    jesd_config.jesd_tx_glue_config.tx_mem_rd_freq_cfg                          = 0x0000000f;
    jesd_config.jesd_tx_glue_config.tx_dp_gate_sel                              = 0x00000004;
    jesd_config.jesd_tx_glue_config.tx_strm_phm_en                              = disable;
   
    // JESD B2H - TX
    jesd_config.jesd_b2h_config.b2h_fifo_ctrl                                   = 0x00000184;
    jesd_config.jesd_b2h_config.b2h_credit_ready                                = 0x8;
   
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
* @brief           Function for noc reset
* @param [in]      srp
* @return          status value
*/

static int release_reset_abc_noc (void *srp)
{
int i, rv = 0, flags = 0;
for (i = 0; i < ARRAY_SIZE(g_vex_noc_config); i++)
{
    rv = srp_dev_block_write32(srp,
            SRP_BLOCK_VEX_CFG_CTRL,
            0,
            g_vex_noc_config[i].addr,
            &g_vex_noc_config[i].value,
            1,
            flags);
    }
    return rv;
}

/**
 * @brief           Function for configuring fpga clk and sysref period
 * @param [in]      serdes_rate_sel, clk_ratio
 * @return          
 */
void fpga_clk_and_sysref_period(uint32_t serdes_rate_sel, uint32_t clk_ratio)
{ 
#if(1) 
    printf("starting fpga_clk_sysref \n");
    printf("starting serdes_rate_sel_before_switch:%d, %d\n",serdes_rate_sel, clk_ratio);
    switch (serdes_rate_sel)
    {
        case serdes_rate_8P11008: 
        case serdes_rate_24P33024: 
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 
        
            printf("error: yet to configure clocks for sedes rate id %d \n", serdes_rate_sel);
            break;
            
        case serdes_rate_16P22016: //TODO : provide enum name instead of value
            
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("for 16G 1_1\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
                    break;

                case clk_ratio_2_1:
					printf("for 16G 2_1\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x00");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x00");
                    break;
                    
                default:
                printf("16G default\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
                    break;
            }    
          printf("16G_after def\n");  
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
            
           printf("16G_ip\n");
            //enable jesd_ip path or serial or parallel lpbk
            system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
            //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
            //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
            break;
        
          
        case serdes_rate_32P44032:
            switch (clk_ratio)
            {
                
                case clk_ratio_1_1:
                    printf("32G 1_1\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x14");
                    break;
                    
                case clk_ratio_2_1:
                    printf("for 32G 2_1\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x04");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x04");
                    break;
                    
                default:
                printf("32G default\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x14");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x14");
                    break;
            }
            printf("32G after def\n");
            system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
            system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
                
            printf("32G IP\n");
            //enable jesd_ip path or serial or parallel lpbk
            system("frioPciWrite -F s5a3 -P 0x20000 0x06"); //IP
            //system("frioPciWrite -F s5a3 -P 0x20000 0x04"); //Serial
            //system("frioPciWrite -F s5a3 -P 0x20000 0x05"); //Parallel
            break;
        default:
            printf("error: unexpected serdes rate \n");
            break;
    }
#else
        system("frioPciWrite -F s5a1 -P 0x20000 0x10");
        system("frioPciWrite -F s5b1 -P 0x20000 0x10");
        system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
        system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
    

        //enable jesd_ip path or serial or parallel lpbk
        system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
        //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
        //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
#endif
}

/**
 * @brief           Function for enabling sysref
 * @param [in]      serdes_rate_sel, clk_ratio
 * @return          
 */
void fpga_provided_sysref(uint32_t serdes_rate_sel,uint32_t clk_ratio)
{
       printf("starting fpga_provided_sysref \n");
    printf("starting serdes_rate_sel_before_switch:%d, %d\n",serdes_rate_sel, clk_ratio);
#if(1)

    //enable sysref
    switch (serdes_rate_sel)
    {
        case serdes_rate_8P11008: 
        case serdes_rate_24P33024: 
        case serdes_rate_50P13504: 
        case serdes_rate_66P84672: 
        case serdes_rate_83P5584: 
        case serdes_rate_100P27008: 
        
        printf("error: yet to configure clocks for sedes rate id %d \n", serdes_rate_sel);
        break;
        case serdes_rate_16P22016:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("for 16G 1_1\n");
                    //system("frioPciWrite -F s5a1 -P 0x20000 0x90");
                    //system("frioPciWrite -F s5b1 -P 0x20000 0x90");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
                    break;
                    
                case clk_ratio_2_1:
                    system("frioPciWrite -F s5a1 -P 0x20000 0x80");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x80");
                    break;
                    
                default:
                    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
                    break;
            }
          break;

        
        case serdes_rate_32P44032:
            switch (clk_ratio)
            {
                case clk_ratio_1_1:
                    printf("for 32G 1_1\n");
                    system("frioPciWrite -F s5a1 -P 0x20000 0x94");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x94");
                    break;
                    
                case clk_ratio_2_1:
                    system("frioPciWrite -F s5a1 -P 0x20000 0x84");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x84");
                    break;
                    
                default:
                    system("frioPciWrite -F s5a1 -P 0x20000 0x94");
                    system("frioPciWrite -F s5b1 -P 0x20000 0x94");
                    break;
            }
            break;
       default:
            printf("error: unexpected serdes rate \n");
            break;
            

    }

    printf("after def\n");  

#else
      //enable sysref
        system("frioPciWrite -F s5a1 -P 0x20000 0x90");
        system("frioPciWrite -F s5b1 -P 0x20000 0x90");
#endif
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
    delay(100);
    
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
    delay(100);
    
    printf("INFO: Initialize srp\n");
	init(); // Initialize the srp
	delay(1000);
    
    jesd_reset(1 << jesd_id,0);
    delay(1000);
    
    fpga_provided_sysref(jesd_config.jesd_link_config.serdes_rate, jesd_config.jesd_link_config.smpl_char_clk_ratio);
    printf("@@@@@@@@@@@@@@Clock and Sysref Done@@@@@@@@@@@@@@\n");
	delay(100);
	return rv;
}

/**
 * @brief           Function for Init sequence : Vex
 * @param [in]      rx_vex_id
 * @return          status
 */      
int init_vex(uint32_t rx_vex_id)
{
	int rv = 0;

    //clear vex memory
    printf("\n########Starting to clear vex mem from 0\n");
    vex_mem_clear(rx_vex_id, srp);
    printf("########Done clearing vex mem 0\n\n");
    
	memset(&g_vex_params, 0, sizeof(g_vex_params));
    memset(&g_srp_vex_hdl, 0, sizeof(g_srp_vex_hdl));
    
	g_vex_hdl = &g_srp_vex_hdl;

	if ((rv = srp_vex_config(srp, &g_vex_hdl, &g_vex_params)))
		return rv;
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
        // STRM2CIO interrupt en, fifo status ,word cnt ctl
        {STRM2CIO_MEM_STRM2CIO_INT_ENABLE_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_int_en, STRM2CIO_MEM_STRM2CIO_INT_ENABLE_WR_MASK, "STRM2CIO_INT_ENABLE"},
        {STRM2CIO_MEM_STRM2CIO_FIFO_STATUS_CTL_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_fifo_sts_ctrl, STRM2CIO_MEM_STRM2CIO_FIFO_STATUS_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
        {STRM2CIO_MEM_STRM2CIO_WORD_CNT_CTL_ADR(strm2cio_base), vex_strm2cio_config.strm2cio_wrd_cnt_ctrl, STRM2CIO_MEM_STRM2CIO_WORD_CNT_CTL_WR_MASK, "STRM2CIO_MEM_WORD_CNT_CTL"}
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
    
    uint64_t cio2strm_range_en                  = 0x0;
    uint64_t str_reg_addr_offset                = 0x4;
    uint64_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint64_t str_id                             = 0x0;
    
    uint64_t cio2strm_mem_addr_low_value        = 0x00000000;
    uint64_t cio2strm_mem_addr_low_offset       = 0x20000;
    
    uint64_t cio2strm_mem_addr_high_offset      = 0x1FFFF;
    uint64_t cio2strm_mem_addr_offset_value     = 0x00000000;
    uint64_t cio2strm_mem_addr_dest_value       = jesd_host_id;
    
    switch (num_of_streams)
    {
        case 0x8:
                cio2strm_range_en              = 0xff;
                break;
        
        case 0x4:
                cio2strm_range_en              = 0xf;
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
        {CIO2STRM_MEM_CIO2STRM_INT_ENABLE_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_int_en,
            CIO2STRM_MEM_CIO2STRM_INT_ENABLE_WR_MASK,
            "CIO2STRM_INT_ENABLE"},
            
		{CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_fifo_sts_ctrl,
            CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_WR_MASK,
            "CIO2STRM_FIFO_STATUS_CTL"},
            
		{CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base),
            vex_cio2strm_config.cio2strm_wrd_cnt_ctrl,
            CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_WR_MASK,
            "CIO2STRM_WORD_CNT_CTL"},
            
		{CIO2STRM_MEM_CIO2STRM_RANGE_EN_ADR(cio2strm_base),
            cio2strm_range_en,
            CIO2STRM_MEM_CIO2STRM_RANGE_EN_WR_MASK,
            "CIO2STRM_RANGE_EN"}
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
            {(CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                (cio2strm_mem_addr_low_value + (str_id * cio2strm_mem_addr_low_offset)),
                CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK,
                "CIO2STRM_MEM_ADDR_LOW"},
                
            {(CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                (cio2strm_mem_addr_low_value + (str_id * cio2strm_mem_addr_low_offset)) + cio2strm_mem_addr_high_offset,
                CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK,
                "CIO2STRM_MEM_ADDR_HIGH"},
                
            {(CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                cio2strm_mem_addr_offset_value,
                CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK,
                "CIO2STRM_MEM_OFFSET"},
                
            {(CIO2STRM_MEM_CIO2STRM_STRM_DEST0_ADR(cio2strm_base) + (str_id * str_reg_addr_offset)),
                cio2strm_mem_addr_dest_value,
                CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK,
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
        // NSIP_HBI interrupt en - Rx path
        {NSIP_HBI_INTR_INT_HIGH_EN_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_hbi_config.hbi_int_high_en,
            NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK,
            "NSIP_HBI_INTR_INT_HIGH_EN"},
            
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
    
    uint64_t str_reg_addr_offset                = 0x4;
    uint64_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint64_t str_id                             = 0x0;
    
    uint64_t h2b_buf_sz_hw_tbl_value            = 0x0;
    uint64_t h2b_tk_route_tbl_value             = rx_vex_id;
    uint64_t h2b_route_tbl_value                = rx_vex_id;
    uint64_t h2b_md_route_tbl_value             = rx_vex_id;
    
    uint64_t h2b_addr_lkup_tbl_value            = 0x80000000;
    uint64_t h2b_tk_addr_lkup_tbl_value         = 0x18000;
    uint64_t h2b_md_ctrl_tbl_value              = 0x1f;
    
    uint64_t h2b_addr_lkup_tbl_offset           = 0x800;
    uint64_t h2b_tk_addr_lkup_tbl_offset        = 0x4;
      
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
        {NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_h2b_config.h2b_fifo_ctrl,
            NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK,
            "NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL"},
        
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
            {(NSIP_HBI_H2B_MD_CONTROL_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                h2b_md_ctrl_tbl_value,
                NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK,
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
    
    uint64_t str_reg_addr_offset                = 0x4;
    uint64_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint64_t str_id                             = 0x0;
    
    uint64_t b2h_addr_map_tbl_value             = 0x80000000;
    uint64_t b2h_addr_mask_tbl_value            = 0x1FFFF;

    uint64_t b2h_addr_map_tbl_offset            = 0x20000;
    
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
        default:
                b2h_addr_map_tbl_offset         = 0x20000;
                b2h_addr_mask_tbl_value         = 0x1FFFF;
            break;
    }
    
    register_config_tbl_t jesd_b2h_cmn_config_tbl[] = 
    {
        // B2H Registers
        // Set high (almost full) and low (almost empty) watermarks 
        {NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_b2h_config.b2h_fifo_ctrl,
            NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK,
            "B2H_FIFO_CONTROL"},
            
        // Set maximum credit value
		{NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_ADR(jesd_nsip_hbi_base),
            jesd_config.jesd_b2h_config.b2h_credit_ready,
            NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK,
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
            {(NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                (b2h_addr_map_tbl_value + (str_id * b2h_addr_map_tbl_offset)),
                NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK,
                "B2H_ADDR_MAP_TBL"},
                
            // ADDR MASK TBL: 28-bit Mask bits (‘1’=address bit is masked out) for the address range specified in the B2H_ADDR_MAP_TBL reg       
            {(NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_ADR(jesd_nsip_hbi_base) + (str_id * str_reg_addr_offset)),
                b2h_addr_mask_tbl_value,
                NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK,
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

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, 
                            jesd_config.jesd_rx_cmn_csr_config.rx_ip_clk_ctrl, 
                            JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL"))
        return rv;               
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_clk_gen,
                            JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET,
                            jesd_config.jesd_rx_cmn_csr_config.rx_bfn_sync_point_cnt_en,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE"))
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
    
    uint64_t num_of_streams                     = jesd_config.jesd_link_config.converters / 2;
    uint64_t str_id                             = 0x0;
    uint64_t tx_num_valid_str                   = 0x0;
    
    switch (num_of_streams)
    {
        case 0x8:
                tx_num_valid_str              = 0xff;
                break;
        
        case 0x4:
                tx_num_valid_str              = 0xf;
                break;
        
        case 0x1:
                tx_num_valid_str              = 0x1;
                break;
            
        default:
                tx_num_valid_str              = 0x1;
                break;
    }
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET,
                            tx_num_valid_str,
                            JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR"))
        return rv;               
    
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD"))
        return rv;               

	//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
	if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL"))
        return rv;               
    
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD"))
        return rv;               
	
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL"))
        return rv;               

	//this register can be ingnored as per RP, roshan 12/02/24
    /*if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET,
                                jesd_config.jesd_tx_cmn_csr_config.tx_clk_1p5g_div_en,
                                JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK,
                                "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE"))
        return rv;     */
        
	if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_clk_gen,
                            JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE"))
        return rv;               
				
	//this register can be ingnored as per RP, roshan 12/02/24
    /*if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET,
                                jesd_config.jesd_tx_cmn_csr_config.tx_num_valid_str,
                                JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK,
                                "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE"))
        return rv;   */            
	
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_bfn_sync_point_cnt_en,
                            JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE"))
        return rv;               
			
	if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET,
                            jesd_config.jesd_tx_cmn_csr_config.tx_ip_clk_ctrl,
                            JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL"))
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
    
    uint64_t rx_wr_mem_tbl          = 0x00000000;
    uint64_t rx_rd_mem_tbl          = 0x00000000;
    uint64_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;;
    uint64_t str_reg_addr_offset    = 0x4;
    uint64_t str_id                 = 0x0;
    uint64_t rx_wr_mem_tbl_offset   = 0x0;
    uint64_t rx_rd_mem_tbl_offset   = 0x0;
    uint64_t rx_mem_strm_cfg        = 0x0;
    uint64_t rx_strm_cfg            = 0x0;
    
    switch (num_of_streams)
    {
        case 0x10:
            rx_wr_mem_tbl_offset = 0x20;
            rx_rd_mem_tbl_offset = 0x220;
            rx_mem_strm_cfg      = 0x1f;
            rx_strm_cfg          = 0xf0;
            break;
        
        case 0x8:
            rx_wr_mem_tbl_offset = 0x40;
            rx_rd_mem_tbl_offset = 0x240;
            rx_mem_strm_cfg      = 0x3f;
            rx_strm_cfg          = 0xe8;
            break;
        
        case 0x4:
            rx_wr_mem_tbl_offset = 0x80;
            rx_rd_mem_tbl_offset = 0x280;
            rx_mem_strm_cfg      = 0x7f;
            rx_strm_cfg          = 0xe4;
            break;
        
        case 0x2:
            rx_wr_mem_tbl_offset = 0x100;
            rx_rd_mem_tbl_offset = 0x300;
            rx_mem_strm_cfg      = 0xff;
            rx_strm_cfg          = 0xe2;
            break;
       
       case 0x1:
            rx_wr_mem_tbl_offset = 0x0;
            rx_rd_mem_tbl_offset = 0x0;
            rx_mem_strm_cfg      = 0x1ff;
            rx_strm_cfg          = 0xe1;
            break;
        default:
            rx_wr_mem_tbl_offset = 0x0;
            rx_rd_mem_tbl_offset = 0x0;
            rx_mem_strm_cfg      = 0x0;
            rx_strm_cfg          = 0x0;
            break;
    }
    
    // For each JESD I/Q stream (up to 16), provide the write and read memory base addresses for each stream
    for (str_id = 0x0; str_id < num_of_streams; str_id++)
    {
        // Specify NSIP write base address for each JESD stream
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)),
                                 (rx_wr_mem_tbl + (str_id * rx_wr_mem_tbl_offset)),
                                 JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK,
                                 "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL"))
            return rv;                               
    
        // Specify NSIP read base address and Stream ID
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET + (str_id * str_reg_addr_offset)), 
                                 (rx_rd_mem_tbl + (str_id * rx_rd_mem_tbl_offset)),
                                 JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK,
                                 "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL"))
            return rv;  
    }
    
    // Configure remaining parameters that are common to all streams
    // FLITS_PER_STRM: Typically 7 (for 8 flits) before beginning read of RSB , NUM_STRM: : Refer UC table
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET,
                            rx_strm_cfg,
                            JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK,
                            "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG"))
        return rv;                   
    
    // Specify max flits/depth allocated to memory minus 1. 
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET,
                            rx_mem_strm_cfg,
                            JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK,
                            "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG"))
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
    
    uint64_t tx_strm_mem_addr          = 0x00000000;
    uint64_t tx_strm_mem_addr_offset   = 0x00000000;
    uint64_t tx_strm_mem_size          = 0x00000000;
    uint64_t tx_tsb_trig_en            = 0x00000000;
    uint64_t num_of_streams            = jesd_config.jesd_link_config.converters / 2;;
    uint64_t str_reg_addr_offset       = 0x4;
    uint64_t str_id                    = 0x0;
    
    // Note: The size should be set the same for all streams, and should only be 4k, 8k, 16k, 32k or 64k to align with the reading as defined in reg STRM_MEM_INST_CNT
    switch (num_of_streams)
    {
        case 0x10:
            tx_strm_mem_addr_offset   = 0x00001000;
            tx_strm_mem_size          = 0x00000fff;
            tx_tsb_trig_en            = 0x00010fff;
            break;
        
        case 0x8:
            tx_strm_mem_addr_offset   = 0x00001000;
            tx_strm_mem_size          = 0x00000fff;
            tx_tsb_trig_en            = 0x00010fff;
            break;
        
        case 0x4:
            tx_strm_mem_addr_offset   = 0x00001000;
            tx_strm_mem_size          = 0x00000fff;
            tx_tsb_trig_en            = 0x00010fff;
            break;
        
        case 0x2:
            tx_strm_mem_addr_offset   = 0x00001000;
            tx_strm_mem_size          = 0x00000fff;
            tx_tsb_trig_en            = 0x00010fff;
            break;
            
        default:
            tx_strm_mem_addr_offset   = 0x00001000;
            tx_strm_mem_size          = 0x00000fff;
            tx_tsb_trig_en            = 0x00010fff;
            break;
    }
    
    
    // For each stream (up to 16), provide the stream memory base and size & number of chains/converters : Refer UC table
    for (str_id = 0x0; str_id < num_of_streams; str_id++)
    {
        // Configure the mapping table from NSIP ID # to the TSB ID# (memory address and size)
        // Specify stream memory base address for each stream.Mapping table from NSIP ID # to JESD controller port
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET + (str_id * str_reg_addr_offset)),
                                 (tx_strm_mem_addr + (str_id * tx_strm_mem_addr_offset)),
                                 JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK,
                                 "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR"))
            return rv;                               
    
        // Specify stream memory size for each stream
        if(rv = write_reg_18a((jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET + (str_id * str_reg_addr_offset)), 
                                 tx_strm_mem_size,
                                 JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK,
                                 "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE"))
            return rv;  
    }
    
    // Specify tsb trig en
    if(rv = write_reg_18a(jesd_crux_clk_csr_base + JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET,
                            tx_tsb_trig_en,
                            JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK,
                            "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG"))
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
    
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET,
                            jesd_config.jesd_link_config.sonif,
                            JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK,
                            "RX_GLUE_MEM_RX_GLUE_SONI"))
        return rv;
    
    // dp_gate_sel, as per simval log
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_gate_sel,
                            JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK,
                            "RX_DATAPATH_GATE_SEL"))
        return rv;
    // dp_init_cyc_cnt enable, as per simval log   
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt,
                            JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK,
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
    
    uint64_t tx_strm_mem_inst_cnt      = 0x00000000;
    uint64_t num_of_streams            = jesd_config.jesd_link_config.converters / 2;;
    uint64_t str_reg_addr_offset       = 0x4;
    uint64_t str_id                    = 0x0;
    
    // Note: This should align with the assignments for the NSIP assignments in reg STRM_ID_MEM_ADDR/SIZE
    switch (num_of_streams)
    {
        case 0x10:
            tx_strm_mem_inst_cnt      = 0x01;
            break;
        
        case 0x8:
            tx_strm_mem_inst_cnt      = 0x01;
            break;
        
        case 0x4:
            tx_strm_mem_inst_cnt      = 0x01;
            break;
        
        case 0x2:
            tx_strm_mem_inst_cnt      = 0x01;
            break;
            
        default:
            tx_strm_mem_inst_cnt      = 0x01;
            break;
    }
    
    // Specify number of 4kB memory blocks assigned for each stream (same for all streams)
    if(rv = write_reg_18a(jesd_tx_glue_base + JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET,
                            tx_strm_mem_inst_cnt,
                            JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK,
                            "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT"))
        return rv;
        
    // Specify sample width, SonI and shift size : Refer UC table
    if(rv = write_reg_18a(jesd_tx_glue_base + JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_conv_dp_cfg,
                            JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK,
                            "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG"))
        return rv;
    
    // Specify memory read frequency : Refer UC table 
    if(rv = write_reg_18a(jesd_tx_glue_base + JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_mem_rd_freq_cfg,
                            JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK,
                            "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG"))
        return rv;
        
    if(rv = write_reg_18a(jesd_tx_glue_base + JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_dp_gate_sel,
                            JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK,
                            "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL"))
        return rv;
        
    if(rv = write_reg_18a(jesd_tx_glue_base + JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET,
                            jesd_config.jesd_tx_glue_config.tx_strm_phm_en,
                            JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK,
                            "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN"))
        return rv;
        
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
    int sample_x8_ratio =0x0;
    int soni = 0x0;
    
    sample_x8_ratio = (jesd_config.jesd_link_config.smpl_per_frame*8) / (jesd_config.jesd_link_config.sonif);
    soni 			= (jesd_config.jesd_link_config.sonif) - 0x1;
    soni 			= (sample_x8_ratio<<5) | soni;
    
    // Pre-configure JESD receiver per the particular use chain
    // Set to subclass 1
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_SUBCLASS_OFFSET, 
                            jesd_config.jesd_link_config.subclass, 
                            JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_SUBCLASS"))
        return rv;
        
    // Number of Control Frames (CF). No Control bits, so keep default register value.
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CF_OFFSET,
                            jesd_config.jesd_link_config.ctrl_frames_cf,
                            JESD_XIP_204C_RX_MEM_RX_CF_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CF"))
        return rv;
    
    // Number of control bits per sample (CS). No Control bits are used for JESD Rx (CS = 0).    
     if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CS_OFFSET,
                            jesd_config.jesd_link_config.ctrl_bits_cs,
                            JESD_XIP_204C_RX_MEM_RX_CS_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CS"))
        return rv;
        
    // Number of octets per Frame (F) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_F"))
        return rv;
        
    // Number of Lanes (L) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_L"))
        return rv;
        
    // Sample resolution (N) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_RX_MEM_RX_N_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_N"))
        return rv;
        
    // Number of converters (M) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_M"))
        return rv;
    
    // Total number of bits per sample (N’) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_NTOTAL"))
        return rv;
   
    // Number of samples (S) – 1 per converter : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_S_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_per_frame) - 1),
                            JESD_XIP_204C_RX_MEM_RX_S_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_S"))
        return rv;
    
    // Enable High Density (HD) format : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_HD_OFFSET,
                            jesd_config.jesd_link_config.high_density,
                            JESD_XIP_204C_RX_MEM_RX_HD_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_HD"))
        return rv;
    
    // Enable scrambling
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET,
                            jesd_config.jesd_link_config.scr,
                            JESD_XIP_204C_RX_MEM_RX_SCR_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_SCR"))
        return rv;
        
    // Sample-to-Character Clock ratio : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_OFFSET,
                            jesd_config.jesd_link_config.smpl_char_clk_ratio,
                            JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CLK_RATIO"))
        return rv;
   
    // 204C -FEC en, 204D - FEC mode, FEC bypass
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET,
                            jesd_config.jesd_link_config.fec.fec_enable,
                            JESD_XIP_204C_RX_MEM_RX_FEC_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_FEC"))
        return rv; 
        
    // Bit order Serdes and En  
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_OFFSET, 
                            jesd_config.jesd_link_config.bit_order.bitorder,
                            JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_BIT_ORDER"))
        return rv;
    
    // Transport Layer test mode En
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET,
                            jesd_config.jesd_link_config.tl_testmode,
                            JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE"))
        return rv;
    
    // Samples on Interface (SONI). Set to SONI – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET,
                            soni,
                            JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_SONIF"))
        return rv;
    
    // JESD 204C-Only Registers
    // CRC-3 error checking
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable,
                            JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CRC3_EN"))
        return rv;
     
    // Enable CRC-12 per use case
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable, 
                            JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CRC12_EN"))
        return rv;
        
    //Number of Multiblocks per Extended Multiblocks (E) – 1 
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_E_OFFSET,
                            ((jesd_config.jesd_link_config.min_e) - 1),
                            JESD_XIP_204C_RX_MEM_RX_E_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_E"))
        return rv;
    
    // Extended Multi Block state machine error threshold. Use default value (8)
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh,
                            JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR"))
        return rv;
        
    // Sync header state machine error threshold. Use default value (16)
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh,
                            JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR"))
        return rv;
        
    // Command Channel not used
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_CMD_EN_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable,
                            JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_CMD_EN"))
        return rv;
    
    print("INFO: JESD IP configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring JESD IP Resgisters for Tx path
 * @param [in]      tx_jesd_id
 * @return          status
 */     
// JESD RX reg
int configure_jesd_tx_ip(uint32_t tx_jesd_id)
{
    int i = 0, rv;
    int jesd_tx_ip_base = g_jesd_tx_ip_base_addr[tx_jesd_id];
    int sample_x8_ratio =0x0;
    int soni = 0x0;
    
    sample_x8_ratio=(jesd_config.jesd_link_config.smpl_per_frame*8)/(jesd_config.jesd_link_config.sonif);
    soni = (jesd_config.jesd_link_config.sonif) - 0x1;
    soni = (sample_x8_ratio<<5) | soni;
    
    // Pre-configure JESD receiver per the particular use chain
    // Set to subclass 1
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_SUBCLASS_OFFSET, 
                            jesd_config.jesd_link_config.subclass, 
                            JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_SUBCLASS"))
        return rv;
        
    // Number of Control Frames (CF). No Control bits, so keep default register value.
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CF_OFFSET,
                            jesd_config.jesd_link_config.ctrl_frames_cf,
                            JESD_XIP_204C_TX_MEM_TX_CF_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CF"))
        return rv;
    
    // Number of control bits per sample (CS). No Control bits are used for JESD Rx (CS = 0).    
     if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CS_OFFSET,
                            jesd_config.jesd_link_config.ctrl_bits_cs,
                            JESD_XIP_204C_TX_MEM_TX_CS_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CS"))
        return rv;
        
    // Number of octets per Frame (F) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_F_OFFSET,
                            ((jesd_config.jesd_link_config.frames) - 1),
                            JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_F"))
        return rv;
        
    // Number of Lanes (L) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_L_OFFSET,
                            ((jesd_config.jesd_link_config.lanes) - 1),
                            JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_L"))
        return rv;
        
    // Sample resolution (N) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_N_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_res) - 1),
                            JESD_XIP_204C_TX_MEM_TX_N_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_N"))
        return rv;
        
    // Number of converters (M) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_M_OFFSET,
                            ((jesd_config.jesd_link_config.converters) - 1),
                            JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_M"))
        return rv;
    
    // Total number of bits per sample (N’) – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_NTOTAL_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_total_bits) - 1),
                            JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_NTOTAL"))
        return rv;
   
    // Number of samples (S) – 1 per converter : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_S_OFFSET,
                            ((jesd_config.jesd_link_config.smpl_per_frame) - 1),
                            JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_S"))
        return rv;
    
    // Enable High Density (HD) format : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_HD_OFFSET,
                            jesd_config.jesd_link_config.high_density,
                            JESD_XIP_204C_TX_MEM_TX_HD_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_HD"))
        return rv;
    
    // Enable scrambling
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET,
                            jesd_config.jesd_link_config.scr,
                            JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_SCR"))
        return rv;
        
    // Sample-to-Character Clock ratio : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET,
                            jesd_config.jesd_link_config.smpl_char_clk_ratio,
                            JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO"))
        return rv;
   
    // 204C -FEC en, 204D - FEC mode, FEC bypass
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_FEC_OFFSET,
                            jesd_config.jesd_link_config.fec.fec_enable,
                            JESD_XIP_204C_TX_MEM_TX_FEC_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_FEC"))
        return rv; 
        
    // Bit order Serdes and En  
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_OFFSET, 
                            jesd_config.jesd_link_config.bit_order.bitorder,
                            JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_BIT_ORDER"))
        return rv;
    
    // Transport Layer test mode En
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_OFFSET,
                            jesd_config.jesd_link_config.tl_testmode,
                            JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE"))
        return rv;
    
    // Samples on Interface (SONI). Set to SONI – 1 : Refer UC table
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET,
                            soni,
                            JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_SONIF"))
        return rv;
    
    // JESD 204C-Only Registers
    // CRC-3 error checking
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CRC3_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc3_enable,
                            JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CRC3_EN"))
        return rv;
     
    // Enable CRC-12 per use case
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CRC12_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.crc12_enable, 
                            JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CRC12_EN"))
        return rv;
        
    //Number of Multiblocks per Extended Multiblocks (E) – 1 
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_E_OFFSET,
                            ((jesd_config.jesd_link_config.min_e) - 1),
                            JESD_XIP_204C_TX_MEM_TX_E_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_E"))
        return rv;
    
    // Extended Multi Block state machine error threshold. Use default value (8)
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_tl_latency,
                            JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG"))
        return rv;
        
    // Sync header state machine error threshold. Use default value (16)
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.tx_smpl_req,
                            JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG"))
        return rv;
        
    // Command Channel not used
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_CMD_EN_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_204c_tx_config.cmd_enable,
                            JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_CMD_EN"))
        return rv;
    
    print("INFO: JESD IP configuration completed for JESD%d in Tx path\n", tx_jesd_id);
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
    if(rv = write_reg_18a(jesd_rx_ip_base + JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_ip_enable,
                            JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_WR_MASK,
                            "JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE"))
        return rv;
        
    // Enable JESD transmitter
    if(rv = write_reg_18a(jesd_tx_ip_base + JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_ip_enable,
                            JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_WR_MASK,
                            "JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE"))
        return rv;                    
    
    // Cmn_csr sysref enable, as per simval log
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_OFFSET,
                            jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable,
                            JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE"))
        return rv;
    
    // Cmn_csr sysref enable, as per simval log
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_OFFSET,
                            jesd_config.jesd_tx_ip_config.jesd_tx_ip_sysref_enable,
                            JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE"))
        return rv;
            
    print("INFO: JESD RX and TX IP en configuration completed for JESD%d in Rx path\n", jesd_id);
    return rv;
}

/**
 * @brief           Function configuring VEX: Tx path
 * @param [in]      tx_vex_id
 * @return          status
 */
int configure_vex_tx(uint32_t tx_vex_id)
{
    int rv = 0;
	int flags = 0;
	int lc, i, j;
	int dmem_offset = 0x4000;
	int host_flag = 1;
    int total_streams_0 = 8;
    
    int vex_tx_offset_val[] = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base,
                                    HIVE_ADDR_jesd_tx_g_timeout_cycles};
    
    unsigned vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,255};
    
    unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
									HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
									HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
									HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
									
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
	unsigned int add_val[1];
    
    //configure_jesd(testcase);
    
    // Status reg dump
    printf("Before Init\n");
    printf("dumping tsb write pointers-before init\n");
    system("srpRead 0x06709300 1");
    
	printf("dumping TX_SAMPLE_REQ_REG\n");
    system("srpRead 0x067013e0 1");
	printf("dumping TX_CONV_DP_CONFIG\n");
    system("srpRead 0x0670d014 1");
	printf("dumping TX_MEM_RD_FREQ\n");
    system("srpRead 0x0670d018 1");
	printf("dumping TX_DATAPATH_GATE_SEL\n");
    system("srpRead 0x0670d01c 1");
    
   
    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    printf("Host: start vex tx program load \n");
    if ((rv = srp_vex_loader(g_vex_hdl, tx_vex_id, "vex_fw/sim_m64/jesd_tx.fw")))
            return rv;
    printf("Host: vex program load - done\n");
    
    
    printf("Loading the host parameters to VEX%d\n",tx_vex_id);
    for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        tx_vex_id,
                        dmem_offset + vex_tx_offset_val[lc],
                        &vex_tx_val_kargs[lc],
                        1,
                        flags)))
            return rv;
        //sleep(1);
    }                  
    printf("Host parameters loaded to Vex%d\n",tx_vex_id);
    
    printf("Input vectors generation start for Vex0 \n");
    /* Input Vector Generation VEX_0*/
	for (lc = 0; lc < total_streams_0; lc++)
	{
        printf("DEBUG: vex_id %d, lc = %d\n",tx_vex_id, lc);
        for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
        {
            
            for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
            {
				val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
				val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
				val_inp[i][j] = val_inp[i][j] | (lc << 28 | lc << 12);
				//val_inp[i][j] = 0xb2b2a5a5;
				
            }
        }
     
        if ((rv = srp_vex_memid_store(g_vex_hdl,
                            tx_vex_id,
                            SRP_VEX_VMEM,
                            vex_tx_buffer_addr[lc],/*local_addr*/
                            val_inp[0],
                            (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
        printf(" DEBUG: vex_id %d, addr = 0x%x , data = 0x%x\n", tx_vex_id, vex_tx_buffer_addr[lc], val_inp[0][0]);
    }
    printf("Input vectors generated for Vex%d\n",tx_vex_id);
     
    printf("Host: Vex%d program start\n",tx_vex_id);
    srp_vex_start(g_vex_hdl, tx_vex_id, 0); // vex_0 start
    printf("Host: vex program start - done Vex%d\n",tx_vex_id);
    
    int b2h_flit_count  = 0;
    b2h_flit_count  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
    printf("\n");
    printf("\nreading flit count after jesd enable\n");
    printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",b2h_flit_count);
    
    /*Signal VEX to start continuous flow*/
    //for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
    
    if ((rv = srp_dev_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    tx_vex_id,
                    dmem_offset + HIVE_ADDR_jesd_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;
    
    printf("DEBUG: dumping b2h flit count-After vex start \n");
    uint32_t z=0;
    printf("\n");
    for (z=0;z<5;z++)
	{
		int b2h_flit_count  = 0;
        b2h_flit_count  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
        printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",b2h_flit_count);
	}
    printf("\n");
   
    printf("\n");
    printf("dumping jesd h2b flit count\n");
    system("srpRead 0x06705314 1");
    printf("dumping jesd b2h flit count\n");
    system("srpRead 0x06705014 1");
    printf("dumping tsb write pointers \n");
    system("srpRead 0x06709300 16");
    printf("dumping vex0 flit count\n");
    system("srpRead 0x02802024 1");
    printf("dumping vex1 flit count\n");
    system("srpRead 0x02842024 1");
	
	printf("reading mem_size\n");
    system("srpRead 0x06709280 1");
	

    int wptr,hbi_intr,b2h_fifo,tx_strm;
    b2h_flit_count  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
    wptr  = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_WPTR0_OFFSET, "TX_STRM_MEM_WPTR0");
    printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",b2h_flit_count);
    printf("Present value of TX_STRM_MEM_WPTR0 is 0x%x \n",wptr);
    
    hbi_intr  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_STATUS_OFFSET, "NSIP_HBI_INTR_INT_STATUS");
    b2h_fifo  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_FF_B2H_FIFO_STATUS_OFFSET, "NSIP_HBI_B2H_FF_B2H_FIFO_STATUS");
    tx_strm  = read_reg_18a(g_jesd_crux_clk_csr_base_addr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
    printf("Present value of NSIP_HBI_INTR_INT_STATUS is 0x%x \n",hbi_intr);
    printf("Present value of NSIP_HBI_B2H_FF_B2H_FIFO_STATUS is 0x%x \n",b2h_fifo);
    printf("Present value of JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0 is 0x%x \n",tx_strm);
    printf("\n");
   
	printf("After INIT\n");

    
    printf("reading vex time_out cycles\n");
    system("srpRead 0x63.0.0x4030 1");
	
	printf("At the End of Test\n");
    printf("dumping TX_SAMPLE_REQ_REG\n");
    system("srpRead 0x067013e0 1");
	printf("dumping TX_CONV_DP_CONFIG\n");
    system("srpRead 0x0670d014 1");
	printf("dumping TX_MEM_RD_FREQ\n");
    system("srpRead 0x0670d018 1");
	printf("dumping TX_DATAPATH_GATE_SEL\n");
    system("srpRead 0x0670d01c 1");
	printf("dumping TX_SYNC_POINT_CTRL\n");
    system("srpRead 0x06707028 1");
	printf("dumping VEX0 Counter\n");
    system("srpRead 0x02801024  1");
	printf("dumping VEX1 Counter\n");
    system("srpRead 0x02841024  1");
	printf("dumping Map Drop\n");
    system("srpRead 0x06705080  1");	 

}
/**
 * @brief           Function to dump jesd registers EOT
 * @param [in]      
 * @return          status
 */
int jesd_eot_reg_dump()
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
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};

    srp_dev_open(dev_id, dev_flags, &srp);

    delay(2000);
    while(count < 1)
    //while(1)
    {
        for(i=0; i<1; i++)
        {
            tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
            tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
        }
        for(j=0; j<1; j++)
        {
            rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
            rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
        }

        sh_lock_status_reg  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
        emb_lock_status_reg  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
        sh_lock_loss_status_reg  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
        emb_lock_loss_status_reg  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
        rx_err_report_lane_reg0  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG0_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG0");
        rx_err_report_lane_reg1  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG1_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG1");
        rx_err_report_lane_reg2  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG2_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG2");
        rx_err_report_lane_reg3  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG3_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG3");
        rx_fec  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET, "JESD_XIP_204C_RX_MEM_RX_FEC");
        rx_crc3_en  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CRC3_EN");
        rx_crc12_en  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CRC12_EN");
        //INT STATUS -if jesd 204c and rx cfg en  
        rx_core_interrupt_mask  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_MASK_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_MASK");
        rx_core_interrupt_status  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_STATUS_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_STATUS");
        //lemc boundary phase TODO: can these be predicted?-if jesd 204c and rx cfg en 
        rx_lemc_boundary_phase  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_LEMC_BOUNDARY_PHASE_OFFSET, "JESD_XIP_204C_RX_MEM_RX_LEMC_BOUNDARY_PHASE");
        //Sysref-  One shot sysref / periodic sysre -if jesd 204c and rx cfg en 
        rx_sysref_cntr_status  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SYSREF_COUNTER_STATUS_OFFSET, "JESD_XIP_204C_RX_MEM_RX_SYSREF_COUNTER_STATUS");
        nsip_hbi_intr_int_status  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_STATUS_OFFSET, "NSIP_HBI_INTR_INT_STATUS");
        nsip_hbi_h2b_flit_cnt  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "NSIP_HBI_H2B_FLIT_COUNT");

        printf("\n\n");
        printf("//############################################################\n");
        printf("Present value of JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
        printf("Present value of JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
        printf("Present value of JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
        printf("Present value of for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
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

        i=0;
        j=0;
        for(i=0; i<1; i++)
        {
            rx_icounter_report_lane0  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE0_OFFSET, "ICOUNTER_REPORT_LANE0");
            rx_icounter_report_lane1  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE1_OFFSET, "ICOUNTER_REPORT_LANE1");
            rx_icounter_report_lane2  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE2_OFFSET, "ICOUNTER_REPORT_LANE2");
            rx_icounter_report_lane3  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE3_OFFSET, "ICOUNTER_REPORT_LANE3");
            rx_icounter_report_lane4  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE4_OFFSET, "ICOUNTER_REPORT_LANE4");
            rx_icounter_report_lane5  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE5_OFFSET, "ICOUNTER_REPORT_LANE5");
            rx_icounter_report_lane6  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE6_OFFSET, "ICOUNTER_REPORT_LANE6");
            rx_icounter_report_lane7  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE7_OFFSET, "ICOUNTER_REPORT_LANE7");
            rx_icounter_report_lane8  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE8_OFFSET, "ICOUNTER_REPORT_LANE8");
            rx_icounter_report_lane9  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE9_OFFSET, "ICOUNTER_REPORT_LANE9");
            rx_icounter_report_lane10 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE10_OFFSET, "ICOUNTER_REPORT_LANE10");
            rx_icounter_report_lane11 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE11_OFFSET, "ICOUNTER_REPORT_LANE11");
            rx_icounter_report_lane12 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE12_OFFSET, "ICOUNTER_REPORT_LANE12");
            rx_icounter_report_lane13 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE13_OFFSET, "ICOUNTER_REPORT_LANE13");
            rx_icounter_report_lane14 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE14_OFFSET, "ICOUNTER_REPORT_LANE14");
            rx_icounter_report_lane15 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE15_OFFSET, "ICOUNTER_REPORT_LANE15");
            rx_icounter_report_lane16 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE16_OFFSET, "ICOUNTER_REPORT_LANE16");
            rx_icounter_report_lane17 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE17_OFFSET, "ICOUNTER_REPORT_LANE17");
            rx_icounter_report_lane18 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE18_OFFSET, "ICOUNTER_REPORT_LANE18");
            rx_icounter_report_lane19 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE19_OFFSET, "ICOUNTER_REPORT_LANE19");
            rx_icounter_report_lane20 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE20_OFFSET, "ICOUNTER_REPORT_LANE20");
            rx_icounter_report_lane21 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE21_OFFSET, "ICOUNTER_REPORT_LANE21");
            rx_icounter_report_lane22 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE22_OFFSET, "ICOUNTER_REPORT_LANE22");
            rx_icounter_report_lane23 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE23_OFFSET, "ICOUNTER_REPORT_LANE23");
            rx_gb_empty_reg = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
            rx_gb_full_reg = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
        }
        int j=0;
        for(j=0; j<1; j++)
        {
            tx_gb_empty_reg = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
            tx_gb_full_reg = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
        }
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
            printf(" Present value of JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
            printf(" Present value of JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
            printf(" Present value of JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
            printf(" Present value of JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
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
                printf(" \nprevious and current value for JL_N_TX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_tx_gb_empty_reg, curr_tx_gb_empty_reg);
                print24 = 1;
                prev_tx_gb_empty_reg = curr_tx_gb_empty_reg;
            }
        }

        if(tx_gb_full_reg)
        {
            curr_tx_gb_full_reg = tx_gb_full_reg;
            if(prev_tx_gb_full_reg != curr_tx_gb_full_reg)
            {
                printf(" \nprevious and current value for JL_N_TX_GB_FULL_REG are 0x%x, 0x%x\n", prev_tx_gb_full_reg, curr_tx_gb_full_reg);
                print25 = 1;
                prev_tx_gb_full_reg = curr_tx_gb_full_reg;
            }
        }

        if(rx_gb_empty_reg)
        {
            curr_rx_gb_empty_reg = rx_gb_empty_reg;
            if(prev_rx_gb_empty_reg != curr_rx_gb_empty_reg)
            {
                printf(" \nprevious and current value for JL_N_RX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_rx_gb_empty_reg, curr_rx_gb_empty_reg);
                print26 = 1;
                prev_rx_gb_empty_reg = curr_rx_gb_empty_reg;
            }
        }

        if(rx_gb_full_reg)
        {
            curr_rx_gb_full_reg = rx_gb_full_reg;
            if(prev_rx_gb_full_reg != curr_rx_gb_full_reg)
            {
                printf(" \nprevious and current value for JL_N_RX_GB_FULL_REG are 0x%x, 0x%x\n", prev_rx_gb_full_reg, curr_rx_gb_full_reg);
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
    nsip_hbi_h2b_flit_cnt  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "NSIP_HBI_H2B_FLIT_COUNT");
    printf("Present value of NSIP_HBI_H2B_FLIT_COUNT is 0x%x \n",nsip_hbi_h2b_flit_cnt);
    printf("\n");
    i=0;
    while(i < 5)
    {
        delay(1000);
        nsip_hbi_h2b_flit_cnt  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FLIT_COUNT_OFFSET, "NSIP_HBI_H2B_FLIT_COUNT");
        printf("Present value of NSIP_HBI_H2B_FLIT_COUNT is 0x%x \n",nsip_hbi_h2b_flit_cnt);
        delay(1000);
        i++;
    }
    
}
/**
 * @brief           Function to dump RX VEX mem to check captured data
 * @param [in]      
 * @return          status
 */
int rx_vex_mem_dump()
{
    int i = 0, rv;
    uint64_t num_of_streams         = jesd_config.jesd_link_config.converters / 2;
    
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

                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);

                    // Config JESD glue, comcores IP , DNRT - as per UC
                    configure_jesd_rx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_crux_clk_csr(jesd_tc_config.jesd_id);
                    configure_jesd_rx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);

                    //enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
					
                    //End of the test - reg dump 
                    jesd_eot_reg_dump();

                    //Dump the captured data at vex
                    rx_vex_mem_dump();
                    
					break;
        
        case flow_tx_vex_to_dnrt:
        
                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_cio2strm(jesd_tc_config.vex_id,jesd_tc_config.jesd_id);

                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_b2h(jesd_tc_config.jesd_id);

                    // Config JESD glue, comcores IP , DNRT - as per UC
                    configure_jesd_tx_cmn_csr(jesd_tc_config.jesd_id);
                    configure_jesd_tx_ip(jesd_tc_config.jesd_id);
                    configure_jesd_tx_glue(jesd_tc_config.jesd_id);
                    configure_jesd_tx_crux_clk_csr(jesd_tc_config.jesd_id);

                    //enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    
                     // Configure Vex Tx and start Vex
                    configure_vex_tx(jesd_tc_config.vex_id);

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
    memset(&jesd_config, 0, sizeof(jesd_config));
    //memset(&vex_strm2cio_config, 0, sizeof(vex_strm2cio_config));
    
    // Assign default values to JESD Testcase config and Jesd config structures 
    printf("INFO: Assign defaults to jesd_config struct\n");
    assign_defaults();
    
    // Parse from command line - JESD Testcase config -as per TC
    assign_tc_config(jesd_tc_config_arr,testcase);
    
    // Configure jesd config struct as per UC
    printf("INFO: update/fill/assign jesd config struct as per UC\n");
	assign_jesd_config(jesd_config_arr,jesd_tc_config.usecase_id);
	
	//jesd_config = jesd_config_arr[jesd_tc_config.usecase_id];
    
    //Initialize Test - fpga clk, fpga provided sysref for jesd, reset cycle for jesd,vex,other SS, clearing vex/jesd mem
    printf("INFO: Initialize Jesd%d\n",jesd_tc_config.jesd_id);
    init_jesd(jesd_tc_config.jesd_id,jesd_config.jesd_link_config.serdes_rate,jesd_config.jesd_link_config.smpl_char_clk_ratio);
    
    printf("INFO: Initialize Vex%d\n",jesd_tc_config.vex_id);
    init_vex(jesd_tc_config.vex_id);
    
    //Configure jesd TC as per flow selected
    configure_jesd_flow (jesd_tc_config.flow_id);
}   
/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */

int main(
    int argc,
    const char *argv[])
{
    int rv = 0, val = 0, dev_id = 0, flags = 0;
    uint64_t testcase;
    
    LOG_PRINT("INFO: Logger beginning\n");
    printf("Test: JESD Rx path \n");
    printf("INFO: argc : %d\n", argc);
    
    testcase        = atoi(argv[0]);
    
    printf("INFO: argv[0] : %d testcase_id     = %d\n",testcase, testcase);
  
    // Configure JESD test
    configure_jesd(testcase);
    
    // Test pass/fail criteria
    if(0 == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    } else
    {
        printf("Test Result:------ FAIL -----!\n\n");
    }

    printf("HOST: End of the Test execution....!\n");

    return rv;

}
