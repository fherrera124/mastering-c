/*
Exercise 4-7. Write a routine ungets(s) that will push back
an entire string onto the input. Should ungets know about
buf and bufp, or should it just use ungetch?

Answer: it's usually preferable for something like ungets()
to just build itself on top of ungetch(). This allows us to
change ungetch() and getch() in the future, perhaps to use
a linked list instead, without affecting ungets().

Note: I defined the function getstr, pretty similar to
getline(). getstr will try first fetch the characters
from the array buffer.
*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

#define MAXSTR 100 /* max size of string */

/* functions */
int  getch(void);
void ungetch(int);
int  getstr(char[], int);
void ungets(char[]);

void ungets(char s[]) { /* push string back onto the input */
    /* buffer is lifo, so pushing in reverse order */
    int i = strlen(s);
    while (i >= 0)
        ungetch(s[i--]);
}

/*
    getstr: try to get pushed-back characters from buffer into
    string. Fallback to standard input. Return length
*/
int getstr(char s[], int lim) {
    int c, i = 0;

    while (--lim > 0 && (c = getch()) != '\0' && c != '\n') {
        s[i++] = c;
    }
    s[i] = '\0';

    return i;
}

int main(void) {
    char s[MAXSTR], t[MAXSTR];

    printf("Awaiting for input:\n");
    getstr(s, MAXSTR); /* buffer empty, getting the string from terminal */
    printf("string s: %s\n", s);

    ungets(s); /* push the string onto the buffer */

    getstr(t, MAXSTR); /* construct the string from the content of the buffer */
    printf("string t: %s\n", t);

    assert(strcmp(s, t) == 0);

    printf("Awaiting for input:\n");
    getstr(s, MAXSTR); /* buffer should be empty at this point, getting the string from terminal */
    printf("string s: %s\n", s);

    return 0;
}
