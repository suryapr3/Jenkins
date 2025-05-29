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
 * @file    tx_v2d_tx_Ch0_Ch1_trigger.c
 * @brief   Will write the BFN registers of V2D along with writing to a specific VEX
 *          memory location, which will act as a trigger.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_event.h"
#include "com_shared_memory.h"
#include "rcs_gpreg.h"

#include "bfn_csr.h"
#include "av2d_csr.h"
#include "nsip_hbi.h"
#include "ve32_bp_config_dmem.h"
#include "av2d_axi4.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32
#define VEX_DMEM_OFFSET 0x10

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile uint32_t rsm_buf[TEST_BUFF_SIZE] __attribute__((section(".sram.reserved")));

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    uint32_t v2d_num = 0, vex_num1 = 0, vex_num2 = 0, v2d_base = 0, vex_base = 0;

    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};
    bfne_start_reg.value = 0xFFFFFFFF;

    bfn_csr_general_csr_reg_t bfn_csr_general_csr_reg = {.value = BFN_CSR_GENERAL_CSR_DEFAULT};

    bfn_csr_bfne_config_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CONFIG_DEFAULT};
    bfne_config_reg.ENABLE = 1;

    bfn_csr_start_lm_reg_t bfn_csr_start_lm_reg = {.value = BFN_CSR_START_LM_MATCH_EN_BF_MSK};

    ve32_bp_config_dmem_mem_first_reg_t vex_mem_reg = {.value = VE32_BP_CONFIG_DMEM_MEM_FIRST_DEFAULT};
    vex_mem_reg.value = 0x1;

    vex_num1 = rsm_buf[0];
    vex_num2 = rsm_buf[1];
    v2d_num = rsm_buf[2];

    switch (v2d_num)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D1_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D3_BFN_CSR_BASE;
        break;
    case 4:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 5:
        v2d_base = V2D5_BFN_CSR_BASE;
        break;
    case 6:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    case 7:
        v2d_base = V2D7_BFN_CSR_BASE;
        break;
    }

    /*Trigger BFN*/
    bfn_csr_general_csr_reg = *(BFN_CSR_GENERAL_CSR_REG(v2d_base));
    bfn_csr_general_csr_reg.value |= BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
    *(BFN_CSR_GENERAL_CSR_REG(v2d_base)) = bfn_csr_general_csr_reg;

    /*Enabling the BFN EVENT in the BFN config*/
    *(BFN_CSR_BFNE_CONFIG0_REG(v2d_base)) = bfne_config_reg;

    /*Writing the LM_START values with the required match values*/
    bfn_csr_start_lm_reg.MATCH_VALUE = 0;

    *(BFN_CSR_START_LM0_REG(v2d_base)) = bfn_csr_start_lm_reg;
    *(BFN_CSR_START_LM1_REG(v2d_base)) = bfn_csr_start_lm_reg;

    /* For the first Channel*/
    /*Indicating VEX to start continuous transfer*/
    vex_base = VEXABC0_DMEM_VE32_BP_CONFIG_BASE + (0x40000 * vex_num1);
    *(VE32_BP_CONFIG_DMEM_MEM_FIRST_REG(vex_base + VEX_DMEM_OFFSET)) = vex_mem_reg;

    /* For the second Channel*/
    /*Indicating VEX to start continuous transfer*/
    vex_base = VEXABC0_DMEM_VE32_BP_CONFIG_BASE + (0x40000 * vex_num2);
    *(VE32_BP_CONFIG_DMEM_MEM_FIRST_REG(vex_base + VEX_DMEM_OFFSET)) = vex_mem_reg;

    /*Trigger the FORCED BFN START*/
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    return (0);
}

// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
