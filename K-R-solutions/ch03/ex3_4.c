#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include "utils.h"

void itoa(unsigned n, char s[]);

/*
Exercise 3-4. In a two's complement number representation, our version
of itoa does not handle the largest negative number, that is, the
value of n equal to -( 2^(wordsize-1) ). Explain why not. Modify it to
print that value correctly, regardless of the machine on which it runs.

Answer: since there is an extra negative number in ca2, passing it to
positive will incurr in overflow, that's because abs(INT_MIN) is 1
higher than INT_MAX.

Solution: casting n to unsigned in the function prototype solves our
problem since UINT_MAX is higher than abs(INT_MIN)
*/

/* itoa:  convert n to characters in s */
void itoa(unsigned n, char s[]) {
    int i, sign;

    i = 0;

    if ((sign = n) < 0)        /* record sign */
        n = -n;                /* make n positive */
    do {                       /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main(void) {
    char s[12];

    /* Some thoughts.

    UINT_MAX = 2^(32) -1 = 0xffffffff = 11111111 11111111 11111111 11111111
    INT_MAX  = 2^(31) -1 = 0x7fffffff = 01111111 11111111 11111111 11111111
    INT_MIN  = 2^(31)    = 0x80000000 = 10000000 00000000 00000000 00000000

    UINT_MAX represents all combinations available with 32 bits
    INT_MAX represents all positive signed numbers available
    INT_MIN represents all negative numbers available

    A natural way to obtain the largest negative number (INT_MIN) could be:

        INT_MIN = UINT_MAX - INT_MAX = 2^(31)

    but the practical procedure is to invert all the bits of INT_MAX:
        INT_MIN = ~INT_MAX
    */

    assert(-INT_MAX == ~INT_MAX + 1);  // the negation is calculated as two's complement
    assert(-(-INT_MAX) == INT_MAX);
    assert(-(-INT_MAX) == ~(-INT_MAX) + 1);
    assert(INT_MIN == UINT_MAX - INT_MAX);
    assert(INT_MIN == ~INT_MAX);

    // 2^(32) -1 = 11111111 11111111 11111111 11111111
    printf("largest unsigned:        %u (0x%x)\n", UINT_MAX, UINT_MAX);
    // 2^(31) -1  = 01111111 11111111 11111111 11111111
    printf("largest positive signed: %d (0x%x)\n", INT_MAX, INT_MAX);
    // 2^(31)  = 10000000 00000000 00000000 00000000
    printf("largest negative:        %d (0x%x)\n", INT_MIN, INT_MIN);

    itoa(INT_MIN, s);
    printf("Expected: %d. Result: %s\n", INT_MIN, s);

    return 0;
}