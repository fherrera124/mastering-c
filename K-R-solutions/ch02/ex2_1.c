/*
 * Exercise 2-1. Write a program to determine
 * the ranges of char, short, int, and long
 * variables, both signed and unsigned, by
 * printing appropriate values from standard
 * headers and by direct computation. Harder
 * if you compute them: determine the ranges
 * of the various floating-point types.
 */

#include <assert.h>
#include <float.h>
#include <limits.h>

/*
 * ALL1 macro returns all bits filled with
 * ones, number of bits depends on the type
 * X. Casting to unsigned ensures that when
 * it is right-shifted, vacated bits will be
 * filled with zeros, not sign bits.
 * */
#define ALL1(X)       ((unsigned X)(~0))
#define MAX_UNSIGN(X) (ALL1(X))
#define MAX_SIGN(X)   (ALL1(X) >> 1) /* max number on ca2 (MSB set to zero) */
#define MIN_SIGN(X)   (~MAX_SIGN(X)) /* min number on ca2 (all bits set to zero but MSB)*/

int main(void) {
    /* char tests */
    assert(CHAR_MIN == MIN_SIGN(char));
    assert(CHAR_MAX == MAX_SIGN(char));
    assert(UCHAR_MAX == MAX_UNSIGN(char));
    /* short tests */
    assert(SHRT_MIN == MIN_SIGN(short));
    assert(SHRT_MAX == MAX_SIGN(short));
    assert(USHRT_MAX == MAX_UNSIGN(short));
    /* int tests */
    assert(INT_MIN == MIN_SIGN(int));
    assert(INT_MAX == MAX_SIGN(int));
    assert(UINT_MAX == MAX_UNSIGN(int));
    /* long tests */
    assert(LONG_MIN == MIN_SIGN(long));
    assert(LONG_MAX == MAX_SIGN(long));
    assert(ULONG_MAX == MAX_UNSIGN(long));

    /* 
     * following the IEEE 754 standar, single-precision floating point
     * notation uses a 32-bit float with 1 bit for the sign, 8 bits
     * for the exponent, and 23 bits for the mantissa.
     *
     * The exponent is an 8-bit unsigned integer from 0 to 255.
     * 127 bias: A bias is added to the actual exponent in order to
     * get the stored exponent, so in biased form: an exponent value
     * of 127 represents the actual zero.
     * Exponents range from −126 to +127 because exponents of −127
     * (all 0s) and +128 (all 1s) are reserved for special numbers.
     *
     * So, the max float is:
     * 0 11111110 11111111111111111111111   --> 0x7F7FFFFF
     *
     * The first zero indicates that is positive
     *
     * Next 8 bits represents the (biased) exponent, so the real
     * (unbiased) exponent is obtained this way:
     * 
     * biased_exp - 127 bias = unbiased_exp
     *
     * Back in our example:
     * 
     *   11111110 -> 254 (E biased)
     *   254-127 --> real exponent: +127
     *
     * 127 is the max exponent, since 128 is reserved.
     *
     * The mantissa (last 23 bits) represents the decimal part,
     * with all ones we get the largest decimal number.
     *
     * The max negative float is obtained simply by setting the
     * MSB to 1 (sign) of the max float number:
     *
     *   1 11111110 11111111111111111111111 (0xFF7FFFFF)
     *
     * The minimum positive float:
     *
     *   0 00000001 00000000000000000000000 (0x800000)
     *
     * no decimal (aka mantissa), and exponent unbiased: 1 -127 = -126
     *
     * above I stated that -128 and +127 unbiased exponent are
     * reserved for special values. One of the specials value in which
     * -127 is used for is the ZERO value, defined in the standard
     *
     *   0 00000000 00000000000000000000000 (0x00000000)
     *   1 00000000 00000000000000000000000 (0x80000000)
     *
     * the sign bit can be either 0 or 1. Altough different numbers,
     * both represents zero.
     *
     * - double-precision floating point notation: same reasoning as
     * simmple precision but with 64-bit as double: 1 bit for the sign,
     * 11 bits for the exponent, and 53 bits for the mantissa (52
     * explicitly stored). Some examples:
     *
     *   DBL_MAX:     0x7FEFFFFFFFFFFFFF
     *   DBL_MIN:     0x10000000000000
     *   -(DBL_MAX):  0xFFEFFFFFFFFFFFFF
     *   ZERO:        0x0000000000000000
     *                0x8000000000000000
     *
     */

    union {
        long long l; /* valid for storing int unsigned too*/
        float     f;
        double    d;
    } n = {0};

    /* max float */
    n.l = 0x7F7FFFFF;
    assert(FLT_MAX == n.f);

    /* min float */
    n.l = 0x800000;
    assert(FLT_MIN == n.f);

    /* max neg float*/
    n.l = 0xFF7FFFFF;
    assert(-FLT_MAX == n.f);

    /* special value: zero */
    n.l = 0x00000000;
    assert(0.0 == n.f);
    n.l = 0x80000000; /* signed, also is interpreted as zero */
    assert(0.0 == n.f);

    /* max double */
    n.l = 0x7FEFFFFFFFFFFFFF;
    assert(DBL_MAX == n.d);

    /* min double */
    n.l = 0x10000000000000;
    assert(DBL_MIN == n.d);

    /* max neg double */
    n.l = 0xFFEFFFFFFFFFFFFF;
    assert(-DBL_MAX == n.d);

    /* special value: zero */
    n.l = 0x0000000000000000;
    assert(0.0 == n.d);
    n.l = 0x8000000000000000; /* signed, also is interpreted as zero */
    assert(0.0 == n.d);
}