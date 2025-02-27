#include "login.h"

// Function to check if a username is unique
int isUsernameUnique(char *username)
{
    FILE *fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return 0;
    }

    char fileUsername[21], password[17];
    while (fscanf(fp, "\n%20[^,],%16s", fileUsername, password) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            fclose(fp);
            return 0; // Username is not unique
        }
    }
    fclose(fp);
    return 1; // Username is unique
}

// Admin profile definition
void adminProfile(char username[])
{
    int secondInput;
    while (1)
    {
        system("clear");
        printf("Welcome to the Admin Profile!\n");
        printf("1. Create new account\n");
        printf("2. Delete account\n");
        printf("3. Create admin account\n");
        printf("4. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &secondInput);
        switch (secondInput)
        {
        case 1:
            createNewAccholder(); // Admin creates a new accholder account
            break;
        case 2:
            deleteAccholderAccount(); // Admin deletes a accholder account
            break;
        case 3:
            createAdminAccount(); // Admin creates an admin account
            break;
        case 4:
            return; // Exit to the main menu
        default:
            printf("Invalid input. Please try again.\n");
        }
        printf("Press 'Enter' to continue...");
        getchar();
        getchar(); // Pause before continuing
    }
}

// Function to create an admin account
void createAdminAccount()
{
    char username[21], password[17], line[100];
    FILE *fp;

    system("clear");
    printf("Enter the username of the existing customer account to promote to admin: ");
    scanf("%20s", username);

    // Check if the username exists in accholderCredential.csv
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }

    int accountFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char fileUsername[21], filePassword[17];
        sscanf(line, "%20[^,],%16s", fileUsername, filePassword);

        if (strcmp(username, fileUsername) == 0)
        {
            strcpy(password, filePassword);
            accountFound = 1;
            break;
        }
    }
    fclose(fp);

    if (!accountFound)
    {
        printf("Customer account not found.\n");
        return;
    }

    // Save to adminCredential.csv
    fp = fopen("adminCredential.csv", "a");
    if (fp == NULL)
    {
        printf("Error: Unable to open adminCredential.csv.\n");
        return;
    }
    fprintf(fp, "\n%s,%s", username, password); // Save username and password
    fflush(fp);
    fseek(fp, 0, SEEK_END);
    fclose(fp);

    printf("Admin account created successfully.\n");
}

