#ifndef __FLOW1_UTIL_H__
#define __FLOW1_UTIL_H__

#include "common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
/*For 5nm 12th bit (Tx_UNDERRUN) and 13th bit are set*/
/*For 18A , 13th bit (Tx_NO_DATA_START) shouldn't be set*/
#define TX_UNDERRUN_VALUE   0x1000
/*TX_CFG_COMPLETE(23) bit was set*/
#define TX_GNRL_CSR_VALUE   ((1 << 23) | AV2D_CSR_TX_CSR_TX_GNRL_CSR_BUFF_1_PWR_DOWN_BF_MSK)

#define TX_GNRL_CSR_VALUE_SRAM   ((1 << 23))
/*RX_CFG_COMPLETE(0) bit was set*/
#define RX_GNRL_CSR_VALUE   (1 << 0)
#endif
