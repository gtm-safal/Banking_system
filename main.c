#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utilities.h"
#include "login.c"
#include "loginPage.c"
#include "depositAndWithdraw.c"
#include "utilities.c"

int main()
{
    int firstInput;

    initialize_files(); // Ensure all necessary files exist

    while (1)
    {
        system(CLEAR_SCREEN);

        printf("\x1b[48;2;48;10;36m");    // Set background color to dark purple
        printf("\x1b[38;2;255;255;255m"); // Set text color to white
        printf("\x1b[H");                 // Move the cursor to the top-left corner

        printf("\n");
        printf("\n");
        printf("|----------------------------------------C_PROJECT----------------------------------------------------|\n");
        printf("|                                                                                                     |\n");
        printf("|       ██████╗ ██╗████████╗███████╗       ██╗       ██████╗ ██╗   ██╗████████╗███████╗███████╗       |\n");
        printf("|       ██╔══██╗██║╚══██╔══╝██╔════╝       ██║       ██╔══██╗╚██╗ ██╔╝╚══██╔══╝██╔════╝██╔════╝       |\n");
        printf("|       ██████╔╝██║   ██║   ███████╗    ████████╗    ██████╔╝ ╚████╔╝    ██║   █████╗  ███████╗       |\n");
        printf("|       ██╔══██╗██║   ██║   ╚════██║    ██╔═██╔═╝    ██╔══██╗  ╚██╔╝     ██║   ██╔══╝  ╚════██║       |\n");
        printf("|       ██████╔╝██║   ██║   ███████║    ██████║      ██████╔╝   ██║      ██║   ███████╗███████║       |\n");
        printf("|       ╚═════╝ ╚═╝   ╚═╝   ╚══════╝    ╚═════╝      ╚═════╝    ╚═╝      ╚═╝   ╚══════╝╚══════╝       |\n");
        printf("|                                                                                                     |\n");
        printf("|-----------------------------------------------------------------------------------------------------|\n");
        printf("\n");
        printf("Account login:\n\n");
        printf("1. Agent login\n");
        printf("2. Account holder login\n");
        printf("3. Exit\n\n");
        printf("[Note : Enter respective number to enter login portal.]\n\n");

        if (scanf("%d", &firstInput) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ; // Clear invalid input
            continue;
        }

        if (firstInput == 1 || firstInput == 2)
        {
            login(firstInput);
        }
        else if (firstInput == 3)
        { // Exit option
            printf("Exiting the program. Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n')
                ; // Clear extra input
        }
    }
    return 0;
}

void check_and_create_file(const char *filename)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        fprintf(stderr, "Error creating file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

void initialize_files()
{
    check_and_create_file("adminCredential.csv");
    check_and_create_file("accholderCredential.csv");
    check_and_create_file("details.csv");

    // Check if adminCredential.csv is empty and add default admin credentials if it is
    FILE *adminFile = fopen("adminCredential.csv", "r");
    if (adminFile == NULL)
    {
        // File does not exist, create it and add default admin credentials
        adminFile = fopen("adminCredential.csv", "w");
        if (adminFile == NULL)
        {
            fprintf(stderr, "Error creating file: adminCredential.csv\n");
            exit(EXIT_FAILURE);
        }
        fprintf(adminFile, "admin,admin\n");
    }
    else
    {
        // File exists, check if it is empty
        fseek(adminFile, 0, SEEK_END);
        if (ftell(adminFile) == 0) // File is empty
        {
            fclose(adminFile);
            adminFile = fopen("adminCredential.csv", "w");
            if (adminFile == NULL)
            {
                fprintf(stderr, "Error opening file: adminCredential.csv\n");
                exit(EXIT_FAILURE);
            }
            fprintf(adminFile, "admin,admin\n");
        }
    }
    fclose(adminFile);
}
