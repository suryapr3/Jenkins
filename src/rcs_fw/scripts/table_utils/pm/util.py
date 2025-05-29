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

import sys
import re # for regular expression
import textwrap as tr # wraping long comments

"""
helper functions: terminal color output
"""
# print v2 and v4 in red, v1 and v3 in normal
def p_red4(v1, v2, v3, v4): print("{} \033[91m{}\033[00m {} \033[91m{}\033[00m".format(v1, v2, v3, v4))

# print v2 in red and v1 in normal
def p_red2(v1, v2): print("{} \033[91m{}\033[00m".format(v1, v2))

# print v1 in red
def p_red(v1): print("\033[91m{}\033[00m".format(v1))

# print v1 in normal, v2 in green
def p_green2(v1, v2): print("{} \033[92m{}\033[00m".format(v1, v2))

# print v1, v3, v5 in normal, v2, v4 and v6 in purple
def p_purple_red6(v1, v2, v3, v4, v5, v6): print("{} \033[95m{}\033[00m {} \033[91m{}\033[00m {} \033[91m{}\033[00m".format(v1, v2, v3, v4, v5, v6))

# print v1, v3 in normal, v2 in purple
def p_purple3(v1, v2, v3): print("{} \033[95m{}\033[00m {}".format(v1, v2, v3))

# print v1, v3 in normal, v2 and v4 in green
def p_green4(v1, v2, v3, v4): print("{} \033[92m{}\033[00m {} \033[92m{}\033[00m".format(v1, v2, v3, v4))

def set_pos(mystr, length):
    """set position adjustment

    calculate offset to adjust string position

    Parameters
    ----------
    mystr : str
        string to set position for
    length : int
        offset for adjustment

    Returns
    -------
    int value to be used for position adjustment

    """
    return (length - len(mystr), 2)[len(mystr) >= length]

def wrap(string, max_width, num_of_tab, prefix_str, pos):
    """wrap string if necessary

    Wrapping a string based on maximum sub-string length setting, also adding tabs in front of each sub-string if specified

    Parameters
    ----------
    string : str
        an input string for wrapping
    max_width : int
        maximum string length for wrapping
    num_of_tab : int
        number of tabs added in front of each wrapped sub-string
    pos : int
        position adjustment (as blank space after sub-string)

    Returns
    -------
    a string after wrapping
    """
    return ('\n' + '\t' * num_of_tab + ' ' * pos + prefix_str).join(tr.wrap(string, max_width))

def parse_dim_info(dim_info, length, sheet, cell_pos):
    """parsing dimension info

    Parameters
    ----------
    dim_info : str
        string contains numbers as dimension to be parsed
    length : int
        specifying the expected dimension, for error check
    sheet : Worksheet
        the worksheet which contains table info
    cell_pos : str
        cell position info, for error check

    Returns
    ----------
    tup containing table dimension (int) and sign (str) info
    """
    if not isinstance(dim_info, str):
        p_red4("information is not correct at cell", cell_pos, "in sheet", sheet.title)
        sys.exit()
    dim = re.findall(r'\d+', dim_info)
    if len(dim) == length:
        dim_tuple = tuple(map(int, dim))
        sig = tuple(re.findall(r"[*+-]", dim_info))
        dim_tuple += sig
        return dim_tuple
    else:
        p_purple_red6('dimension info', dim_info, 'is wrong in sheet', sheet.title, 'at cell', cell_pos)
        sys.exit()

