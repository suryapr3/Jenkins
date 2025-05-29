/*
 * Copyright (c) 2022 by Cadence Design Systems, Inc.  ALL RIGHTS RESERVED.
 * These coded instructions, statements, and computer programs are the
 * copyrighted works and confidential proprietary information of
 * Cadence Design Systems Inc.  They may be adapted and modified by bona fide
 * purchasers for internal use, but neither the original nor any adapted
 * or modified version may be disclosed or distributed to third parties
 * in any manner, medium, or form, in whole or in part, without the prior
 * written consent of Cadence Design Systems Inc.  This software and its
 * derivatives are to be executed solely on products incorporating a Cadence
 * Design Systems processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef RF_CALIB_NLEQ_FIR_F32_OPT_H
#define RF_CALIB_NLEQ_FIR_F32_OPT_H

#include "rf_calib_com_ex.h"
#define SZ_F32  ((int)sizeof (float))
#define SZ_CF32 ((int)sizeof (complex float))

/*-------------------------------------------------------------------------
Does a real-real FIR (real data, real coeffs)
Input:
  data      : Pointer to input data
  coeff     : Pointer to coefficient data
  tap_size  : FIR tap size.
  data_size : Number of input samples for real input
Output:
  rPtr      : Pointer to filtered output
Restrictions:
  tap_size,data_size    Should be a multiple of 8
-------------------------------------------------------------------------*/

void rf_calib_nleq_fir_f32_opt (const float *__restrict data, const float *__restrict coeff, float *__restrict rPtr, int tap_size, int data_size);
#endif // RF_CALIB_NLEQ_FIR_F32_OPT_H
