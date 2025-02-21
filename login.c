void login(int input)
{
    char username[20], pass[16], fileUsername[20], filePass[16], pseudo;
    system("clear");
    printf("\nEnter agent's username: ");
    scanf("%19s", username); // Prevents buffer overflow
    printf("Enter agent's password: ");
    scanf("%15s", pass);
    clearBuffer();

    FILE *fp;
    if (input == 1)
    {
        fp = fopen("adminCredential.csv", "r");
        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) // Read username, password
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0)
            {
                system("clear");
                printf("Successfully logged in.\nPress 'Enter' to continue.\n");
                pseudo = getchar();
                fclose(fp);
                return 0;
            }
        }

        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
        pseudo = getchar();
        main();
        return 1;
    }

    else if (input == 2)
    {
        fp = fopen("customerCredential.csv", "r");
        while (fscanf(fp, "%19[^,],%15s", fileUsername, filePass) != EOF) // Read username, password
        {
            if (strcmp(username, fileUsername) == 0 && strcmp(pass, filePass) == 0)
            {
                system("clear");
                printf("Successfully logged in.\nPress 'Enter' to continue.\n");
                pseudo = getchar();
                fclose(fp);
                return 0;
            }
        }

        printf("Username and password didn't match.\nPress 'Enter' to continue.\n");
        fclose(fp);
        pseudo = getchar();
        main();
        return 1;
    }
}

void clearBuffer()
{
    while (getchar() != '\n')
        ;
}