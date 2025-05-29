-------------------------------------------------------------------------------------------------------------------------------------------------------
1. Go to vex_fw folder.
2. make clean sim_m64 NO_SIM=1(vex_fw executables)
3. cd -
4. gmake clean; gmake (create the .so file)

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 9 arguments and script should be run in below format

python3 flow3_2Tx_2Rx.py <tx0_vex_id> <rx0_vex_id> <tx1_vex_id> <rx1_vex_id> <v2d_id> <apb_id> <split_method> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 24, 25, 32, 33, 34, 35, 36, 37, 38, 39]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
split_method can be with in the range [0,1]  ; 0 - EQUAL_SPLIT , 1 - UNEQUAL_SPLIT
drf_clock should be in the range [0,1]; 0 - 983MHz, 1 - 1.5GHz

# Remaining test_configs will pass for equal split. test_config=0 will fail for both splits.
test_config = [2, 3, 4, 6, 8, 9, 12, 14, 15]

Note: tx0_vex_id , tx1_vex_id can not be same

ex: python3 flow3_2Tx_2Rx.py 0 1 8 9 0 0 0 0 4

Note: This information is for the FPGA model ABC_18A_0p5_R1.1

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow3_2Tx_2Rx_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_2Tx_2Rx_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_2Tx_2Rx_list.xlsx file.
