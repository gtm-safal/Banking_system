#include "login.h"

// Clear the input buffer
void clearBuffer() {
    while (getchar() != '\n'); // Clear remaining input
}

// Remove newline characters from a string
void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0'; // Remove newline
    }
}

// Function to search for a username in accholderCredential.csv
int searchUsername(char *username)
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
            return 1; // Username found
        }
    }
    fclose(fp);
    return 0; // Username not found
}

// Function to check if a username is unique
int isUsernameUnique(char *username)
{
    return !searchUsername(username);
}


void capitalize(char *str)
{
    str[0] = toupper(str[0]);
}

void strlwr( char *str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
}