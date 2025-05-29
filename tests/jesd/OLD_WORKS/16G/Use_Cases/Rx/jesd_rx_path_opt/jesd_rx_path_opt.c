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

//#include "vex_producer.map.h"

/***********************************************

 * LOCAL/PRIVATE MACROS AND DEFINES            *
 
 ***********************************************/

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

/***********************************************

 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 
 ***********************************************/
// JESD_config Enums
typedef enum {TC_0 = 0,
              TC_1 = 1,
              TC_2 = 2,
              TC_3 = 3} testcase_id_t;                                  //JESD testcase selection
              
typedef enum {UC_5C = 0,
              UC_3A = 1,
              UC_1A = 2,
              UC_2A = 3,
              UC_3B = 4} usecase_id_t;                                  //Link config UC 
              
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

// VEX STRM2CIO config structs - CIO
typedef struct vex_strm2cio_config_t 
{
    int strm2cio_int_en;                                                //STRM2CIO Interrupt Enable 
    int strm2cio_fifo_sts_ctrl;                                         //Streaming FIFO Status Control
    int strm2cio_wrd_cnt_ctrl;                                          //FIFO Word Counter Control 
} vex_strm2cio_config_t;


// JESD_config structs - NSIP H2B
typedef struct jesd_h2b_config_t 
{
    int hbi_int_high_en;                                                //HBI High Priority Interrupt Enable 
    int hbi_int_low_en;                                                 //HBI Low Priority Interrupt Enable Register
    int h2b_fifo_ctrl;                                                  //H2B_FIFO_CONTROL
    int h2b_credit_ready;                                               //H2B Credit and Ready signal Control and Status 
    
} jesd_h2b_config_t;

// JESD_config structs - GLUE RX
typedef struct jesd_rx_glue_config_t 
{
    int rx_glue_soni;
    int rx_dp_gate_sel;
    int rx_dp_init_cyc_cnt;
} jesd_rx_glue_config_t;

// JESD _config structs - GLUE TX
typedef struct jesd_tx_glue_config_t 
{
    
} jesd_tx_glue_config_t;

// JESD_config structs - NSIP B2H
typedef struct jesd_b2h_config_t 
{
    
} jesd_b2h_config_t;

// JESD_config structs - CMN CSR
typedef struct jesd_cmn_csr_config_t
{
    int rx_ip_clk_ctrl;
    int rx_sysref_tsad;
    int rx_sync_point_ctrl;
    int rx_bfn_sysref_tsad;
    int rx_bfn_sync_point_ctrl;
    int rx_clk_gen_en;
    int rx_bfn_sync_point_cnt_en;
}jesd_cmn_csr_config_t;

// JESD_config structs - CRUX CLK CSR
typedef struct jesd_crux_clk_csr_config_t
{
    int rx_strm_cfg;
    int rx_mem_strm_cfg;
}jesd_crux_clk_csr_config_t;

// JESD Link Config enums                                                            //Refer JESD204C/D Link Configurations              
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
              
typedef enum {serdes_rate_8P11008   = 8,
              serdes_rate_16P22016  = 16,
              serdes_rate_24P33024  = 24,
              serdes_rate_32P44032  = 32,
              serdes_rate_50P13504  = 50,
              serdes_rate_66P84672  = 66,
              serdes_rate_83P5584   = 83,
              serdes_rate_100P27008 = 100} serdes_rate_t;               //Serdes Rate (Gbps)
              
typedef enum {e_1 = 1,
              e_3 = 3} min_e_t;                                         //Least #Blocks in EMB, LAC (Emin, Amin)
              
