include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/src/common -I../flow3_common/ -I../../common/
LIBS += ../flow3_common
LIBS += ../../common

REGRESSION=0
FILL_LEVEL_TRIGGER=1
VEX_1P5G=0
RCS_TRIGGER=1
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
CFLAGS += -DFILL_LEVEL_TRIGGER=$(FILL_LEVEL_TRIGGER)
CFLAGS += -DVEX_1P5G=$(VEX_1P5G)
CFLAGS += -DRCS_TRIGGER=$(RCS_TRIGGER)
VERBOSE = TRUE
all: vex_fw_binary rcs_binary TARGET
TARGET:$(TESTNAME).so

SRP_INCLUDE += -Ivex_fw/sim_m64 -Ivex_fw

$(TESTNAME).so: $(TESTNAME).o  obj
	$(CC) $(CFLAGS)  $(SRP_INCLUDE) $(SRP_LD_FLAGS) $< $(wildcard obj/*) -o $@
$(TESTNAME).o: $(TESTNAME).c
	$(CC) $(CFLAGS)  $(SRP_INCLUDE) $(INC) -c -o $@ $<

obj:
	mkdir obj
	for dir in $(LIBS); do \
		echo $$dir; \
		cd $$dir; \
		echo pwd; \
		$(CC) -c $(CFLAGS) *.c $(INC) $(SRP_INCLUDE) $(SRP_LD_FLAGS); \
		mv *.o $(CURDIR)/obj; \
		cd -; \
	done

vex_fw_binary:
	@echo "Building VEX FW binary"
	$(MAKE) -C ./vex_fw sim_m64 NO_SIM=1 FILL_LEVEL_TRIGGER=$(FILL_LEVEL_TRIGGER)

rcs_binary:
	@echo "Building RCS elf file"
	$(MAKE) -C rcs_fw/v2d_gbuffer_mode1_update prog=ax
	mv $(PROJECT_HOME)/src/rcs_fw/out/bin/v2d_gbuffer_mode1_update/ax_hw.elf rcs_fw/
	@echo "Moved the elf file"

clean:
	rm -rf obj
	rm -rf *.o *.so *.log
	rm -rf rcs_fw/*elf
	$(MAKE) clean -C ./vex_fw
	$(MAKE) clean -C rcs_fw/v2d_gbuffer_mode1_update prog=ax


