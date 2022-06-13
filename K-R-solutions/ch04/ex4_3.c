/*
Exercise 4-3. Given the basic framework, it's straightforward
to extend the calculator. Add the modulus (%) operator and
provisions for negative numbers.
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100

/* functions */
void   push(double);
double pop(void);
int    getch(void);
void   ungetch(int);
int    getop(char[]);

/* globals */
int    sp = 0;       /* next free stack position */
double val[MAXVAL];  /* value stack */
char   buf[BUFSIZE]; /* buffet for ungetch */
int    bufp = 0;     /* next free position in buf */

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
    i    = 0;

    if (c == '-') {
        if (isdigit(c = getch())) /* asume '-' as negative of c */
            s[++i] = c;
        else {
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
        ungetch(c); /* unget the nonnumeric character*/
    printf("number: %s\n", s);
    return NUMBER;
}

int getch(void) { /* get a (possibly pushed-back) character */
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters");
    else
        buf[bufp++] = c;
}

/* reverse polish calculator */

int main(void) {
    int    type;
    double op2;
    char   s[MAXOP];

    double e = -4;

    printf("%g\n", e);

    while ((type = getop(s)) != EOF && type != '\n') {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                push(pop() - pop());
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
            default:
                break;
        }
    }
    printf("Result: %g\n", pop());

    return 0;
}