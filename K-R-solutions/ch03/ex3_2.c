#include <stdio.h>


int  main(void) {

    return 0;
}

/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into
visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a
function for the other direction as well, converting escape sequences into the real characters.
*/
void escape(char s[], char t[]) {
    int i, j;
    i = j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\t':
                s[j] = 't';
                break;
            case '\n':
                s[j] = 'n';
                break;
            case ' ':
                s[j] = ' ';
                break;
            default:
                break;
        }
        i++;
        j++;
    }
    s[j] = '\0';
}