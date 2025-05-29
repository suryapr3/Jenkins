# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Lovekesh Gupta
# Created Date: January 1 2023
# =============================================================================
# Main Regression script for ABC emul Validation ..."""
# =============================================================================
# Import statements
# =============================================================================
import sys
import os
import time
import subprocess
import logging
import csv

valid_vex_list = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 10, 11, 12, 13, 14, 15, 32, 34, 36, 38]
invalid_vex_list = [16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 33, 35, 37, 39]
invalid_v2d_list = [4, 5, 6, 7]
v2d_skip_cycle_blocks = [70, 140, 270, 540, 1070, 270, 540, 540, 1070, 1070, 1070, 270, 540, 540, 1070, 1070, 1070]
v2d_num_captures_list = [210, 114, 60, 30, 16, 60, 30, 30, 16, 16, 16, 60, 30, 30, 16, 16, 16]

class ABC_V2D():

    def __init__(self):

         self.testinput = None
    ###########################################################################################
    #     Function name   :- vex id validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of vex_num
    #
    #
    ###########################################################################################
    def vex_check(self, vex_num, v2d_num):
        for invalid_vex in invalid_vex_list:
            if (vex_num == invalid_vex):
                print("provided vex_num is not valid for this fpga\n")
                sys.exit("proper input parameters were not provided\n")
        if (v2d_num == 0) and not ((vex_num % 8 == 0) or (vex_num % 8 == 1)):
            print("provided inputs doesn't match with the NOC connections\n")
            sys.exit("proper input parameters were not provided\n")
        elif (v2d_num == 1) and not ((vex_num % 8 == 2) or (vex_num % 8 == 3)):
            print("provided inputs doesn't match with the NOC connections\n")
            sys.exit("proper input parameters were not provided\n")
        elif (v2d_num == 2) and not ((vex_num % 8 == 4) or (vex_num % 8 == 5)):
            print("provided inputs doesn't match with the NOC connections\n")
            sys.exit("proper input parameters were not provided\n")
        elif (v2d_num == 3) and not ((vex_num % 8 == 6) or (vex_num % 8 == 7)):
            print("provided inputs doesn't match with the NOC connections\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- v2d_num validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of v2d_num
    #
    #
    ###########################################################################################
    def v2d_check(self, v2d_num):
        for invalid_v2d in invalid_v2d_list:
            if (v2d_num == invalid_v2d):
                print("provided v2d_num is not valid for this fpga\n")
                sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- v2d_num validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of v2d_num
    #
    #
    ###########################################################################################
    def v2d_bfn_trigger_check(self, v2d_num):
        for invalid_v2d in invalid_v2d_list:
            if (v2d_num == invalid_v2d) or (v2d_num % 2 == 1):
                print("provided v2d_num is not valid for this fpga and it should be even number only\n")
                print("v2d param valid list is [0,3]")
                sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- apb_num validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of apb_num
    #
    #
    ###########################################################################################
    def apb_id_check(self, apb_id):
        if (apb_id < 0 or apb_id > 1):
            print("provided apb_num is not with in the range,apb_num should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- split_method validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of split_method
    #
    #
    ###########################################################################################
    def split_method_check(self, split_method):
        if (split_method < 0 or split_method > 1):
            print("provided split_method is not with in the range,split_method should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- sys_rate validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of sys_rate
    #
    #
    ###########################################################################################
    def sys_rate_check(self, drf_clock, sys_rate):
        if (drf_clock < 0 or drf_clock > 1):
            print("provided drf_clock is not with in the range,drf_clock should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

        if (sys_rate < 0) or (sys_rate > 11 and sys_rate < 21) or (sys_rate > 28):
            print("provided sys_rate is not within the range , sys_rate should be [0,11] and [21,28]\n")
            sys.exit("proper input parameters were not provided\n")

        if ((drf_clock == 0) and (sys_rate == 11 or sys_rate == 27 or sys_rate == 28)):
            print("sys_rate 12IQ(11) or SYS_RATE R_18(27) or SYS_RATE R_24(28) is not supported for drf_clock of 983M")
            sys.exit("proper input parameters were not provided\n")

        if ((drf_clock == 1) and (sys_rate == 21 or sys_rate == 22 or sys_rate == 24 or sys_rate == 26)):
            print("sys_rate R_3(21) or SYS_RATE R_4(22) or SYS_RATE R_8(24) or SYS_RATE_R_16(26) is not supported for drf_clock of 1.47G")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- test_config validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of test_config
    #
    #
    ###########################################################################################
    def test_config_check(self, test_config):
        if (test_config < 0 or test_config > 16):
            print("provided test_config is not within the range , test_config should be [0,16]\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- test_config validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of test_config
    #
    #
    ###########################################################################################
    def sram_test_config_check(self, test_config):
        if (test_config < 0 or test_config > 4):
            print("provided test_config is not within the range , test_config should be [0,4]\n")
            sys.exit("proper input parameters were not provided\n")


    ###########################################################################################
    #     Function name   :- drf_clock validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of drf_clock
    #
    #
    ###########################################################################################
    def drf_clock_check(self, drf_clock):
        if (drf_clock < 0 or drf_clock > 1):
            print("provided drf_clock is not with in the range,drf_clock should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- drf_clock validity check for sram cases
    #     Input parameter :-
    #     Description     :- This function will check validity of drf_clock
    #
    #
    ###########################################################################################
    def sram_drf_clock_check(self, drf_clock):
        if (drf_clock != 0):
            print("provided drf_clock is not with in the range,drf_clock should be 0 \n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- filter_mode validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of filter_mode
    #
    #
    ###########################################################################################
    def filter_mode_check(self, filter_mode):
        if (filter_mode< 0 or filter_mode> 1):
            print("provided filter_mode is not with in the range,filter_mode should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- quad instance validity check
    #     Input parameter :-
    #     Description     :- This function will check validity of filter_mode
    #
    #
    ###########################################################################################
    def quad_instance_check(self, quad_instance):
        if (quad_instance < 0 or quad_instance > 1):
            print("provided quad_instance is not with in the range,quad_instance should be 0 or 1\n")
            sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- capture delay value check
    #     Input parameter :-
    #     Description     :- This function will check validity of delay value
    #
    #
    ###########################################################################################
    def capture_delay_value_check(self, drf_clock, capture_delay_value):
        if (0 == drf_clock):
            if (capture_delay_value % 512):
                print("capture delay value should be multiples of 512 clocks for 983MHz clock")
                sys.exit("proper input parameters were not provided\n")

        if (1 == drf_clock):
            if (capture_delay_value % 768):
                print("capture delay value should be multiples of 768 clocks for 1.474GHz clock")
                sys.exit("proper input parameters were not provided\n")

    ###########################################################################################
    #     Function name   :- get skip cycles
    #     Input parameter :-
    #     Description     :- This function will provide the skip cycles for the
    #                       given data rate
    #
    ###########################################################################################
    def get_skip_cycles(self, drf_clock, test_config):
        if (0 == drf_clock):
            return (512 * v2d_skip_cycle_blocks[test_config])
        if (1 == drf_clock):
            #Need to double the value when compared with 983M
            return (768 * (v2d_skip_cycle_blocks[test_config] * 2))

    ###########################################################################################
    #     Function name   :- get number of captures
    #     Input parameter :-
    #     Description     :- This function will provide the number of captures for the
    #                       given data rate
    #
    ###########################################################################################
    def get_num_captures(self, drf_clock, test_config):
        if (0 == drf_clock):
            return (v2d_num_captures_list[test_config])
        if (1 == drf_clock):
            return (int) (v2d_num_captures_list[test_config] / 2)


