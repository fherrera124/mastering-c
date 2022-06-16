/*
Exercise 4-9. Our getch and ungetch do not handle a
pushed-back EOF correctly. Decide what their properties ought
to be if an EOF is pushed back, then implement your design.

Answer: when an EOF character is encountered, it wont be stored
in the buffer. The EOF character is an integer type. This
problem can be solved by declaring buf to be of integer type.
*/

#include <stdio.h>

#define MAXSTR   100 /* max size of string */
#define BUFEMPTY '\0'

/* functions */
int  getch(void);
void ungetch(int);

/* globals */
int buf = BUFEMPTY; /* buffer for ungetch */

int getch(void) { /* get a (possibly pushed-back) character */
    int c;
    if (buf == BUFEMPTY)
        c = getchar();
    else {
        c   = buf;
        buf = BUFEMPTY;
    }
    return c;
}

void ungetch(int c) { /* push character back on input */
    buf = c;
}

int main(void) {
    int c;

    c = '*';

    ungetch(c);

    while ((c = getch()) != EOF)
        putchar(c);

    return 0;
}
