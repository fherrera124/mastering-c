#include <string.h>

int  binsearch(int x, int v[], int n);
void escape(char s[], char t[]);
void expand(char s1[], char s2[]);
void itoa(int n, char s[]);
void itob(int n, char s[], int b);


/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}