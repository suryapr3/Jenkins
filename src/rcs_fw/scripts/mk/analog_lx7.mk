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

CPU = hwc_adc_lx7

TOOLS_BASE ?= /workspace/hw/xne/tools
SWTOOLS_ANA ?= $(TOOLS_BASE)/RI-2022.9-linux/XtensaTools

CC = $(SWTOOLS_ANA)/bin/xt-clang
CCP = $(SWTOOLS_ANA)/bin/xt-clang++
SIZE = $(SWTOOLS_ANA)/bin/xt-size
DUMP = $(SWTOOLS_ANA)/bin/xt-objdump
SRAM = $(SWTOOLS_ANA)/bin/xt-dumpelf

DRAM_START=0x10000
DRAM_SIZE =0x10000
DRAM_OFFSET=0
IRAM_START=0x20000
IRAM_SIZE =0x10000
#SRAM_START=0x30000
#SRAM_SIZE= 0x20000

ifeq ($(TARGET),sim)
LDFLAGS += -mlsp=$(PRJDIR)/scripts/lsp/$(TARGET)/$(PROG)
else
LDFLAGS += -mlsp=$(PRJDIR)/scripts/lsp/$(TARGET)/$(PROG)
endif

