
include includes
CPP_COMPILE_PATH = /home/peter/opt/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi-g++
C_COMPILE_PATH =   /home/peter/opt/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi-gcc
ASSEM_PATH =       /home/peter/opt/gcc-arm-none-eabi-6-2017-q2-update/bin/arm-none-eabi-gcc


CPP_FLAGS = -c -mcpu=cortex-m3 -mthumb -mlittle-endian -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fno-threadsafe-statics -g3 -ggdb -std=gnu++11 -fabi-version=0 -MMD -MP
C_FLAGS =   -c -mcpu=cortex-m3 -mthumb -mlittle-endian -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -ggdb -std=gnu11 -nostdlib -MMD -MP
ASSEM_FLAGS = -mcpu=cortex-m3 -mthumb -mlittle-endian -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -ggdb -x assembler-with-cpp



COMPILE_C = $(C_COMPILE_PATH) $(C_FLAGS)
COMPILE_CPP = $(CPP_COMPILE_PATH) $(CPP_FLAGS)
ASSEM = $(ASSEM_PATH) $(ASSEM_FLAGS)

outputdir = ./obj
srcdir = ./src ./usb_drv/src


# for each source path above, collect all .cpp, .c and .s files. These are the application sources.
sources = $(foreach path, $(srcdir), $(notdir $(wildcard $(path)/*.c)))

# from the sources, define the application object files.
objects = $(patsubst %,$(outputdir)/%,$(addsuffix .o,$(basename $(sources))))

all: $(objects)

$(outputdir)/%.o: ./src/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@

$(outputdir)/%.o: ./usb_drv/src/%.c
	$(COMPILE_C) $(includes) -DSTM32F30X $^ -o $@



clean:
	rm $(outputdir)/*.o
	rm $(outputdir)/*.d

help: 
	@echo " >make all, builds stm files for arm o"
	
names: 
	@echo $(objects)
	
