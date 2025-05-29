# =============================================================================
#!/usr/bin/env python
# =============================================================================
# Created By  : Sai Manideep.K.V
# Created Date: June 28 2023
# =============================================================================
# test description : this test checks the V2D Buffer A Underflow status
# =============================================================================
# Import statements
# =============================================================================
import sys
import scripts as fw
import os
import subprocess
import logging
import datetime
from ctypes import *
import ctypes
from enum import Enum
import numpy as np


def getbinary(param):

    print('Param ID')
    print(param)
    param = param.rstrip()
    print(param)
    param = int(param)
    if param == 23:
        path = 'xstep_files/UC_5C/UC_5C_TX/JESD204C_4Lane_1250Mbps_Rx'
        print('UC5C in TX_Path')
        return path
        
    elif param == 21:
        path = 'xstep_files/UC_3A/UC_3A_TX/JESD204C_1Lane_1250Mbps_Rx'
        print('UC3A in TX Path')
        return path

    elif param == 25:
        path = 'xstep_files/UC_3B/UC_3B_TX/JESD204C_2Lane_1250Mbps_Rx'
        print('UC3B in TX Path')
        return path
        
    elif param == 26:
        path = 'xstep_files/UC_5E/UC_5E_TX/JESD204C_2Lane_1250Mbps_Rx'
        print('UC5E in TX Path')
        return path
        
    elif param == 29:
        path = 'xstep_files/UC_5B/UC_5B_TX/JESD204C_1Lane_1250Mbps_Rx'
        print('UC5B in TX Path')
        return path

    elif param == 35:
        path = 'xstep_files/UC_5C/UC_5C_TX/JESD204C_4Lane_1250Mbps_Rx'
        print('UC5C in Glue Loopback')
        return path
        
    elif param == 32:
        path = 'xstep_files/UC_9A/UC_9A_TX/JESD204C_1Lane_1250Mbps_Rx'
        print('UC9A in TX Path')
        return path
        
    elif param == 33:
        path = 'xstep_files/UC_7B/UC_7B_TX/JESD204C_1Lane_1250Mbps_Rx'
        print('UC7B in TX Path')
        return path

    else:
        print('Binary not specified')
