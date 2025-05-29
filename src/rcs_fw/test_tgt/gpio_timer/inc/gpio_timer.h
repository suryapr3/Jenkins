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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#include "com_definitions.h"


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
void timer0_irq_handler (void *arg);
uint32_t gpioTimeStampTestSingle();
uint32_t gpio_in_test();
uint32_t gpio_out_test();
uint32_t timerOneshotGrp0Tim0Test();
uint32_t timerOneshotGrp0Tim1Test();
uint32_t timerOneshotGrp1Tim0Test();
uint32_t timerOneshotGrp1Tim1Test();
uint32_t timerContGrp0Tim0Test();
uint32_t timerContGrp0Tim1Test();
uint32_t timerContGrp1Tim0Test();
uint32_t timerContGrp1Tim1Test();
 
uint32_t bfn_test();
uint32_t bfn_start();
uint32_t bfn_testfreeRun();
uint32_t bfn_testPresetCmd();
uint32_t bfn_testResetCmd();
uint32_t bfn_testCaptureCmd();

uint32_t bfn_testSyncRead();
uint32_t bfn_testSyncLoad();
uint32_t bfn_testUpperCntAdjReg();
uint32_t bfn_testTenmsCnt();
uint32_t bfn_testLcnt();
uint32_t bfn_timerSingleShot();
uint32_t bfn_timerContinuous();

void captureBfnCounter(uint32_t const dram_offset);
void presetBfnCounter(uint32_t const bfn_time_high, uint32_t const bfn_time_low);
void resetBfn(void);
void resetBfnCounter(uint32_t const bfn_time_high, uint32_t const bfn_time_low);
