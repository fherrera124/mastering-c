#include "functions.h"

#include <stdio.h>

/* getline: get line into s, return length */
/* note: my version doesn't store new line */
int getline(char *s, int lim) {
    int c, i = 0;

    while (--lim > 0 && (c = getchar()) != '\n' && c != EOF) {
        *s++ = c;
        i++;
    }
    *s = '\0';

    return ++i;
}

/* atoi: converts s to integer */
int atoi(const char *s) {
    int n, sign;

    for (; *s == ' '; s++) /* skip white space */
        ;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '-' || *s == '+')
        s++;

    for (n = 0; *s >= '0' && *s <= '9'; s++)
        n = n * 10 + (*s - '0');

    return sign * n;
}

/* itoa: convert n to characters in s. */
/* NOTE: just for fun I use static variables and recursion. */
void itoa(int n, char *s) {
    static char len, *t;

    if (!len) { /* first call for converting n */
        if (n < 0) {
            n    = -n;
            *s++ = '-';
        } else if (n == 0)
            *s++ = '0';
        t = s; /* backup start address */
    }
    if (n) {
        len++;
        itoa(n / 10, s + 1);
        len--;
        *t++ = n % 10 + '0';
    } else {
        *s = '\0';
    }
}

/* reverse: reverse string s in place */
void reverse(char *s) {
    char c, *i;

    for (i = s; *i; i++)
        ;
    for (--i; s < i; s++, i--) {
        c  = *s;
        *s = *i;
        *i = c;
    }
}

/* strindex: returns the position of the
 * rightmost occurrence of t in s, -1 if none.
 */
int strindex(char *s, char *t) {
    char *i, *j;
    int   pos = -1;

    for (; *s != 0; s++) {
        for (i = s, j = t; *t != 0 && *t == *i; i++, j++)
            ;
        if (j > t && *t == 0)
            pos = i - s;
    }
}

/* strcmp:  return <0 if s<t, 0 if s==t, >0 if s>t */
/* Used for run tests. To avoid import string.h */
int strcmp(char *s, const char *t) {
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

/* strcpy: copy string ct to string s, including '\0'; return s. */
/* Used for run tests. To avoid import string.h */
char *strcpy(char *s, const char *ct) {
    char *p = s;

    while (*s++ = *ct++)
        ;
    return p;
}