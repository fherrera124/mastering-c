/*
 * Exercise 3-5. Write the function itob(n,s,b) that
 * converts the integer n into a base b character
 * representation in the string s. In particular,
 * itob(n,s,16) formats s as a hexadecimal integer in s.
 */

#include <assert.h>
#include <string.h>

#include "utils.h"

#define INT_ARRAY_SIZE __INT_WIDTH__ + 2

void itob(unsigned, char[], int);

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

    itob(-0x3B, s, 16);
    assert(strcmp(s, "-3B") == 0);

    itob(0xFF13, s, 16);
    assert(strcmp(s, "FF13") == 0);

    itob(-0x110E, s, 16);
    assert(strcmp(s, "-110E") == 0);

    itob(0xA5, s, 2);
    assert(strcmp(s, "10100101") == 0);

    itob(0x12CC, s, 10);
    assert(strcmp(s, "4812") == 0);

    return 0;
}
