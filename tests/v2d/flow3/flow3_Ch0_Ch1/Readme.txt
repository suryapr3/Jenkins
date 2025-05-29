Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex FW binary and .so file)

Available Compilation Flags
REGRESSION=1        -> while running regressions
VEX_1P5G=1          -> To generate the VEX Tx timer for every 768 clock cycles (needs to be enabled only
                       when VEX sub system is working at 1.5G clock).
VEX_1US_WINDOW=1    -> If we want to enable VEX processing granularity of 1US instead of 0.5us

ex: gmake clean; gmake REGRESSION=1

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 8 arguments and script should be run in below format

python3 flow3_Ch0_Ch1.py <tx0_vex_id> <rx0_vex_id> <tx1_vex_id> <rx1_vex_id> <v2d_id> <drf_clock> <test_config> <post_filer_mode>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0, 1]
test_config can be with in the range [0,16]
post_filer_mode can be with in the range [0,1]

ex: python3 flow3_Ch0_Ch1.py 0 1 8 9 0 0 0 0

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

Note: This information is for the FPGA model ABC_18A_0p5_R1.1

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate flow3_Ch0_Ch1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..

Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_Ch0_Ch1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_Ch0_Ch1_list.xlsx file.


#######################################################################################################################################################
Steps to run V2D All Channel live TC
#######################################################################################################################################################

Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex FW binary and .so file)

Available Compilation Flags
REGRESSION=1        -> while running regressions
VEX_1P5G=1          -> To generate the VEX Tx timer for every 768 clock cycles (needs to be enabled only
                       when VEX sub system is working at 1.5G clock).
VEX_1US_WINDOW=1    -> If we want to enable VEX processing granularity of 1US instead of 0.5us
V2D_ALL_TESTING=1   -> To make all V2D's and all channels running

ex: gmake clean; gmake REGRESSION=1

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 1 arguments and script should be run in below format

python3 flow3_ch0_ch1_v2d_all_test.py <drf_clock> <test_config>

drf_clock can be with in the range [0, 1]
test_config can be with in the range [0,16]

ex: python3 flow3_ch0_ch1_v2d_all_test.py 0 4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 v2d_all_regression_list_generation.py <drf_clock>

The above will generate flow3_Ch0_Ch1_v2d_all_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_Ch0_Ch1_v2d_all_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_Ch0_Ch1_list.xlsx file.

