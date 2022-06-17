/*
Exercise 4-10. An alternate organization uses getline to read
an entire input line; this makes getch and ungetch
unnecessary. Revise the calculator to use this approach.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#include "utils.h"

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100

/* functions */
void   push(double);
double pop(void);
double peek(void);
void   swap(void);
void   clear(void);
void   dup(void);
int    getop(char[]);

/* globals */
int    sp = 0;           /* next free stack position */
double val[MAXVAL];      /* value stack */
char   bufline[BUFSIZE]; /* buffer for getline */
int    bufp = 0;         /* next position in bufline */

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

/* peek: return top value from stack without popping*/
double peek(void) {
    if (sp > 0)
        return val[sp - 1];
    else
        printf("warning: stack empty\n");
}

/* clear: clear the stack */
void clear(void) {
    sp = 0;
}

/* dup: duplicate top value from stack*/
void dup(void) {
    if (sp > 0)
        push(peek());
    else
        printf("error: stack empty\n");
}

/* swap: swap the top two values from stack*/
void swap(void) {
    double tmp, tmp2;
    if (sp >= 2) {
        tmp  = pop();
        tmp2 = pop();
        push(tmp);
        push(tmp2);
    } else
        printf("error: need at least two values on stack\n");
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = bufline[bufp++]) == ' ' || c == '\t')
        ;
    s[1] = '\0';

    i = 0;
    if (c == '-') { /* check if '-' is operand or sign */
        if (!isdigit(s[++i] = c = bufline[bufp++])) {
            bufp--;
            c = '-';
        }
    }
    if (!isdigit(c) && c != '.')
        return c;     /* not a number */
    if (isdigit(c)) { /* collect integer part */
        while (isdigit(s[++i] = c = bufline[bufp++]))
            ;
    }
    if (c == '.') { /* collect fraction part */
        while (isdigit(s[++i] = c = bufline[bufp++]))
            ;
    }
    s[i] = '\0';

    return NUMBER;
}

/* reverse polish calculator */

int main(void) {
    double op2;
    char   s[MAXOP];

    getline(bufline, MAXOP);

    for (;;) {
        switch (getop(s)) {
            case '\0': /* start over */
                bufp = 0;
                getline(bufline, MAXOP);
                break;
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
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '%':
                op2 = pop();
                push(fmod(pop(), op2));
                break;
            case 'c':
                push(cos(pop()));
                break;
            case 'd':
                dup();
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'p':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 's':
                push(sin(pop()));
                break;
            case 'w':
                swap();
                break;
            case '=':
                printf("\t%.8g\n", pop());
                break;
            case '?':
                printf("peek: %g\n", peek());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}
