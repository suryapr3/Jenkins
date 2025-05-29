This producer_consumer_prog VEX FW program supports below two tests.

1) VEX chain data transfer tests where the first vex generates the test data and
   the last vex loops back the test data to the first vex which also checks the result.
   To run this test, please set the global variable first_vex_vex = 1 in the first vex core.

2) Common Module(CM) to VEX chain to Common Module(CM) data transfer test where
   the first vex receives data from CM and the last vex sends data to CM. 
   To run this test, please set first_cm_vex = 1 in the first vex core and 
   last_vex_cm = 1 in the last vex core.

NOTES:
By default, the tests will run forever but the desired number of blocks to run 
can also be set via producer_consumer_max_count variable.

The appropriate CIO2STRM/STRM2CIO and CM programming and flags setting need to be done by the host.
( Please see host.c for example test #1 settings )

The VEX FW is setup to transfer 4 test vectors per block( 1 vector = 1024 bits ).
It can be changed via #define NUM_VEC_IN_BLK and recompile the FW.
