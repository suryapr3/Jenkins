This script will take 4 arguments and script should be run in below format

python3 pd_main_pd_extra_no_data_start.py <v2d_id> <apb_id> <drf_clock> <test_config>

v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
drf_clock can be with in the range [0,1]
test_config can be with in the range [0,16]

ex: python3 pd_main_pd_extra_no_data_start.py 0 0 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R1.0_ww12

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate pd_main_pd_extra_no_data_start_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 pd_main_pd_extra_no_data_start_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the pd_main_pd_extra_no_data_start_list.xlsx file.
