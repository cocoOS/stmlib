#default values for host and mcu
host = linux
mcu = stm32f4

include includes
include ../../../flags.mk


outputdir = ./obj
srcdir = ./src ./usb/src
#usbsrcdir = ./usb/src
modpath = ../../../modules

# for each source path above, collect all .cpp, .c and .s files. These are the application sources.
sources = $(foreach path, $(srcdir), $(notdir $(wildcard $(path)/*.c)))

# from the sources, define the application object files.
objects = $(patsubst %,$(outputdir)/%,$(addsuffix .o,$(basename $(sources))))

all: $(objects)


$(outputdir)/%.o: ./src/%.c
	$(COMPILE_C) $(includes) -DHSE_VALUE=8000000  $^ -o $@

$(outputdir)/%.o: ./usb/src/%.c
	$(COMPILE_C) $(includes) -DHSE_VALUE=8000000  $^ -o $@


	
clean:
	rm $(outputdir)/*.o
	rm $(outputdir)/*.d
	
help: 
	@echo " >make all, builds mcal and stm files for arm on linux machine"
	@echo " >make all host=win, builds mcal and stm files for arm on windows machine"
	@echo " >make test, builds and runs unit tests on the current host machine"