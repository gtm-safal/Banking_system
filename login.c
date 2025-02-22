#include "login.h"

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
            printf("Error: Unable to open admin credentials file.\n");
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
            printf("Error: Unable to open accholder credentials file.\n");
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