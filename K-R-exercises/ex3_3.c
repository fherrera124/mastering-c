#include <stdio.h>
#include "include/chapter3.h"

int  main(void) {

    char s1[] = "--hd-a0-4-";
    char s2[100];

    expand(s1, s2);
    printf("%s\n", s2);

    return 0;
}

/*
Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case
and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
leading or trailing - is taken literally.
*/
void expand(char s1[], char s2[]) {
    int i, j, current, last;
    int valid_shorthand(char s1[], int i);

    i = j = 0;

    do {
        if (valid_shorthand(s1, i)) {
            current = s1[i];
            last    = s1[i + 2];
            while (current <= last)
                s2[j++] = current++;
            i += 3;
        } else {
            i++;
        }
    } while (s1[i] != 0);
    s2[j] = 0;
}

int valid_shorthand(char c[], int i) {
    short cond;
    cond = c[i] != 0 && c[i + 1] == '-';
    cond += c[i] < c[i + 2];
    return cond;
}