#include <stdio.h>
#include "rect.h"

/* Standalone test client for the rect module (Step 1).
   Reads dimensions from the keyboard and exercises
   set_rect / disp_rect / area_rect / compare_rect. */
int main()
{
    rect_t r1, r2;
    int l, b;

    printf("Enter length and breadth of rectangle 1: ");
    scanf("%d %d", &l, &b);
    set_rect(&r1, l, b);

    printf("Enter length and breadth of rectangle 2: ");
    scanf("%d %d", &l, &b);
    set_rect(&r2, l, b);

    printf("Rectangle 1: ");
    disp_rect(&r1);
    printf("\n");

    printf("Rectangle 2: ");
    disp_rect(&r2);
    printf("\n");

    printf("Area of rectangle 1 = %d\n", area_rect(&r1));
    printf("Area of rectangle 2 = %d\n", area_rect(&r2));

    if (compare_rect(&r1, &r2))
        printf("Rectangle 1 is smaller than Rectangle 2 (by area)\n");
    else if (compare_rect(&r2, &r1))
        printf("Rectangle 2 is smaller than Rectangle 1 (by area)\n");
    else
        printf("Rectangle 1 and Rectangle 2 have equal area\n");

    return 0;
}
