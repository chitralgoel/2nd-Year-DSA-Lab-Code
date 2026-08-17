#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(mylist_t *ptr_list)
{
    ptr_list->head_ = NULL;
}

// 1. empty list
// 2. insert in the middle
// 3. insert in the beginning
// 4. insert at the end

void insert_list(mylist_t *ptr_list, int length, int breadth)
{
    // create the node
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    set_rect(&temp->site_, length, breadth);
    temp->next_ = NULL;

    // 1. empty list
    if (ptr_list->head_ == NULL)
    {
        ptr_list->head_ = temp;
        temp->next_ = NULL;
    }
    else
    {
        // traverse -- ordering is now done by area via compare_rect
        node_t *prev = NULL;
        node_t *pres = ptr_list->head_;
        while (pres != NULL && compare_rect(&pres->site_, &temp->site_))
        {
            prev = pres;
            pres = pres->next_;
        }
        if (prev == NULL) // insert in the beginning
        {
            temp->next_ = pres;
            ptr_list->head_ = temp;
        }
        else // middle or end
        {
            temp->next_ = pres;
            prev->next_ = temp;
        }
    }
}

/* Display the list */
void disp_list(mylist_t *ptr_list)
{
    node_t *q = ptr_list->head_;

    while (q != NULL)
    {
        disp_rect(&q->site_);
        q = q->next_;
    }

    printf("\n");
}

/* Free the list */
void free_list(mylist_t *ptr_list)
{
    node_t *q = ptr_list->head_;
    node_t *r;

    while (q != NULL)
    {
        r = q->next_;
        free(q);
        q = r;
    }

    ptr_list->head_ = NULL;
}

/* Additional Problem 1: total value of the layout = sum(area * unit_value) */
int total_layout_value(mylist_t *ptr_list, int unit_value)
{
    int total = 0;
    node_t *q = ptr_list->head_;

    while (q != NULL)
    {
        total += area_rect(&q->site_) * unit_value;
        q = q->next_;
    }

    return total;
}

/* Additional Problem 2: site with the highest length.
   Returns 1 and fills *result if list is non-empty, else returns 0. */
int find_highest_length(mylist_t *ptr_list, rect_t *result)
{
    node_t *q = ptr_list->head_;

    if (q == NULL)
        return 0;

    *result = q->site_;
    q = q->next_;

    while (q != NULL)
    {
        if (q->site_.length_ > result->length_)
            *result = q->site_;
        q = q->next_;
    }

    return 1;
}

/* Additional Problem 3: site with the least breadth.
   Returns 1 and fills *result if list is non-empty, else returns 0. */
int find_least_breadth(mylist_t *ptr_list, rect_t *result)
{
    node_t *q = ptr_list->head_;

    if (q == NULL)
        return 0;

    *result = q->site_;
    q = q->next_;

    while (q != NULL)
    {
        if (q->site_.breadth_ < result->breadth_)
            *result = q->site_;
        q = q->next_;
    }

    return 1;
}