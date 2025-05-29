
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
#include "all_comps.h"
//#include "flow2_common_utils.h"

#include<time.h> 

#include "jesd_tx.map.h"


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
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW(7), 0xE0000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH(7), 0xFFFFF, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[7]- is in words
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET(7), 0x00000000, VEXA_VEXABC_C2S_REGS_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[7] - mapped to JESD_Port_1
    {VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST(7), 0x00000041, VEXA_VEXABC_C2S_REGS_CIO2STRM_STRM_DEST_WR_MASK, \
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

// B2H Registers - JESD - 1
    {(JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL), FIFO_CONTROL_VALUE, \
        JESD_NSIP_HBI_MAP_B2H_FIFO_CSR_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
    {(JESD_NSIP_HBI_MAP_B2H_CREDIT_CS), CREDIT_CS_VALUE, JESD_NSIP_HBI_MAP_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
    {(JESD_NSIP_HBI_MAP_B2H_MISC_CTRL), MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},

    // These are for Buffer S4
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(4)), 0x80020000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(4)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

    // These are for Buffer S5
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(5)), 0x80028000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(5)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S6
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(6)), 0x80030000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(6)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
	
	// These are for Buffer S7
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL(7)), 0x80038000, JESD_NSIP_HBI_MAP_B2H_ADDR_MAP_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
    // Mask was set for total 2K flits in words
    {(JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL(7)), 0x7FFF, JESD_NSIP_HBI_MAP_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
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
    int i, rv = 0;
    
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
	
	for (i = 0; i< (ARRAY_SIZE(g_cm_1_config_tbl)); i++)
    {
        if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, jesd_num+1, (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
                g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
            return rv;
    }
	
    return rv;

}

static void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// JESD TX reg
static int program_tx_ip_registers()
{
	uint16_t core_number;

	printf("JESD TX IP CONFIG : program_tx_ip_registers \n");
	for (core_number=0; core_number <= 1; core_number++)
	{
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_SUBCLASS_REG,0x00000001,0x00000001,JESD_XIP_TX_JL_SUBCLASS_REG_RD_MASK,JESD_XIP_TX_JL_SUBCLASS_REG_WR_MASK,"JESD_XIP_TX_JL_SUBCLASS_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_FEC_ENB_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_FEC_ENB_REG_RD_MASK,JESD_XIP_TX_JL_FEC_ENB_REG_WR_MASK,"JESD_XIP_TX_JL_FEC_ENB_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CRC3_EN_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CRC3_EN_REG_RD_MASK,JESD_XIP_TX_JL_CRC3_EN_REG_WR_MASK,"JESD_XIP_TX_JL_CRC3_EN_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CRC12_EN_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CRC12_EN_REG_RD_MASK,JESD_XIP_TX_JL_CRC12_EN_REG_WR_MASK,"JESD_XIP_TX_JL_CRC12_EN_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_BIT_ORDER_REG,0x00000003,0x00000003,JESD_XIP_TX_JL_BIT_ORDER_REG_RD_MASK,JESD_XIP_TX_JL_BIT_ORDER_REG_WR_MASK,"JESD_XIP_TX_JL_BIT_ORDER_REG");
		
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_E_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_E_REG_RD_MASK,JESD_XIP_TX_JL_E_REG_WR_MASK,"JESD_XIP_TX_JL_E_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CF_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CF_REG_RD_MASK,JESD_XIP_TX_JL_CF_REG_WR_MASK,"JESD_XIP_TX_JL_CF_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_HD_REG,0x00000001,0x00000001,JESD_XIP_TX_JL_HD_REG_RD_MASK,JESD_XIP_TX_JL_HD_REG_WR_MASK,"JESD_XIP_TX_JL_HD_REG");
		
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CMD_ENB_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CMD_ENB_REG_RD_MASK,JESD_XIP_TX_JL_CMD_ENB_REG_WR_MASK,"JESD_XIP_TX_JL_CMD_ENB_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_SAMPLE_REQ_REG,0x00000001,0x00000001,JESD_XIP_TX_JL_SAMPLE_REQ_REG_RD_MASK,JESD_XIP_TX_JL_SAMPLE_REQ_REG_WR_MASK,"JESD_XIP_TX_JL_SAMPLE_REQ_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CLK_RATIO_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CLK_RATIO_REG_RD_MASK,JESD_XIP_TX_JL_CLK_RATIO_REG_WR_MASK,"JESD_XIP_TX_JL_CLK_RATIO_REG");
		
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_L_REG,0x00000003,0x00000003,JESD_XIP_TX_JL_L_REG_RD_MASK,JESD_XIP_TX_JL_L_REG_WR_MASK,"JESD_XIP_TX_JL_L_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_M_REG,0x0000000f,0x0000000f,JESD_XIP_TX_JL_M_REG_RD_MASK,JESD_XIP_TX_JL_M_REG_WR_MASK,"JESD_XIP_TX_JL_M_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_F_REG,0x00000007,0x00000007,JESD_XIP_TX_JL_F_REG_RD_MASK,JESD_XIP_TX_JL_F_REG_WR_MASK,"JESD_XIP_TX_JL_F_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_S_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_S_REG_RD_MASK,JESD_XIP_TX_JL_S_REG_WR_MASK,"JESD_XIP_TX_JL_S_REG");
		
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_SONIF_REG,0x00000100,0x00000100,JESD_XIP_TX_JL_SONIF_REG_RD_MASK,JESD_XIP_TX_JL_SONIF_REG_WR_MASK,"JESD_XIP_TX_JL_SONIF_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_N_REG,0x0000000f,0x0000000f,JESD_XIP_TX_JL_N_REG_RD_MASK,JESD_XIP_TX_JL_N_REG_WR_MASK,"JESD_XIP_TX_JL_N_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_NTOTAL_REG,0x0000000f,0x0000000f,JESD_XIP_TX_JL_NTOTAL_REG_RD_MASK,JESD_XIP_TX_JL_NTOTAL_REG_WR_MASK,"JESD_XIP_TX_JL_NTOTAL_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_CS_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_CS_REG_RD_MASK,JESD_XIP_TX_JL_CS_REG_WR_MASK,"JESD_XIP_TX_JL_CS_REG");
		
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_TX_TL_TEST_MODE_REG,0x00000000,0x00000000,JESD_XIP_TX_JL_TX_TL_TEST_MODE_REG_RD_MASK,JESD_XIP_TX_JL_TX_TL_TEST_MODE_REG_WR_MASK,"JESD_XIP_TX_JL_TX_TL_TEST_MODE_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_TX_TL_DELAY_REG,0x0000000b,0x0000000b,JESD_XIP_TX_JL_TX_TL_DELAY_REG_RD_MASK,JESD_XIP_TX_JL_TX_TL_DELAY_REG_WR_MASK,"JESD_XIP_TX_JL_TX_TL_DELAY_REG");
		
		//is this SCR reg ?
		//write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_SYSREF_CONFIG_REG,0x00000001,0x00000001,JESD_XIP_TX_JL_SYSREF_CONFIG_REG_RD_MASK,JESD_XIP_TX_JL_SYSREF_CONFIG_REG_WR_MASK,"JESD_XIP_TX_JL_SYSREF_CONFIG_REG");	
	}
}

