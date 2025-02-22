#include "login.h"

void clearBuffer() {
    while (getchar() != '\n'); // Clear remaining input
}

void login(int input) {
    char username[20] = {0}, pass[16] = {0}, fileUsername[20] = {0}, filePass[16] = {0};
    system("clear");

    printf("\nEnter username: ");
    scanf("%19s", username);
    printf("Enter password: ");
    scanf("%15s", pass);
    clearBuffer();

    FILE *fp;
    if (input == 1) { // Admin login
        fp = fopen("adminCredential.csv", "r");
        if (fp == NULL) {
            printf("Error: Unable to open adminCredential.csv. Make sure the file exists.\n");
            return;
        }

        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0) {
                system("clear");
                printf("Successfully logged in as Admin.\nPress 'Enter' to continue.\n");
                getchar(); // Wait for Enter key
                fclose(fp);
                adminProfile(username); // Redirect to admin profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    } else if (input == 2) { // Accholder login
        fp = fopen("accholderCredential.csv", "r");
        if (fp == NULL) {
            printf("Error: Unable to open accholderCredential.csv. Make sure the file exists.\n");
            return;
        }

        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0) {
                system("clear");
                printf("Successfully logged in as Accholder.\nPress 'Enter' to continue.\n");
                getchar(); // Wait for Enter key
                fclose(fp);
                accholderProfile(username); // Redirect to accholder profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    } else {
        printf("Invalid input.\n");
    }

    getchar(); // Catch Enter after failed login attempt
}

void createNewAccholder() {
    char name[20] = {0}, username[20] = {0}, password[16] = {0}, fileUsername[20] = {0};
    float balance;
    long phno;
    FILE *fp;

    system("clear");
    printf("Enter accholder's name: ");
    scanf("%19s", name);

    // Check for unique username
    while (1) {
        printf("Enter new username: ");
        scanf("%19s", username);

        fp = fopen("accholderCredential.csv", "r");
        if (fp == NULL) {
            // If the file doesn't exist, the username is automatically unique
            break;
        }

        int usernameExists = 0;
        while (fscanf(fp, "%19[^,],%15s", fileUsername, password) != EOF) {
            if (strcmp(username, fileUsername) == 0) {
                usernameExists = 1;
                break;
            }
        }
        fclose(fp);

        if (!usernameExists) {
            break; // Username is unique
        } else {
            printf("Username already exists. Please choose a different username.\n");
        }
    }

    printf("Enter new password: ");
    scanf("%15s", password);

    printf("Enter accholder's phone number: ");
    scanf("%ld", &phno);

    printf("Enter initial balance: ");
    scanf("%f", &balance);

    // Save to accholderCredential.csv
    fp = fopen("accholderCredential.csv", "a");
    if (fp == NULL) {
        printf("Error: Unable to open accholderCredential.csv.\n");
        return;
    }
    fprintf(fp, "%s,%s\n", username, password); // Save username and password
    fclose(fp);

    // Save to details.csv
    fp = fopen("details.csv", "a");
    if (fp == NULL) {
        printf("Error: Unable to open details.csv.\n");
        return;
    }
    fprintf(fp, "%s,%.2f,%ld,%s\n", name, balance, phno, username); // Save account details
    fclose(fp);

    printf("Accholder account created successfully.\nPress 'Enter' to continue.");
    getchar(); getchar(); // Pause before returning
}