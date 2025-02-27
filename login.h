#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "login.h"

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
int isUsernameUnique(char *username);
void changeUsernamePassword(char username[]);
int searchUsername(char *username);
void capitalize(char *str);
void strlwr(char *str);
void addBalance(); 
void withdrawBalance(); 

#endif // LOGIN_H