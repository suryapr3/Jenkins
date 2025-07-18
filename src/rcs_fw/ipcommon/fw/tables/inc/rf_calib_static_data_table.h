/* INTEL CONFIDENTIAL
 *
 * Copyright 2024 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/

/**
 * this header file is generated by tool, any direct modification without going
 * through the table generation process will get lost
 */

#ifndef __RF_CALIB_STATIC_DATA_TABLE__
#define __RF_CALIB_STATIC_DATA_TABLE__

#include "table_access_macros.h"
#include "rf_calib_static_data_bitfield.h"
#include "rf_calib_static_data_const.h"

// rf_calib_control_lut:
typedef struct
{
    rf_calib_control_lut_bf_t rf_calib_control_lut[RF_CALIB_CONTROL_LUT_MAX_ENTRY_NUM];
} rf_calib_control_lut_t;

// cal_print_config_lut:
typedef struct
{
    cal_print_config_lut_bf_t cal_print_config_lut[CAL_PRINT_CONFIG_LUT_MAX_ENTRY_NUM];
} cal_print_config_lut_t;

/*
 * rf_calib_static_data:
 */
typedef struct
{
    rf_calib_control_lut_t rf_calib_control_lut;
    cal_print_config_lut_t cal_print_config_lut;
} rf_calib_static_data_t;

#if RCS
extern rf_calib_static_data_t _dram0_cal_tables_data_start; // symbol defined in LSP
#define RF_CALIB_STATIC_DATA_START_ADDRESS (&_dram0_cal_tables_data_start)
#endif

#ifndef offsetof
#define offsetof(st, m) ((size_t)((char *)&((st *)0)->m - (char *)0))
#endif

// pointers to access each table:
#define p_rf_calib_static_data ((rf_calib_static_data_t *)(RF_CALIB_STATIC_DATA_START_ADDRESS))
#define p_rf_calib_control_lut \
    ((rf_calib_control_lut_t *)((char *)(RF_CALIB_STATIC_DATA_START_ADDRESS) + offsetof (rf_calib_static_data_t, rf_calib_control_lut)))
#define p_cal_print_config_lut \
    ((cal_print_config_lut_t *)((char *)(RF_CALIB_STATIC_DATA_START_ADDRESS) + offsetof (rf_calib_static_data_t, cal_print_config_lut)))

#endif // __RF_CALIB_STATIC_DATA_TABLE__
