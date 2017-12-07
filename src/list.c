/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h>     // For use of the system function
#include <stdio_ext.h>  // For use of the __fpurge function
#include <string.h>     // For use of strcmp


/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/list.h"


/*--------------------------------------------------------------
                        list_passengers
            Lists passengers of a specific flight
        Also returns how many people between those flights
--------------------------------------------------------------*/

int list_passengers(PASSENGER *passengers, int day_check, int flight_check)
{
    int i=0, j=0;
    int do_print = 0;
    int flight_first_line=-1, flight_last_line=0; // For knowing which lines to read when printing.
    char origem_dest[9][2][11]= 
    { 
        {"Lisboa    ", "Amesterdao"},
        {"Lisboa    ", "Frankfurt "},
        {"Lisboa    ", "Milao     "},
        {"Amesterdao", "Berlim    "},
        {"Amesterdao", "Bucareste "},
        {"Frankfurt ", "Varsovia  "},
        {"Frankfurt ", "Bucareste "},
        {"Milao     ", "Berlim    "},
        {"Milao     ", "Varsovia  "}
    };

    if (day_check == 0 && flight_check == 0) // If the 2nd and 3rd arguments were not provided, it means the function was ran from the menu.
        do_print = 1;     

    if (do_print == 1) // Check if arguments were provided.
    {
        printf(cr_magenta "Indique o dia que quer ver: " cr_reset);
        while (1) // Only let a number between 1 and 30 pass.
        {
            scanf(" %i", &day_check);
            if (day_check > 0 && day_check <= 30)
                break;
            else // You shall not pass
            {
                printf(cr_red "O dia tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "30" cr_red ". " cr_magenta "Experimente outro: " cr_reset);
                __fpurge(stdin);
            }
        }
        
        printf(cr_green "\n    Origem\t\tDestino\n" cr_reset);
        printf(cr_cyan "1" cr_reset " – Lisboa\t\tAmesterdão\n");
        printf(cr_cyan "2" cr_reset " – Lisboa\t\tFrankfurt\n");
        printf(cr_cyan "3" cr_reset " – Lisboa\t\tMilão\n");
        printf(cr_cyan "4" cr_reset " – Amesterdão\t\tBerlim\n");
        printf(cr_cyan "5" cr_reset " – Amesterdão\t\tBucareste\n");
        printf(cr_cyan "6" cr_reset " – Frankfurt\t\tVarsóvia\n");
        printf(cr_cyan "7" cr_reset " – Frankfurt\t\tBucareste\n");
        printf(cr_cyan "8" cr_reset " – Milão\t\tBerlim\n");
        printf(cr_cyan "9" cr_reset " – Milão\t\tVarsóvia");
        printf(cr_magenta "\n\nIndique o voo que quer ver: " cr_reset);
        while (1) // Only let a number between 1 and 9 pass.
        {
            scanf(" %i", &flight_check);
            if (flight_check > 0 && flight_check <= 9)
                break;
            else
            {
                printf(cr_red "O voo tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "9" cr_red ". " cr_magenta "Experimente outro: " cr_reset);
                __fpurge(stdin);
            }
        }
    }

    for (i=0;i<6000;i++) // First check where in the array the day requested starts
    {
        if (passengers[i].day == day_check)
            // If both strings are the same, it'll return 0. Negate 0 to get 1. 1 and 1 is 1, so increments j by 1. Else, doesn't increment
            j+=(!strcmp(passengers[i].orig,origem_dest[flight_check-1][0]) && !strcmp(passengers[i].dest,origem_dest[flight_check-1][1])); 

        if (j == 1)
            flight_first_line = i;
    }

    
    if (j == 0)
    {
        flight_last_line = -1;
        flight_first_line = 0;
        if (do_print)
        {
            system("clear");
            printf(cr_green "Dia:     " cr_reset "%d", day_check);
            printf(cr_red "Não há passageiros marcados nesse voo.\n\n" cr_reset);
        }
    }
    else
    {
        flight_last_line = flight_first_line + j-1;

        if (do_print)
        {
            system("clear");
            printf(cr_green "Dia:     " cr_reset "%d", day_check);
            printf(cr_green "\nOrigem:  " cr_reset);

            printf("%s", origem_dest[flight_check-1][0]);
            printf(cr_green "\nDestino: " cr_reset);
            printf("%s\n", origem_dest[flight_check-1][1]);

            for (j=flight_first_line;j<flight_last_line+1;j++)
            {
                printf(cr_green "\n%i " cr_reset,passengers[j].id);
                for (i=0;i<51;i++)
                    putchar(passengers[j].name[i]);
            }
            putchar('\n');
            putchar('\n');
        }
    }

    return (flight_last_line-flight_first_line+1);
}


/*--------------------------------------------------------------
                        ten_day_table
            Creates a table showing 10 days of flights
--------------------------------------------------------------*/

void ten_day_table(PASSENGER *passengers)
{
    int i,j; // For our loops
    int day_check, people_count;

    printf(cr_magenta "Indique o dia que começa o intervalo: " cr_reset);
    while (1) // Only let a number between 1 and 30 pass.
    {
        scanf(" %i", &day_check);
        if (day_check > 0 && day_check <= 30)
            break;
        else
        {
            printf(cr_red "O dia tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "30" cr_red ". " cr_magenta "Experimente outro: " cr_reset);
            __fpurge(stdin);
        }
    }
    system("clear");
    printf(cr_green);
    printf("\t");
    for (i=1;i<=9;i++)
        printf("| Voo %d ", i);

    putchar('\n');

    for(i=0;i<80;i++)
        putchar('-');


    printf(cr_reset);

    for (i=0;i<10;i++)
    {
        int day_num = ((day_check+i-1)%30)+1; // Crazy maths to make sure it doesn't display day 30 as 0.

        printf(cr_green "\nDia %d\t|" cr_reset, day_num); 

        for (j=0;j<9;j++)
        {
            people_count = list_passengers(passengers, day_num, j+1);
            printf("  %2d\t", people_count);
            printf(cr_green "|" cr_reset);
        }

        putchar('\n');
        printf(cr_green);
        for(j=0;j<80;j++)
            putchar('-');
        printf(cr_reset);
    }

    putchar('\n');
    putchar('\n');
}