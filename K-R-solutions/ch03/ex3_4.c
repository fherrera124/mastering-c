/*
 * Exercise 3-4. In a two's complement number representation,
 * our version of itoa does not handle the largest negative
 * number, that is, the value of n equal to -(2^(wordsize-1)).
 * Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 *
 * Answer: since there is an extra negative number in ca2,
 * passing it to positive will incurr in overflow, that's
 * because abs(INT_MIN) is 1 higher than INT_MAX.
 *
 * Solution: casting n to unsigned in the function prototype
 * solves our problem since UINT_MAX is higher than abs(INT_MIN)
 */

#include <limits.h>
#include <stdio.h>

#include "utils.h"

void itoa(unsigned, char[]);

/* itoa:  convert n to characters in s */
void itoa(unsigned n, char s[]) {
    int i, sign;

    i = 0;

    if ((sign = n) < 0)        /* record sign */
        n = -n;                /* in the old version n overflowed when its value was INT_MAX */
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

    itoa(INT_MIN, s);
    printf("Expected: %d. Result: %s\n", INT_MIN, s);

    return 0;
}