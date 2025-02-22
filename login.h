#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void clearBuffer();
void login(int input);
void createNewAccholder();
void adminProfile(char username[]);
void accholderProfile(char username[]);
void transferBalance(char senderUsername[]);
void deleteAccholderAccount();

#endif // LOGIN_H