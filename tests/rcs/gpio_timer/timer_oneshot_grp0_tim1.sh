# soft reset BFN
srpWrite 0x268c2c 0x8000
# remove soft reset
srpWrite 0x268c2c 0x0
# read BFN live count
srpRead 0x268c3c 2


# timer trigger 0, after 10us
# The timer logic compares the lower 32 bits of the BFN counter with the contents of this register.
# 10000 cycles
srpWrite 0x268100 0x2710

# timer trigger 1, after 10us
srpWrite 0x268120 0x2710
# timer trigger 2, after 10us
srpWrite 0x268140 0x2710
# timer trigger 3, after 10us
srpWrite 0x268160 0x2710
# timer trigger 4, after 10us
srpWrite 0x268180 0x2710
# timer trigger 5, after 10us
srpWrite 0x2681A0 0x2710
# timer trigger 6, after 10us
srpWrite 0x2681C0 0x2710
# timer trigger 7, after 10us
srpWrite 0x2681E0 0x2710

# timer interval 0
# In continuous mode only, this register contains the BFN period that the timer re-trigger
srpWrite 0x268104 0x0

# grp0 GPIO inout: make as out
srpWrite 0x268210 0xFFFFFFFF

# gpio_polarity
srpWrite 0x268208 0x0

# gpio set mask - timer 0
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268108 0xF

# gpio set mask - timer 1
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268128 0xF0

# gpio set mask - timer 2
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268148 0xF00

# gpio set mask - timer 3
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268168 0xF000

# gpio set mask - timer 4
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x268188 0xF0000

# gpio set mask - timer 5
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2681A8 0xF00000

# gpio set mask - timer 6
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2681C8 0xF000000

# gpio set mask - timer 7
# If set to 1, the corresponding bit in the timer GPIO Value register is applied to the GPIO output
srpWrite 0x2681E8 0xF0000000

# gpio_val- timer0, The value to which the GPIO will be set
srpWrite 0x26810c 0x88

# gpio_val- timer1, The value to which the GPIO will be set
srpWrite 0x26812c 0x0

# gpio_val- timer2, The value to which the GPIO will be set
srpWrite 0x26814c 0x600

# gpio_val- timer3, The value to which the GPIO will be set
srpWrite 0x26816c 0x5000
# gpio_val- timer4, The value to which the GPIO will be set
srpWrite 0x26818c 0x40000

# gpio_val- timer5, The value to which the GPIO will be set
srpWrite 0x2681ac 0x300000
# gpio_val- timer6, The value to which the GPIO will be set
srpWrite 0x2681cc 0x2000000

# gpio_val- timer7, The value to which the GPIO will be set
srpWrite 0x2681ec 0x10000000

#timer_cfg0, one shot, enable
srpWrite 0x268110 0x1
#timer_cfg1, one shot, enable
srpWrite 0x268130 0x1
#timer_cfg2, one shot, enable
srpWrite 0x268150 0x1
#timer_cfg3, one shot, enable
srpWrite 0x268170 0x1
#timer_cfg4, one shot, enable
srpWrite 0x268190 0x1
#timer_cfg5, one shot, enable
srpWrite 0x2681B0 0x1
#timer_cfg6, one shot, enable
srpWrite 0x2681D0 0x1
#timer_cfg7, one shot, enable
srpWrite 0x2681F0 0x1

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
srpRead 0x2681fc 1

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014

# Read grp1 GPIO
#frioPciRead -F s6a1 -P 0x2001C

# read timer_cfg to clear status
srpRead 0x268110
srpRead 0x268130
srpRead 0x268150
srpRead 0x268170
srpRead 0x268190
srpRead 0x2681B0
srpRead 0x2681D0
srpRead 0x2681F0

# timer status
srpRead 0x2681fc 1



