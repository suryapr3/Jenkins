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
#ifndef E2E_COMMON_DEFINITIONS_H
#define E2E_COMMON_DEFINITIONS_H

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
#include "common_utils.h"

#include "vha_common_definitions.h"

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct register_config_tbl_s {
	uint32_t addr;
	uint32_t value;
	uint32_t mask;
	char *name;
} register_config_tbl_t;


// Data type to hold table for NOC data
typedef struct noc_tbl_s {
	unsigned  address;
	unsigned  value;
	unsigned  core;
} noc_tbl_t;

typedef enum {
    VHA_SYS_RATE_IQ_P125 = 0,
    VHA_SYS_RATE_IQ_P25,
    VHA_SYS_RATE_IQ_P5,
    VHA_SYS_RATE_IQ_1,
    VHA_SYS_RATE_IQ_2,
    VHA_SYS_RATE_IQ_4,
    VHA_SYS_RATE_IQ_8,
} vha_sys_rate_t;

typedef enum {
    JESD_SYS_RATE_IQ_P125 = 0,
    JESD_SYS_RATE_IQ_P25,
    JESD_SYS_RATE_IQ_P5,
    JESD_SYS_RATE_IQ_1,
    JESD_SYS_RATE_IQ_2,
    JESD_SYS_RATE_IQ_4,
    JESD_SYS_RATE_IQ_8,
} jesd_sys_rate_t;


typedef struct _vha_node_config_t
{
	uint32_t vha_num;
	uint32_t ant_num;
	vha_sys_rate_t in_rate;
	vha_sys_rate_t out_rate;
	filter_mode_t mode;
} vha_node_config_t;

//Rajesh
typedef struct _v2d_node_config_t
{
    uint32_t v2d_num;
    uint32_t apb_num;
    uint32_t test_config;
    v2d_sys_rate_t in_rate;
    v2d_sys_rate_t out_rate;
    uint32_t drf_clock;
    uint32_t pdpd_enable;	
}v2d_node_config_t;

/***********************************************
 *        Function prototypes                  *     
 ***********************************************/
int test_configure_vha_duc_ddc(uint32_t vha_num,uint32_t ant_num,uint32_t in_rate,uint32_t out_rate,filter_mode_t mode,uint32_t clk);
int test_configure_vha_mod_demod(uint32_t vha_num,uint32_t ant_num,uint32_t in_rate,uint32_t out_rate,filter_mode_t mode,uint32_t clk);
int configure_v2d_flow1(int v2d_num, int apb_num, int drf_clock, sys_rate_t sys_rate);
int configure_v2d_flow2(int v2d_num, int apb_num, v2d_sys_rate_t in_rate, v2d_sys_rate_t out_rate, int drf_clock, int test_config, int pdpd_enable);
int configure_v2d_flow3(int v2d_num, int apb_num, v2d_sys_rate_t in_rate, v2d_sys_rate_t out_rate, int drf_clock, int test_config, int pdpd_enable);

#endif     //E2E_COMMON_DEFINITIONS_H
