#default values for host and mcu
host = linux
mcu = stm32f4

include includes
include ../../../flags.mk


outputdir = ./obj
srcdir = ./src
stmsrcdir = ./stm/src
usbsrcdir = ./usb/src
modpath = ../../../modules

#Unit test
TESTSRC = ./test
UTESTSRC = ../../../punit/src/test.c
UTESTINC = ../../../punit/inc

objects = $(patsubst $(srcdir)/%.cpp,$(outputdir)/%.o,$(wildcard $(srcdir)/*.cpp))
stmobjects = $(patsubst $(stmsrcdir)/%.c,$(outputdir)/%.o,$(wildcard $(stmsrcdir)/*.c))
usbobjects = $(patsubst $(usbsrcdir)/%.c,$(outputdir)/%.o,$(wildcard $(usbsrcdir)/*.c))
testobjects = $(subst $(TESTSRC)/,$(outputdir)/,$(patsubst %.cpp, %.o, $(wildcard $(TESTSRC)/*.cpp)))

# list of all modules that the application depends on
moddeps = utils

# for each module, define the module object files. 
moduleobjs = $(foreach module, $(moddeps), $(wildcard $(modpath)/$(module)/$(mcu)/obj/*.o) ) $(foreach module, $(moddeps), $(wildcard $(modpath)/$(module)/common/obj/*.o) )


ifeq ($(MAKECMDGOALS), test)
	COMPILE_CPP = g++ -c -Wall -g3
	COMPILE_C = cc -c -Wall -g3
endif

all: $(objects) $(stmobjects) $(usbobjects) $(moddeps)


$(moddeps) : 
	cd $(modpath)/$@ && $(MAKE)
	
$(outputdir)/%.o: $(srcdir)/%.cpp
	$(COMPILE_CPP) $(includes) $^ -o $@
	
$(outputdir)/%.o: $(stmsrcdir)/%.c
	$(COMPILE_C) $(includes) -DHSE_VALUE=8000000  $^ -o $@

$(outputdir)/%.o: $(usbsrcdir)/%.c
	$(COMPILE_C) $(includes) -DHSE_VALUE=8000000  $^ -o $@

$(outputdir)/%.o: $(TESTSRC)/%.cpp
	$(COMPILE_CPP) $(testincludes) -I$(UTESTINC)  $^ -o $@

testframework: $(UTESTSRC)
	cc -c -I$(UTESTINC) $(DEFINES) $^ -o $(outputdir)/testframework.o	

test: testframework $(objects) $(testobjects)
	@echo .
	@echo "linking unittests"
	g++ -o $(outputdir)/testprog $(outputdir)/testframework.o $(objects) $(testobjects)
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