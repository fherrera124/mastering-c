#include "utils.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/* globals */
char buf[BUFSIZE]; /* buffer for ungetch */
int  bufp = 0;     /* next free position in buf */

/* reverse: reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* getline: get line into s, return length */
int getline(char s[], int lim) {
    int c, i = 0;

    while (--lim > 0 && (c = getchar()) != '\n' && c != EOF) {
        s[i++] = c;
    }
    s[i] = '\0';

    return i;
}

/* clear_spaces: clear both leading and ending space characters from s */
void clear_spaces(char s[]) {
    int i, j, k;

    for (i = 0; isspace(s[i]); i++)
        ;
    for (j = strlen(s) - 1; isspace(s[j]); j--)
        ;
    s[++j] = '\0';

    if (i > 0) {
        for (k = 0; i <= j; k++, i++)
            s[k] = s[i];
    }
}

/* getch: get a (possibly pushed-back) character */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}