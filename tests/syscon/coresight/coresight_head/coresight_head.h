/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
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
*********************************************************************************************/
/**************************************************************************************
 * @file  coresight_head.h
****************************************************************************************/

#ifndef CORESIGHT_HEAD_H
#define CORESIGHT_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "all_comps.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define RPC_LX7_0_ETMB_BASE         0xac10000
#define RPC_LX7_1_ETMB_BASE         0xac20000
#define RPC_LX7_2_ETMB_BASE         0xac30000
#define RPC_KP1_ETMB_BASE           0xac40000

// CS SOC funnel address
#define CS_SOC_4TO1_FUNNEL_ADDR     0x10000

// TSGEN Base address
#define TSGEN_ADDR                  0x40000

//ETMB MACROS
#define ETMB_TRCSTATR_OFFSET        0xc
#define ETMB_TRCCONFIGR_OFFSET      0x10
#define ETMB_TRCSYNCPR_OFFSET       0x34
#define ETMB_TRCCCCTLR_OFFSET       0x38
#define ETMB_TRCTRACEIDR_OFFSET     0x40
#define ETMB_TRCVICTLR_OFFSET       0x80
#define ETMB_TRCPRGCTLR_OFFSET      0x4
#define ETMB_TRCEXTINSELR_OFFSET    0x120
#define ETMB_DBGCMDR_OFFSET         0x1000
#define ETMB_DBGBPIACSELR_OFFSET    0x1004
#define ETMB_DBGCTRLSTATR_OFFSET    0x102c
#define ETMB_DBGPROCSTATR_OFFSET    0x1024
#define ETMB_DBGPROCPCR_OFFSET      0x1028
#define ETMB_IACVALR0_OFFSET        0x1080
#define ETMB_IACVALR1_OFFSET        0x1084
#define ETMB_IACVALR2_OFFSET        0x1088
#define ETMB_IACVALR3_OFFSET        0x108c
#define ETMB_IACVALR4_OFFSET        0x1090
#define ETMB_IACVALR5_OFFSET        0x1094
#define ETMB_IACVALR6_OFFSET        0x1098
#define ETMB_IACVALR7_OFFSET        0x109c
#define ETMB_TRCSYNCPR_REQ          0x10

// ETF Macros
#define ETF_BASE_ADDR               0x20000
#define ETF_CTL_OFFSET              0x20
#define ETF_RSZ_OFFSET              0x4
#define ETF_STS_OFFSET              0xc
#define ETF_MODE_OFFSET             0x28
#define ETF_RWP_OFFSET              0x18
#define ETF_RRD_OFFSET              0x10
#define ETF_RRP_OFFSET              0x14
#define ETF_RWD_OFFSET              0x24
#define ETF_FFCR_OFFSET             0x304
#define ETF_PSCR_OFFSET             0x308
#define ETF_FFSR_OFFSET             0x300
#define ETF_TRG_OFFSET              0x1c
#define ETF_BUFWM_OFFSET            0x34
#define ETF_CBUFLEVEL_OFFSET        0x30
#define ETF_FULL                    0x1
#define ETF_EMPTY                   0x10
#define FLUSH_IN_PROGRESS           0x1
#define ETF_ENABLE                  0x1
#define ETF_DISABLE                 0x0
#define ETF_CB_BUFFER               0x00
#define ETF_SWF_BUFFER              0x01
#define ETF_HWF_BUFFER              0x02
#define STS_BIT_TMCReady            0x2
#define TIME_INTERVAL               10
#define ETF_ENFT_ENTI               0x1003
#define ETF_TRG_EN                  0x80
#define ETF_FLUSH_EN                0x1043
#define ETF_DRAIN                   0xd403
#define ETF_RRP_START               0x0
#define ETF_RWP_START               0x0
#define ETF_WATERMARK_LVL           0x20
#define ETF_PSCR_CNT                0xf

// ETR Macros
#define ETR_BASE_ADDR               0x30000
#define ETR_CTL_OFFSET              0x20
#define ETR_RSZ_OFFSET              0x4
#define ETR_STS_OFFSET              0xc
#define ETR_MODE_OFFSET             0x28
#define ETR_RWP_OFFSET              0x18
#define ETR_RWPHI_OFFSET            0x3c
#define ETR_RRD_OFFSET              0x10
#define ETR_RRP_OFFSET              0x14
#define ETR_RRPHI_OFFSET            0x38
#define ETR_RWD_OFFSET              0x24
#define ETR_FFCR_OFFSET             0x304
#define ETR_FFSR_OFFSET             0x300
#define ETR_TRG_OFFSET              0x1c
#define ETR_BUFWM_OFFSET            0x34
#define ETR_DBALO_OFFSET            0x118
#define ETR_DBAHI_OFFSET            0x11c
#define ETR_CBUFLEVEL_OFFSET        0x30
#define ETR_PSCR_OFFSET             0x308
#define ETR_FULL                    0x1
#define ETR_EMPTY                   0x10
#define ETR_ENABLE                  0x1
#define ETR_DISABLE                 0x0
#define ETR_RSZ                     0x2000    // ETR RAM Size
#define ETR_TRG_EN                  0x80
#define ETR_AXI_CTL_OFFSET          0x110
#define ETR_WATERMARK_LVL           0x20
#define ETR_AXI_SECURE_EN           0x10a07
#define ETR_FORMATTER_EN            0x1003
#define ETR_MANUAL_FLUSH            0x1043
#define FLUSH_IN_PROGRESS           0x1
#define ETR_CB_BUFFER               0x00
#define ETR_SWF1_BUFFER             0x01
#define ETR_SWF2_BUFFER             0x03
#define ETR_PSCR_CNT                0x20
#define SYS_MEM_ADDR                0x800000  // Address of the memory in which trace data should be written

