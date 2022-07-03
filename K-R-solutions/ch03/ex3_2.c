
/*
 * Exercise 3-2. Write a function escape(s,t) that
 * converts characters like newline and tab into
 * visible escape sequences like \n and \t as it
 * copies the string t to s. Use a switch. Write a
 * function for the other direction as well,
 * converting escape sequences into the real
 * characters.
 */

#include <assert.h>
#include <string.h>

#define MAX 100

void escape(char[], const char[]);
void escape_rev(char[], const char[]);

void escape(char s[], const char t[]) {
    int i, j;
    i = j = 0;

    while (t[i] != '\0') {
        switch (t[i]) {
            case '\t':
                s[j++] = '\\';
                s[j]   = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j]   = 'n';
                break;
            default:
                s[j] = t[i];
                break;
        }
        i++, j++;
    }
    s[j] = '\0';
}

void escape_rev(char s[], const char t[]) {
    int i, j;
    i = j = 0;

    while (t[i] != '\0') {
        if (t[i] != '\\')
            s[j++] = t[i++];
        else {
            switch (t[++i]) {
                case 't':
                    s[j] = '\t';
                    break;
                case 'n':
                    s[j] = '\n';
                    break;
                default:
                    s[j] = t[i];
                    break;
            }
            i++, j++;
        }
    }
    s[j] = '\0';
}

int main(void) {
    char s[MAX];

    escape(s, "\n3\tR\n");                 /* copy pattern into s */
    assert(strcmp(s, "\\n3\\tR\\n") == 0); /* succefully converted */
    escape_rev(s, s);
    assert(strcmp(s, "\n3\tR\n") == 0); /* original pattern restored */

    return 0;
}