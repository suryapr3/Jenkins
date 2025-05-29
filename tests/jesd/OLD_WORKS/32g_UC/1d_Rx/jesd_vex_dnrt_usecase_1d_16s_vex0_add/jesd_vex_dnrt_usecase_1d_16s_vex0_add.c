
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
 * @file    vex_jesd_dnrt.c
 * @brief   HOST Configuration code for sending the data from VEX to JESD and receving it back.
 * @details 1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
               and receving it back to VEX for all the Sample Rates
            2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
        1. 32K samples (1K vectors) for given data rate will be streamed to JESD from
           configured VEX core.
        2. With JESD NSIP loop back enabled the data looped back at sample interface
           was expected to reach the other VEX core where comparison will be performed.
        4. VEX core on which comparison algo was running will update the comparison result for
           every vector comparison and once the total 1K vector comparison was done HOST will
           read the result.
        5. Host will be waiting on a memory location where VEX will update the number of vectors
           it was processed.
        6. The supported Sample rates are
           0.25IQ, 0.5IQ, 1IQ, 2IQ, 4IQ, 8IQ, 4R, 8R, 16R
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"

#include "srp_jesd_nsip_hbi_map_regs.h"
#include "srp_vexa_vexabc_regs.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
//#include "flow2_common_utils.h"

#include "jesd_rx.map.h"


/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct register_config_tbl_s {
    uint32_t offset;
    uint32_t value;
    uint32_t mask;
    char *name;
} register_config_tbl_t;

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define printf LOG_PRINT

#define NUM_TOTAL_VEC_PER_STREAM 64

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define NUM_OF_ELEMENTS_PER_VEC 32

#define APB_OFFSET_GEN(apb_num) (apb_num * 0x20000)

#define CIO2STRM_INT_EN_VALUE 0x3F
#define CIO2STRM_FIFO_STATUS_CTL_VALUE 0x00000001
#define CIO2STRM_WORD_CNT_CTL_VALUE 0x00000001
#define STRM2CIO_INT_ENABLE_VALUE 0xF
#define STRM2CIO_FIFO_STATUS_CTL_VALUE 0x00000001
#define STRM2CIO_WORD_CNT_CTL_VALUE 0x00000001
#define NSIP_HBI_INT_CSR_INT_VALUE 0xFFF
#define FIFO_CONTROL_VALUE 0x00000184
#define CREDIT_CS_VALUE 0x3
#define MISC_CTRL_VALUE 0x0
#define CSR_INT_VALUE 0xFFFFFFFF


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
 
static register_config_tbl_t g_strm2cio_config_tbl[] = {
// INT Enable
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_INT_ENABLE, STRM2CIO_INT_ENABLE_VALUE, VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_INT_ENABLE_WR_MASK, \
        "STRM2CIO_INT_ENABLE"},
// VE00 strm2cio
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_FIFO_STATUS_CTL, STRM2CIO_FIFO_STATUS_CTL_VALUE, \
        VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_FIFO_STATUS_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
    {VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_WORD_CNT_CTL, STRM2CIO_WORD_CNT_CTL_VALUE, VEXA_VEXABC_S2C_REGS_REG_STRM2CIO_WORD_CNT_CTL_WR_MASK, \
        "STRM2CIO_MEM_WORD_CNT_CTL"}
};

// The last entry should be CIO2STRM_STRM_DEST0_OFFSET
static register_config_tbl_t g_cio2strm_config_tbl[] = {

// INT Enable
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_INT_ENABLE, CIO2STRM_INT_EN_VALUE, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_INT_ENABLE_WR_MASK, \
        "CIO2STRM_INT_ENABLE"},
