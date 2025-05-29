# Include directories
INC := -I$(PROJECT_HOME)/src/hw_inc \
       -I$(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs \
       -I$(PROJECT_HOME)/src/common \
       -I$(PROJECT_HOME)/src/rcs_fw/rcs/com/inc \
       -I$(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs

# Libraries
LIBS := -L$(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs \
        -L$(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs


CC = $(SWTOOLS_ANA)/bin/xt-clang
LD = $(CC)


CORE_LOWER = $(shell echo $(CORE) | tr '[:upper:]' '[:lower:]')

ifeq ($(CORE),ana)
  DEFINES += -DCPU_ANA=1
else ifeq ($(CORE),ax)
  DEFINES += -DCPU_AX=1
  CPU =  HWC_RCS_LX7
else ifeq ($(CORE),cal)
  DEFINES += -DCPU_CAL=1
  CPU = HWC_RCS_KP1
else ifeq ($(CORE),rx)
  DEFINES += -DCPU_RX=1
  CPU = HWC_RCS_LX7
else ifeq ($(CORE),tx)
  DEFINES += -DCPU_TX=1
  CPU = HWC_RCS_LX7
else
  $(error CORE not defined)
endif


CPPFLAGS += -O3
CPPFLAGS += -fforce-enable-int128
CCFLAGS += -fforce-enable-int128

ifeq ($(CORE),cal)
    ASFLAGS += -fdata-sections -ffunction-sections
    CCFLAGS += -fdata-sections -ffunction-sections -mlongcalls
    CPPFLAGS += -std=c++17 -mlongcalls -LNO:simd $(VERBOSE) -fdata-sections -LNO:simd_agg_if_conv -fno-threadsafe-statics -ffunction-sections -stdlib=libc++-re
endif


LDFLAGS += -Xlinker  -Map=$(CORE)_$(TESTNAME).map
APP_CFLAGS = -g -lc -lreftb -lm $(DIAG_CFLAGS)
COMMON_FLAGS += --xtensa-core=$(CPU)

ifeq ($(CORE),adc)
DRAM_START=0x10000
DRAM_SIZE =0x10000
DRAM_OFFSET=0
IRAM_START=0x20000
IRAM_SIZE =0x10000
#SRAM_START=0x30000
#SRAM_SIZE= 0x20000
LDFLAGS += -mlsp=min-rt-local
SOURCE_FILES += adc_rcs_fw.c
endif

ifeq ($(CORE),ax)
DRAM_START=0x10020000
DRAM_SIZE= 0x00020000
DRAM_OFFSET=0
IRAM_START=0x10000000
IRAM_SIZE= 0x00020000
SRAM_START=0x00200000
SRAM_SIZE= 0x00040000
LDFLAGS += -mlsp=$(PROJECT_HOME)/src/rcs_fw/scripts/lsp/hw/$(CORE)
$(info Using linker script: $(LDFLAGS))
SOURCE_FILES += rcs_fw.c $(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs/access_check_common_rcs_definitions.c
SOURCE_FILES += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs/access_check_common_noc_rcs_definitions.c
endif



ifeq ($(CORE),rx)
DRAM_START=0x10020000
DRAM_SIZE= 0x00020000
DRAM_OFFSET=0
IRAM_START=0x10000000
IRAM_SIZE= 0x00020000
SRAM_START=0x00200000
SRAM_SIZE= 0x00040000
LDFLAGS += -mlsp=$(PROJECT_HOME)/src/rcs_fw/scripts/lsp/hw/$(CORE)
$(info Using linker script: $(LDFLAGS))
SOURCE_FILES += rcs_fw.c $(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs/access_check_common_rcs_definitions.c
SOURCE_FILES += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs/access_check_common_noc_rcs_definitions.c
endif

ifeq ($(CORE),tx)
DRAM_START=0x10020000
DRAM_SIZE= 0x00020000
DRAM_OFFSET=0
IRAM_START=0x10000000
IRAM_SIZE= 0x00020000
SRAM_START=0x00200000
SRAM_SIZE= 0x00040000
LDFLAGS += -mlsp=$(PROJECT_HOME)/src/rcs_fw/scripts/lsp/hw/$(CORE)
$(info Using linker script: $(LDFLAGS))
SOURCE_FILES += rcs_fw.c $(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs/access_check_common_rcs_definitions.c
SOURCE_FILES += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs/access_check_common_noc_rcs_definitions.c
endif

ifeq ($(CORE),cal)
DRAM_START=0x10040000
DRAM_SIZE =0x00010000
DRAM_OFFSET=0
IRAM_START=0x10000000
IRAM_SIZE =0x00040000
SRAM_START=0x00200000
SRAM_SIZE= 0x00040000
LDFLAGS += -std=c++17 -stdlib=libc++-re  -mlsp=$(PROJECT_HOME)/src/rcs_fw/scripts/lsp/hw/$(CORE) -Wl,--gc-sections

$(info Using linker script: $(LDFLAGS))
SOURCE_FILES += rcs_fw.c $(PROJECT_HOME)/tests/security/access_check/access_check_common_rcs/access_check_common_rcs_definitions.c
SOURCE_FILES += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc_rcs/access_check_common_noc_rcs_definitions.c
endif

DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")
OBJ = $(CORE)_$(TESTNAME).o

VERBOSE = TRUE
TARGET: $(CORE)_$(TESTNAME).elf

OBJ_FILES := $(patsubst %.c,%.o,$(SOURCE_FILES))


$(OBJ_FILES): %.o: %.c
	@echo "Compiling $<..."
	$(CC) $(INC) $(CCFLAGS) -c -o $@ $^



$(CORE)_$(TESTNAME).elf: $(OBJ_FILES)
	@echo "---- $(CORE) LINKING $@  ($(CPU))"
	@mkdir -p $(dir $@)
	@echo "$(LD) -v $^ $(APP_FLAGS) $(LDFLAGS) $(COMMON_FLAGS) -o $@"
	@$(LD) -v $^ $(APP_FLAGS) $(LDFLAGS) $(COMMON_FLAGS) -o $@

clean:
	rm -rf obj
	rm -rf *.o *.so *.map *.elf


