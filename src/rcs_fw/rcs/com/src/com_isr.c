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
 * @file    com_isr.c
 * @brief   Common functions for interrupt handling.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_isr.h"
#include "com_print.h"
#include "rcs_gpreg.h"
#include "com_msgs_enum.h"
#include "com_error.h"
#include <xtensa/core-macros.h>
#include <xtensa/xtruntime.h>
#if EVENT_USE_CPU_TIMER == 0
#include "int_cfg.h"
#endif

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define EDGE_REG0                  (1)
#define EDGE_REG1                  (2)
#define EDGE_REG2                  (3)
#define REG3                       (3)
#define REG4                       (4)
#define REG5                       (5)
#define REG10                      (10)
#define REG13                      (13)
#define NUM_OF_AGGRTR_IRQ_GRP      (18)
#define NUM_OF_DIRECT_IRQ_GRP      (14)
#define NUM_OF_REG3_INTRPT         (28)
#define NUM_OF_REG4_INTRPT         (10)
#define NUM_OF_REG5_INTRPT         (26)
#define NUM_OF_REG10_INTRPT        (16)
#define NUM_OF_REG13_INTRPT        (20)
#define NUM_OF_EDGE_IRQ_REG_INTRPT (32)
#define LEVEL_IRQ_BIT_POSN         (5)
#define GROUP_OF_BITS              (0x1f)
#define LEVEL_IRQ_BITS             (10)
#define EDGE_IRQ_BITS              (15)
#define EDGE_IRQ_REG_BITS          (0x3)

#if CPU_AX
#define GPREG_CORE_BASE RCS_GPREG_CORE0_BASE
#elif CPU_RX
#define GPREG_CORE_BASE RCS_GPREG_CORE1_BASE
#elif CPU_TX
#define GPREG_CORE_BASE RCS_GPREG_CORE2_BASE
#elif CPU_CAL
#define GPREG_CORE_BASE RCS_GPREG_CORE3_BASE
#endif
#define INIT 0

// clang-format off
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
irq_map_t direct_irq_config[NUM_OF_DIRECT_IRQ_GRP] = {
    {.cpu_irq = 0},
    {.cpu_irq = 1},
    {.cpu_irq = 2},
    {.cpu_irq = 3},
    {.cpu_irq = 4},
    {.cpu_irq = 5},
    {.cpu_irq = 6},
    {.cpu_irq = 7},
    {.cpu_irq = 28},
    {.cpu_irq = 29},
    {.cpu_irq = 30},
    {.cpu_irq = 31}, //todo:This needs update in the spreadsheet.
    {.cpu_irq = 14},
    {.cpu_irq = 15},
};

irq_num_handler_map_t aggr_irq_config[NUM_OF_AGGRTR_IRQ_GRP] = {
    {.cpu_irq = 16, .irq_handler = NULL, .reg_idx = 0, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 17, .irq_handler = NULL, .reg_idx = 1, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 18, .irq_handler = NULL, .reg_idx = 2, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 19, .irq_handler = NULL, .reg_idx = 3, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 20, .irq_handler = NULL, .reg_idx = 4, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 21, .irq_handler = NULL, .reg_idx = 5, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 22, .irq_handler = NULL, .reg_idx = 6, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 23, .irq_handler = NULL, .reg_idx = 7, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 24, .irq_handler = NULL, .reg_idx = 8, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 25, .irq_handler = NULL, .reg_idx = 9, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 8,  .irq_handler = NULL, .reg_idx = 10, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 9,  .irq_handler = NULL, .reg_idx = 11, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 10, .irq_handler = NULL, .reg_idx = 12, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 11, .irq_handler = NULL, .reg_idx = 13, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 12, .irq_handler = NULL, .reg_idx = 14, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 13, .irq_handler = NULL, .reg_idx = 15, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 26, .irq_handler = NULL, .reg_idx = 16, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
    {.cpu_irq = 27, .irq_handler = NULL, .reg_idx = 17, .mask_reg = INT_CFG_GPREG_LVL_IRQ_MASK_DEFAULT, .data = (void *)0},
};

irq_reg_handler_map_t reg3_irq_config[NUM_OF_REG3_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
};

irq_reg_handler_map_t reg4_irq_config[NUM_OF_REG4_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
};
irq_reg_handler_map_t reg5_irq_config[NUM_OF_REG5_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
};
irq_reg_handler_map_t reg10_irq_config[NUM_OF_REG10_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
	{.irq_handler = NULL, .data = (void *)0},
};
irq_reg_handler_map_t reg13_irq_config[NUM_OF_REG13_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
};

// Edge interrupt table
// Note: The EDGE IRQ handlers will be grouped in future after we understand the nature of these interrupts.
irq_edge_handler_map_t edge_irq_reg0_handler_map[NUM_OF_EDGE_IRQ_REG_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
};
irq_edge_handler_map_t edge_irq_reg1_handler_map[NUM_OF_EDGE_IRQ_REG_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
};
irq_edge_handler_map_t edge_irq_reg2_handler_map[NUM_OF_EDGE_IRQ_REG_INTRPT] = {
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL, .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},
    {.irq_handler = NULL,  .data = (void *)0},

};
// clang-format on

