##############################################################################
#                                                                            #
#  2014-2019 Mentor Graphics Corporation. All rights reserved.             #
#                                                                            #
#  THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY                           #
#  INFORMATION WHICH ARE THE PROPERTY OF MENTOR                              #
#  GRAPHICS CORPORATION OR ITS LICENSORS AND IS                              #
#  SUBJECT TO LICENSE TERMS.                                                 #
#                                                                            #
##############################################################################

# This is an example on how to launch and interface with a 
# precompiled X-STEP test case from a Python script.

#!/usr/intel/pkgs/python3/3.6.3a/bin/python
import UsrIntel.R1
#!/usr/intel/bin/python3.6.3a
import UsrIntel.R1
#!/usr/intel/pkgs/python3/3.7.4/bin/python
import UsrIntel.R1
#!/usr/intel/bin/python3.7.4
import UsrIntel.R1

import paramiko
import os
import sys
import time
import telnetlib

#Added by Aditya for importing binary
from jesd_test_map import *



# Connection settings (fixed username + password in every X-STEP)
XSTEP = os.environ['XSTEPV']
user = "root"
passwd = "sarokal"

# Testing speficic settings, eg. folders and test case in XStep-board, where the 
# testing environment has been deployed
xstep_base      = '/root/XStep/'
xstep_base_libs = os.path.join(xstep_base, 'lib')
xstep_base_work = os.path.join(xstep_base, 'work')

#Added by Aditya for binary picking
#path = 'xstep_files/UC_5C/UC_5C_TX/JESD204C_4Lane_1250Mbps_Rx'

path = None
test_case = None
log_file = None
binary = None
def pickbinary(param):
    print('Getting binary')
    global path
    path = getbinary(param)
    parts = path.split('/')  # Split the string by '/'
    global binary
    binary = parts[-1]  # Get the last part of the list
    print(binary)
    # Test case expect that JESD204C_4Lane_1250Mbps_Rx binary is available at /root/XStep/work - run or compiled once using Client GUI before this script is run
    #test_case       = './JESD204C_2Lane_1250Mbps_Rx mode=slave'

    #Modified by Aditya for binary picking
    global test_case
    test_case       = './' + binary + ' mode=slave'
    global log_file
    log_file        = open(binary + '_Python.log', 'w')


def display_print():
    print("hello from roshan inside display_print\n")

def waitForMsgs(response_to_wait):
    resp = ''
    global verdict
    global errors
    global warnings
    
    while (1):
        resp   = ssh_channel.recv(9999).decode('utf-8')
        print (resp, end='')
        log_file.write(resp)
        log_file.flush()
        
        # From response we wan't to grab the RETURN_VALUE
        # Response syntax is following:
        # #API_CALL TIMEms: RETURN_VALUE API_CALL_PARAMETERS
        # eg. #x.variable.set 1948ms: 0 CPRI/numlinks 1
        if (resp.find(response_to_wait) != -1):
            index     = resp.find(response_to_wait)
            error_msg = resp[index:].split('\n') 
            error_msg = error_msg[0]                 # #API_CALL TIMEms: RETURN_VALUE API_CALL_PARAMETERS
                                                    # Add this msg to errors[] or warnings[]
            temp      = error_msg                     
            index     = temp.find('ms:') 
            temp      = temp[(index+4):]             # ms: RETURN_VALUE API_CALL_PARAMETERS
            temp      = temp.split(' ')              # (RETURN_VALUE, API_CALL_PARAMETER_1, API_CALL_PARAMETER_2)
            retval    = int(temp[0])                 # RETURN_VALUE
            
            if (retval < 0):
                verdict = 'FAIL'
                errors.append(error_msg)
            elif (retval > 0):
                verdict = 'FAIL'
                warnings.append(error_msg)
            
        if (resp.find('testcase.error') != -1):
            index   = resp.find('testcase.error')
            error   = resp[index:].split('\n')
            error   = error[0]
            errors.append(error)
            verdict = 'FAIL'
                
        if (resp.find('testcase.warning') != -1):
            index    = resp.find('testcase.warning')
            warning  = resp[index:].split('\n')
            warning  = warning[0]
            warnings.append(warning)
            verdict  = 'FAIL'
            
        if (resp.find('log.warning') != -1):
            index    = resp.find('log.warning')
            warning  = resp[index:].split('\n')
            warning  = warning[0]
            warnings.append(warning)
            verdict  = 'FAIL'
        
        # Special handler for x.exit API call
        if (resp.find('Exit from XStep pid') != -1):
            if (verdict == 'RUNNING'):
                verdict = 'PASS'
            return
        
        # If X-STEP prompt is ready for new command, then return
        # and continue execution
        if (resp.find('X-STEP:') != -1):
            return


