#include <limits.h>
#include <stdio.h>
#include <string.h>

#define INT_ARRAY_SIZE __INT_WIDTH__ + 2

void reverse(char s[]);
void itob(unsigned n, char s[], int b);

/* reverse:  reverse string s in place */
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c    = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.
*/
void itob(unsigned n, char s[], int b) {
    int i, sign, rem;

    i = 0;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    do {
        rem    = n % b;
        s[i++] = rem + (rem > 9 ? '7' : '0');
    } while ((n /= b) > 0);
    if (sign < 0)
        s[i++] = '-';

    s[i] = 0;
    reverse(s);
}

int main() {
    char s[INT_ARRAY_SIZE];
    itob(-59, s, 16);
    printf("%s\n", s);

    itob(INT_MAX, s, 16);
    printf("%s\n", s);

    itob(INT_MIN, s, 16);
    printf("%s\n", s);

    itob(INT_MIN, s, 2);
    printf("%s\n", s);

    return 0;
}
