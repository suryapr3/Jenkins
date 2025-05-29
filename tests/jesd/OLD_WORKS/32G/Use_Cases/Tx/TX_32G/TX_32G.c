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

 * @file    dnrt_jesd_vex_rx_path_usecases_19_02_24.c

 * @brief   HOST Configuration code for sending the data from VEX to JESD and receving it back.
 
 * @details 1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
               and receving it back to VEX for all the Sample Rates
               
            2. Evaluate the result written by VEX for the test case evaluation.
            
 * @todo    1. 32K samples (1K vectors) for given data rate will be streamed to JESD from
               configured VEX core.
               
            2. With JESD NSIP loop back enabled the data looped back at sample interface
               was expected to reach the other VEX core where comparison will be performed.
           
            3. VEX core on which comparison algo was running will update the comparison result for
               every vector comparison and once the total 1K vector comparison was done HOST will
               read the result.
           
            4. Host will be waiting on a memory location where VEX will update the number of vectors
               it was processed.

 */

/*********************************************** 

 * LOCAL INCLUDE STATEMENTS                    * 

 ***********************************************/ 
#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"
#include "common_functions.h"
#include "nsip_hbi.h"
#include "ve32_cell.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include<time.h> 
#include "vex_fw/sim_m64/jesd_tx.map.h"

#define prefil_tsb_to_zero         0
#define tsb_capture_enabled        0
#define tsb_dump_enabled           0

#define prefill_rsb_zero		   0
#define dump_rsb_valid			   0
#define enable_rsb_cap			   0 

#define jesd_tx_to_rx_lpbk_en      0


/*********************************************** 

 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     * 

 ***********************************************/ 
//16G: 8 stream UC's->UC5C,UC2B,UC3B; 4 stream UC's->UC3A, UC7C; 16 stream UC's->UC2C,UC3D
//32G: 8 stream UC's->UC5E,UC3C,UC7G; 4 stream UC's->UC5B,UC7E,UC9C; 2 stream UC's->UC7B,UC9B,UC11C; 1 stream UC's->UC9A,UC11A,UC13A; 16 stream UC's->UC3E,UC5F
enum jesdUsecasenum{UC5C,UC2B,UC2C,UC3A,UC3B,UC3D,UC7C,UC5E,UC3C,UC7G,UC5B,UC7E,UC9C,UC7B,UC9B,UC11C,UC9A,UC11A,UC13A,UC3E,UC5F};

typedef struct jesdConfig_t 
{
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

struct  flow_params_t 
{
    int vexCount;
    int nsipCount;
    jesdConfig_t jesdConfig;
}flow_params;

static int vexCountStartIdxTbl_CIO2STRM[2]; //CIO2STRM table 

typedef struct register_config_tbl_s 
{
    uint32_t offset;
    uint32_t value;
    uint32_t mask;
    char *name;
} register_config_tbl_t;

/*********************************************** 

 * STATIC VARIABLES                            * 

 ***********************************************/ 
static int vexCountStartIdxTbl_STRM2CIO[2]; 

 
fpga_clk_and_sysref_period()
{ 
    if (flow_params.jesdConfig.jesdUsecase == UC5E || flow_params.jesdConfig.jesdUsecase == UC3C || flow_params.jesdConfig.jesdUsecase == UC7G || flow_params.jesdConfig.jesdUsecase == UC5B || flow_params.jesdConfig.jesdUsecase == UC7E || flow_params.jesdConfig.jesdUsecase == UC9C || flow_params.jesdConfig.jesdUsecase == UC7B || flow_params.jesdConfig.jesdUsecase == UC9B || flow_params.jesdConfig.jesdUsecase == UC11C || flow_params.jesdConfig.jesdUsecase == UC11A || flow_params.jesdConfig.jesdUsecase == UC3E || flow_params.jesdConfig.jesdUsecase == UC5F)
    {
        system("frioPciWrite -F s5a1 -P 0x20000 0x14");
		system("frioPciWrite -F s5b1 -P 0x20000 0x14");
		system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
		system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
    }
    else if (flow_params.jesdConfig.jesdUsecase == UC9A || flow_params.jesdConfig.jesdUsecase == UC13A )
    {
        system("frioPciWrite -F s5a1 -P 0x20000 0x4");
		system("frioPciWrite -F s5b1 -P 0x20000 0x4");
		system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
		system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
    }
    else
    {
        system("frioPciWrite -F s5a1 -P 0x20000 0x14");
		system("frioPciWrite -F s5b1 -P 0x20000 0x14");
		system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
		system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");
    }

	//enable jesd_ip path or serial or parallel lpbk
	system("frioPciWrite -F s5a3 -P 0x20000 0x06"); //IP
	//system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
	//system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
}

fpga_provided_sysref()
{
    if (flow_params.jesdConfig.jesdUsecase == UC5C || flow_params.jesdConfig.jesdUsecase == UC2B || flow_params.jesdConfig.jesdUsecase == UC3B || flow_params.jesdConfig.jesdUsecase == UC3A || flow_params.jesdConfig.jesdUsecase == UC7C || flow_params.jesdConfig.jesdUsecase == UC2C || flow_params.jesdConfig.jesdUsecase == UC3D)
    {
        //enable sysref
        system("frioPciWrite -F s5a1 -P 0x20000 0x94");
		system("frioPciWrite -F s5b1 -P 0x20000 0x94");
    }
    else if (flow_params.jesdConfig.jesdUsecase == UC9A || flow_params.jesdConfig.jesdUsecase == UC13A )
    {
        //enable sysref
        system("frioPciWrite -F s5a1 -P 0x20000 0x84");
		system("frioPciWrite -F s5b1 -P 0x20000 0x84");
    }
    else
    {
        //enable sysref
        system("frioPciWrite -F s5a1 -P 0x20000 0x94");
		system("frioPciWrite -F s5b1 -P 0x20000 0x94");
    }
}

void delay(unsigned int milliseconds)
{
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}


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
#define NSIP_HBI_INT_CSR_INT_VALUE 0xFFFFF
#define FIFO_CONTROL_VALUE 0x00000184
#define CREDIT_CS_VALUE 0x8
#define MISC_CTRL_VALUE 0x0
#define CSR_INT_VALUE 0xFFFFFFFF


/***********************************************
* GLOBAL DATA DEFINITIONS (consts, vars)      *
***********************************************/
//16G Usecases: UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;
//32G Usecases: UC-5E;UC-3C;UC-7G;UC-5B;UC-7E;UC-9C;UC-7B;UC-9B;UC-11C;9A;11A;13A;UC-3E;UC-5F
//CIO2STRM configuration table
// VEX 0 table 0 
static register_config_tbl_t g_cio2strm_0_config_tbl[] = 
{
	// INT Enable
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_INT_ENABLE_OFFSET, CIO2STRM_INT_EN_VALUE, \
        CIO2STRM_MEM_CIO2STRM_INT_ENABLE_WR_MASK, "CIO2STRM_INT_ENABLE"},

    //VE00 cio2strm
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_OFFSET, CIO2STRM_FIFO_STATUS_CTL_VALUE,
        CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_WR_MASK, "CIO2STRM_FIFO_STATUS_CTL"},

    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_OFFSET, CIO2STRM_WORD_CNT_CTL_VALUE, CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_WR_MASK, \
        "CIO2STRM_WORD_CNT_CTL"},

    // Enables the eight stream from vex core to CRUX -0xff
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_RANGE_EN_OFFSET, 0x00000003, CIO2STRM_MEM_CIO2STRM_RANGE_EN_WR_MASK, \
        "CIO2STRM_RANGE_EN"},

    //MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_OFFSET, 0x00000000, \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, "CIO2STRM_MEM_ADDR_LOW0"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_OFFSET, 0x1FFFF, \
        CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, "CIO2STRM_MEM_ADDR_HIGH0"},
    //MEM_OFFSET[0]- is in bytes
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET0"},
    //STRM_DEST[0] - mapped to JESD_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST0_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST0"},
		
	//MEM_ADDR_LOW[1] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW1_OFFSET, 0x20000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW1"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH1_OFFSET, 0x3FFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH1"},
    //MEM_OFFSET[1]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET1_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET1"},
    //STRM_DEST[1] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST1_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST1"},

    //MEM_ADDR_LOW[2] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW2_OFFSET, 0x40000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW2"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH2_OFFSET, 0x5FFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH2"},
    //MEM_OFFSET[2]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET2_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET2"},
    //STRM_DEST[2] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST2_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST2"},

    //MEM_ADDR_LOW[3] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW3_OFFSET, 0x60000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW3"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH3_OFFSET, 0x7FFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH3"},
    //MEM_OFFSET[3]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET3_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET3"},
    //STRM_DEST[3] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST3_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST3"},

    //MEM_ADDR_LOW[4] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW4_OFFSET, 0x80000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW4"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH4_OFFSET, 0x9FFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH4"},
    //MEM_OFFSET[4]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET4_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET4"},
    //STRM_DEST[4] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST4_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST4"},

    //MEM_ADDR_LOW[5] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW5_OFFSET, 0xA0000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW5"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH5_OFFSET, 0xBFFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH5"},
    //MEM_OFFSET[5]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET5_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET5"},
    //STRM_DEST[5] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST5_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST5"},

    //MEM_ADDR_LOW[6] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW6_OFFSET, 0xC0000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW6"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH6_OFFSET, 0xDFFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH6"},
    //MEM_OFFSET[6]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET6_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET6"},
    //STRM_DEST[6] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST6_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST6"},

    //MEM_ADDR_LOW[7] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW7_OFFSET, 0xE0000, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW_WR_MASK, \
        "CIO2STRM_MEM_ADDR_LOW7"},
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH7_OFFSET, 0xFFFFF, CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH_WR_MASK, \
        "CIO2STRM_MEM_ADDR_HIGH7"},
    //MEM_OFFSET[7]- is in words
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_MEM_OFFSET7_OFFSET, 0x00000000, CIO2STRM_MEM_CIO2STRM_MEM_OFFSET_WR_MASK, \
        "CIO2STRM_MEM_OFFSET7"},
    //STRM_DEST[7] - mapped to JESD_Port_0
    {VEXABC0_C2S_CIO2STRM_BASE + CIO2STRM_MEM_CIO2STRM_STRM_DEST7_OFFSET, 0x00000040, CIO2STRM_MEM_CIO2STRM_STRM_DEST_WR_MASK, \
        "CIO2STRM_STRM_DEST7"},
		
};

//UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;

static register_config_tbl_t* vexConfigArray[1] = {	g_cio2strm_0_config_tbl};
static int vexConfigArraySize[1] = {	ARRAY_SIZE(g_cio2strm_0_config_tbl)};

static int vexCountStartIdxTbl[2];

//NSIP HBI
//16G Usecases: UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;
//32G Usecases: UC-5E;UC-3C;UC-7G;UC-5B;UC-7E;UC-9C;UC-7B;UC-9B;UC-11C;9A;11A;13A;UC-3E;UC-5F
// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..

//NSIP configuration table
//NSIP table-0
static register_config_tbl_t g_cm_0_config_tbl[] =
{
	
	// NSIP Interrupt enable registers
    {DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, \
        "NSIP_HBI_INTR_INT_HIGH_EN"},
    {DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, \
        "NSIP_HBI_INTR_INT_LOW_EN"},

    // H2B Registers
    {DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET, FIFO_CONTROL_VALUE, \
        NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL"},
        
    {DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, CREDIT_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, \
        "NSIP_HBI_H2B_CREDIT_READY_CS"},
		
	
    // These are for Buffer S0
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET, 0x80000000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_OFFSET"},
   
	// These are for Buffer S1
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET, 0x80020000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL1_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL1_OFFSET"},
   
    // These are for Buffer S2
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL2_OFFSET, 0x80040000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL2_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL2_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL2_OFFSET"},
   
    // These are for Buffer S3
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL3_OFFSET, 0x80060000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL3_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL3_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL3_OFFSET"},
   
    // These are for Buffer S4
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL4_OFFSET, 0x80080000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL4_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL4_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL4_OFFSET"},
   
    // These are for Buffer S5
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL5_OFFSET, 0x800a0000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL5_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL5_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL5_OFFSET"},
   
    // These are for Buffer S6
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL6_OFFSET, 0x800c0000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL6_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL6_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL6_OFFSET"},
   
    // These are for Buffer S7
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_TBL7_OFFSET, 0x800e0000, NSIP_HBI_B2H_CSR_B2H_ADDR_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_TBL7_OFFSET"},
    // Mask was set for total 2K flits in words
	{DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL7_OFFSET, 0x1ffff, NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL_WR_MASK, "NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL7_OFFSET"},
   
};


static register_config_tbl_t* nsipConfigArray[1] = {g_cm_0_config_tbl};
static int nsipConfigArraySize[1] = {ARRAY_SIZE(g_cm_0_config_tbl)};


register_config_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

/*********************************************** 

 * STATIC FUNCTION PROTOTYPES                  * 

 ***********************************************/ 
int configure_jesd_host(int, int [], int, int[], int, int);

/*********************************************** 

 * STATIC FUNCTION DEFINITIONS                 * 

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

//Added for RSB
static int configure_jesd_h2b()
{
    //================
    //NSIP_HBI config
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_INTR_INT_HIGH_EN_OFFSET, NSIP_HBI_INTR_INT_HIGH_EN_DEFAULT, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_RD_MASK, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_INTR_INT_HIGH_EN");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_INTR_INT_LOW_EN_OFFSET, NSIP_HBI_INTR_INT_LOW_EN_DEFAULT, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INT_CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_RD_MASK, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_INTR_INT_LOW_EN");

    // H2B Registers
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_OFFSET,NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_DEFAULT , FIFO_CONTROL_VALUE, FIFO_CONTROL_VALUE, NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_RD_MASK, NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_WR_MASK, "NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_CREDIT_READY_CS_OFFSET, NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT, CREDIT_CS_VALUE, CREDIT_CS_VALUE, NSIP_HBI_H2B_CREDIT_READY_CS_RD_MASK, NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK, "NSIP_HBI_H2B_CREDIT_READY_CS");

    //Sending all data to VEX1
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_ROUTE_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_ROUTE_LKUP_TBL_DEFAULT, 0x1, 0x1, NSIP_HBI_H2B_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK, "H2B_ROUTE_LKUP_TBL0");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_ADDR_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_ADDR_LKUP_TBL_DEFAULT, 0x80001000, 0x80001000, NSIP_HBI_H2B_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK, "H2B_ADDR_LKUP_TBL0");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_DEFAULT, 0x18000, 0x18000, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK, "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_OFFSET, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_DEFAULT, 0x1, 0x1, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_RD_MASK, NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK, "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0");
    write_read_expect_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE+NSIP_HBI_H2B_MD_CONTROL_TBL0_OFFSET, NSIP_HBI_H2B_MD_CONTROL_TBL_DEFAULT, 0x7, 0x7, NSIP_HBI_H2B_MD_CONTROL_TBL_RD_MASK, NSIP_HBI_H2B_MD_CONTROL_TBL_WR_MASK, "NSIP_HBI_H2B_MD_CONTROL_TBL0");
}

/*********************************************** 

 * GLOBAL FUNCTION DEFINITIONS                 * 

 ***********************************************/ 

/**
* @brief           Function configuring all the required registers from host
* @param [in]      Vex Id, Jesd Id, APB Id and SYS_RATE_IQ_P5
* @return          status
*/
int configure_jesd_host(int vexCount, int vexId[], int nsipCount, int nsipId[], int apb_num, int cm_num)
{
    int vexIdx,j,k,rv = 0;
    int i=0;
    int nsipIdx = 0;

    printf("###### Configuring JESD host\n");

    //CIO2STRM table selection
    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
    {
        for (j = 0; j < vexConfigArraySize[vexIdx]; j++)
		{
			if (rv = write_reg_18a(vexConfigArray[vexIdx][j].offset + (0x40000*vexIdx), vexConfigArray[vexIdx][j].value, \
					vexConfigArray[vexIdx][j].mask, vexConfigArray[vexIdx][j].name))
			return rv;
        }
        printf("INFO: Vex %d cio2strm configuration completed", vexIdx);
    }

    //NSIP table selection 
    for (nsipIdx = 0; nsipIdx < nsipCount; nsipIdx++)
    {
        printf("nsipId[%d] = %d\n", nsipIdx, nsipId[nsipIdx]);
        printf("nsipConfigArraySize[%d] = %d\n", nsipIdx, nsipConfigArraySize[nsipIdx]);
        for (i = 0; i<nsipConfigArraySize[nsipIdx]; i++)
            {
                printf("looped %d, %d, %d + %d, 0x%x, 0x%x, %s\n", DLNK_JESDABC0_NSIP_HBI_CSR_BASE, nsipConfigArray[nsipIdx][i].offset, nsipConfigArray[nsipIdx][i].value, nsipConfigArray[nsipIdx][i].mask, nsipConfigArray[nsipIdx][i].name);
                if (rv = write_reg_18a((nsipConfigArray[nsipIdx][i].offset), nsipConfigArray[nsipIdx][i].value, \
                        nsipConfigArray[nsipIdx][i].mask, nsipConfigArray[nsipIdx][i].name))
                 
                    {
                        printf("INFO: ### loading jesd0 b2h config done");
                        return rv;
                        
                    }
            }
        
        printf("INFO: ### JESD0 NSIP %d, nsipIdx DONE completed", nsipIdx);
    }
	configure_jesd_h2b();
    return rv;
}

// JESD CMN CSR reg
static int program_cmn_csr_tx_registers()
{
    int i=0;
    uint32_t base_address_cmn[] = {DLNK_JESDABC0_CMN_CSR_BASE,  DLNK_JESDABC1_CMN_CSR_BASE,  DLNK_JESDABC2_CMN_CSR_BASE,  DLNK_JESDABC3_CMN_CSR_BASE};
    printf("JESD CMN CSR CONFIG : program_cmn_csr_tx_registers \n");
    for(i=0; i<1; i++)
    {
		if (flow_params.jesdConfig.jesdUsecase == UC5C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC2B )
	    {
			
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3B )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00010001, 0x00010001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00010001, 0x00010001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000014, 0x00000014, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7G )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5B )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7E )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0007000f, 0x0007000f, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9B )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5E )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000b, 0x0000000b, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000b0011, 0x000b0011, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7B )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0001000b, 0x0001000b, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0001000b, 0x0001000b, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}		
		//Alok's Sim_Log
		/*
		else if (flow_params.jesdConfig.jesdUsecase == UC11A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0001000b, 0x0001000b, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0001000b, 0x0001000b, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		*/
		//Our 0p6_Repo Sim_Log
		else if (flow_params.jesdConfig.jesdUsecase == UC11A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0007003b, 0x0007003b, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		//Alok's Sim_Log
		/*
		else if (flow_params.jesdConfig.jesdUsecase == UC11C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000005, 0x00000005, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00030007, 0x00030007, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		*/
		//Our 0p6_Repo Sim_Log
		else if (flow_params.jesdConfig.jesdUsecase == UC11C )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x0009005f, 0x0009005f, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC13A )
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00010013, 0x00010013, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000009, 0x00000009, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00010013, 0x00010013, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
		
		else
	    {
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_OFFSET, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_RD_MASK, JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_NUM_VALID_STR");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_DEFAULT, 0x00000017, 0x00000017, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00170023, 0x00170023, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_CLK_GEN_ENABLE");
				
			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CNT_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_BFN_SYNC_POINT_CNT_ENABLE");
			
	        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL");
		}
	}
}

