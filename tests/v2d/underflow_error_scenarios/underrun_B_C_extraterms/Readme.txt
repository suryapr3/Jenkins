This script will take 5 arguments and script should be run in below format

python3 underrun_B_C_extraterms.py <vex_id1> <vex_id2> <v2d_id> <apb_id> <sys_rate>


Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
sys_rate can be with in the range [0,4]

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id1                                             vex_id2
0       0,8,16,24,32 (1,9,17,25,33 are used for Rx)         0,1,8,9,16,17,24,25,32,33
1       2,10,34 (3,11,35 are used for Rx)                   2,3,10,11,34,35
2       4,12,36 (5,13,37 are used for Rx)                   4,5,12,13,36,37
3       6,14,38 (7,15,39 are used for Rx)                   6,7,14,15,38,39

Note: vex_id1 , vex_id2 can not be same

ex: python3 underrun_B_C_extraterms.py 0 8 0 0 4

Note: This information is for the FPGA model ABC_N5_0p5_R1.1

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate underrun_B_C_extraterms_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 underrun_B_C_extraterms_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the underrun_B_C_extraterms_list.xlsx file.
