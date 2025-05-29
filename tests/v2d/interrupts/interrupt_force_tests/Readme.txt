This script will take 2 arguments and script should be run in below format

python3 interrupt_force_tests.py <v2d_id> <apb_id> <rcs_cpre>

v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0,2]
rcs_core can be with in the range [0,3]

ex: python3 interrupt_force_tests.py 0 0 0

Note: This information is for the FPGA model ABC 18A 0p8 R0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate interrupt_force_tests_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 interrupt_force_test_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the interrupt_force_tests_list.xlsx file.
