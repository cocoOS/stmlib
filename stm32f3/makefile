#default values for host and mcu
host = linux
mcu = stm32f3

include includes
include ../../../flags.mk


outputdir = ./obj
srcdir = ./src ./usb_drv/src

modpath = ../../../modules

# for each source path above, collect all .cpp, .c and .s files. These are the application sources.
sources = $(foreach path, $(srcdir), $(notdir $(wildcard $(path)/*.c)))

# from the sources, define the application object files.
objects = $(patsubst %,$(outputdir)/%,$(addsuffix .o,$(basename $(sources))))


#objects = $(patsubst $(srcdir)/%.c,$(outputdir)/%.o,$(wildcard $(srcdir)/*.c))
# list of all modules that the application depends on


# for each module, define the module object files. 

all: $(objects)

$(outputdir)/%.o: ./src/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@

$(outputdir)/%.o: ./usb_drv/src/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@



clean:
	rm $(outputdir)/*.o
	rm $(outputdir)/*.d

help: 
	@echo " >make all, builds mcal and stm files for arm on linux machine"
	@echo " >make all host=win, builds mcal and stm files for arm on windows machine"
	@echo " >make test, builds and runs unit tests on the current host machine"
	
names: 
	@echo $(objects)
	