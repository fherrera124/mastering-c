/*
 * Exercise 2-7. Write a function invert(x,p,n)
 * that returns x with the n bits that begin at
 * position p inverted (i.e., 1 changed into 0
 * and vice versa), leaving the others unchanged.
 */

#include <assert.h>

unsigned invert(unsigned x, int p, int n) {
    unsigned t;

    t = ~0 << p + 1;
    t ^= ~0 << p + 1 - n;
    x ^= t;

    return x;
}

int main(void) {
    assert(invert(0xEE, 5, 3) == 0xD6); /* x=11(101)110 : 11(010)110 */
    assert(invert(0xEE, 5, 0) == 0xEE); /* x=11101110   : equal to x */
    assert(invert(0xF, 0, 1) == 0xE);   /* x=0000111(1) : 0000111(0) */
    assert(invert(0x37, 3, 2) == 0x3B); /* x=0011(01)11 : 0011(10)11 */
    assert(invert(0x37, 7, 8) == 0xC8); /* x=(00110111) : (11001000) */

    return 0;
}