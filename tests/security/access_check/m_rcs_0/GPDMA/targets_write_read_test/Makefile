include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common -I$(PROJECT_HOME)/tests/security/access_check/access_check_common
INC +=  -I$(PROJECT_HOME)/tests/security/access_check/access_check_common_noc
LIBS = $(PROJECT_HOME)/src/common $(PROJECT_HOME)/tests/security/access_check/access_check_common
LIBS += $(PROJECT_HOME)/tests/security/access_check/access_check_common_noc
CFLAGS += -fpic -shared -DENABLE_V2D_CLK  -DENABLE_VHA_CLK  -DENABLE_FRIO -DLOG_ERROR -DDISABLE_TIMESTAMP -DENABLE_JESD_CLK
CFLAGS += -DBUILD_DIR=\"$(CURDIR)/\"
DEPS = *.h
#TESTNAME = all_target_rbm_registers
TESTNAME = $(shell basename "$(CURDIR)")

VERBOSE = TRUE
TARGET:$(TESTNAME).so

#SRP_INCLUDE += -Ivex_fw/sim_m64 -Ivex_fw
all: $(TESTNAME).so rcs_fw_build_makefile

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
	$(MAKE) clean -C $(PROJECT_HOME)/tests/security/access_check/m_rcs_0/GPDMA/targets_write_read_test/rcs_fw CORE=ax
	@echo "Done with clean the  .o,.so,.map and .elf in the rcs_fw folder.."

rcs_fw_build_makefile:
	@echo "Building rcs_fw .elf for all  cores.."
	$(MAKE) -C  $(PROJECT_HOME)/tests/security/access_check/m_rcs_0/GPDMA/targets_write_read_test/rcs_fw CORE=ax
	@echo " ax_rcs_fw.elf build is  done.."
	$(MAKE) -C  $(PROJECT_HOME)/tests/security/access_check/m_rcs_0/GPDMA/targets_write_read_test/rcs_fw CORE=rx
	@echo " rx_rcs_fw.elf build is  done.."
	$(MAKE) -C  $(PROJECT_HOME)/tests/security/access_check/m_rcs_0/GPDMA/targets_write_read_test/rcs_fw CORE=tx
	@echo " tx_rcs_fw.elf build is  done.."
 
.PHONY: all rcs_fw_build_makefile