//VE00 cio2strm
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_FIFO_STATUS_CTL, CIO2STRM_FIFO_STATUS_CTL_VALUE,
        VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_FIFO_STATUS_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_WORD_CNT_CTL, CIO2STRM_WORD_CNT_CTL_VALUE, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_WORD_CNT_CTL_WR_MASK, \
        "CIO2STRM_WORD_CNT_CTL"},
    /* Enables the single stream from vex core to CRUX*/
    {VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_RANGE_EN, 0x000000FF, VEXA_VEXABC_C2S_REGS_REG_CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(0), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(0), 0x1FFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(0), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[0] - mapped to JESD_Port_0
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(0), 0x00000040, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
	
	//MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(1), 0x20000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(1), 0x3FFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[1]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(1), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[1] - mapped to JESD_Port_0
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(1), 0x00000040, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},

	//MEM_ADDR_LOW[2] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(2), 0x40000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(2), 0x5FFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[2]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(2), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[2] - mapped to JESD_Port_0
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(2), 0x00000040, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[3] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(3), 0x60000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(3), 0x7FFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[3]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(3), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[3] - mapped to JESD_Port_0
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(3), 0x00000040, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[4] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(4), 0x80000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(4), 0x9FFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[4]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(4), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[4] - mapped to JESD_Port_1
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(4), 0x00000041, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[5] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(5), 0xA0000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(5), 0xBFFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[5]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(5), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[5] - mapped to JESD_Port_1
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(5), 0x00000041, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[6] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(6), 0xC0000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(6), 0xDFFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[6]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(6), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[6] - mapped to JESD_Port_1
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(6), 0x00000041, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[7] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(4), 0xE0000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(4), 0xFFFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[7]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(4), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[7] - mapped to JESD_Port_1
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(4), 0x00000041, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
};

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last Three entries order shouldn't be modified*/
static register_config_tbl_t g_cm_0_config_tbl[] = {
// NSIP Interrupt enable registers
    {JESD_NSIP_HBI_MAP_INT_CSR_INT_HIGH_EN, NSIP_HBI_INT_CSR_INT_VALUE, JESD_NSIP_HBI_MAP_INT_CSR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {JESD_NSIP_HBI_MAP_INT_CSR_INT_LOW_EN, NSIP_HBI_INT_CSR_INT_VALUE, JESD_NSIP_HBI_MAP_INT_CSR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},

// H2B Registers
    {JESD_NSIP_HBI_MAP_H2B_FIFO_CSR_H2B_FIFO_CONTROL, FIFO_CONTROL_VALUE, \
        JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {JESD_NSIP_HBI_MAP_H2B_CREDIT_READY_CS, CREDIT_CS_VALUE, JESD_NSIP_HBI_MAP_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN, MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},
    
    
    /* 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case */
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(0), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(1), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(2), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(3), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(4), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(5), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(6), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(7), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(8), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(9), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(10), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(11), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(12), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(13), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(14), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(15), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    
    /* Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80*/
    {JESD_NSIP_HBI_MAP_H2B_TK_ADDR_LKUP_TBL(0), 0x4020, JESD_NSIP_HBI_MAP_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_MD_ADDR_LKUP_TBL(0), 0x4000, JESD_NSIP_HBI_MAP_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},

    {JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL(0), 0x400, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},

    /* Data will be written to VEX location 0x0000 * 4 = 0x0000 , i.e VEX VMEM location 0x0000*/
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(0), 0x80000000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
#if 1
    /* Data will be written to VEX location 0x200 * 4 = 0x800 , i.e VEX VMEM location 0x800*/
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(1), 0x80000200, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    /* Data will be written to VEX location 0x400 * 4 = 0x1000 , i.e VEX VMEM location 0x1000*/
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(2), 0x80000400, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    /* Data will be written to VEX location 0x600 * 4 = 0x1800 , i.e VEX VMEM location 0x1800*/
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(3), 0x80000600, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	/* Data will be written to VEX location 0x800 * 4 = 0x2000 , i.e VEX VMEM location 0x2000*/
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(4), 0x80000800, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000*/
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(5), 0x80001000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    /* Data will be written to VEX location 0x1200 * 4 = 0x4800 , i.e VEX VMEM location 0x4800*/
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(6), 0x80001200, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    /* Data will be written to VEX location 0x1400 * 4 = 0x5000 , i.e VEX VMEM location 0x5000*/
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(7), 0x80001400, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(8), 0x80001600, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(9), 0x80001800, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(10), 0x80002000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(11), 0x80002200, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(12), 0x80002400, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(13), 0x80002600, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(14), 0x80002800, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(15), 0x80003000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
    
#endif
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(0), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(1), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(2), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(3), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
	{JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(4), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(5), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(6), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(7), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
    
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(8), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(9), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(10), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(11), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(12), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(13), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(14), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(15), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
    
// B2H Registers - JESD - 0
    {(JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL), FIFO_CONTROL_VALUE, \
        JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(JESD_NSIP_HBI_MAP_B2H_CREDIT_CS), CREDIT_CS_VALUE, JESD_NSIP_HBI_MAP_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    {(JESD_NSIP_HBI_MAP_B2H_MISC_CTRL), MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},

    // These are for Buffer S0
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(0)), 0x80000000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(0)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

    // These are for Buffer S1
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(1)), 0x80008000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(1)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S2
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(2)), 0x80010000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(2)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S3
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(3)), 0x80018000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(3)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
};