// DEBUG AND TRACE CONTROLLER ACCESS MACROS
#define DTC_COMMAND_NOP             0
#define DTC_COMMAND_ON              1
#define DTC_COMMAND_OFF             2
#define DTC_COMMAND_STOP            3
#define DTC_COMMAND_CONTINUE        4
#define DTC_COMMAND_STEP            5

// DTC STATUS MACROS
#define DTC_STATE_OFF               0
#define DTC_STATE_IDLE              1
#define DTC_STATE_STOPPED           2
#define DTC_STATE_RUN_UNTIL_STOP    3
#define DTC_STATE_RUN_ONE_STEP      4

// PROCESSOR STATUS MACROS
#define PROC_STATE_IDLING           0x01
#define PROC_STATE_STARTING         0x02
#define PROC_STATE_EXECUTING        0x04
#define PROC_STATE_STALLING         0x08
#define PROC_STATE_SLEEPING         0x10
#define PROC_STATE_BREAKING         0x20

// Structure for CS SOC funnel priority control register
typedef union {
  struct {
    uint32_t PRIPORT0 : 3;
    ///< Priority value for port 0. Field is RES0 if port 0 is not implemented.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t PRIPORT1 : 3;
    ///< Priority value for port 1. Field is RES0 if port 1 is not implemented.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"
    uint32_t PRIPORT2 : 3;
    ///< Priority value for port 2. Field is RES0 if port 2 is not implemented.
    ///< AccessType="RW" BitOffset="6" ResetValue="0x0"
    uint32_t PRIPORT3 : 3;
    ///< Priority value for port 3. Field is RES0 if port 3 is not implemented.
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t PRIPORT4 : 3;
    ///< Priority value for port 4. Field is RES0 if port 4 is not implemented.
    ///< AccessType="RO" BitOffset="12" ResetValue="0x0"
    uint32_t PRIPORT5 : 3;
    ///< Priority value for port 5. Field is RES0 if port 5 is not implemented.
    ///< AccessType="RO" BitOffset="15" ResetValue="0x0"
    uint32_t PRIPORT6 : 3;
    ///< Priority value for port 6. Field is RES0 if port 6 is not implemented.
    ///< AccessType="RO" BitOffset="18" ResetValue="0x0"
    uint32_t PRIPORT7 : 3;
    ///< Priority value for port 7. Field is RES0 if port 7 is not implemented.
    ///< AccessType="RO" BitOffset="21" ResetValue="0x0"
    uint32_t RES0_0 : 8;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="24" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_css600_atbfunnel_4to1_64bit_addrblk_0_priorityctrl_reg_t;

// Structure for CS_SOC funnel control register
typedef union {
  struct {
    uint32_t ENS0 : 1;
    ///< Enable slave interface 0. Field is RES0 if slave interface 0 is not
    ///< implemented.
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t ENS1 : 1;
    ///< Enable slave interface 1. Field is RES0 if slave interface 1 is not
    ///< implemented.
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t ENS2 : 1;
    ///< Enable slave interface 2. Field is RES0 if slave interface 2 is not
    ///< implemented.
    ///< AccessType="RW" BitOffset="2" ResetValue="0x0"
    uint32_t ENS3 : 1;
    ///< Enable slave interface 3. Field is RES0 if slave interface 3 is not
    ///< implemented.
    ///< AccessType="RW" BitOffset="3" ResetValue="0x0"
    uint32_t ENS4 : 1;
    ///< Enable slave interface 4. Field is RES0 if slave interface 4 is not
    ///< implemented.
    ///< AccessType="RO" BitOffset="4" ResetValue="0x0"
    uint32_t ENS5 : 1;
    ///< Enable slave interface 5. Field is RES0 if slave interface 5 is not
    ///< implemented.
    ///< AccessType="RO" BitOffset="5" ResetValue="0x0"
    uint32_t ENS6 : 1;
    ///< Enable slave interface 6. Field is RES0 if slave interface 6 is not
    ///< implemented.
    ///< AccessType="RO" BitOffset="6" ResetValue="0x0"
    uint32_t ENS7 : 1;
    ///< Enable slave interface 7. Field is RES0 if slave interface 7 is not
    ///< implemented.
    ///< AccessType="RO" BitOffset="7" ResetValue="0x0"
    uint32_t HT : 4;
    ///< Hold time. Value sets the minimum hold time before switching trace
    ///< sources (funnel inputs) based on the ID. Value used is programmed
    ///< value + 1.
    ///< AccessType="RW" BitOffset="8" ResetValue="0x3"
    uint32_t FLUSH_NORMAL : 1;
    ///< This bit, when clear, allows slave ports that are already flushed
    ///< to receive further data even if there are other ports that have not
    ///< completed flush. If set, a port that has completed flush is not be
    ///< allowed to receive further data until all ports have completed flush.
    ///< AccessType="RW" BitOffset="12" ResetValue="0x0"
    uint32_t RES0_0 : 19;
    ///< Reserved bit or field with SBZP behavior
    ///< AccessType="RW" BitOffset="13" ResetValue="0x0"
  } ;
  uint32_t value;
} cs_soc_css600_atbfunnel_4to1_64bit_addrblk_0_funnelctrl_reg_t;

typedef struct
{
    int core_num; uint32_t core_address;
}core_num_address_t;

// Declaration of vex array
extern core_num_address_t vex_address_map[40];

// Declaration of rcs array
extern core_num_address_t rcs_address_map[4];

uint32_t get_etmb_core_address(int core_num, char core_name[]);

//========================================= ETM ===============================================================//

typedef enum{
    DISABLE,
    ENABLE
}etm_disable_enable_t;

void etm_switch(int core_num, char core_name[], etm_disable_enable_t ctrl);
void etm_config(int core_num, char core_name[], uint32_t trace_id);
uint32_t etm_status(int core_num, char core_name[]);

//======================================== ATBFUNNEL =========================================================//

typedef struct {
    uint32_t funnel_2to1_addr_1;
    uint32_t funnel_4to1_addr;
    uint32_t funnel_2to1_addr_2;
} funnelblock_t;

typedef struct{
    uint32_t core_addr[4];      // Array to hold addresses of cores
}coreblock;

typedef struct{
    int port;                   // port number of the funnel
    int row;                    // row index in the core grid
    int column;                 // coloumn index of the core grid
    funnelblock_t funnel_addr;  // Base address of the funnel
}funnelconfig_t;

void set_funnel_enable(uint32_t funnel_addr, int enable_port);
funnelconfig_t get_funnel_port_and_base_by_core(uint32_t core_addr);
void configure_2to1_funnel_by_core(int core_num, char core_name[]);
void configure_4to1_funnel_by_core(int core_num, char core_name[]);
void configure_4to1_funnel_by_cs_core(int core_num, char core_name[]);
void atbfunnel_main(int core_num, char core_name[]);

//========================================== ETF ===============================================================//

typedef enum
{
    ETF_CB_MODE,                // Circular Buffer mode
    SWF_MODE,                   // Software FIFO mode
    HWF_MODE                    // Hardware FIFO mode
}etf_mode_t;

typedef enum{
    ETF_DIS,
    ETF_EN,
}etf_switch_t;

uint32_t etf_status();
void etf_ready();
void etf_switch(etf_switch_t ctrl);
void etf_manual_flush();
uint32_t get_etf_ram_size();
void configure_etf(etf_mode_t etf_mode);
uint32_t etf_mem_read(etf_switch_t etf_mem_en);
void drain_etf(etf_mode_t mode);

//========================================== ETR ===============================================================//

typedef enum
{
    ETR_CB_MODE,                // Circular Buffer mode
    SWF_MODE_1,                 // Software FIFO mode 1
    SWF_MODE_2                  // Software FIFO mode 2
}etr_mode_t;

typedef enum{
    ETR_DIS,
    ETR_EN,
}etr_switch_t;

uint32_t etr_status();
uint32_t get_etr_buffer_level();
void etr_ready();
void etr_switch(etr_switch_t ctrl);
void etr_manual_flush(etr_switch_t flush_ctrl);
uint32_t get_etr_ram_size();
void configure_etr(etr_mode_t etf_mode);
uint32_t etr_mem_read(etr_switch_t mem_en);

//======================================= CORESIGHT MAIN ==========================================================//

typedef enum{
    ON,
    OFF,
    STOP,
    CONTINUE,
    STEP
}dtc_switch_t;

void verbose_switch(char verb_switch[]);
void pre_coresight_config();
void post_coresight_config(int core_num, char core_name[], etr_switch_t flush_ctrl);
void rsm_mem_read(uint32_t etr_size, uint32_t trace_id);
void mem_cap_mem_read(uint32_t etr_size);
void dtc_switch(uint32_t etmb_base_address, dtc_switch_t debug_ctrl);
uint32_t get_debug_status(uint32_t etmb_base_address);
uint32_t get_processor_status(uint32_t etmb_base_address);
uint32_t get_proc_pc(uint32_t etmb_base_address);
int dtc_run_until_stopped(uint32_t etmb_base_address);
int dtc_wait_until_stopped(uint32_t etmb_base_address);
void pre_proc_run(int core_num, char core_name[]);
void post_proc_run(int core_num, char core_name[]);

#endif
