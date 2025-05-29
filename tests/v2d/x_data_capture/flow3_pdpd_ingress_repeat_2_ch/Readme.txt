
Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the .so file ,RCS elf and VEX FW binary files)

Available Compilation Flags

Compilation Flag        Description                                     Default Value
------------------      --------------------------------------------    ----------------
REGRESSION              Need to enable while running regressions.       0
                        to reduce time taken.
VEX_1P5G                To enable VEX Tx timer for 1.5G clock.          0

ex: gmake clean; gmake VEX_1P5G=1

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 5 arguments and script should be run in below format

python flow3_pdpd_ingress_repeat_2_ch.py <quad_instance> <channel0> <channel1> <drf_clock> <test_config>

quad instance can be within the range [0,1]
channel0 can be within the range [0,3]
channel1 can be within the range [0,3]
drf_clock should be 0
test_config should be with in the range [0,16]

channel0 and channel1 shouldn't be same.

ex: python3 flow3_pdpd_ingress_repeat_2_ch.py 0 0 1 0 0

Note: This information is for the FPGA model ABC_18A_0p8_R0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate flow3_pdpd_ingress_repeat_2_ch_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_pdpd_ingress_repeat_2_ch_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_pdpd_ingress_repeat_2_ch_list.xlsx file.
