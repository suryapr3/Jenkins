# halt core 1
srpWrite 0x26C00C 0x11
# RCS_CONFIG[31:24] needs to be 8'hFA for this soft reset 
srpWrite 0x26c004 0xFA070202
# soft reset core1
srpWrite 0x26C02C 0x200
# remove core1 soft reset, needs to be done after loading elf?
srpWrite 0x26C02C 0x0

# load program
srpRcsLoader -c1 -f rcs/rx_hw.elf 
# enable core run
srpWrite 0x26C00C 0x10
# core0 DRAM
srpRead 0xE4030 4
# core1 DRAM
srpRead 0x124030 32
# core2 DRAM
srpRead 0x164030 4
# core3 DRAM
srpRead 0x1C4030 4
# RSM
srpRead 0x210000 32
# double exception -core0
srpRead 0x26c0f4 
# double exception -core1
srpRead 0x26c120 
# double exception -core2
srpRead 0x26c14c
# double exception -core3
srpRead 0x26c178

# clear core1 DRAM
srpWrite 0x124030 0 0 0 0 0 0 0 0 
# clear RSM
srpWrite 0x210000 0 0 0 0 0 0 0 0 
