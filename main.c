#include <stdio.h>
#include <stdlib.h>
#include "login.h"  // Include login functionality

int main() {
    int firstInput;

    while (1) {
        system("clear");
        printf("\n\n-------------------------------------------------------------------\n\n");
        printf("\t\t\tWelcome to Sabaiko Bank.\n\n");
        printf("-------------------------------------------------------------------\n\n");
        printf("Account login:\n\n");
        printf("1. Agent login\n");
        printf("2. Accholder login\n\n");
        printf("[Note : Enter respective number to enter login portal.]\n\n");

        if (scanf("%d", &firstInput) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        if (firstInput == 1 || firstInput == 2) {
            login(firstInput);
            break;
        } else {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear extra input
        }
    }
    return 0;
}