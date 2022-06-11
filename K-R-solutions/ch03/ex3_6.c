#include <stdio.h>
#include <string.h>

#include "utils.h"

#define MAX 1000

void itoa(int n, char s[], int w);

int main(void) {
    char s[MAX];

    itoa(100, s, 4);
    printf("%s\n", s);
    itoa(-100, s, 4);
    printf("%s\n", s);
    itoa(-100, s, 3);
    printf("%s\n", s);
    itoa(-100, s, 18);
    printf("%s\n", s);

    return 0;
}

/*
Exercise 3-6. Write a version of itoa that accepts three
arguments instead of two. The third argument is a minimum
field width; the converted number must be padded with
blanks on the left if necessary to make it wide enough.
*/

/* itoa:  convert n to characters in s */
void itoa(int n, char s[], int w) {
    int i, sign, count;

    i = count = 0;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */

    do {                       /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
        count++;               /* count digits*/
    } while ((n /= 10) > 0);   /* delete it */

    if (sign < 0) {
        s[i++] = '-';
        count++; /*count the minus*/
    }
    while (w-- > count)
        s[i++] = '*';

    s[i] = '\0';
    reverse(s);
}
