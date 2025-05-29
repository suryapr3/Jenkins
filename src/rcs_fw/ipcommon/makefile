###################################################################################################
#
# INTEL CONFIDENTIAL
#
# Copyright (C) 2023 Intel Corporation
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

# table related defines:
TABLE_UTILS = fw/table_utils/table_utils.sh
FW_TABLES_CSV_DIR = fw/tables/csv
FW_TABLES_INC_DIR = fw/tables/inc
FW_TABLES_SRC_DIR = fw/tables/src
FW_TABLES_PYINC_DIR = fw/tables/py_inc
FW_TABLES_HTML_DIR = fw/tables/html
FW_MSG_CSV_DIR = fw/msg/csv
FW_MSG_INC_DIR = fw/msg/inc
FW_MSG_HTML_DIR = fw/msg/html

# These are for test-compiling srp/ and fw/ files vs RTE.
RTE_BASE ?= fw/srp/rte
RTE_INCLUDES=-I$(RTE_BASE)/modules/common/api -I$(RTE_BASE)/modules/dev/ -I$(RTE_BASE)/include
FW_INCLUDES=-Ifw/com/inc -Ifw/msg/inc -Ifw/tables/inc -Ifw/srp/inc


.PHONY: all clean tables tables_unit

all: headermake tables

headermake: ./test/test_header.c
	@mkdir -p out
	gcc -o ./out/test_header.out ./test/test_header.c

srp: $(RTE_BASE)
	@mkdir -p out
	gcc -o ./out/fw_msg_queue.o -Wall -Ihw_inc $(FW_INCLUDES) -c fw/com/src/fw_msg_queue.c
	gcc -o ./out/srp_rcs_msg_if.o -Wall -Ihw_inc $(FW_INCLUDES) $(RTE_INCLUDES) -c fw/srp/src/srp_rcs_msg_if.c
	gcc -o ./out/srp_rcs_queue_if.o -Wall -Ihw_inc $(FW_INCLUDES) $(RTE_INCLUDES) -c fw/srp/src/srp_rcs_queue_if.c
	gcc -o ./out/srp_rcs_device_if.o -Wall -Ihw_inc $(FW_INCLUDES) $(RTE_INCLUDES) -c fw/srp/src/srp_rcs_device_if.c
	gcc -o ./out/test_srp_header.o -Wall  -Ihw_inc $(FW_INCLUDES) $(RTE_INCLUDES) -c test/test_srp_header.c

$(RTE_BASE):
	@echo 
	@echo "RPC test build requires RTE clone linked to $(RTE_BASE)"
	@echo 
	@ls $(RTE_BASE)


clean:
	rm -rf ./out

