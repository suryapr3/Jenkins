Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
gmake clean; gmake (create the VEX binary and .so file)

Available Compilation Flags:
===================================================================================================================
REGRESSION=1            -> while running regressions
VEX_1P5G=1              -> To generate the VEX Tx timer for every 768 clock cycles (needs to be enabled only
                           when VEX sub system is working at 1.5G clock).
FILL_LEVEL_TRIGGER=0    -> If we want to disable FILL_LEVEL_TRIGGER and use forced BFN Trigger.

ex: gmake clean; gmake REGRESSION=1


Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 6 arguments and script should be run in below format

python3 flow2_multi_rate.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
drf_clock should be 0
test_config can be with in the range [0,16]

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

ex: python3 flow2_multi_rate.py 0 1 0 0 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R1.0


Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow2_multi_rate_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow2_multi_rate_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow2_multi_rate_list.xlsx file.

