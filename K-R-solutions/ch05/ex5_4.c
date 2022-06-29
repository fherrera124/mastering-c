/*
 * Exercise 5-4. Write the function strend(s,t),
 * which returns 1 if the string t occurs at the
 * end of the string s, and zero otherwise.
 */

#include <stdio.h>

#include "utils.h"

#define MAX 100

/*
 * strend(s,t): returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise
 */
int strend(char *s, char *t) {
    int s_t, s_s;

    for (s_s = 0; *s; s++, s_s++)
        ;
    for (s_t = 0; *t; t++, s_t++)
        ;
    if (s_t > s_s) /* t cannot be greater than s */
        return 0;
    while (s_t-- > 0) {
        if (*--s != *--t)
            return 0;
    }
    return 1;
}

int main(void) {
    char s[MAX], t[MAX];

    printf("Waiting characters for s: ");
    getline(s, MAX);
    printf("\nWaiting characters for t: ");
    getline(t, MAX);

    printf("\nReturn value of strend(s,t): %d", strend(s, t));

    return 0;
}