table_clean:
	rm -rf $(FW_TABLES_HTML_DIR)/*.html
	rm -rf $(FW_TABLES_INC_DIR)/*.h
	rm -rf $(FW_TABLES_PYINC_DIR)/*.py
	rm -rf $(FW_MSG_HTML_DIR)/*.html
	rm -rf $(FW_MSG_INC_DIR)/*_msg.h
	rm -rf $(FW_MSG_SRC_DIR)/*.c
	rm -rf $(FW_MSG_CSV_DIR)/*/*.xlsx
	rm -rf $(FW_TABLES_CSV_DIR)/cal/*.xlsx
	rm -rf $(FW_TABLES_CSV_DIR)/com/*.xlsx
	rm -rf $(FW_TABLES_CSV_DIR)/*/static/*.xlsx
#table_unit_clean:
#	rm -rf ../rcs/com/unit/com_tables_test.c
#	rm -rf ../rcs/ax/unit/ax_tables_test.c
#	rm -rf ../rcs/rx/unit/rx_tables_test.c
#	rm -rf ../rcs/tx/unit/tx_tables_test.c
#	rm -rf ../rcs/cal/unit/cal_tables_test.c

tables: tables_com tables_ax tables_rx tables_tx tables_cal tables_msg tables_csv2api
	find fw -name '*.[ch]' -exec clang-format -style=file -i {} \;

tables_com:
	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/com -d $(FW_TABLES_INC_DIR) --html_dir $(FW_TABLES_HTML_DIR) --hdr com_rf_def.h -m table_access_macros.h -s .dram0.com_tables.data -l 0xD000 --no_test --table_init $(FW_TABLES_SRC_DIR)/com_tables.c --ctypes_dir $(FW_TABLES_PYINC_DIR)
tables_ax:
	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/ax/static -d $(FW_TABLES_INC_DIR) --html_dir $(FW_TABLES_HTML_DIR) --hdr com_rf_def.h -m table_access_macros.h -s .dram0.ax_tables.data -l 0xD000 --no_test --table_init $(FW_TABLES_SRC_DIR)/ax_tables.c --ctypes_dir $(FW_TABLES_PYINC_DIR)
tables_rx:
	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/rx/static -d $(FW_TABLES_INC_DIR) --html_dir $(FW_TABLES_HTML_DIR) -m table_access_macros.h -s .dram0.rx_tables.data -l 0xD000 --no_test --table_init $(FW_TABLES_SRC_DIR)/rx_tables.c --ctypes_dir $(FW_TABLES_PYINC_DIR)
tables_tx:
	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/tx/static -d $(FW_TABLES_INC_DIR) --html_dir $(FW_TABLES_HTML_DIR) --hdr com_rf_def.h -m table_access_macros.h -s .dram0.tx_tables.data -l 0xD000 --no_test --table_init $(FW_TABLES_SRC_DIR)/tx_tables.c --ctypes_dir $(FW_TABLES_PYINC_DIR)
tables_cal:
	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/cal -d $(FW_TABLES_INC_DIR) --html_dir $(FW_TABLES_HTML_DIR) -m table_access_macros.h -s .dram0.cal_tables.data -l 0xD000 --no_test --table_init $(FW_TABLES_SRC_DIR)/cal_tables.c --ctypes_dir $(FW_TABLES_PYINC_DIR)

tables_csv2api:
	$(TABLE_UTILS) --csv2api $(FW_MSG_CSV_DIR)/tx:w  -d fw/srp/
	$(TABLE_UTILS) --csv2api $(FW_MSG_CSV_DIR)/rx:a -d fw/srp/
	$(TABLE_UTILS) --csv2api $(FW_MSG_CSV_DIR)/ad:a -d fw/srp/
	$(TABLE_UTILS) --csv2api $(FW_MSG_CSV_DIR)/set_time_ref:t -d fw/srp/

tables_msg:
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/tx -d $(FW_MSG_INC_DIR)/ --msg dl_req --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/rx -d $(FW_MSG_INC_DIR)/ --msg ul_req --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/rb -d $(FW_MSG_INC_DIR)/ --msg readback --hdr com_cpu_id.h com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/ad -d $(FW_MSG_INC_DIR)/ --msg admin --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/set_time_ref -d $(FW_MSG_INC_DIR)/ --msg set_time_ref --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/tx_spi -d $(FW_MSG_INC_DIR)/ --msg dl_spi_req --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)
	$(TABLE_UTILS) --c2h $(FW_MSG_CSV_DIR)/rx_spi -d $(FW_MSG_INC_DIR)/ --msg ul_spi_req --hdr com_msgs_enum.h --ctypes_dir $(FW_TABLES_PYINC_DIR) --html_dir $(FW_MSG_HTML_DIR)

#tables_unit:
#	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/com -d $(FW_TABLES_INC_DIR) -m table_access_macros.h --hdr com_rf_def.h -s .dram0.com_tables.data -l 0xD000 --table_init $(FW_TABLES_SRC_DIR)/com_tables.c --use_xtensa --test_file ../rcs/com/unit/com_tables_test.c --html_dir out
#	$(MAKE) -C ../rcs/com unit UNIT=1
#	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/ax/static -d $(FW_TABLES_INC_DIR) -m table_access_macros.h --hdr com_rf_def.h -s .dram0.ax_tables.data -l 0xD000 --table_init $(FW_TABLES_SRC_DIR)/ax_tables.c --use_xtensa --test_file ../rcs/ax/unit/ax_tables_test.c --html_dir out
#	$(MAKE) -C ../rcs/ax unit UNIT=1
#	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/rx/static -d $(FW_TABLES_INC_DIR) -m table_access_macros.h -s .dram0.rx_tables.data -l 0xD000 --table_init $(FW_TABLES_SRC_DIR)/rx_tables.c --use_xtensa --test_file ../rcs/rx/unit/rx_tables_test.c --html_dir out
#	$(MAKE) -C ../rcs/rx unit UNIT=1
#	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/tx/static -d $(FW_TABLES_INC_DIR) -m table_access_macros.h --hdr com_rf_def.h -s .dram0.tx_tables.data -l 0xD000 --table_init $(FW_TABLES_SRC_DIR)/tx_tables.c --use_xtensa --test_file ../rcs/tx/unit/tx_tables_test.c --html_dir out
#	$(MAKE) -C ../rcs/tx unit UNIT=1
#	$(TABLE_UTILS) --c2h $(FW_TABLES_CSV_DIR)/cal -d $(FW_TABLES_INC_DIR) -m table_access_macros.h -s .dram0.cal_tables.data -l 0xD000 --table_init $(FW_TABLES_SRC_DIR)/cal_tables.c --use_xtensa --test_file ../rcs/cal/unit/cal_tables_test.cpp --html_dir out
#	$(MAKE) -C ../rcs/cal unit UNIT=1

tables_xlsx:cal_xlsx com_xlsx ax_xlsx rx_xlsx tx_xlsx msg_xlsx

cal_xlsx:
	$(TABLE_UTILS) --c2x $(FW_TABLES_CSV_DIR)/cal/ -d $(FW_TABLES_CSV_DIR)/cal --xlsx rcs_cal.xlsx
com_xlsx:
	$(TABLE_UTILS) --c2x $(FW_TABLES_CSV_DIR)/com/ -d $(FW_TABLES_CSV_DIR)/com --xlsx rcs_com.xlsx
ax_xlsx:
	$(TABLE_UTILS) --c2x $(FW_TABLES_CSV_DIR)/ax/static/ -d $(FW_TABLES_CSV_DIR)/ax/static --xlsx rcs_ax_static.xlsx
rx_xlsx:
	$(TABLE_UTILS) --c2x $(FW_TABLES_CSV_DIR)/rx/static/ -d $(FW_TABLES_CSV_DIR)/rx/static --xlsx rcs_rx_static.xlsx
tx_xlsx:
	$(TABLE_UTILS) --c2x $(FW_TABLES_CSV_DIR)/tx/static/ -d $(FW_TABLES_CSV_DIR)/tx/static --xlsx rcs_tx_static.xlsx
msg_xlsx:
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/tx -d $(FW_MSG_CSV_DIR)/tx --xlsx tx.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/rx -d $(FW_MSG_CSV_DIR)/rx --xlsx rx.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/rb -d $(FW_MSG_CSV_DIR)/rb --xlsx rb.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/ad -d $(FW_MSG_CSV_DIR)/ad --xlsx ad.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/set_time_ref -d $(FW_MSG_CSV_DIR)/set_time_ref --xlsx set_time_ref.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/tx_spi -d $(FW_MSG_CSV_DIR)/tx_spi --xlsx tx_spi.xlsx
	$(TABLE_UTILS) --c2x $(FW_MSG_CSV_DIR)/rx_spi -d $(FW_MSG_CSV_DIR)/rx_spi --xlsx rx_spi.xlsx

# if you want to run table test, unset NO_TEST:
NO_TEST=--no_test
tables_csv: cal_csv com_csv ax_csv rx_csv tx_csv msg_csv
cal_csv:
	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/cal/rcs_cal.xlsx -d /tmp/cal $(NO_TEST)
	@rm -rf /tmp/cal
	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/cal/rcs_cal.xlsx -d $(FW_TABLES_CSV_DIR)/cal
com_csv:
	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/com/rcs_com.xlsx -d /tmp/com $(NO_TEST)
	@rm -rf /tmp/com
	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/com/rcs_com.xlsx -d $(FW_TABLES_CSV_DIR)/com
ax_csv:
	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/ax/static/rcs_ax_static.xlsx -d /tmp/ax $(NO_TEST)
	@rm -rf /tmp/ax
	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/ax/static/rcs_ax_static.xlsx -d $(FW_TABLES_CSV_DIR)/ax/static
rx_csv:
	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/rx/static/rcs_rx_static.xlsx -d /tmp/rx $(NO_TEST)
	@rm -rf /tmp/rx
	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/rx/static/rcs_rx_static.xlsx -d $(FW_TABLES_CSV_DIR)/rx/static
tx_csv:
	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/tx/static/rcs_tx_static.xlsx -d /tmp/tx $(NO_TEST)
	@rm -rf /tmp/tx
	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/tx/static/rcs_tx_static.xlsx -d $(FW_TABLES_CSV_DIR)/tx/static

# above can be replaced with below
#XLSX_TEST= cal/rcs_cal.xlsx com/rcs_com.xlsx ax/static/rcs_ax_static.xlsx rx/static/rcs_rx_static.xlsx tx/static/rcs_tx_static.xlsx
#tables_xlsx_test:$(XLSX_TEST)
#$(XLSX_TEST):
#	$(TABLE_UTILS) --x2h $(FW_TABLES_CSV_DIR)/$@ -d /tmp/$(basename $(notdir $@)) $(NO_TEST)
#	@rm -rf /tmp/$(basename $(notdir $@))
#	$(TABLE_UTILS) --x2c $(FW_TABLES_CSV_DIR)/$@ -d $(FW_TABLES_CSV_DIR)/$(dir $@))

MSG_CSV=tx rx rb ad set_time_ref tx_spi rx_spi
msg_csv:$(MSG_CSV)
$(MSG_CSV):
	$(TABLE_UTILS) --x2h $(FW_MSG_CSV_DIR)/$@/$@.xlsx -d /tmp/$@ $(NO_TEST) --msg test_msg --hdr com_msgs_enum.h
	@rm -rf /tmp/$@
	$(TABLE_UTILS) --x2c $(FW_MSG_CSV_DIR)/$@/$@.xlsx -d $(FW_MSG_CSV_DIR)/$@
