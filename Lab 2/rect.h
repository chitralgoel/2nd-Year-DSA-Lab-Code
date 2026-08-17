#ifndef RECT_H
#define RECT_H

/* Rectangle structure representing a layout site */
struct rect
{
    int length_;
    int breadth_;
};

typedef struct rect rect_t;

/* Function declarations */
void  set_rect(rect_t *ptr_rect, int length, int breadth);
void  disp_rect(rect_t *ptr_rect);
int   area_rect(rect_t *ptr_rect);

/* Returns 1 (true) if r1 is "smaller" than r2, based on area; else 0 */
int   compare_rect(rect_t *r1, rect_t *r2);

#endif
