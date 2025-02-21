#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adminProfile(char username[]) {
    printf("Welcome to the Admin Profile!\n");
    // Add any admin-specific functionality here
}

void customerProfile(char username[]) {
    char name[20], fileUsername[15], option;
    float balance;
    long phno;
    FILE *fp = fopen("details.csv", "r");

    while (fscanf(fp, "%19[^,],%f,%ld,%15s", name, &balance, &phno, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            printf("Name: %s", name);
            printf("Contact No: %ld", phno);
            printf("Balance: Rs %.3f", balance);
            break;
        }
    }

    if (strcmp(username, fileUsername) != 0) {
        // If no matching username is found
        printf("No customer profile found with the username %s.\n", username);
    }

    printf("\n\nEnter 'T' to transfer money, '**' to go to main menu and 'Q' to quit: ");
    scanf(" %c", &option);

    switch (option) {
    case 'T':
    case 't':
        // Transfer money logic here
        printf("Proceeding to money transfer...\n");
        break;
    case '*':
        // Main menu logic here
        printf("Going back to main menu...\n");
        break;
    case 'Q':
    case 'q':
        // Quit logic here
        printf("Exiting...\n");
        break;
    default:
        printf("Invalid option!\n");
    }
    fclose(fp);
}
