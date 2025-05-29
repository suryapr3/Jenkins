
/*********************************************************************************************
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

//#include "srp_jesd_nsip_hbi_map_regs.h"
#include "nsip_hbi.h"
#include "ve32_tile_strm2cio.h"
#include "ve32_tile_cio2strm.h"
#include "ve32_cell.h"
//#include "srp_vexa_vexabc_regs.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
//#include "flow2_common_utils.h"

#include<time.h>  

#include "vex_fw/sim_m64/jesd_rx.map.h"
//test
#define CIO2STRM_OFFSET (VEXABC0_C2S_VE32_TILE_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE)
#define STRM2CIO_OFFSET (VEXABC0_S2C_VE32_TILE_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE)

enum jesdUsecasenum{UC0B, UC1A,UC1D,UC0A,UC1C,UC3C,UC3D,UC4A,UC4B,UC4D,UC5A,UC5C};

typedef struct jesdConfig_t {
int jesdUsecase;
int jesdTxncs;
int jesdEn;
int jesdTestmode;
int jesdFecCrc;
int jesdBitordertx;
int jesdBitorderrx;
int jesdShth;
int jesdEmbth;
}jesdConfig_t;

struct  flow_params_t {
int vexCount;
int nsipCount;
jesdConfig_t jesdConfig;
}flow_params;

//roshan uncommenting below 2 lines, for testing, 01/12/23
int vexCount = 1;
int nsipCount = 1;

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

//#define printf LOG_PRINT

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
//Added for U-0B;U-1A;U-1D;U-0A;U-1C.
//STRM2CIO table
static register_config_tbl_t g_strm2cio_config_tbl[] = {
// INT Enable
{STRM2CIO_OFFSET + VE32_TILE_STRM2CIO_MEM_INT_ENABLE_OFFSET, STRM2CIO_INT_ENABLE_VALUE, VE32_TILE_STRM2CIO_MEM_INT_ENABLE_WR_MASK, \
	"STRM2CIO_INT_ENABLE"},
// VE00 strm2cio
{STRM2CIO_OFFSET + VE32_TILE_STRM2CIO_MEM_FIFO_STATUS_CTL_OFFSET, STRM2CIO_FIFO_STATUS_CTL_VALUE, \
	VE32_TILE_STRM2CIO_MEM_FIFO_STATUS_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
{STRM2CIO_OFFSET + VE32_TILE_STRM2CIO_MEM_WORD_CNT_CTL_OFFSET, STRM2CIO_WORD_CNT_CTL_VALUE, VE32_TILE_STRM2CIO_MEM_WORD_CNT_CTL_WR_MASK, \
	"STRM2CIO_MEM_WORD_CNT_CTL"}
};


/* //roshan 30/11/23, this is not needed for rx path, start2
// The last entry should be CIO2STRM_STRM_DEST0_OFFSET
//CIO2STRM table-0
//For U-0B ;U-1A RX;U-1D;U-0A;U-1C
// VEX0 table1
static register_config_tbl_t g_cio2strm_config_tbl[] = {
		
// INT Enable
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_INT_ENABLE_OFFSET, CIO2STRM_INT_EN_VALUE, VE32_TILE_CIO2STRM_MEM_CIO2STRM_INT_ENABLE_WR_MASK, \
	"CIO2STRM_INT_ENABLE"},
//VE00 cio2strm
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE,
	VE32_TILE_CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, VE32_TILE_CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_WR_MASK, \
	"CIO2STRM_WORD_CNT_CTL"},
// Enables the single stream from vex core to CRUX
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_RANGE_EN_OFFSET, 0x000000FF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_RANGE_EN_WR_MASK, \
	"CIO2STRM_RANGE_EN"},

//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_OFFSET, 0x1FFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[0]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[0] - mapped to JESD_Port_0
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST0_OFFSET, 0x00000040, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},

//MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW1_OFFSET, 0x20000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH1_OFFSET, 0x3FFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[1]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET1_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[1] - mapped to JESD_Port_0
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST1_OFFSET, 0x00000040, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},

//MEM_ADDR_LOW[2] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW2_OFFSET, 0x40000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH2_OFFSET, 0x5FFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[2]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET2_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[2] - mapped to JESD_Port_0
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST2_OFFSET, 0x00000040, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
	
//MEM_ADDR_LOW[3] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW3_OFFSET, 0x60000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH3_OFFSET, 0x7FFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[3]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET3_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[3] - mapped to JESD_Port_0
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST3_OFFSET, 0x00000040, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
	
//MEM_ADDR_LOW[4] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW4_OFFSET, 0x80000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH4_OFFSET, 0x9FFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[4]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET4_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[4] - mapped to JESD_Port_1
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST4_OFFSET, 0x00000041, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
	
//MEM_ADDR_LOW[5] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW5_OFFSET, 0xA0000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH5_OFFSET, 0xBFFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[5]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET5_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[5] - mapped to JESD_Port_1
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST5_OFFSET, 0x00000041, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
	
//MEM_ADDR_LOW[6] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW6_OFFSET, 0xC0000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH6_OFFSET, 0xDFFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[6]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET6_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[6] - mapped to JESD_Port_1
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST6_OFFSET, 0x00000041, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
	
//MEM_ADDR_LOW[7] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW7_OFFSET, 0xE0000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
	"CIO2STRM_MEM_ADDR_LOW0"},
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH7_OFFSET, 0xFFFFF, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
	"CIO2STRM_MEM_ADDR_HIGH0"},
//MEM_OFFSET[7]- is in words
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET7_OFFSET, 0x00000000, VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_DEFAULT, \
	"CIO2STRM_MEM_OFFSET0"},
//STRM_DEST[7] - mapped to JESD_Port_1
{CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST7_OFFSET, 0x00000041, VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
	"CIO2STRM_STRM_DEST0"},
};
*/
//end2

//Added on 27/10/23 for RX side 
//FOR  STRM2CIO
//Added for _0B; U_1A;U_1D;U_0A;U_1C
//                                                                    0                         1                       2               3                      4                             
static register_config_tbl_t* vexConfigArray_STRM2CIO[5] = {g_strm2cio_config_tbl, g_strm2cio_config_tbl, g_strm2cio_config_tbl, g_strm2cio_config_tbl, g_strm2cio_config_tbl};

//                                                                  0                        1                                2                                            3                           4
static int vexConfigArray_STRM2CIOSize[5] = {	ARRAY_SIZE(g_strm2cio_config_tbl),ARRAY_SIZE(g_strm2cio_config_tbl), ARRAY_SIZE(g_strm2cio_config_tbl),ARRAY_SIZE(g_strm2cio_config_tbl),ARRAY_SIZE(g_strm2cio_config_tbl)};

static int vexCountStartIdxTbl_STRM2CIO[2];

/* //roshan 01/12/23, not needed for rx path, start3
//FOR CIO2STRM
static register_config_tbl_t* vexConfigArray_CIO2STRM[5] = { g_cio2strm_config_tbl, g_cio2strm_config_tbl, g_cio2strm_config_tbl, g_cio2strm_config_tbl, g_cio2strm_config_tbl
					};
static int vexConfigArray_CIO2STRMSize[5] = {	ARRAY_SIZE(g_cio2strm_config_tbl),ARRAY_SIZE(g_cio2strm_config_tbl),ARRAY_SIZE(g_cio2strm_config_tbl),ARRAY_SIZE(g_cio2strm_config_tbl),ARRAY_SIZE(g_cio2strm_config_tbl)

			};
*/ //end3

//static int vexCountStartIdxTbl_CIO2STRM[2]={2,1};


//Added for U_1A;U-0A;U-1C
// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
//The Last Three entries order shouldn't be modified
//NSIP table-1

//roshan hardcoding nsip registers for usecase 5c, for now, will update automation later 01/12/23
//below table is not used for now,
//
static register_config_tbl_t g_cm_0_config_tbl[] = {
	// NSIP Interrupt enable registers

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
		"CM_0_INT_HIGH_EN"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
		"CM_0_INT_LOW_EN"},

	// H2B Registers
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
		NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, CREDIT_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
		"H2B_CREDIT_READY_CS"},	
		//To Check
	//{JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN, MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},

	//===============================================================================================================================
	//Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80
	// TK, MD Addr and MD Control not needed for jesd to vex traffic as of now, roshan 01/12/23, this was presnet only for 0th table and for others it was already removed.
	//{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, 0x4020, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
		"H2B_TK_ADDR_LKUP_TBL0"},
	//{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_OFFSET, 0x4000, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
		"H2B_MD_ADDR_LKUP_TBL0"},
	//{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, 0x400, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},

	// 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case 
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
	// Data will be written to VEX location 0x0000 * 4 = 0x0000 , i.e VEX VMEM location 0x0000
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},


	//keeping only stream one for 18A for now due design restriction, roshan 01/12/23 
	/* //start5
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL1_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL1_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
	// Data will be written to VEX location 0x200 * 4 = 0x800 , i.e VEX VMEM location 0x800
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL1_OFFSET, 0x80000200, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL2_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
	// Data will be written to VEX location 0x400 * 4 = 0x1000 , i.e VEX VMEM location 0x1000
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL2_OFFSET, 0x80000400, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL3_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL3_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
	// Data will be written to VEX location 0x600 * 4 = 0x1800 , i.e VEX VMEM location 0x1800
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL3_OFFSET, 0x80000600, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	 
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL4_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL4_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
	// Data will be written to VEX location 0x800 * 4 = 0x2000 , i.e VEX VMEM location 0x2000
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL4_OFFSET, 0x80000800, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL5_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL5_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
	// Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL5_OFFSET, 0x80001000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL6_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL6_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
	// Data will be written to VEX location 0x1200 * 4 = 0x4800 , i.e VEX VMEM location 0x4800
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL6_OFFSET, 0x80001200, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},

	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL7_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL7_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
	// Data will be written to VEX location 0x1400 * 4 = 0x5000 , i.e VEX VMEM location 0x5000
	{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL7_OFFSET, 0x80001400, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
	*/ //end5

};

