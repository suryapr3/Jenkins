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
 * @file    rf_calib_nleq_qua_comp_exp_obt_diff.cpp
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_qua_comp_exp_obt_diff.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_qua_comp_exp_obt_diff.h"
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
 * @brief           Compute the difference between expected fixed point NLEQ coefficients and the obtained fixd point NLEQ coefficients
 * @param [in]      input: Reference to double matrix containing the computed NLEQ coefficients. Column 0 has the obtained double value
 * coefficients. Column 1 has the MATLAB computed double NLEQ coefficients
 * @param [out]     output: Reference to integer matrix of 3 columns. Column 0 has the computed fixed point NLEQ coefficients, Column 1 has
 * the MATLAB fixed point coefficnts and column 2 has  the absolute of the difference between the computed and expected fixed point NLEQ
 * coefficients
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_quantize_compute_expected_obtained_difference (rf_calib_double_matrix_dy_dy &input, rf_calib_int_matrix_dy_dy &output)
{
    using std::ceil;
    int factor = 1 << RF_CALIB_NLEQ_COEFF_OUTPUT_NUM_FRACTIONAL_BITS;
    output.leftCols<2> () = (((input * factor).array ()).round ()).template cast<int> ();
    output.col (2) = (output.col (1) - output.col (0)).cwiseAbs ();
    return;
}
