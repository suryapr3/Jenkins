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
 * @file  common_sample.c
****************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"
#include "common_functions.h"
#include "srp_block_ids.h"
#include "coresight_common.h"

#define RCS_NONSEC      0x800000
#define RCS_NONSEC_SIZE 0x400

int main()
{

    init();
    int offset;

   // reading and writing into rcs_non_sec for 1KB size at offsets of 4 using coresight api
   for(offset = 0; offset < RCS_NONSEC_SIZE; offset += 4)
   {
       read_m_syscon_1_cs_dbg_18a(RCS_NONSEC + offset, NON_SECURE, "rcs_non_sec");

       write_m_syscon_1_cs_dbg_18a(RCS_NONSEC + offset, 0xa5a5, NON_SECURE, "rcs_non_sec");
       read_m_syscon_1_cs_dbg_18a(RCS_NONSEC + offset, NON_SECURE, "rcs_non_sec");

       /* as RCS_NONSEC is not accesible from host and RCS_RSM represent the RCS_NONSEC from host,
       reading the RCS_RSM from host to verify data written */
       read_reg_18a(RCS_RSM_START + offset, "rcs_non_sec");
       LOG_PRINT("\n");
   }
}
