/* INTEL CONFIDENTIAL
 *
 * Copyright  2024 Intel Corporation All Rights Reserved.
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
#if (CPU_AX)
/**
 * @file    com_swg_test.c
 * @brief
 * @details
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"
#include "com_assert.h"
#include "com_swg.h"

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
int main (int argc, char **argv)
{
    uint32_t f_shift[] = {10, 450, 80000};          // 10MHz, 450MHz, 8000MHz
    uint32_t f_op[] = {983040, 1474560};            // 1GHz / 1.5GHz
    uint32_t num_pp[] = {1, 2, 3, 4, 6, 8, 12, 16}; // 1..16

    uint64_t verify_result[3][2][8] = {
        {{0x2aaaaa, 0x155555, 0xe38e3, 0xaaaaa, 0x71c71, 0x55555, 0x38e38, 0x2aaaa},
         {0x1c71c7, 0xe38e3, 0x97b42, 0x71c71, 0x4bda1, 0x38e38, 0x25ed0, 0x1c71c}},
        {{0x7800000, 0x3c00000, 0x2800000, 0x1e00000, 0x1400000, 0xf00000, 0xa00000, 0x780000},
         {0x5000000, 0x2800000, 0x1aaaaaa, 0x1400000, 0xd55555, 0xa00000, 0x6aaaaa, 0x500000}},
        {{0x535555555, 0x29aaaaaaa, 0x1bc71c71c, 0x14d555555, 0xde38e38e, 0xa6aaaaaa, 0x6f1c71c7, 0x53555555},
         {0x378e38e38, 0x1bc71c71c, 0x1284bda12, 0xde38e38e, 0x9425ed09, 0x6f1c71c7, 0x4a12f684, 0x378e38e3}}};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                uint64_t tmp = cordic_incr_calc (f_shift[i], f_op[j], num_pp[k]);
                if (verify_result[i][j][k] != tmp)
                {
                    FW_PRINT (FW_INFO, "failed at index i=%d j=%d k=%d", i, j, k);
                    FW_PRINT (FW_INFO, "value get 0x%x", tmp);
                    FW_PRINT (FW_INFO, "value expected 0x%x", verify_result[i][j][k]);
                }
            }
        }
    }
    return 0;
}
#endif
