/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h>     // For use of the exit and system functions
#include <stdio_ext.h>  // For use of the __fpurge function


/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/store.h"
#include "headers/list.h"
#include "headers/gera.h"
#include "headers/econ.h"
#include "headers/menu.h"


/*--------------------------------------------------------------
                        press_enter
        Handles the "Press Enter to continue" message
--------------------------------------------------------------*/

void press_enter()
{
    printf(cr_magenta "Prima Enter para continuar." cr_reset);
    int i=0;
    char c;
    while(1) // I have to do this to stop getchar from reading the first enter keystroke.
    {
        c = getchar();
        if (c == '\n' && i>0)
            break;
        else
            i++;
    }
}


/*--------------------------------------------------------------
                            Menu
        Used for selecting which functions to execute
--------------------------------------------------------------*/

void menu(PASSENGER *passengers)
{
    int doOption;           // Allows us to refresh the menu once a function has been completed
    char o;                 // To   select a menu option
    int database_loaded;    // To make sure the user has sucessfully loaded a database in the main.

    if (passengers[50].id == 0) // If the user loaded a database via ./gest FILE, detect the database is loaded
        database_loaded = 0;
    else
        database_loaded = 1;

    while (1)
    {
        doOption = 1;
        system("clear");

        printf(cr_green "\tCompanhia de Aviação “Ja Fui”\n" cr_green);
        printf(cr_green "\t    Programa de Reservas\n\n\n" cr_green);
        printf(cr_cyan "0 " cr_reset "– Sair do programa\n");
        printf(cr_cyan "1 " cr_reset "– Ler ficheiro de texto\n");
        printf(cr_cyan "2 " cr_reset "– Ler ficheiro binário\n");
        printf(cr_cyan "3 " cr_reset "– Listar passageiros de um voo\n");
        printf(cr_cyan "4 " cr_reset "– Número de passageiros de um período de dias\n");
        printf(cr_cyan "5 " cr_reset "– Escrita em ficheiro\n");
        printf(cr_cyan "6 " cr_reset "– Análise económica\n");
        printf(cr_cyan "7 " cr_reset "– Passageiros em duas escalas\n");
        printf(cr_cyan "8 " cr_reset "– Reserva simples de um voo\n\n");
        printf(cr_magenta "Qual opção quer? " cr_reset);
        
        while (doOption)
        {

            scanf(" %c", &o);
            switch (o)
            {
                case '0':
                    system("clear");
                    printf("Adeus!\n\n");
                    exit(0);
                    break;
                case '1':
                    database_loaded = store_text(passengers, NULL); // The NULL will make the function see it has no filename, so it will prompt one from the user
                    doOption = 0;
                    break;
                case '2':
                    database_loaded = store_binary(passengers, NULL);
                    doOption = 0;
                    break;
                case '3':
                    if (database_loaded == 1)
                        list_passengers(passengers, 0, 0);
                    else    
                        printf(cr_red "É necessário ler um ficheiro de texto ou binário antes de correr esta ação.\n\n" cr_reset);
                    press_enter();
                    doOption = 0;
                    break;
                case '4':
                    if (database_loaded == 1)
                        ten_day_table(passengers);
                    else    
                        printf(cr_red "É necessário ler um ficheiro de texto ou binário antes de correr esta ação.\n\n" cr_reset);
                    press_enter();
                    doOption = 0;
                    break;
                case '5':
                    if (database_loaded == 1)
                        write_textfile(passengers);
                    else    
                        printf(cr_red "É necessário ler um ficheiro de texto ou binário antes de correr esta ação.\n\n" cr_reset);
                    press_enter();
                    doOption = 0;
                    break;
                case '6':
                    if (database_loaded == 1)
                        economic_analysis(passengers);
                    else    
                        printf(cr_red "É necessário ler um ficheiro de texto ou binário antes de correr esta ação.\n\n" cr_reset);
                    press_enter();
                    doOption = 0;
                    break;
                case '7':
                case '8':
                default:
                    printf(cr_red "Opção inválida." cr_magenta " Tente outra: " cr_reset);
                    __fpurge(stdin);
                    break;
            }
        }
    }
}
