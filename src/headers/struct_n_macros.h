#ifndef PMSTNM_H
#define PMSTNM_H

#define cr_red     "\x1b[31m"
#define cr_green   "\x1b[32m"
#define cr_yellow  "\x1b[33m"
#define cr_blue    "\x1b[34m"
#define cr_magenta "\x1b[35m"
#define cr_cyan    "\x1b[36m"
#define cr_reset   "\x1b[0m"

typedef struct Passenger
{
    unsigned int id;
    char name[51];
    char orig[11];
    char dest[11];
    unsigned short int day;
} PASSENGER;

#endif
