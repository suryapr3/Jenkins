/*************************************************
*                                                *
*   VHA-VEX connectivity test                    *
*                                                *
* Author : Haridas P                             *
* Date   : July 20, 2023                         *
*                                                *
*************************************************/

This test is to validate the connectivities between various VHAs and VEXs.
A single VHA instance has two ports, which can be connected to a certain
combinations of VEXs.

How to run the test ?
	From the FRIO bash terminal
	python vha_vex_connectivity_test.py

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.


Notes:-
	1. Register dump is disabled by default to increase the time of execution during regression runs.
	   This can be enabled by a compile time argument REGISTER_DUMP. Please refere Makefile for an
	   example of the same.
