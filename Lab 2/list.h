#ifndef LIST_H
#define LIST_H
/* Node structure */
struct node
{
    int key_;
    struct node *next_;
};
typedef struct node node_t;

/* List structure */
struct mylist
{
    node_t *head_;
};

typedef struct mylist mylist_t;

/* Function declarations */
void init_list(mylist_t *);
void insert_list(mylist_t *, int);
void disp_list(mylist_t *);
void free_list(mylist_t *);
#endif