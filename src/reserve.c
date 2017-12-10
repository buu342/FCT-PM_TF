/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of everything
#include <stdlib.h>     // For use of the system and abs function
#include <stdio_ext.h>  // For use of the __fpurge function
#include <string.h>     // For use of strcmp and strcpy functions


/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/list.h"
#include "headers/reserve.h"


/*--------------------------------------------------------------
                        reserve
           Allow the user to reserve a flight
--------------------------------------------------------------*/

void reserve(PASSENGER *passengers)
{
    int i,j=0,k;
    int day_check;
    int destination_check;
    int connection_check[3];
    char c;
    char destinations[6][11]= 
    { 
        {"Amesterdao"},
        {"Frankfurt" },
        {"Milao"     },
        {"Berlim"    },
        {"Bucareste" },
        {"Varsovia"  },
    };
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


    // Ask for a day

    printf(cr_magenta "Indique o dia que gostaria de viajar: " cr_reset);
    while (1) // Only let a number between 1 and 30 pass.
    {
        scanf(" %i", &day_check);
        if (day_check > 0 && day_check <= 30)
            break;
        else
        {
            printf(cr_red "O dia tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "30" cr_red ". " cr_magenta "Tente outro: " cr_reset);
            __fpurge(stdin);
        }
    }
    putchar('\n');


    // Ask for a destination

    for (i=0;i<6;i++)
        printf(cr_cyan "%d" cr_reset " – %s\n",i+1,destinations[i]);
    printf(cr_magenta "Indique o destino que pretende viajar para: " cr_reset);
    while (1) // Only let a number between 1 and 6 pass.
    {
        scanf(" %i", &destination_check);
        if (destination_check > 0 && destination_check <= 6)
            break;
        else
        {
            printf(cr_red "O voo tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "6" cr_red ". " cr_magenta "Tente outro: " cr_reset);
            __fpurge(stdin);
        }
    }


    // If they chose a destination which requires a connection flight, ask them to choose the connection flight

    if (destination_check > 3)
    {
        for (i=0;i<6;i++)
            if (!strcmp(destinations[destination_check-1], origem_dest[i+3][1]))
            {
                printf(cr_cyan "\n%d" cr_reset " – %s\t%s", ++j, origem_dest[i+3][0], origem_dest[i+3][1]);
                connection_check[j] = i+3; // Store the array index so we can retrieve it later. 
                for (k=0;k<3;k++)
                    if (!strcmp(origem_dest[i+3][0],destinations[k]))
                        connection_check[j+2] = k;
            }
        printf(cr_magenta "\nO voo que escolheu precisa de uma escala. Indique a sua escolha: " cr_reset);
    
        while (1) // Only let a number between 1 and 2 pass.
        {
            scanf(" %i", &connection_check[0]);
            if (connection_check[0] > 0 && connection_check[0] <= 2)
                break;
            else
            {
                printf(cr_red "O voo tem que ser um numero entre " cr_cyan "1" cr_red " e " cr_cyan "2" cr_red ". " cr_magenta "Tente outro: " cr_reset);
                __fpurge(stdin);
            }
        }
    }

    // To Simplify reading, these variables were created.

    int day; 
    int connection = connection_check[connection_check[0]+2]+1; // Lisbon   -> Connection
    int destination = connection_check[connection_check[0]]+1;  // Connect. -> Destination


    // Print the available options for days

    if (destination_check > 3)
    {
        printf(cr_green "\n\tEscala\tDestino\n" cr_reset);
        destination = connection_check[connection_check[0]]+1;
    }
    else
    {
        printf(cr_green "\n\tDestino\n" cr_reset);
        destination = destination_check;
    }
    for (i=0;i<9;i++)
    {
        day = ((day_check+25+i)%30)+1; // 4 numbers behind and 4 in front, jumping to 1 when we hit 31
        if (destination_check > 3)
            printf(cr_green "Dia " cr_cyan "%d" cr_reset "\t%4d\t%4d\n", day, list_passengers(passengers, day, connection), list_passengers(passengers, day, destination));
        else
            printf(cr_green "Dia " cr_cyan "%d" cr_reset "\t%4d\n", day, list_passengers(passengers, day, destination));
    }


    // Find a value of the amount of passengers in our database so we can add our user to the end of the database. Save it into k

    for (k=0;k<6000;k++)
        if (passengers[k].id == 0)
            break;


    // Ask for the final chosen day and make sure it's valid

    printf(cr_magenta "Indique o dia que gostaria de viajar (ou " cr_cyan "0" cr_magenta " para cancelar): " cr_reset);
    while (1)
    {
        scanf(" %hi", &passengers[k].day);
        if (passengers[k].day == 0)
        {
            printf(cr_yellow "Reserva cancelada com êxito.\n\n" cr_reset);
            return;
        }
        else if (destination_check > 3)
        {
            if (!(passengers[k].day > 0 && passengers[k].day <= 30 && (passengers[k].day >= (((day_check+25)%30)+1) || passengers[k].day <= day)))
            {
                printf(cr_red "O dia tem que ser um numero entre " cr_cyan "%d" cr_red " e " cr_cyan "%d" cr_red ". " cr_magenta "Tente outro: " cr_reset,((day_check+25)%30)+1,day);
                __fpurge(stdin);
            }
            else if (list_passengers(passengers, passengers[k].day, connection) == 20 || list_passengers(passengers, passengers[k].day, destination) == 20)
            {
                printf(cr_red "Um ou mais voos estão cheios." cr_magenta " Tente outro: " cr_reset);
                __fpurge(stdin);
            }
            else
                break;
        }
        else
        {
            if (!(passengers[k].day > 0 && passengers[k].day <= 30 && (passengers[k].day >= (((day_check+25)%30)+1) || passengers[k].day <= day)))
            {
                printf(cr_red "O dia tem que ser um numero entre " cr_cyan "%d" cr_red " e " cr_cyan "%d" cr_red ". " cr_magenta "Tente outro: " cr_reset,((day_check+25)%30)+1,day);
                __fpurge(stdin);
            }
            else if (list_passengers(passengers, passengers[k].day, destination) == 20)
            {
                printf(cr_red "O voo está cheio." cr_magenta " Tente outro: " cr_reset);
                __fpurge(stdin);
            }
            else
                break;
        }
    }


    // Ask for necessary info

    printf(cr_magenta "Indique o seu BI: " cr_reset);
    while (1) // Only let a number between 10000 and 99999 pass.
    {
        scanf(" %i", &passengers[k].id);
        if (passengers[k].id >= 10000 && passengers[k].id <= 99999)
            break;
        else
        {
            printf(cr_red "O BI tem que ser um numero entre " cr_cyan "10000" cr_red " e " cr_cyan "99999" cr_red ". " cr_magenta "Tente outro: " cr_reset);
            __fpurge(stdin);
        }
    }
    
    i=0;
    printf(cr_magenta "Indique o seu nome: " cr_reset);
    while ((c = getchar()) && i<51)
    {
        if (i==0 && c == '\n')
            continue;
        else if (c == '\n')
            break;
        passengers[k].name[i++] = c;

    }
    for (j=i;j<51;j++)
        if (j == 50)
            passengers[k].name[50] = '\0';
        else
            passengers[k].name[j] = ' ';


    // Put the user's data at the end of the passengers array

    if (destination_check > 3)
    {
        strcpy(passengers[k].orig, "Lisboa");
        strcpy(passengers[k].dest, origem_dest[connection-1][1]);

        passengers[k+1].id = passengers[k].id;
        passengers[k+1].day = passengers[k].day;
        strcpy(passengers[k+1].name, passengers[k].name);
        strcpy(passengers[k+1].orig, passengers[k].dest);
        strcpy(passengers[k+1].dest, origem_dest[destination-1][1]);
    }
    else
    {
        strcpy(passengers[k].orig, "Lisboa");
        strcpy(passengers[k].dest, origem_dest[destination-1][1]);
    }


    // Output what has been saved into the array.

    system("clear");
    printf(cr_yellow "Reserva feita\n" cr_reset);
    printf(cr_green "BI:\t\t " cr_reset "%d\n", passengers[k].id);
    printf(cr_green "Nome:\t\t " cr_reset "%s\n", passengers[k].name);
    printf(cr_green "Dia:\t\t " cr_reset "%d\n", passengers[k].day);
    printf(cr_green "Partida:\t " cr_reset "Lisboa\n");
    if (destination_check > 3)
    {
        printf(cr_green "Conneção:\t " cr_reset "%s\n", passengers[k+1].orig);
        printf(cr_green "Destino:\t " cr_reset "%s\n", passengers[k+1].dest);
    }
    else
        printf(cr_green "Destino:\t " cr_reset "%s\n", passengers[k].dest);

    printf(cr_magenta "\nPrima Enter para continuar." cr_reset);
    while((c = getchar())!='\n');
}