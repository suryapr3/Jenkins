#ifndef RESET_H
#define RESET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sw_cold_reset();
void sw_warm_reset();
void register_read_write_access();
void register_access_for_default_value_after_reset();

#endif//RESET_H
