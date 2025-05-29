Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the corresponding .so file)

Available Compilation Flags

Compilation Flag        Description                                     Default Value
------------------      --------------------------------------------    ----------------
EXTRA_UNDERRUN_ENABLE   To enable extra underrun interrupt in place of    0
                        underrun.

ex: gmake clean; gmake EXTRA_UNDERRUN_ENABLE=1

Steps to run individual TC:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 2 arguments and script should be run in below format

python3 tx_alarm.py <v2d_id> <apb_id>

v2d_id can be with in the range [0,3]
drf_clock can be with in the range [0,2]

ex: python3 tx_alarm.py 0 0

Note: This information is for the FPGA model ABC 18A 0p8b R0.2

Steps to create regression excel list (one time):
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 regression_list_generation.py

The above will generate tx_alarm_list.xlsx file , needs to be done only if the xlsx file is not present or there were any changes done
in the regression_list_generation.py file..

Steps to run regression:
-------------------------------------------------------------------------------------------------------------------------------------------------------
python3 tx_alarm_regression.py

The above will run all the possible combination which was mentioned at the first step.
The input combinations will be taken from the tx_alarm_list.xlsx file.
