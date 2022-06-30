/*
 * Exercise 2-4. Write an alternative version of
 * squeeze(s1,s2) that deletes each character in
 * s1 that matches any character in the string s2.
 */

#include <assert.h>
#include <string.h>

void squeeze(char s1[], const char s2[]) {
    int i, j, k, match;

    for (i = j = 0; s1[i]; i++) {
        for (match = k = 0; !match && s2[k]; k++)
            match = s1[i] == s2[k];
        if (!match)
            s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main(void) {
    char t[20];

    strcpy(t,"aBcDe123");
    squeeze(t, "fff");
    assert(strcmp(t, "aBcDe123") == 0);

    strcpy(t,"aBcDe123");
    squeeze(t, "BB321");
    assert(strcmp(t, "acDe") == 0);

    strcpy(t,"aduo90");
    squeeze(t, "aduo90");
    assert(strcmp(t, "") == 0);

    return 0;
}