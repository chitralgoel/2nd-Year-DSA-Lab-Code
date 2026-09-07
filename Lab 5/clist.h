#ifndef CLIST_H
#define CLIST_H

typedef struct Node {
    int number;
    char name[100];
    struct Node *next;
} Node;

typedef struct {
    Node *current;   /* Node before the next person to be counted */
    int size;
} CircularList;

void initList(CircularList *list);
int insertEnd(CircularList *list, int number, const char *name);
void displayList(const CircularList *list);

/* Removes and returns the node immediately after current.
   The caller is responsible for freeing the returned node. */
Node *removeAfter(CircularList *list);

/* Locates the k-th person, removes that node using removeAfter(),
   and returns the removed node. */
Node *locateAndRemove(CircularList *list, int k);

void freeList(CircularList *list);

#endif
