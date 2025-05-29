# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Sai Manideep.K.V
# Created Date: 11 Jan 2024
# =============================================================================
# test description : this test checks the data drop feature on CM1
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


DUT = fw.ABC();
V2D = fw.ABC_V2D()
path = os.getcwd()
path_split  = path.split("/")
frio_name = os.environ['HOST']
present_time = datetime.datetime.now()
clog = frio_name + '_' + str(present_time) +'.log'
os.environ['C_LOG'] = clog
current_working_directory = path_split[-1]
print(current_working_directory)

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
if arg_len != 7:
    print("Script should be run in below format\n")
    print("python cm1_data_drop.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>\n")
    print("As there were no inputs provided executing with below parameters\n")
    print(" tx_vex_id : 0\n rx_Vex_id : 1\n v2d_id : 0\n apb_id : 0\n drf_clock: 0\n test_config : 0\n")
    param = [0, 1, 0, 0, 0, 0]
else:
    param = [(int)(sys.argv[1])]
    i = 0
    for i in range(2,arg_len):
        param.append(int(sys.argv[i]))
print (param)

V2D.v2d_check(param[2])
V2D.vex_check(param[0], param[2])
V2D.vex_check(param[1], param[2])
V2D.apb_id_check(param[3])
V2D.drf_clock_check(param[4])
V2D.test_config_check(param[5])

if (param[0] == param[1]):
    print("Tx and Rx VEX cores can't be same\n")
    sys.exit("proper inputs were not provided\n")

print("All parameters are proper\n")

param_c = (c_voidp * (len(param)))(*param)

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

dut_preconfig = 1
if dut_preconfig == 1:
    #calling common init function
    #logger.info(my_functions.init())
    # executing test specific stimulus
    logger.info(my_functions.main(arg_len,param_c))
    #input_config_file = os.path.join(os.getcwd(), config_file)
    #DUT.PreConfiguration(input_config_file)


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


#compare output data
#output files not in version control
#register sequences from verification

#status check
test_status_check = 1
if test_status_check == 1:
    DUT.CheckStatus(logfile,clog)

# test run completion info
logger.info('================================test run completed==============================')
