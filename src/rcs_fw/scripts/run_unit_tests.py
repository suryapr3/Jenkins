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
#  Execute Unit tests, no command-line input required.
#    Two environment variables expected:
#         PRJDIR:      Base driectory of the FW repo.
#         SWTOOLS_CTL: Base driectory of the RCS Xtensa toolchain.
#
#  To add unit tests, add the UnitTest ELF file to the test_list.
#
#  If the test has specific outputs that would be counted as errors, these
#  can be ignored by adding the strings to the 'ignorelist' dictionary.
#  Any test can also bracket expected fails with:  
#     'expected errors follow'/'end of expected errors'
#


import sys
import os
import io
import subprocess


#
# Represent a unit test, group the CPU type and ELF executable file.
#
class UnitTest:
    cpu_map = { "LX7" : "HWC_RCS_LX7", "KP1" : "HWC_RCS_KP1", "ANA" : "hwc_adc_lx7" }
    
    def __init__(self, file, cpu):
        self.elf_file = file
        self.core = cpu
        if ( not cpu in self.cpu_map ):
            print( "Invalid CPU name: " + cpu )
            quit(1)

    # return the file name only for dict keys.
    def test_name(self):
        return os.path.basename( self.elf_file )


    # Find the toolchain.
    def xtensa_dir(self):
        xtensa_bin = "xxx"
        if ( self.core == "LX7" or self.core == "KP1" ):
            xtensa_bin=os.environ.get("SWTOOLS_CTL")
        if ( self.core == "ANA" ):
            xtensa_bin=os.environ.get("SWTOOLS_ANA")
        if ( not os.path.isdir(xtensa_bin) ):
            print("Unable to find Xtensa directory: " + xtensa_bin )
            quit(1)
        return xtensa_bin

    # start the test program, return a subprocess.
    def execute(self):
        xt_run = self.xtensa_dir() + "/bin/xt-run"
        cpu_flag = "--xtensa-core=" + self.cpu_map[self.core]
        print( "**\n** Running test: " + self.elf_file + "\n**" )
        test_process = subprocess.Popen( [xt_run, "--turbo", cpu_flag, self.elf_file], stdout=subprocess.PIPE, stderr=subprocess.STDOUT )
        return test_process



prjdir=os.environ.get("PRJDIR")

if ( not os.path.isdir(prjdir) ):
    print("Unable to find project directory: " + prjdir )
    quit(1)

#
#  These strings manage errors.   detection and suspension.
#
errors=[ 'assert', 'error', 'warning' ]
global_stop='expected errors follow'
global_start='end of expected errors'
#
#  Add unit tests to this list.  Full path to test.
#
test_list=[ UnitTest(prjdir+"/out/bin/unit/ax/com_event_test.elf", "LX7"), 
            UnitTest(prjdir+"/out/bin/unit/ax/com_bfn_test.elf", "LX7"),
            UnitTest(prjdir+"/out/bin/unit/ax/com_idma_test.elf", "LX7"),
            UnitTest(prjdir+"/out/bin/unit/ax/com_gpdma_test.elf", "LX7"),  
            UnitTest(prjdir+"/out/bin/unit/ax/com_queue_test.elf", "LX7"), 
            UnitTest(prjdir+"/out/bin/unit/ax/com_timing_test.elf", "LX7"),
            UnitTest(prjdir+"/out/bin/unit/tx/tx_msg_handler_test.elf", "LX7"),
            UnitTest(prjdir+"/out/bin/unit/rx/rx_msg_handler_test.elf", "LX7"),
            UnitTest(prjdir+"/out/bin/unit/cal/cal_sample_unit_test.elf", "KP1"),
            UnitTest(prjdir+"/out/bin/unit/ax/com_swg_test.elf", "LX7")]

#  Add ignore strings here.   Test file name only as key.
#  All strings must be lower-case.
ignore_list={ "com_event_test.elf" : ["requesting exit of event loop."],
              "tx_msg_handler_test.elf" : ["requesting exit of event loop.", "unsupported opcode 65528"],
              "rx_msg_handler_test.elf" : ["requesting exit of event loop.","unsupported opcode 65523"]
              }

#  Add stop checking strings here to ignore a block of warnings.   Test file name only as key.
#  All strings must be lower-case.
stop_check_list={ "com_queue_test.elf"  : ["expecting queue full"] }#, "expecting queue empty"] }

#  Restart checking after suspending warnings.   Test file name only as key.
#  All strings must be lower-case.
start_check_list={ "com_queue_test.elf"  : ["queue is full"] }#, "queue is empty"] }

for test in test_list:
    test_name = test.test_name()
    stop_checking = False
    test_failed = False
    ignored_fails = 0
    test_process = test.execute()

    for line in io.TextIOWrapper(test_process.stdout):
        data = line.rstrip('\n')
        print( data )
        ldata=data.lower()

        ignore = False
        if test_name in ignore_list:
            for pass_str in ignore_list[test_name]:
                if ( pass_str in ldata ):
                    print( "** ignore failure due to: " + pass_str )
                    ignore = True;

        stop_list = [ global_stop ]
        if test_name in stop_check_list:
            stop_list.extend(stop_check_list[test_name])
        for stop_str in stop_list:
            if ( stop_str in ldata ):
                print( "** stop checking due to: " + stop_str )
                stop_checking = True
                ignored_fails  = 0

        for err_str in errors:
            if ( err_str in ldata ):
                if ( ignore or stop_checking ):
                    print( "** Error Forgiven: " + err_str )
                    ignored_fails += 1
                else:
                    print( "** Error found: " + err_str )
                    test_failed = True

        start_list = [ global_start ]
        if test_name in start_check_list:
            start_list.extend(start_check_list[test_name])
        for start_str in start_list:
            if ( start_str in ldata ):
                print( "** start checking due to: " + start_str )
                stop_checking = False
                if ( ignored_fails == 0 ):
                    print ( "** no fails encountered while they were expected." )
                    test_failed = True

    test_process.wait()
    if ( test_process.returncode ):
        print( "**\n** Test return: " + str(test_process.returncode) + "\n**" )
        test_failed = True
    
    if ( test_failed ):
        print( "**\n** test FAIL\n**" )
        quit(1)

print( "**\n** ALL PASS\n**" )
quit( 0 )