// JESD CMN CSR reg
static int program_cmn_csr_registers()
{
	uint16_t core_number;

	printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
	for (core_number=0; core_number <= 1; core_number++)
	{
		write_read_expect(SRP_BLOCK_JESD_CMN_CSR, core_number,JESD_JESDABC_CMN_CSR_TX_CLK_CTRL,0x0000000a,0x0000000a,JESD_JESDABC_CMN_CSR_TX_CLK_CTRL_RD_MASK,JESD_JESDABC_CMN_CSR_TX_CLK_CTRL_WR_MASK,"JESD_JESDABC_CMN_CSR_TX_CLK_CTRL");
		write_read_expect(SRP_BLOCK_JESD_CMN_CSR, core_number,JESD_JESDABC_CMN_CSR_RX_CLK_CTRL,0x0000000a,0x0000000a,JESD_JESDABC_CMN_CSR_RX_CLK_CTRL_RD_MASK,JESD_JESDABC_CMN_CSR_RX_CLK_CTRL_WR_MASK,"JESD_JESDABC_CMN_CSR_RX_CLK_CTRL");
	}
}

// JESD TX glue reg
static int program_tx_glue_registers()
{
	uint16_t core_number;

	printf("JESD TX GLUE CONFIG : program_tx_glue_registers \n");
	for (core_number=0; core_number <= 1; core_number++)
	{	
		//for (i=0; i <= 31; i++)
		//for (i=0; i <= 15; i++)
					
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(0),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(1),0x00001000,0x00001000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(1),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(2),0x00002000,0x00002000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(2),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(3),0x00003000,0x00003000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(3),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(4),0x00004000,0x00004000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(4),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(5),0x00005000,0x00005000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(5),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(6),0x00006000,0x00006000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(6),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0(7),0x00007000,0x00007000,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL0_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL0");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1(7),0x00000fff,0x00000fff,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_ID_TBL1_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_ID_TBL1");
	
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_CRUX_PORT_MAP,0x000000f0,0x000000f0,JESD_JESDABC_TX_GLUE_STRM_CRUX_PORT_MAP_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_CRUX_PORT_MAP_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_CRUX_PORT_MAP");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_STRM_MEM_INST_CNT,0x00000001,0x00000001,JESD_JESDABC_TX_GLUE_STRM_MEM_INST_CNT_RD_MASK,JESD_JESDABC_TX_GLUE_STRM_MEM_INST_CNT_WR_MASK,"JESD_JESDABC_TX_GLUE_STRM_MEM_INST_CNT");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_CONV_DP_CFG,0x00000050,0x00000050,JESD_JESDABC_TX_GLUE_CONV_DP_CFG_RD_MASK,JESD_JESDABC_TX_GLUE_CONV_DP_CFG_WR_MASK,"JESD_JESDABC_TX_GLUE_CONV_DP_CFG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_MEM_RD_CFG,0x0000000f,0x0000000f,JESD_JESDABC_TX_GLUE_MEM_RD_CFG_RD_MASK,JESD_JESDABC_TX_GLUE_MEM_RD_CFG_WR_MASK,"JESD_JESDABC_TX_GLUE_MEM_RD_CFG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_TX_DATAPATH_EN_REG,0x00000120,0x00000120,JESD_JESDABC_TX_GLUE_TX_DATAPATH_EN_REG_RD_MASK,JESD_JESDABC_TX_GLUE_TX_DATAPATH_EN_REG_WR_MASK,"JESD_JESDABC_TX_GLUE_TX_DATAPATH_EN_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_TX_CFG_UPD,0x00000001,0x00000001,JESD_JESDABC_TX_GLUE_TX_CFG_UPD_RD_MASK,JESD_JESDABC_TX_GLUE_TX_CFG_UPD_WR_MASK,"JESD_JESDABC_TX_GLUE_TX_CFG_UPD");	
	    write_read_expect(SRP_BLOCK_JESD_XIP_TX_GLUE, core_number,JESD_JESDABC_TX_GLUE_TX_TSB_TRIG_EN_REG,0x80000000,0x80000000,JESD_JESDABC_TX_GLUE_TX_TSB_TRIG_EN_REG_RD_MASK,JESD_JESDABC_TX_GLUE_TX_TSB_TRIG_EN_REG_WR_MASK,"JESD_JESDABC_TX_GLUE_TX_TSB_TRIG_EN_REG");
	}
}

