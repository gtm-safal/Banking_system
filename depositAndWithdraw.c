#include "utilities.h"

// Function to deposit balance to an account
void depositBalance()
{
    char username[21];
    float amount;
    Account account;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";
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

    // Open details.dat to find the account
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
        if (strcmp(username, account.username) == 0)
        {
            found = 1;
            account.balance += amount; // Add the amount to the existing balance
            amount = account.balance;
        }
        fwrite(&account, sizeof(Account), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("Account not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.dat with the updated file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\nBalance deposited successfully.\nNew Balance: Rs %.2f\n", amount);
}

// Function to withdraw balance from an account
void withdrawBalance()
{
    char username[21];
    float amount;
    Account account;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.dat";
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

    // Open details.dat to find the account
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
        if (strcmp(username, account.username) == 0)
        {
            found = 1;
            if (account.balance < amount)
            {
                printf("Insufficient balance.\n");
                fclose(fp);
                fclose(tempFp);
                remove(tempFile);
                return;
            }
            account.balance -= amount; // Withdraw the amount from the existing balance
            amount = account.balance;
        }
        fwrite(&account, sizeof(Account), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (!found)
    {
        printf("\nAccount not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.dat with the updated file
    remove("details.dat");
    rename(tempFile, "details.dat");

    printf("\nBalance withdrawn successfully.\nNew Balance: Rs %.2f\n", amount);
}

