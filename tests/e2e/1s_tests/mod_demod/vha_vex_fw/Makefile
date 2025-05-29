DUT = abc_vex40
SYSTEM = ${DUT}_system
METHODS  = sim_m64
CPU = HostProcessor
VECTOR_ENGINE = ve32

HOST_FILES = host.c
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

PROGRAMS =  vex2vha vha2vex_p5_8iq vha2vex_p25iq producer_prog

HIVE_CFLAGS  = -html -verbose -Wall -O3 -save-temps \
               -I${HIVE_INSTALL}/include\
               -Whtmlgen,-issued-rf-pressure

vex2vha_CELL    = ${VECTOR_ENGINE}
vex2vha_FILES   = vex2vha.c
vex2vha_CFLAGS  = ${HIVE_CFLAGS}
vex2vha_LDFLAGS = ${HIVE_LDFLAGS}

vha2vex_p5_8iq_CELL    = ${VECTOR_ENGINE}
vha2vex_p5_8iq_FILES   = vha2vex_p5_8iq.c
vha2vex_p5_8iq_CFLAGS  = ${HIVE_CFLAGS}
vha2vex_p5_8iq_LDFLAGS = ${HIVE_LDFLAGS}

producer_prog_CELL    = ${VECTOR_ENGINE}
producer_prog_FILES   = producer.hive.c
producer_prog_CFLAGS  = ${HIVE_CFLAGS}
producer_prog_LDFLAGS = ${HIVE_LDFLAGS}

vha2vex_p25iq_CELL    = ${VECTOR_ENGINE}
vha2vex_p25iq_FILES   = vha2vex_p25iq.c
vha2vex_p25iq_CFLAGS  = ${HIVE_CFLAGS}
vha2vex_p25iq_LDFLAGS = ${HIVE_LDFLAGS}


# hivesim simulator options
#SIM_ARGUMENTS += --config_file ${PROJ_DIR}/abc_ve32_system_sim.cfg

include $(HIVEBIN)/../share/apps/hive_make.mk
