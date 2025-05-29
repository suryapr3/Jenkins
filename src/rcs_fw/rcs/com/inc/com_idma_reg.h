/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
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
#ifndef COMMON_IDMA_REG_H
#define COMMON_IDMA_REG_H

typedef union {
    struct
    {
        uint32_t : 2;
        uint32_t BLOCK : 2; // 0=block 2, 1=block 4, 2=block 8, 3=block 16
        uint32_t : 2;
        uint32_t HALTABLE : 1; // 0=disallow halt, 1=allow halt
        uint32_t FETCH_START : 1;
        uint32_t NUM_OUT : 6;
        uint32_t : 18;
    };
    uint32_t value;
} idma_settings_reg_t;

typedef union {
    struct
    {
        uint32_t CLOCKS : 3;
        uint32_t TIMEOUT : 29;
    };
    uint32_t value;
} idma_timeout_reg_t;

typedef union {
    struct
    {
        uint32_t DESC_START_ADDR : 32;
    };
    uint32_t value;
} idma_desc_start_addr_reg_t;

typedef union {
    struct
    {
        uint32_t NUM_DESC : 8;
        uint32_t : 24;
    };
    uint32_t value;
} idma_num_desc_reg_t;

typedef union {
    struct
    {
        uint32_t NUM_DESC_INCR : 8;
        uint32_t : 24;
    };
    uint32_t value;
} idma_num_desc_incr_reg_t;

typedef union {
    struct
    {
        uint32_t ENABLE_IDMA : 1;
        uint32_t RESET_IDMA : 1;
        uint32_t : 30;
    };
    uint32_t value;
} idma_ctrl_reg_t;

typedef union {
    struct
    {
#if (HAS_MMU)
        uint32_t : 30;
        uint32_t PRIV_MODE : 2;
#else
        uint32_t : 31;
        uint32_t PRIV_MODE : 1;
#endif // HAS_MMU
    };
    uint32_t value;
} idma_priviledge_reg_t;

typedef union {
    struct
    {
        uint32_t RUN_MODE : 3; // 0=idle, 1=standby, 2=busy, 3=done, 4=halt, 5=error
        uint32_t : 1;
        uint32_t HAVE_TRIG : 1;
        uint32_t : 4;
        uint32_t ERR_TLB : 9;
        uint32_t ERR_CODES : 14;
    };
    uint32_t value;
} idma_stat_reg_t;

typedef union {
    struct
    {
        uint32_t DESC_CURR_ADDR : 32;
    };
    uint32_t value;
} idma_desc_curr_addr_reg_t;

typedef union {
    struct
    {
        uint32_t DESC_CURR_TYPE : 3;
        uint32_t : 29;
    };
    uint32_t value;
} idma_desc_curr_type_reg_t;

typedef union {
    struct
    {
        uint32_t SRC_ADDR : 32;
    };
    uint32_t value;
} idma_src_addr_reg_t;

typedef union {
    struct
    {
        uint32_t DST_ADDR : 32;
    };
    uint32_t value;
} idma_dst_addr_reg_t;

typedef struct
{
    idma_settings_reg_t IDMA_SETTINGS;
    idma_timeout_reg_t IDMA_TIMEOUT;
    idma_desc_start_addr_reg_t IDMA_DESC_ADDR;
    idma_num_desc_reg_t IDMA_NUM_DESC;
    idma_num_desc_incr_reg_t IDMA_NUM_DESC_INCR;
    idma_ctrl_reg_t IDMA_CTRL;
    idma_priviledge_reg_t IDMA_PRIVILEDGE;
    const uint32_t rsvd0[10];
    idma_stat_reg_t IDMA_STATUS;
    idma_desc_curr_addr_reg_t IDMA_CURR_ADDR;
    idma_desc_curr_type_reg_t IDMA_CURR_TYPE;
    idma_src_addr_reg_t IDMA_SRC_ADDR;
    idma_dst_addr_reg_t IDMA_DST_ADDR;
} idma_t;

#define IDMA                   ((idma_reg_t *)0x00110000) // supervisor
#define IDMA_SETTINGS_REG      ((idma_settings_reg_t *)0x00110000)
#define IDMA_TIMEOUT_REG       ((idma_timeout_reg_t *)0x00110004)
#define IDMA_DESC_ADDR_REG     ((idma_desc_start_addr_reg_t *)0x00110008)
#define IDMA_NUM_DESC_REG      ((idma_num_desc_reg_t *)0x0011000C)
#define IDMA_NUM_DESC_INCR_REG ((idma_num_desc_incr_reg_t *)0x00110010)
#define IDMA_CTRL_REG          ((idma_ctrl_reg_t *)0x00110014)
#define IDMA_PRIVILEDGE_REG    ((idma_priviledge_reg_t *)0x00110018)
#define IDMA_STATUS_REG        ((idma_stat_reg_t *)0x00110040)
#define IDMA_CURR_ADDR_REG     ((idma_desc_curr_addr_reg_t *)0x00110044)
#define IDMA_CURR_TYPE_REG     ((idma_desc_curr_type_reg_t *)0x00110048)
#define IDMA_SRC_ADDR_REG      ((idma_src_addr_reg_t *)0x0011004C)
#define IDMA_DST_ADDR_REG      ((idma_dst_addr_reg_t *)0x00110050)

#define IDMA_SETTINGS_REG_RESET_VALUE      (0x000000CC)
#define IDMA_TIMEOUT_REG_RESET_VALUE       (0x00000000)
#define IDMA_DESC_ADDR_REG_RESET_VALUE     (0x00000000)
#define IDMA_NUM_DESC_REG_RESET_VALUE      (0x00000000)
#define IDMA_NUM_DESC_INCR_REG_RESET_VALUE (0x00000000)
#define IDMA_CTRL_REG_RESET_VALUE          (0x00000000)
#define IDMA_PRIVILEDGE_REG_RESET_VALUE    (0x00000000)
#define IDMA_STATUS_REG_RESET_VALUE        (0x00000000)
#define IDMA_CURR_ADDR_REG_RESET_VALUE     (0x00000000)
#define IDMA_CURR_TYPE_REG_RESET_VALUE     (0x00000000)
#define IDMA_SRC_ADDR_REG_RESET_VALUE      (0x00000000)
#define IDMA_DST_ADDR_REG_RESET_VALUE      (0x00000000)

#endif // COMMON_IDMA_REG_H
