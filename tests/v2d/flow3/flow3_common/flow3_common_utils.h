#ifndef __FLOW3_UTIL_H__
#define __FLOW3_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
/* Set Tx_CFG_COMPLETE (23) to 1*/
#define TX_GNRL_CSR_VALUE   (AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK | AV2D_CSR_TX_CSR_TX_GNRL_CSR_BUFF_1_PWR_DOWN_BF_MSK)
/* RX_CFG_COMPLETE (0) to 1*/
#define RX_GNRL_CSR_VALUE   (1 << 0)
#define GMP_C_I_VALUE  (1 << 11)
#define GMP_C_Q_VALUE  0
#define DDR_C_I_VALUE   0
#define DDR_C_Q_VALUE   0
#define FLOW3_PASSTHRU_DELAY    10
#define FLOW3_GMP_SHIFT_VALUE   0
#define FLOW3_DDR_SHIFT_VALUE   0

#define V2D_PDPD_GMP_TERMS  2   // Number of GMP terms that are active
#define V2D_PDPD_DDR_TERMS  0   // Number of DDR terms that are active

#define V2D_INTERRUPT_VALUE AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_MSK //(1 << PDPD_MAIN_UNDERRUN_BIT)

#define INPUT_IQ_FILE   ("../test_vectors_1us/input_iq.txt")
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/*Function Declarations*/
int pdpd_gmp_ddr_reg_config(int v2d_num, int apb_num, int test_config);
int pdpd_gmp_ddr_reg_config_p5_1_2(int v2d_num, int apb_num);
int gbuffer_update_configure_pdpd(int v2d_num, int apb_num, int test_config);
int pdpd_gmp_ddr_reg_config_iq_4(int v2d_num, int apb_num, pdpd_rate_t pdpd_in_rate);
int pdpd_gmp_ddr_reg_config_iq_8(int v2d_num, int apb_num);
char* get_ref_file_flow3(int post_filter_mode, int test_config);
int dynamic_gbuffer_update_configure_pdpd(int v2d_num, int apb_num, int test_config, int num_gmp_terms, int num_ddr_terms);
int flow3_configure_pdpd(int v2d_num, int apb_num, int test_config);
#if LIVEIQ_SAMPLES
int pdpd_gmp_ddr_reg_config_generic(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param, int test_config);
int pdpd_gmp_ddr_reg_config_p5_1_2_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param);
int pdpd_gmp_ddr_reg_config_iq_4_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param);
int pdpd_gmp_ddr_reg_config_iq_8_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param);
#endif  //
#endif
