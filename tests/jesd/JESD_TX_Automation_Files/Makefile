#
#
include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc \
	-I$(PROJECT_HOME)/src/common \
	-I$(PROJECT_HOME)/tests/jesd/ \
	-I$(PROJECT_HOME)/tests/jesd/jesd_common \
	-I$(PROJECT_HOME)/tests/jesd/jesd_uc_tests/jesd_sample_test

LIBS = $(PROJECT_HOME)/src/common \
	$(PROJECT_HOME)/tests/jesd/jesd_common \
	$(PROJECT_HOME)/tests/jesd/jesd_uc_tests/jesd_sample_test

#CC=gcc
CFLAGS = -fpic -shared 
CFLAGS += -DENABLE_VEX
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so

SRP_INCLUDE += -Ivex_fw/sim_m64 -Ivex_fw

$(TESTNAME).so: jesd_test_main.o obj
	$(CC) -fpic -shared  $(SRP_INCLUDE) $(INC) $(SRP_LD_FLAGS) $< $(wildcard obj/*) -o $@
# $(TESTNAME).o: $(TESTNAME).c
jesd_test_main.o: jesd_test_main.c
	$(CC) $(CFLAGS)  $(SRP_INCLUDE) $(INC) -c -o $@ $<

obj:
	mkdir obj
	for dir in $(LIBS); do \
		echo $$dir; \
		cd $$dir; \
		echo $$PWD; \
		$(CC) -c $(CFLAGS) *.c $(INC) $(SRP_INCLUDE) $(SRP_LD_FLAGS); \
		mv *.o $(CURDIR)/obj; \
		cd -; \
	done

clean:
	rm -rf obj
	rm -rf *.o *.so


