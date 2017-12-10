/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of everything
#include <stdlib.h>     // For use of the exit and rand function
#include <stdio_ext.h>  // For use of the __fpurge function
#include <string.h>     // For use of strcpy and strcat function
#include <time.h>       // For use of time function
#include <sys/stat.h>   // For use of the stat function
#include <unistd.h>     // For use of the mkdir function
#include <sys/types.h>  // For use of ACCESSPERMS

/*--------------------------------------------------------------
                Custom Libraries and macroes
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/gera.h"

#define LIS_AMS 0
#define LIS_FRA 1
#define LIS_MIL 2
#define AMS_BER 3
#define AMS_BUC 4
#define FRA_WAR 5
#define FRA_BUC 6
#define MIL_BER 7
#define MIL_WAR 8


/*--------------------------------------------------------------
                        write_file
                      Writes the file
--------------------------------------------------------------*/

void write_file(PASSENGER *passengers, int mode)
{
    FILE *p_file;
    int i=0;
    char name[140]; 
    char filename[146] = "texts/"; // The location it will be saved to.
    struct stat struc = {0}; // Needed for the stat function. Won't be used.

    printf(cr_magenta "Indica o nome do ficheiro para guardar: " cr_reset); // Request file name.
    scanf(" %s", name);

    strcat(filename,name); // Merge the words texts/ and the filename together

    if (stat("/texts", &struc) == -1) // Check if the directory exists
        mkdir("texts", ACCESSPERMS); // if not make it. Permissions to everyone.

    if (mode == 0)
    {
        p_file = fopen(filename, "w+");

        for (i=0;passengers[i].id!=0;i++) // Write until no more information.
            fprintf(p_file, "%d%-50s %-10s %-10s %2d\n", passengers[i].id, passengers[i].name, passengers[i].orig, passengers[i].dest, passengers[i].day );

        fclose(p_file);
    }
    else
    {
        p_file = fopen(filename, "wb+");

        for (i=0;passengers[i].id!=0;i++) // Write until no more information.
        {
            int j; // We have to put back the spaces
            for (j=0;j<52;j++)
                if (passengers[i].name[j] == '\0')
                    passengers[i].name[j] = ' ';
            for (j=0;j<12;j++)
                if (passengers[i].orig[j] == '\0')
                    passengers[i].orig[j] = ' ';
            for (j=0;j<11;j++)
                if (passengers[i].dest[j] == '\0')
                    passengers[i].dest[j] = ' ';
            fwrite(&passengers[i], 80, 1, p_file);
        }

        fclose(p_file);
    }
    printf(cr_yellow "Ficheiro guardado como %s.\n\n" cr_reset, filename);
}


/*--------------------------------------------------------------
                        is_in_array_2d
    Checks if a value exists in 2 dimensions of a 3D array
--------------------------------------------------------------*/

int is_in_array_2d(int num, int array[][9][20], int which, int size1, int size2)
{
    int i,j;
    for (i=0;i<size1;i++)
    {
        for (j=0;j<size2;j++)
        {
            if (array[which][i][j] == num)
                return 1;
        }
    }
    return 0;
}


/*--------------------------------------------------------------
                           generate
      generates the passenger number and names per flight
--------------------------------------------------------------*/

