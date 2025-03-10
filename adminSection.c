#include "utilities.h"

// Admin profile definition
void adminProfile(char username[])
{
    int secondInput;
    char senderUsername[21];
    system(CLEAR_SCREEN);
    printf("\nWelcome, %s!\n", username);
    printf("Admin Profile!\n\n");
    printf("1. Create new account holder\n");
    printf("2. Delete account holder account\n");
    printf("3. Create admin account\n");
    printf("4. Deposit balance\n");
    printf("5. Withdraw balance\n");
    printf("6. Transfer balance\n");
    printf("7. View account holders' details\n");
    printf("8. Exit to Main Menu\n\n");
    printf("Enter your choice: ");

    while (scanf("%d", &secondInput) != 1)
    {
        printf("Invalid input. Please enter a number.\n");
        while (getchar() != '\n')
            ; // Clear invalid input
    }

    switch (secondInput)
    {
    case 1:
        createNewAccholder(); // Admin creates a new account holder
        break;
    case 2:
        deleteAccholderAccount(); // Admin deletes an account holder account
        break;
    case 3:
        createAdminAccount(); // Admin creates an admin account
        break;
    case 4:
        depositBalance(); // Deposit balance to an account
        break;
    case 5:
        withdrawBalance(); // Withdraw balance from an account
        break;
    case 6:
        transferBalanceAdmin(); // Transfer balance as admin
        break;
    case 7:
        viewAccountHolders(); // View account holders' details
        break;
    case 8:
        printf("Exiting to Main Menu...\n");
        return; // Exit to the main menu
    default:
        printf("Invalid input. Please try again.\n");
    }

    printf("Press 'Enter' to continue...");
    getchar(); // Pause before continuing
    system(CLEAR_SCREEN);
    adminProfile(username); // Return to admin profile
}

