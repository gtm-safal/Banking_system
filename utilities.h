#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
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

#endif // UTILITIES_H
