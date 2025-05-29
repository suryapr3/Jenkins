# soft reset BFN
srpWrite 0x268c2c 0x8000
# remove soft reset
srpWrite 0x268c2c 0x0
# read BFN live count
srpRead 0x268c3c 2

# LCNT_INC - lower CNT increment with each clock
#srpWrite 0x268c14 0x1

# TEN_MS_CNT = 0x95FFFF for 1MHz clock, lower BFN counter resets to 0 when it reaches this val
# check if this reset happens
#srpWrite 0x268c18 0x95ffff

# INC_PRE_REG0: This value is used to preset/increment the lower BFN counter or 
# add to the upper BFN counter depending on the value of i_timer_cmd.
# timer_cmd =0x1 = preset -> bfn_lower_cnt and bfn_upper_cnt are preset to the value in the TIMER_INC_PRE register.
# what is the difference between preset and reset? timer_cmd = 1 and 3
#srpWrite 0x268c1c 0x0

# INC_PRE_REG1:
# what is difference between timere preset and reset command?
# preset : BFN counter will start from preset value?
# timer_cmd =5 =sync_adj is used used to preset bfn_lower_cnt to INC_PRE_REG0
#srpWrite 0x268c20 0x0

# CNT_ADJ_REG0 : bits 31:0 of upper BFN counter
# When the value of the upper BFN counter equals this value, 
# the Upper BFN counter is incremented by the value in TIMER_INC_PRE register.
#srpWrite 0x268c24 0x0

# CNT_ADJ_REG1 bits 39:32 of upper BFN counter
# Defalt val of 0x0 is ok
#srpWrite 0x268c28 0x0

# ICNTRL - load the values in above registers to internal registers of BFN, but do not trigger
# ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
#srpWrite 0x268c2c 0x32

# opps_val_timesync_ctrl
# sysref_en =1 , extsync_en=1, oneppsval =0x31
#srpWrite 0x268c30 0x30031

# timer trigger 0, after 10us
# The timer logic compares the lower 32 bits of the BFN counter with the contents of this register.
# 10000 cycles
srpWrite 0x268000 0x2710

# timer trigger 1, after 10us
srpWrite 0x268020 0x2710
# timer trigger 2, after 10us
srpWrite 0x268040 0x2710
# timer trigger 3, after 10us
srpWrite 0x268060 0x2710
# timer trigger 4, after 10us
srpWrite 0x268080 0x2710
# timer trigger 5, after 10us
srpWrite 0x2680A0 0x2710
# timer trigger 6, after 10us
srpWrite 0x2680C0 0x2710
# timer trigger 7, after 10us
srpWrite 0x2680E0 0x2710

# timer interval 0
# In continuous mode only, this register contains the BFN period that the timer re-trigger
srpWrite 0x268004 0x0

# grp0 GPIO inout: make as out
srpWrite 0x268210 0xFFFFFFFF

# gpio set mask - timer 0
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268008 0xF

# gpio set mask - timer 1
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268028 0xF0

# gpio set mask - timer 2
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268048 0xF00

# gpio set mask - timer 3
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268068 0xF000

# gpio set mask - timer 4
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268088 0xF0000

# gpio set mask - timer 5
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2680A8 0xF00000

# gpio set mask - timer 6
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2680C8 0xF000000

# gpio set mask - timer 7
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2680E8 0xF0000000

# gpio_val- timer0, The value to which the GPIO will be set
srpWrite 0x26800c 0x1

# gpio_val- timer1, The value to which the GPIO will be set
srpWrite 0x26802c 0x20

# gpio_val- timer2, The value to which the GPIO will be set
srpWrite 0x26804c 0x300

# gpio_val- timer3, The value to which the GPIO will be set
srpWrite 0x26806c 0x4000
# gpio_val- timer4, The value to which the GPIO will be set
srpWrite 0x26808c 0x50000

# gpio_val- timer5, The value to which the GPIO will be set
srpWrite 0x2680ac 0x600000
# gpio_val- timer6, The value to which the GPIO will be set
srpWrite 0x2680cc 0x7000000

# gpio_val- timer7, The value to which the GPIO will be set
srpWrite 0x2680ec 0x80000000

#timer_cfg0, one shot, enable
srpWrite 0x268010 0x1
#timer_cfg1, one shot, enable
srpWrite 0x268030 0x1
#timer_cfg2, one shot, enable
srpWrite 0x268050 0x1
#timer_cfg3, one shot, enable
srpWrite 0x268070 0x1
#timer_cfg4, one shot, enable
srpWrite 0x268090 0x1
#timer_cfg5, one shot, enable
srpWrite 0x2680B0 0x1
#timer_cfg6, one shot, enable
srpWrite 0x2680D0 0x1
#timer_cfg7, one shot, enable
srpWrite 0x2680F0 0x1

# ICNTRL -  trigger ISYNC, BFN should start
# isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
srpWrite 0x268c2c 0xB2

# read BFN live count
srpRead 0x268c3c 2

# read BFN live count
srpRead 0x268c3c 2

# read BFN live count
srpRead 0x268c3c 2

# timer status
srpRead 0x2680fc 1

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014

# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C

# read timer_cfg to clear status
srpRead 0x268010
srpRead 0x268030
srpRead 0x268050
srpRead 0x268070
srpRead 0x268090
srpRead 0x2680B0
srpRead 0x2680D0
srpRead 0x2680F0

# timer status
srpRead 0x2680fc 1



