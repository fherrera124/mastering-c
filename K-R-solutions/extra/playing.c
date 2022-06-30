/*
 * Some tests to learn and study.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

void static endianness(void) {
    uint16_t _579;
    uint8_t *LSB, *MSB;

    _579 = 0x0243; /* 00000010 01000011 --> 512 + 67 = 579 */
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
    *MSB |= 2;           /* 00000000 | 00000010 = 00000010 (2) */
                         /* _579 |= (2<<8) should do the work too*/
    assert(_579 == 579); /* _579 back to original value */
}

int main(void) {
    endianness();

    return 0;
}