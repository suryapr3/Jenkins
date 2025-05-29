###################################################################################################
#
# INTEL CONFIDENTIAL
#
# Copyright (C) 2022 Intel Corporation
#
# This software and the related documents ("Material") are Intel copyrighted materials,
# and your use of them is governed by the express license under which they were provided
# to you ("License"). Unless the License provides otherwise, you may not use, modify,
#* copy, publish, distribute, disclose or transmit this software or the related documents
# without Intel's prior written permission.
# This software and the related documents are provided as is, with no express or implied
# warranties, other than those that are expressly stated in the License.
# No license under any patent, copyright, trade secret or other intellectual property
# right is granted to or conferred upon you by disclosure or delivery of the Materials,
# either expressly, by implication, inducement, estoppel or otherwise. Any license under
# such intellectual property rights must be expressed and approved by Intel in writing.
#
###################################################################################################


.PHONY: ana rcs ax rx tx cal clean ana_clean rcs_clean cal_clean ax_clean rx_clean tx_clean debug code_format test doxygen spl spl_clean
.PHONY: unit com_unit ana_unit rcs_unit rcs_com_unit cal_unit ax_unit tx_unit rx_unit code_format

RCS_FW_DIR      = $(CURDIR)
ANT             = ant
PACKAGE_FILE    = package.xml
CURR_DATE       = $(shell date +"%d-%m-%Y")
ABCFW_COMMIT_ID = $(shell git rev-parse --verify --short HEAD)
BIN_DIR_NAME    = abcfw_bin
BIN_DIR         = $(RCS_FW_DIR)/images/$(BIN_DIR_NAME)
DOC_DIR_NAME    = abcfw_html
DOC_DIR         = $(RCS_FW_DIR)/images/$(DOC_DIR_NAME)
SRC_DIR_NAME    = abcfw_source
SRC_DIR         = $(RCS_FW_DIR)/images/$(SRC_DIR_NAME)
MAKE_JOBS      ?= -j16

# Format code
FORMAT := 0

# Everything targets.
all: ver ana rcs spl unit factory
	$(MAKE) -C test_tgt/rtl

all_sim: ana_sim rcs_sim factory_sim
all_hw: ana_hw rcs_hw factory_hw
all_all: all unit

clean: ana_clean rcs_clean unit_clean spl_clean factory_clean ver_clean
	rm -rf $(RCS_FW_DIR)/images

tidy: ana_clean ax_clean tx_clean rx_clean cal_tidy spl_clean factory_tidy

unit: com_unit ana_unit rcs_unit ax_unit tx_unit rx_unit

test:
	scripts/run_unit_tests.py

doxygen:
	@echo doxygen generating code...
	python scripts/generate_docs.py

# Format code
code_format:
ifneq ($(FORMAT), 0)
	@echo formatting code...
#	@git status -suall | awk '{ print $$2 }' | grep -v "${eigen_folder}" | grep "\.[cChH]$$" | xargs --no-run-if-empty clang-format --style=file -i to exclude eigen folder
	@for f in $$(git status -suall | awk '{ print $$2 }' | grep -E "\.c$$|\.C$$|\.h$$|\.H$$|\.cpp$$"); \
	do \
		clang-format --style=file -i $$f; \
	done

	@for f in $$(git --git-dir ./ipcommon/.git status -suall | awk '{ print $$2 }' | grep -E "fw/" | grep -E "\.c$$|\.C$$|\.h$$|\.H$$|\.cpp$$"); \
	do \
		clang-format --style=file -i ./ipcommon/$$f; \
	done

else
	@echo skip format code
endif

#
# Individual subsystem or CPU builds.
#

ana: code_format
	$(MAKE) -C ana TARGET=sim
	$(MAKE) -C ana TARGET=hw

ana_hw: code_format
	$(MAKE) -C ana TARGET=hw

ana_sim: code_format
	$(MAKE) -C ana TARGET=sim

spl: code_format
	$(MAKE) -C spl TARGET=sim
	$(MAKE) -C spl TARGET=hw

factory: factory_sim factory_hw

factory_sim: factory_ana_sim factory_cal_sim
factory_hw: factory_ana_hw factory_cal_hw

factory_cal_sim: code_format
	$(MAKE) -C factory TARGET=sim factory_test

factory_ana_sim: code_format
	$(MAKE) -C ana TARGET=sim factory_test

factory_cal_hw: code_format
	$(MAKE) -C factory TARGET=hw factory_test

factory_ana_hw: code_format
	$(MAKE) -C ana TARGET=hw factory_test

rcs: ax rx tx cal
rcs_hw: ax_hw rx_hw tx_hw cal_hw
rcs_sim: ax_sim rx_sim tx_sim cal_sim

cal: cal_sim  cal_hw

cal_sim: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/cal TARGET=sim

cal_hw: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/cal TARGET=hw

ax:  ax_sim  ax_hw

ax_sim: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/ax TARGET=sim

ax_hw: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/ax TARGET=hw

rx:  rx_sim  rx_hw

rx_sim: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/rx TARGET=sim

rx_hw: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/rx TARGET=hw


tx: tx_sim  tx_hw

