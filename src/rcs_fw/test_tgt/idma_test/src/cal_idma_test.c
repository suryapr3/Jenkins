/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
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
 *
 *********************************************************************************************/

/**
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */


#include "com_event.h"
#include "rcs_gpreg.h"
#include "com_idma.h"
#include "com_idma_reg.h"
#include "tx_tests.h"
#include "com_definitions.h"

#define IDMA_TEST_BUFF_SIZE 0x200
#define FWT_IDMA_MAX_NUM_DESC 256


volatile idma_desc2d_t g_idma_desc2d_test[FWT_IDMA_MAX_NUM_DESC] __attribute__ ((__aligned__ (8))) __attribute__ ((section (".dram0.data")));
volatile idma_desc1d_t g_idma_desc1d_test[FWT_IDMA_MAX_NUM_DESC] __attribute__ ((__aligned__ (8))) __attribute__ ((section (".dram0.data")));
volatile uint32_t  buff_rsm[IDMA_TEST_BUFF_SIZE] __attribute__ ((section (".sram.cal.rw")));
volatile uint32_t  buff_src[IDMA_TEST_BUFF_SIZE] __attribute__((section(".dram0.data")));
volatile uint32_t  buff_dst[IDMA_TEST_BUFF_SIZE] = {0x00};
volatile uint32_t  buff_b[IDMA_TEST_BUFF_SIZE * 4] = {0x00}; // 8 rows
volatile uint32_t  buff_r[IDMA_TEST_BUFF_SIZE*8] __attribute__ ((section (".sram.cal.rw")));

volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


volatile uint32_t num_bytes_val=0,ctrl_reg[],block_size=0;
uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;

unsigned int g_test_val = 0;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/

void idma_test_desc_1d_dcode_to_dcode(uint32_t num_bytes,uint32_t blk_size);
uint32_t idma_reg_read (void const *const p_addr);


uint32_t idma_reg_read (void const *const p_addr)
{
    uint32_t val = 0;
    __asm__ volatile("rer %0, %1" : "=a"(val) : "a"((uint32_t)p_addr));
    return val;
}

void com_idma_status_check_1()
{
    volatile idma_stat_reg_t idma_stat = {.value = IDMA_STATUS_REG_RESET_VALUE};

    do {
	ctrl_reg[1]=idma_reg_read (IDMA_STATUS_REG);
	idma_stat.value = idma_reg_read (IDMA_STATUS_REG);
    } while (idma_stat.RUN_MODE != 0);
}

void com_idma_poll_done ()
{
    volatile idma_ctrl_reg_t idma_ctrl = {.value = 0};

    do {
	ctrl_reg[0]=idma_reg_read (IDMA_CTRL_REG);
	idma_ctrl.value = idma_reg_read (IDMA_CTRL_REG);
    } while (idma_ctrl.ENABLE_IDMA);
}
int main(int argc, char **argv)
{
    xthal_enable_interrupts();
    do
    {	
	if(rsm_cal_shared_flag==0x1234)
	    break;
	com_timing_wait_ns(10000);   

    }while(rsm_cal_shared_flag!=0x1234);
    idma_tests();
    return (0);
}



void idma_test_1d_poll_dcode_to_dcode ()
{

    rsm_rx_shared_flag=0;
    rsm_com_shared_flag=0;
    memset (buff_dst,0, IDMA_TEST_BUFF_SIZE);
    for (dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE/4; dataCnt++)
    {
	buff_src[dataCnt] = 0x88885555;
    }
    com_idma_trans_1d (buff_dst, buff_src,IDMA_TEST_BUFF_SIZE, NULL);

    com_idma_poll_done();
    //com_idma_status_check_1();
    //set rsm flag
    //rsm_cal_shared_flag=0xABCD;
}

