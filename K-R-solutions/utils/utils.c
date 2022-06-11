#include <stdio.h>
#include <string.h>

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