static register_config_tbl_t g_cm_1_config_tbl[] = {
// NSIP Interrupt enable registers
    {JESD_NSIP_HBI_MAP_INT_CSR_INT_HIGH_EN, NSIP_HBI_INT_CSR_INT_VALUE, JESD_NSIP_HBI_MAP_INT_CSR_INT_HIGH_EN_WR_MASK, \
        "CM_0_INT_HIGH_EN"},
    {JESD_NSIP_HBI_MAP_INT_CSR_INT_LOW_EN, NSIP_HBI_INT_CSR_INT_VALUE, JESD_NSIP_HBI_MAP_INT_CSR_INT_LOW_EN_WR_MASK, \
        "CM_0_INT_LOW_EN"},


// H2B Registers
    {JESD_NSIP_HBI_MAP_H2B_FIFO_CSR_H2B_FIFO_CONTROL, FIFO_CONTROL_VALUE, \
        JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
    {JESD_NSIP_HBI_MAP_H2B_CREDIT_READY_CS, CREDIT_CS_VALUE, JESD_NSIP_HBI_MAP_H2B_CREDIT_READY_CS_WR_MASK, \
        "H2B_CREDIT_READY_CS"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN, MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},
    
    
    /* 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case */
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(8), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(9), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(10), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(11), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(12), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(13), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(14), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL(15), 0x2, JESD_NSIP_HBI_MAP_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},


    /* Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80*/
    {JESD_NSIP_HBI_MAP_H2B_TK_ADDR_LKUP_TBL(8), 0x4020, JESD_NSIP_HBI_MAP_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_TK_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_MD_ADDR_LKUP_TBL(8), 0x4000, JESD_NSIP_HBI_MAP_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
        "H2B_MD_ADDR_LKUP_TBL0"},
    /* Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000*/
#if 1
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(8), 0x80000000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(9), 0x80001000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(10), 0x80002000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(11), 0x80003000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	{JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(12), 0x80000000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(13), 0x80001000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(14), 0x80002000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL(15), 0x80003000, JESD_NSIP_HBI_MAP_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
#endif
    {JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL(8), 0x400, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},
    
	//config for streams 8-15 to vex1
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(8), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(9), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(10), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(11), 0x0, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
	{JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(12), 0x1, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(13), 0x1, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(14), 0x1, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL(15), 0x1, JESD_NSIP_HBI_MAP_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
    
    {JESD_NSIP_HBI_MAP_H2B_MD_ROUTE_LKUP_TBL(8), 0x1, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_MD_ROUTE_LKUP_TBL(9), 0x1, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_MD_ROUTE_LKUP_TBL(10), 0x1, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_MD_ROUTE_LKUP_TBL(11), 0x1, JESD_NSIP_HBI_MAP_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL3"},
    
    {JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL(8), 0x1, JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL0"},
    {JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL(9), 0x1, JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL1"},
    {JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL(10), 0x1, JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL2"},
    {JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL(11), 0x1, JESD_NSIP_HBI_MAP_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL3"},
    

    


// B2H Registers - JESD - 1
    {(JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL), FIFO_CONTROL_VALUE, \
        JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(JESD_NSIP_HBI_MAP_B2H_CREDIT_CS), CREDIT_CS_VALUE, JESD_NSIP_HBI_MAP_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    {(JESD_NSIP_HBI_MAP_B2H_MISC_CTRL), MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},

    // These are for Buffer S4
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(0)), 0x80020000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(0)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

    // These are for Buffer S5
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(1)), 0x80028000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(1)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S6
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(2)), 0x80030000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(2)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S7
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(3)), 0x80038000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(3)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
};

register_config_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

/*
register_config_tbl_t g_jesd_reset_config[] = {
    {0x184, 0, 0, "JESD_SOFT_RESET"},
    {0x184, 0, 0, "JESD_SOFT_RESET"}
};
*/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int configure_jesd_host(int, int, int, int);



/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/
/**
 * @brief           Function for noc reset
 * @param [in]      srp
 * @return          status value
 */

static int release_reset_abc_noc (void *srp)
{
    int i, rv = 0, flags = 0;
    for (i = 0; i < ARRAY_SIZE(g_vex_noc_config); i++)
    {
        rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CFG_CTRL,
                        0,
                        g_vex_noc_config[i].offset,
                        &g_vex_noc_config[i].value,
                        1,
                        flags);

    }
    return rv;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id, Jesd Id, APB Id and SYS_RATE_IQ_P5
 * @return          status
 */
int configure_jesd_host(int vex_num, int jesd_num, int apb_num, int cm_num)
{
    int i,j,rv = 0;
    

	for (i = 0; i < ARRAY_SIZE(g_strm2cio_config_tbl); i++)
	{

		if (rv = write_reg(SRP_BLOCK_VEX_CORE, (vex_num), g_strm2cio_config_tbl[i].offset, g_strm2cio_config_tbl[i].value, \
					g_strm2cio_config_tbl[i].mask, g_strm2cio_config_tbl[i].name))
			return rv;
	}
	
    printf("INFO: strm2cio configuration completed");
    
    
    for (i = 0; i < ARRAY_SIZE(g_cio2strm_config_tbl); i++)
    {
        if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num, g_cio2strm_config_tbl[i].offset, g_cio2strm_config_tbl[i].value, \
                g_cio2strm_config_tbl[i].mask, g_cio2strm_config_tbl[i].name))
            return rv;
    }

    printf("INFO: cio2strm configuration completed");

    for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
    {
        if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, jesd_num, (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
                g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
            return rv;
    }
#if 0
	for (i = 0; i< (ARRAY_SIZE(g_cm_1_config_tbl)); i++)
    {
        if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, jesd_num+1, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
#endif
    // SDF init
    if (rv = write_reg(SRP_BLOCK_VEX_CORE, vex_num, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM, \
                HIVE_ADDR_jesd_rx_consumer_sm_gate, VEXA_VEXABC_SC_REGS_LM_BPCA_BP_DMEM_WR_MASK, "BPCA_BP_DMEM"))
        return rv;
	
    return rv;

}


int
main(int argc, const char *argv[])
{
    int rv = 0;
    int flags = 0;
    void *vex_hdl;
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vex_num, jesd_num, apb_num, host_flag = 1, cm_num = 0, port_num = 0;
    volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
	int total_streams = 8;

    int dmem_offset = 0x4000;
    int vex_tx_offset_val[] = {HIVE_ADDR_jesd_rx_g_num_vecs_in, HIVE_ADDR_jesd_rx_g_tbs_in_blk};
    unsigned vex_tx_val_kargs[] = {128, 4};

	/*unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
                                HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
								HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
                                HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};*/
    unsigned int add_val[1];

    init(); /* Initialize the srp*/

    //subsys_reset_cycle();
    vex_reset_cycle();
    //jesd_reset_cycle();
    crux_reset_cycle();
    
    sleep(2);
    //system("source jesd_config.sh"); //vijay

    LOG_PRINT("INFO: logger beginning\n");

    vex_num = 0;
    jesd_num = 0;
    port_num= 0;
    apb_num = 0;
    cm_num = 0;
    printf("vex id: %d , jesd_num : %d , apb_num: %d, cm_num: %d\n",vex_num, jesd_num, apb_num, cm_num);

    memset(&vex_params, 0, sizeof(vex_params));
    memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

    if (rv = configure_jesd_host(vex_num, jesd_num, apb_num, cm_num))
    {
        printf ("ERROR: configure_jesd_host\n");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, vex_params)))
        return rv;

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    printf("Host: start vex rx program load \n");

    if ((rv = srp_vex_loader(vex_hdl, vex_num, "vex_fw/sim_m64/jesd_rx.fw")))
        return rv;

    printf("Host: vex program load - done\n");


    /* Loading the host parameters to VEX  Rx core*/
    for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++)
    {
        if ((rv = srp_core_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vex_num,
                        dmem_offset + vex_tx_offset_val[lc],
                        &vex_tx_val_kargs[lc],
                        1,
                        flags)))
            return rv;
        //sleep(1);
    }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends

    /* Input Vector Generation*/
#if 0
	for (lc = 0; lc < total_streams; lc++)
	{
        for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
        {
            for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
            {
				val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
				val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
				val_inp[i][j] = val_inp[i][j] | (lc << 28 | lc << 12);
            }
        }
     
        if ((rv = srp_vex_memid_store(vex_hdl,
                            vex_num,
                            SRP_VEX_VMEM,
                            vex_tx_buffer_addr[lc],/*local_addr*/
                            val_inp[0],
                            (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
    }
#endif
    printf("Host: vex program start\n");

    srp_vex_start(vex_hdl, vex_num, 0); // vijay

    printf("Host: vex program start - done\n");
	
    /*Signal VEX to start continuous flow*/
    /*if ((rv = srp_core_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_jesd_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;*/

    //system("srpRamTest -s 64KB -W 0x63.0.0x30000 0"); // Vijay: Just for testing, remove it
return rv;
}   // main ends