// Create new account holder
void createNewAccholder()
{
    char fname[21], lname[21], username[21], password[17], cpassword[17];
    float balance;
    long contact;
    FILE *fp;

    system(CLEAR_SCREEN);
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
    while (1)
    {
        printf("Username: ");
        scanf("%20s", username);
        toLowerCase(username); // Convert to lowercase
        clearBuffer();

        // Check if username already exists
        FILE *credFile = fopen("accholderCredential.dat", "rb");
        if (credFile == NULL)
        {
            printf("Error: Unable to open file.\n");
            return;
        }

        Credential credential;
        int usernameExists = 0;
        while (fread(&credential, sizeof(Credential), 1, credFile))
        {
            if (strcmp(username, credential.username) == 0)
            {
                usernameExists = 1;
                break;
            }
        }
        fclose(credFile);

        if (!usernameExists)
        {
            break; // Username is unique
        }
        else
        {
            printf("Username already exists. Please choose a different username.\n\n");
        }
    }

    do
    {
        printf("Password (8-16 characters): ");
        getAndHidePassword(password, sizeof(password)); // Use getAndHidePassword to read the password
        if (strlen(password) < 8 || strlen(password) > 16)
        {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm password: ");
        getAndHidePassword(cpassword, sizeof(cpassword)); // Use getAndHidePassword to read the password
        if (strcmp(password, cpassword) != 0)
        {
            printf("Passwords do not match. Please try again.\n");
        }
    } while (strcmp(password, cpassword) != 0);

    while (1)
    {
        printf("Contact: ");
        scanf("%ld", &contact);
        clearBuffer();
        if (isValidContact(contact))
        {
            break;
        }
        else
        {
            printf("Invalid contact number. Please enter a 10-digit contact number.\n");
        }
    }
    do
    {
        printf("Enter initial balance: ");
        scanf("%f", &balance);
        if (balance < 0)
        {
            printf("Invalid balance. Please enter a positive value.\n");
        }
    } while (balance < 0);
    
    clearBuffer();

    // Save to accholderCredential.dat
    fp = fopen("accholderCredential.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    Credential newCredential ;
    strncpy(newCredential.username, username, sizeof(newCredential.username) - 1);
    strncpy(newCredential.password, password, sizeof(newCredential.password) - 1);
    fwrite(&newCredential, sizeof(Credential), 1, fp);
    fclose(fp);

    // Save to details.dat
    fp = fopen("details.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    Account newAccount = {0};
    strncpy(newAccount.fname, fname, sizeof(newAccount.fname) - 1);
    strncpy(newAccount.lname, lname, sizeof(newAccount.lname) - 1);
    newAccount.balance = balance;
    newAccount.contact = contact;
    strncpy(newAccount.username, username, sizeof(newAccount.username) - 1);
    fwrite(&newAccount, sizeof(Account), 1, fp);
    fclose(fp);

    system(CLEAR_SCREEN);
    printf("\nAccount created successfully.\n");
}

// Function to delete account holder account
void deleteAccholderAccount()
{
    char username[21];
    Account account;
    Credential credential;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";

    system(CLEAR_SCREEN);
    printf("Enter Account holder's username to delete: ");
    scanf("%20s", username);
    clearBuffer();         // Clear the input buffer
    toLowerCase(username); // Convert to lowercase

    // Open accholderCredential.dat to remove the account
    fp = fopen("accholderCredential.dat", "rb");
    tempFp = fopen(tempFile, "wb");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int accountFound = 0;
    while (fread(&credential, sizeof(Credential), 1, fp))
    {
        if (strcmp(username, credential.username) != 0)
        {
            fwrite(&credential, sizeof(Credential), 1, tempFp);
        }
        else
        {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound)
    {
        printf("\nAccount not found.\n");
        remove(tempFile);
        return;
    }

    // Replace accholderCredential.dat with updated temp file
    remove("accholderCredential.dat");
    rename(tempFile, "accholderCredential.dat");

    // Open details.dat to remove the account details
    fp = fopen("details.dat", "rb");
    tempFp = fopen(tempFile, "wb");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    accountFound = 0;
    while (fread(&account, sizeof(Account), 1, fp))
    {
        if (strcmp(username, account.username) != 0)
        {
            fwrite(&account, sizeof(Account), 1, tempFp);
        }
        else
        {
            accountFound = 1;
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!accountFound)
    {
        printf("\nAccount holder details not found.\n");
        remove(tempFile);
        return;
    }

    // Replace details.dat with updated temp file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\nAccount holder account deleted successfully.\n");
}

// Function to create an admin account
void createAdminAccount()
{
    char username[21], password[17], fileUsername[21], filePassword[17];
    FILE *fp;

    system(CLEAR_SCREEN);
    printf("[Note: Admin account can be created only for existing customer accounts.]\n\n");
    printf("Enter the username of new admin: ");
    scanf("%20s", username);
    toLowerCase(username); // Convert to lowercase
    clearBuffer();

    // Check if the username exists in accholderCredential.dat
    fp = fopen("accholderCredential.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    Credential credential;
    int found = 0;
    while (fread(&credential, sizeof(Credential), 1, fp))
    {
        if (strcmp(username, credential.username) == 0)
        {
            found = 1;
            strncpy(password, credential.password, sizeof(password) - 1); // Copy the password
            break;
        }
    }
    fclose(fp);

    if (!found)
    {
        printf("Customer account not found.\n");
        return;
    }

    // Save to adminCredential.dat
    fp = fopen("adminCredential.dat", "ab");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    Credential newAdmin = {0};
    strncpy(newAdmin.username, username, sizeof(newAdmin.username) - 1);
    strncpy(newAdmin.password, password, sizeof(newAdmin.password) - 1);
    fwrite(&newAdmin, sizeof(Credential), 1, fp);
    fclose(fp);

    printf("Admin account created successfully.\n");
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

// Function to view account holders' details
void viewAccountHolders()
{
    Credential credential;
    Account account;
    FILE *fp = fopen("details.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }
    FILE *fpp = fopen("accholderCredential.dat", "rb");
    if (fpp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    system(CLEAR_SCREEN);
    printf("\nAccount Holders' Details:\n");
    printf("+----------------------+----------------------+----------------------+--------------+----------------------+------------------+\n");
    printf("| First Name           | Last Name            | Balance              | Contact      | Username             | Password         |\n");
    printf("+----------------------+----------------------+----------------------+--------------+----------------------+------------------+\n");

    while (fread(&account, sizeof(Account), 1, fp) && fread(&credential, sizeof(Credential), 1, fpp))
    {
        if (strcmp(account.username, credential.username) != 0)
        {
            printf("Error: Data mismatch.\n");
            return;
        }
        printf("| %-20s | %-20s | %-20.2f | %-12ld | %-20s | %-16s |\n",
               account.fname, account.lname, account.balance, account.contact, account.username, credential.password);
    }

    printf("+----------------------+----------------------+----------------------+--------------+----------------------+------------------+\n");

    fclose(fp);
    getchar(); // Pause before continuing

}

