#include "utilities.h"

// Admin profile definition
void adminProfile(char username[])
{
    int secondInput;
    while (1)
    {
        system(CLEAR_SCREEN);
        printf("%s!\n", username);
        printf("Welcome to the Admin Profile!\n\n");
        printf("1. Create new account\n");
        printf("2. Delete account\n");
        printf("3. Create admin account\n");
        printf("4. Deposit balance\n");
        printf("5. Withdraw balance\n");
        printf("6. Transfer balance\n");
        printf("7. Exit to Main Menu\n\n");
        printf("Enter your choice: ");
        scanf("%d", &secondInput);
        clearBuffer();

        switch (secondInput)
        {
        case 1:
            createNewAccholder(); // Admin creates a new account holder account
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 2:
            deleteAccholderAccount(); // Admin deletes an account holder account
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 3:
            createAdminAccount(); // Admin creates an admin account
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 4:
            depositBalance(); // Deposit balance to an account
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 5:
            withdrawBalance(); // Withdraw balance from an account
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 6:
            transferBalanceAdmin(); // Transfer balance as admin
            printf("Press 'Enter' to continue...");
            getchar(); // Pause before continuing
            system(CLEAR_SCREEN);
            break;
        case 7:
            printf("Exiting to Main Menu...\n");
            return; // Exit to the main menu
        default:
            printf("Invalid input. Please try again.\n");
        }
    }
}

// Account holder profile definition
void accholderProfile(char username[])
{
    char fname[21], lname[21], fileUsername[21], secondInput;
    float balance;
    long contact;
    FILE *fp = fopen("details.csv", "r");
    system(CLEAR_SCREEN);

    int found = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fname, lname, &balance, &contact, fileUsername) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = 1;
            printf("Name: %s %s\n", fname, lname);
            printf("Contact No: %ld\n", contact);
            printf("Balance: Rs %.2f\n", balance);
            break;
        }
    }

    if (!found)
    {
        printf("No account found with the username %s.\n", username);
    }

    printf("\n[Enter: ]\n'T' to transfer money,\n'C' to change username/password,\n'M' to go to the main menu,\n'Q' to quit\n\n");
    scanf(" %c", &secondInput);
    clearBuffer();

    switch (secondInput)
    {
    case 'T':
    case 't':
        transferBalance(username); // Transfer money
        break;
    case 'C':
    case 'c':
        changeUsernamePassword(username); // Change username/password
        break;
    case 'M':
    case 'm':
        system(CLEAR_SCREEN);
        printf("Going back to main menu...\n");
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
        FILE *credFile = fopen("accholderCredential.csv", "r");

        char fileUsername[21], filePassword[17];
        int usernameExists = 0;
        while (fscanf(credFile, "%20[^,],%16s\n", fileUsername, filePassword) != EOF)
        {
            if (strcmp(username, fileUsername) == 0)
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

    // Save to accholderCredential.csv
    fp = fopen("accholderCredential.csv", "a");

    fprintf(fp, "%s,%s\n", username, password); // Save username and password
    fclose(fp);

    // Save to details.csv
    fp = fopen("details.csv", "a");

    fprintf(fp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, username); // Save account details
    fclose(fp);

    system(CLEAR_SCREEN);
    printf("\nAccount created successfully.\n");
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

    // Check if the username exists in accholderCredential.csv
    fp = fopen("accholderCredential.csv", "r");

    int found = 0;
    while (fscanf(fp, "%20[^,],%16s\n", fileUsername, filePassword) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = 1;
            strcpy(password, filePassword); // Copy the password
            break;
        }
    }
    fclose(fp);

    if (!found)
    {
        printf("Customer account not found.\n");
        return;
    }

    // Save to adminCredential.csv
    fp = fopen("adminCredential.csv", "a");

    fprintf(fp, "%s,%s\n", username, password); // Save username and password
    fclose(fp);

    printf("Admin account created successfully.\n");
}

// Function to change username and password
void changeUsernamePassword(char oldUsername[])
{
    char newUsername[21], newPassword[17], confirmNewPassword[17], fileUsername[21], filePassword[17];
    char fname[21], lname[21];
    float balance;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
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

    // Open accholderCredential.csv to find and update the credentials
    fp = fopen("accholderCredential.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%16s\n", fileUsername, filePassword) != EOF)
    {
        if (strcmp(oldUsername, fileUsername) == 0)
        {
            found = 1;
            fprintf(tempFp, "%s,%s\n", newUsername, newPassword);
        }
        else
        {
            fprintf(tempFp, "%s,%s\n", fileUsername, filePassword);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("Username not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace accholderCredential.csv with the updated file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to update the username
    fp = fopen("details.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fname, lname, &balance, &contact, fileUsername) != EOF)
    {
        if (strcmp(oldUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, newUsername);
        }
        else
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, fileUsername);
        }
    }

    fclose(fp);
    fclose(tempFp);

    // Replace details.csv with the updated file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nUsername and password changed successfully.\n");
    printf("Press 'Enter' to continue...");
    getchar(); // Pause before continuing
}

// Function to transfer balance for account holders
void transferBalance(char senderUsername[])
{
    char recipientUsername[21], fileFname[21], fileLname[21], fileUsername[21];
    float amount, senderBalance = 0, recipientBalance = 0;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
    int recipientFound = 0;

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

    // Open details.csv to find recipient balance
    fp = fopen("details.csv", "r");

    // Find sender's balance
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &senderBalance, &contact, fileUsername) != EOF)
    {
        if (strcmp(senderUsername, fileUsername) == 0)
        {
            break;
        }
    }
    fclose(fp);

    if (senderBalance < amount)
    {
        printf("Insufficient balance.\n");
        return;
    }

    // Open details.csv again to find recipient balance and update balances
    fp = fopen("details.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &recipientBalance, &contact, fileUsername) != EOF)
    {
        if (strcmp(senderUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, senderBalance - amount, contact, fileUsername);
        }
        else if (strcmp(recipientUsername, fileUsername) == 0)
        {
            recipientFound = 1;
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, recipientBalance + amount, contact, fileUsername);
        }
        else
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, recipientBalance, contact, fileUsername);
        }
    }
    fclose(fp);
    fclose(tempFp);

    if (!recipientFound)
    {
        printf("Recipient account not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nTransfer successful.\nNew balance: Rs %.2f\n", senderBalance - amount);
    printf("\n\nPress 'Enter' to continue...");
    getchar(); // Pause before continuing

    // Return to the account holder profile
    accholderProfile(senderUsername);
}

// Function to delete account holder account
void deleteAccholderAccount()
{
    char username[21], fname[21], lname[21], fileUsername[21], password[17], tempFile[] = "temp.csv";
    float balance;
    long contact;
    FILE *fp, *tempFp;

    system(CLEAR_SCREEN);
    printf("Enter Account holder's username to delete: ");
    scanf("%20s", username);
    clearBuffer();         // Clear the input buffer
    toLowerCase(username); // Convert to lowercase

    // Open accholderCredential.csv to remove the account
    fp = fopen("accholderCredential.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int accountFound = 0;
    while (fscanf(fp, "%20[^,],%16s\n", fileUsername, password) != EOF)
    {
        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "%s,%s\n", fileUsername, password);
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

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to remove the account details
    fp = fopen("details.csv", "r");

    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    accountFound = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fname, lname, &balance, &contact, fileUsername) == 5)
    {
        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, fileUsername);
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

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nAccount holder account deleted successfully.\n");
}

