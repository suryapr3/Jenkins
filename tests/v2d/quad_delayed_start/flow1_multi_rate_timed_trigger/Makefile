include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/tests/v2d/flow1/flow1_common -I$(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/v2d/flow1/flow1_common/
LIBS += $(PROJECT_HOME)/tests/v2d/quad_delayed_start/quad_delayed_start_common/

REGRESSION=0
RCS_TRIGGER=1
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
CFLAGS += -DRCS_TRIGGER=$(RCS_TRIGGER)
VERBOSE = TRUE
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

clean:
	rm -rf obj
	rm -rf *.o *.so *.log


