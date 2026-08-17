#include <stdio.h>
#include <string.h>

#include "date.h"
#include "event.h"
#include "eventlist.h"

void print_menu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("            EVENTS MENU\n");
    printf("========================================\n");

    printf(" 1. Display all events\n");

    printf("\n--- Sorting ---\n");
    printf(" 2. Sort by date\n");
    printf(" 3. Sort by year\n");
    printf(" 4. Sort by name\n");

    printf("\n--- Searching / Filtering ---\n");
    printf(" 5. Search by keyword\n");
    printf(" 6. Filter by month\n");
    printf(" 7. Filter by year range\n");
    printf(" 8. Upcoming events\n");
    printf("14. Find event on exact date\n");

    printf("\n--- Analysis ---\n");
    printf(" 9. Events-per-month chart\n");
    printf("10. Statistics\n");

    printf("\n--- File ---\n");
    printf("11. Export current list\n");

    printf("\n--- Lab 1 Operations ---\n");
    printf("12. Find latest event\n");
    printf("13. Count events in a month\n");
    printf("15. Remove events on a date\n");

    printf("\n16. Reset to original list\n");

    printf("\n 0. Exit\n");

    printf("========================================\n");
}


int main(int argc, char *argv[])
{
    char filename[200] = "events.txt";

    event_t events[MAX_EVENTS];
    event_t original[MAX_EVENTS];

    int count;
    int original_count;
    
    if (argc >= 2)
    {
        strncpy(filename, argv[1], sizeof(filename) - 1);
        filename[sizeof(filename) - 1] = '\0';
    }
    count = load_events(filename, events, MAX_EVENTS);

    if (count < 0)
    {
        return 1;
    }
    original_count = count;
    memcpy(original,
           events,
           sizeof(event_t) * count);

    printf("\nLoaded %d events.\n", count);

    while (1)
    {
        int choice;

        print_menu();

        printf("\nChoose an option: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n')
                ;

            continue;
        }

        switch (choice)
        {
            case 1:
            {
                printf("\n--- All Events (%d entries) ---\n",
                       count);

                disp_all(events, count);

                break;
            }
            case 2:
            {
                sort_by_date(events, count);

                printf("\n--- Sorted by Date ---\n");

                disp_all(events, count);

                break;
            }
            case 3:
            {
                sort_by_year(events, count);

                printf("\n--- Sorted by Year ---\n");

                disp_all(events, count);

                break;
            }
            case 4:
            {
                sort_by_name(events, count);

                printf("\n--- Sorted by Name ---\n");

                disp_all(events, count);

                break;
            }
            case 5:
            {
                char keyword[120];

                printf("Enter keyword: ");
                scanf("%119s", keyword);

                printf("\n--- Search Results ---\n");

                int found =
                    search_by_keyword(events,
                                      count,
                                      keyword);

                printf("\n%d event(s) found.\n",
                       found);

                break;
            }
            case 6:
            {
                int month;

                printf("Enter month (1-12): ");
                scanf("%d", &month);

                if (month < 1 || month > 12)
                {
                    printf("Invalid month.\n");
                }
                else
                {
                    printf("\n--- Events in Month %d ---\n",
                           month);

                    int found =
                        filter_by_month(events,
                                        count,
                                        month);

                    printf("\n%d event(s) found.\n",
                           found);
                }

                break;
            }
            case 7:
            {
                int start;
                int end;

                printf("Enter start year: ");
                scanf("%d", &start);

                printf("Enter end year: ");
                scanf("%d", &end);

                if (start > end)
                {
                    printf("Invalid year range.\n");
                }
                else
                {
                    printf("\n--- Events from %d to %d ---\n",
                           start,
                           end);

                    int found =
                        filter_by_year_range(events,
                                             count,
                                             start,
                                             end);

                    printf("\n%d event(s) found.\n",
                           found);
                }

                break;
            }
            case 8:
            {
                int day;
                int month;
                int days;

                printf("Enter today's day: ");
                scanf("%d", &day);

                printf("Enter today's month: ");
                scanf("%d", &month);

                printf("Enter number of upcoming days: ");
                scanf("%d", &days);

                if (day < 1 ||
                    day > 31 ||
                    month < 1 ||
                    month > 12 ||
                    days < 0)
                {
                    printf("Invalid input.\n");
                }
                else
                {
                    upcoming_events(events,
                                    count,
                                    day,
                                    month,
                                    days);
                }

                break;
            }
            case 9:
            {
                monthly_chart(events, count);

                break;
            }
            case 10:
            {
                statistics(events, count);

                break;
            }
            case 11:
            {
                char output[200];

                printf("Enter output filename: ");
                scanf("%199s", output);

                if (export_events(output,
                                  events,
                                  count))
                {
                    printf("Successfully exported to %s\n",
                           output);
                }
                else
                {
                    printf("Could not create output file.\n");
                }

                break;
            }
            case 12:
            {
                if (count == 0)
                {
                    printf("No events available.\n");
                }
                else
                {
                    event_t latest;

                    latest =
                        find_latest(events, count);

                    printf("\nLatest event: ");

                    print_event(latest);

                    printf("\n");
                }

                break;
            }
            case 13:
            {
                int month;

                printf("Enter month (1-12): ");
                scanf("%d", &month);

                if (month < 1 || month > 12)
                {
                    printf("Invalid month.\n");
                }
                else
                {
                    int found =
                        count_in_month(events,
                                       count,
                                       month);

                    printf("%d event(s) found in month %d.\n",
                           found,
                           month);
                }

                break;
            }
            case 14:
            {
                int day;
                int month;
                int year;

                printf("Enter day: ");
                scanf("%d", &day);

                printf("Enter month: ");
                scanf("%d", &month);

                printf("Enter year: ");
                scanf("%d", &year);

                date_t d =
                    make_date(day,
                              month,
                              year);

                int found =
                    find_exact_date(events,
                                    count,
                                    d);

                if (found == 0)
                {
                    printf("No event found on that date.\n");
                }

                break;
            }
            case 15:
            {
                int day;
                int month;
                int year;

                printf("Enter day: ");
                scanf("%d", &day);

                printf("Enter month: ");
                scanf("%d", &month);

                printf("Enter year: ");
                scanf("%d", &year);

                date_t d =
                    make_date(day,
                              month,
                              year);

                int removed =
                    remove_on_date(events,
                                   &count,
                                   d);

                printf("%d event(s) removed.\n",
                       removed);

                break;
            }
            case 16:
            {
                memcpy(events,
                       original,
                       sizeof(event_t) *
                       original_count);

                count = original_count;

                printf("List reset to original list.\n");

                break;
            }
            case 0:
            {
                printf("Exiting program...\n");

                return 0;
            }
            default:
            {
                printf("Invalid choice. Please try again.\n");

                break;
            }
        }
    }

    return 0;
}