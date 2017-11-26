############################# Sexy Makefile #############################
SRC=main.c
all: menu
menu: menu.o main.o 
        gcc -o menu menu.o main.o

menu.o: menu.c
        gcc -o menu.o -c menu.c -Wall

main.o: $(SRC) menu.h
        gcc -o main.o -c $(SRC) -Wall
clean:
        rm -rf *.o
mrproper: clean
        rm -rf menu
