/*
 * Exercise 5-10. Write the program expr, which
 * evaluates a reverse Polish expression from the
 * command line, where each operator or operand
 * is a separate argument. For example,
 * expr 2 3 4 + *
 * evaluates 2 * (3+4).
 *
 * ---------------------------------
 * 
 * Note: Depending on the shell used, you should
 * escape wildcard, because shell would expand the glob.
 *
 * Some working examples:
 * ./prog 2 2 +     returns 4
 * ./prog 8 -2 -    returns 10
 * ./prog -8 -2 +   returns -10 (operands swapped)
 * ./prog -2 5 p    returns -32
 * 
 * Escaping wildcard in Linux:
 * ./prog -2 5 '*'
 *
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> /* for atof() */

#define MAXOP  100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

/* functions */
void   push(double);
double pop(void);

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

/* reverse polish calculator */

int main(int argc, char* argv[]) {
    double num;
    int    type;

    if (argc < 3) {
        printf("Error: not enough arguments\n");
        return -1;
    }

    while (--argc > 0) {
        num  = atof(*++argv);
        type = num ? NUMBER : **argv;

        switch (type) {
            case NUMBER:
                push(num);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '-':
                num = pop();
                push(pop() - num);
                break;
            case '*':
                num = pop();
                push(pop() * num);
                break;
            case '/':
                num = pop();
                if (num != 0.0)
                    push(pop() / num);
                else {
                    printf("error: zero divisor\n");
                    argc = -10;
                }
                break;
            case '%':
                num = pop();
                push(fmod(pop(), num));
                break;
            case 'c':
                push(cos(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'p':
                num = pop();
                push(pow(pop(), num));
                break;
            case 's':
                push(sin(pop()));
                break;
            default:
                printf("error: unknown command: %s\n", *argv);
                argc = -1;
                break;
        }
    }
    if (argc == 0)
        printf("Result: \t%.8g\n", pop());
    return argc;
}