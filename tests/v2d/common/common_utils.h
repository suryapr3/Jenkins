#ifndef V2D_UTIL_H
#define V2D_UTIL_H

#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"
#include "common_functions.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "host_utils.h"
#include "srp_rcs.h"
#include "noc.h"
#include "all_comps.h"

/***********************************************
 * GLOBAL DEFINES            *
 ***********************************************/


#if LIVEIQ_SAMPLES
#define LIVE_IQ_NTESTPTS  12288
#define VMEM_SIZE_SAMPLES 16384
/*
int term_types[48];
int q_delay[48];
int m_delay[48];
int passthru_dly = LIVE_IQ_PASSTHRU_DELAY;
int lut_c_i[48];
int lut_c_q[48];
int lut_s[48];
int data_in_i[LIVE_IQ_NTESTPTS];
int data_in_q[LIVE_IQ_NTESTPTS];
int y_out_i[LIVE_IQ_NTESTPTS];
int y_out_q[LIVE_IQ_NTESTPTS];
*/
typedef struct v2d_live_IQ_param_s
{
    int passthru_dly;
    int passthru_coeft_i;
    int passthru_coeft_q;
    int term_types[48];
    int q_delay[48];
    int m_delay[48];
    int lut_c_i[48][65];
    int lut_c_q[48][65];
    int lut_s[48];
    int data_in_i[VMEM_SIZE_SAMPLES];
    int data_in_q[VMEM_SIZE_SAMPLES];
    int y_out_i[VMEM_SIZE_SAMPLES];
    int y_out_q[VMEM_SIZE_SAMPLES];
    int num_gmp_terms;
    int num_ddr_terms;

} v2d_liveIQ_param_t;

/* The global variable which will get populated with MATLABTVs and params */
v2d_liveIQ_param_t  v2d_liveIQ_param;

#define LIVEIQ_PASSTHRU_TEST 0 // for testing the passthru alone config
#endif //LIVEIQ_SAMPLES

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define printf LOG_PRINT

#ifndef E2E_FLOW_EN
#define NUMBER_OF_VECTORS_INPUT 192 // Corresponds to 1 block of data for 12GSPS
#define NUMBER_OF_VECTORS_OUTPUT 192 // Corresponds to 1 block of data for 12GSPS
#define VEX_MAX_BUF_SIZE 256    // in vectors and it should be power of 2
#endif // !E2E_FLOW_EN

#define VEX_VMEM_IN_VEC (512)   // VEX VMEM size in vectors
#define SPLIT_METHOD_EQUAL  0
#define SPLIT_METHOD_UNEQUAL    1
#define SAMPLES_PER_VEC 32
#define FALSE   (0)
#define TRUE    (1)

#define APB_OFFSET_GEN(apb_num) (apb_num * (V2D0_AV2D_APB_1_CSR_BASE - V2D0_AV2D_APB_0_CSR_BASE))
#define CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE)
#define STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE)
#define V2D_NSIP_HBI_0_OFFSET (V2D0_AV2D_APB_0_NSIP_HBI_0_BASE - V2D0_PDPD_0_BASE)
#define V2D_NSIP_HBI_1_OFFSET (V2D0_AV2D_APB_0_NSIP_HBI_1_BASE - V2D0_PDPD_0_BASE)
#define V2D_CSR_OFFSET (V2D0_AV2D_APB_0_CSR_BASE - V2D0_PDPD_0_BASE)
#define V2D_BFN_OFFSET (V2D0_BFN_CSR_BASE - V2D0_PDPD_0_BASE)
#define PDPD_BASE_ADDR(v2d_num, apb_num) ((V2D0_PDPD_0_BASE + ((v2d_num) * (V2D1_PDPD_0_BASE - V2D0_PDPD_0_BASE))) + APB_OFFSET_GEN(apb_num))
#define TRX_SYS_CSR_BASE(trx_num)   (TRX_SYS0_CSR_BASE + ((trx_num) * (TRX_SYS1_CSR_BASE - TRX_SYS0_CSR_BASE)))
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VEX_DMEM(vex_num) (VEXABC0_DMEM_VE32_BP_CFG_BASE + ((vex_num) * (VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE)))
#define VEX_VMEM(vex_num) (VEXABC0_VMEM_VE32_SIMD0_BASE + (vex_num * (VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE)))

