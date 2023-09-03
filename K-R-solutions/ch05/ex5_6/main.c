/*
 * Exercise 5-6. Rewrite appropriate programs
 * from earlier chapters and exercises with
 * pointers instead of array indexing. Good
 * possibilities include getline (Chapters 1
 * and 4), atoi, itoa, and their variants
 * (Chapters  2, 3, and 4), reverse (Chapter
 * 3), and strindex and getop (Chapter 4).
 */

#include <assert.h>
#include <stdio.h>

#include "functions.h"

#define MAXLINE 20

int main(void) {
    char s[MAXLINE];

    /* Test getline */
    printf("Test getline function\n");
    printf("Waiting for any input (max %d characters will be read): ", MAXLINE - 1);
    getline(s, MAXLINE);
    printf("\nYour input: %s", s);
    printf("\nRunning other tests...");
    /* Test atoi */
    assert(atoi("34") == 34);
    assert(atoi("  34") == 34);
    assert(atoi("34etg") == 34);
    assert(atoi("-34") == -34);
    /* Test itoa */
    itoa(34, s);
    assert(strcmp(s, "34") == 0);
    itoa(-934, s);
    assert(strcmp(s, "-934") == 0);
    itoa(0, s);
    assert(strcmp(s, "0") == 0);
    /* Test reverse */
    strcpy(s, "casa");
    reverse(s);
    assert(strcmp(s, "asac") == 0);
    strcpy(s, "U00");
    reverse(s);
    assert(strcmp(s, "00U") == 0);
    strcpy(s, "");
    reverse(s);
    assert(strcmp(s, "") == 0);
    strcpy(s, "7");
    reverse(s);
    assert(strcmp(s, "7") == 0);
    printf("\nAll tests passed.");
    /* Test strindex */

    /* Test getop */

    return 0;
}