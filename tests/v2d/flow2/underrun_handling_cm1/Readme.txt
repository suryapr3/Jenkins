Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex binary and corresponding .so file)

Available Compilation Flags
==============================================================================================================
REGRESSION=1            -> while running regressions
FILL_LEVEL_TRIGGER=0   -> If we want to disable the fill level trigger and use force BFN trigger to start.

ex: gmake clean; gmake REGRESSION=1

Steps to run individual TC:
-----------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 6 arguments and script should be run in below format

python3 underrun_handling_cm1.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39]
tx_vex can be with in the range [0,2,4,6,8,12,14,16,24,32,34,36,38].
rx_vex can be with in the range [1,3,5,7,9,13,15,17,25,33,35,37,39].
v2d_num can be with in the range [0,3].
apb_num can be with in the range [0,1].
drf_clock can be [0].
test_config can be with in the range [0,16].

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

ex: python3 underrun_handling_cm1.py 0 1 0 0 0 10

Note: This information is for the FPGA model ABC_18A_0p6_R1.0


Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate underrun_handling_cm1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 underrun_handling_cm1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the underrun_handling_cm1_list.xlsx file.

