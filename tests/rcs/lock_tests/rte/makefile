include $(PROJECT_HOME)/common.mk
include $(SRP_RTE)/flags.mk

TESTNAME = lock_tests
TESTFILE = srpRcsLock
#PROJECT_HOME = $(SRP_SRC)/..
TEST_FWK_INC = -I$(PROJECT_HOME)/src/hw_inc -I$(PROJECT_HOME)/src/common
TEST_FWK_LIBS = $(PROJECT_HOME)/src/common

VERBOSE = TRUE

CFLAGS+= -Wall -fpic -shared
#CFLAGS =

# -fpic -shared
SRC = \
	  $(TESTFILE).c

HOST_OBJ = $(SRC:.c=.o)

SRP_INCLUDE = -I$(SRP_RTE)/include $(TEST_FWK_INC)
SRP_LD_FLAGS = -L$(SRP_RTE)/lib -lSrp -lVex -lRcs
#SRP_INCLUDE+= -I$(SRP_SRC)/include

default: $(TESTNAME).so

clean:
	rm -rf obj *.o $(TESTFILE) $(TESTNAME).so

$(TESTNAME).so: $(TESTFILE).o obj
	$(CC) $(CFLAGS) $(SRP_INCLUDE) $(SRP_LD_FLAGS) $< $(wildcard obj/*) -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) $(SRP_INCLUDE) -c $? -o $@

obj:
		mkdir obj
		for dir in $(TEST_FWK_LIBS); do \
				echo $$dir; \
				cd $$dir; \
				echo pwd; \
				$(CC) -c $(CFLAGS) *.c $(TEST_FWK_INC); \
				mv *.o $(CURDIR)/obj; \
				cd -; \
		done
