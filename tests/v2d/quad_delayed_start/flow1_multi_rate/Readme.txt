Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
1. Go to vex_fw folder.
2. make clean sim_m64 NO_SIM=1(vex_fw executables)
3. cd -
4. gmake clean; gmake (create the .so file)

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 4 arguments and script should be run in below format

python3 flow1_multi_rate.py <quad_instance> <drf_clock> <sys_rate> <delay_value>

quad instance can be within the range [0,1]
drf_clock should be 0
sys_rate can be with in the range [0,11] and [21,26]

ex: python3 flow1_multi_rate.py 0 0 0 768

Note: This information is for the FPGA model ABC_18A_0p6_R0.11

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate flow1_multi_rate_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done in the regression_list_generation.py file.


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow1_multi_rate_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow1_multi_rate_list.xlsx file.

