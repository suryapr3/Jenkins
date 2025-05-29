PROG=factory
INCLUDEDIRS += inc \
			 ../ipcommon/hw_inc \
			 ../com/inc \
			 ../rcs/com/inc \
			 ../ipcommon/fw/com/inc \
			 ../ipcommon/fw/msg/inc \
			 ../rcs/cal/nleq/inc \
			 ../ipcommon/fw/tables/inc \
			 $(TOOLS_BASE)/eigen \
			 ../rcs/cal/inc

SOURCEDIRS = src \
			 ../rcs/com/src \
			 ../com/src \
			 ../rcs/cal/nleq/src \
			 ../rcs/cal/src
CSOURCES += ../ipcommon/fw/tables/src/com_tables.c \
			../ipcommon/fw/tables/src/cal_tables.c
EXCLUDE_OBJ = $(OBJDIR)/cal_main.o

VPATH += ../ipcommon/fw/tables/src

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
DEFINES += -DLTLFTF_HANDCODED=1

include ../scripts/mk/make_common.mk
