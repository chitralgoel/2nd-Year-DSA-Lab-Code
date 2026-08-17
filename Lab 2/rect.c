#include <stdio.h>
#include "rect.h"

/* Set (initialize) the length and breadth of a rectangle */
void set_rect(rect_t *ptr_rect, int length, int breadth)
{
    ptr_rect->length_  = length;
    ptr_rect->breadth_ = breadth;
}

/* Display a rectangle */
void disp_rect(rect_t *ptr_rect)
{
    printf("(L=%d, B=%d, Area=%d) ", ptr_rect->length_, ptr_rect->breadth_,
           area_rect(ptr_rect));
}

/* Compute and return the area of a rectangle */
int area_rect(rect_t *ptr_rect)
{
    return ptr_rect->length_ * ptr_rect->breadth_;
}

/* Comparison function used for ordering by area.
   Returns 1 (true) if r1 is "smaller" than r2, 0 otherwise. */
int compare_rect(rect_t *r1, rect_t *r2)
{
    return area_rect(r1) < area_rect(r2);
}
