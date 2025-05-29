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

.PHONY: rcs ax rx tx cal clean ax_clean rx_clean tx_clean cal_clean radio

rcs: ax rx tx cal
clean: ax_clean rx_clean tx_clean cal_clean

ax:
	$(MAKE) -C ax $@

rx:
	$(MAKE) -C rx $@

tx:
	$(MAKE) -C tx $@

cal:
	$(MAKE) -C cal $@

ax_clean:
	$(MAKE) -C ax clean

rx_clean:
	$(MAKE) -C rx clean

tx_clean:
	$(MAKE) -C tx clean

cal_clean:
	$(MAKE) -C cal clean

unit_clean:
	$(MAKE) -C com unit_clean

radio:
	../ipcommon/fw/table_utils/table_utils.sh --c2h msg/csv/rm -d msg/inc --msg com_rm --html_dir msg/html --no_msg_dic_gen
radio_xlsx:
	../ipcommon/fw/table_utils/table_utils.sh --c2x msg/csv/rm -d msg/csv/rm --xlsx rm.xlsx --no_msg_dic_gen
radio_csv:
	../ipcommon/fw/table_utils/table_utils.sh --x2h msg/csv/rm/rm.xlsx -d /tmp/rm --msg test_msg --no_test --no_msg_dic_gen
	@rm -rf /tmp/rm
	../ipcommon/fw/table_utils/table_utils.sh --x2c msg/csv/rm/rm.xlsx -d msg/csv/rm --no_msg_dic_gen
radio_clean:
	@rm -rf msg/csv/rm/rm.xlsx
	@rm -rf msg/inc/com_rm_msg.h
	@rm -rf msg/html/com_rm.html