typedef enum {soni_1  = 0x100,
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

typedef enum {fec_dis  = 0x0,
              fec_en   = 0x1} fec_enable_t;                             //FEC_EN : Enable FEC per use case

typedef enum {fec_no_bypass = 0,
              fec_bypass = 1} fec_bypass_sel_t;                         //FEC_BYPASS : Set to ‘1’ to bypass FEC

typedef struct fec_t                                                    
{
    fec_enable_t fec_enable;
    fec_mode_t fec_mode;
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

typedef enum {scr_dis = 0x0,
              scr_en  = 0x1} scr_t;                                     //Scrambling

typedef enum {tl_testmode_dis = 0x0,
              tl_testmode_en  = 0x1} tl_testmode_t;                     //Transport Layer test mode

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
    scr_t                   scr;                                        //SCR
    fec_t                   fec;                                        //FEC
    bit_order_t             bit_order;                                  //Bitorder
    tl_testmode_t           tl_testmode;                                //TL_testmode
} jesd_link_config_t;

// JESD 204C-Only Registers - RX enums
typedef enum {crc3_dis  = 0x0,
              crc3_en   = 0x1} crc3_enable_t;                           //CRC3_EN

typedef enum {crc12_dis  = 0x0,
              crc12_en   = 0x1} crc12_enable_t;                         //CRC12_EN

typedef enum {rx_emb_err_thresh_3  = 0x3,
              rx_emb_err_thresh_8  = 0x8,
              rx_emb_err_thresh_9  = 0x9,
              rx_emb_err_thresh_16 = 0x10} rx_emb_err_thresh_t;         //Rx_Emb_err_threshold

typedef enum {rx_sh_err_thresh_3  = 0x3,
              rx_sh_err_thresh_8  = 0x8,
              rx_sh_err_thresh_9  = 0x9,
              rx_sh_err_thresh_16 = 0x10} rx_sh_err_thresh_t;           //Rx_Sh_err_threshold

typedef enum {cmd_dis  = 0x0,
              cmd_en   = 0x1} cmd_enable_t;                             //CMD_EN
              
typedef enum {jesd_ip_dis = 0x0,
              jesd_ip_en  = 0x1} jesd_ip_enable_t;                      //COMCORES_IP_EN

typedef enum {jesd_rx_ip_sysref_dis = 0x0,
              jesd_rx_ip_sysref_en  = 0x1} jesd_rx_ip_sysref_enable_t;  //Rx_ip_sysref_en

// JESD 204C-Only Registers - RX Struct 
typedef struct jesd_204c_rx_config_t 
{
    crc3_enable_t           crc3_enable;                                //CRC3_EN
    crc12_enable_t          crc12_enable;                               //CRC12_EN
    rx_emb_err_thresh_t     rx_emb_err_thresh;                          //Rx_Emb_err_threshold
    rx_sh_err_thresh_t      rx_sh_err_thresh;                           //Rx_Sh_err_threshold
    cmd_enable_t            cmd_enable;                                 //CMD_EN
} jesd_204c_rx_config_t;


// JESD RX IP CONFIG - Struct
typedef struct jesd_rx_ip_config_t 
{
    jesd_204c_rx_config_t       jesd_204c_rx_config;                    //CRC,ERR_THRESH,E,CMD
    jesd_ip_enable_t            jesd_ip_enable;                         //COMCORES_IP_EN    
    jesd_rx_ip_sysref_enable_t  jesd_rx_ip_sysref_enable;               //Rx_ip_sysref_en
} jesd_rx_ip_config_t;

// JESD_config structs - TX IP
typedef struct jesd_tx_ip_config_t
{
    jesd_ip_enable_t        jesd_ip_enable;                             //COMCORES_IP_EN    
} jesd_tx_ip_config_t;

typedef struct jesd_config_t
{
    jesd_link_config_t              jesd_link_config;                           //LMFS and other link config
    
    jesd_tx_glue_config_t           jesd_tx_glue_config;
    jesd_tx_ip_config_t             jesd_tx_ip_config;
    
    jesd_rx_glue_config_t           jesd_rx_glue_config;
    jesd_rx_ip_config_t             jesd_rx_ip_config;
    
    jesd_cmn_csr_config_t           jesd_cmn_csr_config;
    jesd_crux_clk_csr_config_t      jesd_crux_clk_csr_config;
    
    jesd_h2b_config_t               jesd_h2b_config;
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
struct jesd_tc_config_t jesd_tc_config_arr[2] = 
{
    // testcase_id, usecase_id, flow_id, vex_id, jesd_id
    
    //TC_0 -> arr[0]
	{TC_0, UC_5C, flow_rx_dnrt_to_vex, vex_0, jesd_0},
    //TC_1 -> arr[1]
    {TC_1, UC_3A, flow_rx_dnrt_to_vex, vex_0, jesd_0}
};

// Array of Struct to hold link config  : Refer UC config
struct jesd_link_config_t jesd_link_config_arr[2] = 
{
    // usecase_id, Sample rate, L, M, F, S, N', JESD04C/D, Serdes rate, E, Soni, clk ratio, smpl_pos/neg
    
    //UC_5C -> arr[0]
    {UC_5C, sample_rate_245P76, l_4, m_16, f_8, s_1, n_tot_16, jesd_204c, serdes_rate_32P44032, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_0},
    
    //UC_3A -> arr[1]
 	{UC_3A, sample_rate_122P88, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1}
  
};

/***********************************************

 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 
 ***********************************************/
void *g_vex_hdl;
srp_vex_config_t g_vex_params;
srp_vex_t g_srp_vex_hdl;

// JESD_Base Addresses for reg config 
static int g_jesd_nsip_base_addr[4]         = {DLNK_JESDABC0_NSIP_HBI_CSR_BASE, DLNK_JESDABC1_NSIP_HBI_CSR_BASE, DLNK_JESDABC2_NSIP_HBI_CSR_BASE, DLNK_JESDABC3_NSIP_HBI_CSR_BASE};
static int g_jesd_rx_ip_base_addr[4]        = {DLNK_JESDABC0_XIP_204C_RX_BASE, DLNK_JESDABC1_XIP_204C_RX_BASE, DLNK_JESDABC2_XIP_204C_RX_BASE, DLNK_JESDABC3_XIP_204C_RX_BASE};
static int g_jesd_cmn_csr_base_addr[4]      = {DLNK_JESDABC0_CMN_CSR_BASE, DLNK_JESDABC1_CMN_CSR_BASE, DLNK_JESDABC2_CMN_CSR_BASE, DLNK_JESDABC3_CMN_CSR_BASE};
static int g_jesd_crux_clk_csr_base_addr[4] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE, DLNK_JESDABC1_CRUX_CLK_CSR_BASE, DLNK_JESDABC2_CRUX_CLK_CSR_BASE, DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
static int g_jesd_rx_glue_base_addr[4]      = {DLNK_JESDABC0_RX_GLUE_BASE, DLNK_JESDABC1_RX_GLUE_BASE, DLNK_JESDABC2_RX_GLUE_BASE, DLNK_JESDABC3_RX_GLUE_BASE};
static int g_jesd_tx_ip_base_addr[4]        = {DLNK_JESDABC0_XIP_204C_TX_BASE, DLNK_JESDABC1_XIP_204C_TX_BASE, DLNK_JESDABC2_XIP_204C_TX_BASE, DLNK_JESDABC3_XIP_204C_TX_BASE};

vex_strm2cio_config_t vex_strm2cio_config;
jesd_config_t jesd_config;
jesd_tc_config_t jesd_tc_config;
/*********************************************** 

 * STATIC FUNCTION PROTOTYPES                  * 

 ***********************************************/ 
void fpga_clk_and_sysref_period();
void fpga_provided_sysref();
void delay(unsigned int milliseconds );

int init_jesd(uint32_t jesd_id);
int init_vex(uint32_t vex_id);

int configure_vex_strm2cio(uint32_t rx_vex_id);

int configure_jesd_nsip_common(uint32_t jesd_id);

int configure_jesd_h2b(uint32_t rx_jesd_id, uint32_t rx_vex_id);
int configure_jesd_cmn_csr_rx(uint32_t rx_jesd_id);
int configure_jesd_crux_clk_csr_(uint32_t rx_jesd_id);
int configure_jesd_glue_rx(uint32_t rx_jesd_id);
int configure_jesd_rx_ip(uint32_t rx_jesd_id);

int configure_jesd_ip_enable(uint32_t jesd_id);
void assign_defaults();
//void assign_link_config(struct jesd_tc_config_t jesd_tc_config_arr[2], uint64_t testcase); 
//void assign_tc_config(struct jesd_link_config_t jesd_link_config_arr[2], uint64_t usecase);
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
 * @param [in]      jesd_link_config_arr[],usecase_id
 * @return          
 */
void assign_link_config(struct jesd_link_config_t jesd_link_config_arr[2], uint64_t usecase)
{
    // Select usecase from tbl 
    printf("Assigning link config \n");
    // JESD link config - RX 
    jesd_config.jesd_link_config.usecase_id                                     = jesd_link_config_arr[usecase].usecase_id;
    jesd_config.jesd_link_config.sample_rate                                    = jesd_link_config_arr[usecase].sample_rate;
    jesd_config.jesd_link_config.lanes                                          = jesd_link_config_arr[usecase].lanes;
    jesd_config.jesd_link_config.converters                                     = jesd_link_config_arr[usecase].converters;
    jesd_config.jesd_link_config.frames                                         = jesd_link_config_arr[usecase].frames;
    jesd_config.jesd_link_config.smpl_per_frame                                 = jesd_link_config_arr[usecase].smpl_per_frame;
    jesd_config.jesd_link_config.smpl_total_bits                                = jesd_link_config_arr[usecase].smpl_total_bits;
    jesd_config.jesd_link_config.serdes_rate                                    = jesd_link_config_arr[usecase].serdes_rate;
    jesd_config.jesd_link_config.min_e                                          = jesd_link_config_arr[usecase].min_e;
    jesd_config.jesd_link_config.sonif                                          = jesd_link_config_arr[usecase].sonif;
    jesd_config.jesd_link_config.smpl_char_clk_ratio                            = jesd_link_config_arr[usecase].smpl_char_clk_ratio;
    jesd_config.jesd_link_config.smpl_trans_pos_neg                             = jesd_link_config_arr[usecase].smpl_trans_pos_neg;
}

/**
 * @brief           Function for assigning default values to jesd_config struct
 * @param [in]      jesd_link_config_arr[],use_case_id
 * @return          
 */
void assign_defaults()
{
    printf("Assigning default values \n");
    
    // JESD IP CONFIG - RX
    jesd_config.jesd_link_config.subclass                                       = subclass_1;
    jesd_config.jesd_link_config.ctrl_frames_cf                                 = cf_0;
    jesd_config.jesd_link_config.ctrl_bits_cs                                   = cs_0;
    jesd_config.jesd_link_config.smpl_res                                       = n_16;
    jesd_config.jesd_link_config.high_density                                   = hd_1;
    jesd_config.jesd_link_config.scr                                            = scr_en;
    jesd_config.jesd_link_config.fec.fec_enable                                 = fec_dis;
    jesd_config.jesd_link_config.bit_order.bitorder                             = bitorder_3;
    jesd_config.jesd_link_config.tl_testmode                                    = tl_testmode_dis;
    
    // JESD 204C ONLY REG - RX 
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc3_enable               = crc3_dis;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.crc12_enable              = crc12_dis;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_emb_err_thresh         = rx_emb_err_thresh_3;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.rx_sh_err_thresh          = rx_sh_err_thresh_3;
    jesd_config.jesd_rx_ip_config.jesd_204c_rx_config.cmd_enable                = cmd_dis;
    
    // JESD H2B - RX
    jesd_config.jesd_h2b_config.hbi_int_high_en                                 = 0xFFFFF;
    jesd_config.jesd_h2b_config.hbi_int_low_en                                  = 0xFFFFF;
    jesd_config.jesd_h2b_config.h2b_fifo_ctrl                                   = 0x00000184;
    jesd_config.jesd_h2b_config.h2b_credit_ready                                = 0x3;
    
    // VEX - STRM2CIO
    vex_strm2cio_config.strm2cio_int_en                                         = 0xF;              
    vex_strm2cio_config.strm2cio_fifo_sts_ctrl                                  = 0x00000001;                   
    vex_strm2cio_config.strm2cio_wrd_cnt_ctrl                                   = 0x00000001;                     
    
    // JESD IP EN AND SYSREF EN
    jesd_config.jesd_rx_ip_config.jesd_ip_enable                                = jesd_ip_en;
    jesd_config.jesd_tx_ip_config.jesd_ip_enable                                = jesd_ip_en;
    jesd_config.jesd_rx_ip_config.jesd_rx_ip_sysref_enable                      = jesd_rx_ip_sysref_en;
    
    // JESD CMN CSR - RX
    jesd_config.jesd_cmn_csr_config.rx_ip_clk_ctrl                              = 0x00000018;
    jesd_config.jesd_cmn_csr_config.rx_sysref_tsad                              = 0x0000000f;
    jesd_config.jesd_cmn_csr_config.rx_sync_point_ctrl                          = 0x000b001b;
    jesd_config.jesd_cmn_csr_config.rx_bfn_sysref_tsad                          = 0x0000000f;
    jesd_config.jesd_cmn_csr_config.rx_bfn_sync_point_ctrl                      = 0x000b001b;
    jesd_config.jesd_cmn_csr_config.rx_clk_gen_en                               = 0x00000001;
    jesd_config.jesd_cmn_csr_config.rx_bfn_sync_point_cnt_en                    = 0x00000018;
    
    // JESD GLUE - RX 
    jesd_config.jesd_rx_glue_config.rx_glue_soni                                = 0x00000001;
    jesd_config.jesd_rx_glue_config.rx_dp_gate_sel                              = 0x00000001;
    jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt                          = 0x00000100;
   
}
/**
 * @brief           Function for configuring fpga clk and sysref period
 * @param [in]      use_case_id
 * @return          
 */
void fpga_clk_and_sysref_period()
{ 

        system("frioPciWrite -F s5a1 -P 0x20000 0x10");
        system("frioPciWrite -F s5b1 -P 0x20000 0x10");
        system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
        system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
    

        //enable jesd_ip path or serial or parallel lpbk
        system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
        //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
        //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
    
}

/**
 * @brief           Function for enabling sysref
 * @param [in]      
 * @return          
 */
void fpga_provided_sysref()
{
       //enable sysref
        system("frioPciWrite -F s5a1 -P 0x20000 0x90");
        system("frioPciWrite -F s5b1 -P 0x20000 0x90");
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
 * @param [in]      rx_jesd_id
 * @return          status
 */      
int init_jesd(uint32_t rx_jesd_id)
{
	int rv = 0;

    fpga_clk_and_sysref_period();
    delay(100);
    
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
    delay(100);
    
	init(); // Initialize the srp
	delay(1000);
    
    jesd_reset(1 << rx_jesd_id,0);
    delay(1000);
    
	fpga_provided_sysref();
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
 * @brief           Function configuring VEX CIO: strm2cio for receiving vex
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
 * @brief           Function configuring JESD NSIP HBI Commmon: Interrupt en
 * @param [in]      tx_jesd_id, rx_jesd_id
 * @return          status
 */
int configure_jesd_nsip_common(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_nsip_h2b_base = g_jesd_nsip_base_addr[rx_jesd_id];
    
    register_config_tbl_t jesd_port_nsip_hbi_cmn_config_tbl[] = 
    {
        // NSIP_HBI interrupt en - Rx path
        {NSIP_HBI_INTR_INT_HIGH_EN_ADR(jesd_nsip_h2b_base), jesd_config.jesd_h2b_config.hbi_int_high_en, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_INTR_INT_HIGH_EN"},
        {NSIP_HBI_INTR_INT_LOW_EN_ADR(jesd_nsip_h2b_base), jesd_config.jesd_h2b_config.hbi_int_low_en, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_INTR_INT_LOW_EN"},
        
        // H2B Registers
        // Set high and low watermarks and soft resets for the 16-entry clock crossing FIFO.
        {NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_ADR(jesd_nsip_h2b_base), jesd_config.jesd_h2b_config.h2b_fifo_ctrl, NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL"},
        
        // H2B Credit and Ready signal Control and Status
        {NSIP_HBI_H2B_CREDIT_READY_CS_ADR(jesd_nsip_h2b_base), jesd_config.jesd_h2b_config.h2b_credit_ready, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, "NSIP_HBI_H2B_CREDIT_READY_CS"}
   };
    
    for(i = 0; i < ARRAY_SIZE(jesd_port_nsip_hbi_cmn_config_tbl); i++)
    {
        if(rv = write_reg_18a(jesd_port_nsip_hbi_cmn_config_tbl[i].addr,
                              jesd_port_nsip_hbi_cmn_config_tbl[i].value,
                              jesd_port_nsip_hbi_cmn_config_tbl[i].mask,
                              jesd_port_nsip_hbi_cmn_config_tbl[i].name))
            return rv;
    }

    print("INFO: NSIP HBI Commmon configuration completed for JESD%d in Rx path \n", rx_jesd_id);
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
    int jesd_nsip_h2b_base = g_jesd_nsip_base_addr[rx_jesd_id];
    
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
        default:
                h2b_addr_lkup_tbl_offset       = 0x800;
                h2b_tk_addr_lkup_tbl_offset    = 0x4;
            break;
    }
    
    for (str_id = 0x0 ; str_id < num_of_streams ; str_id++)
    {
        register_config_tbl_t jesd_port_nsip_hbi_h2b_config_tbl[] = 
        {
            // H2B Stream Config - Vector/Sample Data Buffer Size LUT
            {(NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)), 
                h2b_buf_sz_hw_tbl_value, 
                NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, 
                "H2B_BUF_SZ_HW_TBL"},

            // Vector/Sample Data Routing LUT.
            {(NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)),
                h2b_route_tbl_value,
                NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_ROUTE_LKUP_TBL"},
            
             // Token Address LUT. 
            {(NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)),
                (h2b_tk_addr_lkup_tbl_value + str_id * h2b_tk_addr_lkup_tbl_offset),
                NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK,
                "H2B_TK_ADDR_LKUP_TBL"},
            
            // Token Routing LUT.
            {(NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)),
                h2b_tk_route_tbl_value,
                NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_TK_ROUTE_LKUP_TBL"},
                
            // Metadata Base Address LUT
            /*{(NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)), 
                    0x10000,
                    NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK,
                    "H2B_MD_ADDR_LKUP_TBL"}, */
            
            // Metadata Routing LUT
            {(NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)),
                h2b_md_route_tbl_value,
                NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK,
                "H2B_MD_ROUTE_LKUP_TBL"},
                
            // Metadata Control tbl
            {(NSIP_HBI_H2B_MD_CONTROL_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * str_reg_addr_offset)),
                h2b_md_ctrl_tbl_value,
                NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK,
                "H2B_MD_CONTROL_TBL"},
            
            // Valid Address and Routing Entry in Data/Token/Metadata Lookup Registers.Vector/Sample Base address
            // This register should be written LAST since it validates all of the other registers.
            {(NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(jesd_nsip_h2b_base) + (str_id * 0x4)),
                (h2b_addr_lkup_tbl_value + str_id * h2b_addr_lkup_tbl_offset ),
                NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK,
                "H2B_ADDR_LKUP_TBL"}
          
        };
        
        for(i = 0; i < ARRAY_SIZE(jesd_port_nsip_hbi_h2b_config_tbl); i++)
        {
            if(rv = write_reg_18a(jesd_port_nsip_hbi_h2b_config_tbl[i].addr,
                                  jesd_port_nsip_hbi_h2b_config_tbl[i].value,
                                  jesd_port_nsip_hbi_h2b_config_tbl[i].mask,
                                  jesd_port_nsip_hbi_h2b_config_tbl[i].name))
                return rv;
        }
    }
    
    print("INFO: NSIP H2B configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CMN CSR: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_cmn_csr_rx(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_cmn_csr_base = g_jesd_cmn_csr_base_addr[rx_jesd_id];

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, 
                            jesd_config.jesd_cmn_csr_config.rx_ip_clk_ctrl, 
                            JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL"))
        return rv;               
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_bfn_sysref_tsad,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD"))
        return rv;  
        
    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_bfn_sync_point_ctrl,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_clk_gen_en,
                            JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE"))
        return rv;  

    if(rv = write_reg_18a(jesd_cmn_csr_base + JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET,
                            jesd_config.jesd_cmn_csr_config.rx_bfn_sync_point_cnt_en,
                            JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK,
                            "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE"))
        return rv;
    
    print("INFO: JESD CMN CSR configuration completed for JESD%d in Rx path\n", rx_jesd_id);
    return rv;
}

/**
 * @brief           Function configuring CRUX CLK CSR: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_crux_clk_csr_(uint32_t rx_jesd_id)
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
 * @brief           Function configuring GLUE: JESD in Rx path
 * @param [in]      rx_jesd_id
 * @return          status
 */
int configure_jesd_glue_rx(uint32_t rx_jesd_id)
{
    int i = 0, rv;
    int jesd_rx_glue_base = g_jesd_rx_glue_base_addr[rx_jesd_id];
    
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_glue_soni,
                            JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK,
                            "RX_GLUE_MEM_RX_GLUE_SONI"))
        return rv;
    
    // dp_gate_sel, as per simval log
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_gate_sel,
                            JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK,
                            "RX_DATAPATH_GATE_SEL"))
        return rv;
    // dp_init_cyc_cntenable, as per simval log   
    if(rv = write_reg_18a(jesd_rx_glue_base + JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET,
                            jesd_config.jesd_rx_glue_config.rx_dp_init_cyc_cnt,
                            JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK,
                            "RX_DATAPATH_INIT_CYC_CNT"))
        return rv;                    

    print("INFO: JESD GLUE configuration completed for JESD%d in Rx path\n", rx_jesd_id);
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
                            jesd_config.jesd_link_config.sonif,
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
    
    print("INFO: JESD RX IP configuration completed for JESD%d in Rx path\n", rx_jesd_id);
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
        
    print("INFO: JESD RX and TX IP en configuration completed for JESD%d in Rx path\n", jesd_id);
    return rv;
}

