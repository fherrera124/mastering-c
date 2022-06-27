/*
 * Exercise 5-5. Write versions of the library
 * functions strncpy, strncat, and strncmp, which
 * operate on at most the first n characters of
 * their argument strings. For example, strncpy(s,t,n)
 * copies at most n characters of t to s. Full
 * descriptions are in Appendix B.
 */

#include <assert.h>
#include <stdio.h>

char *strncpy(char *, const char *, int);
char *strncat(char *, const char *, int);
int   strncmp(char *, const char *, int);

int main(void) {
    /* strncpy tests */

    char s[20] = {'.', '.', '.', 'Y', 'X', '\0'};

    printf("%s\n", strncpy(s, "pzJ", 2)); /* prints 'pz.YX' */
    assert(s[0] == 'p');
    assert(s[1] == 'z');
    assert(s[2] == '.'); /* unchanged */
    assert(s[3] == 'Y'); /* unchanged */
    assert(s[4] == 'X'); /* unchanged */

    printf("%s\n", strncpy(s, "pzJ", 3)); /* prints 'pzJYX' */
    assert(s[0] == 'p');
    assert(s[1] == 'z');
    assert(s[2] == 'J');
    assert(s[3] == 'Y'); /* unchanged */
    assert(s[4] == 'X'); /* unchanged */

    printf("%s\n", strncpy(s, "pzJ", 5)); /* prints 'pzJ' */
    assert(s[0] == 'p');
    assert(s[1] == 'z');
    assert(s[2] == 'J');
    assert(s[3] == '\0'); /* pad with '\0' */
    assert(s[4] == '\0'); /* pad with '\0' */

    /* strncat tests */

    char t[10] = {'.', 'X', '\0', 'u', 'e', 'p', '3', 'q'};

    printf("%s\n", t);                     /* prints '.X' */
    printf("%s\n", strncat(t, "wolf", 3)); /* prints '.Xwol' */
    assert(t[2] == 'w');                   /* '\0' replaced with 'w' */
    assert(t[5] == '\0');                  /* 'p' replaced with '\0' */
    printf("%s\n", strncat(t, "v", 3000)); /* prints '.Xwolv' */
    assert(t[5] == 'v');                   /* '\0' replaced with 'v' */
    assert(t[6] == '\0');                  /* '3' replaced with '\0' */
    assert(t[7] == 'q');                   /* unchanged */

    /* strncmp tests */

    assert(strncmp("abTa", "abuA", 2) == 0);
    assert(strncmp("a4cd", "a7cd", 4) == -3);
    assert(strncmp("abc4", "abc1", 4) == 3);
    assert(strncmp("at", "at", 400) == 0);

    return 0;
}

/*
 * strncpy: copy at most n characters of string t
 * to s; return s. Pad with '\0''s if t has fewer
 * than n characters. Return s.
 */
char *strncpy(char *s, const char *t, int n) {
    char *p = s;

    for (; n > 0 && (*s++ = *t++); n--)
        ;
    while (n--)
        *s++ = '\0';
    return p;
}

/*
 * strncat: concatenate at most n characters of
 * string t to string s, terminate s with '\0';
 * return s.
 */
char *strncat(char *s, const char *t, int n) {
    char *p = s;

    for (; *s; s++)
        ;
    for (; n > 0 && (*s++ = *t++); n--)
        ;
    if (n == 0)
        *s = '\0';
    return p;
}

/*
 * strncmp: compare at most n characters of
 * string s to string t, return <0 if s<t,
 * 0 if s==t, or >0 if s>t.
 */
int strncmp(char *s, const char *t, int n) {
    for (; n > 0; s++, t++, n--)
        if (*s != *t)
            return (*s - *t);
    return 0;
}