// JESD enable reg
static int program_enable_registers()
{
	uint16_t core_number;

	printf("JESD ENABLE : program_enable_registers \n");
	for (core_number=0; core_number <= 1; core_number++)
	{
		write_read_expect(SRP_BLOCK_JESD_XIP_TX, core_number,JESD_XIP_TX_JL_JESD_ENABLE_REG,0x1,0x1,JESD_XIP_TX_JL_JESD_ENABLE_REG_RD_MASK,JESD_XIP_TX_JL_JESD_ENABLE_REG_WR_MASK,"JESD_XIP_TX_JL_JESD_ENABLE_REG");
		write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_JESD_ENABLE_REG,0x1,0x1,JESD_XIP_RX_JL_JESD_ENABLE_REG_RD_MASK,JESD_XIP_RX_JL_JESD_ENABLE_REG_WR_MASK,"JESD_XIP_RX_JL_JESD_ENABLE_REG");
	}
}

static void configure_jesd_block()
{
	uint32_t tx_gb_empty_reg = 0;
	uint32_t tx_gb_full_reg = 0;
	uint32_t rx_gb_empty_reg = 0;
	uint32_t rx_gb_full_reg = 0;

	// function calls - Reg seq usecase 1a
	program_tx_ip_registers();
	program_cmn_csr_registers();
	program_tx_glue_registers();


	printf("Giving delay of 10 milli seconds \n");
	delay(10);
	tx_gb_empty_reg = read_reg(SRP_BLOCK_JESD_XIP_TX, 0, 0x000003E8, "JL_N_TX_GB_EMPTY_REG");
	tx_gb_full_reg = read_reg(SRP_BLOCK_JESD_XIP_TX, 0, 0x000003EC, "JL_N_TX_GB_FULL_REG");
	rx_gb_empty_reg = read_reg(SRP_BLOCK_JESD_XIP_RX, 0, 0x000003E8, "JL_N_RX_GB_EMPTY_REG");
	rx_gb_full_reg = read_reg(SRP_BLOCK_JESD_XIP_RX, 0, 0x000003EC, "JL_N_RX_GB_FULL_REG");
	printf(" Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
	printf(" Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
	printf(" Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
	printf(" Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);

	program_enable_registers();
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
    int vex_tx_offset_val[] = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,
                                HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
								HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
                                HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base};
    unsigned vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000};

	unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
                                HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
								HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
                                HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
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

    printf("Host: start vex tx program load \n");

    if ((rv = srp_vex_loader(vex_hdl, vex_num, "vex_fw/sim_m64/jesd_tx.fw")))
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

    printf("Host: vex program start\n");
    
    srp_vex_start(vex_hdl, vex_num, 0); // vijay
    
    configure_jesd_block();

    printf("Host: vex program start - done\n");
	
    /*Signal VEX to start continuous flow*/
    if ((rv = srp_core_block_write32(srp,
                    SRP_BLOCK_VEX_CORE,
                    vex_num,
                    dmem_offset + HIVE_ADDR_jesd_tx_g_host_indicator,
                    &host_flag,
                    1,
                    flags)))
        return rv;

    //system("srpRamTest -s 64KB -W 0x63.0.0x30000 0"); // Vijay: Just for testing, remove it
return rv;
}   // main ends
