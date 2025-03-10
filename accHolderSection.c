#include "utilities.h"

// Account holder profile definition
void accholderProfile(char username[])
{
    Account account;
    FILE *fp = fopen("details.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }
    system(CLEAR_SCREEN);

    int found = 0;
    while (fread(&account, sizeof(Account), 1, fp))
    {
        if (strcmp(username, account.username) == 0)
        {
            found = 1;
            printf("Name: %s %s\n", account.fname, account.lname);
            printf("Contact No: %ld\n", account.contact);
            printf("Balance: Rs %.2f\n", account.balance);
            break;
        }
    }

    fclose(fp);

    if (!found)
    {
        printf("No account found with the username %s.\n", username);
        return;
    }

    char secondInput;
    printf("\n[Enter: ]\n'T' to transfer money,\n'C' to change username/password,\n'M' to go to the main menu,\n'Q' to quit\n\n");
    scanf(" %c", &secondInput);
    clearBuffer();

    switch (secondInput)
    {
    case 'T':
    case 't':
        transferBalance(username);
        break;
    case 'C':
    case 'c':
        changeUsernamePassword(username);
        break;
    case 'M':
    case 'm':
        return;
    case 'Q':
    case 'q':
        exit(0);
    default:
        printf("Invalid input. Please try again.\n");
    }

    printf("Press 'Enter' to continue...");
    getchar(); // Pause before continuing
    accholderProfile(username); // Return to account holder profile
}

// Function to change username and password
void changeUsernamePassword(char oldUsername[])
{
    char newUsername[21], newPassword[17], confirmNewPassword[17], fileUsername[21], filePassword[17];
    Credential credential;
    Account account;
    char fname[21], lname[21];
    float balance;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";
    int found = 0;

    system(CLEAR_SCREEN);
    printf("Enter new username: ");
    scanf("%20s", newUsername);
    clearBuffer();
    toLowerCase(newUsername); // Convert to lowercase

    do {
        printf("Enter new password (8-16 characters): ");
        getAndHidePassword(newPassword, sizeof(newPassword)); // Use getAndHidePassword to read the password
        if (strlen(newPassword) < 8 || strlen(newPassword) > 16) {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm new password: ");
        getAndHidePassword(confirmNewPassword, sizeof(confirmNewPassword)); // Use getAndHidePassword to read the password
        if (strcmp(newPassword, confirmNewPassword) != 0) {
            printf("Passwords do not match. Please try again.\n");
        }
    } while (strcmp(newPassword, confirmNewPassword) != 0);

    // Open accholderCredential.dat to find and update the credentials
    fp = fopen("accholderCredential.dat", "rb");

    tempFp = fopen(tempFile, "wb");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&credential, sizeof(Credential), 1, fp))
    {
        if (strcmp(oldUsername, credential.username) == 0)
        {
            found = 1;
            strncpy(credential.username, newUsername, sizeof(credential.username) - 1);
            strncpy(credential.password, newPassword, sizeof(credential.password) - 1);
        }
        fwrite(&credential, sizeof(Credential), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("Username not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace accholderCredential.dat with the updated file
    remove("accholderCredential.dat");
    rename(tempFile, "accholderCredential.dat");

    // Open details.dat to update the username
    fp = fopen("details.dat", "rb");

    tempFp = fopen(tempFile, "wb");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&account, sizeof(Account), 1, fp))
    {
        if (strcmp(oldUsername, account.username) == 0)
        {
            strncpy(account.username, newUsername, sizeof(account.username) - 1);
        }
        fwrite(&account, sizeof(Account), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    // Replace details.dat with the updated file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\nUsername and password changed successfully.\n");

}

// Function to transfer balance for account holders
void transferBalance(char senderUsername[])
{
    char recipientUsername[21];
    Account account;
    float amount, senderBalance = 0, recipientBalance = 0;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";
    int recipientFound = 0, senderFound = 0;

    system(CLEAR_SCREEN);
    while (1)
    {
        printf("Enter recipient's username: ");
        scanf("%20s", recipientUsername);
        clearBuffer();
        toLowerCase(recipientUsername); // Convert to lowercase

        if (strcmp(senderUsername, recipientUsername) == 0)
        {
            printf("\nYou cannot transfer money to yourself.\n\n");
            continue;
        }
        break; // Exit the loop if a valid recipient username is entered
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.dat to find sender and recipient balances
    fp = fopen("details.dat", "rb");

    while (fread(&account, sizeof(Account), 1, fp))
    {
        if (strcmp(senderUsername, account.username) == 0)
        {
            senderFound = 1;
            senderBalance = account.balance;
        }
        if (strcmp(recipientUsername, account.username) == 0)
        {
            recipientFound = 1;
            recipientBalance = account.balance;
        }
    }
    fclose(fp);

    if (!senderFound)
    {
        printf("Sender not found.\n");
        return;
    }

    if (!recipientFound)
    {
        printf("Recipient not found.\n");
        return;
    }

    if (senderBalance < amount)
    {
        printf("Insufficient balance.\n");
        return;
    }

    // Open details.dat again to update balances
    fp = fopen("details.dat", "rb");
    tempFp = fopen(tempFile, "wb");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&account, sizeof(Account), 1, fp))
    {
        if (strcmp(senderUsername, account.username) == 0)
        {
            account.balance -= amount;
            senderBalance = account.balance;
        }
        else if (strcmp(recipientUsername, account.username) == 0)
        {
            account.balance += amount;
            recipientBalance = account.balance;
        }
        fwrite(&account, sizeof(Account), 1, tempFp);
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.dat with updated temp file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\nTransfer successful.\nNew balance: Rs %.2f\n", senderBalance);
    printf("\n\nPress 'Enter' to continue...");
    getchar(); // Pause before continuing

    // Return to the account holder profile
    accholderProfile(senderUsername);
}
