/* INTEL CONFIDENTIAL
 *
 * Copyright  2023 Intel Corporation All Rights Reserved.
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
#ifndef COM_PLATFORM_H
#define COM_PLATFORM_H

#include "com_rf_def.h"

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read chip mode whether it is 4016 or 0016.
 * @param [in]      none.
 * @return          e_chip_mode_t: chip mode.
 * -------------------------------------------------------------------------------------------------------------------*/
// value is invalid in RCS RTL model
e_chip_mode_t com_get_chip_mode ();

#endif // COM_PLATFORM_H
