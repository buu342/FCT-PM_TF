/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of everything
#include <stdlib.h>     // For use of the exit function


/*--------------------------------------------------------------
                        Custom Libraries
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/gera.h"


/*--------------------------------------------------------------
                            Main
            Check for arguments and call generate
--------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    PASSENGER passengers[6000];
    int i,j;


    // Clean the database first

    for (i=0;i<6000;i++)
    {
        passengers[i].id = 0;
        for (j=0;j<51;j++)
            passengers[i].name[j] = '\0';
        for (j=0;j<11;j++)
            passengers[i].orig[j] = '\0';
        for (j=0;j<11;j++)
            passengers[i].dest[j] = '\0';
        passengers[i].day = 0;
    }


    // Check the arguments

    if (argc == 2)
    {
        if (argv[1][0] != '-')
        {
            generate(passengers,0, argv[1]);
            exit(0);
        }
    }
    else if (argc == 3)
    {
        if (argv[1][0] == '-' && argv[1][1] == 'b' && argv[1][2] == '\0')
        {
            generate(passengers,1, argv[2]);
            exit(0);
        }
    }
    printf(cr_yellow "\nCommandos:\n\n" cr_reset);
    printf(cr_yellow "\t%s ficheiro_texto\t\tGerar ficheiro texto.\n" cr_reset, argv[0]);
    printf(cr_yellow "\t%s -b ficheiro_texto\tGerar ficheiro binário.\n\n" cr_reset, argv[0]);
}