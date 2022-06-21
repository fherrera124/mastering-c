/*
 * Exercise 5-1. As written, getint treats a +
 * or - not followed by a digit as a valid
 * representation of zero. Fix it to push such
 * a character back on the input.
 */

#include <ctype.h>
#include <stdio.h>

#include "utils.h"

/* getint: get next integer from input into *pn */
int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        /* solution to exercise */
        if (!isdigit(c)) { /* + or - not followed by a digit */
            ungetch(c);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main(void) {
    int  n;
    char c;

    getint(&n);

    printf("%d\n", n);
    /* debug */
    c = getch(); /* get a (possibly pushed-back) character */
    printf("%c\n", c);

    return 0;
}