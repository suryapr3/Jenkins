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

#ifndef RF_CALIB_COM_UTIL__H
#define RF_CALIB_COM_UTIL__H

#include "stdint.h"
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief   Convert the 13 bit captured data to a floating point number
 * @param [in]  data_in   : Pointer to the int16_t buffer holding the DMA input samples
 * @param [in]  size      : size of the input and output
 * @param [in]  num_bits_to_clear   : Number of bits in the LSB to be cleared before conversion to float
 * @param [in]  data_out  : Pointer to the float array to store the converted output.
 * @return          none.
 * Restrictions:
  data_in and data_out can be non aligned but the size must be multiple of 4
 * -------------------------------------------------------------------------------------------------------------------*/
extern void rf_calib_com_convert_dma_output_to_float (const int16_t *__restrict data_in, const uint32_t size, const uint32_t num_bits_to_clear, const float *__restrict data_out);
#endif
