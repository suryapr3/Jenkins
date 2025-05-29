This script will take 2 arguments and script should be run in below format

python3 bfn_test.py <v2d_id> <drf_clock>

v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0,1]

ex: python3 bfn_test.py 0 0

Note: This information is for the FPGA model ABC_18A_0p6_R1.0_ww12

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate bfn_test_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 bfn_test_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the bfn_test_list.xlsx file.
