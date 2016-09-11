mcu = $(filter-out makefile,$(notdir $(wildcard *)))

all test: $(mcu)
#test: $(mcutarget)

$(mcu): FORCE
	cd ./$@ && $(MAKE) $(MAKECMDGOALS)

FORCE: 

clean:
	-rm ./stm32f3/obj/*.o
	-rm ./stm32f3/obj/*.d
	-rm ./stm32f4/obj/*.o
	-rm ./stm32f4/obj/*.d
	
	
help:
	@echo ">make mcu=targetname,  builds mcal for the specified target on linux"
	@echo ">make mcu=targetname host=win,  builds mcal for the specified target on windows"
	@echo ">make all, builds mcal module for all target mcu's on linux machine"
	@echo ">make all host=win builds mcal module for all target mcu's on windows machine"
	@echo " >make test, builds and runs unit tests on the current host machine"