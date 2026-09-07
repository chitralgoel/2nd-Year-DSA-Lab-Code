#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"

void initList(CircularList *list)
{
    list->current = NULL;
    list->size = 0;
}

int insertEnd(CircularList *list, int number, const char *name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
        return 0;

    newNode->number = number;

    if (name != NULL)
        strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    else
        newNode->name[0] = '\0';

    newNode->name[sizeof(newNode->name) - 1] = '\0';

    if (list->current == NULL) {
        newNode->next = newNode;
        list->current = newNode;
    } else {
        /*
         * current is the last node, so current->next is the
         * first node. Insert after current and make the new node
         * the last node.
         */
        newNode->next = list->current->next;
        list->current->next = newNode;
        list->current = newNode;
    }

    list->size++;
    return 1;
}

void displayList(const CircularList *list)
{
    Node *p;

    if (list->current == NULL) {
        printf("List is empty.\n");
        return;
    }

    p = list->current->next;

    printf("List: ");
    do {
        if (p->name[0] != '\0')
            printf("%d(%s)", p->number, p->name);
        else
            printf("%d", p->number);

        p = p->next;

        if (p != list->current->next)
            printf(" -> ");
    } while (p != list->current->next);

    printf("\n");
}

Node *removeAfter(CircularList *list)
{
    Node *removed;

    if (list == NULL || list->current == NULL)
        return NULL;

    removed = list->current->next;

    if (removed == list->current) {
        /* Only one node is present. */
        list->current = NULL;
    } else {
        list->current->next = removed->next;
    }

    removed->next = NULL;
    list->size--;

    return removed;
}

Node *locateAndRemove(CircularList *list, int k)
{
    int i;

    if (list == NULL || list->current == NULL || k < 1 || k > list->size)
        return NULL;

    /*
     * current is the node immediately before the person from whom
     * counting starts. Therefore:
     *   k = 1 -> current stays where it is
     *   k = 2 -> move once
     *   k = 3 -> move twice
     *
     * No special case is needed for k = 1.
     */
    for (i = 1; i < k; i++)
        list->current = list->current->next;

    /*
     * The k-th node is now immediately after current.
     * Requirement: removal must be done through removeAfter().
     */
    return removeAfter(list);
}

void freeList(CircularList *list)
{
    Node *first;
    Node *p;
    Node *next;

    if (list == NULL || list->current == NULL)
        return;

    first = list->current->next;
    p = first;

    do {
        next = p->next;
        free(p);
        p = next;
    } while (p != first);

    list->current = NULL;
    list->size = 0;
}