void idma_test_1d_poll_dcode_to_rsm ()
{

    rsm_com_shared_flag=0;
    do
    {   
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    memset (buff_rsm,0, IDMA_TEST_BUFF_SIZE);
    for (dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE/4; dataCnt++)
    {
	buff_src[dataCnt] = 0x85858585;
    }
    com_idma_trans_1d (buff_rsm, buff_src, IDMA_TEST_BUFF_SIZE, NULL);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;
}
void idma_test_1d_poll_rsm_to_dcode ()
{

    rsm_com_shared_flag=0;
    do
    { 
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    memset (buff_dst,0, IDMA_TEST_BUFF_SIZE);
    for (dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE/4; dataCnt++)
    {
	buff_rsm[dataCnt] = 0xA5A5A5A5;
    }
    com_idma_trans_1d (buff_dst, buff_rsm, IDMA_TEST_BUFF_SIZE, NULL);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;
}


void idma_test_desc_1d_dcode_to_rsm(uint32_t num_bytes,uint32_t blk_size)
{

    uint32_t test_var = 0x456;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0x0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    idma_desc1d_t *p_desc_1d = (idma_desc1d_t *)&g_idma_desc1d_test;
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_src[dataCnt]=0x58585858;
    }	
    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc1d_test[i].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc1d_test[i].dst = (uint32_t)& (buff_rsm[xferd_bytes]);
	g_idma_desc1d_test[i].row_bytes = blk_size;
	xferd_bytes = xferd_bytes + blk_size;
    }
#if 0
    uint32_t rem_bytes = num_bytes - xferd_bytes;
    if (rem_bytes > 0)
    {
	g_idma_desc1d_test[num_blks].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc1d_test[num_blks].dst = (uint32_t)& (buff_rsm[xferd_bytes]);
	g_idma_desc1d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif 
    com_idma_fill_ctrl (g_idma_desc1d_test, num_blks, e_IDMA_DESC_TYPE_1D, NULL);
    com_idma_trans_desc (g_idma_desc1d_test, num_blks, &task_test);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;


}
void idma_test_desc_1d_dcode_to_dcode(uint32_t num_bytes,uint32_t blk_size )
{

    uint32_t test_var = 0x456;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0x0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    idma_desc1d_t *p_desc_1d = (idma_desc1d_t *)&g_idma_desc1d_test;
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    memset (buff_dst, 0, IDMA_TEST_BUFF_SIZE);
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_src[dataCnt]=0x85858585;
    }	
    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc1d_test[i].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc1d_test[i].dst = (uint32_t)& (buff_dst[xferd_bytes]);
	g_idma_desc1d_test[i].row_bytes = blk_size;
	xferd_bytes = xferd_bytes + blk_size;
    }
#if 0
    uint32_t rem_bytes = num_bytes - xferd_bytes;
    if (rem_bytes > 0)
    {
	g_idma_desc1d_test[num_blks].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc1d_test[num_blks].dst = (uint32_t)& (buff_dst[xferd_bytes]);
	g_idma_desc1d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif 
    com_idma_fill_ctrl (g_idma_desc1d_test, num_blks, e_IDMA_DESC_TYPE_1D, NULL);
    com_idma_trans_desc (g_idma_desc1d_test, num_blks, &task_test);
    com_idma_poll_done ();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;


}
void idma_test_desc_1d_rsm_to_dcode(uint32_t num_bytes,uint32_t blk_size)
{

    uint32_t test_var = 0x456;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0x0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    idma_desc1d_t *p_desc_1d = (idma_desc1d_t *)&g_idma_desc1d_test;
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    memset (buff_dst, 0, IDMA_TEST_BUFF_SIZE);
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_rsm[dataCnt]=0xA5A5A5A5;
    }	
    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc1d_test[i].src = (uint32_t)&(buff_rsm[xferd_bytes]);
	g_idma_desc1d_test[i].dst = (uint32_t)& (buff_dst[xferd_bytes]);
	g_idma_desc1d_test[i].row_bytes = blk_size;

	xferd_bytes = xferd_bytes + blk_size;
    }