# Initialize ssh-connection.
def sshInit():
    global ssh_client
    global ssh_channel
    print ('\n###Siemens start ssh!!!')
    ssh_client = paramiko.SSHClient()
    ssh_client.load_system_host_keys()
    ssh_client.set_missing_host_key_policy(paramiko.WarningPolicy())
    ssh_client.connect(XSTEP, username=user, password=passwd)
    print ('\n###Siemens ssh Init done!!!')
    
    # Invoke an interactive shell
    ssh_channel = ssh_client.invoke_shell()
    time.sleep(1)

# Test case specific commands and variables
verdict          = 'NOT_EXECUTED'     # initial verdict
warnings         = []                # append all warnings to this table
errors           = []                # append all errors to this table
testCaseCommands = []                # append all API CALLs to this table


def initTestCase():
    # This test case run JESD204C_1Lane_1250Mbps_Tx_Rx on slave mode.
    # Below test hits are compiled into the JESD204C_1Lane_1250Mbps_Tx_Rx and they are run one after another from the testCaseCommands list.
    testCaseCommands.append('x.testcase.runhit JESD204C_Test_Case_Settings\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_Program_Device\n')
    testCaseCommands.append('x.testcase.runhit COMMON_Ext_Ref_Clock_Usage\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_TX_Copy_Input_Files\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_TX_Initialize_and_Mode_Definition\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_TX_Generate_Stimulus\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_TX_Start\n')
    #testCaseCommands.append('x.testcase.runhit JESD204C_TX_Poll_State\n')
    #testCaseCommands.append('x.exit\n')

def initTestCase_2():
    # This test case run JESD204C_1Lane_1250Mbps_Tx_Rx on slave mode.
    # Below test hits are compiled into the JESD204C_1Lane_1250Mbps_Tx_Rx and they are run one after another from the testCaseCommands list. 
    #test_case = ""
    testCaseCommands.clear()
    #testCaseCommands.append('x.testcase.runhit JESD204C_TX_Generate_Stimulus\n')
    #testCaseCommands.append('x.testcase.runhit JESD204C_TX_Start\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_Test_Case_Settings\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_Program_Device\n')
    testCaseCommands.append('x.testcase.runhit COMMON_Ext_Ref_Clock_Usage\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Copy_Input_Files\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Initialize_and_Trigger_Definition\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Reserve_Capture_Segment\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Check_Receiver_Sync\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Start\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Wait_For_Trigger_and_Capture\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Analyze_Capture\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Stop\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Print_Results_Vector\n')
    testCaseCommands.append('x.testcase.runhit JESD204C_RX_Copy_Output_Files\n')
    testCaseCommands.append('x.time.sleep 2 \n')
    testCaseCommands.append('x.exit\n')


def testLogic():
    # Constuct a command, that will launch the test case in slave mode
    # - add xstep_base_libs to LD_LIBRARY_PATH
    # - cd to xstep_base_work
    # - launch the test case
    # - ALWAYS add newline '\n' character at the end of the command, when using
    #   paramiko's send-method. Otherwise the command won't get executed in interpreter
    print ('\n#########Siemens starting API List-1!!!')
    cmd_to_send  = 'export LD_LIBRARY_PATH=' + xstep_base_libs + ';'
    cmd_to_send += 'cd ' + xstep_base_work + ';'
    global test_case
    cmd_to_send += test_case + '\n'
    ssh_channel.send(cmd_to_send)
    time.sleep(3)
    
    # Check that we actually did succesfully invoke the test case
    resp = ssh_channel.recv(9999).decode('utf-8')
    print (resp, end='')
    
    if (resp.find('X-STEP') == -1):
        print ('\nERROR: Could not start test case!!!')
        sys.exit(1)

    # ----------------------------------------------
    # Now that test case is running, start interacting
    # with X-STEP interpreter
    global verdict
    verdict = 'RUNNING'
    
    # Loop through each API command listed in testCaseCommands table.
    # With response_to_wait -variable we tell to the waitForMsgs()- function, what
    # is the API call whose return value we wan't to check
    for cmd in testCaseCommands:
        ssh_channel.send(cmd)
        response_to_wait = '#' + cmd.split(' ')[0]
        time.sleep(1)
        waitForMsgs(response_to_wait)
        print(' ----------------------------------------------------------------------- ')
    # ----------------------------------------------
    print ('\n#########Siemens API List-1 done!!!')
	