typedef struct
{
    uint32_t reg_no;
    irq_reg_handler_map_t *p_irq_data;
    int_cfg_gpreg_lvl_irq_stat_reg_t *irq_stat;
} isr_info_t;

isr_info_t reg3_data = {REG3, reg3_irq_config, (INT_CFG3_GPREG_LVL_IRQ_STAT_REG (GPREG_CORE_BASE))};
isr_info_t reg4_data = {REG4, reg4_irq_config, (INT_CFG4_GPREG_LVL_IRQ_STAT_REG (GPREG_CORE_BASE))};
isr_info_t reg5_data = {REG5, reg5_irq_config, (INT_CFG5_GPREG_LVL_IRQ_STAT_REG (GPREG_CORE_BASE))};
isr_info_t reg10_data = {REG10, reg10_irq_config, (INT_CFG10_GPREG_LVL_IRQ_STAT_REG (GPREG_CORE_BASE))};
isr_info_t reg13_data = {REG13, reg13_irq_config, (INT_CFG13_GPREG_LVL_IRQ_STAT_REG (GPREG_CORE_BASE))};

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

/*
 * @brief           Extract register number from the received interrupt number.
 */
static uint32_t com_get_reg (uint32_t int_num)
{
    return ((int_num >> LEVEL_IRQ_BIT_POSN) & GROUP_OF_BITS);
}

/*
 * @brief           Extract bit placing for interrupt masking.
 */
static uint32_t com_get_bit_place (uint32_t int_num)
{
    return (1 << (int_num & GROUP_OF_BITS));
}

/*
 * @brief           Extract register number from the  edge triggered interrupt number.
 */
static uint32_t com_get_edge_reg (uint32_t int_num)
{
    return (int_num >> LEVEL_IRQ_BITS);
}

/*
 * @brief           Second level handler for the registers with unique interrupts
 */
static void com_distinct_handler (void *p_arg)
{
    isr_info_t *p_isr_info = (isr_info_t *)p_arg;
    int_cfg_gpreg_lvl_irq_stat_reg_t stat_reg = *p_isr_info->irq_stat;
    uint32_t i = 0;
    FW_PRINT (FW_INFO, "Inside distinct handler %d, REG=%d", stat_reg.value, p_isr_info->reg_no);
    int_cfg_gpreg_lvl_irq_stat_reg_t irq_stat = {.value = INT_CFG_GPREG_LVL_IRQ_STAT_DEFAULT};
    while (stat_reg.value)
    {
        if (stat_reg.value & 0x1)
        {
            p_isr_info->p_irq_data[i].irq_handler (p_isr_info->p_irq_data[i].data);
            irq_stat.LVL_IRQ_STAT = 0x1 << i;
            *p_isr_info->irq_stat = irq_stat;
        }
        stat_reg.value >>= 0x1;
        i++;
    }
}

/*
 * @brief           Second level handler for Edge triggered interrupts
 */
