###################################################################################################
#
# INTEL CONFIDENTIAL
#
# Copyright (C) 2022 Intel Corporation
#
# This software and the related documents ("Material") are Intel copyrighted materials,
# and your use of them is governed by the express license under which they were provided
# to you ("License"). Unless the License provides otherwise, you may not use, modify,
#* copy, publish, distribute, disclose or transmit this software or the related documents
# without Intel's prior written permission.
# This software and the related documents are provided as is, with no express or implied
# warranties, other than those that are expressly stated in the License.
# No license under any patent, copyright, trade secret or other intellectual property
# right is granted to or conferred upon you by disclosure or delivery of the Materials,
# either expressly, by implication, inducement, estoppel or otherwise. Any license under
# such intellectual property rights must be expressed and approved by Intel in writing.
#
###################################################################################################

TARGET ?= iss
SIM_ASSERT_EN ?= 1

CSOURCES += $(OUTDIR)/gen/src/fw_ver.c
CSOURCES += $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.c))
ASOURCES += $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.S))
CPPSOURCES += $(foreach dir, $(SOURCEDIRS), $(wildcard $(dir)/*.cpp))
OBJS += $(filter-out $(EXCLUDE_OBJ), $(foreach obj, $(CSOURCES:%.c=%.o), $(OBJDIR)/$(notdir $(obj))))
OBJS += $(filter-out $(EXCLUDE_OBJ), $(foreach obj, $(CPPSOURCES:%.cpp=%.o), $(OBJDIR)/$(notdir $(obj))))
OBJS += $(filter-out $(EXCLUDE_OBJ), $(foreach obj, $(ASOURCES:%.S=%.o), $(OBJDIR)/$(notdir $(obj))))
TIDY_OBJS = $(subst /iss/,/*/, $(filter-out $(OBJDIR)/rf_calib%, $(OBJS)))

VPATH += $(OUTDIR)/gen/src
VPATH += $(foreach dir, $(SOURCEDIRS), $(dir):)
INCLUDEDIRS += ../../ipcommon/hw_inc
INCLUDES += $(foreach inc, $(INCLUDEDIRS), -I$(inc))

ifdef UNIT
    DEFINES += -DUNIT=$(UNIT)
else
    DEFINES += -DUNIT=0
    LDFLAGS += -Xlinker -Map=$(BIN_DIR)/info/$(PROG)_$(TARGET).map
endif

CPPFLAGS += -O3

ifeq ($(TARGET),iss)
    CCFLAGS += -g
    CPPFLAGS += -g
    ifeq (,$(findstring -DPRINT_C_PRINTF,$(DEFINES)))
		DEFINES += -DPRINT_C_PRINTF=1
	endif
    DEFINES += -DPRINT_CUSTOM_DEBUGCALL=0
    DEFINES += -DFW_ASSERT_EN=1
else
    ifeq ($(TARGET),sim)
        DEFINES += -DFW_ASSERT_EN=$(SIM_ASSERT_EN)
        DEFINES += -DPRINT_CUSTOM_DEBUGCALL=1
        DEFINES += -DTARGET_SIM=1
    else
        DEFINES += -DFW_ASSERT_EN=0
        DEFINES += -DTARGET_SIM=0
    endif
    DEFINES += -DPRINT_C_PRINTF=0
endif

#
# Specify FW version by grabbing the current tags
#
version := $(subst -, ,$(shell git describe --long --dirty --tags | sed 's/g\([^g]\{1,\}\)$$/0x\1/'))
COMMIT := $(strip $(word 3, $(version)))
COMMITS_PAST := $(strip $(word 2, $(version)))
ifneq ($(COMMITS_PAST), 0)
	BUILD_INFO_COMMITS := $(COMMITS_PAST)
else
	BUILD_INFO_COMMITS := "0"
endif

BUILD_TAG :=$(strip $(word 1, $(version)))
BUILD_INFO := $(COMMIT)

COMMON_FLAGS += --xtensa-core=$(CPU)
DEP_FLAGS += -MMD -MF $(OBJDIR)/$(*F).d
# -fno-short-enums helps Coverity align w/enum size.
CCFLAGS += -fno-short-enums -mno-serialize-volatile -Wshorten-64-to-32
CPPFLAGS += -fno-short-enums
CCFLAGS += -DVERSION_BUILD_DATE=\""$(shell date)"\" \
           -DVERSION_BUILD_MACHINE=\""$(shell echo `whoami`@`hostname`)"\" \
           -DVERSION_TAG=\"$(BUILD_TAG)\" \
           -DVERSION_COMMIT_ID=$(BUILD_INFO) \
           -DVERSION_INFO_COMMITS=\"$(BUILD_INFO_COMMITS)\"
.PHONY: $(PROG) debug unit factory_test
.SECONDARY:

#
# Default make target, build main binary for PROG/TARGET.
# Place no targets above this line.
#
$(PROG):$(BIN_DIR)/$(PROG)_$(TARGET).elf
	@$(SIZE) $(BIN_DIR)/$(PROG)_$(TARGET).elf
	@$(DUMP) $(COMMON_FLAGS) $(BIN_DIR)/$(PROG)_$(TARGET).elf -D > $(BIN_DIR)/info/$(PROG)_$(TARGET).lst
	@mkdir -p $(BIN_DIR)/sram

#ifeq ($(PROG),ana)
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --ana_core --start=$(DRAM_START) --offset=$(DRAM_OFFSET) --size=$(DRAM_SIZE) #--tools=$(SWTOOLS_CTL) > $(BIN_DIR)/sram/$(PROG)_$(TARGET)_dram.data
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --ana_core --start=$(IRAM_START) --size=$(IRAM_SIZE) --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(PROG)_$(TARGET)_iram.data
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --rom --size=0x100 --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(PROG)_$(TARGET)_rom.data
#else ifeq ($(PROG),spl)
#	$(SWTOOLS_CTL)/bin/xt-dumpelf --width=128 --little-endian --full --no-bss --base=$(SRAM_START) --size=0x2000 $(BIN_DIR)/$(PROG)_$(TARGET).elf > #$(BIN_DIR)/sram/$(PROG)_$(TARGET).data
#else
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --start=$(DRAM_START) --offset=$(DRAM_OFFSET) --size=$(DRAM_SIZE) #--tools=$(SWTOOLS_CTL) > $(BIN_DIR)/sram/$(PROG)_$(TARGET)_dram.data
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --start=$(IRAM_START) --size=$(IRAM_SIZE) --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(PROG)_$(TARGET)_iram.data
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --start=$(SRAM_START) --size=$(SRAM_SIZE) --no-lines --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(PROG)_$(TARGET)_sram.data
#	@$(PRJDIR)/scripts/gen_ram.py $(BIN_DIR)/$(PROG)_$(TARGET).elf --rom --size=0x100 --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(PROG)_$(TARGET)_rom.data
#endif

#ifeq ($(TARGET),sim)
#	@$(PRJDIR)/scripts/gen_dbg_prints.py $(BIN_DIR)/$(PROG)_$(TARGET).elf $(BIN_DIR)/info/$(PROG)_$(TARGET).lst --tools=$(SWTOOLS_CTL) #--path=$(BIN_DIR)/info > $(BIN_DIR)/info/$(PROG)_$(TARGET)_mssg.txt
#endif

APP_CFLAGS = -g -lc -lreftb -lm $(DIAG_CFLAGS)

# define a macro 'newline' with two empty lines:
define newline


endef
#
# Build unit test binaries and its data format output.
#
unit:$(UNIT_TARGS)
	@$(SIZE) $(UNIT_TARGS)
	@mkdir -p $(BIN_DIR)/sram
	@mkdir -p $(BIN_DIR)/info
	@$(foreach f, $^, \
#		@$(PRJDIR)/scripts/gen_ram.py $(f) --start=$(DRAM_START) --offset=$(DRAM_OFFSET) --size=$(DRAM_SIZE) --tools=$(SWTOOLS_CTL) > #$(BIN_DIR)/sram/$(basename $(notdir $(f)))_dram.data $(newline) \
#		@$(PRJDIR)/scripts/gen_ram.py $(f) --start=$(IRAM_START) --size=$(IRAM_SIZE) --tools=$(SWTOOLS_CTL) > $(BIN_DIR)/sram/$(basename $(notdir #$(f)))_iram.data $(newline) \
#		@$(PRJDIR)/scripts/gen_ram.py $(f) --rom --size=0x100 --tools=$(SWTOOLS_CTL) > $(BIN_DIR)/sram/$(basename $(notdir $(f)))_rom.data #$(newline) \
		@$(DUMP) $(COMMON_FLAGS) $(f) -D > $(BIN_DIR)/info/$(basename $(notdir $(f))).lst $(newline) \
		)
#ifneq ($(PROG),ana)
#	@$(foreach f, $^, \
#		@$(PRJDIR)/scripts/gen_ram.py $(f) --start=$(SRAM_START) --size=$(SRAM_SIZE) --tools=$(SWTOOLS_CTL) --no-lines > $(BIN_DIR)/sram/$(basename #$(notdir $(f)))_sram.data $(newline) \
#		)
#endif

# Binary depends on object list, link when objects are available.
$(BIN_DIR)/$(PROG)_$(TARGET).elf: $(OBJS)
	@echo "---- $(PROG) LINKING $@  ($(CPU))"
	@mkdir -p $(BIN_DIR)/info
	@$(CCP) $(OBJS) $(APP_CFLAGS) $(LDFLAGS) $(COMMON_FLAGS)  -o $(BIN_DIR)/$(PROG)_$(TARGET).elf

# Unit Test binary link rule, objects plus unit main..
$(BIN_DIR)/%.elf: $(OBJS) $(OBJDIR)/%.o
	@echo "---- $(PROG) LINKING $@  ($(CPU))"
	@mkdir -p $(dir $@)
	@$(CCP) $(LDFLAGS) $(COMMON_FLAGS) $(OBJS) $(OBJDIR)/$(basename $(@F)).o -o $@

clean:
	rm -rf $(OBJDIR)
	rm -rf $(OUTDIR)/$(PROG)

ifneq ($(TEST_TGT),)
	rm -rf $(OBJDIR)/$(PROG)_$(TEST_TGT).o
endif
	rm -f $(BIN_DIR)/$(PROG)_*.elf
	rm -f $(BIN_DIR)/info/$(PROG)_*.lst
	rm -f $(BIN_DIR)/info/$(PROG)_*.map
	rm -f $(BIN_DIR)/info/$(PROG)_*.txt
	rm -f $(BIN_DIR)/sram/$(PROG)_*.data
	rm -f $(BIN_DIR)/sram/*_*.data
	rm -f $(BIN_DIR)/factory/*.tar

tidy:
	rm -f $(TIDY_OBJS)
	rm -f $(BIN_DIR)/$(PROG)_*.elf
	rm -f $(BIN_DIR)/info/$(PROG)_*.lst
	rm -f $(BIN_DIR)/info/$(PROG)_*.map
	rm -f $(BIN_DIR)/info/$(PROG)_*.txt
	rm -f $(BIN_DIR)/sram/$(PROG)_*.data
	rm -f $(BIN_DIR)/factory/*.tar

unit_clean:
	rm -rf $(OBJDIR)
	rm -f $(BIN_DIR)/*.elf
	rm -f $(BIN_DIR)/sram/*_*.data

# build rule (C)
$(OBJDIR)/%.o : %.c
	@echo "---- $(PROG) Compiling C $< --> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $(COMMON_FLAGS) $(INCLUDES) -D__FILENAME__=$(notdir $<) $(DEFINES) -c $< -o $@ $(DEP_FLAGS)

# build rule (CPP)
$(OBJDIR)/%.o : %.cpp
	@echo "---- $(PROG) Compiling CPP $< --> $@"
	@mkdir -p $(dir $@)
	@$(CCP) $(CPPFLAGS) $(COMMON_FLAGS) $(INCLUDES) -D__FILENAME__=$(notdir $<) $(DEFINES) -c $< -o $@ $(DEP_FLAGS)

# build rule (ASM)
$(OBJDIR)/%.o : %.S
	@echo "---- $(PROG) Assembling $< --> $@"
	@mkdir -p $(dir $@)
	@$(CC) $(ASFLAGS) $(COMMON_FLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

-include $(wildcard $(OBJDIR)/*.d)

debug:
	@echo PRJDIR:     $(PRJDIR)
	@echo BIN_DIR:    $(BIN_DIR)
	@echo OBJDIR:     $(OBJDIR)
	@echo OUTDIR:     $(OUTDIR)
	@echo CURDIR:     $(CURDIR)
	@echo SOURCES:    $(SOURCES)
	@echo OBJS:       $(OBJS)
	@echo TIDY_OBJS:  $(TIDY_OBJS)
	@echo UNIT_TESTS: $(UNIT_TESTS)
	@echo UNIT_TARGS: $(UNIT_TARGS)

factory_test: $(PROG)
	mkdir -p $(BIN_DIR)/factory
#	@$(PRJDIR)/scripts/gen_stil.py --tools=$(SWTOOLS_CTL) --program=$(PROG) --target=$(TARGET) $(BIN_DIR)/$(PROG)_$(TARGET).elf

