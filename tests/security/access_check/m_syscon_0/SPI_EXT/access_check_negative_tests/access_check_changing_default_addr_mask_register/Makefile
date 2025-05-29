include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc
INC += -I$(PROJECT_HOME)/src/common
INC += -I$(PROJECT_HOME)/tests/security/access_check/access_check_common
INC += -I$(PROJECT_HOME)/tests/security/access_check/access_check_common_noc
LIBS = $(PROJECT_HOME)/src/common $(PROJECT_HOME)/tests/security/access_check/access_check_common
LIBS += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc
CFLAGS += -fpic -shared -DENABLE_V2D_CLK  -DENABLE_VHA_CLK  -DENABLE_FRIO -DDISABLE_TIMESTAMP -DENABLE_JESD_CLK -DLOG_ERROR
CFLAGS += -DBUILD_DIR=\"$(CURDIR)/\"
DEPS = *.h
#TESTNAME = all_target_rbm_registers
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so

#SRP_INCLUDE += -Ivex_fw/sim_m64 -Ivex_fw

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
	rm -rf *.o *.so
 

