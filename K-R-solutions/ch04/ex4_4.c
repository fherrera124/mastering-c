/*
Exercise 4-4. Add the commands to print the top elements of
the stack without popping, to duplicate it, and to swap the
top two elements. Add a command to clear the stack.

Note: this version ignores newlines, if you want to consume
the top value from stack, use '='. Use '?' to just peek.
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
double peek(void);
void   swap(void);
void   clear(void);
void   dup(void);
int    getch(void);
void   ungetch(int);
int    getop(char[]);

/* globals */
int    sp = 0;       /* next free stack position */
double val[MAXVAL];  /* value stack */
char   buf[BUFSIZE]; /* buffer for ungetch */
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

int getch(void) { /* get a (possibly pushed-back) character */
    return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
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
                push(pop() - pop());
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
            case 'd':
                dup();
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
            case '\n':
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}