void generate(PASSENGER *passengers, int mode, char *argv)
{
    PASSENGER alunos[6000];
    int i,j,k,l=0,m;
    int num_full;
    int flight_passengersNum[30][9];

    int alunos_list_size=0;
    char filename[100];
    int used_ids[30][9][20];
    char used_names[30][9][20][51];
    FILE *p_file;
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
    srand (time(NULL)); // Generate a new seed via system time.


    // Open the file

    strcpy(filename,argv);
    while(1)
    {
        p_file = fopen(filename, "r");
        if (!p_file)
        {
            printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, filename);
            __fpurge(stdin);
            scanf(" %s", filename);
        }
        else
            break;
    }


    // Fill an array with the data from the text file.

    while(fscanf(p_file,"%d\t%51[^\n]c\n",&alunos[alunos_list_size].id, alunos[alunos_list_size].name)==2)
        alunos_list_size++;
    fclose(p_file);


    // Request number of full flights

    printf(cr_magenta "Indique a quantidade de voos que estão lotados por dia: " cr_reset);
    while (1) // Only let a number between 1 and 9 pass.
    {
        scanf(" %i", &num_full);
        if (num_full >= 1 && num_full <= 9)
            break;
        else
        {
            printf(cr_red "O numero tem que ser entre " cr_cyan "1" cr_red " e " cr_cyan "9" cr_red ". " cr_magenta "Tente outro: " cr_reset);
            __fpurge(stdin);
        }
    }


    // Fill the array with 20's and fill the rest of the flights with anything

    for (i=0;i<30;i++) // 30 days
    {
        j = num_full;
        while (j>0) // Cycle until num_full amount of 20's has been put per day
        {
            int ran = rand()%9;
            if (flight_passengersNum[i][ran] != 20) // If a 20 doesn't exist in this position
            {
                flight_passengersNum[i][ran] = 20;
                j--;
            }

        }
        for(j=0;j<9;j++) // Fill the rest of the table with random numbers
            if (flight_passengersNum[i][j] != 20)
                flight_passengersNum[i][j] = rand()%20;
    }


    // Correct the table according to conditions.

    for (i=0;i<30;i++) // 30 days
    {
        for(j=0;j<9;j++) // 9 Flights
        {
            if (flight_passengersNum[i][j] != 20) // Ignore days that already have 20 passengers
            {
                for (k=0;k<3;k++) // Since we know the structure of the table, we'll use k to cycle through the different if statements. 
                {
                    if (j == AMS_BER+k*2 && flight_passengersNum[i][LIS_AMS+k] > 0) // If LIS_AMS doesn't have 0 passengers
                        flight_passengersNum[i][AMS_BER+k*2] = rand()%flight_passengersNum[i][LIS_AMS+k]; // Give AMS_BER a number not higher than LIS_AMS

                    // "Se os dois segundos voos não estiverem lotados, então a soma dos passageiros desses voos não pode ser superior ao número de passageiros no primeiro voo"
                    if (j == AMS_BUC+k*2 && flight_passengersNum[i][LIS_AMS+k] > 0 && flight_passengersNum[i][LIS_AMS+k] > flight_passengersNum[i][AMS_BER+k*2])
                        flight_passengersNum[i][AMS_BUC+k*2] = rand()%(flight_passengersNum[i][LIS_AMS+k] - flight_passengersNum[i][AMS_BER+k*2]);

                }
            }
        }
    }


    // Add names to the flights

    for (i=0;i<30;i++) // 30 days
    {

        // Add names to the first 3 flights

        for(j=0;j<3;j++) 
        {
            m = 0;

            if (flight_passengersNum[i][j] == 0)
                continue;

            for(k=0;k<flight_passengersNum[i][j];k++) // Number of passengers in that day, that flight
            {
                int ran = rand()%alunos_list_size;

                while (is_in_array_2d(alunos[ran].id, used_ids, i, j, k))
                    ran = rand()%alunos_list_size;

                used_ids[i][j][m] = alunos[ran].id;
                passengers[l].id = used_ids[i][j][m];
                
                strcpy(passengers[l].name, alunos[ran].name);
                strcpy(used_names[i][j][m], passengers[l].name);

                strcpy(passengers[l].orig, origem_dest[j][0]);
                strcpy(passengers[l].dest, origem_dest[j][1]);
                passengers[l].day  = i+1;
                
                m++;
                l++;
            }
        }

        m = 0;

        for(j=0;j<3;j++) // 3 flights from Lisbon
        {

            int src = LIS_AMS+j;
            int dest1 = AMS_BER+j*2;
            int dest2 = AMS_BUC+j*2;

            int passengersFromLisbon = flight_passengersNum[i][src];
            
            int passengersToDest1 = 0;
            int passengersToDest2 = 0;


            // Fill up a day with names from a previous flight
            
            while(passengersFromLisbon > 0 && (passengersToDest1 < flight_passengersNum[i][dest1] || passengersToDest2 < flight_passengersNum[i][dest2]))
            {
                int ran = rand()%2;
                if(ran == 0 && flight_passengersNum[i][dest1] > passengersToDest1)
                {
                    passengers[l].id = used_ids[i][src][passengersToDest1 + passengersToDest2];
                    strcpy(passengers[l].name, used_names[i][src][passengersToDest1 + passengersToDest2]);
                    strcpy(passengers[l].orig, origem_dest[dest1][0]);
                    strcpy(passengers[l].dest, origem_dest[dest1][1]);
                    passengers[l].day  = i+1;

                    passengersFromLisbon--;
                    passengersToDest1++;
                    l++;
                }
                else if(ran == 1 && flight_passengersNum[i][dest2] > passengersToDest2)
                {
                    passengers[l].id = used_ids[i][src][passengersToDest1 + passengersToDest2];
                    strcpy(passengers[l].name, used_names[i][src][passengersToDest1 + passengersToDest2]);
                    strcpy(passengers[l].orig, origem_dest[dest2][0]);
                    strcpy(passengers[l].dest, origem_dest[dest2][1]);
                    passengers[l].day  = i+1;

                    passengersFromLisbon--;
                    passengersToDest2++;
                    l++;
                }
            }

            m = passengersToDest1 + passengersToDest2;


            // If we weren't able to use up all the old names, fill up the rest with new random names.

            while(passengersToDest1 < flight_passengersNum[i][dest1])
            {
                int ran = rand()%alunos_list_size;

                while (is_in_array_2d(alunos[ran].id, used_ids, i, 9, 20))
                    ran = rand()%alunos_list_size;

                used_ids[i][dest1][m] = alunos[ran].id;

                passengers[l].id = used_ids[i][dest1][m];
                strcpy(passengers[l].name, alunos[ran].name);
                strcpy(used_names[i][dest1][m], passengers[l].name);

                strcpy(passengers[l].orig, origem_dest[dest1][0]);
                strcpy(passengers[l].dest, origem_dest[dest1][1]);
                passengers[l].day  = i+1;
                l++;
                m++;

                passengersToDest1++;
            }
            while(passengersToDest2 < flight_passengersNum[i][dest2])
            {
                int ran = rand()%alunos_list_size;

                while (is_in_array_2d(alunos[ran].id, used_ids, i, 9, 20))
                    ran = rand()%alunos_list_size;

                used_ids[i][dest2][m] = alunos[ran].id;

                passengers[l].id = used_ids[i][dest2][m];
                strcpy(passengers[l].name, alunos[ran].name);
                strcpy(used_names[i][dest2][m], passengers[l].name);

                strcpy(passengers[l].orig, origem_dest[dest2][0]);
                strcpy(passengers[l].dest, origem_dest[dest2][1]);
                passengers[l].day  = i+1;
                l++;
                m++;

                passengersToDest2++;
            }

        }
        m=0;
    }

    // Helper table to visualize how many passengers were put per flight. Only here for testing.

    /*printf("\nVoo   |\t");
    for (i=0;i<9;i++)
        printf("   %d",i+1);
    putchar('\n');
    printf("––––––+–––––––––––––––––––––––––––––––––––––\n");
    for (i=0;i<30;i++)
    {
        printf("Day %2d|\t",i+1);
        for (j=0;j<9;j++)
            printf("  %2d", flight_passengersNum[i][j]);
        putchar('\n');
    }
    putchar('\n');
    */
    printf(cr_yellow "Colocados: %d\n" cr_reset,l);
    write_file(passengers,mode);
}