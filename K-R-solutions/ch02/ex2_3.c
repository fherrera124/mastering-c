/*
 * Exercise 2-3. Write a function htoi(s), which
 * converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its
 * equivalent integer value. The allowable digits
 * are 0 through 9, a through f, and A through F.
 */

#include <assert.h>

int htoi(const char s[]) {
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
     * 0xa1 = 1010 0001 --> 161 = 16 * 10 + 1  (16 refers the base)
     *
     * Steps:
     *
     * '0xa1' --> 10 1 --> 16 * 10 + 1 --> 161
     */

    int i, n;

    /*
     * Note: there is no need to skip 0x or 0X
     * - '0' falls in line 53:
     *     n = 0*16 + ('0'-'0') = 0   no changes
     * - 'x' is never evaluated, since
     *     'x' > 'f' and 'x' > 'F'.
     */

    for (i = n = 0; s[i] != '\0'; i++) {
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
    assert(0x443cE == htoi("0x443cE"));
    return 0;
}