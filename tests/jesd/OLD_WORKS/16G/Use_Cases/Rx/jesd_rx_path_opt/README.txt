/*************************************************
*                                                *
*           Single band demodulation             *
*                                                *
* Author :  Bhuvaneshwari M S          *
* Date   :  7th May 2024               *
*                                                *
*************************************************/
The optimized code enables user to select the testcase and run the JESD config.

The following is a sample jesd_tc_config array in jesd_rx_path_opt.c code.
//TC_1 - > arr[1]
    {TC_1, UC_3A, flow_rx_dnrt_to_vex, vex_0, jesd_0}

Once the testcase is selected the UC parameters are selected from the jesd_link_config array in jesd_rx_path_opt.c code.
    {UC_3a, sample_rate_122P88, l_1, m_8, f_16, s_1, n_tot_16, jesd_204c, serdes_rate_16P22016, e_1, soni_1, clk_ratio_1_1, smpl_trans_1_1},

How to run the test ?
	From the FRIO bash terminal
        Rx path : 
            Run the DNRT TX test with the setup file and payloads as per UC
            python jesd_rx_path_opt.py <testcase_num>

	@input arguments
		testcase   : This is the testcase selected to run JESD test
		
How to check the output ?
        Rx path : Vex memory is dumped the end of the test - Captured data is compared with the transmitted data from DNRT
	
        Upon completion of the test, PASS/FAIL status will be displayed in the bash terminal itself.


