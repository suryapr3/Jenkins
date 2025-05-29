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
 * @file    rf_calib_nleq_interpolate.cpp
 * @brief   Interpolator implementation using Eigen, High level language and hand optimized versions of the FIR filter
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_interpolate.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_interpolate.h"
#include "rf_calib_nleq_const.h"
#include "rf_calib_nleq_fir_f32_opt.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
using namespace Eigen;
using rf_calib_double_map_3_dy_row_major =
    Eigen::Map<Eigen::Matrix<float, 3, Dynamic>, Eigen::Aligned128, Stride<1, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH>>;

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static float filt_coeff[RF_CALIB_NLEQ_INTERPOLATION_FACTOR][RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH] __attribute__ ((aligned (128))) = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {-0.00390625, 0.0078125,   -0.01171875, 0.015625,    -0.01953125, 0.02734375,  -0.0390625, 0.05078125,
     -0.07421875, 0.109375,    -0.203125,   0.82421875,  0.4140625,   -0.16015625, 0.09765625, -0.06640625,
     0.046875,    -0.03515625, 0.02734375,  -0.01953125, 0.015625,    -0.01171875, 0.0078125,  -0.00390625},
    {-0.00390625, 0.0078125,  -0.01171875, 0.015625,    -0.01953125, 0.02734375,  -0.03515625, 0.046875,
     -0.06640625, 0.09765625, -0.16015625, 0.4140625,   0.82421875,  -0.203125,   0.109375,    -0.07421875,
     0.05078125,  -0.0390625, 0.02734375,  -0.01953125, 0.015625,    -0.01171875, 0.0078125,   -0.00390625}};

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implementation of a FIR filter routine using High level language non Eigen based
 * @param [in]      p_input: Pointer to the input data
 * @param [in]      p_filt_coeff: Pointer to the filter coefficients
 * @param [out]     p_output:  Pointer to the filtered output
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

static void rf_calib_nleq_interpolate_optimized (float *__restrict p_input, float *__restrict p_filt_coeff, float *__restrict p_output)
{
#pragma aligned(p_input, 16)
#pragma aligned(p_filt_coeff, 16)
#pragma aligned(p_output, 16)
    for (uint32_t n = 0; n < RF_CALIB_NLEQ_CAPTURE_SIZE; n += 4)
    {
        for (uint32_t k = 0; k < RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH; k += 4)
        {
            uint32_t temp = n - k + RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH - 1;
            p_output[n] += p_filt_coeff[k] * p_input[temp] + p_filt_coeff[k + 1] * p_input[temp - 1]
                           + p_filt_coeff[k + 2] * p_input[temp - 2] + p_filt_coeff[k + 3] * p_input[temp - 3];
            p_output[n + 1] += p_filt_coeff[k] * p_input[temp + 1] + p_filt_coeff[k + 1] * p_input[temp]
                               + p_filt_coeff[k + 2] * p_input[temp - 1] + p_filt_coeff[k + 3] * p_input[temp - 2];
            p_output[n + 2] += p_filt_coeff[k] * p_input[temp + 2] + p_filt_coeff[k + 1] * p_input[temp + 1]
                               + p_filt_coeff[k + 2] * p_input[temp] + p_filt_coeff[k + 3] * p_input[temp - 1];
            p_output[n + 3] += p_filt_coeff[k] * p_input[temp + 3] + p_filt_coeff[k + 1] * p_input[temp + 2]
                               + p_filt_coeff[k + 2] * p_input[temp + 1] + p_filt_coeff[k + 3] * p_input[temp];
        }
    }
    return;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Eigen implementation of interpolator
 * @param [in]      dma_in_float: Reference to the matrix containing the input
 * @param [out]     rf_calib_interp_out: Reference to the matrix where the filtered outpu will be stored
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_interpolate (rf_calib_float_matrix_dy_dy &dma_in_float, rf_calib_float_matrix_dy_dy &rf_calib_interp_out)
{
    rf_calib_double_map_3_dy_row_major interpolation_filter_map_matrix (&filt_coeff[0][0], 3, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH);
    for (int i = 0; i < RF_CALIB_NLEQ_CAPTURE_SIZE; i++)
    {
        rf_calib_interp_out.block<1, 1> (i + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR, 0).noalias () =
            interpolation_filter_map_matrix.row (0)
            * dma_in_float.middleRows (i, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH).colwise ().reverse ();
        rf_calib_interp_out.block<1, 1> (i + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR, 1).noalias () =
            interpolation_filter_map_matrix.row (1)
            * dma_in_float.middleRows (i, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH).colwise ().reverse ();
        rf_calib_interp_out.block<1, 1> (i + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR, 2).noalias () =
            interpolation_filter_map_matrix.row (2)
            * dma_in_float.middleRows (i, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH).colwise ().reverse ();
    }
    return;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implementation of interpolator using High level language implementation of FIR filter
 * @param [in]      p_input: Pointer to the input data
 * @param [out]     p_output: Pointer to the interpolated output
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void rf_calib_nleq_interpolate (float *p_input, float *p_output)
{
    rf_calib_nleq_interpolate_optimized (p_input, &filt_coeff[0][0], p_output + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR);
    rf_calib_nleq_interpolate_optimized (p_input, &filt_coeff[1][0],
                                         p_output + RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE
                                             + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR);
    rf_calib_nleq_interpolate_optimized (p_input, &filt_coeff[2][0],
                                         p_output + 2 * RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE
                                             + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implementation of interpolator using hand optimized FIR filter
 * @param [in]      p_input: Pointer to the input data
 * @param [out]     p_output: Pointer to the interpolated output
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_interpolate_intrinsic (float *p_input, float *p_output)
{
    rf_calib_nleq_fir_f32_opt (p_input, &filt_coeff[0][RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH - 1],
                               p_output + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR, RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH,
                               RF_CALIB_NLEQ_CAPTURE_SIZE);
    rf_calib_nleq_fir_f32_opt (p_input, &filt_coeff[1][RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH - 1],
                               p_output + RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR,
                               RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH, RF_CALIB_NLEQ_CAPTURE_SIZE);
    rf_calib_nleq_fir_f32_opt (p_input, &filt_coeff[2][RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH - 1],
                               p_output + 2 * RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE
                                   + RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR,
                               RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH, RF_CALIB_NLEQ_CAPTURE_SIZE);
}
