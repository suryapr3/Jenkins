DUT = abc_vex40
SYSTEM = ${DUT}_system
METHODS  = sim_m64
CPU = HostProcessor
VECTOR_ENGINE = ve32

#HOST_FILES = host.c
HOST_CPPFLAGS =

HOST_INSTANCE = host

HOST_CPPFLAGS = -DHIVE_MULTIPLE_PROGRAMS
HOST_CFLAGS  = -g -w -std=c99 \
               -I$(HIVEBIN)/../include/hrt \
               -I${HIVE_INSTALL}/include \
               -I${HIVE_INSTALL}/cores/${CPU}/include \
               -I${HIVE_INSTALL}/systems/${SYSTEM}/include \
               -I${HIVE_INSTALL}/systems/${SYSTEM}/lib64/host/include \
               -I${HIVE_INSTALL}/include/utilities/include

HOST_LFLAGS = -L${HIVE_INSTALL}/lib \
              -L${HIVE_INSTALL}/cores/${CPU}/lib64 \
              -L${HIVE_INSTALL}/systems/${SYSTEM}/lib64/host/lib64

HOST_LDFLAGS = --verbose ${HOST_LFLAGS} \
               -lutilities

#PROGRAMS =  jesd_tx jesd_rx 
#PROGRAMS =  jesd_tx jesd_rx jesd_rx_1shot jesd_rx_tx_lpbk
PROGRAMS =  jesd_tx jesd_rx jesd_rx_tx_lpbk

#HIVE_CFLAGS  = -html -verbose -Wall -O3 -save-temps \
               -I${HIVE_INSTALL}/include\
               -Whtmlgen,-issued-rf-pressure

HIVE_CFLAGS  += -exhaustive-verbose -html -verbose -Wall -O3 -save-temps \
               -I${HIVE_INSTALL}/include\
               -Whtmlgen,-issued-rf-pressure

jesd_tx_CELL    = ${VECTOR_ENGINE}
jesd_tx_FILES   = vex_jesd_tx.c
jesd_tx_CFLAGS  = ${HIVE_CFLAGS}
jesd_tx_LDFLAGS = ${HIVE_LDFLAGS}

jesd_rx_CELL    = ${VECTOR_ENGINE}
jesd_rx_FILES   = vex_jesd_rx.c
jesd_rx_CFLAGS  = ${HIVE_CFLAGS}
jesd_rx_LDFLAGS = ${HIVE_LDFLAGS}

#jesd_rx_1shot_CELL    = ${VECTOR_ENGINE}
#jesd_rx_1shot_FILES   = vex_jesd_rx_1shot.c
#jesd_rx_1shot_CFLAGS  = ${HIVE_CFLAGS}
#jesd_rx_1shot_LDFLAGS = ${HIVE_LDFLAGS}

jesd_rx_tx_lpbk_CELL    = ${VECTOR_ENGINE}
jesd_rx_tx_lpbk_FILES   = vex_jesd_rx-tx_lpbk.c
jesd_rx_tx_lpbk_CFLAGS  = ${HIVE_CFLAGS}
jesd_rx_tx_lpbk_LDFLAGS = ${HIVE_LDFLAGS}

# hivesim simulator options
#SIM_ARGUMENTS += --config_file ${PROJ_DIR}/abc_ve32_system_sim.cfg

include $(HIVEBIN)/../share/apps/hive_make.mk
