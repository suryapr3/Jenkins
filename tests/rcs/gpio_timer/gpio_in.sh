###### GPIO IN ######################
# grp0 gpio_inout, in
srpWrite 0x268210 0x0
# grp1 gpio_inout, in
srpWrite 0x268610 0x0

# drive grp0 GPIO
frioPciWrite -F s6a1 -P 0x20010 0xa5a5a5a5
# drive grp1 GPIO
frioPciWrite -F s6a1 -P 0x20018 0x5a5a5a5a

# grp0 gpio_curr_in
srpRead 0x268218
# grp1 gpio_curr_in
srpRead 0x268618

# drive grp0 GPIO
frioPciWrite -F s6a1 -P 0x20010 0x5a5a5a5a
# drive grp1 GPIO
frioPciWrite -F s6a1 -P 0x20018 0xa5a5a5a5

# grp0 gpio_curr_in
srpRead 0x268218
# grp1 gpio_curr_in
srpRead 0x268618

# drive grp0 GPIO
frioPciWrite -F s6a1 -P 0x20010 0x44332211
# drive grp1 GPIO
frioPciWrite -F s6a1 -P 0x20018 0x55667788

# grp0 gpio_curr_in
srpRead 0x268218
# grp1 gpio_curr_in
srpRead 0x268618

# gpio_in_delta: state of the sampled GPIO input bit has changed
srpRead 0x268224

# gpio_int_mask: Set to 1 to allow associated GPIO bit's contribution to GPIO interrupt
srpWrite 0x268228 0x0

# gpio_lpr_15_0
srpWrite 0x268240 0x0

# gpio_lpr_31_16
srpWrite 0x268244 0x0
