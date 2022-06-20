/*
Exercise 4-14. Define a macro swap(t,x,y)
that interchanges two arguments of type t.
(Block structure will help.)
*/

#include <stdio.h>

#define swap(t, x, y)  \
    {                  \
        t temp = x;    \
        x      = y;    \
        y      = temp; \
    }

int main(void) {
    char  a, b;
    float c, d;

    a = 't';
    b = '8';

    swap(char, a, b);
    printf("a: %c, b: %c\n", a, b);

    c = 89.4;
    d = -45;
    swap(float, c, d);
    printf("c: %g, d: %g\n", c, d);

    return 0;
}