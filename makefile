############################ Sexy Makefile ##############################

all: program clean
	@echo done!

########################### Program Recipie #############################

program: main.o menu.o
	@echo merging .o files
	@gcc -o program main.o menu.o


######################### Program Ingridients ###########################

main.o: main.c menu.h	
	@echo creating main.o
	@gcc -c main.c -Wall

menu.o: menu.c
	@echo creating menu.o
	@gcc -c menu.c -Wall


############################ Cleanup Crew ##############################

clean:
	@echo cleaning up
	@rm -rf *.o
