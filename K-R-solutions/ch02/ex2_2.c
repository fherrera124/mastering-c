/*
 * Exercise 2-2. Write a loop equivalent
 * to the for loop above without using
 * && or ||.
 */

#include <stdio.h>

#define MAXLINE 1000

char line[MAXLINE];

int getline(void) {
    int c, i;

    /*
     * for (i = 0; i < MAXLINE - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
     *      line[i] = c;
    */

    for (i = 0; i < MAXLINE; ++i) {
        if ((c = getchar()) == '\n')
            break;
        if (c == EOF)
            break;
        line[i] = c;
    }
}

int main(void) {
    printf("Waiting for input: \n");
    getline();
    printf("Your input: %s", line);

    return 0;
}