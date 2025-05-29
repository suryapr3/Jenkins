/*************************************************
*                                                *
* NSIP interrupt test (H2B NOLKUP DROP ERROR)    *
*                                                *
* Author : Haridas P                             *
* Date   : April 05, 2024                        *
*                                                *
*************************************************/

This test is to generate an H2B NOLKUP DROP interrupt and then check the status of the same on the
status registers.

How to run the test ?
	From the FRIO bash terminal
		python nsip_h2b_nolkup_drop.py

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.
