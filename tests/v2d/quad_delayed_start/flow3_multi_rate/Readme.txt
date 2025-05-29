Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex binary and corresponding .so file)

Available Compilation Flags

Compilation Flag        Description                                     Default Value
------------------      --------------------------------------------    ----------------
REGRESSION              Need to enable while running regressions.       0
                        to reduce time taken.
VEX_1P5G                To enable VEX Tx timer for 1.5G clock.          0
VEX_1US_WINDOW          To enable VEX Processing granularity of 1US     0
                        instead of 0.5us.

ex: gmake clean; gmake REGRESSION=1
Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 5 arguments and script should be run in below format

python3 flow3_multi_rate.py <quad_instance> <drf_clock> <test_config> <filter_mode> <delay_value>

quad instance can be within the range [0,1]
drf_clock should be 0 or 1.
test_config should be with in the range [0,16]
filter_mode should be with in the range [0,1]

ex: python3 flow3_multi_rate.py 0 0 0 0 768

Note: This information is for the FPGA model ABC_18A_0p8_R0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate flow3_multi_rate_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done in the regression_list_generation.py file.

Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_multi_rate_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_multi_rate_list.xlsx file.

