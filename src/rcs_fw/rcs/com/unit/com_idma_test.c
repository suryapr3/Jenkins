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

#include <string.h>
#include <xtensa/xtruntime.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_idma.h"
#include "com_print.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define IDMA_TEST_BUFF_SIZE 4

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static idma_desc2d_t g_idma_desc2d_test __attribute__ ((__aligned__ (8))) __attribute__ ((section (".dram0.data")));
static uint8_t buff_src[IDMA_TEST_BUFF_SIZE] __attribute__ ((section (".dram0.data")));

static uint32_t g_test_val = 0;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void idma_test_fill_1d_desc (); // test fill 1d descriptors
static void idma_test_fill_2d_desc (); // test fill 1d descriptors
static void idma_test_1d ();           // leagcy DMA test
static void idma_test_1d_task ();      // this will test call back as well
static void imda_test_desc_1d ();      // this will test call back as well
static void imda_test_broadcast ();    // this will test broadcast
static void imda_test_last_err ();     // test last error

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void idma_test_fill_1d_desc ()
{
    uint32_t const desc_cnt = 3;
    idma_desc1d_t const desc1d_test[desc_cnt];

    com_idma_fill_ctrl ((idma_desc1d_t *)desc1d_test, desc_cnt, e_IDMA_DESC_TYPE_1D, NULL);
    for (uint32_t idx = 0; idx < desc_cnt; idx++)
    {
        bool const intr = (idx == desc_cnt - 1) ? 1 : 0;
        RT_ASSERT (desc1d_test[idx].ctrl.DESCRIPTOR == e_IDMA_DESC_TYPE_1D);
        RT_ASSERT (desc1d_test[idx].ctrl.INTR == intr);
        RT_ASSERT (desc1d_test[idx].ctrl.PRIV_DST == 0);
        RT_ASSERT (desc1d_test[idx].ctrl.PRIV_SRC == 0);
        RT_ASSERT (desc1d_test[idx].ctrl.QOS == 0);
        RT_ASSERT (desc1d_test[idx].ctrl.TRIGGER == 0);
        RT_ASSERT (desc1d_test[idx].ctrl.TWAIT == 0);
    }
}

static void idma_test_fill_2d_desc ()
{
    uint32_t const desc_cnt = 3;
    idma_desc2d_t const desc2d_test[desc_cnt];

    com_idma_fill_ctrl ((idma_desc2d_t *)desc2d_test, desc_cnt, e_IDMA_DESC_TYPE_2D, NULL);
    for (uint32_t idx = 0; idx < desc_cnt; idx++)
    {
        bool const intr = (idx == desc_cnt - 1) ? 1 : 0;
        RT_ASSERT (desc2d_test[idx].ctrl.DESCRIPTOR == e_IDMA_DESC_TYPE_2D);
        RT_ASSERT (desc2d_test[idx].ctrl.INTR == intr);
        RT_ASSERT (desc2d_test[idx].ctrl.PRIV_DST == 0);
        RT_ASSERT (desc2d_test[idx].ctrl.PRIV_SRC == 0);
        RT_ASSERT (desc2d_test[idx].ctrl.QOS == 0);
        RT_ASSERT (desc2d_test[idx].ctrl.TRIGGER == 0);
        RT_ASSERT (desc2d_test[idx].ctrl.TWAIT == 0);
    }
}

static void idma_test_1d ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE] = {0x00};

    FW_PRINT (FW_INFO, "Test: idma 1D test");
    memset (buff_src, 0xFF, IDMA_TEST_BUFF_SIZE);
    com_idma_trans_1d (buff_b, buff_src, IDMA_TEST_BUFF_SIZE, NULL);
    uint32_t idma_err = com_idma_wait_done ();
    RT_ASSERT (idma_err == ERR_IDMA_OK);
    RT_ASSERT (memcmp (buff_src, buff_b, IDMA_TEST_BUFF_SIZE) == 0);
}

static void idma_cb_test (void *arg)
{
    g_test_val = *(uint32_t *)arg;
}

