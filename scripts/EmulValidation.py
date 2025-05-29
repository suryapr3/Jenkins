# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Lovekesh Gupta
# Created Date: January 1 2023
# =============================================================================
# Main Regression script for ABC emul Validation ..."""
# =============================================================================
# Import statements
# =============================================================================
import sys
import os
import time
import subprocess
import logging
import csv

path =os.getcwd()
path_split  = path.split("/")
current_working_directory = path_split[-1]
logfile = current_working_directory + '.log'
isFile = os.path.exists(logfile)
if isFile:
    os.remove(logfile)
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
file_handler = logging.FileHandler(logfile,mode = "a")
formatter = logging.Formatter('%(asctime)s - %(filename)s - %(lineno)d - %(levelname)s - %(name)s - %(message)s')
file_handler.setFormatter(formatter)
logger.addHandler(file_handler)
stream_handler = logging.StreamHandler()
logger.addHandler(stream_handler)
logger.debug("=============================test starts here========================")




class ABC():

    def __init__(self):

         self.testinput = None



    ###########################################################################################
    #     Function name   :- CheckStatus
    #     Input parameter :-
    #     Description     :- This function will check for errors in logfile
    #
    #
    ###########################################################################################

    def CheckStatus(self,logfile,clog):
         error_count = 0
         warning_count = 0
         logfile = open(logfile,'r')
         clog   = open(clog,'r')
         lines = logfile.readlines()
         for line in lines:
             if 'ERROR:' in line:
                   error_count += 1;
             elif 'WARNING:' in line:
                   warning_count +=1;
         lines = clog.readlines()
         for line in lines:
             if 'ERROR:' in line:
                   error_count += 1;
             elif 'WARNING:' in line:
                   warning_count +=1;
         if error_count == 0 and  warning_count == 0:
              logger.info("there is no error or warning")
              logger.info("========================= test pass =============================")
         elif  error_count ==0 and warning_count > 0:
              logger.info("there are warnings in the test, please review")
              logger.info("========================= test pass =============================")
         elif  error_count > 0 :
              logger.error("there are  errors in the test, please resolve")
              logger.error(f"no of errors are {error_count}")
              logger.error("========================= test Fail =============================")







    ###########################################################################################
    #     Function name   :- DutReset
    #     Input parameter :- None
    #     Description     :- This function is used to reset the DUT ( Dummy function at present)
    #
    #
    ###########################################################################################

    def DutReset():
         address = 0x20000 #just random address just 2for placeholder
         mask = 0x00000080
         write_data = 0x00000080 #just a random mask bit for placeholder
         read_data_status = subprocess.run(['srpRead', 'address'], stdout=subprocess.PIPE,text=True)
         if read_data_status.returncode == 1:
              logger.error(f"read from {address} is not successful")
         logger.debug(f"data read from {address} is read_data_status.stdout")
         data_to_write = read_data_status.stdout | (mask & write_data)
         write_data_status = subprocess.run(['srpWrite','address' , 'write_data'],stdout=subprocess.PIPE,text=True)
         if write_data_status.returncode == 1:
              logger.error(f"{write_data} with {mask} to {address} is not successful")
         logger.debug(f"data written at {address} is {write_data} with {mask}")


     ###########################################################################################
     #     Function name    :- PreConfiguration
     #     Input parameter  :- csv file containg read/write/compare transaction
     #     Description      :- This function is used to configure DUT using RTE read/write calls
     #                         before configuring external equipments likes XSTEPV and driving input
     #                         data to the controller
     ###########################################################################################

    def PreConfiguration(self, configuration_file):
         #with configuration_file as file:
         with open(configuration_file, 'r') as file:
              csvreader = csv.DictReader(file)
              for row in csvreader:
                   #configuration before starting external equipement (XSTEPV etc)
                   if row['Configuration'] == "Pre":
                        if row['Transaction_Type'] == "Write":
                             address = row['Address']
                             mask = row['Mask']
                             write_data = row['Data']
                             read_data_status = subprocess.run(['srpRead', f'{address}'], stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                             data_to_write = hex(int(read_data_split[1],16) | (int(mask,16) & int(write_data,16)))
                             write_data_status = subprocess.run(['srpWrite',f'{address}' , f'{data_to_write}'],stdout=subprocess.PIPE,text=True)
                             if write_data_status.returncode == 1:
                                  logger.error(f"{write_data} with {mask} to {address} is not successful")
                             logger.debug(f"data written at {address} is {data_to_write} with {mask}")
                        if row['Transaction_Type'] == "Read":
                             address = row['Address']
                             mask = row['Mask']
                             read_data_status = subprocess.run(['srpRead', f'{address}'],stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                        if row['Transaction_Type'] == "Compare":
                             address = row['Address']
                             mask = row['Mask']
                             expected_data = row['Data']
                             read_data_status = subprocess.run(['srpRead', f'{address}'],stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                             if int(expected_data,16) == int(read_data_split[1],16):
                                  logger.info(f"read_data_status.stdout matches with expected data")
                             else :
                                  logger.error(f"read_data_status.stdout does not matches with expected data")


     ###########################################################################################
     #     Function name   :- PostConfiguration
     #     Input parameter :- csv file containg read/write/compare transaction
     #     Description     :- This function is used to configure DUT using RTE read/write calls
     #                        before configuring external equipments likes XSTEPV and driving input
     #                        data to the controller
     ###########################################################################################
    def PostConfiguration(self, configuration_file):
         #with configuration_file as file:
         with open(configuration_file, 'r') as file:
              csvreader = csv.DictReader(file)
              for row in csvreader:
                   #configuration before starting external equipement (XSTEPV etc)
                   if row['Configuration'] == "Post":
                        if row['Transaction_Type'] == "Write":
                             address = row['Address']
                             mask = row['Mask']
                             write_data = row['Data']
                             read_data_status = subprocess.run(['srpRead', f'{address}'], stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                             data_to_write = hex(int(read_data_split[1],16) | (int(mask,16) & int(write_data,16)))
                             write_data_status = subprocess.run(['srpWrite',f'{address}' , f'{data_to_write}'],stdout=subprocess.PIPE,text=True)
                             if write_data_status.returncode == 1:
                                  logger.error(f"{write_data} with {mask} to {address} is not successful")
                             logger.debug(f"data written at {address} is {data_to_write} with {mask}")
                        if row['Transaction_Type'] == "Read":
                             address = row['Address']
                             mask = row['Mask']
                             read_data_status = subprocess.run(['srpRead', f'{address}'],stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                        if row['Transaction_Type'] == "Compare":
                             address = row['Address']
                             mask = row['Mask']
                             expected_data = row['Data']
                             read_data_status = subprocess.run(['srpRead', f'{address}'],stdout=subprocess.PIPE,text=True)
                             if read_data_status.returncode == 1:
                                  logger.error(f"read from {address} is not successful")
                             read_data = read_data_status.stdout
                             read_data_split = read_data.split()
                             logger.debug(f"data read from {address} is {read_data_split[1]}")
                             if int(expected_data,16) == int(read_data_split[1],16):
                                  logger.info(f"read_data_status.stdout matches with expected data")
                             else :
                                  logger.error(f"read_data_status.stdout does not matches with expected data")


     ###########################################################################################
     #     Function name   :- CompileRcsFw
     #     Input parameter :- compilation options
     #     Description     :- This function compile the RCS firmware
     #
     ###########################################################################################


     ###########################################################################################
     #     Function name   :- CompileRcsFw
     #     Input parameter :- compilation options
     #     Description     :- This function compile the RCS firmware
     #
     ###########################################################################################


     ###########################################################################################
     #     Function name   :- DownloadRcsFw
     #     Input parameter :- memory instance
     #     Description     :- This function will download the RCS firmware into the memory
     #
     ###########################################################################################
    def DownloadRcsFw(self,index,rcs_fw):
         core_id = index
         with open(rcs_fw, 'r') as file:
              rcs_fw_download = subprocess.run(['srpRcsLoader', "-c", f'{index}', "-f" ,f'{rcs_fw}'], stdout=subprocess.PIPE,text=True)
              if rcs_fw_download.returncode == 1:
                   logger.error(f"rcs fw download to rcs core no {index} failed")
              logger.info(f"rcs fw download to rcs core no {index} is successful")


     ###########################################################################################
     #     Function name   :- DownloadVexFw
     #     Input parameter :- memory instance
     #     Description     :- This function will download the VEX firmware into the memory
     #
     ###########################################################################################
    def DownloadVexFw(self,index,vex_fw):
         index = index
         with open(vex_fw, 'r') as file:
              vex_fw_download = subprocess.run(['srpVexLoader', "-c", f'{index}', "-f" ,f'{vex_fw}'], stdout=subprocess.PIPE,text=True)
              if vex_fw_download.returncode == 1:
                   logger.error(f"vex fw download to vex core no {index} failed")
              logger.info(f"vex fw download to vex core no {index} is successful")
     ###########################################################################################
     #     Function name   :- JESDConfig
     #     Input parameter :- JESD configuration file and input data file
     #     Description     :- This function will configure the the XSTEPV and send the input data to
     #                        controller
     #
     ###########################################################################################


     ###########################################################################################
     #     Function name   :- DumpOutputData
     #     Input parameter :-
     #     Description     :- This function dumps the data from the memory
     #
     #
     ###########################################################################################


     ###########################################################################################
     #     Function name   :- DumpJESDOutput
     #     Input parameter :-
     #     Description     :- Dump the output data from JESD
     #                        controller
     #
     ###########################################################################################




     ###########################################################################################
     #     Function name   :-  CompareData
     #     Input parameter :-
     #     Description     :-  This function compare the data with expected value
     #
     #
     ###########################################################################################

     ###########################################################################################
     #     Function name   :-  GenerateReport
     #     Input parameter :-
     #     Description     :-  This function generates the status report
     #
     #
     ###########################################################################################

     ###########################################################################################
     #     Function name   :-  RunRegression
     #     Input parameter :-
     #     Description     :-  This function runs the regression
     #
     #
     ###########################################################################################
