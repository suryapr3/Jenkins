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
#ifndef COMMON_DEVICE_API_H
#define COMMON_DEVICE_API_H

#include <stdint.h>

/*! @fn int dev_mem_read(void *dev_handle, void *local_target, void *dev_address, uint32_t size_bytes);
    @brief Read arbitrary memory location from device memory.
    @param dev_handle Incoming handle of the current RCS module instance.
    @param local_target pointer to local memory to fill as a result of the read operation.
    @param dev_address device address of the data to read.
    @param size_bytes number of bytes to read from the device.
    @return number of bytes read.
*/

int dev_mem_read (void *dev_handle, void *local_target, void *dev_address, uint32_t size_bytes);

/*! @fn int dev_mem_write(void *dev_handle, void *dev_address, void *local_source, uint32_t size_bytes);
    @brief Read arbitrary memory location from device memory.
    @param dev_handle Incoming handle of the current RCS module instance.
    @param dev_address device address of the data to read.
    @param local_source pointer to local memory to write to the device.
    @param size_bytes number of bytes to write to the device.
    @return number of bytes written.
*/
int dev_mem_write (void *dev_handle, void *dev_address, void *local_source, uint32_t size_bytes);

#endif