#define CIO2STRM_INT_EN_VALUE 0x3F
#define CIO2STRM_FIFO_STATUS_CTL_VALUE 0x00000001
#define CIO2STRM_WORD_CNT_CTL_VALUE 0x00000001
#define STRM2CIO_INT_ENABLE_VALUE 0xF
#define STRM2CIO_FIFO_STATUS_CTL_VALUE 0x00000001
#define STRM2CIO_WORD_CNT_CTL_VALUE 0x00000001
#define NSIP_HBI_INT_CSR_INT_VALUE 0xFFFFFFFF
#define FIFO_CONTROL_VALUE 0x00000184
#define B2H_CREDIT_CS_VALUE NSIP_HBI_B2H_CSR_CREDIT_CS_MAX_CREDITS_BF_DEF
#define H2B_CREDIT_READY_CS_VALUE NSIP_HBI_H2B_CREDIT_READY_CS_MAX_CREDITS_BF_DEF
#define CSR_INT_VALUE 0xFFFFFFFF
#define NUM_DATA_BLOCKS 2
#define DMEM_OFFSET (VEXABC0_DMEM_VE32_BP_CFG_BASE - VEXABC0_SC_VE32_CELL_BASE)

#define RX_PACKET_SZ_VALUE  2
#define RX_PACKET_SZ_VALUE_2STREAM  (RX_PACKET_SZ_VALUE << 2 | RX_PACKET_SZ_VALUE)
#define RX_PD_PACKET_SZ_VALUE   (2 << AV2D_CSR_RX_CSR_RX_PACKET_SZ_PD_PKT_SZ_STRM_0_BF_OFF)
#define RX_PD_PACKET_SZ_VALUE_2STREAM   ((RX_PD_PACKET_SZ_VALUE << 2) | RX_PD_PACKET_SZ_VALUE)
#define POST_PROCESSING_RX_PACKET_SZ_VALUE (RX_PACKET_SZ_VALUE | RX_PD_PACKET_SZ_VALUE)
#define POST_PROCESSING_2STREAM_RX_PACKET_SZ_VALUE  (RX_PACKET_SZ_VALUE_2STREAM | RX_PD_PACKET_SZ_VALUE)

#define POST_C_CENTER_VALUE_UNITY_GAIN 0x7FF
#define PASSTHRU_I_COEFF_UNITY_GAIN    (1 << 13)
#define PASSTHRU_Q_COEFF_UNITY_GAIN    0

#define V2D_PDPD_MAX_GMP_TERMS 32
#define V2D_PDPD_MAX_DDR_TERMS 16

#define V2D_PDPD_MAX_GMP_TERMS_4GSPS V2D_PDPD_MAX_GMP_TERMS>>1
#define V2D_PDPD_MAX_DDR_TERMS_4GSPS V2D_PDPD_MAX_DDR_TERMS>>1

#define V2D_PDPD_MAX_GMP_TERMS_8GSPS V2D_PDPD_MAX_GMP_TERMS>>2
#define V2D_PDPD_MAX_DDR_TERMS_8GSPS V2D_PDPD_MAX_DDR_TERMS>>2

#define V2D_PDPD_MAX_C_LUT_SEGMENTS 65
#define V2D_PDPD_MAX_POST_C_TERMS   8

#define V2D_PDPD_GMP_TERMS_4IQ  16
#define V2D_PDPD_DDR_TERMS_4IQ  8

#define V2D_PDPD_GMP_TERMS_8IQ  8
#define V2D_PDPD_DDR_TERMS_8IQ  4
#define PASSTHRU_DELAY  10

#define NL_C_VALUE  0

#define V2D_BUFFER0_OFFSET  0
#define V2D_BUFFER1_OFFSET  0x400

#define PATH_PREFIX "../test_vectors/"

