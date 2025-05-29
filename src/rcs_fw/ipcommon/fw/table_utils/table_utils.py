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

#!/usr/bin/env python3

import sys
import subprocess
# don't generate __cache__
sys.dont_write_bytecode = True

# below is workaround CI env not consistent with Dev env for python support:
try:
    from openpyxl import Workbook
except ImportError or ModuleNotFoundError:
    try:
        # to use Intel customized Python Module which contains openpyxl module
        import UsrIntel.R1
    except ImportError or ModuleNotFoundError:
        print("Cannot import openpyxl module and UsrIntel.R1 module!!!")
        exit(1)

import argparse
import automate_msg 

from pm.util import *
from pm.converter import *
from pm.access_macros import build_access_macros_output

#import pprint # for debug print
#pp = pprint.PrettyPrinter(indent=4)
## breakpoint() # for putting breakpoint to debug

def main():
    """main routine to call other routines

    this routine parses command line options and call different routines accordingly

    Parameters
    ----------
    None

    Returns
    ----------
    None
    """
    parser = argparse.ArgumentParser(
            description="Utils to generate header files or convert file between .csv and .xlsx format",
            usage='%(prog)s [arguments]',
            allow_abbrev=False)
    group = parser.add_mutually_exclusive_group()
    group.add_argument('--c2h', nargs = 1, dest="c2h", type=str, help='converting given CSV file (with extention .csv) to XLSX file, then generate header file')
    group.add_argument('--c2x', nargs = 1, dest="c2x", type=str, help='converting given CSV file (with extention .csv) to XLSX file')
    group.add_argument('--x2c', nargs = 1, dest="x2c", type=str, help='converting given XLSX file (with extention .xlsx) to CSV files named after each sheets in the XLSX file')
    group.add_argument('--x2h', nargs = 1, dest="x2h", type=str, help='converting given XLSX file (with extention .xlsx) to header files')
    group.add_argument('--csv2api', nargs = 1, dest="csv2api", type=str, help='converting csv msg files to api function definitions')

    group1 = parser.add_mutually_exclusive_group()
    group1.add_argument('-a', '--address', action="store", dest="address", type=str, default="", help='start address of the table, in hex. cannot use wit -s/--section option')
    group1.add_argument('-s', '--section', action="store", dest="section", type=str, default="", help='data section name to store table. cannot use with -a/--address or -o/--offset options')
    group1.add_argument('--msg', action="store", dest="msg", type=str, help='specify name used for message header file generation. only works with switch --x2h/--c2h')

    group2 = parser.add_mutually_exclusive_group()
    group2.add_argument('--no_test', action="store_true", default=False, help='don\'t generate test program for header files, only works with switch --x2h or --c2h')
    group2.add_argument('--test_file', action="store", dest="test_file", type=str, help='specify name of table test file (without .c suffix), only works with switch --x2h or --c2h')

    parser.add_argument('--no_msg_dic_gen', action="store_true", default=False, help='don\'t generate msg_dic.dat file, only works with switch --msg, set to trun for radio msgs generation')
    parser.add_argument('--html_dir', action="store", dest="html_dir", type=str, help='folder to hold Generated HTML file for table struct, only works together with switch --c2h or --x2h')
    parser.add_argument('--xlsx', action="store", dest="xlsx", type=str, default="rename_me.xlsx", help='speicify output .xlsx file name; if not given, use name "rename_me.xlsx". only works with switch --c2x')
    parser.add_argument('--xml', action="store", dest="xml", type=str, help='specify .xsd file name used for XML file generation. only works with switch --x2h/--c2h')
    parser.add_argument('--hdr', nargs = '+', dest="hdr", help='specify .h files containing enum definition to be included for bitfield struct definition')
    parser.add_argument('--ctypes_dir', action="store", dest="ctypes_dir", type=str, help='folder to hold Generated ctypes compatible struct definition file, only works with switch --c2h or --x2h')

    parser.add_argument('--table_init', action="store", dest="table_init", type=str, help='generate table init c file, only works with switch --x2h or --c2h')
    parser.add_argument('--sheets', nargs = '+', help='specify list of sheets to process')
    parser.add_argument('--use_xtensa', action="store_true", default=False, help='create test program to be used on XTensilica based platform')
    parser.add_argument('-d', '--dir', action="store", dest="dir", type=str, default=".", help='DIR is the folder to hold result files')
    parser.add_argument('-l', '--length', action="store", dest="length", type=str, default="0x0", help='length of the table in hex, only used for sanity checking')
    parser.add_argument('-m', '--macros', action="store", dest="macros", type=str, help="Generating header file for table access macros definition, DON't run this with other switches")
    parser.add_argument('-o', '--offset', action="store", dest="offset", type=str, default="0x0", help='offset from the start address, in hex. using with -s/--section is not allowed!')
    args = parser.parse_args()
    #pp.pprint(args)
    if args.no_msg_dic_gen and args.msg == None:
        p_red('--no_msg_dic_gen can only use with --msg option for internal radio message header generation')
        sys.exit()
    if args.msg != None and (args.c2h == None and args.x2h == None):
        p_red('can only use with --c2h or --x2h option for message header generation')
        sys.exit()
    if args.ctypes_dir != None and (args.c2h == None and args.x2h == None):
        p_red('can only use with --c2h or --x2h option for ctypes compatible struct generation')
        sys.exit()
    if args.section and args.offset != '0x0':
        p_red("cannot use -o/--offset and -s/--section together!")
        parser.print_help()
        sys.exit()
    if args.address != '' and not args.address.startswith(('0x', '0X')):
        p_red('address has to be hex number start with ' + '0x ' or '0X')
        parser.print_help()
        sys.exit()
    if not args.length.startswith(('0x', '0X')):
        p_red('length has to be hex number start with ' + '0x ' or '0X')
        parser.print_help()
        sys.exit()
    if not args.offset.startswith(('0x', '0X')):
        p_red('offset has to be hex number start with ' + '0x ' or '0X')
        parser.print_help()
        sys.exit()
    if (args.xml or args.html_dir or args.no_test or args.table_init != None or args.test_file != None) \
            and (args.c2h == None and args.x2h == None):
        p_red('can only use --xml or --html_dir or --no_test or --table_init or --test_file together with either --c2h or --x2h option')
        #parser.print_help()
        sys.exit()
    else:
        if args.macros != None and (args.c2h == None and args.x2h == None):
            build_access_macros_output(args.macros, args.dir)
            sys.exit()
        if args.x2c != None:
            for f in args.x2c:
                x2c_convert(f, args.sheets, args.dir, args.msg)
        elif args.c2x != None:
            c2x_convert(args.c2x, args.xlsx, args.dir)
        elif args.c2h != None:
            xlsx_fn = args.xlsx
            tmp_dir = tempfile.gettempdir()
            if args.xlsx == 'rename_me.xlsx':
                xlsx_fn = tempfile.mktemp(suffix='.xlsx', dir='')
            c2x_convert(args.c2h, xlsx_fn, tmp_dir)
            f_name = tmp_dir + '/' + xlsx_fn + ('.xlsx', '')[xlsx_fn.endswith(".xlsx")]
            f = Path(f_name)
            if f.is_file():
                x2h_convert(f_name, args.sheets, args.dir, args.no_test, args.use_xtensa, args.address + args.section, args.length, args.offset, args.xml, args.html_dir, args.table_init, args.test_file, args.macros, args.msg, args.hdr, args.ctypes_dir, args.no_msg_dic_gen)
                f.unlink() # delete the generated .xlsx file
            else:
                p_purple3("Generated file", f_name, "doesn't exist!!!")
        elif args.x2h != None:
            for f in args.x2h:
                if Path(f).is_file():
                    x2h_convert(f, args.sheets, args.dir, args.no_test, args.use_xtensa, args.address + args.section, args.length, args.offset, args.xml, args.html_dir, args.table_init, args.test_file, args.macros, args.msg, args.hdr, args.ctypes_dir, args.no_msg_dic_gen)
                else:
                    p_purple3("given file", f, "doesn't exist!!!")
        elif args.csv2api != None:
            filename = (args.csv2api[0]).split(":")[0]
            mode = (args.csv2api[0]).split(":")[1]
            automate_msg.csv2api(filename, args.dir, mode, "fw/table_utils/pm/msg_dic.dat")
        else:
            parser.print_help()
            sys.exit()
    if not args.no_msg_dic_gen:
        try:
            result = subprocess.run(["python", "./solstice/tables.py"], check=True, capture_output=True, text=True)
            print("Output of tables.py:")
            print(result.stdout)
        except subprocess.CalledProcessError as e:
            print("Error calling tables.py")
            print(e.stderr)

if __name__ == '__main__':
    main()
