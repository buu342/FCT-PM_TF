/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <sys/stat.h>   // For use of the stat function
#include <unistd.h>     // For use of the mkdir function
#include <sys/types.h>  // For use of ACCESSPERMS
#include <string.h>     // For use of the strcat function

/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/gera.h"


/*--------------------------------------------------------------
                       write_textfile
            Writes the database to a text file.
--------------------------------------------------------------*/

void write_file(PASSENGER *passengers, int mode)
{
    FILE *p_file;
    int i=0;
    char name[140]; // Now you can name your text file after your tweet!
    char filename[146] = "texts/"; // The location it will be saved to.
    struct stat struc = {0}; // Needed for the stat function. Won't be used.

    printf(cr_magenta "Indica o nome do ficheiro para guardar: " cr_reset); // Request file name.
    scanf(" %s", name);

    strcat(filename,name); // Merge the words texts/ and the filename together

    if (stat("/texts", &struc) == -1) // Check if the directory exists
        mkdir("texts", ACCESSPERMS); // if not make it. Permissions to everyone.

    p_file = fopen(filename, "w+");

    if (mode == 0) // If in text mode
    {
        for (i=0;passengers[i].id!=0;i++) // Write until no more information.
            fprintf(p_file, "%d%s %s %s %2d\n", passengers[i].id, passengers[i].name, passengers[i].orig, passengers[i].dest, passengers[i].day );
    }

    fclose(p_file);

    printf(cr_yellow "Ficheiro guardado como %s.\n\n" cr_reset, filename);
}