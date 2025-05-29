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
#ifndef ACCESS_CHECK_COMMON_DEFINITIONS_H
#define ACCESS_CHECK_COMMON_DEFINITIONS_H

#include "srp.h"
#include "cli.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <srp_rcs.h>
#include <srp_block_ids.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "init.h"
#include "logger.h"
#include "all_comps.h"
#include "common_macro.h"
#include "noc.h"
#include "noc_orion.h"

#define printf                         LOG_PRINT
#define SUCCESS                        ( 0 )
#define FAILURE                        ( -1 )
#define ACCESS_ALLOWED                 ( 1 )
#define ACCESS_NOT_ALLOWED             ( 0 )
#define RCS_CORE_AX                    ( 0 )
#define RCS_CORE_RX                    ( 1 )
#define RCS_CORE_TX                    ( 2 )
#define RCS_CORE_KP1                   ( 3 )

int rcs_halt_soft_reset(void);
int poll_rsm_flag(void* srp, uint32_t addr, uint32_t message);
void enable_drf0_memories();

#endif
