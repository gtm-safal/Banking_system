#include "utilities.h"

// Clear the input buffer
void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // Clear remaining input
}

// Remove newline characters from a string
void trimNewline(char *str)
{
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0'; // Remove newline
    }
}

// Capitalize the first letter of each word in a string
void capitalize(char *str)
{   
    int i =1;
    str[0] = toupper(str[0]);
    while (str[i]!='\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
    
}

// Convert a string to lowercase
void toLowerCase(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
}

// Validate if the contact number has exactly 10 digits
int isValidContact(long contact)
{
    int count = 0;
    while (contact != 0)
    {
        contact /= 10;
        count++;
    }
    return count == 10;
}

// To hide password using '*' character
void getAndHidePassword(char *password, int size)
{
    int i = 0;
    char ch;

#ifdef _WIN32
    while ((ch = _getch()) != '\r' && i < size - 1)
    { // '\r' is Enter key
        if (ch == '\b' && i > 0)
        { // Handle backspace
            i--;
            printf("\b \b");
        }
        else if (isprint(ch))
        { // Accept only printable characters
            password[i++] = ch;
            printf("*"); // Print '*' instead of actual input
        }
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    while ((ch = getchar()) != '\n' && i < size - 1)
    {
        if (ch == 127 && i > 0)
        { // Handle backspace (ASCII 127)
            i--;
            printf("\b \b");
        }
        else if (isprint(ch))
        { // Accept only printable characters
            password[i++] = ch;
            printf("*"); // Print '*' instead of actual input
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore terminal settings
#endif

    password[i] = '\0'; // Null-terminate password
    printf("\n");

    if (i >= size - 1)
    {
        printf("Warning: Password exceeds maximum length. Truncated.\n");
    }
}
