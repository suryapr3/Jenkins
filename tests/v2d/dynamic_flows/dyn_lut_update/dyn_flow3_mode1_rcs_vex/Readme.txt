
Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex binary and corresponding .so file)

Compilation Flag        Description                                     Default Value
------------------      --------------------------------------------    ----------------
REGRESSION              Need to enable while running regressions.       0
                        to reduce time taken.
VEX_1P5G                To enable VEX Tx timer for 1.5G clock.          0
VEX_1US_WINDOW          To enable VEX Processing granularity of 1US     0
                        instead of 0.5us.
Z0_USE_CASE             To enable the PDPD LUT to be 24 for lower       0
                        rates, specific to Z0.

ex: gmake clean; gmake REGRESSION=1

Steps to run individual TC to stop the capture based on sample count:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 7 arguments and script should be run in below format

python3 dyn_flow3_mode1_rcs_vex.py <tx_vex> <adapt_vex> <v2d_num> <apb_num> <drf_clock> <test_config> <delay_value>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
adapt_vex id should be in the list [32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
drf_clock can be with in the range [0,1]
test_config can be with in the range [0,16]

ex: python3 dyn_flow3_mode1_vex_vex.py 0 32 0 0 0 0 768

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38


Note: This information is for the FPGA model ABC_18A_0p6_R1.1

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate dyn_flow3_mode1_vex_vex_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 dyn_flow3_mode1_vex_vex_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the dyn_flow3_mode1_vex_vex_list.xlsx file.
