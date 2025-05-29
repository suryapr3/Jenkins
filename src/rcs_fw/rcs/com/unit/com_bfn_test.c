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

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_bfn.h"
#include "com_print.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BFN_983_CNTL_TOTAL  0x960000
#define TEST_BFN_1474_CNTL_TOTAL 0xE10000

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct
{
    com_bfn_time_t bfn_main;
    com_bfn_time_t bfn_rmt;
    com_bfn_time_t expected;
} bfn_time_diff_test_t;

typedef struct
{
    com_bfn_time_t base_time;
    com_bfn_time_t offset;
    com_bfn_time_t new_time;
} bfn_addsub_offset_test_t;

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

static bfn_time_diff_test_t time_diff_983_test[] = {
    // main                                    remote                                 expected
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 0
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x00008a, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFF}}, // 1
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x000086, .FRAME_P0 = 0x00}, {.OFFSET = 0x000002, .FRAME_P0 = 0x00}}, // 2
    {{.OFFSET = 0x95FFFE, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x95FFFD, .FRAME_P0 = 0xFF}}, // 3
    {{.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0x00}, {.OFFSET = 0x000003, .FRAME_P0 = 0x00}}, // 4
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 5
    {{.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFF}}, // 6
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000002, .FRAME_P0 = 0x00}}, // 7
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x89}, {.OFFSET = 0x000000, .FRAME_P0 = 0x88}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 8
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x88}, {.OFFSET = 0x000000, .FRAME_P0 = 0x89}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFF}}, // 9
    {{.OFFSET = 0x000000, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFE}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 10
    {{.OFFSET = 0x000000, .FRAME_P0 = 0xFE}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFF}}, // 11
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x88}, {.OFFSET = 0x00008A, .FRAME_P0 = 0x8A}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFD}}, // 12
    {{.OFFSET = 0x00008A, .FRAME_P0 = 0x8A}, {.OFFSET = 0x000088, .FRAME_P0 = 0x88}, {.OFFSET = 0x000002, .FRAME_P0 = 0x02}}, // 13
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x88}, {.OFFSET = 0x000088, .FRAME_P0 = 0x74}, {.OFFSET = 0x000000, .FRAME_P0 = 0x14}}, // 14
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x74}, {.OFFSET = 0x000088, .FRAME_P0 = 0x88}, {.OFFSET = 0x000000, .FRAME_P0 = 0xEC}}, // 15
    {{.OFFSET = 0x000002, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0xFF}}, // 16
    {{.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000002, .FRAME_P0 = 0x00}, {.OFFSET = 0x95ffff, .FRAME_P0 = 0x00}}, // 17
    {{.OFFSET = 0x000002, .FRAME_P0 = 0x02}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}}, // 18
    {{.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000002, .FRAME_P0 = 0x02}, {.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFE}}, // 19
};

static bfn_time_diff_test_t time_diff_1474_test[] = {
    // main                                    remote                                 expected
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 0
    {{.OFFSET = 0x000088, .FRAME_P0 = 0x00}, {.OFFSET = 0x00008a, .FRAME_P0 = 0x00}, {.OFFSET = 0xE0FFFE, .FRAME_P0 = 0xFF}}, // 1
};

static bfn_addsub_offset_test_t bfn_add_offset_983_test[] = {
    // base_time                     	      offset                                  new time
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 0
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}}, // 1
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}}, // 2
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 3
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x02}}, // 4
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000002, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}}, // 5
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 6
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFE}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 7
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x02}}, // 8
    {{.OFFSET = 0x95FFF0, .FRAME_P0 = 0x06}, {.OFFSET = 0x95FFF0, .FRAME_P0 = 0x01}, {.OFFSET = 0x95FFE0, .FRAME_P0 = 0x08}}, // 9
};

