include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/src/hw_inc_rte -I$(PROJECT_HOME)/src/common -I../../flow6/common/
LIBS += ../../flow6/common

REGRESSION=0
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
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
		$(CC) -c -fpic -shared *.c $(INC) $(SRP_INCLUDE) $(SRP_LD_FLAGS); \
		mv *.o $(CURDIR)/obj; \
		cd -; \
	done

clean:
	rm -rf obj
	rm -rf *.o *.so *.log


