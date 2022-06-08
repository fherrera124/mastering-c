#include <assert.h>
#include <limits.h>
#include <stdio.h>

#include "chapter3.h"

void itoa(int n, char s[]);

int main(void) {
    char s[12];

    // warmup

    unsigned a = UINT_MAX;  //  0xffffffff = 4294967295 = 2^(32) -1 = 11111111 11111111 11111111 11111111

    int b = INT_MAX;  // 0x7fffffff = 2147483647 = 2^(31) -1  =       01111111 11111111 11111111 11111111

    int c = -b;
    int d = ~b + 1;  // always a negative is calculated as two's complement
    assert(c == d);
    // although both c and d represent the negative of the largest unsigned number, that number is
    // NOT the largest negative number..
    // with two's complement we have one extra negative number, so:
    // b is the largest signed positive number, and ~b is the largest signed negative number.

    // the natural procedure to get the largest negative number is:

    // Largest unsigned: UINT_MAX          Largest positive: int INT_MAX

    // (UINT_MAX)  -  (INT_MAX)   --> 0x80000000  --> 10000000 00000000 00000000 00000000

    // on decimal:
    // (2^(32) -1) - (2^(31) -1)  --> 2^(31)      --> 2147483648

    // the practical procedure is to invert all the bits of INT_MAX
    // ~INT_MAX

    printf("largest unsigned: %u\n", a);
    printf("largest signed:   %d\n", b);
    printf("largest negative: %d\n", ~b);

    itoa(~INT_MAX, s);
    printf("Expected: %d. Result: %s\n", ~INT_MAX, s);

    return 0;
}

/*
Exercise 3-4. In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -( 2^(wordsize-1) ). Explain why not.
Modify it to print that value correctly, regardless of the machine on which it runs.
*/
/*Answer: since there is an extra negative number in ca2, passing it to positive will results in overflow,
 abs(INT_MIN) is 1 higher than INT_MAX*/
/* itoa:  convert n to characters in s */
void itoa(int n, char s[]) {
    int i, sign;

    i = 0;

    if (n == INT_MIN) {
        /*
        So we know n its the largest negative, and n = -n
        will incurr in overflow. Here simply store the less
        significant digit and decrease n,
        so that bellow n = -n; will work fine.
        */
        s[i++] = -(n % 10) + '0';
        n /= 10;
    }

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