//As per Hard coding in the memmap.xmm file in RCS, need to change it whenever memmap.xmm changes
#define RSM_MEM_OFFSET  0x230000

#define CYCLES_PER_BLOCK_1P5G          (768)
#define CYCLES_PER_BLOCK_983M          (512)
#define BYTES_PER_VEC                  (128)
#define VEC2FLIT(num_vec)              ((num_vec) * 2)
#define NUM_OF_ELEMENTS_PER_VEC        (32)

#define NUM_CONFIG_PDPD 17
#define MAX_NUM_STREAMS 4

#define VEX_STOP_TRANSMIT_INDICATION    3

/*G Buffer Related macros*/
#define G_BUF_SIZE_FLITS    241
#define G_BUF_LUT   48
#define NUM_WORDS_PER_LUT   80
#define NUM_TILES   8
#define GMP_LUT_TILE    4
#define DDR_LUT_TILE    2

#define V2D_PER_QUAD    2
#define VEX_PER_V2D     4
#define NUM_QUAD_ABC    4

/*This size should be in 512 bits, 0 = 1 512 bit entry*/
#define SAMPLES_TO_FB_MEM_SIZE(num_samples) (((num_samples) * 4) / 64)
#define CAPTURE_DELAY_DELTA_VALUE   0x9

#define MEM_FB_ACCESS_SIZE  (1024 * 4)  // in Bytes
#define MEM_FB_SIZE (256 * 1024 * 4)    // in Bytes
#define MEM_FB_INIT_VALUE    0xa5a5a5a5
#define FB_MEM_SECTOR_SIZE  512 // each sector is of 512 x 512 bits

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct v2d_flow_config_tbl_s
{
    uint32_t offset;
    unsigned int value;
    int mask;
    char *name;
} v2d_flow_tbl_t;

typedef struct v2d_shdw_live_reg_check_param_s
{
    int v2d_num;
    int apb_num;
    int test_config;
    int num_gmp_terms;
    int num_ddr_terms;
    int gmp_c_i_value;
    int gmp_c_q_value;
    int ddr_c_i_value;
    int ddr_c_q_value;
    int gmp_shift_value;
    int ddr_shift_value;
} v2d_shdw_live_reg_check_t;

#ifdef E2E_FLOW_EN
typedef enum {
    V2D_SYS_RATE_IQ_P25 = 0x0,
    V2D_SYS_RATE_IQ_P375 = 0x1,
    V2D_SYS_RATE_IQ_P5 = 0x2,
    V2D_SYS_RATE_IQ_P75 = 0x3,
    V2D_SYS_RATE_IQ_1 = 0x4,
    V2D_SYS_RATE_IQ_1P5 = 0x5,
    V2D_SYS_RATE_IQ_2 = 0x6,
    V2D_SYS_RATE_IQ_3 = 0x7,
    V2D_SYS_RATE_IQ_4 = 0x8,
    V2D_SYS_RATE_IQ_6 = 0x9,
    V2D_SYS_RATE_IQ_8 = 0xa,
    V2D_SYS_RATE_IQ_12 = 0xb,
    V2D_SYS_RATE_R_3 = 0x15,
    V2D_SYS_RATE_R_4 = 0x16,
    V2D_SYS_RATE_R_6 = 0x17,
    V2D_SYS_RATE_R_8 = 0x18,
    V2D_SYS_RATE_R_12 = 0x19,
    V2D_SYS_RATE_R_16 = 0x1a,
    V2D_SYS_RATE_R_18 = 0x1b,
    V2D_SYS_RATE_R24 = 0x1C,
    NUM_SYS_RATES
} v2d_sys_rate_t;
#else // !E2E_FLOW_EN
typedef enum {
    SYS_RATE_IQ_P25 = 0x0,
    SYS_RATE_IQ_P375 = 0x1,
    SYS_RATE_IQ_P5 = 0x2,
    SYS_RATE_IQ_P75 = 0x3,
    SYS_RATE_IQ_1 = 0x4,
    SYS_RATE_IQ_1P5 = 0x5,
    SYS_RATE_IQ_2 = 0x6,
    SYS_RATE_IQ_3 = 0x7,
    SYS_RATE_IQ_4 = 0x8,
    SYS_RATE_IQ_6 = 0x9,
    SYS_RATE_IQ_8 = 0xa,
    SYS_RATE_IQ_12 = 0xb,
    SYS_RATE_R_3 = 0x15,
    SYS_RATE_R_4 = 0x16,
    SYS_RATE_R_6 = 0x17,
    SYS_RATE_R_8 = 0x18,
    SYS_RATE_R_12 = 0x19,
    SYS_RATE_R_16 = 0x1a,
    SYS_RATE_R_18 = 0x1b,
    SYS_RATE_R24 = 0x1C,
    NUM_SYS_RATES
} sys_rate_t;
#endif // !E2E_FLOW_EN

