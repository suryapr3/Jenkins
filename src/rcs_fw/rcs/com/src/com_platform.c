/* INTEL CONFIDENTIAL
 *
 * Copyright 2023 Intel Corporation All Rights Reserved.
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

/**
 * @file    com_platform.c
 * @brief   Common platform information and functions.
 * @details Common platform information and functions.
 * @todo    none.
 */

#include <stdint.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_platform.h"
#include "bfn_csr.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read chip mode whether it is 4016 or 0016.
 * @param [in]      none.
 * @return          e_chip_mode_t: chip mode.
 * -------------------------------------------------------------------------------------------------------------------*/
// value is invalid in RCS RTL model
e_chip_mode_t com_get_chip_mode ()
{
    volatile bfn_csr_general_csr_reg_t *p_general_csr = BFN_CSR_GENERAL_CSR_REG (V2D0_BFN_CSR_BASE);
    return (e_chip_mode_t)p_general_csr->DIE_MODE;
}
