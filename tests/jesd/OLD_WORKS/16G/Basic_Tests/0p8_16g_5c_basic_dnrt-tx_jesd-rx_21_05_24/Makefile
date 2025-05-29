#
#
include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common
#      -I$(PROJECT_HOME)/tests/jesd/jesd_common
LIBS = $(PROJECT_HOME)/src/common
#       $(PROJECT_HOME)/tests/jesd/jesd_common

#CC=gcc
CFLAGS = -fpic -shared 
DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so


$(TESTNAME).so: $(TESTNAME).o  obj
	$(CC) -fpic -shared  $(SRP_INCLUDE) $(SRP_LD_FLAGS) $< $(wildcard obj/*) -o $@
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


