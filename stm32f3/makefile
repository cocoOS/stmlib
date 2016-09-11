#default values for host and mcu
host = linux
mcu = stm32f3

include includes
include ../../../flags.mk


outputdir = ./obj
srcdir = ./src

modpath = ../../../modules

#Unit test
TESTSRC = ./test
UTESTSRC = ../../../punit/src/test.c
UTESTINC = ../../../punit/inc

objects = $(patsubst $(srcdir)/%.c,$(outputdir)/%.o,$(wildcard $(srcdir)/*.c))


# list of all modules that the application depends on


# for each module, define the module object files. 


ifeq ($(MAKECMDGOALS), test)
	COMPILE_CPP = g++ -c -Wall -g3
	COMPILE_C = cc -c -Wall -g3
endif

all: $(objects)

$(outputdir)/%.o: $(srcdir)/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@	

	

testframework: $(UTESTSRC)
	cc -c -I$(UTESTINC) $(DEFINES) $^ -o $(outputdir)/testframework.o	

test: testframework $(objects) $(testobjects)
	@echo .
	@echo "linking unittests"
	g++ -o $(outputdir)/testprog $(outputdir)/testframework.o $(testobjects) $(objects)
	@echo .
	@echo "running tests"
	$(outputdir)/testprog


test: includes = $(testincludes)


clean:
	rm $(outputdir)/*.o
	rm $(outputdir)/*.d

help: 
	@echo " >make all, builds mcal and stm files for arm on linux machine"
	@echo " >make all host=win, builds mcal and stm files for arm on windows machine"
	@echo " >make test, builds and runs unit tests on the current host machine"
	
	