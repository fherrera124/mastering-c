/*
 * Exercise 3-1. Our binary search makes two tests
 * inside the loop, when one would suffice (at the
 * price of more tests outside.) Write a version with
 * only one test inside the loop and measure the
 * difference in run-time.
 * 
 * ANSWER: we can test only if x is lower than the current
 * value on the array, so that if x its equal or greater
 * will fall in the else statement. Then when the loop ends
 * we evaluate once if x was found in the array. Evaluating
 * outside the loop once than everitime in the loop is an
 * advantage. The disanvanatge is that the loop wont break
 * when the value is found, it still run until while
 * condition evaluates false. 
 */

#include <stdio.h>

int binsearch(int, int[], int);

int main(void) {
    int arr[] = {2, 4, 6, 7, 9, 29, 45, 46, 49, 50, 51};
    // printf("%d", binsearch(2, arr, 11));
    return 0;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n-1] */

// int arr[] = {2, 4, 6, 7, 9, 29, 45, 46, 49, 50, 51};
int binsearch(int x, int v[], int n) {
    int low, high, mid;
    low  = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return (x == v[mid]) ? mid : -1;
}