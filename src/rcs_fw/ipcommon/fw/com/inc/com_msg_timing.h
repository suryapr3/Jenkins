/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/
#ifndef COMMON_MSG_TIMING_H
#define COMMON_MSG_TIMING_H

#include <stdbool.h>
#include <stdint.h>

#define CONV_US_TO_BFN_TICKS(us) (((us)*24576) / 25)

#define UL_ON_REF_ACT_TS_US       26
#define UL_ON_SET_UP_TS_US        2
#define UL_FAST_ON_REF_ACT_TS_US  18
#define UL_FAST_ON_SET_UP_TS_US   2
#define UL_UPDATE_REF_ACT_TS_US   22
#define UL_UPDATE_SET_UP_TS_US    2
#define UL_OFF_REF_ACT_TS_US      18
#define UL_OFF_SET_UP_TS_US       2
#define UL_FAST_OFF_REF_ACT_TS_US 8
#define UL_FAST_OFF_SET_UP_TS_US  2

#define DL_ON_REF_ACT_TS_US       26
#define DL_ON_SET_UP_TS_US        2
#define DL_FAST_ON_REF_ACT_TS_US  18
#define DL_FAST_ON_SET_UP_TS_US   2
#define DL_UPDATE_REF_ACT_TS_US   22
#define DL_UPDATE_SET_UP_TS_US    2
#define DL_OFF_REF_ACT_TS_US      18
#define DL_OFF_SET_UP_TS_US       2
#define DL_FAST_OFF_REF_ACT_TS_US 8
#define DL_FAST_OFF_SET_UP_TS_US  2

#define DL_STOP_TO_DL_START_US        25
#define DL_STOP_FAST_TO_DL_START_US   15
#define DL_START_TO_DL_PWRCTRL_US     25
#define DL_PWRCTRL_TO_DL_PWRCTRL_US   16
#define DL_START_TO_DL_STOP_US        8
#define DL_PWRCTRL_TO_DL_STOP_US      16
#define DL_PWRCTRL_TO_DL_STOP_FAST_US 8

#define UL_STOP_TO_UL_START_US         25
#define UL_STOP_FAST_TO_UL_START_US    15
#define UL_START_TO_UL_GAINCTRL_US     16
#define UL_GAINCTRL_TO_UL_GAINCTRL_US  16
#define UL_START_TO_UL_STOP_US         8
#define UL_GAINCTRL_TO_UL_STOP_US      16
#define UL_GAINCTRL_TO_UL_STOP_FAST_US 8

#define CONFIG_TO_MSG_US 30

#define CALC_LEAD_TIME(ref_act_time, set_up_time)                 ((ref_act_time) + (set_up_time))
#define CALC_LEAD_TIME_US_TO_BFN(ref_act_time_us, set_up_time_us) CONV_US_TO_BFN_TICKS (CALC_LEAD_TIME (ref_act_time_us, set_up_time_us))

#define CALC_DL_ON_LEAD_TIME     CALC_LEAD_TIME_US_TO_BFN (DL_ON_REF_ACT_TS_US, DL_ON_SET_UP_TS_US)
#define CALC_DL_UPDATE_LEAD_TIME CALC_LEAD_TIME_US_TO_BFN (DL_UPDATE_REF_ACT_TS_US, DL_UPDATE_SET_UP_TS_US)
#define CALC_DL_OFF_LEAD_TIME    CALC_LEAD_TIME_US_TO_BFN (DL_OFF_REF_ACT_TS_US, DL_OFF_SET_UP_TS_US)

#define CALC_UL_ON_LEAD_TIME     CALC_LEAD_TIME_US_TO_BFN (UL_ON_REF_ACT_TS_US, UL_ON_SET_UP_TS_US)
#define CALC_UL_UPDATE_LEAD_TIME CALC_LEAD_TIME_US_TO_BFN (UL_UPDATE_REF_ACT_TS_US, UL_UPDATE_SET_UP_TS_US)
#define CALC_UL_OFF_LEAD_TIME    CALC_LEAD_TIME_US_TO_BFN (UL_OFF_REF_ACT_TS_US, UL_OFF_SET_UP_TS_US)

#define DL_STOP_TO_DL_START_BFN        CONV_US_TO_BFN_TICKS (DL_STOP_TO_DL_START_US)
#define DL_STOP_FAST_TO_DL_START_BFN   CONV_US_TO_BFN_TICKS (DL_STOP_FAST_TO_DL_START_US)
#define DL_START_TO_DL_PWRCTRL_BFN     CONV_US_TO_BFN_TICKS (DL_START_TO_DL_PWRCTRL_US)
#define DL_PWRCTRL_TO_DL_PWRCTRL_BFN   CONV_US_TO_BFN_TICKS (DL_PWRCTRL_TO_DL_PWRCTRL_US)
#define DL_START_TO_DL_STOP_BFN        CONV_US_TO_BFN_TICKS (DL_START_TO_DL_STOP_US)
#define DL_PWRCTRL_TO_DL_STOP_BFN      CONV_US_TO_BFN_TICKS (DL_PWRCTRL_TO_DL_STOP_US)
#define DL_PWRCTRL_TO_DL_STOP_FAST_BFN CONV_US_TO_BFN_TICKS (DL_PWRCTRL_TO_DL_STOP_FAST_US)

#define UL_STOP_TO_UL_START_BFN         CONV_US_TO_BFN_TICKS (UL_STOP_TO_UL_START_US)
#define UL_STOP_FAST_TO_UL_START_BFN    CONV_US_TO_BFN_TICKS (UL_STOP_FAST_TO_UL_START_US)
#define UL_START_TO_UL_GAINCTRL_BFN     CONV_US_TO_BFN_TICKS (UL_START_TO_UL_GAINCTRL_US)
#define UL_GAINCTRL_TO_UL_GAINCTRL_BFN  CONV_US_TO_BFN_TICKS (UL_GAINCTRL_TO_UL_GAINCTRL_US)
#define UL_START_TO_UL_STOP_BFN         CONV_US_TO_BFN_TICKS (UL_START_TO_UL_STOP_US)
#define UL_GAINCTRL_TO_UL_STOP_BFN      CONV_US_TO_BFN_TICKS (UL_GAINCTRL_TO_UL_STOP_US)
#define UL_GAINCTRL_TO_UL_STOP_FAST_BFN CONV_US_TO_BFN_TICKS (UL_GAINCTRL_TO_UL_STOP_FAST_US)

#define CONFIG_TO_MSG_BFN CONV_US_TO_BFN_TICKS (CONFIG_TO_MSG_US)

#endif
