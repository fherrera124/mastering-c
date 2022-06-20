/*
Exercise 4-13. Write a recursive version of
the function reverse(s), which reverses the
string s in place.
*/

#include <stdio.h>
#include <string.h>

/*
reverse: reverse string s in place.
Recursive version.
Note: this version uses static variables.
Pay attention to i, and why resetted twice.

Not the most efficient version, since starts
recursion for each character, but for the
same reason I like it, since its an
exercise of recursion right? There are
others version, that mimics in some way
the version with loop.
*/
void reverse(char s[]) {
    static int i, len;
    if (!len)
        len = strlen(s);
    if (s[i]) {
        int c = s[i++];  // backup character
        reverse(s);
        s[i++] = c;
        if (i == len)
            len = i = 0;  // reset static vars for next string
    } else {
        i = 0;  // no more recursion, start writing in array
    }
}

int main(void) {
    char s[] = {'a', 'b', 'c', '7', '\0'};
    char t[] = {'z', 'L', '9', '\0'};

    printf("%s\n", s);
    reverse(s);
    printf("%s\n", s);
    printf("%s\n", t);
    reverse(t);
    printf("%s\n", t);

    return 0;
}