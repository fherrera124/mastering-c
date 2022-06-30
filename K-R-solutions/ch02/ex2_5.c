/*
 * Exercise 2-5. Write the function any(s1,s2),
 * which returns the first location in a string
 * s1 where any character from the string s2
 * occurs, or -1 if s1 contains no characters
 * from s2. (The standard library function
 * strpbrk does the same job but returns a
 * pointer to the location.)
 */

#include <assert.h>

int any(const char s1[], const char s2[]) {
    int i, j;

    for (i = 0; s1[i]; i++) {
        for (j = 0; s2[j]; j++) {
            if (s1[i] == s2[j])
                return i;
        }
    }
    return -1;
}

int main(void) {
    char *s = "0x4d43cEa";

    assert(any(s, "0") == 0);
    assert(any(s, "4") == 2);
    assert(any(s, "c") == 6);
    assert(any(s, "ra") == 8);
    assert(any(s, "r") == -1);

    return 0;
}