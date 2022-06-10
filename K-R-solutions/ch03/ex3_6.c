#include <stdio.h>
#include <string.h>

#define MAX 1000

int main(void) {

    char s[MAX];

    itoa2(100,s,3);

    return 0;
}


/*
Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough.
*/
void itoa2(int n, char s[], int w) {

    itoa(n, s);

    printf("%d\n", strlen(s));


}