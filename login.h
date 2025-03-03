#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function declarations
void clearBuffer();
void login(int input);
void createNewAccholder();
void adminProfile(char username[]);
void accholderProfile(char username[]);
void transferBalance(char senderUsername[]);
void deleteAccholderAccount();
void trimNewline(char *str);
void createAdminAccount();
void capitalize(char *str);
void strlwr(char *str);
void depositBalance();
void withdrawBalance();
void changeUsernamePassword(char[]);
void transferBalanceAdmin();

#endif // LOGIN_H