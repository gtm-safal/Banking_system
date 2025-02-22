#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare adminProfile functions here

void createNewAccountHolder() {
    printf("Creating a new account holder account...\n");
    // Logic to create a new account holder account
}

void deleteAccountHolderAccount() {
    printf("Deleting an account holder account...\n");
    // Logic to delete an account holder account
}

void adminProfile(char username[]) {
    int option;
    system("clear");
    printf("Admin Profile: %s\n", username);

    printf("1. Create New Account Holder Account\n");
    printf("2. Delete Account Holder Account\n");
    printf("3. Go Back\n");
    printf("Enter your option: ");
    scanf("%d", &option);

    switch (option) {
        case 1:
            createNewAccountHolder();  // Admin creates a new account holder
            break;
        case 2:
            deleteAccountHolderAccount();  // Admin deletes an account holder
            break;
        case 3:
            printf("Going back to main menu...\n");
            break;
        default:
            printf("Invalid option! Try again.\n");
            break;
    }
}
