/*
 * Exercise 5-2. Write getfloat, the floating-point
 * analog of getint. What type does getfloat
 * return as its function value?
 */

#include <ctype.h>
#include <stdio.h>

#include "utils.h"

#define SIGN(x)      ((x) == '-' || (x) == '+')
#define END(x)       ((x) == EOF || (x) == '\n')
#define CLEAR_BUFFER while ((getchar()) != '\n')

/* getfloat: get next float from input into *pn
 *  returns 0 if input it's an invalid number
 */
int getfloat(float *pn) {
    int   c, sign;
    float power;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && !SIGN(c) && c != '.') {
        ungetch(c); /* it's not a number */
        return 0;
    }
    sign = c == '-' ? -1 : 1;

    if (SIGN(c))
        c = getch();
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    if (END(c)) {
        *pn *= sign; /* a number */
    } else if (c == '.') {
        c = getch();
        for (power = 1.0; isdigit(c); c = getch()) {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10;
        }
        if (!END(c)) {
            ungetch(c); /* it's not a number */
            return 0;
        }
        *pn *= sign / power; /* a number */
    } else {
        ungetch(c); /* it's not a number */
        return 0;
    }

    return c;
}

int main(void) {
    char c;
    int  res;

    int   i = 0;
    float array[5];

    /*
     * some valid numbers are:
     *   -7, +0.3, -.56, +65, -89.54
     *
     * invalid numbers:
     *  - 7, fri, 78f, 0.., .0q, --ñ
     *
     */

    printf("Storing 5 valid float numbers into array.\n");

    printf("\nAwaiting for [%d] number: ", i + 1);
    while (i < 5 && (res = getfloat(&array[i])) != EOF) {
        if (res) {
            i++;
        } else {
            c = getch(); /* remove the offending character from ungetch buffer */
            printf("Try again, nonnumeric character found: \'%c\' (ascii: %d)\n", c, c);
            CLEAR_BUFFER; /* clear the internal getchar() buffer */
        }
        if (i < 5)
            printf("\nAwaiting for [%d] number: ", i + 1);
    }

    printf("\nFloat numbers stored in array:\n");
    for (int x = 0; x < i; x++)
        printf("[%f] ", array[x]);

    return 0;
}