static void idma_test_1d_task ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE] = {0x00};
    g_test_val = 0;

    FW_PRINT (FW_INFO, "Test: idma 1D with interrupt");
    memset (buff_src, 0xFF, IDMA_TEST_BUFF_SIZE);
    com_idma_trans_1d (buff_b, buff_src, IDMA_TEST_BUFF_SIZE, NULL);
    uint32_t idma_stat = com_idma_wait_done ();
    RT_ASSERT (idma_stat == ERR_IDMA_OK);
    RT_ASSERT (memcmp (buff_src, buff_b, IDMA_TEST_BUFF_SIZE) == 0);
    RT_ASSERT (g_test_val == 0);

    uint32_t test_var = 123;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    memset (buff_b, 0, IDMA_TEST_BUFF_SIZE);
    com_idma_trans_1d (buff_b, buff_src, 4, &task_test);
    uint32_t idma_err = com_idma_wait_done ();
    RT_ASSERT (idma_err == ERR_IDMA_OK);
    RT_ASSERT (memcmp (buff_src, buff_b, IDMA_TEST_BUFF_SIZE) == 0);
    RT_ASSERT (g_test_val == 123);
}

static void imda_test_desc_1d ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE] = {0x00};
    uint32_t test_var = 456;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    idma_desc1d_t *p_desc_1d = (idma_desc1d_t *)&g_idma_desc2d_test;
    g_test_val = 0;

    FW_PRINT (FW_INFO, "Test: idma 1D using descriptor with interrupt");
    memset (buff_src, 0xFF, IDMA_TEST_BUFF_SIZE);
    com_idma_fill_ctrl (p_desc_1d, 1, e_IDMA_DESC_TYPE_1D, NULL);
    p_desc_1d->src = U32 (buff_src);
    p_desc_1d->dst = U32 (buff_b);
    p_desc_1d->row_bytes = IDMA_TEST_BUFF_SIZE;
    com_idma_trans_desc (p_desc_1d, 1, &task_test);
    uint32_t idma_err = com_idma_wait_done ();
    RT_ASSERT (idma_err == ERR_IDMA_OK);
    RT_ASSERT (memcmp (buff_src, buff_b, IDMA_TEST_BUFF_SIZE) == 0);
    RT_ASSERT (g_test_val == 456);
}

static void imda_test_broadcast ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE * 8] = {0x00}; // 8 rows
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE; idx++) buff_src[idx] = idx;

    FW_PRINT (FW_INFO, "Test: idma broadcast (2D) test");
    com_idma_broadcast (buff_b, buff_src, 4, 8, 4, NULL);
    uint32_t idma_err = com_idma_wait_done ();
    RT_ASSERT (idma_err == ERR_IDMA_OK);

    for (int row = 0; row < 8; row++) RT_ASSERT (memcmp (buff_src, &buff_b[row * IDMA_TEST_BUFF_SIZE], IDMA_TEST_BUFF_SIZE) == 0);
}

static void idma_memcpy_test ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE] = {0x00};

    FW_PRINT (FW_INFO, "Test: idma memcpy");
    uint32_t idma_err = com_idma_memcpy (buff_b, buff_src, IDMA_TEST_BUFF_SIZE);
    RT_ASSERT (idma_err == ERR_IDMA_OK);
    RT_ASSERT (memcmp (buff_src, buff_b, IDMA_TEST_BUFF_SIZE) == 0);
}

static void imda_test_last_err ()
{
    uint8_t buff_b[IDMA_TEST_BUFF_SIZE] = {0x00};
    idma_desc1d_t bad_desc = {0};

    FW_PRINT (FW_NOTE, "--- Expected errors follow.");
    FW_PRINT (FW_INFO, "Test: idma negative test, error means test pass");
    com_idma_fill_ctrl (&bad_desc, 1, e_IDMA_DESC_TYPE_1D, NULL);
    com_idma_trans_desc (&bad_desc, 1, NULL);
    // coverity does not like this negative test, bypass coverity
    // coverity[check_return]
    com_idma_wait_done ();
    uint32_t idma_err = com_idma_get_last_errcode ();
    RT_ASSERT (idma_err != ERR_IDMA_OK);
    idma_err = com_idma_get_last_errcode (); // Test read to clear (cleared on previous read)
    RT_ASSERT (idma_err == ERR_IDMA_OK);
    FW_PRINT (FW_NOTE, "--- End of expected errors.");
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    g_assertion_counter = 0;
    com_idma_init ();
    idma_test_fill_1d_desc ();
    idma_test_fill_2d_desc ();
    idma_test_1d ();
    idma_test_1d_task ();
    imda_test_desc_1d ();
    imda_test_broadcast ();
    idma_memcpy_test ();
    imda_test_last_err ();

    if (g_assertion_counter)
    {
        FW_PRINT (FW_WARN, "IDMA total test fail: %d", g_assertion_counter);
        return -1;
    }

    FW_PRINT (FW_INFO, "IDMA test PASSED");
    return 0;
}
