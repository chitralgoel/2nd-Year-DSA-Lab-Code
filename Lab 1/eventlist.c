#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "eventlist.h"

/* READ ALL */

int read_all(FILE *fp, event_t e[], int n)
{
    int count = 0;

    while (count < n)
    {
        int dd, mm, yy;
        char detail[120];

        if (fscanf(fp, "%d-%d-%d %119s",
                   &dd, &mm, &yy, detail) != 4)
        {
            break;
        }

        e[count].d = make_date(dd, mm, yy);

        strncpy(e[count].detail, detail,
                sizeof(e[count].detail) - 1);

        e[count].detail[sizeof(e[count].detail) - 1] = '\0';

        count++;
    }

    return count;
}

/* ROBUST FILE LOADING  */

int load_events(const char *filename, event_t e[], int max)
{
    FILE *fp;
    char line[300];
    int count = 0;
    int skipped = 0;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Could not open file: %s\n", filename);
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int dd, mm, yy;
        char name[120];

        if (sscanf(line, "%d-%d-%d %119s",
                   &dd, &mm, &yy, name) == 4)
        {
            if (count < max)
            {
                e[count].d = make_date(dd, mm, yy);

                strncpy(e[count].detail, name,
                        sizeof(e[count].detail) - 1);

                e[count].detail[
                    sizeof(e[count].detail) - 1
                ] = '\0';

                count++;
            }
        }
        else
        {
            skipped++;
        }
    }

    fclose(fp);

    printf("Loaded %d events from '%s'.\n",
           count, filename);

    if (skipped > 0)
    {
        printf("Skipped %d invalid line(s).\n", skipped);
    }

    return count;
}

/* DISPLAY */

void disp_all(event_t e[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        printf("%3d. ", i + 1);
        print_event(e[i]);
        printf("\n");
    }
}


/* FIND LATEST */


event_t find_latest(event_t e[], int n)
{
    int i;
    event_t latest = e[0];

    for (i = 1; i < n; i++)
    {
        if (compare_event(e[i], latest) > 0)
        {
            latest = e[i];
        }
    }

    return latest;
}


/* COUNT MONTH */

int count_in_month(event_t e[], int n, int month)
{
    int i;
    int count = 0;

    for (i = 0; i < n; i++)
    {
        if (e[i].d.mm == month)
        {
            count++;
        }
    }

    return count;
}

/* REMOVE ON DATE */

int remove_on_date(event_t e[], int *n, date_t d)
{
    int i;
    int j;
    int removed = 0;

    for (i = 0; i < *n; i++)
    {
        if (compare_date(e[i].d, d) == 0)
        {
            for (j = i; j < *n - 1; j++)
            {
                e[j] = e[j + 1];
            }

            (*n)--;
            removed++;

            i--;
        }
    }

    return removed;
}

/* SORT BY DATE (MONTH + DAY) */

int compare_calendar(const void *a, const void *b)
{
    const event_t *e1 = (const event_t *)a;
    const event_t *e2 = (const event_t *)b;

    if (e1->d.mm != e2->d.mm)
        return e1->d.mm - e2->d.mm;

    if (e1->d.dd != e2->d.dd)
        return e1->d.dd - e2->d.dd;

    return e1->d.yy - e2->d.yy;
}

void sort_by_date(event_t e[], int n)
{
    qsort(e, n, sizeof(event_t), compare_calendar);
}

/* SORT BY YEAR  */

int compare_year(const void *a, const void *b)
{
    const event_t *e1 = (const event_t *)a;
    const event_t *e2 = (const event_t *)b;

    return compare_date(e1->d, e2->d);
}

void sort_by_year(event_t e[], int n)
{
    qsort(e, n, sizeof(event_t), compare_year);
}

/* SORT BY NAME */

int compare_name(const void *a, const void *b)
{
    const event_t *e1 = (const event_t *)a;
    const event_t *e2 = (const event_t *)b;

    return strcmp(e1->detail, e2->detail);
}

void sort_by_name(event_t e[], int n)
{
    qsort(e, n, sizeof(event_t), compare_name);
}

/* CASE INSENSITIVE SEARCH */

int contains_ignore_case(const char *text,
                         const char *keyword)
{
    int i;
    int j;

    for (i = 0; text[i] != '\0'; i++)
    {
        for (j = 0;
             keyword[j] != '\0' &&
             text[i + j] != '\0';
             j++)
        {
            if (tolower((unsigned char)text[i + j]) !=
                tolower((unsigned char)keyword[j]))
            {
                break;
            }
        }

        if (keyword[j] == '\0')
            return 1;
    }

    return 0;
}

