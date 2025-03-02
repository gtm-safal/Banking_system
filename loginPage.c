#include "login.h"

// Admin profile definition
void adminProfile(char username[]) {
    int secondInput;
    while (1) {
        system("clear");
        printf("Welcome to the Admin Profile!\n\n");
        printf("1. Create new account\n");
        printf("2. Delete account\n");
        printf("3. Create admin account\n");
        printf("4. Add balance to an account\n");
        printf("5. Withdraw balance from an account\n");
        printf("6. Exit to Main Menu\n\n");
        printf("Enter your choice: ");
        scanf("%d", &secondInput);
        clearBuffer();

        switch (secondInput) {
        case 1:
            createNewAccholder(); // Admin creates a new account holder account
            break;
        case 2:
            deleteAccholderAccount(); // Admin deletes an account holder account
            break;
        case 3:
            createAdminAccount(); // Admin creates an admin account
            break;
        case 4:
            addBalance(); // Add balance to an account
            break;
        case 5:
            withdrawBalance(); // Withdraw balance from an account
            break;
        case 6:
            return; // Exit to the main menu
        default:
            printf("Invalid input. Please try again.\n");
        }
        printf("Press 'Enter' to continue...");
        getchar(); // Pause before continuing
    }
}

// Account holder profile definition
void accholderProfile(char username[]) {
    char fname[21], lname[21], fileUsername[21], secondInput;
    float balance;
    long contact;
    FILE *fp = fopen("details.csv", "r");

    if (fp == NULL) {
        printf("Error: Unable to open details.csv.\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) == 0) {
            found = 1;
            printf("Name: %s %s\n", fname, lname);
            printf("Contact No: %ld\n", contact);
            printf("Balance: Rs %.2f\n", balance);
            break;
        }
    }

    if (!found) {
        printf("No account found with the username %s.\n", username);
    }

    printf("\nEnter 'T' to transfer money, 'M' to go to the main menu, 'C' to change username/password, or 'Q' to quit: ");
    scanf(" %c", &secondInput);
    clearBuffer();

    switch (secondInput) {
    case 'T':
    case 't':
        transferBalance(username); // Transfer money
        break;
    case 'M':
    case 'm':
        printf("Going back to main menu...\n");
        break;
    case 'C':
    case 'c':
        changeUsernamePassword(username); // Change username/password
        break;
    case 'Q':
    case 'q':
        printf("Exiting...\n");
        exit(0);
    default:
        printf("Invalid input!\n");
    }

    fclose(fp);
}

// Create new account holder
void createNewAccholder() {
    char fname[21], lname[21], username[21], password[17], cpassword[17];
    float balance;
    long contact;
    FILE *fp;

    system("clear");
    printf("Enter account holder's details:\n\n");
    printf("First Name: ");
    scanf("%20s", fname);
    capitalize(fname);
    clearBuffer();

    printf("Last Name: ");
    scanf("%20s", lname);
    capitalize(lname);
    clearBuffer();

    // Check for unique username
    while (1) {
        printf("Username: ");
        scanf("%20s", username);
        strlwr(username); // Convert to lowercase

        // Check if username already exists
        FILE *credFile = fopen("accholderCredential.csv", "r");
        if (credFile == NULL) {
            printf("Error: Unable to open accholderCredential.csv.\n");
            return;
        }

        char fileUsername[21], filePassword[17];
        int usernameExists = 0;
        while (fscanf(credFile, "%20[^,],%16s", fileUsername, filePassword) != EOF) {
            if (strcmp(username, fileUsername) == 0) {
                usernameExists = 1;
                break;
            }
        }
        fclose(credFile);

        if (!usernameExists) {
            break; // Username is unique
        } else {
            printf("Username already exists. Please choose a different username.\n");
        }
    }

    do {
        printf("Password (8-16 characters): ");
        scanf("%16s", password);
        if (strlen(password) < 8 || strlen(password) > 16) {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm password: ");
        scanf("%16s", cpassword);
    } while (strcmp(password, cpassword) != 0);

    printf("Contact: ");
    scanf("%ld", &contact);
    clearBuffer();

    printf("Enter initial balance: ");
    scanf("%f", &balance);
    clearBuffer();

    // Save to accholderCredential.csv
    fp = fopen("accholderCredential.csv", "a");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    fprintf(fp, "%s,%s\n", username, password); // Save username and password
    fclose(fp);

    // Save to details.csv
    fp = fopen("details.csv", "a");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    fprintf(fp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, username); // Save account details
    fclose(fp);

    printf("Account created successfully.\n");
}

// Function to create an admin account
void createAdminAccount() {
    char username[21], password[17], line[100];
    FILE *fp;

    system("clear");
    printf("Enter the username of the existing customer account to promote to admin: ");
    scanf("%20s", username);
    strlwr(username); // Convert to lowercase
    clearBuffer();

    // Check if the username exists in accholderCredential.csv
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%20[^,],%16s", username, password) != EOF) {
        if (strcmp(username, username) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Customer account not found.\n");
        return;
    }

    // Save to adminCredential.csv
    fp = fopen("adminCredential.csv", "a");
    if (fp == NULL) {
        printf("Error: Unable to open adminCredential.csv.\n");
        return;
    }
    fprintf(fp, "%s,%s\n", username, password); // Save username and password
    fclose(fp);

    printf("Admin account created successfully.\n");
}

// Function to change username and password
void changeUsernamePassword(char oldUsername[]) {
    char newUsername[21], newPassword[17], confirmPassword[17], line[100], tempFile[] = "temp.csv";
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter new username: ");
    scanf("%20s", newUsername);
    strlwr(newUsername); // Convert to lowercase
    clearBuffer();

    // Check if the new username is unique
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }

    int usernameExists = 0;
    while (fscanf(fp, "%20[^,],%16s", line, line) != EOF) {
        if (strcmp(newUsername, line) == 0) {
            usernameExists = 1;
            break;
        }
    }
    fclose(fp);

    if (usernameExists) {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }

    do {
        printf("Enter new password (8-16 characters): ");
        scanf("%16s", newPassword);
        if (strlen(newPassword) < 8 || strlen(newPassword) > 16) {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm new password: ");
        scanf("%16s", confirmPassword);
    } while (strcmp(newPassword, confirmPassword) != 0);

    // Update accholderCredential.csv
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%16s", line, line) != EOF) {
        if (strcmp(oldUsername, line) != 0) {
            fprintf(tempFp, "%s,%s\n", line, line);
        } else {
            fprintf(tempFp, "%s,%s\n", newUsername, newPassword);
        }
    }
    fclose(fp);
    fclose(tempFp);

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Update details.csv
    fp = fopen("details.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", line, line, &(float){0}, &(long){0}, line) != EOF) {
        if (strcmp(oldUsername, line) != 0) {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", line, line, (float){0}, (long){0}, line);
        } else {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", line, line, (float){0}, (long){0}, newUsername);
        }
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Username and password updated successfully.\n");
}

