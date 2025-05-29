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
#ifndef ACCESS_CHECK_COMMON_NOC_ORION_DEFINITIONS_H
#define ACCESS_CHECK_COMMON_NOC_ORION_DEFINITIONS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "com_definitions.h"
#include "all_comps.h"
#include "common_macro.h"
#include "uc_top_msg.h"
#include "noc.h"
#include "noc_orion.h"

#define ARRAY_SIZE(x) ( sizeof(x) / sizeof(x[0]) )

typedef enum
{
    M_RCS_0 = 0,
    M_RCS_1,
    M_PCIE,
    M_CS_DBG,
    M_SYSCON_1,
    M_SYSCON_0,
    M_DRF0_MEM_FB,
    M_DRF1_MEM_FB,
    S_JESD0 = 0,
    S_JESD1,
    S_JESD2,
    S_JESD3,
    S_DRF0_FB_ANT,
    S_DRF0_FB_SYS,
    S_DRF0_TRXANT0,
    S_DRF0_ANT0,
    S_DRF0_TRXSYS0,
    S_DRF0_TRXANT1,
    S_DRF0_ANT1,
    S_DRF0_TRXSYS1,
    S_DRF0_TRXANT2,
    S_DRF0_TRXSYS2,
    S_DRF0_TRXANT3,
    S_DRF0_TRXSYS3,
    S_DRF0_MEM,
    S_DRF0_MEM_FB,
    S_DRF1_FB_ANT,
    S_DRF1_FB_SYS,
    S_DRF1_TRXANT0,
    S_DRF1_ANT0,
    S_DRF1_TRXSYS0,
    S_DRF1_TRXANT1,
    S_DRF1_ANT1,
    S_DRF1_TRXSYS1,
    S_DRF1_TRXANT2,
    S_DRF1_TRXSYS2,
    S_DRF1_TRXANT3,
    S_DRF1_TRXSYS3,
    S_DRF1_MEM,
    S_DRF1_MEM_FB,
    S_SYSCON_MAIN,
    S_PCIE,
    S_PCIE_DBI,
    //S_PCIE_CFG,
    S_VEX_CAR,
    S_VEX0,
    S_VEX1,
    S_VEX2,
    //S_VEX_DBG0,
    //S_VEX_DBG1,
    //S_VEX_DBG2,
    S_VHA0,
    S_VHA1,
    S_VHA2,
    S_VHA3,
    S_VHA4,
    S_VHA5,
    S_VHA6,
    S_VHA7,
    S_V2D0,
    S_V2D1,
    S_V2D2,
    S_V2D3,
    S_V2D4,
    S_V2D5,
    S_V2D6,
    S_V2D7,
    //S_HUB,
    S_RCS0,
    S_RCS1,
    //S_RCS_CS,
    S_VEX_SFC_RBM
}bridge_type_t;

// This enum follows the order in which the RBM registers are arranged per master bridge.
typedef enum {
    HUB = 0,
    JESD_0,
    JESD_1,
    JESD_2,
    JESD_3,
    PCIE,
    PCIE_CFG,
    PCIE_DBI,
    DRF_0_ANT_0,
    DRF_0_ANT_1,
    DRF_0_FB_ANT,
    DRF_0_FB_SYS,
    DRF_0_MEM,
    DRF_0_MEM_FB,
    DRF_0_TRXANT_0,
    DRF_0_TRXANT_1,
    DRF_0_TRXANT_2,
    DRF_0_TRXANT_3,
    DRF_0_TRXSYS_0,
    DRF_0_TRXSYS_1,
    DRF_0_TRXSYS_2,
    DRF_0_TRXSYS_3,
    DRF_1_ANT_0,
    DRF_1_ANT_1,
    DRF_1_FB_ANT,
    DRF_1_FB_SYS,
    DRF_1_MEM,
    DRF_1_MEM_FB,
    DRF_1_TRXANT_0,
    DRF_1_TRXANT_1,
    DRF_1_TRXANT_2,
    DRF_1_TRXANT_3,
    DRF_1_TRXSYS_0,
    DRF_1_TRXSYS_1,
    DRF_1_TRXSYS_2,
    DRF_1_TRXSYS_3,
    VEX_SFC_RBM,
    RCS_0,
    RCS_1,
    RCS_CS,
    SYSCON_MAIN,
    V2D_0,
    V2D_1,
    V2D_2,
    V2D_3,
    V2D_4,
    V2D_5,
    V2D_6,
    V2D_7,
    VEX_0,
    VEX_1,
    VEX_2,
    VEX_CAR,
    VEX_DBG_0,
    VEX_DBG_1,
    VEX_DBG_2,
    VHA_0,
    VHA_1,
    VHA_2,
    VHA_3,
    VHA_4,
    VHA_5,
    VHA_6,
    VHA_7
}target_type_t;

typedef struct {
    uint32_t offset;
    uint32_t rd_mask;
    uint32_t wr_mask;
}bridge_reg_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[216];
}m_rcs_0_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[216];
}m_rcs_1_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[219];
}m_pcie_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[42];
}m_cs_dbg_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[219];
}m_syscon_1_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[222];
}m_syscon_0_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[216];
}m_drf0_mem_fb_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[216];
}m_drf1_mem_fb_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[15];
}s_bridge_type_t;

typedef struct {
    uint32_t base_addr;
    bridge_reg_type_t regs[6];
}s_bridge_rbm_type_t;

typedef struct {
    m_rcs_0_type_t m_rcs_0;
    m_rcs_1_type_t m_rcs_1;
    m_pcie_type_t m_pcie;
    m_cs_dbg_type_t m_cs_dbg;
    m_syscon_1_type_t m_syscon_1;
    m_syscon_0_type_t m_syscon_0;
    m_drf0_mem_fb_type_t m_drf0_mem_fb;
    m_drf1_mem_fb_type_t m_drf1_mem_fb;
    s_bridge_type_t s_bridges[57];
    s_bridge_rbm_type_t s_bridge_rbm;
}noc_type_t;

typedef struct {
    uint32_t base_addr, offset, rd_mask, wr_mask;
}target_reg_type_t;

typedef struct {
    target_reg_type_t regs[2];
}target_list_type_t;

#endif
