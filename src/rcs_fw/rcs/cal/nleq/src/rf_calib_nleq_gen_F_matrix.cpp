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
 * @file    rf_calib_nleq_gen_F_matrix.cpp
 * @brief   Generate the F matrix from the interpolator output and the basis functions
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_gen_F_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_F_matrix.h"
#include "rf_calib_nleq_const.h"
#include <Eigen/Core>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static int32_t basis_mapping[RF_CALIB_NLEQ_BASIS_LENGTH][3] = {
    {1, 0, 1},  {0, 2, 0}, // x, square, no delay -1
    {1, 2, 0},             // x-, square, no delay -2
    {2, 2, 0},             // x--, square, no delay -3
    {2, 1, 1},             // x--, linear, +1 delay -4
    {0, 1, 0},             // x, linear, no delay -5
    {1, 1, 0},             // x-, linear, no delay -6
    {2, 1, 0},             // x--, linear, no_delay -7
    {0, 1, -1},            // x, linear, -1 delay -8
    {1, 3, 1},             // x-,cube,+1 delay -9
    {2, 3, 1},             // x--,cube,+1 delay -10
    {0, 3, 0},             // x,cube,no delay -11
    {1, 3, 0},             // x-, cube no delay -12
    {2, 3, 0},             // x--, cube, no delay -13
    {0, 3, -1},            // x, cube, -1 delay -14
    {1, 3, -1},            // x-,cube,-1 delay -15
    {2, 3, -1},            // x--,cube,-1 delay -16
    {0, 3, -2}             // x,cube, -2 delay -17

};

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
 * @brief           Generate the F matrix. This is the plain implementation which is very inefficient as it generates output row by row
 * @param [in]      interp_out: Reference to the interpolator output matrix
 * @param [in]      offset: offset into the interp_out matrix from where the data should be used for the F matrix generation
 * @param [out]     F: Referebce to the F matrix where the output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_F_matrix (rf_calib_float_matrix_dy_dy &interp_out, rf_calib_float_matrix_dy_dy &F, uint32_t offset)
{
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_F_MATRIX_ROWS; ++i)
    {
        F (i, 0) = 1.0;
        for (uint32_t j = 1; j < RF_CALIB_NLEQ_BASIS_LENGTH; ++j)
        {
            F (i, j) = pow (interp_out (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR + i * RF_CALIB_NLEQ_ADC_NUM_PHASE + basis_mapping[j][2],
                                        basis_mapping[j][0]),
                            basis_mapping[j][1]);
        }
    }
    return;
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Generate the F matrix. This is an improvement over the plain implementation and the matrix is generated column wise. It
 * is still inefficient as the same data gets accessed at different times
 * @param [in]      interp_out: Reference to the interpolator output matrix
 * @param [in]      offset: offset into the interp_out matrix from where the data should be used for the F matrix generation
 * @param [out]     F: Referebce to the F matrix where the output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_F_matrix_new (rf_calib_float_matrix_dy_dy &interp_out, rf_calib_float_matrix_dy_dy &F, uint32_t offset)
{
    F.col (0).array () = 1.0;

    for (uint32_t j = 1; j < RF_CALIB_NLEQ_BASIS_LENGTH; ++j)
    {
        F.col (j) =
            interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR + basis_mapping[j][2], fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE),
                        basis_mapping[j][0])
                .array ()
                .pow (basis_mapping[j][1]);
    }
    return;
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Generate the F matrix. This is the efficient implementation as the generation of different columns of the F matrix is
 * done according to the data being fetched. The drawback is if the basis functions change the changes need to be hand coded again
 * @param [in]      interp_out: Reference to the interpolator output matrix
 * @param [in]      offset: offset into the interp_out matrix from where the data should be used for the F matrix generation
 * @param [out]     F: Referebce to the F matrix where the output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_F_matrix_new1 (rf_calib_float_matrix_dy_dy &interp_out, rf_calib_float_matrix_dy_dy &F, uint32_t offset)
{
    F.col (0).array () = 1.0;
    F.col (1) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0).array ().square ();
    F.col (5) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0);
    F.col (11) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0).array ().cube ();
    F.col (2) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 1).array ().square ();
    F.col (6) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 1);
    F.col (12) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 1).array ().cube ();
    F.col (3) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2).array ().square ();
    F.col (7) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2);
    F.col (13) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2).array ().cube ();
    F.col (8) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR - 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0);
    F.col (14) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR - 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0).array ().cube ();
    F.col (15) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR - 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 1).array ().cube ();
    F.col (16) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR - 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2).array ().cube ();
    F.col (17) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR - 2, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 0).array ().cube ();
    F.col (9) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR + 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 1).array ().cube ();
    F.col (4) = interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR + 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2);
    F.col (10) =
        interp_out (seqN (offset + RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR + 1, fix<100>, RF_CALIB_NLEQ_ADC_NUM_PHASE), 2).array ().cube ();
    return;
}
