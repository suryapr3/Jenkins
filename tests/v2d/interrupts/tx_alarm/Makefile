include $(PROJECT_HOME)/common.mk
INC += -I$(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/v2d/common

REGRESSION=0
EXTRA_UNDERRUN_ENABLE=0
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
CFLAGS += -DEXTRA_UNDERRUN_ENABLE=$(EXTRA_UNDERRUN_ENABLE)
VERBOSE = TRUE
all: TARGET
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

clean:
	rm -rf obj
	rm -rf *.o *.so *.log


