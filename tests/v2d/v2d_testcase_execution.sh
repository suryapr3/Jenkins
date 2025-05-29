#!/bin/bash

# Call a test here.

test_case=1

#echo "executing connectivity test no $test_case"
#cd $PROJECT_HOME/tests/v2d/connectivity
#make clean
#make
#python3 connectivity.py

#echo "executing underrun_A test no $test_case"
#cd $PROJECT_HOME/tests/v2d/underflow_error_scenarios/underrun_A
#make clean
#make REGRESSION=1
#python3 underrun_A_regression.py

#((test_case++))
#echo "executing flow1_v2d_sram_multi_rate test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/flow1_v2d_sram_multi_rate
#make clean
#make REGRESSION=1
#python3 flow1_v2d_sram_regression.py

((test_case++))
echo "executing flow1_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow1/flow1_multi_rate
gmake clean;gmake REGRESSION=1
python3 regression_list_generation.py
python3 flow1_multi_rate_regression.py

((test_case++))
echo "executing flow1_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow1/flow1_fill_level
gmake clean;gmake REGRESSION=1
python3 regression_list_generation.py
python3 flow1_fill_level_regression.py

#((test_case++))
#echo "executing cm0_buffer_full test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/cm0_buffer_full
#make clean
#make REGRESSION=1
#python3 cm0_buffer_full_regression.py

#((test_case++))
#echo "executing cm0_underrun_handling test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/cm0_underrun_handling
#make clean
#make REGRESSION=1
#python3 cm0_underrun_handling_regression.py

#((test_case++))
#echo "executing flow1_2Tx_1Rx test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/flow1_2Tx_1Rx
#make clean
#make REGRESSION=1 RCS_TRIGGER=1
#python3 flow1_2Tx_1Rx_regression.py

#((test_case++))
#echo "executing flow1_2Tx_2Rx test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/flow1_2Tx_2Rx
#make clean
#make REGRESSION=1 RCS_TRIGGER=1
#python3 flow1_2Tx_2Rx_regression.py

#((test_case++))
#echo "executing flow1_Ch0_Ch1 test no $test_case"
#cd $PROJECT_HOME/tests/v2d/flow1/flow1_Ch0_Ch1
#make clean
#make REGRESSION=1 RCS_TRIGGER=1
#python3 flow1_Ch0_Ch1_regression.py

((test_case++))
echo "executing flow2_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_multi_rate
make clean;make REGRESSION=1 FILL_LEVEL_TRIGGER=1
python3 regression_list_generation.py
python3 flow2_multi_rate_regression.py

((test_case++))
echo "executing flow2_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_multi_rate
make clean;make REGRESSION=1 FILL_LEVEL_TRIGGER=0
python3 regression_list_generation.py
python3 flow2_multi_rate_regression.py

((test_case++))
echo "executing underrun_handling_cm1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/underrun_handling_cm1
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 underrun_handling_cm1_regression.py

((test_case++))
echo "executing flow3_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow3/flow3_multi_rate
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 flow3_multi_rate_regression.py

((test_case++))
echo "executing bfn_test test no $test_case"
cd $PROJECT_HOME/tests/v2d/bfn/bfn_test
make clean;make
python3 regression_list_generation.py
python3 bfn_test_regression.py

((test_case++))
echo "executing bfn_isync_test test no $test_case"
cd $PROJECT_HOME/tests/v2d/bfn/bfn_isync_test
make clean;make
python3 regression_list_generation.py
python3 bfn_isync_test_regression.py

((test_case++))
echo "executing v2d_all_sync test no $test_case"
cd $PROJECT_HOME/tests/v2d/bfn/v2d_all_sync
make clean;make
python3 v2d_all_sync.py

((test_case++))
echo "executing flow3_pdpd_ingress_capture test no $test_case"
cd $PROJECT_HOME/tests/v2d/x_data_capture/flow3_pdpd_ingress
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 flow3_pdpd_ingress_regression.py

((test_case++))
echo "executing flow3_pdpd_ingress_capture_duration test no $test_case"
cd $PROJECT_HOME/tests/v2d/x_data_capture/flow3_pdpd_ingress
make clean;make CAPTURE_DURATION=1 REGRESSION=1
python3 regression_list_generation_duration.py
python3 flow3_pdpd_ingress_duration_regression.py

((test_case++))
echo "executing flow3_pdpd_ingress_capture_repeat test no $test_case"
cd $PROJECT_HOME/tests/v2d/x_data_capture/flow3_pdpd_ingress_repeat
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 flow3_pdpd_ingress_repeat_regression.py

((test_case++))
echo "executing quad_flow3_pdpd_ingress_capture test no $test_case"
cd $PROJECT_HOME/tests/v2d/x_data_capture/quad_flow3_pdpd_ingress
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 quad_flow3_pdpd_ingress_regression.py

