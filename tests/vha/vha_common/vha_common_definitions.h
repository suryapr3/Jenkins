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
#ifndef VHA_COMMON_DEFINITIONS_H
#define VHA_COMMON_DEFINITIONS_H

#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"                           // Should be the first file to include
#include "cli.h"
#include "init.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"
#include "srp_block_ids.h"
#include "all_comps.h"
#include "host_utils.h"
#include "common_functions.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define printf                         LOG_PRINT
#define MAX_READ_SIZE                  ( 2048 )
//#define DEBUG                          ( 1 )   // uncomment to enable debug prints

#define NUMBER_OF_VECTORS_INPUT        ( 128 )   // Corresponds to 1 block of data for 8GSPS
#define NUM_OF_ELEMENTS_PER_VEC        (  32 )
#define VEX_MAX_BUF_SIZE               ( 256 )   // in vectors and it should be power of 2

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define CIO2STRM_BASE(vex_num)         ( VEXABC0_C2S_CIO2STRM_BASE + (vex_num * 0x00040000) )
#define STRM2CIO_BASE(vex_num)         ( VEXABC0_S2C_STRM2CIO_BASE + (vex_num * 0x00040000) )
#define VHA_BASE(vha_num)              ( VHA0_ANT0_DUC0_BASE + (vha_num * 0x00020000) )
#define VHA_APB_OFFSET(ant_num)        ( (0x000000 + (ant_num * 0x10000)) )
#define VHA_DUC_OFFSET(duc_num)        ( (0x0000 + (duc_num * 0x8000)) )
#define VHA_DDC_OFFSET(ddc_num)        ( (0x2000 + (ddc_num * 0x8000)) )
#define VHA_MOD_OFFSET                 ( 0x1000 )
#define VHA_ANT_REG_OFFSET             ( 0x3000 )
#define VHA_NSIP_OFFSET                ( 0x4000 )
#define VHA_DMOD_OFFSET                ( 0x9000 )
#define VHA_DL_SWG_OFFSET              ( 0xB000 )
#define VHA_REG_OFFSET                 ( 0xC000 )
#define VHA_UL_SWG_OFFSET              ( 0x1B000 )

#define NUM_VHA_INSTANCES              (  8 )
#define NUM_VE_CORES                   ( 40 )
#define NUM_VE_PER_VHA                 ( 10 )

#define VHA_ANT_NUM_INTERRUPTS         ( 17 )
#define NSIP_HBI_NUM_INTERRUPTS        ( 21 )
#define SWG_NUM_INTERRUPTS             (  3 )

#define FIFO_UNDERFLOW                 ( 1 << 0 )
#define FIFO_OVERFLOW                  ( 1 << 1 )

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef enum {
    SYS_RATE_IQ_P125 = 0,
    SYS_RATE_IQ_P25,
    SYS_RATE_IQ_P5,
    SYS_RATE_IQ_1,
    SYS_RATE_IQ_2,
    SYS_RATE_IQ_4,
    SYS_RATE_IQ_P187 = 0,
    SYS_RATE_IQ_P375,
    SYS_RATE_IQ_P75,
    SYS_RATE_IQ_1P5,
    SYS_RATE_IQ_3,
    SYS_RATE_IQ_6
}sys_rate_t;

typedef enum {
    AUTO = 0,
    MANUAL
}filter_mode_t;

// Model a VHA antenna
typedef struct {
    uint64_t base_addr;
    vha_duc_t duc[2];
    vha_ddc_t ddc[2];
    vha_ant_t ant_reg;
    vha_mod_t mod;
    vha_dmod_t dmod;
    nsip_hbi_t cm;
}vha_antenna_t;

// Model a VHA
typedef struct {
    uint64_t base_addr;
    vha_t vha_reg;
    swg_t dl_swg, ul_swg;
    vha_antenna_t ant[2];
}vha_dev_t;


// Function prototypes
int is_vha_present(uint32_t vha_num);
int is_vex_present(uint32_t vex_num);
int vha_init(uint32_t vha_num);
void vha_show_regs(uint32_t vha_num, uint32_t ant_num);
int vha_check_status(uint32_t vha_num, uint32_t ant_num);
int vex_cio2strm_configure(uint32_t vex_num, uint32_t host_id);
int vex_cio2strm_configure_for_2_streams(uint32_t vex_num, uint32_t host_id);
int vex_strm2cio_configure(uint32_t vex_num);
void vex_cio2strm_show_regs(uint32_t vex_num);
int vex_cio2strm_check_status(uint32_t vex_num);
int vex_strm2cio_check_status(uint32_t vex_num);
void vex_strm2cio_show_regs(uint32_t vex_num);
void print_registers(uint64_t address, uint32_t size, char name[]);

#endif
