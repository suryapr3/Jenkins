# soft reset BFN
srpWrite 0x268c3c 0x8000
# remove soft reset
srpWrite 0x268c3c 0x0
# read BFN live count
srpRead 0x268c4c 2


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

# gpio_polarity
srpWrite 0x268208 0x0
# clear GPIO
# grp0 gpio_set_val_15_0
srpWrite 0x26821c 0xFFFF0000
# grp0 gpio_set_val_31_16
srpWrite 0x268220 0xFFFF0000

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014


# gpio set mask - timer 0
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268008 0xFFFF

# gpio set mask - timer 1
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x268028 0xFF00
#srpWrite 0x268028 0xFF00
srpWrite 0x268028 0xFFFF0000

# gpio set mask - timer 2
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x268048 0xF00
srpWrite 0x268048 0x0
# gpio set mask - timer 3
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x268068 0xF000
srpWrite 0x268068 0x0
# gpio set mask - timer 4
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x268088 0xF0000
srpWrite 0x268088 0x0
# gpio set mask - timer 5
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x2680A8 0xF00000
srpWrite 0x2680A8 0x0

# gpio set mask - timer 6
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x2680C8 0xF000000
srpWrite 0x2680C8 0x0

# gpio set mask - timer 7
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
#srpWrite 0x2680E8 0xF0000000
srpWrite 0x2680E8 0x0

# gpio_val- timer0, The value to which the GPIO will be set
srpWrite 0x26800c 0x11111111

# gpio_val- timer1, The value to which the GPIO will be set
srpWrite 0x26802c 0x22222222
#srpWrite 0x26802c 0x0

# gpio_val- timer2, The value to which the GPIO will be set
#srpWrite 0x26804c 0xa00
srpWrite 0x26804c 0x0

# gpio_val- timer3, The value to which the GPIO will be set
#srpWrite 0x26806c 0x5000
srpWrite 0x26806c 0x0
# gpio_val- timer4, The value to which the GPIO will be set
#srpWrite 0x26808c 0xa0000
srpWrite 0x26808c 0x0

# gpio_val- timer5, The value to which the GPIO will be set
#srpWrite 0x2680ac 0x500000
srpWrite 0x2680ac 0x0
# gpio_val- timer6, The value to which the GPIO will be set
#srpWrite 0x2680cc 0xa000000
srpWrite 0x2680cc 0x0

# gpio_val- timer7, The value to which the GPIO will be set
#srpWrite 0x2680ec 0x50000000
srpWrite 0x2680ec 0x0

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
srpWrite 0x268c3c 0xB2

# read BFN live count
srpRead 0x268c4c 2

# read BFN live count
srpRead 0x268c4c 2

# read BFN live count
srpRead 0x268c4c 2

# timer status
srpRead 0x2680fc 1

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014

# Read grp1 GPIO
#frioPciRead -F s6a1 -P 0x2001C

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



