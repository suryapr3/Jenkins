PROJ_DIR = $(CURDIR)
DUT = abc_vex40
SYSTEM = ${DUT}_system
#METHODS  = sim_m64 system_vhdl
METHODS  = sim_m64
CPU = HostProcessor

VECTOR_ENGINE = ve32
VECTOR_ENGINE_DEFINES =


SYSTEM_LIBRARY_PATH=${HIVE_INSTALL}/systems/${SYSTEM}/lib64
OLD_LD_LIBRARY_PATH:=${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH = ${SYSTEM_LIBRARY_PATH}:${OLD_LD_LIBRARY_PATH}

HOST_FILES =

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
              -L${SYSTEM_LIBRARY_PATH} \
              -L${HIVE_INSTALL}/systems/${SYSTEM}/lib64/host/lib64

HOST_LDFLAGS = --verbose ${HOST_LFLAGS} \
               -lutilities

PROGRAMS = vex2any_prog

HIVE_CFLAGS  = -Wall -O3 -html  -Whtmlgen,-issued-rf-pressure -save-temps\
               -I${HIVE_INSTALL}/include

HIVE_LDFLAGS = -embed

$(PROGRAMS)_CELL    = ${VECTOR_ENGINE}
$(PROGRAMS)_FILES   = ${PROJ_DIR}/vex2any.hive.c
$(PROGRAMS)_CPPFLAGS = ${VECTOR_ENGINE_DEFINES}
$(PROGRAMS)_CFLAGS  = ${HIVE_CFLAGS}
$(PROGRAMS)_LDFLAGS = ${HIVE_LDFLAGS}


##inc_CFLAGS   += -Wvolcano,"-exhaustive-verbose"
##inc_CFLAGS   += -Wvolcano,"-trace-all"

# hivesim simulator options
#SIMULATOR_ARGS  = -rtl-listing -verbose -sim-cflags -sim-libs
# SystemC (ISS) based simulator options
#SIM_ARGUMENTS = --enable_listing --enable_statistics --enable_memory_dump --enable_verbose_analysis
#SIM_ARGUMENTS += --config_file ${PROJ_DIR}/sim/abc_vex40_system_sim.cfg

include ${HIVEBIN}/../share/apps/hive_make.mk
