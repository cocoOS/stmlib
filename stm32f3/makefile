#default values for host and mcu
host = linux
mcu = stm32f3

include includes
include ../../../flags.mk


outputdir = ./obj
srcdir = ./src
stmsrcdir = ./stm/src

modpath = ../../../modules

#Unit test
TESTSRC = ./test
UTESTSRC = ../../../punit/src/test.c
UTESTINC = ../../../punit/inc

objects = $(patsubst $(srcdir)/%.cpp,$(outputdir)/%.o,$(wildcard $(srcdir)/*.cpp))
stmobjects = $(patsubst $(stmsrcdir)/%.c,$(outputdir)/%.o,$(wildcard $(stmsrcdir)/*.c))
testobjects = $(subst $(TESTSRC)/,$(outputdir)/,$(patsubst %.cpp, %.o, $(wildcard $(TESTSRC)/*.cpp)))

# list of all modules that the application depends on
moddeps = utils

# for each module, define the module object files. 
moduleobjs = $(foreach module, $(moddeps), $(wildcard $(modpath)/$(module)/$(mcu)/obj/*.o) ) $(foreach module, $(moddeps), $(wildcard $(modpath)/$(module)/common/obj/*.o) )


ifeq ($(MAKECMDGOALS), test)
	COMPILE_CPP = g++ -c -Wall -g3
	COMPILE_C = cc -c -Wall -g3
endif

all: $(objects) $(stmobjects) $(moddeps)

$(moddeps) : 
	cd $(modpath)/$@ && $(MAKE)

$(outputdir)/%.o: $(srcdir)/%.cpp
	$(COMPILE_CPP) $(includes) -DSTM32F30X $^ -o $@

$(outputdir)/%.o: $(stmsrcdir)/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@	

$(outputdir)/%.o: $(TESTSRC)/%.cpp
	$(COMPILE_CPP) $(testincludes) -I$(UTESTINC) -DSTM32F30X -c $^ -o $@
	

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
	
	