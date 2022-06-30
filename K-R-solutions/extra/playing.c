/*
 * Intro:
*/


#include <stdint.h>
#include <stdio.h>

void static integers(void) {
    uint16_t _579 = 0x0243;  // 00000010 01000011 --> 512 + 67 = 579

    /* _579 in memory (low endian):
        00: 00000010
        01: 01000011
    */

    uint8_t *test = (uint8_t *)&_579;  // *test = 01000011 --> 67 (LSB of _579)

    printf("1) %d, \n", *test++);  // 67

    printf("2) %d, \n", *test--);  // *test == 00000010 --> 2  ( MSB of _579)

    _579 &= 0x0ff;  // 00000010 01000011 & 00000000 11111111 --> 00000000 01000011 --> 67
    printf("3) %d, \n", _579);

    printf("4) %d, \n", *test++);  // LSB of _579 --> 67, untouched as in 1)

    printf("5) %d, \n", *test);  // MSB of _579 --> changed: 0

    *test |= 2;  // 00000000 | 00000010 --> 00000010 --> 2

    printf("6) %d, \n", _579);  // now MSB back to original value --> 00000010 01000011 --> 579
}


int main(void) {

    integers();

    return 0;
}