/* //roshan 01/12/23, 2nd NSIP not needed for 18A, start4
//NSIP table-2
static register_config_tbl_t g_cm_1_config_tbl[] = {
// NSIP Interrupt enable registers
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
	"CM_0_INT_HIGH_EN"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
	"CM_0_INT_LOW_EN"},


// H2B Registers
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
	NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "H2B_FIFO_CONTROL"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, CREDIT_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
	"H2B_CREDIT_READY_CS"},	
	//To Check
//{JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN, MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_H2B_BUF_FC_EN_WR_MASK, "H2B_BUF_FC_EN"},


// 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case 
(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL2_OFFSET,,0x643ae8a6,0x643ae8a6,NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK,NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK,"NSIP_HBI_H2B_BUF_SZ_HW_TBL");

{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL8_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL9_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL10_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL11_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL12_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL13_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL14_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_BUF_SZ_HW_TBL15_OFFSET, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0"},


// Data will be written to VEX location 0x4020 * 4 = 0x10080 , i.e VEX DMEM location 0x80
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ADDR_LKUP_TBL8_OFFSET, 0x4020, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, \
	"H2B_TK_ADDR_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ADDR_LKUP_TBL8_OFFSET, 0x4000, NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK, \
	"H2B_MD_ADDR_LKUP_TBL0"},
// Data will be written to VEX location 0x1000 * 4 = 0x4000 , i.e VEX VMEM location 0x4000
#if 1
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL8_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL9_OFFSET, 0x80001000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL10_OFFSET, 0x80002000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL11_OFFSET, 0x80003000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL12_OFFSET, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL13_OFFSET, 0x80001000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL14_OFFSET, 0x80002000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ADDR_LKUP_TBL15_OFFSET, 0x80003000, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL3"},
#endif
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_CONTROL_TBL8_OFFSET, 0x400, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "H2B_MD_CONTROL_TBL0"},

//config for streams 8-15 to vex1
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL8_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL9_OFFSET 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL10_OFFSET 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL11_OFFSET, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL12_OFFSET, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL13_OFFSET, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL14_OFFSET, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_ROUTE_LKUP_TBL15_OFFSET, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL3"},

{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL8_OFFSET, 0x1, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL9_OFFSET, 0x1, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL10_OFFSET, 0x1, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL11_OFFSET, 0x1, NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK, "H2B_MD_ROUTE_LKUP_TBL3"},

{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL8_OFFSET, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL0"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL9_OFFSET, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL1"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL10_OFFSET, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL2"},
{JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL11_OFFSET, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "H2B_TK_ROUTE_LKUP_TBL3"},


// B2H Registers - JESD - 1
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_OFFSET), FIFO_CONTROL_VALUE, \
	NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_WR_MASK, "B2H_FIFO_CONTROL"},
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_OFFSET), CREDIT_CS_VALUE, NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_WR_MASK, "B2H_CREDIT_CS"},
//To Check
//{(JESD_NSIP_HBI_MAP_B2H_MISC_CTRL), MISC_CTRL_VALUE, JESD_NSIP_HBI_MAP_B2H_MISC_CTRL_WR_MASK, "B2H_MISC_CTRL"},

// These are for Buffer S4
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET), 0x80020000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
// Mask was set for total 2K flits in words
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET), 0x7FFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// These are for Buffer S5
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET), 0x80028000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
// Mask was set for total 2K flits in words
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET), 0x7FFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// These are for Buffer S6
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL2_OFFSET), 0x80030000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
// Mask was set for total 2K flits in words
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL2_OFFSET), 0x7FFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},

// These are for Buffer S7
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_TBL3_OFFSET), 0x80038000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "B2H_ADDR_MAP_TBL0"},
// Mask was set for total 2K flits in words
{(JESDABC_M0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL3_OFFSET), 0x7FFF, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "B2H_ADDR_MASK_TBL0"},
};
*/ //end4


//All usecases == 2 NSIP entries
//static register_config_tbl_t* nsipConfigArray[2] = {g_cm_0_config_tbl, g_cm_1_config_tbl};
static register_config_tbl_t* nsipConfigArray[1] = {g_cm_0_config_tbl};
//static int nsipConfigArraySize[2] = {ARRAY_SIZE(g_cm_0_config_tbl),ARRAY_SIZE(g_cm_1_config_tbl)};
static int nsipConfigArraySize[1] = {ARRAY_SIZE(g_cm_0_config_tbl)};

//static int nsipConfigArraySize[2] = {ARRAY_SIZE(g_cm_0_config_tbl),ARRAY_SIZE(g_cm_1_config_tbl)};
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
int configure_jesd_host(int, int [], int, int[], int, int);



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
	rv = srp_dev_block_write32(srp,
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
// static register_config_tbl_t* ptr;
int configure_jesd_host(int vexCount, int vexId[], int nsipCount, int nsipId[], int apb_num, int cm_num)
{
int vexIdx,j,k,rv = 0;
int i=0;
int nsipIdx = 0;

printf("###### Hi configuring JESD host\n");
//CIO2STRM
//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
/*for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
{
	for (j = 0; j < vexConfigArray_CIO2STRMSize[vexIdx]; j++)
	{

		if (rv = write_reg(SRP_BLOCK_VEX_CORE, vexId[vexIdx], vexConfigArray_CIO2STRM[vexIdx][j].offset, vexConfigArray_CIO2STRM[vexIdx][j].value, \
					vexConfigArray_CIO2STRM[vexIdx][j].mask, vexConfigArray_CIO2STRM[vexIdx][j].name))
			return rv;
	}

	printf("INFO: Vex %d configuration completed", vexIdx);
}
*/
//Added for STRM2CIO 27/10/23
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
{
	for (j = 0; j < vexConfigArray_STRM2CIOSize[vexIdx]; j++)
	{

		if (rv = write_reg(SRP_BLOCK_VEX_CORE, vexId[vexIdx], vexConfigArray_STRM2CIO[vexIdx][j].offset, vexConfigArray_STRM2CIO[vexIdx][j].value, \
					vexConfigArray_STRM2CIO[vexIdx][j].mask, vexConfigArray_STRM2CIO[vexIdx][j].name))
			return rv;
	}

	printf("INFO: Vex %d configuration completed", vexIdx);
}

nsipCount = 1;  //roshan hardcoding this value for debug 01/12/23
/*
for (nsipIdx = 0; nsipIdx < nsipCount; nsipIdx++)
{
	printf("nsipCount = %d\n", nsipCount);
	printf("nsipId[%d] = %d\n", nsipIdx, nsipId[nsipIdx]);
	printf("nsipConfigArraySize[%d] = %d\n", nsipIdx, nsipConfigArraySize[nsipIdx]);
	for (i = 0; i<nsipConfigArraySize[nsipIdx]; i++)
	{
		printf("looped %d, %d, %d + %d, 0x%x, 0x%x, %s\n", SRP_BLOCK_JESD_NSIP_HBI, nsipId[nsipIdx], APB_OFFSET_GEN(apb_num), nsipConfigArray[nsipIdx][i].offset, nsipConfigArray[nsipIdx][i].value, nsipConfigArray[nsipIdx][i].mask, nsipConfigArray[nsipIdx][i].name);
//		if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, nsipId[nsipIdx], (APB_OFFSET_GEN(apb_num) + nsipConfigArray[nsipIdx][i].offset), nsipConfigArray[nsipIdx][i].value, \
//					nsipConfigArray[nsipIdx][i].mask, nsipConfigArray[nsipIdx][i].name))
		if (rv = write_reg(JESDABC_M0_NSIP_HBI_CSR_BASE, nsipConfigArray(, nsipConfigArray[nsipIdx][i].value, \
					nsipConfigArray[nsipIdx][i].mask, nsipConfigArray[nsipIdx][i].name))
		{
			printf("INFO: ### loading jesd0 b2h config done");
			printf("INFO: rv value is %d ", rv);
			return rv;
			
		}
	}
	printf("INFO:  ### JESD0 NSIP %d, nsipIdx DONE completed", nsipIdx);
}
*/


	//roshan hardcoding nsip registers for usecase 5c, for now, will update automation later 01/12/23
	printf("###vexcount is = %d\n", vexCount);
	printf("###nsipCount is = %d\n", nsipCount);
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INTR_INT_HIGH_EN_DEFAULT, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_RD_MASK, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_INTR_INT_HIGH_EN");
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INTR_INT_LOW_EN_DEFAULT, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_RD_MASK, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_INTR_INT_LOW_EN");
	// H2B Registers
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET,NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_DEFAULT , FIFO_CONTROL_VALUE, FIFO_CONTROL_VALUE, NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_RD_MASK, NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL");
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT, CREDIT_CS_VALUE, CREDIT_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_RD_MASK, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, "NSIP_HBI_H2B_CREDIT_READY_CS");
	
	// 512 flits of DEST Buffer Size (2 ^ 9) in VEX corresponds to 2 blocks of data for max 8GSPS case
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_BUF_SZ_HW_TBL0_OFFSET, NSIP_HBI_H2B_BUF_SZ_HW_TBL_DEFAULT, 0x2, 0x2, NSIP_HBI_H2B_BUF_SZ_HW_TBL_RD_MASK, NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK, "H2B_BUF_SZ_HW_TBL0");
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, 0x0, 0x0, NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0");
	// Data will be written to VEX location 0x0000 * 4 = 0x0000 , i.e VEX VMEM location 0x0000
	write_read_expect_18a(JESDABC_M0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, 0x80000000, 0x80000000, NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0");
	
/*
printf("ARRAY_SIZE(g_cm_0_config_tbl) = %d\n", ARRAY_SIZE(g_cm_0_config_tbl));
for (i = 0; i< (ARRAY_SIZE(g_cm_0_config_tbl)); i++)
{
	printf("Focus %d, %d, %d + %d, 0x%x, 0x%x, %s\n", SRP_BLOCK_JESD_NSIP_HBI, nsipId[0], APB_OFFSET_GEN(apb_num), g_cm_0_config_tbl[i].offset, g_cm_0_config_tbl[i].value, g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name);
	if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, nsipId[0], (APB_OFFSET_GEN(apb_num) + g_cm_0_config_tbl[i].offset), g_cm_0_config_tbl[i].value, \
				g_cm_0_config_tbl[i].mask, g_cm_0_config_tbl[i].name))
	{
		printf("INFO: ### loading jesd0 b2h config done");
		return rv;
	}
}
printf("INFO: ### JESD0 NSIP DONE completed");

printf("ARRAY_SIZE(g_cm_1_config_tbl) = %d\n", ARRAY_SIZE(g_cm_1_config_tbl));
for (i = 0; i< (ARRAY_SIZE(g_cm_1_config_tbl)); i++)
{
	printf("Focus %d, %d, %d + %d, 0x%x, 0x%x, %s\n", SRP_BLOCK_JESD_NSIP_HBI, nsipId[1], APB_OFFSET_GEN(apb_num), g_cm_1_config_tbl[i].offset, g_cm_1_config_tbl[i].value, g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name);
	if (rv = write_reg(SRP_BLOCK_JESD_NSIP_HBI, nsipId[1], (APB_OFFSET_GEN(apb_num) + g_cm_1_config_tbl[i].offset), g_cm_1_config_tbl[i].value, \
				g_cm_1_config_tbl[i].mask, g_cm_1_config_tbl[i].name))
	{
		printf("INFO: ### loading jesd1 b2h config done");        
		return rv;
	}
}
printf("INFO: ### JESD1 NSIP DONE completed");
*/

return rv;
}

