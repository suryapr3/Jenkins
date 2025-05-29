/*************************************************
*                                                *
*           VHA interrupt test (FORCE)           *
*                                                *
* Author : Haridas P                             *
* Date   : March 11, 2024                        *
*                                                *
*************************************************/

This test is to validate various VHA interrupts within the VHA module. The test will write into the
INTERRUPT FORCE registers of the VHA and their occurrence is read out from the appropriate STATUS
registers.

How to run the test ?
	From the FRIO bash terminal
		python interrupt_force_test.py

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.