void com_edge_irq_handler (void *arg)
{
    uint32_t reg_grp = (uint32_t)arg;
    irq_edge_handler_map_t *p_irq_data;
    uint32_t stat_reg;
    uint32_t i;

    if (reg_grp == EDGE_REG0)
    {
        stat_reg = RCS_GPREG_EDG_IRQ_STAT_0_REG->value;
        p_irq_data = &edge_irq_reg0_handler_map[0];
        i = 0;
        while (stat_reg)
        {
            if (stat_reg & 0x1)
            {
                p_irq_data[i].irq_handler (p_irq_data[i].data);
                RCS_GPREG_EDG_IRQ_STAT_0_REG->value = 0x1 << i;
            }
            stat_reg >>= 0x1;
            i++;
        }
    }
    else if (reg_grp == EDGE_REG1)
    {
        stat_reg = RCS_GPREG_EDG_IRQ_STAT_1_REG->value;
        p_irq_data = edge_irq_reg1_handler_map;
        i = 0;
        while (stat_reg)
        {
            if (stat_reg & 0x1)
            {
                p_irq_data[i].irq_handler (p_irq_data[i].data);
                RCS_GPREG_EDG_IRQ_STAT_1_REG->value = 0x1 << i;
            }
            stat_reg >>= 0x1;
            i++;
        }
    }
    else if (reg_grp == EDGE_REG2)
    {
        stat_reg = RCS_GPREG_EDG_IRQ_STAT_2_REG->value;
        p_irq_data = edge_irq_reg2_handler_map;
        i = 0;
        while (stat_reg)
        {
            if (stat_reg & 0x1)
            {
                p_irq_data[i].irq_handler (p_irq_data[i].data);
                RCS_GPREG_EDG_IRQ_STAT_2_REG->value = 0x1 << i;
            }
            stat_reg >>= 0x1;
            i++;
        }
    }
}

/*
 * @brief           Edge IRQ related Info
 */