#if 0
    uint32_t rem_bytes = num_bytes - xferd_bytes;
    if (rem_bytes > 0)
    {
	g_idma_desc1d_test[num_blks].src = (uint32_t)&(buff_rsm[xferd_bytes]);
	g_idma_desc1d_test[num_blks].dst = (uint32_t)& (buff_dst[xferd_bytes]);
	g_idma_desc1d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif 
    com_idma_fill_ctrl (g_idma_desc1d_test, num_blks, e_IDMA_DESC_TYPE_1D, NULL);
    com_idma_trans_desc (g_idma_desc1d_test, num_blks, &task_test);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;


}
void idma_test_desc_2d_dcode_to_rsm(uint32_t num_bytes,uint32_t blk_size)
{

    uint32_t test_var = 0x456;
    uint32_t dst_pitch=4,src_pitch=0;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_src[dataCnt]=0x5C5C5C5C;
    }

    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc2d_test[i].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc2d_test[i].dst = (uint32_t)& (buff_r[xferd_bytes]);
	g_idma_desc2d_test[i].row_bytes = blk_size;
	g_idma_desc2d_test[i].rows = 8;
	g_idma_desc2d_test[i].src_pitch = src_pitch;
	g_idma_desc2d_test[i].dst_pitch = dst_pitch;
	xferd_bytes = xferd_bytes + blk_size;

    }
    uint32_t rem_bytes = num_bytes - xferd_bytes;
#if 0
    if (rem_bytes > 0)
    {
	g_idma_desc2d_test[num_blks].src = (uint32_t)&(buff_rsm[xferd_bytes]);
	g_idma_desc2d_test[num_blks].dst = (uint32_t)& (buff_b[xferd_bytes]);
	g_idma_desc2d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif
    com_idma_fill_ctrl (g_idma_desc2d_test, num_blks, e_IDMA_DESC_TYPE_2D, NULL);
    com_idma_trans_desc (g_idma_desc2d_test, num_blks, &task_test);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;
}


void idma_test_desc_2d_dcode_to_dcode(uint32_t num_bytes,uint32_t blk_size)
{

    uint32_t test_var = 0x456;
    uint32_t dst_pitch=4,src_pitch=0;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0x0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_src[dataCnt]=0x5D5D5D5D;
    }	
    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc2d_test[i].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc2d_test[i].dst = (uint32_t)& (buff_b[xferd_bytes]);
	g_idma_desc2d_test[i].row_bytes = blk_size;
	g_idma_desc2d_test[i].rows = 8;
	g_idma_desc2d_test[i].src_pitch = src_pitch;
	g_idma_desc2d_test[i].dst_pitch = dst_pitch;
	xferd_bytes = xferd_bytes + blk_size;

    }
    uint32_t rem_bytes = num_bytes - xferd_bytes;
