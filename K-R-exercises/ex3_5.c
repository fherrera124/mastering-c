#include <stdio.h>
#include "include/chapter3.h"

int main() {

    char s[12];

    itob(5,s,2);

    printf("%s\n", s);

    return 0;
}

/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.
*/
void itob(int n, char s[], char b) {

    short base, i;
    
    base = b - '0'; // convert to integer
    i = 0;
    do
    {
        s[i++] = n % base + '0';
    } while ((n /= base) > 0 );

}