# soft reset BFN
srpWrite 0x268c2c 0x8000
# remove soft reset
srpWrite 0x268c2c 0x0
# read BFN live count
srpRead 0x268c3c 


# timer trigger 0, after 10us
# The timer logic compares the lower 32 bits of the BFN counter with the contents of this register.
# 10000 cycles
srpWrite 0x268500 0x2710
# timer trigger 1, after 10us
srpWrite 0x268520 0x2710
# timer trigger 2, after 10us
srpWrite 0x268540 0x2710
# timer trigger 3, after 10us
srpWrite 0x268560 0x2710
# timer trigger 4, after 10us
srpWrite 0x268580 0x2710
# timer trigger 5, after 10us
srpWrite 0x2685A0 0x2710
# timer trigger 6, after 10us
srpWrite 0x2685C0 0x2710
# timer trigger 7, after 10us
srpWrite 0x2685E0 0x2710

# timer interval 0
# In continuous mode only, this register contains the BFN period that the timer re-trigger
srpWrite 0x268504 0x0

# grp1 GPIO inout: make as out
srpWrite 0x268610 0xFFFFFFFF

# gpio_polarity
srpWrite 0x268608 0x0

# gpio set mask - timer 0
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268508 0xF

# gpio set mask - timer 1
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268528 0xF0

# gpio set mask - timer 2
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268548 0xF00

# gpio set mask - timer 3
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268568 0xF000

# gpio set mask - timer 4
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268588 0xF0000

# gpio set mask - timer 5
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2685A8 0xF00000

# gpio set mask - timer 6
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2685C8 0xF000000

# gpio set mask - timer 7
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2685E8 0xF0000000

# gpio_val- timer0, The value to which the GPIO will be set
srpWrite 0x26850c 0xa

# gpio_val- timer1, The value to which the GPIO will be set
srpWrite 0x26852c 0x55555555

# gpio_val- timer2, The value to which the GPIO will be set
srpWrite 0x26854c 0xaaaaaaaa

# gpio_val- timer3, The value to which the GPIO will be set
srpWrite 0x26856c 0x55555555
# gpio_val- timer4, The value to which the GPIO will be set
srpWrite 0x26858c 0xaaaaaaaa

# gpio_val- timer5, The value to which the GPIO will be set
srpWrite 0x2685ac 0x55555555
# gpio_val- timer6, The value to which the GPIO will be set
srpWrite 0x2685cc 0xaaaaaaaa

# gpio_val- timer7, The value to which the GPIO will be set
srpWrite 0x2685ec 0x55555555

#timer_cfg0, one shot, enable
srpWrite 0x268510 0x1
#timer_cfg1, one shot, enable
srpWrite 0x268530 0x1
#timer_cfg2, one shot, enable
srpWrite 0x268550 0x1
#timer_cfg3, one shot, enable
srpWrite 0x268570 0x1
#timer_cfg4, one shot, enable
srpWrite 0x268590 0x1
#timer_cfg5, one shot, enable
srpWrite 0x2685B0 0x1
#timer_cfg6, one shot, enable
srpWrite 0x2685D0 0x1
#timer_cfg7, one shot, enable
srpWrite 0x2685F0 0x1

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
srpRead 0x2685fc 1

# Read grp0 GPIO
# frioPciRead -F s6a1 -P 0x20014

# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C

# gpio_curr_out
srpRead 0x268614

# read timer_cfg to clear status
srpRead 0x268510
srpRead 0x268530
srpRead 0x268550
srpRead 0x268570
srpRead 0x268590
srpRead 0x2685B0
srpRead 0x2685D0
srpRead 0x2685F0

# timer status
srpRead 0x2685fc 1



