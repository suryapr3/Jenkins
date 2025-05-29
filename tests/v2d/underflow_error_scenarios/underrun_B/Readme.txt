This script will take 4 arguments and script should be run in below format

python3 underrun_B.py <vex_id> <v2d_id> <apb_id> <pdpd_rate>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39]
vex_id can be with in the range [0,39]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
pdpd_rate can be with in the range [0,5]

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0 (1,8 and 9 are used in the Rx), 8(9,16,and 17 are used in Rx), 16 (17,24 and 25 are used in Rx)
        24 (24,32 and 33 are used in Rx)
1       2 (3,10 and 11 are used in the Rx)
2       4 (5,12 and 13 are used in the Rx)
3       6 (7,14 and 15 are used in the Rx)

ex: python3 underrun_B.py 0 0 0 0

Note: This information is for the FPGA model ABC_N5_0p5_R1.1

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate underrun_B_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 underrun_B_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the underrun_B_list.xlsx file.
