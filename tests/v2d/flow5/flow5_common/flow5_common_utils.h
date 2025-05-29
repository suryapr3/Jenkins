#ifndef __FLOW4_UTIL_H__
#define __FLOW4_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/* Set Tx_CFG_COMPLETE (23) to 1 , PD_EXTRA_EN(16) to 1*/
#define TX_GNRL_CSR_VALUE   AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK | AV2D_CSR_TX_CSR_TX_GNRL_CSR_PD_EXTRA_EN_BF_MSK
/* RX_CFG_COMPLETE (0) to 1*/
#define RX_GNRL_CSR_VALUE   AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_CFG_COMPLETE_BF_MSK
#define GMP_C_I_VALUE  (1 << 11)
#define GMP_C_Q_VALUE  0
#define DDR_C_I_VALUE   0
#define DDR_C_Q_VALUE   0

#define FLOW5_PASSTHRU_DELAY  10
#define FLOW5_EXTRA_DELAY   10
#define FLOW5_GMP_SHIFT_VALUE   0
#define FLOW5_DDR_SHIFT_VALUE   0

#define V2D_PDPD_GMP_TERMS  2   // Number of GMP terms that are active
#define V2D_PDPD_DDR_TERMS  0   // Number of DDR terms that are active

#define PDPD_MAIN_UNDERRUN_BIT 18
#define RX_1_NOCFG_DROP_BIT 11
#define V2D_INTERRUPT_VALUE AV2D_CSR_INT_CSR_INT_STATUS_PD_MAIN_UNDERRUN_BF_MSK  | AV2D_CSR_INT_CSR_INT_STATUS_PD_EXTRA_UNDERRUN_BF_MSK
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

#endif
