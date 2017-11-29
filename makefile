############################ Sexy Makefile ##############################

all: gest clean_o
	@echo done!

########################### Program Recipie #############################

gest: main.o menu.o
	@echo merging .o files
	@gcc -o gest main.o menu.o


######################### Program Ingredients ###########################

main.o: ./src/main.c ./src/headers/menu.h	
	@echo creating main.o
	@gcc -c ./src/main.c -Wall

menu.o: ./src/menu.c
	@echo creating menu.o
	@gcc -c ./src/menu.c -Wall


############################ Cleanup Crew ##############################

clean_o:
	@echo cleaning up .o files
	@rm -rf *.o

clean:
	@echo Cleaning up everything as requested
	@rm -rf *.o
	@rm -rf gest
	@echo Done!
