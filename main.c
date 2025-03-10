#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utilities.h"
#include "login.c"
#include "loginPage.c"
#include "depositAndWithdraw.c"
#include "utilities.c"

//Main function
int main()
{
    int firstInput;

    initialize_files(); // Ensure all necessary files exist

    while (1)
    {
        system(CLEAR_SCREEN);

        printf("\x1b[48;2;50;50;50m");  // Set background color to dark gray
        printf("\x1b[38;2;0;255;255m"); // Set text color to cyan
        printf("\x1b[H");               // Move the cursor to the top-left corner

        printf("\n");
        printf("\n");
        printf("+----------------------------------------C_PROJECT----------------------------------------------------+\n");
        printf("|                                                                                                     |\n");
        printf("|       ██████╗ ██╗████████╗███████╗       ██╗       ██████╗ ██╗   ██╗████████╗███████╗███████╗       |\n");
        printf("|       ██╔══██╗██║╚══██╔══╝██╔════╝       ██║       ██╔══██╗╚██╗ ██╔╝╚══██╔══╝██╔════╝██╔════╝       |\n");
        printf("|       ██████╔╝██║   ██║   ███████╗    ████████╗    ██████╔╝ ╚████╔╝    ██║   █████╗  ███████╗       |\n");
        printf("|       ██╔══██╗██║   ██║   ╚════██║    ██╔═██╔═╝    ██╔══██╗  ╚██╔╝     ██║   ██╔══╝  ╚════██║       |\n");
        printf("|       ██████╔╝██║   ██║   ███████║    ██████║      ██████╔╝   ██║      ██║   ███████╗███████║       |\n");
        printf("|       ╚═════╝ ╚═╝   ╚═╝   ╚══════╝    ╚═════╝      ╚═════╝    ╚═╝      ╚═╝   ╚══════╝╚══════╝       |\n");
        printf("|                                                                                                     |\n");
        printf("+-----------------------------------------------------------------------------------------------------+\n");
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

//Function to check exising files and create if not present
void check_and_create_file(const char *filename)
{
    FILE *file = fopen(filename, "ab");
    if (file == NULL)
    {
        fprintf(stderr, "Error creating file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

//Function to initialize files
void initialize_files()
{
    check_and_create_file("adminCredential.dat");
    check_and_create_file("accholderCredential.dat");
    check_and_create_file("details.dat");

    // Check if adminCredential.dat is empty and add default admin credentials if it is
    FILE *adminFile = fopen("adminCredential.dat", "rb");
    if (adminFile == NULL)
    {
        // File does not exist, create it and add default admin credentials
        adminFile = fopen("adminCredential.dat", "wb");
        if (adminFile == NULL)
        {
            fprintf(stderr, "Error creating file: adminCredential.dat\n");
            exit(EXIT_FAILURE);
        }
        Credential defaultAdmin = {"admin", "admin"};
        fwrite(&defaultAdmin, sizeof(Credential), 1, adminFile);
    }
    else
    {
        // File exists, check if it is empty
        fseek(adminFile, 0, SEEK_END);
        if (ftell(adminFile) == 0) // File is empty
        {
            fclose(adminFile);
            adminFile = fopen("adminCredential.dat", "wb");
            if (adminFile == NULL)
            {
                fprintf(stderr, "Error opening file: adminCredential.dat\n");
                exit(EXIT_FAILURE);
            }
            Credential defaultAdmin = {"admin", "admin"};
            fwrite(&defaultAdmin, sizeof(Credential), 1, adminFile);
        }
    }
    fclose(adminFile);
}
