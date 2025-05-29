include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/tests/v2d/flow3/flow3_common -I$(PROJECT_HOME)/tests/v2d/common -I$(PROJECT_HOME)/tests/v2d/quad_delayed_start/quad_delayed_start_common
LIBS += $(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/v2d/flow3/flow3_common/
LIBS += $(PROJECT_HOME)/tests/v2d/quad_delayed_start/quad_delayed_start_common/

REGRESSION=0
RCS_TRIGGER=1
CAPTURE_DURATION=0
LIVEIQ_SAMPLES=0
VEX_1P5G=0
#CC=gcc
DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
CFLAGS += -DRCS_TRIGGER=$(RCS_TRIGGER)
CFLAGS += -DCAPTURE_DURATION=$(CAPTURE_DURATION)
CFLAGS += -DLIVEIQ_SAMPLES=$(LIVEIQ_SAMPLES)
CFLAGS += -DVEX_1P5G=$(VEX_1P5G)
VERBOSE = TRUE
all: vex_fw_binary rcs_binary $(TESTNAME).so
TARGET:$(TESTNAME).so

SRP_INCLUDE += -I../vex_fw/sim_m64 -I../vex_fw

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
	$(MAKE) -C ../vex_fw sim_m64 NO_SIM=1  

rcs_binary:
	@echo "Building RCS elf file"
	$(MAKE) -C rcs_fw/v2d_liveIQ_flow3_pdpd_egress_capture PROG=ax CAPTURE_DURATION=$(CAPTURE_DURATION)
	mv $(PROJECT_HOME)/src/rcs_fw/out/bin/v2d_liveIQ_flow3_pdpd_egress_capture/ax_hw.elf rcs_fw/
	@echo "Moved the elf file"

clean:
	rm -rf obj
	rm -rf *.o *.so *.log
	rm -rf rcs_fw/*elf
	$(MAKE) clean -C ../vex_fw
	$(MAKE) clean -C rcs_fw/v2d_liveIQ_flow3_pdpd_egress_capture PROG=ax
