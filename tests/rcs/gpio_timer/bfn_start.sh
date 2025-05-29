# soft reset BFN
srpWrite 0x268c2c 0x8000
# remove soft reset
srpWrite 0x268c2c 0x0
# read BFN live count
srpRead 0x268c3c 2

# LCNT_INC - lower CNT increment with each clock
# srpWrite 0x268c14 0x1

# TEN_MS_CNT = 0x95FFFF for 1MHz clock, lower BFN counter resets to 0 when it reaches this val
# check if this reset happens
# srpWrite 0x268c18 0x95ffff

# INC_PRE_REG0: This value is used to preset/increment the lower BFN counter or 
# add to the upper BFN counter depending on the value of i_timer_cmd.
# timer_cmd =0x1 = preset -> bfn_lower_cnt and bfn_upper_cnt are preset to the value in the TIMER_INC_PRE register.
# what is the difference between preset and reset? timer_cmd = 1 and 3
srpWrite 0x268c1c 0x20000

# INC_PRE_REG1:
# what is difference between timere preset and reset command?
# preset : BFN counter will start from preset value?
# timer_cmd =5 =sync_adj is used used to preset bfn_lower_cnt to INC_PRE_REG0
# srpWrite 0x268c20 0x0

# CNT_ADJ_REG0 : bits 31:0 of upper BFN counter
# When the value of the upper BFN counter equals this value, 
# the Upper BFN counter is incremented by the value in TIMER_INC_PRE register.
# srpWrite 0x268c24 0x0

# CNT_ADJ_REG1 bits 39:32 of upper BFN counter
# Defalt val of 0x0 is ok
# srpWrite 0x268c28 0x0

#srpWrite 0x268c2c 0x32

# ICNTRL - load the values in above registers to internal registers of BFN, but do not trigger
# ISYNC = 3 = timer_cmd , timer_cmd = 2 = init


# opps_val_timesync_ctrl
# sysref_en =1 , extsync_en=1, oneppsval =0x31
#srpWrite 0x268c30 0x30031

# ICNTRL -  trigger ISYNC, BFN should start
# isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
#srpWrite 0x268c2c 0xB1
# srpWrite 0x268c2c 0xB1

srpWrite 0x268c2c 0xB2

srpWrite 0x268c2c 0xB1

# read BFN live count
srpRead 0x268c3c 2

# read BFN live count
srpRead 0x268c3c 2
# read BFN live count
srpRead 0x268c3c 2

