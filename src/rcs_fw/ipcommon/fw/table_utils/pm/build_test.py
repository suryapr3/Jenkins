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
from .access_macros import build_table_access
from .util import *

def type_fmt_str(sign_str):
    """util function to return print format for specific type

    only used in test file generation

    Parameters
    ----------
    sign_str: str
        name of the sign type

    Returns
    ----------
    None
    """
    if sign_str == 'unsigned':
        return 'u\\n"'
    elif sign_str == 'float' or sign_str == 'double':
        return 'f\\n"'
    else:
        return 'd\\n"'

def build_table_test(test_file, tbl_dic, super_table_name, table_dim_dic, addr_len_tup, addr_sec, length, ofs, use_xtensa, pos_shift, table_init, tb_access_macros):
    """build test file to sanity check the generated header files

    generate a c test file to check the first and last field values from each table, also check table size is within limits or not

    Parameters
    ----------
    test_file : str
        name of the test file to generate
    tbl_dic : dict
        a dictionary: tbl_name as key, tup (tbl_des, bf_blks, sub_tbl_dic, tbl_bitwidth_tup, align) as value
        tbl_des: table description
        bf_blks: bit-field block list, each bit-field block is a list of info for a specific bit-field
        sub_tbl_dic: a dictionary with info about a subtable
        tbl_bitwidth_tup: a tup with bitwidth info for each table
        align: specifying the alignment attribute of this table
    super_table_name : str
        table name for the combinded table containing all the tables defined in this .xlsx file
    table_dim_dic : dict
        a dimision dictionary: tbl_name as key, tup (sub_tbl_num_max, sub_tbl_entry_num_max) as value
        sub_tbl_num_max: constant, subtable first dimision
        sub_tbl_entry_num_max: constant, subtable second dimision
    addr_len_tup : tup
        a tup of (table_address, table_length_in_bytes)
    addr_sec : str
        start address or memory section name to put the combined table
    length : str
        string contains memory size to hold the combined table
    ofs : str
        string contains the offset to the start address
    use_xtensa : bool
        toolset selection: true to use XTENSA toolset, false to use GCC toolset.
    pos_shift : int
        position shift for output formating
    table_init : str
        table initialization file name
    tb_access_macros : str
        header file name of table access macros definition

    Returns
    ----------
    None
    """
    pre_tab = ' '*4
    Path(test_file).parent.mkdir(parents=True, exist_ok=True)
    with open(test_file, "w") as of:
        of.write("#define RCS 1\n") # test table under RCS
        of.write("#include " + '"' + 'com_rf_def.h' + '"' + "\n")
        of.write("#include <stdio.h>\n")
        if use_xtensa and (addr_sec == '' or addr_sec.startswith('0x')):
            of.write("#include <string.h>\n") # for memcpy
        of.write("{} {}{}".format('#include', '"' + super_table_name.lower(), '_table.h"\n'))
        of.write("{} {}{}".format('#include', '"' + super_table_name.lower(), '_data.h"\n'))

        # generate local table access macros in case no table access macro definition file specified:
        if tb_access_macros == None:
            build_table_access(of)

        if table_init == None:
            if addr_sec != '' and not addr_sec.startswith('0x'):
                of.write("\n{}{} {}{}".format(super_table_name, '_t __attribute__ ((section("' + addr_sec + '"))) ', super_table_name + '_init', ' = {\n'))
            else:
                of.write("\n{}{} {}{}".format(super_table_name, '_t', super_table_name + '_init', ' = {\n'))
            key_len = len(tbl_dic.keys())
            for tbl_name in tbl_dic.keys():
                key_len -= 1
                sub_tbl_entry_num_max = tbl_dic[tbl_name][3][1]
                sub_tbl_num_max = tbl_dic[tbl_name][3][0]
                tail = (',', '')[key_len == 0]
                of.write("{5}{0} {1:>{2}} {3}{4}\n".format('.' + tbl_name + '.' + tbl_name, '= ',\
                    set_pos(tbl_name + tbl_name + pre_tab, pos_shift), tbl_name.upper() + '_DATA', tail, pre_tab))
            of.write("{}".format('};\n'))
        else:
            of.write("\n{} {} {}".format('extern', super_table_name + '_t', super_table_name + '_init;\n'))

        of.write("\n{}\n".format('int main()'))
        of.write("{\n")

        if length == '0' or length == '0x0' or length == 0:
            length = addr_len_tup[1]

        pointer_prefix = 'p_'
        if not use_xtensa:
            # table pointers:
            of.write("{}{}".format(pre_tab, '// pointers to access each table:\n'))
            of.write("{}{} {}".format(pre_tab, '#undef', pointer_prefix + super_table_name + '\n'))
            of.write("{6}{0} {1} {3:>{2}}{4}{5}".format('#define', pointer_prefix + super_table_name, set_pos(super_table_name, pos_shift),\
                    '((', super_table_name + '_t *) (&', super_table_name + '_init' + '))\n', pre_tab))
            for tbl_name in tbl_dic.keys():
                of.write("{}{} {}".format(pre_tab, '#undef', pointer_prefix + tbl_name + '\n'))
                of.write("{9}{0} {1} {3:>{2}}{4}{5}{6} {7}{8}".format('#define', pointer_prefix + tbl_name, set_pos(tbl_name, pos_shift), '((',\
                        tbl_name + '_t *) ((char *)(&', super_table_name + '_init' + ') + offsetof(', super_table_name + '_t,', tbl_name, ')))\n', pre_tab))
            type_size = '0x%lx'
        else:
            if addr_sec == '' or addr_sec.startswith('0x'):
                of.write("{}{}{}{}{}\n".format(pre_tab, 'memcpy(', pointer_prefix + super_table_name, ', &' + super_table_name + '_init', ', sizeof(' + super_table_name + '_init' + '));'))
            type_size = '0x%x'
        # check table oversized or not, also avoid warning of unused variable
        of.write("{}{}{}{}{}".format(pre_tab, 'printf("sizeof(', super_table_name + \
                '_init): \\033[0;33m' + type_size + '\\033[0m bytes, oversized: %s, limits is \\033[0;32m0x%x\\033[0m\\n", ',\
                'sizeof(' + super_table_name + '_init), ', 'sizeof(' + super_table_name + '_init)  > ' \
                + length + ' - ' + ofs + '? \"\\033[0;31mYes\\033[0m\" : \"\\033[0;32mNo\\033[0m\",' + length + ' - ' + ofs + ');\n'))

        of.write("{}{}".format(pre_tab, 'printf("\\nTable access verification:\\n");'))
        for tbl_name, dim_info in table_dim_dic.items():
            if tbl_name in tbl_dic.keys(): # only if it's been processed
                sub_tbl_dic = tbl_dic[tbl_name][2] # {sub_tbl_name:(L, R, sub_tbl_hex), ...}}
                tbl_bitwidth_tup = tbl_dic[tbl_name][3]
                type_bitwidth = tbl_bitwidth_tup[1]
                tbl_struct_blk_num = tbl_bitwidth_tup[2]
                sub_tbl_num_max = table_dim_dic[tbl_name][0] # A
                sub_tbl_entry_num_max = table_dim_dic[tbl_name][1] # B

                bf_blk = tbl_dic[tbl_name][1]
                first_bf_name = bf_blk[0][0][0]
                first_bf_sign = bf_blk[0][0][6]
                last_bf_name = bf_blk[tbl_struct_blk_num - 1][len(bf_blk[tbl_struct_blk_num - 1]) - 1][0]
                last_bf_sign = bf_blk[tbl_struct_blk_num - 1][len(bf_blk[tbl_struct_blk_num - 1]) - 1][6]
                prefix0 = "{}{}{}".format('printf("first entry bit-field: ', first_bf_name, ' = %')
                prefix1 = "{}{}{}".format('printf("last entry bit-field: ', last_bf_name, ' = %')
                # in case no init data provided for tables:
                if sub_tbl_dic == {}:
                    of.write("\n{}{}{}{}".format(pre_tab, 'printf("no initialization data for table \\033[0;31m', tbl_name, '\\033[0m\\n");\n'))
                sub_tbl_idx = 0
                for sub_tbl_name in sub_tbl_dic.keys():
                    L = sub_tbl_dic[sub_tbl_name][0]
                    #R = sub_tbl_dic[sub_tbl_name][1]
                    of.write("\n{}{} {} {}".format(pre_tab, 'printf("\\non subtable:', sub_tbl_name, '\\n");'))
                    prefix2 = ('get_tf2d(' + tbl_name + ', ' + sub_tbl_name.upper(), \
                            'get_tf(' + tbl_name)[sub_tbl_num_max == 1 or sub_tbl_entry_num_max == 1]
                    of.write("\n{}{}{}, {}, {}, {}{}".format(pre_tab, prefix0, type_fmt_str(first_bf_sign), \
                            prefix2, 0, first_bf_name, '));'))
                    if sub_tbl_num_max > 1 or L >= 1:
                        of.write("\n{}{}{}, {}, {}, {}{}".format(pre_tab, prefix1, type_fmt_str(last_bf_sign), \
                                prefix2, L - 1, last_bf_name, '));'))
        if use_xtensa:
            of.write("\n{}{}\n".format(pre_tab, 'while(1);')) # needed for ASE test workaround to keep VP alive
        of.write("\n{}{}\n{}".format(pre_tab, 'return 0;', '}'))

