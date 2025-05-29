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
#include "com_assert.h"
#include "com_gpdma.h"
#include "com_print.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
extern e_gpdma_tr_width_t com_gpdma_get_trw (uint32_t const idx_ch_gpdma, int const bytes, uint64_t const dst, uint64_t const src);

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct
{
    uint32_t bytes;
    uint32_t gpdma_idx;
    uint64_t dst;
    uint64_t src;
    e_gpdma_tr_width_t e_tr_width;
} gpdma_trw_info_test_t;

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
// clang-format off
static gpdma_trw_info_test_t gpdma_trw_info_test[] = {
    {64 * 1024, e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_128},    // 0
    {64,        e_GPDMA_RCS_1, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_128},    // 1
    {32,        e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_128},    // 2
    {16,        e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_128},    // 3
    {8,         e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_64},     // 4
    {4,         e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_32},     // 5
    {2,         e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_16},     // 6
    {1,         e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_8},      // 7
    {123,       e_GPDMA_RCS_0, 0x10000008, 0x00000008, e_GPDMA_TR_WIDTH_8},      // 8

	{64,        e_GPDMA_RCS_1, 0x10000001, 0x00000008, e_GPDMA_TR_WIDTH_8},      // 9
	{64,        e_GPDMA_RCS_1, 0x10000002, 0x00000008, e_GPDMA_TR_WIDTH_8},      // 10
	{64,        e_GPDMA_RCS_1, 0x10000003, 0x00000008, e_GPDMA_TR_WIDTH_8},      // 11
	{64,        e_GPDMA_RCS_1, 0x10000004, 0x00000008, e_GPDMA_TR_WIDTH_128},    // 12

	{64,        e_GPDMA_RCS_1, 0x10000008, 0x00000001, e_GPDMA_TR_WIDTH_8},      // 13
	{64,        e_GPDMA_RCS_1, 0x10000008, 0x00000002, e_GPDMA_TR_WIDTH_8},      // 14
	{64,        e_GPDMA_RCS_1, 0x10000008, 0x00000003, e_GPDMA_TR_WIDTH_8},      // 15
	{64,        e_GPDMA_RCS_1, 0x10000008, 0x00000004, e_GPDMA_TR_WIDTH_128},    // 16

#if HAVE_MEM_FB_GPDMA
    {64 * 1024, e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_512}, // 17
    {64,        e_GPDMA_MEMFB0_1, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_512}, // 18
    {32,        e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_256}, // 19
    {16,        e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_128}, // 20
    {8,         e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_64},  // 21
    {4,         e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_32},  // 22
    {2,         e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_16},  // 23
    {1,         e_GPDMA_MEMFB1_3, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_8},   // 24
    {123,       e_GPDMA_MEMFB0_0, 0x00000008, 0x00000008, e_GPDMA_TR_WIDTH_8},   // 25
#endif // HAVE_MEM_FB_GPDMA
};
// clang-format on

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void gpdma_test_trw ();

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void gpdma_test_trw ()
{
    for (uint32_t idx = 0; idx < sizeof (gpdma_trw_info_test) / sizeof (gpdma_trw_info_test_t); idx++)
    {
        gpdma_trw_info_test_t const *const p_trw_test = &gpdma_trw_info_test[idx];
        e_gpdma_tr_width_t const trw = com_gpdma_get_trw (p_trw_test->gpdma_idx, p_trw_test->bytes, p_trw_test->dst, p_trw_test->src);
        uint32_t const trw_expected = U32 (p_trw_test->e_tr_width);
        uint32_t const trw_actual = U32 (trw);
        RT_ASSERT_EX (trw_expected == trw_actual, "GPDMA idx %d, trw actual=0x%x, expected=0x%x", idx, trw_actual, trw_expected);
    }
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    g_assertion_counter = 0;

    gpdma_test_trw ();

    if (g_assertion_counter)
    {
        FW_PRINT (FW_WARN, "GPDMA total test fail: %d", g_assertion_counter);
        return -1;
    }

    FW_PRINT (FW_INFO, "GPDMA test PASSED");
    return 0;
}
