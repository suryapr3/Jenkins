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
 * @file    ax_v2d_quad_ch0_trigger.c
 * @brief   Trigger the delayed start of for the Ch0 of given quad along with start the corresponding vex cores.
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
#include "ve32_cell.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32
#define VEX_DMEM_OFFSET 0x10
#define V2D_PER_QUAD    2
#define VEX_PER_V2D 4

#define VEX_BASE(vex_num)   VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE))

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

const int g_v2d_instance_in_quad[][V2D_PER_QUAD] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7}
};

const int g_vex_instance_in_v2d[][VEX_PER_V2D] = {
    {0, 1, 8, 9},
    {2, 3, 10, 11},
    {4, 5, 12, 13},
    {6, 7, 14, 15}
};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
void configure_v2d_force_bfn(int);

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    uint32_t v2d_base = 0, vex_base = 0, quad_instance = 0, v2d_num = 0;
    int lc = 0, vex_num = 0;

    /*BFNE start reg value to be configured with forced trigger value*/
    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};
    bfne_start_reg.value = 0xFFFFFFFF;

    /*To start the VEX core*/
    ve32_cell_mem_control_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_MEM_CONTROL_START_BF_MSK | VE32_CELL_MEM_CONTROL_RUN_BF_MSK};

    quad_instance = rsm_buf[0];

    /*BFN configuration*/
    configure_v2d_force_bfn(quad_instance);

    switch (quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*Take only even V2D*/
    v2d_num = g_v2d_instance_in_quad[quad_instance][0];

    /*start the VEX cores*/
    /*First start the RX core then the Tx Core*/
    for (lc = 1; lc >= 0; lc--)
    {
        vex_num = g_vex_instance_in_v2d[v2d_num][lc];
        vex_base = VEX_BASE(vex_num);
        *(VE32_CELL_MEM_CONTROL_REG(vex_base)) = ve32_cell_mem_control_reg;
    }

    /*Trigger the FORCED BFN START*/
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    return (0);
}

/**
 * @brief           Function for configuring the BFN registers
 * @param [in]      quad instance
 * @return          none
 */
void configure_v2d_force_bfn(int quad_instance)
{
    int v2d_base = 0, lc = 0;

    bfn_csr_general_csr_reg_t bfn_csr_general_csr_reg = {.value = BFN_CSR_GENERAL_CSR_DEFAULT};

    /*Enabling the BFN events*/
    bfn_csr_bfne_config_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CONFIG_DEFAULT};
    bfne_config_reg.ENABLE = 1;

    bfn_csr_start_lm_reg_t bfn_csr_start_lm_reg = {.value = BFN_CSR_START_LM_MATCH_EN_BF_MSK};

    quad_instance = rsm_buf[0];

    switch (quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*Enabling the BFN start Enable*/
    bfn_csr_general_csr_reg= *(BFN_CSR_GENERAL_CSR_REG(v2d_base));
    bfn_csr_general_csr_reg.value |= BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
    *(BFN_CSR_GENERAL_CSR_REG(v2d_base)) = bfn_csr_general_csr_reg;

    /*Enabling the BFN EVENT in the BFN config*/
    *(BFN_CSR_BFNE_CONFIG0_REG(v2d_base)) = bfne_config_reg;

    /*Writing the LM_START values with the required match values
     *for all the required channels*/
    bfn_csr_start_lm_reg.MATCH_VALUE = rsm_buf[1];

    for (lc = 0; lc < V2D_PER_QUAD; lc++)
    {
        v2d_base = v2d_base + (lc * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE));
        *(BFN_CSR_START_LM0_REG(v2d_base)) = bfn_csr_start_lm_reg;
        *(BFN_CSR_START_LM1_REG(v2d_base)) = bfn_csr_start_lm_reg;
    }
}
// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
