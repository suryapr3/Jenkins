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


#
#  Pull the daily CI build and run the RTL RCS simulation using those binaries.
#  The test runs with the 'local' RTL script and *.so test harness.
#

import urllib.request
import os
import subprocess



# Rebuild the SO files.
os.chdir( "test_tgt/rtl" )
make = subprocess.run( ["make","clean"] )
if make.returncode != 0:
    print( "Clean SO fail." )
    exit( 1 )

make = subprocess.run( ["make"] )
if make.returncode != 0:
    print( "Build SO fail." )
    exit( 1 )

# Pull the FW from the web.
contents = urllib.request.urlopen("http://txaweb.an.intel.com/hwc/daily/main/download_fw/").read()
# print( contents )
str_contents = str( contents )
start_idx = str_contents.find( "abcfw_bin" )
end_idx = str_contents.find( ".gz", start_idx )

zipfile = str_contents[start_idx:end_idx+3]

print("getting: " + zipfile )
outfile = open( zipfile, "wb")
outfile.write(  urllib.request.urlopen("http://txaweb.an.intel.com/hwc/daily/main/download_fw/" + zipfile ).read() )
outfile.close()

# Extract the zip file.
tar = subprocess.run( ["tar", "-xvf", zipfile] )
if tar.returncode != 0:
    print( "Extract FW fail." )
    exit( 1 )

# Extract the ROM from the AX binary.
rom = subprocess.run( ["../../scripts/gen_ram.py", "abc_fw/bin/ax_hw.elf", "--rom", "--size=0x100", "--tools="+os.environ['SWTOOLS_CTL']],
                        stdout = subprocess.PIPE, universal_newlines = True )
#print( rom )
if os.path.isfile("abc_fw/bin/sram/ax_rom.data"):
    os.unlink("abc_fw/bin/sram/ax_rom.data")
if not os.path.isdir("abc_fw/bin/sram"):
    os.mkdir( "abc_fw/bin/sram" )
rom_file = open( "abc_fw/bin/sram/ax_hw_rom.data", "w" )
rom_file.write(rom.stdout)
rom_file.close()

# Run the test.
subprocess.run( ['./run_rcs.sh', '-dpi', '"-r 200"', 'abc_fw/bin'] )