static void com_edge_irq_info (irq_edge_handler_map_t **p_irq_data, uint32_t edge_irq_reg)
{
    if (edge_irq_reg == EDGE_REG0)
    {
        *p_irq_data = edge_irq_reg0_handler_map;
    }
    else if (edge_irq_reg == EDGE_REG1)
    {
        *p_irq_data = edge_irq_reg1_handler_map;
    }
    else if (edge_irq_reg == EDGE_REG2)
    {
        *p_irq_data = edge_irq_reg2_handler_map;
    }
    else
    {
        FW_PRINT (FW_INFO, "core%u: This EDGE IRQ not supported", RCS_CPU);
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Level IRQ related info
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_lvl_irq_reg_info (irq_reg_handler_map_t **p_irq_data, isr_info_t **p_isr_info, uint32_t regstr_number)
{
    if (regstr_number == REG3)
    {
        *p_irq_data = reg3_irq_config;
        *p_isr_info = &reg3_data;
    }
    else if (regstr_number == REG4)
    {
        *p_irq_data = reg4_irq_config;
        *p_isr_info = &reg4_data;
    }
    else if (regstr_number == REG5)
    {
        *p_irq_data = reg5_irq_config;
        *p_isr_info = &reg5_data;
    }
    else if (regstr_number == REG10)
    {
        *p_irq_data = reg10_irq_config;
        *p_isr_info = &reg10_data;
    }
    else if (regstr_number == REG13)
    {
        *p_irq_data = reg13_irq_config;
        *p_isr_info = &reg13_data;
    }
    else
    {
        FW_PRINT (FW_INFO, "core%u: This IRQ not supported %u", RCS_CPU, regstr_number);
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Store the HW interrupt info into the table
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_store_aggregator_irq_info (uint32_t irq, f_isr_handler_t irq_handler, void *data)
{
    uint32_t regstr_number = com_get_reg (irq);
    if (regstr_number >= NUM_OF_AGGRTR_IRQ_GRP)
    {
        FW_PRINT (FW_ERR, "core%u: This Register number: %u is invalid", RCS_CPU, regstr_number);
    }
    else
    {
        isr_info_t *p_isr_info;
        if ((regstr_number == REG3) || (regstr_number == REG4) || (regstr_number == REG5) || (regstr_number == REG10)
            || (regstr_number == REG13))
        {
            irq_reg_handler_map_t *p_irq_data;
            uint32_t bit_place;
            bit_place = com_get_bit_place (irq);
            uint32_t irq_bit = (irq & 0x1f);
            uint32_t edge_irq_reg = com_get_edge_reg (irq);
            if (edge_irq_reg != 0) // Edge triggered IRQ
            {
                irq_edge_handler_map_t *p_edge_irq_data;

                com_edge_irq_info (&p_edge_irq_data, edge_irq_reg);
                p_edge_irq_data[irq_bit].irq_handler = irq_handler;
                p_edge_irq_data[irq_bit].data = data;
            }
            else // level triggered IRQ
            {
                com_lvl_irq_reg_info (&p_irq_data, &p_isr_info, regstr_number);

                p_irq_data[irq_bit].irq_handler = irq_handler;
                p_irq_data[irq_bit].data = data;
                xtos_set_interrupt_handler (aggr_irq_config[regstr_number].cpu_irq, com_distinct_handler, (void *)p_isr_info, NULL);
            }
        }
        else
        {
            aggr_irq_config[regstr_number].irq_handler = irq_handler;
            aggr_irq_config[regstr_number].data = data;
            xtos_set_interrupt_handler (aggr_irq_config[regstr_number].cpu_irq, (xtos_handler)aggr_irq_config[regstr_number].irq_handler,
                                        (void *)aggr_irq_config[regstr_number].data, NULL);
        }
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Store the SW interrupt info into the table
 * -------------------------------------------------------------------------------------------------------------------*/
static void com_store_direct_irq_info (uint32_t irq, f_isr_handler_t irq_handler, void *data)
{
    uint32_t int_num = irq - (e_AGGRGTR_INTERRUPTS + 1);
    xtos_set_interrupt_handler (direct_irq_config[int_num].cpu_irq, (xtos_handler)irq_handler, (void *)data, NULL);
}

/*
 * @brief           Configure interrupt handler.
 * @param [in]      irq: Interrupt number.
 * @param [in]      irq_handler: handler function
 * @param [in]      data: data received with interrupt
 * @return          none.
 */
void com_isr_event (uint32_t irq, f_isr_handler_t irq_handler, void *data)
{
    FW_PRINT (FW_INFO, "core%u: COM_ISR_EVENT, IRQ=%u", RCS_CPU, irq);
    if ((irq > e_AGGRGTR_INTERRUPTS) && (irq < e_DIRECT_HW_AND_SW_INTERRUPTS))
    {
        com_store_direct_irq_info (irq, irq_handler, data);
    }
    else
    {
        com_store_aggregator_irq_info (irq, irq_handler, data);
    }
}

/*
 * @brief           Enable interrupt.
 * @param [in]      irq: Interrupt number.
 * @return          none.
 */
void com_isr_interrupt_enable (uint32_t irq)
{
    uint32_t irq_base;

    FW_PRINT (FW_INFO, "core%u: com_isr enable:: irq =%u is requested", RCS_CPU, irq);
    if ((irq > e_AGGRGTR_INTERRUPTS)
        && (irq < e_DIRECT_HW_AND_SW_INTERRUPTS)) // SW interrupts and HW interrupts connected directly to cpu irq lines
    {
        irq_map_t *p_irq_data;
        irq_base = irq - (e_AGGRGTR_INTERRUPTS + 1);
        p_irq_data = &direct_irq_config[irq_base];
        xtos_interrupt_enable (p_irq_data->cpu_irq);
    }
    else
    {
        irq_num_handler_map_t *p_irq_data;
        uint32_t mask_bit;
        uint32_t edge_irq_reg;
        irq_base = com_get_reg (irq);
        if (irq_base >= NUM_OF_AGGRTR_IRQ_GRP)
        {
            FW_PRINT (FW_ERR, "core%u: This Register number: %u is invalid", RCS_CPU, irq_base);
        }
        else
        {
            mask_bit = com_get_bit_place (irq);

            edge_irq_reg = com_get_edge_reg (irq);
            p_irq_data = &aggr_irq_config[irq_base];
            if (edge_irq_reg != 0) // Edge Interrupts
            {
                if (edge_irq_reg == EDGE_REG0)
                {
                    if (!(RCS_GPREG_EDG_IRQ_MASK_0_REG->value & mask_bit))
                    {
                        RCS_GPREG_EDG_IRQ_MASK_0_REG->value |= mask_bit;
                    }
                    mask_bit = 0x2 << EDGE_REG0;
                }
                else if (edge_irq_reg == EDGE_REG1)
                {
                    if (!(RCS_GPREG_EDG_IRQ_MASK_1_REG->value & mask_bit))
                    {
                        RCS_GPREG_EDG_IRQ_MASK_1_REG->value |= mask_bit;
                    }
                    mask_bit = 0x2 << EDGE_REG1;
                }
                else if (edge_irq_reg == EDGE_REG2)
                {
                    if (!(RCS_GPREG_EDG_IRQ_MASK_2_REG->value & mask_bit))
                    {
                        RCS_GPREG_EDG_IRQ_MASK_2_REG->value |= mask_bit;
                    }
                    mask_bit = 0x2 << EDGE_REG2;
                }
                else
                {
                    FW_PRINT (FW_INFO, "core%u: Wrong Edge Triggered Interrupt Request Made", RCS_CPU);
                }
            }
            if (!((p_irq_data->mask_reg.LVL_IRQ_MASK) & mask_bit))
            {
                p_irq_data->mask_reg.LVL_IRQ_MASK |= mask_bit;
                *(INT_CFG0_GPREG_LVL_IRQ_MASK_REG (GPREG_CORE_BASE) + (p_irq_data->reg_idx * 4)) = p_irq_data->mask_reg;
            }
            xtos_interrupt_enable (p_irq_data->cpu_irq);
        }
    }
}

static void com_edge_irq_mask (rcs_gpreg_edg_irq_mask_0_reg_t *edge_reg, uint32_t mask_bit, uint32_t bit_posn)
{
    if ((edge_reg->value & mask_bit))
    {
        edge_reg->value &= ~mask_bit;
    }
    // Update the aggregator Reg10 mask bit
    if ((!edge_reg->value))
    {
        int_cfg_gpreg_lvl_irq_mask_reg_t temp;
        (INT_CFG0_GPREG_LVL_IRQ_MASK_REG (GPREG_CORE_BASE) + (10 * 4))->LVL_IRQ_MASK &= ~bit_posn;
    }
}

/*
 * @brief           Disable interrupt.
 * @param [in]      irq: Interrupt number.
 * @return          none.
 */
void com_isr_interrupt_disable (uint32_t irq)
{
    uint32_t irq_base;
    FW_PRINT (FW_INFO, "core%u: com_isr disable:: irq =%d is requested", RCS_CPU, irq);
    if ((irq > e_AGGRGTR_INTERRUPTS)
        && (irq < e_DIRECT_HW_AND_SW_INTERRUPTS)) // SW interrupts and HW interrupts connected directly to cpu irq lines
    {
        irq_map_t *p_irq_data;
        irq_base = irq - (e_AGGRGTR_INTERRUPTS + 1);
        p_irq_data = &direct_irq_config[irq_base];
        xtos_interrupt_disable (p_irq_data->cpu_irq);
    }
    else
    {
        uint32_t mask_bit;
        irq_num_handler_map_t *p_irq_data;
        irq_base = com_get_reg (irq);
        if (irq_base >= NUM_OF_AGGRTR_IRQ_GRP)
        {
            FW_PRINT (FW_ERR, "core%u: This Register number: %d is invalid", RCS_CPU, irq_base);
        }
        else
        {
            mask_bit = com_get_bit_place (irq);
            uint32_t edge_irq_reg;
            edge_irq_reg = com_get_edge_reg (irq);
            p_irq_data = &aggr_irq_config[irq_base];
            if (edge_irq_reg != 0) // Edge IRQ
            {
                uint32_t aggr_bit_posn;
                if (edge_irq_reg == EDGE_REG0)
                {
                    aggr_bit_posn = com_get_bit_place (e_RCS_GPREG_INT0_IRQ);
                    com_edge_irq_mask (RCS_GPREG_EDG_IRQ_MASK_0_REG, mask_bit, aggr_bit_posn);
                }
                else if (edge_irq_reg == EDGE_REG1)
                {
                    aggr_bit_posn = com_get_bit_place (e_RCS_GPREG_INT1_IRQ);
                    com_edge_irq_mask ((rcs_gpreg_edg_irq_mask_0_reg_t *)RCS_GPREG_EDG_IRQ_MASK_1_REG, mask_bit, aggr_bit_posn);
                }
                else if (edge_irq_reg == EDGE_REG2)
                {
                    aggr_bit_posn = com_get_bit_place (e_RCS_GPREG_INT2_IRQ);
                    com_edge_irq_mask ((rcs_gpreg_edg_irq_mask_0_reg_t *)RCS_GPREG_EDG_IRQ_MASK_2_REG, mask_bit, aggr_bit_posn);
                }
                else
                {
                    FW_PRINT (FW_INFO, "core%u: Wrong Edge Triggered Interrupt Request Made", RCS_CPU);
                }
            }
            else if (((p_irq_data->mask_reg.LVL_IRQ_MASK) & mask_bit)) // level IRQ
            {
                p_irq_data->mask_reg.LVL_IRQ_MASK &= ~mask_bit;
                *(INT_CFG0_GPREG_LVL_IRQ_MASK_REG (GPREG_CORE_BASE) + (p_irq_data->reg_idx * 4)) = p_irq_data->mask_reg;
            }

            if ((INT_CFG0_GPREG_LVL_IRQ_MASK_REG (GPREG_CORE_BASE) + (p_irq_data->reg_idx * 4))->value == 0)
            {
                xtos_interrupt_disable (p_irq_data->cpu_irq);
            }
        }
    }
}

/*
 * @brief           Trigger interrupt external to ABC.
 * @param [in]      irq: Interrupt number.
 * @return          none.
 */
void com_isr_ext_int (uint32_t irq)
{
    int_cfg_gpreg_lvl_irq_mask_reg_t irq_mask_reg;
    irq_mask_reg.LVL_IRQ_MASK = 1;
    *(INT_CFG0_GPREG_LVL_IRQ_MASK_REG (RCS_GPREG_EXT_BASE) + (irq * 4)) =
        irq_mask_reg; // Assuming one external interrupt assigned per aggregator registor.
}

/*
 * @brief           Trigger interrupt with Mailbox registers.
 * @param [in]      mb_irq:  MailBox Interrupt number.
 * @return          none.
 */
void com_mb_isr_trigger (e_com_int_mb_sel_t mb_irq, uint32_t data)
{
    RT_ASSERT (mb_irq < e_NUM_COM_INT_MB_SEL);
    if (mb_irq < e_NUM_EXT_TO_RCS)
    {
        RCS_GPREG_EXT_TO_RCS_MB0_MBDATA0_REG[mb_irq * 4 + 3].MAILBOX_DATA = data;
    }
    else
    {
        RCS_GPREG_RCS_TO_RCS_MB0_REG[mb_irq - e_RCS_TO_RCS0].MAILBOX_DATA = data;
    }
}

/*
 * @brief           Clear interrupt with Mailbox registers.
 * @param [in]      mb_irq:  MailBox Interrupt number.
 * @return          none.
 */
void com_mb_isr_clear (e_com_int_mb_sel_t mb_irq)
{
    RT_ASSERT (mb_irq < e_NUM_COM_INT_MB_SEL);
    rcs_gpreg_mailbox_clr_reg_t rcs_gpreg_mailbox_clr_reg = {.value = 1 << mb_irq};
    *RCS_GPREG_MAILBOX_CLR_REG = rcs_gpreg_mailbox_clr_reg;
}

/*
 * @brief           Routine to address unhandled interrupt.
 * @param [in]      arg: interrupt number.
 * @return          none.
 */
void com_unhandled_interrupt (void *arg)
{
    uint32_t intrpt_id = (uint32_t)arg;
    FW_PRINT (FW_ERR, "core%u: Attempting to execute uninitialized interrupt:  interrupt_no:%u", RCS_CPU, intrpt_id);
    FW_SEND_ERR_RB (e_IRQ_ERR, e_UNHANDLED_IRQ_ERR, intrpt_id);
    RT_ASSERT_HERE ();
    xtos_interrupt_disable (intrpt_id);
}

/*
 * @brief           Initialize interrupt.
 * @param [in]      none.
 * @return          none.
 */
void com_isr_init ()
{
    if (RCS_CPU == e_CPUID_AX)
    {
        com_isr_event (e_RCS_GPREG_INT0_IRQ, com_edge_irq_handler, (void *)EDGE_REG0);
        com_isr_event (e_RCS_GPREG_INT1_IRQ, com_edge_irq_handler, (void *)EDGE_REG1);
        com_isr_event (e_RCS_GPREG_INT2_IRQ, com_edge_irq_handler, (void *)EDGE_REG2);
    }
}
