#ifndef _CS_SOC_600_CTI16BIT_H_
#define _CS_SOC_600_CTI16BIT_H_

// ******************************************************************************
// ------------------------------------------------------------------------------
//                               INTEL CONFIDENTIAL
// ------------------------------------------------------------------------------
//    Copyright (c) 2018 - 2024 Intel Corporation
//
//    This software and the related documents are Intel copyrighted materials,
//    and your use of them is governed by the express license under which they
//    were provided to you ("License").
//    Unless the License provides otherwise, you may not use, modify, copy, publish,
//    distribute, disclose or transmit this software or the related documents
//    without Intel's prior written permission.
//
//    This software and the related documents are provided as is, with no express or
//    implied warranties, other than those that are expressly stated in the License.
// ------------------------------------------------------------------------------

// ******************************************************************************

#ifndef __KERNEL__
#include <stdint.h>
#endif // __KERNEL__
// ******************************************* Base address macros

#define CS_SOC_CTI16BIT_APB4_SLAVE_0_MM_BASE  ( 0x050000 )


// ******************************************* /Base address macros


// ******************************************* Register offset macros

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_OFFSET ( 0x00000000U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_OFFSET ( 0x00000010U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_OFFSET ( 0x00000014U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_OFFSET ( 0x00000018U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET ( 0x0000001cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_OFFSET ( 0x00000020U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_OFFSET ( 0x00000024U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_OFFSET ( 0x00000028U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_OFFSET ( 0x0000002cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_OFFSET ( 0x00000030U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_OFFSET ( 0x00000034U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_OFFSET ( 0x00000038U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_OFFSET ( 0x0000003cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_OFFSET ( 0x00000040U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_OFFSET ( 0x00000044U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_OFFSET ( 0x00000048U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_OFFSET ( 0x0000004cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_OFFSET ( 0x00000050U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_OFFSET ( 0x00000054U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_OFFSET ( 0x00000058U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_OFFSET ( 0x0000005cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_OFFSET ( 0x000000a0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_OFFSET ( 0x000000a4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_OFFSET ( 0x000000a8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_OFFSET ( 0x000000acU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_OFFSET ( 0x000000b0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_OFFSET ( 0x000000b4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_OFFSET ( 0x000000b8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_OFFSET ( 0x000000bcU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_OFFSET ( 0x000000c0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_OFFSET ( 0x000000c4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_OFFSET ( 0x000000c8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_OFFSET ( 0x000000ccU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_OFFSET ( 0x000000d0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_OFFSET ( 0x000000d4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_OFFSET ( 0x000000d8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_OFFSET ( 0x000000dcU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET ( 0x00000130U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET ( 0x00000134U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_OFFSET ( 0x00000138U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET ( 0x0000013cU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_OFFSET ( 0x00000140U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_OFFSET ( 0x00000144U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_OFFSET ( 0x00000ee4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_OFFSET ( 0x00000ee8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_OFFSET ( 0x00000ef4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_OFFSET ( 0x00000ef8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_OFFSET ( 0x00000f00U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_OFFSET ( 0x00000fa0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_OFFSET ( 0x00000fa4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_OFFSET ( 0x00000fa8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_OFFSET ( 0x00000facU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_OFFSET ( 0x00000fb8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_OFFSET ( 0x00000fbcU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_OFFSET ( 0x00000fc8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_OFFSET ( 0x00000fccU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_OFFSET ( 0x00000fd0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_OFFSET ( 0x00000fd4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_OFFSET ( 0x00000fd8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_OFFSET ( 0x00000fdcU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_OFFSET ( 0x00000fe0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_OFFSET ( 0x00000fe4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_OFFSET ( 0x00000fe8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_OFFSET ( 0x00000fecU )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_OFFSET ( 0x00000ff0U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_OFFSET ( 0x00000ff4U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_OFFSET ( 0x00000ff8U )
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_OFFSET ( 0x00000ffcU )

// ******************************************* /Register offset macros


// ******************************************* AddressSpace macros
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_OFFSET ) ))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_ADR(_BASE) (( ( _BASE ) + ( CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_OFFSET ) ))

// ******************************************* /Address Space

//************************************************ RegisterStructs


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTICONTROL register description at address offset 0x0
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTICONTROL
  * CTI Control register
  */

typedef union {
  struct {
    uint32_t CTIEN : 1;
    ///< Enable control:
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 31;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctictrl_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_WR_MASK (0xffffffffU)


///< Enable control:
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_CTIEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_CTIEN_BF_WID ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_CTIEN_BF_MSK (0x00000001)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_CTIEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_RES0_0_BF_OFF ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_RES0_0_BF_WID (31)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_RES0_0_BF_MSK (0xFFFFFFFE)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINTACK register description at address offset 0x10
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINTACK
  * CTI Interrupt Acknowledge register
  */

typedef union {
  struct {
    uint32_t INTACK : 32;
    ///< Acknowledges the corresponding event_out output
    ///< AccessType="WS" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiintack_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_RD_MASK (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_WR_MASK (0xffffffffU)


///< Acknowledges the corresponding event_out output
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_INTACK_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_INTACK_BF_WID (32)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_INTACK_BF_MSK (0xFFFFFFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_INTACK_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIAPPSET register description at address offset 0x14
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIAPPSET
  * CTI Application Channel Set register
  */

typedef union {
  struct {
    uint32_t APPSET : 4;
    ///< Sets the corresponding internal channel flag:
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiappset_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_WR_MASK (0xffffffffU)


///< Sets the corresponding internal channel flag:
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_APPSET_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_APPSET_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_APPSET_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_APPSET_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIAPPCLEAR register description at address offset 0x18
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIAPPCLEAR
  * CTI Application Channel Clear register
  */

typedef union {
  struct {
    uint32_t APPCLEAR : 4;
    ///< Clears the corresponding internal channel flag.
    ///< AccessType="WS" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="WS" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiappclr_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RD_MASK (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_WR_MASK (0xffffffffU)


///< Clears the corresponding internal channel flag.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_APPCLR_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_APPCLR_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_APPCLR_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_APPCLR_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIAPPPULSE register description at address offset 0x1c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIAPPPULSE
  * CTI Application Channel Pulse register
  */

typedef union {
  struct {
    uint32_t APPPULSE : 4;
    ///< Pulses the channel outputs.
    ///< AccessType="WS" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="WS" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiapppulse_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RD_MASK (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_WR_MASK (0xffffffffU)


///< Pulses the channel outputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_APPPULSE_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_APPPULSE_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_APPPULSE_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_APPPULSE_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN0 register description at address offset 0x20
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN0
  * CTI Trigger 0 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen0_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN1 register description at address offset 0x24
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN1
  * CTI Trigger 1 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen1_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN2 register description at address offset 0x28
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN2
  * CTI Trigger 2 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen2_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN3 register description at address offset 0x2c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN3
  * CTI Trigger 3 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen3_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN4 register description at address offset 0x30
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN4
  * CTI Trigger 4 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen4_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN5 register description at address offset 0x34
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN5
  * CTI Trigger 5 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen5_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN6 register description at address offset 0x38
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN6
  * CTI Trigger 6 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen6_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN7 register description at address offset 0x3c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN7
  * CTI Trigger 7 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen7_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN8 register description at address offset 0x40
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN8
  * CTI Trigger 8 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen8_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN9 register description at address offset 0x44
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN9
  * CTI Trigger 9 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen9_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN10 register description at address offset 0x48
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN10
  * CTI Trigger 10 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen10_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN11 register description at address offset 0x4c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN11
  * CTI Trigger 11 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen11_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN12 register description at address offset 0x50
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN12
  * CTI Trigger 12 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen12_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN13 register description at address offset 0x54
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN13
  * CTI Trigger 13 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen13_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN14 register description at address offset 0x58
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN14
  * CTI Trigger 14 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen14_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIINEN15 register description at address offset 0x5c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIINEN15
  * CTI Trigger 15 to Channel Enable register
  */

typedef union {
  struct {
    uint32_t TRIGINEN : 4;
    ///< Trigger input to channel mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiinen15_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_WR_MASK (0xffffffffU)


///< Trigger input to channel mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_TRIGINEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_TRIGINEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_TRIGINEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_TRIGINEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN0 register description at address offset 0xa0
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN0
  * CTI Channel to Trigger 0 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten0_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN1 register description at address offset 0xa4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN1
  * CTI Channel to Trigger 1 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten1_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN2 register description at address offset 0xa8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN2
  * CTI Channel to Trigger 2 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten2_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN3 register description at address offset 0xac
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN3
  * CTI Channel to Trigger 3 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten3_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN4 register description at address offset 0xb0
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN4
  * CTI Channel to Trigger 4 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten4_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN5 register description at address offset 0xb4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN5
  * CTI Channel to Trigger 5 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten5_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN6 register description at address offset 0xb8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN6
  * CTI Channel to Trigger 6 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten6_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN7 register description at address offset 0xbc
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN7
  * CTI Channel to Trigger 7 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten7_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN8 register description at address offset 0xc0
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN8
  * CTI Channel to Trigger 8 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten8_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN9 register description at address offset 0xc4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN9
  * CTI Channel to Trigger 9 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten9_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN10 register description at address offset 0xc8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN10
  * CTI Channel to Trigger 10 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten10_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN11 register description at address offset 0xcc
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN11
  * CTI Channel to Trigger 11 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten11_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN12 register description at address offset 0xd0
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN12
  * CTI Channel to Trigger 12 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten12_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN13 register description at address offset 0xd4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN13
  * CTI Channel to Trigger 13 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten13_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN14 register description at address offset 0xd8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN14
  * CTI Channel to Trigger 14 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten14_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIOUTEN15 register description at address offset 0xdc
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIOUTEN15
  * CTI Channel to Trigger 15 Enable register
  */

typedef union {
  struct {
    uint32_t TRIGOUTEN : 4;
    ///< Channel to trigger output mapping.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctiouten15_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_WR_MASK (0xffffffffU)


///< Channel to trigger output mapping.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_TRIGOUTEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_TRIGOUTEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_TRIGOUTEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_TRIGOUTEN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTITRIGINSTATUS register description at address offset 0x130
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTITRIGINSTATUS
  * CTI Trigger Input Status register
  */

typedef union {
  struct {
    uint32_t TRIGINSTATUS : 32;
    ///< Trigger input status.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctitriginstat_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_WR_MASK (0x00000000U)


///< Trigger input status.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_TRIGINSTAT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_TRIGINSTAT_BF_WID (32)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_TRIGINSTAT_BF_MSK (0xFFFFFFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_TRIGINSTAT_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTITRIGOUTSTATUS register description at address offset 0x134
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTITRIGOUTSTATUS
  * CTI Trigger Output Status register
  */

typedef union {
  struct {
    uint32_t TRIGOUTSTATUS : 32;
    ///< Trigger output status.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctitrigoutstat_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_WR_MASK (0x00000000U)


///< Trigger output status.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_TRIGOUTSTAT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_TRIGOUTSTAT_BF_WID (32)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_TRIGOUTSTAT_BF_MSK (0xFFFFFFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_TRIGOUTSTAT_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTICHINSTATUS register description at address offset 0x138
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTICHINSTATUS
  * CTI Channel Input Status register
  */

typedef union {
  struct {
    uint32_t CTICHINSTATUS : 4;
    ///< Channel input status.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctichinstat_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_WR_MASK (0x00000000U)


///< Channel input status.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTICHOUTSTATUS register description at address offset 0x13c
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTICHOUTSTATUS
  * CTI Channel Output Status register
  */

typedef union {
  struct {
    uint32_t CTICHOUTSTATUS : 4;
    ///< Channel output status.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctichoutstat_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_WR_MASK (0x00000000U)


///< Channel output status.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CTIGATE register description at address offset 0x140
  *
  * Register default value:        0x0000000F
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CTIGATE
  * Enable CTI Channel Gate register
  */

typedef union {
  struct {
    uint32_t CTIGATEEN : 4;
    ///< Enables the propagation of channel events out of the CTI, one bit
    ///< per channel.
    ///< AccessType="RW" BitOffset="0" ResetValue="0xF"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ctigate_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_DEFAULT (0x0000000fU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_WR_MASK (0xffffffffU)


///< Enables the propagation of channel events out of the CTI, one bit
///< per channel.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_CTIGATEEN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_CTIGATEEN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_CTIGATEEN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_CTIGATEEN_BF_DEF (0x0000000F)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ASICCTRL register description at address offset 0x144
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ASICCTRL
  * External Multiplexer Control register
  */

typedef union {
  struct {
    uint32_t ASICCTRL : 8;
    ///< Set and clear external output signal.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_asicctrl_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_WR_MASK (0xffffffffU)


///< Set and clear external output signal.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ITCHOUT register description at address offset 0xee4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ITCHOUT
  * Integration Test Channel Output register
  */

typedef union {
  struct {
    uint32_t CTICHOUT : 4;
    ///< Pulses the channel outputs.
    ///< AccessType="WS" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_itchout_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RD_MASK (0xfffffff0U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_WR_MASK (0xffffffffU)


///< Pulses the channel outputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_CTICHOUT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_CTICHOUT_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_CTICHOUT_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_CTICHOUT_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ITTRIGOUT register description at address offset 0xee8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ITTRIGOUT
  * Integration Test Trigger Output register
  */

typedef union {
  struct {
    uint32_t CTITRIGOUT : 16;
    ///< Set/clear trigger output signal. Reads return the value in the register
    ///< if SW_HANDSHAKE=1, otherwise 0 is returned if SW_HANDSHAKE=0. Writes:
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 16;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ittrigout_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_WR_MASK (0xffffffffU)


///< Set/clear trigger output signal. Reads return the value in the register
///< if SW_HANDSHAKE=1, otherwise 0 is returned if SW_HANDSHAKE=0. Writes:
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_CTITRIGOUT_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_CTITRIGOUT_BF_WID (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_CTITRIGOUT_BF_MSK (0x0000FFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_CTITRIGOUT_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RES0_0_BF_OFF (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RES0_0_BF_WID (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RES0_0_BF_MSK (0xFFFF0000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ITCHIN register description at address offset 0xef4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ITCHIN
  * Integration Test Channel Input register
  */

typedef union {
  struct {
    uint32_t CTICHIN : 4;
    ///< Reads the latched value of the channel inputs.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 28;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_itchin_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_WR_MASK (0x00000000U)


///< Reads the latched value of the channel inputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_CTICHIN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_CTICHIN_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_CTICHIN_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_CTICHIN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_RES0_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_RES0_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_RES0_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ITTRIGIN register description at address offset 0xef8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ITTRIGIN
  * Integration Test Trigger Input register
  */

typedef union {
  struct {
    uint32_t CTITRIGIN : 16;
    ///< Reads the latched value of the trigger inputs.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 16;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="16" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_ittrigin_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_WR_MASK (0x00000000U)


///< Reads the latched value of the trigger inputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_CTITRIGIN_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_CTITRIGIN_BF_WID (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_CTITRIGIN_BF_MSK (0x0000FFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_CTITRIGIN_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RES0_0_BF_OFF (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RES0_0_BF_WID (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RES0_0_BF_MSK (0xFFFF0000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_ITCTRL register description at address offset 0xf00
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/ITCTRL
  * Integration Mode Control Register
  */

typedef union {
  struct {
    uint32_t IME : 1;
    ///< Integration Mode Enable. When set, the component enters integration
    ///< mode, enabling topology detection or integration testing to be performed.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 31;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_itctrl_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_WR_MASK (0xffffffffU)


///< Integration Mode Enable. When set, the component enters integration
///< mode, enabling topology detection or integration testing to be performed.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_IME_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_IME_BF_WID ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_IME_BF_MSK (0x00000001)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_IME_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_RES0_0_BF_OFF ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_RES0_0_BF_WID (31)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_RES0_0_BF_MSK (0xFFFFFFFE)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CLAIMSET register description at address offset 0xfa0
  *
  * Register default value:        0x0000000F
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CLAIMSET
  * Claim Tag Set Register
  */

typedef union {
  struct {
    uint32_t SET : 4;
    ///< A bit-programmable register bank that sets the claim tag value. A
    ///< read returns a logic 1 for all implemented locations.
    ///< AccessType="RW" BitOffset="0" ResetValue="0xF"
    uint32_t RAZWI_0 : 28;
    ///< RAZ/WI
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_claimset_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_DEFAULT (0x0000000fU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_WR_MASK (0xffffffffU)


///< A bit-programmable register bank that sets the claim tag value. A
///< read returns a logic 1 for all implemented locations.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_SET_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_SET_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_SET_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_SET_BF_DEF (0x0000000F)

///< RAZ/WI
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RAZWI_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RAZWI_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RAZWI_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_RAZWI_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CLAIMCLR register description at address offset 0xfa4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CLAIMCLR
  * Claim Tag Clear Register
  */

typedef union {
  struct {
    uint32_t CLR : 4;
    ///< A bit-programmable register bank that clears the claim tag value.
    ///< It is zero at reset. It is used by software agents to signal to each
    ///< other ownership of the hardware. It has no direct effect on the hardware
    ///< itself.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t RAZWI_0 : 28;
    ///< RAZ/WI
    ///< AccessType="RW" BitOffset="4" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_claimclr_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_WR_MASK (0xffffffffU)


///< A bit-programmable register bank that clears the claim tag value.
///< It is zero at reset. It is used by software agents to signal to each
///< other ownership of the hardware. It has no direct effect on the hardware
///< itself.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_CLR_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_CLR_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_CLR_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_CLR_BF_DEF (0x00000000)

///< RAZ/WI
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RAZWI_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RAZWI_0_BF_WID (28)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RAZWI_0_BF_MSK (0xFFFFFFF0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_RAZWI_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_DEVAFF0 register description at address offset 0xfa8
  *
  * Register default value:        0xFFFFFFFF
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/DEVAFF0
  * Device Affinity register 0
  */

typedef union {
  struct {
    uint32_t DEVAFF0 : 32;
    ///< Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off
    ///< inputs.
    ///< AccessType="RO" BitOffset="0" ResetValue="0xFFFFFFFF"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_devaff0_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_DEFAULT (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_WR_MASK (0x00000000U)


///< Lower 32-bits of DEVAFF. The value is set by the devaff[31:0] tie-off
///< inputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_BF_WID (32)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_BF_MSK (0xFFFFFFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_BF_DEF (0xFFFFFFFF)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_DEVAFF1 register description at address offset 0xfac
  *
  * Register default value:        0xFFFFFFFF
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/DEVAFF1
  * Device Affinity register 1
  */

typedef union {
  struct {
    uint32_t DEVAFF1 : 32;
    ///< Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off
    ///< inputs.
    ///< AccessType="RO" BitOffset="0" ResetValue="0xFFFFFFFF"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_devaff1_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_DEFAULT (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_WR_MASK (0x00000000U)


///< Upper 32-bits of DEVAFF. The value is set by the devaff[63:32] tie-off
///< inputs.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_BF_WID (32)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_BF_MSK (0xFFFFFFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_BF_DEF (0xFFFFFFFF)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_AUTHSTATUS register description at address offset 0xfb8
  *
  * Register default value:        0x0000000A
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/AUTHSTATUS
  * Authentication Status Register
  */

typedef union {
  struct {
    uint32_t NSID : 2;
    ///< Non-secure invasive debug.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x2"
    uint32_t NSNID : 2;
    ///< Non-secure non-invasive debug.
    ///< AccessType="RO" BitOffset="2" ResetValue="0x2"
    uint32_t SID : 2;
    ///< Secure invasive debug.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
    uint32_t SNID : 2;
    ///< Secure non-invasive debug.
    ///< AccessType="RO" BitOffset="6" ResetValue="0x0"
    uint32_t HID : 2;
    ///< Hypervisor invasive debug.
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
    uint32_t HNID : 2;
    ///< Hypervisor non-invasive debug.
    ///< AccessType="RO" BitOffset="10" ResetValue="0x0"
    uint32_t RES0_0 : 20;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="12" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_authstat_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_DEFAULT (0x0000000fU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_WR_MASK (0x00000000U)


///< Non-secure invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSID_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSID_BF_MSK (0x00000003)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSID_BF_DEF (0x00000002)

///< Non-secure non-invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSNID_BF_OFF ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSNID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSNID_BF_MSK (0x0000000C)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_NSNID_BF_DEF (0x00000008)

///< Secure invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SID_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SID_BF_MSK (0x00000030)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SID_BF_DEF (0x00000000)

///< Secure non-invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SNID_BF_OFF ( 6)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SNID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SNID_BF_MSK (0x000000C0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_SNID_BF_DEF (0x00000000)

///< Hypervisor invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HID_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HID_BF_MSK (0x00000300)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HID_BF_DEF (0x00000000)

///< Hypervisor non-invasive debug.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HNID_BF_OFF (10)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HNID_BF_WID ( 2)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HNID_BF_MSK (0x00000C00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_HNID_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RES0_0_BF_OFF (12)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RES0_0_BF_WID (20)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RES0_0_BF_MSK (0xFFFFF000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_DEVARCH register description at address offset 0xfbc
  *
  * Register default value:        0x47701A14
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/DEVARCH
  * Device Architecture Register
  */

typedef union {
  struct {
    uint32_t ARCHID : 16;
    ///< Architecture ID. Returns 0x1a14, identifying Cross Trigger Interface
    ///< architecture v2.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x1A14"
    uint32_t REVISION : 4;
    ///< Architecture revision. Returns the revision of the architecture that
    ///< the ARCHID field specifies.
    ///< AccessType="RO" BitOffset="16" ResetValue="0x0"
    uint32_t PRESENT : 1;
    ///< Returns 1, indicating that the DEVARCH register is present.
    ///< AccessType="RO" BitOffset="20" ResetValue="0x1"
    uint32_t ARCHITECT : 11;
    ///< Returns 0x23b, denoting Arm as architect of the component.
    ///< AccessType="RO" BitOffset="21" ResetValue="0x23B"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_devarch_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_DEFAULT (0x47701a14U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_WR_MASK (0x00000000U)


///< Architecture ID. Returns 0x1a14, identifying Cross Trigger Interface
///< architecture v2.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHID_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHID_BF_WID (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHID_BF_MSK (0x0000FFFF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHID_BF_DEF (0x00001A14)

///< Architecture revision. Returns the revision of the architecture that
///< the ARCHID field specifies.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_REVISION_BF_OFF (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_REVISION_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_REVISION_BF_MSK (0x000F0000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_REVISION_BF_DEF (0x00000000)

///< Returns 1, indicating that the DEVARCH register is present.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_PRESENT_BF_OFF (20)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_PRESENT_BF_WID ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_PRESENT_BF_MSK (0x00100000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_PRESENT_BF_DEF (0x00100000)

///< Returns 0x23b, denoting Arm as architect of the component.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHITECT_BF_OFF (21)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHITECT_BF_WID (11)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHITECT_BF_MSK (0xFFE00000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ARCHITECT_BF_DEF (0x47600000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_DEVID register description at address offset 0xfc8
  *
  * Register default value:        0x01041000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/DEVID
  * Device Configuration Register
  */

typedef union {
  struct {
    uint32_t EXT_MUX_NUM : 5;
    ///< Indicates the value of the EXT_MUX_NUM parameter, which determines
    ///< if there is any external multiplexing on the trigger inputs and outputs.
    ///< 0 indicates no multiplexing.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 3;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="5" ResetValue="0x0"
    uint32_t NUM_TRIG : 8;
    ///< Indicates the maximum number of triggers - the maximum of the two
    ///< parameters, NUM_EVENT_SLAVES and NUM_EVENT_MASTERS.
    ///< AccessType="RO" BitOffset="8" ResetValue="0x10"
    uint32_t NUM_CH : 4;
    ///< The number of channels. Always 4.
    ///< AccessType="RO" BitOffset="16" ResetValue="0x4"
    uint32_t RES0_1 : 4;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="20" ResetValue="0x0"
    uint32_t INOUT : 1;
    ///< Indicates channel inputs are also masked by the CTIGATE register.
    ///< Always 1.
    ///< AccessType="RO" BitOffset="24" ResetValue="0x1"
    uint32_t RES0_2 : 7;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="25" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_devid_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_DEFAULT (0x01041000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_WR_MASK (0x00000000U)


///< Indicates the value of the EXT_MUX_NUM parameter, which determines
///< if there is any external multiplexing on the trigger inputs and outputs.
///< 0 indicates no multiplexing.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_EXT_MUX_NUM_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_EXT_MUX_NUM_BF_WID ( 5)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_EXT_MUX_NUM_BF_MSK (0x0000001F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_EXT_MUX_NUM_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_0_BF_OFF ( 5)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_0_BF_WID ( 3)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_0_BF_MSK (0x000000E0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_0_BF_DEF (0x00000000)

///< Indicates the maximum number of triggers - the maximum of the two
///< parameters, NUM_EVENT_SLAVES and NUM_EVENT_MASTERS.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_TRIG_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_TRIG_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_TRIG_BF_MSK (0x0000FF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_TRIG_BF_DEF (0x00001000)

///< The number of channels. Always 4.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_CH_BF_OFF (16)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_CH_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_CH_BF_MSK (0x000F0000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_NUM_CH_BF_DEF (0x00040000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_1_BF_OFF (20)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_1_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_1_BF_MSK (0x00F00000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_1_BF_DEF (0x00000000)

///< Indicates channel inputs are also masked by the CTIGATE register.
///< Always 1.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_INOUT_BF_OFF (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_INOUT_BF_WID ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_INOUT_BF_MSK (0x01000000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_INOUT_BF_DEF (0x01000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_2_BF_OFF (25)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_2_BF_WID ( 7)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_2_BF_MSK (0xFE000000)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_RES0_2_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_DEVTYPE register description at address offset 0xfcc
  *
  * Register default value:        0x00000014
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/DEVTYPE
  * Device Type Identifier Register
  */

typedef union {
  struct {
    uint32_t MAJOR : 4;
    ///< Major classification. Returns 0x4, indicating this component performs
    ///< Debug Control.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x4"
    uint32_t SUB : 4;
    ///< Minor classification. Returns 0x1, indicating this component is a
    ///< Trigger-Matrix.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x1"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_devtype_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_DEFAULT (0x00000014U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_WR_MASK (0x00000000U)


///< Major classification. Returns 0x4, indicating this component performs
///< Debug Control.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_MAJOR_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_MAJOR_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_MAJOR_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_MAJOR_BF_DEF (0x00000004)

///< Minor classification. Returns 0x1, indicating this component is a
///< Trigger-Matrix.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_SUB_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_SUB_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_SUB_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_SUB_BF_DEF (0x00000010)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR4 register description at address offset 0xfd0
  *
  * Register default value:        0x00000004
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR4
  * Peripheral Identification Register 4
  */

typedef union {
  struct {
    uint32_t DES_2 : 4;
    ///< JEP106 continuation code. Together, with PIDR2.DES_1 and PIDR1.DES_0,
    ///< they indicate the designer of the component and not the implementer,
    ///< except where the two are the same.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x4"
    uint32_t SIZE : 4;
    ///< Indicates the memory size that is used by this component. Returns
    ///< 0 indicating that the component uses an UNKNOWN number of 4KB blocks.
    ///< Using the SIZE field to indicate the size of the component is deprecated.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr4_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_DEFAULT (0x00000004U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_WR_MASK (0x00000000U)


///< JEP106 continuation code. Together, with PIDR2.DES_1 and PIDR1.DES_0,
///< they indicate the designer of the component and not the implementer,
///< except where the two are the same.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_DES_2_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_DES_2_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_DES_2_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_DES_2_BF_DEF (0x00000004)

///< Indicates the memory size that is used by this component. Returns
///< 0 indicating that the component uses an UNKNOWN number of 4KB blocks.
///< Using the SIZE field to indicate the size of the component is deprecated.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_SIZE_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_SIZE_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_SIZE_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_SIZE_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR5 register description at address offset 0xfd4
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR5
  * Peripheral Identification Register 5
  */

typedef union {
  struct {
    uint32_t PIDR5 : 8;
    ///< Reserved.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr5_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_WR_MASK (0x00000000U)


///< Reserved.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR6 register description at address offset 0xfd8
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR6
  * Peripheral Identification Register 6
  */

typedef union {
  struct {
    uint32_t PIDR6 : 8;
    ///< Reserved.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr6_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_WR_MASK (0x00000000U)


///< Reserved.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR7 register description at address offset 0xfdc
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR7
  * Peripheral Identification Register 7
  */

typedef union {
  struct {
    uint32_t PIDR7 : 8;
    ///< Reserved.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr7_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_WR_MASK (0x00000000U)


///< Reserved.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR0 register description at address offset 0xfe0
  *
  * Register default value:        0x000000ED
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR0
  * Peripheral Identification Register 0
  */

typedef union {
  struct {
    uint32_t PART_0 : 8;
    ///< Part number, bits[7:0]. Taken together with PIDR1.PART_1 it indicates
    ///< the component. The Part Number is selected by the designer of the
    ///< component.
    ///< AccessType="RO" BitOffset="0" ResetValue="0xED"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr0_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_DEFAULT (0x000000edU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_WR_MASK (0x00000000U)


///< Part number, bits[7:0]. Taken together with PIDR1.PART_1 it indicates
///< the component. The Part Number is selected by the designer of the
///< component.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_PART_0_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_PART_0_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_PART_0_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_PART_0_BF_DEF (0x000000ED)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR1 register description at address offset 0xfe4
  *
  * Register default value:        0x000000B9
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR1
  * Peripheral Identification Register 1
  */

typedef union {
  struct {
    uint32_t PART_1 : 4;
    ///< Part number, bits[11:8]. Taken together with PIDR0.PART_0 it indicates
    ///< the component. The Part Number is selected by the designer of the
    ///< component.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x9"
    uint32_t DES_0 : 4;
    ///< JEP106 identification code, bits[3:0]. Together, with PIDR4.DES_2
    ///< and PIDR2.DES_1, they indicate the designer of the component and not
    ///< the implementer, except where the two are the same.
    ///< AccessType="RO" BitOffset="4" ResetValue="0xB"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr1_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_DEFAULT (0x000000b9U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_WR_MASK (0x00000000U)


///< Part number, bits[11:8]. Taken together with PIDR0.PART_0 it indicates
///< the component. The Part Number is selected by the designer of the
///< component.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_PART_1_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_PART_1_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_PART_1_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_PART_1_BF_DEF (0x00000009)

///< JEP106 identification code, bits[3:0]. Together, with PIDR4.DES_2
///< and PIDR2.DES_1, they indicate the designer of the component and not
///< the implementer, except where the two are the same.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_DES_0_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_DES_0_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_DES_0_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_DES_0_BF_DEF (0x000000B0)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR2 register description at address offset 0xfe8
  *
  * Register default value:        0x0000003B
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR2
  * Peripheral Identification Register 2
  */

typedef union {
  struct {
    uint32_t DES_1 : 3;
    ///< JEP106 identification code, bits[6:4]. Together, with PIDR4.DES_2
    ///< and PIDR1.DES_0, they indicate the designer of the component and not
    ///< the implementer, except where the two are the same.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x3"
    uint32_t JEDEC : 1;
    ///< 1 - Always set. Indicates that a JEDEC assigned value is used.
    ///< AccessType="RO" BitOffset="3" ResetValue="0x1"
    uint32_t REVISION : 4;
    ///< Revision. It is an incremental value starting at 0x0 for the first
    ///< design of a component. See the Component list in Chapter 1 for information
    ///< on the RTL revision of the component.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x3"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr2_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_DEFAULT (0x0000003bU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_WR_MASK (0x00000000U)


///< JEP106 identification code, bits[6:4]. Together, with PIDR4.DES_2
///< and PIDR1.DES_0, they indicate the designer of the component and not
///< the implementer, except where the two are the same.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_DES_1_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_DES_1_BF_WID ( 3)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_DES_1_BF_MSK (0x00000007)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_DES_1_BF_DEF (0x00000003)

///< 1 - Always set. Indicates that a JEDEC assigned value is used.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_JEDEC_BF_OFF ( 3)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_JEDEC_BF_WID ( 1)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_JEDEC_BF_MSK (0x00000008)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_JEDEC_BF_DEF (0x00000008)

///< Revision. It is an incremental value starting at 0x0 for the first
///< design of a component. See the Component list in Chapter 1 for information
///< on the RTL revision of the component.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_REVISION_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_REVISION_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_REVISION_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_REVISION_BF_DEF (0x00000030)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_PIDR3 register description at address offset 0xfec
  *
  * Register default value:        0x00000000
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/PIDR3
  * Peripheral Identification Register 3
  */

typedef union {
  struct {
    uint32_t CMOD : 4;
    ///< Customer Modified. Where the component is reusable IP, this value
    ///< indicates if the customer has modified the behavior of the component.
    ///< In most cases this field is 0x0.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t REVAND : 4;
    ///< This field indicates minor errata fixes specific to this design, for
    ///< example metal fixes after implementation. In most cases this field
    ///< is 0x0.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_pidr3_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_DEFAULT (0x00000000U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_WR_MASK (0x00000000U)


///< Customer Modified. Where the component is reusable IP, this value
///< indicates if the customer has modified the behavior of the component.
///< In most cases this field is 0x0.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_CMOD_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_CMOD_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_CMOD_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_CMOD_BF_DEF (0x00000000)

///< This field indicates minor errata fixes specific to this design, for
///< example metal fixes after implementation. In most cases this field
///< is 0x0.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_REVAND_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_REVAND_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_REVAND_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_REVAND_BF_DEF (0x00000000)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CIDR0 register description at address offset 0xff0
  *
  * Register default value:        0x0000000D
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CIDR0
  * Component Identification Register 0
  */

typedef union {
  struct {
    uint32_t PRMBL_0 : 8;
    ///< Preamble. Returns 0x0D.
    ///< AccessType="RO" BitOffset="0" ResetValue="0xD"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_cidr0_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_DEFAULT (0x0000000dU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_WR_MASK (0x00000000U)


///< Preamble. Returns 0x0D.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_PRMBL_0_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_PRMBL_0_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_PRMBL_0_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_PRMBL_0_BF_DEF (0x0000000D)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CIDR1 register description at address offset 0xff4
  *
  * Register default value:        0x00000090
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CIDR1
  * Component Identification Register 1
  */

typedef union {
  struct {
    uint32_t PRMBL_1 : 4;
    ///< Preamble. Returns 0x0.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x0"
    uint32_t CLASS : 4;
    ///< Component class. Returns 0x9, indicating this is a CoreSight component.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x9"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_cidr1_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_DEFAULT (0x00000090U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_WR_MASK (0x00000000U)


///< Preamble. Returns 0x0.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_PRMBL_1_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_PRMBL_1_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_PRMBL_1_BF_MSK (0x0000000F)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_PRMBL_1_BF_DEF (0x00000000)

///< Component class. Returns 0x9, indicating this is a CoreSight component.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_CLASS_BF_OFF ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_CLASS_BF_WID ( 4)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_CLASS_BF_MSK (0x000000F0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_CLASS_BF_DEF (0x00000090)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CIDR2 register description at address offset 0xff8
  *
  * Register default value:        0x00000005
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CIDR2
  * Component Identification Register 2
  */

typedef union {
  struct {
    uint32_t PRMBL_2 : 8;
    ///< Preamble. Returns 0x05.
    ///< AccessType="RO" BitOffset="0" ResetValue="0x5"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_cidr2_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_DEFAULT (0x00000005U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_WR_MASK (0x00000000U)


///< Preamble. Returns 0x05.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_PRMBL_2_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_PRMBL_2_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_PRMBL_2_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_PRMBL_2_BF_DEF (0x00000005)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_RES0_0_BF_DEF (0x00000000)


/** @brief CS_SOC_600_CTI_HWC_16BIT_APB4_SLAVE_0_MM_ADDRESSBLOCK_0_CIDR3 register description at address offset 0xffc
  *
  * Register default value:        0x000000B1
  * Register full path in IP: cs_soc_600_cti_hwc_16bit/APB4_Slave_0_MM/addressBlock_0/CIDR3
  * Component Identification Register 3
  */

typedef union {
  struct {
    uint32_t PRMBL_3 : 8;
    ///< Preamble. Returns 0xB1.
    ///< AccessType="RO" BitOffset="0" ResetValue="0xB1"
    uint32_t RES0_0 : 24;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RO" BitOffset="8" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_600_cti_16bit_addrblk_0_cidr3_reg_t;

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_DEFAULT (0x000000b1U)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_RD_MASK (0xffffffffU)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_WR_MASK (0x00000000U)


///< Preamble. Returns 0xB1.
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_PRMBL_3_BF_OFF ( 0)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_PRMBL_3_BF_WID ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_PRMBL_3_BF_MSK (0x000000FF)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_PRMBL_3_BF_DEF (0x000000B1)

///< Reserved bit or field with SBZP behavior
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_RES0_0_BF_OFF ( 8)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_RES0_0_BF_WID (24)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_RES0_0_BF_MSK (0xFFFFFF00)
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_RES0_0_BF_DEF (0x00000000)

//************************************************ /RegisterStructs


// ******************************************* Register pointer macros

#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctictrl_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICTRL_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiintack_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINTACK_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiappset_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPSET_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiappclr_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPCLR_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiapppulse_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIAPPPULSE_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen0_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN0_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen1_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN1_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen2_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN2_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen3_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN3_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen4_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN4_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen5_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN5_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen6_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN6_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen7_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN7_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen8_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN8_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen9_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN9_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen10_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN10_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen11_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN11_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen12_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN12_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen13_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN13_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen14_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN14_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiinen15_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIINEN15_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten0_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN0_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten1_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN1_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten2_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN2_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten3_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN3_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten4_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN4_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten5_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN5_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten6_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN6_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten7_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN7_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten8_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN8_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten9_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN9_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten10_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN10_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten11_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN11_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten12_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN12_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten13_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN13_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten14_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN14_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctiouten15_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIOUTEN15_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctitriginstat_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGINSTAT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctitrigoutstat_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTITRIGOUTSTAT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctichinstat_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHINSTAT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctichoutstat_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTICHOUTSTAT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ctigate_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CTIGATE_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_asicctrl_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ASICCTRL_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_itchout_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHOUT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ittrigout_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGOUT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_itchin_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCHIN_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_ittrigin_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITTRIGIN_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_itctrl_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_ITCTRL_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_claimset_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMSET_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_claimclr_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CLAIMCLR_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_devaff0_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF0_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_devaff1_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVAFF1_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_authstat_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_AUTHSTAT_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_devarch_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVARCH_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_devid_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVID_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_devtype_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_DEVTYPE_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr4_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR4_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr5_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR5_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr6_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR6_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr7_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR7_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr0_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR0_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr1_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR1_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr2_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR2_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_pidr3_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_PIDR3_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_cidr0_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR0_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_cidr1_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR1_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_cidr2_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR2_ADR(_BASE))
#define CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_REG(_BASE) ((cs_soc_600_cti_16bit_addrblk_0_cidr3_reg_t*) CS_SOC_600_CTI_16BIT_ADDRBLK_0_CIDR3_ADR(_BASE))

// ******************************************* /Register pointer macros


// ******************************************* AddressSpace struct
typedef struct
{
    cs_soc_600_cti_16bit_addrblk_0_ctictrl_reg_t ADDRBLK_0_CTICTRL; /*< Address offset = 0x0 */
    const uint8_t        reservedArea0 [12];  /*< Address offset = 0x4 */
    cs_soc_600_cti_16bit_addrblk_0_ctiintack_reg_t ADDRBLK_0_CTIINTACK; /*< Address offset = 0x10 */
    cs_soc_600_cti_16bit_addrblk_0_ctiappset_reg_t ADDRBLK_0_CTIAPPSET; /*< Address offset = 0x14 */
    cs_soc_600_cti_16bit_addrblk_0_ctiappclr_reg_t ADDRBLK_0_CTIAPPCLR; /*< Address offset = 0x18 */
    cs_soc_600_cti_16bit_addrblk_0_ctiapppulse_reg_t ADDRBLK_0_CTIAPPPULSE; /*< Address offset = 0x1c */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen0_reg_t ADDRBLK_0_CTIINEN0; /*< Address offset = 0x20 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen1_reg_t ADDRBLK_0_CTIINEN1; /*< Address offset = 0x24 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen2_reg_t ADDRBLK_0_CTIINEN2; /*< Address offset = 0x28 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen3_reg_t ADDRBLK_0_CTIINEN3; /*< Address offset = 0x2c */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen4_reg_t ADDRBLK_0_CTIINEN4; /*< Address offset = 0x30 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen5_reg_t ADDRBLK_0_CTIINEN5; /*< Address offset = 0x34 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen6_reg_t ADDRBLK_0_CTIINEN6; /*< Address offset = 0x38 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen7_reg_t ADDRBLK_0_CTIINEN7; /*< Address offset = 0x3c */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen8_reg_t ADDRBLK_0_CTIINEN8; /*< Address offset = 0x40 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen9_reg_t ADDRBLK_0_CTIINEN9; /*< Address offset = 0x44 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen10_reg_t ADDRBLK_0_CTIINEN10; /*< Address offset = 0x48 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen11_reg_t ADDRBLK_0_CTIINEN11; /*< Address offset = 0x4c */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen12_reg_t ADDRBLK_0_CTIINEN12; /*< Address offset = 0x50 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen13_reg_t ADDRBLK_0_CTIINEN13; /*< Address offset = 0x54 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen14_reg_t ADDRBLK_0_CTIINEN14; /*< Address offset = 0x58 */
    cs_soc_600_cti_16bit_addrblk_0_ctiinen15_reg_t ADDRBLK_0_CTIINEN15; /*< Address offset = 0x5c */
    const uint8_t        reservedArea1 [64];  /*< Address offset = 0x60 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten0_reg_t ADDRBLK_0_CTIOUTEN0; /*< Address offset = 0xa0 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten1_reg_t ADDRBLK_0_CTIOUTEN1; /*< Address offset = 0xa4 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten2_reg_t ADDRBLK_0_CTIOUTEN2; /*< Address offset = 0xa8 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten3_reg_t ADDRBLK_0_CTIOUTEN3; /*< Address offset = 0xac */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten4_reg_t ADDRBLK_0_CTIOUTEN4; /*< Address offset = 0xb0 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten5_reg_t ADDRBLK_0_CTIOUTEN5; /*< Address offset = 0xb4 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten6_reg_t ADDRBLK_0_CTIOUTEN6; /*< Address offset = 0xb8 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten7_reg_t ADDRBLK_0_CTIOUTEN7; /*< Address offset = 0xbc */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten8_reg_t ADDRBLK_0_CTIOUTEN8; /*< Address offset = 0xc0 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten9_reg_t ADDRBLK_0_CTIOUTEN9; /*< Address offset = 0xc4 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten10_reg_t ADDRBLK_0_CTIOUTEN10; /*< Address offset = 0xc8 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten11_reg_t ADDRBLK_0_CTIOUTEN11; /*< Address offset = 0xcc */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten12_reg_t ADDRBLK_0_CTIOUTEN12; /*< Address offset = 0xd0 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten13_reg_t ADDRBLK_0_CTIOUTEN13; /*< Address offset = 0xd4 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten14_reg_t ADDRBLK_0_CTIOUTEN14; /*< Address offset = 0xd8 */
    cs_soc_600_cti_16bit_addrblk_0_ctiouten15_reg_t ADDRBLK_0_CTIOUTEN15; /*< Address offset = 0xdc */
    const uint8_t        reservedArea2 [80];  /*< Address offset = 0xe0 */
    cs_soc_600_cti_16bit_addrblk_0_ctitriginstat_reg_t ADDRBLK_0_CTITRIGINSTAT; /*< Address offset = 0x130 */
    cs_soc_600_cti_16bit_addrblk_0_ctitrigoutstat_reg_t ADDRBLK_0_CTITRIGOUTSTAT; /*< Address offset = 0x134 */
    cs_soc_600_cti_16bit_addrblk_0_ctichinstat_reg_t ADDRBLK_0_CTICHINSTAT; /*< Address offset = 0x138 */
    cs_soc_600_cti_16bit_addrblk_0_ctichoutstat_reg_t ADDRBLK_0_CTICHOUTSTAT; /*< Address offset = 0x13c */
    cs_soc_600_cti_16bit_addrblk_0_ctigate_reg_t ADDRBLK_0_CTIGATE; /*< Address offset = 0x140 */
    cs_soc_600_cti_16bit_addrblk_0_asicctrl_reg_t ADDRBLK_0_ASICCTRL; /*< Address offset = 0x144 */
    const uint8_t        reservedArea3 [3484]; /*< Address offset = 0x148 */
    cs_soc_600_cti_16bit_addrblk_0_itchout_reg_t ADDRBLK_0_ITCHOUT; /*< Address offset = 0xee4 */
    cs_soc_600_cti_16bit_addrblk_0_ittrigout_reg_t ADDRBLK_0_ITTRIGOUT; /*< Address offset = 0xee8 */
    const uint8_t        reservedArea4 [8];   /*< Address offset = 0xeec */
    cs_soc_600_cti_16bit_addrblk_0_itchin_reg_t ADDRBLK_0_ITCHIN; /*< Address offset = 0xef4 */
    cs_soc_600_cti_16bit_addrblk_0_ittrigin_reg_t ADDRBLK_0_ITTRIGIN; /*< Address offset = 0xef8 */
    const uint8_t        reservedArea5 [4];   /*< Address offset = 0xefc */
    cs_soc_600_cti_16bit_addrblk_0_itctrl_reg_t ADDRBLK_0_ITCTRL; /*< Address offset = 0xf00 */
    const uint8_t        reservedArea6 [156]; /*< Address offset = 0xf04 */
    cs_soc_600_cti_16bit_addrblk_0_claimset_reg_t ADDRBLK_0_CLAIMSET; /*< Address offset = 0xfa0 */
    cs_soc_600_cti_16bit_addrblk_0_claimclr_reg_t ADDRBLK_0_CLAIMCLR; /*< Address offset = 0xfa4 */
    cs_soc_600_cti_16bit_addrblk_0_devaff0_reg_t ADDRBLK_0_DEVAFF0; /*< Address offset = 0xfa8 */
    cs_soc_600_cti_16bit_addrblk_0_devaff1_reg_t ADDRBLK_0_DEVAFF1; /*< Address offset = 0xfac */
    const uint8_t        reservedArea7 [8];   /*< Address offset = 0xfb0 */
    cs_soc_600_cti_16bit_addrblk_0_authstat_reg_t ADDRBLK_0_AUTHSTAT; /*< Address offset = 0xfb8 */
    cs_soc_600_cti_16bit_addrblk_0_devarch_reg_t ADDRBLK_0_DEVARCH; /*< Address offset = 0xfbc */
    const uint8_t        reservedArea8 [8];   /*< Address offset = 0xfc0 */
    cs_soc_600_cti_16bit_addrblk_0_devid_reg_t ADDRBLK_0_DEVID; /*< Address offset = 0xfc8 */
    cs_soc_600_cti_16bit_addrblk_0_devtype_reg_t ADDRBLK_0_DEVTYPE; /*< Address offset = 0xfcc */
    cs_soc_600_cti_16bit_addrblk_0_pidr4_reg_t ADDRBLK_0_PIDR4; /*< Address offset = 0xfd0 */
    cs_soc_600_cti_16bit_addrblk_0_pidr5_reg_t ADDRBLK_0_PIDR5; /*< Address offset = 0xfd4 */
    cs_soc_600_cti_16bit_addrblk_0_pidr6_reg_t ADDRBLK_0_PIDR6; /*< Address offset = 0xfd8 */
    cs_soc_600_cti_16bit_addrblk_0_pidr7_reg_t ADDRBLK_0_PIDR7; /*< Address offset = 0xfdc */
    cs_soc_600_cti_16bit_addrblk_0_pidr0_reg_t ADDRBLK_0_PIDR0; /*< Address offset = 0xfe0 */
    cs_soc_600_cti_16bit_addrblk_0_pidr1_reg_t ADDRBLK_0_PIDR1; /*< Address offset = 0xfe4 */
    cs_soc_600_cti_16bit_addrblk_0_pidr2_reg_t ADDRBLK_0_PIDR2; /*< Address offset = 0xfe8 */
    cs_soc_600_cti_16bit_addrblk_0_pidr3_reg_t ADDRBLK_0_PIDR3; /*< Address offset = 0xfec */
    cs_soc_600_cti_16bit_addrblk_0_cidr0_reg_t ADDRBLK_0_CIDR0; /*< Address offset = 0xff0 */
    cs_soc_600_cti_16bit_addrblk_0_cidr1_reg_t ADDRBLK_0_CIDR1; /*< Address offset = 0xff4 */
    cs_soc_600_cti_16bit_addrblk_0_cidr2_reg_t ADDRBLK_0_CIDR2; /*< Address offset = 0xff8 */
    cs_soc_600_cti_16bit_addrblk_0_cidr3_reg_t ADDRBLK_0_CIDR3; /*< Address offset = 0xffc */
} cs_soc_600_cti_16bit_t;     // size: 0x0110

// AddressSpace struct pointer
//
#define CS_SOC_CTI16BIT_APB4_SLAVE_0_MM  ((cs_soc_600_cti_16bit_t*) CS_SOC_CTI16BIT_APB4_SLAVE_0_MM_BASE)


// ******************************************* /Address Space

#endif      // _CS_SOC_600_CTI_16BIT_H_

