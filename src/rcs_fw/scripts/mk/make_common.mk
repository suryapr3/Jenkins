MK_FILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PRJDIR ?= $(abspath $(MK_FILE_DIR)../..)
OUTDIR = $(PRJDIR)/out

ifeq ($(UNIT),1)
  UNIT_DIR = unit/$(PROG)
  BIN_DIR = $(OUTDIR)/bin/$(UNIT_DIR)
  UNIT_TARGS = $(foreach targ, $(UNIT_TESTS:%.c=%.elf), $(BIN_DIR)/$(targ))
  UNIT_TARGS += $(foreach targ, $(UNIT_TESTS_CPP:%.cpp=%.elf), $(BIN_DIR)/$(targ))
  VPATH += unit
  OBJDIR = $(OUTDIR)/$(UNIT_DIR)/$(TARGET)
  EXCLUDE_OBJ = $(OBJDIR)/$(PROG)_main.o
else
  OBJDIR = $(OUTDIR)/$(PROG)/$(TARGET)
  BIN_DIR = $(OUTDIR)/bin
endif

ifeq ($(PROG),ana)
  DEFINES += -DCPU_ANA=1
  DEFINES += -DRCS=1
else ifeq ($(PROG),cal)
  DEFINES += -DCPU_CAL=1
  DEFINES += -DRCS=1
else ifeq ($(PROG),ax)
  DEFINES += -DCPU_AX=1
  DEFINES += -DRCS=1
else ifeq ($(PROG),rx)
  DEFINES += -DCPU_RX=1
  DEFINES += -DRCS=1
else ifeq ($(PROG),tx)
  DEFINES += -DCPU_TX=1
  DEFINES += -DRCS=1
else ifeq ($(PROG),factory)
  DEFINES += -DCPU_CAL=1
  DEFINES += -DRCS=1
else ifneq ($(PROG),spl)
  $(error PROG not defined)
endif

# For building ipcommon specific to RCS FW side.
include $(MK_FILE_DIR)/makeinclude.mk


ifeq ($(PROG),ana)
  include $(MK_FILE_DIR)/analog_lx7.mk
else ifeq ($(PROG),cal)
  include $(MK_FILE_DIR)/control_kp1.mk
else ifeq ($(PROG),factory)
  include $(MK_FILE_DIR)/control_kp1.mk
else
  include $(MK_FILE_DIR)/control_lx7.mk
endif
