/*
 * Exercise 5-3. Write a pointer version of the
 * function strcat that we showed in Chapter 2:
 * strcat(s,t) copies the string t to the end
 * of s.
 */

#include <stdio.h>

#include "utils.h"

#define MAX 100

/* strcat2: concatenate t to end of s;
 * s must be big enough. Note: changed
 * the name to avoid conflict with strcat
 * from string.h (imported in utils.c)
 */
void strcat2(char *s, char *t) {
    for (; *s; s++)
        ;
    while (*s++ = *t++)
        ;
}

int main(void) {
    char s[MAX], t[MAX];

    printf("Awaiting string for s: ");
    getline(s, MAX);
    printf("\nAwaiting string for t: ");
    getline(t, MAX);

    strcat2(s, t);
    printf("\nstrcat(s,t): %s", s);

    return 0;
}