
/*
 * Exercise 2-9. In a two's complement number
 * system, x &= (x-1) deletes the rightmost 1-bit
 * in x. Explain why. Use this observation to
 * write a faster version of bitcount.
 *
 * ANSWER:
 *
 * It has to do with the way binary subtraction works in two's complement
 * number system, which is similar to base 10 subtraction.
 *
 * The bits are subtracted from each other starting from the least to the most
 * significant bit:
 *
 * 		0xFF - 0x01 = 0xFE
 *
 * 		Or
 *
 * 		1111 1111 - 0000 0001 = 1111 1110
 *
 * However, we cannot subtract a higher binary number from a lesser one, i.e.
 * subtracting 1 from 0. In this case, we "borrow" 1 from the next available
 * 1-bit to left (from the rightmost 1-bit). We then add 2 or 10b (base^n) to
 * the binary number we were trying to subtract from. This has the effect of
 * turning off the next available 1-bit and turning on any 0-bits after it. In
 * other words, all the bits starting with the rightmost 1-bit will be
 * inverted:
 *
 * 		0xF8 - 0x01 =  0xF7
 *
 * 		or
 *
 * 		1111 1000 - 0000 0001 = 11111  0111
 *
 * Notice the 4 least significant bits are inverted.
 *
 * The result of the subtraction, then, produces a mask that when ANDed with
 * the original value x will turn off the rightmost 1-bit, leaving the other
 * bits unchanged.
 *
 * Given this observation, we can use x &= (x - 1) in each execution of the
 * loop for turning off the current rightmost 1-bit, and when there are no
 * 1-bits left, just return the number of times the loop was executed. This
 * has the advantage that we effectively turn off an 1-bit in each loop, so
 * for example for 100000100000001, the loop is evaluated and executed 3
 * times, the same number of 1-bits. In the previous version of bitcount,
 * the loop would run 15 times for this example, right-shifting one position
 * in each execution of the loop to asks if current LSB its either 0 or 1,
 * incrementing the counter if 1. Also, AND operation is faster than shifting.
 */

#include <assert.h>
#include <stdio.h>

/* bitcount: count 1 bits in x */
int bitcount(unsigned x) {
    int b;
    for (b = 0; x; b++)
        x &= (x - 1); /* the current rightmost 1-bit is turned off */
    return b;
}

int main(void) {
    assert(bitcount(0xdc) == 5);
    assert(bitcount(0xD) == 3);
    assert(bitcount(0x15) == 3);  // 10101

    return 0;
}