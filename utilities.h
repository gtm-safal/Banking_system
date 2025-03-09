#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
    #include <stdio.h>
#else
    #define CLEAR_SCREEN "clear"
    #include <termio.h>
    #include <unistd.h>
#endif

// Function declarations
void clearBuffer();
void trimNewline(char *str);
void capitalize(char *str);
void toLowerCase(char *str);
int isValidContact(long contact);
void login(int input);
void createNewAccholder();
void adminProfile(char username[]);
void accholderProfile(char username[]);
void transferBalance(char senderUsername[]);
void deleteAccholderAccount();
void createAdminAccount();
void depositBalance();
void withdrawBalance();
void changeUsernamePassword(char[]);
void transferBalanceAdmin();
void initialize_files();
void getAndHidePassword(char *password, int size);

#endif // UTILITIES_H
