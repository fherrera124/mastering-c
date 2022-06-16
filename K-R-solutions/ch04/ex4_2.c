/*
Exercise 4-2. Extend atof to handle scientific
notation of the form 123.45e-6 where a
floating-point number may be followed by e or
E and an optionally signed exponent.
*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "utils.h"

#define MAXLEN 10

float atof(char[]);

/* atof: convert string to float */
float atof(char s[]) {
    int   i, sign, expsign;
    float n, power;

    for (i = 0; isspace(s[i]); i++) /* skip whites*/
        ;
    sign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    for (n = 0.0; isdigit(s[i]); i++)
        n = 10.0 * n + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        n = 10.0 * n + (s[i] - '0');
        power *= 10;
    }
    if (tolower(s[i]) != 'e') /* no exponent */
        return sign * n / power;
    i++;
    expsign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+')
        i++;
    if (isdigit(s[i])) { /* one digit is enough */
        short e = (s[i] - '0');
        while (e-- > 0)
            expsign > 0 ? (power /= 10) : (power *= 10);
    }
    return sign * n / power;
}

int main(void) {
    char s[MAXLEN];

    printf("atof of 123.45:     %f\n", atof("123.45"));
    printf("atof of 123.45e-6:  %f\n", atof("123.45e-6"));
    printf("atof of 123.45e+6:  %f\n", atof("123.45e+6"));
    printf("atof of -123.45E+6: %f\n", atof("-123.45E+6"));

    printf("Awaiting for input:\n");
    getline(s, MAXLEN);

    printf("atof of %s: %f\n", s, atof(s));
    return 0;
}