int search_by_keyword(event_t e[], int n,
                      const char *keyword)
{
    int i;
    int found = 0;

    for (i = 0; i < n; i++)
    {
        if (contains_ignore_case(e[i].detail, keyword))
        {
            printf("%3d. ", i + 1);
            print_event(e[i]);
            printf("\n");

            found++;
        }
    }

    return found;
}

/* FILTER MONTH */

int filter_by_month(event_t e[], int n, int month)
{
    int i;
    int found = 0;

    for (i = 0; i < n; i++)
    {
        if (e[i].d.mm == month)
        {
            printf("%3d. ", found + 1);
            print_event(e[i]);
            printf("\n");

            found++;
        }
    }

    return found;
}


/* FILTER YEAR RANGE */

int filter_by_year_range(event_t e[], int n,
                         int start, int end)
{
    int i;
    int found = 0;

    for (i = 0; i < n; i++)
    {
        if (e[i].d.yy >= start &&
            e[i].d.yy <= end)
        {
            printf("%3d. ", found + 1);
            print_event(e[i]);
            printf("\n");

            found++;
        }
    }

    return found;
}

/* DATE UTILITIES */

int leap_year(int year)
{
    return (year % 400 == 0) ||
           (year % 4 == 0 && year % 100 != 0);
}

int days_in_month(int month, int year)
{
    int days[] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && leap_year(year))
        return 29;

    return days[month - 1];
}

int day_of_year(int day, int month, int year)
{
    int i;
    int total = day;

    for (i = 1; i < month; i++)
    {
        total += days_in_month(i, year);
    }

    return total;
}


/* UPCOMING EVENTS */

void upcoming_events(event_t e[], int n,
                     int today_day,
                     int today_month,
                     int days)
{
    int i;
    int today = day_of_year(today_day,
                            today_month,
                            2025);

    printf("\nUpcoming events:\n");

    for (i = 0; i < n; i++)
    {
        int event_day;
        event_day = day_of_year(
            e[i].d.dd,
            e[i].d.mm,
            e[i].d.yy
        );
        int difference;
        if (event_day >= today)
            difference = event_day - today;
        else
            difference = 365 - today + event_day;

        if (difference <= days)
        {
            printf("%3d. ", i + 1);
            print_event(e[i]);
            printf("  (%d day(s) away)\n",
                   difference);
        }
    }
}

/* MONTHLY CHART */

void monthly_chart(event_t e[], int n)
{
    int counts[12] = {0};
    int i;
    int month;

    for (i = 0; i < n; i++)
    {
        if (e[i].d.mm >= 1 &&
            e[i].d.mm <= 12)
        {
            counts[e[i].d.mm - 1]++;
        }
    }

    printf("\nEvents per month:\n");

    for (month = 0; month < 12; month++)
    {
        printf("%2d | ", month + 1);

        for (i = 0; i < counts[month]; i++)
        {
            printf("*");
        }

        printf(" (%d)\n", counts[month]);
    }
}

/* STATISTICS */

void statistics(event_t e[], int n)
{
    int i;
    int earliest;
    int latest;
    int counts[12] = {0};
    int busiest_month = 1;

    if (n == 0)
    {
        printf("No events available.\n");
        return;
    }

    earliest = e[0].d.yy;
    latest = e[0].d.yy;

    for (i = 0; i < n; i++)
    {
        if (e[i].d.yy < earliest)
            earliest = e[i].d.yy;

        if (e[i].d.yy > latest)
            latest = e[i].d.yy;

        if (e[i].d.mm >= 1 &&
            e[i].d.mm <= 12)
        {
            counts[e[i].d.mm - 1]++;
        }
    }

    for (i = 1; i < 12; i++)
    {
        if (counts[i] > counts[busiest_month - 1])
        {
            busiest_month = i + 1;
        }
    }

    printf("\n========== STATISTICS ==========\n");
    printf("Total events : %d\n", n);
    printf("Earliest year: %d\n", earliest);
    printf("Latest year  : %d\n", latest);
    printf("Busiest month: %d (%d event(s))\n",
           busiest_month,
           counts[busiest_month - 1]);
}

/* EXPORT */

int export_events(const char *filename,
                  event_t e[], int n)
{
    FILE *fp;
    int i;
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        fprintf(fp,
                "%02d-%02d-%04d %s\n",
                e[i].d.dd,
                e[i].d.mm,
                e[i].d.yy,
                e[i].detail);
    }
    fclose(fp);
    return 1;
}

/* EXACT DATE SEARCH */

int find_exact_date(event_t e[], int n, date_t d)
{
    int i;
    int found = 0;
    for (i = 0; i < n; i++)
    {
        if (compare_date(e[i].d, d) == 0)
        {
            printf("%3d. ", i + 1);
            print_event(e[i]);
            printf("\n");

            found++;
        }
    }
    return found;
}