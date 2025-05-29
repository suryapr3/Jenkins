/*************************************************
*                                                *
* VHA interrupt test (DL input fifo UNDERFLOW)   *
*                                                *
* Author : Haridas P                             *
* Date   : April 05, 2024                        *
*                                                *
*************************************************/

This test is to generate an UNDERFLOW interrupt in the input fifo of the downlink path of the
VHA antenna and then check the status of the same on the status registers.

How to run the test ?
	From the FRIO bash terminal
		python dl_input_fifo_underflow.py

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.

