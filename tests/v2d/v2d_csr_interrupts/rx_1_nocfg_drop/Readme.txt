Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. Go to vex_fw folder.
2. make clean sim_m64 NO_SIM=1(vex_fw executables)
3. cd -
4. gmake clean; gmake (create the .so file)

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 6 arguments and script should be run in below format

python3 rx_1_nocfg_drop.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3] and should be even only
apb_id can be with in the range [0,1]
drf_clock should be 0
test_config can be with in the range [0, 16]

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

ex: python3 rx_1_nocfg_drop.py 0 1 0 0 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R1.0_ww12

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate rx_1_nocfg_drop_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done in the regression_list_generation.py file.


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 rx_1_nocfg_drop_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the rx_1_nocfg_drop_list.xlsx file.

