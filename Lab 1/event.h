#ifndef EVENT_H
#define EVENT_H

#include <stdio.h>
#include "date.h"

typedef struct {
    date_t d;
    char detail[120];
} event_t;

void read_event(FILE *fp, event_t *e);
void print_event(event_t e);
int compare_event(event_t e1, event_t e2);

#endif