// Function to transfer balance
void transferBalance(char senderUsername[]) {
    char recipientUsername[21], line[100], tempFile[] = "temp.csv";
    float amount, senderBalance = 0, recipientBalance = 0;
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter recipient's username: ");
    scanf("%20s", recipientUsername);
    strlwr(recipientUsername); // Convert to lowercase
    clearBuffer();

    if (strcmp(senderUsername, recipientUsername) == 0) {
        printf("You cannot transfer money to yourself.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    clearBuffer();

    // Open details.csv to find recipient balances
    fp = fopen("details.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv. Make sure the file exists.\n");
        return;
    }

    int recipientFound = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", line, line, &senderBalance, &(long){0}, line) != EOF) {
        if (strcmp(senderUsername, line) == 0) {
            senderBalance = senderBalance;
        }
        if (strcmp(recipientUsername, line) == 0) {
            recipientBalance = senderBalance;
            recipientFound = 1;
        }
    }
    fclose(fp);

    if (!recipientFound) {
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

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", line, line, &senderBalance, &(long){0}, line) != EOF) {
        if (strcmp(senderUsername, line) == 0) {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", line, line, senderBalance - amount, (long){0}, line);
        } else if (strcmp(recipientUsername, line) == 0) {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", line, line, recipientBalance + amount, (long){0}, line);
        } else {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", line, line, senderBalance, (long){0}, line);
        }
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Transfer successful. New balance: Rs %.2f\n", senderBalance - amount);
}

// Function to delete account holder account
void deleteAccholderAccount() {
    char username[21], fname[21], lname[21], fileUsername[21], password[17], tempFile[] = "temp.csv";
    float balance;
    long contact;
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter Account holder's username to delete: ");
    scanf("%20s", username);
    strlwr(username); // Convert to lowercase
    clearBuffer(); // Clear the input buffer

    // Open accholderCredential.csv to remove the account
    fp = fopen("accholderCredential.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int accountFound = 0;
    while (fscanf(fp, " ,%20[^,],%16s", fileUsername, password) != EOF) {
        if (strcmp(username, fileUsername) != 0) {
            fprintf(tempFp, "%s,%s\n", fileUsername, password);
        } else {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound) {
        printf("Account not found.\n");
        remove(tempFile);
        return;
    }

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to remove the account details
    fp = fopen("details.csv", "r");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL) {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    accountFound = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) != 0) {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, fileUsername);
        } else {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound) {
        printf("Account holder details not found.\n");
        remove(tempFile);
        return;
    }

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Account holder account deleted successfully.\n");
}