#if 0
    if (rem_bytes > 0)
    {
	g_idma_desc2d_test[num_blks].src = (uint32_t)&(buff_src[xferd_bytes]);
	g_idma_desc2d_test[num_blks].dst = (uint32_t)& (buff_b[xferd_bytes]);
	g_idma_desc2d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif
    com_idma_fill_ctrl (g_idma_desc2d_test, num_blks, e_IDMA_DESC_TYPE_2D, NULL);
    com_idma_trans_desc (g_idma_desc2d_test, num_blks, &task_test);
    com_idma_poll_done ();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;
}
void idma_test_desc_2d_rsm_to_dcode(uint32_t num_bytes,uint32_t blk_size)
{

    uint32_t test_var = 0x456;
    uint32_t dst_pitch=4,src_pitch=0;
    uint32_t xferd_bytes =0;
    rsm_rx_shared_flag=0;
    idma_task_info_t task_test = {.pfunc_idma_callback = idma_cb_test, .p_arg = &test_var};
    g_test_val = 0;
    uint32_t num_blks;
    num_blks=num_bytes/blk_size; 
    if(num_blks>254)
	num_blks=254;
    if(num_blks<1)
	num_blks=1;
    for (int dataCnt = 0; dataCnt < IDMA_TEST_BUFF_SIZE; dataCnt++)
    {
	buff_rsm[dataCnt]=0xB5B5B5B5;
    }

    for (int i = 0; i < num_blks; i++)
    {
	g_idma_desc2d_test[i].src = (uint32_t)&(buff_rsm[xferd_bytes]);
	g_idma_desc2d_test[i].dst = (uint32_t)& (buff_b[xferd_bytes]);
	g_idma_desc2d_test[i].row_bytes = blk_size;
	g_idma_desc2d_test[i].rows = 8;
	g_idma_desc2d_test[i].src_pitch = src_pitch;
	g_idma_desc2d_test[i].dst_pitch = dst_pitch;
	xferd_bytes = xferd_bytes + blk_size;

    }
    uint32_t rem_bytes = num_bytes - xferd_bytes;
#if 0
    if (rem_bytes > 0)
    {
	g_idma_desc2d_test[num_blks].src = (uint32_t)&(buff_rsm[xferd_bytes]);
	g_idma_desc2d_test[num_blks].dst = (uint32_t)& (buff_b[xferd_bytes]);
	g_idma_desc2d_test[num_blks].row_bytes = rem_bytes;
	/* one extra blok to xfer */
	num_blks++;
    }
#endif
    com_idma_fill_ctrl (g_idma_desc2d_test, num_blks, e_IDMA_DESC_TYPE_2D, NULL);
    com_idma_trans_desc (g_idma_desc2d_test, num_blks, &task_test);
    com_idma_poll_done();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;
}

void idma_test_broadcast ()
{

    rsm_com_shared_flag=0;
    /*do
      { 
      if(rsm_com_shared_flag==0x8877)
      break;
      }while(rsm_com_shared_flag!=0x8877);*/
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    memset (buff_b, 0, IDMA_TEST_BUFF_SIZE);
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_src[idx] = idx;
    com_idma_broadcast (buff_b,buff_src,IDMA_TEST_BUFF_SIZE,4,0,IDMA_TEST_BUFF_SIZE, NULL); 
    com_idma_poll_done ();
    //set rsm flag
    rsm_cal_shared_flag=0xABCD;

}

