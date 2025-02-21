#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.c"
int main()
{
    int firstInput;
    system("clear");
    printf("\n\n-------------------------------------------------------------------\n\n");
    printf("\t\t\tWelcome to Sabaiko Bank.\n\n");
    printf("-------------------------------------------------------------------\n\n");
    printf("Account login:\n\n");
    printf("1. Agent login\n");
    printf("2. Customer login\n\n");
    printf("[Note : Enter respective number to enter login portal.]\n\n");
    scanf("%d", &firstInput);

    login(firstInput);
    return 0;
}