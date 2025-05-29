#ifndef __SAMPLE_COUNT_UTILS_H__
#define __SAMPLE_COUNT_UTILS_H__

#include "common_utils.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define PASSTHRU_I_COEFF    (1 << 13)
#define PASSTHRU_Q_COEFF    (1 << 12)
#define PASSTHRU_SHDW_I_COEFF    (1 << 3)
#define PASSTHRU_SHDW_Q_COEFF    (1 << 2)
#define GMP_C_I_VALUE  (1 << 11)
#define GMP_C_Q_VALUE  (1 << 11)
#define DDR_C_I_VALUE   (1 << 11)
#define DDR_C_Q_VALUE   (1 << 11)
#define SAMPLE_CNT_VALUE    1000
#define INCR_SAMPLE_CNT_VALUE   1000
#define NL_C_VALUE  0x70F


/* Set Tx_CFG_COMPLETE (23) to 1*/
#define TX_GNRL_CSR_VALUE   ((1 << 23))
/* RX_CFG_COMPLETE (0) to 1*/
#define RX_GNRL_CSR_VALUE   (1 << 0)

// PDPD related Macros
#define PASSTHRU_DELAY  10
#define GMP_SHIFT_VALUE 0xE
#define DDR_SHIFT_VALUE 0xE

#define GMP_SHIFT_LIVE  0xF
#define DDR_SHIFT_LIVE  0xF
#define NL_C_LIVE   0x777


#define PDPD_MAIN_UNDERRUN_BIT 18
#define RX_1_NOCFG_DROP_BIT 11
#define V2D_INTERRUPT_VALUE ((1 << PDPD_MAIN_UNDERRUN_BIT) | (1 << AV2D_CSR_INT_CSR_INT_STATUS_PC_UPDATE_ERR_BF_OFF))


/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

#endif
