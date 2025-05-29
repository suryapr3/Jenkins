# soft reset BFN
srpWrite 0x268c2c 0x8000
# remove soft reset
srpWrite 0x268c2c 0x0
# read BFN live count
srpRead 0x268c3c 


# timer trigger 0, after 10us
# The timer logic compares the lower 32 bits of the BFN counter with the contents of this register.
# 10000 cycles
srpWrite 0x268400 0x2710
# timer trigger 1, after 10us
srpWrite 0x268420 0x2710
# timer trigger 2, after 10us
srpWrite 0x268440 0x2710
# timer trigger 3, after 10us
srpWrite 0x268460 0x2710
# timer trigger 4, after 10us
srpWrite 0x268480 0x2710
# timer trigger 5, after 10us
srpWrite 0x2684A0 0x2710
# timer trigger 6, after 10us
srpWrite 0x2684C0 0x2710
# timer trigger 7, after 10us
srpWrite 0x2684E0 0x2710

# timer interval 0
# In continuous mode only, this register contains the BFN period that the timer re-trigger
srpWrite 0x268404 0x0

# grp1 GPIO inout: make as out
srpWrite 0x268610 0xFFFFFFFF

# gpio_polarity
srpWrite 0x268608 0x0

# gpio set mask - timer 0
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268408 0xF

# gpio set mask - timer 1
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268428 0xF0

# gpio set mask - timer 2
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268448 0xF00

# gpio set mask - timer 3
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268468 0xF000

# gpio set mask - timer 4
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268488 0xF0000

# gpio set mask - timer 5
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2684A8 0xF00000

# gpio set mask - timer 6
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2684C8 0xF000000

# gpio set mask - timer 7
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2684E8 0xF0000000

# gpio_val- timer0, The value to which the GPIO will be set
srpWrite 0x26840c 0xaaaaaaaaa

# gpio_val- timer1, The value to which the GPIO will be set
srpWrite 0x26842c 0x50

# gpio_val- timer2, The value to which the GPIO will be set
srpWrite 0x26844c 0xa00

# gpio_val- timer3, The value to which the GPIO will be set
srpWrite 0x26846c 0x5000
# gpio_val- timer4, The value to which the GPIO will be set
srpWrite 0x26848c 0xa0000

# gpio_val- timer5, The value to which the GPIO will be set
srpWrite 0x2684ac 0x500000
# gpio_val- timer6, The value to which the GPIO will be set
srpWrite 0x2684cc 0xa000000

# gpio_val- timer7, The value to which the GPIO will be set
srpWrite 0x2684ec 0x50000000

#timer_cfg0, one shot, enable
srpWrite 0x268410 0x1
#timer_cfg1, one shot, enable
srpWrite 0x268430 0x1
#timer_cfg2, one shot, enable
srpWrite 0x268450 0x1
#timer_cfg3, one shot, enable
srpWrite 0x268470 0x1
#timer_cfg4, one shot, enable
srpWrite 0x268490 0x1
#timer_cfg5, one shot, enable
srpWrite 0x2684B0 0x1
#timer_cfg6, one shot, enable
srpWrite 0x2684D0 0x1
#timer_cfg7, one shot, enable
srpWrite 0x2684F0 0x1

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
srpRead 0x2684fc 1

# Read grp0 GPIO
# frioPciRead -F s6a1 -P 0x20014

# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C

# gpio_curr_out
srpRead 0x268614

# read timer_cfg to clear status
srpRead 0x268410
srpRead 0x268430
srpRead 0x268450
srpRead 0x268470
srpRead 0x268490
srpRead 0x2684B0
srpRead 0x2684D0
srpRead 0x2684F0

# timer status
srpRead 0x2684fc 1



