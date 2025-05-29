#ifndef __FLOW2_UTIL_H__
#define __FLOW2_UTIL_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define V2D_INTERRUPT_VALUE 0x40000
/*TX_CFG_COMPLETE(23) bit was set*/
#define TX_GNRL_CSR_VALUE   ((1 << 23) | AV2D_CSR_TX_CSR_TX_GNRL_CSR_BUFF_1_PWR_DOWN_BF_MSK)
/*RX_CFG_COMPLETE(0) bit was set*/
#define RX_GNRL_CSR_VALUE   (1 << 0)

#define FLOW2_PASSTHRU_VALUE    0

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

int flow2_configure_pdpd(int v2d_num, int apb_num, int test_config, int post_c_center_value);
#endif


