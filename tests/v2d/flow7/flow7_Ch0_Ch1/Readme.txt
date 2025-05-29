This script will take 7 arguments and script should be run in below format

python3 flow7_Ch0_Ch1.py <tx0_vex_id> <rx0_vex_id> <tx1_vex_id> <rx1_vex_id> <v2d_id> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0]
test_config can be with in the range [0,16]

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

Note: none of the vex id's can be same.

ex: python3 flow7_Ch0_Ch1.py 0 1 8 9 0 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R1.0

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow7_Ch0_Ch1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow7_Ch0_Ch1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow7_Ch0_Ch1_list.xlsx file.