def testLogic_2():
    # Constuct a command, that will launch the test case in slave mode
    # - add xstep_base_libs to LD_LIBRARY_PATH
    # - cd to xstep_base_work
    # - launch the test case
    # - ALWAYS add newline '\n' character at the end of the command, when using
    #   paramiko's send-method. Otherwise the command won't get executed in interpreter
    #cmd_to_send  = 'export LD_LIBRARY_PATH=' + xstep_base_libs + ';'
    #cmd_to_send += 'cd ' + xstep_base_work + ';'
    print ('\n###Siemens starting API List-2 !!!')
    cmd_to_send = ""
    cmd_to_send += test_case + '\n'
    ssh_channel.send(cmd_to_send)
    time.sleep(3)
    
    # Check that we actually did succesfully invoke the test case
    resp = ssh_channel.recv(9999).decode('utf-8')
    print (resp, end='')
    
    if (resp.find('X-STEP') == -1):
        print ('\nERROR: Could not start test case!!!')
        sys.exit(1)

    # ----------------------------------------------
    # Now that test case is running, start interacting
    # with X-STEP interpreter
    global verdict
    verdict = 'RUNNING'
    
    # Loop through each API command listed in testCaseCommands table.
    # With response_to_wait -variable we tell to the waitForMsgs()- function, what
    # is the API call whose return value we wan't to check
    for cmd in testCaseCommands:
        ssh_channel.send(cmd)
        response_to_wait = '#' + cmd.split(' ')[0]
        time.sleep(1)
        waitForMsgs(response_to_wait)
        print(' ----------------------------------------------------------------------- ')
    # ----------------------------------------------
    print ('\n###Siemens API List-2 done !!!')

'''
def copyGuiToXStep():
	# Copy all files needed to xstep
    sftp = ssh_client.open_sftp()
    sftp.put("xstep_files/JESD204C_2Lane_1250Mbps_Rx", "/root/XStep/work/JESD204C_2Lane_1250Mbps_Rx")
    sftp.put("xstep_files/jesd204c_setup_1G25_1lane_ABC_usecase_3b_28_12_23.txt", "/root/XStep/work/JESD204C/jesd204c_setup_1G25_1lane_ABC_usecase_3b_28_12_23.txt")
'''

#Modified by Aditya for binary picking

def copyGuiToXStep():
	# Copy all files needed to xstep
    sftp = ssh_client.open_sftp()
    #sftp.put("/xstep_files/UC_5C/UC_5C_TX/JESD204C_4Lane_1250Mbps_Rx", "/root/XStep/work/JESD204C_4Lane_1250Mbps_Rx")
    global path
    global binary
    sftp.put( path, "/root/XStep/work/" + binary)

    #sftp.put( path, "/root/XStep/work/" + binary)
    #sftp.put("xstep_files/JESD204C_4Lane_1250Mbps_Rx", "/root/XStep/work/JESD204C_4Lane_1250Mbps_Rx")
    print('@@@@@@@@Copy Done@@@@@@@@')

    
    
#test_case       = './JESD204C_2Lane_1250Mbps_Rx mode=slave'

#Modified by Aditya for binary picking
#test_case       = './' + binary + ' mode=slave'

