/*
Exercise 4-3. Given the basic framework, it's straightforward
to extend the calculator. Add the modulus (%) operator and
provisions for negative numbers.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#include "utils.h"

#define MAXOP  100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

/* functions */
void   push(double);
double pop(void);

int getop(char[]);

/* globals */
int    sp = 0;      /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else
        printf("error: stack empty\n");
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (c == '-') { /* check if '-' is operand or sign */
        if (!isdigit(s[++i] = c = getch())) {
            ungetch(c);
            c = '-';
        }
    }
    if (!isdigit(c) && c != '.')
        return c;   /* not a number */
    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c); /* unget the non-numeric character*/
    return NUMBER;
}

/* reverse polish calculator */

int main(void) {
    int    type;
    double op2;
    char   s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '*':
                op2 = pop();
                push(pop() * op2);
                break;
            case '/':
                op2 = pop();
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                break;
        }
    }
    return 0;
}
