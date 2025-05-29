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
This script will take 9 arguments and script should be run in below format

python3 flow3_pdpd_ingress_continuous.py <tx_vex> <rx_vex> <v2d_num> <apb_num> <drf_clock> <test_config> <filter_mode> <delay_value> <capture_delay_value>

Below are the VEX ID's that were enabled in the model
[0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
v2d_id can be with in the range [0,3]
apb_id can be with in the range [0,1]
drf_clock can be with in the range [0,1]
test_config can be with in the range [0,16]
filter mode can be with in the range [0,1] ; 0 - PASSTHRU MODE and 1 - FILTER MODE
capture_delay_value should be multiple of 512

ex: python3 flow3_pdpd_ingress_continuous.py 0 1 0 0 0 0 0 768 0

There is a connection restriction between vex_id to v2d_id so below is the table shows the allowed combinations for given v2d_id for this specific TC

v2d_id  vex_id
0       0, 1, 8, 9, 32
1       2, 3, 10, 11, 34
2       4, 5, 12, 13, 36
3       6, 7, 14, 15, 38


Note: This information is for the FPGA model ABC_18A_0p8_R0.4

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py <drf_clock>

The above will generate flow3_pdpd_ingress_continuous_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file.


Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 flow3_pdpd_ingress_continuous_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the flow3_pdpd_ingress_continuous_list.xlsx file.