/**
 * @brief           Function configuring JESD: As per testflow selected
 * @param [in]      flow_id
 * @return          status
 */
int configure_jesd_flow (uint32_t flow_id)
{
    //Select Test flow
    switch (flow_id)
    {
        case flow_rx_dnrt_to_vex:
                    
                    // Configure jesd config struct as per UC
                    printf("INFO: Configure jesd config struct as per UC\n");
                    assign_link_config(jesd_link_config_arr,jesd_tc_config.usecase_id);
                
                    // Config JESD NSIP - as per UC
                    configure_jesd_nsip_common(jesd_tc_config.jesd_id);
                    configure_jesd_h2b(jesd_tc_config.jesd_id,jesd_tc_config.vex_id);

                    // Configure STRM2CIO registers of rx_vex
                    configure_vex_strm2cio(jesd_tc_config.vex_id);

                    // Config JESD glue, comcores IP , DNRT - as per UC
                    configure_jesd_cmn_csr_rx(jesd_tc_config.jesd_id);
                    configure_jesd_crux_clk_csr_(jesd_tc_config.jesd_id);
                    configure_jesd_glue_rx(jesd_tc_config.jesd_id);
                    configure_jesd_rx_ip(jesd_tc_config.jesd_id);

                    //enable jesd
                    configure_jesd_ip_enable(jesd_tc_config.jesd_id);
                    break;
    }
}

