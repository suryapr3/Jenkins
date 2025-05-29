include $(PROJECT_HOME)/common.mk
INC = -I$(PROJECT_HOME)/src/hw_inc \
      -I$(PROJECT_HOME)/src/common \
      -I$(PROJECT_HOME)/tests/security/access_check/access_check_common \
      -I$(PROJECT_HOME)/tests/security/access_check/access_check_common_noc \
      -I$(PROJECT_HOME)/tests/syscon/coresight/coresight_common

LIBS = $(PROJECT_HOME)/src/common \
       $(PROJECT_HOME)/tests/security/access_check/access_check_common \
       $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc \
       $(PROJECT_HOME)/tests/syscon/coresight/coresight_common
CFLAGS += -fpic -shared -DENABLE_V2D_CLK  -DENABLE_VHA_CLK  -DENABLE_FRIO -DLOG_ERROR -DDISABLE_TIMESTAMP -DENABLE_JESD_CLK

CFLAGS += -DBUILD_DIR=\"$(CURDIR)/\"
DEPS = *.h
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
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
	rm -rf *.o *.so


