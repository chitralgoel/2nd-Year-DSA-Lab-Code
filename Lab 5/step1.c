#include <stdio.h>
#include "clist.h"
#include "josephus.h"

int main(void)
{
    CircularList list;
    int n, k, i;
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

    /*
     * The counting repeats around the remaining circle, so k may
     * be larger than the current number of people.
     */
    for (i = 1; i <= n; i++) {
        if (!insertEnd(&list, i, NULL)) {
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

        printf("Round %d: person #%d executed\n", i, removed->number);
        free(removed);
    }

    printf("\nSurvivor -> person #%d\n", list.current->number);

    freeList(&list);
    return 0;
}
