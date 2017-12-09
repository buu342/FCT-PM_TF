############################ Sexy Makefile ##############################
####################### Now with 30% more colors! #######################

ask: .
	@clear
	@/bin/echo -e "\x1b[31mWhat do you want made?\nTry \x1b[36m'make gest'\x1b[31m or \x1b[36m'make gera'\x1b[31m.\x1b[0m\n"

gest: start_make make_gest clean_o
	@/bin/echo -e "\x1b[32mDone!\x1b[0m\n"

start_make:
	@clear
	@/bin/echo -e "\x1b[31mStarting gest compiler.\x1b[0m\n"


########################### Program Recipie #############################

make_gest: make_main make_menu make_store make_list make_gera make_analysis make_reserve
	@echo Merging .o files
	@gcc -o gest ./bin/*.o


######################### Program Ingredients ###########################
### C knows which header files to use, so compile WITH ALL OF THEM 😈 ###

make_main: ./src/main_gest.c ./src/headers/*.h
	@echo Creating main.o
	@gcc -c ./src/main_gest.c -Wall
	@mv *.o ./bin

make_menu: ./src/menu.c ./src/headers/*.h
	@echo Creating menu.o
	@gcc -c ./src/menu.c -Wall
	@mv *.o ./bin

make_store: ./src/store.c ./src/headers/*.h
	@echo Creating store.o
	@gcc -c ./src/store.c -Wall
	@mv *.o ./bin

make_list: ./src/list.c ./src/headers/*.h
	@echo Creating list.o
	@gcc -c ./src/list.c -Wall
	@mv *.o ./bin

make_gera: ./src/gera.c ./src/headers/*.h
	@echo Creating gera.o
	@gcc -c ./src/gera.c -Wall
	@mv *.o ./bin

make_analysis: ./src/analysis.c ./src/headers/*.h
	@echo Creating analysis.o
	@gcc -c ./src/analysis.c -Wall
	@mv *.o ./bin

make_reserve: ./src/reserve.c ./src/headers/*.h
	@echo Creating reserve.o
	@gcc -c ./src/reserve.c -Wall
	@mv *.o ./bin



############################ Cleanup Crew ##############################

clean_o:
	@/bin/echo -e "Cleaning up .o files\n"
	@rm -rf ./bin/*.o

clean:
	@clear
	@/bin/echo -e "\x1b[31mCleaning up everything as requested.\x1b[0m\n"
	@echo Removing .o files.
	@rm -rf *.o
	@echo Removing compiled program.
	@rm -rf gest
	@/bin/echo -e "\n\x1b[32mDone!\x1b[0m\n"
