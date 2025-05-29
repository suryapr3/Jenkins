#!/usr/intel/pkgs/python3/3.6.3a/bin/python3
#
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


import UsrIntel.R1

import re
import argparse
import os.path
import subprocess


indent_level = 0 
last_inst_indent = 0
count_stack = [0,0]
function_stack = ["crt0", "crt1"]
symbols = dict()


#
# Track function calls and indent level.   This function prints each instruction.
#  'entry' instructions increase indent level.
#  'ret'   instructions decrease indent level.
#  'rfw'   instructions indicate 'return from window' exception and can cause a re-issue of a ret.
#
def indent( addr, inst, count ):
    global indent_level
    global last_inst_indent
    global count_stack
    global function_stack
    global symbols
    out = "  "  + inst
    for i in range(indent_level):
        out = "  " + out

    last_inst_indent = 0
    duration = 0

    if inst.startswith("entry") and indent.re_issue == 0:
        last_inst_indent = 1
        count_stack.append( int(count) )
        if addr in symbols:
            function_stack.append( symbols[addr] )
        else:
            function_stack.append( "anon" )
        out = out + "     (" + str(count) + ")"

    if "ret" in inst and indent.re_issue == 0:
        last_inst_indent = -1
        duration = int(count) - count_stack.pop()
        out = out + "     (" + str(duration) + "):" + function_stack.pop()

    if inst.startswith("rfw") or inst.startswith("rfe") or inst.startswith("rfi"):
        indent.re_issue = 1
    else:
        indent.re_issue = 0

    indent_level = indent_level + last_inst_indent
    if indent_level < 0: 
        indent_level = 0
        print ("underflow")

    return addr + "  " + out

indent.re_issue = 0


#
# Build the symbol table from the dis-assembly listing.
#
def gen_symbol_table( listing ):
    global symbols
    with open( listing ) as f:
        grep_symbol = re.compile( r"(........).<([a-zA-Z0-9_]+)>:$" )
        for line in f:
            label=grep_symbol.match(line)
            if label:
                print( label.group(1) + " ---> " + label.group(2) )
                symbols[label.group(1)] = label.group(2)
    f.close()


#
# Parse a trace from XT-RUN or ASE with trace_level = 2
#
def parse_trace_2( fname ):
    global symbols
    with open( fname ) as f:
        grep_inst = re.compile( r"\[ 0x(........) .*\] \(([0-9].*)\).*\"(.*)\"" ) 
        grep_exc  = re.compile( r".+\$exception\(\"(.*)\"\)" ) 
        grep_ccount  = re.compile( r"\s+CCOUNT <- 0x(........)" ) 
        last_ccount = 0
        except_str = ""
        for line in f:

            inst=grep_inst.match( line )
            if inst:
                addr = inst.group(1)
                count = inst.group(2)
                instr = inst.group(3)
                if addr in symbols:
                    print( indent( addr, instr, last_ccount ) + "  --->  " + symbols[ addr ]  )
                else:
                    print( indent( addr, instr, last_ccount ))
            else:
               exc = grep_exc.match( line )
               if exc:
                   except_str = exc.group(0) + " xxx " + exc.group(1)
               ccount = grep_ccount.match( line )
               if ccount:
                   last_ccount = int(ccount.group(1),16)
                   if ( except_str ):
                      print( except_str + " (" + str(last_ccount) + ")" )
                      except_str = ""
        f.close()

#
# Generate the *.dis file if it wasn't created by the post-sim actinos.
#
def generate_rtl_dis( fname ):
    if not os.path.isfile( fname ):
        tmp_script = '/tmp/pscr_' + os.environ['USER'] + '.csh'
        with open( tmp_script, 'w' ) as scr:
            scr.write( "setenv WORKAREA /nfs/site/disks/abc.mod.0001/hwc_rcs/hwc_rcs-srvrgen4-latest\n" )
            scr.write( "$WORKAREA/scripts/xt_rtldis\n" )
            scr.close()
        subprocess.run( ['tcsh', '-b', tmp_script] )
        os.unlink(tmp_script)


