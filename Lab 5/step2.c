#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
#include "josephus.h"

static void readName(char *name, size_t size)
{
    size_t len;

    if (fgets(name, (int)size, stdin) == NULL) {
        name[0] = '\0';
        return;
    }

    len = strlen(name);
    if (len > 0 && name[len - 1] == '\n')
        name[len - 1] = '\0';
}

int main(void)
{
    CircularList list;
    int n, k, i;
    char name[100];
    Node *removed;

    initList(&list);

    printf("Enter number of people (n): ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid value of n. n must be at least 1.\n");
        return 1;
    }

    printf("Enter the count k [kth element is removed]: ");
    if (scanf("%d", &k) != 1 || k < 1) {
        printf("Invalid value of k. k must be at least 1.\n");
        return 1;
    }

    /* Consume the newline left by scanf(). */
    getchar();

    printf("\nEnter names of the %d people:\n", n);

    for (i = 1; i <= n; i++) {
        printf("Name of person #%d: ", i);
        readName(name, sizeof(name));

        if (name[0] == '\0') {
            printf("Name cannot be empty.\n");
            freeList(&list);
            return 1;
        }

        if (!insertEnd(&list, i, name)) {
            printf("Memory allocation failed.\n");
            freeList(&list);
            return 1;
        }
    }

    printf("\nInitial ");
    displayList(&list);

    printf("\nElimination order:\n");

    for (i = 1; i < n; i++) {
        int effectiveK = ((k - 1) % list.size) + 1;

        removed = josephusRemove(&list, effectiveK);

        if (removed == NULL) {
            printf("Removal failed.\n");
            freeList(&list);
            return 1;
        }

        printf("Round %d: %s (person #%d) executed\n",
               i, removed->name, removed->number);

        free(removed);
    }

    printf("\nSurvivor -> %s (person #%d)\n",
           list.current->name, list.current->number);

    freeList(&list);
    return 0;
}
