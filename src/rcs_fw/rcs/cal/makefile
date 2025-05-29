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

PROG = cal

INCLUDEDIRS = ../../com/inc \
			  ../com/inc \
			  ../com/xtensa \
			  ../../ipcommon/fw/tables/inc \
			  ../../ipcommon/fw/msg/inc \
			  ../../ipcommon/fw/com/inc \
			  inc \
			  $(TOOLS_BASE)/eigen \
			  ./nleq/inc

SOURCEDIRS = ../../com/src \
			 ../com/src \
			 ../com/xtensa \
			 src \
			 ./nleq/src
#Common tables and tables for core required

CSOURCES += ../../ipcommon/fw/tables/src/com_tables.c \
            ../../ipcommon/fw/tables/src/$(PROG)_tables.c

VPATH += ../../ipcommon/fw/tables/src

ASFLAGS += -fdata-sections -ffunction-sections
CCFLAGS += -fdata-sections -ffunction-sections -mlongcalls
CPPFLAGS += -std=c++17 -mlongcalls -LNO:simd $(VERBOSE) -fdata-sections -LNO:simd_agg_if_conv -fno-threadsafe-statics -ffunction-sections -stdlib=libc++-re
DEFINES += -DPROC_HWC_RCS_KP1
DEFINES += -DCONFIG_HWC_RCS_KP1
DEFINES += -DEIGEN_USE_XTENSA_PKTMATH=1
DEFINES += -DEIGEN_MAX_ALIGN_BYTES=128
DEFINES += -DEIGEN_MAX_STATIC_ALIGN_BYTES=128
DEFINES += -DDEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT=1
DEFINES += -DEIGEN_USE_XTENSA_DSPLIB=0
ifeq ($(UNIT),1)
  UNIT_TESTS_CPP = $(notdir $(shell ls -1 unit/*.cpp))
  SOURCEDIRS += unit/data
  DEFINES += -DDO_INJECT=1
  DEFINES += -DDO_PRINTF=1
  DEFINES += -DLOG_TO_FILE=1
  ifeq ($(PROFILE),1)
        DEFINES += -DDO_PROFILE=1
        DEFINES += -DDO_PRINTF_MATRIX=0
		DEFINES += -DPRINT_C_PRINTF=0
  else
  	DEFINES += -DDO_PROFILE=0
  	DEFINES += -DDO_PRINTF_MATRIX=1

  endif
endif
DEFINES += -DLTLFTF_HANDCODED=1
include ../../scripts/mk/make_common.mk
