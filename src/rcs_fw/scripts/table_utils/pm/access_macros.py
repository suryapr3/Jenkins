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

def build_access_macros_output(out_fn, dest_dir):
    path = Path(dest_dir)
    path.mkdir(parents=True, exist_ok=True)
    with open(dest_dir + '/' + out_fn, "w") as of:
        build_copyright_info(of)
        build_includ_head_info(of, out_fn, '')
        build_table_access(of)
        build_includ_tail_info(of, out_fn, '')
        p_green2("Generated header file", dest_dir + '/' + out_fn)

