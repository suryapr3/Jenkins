#!/usr/bin/env python3
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
# writing.

import re
import sys
import os
import argparse
from os import path

def gen_mssg( elf, dest_path, tools_dir ):
    if tools_dir != "":
        path = tools_dir + "/bin/"
    core_arg = ""
    if "cal" in elf:
        core_arg = "--xtensa-core=HWC_RCS_KP1"
    cmd = path + "xt-objdump " + core_arg + " -EB -D -j .dram0.debug.rodata" + " " + elf
    count = 0
    with open(os.path.join(dest_path, "out_debug.txt"), 'a+') as fout:
        grep_symbol = re.compile( r"(........).<([a-zA-Z0-9_\.]+)>:$" )
        for line in os.popen( cmd ).readlines():
            label=grep_symbol.match(line)
            if label:
                all_words = line.split()
                if count == 0:
                    fout.write(all_words[0] + "    ")
                    count = count + 1
                else:
                    fout.write( "\n" + all_words[0] + "    ")
            else:
                symbol2 = re.compile( r"(........:\s*)(.{8}\s.{8}\s.{8}\s.{8}\s*)(.*)")
                inst = symbol2.match( line)
                if inst:
                    fout.write(inst.group(3))
        fout.write("\n")
    fout.close()
    
    fin = open(os.path.join(dest_path, "out_debug.txt"), 'rt')
    for line in fin:
        s1 = re.sub(r".c\"", ".c", line)
        s1 = re.sub(r"\s+\.+\n", "\"\n", s1)
        s1 = re.sub(r"%lu", "%d", s1)
        s1 = re.sub(r"%u", "%d", s1)
      
        print(s1, end ="")
    fin.close()
    os.remove(os.path.join(dest_path, "out_debug.txt"))

   
parser = argparse.ArgumentParser(description='Extract debug messages for pre-silicon verification.')
parser.add_argument('elf', metavar='file.elf', help='ELF file to process')
parser.add_argument('lst', metavar='file.lst', help='LST file to process')
parser.add_argument('--tools', dest='tools_dir', default="", help='Xtensa Tools Directory')
parser.add_argument('--path', dest= 'directory', default="", help='Sim Directory')
args = parser.parse_args()
f=open(args.lst, 'rt')
content = f.readlines()
if any(".dram0.debug.rodata" in word for word in content):
    gen_mssg( args.elf, args.directory, args.tools_dir )
