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
#ifndef _COM_RADIO_MSG_DEF_H
#define _COM_RADIO_MSG_DEF_H


#include "com_rm_msg.h"

// Radio message OPCODE start from 0xFExx
typedef enum
{
    e_RM_FBR_CONFIG_OPCODE = 0xFE00,
} e_rm_opcode_t;

typedef union {
    rm_fbr_config_bf_t rm_fbr_config;
} msg_rm_t;

#endif // _COM_RADIO_MSG_DEF_H
