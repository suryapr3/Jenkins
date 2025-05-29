#ifndef __GANGING_UTIL_H__
#define __GANGING_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
/* Set Tx_CFG_COMPLETE (23) to 1 and EXTRA_EN (16) to 1*/
#define TX_GNRL_CSR_VALUE_EXTRA_TERMS   ((1 << 23) | (1 << 16))
/* Set Tx_CFG_COMPLETE (23) to 1*/
#define TX_GNRL_CSR_VALUE   ((1 << 23))
/* RX_CFG_COMPLETE (0) to 1*/
#define RX_GNRL_CSR_VALUE   (1 << 0)

#define GMP_C_I_VALUE  (1 << 11)
#define GMP_C_Q_VALUE  0
#define DDR_C_I_VALUE   0
#define DDR_C_Q_VALUE   0
#define GANGING_PASSTHRU_DELAY    10
#define GANGING_GMP_SHIFT_VALUE   0
#define GANGING_DDR_SHIFT_VALUE   0
#define GANGING_NL_VALUE    0
#define GANGING_EXTRA_DELAY GANGING_PASSTHRU_DELAY

#define V2D_PDPD_GMP_TERMS  2   // Number of GMP terms that are active
#define V2D_PDPD_DDR_TERMS  0   // Number of DDR terms that are active

#define V2D_INTERRUPT_VALUE AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_MSK //(1 << PDPD_MAIN_UNDERRUN_BIT)

#define V2D_INTERRUPT_VALUE_EXTRA_TERMS (AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_MSK  | AV2D_CSR_INT_CSR_INT_STAT_PD_EXTRA_UNDERRUN_BF_MSK)

#define TEST_VECTORS_PATH_PREFIX   "test_vectors/"

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

char* get_ref_file_flow3(int post_filter_mode, int test_config);
int pdpd_gmp_ddr_reg_config(int v2d_num, int apb_num, int test_config);
int pdpd_gmp_ddr_reg_config_p5_1_2(int v2d_num, int apb_num);
int pdpd_gmp_ddr_reg_config_iq_4(int v2d_num, int apb_num, pdpd_rate_t pdpd_in_rate);
int pdpd_gmp_ddr_reg_config_iq_8(int v2d_num, int apb_num);
#endif
