#ifndef EVENTLIST_H
#define EVENTLIST_H

#include <stdio.h>
#include "event.h"

#define MAX_EVENTS 100

int read_all(FILE *fp, event_t e[], int n);
void disp_all(event_t e[], int n);
event_t find_latest(event_t e[], int n);
int count_in_month(event_t e[], int n, int month);
int remove_on_date(event_t e[], int *n, date_t d);

int load_events(const char *filename, event_t e[], int max);
void sort_by_date(event_t e[], int n);
void sort_by_year(event_t e[], int n);
void sort_by_name(event_t e[], int n);

int search_by_keyword(event_t e[], int n, const char *keyword);
int filter_by_month(event_t e[], int n, int month);
int filter_by_year_range(event_t e[], int n, int start, int end);

void upcoming_events(event_t e[], int n,
                     int today_day, int today_month,
                     int days);

void monthly_chart(event_t e[], int n);
void statistics(event_t e[], int n);

int export_events(const char *filename, event_t e[], int n);

int find_exact_date(event_t e[], int n, date_t d);

#endif