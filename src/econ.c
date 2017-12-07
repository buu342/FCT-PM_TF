/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h>      // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h>     // For use of the system function
#include <stdio_ext.h>  // For use of the __fpurge function


/*--------------------------------------------------------------
                Custom Libraries and macros
--------------------------------------------------------------*/

#include "headers/struct_n_macros.h"
#include "headers/list.h"
#include "headers/econ.h"


/*--------------------------------------------------------------
                        store_text
            Retrieves and stores data from a text file
--------------------------------------------------------------*/

void economic_analysis(PASSENGER *passengers)
{
    int i,j,k=0;
    int num_pass[270]; // An array containing all the raw, unorganized data
    int info[8];       // Our array containing the organized data
    int largest=0;     // The largest number in the array.


    // Wipe info

    for (k=0;k<8;k++)
        info[k] = 0;

    for (k=0;k<270;k++)
        num_pass[k] = 0;

    k=0;


    // Fill num_pass with all the data

    for (i=1;i<31;i++)
        for (j=1;j<10;j++)
            num_pass[k++] = list_passengers(passengers, i, j); 


    // Fill Groups 1 to 8 with the data

    for (i=0;i<7;i++)
        for (j=0;j<3;j++)
            for (k=0;k<270;k++)
                if (num_pass[k] == (i*3 + j))
                {
                    info[i]++;
                    info[7]+=((i*3 + j)==20);
                }



    // Find the largest number

    for (k=0;k<8;k++)
        largest = (largest > info[k]) ? largest : info[k];


    // Print

    system("clear");
    for (k=0;k<8;k++)
    {
        if (k == 7)
            printf(cr_green "Groupo %d ( cheio )  {" cr_reset "%3d" cr_green "}  |" cr_reset, k, info[k]);
        else
            printf(cr_green "Groupo %d (%2d - %2d)  {" cr_reset "%3d" cr_green "}  |" cr_reset, k, k*3, k*3+2, info[k]);

        for(i=0;i<30*(((double)info[k])/largest);i++)
            putchar('*');

        putchar('\n');
    }
    putchar('\n');
}