This script will take 8 arguments and script should be run in below format

python3 flow1_2Tx_1Rx.py <tx0_vex_id> <rx_vex_id> <tx1_vex_id> <v2d_id> <apb_id> <split_method> <drf_clock> <sys_rate>


Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
split_method can be with in the range [0,1]  0 : Equal split , 1: unequal split
drf_clock should be in the range [0,1]; 0 - 983MHz, 1 - 1.5GHz
sys_rate should be between [4,5,6,7,8,9,10,21,22,23,24,25,26,27] (greater than equal to 1GSPS)

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

Note: none of the vex_id should be duplicated

ex: python3 flow1_2Tx_1Rx.py 0 1 8 0 0 0 0 10

Note: This information is for the FPGA model ABC_18A_0p6_R1.0

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow1_2Tx_1Rx_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow1_2Tx_1Rx_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow1_2Tx_1Rx_list.xlsx file.

