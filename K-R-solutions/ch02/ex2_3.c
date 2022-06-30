/*
 * Exercise 2-3. Write a function htoi(s), which
 * converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its
 * equivalent integer value. The allowable digits
 * are 0 through 9, a through f, and A through F.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint32_t htoi(const char s[]) {
    /*
     * Patterns:
     * 'a' = 97
     * 'A' = 65
     * 
     * 'a' to 10:   97  - 87
     * .
     * .
     * 'f' to 15:   102 - 87
     * 
     * 'A' to 10:   65  - 55
     * .
     * .
     * 'F' to 15:   70  - 55
     * 
     * Example:
     * 
     * 0xa1 = 1010 0001 --> 161 = 16 * 10 + 1  (16 means base)
     * 
     * Steps:
     * 
     * '0xa1' --> 10 1 --> 16 * 10 + 1 --> 161
    */

    uint32_t n = 0;

    /*
     * Note: there is no need to skip 0x or 0X
     * - '0' falls in line 54:
     *     n = 0*16 + ('0'-'0') = 0   no changes
     * - 'x' is never evaluated, since
     *     'x' > 'f' and 'x' > 'F'.
    */

    for (uint8_t i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'f') {
            n = n * 16 + (s[i] - 87);
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = n * 16 + (s[i] - 55);
        } else if (s[i] >= '0' && s[i] <= '9') {
            n = n * 16 + (s[i] - '0');
        }
    }

    return n;
}

int main() {
    printf("%x is equal to %x\n", 0x443cE, htoi("0x443cE"));
    assert(0x443cE == htoi("0x443cE"));
    return 0;
}