static void delay(unsigned int milliseconds){

clock_t start = clock();

while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// JESD CMN CSR reg
//For 16G usecases JESD CMN CSR reg == 0xa(U-0B;U-1A;U-0A)
//For 32G usecases JESD CMN CSR reg == 0x5(U-1D)


static int program_cmn_csr_registers()
{
	int i=0;
	uint32_t base_address_cmn[] = {JESDABC_M0_CMN_CSR_BASE,  JESDABC_M1_CMN_CSR_BASE,  JESDABC_M2_CMN_CSR_BASE,  JESDABC_M3_CMN_CSR_BASE};
	printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
	//for(i=0; i<sizeof(base_address_cmn) / sizeof(base_address_cmn[0]); i++)
	for(i=0; i<1; i++)
	{ 		
		if (flow_params.jesdConfig.jesdUsecase == UC0B)
		{
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	    }
		 
		else if (flow_params.jesdConfig.jesdUsecase == UC1A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC0A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	    }
	   
	    else if(flow_params.jesdConfig.jesdUsecase == UC1D)
		{
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
		}
	   
		else if (flow_params.jesdConfig.jesdUsecase == UC1C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	    }
	    else if (flow_params.jesdConfig.jesdUsecase == UC5C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	    }
	   
		else
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x0000000a, 0x0000000a, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	    }
	}
}


//Modified code for RX
//Commanon parameters & diff parameters added for U-0b,U-1a,U-1d, U-0a
// JESD TX reg
static int program_rx_ip_registers()
{
	int i=0;
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	printf("JESD RX IP CONFIG : program_rx_ip_registers \n");
	//for(i=0; i<sizeof(base_address_rx) / sizeof(base_address_rx[0]); i++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SUBCLASS_OFFSET, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SUBCLASS_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET, JESD_XIP_204C_RX_MEM_RX_FEC_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_FEC_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_FEC_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_OFFSET, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_OFFSET");
		
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_E_OFFSET, JESD_XIP_204C_RX_MEM_RX_E_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_E_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_E_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_E_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CF_OFFSET, JESD_XIP_204C_RX_MEM_RX_CF_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CF_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_HD_OFFSET, JESD_XIP_204C_RX_MEM_RX_HD_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_HD_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_HD_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_HD_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CMD_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CMD_EN_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_OFFSET, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_S_OFFSET, JESD_XIP_204C_RX_MEM_RX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_S_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_S_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_S_OFFSET");
		
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_N_OFFSET, JESD_XIP_204C_RX_MEM_RX_N_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_N_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_N_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_N_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CS_OFFSET, JESD_XIP_204C_RX_MEM_RX_CS_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CS_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CS_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CS_OFFSET");
		
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET, JESD_XIP_204C_RX_MEM_RX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_SCR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SCR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET");
		
	}
	

   if (flow_params.jesdConfig.jesdUsecase == UC5C )
   {
		printf("JESD RX path - UC 5B -LMFS -4-16-8-1 - IQ bandwidth -\n");
		write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
		write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
		write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

		write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000005, 0x00000005, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
		write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000005, 0x00000005, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
   }
   
   else if (flow_params.jesdConfig.jesdUsecase == UC0B )
   {
		printf("JESD RX path - UC 0B -LMFS -4-32-16-1 - IQ bandwidth -2Gsps\n");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000001f, 0x0000001f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000008, 0x00000008, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
   }
   
   else if (flow_params.jesdConfig.jesdUsecase == UC1A)
	{

		printf("JESD RX path - UC 1A -LMFS -4-16-8-1 \n");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
	}
   
	else if (flow_params.jesdConfig.jesdUsecase == UC1D )
   {
		printf("JESD RX path - UC 1D -LMFS -4-32-16-1 - IQ bandwidth -2Gsps\n");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000001f, 0x0000001f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000008, 0x00000008, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
   }

	else if (flow_params.jesdConfig.jesdUsecase == UC0A)
	{

	printf("JESD RX path - UC 0A -LMFS -2-16-16-1 \n");
		
/* 	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_L_REG,0x00000001,0x00000001,JESD_XIP_RX_JL_L_REG_RD_MASK,JESD_XIP_RX_JL_L_REG_WR_MASK,"JESD_XIP_RX_JL_L_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_M_REG,0x0000000f,0x0000000f,JESD_XIP_RX_JL_M_REG_RD_MASK,JESD_XIP_RX_JL_M_REG_WR_MASK,"JESD_XIP_RX_JL_M_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_F_REG,0x0000000f,0x0000000f,JESD_XIP_RX_JL_F_REG_RD_MASK,JESD_XIP_RX_JL_F_REG_WR_MASK,"JESD_XIP_RX_JL_F_REG");
	
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_SH_ERR_REG,0x00000010,0x00000010,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_SH_ERR_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG,0x00000008,0x00000008,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_EMB_ERR_REG");
 */
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000008, 0x00000008, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");

	}

	else if (flow_params.jesdConfig.jesdUsecase == UC1C)
	{

	printf("JESD RX path - UC 1C -LMFS -2-16-16-1 \n");
	
/* 	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_L_REG,0x00000001,0x00000001,JESD_XIP_RX_JL_L_REG_RD_MASK,JESD_XIP_RX_JL_L_REG_WR_MASK,"JESD_XIP_RX_JL_L_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_M_REG,0x0000000f,0x0000000f,JESD_XIP_RX_JL_M_REG_RD_MASK,JESD_XIP_RX_JL_M_REG_WR_MASK,"JESD_XIP_RX_JL_M_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_F_REG,0x0000000f,0x0000000f,JESD_XIP_RX_JL_F_REG_RD_MASK,JESD_XIP_RX_JL_F_REG_WR_MASK,"JESD_XIP_RX_JL_F_REG");
	
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_SH_ERR_REG,0x00000010,0x00000010,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_SH_ERR_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG,0x00000008,0x00000008,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_EMB_ERR_REG");
 */
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000008, 0x00000008, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");

	}

	else
	{
	printf("JESD RX path for Default test i.e. - UC 0B -LMFS -4-32-16-1 \n");
					
/* 	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_L_REG,0x00000003,0x00000003,JESD_XIP_RX_JL_L_REG_RD_MASK,JESD_XIP_RX_JL_L_REG_WR_MASK,"JESD_XIP_RX_JL_L_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_M_REG,0x0000001f,0x0000001f,JESD_XIP_RX_JL_M_REG_RD_MASK,JESD_XIP_RX_JL_M_REG_WR_MASK,"JESD_XIP_RX_JL_M_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_F_REG,0x0000000f,0x0000000f,JESD_XIP_RX_JL_F_REG_RD_MASK,JESD_XIP_RX_JL_F_REG_WR_MASK,"JESD_XIP_RX_JL_F_REG");
	
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_SH_ERR_REG,0x00000010,0x00000010,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_SH_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_SH_ERR_REG");
	write_read_expect(SRP_BLOCK_JESD_XIP_RX, core_number,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG,0x00000008,0x00000008,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_RD_MASK,JESD_XIP_RX_JL_THRESH_EMB_ERR_REG_WR_MASK,"JESD_XIP_RX_JL_THRESH_EMB_ERR_REG");
 */
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000001f, 0x0000001f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000008, 0x00000008, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
	}

}

