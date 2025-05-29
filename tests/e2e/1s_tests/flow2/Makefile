#
#
include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common -I../common/
INC += -I$(PROJECT_HOME)/tests/vha/vha_common
INC += -I$(PROJECT_HOME)/tests/v2d/flow2/flow2_common 
INC += -I$(PROJECT_HOME)/tests/v2d/common
INC += -I$(PROJECT_HOME)/tests/jesd/jesd_common
INC += -I$(PROJECT_HOME)/tests/e2e/e2e_common

LIBS = $(PROJECT_HOME)/src/common
LIBS += $(PROJECT_HOME)/tests/vha/vha_common
LIBS += $(PROJECT_HOME)/tests/v2d/flow2/flow2_common
LIBS += $(PROJECT_HOME)/tests/v2d/common
LIBS += $(PROJECT_HOME)/tests/jesd/jesd_common
LIBS += $(PROJECT_HOME)/tests/e2e/e2e_common

REGRESSION=0
#CC=gcc
CFLAGS = -fpic -shared
CFLAGS += -DENABLE_VHA_CLK -DENABLE_V2D_CLK -DENABLE_JESD_CLK
CFLAGS += -DE2E_FLOW_EN -DFLOW2_EN
DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")

CFLAGS += -DREGRESSION=$(REGRESSION)
VERBOSE = TRUE
TARGET:$(TESTNAME).so

SRP_INCLUDE += -Iproducer/sim_m64 -Iproducer -Ivha_vex_fw/sim_m64 -Ivha_vex_fw -Ivex_fw/sim_m64 -Ivex_fw

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
		$(CC) -c -fpic -shared $(CFLAGS) *.c $(INC) $(SRP_INCLUDE) $(SRP_LD_FLAGS); \
		mv *.o $(CURDIR)/obj; \
		cd -; \
	done

clean:
	rm -rf obj
	rm -rf *.o $(TESTNAME).so *.log $(TESTNAME)