void idma_test_broadcast_src_pitch ()
{

    rsm_com_shared_flag=0;
    do
    { 
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    memset (buff_b, 0, IDMA_TEST_BUFF_SIZE);
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_src[idx] = idx;
    com_idma_broadcast (buff_b,buff_src,IDMA_TEST_BUFF_SIZE,4,0,0, NULL); 
    com_idma_poll_done ();
    rsm_cal_shared_flag=0xABCD;

}
void idma_test_broadcast_rsm_to_dcode ()
{

    rsm_com_shared_flag=0;
    /*do
      { 
      if(rsm_com_shared_flag==0x8877)
      break;
      }while(rsm_com_shared_flag!=0x8877);*/
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    memset (buff_b, 0, IDMA_TEST_BUFF_SIZE);
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_rsm[idx] = idx;
    com_idma_broadcast (buff_b,buff_rsm,IDMA_TEST_BUFF_SIZE,4,0,0, NULL); 
    com_idma_poll_done ();
    rsm_cal_shared_flag=0xABCD;

}
void idma_test_broadcast_rsm_to_dcode_src_pitch ()
{

    rsm_com_shared_flag=0;
    do
    { 
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    rsm_com_shared_flag=0;
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_rsm[idx] = idx;
    com_idma_broadcast (buff_b,buff_rsm,IDMA_TEST_BUFF_SIZE,4,0,IDMA_TEST_BUFF_SIZE, NULL);  
    com_idma_poll_done ();
    rsm_cal_shared_flag=0xABCD;


}
void idma_test_broadcast_dcode_to_rsm()
{

    rsm_com_shared_flag=0;
    do
    { 
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_src[idx] = idx;
    com_idma_broadcast (buff_r,buff_src,IDMA_TEST_BUFF_SIZE,4,0,IDMA_TEST_BUFF_SIZE, NULL); 
    com_idma_poll_done ();
    rsm_cal_shared_flag=0xABCD;


}
void idma_test_broadcast_dcode_to_rsm_src_pitch()
{

    rsm_com_shared_flag=0;
    do
    { 
	if(rsm_com_shared_flag==0x8877)
	    break;
    }while(rsm_com_shared_flag!=0x8877);
    rsm_com_shared_flag=0;
    uint32_t test_var = 0x456;
    uint32_t dataCnt, errCnt = -1;
    for (int idx = 0; idx < IDMA_TEST_BUFF_SIZE/4; idx++) buff_src[idx] = idx;
    com_idma_broadcast (buff_r,buff_src,IDMA_TEST_BUFF_SIZE,4,0,IDMA_TEST_BUFF_SIZE, NULL);  
    com_idma_poll_done ();
    rsm_cal_shared_flag=0xABCD;

}
void idma_cb_test (void *arg)
{
    g_test_val = *(uint32_t *)arg;
}
uint8_t  idma_tests ()
{

    com_idma_init ();
    for (int i = 0; i <1; i++)
    {
	rsm_com_shared_flag=0;   
	//idma_test_broadcast();	
	//idma_test_broadcast_dcode_to_rsm();
	idma_test_broadcast_rsm_to_dcode();
	while(1);
	idma_test_broadcast_rsm_to_dcode();
	idma_test_broadcast_src_pitch();
	idma_test_broadcast_dcode_to_rsm_src_pitch();
	idma_test_broadcast_rsm_to_dcode_src_pitch();

	do
	{ 
	    if(rsm_com_shared_flag==0x8877)
		break;
	}while(rsm_com_shared_flag!=0x8877);
	rsm_cal_shared_flag=0x0;
	rsm_com_shared_flag=0;
	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {
		block_size=blk_size;
		num_bytes_val=num_bytes;
		idma_test_desc_1d_dcode_to_dcode(num_bytes,blk_size);
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}

	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0;
	rsm_com_shared_flag=0; 

	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {       

		block_size=blk_size;
		num_bytes_val=num_bytes;
		idma_test_desc_1d_dcode_to_rsm(num_bytes,blk_size);	
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}

	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0;
	rsm_com_shared_flag=0;    
#if 1
	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {       

		block_size=blk_size;;
		num_bytes_val=num_bytes;
		idma_test_desc_1d_rsm_to_dcode(num_bytes,blk_size);	
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}
	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0x0;  
	rsm_com_shared_flag=0;  

	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {       

		block_size=blk_size;;
		num_bytes_val=num_bytes;
		idma_test_desc_2d_dcode_to_dcode(num_bytes,blk_size);	
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}

	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0x0;
	rsm_com_shared_flag=0;   
	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {       

		block_size=blk_size;;
		num_bytes_val=num_bytes;
		idma_test_desc_2d_rsm_to_dcode(num_bytes,blk_size);	
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}
	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0x0;
	rsm_com_shared_flag=0;    
	for(uint32_t num_bytes=4;num_bytes<3072;num_bytes*=2)
	{
	    for(uint32_t blk_size=4;blk_size<3072;blk_size*=2)
	    {       

		block_size=blk_size;;
		num_bytes_val=num_bytes;
		idma_test_desc_2d_dcode_to_rsm(num_bytes,blk_size);	
		do
		{	
		    if(num_bytes==2048)
			break;
		    if(rsm_com_shared_flag==0x8877)
			break;
		} while(rsm_com_shared_flag!=0x8877);
		rsm_com_shared_flag=0;
	    }

	}
	while(rsm_cal_shared_flag!=0x8877);
	rsm_cal_shared_flag=0x0;
	rsm_com_shared_flag=0;
#endif
    }

}



