MK_FILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PRJDIR ?= $(abspath $(MK_FILE_DIR)../..)
OUTDIR = $(PRJDIR)/out
BIN_DIR = $(OUTDIR)/bin/$(TEST_TGT)
OBJDIR = $(OUTDIR)/$(TEST_TGT)/$(PROG)_$(TARGET)
# instead of adding all .c file in src, only add the one for this core:
OBJS += $(OBJDIR)/$(PROG)_$(TEST_TGT).o

CSOURCES += ../../ipcommon/fw/tables/src/com_tables.c \
            ../../ipcommon/fw/tables/src/$(PROG)_tables.c

VPATH += src
VPATH += ../../ipcommon/fw/tables/src

ifeq ($(PROG),ana)
  DEFINES += -DCPU_ANA=1
else ifeq ($(PROG),cal)
  DEFINES += -DCPU_CAL=1 -DRCS=1
else ifeq ($(PROG),ax)
  DEFINES += -DCPU_AX=1 -DRCS=1
else ifeq ($(PROG),rx)
  DEFINES += -DCPU_RX=1 -DRCS=1
else ifeq ($(PROG),tx)
  DEFINES += -DCPU_TX=1 -DRCS=1
else
  $(error PROG not defined)
endif

include $(MK_FILE_DIR)/makeinclude.mk
ifeq ($(PROG),ana)
  include $(MK_FILE_DIR)/analog_lx7.mk
else ifeq ($(PROG),cal)
  include $(MK_FILE_DIR)/control_kp1.mk
else
  include $(MK_FILE_DIR)/control_lx7.mk
#  LDFLAGS +=  -Wl,--gc-sections
#  LDFLAGS +=  -Wl,--gc-keep-exported
endif
