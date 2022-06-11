#include <ctype.h>
#include <stdio.h>



#define MAXLEN 10000

void expand(char s1[], char s2[]);
int  valid_shorthand(char s1[], int i);
int  get_str(char str[], int limit);

int main(void) {
    char str[MAXLEN];  // = "--hd-a0-4-";
    char expanded_str[MAXLEN];

    get_str(str, MAXLEN);

    expand(str, expanded_str);
    printf("%s\n", expanded_str);

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

    i = j = 0;

    do {
        if (valid_shorthand(s1, i)) {
            current = s1[i];
            last    = s1[i + 2];
            while (current <= last)
                s2[j++] = current++;
            i += 3;
        } else {
            s2[j++] = s1[i++];
        }
    } while (s1[i] != 0);
    s2[j] = 0;
}

int valid_shorthand(char c[], int i) {
    short cond;
    cond = isalnum(c[i]) && isalnum(c[i + 2]);
    if (cond)
        cond = c[i + 1] == '-';
    if (cond)
        cond = c[i] < c[i + 2];
    return cond;
}

int get_str(char str[], int limit) {
    int c, i = 0;

    while (i < limit - 1 && (c = getchar()) != '\n' && c != EOF) {
        str[i++] = c;
    }
    str[i] = '\0';

    return i;
}