#include "login.h"

// Function to add balance to an account
void addBalance() {
    char username[21], fname[21], lname[21], fileUsername[21], fileFname[21], fileLname[21];
    float amount, fileBalance;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
    int found = 0;

    system("clear");
    printf("Enter the username of the account holder: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username); // Remove newline
    strlwr(username); // Convert to lowercase

    printf("Enter the first name of the account holder: ");
    fgets(fname, sizeof(fname), stdin);
    trimNewline(fname); // Remove newline
    capitalize(fname);

    printf("Enter the last name of the account holder: ");
    fgets(lname, sizeof(lname), stdin);
    trimNewline(lname); // Remove newline
    capitalize(lname);

    printf("Enter the amount to add: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.csv to find the account
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

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", fileFname, fileLname, &fileBalance, &(long){0}, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(fname, fileFname) == 0 && strcmp(lname, fileLname) == 0) {
            found = 1;
            fileBalance += amount; // Add the amount to the existing balance
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, (long){0}, fileUsername);
        } else {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, (long){0}, fileUsername);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found) {
        printf("Account not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.csv with the updated file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Balance added successfully. New balance: Rs %.2f\n", fileBalance);
}

// Function to withdraw balance from an account
void withdrawBalance() {
    char username[21], fname[21], lname[21], fileUsername[21], fileFname[21], fileLname[21];
    float amount, fileBalance;
    FILE *fp, *tempFp;
    char tempFile[] = "temp.csv";
    int found = 0;

    system("clear");
    printf("Enter the username of the account holder: ");
    fgets(username, sizeof(username), stdin);
    trimNewline(username); // Remove newline
    strlwr(username); // Convert to lowercase

    printf("Enter the first name of the account holder: ");
    fgets(fname, sizeof(fname), stdin);
    trimNewline(fname); // Remove newline
    capitalize(fname);

    printf("Enter the last name of the account holder: ");
    fgets(lname, sizeof(lname), stdin);
    trimNewline(lname); // Remove newline
    capitalize(lname);

    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    clearBuffer();

    if (amount <= 0) {
        printf("Invalid amount. Please enter a positive value.\n");
        return;
    }

    // Open details.csv to find the account
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

    while (fscanf(fp, "%20[^,],%20[^,],%f,%ld,%20s", fileFname, fileLname, &fileBalance, &(long){0}, fileUsername) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(fname, fileFname) == 0 && strcmp(lname, fileLname) == 0) {
            found = 1;
            if (fileBalance < amount) {
                printf("Insufficient balance.\n");
                fclose(fp);
                fclose(tempFp);
                remove(tempFile);
                return;
            }
            fileBalance -= amount; // Withdraw the amount from the existing balance
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, (long){0}, fileUsername);
        } else {
            fprintf(tempFp, "%s,%s,%.2f,%ld,%s\n", fileFname, fileLname, fileBalance, (long){0}, fileUsername);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if (!found) {
        printf("Account not found.\n");
        remove(tempFile); // Delete the temporary file
        return;
    }

    // Replace details.csv with the updated file
    remove("details.csv");
    rename(tempFile, "details.csv");

    printf("Balance withdrawn successfully. New balance: Rs %.2f\n", fileBalance);
}