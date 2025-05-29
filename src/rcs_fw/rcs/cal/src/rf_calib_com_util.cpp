/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/

/**
 * @file    rf_calib_com_util.cpp
 * @brief   Utility functions for calibration support
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_com_util.cpp
 */
#include "stddef.h"
#include <xtensa/config/core-isa.h>
#include <xtensa/config/system.h>
#include <xtensa/tie/xt_bben.h>
#include "xtensa/core-macros.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Convert the 13 bit MSB aligned DMA data from capture memory to float.
 *                  The LSB 3 bits may have junk so need clean up before conversion to float
 * @param [in]  data_in   : Pointer to the int16_t buffer holding the DMA input samples
 * @param [in]  size      : size of the input and output
 * @param [in]  num_bits_to_clear   : Number of bits in the LSB to be cleared before conversion to float
 * @param [in]  data_out  : Pointer to the float array to store the converted output.
 * @return          none.
 * Restrictions:
 * data_in and data_out can be non aligned but the size must be multiple of 4
 * -------------------------------------------------------------------------------------------------------------------*/
void rf_calib_com_convert_dma_output_to_float (const int16_t *__restrict data_in, const uint32_t size, const uint32_t num_bits_to_clear, const float *__restrict data_out)
{
    int i, j;
    xb_vecN_2x32v vy_2;
    xb_vecN_2x32v mask;

    valign vaData_out_1;
    valign vaData_in;
    xb_vecN_2xf32 *__restrict ptr_out_1 = (xb_vecN_2xf32*)data_out;
    xb_vecN_2x16 *__restrict ptr_in = (xb_vecN_2x16*)data_in;
    xb_vecNx16 *__restrict ptr_in_align = (xb_vecNx16*)data_in;
    vaData_out_1 = BBE_ZALIGN ();
    vaData_in = BBE_LANX16_PP(ptr_in_align);
    xb_vecN_2xf32 v_out_1;
    mask = int16_rtor_xb_vecN_2x32v((1 << num_bits_to_clear)-1);
    mask = BBE_NOTN_2X32(mask);
    for (j = 0; j < size; j = j + 4)
    {
        BBE_LAN_2X16S_IP(vy_2,vaData_in,ptr_in);
        vy_2 = BBE_ANDN_2X32(vy_2, mask);
        v_out_1 = BBE_FLOATN_2X32(vy_2,15);
        BBE_SAN_2XF32_IP(v_out_1,vaData_out_1,ptr_out_1);
    }
    BBE_SAN_2XF32POS_FP(vaData_out_1,ptr_out_1);
    return;
}
