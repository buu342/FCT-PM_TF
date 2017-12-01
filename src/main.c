/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h>     // For use of the exit functions
#include <stdio_ext.h>  // For use of the __fpurge function

/*--------------------------------------------------------------
                        Custom Libraries
--------------------------------------------------------------*/

#include "headers/menu.h" // Menu


/*--------------------------------------------------------------
                            Main
--------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc > 1)
    {
        if (argv[1][0] == '-' && argv[1][2] == '\0')
        {
            switch(argv[1][1])
            {
                case 'b':
                    if (argc == 3)
                    {
                        fp = fopen(argv[2], "rb");
                        if (fp)
                        {
                            printf("\nBinary Mode Detected and initialized.\n\n");
                            fclose(fp);
                        }
                        else
                            printf("\nUnable to read database file.\n\n");
                    }
                    else
                    {
                        printf("\nBinary Mode not in the right format\n\n");
                        exit(0);
                    }
                    break;
                case 'h':
                    if (argc == 2)
                    {
                        printf("\nHelp Mode Detected.\n\n");
                        exit(0);
                    }
                    else
                    {
                        printf("\nHelp Mode not in the right format\n\n");
                        exit(0);
                    }
                    break;
                default:
                    printf("\nUnknown Mode Detected\n\n");
                    exit(0);
                    break;
            }
        }
        else
        {
            fp = fopen(argv[1], "r");
            if (fp)
            {
                printf("\nRead Mode Detected and initialized.\n\n");
                fclose(fp);
            }
            else
                printf("\nUnable to read database file.\n\n");
            
        }
    }
    else
    {
        menu();
        exit(0);
    }
}