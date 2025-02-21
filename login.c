void agentLogin()
{
    char agentUsrname[20], agentPass[16], usrname[20], pass[16];
    system("clear");
    printf("\nEnter agent's username: ");
    scanf("%19s", agentUsrname);  // Prevents buffer overflow
    printf("\nEnter agent's password: ");
    scanf("%15s", agentPass);

    FILE *fp;
    fp = fopen("adminCredential.csv", "r");

    while (fscanf(fp, "%19[^,],%15s", usrname, pass) != EOF)  // Read username, password
    {
        if (strcmp(usrname, agentUsrname) == 0 && strcmp(pass, agentPass) == 0)
        {
            printf("Successfully logged in\n");
            fclose(fp);
            return;
        }
    }

    printf("Username and password didn't match\n");
    fclose(fp);
}

void customerLogin()
{
    system("clear");
    printf("1. Balance inquiry\n");
}
