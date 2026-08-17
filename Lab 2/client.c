#include <stdio.h>
#include "list.h"

int main()
{
    mylist_t list;
    int n, i, length, breadth, unit_value, total;
    rect_t result;

    /* Initialize */
    init_list(&list);

    /* Read number of sites and their dimensions */
    printf("Enter number of sites: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter length and breadth of site %d: ", i + 1);
        scanf("%d %d", &length, &breadth);
        insert_list(&list, length, breadth);
    }

    /* Display the ordered list (ascending by area) */
    printf("\nOrdered List of Sites (by area): ");
    disp_list(&list);

    /* Additional Problem 1: total value of the layout */
    printf("\nEnter value per unit area: ");
    scanf("%d", &unit_value);
    total = total_layout_value(&list, unit_value);
    printf("Total value of the layout = %d\n", total);

    /* Additional Problem 2: site with highest length */
    if (find_highest_length(&list, &result))
    {
        printf("\nSite with the highest length: ");
        disp_rect(&result);
        printf("\n");
    }

    /* Additional Problem 3: site with least breadth */
    if (find_least_breadth(&list, &result))
    {
        printf("\nSite with the least breadth: ");
        disp_rect(&result);
        printf("\n");
    }

    /* Free memory */
    free_list(&list);

    return 0;
}
