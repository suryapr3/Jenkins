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
#ifndef COMMON_IDMA_H
#define COMMON_IDMA_H

#include <stdint.h>

#define IDMA_MAX_DESCRIPTOR 256

#define ERR_IDMA_OK                (0x0)
#define ERR_IDMA_PRIV_VIOLATION    (0x1)
#define ERR_IDMA_NULL_ADDR         (0x2)
#define ERR_IDMA_BAD_PARAM         (0x4)
#define ERR_IDMA_UNSUPPORTED_DIR   (0x8)
#define ERR_IDMA_UNKNOWN_CMD       (0x10)
#define ERR_IDMA_NUM_DESC_OVERFLOW (0x20)
#define ERR_IDMA_RIG_OVERFLOW      (0x40)
#define ERR_IDMA_IMEOUT            (0x80)
#define ERR_IDMA_WRITE_DATA        (0x100)
#define ERR_IDMA_WRITE_ADDR        (0x200)
#define ERR_IDMA_READ_DATA         (0x400)
#define ERR_IDMA_READ_ADDR         (0x800)
#define ERR_IDMA_DESC_DATA         (0x1000)
#define ERR_IDMA_DESC_ADDR         (0x2000)
#define ERR_IDMD_MISSING_INTR      (0x11111111)

typedef union {
    struct
    {
        uint32_t DESCRIPTOR : 3; // 3=1D, 7=2D, 0=Addr
#if (HAS_MMU)
        uint32_t : 5;
        uint32_t PRIV_SRC : 2;
        uint32_t PRIV_DST : 2;
#else
        uint32_t : 6;
        uint32_t PRIV_SRC : 1;
        uint32_t : 1;
        uint32_t PRIV_DST : 1;
#endif                    // HAS_MMU
        uint32_t QOS : 4; // 0=Low priority, 8=High priority
        uint32_t : 13;
        uint32_t TWAIT : 1;
        uint32_t TRIGGER : 1;
        uint32_t INTR : 1;
    };
    uint32_t value;
} idma_desc_ctrl_t;

typedef struct
{
    union {
        idma_desc_ctrl_t ctrl;
        uint32_t jump;
    };
    uint32_t src;
    uint32_t dst;
    uint32_t row_bytes;
} idma_desc1d_t;

typedef struct
{
    union {
        idma_desc_ctrl_t ctrl;
        uint32_t jump;
    };
    uint32_t src;
    uint32_t dst;
    uint32_t row_bytes;
    uint32_t src_pitch;
    uint32_t dst_pitch;
    uint32_t rows;
    uint32_t rsvd; // for alignment
} idma_desc2d_t;

typedef struct
{
    uint32_t jump;
} idma_desc_jump_t;

typedef enum
{
    e_IDMA_BLOCK2 = 0,
    e_IDMA_BLOCK4 = 1,
    e_IDMA_BLOCK8 = 2,
    e_IDMA_BLOCK16 = 3,
    e_IDMA_BLOCK_MAX
} e_idma_block_t;

typedef enum
{
    e_IDMA_DESC_TYPE_JUMP = 0,
    e_IDMA_DESC_TYPE_1D = 3,
    e_IDMA_DESC_TYPE_2D = 7,
} e_idma_desc_type_t;

typedef enum
{
    e_IDMA_STAT_IDLE = 0,
    e_IDMA_STAT_STANDBY = 1,
    e_IDMA_STAT_BUSY = 2,
    e_IDMA_STAT_DONE = 3,
    e_IDMA_STAT_HALT = 4,
    e_IDMA_STAT_ERROR = 5,
    e_IDMA_STAT_MAX
} e_idma_stat_t;

typedef enum
{
    e_IDMA_QOS_PRIORITY_LOW = 0,
    e_IDMA_QOS_PRIORITY_HIGH = 8,
} e_idma_qos_t;

typedef struct
{
    e_idma_qos_t qos; // default: low priority
    uint32_t timer;   // not supported, always set to 0
    uint8_t ps;       // default: supervisor or ring 0
    uint8_t pd;       // default: supervisor or ring 0
} idma_desc_ctrl;

typedef void (*idma_task_cb) (void *arg);

typedef struct
{
    idma_task_cb pfunc_idma_callback;
    void *p_arg;
} idma_task_info_t;

/**
 * @brief           Initialize iDMA. Call only once during boot
 * @param [in]      none.
 * @return          none.
 */
void com_idma_init ();

/**
 * @brief           Fill control field in iDMA descriptors.
 * @param [in]      p_desc: Pointer to descriptor buffer.
 * @param [in]      decs_cnt: Number of descriptor
 * @param [in]      desc_type: 1D or 2D descriptor
 * @param [in]      p_ctrl: Unused
 * @return          none.
 */
void com_idma_fill_ctrl (void *p_desc, uint32_t const decs_cnt, e_idma_desc_type_t const desc_type, idma_desc_ctrl const *const p_ctrl);

/**
 * @brief           Get iDMA status, busy, done, error.
 * @param [in]      none.
 * @return          e_idma_stat_t: iDMA status.
 */
e_idma_stat_t com_idma_get_status ();

/**
 * @brief           Get last iDMA error code. Function is read to clear.
 * @param [in]      none.
 * @return          uint32_t: iDMA error code.
 */
uint32_t com_idma_get_last_errcode ();

/**
 * @brief           Wait until iDma transfer completed, when not using interrupt.
 * @param [in]      none.
 * @return          uint32_t: iDMA error code or ERR_IDMA_OK when no error.
 */
uint32_t com_idma_wait_done ();

/**
 * @brief           Legacy DMA transfer, using 1D descriptor
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_1d (void const *const dst, void const *const src, uint32_t const bytes, idma_task_info_t const *const p_task);

/**
 * @brief           IDMA 2D transfer, support call back and non-blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer per row.
 * @param [in]      rows: Number of row to transfer.
 * @param [in]      src_pitch: Source pitch.
 * @param [in]      dst_pitch: Destination pitch.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_2d (void const *const dst, void const *const src, uint32_t const bytes, uint32_t const rows, uint32_t const src_pitch,
                        uint32_t const dst_pitch, idma_task_info_t const *const p_task);

/**
 * @brief           IDMA broadcast, support call back and non-blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer per row.
 * @param [in]      rows: Number of row to transfer.
 * @param [in]      dst_pitch: Destination pitch.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_broadcast (void const *const dst, void const *const src, uint32_t const bytes, uint32_t const rows, uint32_t const dst_pitch,
                         idma_task_info_t const *const p_task);

/**
 * @brief           IDMA transfer using descriptor, support call back and non-blocking.
 * @param [in]      p_desc: Pointer to descriptor buffer. Last descriptor need to set ctrl.INTR=1. The rest are 0.
 * @param [in]      desc_cnt: Number of descriptor.
 * @param [in]      p_task: Task to be execute after DMA complete. Pass in NULL if no callback needed.
 * @return          none.
 */
void com_idma_trans_desc (void const *const p_desc, uint32_t const desc_cnt, idma_task_info_t const *const p_task);

/**
 * @brief           IDMA memcpy, no call back support and is blocking.
 * @param [in]      dst: Destination address.
 * @param [in]      src: Source address.
 * @param [in]      bytes: Bytes to transfer.
 * @return          uint32_t: error status. 0=success, non-zero=fail.
 */
uint32_t com_idma_memcpy (void const *const dst, void const *const src, uint32_t const bytes);

#endif // COMMON_IDMA_H
