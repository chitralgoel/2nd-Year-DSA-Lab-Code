#ifndef LIST_H
#define LIST_H

#include "rect.h"

/* Node structure -- now holds a rect instead of a plain integer key */
struct node
{
    rect_t       site_;
    struct node *next_;
};
typedef struct node node_t;

/* List structure */
struct mylist
{
    node_t *head_;
};
typedef struct mylist mylist_t;

/* Core list functions */
void init_list(mylist_t *ptr_list);
void insert_list(mylist_t *ptr_list, int length, int breadth);
void disp_list(mylist_t *ptr_list);
void free_list(mylist_t *ptr_list);

/* Additional problems */
int  total_layout_value(mylist_t *ptr_list, int unit_value);
int  find_highest_length(mylist_t *ptr_list, rect_t *result);
int  find_least_breadth(mylist_t *ptr_list, rect_t *result);

#endif