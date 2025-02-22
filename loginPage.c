#include "login.h"

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
        printf("3. Exit to Main Menu\n");
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
            return; // Exit to the main menu
        default:
            printf("Invalid input. Please try again.\n");
        }
        printf("Press 'Enter' to continue...");
        getchar();
        getchar(); // Pause before continuing
    }
}

// Accholder profile definition
void accholderProfile(char username[])
{
    char fname[20],lname[20] , fileUsername[20] , secondInput;
    float balance;
    long contact;
    FILE *fp = fopen("details.csv", "r");

    int found = 0;
    while (fscanf(fp, "%19[^,],%19[^,],%f,%ld,%19s", fname, lname, &balance, &contact, fileUsername) != EOF)
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

    printf("\nEnter 'T' to transfer money, 'M' to go to the main menu, or 'Q' to quit: ");
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
    case 'Q':
    case 'q':
        printf("Exiting...\n");
        exit(0);
    default:
        printf("Invalid secondInput!\n");
    }

    fclose(fp);
}

//Create new Account

void createNewAccholder()
{
    char fname[20], lname[20], username[20], password[16], cpassword[16], fileUsername[20];
    float balance;
    long contact;
    FILE *fp;

    system("clear");
    printf("Enter account holder's details:\n\n");
    printf("First Name: ");
    scanf("%19s", fname);
    printf("Last Name: ");
    scanf("%19s", lname);
    clearBuffer();

    // Check for unique username
    while (1)
    {
        printf("Username: ");
        scanf("%19s", username);

        fp = fopen("accholderCredential.csv", "r");

        int usernameExists = 0;
        while (fscanf(fp, "\n%19[^,],%15s", fileUsername, password) != EOF)
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
        printf("Password: ");
        scanf("%15s", password);
        printf("Confirm password: ");
        scanf("%15s", cpassword);
    }
    while(strcmp(password, cpassword) !=0);
    

    printf("Contact: ");
    scanf("%ld", &contact);

    printf("Enter initial balance: ");
    scanf("%f", &balance);

    trimNewline(username); // Remove newline characters
    trimNewline(password); // Remove newline characters

    // Save to accholderCredential.csv
    fp = fopen("accholderCredential.csv", "a");
    fprintf(fp, "\n%s,%s", username, password); // Save username and password
    fclose(fp);

    // Save to details.csv
    fp = fopen("details.csv", "a");
    fprintf(fp, "%s,%s,%.2f,%ld,%s\n", fname, lname, balance, contact, username); // Save account details
    fclose(fp);

    printf("Account created successfully.\n");
}
// Function to transfer balance
void transferBalance(char senderUsername[])
{
    char recipientUsername[20], line[100], tempFile[] = "temp.csv";
    float amount, senderBalance = 0, recipientBalance = 0;
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter recipient's username: ");
    scanf("%19s", recipientUsername);

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
    { // Fixed typo here
        char name[20], fileUsername[20];
        long contact;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &contact, fileUsername);

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
        char name[20], fileUsername[20];
        long contact;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &contact, fileUsername);

        if (strcmp(senderUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%.2f,%ld,%s\n", name, senderBalance - amount, contact, fileUsername);
        }
        else if (strcmp(recipientUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%.2f,%ld,%s\n", name, recipientBalance + amount, contact, fileUsername);
        }
        else
        {
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

// Function to delete accholder account
void deleteAccholderAccount()
{
    char username[20], line[100], tempFile[] = "temp.csv";
    FILE *fp, *tempFp;

    system("clear");
    printf("Enter Account holder's username to delete: ");
    scanf("%19s", username);
    clearBuffer();
    
    // Open accholderCredential.csv to remove the account
    fp = fopen("accholderCredential.csv", "r");
    tempFp = fopen(tempFile, "w");

    int accountFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char fileUsername[20], password[16];
        sscanf(line, "\n%19[^,],%15s", fileUsername, password);

        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "%s", line);
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
        printf("Account not found.\n");
        remove(tempFile);
        return;
    }

    // Replace accholderCredential.csv with updated temp file
    remove("accholderCredential.csv");
    rename(tempFile, "accholderCredential.csv");

    // Open details.csv to remove the account details
    fp = fopen("details.csv", "r");

    tempFp = fopen(tempFile, "w");

    accountFound = 0;
    while (fgets(line, sizeof(line), fp))
    {
        char name[20], fileUsername[20];
        long contact;
        float balance;
        sscanf(line, "%19[^,],%f,%ld,%19s", name, &balance, &contact, fileUsername);

        if (strcmp(username, fileUsername) != 0)
        {
            fprintf(tempFp, "%s", line);
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
        printf("Accholder details not found.\n");
        remove(tempFile);
        return;
    }

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Accholder account deleted successfully.\n");
}