#
# Parse a trace from the RTL simulation trace post-processed *.dis file.
#
def parse_rtl_dis( fname, brief ):
    global symbols
    generate_rtl_dis( fname )
    if not os.path.isfile( fname ):
        print( "!!!")
        print( "!!! No trace file found: " + fname )
        print( "!!!")
        return
    with open( fname ) as f:
        grep_inst = re.compile( r"\[(........)\] -*.* \(([0-9]*),([0-9]*)\) # (.*)" ) 
        grep_exc  = re.compile( r".+\$exception (.*)" ) 
        last_ccount = 0
        except_str = ""
        for line in f:

            inst=grep_inst.match( line )
            if inst:
                addr = inst.group(1)
                icount = inst.group(2)
                ccount = inst.group(3)
                instr = inst.group(4)
                if addr in symbols:
                    print( indent( addr, instr, last_ccount ) + "  --->  " + symbols[ addr ]  )
                else:
                    inst = indent( addr, instr, last_ccount )
                    if ( brief ):
                        if ( "ret" in inst ): 
                            print( inst )
                    else:
                            print( inst )
                if ccount == "0":
                    ccount = icount
                last_ccount = int(ccount,10)
            else:
                exc = grep_exc.match( line )
                if exc:
                    except_str = exc.group(0) + " xxx " + exc.group(1)
                    print( except_str + " (" + str(last_ccount) + ")" )
        f.close()



rtl_trace_dict = { "ax" : "lx7_0.log.dis", "rx" : "lx7_1.log.dis", "tx" : "lx7_2.log.dis", "cal" : "kp1.log.dis" }
rtl_list_dict = { "ax" : "/LX70_data/", "rx" : "/LX71_data/", "tx" : "/LX72_data/", "cal" : "/KP1_data/"  }
parser = argparse.ArgumentParser(description='Build a call tree from a listing and a disassembly trace.')
parser.add_argument('--cpu', dest='cpu', default="tx", help='CPU to trace, ax, tx, rx, cal.')
parser.add_argument('--rtl', dest='rtl_trace', default='._', help='Parse an RTL trace and disassembly file from directory N.')
parser.add_argument('--t2', dest='t2_trace', default='', help='XT-RUN/ASE Trace level 2 trace file path.')
parser.add_argument('--bin', dest='binary', default='hw', help='specify sim or hw binary (requred for t2).')
parser.add_argument('--brief', dest='brief', action='store_true', help='only output entry/ret, skip other stuff.')
parser.add_argument('--lst', dest='listing', default='', help='Speficy specific listing file (with t2).')


args = parser.parse_args();

# Find and parse an RTL trace.
rtl_dir = args.rtl_trace
if not os.path.isdir( rtl_dir ):
    rtl_dir = "test_tgt/rtl/rcs_rpc_lx7_0_boot." + args.rtl_trace
if not os.path.isdir( rtl_dir ):
    rtl_dir = os.environ['PRJDIR'] + "/" + rtl_dir
if os.path.isdir( rtl_dir ):
    rtl_trace_file = rtl_dir + "/trace_" + rtl_trace_dict[args.cpu]
    elf_name = args.cpu + "_hw.elf"
    rtl_listing_file = rtl_dir +  rtl_list_dict[args.cpu] + "prog/" + elf_name + "/" + elf_name + ".dis"
    if not os.path.isfile( rtl_listing_file ):
        elf_name = args.cpu + "_sim.elf"
        rtl_listing_file = rtl_dir +  rtl_list_dict[args.cpu] + "prog/" + elf_name + "/" + elf_name + ".dis"
    if not os.path.isfile( rtl_listing_file ):
        print( "!!!" )
        print( "!!! no listing file found: " + rtl_listing_file )
        print( "!!!" )
    else:
        gen_symbol_table( rtl_listing_file )
        parse_rtl_dis( rtl_trace_file, args.brief )
elif os.path.isfile( args.t2_trace ):
    # If not RTL, find and parse a T2 trace.
    listing = args.listing
    if not os.path.isfile( listing ):
        listing = "out/bin/info/" + args.cpu + "_" + args.binary + ".lst"
    if not os.path.isfile( listing ):
        listing = os.environ['PRJDIR'] + "/" + listing
    if not os.path.isfile( listing ):
        print( "!!!" )
        print( "!!! no listing file found: " + listing )
        print( "!!!" )
    else:
        gen_symbol_table( listing )
        parse_trace_2( args.t2_trace )
else:
    print( "!!!" )
    print ("!!! no trace file found.")
    print( "!!!" )
