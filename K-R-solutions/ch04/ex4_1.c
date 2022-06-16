/*
Exercise 4-1. Write the function strindex(s,t) which
returns the position of the rightmost occurrence of
t in s, or -1 if there is none.
*/

#include <stdio.h>

#include "utils.h"

#define MAXLEN 10000

int strindex(char[], char[]);

/* strindex: returns the position of the
rightmost occurrence of t in s, -1 if none.
*/
int strindex(char s[], char t[]) {
    int i, j, k, pos;

    pos = -1;

    for (i = 0; s[i] != 0; i++) {
        for (j = i, k = 0; t[k] != 0 && t[k] == s[j]; j++, k++)
            ;
        if (k > 0 && t[k] == 0)
            pos = i;
    }
    return pos;
}

int main() {
    char s[MAXLEN];
    char t[MAXLEN];

    printf("Awaiting for input:\n");
    getline(s, MAXLEN);
    printf("Awaiting for input:\n");
    getline(t, MAXLEN);

    printf("Pos: %d", strindex(s, t));
    return 0;
}