// JESD RX glue reg
static int program_rx_glue_registers()
{
	int i=0;
	uint32_t base_address_rx_glue[] = {JESDABC_M0_RX_GLUE_BASE,  JESDABC_M1_RX_GLUE_BASE,  JESDABC_M2_RX_GLUE_BASE,  JESDABC_M3_RX_GLUE_BASE};
	printf("JESD RX GLUE CONFIG : program_rx_glue_registers \n");
//	for(i=0; i<sizeof(base_address_rx_glue) / sizeof(base_address_rx_glue[0]); i++)
	for(i=0; i<1; i++)
	{ 
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
		{
		   //keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
		   //enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			
			
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			//write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000000e1, 0x000000e1, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_ID_EN");
			//write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET");
			
			//new values for complete rsb capture
			//stream is 8, for current debug we are keeping it 1 and flits per stream is 63,(register value is 7e8)
			//for 1 stream keeping a value of 7e1
			
			//write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000007e1, 0x000007e1, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET");
			//bits 13:5 is for numbr of flits per stream
			//moving back to 8 streams, so making last 4 bits value as 8, and bits "13 to 5" as 7, so putting all bits together value is e8
			//making value from e8 to 88, so the flit count per stream is now 2.
			write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x00000048, 0x00000048, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET");
			//Now to increase the total flits to 64 x 8 streams = 512, so 511, in hex 0x1ff, for 1 stream we will keep 3f
			write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC0B)
		{	
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000020, 0x00000020, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000060, 0x00000060, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000a0, 0x000000a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000e0, 0x000000e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000120, 0x00000120, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000160, 0x00000160, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001a0, 0x000001a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001e0, 0x000001e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000220, 0x00000220, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000440, 0x00000440, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000660, 0x00000660, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000880, 0x00000880, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000aa0, 0x00000aa0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000cc0, 0x00000cc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000ee0, 0x00000ee0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001100, 0x00001100, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001320, 0x00001320, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001540, 0x00001540, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001760, 0x00001760, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001980, 0x00001980, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001ba0, 0x00001ba0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001dc0, 0x00001dc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001fe0, 0x00001fe0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001d0, 0x000001d0, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");
		}

		else if (flow_params.jesdConfig.jesdUsecase == UC1A)
		{	   
		
			//18A ref
			/* 		
			write_read_expect_18a(JESD_JESDRX_GLUE_BASE + JESDABC_RX_GLUE_MEM_WR_MEM_TBL00_OFFSET(i), JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_DEFAULT,0x00000000,0x00000000,JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_RD_MASK,JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_WR_MASK,"JESDABC_RX_GLUE_MEM_WR_MEM_TBL0");
			write_read_expect_18a(JESD_JESDRX_GLUE_BASE + JESDABC_RX_GLUE_MEM_WR_MEM_TBL01_OFFSET(i), JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_DEFAULT,0x00000000,0x00000000,JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_RD_MASK,JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_WR_MASK,"JESDABC_RX_GLUE_MEM_WR_MEM_TBL1");
			write_read_expect_18a(JESD_JESDRX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RD_MEM_TBL00_OFFSET(i), JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_DEFAULT,0x00000000,0x00000000,JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_RD_MASK,JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_WR_MASK,"JESDABC_RX_GLUE_MEM_RD_MEM_TBL0");
			write_read_expect_18a(JESD_JESDRX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RD_MEM_TBL01_OFFSET(i), JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_DEFAULT,0x00000800,0x00000800,JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_RD_MASK,JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_WR_MASK,"JESDABC_RX_GLUE_MEM_RD_MEM_TBL1");
			*/
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
		
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
		
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001c8, 0x000001c8, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");
		}

		else if (flow_params.jesdConfig.jesdUsecase == UC1D)
		{
		/* 	
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(1),0x00000020,0x00000020,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(1),0x00000220,0x00000220,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(2),0x00000040,0x00000040,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(3),0x00000060,0x00000060,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(2),0x00000440,0x00000440,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(3),0x00000660,0x00000660,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(4),0x00000080,0x00000080,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(5),0x000000a0,0x000000a0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(4),0x00000880,0x00000880,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(5),0x00000aa0,0x00000aa0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(6),0x000000c0,0x000000c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(7),0x000000e0,0x000000e0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(6),0x00000cc0,0x00000cc0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(7),0x00000ee0,0x00000ee0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(8),0x00000100,0x00000100,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(9),0x00000120,0x00000120,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(8),0x00001100,0x00001100,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(9),0x00001320,0x00001320,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(10),0x00000140,0x00000140,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(11),0x00000160,0x00000160,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(10),0x00001540,0x00001540,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(11),0x00001760,0x00001760,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(12),0x00000180,0x00000180,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(13),0x000001a0,0x000001a0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(12),0x00001980,0x00001980,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(13),0x00001ba0,0x00001ba0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(14),0x000001c0,0x000001c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(15),0x000001e0,0x000001e0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL1");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(14),0x00001dc0,0x00001dc0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(15),0x00001fe0,0x00001fe0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL1_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL1"); 

			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI,0x00000001,0x00000001,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_RD_MASK,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_WR_MASK,"JESD_JESDABC_RX_GLUE_RX_GLUE_SONI");
			//adding strm_cfg 0x000000e8
			
			//for (i=0; i <= 1; i++)
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(0),0x000001d0,0x000001d0,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(0),0x0000001f,0x0000001f,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			*/
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000020, 0x00000020, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000060, 0x00000060, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000a0, 0x000000a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000e0, 0x000000e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000120, 0x00000120, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000160, 0x00000160, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001a0, 0x000001a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001e0, 0x000001e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000220, 0x00000220, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000440, 0x00000440, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000660, 0x00000660, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000880, 0x00000880, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000aa0, 0x00000aa0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000cc0, 0x00000cc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000ee0, 0x00000ee0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001100, 0x00001100, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001320, 0x00001320, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001540, 0x00001540, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001760, 0x00001760, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001980, 0x00001980, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001ba0, 0x00001ba0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001dc0, 0x00001dc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001fe0, 0x00001fe0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001d0, 0x000001d0, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");
			
			

		}
		else if (flow_params.jesdConfig.jesdUsecase == UC0A)
		{	   
			/* 	
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(1),0x00000040,0x00000040,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(1),0x00000240,0x00000240,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(2),0x00000080,0x00000080,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(2),0x00000480,0x00000480,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(3),0x000000c0,0x000000c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(3),0x000006c0,0x000006c0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(4),0x00000100,0x00000100,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(4),0x00000900,0x00000900,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(5),0x00000140,0x00000140,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(5),0x00000b40,0x00000b40,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(6),0x00000180,0x00000180,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(6),0x00000d80,0x00000d80,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(7),0x000001c0,0x000001c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(7),0x00000fc0,0x00000fc0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");

			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI,0x00000001,0x00000001,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_RD_MASK,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_WR_MASK,"JESD_JESDABC_RX_GLUE_RX_GLUE_SONI");
			//adding strm_cfg 0x000000e8
			
			//for (i=0; i <= 1; i++)
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(0),0x000001c8,0x000001c8,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(0),0x0000003f,0x0000003f,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			*/ 
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000020, 0x00000020, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000060, 0x00000060, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000a0, 0x000000a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000e0, 0x000000e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000120, 0x00000120, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000160, 0x00000160, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001a0, 0x000001a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001e0, 0x000001e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000220, 0x00000220, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000440, 0x00000440, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000660, 0x00000660, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000880, 0x00000880, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000aa0, 0x00000aa0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000cc0, 0x00000cc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000ee0, 0x00000ee0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001100, 0x00001100, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001320, 0x00001320, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001540, 0x00001540, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001760, 0x00001760, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001980, 0x00001980, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001ba0, 0x00001ba0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001dc0, 0x00001dc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001fe0, 0x00001fe0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001d0, 0x000001d0, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");
			
		}
	  
		else if (flow_params.jesdConfig.jesdUsecase == UC1C)
		{	   
			/* 	
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(0),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(1),0x00000040,0x00000040,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(1),0x00000240,0x00000240,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(2),0x00000080,0x00000080,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(2),0x00000480,0x00000480,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(3),0x000000c0,0x000000c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(3),0x000006c0,0x000006c0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(4),0x00000100,0x00000100,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(4),0x00000900,0x00000900,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(5),0x00000140,0x00000140,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(5),0x00000b40,0x00000b40,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(6),0x00000180,0x00000180,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(6),0x00000d80,0x00000d80,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0(7),0x000001c0,0x000001c0,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_WR_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_WR_MEM_TBL0");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0(7),0x00000fc0,0x00000fc0,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_RD_MASK,JESD_JESDABC_RX_GLUE_RD_MEM_TBL0_WR_MASK,"JESD_JESDABC_RX_GLUE_RD_MEM_TBL0");

			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI,0x00000001,0x00000001,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_RD_MASK,JESD_JESDABC_RX_GLUE_RX_GLUE_SONI_WR_MASK,"JESD_JESDABC_RX_GLUE_RX_GLUE_SONI");
			//adding strm_cfg 0x000000e8
			
			//for (i=0; i <= 1; i++)
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(0),0x000001c8,0x000001c8,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(0),0x0000003f,0x0000003f,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_STRM_ID_EN(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_STRM_ID_EN_RD_MASK,JESD_JESDABC_RX_GLUE_STRM_ID_EN_WR_MASK,"JESD_JESDABC_RX_GLUE_STRM_ID_EN");
			write_read_expect(SRP_BLOCK_JESD_XIP_RX_GLUE, core_number,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG(1),0x00000000,0x00000000,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK,JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK,"JESD_JESDABC_RX_GLUE_MEM_STREAM_CFG");
			*/ 
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000020, 0x00000020, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000060, 0x00000060, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000a0, 0x000000a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000e0, 0x000000e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000120, 0x00000120, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000160, 0x00000160, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001a0, 0x000001a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001e0, 0x000001e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000220, 0x00000220, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000440, 0x00000440, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000660, 0x00000660, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000880, 0x00000880, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000aa0, 0x00000aa0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000cc0, 0x00000cc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000ee0, 0x00000ee0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001100, 0x00001100, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001320, 0x00001320, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001540, 0x00001540, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001760, 0x00001760, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001980, 0x00001980, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001ba0, 0x00001ba0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001dc0, 0x00001dc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001fe0, 0x00001fe0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001d0, 0x000001d0, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");
			

		}
	  
		else
		{
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000020, 0x00000020, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000060, 0x00000060, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000a0, 0x000000a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000e0, 0x000000e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000120, 0x00000120, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000160, 0x00000160, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001a0, 0x000001a0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001e0, 0x000001e0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000220, 0x00000220, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000440, 0x00000440, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000660, 0x00000660, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000880, 0x00000880, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000aa0, 0x00000aa0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000cc0, 0x00000cc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000ee0, 0x00000ee0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL8_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001100, 0x00001100, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL9_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001320, 0x00001320, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL10_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001540, 0x00001540, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL11_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001760, 0x00001760, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL12_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001980, 0x00001980, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL13_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001ba0, 0x00001ba0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL14_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001dc0, 0x00001dc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL15_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00001fe0, 0x00001fe0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");

			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
			
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000001d0, 0x000001d0, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_CFG0_OFFSET");
			write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG0_OFFSET");			
		}
	}
}

// JESD enable reg
static int program_enable_registers()
{
	int i,j = 0;
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	printf("JESD ENABLE : program_enable_registers \n");
	//for(i=0; i<sizeof(base_address_tx) / sizeof(base_address_tx[0]); i++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET");
	}
	//for(j=0; i<sizeof(base_address_rx) / sizeof(base_address_rx[0]); j++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET");
	}
}

