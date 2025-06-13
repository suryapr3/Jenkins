/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
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
*********************************************************************************************/

/**************************************************************************************
 * @file  common_funtions.h
****************************************************************************************/

#ifndef CORESIGHT_COMMON_H
#define CORESIGHT_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_comps.h"

// enum to enable secure or non-secure transaction
typedef enum{
    SECURE,
    NON_SECURE
}security_t;

void configure_apb_security(security_t access);
void configure_axi_security(security_t access);
void write_cs_apb_18a(uint32_t address, uint32_t write_value, char regname[]);
uint32_t read_cs_apb_18a(uint32_t address, uint32_t *data, char regname[]);
void write_cs_axi_18a(uint32_t address, uint32_t write_value, char regname[]);
uint32_t read_cs_axi_18a(uint32_t address, uint32_t *data, char regname[]);
uint32_t write_m_cs_dbg_18a(uint32_t address, uint32_t write_value, security_t access, char regname[]);
uint32_t read_m_cs_dbg_18a(uint32_t address, security_t access, char regname[]);
uint32_t write_m_syscon_1_cs_dbg_18a(uint32_t address, uint32_t write_value, security_t access, char regname[]);
uint32_t read_m_syscon_1_cs_dbg_18a(uint32_t address, security_t access, char regname[]);
uint32_t read_expect_m_cs_dbg_18a(uint32_t address, uint32_t expected_data, uint32_t read_mask, \
                                  security_t access, char regname[]);
uint32_t write_reg_m_cs_dbg_18a(uint32_t address, uint32_t write_data, uint32_t write_mask, \
                                security_t access, char regname[]);
uint32_t read_reg_m_cs_dbg_18a(uint32_t address, uint32_t expected_data, uint32_t write_mask, \
                                   uint32_t read_mask, security_t access, char regname[]);
uint32_t read_expect_m_syscon_1_cs_dbg_18a(uint32_t address, uint32_t expected_data, uint32_t read_mask, \
                                           security_t access, char regname[]);
uint32_t write_expect_m_syscon_1_cs_dbg_18a(uint32_t address, uint32_t write_value, uint32_t default_value, uint32_t expected_data, \
                                            uint32_t write_mask, uint32_t read_mask, security_t access, char regname[]);
#endif

