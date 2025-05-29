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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "srp.h"
#include "common_functions.h"

#include "com_definitions.h"
#include "all_comps.h"
#include "init.h"
#include "cli.h"
#include "logger.h"

int init()
{
    uint32_t dev_id =0;
    uint32_t dev_flags = 0;

    /* open the core, first function to call before initiating any read/write */
    srp_dev_open(dev_id, dev_flags, &srp);

#ifdef ENABLE_FRIO
    jump_to_ram();
#endif


     /* other common configuration */
     //cold_reset_cycle(); //cold reset will be enabled once it is validated
     //subsys_reset_cycle ();
     reenable_pcie_after_sys_reset();

     rte_init();
     LOG_PRINT("VEX RTE config is enabled");

     crux_reset_cycle();
     vex_reset_cycle();

#ifdef ENABLE_V2D_CLK
    v2d_clk_enable(V2D_ALL, DRF_CHANNEL_BOTH);
    LOG_PRINT("V2D clk is enabled");
#endif

#ifdef ENABLE_VHA_CLK
    int vha_num;
    for(vha_num = 0; vha_num < 4; vha_num++)
    {
        vha_clock_config(vha_num, 0x3fc);
        LOG_PRINT("VHA clks are enabled for VHA%d\n", vha_num);
    }
#endif

#ifdef ENABLE_JESD_CLK
    jesd_reset(JESD_INSTANCE_ALL,0 );
    LOG_PRINT("JESD clk and reset is enabled");
#endif

#ifdef JESD_204D_ENABLE
     jesd_204d_enable ();
#endif

    LOG_PRINT("INFO: Common configuration done\n");

    return 0;

}
