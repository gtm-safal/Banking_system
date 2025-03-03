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
    int i = 0;
    while (str[i] != '\0')
    {
        if (i == 0 || str[i - 1] == ' ')
        {
            str[i] = toupper(str[i]);
        }
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