// PDPD interface sample rate
typedef enum {
    PDPD_RATE_IQ_P5 = 0, //   1 "I+Q" every 2 clocks ( 0.5 samples per clock)
    PDPD_RATE_IQ_1  = 1, //   1 "I+Q" every 1 clocks ( 1 sample per clock)
    PDPD_RATE_IQ_2  = 2, //   2 "I+Q" every 1 clocks ( 2 samples per clock)
    PDPD_RATE_IQ_4  = 3, //   4 "I+Q" every 1 clocks ( 4 samples per clock)
    PDPD_RATE_IQ_8  = 4,  //   8 "I+Q" every 1 clock  ( 8 samples per clock)
    PDPD_NUM_SAMPLE_RATES = 5
} pdpd_rate_t;

typedef enum {
    PDPD_LUT_48 = 0, // 48 LUT's
    PDPD_LUT_24,     // 24 LUT's
    PDPD_LUT_12,      // 12 LUT's
    PDPD_NUM_LUTS
}lut_mode_t;

typedef enum {
    PASSTHRU_MODE = 0,
    FILTER_MODE
}post_filter_mode_t;

typedef enum {
    CLOCK_983M = 0,
    CLOCK_1P5G
}drf_clock_t;

typedef enum {
    PDPD_MAIN_INSTANCE = 0,
    PDPD_SECONDARY_INSTANCE,
    PDPD_MAX_INSTANCE
}pdpd_instance_t;

typedef enum {
    PDPD_AT_0 = 0, // this is as per HW design. not to be changed
    PDPD_AT_1,
    PDPD_AT_2,
    PDPD_AT_3,
    PDPD_AT_4,
    PDPD_AT_5,
    PDPD_AT_MAX
}pdpd_termTypes_t;

typedef struct quad_mem_compare_params
{
    int quad_instance;
    int additional_factor;
    int num_vectors_per_block;
    int capture_delay_value;
    int num_antenna;
    int delay_value_between_antenna;
    int samples_per_antenna;
    drf_clock_t drf_clk;
    int num_iter;
    int consecutive_capture_delay;
}quad_mem_compare_t;

typedef struct repeat_mem_compare_params
{
    int v2d_num;
    int additional_factor;
    int num_vectors_per_block;
    int capture_delay_value;
    drf_clock_t drf_clk;
    int num_repeat;
    int num_blocks; /*blocks per capture*/
    int skip_cycles; /*Cycles delay between consecutive captures*/
}repeat_mem_compare_t;

