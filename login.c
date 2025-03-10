#include "utilities.h"

// Function to login Portal
void login(int input)
{
    char username[21], pass[17];
    Credential credential;
    system(CLEAR_SCREEN);

    printf("\nEnter username: ");
    scanf("%20s", username);
    trimNewline(username); // Remove newline
    toLowerCase(username); // Convert to lowercase

    clearBuffer(); 
    printf("Enter password: ");
    getAndHidePassword(pass, sizeof(pass)); // Use getAndHidePassword to read the password

    FILE *fp;
    if (input == 1)
    { // Admin login
        fp = fopen("adminCredential.dat", "rb");

        while (fread(&credential, sizeof(Credential), 1, fp))
        {
            if (strcmp(username, credential.username) == 0 && strcmp(pass, credential.password) == 0)
            {
                system(CLEAR_SCREEN);
                printf("\nSuccessfully logged in as Admin.\nPress 'Enter' to continue.\n");
                getchar(); // Wait for Enter key
                fclose(fp);
                adminProfile(username); // Redirect to admin profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    }
    else if (input == 2)
    { // Accholder login
        fp = fopen("accholderCredential.dat", "rb");

        while (fread(&credential, sizeof(Credential), 1, fp))
        {
            if (strcmp(username, credential.username) == 0 && strcmp(pass, credential.password) == 0)
            {
                system(CLEAR_SCREEN);
                printf("\nSuccessfully logged in as Account holder.\nPress 'Enter' to continue.\n");
                getchar(); // Wait for Enter key
                fclose(fp);
                accholderProfile(username); // Redirect to accholder profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    }
    else
    {
        printf("Invalid input.\n");
    }

    getchar(); // Catch Enter after failed login attempt
}

// Function to transfer balance for admin
void transferBalanceAdmin()
{
    char senderUsername[21], recipientUsername[21];
    float amount, senderBalance = 0, recipientBalance = 0;
    Account account;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";
    int senderFound = 0, recipientFound = 0;

    system(CLEAR_SCREEN);
    printf("Enter sender's username: ");
    scanf("%20s", senderUsername);
    clearBuffer();
    toLowerCase(senderUsername); // Convert to lowercase

    printf("Enter recipient's username: ");
    scanf("%20s", recipientUsername);
    clearBuffer();
    toLowerCase(recipientUsername); // Convert to lowercase

    if (strcmp(senderUsername, recipientUsername) == 0)
    {
        printf("You cannot transfer money to the same account.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0.00)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.dat to find sender and recipient balances
    fp = fopen("details.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.dat file.\n");
        return;
    }

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
        printf("\nInsufficient balance.\n");
        return;
    }

    // Open details.dat again to update balances
    fp = fopen("details.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.dat file.\n");
        return;
    }

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
            account.balance = senderBalance - amount;
        }
        else if (strcmp(recipientUsername, account.username) == 0)
        {
            account.balance = recipientBalance + amount;
        }
        fwrite(&account, sizeof(Account), 1, tempFp);
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.dat with updated temp file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\n\nTransfer successful.\n");
    printf("\nSender (%s) 's new balance: Rs %.2f\n", senderUsername, senderBalance - amount);
    printf("Recipient (%s) 's new balance: Rs %.2f\n", recipientUsername, recipientBalance + amount);
    printf("\n\nPress 'Enter' to continue...");
    getchar(); // Pause before continuing

    // Return to admin profile
    adminProfile(senderUsername);
}

