#common make file that will take care of the flags needs to be included in Makefiles
#include this file in Makefile

include $(SRP_SRC)/flags.mk
INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common
LIBS = $(PROJECT_HOME)/src/common
#CC=gcc
CFLAGS = -fpic -shared
CFLAGS += -DBUILD_DIR=\"$(CURDIR)/\"
#CFLAGS += -DENABLE_VHA_CLK                       #if u want enable VHA_CLK uncomment this.
#CFLAGS += -DENABLE_V2D_CLK                       #if u want enable V2D_CLK uncomment this.
#CFLAGS += -DENABLE_JESD_CLK                      #if u want enable JESD_CLK uncomment this.
#CFLAGS += -DLOG_WARNING
#CFLAGS += -DLOG_ALL
#CFLAGS += -DLOG_ERROR
#CFLAGS += -DLOG_INFO
#CFLAGS += -DLOG_DEBUG
#CFLAGS += -DDISABLE_TIMESTAMP
DEPS = *.h
