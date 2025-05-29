#ifndef __FLOW7_UTIL_H__
#define __FLOW7_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/* Set Tx_CFG_COMPLETE (23) to 1*/
#define TX_GNRL_CSR_VALUE   ((1 << 23) | (1 << 16))
/* RX_CFG_COMPLETE (0) to 1*/
#define RX_GNRL_CSR_VALUE   (1 << 0)
#define TX_UNDERRUN_VALUE   AV2D_CSR_INT_CSR_INT_STATUS_PD_EXTRA_UNDERRUN_BF_MSK
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

#endif


