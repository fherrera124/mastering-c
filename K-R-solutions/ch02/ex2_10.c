/*
 * Exercise 2-10. Rewrite the function lower,
 * which converts upper case letters to lower
 * case, with a conditional expression instead
 * of if-else.
 */

#include <assert.h>
#include <stdio.h>

/* lower: convert c to lower case; ASCII only */
int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main() {
    assert(lower('r') == 'r');
    assert(lower('R') == 'r');
    assert(lower('2') == '2');
    assert(lower(' ') == ' ');
    assert(lower('H') == 'h');
    return 0;
}