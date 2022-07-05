/*
 * Exercise 2-8. Write a function rightrot(x,n)
 * that returns the value of the integer x
 * rotated to the right by n positions.
 */

#include <assert.h>

unsigned rightrot(unsigned x, int n) {
    unsigned t, size;

    size = sizeof(x) * 8;   /* length in bits of x */
    t    = x >> n;          /* right shift, lossing n rightmost bits of x */
    t   |= x << size - n;   /* lost bits now on the left */

    return t;
}

int main(void) {
    /* Note: tests below are valid only for
     * machines with int size of 32 bits*/
    assert(rightrot(0x65, 3) == 0xa000000c);
    assert(rightrot(0xFFFF, 3) == 0xE0001FFF);
    assert(rightrot(0xFFFFFFFF, 3) == 0xFFFFFFFF);
    assert(rightrot(0xFF, 1) == 0x8000007F);

    return 0;
}