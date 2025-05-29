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


import sys
import os
import argparse

#
# ROM image, 4 bytes per line.  No address info.
#
def gen_rom( size, elf, tools_dir ):
    path = ""
    if tools_dir != "":
        path = tools_dir + "/bin/"
    cmd = path + "xt-dumpelf --width=32 --little-endian --sparse --no-bss --base=0x0 --size=" + size + " " + elf
    #print( cmd )
    linecount=0
    for line in os.popen( cmd ).readlines():
        if ( line[0] != '@' ):
            data = line.rstrip('\n')
            #print( f'{linecount:08x} {data}' )
            print( data )
            linecount += 1
    while linecount % 4 != 0:
        print( "00000000" )
        linecount += 1


#
# RAM images, 32 bytes per line. Include address info for scattering using "readmemh".
#
def gen_sram( start, offset, size, elf, count_lines, tools_dir ):
    path = ""
    if tools_dir != "":
        path = tools_dir + "/bin/"
    cmd = path + "xt-dumpelf --width=128 --little-endian --sparse --no-bss --base=" + start + " --size=" + size + " --offset=" + offset + " " + elf
    #print( cmd )
    linecount = 0
    for line in os.popen( cmd ).readlines():
        data = line.rstrip('\n')
        linecount += 1
        if ( data[0] == '@' ):
            linecount = int(data[1:],16)
            #print( "set linecount to " + str(linecount) )
        print( data )
    if ( count_lines ):
        print( linecount )

#
# RAM images, 32 bytes per line. Include address info for scattering using "readmemh".
#
def gen_ana_sram( start, offset, size, elf, count_lines, tools_dir ):
    width=32
    path = ""
    if tools_dir != "":
        path = tools_dir + "/bin/"
    option = "--sparse"
    cmd = path + "xt-dumpelf --width="+str(width)+" --little-endian " + option + " --no-bss --base=" + start + " --size=" + size + " --offset=" + offset + " " + elf
    #print( cmd )
    #print(output_format)
    linecount = 0
    for line in os.popen( cmd ).readlines():
        data = line.rstrip('\n')
        linecount += 1
        if data[0] == "@":
            linecount = int(data[1:], 16)
            # print( "set linecount to " + str(linecount) )
        print(data)
    if count_lines:
        print(linecount)


parser = argparse.ArgumentParser(description='Extract memory contents from elf file for RAM/ROM preloading.')
parser.add_argument('elf', metavar='file.elf', help='ELF file to process')
parser.add_argument('--size', dest='mem_size', default="0", help='max size of the image in bytes, hex format 0xN+.')
parser.add_argument('--start', dest='mem_start', default="0x0", help='start address of the image in bytes.')
parser.add_argument('--rom', dest='rom', action='store_true', help='generate ROM format output')
parser.add_argument('--no-lines', dest='sim_lines', action='store_false',help='suppress number of lines in the file')
parser.add_argument('--tools', dest='tools_dir', default="", help='Xtensa Tools Directory')
parser.add_argument('--offset', dest='offset_addr', default="0", help='Offset for start address')
parser.add_argument('--ana_core', dest='ana_core', action='store_true', help='analog core')
parser.add_argument('--path', dest= 'directory', default="", help='RX src Directory')
parser.add_argument('--file', dest= 'file', default="0", help='iram or dram directory')
parser.add_argument('--file_chk', dest='file_chk', action='store_true', help='generate sim or hw data file')
parser.add_argument('--build', dest= 'build', default="", help='sim or hw build')

args = parser.parse_args()

if ( int(args.mem_size,16) <= 0 ):
    print( "--size must be > 0" )
    sys.exit()

if ( args.rom ):
    gen_rom( args.mem_size, args.elf, args.tools_dir )
elif(args.ana_core):
    gen_ana_sram( args.mem_start, args.offset_addr, args.mem_size, args.elf, args.sim_lines,  args.tools_dir )
else:
    gen_sram( args.mem_start, args.offset_addr, args.mem_size, args.elf, args.sim_lines, args.tools_dir )