// JESD TX reg
static int program_tx_ip_registers()
{
    int i=0;
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};
    printf("JESD TX IP CONFIG : program_tx_ip_registers \n");

    for(i=0; i<1; i++)
    {
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SUBCLASS_OFFSET, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SUBCLASS_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_FEC_OFFSET, JESD_XIP_204C_TX_MEM_TX_FEC_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_FEC_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_FEC_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_FEC_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CRC3_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CRC3_EN_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CRC12_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CRC12_EN_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_OFFSET, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_OFFSET");
        
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_E_OFFSET, JESD_XIP_204C_TX_MEM_TX_E_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_E_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_E_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_E_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CF_OFFSET, JESD_XIP_204C_TX_MEM_TX_CF_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CF_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_HD_OFFSET, JESD_XIP_204C_TX_MEM_TX_HD_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_HD_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_HD_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_HD_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CMD_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CMD_EN_OFFSET");

        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_N_OFFSET, JESD_XIP_204C_TX_MEM_TX_N_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_N_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_N_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_N_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_NTOTAL_OFFSET, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_NTOTAL_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CS_OFFSET, JESD_XIP_204C_TX_MEM_TX_CS_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CS_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CS_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CS_OFFSET");
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_OFFSET");

		if (flow_params.jesdConfig.jesdUsecase == UC5C )
		{
			printf("JESD TX path - UC 5C 16G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC2B )
		{
			printf("JESD TX path - UC 2B 16G -LMFS -1-16-32-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x0000001f, 0x0000001f, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000301, 0x00000301, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3B )
		{
			printf("JESD TX path - UC 3B 16G -LMFS -2-16-16-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000c, 0x0000000c, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000101, 0x00000101, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7C )
		{
			printf("JESD TX path - UC 7C 16G -LMFS -4-8-4-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000101, 0x00000101, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7G )
		{
			printf("JESD TX path - UC 7G 32G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			//write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000b, 0x0000000b, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			//Working in TSB_Source_Mode - Roshan
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5B )
		{
			printf("JESD TX path - UC 5B 32G -LMFS -1-8-16-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000c, 0x0000000c, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000101, 0x00000101, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7E )
		{
			printf("JESD TX path - UC 7E 32G -LMFS -2-8-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3C )
		{
			printf("JESD TX path - UC 3C 32G -LMFS -1-16-32-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x0000001f, 0x0000001f, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000301, 0x00000301, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9C )
		{
			printf("JESD TX path - UC 9C 32G -LMFS -4-8-4-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000c, 0x0000000c, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000081, 0x00000081, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9B )
		{
			printf("JESD TX path - UC 9B 32G -LMFS -2-4-4-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000c, 0x0000000c, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000081, 0x00000081, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5E )
		{
			printf("JESD TX path - UC 5E 32G -LMFS -2-16-16-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000c, 0x0000000c, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000101, 0x00000101, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7B )
		{
			printf("JESD TX path - UC 7B 32G -LMFS -1-4-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9A )
		{
			printf("JESD TX path - UC 9A 32G -LMFS -1-2-4-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11A )
		{
			printf("JESD TX path - UC 11A 32G -LMFS -2-2-2-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000a, 0x0000000a, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000043, 0x00000043, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11C )
		{
			printf("JESD TX path - UC 11C 32G -LMFS -4-4-2-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x0000000a, 0x0000000a, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000043, 0x00000043, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC13A )
		{
			printf("JESD TX path - UC 13A 32G -LMFS -4-2-1-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000006, 0x00000006, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000043, 0x00000043, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
		
		else
		{
			printf("JESD TX path - UC 5C 16G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");
			write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
			write_read_expect_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
		}
	}
}


static int program_crux_clk_csr_tx_registers()
{
    int i=0;
    uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
    printf("###### : program_crux_clk-csr_tx_registers \n");

    for(i=0; i<1; i++)
    {
		if (flow_params.jesdConfig.jesdUsecase == UC5C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC2B )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3B )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			//changing to 4kb -> 1Block per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
				
			//16KB -> 4Blocks per stream
			/*
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00008000, 0x00008000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x0000c000, 0x0000c000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			
			//changing to 16kb per stream 0x00003fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00003fff, 0x00003fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00003fff, 0x00003fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00003fff, 0x00003fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00003fff, 0x00003fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00013fff, 0x00013fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
			*/
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7G )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5B )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7E )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9B )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5E )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7B )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9A )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11A )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			
			//changing to 64kb per stream 0x0000ffff
			//write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x0000ffff, 0x0000ffff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			
			//Trigger for 4KB per stream
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
			
			//Trigger for 64KB per stream
			//write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x0001ffff, 0x0001ffff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		//UC11C TSB_4K
		else if (flow_params.jesdConfig.jesdUsecase == UC11C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		//UC11C TSB_32K
		/*
		else if (flow_params.jesdConfig.jesdUsecase == UC11C )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00008000, 0x00008000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00007fff, 0x00007fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00007fff, 0x00007fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00017fff, 0x00017fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		*/
		else if (flow_params.jesdConfig.jesdUsecase == UC13A )
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			
			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x0000ffff, 0x0000ffff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x0001ffff, 0x0001ffff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
		
		else
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_ADDR7");

			//changing to 4kb per stream 0x00000fff
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00010fff, 0x00010fff, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_TRIG_EN_REG");	
		}
	}
}


static int program_tx_glue_registers()
{
    int i=0;
    uint32_t base_tx_glue[] = {DLNK_JESDABC0_TX_GLUE_BASE,  DLNK_JESDABC1_TX_GLUE_BASE,  DLNK_JESDABC2_TX_GLUE_BASE,  DLNK_JESDABC3_TX_GLUE_BASE};
    printf("JESD TX GLUE CONFIG : program_tx_glue_registers \n");
    for(i=0; i<1; i++)
    {
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC2B)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3B)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7C)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			
			//Calculated values
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000008, 0x00000008, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");
			
			//From Sim_Val_Log
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7G)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC3C)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5B)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7E)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9C)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000142, 0x00000142, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x00000007, 0x00000007, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9B)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000142, 0x00000142, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x00000007, 0x00000007, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC5E)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000001f, 0x0000001f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7B)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC9A)
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11A)
        {
			//Default TSB_4K
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			//added for TSB_64KB
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000010, 0x00000010, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");

			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000124, 0x00000124, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x00000003, 0x00000003, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11C)
        {
			//Default TSB_4K
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			//added for TSB_32KB
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000008, 0x00000008, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000124, 0x00000124, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x00000003, 0x00000003, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC13A)
        {
			//Default TSB_4K
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			//added for TSB_64KB
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000010, 0x00000010, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000124, 0x00000124, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x00000003, 0x00000003, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		else
        {
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_MEM_INST_CNT");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_DEFAULT, 0x00000181, 0x00000181, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

			//tx_start_trig1_sel -> 11, always enabled for tsb data.
			//default was 0x14, making it 0x34, roshan, 15/02/24
			//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000034, 0x00000034, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_DEFAULT, 0x00000004, 0x00000004, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_STRM_PHM_EN");
		}
		
		#if tsb_capture_enabled
			printf("\ntsb capture is enabled\n");
			write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN");
		#else
			printf("\ntsb capture is not enabled\n");
		#endif
	
	}
}


//Added for RSB - Aditya
static int program_cmn_csr_registers()
{
	int i=0;
	uint32_t base_address_cmn[] = {DLNK_JESDABC0_CMN_CSR_BASE,  DLNK_JESDABC1_CMN_CSR_BASE,  DLNK_JESDABC2_CMN_CSR_BASE,  DLNK_JESDABC3_CMN_CSR_BASE};
	printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
	
	for(i=0; i<1; i++)
	{
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
		{
		
			//tx and rx paths work independently, so tx clk ctrl not needed now, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_DEFAULT, 0x000b001b, 0x000b001b, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000b001b, 0x000b001b, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE");

			//this register can be ingnored as per RP, roshan 12/02/24
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE");
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7C)
		{			
			//tx and rx paths work independently, so tx clk ctrl not needed now, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_DEFAULT, 0x0000001b, 0x0000001b, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_DEFAULT, 0x000f0023, 0x000f0023, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_DEFAULT, 0x0000001b, 0x0000001b, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000f0023, 0x000f0023, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE");

			//this register can be ingnored as per RP, roshan 12/02/24
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE");
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC7G)
		{
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_DEFAULT, 0x00000007, 0x00000007, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD");

        //bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_DEFAULT, 0x0005000d, 0x0005000d, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_DEFAULT, 0x00000007, 0x00000007, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x0005000d, 0x0005000d, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL");

        //this register can be ingnored as per RP, roshan 12/02/24
        //write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE");

        //this register can be ingnored as per RP, roshan 12/02/24
        //write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE");
		}
		
		else if (flow_params.jesdConfig.jesdUsecase == UC11A)
		{
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000004, 0x00000004, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD");

        //bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_DEFAULT, 0x00030013, 0x00030013, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_DEFAULT, 0x00000003, 0x00000003, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x00030013, 0x00030013, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL");

        //this register can be ingnored as per RP, roshan 12/02/24
        //write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE");

        //this register can be ingnored as per RP, roshan 12/02/24
        //write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE");
        write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE");
		}
		
		else
		{			
			//tx and rx paths work independently, so tx clk ctrl not needed now, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYSREF_TSAD");

			//bits 0-15 -> 1b, bits 16-31 -> b, so total is 0x0b001b
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_DEFAULT, 0x000b001b, 0x000b001b, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CTRL");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYSREF_TSAD");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_DEFAULT, 0x000b001b, 0x000b001b, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CTRL");

			//this register can be ingnored as per RP, roshan 12/02/24
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_1P5G_DIV_ENABLE");
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_CLK_GEN_ENABLE");

			//this register can be ingnored as per RP, roshan 12/02/24
			write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000018, 0x00000018, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_SYNC_POINT_CNT_ENABLE");
			//write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_BFN_SYNC_POINT_CNT_ENABLE");
		}
	}
}

// JESD RX reg
static int program_rx_ip_registers()
{
    int i=0;
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
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

        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_N_OFFSET, JESD_XIP_204C_RX_MEM_RX_N_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_N_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_N_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_N_OFFSET");
        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET");
        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CS_OFFSET, JESD_XIP_204C_RX_MEM_RX_CS_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CS_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CS_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CS_OFFSET");

        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET");
        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET, JESD_XIP_204C_RX_MEM_RX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_SCR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SCR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET");
		
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
		{
			printf("JESD RX path - UC 5C 16G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
		    write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");

		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7C)
		{
			printf("JESD TX path - UC 7C 16G -LMFS -4-8-4-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_S_OFFSET, JESD_XIP_204C_RX_MEM_RX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_S_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_S_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_S_OFFSET");

			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
		    write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");

		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7G)
		{
			printf("JESD RX path - UC 7G 16G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
		    write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");

		}
		else if (flow_params.jesdConfig.jesdUsecase == UC11A)
		{
			printf("JESD RX path - UC 11A 32G -LMFS -2-2-2-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
		    write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000043, 0x00000043, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");

		}
		else
		{
			printf("JESD RX path - UC 5C 16G -LMFS -4-16-8-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");

		}
	}
} 

// JESD RX glue reg
static int program_crux_clk_csr_registers()
{
    int i=0;
    uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
    printf("###### : program_crux_clk-csr_registers \n");

    for(i=0; i<1; i++)
    {
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
		{
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7");

			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7");

			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_DEFAULT, 0x000000e8, 0x000000e8, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7C)
		{
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3");
			
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_DEFAULT, 0x000000e4, 0x000000e4, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_DEFAULT, 0x0000007f, 0x0000007f, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7G)
		{
		   //keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
		   //enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7");

			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7");
			
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_DEFAULT, 0x000000e8, 0x000000e8, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC11A)
		{
		   //keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
		   //enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0");
			/*
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7");
			*/
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0");
			/*
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7");
			*/
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_DEFAULT, 0x000000e1, 0x000000e1, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_DEFAULT, 0x000001ff, 0x000001ff, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG");
		}
		else
		{
			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_WR_MEM_TBL7");

			//keeping only 1 stream and commenting out other streams for 18a now, roshan 01/12/23
			//enabling for 8 streams, 14/12/23
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL0");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL1");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL2");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL3");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL4");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL5");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL6");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_RD_MEM_TBL7");

			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_DEFAULT, 0x000000e8, 0x000000e8, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_CFG");
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RX_MEM_STREAM_CFG");
		}
	}
}

static int program_rx_glue_registers()
{
    int i=0;
    uint32_t base_rx_glue[] = {DLNK_JESDABC0_RX_GLUE_BASE,  DLNK_JESDABC1_RX_GLUE_BASE,  DLNK_JESDABC2_RX_GLUE_BASE,  DLNK_JESDABC3_RX_GLUE_BASE};
    printf("JESD RX GLUE CONFIG : program_rx_glue_registers \n");
    for(i=0; i<1; i++)
    {
		if (flow_params.jesdConfig.jesdUsecase == UC5C)
		{
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "RX_GLUE_MEM_RX_GLUE_SONI");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "RX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK, "RX_DATAPATH_INIT_CYC_CNT");	
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7C)
		{
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "RX_GLUE_MEM_RX_GLUE_SONI");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "RX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK, "RX_DATAPATH_INIT_CYC_CNT");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC7G)
		{
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "RX_GLUE_MEM_RX_GLUE_SONI");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "RX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK, "RX_DATAPATH_INIT_CYC_CNT");
		}
		else if (flow_params.jesdConfig.jesdUsecase == UC11A)
		{
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000004, 0x00000004, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "RX_GLUE_MEM_RX_GLUE_SONI");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "RX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK, "RX_DATAPATH_INIT_CYC_CNT");
		}
		else
		{
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "RX_GLUE_MEM_RX_GLUE_SONI");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_GATE_SEL_WR_MASK, "RX_DATAPATH_GATE_SEL");
			write_read_expect_18a(base_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_OFFSET, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_RD_MASK, JESDABC_RX_GLUE_MEM_RX_DATAPATH_INIT_CYC_CNT_WR_MASK, "RX_DATAPATH_INIT_CYC_CNT");
		}
    }
}


// JESD enable reg
static int program_enable_registers()
{
    int i,j = 0;
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};
    printf("JESD ENABLE : program_enable_registers \n");

    for(i=0; i<1; i++)
    {
        write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET");
    }

    for(i=0; i<1; i++)
    {
        write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET");
    }
}

