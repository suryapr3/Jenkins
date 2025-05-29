
Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex binary and corresponding .so file)
Available Compilation Flags

Compilation Flag        Description                                     Default Value
------------------      --------------------------------------------    ----------------
REGRESSION              Need to enable while running regressions.       0
                        to reduce time taken.
VEX_1P5G                To enable VEX Tx timer for 1.5G clock.          0

ex: gmake clean; gmake VEX_1P5G=1

Steps to run individual TC to stop the capture based on sample count:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 8 arguments and script should be run in below format

python3 quad_flow3_pdpd_ingress.py <quad_instance> <drf_clock> <test_config> <delay_value> <capture_delay_value> \
<delay_antenna_capture> <capture_blocks_per_antenna> <consecutive_captures_delay>

quad instance can be within the range [0,1]
drf_clock should be 0 or 1.
test_config should be with in the range [0,16]
delay_value should be 768 which is 1.5 blocks of cycles for optimal.
capture_delay_value is the delay to start the capture it should be multiples of 512 or 768 for 983M and 1.5G clock respectively.
delay_antenna_capture is the delay between antenna capture in a quad should be multiple of either 512 or 768 for 983M and 1.5G clock respectively.
capture_bocks_per_antenna can be any value, however if the value crossed total 1MB space then it will be limited to max value.
consecutive_captures_delay is the dleay between two consecutie quad captures should be multiple of either 512 or 768 for 983M and 1.5G clock respectively.

ex: python3 quad_flow3_pdpd_ingress_double.py 0 0 0 768 0 0 20 0

Note: This information is for the FPGA model ABC_18A_0p8_R0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate quad_flow3_pdpd_ingress_double_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file.


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 quad_flow3_pdpd_ingress_double_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the quad_flow3_pdpd_ingress_double_list.xlsx file.
