/*
 * Exercise 5-7. Rewrite readlines to store lines
 * in an array supplied by main, rather than
 * calling alloc to maintain storage. How much
 * faster is the program?
 *
 * Answer: readlines() should be faster because
 * it doesn't have the overhead of calling the
 * alloc function on each iteration of its loop.
 */

#include <stdio.h>
#include <string.h>

#include "utils.h"

#define MAXLINES         5000                /* max #lines to be stored */
#define MAXLEN           1000                /* max length of any input line */
#define MAXSIZE          10000               /* size of available space */
#define CHARS_LEFT(X, Y) ((X + MAXSIZE) - Y) /* chars left on array X */

char *lineptr[MAXLINES]; /* pointers to text lines */

int  readlines(char *[], int, char[]);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
    int  nlines;         /* number of input lines read */
    char chars[MAXSIZE]; /* array to store lines */

    if ((nlines = readlines(lineptr, MAXLINES, chars)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char chars[]) {
    int   len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    p      = chars; /* pointer to the array */
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || len > CHARS_LEFT(chars, p)) {
            return -1;
        } else {
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
    int  i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}