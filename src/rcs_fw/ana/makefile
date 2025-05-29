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

PROG = ana

INCLUDEDIRS += 	../com/inc \
				../ipcommon/hw_inc \
				../ipcommon/fw/com/inc \
				inc \
				slicecal/inc \
				../rcs/com/inc


SOURCEDIRS =	../com/src \
				src \
				slicecal/src

CSOURCES += ../rcs/com/src/com_heap.c
VPATH += ../rcs/com/src
ifeq ($(UNIT),1)
  UNIT_TESTS = $(notdir $(shell ls -1 unit/*.c))
  SOURCEDIRS += unit/data
endif
CCFLAGS += -fdata-sections -ffunction-sections
ifeq ($(UNIT),1)
	ifeq ($(PROFILE),1)
        DEFINES += -DDO_PROFILE=1
		DEFINES += -DPRINT_C_PRINTF=0
		CCFLAGS += -O3
	else
		CCFLAGS += -O0
	endif
else
	CCFLAGS += -O3
endif
include ../scripts/mk/make_common.mk
