#include "utilities.h"

// Function to deposit balance to an account
void depositBalance()
{
    char username[21], fileFname[21], fileLname[21], fileUsername[21];
    float amount, fileBalance;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
    int found = 0;

    system(CLEAR_SCREEN);
    printf("Enter the username of the account holder: ");
    scanf("%20s", username);
    clearBuffer();
    toLowerCase(username); // Convert to lowercase

    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.csv to find the account
    fp = fopen("details.csv", "r");
    
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &fileBalance, &contact, fileUsername) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = 1;
            fileBalance += amount; // Add the amount to the existing balance
            amount = fileBalance;
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, contact, fileUsername);
        }
        else
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, contact, fileUsername);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("Account not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.csv with the updated file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nBalance deposited successfully.\nNew Balance: Rs %.2f\n", amount);
}

// Function to withdraw balance from an account
void withdrawBalance()
{
    char username[21], fileFname[21], fileLname[21], fileUsername[21];
    float amount, fileBalance;
    long contact;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
    int found = 0;

    system(CLEAR_SCREEN);
    printf("Enter the username of the account holder: ");
    scanf("%20s", username);
    clearBuffer();
    toLowerCase(username); // Convert to lowercase

    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0)
    {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.csv to find the account
    fp = fopen("details.csv", "r");
    
    tempFp = fopen(tempFile, "w");
    if (tempFp == NULL)
    {
        printf("Error: Unable to open temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s\n", fileFname, fileLname, &fileBalance, &contact, fileUsername) != EOF)
    {
        if (strcmp(username, fileUsername) == 0)
        {
            found = 1;
            if (fileBalance < amount)
            {
                printf("Insufficient balance.\n");
                fclose(fp);
                fclose(tempFp);
                remove(tempFile);
                return;
            }
            fileBalance -= amount; // Withdraw the amount from the existing balance
            amount = fileBalance;
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, contact, fileUsername);
        }
        else
        {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, contact, fileUsername);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("\nAccount not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.csv with the updated file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("\nBalance withdrawn successfully.\nNew Balance: Rs %.2f\n", amount);
}

