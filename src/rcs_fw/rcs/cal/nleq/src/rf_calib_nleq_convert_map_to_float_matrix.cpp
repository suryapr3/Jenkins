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
 * @file    rf_calib_nleq_convert_map_to_float_matrix.cpp
 * @brief   Convert the map structure holding fixed point captured samples to floating point values and store them in a matrix
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_convert_map_to_float_matrix.h"
#include "rf_calib_nleq_const.h"

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
 * @brief           Convert the fixed point captured samples to floating point
 * @param [in]      input: Reference to the map structure holding the fixed point samples
 * @param [in]      pre_cursor: To make the captured waveform periodic, leave the pre_cirsor samples in the output
 * @param [in]      output: Reference to the output matrix with floating point values
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_convert_map_to_float_matrix (rf_calib_int_map_dy_1 &input, uint32_t pre_cursor, rf_calib_float_matrix_dy_dy &output)
{
    float factor = 1.0 / pow (2.0, RF_CALIB_NLEQ_DMA_IN_FRACTIONAL_BITS);
    output.middleRows (pre_cursor, RF_CALIB_NLEQ_CAPTURE_SIZE) = input.template cast<float> () * factor;
    return;
}
