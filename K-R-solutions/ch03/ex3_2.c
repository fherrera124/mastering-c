
/*
Exercise 3-2. Write a function escape(s,t) that converts
characters like newline and tab into visible escape
sequences like \n and \t as it copies the string t to s.
Use a switch. Write a function for the other direction
as well, converting escape sequences into the real
characters.
*/

#include <stdio.h>

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
    char s[10], t[10] = {'\n', '3', '\t', 'R', '\n', '\0'};

    escape(s, t);
    printf("%s\n", s);

    char v[10] = {'\\', 't', 'y', '4', '\\', 'n', 'q', '\0'};

    escape_rev(s, v);
    printf("%s\n", s);

    return 0;
}