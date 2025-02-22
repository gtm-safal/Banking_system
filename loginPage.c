#include "login.h"

// Function to transfer balance
void transferBalance(char senderUsername[]) {
    char recipientUsername[20] = {0}, line[100] = {0}, tempFile[] = "temp.csv";
    float amount, senderBalance = 0, recipientBalance = 0;
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter recipient's username: ");
    scanf("%19s", recipientUsername);

    if (strcmp(senderUsername, recipientUsername) == 0) {
        printf("You cannot transfer money to yourself.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    // Open details.csv to find sender and recipient balances
    fp = fopen("details.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv. Make sure the file exists.\n");
        return;
    }

    int senderFound = 0, recipientFound = 0;
    while (fgets(line, sizeof(line), fp)) { // Fixed typo here
        char name[20], fileUsername[20];
        long phno;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &phno, fileUsername);

        if (strcmp(senderUsername, fileUsername) == 0) {
            senderBalance = balance;
            senderFound = 1;
        }
        if (strcmp(recipientUsername, fileUsername) == 0) {
            recipientBalance = balance;
            recipientFound = 1;
        }
    }
    fclose(fp);

    if (!senderFound || !recipientFound) {
        printf("Sender or recipient not found.\n");
        return;
    }

    if (senderBalance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    // Write updated balances to temp file
    fp = fopen("details.csv", "r");
    tempFp = fopen(tempFile, "w");
    if (fp == NULL || tempFp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {
        char name[20], fileUsername[20];
        long phno;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &phno, fileUsername);

        if (strcmp(senderUsername, fileUsername) == 0) {
            fprintf(tempFp, "%s,%.2f,%ld,%s\n", name, senderBalance - amount, phno, fileUsername);
        } else if (strcmp(recipientUsername, fileUsername) == 0) {
            fprintf(tempFp, "%s,%.2f,%ld,%s\n", name, recipientBalance + amount, phno, fileUsername);
        } else {
            fprintf(tempFp, "%s", line);
        }
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Transfer successful. New balance: Rs %.2f\n", senderBalance - amount);
}

// Admin profile definition
void adminProfile(char username[]) {
    int option;
    while (1) {
        system("clear");
        printf("Welcome to the Admin Profile!\n");
        printf("1. Create New Accholder Account\n");
        printf("2. Delete Accholder Account\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        switch (option) {
        case 1:
            createNewAccholder(); // Admin creates a new accholder account
            break;
        case 2:
            deleteAccholderAccount(); // Admin deletes a accholder account
            break;
        case 3:
            return;  // Exit to the main menu
        default:
            printf("Invalid option. Please try again.\n");
        }
        printf("Press 'Enter' to continue...");
        getchar(); getchar(); // Pause before continuing
    }
}

// Accholder profile definition
void accholderProfile(char username[]) {
    char name[20] = {0}, fileUsername[20] = {0}, option;
    float balance;
    long phno;
    FILE *fp = fopen("details.csv", "r");

    if (fp == NULL) {
        printf("Error: Unable to open details.csv. Make sure the file exists.\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%19[^,],%f,%ld,%19s", name, &balance, &phno, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            found = 1;
            printf("Name: %s\n", name);
            printf("Contact No: %ld\n", phno);
            printf("Balance: Rs %.3f\n", balance);
            break;
        }
    }

    if (!found) {
        printf("No accholder profile found with the username %s.\n", username);
    }

    printf("\nEnter 'T' to transfer money, '*' to go to the main menu, or 'Q' to quit: ");
    scanf(" %c", &option);

    switch (option) {
    case 'T':
    case 't':
        transferBalance(username); // Transfer money
        break;
    case '*':
        printf("Going back to main menu...\n");
        break;
    case 'Q':
    case 'q':
        printf("Exiting...\n");
        exit(0);
    default:
        printf("Invalid option!\n");
    }

    fclose(fp);
}

// Function to delete accholder account
void deleteAccholderAccount() {
    char username[20] = {0}, line[100] = {0}, tempFile[] = "temp.csv";
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter accholder's username to delete: ");
    scanf("%19s", username);

    // Open accholderCredential.csv to remove the account
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv. Make sure the file exists.\n");
        return;
    }

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int accountFound = 0;
    while (fgets(line, sizeof(line), fp)) {
        char fileUsername[20], password[16];
        sscanf(line, "%19[^,],%15s", fileUsername, password);

        if (strcmp(username, fileUsername) != 0) {
            fprintf(tempFp, "%s", line);
        } else {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound) {
        printf("Accholder account not found.\n");
        remove(tempFile);
        return;
    }

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to remove the account details
    fp = fopen("details.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv. Make sure the file exists.\n");
        return;
    }

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    accountFound = 0;
    while (fgets(line, sizeof(line), fp)) {
        char name[20], fileUsername[20];
        long phno;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &phno, fileUsername);

        if (strcmp(username, fileUsername) != 0) {
            fprintf(tempFp, "%s", line);
        } else {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound) {
        printf("Accholder details not found.\n");
        remove(tempFile);
        return;
    }

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Accholder account deleted successfully.\n");
}