extern const int g_flow1_vectors_per_block[NUM_SYS_RATES];
extern const uint32_t g_flow1_tx_strm_cnt0_offset[NUM_SYS_RATES];
extern const uint32_t g_flow1_md_control_tbl[NUM_SYS_RATES];
extern const uint32_t g_v2d_host_id[8][2][2];
extern const int g_vectors_per_block[2][PDPD_NUM_SAMPLE_RATES];
extern const uint32_t g_tx_strm_cnt0_value[2][PDPD_NUM_SAMPLE_RATES];
extern const int g_md_control_tbl[2][PDPD_NUM_SAMPLE_RATES];
extern const int g_vectors_g_buf_lut_mode[PDPD_NUM_LUTS];
extern const int g_pdpd_rate_sys_rate_map[2][PDPD_NUM_SAMPLE_RATES];
extern const char *drf_clock_str[2];
extern v2d_flow_tbl_t g_cio2strm_config_tbl[8];
extern v2d_flow_tbl_t g_strm2cio_config_tbl[3];
extern const uint32_t g_test_config_tbl[17][5];
extern const char *pdpd_rate_str[PDPD_NUM_SAMPLE_RATES];
extern const char *sys_rate_str[NUM_SYS_RATES];
extern const char *split_method_str[2];
extern const char *post_filter_mode_str[2];
extern const int num_lut[PDPD_NUM_LUTS];
extern const int  g_v2d_instance_in_quad[NUM_QUAD_ABC][V2D_PER_QUAD];
extern const int g_vex_instance_in_v2d[NUM_QUAD_ABC][VEX_PER_V2D];
extern const int g_fb_mem_start_sector_per_v2d[4];
extern int g_abc_build_version;
extern v2d_flow_tbl_t g_v2d_pdpd_passthru_config_tbl[2];
extern v2d_flow_tbl_t g_v2d_pdpd_cfg_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_ctrl_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_post_c_center_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_gmp_static_config_tbl[V2D_PDPD_MAX_GMP_TERMS];
extern v2d_flow_tbl_t g_v2d_pdpd_ddr_static_config_tbl[V2D_PDPD_MAX_DDR_TERMS];
extern v2d_flow_tbl_t g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[V2D_PDPD_MAX_GMP_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_gmp_dynamic_live_gmp_c_live_config_tbl[V2D_PDPD_MAX_GMP_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[V2D_PDPD_MAX_GMP_TERMS];
extern v2d_flow_tbl_t g_pdpd_gmp_dynamic_live_gmp_shift_live_config_tbl[V2D_PDPD_MAX_GMP_TERMS];
extern v2d_flow_tbl_t g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[V2D_PDPD_MAX_DDR_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_ddr_dynamic_live_ddr_c_live_config_tbl[V2D_PDPD_MAX_DDR_TERMS][V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[V2D_PDPD_MAX_DDR_TERMS];
extern v2d_flow_tbl_t g_pdpd_ddr_dynamic_live_ddr_shift_live_config_tbl[V2D_PDPD_MAX_DDR_TERMS];
extern v2d_flow_tbl_t g_pdpd_nl_c_shdw_config_tbl[V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_nl_c_live_config_tbl[V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_pdpd_extra_static_config_tbl[V2D_PDPD_MAX_C_LUT_SEGMENTS];
extern v2d_flow_tbl_t g_v2d_pdpd_post_c_config_tbl[V2D_PDPD_MAX_POST_C_TERMS];
extern v2d_flow_tbl_t g_v2d_pdpd_post_c_center_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_passthru_live_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_passthru_shdw_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_passthru_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_nl_config_tbl[1];
extern v2d_flow_tbl_t g_v2d_pdpd_tcnt_update_c_config_tbl[1];
extern char *g_rcs_file_path[1];

/*Function Declarations*/
int get_v2d_interrupt_status(int v2d_num, int apb_num);
int data_compare (int *underrun_sample, int *underrun_sample_new, int size);
int pdpd_cfg_reg_config(int v2d_num, int apb_num, int passthru_value, pdpd_rate_t pdpd_rate);
int ganging_pdpd_cfg_reg_config(int v2d_num, int apb_num, int passthru_value, pdpd_rate_t pdpd_rate);
int pdpd_ctrl_reg_config(int v2d_num, int apb_num, int update_passthru_bit, int update_c_lut_bit);
int pdpd_passthru_c_reg_config(int v2d_num, int apb_num, int i_value, int q_value);
int pdpd_post_c_center_config(int v2d_num, int apb_num, int value);
int pdpd_post_c_reg_config(int v2d_num, int apb_num, int value);
int pdpd_gmp_static_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value);
int pdpd_gmp_static_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value, pdpd_rate_t pdpd_in_rate);
int pdpd_gmp_static_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int passthru_delay_value);
int pdpd_ddr_static_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value);
int pdpd_ddr_static_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value, pdpd_rate_t pdpd_in_rate);
int pdpd_ddr_static_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int passthru_delay_value);
int pdpd_gmp_dynamic_live_gmp_c_config(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value);
int pdpd_gmp_dynamic_live_gmp_shift_live_reg_config(int v2d_num, int apb_num, int num_gmp_terms, int shift_val);
int pdpd_ddr_dynamic_live_ddr_shift_live_reg_config(int v2d_num, int apb_num, int num_ddr_terms, int shift_val);
int pdpd_ddr_dynamic_live_ddr_c_live_reg_config(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value);
int pdpd_nl_c_live_reg_config(int v2d_num, int apb_num);
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value);
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value);
int pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int i_value, int q_value);
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value);
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value);
int pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int i_value, int q_value);
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_gmp_terms, int shift_val);
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_gmp_terms, int shift_val);
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_gmp_terms, int shift_val);
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_p5_1_2(int v2d_num, int apb_num, int num_ddr_terms, int shift_val);
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(int v2d_num, int apb_num, int num_ddr_terms, int shift_val);
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_8(int v2d_num, int apb_num, int num_ddr_terms, int shift_val);
int pdpd_extra_static_reg_config (int v2d_num, int apb_num, int passthru_delay);
int pdpd_passthru_c_live_reg_config(int v2d_num, int apb_num, int i_value, int q_value);
int pdpd_passthru_c_shdw_reg_config(int v2d_num, int apb_num, int i_value, int q_value);
int pdpd_tcnt_update_passthru_config(int v2d_num, int apb_num, int sample_cnt_value);
int pdpd_tcnt_update_nl_lut_config(int v2d_num, int apb_num, int sample_cnt_value);
int pdpd_tcnt_update_c_lut_config(int v2d_num, int apb_num, int sample_cnt_value);
int release_reset_abc_noc (void *srp);
int tx_start_bfn_trigger(int v2d_num, int apb_num);
int pdpd_start_bfn_force_trigger(int v2d_num, int apb_num);
int interrupt_status_check(int v2d_num, int apb_num, int v2d_exp_value, int nsip0_exp_value, int nsip1_exp_value);
void fill_level_check(int v2d_num, int apb_num, int fill_level_value);
void pdpd_fill_level_check(int v2d_num, int apb_num, int fill_level_value);
int gmp_ddr_shdw_live_reg_check(v2d_shdw_live_reg_check_t *reg_check);
int gmp_reg_check(int v2d_num, int apb_num, int (*gmp_c_value)[V2D_PDPD_MAX_C_LUT_SEGMENTS]);
int ddr_reg_check(int v2d_num, int apb_num, int (*ddr_c_value)[V2D_PDPD_MAX_C_LUT_SEGMENTS]);
int gmp_shift_reg_check(int v2d_num, int apb_num, int *gmp_shift_value);
int ddr_shift_reg_check(int v2d_num, int apb_num, int *ddr_shift_value);
int passthru_reg_check(int v2d_num, int apb_num, int value);
int passthru_shdw_reg_check(int v2d_num, int apb_num, int value);
int get_tx_pdpd_wm_hilo(int v2d_num, int apb_num, int num_streams, int *watermark_buf);
void get_quad_pdpd_tx_wm_hilo(int quad_instance, int num_streams, int (*watermark_buf)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS]);
int get_tx_wm_hilo(int v2d_num, int apb_num, int num_streams, int *watermark_buf);
void get_quad_tx_wm_hilo(int quad_instance, int num_streams, int (*watermark_buf)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS]);
void get_tx_trigger_fill_level(int v2d_num, int apb_num, int num_stream, int *value);
void get_quad_tx_trigger_fill_level(int quad_instance, int num_stream, int (*value)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS]);
void get_pdpd_tx_trigger_fill_level(int v2d_num, int apb_num, int num_stream, int *value);
void get_quad_pdpd_tx_trigger_fill_level(int quad_instance, int num_stream, int (*value)[PDPD_MAX_INSTANCE][MAX_NUM_STREAMS]);
void populate_g_buffer(unsigned int (*dpd_coeff_buffer)[NUM_WORDS_PER_LUT], v2d_shdw_live_reg_check_t *reg_check, lut_mode_t lut_mode);
void get_nsip0_insert_fifo_ptr(int v2d_num, int apb_num, int num_cmd_queue, int *fifo_ptr);
void get_nsip1_insert_fifo_ptr(int v2d_num, int apb_num, int num_cmd_queue, int *fifo_ptr);
int v2d_all_test_init();
int get_all_v2d_int_status(int num_v2d, int value);
int vex_dmem_write(int vex_num, int address, int value);
int vex_dmem_check(int vex_num, int address, int exp_value);
int v2d_quad_clk_enable(int quad_instance);
int quad_interrupt_status_check(int quad_instance, int (*exp_interrupt_value)[PDPD_MAX_INSTANCE], int nsip0_exp_value, int nsip1_exp_value);
int get_start_l_cnt_value(int v2d_num, int *value);
int rcs_halt_reset_load(void *srp_rcs, void *rcs_hdl);
uint64_t get_rcs_dmac_ch1_int_status();
int clear_rcs_dmac_ch1_int(uint64_t value);
int bfn_interrupt_status_check(int v2d_num, int apb_num, uint32_t subb_lo_value, uint32_t subb_hi_value);
int write_interrupt_clear(int v2d_num, int apb_num, uint32_t v2d_int_value, uint32_t nsip_0_int_value, uint32_t nsip_1_int_value);
int quad_tx_drf_check(int quad_instance);
int quad_2_channel_tx_drf_check(int quad_instance, int apb_num);
int quad_tx_pdpd_check(int quad_instance);
int quad_2_channel_tx_pdpd_check(int quad_instance, int apb_num);
int follower_bfn_wa_fpga();
int poll_rsm_flag_rcs(uint32_t address, uint32_t expected_value);
int pdpd_ingress_cap_mem_compare(int v2d_num, int additional_factor, int num_vectors_per_block, int capture_delay_value,
        drf_clock_t drf_clock, uint32_t blocks_to_compare);