int configure_jesd ( uint32_t testcase)
{
    
     memset(&jesd_config, 0, sizeof(jesd_config));
    //memset(&vex_strm2cio_config, 0, sizeof(vex_strm2cio_config));
    
    // Assign default values to JESD Testcase config and Jesd config structures 
    printf("INFO: Assign defaults to jesd_config struct\n");
    assign_defaults();
    
    // Parse from command line - JESD Testcase config -as per TC
    assign_tc_config(jesd_tc_config_arr,testcase);
    
    //Initialize Test - fpga clk, fpga provided sysref for jesd, reset cycle for jesd,vex,other SS, clearing vex/jesd mem
    printf("INFO: Initialize Jesd%d\n",jesd_tc_config.jesd_id);
    init_jesd(jesd_tc_config.jesd_id);
    
    printf("INFO: Initialize Vex%d\n",jesd_tc_config.vex_id);
    init_vex(jesd_tc_config.vex_id);
    
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
    printf("INFO: Initialize srp\n");
    init();                                                // Initialize the srp
    LOG_PRINT("INFO: Logger beginning\n");
    printf("Test: JESD Rx path 16G\n");
    printf("INFO: argc : %d\n", argc);
    
    testcase        = atoi(argv[0]);
    
    printf("INFO: argv[0] : %d testcase_id     = %d\n",testcase, testcase);
  
    // Configure JESD test
    configure_jesd (testcase);
    
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
