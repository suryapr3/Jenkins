To Create the executables

Go to vex_fw folder
make clean sim_m64 NO_SIM=1  (create VEX_FW executables)
cd -
gmake clean; gmake

To run the TC

This script will take 9 arguments and script should be run in below format

python3 flow6_2Tx_2Rx.py <tx0_vex_id> <rx0_vex_id> <tx1_vex_id> <rx1_vex_id> <v2d_id> <apb_id> <split_method> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
split_method can be with in the range [0,1]  ; 0 - EQUAL_SPLIT , 1 - UNEQUAL_SPLIT
drf_clock should be in the range [0,1]; 0 - 983MHz, 1 - 1.5GHz
test_config should be [0,16] 

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38

Note: none of the vex_id should be duplicated

ex: python3 flow6_2Tx_2Rx.py 0 1 8 9 0 0 0 0 4

Note: This information is for the FPGA model ABC_18A_0p6_R1.0

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow6_2Tx_2Rx_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow6_2Tx_2Rx_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow6_2Tx_2Rx_list.xlsx file.
