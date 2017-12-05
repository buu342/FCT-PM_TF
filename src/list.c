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
#include "headers/list.h"


/*--------------------------------------------------------------
                       orig_dest_compare
        compares the 11 chars in the origin/dest arrays
--------------------------------------------------------------*/

int orig_dest_compare(char *str1, char *str2)
{
    int i,j=0;
    for (i=0;i<11;i++)
    {
        if (str1[i] == str2[i])
            j++;
    }

    return (j == 11);
}


/*--------------------------------------------------------------
                        list_passengers
            Retrieves and stores data from a text file
--------------------------------------------------------------*/

void list_passengers(PASSENGER* passengers)
{
    int i,j; // For our loops
    int day_check, flight_check, day_line=0, flight_line=1; // *_check is the thing the user wishes to check, while *_line is the line of the array being read.
    int flight_first_line=0, flight_last_line; // For knowing which lines to read when printing.
    char last_orig[11], last_dest[11]; // For comparing flight locations.

    printf(cr_magenta "Indique o dia que quer ver: " cr_reset);
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
    for (i=0;i<6000;i++) // First check where in the array the day requested starts
    {
        if (passengers[i].day == day_check)
        {
            for (j=0;j<11;j++)
                last_orig[j] = passengers[i].orig[j];
            for (j=0;j<11;j++)
                last_dest[j] = passengers[i].dest[j];
            break;
        }
        day_line++;
    }

    printf(cr_magenta "Indique o voo que quer ver: " cr_reset);
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
    for (i=day_line;i<6000;i++) // Now starting from the day requested, find where the flight starts and ends.
    {
        if (passengers[i].day != day_check)
            break;
        
        // There's probably a better way to do this but I'm going to sleep on it.

        if (!(orig_dest_compare(passengers[i].orig,last_orig) && orig_dest_compare(passengers[i].dest,last_dest))) // If the current line of orig+dest is not the same
        {
            if (flight_line != flight_check) // And the flight # requested is not the current one
            {
                for (j=0;j<11;j++)
                    last_orig[j] = passengers[i].orig[j];
                for (j=0;j<11;j++)
                    last_dest[j] = passengers[i].dest[j];
                flight_line++;
            }
        }

        if (orig_dest_compare(passengers[i].orig,last_orig) && orig_dest_compare(passengers[i].dest,last_dest)) // There is no else statement because I want it to recheck after having incremented flight_line
        {
            if (flight_line == flight_check)
            {
                if (flight_first_line == 0)
                    flight_first_line = i;

                flight_last_line = i;
            }
        }
    }

    // Print all the names from flight_first_line to flight_last_line + 1

    system("clear");

    printf(cr_green "Dia:     " cr_reset "%d", day_check);
    printf(cr_green "\nOrigem:  " cr_reset);
    for (j=0;j<11;j++)
        putchar(passengers[flight_last_line].orig[j]);
    printf(cr_green "\nDestino: " cr_reset);
    for (j=0;j<11;j++)
        putchar(passengers[flight_last_line].dest[j]);

    putchar('\n');

    for (j=flight_first_line;j<flight_last_line+1;j++)
    {
        printf(cr_green "\n%i " cr_reset,passengers[j].id);
        for (i=0;i<51;i++)
            putchar(passengers[j].name[i]);
    }
    putchar('\n');
    putchar('\n');
}