static bfn_addsub_offset_test_t bfn_add_offset_1474_test[] = {
    // base_time                     	      offset                                  new time
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 0
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x960000, .FRAME_P0 = 0x00}}, // 1
    {{.OFFSET = 0xE0FFFF, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 2
    {{.OFFSET = 0x95FFF0, .FRAME_P0 = 0x06}, {.OFFSET = 0x95FFF0, .FRAME_P0 = 0x01}, {.OFFSET = 0x4AFFE0, .FRAME_P0 = 0x08}}, // 4
};

static bfn_addsub_offset_test_t bfn_sub_offset_983_test[] = {
    // base_time                     	      offset                                  new time
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFF}}, // 0
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}}, // 1
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFF, .FRAME_P0 = 0x00}}, // 2
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0x00}}, // 3
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 4
    {{.OFFSET = 0x95FFFF, .FRAME_P0 = 0xFF}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x95FFFE, .FRAME_P0 = 0xFE}}, // 5
    {{.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x00}}, // 6
    {{.OFFSET = 0x95FFF0, .FRAME_P0 = 0x06}, {.OFFSET = 0x95FFF0, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x05}}, // 7
};

static bfn_addsub_offset_test_t bfn_sub_offset_1474_test[] = {
    // base_time                     	      offset                                  new time
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0xFF}}, // 0
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x00}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0xE0FFFF, .FRAME_P0 = 0xFF}}, // 1
    {{.OFFSET = 0x000000, .FRAME_P0 = 0x01}, {.OFFSET = 0x000001, .FRAME_P0 = 0x00}, {.OFFSET = 0xE0FFFF, .FRAME_P0 = 0x00}}, // 2
    {{.OFFSET = 0xE0FFFF, .FRAME_P0 = 0x01}, {.OFFSET = 0xE0FFFF, .FRAME_P0 = 0x00}, {.OFFSET = 0x000000, .FRAME_P0 = 0x01}}, // 3
    {{.OFFSET = 0x95FFF0, .FRAME_P0 = 0x06}, {.OFFSET = 0x95FFF0, .FRAME_P0 = 0x01}, {.OFFSET = 0x000000, .FRAME_P0 = 0x05}}, // 4
};

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern com_bfn_time_t com_bfn_get_time_diff (com_bfn_time_t const time_main, com_bfn_time_t const time_remote);
extern void com_bfn_set_clk_sel (e_sys_clk_t const drf_sel);

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void bfn_test_clk_sel ();                                   // test bfn_ten ms set accordingly
static void bfn_test_add_time (e_sys_clk_t const bfn_clk_sel);     // test bfn add time or offset
static void bfn_test_diff_pre_inc (e_sys_clk_t const bfn_clk_sel); // test bfn time diff and pre_inc

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void bfn_test_clk_sel ()
{
    extern uint32_t g_bfn_cntl_total;

    com_bfn_set_clk_sel (e_CLK_983M);
    RT_ASSERT (g_bfn_cntl_total == TEST_BFN_983_CNTL_TOTAL);

    com_bfn_set_clk_sel (e_CLK_1474M);
    RT_ASSERT (g_bfn_cntl_total == TEST_BFN_1474_CNTL_TOTAL);
}

static void bfn_test_add_time (e_sys_clk_t const bfn_clk_sel)
{
    com_bfn_set_clk_sel (bfn_clk_sel);
    bfn_addsub_offset_test_t *p_tbl_test = bfn_add_offset_983_test;
    uint32_t arr_sz = sizeof (bfn_add_offset_983_test) / sizeof (bfn_addsub_offset_test_t);

    if (bfn_clk_sel == e_CLK_1474M)
    {
        p_tbl_test = bfn_add_offset_1474_test;
        arr_sz = sizeof (bfn_add_offset_1474_test) / sizeof (bfn_addsub_offset_test_t);
    }

    FW_PRINT (FW_INFO, "Test: BFN time add test, clk sel = %d", ENUM2U32 (bfn_clk_sel));
    for (int idx = 0; idx < arr_sz; idx++)
    {
        uint32_t const new_time_expected = p_tbl_test[idx].new_time.value;
        uint32_t const new_time_actual = com_bfn_add_time (p_tbl_test[idx].base_time.value, p_tbl_test[idx].offset.value);

        RT_ASSERT_EX (new_time_actual == new_time_expected, "BFN add idx %d, base=0x%x, offset=0x%x, actual=0x%x, expected=0x%x", idx,
                      p_tbl_test[idx].base_time.value, p_tbl_test[idx].offset.value, new_time_actual, new_time_expected);
    }
}

