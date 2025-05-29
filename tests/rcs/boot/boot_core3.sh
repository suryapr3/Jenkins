# write core0_control - altreset vector
# srpWrite 0x26c008 0x11
# write core0_Altreset
# srpWrite 0x26c018 0x10000000
# halt core 3
srpWrite 0x26C014 0x11
# RCS_CONFIG[31:24] needs to be 8'hFA for this soft reset 
srpWrite 0x26c004 0xFA070202
# soft reset core3
srpWrite 0x26C02C 0x10000000
# remove core3 soft reset
srpWrite 0x26C02C 0x0

# load program core3
srpRcsLoader -c3 -f rcs/cal_hw.elf 
# enable core3 run
srpWrite 0x26C014 0x10
# core0 DRAM
srpRead 0xE4030 4
# core1 DRAM
srpRead 0x124030 4
# core2 DRAM
srpRead 0x164030 4
# core3 DRAM
srpRead 0x1C4030 32
# RSM
srpRead 0x230000 32
# double exception -core0
srpRead 0x26c0f4 
# double exception -core1
srpRead 0x26c120 
# double exception -core2
srpRead 0x26c14c
# double exception -core3
srpRead 0x26c178

# clear core3 DRAM
srpWrite 0x1C4030 0 0 0 0 0 0 0 0 
# clear RSM
srpWrite 0x230000 0 0 0 0 0 0 0 0 
