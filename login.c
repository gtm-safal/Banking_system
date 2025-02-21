#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "loginPage.c"

void clearBuffer() {
    while (getchar() != '\n')
        ; // Clear remaining input
}

void login(int input) {
    char username[20], pass[16], fileUsername[20], filePass[16], pseudo;
    system("clear");
    printf("\nEnter username: ");
    scanf("%19s", username); // Prevents buffer overflow
    printf("Enter password: ");
    scanf("%15s", pass);
    clearBuffer();

    FILE *fp;
    if (input == 1) { // Agent login
        fp = fopen("adminCredential.csv", "r");
        if (fp == NULL) {
            printf("Error opening admin credentials file.\n");
            return;
        }

        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0) {
                system("clear");
                printf("Successfully logged in as Agent.\nPress 'Enter' to continue.\n");
                pseudo = getchar();
                fclose(fp);
                adminProfile(username); // Call admin profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    } else if (input == 2) { // Customer login
        fp = fopen("customerCredential.csv", "r");
        if (fp == NULL) {
            printf("Error opening customer credentials file.\n");
            return;
        }

        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0) {
                system("clear");
                printf("Successfully logged in as Customer.\nPress 'Enter' to continue.\n");
                pseudo = getchar();
                fclose(fp);
                customerProfile(username); // Call customer profile
                return;
            }
        }
        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
    } else {
        printf("Invalid input.\n");
    }

    getchar(); // To catch the Enter key after a failed attempt
    // You may return to main to retry, or loop again in main.c
}

