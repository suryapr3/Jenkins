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
 * @file    rf_calib_nleq_gen_ltl_matrix.cpp
 * @brief   Implementaion of the LTL matrix from the L matrix
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_gen_ltl_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_ltl_matrix.h"
#include "rf_calib_nleq_const.h"
#include "rf_calib_nleq_dot_product_optimized.h"
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
 * @brief           Generate the LTL matrix
 * @param [out]     ltl_mat: Reference to the LTL matrix where output will be writen
 * @param [in]      L_mat: Reference to the L matrix
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_ltl_matrix (rf_calib_float_matrix_dy_dy &ltl_mat, rf_calib_float_matrix_dy_dy &L_mat)
{
#if LTLFTF_EIGEN == 1
    ltl_mat.noalias () += (L_mat.transpose () * L_mat);
    return;
#endif

#if LTLFTF_EIGEN_OPTIMIZED == 1
    ltl_mat.template selfadjointView<Eigen::Lower> ().rankUpdate (L_mat.transpose ());
    return;
#endif

#if LTLFTF_HANDCODED
    float *temp = L_mat.data ();
    float *temp1 = ltl_mat.data ();
    int size = RF_CALIB_NLEQ_F_MATRIX_ROWS;

    // 20 = 5*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_4_opt (temp, temp + 1600, size, temp1 + 16);
    temp += size;
    temp1 += 21;
    // 19 = 4*4 + 2 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_2_opt (temp, temp + 1600, size, temp1 + 16);
    rf_calib_dot_product_1_opt (temp, temp + 1800, size, temp1 + 18);
    temp += size;
    temp1 += 21;
    // 18 = 4*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_2_opt (temp, temp + 1600, size, temp1 + 16);

    temp += size;
    temp1 += 21;
    // 17 = 4*4 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_1_opt (temp, temp + 1600, size, temp1 + 16);

    temp += size;
    temp1 += 21;
    // 16 = 4*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 21;
    // 15 =  3*4 + 2 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_2_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_1_opt (temp, temp + 1400, size, temp1 + 14);

    temp += size;
    temp1 += 21;
    // 14 = 3*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_2_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 21;
    // 13 = 3*4 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_1_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 21;
    // 12 = 3*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 21;
    // 11 =  2*4 + 2 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_2_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_1_opt (temp, temp + 1000, size, temp1 + 10);

    temp += size;
    temp1 += 21;
    // 10 = 2*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_2_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 21;
    // 9 = 2*4 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_1_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 21;
    // 8 = 2*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 21;
    // 7 = 4 + 2 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_2_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_1_opt (temp, temp + 600, size, temp1 + 6);

    temp += size;
    temp1 += 21;
    // 6 = 4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_2_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 21;
    // 5 = 4 + 1
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_1_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 21;
    // 4 = 4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);

    temp += size;
    temp1 += 21;
    // 3 = 2+1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_1_opt (temp, temp + 200, size, temp1 + 2);

    temp += size;
    temp1 += 21;
    // 2 = 2
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);

    temp += size;
    temp1 += 21;
    // 1 = 1
    rf_calib_dot_product_1_opt (temp, temp, size, temp1);

    return;
#endif
}
