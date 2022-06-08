#include <limits.h>
#include <stdio.h>

#include "include/chapter3.h"

#define ARRAY_SIZE __INT_WIDTH__ + 2

int main() {
    char s[ARRAY_SIZE];
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

/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.
*/
void itob(int n, char s[], int b) {
    int i, sign, rem;

    i = 0;

    /*
        if n == INT_MIN, "n = -n" will incurr in overflow,
        since abs(INT_MIN) is 1 higher than INT_MAX
    */
    if (n == INT_MIN) {
        rem    = -(n % b); /* make rem positive */
        s[i++] = (rem > 9 ? '7' : '0');
        n /= b;
    }
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