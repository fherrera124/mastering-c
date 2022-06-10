#include <stdio.h>
#include <string.h>

#define MAX 1000

void itoa(int n, char s[], int w);

int main(void) {
    char s[MAX];

    itoa(100, s, 3);

    return 0;
}

/*
Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The third
argument is a minimum field width; the converted number must be padded with blanks on the
left if necessary to make it wide enough.
*/
void itoa(int n, char s[], int w) {
    printf("%d\n", strlen(s));
}