/*
Exercise 4-12. Adapt the ideas of printd to
write a recursive version of itoa; that is,
convert an integer into a string by calling
a recursive routine.
*/

#include <stdio.h>

/*
itoa: convert n to characters in s.
Recursive version
*/
void itoa(char s[], int n) {
    void _itoarec(char[], int, int);
    int  i = 0;

    if (n < 0) {
        n      = -n;
        s[i++] = '-';
    }
    for (int j = n; j /= 10; i++)
        ;
    _itoarec(s, n, i);
    s[++i] = '\0';
}

void _itoarec(char s[], int n, int i) {
    if (n / 10) {
        _itoarec(s, n / 10, i - 1);
    }
    s[i] = n % 10 + '0';
}

int main(void) {
    char s[5];

    itoa(s, -145);
    printf("%s\n", s);

    itoa(s, 567);
    printf("%s\n", s);

    itoa(s, 0);
    printf("%s\n", s);

    return 0;
}