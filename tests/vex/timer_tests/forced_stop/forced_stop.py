# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Kalyani D
# Created Date: April 04 2024
# =============================================================================

# test description : this test checks if the timer 0 from each of the Vex cores is forced stopped from RCS simultaneously

# =============================================================================
# Import statements
# =============================================================================
import sys
import scripts as fw
import os
import subprocess
import logging
import datetime
from ctypes import *
import ctypes


DUT = fw.ABC();
path = os.getcwd()
path_split  = path.split("/")
frio_name = os.environ['HOST']
present_time = datetime.datetime.now()
clog = frio_name + '_' + str(present_time) +'.log'
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

arg_len = len(sys.argv)
"""
if arg_len != 5:
    print("Script should be run in below format\n")
    print("python flow3_multi_rate.py <vex_id> <v2d_id> <apb_id> <sys_rate> \n")
    print("As there were no inputs provided executing with below parameters\n")
    print(" vex_id : 0\n v2d_id : 0\n apb_id : 0\n pdpd_rate: 0 \n")
    param = ["0","0","0","0"]
    #print (len(param))
    #sys.exit("Not enough command line arguments")
else:
    # param = [(int)(sys.argv[1])]
    param = sys.argv[1:]
"""
param = sys.argv[1:]
print (param)
"""
if (param[0] >= 18 and param[0] <= 23) or (param[0] >= 26 and param[0] <= 31):
    print("Provided VEX core doesn't exist\n")
    sys.exit("proper input parameters were not provided\n")

if not (param[3] >= 0 and param[3] <= 4):
    print("provided sys_rate is not with in the range,sys_rate should be between 0 to 4\n")
    sys.exit("proper input parameters were not provided\n")

if not (param[2] >= 0 and param[2] <= 1):
    print("provided apb_num is not with in the range,apb_num should be 0 or 1\n")
    sys.exit("proper input parameters were not provided\n")

if (param[1] == 0 and not ((param[0] % 8) == 0)):
    print("provided inputs doesn't match with the NOC connections\n")
    sys.exit("proper input parameters were not provided\n")
elif (param[1] == 1 and not ((param[0] % 8) == 2)):
    print("provided inputs doesn't match with the NOC connections\n")
    sys.exit("proper input parameters were not provided\n")
elif (param[1] == 2 and not ((param[0] % 8) == 4)):
    print("provided inputs doesn't match with the NOC connections\n")
    sys.exit("proper input parameters were not provided\n")
elif (param[1] == 3 and not ((param[0] % 8) == 6)):
    print("provided inputs doesn't match with the NOC connections\n")
    sys.exit("proper input parameters were not provided\n")
"""
# Convert the list of strings to an array of c_char_p
param_c = (ctypes.c_char_p * len(param))()
param_c[:] = [s.encode('utf-8') for s in param]


#do you want to compile test specific source code
compile_test_stimulus = 0
if compile_test_stimulus == 1:
    make
print(shared_object)
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
total_no_of_vex_cores = 40
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

#logger.info(f"run with parameters vex_id: {param[0]} , v2d_id : {param[1]}, apb_id: {param[2]}")
dut_preconfig = 1
if dut_preconfig == 1:
    #In Frio, only Vex core 0-15, 32, 34, 36, 38 are functional
    #valid_vex_id_list = [*range(16)] + [32, 34, 36, 38]
    #valid_vex_id_list = [*range(1)]
    #for core_id in valid_vex_id_list:
    for timer_id in range(1):
        logger.info(my_functions.main(timer_id))
           
           
#to load the VEX core memoryS
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


#compare output data
#output files not in version control
#register sequences from verification

#status check
test_status_check = 1
if test_status_check == 1:
    DUT.CheckStatus(logfile,clog)

# test run completion info
logger.info('================================test run completed==============================')
