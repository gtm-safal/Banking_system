#include "utilities.h"

void login(int input)
{
    char username[21], pass[17], fileUsername[21], filePass[17];
    system(CLEAR_SCREEN);

    printf("\nEnter username: ");
    scanf("%20s", username);
    trimNewline(username); // Remove newline
    toLowerCase(username); // Convert to lowercase

    printf("Enter password: ");
    scanf("%16s", pass);
    trimNewline(pass); // Remove newline

    FILE *fp;
    if (input == 1)
    { // Admin login
        fp = fopen("adminCredential.csv", "r");
        
        while (fscanf(fp, "%20[^,],%16s\n", fileUsername, filePass) != EOF)
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0)
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
        fp = fopen("accholderCredential.csv", "r");
        
        while (fscanf(fp, "%20[^,],%16s\n", fileUsername, filePass) != EOF)
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0)
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
    char senderUsername[21], recipientUsername[21], fileFname[21], fileLname[21], fileUsername[21];
    float amount, senderBalance = 0, recipientBalance = 0;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
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

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.csv to find sender and recipient balances
    fp = fopen("details.csv", "r");
    
    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &senderBalance, &contact, fileUsername) != EOF)
    {
                if (strcmp(recipientUsername, fileUsername) == 0)
        {
            recipientFound = 1;
            recipientBalance = senderBalance;
        }
    }
    fclose(fp);

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

    // Open details.csv again to update balances
    fp = fopen("details.csv", "r");
    
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &senderBalance, &contact, fileUsername) != EOF)
    {
        if (strcmp(senderUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, senderBalance - amount, contact, fileUsername);
        }
        else if (strcmp(recipientUsername, fileUsername) == 0)
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, recipientBalance + amount, contact, fileUsername);
        }
        else
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, senderBalance, contact, fileUsername);
        }
    }
    fclose(fp);
    fclose(tempFp);

    // Replace details.csv with updated temp file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nTransfer successful.\n");
    printf("Sender (%s) 's new balance: Rs %.2f\n", senderUsername, senderBalance - amount);
    printf("Recipient (%s) 's new balance: Rs %.2f\n", recipientUsername, recipientBalance + amount);
    printf("\n\nPress 'Enter' to continue...");
    getchar(); // Pause before continuing

    // Return to admin profile
    adminProfile(senderUsername);
}