int get_match_offset(uint32_t address, uint32_t ref_data, int size);
int quad_pdpd_ingress_cap_mem_compare(quad_mem_compare_t *mem_compare);
int stale_value_compare(uint32_t address, int offset, int add_val, int num_vectors_per_block);
uint32_t get_mem_fb_base_address(int v2d_num);
int fb_mem_compare_extra_block(int v2d_num, int num_vectors, uint32_t value, int block_num);
int pdpd_ingress_cap_mem_compare_repeat(repeat_mem_compare_t *mem_compare);
int load_vex_param(int vex_core_id, int size, unsigned int *offset, unsigned int *val);
int mem_fb_x_capture_repeat_mode_configuration(int size_per_sector, int v2d_num, int apb_num);
int quad_mem_fb_x_capture_repeat_mode_configuration(int quad_instance, int num_antennas, int size_per_antenna);
bool get_us_granularity_status(drf_clock_t drf_clock, int test_config);
int input_pattern_read(int *input_data, char *file);
void fill_mem_fb(int v2d_num, uint32_t value);
int pdpd_egress_cap_mem_compare(int v2d_num, int num_vectors_per_block, int capture_delay_value,
        drf_clock_t drf_clock, uint32_t blocks_to_compare, int lut_block_duration, lut_mode_t lut_mode, FILE *fp_ref);
int get_frac_os(int test_config);
int rcsHaltsoftReset(void);

#if LIVEIQ_SAMPLES 
int pdpd_gmp_ddr_config_p5_1_2_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t * v2d_liveIQ_param);
int pdpd_gmp_ddr_config_iq_4_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param);
int pdpd_gmp_ddr_config_iq_8_generic_wrapper(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param);
int liveIQ_pdpd_egress_cap_mem_read(int v2d_num, int *ref_data, int* y_out,  int num_vectors_per_block, drf_clock_t drf_clock, uint32_t blocks_to_compare);
#endif //LIVEIQ_SAMPLES
#endif
