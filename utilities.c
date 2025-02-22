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