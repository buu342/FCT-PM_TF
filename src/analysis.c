/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of everything
#include <stdlib.h>     // For use of the system function
#include <stdio_ext.h>  // For use of the __fpurge function
#include <string.h>     // For use of strcmp


/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/list.h"
#include "headers/analysis.h"


/*--------------------------------------------------------------
                    economic_analysis
        Creates a bar graph of flight passenger data
--------------------------------------------------------------*/

void economic_analysis(PASSENGER *passengers)
{
    int i,j,k=0;
    int num_pass[270]; // An array containing all the raw, unorganized data
    int group[8];      // Our array containing the organized data
    int largest=0;     // The largest number in the array.


    // Wipe the groups to prevent incrementation faults

    for (i=0;i<8;i++)
        group[i] = 0;


    // Fill num_pass with the amount of passengers in each flight of each day

    for (i=1;i<31;i++)      // 30 days
        for (j=1;j<10;j++)  // 9 flights
            num_pass[k++] = list_passengers(passengers, i, j);


    // Fill Groups 1 to 8 with the amount of people in said group.

    for (i=0;i<7;i++)                                               // check all 8 groups (we don't need to check the last group)
        for (k=0;k<270;k++)                                         // Cycle through all the flight passenger number data
            if (num_pass[k] >= (i*3) && num_pass[k] <= (i*3 +2))    // If the number of passengers in a flight belongs to one of the 8 groups
            {
                group[i]++;                                         // Increment that group only
                group[7]+=(num_pass[k]==20);                        // Increment Group 8 if the number of passengers is 20
            }


    // Find the largest number

    for (i=0;i<8;i++)
        largest = ((largest > group[i]) ? largest : group[i]);


    // Print

    system("clear");
    for (k=0;k<8;k++)
    {
        if (k == 7)
            printf(cr_green "Grupo %d ( cheio )  {" cr_reset "%3d" cr_green "}  |" cr_reset, k+1, group[k]);
        else
            printf(cr_green "Grupo %d (%2d – %2d)  {" cr_reset "%3d" cr_green "}  |" cr_reset, k+1, k*3, k*3+2, group[k]);

        for(i=0;i<30*(((double)group[k])/largest);i++) // Floor the decimal places.
            putchar('*');

        putchar('\n');
    }
    putchar('\n');
}


/*--------------------------------------------------------------
                    connecting_flights
        Shows who is traveling via a connected flight
--------------------------------------------------------------*/

void connecting_flights(PASSENGER *passengers)
{
    int i,j,k=0, l=0;
    int day_check;
    int flight_check;
    int ids[6000];
    char origem_dest[9][2][11]= 
    { 
        {"Lisboa"    , "Amesterdao"},
        {"Lisboa"    , "Frankfurt" },
        {"Lisboa"    , "Milao"     },
        {"Amesterdao", "Berlim"    },
        {"Amesterdao", "Bucareste" },
        {"Frankfurt" , "Varsovia"  },
        {"Frankfurt" , "Bucareste" },
        {"Milao"     , "Berlim"    },
        {"Milao"     , "Varsovia"  }
    };


    // Ask the user to input the day he wishes to check

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


    // Ask for which flight to check.

    printf(cr_green "\n    Origem\t\tDestino\n" cr_reset);
    printf(cr_cyan "1" cr_reset " – Lisboa\t\tAmesterdão\n");
    printf(cr_cyan "2" cr_reset " – Lisboa\t\tFrankfurt\n");
    printf(cr_cyan "3" cr_reset " – Lisboa\t\tMilão\n");
    printf(cr_magenta "Indique o voo que quer ver: " cr_reset);
    while (1) // Only let a number between 1 and 3 pass.
    {
        scanf(" %i", &flight_check);
        if (flight_check > 0 && flight_check <= 3)
            break;
        else
        {
            printf(cr_red "O voo tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "3" cr_red ". " cr_magenta "Experimente outro: " cr_reset);
            __fpurge(stdin);
        }
    }


    // Fill the ids array with the id's found in the specified flight and day

    for (i=0;i<6000;i++)
    {
        ids[i] = 0; // Wipe the array
        if (passengers[i].day != day_check)
            continue;

        if ((!strcmp(passengers[i].orig,origem_dest[flight_check-1][0]) && !strcmp(passengers[i].dest,origem_dest[flight_check-1][1])))
            ids[l++] = passengers[i].id;
    }
    l = 0;

    system("clear");
    printf(cr_green "\t\t\t\t\t\t\t     Origem\t   Escala\t  Destino\n" cr_reset);


    // Now check if anyone in a connecting flight ALSO has their ID in the ids array, and if so print their data.

    for (i=0;ids[i]!=0;i++) // Cycle through all the id's in our array
    {
        for (j=0;j<6000;j++) // Cycle through all the flights and find one where an id in our array matches someone going to another flight
        {
            if (passengers[j].id != ids[i] || passengers[j].day != day_check)
                continue;

            if ((!strcmp(passengers[j].orig,origem_dest[flight_check*2+1][0]) && !strcmp(passengers[j].dest,origem_dest[flight_check*2+1][1])) && k == 0)
                printf(cr_green "%2d – %d" cr_reset " %sLisboa\t   %s\t  %s\n",++l , passengers[j].id, passengers[j].name, origem_dest[flight_check-1][1], origem_dest[flight_check*2+1][1]);
            else if ((!strcmp(passengers[j].orig,origem_dest[flight_check*2+2][0]) && !strcmp(passengers[j].dest,origem_dest[flight_check*2+2][1])) && k == 1)
                printf(cr_green "%2d – %d" cr_reset " %sLisboa\t   %s\t  %s\n",++l, passengers[j].id, passengers[j].name, origem_dest[flight_check-1][1], origem_dest[flight_check*2+2][1]);
        }
        if (k == 0 && ids[i+1]==0)
        {
            i = 0;
            k++;
            putchar('\n');
        }
    }
    if (l == 0)
        printf(cr_red "Não há passageiros a fazer escala.\n\n" cr_reset);
}