static void configure_jesd_block()
{
	uint32_t tx_gb_empty_reg = 0;
	uint32_t tx_gb_full_reg = 0;
	uint32_t rx_gb_empty_reg = 0;
	uint32_t rx_gb_full_reg = 0;

	// function calls - Reg seq usecase
	program_rx_ip_registers();
	program_cmn_csr_registers();
	program_rx_glue_registers();


	printf("Giving delay of 10 milli seconds \n");
	delay(10);
	
	//enable rsb data capture
	//rsb freeze mode enabled, roshan 04/01/23
	write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_DATA_CAP_FRZ_EN_OFFSET, JESDABC_RX_GLUE_MEM_RSB_DATA_CAP_FRZ_EN_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_DATA_CAP_FRZ_EN_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_DATA_CAP_FRZ_EN_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_DATA_CAP_FRZ_EN_OFFSET");
	delay(10);
	//for rsb capture, the sequence is configure jesd with rsb capture enable, then start dnrt, then rx enable then check for
	//buffer full, then read from buffer.
	//However since for us we are configuring frio for data towards jesd as pci write and since sysref is final to enable jesd,
	//we are enabling jesd here itself and not part of 2nd test.
	program_enable_registers();

	int i,j=0;
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	
	
	for(i=0; i<1; i++)
	{
		tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}
	for(j=0; j<1; j++)
	{
		rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}

	printf(" Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
	printf(" Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
	printf(" Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
	printf(" Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);

	//program_enable_registers();
}

#define PARSEBUF 160
///
/**
* I2C:,rw,bus,address,NBYTES,{DATA}
* @param parg
* @param flow_ptr
* @return
*/

/* //roshan disabling for debug
int parseVexCnt( char* parg, struct flow_params_t *flow_ptr )
{
	int result=0;
	int i=0;
	int rr;
	int bus=0;
	int rtype=0;
	srp_uint64_t address;
	srp_uint32_t nBytes;
	srp_uint32_t nBytesRead=0;
	//	int slen=0;
	int vidx=0;
	srp_int32_t val=0x1;
	srp_uint8_t *vals;
	srp_dev_hdl_t devHdl=NULL;
	int ll;
	char *p;
	#if(0)
	const char *direction[2];
	direction[0] = "WRITE";
	direction[1] = "READ";
	#endif
	char buffer[PARSEBUF];
	//  ########## VEXCNT ######## 
	for (ll=0;ll<PARSEBUF;ll++)
	{
		buffer[ll]='\0';
	}
	printf("1022\n");
	printf("buffer is %s\n", buffer);
	printf("1024\n");
	printf("parg is %s\n", parg);
	strcpy(buffer, parg);
	p = strtok (buffer, ",");
	printf("1026\n");
	rr = strcmp(p, "VEXCNT:");
	printf("1028\n");
	if ( rr == 0 )
	{
		printf("1027\n");
		while ( p != NULL)
		{
			p = strtok (NULL, ",");

			if ( p != NULL )
			{
				switch (i)
				{
					case 0:
						// ### rType ### 
						flow_ptr->vexCount=atoi(p);
						if ( rtype >1)
						{
							printf("ERROR:, parseVexCnt,  Mode rtype=%d\n", rtype);
							return 1;
						}

						break;

					default:
						break;
				}
				i++;
			}
		}

	#if(0)
	printf("DEBUG:,parseVexCnt, rtype=%s, bus=%d, address=%lx, nBytes=%d,nBytesRead=%d {%d", direction[rtype] ,bus,address, nBytes,nBytesRead,vals[0] );
	for (int ll=1;ll<nBytesRead;ll++)
	{
		printf(",%d", vals[ll]);
	}
	printf("}\n");
	#endif
	result=2;
	}
	return result;
}

*/
///
/**
* I2C:,rw,bus,address,NBYTES,{DATA}
* @param parg
* @param flow_ptr
* @return
*/

/* //roshan disabling for debug
int parseNsipCnt( char* parg, struct flow_params_t *flow_ptr )
{
	int result=0;
	int i=0;
	int rr;
	int bus=0;
	int rtype=0;
	srp_uint64_t address;
	srp_uint32_t nBytes;
	srp_uint32_t nBytesRead=0;
	//	int slen=0;
	int nsipidx=0;
	srp_int32_t val=0x1;
	srp_uint8_t *vals;
	srp_dev_hdl_t devHdl=NULL;
	#if(0)
	const char *direction[2];
	direction[0] = "WRITE";
	direction[1] = "READ";
	#endif
	char buffer[PARSEBUF];
	char *p;
	int ll;
	int vidx=0;

	//  ########## VEXCNT ######## 
	for (ll=0;ll<PARSEBUF;ll++)
	{
		buffer[ll]='\0';
	}
	strcpy(buffer, parg);
	p = strtok (buffer, ",");
	rr = strcmp(p, "NSIPCNT:");
	if ( rr == 0 )
	{
		while ( p != NULL)
		{
			p = strtok (NULL, ",");

			if ( p != NULL )
			{
				switch (i)
				{
					case 0:
						// ### rType ### 
						flow_ptr->nsipCount=atoi(p);
						if ( rtype >1)
						{
							printf("ERROR:, parseNsipCnt,  Mode rtype=%d\n", rtype);
							return 1;
						}

						break;

					default:
						break;
				}
				i++;
			}
		}

	#if(0)
	printf("DEBUG:,parseVexCnt, rtype=%s, bus=%d, address=%lx, nBytes=%d,nBytesRead=%d {%d", direction[rtype] ,bus,address, nBytes,nBytesRead,vals[0] );
	for (int ll=1;ll<nBytesRead;ll++)
	{
		printf(",%d", vals[ll]);
	}
	printf("}\n");
	#endif
		result=2;
	}
	return result;
}

*/
/**
* Parse JESD parameters
* JESD:,
jesdUsecase: 3A,3B,3C,3D,4A,4B,4D,5A
Tx N & CS: 	0 - 160 default
1-  151
2-  142
Tx Rx FB Enable: 	001  	Tx En=0 & Rx En=0 & Fb En=1
010		Tx En=0 & Rx En=1 & Fb En=0	
011		Tx En=0 & Rx En=1 & Fb En=1
100		Tx En=1 & Rx En=0 & Fb En=0
101		Tx En=1 & Rx En=0 & Fb En=1
110		Tx En=1 & Rx En=1 & Fb En=0
111		Tx En=1 & Rx En=1 & Fb En=1

Bit Order=3;

TestMode: 	
0  Tx=0 Rx=0 Fb=0  Test mode off  
1  Tx=0 Rx=1 Fb=0  Short pattern Rx
2  Tx=1 Rx=1 Fb=1  Short Pattern  
3  Tx=1 Rx=0 Fb=1  Short pattern Tx 
4  Tx=3 Rx=0 Fb=3  Long pattern   


FEC & CRC :
00  Tx FEC=1 & CRC12=0  Rx FEC=1 & CRC12=0  - Tx FEC Rx FEC
01 	Tx FEC=0 & CRC12=1  Rx FEC=1 & CRC12=0  - Tx CRC Rx FEC
10	Tx FEC=1 & CRC12=0  Rx FEC=0 & CRC12=1  - Tx FEC Rx CRC
11	Tx FEC=0 & CRC12=1  Rx FEC=0 & CRC12=1  - Tx CRC Rx CRC

SH Error Threshold :
EMB Error Threshold :


**/
int parseJesd( char* parg, struct flow_params_t *flow_ptr )
{
	int result=0;
	int i = 0;
	int rr;
	char *ucnum;
	char buffer[PARSEBUF];
	int flag=0;
	int ll=0;
	for (ll=0;ll<PARSEBUF;ll++)
	{
		buffer[ll]='\0';
	}
	/*  ########## JESD ######## */
	if ( flow_ptr->jesdConfig.jesdUsecase == 0)
		ucnum = "0B";
	printf("DEBUG:,DEFAULT: Usecase=%s, N_CS=%d, TX_RX_FB En=%d, Testmode=%d, FEC_CRC=%d, Bit_order_Tx=%d, Bit_order_Rx=%d, SHErrTh= %d, EMBErrThr= %d\n", ucnum,  flow_ptr->jesdConfig.jesdTxncs, flow_ptr->jesdConfig.jesdEn, flow_ptr->jesdConfig.jesdTestmode, flow_ptr->jesdConfig.jesdFecCrc, flow_ptr->jesdConfig.jesdBitordertx,flow_ptr->jesdConfig.jesdBitorderrx, flow_ptr->jesdConfig.jesdShth, flow_ptr->jesdConfig.jesdEmbth );
	strcpy(buffer, parg);
	char *p = strtok (buffer, ",");
	char *ptr;
	i=0;
	int actstrlen=0;
	int iManipulate=1;
	rr = strcmp(p, "JESD:");
	int j = 0;
	int count=0;
	int k=0;
	if ( rr == 0 )
	{
		while ( p != NULL)
		{
			actstrlen+=strlen(p);		
			k=0;
			while( ((buffer[actstrlen+k]=='\0') && (buffer[actstrlen+k+1]==',') )
					|| ( (buffer[actstrlen+k]==',') && (buffer[actstrlen+k+1]==',') ) )
			{
				iManipulate++;
				i++;
				k++;
			}
			actstrlen+=iManipulate;
			iManipulate=1;
			p = strtok (NULL, ",");
			if ( p != NULL )
			{
				switch (i)
				{
					case 0:
						/* USECASE NUMBER */
						if(strcmp (p, "0B")==0 || strcmp (p, "0b") ==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC0B;
							ucnum="0B";
							vexCountStartIdxTbl_STRM2CIO[0]=0;
						}
						//roshan 30/11/23, replacing 1a with 5c
						else if(strcmp(p, "5C")==0 || strcmp (p, "5c")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC5C;
							ucnum="5C";
							vexCountStartIdxTbl_STRM2CIO[0]=1;
						}
						
						else if(strcmp (p, "1D")==0 || strcmp (p, "1d") ==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC1D;
							ucnum="1D";
							vexCountStartIdxTbl_STRM2CIO[0]=2;
						}
						else if(strcmp(p, "0A")==0 || strcmp (p, "0a")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC0A;
							ucnum="0A";
							vexCountStartIdxTbl_STRM2CIO[0]=3;
						}
						else if(strcmp(p, "1C")==0 || strcmp (p, "1c")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC1C;
							ucnum="1C";
							vexCountStartIdxTbl_STRM2CIO[0]=4;
						}
						else if(strcmp(p, "3D")==0 || strcmp (p, "3d")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC3D;	
							ucnum="3D";
						}
						else if(strcmp(p, "4A")==0 || strcmp (p, "4a")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC4A;	
							ucnum="4A";
						}
						else if(strcmp(p, "4B")==0 || strcmp (p, "4b")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC4B;	
							ucnum="4B";
						}
						else if(strcmp(p, "4D")==0 || strcmp (p, "4d")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC4D;	
							ucnum="4D";
						}
						else if(strcmp(p, "5A")==0 || strcmp (p, "5a")==0)
						{ 
							flow_ptr->jesdConfig.jesdUsecase=UC5A;
							ucnum="5A";
						}
						else
						{
							printf("ERROR:, parseJESD. Usecase number value out of range. Usecase number=%s\n",p);
							ucnum = p;
							return 1;
						}
						break;
					case 1:
						/*Value of N & CS*/
						flow_ptr->jesdConfig.jesdTxncs = atoi(p);
						if ( flow_ptr->jesdConfig.jesdTxncs < 0 ||  flow_ptr->jesdConfig.jesdTxncs > 2)
						{
							printf("ERROR:, parseJESD. N_CS value out of range. N_CS=%d\n",flow_ptr->jesdConfig.jesdTxncs);
							return 1;
						}
						break;
					case 2:
						/*Tx,Rx or Fb En*/
						flow_ptr->jesdConfig.jesdEn = atoi(p);
						if ( flow_ptr->jesdConfig.jesdEn == 000)
						{
							printf("ERROR:, parseJESD. Invalid Value of Enable. En=%d\n",flow_ptr->jesdConfig.jesdEn);
							return 1;
						}
						break;
					case 3: 
						/* Test Mode */
						flow_ptr->jesdConfig.jesdTestmode = atoi(p);
						if ( flow_ptr->jesdConfig.jesdTestmode < 0 && flow_ptr->jesdConfig.jesdTestmode > 4)
						{
							printf("ERROR:, parseJESD. Testmode value out of range. Testmode=%d\n",flow_ptr->jesdConfig.jesdTestmode);
							return 1;
						}
						break;
					case 4:
						/* FEC CRC */
						flow_ptr->jesdConfig.jesdFecCrc = atoi(p);
						if ( flow_ptr->jesdConfig.jesdFecCrc != 0 && flow_ptr->jesdConfig.jesdFecCrc != 1 && flow_ptr->jesdConfig.jesdFecCrc != 2 && flow_ptr->jesdConfig.jesdFecCrc != 3)
						{
							printf("ERROR:, parseJESD. FEC_ CRC value out of range. FEC_CRC=%d\n",flow_ptr->jesdConfig.jesdFecCrc);
							return 1;
						}
						break;
					case 5:
						/* Bit Order Tx */
						flow_ptr->jesdConfig.jesdBitordertx = atoi(p);
						if ( flow_ptr->jesdConfig.jesdBitordertx < 0 && flow_ptr->jesdConfig.jesdBitordertx > 7)
						{
							printf("ERROR:, parseJESD. Bit Order Tx value out of range. BitOrdertx=%d\n",flow_ptr->jesdConfig.jesdBitordertx);
							return 1;
						}
						break;
					case 6:
						/* Bit Order Rx */
						flow_ptr->jesdConfig.jesdBitorderrx = atoi(p);
						if ( flow_ptr->jesdConfig.jesdBitorderrx < 0 && flow_ptr->jesdConfig.jesdBitorderrx > 7)
						{
							printf("ERROR:, parseJESD. Bit Order rx value out of range. BitOrderrx=%d\n",flow_ptr->jesdConfig.jesdBitorderrx);
							return 1;
						}
						break;
					case 7:
						/* SH Error Threshold */
						flow_ptr->jesdConfig.jesdShth = atoi(p);
						if ( flow_ptr->jesdConfig.jesdShth == 0 )
						{
							printf("ERROR:, parseJESD. Invalid Value of SH Error Threshold. ShErrThr=%d\n",flow_ptr->jesdConfig.jesdShth);
							return 1;
						}
						break;
					case 8:
						/* EMB Error Threshold */
						flow_ptr->jesdConfig.jesdEmbth = atoi(p);
						if ( flow_ptr->jesdConfig.jesdEmbth == 0 )
						{
							printf("ERROR:, parseJESD. Invalid Value of EMB Error Threshold. EMBErrThr=%d\n",flow_ptr->jesdConfig.jesdEmbth);
							return 1;
						}
						i=-1;
						break;
				}
				flag=1;
				i++;
			}
		}
		printf("DEBUG:,POST: Usecase=%s, N_CS=%d, TX_RX_FB En=%d, Testmode=%d, FEC_CRC=%d, Bit_order_Tx=%d, Bit_order_Rx=%d, SHErrTh= %d, EMBErrThr= %d\n", ucnum, flow_ptr->jesdConfig.jesdTxncs, flow_ptr->jesdConfig.jesdEn, flow_ptr->jesdConfig.jesdTestmode, flow_ptr->jesdConfig.jesdFecCrc, flow_ptr->jesdConfig.jesdBitordertx,flow_ptr->jesdConfig.jesdBitorderrx, flow_ptr->jesdConfig.jesdShth, flow_ptr->jesdConfig.jesdEmbth );
	}
	return result;
}

/**
* Parse command line options of the form OPT:
* This is called my main with the command line positional arguments
* @param carg - Single option
* @param flow_ptr - Parameters
* @return
*/

/*
int  parseOpts( char* carg, struct flow_params_t *flow_ptr )
{
	int rr=0;
	printf("parseOpts\n");
	rr=parseVexCnt(  carg, flow_ptr )|rr;
	rr=parseNsipCnt(  carg, flow_ptr )|rr;
	rr=parseJesd(  carg, flow_ptr )|rr;
	if ((rr !=0) && (rr !=2))
	{
		printf("ERROR:, Parsing command line option, {%s}\n",carg);
		rr=-1;
	}
	return rr;
}
*/

void assign_defaults(struct flow_params_t *flow_ptr)
{
	flow_ptr->vexCount = 1; 
	flow_ptr->nsipCount = 1;

	/*JESD */
	flow_ptr->jesdConfig.jesdUsecase	=	UC5C;
	flow_ptr->jesdConfig.jesdTxncs		=	0;
	flow_ptr->jesdConfig.jesdEn		    =	111;
	flow_ptr->jesdConfig.jesdTestmode	=	0;
	flow_ptr->jesdConfig.jesdFecCrc		=	0;
	flow_ptr->jesdConfig.jesdBitordertx	=	0;
	flow_ptr->jesdConfig.jesdBitorderrx	=	3;
	flow_ptr->jesdConfig.jesdShth		=	9;
	flow_ptr->jesdConfig.jesdEmbth		=	9;
}

//For RX 27/10/23

int
main(int argc, const char *argv[])
{
	int rv = 0;
	int flags = 0;
	void *vex_hdl;
	srp_vex_config_t vex_params;
	srp_vex_t srp_vex_hdl;
	int lc, i, j;
	int vexId[40], nsipId[2], apb_num, host_flag = 1, cm_num = 0, port_num = 0;
	volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
	int total_streams_0 = 8;
	int total_streams_1 = 16;
	int dmem_offset = 0x4000;

	int vex_rx_offset_val[] = {HIVE_ADDR_jesd_rx_g_num_vecs_in, HIVE_ADDR_jesd_rx_g_tbs_in_blk};
	unsigned vex_rx_val_kargs_tbl[] = {128, 4};

	/* //roshan 30/11/23, these codes are for tx path, start1
	int vex_tx_offset_val[] = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,
		HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
		HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
		HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base,
		HIVE_ADDR_jesd_tx_g_timeout_cycles};

	//Added for U-1A
	unsigned v1_vex_tx_val_kargs[] = {0x00000, 0x20000,
								   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,1024};
	//Added for U-0B
	unsigned v2_vex_tx_val_kargs[] = {0x00000, 0x20000,
								   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,
								   2048};
	unsigned v2_vex_tx_val_kargs_1[] = {0x100000, 0x120000,
								   0x140000, 0x160000,
								   0x180000, 0x1A0000,
								   0x1C0000, 0x1E0000,
								   2048};

	//Added for U-1D
	unsigned vex_tx_val_kargs[] = {0x00000, 0x20000,
								   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,
								   1024};
	unsigned vex_tx_val_kargs_1[] = {0x100000, 0x120000,
								   0x140000, 0x160000,
								   0x180000, 0x1A0000,
								   0x1C0000, 0x1E0000,
								   1024};
								   
	//Added for U-0A
	unsigned v1_vex_tx_val_kargs1[] = {0x00000, 0x20000,
								   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,4096};
								   
	//Added for U-1C
	unsigned v1_vex_tx_val_kargs2[] = {0x00000, 0x20000,
								   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,4096};
								   
								   

	//Added for U-1A,U-0B,U-1D	
	unsigned *vex_tx_val_kargs_tbl[7]={ v1_vex_tx_val_kargs, v1_vex_tx_val_kargs1, v1_vex_tx_val_kargs2,
	v2_vex_tx_val_kargs, v2_vex_tx_val_kargs_1, v2_vex_tx_val_kargs, v2_vex_tx_val_kargs_1 
																}; 


	unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
		HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
		HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
		HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
		
	*/ //roshan end1


	unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
	unsigned int add_val[1];
	//Added for U-1A,U-0B,U-1D
	unsigned int vex_start_stop[7][2]={	{0,8},{0,8},{0,8},
						{0,8},{8,16},{0,8},{8,16} 
					};
	int rr=0;
	int vexIdx;
	int k=0;

	int vexCount = 1;
	int nsipCount = 1;
	printf("Number of command-line arguments: %d\n", argc);

	printf("Command-line arguments:\n");
	for (i = 0; i < argc-1; i++) {
		printf("1313\n");
		if (argv[i] != NULL) {
			printf("argv[%d] = %s\n", i, argv[i]);
		} else {
			printf("argv[%d] is NULL\n", i);
		}
		printf("1319\n");
	}

	assign_defaults(&flow_params);

	/*
	optind=0;
	for(; optind < argc-1; optind++)
	{
		rr = parseOpts( argv[optind],  &flow_params )|rr;
	}
	*/

	init(); // Initialize the srp
	//subsys_reset_cycle();

	//vex_reset_cycle();  //commenting line, as this test is only for rsb capture, roshan 04/12/23
	//jesd_reset_cycle();
	crux_reset_cycle();

	sleep(2);
	//system("source jesd_config.sh"); //vijay

	LOG_PRINT("INFO: logger beginning\n");

	 //STRM2CIO = 1;
	vexCount = flow_params.vexCount;
	printf("Vex count is %d\n", vexCount);
	//for(i=0; i<vexCount; i++)
	for (j=0, i = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; i < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; j++, i++)
	{
		// vexId[i] = i - vexCountStartIdxTbl_STRM2CIO[vexCount-1];
		vexId[i] = j;
	}

	//vexCount = 1;
	vexCount = flow_params.vexCount;
	printf("Vex count is %d\n", vexCount);
	//for(i=0; i<vexCount; i++)
	/*
	for (j=0, i = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; i < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; j++, i++)
	{
		// vexId[i] = i - vexCountStartIdxTbl_CIO2STRM[vexCount-1];
		vexId[i] = j;
	}
	 */
	nsipCount = 1;  //roshan uncommenting for debug 01/12/23
	nsipCount = flow_params.nsipCount;
	printf("Nsip count is %d\n", nsipCount);
	for(i=0; i<nsipCount; i++)
	{
		nsipId[i] = i;
	}

	port_num= 0;
	apb_num = 0;
	cm_num = 0;
	printf("vex id: %d , nsipId : %d , apb_num: %d, cm_num: %d\n",vexId[0], nsipId, apb_num, cm_num);

	memset(&vex_params, 0, sizeof(vex_params));
	memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

	//if (rv = o_configure_jesd_host(vexCount, vexId, nsipId, apb_num, cm_num))
		
	/*  //roshan 04/12/23, commenting as this test is only for rsb capture
	if (rv = configure_jesd_host(vexCount, vexId, nsipCount, nsipId, apb_num, cm_num)) 
	{
		printf ("ERROR: configure_jesd_host\n");
		return rv;
	}
	*/
	vex_hdl = &srp_vex_hdl;

	if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
		return rv;

	//resetting the VEC NOC
	if (rv = release_reset_abc_noc(srp))
	{
		printf("ERROR: reset_abc failed\n");
		return rv;
	}
	 //Added on 27/10/23
	 //FOR STRM2CIO
	 printf("Host: start STRM2CIO rx program load \n");

	// loading applicable only while using start, roshan 01/12/23
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
	{
		if ((rv = srp_vex_loader(vex_hdl, vexId[vexIdx], "vex_fw/sim_m64/jesd_rx.fw")))
			return rv;
	}

	printf("Host: STRM2CIO program load - done\n");

	printf("Host: start vex rx program load \n");

	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	/*
	for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
	{
		if ((rv = srp_vex_loader(vex_hdl, vexId[vexIdx], "vex_fw/sim_m64/jesd_tx.fw")))
			return rv;
	}

	printf("Host: vex program load - done\n");
	*/
	 // FOR STRM2CIO added on 27/10/23
	 // Loading the host parameters to STRM2CIO  Rx core
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
	{
		for (lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
		{
			if ((rv = srp_dev_block_write32(srp,
							SRP_BLOCK_VEX_CORE,
							vexId[vexIdx],
							dmem_offset + vex_rx_offset_val[lc],
							&vex_rx_val_kargs_tbl[lc],
							1,
							flags)))
				return rv;
			//sleep(1);
		}   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends
	}

	// Loading the host parameters to VEX_0  Rx core
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	/*
	for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
	{
		for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++)
		{
			if ((rv = srp_dev_block_write32(srp,
							SRP_BLOCK_VEX_CORE,
							vexId[vexIdx],
							dmem_offset + vex_tx_offset_val[lc],
							&vex_tx_val_kargs_tbl[vexIdx][lc],
							1,
							flags)))
				return rv;
			//sleep(1);
		}   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends
	}
	*/
	printf("Vijay 1\n");
	/*
	 //STRM2CIO added on 27/10/23
	 // Input Vector Generation STRM2CIO
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
	{
		for (lc = vex_start_stop[vexIdx][0]; lc < vex_start_stop[vexIdx][1] ; lc++)
		{
			for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
			{
				for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
				{
					val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
					val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
					val_inp[i][j] = val_inp[i][j] | (lc << 28 | lc << 12);
					//val_inp[i][j] = 0xb2b2a5a5;

				}
			}

			if ((rv = srp_vex_memid_store(vex_hdl,
							vexId[vexIdx],
							SRP_VEX_VMEM,
							vex_tx_buffer_addr[lc - vex_start_stop[vexIdx][0]],//local_addr
							val_inp[0],
							(NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
				return rv;
		}

	}
	*/
	// Input Vector Generation VEX_1
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	/*
	for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
	{
		for (lc = vex_start_stop[vexIdx][0]; lc < vex_start_stop[vexIdx][1] ; lc++)
		{
			for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
			{
				for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
				{
					val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
					val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
					val_inp[i][j] = val_inp[i][j] | (lc << 28 | lc << 12);
					//val_inp[i][j] = 0xb2b2a5a5;

				}
			}

			if ((rv = srp_vex_memid_store(vex_hdl,
							vexId[vexIdx],
							SRP_VEX_VMEM,
							vex_tx_buffer_addr[lc - vex_start_stop[vexIdx][0]],//local_addr
							val_inp[0],
							(NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
				return rv;
		}

	}
	*/
	printf("Vijay 2\n");
	/*
	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
	{
		printf("Host: vex %d program start\n",vexIdx);
		srp_vex_start(vex_hdl, vexId[vexIdx], 0); // vex_0 start
	}
	*/
	// STR2CIO 27/10/23

	/* // needed only while checking data integrity, roshan 01/12/23
	for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
	{
		printf("Host: vex %d program start\n",vexIdx);
		srp_vex_start(vex_hdl, vexId[vexIdx], 0); // STRM2CIO start 
	}
	*/
	configure_jesd_block();

	printf("Host: vex program start - done\n");

	//Signal VEX_0 to start continuous flow

	//for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
	/*
	for (vexIdx = vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_CIO2STRM[vexCount-1]; vexIdx++)
	{
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE,
						vexId[vexIdx],
						dmem_offset + HIVE_ADDR_jesd_tx_g_host_indicator,
						&host_flag,
						1,
						flags)))
			return rv;
	}
	*/
	//STRM2CIO added on 27/10/23

	/* //roshan 30/11/23, not needed for rx path, start1
	for (vexIdx = vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl_STRM2CIO[vexCount-1]; vexIdx++)
	{
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE,
						vexId[vexIdx],
						dmem_offset + HIVE_ADDR_jesd_tx_g_host_indicator,
						&host_flag,
						1,
						flags)))
			return rv;
	}
	*/ //end1

	//Signal VEX_1 to start continuous flow

	//system("srpRamTest -s 64KB -W 0x63.0.0x30000 0"); // Vijay: Just for testing, remove it
	
	delay(2000);
	//===========================================================================
	//enable sysref
	system("frioPciWrite -F s5a3 -P 0x20000 0x02");
	system("frioPciWrite -F s5a1 -P 0x20000 0x90");
	system("frioPciWrite -F s5b1 -P 0x20000 0x90");
	printf("SYSREF Done\n");
	delay(1000);
	//===========================================================================
	//dumping error registers and dumping 8 streams of rsb
	printf("Hello from roshan\n");
	uint32_t read_value;
	extern void * srp;
	uint32_t error = 0;
	uint32_t write_status = 0;
	uint32_t dev_id =0;
    uint32_t dev_flags = 0;

	uint32_t value24 = 0;
	uint32_t value25 = 0;
	uint32_t value26 = 0;
	uint32_t value27 = 0;
    uint32_t value28 = 0;
	uint32_t value29 = 0;
	uint32_t value30 = 0;
	uint32_t value31 = 0;
	uint32_t value32 = 0;
	uint32_t value33 = 0;
    uint32_t value34 = 0;
	uint32_t value35 = 0;
	uint32_t value36 = 0;
	uint32_t value37 = 0;
	uint32_t value38 = 0;
	uint32_t value39 = 0;
	uint32_t value40 = 0;
	uint32_t value41 = 0;
	uint32_t value42 = 0;
	uint32_t value43 = 0;
	uint32_t value44 = 0;
	uint32_t value45 = 0;
	uint32_t stream0_buffer = 0;
	uint32_t stream1_buffer = 0;
	uint32_t stream2_buffer = 0;
	uint32_t stream3_buffer = 0;
	uint32_t stream4_buffer = 0;
	uint32_t stream5_buffer = 0;
	uint32_t stream6_buffer = 0;
	uint32_t stream7_buffer = 0;
	uint32_t stream8_buffer = 0;
	uint32_t stream9_buffer = 0;
	uint32_t stream10_buffer = 0;
	uint32_t stream11_buffer = 0;
	uint32_t stream12_buffer = 0;
	uint32_t stream13_buffer = 0;
	uint32_t stream14_buffer = 0;
	uint32_t stream15_buffer = 0;
	
	uint32_t value   = 0;
	uint32_t value1   = 0;
	uint32_t value2  = 0;
	uint32_t value3  = 0;
	uint32_t value4  = 0;
	uint32_t value5  = 0;
	uint32_t value6  = 0;
	uint32_t value7  = 0;
	uint32_t value8  = 0;
	uint32_t value9  = 0;
	uint32_t value10 = 0;
	uint32_t value11 = 0;
	uint32_t value12 = 0;
	uint32_t value13 = 0;
	uint32_t value14 = 0;
	uint32_t value15 = 0;
	uint32_t value16 = 0;
	uint32_t value17 = 0;
	uint32_t value18 = 0;
	uint32_t value19 = 0;
	uint32_t value20 = 0;
	uint32_t value21 = 0;
	uint32_t value22 = 0;
	uint32_t value23 = 0;
	
	srp_dev_open(dev_id, dev_flags, &srp);
	
	i,j=0;
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	
	
	for(i=0; i<1; i++)
	{
		value24 = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		value25 = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}
	for(j=0; j<1; j++)
	{
		value26 = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		value27 = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}
	
	printf("\n\n");
	printf("Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", value24);
	printf("Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", value25);
	printf("Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", value26);
	printf("Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", value27);
    
	value28  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
	//value29  = read_reg_18a(base_address_rx[1] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
	//value30  = read_reg_18a(base_address_rx[2] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
	//value31  = read_reg_18a(base_address_rx[3] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
	value32  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
	//value33  = read_reg_18a(base_address_rx[1] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
	//value34  = read_reg_18a(base_address_rx[2] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
	//value35  = read_reg_18a(base_address_rx[3] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
	value36  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
	value37  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
	
	//old api
	//srp_dev_read32(devHdl, regionId, JESD_RX_MEM_JL_EMB_LOCK_STATUS_REG, &value30);
	
	//printf("Present value of SH lock of Link0, Link1, Link2 and Link3 are %d %d %d %d \n",value28,value29,value30,value31);
	//printf("Present value of EMB lock of Link0, Link1, Link2 and Link3 are %d %d %d %d \n",value32,value33,value34,value35);
	printf("\n\n");
	printf("Present value of SH lock of Link0 is 0x%x \n",value28);
	printf("Present value of EMB lock of Link0 is 0x%x \n",value32);
	printf("Present value of SH lock loss of Link0 is 0x%x \n",value36);
	printf("Present value of EMB lock loss of Link0 is 0x%x \n",value37);
	
	i=0;
	j=0;
	for(i=0; i<1; i++)
	{
		value   = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE0_OFFSET, "ICOUNTER_REPORT_LANE0");
		value1  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE1_OFFSET, "ICOUNTER_REPORT_LANE1");
		value2  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE2_OFFSET, "ICOUNTER_REPORT_LANE2");
		value3  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE3_OFFSET, "ICOUNTER_REPORT_LANE3");
		value4  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE4_OFFSET, "ICOUNTER_REPORT_LANE4");
		value5  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE5_OFFSET, "ICOUNTER_REPORT_LANE5");
		value6  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE6_OFFSET, "ICOUNTER_REPORT_LANE6");
		value7  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE7_OFFSET, "ICOUNTER_REPORT_LANE7");
		value8  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE8_OFFSET, "ICOUNTER_REPORT_LANE8");
		value9  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE9_OFFSET, "ICOUNTER_REPORT_LANE9");
		value10 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE10_OFFSET, "ICOUNTER_REPORT_LANE10");
		value11 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE11_OFFSET, "ICOUNTER_REPORT_LANE11");
		value12 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE12_OFFSET, "ICOUNTER_REPORT_LANE12");
		value13 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE13_OFFSET, "ICOUNTER_REPORT_LANE13");
		value14 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE14_OFFSET, "ICOUNTER_REPORT_LANE14");
		value15 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE15_OFFSET, "ICOUNTER_REPORT_LANE15");
		value16 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE16_OFFSET, "ICOUNTER_REPORT_LANE16");
		value17 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE17_OFFSET, "ICOUNTER_REPORT_LANE17");
		value18 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE18_OFFSET, "ICOUNTER_REPORT_LANE18");
		value19 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE19_OFFSET, "ICOUNTER_REPORT_LANE19");
		value20 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE20_OFFSET, "ICOUNTER_REPORT_LANE20");
		value21 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE21_OFFSET, "ICOUNTER_REPORT_LANE21");
		value22 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE22_OFFSET, "ICOUNTER_REPORT_LANE22");
		value23 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE23_OFFSET, "ICOUNTER_REPORT_LANE23");
		value26 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		value27 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}
	
	for(j=0; j<1; j++)
	{
		value24 = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		value25 = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}		
	printf("\n");
	printf("\n");
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE0  is 0x%x \n",  value);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE1  is 0x%x \n",  value1);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE2  is 0x%x \n",  value2);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE3  is 0x%x \n",  value3);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE4  is 0x%x \n",  value4);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE5  is 0x%x \n",  value5);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE6  is 0x%x \n",  value6);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE7  is 0x%x \n",  value7);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE8  is 0x%x \n",  value8);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE9  is 0x%x \n",  value9);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE10 is 0x%x \n", value10);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE11 is 0x%x \n", value11);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE12 is 0x%x \n", value12);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE13 is 0x%x \n", value13);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE14 is 0x%x \n", value14);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE15 is 0x%x \n", value15);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE16 is 0x%x \n", value16);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE17 is 0x%x \n", value17);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE18 is 0x%x \n", value18);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE19 is 0x%x \n", value19);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE20 is 0x%x \n", value20);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE21 is 0x%x \n", value21);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE22 is 0x%x \n", value22);
	printf(" After Jesd enable value for ICOUNTER_REPORT_LANE23 is 0x%x \n", value23);
	printf(" After Jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", value24);
	printf(" After Jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", value25);
	printf(" After Jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", value26);
	printf(" After Jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", value27);

	delay(1000);
	//going to dump RSB 8 streams
	//=====================================
	//=====================================
	int fill_level0 = 0;
	int fill_level1 = 0;
	int fill_level2 = 0;
	int fill_level3 = 0;
	int fill_level4 = 0;
	int fill_level5 = 0;
	int fill_level6 = 0;
	int fill_level7 = 0;
	i = 0;
	int flit_count = 0;
	int loop_count = 0;
	while(loop_count < 1)
	{
		printf("#######loop_count is %d\n",loop_count);
		//------------------0
		value38 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS0_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS0");
		fill_level0 = (value38 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS0 register value is 0x%x \n", value38);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS0 register or fill status of rsb buffer value is 0x%x \n", fill_level0);
		if(fill_level0 == 0)
		{
			printf("#######buffer 0 is not full\n");
		}
		else
		{
			printf("###############buffer 0 is full\n");
			
			//below 2 registers are programmed in first test for rsb capture
			printf("###RSB buffer0 0-4 flits for stream0 \n");
			//for(flit_count=0; flit_count<64; flit_count++)
			for(flit_count=0; flit_count<4; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//-------------------------------------1
		value39 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS1_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS1");
		fill_level1 = (value39 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS1 register value is 0x%x \n", value39);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS1 register or fill status of rsb buffer value is 0x%x \n", fill_level1);
		if(fill_level1 == 0)
		{
			printf("#######buffer 1 is not full\n");
		}
		else
		{
			printf("###############buffer 1 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer1 64-68 flits for stream1 \n");
			//for(flit_count=64; flit_count<128; flit_count++)
			for(flit_count=64; flit_count<68; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//-------------------------------------2
		value40 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS2_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS2");
		fill_level2 = (value40 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS2 register value is 0x%x \n", value40);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS2 register or fill status of rsb buffer value is 0x%x \n", fill_level2);
		if(fill_level2 == 0)
		{
			printf("#######buffer 2 is not full\n");
		}
		else
		{
			printf("###############buffer 2 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer2 128-132 flits for stream2 \n");
			//for(flit_count=128; flit_count<192; flit_count++)
			for(flit_count=128; flit_count<132; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		//-------------------------------------3
		value41 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS3_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS3");
		fill_level3 = (value41 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS3 register value is 0x%x \n", value41);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS3 register or fill status of rsb buffer value is 0x%x \n", fill_level3);
		if(fill_level3 == 0)
		{
			printf("#######buffer 3 is not full\n");
		}
		else
		{
			printf("###############buffer 3 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer3 192-196 flits for stream3 \n");
			//for(flit_count=192; flit_count<256; flit_count++)
			for(flit_count=192; flit_count<196; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		//-------------------------------------4
		value42 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS4_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS4");
		fill_level4 = (value42 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS4 register value is 0x%x \n", value42);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS4 register or fill status of rsb buffer value is 0x%x \n", fill_level4);
		if(fill_level4 == 0)
		{
			printf("#######buffer 4 is not full\n");
		}
		else
		{
			printf("###############buffer 4 is full\n");
			flit_count = 0;
			printf("###RSB buffer4 256-260 flits for stream4 \n");
			//for(flit_count=256; flit_count<320; flit_count++)
			for(flit_count=256; flit_count<260; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		//-------------------------------------5
		value43 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS5_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS5");
		fill_level5 = (value43 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS0 register value is 0x%x \n", value43);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS5 register or fill status of rsb buffer value is 0x%x \n", fill_level5);
		if(fill_level5 == 0)
		{
			printf("#######buffer 5 is not full\n");
		}
		else
		{
			printf("###############buffer 5 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer5 320-324 flits for stream5 \n");
			//for(flit_count=320; flit_count<384; flit_count++)
			for(flit_count=320; flit_count<324; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		//-------------------------------------6
		value44 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS6_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS6");
		fill_level6 = (value44 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS0 register value is 0x%x \n", value44);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS6 register or fill status of rsb buffer value is 0x%x \n", fill_level6);
		if(fill_level6 == 0)
		{
			printf("#######buffer 6 is not full\n");
		}
		else
		{
			printf("###############buffer 6 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer6 384-388 flits for stream6 \n");
			//for(flit_count=384; flit_count<448; flit_count++)
			for(flit_count=384; flit_count<388; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		//-------------------------------------7
		value45 = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_STRM_MEM_STS7_OFFSET, "JESDABC_RX_GLUE_MEM_STRM_MEM_STS7");
		fill_level7 = (value45 && 0x400);
		printf("#######JESDABC_RX_GLUE_MEM_STRM_MEM_STS7 register value is 0x%x \n", value45);
		printf("#######10th bit of JESDABC_RX_GLUE_MEM_STRM_MEM_STS7 register or fill status of rsb buffer value is 0x%x \n", fill_level7);
		if(fill_level7 == 0)
		{
			printf("#######buffer 7 is not full\n");
		}
		else
		{
			printf("###############buffer 7 is full\n");
			
			flit_count = 0;
			printf("###RSB buffer7 448-452 flits for stream1 \n");
			//for(flit_count=448; flit_count<512; flit_count++)
			for(flit_count=448; flit_count<452; flit_count++)
			{
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_INDIR_ADDR_OFFSET");
				write_read_expect_18a(JESDABC_M0_RX_GLUE_BASE+JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_DEFAULT, 0x01, 0x01, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_RX_GLUE_MEM_RSB_WR_RD_CTL_OFFSET");
				stream0_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA0");
				stream1_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA1");
				stream2_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA2");
				stream3_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA3");
				stream4_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA4");
				stream5_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA5");
				stream6_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA6");
				stream7_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA7");
				stream8_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA8");
				stream9_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA9");
				stream10_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA10");
				stream11_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA11");
				stream12_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA12");
				stream13_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA13");
				stream14_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA14");
				stream15_buffer = read_reg_18a(JESDABC_M0_RX_GLUE_BASE + JESDABC_RX_GLUE_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_RX_GLUE_MEM_RSB_RD_DATA15"); 
				printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
			}
		}
		//---------------------------------------
		loop_count = loop_count + 1;
	}
	//=====================================
	//=====================================
	return rv;
}   // main ends