static void bfn_test_sub_time (e_sys_clk_t const bfn_clk_sel)
{
    com_bfn_set_clk_sel (bfn_clk_sel);
    bfn_addsub_offset_test_t *p_tbl_test = bfn_sub_offset_983_test;
    uint32_t arr_sz = sizeof (bfn_sub_offset_983_test) / sizeof (bfn_addsub_offset_test_t);

    if (bfn_clk_sel == e_CLK_1474M)
    {
        p_tbl_test = bfn_sub_offset_1474_test;
        arr_sz = sizeof (bfn_sub_offset_1474_test) / sizeof (bfn_addsub_offset_test_t);
    }

    FW_PRINT (FW_INFO, "Test: BFN time sub test, clk sel = %d", ENUM2U32 (bfn_clk_sel));
    for (int idx = 0; idx < arr_sz; idx++)
    {
        uint32_t const new_time_expected = p_tbl_test[idx].new_time.value;
        uint32_t const new_time_actual = com_bfn_sub_time (p_tbl_test[idx].base_time.value, p_tbl_test[idx].offset.value);

        RT_ASSERT_EX (new_time_actual == new_time_expected, "BFN sub idx %d, base=0x%x, offset=0x%x, actual=0x%x, expected=0x%x", idx,
                      p_tbl_test[idx].base_time.value, p_tbl_test[idx].offset.value, new_time_actual, new_time_expected);
    }
}

static void bfn_test_diff_pre_inc (e_sys_clk_t const bfn_clk_sel)
{
    com_bfn_set_clk_sel (bfn_clk_sel);
    bfn_time_diff_test_t *p_tbl_test = time_diff_983_test;
    uint32_t arr_sz = sizeof (time_diff_983_test) / sizeof (bfn_time_diff_test_t);

    if (bfn_clk_sel == e_CLK_1474M)
    {
        p_tbl_test = time_diff_1474_test;
        arr_sz = sizeof (time_diff_1474_test) / sizeof (bfn_time_diff_test_t);
    }

    FW_PRINT (FW_INFO, "Test: BFN time diff test, clk sel = %d", ENUM2U32 (bfn_clk_sel));
    for (int idx = 0; idx < arr_sz; idx++)
    {
        uint32_t const new_time_expected = p_tbl_test[idx].expected.value;
        com_bfn_time_t const bfn_diff = com_bfn_get_time_diff (p_tbl_test[idx].bfn_main, p_tbl_test[idx].bfn_rmt);

        RT_ASSERT_EX (bfn_diff.FRAME_P0 == p_tbl_test[idx].expected.FRAME_P0, "BFN diff %d, main=0x%x, rmt=0x%x, actual=%d, expected=%d",
                      idx, p_tbl_test[idx].bfn_main.value, p_tbl_test[idx].bfn_rmt.value, bfn_diff.value, new_time_expected);
    }
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    g_assertion_counter = 0;

    bfn_test_clk_sel ();
    bfn_test_add_time (e_CLK_983M);
    bfn_test_add_time (e_CLK_1474M);
    bfn_test_diff_pre_inc (e_CLK_983M);
    bfn_test_diff_pre_inc (e_CLK_1474M);
    bfn_test_sub_time (e_CLK_983M);
    bfn_test_sub_time (e_CLK_1474M);

    if (g_assertion_counter)
    {
        FW_PRINT (FW_WARN, "BFN total test fail: %d", g_assertion_counter);
        return -1;
    }

    FW_PRINT (FW_INFO, "BFN test PASSED");
    return 0;
}
