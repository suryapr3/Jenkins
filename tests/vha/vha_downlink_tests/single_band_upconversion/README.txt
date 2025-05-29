/*************************************************
*                                                *
*           Single band upconversion             *
*                                                *
* Author : Haridas P                             *
* Date   : July 20, 2023                         *
*                                                *
*************************************************/

This test case aims to validate the data path of the VHA without involving the MODULATOR in the downlink
direction. The IQ samples for a single band will be fed to the VHA from any of the VEX cores. The VHA will
be configured to work ONLY as a digital up-converter by bypassing the MODULATOR module. The test will cover
validation of the entire filter chain in all possible combinations (4 cascaded interpolation filters).


How to run the test ?
	From the FRIO bash terminal
	python single_band_upconversion.py <tx_vex> <rx_vex> <vha_num> <port_num> <in_rate> <out_rate> <duc mode> <dl_clk>

	@input arguments
		tx_vex   : This is the VEX core who'll stream samples to the VHA instance.
		rx_vex   : This is the VEX core who'll recieve VHA processed samples.
		vha_num  : This is the VHA who'll process the samples from tx_vex and stream to rx_vex.
		port_num : This can be either 0 or 1 (VHA antenna 0 or 1).
		in_rate  : This is the input rate of the VHA.
		out_rate : This is the rate at which the VHA will output to rx_vex.
		duc mode : This is the mode of operation of the DUC (0: AUTO or 1: MANUAL)
		dl_clk   : This is the downlink clock selection (0: 983.04MHz, 1: 1.47GHz)

How to check the output ?
	Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.
	Additionally, the same can be confirmed from the log file generated from the serial console.


Notes:-
	1. Care should be given in passing the vex arguments. NOT all combinations of the tx_vex and
	rx_vex are allowed as per ABC NoC routing for a VHA instance.
	Refer below file for more details on the available routing between VEX and VHA.
	file:///nfs/site/disks/xne_abc78.arc.transaction.000/arc_trans/xip_abc_noc_vexarray/1682508877.sccp305504.16455.00000/ABCA0_ZSC14_VER_004/reference_manual/chapter3.html#routes
	2. Following is the list of a valid VEX cores connected to each of the VHA instances.
		vha0_ve_list = [ 0 1 8 9 16 17 24 25 32 33 ]
		vha1_ve_list = [ 2 3 10 11 18 19 26 27 34 35 ]
		vha2_ve_list = [ 4 5 12 13 20 21 28 29 36 37 ]
		vha3_ve_list = [ 6 7 14 15 22 23 30 31 38 39 ]
		vha4_ve_list = [ 0 1 8 9 16 17 24 25 32 33 ]
		vha5_ve_list = [ 2 3 10 11 18 19 26 27 34 35 ]
		vha6_ve_list = [ 4 5 12 13 20 21 28 29 36 37 ]
		vha7_ve_list = [ 6 7 14 15 22 23 30 31 38 39 ]
	3. Only VHA0-3 are available on FRIO builds.
