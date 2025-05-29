/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unlfbess the License provides otherwise, you may not use, modify,
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
 * @file    com_memfb.c
 * @brief   memfb common functions.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#if CPU_AX
// todo: MEM module has to rethink how to implement.

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_definitions.h"
#include "com_memory.h"
#include "com_abc_mem_info.h"
#include "com_assert.h"
#include "com_gpdma.h"
#include "mem_cap_wrap.h"
#include "mem_cap_cfg.h"
#include "mem_fb.h"
#include "nsip_hbi.h"
#include "test.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define MAX_MEM_REGION (0x8)

#define MEM_CAP_INIT_MODE_LFSR  (0x0)
#define MEM_CAP_INIT_MODE_FIXED (0x1)
#define MEM_CAP_INIT_MODE_ADDR  (0x2)
#define MEM_CAP_INIT_MODE_INCR  (0x3)
#define MEM_CAP_INIT_MODE_DECR  (0x4)

#define MEM_CAP_INIT_START (MEM_CAP_MEM_INIT_RAM_INIT_START_BF_MSK | MEM_CAP_INIT_MODE_FIXED) // use fixed pattern

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct
{
    e_gpdma_memfb_t const gpdma;
    nsip_hbi_t *const p_nsip_hbi;
} com_memfb_gpdma_inst_t;
/*
typedef struct
{
    uint8_t *const p_sram_cap;
    uint8_t *const p_sram_fbr;
    mem_fb_t *const p_memfb_cfg;
    mem_cap_wrap_t *const p_mem_cap;
    test_t *const p_test_cfg;
    mem_cap_cfg_t *const p_cap_cfg;
    com_memfb_gpdma_inst_t const stream[MAX_GPDMA_PER_MEMFB_INST];
} com_mem_inst_t;
*/
/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
/*
PRIVATE com_mem_inst_t const com_mem_inst[] = {
    {U8_P (COM_MEMFB_MEM_CAP0_BASE),
     U8_P (COM_MEMFB_MEM_FB0_BASE),
     MEM_FB0_FB,
     MEM_CAP0_CAP_TOP,
     TEST0_TEST_TOP,
     MEM_CFG0_CFG_TOP,
     {{E_GPDMA_MEM0_FB_0, MEM0_FB_NSIP_HBI_0_REG}, {E_GPDMA_MEM0_FB_1, MEM0_FB_NSIP_HBI_1_REG}}},

    {U8_P (COM_MEMFB_MEM_CAP1_BASE),
     U8_P (COM_MEMFB_MEM_FB1_BASE),
     MEM_FB1_FB,
     MEM_CAP1_CAP_TOP,
     TEST1_TEST_TOP,
     MEM_CFG1_CFG_TOP,
     {{E_GPDMA_MEM1_FB_0, MEM1_FB_NSIP_HBI_0_REG}, {E_GPDMA_MEM1_FB_1, MEM1_FB_NSIP_HBI_1_REG}}},
};
*/

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
 * @brief           Initialize mem_fb. Call only once during boot
 * @param [in]      none.
 * @return          none.
 * -------------------------------------------------------------------------------------------------------------------*/
void com_memory_init ()
{
    /*
        uint32_t idx_ram = 0;
        volatile mem_cap_mem_init_ram_reg_t mem_cap_init = {.value = 0};

        for (uint32_t idx_mem=0; idx_mem<MAX_MEM_INST; idx_mem++)
        {
            com_mem_inst[idx_mem].p_memfb_cfg->ENABLE.value = 1;
            for (idx_ram=0; idx_ram<MAX_MEM_REGION; idx_ram++)
            {
                com_mem_inst[idx_mem].p_mem_cap_cfg->INIT_RAM[idx_ram].value = MEM_CAP_INIT_START;
            }

            for (idx_ram=0; idx_ram<MAX_MEM_REGION; idx_ram++)
            {
                do
                {
                    mem_cap_init = com_mem_inst[idx_mem].p_mem_cap_cfg->INIT_RAM[idx_ram];
                }
                while (! mem_cap_init.INIT_DONE);
            }
        }
    */
}

#endif // CPU_AX
