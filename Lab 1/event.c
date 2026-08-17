#include <stdio.h>
#include <string.h>
#include "event.h"

void read_event(FILE *fp, event_t *e)
{
    char temp[120];

    if (fscanf(fp, "%d-%d-%d %119s",
               &e->d.dd,
               &e->d.mm,
               &e->d.yy,
               temp) == 4)
    {
        strncpy(e->detail, temp, sizeof(e->detail) - 1);
        e->detail[sizeof(e->detail) - 1] = '\0';
    }
}
void print_event(event_t e)
{
    print_date(e.d);
    printf(" %s", e.detail);
}
int compare_event(event_t e1, event_t e2)
{
    return compare_date(e1.d, e2.d);
}