//Added for RSB
/*
static void configure_vex_strm2cio()
{
    printf("\nprograming vex 1 to receive\n");
    write_reg_18a(VEXABC1_S2C_STRM2CIO_BASE + STRM2CIO_MEM_STRM2CIO_INT_ENABLE_OFFSET, STRM2CIO_INT_ENABLE_VALUE, STRM2CIO_MEM_STRM2CIO_INT_ENABLE_WR_MASK, "STRM2CIO_INT_ENABLE");
    write_reg_18a(VEXABC1_S2C_STRM2CIO_BASE + STRM2CIO_MEM_STRM2CIO_FIFO_STATUS_CTL_OFFSET, STRM2CIO_FIFO_STATUS_CTL_VALUE, STRM2CIO_MEM_STRM2CIO_FIFO_STATUS_CTL_WR_MASK, "STRM2CIO_MEM_FIFO_STATUS_CTL");
    write_reg_18a(VEXABC1_S2C_STRM2CIO_BASE + STRM2CIO_MEM_STRM2CIO_WORD_CNT_CTL_OFFSET, STRM2CIO_WORD_CNT_CTL_VALUE, STRM2CIO_MEM_STRM2CIO_WORD_CNT_CTL_WR_MASK, "STRM2CIO_MEM_WORD_CNT_CTL");
}
*/
static void configure_jesd_block()
{
    uint32_t tx_gb_empty_reg = 0;
    uint32_t tx_gb_full_reg = 0;
    uint32_t rx_gb_empty_reg = 0;
    uint32_t rx_gb_full_reg = 0;

    // function calls - Reg seq usecase
	
	//program_cmn_csr_registers();
	program_cmn_csr_tx_registers();
	//program_rx_ip_registers();
    program_tx_ip_registers();
	//program_rx_glue_registers();
    program_tx_glue_registers();
	//program_crux_clk_csr_registers();
    program_crux_clk_csr_tx_registers();
	
	
	#if enable_rsb_cap
    //rsb freeze mode enable, roshan 12/02/24
    printf("###\nRSB capture is enabled\n");
    write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_CAP_FRZ_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_CAP_FRZ_EN_DEFAULT, 0x01, 0x01, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_CAP_FRZ_EN_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_CAP_FRZ_EN_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_CAP_FRZ_EN");
    delay(10);
	#else
		printf("###\nRSB capture is disabled\n");
	#endif
    /*
    configure_vex_strm2cio();
	printf("Giving delay of 10 milli seconds \n");
    delay(10);
	*/
    //enable loopback - NSIP level - jesd b2h to jesd h2b - lpbk ctl - 0x1
    int k =0;
    uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
    /*printf("\n#####Nsip lpbk is enabled\n\n");
    for(k=0; k<1; k++)
    {
        write_read_expect_18a(base_address_crux_clk_csr[k]+JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL");
    }
	*/

    int i,j=0;
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};

    //=================================
    printf("\n");
    printf("\n");
    for(i=0; i<1; i++)
    {
        tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
        tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
    }
    for(j=0; j<1; j++)
    {
        //using JESDABC_M1_XIP_204C_RX_BASE to configure jesd1 for rx
        rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
        rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
    }

    printf(" Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
    printf(" Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
    printf(" Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
    printf(" Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);

    program_enable_registers();
    //CMN_CSR SYSREF ENABLE, AS PER SIMVAL LOG,
    write_read_expect_18a(DLNK_JESDABC0_CMN_CSR_BASE+JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_SYSREF_ENABLE");
    write_read_expect_18a(DLNK_JESDABC0_CMN_CSR_BASE+JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_SYSREF_ENABLE");
	
    //=================================
    tx_gb_empty_reg = 0;
    tx_gb_full_reg = 0;
    rx_gb_empty_reg = 0;
    rx_gb_full_reg = 0;
    printf("\n");
    printf("\n");
    for(i=0; i<1; i++)
    {
        tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
        tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
    }
    for(j=0; j<1; j++)
    {
        //using JESDABC_M1_XIP_204C_RX_BASE to configure jesd1 for rx
        rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
        rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
    }

    printf(" After jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
    printf(" After jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
    printf(" After jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
    printf(" After jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
    printf("\n");
    printf("\n");

}

#define PARSEBUF 160
/**
* VEXCNT:,rw,bus,address,NBYTES,{DATA}
* @param parg
* @param flow_ptr
* @return
*/
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


///
/*
* NSIPCNT:,rw,bus,address,NBYTES,{DATA}
* @param parg
* @param flow_ptr
* @return
*/

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

    //  ########## NSIPCNT ######## 
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


/**
* Parse JESD parameters
* JESD:,
jesdUsecase: // UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;UC-5E;UC-3C;UC-7G;UC-5B;UC-7E;UC-9C;UC-7B;UC-9B;UC-11C;9A;11A;13A;UC-3E;UC-5F
*/
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
        ucnum = "5C";
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
                    //Added for 16G Usecases: UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;
                    //Added for 32G Usecases: UC-5E;UC-3C;UC-7G;UC-5B;UC-7E;UC-9C;UC-7B;UC-9B;UC-11C;9A;11A;13A;UC-3E;UC-5F
                    case 0:
						/* USECASE NUMBER */
						if(strcmp (p, "2B")==0 || strcmp (p, "2b") ==0)
						{  
                  		    printf("Selected Usecase is 2B TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC2B;
							ucnum="2B";
							vexCountStartIdxTbl_CIO2STRM[0]=0;
						}
						else if(strcmp(p, "3B")==0 || strcmp (p, "3b")==0)
						{ 
                  		    printf("Selected Usecase is 3B TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC3B;
							ucnum="3B";
							vexCountStartIdxTbl_CIO2STRM[0]=1;
						}
						
						else if(strcmp (p, "5C")==0 || strcmp (p, "5c") ==0)
						{ 
                  		    printf("Selected Usecase is 5C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC5C;
							ucnum="5C";
							vexCountStartIdxTbl_CIO2STRM[0]=2;
						}
						else if(strcmp(p, "3A")==0 || strcmp (p, "3a")==0)
						{ 
                  		    printf("Selected Usecase is 3A TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC3A;
							ucnum="3A";
							vexCountStartIdxTbl_CIO2STRM[0]=3;
						}
						else if(strcmp(p, "7C")==0 || strcmp (p, "7c")==0)
						{ 
                  		    printf("Selected Usecase is 7C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC7C;	
							ucnum="7C";
							vexCountStartIdxTbl_CIO2STRM[0]=4;
						}
						else if(strcmp (p, "7G")==0 || strcmp (p, "7g")==0)
						{ 
                  		    printf("Selected Usecase is 7G TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC7G;	
							ucnum="7G";
							vexCountStartIdxTbl_CIO2STRM[0]=5;
						}
						else if(strcmp (p, "2C")==0 || strcmp (p, "2c") ==0)
						{ 
                  		    printf("Selected Usecase is 2C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC2C;
							ucnum="2C";
							vexCountStartIdxTbl_CIO2STRM[0]=6;
						}
						else if(strcmp(p, "3D")==0 || strcmp (p, "3d")==0)
						{ 
                  		    printf("Selected Usecase is 3D TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC3D;	
							ucnum="3D";
							vexCountStartIdxTbl_CIO2STRM[0]=8;
						}
						else if(strcmp(p, "5B")==0 || strcmp (p, "5b")==0)
						{ 
                  		    printf("Selected Usecase is 5B TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC5B;	
							ucnum="5B";
							vexCountStartIdxTbl_CIO2STRM[0]=10;
						}
						else if(strcmp(p, "7E")==0 || strcmp (p, "7e")==0)
						{ 
                  		    printf("Selected Usecase is 7E TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC7E;	
							ucnum="7E";
							vexCountStartIdxTbl_CIO2STRM[0]=11;
						}
						else if(strcmp(p, "9C")==0 || strcmp (p, "9c")==0)
						{ 
                  		    printf("Selected Usecase is 9C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC9C;	
							ucnum="9C";
							vexCountStartIdxTbl_CIO2STRM[0]=12;
						}
						else if(strcmp(p, "9B")==0 || strcmp (p, "9b")==0)
						{ 
                  		    printf("Selected Usecase is 9B TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC9B;	
							ucnum="9B";
							vexCountStartIdxTbl_CIO2STRM[0]=13;
						}
						else if(strcmp(p, "7B")==0 || strcmp (p, "7b")==0)
						{ 
                  		    printf("Selected Usecase is 7B TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC7B;	
							ucnum="7B";
							vexCountStartIdxTbl_CIO2STRM[0]=14;
						}
						else if(strcmp(p, "9A")==0 || strcmp (p, "9a")==0)
						{ 
                  		    printf("Selected Usecase is 9A TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC9A;	
							ucnum="9A";
							vexCountStartIdxTbl_CIO2STRM[0]=15;
						}
						else if(strcmp(p, "11A")==0 || strcmp (p, "11a")==0)
						{ 
                  		    printf("Selected Usecase is 11A TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC11A;	
							ucnum="11A";
							vexCountStartIdxTbl_CIO2STRM[0]=16;
						}
						else if(strcmp(p, "11C")==0 || strcmp (p, "11c")==0)
						{ 
                  		    printf("Selected Usecase is 11C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC11C;	
							ucnum="11C";
							vexCountStartIdxTbl_CIO2STRM[0]=17;
						}
						else if(strcmp(p, "13A")==0 || strcmp (p, "13a")==0)
						{ 
                  		    printf("Selected Usecase is 13A TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC13A;	
							ucnum="13A";
							vexCountStartIdxTbl_CIO2STRM[0]=18;
						}
						else if(strcmp(p, "3C")==0 || strcmp (p, "3c")==0)
						{ 
                  		    printf("Selected Usecase is 3C TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC3C;	
							ucnum="3C";
							vexCountStartIdxTbl_CIO2STRM[0]=19;
						}
						else if(strcmp(p, "5E")==0 || strcmp (p, "5e")==0)
						{ 
                  		    printf("Selected Usecase is 5E TX path\n");
							flow_ptr->jesdConfig.jesdUsecase=UC5E;	
							ucnum="5E";
							vexCountStartIdxTbl_CIO2STRM[0]=20;
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


void assign_defaults(struct flow_params_t *flow_ptr)
{
    flow_ptr->vexCount = 1;
    flow_ptr->nsipCount = 1;

    /*JESD */
    flow_ptr->jesdConfig.jesdUsecase    = UC5C;
    flow_ptr->jesdConfig.jesdTxncs      = 0;
    flow_ptr->jesdConfig.jesdTestmode   = 0;
    flow_ptr->jesdConfig.jesdFecCrc     = 0;
    flow_ptr->jesdConfig.jesdBitordertx = 3;
    flow_ptr->jesdConfig.jesdBitorderrx = 0;
    flow_ptr->jesdConfig.jesdShth       = 16;
    flow_ptr->jesdConfig.jesdEmbth      = 8;
}


int main(int argc, const char *argv[])
{
    int rv = 0;
    uint32_t value38 = 0;
    uint32_t value39 = 0;
    uint32_t value40 = 0;
    uint32_t value41 = 0;
    uint32_t value42 = 0;
    uint32_t value43 = 0;
    uint32_t value44 = 0;
    uint32_t value45 = 0;
    int flags = 0;
    void *vex_hdl;
	
	uint32_t value46 = 0;
    uint32_t value47 = 0;
    uint32_t value48 = 0;
    uint32_t value49 = 0;
	uint32_t value50 = 0;
    uint32_t value51 = 0;
    uint32_t value52 = 0;
    uint32_t value53 = 0;
    uint32_t value54 = 0;
	
	
    /*
    //clear vex memory
    //printf("\n########Starting to clear vex mem from 0-10\n");
    vex_mem_clear(0, srp);
    vex_mem_clear(1, srp);
    vex_mem_clear(2, srp);
    vex_mem_clear(3, srp);
    vex_mem_clear(4, srp);
    vex_mem_clear(5, srp);
    vex_mem_clear(6, srp);
    vex_mem_clear(7, srp);
    vex_mem_clear(8, srp);
    vex_mem_clear(9, srp);
    vex_mem_clear(10, srp);
    //printf("########Done clearing vex mem from 0-10\n\n");
    */
    srp_vex_config_t vex_params;
    srp_vex_t srp_vex_hdl;
    int lc, i, j;
    int vexId[40], nsipId[2], apb_num, host_flag = 1, cm_num = 0, port_num = 0;
    volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
    int total_streams_0 = 8;
    int total_streams_1 = 16;
    int dmem_offset = 0x4000;
    int vex_tx_offset_val[] = {HIVE_ADDR_jesd_tx_g_dest_buffer0_base, HIVE_ADDR_jesd_tx_g_dest_buffer1_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer2_base, HIVE_ADDR_jesd_tx_g_dest_buffer3_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer4_base, HIVE_ADDR_jesd_tx_g_dest_buffer5_base,
                                    HIVE_ADDR_jesd_tx_g_dest_buffer6_base, HIVE_ADDR_jesd_tx_g_dest_buffer7_base,
                                    HIVE_ADDR_jesd_tx_g_timeout_cycles};

//8 Streams U-2b==1 VEX entry v0_vex_tx_val_kargs; U-3b== 1 VEX entry v1_vex_tx_val_kargs; U-5c==1 VEX entry v2_vex_tx_val_kargs, 
//Added for U-2B
    unsigned v0_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,1023};								   
//Added for U-3B
	unsigned v1_vex_tx_val_kargs[] = {0x00000, 0x20000,
									0x40000, 0x60000,
									0x80000, 0xA0000,
									0xC0000, 0xE0000,511};
//Added for U-5C
	unsigned v2_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,255};
								   
//4 Streams U-3a==1 VEX entry v3_vex_tx_val_kargs; U-7c== 1 VEX entry v4_vex_tx_val_kargs		   
//Added for U-3A
    unsigned v3_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,31};
//Added for U-7C
    unsigned v4_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,127};
								   
//Added for UC7G
	unsigned v5_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,127};
								   
//16 Streams U-2c==2 VEX entries v6_vex_tx_val_kargs, v7_vex_tx_val_kargs; U-3d== 2 VEX entries v8_vex_tx_val_kargs, v9_vex_tx_val_kargs
//Added for U-2C
    unsigned v6_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,2047};
								   
	unsigned v7_vex_tx_val_kargs[] = {0x100000, 0x120000,
                                   0x140000, 0x160000,
								   0x180000, 0x1A0000,
								   0x1C0000, 0x1E0000,2047};

								   
//Added for U-3D
    unsigned v8_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,2047};
								// need to give - > n-1
								// jesd -> expectes data at every 0-2047
	unsigned v9_vex_tx_val_kargs[] = {0x100000, 0x120000,
                                   0x140000, 0x160000,
								   0x180000, 0x1A0000,
								   0x1C0000, 0x1E0000,2047};
								  
								   
//Added for UC5B
	unsigned v10_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,255};
								   
//Added for UC7E
	unsigned v11_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,127};
								   
//Added for UC9C
	unsigned v12_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,63};
								   
//Added for UC9B
	unsigned v13_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,63};
								   
//Added for UC7B
	unsigned v14_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,127};
								   
//Added for UC9A
	unsigned v15_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,63};
								   
//Added for UC11A
	unsigned v16_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,31};
								   
//Added for UC11C
	unsigned v17_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,31};
								   
//Added for UC13A
	unsigned v18_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,15};
								   
//Added for UC3C
	unsigned v19_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,511};
								   
//Added for UC5E
	unsigned v20_vex_tx_val_kargs[] = {0x00000, 0x20000,
                                   0x40000, 0x60000,
								   0x80000, 0xA0000,
								   0xC0000, 0xE0000,255};
								   
								 								   
//Added for 8 streams : U-2B, U-3B, U-5C
//Added for 4 streams : U-3A, U-7C
//Added for 16 streams : U-2C, U-3D
	unsigned *vex_tx_val_kargs_tbl[21]={ v0_vex_tx_val_kargs, v1_vex_tx_val_kargs, v2_vex_tx_val_kargs,
										v3_vex_tx_val_kargs, v4_vex_tx_val_kargs, v5_vex_tx_val_kargs, 
										v6_vex_tx_val_kargs, v7_vex_tx_val_kargs, v8_vex_tx_val_kargs, 
										v9_vex_tx_val_kargs, v10_vex_tx_val_kargs, v11_vex_tx_val_kargs, 
										v12_vex_tx_val_kargs, v13_vex_tx_val_kargs, v14_vex_tx_val_kargs,
										v15_vex_tx_val_kargs, v16_vex_tx_val_kargs, v17_vex_tx_val_kargs,
										v18_vex_tx_val_kargs, v19_vex_tx_val_kargs, v20_vex_tx_val_kargs}; 

	unsigned vex_tx_buffer_addr[] = {HIVE_ADDR_jesd_tx_vbuffer_0, HIVE_ADDR_jesd_tx_vbuffer_1,
									HIVE_ADDR_jesd_tx_vbuffer_2, HIVE_ADDR_jesd_tx_vbuffer_3,
									HIVE_ADDR_jesd_tx_vbuffer_4, HIVE_ADDR_jesd_tx_vbuffer_5,
									HIVE_ADDR_jesd_tx_vbuffer_6, HIVE_ADDR_jesd_tx_vbuffer_7};
									
	unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
	unsigned int add_val[1];
	
//Added for 8 streams : U-2B, U-3B, U-5C
//Added for 4 streams : U-3A, U-7C
//Added for 16 streams : U-2C, U-3D
	unsigned int vex_start_stop[21][2]={	{0,8},{0,8},{0,8},
										{0,4},{0,4},
										{0,8},{8,16},{0,8},
										{8,16},{0,8},{0,4},{0,4},
											{0,4},{0,2},{0,2},{0,1},
											{0,1},{0,2},{0,1},{0,8},
												{0,8}};
    int rr=0;
    int vexIdx;
    int k=0;

    int vexCount = 1;
    int nsipCount = 1;
	// parse the input args
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
    optind=0;
    for(; optind < argc-1; optind++)
    {
        rr = parseOpts( argv[optind],  &flow_params )|rr;
    }

    sleep(2);
	

    //###########################################
    fpga_clk_and_sysref_period();
    delay(100);    
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
    delay(100);
    init(); // Initialize the srp
    delay(1000);
    //clear vex memory
    printf("\n########Starting to clear vex mem from 0-10\n");
    vex_mem_clear(0, srp);
    vex_mem_clear(1, srp);
	//Commenting 2-10 because of image issue 8th March- Aditya
/*
    vex_mem_clear(2, srp);
    vex_mem_clear(3, srp);
	vex_mem_clear(4, srp);
    vex_mem_clear(5, srp);
    vex_mem_clear(6, srp);
    vex_mem_clear(7, srp);
    vex_mem_clear(8, srp);
    vex_mem_clear(9, srp);
    vex_mem_clear(10, srp);
    printf("########Done clearing vex mem from 0-10\n\n");*/
	printf("########Done clearing vex mem from 0-1\n\n");
    delay(100);
    jesd_reset(JESD_INSTANCE_0,0);
    delay(1000);
    printf("\n");
    fpga_provided_sysref();
    delay(100);
	//program_cmn_csr_registers();
	//program_cmn_csr_tx_registers();
    configure_jesd_block();


    //###########################################
	//Added by Aditya
	printf("dumping tsb write pointers-before init\n");
    system("srpRead 0x06709300 1");
    printf("Number of command-line arguments: %d\n", argc);
	
	
	
	int flit_count = 0;
	int wr_addr = 0x0;
	uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
	uint32_t base_tx_glue[] = {DLNK_JESDABC0_TX_GLUE_BASE,  DLNK_JESDABC1_TX_GLUE_BASE,  DLNK_JESDABC2_TX_GLUE_BASE,  DLNK_JESDABC3_TX_GLUE_BASE};
	
	# if prefil_tsb_to_zero
		int m=0; 

		printf("Loading TSB with 0s\n");
		for(m=0; m<1; m++)
		{
			write_read_expect_18a(base_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");

			//prefill buffer 0  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 6);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###buffer0\n");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");

				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				delay(500);
			}

			//prefill buffer 1  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 7);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer1");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 2  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 8);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("\n###buffer2");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 3  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 9);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer3");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 4  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 10);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer4");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0,0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 5  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 11);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer5");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 6  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 12);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer6");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0,0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 7  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 13);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 8  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 14);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 9  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 15);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 10  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 16);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 11  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 17);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 12  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 18);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 13  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 19);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 14  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 20);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			//prefill buffer 15  0-64
			for(flit_count=0; flit_count < 64; flit_count++)
			{
				//printf("flit count is %x\n",flit_count);
				wr_addr = flit_count | (1 << 21);
				//printf("wr_addr is %x\n",wr_addr);
				//printf("###\nbuffer7");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_DEFAULT, wr_addr, wr_addr, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_APB_MEM_WADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
				
				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0,JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA0_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA1_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA2_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA3_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA4_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA5_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA6_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA7_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA8_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA9_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA10_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA11_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA12_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA13_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA14_OFFSET");
				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WDATA15_OFFSET");

				write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			}

			write_read_expect_18a(base_address_crux_clk_csr[m]+JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_MEM_APB_WR_OFFSET");
			write_read_expect_18a(base_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATA_SRC_EN");
		}
	#else
		printf("####tsb prefil is disabled \n");
	#endif
	
	
	//Added for RSB - Aditya
	
	//uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
		
	#if prefill_rsb_zero
		i=0;
		for(i=0; i<1; i++)
		{
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_DEFAULT, 0x01, 0x01, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN");
			int flit_count_pre = 0; 
			printf("\n########Starting to prefil 512 flits of RSB to 0\n\n");
			for(flit_count_pre=0; flit_count_pre<512; flit_count_pre++)
			{
				// 4kb -> 4096 bytes= 4096*8 = 32,768 bits
				// every flit count 16 registers*32 bits = 512 bits =1 flit
				// 32,768 bits / 512 bits = 64 flits -> flit count 0-63

				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x0, 0x0, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");

				//DBG_MEM_WRITE_ADDR :6; [4:0] ->00 0000
				//DBG_WR_BUFFER_SEL : 16; [23:8] -> indicates the buffers selected to be written in data source mode multiple buffers can be selected to written at once , eg 16'b0000_0000_0000_0001
				// wr_addr -> b' 0001 0000 0000 -> 0xff00

				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count_pre, flit_count_pre, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");

				// 16 registers *32 bit = 512 bit data 
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA0_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA0");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA1_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA1");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA2_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA2");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA3_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA3");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA4_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA4");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA5_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA5");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA6_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA6");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA7_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA7");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA8_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA8");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA9_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA9");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA10_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA10");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA11_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA11");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA12_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA12");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA13_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA13");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA14_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA14");
				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA15_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_DEFAULT, 0x00000000, 0x00000000, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_DATA15");

				write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
			}
			write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_DEFAULT, 0x00, 0x00, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_DATA_SRC_EN");
			printf("\n########Prefil of 512 flits of RSB to 0 done\n");
		}
	#else
		printf("\n########Disabling Prefil of 512 flits of RSB to 0 after reset\n\n");
	#endif
	
	
	printf("Before Init\n");

	printf("dumping TX_SAMPLE_REQ_REG\n");
    system("srpRead 0x067013e0 1");
	printf("dumping TX_CONV_DP_CONFIG\n");
    system("srpRead 0x0670d014 1");
	printf("dumping TX_MEM_RD_FREQ\n");
    system("srpRead 0x0670d018 1");
	printf("dumping TX_DATAPATH_GATE_SEL\n");
    system("srpRead 0x0670d01c 1");
/*
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
    optind=0;
    for(; optind < argc-1; optind++)
    {
        rr = parseOpts( argv[optind],  &flow_params )|rr;
    }

    sleep(2);
*/
    //system("source jesd_config.sh"); //vijay

    LOG_PRINT("INFO: logger beginning\n");

    //vexCount = 1;
    vexCount = flow_params.vexCount;
    printf("Vex count is %d\n", vexCount);
    //for(i=0; i<vexCount; i++)
    for (j=0, i = vexCountStartIdxTbl[vexCount-1]; i < vexCount+vexCountStartIdxTbl[vexCount-1]; j++, i++)
    {
        // vexId[i] = i - vexCountStartIdxTbl[vexCount-1];
        vexId[i] = j;
    }

    //nsipCount = 2;
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
    if (rv = configure_jesd_host(vexCount, vexId, nsipCount, nsipId, apb_num, cm_num))
    {
        printf ("ERROR: configure_jesd_host\n");
        return rv;
    }

    vex_hdl = &srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
        return rv;

    /*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }

    printf("Host: start vex tx program load \n");

    //for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
    {
        if ((rv = srp_vex_loader(vex_hdl, vexId[vexIdx], "vex_fw/sim_m64/jesd_tx.fw")))
            return rv;
    }

    printf("Host: vex program load - done\n");


    /* Loading the host parameters to VEX_0  Rx core*/
    //for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
    {
        for (lc = 0; lc < ARRAY_SIZE(vex_tx_offset_val); lc++)
        {
            if ((rv = srp_dev_block_write32(srp,
                            SRP_BLOCK_VEX_CORE,
                            vexId[vexIdx],
                            dmem_offset + vex_tx_offset_val[lc],
                            &vex_tx_val_kargs_tbl[vexCountStartIdxTbl_CIO2STRM[vexIdx]][lc],
                            1,
                            flags)))
                return rv;
            //sleep(1);
        }   // for (lc = 0; lc < ARRAY_SIZE(offset_val); lc++) ends
    }

    printf("Host parameters loaded to Vex0\n");

    /* Input Vector Generation VEX_0*/
    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
    {
        for (lc = vex_start_stop[vexIdx][0]; lc < vex_start_stop[vexIdx][1] ; lc++)
        {
			printf(" vijay -- vexIdx %d, lc = %d\n", vexIdx, lc);
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
            
            
#if 1
            if ((rv = srp_vex_memid_store(vex_hdl,
                            vexId[vexIdx],
                            SRP_VEX_VMEM,
                            vex_tx_buffer_addr[lc - vex_start_stop[vexIdx][0]],/*local_addr*/
                            val_inp[0],
                            (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
                return rv;
#endif
			//write_mem_18a((vex_tx_buffer_addr[lc - vex_start_stop[vexIdx][0]] + ), (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)), val_inp[0], "vex_vmem" );

            printf(" vijay2 -- vexId[vexIdx] %d, addr = 0x%x , data = 0x%x\n", vexId[vexIdx], vex_tx_buffer_addr[lc - vex_start_stop[vexIdx][0]], val_inp[0][0]);
        }

    }
    
    //return;

    printf("Input vectors generated for Vex0 \n");

    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
    {
        printf("Host: vex %d program start\n",vexIdx);
        srp_vex_start(vex_hdl, vexId[vexIdx], 0); // vex_0 start
    }
	
    //configure_jesd_block();

    printf("Host: vex program start - done for vex0\n");
	
	value54  = 0;
    value50  = 0;
    value54  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
    //value50  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_WPTR0_OFFSET, "TX_STRM_MEM_WPTR0");
    printf("\n");
    printf("\nreading flit count and write pointer after jesd enable\n");
    printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",value54);
    //printf("Present value of TX_STRM_MEM_WPTR0 is 0x%x \n",value50);
    printf("\n");

    /*Signal VEX_0 to start continuous flow*/

    //for (vexIdx = 0; vexIdx < vexCount; vexIdx++)
    for (vexIdx = vexCountStartIdxTbl[vexCount-1]; vexIdx < vexCount+vexCountStartIdxTbl[vexCount-1]; vexIdx++)
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
	
	printf("dumping tsb write pointers-After vex start \n");
    uint32_t z=0;
    printf("\n");
    for (z=0;z<5;z++)
	{
		value54  = 0;
        value50  = 0;
        value54  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
        //value50  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_WPTR0_OFFSET, "TX_STRM_MEM_WPTR0");
        printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",value54);
        //printf("Present value of TX_STRM_MEM_WPTR0 is 0x%x \n",value50);
	}
    printf("\n");

    //=================================
    //=================================
    uint32_t tx_gb_empty_reg = 0;
    uint32_t tx_gb_full_reg = 0;
    uint32_t rx_gb_empty_reg = 0;
    uint32_t rx_gb_full_reg = 0;
    uint32_t rx_sh_lock=0;
    uint32_t rx_emb_lock=0;
    uint32_t rx_sh_lock_loss=0;
    uint32_t rx_emb_lock_loss=0;
    i,j=0;
    uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
    uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};
    uint32_t base_address_cmn[] = {DLNK_JESDABC0_CMN_CSR_BASE,  DLNK_JESDABC1_CMN_CSR_BASE,  DLNK_JESDABC2_CMN_CSR_BASE,  DLNK_JESDABC3_CMN_CSR_BASE};

	//uint32_t base_tx_glue[] = {DLNK_JESDABC0_TX_GLUE_BASE,  DLNK_JESDABC1_TX_GLUE_BASE,  DLNK_JESDABC2_TX_GLUE_BASE,  DLNK_JESDABC3_TX_GLUE_BASE};
    //uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
    //uint32_t base_address_cmn[] = {DLNK_JESDABC0_CMN_CSR_BASE,  DLNK_JESDABC1_CMN_CSR_BASE,  DLNK_JESDABC2_CMN_CSR_BASE,  DLNK_JESDABC3_CMN_CSR_BASE};
    printf("\n");
    printf("\n");
    for(i=0; i<1; i++)
    {
        tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
        tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
    }
    for(j=0; j<1; j++)
    {
        //using JESDABC_M1_XIP_204C_RX_BASE to configure jesd1 for rx
        rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
        rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
    }

    printf(" After SYSREF value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
    printf(" After SYSREF value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
    printf(" After SYSREF value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
    printf(" After SYSREF value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
    printf("\n");
    printf("\n");

    rx_sh_lock  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
    rx_emb_lock  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
    rx_sh_lock_loss  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
    rx_emb_lock_loss  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");

    printf("\n\n");
    printf("After SYSREF value of SH lock of Link0 is 0x%x \n",rx_sh_lock);
    printf("After SYSREF value of EMB lock of Link0 is 0x%x \n",rx_emb_lock);
    printf("After SYSREF value of SH lock loss of Link0 is 0x%x \n",rx_sh_lock_loss);
    printf("After SYSREF value of EMB lock loss of Link0 is 0x%x \n",rx_emb_lock_loss);

    delay(2500);

    printf("\n");
    printf("dumping jesd h2b flit count\n");
    system("srpRead 0x06705314 1");
    printf("dumping jesd b2h flit count\n");
    system("srpRead 0x06705014 1");
    printf("dumping tsb write pointers \n");
    system("srpRead 0x06709300 16");
    printf("dumping vex0 flit count\n");
    system("srpRead 0x02802024 1");
    printf("dumping vex1 flit count\n");
    system("srpRead 0x02842024 1");
	
	printf("reading mem_size\n");
    system("srpRead 0x06709280 1");
	
	printf("After INIT\n");

	printf("dumping TX_SAMPLE_REQ_REG\n");
    system("srpRead 0x067013e0 1");
	printf("dumping TX_CONV_DP_CONFIG\n");
    system("srpRead 0x0670d014 1");
	printf("dumping TX_MEM_RD_FREQ\n");
    system("srpRead 0x0670d018 1");
	printf("dumping TX_DATAPATH_GATE_SEL\n");
    system("srpRead 0x0670d01c 1");
	
    
    /*
	printf("\n#######dumping capturing vex1\n\n");
    system("srpRead 0x63.1.0x28200 64");
    printf("\n####################\n");
    printf("#######dumping streaming vex0\n\n");
    system("srpRead 0x63.0.0x28000 64");
    printf("\n");
    system("srpRead 0x63.0.0x28200 64");
    printf("\n");
    system("srpRead 0x63.0.0x28400 64");
    printf("\n");
    system("srpRead 0x63.0.0x28600 64");
    printf("\n");
    system("srpRead 0x63.0.0x28800 64");
    printf("\n");
    system("srpRead 0x63.0.0x29000 64");
    printf("\n");
    system("srpRead 0x63.0.0x29200 64");
    printf("\n");
    system("srpRead 0x63.0.0x29400 64");
	*/
	
	value46  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS");
    value47  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS");
    value48  = read_reg_18a(base_tx_glue[0] + JESDABC_TX_GLUE_MEM_TX_TSB_EMPTY_STATUS_OFFSET, "JESDABC_TX_GLUE_MEM_TX_TSB_EMPTY_STATUS");
    value49  = read_reg_18a(base_tx_glue[0] + JESDABC_TX_GLUE_MEM_TX_TSB_UNDERFLOW_STATUS_OFFSET, "JESDABC_TX_GLUE_MEM_TX_TSB_UNDERFLOW_STATUS");

	printf("Present value of JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS is 0x%x \n",value46);
    printf("Present value of JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_FULL_STATUS is 0x%x \n",value47);
    printf("Present value of JESDABC_TX_GLUE_MEM_TX_TSB_EMPTY_STATUS is 0x%x \n",value48);
    printf("Present value of JESDABC_TX_GLUE_MEM_TX_TSB_UNDERFLOW_STATUS is 0x%x \n",value49);
	
	int fill_level0 = 0;
    int fill_level1 = 0;
    int fill_level2 = 0;
    int fill_level3 = 0;
    int fill_level4 = 0;
    int fill_level5 = 0;
    int fill_level6 = 0;
    int fill_level7 = 0;
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
    //i = 0;
    


	#if tsb_dump_enabled
	
	printf("\n#####TSB dump is enabled\n");
    //dump tsb buffer, roshan 21/02/24
    //===============================================================
    //uncommenting dumping rsb

    //i = 0;
    
	//int flit_count = 0;
	//int wr_addr = 0x0;
    value38 = 0;
    value38  = read_reg_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE + JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS");
    printf("\n#######TSB buffer 0 fill status register value is 0x%x \n", value38);
    fill_level0 = (value38 & 0x02);
    printf("#######JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_BUF_FILL_STATUS register's buffer full value is 0x%x \n", fill_level0);
	
    // if(value38 != 0)
    // {
        // printf("#######buffer is not full\n");
    // }
    // else
    // {
        printf("###############buffer 0 is full\n");
        printf("###TSB buffer0 0-63 flits \n");
        //for(flit_count=0; flit_count<63; flit_count++)
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | 0x0000;
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer1 0-63 flits \n");
        //for(flit_count=0; flit_count<64; flit_count++)
        for(flit_count=0; flit_count<64; flit_count++)
        {
            wr_addr = flit_count | (1 << 6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer2 0-63 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (2 << 6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer3 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (3 << 6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer4 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (4<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer5 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (5<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }

        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer6 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (6<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
        }


        flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer7 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (7<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer8 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (8<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer9 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (9<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer10 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (10<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer11 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (11<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer12 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (12<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer13 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (13<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer14 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (14<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}
		
		flit_count = 0;
        wr_addr = 0x0;
        printf("\n\n###TSB buffer15 0-3 flits \n");
        for(flit_count=0; flit_count<64; flit_count++)
        //for(flit_count=0; flit_count<4; flit_count++)
        {
            wr_addr = flit_count | (15<<6);
            //printf("###flit count is %d\n",flit_count);
            //printf("current offset address is %x\n",wr_addr);
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RADDR");
            write_read_expect_18a(DLNK_JESDABC0_TX_GLUE_BASE+JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_OFFSET, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_DEFAULT, 0x01, 0x01, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_MASK, JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RD");
            write_read_expect_18a(DLNK_JESDABC0_CRUX_CLK_CSR_BASE+JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_DEFAULT, 0x00000001, 0x00000001, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_TX_TSB_CFG");
            stream0_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA0_OFFSET");
            stream1_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA1_OFFSET");
            stream2_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA2_OFFSET");
            stream3_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA3_OFFSET");
            stream4_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA4_OFFSET");
            stream5_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA5_OFFSET");
            stream6_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA6_OFFSET");
            stream7_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA7_OFFSET");
            stream8_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA8_OFFSET");
            stream9_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA9_OFFSET");
            stream10_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA10_OFFSET");
            stream11_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream12_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA12_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA11_OFFSET");
            stream13_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA13_OFFSET");
            stream14_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA14_OFFSET");
            stream15_buffer = read_reg_18a(DLNK_JESDABC0_TX_GLUE_BASE + JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET, "JESDABC_TX_GLUE_MEM_TX_APB_MEM_RDATA15_OFFSET"); 
            printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
		}


		//write_read_expect_18a(base_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CAPTURE_FRZ_EN");
		//printf("TSB Capture Mode: Disabled -  Aditya\n");
	#else
		printf("\n#####TSB dump is not enabled\n");
	#endif
	
	
	
	//Added for RSB - Aditya	
		
	#if dump_rsb_valid
		//going to dump RSB 8 streams
		/*int fill_level0 = 0;
		int fill_level1 = 0;
		int fill_level2 = 0;
		int fill_level3 = 0;
		int fill_level4 = 0;
		int fill_level5 = 0;
		int fill_level6 = 0;
		int fill_level7 = 0;
		i = 0;
		int flit_count = 0;*/
		int loop_count = 0;
		while(loop_count < 1)
		{
			int i=0;
			uint32_t base_address_crux_clk_csr[] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};
			for(i=0; i<1; i++)
			{
				//printf("#######loop_count is %d\n",loop_count);
				//------------------0
				value38 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS0");
				fill_level0 = (value38 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS0 register value is 0x%x \n", value38);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS0 register or fill status of rsb buffer value is 0x%x \n", fill_level0);
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
					for(flit_count=0; flit_count<64; flit_count++)
					{    
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------1
				value39 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS1");
				fill_level1 = (value39 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS1 register value is 0x%x \n", value39);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS1 register or fill status of rsb buffer value is 0x%x \n", fill_level1);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15");
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------2
				value40 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS2");
				fill_level2 = (value40 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS2 register value is 0x%x \n", value40);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS2 register or fill status of rsb buffer value is 0x%x \n", fill_level2);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------3
				value41 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS3");
				fill_level3 = (value41 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS3 register value is 0x%x \n", value41);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS3 register or fill status of rsb buffer value is 0x%x \n", fill_level3);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------4

				value42 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS4");
				fill_level4 = (value42 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS4 register value is 0x%x \n", value42);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS4 register or fill status of rsb buffer value is 0x%x \n", fill_level4);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15");
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------5
				
				value43 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS5");
				fill_level5 = (value43 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS5 register value is 0x%x \n", value43);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS5 register or fill status of rsb buffer value is 0x%x \n", fill_level5);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------6
				value44 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS6");
				fill_level6 = (value44 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS6 register value is 0x%x \n", value44);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS6 register or fill status of rsb buffer value is 0x%x \n", fill_level6);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}

				//-------------------------------------7
				value45 = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS7");
				fill_level7 = (value45 && 0x400);
				printf("#######JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS7 register value is 0x%x \n", value45);
				printf("#######10th bit of JESDABC_CRUX_CLK_CSR_MEM_RX_STRM_MEM_STS7 register or fill status of rsb buffer value is 0x%x \n", fill_level7);
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
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_DEFAULT, flit_count, flit_count, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_INDIR_ADDR");
						write_read_expect_18a(base_address_crux_clk_csr[i]+JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_OFFSET, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_DEFAULT, 0x1, 0x1, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_RD_MASK, JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL_WR_MASK, "JESDABC_CRUX_CLK_CSR_MEM_RSB_WR_RD_CTL");
						stream0_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA0");
						stream1_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA1");
						stream2_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA2");
						stream3_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA3");
						stream4_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA4");
						stream5_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA5");
						stream6_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA6");
						stream7_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA7");
						stream8_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA8");
						stream9_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA9");
						stream10_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA10");
						stream11_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA11");
						stream12_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA12");
						stream13_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA13");
						stream14_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA14");
						stream15_buffer = read_reg_18a(base_address_crux_clk_csr[i] + JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_RSB_RD_DATA15"); 
						printf("%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n%x %x %x %x\n\n", stream0_buffer, stream1_buffer, stream2_buffer, stream3_buffer, stream4_buffer, stream5_buffer, stream6_buffer, stream7_buffer, stream8_buffer, stream9_buffer, stream10_buffer, stream11_buffer, stream12_buffer, stream13_buffer, stream14_buffer, stream15_buffer);
					}
				}
				//---------------------------------------
			}
			loop_count = loop_count + 1;
		}
	#else
		printf("\n#####not dumping RSB \n");
	#endif

	value54  = 0;
    value50  = 0;
    value54  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
    value50  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_WPTR0_OFFSET, "TX_STRM_MEM_WPTR0");
    printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",value54);
    printf("Present value of TX_STRM_MEM_WPTR0 is 0x%x \n",value50);
    value51  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_INTR_INT_STATUS_OFFSET, "NSIP_HBI_INTR_INT_STATUS");
    value52  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_FF_B2H_FIFO_STATUS_OFFSET, "NSIP_HBI_B2H_FF_B2H_FIFO_STATUS");
    value53  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0_OFFSET, "JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0");
    printf("Present value of NSIP_HBI_INTR_INT_STATUS is 0x%x \n",value51);
    printf("Present value of NSIP_HBI_B2H_FF_B2H_FIFO_STATUS is 0x%x \n",value52);
    printf("Present value of JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_SIZE0 is 0x%x \n",value53);
    printf("\n");
    value54 = 0;
    i=0;
    while(i < 5)
    {
        value54  = read_reg_18a(DLNK_JESDABC0_NSIP_HBI_CSR_BASE + NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_OFFSET, "NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT");
        printf("Present value of NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT is 0x%x \n",value54);
        delay(1000);
        value50  = read_reg_18a(base_address_crux_clk_csr[0] + JESDABC_CRUX_CLK_CSR_MEM_TX_STRM_MEM_WPTR0_OFFSET, "TX_STRM_MEM_WPTR0");
        printf("Present value of TX_STRM_MEM_WPTR0 is 0x%x \n",value50);
        delay(1000);
        i++;
    }
	
	printf("reading vex time_out cycles\n");
    system("srpRead 0x63.0.0x4030 1");
	
	printf("At the End of Test\n");

	
	printf("dumping TX_SAMPLE_REQ_REG\n");
    system("srpRead 0x067013e0 1");
	printf("dumping TX_CONV_DP_CONFIG\n");
    system("srpRead 0x0670d014 1");
	printf("dumping TX_MEM_RD_FREQ\n");
    system("srpRead 0x0670d018 1");
	printf("dumping TX_DATAPATH_GATE_SEL\n");
    system("srpRead 0x0670d01c 1");
	printf("dumping TX_SYNC_POINT_CTRL\n");
    system("srpRead 0x06707028 1");
	 
	
	i=0;
	read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG");

	read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG_OFFSET, "JESDABC_TX_GLUE_MEM_TX_CONV_DP_CFG");

	read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG_OFFSET, "JESDABC_TX_GLUE_MEM_TX_MEM_RD_FREQ_CFG");

	read_reg_18a(base_tx_glue[i] + JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL_OFFSET, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_GATE_SEL");

	read_reg_18a(base_address_cmn[i] + JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL_OFFSET, "JESDABC_CMN_CSR_MEM_TX_SYNC_POINT_CTRL");

    return rv;
}   // main ends

