mcu = $(filter-out makefile,$(notdir $(wildcard *)))

all: $(mcu)

$(mcu): FORCE
	cd ./$@ && $(MAKE) $(MAKECMDGOALS)

FORCE: 

clean:
	-rm ./stm32f3/obj/*.o
	-rm ./stm32f3/obj/*.d
	-rm ./stm32f4/obj/*.o
	-rm ./stm32f4/obj/*.d
	-rm ./stm32f446/obj/*.o
	-rm ./stm32f446/obj/*.d
	
	
help:
	@echo ">make mcu=targetname,  builds for the specified target"
	@echo ">make all, builds module for all target mcu's"

