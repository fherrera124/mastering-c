#include <assert.h>
#include <stdio.h>

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
    if (day < 1 || day > daytab[leap][month])
        return -1;

    for (i = 1; i < month; i++)
        day += daytab[leap][i];
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
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday   = yearday;
}

/*
 * Exercise 5-8. There is no error checking in
 * day_of_year or month_day. Remedy this defect.
 */
int main(void) {
    int m, d;

    printf("Date: 2022/6/26. Year of day: %d\n", day_of_year(2022, 6, 26));
    month_day(2022, 177, &m, &d);
    printf("Day and year: 177/2022. Month and day: %d %d\n", m, d);

    /* Tests */
    assert(day_of_year(2022, 2, 29) == -1);
    assert(day_of_year(2024, 2, 29) == 60);
    assert(day_of_year(2024, 22, 12) == -1);

    month_day(2022, 366, &m, &d);
    assert(m == -1 && d == -1);
    month_day(2024, 366, &m, &d);
    assert(m == 12 && d == 31);
    month_day(100, 500, &m, &d);
    assert(m == -1 && d == -1);

    return 0;
}