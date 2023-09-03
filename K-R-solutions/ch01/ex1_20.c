/*
 * Exercise 1-20. Write a program detab that replaces
 * tabs in the input with the proper number of blanks
 * to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns. Should n be a
 * variable or a symbolic parameter?
 */

#include "utils.h"

#define MAXLINE 100

void detab(char in[], char out[]) {
    char c;
    int  i, j, n;

    for (i = j = 0; c = in[i]; i++) {
        if (c == '\t')
            

        out[j] =
    }
}

int main() {
    char c, line[MAXLINE];

    getline(line, MAXLINE);

    for (int i = 0; (c = line[i]) != '\0'; i++) {
    }
}