:'
((test_case++))
echo "executing quad_flow3_pdpd_ingress_capture_repeat test no $test_case"
cd $PROJECT_HOME/tests/v2d/x_data_capture/quad_flow3_pdpd_ingress_repeat
make clean;make REGRESSION=1
python3 regression_list_generation.py
python3 quad_flow3_pdpd_ingress_repeat_regression.py


((test_case++))
echo "executing flow2_v2d_sram_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_v2d_sram_multi_rate
make clean
make REGRESSION=1
python3 flow2_v2d_sram_regression.py


((test_case++))
echo "executing buffer_full_cm1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/buffer_full_cm1
make clean
make REGRESSION=1
python3 buffer_full_cm1_regression.py


((test_case++))
echo "executing flow2_coeff_vex test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_coeff_vex
make clean
make REGRESSION=1
python3 flow2_coeff_vex_regression.py

((test_case++))
echo "executing flow2_2Tx_1Rx test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_2Tx_1Rx
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow2_2Tx_1Rx_regression.py

((test_case++))
echo "executing flow2_Ch0_Ch1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_Ch0_Ch1
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow2_Ch0_Ch1_regression.py

((test_case++))
echo "executing flow2_2Tx_2Rx test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow2/flow2_2Tx_2Rx
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow2_2Tx_2Rx_regression.py

((test_case++))
echo "executing flow3_coeff_vex_mode1_mode2 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow3/flow3_coeff_vex_mode1_mode2
make clean
make REGRESSION=1
python3 flow3_coeff_vex_mode1_mode2_regression.py

((test_case++))
echo "executing flow3_2Tx_2Rx test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow3/flow3_2Tx_2Rx
make clean
make REGRESSION=1
python3 flow3_2Tx_2Rx_regression.py

((test_case++))
echo "executing flow3_Ch0_Ch1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow3/flow3_Ch0_Ch1
make clean
make REGRESSION=1
python3 flow3_Ch0_Ch1_regression.py

((test_case++))
echo "executing flow6_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_multi_rate
make clean
make REGRESSION=1
python3 flow6_multi_rate_regression.py

((test_case++))
echo "executing flow6_rx_drop_stream test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_rx_drop_stream
make clean
make REGRESSION=1
python3 flow6_rx_drop_stream_regression.py

((test_case++))
echo "executing flow6_mode1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_mode1
make clean
make REGRESSION=1
python3 flow6_mode1_regression.py

((test_case++))
echo "executing flow6_2Tx_2Rx test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_2Tx_2Rx
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow6_2Tx_2Rx_regression.py

((test_case++))
echo "executing flow6_2Tx_1Rx test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_2Tx_1Rx
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow6_2Tx_1Rx_regression.py

((test_case++))
echo "executing flow6_Ch0_Ch1 test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/flow6_Ch0_Ch1
make clean
make REGRESSION=1 RCS_TRIGGER=1
python3 flow6_Ch0_Ch1_regression.py

((test_case++))
echo "executing underrun_B_with_A test no $test_case"
cd $PROJECT_HOME/tests/v2d/underflow_error_scenarios/underrun_B_with_A
make clean
make REGRESSION=1
python3 underrun_B_with_A_regression.py

((test_case++))
echo "executing post processing test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow6/post_processing
make clean
make REGRESSION=1
python3 post_processing_regression.py

((test_case++))
echo "executing underrun_B_C_extraterms test no $test_case"
cd $PROJECT_HOME/tests/v2d/underflow_error_scenarios/underrun_B_C_extraterms
make clean
make REGRESSION=1
python3 underrun_B_C_extraterms_regression.py

((test_case++))
echo "executing underrun_B_extraterms test no $test_case"
cd $PROJECT_HOME/tests/v2d/underflow_error_scenarios/underrun_B_extraterms
make clean
make REGRESSION=1
python3 underrun_B_extraterms_regression.py

((test_case++))
echo "executing underrun_C_extraterms test no $test_case"
cd $PROJECT_HOME/tests/v2d/underflow_error_scenarios/underrun_C_extraterms
make clean
make REGRESSION=1
python3 underrun_C_extraterms_regression.py

((test_case++))
echo "executing flow4_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/flow4/flow4_multi_rate
make clean
make REGRESSION=1
python3 flow4_multi_rate_regression.py

((test_case++))
echo "executing ganging flow3_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/ganging/flow3_multi_rate
make clean
make REGRESSION=1
python3 flow3_multi_rate_regression.py

((test_case++))
echo "executing ganging flow4_multi_rate test no $test_case"
cd $PROJECT_HOME/tests/v2d/ganging/flow4_multi_rate
make clean
make REGRESSION=1
python3 flow4_multi_rate_regression.py

echo "completed $test_case test cases"
'
