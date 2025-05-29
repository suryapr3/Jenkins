# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Sai Manideep.K.V
# Created Date: Feb 14 2024
# =============================================================================
# test description : this test checks the behavior when all V2D's are active.
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
if arg_len != 3:
    print("Script should be run in below format\n")
    print("python flow3_Ch0_Ch1_v2d_all_test.py <drf_clock> <test_config>\n")
    print("As there were no inputs provided executing \n")
    test_config = 0
    drf_clock = 0
else:
    drf_clock = (int) (sys.argv[1])
    test_config = (int) (sys.argv[2])

print("drf_clock:")
print(drf_clock)
print("test_config:")
print(test_config)

V2D.drf_clock_check(drf_clock)
V2D.test_config_check(test_config)

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

rx_vex_index_list = [1, 3]
tx_vex_index_list = [0, 2]

dut_preconfig = 1
if dut_preconfig == 1:
    #calling common init function
    logger.info(my_functions.init())
    # executing test specific stimulus
    param0 = [0, 1, 8, 9, 0, 0, 4, 0]
    param0[5] = drf_clock
    param0[6] = test_config
    param_c = (c_voidp * (len(param0)))(*param0)
    print(param0)
    logger.info(my_functions.main(arg_len,param_c))

    param1 = [2, 3, 10, 11, 1, 0, 4, 0]
    param1[5] = drf_clock
    param1[6] = test_config
    param_c = (c_voidp * (len(param1)))(*param1)
    print(param1)
    logger.info(my_functions.main(arg_len,param_c))

    param2 = [4, 5, 12, 13, 2, 0, 4, 0]
    param2[5] = drf_clock
    param2[6] = test_config
    param_c = (c_voidp * (len(param2)))(*param2)
    print(param2)
    logger.info(my_functions.main(arg_len,param_c))

    param3 = [6, 7, 14, 15, 3, 0, 4, 0]
    param3[5] = drf_clock
    param3[6] = test_config
    param_c = (c_voidp * (len(param3)))(*param3)
    print(param3)
    logger.info(my_functions.main(arg_len,param_c))

    time.sleep(60)
    #check the interrupt status for all V2D's, parameters are number of V2D instances and the expected value of V2D interrupt
    logger.info(my_functions.get_all_v2d_int_status(4, 0))

    for rx_vex in rx_vex_index_list:
        #Check the data integrity of Rx VEX cores
        #parameters are vex_num, DMEM location and expected value
        logger.info(my_functions.vex_dmem_check(param0[rx_vex], 0x34, 0xFFFFFFFF))
        logger.info(my_functions.vex_dmem_check(param1[rx_vex], 0x34, 0xFFFFFFFF))
        logger.info(my_functions.vex_dmem_check(param2[rx_vex], 0x34, 0xFFFFFFFF))
        logger.info(my_functions.vex_dmem_check(param3[rx_vex], 0x34, 0xFFFFFFFF))


    for tx_vex in tx_vex_index_list:
        #write to VEX DMEM to stop continuous data transfer
        #parameters are vex_num, DMEM location and value to be written
        logger.info(my_functions.vex_dmem_write(param0[tx_vex], 0x10, 3))
        logger.info(my_functions.vex_dmem_write(param1[tx_vex], 0x10, 3))
        logger.info(my_functions.vex_dmem_write(param2[tx_vex], 0x10, 3))
        logger.info(my_functions.vex_dmem_write(param3[tx_vex], 0x10, 3))


    time.sleep(5)
    #check the interrupt status for all V2D's, parameters are number of V2D instances and the expected value of V2D interrupt
    logger.info(my_functions.get_all_v2d_int_status(4, 0x40000))

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
