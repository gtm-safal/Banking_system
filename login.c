#include "utilities.h"

// Function to login Portal
void login(int input)
{
    char username[21], pass[17];
    Credential credential;
    system(CLEAR_SCREEN);

    printf("\nEnter username: ");
    scanf("%20s", username);
    trimNewline(username); // Remove newline
    toLowerCase(username); // Convert to lowercase

    clearBuffer(); 
    printf("Enter password: ");
    getAndHidePassword(pass, sizeof(pass)); // Use getAndHidePassword to read the password

    FILE *fp;
    if (input == 1)
    { // Admin login
        fp = fopen("adminCredential.dat", "rb");

        while (fread(&credential, sizeof(Credential), 1, fp))
        {
            if (strcmp(username, credential.username) == 0 && strcmp(pass, credential.password) == 0)
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
        fp = fopen("accholderCredential.dat", "rb");

        while (fread(&credential, sizeof(Credential), 1, fp))
        {
            if (strcmp(username, credential.username) == 0 && strcmp(pass, credential.password) == 0)
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


