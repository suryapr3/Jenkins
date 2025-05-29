/*************************************************
*                                                *
*    VHA interrupt test (FORCE) with RCS         *
*                                                *
* Author : Haridas P                             *
* Date   : July 4, 2024                          *
*                                                *
*************************************************/

This test is to validate various VHA interrupts within the VHA module. The test will write into the
INTERRUPT FORCE registers of the VHA and their occurrence is handled in a selected RCS core (LX7).
Also the status of the VHA is read out from the appropriate STATUS registers.

How to run the test ?
	From the FRIO bash terminal
		python interrupt_force_test_with_rcs.py <rcs_core> <vha_num> <irq_type>
			rcs_core : this is the RCS core which will get used in the test
					0: AX, 1: RX, 2: TX
			vha_num  : one out of the VHA instatnce
			irq_type : LOW or HIGH interrupt (0: LOW, 1: HIGH)

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.

