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

#include "rf_calib_nleq_fir_f32_opt.h"
#include <xtensa/config/core-isa.h>
#include <xtensa/config/system.h>
#include <xtensa/tie/xt_bben.h>

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

void rf_calib_nleq_fir_f32_opt (const float *__restrict data, const float *__restrict coeff, float *__restrict rPtr, int tap_size, int data_size)
{
    int i, j;
    xb_vecN_2xf32 vh_n, vx_0, vx_1, vx_2, vx_3, vx_10, vx_11, vx_12, vx_13;
    xb_vecN_2xf32 vx_20, vx_21, vx_22, vx_23, vx_30, vx_31, vx_32, vx_33;
    xb_vecN_2xf32 vAccum_0, vAccum_1, vAccum_2, vAccum_3, vc_0, vc_1, vc_2, vc_3;
    valign vaData_0, vaData_1, vaData_2, vaData_3;

    xb_vecN_2xf32 *__restrict ptr_xv_0 = (xb_vecN_2xf32 *)data;
    xb_vecN_2xf32 *__restrict ptr_xv_1 = (xb_vecN_2xf32 *)data;
    xb_vecN_2xf32 *__restrict ptr_xv_2 = (xb_vecN_2xf32 *)data;
    xb_vecN_2xf32 *__restrict ptr_xv_3 = (xb_vecN_2xf32 *)data;
    xb_vecN_2xf32 *__restrict ptr_yv = (xb_vecN_2xf32 *)rPtr;
    xb_vecN_2xf32 *__restrict ptr_in_yv = (xb_vecN_2xf32 *)rPtr;
    xb_vecN_2xf32 *__restrict ptr_out_yv = (xb_vecN_2xf32 *)rPtr;
    xtfloat *__restrict xtcoeff = (xtfloat *)coeff;

    for (j = 0; j < tap_size; j = j + 4)
    {

        BBE_LSN_2XF32_IP (vh_n, xtcoeff, -4);
        vc_0 = BBE_REPN_2XF32 (vh_n, 0);
        BBE_LSN_2XF32_IP (vh_n, xtcoeff, -4);
        vc_1 = BBE_REPN_2XF32 (vh_n, 0);
        BBE_LSN_2XF32_IP (vh_n, xtcoeff, -4);
        vc_2 = BBE_REPN_2XF32 (vh_n, 0);
        BBE_LSN_2XF32_IP (vh_n, xtcoeff, -4);
        vc_3 = BBE_REPN_2XF32 (vh_n, 0);

        ptr_xv_0 = (xb_vecN_2xf32 *)&data[j];
        vaData_0 = BBE_LAN_2XF32_PP (ptr_xv_0);
        ptr_xv_1 = (xb_vecN_2xf32 *)&data[j + 1];
        vaData_1 = BBE_LAN_2XF32_PP (ptr_xv_1);
        ptr_xv_2 = (xb_vecN_2xf32 *)&data[j + 2];
        vaData_2 = BBE_LAN_2XF32_PP (ptr_xv_2);
        ptr_xv_3 = (xb_vecN_2xf32 *)&data[j + 3];
        vaData_3 = BBE_LAN_2XF32_PP (ptr_xv_3);

#pragma ymemory(ptr_in_yv)
#pragma ymemory(ptr_out_yv)
        for (i = 0; i<(data_size / (SIMD_N_X_2 / SZ_F32))>> 2; i++)
        {

            BBE_LVN_2XF32_IP (vAccum_0, ptr_in_yv, SIMD_N_X_2);
            BBE_LAN_2XF32_IP (vx_0, vaData_0, ptr_xv_0);
            BBE_LAN_2XF32_IP (vx_10, vaData_1, ptr_xv_1);
            BBE_LAN_2XF32_IP (vx_20, vaData_2, ptr_xv_2);
            BBE_LAN_2XF32_IP (vx_30, vaData_3, ptr_xv_3);
            BBE_MULAN_2XF32 (vAccum_0, vx_0, vc_0);
            BBE_MULAN_2XF32 (vAccum_0, vx_10, vc_1);
            BBE_MULAN_2XF32 (vAccum_0, vx_20, vc_2);
            BBE_MULAN_2XF32 (vAccum_0, vx_30, vc_3);
            BBE_SVN_2XF32_IP (vAccum_0, ptr_out_yv, SIMD_N_X_2);

            BBE_LVN_2XF32_IP (vAccum_1, ptr_in_yv, SIMD_N_X_2);
            BBE_LAN_2XF32_IP (vx_1, vaData_0, ptr_xv_0);
            BBE_LAN_2XF32_IP (vx_11, vaData_1, ptr_xv_1);
            BBE_LAN_2XF32_IP (vx_21, vaData_2, ptr_xv_2);
            BBE_LAN_2XF32_IP (vx_31, vaData_3, ptr_xv_3);
            BBE_MULAN_2XF32 (vAccum_1, vx_1, vc_0);
            BBE_MULAN_2XF32 (vAccum_1, vx_11, vc_1);
            BBE_MULAN_2XF32 (vAccum_1, vx_21, vc_2);
            BBE_MULAN_2XF32 (vAccum_1, vx_31, vc_3);
            BBE_SVN_2XF32_IP (vAccum_1, ptr_out_yv, SIMD_N_X_2);

            BBE_LVN_2XF32_IP (vAccum_2, ptr_in_yv, SIMD_N_X_2);
            BBE_LAN_2XF32_IP (vx_2, vaData_0, ptr_xv_0);
            BBE_LAN_2XF32_IP (vx_12, vaData_1, ptr_xv_1);
            BBE_LAN_2XF32_IP (vx_22, vaData_2, ptr_xv_2);
            BBE_LAN_2XF32_IP (vx_32, vaData_3, ptr_xv_3);
            BBE_MULAN_2XF32 (vAccum_2, vx_2, vc_0);
            BBE_MULAN_2XF32 (vAccum_2, vx_12, vc_1);
            BBE_MULAN_2XF32 (vAccum_2, vx_22, vc_2);
            BBE_MULAN_2XF32 (vAccum_2, vx_32, vc_3);
            BBE_SVN_2XF32_IP (vAccum_2, ptr_out_yv, SIMD_N_X_2);

            BBE_LVN_2XF32_IP (vAccum_3, ptr_in_yv, SIMD_N_X_2);
            BBE_LAN_2XF32_IP (vx_3, vaData_0, ptr_xv_0);
            BBE_LAN_2XF32_IP (vx_13, vaData_1, ptr_xv_1);
            BBE_LAN_2XF32_IP (vx_23, vaData_2, ptr_xv_2);
            BBE_LAN_2XF32_IP (vx_33, vaData_3, ptr_xv_3);
            BBE_MULAN_2XF32 (vAccum_3, vx_3, vc_0);
            BBE_MULAN_2XF32 (vAccum_3, vx_13, vc_1);
            BBE_MULAN_2XF32 (vAccum_3, vx_23, vc_2);
            BBE_MULAN_2XF32 (vAccum_3, vx_33, vc_3);
            BBE_SVN_2XF32_IP (vAccum_3, ptr_out_yv, SIMD_N_X_2);
        }
        ptr_in_yv = ptr_out_yv = ptr_yv;
    }
}
