Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. Go to vex_fw folder.
2. make clean sim_m64 NO_SIM=1(vex_fw executables)
3. cd -
4. gmake clean; gmake (create the .so file)

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 6 arguments and script should be run in below format

python3 flow3_coeff_axi_mode1.py <tx_vex_id> <rx_vex_id> <v2d_id> <apb_id> <drf_clock> <test_config>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
drf_clock should be 0
test_config can be with in the range [0,16]

ex: python3 flow3_coeff_axi_mode1.py 0 1 0 0 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R0.11


Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow3_coeff_axi_mode1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_coeff_axi_mode1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_coeff_axi_mode1_list.xlsx file.

