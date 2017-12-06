/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h>     // For use of the exit functions


/*--------------------------------------------------------------
                        Custom Libraries
 Apparently C supports ANSI escape sequences. Time to abuse :D
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"    // Contains our struct and some macros, such as colors :D
#include "headers/menu.h"               // Menu
#include "headers/store.h"              // Storing functions


/*--------------------------------------------------------------
I'm using colors to make the flow of the program easier for the
user.

red     - For displaying errors
green   - For Titles
cyan    - For usable options
magenta - Awaiting user input
yellow  - Task completed

I'm using cr_* because of my Game Maker habits.
--------------------------------------------------------------*/


/*--------------------------------------------------------------
                            Main
--------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    PASSENGER passengers[6000]; // Given that Main only closes when the program ends, I can keep using it to store my variables, since global variables are condemned. The prefect crime...

    passengers[50].id = 0; // This is explained in the menu, but essentially is there to ensure the user has properly read a database.

    if (argc > 1) // Check if there's something in front of the program name. If not, open the menu instantly
    {
        if (argv[1][0] == '-') // Check if the user has given a command. If not, treat it as a filename.
        {
            if (argv[1][2] == '\0')
            {
                switch(argv[1][1]) // Choose what to do given on what's in front of the hyphen. 
                {
                    case 'b':
                        if (argc == 3) // Make sure only 2 arguments have been provided, otherwise complain
                        {
                            store_binary(passengers, argv[2]);
                            menu(passengers);
                        }
                        break;
                    case 'h':
                        if (argc == 2) // Make sure only 1 argument was provided, otherwise complain
                        {
                            printf(cr_yellow "\nCommandos:\n\n" cr_reset);
                            printf(cr_yellow "\t%s \t\t\t\tAbrir o programa normalmente.\n" cr_reset, argv[0]);
                            printf(cr_yellow "\t%s ficheiro_texto\t\tAbrir diretamente um ficheiro texto.\n" cr_reset, argv[0]);
                            printf(cr_yellow "\t%s -b ficheiro_binário\tAbrir diretamente um ficheiro binário.\n" cr_reset, argv[0]);
                            printf(cr_yellow "\t%s -h \t\t\tVer esta informação.\n\n" cr_reset, argv[0]);
                            exit(0);
                        }
                        break;
                }
            }
        }
        else
        {
            store_text(passengers, argv[1]);
            menu(passengers);
        }
    }
    else
        menu(passengers);

    printf(cr_red "\nComando desconhecido. Experimente '%s -h'\n\n" cr_reset, argv[0]);
}