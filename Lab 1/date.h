#ifndef DATE_H
#define DATE_H

#include <stdio.h>

typedef struct {
    int dd, mm, yy;
} date_t;

date_t make_date(int dd, int mm, int yy);
void read_date(FILE *fp, date_t *d);
void print_date(date_t d);
int compare_date(date_t d1, date_t d2);

#endif