// Accholder profile definition
void accholderProfile(char username[])
{
    char fname[21], lname[21], fileUsername[21], secondInput;
    float balance;
    long contact;
    FILE *fp = fopen("details.csv", "r");

    if (fp == NULL)
    {
        printf("Error: Unable to open details.csv.\n");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = 1;
            printf("Name: %s %s\n", fname, lname);
            printf("Contact No: %ld\n", contact);
            printf("Balance: Rs %.3f\n", balance);
            break;
        }
    }

    if (!found)
    {
        printf("No account found with the username %s.\n", username);
    }

    printf("\nEnter 'T' to transfer money, 'M' to go to the main menu, 'C' to change username/password, or 'Q' to quit: ");
    scanf(" %c", &secondInput);

    switch (secondInput)
    {
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

// Function to change username and password
void changeUsernamePassword(char oldUsername[])
{
    char newUsername[21], newPassword[17], confirmPassword[17], line[100], tempFile[] = "temp.csv";
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter new username: ");
    scanf("%20s", newUsername);

    // Check if the new username is unique
    if (!isUsernameUnique(newUsername))
    {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }

    do
    {
        printf("Enter new password (8-16 characters): ");
        scanf("%16s", newPassword);
        if (strlen(newPassword) < 8 || strlen(newPassword) > 16)
        {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm new password: ");
        scanf("%16s", confirmPassword);
    } while (strcmp(newPassword, confirmPassword) != 0);

    // Update accholderCredential.csv
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char fileUsername[21], password[17];
        sscanf(line, "%20[^,],%16s", fileUsername, password);

        if (strcmp(oldUsername, fileUsername) != 0)
        {
            fprintf(tempFp, "\n%s", line);
        }
        else
        {
            fprintf(tempFp, "\n%s,%s", newUsername, newPassword);
        }
    }
    fclose(fp);
    fflush(tempFp);
    fseek(tempFp, 0, SEEK_END);
    fclose(tempFp);

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Update details.csv
    fp = fopen("details.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char fname[21], lname[21], fileUsername[21];
        long contact;
        float balance;
        sscanf(line, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername);

        if (strcmp(oldUsername, fileUsername) != 0)
        {
            fprintf(tempFp, "\n%s", line);
        }
        else
        {
            fprintf(tempFp, "\n%s,%s,%.2f,%ld,%s", fname, lname, balance, contact, newUsername);
        }
    }
    fclose(fp);
    fflush(tempFp);
    fseek(tempFp, 0, SEEK_END);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Username and password updated successfully.\n");
}

// Create new Account
void createNewAccholder()
{
    char fname[21], lname[21], username[21], password[17], cpassword[17], fileUsername[21];
    float balance;
    long contact;
    FILE *fp;

    system("clear");
    printf("Enter account holder's details:\n\n");
    printf("First Name: ");
    scanf("%20s", fname);
    printf("Last Name: ");
    scanf("%20s", lname);
    clearBuffer();

    // Check for unique username
    while (1)
    {
        printf("Username: ");
        scanf("%20s", username);

        fp = fopen("accholderCredential.csv", "r");
        if (fp == NULL)
        {
            printf("Error: Unable to open accholderCredential.csv.\n");
            return;
        }

        int usernameExists = 0;
        while (fscanf(fp, "\n%20[^,],%16s", fileUsername, password) != EOF)
        {
            if (strcmp(username, fileUsername) == 0)
            {
                usernameExists = 1;
                break;
            }
        }
        fclose(fp);

        if (!usernameExists)
        {
            break; // Username is unique
        }
        else
        {
            printf("Username already exists. Please choose a different username.\n");
        }
    }

    do
    {
        printf("Password (8-16 characters): ");
        scanf("%16s", password);
        if (strlen(password) < 8 || strlen(password) > 16)
        {
            printf("Password must be between 8 to 16 characters long.\n");
            continue;
        }
        printf("Confirm password: ");
        scanf("%16s", cpassword);
    } while (strcmp(password, cpassword) != 0);

    printf("Contact: ");
    scanf("%ld", &contact);

    printf("Enter initial balance: ");
    scanf("%f", &balance);

    trimNewline(username); // Remove newline characters
    trimNewline(password); // Remove newline characters

    // Save to accholderCredential.csv
    fp = fopen("accholderCredential.csv", "a");
    if (fp == NULL)
    {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    fprintf(fp, "\n%s,%s", username, password); // Save username and password
    fflush(fp);
    fseek(fp, 0, SEEK_END);
    fclose(fp);

    // Save to details.csv
    fp = fopen("details.csv", "a");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    fprintf(fp, "\n%s,%s,%.2f,%ld,%s", fname, lname, balance, contact, username); // Save account details
    fflush(fp);
    fseek(fp, 0, SEEK_END);
    fclose(fp);

    printf("Account created successfully.\n");
}

// Function to transfer balance
void transferBalance(char senderUsername[])
{
    char recipientUsername[21], line[100], tempFile[] = "temp.csv";
    float amount, senderBalance = 0, recipientBalance = 0;
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter recipient's username: ");
    scanf("%20s", recipientUsername);

    if (strcmp(senderUsername, recipientUsername) == 0)
    {
        printf("You cannot transfer money to yourself.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    // Open details.csv to find sender and recipient balances
    fp = fopen("details.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.csv. Make sure the file exists.\n");
        return;
    }

    int senderFound = 0, recipientFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char fname[21], lname[21], fileUsername[21];
        long contact;
        float balance;
        sscanf(line, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername);

        if (strcmp(senderUsername, fileUsername) == 0)
        {
            senderBalance = balance;
            senderFound = 1;
        }
        if (strcmp(recipientUsername, fileUsername) == 0)
        {
            recipientBalance = balance;
            recipientFound = 1;
        }
    }
    fclose(fp);

    if (!senderFound || !recipientFound)
    {
        printf("Sender or recipient not found.\n");
        return;
    }

    if (senderBalance < amount)
    {
        printf("Insufficient balance.\n");
        return;
    }

    // Write updated balances to temp file
    fp = fopen("details.csv", "r");
    tempFp = fopen(tempFile, "w");
    if (fp == NULL || tempFp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }

    while (fgets(line, sizeof(line), fp))
    {
        char fname[21], lname[21], fileUsername[21];
        long contact;
        float balance;
        sscanf(line, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername);

        if (strcmp(senderUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "\n%s,%s,%.2f,%ld,%s", fname, lname, senderBalance - amount, contact, fileUsername);
        }
        else if (strcmp(recipientUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "\n%s,%s,%.2f,%ld,%s", fname, lname, recipientBalance + amount, contact, fileUsername);
        }
        else
        {
            fprintf(tempFp, "\n%s", line);
        }
    }
    fclose(fp);
    fflush(tempFp);
    fseek(tempFp, 0, SEEK_END);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Transfer successful. New balance: Rs %.2f\n", senderBalance - amount);
}

// Function to delete accholder account
void deleteAccholderAccount()
{
    char username[21], line[100], tempFile[] = "temp.csv";
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter Account holder's username to delete: ");
    scanf("%20s", username);
    clearBuffer();
    
    // Open accholderCredential.csv to remove the account
    fp = fopen("accholderCredential.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    int accountFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char fileUsername[21], password[17];
        sscanf(line, "%20[^,],%16s", fileUsername, password);

        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "\n%s", line);
        }
        else
        {
            accountFound = 1;
        }
    }
    fclose(fp);
    fflush(tempFp);
    fseek(tempFp, 0, SEEK_END);
    fclose(tempFp);

    if (!accountFound)
    {
        printf("Account not found.\n");
        remove(tempFile);
        return;
    }

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to remove the account details
    fp = fopen("details.csv", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    accountFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char fname[21], lname[21], fileUsername[21];
        long contact;
        float balance;
        sscanf(line, "%20[^,],%20[^,],%f,%ld,%20s", fname, lname, &balance, &contact, fileUsername);

        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "\n%s", line);
        }
        else
        {
            accountFound = 1;
        }
    }
    fclose(fp);
    fflush(tempFp);
    fseek(tempFp, 0, SEEK_END);
    fclose(tempFp);

    if (!accountFound)
    {
        printf("Accholder details not found.\n");
        remove(tempFile);
        return;
    }

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Accholder account deleted successfully.\n");
}