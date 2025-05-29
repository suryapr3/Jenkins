#ifndef __FLOW6_UTIL_H__
#define __FLOW6_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define V2D_INTERRUPT_VALUE AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_MSK
/* Set Tx_CFG_COMPLETE (23) to 1*/
#define TX_GNRL_CSR_VALUE  AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK | AV2D_CSR_TX_CSR_TX_GNRL_CSR_BUFF_1_PWR_DOWN_BF_MSK

#define POST_PROCESSING_TX_GNRL_CSR_VALUE  AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK
/* RX_PD_CFG_COMPLETE (2) to 1*/
#define RX_GNRL_CSR_VALUE  AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_EN_BF_MSK | AV2D_CSR_RX_CSR_RX_GNRL_CSR_RX_PD_CFG_COMPLETE_BF_MSK

#define POST_PROCESSING_TX_GNRL_CSR_VALUE   AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_MSK

#define FLOW6_PASSTHRU_VALUE    0

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

#endif


