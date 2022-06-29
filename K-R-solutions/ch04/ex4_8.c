/*
Exercise 4-8. Suppose that there will never be more than one
character of pushback. Modify getch and ungetch accordingly.
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

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
    char s[MAXSTR], t[MAXSTR] = {'a', 'b', 'c', '\0'};

    strcpy(s, t);

    printf("string s: %s\n", s);
    printf("string t: %s\n", t);

    assert(strcmp(s, t) == 0);

    printf("Waiting for character:\n");
    s[1] = getch();     /* buffer empty, getting character from terminal */

    ungetch(s[1]);      /* push the character onto the buffer */

    t[1] = getch();     /* buffer NOT empty, getting character from there */

    assert(strcmp(s, t) == 0);

    printf("string s: %s\n", s);
    printf("string t: %s\n", t);
}
