/*--------------------------------------------------------------
                    Standard C Libraries
--------------------------------------------------------------*/

#include <stdio.h> // For use of literally everything (Thanks Mike Lesk!)
#include <stdlib.h> // For use of the exit and system functions
#include <stdio_ext.h> // For use of the __fpurge function

/*--------------------------------------------------------------
                            Menu
        Used for selecting which functions to execute
--------------------------------------------------------------*/

#include <menu.h>

int menu()
{
    int o;
    system("clear");
    printf("\tCompanhia de Aviação \“Ja Fui\”\n");
    printf("\t\tPrograma de Reservas\n\n\n");
    printf("0 – Sair do programa\n");
    printf("1 – Ler ficheiro de texto\n");
    printf("2 - Ler ficheiro binário\n");
    printf("3 – Listar passageiros de um voo\n");
    printf("4 – Número de passageiros de um período de dias\n");
    printf("5 – Escrita em ficheiro\n");
    printf("6 – Análise económica\n");
    printf("7 – Passageiros em duas escalas\n");
    printf("8 – Reserva simples de um voo\n\n");
    printf("Qual opção quer? ");

    while (1)
    {
        scanf(" %i", &o);
        switch (o)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                exit(0);
                break;
            default:
                printf("Opção inválida. Tente outra: ");
                __fpurge(stdin);
                break;
        }
    }
}
