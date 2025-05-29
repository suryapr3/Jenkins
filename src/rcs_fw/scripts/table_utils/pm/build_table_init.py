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

from .util import *

def build_table_init(out_f, tbl_dic, super_table_name, addr_sec, pos_shift):
    """build table initializtion file

    Parameters
    ----------
    out_f : str
        name of the table initializaiton file to generate
    tbl_dic : dict
        a dictionary: tbl_name as key, tup (tbl_des, bf_blks, sub_tbl_dic, tbl_bitwidth_tup, align) as value
        tbl_des: table description
        bf_blks: bit-field block list, each bit-field block is a list of info for a specific bit-field
        sub_tbl_dic: a dictionary with info about a subtable
        tbl_bitwidth_tup: a tup with bitwidth info for each table
        align: specifying the alignment attribute of this table
    super_table_name : str
        table name for the combinded table containing all the tables defined in this .xlsx file
    addr_sec : str
        start address or memory section name to put the combined table
    pos_shift : int
        position shift for output formating

    Returns
    ----------
    None
    """
    out_f.write("{} {}{}".format('#include', '"' + super_table_name, '_table.h"\n'))
    out_f.write("{} {}{}".format('#include', '"' + super_table_name, '_data.h"\n'))
    if addr_sec != '' and not addr_sec.startswith('0x'):
        out_f.write("\n{}\n{}\n{}\n{}\n{}\n".format(
            '#ifdef __XTENSA__',
            '#define DATA_ATTRIB __attribute__ ((section("' + addr_sec + '")))',
            '#else',
            '#define DATA_ATTRIB',
            '#endif'))
        out_f.write("\n{}{}{}{}".format(super_table_name, '_t DATA_ATTRIB ',  super_table_name + '_init', ' = {\n'))
        #out_f.write("\n{}{}{}{}".format(super_table_name, '_t __attribute__ ((section("' + addr_sec + '"))) ',  super_table_name + '_init', ' = {\n'))
    else:
        p_red2("Warning: NO section name specified for ", super_table_name + '_init')
        out_f.write("\n{}{}{}{}".format(super_table_name, '_t ', super_table_name + '_init', ' = {\n'))
    indent_prefix = ' ' * 4
    key_len = len(tbl_dic.keys())
    tbl_sorted_keys = sorted(tbl_dic.keys(), key=lambda x:x.lower())
    for tbl_name in tbl_sorted_keys:
        key_len -= 1
        sub_tbl_entry_num_max = tbl_dic[tbl_name][3][1]
        sub_tbl_num_max = tbl_dic[tbl_name][3][0]
        tail = (',', '')[key_len == 0]
        out_f.write("{5}{0} {1:>{2}} {3}{4}\n".format('.' + tbl_name + '.' + tbl_name, '=',\
            set_pos(tbl_name + tbl_name + indent_prefix, pos_shift), tbl_name.upper() + '_DATA', tail, indent_prefix))
    out_f.write("{}".format('};\n'))

