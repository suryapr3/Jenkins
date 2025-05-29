# INTEL CONFIDENTIAL
#
# Copyright 2022 Intel Corporation All Rights Reserved.
#
# The source code contained or described herein and all documents related
# to the source code ("Material") are owned by Intel Corporation or its
# suppliers or licensors. Title to the Material remains with Intel
# Corporation or its suppliers and licensors. The Material contains trade
# secrets and proprietary and confidential information of Intel or its
# suppliers and licensors. The Material is protected by worldwide copyright
# and trade secret laws and treaty provisions. No part of the Material
# may be used, copied, reproduced, modified, published, uploaded, posted,
# transmitted, distributed, or disclosed in any way without Intel's prior
# express written permission.
#
# No license under any patent, copyright, trade secret or other
# intellectual property right is granted to or conferred upon you by
# disclosure or delivery of the Materials, either expressly, by
# implication, inducement, estoppel or otherwise. Any license under such
# intellectual property rights must be express and approved by Intel in
# writing.

from pathlib import Path # for file name/path

from .util import p_green2
from .build_headers import build_copyright_info, build_includ_head_info, build_includ_tail_info

def build_table_access(out_f):
    """Define a set of table access macros

    Parameters
    ----------
    out_f : str
        output file name

    Returns
    ----------
    None
    """
    # define some table access macros:
    out_f.write("#ifdef RCS\n")
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'get_tl', 'get_tl(table, idx)','((p_##table->table)[(idx)])'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'get_tl2d', 'get_tl2d(table, subtable_idx, idx)', '((p_##table->table)[(subtable_idx)][(idx)])'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'get_tf', 'get_tf(table, idx, field)', '((p_##table->table)[(idx)].field)'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'get_tf2d', 'get_tf2d(table, subtable_idx, idx, field)', '((p_##table->table)[(subtable_idx)][(idx)].field)'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'set_tl', 'set_tl(table, idx, val)', '((p_##table->table)[(idx)] = (val))'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'set_tl2d', 'set_tl2d(table, subtable_idx, idx, val)', '((p_##table->table)[(subtable_idx)][(idx)] = (val))'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}".format('#ifndef', '#define', '#endif', \
            'set_tf', 'set_tf(table, idx, field, val)', '((p_##table->table)[(idx)].field = (val))'))
    out_f.write("\n{0} {3}\n{1} {4} {5}\n{2}\n".format('#ifndef', '#define', '#endif', \
            'set_tf2d', 'set_tf2d(table, subtable_idx, idx, field, val)', '((p_##table->table)[(subtable_idx)][(idx)].field = (val))'))
    out_f.write("""
#else

#include "com_device_api.h"
#include "com_cpu_id.h"

// Tables addressed relative to start of DRAM.
#define COM_STATIC_DATA_START_ADDRESS 0

#include "com_static_data_table.h"
#define  AX_STATIC_DATA_START_ADDRESS (COM_STATIC_DATA_START_ADDRESS + sizeof(com_static_data_t))
#define  RX_STATIC_DATA_START_ADDRESS (COM_STATIC_DATA_START_ADDRESS + sizeof(com_static_data_t))
#define  TX_STATIC_DATA_START_ADDRESS (COM_STATIC_DATA_START_ADDRESS + sizeof(com_static_data_t))
#define  RF_CALIB_STATIC_DATA_START_ADDRESS (COM_STATIC_DATA_START_ADDRESS + sizeof(com_static_data_t))

#include "ax_static_data_table.h"
#include "rx_static_data_table.h"
#include "tx_static_data_table.h"
#include "rf_calib_static_data_table.h"

#define table_p_ax(p) ((void *)(RCS_CPU0_DRAM_AXI_ADDRESS+((long long)(p))))
#define table_p_rx(p) ((void *)(RCS_CPU1_DRAM_AXI_ADDRESS+((long long)(p))))
#define table_p_tx(p) ((void *)(RCS_CPU2_DRAM_AXI_ADDRESS+((long long)(p))))
#define table_p_cal(p) ((void *)(RCS_CPU3_DRAM_AXI_ADDRESS+((long long)(p))))

#define get_tl_ax(dev, table, idx)   get_tl(ax,dev,table, idx)
#define get_tl_rx(dev, table, idx)   get_tl(rx,dev,table, idx)
#define get_tl_tx(dev, table, idx)   get_tl(tx,dev,table, idx)
#define get_tl_cal(dev, table, idx)  get_tl(cal,dev,table, idx)

#define set_tl_ax(dev, table, idx, val)   set_tl(ax,dev,table, idx, val)
#define set_tl_rx(dev, table, idx, val)   set_tl(rx,dev,table, idx, val)
#define set_tl_tx(dev, table, idx, val)   set_tl(tx,dev,table, idx, val)
#define set_tl_cal(dev, table, idx, val)  set_tl(cal,dev,table, idx, val)

#define get_tf_ax(dev, table, idx, field)   get_tf(ax,dev,table, idx, field)
#define get_tf_rx(dev, table, idx, field)   get_tf(rx,dev,table, idx, field)
#define get_tf_tx(dev, table, idx, field)   get_tf(tx,dev,table, idx, field)
#define get_tf_cal(dev, table, idx,field)   get_tf(cal,dev,table, idx, field)

#define set_tf_ax(dev, table, idx, field, val)   set_tf(ax,dev,table, idx, field, val)
#define set_tf_rx(dev, table, idx, field, val)   set_tf(rx,dev,table, idx, field, val)
#define set_tf_tx(dev, table, idx, field, val)   set_tf(tx,dev,table, idx, field, val)
#define set_tf_cal(dev, table, idx,field, val)   set_tf(cal,dev,table, idx, field, val)

#define get_tl(cpu, dev, table, idx) ({table##_bf_t _row; dev_mem_read (dev, (void*)(&_row),table_p_##cpu(&(p_##table->table)[(idx)]), sizeof(_row)); _row;})
#define set_tl(cpu, dev, table, idx, value) ({table##_bf_t _row=value; dev_mem_write (dev,table_p_##cpu(&(p_##table->table)[(idx)]),(void*)(&_row), sizeof(_row));})
#define get_tl2d(cpu, dev, table, subtable_idx, idx) ({table##_bf_t _row; dev_mem_read (dev, (void*)(&_row),table_p_##cpu(&(p_##table->table)[(subtable_idx)][(idx)]), sizeof(_row)); _row;})
#define set_tl2d(cpu, dev, table, subtable_idx, idx, val) ({table##_bf_t _row=value; dev_mem_write (dev, table_p_##cpu(&(p_##table->table)[(subtable_idx)][(idx)]),(void*)(&_row), sizeof(_row));})

#define get_tf(cpu, dev, table, idx, field)        ({table##_bf_t __row = get_tl_##cpu(dev, table,idx);  __row.field;})
#define set_tf(cpu, dev, table, idx, field, value) ({table##_bf_t __row = get_tl_##cpu(dev, table,idx);  __row.field = value; set_tl_##cpu(dev,table,idx,__row);})
#define get_tf2d(cpu, dev, table, subtable_idx, idx, field)        ({table##_bf_t __row = get_tl2d_##cpu(dev, table,subtable_idx,idx);  __row.field;})
#define set_tf2d(cpu, dev, table, subtable_idx, idx, field, value) ({table##_bf_t __row = get_tl2d_##cpu(dev, table,subtable_idx, idx);  __row.field = value; set_tl2d_##cpu(dev,table,subtable_idx,idx,__row);})

#endif
""")

def build_access_macros_output(out_fn, dest_dir):
    path = Path(dest_dir)
    path.mkdir(parents=True, exist_ok=True)
    with open(dest_dir + '/' + out_fn, "w") as of:
        build_copyright_info(of)
        build_includ_head_info(of, out_fn, '')
        build_table_access(of)
        build_includ_tail_info(of, out_fn, '')
        p_green2("Generated header file", dest_dir + '/' + out_fn)

