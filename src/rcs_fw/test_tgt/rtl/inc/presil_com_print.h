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
#ifndef PRESIL_COMMON_PRINT_H
#define PRESIL_COMMON_PRINT_H

#include <stdbool.h>
#include <stdint.h>

enum
{
    FW_ERR = 0,
    FW_WARN = 1,
    FW_NOTE = 2,
    FW_INFO = 3,
    FW_DEBUG = 4,
};

#define MACRO_DISPATCHER(func, severity) func##severity
#define FW_PRINT(sev, ...)                                     \
    do                                                         \
    {                                                          \
        MACRO_DISPATCHER (com_stub_print_, sev) (__VA_ARGS__); \
    } while (0)

#define FW_ERR_(fmt, ...) FW_PRINT (FW_ERR, fmt, ...)

void com_stub_print_FW_ERR (char const *const fmt, ...);
void com_stub_print_FW_WARN (char const *const fmt, ...);
void com_stub_print_FW_NOTE (char const *const fmt, ...);
void com_stub_print_FW_INFO (char const *const fmt, ...);
void com_stub_print_FW_DEBUG (char const *const fmt, ...);

#endif
