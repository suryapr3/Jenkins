# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Sneha Singh
# Created Date: 31 July 2024
# =============================================================================
# test description : this test validate the target access via m_rcs_0 port
#                    after modifying the RBM base addr register.
# =============================================================================
# Import statements
# =============================================================================
import sys
import scripts as fw
import os
import subprocess
import logging
import datetime
import time
from ctypes import *

DUT = fw.ABC();
path = os.getcwd()
path_split  = path.split("/")
frio_name = os.environ['HOST']
present_time = datetime.datetime.now()
tstamp = time.time()
clog = frio_name + '_' + str(tstamp) +'.log'
os.environ['C_LOG'] = clog
current_working_directory = path_split[-1]
print(current_working_directory)

# set the elf path for srp_rcs_config API
os.environ['SRP_RCS_FW_FILE_DIR'] = path

logfile = current_working_directory + '.log'
shared_object = current_working_directory + '.so'
config_file = current_working_directory + '_config.csv'
isFile = os.path.exists(clog)
if isFile:
    os.remove(clog)

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s - %(filename)s - %(lineno)d - %(levelname)s - %(name)s - %(message)s')
file_handler = logging.FileHandler(logfile)
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)
stream_handler = logging.StreamHandler()
logger.addHandler(stream_handler)

#do you want to compile test specific source code
compile_test_stimulus = 0
if compile_test_stimulus == 1:
    make

load_shared_object = 1
if load_shared_object == 1:
    #upload thetest specific shared object
    my_functions =CDLL(shared_object)

# do we want to compile the rcs core firmware
compile_rcs_fw = 0
if compile_rcs_fw == 1:
    CompileRcsFw()

#to load the rcs core fw
download_rcs_fw = 0
if download_rcs_fw == 1:
    rcs_cores = [ 'lx0' , 'lx1' , 'kp1']
    rcs_fw_list = os.listdir('rcs_fw')
    for rcs_fw in rcs_fw_list:
         if rcs_cores[0] in rcs_fw:
              rcs_core_id = 0
              rcs_fw_bin = os.getcwd() + '/' + 'rcs_fw' + '/' + rcs_fw
              DUT.DownloadRcsFw(rcs_core_id,rcs_fw_bin)
         if rcs_cores[1] in rcs_fw:
              rcs_core_id = 1
              rcs_fw_bin = os.getcwd() + '/' + 'rcs_fw' + '/' + rcs_fw
              DUT.DownloadRcsFw(rcs_core_id,rcs_fw_bin)
         if rcs_cores[2] in rcs_fw:
              rcs_core_id = 2
              rcs_fw_bin = os.getcwd() + '/' + 'rcs_fw' + '/' + rcs_fw
              DUT.DownloadRcsFw(rcs_core_id,rcs_fw_bin)


#do we want to compile the vex core firmware
compile_vex_fw = 0
if compile_vex_fw == 1:
    CompileVexFw()

#to load the VEX core fw
download_vex_fw = 0
total_no_of_vex_cores = 28
if download_vex_fw == 1:
    index = 0
    string = '_' + str(index) + '_'
    vex_firmware_list  = os.listdir('vex_fw')
    for vex_fw in vex_firmware_list:
         while(string not in vex_fw):
              index += 1
              string = '_' + str(index) + '_'
         vex_fw_bin = os.getcwd() + '/' + 'vex_fw' + '/' + vex_fw
         DUT.DownloadVexFw(index,vex_fw_bin)
         index += 1
         string = '_' + str(index) + '_'

# before strating the test to reset the dut
#just a place holder, configuration needs to be updated
dut_reset = 0
if dut_reset == 1:
    DUT.Reset()

#register access transfers using srpRead/srpWrite

# test specific initialization before driving stimulus from outside( if any)
# avoid calling RTE functions directly, create the input stimulus in test_configuration.py

dut_preconfig = 1
if dut_preconfig == 1:
    core_list = [0, 1, 2]
    skip_targets_list = [
                            [0xfffffffd, 0xffffffff],
                            [0xfffffffb, 0xffffffff],
                            [0xfffffeff, 0xffffffff],
                            [0xfffffdff, 0xffffffff],
                            [0xfffffbff, 0xffffffff],
                            [0xfffff7ff, 0xffffffff],
                            [0xffffefff, 0xffffffff],
                            [0xffffdfff, 0xffffffff],
                            [0xffffbfff, 0xffffffff],
                            [0xffff7fff, 0xffffffff],
                            [0xfffeffff, 0xffffffff],
                            [0xfffdffff, 0xffffffff],
                            [0xfffbffff, 0xffffffff],
                            [0xfff7ffff, 0xffffffff],
                            [0xffefffff, 0xffffffff],
                            [0xffdfffff, 0xffffffff],
                            [0xffffffff, 0xffffffef],
                            [0xffffffff, 0xfffffeff],
                            [0xffffffff, 0xfffffbff],
                            [0xffffffff, 0xfffff7ff],
                            [0xffffffff, 0xffffefff],
                            [0xffffffff, 0xfffdffff],
                            [0xffffffff, 0xfff7ffff],
                            [0xffffffff, 0xffefffff],
                            [0xffffffff, 0xfef7ffff],
                            [0xffffffff, 0xfdffffff],
                            [0xffffffff, 0xfbffffff],
                            [0xffffffff, 0xf7ffffff]
                        ];
for core in core_list:
    for skip_targets in skip_targets_list:
        skip_targets1 = skip_targets[0];
        skip_targets2 = skip_targets[1];
        param = [core, 0x4a4a4a4a, skip_targets1, skip_targets2];
        print (param);
        param_c = (c_voidp * (len(param)))(*param)
        logger.info(my_functions.main(len(sys.argv), param_c))
        logger.info(my_functions.rte_deinit())

#to load the VEX core memory
download_vex_data = 0
if download_vex_data == 1:
    DownloadVexData(data_file)

# equipment_control
jesd_enable = 0
if jesd_enable == 1:
   JESDConfig(control_file, input_data)

#dut_post_config
dut_postconfig = 0
if dut_postconfig == 1:
    DUT.PostConfiguration(config_file)


#dump output
dump_output_data = 0
if dump_output_data == 1:
    DumpOutputData(memory_location, size)

#dump JESD output
dump_jesd_output = 0
if dump_jesd_output == 1:
    DumpJESDOutput()

# test run completion info
logger.info('================================test run completed==============================')

#compare output data
#output files not in version control
#register sequences from verification

#status check
test_status_check = 1
if test_status_check == 1:
    DUT.CheckStatus(logfile,clog)
