# gpio grp0

# gpio_cfg
# gpio_deb_cnt_sel

# grp0 gpio_polarity
srpWrite 0x268208 0x0
# grp1 gpio_polarity
srpWrite 0x268608 0x0

######## GPIO OUT #####################
# grp0 gpio_inout, out
srpWrite 0x268210 0xFFFFFFFF
# grp1 gpio_inout, out
srpWrite 0x268610 0xFFFFFFFF

# grp0 gpio_set_val_15_0
srpWrite 0x26821c 0xFFFF1122
# grp0 gpio_set_val_31_16
srpWrite 0x268220 0xFFFF3344
# grp1 gpio_set_val_15_0
srpWrite 0x26861c 0xFFFF5566
# grp1 gpio_set_val_31_16
srpWrite 0x268620 0xFFFF7788

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014
# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C
# gpio_curr_out
srpRead 0x268214
srpRead 0x268614

# gpio_set_val_15_0
srpWrite 0x26821c 0xFFFF1234
# gpio_set_val_31_16
srpWrite 0x268220 0xFFFF5678
# grp1 gpio_set_val_15_0
srpWrite 0x26861c 0xFFFF1234
# grp1 gpio_set_val_31_16
srpWrite 0x268620 0xFFFF5678

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014
# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C
# gpio_curr_out
srpRead 0x268214
srpRead 0x268614

# gpio_set_val_15_0
srpWrite 0x26821c 0xFFFFa5a5
# gpio_set_val_31_16
srpWrite 0x268220 0xFFFF5a5a
# grp1 gpio_set_val_15_0
srpWrite 0x26861c 0xFFFFa5a5
# grp1 gpio_set_val_31_16
srpWrite 0x268620 0xFFFF5a5a

# Read grp0 GPIO
frioPciRead -F s6a1 -P 0x20014
# Read grp1 GPIO
frioPciRead -F s6a1 -P 0x2001C
# gpio_curr_out
srpRead 0x268214
srpRead 0x268614










 