def copyFilesToXStep():
	# Copy all files needed by setup file to xstep
    sftp = ssh_client.open_sftp()
    sftp.put("xstep_files/payloads/payload0.txt", "/root/XStep/work/JESD204C/payload0.txt")
    sftp.put("xstep_files/payloads/payload1.txt", "/root/XStep/work/JESD204C/payload1.txt")
    sftp.put("xstep_files/payloads/payload2.txt", "/root/XStep/work/JESD204C/payload2.txt")
    sftp.put("xstep_files/payloads/payload3.txt", "/root/XStep/work/JESD204C/payload3.txt")
    sftp.put("xstep_files/payloads/payload4.txt", "/root/XStep/work/JESD204C/payload4.txt")
    sftp.put("xstep_files/payloads/payload5.txt", "/root/XStep/work/JESD204C/payload5.txt")
    sftp.put("xstep_files/payloads/payload6.txt", "/root/XStep/work/JESD204C/payload6.txt")
    sftp.put("xstep_files/payloads/payload7.txt", "/root/XStep/work/JESD204C/payload7.txt")
    sftp.put("xstep_files/payloads/payload8.txt", "/root/XStep/work/JESD204C/payload8.txt")
    sftp.put("xstep_files/payloads/payload9.txt", "/root/XStep/work/JESD204C/payload9.txt")
    sftp.put("xstep_files/payloads/payload10.txt", "/root/XStep/work/JESD204C/payload10.txt")
    sftp.put("xstep_files/payloads/payload11.txt", "/root/XStep/work/JESD204C/payload11.txt")
    sftp.put("xstep_files/payloads/payload12.txt", "/root/XStep/work/JESD204C/payload12.txt")
    sftp.put("xstep_files/payloads/payload13.txt", "/root/XStep/work/JESD204C/payload13.txt")
    sftp.put("xstep_files/payloads/payload14.txt", "/root/XStep/work/JESD204C/payload14.txt")
    sftp.put("xstep_files/payloads/payload15.txt", "/root/XStep/work/JESD204C/payload15.txt")
    #sftp.put("xstep_files/jesd204c_setup_1G25_1lane_ABC_usecase_1a_15_05_23.txt", "/root/XStep/work/JESD204C/jesd204c_setup_1G25_1lane_ABC_usecase_1a_15_05_23.txt")
    #sftp.put("xstep_files/JESD204C_4Lane_1250Mbps_Tx_Rx", "/root/XStep/work/JESD204C_4Lane_1250Mbps_Tx_Rx")
    #sftp.put("a_setup_link0.txt", "/root/XStep/work/...")
    #sftp.put("example_iq_data_lte10m_HEX_16_IQ.txt", "/root/XStep/work/...")
    print ('\n#########roshan file copied from netbatch to xstep')
    sftp.close()

def copyFilesFromXStep():
    sftp = ssh_client.open_sftp()
    sftp.get("/root/XStep/work/JESD204C/savepayload0.txt","xstep_files/savepayloads/savepayload0.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload1.txt","xstep_files/savepayloads/savepayload1.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload2.txt","xstep_files/savepayloads/savepayload2.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload3.txt","xstep_files/savepayloads/savepayload3.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload4.txt","xstep_files/savepayloads/savepayload4.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload5.txt","xstep_files/savepayloads/savepayload5.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload6.txt","xstep_files/savepayloads/savepayload6.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload7.txt","xstep_files/savepayloads/savepayload7.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload8.txt","xstep_files/savepayloads/savepayload8.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload9.txt","xstep_files/savepayloads/savepayload9.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload10.txt","xstep_files/savepayloads/savepayload10.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload11.txt","xstep_files/savepayloads/savepayload11.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload12.txt","xstep_files/savepayloads/savepayload12.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload13.txt","xstep_files/savepayloads/savepayload13.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload14.txt","xstep_files/savepayloads/savepayload14.txt")
    sftp.get("/root/XStep/work/JESD204C/savepayload15.txt","xstep_files/savepayloads/savepayload15.txt")
#    sftp.get("/root/XStep/work/...", "<file1.txt>")
#    sftp.get("/root/XStep/work/...", "<file1.txt>")
    print ('\n#########roshan file copied from xstep to netbatch')
    sftp.close()

def postActions():
    # Close the ssh-connection
    ssh_channel.close()
    
    # Do other post actions, print results, warnings, errors etc...
    print ('\n###################################')
    print ('VERDICT -->', verdict)
    print ('\nERRORS')
    for error in errors:
        print ('---' + error)
    print('\nWARNINGS')
    for warning in warnings:
        print ('---' + warning)
    print ('###################################')

def tx_path_dnrt():
    print('\nStarting XSTEP Rx')
    sshInit()
    copyGuiToXStep()
    initTestCase_2()
    testLogic()
    copyFilesFromXStep()
    postActions()
    print('\nXSTEP Rx Done\n')


def main():
    print('\nHello from roshan, running xstep slave mode test')
    print('\n XSTEP is ', XSTEP)
    sshInit()
#    copyFilesToXStep()
    initTestCase()
    testLogic()
    print('\nHello from roshan, test ran till xstep init\n\n\n\n') 
    time.sleep(2)
    print('\nHello from roshan, runnig rest of xstep tests')
    time.sleep(2)
    initTestCase_2()
    testLogic_2()
    time.sleep(2)
#    copyFilesFromXStep()
    postActions() 
    



#Added by Aditya for binary picking

def main2():
    print('\nHello from Aditya, running xstep slave mode test')
    print('\n XSTEP is ', XSTEP)
    print('\nStarting XSTEP Rx')
    sshInit()
    copyGuiToXStep()

if __name__ == '__main__':
    main()
    #main2()    #Modified by Aditya for binary picking
    