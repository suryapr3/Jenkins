Steps to create executables:
------------------------------------------------------------------------------------------------------------------------------------------------------
1. gmake clean; gmake (create the vex binary and corresponding .so file)

Steps to run individual TC to stop the capture based on sample count:
-------------------------------------------------------------------------------------------------------------------------------------------------------
This script will take 1 argument and script should be run in below format

python3 connectivity.py <drf_clock>

drf_clock can be with in the range [0,1] 0 - 983MHz and 1 - 1.47GHz

ex: python3 connectivity.py 0

This script will iterate for all possible VEX - V2D pairs for all the 4 ports of V2D.

Note: This information is for the FPGA model ABC_18A_0p5_R1.0
