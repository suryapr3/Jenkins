# write core0_control - altreset vector
# srpWrite 0x26c008 0x11
# write core0_Altreset
# srpWrite 0x26c018 0x10000000
# RCS_CONFIG[31:24] needs to be 8'hFA for this soft reset 

# halt core 0
srpWrite 0x26c008 0x1
# enable soft reset, now rsm_zeroise inits all memory to 0?
srpWrite 0x26c004 0xFA070002
# soft reset core0
srpWrite 0x26c02c 0x100
# remove core soft reset, this needs to be done after loading .elf?
# not able to load core, when its in softreset!
srpWrite 0x26c02c 0x0
sleep 1
# load program
srpRcsLoader -c0 -f rcs/ax_hw.elf 

# enable core run
srpWrite 0x26c008 0x0
sleep 1
# core0 DRAM
srpRead 0xE4030 32
# core1 DRAM
srpRead 0x124030 4
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
srpWrite 0xE4030 0 0 0 0 0 0 0 0 
# clear RSM
srpWrite 0x210000 0 0 0 0 0 0 0 0 

