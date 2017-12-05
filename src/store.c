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


/*--------------------------------------------------------------
                        store_text
            Retrieves and stores data from a text file
--------------------------------------------------------------*/

int store_text(PASSENGER *passengers, char *filename)
{
    char c; // For the "Press enter to continue" messages.
    char temp_filename[100]; // Safety, in case people provide incorrect file names first time around.
    int i = 0, j = 0, succesful_firstread = 1;  // succesful_firstread was needed since I couldn't modify the pointer's value. There's probably a nicer way to do this but I'm not sure how now. I'll sleep on it.
                                                // 'i' will be used for counting characters while j will be used for counting lines.
    FILE *p_file;

    if (filename == NULL)
        printf(cr_magenta "Escreva o nome do ficheiro a abrir: " cr_reset);

    while (1) // Make sure the file exists. There's two checks, one for when an argument is provided in the command line directly and one for when the function was ran manually via the menu.s
    {
        if (succesful_firstread == 0 || filename == NULL)
        {
            scanf(" %s", temp_filename);
            p_file = fopen(temp_filename, "r");
            if (!p_file)
            {
                printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, temp_filename);
                __fpurge(stdin);
            }
            else
                break;
        }
        else
        {
            p_file = fopen(filename, "r");
            if (!p_file)
            {
                printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, filename);
                succesful_firstread = 0;
            }
            else
                break;
        }
    }

    for (j=0;j<6000;j++)    // Wipe the old database
    {
        passengers[j].id = 0;
        for (i=0;i<51;i++)
            passengers[j].name[i] = '\0';
        for (i=0;i<11;i++)
            passengers[j].orig[i] = '\0';
        for (i=0;i<11;i++)
            passengers[j].dest[i] = '\0';
        passengers[j].day = 0;
    }

    j = i = 0; // Reset i and j to prevent line reading mistakes.

    fseek(p_file, 0, SEEK_SET); // Jump back to the beggining of the file. 

    while((c=getc(p_file))) // Extra parenthesis or -Wall would complain
    {
        i++;
        if (c == EOF ) // Stop once we hit rock bottom.
            break;

        if (c == '\n')
        {

            // Check if it's a database file. There's many ways to do this and neither is 100% fool proof.
            // But this seems to work, as long as the first 5 characters of every line of a text file are not populated by 
            // anything smaller than line feeds (10 on the ASCII table), which is unlikely unless
            // the file it's reading has JUST THE RIGHT 5 Characters (or less) in it per line.
            // But who writes 5 character text documents anyway?
            if (i == 81 && (passengers[j].id < 99999 && passengers[j].id > 10000)) // This is to make sure it's a correct database file.
            {
                j++;
                i = 0;
                continue;
            }
            else
            {
                if (succesful_firstread == 0 || filename == NULL)
                    printf(cr_red "Ficheiro '%s' não está no formato correto.\n\n" cr_magenta "Prima Enter para continuar." cr_reset, temp_filename);
                else
                    printf(cr_red "Ficheiro '%s' não está no formato correto.\n\n" cr_magenta "Prima Enter para continuar." cr_reset, filename);
                __fpurge(stdin);

                while(1)
                {
                    c = getchar();
                    if (c == '\n')
                        break;
                }
                return 0; // Return failure
            }
        }

        // Store the data

        if (i<=5)
            passengers[j].id = c-'0' + passengers[j].id*10;
        else if (i <= 56)
            passengers[j].name[i-6] = c;
        else if (i <= 67)
            passengers[j].orig[i-57] = c;
        else if (i <= 78)
            passengers[j].dest[i-68] = c;
        else if (c != ' ')
            passengers[j].day = c-'0' + passengers[j].day*10;
    }
    fclose(p_file);

    if (succesful_firstread == 0 || filename == NULL)
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, temp_filename);
    else
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, filename);

    printf(cr_magenta "Prima Enter para continuar." cr_reset);
    i = 0;
    while (1)
    {
        
        c = getchar();
        if (c == '\n' && (filename != NULL || i > 0))
            break;
        else
            i++;
    }
    return 1; // Return success
}


/*--------------------------------------------------------------
                        store_binary
        Retrieves and stores data from a binary filex
--------------------------------------------------------------*/

int store_binary(PASSENGER *passengers, char *filename)
{
    
    char c;
    char temp_filename[100]; // Safety, in case people provide incorrect file names first time around.
    int j = 0, i = 0, succesful_firstread = 1; // succesful_firstread was needed since I couldn't modify the pointer's value. There's probably a nicer way to do this but I'm not sure how now. I'll sleep on it.
                                               // 'i' will be used for counting characters while j will be used for counting lines.    
    FILE *p_file;

    if (filename == NULL)
        printf(cr_magenta "Escreva o nome do ficheiro a abrir: " cr_reset);

    while (1) // Make sure the file exists
    {
        if (succesful_firstread == 0 || filename == NULL)
        {
            scanf(" %s", temp_filename);
            p_file = fopen(temp_filename, "rb");
            if (!p_file)
            {
                printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, temp_filename);
                __fpurge(stdin);
            }
            else
                break;
        }
        else
        {
            p_file = fopen(filename, "rb");
            if (!p_file)
            {
                printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, filename);
                succesful_firstread = 0;
            }
            else
                break;
        }
    }

    for (j=0;j<6000;j++)    // Wipe the old database
    {
        passengers[j].id = 0;
        for (i=0;i<51;i++)
            passengers[j].name[i] = '\0';
        for (i=0;i<11;i++)
            passengers[j].orig[i] = '\0';
        for (i=0;i<11;i++)
            passengers[j].dest[i] = '\0';
        passengers[j].day = 0;
    }
    j = i = 0; // Reset i and j to prevent line reading mistakes.

    while(1)
    {
        // Store the data

        if (fread(&passengers[j].id, 4, 1, p_file) != 1) // Read 1 data element of 4 bytes
            break;                                       // If it didn't read 4 bytes, it's at the EOF.
        fread(&passengers[j].name, 51, 1, p_file);
        fread(&passengers[j].orig, 11, 1, p_file);
        fread(&passengers[j].dest, 11, 1, p_file);
        fread(&passengers[j].day, 3, 1, p_file); // You said it was 2 bytes! Gave me a headache with my already existing one :(
        passengers[j].day = passengers[j].day/256;

        // Line per line safety check, just like in store_text()

        if (passengers[j].id > 99999 || passengers[j].id < 10000)
        {
            if (succesful_firstread == 0 || filename == NULL)
                printf(cr_red "Ficheiro '%s' não está no formato correto.\n\n" cr_magenta "Prima Enter para continuar." cr_reset, temp_filename);
            else
                printf(cr_red "Ficheiro '%s' não está no formato correto.\n\n" cr_magenta "Prima Enter para continuar." cr_reset, filename);
            __fpurge(stdin);

            while(1)
            {
                c = getchar();
                if (c == '\n')
                    break;
            }
            return 0; // Return failure
        }

        j++;
    }
    fclose(p_file);

    if (succesful_firstread == 0 || filename == NULL)
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, temp_filename);
    else
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, filename);

    printf(cr_magenta "Prima Enter para continuar." cr_reset);
    j = 0;
    while (1)
    {
        
        c = getchar();
        if (c == '\n' && (filename != NULL || j > 0))
            break;
        else
            j++;
    }


    return 1; // Return success
}