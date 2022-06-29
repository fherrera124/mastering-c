#include <assert.h>
#include <stdio.h>

/*
 * Exercise 5-9. Rewrite the routines day_of_year
 * and month_day with pointers instead of indexing.
 */

/*
 * My solution: casting the array as one dimensional
 * array of char pointers, then using rectangular subscript
 * calculation: (total_columns * row) + col
 */
#define ELEM(ARRAY, ROW, COLUMN) (*((char *)ARRAY + (13 * ROW) + COLUMN))

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    /* validate year and month input */
    if (year < 1 || month < 1 || month > 12)
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    /* validate day input */
    if (day < 1 || day > ELEM(daytab, leap, month))
        return -1;

    for (i = 1; i < month; i++)
        day += ELEM(daytab, leap, i);
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    /* validate year and yearday input */
    if (year < 1 || yearday < 1 || yearday > (365 + leap)) {
        *pmonth = *pday = -1;
        return;
    }
    for (i = 1; yearday > ELEM(daytab, leap, i); i++)
        yearday -= ELEM(daytab, leap, i);
    *pmonth = i;
    *pday   = yearday;
}

int main(void) {
    int m, d;

    printf("Date: 2022/6/26. Year of day: %d\n", day_of_year(2022, 6, 26));
    month_day(2022, 177, &m, &d);
    printf("Day and year: 177/2022. Month and day: %d %d\n", m, d);

    /* ######### TESTS ######### */

    /* day_of_year */
    assert(day_of_year(2022, 2, 29) == -1);  /* non-leap year */
    assert(day_of_year(2024, 2, 29) == 60);  /* leap year */
    assert(day_of_year(2024, 22, 12) == -1); /* invalid month number */

    /* month_day */
    month_day(2022, 366, &m, &d); /* non-leap year */
    assert(m == -1 && d == -1);
    month_day(2024, 366, &m, &d); /* leap year */
    assert(m == 12 && d == 31);
    month_day(100, 500, &m, &d); /* invalid day year */
    assert(m == -1 && d == -1);

    return 0;
}