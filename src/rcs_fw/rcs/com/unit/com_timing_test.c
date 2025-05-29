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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"
#include "com_timing.h"
#include "com_assert.h"
#include <stdbool.h>

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
    FW_PRINT (FW_INFO, "com_timing_test");

    g_assertion_counter = 0;
    uint32_t bfn1 = BFN_TIME (0xff, 4);
    uint32_t bfn2 = BFN_TIME (0x7f, 3);

    bool c1 = com_timing_is_bfn1_earlier_bfn2 (bfn1, bfn2);
    bool c2 = com_timing_is_bfn1_earlier_bfn2 (bfn2, bfn1);

    // Take half time into consideration
    RT_ASSERT_EX (c1 == true, "bfn1=0x%x < bfn2=0x%x c1 actual=%d, expected=%d", bfn1, bfn2, c1, true);
    RT_ASSERT_EX (c2 == false, "bfn1=0x%x > bfn2=0x%x c2 actual=%d, expected=%d", bfn1, bfn2, c2, false);

    if (g_assertion_counter)
    {
        FW_PRINT (FW_ERR, "Total asserts: %d", g_assertion_counter);
    }
    return (g_assertion_counter);
}
