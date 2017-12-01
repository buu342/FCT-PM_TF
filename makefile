############################ Sexy Makefile ##############################

all: start_make make_gest clean_o
	@echo Done!

start_make:
	@clear
	@echo Starting program maker.

########################### Program Recipie #############################

make_gest: make_main make_menu
	@echo Merging .o files
	@gcc -o gest main.o menu.o


######################### Program Ingredients ###########################

make_main: ./src/main.c ./src/headers/menu.h	
	@echo Creating main.o
	@gcc -c ./src/main.c -Wall

make_menu: ./src/menu.c
	@echo Creating menu.o
	@gcc -c ./src/menu.c -Wall


############################ Cleanup Crew ##############################

clean_o:
	@echo Cleaning up .o files
	@rm -rf *.o

clean:
	@echo Cleaning up everything as requested
	@rm -rf *.o
	@rm -rf gest
	@echo Done!
