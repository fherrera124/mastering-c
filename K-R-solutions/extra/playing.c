/*
 * Some tests to learn and study.
 */

#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

void static endianness(void) {
    uint16_t _579;
    uint8_t *LSB, *MSB;

    _579 = 0x0243; /* 00000010 01000011 --> (2 << 8) + 67 = 512 + 67 = 579 */
    assert(_579 == 579);

    /*  MEMORY (little endian):
     *  addr    : 01000011   (67)
     *  addr+1  : 00000010   (2)
     */

    LSB = (uint8_t *)&_579; /* LSB of _579: 01000011 (67) */
    MSB = LSB + 1;          /* MSB of _579: 00000010 (2) */
    assert(*LSB == 67);
    assert(*MSB == 2);

    /* clear the MSB of _579 */
    _579 &= 0x0ff;        /* 00000010 01000011 & 00000000 11111111 = 00000000 01000011 (67) */
    assert(*MSB == 0);    /* MSB cleared */
    assert(*LSB == 67);   /* LSB untouched */
    assert(_579 == *LSB); /* now all active bits of _579 are located on his LSB*/

    /* restore the MSB of _579 */
    _579 |= 2 << 8;      /* 00000000 01000011 | 00000010 00000000 = 00000010 01000011 (579) */
    assert(*MSB == 2);   /* MSB restored */
    assert(*LSB == 67);  /* LSB untouched */
    assert(_579 == 579); /* _579 back to original value */
}

void static integers(void) {
    /* Some analysis:
     *
     * With unsigned integers:
     * UINT_MAX = 2^(32) -1 = 0xffffffff = 11111111 11111111 11111111 11111111
     * 
     * With signed integers:
     * INT_MAX  = 2^(31) -1 = 0x7fffffff = 01111111 11111111 11111111 11111111
     * INT_MIN  = 2^(31)    = 0x80000000 = 10000000 00000000 00000000 00000000
     * 
     * *INT_MIN represents the largest negative number.
     * 
     * The natural way to obtain the largest negative number (INT_MIN) is:
     * 
     * INT_MIN = UINT_MAX - INT_MAX = 2^(31)
     * 
     * but the practical procedure is to invert all the bits of INT_MAX:
     * 
     * INT_MIN = - (~INT_MAX)
     * 
     * thats the largest negative number.
     * 
     * Attention: INT_MAX inverted, its not INT_MAX negated. That applies
     * for all the signed numbers with ca2.
     * As an example, +5 negated is -5, and +5 inverted?:
     * 
     * With 4 bits:
     * 
     * +5 = 0101
     * ~5 = 1010
     * 
     * ~5 its a negative number in ca2, because msb is 1, but ITS NOT -5.
     * 
     * ~5 = 1010 = - ~(~5) +1 = - 6
     * 
     * 
     * in ca2, ~5 is -6
     * 
     * 
     * 
     * so the negation of any number, is all bits inverted plus 1,
     * its valid from positive to negative, and negative to positive.
     * 
     * +6 (0110) to -6 (1001+1=1010)
     * -6 (1010) to +6 (0101+1=0110)
     * 
     * so its true that there are one number extra as negative
     * 
     * thats because the representation of zero.
     * all positive numbers have 0-bit in MSB. The negative numbers
     * have the mSB set to 1. And the representation
     * of the zero is all the bits set to 0, taking one representation
     * of the positive numbers. thats why there are an extra negative number.
     * 
     * 
    */

    assert(-INT_MAX == ~INT_MAX + 1); /* the negation is calculated as two's complement */
    assert(-(-INT_MAX) == INT_MAX);
    assert(-(-INT_MAX) == ~(-INT_MAX) + 1);
    assert(INT_MIN == UINT_MAX - INT_MAX);
    assert(INT_MIN == ~INT_MAX);

    // 2^(32) -1 = 11111111 11111111 11111111 11111111
    printf("largest unsigned:\t%u (0x%x)\n", UINT_MAX, UINT_MAX);
    // 2^(31) -1  = 01111111 11111111 11111111 11111111
    printf("largest positive signed: %d (0x%x)\n", INT_MAX, INT_MAX);
    // 2^(31)  = 10000000 00000000 00000000 00000000
    printf("largest negative:\t%d (0x%x)\n", INT_MIN, INT_MIN);
}

int main(void) {
    endianness();
    integers();

    return 0;
}