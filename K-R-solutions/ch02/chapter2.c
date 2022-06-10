#include <stdint.h>
#include <stdio.h>

uint32_t htoi(const char s[]);
void     squeeze(char s1[], const char s2[]);
int      any(const char s1[], const char s2[]);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int      bitcount(unsigned x);
int      lower(int c);

void static playing(void) {
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

/*
Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F.
*/
uint32_t htoi(const char s[]) {
    /*
     Notes:
         'a' = 97
         'A' = 65

         Minusculas:

         convertir 'a' a 10:
             97 - 87 = 10
         convertir 'b' a 11:
             98 - 87 = 11
         ... restar por 87.

         Mayusculas:

         convertir 'A' a 10:
             65 - 55 = 10
         convertir 'B' a 11:
             66 - 55 = 11
         ... restar por 55.


         Un ejemplo sería:

         0xa1 = 1010 0001 --> 161 = 16 * 10 + 1  (16 es la base)

         Pasos:

         '0xa1' --> 10 1 --> 16 * 10 + 1 --> 161
    */

    uint32_t n = 0;

    /*
    Note: there is no need to skip 0x or 0X

    First, when '0' is evaluated:

    n = 0 --> n = 0*16 + ('0'-'0') = 0   no changes

    Second, 'x' is never evaluated, since 'x' > 'f' and 'x' > 'F'.

    */

    for (uint8_t i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'f') {
            n = n * 16 + (s[i] - 87);
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = n * 16 + (s[i] - 55);
        } else if (s[i] >= '0' && s[i] <= '9') {
            n = n * 16 + (s[i] - '0');  // first 0 falls here when n == 0, no harm
        }
    }

    return n;
}

/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2.
*/
void squeeze(char s1[], const char s2[]) {
    int i, j, k, match;

    for (i = j = 0; s1[i] != '\0'; i++) {
        for (match = k = 0; match != 1 && s2[k] != '\0'; k++) {
            match = (s1[i] == s2[k]);
        }
        if (!match)
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

/*
Exercise 2-5. Write the function any(s1,s2), which returns the first location in a string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.
(The standard library function strpbrk does the same job but returns a pointer to the
location.)
*/
int any(const char s1[], const char s2[]) {
    int i, j;

    for (i = 0; s1[i] != '\0'; i++) {
        for (j = 0; s2[j] != '\0'; j++) {
            if (s1[i] == s2[j])
                return i;
        }
    }
    return -1;
}

/*
Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/
unsigned setbits(unsigned x, int p, int n, unsigned y) {
    /*

        Example with: p=3  n= 2   x=110011    y=1001110

        x=110011 --> 11(00)11 //bits a modificar

        y=1001110 --> 10011(10) //bits a insertar en x

        x= 11(10)11  // Expected Result

        (~0 << n) ----------------------------> 1111100
        ~(~0 << n) ---------------------------> 0000011
        y & ~(~0 << n)  ----------------------> 0000010
        (y & ~(~0 << n)) << p+1-n ------------> 0001000
        x | ( (y & ~(~0 << n)) << (p+1-n) ) --> 111011 Final Result

        */

    return x | ((y & ~(~0 << n)) << (p + 1 - n));
}

/*
    Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
    position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/
unsigned invert(unsigned x, int p, int n) {
    /*

    p=5 n=3   x=11111110

    11111110 ->   11(000)110    Resultado esperado

    steps:

    ~0 << (p+1-n)  --> 00000111

    ~0 << p+1  -->     11000000

    ( ~0 << (p+1-n) ) ^(~0 << p+1) -->   00000111  ^11000000 -->  00111000

    x ^ (  ( ~0 << (p+1-n) ) ^(~0 << p+1)   ) --> 11111110 ^00111000  -->11000110    Final result

    */

    return x ^ ((~0 << (p + 1 - n)) ^ (~0 << (p + 1)));
}

/*
    Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x rotated
    to the right by n positions.
    */
unsigned rightrot(unsigned x, int n) {
    unsigned a, b, bits_covered;

    /*
    x= 1100101 (1+4+32+64 101)  n=4

    x >> 4  -->   0000110 (a)

    x << (32-4)  -->   0101000 (b)

    a | b   -->   0101110    2 4 8 32 46


    */

    a = x >> n;

    bits_covered = (sizeof(x) * 8) - n;  // number of bits not lost on the above shift

    b = x << bits_covered;

    // la rotacion la hace con los (sizeof(x) * 8) bits

    return a | b;
}

/* bitcount:  count 1 bits in x */
/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x. Explain why. Use this observation to write a faster version of bitcount.
*/
int bitcount(unsigned x) {
    int b;
    for (b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}

/*
Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case,
with a conditional expression instead of if-else.
*/
/* lower:  convert c to lower case; ASCII only */
int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main() {
    printf("%d is equal to %d\n", 0x443cE, htoi("0x443cE"));

    char t[] = "aduo90";

    printf("t[] antes: %s\n", t);
    squeeze(t, "0x4d43cEa");
    printf("t[] despues: %s\n", t);

    printf("0x4d43cEa   0 pos: %d\n", any("0x4d43cEa", "0"));
    printf("0x4d43cEa   4 pos: %d\n", any("0x4d43cEa", "4"));
    printf("0x4d43cEa   c pos: %d\n", any("0x4d43cEa", "c"));
    printf("0x4d43cEa   r pos: %d\n", any("0x4d43cEa", "r"));
    printf("0x4d43cEa   ra pos: %d\n", any("0x4d43cEa", "ra"));

    // Example with: p=3  n= 2   x=110011    y=1001110
    //  Expected Result: 111011  (59)

    printf("setbits() example with: p=3  n= 2   x=51 (110011)    y=78 (1001110)\n");
    printf("Expected Result: 59 (111011)\n");
    printf("Result: %d\n", setbits(51, 3, 2, 78));

    printf("invert() example with: p=5  n= 3   x=254 (11111110)\n");
    printf("Expected Result: 198 (11000110)\n");
    printf("Result: %d\n", invert(254, 5, 3));

    printf("rightrot() example with: x=101 (1100101)  n= 4 \n");
    printf("Expected Result: 46 (0101110)\n");
    printf("Result: %d\n", rightrot(101, 4));

    printf("bitcount() example with: x=218 (11011010) \n");
    printf("Expected Result: 5\n");
    printf("Result: %d\n", bitcount(218));

    return 0;
}
