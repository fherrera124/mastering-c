#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stddef.h>

#define NUMBER '0' /* signal that a number was found */
#define NAME   '1' /* signal that a string command was found */

int  getline(char *, int);
int  atoi(const char *);
void itoa(int, char *);
void reverse(char *);
int  strindex(char *, char *);

#endif /* FUNCTIONS_H */