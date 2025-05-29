
Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 6 arguments and script should be run in below format

python3 buffer_full_cm1.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>


Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39]
tx_vex can be with in the range [0,2,4,6,8,12,14,16,24,32,34,36,38].
rx_vex can be with in the range [1,3,5,7,9,13,15,17,25,33,35,37,39].
v2d_num can be with in the range [0,3].
apb_num can be with in the range [0,1].
drf_clock can be [0].
test_config can be with in the range [0,16].

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  tx_vex          Rx_vex
0       0,8,16,24,32    1,9,17,25,33
1       2,10,34         3,11,35
2       4,12,36	  5,13,37
3       6,14,38 	  7,15,39

ex: python3 buffer_full_cm1.py 0 1 0 0 0 10

Note: This information is for the FPGA model ABC_18A_0p6_R1.0


Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate buffer_full_cm1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 buffer_full_cm1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the buffer_full_cm1_list.xlsx file.

