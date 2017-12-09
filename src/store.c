/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdio_ext.h>  // For use of the __fpurge function
#include <string.h>     // For use of the strlen function

/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/store.h"


/*--------------------------------------------------------------
                        error_function
          Shows that your file is invalid and return 0
--------------------------------------------------------------*/

int error_function(char *filename)
{
    char c;
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


/*--------------------------------------------------------------
                        store_text
            Retrieves and stores data from a text file
--------------------------------------------------------------*/

int store_text(PASSENGER *passengers, char *argv)
{
    int j=0, i=0;
    char filename[100];
    char c;
    FILE *p_file;


    // Check if a file was provided, otherwise ask for one until it opens sucessfully.

    if (argv == NULL)
    {
        printf(cr_magenta "Escreva o nome do ficheiro a abrir: " cr_reset);
        scanf(" %s", filename);
    }
    else if (strlen(argv) > 99)
        printf(cr_red "O nome do seu ficheiro é demasiado longo." cr_magenta " Tente outro: " cr_reset);
    else
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


    // Wipe the old database

    for (j=0;j<6000;j++) 
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

    j = i = 0; // Reset i and j to prevent issues.

    fseek(p_file, 0, SEEK_SET); // Jump back to the beginning of the file. 


    // Store the data

    while(fscanf(p_file,"%d%51c%11c%11c%hd\n",&passengers[j].id, passengers[j].name, passengers[j].orig, passengers[j].dest, &passengers[j].day)==5)
    {

        // Ensure string termination

        passengers[j].name[50] = '\0';

        for (i=0;i<11;i++)
            if (passengers[j].orig[i] == ' ')
                passengers[j].orig[i] = '\0';
        for (i=0;i<11;i++)
            if (passengers[j].dest[i] == ' ')
                passengers[j].dest[i] = '\0';

        // Check if it's a database file. There's many ways to do this and neither is 100% fool proof.
        // But this seems to work, as long as the first 5 characters of every line of a text file are not populated by 
        // anything smaller than line feeds (10 on the ASCII table), which is unlikely unless
        // the file it's reading has JUST THE RIGHT 5 Characters (or less) in it per line.
        // But who writes 5 character text documents anyway?
        if ((passengers[j].id < 99999 && passengers[j].id > 10000))
        {
            j++;
            continue;
        }
        else
            return error_function(filename); // Return failure (0)

    }
    fclose(p_file);


    // Tell the user all is good, or error.

    if ((passengers[0].id < 99999 && passengers[0].id > 10000) && (passengers[j-1].id < 99999 && passengers[j-1].id > 10000)) // Final sanity check
    {
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, filename);
        printf(cr_magenta "Prima Enter para continuar." cr_reset);
        i = 0;
        while (1)
        {
            c = getchar();
            if (c == '\n' && (argv != NULL || i > 0))
                break;
            else
                i++;
        }
        return 1; // Return success
    }
    else
        return error_function(filename); // Return failure (0)

}


/*--------------------------------------------------------------
                        store_binary
        Retrieves and stores data from a binary filex
--------------------------------------------------------------*/

int store_binary(PASSENGER *passengers, char *argv)
{
    int j=0, i=0;
    char filename[100];
    char c;
    FILE *p_file;


    // Check if a file was provided, otherwise ask for one until it opens sucessfully.

    if (argv == NULL)
    {
        printf(cr_magenta "Escreva o nome do ficheiro a abrir: " cr_reset);
        scanf(" %s", filename);
    }
    else if (strlen(argv) > 99)
        printf(cr_red "O nome do seu ficheiro é demasiado longo." cr_magenta " Tente outro: " cr_reset);
    else
        strcpy(filename,argv);

    while(1)
    {
        p_file = fopen(filename, "rB");
        if (!p_file)
        {
            printf(cr_red "Ficheiro '%s' não encontrado." cr_magenta " Tente outro: " cr_reset, filename);
            __fpurge(stdin);
            scanf(" %s", filename);
        }
        else
            break;
    }


    // Wipe the old database

    for (j=0;j<6000;j++)
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
    j = 0; // Reset j to prevent line reading mistakes.

    while(1)
    {
        // Store the data

        /*  
        The 00 in every 80th byte in the binary file killed me, until I eventually figured out how the binary file was storing data (and what the book was saying).
        Things got worse when I hex edited the binary file and thought, because I have an intel machine, it was reading the data in little-endian format (reading
        44cd0000 instead of 0000cd44.  
        No, seriously, I had written a function that would swap the last 2 and first 2 bytes of a 4 byte data type to get the right numbers
        It worked, but bugged me that I even had to do such a thing at my level, given that we haven't learnt about this stuff before.
        Eventually I realized that the book, when it said a type 'long' was 4 bytes on page 47, it was referring to a microcomputer... 
        A long is 8 bytes.
        Duh. (In hindsight, this is why people use <stdint.h>).
        Álso, why do I always complicate everything?
        */

        if (fread(&passengers[j], 80, 1, p_file)==0) // 1 single fread :D
            break;


        // Ensure string termination

        passengers[j].name[50] = '\0';
        for (i=0;i<11;i++)
            if (passengers[j].orig[i] == ' ')
                passengers[j].orig[i] = '\0';
        for (i=0;i<11;i++)
            if (passengers[j].dest[i] == ' ')
                passengers[j].dest[i] = '\0';


        // Line per line safety check, just like in store_text()

        if (passengers[j].id > 99999 || passengers[j].id < 10000)

            return error_function(filename); // Return failure (0)

        j++;
    }

    fclose(p_file);


    // Tell the user all is good, or error.

    if ((passengers[0].id < 99999 && passengers[0].id > 10000) && (passengers[j-1].id < 99999 && passengers[j-1].id > 10000)) // Final sanity check
    {
        printf(cr_yellow "Ficheiro '%s' lido e dados guardados na memória.\n\n" cr_reset, filename);
        printf(cr_magenta "Prima Enter para continuar." cr_reset);
        i = 0;
        while (1)
        {
            c = getchar();
            if (c == '\n' && (argv != NULL || i > 0))
                break;
            else
                i++;
        }
        return 1; // Return success
    }
    else
        return error_function(filename); // Return failure (0)
}