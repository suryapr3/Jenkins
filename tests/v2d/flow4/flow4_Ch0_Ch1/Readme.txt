Steps to create executables:
-------------------------------------------------------------------------------------------------------------------------------------------------------
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
This script will take 8 arguments and script should be run in below format

python3 flow4_Ch0_Ch1.py <tx0_vex_id> <rx0_vex_id> <tx1_vex_id> <rx1_vex_id> <v2d_id> <drf_clock> <test_config> <post_filer_mode>

Below are the VEX ID's that were enabled in the model
Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0,1]
test_config can be with in the range [0,16]
post_filer_mode can be with in the range [0,1]

ex: python3 flow4_Ch0_Ch1.py 0 1 8 9 0 0 0 0

Note: This information is for the FPGA model ABC_18A_0p8_0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate flow4_Ch0_Ch1_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow4_Ch0_Ch1_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow4_Ch0_Ch1_list.xlsx file.
