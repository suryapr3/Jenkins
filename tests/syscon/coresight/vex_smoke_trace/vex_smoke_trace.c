/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2022 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to
 ** the source code ("Material") are owned by Intel Corporation or its
 ** suppliers or licensors. Title to the Material remains with
 ** Intel Corporation or its suppliers and licensors.
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is
 ** protected by worldwide copyright and trade secret laws and treaty
 ** provisions. No part of the Material may be used, copied, reproduced,
 ** modified, published, uploaded, posted, transmitted, distributed, or
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other
 ** intellectual property right is granted to or conferred upon you by
 ** disclosure or delivery of the Materials, either expressly, by implication,
 ** inducement, estoppel or otherwise. Any license under such intellectual
 ** property rights must be express and approved by Intel in writing.
 *************************************************************************/

#include "srp.h"                           // Should be the first file to include
#include "cli.h"
#include "init.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>

#include "logger.h"
#include "srp_block_ids.h"

#include "common_functions.h"
#include "all_comps.h"

#include "boot_prog.map.h"

#include "coresight_common.h"
#include "coresight_head.h"
#include "common_macro.h"
#include "time.h"


int main(int vexCoreId, unsigned test_pattern)
{
    int rv = 0, j = 0, i = 0;
    int core_num;
    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");

    init();

    // To enable coresight
    system("frioPciWrite -F s6b3 -P 0x20000 0x20202e09");

    core_num = vexCoreId;

    // configure funnel
    atbfunnel_main(core_num, "VEX");

    // coresight pre configuration
    pre_coresight_config();

    print("Host: start vex %d program load\n", vexCoreId);

    // To load vex program
    vex_loader(vexCoreId, "smoke.ur");
    print("Host: vex %d program load - done !!\n", vexCoreId);

    uint32_t trace_id = (core_num << 4) | 0xa;
    print("Trace_id: 0x%x\n", trace_id);

    //configure etm for required configuration with trace Id
    etm_config(core_num, "VEX", trace_id);
    print("configured etm for core: %d\n", core_num);

    // Enabling ETM
    etm_switch(core_num, "VEX", ENABLE);

    print("Host: vex %d program start\n", vexCoreId);

    vex_start(vexCoreId, 0);

    LOG_PRINT("Vex for core: %d started", vexCoreId);

    print("Host: vex %d program start - done\n", vexCoreId);

    //Status of ETM for core after core program completed
    LOG_PRINT("============================================");
    LOG_PRINT("status check part 2\n");

    etm_status(core_num, "VEX");

    print("Run is done switching off ETMB, ETF, ETR\n");

    // Post run coresight configuration, with Manual flush disabled
    post_coresight_config(core_num, "VEX", ETR_EN);

    etf_mem_read(ETF_EN);
    uint32_t etr_size = etr_mem_read(ETR_EN);

   rsm_mem_read(etr_size, trace_id);
   // mem_cap_mem_read();
}
