#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.c"

int main() {
    int firstInput;
    
    // Loop for retrying login until the user enters a valid option
    while (1) {
        system("clear");
        printf("\n\n-------------------------------------------------------------------\n\n");
        printf("\t\t\tWelcome to Sabaiko Bank.\n\n");
        printf("-------------------------------------------------------------------\n\n");
        printf("Account login:\n\n");
        printf("1. Agent login\n");
        printf("2. Customer login\n\n");
        printf("[Note : Enter respective number to enter login portal.]\n\n");
        
        // Accept user input
        scanf("%d", &firstInput);
        
        // If valid input is entered, call login
        if (firstInput == 1 || firstInput == 2) {
            login(firstInput);
            break; // Exit the loop once the login process is done
        } else {
            printf("Invalid input. Please try again.\n");
            getchar(); // To handle the Enter key after invalid input
        }
    }
    return 0;
}