tx_sim: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/tx TARGET=sim

tx_hw: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/tx TARGET=hw

ana_unit: code_format
	$(MAKE) -C ana unit UNIT=1

ana_profile: code_format
	$(MAKE) -C ana unit UNIT=1 PROFILE=1

rcs_unit:  rcs_com_unit ax_unit tx_unit rx_unit cal_unit

rcs_com_unit: code_format
	$(MAKE) -C rcs/com unit UNIT=1

cal_unit: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/cal unit UNIT=1

ax_unit: code_format
	$(MAKE) -C rcs/ax unit UNIT=1

rx_unit: code_format
	$(MAKE) -C rcs/rx unit UNIT=1

tx_unit: code_format
	$(MAKE) -C rcs/tx unit UNIT=1

cal_profile: code_format
	$(MAKE) $(MAKE_JOBS) -C rcs/cal unit UNIT=1 PROFILE=1

# for lock, default PROG=ax
lock: lock_sim lock_hw
lock_sim: code_format
	$(MAKE) -C test_tgt/lock TARGET=sim
lock_hw: code_format
	$(MAKE) -C test_tgt/lock TARGET=hw
nleq: nleq_sim nleq_hw
nleq_sim: code_format
	$(MAKE) -C test_tgt/nleq TARGET=sim
nleq_hw: code_format
	$(MAKE) -C test_tgt/nleq TARGET=hw
eigentest: eigentest_sim eigentest_hw
eigentest_sim: code_format
	$(MAKE) -C test_tgt/eigentest TARGET=sim
eigentest_hw: code_format
	$(MAKE) -C test_tgt/eigentest TARGET=hw
#
# individual subsystem or CPU cleaning
#

ana_clean:
	$(MAKE) -C ana clean

rcs_clean:
	$(MAKE) -C rcs clean

cal_clean:
	$(MAKE) -C rcs/cal clean

cal_tidy:
	$(MAKE) -C rcs/cal tidy

ax_clean:
	$(MAKE) -C rcs/ax clean

rx_clean:
	$(MAKE) -C rcs/rx clean

tx_clean:
	$(MAKE) -C rcs/tx clean

spl_clean:
	$(MAKE) -C spl clean

factory_clean: ana_clean
	$(MAKE) -C factory clean

factory_tidy: ana_clean
	$(MAKE) -C factory tidy

lock_clean: lock_hw_clean lock_sim_clean
lock_hw_clean:
	$(MAKE) -C test_tgt/lock TARGET=hw clean
lock_sim_clean:
	$(MAKE) -C test_tgt/lock TARGET=sim clean
nleq_clean: nleq_sim_clean nleq_hw_clean
nleq_sim_clean:
	$(MAKE) -C test_tgt/nleq TARGET=sim clean
nleq_hw_clean:
	$(MAKE) -C test_tgt/nleq TARGET=hw clean
eigentest_clean: eigentest_sim_clean eigentest_hw_clean
eigentest_sim_clean:
	$(MAKE) -C test_tgt/eigentest TARGET=sim clean
eigentest_hw_clean:
	$(MAKE) -C test_tgt/eigentest TARGET=hw clean
unit_clean:
	@$(MAKE) -C ana unit_clean UNIT=1
	@$(MAKE) -C rcs/cal unit_clean UNIT=1
	@$(MAKE) -C rcs/ax unit_clean UNIT=1
	@$(MAKE) -C rcs/rx unit_clean UNIT=1
	@$(MAKE) -C rcs/tx unit_clean UNIT=1
	@$(MAKE) -C rcs unit_clean UNIT=1
	@$(MAKE) -C ana unit_clean UNIT=1

#
# make debug.  substitue a different path to debug a different makefile.
#
debug:
	$(MAKE) -C rcs/cal debug

.PHONY: package doc_package publish

package:
	echo "INFO: Creating arborcrest firmware package"
	$(ANT) -f $(PACKAGE_FILE) -Ddest=$(BIN_DIR) bin-package
	cd $(BIN_DIR) ; \
	tar zcf $(CURDIR)/images/$(BIN_DIR_NAME).tar.gz abc_fw
	rm -rf $(BIN_DIR)
	$(ANT) -f $(PACKAGE_FILE) -Ddest=$(SRC_DIR) src-package
	cd $(SRC_DIR) ; \
	tar zcf $(CURDIR)/images/$(SRC_DIR_NAME).tar.gz abc_src
	rm -rf $(SRC_DIR)

doc_package:
	echo "INFO: Creating arborcrest firmware Document package"
	$(ANT) -f $(PACKAGE_FILE) -Ddest=$(DOC_DIR) doc-package
	cd $(DOC_DIR) ; \
	tar zcf $(CURDIR)/images/$(DOC_DIR_NAME).tar.gz html
	rm -rf $(DOC_DIR)

publish: doc_package
	echo "INFO: Publishing the packages" ; \
        $(RCS_FW_DIR)/bldtools/publish_abcfw.sh

include $(RCS_FW_DIR)/scripts/mk/coverity.mk
include $(RCS_FW_DIR)/scripts/mk/make_fw_ver.mk
