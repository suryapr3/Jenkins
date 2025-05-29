include $(PROJECT_HOME)/common.mk
TESTNAME = vex2rcs_transfer
TESTFILE = vex2rcs_transfer
#TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so
SRP_INCLUDE = -I$(SRP_RTE)/include -Ivex/sim_m64 -Ivex $(TEST_FWK_INC)
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
