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

CORE ?= tx

# specify test target and its corresponding flags:
DEFINES += -DGPDMA_TEST
TEST_TGT := v2d_gbuffer_mode2_update
# make sure your test file under ./src folder named as $(CORE)_$(TEST_TGT).c
CCFLAGS += -fforce-enable-int128

INCLUDEDIRS = ../../com/inc \
			  ../../rcs/com/inc \
			  ../../rcs/com/xtensa \
			  ../../ipcommon/fw/com/inc \
			  ../../ipcommon/fw/msg/inc \
			  ../../ipcommon/fw/tables/inc \
			  ../../rcs/msgs/inc \
			  ../../rcs/tables/inc \
			  inc

SOURCEDIRS = ../../com/src \
			 ../../rcs/com/src \
			 ../../rcs/com/xtensa
			 
# in case need to exclude other *_main.c/*_main.cpp file
# EXCLUDE_OBJ = $(OBJDIR)/$(CORE)_main.o

include ../../scripts/mk/make_test_tgt.mk

