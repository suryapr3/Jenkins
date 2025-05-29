
include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common
LIBS = $(PROJECT_HOME)/src/common
#CC=gcc
CFLAGS = -fpic -shared
CFLAGS += -DENABLE_JESD_CLK
CFLAGS += -DENABLE_V2D_CLK
CFLAGS += -DENABLE_VHA_CLK
CFLAGS += -DENABLE_VEX
#CFLAGS = 

DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so

SRP_INCLUDE += -Ivex_fw/sim_m64 -Ivex_fw

$(TESTNAME).so: $(TESTNAME).o  obj
	$(CC) $(CFLAGS) $(SRP_INCLUDE) $(SRP_LD_FLAGS) $< $(wildcard obj/*) -o $@
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
