include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/v2d/common

REGRESSION=0
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
VERBOSE = TRUE
all: rcs_binary TARGET
TARGET:$(TESTNAME).so

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

rcs_binary:
	@echo "Building RCS elf file"
	$(MAKE) -C rcs_fw/v2d_bfn_isync_test prog=ax
	mv $(PROJECT_HOME)/src/rcs_fw/out/bin/v2d_bfn_isync_test/ax_hw.elf rcs_fw/
	@echo "Moved the elf file"

clean:
	rm -rf obj
	rm -rf *.o *.so *.log
	rm -rf rcs_fw/*elf
	$(MAKE) clean -C rcs_fw/v2d_bfn_isync_test prog=ax


